#ifndef _V4L2_DOLBY_H
#define _V4L2_DOLBY_H

#include "hdr_v4l2_cmn.h"

#define V4L2_EXT_DEV_NO_DHDR     240
#define MAX_WIN	4
#define VSC_SRC_TYPE_INDEX 0
#define MAX_NAME_LENGTH 255

struct vsc_dolby_data {
	struct v4l2_control *ctrl;
	UINT32 extra[2]; /*Extra information*/
};

struct dolby_priv
{
	struct list_head list;

	/* dolby  */
	int dolby_poll;
	wait_queue_head_t dolby_poll_wq;
	void (*process_poll)(struct dolby_priv *v);
	struct work_struct dolby_noti_work;
	struct video_device *dolby_vdev;
	unsigned int event;
};

int v4l2_dolby_register(void *arg);
int vsc_v4l2_dolby_event( UINT8 win,UINT32 event_id,struct vsc_dolby_data *pInfo);
int vpq_v4l2_dolby_event(UINT8 win,UINT32 event_id,void *pData);
int vpq_v4l2_set_ext_ctrl_dolby(struct v4l2_ext_control *ctrl);
int vpq_v4l2_set_ctrl_dolby(struct v4l2_control *ctrl);
int vpq_v4l2_get_ctrl_dolby(struct v4l2_control *ctrl);
int dolby_get_ext_ctrl(struct v4l2_ext_control *ctrl);

int vpq_proc_show_status_dolby(struct seq_file *m, void *v, int id);
int vpq_v4l2_compat_ext_ctrl_dolby(struct v4l2_ext_control *ctrl);

#endif //_V4L2_DOLBY_H
