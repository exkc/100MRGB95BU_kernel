/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		justine.jeong
 *  @version	1.0
 *  @date		2018-05-29
 *  @note		Additional information.
 */

#ifdef INCLUDE_KDRV_BE

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#ifdef ENABLE_UCR
#if 0
#include "linux/v4l2-ext/v4l2-controls-ext_id.h"
#include "linux/v4l2-ext/videodev2-ext_id.h"
#endif
#endif

#include "os_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "pe_cmn.h"
#include "pe_csc.h"
#include "v4l2_vpq_be.h"
#include "vpq_hwrap_be.h"

#include "be_def.h"
#include "be_kapi.h"
#include "ovi_kapi.h"
#include "be_proc.h"
#include "be_top_hal.h"
#include "led_hal.h"
#include "pwm_hal.h"
#include "ovi_hal.h"
#include "vp_kwrap.h"
#include "v4l2_vpq.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define _VPQ_BE_CSC_X100002H(x, bit)	_VPQ_BE_ConvCscX10000ToHex((SINT16)(x), (UINT8)(bit))

/* 20231121, V4L2_CID_EXT_VPQ_GAMUT_ENABLE (SICREQ-536) */
#ifndef V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE
#define V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE (V4L2_CID_EXT_VPQ_BASE + 43)
#endif
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#if 0	//ref.
/* https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/vidioc-g-ctrl.html */
struct v4l2_control
{
	unsigned int id;
	int value;
};

/* https://www.kernel.org/doc/html/v4.12/media/uapi/v4l/vidioc-g-ext-ctrls.html */
struct v4l2_ext_control
{
	unsigned int id;
	unsigned int size;
	unsigned int reserved2[1];
	union
	{
		int value;
		signed long long value64;
		char *string;
		unsigned char *p_u8;
		unsigned short *p_u16;
		unsigned int *p_u32;
		void *ptr;
	};
};

/* https://www.kernel.org/doc/html/v4.12/media/uapi/v4l/vidioc-g-ext-ctrls.html */
struct v4l2_ext_controls
{
	union
	{
		unsigned int ctrl_class;
		unsigned int which;
	};
	unsigned int count;
	unsigned int error_idx;
	unsigned int reserved[2];
	struct v4l2_ext_control *controls;
};
#endif

typedef struct
{
	UINT8	u8Blur; 				// 0~9 : Blur level
	UINT8	u8Judder;				// 0~9 : Judder level
	UINT8	u8MemcType; 			// 0 : OFF, 1: LOW, 2:MID, 3:HIGH, 4:USER, 5: PULLDOWN55 : @ref FRC_MC_TYPE_T
	UINT8	_rsvd;					//reservved
} FRC_MEMC_MODE_T;

typedef struct
{
	unsigned short *u16pT_degamma;
	unsigned int	degamma_size_num;
	unsigned short *u16pT_regamma;
	unsigned int	regamma_size_num;
} DEGAMMA_REGAMMA_T;

typedef struct
{
	struct v4l2_ext_led_ldim_demo_info	demoInfo;
	struct v4l2_ext_led_spi_ctrl_info	ctrlSpi;
	struct v4l2_ext_led_bpl_info	bplInfo;
	UINT32						ledDbIdx;
	UINT32						ledEn;
	UINT32						ledPanelInch;
	UINT32						pwmRatio;
	UINT16 						pccMatrix[LX_BE_PQ_NUM_OF_PCC_COEF];
} BE_PQ_STATUS_DATA_T;

/*-----------------------------------------------------------------------------
                             0xCC9C8C00 FRC INFO
-----------------------------------------------------------------------------*/
typedef union { 
    UINT32 udata32; 
    struct { //0xCC9C8C00 RW 0x0000_0000 
    UINT32 cadence           :10; //( 9:0,RW,0x00)  
    UINT32 reserved          :22; //(23:0,RW,0x0000_0000)  
    };
}REG_FRCINFO_FW_TO_DRIVER_0_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void v4l2_vsc_update_pulldown(UINT32 type);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BOOLEAN _gMemcLowDelay = FALSE;
BOOLEAN _gMemcMotionPro = FALSE;
int _gOaplWeghtCtrl = 0;
volatile REG_FRCINFO_FW_TO_DRIVER_0_T *gBE_TOP_FRC_INFO = NULL;
static UINT32 _gVfreq = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static FRC_MEMC_MODE_T gMemcMode;
static DEGAMMA_REGAMMA_T gGammaMode;
static BE_PQ_STATUS_DATA_T gBeStatus;
/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static UINT32 _VPQ_BE_ConvCscX10000ToHex(SINT16 input, UINT8 signBit)
{
	UINT32 output = 0;
	SINT32 temp = 0;

	temp = (SINT32)((input*4096)/10000);

	if (temp&((0x1)<<signBit))
		output = temp | ( 0xffffffff << signBit );
	else
		output = temp & ( 0xffffffff >> (31-signBit) );

	return output;
}

static UINT32 _VPQ_BE_LEDPanelInchEnumToInch(enum v4l2_ext_led_panel_inch_type enumType)
{
	#define VPQ_BE_LED_CASE_ENUM_TO_INCH(x)	case (x):return simple_strtol(&(TO_STR(x)[18]), NULL, 10)

    switch (enumType)
	{
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_32);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_39);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_42);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_47);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_49);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_50);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_55);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_58);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_60);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_65);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_70);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_77);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_79);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_84);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_98);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_105);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_23);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_24);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_26);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_27);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_22);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_28);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_40);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_43);
		VPQ_BE_LED_CASE_ENUM_TO_INCH(V4L2_EXT_LED_INCH_86);
		default:                            return 0;
	}
}

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/

void v4l2_vpq_detect_vFreq(UINT32 v_freq)
{
	_gVfreq = v_freq;
	PE_PRINT_NOTI("LATENCY inputSrc Vfreq: %d", _gVfreq);
	return;
}

/*========================================================================================
	Implementation Group
========================================================================================*/

int v4l2_vpq_compat_vidioc_ext_ctrls_be(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36)
	#ifdef CONFIG_COMPAT
	switch (ctrl->id) {
		case V4L2_CID_EXT_LED_INIT:
		case V4L2_CID_EXT_LED_DEMOMODE:
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		case V4L2_CID_EXT_LED_APL_DATA:
		case V4L2_CID_EXT_LED_BPL_DATA:
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		case V4L2_CID_EXT_VPQ_LUMINANCE_BOOST:
		case V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT:
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		case V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO:
		case V4L2_CID_EXT_VPQ_MCC_DATA:
		case V4L2_CID_EXT_VPQ_MCC_LUT:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			//PE_PRINT_VPQ_BE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			//PE_PRINT_VPQ_BE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			//PE_PRINT_VPQ_BE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
		}break;
		case V4L2_CID_EXT_LED_DB_DATA:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			v4l2_hwrap_led_lut arg_buf2;
			v4l2_hwrap_led_lut_v2 arg_buf3;
			v4l2_hwrap_led_lut_v3 arg_buf4;
			int i;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if (arg_buf.version == 0x40)
			{
				if(copy_from_user(&arg_buf3,(void __user *)arg_buf.p_data,sizeof(v4l2_hwrap_led_lut_v2)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				arg_buf3.pq_common.pData = (unsigned int *)(uintptr_t)arg_buf3.pq_common.compat_pData;
				arg_buf3.moduleAdj.pData = (unsigned int *)(uintptr_t)arg_buf3.moduleAdj.compat_pData;
				arg_buf3.unsharpMask.pData = (unsigned int *)(uintptr_t)arg_buf3.unsharpMask.compat_pData;
				arg_buf3.lightProfile.sbiHCoef.pData = (unsigned int *)(uintptr_t)arg_buf3.lightProfile.sbiHCoef.compat_pData;
				arg_buf3.lightProfile.sbiVCoef.pData = (unsigned int *)(uintptr_t)arg_buf3.lightProfile.sbiVCoef.compat_pData;
				arg_buf3.lightProfile.lres1TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf3.lightProfile.lres1TabCoef.compat_pData;
				arg_buf3.lightProfile.lres5TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf3.lightProfile.lres5TabCoef.compat_pData;
				for (i=0; i<LX_BE_LED_UI_V2_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_v2_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					arg_buf3.dimmingCurve.upperCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf3.dimmingCurve.upperCurve[i].compat_pData;
					arg_buf3.dimmingCurve.lowerCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf3.dimmingCurve.lowerCurve[i].compat_pData;
					arg_buf3.uiAdj_lut[i].pData = (unsigned int *)(uintptr_t)arg_buf3.uiAdj_lut[i].compat_pData;
					arg_buf3.pixelCompensation[i].pData = (unsigned int *)(uintptr_t)arg_buf3.pixelCompensation[i].compat_pData;
				}
				arg_buf3.smartBvGain.pData = (unsigned int *)(uintptr_t)arg_buf3.smartBvGain.compat_pData;
				if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf3,sizeof(v4l2_hwrap_led_lut_v2)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if (arg_buf.version == 0x60)
			{
				if(copy_from_user(&arg_buf4,(void __user *)arg_buf.p_data,sizeof(v4l2_hwrap_led_lut_v3)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				arg_buf4.pq_common.pData = (unsigned int *)(uintptr_t)arg_buf4.pq_common.compat_pData;
				arg_buf4.moduleAdj.pData = (unsigned int *)(uintptr_t)arg_buf4.moduleAdj.compat_pData;
				arg_buf4.unsharpMask.pData = (unsigned int *)(uintptr_t)arg_buf4.unsharpMask.compat_pData;
				arg_buf4.lightProfile.sbiHCoef.pData = (unsigned int *)(uintptr_t)arg_buf4.lightProfile.sbiHCoef.compat_pData;
				arg_buf4.lightProfile.sbiVCoef.pData = (unsigned int *)(uintptr_t)arg_buf4.lightProfile.sbiVCoef.compat_pData;
				arg_buf4.lightProfile.lres1TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf4.lightProfile.lres1TabCoef.compat_pData;
				arg_buf4.lightProfile.lres5TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf4.lightProfile.lres5TabCoef.compat_pData;
				for (i=0; i<LX_BE_LED_UI_V3_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_v3_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					arg_buf4.dimmingCurve.upperCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf4.dimmingCurve.upperCurve[i].compat_pData;
					arg_buf4.dimmingCurve.lowerCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf4.dimmingCurve.lowerCurve[i].compat_pData;
					arg_buf4.uiAdj_lut[i].pData = (unsigned int *)(uintptr_t)arg_buf4.uiAdj_lut[i].compat_pData;
					arg_buf4.pixelCompensation[i].pData = (unsigned int *)(uintptr_t)arg_buf4.pixelCompensation[i].compat_pData;
				}
				arg_buf4.smartBvGain.pData = (unsigned int *)(uintptr_t)arg_buf4.smartBvGain.compat_pData;
				if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf4,sizeof(v4l2_hwrap_led_lut_v3)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if (arg_buf.version == 0x80)
			{
				LX_BE_LED_DB_LUT_v80_T data_80;
				if (copy_from_user(&data_80,(void __user *)arg_buf.p_data,sizeof(LX_BE_LED_DB_LUT_v80_T)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				data_80.pq_common_lut.pData = (unsigned int *)(uintptr_t)data_80.pq_common_lut.compat_pData;
				data_80.module_lut.pData = (unsigned int *)(uintptr_t)data_80.module_lut.compat_pData;
				data_80.lightProfile_lut.sbiHCoef.pData = (unsigned int *)(uintptr_t)data_80.lightProfile_lut.sbiHCoef.compat_pData;
				data_80.lightProfile_lut.sbiVCoef.pData = (unsigned int *)(uintptr_t)data_80.lightProfile_lut.sbiVCoef.compat_pData;
				data_80.lightProfile_lut.lres1TabCoef.pData = (unsigned int *)(uintptr_t)data_80.lightProfile_lut.lres1TabCoef.compat_pData;
				data_80.lightProfile_lut.lres5TabCoef.pData = (unsigned int *)(uintptr_t)data_80.lightProfile_lut.lres5TabCoef.compat_pData;
				for (i=0; i<LED_DB_UI_ADJ_v80_MAX; i++)
				{
					data_80.dimmingCurve_lut.upperCurve[i].pData = (unsigned int *)(uintptr_t)data_80.dimmingCurve_lut.upperCurve[i].compat_pData;
					data_80.dimmingCurve_lut.lowerCurve[i].pData = (unsigned int *)(uintptr_t)data_80.dimmingCurve_lut.lowerCurve[i].compat_pData;
					data_80.pqUi_lut[i].pData = (unsigned int *)(uintptr_t)data_80.pqUi_lut[i].compat_pData;
					data_80.pixelCompensation_lut[i].pData = (unsigned int *)(uintptr_t)data_80.pixelCompensation_lut[i].compat_pData;
					data_80.unsharpMask_lut[i].pData = (unsigned int *)(uintptr_t)data_80.unsharpMask_lut[i].compat_pData;
					data_80.contgain_lut[i].pData = (unsigned int *)(uintptr_t)data_80.contgain_lut[i].compat_pData;
					data_80.blooming_lut[i].pData = (unsigned int *)(uintptr_t)data_80.blooming_lut[i].compat_pData;
				}
				if (copy_to_user((void __user *)arg_buf.p_data,&data_80,sizeof(LX_BE_LED_DB_LUT_v80_T)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else
			{
				if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(v4l2_hwrap_led_lut)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				arg_buf2.pq_common.pData = (unsigned int *)(uintptr_t)arg_buf2.pq_common.compat_pData;
				arg_buf2.moduleAdj.pData = (unsigned int *)(uintptr_t)arg_buf2.moduleAdj.compat_pData;
				arg_buf2.unsharpMask.pData = (unsigned int *)(uintptr_t)arg_buf2.unsharpMask.compat_pData;
				arg_buf2.lightProfile.sbiHCoef.pData = (unsigned int *)(uintptr_t)arg_buf2.lightProfile.sbiHCoef.compat_pData;
				arg_buf2.lightProfile.sbiVCoef.pData = (unsigned int *)(uintptr_t)arg_buf2.lightProfile.sbiVCoef.compat_pData;
				arg_buf2.lightProfile.lres1TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf2.lightProfile.lres1TabCoef.compat_pData;
				arg_buf2.lightProfile.lres5TabCoef.pData = (unsigned int *)(uintptr_t)arg_buf2.lightProfile.lres5TabCoef.compat_pData;
				for (i=0; i<LX_BE_LED_UI_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					arg_buf2.dimmingCurve.upperCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf2.dimmingCurve.upperCurve[i].compat_pData;
					arg_buf2.dimmingCurve.lowerCurve[i].pData = (unsigned int *)(uintptr_t)arg_buf2.dimmingCurve.lowerCurve[i].compat_pData;
					arg_buf2.uiAdj_lut[i].pData = (unsigned int *)(uintptr_t)arg_buf2.uiAdj_lut[i].compat_pData;
					arg_buf2.pixelCompensation[i].pData = (unsigned int *)(uintptr_t)arg_buf2.pixelCompensation[i].compat_pData;
				}
				arg_buf2.smartBvGain.pData = (unsigned int *)(uintptr_t)arg_buf2.smartBvGain.compat_pData;
				if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(v4l2_hwrap_led_lut)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_gamma_lut arg_buf2;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_gamma_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.table_red = (unsigned int *)(uintptr_t)arg_buf2.compat_table_red;
			arg_buf2.table_green = (unsigned int *)(uintptr_t)arg_buf2.compat_table_green;
			arg_buf2.table_blue = (unsigned int *)(uintptr_t)arg_buf2.compat_table_blue;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_gamma_lut)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_3DLUT:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vpq_gamut_lut arg_buf2;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_gamut_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.p_section_data = (short *)(uintptr_t)arg_buf2.compat_data;
			arg_buf2.add_info.p_info_data = (unsigned int *)(uintptr_t)arg_buf2.add_info.compat_data;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vpq_gamut_lut)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vpq_od_extension arg_buf2;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_od_extension)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.p_ext_data = (unsigned char *)(uintptr_t)arg_buf2.compat_data;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vpq_od_extension)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			v4l2_hwrap_gamut_post_v2 arg_buf2;
			v4l2_hwrap_gamut_post_v3 arg_buf3;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			
			if(arg_buf.version == 0x80)
			{
				if(copy_from_user(&arg_buf3,(void __user *)arg_buf.p_data,sizeof(v4l2_hwrap_gamut_post_v3)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				arg_buf3.pst_chip_data = (unsigned char *)(uintptr_t)arg_buf3.compat_data;
				if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf3,sizeof(v4l2_hwrap_gamut_post_v3)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if(arg_buf.version >=3)
			{
				if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(v4l2_hwrap_gamut_post_v2)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				arg_buf2.pst_chip_data = (unsigned char *)(uintptr_t)arg_buf2.compat_data;
				if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(v4l2_hwrap_gamut_post_v2)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
//#ifdef ENABLE_UCR
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vbe_ucr_lut arg_buf2;

			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vbe_ucr_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.posData = (unsigned short *)(uintptr_t)arg_buf2.compat_data;
			arg_buf2.rgbTbl = (unsigned short *)(uintptr_t)arg_buf2.compat_data_tlb;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vbe_ucr_lut)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
//#endif
//#ifdef ENABLE_EOTF_OETF_LUT
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vpq_degamma_regamma arg_buf2;

			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_degamma_regamma)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.u16pT_degamma = (unsigned short *)(uintptr_t)arg_buf2.compat_degamma;
			arg_buf2.u16pT_regamma = (unsigned short *)(uintptr_t)arg_buf2.compat_regamma;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vpq_degamma_regamma)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
//#endif
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vpq_frame_delay_mode arg_buf2;

			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_frame_delay_mode)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			arg_buf2.frame_delay_mode = (unsigned int)(uintptr_t)arg_buf2.frame_delay_mode;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vpq_frame_delay_mode)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;


		default:
			break;
	}
	#endif
	#endif
	return ret;
}

int v4l2_vpq_vidioc_s_ctrl_be(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_BE("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_LED_DB_IDX:
		{
			LX_BE_SET_DEFAULT_PARAM(LX_BE_LED_MODE_T, stParam);
			
			stParam.u32PictureMode = (UINT32)ctrl->value;
			gBeStatus.ledDbIdx = (UINT32)ctrl->value;
			ret = BE_LED_HAL_Set_Mode(&stParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_Mode error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_EN:
		{
			LX_BE_SET_DEFAULT_PARAM(LX_BE_LED_CONTROL_T, stParam);
			
			stParam.u32DimminOn = ctrl->value ? 1 : 0; /* 0: off, 1:on */
			gBeStatus.ledEn = ctrl->value ? 1 : 0;
			ret = BE_LED_HAL_Control(&stParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Control error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_FIN:
		{
			/* Do Nothing */
		}break;
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
		{
			BE_PWM_DUTY_RATIO_T stParam;
			
			stParam.port = 1;
			stParam.percent = ctrl->value;
			gBeStatus.pwmRatio = (UINT32)ctrl->value;
			ret = BE_PWM_HAL_SetPwmDutyRatio(&stParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PWM_HAL_SetPwmDutyRatio error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_MEMC_INIT:
		{
			PE_PRINT_VPQ_BE("MEMC init\n");
			//vpq_hwrap_memc_initialize();
		}break;
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:		
		{			
			unsigned int param;
			param = (unsigned int)ctrl->value;
			ret = vpq_hwrap_memc_lowdelaymode(&param);

			_gMemcLowDelay = param;
			PE_PRINT_VPQ_BE("_gMemcLowDelay (%d)\n",param);

			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_memc_lowdelaymode error(%d)\n",ret);
				break;
			}		
		}break;
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		{			
			unsigned int param;
			param = (unsigned int)ctrl->value;
			ret = vpq_hwrap_memc_motionpro(&param);

			_gMemcMotionPro = param;
			PE_PRINT_VPQ_BE("_gMemcMotionPro (%d)\n",param);

			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_memc_motionpro error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT:
		{
			int param;
			param = (int)ctrl->value;
			_gOaplWeghtCtrl = param;
			ret = BE_TOP_HAL_SetOaplMaxWeight(param);
			if (ret)
			{
				PE_PRINT_ERROR("BE_TOP_HAL_SetOaplMaxWeight error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_ABI:
		{
			PE_PRINT_DEBUG("Not Support V4L2_CID_EXT_LED_ABI\n");
		}break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

int v4l2_vpq_vidioc_g_ctrl_be(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_BE("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:
		{
			ctrl->value = _gMemcLowDelay;
			PE_PRINT_VPQ_BE("MEMC LowDelay: %d\n", ctrl->value);
		} break;
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		{
			ctrl->value = _gMemcMotionPro;
			PE_PRINT_VPQ_BE("MEMC MotionPro: %d\n", ctrl->value);
		} break;
		case V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT:
		{
			ctrl->value = _gOaplWeghtCtrl;
			PE_PRINT_VPQ_BE("_gOaplWeghtCtrl: %d\n", ctrl->value);
		} break;
		case V4L2_CID_EXT_LED_ABI:
		{
			PE_PRINT_DEBUG("Not Support V4L2_CID_EXT_LED_ABI\n");
		}break;
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
		{
			ctrl->value = gBeStatus.pwmRatio;
			PE_PRINT_VPQ_BE("PWM Ratio: %d\n", ctrl->value);
		}break;
		default:
			ret = -EINVAL;
	}

	return 0;
}

int vpq_set_ext_ctrl_be(struct v4l2_ext_control *ctrl)
{
	struct v4l2_ext_vpq_cmn_data param;
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
	{
		PE_PRINT_ERROR("copy_from_user error\n");
	}

	if (!param.p_data || (param.length == 0))
	{
		PE_PRINT_ERROR("p_data is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_LED_INIT:
		{
			struct v4l2_ext_led_panel_info data;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_led_panel_info)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, pi in:%d,blt:%d,bt:%d,m:%d,ldt:%d\n",\
				param.version,param.length,param.wid,\
				data.panel_inch,data.backlight_type,data.bar_type,data.module_maker,data.local_dim_ic_type);

			gBeStatus.ledPanelInch = _VPQ_BE_LEDPanelInchEnumToInch(data.panel_inch);

		}break;
		case V4L2_CID_EXT_LED_DEMOMODE:
		{
			struct v4l2_ext_led_ldim_demo_info data;
			LX_BE_SET_DEFAULT_PARAM(LX_BE_DEBUG_DISPLAY_T, lxParam);

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_led_ldim_demo_info)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			memcpy(&gBeStatus.demoInfo, &data, sizeof(struct v4l2_ext_led_ldim_demo_info));

			if (data.bOnOff) {
				switch (data.eType)
				{
					case v4l2_ext_led_ldim_demo_type_linedemo:
						lxParam.u8LEDDebugDisplay	 =	4;	//0:Off/1:BV/2:SBI/3:PBI/4:PBI&Rect_hv/5:Gray_Rect/6:Gradation /7,8:external chip pattern
						break;
					case v4l2_ext_led_ldim_demo_type_leftright:
						lxParam.u8LEDDebugDisplay	 =	7;
						break;
					case v4l2_ext_led_ldim_demo_type_topbottom:
						lxParam.u8LEDDebugDisplay	 =	8;
						break;
					default:
						lxParam.u8LEDDebugDisplay	 =	0;
					break;
				}
			}
			else {
				lxParam.u8LEDDebugDisplay	 =	0;
			}

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, di t:%d,on:%d\n",\
				param.version,param.length,param.wid,\
				data.eType,data.bOnOff);
			
			ret = BE_TOP_HAL_SetDebugDisplay(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_TOP_HAL_SetDebugDisplay error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_DB_DATA:
		{
			int i;
			if (param.version == 0x40)
			{
				v4l2_hwrap_led_lut_v2 data2;
				LX_BE_LED_LUT_V2_T lxParam2;

				if (copy_from_user(&data2,(void __user *)param.p_data,sizeof(v4l2_hwrap_led_lut_v2)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}

				lxParam2.u32LutVersion = data2.lutVersion;
				lxParam2.pq_common_lut.u32Size = data2.pq_common.size;
				lxParam2.pq_common_lut.pu32Ptr = (UINT32 *)data2.pq_common.pData;
				lxParam2.module_lut.u32Size = data2.moduleAdj.size;
				lxParam2.module_lut.pu32Ptr = (UINT32 *)data2.moduleAdj.pData;
				lxParam2.unsharpMask_lut.u32Size = data2.unsharpMask.size;
				lxParam2.unsharpMask_lut.pu32Ptr = (UINT32 *)data2.unsharpMask.pData;
				lxParam2.lightProfile_lut.sbiHCoef.u32Size = data2.lightProfile.sbiHCoef.size;
				lxParam2.lightProfile_lut.sbiHCoef.pu32Ptr = (UINT32 *)data2.lightProfile.sbiHCoef.pData;
				lxParam2.lightProfile_lut.sbiVCoef.u32Size = data2.lightProfile.sbiVCoef.size;
				lxParam2.lightProfile_lut.sbiVCoef.pu32Ptr = (UINT32 *)data2.lightProfile.sbiVCoef.pData;
				lxParam2.lightProfile_lut.lres1TabCoef.u32Size = data2.lightProfile.lres1TabCoef.size;
				lxParam2.lightProfile_lut.lres1TabCoef.pu32Ptr = (UINT32 *)data2.lightProfile.lres1TabCoef.pData;
				lxParam2.lightProfile_lut.lres5TabCoef.u32Size = data2.lightProfile.lres5TabCoef.size;
				lxParam2.lightProfile_lut.lres5TabCoef.pu32Ptr = (UINT32 *)data2.lightProfile.lres5TabCoef.pData;
				for (i=0; i<LX_BE_LED_UI_V2_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_v2_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					lxParam2.dimmingCurve_lut.upperCurve[i].u32Size = data2.dimmingCurve.upperCurve[i].size;
					lxParam2.dimmingCurve_lut.upperCurve[i].pu32Ptr = (UINT32 *)data2.dimmingCurve.upperCurve[i].pData;
					lxParam2.dimmingCurve_lut.lowerCurve[i].u32Size = data2.dimmingCurve.lowerCurve[i].size;
					lxParam2.dimmingCurve_lut.lowerCurve[i].pu32Ptr = (UINT32 *)data2.dimmingCurve.lowerCurve[i].pData;
					lxParam2.pqUi_lut[i].u32Size = data2.uiAdj_lut[i].size;
					lxParam2.pqUi_lut[i].pu32Ptr = (UINT32 *)data2.uiAdj_lut[i].pData;
					lxParam2.pixelCompensation_lut[i].u32Size = data2.pixelCompensation[i].size;
					lxParam2.pixelCompensation_lut[i].pu32Ptr = (UINT32 *)data2.pixelCompensation[i].pData;
				}
				lxParam2.sldBvGain.u32Size = data2.smartBvGain.size;
				lxParam2.sldBvGain.pu32Ptr = (UINT32 *)data2.smartBvGain.pData;
				lxParam2.u32PanelInch = gBeStatus.ledPanelInch;

				PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ld v:%d\n",param.version,param.length,param.wid,data2.lutVersion);

				ret = BE_LED_HAL_Set_Lut((LX_BE_LED_LUT_T *)&lxParam2);
			}
			else if (param.version == 0x60)
			{
				v4l2_hwrap_led_lut_v3 data3;
				LX_BE_LED_LUT_V3_T lxParam3;

				if (copy_from_user(&data3,(void __user *)param.p_data,sizeof(v4l2_hwrap_led_lut_v3)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}

				lxParam3.u32LutVersion = data3.lutVersion;
				lxParam3.pq_common_lut.u32Size = data3.pq_common.size;
				lxParam3.pq_common_lut.pu32Ptr = (UINT32 *)data3.pq_common.pData;
				lxParam3.module_lut.u32Size = data3.moduleAdj.size;
				lxParam3.module_lut.pu32Ptr = (UINT32 *)data3.moduleAdj.pData;
				lxParam3.unsharpMask_lut.u32Size = data3.unsharpMask.size;
				lxParam3.unsharpMask_lut.pu32Ptr = (UINT32 *)data3.unsharpMask.pData;
				lxParam3.lightProfile_lut.sbiHCoef.u32Size = data3.lightProfile.sbiHCoef.size;
				lxParam3.lightProfile_lut.sbiHCoef.pu32Ptr = (UINT32 *)data3.lightProfile.sbiHCoef.pData;
				lxParam3.lightProfile_lut.sbiVCoef.u32Size = data3.lightProfile.sbiVCoef.size;
				lxParam3.lightProfile_lut.sbiVCoef.pu32Ptr = (UINT32 *)data3.lightProfile.sbiVCoef.pData;
				lxParam3.lightProfile_lut.lres1TabCoef.u32Size = data3.lightProfile.lres1TabCoef.size;
				lxParam3.lightProfile_lut.lres1TabCoef.pu32Ptr = (UINT32 *)data3.lightProfile.lres1TabCoef.pData;
				lxParam3.lightProfile_lut.lres5TabCoef.u32Size = data3.lightProfile.lres5TabCoef.size;
				lxParam3.lightProfile_lut.lres5TabCoef.pu32Ptr = (UINT32 *)data3.lightProfile.lres5TabCoef.pData;
				for (i=0; i<LX_BE_LED_UI_V3_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_v3_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					lxParam3.dimmingCurve_lut.upperCurve[i].u32Size = data3.dimmingCurve.upperCurve[i].size;
					lxParam3.dimmingCurve_lut.upperCurve[i].pu32Ptr = (UINT32 *)data3.dimmingCurve.upperCurve[i].pData;
					lxParam3.dimmingCurve_lut.lowerCurve[i].u32Size = data3.dimmingCurve.lowerCurve[i].size;
					lxParam3.dimmingCurve_lut.lowerCurve[i].pu32Ptr = (UINT32 *)data3.dimmingCurve.lowerCurve[i].pData;
					lxParam3.pqUi_lut[i].u32Size = data3.uiAdj_lut[i].size;
					lxParam3.pqUi_lut[i].pu32Ptr = (UINT32 *)data3.uiAdj_lut[i].pData;
					lxParam3.pixelCompensation_lut[i].u32Size = data3.pixelCompensation[i].size;
					lxParam3.pixelCompensation_lut[i].pu32Ptr = (UINT32 *)data3.pixelCompensation[i].pData;
				}
				lxParam3.sldBvGain.u32Size = data3.smartBvGain.size;
				lxParam3.sldBvGain.pu32Ptr = (UINT32 *)data3.smartBvGain.pData;
				lxParam3.u32PanelInch = gBeStatus.ledPanelInch;

				PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ld v:%d\n",param.version,param.length,param.wid,data3.lutVersion);

				ret = BE_LED_HAL_Set_Lut((LX_BE_LED_LUT_T *)&lxParam3);
			}
			else if (param.version == 0x80)
			{
				LX_BE_LED_DB_LUT_v80_T data_80;
				if (copy_from_user(&data_80,(void __user *)param.p_data,sizeof(LX_BE_LED_DB_LUT_v80_T)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}
				PE_PRINT_NOTI("v80,l:%d,wid:%d, ld v:%d\n",param.length,param.wid,data_80.u32LutVersion);
				ret = BE_LED_HAL_Set_Lut1((void *)&data_80);
				if (ret) {
					PE_PRINT_ERROR("BE_LED_HAL_Set_Lut1 error(%d)\n",ret);
					break;
				}
			}
			else
			{
				v4l2_hwrap_led_lut data;
				LX_BE_LED_LUT_T lxParam;

				if (copy_from_user(&data,(void __user *)param.p_data,sizeof(v4l2_hwrap_led_lut)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}

				lxParam.u32LutVersion = data.lutVersion;
				lxParam.pq_common_lut.u32Size = data.pq_common.size;
				lxParam.pq_common_lut.pu32Ptr = (UINT32 *)data.pq_common.pData;
				lxParam.module_lut.u32Size = data.moduleAdj.size;
				lxParam.module_lut.pu32Ptr = (UINT32 *)data.moduleAdj.pData;
				lxParam.unsharpMask_lut.u32Size = data.unsharpMask.size;
				lxParam.unsharpMask_lut.pu32Ptr = (UINT32 *)data.unsharpMask.pData;
				lxParam.lightProfile_lut.sbiHCoef.u32Size = data.lightProfile.sbiHCoef.size;
				lxParam.lightProfile_lut.sbiHCoef.pu32Ptr = (UINT32 *)data.lightProfile.sbiHCoef.pData;
				lxParam.lightProfile_lut.sbiVCoef.u32Size = data.lightProfile.sbiVCoef.size;
				lxParam.lightProfile_lut.sbiVCoef.pu32Ptr = (UINT32 *)data.lightProfile.sbiVCoef.pData;
				lxParam.lightProfile_lut.lres1TabCoef.u32Size = data.lightProfile.lres1TabCoef.size;
				lxParam.lightProfile_lut.lres1TabCoef.pu32Ptr = (UINT32 *)data.lightProfile.lres1TabCoef.pData;
				lxParam.lightProfile_lut.lres5TabCoef.u32Size = data.lightProfile.lres5TabCoef.size;
				lxParam.lightProfile_lut.lres5TabCoef.pu32Ptr = (UINT32 *)data.lightProfile.lres5TabCoef.pData;
				for (i=0; i<LX_BE_LED_UI_MAX; i++)
				{
					if (i >= v4l2_hwrap_led_ui_adj_max)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					lxParam.dimmingCurve_lut.upperCurve[i].u32Size = data.dimmingCurve.upperCurve[i].size;
					lxParam.dimmingCurve_lut.upperCurve[i].pu32Ptr = (UINT32 *)data.dimmingCurve.upperCurve[i].pData;
					lxParam.dimmingCurve_lut.lowerCurve[i].u32Size = data.dimmingCurve.lowerCurve[i].size;
					lxParam.dimmingCurve_lut.lowerCurve[i].pu32Ptr = (UINT32 *)data.dimmingCurve.lowerCurve[i].pData;
					lxParam.pqUi_lut[i].u32Size = data.uiAdj_lut[i].size;
					lxParam.pqUi_lut[i].pu32Ptr = (UINT32 *)data.uiAdj_lut[i].pData;
					lxParam.pixelCompensation_lut[i].u32Size = data.pixelCompensation[i].size;
					lxParam.pixelCompensation_lut[i].pu32Ptr = (UINT32 *)data.pixelCompensation[i].pData;
				}
				lxParam.sldBvGain.u32Size = data.smartBvGain.size;
				lxParam.sldBvGain.pu32Ptr = (UINT32 *)data.smartBvGain.pData;
				lxParam.u32PanelInch = gBeStatus.ledPanelInch;

				PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ld v:%d\n",param.version,param.length,param.wid,data.lutVersion);

				ret = BE_LED_HAL_Set_Lut((LX_BE_LED_LUT_T *)&lxParam);
			}
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_Lut error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		{
			struct v4l2_ext_led_spi_ctrl_info data;
			LX_BE_LED_SPI_CTRL_T lxParam;
			UINT32 regVal;

			if (param.version == 0x10)
			{
				UINT16 tmpData;

				if (copy_from_user(&tmpData,(void __user *)param.p_data,sizeof(UINT16)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}

				lxParam.bCtrl = param.version;
				lxParam.u32BitMask = tmpData;
				gBeStatus.ctrlSpi.ctrlValue = tmpData;
			}
			else
			{
				if (copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_led_spi_ctrl_info)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					return -EINVAL;
				}

				regVal = gBeStatus.ctrlSpi.ctrlValue;
				if (data.ctrlValue)
				{
					regVal = regVal | (data.bitMask);
				}
				else
				{
					regVal = regVal & (~(data.bitMask));
				}
				gBeStatus.ctrlSpi.ctrlValue = regVal;

				lxParam.bCtrl = data.ctrlValue;
				lxParam.u32BitMask = data.bitMask;
			}

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, c m:%d,v:%d, lx m:%d,v:%d\n",\
				param.version,param.length,param.wid,\
				data.bitMask,data.ctrlValue,\
				lxParam.u32BitMask,lxParam.bCtrl);
			
			ret = BE_LED_HAL_Set_SpiCtrl(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_SpiCtrl error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_LED_BPL_DATA:
		{
			struct v4l2_ext_led_bpl_info data;
			LX_BE_LED_BPL_DATA_T lxParam;
			
			if (copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_led_bpl_info)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			memcpy(&gBeStatus.bplInfo, &data, sizeof(struct v4l2_ext_led_bpl_info));

			lxParam.bIsGet = FALSE;
			lxParam.bAiBrightnessAdjEn = data.ai_brightness;
			lxParam.u16SensorLevel = data.sensor_level;
			lxParam.blooming_mode = data.blooming_mode;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, c e:%d,s:%d, %d\n",\
				param.version,param.length,param.wid,\
				data.ai_brightness,data.sensor_level, data.blooming_mode);
			
			ret = BE_LED_HAL_Set_BplData(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_BplData error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		{
			struct v4l2_ext_gamma_lut data;
			LX_OVI_TCON_GAMMA_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_gamma_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.rGammaLut.pData= data.table_red;
			lxParam.gGammaLut.pData = data.table_green;
			lxParam.bGammaLut.pData = data.table_blue;
			lxParam.rGammaLut.sizeNum = data.table_num;
			lxParam.gGammaLut.sizeNum = data.table_num;
			lxParam.bGammaLut.sizeNum = data.table_num;
			lxParam.bIsGet = FALSE;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, gl s:%d,rp:0x%x,gp:0x%x,bp:0x%x\n",\
				param.version,param.length,param.wid,\
				data.table_num,(unsigned int)(uintptr_t)data.table_red,(unsigned int)(uintptr_t)data.table_green,(unsigned int)(uintptr_t)data.table_blue);

			ret = OVI_HAL_SetGamma(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetGamma error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		{
			struct v4l2_ext_vpq_color_temp data;
			LX_OVI_TCON_COLOR_TEMP_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_color_temp)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.r_gain = data.rgb_gain[0];
			lxParam.g_gain = data.rgb_gain[1];
			lxParam.b_gain = data.rgb_gain[2];
			lxParam.r_offset = data.rgb_offset[0];
			lxParam.g_offset = data.rgb_offset[1];
			lxParam.b_offset = data.rgb_offset[2];
			lxParam.bIsGet = FALSE;

			if ((lx_chip_rev() >= LX_CHIP_REV(O20,A0))
				&& (param.version == 10)) // ID-Signage model
			{
				lxParam.r_gain |= (1 << 31);
				lxParam.g_gain |= (1 << 31);
				lxParam.b_gain |= (1 << 31);
			}

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ct g r:%d,g:%d,b:%d o r:%d,g:%d,b:%d\n",\
				param.version,param.length,param.wid,\
				data.rgb_gain[0],data.rgb_gain[1],data.rgb_gain[2],\
				data.rgb_offset[0],data.rgb_offset[1],data.rgb_offset[2]);

			ret = OVI_HAL_SetColorTemp(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetColorTemp error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_3DLUT:
		{
			struct v4l2_ext_vpq_gamut_lut data;
			LX_BE_WCG_LUT_T lxLutParam;

			if (copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_gamut_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxLutParam.u32LutVersion = data.lut_version;
			lxLutParam.u32TotalSectionNum = data.total_section_num;
			lxLutParam.pu16SectionData = data.p_section_data;
			lxLutParam.regData.u32Size = data.add_info.info_size;
			lxLutParam.regData.pu32Data = data.add_info.p_info_data;

			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, gl v:%d,sn:%d,p:%p, ai s:%d,p:%p\n",\
				param.version,param.length,param.wid,\
				data.lut_version,data.total_section_num,data.p_section_data,\
				data.add_info.info_size,data.add_info.p_info_data);

			if (lx_chip() >= LX_CHIP_O20)
			{
				ret = BE_WCG_HAL_Set_Lut(&lxLutParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_WCG_HAL_Set_Lut error(%d)\n",ret);
					break;
				}	
			}
			else
			{
				LX_BE_WCG_MODE_T lxModeParam;
				LX_BE_WCG_CONTROL_T lxCtrlParam;
			
				ret = BE_WCG_HAL_Set_Lut(&lxLutParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_WCG_HAL_Set_Lut error(%d)\n",ret);
					break;
				}

				lxModeParam.u32PictureMode = 0;
				ret = BE_WCG_HAL_Set_Mode(&lxModeParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_WCG_HAL_Set_Mode error(%d)\n",ret);
					break;
				}

				lxCtrlParam.u32Enable = TRUE;
				ret = BE_WCG_HAL_Control(&lxCtrlParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_WCG_HAL_Control error(%d)\n",ret);
					break;
				}
			}

			/* 20180511, Miracast PIP sub saturation, SCDCR-1562 */
			/* moved here from HAL_VPQ_SetGamutLUT() */
			do {
				LX_PE_CMN_VCP_LEVEL_CTRL_T stVcpLevelParam;
				unsigned int infoSize = 0, invalid = 0, inputType = 0, colorimetry = 0;
				unsigned int infoData[4];

				infoSize = data.add_info.info_size;
				invalid = 0;
				/* check invalid */
				if (infoSize<(sizeof(unsigned int)*4))	invalid |= 0x01;//size check
				if (data.add_info.p_info_data==NULL)	invalid |= 0x02;//null check
				if (invalid==0)
				{
					ret = copy_from_user((void *)infoData, (void __user *)data.add_info.p_info_data, (sizeof(unsigned int)*4));
					if (ret) 							invalid |= 0x04;//ret check
					if (infoData[0]!=0x1)				invalid |= 0x08;//index check
					if (infoData[2]!=0x2)				invalid |= 0x10;//index check
				}
				/* set vcp level(sub) */
				stVcpLevelParam.win_id = LX_PE_WIN_1;
				stVcpLevelParam.center_position = 0;
				stVcpLevelParam.contrast = 512;
				stVcpLevelParam.brightness = 512;
				if (invalid==0)
				{
					inputType = infoData[1];//(0:SDR, 1:Dolby, 2:HDR10, 3:HLG, 4:Technocolor, 5:HDR Effect)
					colorimetry = infoData[3];//(0:BT601, 1:BT709, 2:BT2020)
					if ((inputType==2||inputType==3||inputType==4)&&colorimetry==2)//HDR2020
					{
						stVcpLevelParam.enable = 1;
						stVcpLevelParam.saturation = 90;//80(0x50)->90(0x5A),20180424demo(SCDCR-1328)
					}
					else//others
					{
						stVcpLevelParam.enable = 0;
						stVcpLevelParam.saturation = 128;//0x80,default
					}
				}
				else//invalid
				{
					stVcpLevelParam.enable = 0;
					stVcpLevelParam.saturation = 128;//0x80,default
				}
				PE_PRINT_NOTI("s:%d, iv:0x%02x, id:%d,%d,%d,%d, [%d] en:%d, cp:%d, c,b,s:%d,%d,%d\n",\
					infoSize,invalid,infoData[0],infoData[1],infoData[2],infoData[3],\
					stVcpLevelParam.win_id,stVcpLevelParam.enable,stVcpLevelParam.center_position,\
					stVcpLevelParam.contrast,stVcpLevelParam.brightness,stVcpLevelParam.saturation);
				#if 0	//debug
				do {
					int ret1 = 0;
					UINT32 localInfoData[4] = {-1,-1,-1,-1};
					ret1 = copy_from_user((void *)localInfoData, (void __user *)lxLutParam.regData.pu32Data, (sizeof(UINT32)*4));
					PE_PRINT_NOTI("ai:%d,%p, rD:%d,%p -> r1:%d, d:%d,%d,%d,%d\n",\
						data.add_info.info_size,data.add_info.p_info_data,\
						lxLutParam.regData.u32Size,lxLutParam.regData.pu32Data,\
						ret1,localInfoData[0],localInfoData[1],localInfoData[2],localInfoData[3]);
				} while(0);
				#endif
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
				{
					ret = PE_CMN_SetVcpSaturationCtrl(&stVcpLevelParam);
					if (ret)
					{
						PE_PRINT_ERROR("PE_CMN_SetVcpSaturationCtrl error(%d)\n",ret);
						break;
					}
				}
				else
				{
					ret = PE_CMN_SetVcpLevelCtrl(&stVcpLevelParam);
					if (ret)
					{
						PE_PRINT_ERROR("PE_CMN_SetVcpLevelCtrl error(%d)\n",ret);
						break;
					}
				}
			} while(0);
		}break;
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		{
			bool gamut_enable[4];
			LX_OVI_MULTIWIN_GAMUT_T lxParam;
			__attribute__((unused)) LX_PE_WIN_ID win_id;
			if(copy_from_user(gamut_enable,(void __user *)param.p_data,sizeof(bool)*4))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.win_id = param.wid;
			lxParam.pcc_eotf_en = gamut_enable[0];
			lxParam.pcc_oetf_en = gamut_enable[1];
			lxParam.reg_pcc_en =  gamut_enable[2];
			lxParam.reg_l3d_en =  gamut_enable[3];

			PE_PRINT_VPQ_BE("ver:%d,len:%d,wid:%d,pcc_eotf_en:%d,pcc_oetf_en:%d,reg_pcc_en:%d, reg_l3d_en:%d\n",\
				param.version,param.length,param.wid,lxParam.pcc_eotf_en,lxParam.pcc_oetf_en,lxParam.reg_pcc_en,lxParam.reg_l3d_en);

			ret = OVI_HAL_SetMultiWindow_Gamut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetMultiWindow_Gamut error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		{
			LX_OVI_TCON_OD_DWLD_T lxParam;

			lxParam.eMode = LX_OVI_TCON_FRAMEOD;
			lxParam.odLut.pData = param.p_data;
			lxParam.odLut.sizeNum = param.length;
			lxParam.bIsGet = FALSE;

			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, p:0x%x\n",\
				param.version,param.length,param.wid,\
				(unsigned int)(uintptr_t)param.p_data);
			
			ret = OVI_HAL_SetOdLut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetOdLut error(%d)\n",ret);
				break;
			}

			ret = OVI_HAL_SetFrameOdcEnable(TRUE);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetFrameOdcEnable error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		{
			struct v4l2_ext_vpq_od_extension data;
			LX_OVI_TCON_OD_DWLD_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_od_extension)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.eMode = (data.ext_type == 0) ? LX_OVI_TCON_LINEOD_POD : LX_OVI_TCON_LINEOD_PCID;
			lxParam.odLut.pData = data.p_ext_data;
			lxParam.odLut.sizeNum = data.ext_length;

			lxParam.bIsGet = FALSE;

			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, ode t:%d,l:%d,p:0x%x\n",\
				param.version,param.length,param.wid,\
				data.ext_type,data.ext_length,(unsigned int)(uintptr_t)data.p_ext_data);

			if (lxParam.eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				ret = OVI_HAL_SetLodLut(&lxParam);
			}
			else
			{
				ret = OVI_HAL_SetPodLut(&lxParam);
			}
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetLod/PodLut error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		{
			int i;
			UINT16 	pccMatrix[LX_BE_PQ_NUM_OF_PCC_COEF];
			ret = vpq_hwrap_gamut_matrix_post(&param, pccMatrix);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gamut_matrix_post error(%d)\n",ret);
				break;
			}

			for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
			{
				gBeStatus.pccMatrix[i] =pccMatrix[i];
			}
		}break;
		case V4L2_CID_EXT_VPQ_LUMINANCE_BOOST:
		{
			LX_BE_PQ_LUT_T lxParam;

			lxParam.u32LutVersion = param.version;
			lxParam.pData = (UINT32 *)param.p_data;
			if (param.version >= 0x40)
			{
				lxParam.sizeNum = param.length;
			}
			else
			{
				lxParam.sizeNum = (param.length)/sizeof(lxParam.pData[0]);
			}

			PE_PRINT_VPQ_BE("V4L2_CID_EXT_VPQ_LUMINANCE_BOOST v:%d,l:%d,wid:%d, rl:%d, p:0x%x \n",\
				param.version,param.length,param.wid,\
				lxParam.sizeNum, (unsigned int)(uintptr_t)param.p_data);
			
			ret = BE_PQ_HAL_Set_LuminenceBoost(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_LuminenceBoost error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT:
		{
			LX_BE_PQ_LUT_T lxParam;

			lxParam.pData = (UINT32 *)param.p_data;
			lxParam.sizeNum = param.length;

			PE_PRINT_VPQ_BE("V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT v:%d,l:%d,wid:%d, p:0x%x\n",\
				param.version,param.length,param.wid,\
				(unsigned int)(uintptr_t)param.p_data);

			ret = BE_PQ_HAL_Set_Oled_Apl_Gain(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Oled_Apl_Gain error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_memc_motion_comp_info data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if (!param.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				return -EINVAL;
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_memc_motion_comp_info)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			param.p_data = (unsigned char *)&data;

			PE_PRINT_VPQ_BE("set: %d %d %d\n", data.blur_level,data.judder_level,data.memc_type);
			ret = vpq_hwrap_memc_setmotioncomp(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_memc_setmotioncomp error(%d)\n",ret);
				break;
			}
			v4l2_vsc_update_pulldown(data.memc_type);
			gMemcMode.u8Blur = data.blur_level;
			gMemcMode.u8Judder = data.judder_level;
			gMemcMode.u8MemcType = data.memc_type;
		}break;
//#ifdef ENABLE_UCR
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
		{
			struct v4l2_ext_vbe_ucr_lut data;
			LX_BE_LED_UCR_PARAM_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vbe_ucr_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.u32Enable = data.on_off;
			lxParam.u32posNum = data.poSize;
			lxParam.u32rgbTblNum = data.tblSize;
			lxParam.pu16posData = data.posData;
			lxParam.pu16rgbTblData = data.rgbTbl;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, onoff:%d, pos s:%d, tlb s:%d\n",\
				param.version,param.length,param.wid,\
				data.on_off, data.poSize, data.tblSize);

			ret = BE_LED_HAL_Set_Ucr(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_Ucr error(%d)\n",ret);
				break;
			}
		}break;
//#endif
//#ifdef ENABLE_EOTF_OETF_LUT
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
		{
			struct v4l2_ext_vpq_degamma_regamma data;
			LX_BE_PQ_EOTF_OETF_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_degamma_regamma)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.pu16Eotf = data.u16pT_degamma;
			lxParam.u32EotfNum = data.degamma_size_num;
			lxParam.pu16Oetf = data.u16pT_regamma;
			lxParam.u32OetfNum = data.regamma_size_num;

			gGammaMode.u16pT_degamma = data.u16pT_degamma;
			gGammaMode.degamma_size_num = data.degamma_size_num;
			gGammaMode.u16pT_regamma = data.u16pT_regamma;
			gGammaMode.regamma_size_num = data.regamma_size_num;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, eotf s:%d, oetf s:%d\n",\
				param.version,param.length,param.wid,\
				lxParam.u32EotfNum, lxParam.u32OetfNum);

			ret = BE_PQ_HAL_Set_Eotf_Oetf_Lut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Eotf_Oetf_Lut error(%d)\n",ret);
				break;
			}
		}break;
//#endif
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		{
			struct v4l2_ext_vpq_frame_delay_mode data;
			LX_BE_FRAME_DELAY_MODE_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_frame_delay_mode)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}
			lxParam.u32DelayMode = data.frame_delay_mode;
			ret = BE_PQ_HAL_Set_Frame_Delay_Mode(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Frame_Delay_Mode error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_MCC_DATA :
		{
			LX_BE_USER_MCC_DATA_T data;
			LX_BE_MCC_DATA_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(LX_BE_USER_MCC_DATA_T)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}
			memcpy(lxParam.phdr_mcc_en, data.phdr_mcc_en, PQDB_PHDR_MCC_EN_LENGTH * sizeof(unsigned short));
			memcpy(lxParam.phdr_mcc_wb_gain, data.phdr_mcc_wb_gain, PQDB_PHDR_MCC_WB2P_GAIN_LENGTH * sizeof(unsigned short));
			memcpy(lxParam.phdr_mcc_wb_offset, data.phdr_mcc_wb_offset, PQDB_PHDR_MCC_WB2P_OFFSET_LENGTH * sizeof(unsigned short));

			ret = BE_PQ_HAL_Set_Mcc_Data(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Mcc_Data error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_MCC_LUT :
		{
			LX_BE_USER_MCC_LUT_T data;
			LX_BE_MCC_LUT_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(LX_BE_USER_MCC_LUT_T)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}
			memcpy(lxParam.phdr_mcc_luma_lut_x, data.phdr_mcc_luma_lut_x, PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH * sizeof(unsigned short));
			memcpy(lxParam.phdr_mcc_luma__lut_y, data.phdr_mcc_luma__lut_y, PQDB_PHDR_MCC_LUMA_GAIN_LUT_LENGTH * sizeof(unsigned short));
			memcpy(lxParam.phdr_mcc_satu_lut_x, data.phdr_mcc_satu_lut_x, PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH * sizeof(unsigned short));
			memcpy(lxParam.phdr_mcc_satu_lut_y, data.phdr_mcc_satu_lut_y, PQDB_PHDR_MCC_SATU_GAIN_LUT_LENGTH * sizeof(unsigned short));

			ret = BE_PQ_HAL_Set_Mcc_Lut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_PQ_HAL_Set_Mcc_Lut error(%d)\n",ret);
				break;
			}
		}break;

		default:
			return -EINVAL;
	}

	return ret;
}

int vpq_get_ext_ctrl_be(struct v4l2_ext_control *ctrl)
{
	struct v4l2_ext_vpq_cmn_data param;
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
	{
		PE_PRINT_ERROR("copy_from_user error\n");
		return -EINVAL;
	}

	if (!param.p_data || (param.length == 0))
	{
		PE_PRINT_ERROR("p_data is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_LED_APL_DATA:
		{
			v4l2_hwrap_led_apl_info vpq_data;
			LX_BE_LED_APL_T lxParam;

			ret = BE_LED_HAL_Get_Apl(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Get_Apl error(%d)\n",ret);
				break;
			}

			vpq_data.block_apl_min = lxParam.u16Min & 0x3FF;
			vpq_data.block_apl_max = lxParam.u16Max & 0x3FF;

			if(copy_to_user((void __user *)param.p_data,&vpq_data,sizeof(v4l2_hwrap_led_apl_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, p:0x%x, get m:%d,x:%d\n",\
				param.version,param.length,param.wid,(unsigned int)(uintptr_t)param.p_data,\
				vpq_data.block_apl_min,vpq_data.block_apl_max);
		}break;
		case V4L2_CID_EXT_LED_BPL_DATA:
		{
			struct v4l2_ext_led_bpl_info vpq_data;
			LX_BE_LED_BPL_DATA_T lxParam;

			lxParam.bIsGet = TRUE;			
			ret = BE_LED_HAL_Set_BplData(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("BE_LED_HAL_Set_BplData error(%d)\n",ret);
				break;
			}

			vpq_data.ai_brightness = (UINT16)lxParam.bAiBrightnessAdjEn;
			vpq_data.sensor_level = lxParam.u16SensorLevel;
			vpq_data.blooming_mode = lxParam.blooming_mode;

			if(copy_to_user((void __user *)param.p_data,&vpq_data,sizeof(struct v4l2_ext_led_bpl_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, p:0x%x, get e:%d,l:%d, %d\n",\
				param.version,param.length,param.wid,(unsigned int)(uintptr_t)param.p_data,\
				vpq_data.ai_brightness,vpq_data.sensor_level,vpq_data.blooming_mode);
		}break;
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		{
			struct v4l2_ext_gamma_lut data;
			LX_OVI_TCON_GAMMA_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_gamma_lut)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.rGammaLut.pData= data.table_red;
			lxParam.gGammaLut.pData = data.table_green;
			lxParam.bGammaLut.pData = data.table_blue;
			lxParam.bIsGet = TRUE;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, gl s:%d,rp:0x%x,gp:0x%x,bp:0x%x\n",\
				param.version,param.length,param.wid,\
				data.table_num,(unsigned int)(uintptr_t)data.table_red,(unsigned int)(uintptr_t)data.table_green,(unsigned int)(uintptr_t)data.table_blue);

			ret = OVI_HAL_SetGamma(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetGamma error(%d)\n",ret);
				break;
			}

			data.table_num = lxParam.rGammaLut.sizeNum;

			if(copy_to_user((void __user *)param.p_data, &data, sizeof(struct v4l2_ext_gamma_lut)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}

		}break;
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		{
			struct v4l2_ext_vpq_color_temp data;
			LX_OVI_TCON_COLOR_TEMP_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_color_temp)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			lxParam.r_gain = data.rgb_gain[0];
			lxParam.g_gain = data.rgb_gain[1];
			lxParam.b_gain = data.rgb_gain[2];
			lxParam.r_offset = data.rgb_offset[0];
			lxParam.g_offset = data.rgb_offset[1];
			lxParam.b_offset = data.rgb_offset[2];
			lxParam.bIsGet = TRUE;

			ret = OVI_HAL_SetColorTemp(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetColorTemp error(%d)\n",ret);
				break;
			}

			data.rgb_gain[0] = lxParam.r_gain;
			data.rgb_gain[1] = lxParam.g_gain;
			data.rgb_gain[2] = lxParam.b_gain;
			data.rgb_offset[0] = lxParam.r_offset;
			data.rgb_offset[1] = lxParam.g_offset;
			data.rgb_offset[2] = lxParam.b_offset;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ct g r:%d,g:%d,b:%d o r:%d,g:%d,b:%d\n",\
				param.version,param.length,param.wid,\
				data.rgb_gain[0],data.rgb_gain[1],data.rgb_gain[2],\
				data.rgb_offset[0],data.rgb_offset[1],data.rgb_offset[2]);

			if(copy_to_user(param.p_data,(void __user *)&data,sizeof(struct v4l2_ext_vpq_color_temp)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}

		}break;
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		{
			LX_OVI_TCON_OD_DWLD_T lxParam;

			lxParam.eMode = LX_OVI_TCON_FRAMEOD;
			lxParam.odLut.pData = param.p_data;
			lxParam.odLut.sizeNum = param.length;
			lxParam.bIsGet = TRUE;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, p:0x%x\n",\
				param.version,param.length,param.wid,\
				(unsigned int)(uintptr_t)param.p_data);

			ret = OVI_HAL_SetOdLut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetOdLut error(%d)\n",ret);
				break;
			}

			param.length = lxParam.odLut.sizeNum;

			if(copy_to_user(ctrl->string,(void __user *)&param,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}

		}break;
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		{
			struct v4l2_ext_vpq_od_extension data;
			LX_OVI_TCON_OD_DWLD_T lxParam;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_od_extension)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			lxParam.eMode = (data.ext_type == 0) ? LX_OVI_TCON_LINEOD_POD : LX_OVI_TCON_LINEOD_PCID;
			lxParam.odLut.pData = data.p_ext_data;
			lxParam.odLut.sizeNum = data.ext_length;

			lxParam.bIsGet = TRUE;

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, ode t:%d,l:%d,p:0x%x\n",\
				param.version,param.length,param.wid,\
				data.ext_type,data.ext_length,(unsigned int)(uintptr_t)data.p_ext_data);

			if (lxParam.eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				ret = OVI_HAL_SetLodLut(&lxParam);
			}
			else
			{
				ret = OVI_HAL_SetPodLut(&lxParam);
			}
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetLod/PodLut error(%d)\n",ret);
				break;
			}

			data.ext_length = lxParam.odLut.sizeNum;

			if(copy_to_user(param.p_data,(void __user *)&data,sizeof(struct v4l2_ext_vpq_od_extension)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		{
			v4l2_hwrap_gamut_post data;
			LX_BE_PQ_PCC_PARAMS_T pccParams;
			int i;

			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(v4l2_hwrap_gamut_post)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}

			if (lx_chip_rev() >= LX_CHIP_REV(O20,A0))
			{
				pccParams.bIsGet = TRUE;

				ret = BE_PQ_HAL_Set_PccParams(&pccParams);
				if (ret)
				{
					PE_PRINT_ERROR("BE_PQ_HAL_Set_PccParams error(%d)\n",ret);
					break;
				}

				for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
				{
					if (i >= 9)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					//data.matrix[i] = pccParams.matrix[i];
					data.matrix[i] = gBeStatus.pccMatrix[i];
				}

				data.bGamma = pccParams.bOetfGammaEn;
				data.bDeGamma = pccParams.bEotfGammaEn;

				data.mux_blend.mux_l3d_in = (UINT32)pccParams.u32MuxL3dIn;
				data.mux_blend.mux_blend_in = (UINT32)pccParams.u32MuxBlendIn;
				data.mux_blend.mux_4p_lut_in = (UINT32)pccParams.u32Mux4pLutIn;
				data.mux_blend.mux_oetf_out = (UINT32)pccParams.u32MuxOetfOut;
				for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
				{
					if (i >= V4L2_HWRAP_CSC_MUX_LUT_SIZE)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					data.mux_blend.b4p_lut_x[i] = (UINT32)pccParams.au32B4pLutX[i];
					data.mux_blend.b4p_lut_y[i] = (UINT32)pccParams.au32B4pLutY[i];
				}
			}
			else
			{
				LX_BE_PQ_PCC_T pccParam;
				LX_BE_PQ_PCC_GAMMA_T gammaParam;
				LX_BE_PQ_PCC_MUX_BLEND_T muxParam;
				
				pccParam.bIsGet = TRUE;
				gammaParam.bIsGet = TRUE;
				muxParam.bIsGet = TRUE;

				ret = BE_PQ_HAL_Set_Pcc(&pccParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_PQ_HAL_Set_Pcc error(%d)\n",ret);
					break;
				}
				ret = BE_PQ_HAL_Set_PccGamma(&gammaParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_PQ_HAL_Set_PccGamma error(%d)\n",ret);
					break;
				}
				ret = BE_PQ_HAL_Set_PccMuxBlend(&muxParam);
				if (ret)
				{
					PE_PRINT_ERROR("BE_PQ_HAL_Set_PccMuxBlend error(%d)\n",ret);
					break;
				}

				for (i=0; i<LX_BE_PQ_NUM_OF_PCC_COEF; i++)
				{
					if (i >= 9)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					//data.matrix[i] = pccParam.matrix[i];
					data.matrix[i] = gBeStatus.pccMatrix[i];
				}

				data.bGamma = gammaParam.bOetfGammaEn;
				data.bDeGamma = gammaParam.bEotfGammaEn;

				data.mux_blend.mux_l3d_in = (UINT32)muxParam.u32MuxL3dIn;
				data.mux_blend.mux_blend_in = (UINT32)muxParam.u32MuxBlendIn;
				data.mux_blend.mux_4p_lut_in = (UINT32)muxParam.u32Mux4pLutIn;
				data.mux_blend.mux_oetf_out = (UINT32)muxParam.u32MuxOetfOut;
				for (i=0; i<LX_BE_PQ_NUM_OF_PCC_4P_LUT_DATA; i++)
				{
					if (i >= V4L2_HWRAP_CSC_MUX_LUT_SIZE)
					{
						PE_PRINT_ERROR("Invalid array size!\n");
						return -EINVAL;
					}
					data.mux_blend.b4p_lut_x[i] = (UINT32)muxParam.au32B4pLutX[i];
					data.mux_blend.b4p_lut_y[i] = (UINT32)muxParam.au32B4pLutY[i];
				}
			}

			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, g:%d,d:%d\n",\
				param.version,param.length,param.wid,\
				data.bGamma,data.bDeGamma);
			PE_PRINT_VPQ_BE("m0:0x%x,m1:0x%x,m2:0x%x\n",\
				data.matrix[0],data.matrix[1],data.matrix[2]);
			PE_PRINT_VPQ_BE("m3:0x%x,m4:0x%x,m5:0x%x\n",\
				data.matrix[3],data.matrix[4],data.matrix[5]);
			PE_PRINT_VPQ_BE("m6:0x%x,m7:0x%x,m8:0x%x\n",\
				data.matrix[6],data.matrix[7],data.matrix[8]);
			PE_PRINT_VPQ_BE("mb l3:%d,bl:%d,4p:%d,oe:%d\n",\
				data.mux_blend.mux_l3d_in,data.mux_blend.mux_blend_in,
				data.mux_blend.mux_4p_lut_in,data.mux_blend.mux_oetf_out);
			PE_PRINT_VPQ_BE("x0:0x%x,x1:0x%x,x2:0x%x,x3:0x%x\n",\
				data.mux_blend.b4p_lut_x[0],data.mux_blend.b4p_lut_x[1],
				data.mux_blend.b4p_lut_x[2],data.mux_blend.b4p_lut_x[3]);
			PE_PRINT_VPQ_BE("y0:0x%x,y1:0x%x,y2:0x%x,y3:0x%x\n",\
				data.mux_blend.b4p_lut_y[0],data.mux_blend.b4p_lut_y[1],
				data.mux_blend.b4p_lut_y[2],data.mux_blend.b4p_lut_y[3]);

			if(copy_to_user(param.p_data,(void __user *)&data,sizeof(v4l2_hwrap_gamut_post)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		}break;
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		{
//			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_memc_motion_comp_info data;
			__attribute__((unused)) unsigned char *p_user_data;
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_memc_motion_comp_info)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			data.blur_level = gMemcMode.u8Blur;
			data.judder_level = gMemcMode.u8Judder;
			data.memc_type = gMemcMode.u8MemcType;

			if(copy_to_user(param.p_data,(void __user *)&data,sizeof(struct v4l2_ext_memc_motion_comp_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
			PE_PRINT_VPQ_BE("Blur:%d,Judder:%d,Type:%d\n",data.blur_level,data.judder_level,data.memc_type);
		}break;
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		{
			bool gamut_enable[4];
			LX_OVI_MULTIWIN_GAMUT_T lxParam;
			__attribute__((unused)) LX_PE_WIN_ID win_id;
			bool param_enable[4];

			if(copy_from_user(gamut_enable,(void __user *)param.p_data,sizeof(bool)*4))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EINVAL;
			}
			lxParam.win_id = param.wid;
			lxParam.pcc_eotf_en = gamut_enable[0];
			lxParam.pcc_oetf_en = gamut_enable[1];
			lxParam.reg_pcc_en =  gamut_enable[2];
			lxParam.reg_l3d_en =  gamut_enable[3];

			ret = OVI_HAL_GetMultiWindow_Gamut(&lxParam);
			if (ret)
			{
				PE_PRINT_ERROR("OVI_HAL_SetMultiWindow_Gamut error(%d)\n",ret);
				break;
			}

			param_enable[0] = lxParam.pcc_eotf_en;
			param_enable[1] = lxParam.pcc_oetf_en;
			param_enable[2] = lxParam.reg_pcc_en;
			param_enable[3] = lxParam.reg_l3d_en;

			if(copy_to_user((void __user *)param.p_data,&param_enable,sizeof(bool)*4))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		}break;
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
		{
			struct v4l2_ext_vpq_degamma_regamma data;
			__attribute__((unused)) LX_BE_PQ_EOTF_OETF_T lxParam;

			data.u16pT_degamma = gGammaMode.u16pT_degamma;
			data.degamma_size_num = gGammaMode.degamma_size_num;
			data.u16pT_regamma = gGammaMode.u16pT_regamma;
			data.regamma_size_num = gGammaMode.regamma_size_num;

			if(copy_to_user((void __user *)param.p_data, &data, sizeof(struct v4l2_ext_vpq_degamma_regamma)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		}break;
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		{
			struct v4l2_ext_vpq_frame_delay_mode data;
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_frame_delay_mode)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_to_user(param.p_data,(void __user *)&data,sizeof(struct v4l2_ext_vpq_frame_delay_mode)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		}break;
		case V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO: // Workaround function for W22 
		{
			ret = BE_TOP_HAL_Get_PatternInfo(param.p_data, &param.length);
			if (ret)
			{
				PE_PRINT_ERROR("BE_TOP_HAL_Get_PatternInfo error(%d)\n",ret);
				break;
			}

			if(copy_to_user(ctrl->string,(void __user *)&param,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				return -EINVAL;
			}
		
			PE_PRINT_VPQ_BE("v:%d,l:%d,wid:%d, p:0x%x\n",\
				param.version,param.length,param.wid,(unsigned int)(uintptr_t)param.p_data);
		}break;
		default:
			return -EINVAL;
	}

	return ret;
}

/**
* pq-status
*    see SCDCR-2425 (SEETV-PQStatus-210619-1011-1722.pdf)
*    see SCDCR-2482 (v4l2_pq_v1.1.7.pdf)
*
* In case of simple integer :
*    CID=value
*    (ex: "LED_DEMOMODE=0")
*
* In case of array :
*    CID={value1,value2,value3,,,,,}
*    (ex: "HLG_Y_GAIN_TBL={0,1,2,3,,,,,,}")
*
* In case of struct :
*    CID={member1:value1, member2:value2, .....}
*    (ex: "MEMC_MOTION_COMP={type:0,de-blur:0,de-judder:10}")
*
* In case of struct which include array :
*    CID={member1:value1, member2:{value1 of member2, value2 of member2, ...}, ....}
*    (ex: "VPQ_GAMUT_MATRIX_POST={gamma:0, degamma:0,matrix:{0,1,2,3,,,,},
*    mux_blend:{mux_l3d_in:1, ....,b4p_lut_x:{0,1,2,1,,,}}}")
*/
int vpq_proc_show_status_be(struct seq_file *m, void *v, int id)
{
	__attribute__((unused)) int ret;
	__attribute__((unused)) unsigned int index;
	__attribute__((unused)) unsigned int index2;
	__attribute__((unused)) unsigned int detect;
	__attribute__((unused)) unsigned int film_index;
	__attribute__((unused)) const char *memc_type[V4L2_EXT_MEMC_TYPE_MEDIUM+1] = {"off","natual","smooth","user","pullDown","cinema"};
	__attribute__((unused)) const char *cadence_type[] = {"INVALID","original","2-2","2-3","3-2-3-2-2","2-2-2-4","1-1-1-2","1-1-1-1-2","1-2-2","ADAP","PULL_DEF"};
	__attribute__((unused)) const char *film_type[] = {"true","false"};
	__attribute__((unused)) const char *film_detect[] = {"24","25","30","50","60","24to48","24to60","25to50","30to60"};

	if (!m)	return 0;

	switch (id) {
		case V4L2_CID_EXT_LED_DEMOMODE:
		{
			const char *demoType[v4l2_ext_led_ldim_demo_type_max+1] = {"line","leftright","topbottom",""};
			seq_printf(m, "{onoff:%d, type:%s}\n", gBeStatus.demoInfo.bOnOff, demoType[gBeStatus.demoInfo.eType]);
		}break;
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		{
			seq_printf(m, "0x%x\n", gBeStatus.ctrlSpi.ctrlValue);
		}break;
		case V4L2_CID_EXT_LED_DB_IDX:
		{
			seq_printf(m, "%d\n", gBeStatus.ledDbIdx);
		}break;
		case V4L2_CID_EXT_LED_EN:
		{
			seq_printf(m, "%d\n",gBeStatus.ledEn);
		}break;
		case V4L2_CID_EXT_LED_BPL_DATA:
		{
			seq_printf(m, "{ai_brightness:%d, sensor_level:%d, blooming_mode:%d}\n",gBeStatus.bplInfo.ai_brightness, gBeStatus.bplInfo.sensor_level,gBeStatus.bplInfo.blooming_mode);
		}break;
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:
		{
			seq_printf(m, "MEMC_LOWDELAY_MODE=%d\n",_gMemcLowDelay);
		}break;
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		{
			seq_printf(m, "%d\n",_gMemcMotionPro);
		}break;
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		{
			index = (gMemcMode.u8MemcType<V4L2_EXT_MEMC_TYPE_MEDIUM)? gMemcMode.u8MemcType:V4L2_EXT_MEMC_TYPE_MEDIUM;

			switch (gMemcMode.u8MemcType) {
				case 1:
						gMemcMode.u8MemcType = 2;
					break;
				case 2:
						gMemcMode.u8MemcType = 3;
					break;
				case 3:
						gMemcMode.u8MemcType = 4;
					break;
				case 4:
						gMemcMode.u8MemcType = 5;
					break;
				case 5:
						gMemcMode.u8MemcType = 1;
					break;
				default :
						gMemcMode.u8MemcType = 0;
					break;
				}

			seq_printf(m, "{memc_type:%d,blur_level:%d,judder_level:%d}\n",\
				gMemcMode.u8MemcType,gMemcMode.u8Blur,gMemcMode.u8Judder);

			if (lx_chip_rev( ) >= LX_CHIP_REV( O22, A0))
			{
				REG_FRCINFO_FW_TO_DRIVER_0_T FRC_INFO;
				phys_addr_t frc_info_base_phy = 0;

				if (lx_chip() == LX_CHIP_O26) {
					frc_info_base_phy = 0xCCCA8C00;
				}
				else if (lx_chip() == LX_CHIP_O24) {
					frc_info_base_phy = 0xCC4A8C00;
				}
				else if (lx_chip() == LX_CHIP_M23 || lx_chip() == LX_CHIP_O22) {
					frc_info_base_phy = 0xCC9C8C00;
				}
				else {
					break;
				}

				gBE_TOP_FRC_INFO = (volatile REG_FRCINFO_FW_TO_DRIVER_0_T *)ioremap(frc_info_base_phy, sizeof(REG_FRCINFO_FW_TO_DRIVER_0_T));
				if(gBE_TOP_FRC_INFO == NULL) return RET_ERROR;
				FRC_INFO = *gBE_TOP_FRC_INFO;
				index2 = FRC_INFO.cadence;

				if(_gVfreq >= 595)		  //60
				{
					detect = 4;
				}
				else if(_gVfreq >= 495)         //50
				{
					if(index2 == 1)
					{
						detect = 3;
					}
					else
					{
						detect = 3;
					}
				}
				else if(_gVfreq >= 295)        //30
				{
					if(index2 == 1)
					{
						detect = 2;
					}
					else
					{
						detect = 8;
					}
				}
				else if(_gVfreq >= 245)      //25
				{
					if(index2 == 1)
					{
						detect = 1;
					}
					else
					{
						detect = 7;
					}
				}
				else if(_gVfreq >= 235)   //24
				{
					if(index2 == 1)
					{
						detect = 0;
					}
					else if(index == 3 || index == 4)
					{
						detect = 5;
					}
					else
					{
						detect = 6;
					}
				}
				else
				{
					detect = 0;
				}

				if(gMemcMode.u8MemcType == 0 && index2 == 0){film_index = 0;}else{film_index = 1;}
				seq_printf(m, "FILM_DETECTION={enable:%s,detected_film_freq:%s,cadence:%s}\n",film_type[film_index],film_detect[detect],cadence_type[index2]);
	//		enable : Indicates whether film detection is working.detected_film_freq : none/24/24to60/30/30to60/25/25to69/....cadence : none/original/2-2/2-3/4-2-2-2/3-2-3-2-2/.
				iounmap((void*)gBE_TOP_FRC_INFO);
			}
		}break;
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		{
			LX_OVI_TCON_COLOR_TEMP_T lxParam;
			int retVal = 0;

			memset(&lxParam, 0x0, sizeof(LX_OVI_TCON_COLOR_TEMP_T));
			lxParam.bIsGet = TRUE;

			retVal = OVI_HAL_SetColorTemp(&lxParam);
			if (retVal)
			{
				seq_printf(m, "OVI_HAL_GetColorTemp error(%d)\n", retVal);
				break;
			}
			seq_printf(m, "{gain:{%d, %d, %d}, offset:{%d, %d, %d}}\n",
				lxParam.r_gain,lxParam.g_gain,lxParam.b_gain,
				lxParam.r_offset,lxParam.g_offset,lxParam.b_offset);
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		{
			LX_BE_PQ_PCC_PARAMS_T pccParams;
			int retVal = 0;

			if (lx_chip_rev() >= LX_CHIP_REV(O20,A0))
			{
				memset(&pccParams, 0x0, sizeof(LX_BE_PQ_PCC_PARAMS_T));
				pccParams.bIsGet = TRUE;

				retVal = BE_PQ_HAL_Set_PccParams(&pccParams);
				if (retVal)
				{
					seq_printf(m, "BE_PQ_HAL_Set_PccParams error(%d)\n", retVal);
					break;
				}

				seq_printf(m, "{gamma:%d, degamma:%d, matrix:{%d, %d, %d, %d, %d, %d, %d, %d, %d}}\n",
					pccParams.bOetfGammaEn, pccParams.bEotfGammaEn,
					gBeStatus.pccMatrix[0], gBeStatus.pccMatrix[1], gBeStatus.pccMatrix[2],
					gBeStatus.pccMatrix[3], gBeStatus.pccMatrix[4], gBeStatus.pccMatrix[5],
					gBeStatus.pccMatrix[6], gBeStatus.pccMatrix[7], gBeStatus.pccMatrix[8]);
			}
			else
			{
				LX_BE_PQ_PCC_T pccParam;
				LX_BE_PQ_PCC_GAMMA_T gammaParam;
				LX_BE_PQ_PCC_MUX_BLEND_T muxParam;
			
				memset(&pccParam, 0x0, sizeof(LX_BE_PQ_PCC_T));
				memset(&gammaParam, 0x0, sizeof(LX_BE_PQ_PCC_GAMMA_T));
				memset(&muxParam, 0x0, sizeof(LX_BE_PQ_PCC_MUX_BLEND_T));
				pccParam.bIsGet = TRUE;
				gammaParam.bIsGet = TRUE;
				muxParam.bIsGet = TRUE;

				retVal = BE_PQ_HAL_Set_Pcc(&pccParam);
				if (retVal)
				{
					seq_printf(m, "BE_PQ_HAL_Get_Pcc error(%d)\n", retVal);
					break;
				}
				retVal = BE_PQ_HAL_Set_PccGamma(&gammaParam);
				if (retVal)
				{
					seq_printf(m, "BE_PQ_HAL_Get_PccGamma error(%d)\n", retVal);
					break;
				}
				retVal = BE_PQ_HAL_Set_PccMuxBlend(&muxParam);
				if (retVal)
				{
					seq_printf(m, "BE_PQ_HAL_Get_PccMuxBlend error(%d)\n", retVal);
					break;
				}
				seq_printf(m, "Gamma:%d, DeGamma:%d\n",
					gammaParam.bOetfGammaEn, gammaParam.bEotfGammaEn);
				seq_printf(m, "m0:0x%x, m1:0x%x, m2:0x%x\n",
					pccParam.matrix[0], pccParam.matrix[1], pccParam.matrix[2]);
				seq_printf(m, "m3:0x%x, m4:0x%x, m5:0x%x\n",
					pccParam.matrix[3], pccParam.matrix[4], pccParam.matrix[5]);
				seq_printf(m, "m6:0x%x, m7:0x%x, m8:0x%x\n",
					pccParam.matrix[6], pccParam.matrix[7], pccParam.matrix[8]);
				seq_printf(m, "mux_l3d:%d, mux_blend:%d, mux_4p_lut:%d, mux_oetf:%d\n",
					muxParam.u32MuxL3dIn, muxParam.u32MuxBlendIn,
					muxParam.u32Mux4pLutIn, muxParam.u32MuxOetfOut);
				seq_printf(m, "x0:0x%x, x1:0x%x, x2:0x%x, x3:0x%x\n",
					muxParam.au32B4pLutX[0], muxParam.au32B4pLutX[1],
					muxParam.au32B4pLutX[2], muxParam.au32B4pLutX[3]);
				seq_printf(m, "y0:0x%x, y1:0x%x, y2:0x%x, y3:0x%x\n",
					muxParam.au32B4pLutY[0], muxParam.au32B4pLutY[1],
					muxParam.au32B4pLutY[2], muxParam.au32B4pLutY[3]);
			}
		}break;
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
		{
			seq_printf(m, "%d\n", gBeStatus.pwmRatio);
		}break;
		default:
			seq_printf(m, "{not support}\n");
			break;
	}

	return 0;
}

#endif
