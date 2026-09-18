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
#include "../include/afe_kapi.h"
#include "../afe_kwrap.h"
#include "../afe_drv.h"

#include "linux/v4l2-ext/v4l2-ext-component.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

extern LX_AFE_ADC_GAIN_VALUE_T user_gain_value;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device v4l2_adc_dev;
struct mutex v4l2_adc_video_device_lock;

struct adc_fh {
	struct v4l2_fh fh;
// need to add some private data
//	struct adc_priv *adc_priv;
};

static enum v4l2_ext_adc_input_src _g_adc_input_src = V4L2_EXT_ADC_INPUT_SRC_NONE;
static enum v4l2_ext_adc_calibration_type _g_adc_cal_type = V4L2_EXT_ADC_CALIBRATION_TYPE_USER;
int _g_adc_fast_switching = 0;

static struct platform_device v4l2_adc_pdev = {
	.name = "v4l2_adc",
	.id = -1,
};

ADC_DEV_INFO_T adc_device_info;

static int v4l2_adc_resume(struct device *dev)
{
	AFE_PRINT("%s\n", __func__);
	/*
	int ret;
	LX_AFE_ADC_INPUT_SOURCE_TYPE_T	adc_src_type;
	LX_AFE_ADC_INPUT_PORT_T			adc_input_port;

	AFE_PRINT("%s\n", __func__);

	if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_NONE)
	{
		return 0;
	}
	else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_COMP)
	{
		_g_adc_input_src = V4L2_EXT_ADC_INPUT_SRC_COMP;
		adc_src_type = LX_ADC_INPUT_SOURCE_YPBPR;
	}
#ifdef V4L2_EXT_ADC_INPUT_SRC_RGB
	else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_RGB)
	{
		_g_adc_input_src = V4L2_EXT_ADC_INPUT_SRC_RGB;
		adc_src_type = LX_ADC_INPUT_SOURCE_RGB_PC;
	}
#endif
	else
		return -EPERM;

	adc_input_port = LX_ADC_YPbPr_IN1;

	AFE_PRINT("adc : input port [%d], source_attribute [%d]\n", adc_input_port, adc_src_type);

	ret = afe_kwrap_adc_connectmodule(adc_src_type, adc_input_port);

	return ret;
	*/
	return 0;
}

static int v4l2_adc_suspend(struct device *dev)
{
	LX_AFE_ADC_INPUT_PORT_T			adc_input_port;

	adc_input_port = LX_ADC_YPbPr_IN1;

	AFE_PRINT("%s : input src [%d]\n", __func__, _g_adc_input_src);
	return 0;
}

static struct dev_pm_ops const adc_pm_ops = {
        .resume = v4l2_adc_resume,
        .suspend = v4l2_adc_suspend,
};

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_ADC_TIMING_INFO:
			return "V4L2_CID_EXT_ADC_TIMING_INFO";
		case V4L2_CID_EXT_ADC_CALIBRATION_DATA:
			return "V4L2_CID_EXT_ADC_CALIBRATION_DATA";
		case V4L2_CID_EXT_ADC_OTP_DATA:
			return "V4L2_CID_EXT_ADC_OTP_DATA";
		case V4L2_CID_EXT_ADC_CALIBRATION_TYPE:
			return "V4L2_CID_EXT_ADC_CALIBRATION_TYPE";
		case V4L2_CID_EXT_ADC_RESET_CALIBRATION:
			return "V4L2_CID_EXT_ADC_RESET_CALIBRATION";
		case V4L2_CID_EXT_ADC_FAST_SWITCH:
			return "V4L2_CID_EXT_ADC_FAST_SWITCH";
		default:
			return "Unkown";
	}
}

static int v4l2_adc_fh_open(struct file *flie)
{
	int ret, call_ret;
//	struct adc_priv *p;
	struct adc_fh *fh;
	ADC_DEV_INFO_T *adc_dev = NULL;

	adc_dev = &adc_device_info;
	adc_dev->adc_open++;

	AFE_PRINT("adc:22041200, open...\n");

	fh = kzalloc(sizeof(struct adc_fh), GFP_KERNEL);
	if (!fh)
	{
		AFE_PRINT("adc:xxxxxxxx, allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	/* open adc */
	ret = 0;

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* adc initialize */
	ret = afe_kwrap_adc_initializemodule();
	ret |= afe_kwrap_adc_enablemodule();

	return ret;

/*
fail_fh:
	kfree(fh);
	return ret;
*/

}

static int v4l2_adc_fh_release(struct file *flie)
{
	int ret, call_ret;
	struct adc_fh *fh = flie->private_data;

	ADC_DEV_INFO_T *adc_dev = NULL;

	adc_dev = &adc_device_info;

	AFE_PRINT("adc, close\n");

	adc_dev->adc_open = 0;

	ret = 0;

	v4l2_fh_release(flie);

	ret = afe_kwrap_adc_disablemodule();
	ret |= afe_kwrap_adc_uninitializemodule();

	return ret;
}

static int v4l2_adc_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret, i;
	struct adc_fh *fh = __fh;

	AFE_PRINT("adc:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {

		case V4L2_CID_EXT_ADC_CALIBRATION_TYPE:
			{
				BOOLEAN cal_src_type;	// TRUE : RGB, FALSE : Component
				LX_AFE_ADC_GAIN_VALUE_T   gain;

				_g_adc_cal_type = ctrl->value;

				AFE_PRINT("[%s,%d] input_src [%d], cal type [%d]\n",__F__,__L__,_g_adc_input_src, _g_adc_cal_type);

				afe_kwrap_set_adc_calibration_mode(TRUE);

				if(_g_adc_cal_type == V4L2_EXT_ADC_CALIBRATION_TYPE_INTERNAL)
				{
					if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_COMP)
					{
						cal_src_type = FALSE;
						ret = afe_kwrap_adc_set_llpll(274);	// Set LLPLL to 1920x1080 60P
						ret |= afe_kwrap_adc_calibration(TRUE, cal_src_type, 0, 0, 0, 1);
					}
#ifdef V4L2_EXT_ADC_INPUT_SRC_RGB
					else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_RGB)
					{
						/* RGB ADC Calibration */
						cal_src_type = TRUE;
						ret = afe_kwrap_adc_set_llpll(277);	// Set LLPLL to 1080P (138.5M)
						ret |= afe_kwrap_adc_calibration(TRUE, cal_src_type, 0, 0, 0, 0);
					}
#endif
					else
						ret = -EINVAL;

				}
				else
					ret = -EINVAL;

				afe_kwrap_set_adc_calibration_mode(FALSE);

				ret |= afe_kwrap_get_adc_gain(&gain);

				AFE_PRINT("[%s,%d] result [%d], red[0x%x], green [0x%x], blue [0x%x]\n",__F__,__L__,\
						ret, gain.R_Gain_Value, gain.G_Gain_Value, gain.B_Gain_Value);

				break;
			}
		case V4L2_CID_EXT_ADC_RESET_CALIBRATION:
			{

				if(ctrl->value == 1)
					ret = afe_kwrap_reset_adc_gainoffset();
				else if(ctrl->value == 0)
					ret = 0;
				else
					ret = -EINVAL;
				break;
			}
		case V4L2_CID_EXT_ADC_FAST_SWITCH:
			{
				_g_adc_fast_switching = ctrl->value;

				if(ctrl->value == 1)
					ret = afe_kwrap_adc_enable_periodic_signal_info_read(3);
				else if(ctrl->value == 0)
					ret = afe_kwrap_adc_enable_periodic_signal_info_read(2);
				else
					ret = -EINVAL;
				break;
			}

		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_adc_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	struct adc_fh *fh = __fh;

	AFE_PRINT("adc:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_ADC_CALIBRATION_TYPE:
			{
				ctrl->value = _g_adc_cal_type;
				break;
			}
		case V4L2_CID_EXT_ADC_FAST_SWITCH:
			{
				ctrl->value = _g_adc_fast_switching;
				break;
			}

		default:
			ret = -EINVAL;
	}

	return 0;
}

static int adc_try_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_EXT_ADC_TIMING_INFO:
		if ( (ctrl->ptr != NULL) && (ctrl->size == sizeof(struct v4l2_ext_adc_timing_info)) )
			ret = 0;
		break;
	case V4L2_CID_EXT_ADC_CALIBRATION_DATA:
		if ( (ctrl->ptr != NULL) && (ctrl->size == sizeof(struct v4l2_ext_adc_calibration_data)) )
			ret = 0;
		break;
	case V4L2_CID_EXT_ADC_OTP_DATA:
		if ( (ctrl->ptr != NULL) && (ctrl->size == sizeof(struct v4l2_ext_adc_calibration_data)) )
			ret = 0;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static int adc_set_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_ADC_CALIBRATION_DATA:
		{
			LX_AFE_ADC_GAIN_VALUE_T   gain  ={0,0,0};
			LX_AFE_ADC_OFFSET_VALUE_T offset={0,0,0};

			struct v4l2_ext_adc_calibration_data cal_data;

			ret = copy_from_user(&cal_data, ctrl->ptr, sizeof(struct v4l2_ext_adc_calibration_data));

			gain.R_Gain_Value = cal_data.r_gain;
			gain.G_Gain_Value = cal_data.g_gain;
			gain.B_Gain_Value = cal_data.b_gain;
			offset.R_Offset_Value = cal_data.r_offset;
			offset.G_Offset_Value = cal_data.g_offset;
			offset.B_Offset_Value = cal_data.b_offset;

			//Set MSB bit to nofity this KADP_AFE_Set_ADC_Gain call is from HAL function
			gain.G_Gain_Value |= 0x8000;

			ret |= afe_kwrap_set_adc_gain(gain.R_Gain_Value, gain.G_Gain_Value, gain.B_Gain_Value);
			ret |= afe_kwrap_set_adc_offset(offset.R_Offset_Value, offset.G_Offset_Value, offset.B_Offset_Value);

		}
		break;
	default:
		return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_adc_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct adc_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = adc_try_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
			ret = adc_set_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int adc_get_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_ADC_TIMING_INFO:
		{
			LX_AFE_ADC_TIMING_INFO_T kwrap_timing_info = {0,};
			struct v4l2_ext_adc_timing_info adc_timing_info;

			ret = afe_kwrap_adc_get_timing_info(&kwrap_timing_info);

			adc_timing_info.h_freq = kwrap_timing_info.u16_HFreq ;
			adc_timing_info.v_freq = kwrap_timing_info.u16_VFreq;
			adc_timing_info.h_total = kwrap_timing_info.u16_HTotal;
			adc_timing_info.v_total = kwrap_timing_info.u16_VTotal;
			adc_timing_info.h_porch = kwrap_timing_info.u16_HStart;
			adc_timing_info.v_porch = kwrap_timing_info.u16_VStart;
			adc_timing_info.scan_type = kwrap_timing_info.u8_ScanType;
			adc_timing_info.phase = kwrap_timing_info.u16_Phase;

			adc_timing_info.active.x = 0;
			adc_timing_info.active.y = 0;
			adc_timing_info.active.w = kwrap_timing_info.u16_HActive;
			adc_timing_info.active.h = kwrap_timing_info.u16_VActive;

			ret |= copy_to_user(ctrl->ptr, &adc_timing_info, sizeof(struct v4l2_ext_adc_timing_info));
		}
		break;
	case V4L2_CID_EXT_ADC_CALIBRATION_DATA:
		{
			LX_AFE_ADC_GAIN_VALUE_T   gain  ={0,0,0};
			LX_AFE_ADC_OFFSET_VALUE_T offset={0,0,0};
			struct v4l2_ext_adc_calibration_data cal_data;

			if( (user_gain_value.R_Gain_Value != 0) && (user_gain_value.G_Gain_Value != 0) && (user_gain_value.B_Gain_Value != 0) )
				memcpy(&gain, &user_gain_value, sizeof(LX_AFE_ADC_GAIN_VALUE_T));
			else
				ret  = afe_kwrap_get_adc_gain(&gain);
			ret |= afe_kwrap_get_adc_offset(&offset);

			cal_data.r_gain    = gain.R_Gain_Value;
			cal_data.g_gain    = gain.G_Gain_Value;
			cal_data.b_gain    = gain.B_Gain_Value;
			cal_data.r_offset  = offset.R_Offset_Value;
			cal_data.g_offset  = offset.G_Offset_Value;
			cal_data.b_offset  = offset.B_Offset_Value;

			ret |= copy_to_user(ctrl->ptr, &cal_data, sizeof(struct v4l2_ext_adc_calibration_data));
		}
		break;

	case V4L2_CID_EXT_ADC_OTP_DATA:
		{
			LX_AFE_ADC_GAIN_VALUE_T   gain  ={0,0,0};
			LX_AFE_ADC_OFFSET_VALUE_T offset={0,0,0};
			LX_AFE_ADC_GAIN_VALUE_T   gain_rgb  ={0,0,0};
			LX_AFE_ADC_OFFSET_VALUE_T offset_rgb={0,0,0};
			struct v4l2_ext_adc_calibration_data cal_data;

#ifdef ADC_OTP_CMDLINE
			ret = AFE_Get_ADC_OTP_from_Cmdline(&gain, &offset, &gain_rgb, &offset_rgb);

			if(ret != RET_OK)
			{
				AFE_ERROR("no adc otp data in cmdline %d\n", ret );
#endif
				// AFE_Wakeup() called in AFE_Get_ADC_OTP_Cal_Data()
				// AFE_Wakeup(LX_AFE_EVENT_OTP_CAL_READ_FROM_SE);

				ret = AFE_Get_ADC_OTP_Cal_Data(&gain, &offset, &gain_rgb, &offset_rgb);

				AFE_PRINT("adc get otp data from KADP SE %d\n", ret );
#ifdef ADC_OTP_CMDLINE
			}
#endif
			/*
			ret  = afe_kwrap_get_adc_gain(&gain);
			ret |= afe_kwrap_get_adc_offset(&offset);
			*/
			if(ret == 0)
			{
				cal_data.r_gain    = gain.R_Gain_Value;
				cal_data.g_gain    = gain.G_Gain_Value;
				cal_data.b_gain    = gain.B_Gain_Value;
				cal_data.r_offset  = offset.R_Offset_Value;
				cal_data.g_offset  = offset.G_Offset_Value;
				cal_data.b_offset  = offset.B_Offset_Value;

				AFE_PRINT("OTP Comp gain_R/G/B 0x%x/0x%x/0x%x, offset_R/G/B 0x%x/0x%x/0x%x\n", \
						gain.R_Gain_Value, gain.G_Gain_Value, gain.B_Gain_Value, \
						offset.R_Offset_Value, offset.G_Offset_Value, offset.B_Offset_Value);
				AFE_PRINT("OTP RGB gain_R/G/B 0x%x/0x%x/0x%x, offset_R/G/B 0x%x/0x%x/0x%x\n", \
						gain_rgb.R_Gain_Value, gain_rgb.G_Gain_Value, gain_rgb.B_Gain_Value, \
						offset_rgb.R_Offset_Value, offset_rgb.G_Offset_Value, offset_rgb.B_Offset_Value);

				ret |= copy_to_user(ctrl->ptr, &cal_data, sizeof(struct v4l2_ext_adc_calibration_data));
			}
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static int v4l2_adc_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct adc_fh *fh = __fh;

	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = adc_try_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
			ret = adc_get_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;

}

static int v4l2_adc_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	struct adc_fh *fh = __fh;
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

	strncpy(cap->card, "adc", sizeof(cap->card)-1);
	strncpy(cap->driver, chip_name, sizeof(chip_name));
	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif
	cap->version = LINUX_VERSION_CODE;

	return 0;

}

static int v4l2_adc_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	struct adc_fh *fh = __fh;
	int ret;
	LX_AFE_ADC_INPUT_SOURCE_TYPE_T	adc_src_type;
	LX_AFE_ADC_INPUT_PORT_T			adc_input_port;

	AFE_PRINT("adc: input %d\n", i);

	/* save source type and port for resume */
	_g_adc_input_src = i;

	if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_NONE)
	{
		ret = afe_kwrap_adc_disconnectmodule();
		return ret;
	}
	else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_COMP)
	{
		_g_adc_input_src = V4L2_EXT_ADC_INPUT_SRC_COMP;
		adc_src_type = LX_ADC_INPUT_SOURCE_YPBPR;
	}
#ifdef V4L2_EXT_ADC_INPUT_SRC_RGB
	else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_RGB)
	{
		_g_adc_input_src = V4L2_EXT_ADC_INPUT_SRC_RGB;
		adc_src_type = LX_ADC_INPUT_SOURCE_RGB_PC;
	}
#endif
	/*
	else if(_g_adc_input_src == V4L2_EXT_ADC_INPUT_SRC_VGA)
	{
		_g_adc_input_src = ADC_SRC_TYPE_VGA;
		adc_src_type = LX_ADC_INPUT_SOURCE_RGB_PC;
	}
	*/
	else
		return -EPERM;

	/*
	if(src.srcPort >= ADC_PORT_MAX)
		return -EPERM;
		*/

	adc_input_port = LX_ADC_YPbPr_IN1;

	ret = afe_kwrap_adc_connectmodule(adc_src_type, adc_input_port);

	return ret;
}
static int v4l2_adc_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	struct adc_fh *fh = __fh;
	int ret;

	if(i == NULL)
		return -EPERM;
	else
		ret = 0;

	AFE_PRINT("adc: get input %d\n", *i);

	*i = _g_adc_input_src;

	return ret;
}

static int v4l2_adc_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	AFE_PRINT("adc type 0x%x, id 0x%x\n", sub->type, sub->id);

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

static unsigned int v4l2_adc_poll(struct file *file, poll_table *wait)
{
	struct adc_fh *fh = (struct adc_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	AFE_PRINT("adc:req_events 0x%lx\n", req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
		/*
		poll_wait(file, &p->adc_poll_wq, wait);

		if (p->adc_poll & POLLIN)
			rc |= POLLIN;
		if (p->adc_poll & POLLOUT)
			rc |= POLLOUT;
		if (p->adc_poll & POLLERR)
			rc |= POLLERR;
			*/
	}

	AFE_PRINT("adc: rc 0x%x\n", rc);

	return rc;
}

struct v4l2_file_operations v4l2_adc_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_adc_fh_open,
	.release	= v4l2_adc_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read = vb2_fop_read,
//	.mmap = vb2_fop_mmap,
	.poll = v4l2_adc_poll,
};

struct v4l2_ioctl_ops v4l2_adc_ioctl_ops = {
	.vidioc_querycap		= v4l2_adc_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_adc_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_adc_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_adc_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_adc_vidioc_g_ext_ctrls,
	.vidioc_s_input			= v4l2_adc_vidioc_s_input,
	.vidioc_g_input			= v4l2_adc_vidioc_g_input,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_adc_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static int v4l2_adc_probe(struct platform_device *pdev)
{
	int ret = 0;
	AFE_PRINT("adc  %s\n", __func__);

	return ret;
}

static int v4l2_adc_remove(struct platform_device *pdev)
{
	AFE_PRINT("adc  %s\n", __func__);

	return 0;
}

static struct platform_driver v4l2_adc_driver = {
	.probe      = v4l2_adc_probe,
	.driver     = {
		.name   = "v4l2_adc",
		.owner  = THIS_MODULE,
		.pm     = &adc_pm_ops,
	},
	.remove		= v4l2_adc_remove,
};

static struct video_device v4l2_adc_video_dev = {
	.v4l2_dev  = &v4l2_adc_dev,
	.fops      = &v4l2_adc_fops,
	.ioctl_ops = &v4l2_adc_ioctl_ops,
	.release   = video_device_release_empty,
	.lock      = &v4l2_adc_video_device_lock,
	.vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

static int v4l2_adc_register(void *arg)
{
	int ret;

	AFE_PRINT("adc  %s\n", __func__);

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_adc_pdev.dev, &v4l2_adc_dev);
		if(ret < 0){
			AFE_PRINT(" adc : v4l2_device_register error[%d]\n", ret);
			break;
		}

		ret = video_register_device(&v4l2_adc_video_dev, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_ADC);
		if (ret < 0) {
			AFE_PRINT("video device register error: %d\n", ret);
			return -1;
		}

	} while(0);

	return ret;
}

int v4l2_adc_device_init(void)
{
	ADC_DEV_INFO_T *adc_dev = NULL;

	AFE_PRINT("adc  %s\n", __func__);
	platform_driver_register(&v4l2_adc_driver);
	platform_device_register(&v4l2_adc_pdev);

	mutex_init(&v4l2_adc_video_device_lock);
	//video_set_drvdata(&v4l2_vsc_video_dev, &vsc_pdev);
	v4l2_adc_register(NULL);

    adc_dev = &adc_device_info;

	adc_dev->adc_open = 0;
	adc_dev->adc_input_src = V4L2_EXT_ADC_INPUT_SRC_NONE;
	adc_dev->adc_cal_type = V4L2_EXT_ADC_CALIBRATION_TYPE_USER;
	adc_dev->adc_fast_switch_mode = 0;
	memset(&adc_dev->adc_timing_info, 0x0, sizeof (LX_AFE_ADC_TIMING_INFO_T));
	memset(&adc_dev->gain, 0x0, sizeof (LX_AFE_ADC_GAIN_VALUE_T));
	memset(&adc_dev->offset, 0x0, sizeof (LX_AFE_ADC_OFFSET_VALUE_T));

	return 0;
}

int adc_update_device_info(void)
{
	int ret = 0;

	ADC_DEV_INFO_T *adc_dev = NULL;

	LX_AFE_ADC_GAIN_VALUE_T   gain  ={0,0,0};
	LX_AFE_ADC_OFFSET_VALUE_T offset={0,0,0};

    adc_dev = &adc_device_info;

	adc_dev->adc_input_src = _g_adc_input_src;
	adc_dev->adc_cal_type = _g_adc_cal_type;
	adc_dev->adc_fast_switch_mode = _g_adc_fast_switching;

	ret = afe_kwrap_adc_get_timing_info(&adc_dev->adc_timing_info);

	if( (user_gain_value.R_Gain_Value != 0) && (user_gain_value.G_Gain_Value != 0) && (user_gain_value.B_Gain_Value != 0) )
		memcpy(&adc_dev->gain, &user_gain_value, sizeof(LX_AFE_ADC_GAIN_VALUE_T));
	else
		ret  = afe_kwrap_get_adc_gain(&adc_dev->gain);
	ret |= afe_kwrap_get_adc_offset(&adc_dev->offset);

	return ret;
}

