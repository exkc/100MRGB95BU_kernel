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
 *  @date		2018-06-05
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
#include <linux/pm_runtime.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>

#include "os_util.h"
#include "../include/afe_kapi.h"
#include "../afe_kwrap.h"
#include "../afe_drv.h"

#include "linux/v4l2-ext/v4l2-ext-avd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* SCDCR-4006 */
#define AVD_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::avd\n",\
			_level,"video",V4L2_EXT_DEV_NO_AV,_g_v4l2_avd_open_count,\
			current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

int v4l2_avd_device_init(void);
int avd_update_device_info(void);
int v4l2_avd_pm_runtime_help(char* buffer);
int v4l2_avd_pm_runtime_test(char* command);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device v4l2_avd_dev;
struct mutex v4l2_avd_video_device_lock;

struct avd_dev {
	struct platform_device *pdev;
};

struct avd_fh {
	struct v4l2_fh fh;
// need to add some private data
//	struct avd_priv *avd_priv;
};

enum v4l2_ext_avd_input_src _g_avd_input_src = V4L2_EXT_AVD_INPUT_SRC_NONE;

static int _g_avd_port = 1;
static int _g_SyncDetectionForTunning = 0;

static struct platform_device v4l2_avd_pdev = {
	.name = "v4l2_avd",
	.id = -1,
};

AVD_DEV_INFO_T avd_device_info;

static int _g_v4l2_avd_open_count = 0;

static int v4l2_avd_resume(struct device *dev)
{
	//avd resume is moved to CVD_RunResume()
	/*
	int ret;
	LX_AFE_CVD_SOURCE_ATTRIBUTE_T source_attribute;
	LX_AFE_CVD_INPUT_PORT_T cvbs_input_port;
	*/

	AFE_PRINT("%s\n", __func__);

	/*
	if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_NONE)
	{
        return 0;
	}
	else if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_ATV)
		source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF;
	else if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_AV)
		source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV;
	else
		return -EPERM;

	cvbs_input_port = _g_avd_port;

	AFE_PRINT("cvd input port [%d], source_attribute [%d]\n", cvbs_input_port, source_attribute);

	ret = afe_kwrap_cvd_connectmodule(source_attribute, cvbs_input_port);

	return ret;
	*/
	return 0;
}

static int v4l2_avd_suspend(struct device *dev)
{
	AFE_PRINT("%s : port[%d], source_attribute [%d]\n", __func__, _g_avd_port, _g_avd_input_src);
	return 0;
}

static int v4l2_avd_runtime_resume(struct device *dev)
{
	struct avd_dev *drv = dev_get_drvdata(dev);

	AFE_PRINT("start\n");

	if (!drv)		{AFE_ERROR("drv null\n");return 0;}
	if (!drv->pdev)	{AFE_ERROR("pdev null\n");return 0;}

	/* TODO : restore resource */

	AFE_PRINT("end\n");
	AVD_PM_INFO("info","resume","ok");
	return 0;
}

static int v4l2_avd_runtime_suspend(struct device *dev)
{
	struct avd_dev *drv = dev_get_drvdata(dev);

	AFE_PRINT("start\n");

	if (!drv)		{AFE_ERROR("drv null\n");return 0;}
	if (!drv->pdev)	{AFE_ERROR("pdev null\n");return 0;}

	/* TODO : release resource */

	AFE_PRINT("end\n");
	AVD_PM_INFO("info","suspend","ok");
	return 0;
}

static struct dev_pm_ops const avd_pm_ops = {
        .resume = v4l2_avd_resume,
        .suspend = v4l2_avd_suspend,
        .runtime_resume = v4l2_avd_runtime_resume,
        .runtime_suspend = v4l2_avd_runtime_suspend,
};

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_AVD_TIMING_INFO:
			return "V4L2_CID_EXT_AVD_TIMING_INFO";
		case V4L2_CID_EXT_AVD_AUTO_TUNING_MODE:
			return "V4L2_CID_EXT_AVD_AUTO_TUNING_MODE";
		case V4L2_CID_EXT_AVD_VIDEO_SYNC:
			return "V4L2_CID_EXT_AVD_VIDEO_SYNC";
		case V4L2_CID_EXT_AVD_PORT:
			return "V4L2_CID_EXT_AVD_PORT";
		default:
			return "Unkown";
	}
}

static int v4l2_avd_fh_open(struct file *flie)
{
	int ret, ret0;
//	struct avd_priv *p;
	struct avd_fh *fh;
	struct avd_dev *dev  = video_drvdata(flie);

	AVD_DEV_INFO_T *avd_dev = NULL;

	avd_dev = &avd_device_info;
	avd_dev->avd_open++;

	AFE_PRINT("avd:22051800, open...\n");

	ret0 = pm_runtime_get_sync(&dev->pdev->dev);
	AFE_PRINT("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct avd_fh), GFP_KERNEL);
	if (!fh)
	{
		AFE_PRINT("avd:xxxxxxxx, allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}
	else
		AFE_PRINT("%s\n", __func__);

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	/* open avd */
	ret = 0;

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* avd initialize */
	ret = afe_kwrap_cvd_initializemodule();
	ret |= afe_kwrap_cvd_enablemodule();

	/* increment open counter */
	_g_v4l2_avd_open_count++;
	AVD_PM_INFO("info","open","ok");

	return ret;

/*
fail_fh:
	kfree(fh);
	return ret;
*/

}

static int v4l2_avd_fh_release(struct file *flie)
{
	int ret, ret0;
	__attribute__((unused)) struct avd_fh *fh = flie->private_data;
	struct avd_dev *dev  = video_drvdata(flie);

	AVD_DEV_INFO_T *avd_dev = NULL;

	avd_dev = &avd_device_info;
	avd_dev->avd_open = 0;

	AFE_PRINT("avd, close\n");
	AFE_PRINT("%s\n", __func__);

	ret = 0;

	v4l2_fh_release(flie);

	ret = afe_kwrap_cvd_disablemodule();
	ret |= afe_kwrap_cvd_uninitializemodule();

	ret0 = pm_runtime_put(&dev->pdev->dev);
	AFE_PRINT("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	/* decrement open counter */
	_g_v4l2_avd_open_count--;
	AVD_PM_INFO("info","close","ok");

	return ret;
}

static int v4l2_avd_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	__attribute__((unused)) struct avd_fh *fh = __fh;

	AFE_PRINT("avd:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {

		case V4L2_CID_EXT_AVD_PORT:
			{
				__attribute__((unused)) BOOLEAN cal_src_type;	// TRUE : RGB, FALSE : Component

				if(ctrl->value < 3 && ctrl->value > 0 )
				{
					_g_avd_port = ctrl->value;

					AFE_PRINT("[%s,%d] set : avd_port [%d]\n",__F__,__L__,_g_avd_port);
					ret = 0;
				}
				else
				{
					AFE_ERROR("[%s,%d] wrong avd_port [%d]\n",__F__,__L__,_g_avd_port);
					ret = -EINVAL;
				}

				break;
			}

		case V4L2_CID_EXT_AVD_AUTO_TUNING_MODE:
			{
				AFE_PRINT("[%s,%d] set : SyncDetectionForTunning [%d]\n",__F__,__L__,ctrl->value);

				if(ctrl->value == 0)
				{
					_g_SyncDetectionForTunning = ctrl->value;

					afe_kwrap_cvd_setsyncdetectionfortuning(FALSE);

					ret = 0;
				}
				else if (ctrl->value == 1)
				{
					_g_SyncDetectionForTunning = ctrl->value;

					afe_kwrap_cvd_setsyncdetectionfortuning(TRUE);

					ret = 0;
				}
				else
				{
					AFE_ERROR("[%s,%d] wrong value [%d]\n",__F__,__L__,_g_avd_port);
					ret = -EINVAL;
				}

				break;
			}

		case V4L2_CID_EXT_AVD_CHANNEL_CHANGE:
			{
				CVD_DEBUG("[%s,%d] set : AVD Channel Change \n",__F__,__L__);

				ret = 0;

				break;
			}


		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_avd_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	__attribute__((unused)) struct avd_fh *fh = __fh;

//	CVD_DEBUG("avd:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_AVD_PORT:
			{
				ctrl->value = _g_avd_port;
				ret = 0;
				break;
			}

		case V4L2_CID_EXT_AVD_AUTO_TUNING_MODE:
			{
				ctrl->value = _g_SyncDetectionForTunning;
				ret = 0;
				break;
			}

		case V4L2_CID_EXT_AVD_VIDEO_SYNC:
			{
				BOOLEAN cvd_sync;
				afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &cvd_sync);
				if(cvd_sync)
					ctrl->value = 1;
				else
					ctrl->value = 0;
				ret = 0;
				break;
			}
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int avd_try_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_EXT_AVD_TIMING_INFO:
		if ( (ctrl->ptr != NULL) && (ctrl->size == sizeof(struct v4l2_ext_avd_timing_info)) )
			ret = 0;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static int avd_set_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	default:
		return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_avd_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	__attribute__((unused)) struct avd_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = avd_try_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
			ret = avd_set_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int avd_get_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_AVD_TIMING_INFO:
		{
			struct v4l2_ext_avd_timing_info avd_timing_info;

			LX_AFE_CVD_TIMING_INFO_T cvd_timing_info;
			BOOLEAN cvd_sync;
			UINT32	cvd_lock_status;

			afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_timing_info);
			afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &cvd_sync);
			afe_kwrap_cvd_get_lock_states(LX_CVD_MAIN, &cvd_lock_status);

			memset(&avd_timing_info, 0, sizeof(struct v4l2_ext_avd_timing_info) );

			// for AV input vlock flag on for short period after cable disconnected...
			// so prevent  vlock/vdlock flag after cable disconnect, if color system is not detected clear lock flags.
			if ( ( (cvd_sync == FALSE) || (cvd_timing_info.cvd_standard >= LX_NON_STANDARD) ) && \
					( _g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_AV ) )
			{
				//above memset cleared pInfo.
			}
			else
			{
				avd_timing_info.h_freq = cvd_timing_info.u16_HFreq;
				avd_timing_info.v_freq = cvd_timing_info.u16_VFreq;
				avd_timing_info.h_porch = cvd_timing_info.u16_HStart;
				avd_timing_info.v_porch = cvd_timing_info.u16_VStart;
				avd_timing_info.active.w = cvd_timing_info.u16_HSize;
				avd_timing_info.active.h = cvd_timing_info.u16_VSize;

				if(cvd_sync)
					avd_timing_info.vd_lock = TRUE;
				else
					avd_timing_info.vd_lock = FALSE;

				if(cvd_lock_status & LX_HLOCK)
					avd_timing_info.h_lock = TRUE;
				else
					avd_timing_info.h_lock = FALSE;

				if(cvd_lock_status & LX_VLOCK)
					avd_timing_info.v_lock = TRUE;
				else
					avd_timing_info.v_lock = FALSE;
			}


			/*
			switch(cvd_timing_info.cvd_standard)
			{
				case LX_NTSC_M :	// NTSC_M
					avd_timing_info.standard = V4L2_STD_NTSC;
					break;

				case LX_NTSC_443 :	//
					avd_timing_info.standard = V4L2_STD_NTSC_443;
					break;

				case LX_PAL_BG :
					avd_timing_info.standard = V4L2_STD_PAL;
					break;

				case LX_PAL_M :
					avd_timing_info.standard = V4L2_STD_PAL_M;
					break;

				case LX_PAL_CN :	//PAL-Cn
					avd_timing_info.standard = V4L2_STD_PAL_Nc;
					break;

				case LX_PAL_60 :	//PAL-60
					avd_timing_info.standard = V4L2_STD_PAL_60;
					break;

				case LX_SECAM :
					avd_timing_info.standard = V4L2_STD_SECAM;
					break;

				case LX_NON_STANDARD :
				default :
					if ( (cvd_lock_status & LX_VLOCK) != LX_VLOCK )
						avd_timing_info.standard = V4L2_STD_UNKNOWN;
					else if(cvd_timing_info.u16_VFreq < 550)
						avd_timing_info.standard = V4L2_STD_625_50;
					else
						avd_timing_info.standard = V4L2_STD_525_60;
					break;
			}
			*/

			ret |= copy_to_user(ctrl->ptr, &avd_timing_info, sizeof(struct v4l2_ext_avd_timing_info));
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static int v4l2_avd_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	__attribute__((unused)) struct avd_fh *fh = __fh;

	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = avd_try_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
			ret = avd_get_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;

}

static int v4l2_avd_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	__attribute__((unused)) struct avd_fh *fh = __fh;

	static char chip_name[8];

	if(0){}
	else if(lx_chip () == LX_CHIP_O26)
		strncpy(chip_name, "o26", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_O24)
		strncpy(chip_name, "o24", sizeof(chip_name));
	else if(lx_chip () == LX_CHIP_M23)
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

	strncpy(cap->card, "av", sizeof(cap->card)-1);
//	strncpy(cap->driver, chip_name, sizeof(chip_name));
	strncpy(cap->driver, chip_name, sizeof(cap->driver) - 1);
	cap->driver[sizeof(cap->driver) - 1] = '\0';
	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif
	cap->version = LINUX_VERSION_CODE;

	return 0;

}

static int v4l2_avd_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	__attribute__((unused)) struct avd_fh *fh = __fh;
	int ret;
	LX_AFE_CVD_SOURCE_ATTRIBUTE_T source_attribute;
	LX_AFE_CVD_INPUT_PORT_T cvbs_input_port;

	AFE_PRINT("avd: input %d, port %d\n", i, _g_avd_port);

	/* save source type and port for resume */
	_g_avd_input_src = i;

	if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_NONE)
	{
		ret = afe_kwrap_cvd_disconnectmodule();
		return ret;
	}
	else if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_ATV)
		source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF;
	else if(_g_avd_input_src == V4L2_EXT_AVD_INPUT_SRC_AV)
		source_attribute = LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV;
	else
		return -EPERM;

	cvbs_input_port = _g_avd_port;

	AFE_PRINT("cvd input port [%d], source_attribute [%d]\n", cvbs_input_port, source_attribute);

	ret = afe_kwrap_cvd_connectmodule(source_attribute, cvbs_input_port);

	return ret;
}
static int v4l2_avd_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	__attribute__((unused)) struct avd_fh *fh = __fh;
	int ret;

	if(i == NULL)
		return -EPERM;
	else
		ret = 0;

	AFE_PRINT("avd: get input %d\n", *i);

	*i = _g_avd_input_src;

	return ret;
}

__attribute__((unused)) static int v4l2_avd_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	AFE_PRINT("avd type 0x%x, id 0x%x\n", sub->type, sub->id);

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

__attribute__((unused)) static unsigned int v4l2_avd_poll(struct file *file, poll_table *wait)
{
	struct avd_fh *fh = (struct avd_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	AFE_PRINT("avd:req_events 0x%lx\n", req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
		/*
		poll_wait(file, &p->avd_poll_wq, wait);

		if (p->avd_poll & POLLIN)
			rc |= POLLIN;
		if (p->avd_poll & POLLOUT)
			rc |= POLLOUT;
		if (p->avd_poll & POLLERR)
			rc |= POLLERR;
			*/
	}

	AFE_PRINT("avd: rc 0x%x\n", rc);

	return rc;
}

static int v4l2_avd_vidioc_g_std(struct file *file, void *fh, v4l2_std_id *pColorSystem)
{
	int ret;

	LX_AFE_CVD_TIMING_INFO_T cvd_timing_info;
	UINT32	cvd_lock_status;
	v4l2_std_id ColorSystem;

	ret = afe_kwrap_cvd_get_lock_states(LX_CVD_MAIN, &cvd_lock_status);

	if ( (cvd_lock_status & LX_VLOCK) != LX_VLOCK )
		ColorSystem = V4L2_STD_UNKNOWN;
	else
	{
		ret |= afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &cvd_timing_info);

		switch(cvd_timing_info.cvd_standard)
		{
			case LX_NTSC_M :	// NTSC_M
				ColorSystem = V4L2_STD_NTSC;
				break;

			case LX_NTSC_443 :	//
				ColorSystem = V4L2_STD_NTSC_443;
				break;

			case LX_PAL_BG :
				ColorSystem = V4L2_STD_PAL;
				break;

			case LX_PAL_M :
				ColorSystem = V4L2_STD_PAL_M;
				break;

			case LX_PAL_CN :	//PAL-Cn
				ColorSystem = V4L2_STD_PAL_Nc;
				break;

			case LX_PAL_60 :	//PAL-60
				ColorSystem = V4L2_STD_PAL_60;
				break;

			case LX_SECAM :
				ColorSystem = V4L2_STD_SECAM;
				break;

			case LX_NON_STANDARD :
			default :
				if(cvd_timing_info.u16_VFreq < 550)
					ColorSystem = V4L2_STD_625_50;
				else
					ColorSystem = V4L2_STD_525_60;
				break;
		}
	}
	*pColorSystem = ColorSystem;

	return ret;
}

static int v4l2_avd_vidioc_s_std(struct file *file, void *fh, v4l2_std_id ColorSystem)
{
	LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T 	support_color_system = 0;
	v4l2_std_id v4l2_colorSystem;

	v4l2_colorSystem = ColorSystem;
    AFE_PRINT("%s : set v4l2 color system = [0x%llx]\n",__func__ ,v4l2_colorSystem);

	if(v4l2_colorSystem & V4L2_STD_NTSC)
		support_color_system |= LX_COLOR_SYSTEM_NTSC_M;
	if(v4l2_colorSystem & V4L2_STD_PAL)
		support_color_system |= LX_COLOR_SYSTEM_PAL_G;
	if(v4l2_colorSystem & V4L2_STD_PAL_Nc)
		support_color_system |= LX_COLOR_SYSTEM_PAL_NC;
	if(v4l2_colorSystem & V4L2_STD_PAL_M)
		support_color_system |= LX_COLOR_SYSTEM_PAL_M;
	if(v4l2_colorSystem & V4L2_STD_SECAM)
		support_color_system |= LX_COLOR_SYSTEM_SECAM;
	if(v4l2_colorSystem & V4L2_STD_NTSC_443)
		support_color_system |= LX_COLOR_SYSTEM_NTSC_443;
	if(v4l2_colorSystem & V4L2_STD_PAL_60)
		support_color_system |= LX_COLOR_SYSTEM_PAL_60;

	if( (support_color_system == 0) || (v4l2_colorSystem > V4L2_STD_ALL))
		return -EINVAL;

  //  AFE_PRINT("%s : SET to COLOR SYSTEM = [%d]\n",__func__, support_color_system);

	afe_kwrap_set_analog_color_system(LX_CVD_MAIN, support_color_system);

	return 0;
}

struct v4l2_ioctl_ops v4l2_avd_ioctl_ops = {
	.vidioc_querycap		= v4l2_avd_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_avd_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_avd_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_avd_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_avd_vidioc_g_ext_ctrls,
	.vidioc_s_input			= v4l2_avd_vidioc_s_input,
	.vidioc_g_input			= v4l2_avd_vidioc_g_input,
	.vidioc_g_std                = v4l2_avd_vidioc_g_std,
	.vidioc_s_std                = v4l2_avd_vidioc_s_std,
//	.vidioc_log_status = v4l2_ctrl_log_status,
//	.vidioc_subscribe_event = v4l2_avd_vidioc_subscribe_event,
//	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static int v4l2_avd_probe(struct platform_device *pdev)
{
	int ret = 0;
	AFE_PRINT("avd  %s\n", __func__);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	return ret;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_avd_remove(struct platform_device *pdev)
#else
static int v4l2_avd_remove(struct platform_device *pdev)
#endif
{
	AFE_PRINT("avd  %s\n", __func__);

	pm_runtime_disable(&pdev->dev);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static struct platform_driver v4l2_avd_driver = {
	.probe      = v4l2_avd_probe,
	.driver     = {
		.name   = "v4l2_avd",
		.owner  = THIS_MODULE,
		.pm     = &avd_pm_ops,
	},
	.remove		= v4l2_avd_remove,
};

struct v4l2_file_operations v4l2_avd_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_avd_fh_open,
	.release	= v4l2_avd_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read = vb2_fop_read,
//	.mmap = vb2_fop_mmap,
//	.poll = v4l2_avd_poll,
};

static struct video_device v4l2_avd_video_dev = {
	.v4l2_dev  = &v4l2_avd_dev,
	.fops      = &v4l2_avd_fops,
	.ioctl_ops = &v4l2_avd_ioctl_ops,
	.release   = video_device_release_empty,
	.lock      = &v4l2_avd_video_device_lock,
//	.vfl_dir   = VFL_DIR_RX,
	.tvnorms	= V4L2_STD_NTSC|V4L2_STD_NTSC_443|V4L2_STD_PAL|V4L2_STD_PAL_M|V4L2_STD_PAL_Nc|V4L2_STD_PAL_60|V4L2_STD_SECAM,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

static int v4l2_avd_register(void *arg)
{
	int ret;
	struct avd_dev *dev;

	AFE_PRINT("avd  %s\n", __func__);

    /* allocate main vivid state structure */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_avd_pdev.dev, &v4l2_avd_dev);
		if(ret < 0){
			AFE_PRINT(" avd : v4l2_device_register error[%d]\n", ret);
			break;
		}

		dev->pdev = &v4l2_avd_pdev;
		video_set_drvdata(&v4l2_avd_video_dev, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(&v4l2_avd_video_dev, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_AV);
#else
		ret = video_register_device(&v4l2_avd_video_dev, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_AV);
#endif
		if (ret < 0) {
			AFE_PRINT("video device register error: %d\n", ret);
			return -1;
		}

		platform_set_drvdata(&v4l2_avd_pdev, dev);
	} while(0);

	return ret;
}

int v4l2_avd_device_init(void)
{
	AFE_PRINT("avd  %s\n", __func__);
	platform_driver_register(&v4l2_avd_driver);
	platform_device_register(&v4l2_avd_pdev);

	mutex_init(&v4l2_avd_video_device_lock);
	//video_set_drvdata(&v4l2_vsc_video_dev, &vsc_pdev);
	v4l2_avd_register(NULL);

	return 0;
}

int avd_update_device_info(void)
{
	int ret = 0;

	__attribute__((unused)) BOOLEAN cvd_sync;
	UINT32	cvd_lock_status;
	AVD_DEV_INFO_T *avd_dev = NULL;
	LX_AFE_CVD_STATES_DETAIL_T cvd_states_detail_t;

    avd_dev = &avd_device_info;

	avd_dev->avd_input_src = _g_avd_input_src;
	avd_dev->hwport = _g_avd_port;

	avd_dev->auto_tuning_mode = _g_SyncDetectionForTunning;

	afe_kwrap_cvd_get_timing_info(LX_CVD_MAIN, &avd_dev->avd_timing_info);
	afe_kwrap_cvd_sync_exist(LX_CVD_MAIN, &avd_dev->avd_sync);
	afe_kwrap_cvd_get_lock_states(LX_CVD_MAIN, &cvd_lock_status);
	afe_kwrap_cvd_get_states_detail(&cvd_states_detail_t);

	avd_dev->noise_level = cvd_states_detail_t.status_noise;

	if(avd_dev->avd_sync)
		avd_dev->vd_lock = TRUE;
	else
		avd_dev->vd_lock = FALSE;

	if(cvd_lock_status & LX_HLOCK)
		avd_dev->h_lock = TRUE;
	else
		avd_dev->h_lock = FALSE;

	if(cvd_lock_status & LX_VLOCK)
		avd_dev->v_lock = TRUE;
	else
		avd_dev->v_lock = FALSE;

	if ( (cvd_lock_status & LX_VLOCK) != LX_VLOCK )
		avd_dev->color_standard = V4L2_STD_UNKNOWN;
	else
	{
		switch(avd_dev->avd_timing_info.cvd_standard)
		{
			case LX_NTSC_M :	// NTSC_M
				avd_dev->color_standard = V4L2_STD_NTSC;
				break;

			case LX_NTSC_443 :	//
				avd_dev->color_standard = V4L2_STD_NTSC_443;
				break;

			case LX_PAL_BG :
				avd_dev->color_standard = V4L2_STD_PAL;
				break;

			case LX_PAL_M :
				avd_dev->color_standard = V4L2_STD_PAL_M;
				break;

			case LX_PAL_CN :	//PAL-Cn
				avd_dev->color_standard = V4L2_STD_PAL_Nc;
				break;

			case LX_PAL_60 :	//PAL-60
				avd_dev->color_standard = V4L2_STD_PAL_60;
				break;

			case LX_SECAM :
				avd_dev->color_standard = V4L2_STD_SECAM;
				break;

			case LX_NON_STANDARD :
			default :
				if(avd_dev->avd_timing_info.u16_VFreq < 550)
					avd_dev->color_standard = V4L2_STD_625_50;
				else
					avd_dev->color_standard = V4L2_STD_525_60;
				break;
		}
	}

	return ret;
}

int v4l2_avd_pm_runtime_help(char* buffer)
{
	int len = 0;
	__attribute__((unused)) struct avd_dev *drv = platform_get_drvdata(&v4l2_avd_pdev);

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "dev name : %s\n",v4l2_avd_pdev.name);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- open_count : %d\n",_g_v4l2_avd_open_count);
	len += sprintf( buffer+len, "- vdev node name : %s\n",video_device_node_name(&v4l2_avd_video_dev));
	len += sprintf( buffer+len, "- usage_count : %d\n",atomic_read(&v4l2_avd_pdev.dev.power.usage_count));
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo runtime_suspend > /proc/lg/be/pm_test\n");
	len += sprintf( buffer+len, "echo runtime_resume > /proc/lg/be/pm_test\n");
	len += sprintf( buffer+len, "- others\n");
	len += sprintf( buffer+len, "cat /sys/devices/platform/v4l2_avd/power/runtime_status\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int v4l2_avd_pm_runtime_test(char* command)
{
	int ret = 0;
	__attribute__((unused)) struct avd_dev *drv = platform_get_drvdata(&v4l2_avd_pdev);

	if (!strncasecmp(command, "pm_runtime_put", strlen("pm_runtime_put"))) {
		ret = pm_runtime_put(&v4l2_avd_pdev.dev);
		AFE_PRINT("pm_runtime_put : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get_sync", strlen("pm_runtime_get_sync"))) {
		ret = pm_runtime_get_sync(&v4l2_avd_pdev.dev);
		AFE_PRINT("pm_runtime_get_sync : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get", strlen("pm_runtime_get"))) {
		ret = pm_runtime_get(&v4l2_avd_pdev.dev);
		AFE_PRINT("pm_runtime_get : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_suspend", strlen("pm_runtime_suspend"))) {
		ret = pm_runtime_suspend(&v4l2_avd_pdev.dev);
		AFE_PRINT("pm_runtime_suspend : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_resume", strlen("pm_runtime_resume"))) {
		ret = pm_runtime_resume(&v4l2_avd_pdev.dev);
		AFE_PRINT("pm_runtime_resume : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "runtime_suspend", strlen("runtime_suspend"))) {
		while (atomic_read(&v4l2_avd_pdev.dev.power.usage_count) > 0) {
			AFE_PRINT("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_avd_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_avd_pdev.dev);
			//msleep(1);
		}
	}
	else if (!strncasecmp(command, "runtime_resume", strlen("runtime_resume"))) {
		while (atomic_read(&v4l2_avd_pdev.dev.power.usage_count) <= 0) {
			AFE_PRINT("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_avd_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_avd_pdev.dev);
			//msleep(1);
		}
	}
	else {
		printk("do nothing\n");
	}

	return ret;
}

