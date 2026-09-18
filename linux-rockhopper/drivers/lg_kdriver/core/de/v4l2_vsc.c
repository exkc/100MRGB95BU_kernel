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
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/pm_runtime.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "base_device.h"
#include "de_def.h"
#include "de_io.h"
#include "de_sync.h"
#include "de_drv.h"
#include "hal/ipc_phys_hal.h"
#include "hal/ipc_hal.h"
#include "hal/de_hal.h"
#include "mcu/de_ipc.h"
#include "mcu/de_int.h"

#include "resource_mgr.h"
#include "v4l2_vsc_event.h"

#include "vsc/hal_vsc_hwrap.h"
#include "vp_kwrap.h"

#include "v4l2_vt.h"
#include "v4l2_gps.h"
#include "v4l2_dolby.h"
//#include "v4l2_ibuf.h"

#include "be_kapi.h"
#ifdef INCLUDE_KDRV_BE
#include "v4l2_vbe.h"
#endif

#include "vsc_bbd.h"

#include "vsc_bwm.h"
#include "vsc_fw.h"

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

#ifdef INCLUDE_KDRV_BE
#include "be_kapi.h"
#include "../be/be_def.h"
#include "../be/frc/frc_hal.h"
#endif

#ifdef INCLUDE_KDRV_OVI
#include "ovi_hal.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_VIDEO_MINOR_NUMBER  V4L2_EXT_DEV_NO_SCALER0

#define V4L2_VSC_FW_DL_TIME_OUT		1000
#define V4L2_VSC_FW_DL_INC_MAX		(V4L2_VSC_FW_DL_TIME_OUT+(V4L2_VSC_FW_DL_TIME_OUT>>1))

/* 20210602, Instant Boot (SICDTV-9992) */
#define V4L2_VSC_APPLY_FREEZABLE

#define V4L2_VSC_BBD_WAITQUEUE
#define V4L2_VSC_RETURN_PUNCH // Y26 -  https://harmony.lge.com:8443/issue/browse/SICREQ-1159
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* SCDCR-4006 */
#define VSC_PM_INFO(_level,_num,_type,_result)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::vsc\n",\
			_level,"video",_num,_g_v4l2_vsc_open_count,\
			current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vsc_priv
{
	struct list_head list;

	/* vsc  */
	int vsc_poll;
	wait_queue_head_t vsc_poll_wq;
	void (*process_poll)(struct vsc_priv *v);
	struct work_struct vsc_noti_work;
	struct video_device *vsc_vdev;
	unsigned int event;
	unsigned int ev_size;
	unsigned char ev_data[64];
	struct task_struct *update_win_thread;
	struct task_struct *resize_win_thread;
	struct task_struct *check_mute_thread;
	struct task_struct *check_delay_thread;
	struct task_struct *update_bbd_thread;
	pid_t bbd_tid;
	pid_t bbd_pid;
	#ifdef V4L2_VSC_BBD_WAITQUEUE
	wait_queue_head_t bbd_queue;
	int bbd_condition;
	#endif
};
struct vsc_priv *new_vsc_priv(void);

enum vsc_init_stat_enum {
	STAT_FW_CHK_START = 0,
	STAT_FW_CHK_0,
	STAT_FW_CHK_END,
	STAT_FW_DL_END,
	STAT_SUSPEND
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

struct vsc_dev {
	struct platform_device *pdev;
    struct v4l2_device v4l2_vsc_dev;
    struct video_device	v4l2_vsc_video_dev0;
    struct video_device	v4l2_vsc_video_dev1;
    struct video_device	v4l2_vsc_video_dev2;
    struct video_device	v4l2_vsc_video_dev3;
    struct video_device	v4l2_vsc_capture_dev;
    struct mutex        v4l2_vsc_video_device_lock;
    spinlock_t          slock;
    BOOLEAN             IsHalVscV4l2Open;
    struct task_struct *vp_thread;
	struct task_struct *vp_darc_thread;
#ifdef INCLUDE_KDRV_PQE_PM
	struct pqe_pm_config *pqe_pm_cfg;
	int pqe_pm_id;
#endif
};

struct vsc_fh {
	struct v4l2_fh fh;
// need to add some private data
	struct vsc_priv *vsc_priv;
	BOOLEAN IsMuteOffSubscribed;
	BOOLEAN IsWinEventSubscribed;
	unsigned int VideoDelay;
	BOOLEAN IsBspErrorSubscribed;
};
static struct v4l2_ext_vsc_active_win_info _g_act_info[LX_DE_WIN_MAX];
int v4l2_vsc_init_stat = STAT_FW_CHK_START;
extern int g_de_device_opened;
unsigned int t_vsc_sec_prv, t_vsc_msec_prv[LX_DE_WIN_MAX]={0,0,0,0}, t_vsc_sec_mute[LX_DE_WIN_MAX]={0,0,0,0}, t_vsc_msec_mute[LX_DE_WIN_MAX]={0,0,0,0};
LX_DE_RECT_T t_vsc_rect_prv[LX_DE_WIN_MAX] = { 0 };
LX_DE_RECT_T t_vsc_policy_punch[LX_DE_WIN_MAX] = { 0 };
unsigned int event_user[LX_DE_WIN_MAX] = { 0 };
unsigned int update_win_send_flag[LX_DE_WIN_MAX] = { 1 };

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static char *ctrl_id_to_str(int id);
static int minor_num_to_win_id(int num);
static char *ctrl_id_ext_to_str(int id);
static int v4l2_vsc_probe(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vsc_remove(struct platform_device *pdev);
#else
static int v4l2_vsc_remove(struct platform_device *pdev);
#endif
static int v4l2_vsc_resume(struct device *dev);
static int v4l2_vsc_suspend(struct device *dev);
static int v4l2_vsc_runtime_resume(struct device *dev);
static int v4l2_vsc_runtime_suspend(struct device *dev);

static int vsc_bbd_thread(void *ptr);

/* FOPS releated to V4L2 */
static int v4l2_dev_register(void *arg);
static void v4l2_vp_thread(void* data);
static void darc_thread(void *data);


static int vsc_update_resize_thread(void *data);
static int vsc_update_win_thread(void *data);
static int vsc_check_mute_thread(void *data);
static int vsc_check_delay_thread(void *data);

static int vsc_v4l2_report_csc_err(struct vsc_priv *p);
static int vsc_v4l2_report_fw_err(struct vsc_priv *p);
static int vsc_v4l2_report_ext_err(struct vsc_priv *p);

int v4l2_vsc_device_init(void);
int v4l2_vsc_de_init_late(unsigned int flag);
int vsc_suspend(int type);
int vsc_resume(int type);
int v4l2_vsc_pm_runtime_help(char* buffer);
int v4l2_vsc_pm_runtime_test(char* command);
void post_event(int win, int type, int val);
int vsc_bbd_simpletest(BOOLEAN flag, unsigned char wid);
int v4l2_vsc_getlocalmute(int win);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct task_struct *V4L2VscFwDlThread = NULL;
static int _g_v4l2_vsc_open_count = 0;
static int _g_v4l2_vsc_local_mute[4] = {0,0,0,0};

const char *_g_vsc_type_str[DE_DRV_PM_TYPE_MAX] = {"none","runpm","suspend","resume","freeze","thaw","restore"};

/*========================================================================================
	Implementation Group
========================================================================================*/


/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static struct platform_device v4l2_vsc_pdev = {
	.name = "v4l2_vsc",
	.id = -1,
};

static struct dev_pm_ops const vsc_pm_ops = {
        .resume = v4l2_vsc_resume,
        .suspend = v4l2_vsc_suspend,
        .runtime_resume = v4l2_vsc_runtime_resume,
        .runtime_suspend = v4l2_vsc_runtime_suspend,
};

static struct platform_driver v4l2_vsc_driver = {
	.probe      = v4l2_vsc_probe,
	.driver     = {
		.name   = "v4l2_vsc",
		.owner  = THIS_MODULE,
	.pm     = &vsc_pm_ops,
	},
	.remove		= v4l2_vsc_remove,
};

int v4l2_vsc_device_init(void)
//static int __init v4l2_vsc_device_init(void)
{
	DE_NOTI("vsc  %s\n", __func__);
	//platform_driver_register(&v4l2_vsc_driver);
	//platform_device_register(&v4l2_vsc_pdev);

	//video_set_drvdata(&v4l2_vsc_video_dev0, &vsc_pdev);
	v4l2_dev_register(NULL);

	return 0;
}
#if 0
static void __exit v4l2_vsc_device_exit(void)
{
	DE_NOTI("vsc  %s\n", __func__);

	platform_device_unregister(&v4l2_vsc_pdev);
	platform_driver_unregister(&v4l2_vsc_driver);
}
#endif
#ifdef INCLUDE_KDRV_PE
extern int vpq_hwrap_initialize(unsigned int resume_mode);
#endif
int v4l2_vsc_de_init_late(unsigned int flag)
{
	vsc_fw_init_late(flag);

	if (flag == CALL_FROM_USER)
	{
		v4l2_vsc_init_stat = STAT_FW_DL_END;

		#ifdef INCLUDE_KDRV_PE
		vpq_hwrap_initialize(0);
		#endif
	}

	DE_NOTI("done (stat:%d)(flag:%s)\n",v4l2_vsc_init_stat,(flag == CALL_FROM_USER)? "u":"k");
	return 0;
}

/* type : see enum de_drv_pm_type */
int vsc_suspend(int type)
{
	int ret = RET_OK;

	if (type < 0 || type >= DE_DRV_PM_TYPE_MAX)
	{
		DE_NOTI("type err(%d)\n",type);
		return RET_ERROR;
	}

	DE_NOTI("start (stat:%d)(type:%s)\n",v4l2_vsc_init_stat,_g_vsc_type_str[type]);

	if (type == DE_DRV_PM_TYPE_RUNTIME_PM)
	{
		vsc_fw_rpm(VSC_FW_FROM_RPM_SUSPEND);
	}

	v4l2_vsc_init_stat = STAT_SUSPEND;

	DE_NOTI("done (stat:%d)(type:%s)\n",v4l2_vsc_init_stat,_g_vsc_type_str[type]);

	return ret;
}

/* type : see enum de_drv_pm_type in de_drv.h */
int vsc_resume(int type)
{
	int ret = RET_OK;

	if (type < 0 || type >= DE_DRV_PM_TYPE_MAX)
	{
		DE_NOTI("type err(%d)\n",type);
		return RET_ERROR;
	}

	DE_NOTI("start (stat:%d)(type:%s)\n",v4l2_vsc_init_stat,_g_vsc_type_str[type]);

	if (type == DE_DRV_PM_TYPE_RUNTIME_PM)
	{
		vsc_fw_rpm(VSC_FW_FROM_RPM_RESUME);
	}
	else
	{
		int from = (type == DE_DRV_PM_TYPE_THAW)? VSC_FW_FROM_THAW:\
			(type == DE_DRV_PM_TYPE_RESTORE)? VSC_FW_FROM_RESTORE:VSC_FW_FROM_RESUME;

		if (VSC_FW_RET_SKIP == vsc_fw_download(from))
		{
			/* do nothing */
			v4l2_vsc_init_stat = STAT_SUSPEND;
			DE_NOTI("skipfw (stat:%d)\n",v4l2_vsc_init_stat);
			return RET_OK;
		}
	}

	v4l2_vsc_init_stat = STAT_FW_DL_END;

	DE_NOTI("done (stat:%d)(type:%s)\n",v4l2_vsc_init_stat,_g_vsc_type_str[type]);

	return ret;
}

static int v4l2_fw_dl_thread(void *data)
{
	int ret = RET_OK;
	//char s0[30];
	static int fw_dl_cnt = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
	mm_segment_t old_fs;
#endif
	struct file *test_filp;

	//ret = v4l2_fw_dl_reset_status();

	DE_NOTI("start (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);

	while(1)
	{
		do {
			if (v4l2_vsc_init_stat == STAT_FW_CHK_END)	break;
			if (v4l2_vsc_init_stat == STAT_SUSPEND)	break;

			/* check count(timeout) */
			if (fw_dl_cnt >= V4L2_VSC_FW_DL_TIME_OUT)
			{
				v4l2_vsc_init_stat = STAT_FW_CHK_END;
				DE_NOTI("check count (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);
			}

			/* check /var */
			if (v4l2_vsc_init_stat == STAT_FW_CHK_START)
			{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				set_fs(KERNEL_DS);
#else
				set_fs(get_ds());
#endif
#endif
				//test_filp = filp_open("/var/temp", O_RDWR|O_CREAT, 0644);
				test_filp = filp_open("/var", O_RDONLY, 0);
				if (!IS_ERR(test_filp))
				{
					v4l2_vsc_init_stat = STAT_FW_CHK_0;
					DE_NOTI("CHK_S (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);
					filp_close(test_filp, NULL);
				}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				set_fs(old_fs);
#endif
			}

			/* check /var/firmware */
			if (v4l2_vsc_init_stat == STAT_FW_CHK_0)
			{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				set_fs(KERNEL_DS);
#else
				set_fs(get_ds());
#endif
#endif
				test_filp = filp_open("/var/firmware", O_RDONLY, 0);
				if (!IS_ERR(test_filp))
				{
					v4l2_vsc_init_stat = STAT_FW_CHK_END;
					DE_NOTI("CHK_0 (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);
					filp_close(test_filp, NULL);
				}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
				set_fs(old_fs);
#endif
			}

			/* increase count */
			if (fw_dl_cnt < V4L2_VSC_FW_DL_INC_MAX)	fw_dl_cnt++;
		} while(0);

		/* fw download */
		if (v4l2_vsc_init_stat == STAT_FW_CHK_END)
		{
			if (VSC_FW_RET_OK == vsc_fw_download(VSC_FW_FROM_THREAD))
			{
				v4l2_vsc_init_stat = STAT_FW_DL_END;
				DE_NOTI("done (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);
			}
			else
			{
				v4l2_vsc_init_stat = STAT_SUSPEND;
				DE_NOTI("skip (stat:%d)(cnt:%d)\n",v4l2_vsc_init_stat,fw_dl_cnt);
			}
			break;
		}

		msleep(40);
	}

	return ret;
}

#ifdef INCLUDE_KDRV_PQE_PM
static int v4l2_vsc_pqe_pm_cb(int action)
{
	DE_NOTI("(%d) start\n",action);

	#if 0
	PQE_PM_DEVICE_SUSPEND_PREPARE = 0,
	//fw suspend
	PQE_PM_DEVICE_SUSPEND,
	//cg on
	PQE_PM_DEVICE_SUSPEND_COMPLETED,

	PQE_PM_DEVICE_RESUME_PREPARE,
	//cg off
	PQE_PM_DEVICE_RESUME,
	//fw resume
	PQE_PM_DEVICE_RESUME_COMPLETED,
	#endif

	if (action == PQE_PM_DEVICE_SUSPEND_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_SUSPEND) {
		/* ipc masking on after fw suspend */
		//ipc_hal_ready_to_use(0);//see vsc_suspend

		/* stop intr handler after fw suspend */
		//DE_INT_StopHandler(1);//see vsc_suspend

		//DE_NOTI("suspend : ipc masking on, handler off\n");
	}
	else if (action == PQE_PM_DEVICE_SUSPEND_COMPLETED) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME) {
		/* restart intr handler before fw resume */
		//DE_INT_StopHandler(0);//see vsc_resume

		/* ipc masking off before fw resume */
		//ipc_hal_ready_to_use(1);//see vsc_resume

		//DE_NOTI("resume : handler on, ipc masking off\n");
	}
	else if (action == PQE_PM_DEVICE_RESUME_COMPLETED) {
		//TODO:
	}

	DE_NOTI("(%d) end\n",action);
	return 0;
}

static struct pqe_pm_config v4l2_vsc_pqe_pm_cfg = {
	.name = "v4l2_vsc",
	.opt = PQE_PM_OPT_NONE,
	.order = 30,
	.callback = v4l2_vsc_pqe_pm_cb,
};
#endif

static int v4l2_vsc_probe(struct platform_device *pdev)
{
	int ret = 0;
	int fw_ret = 0;
	struct vsc_dev *drv;

	DE_NOTI("start\n");

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (drv)
	{
		drv->pdev = &v4l2_vsc_pdev;
#ifdef INCLUDE_KDRV_PQE_PM
		drv->pqe_pm_cfg = &v4l2_vsc_pqe_pm_cfg;
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
#endif
		/* Add what you need (ref. v4l2_vsc_register) */

		platform_set_drvdata(pdev, drv);
	}
	//else	return -ENOMEM;

	vsc_init_config();

	fw_ret = vsc_fw_download(VSC_FW_FROM_NORMAL);
	if (fw_ret == VSC_FW_RET_NEXT)
	{
		v4l2_vsc_init_stat = STAT_FW_CHK_START;	/* start */
		V4L2VscFwDlThread = kthread_create(v4l2_fw_dl_thread, (void*)NULL, "v4l2_fw_dl_thread");
		wake_up_process(V4L2VscFwDlThread);
	}
	else if (fw_ret == VSC_FW_RET_OK)
	{
		v4l2_vsc_init_stat = STAT_FW_DL_END;
	}
	else
	{
		v4l2_vsc_init_stat = STAT_SUSPEND;
	}

	memset(_g_act_info, 0, sizeof(struct v4l2_ext_vsc_active_win_info)*2);

	vp_kwrap_initpicinfo();

	vsc_bwm_init();

	DE_NOTI("done (stat:%d)\n",v4l2_vsc_init_stat);
	return ret;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vsc_remove(struct platform_device *pdev)
#else
static int v4l2_vsc_remove(struct platform_device *pdev)
#endif
{
	struct vsc_dev *drv = platform_get_drvdata(pdev);
	DE_NOTI("vsc  %s\n", __func__);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_unregister(drv->pqe_pm_id);
#endif
		kfree(drv);
	}

	pm_runtime_disable(&pdev->dev);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_vsc_resume(struct device *dev)
{
	DE_NOTI("%s\n", __func__);
        return 0;
}

static int v4l2_vsc_suspend(struct device *dev)
{
	DE_NOTI("%s\n", __func__);
        return 0;
}

static int v4l2_vsc_runtime_resume(struct device *dev)
{
	struct vsc_dev *drv = dev_get_drvdata(dev);

	DE_NOTI("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_resume(drv->pqe_pm_id);
#endif
	}

	VSC_PM_INFO("info",V4L2_VIDEO_MINOR_NUMBER,"resume","ok");
	VSC_PM_INFO("info",V4L2_VIDEO_MINOR_NUMBER+1,"resume","ok");

	return 0;
}

static int v4l2_vsc_runtime_suspend(struct device *dev)
{
	struct vsc_dev *drv = dev_get_drvdata(dev);

	DE_NOTI("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_suspend(drv->pqe_pm_id);
#endif
	}

	VSC_PM_INFO("info",V4L2_VIDEO_MINOR_NUMBER,"suspend","ok");
	VSC_PM_INFO("info",V4L2_VIDEO_MINOR_NUMBER+1,"suspend","ok");

	return 0;
}

int v4l2_vsc_pm_runtime_help(char* buffer)
{
	int len = 0;
	struct vsc_dev *drv = platform_get_drvdata(&v4l2_vsc_pdev);

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "dev name : %s\n",v4l2_vsc_pdev.name);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- open_count : %d\n",_g_v4l2_vsc_open_count);
#ifdef INCLUDE_KDRV_PQE_PM
	if (!drv)					len += sprintf( buffer+len, "drv null\n");
	else if (!drv->pqe_pm_cfg)	len += sprintf( buffer+len, "pqe_pm_cfg null\n");
	else						len += sprintf( buffer+len, "pqe_pm_name : %s, pqe_pm_id : %d\n",drv->pqe_pm_cfg->name,drv->pqe_pm_id);
#endif
	len += sprintf( buffer+len, "- usage_count : %d\n",atomic_read(&v4l2_vsc_pdev.dev.power.usage_count));
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo runtime_suspend     > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "echo vt_runtime_suspend  > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "echo gps_runtime_suspend > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "echo runtime_resume      > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "echo vt_runtime_resume   > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "echo gps_runtime_resume  > /proc/lg/de/pm_test\n");
	len += sprintf( buffer+len, "- others\n");
	len += sprintf( buffer+len, "cat /sys/devices/platform/v4l2_vsc/power/runtime_status\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int v4l2_vsc_pm_runtime_test(char* command)
{
	int ret = 0;
	struct vsc_dev *drv = platform_get_drvdata(&v4l2_vsc_pdev);

	if (!strncasecmp(command, "pm_runtime_put", strlen("pm_runtime_put"))) {
		ret = pm_runtime_put(&v4l2_vsc_pdev.dev);
		DE_NOTI("pm_runtime_put : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get_sync", strlen("pm_runtime_get_sync"))) {
		ret = pm_runtime_get_sync(&v4l2_vsc_pdev.dev);
		DE_NOTI("pm_runtime_get_sync : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get", strlen("pm_runtime_get"))) {
		ret = pm_runtime_get(&v4l2_vsc_pdev.dev);
		DE_NOTI("pm_runtime_get : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_suspend", strlen("pm_runtime_suspend"))) {
		ret = pm_runtime_suspend(&v4l2_vsc_pdev.dev);
		DE_NOTI("pm_runtime_suspend : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_resume", strlen("pm_runtime_resume"))) {
		ret = pm_runtime_resume(&v4l2_vsc_pdev.dev);
		DE_NOTI("pm_runtime_resume : ret:%d\n",ret);
	}
#ifdef INCLUDE_KDRV_PQE_PM
	else if (!strncasecmp(command, "pqe_pm_register", strlen("pqe_pm_register"))) {
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
		DE_NOTI("pqe_pm_register : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_suspend", strlen("pqe_pm_request_suspend"))) {
		ret = pqe_pm_request_suspend(drv->pqe_pm_id);
		DE_NOTI("pqe_pm_request_suspend : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_resume", strlen("pqe_pm_request_resume"))) {
		ret = pqe_pm_request_resume(drv->pqe_pm_id);
		DE_NOTI("pqe_pm_request_resume : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_unregister", strlen("pqe_pm_unregister"))) {
		ret = pqe_pm_unregister(drv->pqe_pm_id);
		DE_NOTI("pqe_pm_unregister : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
#endif
	else if (!strncasecmp(command, "runtime_suspend", strlen("runtime_suspend"))) {
		while (atomic_read(&v4l2_vsc_pdev.dev.power.usage_count) > 0) {
			DE_NOTI("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_vsc_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_vsc_pdev.dev);
			//msleep(1);
		}
	}
	else if (!strncasecmp(command, "runtime_resume", strlen("runtime_resume"))) {
		while (atomic_read(&v4l2_vsc_pdev.dev.power.usage_count) <= 0) {
			DE_NOTI("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_vsc_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_vsc_pdev.dev);
			//msleep(1);
		}
	}
	else {
		printk("do nothing\n");
	}

	return ret;
}

static int vsc_notification(struct vsc_priv *p)
{
	struct v4l2_event evt;

	if(p->ev_size > 64) return -1;

	memset(&evt, 0, sizeof(evt));
	evt.type = V4L2_EVENT_CTRL;
	evt.id	 = p->event;

	//if (p->event == V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR)	DE_NOTI("[%d][%s]\n",p->ev_size,p->ev_data);

	memcpy(evt.u.data, p->ev_data, p->ev_size);
	v4l2_event_queue(p->vsc_vdev, &evt);

	//DE_NOTI("Post evt.type[0x%x] evt.id[0x%x] win_%d",evt.type, evt.id, minor_num_to_win_id(p->vsc_vdev->num));

	return 0;
}
#if 0
static void vsc_noti_ws(struct work_struct *work)
{
	struct vsc_priv *p;
	p = container_of(work, struct vsc_priv, vsc_noti_work);
	if(!p) {
		//DE_WARN("p[%p]", p);
		return;
	}
	vsc_notification(p);
}
#endif
static void process_poll(struct vsc_priv *p)
{
	//queue_work(system_wq, &p->vsc_noti_work);
	vsc_notification(p);
}

struct vsc_priv *new_vsc_priv(void)
{
	struct vsc_priv *p;

	p = kcalloc(1, sizeof(struct vsc_priv), GFP_KERNEL);
	if(!p)
	{
		DE_ERROR("alloc error for vsc priv.");
		return NULL;
	}
	INIT_LIST_HEAD(&p->list);
	init_waitqueue_head(&p->vsc_poll_wq);

	return p;
}

static struct vsc_fh *pfh[LX_DE_WIN_MAX] = { 0,0,0,0 };

static int v4l2_vsc_fh_open(struct file *flie)
{
	int ret = 0;
	int ret0 = 0;
	struct vsc_priv *p;
	struct vsc_fh *fh;
	struct vsc_dev *dev  = video_drvdata(flie);

	DE_NOTI("vsc: open...(stat:%d)(%s-%s)\n",v4l2_vsc_init_stat,current->group_leader->comm,current->comm);

	ret0 = pm_runtime_get_sync(&dev->pdev->dev);
	DE_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct vsc_fh), GFP_KERNEL);
	if (!fh)
	{
		DE_ERROR("vsc: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	p = new_vsc_priv();
	if(!p)
	{
		DE_ERROR("alloc of vsc priv failed");
		ret = -ENOMEM;
		goto fail_fh;
	}

	p->check_mute_thread = NULL;
	p->update_win_thread = NULL;
	p->resize_win_thread = NULL;
	p->check_delay_thread = NULL;

	p->process_poll = process_poll;
	p->vsc_vdev = video_devdata(flie);
	fh->vsc_priv = p;
	pfh[minor_num_to_win_id(p->vsc_vdev->num)] = fh;

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	//DE_NOTI("remove INIT_WORK");
	//INIT_WORK(&p->vsc_noti_work, vsc_noti_ws);

	/* de initialize */

	// create vp thread
	if(dev->vp_thread == NULL && dev->IsHalVscV4l2Open == FALSE) {
		dev->vp_thread = kthread_create((void*)&v4l2_vp_thread,dev,"vsc_v4l2_thread");
		if(dev->vp_thread)
			DE_NOTI("======VSC V4L2 thread created for exxxternal input handlings %p %p\n",\
			dev->vp_thread,&v4l2_vp_thread);
		else
			DE_ERROR("VSC V4L2 thread creation Error\n");
		wake_up_process(dev->vp_thread);
		dev->vp_darc_thread = kthread_create((void*)&darc_thread,dev,"darc_thread");
		wake_up_process(dev->vp_darc_thread);

	}
	else {
		DE_NOTI("VSC V4l2 Thread already created= %d\n",dev->IsHalVscV4l2Open);
	}

	if(pfh[minor_num_to_win_id(p->vsc_vdev->num)]) {
		pfh[minor_num_to_win_id(p->vsc_vdev->num)]->IsMuteOffSubscribed  = FALSE;
		pfh[minor_num_to_win_id(p->vsc_vdev->num)]->IsWinEventSubscribed = FALSE;
		pfh[minor_num_to_win_id(p->vsc_vdev->num)]->IsBspErrorSubscribed = FALSE;
	}

	DE_NOTI("index = %d, minor = %d, win_id[%d]",\
		fh->fh.vdev->index, fh->fh.vdev->minor, minor_num_to_win_id(p->vsc_vdev->num));

	dev->IsHalVscV4l2Open = TRUE;
	g_de_device_opened++;
	ret = vsc_open_info(1, minor_num_to_win_id(p->vsc_vdev->num), g_de_device_opened);

	/* increment open counter */
	_g_v4l2_vsc_open_count++;
	VSC_PM_INFO("info",p->vsc_vdev->num,"open","ok");

	return ret;

fail_fh:
	kfree(fh);
	return ret;

}

static int v4l2_vsc_fh_release(struct file *flie)
{
	int ret = 0;
	int ret0 = 0;
	struct vsc_fh *fh = flie->private_data;
	struct vsc_priv *p = fh->vsc_priv;
	struct video_device *vsc_vdev;
	struct vsc_dev *dev  = video_drvdata(flie);

	DE_NOTI("vsc: close (%s-%s)\n",current->group_leader->comm,current->comm);

	if(p->check_mute_thread) {
		DE_NOTI("p->check_mute_thread  : signal !");
		de_sync_signal(SYNC_WAIT_MUTEOFF);
		send_sig(SIGUSR1, p->check_mute_thread, 0); // send signal to thread
		kthread_stop(p->check_mute_thread);
		DE_NOTI("p->check_mute_thread  : stop !");
		p->check_mute_thread = NULL;
	}
	if(p->update_win_thread) {
		DE_NOTI("p->update_win_thread  : signal !");
		de_sync_signal(SYNC_WAIT_VSYNC);
		kthread_stop(p->update_win_thread);
		DE_NOTI("p->update_win_thread  : stop !");
		p->update_win_thread = NULL;
	}
	if(p->resize_win_thread) {
		DE_NOTI("p->resize_win_thread  : signal !");
		de_sync_signal(SYNC_WAIT_DELAY); //
		send_sig(SIGUSR1, p->resize_win_thread, 0); // send signal to thread
		kthread_stop(p->resize_win_thread);
		DE_NOTI("p->resize_win_thread  : stop !");
		p->resize_win_thread = NULL;
	}	
	if(p->check_delay_thread) {
		send_sig(SIGUSR1, p->check_delay_thread, 0); // send signal to thread
		kthread_stop(p->check_delay_thread);
		p->check_delay_thread = NULL;
	}
	#if 0 // need to check
	if(dev->IsHalVscV4l2Open && (g_de_device_opened==1)) {
		kthread_stop(dev->vp_darc_thread);
		dev->IsHalVscV4l2Open = 0;
	}
	#endif

	if (fh)
	{
		struct vsc_priv *p = fh->vsc_priv;
		if (p && p->update_bbd_thread) {
			#ifdef V4L2_VSC_BBD_WAITQUEUE
			DE_NOTI("wake_up bbd_queue\n");
			p->bbd_condition = 1;
			wake_up_interruptible(&p->bbd_queue);
			#else
			send_sig(SIGUSR1,p->update_bbd_thread,0);
			#endif
			kthread_stop(p->update_bbd_thread);
			p->update_bbd_thread = NULL;
			DE_NOTI("stop bbd%d-%05d%05d\n",minor_num_to_win_id(p->vsc_vdev->num),p->bbd_tid,p->bbd_pid);
		}
	}

	vsc_vdev = video_devdata(flie);
	if(vsc_vdev)
	{
		kfree(fh->vsc_priv);
		fh->vsc_priv = NULL;
		pfh[minor_num_to_win_id(vsc_vdev->num)] = NULL;
	}

	DE_NOTI("vsc: close win[%d]\n", minor_num_to_win_id(vsc_vdev->num));

	v4l2_fh_release(flie);
	_g_v4l2_vsc_open_count--;
	ret = vsc_open_info(0, minor_num_to_win_id(vsc_vdev->num), _g_v4l2_vsc_open_count);

	ret0 = pm_runtime_put(&dev->pdev->dev);
	DE_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	/* decrement open counter */
	VSC_PM_INFO("info",vsc_vdev->num,"close","ok");

	return ret;
}

static int v4l2_vsc_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	struct vsc_fh *fh = __fh;
	UINT8 win = minor_num_to_win_id(fh->fh.vdev->num);

	DE_NOTI("vsc:id 0x%x (%s), value %d\n", \
		ctrl->id, ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
	case V4L2_CID_BG_COLOR:
		{
			ktime_t 	   t;
			struct timespec64 ts;
			if(win<2&&ctrl->value==0) {
				t  = ktime_get_real();
				ts = ktime_to_timespec64(t);
				t_vsc_sec_mute[win] = ts.tv_sec;
				t_vsc_msec_mute[win] = ts.tv_nsec/1000000;
			}
			ret = vsc_set_mute(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_FREEZE:
		{
			ret = vsc_set_freeze(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_PATTERN:
		{
			ret = vsc_set_pattern(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_FRAME_DELAY:
		{
			ret = vsc_set_frame_delay(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_ADAPTIVE_STREAM:
		{
			ret = vsc_set_adaptives_stream(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_RGB444:
		{
			ret = vsc_set_rgb444(1, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_HDR_TYPE:
		{
			struct vsc_dolby_data info; // fix build warning
			struct v4l2_ext_vsc_input_src_info srcInfo = vsc_v4l2_get_input(win);

			ret = vsc_set_hdr_type(1, win, &ctrl->value);

			//Call function of Dolby
			info.ctrl = ctrl;
			info.extra[VSC_SRC_TYPE_INDEX] = srcInfo.src;
			if(RET_OK != vsc_v4l2_dolby_event(win,V4L2_CID_EXT_VSC_HDR_TYPE,&info)){
				DE_ERROR("Dolby EVENT failed!!!!!!\n");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER:
		{
			ret = vsc_set_cvi_frz(1, win, &ctrl->value);
		}
		break;
#ifdef V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
	case V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER:
		{
			ret = vsc_set_sub_occupy(1, win, &ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_LOCAL_MUTE
		case V4L2_CID_EXT_VSC_LOCAL_MUTE:
		{
			ret = vsc_set_local_mute(1, win, &ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_IPMODE
		case V4L2_CID_EXT_VSC_IPMODE:
		{
			ret = vsc_set_ipc_mode(1, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_SCAN_MODE
		case V4L2_CID_EXT_VSC_SCAN_MODE:
		{
			ret = vsc_set_scanmode(1, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL
		case V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL:
		{
			ret = vsc_set_pixeltopixel(1, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
	default:
		ret = -EINVAL;
	}

	return ret;
}

static int v4l2_vsc_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	struct vsc_fh *fh = __fh;
	UINT8 win = fh->fh.vdev->index;

	switch (ctrl->id) {
	case V4L2_CID_BG_COLOR:
		{
			ret = vsc_set_mute(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_FREEZE:
		{
			ret = vsc_set_freeze(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_PATTERN:
		{
			ret = vsc_set_pattern(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_FRAME_DELAY:
		{
			ret = vsc_set_frame_delay(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_ADAPTIVE_STREAM:
		{
			ret = vsc_set_adaptives_stream(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_RGB444:
		{
			ret = vsc_set_rgb444(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_HDR_TYPE:
		{
			ret = vsc_set_hdr_type(0, win, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER:
		{
			ret = vsc_set_cvi_frz(0, win, &ctrl->value);
		}
		break;
#ifdef V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
	case V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER:
		{
			ret = vsc_set_sub_occupy(0, win, &ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_LOCAL_MUTE
	case V4L2_CID_EXT_VSC_LOCAL_MUTE:
		{
			ret = vsc_set_local_mute(0, win, &ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_IPMODE
		case V4L2_CID_EXT_VSC_IPMODE:
		{
			ret = vsc_set_ipc_mode(0, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_SCAN_MODE
		case V4L2_CID_EXT_VSC_SCAN_MODE:
		{
			ret = vsc_set_scanmode(0, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
#ifdef V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL
		case V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL:
		{
			ret = vsc_set_pixeltopixel(0, win, (UINT32 *)&ctrl->value);
		}
		break;
#endif
	default:
		{
			DE_NOTI("Not implemented - %s", \
				ctrl_id_ext_to_str(ctrl->id));
		}
		ret = -EINVAL;
	}

	DE_NOTI("vsc:id 0x%x (%s), value %d\n", \
		ctrl->id, ctrl_id_to_str(ctrl->id), ctrl->value);

	return 0;
}

static int vsc_set_ext_ctrl(struct v4l2_ext_control *ctrl, UINT8 win)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_VSC_CONNECT_INFO:
		{
			struct v4l2_ext_vsc_connect_info param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_connect_info)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_input(1, win, &param);

		}
		break;
	case V4L2_CID_EXT_VSC_WIN_REGION:
		{
			struct v4l2_ext_vsc_win_region param;
			BOOLEAN flag = 0;
			//if(pfh[win])
				//flag = pfh[win]->IsWinEventSubscribed;
				flag = (event_user[win]>0)?1:0;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_win_region)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_win_info(1, win, flag, &param);
		}
		break;
	case V4L2_CID_EXT_VSC_WIN_PROP:
		{
			struct v4l2_ext_vsc_win_prop param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_win_prop)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_sub_mode(1, win, &param);
		}
		break;
	case V4L2_CID_EXT_VSC_ZORDER:
		{
			struct v4l2_ext_vsc_zorder param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_zorder)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_zorder(1, win, &param);
		}
		break;
#ifdef V4L2_CID_EXT_VSC_ALPHA_ZORDER
	case V4L2_CID_EXT_VSC_ALPHA_ZORDER:
		{
			struct v4l2_ext_vsc_zorder_info param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_zorder_info)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_zorder_info(1, win, &param);
		}
		break;
#endif
	case V4L2_CID_EXT_VSC_LATENCY_PATTERN:
		{
			struct v4l2_ext_vsc_latency_pattern_info param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_latency_pattern_info)))
			{
				DE_ERROR("copy from user error ");
			}
#ifdef INCLUDE_KDRV_BE
			ret = v4l2_vbe_set_latency_pattern(1, win, &param);
#endif
		}
		break;
	case V4L2_CID_EXT_VSC_HDR_TYPE:
		{
			ret = vsc_set_hdr_type(1, win, &ctrl->value);
			DE_NOTI("Setting HDR type\n");
		}
		break;
	case V4L2_CID_EXT_VSC_ORBIT_POLICY:
		{
			struct v4l2_ext_vsc_orbit_policy param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_orbit_policy)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_orbit_policy(1, win, &param);
		}
	case V4L2_CID_EXT_VSC_ORBIT_WINDOW:
		{
			struct v4l2_ext_vsc_orbit_window param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_orbit_window)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_orbit_window(1, win, &param);
		}
		break;
	case V4L2_CID_EXT_VSC_ORBIT_MOVE:
		{
			struct v4l2_ext_vsc_orbit_move param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_orbit_move)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_orbit_move(1, win, &param);
		}
		break;
#ifdef V4L2_CID_EXT_VSC_QUAD_MODE
	case V4L2_CID_EXT_VSC_QUAD_MODE:
		{
			unsigned int param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(unsigned int)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_quad_mode(1, win, &param);
		}
		break;
#endif
	case V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY:
		{
		struct v4l2_ext_vsc_aspectratio_policy param;
		if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_aspectratio_policy)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vsc_set_aspectratio_policy(1, win, &param);
		}
		break;
	default:
		{
			DE_NOTI("Not implemented - %s", \
				ctrl_id_ext_to_str(ctrl->id));
		}
		return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_vsc_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct vsc_fh *fh = __fh;
	int i, ret = 0;
//	struct vsc_dev *dev  = video_drvdata(file);
	ktime_t 	   t;
	struct timespec64 ts;
//	UINT8 win = fh->fh.vdev->index;
	UINT8 win = minor_num_to_win_id(fh->fh.vdev->num);
	__attribute__((unused)) int copy_ret;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			DE_NOTI("vsc:id 0x%x (%s)\n", \
				ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			if(ctrl->id == V4L2_CID_EXT_VSC_WIN_REGION) {
				struct v4l2_ext_vsc_win_region param;
				int copy_ret;
				t  = ktime_get_real();
				ts = ktime_to_timespec64(t);
				t_vsc_sec_prv = ts.tv_sec;
				t_vsc_msec_prv[win] = ts.tv_nsec/1000000;
				copy_ret = copy_from_user(&param, (void __user *)ctrl->string, sizeof(struct v4l2_ext_vsc_win_region));
				t_vsc_rect_prv[win].x = param.out.x;
				t_vsc_rect_prv[win].y = param.out.y;
				t_vsc_rect_prv[win].w = param.out.w;
				t_vsc_rect_prv[win].h = param.out.h;
#ifdef V4L2_VSC_RETURN_PUNCH
				t_vsc_policy_punch[win].x = param.punch.x;
				t_vsc_policy_punch[win].y = param.punch.y;
				t_vsc_policy_punch[win].w = param.punch.w;
				t_vsc_policy_punch[win].h = param.punch.h;
#endif
				update_win_send_flag[win] = 0;
			}
#ifdef V4L2_VSC_RETURN_PUNCH
			if(ctrl->id == V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY) {
				struct v4l2_ext_vsc_aspectratio_policy param;
				copy_ret = copy_from_user(&param, (void __user *)ctrl->string, sizeof(struct v4l2_ext_vsc_aspectratio_policy));
				t_vsc_policy_punch[win].x = param.punch.x;
				t_vsc_policy_punch[win].y = param.punch.y;
				t_vsc_policy_punch[win].w = param.punch.w;
				t_vsc_policy_punch[win].h = param.punch.h;
				t_vsc_rect_prv[win].x = param.out.x;
				t_vsc_rect_prv[win].y = param.out.y;
				t_vsc_rect_prv[win].w = param.out.w;
				t_vsc_rect_prv[win].h = param.out.h;

				update_win_send_flag[win] = 0;
			}
#endif
			ret = vsc_set_ext_ctrl(ctrl, win);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int vsc_get_ext_ctrl(struct v4l2_ext_control *ctrl, UINT8 win)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_VSC_CONNECT_INFO:
		{
			struct v4l2_ext_vsc_connect_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_connect_info));

			ret = vsc_set_input(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_connect_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_WIN_REGION:
		{
			struct v4l2_ext_vsc_win_region param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_win_region));

			ret = vsc_set_win_info(0, win, 0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_win_region)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_WIN_PROP:
		{
			struct v4l2_ext_vsc_win_prop param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_win_prop));

			ret = vsc_set_sub_mode(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_win_prop)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_ZORDER:
		{
			struct v4l2_ext_vsc_zorder param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_zorder));

			ret = vsc_set_zorder(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_zorder)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
#ifdef V4L2_CID_EXT_VSC_ALPHA_ZORDER
		case V4L2_CID_EXT_VSC_ALPHA_ZORDER:
		{
			struct v4l2_ext_vsc_zorder_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_zorder_info));

			ret = vsc_set_zorder_info(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_zorder_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
#endif

	case V4L2_CID_EXT_VSC_LATENCY_PATTERN:
		{
			struct v4l2_ext_vsc_latency_pattern_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_latency_pattern_info));

			ret = vsc_set_latency_pattern(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_latency_pattern_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_LIMITED_WIN_RATIO:
		{
			struct v4l2_ext_vsc_scaler_ratio param;
			param.h_scaledown_ratio = 0;
			param.h_scaleup_ratio   = 0;
			param.v_scaledown_ratio = 0;
			param.v_scaleup_ratio   = 0;
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_scaler_ratio)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO:
		{
			struct v4l2_ext_vsc_active_win_info *p;
			if (win>=LX_DE_WIN_MAX)	break;
			p = &_g_act_info[win];
			DE_NOTI("wid:%d, org:%d,%d,%d,%d, act:%d,%d,%d,%d\n",win,\
				p->original.x,p->original.y,p->original.w,p->original.h,\
				p->active.x,p->active.y,p->active.w,p->active.h);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)p, sizeof(struct v4l2_ext_vsc_active_win_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO:
		{
			struct v4l2_ext_vsc_pixel_color_info param;
			struct v4l2_ext_vsc_pixel_color_info arg_buf;
			struct v4l2_ext_vsc_color_pixel_data *pixel;
			unsigned int size;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_pixel_color_info));
			if(copy_from_user(&arg_buf,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_vsc_pixel_color_info)))
			{
				DE_ERROR("copy from user error ");
			}
			//arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			arg_buf.p_data = (struct v4l2_ext_vsc_color_pixel_data *)(uintptr_t)arg_buf.compat_data;

			if(copy_to_user((void __user *)ctrl->string, \
				&arg_buf,\
				sizeof(struct v4l2_ext_vsc_pixel_color_info)))
			{
				DE_ERROR("copy_to_user error\n");
			}
			memcpy((void*)&param, (void*)&arg_buf, sizeof(struct v4l2_ext_vsc_pixel_color_info));

			size = param.r.w * param.r.h * sizeof(struct v4l2_ext_vsc_color_pixel_data);
			//DE_NOTI("w[%d] h[%d] alloc size[%d]", param.r.w, param.r.h, size);
			pixel = (struct v4l2_ext_vsc_color_pixel_data *)kmalloc(size, GFP_KERNEL);
			param.p_data = pixel;
			ret = vsc_set_read_cvi_pixel(0, win, &param);
			if(copy_to_user((void __user *)arg_buf.p_data, (void *)param.p_data, size))
			{
				DE_ERROR("copy_to_user error");
			}
			arg_buf.format = param.format;
			arg_buf.depth  = param.depth;

			size = param.r.w * param.r.h;
#if 0 // request from SCDCR-2300
			for(i=0;i<size;i++)
			{ // reorder y<->cb
				UINT32 temp = arg_buf.p_data[i].y;
				arg_buf.p_data[i].y = arg_buf.p_data[i].cb;
				arg_buf.p_data[i].cb = temp;
			}
#endif
			//DE_NOTI("[after copy & reorder]  (Y,Cb,Cr)=(%d,%d,%d)\n",
			//		arg_buf.p_data[0].y, arg_buf.p_data[0].cb, arg_buf.p_data[0].cr);
			kfree(pixel);
		}
		break;
	case V4L2_CID_EXT_VSC_ORBIT_POLICY:
		{
			struct v4l2_ext_vsc_orbit_policy param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_orbit_policy));

			ret = vsc_set_orbit_policy(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_orbit_policy)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_VSC_ORBIT_WINDOW:
		{
			struct v4l2_ext_vsc_orbit_window param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_orbit_window));

			ret = vsc_set_orbit_window(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_orbit_window)))
			{
				DE_ERROR("copy_to_user error");
			}	
		}
		break;
	case V4L2_CID_EXT_VSC_ORBIT_MOVE:
		{
			struct v4l2_ext_vsc_orbit_move param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_orbit_move));

			ret = vsc_set_orbit_move(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_orbit_move)))
			{
				DE_ERROR("copy_to_user error");
			}	
		}
		break;
		case V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY:
			{
			struct v4l2_ext_vsc_aspectratio_policy param;
			memset(&param, 0, sizeof(struct v4l2_ext_vsc_aspectratio_policy));

			ret = vsc_set_aspectratio_policy(0, win, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_vsc_aspectratio_policy)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
#ifdef V4L2_CID_EXT_VSC_DEVICE_CAPABILITY
		case V4L2_CID_EXT_VSC_DEVICE_CAPABILITY:
			{
				struct v4l2_ext_vsc_device_capability param;
				if(lx_chip_rev() >= LX_CHIP_REV( O26, A0)){
					param.num_planes = 4;
				}
				else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O24)){
					param.num_planes = 4;
				}
				else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O22)){
					param.num_planes = 2;
				}
				else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_M23)){
					param.num_planes = 1;
				}
				DE_NOTI("V4L2_CID_EXT_VSC_DEVICE_CAPABILITY.num_planes = %d", param.num_planes);
				if(copy_to_user((void __user *)ctrl->string, \
					(void *)&param, sizeof(struct v4l2_ext_vsc_device_capability)))
				{
					DE_ERROR("copy_to_user error");
				}
			}
			break;
#endif

	default:
		return -EINVAL;
	}
	return 0;
}


static int v4l2_vsc_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	struct vsc_fh *fh = __fh;
	UINT8 win = minor_num_to_win_id(fh->fh.vdev->num);

	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			if(ctrl->id != V4L2_CID_EXT_VSC_WIN_REGION && \
				ctrl->id != V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO)
				DE_NOTI("vsc[%d]:id 0x%x (%s)\n", \
				win, ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			ret = vsc_get_ext_ctrl(ctrl, win);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;
	}

	return -EINVAL;
}

static int v4l2_vsc_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	struct vsc_fh *fh = __fh;
	UINT8 win = minor_num_to_win_id(fh->fh.vdev->num);

	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	// refer to SCDCR-2432
	if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O26)){
		strncpy(cap->driver, "o26", sizeof(cap->driver)-1);//SOCTSSIC-82109
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O24)){
		strncpy(cap->driver, "o24", sizeof(cap->driver)-1);//SOCTSSIC-82109
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_M23)){
		strncpy(cap->driver, "m23", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O22)){
		strncpy(cap->driver, "o22", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_E60)){
		strncpy(cap->driver, "e60", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O20)){
		strncpy(cap->driver, "o20", sizeof(cap->driver)-1);
	}
	else {
		strncpy(cap->driver, "m16p3", sizeof(cap->driver)-1);
	}

	switch(win)
	{
		case 0:
			strncpy(cap->card, "scaler_main", sizeof(cap->card)-1);break;
		case 1:
			strncpy(cap->card, "scaler_sub0", sizeof(cap->card)-1);break;
		case 2:
			strncpy(cap->card, "scaler_sub1", sizeof(cap->card)-1);break;
		case 3:
			strncpy(cap->card, "scaler_sub2", sizeof(cap->card)-1);break;
		default:
			break;
	}
	cap->version = LINUX_VERSION_CODE; // #define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

	DE_NOTI("Query cap !!!!! soc[%s] card[%s]\n", cap->driver, cap->card);

	return 0;
}

static int v4l2_vsc_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
//	struct vsc_fh *fh = __fh;

	DE_NOTI("vsc: set input %d\n", i);

	return 0;
}

static int v4l2_vsc_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
//	struct vsc_fh *fh = __fh;

	DE_NOTI("vsc: get input %d\n", *i);

	return 0;
}

static int v4l2_vsc_vidioc_s_output(struct file *file, void *__fh, unsigned int i)
{
//	struct vsc_fh *fh = __fh;

	DE_NOTI("vsc: set output %d\n", i);

	return 0;
}

static int v4l2_vsc_vidioc_g_output(struct file *file, void *__fh, unsigned int *i)
{
//	struct vsc_fh *fh = __fh;

	DE_NOTI("vsc: get output %d\n", *i);

	return 0;
}

static int _check_valid_event(const struct v4l2_event_subscription *sub)
{
	int ret = -1;

	if (!sub) {
		return -1;
	}
	if(sub->flags > 10)
		return ret;

	switch (sub->id) {
		case V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN:
		case V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF:
		case V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION:
		case V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY:
		case V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR:
			if (sub->type == V4L2_EVENT_CTRL) {
				ret = 0;
			}
			break;
	}

	return ret;
}

static int v4l2_vsc_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	int err = 0;
	int wid;
	struct vsc_fh *pvsc_fh = container_of(__fh, struct vsc_fh, fh);
	struct vsc_priv *p = pvsc_fh->vsc_priv;

	if (!__fh)	{DE_ERROR("__fh null\n");	return -EINVAL;}
	if (!sub)	{DE_ERROR("sub null\n");	return -EINVAL;}
	if (!pvsc_fh){DE_ERROR("pvsc_fh null\n");return -EINVAL;}

	wid = minor_num_to_win_id(__fh->vdev->num);
	DE_NOTI("vsc[%d] type 0x%x, id 0x%x (base:0x%x) flags 0x%x\n",wid,sub->type,sub->id,V4L2_CID_USER_EXT_VSC_BASE, sub->flags);

	if (0 != _check_valid_event(sub)) {
		DE_ERROR("vsc[%d] _check_valid_event err\n",wid);
		return -1;
	}

	if (sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN)
	{
		if (p && !p->update_bbd_thread) {
			p->bbd_tid = task_tgid_nr(current);
			p->bbd_pid = task_pid_nr(current);

			#ifdef V4L2_VSC_BBD_WAITQUEUE
			init_waitqueue_head(&(p->bbd_queue));
			p->bbd_condition = 0;
			DE_NOTI("init bbd_queue\n");
			#endif

			p->update_bbd_thread = kthread_run(vsc_bbd_thread,p,"bbd%d-%05d%05d",wid,p->bbd_tid,p->bbd_pid);
			if (IS_ERR(p->update_bbd_thread)) {
				err = PTR_ERR(p->update_bbd_thread);
				DE_ERROR("bbd%d-%05d%05d kthread_run err(%d)\n",wid,p->bbd_tid,p->bbd_pid,err);
				p->update_bbd_thread = NULL;
				return err;
			}
			DE_NOTI("run bbd%d-%05d%05d\n",wid,p->bbd_tid,p->bbd_pid);
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF)
	{
		if(!p->check_mute_thread) {
			p->check_mute_thread = kthread_run(vsc_check_mute_thread, p, "%s", "check_mute");
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION)
	{
		if(!p->update_win_thread && !p->resize_win_thread) {
			p->update_win_thread = kthread_run(vsc_update_win_thread, p, "%s", "update_window_update");
			if(minor_num_to_win_id(p->vsc_vdev->num) == 0) {
				p->resize_win_thread = kthread_run(vsc_update_resize_thread, p, "%s", "update_window_resize_animation");
				event_user[wid]++;
			}
			if(pfh[wid]) pfh[wid]->IsWinEventSubscribed = TRUE;

			DE_NOTI("event_user[%d]=%d", wid, event_user[wid]);
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY)
	{
		if(!p->check_delay_thread) {
			p->check_delay_thread = kthread_run(vsc_check_delay_thread, p, "%s", "check_pipeline_delay");
			if (IS_ERR(p->check_delay_thread)) {
				err = PTR_ERR(p->check_delay_thread);
				DE_ERROR("kthread_run err(%d)\n",err);
				p->check_delay_thread = NULL;
				return err;
			}
			if(pfh[wid]) pfh[wid]->VideoDelay = 0; // reset delay value
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR)
	{
		if(pfh[wid]) pfh[wid]->IsBspErrorSubscribed = TRUE;
	}

	return v4l2_event_subscribe(__fh, sub, 32, NULL);
}

static int v4l2_vsc_vidioc_unsubscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	int wid, ret;
	struct vsc_fh *pvsc_fh = container_of(__fh, struct vsc_fh, fh);
	struct vsc_priv *p = pvsc_fh->vsc_priv;

	if (!__fh)	{DE_ERROR("__fh null\n");	return -EINVAL;}
	if (!sub)	{DE_ERROR("sub null\n");	return -EINVAL;}
	if (!pvsc_fh){DE_ERROR("pvsc_fh null\n");return -EINVAL;}

	wid = minor_num_to_win_id(__fh->vdev->num);
	DE_NOTI("vsc[%d] type 0x%x, id 0x%x (base:0x%x) flags 0x%x\n",wid,sub->type,sub->id,V4L2_CID_USER_EXT_VSC_BASE, sub->flags);

	if (0 != _check_valid_event(sub)) {
		DE_ERROR("vsc[%d] _check_valid_event err\n",wid);
		return -1;
	}

	if (sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN)
	{
		if (p && p->update_bbd_thread) {
			#ifdef V4L2_VSC_BBD_WAITQUEUE
			DE_NOTI("wake_up bbd_queue\n");
			p->bbd_condition = 1;
			wake_up_interruptible(&p->bbd_queue);
			#else
			send_sig(SIGUSR1,p->update_bbd_thread,0);
			#endif
			kthread_stop(p->update_bbd_thread);
			p->update_bbd_thread = NULL;
			DE_NOTI("stop bbd%d-%05d%05d\n",wid,p->bbd_tid,p->bbd_pid);
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF)
	{
		if(p->check_mute_thread) {
			DE_NOTI("p->check_mute_thread  : signal !");
			de_sync_signal(SYNC_WAIT_MUTEOFF);
			kthread_stop(p->check_mute_thread);
			DE_NOTI("p->check_mute_thread  : stop !");
			p->check_mute_thread = NULL;
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION)
	{
		if(p->update_win_thread) {
			//DE_NOTI("p->update_win_thread  : signal !");
			//de_sync_signal(SYNC_WAIT_DELAY);
			de_sync_signal(SYNC_WAIT_VSYNC); // use  instead of  VSYNC (because of same intr src)
			send_sig(SIGUSR1, p->update_win_thread, 0); // send signal to thread
			kthread_stop(p->update_win_thread);

			if(minor_num_to_win_id(p->vsc_vdev->num) == 0) {

				de_sync_signal(SYNC_WAIT_DELAY); // use  instead of  VSYNC (because of same intr src)
				send_sig(SIGUSR1, p->resize_win_thread, 0); // send signal to thread
				kthread_stop(p->resize_win_thread);

				//DE_NOTI("p->update_win_thread  : stop !");
			}
			if(pfh[wid]) pfh[wid]->IsWinEventSubscribed = FALSE;
			event_user[wid]--;
			DE_NOTI("event_user[%d]=%d", wid, event_user[wid]);
			p->update_win_thread = NULL;
			p->resize_win_thread = NULL;
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY)
	{
		if(p->check_delay_thread) {
			de_sync_signal(SYNC_WAIT_VIDEO_DELAY);
			send_sig(SIGUSR1, p->check_delay_thread, 0); // send signal to thread
			kthread_stop(p->check_delay_thread);
			p->check_delay_thread = NULL;
		}
	}
	else if(sub->id == V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR)
	{
		if(pfh[wid]) pfh[wid]->IsBspErrorSubscribed = FALSE;
	}

	ret = v4l2_event_unsubscribe(__fh, sub);
	DE_NOTI("done");
	return ret;
}

static unsigned int v4l2_vsc_poll(struct file *file, poll_table *wait)
{
	struct vsc_fh *fh = (struct vsc_fh *)file->private_data;
	int rc = 0;
	//unsigned long req_events = poll_requested_events(wait);

	//DE_NOTI("vsc:req_events 0x%lx\n", req_events);

	poll_wait(file,  &fh->fh.wait, wait);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
#if 0
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

	DE_NOTI("vsc: rc 0x%x\n", rc);
#endif
	return rc;
}

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_BG_COLOR :
			return "V4L2_CID_BG_COLOR";
		case V4L2_CID_EXT_VSC_FREEZE :
			return "V4L2_CID_EXT_VSC_FREEZE";
		case V4L2_CID_EXT_VSC_PATTERN:
			return "V4L2_CID_EXT_VSC_PATTERN";
		case V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER:
			return "V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER";
		case V4L2_CID_EXT_VSC_RGB444:
			return "V4L2_CID_EXT_VSC_RGB444";
		case V4L2_CID_EXT_VSC_ADAPTIVE_STREAM:
			return "V4L2_CID_EXT_VSC_ADAPTIVE_STREAM";
		case V4L2_CID_EXT_VSC_HDR_TYPE:
			return "V4L2_CID_EXT_VSC_HDR_TYPE";
		case V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER:
			return "V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER";
#ifdef V4L2_CID_EXT_VSC_LOCAL_MUTE
		case V4L2_CID_EXT_VSC_LOCAL_MUTE:
			return "V4L2_CID_EXT_VSC_LOCAL_MUTE";
#endif
#ifdef V4L2_CID_EXT_VSC_IPMODE
		case V4L2_CID_EXT_VSC_IPMODE:
			return "V4L2_CID_EXT_VSC_IPMODE";
#endif
		default:
			return "CID Unkown";
	}
}

static int minor_num_to_win_id(int num)
{
	switch(num)
	{
		case V4L2_EXT_DEV_NO_SCALER0:
			return 0;
		case V4L2_EXT_DEV_NO_SCALER1:
			return 1;
		case V4L2_EXT_DEV_NO_SCALER2:
			return 2;
		case V4L2_EXT_DEV_NO_SCALER3:
			return 3;
		default:
			DE_WARN("invalid video device number[%d]", num);
			return 0x0;
	}
}

static char *ctrl_id_ext_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_VSC_WIN_REGION :
			return "V4L2_CID_EXT_VSC_WIN_REGION";
		case V4L2_CID_EXT_VSC_WIN_PROP:
			return "V4L2_CID_EXT_VSC_WIN_PROP";
		case V4L2_CID_EXT_VSC_FRAME_DELAY:
			return "V4L2_CID_EXT_VSC_FRAME_DELAY";
		case V4L2_CID_EXT_VSC_ZORDER:
			return "V4L2_CID_EXT_VSC_ZORDER";
		case V4L2_CID_EXT_VSC_LIMITED_WIN_RATIO:
			return "V4L2_CID_EXT_VSC_LIMITED_WIN_RATIO";
		case V4L2_CID_EXT_VSC_LATENCY_PATTERN:
			return "V4L2_CID_EXT_VSC_LATENCY_PATTERN";
		case V4L2_CID_EXT_VSC_ADAPTIVE_STREAM:
			return "V4L2_CID_EXT_VSC_ADAPTIVE_STREAM";
		case V4L2_CID_EXT_VSC_RGB444:
			return "V4L2_CID_EXT_VSC_RGB444";
		case V4L2_CID_EXT_VSC_HDR_TYPE:
			return "V4L2_CID_EXT_VSC_HDR_TYPE";
		case V4L2_CID_EXT_VSC_CONNECT_INFO:
			return "V4L2_CID_EXT_VSC_CONNECT_INFO";
		case V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO:
			return "V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO";
		case V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF:
			return "V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF";
		case V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN:
			return "V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN";
		case V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO:
			return "V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO";
		case V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER:
			return "V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER";
		case V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION:
			return "V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION";
		case V4L2_CID_EXT_VSC_ORBIT_MOVE:
			return "V4L2_CID_EXT_VSC_ORBIT_MOVE";
		case V4L2_CID_EXT_VSC_ORBIT_WINDOW:
			return "V4L2_CID_EXT_VSC_ORBIT_WINDOW";
		case V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY:
			return "V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY";
#ifdef V4L2_CID_EXT_VSC_DEVICE_CAPABILITY
		case V4L2_CID_EXT_VSC_DEVICE_CAPABILITY:
			return "V4L2_CID_EXT_VSC_DEVICE_CAPABILITY";
#endif
#ifdef V4L2_CID_EXT_VSC_ALPHA_ZORDER
		case V4L2_CID_EXT_VSC_ALPHA_ZORDER:
			return "V4L2_CID_EXT_VSC_ALPHA_ZORDER";
#endif
		default:
			return "Ext. CID Unkown";
	}
}

struct v4l2_file_operations v4l2_vsc_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_vsc_fh_open,
	.release	= v4l2_vsc_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read       = vb2_fop_read,
//	.write      = vb2_fop_write,
//	.mmap       = vb2_fop_mmap,
	.poll = v4l2_vsc_poll,
};

struct v4l2_ioctl_ops v4l2_vsc_ioctl_ops = {
	.vidioc_querycap		= v4l2_vsc_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_vsc_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_vsc_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_vsc_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_vsc_vidioc_g_ext_ctrls,
	.vidioc_s_input			= v4l2_vsc_vidioc_s_input,
	.vidioc_g_input			= v4l2_vsc_vidioc_g_input,
	.vidioc_s_output		= v4l2_vsc_vidioc_s_output,
	.vidioc_g_output		= v4l2_vsc_vidioc_g_output,
	.vidioc_log_status      = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_vsc_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_vsc_vidioc_unsubscribe_event,
};

static int v4l2_vsc_register(void *arg)
{
	int ret;
	struct vsc_dev *dev;
	struct video_device *vfd;
	//struct vb2_queue *q;

	DE_NOTI("vsc  %s\n", __func__);

	platform_driver_register(&v4l2_vsc_driver);
	platform_device_register(&v4l2_vsc_pdev);

    /* allocate main vivid state structure */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	do {
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_vsc_pdev.dev, &dev->v4l2_vsc_dev);
		if(ret < 0){
			DE_NOTI(" vsc : v4l2_device_register error[%d]\n", ret);
			break;
		}

		spin_lock_init(&dev->slock);
		mutex_init(&dev->v4l2_vsc_video_device_lock);
		dev->pdev = &v4l2_vsc_pdev;
		#ifdef INCLUDE_KDRV_PQE_PM
		dev->pqe_pm_cfg = &v4l2_vsc_pqe_pm_cfg;
		#endif
		dev->IsHalVscV4l2Open = FALSE;

		// win_0
		vfd = &dev->v4l2_vsc_video_dev0;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		strscpy(vfd->name, "vsc-video-dev0", sizeof(vfd->name));
#else
		strlcpy(vfd->name, "vsc-video-dev0", sizeof(vfd->name));
#endif
		vfd->v4l2_dev  = &dev->v4l2_vsc_dev;
		vfd->fops      = &v4l2_vsc_fops;
		vfd->ioctl_ops = &v4l2_vsc_ioctl_ops;
		vfd->release   = video_device_release_empty;
		vfd->lock      = &dev->v4l2_vsc_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE;
#endif
		video_set_drvdata(vfd, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_VIDEO_MINOR_NUMBER);
#else
		ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_VIDEO_MINOR_NUMBER);
#endif
		if (ret < 0) {
		    DE_NOTI("video device register error: %d\n", ret);
		    return -1;
		}

		// win_1
		vfd = &dev->v4l2_vsc_video_dev1;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		strscpy(vfd->name, "vsc-video-dev1", sizeof(vfd->name));
#else
		strlcpy(vfd->name, "vsc-video-dev1", sizeof(vfd->name));
#endif
		vfd->v4l2_dev  = &dev->v4l2_vsc_dev;
		vfd->fops      = &v4l2_vsc_fops;
		vfd->ioctl_ops = &v4l2_vsc_ioctl_ops;
		vfd->release   = video_device_release_empty;
		vfd->lock      = &dev->v4l2_vsc_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE;
#endif
		video_set_drvdata(vfd, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_VIDEO_MINOR_NUMBER+1);
#else
		ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_VIDEO_MINOR_NUMBER+1);
#endif
		if (ret < 0) {
		    DE_NOTI("video device register error: %d\n", ret);
		    return -1;
		}

		// win_2
		vfd = &dev->v4l2_vsc_video_dev2;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		strscpy(vfd->name, "vsc-video-dev2", sizeof(vfd->name));
#else
		strlcpy(vfd->name, "vsc-video-dev2", sizeof(vfd->name));
#endif
		vfd->v4l2_dev  = &dev->v4l2_vsc_dev;
		vfd->fops      = &v4l2_vsc_fops;
		vfd->ioctl_ops = &v4l2_vsc_ioctl_ops;
		vfd->release   = video_device_release_empty;
		vfd->lock      = &dev->v4l2_vsc_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE;
#endif
		video_set_drvdata(vfd, dev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_VIDEO_MINOR_NUMBER+2);
#else
		ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_VIDEO_MINOR_NUMBER+2);
#endif
		if (ret < 0) {
			DE_NOTI("video device register error: %d\n", ret);
			return -1;
		}

		// win_3
		vfd = &dev->v4l2_vsc_video_dev3;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		strscpy(vfd->name, "vsc-video-dev3", sizeof(vfd->name));
#else
		strlcpy(vfd->name, "vsc-video-dev3", sizeof(vfd->name));
#endif
		vfd->v4l2_dev  = &dev->v4l2_vsc_dev;
		vfd->fops      = &v4l2_vsc_fops;
		vfd->ioctl_ops = &v4l2_vsc_ioctl_ops;
		vfd->release   = video_device_release_empty;
		vfd->lock      = &dev->v4l2_vsc_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
		vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE;
#endif
		video_set_drvdata(vfd, dev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_VIDEO_MINOR_NUMBER+3);
#else
		ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_VIDEO_MINOR_NUMBER+3);
#endif
		if (ret < 0) {
		    DE_NOTI("video device register error: %d\n", ret);
		    return -1;
		}
	}while(0);

	return ret;
}

static int v4l2_dev_register(void *arg)
{
	DE_NOTI("vsc  %s\n", __func__);

	do{
		if(v4l2_vsc_register(arg) < 0)
		{
			DE_NOTI("v4l2_vsc_register error\n");
			return -1;
		}
		if(v4l2_vt_register(arg) < 0)
		{
			DE_NOTI("v4l2_vt_register error\n");
			return -1;
		}
		if(v4l2_gps_register(arg) < 0)
		{
			DE_NOTI("v4l2_gps_register error\n");
			//return -1;
		}
		if(v4l2_dolby_register(arg) < 0)

		{
			DE_NOTI("v4l2_dolby_register error\n");
			return -1;
		}
	} while(0);

	return 0;
}

void post_event(int win, int type, int val)
{
	struct vsc_priv *p;
	int len;
	char err_str[7][64] = {"FW exception : PC[0x50000016]",\
		"Mute status : 25006 (no signal)",\
		"FRC  status : 3203",\
		"Dolby vision meta error(HDMI) ", \
		"VCP empty, IPP & ND wait error", \
		"Input CSC error", \
		"manual error from vsc0 - cause[7] "};

	if (win>2)		{DE_NOTI("wid : not support(%d) skip\n",win);return;}
	if (!pfh[win])	{DE_NOTI("pfh : not ready(%d) skip\n",win);return;}
	p = pfh[win]->vsc_priv;
	if (!p)	{DE_NOTI("vsc_priv : not ready(%d) skip\n",win);return;}

	switch(type)
	{
		case 0:
			p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF;
			break;
		case 1:
			p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY;
			p->ev_data[0] = 0;
			p->ev_data[1] = val;
			p->ev_data[2] = 0;
			break;
		case 2:
			p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR;
			if(val > 6) val = 6;
			len = strlen(&err_str[val][0]);
			memset(p->ev_data, 0, 64);
			strncpy(p->ev_data, &err_str[val][0], len);
			p->ev_size = len;
			DE_NOTI("[len:%d] %s", len, p->ev_data);
			break;
		default:
			break;
	}
	if(p->process_poll)
	{
		p->process_poll(p);
	}

	return;
}

static int vsc_bbd_thread(void *ptr)
{
	int ret,wid;
	bool was_frozen;
	struct vsc_bbd_cfg cfg;
	struct v4l2_ext_vsc_active_win_info *pact;
	struct vsc_priv *p = (struct vsc_priv *)ptr;
	kwrap_vp_timing_info_t timing_info;
	struct v4l2_ext_vsc_input_src_info src_info;
	struct v4l2_ext_vsc_win_prop win_prop;

	if (!p) {DE_ERROR("p null\n");return 0;}
	if (!p->vsc_vdev) {DE_ERROR("vsc_vdev null\n");return 0;}

	wid = minor_num_to_win_id(p->vsc_vdev->num);

	if (wid>=LX_DE_WIN_MAX) {DE_ERROR("wid%d not support\n",wid);return 0;}

	pact = &_g_act_info[wid];

	DE_NOTI("start bbd%d-%05d%05d\n",wid,p->bbd_tid,p->bbd_pid);

	ret = vsc_bbd_init_cfg(wid,&cfg);
	if (ret<0)	{DE_ERROR("init err:%d\n",ret);return 0;}

	#ifdef V4L2_VSC_BBD_WAITQUEUE
	#else
	allow_signal(SIGUSR1);
	#endif
	set_freezable();

	while (!kthread_freezable_should_stop(&was_frozen))
	{
		if (was_frozen)	DE_NOTI("wakes up\n");
		if (kthread_should_stop()) {
			DE_NOTI("should stop\n");
			break;
		}

		#ifdef V4L2_VSC_BBD_WAITQUEUE
		ret = wait_event_interruptible_timeout(p->bbd_queue,p->bbd_condition,msecs_to_jiffies(40));
		if (ret == 0) {
			//DE_NOTI("time out\n");
		}
		else if (ret == -ERESTARTSYS) {
			DE_NOTI("received signal\n");
			break;
		}
		else {
			DE_NOTI("wake_up(condition:%d)\n",p->bbd_condition);
			break;
		}
		#else
		msleep_interruptible(40);
		#endif

		if (v4l2_vsc_init_stat != STAT_FW_DL_END) {
			if ((vsc_bbd_getdbglevel()>>wid)&1) DE_NOTI("skip[%d] : v4l2_vsc_init_stat:%d\n",wid,v4l2_vsc_init_stat);
			continue;
		}

		src_info = vsc_v4l2_get_input((UINT8)wid);
		if (src_info.src == V4L2_EXT_VSC_INPUT_SRC_NONE) {
			if ((vsc_bbd_getdbglevel()>>wid)&1) DE_NOTI("skip[%d] : src_info.src:%d\n",wid,src_info.src);
			continue;
		}

		ret = vsc_get_timinginfo((UINT8)wid,&timing_info);
		cfg.hsize = timing_info.hActive;
		cfg.vsize = timing_info.vActive;
		cfg.vfreq = timing_info.vFreq;

		ret = vsc_set_hdr_type(0,(UINT8)wid,&cfg.hdr_type);

		ret = vsc_set_sub_mode(0,(UINT8)wid,&win_prop);
		cfg.win_mode = win_prop.win_mode;

		if (1==vsc_bbd_checkupdate(&cfg))
		{
			p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN;
			if(p->process_poll)
			{
				pact->original.x = cfg.cur.org.x;
				pact->original.y = cfg.cur.org.y;
				pact->original.w = cfg.cur.org.w;
				pact->original.h = cfg.cur.org.h;
				pact->active.x = cfg.cur.act.x;
				pact->active.y = cfg.cur.act.y;
				pact->active.w = cfg.cur.act.w;
				pact->active.h = cfg.cur.act.h;

				DE_NOTI("noti -> [%d]%d, %d,%d,%d,%d, %d,%d,%d,%d\n",wid,cfg.hdr_type,\
					pact->original.x,pact->original.y,pact->original.w,pact->original.h,\
					pact->active.x,pact->active.y,pact->active.w,pact->active.h);

				p->process_poll(p);

			}
		}
	}

	DE_NOTI("end bbd%d-%05d%05d\n",wid,p->bbd_tid,p->bbd_pid);

	return 0;
}

int vsc_bbd_simpletest(BOOLEAN flag, unsigned char wid)
{
	struct vsc_priv *p;
	static struct task_struct *p_bbd_test_thread[LX_DE_WIN_MAX] = {0,0,0,0};

	if (wid>=LX_DE_WIN_MAX)	{DE_NOTI("wid[%d] is wrong\n",wid);return 0;}

	DE_NOTI("flag:%d,win:%d\n",flag,wid);

	if (!flag) {
		if (p_bbd_test_thread[wid]) {
			#ifdef V4L2_VSC_BBD_WAITQUEUE
			if (pfh[wid] && pfh[wid]->vsc_priv) {
				DE_NOTI("wake_up bbd_queue\n");
				p = pfh[wid]->vsc_priv;
				p->bbd_condition = 0;
				wake_up_interruptible(&p->bbd_queue);
			}
			#else
			send_sig(SIGUSR1,p_bbd_test_thread[wid],0);
			#endif
			kthread_stop(p_bbd_test_thread[wid]);
			p_bbd_test_thread[wid] = NULL;
			DE_NOTI("stop bbd%d\n",wid);
		}
	}
	else {
		if (!p_bbd_test_thread[wid]) {
			if (!pfh[wid])	{DE_NOTI("pfh[%d] is null\n",wid);return 0;}

			p = pfh[wid]->vsc_priv;
			if (!p)			{DE_NOTI("vsc_priv[%d] is null\n",wid);return 0;}

			#ifdef V4L2_VSC_BBD_WAITQUEUE
			init_waitqueue_head(&(p->bbd_queue));
			p->bbd_condition = 0;
			DE_NOTI("init bbd_queue\n");
			#endif

			p_bbd_test_thread[wid] = kthread_run(vsc_bbd_thread,p,"bbd%d-%05d%05d",wid,p->bbd_tid,p->bbd_pid);
			if (!p_bbd_test_thread[wid])	{DE_ERROR("bbd%d-%05d%05d fail",wid,p->bbd_tid,p->bbd_pid);return 0;}

			DE_NOTI("run bbd%d-%05d%05d\n",wid,p->bbd_tid,p->bbd_pid);
		}
	}
	return 0;
}

static void darc_thread(void *data)
{
	int ret=0;

	while(1)
	{
		//DE_NOTI("enter");
		ret = de_sync_wait(SYNC_WAIT_JPG); // wait arc/afd interrupt
		if(ret != RET_TIMEOUT) {
			DE_NOTI("event post");
			vsc_handle_darc_event();
			//DE_NOTI("timeout");
		}
	}
}

int v4l2_vsc_getlocalmute(int win)
{
	if (win > 3)	return 0;
	return _g_v4l2_vsc_local_mute[win];
}

static void v4l2_vp_thread(void *data)
{
	//struct vsc_dev *dev = data;
	static int count = 30;
	unsigned int i, mute1[4] = { 1,1,1,1 }, mute2[4] ={ 1,1,1,1 };

	#ifdef V4L2_VSC_APPLY_FREEZABLE
	bool was_frozen;
	set_freezable();
	#endif

	vsc_v4l2_vp_init();

	while(1)
	{
		#ifdef V4L2_VSC_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	DE_NOTI("wakes up\n");
		#endif

		if(v4l2_vsc_init_stat != STAT_SUSPEND)
		{
			vsc_v4l2_vp_thread();

			for(i=0;i<4;i++)
			{
				ipc_phys_hal_CheckMute(i, &mute1[i]);
				if(mute1[i] == 0 && mute1[i] != mute2[i])
				{
					_g_v4l2_vsc_local_mute[i] = 0;
					DE_NOTI("mute-off win[%d]", i);
				}
				else if(mute1[i] > 0 && mute1[i] != mute2[i])
				{
					_g_v4l2_vsc_local_mute[i] = mute1[i];
					DE_NOTI("mute-on win[%d] val[%d]\n",i, mute1[i]);
				}
				#ifdef INCLUDE_KDRV_OVI
				if (i == 0 && mute1[i] != mute2[i] && (mute1[i] == 0 || mute2[i] == 0))
				{
					UINT32 ovi_stat;
					OVI_HAL_GetStatus(&ovi_stat);
				}
				#endif
				mute2[i] = mute1[i];
			}

			vsc_bwm_noti();
		}
		msleep(40);

		if(count-- == 0)
		{
			count = 30;
		}
	}
}

static void update_mute_off_event(struct vsc_priv *p, int win)
{
	if(p)
	{
		if(minor_num_to_win_id(p->vsc_vdev->num) != win) return;

		p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF;
		if(p->process_poll)
		{
			p->process_poll(p);
		}
	}
}

static void update_video_delay_event(struct vsc_priv *p, int win, unsigned int delay)
{
	if(p)
	{
		p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY;
		p->ev_data[0] = win;
		p->ev_data[1] = delay & 0xFF;
		p->ev_data[2] = (delay >> 8) & 0xFF;
		p->ev_size = 3;
		if(p->process_poll)
		{
			p->process_poll(p);
		}
	}
}

static void update_error_event(struct vsc_priv *p, int win, char *str)
{
	unsigned int len;
	if(!str) return;
	if(p)
	{
		p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR;
		memset(p->ev_data, 0, 64);
		len = (unsigned int)strlen(str);
		if (len>64)	return;
		memcpy(p->ev_data, str, len);
		p->ev_size = len;
		if(p->process_poll)
		{
			p->process_poll(p);
		}
	}
}

int mute_thread_count = 0;
struct vsc_priv *g_priv_backup;
static int vsc_check_mute_thread(void *data)
{
	struct vsc_priv *p = data;
	int ret=0, i;
	#ifdef V4L2_VSC_APPLY_FREEZABLE
	bool was_frozen;
	#endif
	unsigned int gmute1[4] = { 1,1,1,1 }, gmute2[4] ={ 1,1,1,1 };
	struct vsc_priv *priv;
	unsigned int thread_index;

	DE_NOTI(": enter - %d", ++mute_thread_count);
	thread_index = mute_thread_count;
	if(mute_thread_count == 1)
		g_priv_backup = p;

	#ifdef V4L2_VSC_APPLY_FREEZABLE
	set_freezable();
	#endif

	while(!kthread_should_stop())
	{
		#ifdef V4L2_VSC_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	DE_NOTI("wakes up\n");
		#endif

		priv = p;
		if(g_priv_backup != priv) {
			msleep_interruptible(40);
			//continue;
		}
		else {
			ret = de_sync_wait(SYNC_WAIT_MUTEOFF);
		}
		if(!ret) // no time-out
		{
			for(i=0;i<4;i++) {
				ipc_phys_hal_CheckMute(i, &gmute1[i]);
				if(gmute1[i] == 0 && gmute2[i] != gmute1[i]) {
					ktime_t 	   t;
					struct timespec64 ts;
					unsigned int sec,msec,diff;
					unsigned int sec_old,msec_old;

					update_mute_off_event(p, i);
					sec_old  = t_vsc_sec_mute[i];
					msec_old = t_vsc_msec_mute[i];
					if(i<2) {
						t  = ktime_get_real();
						ts = ktime_to_timespec64(t);
						sec  = ts.tv_sec;
						msec = ts.tv_nsec/1000000;
						if(msec >= msec_old){
							diff = msec - msec_old;
						}
						else{
							diff = msec + (1000 - msec_old);
						}
						if(sec>sec_old) diff += (sec-sec_old)*1000;
					}
#if 0
					if(gmute1[i] == 0 && gmute2[i] != gmute1[i])
					{
						DE_NOTI("mute-off win[%d]\n",\
							i, gmute1[i]);
					}
#else
					if(thread_index==1 || (i>1 && thread_index==2)) {
						/*DE_NOTI("mute-off win[%d] %d msec(%d)",\
							i,(diff<600000)?diff:-1,thread_index);*/
					}
#endif
					if(gmute1[i] > 0 && gmute2[i] != gmute1[i])
					{
						/*DE_NOTI("mute-on win[%d] val[%d]\n",\
							i, gmute1[i]);*/
					}
				}
				gmute2[i] = gmute1[i];
			}
		}
		else{
			vsc_v4l2_report_csc_err(p);
			vsc_v4l2_report_fw_err(p);
			vsc_v4l2_report_ext_err(p);
		}
	}
	DE_NOTI(": leave - %d", --mute_thread_count);
	if(mute_thread_count==0) g_priv_backup = NULL;
	return 0;
}

static int vsc_check_delay_thread(void *data)
{
	struct vsc_priv *p = data;
	int ret;
	#ifdef V4L2_VSC_APPLY_FREEZABLE
	bool was_frozen;
	#endif
	unsigned int delay1[4] = { 1,1,1,1 }, delay2[4] ={ 1,1,1,1 };
	//unsigned int remain;

	DE_NOTI(": enter");

	#ifdef V4L2_VSC_APPLY_FREEZABLE
	set_freezable();
	#endif

	allow_signal(SIGUSR1);
	while(!kthread_should_stop())
	{
		unsigned int diff;
		LX_DE_FW_STATUS_REG_T fw_status;

		#ifdef V4L2_VSC_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	DE_NOTI("wakes up\n");
		#endif

		//remain = (unsigned int)msleep_interruptible(10);
		ret = de_sync_wait(SYNC_WAIT_VIDEO_DELAY);

		if(!ret) { //no timeout
			DE_NOTI("release thread work");
			break;
		}
		// timeout

		// check video pipeline delay
		if(ipc_phys_hal_CheckFwStatus(0, (void *)&fw_status)) {
			DE_NOTI("error");
		}
		delay1[0] = fw_status.reg_0.video_delay;
		delay1[0] = delay1[0]/100; // raw data : usec

		if(delay1[0] != delay2[0])
		{
			update_video_delay_event(p, 0, delay1[0]);
			//DE_NOTI("%p  %d", p, delay1[0]);
			if(delay1[0] > delay2[0])
				diff = delay1[0] - delay2[0];
			else
				diff = delay2[0] - delay1[0];
			//if(diff > 1000 && delay1[0] > 9)
				DE_NOTI("### video_pipeline_delay [%d ms] raw[%d]", delay1[0]/10, delay1[0]);
		}
		delay2[0] = delay1[0];
	}
	//DE_NOTI(": leave - remain[%d]", remain);
	DE_NOTI(": leave ");
	return 0;
}


static void update_win_post_event(struct vsc_priv *p, unsigned int wid, LX_DE_CB_INFO_T delay_info, int flag)
{
	unsigned int win_id;
	win_id = wid;
	if(win_id > LX_DE_WIN_MAX) win_id = 0;
	p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION;
	p->ev_data[0] = win_id;
	if(flag == 0) {
		p->ev_data[1] = (delay_info.owin_sync.rect.x >> 0) & 0xFF;
		p->ev_data[2] = (delay_info.owin_sync.rect.x >> 8) & 0xFF;
		p->ev_data[3] = (delay_info.owin_sync.rect.y >> 0) & 0xFF;
		p->ev_data[4] = (delay_info.owin_sync.rect.y >> 8) & 0xFF;
		p->ev_data[5] = (delay_info.owin_sync.rect.w >> 0) & 0xFF;
		p->ev_data[6] = (delay_info.owin_sync.rect.w >> 8) & 0xFF;
		p->ev_data[7] = (delay_info.owin_sync.rect.h >> 0) & 0xFF;
		p->ev_data[8] = (delay_info.owin_sync.rect.h >> 8) & 0xFF;
		p->ev_data[9]  = (delay_info.owin_sync.delay >> 0) & 0xFF;
		p->ev_data[10] = (delay_info.owin_sync.delay >> 8) & 0xFF;
	} else {
		p->ev_data[1] = (delay_info.video_delay_info[win_id].rect.x >> 0) & 0xFF;
		p->ev_data[2] = (delay_info.video_delay_info[win_id].rect.x >> 8) & 0xFF;
		p->ev_data[3] = (delay_info.video_delay_info[win_id].rect.y >> 0) & 0xFF;
		p->ev_data[4] = (delay_info.video_delay_info[win_id].rect.y >> 8) & 0xFF;
		p->ev_data[5] = (delay_info.video_delay_info[win_id].rect.w >> 0) & 0xFF;
		p->ev_data[6] = (delay_info.video_delay_info[win_id].rect.w >> 8) & 0xFF;
		p->ev_data[7] = (delay_info.video_delay_info[win_id].rect.h >> 0) & 0xFF;
		p->ev_data[8] = (delay_info.video_delay_info[win_id].rect.h >> 8) & 0xFF;
		p->ev_data[9]  = (delay_info.video_delay_info[win_id].delay >> 0) & 0xFF;
		p->ev_data[10] = (delay_info.video_delay_info[win_id].delay >> 8) & 0xFF;
	}

#ifdef V4L2_VSC_RETURN_PUNCH // https://harmony.lge.com:8443/issue/browse/SICREQ-1159
		p->ev_data[11] = (t_vsc_policy_punch[wid].x >> 0) & 0xFF;
		p->ev_data[12] = (t_vsc_policy_punch[wid].x >> 8) & 0xFF;
		p->ev_data[13] = (t_vsc_policy_punch[wid].y >> 0) & 0xFF;
		p->ev_data[14] = (t_vsc_policy_punch[wid].y >> 8) & 0xFF;
		p->ev_data[15] = (t_vsc_policy_punch[wid].w >> 0) & 0xFF;
		p->ev_data[16] = (t_vsc_policy_punch[wid].w >> 8) & 0xFF;
		p->ev_data[17] = (t_vsc_policy_punch[wid].h >> 0) & 0xFF;
		p->ev_data[18] = (t_vsc_policy_punch[wid].h >> 8) & 0xFF;
		DE_NOTI("vsc return event punch w[%d] %d/%d/%d/%d", wid, t_vsc_policy_punch[wid].x, t_vsc_policy_punch[wid].y,t_vsc_policy_punch[wid].w, t_vsc_policy_punch[wid].h);
#endif
	p->ev_size = 19;
	//DE_NOTI("win_id = %d, flag[%d]", win_id, flag);
	if(p->process_poll)
	{
		p->process_poll(p);
	}
}

static int vsc_update_resize_thread(void *data)
{
	struct vsc_priv *p = data;
	int ret;
	LX_DE_CB_INFO_T delay_info;
	unsigned int win;
	#ifdef V4L2_VSC_APPLY_FREEZABLE
	bool was_frozen;
	#endif

	unsigned int msec;
	unsigned int flag = 0;
	ktime_t 	   t;
	struct timespec64 ts;
	unsigned int diff, count=0, sum=0, avg;

	DE_NOTI(": enter");

	#ifdef V4L2_VSC_APPLY_FREEZABLE
	set_freezable();
	#endif

	while(!kthread_should_stop())
	{
		#ifdef V4L2_VSC_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	DE_NOTI("wakes up\n");
		#endif

		ret = de_sync_wait(SYNC_WAIT_DELAY);
		if(!ret) // no time-out
		{
			ret = resource_mgr_ioctl(DE_IOR_GET_VIDEO_DELAY_INT,(unsigned long)&delay_info,1);
			if(!ret)
			{
				//delay_info.owin_sync.win_id = 0;
				//win = delay_info.owin_sync.win_id;
				win = minor_num_to_win_id(p->vsc_vdev->num);
				if(win > 4) { DE_ERROR("invalid win [%d]", win); continue;}
				if(update_win_send_flag[0] != 0) continue;

				delay_info.owin_sync.rect.x = t_vsc_rect_prv[win].x;
				delay_info.owin_sync.rect.y = t_vsc_rect_prv[win].y;
				delay_info.owin_sync.rect.w = t_vsc_rect_prv[win].w;
				delay_info.owin_sync.rect.h = t_vsc_rect_prv[win].h;

				delay_info.owin_sync.delay = (delay_info.owin_sync.delay > 16)?16:delay_info.owin_sync.delay;
				update_win_post_event(p, 0, delay_info, 0);
				update_win_send_flag[0] = 1;

				count++;
				t  = ktime_get_real();
				ts = ktime_to_timespec64(t);
				msec = ts.tv_nsec/1000000;
				if(msec >= t_vsc_msec_prv[win]){
					diff = msec - t_vsc_msec_prv[win];
				}
				else{
					diff = msec + (1000 - t_vsc_msec_prv[win]);
				}
				sum += diff;
				avg = sum/count;
				if( t_vsc_rect_prv[win].x != delay_info.owin_sync.rect.x || \
					t_vsc_rect_prv[win].y != delay_info.owin_sync.rect.y || \
					t_vsc_rect_prv[win].w != delay_info.owin_sync.rect.w || \
					t_vsc_rect_prv[win].h != delay_info.owin_sync.rect.h) {
					flag = 1;
				}
				DE_NOTI("w[%d] delay[%d/%d/avg %d] %d/%d/%d/%d:%d/%d/%d/%d(%s)", \
					win, delay_info.owin_sync.delay,diff, avg,\
					t_vsc_rect_prv[win].x, t_vsc_rect_prv[win].y, t_vsc_rect_prv[win].w, t_vsc_rect_prv[win].h, \
					delay_info.owin_sync.rect.x, delay_info.owin_sync.rect.y, \
					delay_info.owin_sync.rect.w, delay_info.owin_sync.rect.h, \
					flag?"!=":"==");
			}
		}
	}
	DE_NOTI(": leave");
	return 0;
}

static int vsc_update_win_thread(void *data)
{
	struct vsc_priv *p = data;
	int ret;
	LX_DE_CB_INFO_T delay_info;
	unsigned int win;
	#ifdef V4L2_VSC_APPLY_FREEZABLE
	bool was_frozen;
	#endif

	unsigned int msec;
	unsigned int send_flag[LX_DE_WIN_4] = { 0 };
	ktime_t 	   t;
	struct timespec64 ts;
	unsigned int diff, count=0, sum=0, avg;
	int i;
	char systemd_opt[24];
	OS_ScanKernelCmdline("systemd.unit=%s", systemd_opt);

	DE_NOTI(": enter wid[%d]", minor_num_to_win_id(p->vsc_vdev->num));

	#ifdef V4L2_VSC_APPLY_FREEZABLE
	set_freezable();
	#endif

	while(!kthread_should_stop())
	{
		#ifdef V4L2_VSC_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	DE_NOTI("wakes up\n");
		#endif
		win = i = minor_num_to_win_id(p->vsc_vdev->num);
		send_flag[i] = 0;

		//ret = de_sync_wait(SYNC_WAIT_DELAY);
		//ret = de_sync_wait(SYNC_WAIT_VSYNC);
		ret = de_sync_wait_with_window(minor_num_to_win_id(p->vsc_vdev->num), SYNC_WAIT_VSYNC);
		if(!ret) // no time-out crash in this following...20240314
		{
			ret = resource_mgr_ioctl(DE_IOR_GET_VIDEO_DELAY_INT,(unsigned long)&delay_info,1);
			if(!ret)
			{
				//while(i--) 
				{
					struct v4l2_ext_vsc_connect_info param;
					ret = vsc_set_input(0, i, &param);
					if(param.out == V4L2_EXT_VSC_DEST_NONE)
						continue;

					win = delay_info.video_delay_info[i].win_id;
					if(win > LX_DE_WIN_4) continue;

#if 0
					delay_info.video_delay_info[i].rect.x = t_vsc_rect_prv[i].x;
					delay_info.video_delay_info[i].rect.y = t_vsc_rect_prv[i].y;
					delay_info.video_delay_info[i].rect.w = t_vsc_rect_prv[i].w;
					delay_info.video_delay_info[i].rect.h = t_vsc_rect_prv[i].h;
#endif
					delay_info.video_delay_info[i].delay = (delay_info.video_delay_info[i].delay > 16)?16:delay_info.video_delay_info[i].delay;
					//if(minor_num_to_win_id(p->vsc_vdev->num) == i) 
					{
						/*DE_NOTI("wid[%d] [%d,%d] %dx%d : %dx%d", \
							minor_num_to_win_id(p->vsc_vdev->num), i, delay_info.video_delay_info[i].win_id, \
							t_vsc_rect_prv[i].w, t_vsc_rect_prv[i].h, delay_info.video_delay_info[i].rect.w, delay_info.video_delay_info[i].rect.h);*/


						count++;
						t  = ktime_get_real();
						ts = ktime_to_timespec64(t);
						msec = ts.tv_nsec/1000000;
						if(msec >= t_vsc_msec_prv[i]){
							diff = msec - t_vsc_msec_prv[i];
						}
						else{
							diff = msec + (1000 - t_vsc_msec_prv[i]);
						}
						sum += diff;
						avg = sum/count;
						#if 0
						if( (t_vsc_rect_prv[i].x == delay_info.video_delay_info[i].rect.x && \
							t_vsc_rect_prv[i].y == delay_info.video_delay_info[i].rect.y && \
							t_vsc_rect_prv[i].w == delay_info.video_delay_info[i].rect.w && \
							t_vsc_rect_prv[i].h == delay_info.video_delay_info[i].rect.h)) {
							send_flag[i] = 1 ;
						}
						else
							send_flag[i] = 0;
						#endif
						//DE_NOTI("[%d ; %d]", send_flag, update_win_send_flag[win]);
						if(update_win_send_flag[win] == 0) {
						DE_NOTI("w[%d] delay[%d/%d/avg %d] %d/%d/%d/%d:%d/%d/%d/%d(%s)", \
							i, delay_info.video_delay_info[i].delay,diff, avg,\
							t_vsc_rect_prv[i].x, t_vsc_rect_prv[i].y, t_vsc_rect_prv[i].w, t_vsc_rect_prv[i].h, \
							delay_info.video_delay_info[i].rect.x, delay_info.video_delay_info[i].rect.y, \
							delay_info.video_delay_info[i].rect.w, delay_info.video_delay_info[i].rect.h, \
								send_flag[i]?"==":"!=");
							delay_info.video_delay_info[i].rect.x = t_vsc_rect_prv[i].x;
							delay_info.video_delay_info[i].rect.y = t_vsc_rect_prv[i].y;
							delay_info.video_delay_info[i].rect.w = t_vsc_rect_prv[i].w;
							delay_info.video_delay_info[i].rect.h = t_vsc_rect_prv[i].h;

							update_win_post_event(p, i, delay_info, 1);
							send_flag[i] = 1;
							update_win_send_flag[win] = 1;
						}
					}
				}
			}
		}
		else // if timeout occured, send prev window event
		{
			if(send_flag[i] == 0 && update_win_send_flag[win] == 0) {
				delay_info.video_delay_info[i].rect.x = t_vsc_rect_prv[i].x;
				delay_info.video_delay_info[i].rect.y = t_vsc_rect_prv[i].y;
				delay_info.video_delay_info[i].rect.w = t_vsc_rect_prv[i].w;
				delay_info.video_delay_info[i].rect.h = t_vsc_rect_prv[i].h;
				if(strstr(systemd_opt,"socts.target")) continue; // no socts mode, SOCTSSIC-132044
				DE_NOTI("timeout w[%d] %d/%d/%d/%d", i, \
					delay_info.video_delay_info[i].rect.x, delay_info.video_delay_info[i].rect.y, \
					delay_info.video_delay_info[i].rect.w, delay_info.video_delay_info[i].rect.h);

				update_win_post_event(p, i, delay_info, 1);
				send_flag[i] = 1;
				update_win_send_flag[win] = 1;
			}
		}
	}
	DE_NOTI(": leave");
	return 0;
}

static int vsc_v4l2_report_csc_err(struct vsc_priv *p)
{
	int ret = 0;
	char str[64];

	do {
		ret = vsc_check_csc_err(str);
		if (!ret)	break;//no err or skip
		update_error_event(p,0,str);
	} while(0);

	return 0;
}

static int vsc_v4l2_report_fw_err(struct vsc_priv *p)
{
	int ret = 0;
	char str[64];

	do {
		str[0] = 0;
		ret = vsc_check_fw_err(str);
		if (!ret)	break;//no err or skip
		update_error_event(p,0,str);
		DE_NOTI("str: %s", str);
	} while(0);

	return 0;
}

static int vsc_v4l2_report_ext_err(struct vsc_priv *p)
{
	int ret = 0;
	char str[64];

	do {
		str[0] = 0;
		ret = vsc_check_cvi_err(str);
		if (!ret)	break;//no err or skip
		update_error_event(p,0,str);
		DE_NOTI("str: %s", str);
	} while(0);

	return 0;
}

