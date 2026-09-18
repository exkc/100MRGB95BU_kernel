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
 *  @author		juhwan.park
 *  @version	1.0
 *  @date		2018-10-12
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define V4L2_VBE_USE_ID_SIGNAGE_CID

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
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

//#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
#include "v4l2_vbe.h"
#include "be_kapi.h"
#include "ovi_kapi.h"
#include "be_proc.h"
#include "be_top_hal.h"
#include "led_hal.h"
#include "pwm_hal.h"
#include "ovi_hal.h"
#include "frc_hal.h"
#include "be_dbg.h"
#include "vbe_cfg.h"
#include "vbe_dpc.h"
#include "vbe_event.h"
#ifdef INCLUDE_KDRV_PE
#include "pe_kapi.h"
#include "vpq_hwrap.h"
#endif
//#ifdef V4L2_VBE_USE_ID_SIGNAGE_CID
#ifdef INCLUDE_KDRV_DE
#include "vp_kwrap.h"
#include "de_kwrap.h"
#include "resource_mgr.h"
#endif
//#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#define USE_GPS_VBE_EVENT

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* V4L2_VIDEO_DEVICE_BACKEND = 40, see video_dev_no */
#define V4L2_VBE_MINOR_NUMBER  V4L2_EXT_DEV_NO_BACKEND
#define V4L2_GAMMA_LUT_SIZENUM 1024
#define V4L2_LGD_MPLUS_LUT_SIZENUM 928
#define V4L2_BOE_MPLUS_LUT_SIZENUM 256
#define NOT_OK -1

#define VBE_BACKUP_LOG_STR_SIZE	(64)
#define VBE_BACKUP_LOG_BUF_MAX	(50)
#define VBE_BACKUP_LOG_TYPE_PWM	(0)

/* 20221205, Get VBE APL(SICREQ-453) */
#ifndef V4L2_CID_EXT_VBE_GET_APL_FOR_TPC
#define V4L2_CID_EXT_VBE_GET_APL_FOR_TPC (V4L2_CID_EXT_VBE_BASE + 38)

struct v4l2_ext_vbe_panel_tpc_apl_info {
	union {
		unsigned int *tpcAplInfoTable;
		unsigned int compat_data_statustable;
		unsigned long long sizer_statustable;
	};
	unsigned int table_size;
};
#endif

/* 20230901, SetOledAplCtrlParam (SICREQ-550) */
#ifndef V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM
#define V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM (V4L2_CID_EXT_VBE_BASE + 41)

struct v4l2_ext_vbe_panel_apl_control_param_info {
	union {
		unsigned int *pParamTable;
		unsigned int compat_data_paramtable;
		unsigned long long sizer_paramtable;
		};
		unsigned int table_size;
};
#endif

/* 20240617, (SICREQ-847)(SICREQ-566)(AVTASK-1433) */
#ifndef V4L2_CID_EXT_VBE_DCLK_MODE
#define V4L2_CID_EXT_VBE_DCLK_MODE (V4L2_CID_EXT_VBE_BASE + 44)

enum v4l2_ext_vbe_dclk_mode {
	V4L2_EXT_VBE_DCLK_MODE_BASIC,  // DCLK when power on (ex: 74.25MHz for 120Hz module or 84.24MHz for 144Hz module)
	V4L2_EXT_VBE_DCLK_MODE_165HZ,  // DCLK for 165Hz output
	V4L2_EXT_VBE_DCLK_MODE_MAX
};
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/*
static volatile unsigned int *gMapped_address;

#define OVI_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define OVI_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\

*/

/* SCDCR-4006 */
#define VBE_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::vbe\n",\
			_level,"video",V4L2_VBE_MINOR_NUMBER,_g_v4l2_vbe_open_count,\
			current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

#define VBE_BACKUP_PWM_LOG(_fmt, args...)	\
	{\
		char _log_buf[VBE_BACKUP_LOG_STR_SIZE];\
		snprintf(_log_buf, VBE_BACKUP_LOG_STR_SIZE, _fmt, ##args);\
		_vbe_push_log_buf(VBE_BACKUP_LOG_TYPE_PWM,_log_buf);\
	}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vbe_backuplog {
	unsigned int sec;
	unsigned int msec;
	char str[VBE_BACKUP_LOG_STR_SIZE];	///< str
};

struct vbe_ctx {
	unsigned int year;
};

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
// static void __exit v4l2_vbe_device_exit(void);
static int v4l2_vbe_probe(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0)
static void v4l2_vbe_remove(struct platform_device *pdev);
#else
static int v4l2_vbe_remove(struct platform_device *pdev);
#endif
static int v4l2_vbe_resume(struct device *dev);
static int v4l2_vbe_suspend(struct device *dev);
static int v4l2_vbe_fh_open(struct file *flie);
static int v4l2_vbe_fh_release(struct file *flie);
static int v4l2_vbe_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_vbe_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_vbe_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl);
static int vbe_set_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_vbe_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int vbe_get_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_vbe_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int v4l2_vbe_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap);
static int v4l2_vbe_vidioc_s_input(struct file *file, void *__fh, unsigned int i);
static int v4l2_vbe_vidioc_g_input(struct file *file, void *__fh, unsigned int *i);
static int v4l2_vbe_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub);
static int v4l2_vbe_vidioc_unsubscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub);
static unsigned int v4l2_vbe_poll(struct file *file, poll_table *wait);
static int v4l2_vbe_register(void *arg);
static void vbe_disp_transpanelparams(struct v4l2_ext_vbe_panel_info *v4l2PanelInfo, LX_OVI_DISPLAY_INFO_T *lxDispInfo);
static int v4l2_vbe_runtime_resume(struct device *dev);
static int v4l2_vbe_runtime_suspend(struct device *dev);
static void _vbe_push_log_buf(int type, char *data);
static void vbe_obj_status(struct seq_file *m, void* data);
static void vbe_param_status(struct seq_file *m, void* data);

int v4l2_vbe_get_cid_mask(char* buffer);
int v4l2_vbe_set_cid_mask(int mask);
int v4l2_vbe_pm_runtime_help(char* buffer);
int v4l2_vbe_pm_runtime_test(char* command);
struct vbe_priv *new_vbe_priv(void);
int v4l2_vbe_dbg_get_pwm_duty(char* buffer);
int v4l2_vbe_dbg_set_pwm_duty(char* command);
int v4l2_vbe_dbg_obj_apl_help(char* buffer);
int v4l2_vbe_dbg_obj_apl_test(char* command);
int v4l2_vbe_dbg_dispout_help(char* buffer);
int v4l2_vbe_dbg_dispout_test(char* command);
void vbe_status(struct seq_file *m, void* data);
int vbe_vsync_notification(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device v4l2_vbe_dev;
static struct mutex v4l2_vbe_video_device_lock;
static LX_BE_PWM_PARAMS_T pwmParams;
static UINT32 gPwmSetParamIdxFlag = 0;
static UINT32 gPwmApplyParamIdxFlag = 0;
static BE_FRC_INFO_T gBeFrcInfo;
static struct vbe_backuplog *_gp_vbe_backuplog_buf = NULL;
static struct vbe_ctx _g_vbe_ctx;
static int _g_v4l2_vbe_open_count = 0;
static enum v4l2_ext_vbe_dclk_mode _g_v4l2_vbe_dclock = V4L2_EXT_VBE_DCLK_MODE_MAX;
static int _g_v4l2_vbe_displayoutput_5060hz = -1;
static struct v4l2_ext_vbe_output_timing _g_v4l2_vbe_output_timing = {.frameRate=-1,.hResolution=-1,.vResolution=-1};
static int g_v4l2_vbe_dbg_param = 0;
module_param_named(vbe_dbg, g_v4l2_vbe_dbg_param, int, 0644);
static uint _g_v4l2_vbe_cid_mask = 0x0;
module_param_named(vbe_cid_mask, _g_v4l2_vbe_cid_mask, uint, 0644);
static LX_BE_GET_GENLOCK_T gGenlock;
static LX_BE_LED_object_apl *_gp_object_apl = NULL;
static LX_BE_LED_object_apl_gain _g_object_apl_gain[] = {
	[0] = {.id=LX_BE_LED_OBJECT_DETECTION_ID_FACE},
	[1] = {.id=LX_BE_LED_OBJECT_DETECTION_ID_DEPTH},
	[2] = {.id=LX_BE_LED_OBJECT_DETECTION_ID_LIGHT},
	[3] = {.id=LX_BE_LED_OBJECT_DETECTION_ID_LOGO},
};

static struct platform_device v4l2_vbe_pdev = {
	.name = "v4l2_vbe",
	.id = -1,
};

static struct dev_pm_ops const vbe_pm_ops = {
        .resume = v4l2_vbe_resume,
        .suspend = v4l2_vbe_suspend,
        .runtime_resume = v4l2_vbe_runtime_resume,
        .runtime_suspend = v4l2_vbe_runtime_suspend,
};

static struct platform_driver v4l2_vbe_driver = {
	.probe      = v4l2_vbe_probe,
	.driver     = {
		.name   = "v4l2_vbe",
		.owner  = THIS_MODULE,
		.pm     = &vbe_pm_ops,
	},
	.remove		= v4l2_vbe_remove,
};

static struct v4l2_file_operations v4l2_vbe_fops = {
   .owner          = THIS_MODULE,
   .open           = v4l2_vbe_fh_open,
   .release        = v4l2_vbe_fh_release,
   .unlocked_ioctl = video_ioctl2,
// .read = vb2_fop_read,
// .mmap = vb2_fop_mmap,
   .poll = v4l2_vbe_poll,
};

static struct v4l2_ioctl_ops v4l2_vbe_ioctl_ops = {
   .vidioc_querycap          = v4l2_vbe_vidioc_querycap,
   .vidioc_s_ctrl            = v4l2_vbe_vidioc_s_ctrl,
   .vidioc_g_ctrl            = v4l2_vbe_vidioc_g_ctrl,
   .vidioc_s_ext_ctrls       = v4l2_vbe_vidioc_s_ext_ctrls,
   .vidioc_g_ext_ctrls       = v4l2_vbe_vidioc_g_ext_ctrls,
   .vidioc_s_input           = v4l2_vbe_vidioc_s_input,
   .vidioc_g_input           = v4l2_vbe_vidioc_g_input,
   .vidioc_log_status        = v4l2_ctrl_log_status,
   .vidioc_subscribe_event   = v4l2_vbe_vidioc_subscribe_event,
   .vidioc_unsubscribe_event = v4l2_vbe_vidioc_unsubscribe_event,
};

static struct video_device v4l2_vbe_video_dev = {
   .v4l2_dev  = &v4l2_vbe_dev,
   .fops      = &v4l2_vbe_fops,
   .ioctl_ops = &v4l2_vbe_ioctl_ops,
   .release   = video_device_release_empty,
   .lock      = &v4l2_vbe_video_device_lock,
   .vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
   .device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int v4l2_vbe_get_cid_mask(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "--------------------------------------------\n");
	len += sprintf( buffer+len, "curr mask = 0x%08x (%d) (y%d)\n", _g_v4l2_vbe_cid_mask, _g_v4l2_vbe_cid_mask, _g_vbe_ctx.year);
	len += sprintf( buffer+len, "--------------------------------------------\n");
	len += sprintf( buffer+len, "< usage >\n");
	len += sprintf( buffer+len, "see cat /proc/lg/be/cid_list\n");
	len += sprintf( buffer+len, "set bootopts lg1k.vbe_cid_mask=0x??\n");
	len += sprintf( buffer+len, "echo 0x?? > /proc/lg/be/cid_mask\n");
	len += sprintf( buffer+len, "cat /sys/module/lg1k/parameters/vbe_cid_mask\n");
	len += sprintf( buffer+len, "--------------------------------------------\n");
	return len;
}

int v4l2_vbe_set_cid_mask(int mask)
{
	_g_v4l2_vbe_cid_mask = mask;
	return 0;
}

int v4l2_vbe_device_init(void)
{
	BE_PRINT("vbe  %s\n", __func__);
	mutex_init(&v4l2_vbe_video_device_lock);
	platform_driver_register(&v4l2_vbe_driver);
	platform_device_register(&v4l2_vbe_pdev);

	//video_set_drvdata(&v4l2_vbe_video_dev, &vbe_pdev);
	v4l2_vbe_register(NULL);

	return 0;
}
#if 0
static void __exit v4l2_vbe_device_exit(void)
{
	BE_PRINT("vbe  %s\n", __func__);

	platform_device_unregister(&v4l2_vbe_pdev);
	platform_driver_unregister(&v4l2_vbe_driver);
}
#endif
#ifdef INCLUDE_KDRV_PQE_PM
static int v4l2_vbe_pqe_pm_cb(int action)
{
	BE_PRINT("(%d) start\n",action);

	#if 0
	PQE_PM_DEVICE_SUSPEND_PREPARE = 0,
	//fw stall
	PQE_PM_DEVICE_SUSPEND,
	//cg on
	PQE_PM_DEVICE_SUSPEND_COMPLETED,

	PQE_PM_DEVICE_RESUME_PREPARE,
	//cg off
	PQE_PM_DEVICE_RESUME,
	//fw restart
	PQE_PM_DEVICE_RESUME_COMPLETED,
	#endif

	if (action == PQE_PM_DEVICE_SUSPEND_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_SUSPEND) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_SUSPEND_COMPLETED) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME_COMPLETED) {
		//TODO:
	}

	BE_TOP_HAL_SetPmMode(action);
	OVI_HAL_SetPmMode(action);

	BE_PRINT("(%d) end\n",action);
	return 0;
}

static struct pqe_pm_config v4l2_vbe_pqe_pm_cfg = {
	.name = "v4l2_vbe",
	.opt = PQE_PM_OPT_NONE,
	.order = 40,
	.callback = v4l2_vbe_pqe_pm_cb,
};
#endif

static unsigned int v4l2_vbe_get_board_year(void)
{
	unsigned int year = 0;

#ifdef BUILD_FEATURE_y29_board
	year = 29;
#elif defined BUILD_FEATURE_y28_board
	year = 28;
#elif defined BUILD_FEATURE_y27_board
	year = 27;
#elif defined BUILD_FEATURE_y26_board
	year = 26;
#elif defined BUILD_FEATURE_y25_board
	year = 25;
#elif defined BUILD_FEATURE_y24_board
	year = 24;
#elif defined BUILD_FEATURE_y23_board
	year = 23;
#elif defined BUILD_FEATURE_y22_board
	year = 22;
#endif

	return year;
}

static int v4l2_vbe_probe(struct platform_device *pdev)
{
	struct vbe_dev *drv;

	BE_NOTI("start\n");

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (drv)
	{
		drv->pdev = &v4l2_vbe_pdev;
		drv->v4l2_dev = &v4l2_vbe_dev;
		drv->vdev = &v4l2_vbe_video_dev;
#ifdef INCLUDE_KDRV_PQE_PM
		drv->pqe_pm_cfg = &v4l2_vbe_pqe_pm_cfg;
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
#endif
		platform_set_drvdata(pdev, drv);
	}
	//else	return -ENOMEM;

	if (_gp_vbe_backuplog_buf == NULL)
	{
		_gp_vbe_backuplog_buf = (struct vbe_backuplog *)kzalloc((sizeof(struct vbe_backuplog)*VBE_BACKUP_LOG_BUF_MAX), GFP_KERNEL);
	}

	if ((lx_chip() >= LX_CHIP_O26) && (_gp_object_apl == NULL)) {
		_gp_object_apl = (LX_BE_LED_object_apl *)OS_Malloc(sizeof(LX_BE_LED_object_apl));
		if (_gp_object_apl == NULL) {
			BE_ERROR("kmalloc fail\n");
		}
	}

	_g_vbe_ctx.year = v4l2_vbe_get_board_year();
	BE_NOTI("end(y%d)\n",_g_vbe_ctx.year);
	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0)
static void v4l2_vbe_remove(struct platform_device *pdev)
#else
static int v4l2_vbe_remove(struct platform_device *pdev)
#endif
{
	struct vbe_dev *drv = platform_get_drvdata(pdev);

	BE_PRINT("start\n");

	if (_gp_object_apl) {
		OS_Free((void *)_gp_object_apl);
		_gp_object_apl = NULL;
	}

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_unregister(drv->pqe_pm_id);
#endif
		kfree(drv);
	}

	pm_runtime_disable(&pdev->dev);

	BE_PRINT("end\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0)
	return 0;
#endif
}

static int v4l2_vbe_resume(struct device *dev)
{
	BE_PRINT("%s\n", __func__);
    return 0;
}

static int v4l2_vbe_suspend(struct device *dev)
{
	BE_PRINT("%s\n", __func__);
    return 0;
}

static int v4l2_vbe_runtime_resume(struct device *dev)
{
	struct vbe_dev *drv = dev_get_drvdata(dev);

	BE_PRINT("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_resume(drv->pqe_pm_id);
#endif
	}

	VBE_PM_INFO("info","resume","ok");

	return 0;
}

static int v4l2_vbe_runtime_suspend(struct device *dev)
{
	struct vbe_dev *drv = dev_get_drvdata(dev);

	BE_PRINT("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_suspend(drv->pqe_pm_id);
#endif
	}

	VBE_PM_INFO("info","suspend","ok");

	return 0;
}

int v4l2_vbe_pm_runtime_help(char* buffer)
{
	int len = 0;
	struct vbe_dev *drv = platform_get_drvdata(&v4l2_vbe_pdev);

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "dev name : %s\n",v4l2_vbe_pdev.name);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- open_count : %d\n",_g_v4l2_vbe_open_count);
	len += sprintf( buffer+len, "- vdev node name : %s\n",video_device_node_name(&v4l2_vbe_video_dev));
#ifdef INCLUDE_KDRV_PQE_PM
	if (!drv)					len += sprintf( buffer+len, "drv null\n");
	else if (!drv->pqe_pm_cfg)	len += sprintf( buffer+len, "pqe_pm_cfg null\n");
	else						len += sprintf( buffer+len, "pqe_pm_name : %s, pqe_pm_id : %d\n",drv->pqe_pm_cfg->name,drv->pqe_pm_id);
#endif
	len += sprintf( buffer+len, "- usage_count : %d\n",atomic_read(&v4l2_vbe_pdev.dev.power.usage_count));
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo runtime_suspend > /proc/lg/be/pm_test\n");
	len += sprintf( buffer+len, "echo runtime_resume > /proc/lg/be/pm_test\n");
	len += sprintf( buffer+len, "- others\n");
	len += sprintf( buffer+len, "cat /sys/devices/platform/v4l2_vbe/power/runtime_status\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int v4l2_vbe_pm_runtime_test(char* command)
{
	int ret = 0;
	struct vbe_dev *drv = platform_get_drvdata(&v4l2_vbe_pdev);

	if (!strncasecmp(command, "pm_runtime_put", strlen("pm_runtime_put"))) {
		ret = pm_runtime_put(&v4l2_vbe_pdev.dev);
		BE_PRINT("pm_runtime_put : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get_sync", strlen("pm_runtime_get_sync"))) {
		ret = pm_runtime_get_sync(&v4l2_vbe_pdev.dev);
		BE_PRINT("pm_runtime_get_sync : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get", strlen("pm_runtime_get"))) {
		ret = pm_runtime_get(&v4l2_vbe_pdev.dev);
		BE_PRINT("pm_runtime_get : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_suspend", strlen("pm_runtime_suspend"))) {
		ret = pm_runtime_suspend(&v4l2_vbe_pdev.dev);
		BE_PRINT("pm_runtime_suspend : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_resume", strlen("pm_runtime_resume"))) {
		ret = pm_runtime_resume(&v4l2_vbe_pdev.dev);
		BE_PRINT("pm_runtime_resume : ret:%d\n",ret);
	}
#ifdef INCLUDE_KDRV_PQE_PM
	else if (!strncasecmp(command, "pqe_pm_register", strlen("pqe_pm_register"))) {
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
		BE_PRINT("pqe_pm_register : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_suspend", strlen("pqe_pm_request_suspend"))) {
		ret = pqe_pm_request_suspend(drv->pqe_pm_id);
		BE_PRINT("pqe_pm_request_suspend : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_resume", strlen("pqe_pm_request_resume"))) {
		ret = pqe_pm_request_resume(drv->pqe_pm_id);
		BE_PRINT("pqe_pm_request_resume : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_unregister", strlen("pqe_pm_unregister"))) {
		ret = pqe_pm_unregister(drv->pqe_pm_id);
		BE_PRINT("pqe_pm_unregister : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
#endif
	else if (!strncasecmp(command, "runtime_suspend", strlen("runtime_suspend"))) {
		while (atomic_read(&v4l2_vbe_pdev.dev.power.usage_count) > 0) {
			BE_PRINT("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_vbe_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_vbe_pdev.dev);
			//msleep(1);
		}
	}
	else if (!strncasecmp(command, "runtime_resume", strlen("runtime_resume"))) {
		while (atomic_read(&v4l2_vbe_pdev.dev.power.usage_count) <= 0) {
			BE_PRINT("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_vbe_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_vbe_pdev.dev);
			//msleep(1);
		}
	}
	else {
		printk("do nothing\n");
	}

	return ret;
}

struct vbe_priv *new_vbe_priv(void)
{
	struct vbe_priv *p;

	p = kzalloc(sizeof(struct vbe_priv), GFP_KERNEL);
	if(!p)
	{
		BE_ERROR("alloc error for vbe priv.");
		return NULL;
	}
	INIT_LIST_HEAD(&p->list);
	init_waitqueue_head(&p->poll_wq);

	return p;
}

static int v4l2_vbe_fh_open(struct file *flie)
{
	int ret=0;
	int ret0=0;
	struct vbe_priv *priv;
	struct vbe_fh *fh;
	struct vbe_dev *drv = video_drvdata(flie);

	BE_NOTI("vbe: open (%s-%s)\n",current->group_leader->comm,current->comm);

	ret0 = pm_runtime_get_sync(&drv->pdev->dev);
	BE_NOTI("%s : ret0:%d, usage_count:%d\n",(drv->pdev->name)? (drv->pdev->name):"na",ret0,atomic_read(&drv->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct vbe_fh), GFP_KERNEL);
	if (!fh)
	{
		BE_ERROR("vbe: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	priv = new_vbe_priv();
	if(!priv)
	{
		BE_ERROR("alloc of vbe priv failed");
		ret = -ENOMEM;
		goto fail_fh;
	}

	priv->vdev = video_devdata(flie);
	fh->vbe_priv = priv;
	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* increment open counter */
	_g_v4l2_vbe_open_count++;
	VBE_PM_INFO("info","open","ok");

	return ret;

fail_fh:
	kfree(fh);
	return ret;

}

static int v4l2_vbe_fh_release(struct file *flie)
{
	int ret=0;
	int ret0=0;
	struct vbe_dev *drv = video_drvdata(flie);
	struct vbe_fh *fh = flie->private_data;

	BE_NOTI("vbe: close (%s-%s)\n",current->group_leader->comm,current->comm);

	if (fh && fh->vbe_priv) {
		vbe_led_release(flie);
		kfree(fh->vbe_priv);
		fh->vbe_priv = NULL;
	}

	v4l2_fh_release(flie);

	ret0 = pm_runtime_put(&drv->pdev->dev);
	BE_NOTI("%s : ret0:%d, usage_count:%d\n",(drv->pdev->name)? (drv->pdev->name):"na",ret0,atomic_read(&drv->pdev->dev.power.usage_count));

	/* decrement open counter */
	_g_v4l2_vbe_open_count--;
	VBE_PM_INFO("info","close","ok");

	return ret;
}

static unsigned int vbe_is_support(unsigned int ctrl_id)
{
	if (ctrl_id == V4L2_CID_EXT_VBE_DCLK_MODE) {
		return (lx_chip() >= LX_CHIP_O24 && _g_vbe_ctx.year >= 25)? 1:0;
	}
	return 2;
}

static int _vbe_V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ(int ctrl_value)
{
	int ret = 0;
	LX_OVI_DISP_OUTPUT_MODE_T param;
	LX_BE_DISP_MODE_T stParams;

	do {
		param = ctrl_value ? LX_OVI_DISP_OUTPUT_MODE_4K60 : LX_OVI_DISP_OUTPUT_MODE_4K120;
		BE_NOTI("%d param:%d\n",ctrl_value,param);
		ret = OVI_HAL_SetDispOutputMode(param);
		if (ret)
		{
			BE_ERROR("OVI_HAL_SetDispOutputMode error(%d)\n",ret);
			break;
		}

		stParams.dispResolution = LX_BE_DISP_RESOLUTION_3840;
		stParams.dispFrameRate = ctrl_value ? LX_BE_DISP_FRAME_RATE_60 : LX_BE_DISP_FRAME_RATE_120;
		BE_NOTI("%d Resolution,FrameRate:%d,%d\n",ctrl_value,stParams.dispResolution,stParams.dispFrameRate);
		ret = BE_TOP_HAL_SetDispMode(&stParams);
		if (ret)
		{
			BE_ERROR("BE_TOP_HAL_SetDispMode error(%d)\n",ret);
			break;
		}
		BE_NOTI("done\n");
	} while (0);

	return ret;
}

static int v4l2_vbe_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	//struct vbe_fh *fh = __fh;

	if (_g_v4l2_vbe_cid_mask == ctrl->id)
	{
		BE_TRACE("cid_mask(%s) skip\n",vbe_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	if (!(ctrl->id == V4L2_CID_EXT_VBE_PWM_INIT))
		BE_PRINT("vbe:id 0x%x (%s), value %d\n", ctrl->id, vbe_ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_VBE_DISPLAYOUTPUT:
		{
			BOOLEAN param;
			param = (ctrl->value ? TRUE : FALSE);
			ret = OVI_HAL_SetChannelPower(param);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetChannelPower error(%d)\n",ret);
				break;
			}

		}break;
		case V4L2_CID_EXT_VBE_PCCE:
		{
			LX_BE_IPC_PCCE_T param = { .d0.udata32 = 0 };
			param.d0.enable = (ctrl->value == 1);
			BE_NOTI("V4L2_CID_EXT_VBE_PCCE on/off: %d\n", param.d0.enable);
			// printk("[MHLEE] %s(), call BE_TOP_HAL_SetPcce(%d)\n", __func__, param.d0.enable);
			ret = BE_TOP_HAL_SetPcce(&param);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetPcce error(%d)\n", ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_MUTE:
		{
			BOOLEAN param;
			LX_OVI_TCON_PATTERN_GEN_T stTPGParams;

			stTPGParams.bUseInternalSync = FALSE;	
			param = (ctrl->value ? TRUE : FALSE);

			ret = OVI_HAL_SetLvdsBlack(param);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetLvdsBlack error(%d)\n",ret);
				break;
			}

			if(param)
			{
				stTPGParams.eMode = LX_OVI_TCON_TPG_BLACK;
				ret = OVI_HAL_SetPatternGenerator(&stTPGParams);
			}
			else
			{
				stTPGParams.eMode = LX_OVI_TCON_TPG_OFF;
				ret = OVI_HAL_SetPatternGenerator(&stTPGParams);
			}

			if (ret)
			{
				BE_ERROR("OVI_HAL_SetPatternGenerator error(%d)\n",ret);
				break;
			}

		}break;
		case V4L2_CID_EXT_VBE_MPLUS_BOEBYPASS:
		{
			LX_OVI_TCON_BYPASS_T stParams;
			stParams.bEnable = (ctrl->value ? TRUE : FALSE);
			stParams.u32BlockMask = LX_OVI_TCON_BOE_RGBW;

			ret = OVI_HAL_SetBypass(&stParams);

			if (ret)
			{
				BE_ERROR("OVI_HAL_SetBypass error(%d)\n",ret);
				break;
			}
			
		}break;
		case V4L2_CID_EXT_VBE_EPI_SCRAMBLE:
		{
			BOOLEAN param;
			param = (ctrl->value ? TRUE : FALSE);
			ret = OVI_HAL_SetEpiDataScramble(param);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetEpiDataScramble error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_EPI_10BIT:
		{
			BOOLEAN param;
			param = (ctrl->value ? TRUE : FALSE);
			ret = OVI_HAL_SetAdvanced10bit(param);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetAdvanced10bit error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_PWM_INIT:
		{
			UINT32 param;
			param = (UINT32)ctrl->value;
			ret = BE_TOP_HAL_SetFRCStatus(param);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetFRCStatus error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_CPC:
		{
			UINT32 param;
			param = (UINT32)ctrl->value;
			ret = BE_TOP_HAL_SetCPC(param);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetCPC error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_VAC_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VAC_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ:
		{
			_g_v4l2_vbe_displayoutput_5060hz = (int)ctrl->value;
			ret = _vbe_V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ(ctrl->value);
		}break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_vbe_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	//struct vbe_fh *fh = __fh;

	if (_g_v4l2_vbe_cid_mask == ctrl->id)
	{
		BE_TRACE("cid_mask(%s) skip\n",vbe_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VBE_GSR_STATUS:
		{
			BOOLEAN status;

			ret = BE_TOP_HAL_GetGSRStatus(&status);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_GetGSRStatus error(%d)\n",ret);
				break;
			}

			if (status == TRUE)
				ctrl->value = 1;
			else
				ctrl->value = 0;

		}break;
		case V4L2_CID_EXT_VBE_LOCK_STATUS:
		{
			BOOLEAN status;

			ret = OVI_HAL_GetLockStatus(&status);
			if (ret)
			{
				BE_ERROR("OVI_HAL_GetLockStatus error(%d)\n",ret);
				break;
			}

			if (status == TRUE)
				ctrl->value = 1;
			else
				ctrl->value = 0;
		}break;
		case V4L2_CID_EXT_VBE_GSR_STRESS_COUNT:
		{
			UINT32 gsrCnt;

			ret = BE_TOP_HAL_GetGSRStressCount(&gsrCnt);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_GetGSRStressCount error(%d)\n",ret);
				break;
			}

			ctrl->value = gsrCnt;

		}break;
		case V4L2_CID_EXT_VBE_IRR_RESULT:
		{
			UINT32 irrRes;

			ret = BE_TOP_HAL_GetIrrResult(&irrRes);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_GetIrrResult error(%d)\n",ret);
				break;
			}

			ctrl->value = irrRes;

		}break;
		default:
			return -EINVAL;
	}

	BE_PRINT("vbe:id 0x%x (%s), value %d\n", ctrl->id, vbe_ctrl_id_to_str(ctrl->id), ctrl->value);

	return ret;
}

static int v4l2_vbe_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl)
{
	int ret = 0;
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36)
	#ifdef CONFIG_COMPAT
	switch (ctrl->id) {
		case V4L2_CID_EXT_VBE_DGA4CH:
		{
			struct v4l2_ext_vbe_dga4ch arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_dga4ch)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pBlueGammaTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_blue;
			arg_buf.pGreenGammaTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_green;
			arg_buf.pRedGammaTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_red;
			arg_buf.pWhiteGammaTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_white;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_dga4ch)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_TSCIC:
		{
			struct v4l2_ext_vbe_panel_tscic arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tscic)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.u8pControlTbl = (unsigned char *)(uintptr_t)arg_buf.compat_data_ctrl;
			arg_buf.u32pTSCICTbl = (unsigned int *)(uintptr_t)arg_buf.compat_data_tscic;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_tscic)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_MPLUS_DATA:
		{
			struct v4l2_ext_vbe_mplus_data arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_mplus_data)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pRegisterSet = (void *)(uintptr_t)arg_buf.compat_data;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_mplus_data)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_VCOM_PAT_DRAW:
		{
			struct v4l2_ext_vbe_vcom_pat_draw arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_vcom_pat_draw)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.vcomPattern = (unsigned short *)(uintptr_t)arg_buf.compat_data;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_vcom_pat_draw)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_PWM_PARAM:
		{
			struct v4l2_ext_vbe_pwm_param arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_pwm_param)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pstPWMParam = (struct v4l2_ext_vbe_pwm_param_data *)(uintptr_t)arg_buf.compat_data;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_pwm_param)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_LSR:
		{
			struct v4l2_ext_vbe_panel_lsr_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_lsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pLsrTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_lsrtable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_lsr_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_GSR:
		{
			struct v4l2_ext_vbe_panel_gsr_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_gsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pGsrTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_gsrtable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_gsr_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_GSR2:
		{
			struct v4l2_ext_vbe_panel_second_gsr_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_second_gsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pGsrTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_gsrtable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_second_gsr_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_OSD_GAIN:
		{
			struct v4l2_ext_vbe_panel_osd_gain_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_osd_gain_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.levelval = (unsigned int *)(uintptr_t)arg_buf.compat_data_levelval;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_osd_gain_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_ALPHA_OSD:
		{
			struct v4l2_ext_vbe_panel_alpha_osd_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_alpha_osd_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.alphaTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_alphatable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_alpha_osd_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM:
		{
			struct v4l2_ext_vbe_panel_irr_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_irr_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pIrrlum = (unsigned int *)(uintptr_t)arg_buf.compat_data_irr;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_irr_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM:
		{
			struct v4l2_ext_vbe_panel_tpc_recovery_param_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_param_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pParamTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_paramtable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_param_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS:
		{
			struct v4l2_ext_vbe_panel_tpc_recovery_status_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.tpcStatusTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_statustable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_DEMURA:
		{
			struct v4l2_ext_vbe_panel_demura arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_demura)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.config = (unsigned char *)(uintptr_t)arg_buf.compat_data_ctrl;
			arg_buf.data = (unsigned char *)(uintptr_t)arg_buf.compat_data_demura;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_demura)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_PCLRC:
		{
			struct v4l2_ext_vbe_panel_pclrc arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_pclrc)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.data = (unsigned char *)(uintptr_t)arg_buf.compat_data_pclrc;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_pclrc)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_GET_APL_FOR_TPC:
		{
			struct v4l2_ext_vbe_panel_tpc_apl_info arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info)))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.tpcAplInfoTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_statustable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info)))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM:
		{
			struct v4l2_ext_vbe_panel_apl_control_param_info  arg_buf;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info )))
			{
				BE_ERROR("copy_from_user error\n");
			}

			arg_buf.pParamTable = (unsigned int *)(uintptr_t)arg_buf.compat_data_paramtable;

			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info )))
			{
				BE_ERROR("copy_to_user error\n");
			}
		}break;
		case V4L2_CID_EXT_VBE_OUTPUT_TIMING:
		{
			struct v4l2_ext_vbe_output_settingdata arg_buf;

			if (copy_from_user(&arg_buf, (void __user *)ctrl->ptr,sizeof(struct v4l2_ext_vbe_output_settingdata)))
			{
				BE_ERROR("copy_from_user error for V4L2_CID_EXT_VBE_OUTPUT_TIMING\n");
			}

			// if (!arg_buf.compat_data_timingParam || !arg_buf.compat_data_extraInfo)
			// {
			// 	BE_ERROR("Invalid compat data pointers for V4L2_CID_EXT_VBE_OUTPUT_TIMING\n");
			// }
			arg_buf.pTimingParam = (struct v4l2_ext_vbe_output_timing *)(uintptr_t)arg_buf.compat_data_timingParam;
			arg_buf.extraInfo = (void *)(uintptr_t)arg_buf.compat_data_extraInfo;

			if (copy_to_user((void __user *)ctrl->ptr, &arg_buf,sizeof(struct v4l2_ext_vbe_output_settingdata)))
			{
				BE_ERROR("copy_to_user error for V4L2_CID_EXT_VBE_OUTPUT_TIMING\n");
				return -EFAULT;
			}
		}
		break;

		default:
			break;
	}
	#endif
	#endif
	return ret;
}

static void vbe_disp_transpanelparams(struct v4l2_ext_vbe_panel_info *v4l2PanelInfo, LX_OVI_DISPLAY_INFO_T *lxDispInfo)
{
	struct v4l2_ext_vbe_panel_info stV4l2PanelInfo;
	LX_OVI_DISPLAY_INFO_T stLxDispInfo;

	memcpy((void *)&stV4l2PanelInfo, (void *)v4l2PanelInfo, sizeof(struct v4l2_ext_vbe_panel_info));

	switch(stV4l2PanelInfo.panelInterface)
	{
		case V4L2_EXT_VBE_PANEL_LVDS:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_LVDS;
			break;
		case V4L2_EXT_VBE_PANEL_EPI:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_EPI;
			break;
		case V4L2_EXT_VBE_PANEL_EPI_QSAC:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_EPI_QSAC;
			break;
		case V4L2_EXT_VBE_PANEL_Vx1:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_VX1;
			break;
		case V4L2_EXT_VBE_PANEL_CEDS:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_CEDS;
			break;
		default:
			stLxDispInfo.panelInterface = LX_OVI_PANEL_INTERFACE_MAX;
	}

	switch(stV4l2PanelInfo.panelResolution)
	{
		case V4L2_EXT_VBE_PANEL_RESOLUTION_1024X768:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_1024X768;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_1280X720:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_1366X768:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_1920X1080:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_2560X1080:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_2560X1080;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_3840X2160:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_5120X2160:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_5120X2160;
			break;
		case V4L2_EXT_VBE_PANEL_RESOLUTION_7680X4320:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
			break;
		default:
			stLxDispInfo.panelResolution = LX_OVI_PANEL_RESOLUTION_MAX;
	}

	switch(stV4l2PanelInfo.frcType)
	{
		case V4L2_EXT_VBE_FRC_CHIP_INTERNAL:
			stLxDispInfo.frcChipType = LX_OVI_FRC_CHIP_INTERNAL;
			break;
		default:
			stLxDispInfo.frcChipType = LX_OVI_FRC_CHIP_NONE;
	}

	switch(stV4l2PanelInfo.panelCellType)
	{
		case V4L2_EXT_VBE_PANEL_CELL_TYPE_RGBW:
			stLxDispInfo.panelCellType = LX_OVI_PANEL_CELL_RGBW;
			break;
		default:
			stLxDispInfo.panelCellType = LX_OVI_PANEL_CELL_RGB;
	}

	switch(stV4l2PanelInfo.panelVersion)
	{
		case V4L2_EXT_VBE_PANEL_V16:
			stLxDispInfo.panelVersion = LX_OVI_PANEL_V16;
			break;
		case V4L2_EXT_VBE_PANEL_V17:
			stLxDispInfo.panelVersion = LX_OVI_PANEL_V17;
			break;
		case V4L2_EXT_VBE_PANEL_V18:
			stLxDispInfo.panelVersion = LX_OVI_PANEL_V18;
			break;
		default:
			stLxDispInfo.panelVersion = LX_OVI_PANEL_MAX;
	}

	switch(stV4l2PanelInfo.panelInch)
	{
		case V4L2_EXT_VBE_PANEL_INCH_22:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_22;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_23:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_23;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_24:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_24;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_26:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_26;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_27:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_27;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_28:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_28;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_32:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_32;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_39:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_39;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_40:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_40;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_42:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_42;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_43:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_43;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_47:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_47;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_49:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_49;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_50:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_50;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_55:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_55;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_58:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_58;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_60:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_60;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_65:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_65;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_70:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_70;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_75:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_75;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_77:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_77;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_79:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_79;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_84:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_84;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_86:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_86;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_98:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_98;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_105:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_105;
			break;
		case V4L2_EXT_VBE_PANEL_INCH_48:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_48;
			break;
		default:
			stLxDispInfo.panelInch = LX_OVI_PANEL_INCH_MAX;
	}

	switch(stV4l2PanelInfo.panelMaker)
	{
		case V4L2_EXT_VBE_PANEL_MAKER_LGD:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_LGD;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_AUO:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_AUO;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_SHARP:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_SHARP;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_BOE:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_BOE;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_CSOT:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_CSOT;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_INNOLUX:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_INNOLUX;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_LGD_M:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_LGD_M;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_ODM_B:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_ODM_B;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_BOE_TPV:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_BOE_TPV;
			break;
		case V4L2_EXT_VBE_PANEL_MAKER_HKC:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_HKC;
			break;
		default:
			stLxDispInfo.panelMaker = LX_OVI_PANEL_MAKER_MAX;
	}

	switch(stV4l2PanelInfo.panelBacklightType)
	{
		case V4L2_EXT_VBE_PANEL_BL_EDGE_LED:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_EDGE_LED;
			break;
		case V4L2_EXT_VBE_PANEL_BL_DIRECT_L:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
			break;
		case V4L2_EXT_VBE_PANEL_BL_OLED:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
			break;
		case V4L2_EXT_VBE_PANEL_BL_DIRECT_VI:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_VI;
			break;
		case V4L2_EXT_VBE_PANEL_BL_DIRECT_SKY:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_SKY;
			break;
		default:
			stLxDispInfo.panelBacklight = LX_OVI_PANEL_BACKLIGHT_MAX;
	}

	switch(stV4l2PanelInfo.panelLedBarType)
	{
		case V4L2_EXT_VBE_PANEL_LED_BAR_6:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_6;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_12:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_12;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_36:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_36;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_40:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_40;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_48:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_48;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_50:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_50;
			break;
		case V4L2_EXT_VBE_PANEL_LED_BAR_96:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_96;
			break;
		default:
			stLxDispInfo.panelLedBar = LX_OVI_PANEL_LED_BAR_MAX;
	}

	switch(stV4l2PanelInfo.panelFrameRate)
	{
		case V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ:
			stLxDispInfo.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			break;
		case V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ:
			stLxDispInfo.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
			break;
		default:
			stLxDispInfo.panelFramerate = LX_OVI_PANEL_FRAMERATE_144Hz;
	}

	switch(stV4l2PanelInfo.lvdsColorDepth)
	{
		case V4L2_EXT_VBE_LVDS_COLOR_DEPTH_8BIT:
			stLxDispInfo.lvdsBit = LX_OVI_8BIT;
			break;
		case V4L2_EXT_VBE_LVDS_COLOR_DEPTH_10BIT:
			stLxDispInfo.lvdsBit = LX_OVI_10BIT;
			break;
		default:
			stLxDispInfo.lvdsBit = LX_OVI_BIT_MAX;
	}

	switch(stV4l2PanelInfo.lvdsType)
	{
		case V4L2_EXT_VBE_LVDS_TYPE_VESA:
			stLxDispInfo.lvdsType = LX_OVI_LVDS_OUT_VESA;
			break;
		case V4L2_EXT_VBE_LVDS_TYPE_JEIDA:
			stLxDispInfo.lvdsType = LX_OVI_LVDS_OUT_JEIDA;
			break;
		default:
			stLxDispInfo.lvdsType = LX_OVI_LVDS_OUT_MAX;
	}

	switch(stV4l2PanelInfo.dispOutLaneBW)
	{
		case V4L2_EXT_VBE_PANEL_BANDWIDTH_1_5G:
			stLxDispInfo.dispOutLaneBw = LX_OVI_OUTPUT_LANE_BANDWIDTH_1_5G;
			break;
		case V4L2_EXT_VBE_PANEL_BANDWIDTH_2_1G:
			stLxDispInfo.dispOutLaneBw = LX_OVI_OUTPUT_LANE_BANDWIDTH_2_1G;
			break;
		case V4L2_EXT_VBE_PANEL_BANDWIDTH_3_0G:
			stLxDispInfo.dispOutLaneBw = LX_OVI_OUTPUT_LANE_BANDWIDTH_3_0G;
			break;
		default:
			stLxDispInfo.dispOutLaneBw = LX_OVI_OUTPUT_LANE_BANDWIDTH_DEFAULT;
	}

	stLxDispInfo.userSpecificOption.all = stV4l2PanelInfo.userSpecificOption.all;

	memcpy((void *)lxDispInfo, (void *)&stLxDispInfo, sizeof(LX_OVI_DISPLAY_INFO_T));

	return;
}

static int _vbe_V4L2_CID_EXT_VBE_DCLK_MODE(UINT32 lxParams)
{
	int ret = 0;

	do {
		BE_NOTI("%d\n",lxParams);
		ret = OVI_HAL_SetDClock(&lxParams);
		if (ret)
		{
			BE_ERROR("OVI_HAL_SetDClock error(%d)\n",ret);
			break;
		}

		BE_NOTI("be\n");
		ret = BE_TOP_HAL_SetDClock(&lxParams);
		if (ret)
		{
			BE_ERROR("BE_TOP_HAL_SetDClock error(%d)\n",ret);
			break;
		}
		BE_NOTI("done\n");
	} while (0);

	return ret;
}

static int _vbe_V4L2_CID_EXT_VBE_OUTPUT_TIMING(struct v4l2_ext_vbe_output_timing *p)
{
	int ret = 0;
	LX_OVI_TCON_OUTPUT_TIMING_T lxParams;

	if (!p) {
		BE_ERROR("input null\n");
		return -EFAULT;
	}

	do {
		lxParams.frameRate = p->frameRate;
		lxParams.hResolution = p->hResolution;
		lxParams.vResolution = p->vResolution;
		BE_NOTI("fr:%d h,v:%d,%d\n",p->frameRate,p->hResolution,p->vResolution);
		ret = OVI_HAL_SetOutputTiming(&lxParams);
		if (ret)
		{
			BE_ERROR("OVI_HAL_SetOutputTiming error(%d)\n",ret);
			break;
		}

		BE_NOTI("be\n");
		ret = BE_TOP_HAL_SetOutputTiming(&lxParams);
		if (ret)
		{
			BE_ERROR("BE_TOP_HAL_SetOutputTiming error(%d)\n", ret);
			return ret;
		}
		BE_NOTI("done\n");
	} while (0);

	return ret;
}

static int vbe_set_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		BE_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	if (_g_v4l2_vbe_cid_mask == ctrl->id)
	{
		BE_TRACE("cid_mask(%s) skip\n",vbe_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_vbe_compat_vidioc_ext_ctrls(ctrl);
	}
	#endif

	switch (ctrl->id) {
		case V4L2_CID_EXT_VBE_INIT:
		{
			LX_OVI_DISPLAY_INFO_T lxParams;
			LX_BE_FRC_CFG_T lxFrcParams;
			LX_BE_FRC_CFG_T *p_info = &(gBeFrcInfo.cfg);
			struct v4l2_ext_vbe_panel_info param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxFrcParams.cfg_type = LX_BE_FRC_CFG_TYPE_USE;
			lxFrcParams.use_type = (param.frcType == V4L2_EXT_VBE_FRC_CHIP_INTERNAL) ? 0:1;
			lxFrcParams.dfr_type = 0xff;

			BE_FRC_HAL_SetConfig(&lxFrcParams);

			/* update frc info */
			p_info->cfg_type |= lxFrcParams.cfg_type;
			if (lxFrcParams.cfg_type&LX_BE_FRC_CFG_TYPE_USE)
				p_info->use_type = lxFrcParams.use_type;
			if (lxFrcParams.cfg_type&LX_BE_FRC_CFG_TYPE_DFR)
				p_info->dfr_type = lxFrcParams.dfr_type;

			vbe_disp_transpanelparams(&param, &lxParams);

			ret = OVI_HAL_SetDisplayOption(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetDisplayOption error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_RESUME:
		{
			LX_OVI_DISPLAY_INFO_T lxParams;
			LX_BE_FRC_CFG_T lxFrcParams;
			LX_BE_FRC_CFG_T *p_info = &(gBeFrcInfo.cfg);
			struct v4l2_ext_vbe_panel_info param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxFrcParams.cfg_type = LX_BE_FRC_CFG_TYPE_USE;
			lxFrcParams.use_type = (param.frcType == V4L2_EXT_VBE_FRC_CHIP_INTERNAL) ? 0:1;
			lxFrcParams.dfr_type = 0xff;

			BE_FRC_HAL_SetConfig(&lxFrcParams);

			/* update frc info */
			p_info->cfg_type |= lxFrcParams.cfg_type;
			if (lxFrcParams.cfg_type&LX_BE_FRC_CFG_TYPE_USE)
				p_info->use_type = lxFrcParams.use_type;
			if (lxFrcParams.cfg_type&LX_BE_FRC_CFG_TYPE_DFR)
				p_info->dfr_type = lxFrcParams.dfr_type;

			vbe_disp_transpanelparams(&param, &lxParams);

			ret = OVI_HAL_DisplayResume(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_DisplayResume error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_SSC:
		{
			LX_OVI_SPREAD_SPECTRUM_T lxParams;
			struct v4l2_ext_vbe_ssc param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_ssc)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.bEnable = param.on_off;
			lxParams.u16Period = param.period;
			lxParams.eSpreadRatio = param.percent;

			ret = OVI_HAL_SetSpreadSpectrum(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetSpreadSpectrum error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_MIRROR:
		{
			struct v4l2_ext_vbe_mirror param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_mirror)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO,NULL,(void *)&param.bIsV);
			
			ret = BE_TOP_HAL_SetVideoVReverse((BOOLEAN)param.bIsV);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetVideoVReverse error(%d)\n",ret);
			}

			ret = OVI_HAL_SetLvdsHReverse((BOOLEAN)param.bIsH);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetLvdsHReverse error(%d)\n",ret);
				break;
			}

			ret = OVI_HAL_SetTconHReverse((BOOLEAN)param.bIsH);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetTconHReverse error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_MPLUS_MODE:
		{
			enum v4l2_ext_vbe_mplus_mode param;
			LX_OVI_TCON_MLE_MODE_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(enum v4l2_ext_vbe_mplus_mode)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}
			
			switch(param)
			{
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE0:
					lxParam = LX_OVI_TCON_HIGH_LUM1_MSE_ON;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE1:
					lxParam = LX_OVI_TCON_HIGH_LUM2;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE2:
					lxParam = LX_OVI_TCON_LOW_POWER1;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE3:
					lxParam = LX_OVI_TCON_MLE_MODE_OFF;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE4:
					lxParam = LX_OVI_TCON_HIGH_LUM1_MSE_OFF;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE5:
					lxParam = LX_OVI_TCON_LOW_POWER2;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE6:
					lxParam = LX_OVI_TCON_LOW_POWER2_SC_OFF;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE7:
					lxParam = LX_OVI_TCON_BOE_CINEMA;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE8:
					lxParam = LX_OVI_TCON_BOE_VIVID;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE9:
					lxParam = LX_OVI_TCON_BOE_UTUBE0;
					break;
				case V4L2_EXT_VBE_MPLUS_MPLUS_MODE10:
					lxParam = LX_OVI_TCON_BOE_UTUBE1;
					break;
				default :
					lxParam = LX_OVI_TCON_MLE_MODE_OFF;
					break;
			}
			
			ret = OVI_HAL_SetMleMode(lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetMleMode error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_DGA4CH:
		{
			struct v4l2_ext_vbe_dga4ch param;
			LX_OVI_TCON_GAMMA_RGBW_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_dga4ch)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.bGammaLut.pData = param.pBlueGammaTable;
			lxParam.bGammaLut.sizeNum = V4L2_GAMMA_LUT_SIZENUM;
			lxParam.gGammaLut.pData = param.pGreenGammaTable;
			lxParam.gGammaLut.sizeNum = V4L2_GAMMA_LUT_SIZENUM;
			lxParam.rGammaLut.pData = param.pRedGammaTable;
			lxParam.rGammaLut.sizeNum = V4L2_GAMMA_LUT_SIZENUM;
			lxParam.wGammaLut.pData = param.pWhiteGammaTable;
			lxParam.wGammaLut.sizeNum = V4L2_GAMMA_LUT_SIZENUM;

			ret = OVI_HAL_SetGammaRGBW(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetGammaRGBW error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_MPLUS_PARAM:
		{
			struct v4l2_ext_vbe_mplus_param param;
			//UINT32 regVal;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_mplus_param)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			#if 0
			OVI_REG_RD(0xC907A230, regVal);
			regVal = (regVal & (~0xFF)) | ((UINT32)(param.nFrameGainLimit >> 8) & 0xFF);
			OVI_REG_WR(0xC907A230, regVal);

			OVI_REG_RD(0xC907A234, regVal);
			regVal = (regVal & (~0xFF)) | ((UINT32)param.nFrameGainLimit & 0xFF);
			OVI_REG_WR(0xC907A234, regVal);

			OVI_REG_RD(0xC907A2DC, regVal);
			regVal = (regVal & (~0xFF)) | ((UINT32)(param.nPixelGainLimit >> 8) & 0xFF);
			OVI_REG_WR(0xC907A2DC, regVal);

			OVI_REG_RD(0xC907A2E0, regVal);
			regVal = (regVal & (~0xFF)) | ((UINT32)param.nPixelGainLimit & 0xFF);
			OVI_REG_WR(0xC907A2E0, regVal);
			#endif

		}break;
		case V4L2_CID_EXT_VBE_INNER_PATTERN:
		{
			struct v4l2_ext_vbe_inner_pattern param;
			LX_BE_DEBUG_DISPLAY_T lxDebugParam;
			LX_OVI_TCON_PATTERN_GEN_T lxPatParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_inner_pattern)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			memset(&lxDebugParam, 0xFF, sizeof(LX_BE_DEBUG_DISPLAY_T));
			lxPatParam.bUseInternalSync = FALSE;

			if(param.bOnOff == 0xff)
			{
				lxDebugParam.u8LEDDebugDisplay = 0;
				ret = BE_TOP_HAL_SetDebugDisplay(&lxDebugParam);

			    lxPatParam.eMode = LX_OVI_TCON_TPG_OFF;
				ret = OVI_HAL_SetPatternGenerator(&lxPatParam);
			}
			else
			{
				switch(param.ip)
				{
					case 2:	//DPE
					{
						if (param.bOnOff == 0)
						{
							lxDebugParam.u8LEDDebugDisplay = 0;
						}
						else {
							/* Ctrl = OFF */
							lxDebugParam.u8LEDDebugDisplay = param.type;
						}
						ret = BE_TOP_HAL_SetDebugDisplay(&lxDebugParam);
					}
					break;
					case 3:	//TCON
					{
						if(param.bOnOff == 0) //off
						{
							lxPatParam.eMode = LX_OVI_TCON_TPG_OFF;
						}
						else
						{
							lxPatParam.eMode = param.type;
						}
						OVI_HAL_SetPatternGenerator(&lxPatParam);
					}
					break;
					default:
					break;
				}
			}
		}break;
		case V4L2_CID_EXT_VBE_TSCIC:
		{
			struct v4l2_ext_vbe_panel_tscic param;
			LX_OVI_TCON_TSCIC_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tscic)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.pu8ControlTbl = param.u8pControlTbl;
			lxParam.u32Ctrlsize = param.u32Ctrlsize;
			lxParam.pu32TscicTbl = param.u32pTSCICTbl;
			lxParam.u32TscicSize = param.u32Tscicsize;

			BE_NOTI("V4L2_CID_EXT_VBE_TSCIC ctrl size:%d, data size %d\n",param.u32Ctrlsize,param.u32Tscicsize);

			ret = OVI_HAL_SetTscic(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetTscic error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_MPLUS_DATA:
		{
			struct v4l2_ext_vbe_mplus_data param;
			LX_OVI_TCON_FW_DWLD_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_mplus_data)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if(param.pRegisterSet == NULL)
			{
				BE_ERROR("Data is null");
				ret = NOT_OK;
				break;
			}

			switch(param.nPanelMaker)
			{
				case 1:
					lxParam.type = LX_OVI_TCON_FW_BOE;
					lxParam.sizeNum = V4L2_BOE_MPLUS_LUT_SIZENUM;
					break;
				case 0:
				default :
					lxParam.type = LX_OVI_TCON_FW_LGD;
					lxParam.sizeNum = V4L2_LGD_MPLUS_LUT_SIZENUM;
					break;
			}
			lxParam.pData = param.pRegisterSet;
			lxParam.read = FALSE;

			ret = OVI_HAL_UpdateFirmware(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_UpdateFirmware error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_PWM_APPLY_PARAM:
		{
			enum v4l2_ext_vbe_pwm_pin_sel_mask param;
			int i;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(enum v4l2_ext_vbe_pwm_pin_sel_mask)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			BE_NOTI("V4L2_CID_EXT_VBE_PWM_APPLY_PARAM MASK:%d \n",param);
			VBE_BACKUP_PWM_LOG("APPLY) mask:0x%x\n",param);

			pwmParams.portMask = 0;

			param = (param == V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK) ? V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK : param;

			for(i = 0; i < LX_BE_PWM_PORT_MAX; i++)
			{
				if( ((gPwmSetParamIdxFlag & param) >> i) & 0x01 )
				{
					pwmParams.portMask |= (0x1<<i);
				}
			}

			gPwmApplyParamIdxFlag |= pwmParams.portMask;

			ret = BE_PWM_HAL_SetPwmParams(&pwmParams);
			if (ret)
			{
				BE_ERROR("BE_PWM_HAL_SetPwmParams error(%d)\n",ret);
				break;
			}

			BE_NOTI("V4L2_CID_EXT_VBE_PWM_APPLY_PARAM SetParamFlag:%d ApplyParamFlag:%d\n",
				gPwmSetParamIdxFlag,gPwmApplyParamIdxFlag);
		}break;
		case V4L2_CID_EXT_VBE_PWM_PARAM:
		{
			struct v4l2_ext_vbe_pwm_param param;
			struct v4l2_ext_vbe_pwm_param_data pwmParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_pwm_param)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if(copy_from_user(&pwmParam,(void __user *)param.pstPWMParam,sizeof(struct v4l2_ext_vbe_pwm_param_data)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			VBE_BACKUP_PWM_LOG("PARAM)%d en%d,%d,%d,%d adp%d,%d,%d,%d fr%d,%d,%d\n",param.pwmIndex,\
				pwmParam.pwm_enable,pwmParam.pwm_lock,pwmParam.pwm_scanning_enable,pwmParam.pwm_low_power_enable,\
				pwmParam.pwm_adapt_freq_param.pwm_adapt_freq_enable,pwmParam.pwm_adapt_freq_param.pwmfreq_48nHz,\
				pwmParam.pwm_adapt_freq_param.pwmfreq_50nHz,pwmParam.pwm_adapt_freq_param.pwmfreq_60nHz,\
				pwmParam.pwm_frequency,pwmParam.pwm_pos_start,pwmParam.pwm_duty);

			gPwmSetParamIdxFlag |= (0x1 << param.pwmIndex);
			pwmParams.portParams[param.pwmIndex].enable = pwmParam.pwm_enable ? TRUE : FALSE;
			pwmParams.portParams[param.pwmIndex].lockModeEn = pwmParam.pwm_lock ? TRUE : FALSE;

			if(pwmParams.portParams[param.pwmIndex].enable)
				pwmParams.portParams[param.pwmIndex].pwmOutput = BE_PWM_NORMAL;
			else
				pwmParams.portParams[param.pwmIndex].pwmOutput = BE_PWM_LOW;

			pwmParams.portParams[param.pwmIndex].scanningModeEn = pwmParam.pwm_scanning_enable ? TRUE : FALSE;
			pwmParams.portParams[param.pwmIndex].lowPowerModeEn = pwmParam.pwm_low_power_enable ? TRUE : FALSE;
			pwmParams.portParams[param.pwmIndex].adaptFreqEn = pwmParam.pwm_adapt_freq_param.pwm_adapt_freq_enable ? TRUE : FALSE;
			pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_48nHz = pwmParam.pwm_adapt_freq_param.pwmfreq_48nHz;
			pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_50nHz = pwmParam.pwm_adapt_freq_param.pwmfreq_50nHz;
			pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_60nHz = pwmParam.pwm_adapt_freq_param.pwmfreq_60nHz;
			pwmParams.portParams[param.pwmIndex].frequency = pwmParam.pwm_frequency;
			pwmParams.portParams[param.pwmIndex].offset = pwmParam.pwm_pos_start;
			pwmParams.portParams[param.pwmIndex].duty = pwmParam.pwm_duty;
			
			BE_NOTI("V4L2_CID_EXT_VBE_PWM_PARAM Port:%d, Enable:%d, Duty: %d, Freq: %d offset: %d, adpFreqEn: %d setFlag: %d, applyFlag: %d \n",
				param.pwmIndex,pwmParam.pwm_enable,pwmParam.pwm_duty,pwmParam.pwm_frequency,pwmParam.pwm_pos_start,
				pwmParam.pwm_adapt_freq_param.pwm_adapt_freq_enable,gPwmSetParamIdxFlag,gPwmApplyParamIdxFlag);
		}break;
		case V4L2_CID_EXT_VBE_PWM_SET_DUTY:
		{
			struct v4l2_ext_vbe_pwm_duty param;
			UINT32 changeFlag = 0;
			int i;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_pwm_duty)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			BE_DEBUG("V4L2_CID_EXT_VBE_PWM_SET_DUTY MASK:%d, Duty: %d, setFlag: %d, applyFlag: %d \n",
				param.pwmIndex,param.pwm_duty,gPwmSetParamIdxFlag,gPwmApplyParamIdxFlag);

			VBE_BACKUP_PWM_LOG("DUTY) mask:0x%x, duty:%d, sflag:0x%x, aflag:0x%x\n",param.pwmIndex,param.pwm_duty,gPwmSetParamIdxFlag,gPwmApplyParamIdxFlag);

			param.pwmIndex = (param.pwmIndex == V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK) ? V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK : param.pwmIndex;

			for(i = 0; i < LX_BE_PWM_PORT_MAX; i++)
			{
				if( (((gPwmApplyParamIdxFlag & param.pwmIndex) >> i) & 0x01) && (pwmParams.portParams[i].enable == TRUE))
				{
					pwmParams.portParams[i].duty = param.pwm_duty;

					if (changeFlag == 0)
						changeFlag = 1;
				}
			}

			if(changeFlag == 0)
			{
				BE_ERROR("pwm is not initialized\n");
				ret = NOT_OK;
				break;
			}

			ret = BE_PWM_HAL_SetPwmParams(&pwmParams);
			if (ret)
			{
				BE_ERROR("BE_PWM_HAL_SetPwmParams error(%d)\n",ret);
				break;
			}

			do {
				struct vbe_dev *drv = video_get_drvdata(&v4l2_vbe_video_dev);
				struct vbe_dev_task *t = &drv->led_task;
				t->rx_cnt = (t->rx_cnt<0xff)? (t->rx_cnt+1):0;
			} while(0);
		}break;
		case V4L2_CID_EXT_VBE_VCOM_PAT_DRAW:
		{
			struct v4l2_ext_vbe_vcom_pat_draw param;
			LX_OVI_TCON_VCOM_PAT_DATA_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_vcom_pat_draw)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.pu16vcomPattern = param.vcomPattern;
			lxParams.sizeNum = param.nSize;
			
			ret = OVI_HAL_SetVCOMPatternData(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetVCOMPatternData error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_VCOM_PAT_CTRL:
		{
			enum v4l2_ext_vbe_vcom_pat_ctrl param;
			LX_OVI_TCON_VCOM_PAT_CTRL_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(enum v4l2_ext_vbe_vcom_pat_ctrl)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams = (LX_OVI_TCON_VCOM_PAT_CTRL_T)param;
			ret = OVI_HAL_SetVCOMPatternCtrl(lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetVCOMPatternCtrl error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_ORBIT:
		{
			struct v4l2_ext_vbe_panel_orbit_info param;
#ifdef INCLUDE_KDRV_PE
			LX_PE_INF_DISPLAY_T cur_inf_param;
			LX_PE_INF_DISPLAY_T pre_inf_param;
#endif
			LX_BE_SET_DEFAULT_PARAM(LX_BE_ORBIT_T,lxParams);

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_orbit_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.bOnOff = param.on_off;
			if (param.orbitmode == V4L2_EXT_VBE_PANEL_ORBIT_STORE_MODE)
			{
				lxParams.bStoreMode = TRUE; // Higher priority than bAutoMode
			}
			else
			{
				lxParams.bAutoMode = param.orbitmode;
				lxParams.bStoreMode = FALSE;
				if (param.orbitmode == V4L2_EXT_VBE_PANEL_ORBIT_JUSTSCAN_MODE)
				{
					lxParams.bOsdOverscan = FALSE;
				}
				else
				{
					lxParams.bOsdOverscan = TRUE;
				}
			}

			ret = BE_TOP_HAL_SetOrbit(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetOrbit error(%d)\n",ret);
				break;
			}
#ifdef INCLUDE_KDRV_PE
			cur_inf_param.win_id = 0x0;
			/* get pre display info */
			ret = vpq_hwrap_getpicdisplayinfo((void *)&cur_inf_param);
			cur_inf_param.info_type = LX_PE_INFO_MODE;
			memcpy(&pre_inf_param, &cur_inf_param, sizeof(LX_PE_INF_DISPLAY_T));
			/**
			* causion, these items only in this function :
			* mul_win
			*/
			cur_inf_param.mode.is_orbit= (UINT32)param.on_off;
			/* set default */
			if (pre_inf_param.mode.is_orbit != cur_inf_param.mode.is_orbit)
			{
		 		/* set disp info */
				ret = vpq_hwrap_setpicdisplayinfo((void *)&cur_inf_param);
		 	}
#endif
		}break;
		case V4L2_CID_EXT_VBE_LSR:
		{
			struct v4l2_ext_vbe_panel_lsr_info param;
			LX_BE_LSR_T lxParams;
			UINT32 buffer;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_lsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pLsrTable == NULL)
			{
				BE_ERROR("param.pLsrTable is null\n");
				return -EINVAL;
			}

			ret = copy_from_user(&buffer, (void __user *)param.pLsrTable, sizeof(UINT32));
			if (ret)
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.lsrTbl.pu32Data = param.pLsrTable;
			lxParams.lsrTbl.u32SizeNum = (buffer & 0xFF000000) >> 24;
#if 0
			if (param.lsrstep == V4L2_EXT_VBE_PANEL_LSR_OFF)
				lxParams.u32LsrMode = 0;
			else if (param.lsrstep == V4L2_EXT_VBE_PANEL_LSR_LIGHT)
				lxParams.u32LsrMode = 1;
			else if (param.lsrstep == V4L2_EXT_VBE_PANEL_LSR_STRONG)
				lxParams.u32LsrMode = 2;
			else if (param.lsrstep == V4L2_EXT_VBE_PANEL_LSR_STRONG_OTHERS)
				lxParams.u32LsrMode = 3;
			else if (param.lsrstep == V4L2_EXT_VBE_PANEL_LSR_LIGHT_OTHERS)
				lxParams.u32LsrMode = 4;
#endif
			if (param.lsrstep == 0)			//SICREQ-1185
				lxParams.u32LsrMode = 0;
			else if (param.lsrstep == 1)
				lxParams.u32LsrMode = 1;
			else if (param.lsrstep == 2)
				lxParams.u32LsrMode = 2;
			else if (param.lsrstep == 3)
				lxParams.u32LsrMode = 3;
			else if (param.lsrstep == 4)
				lxParams.u32LsrMode = 4;
			else if (param.lsrstep == 5)
				lxParams.u32LsrMode = 5;
			else if (param.lsrstep == 6)
				lxParams.u32LsrMode = 6;
			else if (param.lsrstep == 7)
				lxParams.u32LsrMode = 7;
			else if (param.lsrstep == 8)
				lxParams.u32LsrMode = 8;
			else if (param.lsrstep == 9)
				lxParams.u32LsrMode = 9;

			ret = BE_TOP_HAL_SetLSRParam(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetLSRParam error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_GSR:
		{
			struct v4l2_ext_vbe_panel_gsr_info param;
			LX_BE_GSR_T lxParams;
			UINT32 buffer;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_gsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pGsrTable == NULL)
			{
				BE_ERROR("param.pGsrTable is null\n");
				return -EINVAL;
			}

			ret = copy_from_user(&buffer, (void __user *)param.pGsrTable, sizeof(UINT32));
			if (ret)
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.gsrTbl.pu32Data = param.pGsrTable;
			lxParams.gsrTbl.u32SizeNum = (buffer & 0xFF000000) >> 24;

			ret = BE_TOP_HAL_SetGSR(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetGSR error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_GSR2:
		{
			struct v4l2_ext_vbe_panel_second_gsr_info param;
			LX_BE_GSR_T lxParams;
			UINT32 buffer;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_second_gsr_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pGsrTable == NULL)
			{
				BE_ERROR("param.pGsrTable is null\n");
				return -EINVAL;
			}

			ret = copy_from_user(&buffer, (void __user *)param.pGsrTable, sizeof(UINT32));
			if (ret)
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.gsrTbl.pu32Data = param.pGsrTable;
			lxParams.gsrTbl.u32SizeNum = (buffer & 0xFF000000) >> 24;

			ret = BE_TOP_HAL_SetGSR2(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetGSR2 error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_OSD_GAIN:
		{
			struct v4l2_ext_vbe_panel_osd_gain_info param;
			LX_BE_OSD_RGB_LEVEL_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_osd_gain_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.bOnOff = param.on_off;
			lxParams.levelTbl.pu32Data = param.levelval;
			lxParams.levelTbl.u32SizeNum = param.size/sizeof(UINT32);

			ret = BE_TOP_HAL_SetOSDRGBLevel(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetOSDRGBLevel error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM:
		{
			struct v4l2_ext_vbe_panel_irr_info param;
			LX_BE_LUT_T lxParams;
			UINT32 buffer;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_irr_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pIrrlum == NULL)
			{
				BE_ERROR("param.pIrrlum is null\n");
				return -EINVAL;
			}

			ret = copy_from_user(&buffer, (void __user *)param.pIrrlum, sizeof(UINT32));
			if (ret)
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParams.pu32Data = param.pIrrlum;
			lxParams.u32SizeNum = (buffer & 0xFF000000) >> 24;

			ret = BE_TOP_HAL_SetIrrAdaptedLum(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetIrrAdaptedLum error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM:
		{
			struct v4l2_ext_vbe_panel_tpc_recovery_param_info param;
			LX_BE_LUT_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_param_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pParamTable == NULL)
			{
				BE_ERROR("param.pParamTable is null\n");
				return -EINVAL;
			}

			lxParams.pu32Data = param.pParamTable;
			lxParams.u32SizeNum = param.table_size/sizeof(UINT32);

			ret = BE_TOP_HAL_SetTPCParam(&lxParams);
			if (ret)
			{
				BE_ERROR("BE_TOP_HAL_SetTPCParam error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_DEMURA :
		{
			struct v4l2_ext_vbe_panel_demura param;
			LX_OVI_TCON_DEMURA_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_demura)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.bIsGet = FALSE;
			lxParam.bEnable = param.enable;
			lxParam.pu8Config = param.config;
			lxParam.u32ConfigSize = param.configsize;
			lxParam.pu8Data = (UINT32 *)param.data;
			lxParam.u32DataSize = param.datasize;

			ret = OVI_HAL_SetDemura(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetDemura error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_PCLRC :
		{
			struct v4l2_ext_vbe_panel_pclrc param;
			LX_OVI_PCLRC_LUT_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_pclrc)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.data == NULL)
			{
				BE_ERROR("param.data is null\n");
				return -EINVAL;
			}

			lxParams.enable = param.enable;
			lxParams.path = param.positionAfterLineOD;
			lxParams.pData =param.data;
			lxParams.sizeNum = param.datasize;
			lxParams.bIsGet = FALSE;

			ret = OVI_HAL_SetPCLRC(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetPCLRC error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_ID_VBE_SET_GENLOCK :
		{
			struct v4l2_ext_set_vbe_genlock data;
			LX_BE_SET_GENLOCK_T lxParam;
			BE_PRINT("===============================================V4L2_CID_EXT_ID_VBE_SET_GENLOCK vbe_set_ctrl\n");

			if(copy_from_user(&data,(void __user *)ctrl->string,sizeof(struct v4l2_ext_set_vbe_genlock)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}
			lxParam.genlock = data.genlock;
			gGenlock.genlock_status = lxParam.genlock;
			BE_PRINT("===============================================vbe_set_ctrl genlock: %d, %d\n", lxParam.genlock, gGenlock.genlock_status);

			ret = BE_TOP_HAL_SetGenlock(&lxParam);
			if (ret)
			{
				BE_ERROR("BE_PQ_HAL_Set_Genlock error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM:
		{
			struct v4l2_ext_vbe_panel_apl_control_param_info param;
			LX_BE_LUT_T lxParams;
			UINT32 p[4]={0,0,0,0};

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info )))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.pParamTable == NULL)
			{
				BE_ERROR("param.pParamTable is null\n");
				return -EINVAL;
			}

			lxParams.pu32Data = param.pParamTable;
			lxParams.u32SizeNum = param.table_size/sizeof(UINT32);

			param.table_size = lxParams.u32SizeNum * sizeof(UINT32);

			if(copy_from_user(p,(void __user *)param.pParamTable,sizeof(unsigned int)*4))
			{
				BE_ERROR("copy_from_user error\n");
			}
			ret = BE_TOP_HAL_SetOledAplCtrlParam(&lxParams);
			if (ret)
			{
				BE_DEBUG("BE_TOP_HAL_SetOledAplCtrlParam error(%d)\n",ret);
				break;
			}
		}break;
#ifdef V4L2_VBE_USE_ID_SIGNAGE_CID
		case V4L2_CID_EXT_VBE_FRAME_RATE:
		{
#ifdef INCLUDE_KDRV_DE
			LX_DE_FR_RATE_T lxParam;
			struct v4l2_ext_vbe_frame_rate param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_frame_rate)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}
			lxParam.isForceFreeRun = param.on_off;
			lxParam.fr_rate = param.frameRate;

			ret = resource_mgr_ioctl(DE_IOW_SET_FR_RATE,(unsigned long)&lxParam,1);//vp_kwrap_setfrrate((BOOLEAN)param.on_off, (UINT16)param.frameRate);
			if (ret)
			{
				BE_ERROR("DE_IOW_SET_FR_RATE error(%d)\n",ret);
				break;
			}
#endif
		}break;
#endif
		case V4L2_CID_EXT_ID_VBE_FRAME_RATE:
		{
#ifdef INCLUDE_KDRV_DE
			LX_DE_FR_RATE_T lxParam;
			struct v4l2_ext_vbe_frame_rate param;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_frame_rate)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}
			lxParam.isForceFreeRun = param.on_off;
			lxParam.fr_rate = param.frameRate;

			ret = resource_mgr_ioctl(DE_IOW_SET_FR_RATE,(unsigned long)&lxParam,1);
			if (ret)
			{
				BE_ERROR("DE_IOW_SET_FR_RATE error(%d)\n",ret);
				break;
			}
#endif
		}break;
		case V4L2_CID_EXT_VBE_VAC_PARAM:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VAC_PARAM\n");
		}break;
		case V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_VDF_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VDF_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM\n");
		}break;
		case V4L2_CID_EXT_VBE_DCLK_MODE:
		{
			UINT32 lxParams;

			if(copy_from_user(&_g_v4l2_vbe_dclock,(void __user *)ctrl->string,sizeof(enum v4l2_ext_vbe_dclk_mode)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (0 == vbe_is_support(V4L2_CID_EXT_VBE_DCLK_MODE)) {
				BE_NOTI("DCLK not support (y%d)\n",_g_vbe_ctx.year);
				return 0;
			}

			lxParams = _g_v4l2_vbe_dclock;
			ret = _vbe_V4L2_CID_EXT_VBE_DCLK_MODE(lxParams);
		}break;
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_ID_VBE_UCR_DATA\n");
		}break;
		case V4L2_CID_EXT_VBE_OBJECT_APL_GAIN:
		{
			unsigned int i, num;
			LX_BE_LED_object_apl_gain param;

			if (copy_from_user(&param,(void __user *)ctrl->string,sizeof(LX_BE_LED_object_apl_gain))) {
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			ret = BE_LED_HAL_SetObjectAplGain(&param);
			if (ret) {
				BE_ERROR("BE_LED_HAL_SetObjectAplGain error(%d)\n",ret);
				break;
			}

			/* backup */
			num = sizeof(_g_object_apl_gain)/sizeof(_g_object_apl_gain[0]);
			for (i=0; i<num; i++) {
				if (_g_object_apl_gain[i].id == param.id) {
					memcpy(&_g_object_apl_gain[i],&param,sizeof(param));
				}
			}

			BE_PRINT_OBJ("obj apl gain id:%x en:%x g:%x x:%x,%x,%x,%x y:%x,%x,%x,%x\n",\
				param.id,param.enable,param.master_gain,\
				param.gain_x[0],param.gain_x[1],param.gain_x[2],param.gain_x[3],\
				param.gain_y[0],param.gain_y[1],param.gain_y[2],param.gain_y[3]);
		}break;

		case V4L2_CID_EXT_VBE_OUTPUT_TIMING:
		{
			struct v4l2_ext_vbe_output_settingdata param;

			if (copy_from_user(&param, (void __user *)ctrl->ptr,sizeof(struct v4l2_ext_vbe_output_settingdata)))
			{
				BE_ERROR("copy_from_user error for V4L2_CID_EXT_VBE_OUTPUT_TIMING\n");
				return -EFAULT;
			}

			switch (param.setType)
			{
				case V4L2_EXT_VBE_OUTPUT_SET_TIMING_TYPE:
				case V4L2_EXT_VBE_OUTPUT_SET_TIMING_NOTCONBIN_TYPE:
				{
					struct v4l2_ext_vbe_output_timing *p = &_g_v4l2_vbe_output_timing;

					BE_NOTI("V4L2_CID_EXT_VBE_OUTPUT_TIMING type:%d\n",param.setType);

					if (!param.pTimingParam)
					{
						BE_ERROR("pTimingParam is null\n");
						return -EINVAL;
					}

					if (copy_from_user(p, (void __user *)param.pTimingParam,sizeof(struct v4l2_ext_vbe_output_timing)))
					{
						BE_ERROR("copy_from_user error for timing data\n");
						return -EFAULT;
					}

					ret = _vbe_V4L2_CID_EXT_VBE_OUTPUT_TIMING(p);
				}
				break;
#if 0
				case V4L2_EXT_VBE_OUTPUT_INIT_ALLTCONBINDATA_TYPE:
				{
					void *tcon_data = param.extraInfo;
			
					if (!tcon_data || !param.sizer_extraInfo)
					{
						BE_ERROR("Invalid tcon.bin data\n");
						return -EINVAL;
					}

					// tcon.bin 데이터 저장 (LG 드라이버의 실제 함수로 구현 필요)
					ret = OVI_HAL_SetTconBinData(tcon_data, param.sizer_extraInfo);
					if (ret) {
						BE_ERROR("OVI_HAL_SetTconBinData error(%d)\n", ret);
						return ret;
					}

					BE_NOTI("Initialized tcon.bin data, size=%llu\n", param.sizer_extraInfo);
				}
				break;

				case V4L2_EXT_VBE_OUTPUT_SELECT_ONETCONDATA_TYPE:
				{
					void *tcon_data = param.extraInfo;

					if (!tcon_data) {
						BE_ERROR("Invalid tcon data for selection\n");
						return -EINVAL;
					}

					// tcon 데이터 선택 (LG 드라이버의 실제 함수로 구현 필요)
					ret = OVI_HAL_SelectTconData(tcon_data);
					if (ret)
					{
						BE_ERROR("OVI_HAL_SelectTconData error(%d)\n", ret);
						return -20; // SICREQ-1217 error code
					}

					BE_NOTI("Selected tcon data\n");
				}
				break;
#endif
				default:
					BE_ERROR("Invalid setType: %d\n", param.setType);
					return -EINVAL;
			}
		}
		break;

		default:
			return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_vbe_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct vbe_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			BE_TRACE8("(%s)(%s) [%d]id:0x%x(%s)\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,vbe_ctrl_id_to_str(ctrl->id));
			#endif

			ret = vbe_set_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int vbe_get_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		BE_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	if (_g_v4l2_vbe_cid_mask == ctrl->id)
	{
		BE_TRACE("cid_mask(%s) skip\n",vbe_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_vbe_compat_vidioc_ext_ctrls(ctrl);
	}
	#endif

	switch (ctrl->id) {
		case V4L2_CID_EXT_VBE_MPLUS_PARAM:
		{
			#if 0
			struct v4l2_ext_vbe_mplus_param param;
			UINT32 regVal;

			OVI_REG_RD(0xC907A230, regVal);
			param.nFrameGainLimit = (UINT16)((regVal & 0xFF) << 8);

			OVI_REG_RD(0xC907A234, regVal);
			param.nFrameGainLimit |= (UINT16)(regVal & 0xFF);

			OVI_REG_RD(0xC907A2DC, regVal);
			param.nPixelGainLimit = (UINT16)((regVal & 0xFF) << 8);

			OVI_REG_RD(0xC907A2E0, regVal);
			param.nPixelGainLimit |= (UINT16)(regVal & 0xFF);

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_mplus_param)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
			#endif
		}break;
		case V4L2_CID_EXT_VBE_MPLUS_DATA:
		{
			struct v4l2_ext_vbe_mplus_data param;
			LX_OVI_TCON_FW_DWLD_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_mplus_data)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if(param.pRegisterSet == NULL)
			{
				BE_ERROR("Data is null");
				ret = NOT_OK;
				break;
			}

			switch(param.nPanelMaker)
			{
				case 1:
					lxParam.type = LX_OVI_TCON_FW_BOE;
					lxParam.sizeNum = V4L2_BOE_MPLUS_LUT_SIZENUM;
					break;
				case 0:
				default :
					lxParam.type = LX_OVI_TCON_FW_LGD;
					lxParam.sizeNum = V4L2_LGD_MPLUS_LUT_SIZENUM;
					break;
			}
			lxParam.pData = param.pRegisterSet;
			lxParam.read = TRUE;

			ret = OVI_HAL_UpdateFirmware(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_UpdateFirmware error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_PWM_PARAM:
		{
			struct v4l2_ext_vbe_pwm_param param;
			struct v4l2_ext_vbe_pwm_param_data pwmData;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_pwm_param)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			pwmData.pwm_enable = pwmParams.portParams[param.pwmIndex].enable;
			pwmData.pwm_lock = pwmParams.portParams[param.pwmIndex].lockModeEn;
			pwmData.pwm_scanning_enable = pwmParams.portParams[param.pwmIndex].scanningModeEn;
			pwmData.pwm_low_power_enable = pwmParams.portParams[param.pwmIndex].lowPowerModeEn;
			pwmData.pwm_adapt_freq_param.pwm_adapt_freq_enable = pwmParams.portParams[param.pwmIndex].adaptFreqEn;
			pwmData.pwm_adapt_freq_param.pwmfreq_48nHz = pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_48nHz;
			pwmData.pwm_adapt_freq_param.pwmfreq_50nHz = pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_50nHz;
			pwmData.pwm_adapt_freq_param.pwmfreq_60nHz = pwmParams.portParams[param.pwmIndex].adaptFreqDb.freq_60nHz;
			pwmData.pwm_frequency = pwmParams.portParams[param.pwmIndex].frequency;
			pwmData.pwm_pos_start = pwmParams.portParams[param.pwmIndex].offset;
			pwmData.pwm_duty = pwmParams.portParams[param.pwmIndex].duty;

			if(copy_to_user((void __user *)param.pstPWMParam,&pwmData,sizeof(struct v4l2_ext_vbe_pwm_param_data)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}

			BE_NOTI("V4L2_CID_EXT_VBE_PWM_PARAM Port:%d, Enable:%d, Duty: %d, Freq: %d offset: %d, adpFreqEn: %d setFlag: %d, applyFlag: %d \n",
				param.pwmIndex,pwmData.pwm_enable,pwmData.pwm_duty,pwmData.pwm_frequency,pwmData.pwm_pos_start,
				pwmData.pwm_adapt_freq_param.pwm_adapt_freq_enable,gPwmSetParamIdxFlag,gPwmApplyParamIdxFlag);
		}break;
		case V4L2_CID_EXT_VBE_ALPHA_OSD:
		{
			struct v4l2_ext_vbe_panel_alpha_osd_info param;
			LX_BE_LUT_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_alpha_osd_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.pu32Data = param.alphaTable;
			lxParam.u32SizeNum = param.size/sizeof(UINT32);

			ret = BE_TOP_HAL_GetOSDAlphaAPL(&lxParam);
			if (ret)
			{
				BE_DEBUG("BE_TOP_HAL_GetOSDAlphaAPL error(%d)\n",ret);
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS:
		{
			struct v4l2_ext_vbe_panel_tpc_recovery_status_info param;
			LX_BE_LUT_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.pu32Data = param.tpcStatusTable;
			lxParam.u32SizeNum = param.table_size/sizeof(UINT32);

			ret = BE_TOP_HAL_GetTPCStatus(&lxParam);
			if (ret)
			{
				BE_DEBUG("BE_TOP_HAL_GetTPCStatus error(%d)\n",ret);
				break;
			}

			param.table_size = lxParam.u32SizeNum * sizeof(UINT32);

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}

		}break;
		case V4L2_CID_EXT_VBE_DEMURA :
		{
			struct v4l2_ext_vbe_panel_demura param;
			LX_OVI_TCON_DEMURA_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_demura)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.bIsGet = TRUE;
			lxParam.bEnable = param.enable;
			lxParam.pu8Config = param.config;
			lxParam.u32ConfigSize = param.configsize;
			lxParam.pu8Data = (UINT32 *)param.data;
			lxParam.u32DataSize = param.datasize;

			ret = OVI_HAL_SetDemura(&lxParam);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetDemura error(%d)\n",ret);
				break;
			}

			param.enable = lxParam.bEnable;

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_panel_demura)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_PCLRC :
		{
			struct v4l2_ext_vbe_panel_pclrc param;
			LX_OVI_PCLRC_LUT_T lxParams;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_pclrc)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			if (param.data == NULL)
			{
				BE_ERROR("param.data is null\n");
				return -EINVAL;
			}

			lxParams.pData =param.data;
			lxParams.sizeNum = param.datasize;
			lxParams.bIsGet = TRUE;

			ret = OVI_HAL_SetPCLRC(&lxParams);
			if (ret)
			{
				BE_ERROR("OVI_HAL_SetPCLRC error(%d)\n",ret);
				break;
			}

			param.enable = lxParams.enable;
			param.positionAfterLineOD = lxParams.path;

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_panel_pclrc)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
		}break;
		case V4L2_CID_EXT_ID_VBE_GET_GENLOCK :
		{
			struct v4l2_ext_get_vbe_genlock param;
			BE_PRINT("===============================================V4L2_CID_EXT_ID_VBE_GET_GENLOCK vbe_get_ctrl\n");
			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_get_vbe_genlock)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}
#if 0
			data.genlock_OnOff = gGenlock.genlock_OnOff;
			data.genlock_PortSelect = gGenlock.genlock_PortSelect;
			data.genlock_Status = gGenlock.genlock_Status;
			data.genlock_Status_Phase = gGenlock.genlock_Status_Phase;
			data.phaseShift = gGenlock.phaseShift;
#endif
			param.genlock_status = gGenlock.genlock_status;
			BE_PRINT("===============================================Get Genlock%d\n",param.genlock_status);
			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_get_vbe_genlock)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
		}break;
		case V4L2_CID_EXT_VBE_VAC_PARAM:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VAC_PARAM\n");
		}break;
		case V4L2_CID_EXT_VBE_VAC_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VAC_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_VDF_CONTROL:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VDF_CONTROL\n");
		}break;
		case V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM\n");
		}break;
		case V4L2_CID_EXT_VBE_GET_APL_FOR_TPC:
		{
			struct v4l2_ext_vbe_panel_tpc_apl_info param;
			LX_BE_LUT_T lxParam;

			if(copy_from_user(&param,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info)))
			{
				BE_ERROR("copy_from_user error\n");
				ret = NOT_OK;
				break;
			}

			lxParam.pu32Data = param.tpcAplInfoTable;
			lxParam.u32SizeNum = param.table_size/sizeof(UINT32);

			/* implement here */
			ret = BE_TOP_HAL_GetAplForTpc(&lxParam);
			if (ret)
			{
				BE_DEBUG("BE_TOP_HAL_GetAplForTpc error(%d)\n",ret);
				break;
			}

			param.table_size = lxParam.u32SizeNum * sizeof(UINT32);
#if 0
			if (g_v4l2_vbe_dbg_param == 1)	//for debug
			{
				static UINT32 cnt = 0;
				UINT32 p[4],n;
				for (n=0;n<4;n++)	{p[n] = cnt+n;}
				cnt++;
				if (copy_to_user((void __user *)param.tpcAplInfoTable,p,param.table_size))
				{
					BE_ERROR("copy_to_user error\n");ret = NOT_OK;break;
				}
				BE_NOTI("d:0x%08x,0x%08x,0x%08x,0x%08x (%d,%d,%d,%d)\n",p[0],p[1],p[2],p[3],p[0],p[1],p[2],p[3]);
			}
#endif
			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}

		}break;
#ifdef V4L2_VBE_USE_ID_SIGNAGE_CID
		case V4L2_CID_EXT_VBE_FRAME_RATE:
		{
#ifdef INCLUDE_KDRV_DE
			struct v4l2_ext_vbe_frame_rate param;
			LX_DE_FR_RATE_T lxParam;

			ret = resource_mgr_ioctl(DE_IOR_GET_OUT_FR_RATE,(unsigned long)&lxParam,1); //de_kwrap_getoutfrrate((BOOLEAN *)&param.on_off, (UINT16 *)&param.frameRate);
			if (ret)
			{
				BE_ERROR("DE_IOR_GET_OUT_FR_RATE error(%d)\n",ret);
				break;
			}

			param.frameRate = lxParam.fr_rate;
			param.on_off = lxParam.isForceFreeRun;

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_frame_rate)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
#endif
		}break;
#endif
		case V4L2_CID_EXT_ID_VBE_FRAME_RATE:
		{
#ifdef INCLUDE_KDRV_DE
			struct v4l2_ext_vbe_frame_rate param;
			LX_DE_FR_RATE_T lxParam;

			ret = resource_mgr_ioctl(DE_IOR_GET_OUT_FR_RATE,(unsigned long)&lxParam,1);
			if (ret)
			{
				BE_ERROR("DE_IOR_GET_OUT_FR_RATE error(%d)\n",ret);
				break;
			}

			param.frameRate = lxParam.fr_rate;
			param.on_off = lxParam.isForceFreeRun;

			if(copy_to_user((void __user *)ctrl->string,&param,sizeof(struct v4l2_ext_vbe_frame_rate)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}
#endif
		}break;

		case V4L2_CID_EXT_VBE_DCLK_MODE:
		{
			if(copy_to_user((void __user *)ctrl->string,&_g_v4l2_vbe_dclock,sizeof(enum v4l2_ext_vbe_dclk_mode)))
			{
				BE_ERROR("copy_to_user error\n");
				ret = NOT_OK;
				break;
			}

			BE_NOTI("V4L2_CID_EXT_VBE_DCLK_MODE:%x\n",_g_v4l2_vbe_dclock);
		}break;
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
		{
			//Not support V4L2_CID
			BE_DEBUG("Not Support V4L2_CID_EXT_ID_VBE_UCR_DATA\n");
		}break;
		case V4L2_CID_EXT_VBE_OBJECT_APL:
		{
			if (_gp_object_apl) {
				LX_BE_LED_object_apl *p = _gp_object_apl;

				ret = BE_LED_HAL_GetObjectApl(p);
				if (ret) {
					BE_ERROR("BE_LED_HAL_GetObjectApl error(%d)\n",ret);
					break;
				}

				if (copy_to_user((void __user *)ctrl->string,p,sizeof(LX_BE_LED_object_apl))) {
					BE_ERROR("copy_to_user error\n");
					ret = NOT_OK;
					break;
				}

				BE_PRINT_OBJ("obj apl %x %3d %3d %3d|%3d %3d %3d|%3d %3d %3d\n",\
					p->detection_flag,\
					p->apl[20][10],p->apl[40][10],p->apl[60][10],\
					p->apl[20][20],p->apl[40][20],p->apl[60][20],\
					p->apl[20][30],p->apl[40][30],p->apl[60][30]);
			} else {
				BE_PRINT_OBJ("check probe or not support\n");
			}
		}break;

		default:
			return -EINVAL;
	}
	return ret;
}


static int v4l2_vbe_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct vbe_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			BE_TRACE8("(%s)(%s) [%d]id:0x%x(%s)\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,vbe_ctrl_id_to_str(ctrl->id));
			#endif

			if (ctrl->id != V4L2_CID_EXT_VBE_ALPHA_OSD && ctrl->id != V4L2_CID_EXT_VBE_GET_APL_FOR_TPC)
				BE_PRINT("[%d]vbe:id 0x%x (%s)\n", i, ctrl->id, vbe_ctrl_id_to_str(ctrl->id));

			ret = vbe_get_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;
}

static int v4l2_vbe_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	//struct vbe_fh *fh = __fh;

	strncpy(cap->card, "v4l2_vbe", sizeof(cap->card)-1);
	strncpy(cap->driver, "v4l2_vbe", sizeof(cap->driver)-1);
	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	return 0;

}

static int v4l2_vbe_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	//struct vbe_fh *fh = __fh;
	//int ret;

	BE_PRINT("vbe: set input %d\n", i);

	return 0;
}

static int v4l2_vbe_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	//struct vbe_fh *fh = __fh;
	//int ret;

	BE_PRINT("vbe: get input %d\n", *i);

	return 0;
}


struct vbe_priv *pdev_vsync = NULL;

int vbe_vsync_notification(void)
{
	struct video_device *vdev;
//	struct vbe_dev *dev;
	struct v4l2_event cap_event;
	struct vbe_dev *drv;

	if(pdev_vsync==NULL) return 0;
	vdev = pdev_vsync->vdev;
	if (!vdev) {BE_ERROR("vdev null\n");return -1;}
	drv = video_get_drvdata(vdev);
	if (!drv) {BE_ERROR("drv null\n");return -1;}

	memset(&cap_event, 0, sizeof(cap_event));
	cap_event.type        = V4L2_EVENT_VSYNC;
	cap_event.id = V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC;

	v4l2_event_queue(drv->vdev, &cap_event);

	return 0;
}

static int v4l2_vbe_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub)
{
	struct vbe_priv *priv;
	struct video_device *vdev;
	struct vbe_fh *pvbe_fh = container_of(__fh, struct vbe_fh, fh);

	if (!__fh)	 {BE_ERROR("__fh null\n");	return -EINVAL;}
	if (!sub)	 {BE_ERROR("sub null\n");	return -EINVAL;}
	if (!pvbe_fh){BE_ERROR("pvbe_fh null\n");return -EINVAL;}

	priv = pvbe_fh->vbe_priv;
	if (!priv){BE_ERROR("priv null\n");return -EINVAL;}
	vdev = priv->vdev;
	if (!vdev){BE_ERROR("vdev null\n");return -EINVAL;}

	BE_NOTI("%s type 0x%x, id 0x%x (base:0x%x) (%s-%s)\n",vdev->name,sub->type,sub->id,V4L2_CID_EXT_VBE_BASE,current->group_leader->comm,current->comm);

	if(sub->id == V4L2_CID_EXT_VBE_SUBSCRIBE_DPC)
	{
		if (vbe_led_subscribe_event(priv)) {
			BE_ERROR("vbe_led_subscribe_event err\n");
			return -EINVAL;
		}
	}
	else if(sub->id == V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC)
	{
		pdev_vsync = priv;
	}

	BE_NOTI("done\n");
	return v4l2_event_subscribe(__fh, sub, 32, NULL);
}

static int v4l2_vbe_vidioc_unsubscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub)
{
	struct vbe_priv *priv;
	struct video_device *vdev;
	struct vbe_fh *pvbe_fh = container_of(__fh, struct vbe_fh, fh);

	if (!__fh)	 {BE_ERROR("__fh null\n");	return -EINVAL;}
	if (!sub)	 {BE_ERROR("sub null\n");	return -EINVAL;}
	if (!pvbe_fh){BE_ERROR("pvbe_fh null\n");return -EINVAL;}

	priv = pvbe_fh->vbe_priv;
	if (!priv){BE_ERROR("priv null\n");return -EINVAL;}
	vdev = priv->vdev;
	if (!vdev){BE_ERROR("vdev null\n");return -EINVAL;}

	BE_NOTI("%s type 0x%x, id 0x%x (base:0x%x) (%s-%s)\n",vdev->name,sub->type,sub->id,V4L2_CID_EXT_VBE_BASE,current->group_leader->comm,current->comm);

	if(sub->id == V4L2_CID_EXT_VBE_SUBSCRIBE_DPC)
	{
		if (vbe_led_unsubscribe_event(priv)) {
			BE_ERROR("vbe_led_unsubscribe_event err\n");
			return -EINVAL;
		}
	}
	else if(sub->id == V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC)
	{
		pdev_vsync = NULL;
	}

	BE_NOTI("done\n");
	return v4l2_event_unsubscribe(__fh, sub);
}

static unsigned int v4l2_vbe_poll(struct file *file, poll_table *wait)
{
	struct vbe_fh *fh = (struct vbe_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	BE_TRACE7("vbe:req_events 0x%lx\n", req_events);

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

	BE_TRACE7("vbe: rc 0x%x\n", rc);

	return rc;
}

char *vbe_ctrl_id_to_str(int id)
{
	#define VBE_CASE_ID_TO_STR(_x)		case (_x):return #_x

    switch (id)
	{
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_INIT			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_RESUME			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_DISPLAYOUTPUT	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PCCE			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MUTE			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_SSC 			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MIRROR			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MPLUS_BOEBYPASS   );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MPLUS_MODE		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_DGA4CH			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MPLUS_PARAM 	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_INNER_PATTERN	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_TSCIC			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_EPI_SCRAMBLE	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_EPI_10BIT		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_MPLUS_DATA		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PWM_APPLY_PARAM   );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PWM_PARAM		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PWM_INIT		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VCOM_PAT_DRAW	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VCOM_PAT_CTRL	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PWM_SET_DUTY	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_ORBIT			  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_LSR				  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_CPC				  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_GSR	  		      );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_GSR2	  		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_OSD_GAIN		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_ALPHA_OSD		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_GSR_STATUS		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_LOCK_STATUS		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_GSR_STRESS_COUNT  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_DEMURA  		  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_PCLRC  		      );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM    );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_IRR_RESULT  	  );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VAC_PARAM);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VAC_CONTROL);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VDF_CONTROL);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_GET_APL_FOR_TPC);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_DCLK_MODE);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_ID_VBE_UCR_DATA);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_ID_VBE_SET_GENLOCK );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_ID_VBE_GET_GENLOCK );
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_OBJECT_APL_GAIN);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_OBJECT_APL);
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_OUTPUT_TIMING);
#ifdef V4L2_VBE_USE_ID_SIGNAGE_CID
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_VBE_FRAME_RATE);
#endif
		VBE_CASE_ID_TO_STR(V4L2_CID_EXT_ID_VBE_FRAME_RATE);
		default:				return "V4L2_CID_EXT_UNKOWN";
	}
}

static int v4l2_vbe_register(void *arg)
{
	int ret;
	struct vbe_dev *drv;

	BE_PRINT("vbe  %s\n", __func__);

    /* allocate main vivid state structure */
	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_vbe_pdev.dev, &v4l2_vbe_dev);
		if(ret < 0){
			BE_ERROR(" vbe : v4l2_device_register error[%d]\n", ret);
			break;
		}

		drv->pdev = &v4l2_vbe_pdev;
		drv->v4l2_dev = &v4l2_vbe_dev;
		drv->vdev = &v4l2_vbe_video_dev;
#ifdef INCLUDE_KDRV_PQE_PM
		drv->pqe_pm_cfg = &v4l2_vbe_pqe_pm_cfg;
#endif
		video_set_drvdata(&v4l2_vbe_video_dev, drv);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(&v4l2_vbe_video_dev, VFL_TYPE_VIDEO, V4L2_VBE_MINOR_NUMBER);
#else
		ret = video_register_device(&v4l2_vbe_video_dev, VFL_TYPE_GRABBER, V4L2_VBE_MINOR_NUMBER);
#endif
		if (ret < 0) {
			BE_ERROR("video device register error: %d\n", ret);
			return -1;
		}
	} while(0);

	return ret;
}

int v4l2_vbe_set_latency_pattern(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_latency_pattern_info *p)
{
	int ret = 0;
	LX_BE_INPUT_LAG_PATTERN_T param;

	if(!p) return -1;
	if(p->r.w > 0 && p->r.h > 0)
		param.enable = 1;
	else
		param.enable = 0;

	param.type = p->p;
	param.hoffset = p->r.x;
	param.voffset = p->r.y;
	param.hsize = p->r.w;
	param.vsize = p->r.h;
	ret = BE_TOP_HAL_SetInputLagPattern(&param);

	BE_NOTI("Latency measure  color[%d], rect[%dx%d]", param.type, param.hsize, param.vsize);

	return ret;
}

static void _vbe_push_log_buf(int type, char *data)
{
	UINT32 i, usec;
	static UINT32 cnt = 0;
	struct vbe_backuplog *p_buf = NULL;

	if (!data)	return;

	if (type == VBE_BACKUP_LOG_TYPE_PWM)	p_buf = _gp_vbe_backuplog_buf;

	if (!p_buf)	return;

	if (cnt >= VBE_BACKUP_LOG_BUF_MAX)	cnt = 0;

	OS_GetCurrentTicks(&(p_buf[cnt].sec),&(p_buf[cnt].msec),&usec);
	memset(p_buf[cnt].str,0,VBE_BACKUP_LOG_STR_SIZE);
	for(i=0;i<VBE_BACKUP_LOG_STR_SIZE;i++)
	{
		p_buf[cnt].str[i] = data[i];
		if(data[i] == 0) break;
	}

	cnt++;
}

int v4l2_vbe_dbg_get_pwm_duty(char* buffer)
{
	int i, len = 0;
	struct vbe_backuplog *p_buf = _gp_vbe_backuplog_buf;

	len += sprintf( buffer+len, "usage : echo [sel] [duty] > pwm_duty\n");
	if (!_gp_vbe_backuplog_buf)
	{
		len += sprintf( buffer+len, "backuplog_buf null\n");
		return len;
	}

	for (i=0; i<VBE_BACKUP_LOG_BUF_MAX; i++)
	{
		if (0 == strlen(p_buf[i].str))	continue;
		len += sprintf( buffer+len, "[%2d][%06d.%03d] %s",i,p_buf[i].sec,p_buf[i].msec,p_buf[i].str);
	}

	return len;
}

int v4l2_vbe_dbg_set_pwm_duty(char* command)
{
	UINT32 sel, duty;
	LX_BE_PWM_PARAMS_T param;

	if (!command)	return -1;

	sscanf(command," %d %d",&sel,&duty);
	memset(&param,0,sizeof(param));

	duty &= 0xff;

	if (sel >= 1000)
	{
		param.portMask = 0x2;
		param.portParams[1].enable         = 1;
		param.portParams[1].lockModeEn     = 0;
		param.portParams[1].pwmOutput      = param.portParams[1].enable;
		param.portParams[1].scanningModeEn = 0;
		param.portParams[1].lowPowerModeEn = 0;
		param.portParams[1].adaptFreqEn    = 0;
		param.portParams[1].adaptFreqDb.freq_48nHz = 96;
		param.portParams[1].adaptFreqDb.freq_50nHz = 100;
		param.portParams[1].adaptFreqDb.freq_60nHz = 120;
		param.portParams[1].frequency = sel;
		param.portParams[1].offset = 0;
		param.portParams[1].duty = duty;
		BE_PWM_HAL_SetPwmParams(&param);
	}
	else if (sel == 1)
	{
		param.portMask = 0x1;
		param.portParams[0].enable         = 1;
		param.portParams[0].lockModeEn     = 0;
		param.portParams[0].pwmOutput      = param.portParams[0].enable;
		param.portParams[0].scanningModeEn = 0;
		param.portParams[0].lowPowerModeEn = 0;
		param.portParams[0].adaptFreqEn    = 0;
		param.portParams[0].adaptFreqDb.freq_48nHz = 0;
		param.portParams[0].adaptFreqDb.freq_50nHz = 0;
		param.portParams[0].adaptFreqDb.freq_60nHz = 0;
		param.portParams[0].frequency = 200;
		param.portParams[0].offset = 0;
		param.portParams[0].duty = duty;
		BE_PWM_HAL_SetPwmParams(&param);

		param.portMask = 0x2;
		param.portParams[1].enable         = 1;
		param.portParams[1].lockModeEn     = 0;
		param.portParams[1].pwmOutput      = param.portParams[1].enable;
		param.portParams[1].scanningModeEn = 0;
		param.portParams[1].lowPowerModeEn = 0;
		param.portParams[1].adaptFreqEn    = 1;
		param.portParams[1].adaptFreqDb.freq_48nHz = 96;
		param.portParams[1].adaptFreqDb.freq_50nHz = 100;
		param.portParams[1].adaptFreqDb.freq_60nHz = 120;
		param.portParams[1].frequency = 0;
		param.portParams[1].offset = 0;
		param.portParams[1].duty = duty;
		BE_PWM_HAL_SetPwmParams(&param);
	}
	else
	{
		param.portMask = 0x3;
		param.portParams[0].enable         = 1;
		param.portParams[0].lockModeEn     = 0;
		param.portParams[0].pwmOutput      = param.portParams[0].enable;
		param.portParams[0].scanningModeEn = 0;
		param.portParams[0].lowPowerModeEn = 0;
		param.portParams[0].adaptFreqEn    = 1;
		param.portParams[0].adaptFreqDb.freq_48nHz = 96;
		param.portParams[0].adaptFreqDb.freq_50nHz = 100;
		param.portParams[0].adaptFreqDb.freq_60nHz = 120;
		param.portParams[0].frequency = 0;
		param.portParams[0].offset = 0;
		param.portParams[0].duty = duty;
		param.portParams[1].enable         = 1;
		param.portParams[1].lockModeEn     = 0;
		param.portParams[1].pwmOutput      = param.portParams[1].enable;
		param.portParams[1].scanningModeEn = 0;
		param.portParams[1].lowPowerModeEn = 0;
		param.portParams[1].adaptFreqEn    = 1;
		param.portParams[1].adaptFreqDb.freq_48nHz = 96;
		param.portParams[1].adaptFreqDb.freq_50nHz = 100;
		param.portParams[1].adaptFreqDb.freq_60nHz = 120;
		param.portParams[1].frequency = 0;
		param.portParams[1].offset = 0;
		param.portParams[1].duty = duty;
		BE_PWM_HAL_SetPwmParams(&param);
	}

	return 0;
}

int v4l2_vbe_dbg_obj_apl_help(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "usage : echo [sel] > obj_apl\n");
	len += sprintf( buffer+len, "sel 0 : call BE_LED_HAL_GetObjectApl (cat obj/status for result)\n");
	return len;
}

int v4l2_vbe_dbg_obj_apl_test(char* command)
{
	UINT32 sel;

	if (!command)	return -1;

	sscanf(command," %d",&sel);

	if (sel == 0)
	{
		if (_gp_object_apl) {
			BE_LED_HAL_GetObjectApl(_gp_object_apl);
		} else {
			BE_NOTI("not support\n");
		}
	} else {
		BE_NOTI("see help\n");
	}

	return 0;
}

extern void vbe_evt_status(struct seq_file *m, void* data);
extern void vbe_dpc_status(struct seq_file *m, void* data);
void vbe_status(struct seq_file *m, void* data)
{
	int type = (int)(uintptr_t)data;

	if (type == 2) {
		vbe_param_status(m,data);
	} else if (type == 1) {
		vbe_obj_status(m,data);
	} else {
		struct vbe_dev *drv = video_get_drvdata(&v4l2_vbe_video_dev);
		if (drv->led_task.thread) {
			seq_printf(m, "led_task : cond:%d, ev_sub:0x%x, tx,rx:%3d,%3d\n",\
				drv->led_task.cond,drv->led_task.ev_sub,\
				drv->led_task.tx_cnt,drv->led_task.rx_cnt);
		}
		vbe_evt_status(m,data);
		vbe_dpc_status(m,data);
	}
}

#define VBE_SYNC_HANDLER_EVENT (0)
#define VBE_SYNC_HANDLER_POC   (1)
#define VBE_SYNC_HANDLER_NONE  (2)
#define VBE_SYNC_SHORT_INTERVAL_MS (5)
int vbe_sync_handler(void)
{
	static UINT64 prev_tick = 0;
	UINT64 curr_tick = OS_GetMsecTicks();
	UINT64 diff_tick;

	if (lx_chip() < LX_CHIP_O24) {
		BE_PRINT_SYN("wakeup(%d):not support\n",g_v4l2_vbe_dbg_param);
		return 0;
	}

	diff_tick = (curr_tick > prev_tick)? (curr_tick-prev_tick):0;
	prev_tick = curr_tick;

	if (diff_tick < VBE_SYNC_SHORT_INTERVAL_MS) {
		BE_NOTI("skip(%d)(d:%llu)\n",g_v4l2_vbe_dbg_param,diff_tick);
		return 0;
	}

	BE_PRINT_SYN("wakeup(%d)(d:%llu)\n",g_v4l2_vbe_dbg_param,diff_tick);
	if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_EVENT) {
		vbe_led_wakeup(video_get_drvdata(&v4l2_vbe_video_dev), 0);
	}
	else if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_POC) {
		vbe_dpc_sync_handler();
	}

	return 0;
}

int vbe_noti_chg_clk_wait(void)
{
	if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_POC) {
		vbe_dpc_noti_chg_clk_wait();
	}
	else if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_EVENT) {
		vbe_evt_noti_chg_clk_wait();
	}
	return 0;
}

int vbe_noti_chg_clk_done(unsigned int clk)
{
	if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_POC) {
		vbe_dpc_noti_chg_clk_done(clk);
	}
	else if (g_v4l2_vbe_dbg_param == VBE_SYNC_HANDLER_EVENT) {
		vbe_evt_noti_chg_clk_done(clk);
	}
	return 0;
}

static void vbe_obj_status(struct seq_file *m, void* data)
{
	unsigned int i, num;
	LX_BE_LED_object_apl *p = _gp_object_apl;
	LX_BE_LED_object_apl_gain *p_gain;

	seq_printf(m, ".object_apl_gain\n");
	num = sizeof(_g_object_apl_gain)/sizeof(_g_object_apl_gain[0]);
	for (i=0; i<num; i++) {
		p_gain = &_g_object_apl_gain[i];
		seq_printf(m, "id:%x en:%x g:%x x:%x,%x,%x,%x y:%x,%x,%x,%x\n",\
			p_gain->id,p_gain->enable,p_gain->master_gain,\
			p_gain->gain_x[0],p_gain->gain_x[1],p_gain->gain_x[2],p_gain->gain_x[3],\
			p_gain->gain_y[0],p_gain->gain_y[1],p_gain->gain_y[2],p_gain->gain_y[3]);
	}

	if (_gp_object_apl) {
		seq_printf(m, "._gp_object_apl (flag:%x)\n",p->detection_flag);
		for (i=0; i<40; i++) {
			seq_printf(m, "[ 0][%2d] %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|"\
				"%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",i,\
				p->apl[0][i], p->apl[1][i], p->apl[2][i], p->apl[3][i], p->apl[4][i], p->apl[5][i], p->apl[6][i], p->apl[7][i], p->apl[8][i], p->apl[9][i],\
				p->apl[10][i],p->apl[11][i],p->apl[12][i],p->apl[13][i],p->apl[14][i],p->apl[15][i],p->apl[16][i],p->apl[17][i],p->apl[18][i],p->apl[19][i],\
				p->apl[20][i],p->apl[21][i],p->apl[22][i],p->apl[23][i],p->apl[24][i],p->apl[25][i],p->apl[26][i],p->apl[27][i],p->apl[28][i],p->apl[29][i],\
				p->apl[30][i],p->apl[31][i],p->apl[32][i],p->apl[33][i],p->apl[34][i],p->apl[35][i],p->apl[36][i],p->apl[37][i],p->apl[38][i],p->apl[39][i]);
			seq_printf(m, "[40][%2d] %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|"\
				"%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d|%3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",i,\
				p->apl[40][i],p->apl[41][i],p->apl[42][i],p->apl[43][i],p->apl[44][i],p->apl[45][i],p->apl[46][i],p->apl[47][i],p->apl[48][i],p->apl[49][i],\
				p->apl[50][i],p->apl[51][i],p->apl[52][i],p->apl[53][i],p->apl[54][i],p->apl[55][i],p->apl[56][i],p->apl[57][i],p->apl[58][i],p->apl[59][i],\
				p->apl[60][i],p->apl[61][i],p->apl[62][i],p->apl[63][i],p->apl[64][i],p->apl[65][i],p->apl[66][i],p->apl[67][i],p->apl[68][i],p->apl[69][i],\
				p->apl[70][i],p->apl[71][i],p->apl[72][i],p->apl[73][i],p->apl[74][i],p->apl[75][i],p->apl[76][i],p->apl[77][i],p->apl[78][i],p->apl[79][i]);
		}
	}
}

static void vbe_param_status_id(struct seq_file *m, void* data, int id)
{
	if (!m)	return;

	seq_printf(m, "%s=",vbe_ctrl_id_to_str(id)+13);

	if (id == V4L2_CID_EXT_VBE_OUTPUT_TIMING) {
		struct v4l2_ext_vbe_output_timing *p = &_g_v4l2_vbe_output_timing;
		seq_printf(m, "fr:%d %d %d %d %d %d %d %d %d h,v:%d,%d %d %d\n",p->frameRate,\
			p->hTotal,p->vTotal,p->hSyncWidth,p->vSyncWidth,p->hBlank,p->vBlank,p->hBackPorch,p->vBackPorch,\
			p->hResolution,p->vResolution,p->minVTotal,p->maxVTotal);
	} else if (id == V4L2_CID_EXT_VBE_DCLK_MODE) {
		seq_printf(m, "%d\n",_g_v4l2_vbe_dclock);
	} else if (id == V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ) {
		seq_printf(m, "%d\n",_g_v4l2_vbe_displayoutput_5060hz);
	} else {
		seq_printf(m, "{not support}\n");
	}
}

static void vbe_param_status(struct seq_file *m, void* data)
{
	if (!m)	return;

	vbe_param_status_id(m,data,V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ);
	vbe_param_status_id(m,data,V4L2_CID_EXT_VBE_DCLK_MODE);
	vbe_param_status_id(m,data,V4L2_CID_EXT_VBE_OUTPUT_TIMING);
}

int v4l2_vbe_dbg_dispout_help(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "usage : echo [sel] [val] > dispout\n");
	len += sprintf( buffer+len, "sel:0(V4L2_CID_EXT_VBE_OUTPUT_TIMING) val:120,144,165,240,288,330\n");
	len += sprintf( buffer+len, "sel:1(V4L2_CID_EXT_VBE_DCLK_MODE) val:0(basic),1(165),2(144)\n");
	len += sprintf( buffer+len, "sel:2(V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ) val:0(120),1(60)\n");
	return len;
}

int v4l2_vbe_dbg_dispout_test(char* command)
{
	UINT32 sel, val;

	if (!command)	return -1;

	sscanf(command," %d %d",&sel,&val);

	if (sel == 0) {
		struct v4l2_ext_vbe_output_timing t;
		t.frameRate = (int)val;
		t.hResolution = 3840;
		t.vResolution = (val<200)? 2160:1080;
		_vbe_V4L2_CID_EXT_VBE_OUTPUT_TIMING(&t);
	} else if (sel == 1) {
		_vbe_V4L2_CID_EXT_VBE_DCLK_MODE(val);
	} else if (sel == 2) {
		_vbe_V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ((int)val);
	} else {
		BE_NOTI("see help\n");
	}

	return 0;
}
