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

#if 0
#include "linux/v4l2-ext/v4l2-controls-ext_id.h"
#include "linux/v4l2-ext/videodev2-ext_id.h"
#endif

#include "os_util.h"
#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#endif
#include "debug_util.h"
#include "pe_def.h"
#include "pe_kwrap.h"
#include "vpq_hwrap.h"
#include "vpq_hwrap_hdr.h"
#include "vpq_hwrap_pe.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
#ifndef V4L2_EXT_HDR_MODE_HDR2SDR
#define V4L2_EXT_HDR_MODE_HDR2SDR	9
#endif
#endif

#ifndef V4L2_CID_EXT_VPQ_REGISTER_CTRL
#define V4L2_CID_EXT_VPQ_REGISTER_CTRL (V4L2_CID_EXT_VPQ_BASE + 41)

struct v4l2_ext_vpq_register_data
{
	unsigned int registerAddress;
	unsigned int registerMask;
	unsigned int registerValue;
};

struct v4l2_ext_vpq_register_ctrl
{
	unsigned int number;

	union {
		struct v4l2_ext_vpq_register_data *registerData;
		unsigned int compat_registerData;
		unsigned long long sizer;
	};
};
#endif

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

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int v4l2_vpq_cmn_get_bypass_block(char* buffer);
int v4l2_vpq_cmn_set_bypass_block(int mask);
int v4l2_vpq_compat_vidioc_ext_ctrls_cmn(struct v4l2_ext_control *ctrl);
int vpq_set_ext_ctrl_cmn(struct v4l2_ext_control *ctrl);
int vpq_get_ext_ctrl_cmn(struct v4l2_ext_control *ctrl);
int vpq_proc_show_status_cmn(struct seq_file *m, void *v, int id, int from_who);
int vpq_proc_show_status_srcinfo(struct seq_file *m, void *v);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static unsigned int g_v4l2_vpq_cmn_mute = 0xff;
static int _g_v4l2_vpq_bypass_block = 0x0;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int v4l2_vpq_cmn_get_bypass_block(char* buffer)
{
	int len = 0;
	struct v4l2_ext_vpq_cmn_data param;
	unsigned int data[2];

	param.version = 0;
	param.length = sizeof(unsigned int)*2;
	param.wid = 0;
	param.p_data = (unsigned char *)&data;
	vpq_hwrap_getbypassblocks(&param);

	len += sprintf( buffer+len, "------------------------------------------------------\n");
	len += sprintf( buffer+len, "%-20s : %-30s\n", "0x1 | 0x2 | 0x4", "sharpness,PSP,object contrast");
	len += sprintf( buffer+len, "%-20s : %-30s\n", "0x8", "local dimming,UI gamma");
	len += sprintf( buffer+len, "%-20s : %-30s\n", "0x10", "WB,4CH gamma,LODC,ODC");
	len += sprintf( buffer+len, "%-20s : %-30s\n", "0x20 | 0x40", "HDR");
	len += sprintf( buffer+len, "------------------------------------------------------\n");
	len += sprintf( buffer+len, "prev block = 0x%08x, onoff = %d\n", data[0], data[1]);
	len += sprintf( buffer+len, "curr block(dbg)  = 0x%08x\n", _g_v4l2_vpq_bypass_block);
	len += sprintf( buffer+len, "------------------------------------------------------\n");
	return len;
}

int v4l2_vpq_cmn_set_bypass_block(int mask)
{
	struct v4l2_ext_vpq_cmn_data param;
	unsigned int data[2];

	param.version = 0;
	param.length = sizeof(unsigned int)*2;
	param.wid = 0;

	data[0] = ~mask;
	data[1] = 0;//off

	param.p_data = (unsigned char *)&data;
	vpq_hwrap_setbypassblocks(&param);

	data[0] = mask;
	data[1] = 1;//on

	param.p_data = (unsigned char *)&data;
	vpq_hwrap_setbypassblocks(&param);

	_g_v4l2_vpq_bypass_block = mask;

	return 0;
}

int v4l2_vpq_compat_vidioc_ext_ctrls_cmn(struct v4l2_ext_control *ctrl)
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
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			//PE_PRINT_VPQ_CMN("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			//PE_PRINT_VPQ_CMN("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				ret = -EINVAL;
				break;
			}
			//PE_PRINT_VPQ_CMN("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
		}break;
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			struct v4l2_ext_vpq_register_ctrl arg_buf2;

			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			if (!arg_buf.p_data)
			{
				PE_PRINT_ERROR("p_data is null\n");
				ret = -EINVAL;
				break;
			}
			if(copy_from_user(&arg_buf2,(void __user *)arg_buf.p_data,sizeof(struct v4l2_ext_vpq_register_ctrl)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			arg_buf2.registerData = (struct v4l2_ext_vpq_register_data *)(uintptr_t)arg_buf2.compat_registerData;
			if(copy_to_user((void __user *)arg_buf.p_data,&arg_buf2,sizeof(struct v4l2_ext_vpq_register_ctrl)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				ret = -EINVAL;
				break;
			}
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				ret = -EINVAL;
				break;
			}
		}break;
		default:
			break;
	}
	#endif
	#endif
	return ret;
}

int vpq_set_ext_ctrl_cmn(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[2];
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(unsigned int)*2))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			param.p_data = (unsigned char *)&data;
			PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d, set d:%x,%x\n",\
				param.version,param.length,param.wid,data[0],data[1]);
			ret = vpq_hwrap_setbypassblocks(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setbypassblocks error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[5];
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d\n",param.version,param.length,param.wid);
			if(copy_from_user(&data,(void __user *)param.p_data,param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			param.p_data = (unsigned char *)&data;
			/* [0]v4l2_ext_hdr_mode, [1]colorimetry, [2]display_brightness, [3]support HDR PRIME, [4]reserved */
			PE_PRINT_NOTI("setpqmodeinfo: v:%d,l:%d,w:%d, %d,%d,%d,%d,%d\n",param.version,param.length,param.wid,data[0],data[1],data[2],data[3],data[4]);
			ret = vpq_hwrap_setpqmodeinfo(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setpqmodeinfo error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_vpq_ext_pattern_info_v2 data;
			unsigned int size;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			param.p_data = (unsigned char *)&data;
			size = sizeof(struct v4l2_vpq_ext_pattern_info_v2);
			PE_PRINT_VPQ_CMN("v:%d,l:%d(%d),wid:%d, %d,%d, %d,%d, %d\n",param.version,param.length,size,param.wid,\
				data.bOnOff,data.eMode,data.stGradInfo.numGrad,data.stGradInfo.eGradMode,data.stWinboxInfo.u8NumWin);
			ret = vpq_hwrap_setextpattern(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setextpattern error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
		{
			int i;
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_vpq_register_ctrl data;
			struct v4l2_ext_vpq_register_data regData;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}

			if (!param.p_data || (param.length == 0))
			{
				PE_PRINT_ERROR("p_data is null or length(%d) is zero\n",param.length);
				ret = -EINVAL;
				break;
			}

			if (copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_register_ctrl)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}

			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, %d\n",param.version,param.length,param.wid,data.number);

			for (i=0; i<data.number; i++)
			{
				unsigned int regVal0, regVal1;

				if (copy_from_user(&regData,(void __user *)&(data.registerData[i]),sizeof(struct v4l2_ext_vpq_register_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					ret = -EINVAL;
					break;
				}

				if ((regData.registerAddress & 0xF0000000U) != 0xC0000000U)
				{
					PE_PRINT_ERROR("addr(0x%08x) error\n",regData.registerAddress);
					ret = -EINVAL;
					break;
				}

				#ifdef INCLUDE_KDRV_SYS
				ret = SYS_IO_ReadRegArray(regData.registerAddress, 4, &regVal0);
				if (ret)
				{
					PE_PRINT_ERROR("Error in SYS_IO_ReadRegArray (0x%x)\n", ret);
					break;
				}

				regVal1 = (regVal0 & (~regData.registerMask)) | (regData.registerValue & regData.registerMask);

				PE_PRINT_NOTI("[%4d] 0x%08x,0x%08x,0x%08x | 0x%08x -> 0x%08x\n",i,regData.registerAddress,regData.registerMask,regData.registerValue,regVal0,regVal1);

				ret = SYS_IO_WriteRegArray(regData.registerAddress, 4, &regVal1);
				if (ret)
				{
					PE_PRINT_ERROR("Error in SYS_IO_WriteRegArray (0x%x)\n", ret);
					break;
				}
				#endif
			}
		}break;
		default:
			return -EINVAL;
	}

	return ret;
}

int vpq_get_ext_ctrl_cmn(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[5] = {0xff,0xff,0xff,0xff,0xff};
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d\n",param.version,param.length,param.wid);
			if(copy_from_user(&data,(void __user *)param.p_data,param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getpqmodeinfo(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_getpqmodeinfo error(%d)\n",ret);
				return ret;
			}
			if(copy_to_user((void __user *)p_user_data,data,param.length))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				ret = -EINVAL;
				break;
			}
			g_v4l2_vpq_cmn_mute = KWRAP_PE_IsMuteOn(param.wid);
			/* [0]v4l2_ext_hdr_mode, [1]colorimetry, [2]display_brightness, [3]support HDR PRIME, [4]reserved */
			PE_PRINT_NOTI("getpqmodeinfo: v:%d,l:%d,w:%d, %d,%d,%d,%d,%d, mute:%d\n",param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[4],g_v4l2_vpq_cmn_mute);
			if (g_v4l2_vpq_cmn_mute)	return -1;
		}break;
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[2];
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(unsigned int)*2))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getbypassblocks(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_getbypassblocks error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,data,sizeof(unsigned int)*2))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
				ret = -EINVAL;
				break;
			}
			PE_PRINT_VPQ_CMN("v:%d,l:%d,wid:%d, get d:%x,%x\n",\
				param.version,param.length,param.wid,data[0],data[1]);
		}break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_vpq_ext_pattern_info_v2 data;
			unsigned char *p_user_data;
			unsigned int size;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)&data;
			ret = vpq_hwrap_getextpattern(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_getextpattern error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,&data,param.length))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			size = sizeof(struct v4l2_vpq_ext_pattern_info_v2);
			PE_PRINT_VPQ_CMN("v:%d,l:%d(%d),wid:%d, %d,%d, %d,%d, %d\n",param.version,param.length,size,param.wid,\
				data.bOnOff,data.eMode,data.stGradInfo.numGrad,data.stGradInfo.eGradMode,data.stWinboxInfo.u8NumWin);
		}break;
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
		{
			int i;
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_vpq_register_ctrl data;
			struct v4l2_ext_vpq_register_data regData;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}

			if (!param.p_data || (param.length == 0))
			{
				PE_PRINT_ERROR("p_data is null or length(%d) is zero\n",param.length);
				ret = -EINVAL;
				break;
			}

			if (copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_register_ctrl)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
				ret = -EINVAL;
				break;
			}

			PE_PRINT_NOTI("v:%d,l:%d,wid:%d, %d\n",param.version,param.length,param.wid,data.number);

			for (i=0; i<data.number; i++)
			{
				if (copy_from_user(&regData,(void __user *)&(data.registerData[i]),sizeof(struct v4l2_ext_vpq_register_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
					ret = -EINVAL;
					break;
				}

				if ((regData.registerAddress & 0xF0000000U) != 0xC0000000U)
				{
					PE_PRINT_ERROR("addr(0x%08x) error\n",regData.registerAddress);
					ret = -EINVAL;
					break;
				}

				#ifdef INCLUDE_KDRV_SYS
				ret = SYS_IO_ReadRegArray(regData.registerAddress, 4, &regData.registerValue);
				if (ret)
				{
					PE_PRINT_ERROR("Error in SYS_IO_ReadRegArray (0x%x)\n", ret);
					break;
				}
				#endif

				if (copy_to_user((void __user *)&(data.registerData[i]),&regData,sizeof(struct v4l2_ext_vpq_register_data)))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
					ret = -EINVAL;
					break;
				}

				PE_PRINT_NOTI("[%4d] 0x%08x,0x%08x,0x%08x\n",i,regData.registerAddress,regData.registerMask,regData.registerValue);
			}
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
int vpq_proc_show_status_cmn(struct seq_file *m, void *v, int id, int from_who)
{
	int ret;
	unsigned int index[3];
	const char *hdr_type[11] = {"sdr","dolby","hdr10","hlg","technicolor","hdreffect","6","7","8","9","max"};
	const char *colorm_type[3] = {"bt601","bt709","bt2020"};

	if (!m)	return 0;

	switch (id) {
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[2];
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getbypassblocks(&param);
			if (ret)
			{
				seq_printf(m, "\n");
			}
			else
			{
				seq_printf(m, "{bypassMask:0x%08x,bOnOff:%d}\n",data[0],data[1]);
			}
		}break;
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int data[5] = {0xff,0xff,0xff,0xff,0xff};
			#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
			unsigned int h2s = V4L2_EXT_HDR_MODE_HDR2SDR;
			#endif
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.wid = 0;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getpqmodeinfo(&param);
			if (ret)
			{
				seq_printf(m, "\n");
			}
			else
			{
				index[0] = (data[0]<10)? data[0]:10;
				index[1] = (data[1]<2)? data[1]:2;
				index[2] = vpq_hwrap_getcurpqmodeinfo(0,0);
				if (index[2]>=10)	index[2]=10;
				if (from_who==0)//pq-status
				{
					seq_printf(m, "{hdrStatus:%s,colorimetry:%s,peakLuminance:%d,supportPrime:%d,reserved:%d}\n",\
						hdr_type[index[0]],colorm_type[index[1]],data[2],data[3],g_v4l2_vpq_cmn_mute);
				}
				else
				{
					seq_printf(m, "[0]{hdrStatus:%s(%s),colorimetry:%s,peakLuminance:%d,supportPrime:%d,reserved:%d}\n",\
						hdr_type[index[0]],hdr_type[index[2]],colorm_type[index[1]],data[2],data[3],g_v4l2_vpq_cmn_mute);
				}
			}
			if (from_who==0)	break;//pq-status
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.wid = 1;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getpqmodeinfo(&param);
			if (ret)
			{
				seq_printf(m, "[1]\n");
			}
			else
			{
				index[0] = (data[0]<10)? data[0]:10;
				index[1] = (data[1]<2)? data[1]:2;
				index[2] = vpq_hwrap_getcurpqmodeinfo(1,0);
				if (index[2]>=10)	index[2]=10;
				seq_printf(m, "[1]{hdrStatus:%s(%s),colorimetry:%s,peakLuminance:%d,supportPrime:%d,reserved:%d}\n",\
					hdr_type[index[0]],hdr_type[index[2]],colorm_type[index[1]],data[2],data[3],g_v4l2_vpq_cmn_mute);
			}
			#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
			seq_printf(m, "{V4L2_EXT_HDR_MODE_HDR2SDR:%d}\n",h2s);
			#endif
		}break;
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_vpq_ext_pattern_info_v2 data;
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.length = sizeof(struct v4l2_vpq_ext_pattern_info_v2);
			param.p_data = (unsigned char *)&data;
			ret = vpq_hwrap_getextpattern(&param);
			if (ret)
			{
				seq_printf(m, "\n");
			}
			else
			{
				seq_printf(m, "{On:%d,Mode:%d,G{%d,%d,{%d,%x,%x,%x,%x,%x,%x,%x}},W{%d,{%d,%d,%d,%d,%d,%x,%x,%x}}}\n",\
					data.bOnOff,data.eMode,\
					data.stGradInfo.numGrad,data.stGradInfo.eGradMode,\
					data.stGradInfo.stLineAttr[0].lineIdx,data.stGradInfo.stLineAttr[0].start_R,\
					data.stGradInfo.stLineAttr[0].start_G,data.stGradInfo.stLineAttr[0].start_B,\
					data.stGradInfo.stLineAttr[0].step_R,data.stGradInfo.stLineAttr[0].step_G,\
					data.stGradInfo.stLineAttr[0].step_B,data.stGradInfo.stLineAttr[0].strideSize,\
					data.stWinboxInfo.u8NumWin,\
					data.stWinboxInfo.stWinBoxAttr[0].winIdx,data.stWinboxInfo.stWinBoxAttr[0].x,\
					data.stWinboxInfo.stWinBoxAttr[0].y,data.stWinboxInfo.stWinBoxAttr[0].w,\
					data.stWinboxInfo.stWinBoxAttr[0].h,data.stWinboxInfo.stWinBoxAttr[0].fill_R,\
					data.stWinboxInfo.stWinBoxAttr[0].fill_G,data.stWinboxInfo.stWinBoxAttr[0].fill_B);
			}
		}break;
		default:
			seq_printf(m, "{not support}\n");
			break;
	}

	return 0;
}
/**
* pq-status
*    see SICREQ-311 (PQStatus-ImplementationGuide_0609.pdf)
*
* add contents below
*INPUT_SRC_INFO:
*  input_src_color_space : rgb/ycbcr
*  colorimetry: 601/709/2020
*  input_hdr_type : sdr/hdr/dolby
*INPUT_CSC:
*  INPUT_CSC: bypass/rgb_to_ycbcr
*/

int vpq_proc_show_status_srcinfo(struct seq_file *m, void *v)
{
	int ret;
	struct v4l2_ext_vpq_cmn_data param;
	unsigned int data[5] = {0xff,0xff,0xff,0xff,0xff};
	unsigned int index[3]; // 0:hdrtype 1:colormetry, 2:inputcsc,
	const char *hdr_type[11] = {"sdr","dolby","hdr10","hlg","technicolor","hdreffect","6","7","8","9"," "};
	const char *colorm_type[4] = {"601","709","2020"," "};
	const char *csc_type[2] = {"bypass","rgb_to_ycbcr"};
	const char *color_space[2] = {"ycbcr","rgb"};
	int black_level_type;
	#ifdef VPQ_HWRAP_SUPPORT_HDR2SDR
	unsigned int h2s = V4L2_EXT_HDR_MODE_HDR2SDR;
	#endif
	memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
	param.wid = 0;
	param.p_data = (unsigned char *)data;
	ret = vpq_hwrap_getpqmodeinfo(&param);
	if (ret)
	{
		index[0] = 10;
		index[1] = 3;
		return 0;
	}
	else
	{
		index[0] = (data[0]<10)? data[0]:10;
		index[1] = (data[1]<2)? data[1]:2;
	}
	black_level_type = vpq_hwrap_getblackleveltype(0);//wid = 0
	switch(black_level_type){
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y709_LIMIT_HIGH:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_BT2020_LIMIT_HIGH:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LINEAR_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_RGB_Y601_LIMIT_HIGH:
			index[2] = 1;//rgbtoycbcr
			break;
		case V4L2_EXT_VPQ_BLACKLEVEL_Y709_LINEAR_LIMIT_HIGH:
		case V4L2_EXT_VPQ_BLACKLEVEL_Y709_COMP_LOW:
		case V4L2_EXT_VPQ_BLACKLEVEL_AV_RF_EXTENSION:
		case V4L2_EXT_VPQ_BLACKLEVEL_Y709_BYPASS:
		default:
			index[2] = 0; //bypass
			break;
	}

	seq_printf(m, "INPUT_SRC_INFO={input_src_color_space:%s,colorimetry:%s,input_hdr_type:%s}\n",\
		color_space[index[2]],colorm_type[index[1]],hdr_type[index[0]]);
	seq_printf(m, "INPUT_CSC=%s\n",\
		csc_type[index[2]]);

	return 0;
}
