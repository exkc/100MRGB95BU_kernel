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
#include "debug_util.h"
#include "pe_def.h"
#include "pe_kapi.h"
#include "pe_hdr.h"
#include "v4l2_vpq_hdr.h"
#include "vpq_hwrap_hdr.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#ifndef V4L2_CID_EXT_VPQ_BASE_COMMER
#define V4L2_CID_EXT_VPQ_BASE_COMMER (V4L2_CID_USER_EXT_PQ_BASE + 0xA00)
#endif

#ifndef V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL
#define V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL (V4L2_CID_EXT_VPQ_BASE_COMMER + 2)

struct v4l2_ext_vpq_read_input_pixel
{
    int position_x; //x-coordinate based on input size (0~3839)
    int position_y; //y-coordinate based on input size (0~2159)
    int csc_en; //0:off, 1:on(HDR only)
    int read_g; //0~1023
    int read_b; //0~1023
    int read_r; //0~1023
    int read_y; //64~940
    int read_cb;//64~960
    int read_cr;//64~960
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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int v4l2_vpq_hdr_inv_gamma = 0xff;
static struct v4l2_ext_hdr_tonemap g_v4l2_vpq_hdr_tone_data={0xff,};
static struct v4l2_ext_hdr_tonemap g_v4l2_vpq_hdr_tone_data1={0xff,};
static struct v4l2_ext_hdr_color_correction g_v4l2_vpq_hdr_clcr_data={0xff,};
static struct v4l2_ext_hdr_color_correction g_v4l2_vpq_hdr_clcr_data1={0xff,};
//static LX_PE_HDR_LLLUT_T g_v4l2_vpq_hdr_lllut_data={0,0xff,};
static unsigned short g_v4l2_vpq_hdr_ygain_data[66]={0xff,};//0~65535, 33point x,y
static unsigned short g_v4l2_vpq_hdr_ygain_data1[66]={0xff,};//0~65535, 33point x,y

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int v4l2_vpq_compat_vidioc_ext_ctrls_hdr(struct v4l2_ext_control *ctrl)
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
		case V4L2_CID_EXT_HDR_EOTF:
		case V4L2_CID_EXT_HDR_TONEMAP:
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		case V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL:
		{
			struct v4l2_ext_vpq_cmn_data arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			//PE_PRINT_VPQ_HDR("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			//PE_PRINT_VPQ_HDR("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			//PE_PRINT_VPQ_HDR("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
		}break;
		default:
			break;
	}
	#endif
	#endif
	return ret;
}

int v4l2_vpq_vidioc_s_ctrl_hdr(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_HDR("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_HDR_INV_GAMMA:
		{
			unsigned int param;
			v4l2_vpq_hdr_inv_gamma = ctrl->value;
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("INV skip\n");ret=0;break;}
			param = (unsigned int)ctrl->value;
			ret = vpq_hwrap_sethdrinvgamma(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_sethdrinvgamma error(%d)\n",ret);
				break;
			}
		}break;
		default:
			PE_PRINT_ERROR("invalid id(0x%x)\n",ctrl->id);
			ret = -EINVAL;
			break;
	}

	return ret;
}

int v4l2_vpq_vidioc_g_ctrl_hdr(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	//PE_PRINT_VPQ_HDR("vpq:id 0x%x (%s), value %d\n", ctrl->id, vpq_ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_HDR_INV_GAMMA:
		{
			unsigned int param;
			ctrl->value = v4l2_vpq_hdr_inv_gamma;
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("INV skip\n");ret=0;break;}
			ret = vpq_hwrap_gethdrinvgamma(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gethdrinvgamma error(%d)\n",ret);
				break;
			}
			ctrl->value = (int)param;
		}break;
		default:
			PE_PRINT_ERROR("invalid id(0x%x)\n",ctrl->id);
			ret = -EINVAL;
			break;
	}

	return 0;
}

int vpq_set_ext_ctrl_hdr(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_HDR_3DLUT:
		{
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("3D skip\n");ret=0;break;}
			PE_PRINT_VPQ_HDR("[V4L2_CID_EXT_HDR_3DLUT]\n");
		}break;
		case V4L2_CID_EXT_HDR_EOTF:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int *p_lut_data = NULL;
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("EO skip\n");ret=0;break;}
			do {
				p_lut_data = (unsigned int *)OS_Malloc(sizeof(unsigned int)*1024);
				if (!p_lut_data)	{PE_PRINT_ERROR("p_lut_data is null\n");break;}
				if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(p_lut_data,(void __user *)param.p_data,sizeof(unsigned int)*1024))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				param.p_data = (unsigned char *)p_lut_data;
				PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%x,%x,%x,%x,%x,%x\n",\
					param.version,param.length,param.wid,\
					p_lut_data[0],p_lut_data[1],p_lut_data[2],p_lut_data[3],p_lut_data[4],p_lut_data[5]);
				ret = vpq_hwrap_sethdreotf(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_sethdreotf error(%d)\n",ret);
					break;
				}
			} while(0);
			if (p_lut_data)	{OS_Free(p_lut_data);}
		}break;
		case V4L2_CID_EXT_HDR_OETF:
		{
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("OE skip\n");ret=0;break;}
			PE_PRINT_VPQ_HDR("[V4L2_CID_EXT_HDR_OETF]\n");
		}break;
		case V4L2_CID_EXT_HDR_TONEMAP:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_hdr_tonemap data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_hdr_tonemap)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if ((param.wid==0) && (memcmp(&g_v4l2_vpq_hdr_tone_data,&data,sizeof(struct v4l2_ext_hdr_tonemap))!=0))
			{
				memcpy(&g_v4l2_vpq_hdr_tone_data,&data,sizeof(struct v4l2_ext_hdr_tonemap));
				param.p_data = (unsigned char *)&data;
				PE_PRINT_HDR_LUT("v:%d,l:%d,wid:%d, m:%d\n",param.version,param.length,param.wid,data.hdr_mode);
				PE_PRINT_HDR_LUT("r_x:%x,%x,%x,%x,%x|%x,%x,%x,%x,%x\n",\
					data.r_data[0],data.r_data[1],data.r_data[2],data.r_data[3],data.r_data[4],\
					data.r_data[28],data.r_data[29],data.r_data[30],data.r_data[31],data.r_data[32]);
				PE_PRINT_HDR_LUT("r_y:%x,%x,%x,%x,%x,%x,%x,%x|%x,%x,%x,%x,%x,%x,%x,%x\n",\
					data.r_data[33],data.r_data[34],data.r_data[35],data.r_data[36],data.r_data[37],data.r_data[38],data.r_data[39],data.r_data[40],\
					data.r_data[58],data.r_data[59],data.r_data[60],data.r_data[61],data.r_data[62],data.r_data[63],data.r_data[64],data.r_data[65]);
				PE_PRINT_HDR_LUT("g_ :%x|%x, %x|%x\n",data.g_data[4],data.g_data[28],data.g_data[40],data.g_data[58]);
				PE_PRINT_HDR_LUT("b_ :%x|%x, %x|%x\n",data.b_data[4],data.b_data[28],data.b_data[40],data.b_data[58]);
				ret = vpq_hwrap_sethdrtonemap(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_sethdrtonemap error(%d)\n",ret);
					break;
				}
			}
			else if ((param.wid==1) && (memcmp(&g_v4l2_vpq_hdr_tone_data1,&data,sizeof(struct v4l2_ext_hdr_tonemap))!=0))
			{
				memcpy(&g_v4l2_vpq_hdr_tone_data1,&data,sizeof(struct v4l2_ext_hdr_tonemap));
				param.p_data = (unsigned char *)&data;
				PE_PRINT_HDR_LUT("v:%d,l:%d,wid:%d, m:%d\n",param.version,param.length,param.wid,data.hdr_mode);
				PE_PRINT_HDR_LUT("r_x:%x,%x,%x,%x,%x|%x,%x,%x,%x,%x\n",\
					data.r_data[0],data.r_data[1],data.r_data[2],data.r_data[3],data.r_data[4],\
					data.r_data[28],data.r_data[29],data.r_data[30],data.r_data[31],data.r_data[32]);
				PE_PRINT_HDR_LUT("r_y:%x,%x,%x,%x,%x,%x,%x,%x|%x,%x,%x,%x,%x,%x,%x,%x\n",\
					data.r_data[33],data.r_data[34],data.r_data[35],data.r_data[36],data.r_data[37],data.r_data[38],data.r_data[39],data.r_data[40],\
					data.r_data[58],data.r_data[59],data.r_data[60],data.r_data[61],data.r_data[62],data.r_data[63],data.r_data[64],data.r_data[65]);
				PE_PRINT_HDR_LUT("g_ :%x|%x, %x|%x\n",data.g_data[4],data.g_data[28],data.g_data[40],data.g_data[58]);
				PE_PRINT_HDR_LUT("b_ :%x|%x, %x|%x\n",data.b_data[4],data.b_data[28],data.b_data[40],data.b_data[58]);
				ret = vpq_hwrap_sethdrtonemap(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_sethdrtonemap error(%d)\n",ret);
					break;
				}
			}
		}break;
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_hdr_color_correction data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_hdr_color_correction)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if (param.wid==0)	memcpy(&g_v4l2_vpq_hdr_clcr_data,&data,sizeof(struct v4l2_ext_hdr_color_correction));
			else				memcpy(&g_v4l2_vpq_hdr_clcr_data1,&data,sizeof(struct v4l2_ext_hdr_color_correction));
			param.p_data = (unsigned char *)&data;
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, hs:%x,%x, lxy:%x,%x,%x,%x, %x,%x,%x,%x, sxy:%x,%x,%x,%x, %x,%x,%x,%x\n",\
				param.version,param.length,param.wid,data.hue_blend,data.sat_blend,\
				data.l_gain_x[0],data.l_gain_x[1],data.l_gain_x[6],data.l_gain_x[7],\
				data.l_gain_y[0],data.l_gain_y[1],data.l_gain_y[6],data.l_gain_y[7],\
				data.s_gain_x[0],data.s_gain_x[1],data.s_gain_x[6],data.s_gain_x[7],\
				data.s_gain_y[0],data.s_gain_y[1],data.s_gain_y[6],data.s_gain_y[7]);
			ret = vpq_hwrap_sethdrcolorcorrection(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_sethdrcolorcorrection error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned short data[66];//0~65535, 33point x,y
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(data,(void __user *)param.p_data,sizeof(unsigned short)*66))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if (param.wid == 0)		memcpy(g_v4l2_vpq_hdr_ygain_data,data,sizeof(unsigned short)*66);
			else					memcpy(g_v4l2_vpq_hdr_ygain_data1,data,sizeof(unsigned short)*66);
			param.p_data = (unsigned char *)data;
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%x,%x,%x,%x, %x,%x,%x,%x, %x,%x,%x,%x, %x,%x,%x,%x\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[29],data[30],data[31],data[32],\
				data[33],data[34],data[35],data[36],data[62],data[63],data[64],data[65]);
			ret = vpq_hwrap_sethlgygaintable(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_sethlgygaintable error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		{
			struct v4l2_ext_vpq_cmn_data param;
			short data[9];
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(data,(void __user *)param.p_data,sizeof(short)*9))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			param.p_data = (unsigned char *)data;
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%d,%d,%d, %d,%d,%d, %d,%d,%d\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]);
			ret = vpq_hwrap_setgamutmatrixpre(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_setgamutmatrixpre error(%d)\n",ret);
				break;
			}
		}break;
		#if 0	//legacy
		case (V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL+1):
		{
			struct v4l2_ext_vpq_cmn_data param;
			LX_PE_HDR_LLLUT_T data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&(data.lllut_en),(void __user *)param.p_data,sizeof(LX_PE_HDR_LLLUT_T)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			memcpy(&g_v4l2_vpq_hdr_lllut_data,&data,sizeof(LX_PE_HDR_LLLUT_T));
			param.p_data = (unsigned char *)&data;
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, en:%d,%d, rgb:%x,%x,%x,%x|%x,%x,%x,%x|%x,%x,%x,%x, mtx:%x,%x,%x, sel:%d, r2y:%d,%d,%d, xy:%x,%x,%x,%x|%x,%x,%x,%x, hs:%x,%x\n",\
				param.version,param.length,param.wid,\
				data.lllut_en,data.lllut_csc_en,\
				data.lllut_r[0],data.lllut_r[1],data.lllut_r[126],data.lllut_r[127],\
				data.lllut_g[0],data.lllut_g[1],data.lllut_g[126],data.lllut_g[127],\
				data.lllut_b[0],data.lllut_b[1],data.lllut_b[126],data.lllut_b[127],\
				data.matrix[0],data.matrix[1],data.matrix[2],
				data.blend_in_sel,\
				data.r2y_matrix[0],data.r2y_matrix[1],data.r2y_matrix[2],\
				data.blend_lut_x[0],data.blend_lut_x[1],data.blend_lut_x[4],data.blend_lut_x[5],\
				data.blend_lut_y[0],data.blend_lut_y[1],data.blend_lut_y[4],data.blend_lut_y[5],\
				data.hue_gain,data.sat_gain);
			ret = vpq_hwrap_sethdrlowlevellut(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_sethdrlowlevellut error(%d)\n",ret);
				break;
			}
		}break;
		#endif
		default:
			PE_PRINT_ERROR("invalid id(0x%x)\n",ctrl->id);
			ret = -EINVAL;
			break;
	}

	return ret;
}

int vpq_get_ext_ctrl_hdr(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_HDR_3DLUT:
		{
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("3D skip\n");ret=0;break;}
			PE_PRINT_VPQ_HDR("[V4L2_CID_EXT_HDR_3DLUT]\n");
		}break;
		case V4L2_CID_EXT_HDR_EOTF:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int *p_lut_data = NULL;
			unsigned char *p_user_data;
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("EO skip\n");ret=0;break;}
			do {
				p_lut_data = (unsigned int *)OS_Malloc(sizeof(unsigned int)*1024);
				if (!p_lut_data)	{PE_PRINT_ERROR("p_lut_data is null\n");break;}
				if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				if(copy_from_user(p_lut_data,(void __user *)param.p_data,sizeof(unsigned int)*1024))
				{
					PE_PRINT_ERROR("copy_from_user error\n");
				}
				p_user_data = param.p_data;
				param.p_data = (unsigned char *)p_lut_data;
				ret = vpq_hwrap_gethdreotf(&param);
				if (ret)
				{
					PE_PRINT_ERROR("vpq_hwrap_gethdreotf error(%d)\n",ret);
					break;
				}
				if(copy_to_user((void __user *)p_user_data,p_lut_data,sizeof(unsigned int)*1024))
				{
					PE_PRINT_ERROR("copy_to_user error\n");
				}
				PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%x,%x,%x,%x,%x,%x\n",\
					param.version,param.length,param.wid,\
					p_lut_data[0],p_lut_data[1],p_lut_data[2],p_lut_data[3],p_lut_data[4],p_lut_data[5]);
			} while(0);
			if (p_lut_data)	{OS_Free(p_lut_data);}
		}break;
		case V4L2_CID_EXT_HDR_OETF:
		{
			if (0==vpq_hwrap_gethdrfunctionenable())	{PE_PRINT_VPQ_HDR("OE skip\n");ret=0;break;}
			PE_PRINT_VPQ_HDR("[V4L2_CID_EXT_HDR_OETF]\n");
		}break;
		case V4L2_CID_EXT_HDR_TONEMAP:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_hdr_tonemap data;
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_hdr_tonemap)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)&data;
			ret = vpq_hwrap_gethdrtonemap(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gethdrtonemap error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,&data,sizeof(struct v4l2_ext_hdr_tonemap)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_HDR_LUT("v:%d,l:%d,wid:%d, m:%d\n",param.version,param.length,param.wid,data.hdr_mode);
			PE_PRINT_HDR_LUT("r_x:%x,%x,%x,%x,%x|%x,%x,%x,%x,%x\n",\
				data.r_data[0],data.r_data[1],data.r_data[2],data.r_data[3],data.r_data[4],\
				data.r_data[28],data.r_data[29],data.r_data[30],data.r_data[31],data.r_data[32]);
			PE_PRINT_HDR_LUT("r_y:%x,%x,%x,%x,%x,%x,%x,%x|%x,%x,%x,%x,%x,%x,%x,%x\n",\
				data.r_data[33],data.r_data[34],data.r_data[35],data.r_data[36],data.r_data[37],data.r_data[38],data.r_data[39],data.r_data[40],\
				data.r_data[58],data.r_data[59],data.r_data[60],data.r_data[61],data.r_data[62],data.r_data[63],data.r_data[64],data.r_data[65]);
			PE_PRINT_HDR_LUT("g_ :%x|%x, %x|%x\n",data.g_data[4],data.g_data[28],data.g_data[40],data.g_data[58]);
			PE_PRINT_HDR_LUT("b_ :%x|%x, %x|%x\n",data.b_data[4],data.b_data[28],data.b_data[40],data.b_data[58]);
		}break;
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_hdr_color_correction data;
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_hdr_color_correction)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)&data;
			ret = vpq_hwrap_gethdrcolorcorrection(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gethdrcolorcorrection error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,&data,sizeof(struct v4l2_ext_hdr_color_correction)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, hs:%x,%x, lxy:%x,%x,%x,%x, %x,%x,%x,%x, sxy:%x,%x,%x,%x, %x,%x,%x,%x\n",\
				param.version,param.length,param.wid,data.hue_blend,data.sat_blend,\
				data.l_gain_x[0],data.l_gain_x[1],data.l_gain_x[6],data.l_gain_x[7],\
				data.l_gain_y[0],data.l_gain_y[1],data.l_gain_y[6],data.l_gain_y[7],\
				data.s_gain_x[0],data.s_gain_x[1],data.s_gain_x[6],data.s_gain_x[7],\
				data.s_gain_y[0],data.s_gain_y[1],data.s_gain_y[6],data.s_gain_y[7]);
		}break;
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned short data[66];//0~65535, 33point x,y
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(data,(void __user *)param.p_data,sizeof(unsigned short)*66))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_gethlgygaintable(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gethlgygaintable error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,data,sizeof(unsigned short)*66))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%x,%x,%x,%x, %x,%x,%x,%x, %x,%x,%x,%x, %x,%x,%x,%x\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[29],data[30],data[31],data[32],\
				data[33],data[34],data[35],data[36],data[62],data[63],data[64],data[65]);
		}break;
		case V4L2_CID_EXT_HDR_PIC_INFO:
		{
			struct v4l2_ext_vpq_cmn_data param;
			unsigned int status[300];
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&status,(void __user *)param.p_data,param.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			PE_PRINT_HDR_HIST("v:%d,l,w:%d,%d\n",param.version,param.length,param.wid);

			p_user_data = param.p_data;
			param.p_data = (unsigned char *)status;
			ret = vpq_hwrap_gethdrpicinfo(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_gethdrpicinfo error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,status,param.length))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}

			PE_PRINT_HDR_HIST("%d %d %d %d  %d %d %d %d  %d %d %d %d  %d %d %d %d\n",\
				status[0]+status[1]+status[2]+status[3]+status[4]+status[5]+status[6]+status[7],\
				status[8+0]+status[8+1]+status[8+2]+status[8+3]+status[8+4]+status[8+5]+status[8+6]+status[8+7],\
				status[8*2+0]+status[8*2+1]+status[8*2+2]+status[8*2+3]+status[8*2+4]+status[8*2+5]+status[8*2+6]+status[8*2+7],\
				status[8*3+0]+status[8*3+1]+status[8*3+2]+status[8*3+3]+status[8*3+4]+status[8*3+5]+status[8*3+6]+status[8*3+7],\
				status[8*4+0]+status[8*4+1]+status[8*4+2]+status[8*4+3]+status[8*4+4]+status[8*4+5]+status[8*4+6]+status[8*4+7],\
				status[8*5+0]+status[8*5+1]+status[8*5+2]+status[8*5+3]+status[8*5+4]+status[8*5+5]+status[8*5+6]+status[8*5+7],\
				status[8*6+0]+status[8*6+1]+status[8*6+2]+status[8*6+3]+status[8*6+4]+status[8*6+5]+status[8*6+6]+status[8*6+7],\
				status[8*7+0]+status[8*7+1]+status[8*7+2]+status[8*7+3]+status[8*7+4]+status[8*7+5]+status[8*7+6]+status[8*7+7],\
				status[8*8+0]+status[8*8+1]+status[8*8+2]+status[8*8+3]+status[8*8+4]+status[8*8+5]+status[8*8+6]+status[8*8+7],\
				status[8*9+0]+status[8*9+1]+status[8*9+2]+status[8*9+3]+status[8*9+4]+status[8*9+5]+status[8*9+6]+status[8*9+7],\
				status[8*10+0]+status[8*10+1]+status[8*10+2]+status[8*10+3]+status[8*10+4]+status[8*10+5]+status[8*10+6]+status[8*10+7],\
				status[8*11+0]+status[8*11+1]+status[8*11+2]+status[8*11+3]+status[8*11+4]+status[8*11+5]+status[8*11+6]+status[8*11+7],\
				status[8*12+0]+status[8*12+1]+status[8*12+2]+status[8*12+3]+status[8*12+4]+status[8*12+5]+status[8*12+6]+status[8*12+7],\
				status[8*13+0]+status[8*13+1]+status[8*13+2]+status[8*13+3]+status[8*13+4]+status[8*13+5]+status[8*13+6]+status[8*13+7],\
				status[8*14+0]+status[8*14+1]+status[8*14+2]+status[8*14+3]+status[8*14+4]+status[8*14+5]+status[8*14+6]+status[8*14+7],\
				status[8*15+0]+status[8*15+1]+status[8*15+2]+status[8*15+3]+status[8*15+4]+status[8*15+5]+status[8*15+6]+status[8*15+7]);
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		{
			struct v4l2_ext_vpq_cmn_data param;
			short data[9];
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(data,(void __user *)param.p_data,sizeof(short)*9))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getgamutmatrixpre(&param);
			if (ret)
			{
				PE_PRINT_ERROR("vpq_hwrap_getgamutmatrixpre error(%d)\n",ret);
				break;
			}
			if(copy_to_user((void __user *)p_user_data,data,sizeof(short)*9))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, d:%d,%d,%d, %d,%d,%d, %d,%d,%d\n",\
				param.version,param.length,param.wid,\
				data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]);
		}break;
		case V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL:
		{
			struct v4l2_ext_vpq_cmn_data param;
			struct v4l2_ext_vpq_read_input_pixel data;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&data,(void __user *)param.p_data,sizeof(struct v4l2_ext_vpq_read_input_pixel)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}

			PE_PRINT_VPQ_HDR("v:%d,l,w:%d,%d\n",param.version,param.length,param.wid);

			ret = PE_HDR_GetPixelData((void *)&data);
			if (ret)
			{
				PE_PRINT_ERROR("PE_HDR_GetPixelData error(%d)\n",ret);
				break;
			}

			if(copy_to_user((void __user *)param.p_data,&data,sizeof(struct v4l2_ext_vpq_read_input_pixel)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}

			PE_PRINT_NOTI("x,y:%d,%d, csc:%d, gbr:%d,%d,%d, ycbcr:%d,%d,%d\n",data.position_x,data.position_y,\
				data.csc_en,data.read_g,data.read_b,data.read_r,data.read_y,data.read_cb,data.read_cr);
		}break;
		#if 0	//legacy
		case (V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL+1):
		{
			struct v4l2_ext_vpq_cmn_data param;
			LX_PE_HDR_LLLUT_T data;
			unsigned char *p_user_data;
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			if(copy_from_user(&(data.lllut_en),(void __user *)param.p_data,sizeof(LX_PE_HDR_LLLUT_T)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			p_user_data = param.p_data;
			memcpy(&data,&g_v4l2_vpq_hdr_lllut_data,sizeof(LX_PE_HDR_LLLUT_T));
			if(copy_to_user((void __user *)p_user_data,&(data.lllut_en),sizeof(LX_PE_HDR_LLLUT_T)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			PE_PRINT_VPQ_HDR("v:%d,l:%d,wid:%d, en:%d,%d, rgb:%x,%x,%x,%x|%x,%x,%x,%x|%x,%x,%x,%x, mtx:%x,%x,%x, sel:%d, r2y:%d,%d,%d, xy:%x,%x,%x,%x|%x,%x,%x,%x, hs:%x,%x\n",\
				param.version,param.length,param.wid,\
				data.lllut_en,data.lllut_csc_en,\
				data.lllut_r[0],data.lllut_r[1],data.lllut_r[126],data.lllut_r[127],\
				data.lllut_g[0],data.lllut_g[1],data.lllut_g[126],data.lllut_g[127],\
				data.lllut_b[0],data.lllut_b[1],data.lllut_b[126],data.lllut_b[127],\
				data.matrix[0],data.matrix[1],data.matrix[2],
				data.blend_in_sel,\
				data.r2y_matrix[0],data.r2y_matrix[1],data.r2y_matrix[2],\
				data.blend_lut_x[0],data.blend_lut_x[1],data.blend_lut_x[4],data.blend_lut_x[5],\
				data.blend_lut_y[0],data.blend_lut_y[1],data.blend_lut_y[4],data.blend_lut_y[5],\
				data.hue_gain,data.sat_gain);
		}break;
		#endif
		default:
			PE_PRINT_ERROR("invalid id(0x%x)\n",ctrl->id);
			ret = -EINVAL;
			break;
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
int vpq_proc_show_status_hdr(struct seq_file *m, void *v, int id, int from_who)
{
	int ret;

	if (!m)	return 0;

	switch (id) {
		case V4L2_CID_EXT_HDR_INV_GAMMA:
		{
			if (v4l2_vpq_hdr_inv_gamma==0xff)
			{
				seq_printf(m, "{0}\n");
			}
			else
			{
				seq_printf(m, "%d\n",v4l2_vpq_hdr_inv_gamma);
			}
		}break;
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		{
			struct v4l2_ext_hdr_color_correction *p = &g_v4l2_vpq_hdr_clcr_data;
			if (p->hue_blend==0xff)
			{
				seq_printf(m, "{0}\n");
			}
			else
			{
				if (from_who==0)//pq-status
				{
					seq_printf(m, "{uHueBlend:%d,uSatBlend:%d,uLgainx:{%d,%d,%d,%d,%d,%d,%d,%d},"\
						"uLgainy:{%d,%d,%d,%d,%d,%d,%d,%d},uSgainx:{%d,%d,%d,%d,%d,%d,%d,%d},"\
						"uSgainy:{%d,%d,%d,%d,%d,%d,%d,%d}}\n",p->hue_blend,p->sat_blend,\
						p->l_gain_x[0],p->l_gain_x[1],p->l_gain_x[2],p->l_gain_x[3],\
						p->l_gain_x[4],p->l_gain_x[5],p->l_gain_x[6],p->l_gain_x[7],\
						p->l_gain_y[0],p->l_gain_y[1],p->l_gain_y[2],p->l_gain_y[3],\
						p->l_gain_y[4],p->l_gain_y[5],p->l_gain_y[6],p->l_gain_y[7],\
						p->s_gain_x[0],p->s_gain_x[1],p->s_gain_x[2],p->s_gain_x[3],\
						p->s_gain_x[4],p->s_gain_x[5],p->s_gain_x[6],p->s_gain_x[7],\
						p->s_gain_y[0],p->s_gain_y[1],p->s_gain_y[2],p->s_gain_y[3],\
						p->s_gain_y[4],p->s_gain_y[5],p->s_gain_y[6],p->s_gain_y[7]);
				}
				else
				{
					seq_printf(m, "[0]{hue_blend:%d,sat_blend:%d\n"\
						"l_gain_x:{%d,%d,%d,%d,%d,%d,%d,%d},l_gain_y:{%d,%d,%d,%d,%d,%d,%d,%d}\n"\
						"s_gain_x:{%d,%d,%d,%d,%d,%d,%d,%d},s_gain_y:{%d,%d,%d,%d,%d,%d,%d,%d}}\n",\
						p->hue_blend,p->sat_blend,\
						p->l_gain_x[0],p->l_gain_x[1],p->l_gain_x[2],p->l_gain_x[3],\
						p->l_gain_x[4],p->l_gain_x[5],p->l_gain_x[6],p->l_gain_x[7],\
						p->l_gain_y[0],p->l_gain_y[1],p->l_gain_y[2],p->l_gain_y[3],\
						p->l_gain_y[4],p->l_gain_y[5],p->l_gain_y[6],p->l_gain_y[7],\
						p->s_gain_x[0],p->s_gain_x[1],p->s_gain_x[2],p->s_gain_x[3],\
						p->s_gain_x[4],p->s_gain_x[5],p->s_gain_x[6],p->s_gain_x[7],\
						p->s_gain_y[0],p->s_gain_y[1],p->s_gain_y[2],p->s_gain_y[3],\
						p->s_gain_y[4],p->s_gain_y[5],p->s_gain_y[6],p->s_gain_y[7]);
				}
			}
			if (from_who==0)	break;//pq-status
			p = &g_v4l2_vpq_hdr_clcr_data1;
			if (p->hue_blend==0xff)
			{
				seq_printf(m, "[1]{0}\n");
			}
			else
			{
				seq_printf(m, "[1]{hue_blend:%d,sat_blend:%d\n"\
					"l_gain_x:{%d,%d,%d,%d,%d,%d,%d,%d},l_gain_y:{%d,%d,%d,%d,%d,%d,%d,%d}\n"\
					"s_gain_x:{%d,%d,%d,%d,%d,%d,%d,%d},s_gain_y:{%d,%d,%d,%d,%d,%d,%d,%d}}\n",\
					p->hue_blend,p->sat_blend,\
					p->l_gain_x[0],p->l_gain_x[1],p->l_gain_x[2],p->l_gain_x[3],\
					p->l_gain_x[4],p->l_gain_x[5],p->l_gain_x[6],p->l_gain_x[7],\
					p->l_gain_y[0],p->l_gain_y[1],p->l_gain_y[2],p->l_gain_y[3],\
					p->l_gain_y[4],p->l_gain_y[5],p->l_gain_y[6],p->l_gain_y[7],\
					p->s_gain_x[0],p->s_gain_x[1],p->s_gain_x[2],p->s_gain_x[3],\
					p->s_gain_x[4],p->s_gain_x[5],p->s_gain_x[6],p->s_gain_x[7],\
					p->s_gain_y[0],p->s_gain_y[1],p->s_gain_y[2],p->s_gain_y[3],\
					p->s_gain_y[4],p->s_gain_y[5],p->s_gain_y[6],p->s_gain_y[7]);
			}
		}break;
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		{
			int i;
			unsigned short *p = g_v4l2_vpq_hdr_ygain_data;
			if (p[0]==0xff)
			{
				seq_printf(m, "{0}\n");
			}
			else
			{
				if (from_who==0)//pq-status
				{
					seq_printf(m, "{");
					seq_printf(m, "%d",p[0]);
					for (i=1;i<66;i++)
					{
						seq_printf(m, ",%d",p[i]);
					}
					seq_printf(m, "}");
				}
				else
				{
					seq_printf(m, "[0]{");
					for (i=0;i<66;i++)
					{
						seq_printf(m, "%x",p[i]);
						if (i==16)			seq_printf(m, "\n");
						else if (i==32)		seq_printf(m, "\n");
						else if (i==48)		seq_printf(m, "\n");
						else if (i==65)		seq_printf(m, "}");
						else				seq_printf(m, ",");
					}
				}
				seq_printf(m, "\n");
			}
			if (from_who==0)	break;//pq-status
			p = g_v4l2_vpq_hdr_ygain_data1;
			if (p[0]==0xff)
			{
				seq_printf(m, "[1]{0}\n");
			}
			else
			{
				seq_printf(m, "[1]{");
				for (i=0;i<66;i++)
				{
					seq_printf(m, "%x",p[i]);
					if (i==16)			seq_printf(m, "\n");
					else if (i==32)		seq_printf(m, "\n");
					else if (i==48)		seq_printf(m, "\n");
					else if (i==65)		seq_printf(m, "}");
					else				seq_printf(m, ",");
				}
				seq_printf(m, "\n");
			}
		}break;
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		{
			struct v4l2_ext_vpq_cmn_data param;
			short data[9];
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.wid = 0;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getgamutmatrixpre(&param);
			if (ret || data[0]==0xff)
			{
				seq_printf(m, "{0}\n");
			}
			else
			{
				seq_printf(m, "[0]{%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d}\n",\
					data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]);
			}
			memset(&param,0,sizeof(struct v4l2_ext_vpq_cmn_data));
			param.wid = 1;
			param.p_data = (unsigned char *)data;
			ret = vpq_hwrap_getgamutmatrixpre(&param);
			if (ret || data[0]==0xff)
			{
				seq_printf(m, "[1]{0}\n");
			}
			else
			{
				seq_printf(m, "[1]{%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d}\n",\
					data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]);
			}
		}break;
		case V4L2_CID_EXT_HDR_TONEMAP:
		{
			struct v4l2_ext_hdr_tonemap *p = &g_v4l2_vpq_hdr_tone_data;
			if (p->hdr_mode==0xff)
			{
				seq_printf(m, "{0}\n");
			}
			else
			{
				seq_printf(m, "[0]{hdr_mode:%x\n"\
					"r_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}\n"\
					"g_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}\n"\
					"b_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}}\n",p->hdr_mode,\
					p->r_data[0],p->r_data[1],p->r_data[2],p->r_data[30],p->r_data[31],p->r_data[32],\
					p->r_data[33],p->r_data[34],p->r_data[35],p->r_data[63],p->r_data[64],p->r_data[65],\
					p->g_data[0],p->g_data[1],p->g_data[2],p->g_data[30],p->g_data[31],p->g_data[32],\
					p->g_data[33],p->g_data[34],p->g_data[35],p->g_data[63],p->g_data[64],p->g_data[65],\
					p->b_data[0],p->b_data[1],p->b_data[2],p->b_data[30],p->b_data[31],p->b_data[32],\
					p->b_data[33],p->b_data[34],p->b_data[35],p->b_data[63],p->b_data[64],p->b_data[65]);
			}
			p = &g_v4l2_vpq_hdr_tone_data1;
			if (p->hdr_mode==0xff)
			{
				seq_printf(m, "[1]{0}\n");
			}
			else
			{
				seq_printf(m, "[1]{hdr_mode:%x\n"\
					"r_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}\n"\
					"g_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}\n"\
					"b_data:{%x,%x,%x..%x,%x,%x|%x,%x,%x..%x,%x,%x}}\n",p->hdr_mode,\
					p->r_data[0],p->r_data[1],p->r_data[2],p->r_data[30],p->r_data[31],p->r_data[32],\
					p->r_data[33],p->r_data[34],p->r_data[35],p->r_data[63],p->r_data[64],p->r_data[65],\
					p->g_data[0],p->g_data[1],p->g_data[2],p->g_data[30],p->g_data[31],p->g_data[32],\
					p->g_data[33],p->g_data[34],p->g_data[35],p->g_data[63],p->g_data[64],p->g_data[65],\
					p->b_data[0],p->b_data[1],p->b_data[2],p->b_data[30],p->b_data[31],p->b_data[32],\
					p->b_data[33],p->b_data[34],p->b_data[35],p->b_data[63],p->b_data[64],p->b_data[65]);
			}
		}break;
		#if 0	//legacy
		case (V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL+1):
		{
			LX_PE_HDR_LLLUT_T *p = &g_v4l2_vpq_hdr_lllut_data;
			if (p->lllut_en==0xff)
			{
				seq_printf(m, "\n");
			}
			else
			{
				seq_printf(m, "{lllut_en:%d,lllut_csc_en:%d,lllut_r:{%d,%d,%d,%d},lllut_g:{%d,%d,%d,%d},"\
					"lllut_b:{%d,%d,%d,%d},matrix{%d,%d,%d},blend_in_sel:%d,r2y_matrix:{%d,%d,%d},"\
					"blend_lut_x:{%d,%d,%d,%d},blend_lut_y:{%d,%d,%d,%d},hue_gain:%d,sat_gain:%d}\n",\
					p->lllut_en,p->lllut_csc_en,\
					p->lllut_r[0],p->lllut_r[1],p->lllut_r[126],p->lllut_r[127],\
					p->lllut_g[0],p->lllut_g[1],p->lllut_g[126],p->lllut_g[127],\
					p->lllut_b[0],p->lllut_b[1],p->lllut_b[126],p->lllut_b[127],\
					p->matrix[0],p->matrix[1],p->matrix[2],
					p->blend_in_sel,\
					p->r2y_matrix[0],p->r2y_matrix[1],p->r2y_matrix[2],\
					p->blend_lut_x[0],p->blend_lut_x[1],p->blend_lut_x[4],p->blend_lut_x[5],\
					p->blend_lut_y[0],p->blend_lut_y[1],p->blend_lut_y[4],p->blend_lut_y[5],\
					p->hue_gain,p->sat_gain);
			}
		}break;
		#endif
		default:
			seq_printf(m, "{not support}\n");
			break;
	}

	return 0;
}

