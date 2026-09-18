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
 *  event file for VBE device
 *
 *  author
 *  version		1.0
 *  date		2025.03.12
 *  note
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
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
#include <linux/freezer.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"

#include "os_util.h"
#include "debug_util.h"
#include "be_dbg.h"
#include "vbe_cfg.h"
#include "vbe_event.h"
#include "pwm_hal.h"
#include "be_top_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vbe_evt_cfg {
    struct mutex clk_mlock;
    spinlock_t clk_slock;
	unsigned int clk_cond;
	wait_queue_head_t clk_wq;
	unsigned int clk;
	unsigned int state;
	unsigned int init;
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
static int vbe_led_task_init(struct vbe_dev *drv);
static int vbe_led_task_run(struct vbe_dev *drv);
static int vbe_led_task_stop(struct vbe_dev *drv);
static int vbe_led_event_prepare(struct vbe_dev_task *t, struct vbe_evt_cfg *p);
static int vbe_led_event_late(struct vbe_dev_task *t, struct vbe_evt_cfg *p);
static int vbe_led_thread(void *ptr);

void vbe_evt_status(struct seq_file *m, void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vbe_evt_cfg _g_vbe_evt_cfg = {.init=0};
static int _g_vbe_evt_dbg_apl = -1;
module_param_named(vbe_evt_apl, _g_vbe_evt_dbg_apl, int, 0644);

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
int vbe_event_init(void)
{
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (!p->init) {
		memset(p,0,sizeof(struct vbe_evt_cfg));

		mutex_init(&p->clk_mlock);
		spin_lock_init(&p->clk_slock);
		init_waitqueue_head(&p->clk_wq);
		p->init = 1;
	}

	return 0;
}

int vbe_evt_noti_chg_clk_wait(void)
{
	int ret;
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (p->state == vbe_evt_state_none) {
		BE_NOTI("skip\n");
		return 0;
	}

	p->state = vbe_evt_state_rcv_chg_clk_n_wait;

	BE_NOTI("state to %d, wait_event\n",p->state);
	p->clk_cond = 0;
	ret = wait_event_interruptible_timeout(p->clk_wq,p->clk_cond,msecs_to_jiffies(50));
	if (ret == 0) {
		BE_NOTI("time out\n");
	}
	else if (ret < 0) {
		BE_NOTI("received signal\n");
	}
	else {
		BE_NOTI("wakeup\n");
	}

	return 0;
}

int vbe_evt_noti_chg_clk_done(unsigned int clk)
{
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (p->state == vbe_evt_state_none) {
		BE_NOTI("skip\n");
		return 0;
	}

	BE_PWM_HAL_SetClk(clk);
	p->clk = clk;
	p->state = vbe_evt_state_chg_clk_done;

	return 0;
}

int vbe_led_subscribe_event(struct vbe_priv *priv)
{
	struct video_device *vdev;
	struct vbe_dev *drv;
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (!priv) {BE_ERROR("priv null\n");return -1;}
	vdev = priv->vdev;
	if (!vdev) {BE_ERROR("vdev null\n");return -1;}
	drv = video_get_drvdata(vdev);
	if (!drv)  {BE_ERROR("drv null\n");return -1;}

	if (vbe_led_task_init(drv)) {
		BE_ERROR("vbe_led_task_init err\n");
		return -1;
	}

	mutex_lock(&p->clk_mlock);
	if (drv->led_task.ev_sub == 0) {
		if (vbe_led_task_run(drv)) {
			BE_ERROR("vbe_led_task_run err\n");
			return -1;
		}
	}

	// spin_lock(&drv->led_task.slock);
	priv->led_sub_cnt++;
	if (priv->led_sub_cnt == 1) {
		drv->led_task.ev_sub = (drv->led_task.ev_sub<<1)|1;
	}
	// spin_unlock(&drv->led_task.slock);
	BE_NOTI("led cnt:%d, ev_sub:0x%x\n",priv->led_sub_cnt,drv->led_task.ev_sub);
	mutex_unlock(&p->clk_mlock);

	return 0;
}

int vbe_led_unsubscribe_event(struct vbe_priv *priv)
{
	struct video_device *vdev;
	struct vbe_dev *drv;
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (!priv) {BE_ERROR("priv null\n");return -1;}
	vdev = priv->vdev;
	if (!vdev) {BE_ERROR("vdev null\n");return -1;}
	drv = video_get_drvdata(vdev);
	if (!drv)  {BE_ERROR("drv null\n");return -1;}

	mutex_lock(&p->clk_mlock);
	if (priv->led_sub_cnt) {
		priv->led_sub_cnt--;
		if (priv->led_sub_cnt == 0) {
			drv->led_task.ev_sub = (drv->led_task.ev_sub>>1);
		}
	}
	BE_NOTI("led cnt:%d, ev_sub:0x%x\n",priv->led_sub_cnt,drv->led_task.ev_sub);

	if (drv->led_task.ev_sub == 0) {
		vbe_led_task_stop(drv);
	}
	mutex_unlock(&p->clk_mlock);

	return 0;
}

int vbe_led_release(struct file *flie)
{
	struct vbe_dev *drv;
	struct vbe_fh *fh;
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (!flie) {BE_ERROR("flie null\n");return -1;}
	drv = video_drvdata(flie);
	if (!drv)  {BE_ERROR("drv null\n");return -1;}
	fh = flie->private_data;
	if (!fh)   {BE_ERROR("fh null\n");return -1;}

	mutex_lock(&p->clk_mlock);
	if (fh->vbe_priv->led_sub_cnt) {
		fh->vbe_priv->led_sub_cnt = 0;
		drv->led_task.ev_sub = (drv->led_task.ev_sub>>1);
	}
	BE_NOTI("led cnt:%d, ev_sub:0x%x\n",fh->vbe_priv->led_sub_cnt,drv->led_task.ev_sub);

	if (drv->led_task.ev_sub == 0) {
		vbe_led_task_stop(drv);
	}
	mutex_unlock(&p->clk_mlock);

	return 0;
}

int vbe_led_wakeup(struct vbe_dev *drv, int sig)
{
	if (!drv) {
		//BE_ERROR("drv null\n");
		return -1;
	}

	if (drv->led_task.ev_sub || sig) {
		BE_PRINT_EVT("wake_up(cond:%d to 1)\n",drv->led_task.cond);
		drv->led_task.cond = 1;
		wake_up_interruptible_all(&drv->led_task.wq);
	}

	return 0;
}

static int vbe_led_task_init(struct vbe_dev *drv)
{
	struct vbe_dev_task *led_t;

	if (!drv) {
		BE_ERROR("drv null\n");
		return -1;
	}

	led_t = &drv->led_task;

	if (!led_t->init) {
		spin_lock_init(&led_t->slock);
		mutex_init(&led_t->mlock);
		init_waitqueue_head(&led_t->wq);
		led_t->evt.type = V4L2_EVENT_VSYNC;
		led_t->evt.id = V4L2_CID_EXT_VBE_SUBSCRIBE_DPC;
		led_t->cond = 0;
		BE_NOTI("init led_task.wq\n");
		led_t->init = 1;
	}

	return 0;
}

static int vbe_led_task_run(struct vbe_dev *drv)
{
	struct vbe_dev_task *led_t;

	if (!drv) {
		BE_ERROR("drv null\n");
		return -1;
	}

	led_t = &drv->led_task;

	if (!led_t->thread) {
		led_t->tx_cnt = led_t->rx_cnt = 0;
		led_t->thread = kthread_run(vbe_led_thread,drv,"led_task");
		if (IS_ERR(led_t->thread)) {
			int err = PTR_ERR(led_t->thread);
			BE_ERROR("kthread_run err(%d)\n",err);
			led_t->thread = NULL;
			return err;
		}
		BE_NOTI("run led_task\n");
	}

	return 0;
}

static int vbe_led_task_stop(struct vbe_dev *drv)
{
	struct vbe_dev_task *led_t;

	if (!drv) {
		BE_ERROR("drv null\n");
		return -1;
	}

	led_t = &drv->led_task;

	if (led_t->thread) {
		vbe_led_wakeup(drv,1);
		kthread_stop(led_t->thread);
		led_t->thread = NULL;
		BE_NOTI("stop led_task\n");
	}

	return 0;
}

static int vbe_led_event_prepare(struct vbe_dev_task *t, struct vbe_evt_cfg *p)
{
	if (!t || !p) {
		BE_ERROR("t or p null\n");
		return -1;
	}

	if (p->state == vbe_evt_state_rcv_chg_clk_n_wait) {
		BE_PWM_HAL_SetCtrlStop(1);
		p->state = vbe_evt_state_stop_evt_n_ctl_off;
		BE_NOTI("state to vbe_evt_state_stop_evt_n_ctl_off\n");
	}
	else if (p->state == vbe_evt_state_stop_evt_n_ctl_off) {
		p->clk_cond = 1;
		wake_up_interruptible_all(&p->clk_wq);
		p->state = vbe_evt_state_stop_evt_n_wake_up;
		BE_NOTI("state to vbe_evt_state_stop_evt_n_wake_up\n");
	}
	else if (p->state == vbe_evt_state_chg_clk_done) {
		BE_PWM_HAL_SetCtrlStop(0);
		p->state = vbe_evt_state_normal;
		BE_NOTI("state to vbe_evt_state_normal\n");
	}

	if (p->state == vbe_evt_state_normal) {
		UINT32 apl = (UINT32)_g_vbe_evt_dbg_apl;
		if (apl > 1023) {
			BE_TOP_HAL_GetDispApl(&apl);
		}
		memcpy(t->evt.u.data,&apl,sizeof(apl));
	}

	return 0;
}

static int vbe_led_event_late(struct vbe_dev_task *t, struct vbe_evt_cfg *p)
{
	//do nothing
	return 0;
}

static int vbe_led_thread(void *ptr)
{
	int ret;
	bool was_frozen;
	struct vbe_dev_task *t;
	struct vbe_dev *drv = (struct vbe_dev *)ptr;
    unsigned long wait_timeout = msecs_to_jiffies(1000);
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;

	if (!drv) {BE_ERROR("p null\n");return 0;}
	if (!drv->vdev) {BE_ERROR("vdev null\n");return 0;}

	t = &drv->led_task;
	p->state = vbe_evt_state_normal;

	BE_NOTI("start %s\n",current->comm);

	set_freezable();

	while (!kthread_freezable_should_stop(&was_frozen))
	{
		if (was_frozen)	BE_NOTI("wakes up\n");
		if (kthread_should_stop()) {
			BE_NOTI("should stop\n");
			break;
		}

		t->cond = 0;
		ret = wait_event_interruptible_timeout(t->wq,t->cond,wait_timeout);
		if (ret == 0) {
			BE_PRINT_EVT("time out\n");
			continue;
		}
		else if (ret < 0) {
			BE_NOTI("received signal\n");
			break;
		}

		vbe_led_event_prepare(t,p);
		BE_PRINT_EVT("evt_q (t:%3d)(r:%3d)(state:%d)\n",t->tx_cnt,t->rx_cnt,p->state);
		if (p->state == vbe_evt_state_normal) {
			v4l2_event_queue(drv->vdev,&t->evt);
		}
		t->tx_cnt = (t->tx_cnt<0xff)? (t->tx_cnt+1):0;
		vbe_led_event_late(t,p);
	}

	p->state = vbe_evt_state_none;
	BE_NOTI("end %s\n",current->comm);

	return 0;
}

void vbe_evt_status(struct seq_file *m, void* data)
{
	struct vbe_evt_cfg *p = &_g_vbe_evt_cfg;
	seq_printf(m, "init:%d clk:%d cond:%d state:%d\n",p->init,p->clk,p->clk_cond,p->state);
}
