/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file vbe_cfg.h
 *
 *  It is the header file for controling v4l2 BE driver.
 *
 *  @author
 *  @version
 *  @date
 *  @see
 */

#ifndef _VBE_CFG_H
#define _VBE_CFG_H

#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/videobuf2-v4l2.h>

#ifndef V4L2_CID_USER_EXT_VBE_BASE
#define V4L2_CID_USER_EXT_VBE_BASE (V4L2_CID_USER_BASE + 0x4000)
#endif

#ifndef V4L2_CID_EXT_VBE_BASE
#define V4L2_CID_EXT_VBE_BASE (V4L2_CID_USER_EXT_VBE_BASE)
#endif

#ifndef V4L2_CID_EXT_VBE_SUBSCRIBE_DPC
#define V4L2_CID_EXT_VBE_SUBSCRIBE_DPC (V4L2_CID_EXT_VBE_BASE + 47)
#endif
#ifndef V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC
#define V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC (V4L2_CID_EXT_VBE_BASE + 48)
#endif
struct vbe_priv {
	struct video_device *vdev;
	struct list_head list;
	wait_queue_head_t poll_wq;
	unsigned int led_sub_cnt;
};

struct vbe_dev_task {
	struct task_struct *thread;
	wait_queue_head_t wq;
	unsigned int ev_sub;
	spinlock_t slock;
    struct mutex mlock;
	struct v4l2_event evt;
	unsigned int tx_cnt;
	unsigned int rx_cnt;
	int cond;
	int init;
};

struct vbe_dev {
	struct platform_device *pdev;
	struct v4l2_device *v4l2_dev;
	struct video_device *vdev;
	struct vbe_dev_task led_task;

#ifdef INCLUDE_KDRV_PQE_PM
	struct pqe_pm_config *pqe_pm_cfg;
	int pqe_pm_id;
#endif
};

struct vbe_priv *new_vbe_priv(void);

struct vbe_fh {
	struct v4l2_fh fh;
	struct vbe_priv *vbe_priv;
};

#endif  /* _VBE_CFG_H */
