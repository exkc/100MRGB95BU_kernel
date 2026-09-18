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
 *  @author		mujahatulla.shaik
 *  @version	1.0
 *  @date		2018-11-15
 *  @note		Additional information.
 *  @modifier	harish.singh@lge.com
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
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
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <uapi/linux/sched/types.h>
#endif
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include <media/videobuf2-vmalloc.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "base_device.h"
#include "vb2_gen_memop.h"
#include "de_def.h"
#include "de_io.h"
#include "gps_if.h"
#include "v4l2_gps.h"
#include "v4l2_gps_dbg.h"
#include "de_sync.h"

#ifdef WQ_IMPL
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#endif

//#define FORCE_TEST_SVP

#ifndef V4L2_CID_EXT_GPSCALER_SECURE_MODE
#define V4L2_CID_EXT_GPSCALER_SECURE_MODE (V4L2_CID_USER_EXT_GPSCALER_BASE + 7)
#endif

/* SCDCR-4006 */
#define GPS_PM_INFO(_level,_type,_result,_num)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::gps%d\n",\
			_level,"video",V4L2_EXT_DEV_NO_GPS,_g_v4l2_gps_open_count,\
			current->group_leader->comm,current->comm,_type,_result,_num);\
	} while(0)

char *capture_mem_str[5];
int instance_svp_info = 0;

#define get_gps_mem_pool_yplane()  capture_mem_str[0]
#define get_gps_mem_pool_cplane()  capture_mem_str[1]
#define get_gps_mem_pool_argbplane()  capture_mem_str[2]

static struct vb2_ops gps_cap_qops;
static unsigned int drop_count[MAX_CAPTURE_DEVS];

int g_gps_log_level = 1;
LX_DE_GPS_CTRL_T *g_dbg_pgps_ctx[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
static int _g_v4l2_gps_open_count = 0;
int g_gps_lock_mask[3] = { 0 };

struct gps_priv *new_gps_priv(void);
void add_vb2_queue_mapping(struct video_device *vdev, struct file_vb2_q *file_q);
struct file_vb2_q *delete_vb2_queue_mapping(struct video_device *vdev, struct file *filp);
int v4l2_gps_mmap(struct file *file, struct vm_area_struct *vma);
struct pixel_format_info *find_gps_format(struct pixel_format_info *fmt_array, 
		        int size, __u32 pixelformat, int *index);
int _gps_ioctl_reqbufs(struct file *file, struct vb2_queue *queue,
			  struct v4l2_requestbuffers *p);
int v4l2_gps_vidioc_create_bufs(struct file *file, void *priv,
			  struct v4l2_create_buffers *p);
int v4l2_gps_vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i);
int v4l2_gps_vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i);
int proc_gps_get_frame_drop(unsigned int id, unsigned int *count);
int proc_gps(int cmd, int p1, int p2, int p3, int p4, int p5);
int v4l2_gps_pm_runtime_test(char* command);

static void __freeFrmBuffer(struct gps_priv *pvt,int bufCnt, int planeCnt);
static inline bool is_queue_busy(struct video_device *vdev, struct file *file)
{
    struct vb2_queue *queue = lookup_vb2_queue(vdev, file);

    return queue->owner && queue->owner != file->private_data;
}

static inline struct gps_priv *file_prvdata(struct file *file) 
{
        return ((struct gps_fh *)(file->private_data))->gps_priv;
}

static inline struct gps_cap_buffer *to_gps_cap_buffer(struct vb2_buffer *vb2)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	return container_of(vbuf, struct gps_cap_buffer, vb);
}

static inline struct file_vb2_q *to_file_vb2_q(struct vb2_queue *vq)
{
	return container_of(vq, struct file_vb2_q, queue);
}

static void process_poll(struct gps_priv *p)
{
	//queue_work(system_wq, &p->vt_noti_work);
}

#if 0
static int _gps_setCtx(struct gps_priv *pvt, struct vb2_queue  *queue)
{
    unsigned int buffer;
    int plane;
	LX_DE_GPS_CTRL_T *pgps_ctx = NULL;
	char *mem_pool = NULL;

	pgps_ctx = &pvt->gps_info.gps_ctx;
    for (buffer = 0; buffer < queue->num_buffers; ++buffer) {
        for (plane = 0; plane < queue->bufs[buffer]->num_planes; ++plane) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
            unsigned long size = PAGE_ALIGN(queue->bufs[buffer]->planes[plane].length);
#else
            unsigned long size = PAGE_ALIGN(queue->plane_sizes[plane]);
#endif

            if (plane == 0) {
                pgps_ctx->buffer_addr_y[buffer] = __allocFrmBuffer(plane, size, &mem_pool);
				if (pgps_ctx->buffer_addr_y[buffer] == 0)
					return -1;
            } else {
                pgps_ctx->buffer_addr_c[buffer] = __allocFrmBuffer(plane, size,&mem_pool);
				if (pgps_ctx->buffer_addr_c == 0)
					return -1;
            }

			pvt->mem_pool[buffer][plane] = mem_pool;
			GPS_NOTI("Buffer [%d] Size [%d] plane [%d] allocated [0x%x]",buffer,size,plane,pgps_ctx->buffer_addr_y[buffer]);
        }
    }

	return 0;
}
#endif
static int gps_set_svp_info(int flag)
{
	instance_svp_info = flag;
	return 0;
}

static int v4l2_gps_alloc_memory(struct vb2_queue *queue, struct gps_priv *pvt, int count)
{
	int bufCnt   = 0;
	int planeCnt = 0;
    struct vb2_plane *plane  = NULL;
    struct vb2_gen_buf *buf;
	LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	GPS_NOTI("num_buffers: %d\n",  vb2_get_num_buffers(queue));
#else
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	while (bufCnt < vb2_get_num_buffers(queue)) {
#else
	while (bufCnt < queue->num_buffers) {
#endif
		GPS_NOTI("buf_no: %d, num_planes: %d\n", bufCnt, queue->bufs[bufCnt]->num_planes);
		planeCnt = 0;
		while (planeCnt < queue->bufs[bufCnt]->num_planes) {
			plane = (struct vb2_plane *) &(queue->bufs[bufCnt]->planes[planeCnt]);
			buf   = (struct vb2_gen_buf *) plane->mem_priv;
			if(planeCnt == 0)
				pgps_ctx->buffer_addr_y[bufCnt] = buf->phyAddr;
			else
				pgps_ctx->buffer_addr_c[bufCnt] = buf->phyAddr;
			planeCnt++;
		}

		bufCnt++;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	pvt->gps_cap_fmt.num_buf    = vb2_get_num_buffers(queue);
#else
	pvt->gps_cap_fmt.num_buf    = queue->num_buffers;
#endif
	pvt->gps_cap_fmt.num_planes = queue->bufs[0]->num_planes;

	return 0;
}

struct gps_priv *new_gps_priv(void)
{
	struct gps_priv *p;
	//int rem = 0;

	p = kcalloc(1, sizeof(struct gps_priv), GFP_KERNEL);
	if (!p) {
		GPS_ERROR("Error: alloc error for gps priv.");
		return NULL;
	}

	spin_lock_init(&p->slock);
	INIT_LIST_HEAD(&p->vb_gps_cap_list);

#ifdef WQ_IMPL
	INIT_LIST_HEAD(&p->gps_work_list);
#endif

	p->cap_buffers = 0;

	/* 
	 * Initialize the default values 
	 */
	memset(&p->gps_info.gps_ctx, 0, sizeof(LX_DE_GPS_CTRL_T));

	p->gps_cap_fmt.max_width        = DEF_GPS_CAP_WIDTH;
	p->gps_cap_fmt.max_height       = DEF_GPS_CAP_HEIGHT;

	p->gps_cap_fmt.alloc_buf_width  = DEF_GPS_CAP_WIDTH;
	p->gps_cap_fmt.alloc_buf_height = DEF_GPS_CAP_HEIGHT;

	p->gps_info.gps_ctx.height      = DEF_GPS_CAP_HEIGHT;
	p->gps_info.gps_ctx.width       = DEF_GPS_CAP_WIDTH;

	p->gps_info.gps_ctx.vdec_id     = DEF_GPS_CAP_INPUT;

	p->gps_info.gps_ctx.gps_id  = DEF_GPS_CAP_INPUT;
	p->gps_info.gps_ctx.bbd_id  = -1;
	p->gps_info.gps_ctx.bbd_en  = 0;
	p->gps_info.gps_ctx.bbd_xw  = -1;
	p->gps_info.gps_ctx.bbd_yh  = -1;

	p->gps_cap_fmt.num_buf      = DEF_GPS_BUFS;
	p->gps_cap_fmt.num_planes   = DEF_GPS_PLANES;
	p->gps_cap_fmt.col_space    = DEF_GPS_CAP_COLORSPACE;
	p->gps_cap_fmt.field_order  = DEF_GPS_CAP_FIELD_ORDER;
	p->gps_cap_fmt.encoding.yCbCr_enc = DEF_GPS_CAP_COL_ENCODING;
	p->gps_cap_fmt.pixel_fmt    = V4L2_PIX_FMT_NV12M;
	p->gps_cap_fmt.quantization = DEF_GPS_CAP_QUATIZATION;
	p->gps_cap_fmt.xfer_fun     = DEF_GPS_CAP_XFER_FUN;

	p->cur_width       = 0;
	p->cur_height      = 0;
	p->adaptive_mode   = 0;
	p->change_ctx_size = 0;
	p->svp             = 0;
	p->attr            = 0; //0=V4L2_EXT_GPSC_SOURCE_ATTRIBUTE_TYPE_NONE

	//rem = p->gps_info.gps_ctx.width % LG_MEM_STRIDE_STEP;
	//p->gps_cap_fmt.stride = rem ? (p->gps_info.gps_ctx.width + (LG_MEM_STRIDE_STEP - rem)) : p->gps_info.gps_ctx.width;
	p->gps_cap_fmt.stride = ALIGN_64(p->gps_info.gps_ctx.width);

	return p;
}

void add_vb2_queue_mapping(struct video_device *vdev, struct file_vb2_q *file_q)
{
    struct file_vb2_q   **fq = NULL;
    struct  vb2_queue   *q   = NULL;
	struct gps_dev *dev  = video_get_drvdata(vdev);
	rwlock_t *lock = NULL;

	lock = &dev->v4l2_gps_list_lock;
	if (lock) {
		write_lock(lock);
	}

	q = vdev->queue;
    fq = (struct file_vb2_q **) &(q->drv_priv);

    while (*fq) {
        fq = (struct file_vb2_q **) &((*fq)->queue.drv_priv);
    }

    *fq = file_q;

	if (lock) {
		write_unlock(lock);
	}
}

struct file_vb2_q *delete_vb2_queue_mapping(struct video_device *vdev, struct file *filp)
{
    struct file_vb2_q   **fq, *tmp_fq;
    struct  vb2_queue   *q      = NULL;
	struct gps_dev *dev  = video_get_drvdata(vdev);
	rwlock_t *lock = NULL;

	lock = &dev->v4l2_gps_list_lock;

	if (lock){
		write_lock(lock);
	}

	q = vdev->queue;
    fq = (struct file_vb2_q**) &(q->drv_priv);

    while (*fq) {
        if (filp == (*fq)->file){
            tmp_fq = *fq;
            *fq = (*fq)->queue.drv_priv;
            GPS_NOTI("returning queue::%p\n",tmp_fq);

			if (lock){
				write_unlock(lock);
			}

            return tmp_fq;
        }
        fq = (struct file_vb2_q **)&((*fq)->queue.drv_priv);
    }

	if (lock){
		write_unlock(lock);
	}

    GPS_NOTI("Instance not found\n");
    return NULL;
}

struct vb2_queue *lookup_vb2_queue(struct video_device *vdev, struct file *filp)
{
    struct file_vb2_q   **fq;
    struct vb2_queue    *q    = NULL;
	rwlock_t            *lock = NULL;
	struct gps_dev      *dev  = video_get_drvdata(vdev);

	lock = &dev->v4l2_gps_list_lock;
	if (lock) {
		read_lock(lock);
	}

	q  = vdev->queue;
    fq = (struct file_vb2_q **) &(q->drv_priv);

    while (*fq) {

        if (filp == (*fq)->file){
            if(lock){
				read_unlock(lock);
            }

            return &(*fq)->queue;
        }

        fq = (struct file_vb2_q **) &((*fq)->queue.drv_priv);
    }

	if (lock) {
		read_unlock(lock);
	}

    GPS_NOTI("Instance not found\n");
    return NULL;
}

static int v4l2_gps_init_vb2_queue(struct video_device *vdev, struct file *filp)
{
	int                 ret     = 0;
	struct file_vb2_q   *file_q = NULL;
	struct vb2_queue    *q;

	/* for linked list of vb2_queue */
	file_q = kmalloc(sizeof(struct file_vb2_q), GFP_KERNEL);
	if (!file_q) {
		GPS_ERROR("Error: allocation of file queue failed \n");
		ret = -ENOMEM;
		return ret;
	}

	memset(file_q, 0, sizeof(struct file_vb2_q));

	/* file pointer of opened device file descriptor */
	file_q->file = filp;

	/* vb2 queue pointer of opened device file descriptor */
	q = &file_q->queue;

	q->type               = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes           = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv           = NULL;
	q->buf_struct_size    = sizeof(struct gps_cap_buffer);
	q->ops                = &gps_cap_qops;
	q->mem_ops            = &vb2_gps_memops;
	q->timestamp_flags    = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	q->min_queued_buffers = 1;//MIN_GPS_BUF;
#else
	q->min_buffers_needed = MIN_GPS_BUF;
#endif
	mutex_init(&file_q->gps_vb2_queue_lock);
	q->lock = &file_q->gps_vb2_queue_lock;

	ret = vb2_queue_init(&file_q->queue);
	if (ret) {
		GPS_NOTI("Error: vb2_queue init error: %d\n", ret);
		goto fail_vb2;
	}

	/* add file and vb2 queue to internal mapping table */
	add_vb2_queue_mapping(vdev, file_q);

	return ret;

fail_vb2:
	kfree(file_q);

	return ret;
}


static int v4l2_gps_fh_open(struct file *filp)
{
	int                 ret     = 0;
	struct video_device *vdev   = video_devdata(filp);
	struct gps_priv     *p      = NULL;
	struct gps_fh       *fh     = NULL;
	struct gps_dev      *dev    = video_drvdata(filp);

	GPS_NOTI("%s", __func__);

	ret = pm_runtime_get_sync(&dev->pdev->dev);
	GPS_NOTI("%s : ret:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret,atomic_read(&dev->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct gps_fh), GFP_KERNEL);
	if (!fh) {
		GPS_ERROR("Error: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	p = new_gps_priv();
	if (!p) {
		GPS_ERROR("Error: alloc of gps priv failed");
		ret = -ENOMEM;
		goto fail_fh;
	}

	ret = v4l2_gps_init_vb2_queue(vdev, filp);
	if (ret) {
		GPS_NOTI("Error: vb2_queue init error: %d\n", ret);
		goto fail_fh;
	}

#ifdef WQ_IMPL
	INIT_WORK(&p->gps_noti_work, V4l2_gps_thread);
#endif
	p->process_poll = process_poll;
	p->gps_vdev     = vdev;
	p->filp         = filp;
	fh->gps_priv    = p;

	filp->private_data = fh;
	v4l2_fh_init(&fh->fh,vdev);
	v4l2_fh_add(&fh->fh);

	GPS_NOTI("index = %d, minor = %d", fh->fh.vdev->index, fh->fh.vdev->minor);

	//if(fh->fh.vdev->minor == V4L2_EXT_DEV_NO_GPS + 1)
	if(!strcmp(vdev->name, "ttv-capture-dev"))
	{
		LX_DE_GPS_CTRL_T *pgps_ctx = &p->gps_info.gps_ctx;
		pgps_ctx->vdec_id = 12;
		pgps_ctx->gps_id  = 12;
		pgps_ctx->bbd_id  = 12;
		drop_count[12]	  = 0;
		GPS_NOTI("open TTV device");
	}

	GPS_NOTI("Creating user control interface.....");
	ret = v4l2_gps_ctrls_create(p); 
	if (ret)
		goto error_fh;

	/* increment open counter */
	_g_v4l2_gps_open_count++;
	GPS_PM_INFO("info","open","ok",vdev->num);

	return ret;

error_fh:
	v4l2_gps_ctrls_delete(p);

fail_fh:
	kfree(fh);
	if(p) kfree(p);

	return ret;
}

static int v4l2_gps_fh_release(struct file *file)
{
	int ret = 0;
	struct file_vb2_q   *file_q = NULL;
	struct video_device *vdev   = video_devdata(file);
	struct vb2_queue   *queue   = lookup_vb2_queue(vdev,file);
	struct gps_fh       *fh     = file->private_data;
	struct gps_priv *pvt        = fh->gps_priv;
	LX_DE_GPS_CTRL_T *pgps_ctx  = NULL;
	struct gps_dev      *dev    = video_drvdata(file);

	if (queue){
        struct mutex *lock = queue->lock ? queue->lock : vdev->lock;

        if (lock)
            mutex_lock(lock);
        if (file->private_data == queue->owner) {
            vb2_queue_release(queue);
            queue->owner = NULL;
        }
        if (lock)
            mutex_unlock(lock);
	}

	file_q = delete_vb2_queue_mapping(vdev, file);
	if (file_q)
		kfree(file_q);

	/* Free mapped memory */
	if (pvt) {
		pgps_ctx = &pvt->gps_info.gps_ctx;

		GPS_NOTI("buf::[%d] plane::[%d]\n\n\n", pvt->gps_cap_fmt.num_buf, pvt->gps_cap_fmt.num_planes);

		if (pvt->gps_cap_fmt.num_buf) {
			__freeFrmBuffer(pvt, pvt->gps_cap_fmt.num_buf, pvt->gps_cap_fmt.num_planes);
		}

		if (pgps_ctx->vdec_id < 8) {
			g_dbg_pgps_ctx[pgps_ctx->vdec_id] = NULL;
			GPS_NOTI("gps: release g_dbg_pgps_ctx[%d]\n", pgps_ctx->vdec_id);
		}
	}

	if (fh) {
		v4l2_fh_del(&fh->fh);
		v4l2_fh_exit(&fh->fh);
		v4l2_gps_ctrls_delete(pvt);
		kfree(fh);
	}
	if(pvt)	
		kfree(pvt);
	ret = pm_runtime_put(&dev->pdev->dev);
	GPS_NOTI("gps: close. usage_count[%d]\n", atomic_read(&dev->pdev->dev.power.usage_count));

	/* decrement open counter */
	_g_v4l2_gps_open_count--;
	GPS_PM_INFO("info","close","ok",vdev->num);

	instance_svp_info = 0;

	return ret;
}

int v4l2_gps_mmap(struct file *file, struct vm_area_struct *vma)
{
    struct video_device *vdev = video_devdata(file);
    struct vb2_queue   *queue  = lookup_vb2_queue(vdev,file);

    return vb2_mmap(queue, vma);
}

static unsigned int v4l2_gps_poll(struct file *file, poll_table *wait)
{
    struct video_device *vdev = video_devdata(file);
    struct vb2_queue   *q  = lookup_vb2_queue(vdev,file);
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


static int v4l2_gps_probe(struct platform_device *pdev)
{
	int ret=0;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);
	GPS_NOTI("gps  %s\n", __func__);

	//KMN: Return value is garbage
	return ret;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_gps_remove(struct platform_device *pdev)
#else
static int v4l2_gps_remove(struct platform_device *pdev)
#endif
{
	VIDEO_HighPri_WQ_Delete(MODULE_GPS);

	pm_runtime_disable(&pdev->dev);
	GPS_NOTI("gps  %s\n", __func__);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_gps_resume(struct device *dev)
{
    GPS_NOTI("%s\n", __func__);
    return 0;
}

static int v4l2_gps_suspend(struct device *dev)
{
    GPS_NOTI("%s\n", __func__);
    return 0;
}

static int v4l2_gps_runtime_resume(struct device *dev)
{
	GPS_PM_INFO("info","resume","ok",V4L2_EXT_DEV_NO_GPS);
	return 0;
}

static int v4l2_gps_runtime_suspend(struct device *dev)
{
	GPS_PM_INFO("info","suspend","ok",V4L2_EXT_DEV_NO_GPS);
	return 0;
}

static int v4l2_gps_vidioc_querycap(struct file *file, void *hfile, struct v4l2_capability *cap)
{
	strncpy(cap->card, "v4l2_gps", sizeof(cap->card)-1);
	strncpy(cap->driver, "v4l2_gps", sizeof(cap->driver)-1);
	cap->bus_info[0]  = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps  = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	GPS_NOTI("Query cap: Success\n");

	return 0;
}

static int v4l2_gps_vidioc_enum_input(struct file *file, void *priv, struct v4l2_input *inp)
{
	struct gps_dev *dev  = video_drvdata(file);

    GPS_NOTI("%s: ",__func__);

    if (inp->index >= dev->num_inputs)
        return -EINVAL;

    inp->type = capture_devs[inp->index].type;
    inp->std  = capture_devs[inp->index].std;
    inp->capabilities = capture_devs[inp->index].capabilities;
    strcpy(inp->name, capture_devs[inp->index].name);

    return 0;
}

static int v4l2_gps_vidioc_s_input(struct file *file, void *priv, unsigned i)
{
    struct video_device *vdev  = video_devdata(file);
    struct gps_dev *dev        = video_drvdata(file);
    struct gps_priv *pvt       = file_prvdata(file);
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;

    GPS_NOTI("%s: ", __func__);

    if (vb2_is_busy(lookup_vb2_queue(vdev, file))) {
    	GPS_NOTI("Error: vb2 is busy");
        return -EBUSY;
	}

    if (i >= dev->num_inputs) {
    	GPS_NOTI("Error: exceeds number of inputs");
        return -EINVAL;
	}

    pgps_ctx->vdec_id = i;
    pgps_ctx->gps_id  = i;
    pgps_ctx->bbd_id  = i;
	drop_count[i]     = 0;

	if (pgps_ctx->vdec_id < 8) {
		g_dbg_pgps_ctx[pgps_ctx->vdec_id] = pgps_ctx;
		GPS_NOTI("gps: register g_dbg_pgps_ctx[%d]\n", pgps_ctx->vdec_id);
	}

    return 0;
}

static int v4l2_gps_vidioc_g_input(struct file *file, void *priv, unsigned int *i)
{
    struct gps_priv *pvt       = file_prvdata(file);
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;

    GPS_NOTI("%s: %d",__func__,pgps_ctx->vdec_id);

    *i = pgps_ctx->vdec_id;

    return 0;
}

static int v4l2_gps_vidioc_enum_fmt_vid(struct file *file, void *priv, struct v4l2_fmtdesc *f)
{
    struct pixel_format_info *fmt;

    GPS_NOTI("index:: [%d]", f->index);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    if (f->index >= ARRAY_SIZE(pixel_formats_mp)) {
	    return -EINVAL;
    }
    fmt = &pixel_formats_mp[f->index];
#else
    if (f->index >= ARRAY_SIZE(pixel_formats_sp)) {
	    return -EINVAL;
    }
    fmt = &pixel_formats_sp[f->index];
#endif

    strncpy(f->description, fmt->desc, sizeof(f->description) - 1);
    f->pixelformat = fmt->pixel_format;
    f->flags = V4L2_FMT_FLAG_COMPRESSED;

    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static int v4l2_gps_vidioc_enum_fmt_vid_mplane(struct file *file, void *priv,
				    struct v4l2_fmtdesc *f)
{
    struct pixel_format_info *fmt;

    GPS_NOTI("index:: [%d]", f->index);

    if (f->index >= ARRAY_SIZE(pixel_formats_mp)) {
        return -EINVAL;
    }

    fmt = &pixel_formats_mp[f->index];

    strncpy(f->description, fmt->desc, sizeof(f->description) - 1);
    f->pixelformat = fmt->pixel_format;
    f->flags = V4L2_FMT_FLAG_COMPRESSED;

    return 0;
}
#endif

struct pixel_format_info *find_gps_format(struct pixel_format_info *fmt_array, 
		        int size, __u32 pixelformat, int *index)
{
    struct pixel_format_info *fmt;
    int i;

    for (i = 0; i < size; ++i) {
        fmt = &fmt_array[i];
        if (fmt_array[i].pixel_format == pixelformat) {
			*index = i;
            return fmt;
        }
    }

	GPS_NOTI("find_gps_format(RGB): Invalide format\n");
    return NULL;
}

static int find_gps_framesize(struct pixel_format_info *fmt, __u32 index, struct v4l2_frmsizeenum *fsize)
{
    struct frame_size_info *frm_info = NULL;
    unsigned int idx ;

    if (index >= ARRAY_SIZE(fmt->frame_size_indexes)) {
        return -EINVAL;
    }

	idx = fmt->frame_size_indexes[index];

    frm_info    = &frame_sizes[idx];
    fsize->type = frm_info->type;

    if(fsize->type == V4L2_FRMSIZE_TYPE_DISCRETE) {
        fsize->discrete.width  = frm_info->size.disc_frm.width;
        fsize->discrete.height = frm_info->size.disc_frm.height;
    } else if(fsize->type == V4L2_FRMSIZE_TYPE_STEPWISE) {
        fsize->stepwise.max_width   = frm_info->size.step_frm.max_width;
        fsize->stepwise.max_height  = frm_info->size.step_frm.max_height;
        fsize->stepwise.step_width  = frm_info->size.step_frm.step_width;
        fsize->stepwise.step_height = frm_info->size.step_frm.step_height;
        fsize->stepwise.min_width   = frm_info->size.step_frm.min_width;
        fsize->stepwise.min_height  = frm_info->size.step_frm.min_height;
    } else {
        GPS_ERROR("invalid FRMSIZE_TYPE");
    }

    return 0;
}

static int __gps_video_try_format_mp(struct gps_priv *pvt,
                 struct v4l2_pix_format_mplane *mpix, struct pixel_format_info **fmtinfo)
{
    struct pixel_format_info *fmt = NULL;
	int index, i=0, stride = pvt->gps_cap_fmt.stride,found=0;

    fmt = find_gps_format(pixel_formats_mp, ARRAY_SIZE(pixel_formats_mp), mpix->pixelformat, &index);

	/* 1. If set format is not supported return the current format or default format
	 *    As requested http://clm.lge.com/issue/browse/AVTASK-338
	 * 2. Coverity issue:: 276334 fix
	 */
    if (!fmt) { 
		mpix->width       = pvt->gps_info.gps_ctx.width;
		mpix->height      = pvt->gps_info.gps_ctx.height;
		mpix->pixelformat = pixel_formats_mp[0].pixel_format;
    } else {
		/* Now only capture dimension is flexible in driver */
		for (i = 0; i < MAX_FRAME_SIZE_CNT; i++) {
			if(pixel_formats_mp[index].frame_size_indexes[i] == -1)
				break;
			if (frame_sizes[i].type == V4L2_FRMSIZE_TYPE_DISCRETE) {
				if (mpix->width == frame_sizes[i].size.disc_frm.width &&
					mpix->height == frame_sizes[i].size.disc_frm.height) {
					found = 1;
					break;
				}
			} else if(frame_sizes[i].type == V4L2_FRMSIZE_TYPE_STEPWISE) {
				if(mpix->width >= frame_sizes[i].size.step_frm.min_width &&
				   mpix->width <= frame_sizes[i].size.step_frm.max_width &&
				   mpix->height >= frame_sizes[i].size.step_frm.min_height &&
				   mpix->height <= frame_sizes[i].size.step_frm.max_height && 
				   !(mpix->width % frame_sizes[i].size.step_frm.step_width) && 
				   !(mpix->height % frame_sizes[i].size.step_frm.step_height)) {
					found = 1;
					break;
				}
			}
		}
	}

	/* We need to calculate stride for new width and height */
	if(found == 0) {
		mpix->width = pvt->gps_info.gps_ctx.width;
		mpix->height= pvt->gps_info.gps_ctx.height;
	}

	mpix->colorspace  = pvt->gps_cap_fmt.col_space;
	mpix->field 	  = pvt->gps_cap_fmt.field_order;

	switch (mpix->pixelformat) {
		case V4L2_PIX_FMT_ARGB32:
		case V4L2_PIX_FMT_ABGR32:
			mpix->num_planes = 1;
			pvt->gps_cap_fmt.num_planes = 1;
			stride = ALIGN_64(mpix->width * 4);
			mpix->plane_fmt[0].sizeimage    = stride * mpix->height;
			mpix->plane_fmt[0].bytesperline = stride;
			GPS_NOTI("Fmt: ARGB - num_planes: %d\n", mpix->num_planes);
			break;
		case V4L2_PIX_FMT_NV12M:
			mpix->num_planes = 2;
			pvt->gps_cap_fmt.num_planes = 2;
			stride = ALIGN_64(mpix->width);
			mpix->plane_fmt[0].sizeimage    = stride * mpix->height;
			mpix->plane_fmt[0].bytesperline = stride;
			mpix->plane_fmt[1].sizeimage    = mpix->plane_fmt[0].sizeimage >> 1;
			mpix->plane_fmt[1].bytesperline = stride;
			GPS_NOTI("Fmt: YUV - num_planes: %d\n", mpix->num_planes);
			break;
		default:
			GPS_ERROR("It must not come here");
	}

	mpix->ycbcr_enc    = pvt->gps_cap_fmt.encoding.yCbCr_enc;
	mpix->quantization = pvt->gps_cap_fmt.quantization;
	mpix->xfer_func    = pvt->gps_cap_fmt.xfer_fun;

    return stride;
}

/*
 * Single planar format 
 */
static int __gps_video_try_format_sp(struct gps_priv *pvt, struct v4l2_pix_format *pix, struct pixel_format_info **fmtinfo)
{
    struct pixel_format_info *fmt = NULL;
	int index;
	int i = 0; 
	int found = 0;
	int stride = pvt->gps_cap_fmt.stride;


    fmt = find_gps_format(pixel_formats_sp, ARRAY_SIZE(pixel_formats_sp), pix->pixelformat, &index);

	/* If set format is not supported return the current format or default format */
	/* As requested http://clm.lge.com/issue/browse/AVTASK-338
	    Coverity issue:: 276334 fix */

    if (!fmt) {
		pix->width       = pvt->gps_info.gps_ctx.width;
		pix->height      = pvt->gps_info.gps_ctx.height;
		pix->pixelformat = pixel_formats_sp[0].pixel_format;
    } else {/* Now only capture dimension is flexible in driver */
		for (i = 0; i < MAX_FRAME_SIZE_CNT; i++) {
			if (pixel_formats_sp[index].frame_size_indexes[i] == -1)
				break;
			if (frame_sizes[i].type == V4L2_FRMSIZE_TYPE_DISCRETE) {
				if (pix->width == frame_sizes[i].size.disc_frm.width &&
					pix->height == frame_sizes[i].size.disc_frm.height){
					found = 1;
					break;
				}
			} else if (frame_sizes[i].type == V4L2_FRMSIZE_TYPE_STEPWISE) {
				if (pix->width >= frame_sizes[i].size.step_frm.min_width &&
					pix->width <= frame_sizes[i].size.step_frm.max_width &&
					pix->height >= frame_sizes[i].size.step_frm.min_height &&
					pix->height <= frame_sizes[i].size.step_frm.max_height &&
					!(pix->width % frame_sizes[i].size.step_frm.step_width) &&
					!(pix->height % frame_sizes[i].size.step_frm.step_height)) {
					found = 1;
					break;
				}
			}
		}
	}

	if (found == 0) {
		pix->width = pvt->gps_info.gps_ctx.width;
		pix->height= pvt->gps_info.gps_ctx.height;
	}

	switch(pix->pixelformat){
	case V4L2_PIX_FMT_ARGB32:
	case V4L2_PIX_FMT_ABGR32:
		stride = ALIGN_64(pix->width * 4);
		break;
	default:
		GPS_ERROR("Must not come here!!!");
		break;
	}

	pix->colorspace   = pvt->gps_cap_fmt.col_space;
	pix->field 	      = pvt->gps_cap_fmt.field_order;
	pix->sizeimage    = stride * pix->height;
	pix->bytesperline = stride;
	pix->ycbcr_enc    = pvt->gps_cap_fmt.encoding.yCbCr_enc;
	pix->quantization = pvt->gps_cap_fmt.quantization;
	pix->xfer_func    = pvt->gps_cap_fmt.xfer_fun;

    return stride;
}

/* 
 * ARGB32 For single plane 
 *
 * Defualt device format configuration
 *
 */
static int v4l2_gps_vidioc_g_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *f)
{
	struct gps_priv *pvt = file_prvdata(file);
    struct v4l2_pix_format *pix = &f->fmt.pix;
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;

	switch (pvt->gps_cap_fmt.pixel_fmt) {
	case V4L2_PIX_FMT_ARGB32:
	case V4L2_PIX_FMT_ABGR32:
		pix->pixelformat = pvt->gps_cap_fmt.pixel_fmt;
		break;
	default:
		/* In case multiplanar is set earlier */
		GPS_NOTI("Device is in multiplanar mode!!!");
		return -EBUSY;
	}

	/* Check if any format is set other wise default it to one */
    pix->width        = pgps_ctx->width;
    pix->height       = pgps_ctx->height;
    pix->field        = pvt->gps_cap_fmt.field_order;
    pix->colorspace   = pvt->gps_cap_fmt.col_space;
	pix->sizeimage    = pix->width * pix->height * 4;
    pix->bytesperline = pix->width * 4; // stride
    pix->ycbcr_enc    = pvt->gps_cap_fmt.encoding.yCbCr_enc;
	pix->quantization = pvt->gps_cap_fmt.quantization;
	pix->xfer_func    = pvt->gps_cap_fmt.xfer_fun;

    return 0;
}


static int v4l2_gps_vidioc_g_fmt_vid_cap_mplane(struct file *file, void *priv,
					struct v4l2_format *f)
{
    struct gps_priv *pvt = file_prvdata(file);
    struct v4l2_pix_format_mplane *mpix = &f->fmt.pix_mp;
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;

	switch(pvt->gps_cap_fmt.pixel_fmt){
	case V4L2_PIX_FMT_ARGB32:
	case V4L2_PIX_FMT_ABGR32:
		mpix->plane_fmt[0].sizeimage    = pvt->gps_cap_fmt.stride * pgps_ctx->height; // ARGB32
		mpix->plane_fmt[0].bytesperline = pvt->gps_cap_fmt.stride;
	  	break;
	case V4L2_PIX_FMT_NV12M:
		mpix->plane_fmt[0].sizeimage    = pvt->gps_cap_fmt.stride * pgps_ctx->height; // ARGB32
		mpix->plane_fmt[0].bytesperline = pvt->gps_cap_fmt.stride;
		mpix->plane_fmt[1].sizeimage    = mpix->plane_fmt[0].sizeimage >> 1; // C Bytes
		mpix->plane_fmt[1].bytesperline = pvt->gps_cap_fmt.stride;
	  	break;
	default:
		GPS_NOTI("%s: No default capture format!!!", __func__);
		return -EBUSY;
	}

	mpix->pixelformat = pvt->gps_cap_fmt.pixel_fmt;
	mpix->num_planes = pvt->gps_cap_fmt.num_planes;

	//pvt->gps_cap_fmt.pixel_fmt = mpix->pixelformat;
	//pvt->gps_cap_fmt.num_planes= mpix->num_planes;

    mpix->width       = pgps_ctx->width;
    mpix->height      = pgps_ctx->height;
    mpix->field       = pvt->gps_cap_fmt.field_order;
    mpix->colorspace  = pvt->gps_cap_fmt.col_space;


    mpix->ycbcr_enc    = pvt->gps_cap_fmt.encoding.yCbCr_enc;
	mpix->quantization = pvt->gps_cap_fmt.quantization;
	mpix->xfer_func    = pvt->gps_cap_fmt.xfer_fun;

    return 0;
}


static int v4l2_gps_vidioc_try_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
    struct video_device *vdev  = video_devdata(file);
    struct vb2_queue   *queue  = lookup_vb2_queue(vdev,file);
    struct gps_priv     *pvt   = file_prvdata(file);
	int nRetVal = 0;

    GPS_NOTI("%s: ",__func__);

    if (f->type != queue->type)
        return -EINVAL;

    nRetVal = __gps_video_try_format_sp(pvt, &f->fmt.pix, NULL);

	if(nRetVal < 0)
		return -EINVAL;

	return 0;
}

static int v4l2_gps_vidioc_try_fmt_vid_cap_mplane(struct file *file, void *fh, struct v4l2_format *f)
{
    struct video_device *vdev  = video_devdata(file);
    struct vb2_queue   *queue  = lookup_vb2_queue(vdev,file);
    struct gps_priv     *pvt   = file_prvdata(file);
	int nRetVal = 0;

    GPS_NOTI("%s: ",__func__);

    if (f->type != queue->type)
        return -EINVAL;

    nRetVal = __gps_video_try_format_mp(pvt, &f->fmt.pix_mp, NULL);

	if(nRetVal < 0)
		return -EINVAL;

	return 0;
}

static int v4l2_gps_vidioc_s_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *fmt)
{
    struct video_device    *vdev = video_devdata(file);
    //struct gps_dev         *dev  = video_drvdata(file);
    struct gps_priv        *pvt  = file_prvdata(file);
    struct v4l2_pix_format *pix  = &fmt->fmt.pix;
    LX_DE_GPS_CTRL_T       *pgps_ctx = &pvt->gps_info.gps_ctx;
	struct vb2_queue       *gps_q = NULL;
	int nRetVal = 0;

    GPS_NOTI("%s: ", __func__);

	gps_q = lookup_vb2_queue(vdev, file);
	if (gps_q->streaming)
		return -EBUSY;

	if (pix->width > pvt->gps_cap_fmt.max_width || pix->height > pvt->gps_cap_fmt.max_height) {
		GPS_ERROR("-EINVAL w/h=%d/%d", pix->width, pix->height);
		return -EINVAL;
	}

	nRetVal = __gps_video_try_format_sp(pvt, pix, NULL);

	if(nRetVal >= 0) {
		pvt->gps_cap_fmt.stride = nRetVal;
	} else {
		GPS_ERROR("-EINVAL nRetVal=%d",nRetVal);
		return -EINVAL;
	}

	/* 
	 * Set the format in actual 
	 * If set format is not supported return the current format or default format 
	 */
    pgps_ctx->width             = pix->width;
    pgps_ctx->height            = pix->height;
	pvt->gps_cap_fmt.pixel_fmt  = pix->pixelformat;
	pvt->gps_cap_fmt.num_planes = 1;
	pvt->gps_cap_fmt.num_buf    = MAX_GPS_BUF;

	gps_q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	gps_q->is_multiplanar = V4L2_TYPE_IS_MULTIPLANAR(gps_q->type);

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_ARGB32:
		pgps_ctx->pix_fmt = E_FMT_ARGB32;
		break;
	case V4L2_PIX_FMT_ABGR32:
		pgps_ctx->pix_fmt = E_FMT_ABGR32;
		break;
	default:
		GPS_ERROR("It must not come here");
	}

	/*Harish: This is wrong the alpha need to be set in control API */
	pgps_ctx->pix_alp = 0xFF;
    return 0;
}

static int v4l2_gps_vidioc_s_fmt_vid_cap_mplane(struct file *file, void *priv,
			        struct v4l2_format *f)
{
    struct video_device *vdev = video_devdata(file);
    struct gps_dev *dev       = video_drvdata(file);
    struct gps_priv *pvt      = file_prvdata(file);
    struct v4l2_pix_format_mplane *mpix = &f->fmt.pix_mp;
    LX_DE_GPS_CTRL_T *pgps_ctx  = &pvt->gps_info.gps_ctx;
	struct vb2_queue *gps_q = NULL;
	int nRetVal = 0;

    GPS_NOTI("%s: ",__func__);

#if 0 /*LG GPS can support dynamic configuration */
    if (vb2_is_busy(lookup_vb2_queue(vdev,file)))
        return -EBUSY;
#else
	gps_q = lookup_vb2_queue(vdev,file);
	if (gps_q->streaming)
		return -EBUSY;

	if (mpix->width > pvt->gps_cap_fmt.max_width || mpix->height > pvt->gps_cap_fmt.max_height) {
		GPS_ERROR("aaa -EINVAL w/h=%d/%d",mpix->width,mpix->height);
		return -EINVAL;
	}
#endif

    if (!dev->multiplanar) return -ENOTTY;

	nRetVal = __gps_video_try_format_mp(pvt, mpix, NULL);

	if (nRetVal >= 0) {
		pvt->gps_cap_fmt.stride = nRetVal;
	} else {
		GPS_ERROR("-EINVAL nRetVal=%d",nRetVal);
		return -EINVAL;
	}

	/* Set the format in actual 
	 * If set format is not supported return the current format or default format 
	 */
    pgps_ctx->width  = mpix->width;
    pgps_ctx->height = mpix->height;

	pvt->gps_cap_fmt.pixel_fmt  = mpix->pixelformat;
	pvt->gps_cap_fmt.num_buf    = MAX_GPS_BUF;

	switch (mpix->pixelformat){
	case V4L2_PIX_FMT_ARGB32:
		pgps_ctx->pix_fmt = E_FMT_ARGB32;
		break;
	case V4L2_PIX_FMT_ABGR32:
		pgps_ctx->pix_fmt = E_FMT_ABGR32;
		break;
	case V4L2_PIX_FMT_NV12M:
		pgps_ctx->pix_fmt = E_FMT_YUV420;
		break;
	default:
		GPS_ERROR("It must not come here");
	}

	pvt->gps_cap_fmt.num_planes = mpix->num_planes;
	gps_q->type                 = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	gps_q->is_multiplanar       = V4L2_TYPE_IS_MULTIPLANAR(gps_q->type);
	pgps_ctx->pix_alp           = 0xFF;

	GPS_NOTI("aaa num_planes: %d w/h=%d/%d\n", pvt->gps_cap_fmt.num_planes,mpix->width,mpix->height);

    return 0;
}

static int v4l2_gps_vidioc_enum_framesizes(struct file *file, void *fh, struct v4l2_frmsizeenum *fsize)
{
    struct pixel_format_info *fmt = NULL;
	int index;

    GPS_NOTI("%s: ",__func__);

	/* It can be for multiplanar or for single planar */
    fmt = find_gps_format(pixel_formats_mp, ARRAY_SIZE(pixel_formats_mp), fsize->pixel_format, &index);
    if (!fmt) {
		/*check in single planar*/
		fmt = find_gps_format(pixel_formats_sp, ARRAY_SIZE(pixel_formats_sp), fsize->pixel_format, &index);
		if (!fmt)
        	return -EINVAL;
    }

    return find_gps_framesize(fmt, fsize->index, fsize);
}

static int v4l2_gps_vidioc_enum_frameintervals(struct file *file, void *fh, struct v4l2_frmivalenum *fival)
{
    struct pixel_format_info *fmt = NULL;
    //struct v4l2_frmsizeenum fsize;
	struct frame_size_info *frmSize = NULL;
    unsigned int idx,index;
	int width, height, type, fIIdx=0;

    GPS_NOTI("%s: ",__func__);

	if (fival->index >= ARRAY_SIZE(frame_intervals)) {
		return -EINVAL;
	}

     /* It can be for multiplanar or for single planar */
	fmt = find_gps_format(pixel_formats_mp, ARRAY_SIZE(pixel_formats_mp), fival->pixel_format, &index);
	if (!fmt) {
		/* check in single planar */
		fmt = find_gps_format(pixel_formats_sp, ARRAY_SIZE(pixel_formats_sp), fival->pixel_format, &index);
		if (!fmt)
			return -EINVAL;
	}


    for (idx = 0 ; idx < ARRAY_SIZE(fmt->frame_size_indexes); idx++) {

		if (pixel_formats_mp[index].frame_size_indexes[idx] == -1)
			return -EINVAL;

		frmSize = &frame_sizes[pixel_formats_mp[index].frame_size_indexes[idx]];
		type = frmSize->type;

		if (type == V4L2_FRMSIZE_TYPE_DISCRETE) {
		    width  = frmSize->size.disc_frm.width;
		    height = frmSize->size.disc_frm.height;

			if(width != fival->width || height != fival->height)
				continue;
		}

		fIIdx = frame_sizes[idx].frm_interval_index[fival->index];

		if (fIIdx == -1)
			return -EINVAL;

		/* We only support discrete now */
		fival->type = frame_intervals[fIIdx].type;
		fival->discrete.numerator = \
			 frame_intervals[fIIdx].interval.disc_intrval.numerator;
		fival->discrete.denominator = \
			 frame_intervals[fIIdx].interval.disc_intrval.denominator;
    }

    fival->type = V4L2_FRMSIZE_TYPE_DISCRETE; //SOCTSSIC-164338
    return 0;
}

static int v4l2_gps_vidioc_queryctrl(struct file *file, void *fh,
			  struct v4l2_queryctrl *ctrl)
{
	int i = 0, chkNext = 0;

    GPS_NOTI("%s: ", __func__);

	if (ctrl->id & V4L2_CTRL_FLAG_NEXT_COMPOUND ) { 
		GPS_NOTI("%s: Compound control not supported",__func__);
		return -ENOTTY;
	}

	if (ctrl->id & V4L2_CTRL_FLAG_NEXT_CTRL ) {
		chkNext = 1;
		ctrl->id &= ~V4L2_CTRL_FLAG_NEXT_CTRL;
	}

	for (i = 0; i < ARRAY_SIZE(gps_v4l2_queryctrl); i++) {
		if (chkNext) {
			if (gps_v4l2_queryctrl[i].id > ctrl->id) {
				memcpy(ctrl,&gps_v4l2_queryctrl[i],sizeof(struct v4l2_queryctrl));
				ctrl->id |= V4L2_CTRL_FLAG_NEXT_CTRL;
				return 0;
			}
		} else {
			if (ctrl->id & gps_v4l2_queryctrl[i].id) {
				memcpy(ctrl,&gps_v4l2_queryctrl[i],sizeof(struct v4l2_queryctrl));
				return 0;
			}
		}
	}

	ctrl->flags = V4L2_CTRL_FLAG_DISABLED;
    return -EINVAL;
}

static int v4l2_gps_vidioc_querymenu(struct file *file, void *fh, struct v4l2_querymenu *ctrl)
{
	int i = 0, chkNext = 0;

    GPS_NOTI("%s: ", __func__);

	if (ctrl->id & V4L2_CTRL_FLAG_NEXT_COMPOUND ) {
		GPS_NOTI("%s: Compound control not supported",__func__);
		return -ENOTTY;
	}

	if (ctrl->id & V4L2_CTRL_FLAG_NEXT_CTRL ) {
		chkNext = 1;
		ctrl->id &= ~V4L2_CTRL_FLAG_NEXT_CTRL;
	}

	for (i = 0; i < ARRAY_SIZE(gps_v4l2_querymenu); i++) {
		if (chkNext) {
			if (gps_v4l2_querymenu[i].id > ctrl->id) {
				memcpy(ctrl,&gps_v4l2_querymenu[i],sizeof(struct v4l2_querymenu));
				ctrl->id |= V4L2_CTRL_FLAG_NEXT_CTRL;
				return 0;
			}
		} else {
			if (ctrl->id & gps_v4l2_querymenu[i].id) {
				memcpy(ctrl,&gps_v4l2_querymenu[i],sizeof(struct v4l2_querymenu));
				return 0;
			}
		}
	}

    return -EINVAL;
}

static int v4l2_gps_vidioc_s_ctrl(struct file *file, void *fh, struct v4l2_control *ctrl)
{
	struct video_device *vdev	= video_devdata(file);
    struct gps_priv *pvt = file_prvdata(file);
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;
    __u32 retVal = 0;

    GPS_NOTI("%s: Control ID: %d",__func__,ctrl->id);

    switch(ctrl->id) {
        case V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE:
        {
            pvt->gps_cap_fmt.max_width = (ctrl->value >> 16 & 0xffff);
            pvt->gps_cap_fmt.max_height= ctrl->value & 0xffff;
            GPS_NOTI("Control value:: Width: [%d] Height: [%d]\n",pvt->gps_cap_fmt.max_width,pvt->gps_cap_fmt.max_height);
			if(pvt->gps_cap_fmt.max_width == 0 && pvt->gps_cap_fmt.max_height == 0)
				return -1;
			if(!strcmp(vdev->name, "ttv-capture-dev")) { // in case of TTV   out device
				if(pvt->gps_cap_fmt.max_width > (DEF_GPS_CAP_WIDTH *2) || pvt->gps_cap_fmt.max_height > (DEF_GPS_CAP_WIDTH*2))
					return -1;
			}
			else {
				if(pvt->gps_cap_fmt.max_width > DEF_GPS_CAP_WIDTH || pvt->gps_cap_fmt.max_height > DEF_GPS_CAP_WIDTH)
					return -1;
			}
            pgps_ctx->max_w = pvt->gps_cap_fmt.max_width;
            pgps_ctx->max_h = pvt->gps_cap_fmt.max_height;
        }
        break;
        case V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE:
        {
			if (ctrl->value == 0 || ctrl->value == 1) {
				pgps_ctx->bbd_en = (UINT32)ctrl->value;
			} else {
				retVal = -EINVAL;
			}
			GPS_NOTI("bbd : M [%d(%d)][%d/%d,%d,%d,%d] val:%d ret:%d\n",pgps_ctx->bbd_id,pgps_ctx->vdec_id,pgps_ctx->bbd_en,\
				(pgps_ctx->bbd_xw>>16)&0xffff,(pgps_ctx->bbd_yh>>16)&0xffff,pgps_ctx->bbd_xw&0xffff,pgps_ctx->bbd_yh&0xffff,ctrl->value,retVal);
        }
        break;
        case V4L2_CID_EXT_GPSCALER_SECURE_MODE:
        {
            pvt->svp = ctrl->value;
            gps_set_svp_info(pvt->svp);
            GPS_NOTI("V4L2_CID_EXT_GPSCALER_SECURE_MODE   svp = %d", pvt->svp);
        }
        break;
#ifdef V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE
		case V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE:
		{
            pvt->attr = ctrl->value;
            GPS_NOTI("V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE   attr = %d", pvt->attr);
        }
		break;
#endif
        default:
        {
            GPS_NOTI("Not Supported");
            retVal = -ENOTTY;
        }
    }

    return retVal;
}

static int v4l2_gps_vidioc_g_ctrl(struct file *file, void *fh,
			  struct v4l2_control *ctrl)
{
	struct gps_dev *dev  	  = video_drvdata(file);
	struct vb2_queue *q = NULL;
    struct gps_priv *pvt = file_prvdata(file);
    LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;
	__u32 retVal = 0;

	do {
		if (ctrl->id == V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H)	break;
		if (ctrl->id == V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V)	break;
		GPS_NOTI("%s: Control ID: %d",__func__,ctrl->id);
	} while(0);

	switch(ctrl->id){
		case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		{
			q = &dev->vb_gps_cap_q;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
			ctrl->value = 3;//q->min_queued_buffers;
#else
			ctrl->value = DEF_GPS_BUFS/*q->min_buffers_needed*/;
#endif
			GPS_NOTI("aaa Control value: %d",ctrl->value);
		}break;
		case V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE:
		{
			ctrl->value = (pvt->gps_cap_fmt.max_height & 0xffff) | (pvt->gps_cap_fmt.max_width << 16);
		}break;
		case V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE:
		{
			unsigned int width, height;
			width  = pvt->cur_width;
			height = pvt->cur_height;
			ctrl->value = ((width&0xFFFF) << 16) | (height&0xFFFF);
			GPS_NOTI("Input size: %dx%d",(ctrl->value >> 16), ctrl->value&0xFFFF);
		}break;
		case V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE:
		{
			ctrl->value = pgps_ctx->bbd_en;
			GPS_NOTI("bbd : M [%d(%d)][%d/%d,%d,%d,%d]\n",pgps_ctx->bbd_id,pgps_ctx->vdec_id,pgps_ctx->bbd_en,\
				(pgps_ctx->bbd_xw>>16)&0xffff,(pgps_ctx->bbd_yh>>16)&0xffff,pgps_ctx->bbd_xw&0xffff,pgps_ctx->bbd_yh&0xffff);
		}break;
		case V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H:
		{
			int bbd_ret = -100;
			unsigned int bbd_act[2] = {-1,-1};
			bbd_ret = gps_if_get_bbd(pgps_ctx->vdec_id,bbd_act);
			if (bbd_ret==0 && (pgps_ctx->bbd_xw!=bbd_act[0]||pgps_ctx->bbd_yh!=bbd_act[1]))
			{
				GPS_NOTI("bbd : H [%d(%d)][%d/%d,%d,%d,%d <- %d,%d,%d,%d]\n",pgps_ctx->bbd_id,pgps_ctx->vdec_id,pgps_ctx->bbd_en,\
					(bbd_act[0]>>16)&0xffff,(bbd_act[1]>>16)&0xffff,bbd_act[0]&0xffff,bbd_act[1]&0xffff,\
					(pgps_ctx->bbd_xw>>16)&0xffff,(pgps_ctx->bbd_yh>>16)&0xffff,pgps_ctx->bbd_xw&0xffff,pgps_ctx->bbd_yh&0xffff);
				pgps_ctx->bbd_xw = bbd_act[0];
				pgps_ctx->bbd_yh = bbd_act[1];
			}
			ctrl->value = pgps_ctx->bbd_xw;
			GPS_TRACE1("bbd : H [%d(%d)][%d/%d,%d,%d,%d](ret:%d)\n",pgps_ctx->bbd_id,pgps_ctx->vdec_id,pgps_ctx->bbd_en,\
				(pgps_ctx->bbd_xw>>16)&0xffff,(pgps_ctx->bbd_yh>>16)&0xffff,pgps_ctx->bbd_xw&0xffff,pgps_ctx->bbd_yh&0xffff,bbd_ret);
		}break;
		case V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V:
		{
			ctrl->value = pgps_ctx->bbd_yh;
			GPS_TRACE1("bbd : V [%d(%d)][%d/%d,%d,%d,%d]\n",pgps_ctx->bbd_id,pgps_ctx->vdec_id,pgps_ctx->bbd_en,\
				(pgps_ctx->bbd_xw>>16)&0xffff,(pgps_ctx->bbd_yh>>16)&0xffff,pgps_ctx->bbd_xw&0xffff,pgps_ctx->bbd_yh&0xffff);
		}break;
#ifdef V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE
		case V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE:
		{
			ctrl->value = pvt->attr;
			GPS_NOTI("V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE   attr = %d", ctrl->value);
		}break;
#endif
		default:
		{
			GPS_NOTI("Not Supported");
			retVal = -ENOTTY;
		}
	}

    return retVal;
}

static int v4l2_gps_vidioc_g_parm(struct file *file, void *fh,
			  struct v4l2_streamparm *parm)
{
	//struct video_device *vdev = video_devdata(file);
	struct gps_dev *dev  = video_drvdata(file);
	struct vb2_queue *q = NULL;

    //GPS_NOTI("%s: ",__func__);

	q = &dev->vb_gps_cap_q;

	if (parm->type != q->type)
        return -EINVAL;

    return 0;
}

static int v4l2_gps_vidioc_s_parm(struct file *file, void *fh,
			  struct v4l2_streamparm *parm)
{
	//struct video_device *vdev = video_devdata(file);
	struct gps_dev *dev  = video_drvdata(file);
	struct vb2_queue *q = NULL;

    //GPS_NOTI("%s: ",__func__);

	q = &dev->vb_gps_cap_q;

	if (parm->type != q->type)
        return -EINVAL;

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int v4l2_gps_vidioc_g_pixelaspect(struct file *file, void *priv,
			int buf_type, struct v4l2_fract *aspect)
#else
static int v4l2_gps_vidioc_cropcap(struct file *file, void *priv,
			struct v4l2_cropcap *crop)
#endif
{
    GPS_NOTI("%s: ",__func__);

#if 0
	memset(crop, 0, sizeof(struct v4l2_cropcap));

	crop->type              = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	crop->defrect.width     = 0;
	crop->bounds.width      = 0;
	crop->defrect.height    = 0;
	crop->bounds.height     = 0;
#endif
	return -ENOTTY;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static int v4l2_gps_vidioc_g_crop(struct file *file, void *fh, struct v4l2_crop *cr)
{
    GPS_NOTI("%s: ",__func__);

    return -ENOTTY;
}

static int v4l2_gps_vidioc_s_crop(struct file *file, void *fh, const struct v4l2_crop *crop)
{
    GPS_NOTI("%s: ",__func__);

    return -ENOTTY;
}
#endif

static int v4l2_gps_vidioc_g_selection(struct file *file, void *fh, struct v4l2_selection *s)
{
    GPS_NOTI("%s: ",__func__);

    return -ENOTTY;
}

static int v4l2_gps_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
    GPS_NOTI("%s: id[%d]",__func__, sub->id);

	return v4l2_event_subscribe(__fh, sub, 32, NULL);
}

static int v4l2_gps_vidioc_unsubscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
    GPS_NOTI("%s: ",__func__);

	return v4l2_event_unsubscribe(__fh, sub);
}


static void __freeFrmBuffer(struct gps_priv *pvt,int bufCnt, int planeCnt)
{
    unsigned int /*paddr,plane,*/buffer;
	LX_DE_GPS_CTRL_T    *pgps_ctx = &pvt->gps_info.gps_ctx;

    for (buffer = 0; buffer < bufCnt; ++buffer){
		pgps_ctx->buffer_addr_y[buffer] = 0;
		pgps_ctx->buffer_addr_c[buffer] = 0;
    }
}


int _gps_ioctl_reqbufs(struct file *file, struct vb2_queue *queue,
			  struct v4l2_requestbuffers *p)
{
	struct video_device *vdev  = video_devdata(file);
	int res;

	if (is_queue_busy(vdev, file)){
		return -EBUSY;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
	res = vb2_core_reqbufs(queue, p->memory, 0, &p->count);
#else
	res = vb2_core_reqbufs(queue, p->memory, &p->count);
#endif
	if (res == 0)
		queue->owner = p->count ? file->private_data : NULL;

	GPS_NOTI("res:%d\n", res);

	return res;
}

static int v4l2_gps_vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
    struct video_device *vdev     = video_devdata(file);
    struct vb2_queue    *queue    = lookup_vb2_queue(vdev, file);
    struct gps_priv     *pvt      = file_prvdata(file);
    struct dma_buf *dmabuf        = file->private_data;
    char *svp_str = "secured";
    //LX_DE_GPS_CTRL_T    *pgps_ctx = &pvt->gps_info.gps_ctx;
    int bufCnt = 0, planeCnt   = 0;
    int res;

#ifdef FORCE_TEST_SVP
	pvt->svp = 1;
#else
	//pvt->svp = p->reserved[0];
#endif
	if(pvt->svp)
		memcpy(dmabuf->exp_name, svp_str, 8);

    GPS_NOTI("%s: type::%d q->type:: %d svp:: %d", __func__,p->type,queue->type, pvt->svp);

    if (p->count && p->count < MIN_GPS_BUF) {
		GPS_NOTI("aaa p->count = %d",p->count);
        return -EINVAL;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	if(p->count == 0 && vb2_get_num_buffers(queue)){
		bufCnt   = vb2_get_num_buffers(queue);
#else
	if(p->count == 0 && queue->num_buffers){
		bufCnt   = queue->num_buffers;
#endif
		planeCnt = queue->bufs[0]->num_planes;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	p->capabilities = V4L2_BUF_CAP_SUPPORTS_MMAP   | \
                      V4L2_BUF_CAP_SUPPORTS_DMABUF | \
                      V4L2_BUF_CAP_SUPPORTS_ORPHANED_BUFS;
#endif
    /* call default function of vb2 ioctl */
    res = _gps_ioctl_reqbufs(file, queue, p);
    if (res) {
        return res;
    }
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	GPS_NOTI("%s: aaa REQ_BUF (0) BufCnt::%d, p->count:%d vb2_get_num_buffers:%d", __func__, bufCnt, p->count, vb2_get_num_buffers(queue));
#else
	GPS_NOTI("%s: aaa REQ_BUF (0) BufCnt::%d, p->count:%d queue->num_buffers:%d", __func__, bufCnt, p->count, queue->num_buffers);
#endif

	/* count == 0 means release buffers */
	if(p->count == 0){
		if (bufCnt) {
			__freeFrmBuffer(pvt, bufCnt, planeCnt);
		}

		GPS_NOTI("%s: aaa REQ_BUF (0)",__func__);
		return 0;
	}

	res = v4l2_gps_alloc_memory(queue, pvt, p->count);
#ifdef SUPPORT_ADAPTIVE_STREAM
	if(pvt->gps_info.gps_ctx.max_w > pvt->gps_info.gps_ctx.width || \
			pvt->gps_info.gps_ctx.max_h > pvt->gps_info.gps_ctx.height) {
		pvt->adaptive_mode = 1;
		GPS_NOTI("%s: adaptive_mode::%d",__func__,pvt->adaptive_mode);
	}
#endif

	GPS_NOTI("%s: aaa res::%d",__func__,res);

	return res;
}


int v4l2_gps_vidioc_create_bufs(struct file *file, void *priv,
			  struct v4l2_create_buffers *p)
{
	int res;
	struct vb2_queue    *queue = NULL;
	struct video_device *vdev  = video_devdata(file);
    struct gps_priv     *pvt   = file_prvdata(file);
	struct v4l2_requestbuffers reqInfo;

	queue = lookup_vb2_queue(vdev, file);

    GPS_NOTI("%s: q->type:: %d ", __func__, queue->type);

	res = vb2_verify_memory_type(queue, p->memory, p->format.type);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
	p->index = vb2_get_num_buffers(queue);
#else
	p->index = queue->num_buffers;
#endif

	if (p->count == 0)
		return res != -EBUSY ? res : 0;

	if (res)
		return res;

	if (is_queue_busy(vdev, file))
		return -EBUSY;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	res = vb2_create_bufs(queue, p);
#else
	res = vb2_core_create_bufs(queue, p->memory, &p->count,
			&p->format);
#endif
	if (res == 0)
		queue->owner = file->private_data;
	else
		return res;

	/* Error scenario */
	res = v4l2_gps_alloc_memory(queue, pvt, p->count);
	if (res) {
		GPS_NOTI("%s: MemoryAllocation failed",__func__);
		p->count = 0;
		memset(&reqInfo, 0, sizeof(struct v4l2_requestbuffers));
		reqInfo.count  = 0;
		reqInfo.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE | V4L2_BUF_TYPE_VIDEO_CAPTURE;
		reqInfo.memory = p->memory;
		_gps_ioctl_reqbufs(file, queue, &reqInfo);
	}

	return res;
}

static int v4l2_gps_vidioc_querybuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	struct video_device *vdev = video_devdata(file);
	struct vb2_queue *q;
	int ret = 0;

	q = lookup_vb2_queue(vdev, file);
	
	ret = vb2_querybuf(q, p);

	return ret;
}

static int v4l2_gps_vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	int ret;
	struct video_device *vdev = video_devdata(file);

	if (is_queue_busy(vdev, file))
		return -EBUSY;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	ret = vb2_qbuf(lookup_vb2_queue(vdev,file), vdev->v4l2_dev->mdev, p);
	//ret = vb2_qbuf(vdev->queue, vdev->v4l2_dev->mdev, p);
	GPS_NOTI("%s: %p, idx[%d] ret[%d]",__func__, vdev->queue, p->index, ret);

	return ret;
#else
	return vb2_qbuf(lookup_vb2_queue(vdev,file), p);
#endif
}

static int v4l2_gps_vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	int ret=0;
	struct video_device *vdev = video_devdata(file);

	if (is_queue_busy(vdev, file))
		return -EBUSY;

	ret = vb2_dqbuf(lookup_vb2_queue(vdev, file), p, file->f_flags & O_NONBLOCK);
	p->flags = p->flags & (~V4L2_BUF_FLAG_QUEUED);

	GPS_NOTI("byteused(%d), length(%d)\n", p->bytesused, p->length);

	return ret;
}

int v4l2_gps_vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct video_device *vdev = video_devdata(file);

	if (is_queue_busy(vdev, file))
		return -EBUSY;

	return vb2_streamon(lookup_vb2_queue(vdev,file), i);
}

int v4l2_gps_vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct video_device *vdev = video_devdata(file);

	if (is_queue_busy(vdev, file))
		return -EBUSY;

	return vb2_streamoff(lookup_vb2_queue(vdev,file), i);
}

static int v4l2_gps_vidioc_expbuf(struct file *file, void *priv, struct v4l2_exportbuffer *p)
{
	struct dma_buf *dmabuf = file->private_data;
	struct video_device *vdev = video_devdata(file);

	GPS_NOTI("%s: exp_name[%s]",__func__, dmabuf->exp_name);

	return vb2_expbuf(lookup_vb2_queue(vdev,file), p);
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
    struct file_vb2_q *file_q  = to_file_vb2_q(vq);
	struct gps_priv *pvt       = file_prvdata(file_q->file);
	LX_DE_GPS_CTRL_T *pgps_ctx = &pvt->gps_info.gps_ctx;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	struct v4l2_format *fmt    = (struct v4l2_format *)parg;
#endif
	int stride = 0,height = 0, width = 0;

	GPS_NOTI("%s: ",__func__);

	/* VIDIOC_REQBUFS call*/
	/*AVTASK-442: New request to create buffer of maximum size rather than the requested size */

	/* We need to calculate stride for new width and height */
	if (pvt->gps_cap_fmt.max_width && pvt->gps_cap_fmt.max_height) {

		switch(pvt->gps_cap_fmt.pixel_fmt){
		case V4L2_PIX_FMT_NV12M:
			//stride = pvt->gps_cap_fmt.max_width;
			//rem    = stride % LG_MEM_STRIDE_STEP;
			stride  = pvt->gps_cap_fmt.max_width;
			break;
		case V4L2_PIX_FMT_ARGB32:
		case V4L2_PIX_FMT_ABGR32:
			stride = pvt->gps_cap_fmt.max_width * 4;
			break;
		default:
			GPS_ERROR("It should not come here!!!!!");
			break;
		}

		stride = ALIGN_64(stride);

		height = pvt->gps_cap_fmt.max_height;
		width  = pvt->gps_cap_fmt.max_width;
	} else {
		stride = pvt->gps_cap_fmt.stride;
		height = pgps_ctx->height;
		width  = pgps_ctx->width;
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	if(parg == NULL){
#endif
		switch(pvt->gps_cap_fmt.pixel_fmt){
		case V4L2_PIX_FMT_NV12M:
			GPS_NOTI("Format is V4L2_PIX_FMT_NV12M [0x%x]",pvt->gps_cap_fmt.pixel_fmt);
			sizes[0] = stride * height;
			sizes[1] = sizes[0] / 2;				
			break;
		case V4L2_PIX_FMT_ARGB32:
		case V4L2_PIX_FMT_ABGR32:
			sizes[0] = stride * height;
			GPS_NOTI("Format is :: [0x%x] and Size[0] :: %d", pvt->gps_cap_fmt.pixel_fmt, sizes[0]);
			break;
		default:
			GPS_NOTI("Unsupported format::%d",pvt->gps_cap_fmt.pixel_fmt);
		}

		*nbuffers = pvt->gps_cap_fmt.num_buf;
		*nplanes  = pvt->gps_cap_fmt.num_planes;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	} else { /* VIDIOC_CREATE_BUFS */
		switch(pvt->gps_cap_fmt.pixel_fmt) {
		case V4L2_PIX_FMT_NV12M:
			/* multiplaner format [Y and UV plane] */
			sizes[0] = fmt->fmt.pix_mp.plane_fmt[0].sizeimage;
			sizes[1] = fmt->fmt.pix_mp.plane_fmt[1].sizeimage;				
			if((fmt->fmt.pix_mp.num_planes != MAX_VT_PLANE) && (sizes[0] != pgps_ctx->width * pgps_ctx->height) ||\
					(sizes[1] != sizes[0] / 2))
				return -EINVAL;
				
			*nplanes = fmt->fmt.pix_mp.num_planes;
			break;
		case V4L2_PIX_FMT_ARGB32:
			sizes[0] = fmt->fmt.pix.sizeimage;
			*nplanes = 1;
			break;
		default:
			GPS_NOTI("Unsupported format::%d", pvt->gps_cap_fmt.pixel_fmt);
		}
#endif
		width  = pgps_ctx->width;
		height = pgps_ctx->height;

	//	GPS_NOTI("Allocated Buffers [CREATE_BUFS]::%d\n", vq->num_buffers);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
		if(vb2_get_num_buffers(vq) == MAX_GPS_BUF) {
#else
		if(vq->num_buffers == MAX_GPS_BUF) {
#endif
//			GPS_NOTI("maximum number of buffers already allocated::%d\n", vq->num_buffers);
			return -ENOBUFS;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
		} else if(vb2_get_num_buffers(vq) < MAX_GPS_BUF) {
			*nbuffers = MAX_GPS_BUF - vb2_get_num_buffers(vq);
		}
#else
		} else if(vq->num_buffers < MAX_GPS_BUF) {
			*nbuffers = MAX_GPS_BUF - vq->num_buffers;
		}
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	}
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
    GPS_NOTI("aaa %s: num_buffers:%d, *nbuffers:%d\n", __func__, vb2_get_num_buffers(vq), *nbuffers);
#else
    GPS_NOTI("aaa %s: num_buffers:%d, *nbuffers:%d\n", __func__, vq->num_buffers, *nbuffers);
#endif

	pvt->cap_buffers = *nbuffers;

	/* Store the allocated buffer information */
	pvt->gps_cap_fmt.alloc_buf_width = width;
	pvt->gps_cap_fmt.alloc_buf_height= height;
	pvt->gps_info.gps_ctx.src_attr = (UINT32)pvt->attr;

    return 0;
}

static int buffer_prepare(struct vb2_buffer *vb)
{
	struct file_vb2_q  *file_q   = to_file_vb2_q(vb->vb2_queue);
	struct gps_priv    *pvt      = file_prvdata(file_q->file);
	LX_DE_GPS_CTRL_T   *pgps_ctx = &pvt->gps_info.gps_ctx;
	unsigned int plane_idx, cPlaneShift = 0;

	if (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		switch(pvt->gps_cap_fmt.pixel_fmt) {
		case V4L2_PIX_FMT_NV12M:
			cPlaneShift = 1; /* 1/2 of Y plane*/
			break;
		case V4L2_PIX_FMT_ARGB32:
		case V4L2_PIX_FMT_ABGR32:
		{
			cPlaneShift = 0; /* NO C plane*/
		}break;
		default:
			GPS_ERROR("Unsupported format");
		}

		/* Only YCbCr4:2:0 ans semiplaner format [NV12M] is supported */
		for (plane_idx = 0; plane_idx < vb->num_planes; plane_idx++) {
			vb->planes[plane_idx].bytesused = (plane_idx == 0) ? 
				(pvt->gps_cap_fmt.stride * pgps_ctx->height) : 
				((pvt->gps_cap_fmt.stride * pgps_ctx->height) >> cPlaneShift);
		}
	} else if(vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE){
		switch(pvt->gps_cap_fmt.pixel_fmt) {
		case V4L2_PIX_FMT_ARGB32:
		case V4L2_PIX_FMT_ABGR32:
			vb->planes[0].length = (pvt->gps_cap_fmt.stride * pgps_ctx->height);
			break;
		default:
			GPS_ERROR("Unsupported format");
		}
	}

	return 0;
}

static void buffer_queue(struct vb2_buffer *vb)
{
	int ret = 0;
	struct gps_cap_buffer *vbuf     = to_gps_cap_buffer(vb);
	struct file_vb2_q     *file_q   = to_file_vb2_q(vb->vb2_queue);
	//struct gps_dev        *dev      = video_drvdata(file_q->file);
	struct gps_priv       *pvt      = file_prvdata(file_q->file);
	LX_DE_GPS_CTRL_T      *pgps_ctx = &pvt->gps_info.gps_ctx;
	unsigned int lock_flag = 1;
	lock_flag = 1 & g_gps_lock_mask[vb->index];

	// unlock buffer (QBUF)
	ret = gps_if_lock_buffer(pgps_ctx->vdec_id, vbuf->vb.vb2_buf.index, lock_flag, g_gps_log_level);
	if (ret) { GPS_ERROR("error"); }

	spin_lock(&pvt->slock);
	list_add_tail(&vbuf->list, &pvt->vb_gps_cap_list);
	spin_unlock(&pvt->slock);

	if (g_gps_log_level < 1) GPS_NOTI("Unlock buffer : id[%d] current index[%d] BuffIndex[%d]", \
		pgps_ctx->vdec_id, pgps_ctx->buf_idx,vbuf->vb.vb2_buf.index);
}

static void buffer_finish(struct vb2_buffer *vb)
{
	int ret = 0;
    //struct gps_cap_buffer *vbuf     = to_gps_cap_buffer(vb);
    struct file_vb2_q     *file_q   = to_file_vb2_q(vb->vb2_queue);
    //struct gps_dev        *dev      = video_drvdata(file_q->file);
	struct gps_priv       *pvt      = file_prvdata(file_q->file);
	LX_DE_GPS_CTRL_T      *pgps_ctx = &pvt->gps_info.gps_ctx;
	unsigned int buf_idx, lock_flag;

	// lock buffer (DQBUF)
	ret = gps_if_get_index(pgps_ctx->vdec_id, &buf_idx);
	if (ret) { GPS_ERROR("error"); }

	pgps_ctx->buf_idx = buf_idx;

	lock_flag = 1 ;//& g_gps_lock_mask[buf_idx];

	ret = gps_if_lock_buffer(pgps_ctx->vdec_id, vb->index, lock_flag, g_gps_log_level);
	if(ret) { GPS_ERROR("error"); }

	if(g_gps_log_level < 1) GPS_NOTI("[DQ]lock : id[%d] buf_idx[%d],vb->idx[%d]", \
		pgps_ctx->vdec_id, buf_idx, vb->index);

#ifdef SUPPORT_ADAPTIVE_STREAM
	if(pvt->adaptive_mode && pvt->change_ctx_size) {
		pgps_ctx->width = pvt->cur_width;
		pgps_ctx->height = pvt->cur_height;
		ret = gps_if_control(pgps_ctx);
		if(ret) DE_ERROR("error");
		DE_NOTI("id[%d] change pgps_ctx size up to %dx%d (max%dx%d)", \
			pgps_ctx->vdec_id,pgps_ctx->width, pgps_ctx->height, pgps_ctx->max_w,pgps_ctx->max_h);
		pvt->change_ctx_size = 0;
	}
#endif
}
static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	int ret = 0;
	struct file_vb2_q *file_q   = to_file_vb2_q(vq);
	//struct gps_dev    *dev      = video_drvdata(file_q->file);
	struct gps_priv   *pvt      = file_prvdata(file_q->file);
	LX_DE_GPS_CTRL_T  *pgps_ctx = &pvt->gps_info.gps_ctx;
	//struct sched_param k_param;
	ktime_t 	   t;
	struct timespec64 ts;
	struct gps_cap_buffer *buf      = NULL;

	GPS_NOTI("%s: ", __func__);

	/*Allocate the work in WQ */
	t  = ktime_get_real();
	ts = ktime_to_timespec64(t);
	pvt->drop = 0;
	drop_count[pgps_ctx->vdec_id] = 0;
	pvt->t_sec_prv  = ts.tv_sec;
	pvt->t_msec_prv = (ts.tv_nsec / 1000000);
	pvt->t_frm_sec_prv = ts.tv_sec;
	pvt->t_frm_msec_prv= pvt->t_msec_prv;
	pvt->avg_frame_lat = 0;
	pvt->max_frame_lat = 0;
	pvt->min_frame_lat = 1000;
	pvt->min_wq_lat = 1000;
	pvt->max_wq_lat = 0;
	pvt->avg_wq_lat = 0;
	pvt->int_drop = 0;
	pvt->max_int_cnt = 0;
	pvt->frm_int_cnt = 0;
	pvt->last_frm_index = 0;

	ret = gps_if_set_bbd(pgps_ctx->vdec_id, &pgps_ctx->bbd_en);
	if(ret)
		GPS_ERROR("gps_if_set_bbd error(%d)",ret);

#ifdef WQ_IMPL
	/*Allocate the work in WQ */
	pgps_ctx->enable = 1;
	pgps_ctx->stride = pvt->gps_cap_fmt.stride;

	ret = gps_if_control(pgps_ctx);

	if (ret) {
		GPS_ERROR("gps_if_control[Updated] error");

		//returned the buffer queued
		spin_lock(&pvt->slock);
		while (!list_empty(&pvt->vb_gps_cap_list)) {
			buf = list_entry(pvt->vb_gps_cap_list.next,	struct gps_cap_buffer, list);
			list_del(&buf->list);
			GPS_NOTI("Buffer :: %lx",(unsigned long)&buf->vb.vb2_buf);
			vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
		}
		spin_unlock(&pvt->slock);
		pgps_ctx->enable = 0;
		return -EIO;
	}

	if (VIDEO_HighPri_WQ_QWork(MODULE_GPS,&pvt->gps_noti_work) != 0){
		GPS_ERROR("[%d]Failed to Queue Work", pgps_ctx->vdec_id);
		pgps_ctx->enable = 0;
		ret = gps_if_control(pgps_ctx);
		return -EIO;
	}
#else
	pgps_ctx->enable = 1;
	pvt->thread_stop = 0;
	ret = gps_if_control(pgps_ctx);
	if(ret) GPS_ERROR("gps_if_control error");

	k_param.sched_priority = 99;
	pvt->gps_cap_thread = kthread_create(V4l2_gps_thread, vq, "irq/%s", dev->v4l2_gps_video_dev.name);
			sched_setscheduler(pvt->gps_cap_thread, SCHED_RR, &k_param);
			if(pvt->gps_cap_thread)
				wake_up_process(pvt->gps_cap_thread);

#endif
	return 0;
}

static void stop_streaming(struct vb2_queue *vq)
{
	int ret = 0;
    struct file_vb2_q     *file_q   = to_file_vb2_q(vq);
#ifndef WQ_IMPL
    struct gps_dev        *dev      = video_drvdata(file_q->file);
#endif
    struct gps_cap_buffer *buf      = NULL;
    struct gps_priv       *pvt      = file_prvdata(file_q->file);
    LX_DE_GPS_CTRL_T      *pgps_ctx = &pvt->gps_info.gps_ctx;

    GPS_NOTI("%s:",__func__);

#ifndef WQ_IMPL
    if (!dev || pvt->gps_cap_thread == NULL)
        return;
#endif
	pgps_ctx->enable = 0;
	ret = gps_if_control(pgps_ctx);
	if(ret) GPS_ERROR("gps_if_control error");

	pgps_ctx->bbd_en = 0;
	ret = gps_if_set_bbd(pgps_ctx->vdec_id, &pgps_ctx->bbd_en);
	if(ret) 
		GPS_ERROR("gps_if_set_bbd error(%d)", ret);

    spin_lock(&pvt->slock);
    while (!list_empty(&pvt->vb_gps_cap_list)) {
        buf = list_entry(pvt->vb_gps_cap_list.next, struct gps_cap_buffer, list);
        list_del(&buf->list);
        vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
    }
    spin_unlock(&pvt->slock);

#ifdef WQ_IMPL
	if (VIDEO_HighPri_WQ_DQWork(MODULE_GPS,&pvt->gps_noti_work) != 0) {
		GPS_ERROR("Failed to DQ Work");
	} else {
		msleep(20);
	}
#else
	pvt->thread_stop = 1;
	//kthread_stop(pvt->gps_cap_thread);
	pvt->gps_cap_thread = NULL;
#endif

	/* Print profiling details */
	GPS_NOTI("Profiling Info for VDEC::%d -->\n",pgps_ctx->vdec_id);
	GPS_NOTI("Frame Drop [QBUF]:: %d\nFrame Drop [Interrupt]:: %d\n",pvt->drop,pvt->int_drop);
	GPS_NOTI("Min Frame Latency:: %d\nMax Frame Latency:: %d\nAvg Frame Latency::%d\n",pvt->min_frame_lat,pvt->max_frame_lat,\
		(pvt->avg_frame_lat/pvt->frm_int_cnt));
	GPS_NOTI("Min WQ/Kthread Latency:: %d\nMax WQ/Kthread Latency:: %d\nAvg WQ/Kthread Latency::%d\n",pvt->min_wq_lat,pvt->max_wq_lat,\
		(pvt->avg_wq_lat/pvt->max_int_cnt));
}

static struct platform_device v4l2_gps_pdev = {
	.name = "v4l2_gps",
	.id   = -1,
};

static struct dev_pm_ops const gps_pm_ops = {
	.resume  = v4l2_gps_resume,
	.suspend = v4l2_gps_suspend,
	.runtime_resume = v4l2_gps_runtime_resume,
	.runtime_suspend = v4l2_gps_runtime_suspend,
};

static struct platform_driver v4l2_gps_driver = {
	.probe      = v4l2_gps_probe,
	.driver     = {
		.name   = "v4l2_gps",
		.owner  = THIS_MODULE,
		.pm     = &gps_pm_ops,
	},
	.remove		= v4l2_gps_remove,
};

struct v4l2_file_operations v4l2_gps_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_gps_fh_open,
	.release	= v4l2_gps_fh_release,
	.unlocked_ioctl = video_ioctl2,
//	.read       = vb2_fop_read,
	.mmap       = v4l2_gps_mmap,
	.poll       = v4l2_gps_poll,
};

static struct vb2_ops gps_cap_qops = {
	.queue_setup        = queue_setup,
	.buf_prepare        = buffer_prepare,
	.buf_queue          = buffer_queue,
	.buf_finish         = buffer_finish,
	.start_streaming    = start_streaming,
	.stop_streaming     = stop_streaming,
	.wait_prepare       = vb2_ops_wait_prepare,
	.wait_finish        = vb2_ops_wait_finish,
};

struct v4l2_ioctl_ops v4l2_gps_ioctl_ops = {
    .vidioc_querycap		        = v4l2_gps_vidioc_querycap,
    .vidioc_enum_input		        = v4l2_gps_vidioc_enum_input,
    .vidioc_s_input                 = v4l2_gps_vidioc_s_input,
    .vidioc_g_input                 = v4l2_gps_vidioc_g_input,
    .vidioc_enum_fmt_vid_cap		= v4l2_gps_vidioc_enum_fmt_vid,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    .vidioc_enum_fmt_vid_cap_mplane = v4l2_gps_vidioc_enum_fmt_vid_mplane,
#endif
    .vidioc_g_fmt_vid_cap			= v4l2_gps_vidioc_g_fmt_vid_cap,
    .vidioc_g_fmt_vid_cap_mplane    = v4l2_gps_vidioc_g_fmt_vid_cap_mplane,
    .vidioc_try_fmt_vid_cap			= v4l2_gps_vidioc_try_fmt_vid_cap,
    .vidioc_try_fmt_vid_cap_mplane	= v4l2_gps_vidioc_try_fmt_vid_cap_mplane,
    .vidioc_s_fmt_vid_cap			= v4l2_gps_vidioc_s_fmt_vid_cap,
    .vidioc_s_fmt_vid_cap_mplane    = v4l2_gps_vidioc_s_fmt_vid_cap_mplane,

    .vidioc_enum_framesizes		    = v4l2_gps_vidioc_enum_framesizes,
    .vidioc_enum_frameintervals	    = v4l2_gps_vidioc_enum_frameintervals,
    .vidioc_queryctrl		        = v4l2_gps_vidioc_queryctrl,
    .vidioc_querymenu		        = v4l2_gps_vidioc_querymenu,
    .vidioc_s_ctrl                  = v4l2_gps_vidioc_s_ctrl,
    .vidioc_g_ctrl                  = v4l2_gps_vidioc_g_ctrl,
    .vidioc_g_parm                  = v4l2_gps_vidioc_g_parm,
    .vidioc_s_parm                  = v4l2_gps_vidioc_s_parm,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .vidioc_g_pixelaspect           = v4l2_gps_vidioc_g_pixelaspect,
#else
    .vidioc_cropcap                 = v4l2_gps_vidioc_cropcap,
    .vidioc_g_crop                  = v4l2_gps_vidioc_g_crop,
    .vidioc_s_crop                  = v4l2_gps_vidioc_s_crop,
#endif
    .vidioc_g_selection             = v4l2_gps_vidioc_g_selection,

    .vidioc_log_status              = v4l2_ctrl_log_status,
    .vidioc_subscribe_event         = v4l2_gps_vidioc_subscribe_event,
    .vidioc_unsubscribe_event       = v4l2_gps_vidioc_unsubscribe_event,
    .vidioc_reqbufs                 = v4l2_gps_vidioc_reqbufs,
    .vidioc_create_bufs             = v4l2_gps_vidioc_create_bufs,
    .vidioc_querybuf                = v4l2_gps_vidioc_querybuf,
    .vidioc_qbuf                    = v4l2_gps_vidioc_qbuf,
    .vidioc_dqbuf                   = v4l2_gps_vidioc_dqbuf,
    .vidioc_streamon                = v4l2_gps_vidioc_streamon,
    .vidioc_streamoff               = v4l2_gps_vidioc_streamoff,
    .vidioc_expbuf                  = v4l2_gps_vidioc_expbuf
};

static void capture_mem_str_init(void)
{
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60)) {
		/* Shared memory names */
		capture_mem_str[0] = "de-vt-m1"; /* y-plane */
		capture_mem_str[1] = "de-vt-m0"; /* c-plane */
		capture_mem_str[2] = "de-vt-m0";
	} else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20)){
		capture_mem_str[0] = "de-vt-m0";
		capture_mem_str[1] = "de-vt-m0";
		capture_mem_str[2] = "de-vt-m0";
	} else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26)){
		capture_mem_str[0] = "bwb1_free";
		capture_mem_str[1] = "bwb1_free";
		capture_mem_str[2] = "debug1";
		capture_mem_str[3] = "vpb";
		capture_mem_str[4] = "vpb";
	}
	else { // O24, O22, M23
		capture_mem_str[0] = "de-vt-m0";
		capture_mem_str[1] = "de-vt-m1";
		capture_mem_str[2] = "debug0";
		capture_mem_str[3] = "vpb";
		capture_mem_str[4] = "vpb";
	}
	GPS_NOTI("y['%s'] c['%s'] ext['%s']", capture_mem_str[0], capture_mem_str[1], capture_mem_str[2]);
}

int v4l2_gps_register(void *arg)
{
	int ret = 0;
    struct gps_dev      *dev;
    struct video_device *vfd;
    struct vb2_queue    *q;

	platform_driver_register(&v4l2_gps_driver);
	platform_device_register(&v4l2_gps_pdev);

	/* 
	 * Register gps debug module with log manager 
	 */
	v4l2_gps_dbg_init();

    GPS_NOTI("gps  %s\n", __func__);

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    do {
        ret = v4l2_device_register(&v4l2_gps_pdev.dev, &dev->v4l2_gps_dev);
        if(ret < 0) {
            GPS_NOTI(" gps : v4l2_device_register error[%d]\n", ret);
            return ret;
        }

        //_initConfig(dev);  //Funcationlity is not eliable to be function better to initialize here for better redability

	dev->multiplanar = 1;
	dev->num_inputs  = MAX_CAPTURE_DEVS;
	dev->pdev = &v4l2_gps_pdev;

        mutex_init(&dev->v4l2_gps_video_device_lock);
	rwlock_init(&dev->v4l2_gps_list_lock);

        q = &dev->vb_gps_cap_q;
        q->type     = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	    q->io_modes = VB2_MMAP | VB2_DMABUF;
        q->drv_priv = NULL;
        q->buf_struct_size = sizeof(struct gps_cap_buffer);
        q->ops      = &gps_cap_qops;
        q->mem_ops  = &vb2_gps_memops;
        q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,9,0)
        q->min_queued_buffers = 3;//MIN_GPS_BUF;
#else
        q->min_buffers_needed = MIN_GPS_BUF;
#endif
        q->lock = &dev->v4l2_gps_video_device_lock;
        /* this is a dummy queue which acts as a head for list of queue */
        ret = vb2_queue_init(q);
        if (ret){
            GPS_NOTI("vb2_queue init error: %d\n", ret);
            return -1;
        }

        // gps device
        vfd = &dev->v4l2_gps_video_dev;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        strscpy(vfd->name, "gps-capture-dev", sizeof(vfd->name));
#else
        strlcpy(vfd->name, "gps-capture-dev", sizeof(vfd->name));
#endif
        vfd->v4l2_dev  = &dev->v4l2_gps_dev;
        vfd->fops      = &v4l2_gps_fops;
        vfd->ioctl_ops = &v4l2_gps_ioctl_ops;
        vfd->release   = video_device_release_empty;
        vfd->queue     = &dev->vb_gps_cap_q;                //Link vb_queue with videodevice
        vfd->lock      = &dev->v4l2_gps_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_VIDEO_CAPTURE;
#endif
        video_set_drvdata(vfd, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_GPS);
#else
        ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_GPS);
#endif
	if (ret < 0) {
            GPS_NOTI("video device register error: %d\n", ret);
            return -1;
        }

        // TTV device (https://harmony.lge.com:8443/issue/browse/SICREQ-1169)
        vfd = &dev->v4l2_ttv_video_dev;
        strncpy(vfd->name, "ttv-capture-dev", sizeof(vfd->name));
        vfd->v4l2_dev  = &dev->v4l2_gps_dev;
        vfd->fops	   = &v4l2_gps_fops;
        vfd->ioctl_ops = &v4l2_gps_ioctl_ops;
        vfd->release   = video_device_release_empty;
        vfd->queue	   = &dev->vb_gps_cap_q;				//Link vb_queue with videodevice
        vfd->lock	   = &dev->v4l2_gps_video_device_lock;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_VIDEO_CAPTURE;
#endif
        video_set_drvdata(vfd, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
        ret = video_register_device(vfd, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_GPS + 1);
#else
        ret = video_register_device(vfd, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_GPS + 1);
#endif
        if (ret < 0) {
        	GPS_NOTI("video device register error: %d\n", ret);
        	return -1;
        }
        GPS_NOTI("register TTV device(%d)", V4L2_EXT_DEV_NO_GPS + 1);

		ret = gps_if_init();
		capture_mem_str_init();

    } while(0);

#ifdef WQ_IMPL
	/* Initialize the work queue */
	if (VIDEO_HighPri_WQ_Create(MODULE_GPS) != 0){
		GPS_NOTI("GPS WorkQ Creation Failed\n");
	}
#endif

	return ret;
}

static void gps_capture_notification(struct gps_dev *dev, int instId, int index)
{
	struct v4l2_event cap_event;

	memset(&cap_event, 0, sizeof(cap_event));
	cap_event.type        = V4L2_EVENT_SOURCE_CHANGE;
	//cap_event.u.data[0] = index;
	cap_event.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION;
	cap_event.id = instId;

	v4l2_event_queue(&dev->v4l2_gps_video_dev, &cap_event);
}

#ifndef WQ_IMPL
void V4l2_gps_thread(void *data)
{
	struct vb2_queue *vq = (struct vb2_queue *)data;
	struct file_vb2_q *file_q = to_file_vb2_q(vq);
	struct gps_dev    *dev      = video_drvdata(file_q->file);
	struct gps_priv   *pvt = file_prvdata(file_q->file);
	struct file *fp = pvt->filp;
	LX_DE_GPS_CTRL_T  *pgps_ctx = &pvt->gps_info.gps_ctx;
    struct gps_cap_buffer *buff = NULL;
	struct gps_instance_info gps_instance;
	ktime_t 	   t;
	struct timespec64 ts;
	UINT32 t_sec, t_msec,time_diff=0;
	int ret = RET_ERROR;
	int win_id = 0;
	int instId = 0, planeIdx = 0, nFound = 0;
	int buffIdx = 0;
	struct list_head *head = NULL, *head_old = NULL;

    GPS_NOTI("%s: fh:0x%x",__func__,fp);

	while(!pvt->thread_stop){
		if(kthread_should_stop()){
			buffIdx = 0;
			return;
		}

		GPS_NOTI("Waiting for interrupt:: 0x%x",fp);
		ret = gps_if_wait_intr(0);
		if(ret == RET_TIMEOUT){
			GPS_NOTI("Interrupt timeout:: 0x%x",fp);
			continue;
		}

		buff = NULL;
		instId = pgps_ctx->vdec_id;
		ret = gps_if_get_data(&instId, &gps_instance);
		buffIdx = gps_instance.buf_index[0];

		t  = ktime_get_real();
		ts = ktime_to_timespec64(t);
		t_sec  = ts.tv_sec;
		t_msec = ts.tv_nsec/1000000;
		time_diff = (t_sec*1000+t_msec)-(pvt->t_sec_prv*1000+pvt->t_msec_prv);
		pvt->t_sec_prv = t_sec;
		pvt->t_msec_prv = t_msec;
		pvt->max_int_cnt++;

		if(pvt->max_int_cnt != 1){
			pvt->max_wq_lat = pvt->max_wq_lat>time_diff?pvt->max_wq_lat:time_diff;
			pvt->min_wq_lat = pvt->min_wq_lat<time_diff?pvt->min_wq_lat:time_diff;
			pvt->avg_wq_lat += time_diff;
		}

		//GPS_NOTI("INTR:%d instId:%d vdec_id:%d time_diff[%u] buffIdx:%d\n",pvt->drop++,instId ,pgps_ctx->vdec_id,time_diff,buffIdx);
#if 0
		if(instId != pgps_ctx->vdec_id || buffIdx >= MAX_GPS_BUF || buffIdx < 0){
		//	GPS_NOTI("instId:%d vdec_id:%d\n", instId ,pgps_ctx->vdec_id);
			break;
		}
#else
		if(ret != RET_OK || buffIdx >= MAX_GPS_BUF || buffIdx < 0){
		//	GPS_NOTI("instId:%d vdec_id:%d\n", instId ,pgps_ctx->vdec_id);
			continue;
		}
#endif

		if((pvt->last_frm_index+1)%MAX_GPS_BUF != buffIdx)
			pvt->int_drop++; //we sud get all frames in consecutive buffers so either it is we miss interrupt or no interrupt generated

		pvt->last_frm_index = buffIdx;
		time_diff = (t_sec*1000+t_msec)-(pvt->t_frm_sec_prv*1000+pvt->t_frm_msec_prv);
		pvt->t_frm_sec_prv = t_sec;
		pvt->t_frm_msec_prv = t_msec;
		pvt->frm_int_cnt++;

		if(pvt->max_int_cnt != 1){
			pvt->max_frame_lat = pvt->max_frame_lat>time_diff?pvt->max_frame_lat:time_diff;
			pvt->min_frame_lat = pvt->min_frame_lat<time_diff?pvt->min_frame_lat:time_diff;
			pvt->avg_frame_lat += time_diff;
		}

		spin_lock(&pvt->slock);

		/*Harish: Got the availabel buffer index now.
		  TODO:  Remove the buffer from queue with index only. Now removing buffer at start only
		 */
		head = &pvt->vb_gps_cap_list;
		head_old = &pvt->vb_gps_cap_list;
		while(!list_empty(head) && (head->next != head_old)) {
			//GPS_NOTI("Index: %d",buffIdx);
			buff = (struct gps_cap_buffer *)list_entry(head->next, struct gps_cap_buffer, list);
			GPS_NOTI("BUFF Index: %d GPS Index:: %d",buff->vb.vb2_buf.index,buffIdx);

			if(buff->vb.vb2_buf.index == buffIdx){
				list_del(&buff->list);
				nFound = 1;
				break;
			}
			head = head->next;
		}

		//spin_unlock(&pvt->slock);
		if(nFound){
			/* Update the time stamp */
			//do_gettimeofday(&(buff->vb.timestamp));
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			GET_SYSCLOCK_FRM_PTS(gps_instance.pts,buff->vb.vb2_buf.timestamp)
#else
			GET_SYSCLOCK_FRM_PTS(gps_instance.pts,buff->vb.timestamp.tv_sec,buff->vb.timestamp.tv_usec)
#endif
			vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_DONE);
			gps_capture_notification(dev, buffIdx);
			GPS_NOTI("Found:: buf:0x%x Instance:: %d Index:: %d time:: %d[sec] %d[msec]",buff,instId,buffIdx,t_sec,t_msec);
		}
		else {
			drop_count[pgps_ctx->vdec_id]++;
			pvt->drop++; //Frame drop due to QBUF issue
			GPS_NOTI("FrameDrop::[Inst_%d] Index:: %d time:: %d[sec] %d[msec]",instId,buffIdx,t_sec,t_msec);
		}
		spin_unlock(&pvt->slock);
		nFound = 0;
    }
   GPS_NOTI("%s:: fh:0x%x EXIT",__func__,fp);
}

#else

void V4l2_gps_thread(struct work_struct *gps_work)
{
	struct vb2_queue *vq = NULL;
	struct gps_priv   *pvt      = container_of(gps_work, struct gps_priv, gps_noti_work);
	struct file *fp = pvt->filp;
	struct gps_dev    *dev      = video_drvdata(fp);
	LX_DE_GPS_CTRL_T  *pgps_ctx = &pvt->gps_info.gps_ctx;
    struct gps_cap_buffer *buff = NULL;
	struct gps_instance_info gps_instance;
	ktime_t 	   t;
	struct timespec64 ts;
	UINT32 t_sec, t_msec,time_diff=0;
	int ret = RET_ERROR;
	int instId = 0, nFound = 0;
	int buffIdx = 0;
	struct list_head *head = NULL, *head_old = NULL;
	int size_noti_flag = 0;

    //GPS_NOTI("%s: fh:0x%x",__func__,fp);

	vq = lookup_vb2_queue(&dev->v4l2_gps_video_dev, fp);

    do{
        buff = NULL;
		instId = pgps_ctx->vdec_id;
		ret = gps_if_get_data(&instId, &gps_instance);
		buffIdx = gps_instance.buf_index[0];

		t  = ktime_get_real();
		ts = ktime_to_timespec64(t);
		t_sec  = ts.tv_sec;
		t_msec = ts.tv_nsec/1000000;
		time_diff = (t_sec*1000+t_msec)-(pvt->t_sec_prv*1000+pvt->t_msec_prv);
		pvt->t_sec_prv = t_sec;
		pvt->t_msec_prv = t_msec;
		pvt->max_int_cnt++;

		if(pvt->max_int_cnt != 1){
			pvt->max_wq_lat = pvt->max_wq_lat>time_diff?pvt->max_wq_lat:time_diff;
			pvt->min_wq_lat = pvt->min_wq_lat<time_diff?pvt->min_wq_lat:time_diff;
			pvt->avg_wq_lat += time_diff;
		}

		//GPS_NOTI("INTR:%d instId:%d vdec_id:%d time_diff[%u] buffIdx:%d\n",pvt->drop++,instId ,pgps_ctx->vdec_id,time_diff,buffIdx);
#if 0
		if(instId != pgps_ctx->vdec_id || buffIdx >= MAX_GPS_BUF || buffIdx < 0){
		//	GPS_NOTI("instId:%d vdec_id:%d\n", instId ,pgps_ctx->vdec_id);
			break;
		}
#else
		if(ret != RET_OK || buffIdx >= MAX_GPS_BUF || buffIdx < 0){
			if(g_gps_log_level<1) GPS_NOTI("instId:%d vdec_id:%d\n", instId ,pgps_ctx->vdec_id);
			break;
		}
#endif

		if((pvt->last_frm_index+1)%MAX_GPS_BUF != buffIdx)
			pvt->int_drop++; //we sud get all frames in consecutive buffers so either it is we miss interrupt or no interrupt generated

		pvt->last_frm_index = buffIdx;
		time_diff = (t_sec*1000+t_msec)-(pvt->t_frm_sec_prv*1000+pvt->t_frm_msec_prv);
		pvt->t_frm_sec_prv = t_sec;
		pvt->t_frm_msec_prv = t_msec;
		pvt->frm_int_cnt++;

		if(pvt->max_int_cnt != 1){
			pvt->max_frame_lat = pvt->max_frame_lat>time_diff?pvt->max_frame_lat:time_diff;
			pvt->min_frame_lat = pvt->min_frame_lat<time_diff?pvt->min_frame_lat:time_diff;
			pvt->avg_frame_lat += time_diff;
		}

		spin_lock(&pvt->slock);

		/*Harish: Got the availabel buffer index now.
		  TODO:  Remove the buffer from queue with index only. Now removing buffer at start only
		 */
		head = &pvt->vb_gps_cap_list;
		head_old = &pvt->vb_gps_cap_list;
		while(!list_empty(head) && (head->next != head_old)) {
			//GPS_NOTI("Index: %d",buffIdx);
			buff = (struct gps_cap_buffer *)list_entry(head->next, struct gps_cap_buffer, list);
			//GPS_NOTI("BUFF Index: %d GPS Index:: %d",buff->vb.vb2_buf.index,buffIdx);

			if(buff->vb.vb2_buf.index == buffIdx){
				list_del(&buff->list);
				nFound = 1;
				break;
			}
			head = head->next;
		}

		//spin_unlock(&pvt->slock);
		if(nFound){
			/* Update the time stamp */
			//do_gettimeofday(&(buff->vb.timestamp));
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
			GET_SYSCLOCK_FRM_PTS(gps_instance.pts,buff->vb.vb2_buf.timestamp)
#else
			GET_SYSCLOCK_FRM_PTS(gps_instance.pts,buff->vb.timestamp.tv_sec,buff->vb.timestamp.tv_usec)
#endif

			if(pvt->cur_width !=  gps_instance.ret_w || pvt->cur_height != gps_instance.ret_h) {
				if( pvt->cur_width != 0 && pvt->cur_height != 0 )
					size_noti_flag = 1;
				else
					size_noti_flag = 0;
			}
			else
				size_noti_flag = 0;
#ifdef SUPPORT_ADAPTIVE_STREAM
			if(gps_instance.ret_w > pgps_ctx->width || \
				gps_instance.ret_h > pgps_ctx->height)
			{
				pvt->change_ctx_size = 1;
			}
#endif
			pvt->cur_width  = gps_instance.ret_w;
			pvt->cur_height = gps_instance.ret_h;
			if(size_noti_flag) {
				vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_ERROR); // to solve user's blocking(not to be zombie process)
				//vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_ERROR); // to solve user's blocking(not to be zombie process)
				//vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_ERROR); // to solve user's blocking(not to be zombie process)
				gps_capture_notification(dev, instId, buffIdx);
				DE_NOTI("id[%d] resolution changed %dx%d pts[%x]", \
					instId,gps_instance.ret_w, gps_instance.ret_h, gps_instance.pts);
			}
			else {
				vb2_buffer_done(&buff->vb.vb2_buf,VB2_BUF_STATE_DONE);
			}
			if(g_gps_log_level<1) {
				GPS_NOTI("[Inst_%d] Found:: buf:%lx Index:: %d time:: %d[msec] pts:: %d",\
							instId,(unsigned long)buff,buffIdx,time_diff,gps_instance.pts);
			}
		}
		else {
			drop_count[pgps_ctx->vdec_id]++;
			pvt->drop++; //Frame drop due to QBUF issue
			 GPS_NOTI("FrameDrop::[Inst_%d] buf:%lx Index:: %d time:: %d[msec] pts:: %d",\
				instId,(unsigned long)buff,buffIdx,time_diff,gps_instance.pts);
		}
		spin_unlock(&pvt->slock);
		nFound = 0;
    }while(0);
   if(g_gps_log_level<1) GPS_NOTI("%s:: fh:0x%lx EXIT",__func__,(unsigned long)fp);
}
#endif

int proc_gps_get_frame_drop(unsigned int id, unsigned int *count)
{
	if (!count)
		return -1;

	*count = drop_count[id];

	return 0;
}

int proc_gps(int cmd, int p1, int p2, int p3, int p4, int p5)
{
	switch(cmd)
	{
		case 0:
			g_gps_log_level = p1;
			break;
		case 1:
			//gps_proc_control(p1, p2, p3, p4, p5);
			//gps_proc_wait_intr();
			break;
		case 2: // divide control
			break;
		case 3: // freeze wait
			break;
		case 4 : 
			break;
		default:
			break;
	}
	return 0;
}

int v4l2_gps_pm_runtime_test(char* command)
{
	int ret = 0;
	//struct gps_dev *drv = platform_get_drvdata(&v4l2_gps_pdev);

	GPS_NOTI("%s", command);

	if (!strncasecmp(command, "gps_runtime_suspend", strlen("gps_runtime_suspend"))) {
		while (atomic_read(&v4l2_gps_pdev.dev.power.usage_count) > 0) {
			GPS_NOTI("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_gps_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_gps_pdev.dev);
		}
	}
	else if (!strncasecmp(command, "gps_runtime_resume", strlen("gps_runtime_resume"))) {
		while (atomic_read(&v4l2_gps_pdev.dev.power.usage_count) <= 0) {
			GPS_NOTI("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_gps_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_gps_pdev.dev);
		}
	}
	else {
		GPS_NOTI("do nothing\n");
	}

	return ret;
}

#if 0
struct source_frame_info {
	unsigned int addr_y;
	unsigned int addr_c;
	unsigned int stride;
	unsigned int width;
	unsigned int height;
	unsigned int map_type;
	unsigned int scan_type;
	unsigned int hdr_type;
	unsigned int hdr_ott_meta_addr;
	unsigned int color_sample;
};

struct target_frame_info {
	unsigned int addr_y;
	unsigned int addr_c;
	unsigned int width;
	unsigned int height;
	unsigned int format;
};

enum {
	DEIPC_RASTER_MAP = 0,
	DEIPC_HEVC_PACKED_MAP = 1,
	DEIPC_G1_DECODER_8_4_MAP = 5,
	DEIPC_AV1_FBC_MAP = 11,
	DEIPC_INVALID_MAP = 0xFF,
};
#endif
#include"gps_dma.h"

int dma_start(struct source_frame_info *src_info, struct target_frame_info *dst_info)
{
	int ret = 0;
	LX_DE_GPSDMA_IPC_T stParams;
	UINT32 crc_mode=0, crc_y=0, crc_c=0;

	stParams.dst                   = 0; // external buffer from vdec
	stParams.dpb_y_frame_base      = src_info->addr_y;
	stParams.dpb_c_frame_base      = src_info->addr_c;
	stParams.out_y_frame_base      = dst_info->addr_y;
	stParams.out_c_frame_base      = dst_info->addr_c;
	stParams.dpb_type.scan         = src_info->scan_type;
	stParams.dpb_type.dpb_map_type = src_info->map_type;
	stParams.dpb_type.cs           = src_info->color_sample;
	stParams.dpb_type.bpp          = src_info->bpp;
	stParams.dpb_width             = src_info->width;
	stParams.dpb_height            = src_info->height;
	stParams.out_width             = dst_info->width;
	stParams.out_height            = dst_info->height;
	crc_mode                       = dst_info->crc_mode;

	if (g_gps_log_level < 1) {
		GPS_NOTI("src[0x%08x,0x%08x]%dx%d,stride(%d) bpp(%d) cs(%d) scan(%d)",\
			src_info->addr_y, src_info->addr_c, src_info->width, src_info->height, src_info->stride, \
			stParams.dpb_type.bpp, src_info->color_sample, stParams.dpb_type.scan);
		GPS_NOTI("dst[0x%08x,0x%08x]fmt(%d)size(%dx%d)",\
			dst_info->addr_y, dst_info->addr_c, dst_info->format, dst_info->width, dst_info->height);
		GPS_NOTI("start dma. wait interrupt...");
	}
	ret = gps_if_dma_start(stParams, crc_mode);
	if(ret) {
		GPS_NOTI("ipc return error");
	}
	ret = VIDEO_GPSDMA_WaitVsync();

	if(ret){
		if (g_gps_log_level < 1)
			GPS_NOTI("timeout");
	}
	else {
		GPS_NOTI("done.");
		gps_if_get_crc(crc_mode, &crc_y, &crc_c);
		if(dst_info->crc_y && dst_info->crc_c && crc_y && crc_c) {
			dst_info->crc_y = crc_y;
			dst_info->crc_c = crc_c;
		}
	}

	return ret;
}
EXPORT_SYMBOL(dma_start);

