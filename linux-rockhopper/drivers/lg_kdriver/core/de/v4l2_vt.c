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
 *  @date		2018-09-21
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
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/pm_runtime.h>
#include <linux/vmalloc.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include <media/videobuf2-vmalloc.h>

// #ifndef v4l2_ext_video_rect
// struct v4l2_ext_video_rect {
//   unsigned short x;
//   unsigned short y;
//   unsigned short w;
//   unsigned short h;
// };
// #endif

#include "linux/v4l2-ext/v4l2-ext-vsc.h"
#include "linux/v4l2-ext/v4l2-ext-screencapture.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "base_device.h"
#include "v4l2_lg_dev_configs.h"
#include "v4l2_vt.h"
#include "v4l2_vsc_event.h"
#include "vb2_gen_memop.h"
#include "de_def.h"
#include "de_kapi.h"
#include "de_io.h"
#include "de_sync.h"
#include "hal/ipc_phys_hal.h"

//#undef INCLUDE_KDRV_OVI  // if you want half-rate capture with 120Hz pannel, change undef->define
#ifdef INCLUDE_KDRV_OVI
#include "ovi_hal.h"
#endif

#ifndef V4L2_CID_EXT_HISTOGRAM_START
struct v4l2_ext_histogram_data {
	unsigned int areaId; // id of the area this histogram was computed.
	unsigned short r[256];
	unsigned short g[256];
	unsigned short b[256];
};
#define V4L2_CID_EXT_HISTOGRAM_START         (V4L2_CID_USER_EXT_CAPTURE_BASE + 20)
#define V4L2_CID_EXT_HISTOGRAM_PRESET        (V4L2_CID_USER_EXT_CAPTURE_BASE + 21)
#define V4L2_CID_EXT_HISTOGRAM_DATA          (V4L2_CID_USER_EXT_CAPTURE_BASE + 22)
#define V4L2_CID_EXT_HISTOGRAM_STOP          (V4L2_CID_USER_EXT_CAPTURE_BASE + 23)

#define HISTORAM_START_EVENT  (V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT + 1)
#define HISTORAM_STOP_EVENT   (V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT + 2)
#define HISTORAM_PRESET_EVENT (V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT + 3)

#endif



/* SCDCR-4006 */
#define VT_PM_INFO(_level,_type,_result,_num)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::vt%d\n",\
			_level,"video",V4L2_EXT_DEV_NO_CAPTURE,g_vt_device_opened,\
			current->group_leader->comm,current->comm,_type,_result,_num);\
	} while(0)

// for test using hal
#define V4L2_CID_EXT_CAPTURE_BUFFER_PROPERTY_TEST (V4L2_CID_USER_EXT_CAPTURE_BASE + 10)
struct capture_buffer_property {
	unsigned int	stride;
	unsigned int	width;
	unsigned int	height;
	unsigned int	phys_y[5];
	unsigned int	phys_c[5];
};


extern const struct vb2_mem_ops vb2_vt_memops;

// =====================================================================
typedef struct
{
	// Write Only
	LX_DE_WIN_ID_T              win_id;     ///< De window index  [rw]
	UINT32                      address;    ///< physical header address [rw]
	BOOLEAN                     enable;     ///< enable control [rw]
	UINT32						numBuffer;
	UINT32                      rate;       ///< frame rate [rw]
	UINT32						frz;        ///< flag of freeze(1) / release(0) [rw]
	UINT32						frc_mode;	///< 0 : auto, 1 : forced off
	LX_DE_LOCATION_T			location;   ///< capture location source(0)/display(0) [ro]
	LX_DE_RECT_T				crop_size;	///< source crop size information [wo]
	LX_DE_RECT_T				w_out_size; ///< window size information [wo]

	// Read Only
	LX_DE_RECT_T                srcSize;    ///< source size information [rw]
	LX_DE_RECT_T                winSize;    ///< active window size information [rw]
	LX_DE_RECT_T                outSize;    ///< out window size information [rw]
	LX_DE_RECT_T                panelSize;    ///< panel size information [rw]
	UINT32                      mirror;     ///< mirror info.
	UINT32                      scan;       ///< scan info.	[ro]
	UINT32				        isSecure;   ///< secure(1) / non-secure(0)
	UINT32                      mute;       ///< mute status [ro]

	// Read Only
	UINT32                      stride;     ///< stride size [ro]
	LX_DE_SCALER_CSAMPLE_T      sampling;   ///< data format [ro]
	UINT32                      y_frame[MAX_VTG_BUFFER]; ///< y frame data start address [ro]
	UINT32                      c_frame[MAX_VTG_BUFFER]; ///< cbcr frame data start address [ro]
	UINT32                      r_idx;      ///< read frame index [ro]

	//UINT32				        reserved;
	UINT32				        svp_hist;
} VTG_INFO_T;

typedef struct
{
	LX_DE_WIN_ID_T              win_id;     ///< De window index  [rw]
	UINT32                      address;    ///< physical header address [rw]
	BOOLEAN                     enable;     ///< enable control [rw]
} VTG_CMD_T;

typedef struct
{
	VTG_INFO_T	arm_to_mcu;
	VTG_INFO_T	mcu_to_arm;
} VTGSHARED_MEM_T;
// =====================================================================
typedef struct
{
		UINT32		address;
		BOOLEAN 	enable;
		UINT32		mute;
		UINT32		r_idx;
		UINT32		rate;
		LX_DE_FRAMEINFO_T	in_info[5];
		LX_DE_FRAMEINFO_T	out_info[3];
		LX_DE_FRAMEBUFFER_T in_buf[5];
		LX_DE_FRAMEBUFFER_T out_buf[3];
		UINT32		pqe_meta_idx; //
		UINT32		frz;
		UINT32		frz_idx;
		UINT32		reserved;
} VTV_INFO_T;
// =====================================================================

struct vt_dev {
	struct platform_device *pdev;
	struct v4l2_device 	v4l2_vt_dev;
	struct v4l2_device 	v4l2_vivt_dev;
	struct video_device	v4l2_vt_video_dev;
	struct video_device	v4l2_vivt_video_dev;

	struct mutex        v4l2_vt_video_device_lock;
	struct list_head	vb_vt_cap_list;
	struct vb2_queue    vb_vt_cap_q;
	spinlock_t			slock;
	struct task_struct *vt_cap_thread;
	BOOLEAN             _IsCapThreadRunning;
	unsigned int model;//0:uhd,1:fhd
};

struct file_vb2_q {
    struct file      *file;
    struct vb2_queue queue;
    struct mutex     gps_vb2_queue_lock;
};

struct vt_cap_buffer {
	/* common v4l buffer stuff -- must be first */
	struct vb2_v4l2_buffer vb;
	struct list_head list;
};

struct vt_fh {
	struct v4l2_fh fh;
// need to add some private data
	struct vt_priv *vt_priv;
	struct vt_priv *vt_priv_own;
};

struct vtg_cap_info {
	void *a2m;
	void *m2a;
	UINT32 r_idx;
	unsigned int shared_mem;
	struct v4l2_ext_capture_video_win_info win_info;
	struct v4l2_ext_capture_plane_info plane_info;
	struct v4l2_ext_capture_plane_prop plane_prop;
	struct v4l2_ext_capture_freeze_mode freeze;
	struct v4l2_ext_video_rect w_out;
	unsigned int y_frame[MAX_VTG_BUFFER];
	unsigned int c_frame[MAX_VTG_BUFFER];
	unsigned int rate;
	unsigned int svp;
	unsigned int ext8k_dec; // external decoder
	unsigned int ext8k_frc; //external frc
	unsigned int use_ext_buf;
	unsigned int max_w;
	unsigned int max_h;
	unsigned int src_hdr_type;
#ifdef INCLUDE_KDRV_OVI
	unsigned int need_half_rate;
#endif
	unsigned int model;//0:uhd,1:fhd
};

struct vtv_cap_info {
	void *a2m;
	void *m2a;
	unsigned int shared_mem;
	unsigned int input_width;
	unsigned int input_height;
	unsigned int output_width;
	unsigned int output_height;
	unsigned int input_buf_count;

	UINT32		mute;
	UINT32		r_idx;
	UINT16		frz;
	UINT16		frz_idx;
	LX_DE_FRAMEINFO_T   in_info;
	LX_DE_FRAMEINFO_T   out_info;
	LX_DE_FRAMEBUFFER_T in_buf[5];
	LX_DE_FRAMEBUFFER_T out_buf[3];
};

struct vt_priv
{
	struct list_head list;

	/* vt  */
	int vt_poll;
	wait_queue_head_t vt_poll_wq;
	void (*process_poll)(struct vt_priv *v);
	struct work_struct vt_noti_work;
	struct video_device *vt_vdev;
	unsigned int event;
	/*Base address of VTM capture buffer */
	unsigned int phyAddress;
	int vt_target; // 0:none , 1:vtg, 2:vtv
	struct vtg_cap_info vtg_info;
	struct vtv_cap_info vtv_info;
};

static int __kthread_exit = FALSE;
static int test_cmd = 0;
static int g_vt_device_opened = 0;
static int g_vivt_device_opened = 0;
int g_frz_wait = 1, g_idx_offset = 0;
int g_prev_loc = 1;
int g_log_level = 3;
struct mutex     vt_mutex_lock;
struct mutex     vivt_mutex_lock;
unsigned int g_vt_hist_cmd = 2, g_vt_hist_count = 0;;
unsigned int g_vt_hist_preset  = 2, g_vt_prev_preset=7;
struct v4l2_ext_histogram_data hist_data[16];

int v4l2_vt_mmap(struct vb2_queue *q, struct vm_area_struct *vma);
int proc_capture(int cmd, int w, int h, unsigned int *v, unsigned int *p);
int v4l2_vt_pm_runtime_test(char* command);

struct vt_priv *new_vt_priv(void);
static void vt_capture_notification(UINT32 event_type, struct vt_dev *dev, int index);

static int vt_capture_thread(void* data);
static int vt_get_capability_info(unsigned int win_id, \
	struct v4l2_ext_capture_capability_info *param);
static int vt_get_plane_info(unsigned int win_id, \
	struct v4l2_ext_capture_plane_info *param);
static int vt_get_win_info(unsigned int win_id, \
	struct v4l2_ext_capture_video_win_info *param);
static int vt_get_plane_prop(unsigned int win_id, \
	struct v4l2_ext_capture_plane_prop *param);
static int vt_get_freeze_mode(unsigned int win_id, \
	struct v4l2_ext_capture_freeze_mode *param);
static int vt_set_plane_property(unsigned int win_id, \
	struct v4l2_ext_capture_plane_prop *param);
static int vt_set_freeze(unsigned int win_id, \
	struct v4l2_ext_capture_freeze_mode *param);
static int vt_get_buffer_phys_info(unsigned int win_id, \
	struct capture_buffer_property *param);
static int vt_get_buffer_address(int in_out, int idx,\
	unsigned int *y, unsigned int *c);
static int vt_set_divide_rate(BOOLEAN flag, unsigned int win_id, \
	unsigned int *param);
static int vt_get_output_rate(BOOLEAN flag, unsigned int win_id, \
	unsigned int *param);
static int vt_set_out_buffer_index(BOOLEAN flag, unsigned int *param);
static int vt_set_win_info(unsigned int win_id, \
	struct v4l2_ext_capture_video_win_info *param);
static int vt_set_hist_preset(unsigned int preset);

static int vt_get_ridx(unsigned int *p);
static int _get_vtg_info(void);
static int _set_vtg_info(void);
static int _set_vtg_run(unsigned int c, unsigned int shared_mem_addr);
static int _get_vtv_info(void);
static int _set_vtv_info(void);
static int _set_vtv_run(unsigned int c, unsigned int shared_mem_addr);

static int vivt_set_plane_property(unsigned int win_id, struct v4l2_ext_capture_plane_prop *param);
static int vivt_get_buffer_address(int in_out, int idx, unsigned int *y, unsigned int *c);
static int _set_vivt_vtg_run(unsigned int c, unsigned int shared_mem_addr);

struct vt_priv *fh_vt_priv;
struct vt_priv *fh_vivt_priv;


static inline struct vt_cap_buffer *to_vt_cap_buffer(struct vb2_buffer *vb2)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	return container_of(vbuf, struct vt_cap_buffer, vb);
}

static char *ctrl_id_ext_to_str(int id)
{
    switch (id)
	{
		case V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO :
			return "V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO";
		case V4L2_CID_EXT_CAPTURE_PLANE_INFO:
			return "V4L2_CID_EXT_CAPTURE_PLANE_INFO";
		case V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO:
			return "V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO";
		case V4L2_CID_EXT_CAPTURE_PLANE_PROP :
			return "V4L2_CID_EXT_CAPTURE_PLANE_PROP";
		case V4L2_CID_EXT_CAPTURE_FREEZE_MODE :
			return "V4L2_CID_EXT_CAPTURE_FREEZE_MODE";
		case V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING:
			return "V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING";
		case V4L2_CID_EXT_CAPTURE_SUBSCRIBE_FRAME_READY:
			return "V4L2_CID_EXT_CAPTURE_SUBSCRIBE_FRAME_READY";
		case V4L2_CID_EXT_CAPTURE_BUFFER_PROPERTY_TEST:
			return "V4L2_CID_EXT_CAPTURE_BUFFER_PROPERTY_TEST(HAL TEST)";
		case V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO:
			return "V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO";
		case V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE:
			return "V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE";
		case V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE:
			return "V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE";
#ifdef V4L2_CID_EXT_HISTOGRAM_START
		case V4L2_CID_EXT_HISTOGRAM_START:
			return "V4L2_CID_EXT_HISTOGRAM_START";
		case V4L2_CID_EXT_HISTOGRAM_STOP:
			return "V4L2_CID_EXT_HISTOGRAM_STOP";
		case V4L2_CID_EXT_HISTOGRAM_PRESET:
			return "V4L2_CID_EXT_HISTOGRAM_PRESET";
		case V4L2_CID_EXT_HISTOGRAM_DATA:
			return "V4L2_CID_EXT_HISTOGRAM_DATA";
#endif
		default:
			return "Ext. CID Unkown";
	}
}

static inline bool is_queue_busy(struct video_device *vdev, struct file *file)
{
    return vdev->queue->owner && vdev->queue->owner != file->private_data;
}

static int v4l2_vt_vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
	struct video_device *vdev = video_devdata(file);
	struct vt_priv *prv_data = NULL;
	int bufCnt = 0, planeCnt=0;
	struct vb2_gen_buf *buf;
	struct vb2_plane *plane = NULL;
	VTG_INFO_T *p_m2a = NULL;
	VTG_INFO_T *p_a2m = NULL;
	void *vAddr = NULL;
	unsigned int y_frame=0, c_frame=0, buf_addr=0;
	int res;

	prv_data = ((struct vt_fh *)(file->private_data))->vt_priv;
	if(prv_data == NULL){
	   DE_NOTI("[%s]Failed to get private data\n",__func__);
	   return -1;
   }

	if(fh_vt_priv->vt_target > V4L2_EXT_CAPTURE_DISPLAY_OUTPUT)
		return -ENOTSUPP;

	p_m2a = (VTG_INFO_T *)prv_data->vtg_info.m2a;
	p_a2m = (VTG_INFO_T *)prv_data->vtg_info.a2m;

	if(!p_m2a || !p_a2m)
	{
		DE_ERROR("Failed physical address from firmware\n");
		goto ALLOC_FAIL;
	}

	if (is_queue_busy(vdev, file)){
		DE_NOTI("-EBUSY");
		return -EBUSY;
	}

	/* call default function of vb2 ioctl */
	res = vb2_ioctl_reqbufs(file,priv,p);

	if (res)
	{
		DE_NOTI("res[%d] p->count[%d]", res, p->count);
		return res;
	}
	if(p->count == 0){
		return 0;
	}

	prv_data->phyAddress = p_a2m->address;

	/*Harish: Assign real memory here now [As of now hardcode to Win0] */
	if(p->memory == VB2_MEMORY_MMAP){
		if(prv_data && (prv_data->phyAddress != 0)){
			/*Map the address to access the real address */
			vAddr = vmap_phys(prv_data->phyAddress, sizeof(LX_DE_VTM_FRAME_INFO_T));
			if(vAddr == NULL){
				DE_ERROR("Failed Virtual Address mapping\n");
				goto ALLOC_FAIL;
			}
			else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
#else
				DE_NOTI("PHY [0x%x] VIRT [%p] Total Buffers [%d/%d] stride[%d]\n",\
				prv_data->phyAddress,vAddr,\
				prv_data->vtg_info.plane_prop.buf_count,vdev->queue->num_buffers,\
				p_m2a->stride);
#endif

			/*Harish: TODO: Dynamic handling of different semiplaner/planer format */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
			while(bufCnt < vb2_get_num_buffers(vdev->queue)){
#else
			while(bufCnt < vdev->queue->num_buffers){
#endif
				planeCnt = 0;

				if(fh_vt_priv->vt_target<2) {
					y_frame = prv_data->vtg_info.y_frame[bufCnt];
					c_frame = prv_data->vtg_info.c_frame[bufCnt];
					if(y_frame == 0xffffffff || c_frame == 0xffffffff)
					{
						y_frame = prv_data->phyAddress; // not used buffer
						c_frame = prv_data->phyAddress;
					}
				}
				else {
					y_frame = prv_data->vtv_info.in_buf[bufCnt].y_frame;
					c_frame = prv_data->vtv_info.in_buf[bufCnt].c_frame;
				}

				while(planeCnt < vdev->queue->bufs[bufCnt]->num_planes){
					plane = (struct vb2_plane *)&(vdev->queue->bufs[bufCnt]->planes[planeCnt]);
					buf = (struct vb2_gen_buf *)plane->mem_priv;
					buf->vaddr = NULL;

					if(!plane->length) {
						if(vAddr) vunmap(vAddr);
						DE_ERROR("plane->length(stride from fw) = 0");
						return -EFAULT;
					}

					if(planeCnt == 0){
						buf->vaddr = vmap_phys(y_frame,plane->length);
						buf_addr = y_frame;
						if(g_log_level < 1) DE_NOTI("Mapping Buf [%d] plane [%d] PHY Address [0x%x] VIRT Address [%p]\n",bufCnt,planeCnt,y_frame,buf->vaddr);
					}
					else {
						buf->vaddr = vmap_phys(c_frame,plane->length);
						buf_addr = c_frame;
						if(g_log_level < 1) DE_NOTI("Mapping Buf [%d] plane [%d] PHY Address [0x%x] VIRT Address [%p]\n",bufCnt,planeCnt,c_frame,buf->vaddr);
					}

					if(buf->vaddr == NULL)
						goto ALLOC_FAIL;
					else
						plane->m.offset = buf_addr;
					planeCnt++;
				}
				bufCnt++;
			}

			vunmap(vAddr);
		}
		else {
			res = -ENOMEM;
			goto ALLOC_FAIL;
		}
	}
	return res;

ALLOC_FAIL:
	bufCnt = 0 ;
	planeCnt = 0;

	if(vAddr) vunmap(vAddr);

	while(bufCnt < p->count){
		while(planeCnt < vdev->queue->bufs[bufCnt]->num_planes){
			buf = (struct vb2_gen_buf *)vdev->queue->bufs[bufCnt]->planes[planeCnt].mem_priv;
			if(buf->vaddr) {
				vunmap(buf->vaddr);
				buf->vaddr = NULL;
			}
			kfree(buf);
			planeCnt++;
		}
		bufCnt++;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
#else
	vdev->queue->num_buffers = 0;
#endif
	p->count = 0;
	return -ENOMEM;
}

static int vt_notification(struct vt_priv *p)
{
	struct v4l2_event evt;
	int info = 0x11223344;

	memset(&evt, 0, sizeof(evt));
	evt.type = V4L2_EVENT_CTRL;
	evt.id	 = p->event;
	memcpy(evt.u.data, &info, sizeof(info));
	v4l2_event_queue(p->vt_vdev, &evt);

	DE_NOTI("Post  %x - evt.type[0x%x] evt.id[0x%x]", \
		info, evt.type, evt.id);

	return 0;
}

static void vt_noti_ws(struct work_struct *work)
{
	struct vt_priv *p;
	p = container_of(work, struct vt_priv, vt_noti_work);
	vt_notification(p);
}

static void process_poll(struct vt_priv *p)
{
	queue_work(system_wq, &p->vt_noti_work);
}

struct vt_priv *new_vt_priv(void)
{
	struct vt_priv *p;

	p = kcalloc(1, sizeof(struct vt_priv), GFP_KERNEL);
	if(!p)
	{
		DE_ERROR("alloc error for vt priv.");
		return NULL;
	}
	INIT_LIST_HEAD(&p->list);
	init_waitqueue_head(&p->vt_poll_wq);

	return p;
}

static int init_vivt_dev(struct vt_priv *p)
{
	int ret = 0;
	unsigned int shared_mem_addr;

	// get shared memory from DE_IO
	// and vmap_phys
	shared_mem_addr = 1; // get shared mem address of vtg
	ret = DE_IO_GetSharedMem((unsigned long)&shared_mem_addr);
	if(g_log_level < 1) DE_NOTI("vtg shared_mem_addr : 0x%08x", shared_mem_addr);
	p->vtg_info.a2m = (void*)vmap_phys(shared_mem_addr, sizeof(VTG_INFO_T)*2);
	p->vtg_info.m2a = p->vtg_info.a2m + sizeof(VTG_INFO_T);
	p->vtg_info.shared_mem = shared_mem_addr;
	memset(p->vtg_info.a2m, 0, sizeof(VTG_INFO_T));
	memset(p->vtg_info.m2a, 0, sizeof(VTG_INFO_T));

	ret = _set_vivt_vtg_run(1, shared_mem_addr); // enable vtg capture

	return ret;
}

static int init_vt_dev(struct vt_priv *p)
{
	int ret = 0;
	unsigned int shared_mem_addr;

	// get shared memory from DE_IO
	// and vmap_phys
	shared_mem_addr = 1; // get shared mem address of vtg
	ret = DE_IO_GetSharedMem((unsigned long)&shared_mem_addr);
	if(g_log_level < 1) DE_NOTI("vtg shared_mem_addr : 0x%08x", shared_mem_addr);
	p->vtg_info.a2m = (void*)vmap_phys(shared_mem_addr, sizeof(VTG_INFO_T)*2);
	p->vtg_info.m2a = p->vtg_info.a2m + sizeof(VTG_INFO_T);
	p->vtg_info.shared_mem = shared_mem_addr;
	memset(p->vtg_info.a2m, 0, sizeof(VTG_INFO_T));
	memset(p->vtg_info.m2a, 0, sizeof(VTG_INFO_T));

	_set_vtg_run(1, shared_mem_addr); // enable vtg capture

	shared_mem_addr = 3; // get shared mem address of vtv
	ret = DE_IO_GetSharedMem((unsigned long)&shared_mem_addr);
	if(g_log_level < 1) DE_NOTI("vtv shared_mem_addr : 0x%08x", shared_mem_addr);
	p->vtv_info.a2m = (void*)vmap_phys(shared_mem_addr, sizeof(VTV_INFO_T)*2);
	p->vtv_info.m2a = p->vtv_info.a2m + sizeof(VTV_INFO_T);
	p->vtv_info.shared_mem = shared_mem_addr;
	memset(p->vtv_info.a2m, 0, sizeof(VTV_INFO_T));
	memset(p->vtv_info.m2a, 0, sizeof(VTV_INFO_T));

	return 0;
}

static int uninit_vt_dev(struct vt_priv *p)
{
	int ret = 0;

	// vunmap_phys
	if(p->vtg_info.a2m){
		vunmap_phys(p->vtg_info.a2m);
		p->vtg_info.a2m = NULL;
	}
	if(p->vtv_info.a2m){
		vunmap_phys(p->vtv_info.a2m);
		p->vtv_info.a2m = NULL;
	}

	return ret;
}

static int v4l2_vivt_fh_open(struct file *filp)
{
	int ret = 0;
	struct video_device *vdev = video_devdata(filp);
	//struct vt_dev *dev  = video_drvdata(filp);
	struct vt_fh *fh = filp->private_data;
	struct vt_priv *p;
	DE_NOTI("name[%s] open", vdev->name);

	if(kthread_exit == TRUE) {DE_ERROR("vt thread is running..."); return -1;}
	if(g_vivt_device_opened >0){DE_ERROR("vt device is openned..."); return -1;}

	fh = kzalloc(sizeof(struct vt_fh), GFP_KERNEL);
	if (!fh) {
		DE_ERROR("vt: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	p = new_vt_priv();

	fh->vt_priv = p;
	fh->vt_priv_own = p;

	filp->private_data = fh;
	v4l2_fh_init(&fh->fh,vdev);
	v4l2_fh_add(&fh->fh);

	fh_vivt_priv = fh->vt_priv; // to acess shared memory

	ret = init_vivt_dev(p); // handler init
	g_vivt_device_opened++;

	DE_NOTI("name[%s] open count[%d]", vdev->name, g_vivt_device_opened);
	return ret;
}

static int v4l2_vivt_fh_release(struct file *file)
{
	int ret = 0;
	struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev	= video_drvdata(file);
	struct vt_fh *fh = file->private_data;
	struct vt_priv *pvt;

	_set_vivt_vtg_run(0, 0); //disable capture

	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);

	pvt = ((struct vt_fh *)(file->private_data))->vt_priv_own;
	if(pvt) {
		kfree(pvt);
		kfree(fh);
	}
	file->private_data = NULL;
	fh_vivt_priv = NULL;
	g_vivt_device_opened--;

	DE_NOTI("name[%s] close count[%d]", vdev->name, g_vivt_device_opened);
	return ret;
}

static int v4l2_vt_fh_open(struct file *filp)
{
	int ret = 0;
	struct video_device *vdev = video_devdata(filp);
	struct vt_priv *p;
	struct vt_fh *fh;
	struct vt_dev *dev  = video_drvdata(filp);
#ifdef INCLUDE_KDRV_OVI
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
#endif
	kwrap_vp_timing_info_t ti;

	//DE_NOTI("vt: open...\n");
	mutex_lock(&vt_mutex_lock);

	ret = pm_runtime_get_sync(&dev->pdev->dev);
	DE_NOTI("%s : ret:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret,atomic_read(&dev->pdev->dev.power.usage_count));

	if(g_vt_device_opened) { // request from HE lab. : QEVENTTWEN-21098
		DE_ERROR("open_count[%d] return -EBUSY name[%s]", g_vt_device_opened, vdev->name);
		mutex_unlock(&vt_mutex_lock);
		return -EBUSY;
	}

	fh = kzalloc(sizeof(struct vt_fh), GFP_KERNEL);
	if (!fh) {
		DE_ERROR("vt: allocation of file handle failed \n");
		ret = -ENOMEM;
		mutex_unlock(&vt_mutex_lock);
		return ret;
	}

	p = new_vt_priv();
	if(!p) {
		DE_ERROR("alloc of vt priv failed");
		ret = -ENOMEM;
		goto fail_fh;
	}

	INIT_WORK(&p->vt_noti_work, vt_noti_ws);
	p->process_poll = process_poll;
	p->vt_vdev = vdev;
	p->vtg_info.model = dev->model;
	fh->vt_priv = p;
	fh->vt_priv_own = p;

	filp->private_data = fh;
	v4l2_fh_init(&fh->fh,vdev);
	v4l2_fh_add(&fh->fh);

	/* vt initialize */
	if(!g_vt_device_opened) {
		fh_vt_priv = fh->vt_priv;
		vsc_get_timinginfo(0,&ti);
		if(test_cmd == 1) {
			ti.svp = 1;
			if(g_log_level < 1)DE_NOTI("set_by_proc:svp=1");
		}

		p->vtg_info.svp = ti.svp;


		if(ti.svp) {
			vsc_set_fbpos(FB_OSD_ONLY);
			#if 0 // 20210806 TVPLAT-146074(to support secure venc)
			ret = -EACCES;
			DE_NOTI("svp!!!");
			goto fail_fh;
			#endif
		}
		//else {
			ret = init_vt_dev(p); // handler init
		//}
	}
	else {
		fh->vt_priv = fh_vt_priv;
	}

	p->vt_target = 0; // init
	//p->vtg_info.svp = 0;
	p->vtg_info.ext8k_dec = 0;
	p->vtg_info.ext8k_frc = 0;
	p->vtg_info.use_ext_buf = 0;
#ifdef INCLUDE_KDRV_OVI
	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);
	if ((ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
		|| (ovi_opt.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ_FIXED))
		p->vtg_info.need_half_rate = 0;
	else
		p->vtg_info.need_half_rate = 1;

	if(ovi_opt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22) // O22+Fxx ext frc model
		p->vtg_info.ext8k_frc = 1;
#endif

	/* increment open counter */
	g_vt_device_opened++;
	VT_PM_INFO("info","open","ok", vdev->num);

/*	DE_NOTI("name[%s], index = %d, minor = %d, svp[%d], open_count[%d], ext8k_frc[%d]",\
		vdev->name, fh->fh.vdev->index, fh->fh.vdev->minor, \
		p->vtg_info.svp, g_vt_device_opened,p->vtg_info.ext8k_frc);*/

	mutex_unlock(&vt_mutex_lock);

	DE_NOTI("name[%s] open", vdev->name);

	return ret;

fail_fh:
	if(fh) {
		v4l2_fh_del(&fh->fh);
		v4l2_fh_exit(&fh->fh);
		kfree(p);
		kfree(fh);
	}
	mutex_unlock(&vt_mutex_lock);
	return ret;
}

static int v4l2_vt_fh_release(struct file *file)
{
	int ret = 0;
	struct vt_dev *dev  = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);
	struct vt_fh *fh = file->private_data;
	struct vt_priv *pvt = ((struct vt_fh *)(file->private_data))->vt_priv;
	struct mutex *lock;//

	if(vdev->queue)
		lock = vdev->queue->lock ? vdev->queue->lock : vdev->lock;

	if(g_vt_device_opened < 2) {
		//unsigned int cmd = 0;
		if(!pvt->vtg_info.svp)_set_vtg_run(0, 0); //disable capture
		//DE_IO_SetSharedMem(cmd);
		if(pvt->vt_target==2)
			_set_vtv_run(2, 0);//disable vtv
		pvt->vt_target = 0;

		ret = uninit_vt_dev(pvt);
		if(ret) DE_NOTI("uninit_vt_dev fail");
	}

	if(pvt->vtg_info.use_ext_buf == 1 && pvt->vtg_info.ext8k_frc == 1) {
		unsigned int c = 5; // free
		ret = DE_IO_SetSharedMem((unsigned long)&c);
		if(ret) DE_NOTI("use_ext_buf release fail");
		pvt->vtg_info.use_ext_buf = 0;
		pvt->vtg_info.ext8k_frc   = 0;
	}

	if (vdev->queue){
		if (lock)
			mutex_lock(lock);
		if (file->private_data == vdev->queue->owner) {
			vb2_queue_release(vdev->queue);
			vdev->queue->owner = NULL;
		}

		if (lock)
			mutex_unlock(lock);
	}

	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);

	pvt = ((struct vt_fh *)(file->private_data))->vt_priv_own;
	if(pvt){
		kfree(pvt);
		fh->vt_priv_own = NULL;

		kfree(fh);
		file->private_data = NULL;
	}

	ret = pm_runtime_put(&dev->pdev->dev);
	DE_NOTI("vt: close, usage_count[%d][%d]\n", atomic_read(&dev->pdev->dev.power.usage_count), g_vt_device_opened);

	/* decrement open counter */
	g_vt_device_opened--;
	if(g_vt_device_opened < 0) g_vt_device_opened = 0;

	VT_PM_INFO("info","close","ok",vdev->num);
	mutex_unlock(&vt_mutex_lock);

//	g_vt_hist_cmd = 2;
	fh_vt_priv = NULL;

	DE_NOTI("name[%s] close hist_cmd[%d](1:start,2:stop) ", vdev->name, g_vt_hist_cmd);

	return ret;
}

static int v4l2_vt_probe(struct platform_device *pdev)
{
	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);
	DE_NOTI("vt  %s\n", __func__);
	return 0;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vt_remove(struct platform_device *pdev)
#else
static int v4l2_vt_remove(struct platform_device *pdev)
#endif
{
	pm_runtime_disable(&pdev->dev);
	DE_NOTI("vt  %s\n", __func__);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_vt_resume(struct device *dev)
{
	DE_NOTI("%s\n", __func__);
	return 0;
}

static int v4l2_vt_suspend(struct device *dev)
{
	DE_NOTI("%s\n", __func__);
	return 0;
}

static int v4l2_vt_runtime_resume(struct device *dev)
{
	VT_PM_INFO("info", "resume","ok", V4L2_EXT_DEV_NO_VT);

	return 0;
}

static int v4l2_vt_runtime_suspend(struct device *dev)
{
	VT_PM_INFO("info", "suspend","ok", V4L2_EXT_DEV_NO_VT);

	return 0;
}

static unsigned int v4l2_vt_poll(struct file *file, poll_table *wait)
{
	struct video_device *vdev = video_devdata(file);
	struct vb2_queue   *q  = vdev->queue;
	struct mutex *lock = q->lock ? q->lock : vdev->lock;
	unsigned res;
    void *fileio;

  /*
    * If this helper doesn't know how to lock, then you shouldn't be using
    * it but you should write your own.
    */
    WARN_ON(!lock);

    if (lock && mutex_lock_interruptible(lock))
        return POLLERR;

    fileio = q->fileio;

    res = vb2_poll(q , file, wait);

    /* If fileio was started, then we have a new queue owner. */
    if (!fileio && q->fileio)
        q->owner = file->private_data;
    if (lock)
        mutex_unlock(lock);
    return res;
}

static int vivt_set_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
		case V4L2_CID_EXT_CAPTURE_PLANE_PROP:
			{
				struct v4l2_ext_capture_plane_prop param;
				if(copy_from_user(&param,\
					(void __user *)ctrl->string,\
					sizeof(struct v4l2_ext_capture_plane_prop)))
				{
					DE_ERROR("copy from user error ");
				}
				ret = vivt_set_plane_property(0, &param);
				if(ret)
				{
					DE_ERROR("vt_set_plane_property error ");
				}
			}
			break;
		case V4L2_CID_EXT_HISTOGRAM_DATA:
			{
				unsigned int block_size = 16;
		#if 0
				if(g_vt_hist_preset == 3)
					block_size = 14;
				else
					block_size = 16;
		#endif
				ret = copy_from_user(hist_data,\
					(void __user *)ctrl->string,\
					block_size * sizeof(struct v4l2_ext_histogram_data));
		
				if(!ret) {
					//DE_NOTI("Save HISTOGRAM_DATA (from libpqeca) preset(%d)@@@@", hist_data[15].areaId);
				}
				else
					DE_NOTI("copy_from_user error ret[%d]", ret);
				hist_data[15].areaId = 15;
				DE_NOTI("2set %d: %d %d %d", hist_data[0].areaId, hist_data[0].r[0], hist_data[0].g[0], hist_data[0].b[0]);
				g_vt_prev_preset = g_vt_hist_preset;
				g_vt_hist_count = 3;
			}break;

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

static int vt_set_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_CAPTURE_PLANE_PROP:
		{
			struct v4l2_ext_capture_plane_prop param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_capture_plane_prop)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vt_set_plane_property(0, &param);
			if(ret)
			{
				DE_ERROR("vt_set_plane_property error ");
			}
		}
		break;
	case V4L2_CID_EXT_CAPTURE_FREEZE_MODE :
		{
			struct v4l2_ext_capture_freeze_mode param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_capture_freeze_mode)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vt_set_freeze(0, &param);
		}
		break;
	case V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO:
		{
			struct v4l2_ext_capture_video_win_info param;
			if(copy_from_user(&param,\
				(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_capture_video_win_info)))
			{
				DE_ERROR("copy from user error ");
			}
			ret = vt_set_win_info(0, &param);
		}
		break;
	case V4L2_CID_EXT_HISTOGRAM_START:
		{
			//struct vt_dev *dev	= video_drvdata(file);
			//vt_capture_notification(HISTORAM_START_EVENT, dev, 0);

			g_vt_hist_cmd = 1;
			g_vt_hist_count  = 1;
			g_vt_hist_preset = 0;
			OS_UsecDelay(9000);
			DE_NOTI("HISTORAM_START_EVENT @@@@");
		}break;
	case V4L2_CID_EXT_HISTOGRAM_STOP:
		{
			//struct vt_dev *dev	= video_drvdata(file);
			//vt_capture_notification(HISTORAM_STOP_EVENT, dev, 0);
			DE_NOTI("HISTORAM_STOP_EVENT @@@@");
			g_vt_hist_cmd = 2;
			g_vt_hist_count = 0;
		}break;
	case V4L2_CID_EXT_HISTOGRAM_PRESET:
		{
			unsigned int preset;
			//struct vt_dev *dev	= video_drvdata(file);

			preset = ctrl->value;

			DE_NOTI("HISTORAM_PRESET_EVENT @@@@ [%d]", preset);
			g_vt_hist_cmd = 3;
			g_vt_hist_count = 2;
			//OS_UsecDelay(9000);
			//if(g_vt_hist_preset == 3 && preset == 0)
				OS_UsecDelay(9000);
				//msleep(1);
			DE_NOTI("HISTORAM_PRESET_EVENT[%d] done", preset);
			vt_set_hist_preset(preset);

			//msleep(30);
		}break;
	case V4L2_CID_EXT_HISTOGRAM_DATA:
		{
			unsigned int block_size;

			if(g_vt_hist_preset == 3)
				block_size = 14;
			else
				block_size = 16;

			ret = copy_from_user(hist_data,\
				(void __user *)ctrl->string,\
				block_size * sizeof(struct v4l2_ext_histogram_data));

			if(!ret)
				DE_NOTI("Save HISTOGRAM_DATA (from libpqeca) preset(%d)@@@@", g_vt_hist_preset);
			else
				DE_NOTI("copy_from_user error ret[%d]", ret);

			DE_NOTI("2set %d: %d %d %d", hist_data[0].areaId, hist_data[0].r[0], hist_data[0].g[0], hist_data[0].b[0]);
			g_vt_prev_preset = g_vt_hist_preset;
			g_vt_hist_count = 3;
		}break;

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

unsigned int hist_prev_y=0xffffffff, hist_prev_c=0xffffffff;
static int vivt_get_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO :
		{
			struct v4l2_ext_capture_physical_memory_info param;
			int bufIdx, location;
			unsigned int y, c;

			ret = copy_from_user(&param,(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_capture_physical_memory_info));
			if(ret) DE_ERROR("copy from user error %d", ret);

			param.y = (unsigned int *)(uintptr_t)param.compat_y_data;
			param.c = (unsigned int *)(uintptr_t)param.compat_c_data;

			ret = copy_to_user((void __user *)ctrl->string,&param,\
				sizeof(struct v4l2_ext_capture_physical_memory_info));
			if(ret) DE_ERROR("copy_to_user error %d", ret);

			bufIdx = param.buf_index;
			location = param.buf_location;
			if(bufIdx >= MAX_VTG_BUFFER)
			{
				DE_ERROR("invalid index[%d]", bufIdx);
				return -EINVAL;
			}

			ret = vivt_get_buffer_address(location, bufIdx, &y, &c);
			if(location == V4L2_EXT_CAPTURE_OSD_OUTPUT + 1) { // in case of histogram location
				unsigned int start, end;
				ret = DE_IO_GetHistoBufferRange(&start, &end);
				if(!ret) {
					if((y < start) || (y > end)/* || (c < start) || (c > end)*/) {
						DE_NOTI("get svp buffer y(0x%08x) c(%08x)", y, c);
						DE_NOTI("get svp buffer start(0x%08x) ~ end(%08x)", start, end);

						y = (hist_prev_y==0xffffffff)?start:hist_prev_y;
						c = (hist_prev_c==0xffffffff)?start:hist_prev_c;

						hist_prev_y = start;
						hist_prev_c = start;
						DE_WARN("default return. skip this req.[%08x/%08x] range[0x%08x ~ 0x%08x]", y, c, start, end);
					}
					else
					{
						hist_prev_y = y;
						hist_prev_c = c;
					}
				}
			}
			ret  = copy_to_user((void __user *)param.y, \
				(void *)&y, sizeof(unsigned int));
			if(ret) DE_ERROR("copy to user error %d", ret);
			ret = copy_to_user((void __user *)param.c, \
				(void *)&c, sizeof(unsigned int));
			if(ret) DE_ERROR("copy to user error %d", ret);
		}
		break;
	case V4L2_CID_EXT_HISTOGRAM_PRESET:
		{
			unsigned int preset = g_vt_hist_preset;

			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&preset, sizeof(unsigned int)))
			{
				DE_ERROR("copy_to_user error");
			}
			DE_NOTI("get preset[%d] from libpqeca", preset);
		}
		break;
	default:
			return -EINVAL;
	}

	return 0;

}

static int vt_get_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO:
		{
			struct v4l2_ext_capture_capability_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_capture_capability_info));

			ret = vt_get_capability_info(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_capture_capability_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}break;
	case V4L2_CID_EXT_CAPTURE_PLANE_INFO:
		{
			struct v4l2_ext_capture_plane_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_capture_plane_info));

			ret = vt_get_plane_info(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_capture_plane_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}break;
	case V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO:
		{
			struct v4l2_ext_capture_video_win_info param;
			memset(&param, 0, sizeof(struct v4l2_ext_capture_video_win_info));

			ret = vt_get_win_info(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_capture_video_win_info)))
			{
				DE_ERROR("copy_to_user error");
			}
		}break;
	case V4L2_CID_EXT_CAPTURE_PLANE_PROP:
		{
			struct v4l2_ext_capture_plane_prop param;
			memset(&param, 0, sizeof(struct v4l2_ext_capture_plane_prop));

			ret = vt_get_plane_prop(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_capture_plane_prop)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_CAPTURE_FREEZE_MODE :
		{
			struct v4l2_ext_capture_freeze_mode param;
			memset(&param, 0, sizeof(struct v4l2_ext_capture_freeze_mode));

			ret = vt_get_freeze_mode(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct v4l2_ext_capture_freeze_mode)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_CAPTURE_BUFFER_PROPERTY_TEST :
		{
			struct capture_buffer_property param;

			ret = vt_get_buffer_phys_info(0, &param);
			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&param, sizeof(struct capture_buffer_property)))
			{
				DE_ERROR("copy_to_user error");
			}
		}
		break;
	case V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO :
		{
			struct v4l2_ext_capture_physical_memory_info param;
			int bufIdx, location;
			unsigned int y, c;

			ret = copy_from_user(&param,(void __user *)ctrl->string,\
				sizeof(struct v4l2_ext_capture_physical_memory_info));
			if(ret) DE_ERROR("copy from user error %d", ret);

			param.y = (unsigned int *)(uintptr_t)param.compat_y_data;
			param.c = (unsigned int *)(uintptr_t)param.compat_c_data;

			ret = copy_to_user((void __user *)ctrl->string,&param,\
				sizeof(struct v4l2_ext_capture_physical_memory_info));
			if(ret) DE_ERROR("copy_to_user error %d", ret);

			bufIdx = param.buf_index;
			location = param.buf_location;
			if(bufIdx >= MAX_VTG_BUFFER)
			{
				DE_ERROR("invalid index[%d]", bufIdx);
				return -EINVAL;
			}

			ret = vt_get_buffer_address(location, bufIdx, &y, &c);
			if(location == V4L2_EXT_CAPTURE_OSD_OUTPUT + 1) { // in case of histogram location
				unsigned int start, end;
				ret = DE_IO_GetHistoBufferRange(&start, &end);
				if(!ret) {
					//DE_NOTI("get svp buffer start(0x%08x) ~ end(%08x)", start, end);
					if((y < start) || (y > end) || (c < start) || (c > end)) {

						y = (hist_prev_y==0xffffffff)?start:hist_prev_y;
						c = (hist_prev_c==0xffffffff)?start:hist_prev_c;

						hist_prev_y = start;
						hist_prev_c = start;
						DE_WARN("default return. skip this capture[%08x/%08x] range[0x%08x ~ 0x%08x]", y, c, start, end);
					}
					else
					{
						hist_prev_y = y;
						hist_prev_c = c;
					}
				}
			}
			ret  = copy_to_user((void __user *)param.y, \
				(void *)&y, sizeof(unsigned int));
			if(ret) DE_ERROR("copy to user error %d", ret);
			ret = copy_to_user((void __user *)param.c, \
				(void *)&c, sizeof(unsigned int));
			if(ret) DE_ERROR("copy to user error %d", ret);
		}
		break;
		case V4L2_CID_EXT_HISTOGRAM_DATA:
		{
			unsigned int block_size;
			int timeout = 9;
			//DE_NOTI("v4l2 get CID HISTOGRAM_DATA enter");

			do {
				OS_UsecDelay(1000);
				timeout--;
				//DE_NOTI("timeout=%d", timeout);
				if(timeout==0) break;
			}while(g_vt_hist_count < 3);

			if(g_vt_hist_preset == 3)
				block_size = 14;
			else
				block_size = 16;

			ret = copy_to_user((void __user *)ctrl->string, hist_data,\
				block_size * sizeof(struct v4l2_ext_histogram_data));
			if(ret) DE_ERROR("hist_data copy_to_user error %d", ret);

			//DE_NOTI("v4l2 get CID HISTOGRAM_DATA @@@@@@@@@@@@@@@@@@ , preset[%d] timeout[%d]", g_vt_hist_preset, timeout);
			DE_NOTI("1get %d: %d %d %d", hist_data[0].areaId, hist_data[0].r[0], hist_data[0].g[0], hist_data[0].b[0]);
		}
		break;
		case V4L2_CID_EXT_HISTOGRAM_PRESET:
		{
			unsigned int preset = g_vt_hist_preset;

			if(copy_to_user((void __user *)ctrl->string, \
				(void *)&preset, sizeof(unsigned int)))
			{
				DE_ERROR("copy_to_user error");
			}
			DE_NOTI("get preset[%d] from libpqeca", preset);
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static int v4l2_vt_vidioc_expbuf(struct file *file, void *priv, struct v4l2_exportbuffer *p)
{
	struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev  = video_drvdata(file);

	DE_NOTI("%s: ",__func__);

	return vb2_expbuf(vdev->queue, p);
}

#ifndef V4L2_EXT_VSC_WIN_MODE_PBP
#define V4L2_EXT_VSC_WIN_MODE_PBP 2
#define V4L2_EXT_VSC_WIN_MODE_PIP 1
#endif
static int v4l2_vt_vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	//int ret = 0;
	struct video_device *vdev = video_devdata(file);
	struct vt_priv *prv_data = NULL;
	unsigned int mute;
	unsigned int sub_mode;
	kwrap_vp_timing_info_t ti;
	prv_data = ((struct vt_fh *)(file->private_data))->vt_priv;
	vsc_get_timinginfo(0,&ti);

	vsc_get_submode(&sub_mode);
	if(sub_mode == V4L2_EXT_VSC_WIN_MODE_PBP || sub_mode == V4L2_EXT_VSC_WIN_MODE_PIP) {
		if(prv_data->vtg_info.plane_prop.buf_count > 1 && prv_data->vtg_info.plane_prop.plane.w > 2560)
		{
			DE_ERROR("sub_mode = pbp/pip, impossible to use internal buffer");
			return -EACCES;
		}
	}

	ipc_phys_hal_CheckMute(0, &mute);
	if(mute && (prv_data->vt_target < 2) && (fh_vt_priv->vtg_info.plane_prop.l <= V4L2_EXT_CAPTURE_DISPLAY_OUTPUT))
	{
		DE_WARN("mute[%d] : return -ENODATA ", mute);
		return -ENODATA ;
	}

	if(prv_data->vtg_info.svp)
	{
		p->index = 0xFF;
		p->flags = V4L2_BUF_FLAG_ERROR;
		return -EACCES;
	}
	if(prv_data->vtg_info.ext8k_dec==1)
	{
		prv_data->vtg_info.ext8k_dec = 0; // reset ext8k_dec flag
		p->index = 0xFF;
		p->flags = V4L2_BUF_FLAG_ERROR;
		DE_WARN("ext8k_dec mode, return -EAGAIN");
		return -EAGAIN;
	}

	if(fh_vt_priv->vtg_info.plane_prop.l == V4L2_EXT_CAPTURE_DISPLAY_OUTPUT && \
		fh_vt_priv->vtg_info.plane_prop.buf_count == 3 && \
		(fh_vt_priv->vtg_info.plane_prop.plane.w == 3840 || fh_vt_priv->vtg_info.plane_prop.plane.h == 2160) && \
		(ti.hActive > 4096 || ti.vActive > 3840)) {
		if(ti.isMVI == 0) { // case : HDMI 8k
			DE_ERROR("8k input + 4k display capture, buf_num==3 : not supported");
			return -EAGAIN;
		}
	}

	// RITTEST-399
	if(((fh_vt_priv->vtg_info.win_info.in.w > 4096 || fh_vt_priv->vtg_info.win_info.in.h > 3840)) && fh_vt_priv->vtg_info.src_hdr_type) {
		/*if((fh_vt_priv->vtg_info.plane_prop.plane.w >= 3840 && fh_vt_priv->vtg_info.plane_prop.plane.h >= 2160) && \
			fh_vt_priv->vtg_info.plane_prop.buf_count == 3) */
                {
			p->index = 0xFF;
			p->flags = V4L2_BUF_FLAG_ERROR;
			DE_WARN("in wxh(%dx%d) hdr(%d) return -EACCES", fh_vt_priv->vtg_info.win_info.in.w, fh_vt_priv->vtg_info.win_info.in.h, fh_vt_priv->vtg_info.src_hdr_type);
			return -EACCES;
		}
	}

	return vb2_dqbuf(vdev->queue, p, file->f_flags & O_NONBLOCK);
}

static int v4l2_vt_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
//	struct vsc_fh *fh = __fh;

	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	// refer to SCDCR-2433
	if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O26)){
		strncpy(cap->driver, "o26", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O24)){
		strncpy(cap->driver, "o24", sizeof(cap->driver)-1);
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

	strncpy(cap->card, "vt", sizeof(cap->card)-1);
	cap->version = LINUX_VERSION_CODE; // #define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

	if(g_log_level < 2) DE_NOTI("Query cap !!!!! \n");

	return 0;
}

static int v4l2_vt_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	//struct vsc_fh *fh = __fh;

	if(g_log_level < 2) DE_NOTI("vt : id 0x%x (%s), value %d\n", \
		ctrl->id, ctrl_id_ext_to_str(ctrl->id),ctrl->value);
	if(g_vt_device_opened != 1) return 0;

	switch (ctrl->id) {
	case V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE:
		{
			ret = vt_set_divide_rate(1, 0, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING : // update index of out buffer (vtv mode)
		{
			ret = vt_set_out_buffer_index(1, &ctrl->value);
		}
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static int v4l2_vt_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	int ret;
	//struct vsc_fh *fh = __fh;

	//DE_NOTI("vt : id 0x%x (%s), value %d\n",
		//ctrl->id, ctrl_id_ext_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
	case V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE:
		{
			ret = vt_set_divide_rate(0, 0, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE:
		{
			ret = vt_get_output_rate(0, 0, &ctrl->value);
		}
		break;
	case V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING : // update index of out buffer (vtv mode)
		{
			ret = vt_set_out_buffer_index(0, &ctrl->value);
		}
		break;
	default:
		ret = -EINVAL;
	}

	return 0;
}

static int v4l2_vt_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	//struct vt_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			DE_NOTI("vt : id 0x%x (%s)\n", \
				ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			ret = vt_set_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;
	}
	return ret;

}

static int v4l2_vivt_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	//struct vsc_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			//DE_NOTI("vt : id 0x%x (%s)\n",ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			ret = vivt_get_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;
	}

	return -EINVAL;
}

static int v4l2_vt_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	//struct vsc_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			//DE_NOTI("vt : id 0x%x (%s)\n",ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			ret = vt_get_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;
	}

	return -EINVAL;
}

static int v4l2_vivt_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	//struct vt_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			//DE_NOTI("vt : id 0x%x (%s)\n", \
			//	ctrl->id, ctrl_id_ext_to_str(ctrl->id));

			ret = vivt_set_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;
	}
	return ret;

}


static int v4l2_vt_vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	//struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev  = video_drvdata(file);

	return 0;
}

static int v4l2_vt_vidioc_s_fmt_vid_cap(struct file *file, void *priv,
			        struct v4l2_format *f)
{
	//struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev  = video_drvdata(file);

	return 0;
}

static int v4l2_vt_vidioc_g_fmt_vid_cap_mplane(struct file *file, void *priv,
					struct v4l2_format *f)
{
	//struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev  = video_drvdata(file);
	struct v4l2_pix_format_mplane *mpix = &f->fmt.pix_mp;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;

	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

	mpix->width  = pVtg->plane_prop.plane.w;
	mpix->height = pVtg->plane_prop.plane.h;

	return 0;
}

static int v4l2_vt_vidioc_s_fmt_vid_cap_mplane(struct file *file, void *priv,
			        struct v4l2_format *f)
{
	//struct video_device *vdev = video_devdata(file);
	//struct vt_dev *dev  = video_drvdata(file);
	struct v4l2_pix_format_mplane *mpix = &f->fmt.pix_mp;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;

	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

	pVtg->plane_prop.plane.x = 0;
	pVtg->plane_prop.plane.y = 0;
	pVtg->plane_prop.plane.w = mpix->width;
	pVtg->plane_prop.plane.h = mpix->height;

	return 0;
}

static int v4l2_vt_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
//	int ret = 0;
	return v4l2_event_subscribe(__fh, sub, 32, NULL);
}

static int v4l2_vt_vidioc_unsubscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
//	int ret = 0;
	return v4l2_event_unsubscribe(__fh, sub);
}

/*Harish:: The format and size of planes either will be provided by user after checking supported format
or if only 1 format is supported then it need to be fixed
*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int queue_setup(struct vb2_queue *vq,
              unsigned int *nbuffers, unsigned int *nplanes,
             unsigned int sizes[], struct device *alloc_devs[])
#else
static int queue_setup(struct vb2_queue *vq, const void *parg,
              unsigned int *nbuffers, unsigned int *nplanes,
             unsigned int sizes[], void *alloc_ctxs[])
#endif
{
    //struct vt_dev *dev = vb2_get_drv_priv(vq);
	int width, height, stride;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
    if (vb2_get_num_buffers(vq) + *nbuffers < MAX_VT_BUF)
        *nbuffers = MAX_VT_BUF - vb2_get_num_buffers(vq);
#else
    if (vq->num_buffers + *nbuffers < MAX_VT_BUF)
        *nbuffers = MAX_VT_BUF - vq->num_buffers;
#endif

/*Harish: Hard code now for only YUV420 semiplaner format. Need to change it based on supported format and
user request for capture format
*/
    *nplanes = MAX_VT_PLANE;
/* If set format is called then we will setup as per requested format */
    //sizes[0] = sizes[1] = MAX_VT_PLANE_STRIDE * MAX_VT_PLANE_HEIGHT;
    if(fh_vt_priv->vt_target<2) {
		width = fh_vt_priv->vtg_info.plane_prop.plane.w;
		height= fh_vt_priv->vtg_info.plane_prop.plane.h;
		stride= fh_vt_priv->vtg_info.plane_info.stride;

	/*Only YCbCr4:2:0 [NV12] is supported */
		sizes[0] = fh_vt_priv->vtg_info.plane_info.stride * height;
		sizes[1] = sizes[0]/2;
    }
	else {
		width = fh_vt_priv->vtv_info.input_width;
		height= fh_vt_priv->vtv_info.input_height;
		stride= fh_vt_priv->vtv_info.in_info.stride;

	/*Only YCbCr4:2:0 [NV12] is supported */
		sizes[0] = fh_vt_priv->vtv_info.in_info.stride * height;
		sizes[1] = sizes[0]/2;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
#else
    	DE_NOTI("%s: num_buffers:%d, *nbuffers:%d, stride:%d w/h:%d/%d\n",__func__,\
		vq->num_buffers, *nbuffers, stride,width,height);
#endif

	if(stride < width) return -2;
    return (stride)?0:-1;
}


static int buffer_prepare(struct vb2_buffer *vb)
{
	//DE_NOTI("%s: ",__func__);
	return 0;
}

static void buffer_queue(struct vb2_buffer *vb)
{
	struct vt_cap_buffer *vbuf = to_vt_cap_buffer(vb);
	struct vt_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	// unlock buffer (QBUF)
	if(g_log_level == 3) DE_NOTI("%s: %p  - vt_qbuf",__func__,vbuf);

	spin_lock(&dev->slock);
	list_add_tail(&vbuf->list, &dev->vb_vt_cap_list);
	spin_unlock(&dev->slock);
}

static void buffer_finish(struct vb2_buffer *vb)
{
	struct vt_cap_buffer *vbuf = to_vt_cap_buffer(vb);

	// lock buffer (DQBUF)
	if(g_log_level == 3) DE_NOTI("%s: %p - vt_dqbuf",__func__,vbuf);
}

static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	int ret = 0;
	struct vt_dev *dev = vb2_get_drv_priv(vq);

	DE_NOTI("%s: ",__func__);

	if(g_vt_device_opened != 1) return 0;

	__kthread_exit = TRUE;

	if (dev){
		if (!dev->vt_cap_thread)
		{
			dev->vt_cap_thread = kthread_run(vt_capture_thread,dev,"%s",dev->v4l2_vt_video_dev.name);
			if (IS_ERR(dev->vt_cap_thread)) {
				ret = PTR_ERR(dev->vt_cap_thread);
				DE_ERROR("kthread_run err(%d)\n",ret);
				dev->vt_cap_thread = NULL;
				return ret;
			}
		}
	}

	return ret;
}

static void stop_streaming(struct vb2_queue *vq)
{
	struct vt_dev *dev = vb2_get_drv_priv(vq);
	DE_NOTI("%s: ",__func__);

	if (dev->vt_cap_thread == NULL)
		return;

//	if(fh_vt_priv->vt_target < 2)
//		_set_vtg_run(0, 0);

	send_sig(SIGUSR1, dev->vt_cap_thread, 0); // send signal to thread
	kthread_stop(dev->vt_cap_thread);

	/* Release all active buffers */
	spin_lock(&dev->slock);
	while (!list_empty(&dev->vb_vt_cap_list)) {
		struct vt_cap_buffer *buf;

		buf = list_entry(dev->vb_vt_cap_list.next,
				 struct vt_cap_buffer, list);
		list_del(&buf->list);
		//DE_NOTI("%s:: %p ",__func__,buf);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}
	spin_unlock(&dev->slock);

	__kthread_exit = FALSE;
	dev->vt_cap_thread = NULL;
}

/*
 * __find_vt plane_by_offset() - find plane associated with the given offset off
 */
static int __find_vt_plane_by_offset(struct vb2_queue *q, unsigned long off,
                        unsigned int *_buffer, unsigned int *_plane)
{
        struct vb2_buffer *vb;
        unsigned int buffer, plane;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	unsigned int q_num_buffers = vb2_get_num_buffers(q);
#else
	unsigned int q_num_buffers = q->num_buffers;
#endif
	/*
         * Go over all buffers and their planes, comparing the given offset
         * with an offset assigned to each plane. If a match is found,
         * return its buffer and plane numbers.
         */
        for (buffer = 0; buffer < q_num_buffers; ++buffer) {
                vb = q->bufs[buffer];

                for (plane = 0; plane < vb->num_planes; ++plane) {
                        if (vb->planes[plane].m.offset == off) {
                                *_buffer = buffer;
                                *_plane = plane;
                                return 0;
                        }
                }
        }

        return -EINVAL;
}

int v4l2_vt_mmap(struct vb2_queue *q, struct vm_area_struct *vma)
{
        unsigned long off = vma->vm_pgoff << PAGE_SHIFT;
        struct vb2_buffer *vb;
        unsigned int buffer = 0, plane = 0;
        int ret;
        unsigned long length;

        if (q->memory != VB2_MEMORY_MMAP) {
                DE_ERROR("queue is not currently set up for mmap\n");
                return -EINVAL;
        }

        /*
         * Check memory area access mode.
         */
        if (!(vma->vm_flags & VM_SHARED)) {
                DE_ERROR("invalid vma flags, VM_SHARED needed\n");
                return -EINVAL;
        }
        if (q->is_output) {
                if (!(vma->vm_flags & VM_WRITE)) {
                        DE_ERROR("invalid vma flags, VM_WRITE needed\n");
                        return -EINVAL;
                }
        } else {
                if (!(vma->vm_flags & VM_READ)) {
                        DE_ERROR("invalid vma flags, VM_READ needed\n");
                        return -EINVAL;
                }
        }

        mutex_lock(&q->mmap_lock);

        if (vb2_fileio_is_active(q)) {
                DE_ERROR("mmap: file io in progress\n");
                ret = -EBUSY;
                goto unlock;
        }

        /*
         * Find the plane corresponding to the offset passed by userspace.
         */
        ret = __find_vt_plane_by_offset(q, off, &buffer, &plane);
        if (ret)
                goto unlock;

        vb = q->bufs[buffer];

        /*
         * MMAP requires page_aligned buffers.
         * The buffer length was page_aligned at __vb2_buf_mem_alloc(),
         * so, we need to do the same here.
         */
        length = PAGE_ALIGN(vb->planes[plane].length);
        if (length < (vma->vm_end - vma->vm_start)) {
                DE_ERROR("MMAP invalid, as it would overflow buffer length\n");
                ret = -EINVAL;
                goto unlock;
        }

        /*
         * vm_pgoff is treated in V4L2 API as a 'cookie' to select a buffer,
         * not as a in-buffer offset. We always want to mmap a whole buffer
         * from its beginning.
         */
        vma->vm_pgoff = 0;

        ret = vb->vb2_queue->mem_ops->mmap
		? vb->vb2_queue->mem_ops->mmap(vb->planes[plane].mem_priv, vma) : 0;

unlock:
        mutex_unlock(&q->mmap_lock);
        if (ret) {
			DE_ERROR("MMAP fail.");
            return ret;
        }

        DE_NOTI("buffer %d, plane %d successfully mapped\n", buffer, plane);
        return 0;
}

__attribute__((unused)) static int v4l2_vt_fop_mmap(struct file *file, struct vm_area_struct *vma)
{
        struct video_device *vdev = video_devdata(file);

        return v4l2_vt_mmap(vdev->queue, vma);
}


static struct platform_device v4l2_vt_pdev = {
	.name = "v4l2_vt",
	.id = -1,
};

static struct platform_device v4l2_vivt_pdev = {
	.name = "v4l2_vivt",
	.id = -1,
};

static struct dev_pm_ops const vt_pm_ops = {
	.resume = v4l2_vt_resume,
	.suspend = v4l2_vt_suspend,
	.runtime_resume = v4l2_vt_runtime_resume,
	.runtime_suspend = v4l2_vt_runtime_suspend,
};

static struct platform_driver v4l2_vt_driver = {
	.probe      = v4l2_vt_probe,
	.driver     = {
		.name   = "v4l2_vt",
		.owner  = THIS_MODULE,
		.pm     = &vt_pm_ops,
	},
	.remove		= v4l2_vt_remove,
};

static struct platform_driver v4l2_vivt_driver = {
	.probe      = v4l2_vt_probe,
	.driver     = {
		.name   = "v4l2_vivt",
		.owner  = THIS_MODULE,
		.pm     = &vt_pm_ops,
	},
	.remove		= v4l2_vt_remove,
};

struct v4l2_file_operations v4l2_vt_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_vt_fh_open,
	.release	= v4l2_vt_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read       = vb2_fop_read,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
    .mmap       = v4l2_vt_fop_mmap,
#else
	.mmap       = vb2_fop_mmap,
#endif
	.poll       = v4l2_vt_poll,
};

struct v4l2_file_operations v4l2_vivt_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_vivt_fh_open,
	.release	= v4l2_vivt_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read       = vb2_fop_read,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
    .mmap       = v4l2_vt_fop_mmap,
#else
    .mmap       = vb2_fop_mmap,
#endif

	//.poll       = v4l2_vt_poll,
};

static struct vb2_ops vt_cap_qops = {
	.queue_setup        = queue_setup,
	.buf_prepare        = buffer_prepare,
	.buf_queue          = buffer_queue,
	.buf_finish         = buffer_finish,
	.start_streaming    = start_streaming,
	.stop_streaming     = stop_streaming,
	.wait_prepare       = vb2_ops_wait_prepare,
	.wait_finish        = vb2_ops_wait_finish,
};

struct v4l2_ioctl_ops v4l2_vt_ioctl_ops = {
	.vidioc_querycap		= v4l2_vt_vidioc_querycap,
	.vidioc_s_ctrl			= v4l2_vt_vidioc_s_ctrl,
	.vidioc_g_ctrl			= v4l2_vt_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_vt_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_vt_vidioc_g_ext_ctrls,
    .vidioc_g_fmt_vid_cap   = v4l2_vt_vidioc_g_fmt_vid_cap,
    .vidioc_s_fmt_vid_cap   = v4l2_vt_vidioc_s_fmt_vid_cap,
    .vidioc_g_fmt_vid_cap_mplane = v4l2_vt_vidioc_g_fmt_vid_cap_mplane,
    .vidioc_s_fmt_vid_cap_mplane = v4l2_vt_vidioc_s_fmt_vid_cap_mplane,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_vt_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_vt_vidioc_unsubscribe_event,
    .vidioc_reqbufs         = v4l2_vt_vidioc_reqbufs,
	.vidioc_create_bufs     = vb2_ioctl_create_bufs,
	.vidioc_querybuf        = vb2_ioctl_querybuf,
	.vidioc_expbuf          = v4l2_vt_vidioc_expbuf,
	.vidioc_qbuf            = vb2_ioctl_qbuf,
	.vidioc_dqbuf           = v4l2_vt_vidioc_dqbuf,
	.vidioc_streamon        = vb2_ioctl_streamon,
	.vidioc_streamoff       = vb2_ioctl_streamoff,
};

struct v4l2_ioctl_ops v4l2_vivt_ioctl_ops = {
	.vidioc_s_ext_ctrls		= v4l2_vivt_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_vivt_vidioc_g_ext_ctrls,
};

int v4l2_vt_register(void *arg)
{
	int ret = 0;
    struct vt_dev *dev;
	struct vt_dev *dev2;
    struct video_device *vfd;
	struct video_device *vfd2;
    struct vb2_queue *q;
#ifdef INCLUDE_KDRV_OVI
	LX_OVI_HW_DISPLAY_INFO_T ovi_opt;
#endif

	platform_driver_register(&v4l2_vt_driver);
	platform_device_register(&v4l2_vt_pdev);

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev){
        return -ENOMEM;}
    dev2 = kzalloc(sizeof(*dev2), GFP_KERNEL);
    if (!dev2){
        return -ENOMEM;}

	dev->model = 0;
#ifdef INCLUDE_KDRV_OVI
	ret = OVI_HAL_GetHWDisplayOption(&ovi_opt);

	if (ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080 || ovi_opt.panelResolution == LX_OVI_PANEL_RESOLUTION_1366X768)
	{
		DE_NOTI("model : FHD\n");
		dev->model = 1;
	}
#endif

    do{
        ret = v4l2_device_register(&v4l2_vt_pdev.dev, &dev->v4l2_vt_dev);
        if(ret < 0){
            DE_NOTI(" vt : v4l2_device_register error[%d]\n", ret);
            return ret;
        }

	mutex_init(&vt_mutex_lock);
	mutex_init(&vivt_mutex_lock);
        spin_lock_init(&dev->slock);
        mutex_init(&dev->v4l2_vt_video_device_lock);
        INIT_LIST_HEAD(&dev->vb_vt_cap_list);
        dev->pdev = &v4l2_vt_pdev;

        q = &dev->vb_vt_cap_q;
        q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	    q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
        q->drv_priv = dev;
        q->buf_struct_size = sizeof(struct vt_cap_buffer);
        q->ops = &vt_cap_qops;
        q->mem_ops = &vb2_vt_memops;
        q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0) 
        q->min_queued_buffers = MIN_VT_BUF;
#else  
        q->min_buffers_needed = MIN_VT_BUF;
#endif
	q->lock = &dev->v4l2_vt_video_device_lock;

        ret = vb2_queue_init(q);
        if (ret){
            DE_NOTI("vb2_queue init error: %d\n", ret);
            return -1;
        }

        // vt
        vfd = &dev->v4l2_vt_video_dev;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        strscpy(vfd->name, "vt-capture-dev", sizeof(vfd->name));
#else
        strlcpy(vfd->name, "vt-capture-dev", sizeof(vfd->name));
#endif
        vfd->v4l2_dev  = &dev->v4l2_vt_dev;
        vfd->fops      = &v4l2_vt_fops;
        vfd->ioctl_ops = &v4l2_vt_ioctl_ops;
        vfd->release   = video_device_release_empty;
        vfd->queue     = &dev->vb_vt_cap_q;                //Link vb_queue with videodevice
        vfd->lock      = &dev->v4l2_vt_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE;
#endif
        video_set_drvdata(vfd, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_CAPTURE);
#else
        ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_CAPTURE);
#endif
		if (ret < 0) {
            DE_NOTI("video device register error: %d\n", ret);
            return -1;
        }

		platform_driver_register(&v4l2_vivt_driver);
		platform_device_register(&v4l2_vivt_pdev);

		ret = v4l2_device_register(&v4l2_vivt_pdev.dev, &dev2->v4l2_vivt_dev);
		if (ret < 0) {
			DE_NOTI("video device register error: %d\n", ret);
			return -1;
		}

		dev2->pdev = &v4l2_vivt_pdev;

        // vivt (svp color histogram)
        vfd2 = &dev2->v4l2_vivt_video_dev;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        strscpy(vfd2->name, "vvivtdev-dev", sizeof(vfd2->name));
#else
        strlcpy(vfd2->name, "vivtdev-dev", sizeof(vfd2->name));
#endif
        vfd2->v4l2_dev  = &dev2->v4l2_vivt_dev;
        vfd2->fops	   = &v4l2_vivt_fops;
        vfd2->ioctl_ops = &v4l2_vivt_ioctl_ops;
        vfd2->release   = video_device_release_empty;
        vfd2->queue	   = &dev2->vb_vt_cap_q;				//Link vb_queue with videodevice
        vfd2->lock	   = &dev2->v4l2_vt_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        vfd2->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_VIDEO_CAPTURE;
#endif
        video_set_drvdata(vfd2, dev2);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(vfd2, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_CAPTURE + 1);
#else
        ret = video_register_device(vfd2, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_CAPTURE + 1);
#endif
        if (ret < 0) {
            DE_NOTI("video device register error: %d\n", ret);
            return -1;
        }
        DE_NOTI("register vivt device(%d)", V4L2_EXT_DEV_NO_CAPTURE + 1);
    } while(0);

	return ret;
}

static inline struct file_vb2_q *to_file_vb2_q(struct vb2_queue *vq)
{
	return container_of(vq, struct file_vb2_q, queue);
}

static inline struct vt_priv *file_prvdata(struct file *file){
        return ((struct vt_fh *)(file->private_data))->vt_priv;
}

static int vt_capture_thread(void *data)
{
//	struct vb2_queue *vq = (struct vb2_queue *)data;
//	struct file_vb2_q *file_q   = to_file_vb2_q(vq);
//	struct vt_priv   *pvt      = file_prvdata(file_q->file);

	struct vt_dev *dev = (struct vt_dev *)data;
	struct vt_cap_buffer *buff = NULL;
	int ret = RET_ERROR, timeout = 0;
	int buffIdx = 0, count = 0, prev_idx = 0xFF;
	struct v4l2_ext_capture_freeze_mode frz;
	int frz_wait_count;
	kwrap_vp_timing_info_t ti;
	int in_w, in_h, nFound = 0;
	struct list_head *head = NULL, *head_old = NULL;

	ktime_t 	   t;
	struct timespec64 ts;
	UINT32 t_sec, t_msec,t_sec_prev, t_msec_prev,time_diff=0;

    //DE_NOTI("%s: ",__func__);

	allow_signal(SIGUSR1);
    while (!kthread_should_stop()) {
        buff = NULL;

		//DE_NOTI("fh_vt_priv->vt_target = %d", fh_vt_priv->vt_target);

		if(fh_vt_priv->vt_target<2) {
			timeout = de_sync_wait(SYNC_WAIT_WEL);
		}
		else {//if(fh_vt_priv->vt_target == 2)
			timeout = de_sync_wait(SYNC_WAIT_USB);
		}

		if(!__kthread_exit){
			return 0;
		}

		ret = vt_get_ridx(&buffIdx);
		if(ret) {DE_ERROR("vt_get_ridx error");}
		if(buffIdx < 0 && buffIdx >= MAX_VTG_BUFFER) {
			DE_ERROR("vt_get_ridx error [%d]", buffIdx);
			continue;
		}

		if(fh_vt_priv->vtg_info.plane_prop.buf_count==1) {
			frz.plane_index = 0;
			frz.val = 1;
			vt_set_freeze(0, &frz); // lock current buffer (if buf_count==1) until close capture path
			frz_wait_count = g_frz_wait;
			while(frz_wait_count--) {
				de_sync_wait(SYNC_WAIT_WEL); // wait until activating of frz
				//DE_NOTI("lock buffer idx[%d] count[%d]", buffIdx, frz_wait_count);
			}
		}
		else
		{
			if(buffIdx == prev_idx && !timeout) continue;
			prev_idx = buffIdx;
		}

		vsc_get_timinginfo(0, &ti);
		in_w = fh_vt_priv->vtg_info.win_info.in.w = ti.hActive;
		in_h = fh_vt_priv->vtg_info.win_info.in.h = ti.vActive;
		fh_vt_priv->vtg_info.src_hdr_type = ti.hdr_type;
		//DE_NOTI("[%dx%d] hdr_type[%d]", fh_vt_priv->vtg_info.win_info.in.w, fh_vt_priv->vtg_info.win_info.in.h, ti.hdr_type);
#ifdef INCLUDE_KDRV_OVI
		if(fh_vt_priv->vt_target == 1 && fh_vt_priv->vtg_info.plane_prop.buf_count==5 && ti.cp_streaming==0) {//VTG & 5 buffer = VR360
			if(ti.vFreq <= 300 && (ti.isMVI))  {// for source rate (TVPLAT-51006)
				unsigned int rate;
				if(fh_vt_priv->vtg_info.need_half_rate == 1 && fh_vt_priv->vtg_info.ext8k_frc == 0)
					rate = 3; // 120Hz model
				else
					rate = 1; // 60Hz model
				vt_set_divide_rate(1, 0, &rate);
			}
		}
#endif
		spin_lock(&dev->slock);

		/*Harish: Got the availabel buffer index now.
		    TODO:  Remove the buffer from queue with index only. Now removing buffer at start only */
		head = &dev->vb_vt_cap_list;
		head_old = &dev->vb_vt_cap_list;
		while(!list_empty(head) && (head->next != head_old)) {
			if(fh_vt_priv->vtg_info.plane_prop.buf_count==1 && count++<5)
				DE_NOTI("Index: %d locked",buffIdx);
			buff = (struct vt_cap_buffer *)list_entry(head->next, struct vt_cap_buffer, list);

			if(buff->vb.vb2_buf.index == buffIdx){
				list_del(&buff->list);
				nFound = 1;
				break;
			}
			head = head->next;
		}

		if(ti.vActive > 2160 && ti.phyMode > 1 && fh_vt_priv->vtg_info.plane_prop.buf_count==5) {
			if(in_h > 2160) {
				fh_vt_priv->vtg_info.ext8k_dec = 1;
				DE_WARN("======>>>>>  vt in_w,in_h = %dx%d", in_w, in_h);
			}
			else {
				fh_vt_priv->vtg_info.ext8k_dec = 0;
			}
		}

		if(nFound && buff){
			t  = ktime_get_real();
			ts = ktime_to_timespec64(t);
			t_sec  = ts.tv_sec;
			t_msec = ts.tv_nsec/1000000;
			time_diff = (t_sec*1000+t_msec)-(t_sec_prev*1000+t_msec_prev);
			t_sec_prev = t_sec;
			t_msec_prev = t_msec;

			if(!timeout)
				vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_DONE);
			else
				vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_ERROR);
			vt_capture_notification(V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT, dev, buffIdx);
			if(g_log_level == 3) DE_NOTI("idx[%d] buff[%p][%d] offs[%d] fr[%d] diff[%dmsec]", \
				buffIdx, buff, buff->vb.vb2_buf.index, g_idx_offset, ti.vFreq,time_diff);
		}
		nFound = 0;
		spin_unlock(&dev->slock);
    }

    DE_NOTI("%s: stop",__func__);
	return 0;
}


#define VT_M2A_BUFFER_COUNT 5
#define VT_A2M_BUFFER_COUNT 3

struct vtg_texture_info
{
	//read only
	LX_DE_SCAN_T src_scan_type;
	LX_DE_RECT_T src_size;
	LX_DE_RECT_T out_win;
	LX_DE_RECT_T panel_size;
	LX_DE_RECT_T out_region;
	LX_DE_RECT_T act_region;
//	unsigned int out_index;

	unsigned int y_frame[VT_M2A_BUFFER_COUNT]; ///< y frame data start address
	unsigned int c_frame[VT_M2A_BUFFER_COUNT]; ///< cbcr frame data start address

	// write only
	unsigned int location; // VTG_src, VTG_disp
	LX_DE_RECT_T capture_size;
	unsigned int frz_index;
	unsigned int frz_flag;
	unsigned int out_index;
};

struct vtv_texture_info
{
	//read only

	unsigned int in_y_frame[VT_M2A_BUFFER_COUNT]; ///< y frame data start address
	unsigned int in_c_frame[VT_M2A_BUFFER_COUNT]; ///< cbcr frame data start address

	unsigned int out_y_frame[VT_A2M_BUFFER_COUNT]; ///< y frame data start address
	unsigned int out_c_frame[VT_A2M_BUFFER_COUNT]; ///< cbcr frame data start address

	// write only

};

struct vt_texture
{
	unsigned int shared_addr_vtg;
	struct vtg_texture_info vtg_info;

	unsigned int shared_addr_vtv;
	struct vtv_texture_info vtv_info;
};
#ifdef USE_KDRV_CODES_FOR_M23
#include "de_cfg_m23.h"
#endif

static int vt_get_capability_info(unsigned int win_id, \
	struct v4l2_ext_capture_capability_info *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg;
	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}

	pVtg = &fh_vt_priv->vtg_info;

	param->flags = \
		V4L2_EXT_CAPTURE_CAP_INPUT_VIDEO_DEINTERLACE   | \
		V4L2_EXT_CAPTURE_CAP_DISPLAY_VIDEO_DEINTERLACE | \
		V4L2_EXT_CAPTURE_CAP_SCALE_UP                  | \
		V4L2_EXT_CAPTURE_CAP_SCALE_DOWN                | \
		V4L2_EXT_CAPTURE_CAP_DIVIDE_FRAMERATE;

	param->max_res.x = 0;
	param->max_res.y = 0;

	if (LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		LX_DE_IPC_SYSTEM_MODEL_T system = {.u32Data = 0,};
#ifdef USE_KDRV_CODES_FOR_M23
		de_cfg_m23_get_hw_opt(&system.u32Data);
#endif
		param->flags |= V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO;

		switch(system.panel_resolution)
		{
			case LX_DE_IPC_PANEL_RESOLUTION_1280x720:
			case LX_DE_IPC_PANEL_RESOLUTION_1366x768:
				param->scale_up_limit_w = 1280;
				param->scale_up_limit_h = 720;
				param->max_res.w = pVtg->max_w = 1280;
				param->max_res.h = pVtg->max_h = 720;
				break;
			case LX_DE_IPC_PANEL_RESOLUTION_1920x1080:
				param->scale_up_limit_w = 1920;
				param->scale_up_limit_h = 1080;
				param->max_res.w = pVtg->max_w = 1920;
				param->max_res.h = pVtg->max_h = 1080;
				break;
			case LX_DE_IPC_PANEL_RESOLUTION_3840x2160:
			default:
				param->scale_up_limit_w = MAX_VT_PLANE_WIDTH;
				param->scale_up_limit_h = MAX_VT_PLANE_HEIGHT;
				param->max_res.w = pVtg->max_w = MAX_VT_PLANE_WIDTH;
				param->max_res.h = pVtg->max_h = MAX_VT_PLANE_HEIGHT;
			break;
		}
	}
	else {
		param->scale_up_limit_w = MAX_VT_PLANE_WIDTH;
		param->scale_up_limit_h = MAX_VT_PLANE_HEIGHT;
		param->max_res.w = pVtg->max_w = MAX_VT_PLANE_WIDTH;
		param->max_res.h = pVtg->max_h = MAX_VT_PLANE_HEIGHT;
	}
	param->scale_down_limit_w = MIN_VT_PLANE_WIDTH;
	param->scale_down_limit_h = MIN_VT_PLANE_HEIGHT;

	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		param->num_video_frame_buffer = 3;
	}
	else {
		param->num_video_frame_buffer = MAX_VT_BUF;
	}
	param->num_plane = \
		V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_SEMI_PLANAR;
	param->pixel_format = \
		V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_SEMI_PLANAR;

	return ret;
}

unsigned int prev_vivt_y_frame[MAX_VTG_BUFFER];
unsigned int prev_vivt_c_frame[MAX_VTG_BUFFER];

static int _get_vivt_vtg_info(void)
{
	int ret = 0, i;
	VTG_INFO_T *p_m2a;
	VTG_INFO_T *p_a2m;
	struct vtg_cap_info *p;

	if(fh_vivt_priv==NULL) {DE_ERROR("***fh_vivt_priv==NULL"); return -1;}
	p = &fh_vivt_priv->vtg_info;

	if(p==NULL) {DE_ERROR("p==NULL"); return -1;}
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}
	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -3;}

	p_m2a = (VTG_INFO_T *)p->m2a;
	p_a2m = (VTG_INFO_T *)p->a2m;

	p->win_info.type = p_m2a->scan;
	p->win_info.in.x = p_m2a->srcSize.x;
	p->win_info.in.y = p_m2a->srcSize.y;
	p->win_info.in.w = p_m2a->srcSize.w;
	p->win_info.in.h = p_m2a->srcSize.h;
	p->win_info.out.x = p_m2a->outSize.x;
	p->win_info.out.y = p_m2a->outSize.y;
	p->win_info.out.w = p_m2a->outSize.w;
	p->win_info.out.h = p_m2a->outSize.h;
	p->win_info.panel.w = p_m2a->panelSize.w;
	p->win_info.panel.h = p_m2a->panelSize.h;

	p->plane_info.stride = p_m2a->stride;
	p->plane_info.plane_region.w = p_a2m->w_out_size.w;
	p->plane_info.plane_region.h = p_a2m->w_out_size.h;
	p->plane_info.active_region.x = p_m2a->winSize.x;
	p->plane_info.active_region.y = p_m2a->winSize.y;
	p->plane_info.active_region.w = (p_m2a->winSize.w>p_a2m->w_out_size.w)?p_a2m->w_out_size.w:p_m2a->winSize.w;
	p->plane_info.active_region.h = (p_m2a->winSize.h>p_a2m->w_out_size.h)?p_a2m->w_out_size.h:p_m2a->winSize.h;
	p->w_out.w = p_m2a->w_out_size.w;
	p->w_out.h = p_m2a->w_out_size.h;
	p->r_idx = p_m2a->r_idx;
	for(i=0;i<MAX_VTG_BUFFER;i++)
	{
		if(p_m2a->y_frame[i] == 0xffffffff || p_m2a->y_frame[i] == 0)
			p->y_frame[i] = prev_vivt_y_frame[i];
		else
			p->y_frame[i] = p_m2a->y_frame[i];

		if(p_m2a->c_frame[i] == 0xffffffff || p_m2a->c_frame[i] == 0)
			p->c_frame[i] = prev_vivt_c_frame[i];
		else
			p->c_frame[i] = p_m2a->c_frame[i];

		prev_vivt_y_frame[i] = p->y_frame[i];
		prev_vivt_c_frame[i] = p->c_frame[i];
	}
	p->svp = p_m2a->isSecure;

	return ret;
}

unsigned int prev_vtg_y_frame[MAX_VTG_BUFFER];
unsigned int prev_vtg_c_frame[MAX_VTG_BUFFER];

static int _get_vtg_info(void)
{
	int ret = 0, i;
	VTG_INFO_T *p_m2a;
	VTG_INFO_T *p_a2m;
	struct vtg_cap_info *p = &fh_vt_priv->vtg_info;

	if(p==NULL) {DE_ERROR("p==NULL"); return -1;}
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}
	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -3;}

	p_m2a = (VTG_INFO_T *)p->m2a;
	p_a2m = (VTG_INFO_T *)p->a2m;

	p->win_info.type = p_m2a->scan;
	p->win_info.in.x = p_m2a->srcSize.x;
	p->win_info.in.y = p_m2a->srcSize.y;
	p->win_info.in.w = p_m2a->srcSize.w;
	p->win_info.in.h = p_m2a->srcSize.h;
	p->win_info.out.x = p_m2a->outSize.x;
	p->win_info.out.y = p_m2a->outSize.y;
	p->win_info.out.w = p_m2a->outSize.w;
	p->win_info.out.h = p_m2a->outSize.h;
	p->win_info.panel.w = p_m2a->panelSize.w;
	p->win_info.panel.h = p_m2a->panelSize.h;

	p->plane_info.stride = p_m2a->stride;
	p->plane_info.plane_region.w = p_a2m->w_out_size.w;
	p->plane_info.plane_region.h = p_a2m->w_out_size.h;
	p->plane_info.active_region.x = p_m2a->winSize.x;
	p->plane_info.active_region.y = p_m2a->winSize.y;
	p->plane_info.active_region.w = (p_m2a->winSize.w>p_a2m->w_out_size.w)?p_a2m->w_out_size.w:p_m2a->winSize.w;
	p->plane_info.active_region.h = (p_m2a->winSize.h>p_a2m->w_out_size.h)?p_a2m->w_out_size.h:p_m2a->winSize.h;
	p->w_out.w = p_m2a->w_out_size.w;
	p->w_out.h = p_m2a->w_out_size.h;
	p->r_idx = p_m2a->r_idx;
	for(i=0;i<MAX_VTG_BUFFER;i++)
	{
		if(p_m2a->y_frame[i] == 0xffffffff || p_m2a->y_frame[i] == 0)
			p->y_frame[i] = prev_vtg_y_frame[i];
		else
			p->y_frame[i] = p_m2a->y_frame[i];
		if(p_m2a->c_frame[i] == 0xffffffff || p_m2a->c_frame[i] == 0)
			p->c_frame[i] = prev_vtg_y_frame[i];
		else
			p->c_frame[i] = p_m2a->c_frame[i];

		prev_vtg_y_frame[i] = p->y_frame[i];
		prev_vtg_c_frame[i] = p->c_frame[i];
	}
	if(test_cmd == 1) {
		p->svp = 1;
		if(g_log_level < 1)DE_NOTI("set_by_proc:svp=1");
	}
	else
		p->svp = p_m2a->isSecure;

	return ret;
}

static int _set_vivt_vtg_info(void)
{
	int ret = 0;
	VTG_INFO_T *p_a2m, *p_m2a;
	struct vtg_cap_info *p;

	if(fh_vivt_priv==NULL) {DE_ERROR("***fh_vivt_priv==NULL"); return -1;}
	p = &fh_vivt_priv->vtg_info;

	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}

	p_a2m = (VTG_INFO_T *)p->a2m;
	p_m2a = (VTG_INFO_T *)p->m2a;

	p_a2m->location = (p->plane_prop.l>0)? (LX_DE_LOCATION_T)(p->plane_prop.l-1):(LX_DE_LOCATION_T)p->plane_prop.l;
	p_a2m->crop_size.x = 0;
	p_a2m->crop_size.y = 0;
	p_a2m->crop_size.w = p_m2a->panelSize.w;
	p_a2m->crop_size.h = p_m2a->panelSize.h;
	p_a2m->w_out_size.x = p->plane_prop.plane.x;
	p_a2m->w_out_size.y = p->plane_prop.plane.y;
	p_a2m->w_out_size.w = p->plane_prop.plane.w;
	p_a2m->w_out_size.h = p->plane_prop.plane.h;
	p_a2m->numBuffer = p->plane_prop.buf_count;
	p_a2m->frz  = p->freeze.val;
	p_a2m->rate = p->rate;
	p_a2m->svp_hist = 1;

	return ret;
}

static int _set_vtg_info(void)
{
	int ret = 0;
	VTG_INFO_T *p_a2m, *p_m2a;
	unsigned int tot;
	struct vtg_cap_info *p = &fh_vt_priv->vtg_info;

	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}

	p_a2m = (VTG_INFO_T *)p->a2m;
	p_m2a = (VTG_INFO_T *)p->m2a;

	p_a2m->location = (p->plane_prop.l>0)? (LX_DE_LOCATION_T)(p->plane_prop.l-1):(LX_DE_LOCATION_T)p->plane_prop.l;
	if(p->plane_prop.l == 5) p_a2m->location = p->plane_prop.l; // for bg capture , https://harmony.lge.com:8443/issue/browse/IDSICRQ-97
	g_prev_loc = p_a2m->location;
	p_a2m->crop_size.x = 0;
	p_a2m->crop_size.y = 0;
	p_a2m->crop_size.w = p_m2a->panelSize.w;
	p_a2m->crop_size.h = p_m2a->panelSize.h;
	p_a2m->w_out_size.x = p->plane_prop.plane.x;
	p_a2m->w_out_size.y = p->plane_prop.plane.y;
	p_a2m->w_out_size.w = p->plane_prop.plane.w;
	p_a2m->w_out_size.h = p->plane_prop.plane.h;
	p_a2m->numBuffer = p->plane_prop.buf_count;
	p_a2m->frz  = p->freeze.val;
	p_a2m->rate = p->rate;
	tot = p->plane_prop.plane.w * p->plane_prop.plane.h * p->plane_prop.buf_count;
	if(p->model == 1) { // FHD model(1366x768)
		if(tot > 1280 * 720 * 1 )
			p_a2m->frc_mode = 1;
		else
			p_a2m->frc_mode = 0;
	}
	else {
		if(tot > 3840 * 2160 * 1) { // over than ext_buffer_size
			p_a2m->frc_mode = 1; // use internal buffer
		}
		else {
			p_a2m->frc_mode = 0; // use external buffer
		}
	}
//	p_a2m->frz_index = p->freeze.plane_index;

	return ret;
}

static int _set_vivt_vtg_run(unsigned int c, unsigned int shared_mem_addr)
{
	int ret = 0;
	VTG_INFO_T *p_a2m;
	struct vtg_cap_info *p;

	if(fh_vivt_priv==NULL) {DE_ERROR("***fh_vivt_priv==NULL"); return -1;}
	p = &fh_vivt_priv->vtg_info;

	if(p==NULL){DE_ERROR("p==NULL"); return -1;}

	p_a2m = (VTG_INFO_T *)p->a2m;
	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}

	if(c) { // initial information for capture setup
		p_a2m->address      = shared_mem_addr;
		p_a2m->location     = g_prev_loc;
		p_a2m->w_out_size.w = 256;
		p_a2m->w_out_size.h = 256;
		p_a2m->numBuffer    = 3;
	}
	else {
		p_a2m->address      = shared_mem_addr;
		p_a2m->location     = 0;
		p_a2m->w_out_size.w = 0;
		p_a2m->w_out_size.h = 0;
		p_a2m->numBuffer    = 0;
	}
	p_a2m->enable  = c;

	ret = DE_IO_SetSharedMem((unsigned long)&c);
	return ret;
}

static int _set_vtg_run(unsigned int c, unsigned int shared_mem_addr)
{
	int ret = 0;
	VTG_INFO_T *p_a2m;
	struct vtg_cap_info *p = &fh_vt_priv->vtg_info;

	if(p==NULL){DE_ERROR("p==NULL"); return -1;}

	p_a2m = (VTG_INFO_T *)p->a2m;
	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}

	if(g_prev_loc == 5) g_prev_loc = 2; // SCDCR-7976, SOCTSSIC-185909, SICDTV-16211
	if(c) { // initial information for capture setup
		p_a2m->address      = shared_mem_addr;
		p_a2m->location     = g_prev_loc;
		p_a2m->w_out_size.w = 256;
		p_a2m->w_out_size.h = 256;
		p_a2m->numBuffer    = 3;
	}
	else {
		p_a2m->address      = shared_mem_addr;
		p_a2m->location     = 2;
		p_a2m->w_out_size.w = 256;
		p_a2m->w_out_size.h = 256;
		p_a2m->numBuffer    = 1;
	}
	p_a2m->enable  = c;

	ret = DE_IO_SetSharedMem((unsigned long)&c);
	return ret;
}

static int _get_vtv_info(void)
{
	int ret = 0;
	VTV_INFO_T *p_m2a;
	struct vtv_cap_info *p = &fh_vt_priv->vtv_info;

	if(p==NULL) {DE_ERROR("p==NULL"); return -1;}
	p_m2a = (VTV_INFO_T *)p->m2a;
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}

	memcpy(&p->in_info,  &p_m2a->in_info[0], sizeof(LX_DE_FRAMEINFO_T));
	memcpy(&p->out_info, &p_m2a->out_info[0],   sizeof(LX_DE_FRAMEINFO_T));
	memcpy(p->in_buf,  p_m2a->in_buf,  sizeof(LX_DE_FRAMEBUFFER_T)*5);
	memcpy(p->out_buf, p_m2a->out_buf, sizeof(LX_DE_FRAMEBUFFER_T)*3);
	p->r_idx = p_m2a->r_idx;
	p->mute  = p_m2a->mute;

	return ret;
}

static int _set_vtv_info(void)
{
	int ret = 0;
	int i;
	VTV_INFO_T *p_a2m, *p_m2a;
	struct vtv_cap_info *p = &fh_vt_priv->vtv_info;

	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}
	if(p->m2a==NULL){DE_ERROR("p->m2a==NULL"); return -2;}

	p_a2m = (VTV_INFO_T *)p->a2m;
	p_m2a = (VTV_INFO_T *)p->m2a;

	p_a2m->mute = 1;
	p_a2m->address = p->shared_mem;
	p_a2m->reserved = 0x1234;

	p_m2a->mute = 1;

	for(i=0;i<5;i++)
	{
		p_a2m->in_info[i].sampling = LX_DE_SCALER_420;
		p_a2m->in_info[i].bitdepth = LX_DE_BPP_8;
		p_a2m->in_info[i].width    = p->input_width;
		p_a2m->in_info[i].height   = p->input_height;
	}
	for(i=0;i<3;i++)
	{
		p_a2m->out_info[i].sampling = LX_DE_SCALER_420;
		p_a2m->out_info[i].bitdepth = LX_DE_BPP_8;
		p_a2m->out_info[i].stride   = p->output_width;
		p_a2m->out_info[i].width    = p->output_width;
		p_a2m->out_info[i].height   = p->output_height;
	}
	return ret;
}

static int _set_vtv_run(unsigned int c, unsigned int shared_mem_addr)
{
	int ret = 0;
	VTV_INFO_T *p_a2m;
	struct vtv_cap_info *p = &fh_vt_priv->vtv_info;

	p_a2m = (VTV_INFO_T *)p->a2m;
	if(p->a2m==NULL){DE_ERROR("p->a2m==NULL"); return -1;}

	p_a2m->enable  = c;
	//p_a2m->address = (c==1)?p->shared_mem:0;

	ret = DE_IO_SetSharedMem((unsigned long)&c);
	return ret;
}

static int vt_get_win_info(unsigned int win_id, \
	struct v4l2_ext_capture_video_win_info *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;
	struct vtv_cap_info *pVtv = &fh_vt_priv->vtv_info;

	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}
	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

	// get win_info from firmware
	ret = _get_vtg_info();

	param->type = pVtg->win_info.type;

	if(fh_vt_priv->vt_target<2) {
		param->in.x = pVtg->win_info.in.x;
		param->in.y = pVtg->win_info.in.y;
		param->in.w = pVtg->win_info.in.w;
		param->in.h = pVtg->win_info.in.h;
		param->out.x = pVtg->win_info.out.x;
		param->out.y = pVtg->win_info.out.y;
		param->out.w = pVtg->win_info.out.w;
		param->out.h = pVtg->win_info.out.h;
	}
	else {
		param->in.x = 0;
		param->in.y = 0;
		param->in.w = pVtv->in_info.width;
		param->in.h = pVtv->in_info.height;
		param->out.x = 0;
		param->out.y = 0;
		param->out.w = pVtv->output_width;
		param->out.h = pVtv->output_height;
	}
	param->panel.w = pVtg->win_info.panel.w;
	param->panel.h = pVtg->win_info.panel.h;

	return ret;
}

static int vt_get_ridx(unsigned int *p)
{
	int ret = 0;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;
	struct vtv_cap_info *pVtv = &fh_vt_priv->vtv_info;

	if(p==NULL) {DE_ERROR("p==NULL"); return -1;}
	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -2;}
	if(pVtv==NULL) {DE_ERROR("pVtv==NULL"); return -2;}

	if(fh_vt_priv->vt_target<2) {
		ret = _get_vtg_info();
		*p  = pVtg->r_idx + g_idx_offset;
		*p  = (*p)%5;
	}
	else {
		ret = _get_vtv_info();
		*p  = pVtv->r_idx;
	}

	return ret;
}

static int vt_get_plane_info(unsigned int win_id, \
	struct v4l2_ext_capture_plane_info *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg;
	struct vtv_cap_info *pVtv;

	if(fh_vt_priv->vt_target<2){

		if(param==NULL) {DE_ERROR("p==NULL"); return -1;}
		pVtg = &fh_vt_priv->vtg_info;
		if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -2;}

		// get plane_info from firmware
		ret = _get_vtg_info();

		param->stride = pVtg->plane_info.stride;
		param->plane_region.x = pVtg->plane_info.plane_region.x;
		param->plane_region.y = pVtg->plane_info.plane_region.y;
		param->plane_region.w = pVtg->plane_info.plane_region.w;
		param->plane_region.h = pVtg->plane_info.plane_region.h;

		param->active_region.x = pVtg->plane_info.active_region.x;
		param->active_region.y = pVtg->plane_info.active_region.y;
		param->active_region.w = pVtg->plane_info.active_region.w;
		param->active_region.h = pVtg->plane_info.active_region.h;
	}
	else {
		VTV_INFO_T *p_m2a;
		pVtv = &fh_vt_priv->vtv_info;
		if(pVtv==NULL) {DE_ERROR("pVtv==NULL"); return -3;}
		p_m2a = (VTV_INFO_T *)pVtv->m2a;
		if(p_m2a==NULL) {DE_ERROR("p_m2a==NULL"); return -4;}

		param->stride = p_m2a->in_info[0].stride;
		param->plane_region.x = 0;
		param->plane_region.y = 0;
		param->plane_region.w = pVtv->input_width;
		param->plane_region.h = pVtv->input_height;

		param->active_region.x = 0;
		param->active_region.y = 0;
		param->active_region.w = p_m2a->in_info[0].width;
		param->active_region.h = p_m2a->in_info[0].height;
	}
	if(g_log_level < 2) {
		DE_NOTI("%s : stride[%d] out_region[%d/%d/%d/%d] act_region[%d/%d/%d/%d]\n",\
			__func__, param->stride,\
			param->plane_region.x,param->plane_region.y,\
			param->plane_region.w,param->plane_region.h,\
			param->active_region.x,param->active_region.y,\
			param->active_region.w,param->active_region.h);
	}
	return ret;
}

static int vt_get_plane_prop(unsigned int win_id, \
	struct v4l2_ext_capture_plane_prop *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg;
	struct vtv_cap_info *pVtv;
	VTG_INFO_T *p_m2a;

	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}

	if(fh_vt_priv->vt_target<2){
		pVtg = &fh_vt_priv->vtg_info;
		if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -2;}

		p_m2a = pVtg->m2a;

		//msleep(100);  // wait valid buffer address  (temporal code - add check code from firmware)

		// get plane_prop from firmware
		ret = _get_vtg_info();

		param->l = pVtg->plane_prop.l;
		param->plane.x = pVtg->plane_prop.plane.x;
		param->plane.y = pVtg->plane_prop.plane.y;
		param->plane.w = pVtg->plane_prop.plane.w;
		param->plane.h = pVtg->plane_prop.plane.h;
		param->buf_count = pVtg->plane_prop.buf_count;
	}
	else {
		pVtv = &fh_vt_priv->vtv_info;
		if(pVtv==NULL) {DE_ERROR("pVtv==NULL"); return -3;}

		param->l = 0;
		param->plane.x = param->plane.y = 0;
		param->plane.w = pVtv->input_width;
		param->plane.h = pVtv->input_height;
		param->buf_count = pVtv->input_buf_count;
	}
	return ret;
}

static int vt_get_freeze_mode(unsigned int win_id, \
	struct v4l2_ext_capture_freeze_mode *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg;

	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}
	pVtg = &fh_vt_priv->vtg_info;
	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

	// get freeze_mode from firmware
	ret = _get_vtg_info();

	param->val = pVtg->freeze.val;
	param->plane_index = pVtg->freeze.plane_index;

	return ret;
}

static int vivt_set_plane_property(unsigned int win_id, \
	struct v4l2_ext_capture_plane_prop *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg;
	int count = 3;

	{
		if(fh_vivt_priv==NULL) { DE_ERROR("***fh_vivt_priv==NULL"); return -1;}
		pVtg = &fh_vivt_priv->vtg_info;
		if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

		pVtg->plane_prop.l = param->l;
		pVtg->plane_prop.plane.x = param->plane.x;
		pVtg->plane_prop.plane.y = param->plane.y;
		pVtg->plane_prop.plane.w = param->plane.w;
		pVtg->plane_prop.plane.h = param->plane.h;
		pVtg->plane_prop.buf_count = param->buf_count;

		pVtg->use_ext_buf = 0;

		ret = _set_vivt_vtg_info();
	}
	do{
		de_sync_wait(SYNC_WAIT_WEL); // wait interrupt
		//msleep(40);  // wait valid buffer address  (temporal code - add check code from firmware)

		ret = _get_vivt_vtg_info();
		if(ret) DE_ERROR("_get_vtg_info error");
		if(pVtg->w_out.w == param->plane.w)
			break;
	}while(count--);

	DE_NOTI("loc[%d] w/h[%d/%d] buf_count[%d] - timeout_rem[%d] @%s 2311",\
		param->l, param->plane.w, param->plane.h, param->buf_count, count,\
		(fh_vivt_priv->vt_target==2)?"VTV":"VTG");

	return ret;
}

static int vt_set_plane_property(unsigned int win_id, \
	struct v4l2_ext_capture_plane_prop *param)
{
	int ret = 0;
	UINT32 param_l;
	struct vtg_cap_info *pVtg;
	struct vtv_cap_info *pVtv;
	int count = 3;//10; // 300msec timeout
	enum vsc_feedback_position pos = FB_NONE;
	kwrap_vp_timing_info_t ti;

	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}

	if (lx_board_opt() & LX_BOARD_OPT_EXT_FRC) {
		if(param->l == V4L2_EXT_CAPTURE_BLENDED_OUTPUT) { //SCDCR-5451
			DE_ERROR("8k model + BLENDED_OUTPUT: not supported");
			return -EOPNOTSUPP;
		}
	}

	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		if(param->l == V4L2_EXT_CAPTURE_SCALER_INPUT) {
			DE_ERROR("M23 VTV : not supported");
			return -EOPNOTSUPP;
		}
	}

	// https://alm-lge-hlm.singlex.com/polarion/#/project/TVwebOS24RelProjMgmt/workitem?id=TVWBS_24-52792  ==> TVPM-25705
	vsc_get_timinginfo(0, &ti);
	if(param->l == V4L2_EXT_CAPTURE_DISPLAY_OUTPUT && \
		param->buf_count == 3 && \
		(param->plane.w == 3840 || param->plane.h == 2160) && \
		(ti.hActive > 4096 || ti.vActive > 3840)) {
		//(ti.isMVI == 0)) {
		DE_ERROR("8k input + 4k display capture, buf_num==3 : not supported");
		return -EOPNOTSUPP;
	}
	// set location info to vsc (for miracast-tx)
	param_l = param->l;
	switch(param_l) {
		case V4L2_EXT_CAPTURE_SCALER_OUTPUT: // source
			pos = FB_WITHOUT_OSD; break;
		case V4L2_EXT_CAPTURE_DISPLAY_OUTPUT: // display(no blending)
			pos = FB_DISP; break;
		case V4L2_EXT_CAPTURE_BLENDED_OUTPUT:
			pos = FB_WITH_OSD; break;
		case V4L2_EXT_CAPTURE_OSD_OUTPUT:
			pos = FB_OSD_ONLY; break;
		case V4L2_EXT_CAPTURE_OSD_OUTPUT+1:
			pos = FB_HIST; break;
		default:
			pos = FB_NONE; break;
	}
	ret = vsc_set_fbpos(pos);

	if(/*pos > FB_WITHOUT_OSD &&*/ param->buf_count == 0) {
		_set_vtg_run(0, 0); //disable capture
		pVtg = &fh_vt_priv->vtg_info;
		if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}
		pVtg->plane_prop.l = param->l;
		pVtg->plane_prop.plane.x = param->plane.x;
		pVtg->plane_prop.plane.y = param->plane.y;
		pVtg->plane_prop.plane.w = param->plane.w;
		pVtg->plane_prop.plane.h = param->plane.h;
		pVtg->plane_prop.buf_count = param->buf_count;
		DE_NOTI("use display feedback for miracast-tx. pos[%d](0:none(ATVRec),1:wo/OSD,2:w/OSD,3:OSD", pos);
		return 0;
	}

	fh_vt_priv->vt_target = (param->l==V4L2_EXT_CAPTURE_SCALER_INPUT)?2:1;
	if(param->l > (V4L2_EXT_CAPTURE_OSD_OUTPUT + 2)) fh_vt_priv->vt_target = 0xF;

	if(fh_vt_priv->vt_target<2){
		unsigned int w;
		unsigned int tot;
		pVtg = &fh_vt_priv->vtg_info;
		if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}

		w = param->plane.w;
		if(ALIGN_X(w,16) != w) {
			DE_ERROR("not supported width[%d]", w);
			return -EOPNOTSUPP;
		}

		pVtg->plane_prop.l = param->l;
		pVtg->plane_prop.plane.x = param->plane.x;
		pVtg->plane_prop.plane.y = param->plane.y;
		pVtg->plane_prop.plane.w = param->plane.w;
		pVtg->plane_prop.plane.h = param->plane.h;
		pVtg->plane_prop.buf_count = param->buf_count;

		tot = param->plane.w * param->plane.h * param->buf_count;
		if(tot > 3840 * 2160 * 1) { // over than ext_buffer_size
			pVtg->use_ext_buf	= 1;
			if(pVtg->ext8k_frc == 1) { // alloc ext buffer (O22+F22 only)
				unsigned int c = 6;
				ret = DE_IO_SetSharedMem((unsigned long)&c);
			}
		}
		else
			pVtg->use_ext_buf = 0;

		// set plane property
		if(ret) {
			DE_ERROR("alloc error");
		}
		else {
			ret = _set_vtg_info();
		}
	}
	else {
		pVtv = &fh_vt_priv->vtv_info;
		if(pVtv==NULL) {DE_ERROR("pVtv==NULL"); return -1;}

		pVtv->input_width   = param->plane.w;
		pVtv->input_height  = param->plane.h;
		pVtv->output_width  = 1920;
		pVtv->output_height = 1080;
		pVtv->input_buf_count = param->buf_count;

		// set property
		ret = _set_vtv_info();
		if(ret) DE_ERROR("error");
		ret = _set_vtv_run(4, pVtv->shared_mem);

		count = 2;
	}
	if(ret) DE_ERROR("error ret[%d]", ret);
	//
	do{
		if(fh_vt_priv->vt_target<2) {
			de_sync_wait(SYNC_WAIT_WEL); // wait interrupt
			//msleep(40);  // wait valid buffer address  (temporal code - add check code from firmware)

			ret = _get_vtg_info();
			if(ret) DE_ERROR("_get_vtg_info error");
			if(pVtg->w_out.w == param->plane.w)
				break;
		}
		else {
			de_sync_wait(SYNC_WAIT_USB);
			ret = _get_vtv_info();
			if(pVtv->in_info.stride)
			{
				DE_NOTI("stride = %d", pVtv->in_info.stride);
				DE_NOTI("Y[0x%08x] C[0x%08x]", pVtv->in_buf[0].y_frame, pVtv->in_buf[0].c_frame);
				break;
			}
		}
	}while(count--);
	//if(!count)DE_ERROR("timeout");

	DE_NOTI("loc[%d] w/h[%d/%d] buf_count[%d] - timeout_rem[%d] @%s 2311",\
		param->l, param->plane.w, param->plane.h, param->buf_count, count,\
		(fh_vt_priv->vt_target==2)?"VTV":"VTG");

	return ret;
}

static int vt_get_buffer_phys_info(unsigned int win_id, \
	struct capture_buffer_property *param)
{
	struct vtg_cap_info *p = &fh_vt_priv->vtg_info;
	VTG_INFO_T *p_m2a = p->m2a;
	VTG_INFO_T *p_a2m = p->a2m;

//	msleep(100);  // wait valid buffer address  (temporal code - add check code from firmware)

	param->stride = p_m2a->stride;
	param->width = p_a2m->w_out_size.w;
	param->height = p_a2m->w_out_size.h;
	param->phys_y[0] = p_m2a->y_frame[0];
	param->phys_y[1] = p_m2a->y_frame[1];
	param->phys_y[2] = p_m2a->y_frame[2];
	param->phys_y[3] = p_m2a->y_frame[3];
	param->phys_y[4] = p_m2a->y_frame[4];
	param->phys_c[0] = p_m2a->c_frame[0];
	param->phys_c[1] = p_m2a->c_frame[1];
	param->phys_c[2] = p_m2a->c_frame[2];
	param->phys_c[3] = p_m2a->c_frame[3];
	param->phys_c[4] = p_m2a->c_frame[4];

	DE_NOTI("Y : 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x", \
		param->phys_y[0], param->phys_y[1], param->phys_y[2], param->phys_y[3], param->phys_y[4]);
	DE_NOTI("C : 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x", \
		param->phys_c[0], param->phys_c[1], param->phys_c[2], param->phys_c[3], param->phys_c[4]);

	return 0;
}

static int vivt_get_buffer_address(int in_out, int idx, unsigned int *y, unsigned int *c)
{
	struct vtg_cap_info *p_vtg;
	VTG_INFO_T *p_vtg_m2a;
	unsigned int stride = 0;
	int count = 30;

	if(fh_vivt_priv==NULL) {DE_ERROR("***fh_vivt_priv==NULL"); return -1;}
	p_vtg = &fh_vivt_priv->vtg_info;
	if(p_vtg==NULL) {DE_ERROR("***p_vtg==NULL"); return -1;}
	p_vtg_m2a = p_vtg->m2a;

	stride = p_vtg_m2a->stride;
	*y = p_vtg_m2a->y_frame[idx];
	*c = p_vtg_m2a->c_frame[idx];

	//DE_NOTI("[%d] %s  Y : 0x%08x , C : 0x%08x , s[%d] count[%d]", \
	//	idx, (in_out==0)?"IN":"OUT", *y, *c, stride, count);

	return 0;
}

static int vt_get_buffer_address(int in_out, int idx, unsigned int *y, unsigned int *c)
{
	struct vtg_cap_info *p_vtg = &fh_vt_priv->vtg_info;
	struct vtv_cap_info *p_vtv = &fh_vt_priv->vtv_info;
	unsigned int stride = 0;
	int count = 30;

	VTG_INFO_T *p_vtg_m2a = p_vtg->m2a;
	//VTG_INFO_T *p_vtg_a2m = p_vtg->a2m;
	VTV_INFO_T *p_vtv_m2a = p_vtv->m2a;
	//VTV_INFO_T *p_vtv_a2m = p_vtv->a2m;

	if(idx>5) {DE_ERROR("invalid index %d", idx); return -1;}

	//msleep(100);  // wait valid buffer address  (temporal code - add check code from firmware)
	do {
		if(fh_vt_priv->vt_target<2) {
			stride = p_vtg_m2a->stride;
		}
		else {
			if(in_out) {
				//stride = p_vtv_m2a->out_info[0].stride;
				stride = p_vtv_m2a->out_buf[0].y_frame;
			}
			else
				stride = p_vtv_m2a->in_info[0].stride;
		}
		if(stride > 0) break;		
		msleep(10);
	} while(count--);

	if(fh_vt_priv->vt_target<2) {
		*y = p_vtg_m2a->y_frame[idx];
		*c = p_vtg_m2a->c_frame[idx];
	}
	else {
		if(in_out) { // vtv out buffer
			*y = p_vtv_m2a->out_buf[idx].y_frame;
			*c = p_vtv_m2a->out_buf[idx].c_frame;
			stride = p_vtv_m2a->out_info[0].stride;
		}
		else {
			*y = p_vtv_m2a->in_buf[idx].y_frame;
			*c = p_vtv_m2a->in_buf[idx].c_frame;
		}
	}

	DE_NOTI("[%d] %s  Y : 0x%08x , C : 0x%08x , s[%d] count[%d]", \
		idx, (in_out==0)?"IN":"OUT", *y, *c, stride, count);

	return 0;
}

static int vt_set_freeze(unsigned int win_id, \
	struct v4l2_ext_capture_freeze_mode *param)
{
	int ret = 0;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;

	if(param==NULL) {DE_ERROR("p==NULL"); return -1;}
	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -2;}

	pVtg->freeze.val = param->val;
	pVtg->freeze.plane_index = param->plane_index;

	// set freeze
	if(fh_vt_priv->vt_target<2)
		ret = _set_vtg_info();

	return ret;
}

static int vt_set_divide_rate(BOOLEAN flag, unsigned int win_id, unsigned int *param)
{
/* SCDCR-3406
	divide 0: sourceFPS/1 (origin)
	divide 1: sourceFPS/1 (origin)
	divide 2: sourceFPS/2
	divide 3: sourceFPS/3
*/
	int ret = 0;
	LX_DE_FW_STATUS_REG_T fw_status;
	int max_divide = 60;
	//kwrap_vp_timing_info_t ti;
	unsigned int disp_fr;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;
	if(pVtg==NULL) {DE_ERROR("pVtg==NULL"); return -1;}
	if(*param>max_divide) {
		DE_ERROR("divide[%d] is over %d", *param, max_divide);
		return -1;
	}

	if(flag)
	{
		ipc_phys_hal_CheckFwStatus(0, (void *)&fw_status);
		disp_fr = fw_status.reg_1.frate_out;

		if(pVtg->plane_prop.l == V4L2_EXT_CAPTURE_SCALER_OUTPUT) { // source capture
			if(*param <= 1)
				pVtg->rate = 0;
			else {
				if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
					pVtg->rate = *param - 1;
				}
				else {
					/*vsc_get_timinginfo(0, &ti);
					if(ti.vFreq >= 96) {
						pVtg->rate = *param - 2;
					}
					else*/
					{
						if(*param==2) *param = 1;
						pVtg->rate = *param;
					}
				}
			}
		}
		else if( pVtg->plane_prop.l == V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT ) {
			if(*param <= 1)
				pVtg->rate = 0;
			else {
				if(*param==2) *param = 1;
				pVtg->rate = *param;
			}
		}
		else { // display capture
			if(disp_fr >= 96) { // out frame rate : 100/120Hz
				if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
					pVtg->rate = *param + 1;
				}
				else {
					pVtg->rate = *param;
				}
			}
			else { // out frame rate : 50/60Hz
				if(*param <= 1)
					pVtg->rate = 0;
				else
					pVtg->rate = *param - 1;
			}
		}
		if(fh_vt_priv->vt_target<2)
			ret = _set_vtg_info();
	}
	else
	{
		*param = pVtg->rate;
	}
	/*if(g_log_level < 2)*/ DE_NOTI("%s loc[%d] rate[%d] fw[%d] disp_fr[%d]", \
		flag?"Set":"Get", pVtg->plane_prop.l, *param, pVtg->rate, disp_fr);
	return ret;
}

static int vt_get_output_rate(BOOLEAN flag, unsigned int win_id, unsigned int *param)
{
	int ret = 0;
	LX_DE_FW_STATUS_REG_T fw_status;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;
	kwrap_vp_timing_info_t ti;
	unsigned int disp_fr;
	UINT8 win;

	if(param==NULL) {DE_ERROR("param==NULL"); return -1;}

	if(flag) {

	}
	else {
		ipc_phys_hal_CheckFwStatus(0, (void *)&fw_status); // get out frame rate
		disp_fr = fw_status.reg_1.frate_out;

		if(pVtg->plane_prop.l == V4L2_EXT_CAPTURE_SCALER_OUTPUT || pVtg->plane_prop.l == V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT ) // source & subpath capture
		{
			if(pVtg->plane_prop.l == V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT)
				win = 1; // sub source capture 
			else
				win = 0; // main source capture
			vsc_get_timinginfo(win, &ti);
			if(disp_fr >= 96) { // out frame rate : 100/120Hz
				*param = ti.vFreq/10;
				//if ( lx_chip_rev() < LX_CHIP_REV(E60,A0) ) { // O20
				if (LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) { // O20, O22(20210601 modified)
					if(*param >= 96)
						*param = (*param) >> 1;
				}
			}
			else { // out frame rate : 50/60Hz
				*param = ti.vFreq/10;
				if(*param >= 96)
					*param = *param >> 1;
			}
		}
		else { // display capture
			if(disp_fr >= 96) // out frame rate : 100/120Hz
				*param = disp_fr >> 1;
			else // out frame rate : 50/60Hz
				*param = disp_fr;
			if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
				vsc_get_timinginfo(0, &ti);
				if(pVtg->plane_prop.buf_count==5 && fh_vt_priv->vtg_info.ext8k_frc == 1) // 8k model, 4k 5buf : youtube vr360
				{
					if(pVtg->plane_prop.plane.w > 1920 && pVtg->plane_prop.plane.h > 1080)
					*param = ti.vFreq;
				}
			}
		}
	}
	//if(g_log_level == 3)
	DE_NOTI("loc[%d] vt_fr[%d] disp_fr[%d]", \
		pVtg->plane_prop.l, *param, disp_fr);
	return ret;
}
unsigned int g_wIdx = 0;
unsigned int t_idx_msec_prv;

static int vt_set_out_buffer_index(BOOLEAN flag, unsigned int *param)
{
	int ret = 0;
	struct vtv_cap_info *pVtv = &fh_vt_priv->vtv_info;
	VTV_INFO_T *p_out = (VTV_INFO_T *)pVtv->a2m;
	VTV_INFO_T *p_in  = (VTV_INFO_T *)pVtv->m2a;
	int curr, diff;
	ktime_t 	   t;
	struct timespec64 ts;

	if(param==NULL) {DE_ERROR("param==NULL"); return -1;}
	if(*param > 2)  {DE_ERROR("invalid idx[%d]", *param); return -2;}
	if(p_out==NULL) {DE_ERROR("p_out==NULL"); return -3;}
	if(p_in==NULL)  {DE_ERROR("p_in==NULL"); return -4;}

	t  = ktime_get_real();
	ts = ktime_to_timespec64(t);
	curr = ts.tv_nsec/1000000;
	if(t_idx_msec_prv < curr)
		diff =  curr - t_idx_msec_prv;
	else
		diff = (1000-t_idx_msec_prv)+ curr;
	if(flag) {
		unsigned int val= *param;
		val = val + g_wIdx;
		if(val>2) val = val%3;
		p_out->r_idx        = val;

		DE_NOTI("%d=> %d, +offset %d :  %d msec", *param,val, g_wIdx, diff);
		p_out->pqe_meta_idx = p_in->pqe_meta_idx;
	}
	else {
		*param = p_out->r_idx;
	}
	t_idx_msec_prv = curr;

	return ret;
}

static int vt_set_win_info(unsigned int win_id, struct v4l2_ext_capture_video_win_info *param)
{
	int ret = 0;
	struct vtv_cap_info *pVtv = &fh_vt_priv->vtv_info;

	if(pVtv==NULL)  {DE_ERROR("pVtv==NULL"); return -1;}
	if(param==NULL) {DE_ERROR("param==NULL"); return -2;}

	pVtv->output_width  = param->out.w;
	pVtv->output_height = param->out.h;

	// set property
	ret = _set_vtv_info();

	return ret;
}

static int vt_set_hist_preset(unsigned int preset)
{
	int ret = 0;
	g_vt_hist_preset = preset;
	return ret;
}

int g_histogram_count = 0;

int proc_capture(int cmd, int w, int h, unsigned int *v, unsigned int *p)
{
	struct v4l2_ext_capture_plane_prop param;
	unsigned int shared_mem_addr;
	struct vt_priv *priv;
	struct vtg_cap_info *pVtg = &fh_vt_priv->vtg_info;
	char start[] = "start";
	char stop[] = "stop";
	char preset[] = "preset";
	char *s;

	switch(cmd)
	{
		case 0:

			// get shared memory from DE_IO
			// and vmap_phys
			p = (unsigned int *)new_vt_priv();
			init_vt_dev((struct vt_priv *)p);

			param.plane.x = 0;
			param.plane.y = 0;
			param.plane.w = w;
			param.plane.h = h;
			param.buf_count = 3;
			param.l = 3;
			vt_set_plane_property(0, &param);
			break;
		case 1: // force svp
			test_cmd = w;
			break;
		case 2: // divide control
			vt_set_divide_rate(1, 0, &w);
			break;
		case 3: // GET CMD & PRESET
			*v = g_vt_hist_cmd;
			*p = g_vt_hist_preset;

			if(g_vt_hist_cmd == 1) { //start
				s = start;
			}
			else if(g_vt_hist_cmd == 2) {//stop
				s = stop;
				g_histogram_count = 0;
				msleep(5);
			}
			else if(g_vt_hist_cmd == 3) // preset
				{s = preset;}
			else {
				s = "defaut";
				g_histogram_count++;
			}
#if 1
			if(g_vt_hist_cmd == 1 || g_vt_hist_cmd == 3)
			{
				if(vsc_get_dev_info(0, 34))
					OS_UsecDelay(9000);
				else {
					if(g_histogram_count < 100)
						OS_UsecDelay(1000);
					else if((g_histogram_count > 100) && (g_histogram_count < 700) && (g_histogram_count%2)){
						// do not waiting
					}
				else
						msleep_interruptible(70);
				}

				g_histogram_count++;

				if(g_histogram_count > 1000)
					g_histogram_count = 50;
			}
#endif
			if(g_vt_hist_cmd != 2)
				DE_NOTI("vt_hist_cmd [%d] get param v[%d], p[%d] [%s] c[%d]", cmd, *v, *p, s, g_histogram_count);
			break;
		case 4 : 
			g_log_level = w;
			break;
		case 5: // SET CMD & PRESET  
			//DE_NOTI("cmd [%d] set param v[%d], p[%d]", cmd, *v, *p);
			g_vt_hist_cmd = *v;
			g_vt_hist_preset = *p;
			break;
		case 6:
			vt_get_output_rate(0, 0, &w);
			break;
		case 7:
			g_wIdx = w;
			break;
		default:
			break;
	}
	return 0;
}

static void vt_capture_notification(UINT32 event_type, struct vt_dev *dev, int index)
{
	struct v4l2_event cap_event;

	memset(&cap_event, 0, sizeof(cap_event));
	cap_event.type 			= event_type;
	cap_event.u.data[0]	= index;

	v4l2_event_queue(&dev->v4l2_vt_video_dev, &cap_event);
}

int v4l2_vt_pm_runtime_test(char* command)
{
	int ret = 0;
	//struct vt_dev *drv = platform_get_drvdata(&v4l2_vt_pdev);

	DE_NOTI("%s", command);

	if (!strncasecmp(command, "vt_runtime_suspend", strlen("vt_runtime_suspend"))) {
		while (atomic_read(&v4l2_vt_pdev.dev.power.usage_count) > 0) {
			DE_NOTI("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_vt_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_vt_pdev.dev);
		}
	}
	else if (!strncasecmp(command, "vt_runtime_resume", strlen("vt_runtime_resume"))) {
		while (atomic_read(&v4l2_vt_pdev.dev.power.usage_count) <= 0) {
			DE_NOTI("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_vt_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_vt_pdev.dev);
		}
	}
	else {
		DE_NOTI("do nothing\n");
	}

	return ret;
}

