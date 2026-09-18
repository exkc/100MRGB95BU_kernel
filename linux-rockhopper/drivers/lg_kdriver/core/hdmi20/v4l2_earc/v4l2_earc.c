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
 *  @author		taejun.lee(taejun.lee@lge.com)
 *  @version	1.0 
 *  @date		2019-05-07
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

#include "../hdmi21_engine/hdmi21_hal_driver.h"
#include "../hdmi21_engine/hdmi21_rx_disland.h"
#include "../hdmi21_engine/hdmi21_rx_phy.h"
#include "../hdmi21_engine/hdmi21_rx_audio.h"
#include "../hdmi21_engine/hdmi21_earc_driver.h"

#include "os_util.h"
#include "linux/v4l2-ext/v4l2-ext-earc.h"
#include "v4l2_earc.h"

//#include "../hdmi21_earc_kwarp.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_HDMI21_EARC_VIDEO_MINOR_NUMBER  13

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
//extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_RX_PORTS];
//extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
//extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T gHDMI21DevEARCControler[HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/


/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static struct v4l2_device v4l2_earc_dev;
struct mutex v4l2_earc_video_device_lock;

struct earc_fh {
	struct v4l2_fh fh;
	unsigned int numOfPort;	// Number of Max ports
// need to add some private data
};

//static enum v4l2_ext_earc_output_port _g_earc_output_port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
//static enum v4l2_ext_earc_enable _g_earc_enable = V4L2_EXT_EARC_DISABLE;

static struct platform_device v4l2_earc_pdev = {
	.name = "v4l2_earc",
	.id = -1,
};

static int v4l2_earc_resume(struct device *dev)
{
	printk("%s\n", __func__);
	return 0;
}

static int v4l2_earc_suspend(struct device *dev)
{
	printk("%s\n", __func__);
	return 0;
}

static struct dev_pm_ops const earc_pm_ops = {
    .resume = v4l2_earc_resume,
    .suspend = v4l2_earc_suspend,
};

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_EARC:
			return "V4L2_CID_EXT_EARC";
		case V4L2_CID_EXT_EARC_CONNECTION_INFO:
			return "V4L2_CID_EXT_EARC_CONNECTION_INFO";
		case V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ:
			return "V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ";
		default:
			return "Unknwon CTRL ID";
	}
}

static int v4l2_earc_fh_open(struct file *flie)
{
	int ret;
	struct earc_fh *fh;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc:19061400, open...\n");

		fh = kzalloc(sizeof(struct earc_fh), GFP_KERNEL);
		if (!fh)
		{
			printk("earc:xxxxxxxx, allocation of file handle failed \n");
			ret = -ENOMEM;
			return ret;
		}

		v4l2_fh_init(&fh->fh, video_devdata(flie));

		/* open earc */
		ret = 0;

		flie->private_data = fh;
		v4l2_fh_add(&fh->fh);

		fh->numOfPort = HDMI21_NUM_OF_RX_PORTS;	

		/* earc initialize */
		return ret;
/*
fail_fh:
		kfree(fh);
		return ret;
*/
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_fh_release(struct file *flie)
{
	int ret = RET_OK;
	//struct earc_fh *fh = flie->private_data;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

		printk("earc, close\n");

		ret = 0;

		v4l2_fh_release(flie);

		return ret;
	}else{
		return RET_ERROR;
	}	
}

static int v4l2_earc_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		switch (ctrl->id) 
		{
			case V4L2_CID_EXT_EARC:
			case V4L2_CID_EXT_EARC_CONNECTION_INFO:
			case V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ:
				ret = -EPERM;	
				break;
			default:
				ret = -EINVAL;
				break;
		}
		return ret;
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){	
		return ret;
	}else{
		return RET_ERROR;
	}	
}

static int v4l2_earc_process_ctrl(struct v4l2_ext_control *ctrl, int isGet, void *__fh)
{
	int ret = RET_OK;
	struct earc_fh *fh = __fh;

	if(ctrl->ptr == NULL){
		return -EINVAL;
	}
	switch (ctrl->id) {
		/* Enable eARC/ARC */
		case V4L2_CID_EXT_EARC:	
			{
				struct v4l2_ext_earc	userdata;
				
				if(ctrl->size != sizeof(struct v4l2_ext_earc)){
					ret = RET_INVALID_PARAMS;	
					break;
				}

				//memset(&data, 0, sizeof(LX_HDMI_EARC_CTRL_T));

				if(copy_from_user(&userdata, (void __user *)ctrl->ptr, sizeof(struct v4l2_ext_earc))){
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port) >= fh->numOfPort){
					ret = RET_INVALID_PARAMS;
					break;
				}
				
				if(isGet){		
					if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value == 1)
					{
						userdata.earc_enable_state = V4L2_EXT_EARC_ENABLE;
					}
					else
					{
						userdata.earc_enable_state = V4L2_EXT_EARC_DISABLE;
					}
				}
				else{			
					if(userdata.earc_enable_state == V4L2_EXT_EARC_ENABLE){
						ret = HDMI21_Tx_eARC_SetEARCMode(V4L2_EXT_EARC_ENABLE); // function call
					}
					else if(userdata.earc_enable_state == V4L2_EXT_EARC_DISABLE){
						ret = HDMI21_Tx_eARC_SetEARCMode(V4L2_EXT_EARC_DISABLE); // function call
					}
					else {
						ret = RET_INVALID_PARAMS;
					}			
				}

				if(copy_to_user((void __user *)ctrl->ptr, (void *)&userdata, sizeof(struct v4l2_ext_earc))){
					ret = RET_TRY_AGAIN;
				}
				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : eARC Enable Control Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}
				break;
			}
		/* Get Info */
		case V4L2_CID_EXT_EARC_CONNECTION_INFO:
			{
				struct v4l2_ext_earc_connection_info	userdata;
				LX_HDMI_EARC_CONNECTION_INFO_T eARCConnectionInfo;
				
				if(ctrl->size != sizeof(struct v4l2_ext_earc_connection_info)){
					ret = RET_INVALID_PARAMS;
					break;
				}
				//////pass


				memset(&eARCConnectionInfo, 0, sizeof(LX_HDMI_EARC_CONNECTION_INFO_T));

				if(copy_from_user(&userdata, ctrl->ptr, sizeof(struct v4l2_ext_earc_connection_info))){
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port) >= fh->numOfPort){
					ret = RET_INVALID_PARAMS;
					break;
				}


				if(isGet){
					// Get Info					
					ret = HDMI21_Tx_eARC_GetInfo(&eARCConnectionInfo, sizeof(LX_HDMI_EARC_CONNECTION_INFO_T), 0);
					userdata.port= (int)eARCConnectionInfo.portNum;
					userdata.status= (int)eARCConnectionInfo.earcStatus;
					userdata.erx_latency= eARCConnectionInfo.latency;
					userdata.erx_latency_req= eARCConnectionInfo.latency_req;
					memcpy((UINT8 *)&userdata.capability,(UINT8 *)&eARCConnectionInfo.capability, HDMI21_EARC_SIZE_OF_CAPS);
				}
				else{
					ret = RET_INVALID_PARAMS;
				}

				if(copy_to_user(ctrl->ptr, &userdata, sizeof(struct v4l2_ext_earc_connection_info))){
					ret = RET_TRY_AGAIN;
				}
				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : eARC Get Connection Info Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port);
					break;
				}
				break;				
			}
		/* Set Latency */
		case V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ:
			{
				struct v4l2_ext_earc_connection_info	userdata;
				unsigned char latency;
				
				if(ctrl->size != sizeof(struct v4l2_ext_earc_connection_info)){
					ret = RET_INVALID_PARAMS;	
					break;
				}

				memset(&userdata, 0, sizeof(struct v4l2_ext_earc_connection_info));

				if(copy_from_user(&userdata, ctrl->ptr, sizeof(struct v4l2_ext_earc_connection_info))){
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port) >= fh->numOfPort){
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(isGet){// Get
					ret = RET_INVALID_PARAMS;
					break;
				}
				else{// Set
					latency = userdata.erx_latency_req;
					ret = HDMI21_Tx_eARC_SetVideoLatency(latency); // function call
				}

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : eARC Get Connection Info Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port);
					break;
				}
				break;
			}

		/* HPD Bit Reset */
#ifdef 	V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT		
		case V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT:	
			{
				struct v4l2_ext_earc_connection_info	userdata;
				
				if(ctrl->size != sizeof(struct v4l2_ext_earc_connection_info)){
					ret = RET_INVALID_PARAMS;	
					break;
				}

				memset(&userdata, 0, sizeof(struct v4l2_ext_earc_connection_info));

				if(copy_from_user(&userdata, ctrl->ptr, sizeof(struct v4l2_ext_earc_connection_info))){
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port) >= fh->numOfPort){
					ret = RET_INVALID_PARAMS;
					break;
				}
				
				if(isGet){		
					ret = RET_INVALID_PARAMS;
					break;
				}
				else{			
					ret = HDMI21_Tx_eARC_SetHpdBitOn();
				}

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : eARC Set HPD Bit Reset Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port);
					break;
				}
				break;
			}
#endif			
		default:
			ret = RET_INVALID_IOCTL;
	}		
	return ret;
}

static int v4l2_earc_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct earc_fh *fh = __fh;
	int i, ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
		if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
			for (i = 0; i < ctrls->count; i++) {
				struct v4l2_ext_control *ctrl = ctrls->controls + i;

				ret = v4l2_earc_process_ctrl(ctrl, 0, fh);
				if (ret) {
					ctrls->error_idx = i;
					break;
				}
			}
			return ret;
		}
		return -1;
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct earc_fh *fh = __fh;
	int i, ret = 0;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
		if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {	
#endif
			for (i = 0; i < ctrls->count; i++) {
				struct v4l2_ext_control *ctrl = ctrls->controls + i;

				ret = v4l2_earc_process_ctrl(ctrl, 1, fh);
				if (ret) {
					ctrls->error_idx = i;
					break;
				}
			}
			return ret;
		}
		return -1;
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	//struct earc_fh *fh = __fh;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		strncpy(cap->card, "v4l2_earc", sizeof(cap->card)-1);
		strncpy(cap->driver, "v4l2_earc", sizeof(cap->driver)-1);
		cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
		cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
		cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

		return 0;
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	//struct earc_fh *fh = __fh;
	int ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		return ret;
	}else{
		return RET_ERROR;
	}	
}
static int v4l2_earc_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	//struct earc_fh *fh = __fh;
	int ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		return ret;
	}else{
		return RET_ERROR;
	}
}

static int v4l2_earc_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc type 0x%x, id 0x%x\n", sub->type, sub->id);

		switch (sub->type)
		{
			default:
			return -EINVAL;
		}
	}else{
		return RET_ERROR;
	}
}

static unsigned int v4l2_earc_poll(struct file *file, poll_table *wait)
{
	struct earc_fh *fh = (struct earc_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc:req_events 0x%lx\n", req_events);

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

		printk("earc: rc 0x%x\n", rc);

		return rc;
	}else{
		return RET_ERROR;
	}
}

struct v4l2_file_operations v4l2_earc_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_earc_fh_open,
	.release	= v4l2_earc_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read = vb2_fop_read,
//	.mmap = vb2_fop_mmap,
	.poll = v4l2_earc_poll,
};

struct v4l2_ioctl_ops v4l2_earc_ioctl_ops = {
	.vidioc_querycap		= v4l2_earc_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_earc_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_earc_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_earc_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_earc_vidioc_g_ext_ctrls,
	.vidioc_s_input			= v4l2_earc_vidioc_s_input,
	.vidioc_g_input			= v4l2_earc_vidioc_g_input,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_earc_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static int v4l2_earc_probe(struct platform_device *pdev)
{
	int ret = RET_OK;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc  %s\n", __func__);

		return ret;
	}else{
		return RET_ERROR;
	}
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_earc_remove(struct platform_device *pdev)
#else
static int v4l2_earc_remove(struct platform_device *pdev)
#endif
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc  %s\n", __func__);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
		return RET_OK;
	}else{
		return RET_ERROR;
#endif
	}
}

static struct platform_driver v4l2_earc_driver = {
	.probe      = v4l2_earc_probe,
	.driver     = {
		.name   = "v4l2_earc",
		.owner  = THIS_MODULE,
		.pm     = &earc_pm_ops,
	},
	.remove		= v4l2_earc_remove,
};

static struct video_device v4l2_earc_video_dev = {
	.v4l2_dev  = &v4l2_earc_dev,
	.fops      = &v4l2_earc_fops,
	.ioctl_ops = &v4l2_earc_ioctl_ops,
	.release   = video_device_release_empty,
	.lock      = &v4l2_earc_video_device_lock,
	.vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

static int v4l2_earc_register(void *arg)
{
	int ret;
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc  %s\n", __func__);

		do{
			/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
			ret = v4l2_device_register(&v4l2_earc_pdev.dev, &v4l2_earc_dev);
			if(ret < 0){
				printk(" earc : v4l2_device_register error[%d]\n", ret);
				break;
			}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
			ret = video_register_device(&v4l2_earc_video_dev, VFL_TYPE_VIDEO , V4L2_HDMI21_EARC_VIDEO_MINOR_NUMBER);
#else
			ret = video_register_device(&v4l2_earc_video_dev, VFL_TYPE_GRABBER , V4L2_HDMI21_EARC_VIDEO_MINOR_NUMBER);
#endif
			if (ret < 0) {
				printk("video device register error: %d\n", ret);
				return -1;
			}

		} while(0);
	
		return ret;
	}else{
		return RET_ERROR;
	}
}

int v4l2_earc_device_init(void)
{
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		printk("earc  %s\n", __func__);
		platform_driver_register(&v4l2_earc_driver);
		platform_device_register(&v4l2_earc_pdev);

		mutex_init(&v4l2_earc_video_device_lock);
		//video_set_drvdata(&v4l2_vsc_video_dev, &vsc_pdev);
		v4l2_earc_register(NULL);

		return 0;
	}else{
		return RET_ERROR;
	}
}

