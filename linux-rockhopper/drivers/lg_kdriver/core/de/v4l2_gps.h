#ifndef __V4L2_GPS_H__
#define __V4L2_GPS_H__


#include "v4l2_lg_dev_configs.h"

#define WQ_IMPL		1

// Coverity issues - CID 286916, 286914
#define __ALIGN_MASK_GPS(x, mask)	(((x) + (mask)) & ~(mask))
#define __ALIGN_GPS(x, a)           __ALIGN_MASK_GPS(x, (typeof(x))(a) - 1)
#define ALIGN_64(addr)          __ALIGN_GPS(addr, 64)


/* The maximum number of vivid devices */
#define GPS_MAX_DEVS            8
#define GPS_MAX_WIDTH           1920
#define GPS_MAX_HEIGHT          1080

#define V4L2_EXT_DEV_NO_GPS     70


#ifndef V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE
#define V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE \
	    (V4L2_CID_USER_EXT_GPSCALER_BASE + 2)
#endif

#ifndef V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE \
	    (V4L2_CID_USER_EXT_GPSCALER_BASE + 3)
#endif

#ifndef V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H \
	    (V4L2_CID_USER_EXT_GPSCALER_BASE + 4)
#endif

#ifndef V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V \
	    (V4L2_CID_USER_EXT_GPSCALER_BASE + 5)
#endif


extern const struct vb2_mem_ops vb2_gps_memops;

extern struct capture_device_info capture_devs[MAX_CAPTURE_DEVS];
extern struct pixel_format_info pixel_formats_mp[MAX_FORMAT_CNT_MP];
extern struct pixel_format_info pixel_formats_sp[MAX_FORMAT_CNT_SP];
extern struct frame_size_info frame_sizes[MAX_FRAME_SIZE_CNT];
extern struct frame_interval_info frame_intervals[MAX_FRAME_INTER_CNT];
extern struct v4l2_queryctrl gps_v4l2_queryctrl[MAX_CNTRL_CNT];
extern struct v4l2_querymenu gps_v4l2_querymenu[MAX_MENU_CNT];

enum capture_fmt{
	E_FMT_YUV420 = 0,
	E_FMT_YUV422 = 1,
	E_FMT_ARGB32 = 2,
	E_FMT_ABGR32 = 3,
	E_FMT_RGBA32 = 4
};

struct gps_dev {
    struct platform_device *pdev;
    struct v4l2_device  v4l2_gps_dev;
    struct video_device v4l2_gps_video_dev;
	struct video_device v4l2_ttv_video_dev;
    struct mutex        v4l2_gps_video_device_lock;
    rwlock_t            v4l2_gps_list_lock; /* Lock to access internal vb2 queue list to support multi-capture */
    struct vb2_queue    vb_gps_cap_q;
    BOOLEAN             _IsCapThreadRunning;
    unsigned int        multiplanar;
    unsigned            num_inputs;
    struct capture_device_info   dev_info;
};

struct file_vb2_q {
    struct file      *file;
    struct vb2_queue queue;
    struct mutex     gps_vb2_queue_lock;
};

struct gps_cap_buffer {
    struct vb2_v4l2_buffer vb; /* must be as first   element */
    struct list_head      list;
};

struct gps_fh {
    struct v4l2_fh   fh;
    struct gps_priv *gps_priv; /* For context storing */
};

struct gps_cap_info {
    void *a2m;
    void *m2a;

    LX_DE_GPS_CTRL_T gps_ctx;
};



struct gps_priv {
    struct list_head     vb_gps_cap_list;
#ifdef WQ_IMPL
    struct list_head     gps_work_list;
#endif
    spinlock_t           slock;
    int                  gps_poll;
    wait_queue_head_t    gps_poll_wq;
    void (*process_poll) (struct gps_priv *v);
    struct work_struct   gps_noti_work;
    struct video_device *gps_vdev;
    struct gps_cap_info  gps_info;
    unsigned int         event;
    __s32                cap_buffers;
    struct task_struct  *gps_cap_thread;
    struct format_info   gps_cap_fmt;
    struct file         *filp;
    unsigned int         thread_stop;
    unsigned int         t_sec_prv;
    unsigned int         t_msec_prv;
    unsigned int         t_frm_sec_prv;
    unsigned int         t_frm_msec_prv;
    unsigned int         max_int_cnt;
    unsigned int         frm_int_cnt;
    unsigned int         drop;           /* drop due to buffer unavailability [QBUF] */
    unsigned int         int_drop;       /* drop due to interrupt miss */
    unsigned int         avg_frame_lat;  /* avg frame latency */
    unsigned int         min_frame_lat;  /* minimum frame latency */
    unsigned int         max_frame_lat;  /* max frame latency */
    unsigned int         avg_wq_lat;     /* avg frame latency */
    unsigned int         min_wq_lat;     /* min frame latency */
    unsigned int         max_wq_lat;     /* max frame latency */
    unsigned int         last_frm_index; /* retain the last available frame index */
    unsigned int         cur_width;      /* vdec dpb size */
    unsigned int         cur_height;
    unsigned int         adaptive_mode;   /* to support adaptive stream (SCDCR-2989) */
    unsigned int         change_ctx_size; /* size update flag */
    char *				 mem_pool[MAX_GPS_BUF][MAX_VT_PLANE];
    u8                   alpha;
    u8                   svp;
    bool                 ctrls_rdy;        /* true if the control handler is initialized */
    struct v4l2_ctrl_handler ctrl_handler;
    struct v4l2_ctrl    *ctrl_alpha;
	
#ifdef V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE
	enum v4l2_ext_gpscaler_source_attribute_type attr;
#endif
};



int vb2_verify_memory_type(struct vb2_queue *q,
                   enum vb2_memory memory, unsigned int type);

struct vb2_queue *lookup_vb2_queue(struct video_device *vdev,
                   struct file *filp);

#ifdef WQ_IMPL
void V4l2_gps_thread(struct work_struct *gps_work);
#else
void V4l2_gps_thread(void *data);
#endif



int v4l2_gps_ctrls_create(struct gps_priv *ctx);
void v4l2_gps_ctrls_delete(struct gps_priv *ctx);

int v4l2_gps_register(void *arg);

#endif
