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
 *  @author		won.hur
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

#include "linux/v4l2-ext/v4l2-ext-hdmi.h"
#include "../hdmi20_module.h"
#include "../hdmi20_kwarp.h"
#include "../hdmi20_drv.h"

#include "../hdmi21_engine/hdmi21_hal_driver.h"
#include "../hdmi21_engine/hdmi21_rx_snps_hdcp.h"
#include "../hdmi21_engine/hdmi21_rx_snps_scdc.h"
#include "../hdmi21_engine/hdmi21_rx_disland.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_HDMI20_VIDEO_MINOR_NUMBER  12

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_V4L2_REG_WR(address,data)   \
		_sMapped_address=(UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
		if(_sMapped_address == NULL) break;\
		*_sMapped_address = data;\
		iounmap((void *)_sMapped_address);\
}while(0);\

#define HDMI20_V4L2_REG_RD(address,data)   \
		_sMapped_address = (UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
		if(_sMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*_sMapped_address;\
		iounmap((void *)_sMapped_address);\
}while(0);\

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern bool 	g_hdmi20_open_done;

extern unsigned char gHDMI21RepeaterRxID[32][5];
extern int gHDMI21RepeaterCount;
extern int gHDMI21RepeaterDepth;

extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

/* 2022/03/29 : For ESM kmalloc issue */
extern dma_addr_t gEsm_Dma_codebase;
extern dma_addr_t gEsm_Dma_database;

extern UINT8 *pEsm_codeVirtAddr;
extern UINT8 *pEsm_dataVirtAddr;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device hdmi20_v4l2_dev;


struct mutex hdmi20_video_device_lock;
struct hdmi20_fh {
	struct v4l2_fh fh;
	unsigned int numOfPort;	// Number of Max ports
};

static int _g_v4l2_hdmi20_disconnect = 0;
static int _g_v4l2_hdmi20_power = 0;
static int _g_v4l2_hdmi20_port = 1;

static unsigned int *_sMapped_address; // For DBG: REG Read/Write macro

static unsigned int _g_v4l2_hdmi20_hdcp23_repeater_msgId = 0;
static unsigned char _g_v4l2_hdmi20_hdcp_repeater_mode = 0;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static char *ctrl_id_to_str(int id);
static int hdmi20_v4l2_probe(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void hdmi20_v4l2_remove(struct platform_device *pdev);
#else
static int hdmi20_v4l2_remove(struct platform_device *pdev);
#endif
static int hdmi20_v4l2_suspend(struct device *dev);
static int hdmi20_v4l2_resume(struct device *dev);
static void hdmi20_v4l2_release(struct video_device *vdev);


/* V4L2 */
static int v4l2_hdmi20_register(void *arg);

/* FOPS releated to V4L2 */
static struct v4l2_file_operations hdmi20_v4l2_fops;
static int v4l2_hdmi20_open(struct file *filp);
static int v4l2_hdmi20_release(struct file *flie);
static int v4l2_hdmi20_vidioc_querycap(struct file *file, void  *priv, struct v4l2_capability *cap);
static int v4l2_hdmi20_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_hdmi20_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_hdmi20_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int v4l2_hdmi20_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int v4l2_hdmi20_vidioc_s_input(struct file *file, void *__fh, unsigned int i);
static int v4l2_hdmi20_vidioc_g_input(struct file *file, void *__fh, unsigned int *i);
static int v4l2_hdmi20_vidioc_s_output(struct file *file, void *__fh, unsigned int i);
static int v4l2_hdmi20_vidioc_g_output(struct file *file, void *__fh, unsigned int *i);
static unsigned int v4l2_hdmi20_poll(struct file *file, poll_table *wait);

void v4l2_hdmi20_header_ver_print(struct seq_file *m);	
int v4l2_hdmi20_device_init(void);

/* Internal Static */
static int v4l2_hdmi20_process_ctrl(struct v4l2_ext_control *ctrl, int isGet, void *__fh);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
UINT32 gHDMI20EnableStatus[10] = {0,}; 	//temp code
UINT32 gHDMI20TMDSErrorStamp[HDMI21_NUM_OF_MAX_PORTS] = {0,}; 
UINT32 gHDMI20CEDErrorStamp[HDMI21_NUM_OF_MAX_PORTS] = {0,}; 
UINT32 gHDMI20RangeErrorStamp[HDMI21_NUM_OF_MAX_PORTS] = {0,}; 
/*========================================================================================
	Implementation Group
========================================================================================*/
void v4l2_hdmi20_header_ver_print(struct seq_file *m)
{
	if (!m){
		printk("invalid seq_file m..!\n");
	}

	/* 2022/08/17 won.hur : No longer linuxtv-ext-ver.h file is being kept. */
}

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/


static struct platform_device hdmi20_v4l2_pdev = {
	.name = "hdmi20_v4l2",
	.id = -1,
};

static struct dev_pm_ops const hdmi20_pm_ops = {
        .resume = hdmi20_v4l2_resume,
        .suspend = hdmi20_v4l2_suspend,
};

static struct platform_driver hdmi20_v4l2_driver = {
	.probe      = hdmi20_v4l2_probe,
	.driver     = {
		.name   = "hdmi20_v4l2",
		.owner  = THIS_MODULE,
		.pm     = &hdmi20_pm_ops,
	},
	.remove		= hdmi20_v4l2_remove,
};

static struct v4l2_file_operations hdmi20_v4l2_fops = {
	.owner          = THIS_MODULE,
	.open           = v4l2_hdmi20_open,
	.release        = v4l2_hdmi20_release,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_hdmi20_poll,
};

struct v4l2_ioctl_ops hdmi20_video_ioctl_ops = {
	.vidioc_querycap		= v4l2_hdmi20_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_hdmi20_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_hdmi20_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_hdmi20_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_hdmi20_vidioc_g_ext_ctrls,
	.vidioc_s_input			= v4l2_hdmi20_vidioc_s_input,
	.vidioc_g_input			= v4l2_hdmi20_vidioc_g_input,
	.vidioc_s_output		= v4l2_hdmi20_vidioc_s_output,
	.vidioc_g_output		= v4l2_hdmi20_vidioc_g_output,
	.vidioc_log_status		= v4l2_ctrl_log_status,
};

static struct video_device hdmi20_v4l2_video_dev = {
	.v4l2_dev  = &hdmi20_v4l2_dev,
	.fops      = &hdmi20_v4l2_fops,
	.ioctl_ops = &hdmi20_video_ioctl_ops,
	.release   = &hdmi20_v4l2_release,
	.lock      = &hdmi20_video_device_lock,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
	//.vfl_dir   = VFL_DIR_RX,
};

int v4l2_hdmi20_device_init(void)
//static int __init v4l2_hdmi20_device_init(void)
{
	int ret = 0;

	printk("HDMI20  %s\n", __func__);

	ret = platform_driver_register(&hdmi20_v4l2_driver);
	ret |= platform_device_register(&hdmi20_v4l2_pdev);

	mutex_init(&hdmi20_video_device_lock);

	//video_set_drvdata(&hdmi20_v4l2_video_dev, &hdmi20_pdev);
	v4l2_hdmi20_register(NULL);

	/* Need this for original HDMI20 Method layer for suspend/resume */
	g_hdmi20_open_done = true;

	return ret;
}

static void hdmi20_v4l2_release(struct video_device *vdev)
{
	printk("HDMI20  %s\n", __func__);
	return;
}

static void __exit __attribute__((unused)) v4l2_hdmi20_device_exit(void)
{
	printk("HDMI20  %s\n", __func__);

	platform_device_unregister(&hdmi20_v4l2_pdev);
	platform_driver_unregister(&hdmi20_v4l2_driver);
	return;
}

static int hdmi20_v4l2_probe(struct platform_device *pdev)
{
	int ret = RET_OK;

	printk("HDMI20  %s\n", __func__);

	ret = HDMI20_Module_Open();

	KWARP_HDMI20_Open();
	KWARP_HDMI20_RX_Initialize();

	ret |= HDMI20_Module_Initialize(NULL, 0, 1);

	return 0;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void hdmi20_v4l2_remove(struct platform_device *pdev)
#else
static int hdmi20_v4l2_remove(struct platform_device *pdev)
#endif
{
	printk("HDMI20  %s\n", __func__);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_hdmi20_register(void *arg)
{
	int ret;

	printk("HDMI20  %s\n", __func__);

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&hdmi20_v4l2_pdev.dev, &hdmi20_v4l2_dev);
		if(ret < 0){
			printk(" HDMI20 : v4l2_device_register error[%d]\n", ret);
			break;
		}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(&hdmi20_v4l2_video_dev, VFL_TYPE_VIDEO, V4L2_HDMI20_VIDEO_MINOR_NUMBER); /* For Mr.Do VBI device : VFL_TYPE_VBI */
#else
		ret = video_register_device(&hdmi20_v4l2_video_dev, VFL_TYPE_GRABBER, V4L2_HDMI20_VIDEO_MINOR_NUMBER); /* For Mr.Do VBI device : VFL_TYPE_VBI */
#endif
		if (ret < 0) {
			printk("video device register error: %d\n", ret);
			return -1;
		}


	} while(0);

	return ret;
}

static int hdmi20_v4l2_resume(struct device *dev)
{
	printk("%s\n", __func__);
        return 0;
}

static int hdmi20_v4l2_suspend(struct device *dev) 
{
	printk("%s\n", __func__);
        return 0;
}


static unsigned int v4l2_hdmi20_poll(struct file *file, poll_table *wait)
{
	struct hdmi20_fh *fh = file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	printk("[%s] :req_events 0x%lx\n", __func__, req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
	}

	//printk("[%s] : rc 0x%x\n", __func__, rc);

	return rc;
}

static int __attribute__((unused)) hdmi20_v4l2_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	enum v4l2_buf_type fh_type = 0;
	int ret;

	switch (vdev->vfl_type) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		case VFL_TYPE_VIDEO:
#else
		case VFL_TYPE_GRABBER:
#endif
			fh_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			break;
		case VFL_TYPE_VBI:
			fh_type = V4L2_BUF_TYPE_VBI_CAPTURE;
			break;
		case VFL_TYPE_RADIO:
			break;
		default:
			return -EINVAL;
	}

	ret = v4l2_fh_open(filp);
	if (ret) {
		return ret;
	}

	return 0;
}

static int v4l2_hdmi20_vidioc_querycap(struct file *file, void  *priv, struct v4l2_capability *cap)
{
	if (lx_chip_rev() >= LX_CHIP_REV( O26, A0))
	{	
		strncpy(cap->driver, "o26", sizeof(cap->driver)-1);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O24, A0))
	{	
		strncpy(cap->driver, "o24", sizeof(cap->driver)-1);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( M23, A0))
	{	
		strncpy(cap->driver, "m23", sizeof(cap->driver)-1);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
	{	
		strncpy(cap->driver, "o22", sizeof(cap->driver)-1);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{	
		strncpy(cap->driver, "e60", sizeof(cap->driver)-1);
	} 
	else if ( lx_chip_rev() >= LX_CHIP_REV(O20, A0))	
	{	
		strncpy(cap->driver, "o20", sizeof(cap->driver)-1); 
	} 
	else 
	{	
		strncpy(cap->driver, "unknown", sizeof(cap->driver)-1);	
	}
	
	strncpy(cap->card, "hdmi", sizeof(cap->card)-1);
	cap->bus_info[0] = 0;
	cap->version = LINUX_VERSION_CODE;
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}

static int v4l2_hdmi20_open(struct file *flie)
{
	int ret = RET_OK;
	struct hdmi20_fh *fh;

	printk("%s\n", __func__);

	do{
		fh = kzalloc(sizeof(struct hdmi20_fh), GFP_KERNEL);
		if (!fh)
		{
			printk("hdmi20 v4l2, allocation of file handle failed \n");
			ret = -ENOMEM;
			break;
		}

		v4l2_fh_init(&fh->fh, video_devdata(flie));

		flie->private_data = fh;
		v4l2_fh_add(&fh->fh);


		if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		{
			fh->numOfPort = HDMI21_NUM_OF_PORTS_E60;	
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
		{
			fh->numOfPort = HDMI21_NUM_OF_PORTS_O20;	
		}
		else 
		{
			fh->numOfPort =	HDMI20_NUM_OF_RX_PORTS;
		}



		printk("[%s] :  index = %d, minor = %d\n", __func__,  fh->fh.vdev->index, fh->fh.vdev->minor);
	} while(0);

	return ret;
}

static int v4l2_hdmi20_release(struct file *flie)
{
	int ret = RET_OK;
//	int i = 0;
	struct hdmi20_fh *fh = flie->private_data;

	printk("%s\n", __func__);
	printk("%s : *fh[0x%p], flie[0x%p]\n",  __func__, (void *)fh, (void *)flie);


	//if(fh != NULL) kfree(fh);

	v4l2_fh_release(flie);

	return ret;
}

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_HDMI_TIMING_INFO:
			return "V4L2_CID_EXT_HDMI_TIMING_INFO";
		case V4L2_CID_EXT_HDMI_DRM_INFO:
			return "V4L2_CID_EXT_HDMI_DRM_INFO";
		case V4L2_CID_EXT_HDMI_VSI_INFO:
			return "V4L2_CID_EXT_HDMI_VSI_INFO";
		case V4L2_CID_EXT_HDMI_SPD_INFO:
			return "V4L2_CID_EXT_HDMI_SPD_INFO";
		case V4L2_CID_EXT_HDMI_AVI_INFO:
			return "V4L2_CID_EXT_HDMI_AVI_INFO";
		case V4L2_CID_EXT_HDMI_PACKET_INFO:
			return "V4L2_CID_EXT_HDMI_PACKET_INFO";
		case V4L2_CID_EXT_HDMI_DOLBY_HDR:
			return "V4L2_CID_EXT_HDMI_DOLBY_HDR";
		case V4L2_CID_EXT_HDMI_EDID:
			return "V4L2_CID_EXT_HDMI_EDID";
		case V4L2_CID_EXT_HDMI_EDID_ACCESS:	
			return "V4L2_CID_EXT_HDMI_EDID_ACCESS";
		case V4L2_CID_EXT_HDMI_CONNECTION_STATE:
			return "V4L2_CID_EXT_HDMI_CONNECTION_STATE";
		case V4L2_CID_EXT_HDMI_HPD:
			return "V4L2_CID_EXT_HDMI_HPD";
		case V4L2_CID_EXT_HDMI_HDCP_KEY:
			return "V4L2_CID_EXT_HDMI_HDCP_KEY";
		case V4L2_CID_EXT_HDMI_POWER_OFF:
			return "V4L2_CID_EXT_HDMI_POWER_OFF"; 
		case V4L2_CID_EXT_HDMI_DISCONNECT:
			return "V4L2_CID_EXT_HDMI_DISCONNECT";
		case V4L2_CID_EXT_HDMI_VRR_FREQUENCY:
			return "V4L2_CID_EXT_HDMI_VRR_FREQUENCY";
		case V4L2_CID_EXT_HDMI_EMP_INFO:
			return "V4L2_CID_EXT_HDMI_EMP_INFO";
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER:
			return "V4L2_CID_EXT_HDMI_HDCP_REPEATER";
		case V4L2_CID_EXT_HDMI_OVERRIDE_EOTF:
			return "V4L2_CID_EXT_HDMI_OVERRIDE_EOTF";
		case V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS:
			return "V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS";
		case V4L2_CID_EXT_HDMI_PHY_STATUS:
			return "V4L2_CID_EXT_HDMI_PHY_STATUS";
		case V4L2_CID_EXT_HDMI_LINK_STATUS:
			return "V4L2_CID_EXT_HDMI_LINK_STATUS";
		case V4L2_CID_EXT_HDMI_VIDEO_STATUS :
			return "V4L2_CID_EXT_HDMI_VIDEO_STATUS";
		case V4L2_CID_EXT_HDMI_AUDIO_STATUS:
			return "V4L2_CID_EXT_HDMI_AUDIO_STATUS";
		case V4L2_CID_EXT_HDMI_HDCP_STATUS:
			return "V4L2_CID_EXT_HDMI_HDCP_STATUS";
		case V4L2_CID_EXT_HDMI_SCDC_STATUS:
			return "V4L2_CID_EXT_HDMI_SCDC_STATUS";
		case V4L2_CID_EXT_HDMI_ERROR_STATUS:
			return "V4L2_CID_EXT_HDMI_ERROR_STATUS";
		case V4L2_CID_EXT_HDMI_EXPERT_SETTING :
			return "V4L2_CID_EXT_HDMI_EXPERT_SETTING";
		case V4L2_CID_EXT_HDMI_QUERYCAP:
			return "V4L2_CID_EXT_HDMI_QUERYCAP";
		
		case  V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY:
			return "V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY";
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE:
			return "V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE";
		#if 0
		case V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON:
			return "V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON";
		#endif
		//case V4L2_CID_EXT_HDMI_DOLBY_CONTENT:
		//	return "V4L2_CID_EXT_HDMI_DOLBY_CONTENT";
		case V4L2_CID_EXT_HDMI_SLEEP:
			return "V4L2_CID_EXT_HDMI_SLEEP";
		case V4L2_CID_EXT_HDMI_DPMS:
			return "V4L2_CID_EXT_HDMI_DPMS";
		default:
			return "Unknwon CTRL ID";
	}
}

static int v4l2_hdmi20_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = RET_OK;
	int i;
	UINT32 data;
	struct hdmi20_fh *fh = __fh;

	//printk("hdmi20 v4l2 s ctrl:id 0x%x (%s), value %d\n", ctrl->id, ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) 
	{
		case V4L2_CID_EXT_HDMI_TIMING_INFO:
		case V4L2_CID_EXT_HDMI_DRM_INFO:
		case V4L2_CID_EXT_HDMI_VSI_INFO:
		case V4L2_CID_EXT_HDMI_SPD_INFO:
		case V4L2_CID_EXT_HDMI_AVI_INFO:
		case V4L2_CID_EXT_HDMI_PACKET_INFO:
		case V4L2_CID_EXT_HDMI_EDID:
		case V4L2_CID_EXT_HDMI_EDID_ACCESS:
		case V4L2_CID_EXT_HDMI_CONNECTION_STATE:
		case V4L2_CID_EXT_HDMI_HPD:
		case V4L2_CID_EXT_HDMI_HDCP_KEY:
		case V4L2_CID_EXT_HDMI_VRR_FREQUENCY:
		case V4L2_CID_EXT_HDMI_EMP_INFO:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER:
		case V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS:
		case V4L2_CID_EXT_HDMI_PHY_STATUS:
		case V4L2_CID_EXT_HDMI_LINK_STATUS:
		case V4L2_CID_EXT_HDMI_VIDEO_STATUS:
		case V4L2_CID_EXT_HDMI_AUDIO_STATUS:
		case V4L2_CID_EXT_HDMI_HDCP_STATUS:
		case V4L2_CID_EXT_HDMI_SCDC_STATUS:
		case V4L2_CID_EXT_HDMI_ERROR_STATUS:
		case V4L2_CID_EXT_HDMI_EXPERT_SETTING:
		case V4L2_CID_EXT_HDMI_OVERRIDE_EOTF:
		//case V4L2_CID_EXT_HDMI_DOLBY_CONTENT:
		//case V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON:
		case V4L2_CID_EXT_HDMI_QUERYCAP:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE:
		case V4L2_CID_EXT_HDMI_SLEEP:
		case V4L2_CID_EXT_HDMI_DPMS:
			ret = -EPERM;	
			break;
		case V4L2_CID_EXT_HDMI_POWER_OFF:
			{
				if(ctrl->value == 0){
					/* Power On */
					_g_v4l2_hdmi20_power = 0;
				}
				else {
					/* Power Off */
					_g_v4l2_hdmi20_power = 1;

					if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
						HDMI20_V4L2_REG_RD(0xCA3A6004, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xCA3A6004, data);
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
						HDMI20_V4L2_REG_RD(0xC8862004, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xC8862004, data);
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
						HDMI20_V4L2_REG_RD(0xC61B2004, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xC61B2004, data);

						HDMI20_V4L2_REG_RD(0xF3512004, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xF3512004, data);
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
						HDMI20_V4L2_REG_RD(0xCA432004, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xCA432004, data);
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
						/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
						HDMI20_V4L2_REG_RD(0xC98A2404, data);
						data &= (~0x1F1F);
						data |= (0x1F00);
						HDMI20_V4L2_REG_WR(0xC98A2404, data);
					}
					else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
						/* Make Sure to Set DDC/Link clock gating ON at this point, and free it before HPD Up */
						HDMI20_V4L2_REG_RD(0xC330004C, data);
						data &= (~0x1F1F0000);
						data |= (0x1F000000);
						HDMI20_V4L2_REG_WR(0xC330004C, data);
					}

				}

				ret = RET_OK;
			}
			break;
		case V4L2_CID_EXT_HDMI_DISCONNECT:
			{
				/* save latest value */
				_g_v4l2_hdmi20_disconnect = ctrl->value;
				ret = 0;

				switch(ctrl->value)
				{
					case V4L2_EXT_HDMI_INPUT_PORT_1:
						HDMI21_HAL_Rx_Set_V4l2PortActivate(0, 0);
						break;

					case V4L2_EXT_HDMI_INPUT_PORT_2:
						HDMI21_HAL_Rx_Set_V4l2PortActivate(1, 0);
						break;

					case V4L2_EXT_HDMI_INPUT_PORT_3:
						HDMI21_HAL_Rx_Set_V4l2PortActivate(2, 0);
						break;

					case V4L2_EXT_HDMI_INPUT_PORT_4:
						HDMI21_HAL_Rx_Set_V4l2PortActivate(3, 0);
						break;

					case V4L2_EXT_HDMI_INPUT_PORT_5:
						HDMI21_HAL_Rx_Set_V4l2PortActivate(4, 0);
						break;

					case V4L2_EXT_HDMI_INPUT_PORT_ALL:
						for(i=0; i<fh->numOfPort; i++) {
							/* Release all ports */
							HDMI21_HAL_Rx_Set_V4l2PortActivate(i, 0);
						}
						break;

					default :
						/* 2025/07/30 won.hur : Request from MS lab(AVTask-1544) */
						printk("%s:%s : Error! Invalid param[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ctrl->value);
						ret = -EINVAL;
						break;
				}
				
			}
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret;
}

static int v4l2_hdmi20_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	//struct hdmi20_fh *fh = __fh;
	int ret = RET_OK;

	//printk("hdmi20 v4l2 s ext ctrl : Count[%d]\n", ctrls->count);

	switch (ctrl->id) 
	{
		case V4L2_CID_EXT_HDMI_TIMING_INFO:
		case V4L2_CID_EXT_HDMI_DRM_INFO:
		case V4L2_CID_EXT_HDMI_VSI_INFO:
		case V4L2_CID_EXT_HDMI_SPD_INFO:
		case V4L2_CID_EXT_HDMI_AVI_INFO:
		case V4L2_CID_EXT_HDMI_PACKET_INFO:
		case V4L2_CID_EXT_HDMI_EDID:
		case V4L2_CID_EXT_HDMI_EDID_ACCESS:				
		case V4L2_CID_EXT_HDMI_CONNECTION_STATE:
		case V4L2_CID_EXT_HDMI_HPD:
		case V4L2_CID_EXT_HDMI_HDCP_KEY:
		case V4L2_CID_EXT_HDMI_VRR_FREQUENCY:
		case V4L2_CID_EXT_HDMI_EMP_INFO:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER:
		case V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS:
		case V4L2_CID_EXT_HDMI_PHY_STATUS:
		case V4L2_CID_EXT_HDMI_LINK_STATUS:
		case V4L2_CID_EXT_HDMI_VIDEO_STATUS:
		case V4L2_CID_EXT_HDMI_AUDIO_STATUS:
		case V4L2_CID_EXT_HDMI_HDCP_STATUS:
		case V4L2_CID_EXT_HDMI_SCDC_STATUS:
		case V4L2_CID_EXT_HDMI_ERROR_STATUS:
		case V4L2_CID_EXT_HDMI_EXPERT_SETTING:
		case V4L2_CID_EXT_HDMI_OVERRIDE_EOTF:
		//case V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON:
		//case V4L2_CID_EXT_HDMI_DOLBY_CONTENT:
		case V4L2_CID_EXT_HDMI_QUERYCAP:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY:
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE: 
		case V4L2_CID_EXT_HDMI_SLEEP:
		case V4L2_CID_EXT_HDMI_DPMS:
			ret = -EPERM;	
			break;
		case V4L2_CID_EXT_HDMI_POWER_OFF:
			{
				ctrl->value = _g_v4l2_hdmi20_power;
				ret = RET_OK;
			}
			break;
		case V4L2_CID_EXT_HDMI_DISCONNECT:
			{
				ctrl->value = _g_v4l2_hdmi20_disconnect;
				//ret = RET_OK;
				ret = 0;
		}
			break;
		default:
			ret = -EINVAL;
			break;
	}


	return ret;
}

static int v4l2_hdmi20_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	struct hdmi20_fh *fh = __fh;
	int i, ret = RET_OK;

	//printk("hdmi20 v4l2 s ext ctrl : Count[%d]\n", ctrls->count);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = v4l2_hdmi20_process_ctrl(ctrl, 0, fh);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}

		}
		return ret;
	}

	return ret;
}


static int v4l2_hdmi20_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	struct hdmi20_fh *fh = __fh;

	int i, ret = 0;

	//printk("hdmi20 v4l2 g ext ctrl : Count[%d]\n", ctrls->count);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			ret = v4l2_hdmi20_process_ctrl(ctrl, 1, fh);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;

}

static int v4l2_hdmi20_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	struct hdmi20_fh *fh = __fh;
	int ret = RET_OK;
	int __internal_port = 0;

	printk("[%s] entered with input[%d] \n", __func__, i);
	//get hdmi-port num from user
	_g_v4l2_hdmi20_port = i;


	/* 2020/03/30 : To notify driver for power saving */
	/* Need to convert V4L2 port -> BSP chip port */
	__internal_port = (int)_g_v4l2_hdmi20_port - 1;
	
	do {
		if((__internal_port ) >= fh->numOfPort){
			printk("Error! Unknwon Port[%d].\n", i);
			break;
		}

		HDMI21_HAL_Rx_Set_V4l2PortActivate(__internal_port, 1);

	} while(0);

	return ret;
}

static int v4l2_hdmi20_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	//struct hdmi20_fh *fh = __fh;
	int ret = RET_OK;

	printk("[%s] entered with input address[0x%p] \n", __func__, i);

	if( i == NULL)
		return -EPERM;

	//TODO: implement vidioc_g_input with port
	
	//copy hdmi-port num to user
	*i = _g_v4l2_hdmi20_port;

	return ret;
}

static int v4l2_hdmi20_vidioc_s_output(struct file *file, void *__fh, unsigned int i)
{
	//struct hdmi20_fh *fh = __fh;
	int ret = RET_OK;

	//printk("[%s] entered with input[%d] %d\n", __func__, i);

	return ret;
}

static int v4l2_hdmi20_vidioc_g_output(struct file *file, void *__fh, unsigned int *i)
{
	//struct hdmi20_fh *fh = __fh;
	int ret = RET_OK;

	//printk("[%s] entered with input[%d] %d\n", __func__, i);

	return ret;
}

static int __V4L2_HDMI20_Fill_HDMI_Capability(int _port_num, struct v4l2_ext_hdmi_capability * _cap)
{
	int ret = RET_ERROR;
	
	//Sanity Check
	if( _cap == NULL )
	{
		printk("pointer of cap is invalid..!\n");
		ret = RET_INVALID_PARAMS;
		goto failed;
	}

	//1. fill chip info
	if( lx_chip_rev() >= LX_CHIP_REV(O26, A0))
		strncpy(_cap->chip, "o26", sizeof(_cap->chip)-1);
	else if( lx_chip_rev() >= LX_CHIP_REV(O24, A0))
		strncpy(_cap->chip, "o24", sizeof(_cap->chip)-1);
	else if( lx_chip_rev() >= LX_CHIP_REV(M23, A0))
		strncpy(_cap->chip, "m23", sizeof(_cap->chip)-1);
	else if( lx_chip_rev() >= LX_CHIP_REV(O22, A0))
		strncpy(_cap->chip, "o22", sizeof(_cap->chip)-1);
	else if( lx_chip_rev() >= LX_CHIP_REV(E60, A0))
		strncpy(_cap->chip, "e60", sizeof(_cap->chip)-1);
	else if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
		strncpy(_cap->chip, "o20", sizeof(_cap->chip)-1);
	else 
		strncpy(_cap->chip, "unknown", sizeof(_cap->chip)-1);

	//2. fill version info
	_cap->version = LINUX_VERSION_CODE;
	
	//3. fill capability flag
	_cap->capabilities = 0x0;
	_cap->capabilities |= V4L2_EXT_HDMI_HDCP14;
	// _cap->capabilities |= V4L2_EXT_HDMI_HDCP14_KEY_OTP; /* 2020/03/02 won.hur : SIC does not support HDCP OTP */
	_cap->capabilities |= V4L2_EXT_HDMI_HDCP23;
	//_cap->capabilities |= V4L2_EXT_HDMI_HDCP23_KEY_OTP; /* 2020/03/02 won.hur : SIC does not support HDCP OTP */
	_cap->capabilities |= V4L2_EXT_HDMI_HDMI14;
	_cap->capabilities |= V4L2_EXT_HDMI_HDMI20;

	_cap->capabilities |= V4L2_EXT_HDMI_TMDS_3G;
	_cap->capabilities |= V4L2_EXT_HDMI_TMDS_6G;
	if (lx_chip() != LX_CHIP_M23) {
		_cap->capabilities |= V4L2_EXT_HDMI_HDMI21;

		_cap->capabilities |= V4L2_EXT_HDMI_FRL_3L_3G;
		_cap->capabilities |= V4L2_EXT_HDMI_FRL_3L_6G;
		_cap->capabilities |= V4L2_EXT_HDMI_FRL_4L_6G;
		_cap->capabilities |= V4L2_EXT_HDMI_FRL_4L_8G;
		_cap->capabilities |= V4L2_EXT_HDMI_FRL_4L_10G;
		
		if( lx_chip_rev() >= LX_CHIP_REV(E60, A0)) {	
			_cap->capabilities |= V4L2_EXT_HDMI_FRL_4L_12G;
		}

		_cap->capabilities |= V4L2_EXT_HDMI_DSC;
		_cap->capabilities |= V4L2_EXT_HDMI_FVA;
		_cap->capabilities |= V4L2_EXT_HDMI_VRR;
		_cap->capabilities |= V4L2_EXT_HDMI_CINEMAVRR;
		_cap->capabilities |= V4L2_EXT_HDMI_DOLBY_VISION_LL;
		_cap->capabilities |= V4L2_EXT_HDMI_DOLBY_VISION;
	}
	_cap->capabilities |= V4L2_EXT_HDMI_BACKGROUND_TIMING_DETECT;
	// _cap->capabilities |= V4L2_EXT_HDMI_DOLBY_VISION_HDMI21; /* 2020/03/02 won.hur : Not yet */
	_cap->capabilities |= V4L2_EXT_HDMI_512BYTE_EDID;
	_cap->capabilities |= V4L2_EXT_HDMI_EMPACKET;
	_cap->capabilities |= V4L2_EXT_HDMI_HDCP_REPEATER;


	ret = RET_OK;
failed:
	return ret;
}

static int __V4L2_HDMI20_Get_QueryCapability(struct v4l2_ext_control *_ctrl)
{
	int ret = RET_ERROR;
	int port_num = -1;

	struct v4l2_ext_hdmi_querycap userdata;	

	//Size Check
	if( _ctrl->size != sizeof(struct v4l2_ext_hdmi_querycap) )
	{
		printk("Ginven size [%d] is not [%lu]\n", _ctrl->size, sizeof(struct v4l2_ext_hdmi_querycap));
		ret = RET_INVALID_PARAMS;
		goto failed;
	}

	//Get user data
	ret = copy_from_user( (struct v4l2_ext_hdmi_querycap *)&userdata, (void __user *)_ctrl->string, 
			sizeof(struct v4l2_ext_hdmi_querycap)); 
	if(ret)
	{
		printk("Failed to copy_from_user!\n");
		ret = RET_TRY_AGAIN;
		goto failed;
	}

	//Check port-num
	port_num = userdata.port;
	//TODO : Check Max-num of port-num
	if( port_num < 0)
	{
		printk("received hdmi port-num[%02d] is invalid!\n", port_num);
		ret = RET_INVALID_PARAMS;
	}

	//Fill hdmi capability
	ret = __V4L2_HDMI20_Fill_HDMI_Capability(port_num,  &userdata.hdmi_capability );
	if( ret != RET_OK )
	{
		printk("Failed to Fill HDMI-Capability!\n");
		goto failed;
	}

	//Copy to user
	ret = copy_to_user( (void __user *)_ctrl->string, (void *)&userdata, 
			sizeof(struct v4l2_ext_hdmi_querycap));
	if(ret)
	{
		printk("Failed to copy_to_user!\n");
		ret =RET_TRY_AGAIN;
		goto failed;
	}

failed:
	return ret;
}

static int v4l2_hdmi20_process_ctrl(struct v4l2_ext_control *ctrl, int isGet, void *__fh)
{
	int ret = RET_OK;
	struct hdmi20_fh *fh = __fh;

	//printk("%s : &ctrl->id[0x%x] :[0x%x][%s] CommandType[%s], PTR[0x%x]\n", __func__, &ctrl->id, ctrl->id, ctrl_id_to_str(ctrl->id), isGet?"Get":"Set", ctrl->ptr);

	if(ctrl->ptr == NULL){
		//printk("%s : PTR is NULL. Will not proceed\n", __func__);	
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_HDMI_TIMING_INFO:
			{
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				LX_HDMI_TIMING_INFO_T data;
				LX_HDMI20_OP_STATUS_T status;
				struct v4l2_ext_hdmi_timing_info userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_timing_info)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_timing_info));
					ret = RET_INVALID_PARAMS;	
					break;
				}

				if( lx_board_opt() & LX_BOARD_OPT_SLT) {
					printk("%s:%s : Port[%d] isGet[%d]\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, isGet); 
				}

				memset(&data, 0, sizeof(LX_HDMI_TIMING_INFO_T));

				if(copy_from_user((struct v4l2_ext_hdmi_timing_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_timing_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_TimingInfo((userdata.port - 1), &data, sizeof(LX_HDMI_TIMING_INFO_T) ,1);

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : GetTimingInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

				ret = HDMI20_Module_Get_OperationStatus((userdata.port -1), &status);
				if(ret < 0){
					printk("%s:%s : Get Module Operation Status Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				userdata.h_freq = data.hFreq;
				userdata.v_vreq = data.vFreq; 
				userdata.h_total = data.hTotal;
				userdata.v_total = data.vTotal ;
				userdata.h_porch = data.vStart;
				userdata.v_porch = data.hStart;
				userdata.scan_type = data.scanType;
				userdata.active.x = 0;
				userdata.active.y = 0;
				userdata.active.w = data.hActive;
				userdata.active.h = data.vActive;
				if(data.isAllmMode > 0) userdata.allm_mode = 1;
				else userdata.allm_mode = 0;

				/* 20191014 */
				_p = &gHDMI21RxHandler[userdata.port-1];
				
				if(status.isSteady == true) {
					if(status.isDVI == true){
						userdata.dvi_hdmi 	= V4L2_EXT_HDMI_MODE_DVI;
					}
					else{
						userdata.dvi_hdmi 	= V4L2_EXT_HDMI_MODE_HDMI;
					}
				}
				else{
					userdata.dvi_hdmi 	= V4L2_EXT_HDMI_MODE_DVI;
				}
				
				if((data.deepColorMode == 0) || (data.deepColorMode == 4)) userdata.color_depth = V4L2_EXT_HDMI_COLOR_DEPTH_8BIT; 
				else if(data.deepColorMode == 5)	userdata.color_depth = V4L2_EXT_HDMI_COLOR_DEPTH_10BIT; 
				else if(data.deepColorMode == 6)	userdata.color_depth = V4L2_EXT_HDMI_COLOR_DEPTH_12BIT; 
				else if(data.deepColorMode == 7)	userdata.color_depth = V4L2_EXT_HDMI_COLOR_DEPTH_16BIT; 			
				else userdata.color_depth = V4L2_EXT_HDMI_COLOR_DEPTH_8BIT; 
					
				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_timing_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_DRM_INFO:
			{
				LX_HDMI20_RX_DRM_PACKET_T data;
				struct v4l2_ext_hdmi_drm_info userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_drm_info)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_drm_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset(&data, 0, sizeof(LX_HDMI20_RX_DRM_PACKET_T));

				if(copy_from_user((struct v4l2_ext_hdmi_drm_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_drm_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret =  HDMI20_Module_Get_DRMInfo((userdata.port - 1), &data, sizeof(LX_HDMI20_RX_DRM_PACKET_T), 1);

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : GetDRMInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

				/* Step 3. Set data for DIL */
				userdata.version  = data.nVersion;
				userdata.length   = data.nLength;

				userdata.eotf_type  = (int)(data.metaData[4]);
				userdata.meta_desc = (int)(data.metaData[5]);

				memcpy((void *)&userdata.display_primaries_x0, (void *)&data.metaData[6], sizeof(unsigned short));
				memcpy((void *)&userdata.display_primaries_y0, (void *)&data.metaData[8], sizeof(unsigned short));
				memcpy((void *)&userdata.display_primaries_x1, (void *)&data.metaData[10], sizeof(unsigned short));
				memcpy((void *)&userdata.display_primaries_y1, (void *)&data.metaData[12], sizeof(unsigned short));
				memcpy((void *)&userdata.display_primaries_x2, (void *)&data.metaData[14], sizeof(unsigned short));
				memcpy((void *)&userdata.display_primaries_y2, (void *)&data.metaData[16], sizeof(unsigned short));
				memcpy((void *)&userdata.white_point_x, (void *)&data.metaData[18], sizeof(unsigned short));
				memcpy((void *)&userdata.white_point_y, (void *)&data.metaData[20], sizeof(unsigned short));
				memcpy((void *)&userdata.max_display_mastering_luminance, (void *)&data.metaData[22], sizeof(unsigned short));
				memcpy((void *)&userdata.min_display_mastering_luminance, (void *)&data.metaData[24], sizeof(unsigned short));
				memcpy((void *)&userdata.maximum_content_light_level, (void *)&data.metaData[26], sizeof(unsigned short));
				memcpy((void *)&userdata.maximum_frame_average_light_level, (void *)&data.metaData[28], sizeof(unsigned short));

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_drm_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			
			}
			break;
		case V4L2_CID_EXT_HDMI_VSI_INFO:
			{
				LX_HDMI_INFO_PACKET_T data;
				struct v4l2_ext_hdmi_vsi_info userdata;
				int i;
				LX_HDMI20_VSI_TYPE_T type = LX_HDMI20_VSI_UNKNOWN;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_vsi_info)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_vsi_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));

				if(copy_from_user((struct v4l2_ext_hdmi_vsi_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_vsi_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN; 
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				/* 2020/05/25 : Check regid */
				if((userdata.regid[0] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_0) \
						&&  (userdata.regid[1] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_1) \
						&&  (userdata.regid[2] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_2)) {
					
					type = LX_HDMI20_VSI_H14B_VSIF;
				}
				else if((userdata.regid[0] ==  HDMI21_RX_VSI_TYPE_HF_OUI_0) \
						&&  (userdata.regid[1] ==  HDMI21_RX_VSI_TYPE_HF_OUI_1) \
						&&  (userdata.regid[2] ==  HDMI21_RX_VSI_TYPE_HF_OUI_2)) {
					
					type = LX_HDMI20_VSI_HF_VSIF;
				}
				else if((userdata.regid[0] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_0) \
						&&  (userdata.regid[1] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_1) \
						&&  (userdata.regid[2] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_2)) {
			
					type = LX_HDMI20_VSI_DOLBY;
				}
				else {
					type = LX_HDMI20_VSI_UNKNOWN;
				}


				ret = HDMI20_Module_Get_VSIInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1, type);

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : GetVSIInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

				userdata.regid[0]                        = (data.dataBytes[0] &0xff00)>>8;
				userdata.regid[1]                        = (data.dataBytes[0] &0xff0000)>>16;
				userdata.regid[2]                        = (data.dataBytes[0] &0xff000000)>>24;

				for (i = 1; i < 6; i++)
				{
					userdata.payload [i*4]			= (data.dataBytes[i] & 0xff);
					userdata.payload [i*4 +1]		= (data.dataBytes[i] & 0xff00)>>8;
					userdata.payload [i*4 +2]		= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.payload [i*4 +3]		= (data.dataBytes[i] & 0xff000000)>>24;
				}

				for (i = 0; i < 4; i++)
				{
					userdata.packet.data_bytes [i*4]		= (data.dataBytes[i] & 0xff);
					userdata.packet.data_bytes [i*4 +1]	= (data.dataBytes[i] & 0xff00)>>8;
					userdata.packet.data_bytes [i*4 +2]	= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.packet.data_bytes [i*4 +3]	= (data.dataBytes[i] & 0xff000000)>>24;
				}

				userdata.packet.type		= 0x81;
				userdata.packet.version	= (data.header & 0xff);
				userdata.packet.length	= (data.header &0xff00 )>>8;

				userdata.video_format 	= ((data.dataBytes[1] &0xff))>> 5;
				/* WA for china devices */
				if(userdata.video_format == 1){
					userdata.video_format = 0;
				}

				userdata.st_3d 	= ((data.dataBytes[1] &0xff00)>>8)>> 4;
				userdata.ext_data_3d 		= ((data.dataBytes[1] &0xff0000)>>16)>> 4;
				userdata.vic 		= (data.dataBytes[1] &0xff00)>>8;

				userdata.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_vsi_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_SPD_INFO:
			{
				LX_HDMI_INFO_PACKET_T data;
				struct v4l2_ext_hdmi_spd_info userdata;
				int i;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_spd_info)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_spd_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));

				if(copy_from_user((struct v4l2_ext_hdmi_spd_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_spd_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_SPDInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1);

				if(ret < 0){
					ret = RET_INVALID_PARAMS;
					printk("%s:%s : GetSPDInfo Error[%d]. port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

				for (i = 0; i < (V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN/4); i++)
				{
					userdata.vendor_name[i*4+0]			= (data.dataBytes[i] &0xff00)>>8;
					userdata.vendor_name[i*4+1]			= (data.dataBytes[i] &0xff0000)>>16;
					userdata.vendor_name[i*4+2]			= (data.dataBytes[i] &0xff000000)>>24;
					userdata.vendor_name[i*4+3]			= (data.dataBytes[i+1] &0xff);
				}

				for (i = 0; i < (V4L2_EXT_HDMI_SPD_IF_DESC_LEN/4); i++)
				{
					userdata.product_description[i*4+0]	 	= (data.dataBytes[i+2] &0xff00)>>8;
					userdata.product_description[i*4+1]	 	= (data.dataBytes[i+2] &0xff0000)>>16;
					userdata.product_description[i*4+2]	 	= (data.dataBytes[i+2] &0xff000000)>>24;
					userdata.product_description[i*4+3]	 	= (data.dataBytes[i+3] &0xff);
				}

				userdata.source_device_info = (data.dataBytes[6] &0xff00)>>8;

				userdata.packet.type		= 0x83;
				userdata.packet.version	= (data.header & 0xff);
				userdata.packet.length	= (data.header &0xff00 )>>8;

				for (i = 0; i < 7; i++)
				{
					userdata.packet.data_bytes[i*4+0]			= (data.dataBytes[i] &0xff00)>>8;
					userdata.packet.data_bytes[i*4+1]			= (data.dataBytes[i] &0xff0000)>>16;
					userdata.packet.data_bytes[i*4+2]			= (data.dataBytes[i] &0xff000000)>>24;
					userdata.packet.data_bytes[i*4+3]			= (data.dataBytes[i+1] &0xff);
				}

				userdata.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_spd_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_AVI_INFO:
			{
				LX_HDMI20_OP_STATUS_T status;
				LX_HDMI_INFO_PACKET_T data;
				int i;
				struct v4l2_ext_hdmi_avi_info userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_avi_info)){
					//printk(" %s:%s : Given Size[%d] is not [%d]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_avi_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));

				if(copy_from_user((struct v4l2_ext_hdmi_avi_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_avi_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_OperationStatus((userdata.port -1), &status);
				if(ret < 0){
					printk("%s:%s : Get Module Operation Status Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_AVIInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1);

				if(ret < 0){
					printk("%s:%s : GetAVIInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				/* If not on stable video status, respond as DVI : 2019/03/06 request from yusun85.lee(http://clm.lge.com/issue/browse/SCDCR-2205) */
				if(status.isSteady == true) {
					if(status.isDVI == true){
						userdata.mode 	= V4L2_EXT_HDMI_MODE_DVI;
					}
					else{
						userdata.mode 	= V4L2_EXT_HDMI_MODE_HDMI;
					}
				}
				else{
					userdata.mode 	= V4L2_EXT_HDMI_MODE_DVI;
				}
			
				userdata.pixel_encoding						= (((data.dataBytes[0] &0xff00)>>8) &0x60)>>5;				// Y1Y0
				userdata.active_info							= (((data.dataBytes[0] &0xff00)>>8) &0x10)>>4;				// A0
				userdata.bar_info							= (((data.dataBytes[0] &0xff00)>>8) &0x0c)>>2;						// B1B0
				userdata.scan_info							= (((data.dataBytes[0] &0xff00)>>8) &0x03);						// S1S0

				userdata.colorimetry						= (((data.dataBytes[0] &0xff0000)>>16) &0xc0)>>6;				// C1C0
				userdata.picture_aspect_ratio					= (((data.dataBytes[0] &0xff0000)>>16) &0x30)>>4;		// M1M0
				userdata.active_format_aspect_ratio				= (((data.dataBytes[0] &0xff0000)>>16) &0x0f);		// R3R2R1R0

				userdata.it_content							= (((data.dataBytes[0] &0xff000000)>>24) &0x80)>>7;			// ITC
				userdata.extended_colorimetry				= (((data.dataBytes[0] &0xff000000)>>24) &0x70)>>4;	// EC2EC1EC0
				userdata.rgb_quantization_range				= (((data.dataBytes[0] &0xff000000)>>24) &0x0c)>>2;	// Q1Q0
				userdata.scaling							= (((data.dataBytes[0] &0xff000000)>>24) &0x03);					// SC1SC0
				userdata.vic						= (((data.dataBytes[1] &0xff)) &0xff);				// VIC6~VIC0

				userdata.ycc_quantization_range				= (((data.dataBytes[1] &0xff00)>>8) &0xc0)>>6;			// YQ1YQ0
				userdata.content_type  						= (((data.dataBytes[1] &0xff00)>>8) &0x30)>>4;					// CN1CN0
				userdata.pixel_repeat							= (((data.dataBytes[1] &0xff00)>>8) &0x0f);							// PR3PR2PR1PR0

				userdata.top_bar_end_line_number				= ((data.dataBytes[1] &0xffff0000)>>16);								// Line Number of End of Top Bar
				userdata.bottom_bar_start_line_number			= ((data.dataBytes[2] &0xffff));	// Line Number of Start of Bottom Bar
				userdata.left_bar_end_pixel_number				= ((data.dataBytes[2] &0xffff0000)>>16);								// Pixel Number of End of Left Bar
				userdata.right_bar_end_pixel_number				=((data.dataBytes[3] &0xffff));		// Pixel Number of Start of Right Bar


				userdata.packet.type			= 0x82;
				userdata.packet.version		= (data.header & 0xff);
				userdata.packet.length			= (data.header &0xff00 )>>8;

				if((userdata.packet.version) >= 4){
					userdata.additional_colorimetry = (((data.dataBytes[3] &0xff0000)>>16)&0xF0)>>4;	// ACE3ACE2ACE1ACE0
					//printk("%s:%s : V4L2 add_color1(%d) byte3:[0x%x]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port, (data.dataBytes[3]));
				}else{
					userdata.additional_colorimetry = 0;
					//printk("%s:%s : V4L2 add_color1(%d) byte3:[0x%x]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port, (data.dataBytes[3]));
				}

				for (i = 0; i < 6; i++)
				{
					userdata.packet.data_bytes [i*4]		= (data.dataBytes[i] & 0xff);
					userdata.packet.data_bytes [i*4 +1]	= (data.dataBytes[i] & 0xff00)>>8;
					userdata.packet.data_bytes [i*4 +2]	= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.packet.data_bytes [i*4 +3]	= (data.dataBytes[i] & 0xff000000)>>24;
				}

				userdata.mode = (data.dataBytes[7] &0x1);
				
				userdata.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_avi_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_PACKET_INFO:
			{
				LX_HDMI20_OP_STATUS_T status;
				LX_HDMI_INFO_PACKET_T data;
				int i;
				struct v4l2_ext_hdmi_packet_info userdata;
				LX_HDMI20_VSI_TYPE_T type = LX_HDMI20_VSI_UNKNOWN;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_packet_info)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_packet_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_packet_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_packet_info))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s : Error! Port exceeded max port(%d)\n", __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				/* VSI */
				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));
		
				/* 2020/05/25 : Check regid */
				if((userdata.vsi.regid[0] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_0) \
						&&  (userdata.vsi.regid[1] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_1) \
						&&  (userdata.vsi.regid[2] ==  HDMI21_RX_VSI_TYPE_H14B_OUI_2)) {
					
					type = LX_HDMI20_VSI_H14B_VSIF;
				}
				else if((userdata.vsi.regid[0] ==  HDMI21_RX_VSI_TYPE_HF_OUI_0) \
						&&  (userdata.vsi.regid[1] ==  HDMI21_RX_VSI_TYPE_HF_OUI_1) \
						&&  (userdata.vsi.regid[2] ==  HDMI21_RX_VSI_TYPE_HF_OUI_2)) {
					
					type = LX_HDMI20_VSI_HF_VSIF;
				}
				else if((userdata.vsi.regid[0] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_0) \
						&&  (userdata.vsi.regid[1] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_1) \
						&&  (userdata.vsi.regid[2] ==  HDMI21_RX_VSI_TYPE_DOLBY_OUI_2)) {
			
					type = LX_HDMI20_VSI_DOLBY;
				}
				else {
					type = LX_HDMI20_VSI_UNKNOWN;
				}

				ret = HDMI20_Module_Get_VSIInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1, type);

				if(ret < 0){
					printk("%s:%s : GetVSIInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret =RET_INVALID_PARAMS;
					break;
				}

				userdata.vsi.regid[0]                        = (data.dataBytes[0] &0xff00)>>8;
				userdata.vsi.regid[1]                        = (data.dataBytes[0] &0xff0000)>>16;
				userdata.vsi.regid[2]                        = (data.dataBytes[0] &0xff000000)>>24;

				for (i = 1; i < 6; i++)
				{
					userdata.vsi.payload [i*4]			= (data.dataBytes[i] & 0xff);
					userdata.vsi.payload [i*4 +1]		= (data.dataBytes[i] & 0xff00)>>8;
					userdata.vsi.payload [i*4 +2]		= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.vsi.payload [i*4 +3]		= (data.dataBytes[i] & 0xff000000)>>24;
				}

				for (i = 0; i < 4; i++)
				{
					userdata.vsi.packet.data_bytes [i*4]		= (data.dataBytes[i] & 0xff);
					userdata.vsi.packet.data_bytes [i*4 +1]	= (data.dataBytes[i] & 0xff00)>>8;
					userdata.vsi.packet.data_bytes [i*4 +2]	= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.vsi.packet.data_bytes [i*4 +3]	= (data.dataBytes[i] & 0xff000000)>>24;
				}

				userdata.vsi.packet.type		= 0x81;
				userdata.vsi.packet.version	= (data.header & 0xff);
				userdata.vsi.packet.length	= (data.header &0xff00 )>>8;

				userdata.vsi.video_format 	= ((data.dataBytes[1] &0xff))>> 5;
				/* WA for china devices */
				if(userdata.vsi.video_format == 1){
					userdata.vsi.video_format = 0;
				}

				userdata.vsi.st_3d 	= ((data.dataBytes[1] &0xff00)>>8)>> 4;
				userdata.vsi.ext_data_3d 		= ((data.dataBytes[1] &0xff0000)>>16)>> 4;
				userdata.vsi.vic 		= (data.dataBytes[1] &0xff00)>>8;

				userdata.vsi.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;
				/* End of VSI */

				/* AVI */
				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));

				ret = HDMI20_Module_Get_OperationStatus((userdata.port -1), &status);
				if(ret < 0){
					printk("%s:%s : Get Module Operation Status Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_AVIInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1);

				if(ret < 0){
					printk("%s:%s : GetAVIInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

				/* If not on stable video status, respond as DVI : 2019/03/06 request from yusun85.lee(http://clm.lge.com/issue/browse/SCDCR-2205) */
				if(status.isSteady == true) {
					if(status.isDVI == true){
						userdata.avi.mode 	= V4L2_EXT_HDMI_MODE_DVI;
					}
					else{
						userdata.avi.mode 	= V4L2_EXT_HDMI_MODE_HDMI;
					}
				}
				else{
					userdata.mode 	= V4L2_EXT_HDMI_MODE_DVI;
				}

				userdata.avi.pixel_encoding						= (((data.dataBytes[0] &0xff00)>>8) &0x60)>>5;				// Y1Y0
				userdata.avi.active_info							= (((data.dataBytes[0] &0xff00)>>8) &0x10)>>4;				// A0
				userdata.avi.bar_info							= (((data.dataBytes[0] &0xff00)>>8) &0x0c)>>2;						// B1B0
				userdata.avi.scan_info							= (((data.dataBytes[0] &0xff00)>>8) &0x03);						// S1S0

				userdata.avi.colorimetry						= (((data.dataBytes[0] &0xff0000)>>16) &0xc0)>>6;				// C1C0
				userdata.avi.picture_aspect_ratio					= (((data.dataBytes[0] &0xff0000)>>16) &0x30)>>4;		// M1M0
				userdata.avi.active_format_aspect_ratio				= (((data.dataBytes[0] &0xff0000)>>16) &0x0f);		// R3R2R1R0

				userdata.avi.it_content							= (((data.dataBytes[0] &0xff000000)>>24) &0x80)>>7;			// ITC
				userdata.avi.extended_colorimetry				= (((data.dataBytes[0] &0xff000000)>>24) &0x70)>>4;	// EC2EC1EC0
				userdata.avi.rgb_quantization_range				= (((data.dataBytes[0] &0xff000000)>>24) &0x0c)>>2;	// Q1Q0
				userdata.avi.scaling							= (((data.dataBytes[0] &0xff000000)>>24) &0x03);					// SC1SC0
				userdata.avi.vic						= (((data.dataBytes[1] &0xff)) &0xff);				// VIC6~VIC0

				userdata.avi.ycc_quantization_range				= (((data.dataBytes[1] &0xff00)>>8) &0xc0)>>6;			// YQ1YQ0
				userdata.avi.content_type  						= (((data.dataBytes[1] &0xff00)>>8) &0x30)>>4;					// CN1CN0
				userdata.avi.pixel_repeat							= (((data.dataBytes[1] &0xff00)>>8) &0x0f);							// PR3PR2PR1PR0

				userdata.avi.top_bar_end_line_number				= ((data.dataBytes[1] &0xffff0000)>>16);								// Line Number of End of Top Bar
				userdata.avi.bottom_bar_start_line_number			= ((data.dataBytes[2] &0xffff));	// Line Number of Start of Bottom Bar
				userdata.avi.left_bar_end_pixel_number				= ((data.dataBytes[2] &0xffff0000)>>16);								// Pixel Number of End of Left Bar
				userdata.avi.right_bar_end_pixel_number				=((data.dataBytes[3] &0xffff));		// Pixel Number of Start of Right Bar


				userdata.avi.packet.type			= 0x82;
				userdata.avi.packet.version		= (data.header & 0xff);
				userdata.avi.packet.length			= (data.header &0xff00 )>>8;

				if((userdata.avi.packet.version) >= 4){
					userdata.avi.additional_colorimetry = (((data.dataBytes[3] &0xff0000)>>16)&0xF0)>>4;	// ACE3ACE2ACE1ACE0
				}else{
					userdata.avi.additional_colorimetry = 0;
				}
				
				for (i = 0; i < 6; i++)
				{
					userdata.avi.packet.data_bytes [i*4]		= (data.dataBytes[i] & 0xff);
					userdata.avi.packet.data_bytes [i*4 +1]	= (data.dataBytes[i] & 0xff00)>>8;
					userdata.avi.packet.data_bytes [i*4 +2]	= (data.dataBytes[i] & 0xff0000)>>16;
					userdata.avi.packet.data_bytes [i*4 +3]	= (data.dataBytes[i] & 0xff000000)>>24;
				}

				userdata.avi.mode = (data.dataBytes[7] &0x1);
				
				userdata.avi.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;
				/* End Of AVI */

				/* SPD */
				memset(&data, 0, sizeof(LX_HDMI_INFO_PACKET_T));
				ret = HDMI20_Module_Get_SPDInfo((userdata.port - 1), &data, sizeof(LX_HDMI_INFO_PACKET_T), 1);

				if(ret < 0){
					printk("%s:%s : GetSPDInfo Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					break;
				}

			for (i = 0; i < (V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN/4); i++)
				{
					userdata.spd.vendor_name[i*4+0]			= (data.dataBytes[i] &0xff00)>>8;
					userdata.spd.vendor_name[i*4+1]			= (data.dataBytes[i] &0xff0000)>>16;
					userdata.spd.vendor_name[i*4+2]			= (data.dataBytes[i] &0xff000000)>>24;
					userdata.spd.vendor_name[i*4+3]			= (data.dataBytes[i+1] &0xff);
				}

				for (i = 0; i < (V4L2_EXT_HDMI_SPD_IF_DESC_LEN/4); i++)
				{
					userdata.spd.product_description[i*4+0]	 	= (data.dataBytes[i+2] &0xff00)>>8;
					userdata.spd.product_description[i*4+1]	 	= (data.dataBytes[i+2] &0xff0000)>>16;
					userdata.spd.product_description[i*4+2]	 	= (data.dataBytes[i+2] &0xff000000)>>24;
					userdata.spd.product_description[i*4+3]	 	= (data.dataBytes[i+3] &0xff);
				}

				userdata.spd.source_device_info = (data.dataBytes[6] &0xff00)>>8;

				userdata.spd.packet.type		= 0x83;
				userdata.spd.packet.version	= (data.header & 0xff);
				userdata.spd.packet.length	= (data.header &0xff00 )>>8;

				for (i = 0; i < 7; i++)
				{
					userdata.spd.packet.data_bytes[i*4+0]			= (data.dataBytes[i] &0xff00)>>8;
					userdata.spd.packet.data_bytes[i*4+1]			= (data.dataBytes[i] &0xff0000)>>16;
					userdata.spd.packet.data_bytes[i*4+2]			= (data.dataBytes[i] &0xff000000)>>24;
					userdata.spd.packet.data_bytes[i*4+3]			= (data.dataBytes[i+1] &0xff);
				}

				userdata.spd.packet_status = V4L2_EXT_HDMI_PACKET_STATUS_UPDATED;
				
				/* END of SPD */


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_packet_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_DOLBY_HDR:
			{
				struct  v4l2_ext_hdmi_dolby_hdr userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_dolby_hdr)){
					//printk(" %s:%s : Given Size[%d] is not [%d]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_connection_state));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_dolby_hdr *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_dolby_hdr))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s :Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}
				
				switch( HDMI20_Module_Get_IsDolbyHDR(userdata.port-1))
				{
					case HDMI_DOLBY_STATE_OFF:
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_SDR;
						break;
					case HDMI_DOLBY_STD_OLDVSI:
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_1;
						break;
					case HDMI_DOLBY_STD_NEWVSI:
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_2;
						break;
					case HDMI_DOLBY_LL_422_12B:
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_LOW_LATENCY;
						break;
					case HDMI_DOLBY_LL_PC:
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_DOLBY_VISION_PC;
						break;
					default :
						userdata.type = V4L2_EXT_HDMI_DOLBY_HDR_TYPE_SDR;
						break;
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_dolby_hdr))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_EDID:
			{
				#if 1 
				struct v4l2_ext_hdmi_edid userdata;
				unsigned char *pData;
				int size = 0;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_edid)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_edid));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_edid *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_edid))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				printk("%s:%s : Size[%d] Port[%d] isGet[%d]\n", __func__, ctrl_id_to_str(ctrl->id), userdata.size, userdata.port, isGet); 

				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(userdata.size == V4L2_EXT_HDMI_EDID_SIZE_128) size = 128;
				else if(userdata.size == V4L2_EXT_HDMI_EDID_SIZE_256) size = 256;
				else if(userdata.size == V4L2_EXT_HDMI_EDID_SIZE_512) size = 512;
				else {
					printk("%s:%s : Unsupported Size[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.size);
					size = 0;
					ret = RET_INVALID_PARAMS; 
					break;
				}

				pData = (unsigned char *)kmalloc(size, GFP_KERNEL);
				memset((void *)pData, 0, size);

				if(isGet){
					ret = HDMI20_Module_Get_EDID((userdata.port - 1), pData, size, 1);
					if(copy_to_user((void __user *)userdata.pData, (void *)pData, size)){
						printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
						ret = RET_TRY_AGAIN;
						break;
					}
				}
				else{
					if(userdata.pData != NULL){
						if(copy_from_user((unsigned char *)pData, (void __user *)userdata.pData, size)){
							printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
							ret = RET_TRY_AGAIN;
							break;
						}
					}

					ret = HDMI20_Module_Set_EDID((userdata.port - 1), pData, size, 1);
				}

				if(ret < 0){
					printk("%s:%s : EDID Access Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					kfree(pData);

					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_edid))){
					printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}

				kfree(pData);
				#endif
			}
			break;
		case V4L2_CID_EXT_HDMI_EDID_ACCESS:
			{
				struct v4l2_ext_hdmi_edid_access userdata;
				volatile UINT32 data, data2;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_edid_access)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_edid_access));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_edid_access *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_edid_access))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				printk("%s:%s : Port[%d] isGet[%d]\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, isGet); 

				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(isGet){
					if ( lx_chip( ) == LX_CHIP_O26){
						HDMI20_V4L2_REG_RD(0xCA36000C, data); // M23:CRG_SUB > EDID0/1(edid_syn, woc_sync), O24:CRG_SUB > EDID(edid_syn), O26:CRG_SUB > EDID(woc_syn)
						if((userdata.port-1) == 0) 	{
							data &= (0x04);							
						}else if((userdata.port-1) == 1) {
							data &= (0x10);
						}else if((userdata.port-1) == 2) {
							data &= (0x40);
						}else if((userdata.port-1) == 3) {
							data &= (0x100);
						}

						HDMI20_V4L2_REG_RD(0xC883000C, data2);
					}else if ( lx_chip( ) == LX_CHIP_O24){
						HDMI20_V4L2_REG_RD(0xC883000C, data); 
						if((userdata.port-1) == 0) 	{
							data &= (0x04);							
						}else if((userdata.port-1) == 1) {
							data &= (0x10);
						}else if((userdata.port-1) == 2) {
							data &= (0x40);
						}else if((userdata.port-1) == 3) {
							data &= (0x100);
						}

						HDMI20_V4L2_REG_RD(0xC883000C, data2);
					}else if ( lx_chip( ) == LX_CHIP_M23){			
						if((userdata.port-1) == 0) 	{
							HDMI20_V4L2_REG_RD(0xC619000C, data);
							data &= (0x04);							
						}else if((userdata.port-1) == 1) {
							HDMI20_V4L2_REG_RD(0xC619000C, data);
							data &= (0x10);
						}else if((userdata.port-1) == 2) {
							HDMI20_V4L2_REG_RD(0xF311000C, data);
							data &= (0x4);
						}else if((userdata.port-1) == 3) {
							HDMI20_V4L2_REG_RD(0xF311000C, data);
							data &= (0x10);
						}

						HDMI20_V4L2_REG_RD(0xC619000C, data2);
					}

					if(data != 0) {
						userdata.mode = V4L2_EXT_HDMI_EDID_DISABLE;
						//printk("%s:%s : V4L2 EDID Get [Disable]. Port[%d] data[0x%x] data2[0x%x] \n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port-1, data, data2);
					}else{
						userdata.mode = V4L2_EXT_HDMI_EDID_ENABLE;
						//printk("%s:%s : V4L2 EDID Get [Enable]. Port[%d] data[0x%x] data2[0x%x] \n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port-1, data, data2);
					}
				}
				else{
					if(userdata.mode == V4L2_EXT_HDMI_EDID_ENABLE ){
						ret = HDMI20_Module_Set_EDID_Enable((userdata.port - 1), 1);
						//printk("%s:%s : V4L2 EDID Set [Enable]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port-1);
					}
					else if(userdata.mode == V4L2_EXT_HDMI_EDID_DISABLE){
						ret = HDMI20_Module_Set_EDID_Enable((userdata.port - 1), 0);
						//printk("%s:%s : V4L2 EDID Set [Disable]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port-1);
					}
					else {
						/* 2025/07/30 won.hur : Request from MS lab(AVTask-1544) */
						printk("%s:%s : Error! Invalid param[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.mode);
						ret = RET_INVALID_PARAMS;
						break;
					}
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_edid_access))){
					ret =RET_TRY_AGAIN;
				}
			}
			break;		
		case V4L2_CID_EXT_HDMI_CONNECTION_STATE:
			{
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				LX_HDMI_PHY_INFORM_T data;
				struct v4l2_ext_hdmi_connection_state userdata;
				int __5V = 0;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_connection_state)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_connection_state));
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset(&data, 0, sizeof(LX_HDMI_PHY_INFORM_T));

				if(copy_from_user((struct v4l2_ext_hdmi_connection_state *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_connection_state))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s :Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id),userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					_p = &gHDMI21RxHandler[userdata.port-1];

					ret = HDMI21_HAL_Rx_Get_Check5VLevelInfo((userdata.port -1), &__5V, 1);

					if( __5V > 0 )	{	userdata.state = 1;	}
					else 			{	userdata.state = 0;	}
				}
				else {	
					ret = HDMI20_Module_Get_PHYStatus(&data, sizeof(LX_HDMI_PHY_INFORM_T),  0, 1);
					userdata.state = data.hdmi5v[userdata.port - 1];
				}

				if(ret < 0){
					printk("%s:%s : HDMI20_PHY_Rx_Get_PHYStatus[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret);
					break;
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_connection_state))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_HPD:
			{
				LX_HDMI20_OP_STATUS_T status;
				struct v4l2_ext_hdmi_hpd userdata;
				LX_HDMI20_CMD_T cmd;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hpd)){
					//printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hpd));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_hpd *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hpd))){
					//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					//printk("%s:%s Wrong Port[%d] \n", __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				ret = HDMI20_Module_Get_OperationStatus((userdata.port -1), &status);
				if(ret < 0){
					printk("%s:%s : Get Module Operation Status Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(isGet){
					if(status.isRestartState == true)
					{
						userdata.hpd_state = gHDMI20EnableStatus[userdata.port];
						//userdata.hpd_state = V4L2_EXT_HDMI_HPD_RESTART;
					}
					else if(status.numOfActivePort > 0)
					{
						userdata.hpd_state = gHDMI20EnableStatus[userdata.port];
						//userdata.hpd_state = V4L2_EXT_HDMI_HPD_ENABLE;
					}
					else{
						userdata.hpd_state = gHDMI20EnableStatus[userdata.port];
						//userdata.hpd_state = V4L2_EXT_HDMI_HPD_DISABLE;
					}

				}
				else{
					if(userdata.hpd_state == V4L2_EXT_HDMI_HPD_ENABLE){
						gHDMI20EnableStatus[userdata.port] = userdata.hpd_state;

						cmd.command = HDMI20_CMD_RX_SET_ENABLE_OPERATION;
						cmd.size = 1;
						HDMI20_Module_Process_Cmd(&cmd);
						ret = cmd.status;
					}
					else if(userdata.hpd_state == V4L2_EXT_HDMI_HPD_RESTART){
						gHDMI20EnableStatus[userdata.port] = userdata.hpd_state;

						ret = HDMI20_Module_Set_RestartHPD(userdata.port - 1);
					}
					else if(userdata.hpd_state == V4L2_EXT_HDMI_HPD_DISABLE){
						gHDMI20EnableStatus[userdata.port] = userdata.hpd_state;
						cmd.command = HDMI20_CMD_RX_SET_DISABLE_OPERATION;
						cmd.size = 0;
						HDMI20_Module_Process_Cmd(&cmd);
						ret = cmd.status;
					}
					else {
						ret = RET_INVALID_PARAMS;
					}
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hpd))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_HDCP_KEY:
			{
				struct v4l2_ext_hdmi_hdcp_key userdata;
				unsigned char *pData = NULL;
				int i, copy_pointer;
				UINT32 data0, data1;
				LX_HDMI20_HDCP14_DATA_T params; /* data struct for HDCP1.4 */
				int size = 0;

				printk(" %s:%s : Called! \n", __func__, ctrl_id_to_str(ctrl->id));

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hdcp_key)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hdcp_key));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_hdcp_key *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hdcp_key))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				/* Do not block by port size in this code!!! */

				/* Block if provided pointer is NULL */
				if(userdata.pData == NULL)
				{
					printk("[%s] : [%s] Error! userdata.pData is NULL!\n", __func__, ctrl_id_to_str(ctrl->id));

					ret = RET_INVALID_PARAMS;
					break;
				}

				/* Block by key type */
				if(userdata.version != V4L2_EXT_HDMI_HDCP_VERSION_14){
					if(userdata.version != V4L2_EXT_HDMI_HDCP_VERSION_22){
						printk("[%s] : [%s] Error! Unknown version [%d]!\n", __func__, ctrl_id_to_str(ctrl->id), userdata.version);
						ret = RET_INVALID_PARAMS;
						break;
					}
				}


				/* Allocate memory for key size */
				size = userdata.key_size;
				pData = (unsigned char *)kmalloc(size, GFP_KERNEL);
				if(pData == NULL){
					printk("[%s] : [%s] Error! MALLOC error!!\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_OUT_OF_MEMORY;
					break;
				}
				/* Clear allocated memory */
				memset((void *)pData, 0, size);

				/* Copy key from user space */
				if(copy_from_user((unsigned char *)pData, (void __user *)userdata.pData, size)){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				/* HDCP1.4 Case */
				if(userdata.version == V4L2_EXT_HDMI_HDCP_VERSION_14){
					memset(&params, 0, sizeof(LX_HDMI20_HDCP14_DATA_T));
					if(size != HDMI20_HDCP_CUSTOMER_SIZE)
					{
						kfree(pData);
						ret = RET_INVALID_PARAMS;
						break;
					}

					params.repeat = 0;
					params.seed = 0x0000a55a;

					/* Copy BKSV */
					memcpy((UINT32 *)&params.bksv, (UINT32 *)pData, (sizeof(UINT32) *2));

					/* Store BKSV : For later use */
					//memcpy((void *)&_gHDCP14_Written_BKSV_Value, (void *)&params.bksv, 5);

					/* For Repeater support */
					#if 1 
					if((_g_v4l2_hdmi20_hdcp_repeater_mode & 0x30) != 0){
						params.repeat = 1;
					}
					else{
						params.repeat = 0;
					}
					#endif

					/* Copy Key */
					copy_pointer = (sizeof(UINT32) * 2);
					for(i=0; i<HDMI20_HDCP_KEYS_SIZE; i=i+2){
						memcpy((void *)&data0, (void *)((uintptr_t)pData + (uintptr_t)copy_pointer), 4);
						copy_pointer += 4;
						memcpy((void *)&data1, (void *)((uintptr_t)pData + (uintptr_t)copy_pointer), 3); 
						copy_pointer += 3;

						data1 &= 0x00FFFFFF;

						params.keys[i]   = data0;
						params.keys[i+1] = data1;
					}
				
					/* Call API */
					ret = HDMI20_Module_Set_HDCP14((userdata.port -1), (UINT32 *)&params, sizeof(LX_HDMI20_HDCP14_DATA_T), 1);
					
				}
				else if(userdata.version == V4L2_EXT_HDMI_HDCP_VERSION_22){
					if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
						if(lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 6, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else if(lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 5, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else if(lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 4, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 3, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else if(lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 2, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else if(lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ){
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 1, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}
						else{
							ret  = HDMI21_HDCP23_Module_Set_Open(pData ,size, 0, gEsm_Dma_codebase, pEsm_codeVirtAddr, gEsm_Dma_database, pEsm_dataVirtAddr);
						}

						if(ret >= 0) {
							ret = HDMI21_HAL_Rx_Set_HDCP22Info((userdata.port -1), 1);
						}
						
					}
					else {
						/* Not implemented : Only after for O20 */
					}
				}

				/* Free allocated memory */
				kfree(pData);

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hdcp_key))){
					printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_DISCONNECT:
			{
				//ret = RET_OK;
				ret = 0;
			}
			break;
		case V4L2_CID_EXT_HDMI_VRR_FREQUENCY:
			{
				struct v4l2_ext_hdmi_vrr_frequency userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_vrr_frequency)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_vrr_frequency));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_vrr_frequency *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_vrr_frequency))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				userdata.frequency = HDMI20_Module_Get_VrrFrequency(userdata.port - 1);

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_vrr_frequency))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_EMP_INFO:
			{
				struct v4l2_ext_hdmi_emp_info userdata;
				LX_HDMI20_EMP_TYPE_T type;
				unsigned char cvtemData[HDMI21_MAX_CVTEM_LENGHT];

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_emp_info)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_emp_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_emp_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_emp_info))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(userdata.type == V4L2_EXT_HDMI_EMP_TYPE_VTEM) {
					userdata.total_packet_number = 1;
					type = LX_HDMI20_EMP_VTEM;
					ret = HDMI20_Module_Get_EMPInfo((userdata.port - 1), &userdata.data[0], type, 1);

				}
				else if(userdata.type == V4L2_EXT_HDMI_EMP_TYPE_CVTEM) {
					userdata.total_packet_number = 6;
					type = LX_HDMI20_EMP_CVTEM;

					memset((void *)&cvtemData[0], 0, sizeof(unsigned char) * HDMI21_MAX_CVTEM_LENGHT);
					ret = HDMI20_Module_Get_EMPInfo((userdata.port - 1), &cvtemData[0], type, 1);

					userdata.data[0] = 0x7F;
					if(userdata.current_packet_index == 0) {
						userdata.data[1] = 0x80;
						userdata.data[2] = 0x0;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[3], (sizeof(unsigned char) * 28)); /* From [3] for 28 -> Next=31 */
					}
					else if(userdata.current_packet_index == 1) {
						userdata.data[1] = 0x00;
						userdata.data[2] = 0x1;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[31], (sizeof(unsigned char) * 28)); /* From [31] for 28 -> Next=59 */
					}
					else if(userdata.current_packet_index == 2) {
						userdata.data[1] = 0x00;
						userdata.data[2] = 0x2;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[59], (sizeof(unsigned char) * 28)); /* From [59] for 28 -> Next=87 */
					}
					else if(userdata.current_packet_index == 3) {
						userdata.data[1] = 0x00;
						userdata.data[2] = 0x3;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[87], (sizeof(unsigned char) * 28)); /* From [87] for 28 -> Next=115 */
					}
					else if(userdata.current_packet_index == 4) {
						userdata.data[1] = 0x00;
						userdata.data[2] = 0x4;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[115], (sizeof(unsigned char) * 28)); /* From [115] for 28 -> Next=143 */
					}
					else {
						userdata.data[1] = 0x40;
						userdata.data[2] = 0x5;
						memcpy((unsigned char *)&userdata.data[3], &cvtemData[143], (sizeof(unsigned char) * 3)); /* From [143] for 3 -> Next=146 */
						memset((unsigned char *)&userdata.data[6], 0, (sizeof(unsigned char) * 25));
					}
				
				}
				else {
					userdata.total_packet_number = 0;
				}


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_emp_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS:
			{
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				struct v4l2_ext_hdmi_diagnostics_status userdata;
				HDMI21_RX_HDCP_HDCP14_INFO_T _h14Info; 
				HDMI21_SNPS_LINK_REG_0X584_T _r0;
				HDMI21_SNPS_LINK_REG_0X588_T _r1;
				HDMI21_SNPS_LINK_REG_0X58C_T _r2;
				HDMI21_SNPS_LINK_REG_0X590_T _r3;
				HDMI21_SNPS_LINK_REG_0X594_T _r4;
				HDMI21_SNPS_LINK_REG_0X598_T _r5;
				HDMI21_SNPS_LINK_REG_0X59C_T _r6;
				HDMI21_SNPS_LINK_REG_0X5A0_T _r7;
				LX_HDMI20_OP_STATUS_T _opStatus;
				UINT32 __data;
				int hdcpVer = 0;
				UINT32 __a = 0;
				UINT32 __Vfreq = 0;
				int __5Vlevel;

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
					__a = 0x4;
				}
				else {
					__a = 0;
				}

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_diagnostics_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_diagnostics_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_diagnostics_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_diagnostics_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}


				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					/* 2020/09/21 */
					HDMI21_HAL_Rx_Get_Check5VLevelInfo((userdata.port-1), &__5Vlevel, 1);

					/* Link Status */
					userdata.link_status.hpd = _p->isHPD;
					userdata.link_status.hdmi_5v = (unsigned char)(__5Vlevel?1:0); 
					userdata.link_status.rx_sense  = _p->isHPD;

					/* 2020/11/03 : There is no TMDS Clock on FRL Modes */
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G){
						__Vfreq = HDMI21_HAL_Rx_Get_CompensateDignosticsVfreq(_p->hwVideo.tmds_clk, _p->hwVideo.vtotal, _p->hwVideo.htotal, _p->hwVideo.interlaced, _p->hwVideo.video_format);
					}
					else {
						__Vfreq = 0;
					}

					if( __Vfreq == 0 ){
						__Vfreq = _p->hwVideo.vfreq * 100;
					}
					userdata.link_status.frame_rate_x100_hz = __Vfreq;

					if(_p->is5Vconnected == 0) {
						userdata.link_status.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_DVI;
					}
					else {
						if(_p->hwVideo.dvi ) userdata.link_status.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_DVI;
						else  userdata.link_status.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_HDMI;
					}

					userdata.link_status.video_width = _p->hwVideo.hactive;
					userdata.link_status.video_height = _p->hwVideo.vactive;
					if(_p->hwVideo.video_format == 0) userdata.link_status.color_space = V4L2_EXT_HDMI_AVI_CSC_RGB;
					else if(_p->hwVideo.video_format == 1) userdata.link_status.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR422;
					else if(_p->hwVideo.video_format == 2) userdata.link_status.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR444;
					else userdata.link_status.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR420;

					if(_p->hwVideo.deep_color_mode <= 4) userdata.link_status.color_depth = 8;
					else if(_p->hwVideo.deep_color_mode == 5)userdata.link_status.color_depth = 10;
					else if(_p->hwVideo.deep_color_mode == 6)userdata.link_status.color_depth = 12;
					else userdata.link_status.color_depth = 16;

					userdata.link_status.colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][5] & 0xC0)>>6);
					userdata.link_status.ext_colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x70)>>4);
					if(((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][1] & 0xFF) >= 4)){
						userdata.link_status.additional_colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][17] & 0xF0)>>4);					
					}else{
						userdata.link_status.additional_colorimetry = 0;					
					}
					userdata.link_status.hdr_type = (int)HDMI21_HAL_Rx_Get_HDR_Mode((userdata.port-1));

					switch(_p->audioInfo.audioType){
						case LX_HDMI_AUDIO_DVI:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_NOAUDIO;
							break;
						case LX_HDMI_AUDIO_PCM:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_PCM;
							break;
						case LX_HDMI_AUDIO_AC3:
						case LX_HDMI_AUDIO_UNKNOWN_AC3:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_AC3;
							break;
						case LX_HDMI_AUDIO_EAC3:
						case LX_HDMI_AUDIO_UNKNOWN_EAC3:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3;
							break;
						case LX_HDMI_AUDIO_EAC3_ATMOS:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3_ATMOS;
							break;
						case LX_HDMI_AUDIO_MAT:
						case LX_HDMI_AUDIO_UNKNOWN_MAT:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_MAT;
							break;
						case LX_HDMI_AUDIO_MAT_ATMOS:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_MAT_ATMOS;
							break;
						case LX_HDMI_AUDIO_TRUE_HD:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD;
							break;
						case LX_HDMI_AUDIO_TRUE_HD_ATMOS:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD_ATMOS;
							break;
						case LX_HDMI_AUDIO_AAC:
						case LX_HDMI_AUDIO_UNKNOWN_AAC:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_AAC;
							break;
						case LX_HDMI_AUDIO_MPEG:
						case LX_HDMI_AUDIO_UNKNOWN_MPEG:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_MPEG;
							break;
						case LX_HDMI_AUDIO_DTS:
						case LX_HDMI_AUDIO_UNKNOWN_DTS:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_DTS;
							break;
						case LX_HDMI_AUDIO_DTS_HD_MA:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_HD_MA;
							break;
						case LX_HDMI_AUDIO_DTS_EXPRESS:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_EXPRESS;
							break;
						case LX_HDMI_AUDIO_DTS_CD:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_CD;
							break;		
						default:
							userdata.link_status.audio_format = V4L2_EXT_HDMI_AUDIO_FORMAT_UNKNOWN;
							break;
						
					}
					//userdata.link_status.audio_format = _p->audioInfo.audioType;
					userdata.link_status.audio_sampling_freq = _p->audioInfo.samplingFreq;
					userdata.link_status.audio_channel_number = _p->audioInfo.countOfChannel;

					/* Phy Status */
					userdata.phy_status.lock_status = _p->isPhyLocked ;
					if(_p->phyInitiatedMode >=  2) { 
						userdata.phy_status.tmds_clk_khz = 0;
					}
					else{
						userdata.phy_status.tmds_clk_khz = (_p->phy_tmds_clk * 10);
					}

					if(_p->phyInitiatedMode >=  2) { 
						userdata.phy_status.link_type = V4L2_EXT_HDMI_LINK_TYPE_FRL; 
						if(_p->phyInitiatedMode >= 4) userdata.phy_status.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_4;
						else userdata.phy_status.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_3;
					}
					else { 
						userdata.phy_status.link_type = V4L2_EXT_HDMI_LINK_TYPE_TMDS; 
						userdata.phy_status.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_3;
					}

					if((_p->phyInitiatedMode ==  0)|| (_p->phyInitiatedMode ==  2)){
						userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_3G;
					}
					else if((_p->phyInitiatedMode == 1) || (_p->phyInitiatedMode == 3) || (_p->phyInitiatedMode == 4)) {
						userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_6G;
					}
					else if(_p->phyInitiatedMode == 5) userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_8G;
					else if(_p->phyInitiatedMode == 6) userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_10G;
					else if(_p->phyInitiatedMode == 7) userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_12G;
					else userdata.phy_status.link_rate = V4L2_EXT_HDMI_LINK_RATE_3G;

					userdata.phy_status.ctle_eq_min_range[0] = _p->phyDeltaMinus[0];
					userdata.phy_status.ctle_eq_min_range[1] = _p->phyDeltaMinus[1];
					userdata.phy_status.ctle_eq_min_range[2] = _p->phyDeltaMinus[2];
					userdata.phy_status.ctle_eq_min_range[3] = _p->phyDeltaMinus[3];

					userdata.phy_status.ctle_eq_max_range[0] = _p->phyDeltaPlus[0];
					userdata.phy_status.ctle_eq_max_range[1] = _p->phyDeltaPlus[1];
					userdata.phy_status.ctle_eq_max_range[2] = _p->phyDeltaPlus[2];
					userdata.phy_status.ctle_eq_max_range[3] = _p->phyDeltaPlus[3];

					userdata.phy_status.ctle_eq_result[0] = _p->phyTCSResult[0];
					userdata.phy_status.ctle_eq_result[1] = _p->phyTCSResult[1];
					userdata.phy_status.ctle_eq_result[2] = _p->phyTCSResult[2];
					userdata.phy_status.ctle_eq_result[3] = _p->phyTCSResult[3];

					userdata.phy_status.error[0] = _p->phyCEDError[0];
					userdata.phy_status.error[1] = _p->phyCEDError[1];
					userdata.phy_status.error[2] = _p->phyCEDError[2];
					userdata.phy_status.error[3] = _p->phyCEDError[3];

					/* Video Status */
					userdata.video_status.video_width_real = _p->hwVideo.hactive;
					userdata.video_status.video_htotal_real = _p->hwVideo.htotal;
					userdata.video_status.video_height_real = _p->hwVideo.vactive;
					userdata.video_status.video_vtotal_real = _p->hwVideo.vtotal;
					if(_p->hwVideo.video_format == 3) {
						userdata.video_status.pixel_clock_khz  = (_p->real_pixel_clk << 1);
					} else {
						userdata.video_status.pixel_clock_khz  = _p->real_pixel_clk;
					}
					
					//userdata.video_status.current_vrr_refresh_rate = HDMI20_Module_Get_VrrFrequency(userdata.video_status.port - 1);
					/* 2022/07/14 : Yi U Sun didnot add port info to video_status data structure.. */
					userdata.video_status.current_vrr_refresh_rate = HDMI20_Module_Get_VrrFrequency(userdata.port - 1);

					/* Audio Status */
					userdata.audio_status.ChannelStatusBits = _p->audioInfo.countOfChannel;
					userdata.audio_status.LayoutBitValue = _p->audioInfo.layout;
					userdata.audio_status.pcm_CTS = _p->audioInfo.acr_cts;
					userdata.audio_status.pcm_N = _p->audioInfo.acr_n;

					/* HDCP Status */
					hdcpVer = HDMI21_HAL_Rx_Get_HDCPStatus(userdata.port-1);
					HDMI21_HAL_Rx_Get_OperationStatus((userdata.port -1), &_opStatus);

/*
					printk("%s:2341 [%d] hdcpVer[%d] Steady[%d] DVI[%d] isHDCP22[%d] isHDCP14[%d] ->\n",\
							__func__, userdata.port, hdcpVer, _opStatus.isSteady,_p->hwVideo.dvi, _p->isHDCP22, _p->isHDCP14 );
*/

					if((hdcpVer >= 20) && (_opStatus.isSteady == true) && (_p->hwVideo.dvi == false) && (_p->isHDCP22 == true)) {
						userdata.hdcp_status.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_22;
						userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
						userdata.hdcp_status.encEn = 1;
					}
					else if((hdcpVer >= 10) &&  (_opStatus.isSteady == true) && (_p->hwVideo.dvi == false) && (_p->isHDCP14 == true)) {
						userdata.hdcp_status.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_14;
						userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
						userdata.hdcp_status.encEn = 1;
					}
					else {
						if(_p->isHDCP22 == true)  {
							userdata.hdcp_status.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_22;
							userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
							userdata.hdcp_status.encEn = 0;
						}
						else if(_p->isHDCP14 == true) {
							userdata.hdcp_status.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_14;
							userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
							userdata.hdcp_status.encEn = 0;
						}
						else {
							userdata.hdcp_status.hdcp_version =  V4L2_EXT_HDMI_HDCP_VERSION_RESERVED; /* There isn't indication for none */
							if(_p->isHPD > 0) {
								userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_UNAUTHENTICATED;
								userdata.hdcp_status.encEn = 0; 
							}
							else {
								userdata.hdcp_status.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_NO_TX_CONNECTED;
								userdata.hdcp_status.encEn = 0; 
							}
						}
					}

					userdata.hdcp_status.hdcp22_status.ake_init_count_since_5v = _p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATED_IRQ];
					userdata.hdcp_status.hdcp22_status.reauth_req_count_since_5v = _p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_FAIL_IRQ];
				
					HDMI21_HDCP_Rx_Get_HDCP14Info(_p, &_h14Info);
					memcpy((void *)&userdata.hdcp_status.hdcp14_status.An, &_h14Info.An, sizeof(unsigned char) * 8);
					memcpy((void *)&userdata.hdcp_status.hdcp14_status.Aksv, &_h14Info.Aksv, sizeof(unsigned char) * 5);
					memcpy((void *)&userdata.hdcp_status.hdcp14_status.Bksv, &_h14Info.Bksv, sizeof(unsigned char) * 5);
					memcpy((void *)&userdata.hdcp_status.hdcp14_status.Ri, &_h14Info.Ri, sizeof(unsigned char) * 2);
					userdata.hdcp_status.hdcp14_status.Bcaps = _h14Info.Bcaps;
					memcpy((void *)&userdata.hdcp_status.hdcp14_status.Bstatus, &_h14Info.Bstatus, sizeof(unsigned char) * 2);

					/* SCDC Status */
					__data = _p->link_read(0x584 + __a);	memcpy((void *)&_r0, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
					__data = _p->link_read(0x588 + __a);	memcpy((void *)&_r1, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X588_T));
					__data = _p->link_read(0x58C + __a);	memcpy((void *)&_r2, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
					__data = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));
					__data = _p->link_read(0x594 + __a);	memcpy((void *)&_r4, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X594_T));
					__data = _p->link_read(0x598 + __a);	memcpy((void *)&_r5, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X598_T));
					__data = _p->link_read(0x59C + __a);	memcpy((void *)&_r6, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X59C_T));
					__data = _p->link_read(0x5A0 + __a);	memcpy((void *)&_r7, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X5A0_T));

					userdata.scdc_status.source_version		= _r0.SCDC_SOURCEVERSION;
					userdata.scdc_status.sink_version		= 0x1;

					userdata.scdc_status.rsed_update 		= _r0.SCDC_RSED_UPDATE;
					userdata.scdc_status.flt_update			= _r0.SCDC_FLT_UPDATE;
					userdata.scdc_status.frl_start			= _r0.SCDC_FRL_START;
					userdata.scdc_status.source_test_update	= _r0.SCDC_SOURCE_TEST_UPDATE;
					userdata.scdc_status.rr_test			= _r0.SCDC_RRTEST;
					userdata.scdc_status.ced_update			= _r0.SCDC_CEDUPDATE;
					userdata.scdc_status.status_update		= _r0.SCDC_STATUSUPDATE;

					userdata.scdc_status.tmds_bit_clock_ratio	= _r1.SCDC_TMDSBITCLKRATIO;
					userdata.scdc_status.scrambling_enable		= _r1.SCDC_SCRAMB_EN;
					userdata.scdc_status.tmds_scrambler_status	= _r1.SCDC_SCRAMB_STATUS;

					userdata.scdc_status.flt_no_retrain			= _r2.SCDC_FLT_NO_RETRAIN;
					userdata.scdc_status.rr_enable				= _r2.SCDC_RRENABLE;
					userdata.scdc_status.ffe_levels				= _r2.SCDC_FFE_LEVELS;
					userdata.scdc_status.frl_rate				= _r2.SCDC_FRL_RATE;

					userdata.scdc_status.dsc_decode_fail		= 0;	/* Need to implement */
					userdata.scdc_status.flt_ready				= _r3.SCDC_FLT_READY;
					userdata.scdc_status.clk_detect				= _r3.SCDC_CLOCKDETECTED;
			
					userdata.scdc_status.lane0_ltp_request		= _r3.SCDC_FLT_LN0_LTP_REQ;
					userdata.scdc_status.lane1_ltp_request		= _r3.SCDC_FLT_LN1_LTP_REQ;
					userdata.scdc_status.lane2_ltp_request		= _r3.SCDC_FLT_LN2_LTP_REQ;
					userdata.scdc_status.lane3_ltp_request		= _r3.SCDC_FLT_LN3_LTP_REQ;

					if(_p->phyInitiatedMode >=  2) { 
						userdata.scdc_status.ch0_locked				= _r3.SCDC_LN0LOCKED;
						userdata.scdc_status.ch1_locked				= _r3.SCDC_LN1LOCKED;
						userdata.scdc_status.ch2_locked				= _r3.SCDC_LN2LOCKED;
						userdata.scdc_status.ch3_locked				= _r3.SCDC_LN3LOCKED;
						userdata.scdc_status.ch0_ced_valid			= _r5.SCDC_ERDET_LANE0_VALID;
						userdata.scdc_status.ch1_ced_valid			= _r6.SCDC_ERDET_LANE1_VALID;
						userdata.scdc_status.ch2_ced_valid			= _r6.SCDC_ERDET_LANE2_VALID;
						userdata.scdc_status.ch3_ced_valid			= _r7.SCDC_ERDET_LANE3_VALID;
						userdata.scdc_status.ch0_ced				= _r5.SCDC_ERDET_LANE0;
						userdata.scdc_status.ch1_ced				= _r6.SCDC_ERDET_LANE1;
						userdata.scdc_status.ch2_ced				= _r6.SCDC_ERDET_LANE2;
						userdata.scdc_status.ch3_ced				= _r7.SCDC_ERDET_LANE3;
					}
					else{
						userdata.scdc_status.ch0_locked				= _r3.SCDC_CH0LOCKED;
						userdata.scdc_status.ch1_locked				= _r3.SCDC_CH1LOCKED;
						userdata.scdc_status.ch2_locked				= _r3.SCDC_CH2LOCKED;
						userdata.scdc_status.ch3_locked				= 0;
						userdata.scdc_status.ch0_ced_valid			= _r4.SCDC_ERR_DET0_VALID;
						userdata.scdc_status.ch1_ced_valid			= _r4.SCDC_ERR_DET1_VALID;
						userdata.scdc_status.ch2_ced_valid			= _r5.SCDC_ERR_DET2_VALID;
						userdata.scdc_status.ch3_ced_valid			= 0;
						userdata.scdc_status.ch0_ced				= _r4.SCDC_ERR_DET0;
						userdata.scdc_status.ch1_ced				= _r4.SCDC_ERR_DET1;
						userdata.scdc_status.ch2_ced				= _r5.SCDC_ERR_DET2;
						userdata.scdc_status.ch3_ced				= 0;
					}
					
					userdata.scdc_status.rs_correction_valid	= _r7.SCDC_RSFEC_CERDET_VALID;
					userdata.scdc_status.rs_correcton_count		= _r7.SCDC_RSFEC_CERDET;
				}
				else{
					/* Only support from O20 */
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_diagnostics_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}

			}
			break;
		case V4L2_CID_EXT_HDMI_PHY_STATUS:
			{
				struct v4l2_ext_hdmi_phy_status userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_phy_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_phy_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_phy_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_phy_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					userdata.lock_status = _p->isPhyLocked ;
					if(_p->phyInitiatedMode >=  2) { 
						userdata.tmds_clk_khz = 0;
					}
					else{
						userdata.tmds_clk_khz = (_p->phy_tmds_clk * 10);
					}

					if(_p->phyInitiatedMode >=  2) { 
						userdata.link_type = V4L2_EXT_HDMI_LINK_TYPE_FRL; 
						if(_p->phyInitiatedMode >= 4) userdata.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_4;
						else userdata.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_3;
					}
					else { 
						userdata.link_type = V4L2_EXT_HDMI_LINK_TYPE_TMDS; 
						userdata.link_lane = V4L2_EXT_HDMI_LINK_LANE_NUMBER_3;
					}

					if((_p->phyInitiatedMode ==  0)|| (_p->phyInitiatedMode ==  2)){
						userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_3G;
					}
					else if((_p->phyInitiatedMode == 1) || (_p->phyInitiatedMode == 3) || (_p->phyInitiatedMode == 4)) {
						userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_6G;
					}
					else if(_p->phyInitiatedMode == 5) userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_8G;
					else if(_p->phyInitiatedMode == 6) userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_10G;
					else if(_p->phyInitiatedMode == 7) userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_12G;
					else userdata.link_rate = V4L2_EXT_HDMI_LINK_RATE_3G;

					userdata.ctle_eq_min_range[0] = _p->phyDeltaMinus[0];
					userdata.ctle_eq_min_range[1] = _p->phyDeltaMinus[1];
					userdata.ctle_eq_min_range[2] = _p->phyDeltaMinus[2];
					userdata.ctle_eq_min_range[3] = _p->phyDeltaMinus[3];

					userdata.ctle_eq_max_range[0] = _p->phyDeltaPlus[0];
					userdata.ctle_eq_max_range[1] = _p->phyDeltaPlus[1];
					userdata.ctle_eq_max_range[2] = _p->phyDeltaPlus[2];
					userdata.ctle_eq_max_range[3] = _p->phyDeltaPlus[3];

					userdata.ctle_eq_result[0] = _p->phyTCSResult[0];
					userdata.ctle_eq_result[1] = _p->phyTCSResult[1];
					userdata.ctle_eq_result[2] = _p->phyTCSResult[2];
					userdata.ctle_eq_result[3] = _p->phyTCSResult[3];

					userdata.error[0] = _p->phyCEDError[0];
					userdata.error[1] = _p->phyCEDError[1];
					userdata.error[2] = _p->phyCEDError[2];
					userdata.error[3] = _p->phyCEDError[3];
				}
				else{
					/* only support from O20 A0 */
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_phy_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_LINK_STATUS:
			{
				struct v4l2_ext_hdmi_link_status userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				int __5Vlevel;
				UINT32 __Vfreq = 0;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_link_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_link_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_link_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_link_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					/* 2020/09/21 */
					HDMI21_HAL_Rx_Get_Check5VLevelInfo((userdata.port-1), &__5Vlevel, 1);

					userdata.hpd = _p->isHPD;
					userdata.hdmi_5v = (unsigned char)(__5Vlevel?1:0);
					userdata.rx_sense  = _p->isHPD;

					/* 2020/11/03 : There is no TMDS Clock on FRL Modes */
					if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G){
						__Vfreq = HDMI21_HAL_Rx_Get_CompensateDignosticsVfreq(_p->hwVideo.tmds_clk, _p->hwVideo.vtotal, _p->hwVideo.htotal, _p->hwVideo.interlaced, _p->hwVideo.video_format);
					}
					else {
						__Vfreq = 0;
					}

					if( __Vfreq == 0 ){
						__Vfreq = _p->hwVideo.vfreq * 100;
					}
					userdata.frame_rate_x100_hz = __Vfreq;

					if(_p->is5Vconnected == 0) {
						userdata.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_DVI;
					}
					else{
						if(_p->hwVideo.dvi ) userdata.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_DVI;
						else  userdata.dvi_hdmi_mode = V4L2_EXT_HDMI_MODE_HDMI;
					}

					userdata.video_width = _p->hwVideo.hactive;
					userdata.video_height = _p->hwVideo.vactive;
					if(_p->hwVideo.video_format == 0) userdata.color_space = V4L2_EXT_HDMI_AVI_CSC_RGB;
					else if(_p->hwVideo.video_format == 1) userdata.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR422;
					else if(_p->hwVideo.video_format == 2) userdata.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR444;
					else userdata.color_space = V4L2_EXT_HDMI_AVI_CSC_YCBCR420;

					if(_p->hwVideo.deep_color_mode <= 4) userdata.color_depth = 8;
					else if(_p->hwVideo.deep_color_mode == 5)userdata.color_depth = 10;
					else if(_p->hwVideo.deep_color_mode == 6)userdata.color_depth = 12;
					else userdata.color_depth = 16;

					userdata.colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][5] & 0xC0)>>6);
					userdata.ext_colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][6] & 0x70)>>4);
					if(((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][1] & 0xFF) >= 4)){
						userdata.additional_colorimetry = ((_p->dataPacket[HDMI21_DISLAND_DATA__AVI][17] & 0xF0)>>4);
					}else{
						userdata.additional_colorimetry = 0;
					}
					userdata.hdr_type = (int)HDMI21_HAL_Rx_Get_HDR_Mode((userdata.port-1));

					userdata.audio_format = (int)_p->audioInfo.stream;
					userdata.audio_sampling_freq = _p->audioInfo.samplingFreq;
					userdata.audio_channel_number = _p->audioInfo.countOfChannel;
				}
				else {
					/* Only Support from O20 A0 */
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_link_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_VIDEO_STATUS:
			{
				struct v4l2_ext_hdmi_video_status userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_video_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_video_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_video_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_video_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];
					
					userdata.video_width_real = _p->hwVideo.hactive;
					userdata.video_htotal_real = _p->hwVideo.htotal;
					userdata.video_height_real = _p->hwVideo.vactive;
					userdata.video_vtotal_real = _p->hwVideo.vtotal;
					if(_p->hwVideo.video_format == 3) {
						userdata.pixel_clock_khz  = (_p->real_pixel_clk << 1);
					}
					else {
						userdata.pixel_clock_khz  = _p->real_pixel_clk;
					}

					userdata.current_vrr_refresh_rate = HDMI20_Module_Get_VrrFrequency(userdata.port - 1);


				}
				else {
					/* Only Support from O20 A0 */
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_video_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_AUDIO_STATUS:
			{
				struct v4l2_ext_hdmi_audio_status userdata;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_audio_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_audio_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_audio_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_audio_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_audio_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_HDCP_STATUS:
			{
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				struct v4l2_ext_hdmi_hdcp_status userdata;
				HDMI21_RX_HDCP_HDCP14_INFO_T _h14Info; 
				LX_HDMI20_OP_STATUS_T _opStatus;
				int hdcpVer = 0;
				

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hdcp_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hdcp_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_hdcp_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hdcp_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}


				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					hdcpVer = HDMI21_HAL_Rx_Get_HDCPStatus(userdata.port-1);
					HDMI21_HAL_Rx_Get_OperationStatus((userdata.port -1), &_opStatus);

/*
					printk("%s:2774 [%d] hdcpVer[%d] Steady[%d] DVI[%d] isHDCP22[%d] isHDCP14[%d] ->\n",\
							__func__, userdata.port, hdcpVer, _opStatus.isSteady,_p->hwVideo.dvi, _p->isHDCP22, _p->isHDCP14 );
*/

					if((hdcpVer >= 20) &&  (_opStatus.isSteady == true) && (_p->hwVideo.dvi == false) && (_p->isHDCP22 == true))			{
						userdata.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_22;
						userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
						userdata.encEn = 1;
					}
					else if((hdcpVer >= 10)	 &&  (_opStatus.isSteady == true) && (_p->hwVideo.dvi == false)&& (_p->isHDCP14 == true))  {
						userdata.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_14;
						userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
						userdata.encEn = 1;
					}
					else {
						if(_p->isHDCP22 == true) {
							userdata.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_22;
							userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
							userdata.encEn = 0;
						}
						else if(_p->isHDCP14 == true) {
							userdata.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_14;
							userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED;
							userdata.encEn = 0;
						}
						else {

							userdata.hdcp_version =  V4L2_EXT_HDMI_HDCP_VERSION_RESERVED;
							if(_p->isHPD > 0) {
								userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_UNAUTHENTICATED;
								userdata.encEn = 0; 
							}
							else {
								userdata.auth_status  = V4L2_EXT_HDMI_HDCP_AUTH_STATUS_NO_TX_CONNECTED;
								userdata.encEn = 0; 
							}
						}
					}

					userdata.hdcp22_status.ake_init_count_since_5v = _p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATED_IRQ];
					userdata.hdcp22_status.reauth_req_count_since_5v = _p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_FAIL_IRQ];
				
					HDMI21_HDCP_Rx_Get_HDCP14Info(_p, &_h14Info);
					memcpy((void *)&userdata.hdcp14_status.An, &_h14Info.An, sizeof(unsigned char) * 8);
					memcpy((void *)&userdata.hdcp14_status.Aksv, &_h14Info.Aksv, sizeof(unsigned char) * 5);
					memcpy((void *)&userdata.hdcp14_status.Bksv, &_h14Info.Bksv, sizeof(unsigned char) * 5);
					memcpy((void *)&userdata.hdcp14_status.Ri, &_h14Info.Ri, sizeof(unsigned char) * 2);
					userdata.hdcp14_status.Bcaps = _h14Info.Bcaps;
					memcpy((void *)&userdata.hdcp14_status.Bstatus, &_h14Info.Bstatus, sizeof(unsigned char) * 2);
				}
				else {
					/* Only Support from O20 A0 */
				}


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hdcp_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_SCDC_STATUS:
			{
				struct v4l2_ext_hdmi_scdc_status userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				HDMI21_SNPS_LINK_REG_0X584_T _r0;
				HDMI21_SNPS_LINK_REG_0X588_T _r1;
				HDMI21_SNPS_LINK_REG_0X58C_T _r2;
				HDMI21_SNPS_LINK_REG_0X590_T _r3;
				HDMI21_SNPS_LINK_REG_0X594_T _r4;
				HDMI21_SNPS_LINK_REG_0X598_T _r5;
				HDMI21_SNPS_LINK_REG_0X59C_T _r6;
				HDMI21_SNPS_LINK_REG_0X5A0_T _r7;
				UINT32 __data;
				UINT32 __a = 0;

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0) ) {
					__a = 0x4;
				}
				else {
					__a = 0;
				}

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_scdc_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_scdc_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_scdc_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_scdc_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					__data = _p->link_read(0x584 + __a);	memcpy((void *)&_r0, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
					__data = _p->link_read(0x588 + __a);	memcpy((void *)&_r1, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X588_T));
					__data = _p->link_read(0x58C + __a);	memcpy((void *)&_r2, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
					__data = _p->link_read(0x590 + __a);	memcpy((void *)&_r3, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X590_T));
					__data = _p->link_read(0x594 + __a);	memcpy((void *)&_r4, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X594_T));
					__data = _p->link_read(0x598 + __a);	memcpy((void *)&_r5, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X598_T));
					__data = _p->link_read(0x59C + __a);	memcpy((void *)&_r6, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X59C_T));
					__data = _p->link_read(0x5A0 + __a);	memcpy((void *)&_r7, &__data, sizeof(HDMI21_SNPS_LINK_REG_0X5A0_T));

					userdata.source_version		= _r0.SCDC_SOURCEVERSION;
					userdata.sink_version		= 0x1;

					userdata.rsed_update 		= _r0.SCDC_RSED_UPDATE;
					userdata.flt_update			= _r0.SCDC_FLT_UPDATE;
					userdata.frl_start			= _r0.SCDC_FRL_START;
					userdata.source_test_update	= _r0.SCDC_SOURCE_TEST_UPDATE;
					userdata.rr_test			= _r0.SCDC_RRTEST;
					userdata.ced_update			= _r0.SCDC_CEDUPDATE;
					userdata.status_update		= _r0.SCDC_STATUSUPDATE;

					userdata.tmds_bit_clock_ratio	= _r1.SCDC_TMDSBITCLKRATIO;
					userdata.scrambling_enable		= _r1.SCDC_SCRAMB_EN;
					userdata.tmds_scrambler_status	= _r1.SCDC_SCRAMB_STATUS;

					userdata.flt_no_retrain			= _r2.SCDC_FLT_NO_RETRAIN;
					userdata.rr_enable				= _r2.SCDC_RRENABLE;
					userdata.ffe_levels				= _r2.SCDC_FFE_LEVELS;
					userdata.frl_rate				= _r2.SCDC_FRL_RATE;

					userdata.dsc_decode_fail		= 0;	/* Need to implement */
					userdata.flt_ready				= _r3.SCDC_FLT_READY;
					userdata.clk_detect				= _r3.SCDC_CLOCKDETECTED;

					userdata.lane0_ltp_request		= _r3.SCDC_FLT_LN0_LTP_REQ;
					userdata.lane1_ltp_request		= _r3.SCDC_FLT_LN1_LTP_REQ;
					userdata.lane2_ltp_request		= _r3.SCDC_FLT_LN2_LTP_REQ;
					userdata.lane3_ltp_request		= _r3.SCDC_FLT_LN3_LTP_REQ;

					if(_p->phyInitiatedMode >=  2) { 
						userdata.ch0_locked				= _r3.SCDC_LN0LOCKED;
						userdata.ch1_locked				= _r3.SCDC_LN1LOCKED;
						userdata.ch2_locked				= _r3.SCDC_LN2LOCKED;
						userdata.ch3_locked				= _r3.SCDC_LN3LOCKED;
						userdata.ch0_ced_valid			= _r5.SCDC_ERDET_LANE0_VALID;
						userdata.ch1_ced_valid			= _r6.SCDC_ERDET_LANE1_VALID;
						userdata.ch2_ced_valid			= _r6.SCDC_ERDET_LANE2_VALID;
						userdata.ch3_ced_valid			= _r7.SCDC_ERDET_LANE3_VALID;
						userdata.ch0_ced				= _r5.SCDC_ERDET_LANE0;
						userdata.ch1_ced				= _r6.SCDC_ERDET_LANE1;
						userdata.ch2_ced				= _r6.SCDC_ERDET_LANE2;
						userdata.ch3_ced				= _r7.SCDC_ERDET_LANE3;
					}
					else{
						userdata.ch0_locked				= _r3.SCDC_CH0LOCKED;
						userdata.ch1_locked				= _r3.SCDC_CH1LOCKED;
						userdata.ch2_locked				= _r3.SCDC_CH2LOCKED;
						userdata.ch3_locked				= 0;
						userdata.ch0_ced_valid			= _r4.SCDC_ERR_DET0_VALID;
						userdata.ch1_ced_valid			= _r4.SCDC_ERR_DET1_VALID;
						userdata.ch2_ced_valid			= _r5.SCDC_ERR_DET2_VALID;
						userdata.ch3_ced_valid			= 0;
						userdata.ch0_ced				= _r4.SCDC_ERR_DET0;
						userdata.ch1_ced				= _r4.SCDC_ERR_DET1;
						userdata.ch2_ced				= _r5.SCDC_ERR_DET2;
						userdata.ch3_ced				= 0;
					}
					
					userdata.rs_correction_valid	= _r7.SCDC_RSFEC_CERDET_VALID;
					userdata.rs_correcton_count		= _r7.SCDC_RSFEC_CERDET;

				}
				else {
					/* Only Support from O20 A0 */
				}


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_scdc_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_ERROR_STATUS:
			{
				struct v4l2_ext_hdmi_error_status userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				UINT32 __error = 0;
				UINT32 __data = 0;
				int i;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_error_status)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_error_status));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_error_status *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_error_status))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}


				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){

					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					/* TMDS Error */
					__data = _p->phyTMDSError[0] + _p->phyTMDSError[1] + _p->phyTMDSError[2]+ _p->phyTMDSError[3];
					if(__data > 4) {
						if(gHDMI20TMDSErrorStamp[userdata.port-1] != _p->stableHist) {
							__error |= V4L2_EXT_HDMI_ERROR_TYPE_TMDS_ERROR;
							gHDMI20TMDSErrorStamp[userdata.port-1] = _p->stableHist;
						}
					}

					/* PHY LOW RANGE */
					if(_p->phyCurrentTMDSExceptionRange < 1){
						for(i=0;i<4;i++)
						{
							if(_p->phyDeltaMinus[i] + _p->phyDeltaPlus[i] <= 3) {
								if(gHDMI20RangeErrorStamp[userdata.port-1] != _p->stableHist) {
									__error |= V4L2_EXT_HDMI_ERROR_TYPE_PHY_LOW_RANGE;
									gHDMI20RangeErrorStamp[userdata.port-1] = _p->stableHist;
									break;
								}
							}
						}
					}

					/* CED Error */
					__data = _p->phyCEDError[0] + _p->phyCEDError[1] +  _p->phyCEDError[2] + _p->phyCEDError[3];
					if(__data > 4) {
						if(gHDMI20CEDErrorStamp[userdata.port-1] != _p->stableHist) {
							__error |= V4L2_EXT_HDMI_ERROR_TYPE_CED_ERROR;
							gHDMI20CEDErrorStamp[userdata.port-1] = _p->stableHist;
						}
					}

					/* update user data struct */
					userdata.error = __error;
				
					/* Use Filter Sel SWWA count for param 1*/
					userdata.param1 = _p->filterSelSwWaCnt;
				}
				else {
					/* Only Support from O20 A0 */
				}


				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_error_status))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
		case V4L2_CID_EXT_HDMI_EXPERT_SETTING:
			{
				struct v4l2_ext_hdmi_expert_setting userdata;
				LX_HDMI20_SETTING_FACTOR_T __set;

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_expert_setting)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_expert_setting));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_expert_setting *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_expert_setting))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				memset((void *)&__set, 0, sizeof(LX_HDMI20_SETTING_FACTOR_T));

				switch(userdata.type)
				{
					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_HPD_LOW_DURATION:
						{
							__set.type 	 = LX_HDMI20_SETTING_HPD_LOW_DURATION ;
							__set.value1 = userdata.param1 ;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_MODE:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_PORT0_MANUAL_EQ_MODE;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_PORT1_MANUAL_EQ_MODE;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_PORT2_MANUAL_EQ_MODE;
							else							 __set.type = LX_HDMI20_SETTING_PORT3_MANUAL_EQ_MODE;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH0:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH0;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH0;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH0;
							else							 __set.type = LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH0;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH1:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH1;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH1;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH1;
							else							 __set.type = LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH1;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH2:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH2;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH2;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH2;
							else							 __set.type = LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH2;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH3:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH3;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH3;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH3;
							else							 __set.type = LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH3;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_EQ_PERIOD:
						{
							__set.type 	 = LX_HDMI20_SETTING_TMDS_EQ_PERIOD;
							__set.value1 = userdata.param1 ;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_VIDEO_STABLE_COUNT:
						{
							__set.type   = LX_HDMI20_SETTING_VIDEO_STABLE_COUNT;
							__set.value1 = userdata.param1 ;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_AUDIO_STABLE_COUNT:
						{
							__set.type   = LX_HDMI20_SETTING_AUDIO_STABLE_COUNT;
							__set.value1 = userdata.param1 ;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_DISABLE_HDCP22:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_DISABLE_HDCP22_PORT0;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_DISABLE_HDCP22_PORT1;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_DISABLE_HDCP22_PORT2;
							else							 __set.type = LX_HDMI20_SETTING_DISABLE_HDCP22_PORT3;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_REAUTH_HDCP22:
						{
							if((userdata.port -1) == 0) 	 __set.type = LX_HDMI20_SETTING_REAUTH_HDCP22_PORT0;
							else if((userdata.port -1) == 1) __set.type = LX_HDMI20_SETTING_REAUTH_HDCP22_PORT1;
							else if((userdata.port -1) == 2) __set.type = LX_HDMI20_SETTING_REAUTH_HDCP22_PORT2;
							else							 __set.type = LX_HDMI20_SETTING_REAUTH_HDCP22_PORT3;
							__set.value1 = userdata.param1;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_ON_TO_RXSENSE_TIME:
						{
							__set.type   = LX_HDMI20_SETTING_ON_TO_RXSENSE_TIME;
							__set.value1 = userdata.param1 ;
						}
						break;

					case V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_RXSENSE_TO_HPD_TIME:
						{
							__set.type   = LX_HDMI20_SETTING_RXSENSE_TO_HPD_TIME;
							__set.value1 = userdata.param1 ;
						}
						break;

					default:
						{
							
						}
						break;
				}

				ret = HDMI21_HAL_Rx_Set_HDMIFactor(&__set, sizeof(LX_HDMI20_SETTING_FACTOR_T), 1);
			}
			break;
		#if 0
		case V4L2_CID_EXT_HDMI_DOLBY_CONTENT:
			{

			}break;
		#endif
		case V4L2_CID_EXT_HDMI_HDCP_REPEATER:
			{
				struct v4l2_ext_hdmi_hdcp_repeater userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;
				int __is_hdcp23_repeater = 0;

				/*
				struct v4l2_ext_hdmi_hdcp_repeater {
					enum v4l2_ext_hdmi_input_port port;
					unsigned char repeater_mode;
					unsigned char receiver_id[5];
					unsigned char repeater_hpd;
				};
				*/

				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hdcp_repeater)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hdcp_repeater));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_hdcp_repeater *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hdcp_repeater))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}
	
				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					printk("%s:%s : Port[%d] IsRepeater[0x%x] HPD[%d] RxID[0x%02x][0x%02x][0x%02x][0x%02x][0x%02x]\n",\
							__func__, ctrl_id_to_str(ctrl->id), userdata.port, userdata.repeater_mode, userdata.repeater_hpd,\
							userdata.receiver_id[0], userdata.receiver_id[1],userdata.receiver_id[2],userdata.receiver_id[3],\
							userdata.receiver_id[4]);

					/* SWWA for RxID */
					gHDMI21RepeaterRxID[0][0] = userdata.receiver_id[0];
					gHDMI21RepeaterRxID[0][1] = userdata.receiver_id[1];
					gHDMI21RepeaterRxID[0][2] = userdata.receiver_id[2];
					gHDMI21RepeaterRxID[0][3] = userdata.receiver_id[3];
					gHDMI21RepeaterRxID[0][4] = userdata.receiver_id[4];
					gHDMI21RepeaterCount = 1;
					gHDMI21RepeaterDepth = 0;

					/* Repeater Mode */
					_g_v4l2_hdmi20_hdcp_repeater_mode = userdata.repeater_mode;
					if((_g_v4l2_hdmi20_hdcp_repeater_mode & 0x03) != 0) { __is_hdcp23_repeater = 1;}

					/* Set HDCP2.3 Repeater Mode */
					HDMI21_HDCP23_Module_Set_IsRepeater(__is_hdcp23_repeater);

					HDMI21_HDCP23_Module_Set_RxId((unsigned char*)&userdata.receiver_id, 5, gHDMI21RepeaterCount, gHDMI21RepeaterDepth);

					if(userdata.repeater_hpd == 0) _p->repeaterHpd = 0;
					else _p->repeaterHpd = 1;
				}
				else {
					/* Only Support from O20 A0 */
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hdcp_repeater))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}

			}break;
		case V4L2_CID_EXT_HDMI_OVERRIDE_EOTF:
			{
				struct v4l2_ext_hdmi_override_drm_info userdata;
				HDMI21_HAL_RX_DEVICE_DATA *_p;


				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_override_drm_info)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_override_drm_info));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_override_drm_info *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_override_drm_info))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					printk("%s:%s : Port[%d] given value [%d] for EOTF override\n",\
							__func__, ctrl_id_to_str(ctrl->id), userdata.port, userdata.override_eotf);

					switch(userdata.override_eotf) 
					{
						case V4L2_EXT_HDMI_OVERRIDE_EOTF_SDR_LUMINANCE_RANGE:
							_p->hdrOverRide = 1; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_HDR_LUMINANCE_RANGE:
							_p->hdrOverRide = 2; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_SMPTE_ST_2084:
							_p->hdrOverRide = 3; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_HLG:
							_p->hdrOverRide = 4; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_4:
							_p->hdrOverRide = 5; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_5:
							_p->hdrOverRide = 6; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_6:
							_p->hdrOverRide = 7; /* value as in CTA-861 spec + 1 */

							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_7:
							_p->hdrOverRide = 8; /* value as in CTA-861 spec + 1 */
							break;

						case V4L2_EXT_HDMI_OVERRIDE_EOTF_AUTO:
							_p->hdrOverRide = 0; /* 0 means Auto */
							break;
						default :
							/* 2025/07/30 won.hur : Request from MS lab(AVTask-1544) */
							ret = RET_INVALID_PARAMS;
							break;
					}

					if(ret != RET_INVALID_PARAMS) {
						/* 2023/03/09 won.hur : From ID Department(SCDCRID-3402). Need testing.. */
						ret = HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(userdata.port-1);
					}

				}
				else {
					/* Only Support from O20 A0 */
				}

				if(ret == RET_INVALID_PARAMS) {
					printk("%s:%s : Error! Invalid param[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.override_eotf);
					break;
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_override_drm_info))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
			}
			break;
			
		case V4L2_CID_EXT_HDMI_QUERYCAP:
			{
				ret = __V4L2_HDMI20_Get_QueryCapability(ctrl);	
			}
			break;
		#if 0
		 case V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON:
		{
				struct v4l2_ext_hdmi_hpd_low_duration_dc_on userdata;
				volatile HDMI21_HAL_RX_DEVICE_DATA *_p;
			
				if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hpd_low_duration_dc_on)){
					printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hpd_low_duration_dc_on));
					ret = RET_INVALID_PARAMS;
					break;
				}

				if(copy_from_user((struct v4l2_ext_hdmi_hpd_low_duration_dc_on *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hpd_low_duration_dc_on))){
					printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret = RET_TRY_AGAIN;
					break;
				}

				if((userdata.port-1) >= fh->numOfPort){
					printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
					ret = RET_INVALID_PARAMS;
					break;
				}

				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) {
					// Get Handler 
					_p = &gHDMI21RxHandler[userdata.port-1];
					
					if(isGet){
						userdata.hpd_low_duration = gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value;	
					}
					else {
						if(userdata.hpd_low_duration <= 0)
						{
							gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value = 1;
						}
						else {
							gHDMI21RxDevVideoControler[HDMI21__VIDEO_HPD_LOW_DURATION_ON_BOOT].value = userdata.hpd_low_duration;
						}
					}
				}

				if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hpd_low_duration_dc_on))){
					//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
					ret =RET_TRY_AGAIN;
				}
				else {
					ret = 0;
				}
		}
		break;
		#endif
		 case V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY:
		{
			struct v4l2_ext_hdmi_hdcp_repeater_topology userdata;
			HDMI21_HAL_RX_DEVICE_DATA *_p;
			int i;
			int __is_hdcp23_repeater = 0;


			if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hdcp_repeater_topology)){
				printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_topology));
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(copy_from_user((struct v4l2_ext_hdmi_hdcp_repeater_topology *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_topology))){
				printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret = RET_TRY_AGAIN;
				break;
			}

			if((userdata.port-1) >= fh->numOfPort){
				printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(isGet) {
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					userdata.repeater_mode = (unsigned char)_g_v4l2_hdmi20_hdcp_repeater_mode;
					userdata.repeater_hpd = _p->repeaterHpd;
					userdata.count = gHDMI21RepeaterCount;
					userdata.depth = gHDMI21RepeaterDepth;
					userdata.msg_id = _g_v4l2_hdmi20_hdcp23_repeater_msgId;

					for(i=0;i<gHDMI21RepeaterCount;i++) {
						userdata.receiver_id[i][0] = gHDMI21RepeaterRxID[i][0];
						userdata.receiver_id[i][1] = gHDMI21RepeaterRxID[i][1];
						userdata.receiver_id[i][2] = gHDMI21RepeaterRxID[i][2];
						userdata.receiver_id[i][3] = gHDMI21RepeaterRxID[i][3];
						userdata.receiver_id[i][4] = gHDMI21RepeaterRxID[i][4];
					}
				}
				else{
					/* Only Support from O20 A0 */
				}
			}
			else {
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
					/* Get Handler */
					_p = &gHDMI21RxHandler[userdata.port-1];

					printk("%s:%s : Port[%d] RepeaterMode[%d] HPD[%d] MsgID[%d]/PreviousID[%d] \n",\
							__func__, ctrl_id_to_str(ctrl->id), userdata.port, userdata.repeater_mode, userdata.repeater_hpd, userdata.msg_id, _g_v4l2_hdmi20_hdcp23_repeater_msgId);

					/* Update Repeater HPD */
					if(userdata.repeater_hpd == 0) _p->repeaterHpd = 0;
					else _p->repeaterHpd = 1;

					if(userdata.msg_id <= 1) { /* Potenial issue code.. */
						_g_v4l2_hdmi20_hdcp_repeater_mode = userdata.repeater_mode;
						
						if((_g_v4l2_hdmi20_hdcp_repeater_mode & 0x03) != 0) { __is_hdcp23_repeater = 1;}
						HDMI21_HDCP23_Module_Set_IsRepeater(__is_hdcp23_repeater);
					}

					if(userdata.msg_id != _g_v4l2_hdmi20_hdcp23_repeater_msgId) {
						printk("%s:%s : NewTopology ID[%d](Previous[%d]). Update Topology.(Cnt[%d]/Depth[%d]\n",\
								__func__, ctrl_id_to_str(ctrl->id), userdata.msg_id, _g_v4l2_hdmi20_hdcp23_repeater_msgId,\
								userdata.count, userdata.depth);

						/* Update MSG ID variable */
						_g_v4l2_hdmi20_hdcp23_repeater_msgId = userdata.msg_id;

						if(userdata.count > 32) {
							printk("%s:%s : RxID count over Limit[%d](Max:32)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.count);
							ret = RET_INVALID_PARAMS;
							break;
						}

						gHDMI21RepeaterCount = userdata.count;
						gHDMI21RepeaterDepth = userdata.depth;

						for(i=0;i<userdata.count;i++) {
							/* SWWA for RxID */
							gHDMI21RepeaterRxID[i][0] = userdata.receiver_id[i][0];
							gHDMI21RepeaterRxID[i][1] = userdata.receiver_id[i][1];
							gHDMI21RepeaterRxID[i][2] = userdata.receiver_id[i][2];
							gHDMI21RepeaterRxID[i][3] = userdata.receiver_id[i][3];
							gHDMI21RepeaterRxID[i][4] = userdata.receiver_id[i][4];
						}

						HDMI21_HDCP23_Module_Set_RxId((unsigned char*)&userdata.receiver_id, (5 * gHDMI21RepeaterCount), gHDMI21RepeaterCount, gHDMI21RepeaterDepth);
					}

				}
				else {
					/* Only Support from O20 A0 */
				}
			}

			if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_topology))){
				//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret =RET_TRY_AGAIN;
			}
			else {
				ret = 0;
			}

		}break;
		 case V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE:
		{
			struct v4l2_ext_hdmi_hdcp_repeater_stream_manage userdata;
			HDMI21_HAL_RX_DEVICE_DATA *_p;
			LX_HDMI20_OP_STATUS_T status;
			int hdcpVer = 0;
//			int i;


			if(ctrl->size != sizeof(struct v4l2_ext_hdmi_hdcp_repeater_stream_manage)){
				printk(" %s:%s : Given Size[%d] is not [%lu]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_stream_manage));
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(copy_from_user((struct v4l2_ext_hdmi_hdcp_repeater_stream_manage *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_stream_manage))){
				printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret = RET_TRY_AGAIN;
				break;
			}

			if((userdata.port-1) >= fh->numOfPort){
				printk("%s:%s : Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.port);
				ret = RET_INVALID_PARAMS;
				break;
			}

			if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
				/* Get Handler */
				_p = &gHDMI21RxHandler[userdata.port-1];
			
				/* Check HDMI Status */
				ret = HDMI20_Module_Get_OperationStatus((userdata.port -1), &status);
				if(ret < 0){
					printk("%s:%s : Get Module Operation Status Error[%d]. Port[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), ret, userdata.port-1);
					ret = RET_INVALID_PARAMS;
					break;
				}

				/* Get HDCP status */
				hdcpVer = HDMI21_HAL_Rx_Get_HDCPStatus(userdata.port-1);

				if((status.isSteady == true) && (status.isRestartState == false) && (hdcpVer >= 20)){
					if(_p->hdcp23_csm > 0) {
						userdata.value = STREAM_MANAGE_TRANSMIT_DENY;
					}
					else {
						userdata.value = STREAM_MANAGE_TRANSMIT_ALLOW;
					}
				}
				else {
					userdata.value = STREAM_MANAGE_RESERVED;
				}

			}
			else {
				/* Only Support from O20 A0 */
			}

			if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_hdcp_repeater_stream_manage))){
				//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret =RET_TRY_AGAIN;
			}
			else {
				ret = 0;
			}

		}break;
		 
		 case V4L2_CID_EXT_HDMI_SLEEP:
		{
			struct  v4l2_ext_hdmi_sleep userdata;

			if(ctrl->size != sizeof(struct v4l2_ext_hdmi_sleep)){
				//printk(" %s:%s : Given Size[%d] is not [%d]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_connection_state));
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(copy_from_user((struct v4l2_ext_hdmi_sleep *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_sleep))){
				//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret = RET_TRY_AGAIN;
				break;
			}

			if((userdata.port-1) >= fh->numOfPort){
				//printk("%s:%s :Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id),userdata.port);
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(isGet) {
				if(HDMI21_HAL_Rx_Get_ZombieMode(userdata.port - 1) > 0) {
					userdata.mode = V4L2_EXT_HDMI_SLEEP_MODE;

				}
				else {
					userdata.mode = V4L2_EXT_HDMI_WAKEUP_MODE;
				}
			}
			else {
				if(userdata.mode == V4L2_EXT_HDMI_SLEEP_MODE) {
					HDMI21_HAL_Rx_Set_ZombieMode((userdata.port -1), 1);
				}
				else if(userdata.mode == V4L2_EXT_HDMI_WAKEUP_MODE) {
					/* Incase a recovery from sleep mode, we need to toggle HPD */
					if(HDMI21_HAL_Rx_Get_ZombieMode(userdata.port - 1) > 0) {
						printk("%s:%s : HDMI Port[%d] wake up from Zombie Mode. RestartHPD is toggled!\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port);

						HDMI20_Module_Set_RestartHPD(userdata.port - 1);
					}

					HDMI21_HAL_Rx_Set_ZombieMode((userdata.port -1), 0);			
				}
				else {
					/* 2025/07/30 won.hur : Request from MS lab(AVTask-1544) */
					printk("%s:%s : Error! Invalid param[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.mode);
					ret = RET_INVALID_PARAMS;
					break;
				}
			}

			if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_sleep))){
				//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret =RET_TRY_AGAIN;
			}
		}
		break;

		 case V4L2_CID_EXT_HDMI_DPMS:
		{
			struct  v4l2_ext_hdmi_dpms userdata;
			volatile UINT32 data, data2;

			if(ctrl->size != sizeof(struct v4l2_ext_hdmi_dpms)){
				//printk(" %s:%s : Given Size[%d] is not [%d]\n", __func__, ctrl_id_to_str(ctrl->id), ctrl->size, sizeof(struct v4l2_ext_hdmi_connection_state));
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(copy_from_user((struct v4l2_ext_hdmi_dpms *)&userdata, (void __user *)ctrl->string, sizeof(struct v4l2_ext_hdmi_dpms))){
				//printk("[%s] : [%s] copy from User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret = RET_TRY_AGAIN;
				break;
			}

			if((userdata.port-1) >= fh->numOfPort){
				//printk("%s:%s :Error! Port exceeded max port(%d)\n",  __func__, ctrl_id_to_str(ctrl->id),userdata.port);
				ret = RET_INVALID_PARAMS;
				break;
			}

			if(isGet) {
					if ( lx_chip( ) == LX_CHIP_O26){
					HDMI20_V4L2_REG_RD(0xCA3A4004, data); // CTOP_MIP_Adapter -> MIP_Adapter_DPM -> MIP_HDMI_DPM01 -> reg_phy_tx_det_disable

					if((userdata.port-1) == 0) 	{	
						data &= (0x02);	
					}	
					else if((userdata.port-1) == 1) {
						data &= (0x04);	
					}
					else if((userdata.port-1) == 2) {
						data &= (0x08);	
					}
					else if((userdata.port-1) == 3) {
						data &= (0x10);	
					}

					if(data != 0) {
						userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_DISABLE;
					}
					else {
						HDMI20_V4L2_REG_RD(0xCA3A4008, data2);
						data2 &= (~0xFFFFFFEF);

						if(data2){
							userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE_DATA_CLK;
						}else{
							userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE;
						}
					}
				}else if ( lx_chip( ) == LX_CHIP_O24){
					HDMI20_V4L2_REG_RD(0xC8864004, data); // CTOP_MIP_Adapter -> MIP_Adapter_DPM -> MIP_HDMI_DPM01 -> reg_phy_tx_det_disable

					if((userdata.port-1) == 0) 	{	
						data &= (0x02);	
					}	
					else if((userdata.port-1) == 1) {
						data &= (0x04);	
					}
					else if((userdata.port-1) == 2) {
						data &= (0x08);	
					}
					else if((userdata.port-1) == 3) {
						data &= (0x10);	
					}

					if(data != 0) {
						userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_DISABLE;
					}
					else {
						HDMI20_V4L2_REG_RD(0xC8864008, data2);
						data2 &= (~0xFFFFFFEF);

						if(data2){
							userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE_DATA_CLK;
						}else{
							userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE;
						}
					}
				}else if ( lx_chip( ) == LX_CHIP_O22){
					HDMI20_V4L2_REG_RD(0xCA432060, data);

					if((userdata.port-1) == 0) 	{	
						data &= (0x10);	
					}	
					else if((userdata.port-1) == 1) {
						data &= (0x20);	
					}
					else if((userdata.port-1) == 2) {
						data &= (0x40);	
					}
					else if((userdata.port-1) == 3) {
						data &= (0x80);	
					}

					if(data != 0) {
						userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_DISABLE;
					}
					else {
						userdata.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE;
					}
				}
			}
			else {
				/* Mail From kibeom624.kim@lge.com @ 2022/04/18 16:41:16 
				 * wr 0xCA433100 0x10000000 ;; IO mux enable [28]
				 *
				 * wr 0xCA432060 0x00010F0F ;; DPM enable, 채널별 enable은 [7:4]
				 */

				if(userdata.mode == V4L2_EXT_HDMI_DPMS_MODE_DISABLE) {
					if ( lx_chip( ) == LX_CHIP_O26){
						HDMI20_V4L2_REG_RD(0xCA3A4000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xCA3A4000, data);

						HDMI20_V4L2_REG_RD(0xCA3A4004, data);
						data &= (~0xFFFFFFE0);

						if((userdata.port-1) == 0) 		{	data |= (0x02);	}
						else if((userdata.port-1) == 1) {	data |= (0x04);	}
						else if((userdata.port-1) == 2) {	data |= (0x08);	}
						else if((userdata.port-1) == 3) {	data |= (0x10);	}

						HDMI20_V4L2_REG_WR(0xCA3A4004, data);

						//printk("%s:%s : HDMI Port[%d] DPM disable!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}else if ( lx_chip( ) == LX_CHIP_O24){
						HDMI20_V4L2_REG_RD(0xC8864000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xC8864000, data);

						HDMI20_V4L2_REG_RD(0xC8864004, data);
						data &= (~0xFFFFFFE0);

						if((userdata.port-1) == 0) 		{	data |= (0x02);	}
						else if((userdata.port-1) == 1) {	data |= (0x04);	}
						else if((userdata.port-1) == 2) {	data |= (0x08);	}
						else if((userdata.port-1) == 3) {	data |= (0x10);	}

						HDMI20_V4L2_REG_WR(0xC8864004, data);

						//HDMI20_V4L2_REG_RD(0xC8864008, data2);
						//data2 &= (~0xFFFFFFFF);
						//data2 |= ( 0x00001001);
						//HDMI20_V4L2_REG_WR(0xC8864008, data2);

						//printk("%s:%s : HDMI Port[%d] DPM disable!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}else if ( lx_chip( ) == LX_CHIP_O22){
						HDMI20_V4L2_REG_RD(0xCA433100, data);
						data &= (~0xF0000000);
						data |= ( 0x10000000);
						HDMI20_V4L2_REG_WR(0xCA433100, data);


						HDMI20_V4L2_REG_RD(0xCA432060, data);
						data &= (~0xFFFFFF0F);
						data |= ( 0x00010F0F);

						if((userdata.port-1) == 0) 		{	data |= (0x10);	}
						else if((userdata.port-1) == 1) {	data |= (0x20);	}
						else if((userdata.port-1) == 2) {	data |= (0x40);	}
						else if((userdata.port-1) == 3) {	data |= (0x80);	}

						HDMI20_V4L2_REG_WR(0xCA432060, data);
					}
				}
				else if(userdata.mode == V4L2_EXT_HDMI_DPMS_MODE_ENABLE) {
					if ( lx_chip( ) == LX_CHIP_O26){
						HDMI20_V4L2_REG_RD(0xCA3A4000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xCA3A4000, data);

						HDMI20_V4L2_REG_RD(0xCA3A4004, data);
						data &= (~0xFFFFFFE0);
						data |= ( 0x00000001);

						if((userdata.port-1) == 0) 		{	data &= (~0x02);	}
						else if((userdata.port-1) == 1) {	data &= (~0x04);	}
						else if((userdata.port-1) == 2) {	data &= (~0x08);	}
						else if((userdata.port-1) == 3) {	data &= (~0x10);	}

						HDMI20_V4L2_REG_WR(0xCA3A4004, data);

						HDMI20_V4L2_REG_RD(0xCA3A4008, data2);
						data2 &= (~0xFFFFFFFF);
						data2 |= ( 0x00001001);
						HDMI20_V4L2_REG_WR(0xCA3A4008, data2);
						//printk("%s:%s : HDMI Port[%d] DPM enable!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}else if ( lx_chip( ) == LX_CHIP_O24){
						HDMI20_V4L2_REG_RD(0xC8864000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xC8864000, data);

						HDMI20_V4L2_REG_RD(0xC8864004, data);
						data &= (~0xFFFFFFE0);
						data |= ( 0x00000001);

						if((userdata.port-1) == 0) 		{	data &= (~0x02);	}
						else if((userdata.port-1) == 1) {	data &= (~0x04);	}
						else if((userdata.port-1) == 2) {	data &= (~0x08);	}
						else if((userdata.port-1) == 3) {	data &= (~0x10);	}

						HDMI20_V4L2_REG_WR(0xC8864004, data);

						HDMI20_V4L2_REG_RD(0xC8864008, data2);
						data2 &= (~0xFFFFFFFF);
						data2 |= ( 0x00001001);
						HDMI20_V4L2_REG_WR(0xC8864008, data2);
						//printk("%s:%s : HDMI Port[%d] DPM enable!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}else if ( lx_chip( ) == LX_CHIP_O22){
						HDMI20_V4L2_REG_RD(0xCA433100, data);
						data &= (~0xF0000000);
						data |= ( 0x10000000);
						HDMI20_V4L2_REG_WR(0xCA433100, data);


						HDMI20_V4L2_REG_RD(0xCA432060, data);
						data &= (~0xFFFFFF0F);
						data |= ( 0x00010F0F);

						if((userdata.port-1) == 0) 		{	data &= (~0x10);	}
						else if((userdata.port-1) == 1) {	data &= (~0x20);	}
						else if((userdata.port-1) == 2) {	data &= (~0x40);	}
						else if((userdata.port-1) == 3) {	data &= (~0x80);	}

						HDMI20_V4L2_REG_WR(0xCA432060, data);
					}

				}
				else if(userdata.mode == V4L2_EXT_HDMI_DPMS_MODE_ENABLE_DATA_CLK) {
					if ( lx_chip( ) == LX_CHIP_O26){
						HDMI20_V4L2_REG_RD(0xCA3A4000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xCA3A4000, data);

						HDMI20_V4L2_REG_RD(0xCA3A4004, data);
						data &= (~0xFFFFFFE0);
						data |= ( 0x00000001);

						if((userdata.port-1) == 0) 		{	data &= (~0x02);	}
						else if((userdata.port-1) == 1) {	data &= (~0x04);	}
						else if((userdata.port-1) == 2) {	data &= (~0x08);	}
						else if((userdata.port-1) == 3) {	data &= (~0x10);	}

						HDMI20_V4L2_REG_WR(0xCA3A4004, data);

						HDMI20_V4L2_REG_RD(0xCA3A4008, data2);
						data2 &= (~0xFFFFFFFF);
						data2 |= ( 0x00001011);
						HDMI20_V4L2_REG_WR(0xCA3A4008, data2);
						//printk("%s:%s : HDMI Port[%d] DPM enable data+clk mode!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}else if ( lx_chip( ) == LX_CHIP_O24){
						HDMI20_V4L2_REG_RD(0xC8864000, data);
						data &= (~0xFFFFFFFF);
						data |= ( 0x0000000F);
						HDMI20_V4L2_REG_WR(0xC8864000, data);

						HDMI20_V4L2_REG_RD(0xC8864004, data);
						data &= (~0xFFFFFFE0);
						data |= ( 0x00000001);

						if((userdata.port-1) == 0) 		{	data &= (~0x02);	}
						else if((userdata.port-1) == 1) {	data &= (~0x04);	}
						else if((userdata.port-1) == 2) {	data &= (~0x08);	}
						else if((userdata.port-1) == 3) {	data &= (~0x10);	}

						HDMI20_V4L2_REG_WR(0xC8864004, data);

						HDMI20_V4L2_REG_RD(0xC8864008, data2);
						data2 &= (~0xFFFFFFFF);
						data2 |= ( 0x00001011);
						HDMI20_V4L2_REG_WR(0xC8864008, data2);
						//printk("%s:%s : HDMI Port[%d] DPM enable data+clk mode!(0x4004:0x%x, 0x4008:0x%x)\n", __func__, ctrl_id_to_str(ctrl->id), userdata.port, data, data2);
					}
				}
				else {
					/* 2025/07/30 won.hur : Request from MS lab(AVTask-1544) */
					printk("%s:%s : Error! Invalid param[%d]\n",  __func__, ctrl_id_to_str(ctrl->id), userdata.mode);
					ret = RET_INVALID_PARAMS;
					break;
				}

			}

			if(copy_to_user((void __user *)ctrl->string, (void *)&userdata, sizeof(struct v4l2_ext_hdmi_dpms))){
				//printk("[%s] : [%s] copy to User Error\n", __func__, ctrl_id_to_str(ctrl->id));
				ret =RET_TRY_AGAIN;
			}
		}
		break;



		 default:
		ret = RET_INVALID_IOCTL;
	}

	return ret;
}




//module_init(v4l2_hdmi20_device_init);
//module_exit(v4l2_hdmi20_device_exit);

//MODULE_DESCRIPTION("HDMI20 V4L2/VIDEO device");
//MODULE_LICENSE("GPL");
