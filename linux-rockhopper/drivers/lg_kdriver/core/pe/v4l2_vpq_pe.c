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
#include <linux/seq_file.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#include "os_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "pe_kwrap.h"
#ifdef INCLUDE_KDRV_DE
#include "de_kwrap.h"
#endif
#include "v4l2_vpq.h"
#include "v4l2_vpq_pe.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_pe.h"
#include "pe_cmn.h"
#include "pe_reg.h"
#include "pe_shp.h"

#include "pe_dnt.h"
#include "pe_cmg.h"
#include "pe_dcm.h"
#include "v4l2_vpq_latency.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_VPQ_PE_NUM_OF_FUNC 	(V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT - V4L2_CID_EXT_VPQ_BASE + 1)
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

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
	void *p[V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT - V4L2_CID_EXT_VPQ_BASE + 1];
} v4l2_vpq_pqe_param_t;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern UINT32 _g_pe_kwrap_block_defaul_setting;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int vpq_proc_init_block_func_pe(void);
int vpq_set_dynamic_contrast_lut(struct v4l2_ext_vpq_cmn_data *pqData, struct v4l2_ext_control *ctrl);
int vpq_set_obc_lut(struct v4l2_ext_vpq_cmn_data *pqData, struct v4l2_ext_control *ctrl);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static v4l2_vpq_pqe_param_t stPqeParam;
static int v4l2_vpq_init_ctl_val[3] = {0,0,0};//[0]:vpq,[1]:memc,[2]:led
static UINT32 uPqeParam[V4L2_VPQ_PE_NUM_OF_FUNC] = { 0, };
static UINT32 _g_v4l2_vpq_pe_block_func[V4L2_VPQ_PE_NUM_OF_FUNC] = { 0, };
module_param_named(vpq_dclut_block, _g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT- V4L2_CID_EXT_VPQ_BASE], int, 0644);
static vpq_hwrap_dynamic_lut_o24_v2_t* pDcmLut_webos24_v2;
//static vpq_hwrap_dynamic_lut_o24_t* pDcmLut_webos24;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int v4l2_vpq_compat_vidioc_ext_ctrls_pe(struct v4l2_ext_control *ctrl)
{
	int ret = 0;
	struct v4l2_ext_vpq_cmn_data arg_buf;

	if (!ctrl)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36)
	#ifdef CONFIG_COMPAT
	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		case V4L2_CID_EXT_VPQ_PSP:
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		case V4L2_CID_EXT_VPQ_HISTO_DATA:
		case V4L2_CID_EXT_VPQ_DB_DATA:
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
		{
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
		}break;
		default:
			break;
	}
	
	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		{
			struct v4l2_ext_vpq_sharpness_data shpData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&shpData,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_sharpness_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				shpData.pst_chip_data = (unsigned char *)(uintptr_t)shpData.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&shpData,sizeof(struct v4l2_ext_vpq_sharpness_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}
		break;
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_noise_reduction_data nrData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&nrData,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_noise_reduction_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				nrData.pst_chip_data = (unsigned char *)(uintptr_t)nrData.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&nrData,sizeof(struct v4l2_ext_vpq_noise_reduction_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}break;
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_mpeg_noise_reduction_data dnrData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&dnrData,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_mpeg_noise_reduction_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				dnrData.pst_chip_data = (unsigned char *)(uintptr_t)dnrData.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&dnrData,sizeof(struct v4l2_ext_vpq_mpeg_noise_reduction_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}break;
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		{
			struct v4l2_ext_vpq_decontour_data dctData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&dctData,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_decontour_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				dctData.pst_chip_data = (unsigned char *)(uintptr_t)dctData.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&dctData,sizeof(struct v4l2_ext_vpq_decontour_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}break;
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		{
			struct v4l2_ext_cm_info cminfo;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&cminfo,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_cm_info)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				cminfo.dbInfo = (unsigned char *)(uintptr_t)cminfo.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&cminfo,sizeof(struct v4l2_ext_cm_info)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		{
			struct v4l2_ext_dynamnic_contrast_ctrl dymData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&dymData,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_dynamnic_contrast_ctrl)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				dymData.pst_chip_data = (unsigned char *)(uintptr_t)dymData.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&dymData,sizeof(struct v4l2_ext_dynamnic_contrast_ctrl)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}break;
		case (V4L2_CID_EXT_VPQ_DB_DATA):
		{
			vpq_hwrap_dc_db_all_t dcData;
			do{
				if (!arg_buf.p_data)break;
				if(copy_from_user(&dcData,(void __user *)arg_buf.p_data,sizeof(vpq_hwrap_dc_db_all_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				dcData.dynContDB.pAddrData   = (unsigned char *)(uintptr_t)dcData.dynContDB.compat_data;
				dcData.aplDB.pAddrData        = (unsigned char *)(uintptr_t)dcData.aplDB.compat_data;
				dcData.aiGainDB.pAddrData    = (unsigned char *)(uintptr_t)dcData.aiGainDB.compat_data;
				dcData.stabilzerDB.pAddrData = (unsigned char *)(uintptr_t)dcData.stabilzerDB.compat_data;
				//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
				if(copy_to_user((void __user *)arg_buf.p_data,&dcData,sizeof(vpq_hwrap_dc_db_all_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			}while(0);
		}
		break;
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		break;
		default:
			break;
	}
	#endif
	#endif
	return ret;
}

int v4l2_vpq_vidioc_s_ctrl_pe(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_PE("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_INIT:
		{
			PE_PRINT_VPQ_PE("vpq:move to probe init\n");
			v4l2_vpq_init_ctl_val[0] = ctrl->value;
		}break;
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		{
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_LOW_DELAY_MODE - V4L2_CID_EXT_VPQ_BASE])
				break;

			PE_PRINT_NOTI("SetLowDelayMode = %d\n", (UINT32)ctrl->value);
			#ifdef INCLUDE_KDRV_DE
			ret = de_kwrap_setlowdelaymode((UINT32)ctrl->value);
			#endif
			if (ret)
			{
				PE_PRINT_ERROR("de_kwrap_setlowdelaymode error(%d)\n",ret);
				break;
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &ctrl->value, 0x0))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
			v4l2_vpq_update_lowDelay(ctrl->value);
		}break;
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		{
			unsigned int ireData[2] = { 0, };
			LX_DE_INNER_PATTERN_T inner_param;
			UINT8 greyPattern22PointsIRE[V4L2_EXT_VPQ_INNER_PATTERN_DISABLE] =
			/* IRE		 0|2.5|  5|7.5| 10| 15| 20| 25| 30| 35|  40|  45|  50|	55|  60|  65|  70|	75|  80|  85|  90|	95| 100| */
			/* Level */{16, 22, 27, 33, 38, 49, 60, 71, 82, 93, 104, 115, 126, 137, 147, 158, 169, 180, 191, 202, 213, 224, 235, };
			UINT8 greyPattern24PointsIRE[V4L2_EXT_VPQ_INNER_PATTERN_DISABLE+2] =
			/* IRE		 0|2.5|  5|7.5| 10| 15| 20| 25| 30| 35|  40|  45|  50|	55|  60|  65|  70|	75|  80|  85|  90|	95| 100| */
			/* Level */{  16, 18, 20,	23,	27,	33,	38,	49,	60,	71,	82,	93,	104, 115, 126, 136, 147, 158, 169, 180, 191, 202, 213, 224, 235,};

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_TESTPATTERN- V4L2_CID_EXT_VPQ_BASE])
				break;
			ireData[0] = (UINT32)ctrl->value;
			if(ireData[0] >= 0x100) // 24p case, add 24p base https://harmony.lge.com:8443/issue/browse/SICREQ-1198
			{
				ireData[0] = ireData[0]-0x100;
				if (ireData[0] >= V4L2_EXT_VPQ_INNER_PATTERN_DISABLE+2)
				{
					inner_param.enable = 0x0;
					inner_param.type = LX_DE_PATTERN_FULL_GRAY;
					inner_param.level = 0;
				}
				else
				{
					inner_param.enable = 0x1;
					inner_param.type = LX_DE_PATTERN_DYNAMIC_INNER;
					inner_param.level = (UINT32)greyPattern24PointsIRE[ireData[0]];
				}
			}
			else// 22p case
			{
				if (ireData[0] >= V4L2_EXT_VPQ_INNER_PATTERN_DISABLE)
				{
					inner_param.enable = 0x0;
					inner_param.type = LX_DE_PATTERN_FULL_GRAY;
					inner_param.level = 0;
				}
				else
				{
					inner_param.enable = 0x1;
					inner_param.type = LX_DE_PATTERN_DYNAMIC_INNER;
					inner_param.level = (UINT32)greyPattern22PointsIRE[ireData[0]];
				}
			}
			PE_PRINT_NOTI("original ire = 0x%08X, adjusted ire = %d\n",(UINT32)ctrl->value, ireData[0]);
			PE_PRINT_ETC("de_kwrap_setinnerpattern: enable = %d, type = %d, level = %d\n",
				inner_param.enable, inner_param.type, inner_param.level);

			#ifdef INCLUDE_KDRV_DE
			ret = de_kwrap_setinnerpattern(&inner_param);
			#endif
			if (ret)
			{
				PE_PRINT_ERROR("de_kwrap_setinnerpattern: error(%d)\n", ret);
			}
			else
			{
				uPqeParam[ctrl->id - V4L2_CID_EXT_VPQ_BASE] = ireData[0];
			}
		} break;
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		{
			LX_PE_DNT_FILMMODE_T filmMode;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_REAL_CINEMA- V4L2_CID_EXT_VPQ_BASE])
				break;

			filmMode.win_id = LX_PE_WIN_0;
			filmMode.enable = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("KWRAP_PE_SetFilmMode:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("KWRAP_PE_SetFilmMode: win_id = %d, enable = %d\n", filmMode.win_id, filmMode.enable);

			ret = PE_DNT_SetFilmMode(&filmMode);
			if (ret)
			{
				PE_PRINT_ERROR("PE_DNT_SetFilmMode: error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &ctrl->value, 0x0))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		{
			LX_PE_CMG_COLOR_CTRL_T color_param;
			UINT16 colorGain = (UINT16)ctrl->value;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN- V4L2_CID_EXT_VPQ_BASE])
				break;

			PE_PRINT_CMG_GAIN("stDcColorGain:%d\n",
				colorGain);
			color_param.win_id = LX_PE_WIN_0;
			color_param.saturation = (128 * colorGain) / 100;
			if (color_param.saturation > 255)
				color_param.saturation = 255;
			PE_PRINT_CMG_GAIN("color_param: win_id %d, saturation %d\n",
				color_param.win_id, color_param.saturation);
			if(PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetCenColorParam((void *)&color_param);
			}
			else
			{
				ret = PE_CMG_SetCenColorCtrl(&color_param);
			}
			if (ret)
			{
				PE_PRINT_ERROR("PE_CMG_SetCenColorCtrl error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &ctrl->value, 0x0))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		}break;
		case V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL:
		{
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL- V4L2_CID_EXT_VPQ_BASE])
				break;
			PE_PRINT_NOTI("OBC_stereo:ctrl->value = %d\n",ctrl->value);

			ret = PE_SHP_SetObcStereoCtrl((void *)&ctrl->value);
			if (ret)
			{
				PE_PRINT_ERROR("PE_SHP_SetObcStereoCtrl: error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &ctrl->value, 0x0))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		}break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

int v4l2_vpq_vidioc_g_ctrl_pe(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	//struct vpq_fh *fh = __fh;
	UINT16 uLevel = 0;
	static UINT16 pre_uLevel = 0;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_PE("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_INIT:
		{
			ret = vpq_hwrap_isinitialized();
			if (!ret)	ctrl->value=0xff;
			else		ctrl->value=v4l2_vpq_init_ctl_val[0];
		}break;
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		{
			ctrl->value = (int)uPqeParam[ctrl->id - V4L2_CID_EXT_VPQ_BASE];
		} break;
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		{
			if (v4l2_vpq_pe_get_param(ctrl->id, &ctrl->value))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_get_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		}break;
		case V4L2_CID_EXT_VPQ_NOISE_LEVEL:
		{
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_NOISE_LEVEL- V4L2_CID_EXT_VPQ_BASE])
			{
				ctrl->value = pre_uLevel;
				break;
			}
			ret = vpq_hwrap_getnoiselevel(&uLevel);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_getnoiselevel error(%d)\n", ret);
			}
			ctrl->value = (UINT32)uLevel;
			pre_uLevel = uLevel;
			//PE_PRINT_INFO("V4L2_CID_EXT_VPQ_NOISE_LEVEL: uLevel = %d\n", uLevel);
		}break;
		default:
			ret = -EINVAL;
	}

	return 0;
}

int v4l2_vpq_pe_save_param(__u32 id, void __user *ptr, unsigned int ver)
{
	int ret = 0;
	void *p = NULL;

	if ((id < V4L2_CID_EXT_VPQ_BASE) || (id > V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT))
		return ret;

	p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE];

	switch (id)
	{
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		{
			struct v4l2_ext_vpq_picture_ctrl_data *pstData = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_picture_ctrl_data *)p;
			memcpy(pstData, ptr, sizeof(*pstData));
		} break;
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		{
			struct v4l2_ext_vpq_sharpness_data *pstData = NULL;
			vpq_hwrap_chip_shp_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_shp_o20_t __attribute__((unused)) *pstChipData_o20 = NULL;
			vpq_hwrap_chip_shp_e60_t __attribute__((unused)) *pstChipData_e60 = NULL;
			vpq_hwrap_chip_shp_o22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_shp_o22n2_t __attribute__((unused)) *pstChipData_o22n2 = NULL;
			vpq_hwrap_chip_shp_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_shp_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_sharpness_data *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			if(ver == 0x80)// O22n2, o24
			{
				if(PE_KDRV_VER_O26)
				{
					if (pstData->pst_chip_data &&
						((pstChipData_o26 = (vpq_hwrap_chip_shp_o26_t *)OS_Malloc(sizeof(*pstChipData_o26))) != NULL))
					{
						memcpy(pstChipData_o26, pstData->pst_chip_data, sizeof(*pstChipData_o26));
						pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
					}
				}
			}
			else if(ver == 0x60)// O22n2, o24
			{
				if(PE_KDRV_VER_O22)
				{
					if (pstData->pst_chip_data &&
						((pstChipData_o22n2 = (vpq_hwrap_chip_shp_o22n2_t *)OS_Malloc(sizeof(*pstChipData_o22n2))) != NULL))
					{
						memcpy(pstChipData_o22n2, pstData->pst_chip_data, sizeof(*pstChipData_o22n2));
						pstData->pst_chip_data = (unsigned char *)pstChipData_o22n2;
					}
				}
				else if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
				{
					if (pstData->pst_chip_data &&
						((pstChipData_o24 = (vpq_hwrap_chip_shp_o24_t *)OS_Malloc(sizeof(*pstChipData_o24))) != NULL))
					{
						memcpy(pstChipData_o24, pstData->pst_chip_data, sizeof(*pstChipData_o24));
						pstData->pst_chip_data = (unsigned char *)pstChipData_o24;
					}
				}
			}
			else if(ver == 0x40)// O22, o22n, m23
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o22 = (vpq_hwrap_chip_shp_o22_t *)OS_Malloc(sizeof(*pstChipData_o22))) != NULL))
				{
					memcpy(pstChipData_o22, pstData->pst_chip_data, sizeof(*pstChipData_o22));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
				}
			}
			else if(PE_KDRV_VER_E60)
			{
				if (pstData->pst_chip_data &&
					((pstChipData_e60 = (vpq_hwrap_chip_shp_e60_t *)OS_Malloc(sizeof(*pstChipData_e60))) != NULL))
				{
					memcpy(pstChipData_e60, pstData->pst_chip_data, sizeof(*pstChipData_e60));
					pstData->pst_chip_data = (unsigned char *)pstChipData_e60;
				}
			}
			else if(PE_KDRV_VER_O20)
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o20 = (vpq_hwrap_chip_shp_o20_t *)OS_Malloc(sizeof(*pstChipData_o20))) != NULL))
				{
					memcpy(pstChipData_o20, pstData->pst_chip_data, sizeof(*pstChipData_o20));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o20;
				}
			}
			else if(ver == 0x1)// temporally M23 for SOCTS version=1, chipdata=NULL case
			{
			     // do nothing bc. chipdata=NULL case
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		{
			struct v4l2_ext_dynamnic_contrast_ctrl *pstData = NULL;
			vpq_hwrap_dc_dynamic_webos60_t __attribute__((unused)) *pstChipData_webos60_t = NULL;
			vpq_hwrap_dc_dynamic_weboso22_t __attribute__((unused)) *pstChipData_weboso22_t = NULL;
			vpq_hwrap_dc_dynamic_weboso26_t __attribute__((unused)) *pstChipData_weboso26_t = NULL;
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_dynamnic_contrast_ctrl *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			if(ver == 0x80)// webos26
			{
				if (pstData->pst_chip_data &&
					((pstChipData_weboso26_t = (vpq_hwrap_dc_dynamic_weboso26_t *)OS_Malloc(sizeof(*pstChipData_weboso26_t))) != NULL))
				{
					memcpy(pstChipData_weboso26_t, pstData->pst_chip_data, sizeof(*pstChipData_weboso26_t));
					pstData->pst_chip_data = (unsigned char *)pstChipData_weboso26_t;
				}
			}
			else if(ver == 0x40)// webos22 O22/E60n, temporally M23 for SOCTS
			{
				if (pstData->pst_chip_data &&
					((pstChipData_weboso22_t = (vpq_hwrap_dc_dynamic_weboso22_t *)OS_Malloc(sizeof(*pstChipData_weboso22_t))) != NULL))
				{
					memcpy(pstChipData_weboso22_t, pstData->pst_chip_data, sizeof(*pstChipData_weboso22_t));
					pstData->pst_chip_data = (unsigned char *)pstChipData_weboso22_t;
				}
			}
			else  //webos6.0- o20e60
			{
				if (pstData->pst_chip_data &&
					((pstChipData_webos60_t = (vpq_hwrap_dc_dynamic_webos60_t *)OS_Malloc(sizeof(*pstChipData_webos60_t))) != NULL))
				{
					memcpy(pstChipData_webos60_t, pstData->pst_chip_data, sizeof(*pstChipData_webos60_t));
					pstData->pst_chip_data = (unsigned char *)pstChipData_webos60_t;
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		{
			#if 1
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_dynamic_lut_o24_v2_t))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			if(ver == 0x61)
				memcpy(p, ptr, sizeof(vpq_hwrap_dynamic_lut_o24_v2_t));
			else if(ver == 0x60)
				memcpy(p, ptr, sizeof(vpq_hwrap_dynamic_lut_o24_t));
			else if(ver == 0x40 || ver == 0x30)
				memcpy(p, ptr, sizeof(vpq_hwrap_dynamic_lut_webos60_t));
			else if(ver == 0x2 || ver == 0x1)
				memcpy(p, ptr, sizeof(vpq_hwrap_dynamic_lut_t));
			else if(ver == 0x0)
				memcpy(p, ptr, sizeof(vpq_hwrap_dynamic_lut_pioneer_t));
			#else
			
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(signed int) * PE_KWRAP_DCM_LUT_STEP * 2)))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			memcpy(p, ptr, sizeof(signed int) * PE_KWRAP_DCM_LUT_STEP * 2);
			#endif
		} break;
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		{
			struct v4l2_ext_cm_info *pstData = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_cm_info *)p;
			memcpy(pstData, ptr, sizeof(*pstData));
		} break;
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_noise_reduction_data *pstData = NULL;
			vpq_hwrap_chip_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t __attribute__((unused)) *pstChipData_o20_e60_022 = NULL;
			vpq_hwrap_chip_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_noise_reduction_data *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			if(ver == 0x80) //webos26 o26
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o26 = (vpq_hwrap_chip_nr_o26_t *)OS_Malloc(sizeof(*pstChipData_o26))) != NULL))
				{
					memcpy(pstChipData_o26, pstData->pst_chip_data, sizeof(*pstChipData_o26));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
				}
			}
			else
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o20_e60_022 = (vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *)OS_Malloc(sizeof(*pstChipData_o20_e60_022))) != NULL))
				{
					memcpy(pstChipData_o20_e60_022, pstData->pst_chip_data, sizeof(*pstChipData_o20_e60_022));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60_022;
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_mpeg_noise_reduction_data *pstData = NULL;
			vpq_hwrap_chip_mpeg_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t __attribute__((unused)) *pstChipData_o20_e60_022 = NULL;
			vpq_hwrap_chip_mpeg_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_mpeg_noise_reduction_data *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			
			if(ver == 0x80) //webos26 o26
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o26 = (vpq_hwrap_chip_mpeg_nr_o26_t *)OS_Malloc(sizeof(*pstChipData_o26))) != NULL))
				{
					memcpy(pstChipData_o26, pstData->pst_chip_data, sizeof(*pstChipData_o26));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
				}
			}
			else
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o20_e60_022 = (vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *)OS_Malloc(sizeof(*pstChipData_o20_e60_022))) != NULL))
				{
					memcpy(pstChipData_o20_e60_022, pstData->pst_chip_data, sizeof(*pstChipData_o20_e60_022));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60_022;
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		{
			struct v4l2_ext_vpq_decontour_data *pstData = NULL;
			vpq_hwrap_chip_decontour_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_decontour_o20_f20_e60_t __attribute__((unused)) *pstChipData_o20_e60 = NULL;
			vpq_hwrap_chip_decontour_o22_f22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_decontour_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_decontour_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_decontour_data *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			if(ver == 0x80) //webos26
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o26 = (vpq_hwrap_chip_decontour_o26_t *)OS_Malloc(sizeof(*pstChipData_o26))) != NULL))
				{
					memcpy(pstChipData_o26, pstData->pst_chip_data, sizeof(*pstChipData_o26));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
				}
			}
			else if(ver == 0x60) //webos23 o24
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o24 = (vpq_hwrap_chip_decontour_o24_t *)OS_Malloc(sizeof(*pstChipData_o24))) != NULL))
				{
					memcpy(pstChipData_o24, pstData->pst_chip_data, sizeof(*pstChipData_o24));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o24;
				}
			}
			else if(ver == 0x40) //webos22 o22, temporally M23
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o22 = (vpq_hwrap_chip_decontour_o22_f22_t *)OS_Malloc(sizeof(*pstChipData_o22))) != NULL))
				{
					memcpy(pstChipData_o22, pstData->pst_chip_data, sizeof(*pstChipData_o22));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
				}
			}
 			else if(PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
			{
				if (pstData->pst_chip_data &&
					((pstChipData_o20_e60 = (vpq_hwrap_chip_decontour_o20_f20_e60_t *)OS_Malloc(sizeof(*pstChipData_o20_e60))) != NULL))
				{
					memcpy(pstChipData_o20_e60, pstData->pst_chip_data, sizeof(*pstChipData_o20_e60));
					pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60;
				}
			}
			else if(ver == 0x1)// temporally M23 for SOCTS version=1, chipdata=NULL case
			{
			     // do nothing bc. chipdata=NULL case
			}
 		} break;
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		{
			struct v4l2_ext_vpq_black_level_info *pstData = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_black_level_info *)p;
			memcpy(pstData, ptr, sizeof(*pstData));
		} break;
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		{
			struct v4l2_ext_vpq_super_resolution_data *pstData = NULL;
			vpq_hwrap_chip_sr_t __attribute__((unused)) *pstChipData = NULL;

			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(*pstData))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			pstData = (struct v4l2_ext_vpq_super_resolution_data *)p;
			if (pstData->pst_chip_data)
			{
				OS_Free(pstData->pst_chip_data);
			}
			memcpy(pstData, ptr, sizeof(*pstData));
			if (pstData->pst_chip_data &&
				((pstChipData = (vpq_hwrap_chip_sr_t *)OS_Malloc(sizeof(*pstChipData))) != NULL))
			{
				memcpy(pstChipData, pstData->pst_chip_data, sizeof(*pstChipData));
				pstData->pst_chip_data = (unsigned char *)pstChipData;
			}
		} break;
		case V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL:
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		{
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(UINT32))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			memcpy(p, ptr, sizeof(UINT32));
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		{
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(UINT32))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			memcpy(p, ptr, sizeof(UINT32));
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		{
			
			if(ver == 0x80) // o26
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t));
			}
			else
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_t));
			}
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		{
			if(ver == 0x80) // webos23 o22, M23 for SOCTS
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso26_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso26_t));
			}
			else if(ver == 0x50) // webos23 o22, M23 for SOCTS
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso23_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso23_t));
			}
			else if(ver == 0x40) // webos22 o22, temporally M23 for SOCTS
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso22_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso22_t));
			}
			else
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_drc_cont_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_chip_dc2p_drc_cont_t));
			}
		} break;
		case V4L2_CID_EXT_VPQ_PSP:
		{
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_chip_perspective_t))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			memcpy(p, ptr, sizeof(vpq_hwrap_chip_perspective_t));
		} break;
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		{
			if(ver == 0x40) // webos22 o22, temporally M23 for SOCTS
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_lut_e60_o22_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_lut_e60_o22_t));
			}
			else if(PE_KDRV_VER_E60)
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_lut_e60_o22_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_lut_e60_o22_t));
			}
			else if(PE_KDRV_VER_O20)
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_lut_o20_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_lut_o20_t));
			}
		} break;
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		{
			if(ver == 0x40)// webos22 o22, temporally M23 for SOCTS
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_ctrl_o22_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_ctrl_o22_t));
			}
			else if(PE_KDRV_VER_E60)
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_ctrl_e60_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_ctrl_e60_t));
			}
			else if(PE_KDRV_VER_O20 || PE_KDRV_VER_O22)
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_obc_ctrl_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_obc_ctrl_t));
			}
		} break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			if (!p &&
				!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(struct vpq_hwrap_ext_pattern_info))))
			{
				PE_PRINT_ERROR("OS_Malloc error\n");
				return -ENOMEM;
			}
			memcpy(p, ptr, sizeof(struct vpq_hwrap_ext_pattern_info));
		} break;
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
		{
			if(ver == 0x50)// webos23 o22,
			{
				if (!p &&
					!(p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE] = OS_Malloc(sizeof(vpq_hwrap_dbc_db_t))))
				{
					PE_PRINT_ERROR("OS_Malloc error\n");
					return -ENOMEM;
				}
				memcpy(p, ptr, sizeof(vpq_hwrap_dbc_db_t));
			}
		} break;
		default:
			break;
	}

	return ret;
}

int v4l2_vpq_pe_get_param(__u32 id, void __user *ptr)
{
	int ret = 0;
	void *p = NULL;
	struct v4l2_ext_vpq_cmn_data param;
	void __user *p_user_data, *p_temp;

	if ((id < V4L2_CID_EXT_VPQ_BASE) || (id > V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT))
		return ret;

	if (((p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE]) == NULL) || (ptr == NULL))
	{
		PE_PRINT_ERROR("v4l2_vpq_pe_get_param() error\n");
		return -EPERM;
	}
	//PE_PRINT_NOTI("get_param id : %s \n", vpq_ctrl_id_to_str(id));
	switch (id)
	{
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		{
			*(UINT32 *)ptr = *(UINT32 *)p;
			return ret;
		} break;
		default:
			break;
	}

	if (copy_from_user(&param, ptr, sizeof(param)))
	{
		PE_PRINT_ERROR("copy_from_user error\n");
		return -EPERM;
	}

	if ((p_user_data = (void __user *)param.p_data) == NULL)
	{
		PE_PRINT_ERROR("p_user_data is null\n");
		return -EINVAL;
	}

	switch (id)
	{
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		{
			struct v4l2_ext_vpq_picture_ctrl_data *stData =(struct v4l2_ext_vpq_picture_ctrl_data*)p;;
			PE_PRINT_DEBUG("v:%d,l:%d,wid:%d, set c:%d,b:%d,s:%d,h:%d\n",\
			param.version,param.length,param.wid,\
			stData->chipData_contrast,stData->chipData_brightness,stData->chipData_saturation,stData->chipData_hue);
			if (copy_to_user(p_user_data, p, sizeof(struct v4l2_ext_vpq_picture_ctrl_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		} break;
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		{
			struct v4l2_ext_vpq_sharpness_data stData;
			struct v4l2_ext_vpq_sharpness_data *pstData = (struct v4l2_ext_vpq_sharpness_data *)p;
			vpq_hwrap_chip_shp_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_shp_o20_t __attribute__((unused)) *pstChipData_o20 = NULL;
			vpq_hwrap_chip_shp_e60_t __attribute__((unused)) *pstChipData_e60 = NULL;
			vpq_hwrap_chip_shp_o22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_shp_o22n2_t __attribute__((unused)) *pstChipData_o22n2 = NULL;
			vpq_hwrap_chip_shp_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_shp_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			PE_PRINT_SHP("get: reserved ui: %d, pstData.pst_chip_data 0x%p, stData.pst_chip_data 0x%p\n", pstData->ui_value[1],pstData->pst_chip_data, stData.pst_chip_data);
			
			if(param.version == 0x80)// O22n2, o24
			{
				if(PE_KDRV_VER_O26)
				{
					pstChipData_o26 = (vpq_hwrap_chip_shp_o26_t *)pstData->pst_chip_data;
					pstData->pst_chip_data = p_temp;
					if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					if (p_temp && pstChipData_o26 && copy_to_user(p_temp, pstChipData_o26, sizeof(*pstChipData_o26)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
				}
			}
			else if(param.version == 0x60)// O22n2, o24
			{
				if(PE_KDRV_VER_O22)
				{
					pstChipData_o22n2 = (vpq_hwrap_chip_shp_o22n2_t *)pstData->pst_chip_data;
					pstData->pst_chip_data = p_temp;
					if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					if (p_temp && pstChipData_o22n2 && copy_to_user(p_temp, pstChipData_o22n2, sizeof(*pstChipData_o22n2)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					pstData->pst_chip_data = (unsigned char *)pstChipData_o22n2;
				}
				else if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
				{
					pstChipData_o24 = (vpq_hwrap_chip_shp_o24_t *)pstData->pst_chip_data;
					pstData->pst_chip_data = p_temp;
					if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					if (p_temp && pstChipData_o24 && copy_to_user(p_temp, pstChipData_o24, sizeof(*pstChipData_o24)))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					pstData->pst_chip_data = (unsigned char *)pstChipData_o24;
				}
			}
			else if(param.version == 0x40)// O22, temporally M23 for SOCTS
			{
				pstChipData_o22 = (vpq_hwrap_chip_shp_o22_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o22 && copy_to_user(p_temp, pstChipData_o22, sizeof(*pstChipData_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
			}
			else if (PE_KDRV_VER_E60)
			{
				pstChipData_e60 = (vpq_hwrap_chip_shp_e60_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_e60 && copy_to_user(p_temp, pstChipData_e60, sizeof(*pstChipData_e60)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_e60;
			}
			else if(PE_KDRV_VER_O20)
			{
				pstChipData_o20 = (vpq_hwrap_chip_shp_o20_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o20 && copy_to_user(p_temp, pstChipData_o20, sizeof(*pstChipData_o20)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o20;
			}
			else if(param.version == 0x1)// temporally M23 for SOCTS  version=1, chipdata=NULL case
			{
				pstChipData_o22 = (vpq_hwrap_chip_shp_o22_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				#if 0
				if (p_temp && pstChipData_o22 && copy_to_user(p_temp, pstChipData_o22, sizeof(*pstChipData_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
				#endif
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		{
			struct v4l2_ext_dynamnic_contrast_ctrl stData;
			struct v4l2_ext_dynamnic_contrast_ctrl *pstData = (struct v4l2_ext_dynamnic_contrast_ctrl *)p;
			vpq_hwrap_dc_dynamic_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_dc_dynamic_webos60_t __attribute__((unused)) *pstChipData_webos60 = NULL;
			vpq_hwrap_dc_dynamic_weboso22_t __attribute__((unused)) *pstChipData_weboso22 = NULL;
			vpq_hwrap_dc_dynamic_weboso26_t __attribute__((unused)) *pstChipData_weboso26 = NULL;
			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			PE_PRINT_DCM("get: version: %d reserved ui: %d, pstData.pst_chip_data 0x%p, stData.pst_chip_data 0x%p\n",\
				param.version, pstData->uDcVal,pstData->pst_chip_data, stData.pst_chip_data);

			if(param.version == 0x80)// webos26 o26
			{
				pstChipData_weboso26 = (vpq_hwrap_dc_dynamic_weboso26_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_weboso26 && copy_to_user(p_temp, pstChipData_weboso26, sizeof(*pstChipData_weboso26)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_weboso26;
			}
			else if(param.version == 0x40)// webos22 O22/E60n, temporally M23 for SOCTS
			{
				pstChipData_weboso22 = (vpq_hwrap_dc_dynamic_weboso22_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_weboso22 && copy_to_user(p_temp, pstChipData_weboso22, sizeof(*pstChipData_weboso22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_weboso22;
			}
			else if(param.version == 0x30) //webos6.0- o20e60
			{
				pstChipData_webos60 = (vpq_hwrap_dc_dynamic_webos60_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_webos60 && copy_to_user(p_temp, pstChipData_webos60, sizeof(*pstChipData_webos60)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_webos60;
			}
			else if(param.version == 0x2)
			{
				pstChipData = (vpq_hwrap_dc_dynamic_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData && copy_to_user(p_temp, pstChipData, sizeof(*pstChipData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData;
			}
			else if (param.version == 0x1 || param.version == 0x0)
			{
				if (copy_to_user(p_user_data, p, sizeof(struct v4l2_ext_dynamnic_contrast_ctrl)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		{
			//UINT32 i;
			UINT32 size;
			PE_PRINT_DCM("get: version: %d \n", param.version);
			if(param.version == 0x2)
			{
				size = sizeof(UINT32)*16*2 + sizeof(UINT16)*66;
			}
			else if(param.version == 0x30 || param.version == 0x40)
			{
				size = sizeof(UINT32)*32*2 + sizeof(UINT16)*66 + sizeof(UINT16)*4*4;
			}
			else if(param.version == 0x60)
			{
				size = sizeof(UINT32)*32*2 + sizeof(UINT16)*66 + sizeof(UINT16)*4*4 + sizeof(UINT8)*16*2;
			}
			else if(param.version == 0x61)
			{
				size = sizeof(UINT32)*32*4*2 + sizeof(UINT16)*66 + sizeof(UINT16)*4*4 + sizeof(UINT8)*16*2;
			}
			else
			{
				size = sizeof(signed int) * PE_KWRAP_DCM_LUT_STEP * 2;
			}
			if (copy_to_user(p_user_data, p, size))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		} break;
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		{
			if (copy_to_user(p_user_data, p, sizeof(struct v4l2_ext_cm_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		} break;
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_noise_reduction_data stData;
			struct v4l2_ext_vpq_noise_reduction_data *pstData = (struct v4l2_ext_vpq_noise_reduction_data *)p;
			vpq_hwrap_chip_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t __attribute__((unused)) *pstChipData_o20_e60_o22 = NULL;
			vpq_hwrap_chip_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			if(param.version == 0x80) // webos26
			{
				pstChipData_o26 = (vpq_hwrap_chip_nr_o26_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o26 && copy_to_user(p_temp, pstChipData_o26, sizeof(*pstChipData_o26)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
			}
			else
			{
				pstChipData_o20_e60_o22 = (vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o20_e60_o22 && copy_to_user(p_temp, pstChipData_o20_e60_o22, sizeof(*pstChipData_o20_e60_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60_o22;
			}
		} break;
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_mpeg_noise_reduction_data stData;
			struct v4l2_ext_vpq_mpeg_noise_reduction_data *pstData = (struct v4l2_ext_vpq_mpeg_noise_reduction_data *)p;
			vpq_hwrap_chip_mpeg_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t __attribute__((unused)) *pstChipData_o20_e60_o22 = NULL;
			vpq_hwrap_chip_mpeg_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			if(param.version == 0x80) // webos26
			{
				pstChipData_o26 = (vpq_hwrap_chip_mpeg_nr_o26_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o26 && copy_to_user(p_temp, pstChipData_o26, sizeof(*pstChipData_o26)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
			}
			else
			{
				pstChipData_o20_e60_o22 = (vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o20_e60_o22 && copy_to_user(p_temp, pstChipData_o20_e60_o22, sizeof(*pstChipData_o20_e60_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60_o22;
			}
		} break;
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		{
			struct v4l2_ext_vpq_decontour_data stData;
			struct v4l2_ext_vpq_decontour_data *pstData = (struct v4l2_ext_vpq_decontour_data *)p;
			vpq_hwrap_chip_decontour_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_decontour_o20_f20_e60_t __attribute__((unused)) *pstChipData_o20_e60 = NULL;
			vpq_hwrap_chip_decontour_o22_f22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_decontour_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_decontour_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			if(param.version == 0x80) // webos26
			{
				pstChipData_o26 = (vpq_hwrap_chip_decontour_o26_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o26 && copy_to_user(p_temp, pstChipData_o26, sizeof(*pstChipData_o26)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o26;
			}
			else if(param.version == 0x60) // webos24
			{
				pstChipData_o24 = (vpq_hwrap_chip_decontour_o24_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o24 && copy_to_user(p_temp, pstChipData_o24, sizeof(*pstChipData_o24)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o24;
			}
			else if(param.version == 0x40) // webos22 O22, temporally M23 for SOCTS
			{
				pstChipData_o22 = (vpq_hwrap_chip_decontour_o22_f22_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o22 && copy_to_user(p_temp, pstChipData_o22, sizeof(*pstChipData_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
			}
			else if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
			{
				pstChipData_o20_e60 = (vpq_hwrap_chip_decontour_o20_f20_e60_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				if (p_temp && pstChipData_o20_e60 && copy_to_user(p_temp, pstChipData_o20_e60, sizeof(*pstChipData_o20_e60)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o20_e60;
			}
			else if(param.version == 0x1)// temporally M23 for SOCTS  version=1, chipdata=NULL case
			{
				pstChipData_o22 = (vpq_hwrap_chip_decontour_o22_f22_t *)pstData->pst_chip_data;
				pstData->pst_chip_data = p_temp;
				if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				#if 0
				if (p_temp && pstChipData_o22 && copy_to_user(p_temp, pstChipData_o22, sizeof(*pstChipData_o22)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				pstData->pst_chip_data = (unsigned char *)pstChipData_o22;
				#endif
			}
		} break;
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		{
			if (copy_to_user(p_user_data, p, sizeof(struct v4l2_ext_vpq_black_level_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		} break;
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		{
			struct v4l2_ext_vpq_super_resolution_data stData;
			struct v4l2_ext_vpq_super_resolution_data *pstData = (struct v4l2_ext_vpq_super_resolution_data *)p;
			vpq_hwrap_chip_sr_t __attribute__((unused)) *pstChipData = NULL;

			if (copy_from_user(&stData, p_user_data, param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				return -EPERM;
			}
			p_temp = (void __user *)stData.pst_chip_data;
			PE_PRINT_SHP("get: reserved ui: %d, pstData.pst_chip_data 0x%p, stData.pst_chip_data 0x%p\n", pstData->ui_value,pstData->pst_chip_data, stData.pst_chip_data);
			pstChipData = (vpq_hwrap_chip_sr_t *)pstData->pst_chip_data;
			pstData->pst_chip_data = p_temp;
			PE_PRINT_SHP("get: ui: %d, pstData.pst_chip_data 0x%p\n", pstData->ui_value,pstData->pst_chip_data);
			if (copy_to_user(p_user_data, pstData, sizeof(*pstData)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			if (p_temp && pstChipData && copy_to_user(p_temp, pstChipData, sizeof(*pstChipData)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			pstData->pst_chip_data = (unsigned char *)pstChipData;
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		{
			if(param.version == 0x80) // webos26
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		{
			if(param.version == 0x80) //webos23 M23, O22
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso26_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if(param.version == 0x50) //webos23 M23, O22
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso23_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if(param.version == 0x40) //webos22 o22, temporally M23 for SOCTS
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso22_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_dc2p_drc_cont_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_PSP:
		{
			if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_chip_perspective_t)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		} break;
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		{
			if(param.version == 0x40) //webos22 o22, temporally M23 for SOCTS
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_lut_e60_o22_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if (PE_KDRV_VER_E60)
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_lut_e60_o22_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if (PE_KDRV_VER_O20)
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_lut_o20_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		{
			if(param.version == 0x40)// webos22 o22, temporally M23 for SOCTS
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_ctrl_o22_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			if (PE_KDRV_VER_E60)
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_ctrl_e60_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
			else if (PE_KDRV_VER_O20)
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_obc_ctrl_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			if (copy_to_user(p_user_data, p, sizeof(struct vpq_hwrap_ext_pattern_info)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
		{
			if(param.version == 0x50)// webos23 o22
			{
				if (copy_to_user(p_user_data, p, sizeof(vpq_hwrap_dbc_db_t)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
			}
		} break;
		default:
			break;
	}

	return ret;
}

int vpq_set_ext_ctrl_pe(struct v4l2_ext_control *ctrl)
{
	struct v4l2_ext_vpq_cmn_data pqData;
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	if (copy_from_user(&pqData, (void __user *)ctrl->ptr, sizeof(pqData)))
	{
		PE_PRINT_ERROR("copy_from_user error\n");
		return -EINVAL;
	}

	PE_PRINT_DEBUG("%s(%d): ctrl->ptr %p, pqData.p_data %p, pqData.length %u, ver 0x%02X\n",\
		__func__, (ctrl->id-V4L2_CID_EXT_VPQ_BASE),	ctrl->ptr, pqData.p_data, pqData.length, pqData.version);

	if (!pqData.p_data || (pqData.length == 0))
	{
		PE_PRINT_ERROR("invalid data\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		{
			struct v4l2_ext_vpq_picture_ctrl_data data;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_PICTURE_CTRL- V4L2_CID_EXT_VPQ_BASE])
				break;

			if (copy_from_user(&data, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			pqData.p_data = (unsigned char *)&data;
			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, set c:%d,b:%d,s:%d,h:%d\n",\
				pqData.version,pqData.length,pqData.wid,\
				data.chipData_contrast,data.chipData_brightness,data.chipData_saturation,data.chipData_hue);
			ret = vpq_hwrap_setpicturectrl(&pqData);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setpicturectrl error(%d)\n",ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &data, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		{
			struct v4l2_ext_vpq_black_level_info data;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_BLACK_LEVEL- V4L2_CID_EXT_VPQ_BASE])
				break;

			if (copy_from_user(&data, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			pqData.p_data = (unsigned char *)&data;
			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, ui_value:%d,curr_input:%d,color_space:%d,black_level_type:%d(0,1,4,5:yuv,others:rgb)\n",
				pqData.version,pqData.length,pqData.wid,data.ui_value,data.curr_input,data.color_space,data.black_level_type);
			ret = vpq_hwrap_setblacklevel2(&pqData);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setblacklevel error(%d)\n",ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &data, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		{
			vpq_hwrap_real_cinema_t realCinema;
			LX_PE_DNT_FILMMODE_T filmMode;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_REAL_CINEMA- V4L2_CID_EXT_VPQ_BASE])
				break;

			if (copy_from_user(&realCinema, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			filmMode.win_id = (pqData.wid == 0) ? LX_PE_WIN_0 : LX_PE_WIN_1;
			filmMode.enable = realCinema.filmMode ? 1 : 0;
			PE_PRINT_ETC("user info: length = %d, chip_data : %p\n",pqData.length, realCinema.chip_data);
			PE_PRINT_ETC("KWRAP_PE_SetFilmMode: win_id = %d, enable = %d\n", filmMode.win_id, filmMode.enable);

			ret = PE_DNT_SetFilmMode(&filmMode);
			if (ret)
			{
				PE_PRINT_ERROR("PE_DNT_SetFilmMode: error(%d)\n", ret);
			}
			#if 0
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &realCinema))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
			#endif
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		{
			struct v4l2_ext_dynamnic_contrast_ctrl dcData;
			//vpq_hwrap_dynamic_contrast_t dcData;
			vpq_hwrap_dc_dynamic_t dcContrast;
			vpq_hwrap_dc_dynamic_webos60_t dcContrast_webos60;
			vpq_hwrap_dc_dynamic_weboso22_t dcContrast_weboso22;
			vpq_hwrap_dc_dynamic_weboso26_t dcContrast_weboso26;
			LX_PE_DCM_DRC_MODE_T drc_param;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST- V4L2_CID_EXT_VPQ_BASE])
				break;
			PE_PRINT_DCM("[%s.%d]version:%d\n",\
						__F__, __L__,	pqData.version);

			if(pqData.version == 0x80) //webos26- o26
			{
				if (copy_from_user(&dcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(&dcContrast_weboso26, (void __user *)dcData.pst_chip_data, sizeof(vpq_hwrap_dc_dynamic_weboso26_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				else
				{
					dcData.pst_chip_data = (unsigned char *)&dcContrast_weboso26;
					ret = vpq_hwrap_setdynamiccontrast_weboso26(&dcData);
					if (ret)
					{
						PE_PRINT_ERROR("vpq_hwrap_setdynamiccontrast_weboso26: error(%d)\n", ret);
					}
				}
				if (!ret)
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &dcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(pqData.version == 0x40) //webos7.0- o22
			{
				if (copy_from_user(&dcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(&dcContrast_weboso22, (void __user *)dcData.pst_chip_data, sizeof(vpq_hwrap_dc_dynamic_weboso22_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				else
				{
					PE_PRINT_DCM("[%s.%d] dse ctrl version:%d\n"\
						" v4l2 set: chroma_gain_en:%d\n"\
						"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
						"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
						__F__, __L__,\
						pqData.version, \
						dcContrast_weboso22.chroma_gain_en, \
						dcContrast_weboso22.chroma_cb_gain1,dcContrast_weboso22.chroma_cb_gain2,\
						dcContrast_weboso22.chroma_cr_gain1,dcContrast_weboso22.chroma_cr_gain2,\
						dcContrast_weboso22.chroma_alpha1,dcContrast_weboso22.chroma_alpha2,\
						dcContrast_weboso22.dtm_hue_gain, dcContrast_weboso22.dtm_sat_gain);
					dcData.pst_chip_data = (unsigned char *)&dcContrast_weboso22;
					ret = vpq_hwrap_setdynamiccontrast_weboso22(&dcData);
					if (ret)
					{
						PE_PRINT_ERROR("vpq_hwrap_setdynamiccontrast: error(%d)\n", ret);
					}
				}
				if (!ret)
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &dcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(pqData.version == 0x30) //webos6.0- o20e60
			{
				if (copy_from_user(&dcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(&dcContrast_webos60, (void __user *)dcData.pst_chip_data, sizeof(vpq_hwrap_dc_dynamic_webos60_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				else
				{
					PE_PRINT_DCM("[%s.%d] dse ctrl version:%d\n"\
						" v4l2 set: chroma_gain_en:%d\n"\
						"chroma_cb_gain1:%d,chroma_cb_gain2:%d,chroma_cr_gain1:%d,chroma_cr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
						"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
						__F__, __L__,\
						pqData.version, \
						dcContrast_webos60.chroma_gain_en, \
						dcContrast_webos60.chroma_cb_gain1,dcContrast_webos60.chroma_cb_gain2,\
						dcContrast_webos60.chroma_cr_gain1,dcContrast_webos60.chroma_cr_gain2,\
						dcContrast_webos60.chroma_alpha1,dcContrast_webos60.chroma_alpha2,\
						dcContrast_webos60.dtm_hue_gain, dcContrast_webos60.dtm_sat_gain);
					dcData.pst_chip_data = (unsigned char *)&dcContrast_webos60;
					ret = vpq_hwrap_setdynamiccontrast_webos60(&dcData);
					if (ret)
					{
						PE_PRINT_ERROR("vpq_hwrap_setdynamiccontrast: error(%d)\n", ret);
					}
				}
				if (!ret)
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &dcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(pqData.version == 0x1)
			{
				if (copy_from_user(&dcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				drc_param.win_id = LX_PE_WIN_0;

				ret = PE_DCM_GetDceDrcMode(&drc_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_GetDceDrcMode: error(%d)\n", ret);
					break;
				}
				drc_param.dc_mode = (UINT32)dcData.uDcVal;
				drc_param.picture_mode = 4;
				PE_PRINT_DCM("PE_DCM_GetDceDrcMode: win_id = %d, dc_mode = %d, picture_mode = %d\n",\
					drc_param.win_id, drc_param.dc_mode, drc_param.picture_mode);

				ret = PE_DCM_SetDceDrcMode(&drc_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceDrcMode: error(%d)\n", ret);
				}
				if (!ret)
				{
					memcpy(&dcContrast_webos60, &dcContrast, sizeof(vpq_hwrap_dc_dynamic_t));
					dcData.pst_chip_data = (unsigned char *)&dcContrast_webos60;
					if (v4l2_vpq_pe_save_param(ctrl->id, &dcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(pqData.version == 0x2) //wegos5.0- o20, e60
			{
				if (copy_from_user(&dcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(&dcContrast, (void __user *)dcData.pst_chip_data, sizeof(vpq_hwrap_dc_dynamic_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				else
				{
					PE_PRINT_DCM("[%s.%d] dse ctrl version:%d\n"\
						" v4l2 set: chroma_gain_en:%d\n"\
						"dce_chr_gain1:%d,dce_chr_gain2:%d,dce_chr_alpha1:%d,dce_chr_alpha2:%d\n"\
						"dtm_hue_gain:%d,dtm_sat_gain: %d\n", \
						__F__, __L__,\
						pqData.version, \
						dcContrast.chroma_gain_en, \
						dcContrast.chroma_chr_gain1,dcContrast.chroma_chr_gain2,dcContrast.chroma_chr_alpha1,dcContrast.chroma_chr_alpha2,\
						dcContrast.dtm_hue_gain, dcContrast.dtm_sat_gain);
					dcData.pst_chip_data = (unsigned char *)&dcContrast;
					ret = vpq_hwrap_setdynamiccontrast(&dcData);
					if (ret)
					{
						PE_PRINT_ERROR("vpq_hwrap_setdynamiccontrast: error(%d)\n", ret);
					}
				}
				if (!ret)
				{
					memcpy(&dcContrast_webos60, &dcContrast, sizeof(vpq_hwrap_dc_dynamic_t));
					dcData.pst_chip_data = (unsigned char *)&dcContrast_webos60;
					if (v4l2_vpq_pe_save_param(ctrl->id, &dcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		{
			#if 1
			ret = vpq_set_dynamic_contrast_lut(&pqData, ctrl);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_set_dynamic_contrast_lut: error(%d)\n", ret);
			}
			#else 
			/*version
			0x0:only for pioneer
			0x1, 0x2: old version before e60
			0x30:webos6.0 e60,o20, 
			0x40:webos7.0 o22, m23
			0x60:webos24 initial o24
			0x61:webos24 MR o24
			*/
			LX_PE_DCM_DCE_LUT_T param;
			LX_PE_DCM_DRC_MODE_T drc_param;
			LX_PE_DCM_DTM_LUT_T dtm_param;
			LX_PE_DCM_DCE_LUT1_T dclut_param;
			LX_PE_DCM_DCE_LUT2_T dclut2_param;
			LX_PE_SHP_ELLIPS_LUT_T shp_ellips_param;
			UINT32 detected = 0;
			static UINT32 cnt_detected=0;
			//UINT32 addr0=0, val0;
			UINT16 *pDtmLut;
			signed int sDcBypassLut[PE_KWRAP_DCM_LUT_STEP] =
				{ 0, 64, 122, 181, 239, 298, 356, 415, 473, 532, 590, 649, 707, 766, 824, 882 };
			//signed int sLumaLUTxy[PE_KWRAP_DCM_LUT_STEP * 2] = { 0, };
			#if 0
			UINT32 sDtmbypassLut[33]=
			{0x000000, 0x020020, 0x040040, 0x060060, 0x080080, 0x0A00A0, 0x0C00C0, 0x0E00E0, 0x100100, 0x120120, \
			0x140140, 0x160160, 0x180180, 0x1A01A0, 0x1C01C0, 0x1E01E0, 0x200200, 0x21F21F, 0x23F23F, 0x25F25F, \
			0x27F27F, 0x29F29F, 0x2BF2BF, 0x2DF2DF, 0x2FF2FF, 0x31F31F, 0x33F33F, 0x35F35F, 0x37F37F, 0x3AC3AC, \
			0x3BF3BF, 0x3DF3DF, 0x3FF3FF};
			#endif
			__attribute__((unused)) UINT32 sDtmbypassLut[33] = {\
			   0,  64, 122, 181, 239, 298, 356, 415, 473, \
			 532, 590, 649, 707, 766, 824, 882, 940,1023, \
			1023,1023,1023,1023,1023,1023,1023,1023,1023, \
			1023,1023,1023,1023,1023,1023};
			#if 0
			UINT16 sDtmbNGLut[66]=
			{0x0000, 0x0040, 0x0080, 0x00C0, 0x0100, 0x0140, 0x0180, 0x01C0, 0x0200, 0x0240, \
			0x0280, 0x02C0, 0x0300, 0x0340, 0x0380, 0x03C0, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
			0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
			0x03FF, 0x03FF, 0x03FF, 0x0001, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
			0x03FF, 0x03FF, 0x03FF, 0x0303, 0x0349, 0x037b, 0x0399, 0x03B1, 0x03Cb, 0x03FF, \
			0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
			0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF};
			#endif
			UINT8 i = 0, j = 0;
			UINT32 x_data = 0, y_data = 0;
			BOOLEAN drc_bypass = TRUE;
			//UINT32 *pLUT;
			__attribute__((unused)) vpq_hwrap_dynamic_lut_t stDcmLut;
			__attribute__((unused)) vpq_hwrap_dynamic_lut_webos60_t stDcmLut_webos60;
			__attribute__((unused)) vpq_hwrap_dynamic_lut_pioneer_t stDcmLut_pioneer;
			__attribute__((unused)) vpq_hwrap_dynamic_lut_o24_t stDcmLut_webos24;
			__attribute__((unused)) vpq_hwrap_dynamic_lut_o24_v2_t stDcmLut_webos24_v2;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT- V4L2_CID_EXT_VPQ_BASE])
				break;
			PE_PRINT_DCM_LUT("[%s.%d]version = %d, wid = %d, length = %d\n", \
				__F__, __L__,pqData.version,pqData.wid,pqData.length);
			/* DCE LUT S*/
			if(pqData.version == 0x61)
			{
				if (copy_from_user(&stDcmLut_webos24_v2, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				dclut2_param.win_id = LX_PE_WIN_0;
				PE_PRINT_DCM_LUT("DC LUT set: n");
				for (i = 0; i < 32; i++)
				{
					for (j =0 ; j < 4; j++)
					{
						x_data = (UINT32)stDcmLut_webos24_v2.sLumaLutX[j][i];
						y_data = (UINT32)stDcmLut_webos24_v2.sLumaLutY[j][i];
						if (x_data != y_data)
						{
							drc_bypass = FALSE;
						}
						
						if ((pqData.wid == 0 || pqData.wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
						{
							y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
						}
						dclut2_param.lumalut_x[j][i] = x_data;
						dclut2_param.lumalut_y[j][i] = y_data;
					}
					PE_PRINT_DCM_LUT("data[%2d] =[0] [%4d] [%4d] |[1] [%4d] [%4d] |[2] [%4d] [%4d] |[3] [%4d] [%4d]\n", \
						i, dclut2_param.lumalut_x[0][i], dclut2_param.lumalut_y[0][i], dclut2_param.lumalut_x[1][i], dclut2_param.lumalut_y[1][i],\
						 dclut2_param.lumalut_x[2][i], dclut2_param.lumalut_y[2][i],dclut2_param.lumalut_x[3][i], dclut2_param.lumalut_y[3][i]);
				}

				if (PE_KDRV_VER_O26) // TVPQCMR-6351, TVPQCMR-6327
					drc_bypass = FALSE;
				memcpy(dclut2_param.chroma_face_alpha_lut1_x,stDcmLut_webos24_v2.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
				PE_PRINT_DCM_LUT(\
					"lut1_x: %d, %d, %d, %d\n" \
					"lut1_y: %d, %d, %d, %d\n" \
					"lut2_x: %d, %d, %d, %d\n" \
					"lut2_y: %d, %d, %d, %d\n", \
					stDcmLut_webos24_v2.chroma_face_alpha_lut1_x[0],stDcmLut_webos24_v2.chroma_face_alpha_lut1_x[1],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut1_x[2],stDcmLut_webos24_v2.chroma_face_alpha_lut1_x[3],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut1_y[0],stDcmLut_webos24_v2.chroma_face_alpha_lut1_y[1],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut1_y[2],stDcmLut_webos24_v2.chroma_face_alpha_lut1_y[3],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut2_x[0],stDcmLut_webos24_v2.chroma_face_alpha_lut2_x[1],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut2_x[2],stDcmLut_webos24_v2.chroma_face_alpha_lut2_x[3],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut2_y[0],stDcmLut_webos24_v2.chroma_face_alpha_lut2_y[1],\
					stDcmLut_webos24_v2.chroma_face_alpha_lut2_y[2],stDcmLut_webos24_v2.chroma_face_alpha_lut2_y[3]);
				if(pqData.wid == 0 || pqData.wid == 1) //o24, o22, e60, o20 only
				{
					ret = PE_DCM_SetDceLut2(&dclut2_param);
					if (ret)
					{
						PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
						break;
					}
				}
				shp_ellips_param.win_id = pqData.wid;
				memcpy(shp_ellips_param.shp_luma_ylut_2k,stDcmLut_webos24_v2.shp_luma_ylut_2k, sizeof(UINT8)*16);
				memcpy(shp_ellips_param.shp_luma_ylut_vsd,stDcmLut_webos24_v2.shp_luma_ylut_vsd, sizeof(UINT8)*16);
				ret = PE_SHP_SetEllipsCtrl(&shp_ellips_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_SHP_SetEllipsCtrl: error(%d)\n", ret);
					break;
				}
				PE_PRINT_DCM_LUT(\
				"Ellips Lut set: n"\
				"shp_luma_ylut_2k  0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"shp_luma_ylut_2k  8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"shp_luma_ylut_vsd 0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
				"shp_luma_ylut_vsd 8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
				stDcmLut_webos24_v2.shp_luma_ylut_2k[0],stDcmLut_webos24_v2.shp_luma_ylut_2k[1],stDcmLut_webos24_v2.shp_luma_ylut_2k[2],stDcmLut_webos24_v2.shp_luma_ylut_2k[3],\
				stDcmLut_webos24_v2.shp_luma_ylut_2k[4],stDcmLut_webos24_v2.shp_luma_ylut_2k[5],stDcmLut_webos24_v2.shp_luma_ylut_2k[6],stDcmLut_webos24_v2.shp_luma_ylut_2k[7],\
				stDcmLut_webos24_v2.shp_luma_ylut_2k[8],stDcmLut_webos24_v2.shp_luma_ylut_2k[9],stDcmLut_webos24_v2.shp_luma_ylut_2k[10],stDcmLut_webos24_v2.shp_luma_ylut_2k[11],\
				stDcmLut_webos24_v2.shp_luma_ylut_2k[12],stDcmLut_webos24_v2.shp_luma_ylut_2k[13],stDcmLut_webos24_v2.shp_luma_ylut_2k[14],stDcmLut_webos24_v2.shp_luma_ylut_2k[15],\
				stDcmLut_webos24_v2.shp_luma_ylut_vsd[0],stDcmLut_webos24_v2.shp_luma_ylut_vsd[1],stDcmLut_webos24_v2.shp_luma_ylut_vsd[2],stDcmLut_webos24_v2.shp_luma_ylut_vsd[3],\
				stDcmLut_webos24_v2.shp_luma_ylut_vsd[4],stDcmLut_webos24_v2.shp_luma_ylut_vsd[5],stDcmLut_webos24_v2.shp_luma_ylut_vsd[6],stDcmLut_webos24_v2.shp_luma_ylut_vsd[7],\
				stDcmLut_webos24_v2.shp_luma_ylut_vsd[8],stDcmLut_webos24_v2.shp_luma_ylut_vsd[9],stDcmLut_webos24_v2.shp_luma_ylut_vsd[10],stDcmLut_webos24_v2.shp_luma_ylut_vsd[11],\
				stDcmLut_webos24_v2.shp_luma_ylut_vsd[12],stDcmLut_webos24_v2.shp_luma_ylut_vsd[13],stDcmLut_webos24_v2.shp_luma_ylut_vsd[14],stDcmLut_webos24_v2.shp_luma_ylut_vsd[15]);
			}
			else if(pqData.version == 0x60 || pqData.version == 0x40 || pqData.version == 0x30)//0x30:webos6.0 e60,o20, 0x40:webos7.0
			{
				if (copy_from_user(&stDcmLut_webos24, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)//o24  
				{
					dclut2_param.win_id = LX_PE_WIN_0;
					PE_PRINT_DCM_LUT("DC LUT set: n");
					for (i = 0; i < 32; i++)
					{
						x_data = (UINT32)stDcmLut_webos24.sLumaLutX[i];
						y_data = (UINT32)stDcmLut_webos24.sLumaLutY[i];
						if (x_data != y_data)
						{
							drc_bypass = FALSE;
						}
						
						if ((pqData.wid == 0 || pqData.wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
						{
							y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
						}
						dclut2_param.lumalut_x[0][i] = dclut2_param.lumalut_x[1][i] = dclut2_param.lumalut_x[2][i] =dclut2_param.lumalut_x[3][i] = x_data;
						dclut2_param.lumalut_y[0][i] = dclut2_param.lumalut_y[1][i] = dclut2_param.lumalut_y[2][i] =dclut2_param.lumalut_y[3][i] = y_data;
						PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
							i, dclut2_param.lumalut_x[0][i], dclut2_param.lumalut_y[0][i]);
					}

					memcpy(dclut2_param.chroma_face_alpha_lut1_x,stDcmLut_webos24.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
					PE_PRINT_DCM_LUT(\
						"lut1_x: %d, %d, %d, %d\n" \
						"lut1_y: %d, %d, %d, %d\n" \
						"lut2_x: %d, %d, %d, %d\n" \
						"lut2_y: %d, %d, %d, %d\n", \
						stDcmLut_webos24.chroma_face_alpha_lut1_x[0],stDcmLut_webos24.chroma_face_alpha_lut1_x[1],\
						stDcmLut_webos24.chroma_face_alpha_lut1_x[2],stDcmLut_webos24.chroma_face_alpha_lut1_x[3],\
						stDcmLut_webos24.chroma_face_alpha_lut1_y[0],stDcmLut_webos24.chroma_face_alpha_lut1_y[1],\
						stDcmLut_webos24.chroma_face_alpha_lut1_y[2],stDcmLut_webos24.chroma_face_alpha_lut1_y[3],\
						stDcmLut_webos24.chroma_face_alpha_lut2_x[0],stDcmLut_webos24.chroma_face_alpha_lut2_x[1],\
						stDcmLut_webos24.chroma_face_alpha_lut2_x[2],stDcmLut_webos24.chroma_face_alpha_lut2_x[3],\
						stDcmLut_webos24.chroma_face_alpha_lut2_y[0],stDcmLut_webos24.chroma_face_alpha_lut2_y[1],\
						stDcmLut_webos24.chroma_face_alpha_lut2_y[2],stDcmLut_webos24.chroma_face_alpha_lut2_y[3]);
					if(pqData.wid == 0 || pqData.wid == 1) //o24, o22, e60, o20 only
					{
						ret = PE_DCM_SetDceLut2(&dclut2_param);
						if (ret)
						{
							PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
							break;
						}
					}
					shp_ellips_param.win_id = pqData.wid;
					memcpy(shp_ellips_param.shp_luma_ylut_2k,stDcmLut_webos24.shp_luma_ylut_2k, sizeof(UINT8)*16);
					memcpy(shp_ellips_param.shp_luma_ylut_vsd,stDcmLut_webos24.shp_luma_ylut_vsd, sizeof(UINT8)*16);
					ret = PE_SHP_SetEllipsCtrl(&shp_ellips_param);
					if (ret)
					{
						PE_PRINT_ERROR("PE_SHP_SetEllipsCtrl: error(%d)\n", ret);
						break;
					}
					PE_PRINT_DCM_LUT(\
					"Ellips Lut set: n"\
					"shp_luma_ylut_2k  0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"shp_luma_ylut_2k  8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"shp_luma_ylut_vsd 0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"shp_luma_ylut_vsd 8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
					stDcmLut_webos24.shp_luma_ylut_2k[0],stDcmLut_webos24.shp_luma_ylut_2k[1],stDcmLut_webos24.shp_luma_ylut_2k[2],stDcmLut_webos24.shp_luma_ylut_2k[3],\
					stDcmLut_webos24.shp_luma_ylut_2k[4],stDcmLut_webos24.shp_luma_ylut_2k[5],stDcmLut_webos24.shp_luma_ylut_2k[6],stDcmLut_webos24.shp_luma_ylut_2k[7],\
					stDcmLut_webos24.shp_luma_ylut_2k[8],stDcmLut_webos24.shp_luma_ylut_2k[9],stDcmLut_webos24.shp_luma_ylut_2k[10],stDcmLut_webos24.shp_luma_ylut_2k[11],\
					stDcmLut_webos24.shp_luma_ylut_2k[12],stDcmLut_webos24.shp_luma_ylut_2k[13],stDcmLut_webos24.shp_luma_ylut_2k[14],stDcmLut_webos24.shp_luma_ylut_2k[15],\
					stDcmLut_webos24.shp_luma_ylut_vsd[0],stDcmLut_webos24.shp_luma_ylut_vsd[1],stDcmLut_webos24.shp_luma_ylut_vsd[2],stDcmLut_webos24.shp_luma_ylut_vsd[3],\
					stDcmLut_webos24.shp_luma_ylut_vsd[4],stDcmLut_webos24.shp_luma_ylut_vsd[5],stDcmLut_webos24.shp_luma_ylut_vsd[6],stDcmLut_webos24.shp_luma_ylut_vsd[7],\
					stDcmLut_webos24.shp_luma_ylut_vsd[8],stDcmLut_webos24.shp_luma_ylut_vsd[9],stDcmLut_webos24.shp_luma_ylut_vsd[10],stDcmLut_webos24.shp_luma_ylut_vsd[11],\
					stDcmLut_webos24.shp_luma_ylut_vsd[12],stDcmLut_webos24.shp_luma_ylut_vsd[13],stDcmLut_webos24.shp_luma_ylut_vsd[14],stDcmLut_webos24.shp_luma_ylut_vsd[15]);
					
					if(pqData.wid == 0xF0 || pqData.wid == 0xF1) //o24+F22
					{
						ret = PE_DCM_SetDceLut3(&dclut2_param);
						if (ret)
						{
							PE_PRINT_ERROR("PE_DCM_SetDceLut3: error(%d)\n", ret);
							break;
						}
					}
				}
				else
				{
					dclut_param.win_id = LX_PE_WIN_0;
					PE_PRINT_DCM_LUT("DC LUT set: n");
					for (i = 0; i < 32; i++)
					{
						x_data = (UINT32)stDcmLut_webos24.sLumaLutX[i];
						y_data = (UINT32)stDcmLut_webos24.sLumaLutY[i];
						if (x_data != y_data)
						{
							drc_bypass = FALSE;
						}
						
						if ((pqData.wid == 0 || pqData.wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)//e60 only model
						{
							y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
						}
						dclut_param.lumalut_x[i] = x_data;
						dclut_param.lumalut_y[i] = y_data;
						PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
							i, dclut_param.lumalut_x[i], dclut_param.lumalut_y[i]);
					}
					memcpy(dclut_param.chroma_face_alpha_lut1_x,stDcmLut_webos24.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
					
					PE_PRINT_DCM_LUT(\
						"lut1_x: %d, %d, %d, %d\n" \
						"lut1_y: %d, %d, %d, %d\n" \
						"lut2_x: %d, %d, %d, %d\n" \
						"lut2_y: %d, %d, %d, %d\n", \
						stDcmLut_webos24.chroma_face_alpha_lut1_x[0],stDcmLut_webos24.chroma_face_alpha_lut1_x[1],\
						stDcmLut_webos24.chroma_face_alpha_lut1_x[2],stDcmLut_webos24.chroma_face_alpha_lut1_x[3],\
						stDcmLut_webos24.chroma_face_alpha_lut1_y[0],stDcmLut_webos24.chroma_face_alpha_lut1_y[1],\
						stDcmLut_webos24.chroma_face_alpha_lut1_y[2],stDcmLut_webos24.chroma_face_alpha_lut1_y[3],\
						stDcmLut_webos24.chroma_face_alpha_lut2_x[0],stDcmLut_webos24.chroma_face_alpha_lut2_x[1],\
						stDcmLut_webos24.chroma_face_alpha_lut2_x[2],stDcmLut_webos24.chroma_face_alpha_lut2_x[3],\
						stDcmLut_webos24.chroma_face_alpha_lut2_y[0],stDcmLut_webos24.chroma_face_alpha_lut2_y[1],\
						stDcmLut_webos24.chroma_face_alpha_lut2_y[2],stDcmLut_webos24.chroma_face_alpha_lut2_y[3]);
					if(pqData.wid == 0 || pqData.wid == 1) //o24, o22, e60, o20 only
					{
						ret = PE_DCM_SetDceLut2(&dclut_param);
						if (ret)
						{
							PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
							break;
						}
					}
					else if(pqData.wid == 2 || pqData.wid == 3) //o22+f22, e60+f20
					{
						ret = PE_DCM_SetDceLut3(&dclut_param);
						if (ret)
						{
							PE_PRINT_ERROR("PE_DCM_SetDceLut3: error(%d)\n", ret);
							break;
						}
					}
				}

			}
			else if(pqData.version == 0x2 ||pqData.version == 0x1)
			{
				if (copy_from_user(&stDcmLut, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				param.win_id = LX_PE_WIN_0;
				param.size = PE_KWRAP_DCM_LUT_STEP;
				param.data = (UINT32 *)OS_Malloc(sizeof(UINT32) * param.size);
				if (!param.data)
				{
					PE_PRINT_ERROR("OS_Malloc error.\n");
					break;
				}
				for (i = 0; i < PE_KWRAP_DCM_LUT_STEP; i++)
				{
					x_data = (UINT32)stDcmLut.sLumaLutX[i]<<16;
					y_data = (UINT32)stDcmLut.sLumaLutY[i];
					if (sDcBypassLut[i] != y_data)
					{
						drc_bypass = FALSE;
					}
					if (y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
					{
						y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
					}
					param.data[i] = x_data + y_data;
					PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
						i, (param.data[i] >> 16) & 0xffff, param.data[i] & 0xffff);
				}
				ret = PE_DCM_SetDceLut(&param);
				if(param.data) OS_Free(param.data);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut: error(%d)\n", ret);
					break;
				}
			}
			else if(pqData.version == 0x0)//0x0:only for pioneer
			{
				if (copy_from_user(&stDcmLut_pioneer, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				dclut_param.win_id = LX_PE_WIN_0;
				for (i = 0; i < 32; i++)
				{
					x_data = (UINT32)stDcmLut_pioneer.sLumaLutX[i];
					y_data = (UINT32)stDcmLut_pioneer.sLumaLutY[i];
					if (x_data != y_data)
					{
						drc_bypass = FALSE;
					}
					
					if ((pqData.wid == 0 || pqData.wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)//e60 only model
					{
						y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
					}
					dclut_param.lumalut_x[i] = x_data;
					dclut_param.lumalut_y[i] = y_data;
					PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
						i, dclut_param.lumalut_x[i], dclut_param.lumalut_y[i]);
				}
				memcpy(dclut_param.chroma_face_alpha_lut1_x,stDcmLut_pioneer.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
				
				PE_PRINT_DCM_LUT(\
					"lut1_x: %d, %d, %d, %d\n" \
					"lut1_y: %d, %d, %d, %d\n" \
					"lut2_x: %d, %d, %d, %d\n" \
					"lut2_y: %d, %d, %d, %d\n", \
					stDcmLut_pioneer.chroma_face_alpha_lut1_x[0],stDcmLut_pioneer.chroma_face_alpha_lut1_x[1],\
					stDcmLut_pioneer.chroma_face_alpha_lut1_x[2],stDcmLut_pioneer.chroma_face_alpha_lut1_x[3],\
					stDcmLut_pioneer.chroma_face_alpha_lut1_y[0],stDcmLut_pioneer.chroma_face_alpha_lut1_y[1],\
					stDcmLut_pioneer.chroma_face_alpha_lut1_y[2],stDcmLut_pioneer.chroma_face_alpha_lut1_y[3],\
					stDcmLut_pioneer.chroma_face_alpha_lut2_x[0],stDcmLut_pioneer.chroma_face_alpha_lut2_x[1],\
					stDcmLut_pioneer.chroma_face_alpha_lut2_x[2],stDcmLut_pioneer.chroma_face_alpha_lut2_x[3],\
					stDcmLut_pioneer.chroma_face_alpha_lut2_y[0],stDcmLut_pioneer.chroma_face_alpha_lut2_y[1],\
					stDcmLut_pioneer.chroma_face_alpha_lut2_y[2],stDcmLut_pioneer.chroma_face_alpha_lut2_y[3]);
				ret = PE_DCM_SetDceLut2(&dclut_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
					break;
				}
			}
			else
			{
				if (copy_from_user(&stDcmLut, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
			}
			/* DCE LUT E*/
			if(pqData.version == 0x2 || pqData.version == 0x30 || pqData.version == 0x40|| pqData.version == 0x60|| pqData.version == 0x61) //0x2:webos5.0 0x30:webos6.0 e60,o20, 0x40:webos7.0
			{
				/* DRC S */
				drc_param.win_id = LX_PE_WIN_0;
				ret = PE_DCM_GetDceDrcMode(&drc_param);
				if (PE_KDRV_VER_O20)
                {
                        ret = KWRAP_PE_GetCurDceDrcMode((void *)&drc_param);
                }
                else
                {
                        ret = PE_DCM_GetDceDrcMode(&drc_param);
                }
                if (ret)
                {
                        PE_PRINT_ERROR("PE_DCM_GetDceDrcMode: error(%d)\n", ret);
                        break;
                }
				drc_param.dc_bypass = drc_bypass ? 1 : 0;
				drc_param.db_type = LX_PE_DRC_DC_BYPASS;
				if (PE_KDRV_VER_O20)
				{
					ret = KWRAP_PE_SetDceDrcMode((void *)&drc_param);
				}
				else
				{
					ret = PE_DCM_SetDceDrcMode(&drc_param);
				}
                if (ret)
                {
                        PE_PRINT_ERROR("PE_DCM_SetDceDrcMode: error(%d)\n", ret);
                        break;
                }
				/* DRC E */
				/* DTM S */
				dtm_param.win_id = LX_PE_WIN_0;
				dtm_param.size = 33;
				dtm_param.data = (UINT32 *)OS_Malloc(sizeof(UINT32) * dtm_param.size);
				detected =0;
				if (!dtm_param.data)
				{
					PE_PRINT_ERROR("OS_Malloc error.\n");
					break;
				}
				if(pqData.version == 0x2)
					pDtmLut = (UINT16*)stDcmLut.dtm_lut;
				else if (pqData.version == 0x61)
					pDtmLut = (UINT16*)stDcmLut_webos24_v2.dtm_lut;
				else 
					pDtmLut = (UINT16*)stDcmLut_webos24.dtm_lut;
				#if 0
				if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT- V4L2_CID_EXT_VPQ_BASE])
				{
					pDtmLut = sDtmbNGLut;
				}
				#endif
				for (i = 0; i < 33 ; i++)
				{
					x_data = (UINT32)(pDtmLut[i]<<16);
					y_data = (UINT32)pDtmLut[i + 33];
					if(i ==0 &&(y_data != 0x0 || x_data != 0x0))
					{
						detected =1;
					}
					if(pDtmLut[i + 33] >= pDtmLut[i])// y >= x case
					{
						if ((pDtmLut[i + 33] - pDtmLut[i]) > 500)
						{
							detected =1;
						}
					}
					else // y < x case
					{
						if ((pDtmLut[i] - pDtmLut[i + 33]) > 500)
						{
							detected =1;
						}
					}
					if (y_data > 0x3ff)
					{
						y_data = 0x3ff;
					}
					dtm_param.data[i] = x_data + y_data;
				}
				if (detected ==1)
				{
					cnt_detected += 1;
					PE_PRINT_NOTI("dtm detected!!!!: %d dtm cnt : %d, x0~9:%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d \n"\
									"y0~9:%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d \n",\
					detected, cnt_detected,\
					pDtmLut[0] & 0xffff,pDtmLut[1] & 0xffff,pDtmLut[2] & 0xffff,\
					pDtmLut[3] & 0xffff,pDtmLut[4] & 0xffff,pDtmLut[5] & 0xffff,\
					pDtmLut[6] & 0xffff,pDtmLut[7] & 0xffff,pDtmLut[8] & 0xffff,\
					pDtmLut[9] & 0xffff,\
					pDtmLut[0+ 33] & 0xffff,pDtmLut[1+ 33] & 0xffff,pDtmLut[2+ 33] & 0xffff,\
					pDtmLut[3+ 33] & 0xffff,pDtmLut[4+ 33] & 0xffff,pDtmLut[5+ 33] & 0xffff,\
					pDtmLut[6+ 33] & 0xffff,pDtmLut[7+ 33] & 0xffff,pDtmLut[8+ 33] & 0xffff,\
					pDtmLut[9+ 33] & 0xffff);
					#if 0
					//pattern on
					addr0 = 0xC9014448;
					val0 = 0x01000000;
					ret = SYS_IO_WriteRegArray(addr0,4,&val0);
					//dummy count
					addr0 = 0xC901228C;
					val0 = cnt_detected;
					ret = SYS_IO_WriteRegArray(addr0,4,&val0);
					#endif
					//break;
				}
				PE_PRINT_DTM("dtm lut\n"\
								"DTM X[0~15] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
										"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n"\
							   "DTM Y[0~15] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
										"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n",\
				(dtm_param.data[0] >> 16) & 0xffff,(dtm_param.data[1] >> 16) & 0xffff,(dtm_param.data[2] >> 16) & 0xffff,\
				(dtm_param.data[3] >> 16) & 0xffff,(dtm_param.data[4] >> 16) & 0xffff,(dtm_param.data[5] >> 16) & 0xffff,\
				(dtm_param.data[6] >> 16) & 0xffff,(dtm_param.data[7] >> 16) & 0xffff,(dtm_param.data[8] >> 16) & 0xffff,\
				(dtm_param.data[9] >> 16) & 0xffff,(dtm_param.data[10] >> 16) & 0xffff,(dtm_param.data[11] >> 16) & 0xffff,\
				(dtm_param.data[12] >> 16) & 0xffff,(dtm_param.data[13] >> 16) & 0xffff,(dtm_param.data[14] >> 16) & 0xffff,\
				(dtm_param.data[15] >> 16) & 0xffff,\
				dtm_param.data[0] & 0xffff,dtm_param.data[1] & 0xffff,dtm_param.data[2] & 0xffff,\
				dtm_param.data[3] & 0xffff,dtm_param.data[4] & 0xffff,dtm_param.data[5] & 0xffff,\
				dtm_param.data[6] & 0xffff,dtm_param.data[7] & 0xffff,dtm_param.data[8] & 0xffff,\
				dtm_param.data[9] & 0xffff,dtm_param.data[10] & 0xffff,dtm_param.data[11] & 0xffff,\
				dtm_param.data[12] & 0xffff,dtm_param.data[13] & 0xffff,dtm_param.data[14] & 0xffff,\
				dtm_param.data[15] & 0xffff);
				PE_PRINT_DTM("\nDTM X[16~32] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
										"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n"\
							   "DTM Y[16~32] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
										"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n",\
				(dtm_param.data[16] >> 16) & 0xffff,(dtm_param.data[17] >> 16) & 0xffff,(dtm_param.data[18] >> 16) & 0xffff,\
				(dtm_param.data[19] >> 16) & 0xffff,(dtm_param.data[20] >> 16) & 0xffff,(dtm_param.data[21] >> 16) & 0xffff,\
				(dtm_param.data[22] >> 16) & 0xffff,(dtm_param.data[23] >> 16) & 0xffff,(dtm_param.data[24] >> 16) & 0xffff,\
				(dtm_param.data[25] >> 16) & 0xffff,(dtm_param.data[26] >> 16) & 0xffff,(dtm_param.data[27] >> 16) & 0xffff,\
				(dtm_param.data[28] >> 16) & 0xffff,(dtm_param.data[29] >> 16) & 0xffff,(dtm_param.data[30] >> 16) & 0xffff,\
				(dtm_param.data[31] >> 16) & 0xffff,(dtm_param.data[32] >> 16) & 0xffff,\
				dtm_param.data[16] & 0xffff,dtm_param.data[17] & 0xffff,dtm_param.data[18] & 0xffff,\
				dtm_param.data[19] & 0xffff,dtm_param.data[20] & 0xffff,dtm_param.data[21] & 0xffff,\
				dtm_param.data[22] & 0xffff,dtm_param.data[23] & 0xffff,dtm_param.data[24] & 0xffff,\
				dtm_param.data[25] & 0xffff,dtm_param.data[26] & 0xffff,dtm_param.data[27] & 0xffff,\
				dtm_param.data[28] & 0xffff,dtm_param.data[29] & 0xffff,dtm_param.data[30] & 0xffff,\
				dtm_param.data[31] & 0xffff,dtm_param.data[32] & 0xffff);
				ret = PE_DCM_SetDtmLut(&dtm_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDtmLut: error(%d)\n", ret);
					break;
				}
				if(dtm_param.data) OS_Free(dtm_param.data);
				/* DTM E */
			}
			if (ret)
			{
				PE_PRINT_ERROR("PE_DCM_SetDtmLut: error(%d)\n", ret);
			}
			else
			{
				if(pqData.version == 0x2 || pqData.version == 0x1 )
				{
					memcpy(&stDcmLut_webos24, &stDcmLut, sizeof(vpq_hwrap_dynamic_lut_t));
				}
				if(pqData.version == 0x61)
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stDcmLut_webos24_v2, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stDcmLut_webos24, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			#endif
		} break;
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		{
			struct v4l2_ext_vpq_sharpness_data shpData;
			vpq_hwrap_shp_t stShpData;
			vpq_hwrap_chip_shp_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_shp_o20_t __attribute__((unused)) *pstChipData_o20 = NULL;
			vpq_hwrap_chip_shp_e60_t __attribute__((unused)) *pstChipData_e60 = NULL;
			vpq_hwrap_chip_shp_o22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_shp_o22n2_t __attribute__((unused)) *pstChipData_o22n2 = NULL;
			vpq_hwrap_chip_shp_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_shp_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_SHARPNESS- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&shpData, 0x00, sizeof(shpData));
			memset(&stShpData, 0x00, sizeof(stShpData));

			if (copy_from_user(&shpData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			memcpy(stShpData.ui_value, shpData.ui_value, sizeof(stShpData.ui_value));
			PQ_PRINT_SHP("set: wid %d, shpData.pst_chip_data 0x%p, ver 0x%02X \n",pqData.wid, shpData.pst_chip_data, pqData.version);
			if(pqData.version == 0x80) // O26
			{
				if (shpData.pst_chip_data)
				{
					if(PE_KDRV_VER_O26)
					{
						if (!(pstChipData_o26 = OS_Malloc(sizeof(*pstChipData_o26))))
						{
							PE_PRINT_ERROR("OS_Malloc error\n");
							return -ENOMEM;
						}
						if (copy_from_user(pstChipData_o26, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_o26)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
							return -ENOMEM;
						}
						else
						{
							stShpData.pst_chip_data = (unsigned char *)pstChipData_o26;
							shpData.pst_chip_data = (unsigned char *)pstChipData_o26;
						}
					}
				}
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setsharpness error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o26)
				{
					OS_Free(pstChipData_o26);
				}
			}
			else if(pqData.version == 0x60) // O22n2, O24
			{
				if (shpData.pst_chip_data)
				{
					if(PE_KDRV_VER_O22) //o22n2
					{
						if (!(pstChipData_o22n2 = OS_Malloc(sizeof(*pstChipData_o22n2))))
						{
							PE_PRINT_ERROR("OS_Malloc error\n");
							return -ENOMEM;
						}
						if (copy_from_user(pstChipData_o22n2, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_o22n2)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
							return -ENOMEM;
						}
						else
						{
							stShpData.pst_chip_data = (unsigned char *)pstChipData_o22n2;
							shpData.pst_chip_data = (unsigned char *)pstChipData_o22n2;
						}
					}
					else if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
					{
						if (!(pstChipData_o24 = OS_Malloc(sizeof(*pstChipData_o24))))
						{
							PE_PRINT_ERROR("OS_Malloc error\n");
							return -ENOMEM;
						}
						if (copy_from_user(pstChipData_o24, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_o24)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
							return -ENOMEM;
						}
						else
						{
							stShpData.pst_chip_data = (unsigned char *)pstChipData_o24;
							shpData.pst_chip_data = (unsigned char *)pstChipData_o24;
						}
					}
				}
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setsharpness error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o22n2)
				{
					OS_Free(pstChipData_o22n2);
				}
				if (pstChipData_o24)
				{
					OS_Free(pstChipData_o24);
				}
			}
			else if(pqData.version == 0x40) // O22, O22n, M23
			{
				if (shpData.pst_chip_data)
				{
					if (!(pstChipData_o22 = OS_Malloc(sizeof(*pstChipData_o22))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o22, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_o22)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stShpData.pst_chip_data = (unsigned char *)pstChipData_o22;
						shpData.pst_chip_data = (unsigned char *)pstChipData_o22;
					}
				}
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setsharpness error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o22)
				{
					OS_Free(pstChipData_o22);
				}
			}
			else if(PE_KDRV_VER_E60)
			{
				if (shpData.pst_chip_data)
				{
					if (!(pstChipData_e60 = OS_Malloc(sizeof(*pstChipData_e60))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_e60, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_e60)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stShpData.pst_chip_data = (unsigned char *)pstChipData_e60;
						shpData.pst_chip_data = (unsigned char *)pstChipData_e60;
					}
				}
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setsharpness error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_e60)
				{
					OS_Free(pstChipData_e60);
				}
			}
			else if(PE_KDRV_VER_O20)
			{
				if (shpData.pst_chip_data)
				{
					if (!(pstChipData_o20 = OS_Malloc(sizeof(*pstChipData_o20))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o20, (void __user *)shpData.pst_chip_data, sizeof(*pstChipData_o20)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stShpData.pst_chip_data = (unsigned char *)pstChipData_o20;
						shpData.pst_chip_data = (unsigned char *)pstChipData_o20;
					}
				}
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setsharpness error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o20)
				{
					OS_Free(pstChipData_o20);
				}
			}
			else if(pqData.version == 0x1) // temporally M23 for SOCTS version=1, chipdata=NULL case
			{
				PE_PRINT_SHP("set: uUi %d %d %d %d, stShpData 0x%p\n",
					stShpData.ui_value[0], stShpData.ui_value[1], stShpData.ui_value[2], stShpData.ui_value[3], stShpData.pst_chip_data);
				//ret = vpq_hwrap_setsharpness(&stShpData, (UINT32)pqData.wid );
				if (v4l2_vpq_pe_save_param(ctrl->id, &shpData, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
				if (pstChipData_o22)
				{
					OS_Free(pstChipData_o22);
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		{
			#if 0
			struct v4l2_ext_vpq_super_resolution_data srData;
			vpq_hwrap_sr_t stSrData;
			vpq_hwrap_chip_sr_t stChipData;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_SUPER_RESOLUTION- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&pqData, 0x00, sizeof(pqData));
			memset(&srData, 0x00, sizeof(srData));
			memset(&stSrData, 0x00, sizeof(stSrData));
			memset(&stChipData, 0x00, sizeof(stChipData));

			if (copy_from_user(&srData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			stSrData.wId = pqData.wid;
			stSrData.uUi = srData.ui_value;
			PE_PRINT_SHP("set: srData.pst_chip_data 0x%p\n", srData.pst_chip_data);
			if (srData.pst_chip_data)
			{
				if (copy_from_user(&stChipData, (void __user *)srData.pst_chip_data, sizeof(stChipData)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				else
				{
					stSrData.pChip = (vpq_hwrap_chip_sr_t *)&stChipData;
					srData.pst_chip_data = (unsigned char *)&stChipData;
				}
			}
			PE_PRINT_SHP("set: uUi %d, pChip 0x%p\n",
				stSrData.uUi, stSrData.pChip);
			ret = vpq_hwrap_setsuperresoulution(&stSrData);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setsuperresoulution error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &srData, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
			#endif
		} break;
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_noise_reduction_data nrData;
			vpq_hwrap_nr_t stNrData;
			vpq_hwrap_chip_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_nr_o20_f20_e60_o22_o24_t __attribute__((unused)) *pstChipData_o20_f20_e60_o22_o24 = NULL;
			vpq_hwrap_chip_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_NOISE_REDUCTION- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&nrData, 0x00, sizeof(nrData));
			memset(&stNrData, 0x00, sizeof(stNrData));

			if (copy_from_user(&nrData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			memcpy(stNrData.ui_value, nrData.ui_value, sizeof(stNrData.ui_value));
			PE_PRINT_NRD("set: wid %d, nrData.pst_chip_data 0x%p, ver 0x%02X\n", pqData.wid, nrData.pst_chip_data, pqData.version);
			if(pqData.version == 0x80) // webos26
			{
				if (nrData.pst_chip_data)
				{
					if (!(pstChipData_o26 = OS_Malloc(sizeof(*pstChipData_o26))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o26, (void __user *)nrData.pst_chip_data, sizeof(*pstChipData_o26)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stNrData.pst_chip_data = (unsigned char *)pstChipData_o26;
						nrData.pst_chip_data = (unsigned char *)pstChipData_o26;
					}
				}
				PE_PRINT_NRD("set: uUi %d %d, pChip 0x%p\n",
					stNrData.ui_value[0], stNrData.ui_value[1], stNrData.pst_chip_data);
				ret = vpq_hwrap_setnoisereduction(&stNrData, (UINT32)pqData.wid, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setnoisereduction error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &nrData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o26)
				{
					OS_Free(pstChipData_o26);
				}
			}
			else
			{
				
				if (nrData.pst_chip_data)
				{
					if (!(pstChipData_o20_f20_e60_o22_o24 = OS_Malloc(sizeof(*pstChipData_o20_f20_e60_o22_o24))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o20_f20_e60_o22_o24, (void __user *)nrData.pst_chip_data, sizeof(*pstChipData_o20_f20_e60_o22_o24)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stNrData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60_o22_o24;
						nrData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60_o22_o24;
					}
				}
				PE_PRINT_NRD("set: uUi %d %d, pChip 0x%p\n",
					stNrData.ui_value[0], stNrData.ui_value[1], stNrData.pst_chip_data);
				ret = vpq_hwrap_setnoisereduction(&stNrData, (UINT32)pqData.wid, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setnoisereduction error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &nrData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o20_f20_e60_o22_o24)
				{
					OS_Free(pstChipData_o20_f20_e60_o22_o24);
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		{
			struct v4l2_ext_vpq_mpeg_noise_reduction_data nrData;
			vpq_hwrap_mpeg_nr_t stNrData;
			vpq_hwrap_chip_mpeg_nr_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_mpeg_nr_o20_f20_e60_o22_24_t __attribute__((unused)) *pstChipData_o20_f20_e60_o22_o24 = NULL;
			vpq_hwrap_chip_mpeg_nr_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&nrData, 0x00, sizeof(nrData));
			memset(&stNrData, 0x00, sizeof(stNrData));

			if (copy_from_user(&nrData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			stNrData.ui_value = nrData.ui_value;
			PE_PRINT_NRD("set: wid %d, nrData.pst_chip_data 0x%p, ver 0x%02X\n", pqData.wid, nrData.pst_chip_data, pqData.version);
			if(pqData.version == 0x80) // webos26
			{
				if (nrData.pst_chip_data)
				{
					if (!(pstChipData_o26 = OS_Malloc(sizeof(*pstChipData_o26))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o26, (void __user *)nrData.pst_chip_data, sizeof(*pstChipData_o26)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stNrData.pst_chip_data = (unsigned char *)pstChipData_o26;
						nrData.pst_chip_data = (unsigned char *)pstChipData_o26;
					}
				}
				PE_PRINT_NRD("set: ui_value %d, pst_chip_data 0x%p\n",
					stNrData.ui_value, stNrData.pst_chip_data);
				ret = vpq_hwrap_setmpegnoisereduction(&stNrData,(UINT32)pqData.wid,(unsigned int)pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setnoisereduction error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &nrData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o26)
				{
					OS_Free(pstChipData_o26);
				}
			}
			else // version : webos24 (ox60)
			{
				if (nrData.pst_chip_data)
				{
					if (!(pstChipData_o20_f20_e60_o22_o24 = OS_Malloc(sizeof(*pstChipData_o20_f20_e60_o22_o24))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(pstChipData_o20_f20_e60_o22_o24, (void __user *)nrData.pst_chip_data, sizeof(*pstChipData_o20_f20_e60_o22_o24)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					else
					{
						stNrData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60_o22_o24;
						nrData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60_o22_o24;
					}
				}
				PE_PRINT_NRD("set: ui_value %d, pst_chip_data 0x%p\n",
					stNrData.ui_value, stNrData.pst_chip_data);
				ret = vpq_hwrap_setmpegnoisereduction(&stNrData,(UINT32)pqData.wid,(unsigned int)pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setnoisereduction error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &nrData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o20_f20_e60_o22_o24)
				{
					OS_Free(pstChipData_o20_f20_e60_o22_o24);
				}
			}
			
		} break;
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		{
			struct v4l2_ext_vpq_decontour_data decontourData;
			vpq_hwrap_decontour_t stDecontourData;
			vpq_hwrap_chip_decontour_t __attribute__((unused)) *pstChipData = NULL;
			vpq_hwrap_chip_decontour_o20_f20_e60_t __attribute__((unused)) *pstChipData_o20_f20_e60 = NULL;
			vpq_hwrap_chip_decontour_o22_f22_t __attribute__((unused)) *pstChipData_o22 = NULL;
			vpq_hwrap_chip_decontour_o24_t __attribute__((unused)) *pstChipData_o24 = NULL;
			vpq_hwrap_chip_decontour_o26_t __attribute__((unused)) *pstChipData_o26 = NULL;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DECONTOUR- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&decontourData, 0x00, sizeof(decontourData));
			memset(&stDecontourData, 0x00, sizeof(stDecontourData));

			if (copy_from_user(&decontourData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			stDecontourData.ui_value = decontourData.ui_value;
			PE_PRINT_NRD("set: wid %d, nrData.decontourData 0x%p, ver 0x%02X\n", pqData.wid, decontourData.pst_chip_data, pqData.version);

			if(pqData.version == 0x80) // webos26
			{
				if (decontourData.pst_chip_data)
				{
					do{
						pstChipData_o26 = OS_Malloc(sizeof(*pstChipData_o26));
						if (!pstChipData_o26)	{PE_PRINT_ERROR("pstChipData is null\n");break;}
						if (copy_from_user(pstChipData_o26, (void __user *)decontourData.pst_chip_data, sizeof(*pstChipData_o26)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							stDecontourData.pst_chip_data = (unsigned char *)pstChipData_o26;
							decontourData.pst_chip_data = (unsigned char *)pstChipData_o26;
						}
					}while(0);
				}
				PE_PRINT_NRD("set: uUi %d, pChip 0x%p\n",
					stDecontourData.ui_value, stDecontourData.pst_chip_data);
				ret = vpq_hwrap_setdecontour(&stDecontourData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setdecontour error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &decontourData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o26)
				{
					OS_Free(pstChipData_o26);
				}
			}
			else if(pqData.version == 0x60) // webos24
			{
				if (decontourData.pst_chip_data)
				{
					do{
						pstChipData_o24 = OS_Malloc(sizeof(*pstChipData_o24));
						if (!pstChipData_o24)	{PE_PRINT_ERROR("pstChipData is null\n");break;}
						if (copy_from_user(pstChipData_o24, (void __user *)decontourData.pst_chip_data, sizeof(*pstChipData_o24)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							stDecontourData.pst_chip_data = (unsigned char *)pstChipData_o24;
							decontourData.pst_chip_data = (unsigned char *)pstChipData_o24;
						}
					}while(0);
				}
				PE_PRINT_NRD("set: uUi %d, pChip 0x%p\n",
					stDecontourData.ui_value, stDecontourData.pst_chip_data);
				ret = vpq_hwrap_setdecontour(&stDecontourData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setdecontour error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &decontourData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o24)
				{
					OS_Free(pstChipData_o24);
				}
			}
			else if(pqData.version == 0x40) // webos22 O22db, M23db
			{
				if (decontourData.pst_chip_data)
				{
					do{
						pstChipData_o22 = OS_Malloc(sizeof(*pstChipData_o22));
						if (!pstChipData_o22)	{PE_PRINT_ERROR("pstChipData is null\n");break;}
						if (copy_from_user(pstChipData_o22, (void __user *)decontourData.pst_chip_data, sizeof(*pstChipData_o22)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							stDecontourData.pst_chip_data = (unsigned char *)pstChipData_o22;
							decontourData.pst_chip_data = (unsigned char *)pstChipData_o22;
						}
					}while(0);
				}
				PE_PRINT_NRD("set: uUi %d, pChip 0x%p\n",
					stDecontourData.ui_value, stDecontourData.pst_chip_data);
				ret = vpq_hwrap_setdecontour(&stDecontourData, (UINT32)pqData.wid, pqData.version );
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setdecontour error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &decontourData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o22)
				{
					OS_Free(pstChipData_o22);
				}
			}
			else if(PE_KDRV_VER_E60 || PE_KDRV_VER_O20)// O22+F22 case ver = 0x1, wID = 0x2or 0x3
			{
				if (decontourData.pst_chip_data)
				{
					do{
						pstChipData_o20_f20_e60 = OS_Malloc(sizeof(*pstChipData_o20_f20_e60));
						if (!pstChipData_o20_f20_e60)	{PE_PRINT_ERROR("pstChipData is null\n");break;}
						if (copy_from_user(pstChipData_o20_f20_e60, (void __user *)decontourData.pst_chip_data, sizeof(*pstChipData_o20_f20_e60)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							stDecontourData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60;
							decontourData.pst_chip_data = (unsigned char *)pstChipData_o20_f20_e60;
						}
					}while(0);
				}
				PE_PRINT_NRD("set: uUi %d, pChip 0x%p\n",
					stDecontourData.ui_value, stDecontourData.pst_chip_data);
				ret = vpq_hwrap_setdecontour(&stDecontourData, (UINT32)pqData.wid, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setdecontour error(%d)\n", ret);
				}
				else
				{
					if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &decontourData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if (pstChipData_o20_f20_e60)
				{
					OS_Free(pstChipData_o20_f20_e60);
				}
			}
			else if(pqData.version == 0x1) // temporally M23 for SOCTS version=1, chipdata=NULL case
			{
				PE_PRINT_NRD("set: uUi %d, pChip 0x%p\n",
					stDecontourData.ui_value, stDecontourData.pst_chip_data);
				if ((pqData.wid == 0x0 ||pqData.wid == 0x1) && v4l2_vpq_pe_save_param(ctrl->id, &decontourData, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		{
			struct v4l2_ext_cm_info cmInfo;
			//struct v4l2_ext_cm_info stcmInfo;
			vpq_hwrap_cm_db_t *pstDb = NULL;
			vpq_hwrap_cm_db_o26_t *pstDb_o26 = NULL;
			//UINT8* testdb;

			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_CM_DB_DATA- V4L2_CID_EXT_VPQ_BASE])
				break;
			memset(&cmInfo, 0x00, sizeof(cmInfo));

			if (copy_from_user(&cmInfo, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			PE_PRINT_CMG("set: use_internal_cm_db %d, dc %d, preferred %d, cms %d, dbInfo 0x%p, size :%zu\n",
				cmInfo.use_internal_cm_db, cmInfo.uiInfo.dynamic.enable,
				cmInfo.uiInfo.preferred.enable, cmInfo.uiInfo.cms.enable, cmInfo.dbInfo,sizeof(vpq_hwrap_cm_db_t));
			//stcmInfo.use_internal_cm_db = cmInfo.use_internal_cm_db;
			//if (cmInfo.dbInfo)
			do{
				if(cmInfo.use_internal_cm_db == 0x0)
				{
					if(pqData.version == 0x80)// webos26 o26
					{
						pstDb_o26 = OS_Malloc(sizeof(*pstDb_o26));
						if (!pstDb_o26)	{PE_PRINT_ERROR("pstDb_o26 is null\n");break;}
						if (copy_from_user(pstDb_o26, (void __user *)cmInfo.dbInfo, sizeof(*pstDb_o26)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							cmInfo.dbInfo = (unsigned char *)pstDb_o26;//TODO: fix warning : assignment from incompatible pointer type
						}
					}
					else// ~webos24 o24
					{
						pstDb = OS_Malloc(sizeof(*pstDb));
						if (!pstDb)	{PE_PRINT_ERROR("pstDb is null\n");break;}
						if (copy_from_user(pstDb, (void __user *)cmInfo.dbInfo, sizeof(*pstDb)))
						{
							PE_PRINT_ERROR("copy_from_user error\n");
						}
						else
						{
							cmInfo.dbInfo = (unsigned char *)pstDb;//TODO: fix warning : assignment from incompatible pointer type
							#if 0
							PE_PRINT_CMG("set: dbInfo needUpdate: region %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d, clear_white %d\n",
								pstDb->region_gain[0].needUpdate,
								pstDb->region_gain[1].needUpdate,
								pstDb->region_gain[2].needUpdate,
								pstDb->region_gain[3].needUpdate,
								pstDb->region_gain[4].needUpdate,
								pstDb->region_gain[5].needUpdate,
								pstDb->region_gain[6].needUpdate,
								pstDb->region_gain[7].needUpdate,
								pstDb->region_gain[8].needUpdate,
								pstDb->region_gain[9].needUpdate,
								pstDb->region_gain[10].needUpdate,
								pstDb->region_gain[11].needUpdate,
								pstDb->region_gain[12].needUpdate,
								pstDb->region_gain[13].needUpdate,
								pstDb->region_gain[14].needUpdate,
								pstDb->region_gain[15].needUpdate,
								pstDb->clear_white.needUpdate);
							
							PE_PRINT_CMG("set[%d] \n"\
								"satTarget : %d\n" \
								"objMapGainLUT_x : %d, %d, %d, %d" \
								"objMapGainLUT_y : %d, %d, %d, %d" \
								"faceMapGainLUT_x : %d, %d, %d, %d" \
								"faceMapGainLUT_y : %d, %d, %d, %d" \
								" hue_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
								" hue_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
								" sat_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
								" sat_g: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
								" val_x: %d, %d, %d, %d, %d, %d, %d, %d,\n" \
								" val_g: %d, %d, %d, %d, %d, %d, %d, %d,\n", \
								pstDb->cm_vspcc.needUpdate,\
								pstDb->cm_vspcc.satTarget,\
								pstDb->cm_vspcc.objMapGainLUT_x[0],pstDb->cm_vspcc.objMapGainLUT_x[1],pstDb->cm_vspcc.objMapGainLUT_x[2],pstDb->cm_vspcc.objMapGainLUT_x[3],\
								pstDb->cm_vspcc.objMapGainLUT_y[0],pstDb->cm_vspcc.objMapGainLUT_y[1],pstDb->cm_vspcc.objMapGainLUT_y[2],pstDb->cm_vspcc.objMapGainLUT_y[3],\
								pstDb->cm_vspcc.faceMapGainLUT_x[0],pstDb->cm_vspcc.faceMapGainLUT_x[1],pstDb->cm_vspcc.faceMapGainLUT_x[2],pstDb->cm_vspcc.faceMapGainLUT_x[3],\
								pstDb->cm_vspcc.faceMapGainLUT_y[0],pstDb->cm_vspcc.faceMapGainLUT_y[1],pstDb->cm_vspcc.faceMapGainLUT_y[2],pstDb->cm_vspcc.faceMapGainLUT_y[3],\
								pstDb->cm_vspcc.hue_x[0], pstDb->cm_vspcc.hue_x[1], pstDb->cm_vspcc.hue_x[2], pstDb->cm_vspcc.hue_x[3], \
								pstDb->cm_vspcc.hue_x[4], pstDb->cm_vspcc.hue_x[5], pstDb->cm_vspcc.hue_x[6], pstDb->cm_vspcc.hue_x[7], \
								pstDb->cm_vspcc.hue_g[0], pstDb->cm_vspcc.hue_g[1], pstDb->cm_vspcc.hue_g[2], pstDb->cm_vspcc.hue_g[3], \
								pstDb->cm_vspcc.hue_g[4], pstDb->cm_vspcc.hue_g[5], pstDb->cm_vspcc.hue_g[6], pstDb->cm_vspcc.hue_g[7], \
								pstDb->cm_vspcc.sat_x[0], pstDb->cm_vspcc.sat_x[1], pstDb->cm_vspcc.sat_x[2], pstDb->cm_vspcc.sat_x[3], \
								pstDb->cm_vspcc.sat_x[4], pstDb->cm_vspcc.sat_x[5], pstDb->cm_vspcc.sat_x[6], pstDb->cm_vspcc.sat_x[7], \
								pstDb->cm_vspcc.sat_g[0], pstDb->cm_vspcc.sat_g[1], pstDb->cm_vspcc.sat_g[2], pstDb->cm_vspcc.sat_g[3], \
								pstDb->cm_vspcc.sat_g[4], pstDb->cm_vspcc.sat_g[5], pstDb->cm_vspcc.sat_g[6], pstDb->cm_vspcc.sat_g[7], \
								pstDb->cm_vspcc.val_x[0], pstDb->cm_vspcc.val_x[1], pstDb->cm_vspcc.val_x[2], pstDb->cm_vspcc.val_x[3], \
								pstDb->cm_vspcc.val_x[4], pstDb->cm_vspcc.val_x[5], pstDb->cm_vspcc.val_x[6], pstDb->cm_vspcc.val_x[7], \
								pstDb->cm_vspcc.val_g[0], pstDb->cm_vspcc.val_g[1], pstDb->cm_vspcc.val_g[2], pstDb->cm_vspcc.val_g[3], \
								pstDb->cm_vspcc.val_g[4], pstDb->cm_vspcc.val_g[5], pstDb->cm_vspcc.val_g[6], pstDb->cm_vspcc.val_g[7]);
							#endif
						}
					}
				}
				PE_PRINT_CMG("**UI info**\n" \
				"dynamic color	en : %d\n" \
				"				value : %d\n" \
				"prefferd color en : %d\n" \
				"				val skin: %d, grass: %d skyblue: %d \n" \
				"cms			en : %d\n" \
				"				g_saturation : %d, %d, %d, %d, %d, %d\n" \
				"				g_hue		 : %d, %d, %d, %d, %d, %d\n" \
				"				g_luminance  : %d, %d, %d, %d, %d, %d\n", \
				cmInfo.uiInfo.dynamic.enable,\
				cmInfo.uiInfo.dynamic.value,\
				cmInfo.uiInfo.preferred.enable,\
				cmInfo.uiInfo.preferred.value[V4L2_EXT_CM_PREFERRED_COLOR_SKIN],\
				cmInfo.uiInfo.preferred.value[V4L2_EXT_CM_PREFERRED_COLOR_GRASS],\
				cmInfo.uiInfo.preferred.value[V4L2_EXT_CM_PREFERRED_COLOR_SKYBLUE],\
				cmInfo.uiInfo.cms.enable,\
				cmInfo.uiInfo.cms.gain_saturation[0],cmInfo.uiInfo.cms.gain_saturation[1],cmInfo.uiInfo.cms.gain_saturation[2],
				cmInfo.uiInfo.cms.gain_saturation[3],cmInfo.uiInfo.cms.gain_saturation[4],cmInfo.uiInfo.cms.gain_saturation[5],
				cmInfo.uiInfo.cms.gain_hue[0],cmInfo.uiInfo.cms.gain_hue[1],cmInfo.uiInfo.cms.gain_hue[2],
				cmInfo.uiInfo.cms.gain_hue[3],cmInfo.uiInfo.cms.gain_hue[4],cmInfo.uiInfo.cms.gain_hue[5],
				cmInfo.uiInfo.cms.gain_luminance[0],cmInfo.uiInfo.cms.gain_luminance[1],cmInfo.uiInfo.cms.gain_luminance[2],
				cmInfo.uiInfo.cms.gain_luminance[3],cmInfo.uiInfo.cms.gain_luminance[4],cmInfo.uiInfo.cms.gain_luminance[5]);
				ret = vpq_hwrap_setcmdbdata(pqData.wid, &cmInfo, pqData.version);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_setcmdbdata error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &cmInfo, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}while(0);
			if (pstDb) {OS_Free(pstDb);}
			if (pstDb_o26) {OS_Free(pstDb_o26);}
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		{
			vpq_hwrap_chip_dc2p_localcontrast_table_t *pstDrcData = NULL;
			vpq_hwrap_chip_dc2p_localcontrast_table_o26_t *pstDrcData_o26 = NULL;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE- V4L2_CID_EXT_VPQ_BASE])
				break;

			PE_PRINT_DCM("[%s.%d]version:%d\n",\
						__F__, __L__,	pqData.version);
			do{
				if(pqData.version == 0x80)//o26
				{
					pstDrcData_o26 = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_o26_t));
					if (!pstDrcData_o26)	{PE_PRINT_ERROR("pstDrcData is null\n");break;}
					if (copy_from_user(pstDrcData_o26, (void __user *)pqData.p_data, pqData.length))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}

					ret =vpq_hwrap_setlocalcontrasttable_o26(pstDrcData_o26);

					if (ret)
					{
						PE_PRINT_ERROR("KWRAP_PE_SetDrcCurv error(%d)\n", ret);
					}
					else
					{
						if (v4l2_vpq_pe_save_param(ctrl->id, pstDrcData_o26, pqData.version))
						{
							PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
						}
					}
					if(pstDrcData_o26) {OS_Free(pstDrcData_o26);}
				}
				else
				{
					pstDrcData = OS_Malloc(sizeof(vpq_hwrap_chip_dc2p_localcontrast_table_t));
					if (!pstDrcData)	{PE_PRINT_ERROR("pstDrcData is null\n");break;}
					if (copy_from_user(pstDrcData, (void __user *)pqData.p_data, pqData.length))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					ret =vpq_hwrap_setlocalcontrasttable(pstDrcData);

					if (ret)
					{
						PE_PRINT_ERROR("KWRAP_PE_SetDrcCurv error(%d)\n", ret);
					}
					else
					{
						if (v4l2_vpq_pe_save_param(ctrl->id, pstDrcData, pqData.version))
						{
							PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
						}
					}
					if(pstDrcData) {OS_Free(pstDrcData);}
				}
			}while(0);
		} break;
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		{
			vpq_hwrap_chip_dc2p_drc_cont_t stDrcData;
			vpq_hwrap_chip_dc2p_drc_cont_weboso22_t stDrcData_o22;
			vpq_hwrap_chip_dc2p_drc_cont_weboso23_t stDrcData_o23;
			vpq_hwrap_chip_dc2p_drc_cont_weboso26_t *pDrcData_o26;
			LX_PE_DCM_DRC_CONT_T param;
			LX_PE_DCM_DRC_CONT1_T param_o22;
			LX_PE_DCM_DRC_CONT2_T param_o23;
			LX_PE_DCM_DRC_CONT3_T *pParam_o26;
			LX_PE_DCM_DRC_MODE_T drc_param;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA- V4L2_CID_EXT_VPQ_BASE])
				break;
				
			PE_PRINT_DCM("[%s.%d]version:%d\n",\
						__F__, __L__,	pqData.version);
			if (pqData.version ==0x80)
			{
				if (!(pDrcData_o26 = OS_Malloc(sizeof(*pDrcData_o26))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
				memset(pDrcData_o26, 0x00, sizeof(vpq_hwrap_chip_dc2p_drc_cont_weboso26_t));
				if (copy_from_user(pDrcData_o26, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				pParam_o26 = OS_Malloc(sizeof(LX_PE_DCM_DRC_CONT3_T));
				if (!(pParam_o26 = OS_Malloc(sizeof(*pParam_o26))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
				pParam_o26->win_id = LX_PE_WIN_0;
				memcpy(&(pParam_o26->ui_mode_loc), pDrcData_o26, sizeof(*pDrcData_o26));
				PE_PRINT_DCM(
					"[%s.%d] DRC param:\n"\
					"local contrast ui:%d\n"\
					"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
					"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n"\
					"nApl_lut_x   :%d, %d, %d, %d\n"\
					"nApl_lut_y   :%d, %d, %d, %d\n"\
					"nTxt_lut_x   :%d, %d, %d, %d, %d, %d, %d, %d\n"\
					"nTxt_lut_y   :%d, %d, %d, %d, %d, %d, %d, %d\n"\
					"nDark_lut_x  :%d, %d, %d, %d\n"\
					"nDark_lut_y  :%d, %d, %d, %d\n"\
					"nBright_lut_x:%d, %d, %d, %d\n"\
					"nBright_lut_y:%d, %d, %d, %d\n"
					"nHead_lut_x  :%d, %d, %d, %d\n"\
					"nHead_lut_y  :%d, %d, %d, %d\n"\
					"nBody_lut_x  :%d, %d, %d, %d\n"\
					"nBody_lut_y  :%d, %d, %d, %d\n"\
					"nText_lut_x  :%d, %d, %d, %d\n"\
					"nText_lut_y  :%d, %d, %d, %d\n"\
					"y_ma_sel, t_ma_sel: %d, %d\n"\
					"bapp_y_lut_x  :%d, %d, %d, %d\n"\
					"bapp_y_lut_y  :%d, %d, %d, %d\n"\
					"bapp_t_lut_x  :%d, %d, %d, %d\n"\
					"bapp_t_lut_y  :%d, %d, %d, %d\n",\
					__F__, __L__,\
					pParam_o26->ui_mode_loc,\
					pParam_o26->pre_norm,pParam_o26->cur_norm,pParam_o26->pre_sc,pParam_o26->cur_sc,\
					pParam_o26->ui_gain_w,pParam_o26->ui_gain_b,pParam_o26->vy_mode,\
					pParam_o26->apl_lut_x[0],pParam_o26->apl_lut_x[1],pParam_o26->apl_lut_x[2],pParam_o26->apl_lut_x[3],\
					pParam_o26->apl_lut_y[0],pParam_o26->apl_lut_y[1],pParam_o26->apl_lut_y[2],pParam_o26->apl_lut_y[3],\
					pParam_o26->txt_lut_x[0],pParam_o26->txt_lut_x[1],pParam_o26->txt_lut_x[2],pParam_o26->txt_lut_x[3],\
					pParam_o26->txt_lut_x[4],pParam_o26->txt_lut_x[5],pParam_o26->txt_lut_x[6],pParam_o26->txt_lut_x[7],\
					pParam_o26->txt_lut_y[0],pParam_o26->txt_lut_y[1],pParam_o26->txt_lut_y[2],pParam_o26->txt_lut_y[3],\
					pParam_o26->txt_lut_y[4],pParam_o26->txt_lut_y[5],pParam_o26->txt_lut_y[6],pParam_o26->txt_lut_y[7],\
					pParam_o26->dark_lut_x[0],pParam_o26->dark_lut_x[1],pParam_o26->dark_lut_x[2],pParam_o26->dark_lut_x[3],\
					pParam_o26->dark_lut_y[0],pParam_o26->dark_lut_y[1],pParam_o26->dark_lut_y[2],pParam_o26->dark_lut_y[3],\
					pParam_o26->bright_lut_x[0],pParam_o26->bright_lut_x[1],pParam_o26->bright_lut_x[2],pParam_o26->bright_lut_x[3],\
					pParam_o26->bright_lut_y[0],pParam_o26->bright_lut_y[1],pParam_o26->bright_lut_y[2],pParam_o26->bright_lut_y[3],\
					pParam_o26->nHead_lut_x[0],pParam_o26->nHead_lut_x[1],pParam_o26->nHead_lut_x[2],pParam_o26->nHead_lut_x[3],\
					pParam_o26->nHead_lut_y[0],pParam_o26->nHead_lut_y[1],pParam_o26->nHead_lut_y[2],pParam_o26->nHead_lut_y[3],\
					pParam_o26->nBody_lut_x[0],pParam_o26->nBody_lut_x[1],pParam_o26->nBody_lut_x[2],pParam_o26->nBody_lut_x[3],\
					pParam_o26->nBody_lut_y[0],pParam_o26->nBody_lut_y[1],pParam_o26->nBody_lut_y[2],pParam_o26->nBody_lut_y[3],\
					pParam_o26->nText_lut_x[0],pParam_o26->nText_lut_x[1],pParam_o26->nText_lut_x[2],pParam_o26->nText_lut_x[3],\
					pParam_o26->nText_lut_y[0],pParam_o26->nText_lut_y[1],pParam_o26->nText_lut_y[2],pParam_o26->nText_lut_y[3],\
					pParam_o26->y_ma_sel, pParam_o26->t_ma_sel,\
					pParam_o26->bapp_y_lut_x[0],pParam_o26->bapp_y_lut_x[1],pParam_o26->bapp_y_lut_x[2],pParam_o26->bapp_y_lut_x[3],\
					pParam_o26->bapp_y_lut_y[0],pParam_o26->bapp_y_lut_y[1],pParam_o26->bapp_y_lut_y[2],pParam_o26->bapp_y_lut_y[3],\
					pParam_o26->bapp_t_lut_x[0],pParam_o26->bapp_t_lut_x[1],pParam_o26->bapp_t_lut_x[2],pParam_o26->bapp_t_lut_x[3],\
					pParam_o26->bapp_t_lut_y[0],pParam_o26->bapp_t_lut_y[1],pParam_o26->bapp_t_lut_y[2],pParam_o26->bapp_t_lut_y[3]);
				//DRC mode
				drc_param.win_id = LX_PE_WIN_0;
				ret = PE_DCM_GetDceDrcMode(&drc_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_GetDceDrcMode: error(%d)\n", ret);
					break;
				}
				drc_param.dc_mode = (UINT32)pDrcData_o26->ui_mode_loc;
				drc_param.db_type = LX_PE_DRC_UI;
				PE_PRINT_DCM("PE_DCM_GetDceDrcMode: win_id = %d, dc_mode = %d, picture_mode = %d\n",\
					drc_param.win_id, drc_param.dc_mode, drc_param.picture_mode);

				ret = PE_DCM_SetDceDrcMode(&drc_param);
				//DRC CTRL
				ret = PE_DCM_SetDrcCtrl((void *)pParam_o26);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDrcCtrl error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, pDrcData_o26, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
				if(pDrcData_o26) {OS_Free(pDrcData_o26);}
				if(pParam_o26) {OS_Free(pParam_o26);}
			}
			else if (pqData.version ==0x50)
			{
				memset(&stDrcData_o23, 0x00, sizeof(stDrcData_o23));
				
				if (copy_from_user(&stDrcData_o23, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				param_o23.win_id = LX_PE_WIN_0;
				memcpy(&param_o23.ui_mode_loc, &stDrcData_o23, sizeof(stDrcData_o23));
				PE_PRINT_DCM(
					"[%s.%d] DRC param:\n"\
					"local contrast ui:%d\n"\
					"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
					"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n"\
					"nApl_lut_x   :%d, %d, %d, %d\n"\
					"nApl_lut_y   :%d, %d, %d, %d\n"\
					"nTxt_lut_x   :%d, %d, %d, %d\n"\
					"nTxt_lut_y   :%d, %d, %d, %d\n"\
					"nDark_lut_x  :%d, %d, %d, %d\n"\
					"nDark_lut_y  :%d, %d, %d, %d\n"\
					"nBright_lut_x:%d, %d, %d, %d\n"\
					"nBright_lut_y:%d, %d, %d, %d\n"
					"nHead_lut_x  :%d, %d, %d, %d\n"\
					"nHead_lut_y  :%d, %d, %d, %d\n"\
					"nBody_lut_x  :%d, %d, %d, %d\n"\
					"nBody_lut_y  :%d, %d, %d, %d\n"\
					"nText_lut_x  :%d, %d, %d, %d\n"\
					"nText_lut_y  :%d, %d, %d, %d\n",\
					__F__, __L__,\
					param_o23.ui_mode_loc,\
					param_o23.pre_norm,param_o23.cur_norm,param_o23.pre_sc,param_o23.cur_sc,\
					param_o23.ui_gain_w,param_o23.ui_gain_b,param_o23.vy_mode,\
					param_o23.apl_lut_x[0],param_o23.apl_lut_x[1],param_o23.apl_lut_x[2],param_o23.apl_lut_x[3],\
					param_o23.apl_lut_y[0],param_o23.apl_lut_y[1],param_o23.apl_lut_y[2],param_o23.apl_lut_y[3],\
					param_o23.txt_lut_x[0],param_o23.txt_lut_x[1],param_o23.txt_lut_x[2],param_o23.txt_lut_x[3],\
					param_o23.txt_lut_y[0],param_o23.txt_lut_y[1],param_o23.txt_lut_y[2],param_o23.txt_lut_y[3],\
					param_o23.dark_lut_x[0],param_o23.dark_lut_x[1],param_o23.dark_lut_x[2],param_o23.dark_lut_x[3],\
					param_o23.dark_lut_y[0],param_o23.dark_lut_y[1],param_o23.dark_lut_y[2],param_o23.dark_lut_y[3],\
					param_o23.bright_lut_x[0],param_o23.bright_lut_x[1],param_o23.bright_lut_x[2],param_o23.bright_lut_x[3],\
					param_o23.bright_lut_y[0],param_o23.bright_lut_y[1],param_o23.bright_lut_y[2],param_o23.bright_lut_y[3],\
					param_o23.nHead_lut_x[0],param_o23.nHead_lut_x[1],param_o23.nHead_lut_x[2],param_o23.nHead_lut_x[3],\
					param_o23.nHead_lut_y[0],param_o23.nHead_lut_y[1],param_o23.nHead_lut_y[2],param_o23.nHead_lut_y[3],\
					param_o23.nBody_lut_x[0],param_o23.nBody_lut_x[1],param_o23.nBody_lut_x[2],param_o23.nBody_lut_x[3],\
					param_o23.nBody_lut_y[0],param_o23.nBody_lut_y[1],param_o23.nBody_lut_y[2],param_o23.nBody_lut_y[3],\
					param_o23.nText_lut_x[0],param_o23.nText_lut_x[1],param_o23.nText_lut_x[2],param_o23.nText_lut_x[3],\
					param_o23.nText_lut_y[0],param_o23.nText_lut_y[1],param_o23.nText_lut_y[2],param_o23.nText_lut_y[3]);
				//DRC mode
				drc_param.win_id = LX_PE_WIN_0;
				ret = PE_DCM_GetDceDrcMode(&drc_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_GetDceDrcMode: error(%d)\n", ret);
					break;
				}
				drc_param.dc_mode = (UINT32)stDrcData_o23.ui_mode_loc;
				drc_param.db_type = LX_PE_DRC_UI;
				PE_PRINT_DCM("PE_DCM_GetDceDrcMode: win_id = %d, dc_mode = %d, picture_mode = %d\n",\
					drc_param.win_id, drc_param.dc_mode, drc_param.picture_mode);

				ret = PE_DCM_SetDceDrcMode(&drc_param);
				//DRC CTRL
				ret = PE_DCM_SetDrcCtrl2((void *)&param_o23);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDrcCtrl2 error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stDrcData_o23, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if (pqData.version ==0x40)
			{
				memset(&stDrcData_o22, 0x00, sizeof(stDrcData_o22));
				
				if (copy_from_user(&stDrcData_o22, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				
				param_o22.win_id = LX_PE_WIN_0;
				memcpy(&param_o22.pre_norm, &stDrcData_o22, sizeof(stDrcData_o22));
				PE_PRINT_DCM(
					"[%s.%d] DRC param:\n"\
					"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
					"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n"\
					"nApl_lut_x   :%d, %d, %d, %d\n"\
					"nApl_lut_y   :%d, %d, %d, %d\n"\
					"nTxt_lut_x   :%d, %d, %d, %d\n"\
					"nTxt_lut_y   :%d, %d, %d, %d\n"\
					"nDark_lut_x  :%d, %d, %d, %d\n"\
					"nDark_lut_y  :%d, %d, %d, %d\n"\
					"nBright_lut_x:%d, %d, %d, %d\n"\
					"nBright_lut_y:%d, %d, %d, %d\n",\
					__F__, __L__,\
					param_o22.pre_norm,param_o22.cur_norm,param_o22.pre_sc,param_o22.cur_sc,\
					param_o22.ui_gain_w,param_o22.ui_gain_b,param_o22.vy_mode,\
					param_o22.apl_lut_x[0],param_o22.apl_lut_x[1],param_o22.apl_lut_x[2],param_o22.apl_lut_x[3],\
					param_o22.apl_lut_y[0],param_o22.apl_lut_y[1],param_o22.apl_lut_y[2],param_o22.apl_lut_y[3],\
					param_o22.txt_lut_x[0],param_o22.txt_lut_x[1],param_o22.txt_lut_x[2],param_o22.txt_lut_x[3],\
					param_o22.txt_lut_y[0],param_o22.txt_lut_y[1],param_o22.txt_lut_y[2],param_o22.txt_lut_y[3],\
					param_o22.dark_lut_x[0],param_o22.dark_lut_x[1],param_o22.dark_lut_x[2],param_o22.dark_lut_x[3],\
					param_o22.dark_lut_y[0],param_o22.dark_lut_y[1],param_o22.dark_lut_y[2],param_o22.dark_lut_y[3],\
					param_o22.bright_lut_x[0],param_o22.bright_lut_x[1],param_o22.bright_lut_x[2],param_o22.bright_lut_x[3],\
					param_o22.bright_lut_y[0],param_o22.bright_lut_y[1],param_o22.bright_lut_y[2],param_o22.bright_lut_y[3]);
				ret = PE_DCM_SetDrcCtrl((void *)&param_o22);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDrcCtrl error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stDrcData_o22, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else
			{
				
				memset(&stDrcData, 0x00, sizeof(stDrcData));
				
				if (copy_from_user(&stDrcData, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				
				param.win_id = LX_PE_WIN_0;
				memcpy(&param.pre_norm, &stDrcData, sizeof(stDrcData));
				PE_PRINT_DCM(
					"[%s.%d] DRC param:\n"\
					"pre_norm:%d,cur_norm:%d,pre_sc:%d,cur_sc:%d\n"\
					"ui_gain_w:%d,ui_gain_b:%d,vy_mode:%d\n",\
					__F__, __L__,\
					param.pre_norm,param.cur_norm,param.pre_sc,param.cur_sc,
					param.ui_gain_w,param.ui_gain_b,param.vy_mode);
				if(PE_KDRV_VER_E60)
				{
					ret = PE_DCM_SetDrcCtrl((void *)&param);
				}
				else
				{
					ret = KWRAP_PE_SetDrcCtrl((void *)&param);
				}
				if (ret)
				{
					PE_PRINT_ERROR("KWRAP_PE_SetDrcCtrl error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stDrcData, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_PSP:
		{
			vpq_hwrap_chip_perspective_t stPspData;
			LX_PE_SHP_PSP_T param;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_PSP- V4L2_CID_EXT_VPQ_BASE])
				break;

			memset(&stPspData, 0x00, sizeof(stPspData));

			if (copy_from_user(&stPspData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			param.win_id = LX_PE_WIN_0;
			memcpy(&param.iir_en, &stPspData, sizeof(stPspData));

			PE_PRINT_OBC(
				"[%s.%d] PSP ctrl: iir_en:%d, psp_en:%d, chrm_protect_en:%dn"
				"map_master_gain:%d,iir_gain:%d, cbcr_offset_gain:%d,%dn"
				"posi_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%dn"
				"posi_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%dn"
				"psp_lut_x: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%dn"
				"psp_lut_y: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%dn",
				__F__, __L__,
				param.iir_en, param.psp_en, param.chroma_protection_en,
				param.map_master_gain, param.iir_gain, param.cb_offset_gain, param.cr_offset_gain,
				param.position_lut_x[0], param.position_lut_x[1], param.position_lut_x[2], param.position_lut_x[3],
				param.position_lut_x[4], param.position_lut_x[5], param.position_lut_x[6], param.position_lut_x[7],
				param.position_lut_x[8], param.position_lut_x[9], param.position_lut_x[10], param.position_lut_x[11],
				param.position_lut_x[12], param.position_lut_x[13], param.position_lut_x[14], param.position_lut_x[15],
				param.position_lut_y[0], param.position_lut_y[1], param.position_lut_y[2], param.position_lut_y[3],
				param.position_lut_y[4], param.position_lut_y[5], param.position_lut_y[6], param.position_lut_y[7],
				param.position_lut_y[8], param.position_lut_y[9], param.position_lut_y[10], param.position_lut_y[11],
				param.position_lut_y[12], param.position_lut_y[13], param.position_lut_y[14], param.position_lut_y[15],
				param.psp_lut_x[0], param.psp_lut_x[1], param.psp_lut_x[2], param.psp_lut_x[3],
				param.psp_lut_x[4], param.psp_lut_x[5], param.psp_lut_x[6], param.psp_lut_x[7],
				param.psp_lut_x[8], param.psp_lut_x[9], param.psp_lut_x[10], param.psp_lut_x[11],
				param.psp_lut_x[12], param.psp_lut_x[13], param.psp_lut_x[14], param.psp_lut_x[15], param.psp_lut_x[16],
				param.psp_lut_y[0], param.psp_lut_y[1], param.psp_lut_y[2], param.psp_lut_y[3],
				param.psp_lut_y[4], param.psp_lut_y[5], param.psp_lut_y[6], param.psp_lut_y[7],
				param.psp_lut_y[8], param.psp_lut_y[9], param.psp_lut_y[10], param.psp_lut_y[11],
				param.psp_lut_y[12], param.psp_lut_y[13], param.psp_lut_y[14], param.psp_lut_y[15], param.psp_lut_y[16]);
			if (PE_KDRV_VER_E60)
			{
				// not support
			}
			else
			{
				ret = KWRAP_PE_SetPspParam((void *)&param);
			}	
			if (ret)
			{
				PE_PRINT_ERROR("KWRAP_PE_SetPspParam error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &stPspData, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		{
			#if 1
			ret = vpq_set_obc_lut(&pqData, ctrl);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_set_obc_lut error(%d)\n", ret);
			}
			#else
			vpq_hwrap_obc_lut_o20_t stObcLut;
			vpq_hwrap_obc_lut_e60_o22_t stObcLut_e60_o22;
			LX_PE_VSD_OBC1_LUT_T param;
			LX_PE_VSD_OBC2_LUT_T param_e60_o22;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_LUT- V4L2_CID_EXT_VPQ_BASE])
				break;
			if(pqData.version == 0x40) // webos22 o22, temporally M23 for SOCTS
			{
				memset(&stObcLut_e60_o22, 0x00, sizeof(stObcLut_e60_o22));

				if (copy_from_user(&stObcLut_e60_o22, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				PE_PRINT_OBC_LUT(
					"[%s.%d] OBC LUT \n"\
					"head_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"head_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
					"head_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"head_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
					"head_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"head_r_lut_y: %d,%d,%d,%d,%d,%d\n"\
					"body_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"body_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
					"body_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"body_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
					"body_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
					"body_r_lut_y: %d,%d,%d,%d,%d,%d\n",\
					__F__, __L__,\
					stObcLut_e60_o22.head_g_lut_x[0],stObcLut_e60_o22.head_g_lut_x[1],stObcLut_e60_o22.head_g_lut_x[2],\
					stObcLut_e60_o22.head_g_lut_x[3],stObcLut_e60_o22.head_g_lut_x[4],stObcLut_e60_o22.head_g_lut_x[5],\
					stObcLut_e60_o22.head_g_lut_y[0],stObcLut_e60_o22.head_g_lut_y[1],stObcLut_e60_o22.head_g_lut_y[2],\
					stObcLut_e60_o22.head_g_lut_y[3],stObcLut_e60_o22.head_g_lut_y[4],stObcLut_e60_o22.head_g_lut_y[5],\
					stObcLut_e60_o22.head_b_lut_x[0],stObcLut_e60_o22.head_b_lut_x[1],stObcLut_e60_o22.head_b_lut_x[2],\
					stObcLut_e60_o22.head_b_lut_x[3],stObcLut_e60_o22.head_b_lut_x[4],stObcLut_e60_o22.head_b_lut_x[5],\
					stObcLut_e60_o22.head_b_lut_y[0],stObcLut_e60_o22.head_b_lut_y[1],stObcLut_e60_o22.head_b_lut_y[2],\
					stObcLut_e60_o22.head_b_lut_y[3],stObcLut_e60_o22.head_b_lut_y[4],stObcLut_e60_o22.head_b_lut_y[5],\
					stObcLut_e60_o22.head_r_lut_x[0],stObcLut_e60_o22.head_r_lut_x[1],stObcLut_e60_o22.head_r_lut_x[2],\
					stObcLut_e60_o22.head_r_lut_x[3],stObcLut_e60_o22.head_r_lut_x[4],stObcLut_e60_o22.head_r_lut_x[5],\
					stObcLut_e60_o22.head_r_lut_y[0],stObcLut_e60_o22.head_r_lut_y[1],stObcLut_e60_o22.head_r_lut_y[2],\
					stObcLut_e60_o22.head_r_lut_y[3],stObcLut_e60_o22.head_r_lut_y[4],stObcLut_e60_o22.head_r_lut_y[5],\
					stObcLut_e60_o22.body_g_lut_x[0],stObcLut_e60_o22.body_g_lut_x[1],stObcLut_e60_o22.body_g_lut_x[2],\
					stObcLut_e60_o22.body_g_lut_x[3],stObcLut_e60_o22.body_g_lut_x[4],stObcLut_e60_o22.body_g_lut_x[5],\
					stObcLut_e60_o22.body_g_lut_y[0],stObcLut_e60_o22.body_g_lut_y[1],stObcLut_e60_o22.body_g_lut_y[2],\
					stObcLut_e60_o22.body_g_lut_y[3],stObcLut_e60_o22.body_g_lut_y[4],stObcLut_e60_o22.body_g_lut_y[5],\
					stObcLut_e60_o22.body_b_lut_x[0],stObcLut_e60_o22.body_b_lut_x[1],stObcLut_e60_o22.body_b_lut_x[2],\
					stObcLut_e60_o22.body_b_lut_x[3],stObcLut_e60_o22.body_b_lut_x[4],stObcLut_e60_o22.body_b_lut_x[5],\
					stObcLut_e60_o22.body_b_lut_y[0],stObcLut_e60_o22.body_b_lut_y[1],stObcLut_e60_o22.body_b_lut_y[2],\
					stObcLut_e60_o22.body_b_lut_y[3],stObcLut_e60_o22.body_b_lut_y[4],stObcLut_e60_o22.body_b_lut_y[5],\
					stObcLut_e60_o22.body_r_lut_x[0],stObcLut_e60_o22.body_r_lut_x[1],stObcLut_e60_o22.body_r_lut_x[2],\
					stObcLut_e60_o22.body_r_lut_x[3],stObcLut_e60_o22.body_r_lut_x[4],stObcLut_e60_o22.body_r_lut_x[5],\
					stObcLut_e60_o22.body_r_lut_y[0],stObcLut_e60_o22.body_r_lut_y[1],stObcLut_e60_o22.body_r_lut_y[2],\
					stObcLut_e60_o22.body_r_lut_y[3],stObcLut_e60_o22.body_r_lut_y[4],stObcLut_e60_o22.body_r_lut_y[5]);
				param_e60_o22.win_id = LX_PE_WIN_0;
				memcpy(param_e60_o22.head_g_lut_x, stObcLut_e60_o22.head_g_lut_x, sizeof(stObcLut_e60_o22.head_g_lut_x));
				memcpy(param_e60_o22.head_g_lut_y, stObcLut_e60_o22.head_g_lut_y, sizeof(stObcLut_e60_o22.head_g_lut_y));
				memcpy(param_e60_o22.head_b_lut_x, stObcLut_e60_o22.head_b_lut_x, sizeof(stObcLut_e60_o22.head_b_lut_x));
				memcpy(param_e60_o22.head_b_lut_y, stObcLut_e60_o22.head_b_lut_y, sizeof(stObcLut_e60_o22.head_b_lut_y));
				memcpy(param_e60_o22.head_r_lut_x, stObcLut_e60_o22.head_r_lut_x, sizeof(stObcLut_e60_o22.head_r_lut_x));
				memcpy(param_e60_o22.head_r_lut_y, stObcLut_e60_o22.head_r_lut_y, sizeof(stObcLut_e60_o22.head_r_lut_y));
				memcpy(param_e60_o22.body_g_lut_x, stObcLut_e60_o22.body_g_lut_x, sizeof(stObcLut_e60_o22.body_g_lut_x));
				memcpy(param_e60_o22.body_g_lut_y, stObcLut_e60_o22.body_g_lut_y, sizeof(stObcLut_e60_o22.body_g_lut_y));
				memcpy(param_e60_o22.body_b_lut_x, stObcLut_e60_o22.body_b_lut_x, sizeof(stObcLut_e60_o22.body_b_lut_x));
				memcpy(param_e60_o22.body_b_lut_y, stObcLut_e60_o22.body_b_lut_y, sizeof(stObcLut_e60_o22.body_b_lut_y));
				memcpy(param_e60_o22.body_r_lut_x, stObcLut_e60_o22.body_r_lut_x, sizeof(stObcLut_e60_o22.body_r_lut_x));
				memcpy(param_e60_o22.body_r_lut_y, stObcLut_e60_o22.body_r_lut_y, sizeof(stObcLut_e60_o22.body_r_lut_y));
				ret = PE_SHP_SetObcLUT((void *)&param_e60_o22);
				if (ret)
				{
					PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut_e60_o22, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(PE_KDRV_VER_E60)
			{
				/* version definition
				   chip O20 : version = 1 (default)
				        E60 : version = 3x.
				*/
				if(pqData.version == 30)
				{
					memset(&stObcLut_e60_o22, 0x00, sizeof(stObcLut_e60_o22));

					if (copy_from_user(&stObcLut_e60_o22, (void __user *)pqData.p_data, pqData.length))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					PE_PRINT_OBC_LUT(
						"[%s.%d] OBC LUT \n"\
						"head_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"head_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
						"head_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"head_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
						"head_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"head_r_lut_y: %d,%d,%d,%d,%d,%d\n"\
						"body_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"body_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
						"body_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"body_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
						"body_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
						"body_r_lut_y: %d,%d,%d,%d,%d,%d\n",\
						__F__, __L__,\
						stObcLut_e60_o22.head_g_lut_x[0],stObcLut_e60_o22.head_g_lut_x[1],stObcLut_e60_o22.head_g_lut_x[2],\
						stObcLut_e60_o22.head_g_lut_x[3],stObcLut_e60_o22.head_g_lut_x[4],stObcLut_e60_o22.head_g_lut_x[5],\
						stObcLut_e60_o22.head_g_lut_y[0],stObcLut_e60_o22.head_g_lut_y[1],stObcLut_e60_o22.head_g_lut_y[2],\
						stObcLut_e60_o22.head_g_lut_y[3],stObcLut_e60_o22.head_g_lut_y[4],stObcLut_e60_o22.head_g_lut_y[5],\
						stObcLut_e60_o22.head_b_lut_x[0],stObcLut_e60_o22.head_b_lut_x[1],stObcLut_e60_o22.head_b_lut_x[2],\
						stObcLut_e60_o22.head_b_lut_x[3],stObcLut_e60_o22.head_b_lut_x[4],stObcLut_e60_o22.head_b_lut_x[5],\
						stObcLut_e60_o22.head_b_lut_y[0],stObcLut_e60_o22.head_b_lut_y[1],stObcLut_e60_o22.head_b_lut_y[2],\
						stObcLut_e60_o22.head_b_lut_y[3],stObcLut_e60_o22.head_b_lut_y[4],stObcLut_e60_o22.head_b_lut_y[5],\
						stObcLut_e60_o22.head_r_lut_x[0],stObcLut_e60_o22.head_r_lut_x[1],stObcLut_e60_o22.head_r_lut_x[2],\
						stObcLut_e60_o22.head_r_lut_x[3],stObcLut_e60_o22.head_r_lut_x[4],stObcLut_e60_o22.head_r_lut_x[5],\
						stObcLut_e60_o22.head_r_lut_y[0],stObcLut_e60_o22.head_r_lut_y[1],stObcLut_e60_o22.head_r_lut_y[2],\
						stObcLut_e60_o22.head_r_lut_y[3],stObcLut_e60_o22.head_r_lut_y[4],stObcLut_e60_o22.head_r_lut_y[5],\
						stObcLut_e60_o22.body_g_lut_x[0],stObcLut_e60_o22.body_g_lut_x[1],stObcLut_e60_o22.body_g_lut_x[2],\
						stObcLut_e60_o22.body_g_lut_x[3],stObcLut_e60_o22.body_g_lut_x[4],stObcLut_e60_o22.body_g_lut_x[5],\
						stObcLut_e60_o22.body_g_lut_y[0],stObcLut_e60_o22.body_g_lut_y[1],stObcLut_e60_o22.body_g_lut_y[2],\
						stObcLut_e60_o22.body_g_lut_y[3],stObcLut_e60_o22.body_g_lut_y[4],stObcLut_e60_o22.body_g_lut_y[5],\
						stObcLut_e60_o22.body_b_lut_x[0],stObcLut_e60_o22.body_b_lut_x[1],stObcLut_e60_o22.body_b_lut_x[2],\
						stObcLut_e60_o22.body_b_lut_x[3],stObcLut_e60_o22.body_b_lut_x[4],stObcLut_e60_o22.body_b_lut_x[5],\
						stObcLut_e60_o22.body_b_lut_y[0],stObcLut_e60_o22.body_b_lut_y[1],stObcLut_e60_o22.body_b_lut_y[2],\
						stObcLut_e60_o22.body_b_lut_y[3],stObcLut_e60_o22.body_b_lut_y[4],stObcLut_e60_o22.body_b_lut_y[5],\
						stObcLut_e60_o22.body_r_lut_x[0],stObcLut_e60_o22.body_r_lut_x[1],stObcLut_e60_o22.body_r_lut_x[2],\
						stObcLut_e60_o22.body_r_lut_x[3],stObcLut_e60_o22.body_r_lut_x[4],stObcLut_e60_o22.body_r_lut_x[5],\
						stObcLut_e60_o22.body_r_lut_y[0],stObcLut_e60_o22.body_r_lut_y[1],stObcLut_e60_o22.body_r_lut_y[2],\
						stObcLut_e60_o22.body_r_lut_y[3],stObcLut_e60_o22.body_r_lut_y[4],stObcLut_e60_o22.body_r_lut_y[5]);
					param_e60_o22.win_id = LX_PE_WIN_0;
					memcpy(param_e60_o22.head_g_lut_x, stObcLut_e60_o22.head_g_lut_x, sizeof(stObcLut_e60_o22.head_g_lut_x));
					memcpy(param_e60_o22.head_g_lut_y, stObcLut_e60_o22.head_g_lut_y, sizeof(stObcLut_e60_o22.head_g_lut_y));
					memcpy(param_e60_o22.head_b_lut_x, stObcLut_e60_o22.head_b_lut_x, sizeof(stObcLut_e60_o22.head_b_lut_x));
					memcpy(param_e60_o22.head_b_lut_y, stObcLut_e60_o22.head_b_lut_y, sizeof(stObcLut_e60_o22.head_b_lut_y));
					memcpy(param_e60_o22.head_r_lut_x, stObcLut_e60_o22.head_r_lut_x, sizeof(stObcLut_e60_o22.head_r_lut_x));
					memcpy(param_e60_o22.head_r_lut_y, stObcLut_e60_o22.head_r_lut_y, sizeof(stObcLut_e60_o22.head_r_lut_y));
					memcpy(param_e60_o22.body_g_lut_x, stObcLut_e60_o22.body_g_lut_x, sizeof(stObcLut_e60_o22.body_g_lut_x));
					memcpy(param_e60_o22.body_g_lut_y, stObcLut_e60_o22.body_g_lut_y, sizeof(stObcLut_e60_o22.body_g_lut_y));
					memcpy(param_e60_o22.body_b_lut_x, stObcLut_e60_o22.body_b_lut_x, sizeof(stObcLut_e60_o22.body_b_lut_x));
					memcpy(param_e60_o22.body_b_lut_y, stObcLut_e60_o22.body_b_lut_y, sizeof(stObcLut_e60_o22.body_b_lut_y));
					memcpy(param_e60_o22.body_r_lut_x, stObcLut_e60_o22.body_r_lut_x, sizeof(stObcLut_e60_o22.body_r_lut_x));
					memcpy(param_e60_o22.body_r_lut_y, stObcLut_e60_o22.body_r_lut_y, sizeof(stObcLut_e60_o22.body_r_lut_y));
					ret = PE_SHP_SetObcLUT((void *)&param_e60_o22);
					if (ret)
					{
						PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
					}
					else
					{
						if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut_e60_o22, pqData.version))
						{
							PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
						}
					}
				}
			}
			else if(PE_KDRV_VER_O20)
			{
				memset(&stObcLut, 0x00, sizeof(stObcLut));

				if (copy_from_user(&stObcLut, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				PE_PRINT_OBC_LUT(
					"[%s.%d] OBC LUT \n"\
					"pqData.p_data: %p, pqData.length: %d,\n"\
					"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"face_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"face_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"face_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
					"face_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n",\
					__F__, __L__,\
					pqData.p_data, pqData.length,\
					stObcLut.object_fg_x[0],stObcLut.object_fg_x[1],stObcLut.object_fg_x[2],stObcLut.object_fg_x[3], \
					stObcLut.object_fg_x[4],stObcLut.object_fg_x[5],stObcLut.object_fg_x[6],stObcLut.object_fg_x[7], \
					stObcLut.object_fg_y[0],stObcLut.object_fg_y[1],stObcLut.object_fg_y[2],stObcLut.object_fg_y[3], \
					stObcLut.object_fg_y[4],stObcLut.object_fg_y[5],stObcLut.object_fg_y[6],stObcLut.object_fg_y[7], \
					stObcLut.object_bg_x[0],stObcLut.object_bg_x[1],stObcLut.object_bg_x[2],stObcLut.object_bg_x[3], \
					stObcLut.object_bg_x[4],stObcLut.object_bg_x[5],stObcLut.object_bg_x[6],stObcLut.object_bg_x[7], \
					stObcLut.object_bg_y[0],stObcLut.object_bg_y[1],stObcLut.object_bg_y[2],stObcLut.object_bg_y[3], \
					stObcLut.object_bg_y[4],stObcLut.object_bg_y[5],stObcLut.object_bg_y[6],stObcLut.object_bg_y[7], \
					stObcLut.face_fg_x[0],stObcLut.face_fg_x[1],stObcLut.face_fg_x[2],stObcLut.face_fg_x[3], \
					stObcLut.face_fg_x[4],stObcLut.face_fg_x[5],stObcLut.face_fg_x[6],stObcLut.face_fg_x[7], \
					stObcLut.face_fg_y[0],stObcLut.face_fg_y[1],stObcLut.face_fg_y[2],stObcLut.face_fg_y[3], \
					stObcLut.face_fg_y[4],stObcLut.face_fg_y[5],stObcLut.face_fg_y[6],stObcLut.face_fg_y[7], \
					stObcLut.face_bg_x[0],stObcLut.face_bg_x[1],stObcLut.face_bg_x[2],stObcLut.face_bg_x[3], \
					stObcLut.face_bg_x[4],stObcLut.face_bg_x[5],stObcLut.face_bg_x[6],stObcLut.face_bg_x[7], \
					stObcLut.face_bg_y[0],stObcLut.face_bg_y[1],stObcLut.face_bg_y[2],stObcLut.face_bg_y[3], \
					stObcLut.face_bg_y[4],stObcLut.face_bg_y[5],stObcLut.face_bg_y[6],stObcLut.face_bg_y[7]);
				param.win_id = LX_PE_WIN_0;
				memcpy(&param.object_fg_x, stObcLut.object_fg_x, sizeof(stObcLut.object_fg_x));
				memcpy(&param.object_fg_y, stObcLut.object_fg_y, sizeof(stObcLut.object_fg_y));
				memcpy(&param.object_bg_x, stObcLut.object_bg_x, sizeof(stObcLut.object_bg_x));
				memcpy(&param.object_bg_y, stObcLut.object_bg_y, sizeof(stObcLut.object_bg_y));
				memcpy(&param.face_fg_x,   stObcLut.face_fg_x,   sizeof(stObcLut.face_fg_x));
				memcpy(&param.face_fg_y,   stObcLut.face_fg_y,   sizeof(stObcLut.face_fg_y));
				memcpy(&param.face_bg_x,   stObcLut.face_bg_x,   sizeof(stObcLut.face_bg_x));
				memcpy(&param.face_bg_y,   stObcLut.face_bg_y,   sizeof(stObcLut.face_bg_y));
				ret = KWRAP_PE_SetObcLUT((void *)&param);
				if (ret)
				{
					PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			#endif
		} break;
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		{
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_CTRL- V4L2_CID_EXT_VPQ_BASE])
				break;
			if(pqData.version == 0x40) // webos22 o22, temporally M23 for SOCTS
			{
				vpq_hwrap_obc_ctrl_o22_t stObcCtrl_o22;
				LX_PE_VSD_OBC4_CONT_T param_o22;
				/* version definition
				   chip O20 : version = 1 (default)
				        E60 : version = 3x.
				        O22 : version = 0x4x
				*/
				memset(&stObcCtrl_o22, 0x00, sizeof(stObcCtrl_o22));

				if (copy_from_user(&stObcCtrl_o22, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				param_o22.win_id = pqData.wid;
				memcpy(&param_o22.head_gain_x, &stObcCtrl_o22, sizeof(stObcCtrl_o22));
				PE_PRINT_OBC("[%s.%d] OBC CTRL\n"\
					"head_gain_x0,x1,x2,x3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"head_gain_y0,y1,y2,y3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"body_gain_x0,x1,x2,x3: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"body_gain_y0,y1,y2,y3: 0x%02X,0x%02X,0x%02X,0x%02X\n",\
					__F__, __L__,\
					stObcCtrl_o22.head_gain_x[0],stObcCtrl_o22.head_gain_x[1],\
					stObcCtrl_o22.head_gain_x[2],stObcCtrl_o22.head_gain_x[3],\
					stObcCtrl_o22.head_gain_y[0],stObcCtrl_o22.head_gain_y[1],\
					stObcCtrl_o22.head_gain_y[2],stObcCtrl_o22.head_gain_y[3],\
					stObcCtrl_o22.body_gain_x[0],stObcCtrl_o22.body_gain_x[1],\
					stObcCtrl_o22.body_gain_x[2],stObcCtrl_o22.body_gain_x[3],\
					stObcCtrl_o22.body_gain_y[0],stObcCtrl_o22.body_gain_y[1],\
					stObcCtrl_o22.body_gain_y[2],stObcCtrl_o22.body_gain_y[3]);
				ret = PE_SHP_SetObcCtrl((void *)&param_o22);
				if (ret)
				{
					PE_PRINT_ERROR("KWRAP_PE_SetObcParam error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stObcCtrl_o22, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
			else if(PE_KDRV_VER_E60)
			{
				vpq_hwrap_obc_ctrl_e60_t stObcCtrl;
				LX_PE_VSD_OBC3_CONT_T param;
				/* version definition
				   chip O20 : version = 1 (default)
				        E60 : version = 3x.
				*/
				if(pqData.version == 30)
				{
					memset(&stObcCtrl, 0x00, sizeof(stObcCtrl));

					if (copy_from_user(&stObcCtrl, (void __user *)pqData.p_data, pqData.length))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
					param.win_id = pqData.wid;
					memcpy(&param.head_gain_x, &stObcCtrl, sizeof(stObcCtrl));
					PE_PRINT_OBC("[%s.%d] OBC CTRL\n"\
						"head_gain_x0,x1: 0x%02X,0x%02X\n"\
						"head_gain_y0,y1: 0x%02X,0x%02X\n"\
						"body_gain_x0,x1: 0x%02X,0x%02X\n"\
						"body_gain_y0,y1: 0x%02X,0x%02X\n",\
						__F__, __L__,\
						stObcCtrl.head_gain_x[0],stObcCtrl.head_gain_x[1],\
						stObcCtrl.head_gain_y[0],stObcCtrl.head_gain_y[1],\
						stObcCtrl.body_gain_x[0],stObcCtrl.body_gain_x[1],\
						stObcCtrl.body_gain_y[0],stObcCtrl.body_gain_y[1]);
					ret = PE_SHP_SetObcCtrl((void *)&param);
					if (ret)
					{
						PE_PRINT_ERROR("KWRAP_PE_SetObcParam error(%d)\n", ret);
					}
					else
					{
						if (v4l2_vpq_pe_save_param(ctrl->id, &stObcCtrl, pqData.version))
						{
							PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
						}
					}
				}
			}
			else if(PE_KDRV_VER_O20)
			{
				vpq_hwrap_obc_ctrl_t stObcCtrl;
				LX_PE_VSD_OBC2_CONT_T param;

				memset(&stObcCtrl, 0x00, sizeof(stObcCtrl));

				if (copy_from_user(&stObcCtrl, (void __user *)pqData.p_data, pqData.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				param.win_id = LX_PE_WIN_0;
				memcpy(&param.obj_fg_gain_x, &stObcCtrl, sizeof(stObcCtrl));
				PE_PRINT_OBC("[%s.%d] OBC CTRL\n"\
					"obj_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
					"obj_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
					"obj_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
					"obj_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
					"obj_sat_enable: 0x%02X, obj_ch_bst_enable:0x%02X \n"\
					"obj_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_fg_gain_x0,x1: 0x%02X,0x%02X\n"\
					"face_fg_gain_y0,y1: 0x%02X,0x%02X\n"\
					"face_bg_gain_x0,x1: 0x%02X,0x%02X\n"\
					"face_bg_gain_y0,y1: 0x%02X,0x%02X\n"\
					"face_sat_enable: 0x%02X, face_ch_bst_enable:0x%02X \n"\
					"face_yy_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_yy_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_cc_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_cc_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_cbst_lut_pts_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_cbst_lut_pts_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_obj_lut_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"face_obj_lut_y: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_face_lut_x: 0x%02X,0x%02X,0x%02X,0x%02X\n"\
					"obj_face_lut_y: 0x%02X,0x%02X,0x%02X,0x%02X\n",\
					__F__, __L__,\
					stObcCtrl.obj_fg_gain_x[0],stObcCtrl.obj_fg_gain_x[1],stObcCtrl.obj_fg_gain_y[0],stObcCtrl.obj_fg_gain_y[1], \
					stObcCtrl.obj_bg_gain_x[0],stObcCtrl.obj_bg_gain_x[1],stObcCtrl.obj_bg_gain_y[0],stObcCtrl.obj_bg_gain_y[1], \
					stObcCtrl.obj_sat_enable, stObcCtrl.obj_ch_bst_enable,\
					stObcCtrl.obj_yy_lut_pts_x[0],stObcCtrl.obj_yy_lut_pts_x[1],stObcCtrl.obj_yy_lut_pts_x[2],stObcCtrl.obj_yy_lut_pts_x[3],\
					stObcCtrl.obj_yy_lut_pts_y[0],stObcCtrl.obj_yy_lut_pts_y[1],stObcCtrl.obj_yy_lut_pts_y[2],stObcCtrl.obj_yy_lut_pts_y[3],\
					stObcCtrl.obj_cc_lut_pts_x[0],stObcCtrl.obj_cc_lut_pts_x[1],stObcCtrl.obj_cc_lut_pts_x[2],stObcCtrl.obj_cc_lut_pts_x[3],\
					stObcCtrl.obj_cc_lut_pts_y[0],stObcCtrl.obj_cc_lut_pts_y[1],stObcCtrl.obj_cc_lut_pts_y[2],stObcCtrl.obj_cc_lut_pts_y[3],\
					stObcCtrl.obj_cbst_lut_pts_x[0],stObcCtrl.obj_cbst_lut_pts_x[1],stObcCtrl.obj_cbst_lut_pts_x[2],stObcCtrl.obj_cbst_lut_pts_x[3],\
					stObcCtrl.face_cbst_lut_pts_y[0],stObcCtrl.face_cbst_lut_pts_y[1],stObcCtrl.face_cbst_lut_pts_y[2],stObcCtrl.face_cbst_lut_pts_y[3],\
					stObcCtrl.face_fg_gain_x[0],stObcCtrl.face_fg_gain_x[1],stObcCtrl.face_fg_gain_y[0],stObcCtrl.face_fg_gain_y[1], \
					stObcCtrl.face_bg_gain_x[0],stObcCtrl.face_bg_gain_x[1],stObcCtrl.face_bg_gain_y[0],stObcCtrl.face_bg_gain_y[1], \
					stObcCtrl.face_sat_enable, stObcCtrl.face_ch_bst_enable,\
					stObcCtrl.face_yy_lut_pts_x[0],stObcCtrl.face_yy_lut_pts_x[1],stObcCtrl.face_yy_lut_pts_x[2],stObcCtrl.face_yy_lut_pts_x[3],\
					stObcCtrl.face_yy_lut_pts_y[0],stObcCtrl.face_yy_lut_pts_y[1],stObcCtrl.face_yy_lut_pts_y[2],stObcCtrl.face_yy_lut_pts_y[3],\
					stObcCtrl.face_cc_lut_pts_x[0],stObcCtrl.face_cc_lut_pts_x[1],stObcCtrl.face_cc_lut_pts_x[2],stObcCtrl.face_cc_lut_pts_x[3],\
					stObcCtrl.face_cc_lut_pts_y[0],stObcCtrl.face_cc_lut_pts_y[1],stObcCtrl.face_cc_lut_pts_y[2],stObcCtrl.face_cc_lut_pts_y[3],\
					stObcCtrl.face_cbst_lut_pts_x[0],stObcCtrl.face_cbst_lut_pts_x[1],stObcCtrl.face_cbst_lut_pts_x[2],stObcCtrl.face_cbst_lut_pts_x[3],\
					stObcCtrl.face_cbst_lut_pts_y[0],stObcCtrl.face_cbst_lut_pts_y[1],stObcCtrl.face_cbst_lut_pts_y[2],stObcCtrl.face_cbst_lut_pts_y[3],\
					stObcCtrl.face_obj_lut_x[0],stObcCtrl.face_obj_lut_x[1],stObcCtrl.face_obj_lut_x[2],stObcCtrl.face_obj_lut_x[3],\
					stObcCtrl.face_obj_lut_y[0],stObcCtrl.face_obj_lut_y[1],stObcCtrl.face_obj_lut_y[2],stObcCtrl.face_obj_lut_y[3],\
					stObcCtrl.obj_face_lut_x[0],stObcCtrl.obj_face_lut_x[1],stObcCtrl.obj_face_lut_x[2],stObcCtrl.obj_face_lut_x[3],\
					stObcCtrl.obj_face_lut_y[0],stObcCtrl.obj_face_lut_y[1],stObcCtrl.obj_face_lut_y[2],stObcCtrl.obj_face_lut_y[3]);
				ret = KWRAP_PE_SetObcParam((void *)&param);
				if (ret)
				{
					PE_PRINT_ERROR("KWRAP_PE_SetObcParam error(%d)\n", ret);
				}
				else
				{
					if (v4l2_vpq_pe_save_param(ctrl->id, &stObcCtrl, pqData.version))
					{
						PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
					}
				}
			}
		} break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			LX_PE_CMG_EXT_PATTERN_INFO_T stParam = { 0, };
			struct vpq_hwrap_ext_pattern_info stExtPtnInfo;
			struct v4l2_vpq_ext_pattern_winbox_info *pstWinboxInfo;
			struct v4l2_vpq_ext_pattern_gradation_info *pstGradInfo;
			int i;
			if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_EXTRA_PATTERN- V4L2_CID_EXT_VPQ_BASE])
				break;
			if (copy_from_user(&stExtPtnInfo, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			pstWinboxInfo = &stExtPtnInfo.stWinboxInfo;
			pstGradInfo = &stExtPtnInfo.stGradInfo;
			stParam.win_id = pqData.wid;
			stParam.bOnOff = (UINT32)stExtPtnInfo.bOnOff;
			stParam.eMode = (LX_PE_EXT_PATTERN_MODE_T)stExtPtnInfo.eMode;
			PE_PRINT_NOTI("win_id: %d bOnOff : %d, eMode: %d\n", stParam.win_id, stParam.bOnOff,stParam.eMode);
			if (!stExtPtnInfo.bOnOff)
			{
				PE_PRINT_NOTI("[%s.%d] OFF\n", __F__, __L__);
			}
			else if (stExtPtnInfo.eMode == V4L2_VPQ_EXT_PATTERN_WINBOX)
			{
				#if 1
				stParam.stWinboxInfo.u8NumWin = (UINT32)pstWinboxInfo->u8NumWin;
				for (i = 0; i < MAX_EXT_PATTERN_WINBOX; i++)
				{
					stParam.stWinboxInfo.stWinBoxAttr[i].winIdx = pstWinboxInfo->stWinBoxAttr[i].winIdx;
					stParam.stWinboxInfo.stWinBoxAttr[i].x = pstWinboxInfo->stWinBoxAttr[i].x;
					stParam.stWinboxInfo.stWinBoxAttr[i].y = pstWinboxInfo->stWinBoxAttr[i].y;
					stParam.stWinboxInfo.stWinBoxAttr[i].w = pstWinboxInfo->stWinBoxAttr[i].w;
					stParam.stWinboxInfo.stWinBoxAttr[i].h = pstWinboxInfo->stWinBoxAttr[i].h;
					stParam.stWinboxInfo.stWinBoxAttr[i].fill_R = pstWinboxInfo->stWinBoxAttr[i].fill_R;
					stParam.stWinboxInfo.stWinBoxAttr[i].fill_G = pstWinboxInfo->stWinBoxAttr[i].fill_G;
					stParam.stWinboxInfo.stWinBoxAttr[i].fill_B = pstWinboxInfo->stWinBoxAttr[i].fill_B;
				}
				#else
				if (copy_from_user(&(stParam.stWinboxInfo), (void __user *)stExtPtnInfo.stWinboxInfo, sizeof(vpq_hwrap_ext_pattern_winbox_info_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				#endif
			}
			else if (stExtPtnInfo.eMode == V4L2_VPQ_EXT_PATTERN_GRADATION)
			{
				#if 1
				stParam.stGradInfo.numGrad = (UINT32)pstGradInfo->numGrad;
				stParam.stGradInfo.eGradMode =
					(LX_PE_EXT_PATTERN_GRADATION_DIRECTION_T)pstGradInfo->eGradMode;
				for (i = 0; i < MAX_EXT_PATTERN_GRADATION_LINE; i++)
				{
					stParam.stGradInfo.stLineAttr[i].lineIdx = pstGradInfo->stLineAttr[i].lineIdx;
					stParam.stGradInfo.stLineAttr[i].start_R = pstGradInfo->stLineAttr[i].start_R;
					stParam.stGradInfo.stLineAttr[i].start_G = pstGradInfo->stLineAttr[i].start_G;
					stParam.stGradInfo.stLineAttr[i].start_B = pstGradInfo->stLineAttr[i].start_B;
					stParam.stGradInfo.stLineAttr[i].step_R = pstGradInfo->stLineAttr[i].step_R;
					stParam.stGradInfo.stLineAttr[i].step_G = pstGradInfo->stLineAttr[i].step_G;
					stParam.stGradInfo.stLineAttr[i].step_B = pstGradInfo->stLineAttr[i].step_B;
					stParam.stGradInfo.stLineAttr[i].strideSize = pstGradInfo->stLineAttr[i].strideSize;
				}
				#else
				if (copy_from_user(&(stParam.stGradInfo), (void __user *)stExtPtnInfo.pstGradInfo, sizeof(vpq_hwrap_ext_pattern_gradation_info_t)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				#endif
			}
			else
			{
				stParam.bOnOff = 0;
			}

			if (PE_KDRV_VER_O20)
			{
				ret = KWRAP_PE_SetExtInnerPattern(&stParam);
			}
			else
			{
				ret = PE_CMG_SetExtInnerPattern(&stParam);
			}
			if (ret)
			{
				PE_PRINT_ERROR("KWRAP_PE_SetExtInnerPattern error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &stExtPtnInfo, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		}
		break;
		case V4L2_CID_EXT_VPQ_DB_DATA:
		{
			vpq_hwrap_dc_db_all_t DcData;
			vpq_hwrap_dc_db_all_t stDcDb;
			LX_PE_DCM_LIB_DB_ALL_T *p_param;
			UINT32 sizeOfItem;
			UINT32 lengthOfData;
			UINT32 sizeOfData;
			UINT32 *p_dcm;
			int i;

			PE_PRINT_NOTI("[%s.%d] version = 0x%02X, length = %d\n",__F__, __L__,pqData.version, pqData.length);
			memset(&DcData, 0x00, sizeof(DcData));
			if (copy_from_user(&DcData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			memcpy(&stDcDb, &DcData, pqData.length);
			//1.copy dynContDB from user
			if(DcData.dynContDB.pAddrData)
			{
				sizeOfItem   =stDcDb.dynContDB.sizeOfItem;
				lengthOfData =stDcDb.dynContDB.lengthOfData;
				sizeOfData   =stDcDb.dynContDB.sizeOfData;
				if(sizeOfItem * lengthOfData == sizeOfData)
				{
					if (!(stDcDb.dynContDB.pAddrData = OS_Malloc(sizeOfData*sizeof(UINT32))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(stDcDb.dynContDB.pAddrData, (void __user *)DcData.dynContDB.pAddrData,sizeOfData*sizeof(UINT32)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
				}
				else
				{
					PE_PRINT_ERROR("size mismatch error\n");
					return -ENOMEM;
				}
			}
			//2.copy aplDB from user
			if(DcData.aplDB.pAddrData)
			{
				sizeOfItem   =stDcDb.aplDB.sizeOfItem;
				lengthOfData =stDcDb.aplDB.lengthOfData;
				sizeOfData   =stDcDb.aplDB.sizeOfData;
				if(sizeOfItem * lengthOfData == sizeOfData)
				{
					if (!(stDcDb.aplDB.pAddrData = OS_Malloc(sizeOfData*sizeof(UINT32))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(stDcDb.aplDB.pAddrData, (void __user *)DcData.aplDB.pAddrData,sizeOfData*sizeof(UINT32)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
				}
				else
				{
					PE_PRINT_ERROR("size mismatch error\n");
					return -ENOMEM;
				}
			}
			//3.copy aiGainDB from user
			if(DcData.aiGainDB.pAddrData)
			{
				sizeOfItem   =stDcDb.aiGainDB.sizeOfItem;
				lengthOfData =stDcDb.aiGainDB.lengthOfData;
				sizeOfData   =stDcDb.aiGainDB.sizeOfData;
				if(sizeOfItem * lengthOfData == sizeOfData)
				{
					if (!(stDcDb.aiGainDB.pAddrData = OS_Malloc(sizeOfData*sizeof(UINT32))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(stDcDb.aiGainDB.pAddrData, (void __user *)DcData.aiGainDB.pAddrData,sizeOfData*sizeof(UINT32)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
				}
				else
				{
					PE_PRINT_ERROR("size mismatch error\n");
					return -ENOMEM;
				}
			}
			//4.copy stabilzerDB from user
			if(DcData.stabilzerDB.pAddrData)
			{
				sizeOfItem   =stDcDb.stabilzerDB.sizeOfItem;
				lengthOfData =stDcDb.stabilzerDB.lengthOfData;
				sizeOfData   =stDcDb.stabilzerDB.sizeOfData;
				if(sizeOfItem * lengthOfData == sizeOfData)
				{
					if (!(stDcDb.stabilzerDB.pAddrData = OS_Malloc(sizeOfData*sizeof(UINT32))))
					{
						PE_PRINT_ERROR("OS_Malloc error\n");
						return -ENOMEM;
					}
					if (copy_from_user(stDcDb.stabilzerDB.pAddrData, (void __user *)DcData.stabilzerDB.pAddrData,sizeOfData*sizeof(UINT32)))
					{
						PE_PRINT_ERROR("copy_from_user error\n");
					}
				}
				else
				{
					PE_PRINT_ERROR("size mismatch error\n");
					return -ENOMEM;
				}
			}
			p_param = (LX_PE_DCM_LIB_DB_ALL_T *)&stDcDb;
			PE_PRINT_NOTI("[%s.%d] DC lib DB info\n"\
				"dynContDB   sizeOfItem, lengthOfData, sizeOfData: %d, %d, %d\n"\
				"aplDB       sizeOfItem, lengthOfData, sizeOfData: %d, %d, %d\n"\
				"aiGainDB    sizeOfItem, lengthOfData, sizeOfData: %d, %d, %d\n"\
				"stabilzerDB sizeOfItem, lengthOfData, sizeOfData: %d, %d, %d\n",\
				__F__, __L__,\
				p_param->dynContDB.sizeOfItem,   p_param->dynContDB.lengthOfData,    p_param->dynContDB.sizeOfData,\
				p_param->aplDB.sizeOfItem,        p_param->aplDB.lengthOfData,        p_param->aplDB.sizeOfData,\
				p_param->aiGainDB.sizeOfItem,    p_param->aiGainDB.lengthOfData,     p_param->aiGainDB.sizeOfData,\
				p_param->stabilzerDB.sizeOfItem, p_param->stabilzerDB.lengthOfData, p_param->stabilzerDB.sizeOfData);
			PE_PRINT_NOTI("[%s.%d] new DB version = 0x%02X\n"\
				"contrast_gain: %d, %d, %d,%d, %d, %d,%d, %d, %d, %d\n"\
				"contrast_gain: %d, %d, %d,%d, %d, %d,%d\n",\
				__F__, __L__,pqData.version,\
				p_param->contrast_gain[0],p_param->contrast_gain[1],p_param->contrast_gain[2],p_param->contrast_gain[3],p_param->contrast_gain[4],\
				p_param->contrast_gain[5],p_param->contrast_gain[6],p_param->contrast_gain[7],p_param->contrast_gain[8],p_param->contrast_gain[9],\
				p_param->contrast_gain[10],p_param->contrast_gain[11],p_param->contrast_gain[12],p_param->contrast_gain[13],p_param->contrast_gain[14],\
				p_param->contrast_gain[15],p_param->contrast_gain[16]);
			PE_PRINT_DCM("[%s.%d] DC lib DB\n",__F__, __L__);
			p_dcm =(UINT32*)p_param->dynContDB.pAddrData;
			sizeOfItem   =p_param->dynContDB.sizeOfItem;
			lengthOfData =p_param->dynContDB.lengthOfData;
			for(i=0; i< sizeOfItem*lengthOfData; i++)
				PE_PRINT_DCM("[%s.%d] 0x%08X\n",__F__, __L__,p_dcm[i]);

			p_dcm =(UINT32*)p_param->aplDB.pAddrData;
			sizeOfItem   =p_param->aplDB.sizeOfItem;
			lengthOfData =p_param->aplDB.lengthOfData;
			for(i=0; i< sizeOfItem*lengthOfData; i++)
				PE_PRINT_DCM("[%s.%d] 0x%08X\n",__F__, __L__,p_dcm[i]);

			p_dcm =(UINT32*)p_param->aiGainDB.pAddrData;
			sizeOfItem   =p_param->aiGainDB.sizeOfItem;
			lengthOfData =p_param->aiGainDB.lengthOfData;
			for(i=0; i< sizeOfItem*lengthOfData; i++)
				PE_PRINT_DCM("[%s.%d] 0x%08X\n",__F__, __L__,p_dcm[i]);

			p_dcm =(UINT32*)p_param->stabilzerDB.pAddrData;
			sizeOfItem   =p_param->stabilzerDB.sizeOfItem;
			lengthOfData =p_param->stabilzerDB.lengthOfData;
			for(i=0; i< sizeOfItem*lengthOfData; i++)
				PE_PRINT_DCM("[%s.%d] 0x%08X\n",__F__, __L__,p_dcm[i]);
			ret = PE_DCM_SetDceDB((void *)p_param);
			if (ret)
			{
				PE_PRINT_ERROR("PE_DCM_SetDceDB error(%d)\n", ret);
			}
			if(stDcDb.dynContDB.pAddrData)    {OS_Free(stDcDb.dynContDB.pAddrData);}
			if(stDcDb.aplDB.pAddrData)         {OS_Free(stDcDb.aplDB.pAddrData);}
			if(stDcDb.aiGainDB.pAddrData)      {OS_Free(stDcDb.aiGainDB.pAddrData);}
			if(stDcDb.stabilzerDB.pAddrData)   {OS_Free(stDcDb.stabilzerDB.pAddrData);}
		}
		break;
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
		{
			__attribute__((unused)) vpq_hwrap_dbc_db_t DbcData;
			__attribute__((unused)) LX_PE_DCM_DBC_DB_T dbc_param;
			__attribute__((unused)) UINT32 sizeOfItem;
			__attribute__((unused)) UINT32 lengthOfData;
			__attribute__((unused)) UINT32 sizeOfData;
			__attribute__((unused)) UINT32 *p_dcm;
			__attribute__((unused)) int i;

			PE_PRINT_NOTI("[%s.%d]DELTA_BRIGHTNESS_CONPENSATION_LUT version = 0x%02X, length = %d\n",__F__, __L__,pqData.version, pqData.length);
			if(pqData.version != 0x50)
				return 0;
			memset(&DbcData, 0x00, sizeof(DbcData));
			if (copy_from_user(&DbcData, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			for(i = 0; i< VPQ_HWRAP_DELTA_BRIGHTNESS_CONPENSATION_LUT_SIZE; i++)
			{
				dbc_param.brightness_gain[i]=(UINT32)DbcData.brightness_gain[i];
				dbc_param.contrast_gain[i]=(UINT32)DbcData.contrast_gain[i];
				dbc_param.input_freq[i]=(UINT32)DbcData.input_freq[i];
			}
			PE_PRINT_NOTI("[%s.%d] DBC LUT DB \n"\
				"brightness_gain: %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"contrast_gain  : %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\n"\
				"input_freq     : %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\n",\
				__F__, __L__,\
				dbc_param.brightness_gain[0],dbc_param.brightness_gain[1],dbc_param.brightness_gain[2],dbc_param.brightness_gain[3],dbc_param.brightness_gain[4],\
				dbc_param.brightness_gain[5],dbc_param.brightness_gain[6],dbc_param.brightness_gain[7],dbc_param.brightness_gain[8],dbc_param.brightness_gain[9],\
				dbc_param.brightness_gain[10],dbc_param.brightness_gain[11],dbc_param.brightness_gain[12],dbc_param.brightness_gain[13],dbc_param.brightness_gain[14],\
				dbc_param.brightness_gain[15],dbc_param.brightness_gain[16],\
				dbc_param.contrast_gain[0],dbc_param.contrast_gain[1],dbc_param.contrast_gain[2],dbc_param.contrast_gain[3],dbc_param.contrast_gain[4],\
				dbc_param.contrast_gain[5],dbc_param.contrast_gain[6],dbc_param.contrast_gain[7],dbc_param.contrast_gain[8],dbc_param.contrast_gain[9],\
				dbc_param.contrast_gain[10],dbc_param.contrast_gain[11],dbc_param.contrast_gain[12],dbc_param.contrast_gain[13],dbc_param.contrast_gain[14],\
				dbc_param.contrast_gain[15],dbc_param.contrast_gain[16],\
				dbc_param.input_freq[0],dbc_param.input_freq[1],dbc_param.input_freq[2],dbc_param.input_freq[3],dbc_param.input_freq[4],\
				dbc_param.input_freq[5],dbc_param.input_freq[6],dbc_param.input_freq[7],dbc_param.input_freq[8],dbc_param.input_freq[9],\
				dbc_param.input_freq[10],dbc_param.input_freq[11],dbc_param.input_freq[12],dbc_param.input_freq[13],dbc_param.input_freq[14],\
				dbc_param.input_freq[15],dbc_param.input_freq[16]);
			ret = PE_DCM_SetDbcDB((void*)&dbc_param);
			if (ret)
			{
				PE_PRINT_ERROR("PE_DCM_HW_O22F22_DownloadDBCDb error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &DbcData, pqData.version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		}
		break;
		default:
			PE_PRINT_NOTI("vpq:id 0x%x set failed",ctrl->id);
			return -EINVAL;
	}
	return ret;
}
int vpq_get_ext_ctrl_pe(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		case V4L2_CID_EXT_VPQ_PSP:
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		case V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL:
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
		{
			if (v4l2_vpq_pe_get_param(ctrl->id, ctrl->ptr))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_get_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		} break;
		case V4L2_CID_EXT_VPQ_HISTO_DATA:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_vpq_dc2p_histodata_info data;
			static struct v4l2_ext_vpq_dc2p_histodata_info pre_data;
			vpq_hwrap_ext_histodata_info data2;
			static vpq_hwrap_ext_histodata_info pre_data2;
			unsigned char *p_user_data;

			if(copy_from_user(&param, (void __user *)ctrl->string, sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(param.version == 1)
			{
				if(copy_from_user(&data, (void __user *)param.p_data, param.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				p_user_data = param.p_data;
				param.p_data = (unsigned char *)&data;

				if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_HISTO_DATA- V4L2_CID_EXT_VPQ_BASE])
				{
					memcpy(&data, &pre_data, param.length);
					if(copy_to_user((void __user *)p_user_data, &data, param.length))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					break;
				}
				if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
					ret = vpq_hwrap_gethistodata_o24(&param);
				else
					ret = vpq_hwrap_gethistodata(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_gethistodata error(%d)\n",ret);
					break;
				}
				if(copy_to_user((void __user *)p_user_data, &data, param.length))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				memcpy(&pre_data, &data, param.length);
				PE_PRINT_HST("[%s.%d][win:%d] hist version:%d, len:%d\n"\
					"apl, min,max, peak low,high,:%d, %d,%d, %d,%d\n"\
					"skin_count, sat_status,diff_sum,motion,texture:%d,%d,%d,%d,%d\n",\
					__F__, __L__,\
					param.wid, param.version, param.length,\
					data.apl,data.min,data.max,data.peak_low,data.peak_high, \
					data.skin_count,data.sat_status,data.diff_sum,data.motion,data.texture);
				PE_PRINT_HST("[%s.%d] hist0 Y\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data.bin[0],data.bin[1],data.bin[2],data.bin[3],data.bin[4],data.bin[5],data.bin[6],data.bin[7],\
					data.bin[8],data.bin[9],data.bin[10],data.bin[11],data.bin[12],data.bin[13],data.bin[14],data.bin[15],\
					data.bin[16],data.bin[17],data.bin[18],data.bin[19],data.bin[20],data.bin[21],data.bin[22],data.bin[23],\
					data.bin[24],data.bin[25],data.bin[26],data.bin[27],data.bin[28],data.bin[29],data.bin[30],data.bin[31],\
					data.bin[32],data.bin[33],data.bin[34],data.bin[35],data.bin[36],data.bin[37],data.bin[38],data.bin[39],\
					data.bin[40],data.bin[41],data.bin[42],data.bin[43],data.bin[44],data.bin[45],data.bin[46],data.bin[47],\
					data.bin[48],data.bin[49],data.bin[50],data.bin[51],data.bin[52],data.bin[53],data.bin[54],data.bin[55],\
					data.bin[56],data.bin[57],data.bin[58],data.bin[59],data.bin[60],data.bin[61],data.bin[62],data.bin[63]);
				PE_PRINT_HST("[%s.%d] hist chroma\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data.chrm_bin[0],data.chrm_bin[1],data.chrm_bin[2],data.chrm_bin[3],data.chrm_bin[4],data.chrm_bin[5],data.chrm_bin[6],data.chrm_bin[7],\
					data.chrm_bin[8],data.chrm_bin[9],data.chrm_bin[10],data.chrm_bin[11],data.chrm_bin[12],data.chrm_bin[13],data.chrm_bin[14],data.chrm_bin[15],\
					data.chrm_bin[16],data.chrm_bin[17],data.chrm_bin[18],data.chrm_bin[19],data.chrm_bin[20],data.chrm_bin[21],data.chrm_bin[22],data.chrm_bin[23],\
					data.chrm_bin[24],data.chrm_bin[25],data.chrm_bin[26],data.chrm_bin[27],data.chrm_bin[28],data.chrm_bin[29],data.chrm_bin[30],data.chrm_bin[31]);
				PE_PRINT_HST("[%s.%d] hist hue\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data.hue_bin[0],data.hue_bin[1],data.hue_bin[2],data.hue_bin[3],data.hue_bin[4],data.hue_bin[5],data.hue_bin[6],data.hue_bin[7],\
					data.hue_bin[8],data.hue_bin[9],data.hue_bin[10],data.hue_bin[11],data.hue_bin[12],data.hue_bin[13],data.hue_bin[14],data.hue_bin[15],\
					data.hue_bin[16],data.hue_bin[17],data.hue_bin[18],data.hue_bin[19],data.hue_bin[20],data.hue_bin[21],data.hue_bin[22],data.hue_bin[23],\
					data.hue_bin[24],data.hue_bin[25],data.hue_bin[26],data.hue_bin[27],data.hue_bin[28],data.hue_bin[29],data.hue_bin[30],data.hue_bin[31]);
			}
			else if(param.version == 2)
			{
				if(copy_from_user(&data2, (void __user *)param.p_data, param.length))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				p_user_data = param.p_data;
				param.p_data = (unsigned char *)&data2;

				if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_HISTO_DATA- V4L2_CID_EXT_VPQ_BASE])
				{
					memcpy(&data2, &pre_data2, param.length);
					if(copy_to_user((void __user *)p_user_data, &data2, param.length))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					break;
				}
				if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)
					ret = vpq_hwrap_gethistodata_o24(&param);
				else
					ret = vpq_hwrap_gethistodata(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_gethistodata error(%d)\n",ret);
					break;
				}
				if(copy_to_user((void __user *)p_user_data, &data2, param.length))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				memcpy(&pre_data2, &data2, param.length);
				
				PE_PRINT_HST("[%s.%d] hist version:%d\n"\
					"apl, min,max, peak low,high,:%d, %d,%d, %d,%d\n"\
					"skin_count, sat_status,diff_sum,motion,texture:%d,%d,%d,%d,%d\n",\
					__F__, __L__,\
					param.version, \
					data2.apl,data2.min,data2.max,data2.peak_low,data2.peak_high, \
					data2.skin_count,data2.sat_status,data2.diff_sum,data2.motion,data2.texture);
				PE_PRINT_HST("[%s.%d] hist0 Y\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data2.bin[0],data2.bin[1],data2.bin[2],data2.bin[3],data2.bin[4],data2.bin[5],data2.bin[6],data2.bin[7],\
					data2.bin[8],data2.bin[9],data2.bin[10],data2.bin[11],data2.bin[12],data2.bin[13],data2.bin[14],data2.bin[15],\
					data2.bin[16],data2.bin[17],data2.bin[18],data2.bin[19],data2.bin[20],data2.bin[21],data2.bin[22],data2.bin[23],\
					data2.bin[24],data2.bin[25],data2.bin[26],data2.bin[27],data2.bin[28],data2.bin[29],data2.bin[30],data2.bin[31],\
					data2.bin[32],data2.bin[33],data2.bin[34],data2.bin[35],data2.bin[36],data2.bin[37],data2.bin[38],data2.bin[39],\
					data2.bin[40],data2.bin[41],data2.bin[42],data2.bin[43],data2.bin[44],data2.bin[45],data2.bin[46],data2.bin[47],\
					data2.bin[48],data2.bin[49],data2.bin[50],data2.bin[51],data2.bin[52],data2.bin[53],data2.bin[54],data2.bin[55],\
					data2.bin[56],data2.bin[57],data2.bin[58],data2.bin[59],data2.bin[60],data2.bin[61],data2.bin[62],data2.bin[63],\
					data2.bin[64],	data2.bin[65],	data2.bin[66],	data2.bin[67],	data2.bin[68],	data2.bin[69],	data2.bin[70],	data2.bin[71],\
					data2.bin[72],	data2.bin[73],	data2.bin[74],	data2.bin[75],	data2.bin[76],	data2.bin[77],	data2.bin[78],	data2.bin[79],\
					data2.bin[80],	data2.bin[81],	data2.bin[82],	data2.bin[83],	data2.bin[84],	data2.bin[85],	data2.bin[86],	data2.bin[87],\
					data2.bin[88],	data2.bin[89],	data2.bin[90],	data2.bin[91],	data2.bin[92],	data2.bin[93],	data2.bin[94],	data2.bin[95],\
					data2.bin[96],	data2.bin[97],	data2.bin[98],	data2.bin[99],	data2.bin[100], data2.bin[101], data2.bin[102], data2.bin[103],\
					data2.bin[104], data2.bin[105], data2.bin[106], data2.bin[107], data2.bin[108], data2.bin[109], data2.bin[110], data2.bin[111],\
					data2.bin[112], data2.bin[113], data2.bin[114], data2.bin[115], data2.bin[116], data2.bin[117], data2.bin[118], data2.bin[119],\
					data2.bin[120], data2.bin[121], data2.bin[122], data2.bin[123], data2.bin[124], data2.bin[125], data2.bin[126], data2.bin[127]);
				PE_PRINT_HST("[%s.%d] hist chroma\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data2.chrm_bin[0],data2.chrm_bin[1],data2.chrm_bin[2],data2.chrm_bin[3],data2.chrm_bin[4],data2.chrm_bin[5],data2.chrm_bin[6],data2.chrm_bin[7],\
					data2.chrm_bin[8],data2.chrm_bin[9],data2.chrm_bin[10],data2.chrm_bin[11],data2.chrm_bin[12],data2.chrm_bin[13],data2.chrm_bin[14],data2.chrm_bin[15],\
					data2.chrm_bin[16],data2.chrm_bin[17],data2.chrm_bin[18],data2.chrm_bin[19],data2.chrm_bin[20],data2.chrm_bin[21],data2.chrm_bin[22],data2.chrm_bin[23],\
					data2.chrm_bin[24],data2.chrm_bin[25],data2.chrm_bin[26],data2.chrm_bin[27],data2.chrm_bin[28],data2.chrm_bin[29],data2.chrm_bin[30],data2.chrm_bin[31]);
				PE_PRINT_HST("[%s.%d] hist hue\n"\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n "\
					"%03d, %03d, %03d, %03d, %03d, %03d, %03d, %03d,\n ",\
					__F__, __L__,\
					data2.hue_bin[0],data2.hue_bin[1],data2.hue_bin[2],data2.hue_bin[3],data2.hue_bin[4],data2.hue_bin[5],data2.hue_bin[6],data2.hue_bin[7],\
					data2.hue_bin[8],data2.hue_bin[9],data2.hue_bin[10],data2.hue_bin[11],data2.hue_bin[12],data2.hue_bin[13],data2.hue_bin[14],data2.hue_bin[15],\
					data2.hue_bin[16],data2.hue_bin[17],data2.hue_bin[18],data2.hue_bin[19],data2.hue_bin[20],data2.hue_bin[21],data2.hue_bin[22],data2.hue_bin[23],\
					data2.hue_bin[24],data2.hue_bin[25],data2.hue_bin[26],data2.hue_bin[27],data2.hue_bin[28],data2.hue_bin[29],data2.hue_bin[30],data2.hue_bin[31]);
			}
		} break;
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT:
		{
			struct v4l2_ext_vpq_cmn_data param;
			const SINT32 dc_bypass_lut[VPQ_HWRAP_NUM_TRANSCURVE] =
				{ 0, 64, 122, 181, 239, 298, 356, 415, 473, 532, 590, 649, 707, 766, 824, 882 };

			if (copy_from_user(&param, (void __user *)ctrl->string, sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if (!param.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				ret = -EINVAL;
			}
			else if ((ret = copy_to_user((void __user *)param.p_data, dc_bypass_lut, param.length)) != 0)
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_VPQ_PE("V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT: %d\n", ret);
		}break;
		case V4L2_CID_EXT_VPQ_OBC_DATA:
		{
			struct v4l2_ext_vpq_cmn_data param;
			vpq_hwrap_obc_data_t stObcData;
			vpq_hwrap_obc_data_e60_t stObcData_e60;
			vpq_hwrap_obc_data_o22_t stObcData_o22;
			LX_PE_DCM_OBC1_DATA_T stObcParam;
			LX_PE_VSD_OBC1_DATA_T stObcParam_e60;
			LX_PE_VSD_OBC2_DATA_T stObcParam_o22;
			static vpq_hwrap_obc_data_t pre_stObcData;
			static vpq_hwrap_obc_data_e60_t pre_stObcData_e60;
			static vpq_hwrap_obc_data_o22_t pre_stObcData_o22;

			if (copy_from_user(&param, (void __user *)ctrl->string, sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			/* version definition
			   chip O20 : version = 1 (default)
			        E60 : version = 3x.
			*/
			if(param.version == 0x40 || param.version == 40)//webos4tv7.0 O22, temporally M23
			{
				if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_DATA- V4L2_CID_EXT_VPQ_BASE])
				{
					memcpy(&stObcData_o22, &pre_stObcData_o22,	param.length);
					if(copy_to_user((void __user *)param.p_data, &stObcData_o22, param.length))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					break;
				}
				if (!param.p_data)
				{
					PE_PRINT_ERROR("p_data is null\n");
					ret = -EINVAL;
				}
				else
				{
					stObcParam_o22.win_id = LX_PE_WIN_0;
					ret = PE_SHP_GetObcData((void *)&stObcParam_o22);
					if (ret)
					{
						PE_PRINT_ERROR("PE_SHP_GetObcLUT error(%d)\n",ret);
						break;
					}
					memcpy(&stObcData_o22, &stObcParam_o22.head_apl, sizeof(stObcData_o22));
					PE_PRINT_OBC_DATA(
						"[%s.%d] obc data:\n"\
						"head_apl: %d\n"\
						"body_apl: %d\n"\
						"head_map_apl: %d\n"\
						"depth_map_apl: %d\n",\
						__F__, __L__,\
						stObcData_o22.head_apl,\
						stObcData_o22.body_apl,\
						stObcData_o22.head_map_apl,\
						stObcData_o22.depth_map_apl);
					if ((ret = copy_to_user((void __user *)param.p_data, &stObcData_o22, param.length)) != 0)
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					memcpy(&pre_stObcData_o22, &stObcData_o22, sizeof(vpq_hwrap_obc_data_o22_t));
				}
			}
			else if(PE_KDRV_VER_E60)
			{
				if(param.version == 30) // E60
				{
					if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_DATA- V4L2_CID_EXT_VPQ_BASE])
					{
						memcpy(&stObcData_e60, &pre_stObcData_e60,	param.length);
						if(copy_to_user((void __user *)param.p_data, &stObcData_e60, param.length))
						{
							PE_PRINT_ERROR("copy_to_user error\n");
						}
						break;
					}
					if (!param.p_data)
					{
						PE_PRINT_ERROR("p_data is null\n");
						ret = -EINVAL;
					}
					else
					{
						stObcParam_e60.win_id = LX_PE_WIN_0;
						ret = PE_SHP_GetObcData((void *)&stObcParam_e60);
						if (ret)
						{
							PE_PRINT_ERROR("PE_SHP_GetObcLUT error(%d)\n",ret);
							break;
						}
						memcpy(&stObcData_e60, &stObcParam_e60.head_apl, sizeof(stObcData_e60));
						PE_PRINT_OBC_DATA(
							"[%s.%d] obc data:\n"\
							"head_apl: %d\n"\
							"body_apl: %d\n",\
							__F__, __L__,\
							stObcData_e60.head_apl,\
							stObcData_e60.body_apl);
						if ((ret = copy_to_user((void __user *)param.p_data, &stObcData_e60, param.length)) != 0)
						{
							PE_PRINT_ERROR("copy_to_user error\n");
						}
						memcpy(&pre_stObcData_e60, &stObcData_e60, sizeof(vpq_hwrap_obc_data_e60_t));
					}
				}
			}
			else
			{
				if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_DATA- V4L2_CID_EXT_VPQ_BASE])
				{
					memcpy(&stObcData, &pre_stObcData,	param.length);
					if(copy_to_user((void __user *)param.p_data, &stObcData, param.length))
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					break;
				}
				if (!param.p_data)
				{
					PE_PRINT_ERROR("p_data is null\n");
					ret = -EINVAL;
				}
				else
				{
					stObcParam.win_id = LX_PE_WIN_0;
					ret = KWRAP_PE_GetObcData((void *)&stObcParam);
					if (ret)
					{
						PE_PRINT_ERROR("KWRAP_PE_GetObcData error(%d)\n",ret);
						break;
					}
					memcpy(&stObcData, &stObcParam.object_relibility, sizeof(stObcData));
					PE_PRINT_OBC_DATA(
						"[%s.%d] obc data:\n"\
						"object_relibility: %d\n"\
						"object_fg_pel_num: %d\n"\
						"object_fg_apl:  %d\n"\
						"object_bg_pel_num: %d\n"\
						"object_bg_apl:  %d\n"\
						"object_boxh1:	 %d\n"\
						"object_boxh2:	 %d\n"\
						"object_boxw1:	 %d\n"\
						"object_boxw2:	 %d\n"\
						"face_relibility: %d\n"\
						"face_fg_pel_num: %d\n"\
						"face_fg_apl:  %d\n"\
						"face_bg_pel_num: %d\n"\
						"face_bg_apl:  %d\n"\
						"face_boxh1:	 %d\n"\
						"face_boxh2:	 %d\n"\
						"face_boxw1:	 %d\n"\
						"face_boxw2:	 %d\n",\
						__F__, __L__,\
						stObcData.object_relibility,\
						stObcData.object_fg_pel_num,\
						stObcData.object_fg_apl,\
						stObcData.object_bg_pel_num,\
						stObcData.object_bg_apl,\
						stObcData.object_boxh1,\
						stObcData.object_boxh2,\
						stObcData.object_boxw1,\
						stObcData.object_boxw2,\
						stObcData.face_relibility,\
						stObcData.face_fg_pel_num,\
						stObcData.face_fg_apl,\
						stObcData.face_bg_pel_num,\
						stObcData.face_bg_apl,\
						stObcData.face_boxh1,\
						stObcData.face_boxh2,\
						stObcData.face_boxw1,\
						stObcData.face_boxw2);
					if ((ret = copy_to_user((void __user *)param.p_data, &stObcData, param.length)) != 0)
					{
						PE_PRINT_ERROR("copy_to_user error\n");
					}
					memcpy(&pre_stObcData, &stObcData, sizeof(vpq_hwrap_obc_data_t));
				}
			}
			PE_PRINT_VPQ_PE("V4L2_CID_EXT_VPQ_OBC_DATA: %d\n", ret);
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
int vpq_proc_show_status_pe(struct seq_file *m, void *v, int id)
{
	__attribute__((unused)) int ret;
	unsigned int index;
	const char *input_type[V4L2_EXT_VPQ_INPUT_MAX+1] = {"atv","av","scartrgb",\
		"comp","rgb_pc","hdmi_tv","hdmi_pc","dtv","picwiz","pictest","media_movie",\
		"media_photo","camera","pvr_dtv","pvr_atv","pvr_av","max"};

	if (!m)	return 0;

	switch (id) {
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		{
			int *p = stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE];
			if (!p)
			{
				seq_printf(m, "0\n");
			}
			else
			{
				seq_printf(m, "%d\n",*p);
			}
		}break;
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		{
			seq_printf(m, "%d\n",uPqeParam[id - V4L2_CID_EXT_VPQ_BASE]);
		}break;
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		{
			struct v4l2_ext_vpq_picture_ctrl_data *p = (struct v4l2_ext_vpq_picture_ctrl_data*)stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE];
			if (!p)
			{
				seq_printf(m, "{picture_ui_value:{10,10,10,1},chipData_contrast:512,chipData_brightness:512,chipData_saturation:143,chipData_hue:128}\n");
			}
			else
			{
				seq_printf(m, "{picture_ui_value:{%d,%d,%d,%d},chipData_contrast:%d,chipData_brightness:%d,chipData_saturation:%d,chipData_hue:%d}\n",\
					p->picture_ui_value[0],p->picture_ui_value[1],p->picture_ui_value[2],p->picture_ui_value[3],\
					p->chipData_contrast,p->chipData_brightness,p->chipData_saturation,p->chipData_hue);
			}
		}break;
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		{
			struct v4l2_ext_vpq_black_level_info *p = (struct v4l2_ext_vpq_black_level_info*)stPqeParam.p[id - V4L2_CID_EXT_VPQ_BASE];
			if (!p)
			{
				seq_printf(m, "{ui_value:2,curr_input:hdmi_tv,color_space:1,black_level_type:10}\n");
			}
			else
			{
				index = (p->curr_input<V4L2_EXT_VPQ_INPUT_MAX)? p->curr_input:V4L2_EXT_VPQ_INPUT_MAX;
				seq_printf(m, "{ui_value:%d,curr_input:%s,color_space:%d,black_level_type:%d}\n",\
					p->ui_value,input_type[index],p->color_space,p->black_level_type);
			}
		}break;
		default:
			seq_printf(m, "{not support}\n");
			break;
	}

	return 0;
}

int vpq_proc_show_func_status_pe(void)
{
	int i;
	for(i = 1 ; i < V4L2_VPQ_PE_NUM_OF_FUNC; i++)
	{
		if( i==11 || i==14 || i==18 || (i>=20 && i<=22) ||(i>=26 && i<=30))
			printk("[%d] %s  : not support!!!!\n", i, vpq_ctrl_id_to_str(V4L2_CID_EXT_VPQ_BASE +i));
		else
			printk("[%d] %s  : %d\n", i, vpq_ctrl_id_to_str(V4L2_CID_EXT_VPQ_BASE +i),\
				_g_v4l2_vpq_pe_block_func[i]);
	}
	printk("[%d] default setting : %d\n", V4L2_VPQ_PE_NUM_OF_FUNC,_g_pe_kwrap_block_defaul_setting);
	printk("[%d] block all func        \n", 88);
	printk("[%d] off block all func        \n", 99);
	return 0;
}

int vpq_proc_set_block_func_pe(int num_func)
{
	int i;
	if(num_func == V4L2_VPQ_PE_NUM_OF_FUNC)
	{
		if(_g_pe_kwrap_block_defaul_setting == 0x0)
			_g_pe_kwrap_block_defaul_setting = 0x1;
		else
			_g_pe_kwrap_block_defaul_setting = 0x0;
	}
	else if(num_func == 88)
	{
		for(i = 1 ; i < V4L2_VPQ_PE_NUM_OF_FUNC; i++)
		{
			_g_v4l2_vpq_pe_block_func[i] = 0x1;
		}
		_g_pe_kwrap_block_defaul_setting = 0x1;
	}
	else if(num_func == 99)
	{
		for(i = 1 ; i < V4L2_VPQ_PE_NUM_OF_FUNC; i++)
		{
			_g_v4l2_vpq_pe_block_func[i] = 0x0;
		}
		_g_pe_kwrap_block_defaul_setting = 0x0;
	}
	else if( num_func==11 || num_func==14 || num_func==18 ||\
		(num_func>=20 && num_func<=22) ||(num_func>=26 && num_func<=30))
	{
		printk("not support!!!!\n");
	}
	else
	{
		if(_g_v4l2_vpq_pe_block_func[num_func] == 0x0)
			_g_v4l2_vpq_pe_block_func[num_func] = 0x1;
		else
			_g_v4l2_vpq_pe_block_func[num_func] = 0x0;
	}
	return 0;
}

int vpq_proc_init_block_func_pe(void)
{
	memset(_g_v4l2_vpq_pe_block_func, 0x0, sizeof(UINT32)*V4L2_VPQ_PE_NUM_OF_FUNC);
	return 0;
}

int vpq_proc_set_block_func_dftmode(int mode)
{
	if(mode)
	{
		PE_PRINT_NOTI("[DFT MODE] LGSR func block!!\n");
	}
	return 0;
}

int vpq_set_dynamic_contrast_lut(struct v4l2_ext_vpq_cmn_data *pqData, struct v4l2_ext_control *ctrl)
{
	/*version
	0x0:only for pioneer
	0x1, 0x2: old version before e60
	0x30:webos6.0 e60,o20, 
	0x40:webos7.0 o22, m23
	0x60:webos24 initial o24
	0x61:webos24 MR o24
	*/
	int ret = 0;
	LX_PE_DCM_DCE_LUT_T param;
	LX_PE_DCM_DRC_MODE_T drc_param;
	LX_PE_DCM_DTM_LUT_T dtm_param;
	LX_PE_DCM_DCE_LUT1_T dclut_param;
	LX_PE_DCM_DCE_LUT2_T dclut2_param;
	LX_PE_SHP_ELLIPS_LUT_T shp_ellips_param;
	UINT32 detected = 0;
	static UINT32 cnt_detected=0;
	//UINT32 addr0=0, val0;
	UINT16 *pDtmLut;
	signed int sDcBypassLut[PE_KWRAP_DCM_LUT_STEP] =
		{ 0, 64, 122, 181, 239, 298, 356, 415, 473, 532, 590, 649, 707, 766, 824, 882 };
	//signed int sLumaLUTxy[PE_KWRAP_DCM_LUT_STEP * 2] = { 0, };
	#if 0
	UINT32 sDtmbypassLut[33]=
	{0x000000, 0x020020, 0x040040, 0x060060, 0x080080, 0x0A00A0, 0x0C00C0, 0x0E00E0, 0x100100, 0x120120, \
	0x140140, 0x160160, 0x180180, 0x1A01A0, 0x1C01C0, 0x1E01E0, 0x200200, 0x21F21F, 0x23F23F, 0x25F25F, \
	0x27F27F, 0x29F29F, 0x2BF2BF, 0x2DF2DF, 0x2FF2FF, 0x31F31F, 0x33F33F, 0x35F35F, 0x37F37F, 0x3AC3AC, \
	0x3BF3BF, 0x3DF3DF, 0x3FF3FF};
	#endif
	__attribute__((unused)) UINT32 sDtmbypassLut[33] = {\
	   0,  64, 122, 181, 239, 298, 356, 415, 473, \
	 532, 590, 649, 707, 766, 824, 882, 940,1023, \
	1023,1023,1023,1023,1023,1023,1023,1023,1023, \
	1023,1023,1023,1023,1023,1023};
	#if 0
	UINT16 sDtmbNGLut[66]=
	{0x0000, 0x0040, 0x0080, 0x00C0, 0x0100, 0x0140, 0x0180, 0x01C0, 0x0200, 0x0240, \
	0x0280, 0x02C0, 0x0300, 0x0340, 0x0380, 0x03C0, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
	0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
	0x03FF, 0x03FF, 0x03FF, 0x0001, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
	0x03FF, 0x03FF, 0x03FF, 0x0303, 0x0349, 0x037b, 0x0399, 0x03B1, 0x03Cb, 0x03FF, \
	0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, \
	0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF, 0x03FF};
	#endif
	UINT8 i = 0, j = 0;
	UINT32 x_data = 0, y_data = 0;
	BOOLEAN drc_bypass = TRUE;
	//UINT32 *pLUT;
	__attribute__((unused)) vpq_hwrap_dynamic_lut_t stDcmLut;
	__attribute__((unused)) vpq_hwrap_dynamic_lut_pioneer_t stDcmLut_pioneer;
	//__attribute__((unused)) vpq_hwrap_dynamic_lut_webos60_t stDcmLut_webos60;
	__attribute__((unused)) vpq_hwrap_dynamic_lut_o24_t stDcmLut_webos24;
	if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT- V4L2_CID_EXT_VPQ_BASE])
		return ret;
	PE_PRINT_DCM_LUT("[%s.%d]version = %d, wid = %d, length = %d\n", \
		__F__, __L__,pqData->version,pqData->wid,pqData->length);
	
	/* DCE LUT S*/
	if(pqData->version == 0x61) // vpq_hwrap_dynamic_lut_o24_v2_t
	{
		if(!pDcmLut_webos24_v2)
			pDcmLut_webos24_v2 = OS_Malloc(sizeof(vpq_hwrap_dynamic_lut_o24_v2_t));
		if (copy_from_user(pDcmLut_webos24_v2, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		dclut2_param.win_id = LX_PE_WIN_0;
		PE_PRINT_DCM_LUT("DC LUT set: n");
		for (i = 0; i < 32; i++)
		{
			for (j =0 ; j < 4; j++)
			{
				x_data = (UINT32)pDcmLut_webos24_v2->sLumaLutX[j][i];
				y_data = (UINT32)pDcmLut_webos24_v2->sLumaLutY[j][i];
				if (x_data != y_data)
				{
					drc_bypass = FALSE;
				}
				
				if ((pqData->wid == 0 || pqData->wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
				{
					y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
				}
				dclut2_param.lumalut_x[j][i] = x_data;
				dclut2_param.lumalut_y[j][i] = y_data;
			}
			PE_PRINT_DCM_LUT("data[%2d] =[0] [%4d] [%4d] |[1] [%4d] [%4d] |[2] [%4d] [%4d] |[3] [%4d] [%4d]\n", \
				i, dclut2_param.lumalut_x[0][i], dclut2_param.lumalut_y[0][i], dclut2_param.lumalut_x[1][i], dclut2_param.lumalut_y[1][i],\
				 dclut2_param.lumalut_x[2][i], dclut2_param.lumalut_y[2][i],dclut2_param.lumalut_x[3][i], dclut2_param.lumalut_y[3][i]);
		}

		memcpy(dclut2_param.chroma_face_alpha_lut1_x,pDcmLut_webos24_v2->chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
		PE_PRINT_DCM_LUT(\
			"lut1_x: %d, %d, %d, %d\n" \
			"lut1_y: %d, %d, %d, %d\n" \
			"lut2_x: %d, %d, %d, %d\n" \
			"lut2_y: %d, %d, %d, %d\n", \
			pDcmLut_webos24_v2->chroma_face_alpha_lut1_x[0],pDcmLut_webos24_v2->chroma_face_alpha_lut1_x[1],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut1_x[2],pDcmLut_webos24_v2->chroma_face_alpha_lut1_x[3],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut1_y[0],pDcmLut_webos24_v2->chroma_face_alpha_lut1_y[1],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut1_y[2],pDcmLut_webos24_v2->chroma_face_alpha_lut1_y[3],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut2_x[0],pDcmLut_webos24_v2->chroma_face_alpha_lut2_x[1],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut2_x[2],pDcmLut_webos24_v2->chroma_face_alpha_lut2_x[3],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut2_y[0],pDcmLut_webos24_v2->chroma_face_alpha_lut2_y[1],\
			pDcmLut_webos24_v2->chroma_face_alpha_lut2_y[2],pDcmLut_webos24_v2->chroma_face_alpha_lut2_y[3]);
		if(pqData->wid == 0 || pqData->wid == 1) //o24, o22, e60, o20 only
		{
			ret = PE_DCM_SetDceLut2(&dclut2_param);
			if (ret)
			{
				PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
				return ret;
			}
		}
		shp_ellips_param.win_id = pqData->wid;
		memcpy(shp_ellips_param.shp_luma_ylut_2k,pDcmLut_webos24_v2->shp_luma_ylut_2k, sizeof(UINT8)*16);
		memcpy(shp_ellips_param.shp_luma_ylut_vsd,pDcmLut_webos24_v2->shp_luma_ylut_vsd, sizeof(UINT8)*16);
		ret = PE_SHP_SetEllipsCtrl(&shp_ellips_param);
		if (ret)
		{
			PE_PRINT_ERROR("PE_SHP_SetEllipsCtrl: error(%d)\n", ret);
			return ret;
		}
		PE_PRINT_DCM_LUT(\
		"Ellips Lut set: n"\
		"shp_luma_ylut_2k  0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
		"shp_luma_ylut_2k  8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
		"shp_luma_ylut_vsd 0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
		"shp_luma_ylut_vsd 8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
		pDcmLut_webos24_v2->shp_luma_ylut_2k[0],pDcmLut_webos24_v2->shp_luma_ylut_2k[1],pDcmLut_webos24_v2->shp_luma_ylut_2k[2],pDcmLut_webos24_v2->shp_luma_ylut_2k[3],\
		pDcmLut_webos24_v2->shp_luma_ylut_2k[4],pDcmLut_webos24_v2->shp_luma_ylut_2k[5],pDcmLut_webos24_v2->shp_luma_ylut_2k[6],pDcmLut_webos24_v2->shp_luma_ylut_2k[7],\
		pDcmLut_webos24_v2->shp_luma_ylut_2k[8],pDcmLut_webos24_v2->shp_luma_ylut_2k[9],pDcmLut_webos24_v2->shp_luma_ylut_2k[10],pDcmLut_webos24_v2->shp_luma_ylut_2k[11],\
		pDcmLut_webos24_v2->shp_luma_ylut_2k[12],pDcmLut_webos24_v2->shp_luma_ylut_2k[13],pDcmLut_webos24_v2->shp_luma_ylut_2k[14],pDcmLut_webos24_v2->shp_luma_ylut_2k[15],\
		pDcmLut_webos24_v2->shp_luma_ylut_vsd[0],pDcmLut_webos24_v2->shp_luma_ylut_vsd[1],pDcmLut_webos24_v2->shp_luma_ylut_vsd[2],pDcmLut_webos24_v2->shp_luma_ylut_vsd[3],\
		pDcmLut_webos24_v2->shp_luma_ylut_vsd[4],pDcmLut_webos24_v2->shp_luma_ylut_vsd[5],pDcmLut_webos24_v2->shp_luma_ylut_vsd[6],pDcmLut_webos24_v2->shp_luma_ylut_vsd[7],\
		pDcmLut_webos24_v2->shp_luma_ylut_vsd[8],pDcmLut_webos24_v2->shp_luma_ylut_vsd[9],pDcmLut_webos24_v2->shp_luma_ylut_vsd[10],pDcmLut_webos24_v2->shp_luma_ylut_vsd[11],\
		pDcmLut_webos24_v2->shp_luma_ylut_vsd[12],pDcmLut_webos24_v2->shp_luma_ylut_vsd[13],pDcmLut_webos24_v2->shp_luma_ylut_vsd[14],pDcmLut_webos24_v2->shp_luma_ylut_vsd[15]);
	}
	else if(pqData->version == 0x60 || pqData->version == 0x40 || pqData->version == 0x30)//0x30:webos6.0 e60,o20, 0x40:webos7.0
	{
		if (copy_from_user(&stDcmLut_webos24, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		if(PE_KDRV_VER_O24 || PE_KDRV_VER_O26)//o24  
		{
			dclut2_param.win_id = LX_PE_WIN_0;
			PE_PRINT_DCM_LUT("DC LUT set: n");
			for (i = 0; i < 32; i++)
			{
				x_data = (UINT32)stDcmLut_webos24.sLumaLutX[i];
				y_data = (UINT32)stDcmLut_webos24.sLumaLutY[i];
				if (x_data != y_data)
				{
					drc_bypass = FALSE;
				}
				
				if ((pqData->wid == 0 || pqData->wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
				{
					y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
				}
				dclut2_param.lumalut_x[0][i] = dclut2_param.lumalut_x[1][i] = dclut2_param.lumalut_x[2][i] =dclut2_param.lumalut_x[3][i] = x_data;
				dclut2_param.lumalut_y[0][i] = dclut2_param.lumalut_y[1][i] = dclut2_param.lumalut_y[2][i] =dclut2_param.lumalut_y[3][i] = y_data;
				PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
					i, dclut2_param.lumalut_x[0][i], dclut2_param.lumalut_y[0][i]);
			}

			memcpy(dclut2_param.chroma_face_alpha_lut1_x,stDcmLut_webos24.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
			PE_PRINT_DCM_LUT(\
				"lut1_x: %d, %d, %d, %d\n" \
				"lut1_y: %d, %d, %d, %d\n" \
				"lut2_x: %d, %d, %d, %d\n" \
				"lut2_y: %d, %d, %d, %d\n", \
				stDcmLut_webos24.chroma_face_alpha_lut1_x[0],stDcmLut_webos24.chroma_face_alpha_lut1_x[1],\
				stDcmLut_webos24.chroma_face_alpha_lut1_x[2],stDcmLut_webos24.chroma_face_alpha_lut1_x[3],\
				stDcmLut_webos24.chroma_face_alpha_lut1_y[0],stDcmLut_webos24.chroma_face_alpha_lut1_y[1],\
				stDcmLut_webos24.chroma_face_alpha_lut1_y[2],stDcmLut_webos24.chroma_face_alpha_lut1_y[3],\
				stDcmLut_webos24.chroma_face_alpha_lut2_x[0],stDcmLut_webos24.chroma_face_alpha_lut2_x[1],\
				stDcmLut_webos24.chroma_face_alpha_lut2_x[2],stDcmLut_webos24.chroma_face_alpha_lut2_x[3],\
				stDcmLut_webos24.chroma_face_alpha_lut2_y[0],stDcmLut_webos24.chroma_face_alpha_lut2_y[1],\
				stDcmLut_webos24.chroma_face_alpha_lut2_y[2],stDcmLut_webos24.chroma_face_alpha_lut2_y[3]);
			if(pqData->wid == 0 || pqData->wid == 1) //o24, o22, e60, o20 only
			{
				ret = PE_DCM_SetDceLut2(&dclut2_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
					return ret;
				}
			}
			shp_ellips_param.win_id = pqData->wid;
			memcpy(shp_ellips_param.shp_luma_ylut_2k,stDcmLut_webos24.shp_luma_ylut_2k, sizeof(UINT8)*16);
			memcpy(shp_ellips_param.shp_luma_ylut_vsd,stDcmLut_webos24.shp_luma_ylut_vsd, sizeof(UINT8)*16);
			ret = PE_SHP_SetEllipsCtrl(&shp_ellips_param);
			if (ret)
			{
				PE_PRINT_ERROR("PE_SHP_SetEllipsCtrl: error(%d)\n", ret);
				return ret;
			}
			PE_PRINT_DCM_LUT(\
			"Ellips Lut set: n"\
			"shp_luma_ylut_2k  0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
			"shp_luma_ylut_2k  8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
			"shp_luma_ylut_vsd 0~7 : 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n"\
			"shp_luma_ylut_vsd 8~15: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			stDcmLut_webos24.shp_luma_ylut_2k[0],stDcmLut_webos24.shp_luma_ylut_2k[1],stDcmLut_webos24.shp_luma_ylut_2k[2],stDcmLut_webos24.shp_luma_ylut_2k[3],\
			stDcmLut_webos24.shp_luma_ylut_2k[4],stDcmLut_webos24.shp_luma_ylut_2k[5],stDcmLut_webos24.shp_luma_ylut_2k[6],stDcmLut_webos24.shp_luma_ylut_2k[7],\
			stDcmLut_webos24.shp_luma_ylut_2k[8],stDcmLut_webos24.shp_luma_ylut_2k[9],stDcmLut_webos24.shp_luma_ylut_2k[10],stDcmLut_webos24.shp_luma_ylut_2k[11],\
			stDcmLut_webos24.shp_luma_ylut_2k[12],stDcmLut_webos24.shp_luma_ylut_2k[13],stDcmLut_webos24.shp_luma_ylut_2k[14],stDcmLut_webos24.shp_luma_ylut_2k[15],\
			stDcmLut_webos24.shp_luma_ylut_vsd[0],stDcmLut_webos24.shp_luma_ylut_vsd[1],stDcmLut_webos24.shp_luma_ylut_vsd[2],stDcmLut_webos24.shp_luma_ylut_vsd[3],\
			stDcmLut_webos24.shp_luma_ylut_vsd[4],stDcmLut_webos24.shp_luma_ylut_vsd[5],stDcmLut_webos24.shp_luma_ylut_vsd[6],stDcmLut_webos24.shp_luma_ylut_vsd[7],\
			stDcmLut_webos24.shp_luma_ylut_vsd[8],stDcmLut_webos24.shp_luma_ylut_vsd[9],stDcmLut_webos24.shp_luma_ylut_vsd[10],stDcmLut_webos24.shp_luma_ylut_vsd[11],\
			stDcmLut_webos24.shp_luma_ylut_vsd[12],stDcmLut_webos24.shp_luma_ylut_vsd[13],stDcmLut_webos24.shp_luma_ylut_vsd[14],stDcmLut_webos24.shp_luma_ylut_vsd[15]);
			
			if(pqData->wid == 0xF0 || pqData->wid == 0xF1) //o24+F22
			{
				ret = PE_DCM_SetDceLut3(&dclut2_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut3: error(%d)\n", ret);
					return ret;
				}
			}
		}
		else
		{
			dclut_param.win_id = LX_PE_WIN_0;
			PE_PRINT_DCM_LUT("DC LUT set: n");
			for (i = 0; i < 32; i++)
			{
				x_data = (UINT32)stDcmLut_webos24.sLumaLutX[i];
				y_data = (UINT32)stDcmLut_webos24.sLumaLutY[i];
				if (x_data != y_data)
				{
					drc_bypass = FALSE;
				}
				
				if ((pqData->wid == 0 || pqData->wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)//e60 only model
				{
					y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
				}
				dclut_param.lumalut_x[i] = x_data;
				dclut_param.lumalut_y[i] = y_data;
				PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
					i, dclut_param.lumalut_x[i], dclut_param.lumalut_y[i]);
			}
			memcpy(dclut_param.chroma_face_alpha_lut1_x,stDcmLut_webos24.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
			
			PE_PRINT_DCM_LUT(\
				"lut1_x: %d, %d, %d, %d\n" \
				"lut1_y: %d, %d, %d, %d\n" \
				"lut2_x: %d, %d, %d, %d\n" \
				"lut2_y: %d, %d, %d, %d\n", \
				stDcmLut_webos24.chroma_face_alpha_lut1_x[0],stDcmLut_webos24.chroma_face_alpha_lut1_x[1],\
				stDcmLut_webos24.chroma_face_alpha_lut1_x[2],stDcmLut_webos24.chroma_face_alpha_lut1_x[3],\
				stDcmLut_webos24.chroma_face_alpha_lut1_y[0],stDcmLut_webos24.chroma_face_alpha_lut1_y[1],\
				stDcmLut_webos24.chroma_face_alpha_lut1_y[2],stDcmLut_webos24.chroma_face_alpha_lut1_y[3],\
				stDcmLut_webos24.chroma_face_alpha_lut2_x[0],stDcmLut_webos24.chroma_face_alpha_lut2_x[1],\
				stDcmLut_webos24.chroma_face_alpha_lut2_x[2],stDcmLut_webos24.chroma_face_alpha_lut2_x[3],\
				stDcmLut_webos24.chroma_face_alpha_lut2_y[0],stDcmLut_webos24.chroma_face_alpha_lut2_y[1],\
				stDcmLut_webos24.chroma_face_alpha_lut2_y[2],stDcmLut_webos24.chroma_face_alpha_lut2_y[3]);
			if(pqData->wid == 0 || pqData->wid == 1) //o24, o22, e60, o20 only
			{
				ret = PE_DCM_SetDceLut2(&dclut_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
					return ret;
				}
			}
			else if(pqData->wid == 2 || pqData->wid == 3) //o22+f22, e60+f20
			{
				ret = PE_DCM_SetDceLut3(&dclut_param);
				if (ret)
				{
					PE_PRINT_ERROR("PE_DCM_SetDceLut3: error(%d)\n", ret);
					return ret;
				}
			}
		}

	}
	else if(pqData->version == 0x2 ||pqData->version == 0x1)
	{
		if (copy_from_user(&stDcmLut, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		param.win_id = LX_PE_WIN_0;
		param.size = PE_KWRAP_DCM_LUT_STEP;
		param.data = (UINT32 *)OS_Malloc(sizeof(UINT32) * param.size);
		if (!param.data)
		{
			PE_PRINT_ERROR("OS_Malloc error.\n");
			return ret;
		}
		for (i = 0; i < PE_KWRAP_DCM_LUT_STEP; i++)
		{
			x_data = (UINT32)stDcmLut.sLumaLutX[i]<<16;
			y_data = (UINT32)stDcmLut.sLumaLutY[i];
			if (sDcBypassLut[i] != y_data)
			{
				drc_bypass = FALSE;
			}
			if (y_data > PE_KWRAP_DCE_LUT_VAL_MAX)
			{
				y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
			}
			param.data[i] = x_data + y_data;
			PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
				i, (param.data[i] >> 16) & 0xffff, param.data[i] & 0xffff);
		}
		ret = PE_DCM_SetDceLut(&param);
		if(param.data) OS_Free(param.data);
		if (ret)
		{
			PE_PRINT_ERROR("PE_DCM_SetDceLut: error(%d)\n", ret);
			return ret;
		}
	}
	else if(pqData->version == 0x0)//0x0:only for pioneer
	{
		if (copy_from_user(&stDcmLut_pioneer, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		dclut_param.win_id = LX_PE_WIN_0;
		for (i = 0; i < 32; i++)
		{
			x_data = (UINT32)stDcmLut_pioneer.sLumaLutX[i];
			y_data = (UINT32)stDcmLut_pioneer.sLumaLutY[i];
			if (x_data != y_data)
			{
				drc_bypass = FALSE;
			}
			
			if ((pqData->wid == 0 || pqData->wid == 1)&&y_data > PE_KWRAP_DCE_LUT_VAL_MAX)//e60 only model
			{
				y_data = PE_KWRAP_DCE_LUT_VAL_MAX;
			}
			dclut_param.lumalut_x[i] = x_data;
			dclut_param.lumalut_y[i] = y_data;
			PE_PRINT_DCM_LUT("data[%2d] = [%4d] [%4d]\n", \
				i, dclut_param.lumalut_x[i], dclut_param.lumalut_y[i]);
		}
		memcpy(dclut_param.chroma_face_alpha_lut1_x,stDcmLut_pioneer.chroma_face_alpha_lut1_x, sizeof(UINT16)*4*4);
		
		PE_PRINT_DCM_LUT(\
			"lut1_x: %d, %d, %d, %d\n" \
			"lut1_y: %d, %d, %d, %d\n" \
			"lut2_x: %d, %d, %d, %d\n" \
			"lut2_y: %d, %d, %d, %d\n", \
			stDcmLut_pioneer.chroma_face_alpha_lut1_x[0],stDcmLut_pioneer.chroma_face_alpha_lut1_x[1],\
			stDcmLut_pioneer.chroma_face_alpha_lut1_x[2],stDcmLut_pioneer.chroma_face_alpha_lut1_x[3],\
			stDcmLut_pioneer.chroma_face_alpha_lut1_y[0],stDcmLut_pioneer.chroma_face_alpha_lut1_y[1],\
			stDcmLut_pioneer.chroma_face_alpha_lut1_y[2],stDcmLut_pioneer.chroma_face_alpha_lut1_y[3],\
			stDcmLut_pioneer.chroma_face_alpha_lut2_x[0],stDcmLut_pioneer.chroma_face_alpha_lut2_x[1],\
			stDcmLut_pioneer.chroma_face_alpha_lut2_x[2],stDcmLut_pioneer.chroma_face_alpha_lut2_x[3],\
			stDcmLut_pioneer.chroma_face_alpha_lut2_y[0],stDcmLut_pioneer.chroma_face_alpha_lut2_y[1],\
			stDcmLut_pioneer.chroma_face_alpha_lut2_y[2],stDcmLut_pioneer.chroma_face_alpha_lut2_y[3]);
		ret = PE_DCM_SetDceLut2(&dclut_param);
		if (ret)
		{
			PE_PRINT_ERROR("PE_DCM_SetDceLut2: error(%d)\n", ret);
			return ret;
		}
	}
	else
	{
		if (copy_from_user(&stDcmLut, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
	}
	/* DCE LUT E*/
	if(pqData->version == 0x2 || pqData->version == 0x30 || pqData->version == 0x40|| pqData->version == 0x60|| pqData->version == 0x61) //0x2:webos5.0 0x30:webos6.0 e60,o20, 0x40:webos7.0
	{
		/* DRC S */
		drc_param.win_id = LX_PE_WIN_0;
		ret = PE_DCM_GetDceDrcMode(&drc_param);
		if (PE_KDRV_VER_O20)
        {
                ret = KWRAP_PE_GetCurDceDrcMode((void *)&drc_param);
        }
        else
        {
                ret = PE_DCM_GetDceDrcMode(&drc_param);
        }
        if (ret)
        {
                PE_PRINT_ERROR("PE_DCM_GetDceDrcMode: error(%d)\n", ret);
                return ret;
        }
		drc_param.dc_bypass = drc_bypass ? 1 : 0;
		drc_param.db_type = LX_PE_DRC_DC_BYPASS;
		if (PE_KDRV_VER_O20)
		{
			ret = KWRAP_PE_SetDceDrcMode((void *)&drc_param);
		}
		else
		{
			ret = PE_DCM_SetDceDrcMode(&drc_param);
		}
        if (ret)
        {
                PE_PRINT_ERROR("PE_DCM_SetDceDrcMode: error(%d)\n", ret);
                return ret;
        }
		/* DRC E */
		/* DTM S */
		dtm_param.win_id = LX_PE_WIN_0;
		dtm_param.size = 33;
		dtm_param.data = (UINT32 *)OS_Malloc(sizeof(UINT32) * dtm_param.size);
		detected =0;
		if (!dtm_param.data)
		{
			PE_PRINT_ERROR("OS_Malloc error.\n");
			return ret;
		}
		if(pqData->version == 0x2)
			pDtmLut = (UINT16*)stDcmLut.dtm_lut;
		else if (pqData->version == 0x61)
			pDtmLut = (UINT16*)pDcmLut_webos24_v2->dtm_lut;
		else 
			pDtmLut = (UINT16*)stDcmLut_webos24.dtm_lut;
		#if 0
		if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT- V4L2_CID_EXT_VPQ_BASE])
		{
			pDtmLut = sDtmbNGLut;
		}
		#endif
		for (i = 0; i < 33 ; i++)
		{
			x_data = (UINT32)(pDtmLut[i]<<16);
			y_data = (UINT32)pDtmLut[i + 33];
			if(i ==0 &&(y_data != 0x0 || x_data != 0x0))
			{
				detected =1;
			}
			if(pDtmLut[i + 33] >= pDtmLut[i])// y >= x case
			{
				if ((pDtmLut[i + 33] - pDtmLut[i]) > 500)
				{
					detected =1;
				}
			}
			else // y < x case
			{
				if ((pDtmLut[i] - pDtmLut[i + 33]) > 500)
				{
					detected =1;
				}
			}
			if (y_data > 0x3ff)
			{
				y_data = 0x3ff;
			}
			dtm_param.data[i] = x_data + y_data;
		}
		if (detected ==1)
		{
			cnt_detected += 1;
			PE_PRINT_NOTI("dtm detected!!!!: %d dtm cnt : %d, x0~9:%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d \n"\
							"y0~9:%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d \n",\
			detected, cnt_detected,\
			pDtmLut[0] & 0xffff,pDtmLut[1] & 0xffff,pDtmLut[2] & 0xffff,\
			pDtmLut[3] & 0xffff,pDtmLut[4] & 0xffff,pDtmLut[5] & 0xffff,\
			pDtmLut[6] & 0xffff,pDtmLut[7] & 0xffff,pDtmLut[8] & 0xffff,\
			pDtmLut[9] & 0xffff,\
			pDtmLut[0+ 33] & 0xffff,pDtmLut[1+ 33] & 0xffff,pDtmLut[2+ 33] & 0xffff,\
			pDtmLut[3+ 33] & 0xffff,pDtmLut[4+ 33] & 0xffff,pDtmLut[5+ 33] & 0xffff,\
			pDtmLut[6+ 33] & 0xffff,pDtmLut[7+ 33] & 0xffff,pDtmLut[8+ 33] & 0xffff,\
			pDtmLut[9+ 33] & 0xffff);
			#if 0
			//pattern on
			addr0 = 0xC9014448;
			val0 = 0x01000000;
			ret = SYS_IO_WriteRegArray(addr0,4,&val0);
			//dummy count
			addr0 = 0xC901228C;
			val0 = cnt_detected;
			ret = SYS_IO_WriteRegArray(addr0,4,&val0);
			#endif
			//break;
		}
		PE_PRINT_DTM("dtm lut\n"\
						"DTM X[0~15] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
								"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n"\
					   "DTM Y[0~15] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
								"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n",\
		(dtm_param.data[0] >> 16) & 0xffff,(dtm_param.data[1] >> 16) & 0xffff,(dtm_param.data[2] >> 16) & 0xffff,\
		(dtm_param.data[3] >> 16) & 0xffff,(dtm_param.data[4] >> 16) & 0xffff,(dtm_param.data[5] >> 16) & 0xffff,\
		(dtm_param.data[6] >> 16) & 0xffff,(dtm_param.data[7] >> 16) & 0xffff,(dtm_param.data[8] >> 16) & 0xffff,\
		(dtm_param.data[9] >> 16) & 0xffff,(dtm_param.data[10] >> 16) & 0xffff,(dtm_param.data[11] >> 16) & 0xffff,\
		(dtm_param.data[12] >> 16) & 0xffff,(dtm_param.data[13] >> 16) & 0xffff,(dtm_param.data[14] >> 16) & 0xffff,\
		(dtm_param.data[15] >> 16) & 0xffff,\
		dtm_param.data[0] & 0xffff,dtm_param.data[1] & 0xffff,dtm_param.data[2] & 0xffff,\
		dtm_param.data[3] & 0xffff,dtm_param.data[4] & 0xffff,dtm_param.data[5] & 0xffff,\
		dtm_param.data[6] & 0xffff,dtm_param.data[7] & 0xffff,dtm_param.data[8] & 0xffff,\
		dtm_param.data[9] & 0xffff,dtm_param.data[10] & 0xffff,dtm_param.data[11] & 0xffff,\
		dtm_param.data[12] & 0xffff,dtm_param.data[13] & 0xffff,dtm_param.data[14] & 0xffff,\
		dtm_param.data[15] & 0xffff);
		PE_PRINT_DTM("\nDTM X[16~32] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
								"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n"\
					   "DTM Y[16~32] = [%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d]," \
								"[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],[%4d],\n",\
		(dtm_param.data[16] >> 16) & 0xffff,(dtm_param.data[17] >> 16) & 0xffff,(dtm_param.data[18] >> 16) & 0xffff,\
		(dtm_param.data[19] >> 16) & 0xffff,(dtm_param.data[20] >> 16) & 0xffff,(dtm_param.data[21] >> 16) & 0xffff,\
		(dtm_param.data[22] >> 16) & 0xffff,(dtm_param.data[23] >> 16) & 0xffff,(dtm_param.data[24] >> 16) & 0xffff,\
		(dtm_param.data[25] >> 16) & 0xffff,(dtm_param.data[26] >> 16) & 0xffff,(dtm_param.data[27] >> 16) & 0xffff,\
		(dtm_param.data[28] >> 16) & 0xffff,(dtm_param.data[29] >> 16) & 0xffff,(dtm_param.data[30] >> 16) & 0xffff,\
		(dtm_param.data[31] >> 16) & 0xffff,(dtm_param.data[32] >> 16) & 0xffff,\
		dtm_param.data[16] & 0xffff,dtm_param.data[17] & 0xffff,dtm_param.data[18] & 0xffff,\
		dtm_param.data[19] & 0xffff,dtm_param.data[20] & 0xffff,dtm_param.data[21] & 0xffff,\
		dtm_param.data[22] & 0xffff,dtm_param.data[23] & 0xffff,dtm_param.data[24] & 0xffff,\
		dtm_param.data[25] & 0xffff,dtm_param.data[26] & 0xffff,dtm_param.data[27] & 0xffff,\
		dtm_param.data[28] & 0xffff,dtm_param.data[29] & 0xffff,dtm_param.data[30] & 0xffff,\
		dtm_param.data[31] & 0xffff,dtm_param.data[32] & 0xffff);
		ret = PE_DCM_SetDtmLut(&dtm_param);
		if (ret)
		{
			PE_PRINT_ERROR("PE_DCM_SetDtmLut: error(%d)\n", ret);
			return ret;
		}
		if(dtm_param.data) OS_Free(dtm_param.data);
		/* DTM E */
	}
	if (ret)
	{
		PE_PRINT_ERROR("PE_DCM_SetDtmLut: error(%d)\n", ret);
	}
	else
	{
		if(pqData->version == 0x2 || pqData->version == 0x1 )
		{
			memcpy(&stDcmLut_webos24, &stDcmLut, sizeof(vpq_hwrap_dynamic_lut_t));
		}
		if(pqData->version == 0x61)
		{
			if (v4l2_vpq_pe_save_param(ctrl->id, pDcmLut_webos24_v2, pqData->version))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		}
		else
		{
			if (v4l2_vpq_pe_save_param(ctrl->id, &stDcmLut_webos24, pqData->version))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		}
	}
	return ret;
}

int vpq_set_obc_lut(struct v4l2_ext_vpq_cmn_data *pqData, struct v4l2_ext_control *ctrl)
{
	//struct v4l2_ext_vpq_cmn_data pqData;
	#if 1
	int ret;
	vpq_hwrap_obc_lut_o20_t stObcLut;
	vpq_hwrap_obc_lut_e60_o22_t stObcLut_e60_o22;
	LX_PE_VSD_OBC1_LUT_T param;
	LX_PE_VSD_OBC2_LUT_T param_e60_o22;
	if(_g_v4l2_vpq_pe_block_func[V4L2_CID_EXT_VPQ_OBC_LUT- V4L2_CID_EXT_VPQ_BASE])
		return ret;
	if(pqData->version == 0x40) // webos22 o22, temporally M23 for SOCTS
	{
		memset(&stObcLut_e60_o22, 0x00, sizeof(stObcLut_e60_o22));

		if (copy_from_user(&stObcLut_e60_o22, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		PE_PRINT_OBC_LUT(
			"[%s.%d] OBC LUT \n"\
			"head_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"head_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
			"head_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"head_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
			"head_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"head_r_lut_y: %d,%d,%d,%d,%d,%d\n"\
			"body_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"body_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
			"body_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"body_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
			"body_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
			"body_r_lut_y: %d,%d,%d,%d,%d,%d\n",\
			__F__, __L__,\
			stObcLut_e60_o22.head_g_lut_x[0],stObcLut_e60_o22.head_g_lut_x[1],stObcLut_e60_o22.head_g_lut_x[2],\
			stObcLut_e60_o22.head_g_lut_x[3],stObcLut_e60_o22.head_g_lut_x[4],stObcLut_e60_o22.head_g_lut_x[5],\
			stObcLut_e60_o22.head_g_lut_y[0],stObcLut_e60_o22.head_g_lut_y[1],stObcLut_e60_o22.head_g_lut_y[2],\
			stObcLut_e60_o22.head_g_lut_y[3],stObcLut_e60_o22.head_g_lut_y[4],stObcLut_e60_o22.head_g_lut_y[5],\
			stObcLut_e60_o22.head_b_lut_x[0],stObcLut_e60_o22.head_b_lut_x[1],stObcLut_e60_o22.head_b_lut_x[2],\
			stObcLut_e60_o22.head_b_lut_x[3],stObcLut_e60_o22.head_b_lut_x[4],stObcLut_e60_o22.head_b_lut_x[5],\
			stObcLut_e60_o22.head_b_lut_y[0],stObcLut_e60_o22.head_b_lut_y[1],stObcLut_e60_o22.head_b_lut_y[2],\
			stObcLut_e60_o22.head_b_lut_y[3],stObcLut_e60_o22.head_b_lut_y[4],stObcLut_e60_o22.head_b_lut_y[5],\
			stObcLut_e60_o22.head_r_lut_x[0],stObcLut_e60_o22.head_r_lut_x[1],stObcLut_e60_o22.head_r_lut_x[2],\
			stObcLut_e60_o22.head_r_lut_x[3],stObcLut_e60_o22.head_r_lut_x[4],stObcLut_e60_o22.head_r_lut_x[5],\
			stObcLut_e60_o22.head_r_lut_y[0],stObcLut_e60_o22.head_r_lut_y[1],stObcLut_e60_o22.head_r_lut_y[2],\
			stObcLut_e60_o22.head_r_lut_y[3],stObcLut_e60_o22.head_r_lut_y[4],stObcLut_e60_o22.head_r_lut_y[5],\
			stObcLut_e60_o22.body_g_lut_x[0],stObcLut_e60_o22.body_g_lut_x[1],stObcLut_e60_o22.body_g_lut_x[2],\
			stObcLut_e60_o22.body_g_lut_x[3],stObcLut_e60_o22.body_g_lut_x[4],stObcLut_e60_o22.body_g_lut_x[5],\
			stObcLut_e60_o22.body_g_lut_y[0],stObcLut_e60_o22.body_g_lut_y[1],stObcLut_e60_o22.body_g_lut_y[2],\
			stObcLut_e60_o22.body_g_lut_y[3],stObcLut_e60_o22.body_g_lut_y[4],stObcLut_e60_o22.body_g_lut_y[5],\
			stObcLut_e60_o22.body_b_lut_x[0],stObcLut_e60_o22.body_b_lut_x[1],stObcLut_e60_o22.body_b_lut_x[2],\
			stObcLut_e60_o22.body_b_lut_x[3],stObcLut_e60_o22.body_b_lut_x[4],stObcLut_e60_o22.body_b_lut_x[5],\
			stObcLut_e60_o22.body_b_lut_y[0],stObcLut_e60_o22.body_b_lut_y[1],stObcLut_e60_o22.body_b_lut_y[2],\
			stObcLut_e60_o22.body_b_lut_y[3],stObcLut_e60_o22.body_b_lut_y[4],stObcLut_e60_o22.body_b_lut_y[5],\
			stObcLut_e60_o22.body_r_lut_x[0],stObcLut_e60_o22.body_r_lut_x[1],stObcLut_e60_o22.body_r_lut_x[2],\
			stObcLut_e60_o22.body_r_lut_x[3],stObcLut_e60_o22.body_r_lut_x[4],stObcLut_e60_o22.body_r_lut_x[5],\
			stObcLut_e60_o22.body_r_lut_y[0],stObcLut_e60_o22.body_r_lut_y[1],stObcLut_e60_o22.body_r_lut_y[2],\
			stObcLut_e60_o22.body_r_lut_y[3],stObcLut_e60_o22.body_r_lut_y[4],stObcLut_e60_o22.body_r_lut_y[5]);
		param_e60_o22.win_id = LX_PE_WIN_0;
		memcpy(param_e60_o22.head_g_lut_x, stObcLut_e60_o22.head_g_lut_x, sizeof(stObcLut_e60_o22.head_g_lut_x));
		memcpy(param_e60_o22.head_g_lut_y, stObcLut_e60_o22.head_g_lut_y, sizeof(stObcLut_e60_o22.head_g_lut_y));
		memcpy(param_e60_o22.head_b_lut_x, stObcLut_e60_o22.head_b_lut_x, sizeof(stObcLut_e60_o22.head_b_lut_x));
		memcpy(param_e60_o22.head_b_lut_y, stObcLut_e60_o22.head_b_lut_y, sizeof(stObcLut_e60_o22.head_b_lut_y));
		memcpy(param_e60_o22.head_r_lut_x, stObcLut_e60_o22.head_r_lut_x, sizeof(stObcLut_e60_o22.head_r_lut_x));
		memcpy(param_e60_o22.head_r_lut_y, stObcLut_e60_o22.head_r_lut_y, sizeof(stObcLut_e60_o22.head_r_lut_y));
		memcpy(param_e60_o22.body_g_lut_x, stObcLut_e60_o22.body_g_lut_x, sizeof(stObcLut_e60_o22.body_g_lut_x));
		memcpy(param_e60_o22.body_g_lut_y, stObcLut_e60_o22.body_g_lut_y, sizeof(stObcLut_e60_o22.body_g_lut_y));
		memcpy(param_e60_o22.body_b_lut_x, stObcLut_e60_o22.body_b_lut_x, sizeof(stObcLut_e60_o22.body_b_lut_x));
		memcpy(param_e60_o22.body_b_lut_y, stObcLut_e60_o22.body_b_lut_y, sizeof(stObcLut_e60_o22.body_b_lut_y));
		memcpy(param_e60_o22.body_r_lut_x, stObcLut_e60_o22.body_r_lut_x, sizeof(stObcLut_e60_o22.body_r_lut_x));
		memcpy(param_e60_o22.body_r_lut_y, stObcLut_e60_o22.body_r_lut_y, sizeof(stObcLut_e60_o22.body_r_lut_y));
		ret = PE_SHP_SetObcLUT((void *)&param_e60_o22);
		if (ret)
		{
			PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
		}
		else
		{
			if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut_e60_o22, pqData->version))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		}
	}
	else if(PE_KDRV_VER_E60)
	{
		/* version definition
		   chip O20 : version = 1 (default)
		        E60 : version = 3x.
		*/
		if(pqData->version == 30)
		{
			memset(&stObcLut_e60_o22, 0x00, sizeof(stObcLut_e60_o22));

			if (copy_from_user(&stObcLut_e60_o22, (void __user *)pqData->p_data, pqData->length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			PE_PRINT_OBC_LUT(
				"[%s.%d] OBC LUT \n"\
				"head_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"head_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"head_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"head_r_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_g_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_g_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_b_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_b_lut_y: %d,%d,%d,%d,%d,%d\n"\
				"body_r_lut_x: %d,%d,%d,%d,%d,%d\n"\
				"body_r_lut_y: %d,%d,%d,%d,%d,%d\n",\
				__F__, __L__,\
				stObcLut_e60_o22.head_g_lut_x[0],stObcLut_e60_o22.head_g_lut_x[1],stObcLut_e60_o22.head_g_lut_x[2],\
				stObcLut_e60_o22.head_g_lut_x[3],stObcLut_e60_o22.head_g_lut_x[4],stObcLut_e60_o22.head_g_lut_x[5],\
				stObcLut_e60_o22.head_g_lut_y[0],stObcLut_e60_o22.head_g_lut_y[1],stObcLut_e60_o22.head_g_lut_y[2],\
				stObcLut_e60_o22.head_g_lut_y[3],stObcLut_e60_o22.head_g_lut_y[4],stObcLut_e60_o22.head_g_lut_y[5],\
				stObcLut_e60_o22.head_b_lut_x[0],stObcLut_e60_o22.head_b_lut_x[1],stObcLut_e60_o22.head_b_lut_x[2],\
				stObcLut_e60_o22.head_b_lut_x[3],stObcLut_e60_o22.head_b_lut_x[4],stObcLut_e60_o22.head_b_lut_x[5],\
				stObcLut_e60_o22.head_b_lut_y[0],stObcLut_e60_o22.head_b_lut_y[1],stObcLut_e60_o22.head_b_lut_y[2],\
				stObcLut_e60_o22.head_b_lut_y[3],stObcLut_e60_o22.head_b_lut_y[4],stObcLut_e60_o22.head_b_lut_y[5],\
				stObcLut_e60_o22.head_r_lut_x[0],stObcLut_e60_o22.head_r_lut_x[1],stObcLut_e60_o22.head_r_lut_x[2],\
				stObcLut_e60_o22.head_r_lut_x[3],stObcLut_e60_o22.head_r_lut_x[4],stObcLut_e60_o22.head_r_lut_x[5],\
				stObcLut_e60_o22.head_r_lut_y[0],stObcLut_e60_o22.head_r_lut_y[1],stObcLut_e60_o22.head_r_lut_y[2],\
				stObcLut_e60_o22.head_r_lut_y[3],stObcLut_e60_o22.head_r_lut_y[4],stObcLut_e60_o22.head_r_lut_y[5],\
				stObcLut_e60_o22.body_g_lut_x[0],stObcLut_e60_o22.body_g_lut_x[1],stObcLut_e60_o22.body_g_lut_x[2],\
				stObcLut_e60_o22.body_g_lut_x[3],stObcLut_e60_o22.body_g_lut_x[4],stObcLut_e60_o22.body_g_lut_x[5],\
				stObcLut_e60_o22.body_g_lut_y[0],stObcLut_e60_o22.body_g_lut_y[1],stObcLut_e60_o22.body_g_lut_y[2],\
				stObcLut_e60_o22.body_g_lut_y[3],stObcLut_e60_o22.body_g_lut_y[4],stObcLut_e60_o22.body_g_lut_y[5],\
				stObcLut_e60_o22.body_b_lut_x[0],stObcLut_e60_o22.body_b_lut_x[1],stObcLut_e60_o22.body_b_lut_x[2],\
				stObcLut_e60_o22.body_b_lut_x[3],stObcLut_e60_o22.body_b_lut_x[4],stObcLut_e60_o22.body_b_lut_x[5],\
				stObcLut_e60_o22.body_b_lut_y[0],stObcLut_e60_o22.body_b_lut_y[1],stObcLut_e60_o22.body_b_lut_y[2],\
				stObcLut_e60_o22.body_b_lut_y[3],stObcLut_e60_o22.body_b_lut_y[4],stObcLut_e60_o22.body_b_lut_y[5],\
				stObcLut_e60_o22.body_r_lut_x[0],stObcLut_e60_o22.body_r_lut_x[1],stObcLut_e60_o22.body_r_lut_x[2],\
				stObcLut_e60_o22.body_r_lut_x[3],stObcLut_e60_o22.body_r_lut_x[4],stObcLut_e60_o22.body_r_lut_x[5],\
				stObcLut_e60_o22.body_r_lut_y[0],stObcLut_e60_o22.body_r_lut_y[1],stObcLut_e60_o22.body_r_lut_y[2],\
				stObcLut_e60_o22.body_r_lut_y[3],stObcLut_e60_o22.body_r_lut_y[4],stObcLut_e60_o22.body_r_lut_y[5]);
			param_e60_o22.win_id = LX_PE_WIN_0;
			memcpy(param_e60_o22.head_g_lut_x, stObcLut_e60_o22.head_g_lut_x, sizeof(stObcLut_e60_o22.head_g_lut_x));
			memcpy(param_e60_o22.head_g_lut_y, stObcLut_e60_o22.head_g_lut_y, sizeof(stObcLut_e60_o22.head_g_lut_y));
			memcpy(param_e60_o22.head_b_lut_x, stObcLut_e60_o22.head_b_lut_x, sizeof(stObcLut_e60_o22.head_b_lut_x));
			memcpy(param_e60_o22.head_b_lut_y, stObcLut_e60_o22.head_b_lut_y, sizeof(stObcLut_e60_o22.head_b_lut_y));
			memcpy(param_e60_o22.head_r_lut_x, stObcLut_e60_o22.head_r_lut_x, sizeof(stObcLut_e60_o22.head_r_lut_x));
			memcpy(param_e60_o22.head_r_lut_y, stObcLut_e60_o22.head_r_lut_y, sizeof(stObcLut_e60_o22.head_r_lut_y));
			memcpy(param_e60_o22.body_g_lut_x, stObcLut_e60_o22.body_g_lut_x, sizeof(stObcLut_e60_o22.body_g_lut_x));
			memcpy(param_e60_o22.body_g_lut_y, stObcLut_e60_o22.body_g_lut_y, sizeof(stObcLut_e60_o22.body_g_lut_y));
			memcpy(param_e60_o22.body_b_lut_x, stObcLut_e60_o22.body_b_lut_x, sizeof(stObcLut_e60_o22.body_b_lut_x));
			memcpy(param_e60_o22.body_b_lut_y, stObcLut_e60_o22.body_b_lut_y, sizeof(stObcLut_e60_o22.body_b_lut_y));
			memcpy(param_e60_o22.body_r_lut_x, stObcLut_e60_o22.body_r_lut_x, sizeof(stObcLut_e60_o22.body_r_lut_x));
			memcpy(param_e60_o22.body_r_lut_y, stObcLut_e60_o22.body_r_lut_y, sizeof(stObcLut_e60_o22.body_r_lut_y));
			ret = PE_SHP_SetObcLUT((void *)&param_e60_o22);
			if (ret)
			{
				PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
			}
			else
			{
				if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut_e60_o22, pqData->version))
				{
					PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
				}
			}
		}
	}
	else if(PE_KDRV_VER_O20)
	{
		memset(&stObcLut, 0x00, sizeof(stObcLut));

		if (copy_from_user(&stObcLut, (void __user *)pqData->p_data, pqData->length))
		{
			PE_PRINT_ERROR("copy_from_user error\n");
		}
		PE_PRINT_OBC_LUT(
			"[%s.%d] OBC LUT \n"\
			"pqData->p_data: %p, pqData->length: %d,\n"\
			"object_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"object_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"face_fg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"face_fg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"face_bg_x: %d,%d,%d,%d,%d,%d,%d,%d,\n"\
			"face_bg_y: %d,%d,%d,%d,%d,%d,%d,%d,\n",\
			__F__, __L__,\
			pqData->p_data, pqData->length,\
			stObcLut.object_fg_x[0],stObcLut.object_fg_x[1],stObcLut.object_fg_x[2],stObcLut.object_fg_x[3], \
			stObcLut.object_fg_x[4],stObcLut.object_fg_x[5],stObcLut.object_fg_x[6],stObcLut.object_fg_x[7], \
			stObcLut.object_fg_y[0],stObcLut.object_fg_y[1],stObcLut.object_fg_y[2],stObcLut.object_fg_y[3], \
			stObcLut.object_fg_y[4],stObcLut.object_fg_y[5],stObcLut.object_fg_y[6],stObcLut.object_fg_y[7], \
			stObcLut.object_bg_x[0],stObcLut.object_bg_x[1],stObcLut.object_bg_x[2],stObcLut.object_bg_x[3], \
			stObcLut.object_bg_x[4],stObcLut.object_bg_x[5],stObcLut.object_bg_x[6],stObcLut.object_bg_x[7], \
			stObcLut.object_bg_y[0],stObcLut.object_bg_y[1],stObcLut.object_bg_y[2],stObcLut.object_bg_y[3], \
			stObcLut.object_bg_y[4],stObcLut.object_bg_y[5],stObcLut.object_bg_y[6],stObcLut.object_bg_y[7], \
			stObcLut.face_fg_x[0],stObcLut.face_fg_x[1],stObcLut.face_fg_x[2],stObcLut.face_fg_x[3], \
			stObcLut.face_fg_x[4],stObcLut.face_fg_x[5],stObcLut.face_fg_x[6],stObcLut.face_fg_x[7], \
			stObcLut.face_fg_y[0],stObcLut.face_fg_y[1],stObcLut.face_fg_y[2],stObcLut.face_fg_y[3], \
			stObcLut.face_fg_y[4],stObcLut.face_fg_y[5],stObcLut.face_fg_y[6],stObcLut.face_fg_y[7], \
			stObcLut.face_bg_x[0],stObcLut.face_bg_x[1],stObcLut.face_bg_x[2],stObcLut.face_bg_x[3], \
			stObcLut.face_bg_x[4],stObcLut.face_bg_x[5],stObcLut.face_bg_x[6],stObcLut.face_bg_x[7], \
			stObcLut.face_bg_y[0],stObcLut.face_bg_y[1],stObcLut.face_bg_y[2],stObcLut.face_bg_y[3], \
			stObcLut.face_bg_y[4],stObcLut.face_bg_y[5],stObcLut.face_bg_y[6],stObcLut.face_bg_y[7]);
		param.win_id = LX_PE_WIN_0;
		memcpy(&param.object_fg_x, stObcLut.object_fg_x, sizeof(stObcLut.object_fg_x));
		memcpy(&param.object_fg_y, stObcLut.object_fg_y, sizeof(stObcLut.object_fg_y));
		memcpy(&param.object_bg_x, stObcLut.object_bg_x, sizeof(stObcLut.object_bg_x));
		memcpy(&param.object_bg_y, stObcLut.object_bg_y, sizeof(stObcLut.object_bg_y));
		memcpy(&param.face_fg_x,   stObcLut.face_fg_x,   sizeof(stObcLut.face_fg_x));
		memcpy(&param.face_fg_y,   stObcLut.face_fg_y,   sizeof(stObcLut.face_fg_y));
		memcpy(&param.face_bg_x,   stObcLut.face_bg_x,   sizeof(stObcLut.face_bg_x));
		memcpy(&param.face_bg_y,   stObcLut.face_bg_y,   sizeof(stObcLut.face_bg_y));
		ret = KWRAP_PE_SetObcLUT((void *)&param);
		if (ret)
		{
			PE_PRINT_ERROR("KWRAP_PE_SetObcLUT error(%d)\n", ret);
		}
		else
		{
			if (v4l2_vpq_pe_save_param(ctrl->id, &stObcLut, pqData->version))
			{
				PE_PRINT_ERROR("v4l2_vpq_pe_save_param(%s) error\n", vpq_ctrl_id_to_str(ctrl->id));
			}
		}
	}
	#endif
	return ret;
}
