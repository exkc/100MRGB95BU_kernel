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
 *  @author		wonsik.do
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

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>

#include "os_util.h"
#include "../include/vbi_kapi.h"
#include "../vbi_kwrap.h"
#include "../vbi_drv.h"

#include "linux/v4l2-ext/v4l2-ext-vbi.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_DEVICE_VBI 1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int v4l2_vbi_device_init(void);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

UINT16 vbi_service_set = 0;
static struct v4l2_device v4l2_vbi_dev;
struct mutex v4l2_vbi_device_lock;

struct vbi_fh {
	struct v4l2_fh fh;
// need to add some private data
};

static struct platform_device v4l2_vbi_pdev = {
	.name = "v4l2_vbi",
	.id = -1,
};

static int vbi_slicer_enable(BOOLEAN enable);

static int v4l2_vbi_resume(struct device *dev)
{
	VBI_PRINT("%s\n", __func__);
        return 0;
}

static int v4l2_vbi_suspend(struct device *dev)
{
	VBI_PRINT("%s\n", __func__);
        return 0;
}

static struct dev_pm_ops const vbi_pm_ops = {
        .resume = v4l2_vbi_resume,
        .suspend = v4l2_vbi_suspend,
};

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO:
			return "V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO";
#ifdef V4L2_CID_EXT_VBI_FLUSH
		case V4L2_CID_EXT_VBI_FLUSH:
			return "V4L2_CID_EXT_VBI_FLUSH";
#endif
#ifdef V4L2_CID_EXT_VBI_SLICER_ENABLE
		case V4L2_CID_EXT_VBI_SLICER_ENABLE:
			return "V4L2_CID_EXT_VBI_SLICER_ENABLE";
#endif
#ifdef V4L2_CID_EXT_VBI_SLICER_DISABLE
		case V4L2_CID_EXT_VBI_SLICER_DISABLE:
			return "V4L2_CID_EXT_VBI_SLICER_DISABLE";
#endif
		default:
			return "Unkown";
	}
}

static int v4l2_vbi_fh_open(struct file *flie)
{
	int ret;
//	struct vbi_priv *p;
	struct vbi_fh *fh;

	VBI_PRINT("vbi:25032000, open...\n");

	fh = kzalloc(sizeof(struct vbi_fh), GFP_KERNEL);
	if (!fh)
	{
		VBI_PRINT("vbi:xxxxxxxx, allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	/* open vbi */
	ret = 0;

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* vbi initialize */
#ifdef SEETV_BRINGUP
	ret = vbi_kwrap_ttx_initializemodule();
	ret |= vbi_kwrap_ttx_enable();
#endif

	return ret;

}

static int v4l2_vbi_fh_release(struct file *flie)
{
	int ret;

	VBI_PRINT("vbi, close\n");

	ret = 0;

	v4l2_fh_release(flie);

#ifdef SEETV_BRINGUP
	ret = vbi_kwrap_ttx_disable();
#endif

	return ret;
}

static int v4l2_vbi_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret = 0;

	VBI_PRINT("vbi:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {

#ifdef V4L2_CID_EXT_VBI_FLUSH
		case V4L2_CID_EXT_VBI_FLUSH:
			{
				VBI_PRINT("[%s,%d] service [0x%x]\n",__F__,__L__,ctrl->value);

				if(vbi_service_set == 0)
				{
					VBI_PRINT("vbi service in Not set !!! \n");
					return -EINVAL;
				}
				else if( !(ctrl->value & (V4L2_SLICED_VBI_525 | V4L2_SLICED_VBI_625)) || (ctrl->value & ~(V4L2_SLICED_VBI_525 | V4L2_SLICED_VBI_625)))
				{
					VBI_PRINT("[%s,%d] wrong service value [0x%x]\n",__F__,__L__,ctrl->value);
					ret = -EINVAL;
				}

				if(ctrl->value & V4L2_SLICED_TELETEXT_B)
				{
					ret |= vbi_kwrap_ttx_resetbuffer();
				}
				if(ctrl->value & V4L2_SLICED_VPS)
				{
					ret |= vbi_kwrap_ttx_reset_vps();
				}
				if(ctrl->value & V4L2_SLICED_CAPTION_525)
				{
					ret |= vbi_kwrap_cc_resetbuffer();
				}
				if(ctrl->value & V4L2_SLICED_WSS_625)
				{
					ret |= vbi_kwrap_ttx_reset_wss();
				}
				break;
			}
#endif
#ifdef V4L2_CID_EXT_VBI_SLICER_ENABLE
		case V4L2_CID_EXT_VBI_SLICER_ENABLE:
			{
				ret = vbi_slicer_enable(true);
			}break;
#endif
#ifdef V4L2_CID_EXT_VBI_SLICER_DISABLE
		case V4L2_CID_EXT_VBI_SLICER_DISABLE:
			{
				ret = vbi_slicer_enable(false);
			}break;
#endif

		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_vbi_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;

	VBI_PRINT("vbi:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {

		default:
			ret = -EINVAL;
	}

	return 0;
}

static int vbi_try_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = -EINVAL;

	switch (ctrl->id) {

		default:
			ret = -EINVAL;
	}

	return ret;
}

static int vbi_set_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {

		default:
			return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_vbi_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = vbi_try_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
			ret = vbi_set_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int vbi_get_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
		case V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO:
			{
				UINT32	packet;
				UINT8 word1, cgms, aps;
				LX_VBI_CP_TYPE_T	result;
				struct v4l2_ext_vbi_copy_protection vbi_copy_protection_info;

				if(ctrl->size != sizeof(vbi_copy_protection_info))
				{
					VBI_ERROR("ctrl->size : %u != sizeof(v4l2_ext_vbi_copy_protection) : %zu", ctrl->size, sizeof(struct v4l2_ext_vbi_copy_protection));
					ret = -EINVAL;
					break;
				}
				result = vbi_kwrap_get_copyprotection_info(&packet);

				VBI_DEBUG("vbi:%s, result[0x%x], packet [0x%x]\n", __func__, result, packet);

				if ((int)result < (int)LX_VBI_CP_TYPE_NONE) {
					vbi_copy_protection_info.macrovision_cp_info = (enum v4l2_ext_vbi_macrovision)V4L2_EXT_VBI_MACROVISION_PSP_OFF;
					vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_PERMIT;
					vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_OFF;
					VBI_PRINT("Error! Return error of KADP_VBI_Get_CopyProtection_Info()\n");
					ret = -EINVAL;
					break;
				}
//				else if(result == LX_VBI_CP_TYPE_NONE) {vbi_copy_protection_info.macrovision_cp_info = V4L2_EXT_VBI_MACROVISION_PSP_OFF; ret=RET_OK; break;}
//				step #1. check macrovision copy protection
				else if(result & LX_VBI_CP_TYPE_ANALOG_1) {
					vbi_copy_protection_info.macrovision_cp_info = (enum v4l2_ext_vbi_macrovision)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_OFF;
				}
				else if(result & LX_VBI_CP_TYPE_ANALOG_2) {
					vbi_copy_protection_info.macrovision_cp_info = (enum v4l2_ext_vbi_macrovision)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_2;
				}
				else if(result & LX_VBI_CP_TYPE_ANALOG_3) {
					vbi_copy_protection_info.macrovision_cp_info = (enum v4l2_ext_vbi_macrovision)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_4;
				}
				else {
					vbi_copy_protection_info.macrovision_cp_info = (enum v4l2_ext_vbi_macrovision)V4L2_EXT_VBI_MACROVISION_PSP_OFF;
				}

				word1 = (packet >> 2) & 0x0F;

				if(word1 == 0)
				{
					cgms = (packet >> 6) & 0x03;
					aps = (packet >> 8) & 0x03;

					if(cgms == 0x0)
						vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_PERMIT;
					else if(cgms == 0x1)
						vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_ONCE;
					else if(cgms == 0x2)
						vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_RESERVED;
					else
						vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_NO_PERMIT;

					if(aps == 0x0)
						vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_OFF;
					else if(aps == 0x1)
						vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_2;
					else if(aps == 0x2)
						vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_OFF;
					else
						vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_4;
				}
				else {
					vbi_copy_protection_info.cgms_cp_info = (enum v4l2_ext_vbi_cgms)V4L2_EXT_VBI_CGMS_PERMIT;
					vbi_copy_protection_info.aps_cp_info = (enum v4l2_ext_vbi_aps)V4L2_EXT_VBI_MACROVISION_PSP_OFF;
				}
				VBI_DEBUG("vbi:%s, cgms_cp_info[0x%x], aps_cp_info[0x%x], macrovision_cp_info[0x%x]\n", __func__, vbi_copy_protection_info.cgms_cp_info, vbi_copy_protection_info.aps_cp_info, vbi_copy_protection_info.macrovision_cp_info);

				ret = RET_OK;


				if (copy_to_user(ctrl->ptr, &vbi_copy_protection_info, sizeof(struct v4l2_ext_vbi_copy_protection)) )
				{
					VBI_ERROR("copy error !!!!!\n");
					return -EINVAL;
					break;
				}
			}
			break;
		default:
			return -EINVAL;
	}
	return ret;
}

static int v4l2_vbi_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{

	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = vbi_get_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;

}

static int v4l2_vbi_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	__attribute__((unused)) struct vbi_fh *fh = __fh;
	static char chip_name[8];

	if(0){}
	else if(lx_chip () == LX_CHIP_O26)
		strncpy(chip_name, "o26", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_O24)
		strncpy(chip_name, "o24", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_O24)
		strncpy(chip_name, "m23", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_O22)
		strncpy(chip_name, "o22", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_E60)
		strncpy(chip_name, "e60", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_O20)
		strncpy(chip_name, "o20", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_M19)
		strncpy(chip_name, "m16p3", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_M19)
		strncpy(chip_name, "o18", sizeof(chip_name));
	else
		strncpy(chip_name, "???", sizeof(chip_name));

	strncpy(cap->card, "vbi", sizeof(cap->card)-1);
	strncpy(cap->driver, chip_name, sizeof(cap->driver) - 1);
	cap->driver[sizeof(cap->driver) - 1] = '\0';
	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_SLICED_VBI_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif
	cap->version = LINUX_VERSION_CODE;

	return 0;
}

static int v4l2_vbi_vidioc_g_fmt_sliced_vbi_cap(struct file *file, void *__fh,
				struct v4l2_format *f)
{

	int ret = 0;

	VBI_PRINT("vbi:g_fmt type 0x%x\n", f->type);

	if (f->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
	{
		f->fmt.sliced.service_set = vbi_service_set;
		VBI_PRINT("vbi:g_fmt service_set 0x%x\n", f->fmt.sliced.service_set);
		return ret;
	}

	return -EINVAL;

}
static int v4l2_vbi_vidioc_s_fmt_sliced_vbi_cap(struct file *file, void *__fh,
				struct v4l2_format *f)
{
	int ret = 0;

	VBI_PRINT("vbi:s_fmt type 0x%x\n", f->type);

	if (f->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
	{
		VBI_PRINT("vbi:s_fmt service_set 0x%x\n", f->fmt.sliced.service_set);

		if(vbi_service_set)
			VBI_PRINT("vbi:prev service set 0x%x\n", vbi_service_set);

		if(f->fmt.sliced.service_set == V4L2_SLICED_CAPTION_525)
		{
			if(vbi_service_set == 0)
				ret = vbi_kwrap_cc_initializemodule();
			else
			{
				VBI_PRINT("vbi:s_fmt Error 0x%x => 0x%x\n", vbi_service_set, f->fmt.sliced.service_set);
				return -EINVAL;
			}
			vbi_service_set = f->fmt.sliced.service_set;
		}
		else if(f->fmt.sliced.service_set & (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_WSS_625 | V4L2_SLICED_VPS) )
		{
			if(vbi_service_set == 0)
				ret = vbi_kwrap_ttx_initializemodule();
			else if(f->fmt.sliced.service_set & V4L2_SLICED_VPS )
			{
				vbi_kwrap_ttx_reset_vps();
				vbi_kwrap_ttx_enable_vps_slicer(TRUE);
				vbi_kwrap_ttx_set_tt_slicer_mode(1);
			}
			else if( (vbi_service_set & V4L2_SLICED_VPS ) && !(f->fmt.sliced.service_set & V4L2_SLICED_VPS))
			{
				vbi_kwrap_ttx_enable_vps_slicer(FALSE);
				vbi_kwrap_ttx_set_tt_slicer_mode(0);
				vbi_kwrap_ttx_reset_vps();
			}
			else
			{
				VBI_PRINT("vbi:s_fmt Error !!! 0x%x => 0x%x\n", vbi_service_set, f->fmt.sliced.service_set);
				return -EINVAL;
			}

			vbi_service_set = f->fmt.sliced.service_set;
		}
		return ret;
	}

	return -EINVAL;

}

static int vbi_slicer_enable(BOOLEAN enable)
{
	int ret = 0;

	if(enable) {
		if(vbi_service_set == V4L2_SLICED_CAPTION_525)
		{
			if(vbi_kwrap_cc_enable() < 0)
			{
				VBI_ERROR("Failed Enabling VBI CC!\n");
				ret = -EFAULT;
			}
			else
			{
				VBI_PRINT("CC enable Success!\n");
			}
		}
		else if(vbi_service_set & (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_WSS_625 | V4L2_SLICED_VPS) )
		{
			if(vbi_kwrap_ttx_enable() < 0)
			{
				VBI_ERROR("Failed Enabling VBI TTX!\n");
				ret = -EFAULT;
			}
			else
			{
				VBI_PRINT("TTX enable Success!\n");
			}
		}
		else
			ret = -EINVAL;
	}
	else {
		if(vbi_service_set == V4L2_SLICED_CAPTION_525)
		{
			if(vbi_kwrap_cc_disable() < 0)
			{
				VBI_ERROR("Failed Disabling VBI CC!\n");
				ret = -EFAULT;
			}
			else
			{
				VBI_PRINT("CC Disable Success!\n");
			}
		}
		else if(vbi_service_set & (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_WSS_625 | V4L2_SLICED_VPS) )
		{
			if(vbi_kwrap_ttx_disable() < 0)
			{
				VBI_ERROR("Failed Disabling VBI TTX!\n");
				ret = -EFAULT;
			}
			else
			{
				VBI_PRINT("TTX Disable Success!\n");
			}
		}
		else
			ret = -EINVAL;
	}
	return ret;
}

static int v4l2_vbi_vidioc_streamon(struct file *file, void *__fh, enum v4l2_buf_type i)
{
	int ret = 0;

	VBI_PRINT("vbi:%s, type %d\n", __func__, i);

	if( i!= V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
		return -EINVAL;

	ret = vbi_slicer_enable(true);

	return ret;

}

static int v4l2_vbi_vidioc_streamoff(struct file *file, void *__fh, enum v4l2_buf_type i)
{
	int ret;

	VBI_PRINT("vbi:%s, type %d\n", __func__, i);

	if( i!= V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
		return -EINVAL;

	ret = vbi_slicer_enable(false);

	return ret;

}

static int v4l2_vbi_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	VBI_PRINT("vbi type 0x%x, id 0x%x\n", sub->type, sub->id);

	switch (sub->type)
	{
		/*
		case V4L_VDEC_1_EVENT:
		case V4L_VDEC_2_EVENT:
		case V4L_VDEC_3_EVENT:
		case V4L_VDEC_4_EVENT:
			return v4l2_event_subscribe(__fh, sub, 32, NULL);
			*/
		default:
			return -EINVAL;
	}
}

static unsigned int v4l2_vbi_poll(struct file *file, poll_table *wait)
{
	struct vbi_fh *fh = (struct vbi_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	VBI_PRINT("vbi:req_events 0x%lx\n", req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
		/*
		poll_wait(file, &p->vbi_poll_wq, wait);

		if (p->vbi_poll & POLLIN)
			rc |= POLLIN;
		if (p->vbi_poll & POLLOUT)
			rc |= POLLOUT;
		if (p->vbi_poll & POLLERR)
			rc |= POLLERR;
			*/
	}

	VBI_PRINT("vbi: rc 0x%x\n", rc);

	return rc;
}

static ssize_t v4l2_vbi_read(struct file *file, char __user *data, size_t count, loff_t *ppos)
{
	ssize_t ret = 0;
	int i = 0;
	LX_CC_DATA_T CC_Data_Buffer;
	struct v4l2_sliced_vbi_data vbi_data = {0,};

//	VBI_DEBUG("read request count[%d]\n", count);


	if( (count < sizeof(struct v4l2_sliced_vbi_data) )  && (count > 0) )
		ret = -EINVAL;

	if(vbi_service_set & V4L2_SLICED_WSS_625)
	{
		volatile UINT8 *_pu8WSS = NULL;

		do {
			if( ( ( i * sizeof(struct v4l2_sliced_vbi_data) ) >=  count ) && (count > 0) )
			{
				VBI_ERROR("read buffer full[%d], vbi data[%d] !!!!!\n", (int)count, i);
				break;
			}

			if(vbi_kwrap_ttx_get_wss_packetstask((void*)&_pu8WSS))
				break;

			if(_pu8WSS != NULL)
			{
				memset(&vbi_data, 0, sizeof(struct v4l2_sliced_vbi_data));

				vbi_data.id = V4L2_SLICED_WSS_625;
				vbi_data.field = 0;
				vbi_data.line = 23;
//				vbi_data.data[0] = *_pu8WSS;
				memcpy((void *)&vbi_data.data[0], (void *)_pu8WSS, 14); //4:3 WSS, 13:12 copy right information
				ret += sizeof(struct v4l2_sliced_vbi_data);

				WSS_PKT_PRINT("V4L2 WSS [%14ph] , i %d, ret %d \n", (UINT8 *)&vbi_data.data[0], i, (int)ret);

				if (copy_to_user((void *)((uintptr_t)data + (uintptr_t)(i*sizeof(struct v4l2_sliced_vbi_data))), (void *)&vbi_data, sizeof(struct v4l2_sliced_vbi_data))) {
					VBI_ERROR("copy error !!!!!\n");
					break;
				}
				i++;

			}
			else
				VBI_DEBUG("WSS data null !!!!!\n");

		} while (0);
	}

	if(vbi_service_set & V4L2_SLICED_VPS )
	{
		volatile UINT8 *_pu8VPS = NULL;

		do {
			if( ( ( i * sizeof(struct v4l2_sliced_vbi_data) ) >=  count ) && (count > 0) )
			{
				VBI_ERROR("read buffer full[%d], vbi data[%d] !!!!!\n", (int)count, i);
				break;
			}

			if(vbi_kwrap_ttx_get_vps_packetstask((void*)&_pu8VPS))
				break;

			if(_pu8VPS != NULL){
				memset(&vbi_data, 0, sizeof(struct v4l2_sliced_vbi_data));

				vbi_data.id = V4L2_SLICED_VPS;
				vbi_data.field = 0;
				vbi_data.line = 16;
				memcpy((void *)&vbi_data.data[0], (void *)&_pu8VPS[2], 13); //Byte number 3 to 15
				ret += sizeof(struct v4l2_sliced_vbi_data);
				if(1) 
				{
					VPS_PKT_PRINT("VPS read i[%d],id[0x%x],field[%d],line[%d],data0/15[%16ph]\n" \
							, i, vbi_data.id, vbi_data.field, vbi_data.line, (UINT8 *)&vbi_data.data[0]);
				}

				if (copy_to_user((void *)((uintptr_t)data + (uintptr_t)(i*sizeof(struct v4l2_sliced_vbi_data))), (void *)&vbi_data, sizeof(struct v4l2_sliced_vbi_data))) {
					VBI_ERROR("copy error !!!!!\n");
					break;
				}
				i++;
			}
			else
				VBI_DEBUG("VPS data null !!!!!\n");
		} while (0);
	}

	if(vbi_service_set & V4L2_SLICED_CAPTION_525)
	{
		for(; ((i*sizeof(struct v4l2_sliced_vbi_data)) <count) && (count > 0);i++)
		{
			vbi_kwrap_cc_get_cc_datatask(&CC_Data_Buffer);
			if(CC_Data_Buffer.line_number == 0)	//No CC Data
			{
//				VBI_DEBUG("No CC data to read \n");
				break;
			}
			vbi_data.id =V4L2_SLICED_CAPTION_525;
			vbi_data.field = CC_Data_Buffer.field;
			vbi_data.line = CC_Data_Buffer.line_number;
			vbi_data.data[0] = CC_Data_Buffer.data1;
			vbi_data.data[1] = CC_Data_Buffer.data2;
			vbi_data.reserved = 0U;
			ret += sizeof(struct v4l2_sliced_vbi_data);
			CC_PKT_PRINT("CC read i[%d],id[0x%x],field[%d],line[%d],data0/1[0x%x,0x%x]\n", i, vbi_data.id, vbi_data.field, vbi_data.line,\
					vbi_data.data[0], vbi_data.data[1]);

			if (copy_to_user((void *)((uintptr_t)data + (uintptr_t)(i*sizeof(struct v4l2_sliced_vbi_data))), (void *)&vbi_data, sizeof(struct v4l2_sliced_vbi_data))) {
				VBI_ERROR("copy error !!!!!\n");
				break;
			}
		}
	}
	else if(vbi_service_set & V4L2_SLICED_TELETEXT_B)
	{
		volatile LX_TTX_PACKET_TYPE_T *gptPB;
		int k = 0;

//		for(i=0; i<count;i+=sizeof(struct v4l2_sliced_vbi_data))
		do {
			if( ((count / sizeof(struct v4l2_sliced_vbi_data)) - i ) <= 0)
				break;

			if( count > 0 ) 
				vbi_kwrap_ttx_get_ttx_packetstask((void*)&gptPB, (count / sizeof(struct v4l2_sliced_vbi_data)) - i );	// -i for WSS/VPS
			else
				vbi_kwrap_ttx_get_ttx_packetstask((void*)&gptPB, 0);

			if (gptPB != NULL)
			{
				if(gptPB->TTX_Packet_Unit == 0)
				{
					VBI_DEBUG("No TTX data to read\n");
					memset(&vbi_data, 0, sizeof(struct v4l2_sliced_vbi_data));
//					ret = 0;
					break;
				}

				if(gptPB->TTX_Packet_Unit > 300) // Too large ttx data in buffer
				{
					VBI_PRINT("Buffer Overflow\n");
					memset(&vbi_data, 0, sizeof(struct v4l2_sliced_vbi_data));
					vbi_kwrap_ttx_resetbuffer();
				//	ret = 0;
					break;
				}

				if(1)
				{
					int j;
					TTX_PKT_PRINT("TTX Read address from [0x%p] , size [0x%x]\n", &gptPB->pTTX_Packet_Buffer[0], gptPB->TTX_Packet_Unit);
					for(j=0;j<(gptPB->TTX_Packet_Unit*LX_TTX_PACKET_UNIT);j+=LX_TTX_PACKET_UNIT)
					{
						TTX_PKT_PRINT("pkt[%d]:d[%48ph]\n",j, (UINT8 *)&gptPB->pTTX_Packet_Buffer[0+j]);
					}
				}

			}
			else {
				memset(&vbi_data, 0, sizeof(struct v4l2_sliced_vbi_data));
//				ret = 0;
				VBI_PRINT("TTX gptPB NULL\n");
				break;
			}

			for(k = 0; k<gptPB->TTX_Packet_Unit;k++)
			{
				vbi_data.id = V4L2_SLICED_TELETEXT_B;
				vbi_data.field = 0;
				vbi_data.line = 0;
				/* re examin below code : memcpy crash with unaligned memcpy */
				//memcpy_fromio((void *)&vbi_data.data[0], (void *)&gptPB->pTTX_Packet_Buffer[3 + k*LX_TTX_PACKET_UNIT], LX_TTX_PACKET_UNIT - 3);	// 190618 45byte copy //exclude clock run-in and framing code(42byte)
				memcpy((void *)&vbi_data.data[0], (void *)&gptPB->pTTX_Packet_Buffer[6 + k*LX_TTX_PACKET_UNIT], LX_TTX_PACKET_UNIT - 6);	// 190618 42byte copy ,exclude clock run-in and framing code(42byte) and ttx_info, line number, field number
				ret += sizeof(struct v4l2_sliced_vbi_data);
				VBI_DEBUG("TTX read i[%d],id[0x%x],field[%d],line[%d],data[%42ph]\n", i, vbi_data.id, vbi_data.field, vbi_data.line, (UINT8 *)&vbi_data.data[0]);
				if (copy_to_user((void *)((uintptr_t)data + (uintptr_t)(i*sizeof(struct v4l2_sliced_vbi_data))), (void *)&vbi_data, sizeof(struct v4l2_sliced_vbi_data))) {
					VBI_ERROR("copy error !!!!!\n");
					break;
				}
				i++;
			}
		} while (0);
	}

	VBI_DEBUG("vbi read count[%d], ret[%d], i[%d], vbi_service_set[0x%x]\n", (int)count, (int)ret, i, vbi_service_set);

	return ret;
}

struct v4l2_file_operations v4l2_vbi_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_vbi_fh_open,
	.release	= v4l2_vbi_fh_release,
	.unlocked_ioctl = video_ioctl2,
	.read = v4l2_vbi_read,
//	.mmap = vb2_fop_mmap,
	.poll = v4l2_vbi_poll,
};

struct v4l2_ioctl_ops v4l2_vbi_ioctl_ops = {
	.vidioc_querycap		= v4l2_vbi_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_vbi_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_vbi_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_vbi_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_vbi_vidioc_g_ext_ctrls,
	.vidioc_s_fmt_sliced_vbi_cap	= v4l2_vbi_vidioc_s_fmt_sliced_vbi_cap,
	.vidioc_g_fmt_sliced_vbi_cap	= v4l2_vbi_vidioc_g_fmt_sliced_vbi_cap,
	.vidioc_streamon		= v4l2_vbi_vidioc_streamon,
	.vidioc_streamoff		= v4l2_vbi_vidioc_streamoff,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_vbi_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static int v4l2_vbi_probe(struct platform_device *pdev)
{
	VBI_PRINT("vbi  %s\n", __func__);

	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vbi_remove(struct platform_device *pdev)
{
	VBI_PRINT("vbi  %s\n", __func__);
}
#else
static int v4l2_vbi_remove(struct platform_device *pdev)
{
	VBI_PRINT("vbi  %s\n", __func__);

	return 0;
}
#endif

static struct platform_driver v4l2_vbi_driver = {
	.probe      = v4l2_vbi_probe,
	.driver     = {
		.name   = "v4l2_vbi",
		.owner  = THIS_MODULE,
		.pm     = &vbi_pm_ops,
	},
	.remove		= v4l2_vbi_remove,
};

static struct video_device v4l2_vbi_video_dev = {
	.v4l2_dev  = &v4l2_vbi_dev,
	.fops      = &v4l2_vbi_fops,
	.ioctl_ops = &v4l2_vbi_ioctl_ops,
	.release   = video_device_release_empty,
	.lock      = &v4l2_vbi_device_lock,
	.vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_SLICED_VBI_CAPTURE
#endif
};

static int v4l2_vbi_register(void *arg)
{
	int ret;

	VBI_PRINT("vbi  %s\n", __func__);

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_vbi_pdev.dev, &v4l2_vbi_dev);
		if(ret < 0){
			VBI_PRINT(" vbi : v4l2_device_register error[%d]\n", ret);
			break;
		}

		ret = video_register_device(&v4l2_vbi_video_dev, VFL_TYPE_VBI, V4L2_DEVICE_VBI);
		if (ret < 0) {
			VBI_PRINT("video device register error: %d\n", ret);
			return -1;
		}

	} while(0);

	return ret;
}

int v4l2_vbi_device_init(void)
{
	VBI_PRINT("vbi  %s\n", __func__);
	platform_driver_register(&v4l2_vbi_driver);
	platform_device_register(&v4l2_vbi_pdev);

	mutex_init(&v4l2_vbi_device_lock);
	//video_set_drvdata(&v4l2_vsc_video_dev, &vsc_pdev);
	v4l2_vbi_register(NULL);

	return 0;
}
