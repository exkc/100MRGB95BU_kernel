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
#include <linux/time.h>
#include <linux/delay.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>

#include "os_util.h"
#include "proc_util.h"
#include "base_device.h"
#include "de_def.h"
#include "v4l2_vsc_bbd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_VSC_BBD_INFO_MAX 25
#define V4L2_VSC_BBD_HIST_MAX 50

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

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
};

struct vsc_fh {
	struct v4l2_fh fh;
// need to add some private data
	struct vsc_priv *vsc_priv;
};

struct vsc_bbd_info{
	pid_t tid;
	pid_t pid;
	struct vsc_fh *pfh;
	int subscribed;
};

union vsc_bbd_update{
	unsigned int data;
	struct {
	unsigned int wid           :2;//1:0
	unsigned int open          :1;//2
	unsigned int open_en       :1;//3
	unsigned int sub0          :1;//4
	unsigned int sub0_en       :1;//5
	unsigned int sub1          :1;//6
	unsigned int sub1_en       :1;//7
	unsigned int sub2          :1;//8
	unsigned int sub2_en       :1;//9
	unsigned int sub3          :1;//10
	unsigned int sub3_en       :1;//11
	};
};

struct vsc_bbd_hist_inf{
	unsigned int sec;
	unsigned int msec;
	unsigned int usec;
	pid_t tid;
	pid_t pid;
	struct vsc_fh *pfh;
	union vsc_bbd_update up;
};

struct vsc_bbd_hist{
	unsigned int cnt;
	struct vsc_bbd_hist_inf info[V4L2_VSC_BBD_HIST_MAX];
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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int _g_vsc_bbd_init = 0;
static struct vsc_bbd_info _g_vsc_bbd0_info[V4L2_VSC_BBD_INFO_MAX];
static struct vsc_bbd_info _g_vsc_bbd1_info[V4L2_VSC_BBD_INFO_MAX];
static struct vsc_bbd_hist _g_vsc_bbd_hist;

/*========================================================================================
	Implementation Group
========================================================================================*/


/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static int bbd_proc_show(struct seq_file *m, void *v)
{
	int i;
	struct vsc_bbd_info *p_inf;
	struct vsc_bbd_hist *p_hist;
	struct vsc_bbd_hist_inf *p_hist_inf;

	if (!m)	return 0;

	p_inf = _g_vsc_bbd0_info;
	seq_printf(m, "----------------------------\n");
	seq_printf(m, "info\n");
	seq_printf(m, "----------------------------\n");
	for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
	{
		if (!p_inf[i].tid)	continue;
		seq_printf(m, "[%02d]tid:%05d,pid:%05d,fh:%p,subs:%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);
	}
	p_inf = _g_vsc_bbd1_info;
	seq_printf(m, "----------------------------\n");
	for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
	{
		if (!p_inf[i].tid)	continue;
		seq_printf(m, "[%02d]tid:%05d,pid:%05d,fh:%p,subs:%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);
	}
	p_hist = &_g_vsc_bbd_hist;
	seq_printf(m, "----------------------------\n");
	seq_printf(m, "history\n");
	seq_printf(m, "----------------------------\n");
	seq_printf(m, "init:%d, cnt : %d\n",_g_vsc_bbd_init,p_hist->cnt);
	for (i=0; i<V4L2_VSC_BBD_HIST_MAX; i++)
	{
		p_hist_inf = &(p_hist->info[i]);
		if ((p_hist_inf->sec|p_hist_inf->msec|p_hist_inf->usec)==0)	continue;
		seq_printf(m, "[%02d][%06d.%03d%03d]t:%05d,p:%05d,f:%p(i:%d,o:%d,%d,s:%d,%d|%d,%d|%d,%d|%d,%d)\n",i,\
			p_hist_inf->sec,p_hist_inf->msec,p_hist_inf->usec,p_hist_inf->tid,p_hist_inf->pid,p_hist_inf->pfh,\
			p_hist_inf->up.wid,p_hist_inf->up.open,p_hist_inf->up.open_en,\
			p_hist_inf->up.sub0,p_hist_inf->up.sub0_en,p_hist_inf->up.sub1,p_hist_inf->up.sub1_en,\
			p_hist_inf->up.sub2,p_hist_inf->up.sub2_en,p_hist_inf->up.sub3,p_hist_inf->up.sub3_en);
	}
	seq_printf(m, "----------------------------\n");
	return 0;
}

static int bbd_proc_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, bbd_proc_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}

static struct file_operations bbd_proc_fops = {
	.open = bbd_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void v4l2_vsc_bbd_proc_init(struct proc_dir_entry *entry)
{
	if (!entry)
	{
		DE_ERROR("entry is not ready\n");
		return;
	}

	proc_create_data("bbd-status", 0440, entry, &bbd_proc_fops, NULL);

	return;
}

int v4l2_vsc_bbd_init(void)
{
	if (!_g_vsc_bbd_init)
	{
		memset(_g_vsc_bbd0_info,0,sizeof(struct vsc_bbd_info)*V4L2_VSC_BBD_INFO_MAX);
		memset(_g_vsc_bbd1_info,0,sizeof(struct vsc_bbd_info)*V4L2_VSC_BBD_INFO_MAX);
		memset(&_g_vsc_bbd_hist,0,sizeof(struct vsc_bbd_hist));
		_g_vsc_bbd_hist.cnt = V4L2_VSC_BBD_HIST_MAX;
		_g_vsc_bbd_init = 1;
	}
	return 0;
}

static int v4l2_vsc_bbd_get_id(int wid, struct vsc_bbd_info *p_inf, pid_t tid)
{
	int i;

	if (wid>1)	{DE_NOTI("not support\n");return -1;}
	if (!p_inf)	{DE_NOTI("fh null\n");return -2;}
	if (!tid)	{DE_NOTI("tid 0\n");return -3;}

	/* searching same tid */
	for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
	{
		if (p_inf[i].tid == tid)	break;
	}

	/* if can't, searching the 1st tid 0 */
	if (i >= V4L2_VSC_BBD_INFO_MAX)
	{
		for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
		{
			if (p_inf[i].tid == 0)	break;
		}
	}
	return i;
}

static int v4l2_vsc_bbd_update_history(pid_t tid,pid_t pid,int wid,void *fh,int up_op,unsigned int up_id,int id_en)
{
	unsigned int cnt,sec,msec,usec;
	struct vsc_bbd_hist_inf *p_inf;

	cnt = _g_vsc_bbd_hist.cnt;

	cnt++;
	if (cnt>=V4L2_VSC_BBD_HIST_MAX)	cnt = 0;
	_g_vsc_bbd_hist.cnt = cnt;

	p_inf = &_g_vsc_bbd_hist.info[cnt];

	memset(p_inf,0,sizeof(struct vsc_bbd_hist_inf));

	OS_GetCurrentTicks(&sec, &msec, &usec);

	p_inf->sec = sec;
	p_inf->msec = msec;
	p_inf->usec = usec;
	p_inf->tid = tid;
	p_inf->pid = pid;
	p_inf->up.wid = wid;

	if (fh)
	{
		p_inf->pfh = (struct vsc_fh *)fh;
	}

	if (up_op)
	{
		p_inf->up.open = 1;
		p_inf->up.open_en = (up_op==1)? 1:0;
	}

	switch (up_id)
	{
		case V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF:
			p_inf->up.sub0 = 1;
			p_inf->up.sub0_en = id_en;
			break;
		case V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN:
			p_inf->up.sub1 = 1;
			p_inf->up.sub1_en = id_en;
			break;
		case V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION:
			p_inf->up.sub2 = 1;
			p_inf->up.sub2_en = id_en;
			break;
		case V4L2_CID_EXT_VSC_SUBSCRIBE_ADAPTIVE_STREAM_AR_INFORMATION:
			p_inf->up.sub3 = 1;
			p_inf->up.sub3_en = id_en;
			break;
		default:
			break;
	}

	DE_NOTI("[%02d][%06d.%03d%03d]t:%05d,p:%05d,f:%p(i:%d,o:%d,%d,s:%d,%d|%d,%d|%d,%d|%d,%d)\n",cnt,\
		p_inf->sec,p_inf->msec,p_inf->usec,p_inf->tid,p_inf->pid,p_inf->pfh,\
		p_inf->up.wid,p_inf->up.open,p_inf->up.open_en,\
		p_inf->up.sub0,p_inf->up.sub0_en,p_inf->up.sub1,p_inf->up.sub1_en,\
		p_inf->up.sub2,p_inf->up.sub2_en,p_inf->up.sub3,p_inf->up.sub3_en);

	return 0;
}

int v4l2_vsc_bbd_update_info(int wid,void *fh)
{
	int i;
	pid_t tid,pid;
	struct vsc_bbd_info *p_inf;

	if (wid>1)	{DE_NOTI("not support\n");return -1;}
	if (!_g_vsc_bbd_init)	{DE_NOTI("not init\n");return -2;}

	tid = task_tgid_nr(current);
	pid = task_pid_nr(current);

	DE_NOTI("tid:pid(%05d:%05d)\n",tid,pid);//pid_t(:=int)

	do {
		p_inf = (wid==0)? _g_vsc_bbd0_info:_g_vsc_bbd1_info;
		i = v4l2_vsc_bbd_get_id(wid,p_inf,tid);

		if (i<0 || i>=V4L2_VSC_BBD_INFO_MAX)	{DE_NOTI("(%d) is wrong\n",i);break;}

		if (fh)	//open:add info
		{
			p_inf[i].tid = tid;
			p_inf[i].pid = pid;
			p_inf[i].pfh = (struct vsc_fh *)fh;
			p_inf[i].subscribed = 0;
		}
		else	//close:delete info
		{
			if (p_inf[i].tid == 0)		{DE_NOTI("(%d) nothing to delete\n",i);break;}
			p_inf[i].tid = 0;
			p_inf[i].pid = 0;
			p_inf[i].pfh = 0;
			p_inf[i].subscribed = 0;
		}
		DE_NOTI("[%02d]%05d:%05d,%p,%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);
	} while(0);

	v4l2_vsc_bbd_update_history(tid,pid,wid,fh,(fh)? 1:2,0,0);

	return 0;
}

int v4l2_vsc_bbd_update_subscribe(int wid, unsigned int id, int flag, void *fh)
{
	int i;
	pid_t tid,pid;
	struct vsc_bbd_info *p_inf;

	if (wid>1)	{DE_NOTI("not support\n");return -1;}
	if (!_g_vsc_bbd_init)	{DE_NOTI("not init\n");return -2;}

	tid = task_tgid_nr(current);
	pid = task_pid_nr(current);

	DE_NOTI("tid:pid(%05d:%05d),subid:0x%08x\n",tid,pid,id);//pid_t(:=int)

	do {
		if (id != V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN)	break;

		p_inf = (wid==0)? _g_vsc_bbd0_info:_g_vsc_bbd1_info;
		i = v4l2_vsc_bbd_get_id(wid,p_inf,tid);

		if (i<0 || i>=V4L2_VSC_BBD_INFO_MAX)	{DE_NOTI("(%d) is wrong\n",i);break;}
		if (p_inf[i].tid == 0)					{DE_NOTI("(%d)nothing to subs\n",i);break;}

		p_inf[i].subscribed = flag;
		DE_NOTI("[%02d]%05d:%05d,%p,%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);
	} while(0);

	if (id == V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN || \
		id == V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION || \
		id == V4L2_CID_EXT_VSC_SUBSCRIBE_ADAPTIVE_STREAM_AR_INFORMATION)
	{
		v4l2_vsc_bbd_update_history(tid,pid,wid,fh,0,id,flag);
	}

	return 0;
}

int v4l2_vsc_bbd_check_subscribed(int wid)
{
	int i;
	struct vsc_bbd_info *p_inf;

	if (wid>1)	{DE_NOTI("not support\n");return -1;}
	if (!_g_vsc_bbd_init)	{DE_NOTI("not init\n");return -2;}

	p_inf = (wid==0)? _g_vsc_bbd0_info:_g_vsc_bbd1_info;

	for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
	{
		if (p_inf[i].tid!=0 && p_inf[i].pfh!=0 && p_inf[i].subscribed!=0)	break;
	}

	if (i>=V4L2_VSC_BBD_INFO_MAX)		{DE_NOTI("(%d)nothing subs\n",i);return -3;}

	DE_NOTI("[%02d]%05d:%05d,%p,%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);

	return 0;
}

int v4l2_vsc_bbd_noti_poll(int wid)
{
	int i;
	struct vsc_priv *p;
	struct vsc_bbd_info *p_inf;

	if (wid>1)	{DE_NOTI("not support\n");return -1;}
	if (!_g_vsc_bbd_init)	{DE_NOTI("not init\n");return -2;}

	p_inf = (wid==0)? _g_vsc_bbd0_info:_g_vsc_bbd1_info;

	for (i=0; i<V4L2_VSC_BBD_INFO_MAX; i++)
	{
		if (p_inf[i].tid!=0 && p_inf[i].pfh!=0 && p_inf[i].subscribed!=0)
		{
			p = p_inf[i].pfh->vsc_priv;
			DE_NOTI("[%02d]%05d:%05d,%p,%d\n",i,p_inf[i].tid,p_inf[i].pid,p_inf[i].pfh,p_inf[i].subscribed);
			if (p)
			{
				p->event = V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN;
				p->process_poll(p);
			}
			else
			{
				DE_NOTI("[%02d]skip\n",i);
			}
		}
	}

	return 0;
}

