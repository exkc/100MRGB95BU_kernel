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
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/pm_runtime.h>

#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/freezer.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#ifdef ENABLE_UCR
#if 0
#include "linux/v4l2-ext/v4l2-controls-ext_id.h"
#include "linux/v4l2-ext/videodev2-ext_id.h"
#endif
#endif

#include "os_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "vpq_hwrap.h"
#include "v4l2_vpq.h"
#include "v4l2_vpq_cmn.h"
#include "v4l2_vpq_be.h"
#include "v4l2_vpq_hdr.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_vpq_latency.h"
#ifdef INCLUDE_KDRV_DE
#include "v4l2_dolby.h"
#include "vsc_fw.h"
#endif
#include "v4l2_lgsr.h"
#include "pe_kapi.h"
#include "pe_io.h"
#include "pe_cmn.h"

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
enum v4l2_vpq_ioctl_mask_type {
	V4L2_VPQ_IOCTL_MASK_NONE      = 0x00000000,

	V4L2_VPQ_IOCTL_MASK_S_CMN     = 0x00000001,
	V4L2_VPQ_IOCTL_MASK_S_PE      = 0x00000002,
	V4L2_VPQ_IOCTL_MASK_S_BE      = 0x00000004,
	V4L2_VPQ_IOCTL_MASK_S_HDR     = 0x00000008,
	V4L2_VPQ_IOCTL_MASK_S_DOVI    = 0x00000010,
	V4L2_VPQ_IOCTL_MASK_S_SLT     = 0x00000020,

	V4L2_VPQ_IOCTL_MASK_G_LAT     = 0x04000000,
	V4L2_VPQ_IOCTL_MASK_G_DOVI    = 0x08000000,
	V4L2_VPQ_IOCTL_MASK_G_HDR     = 0x10000000,
	V4L2_VPQ_IOCTL_MASK_G_BE      = 0x20000000,
	V4L2_VPQ_IOCTL_MASK_G_PE      = 0x40000000,
	V4L2_VPQ_IOCTL_MASK_G_CMN     = 0x80000000,

	V4L2_VPQ_IOCTL_MASK_ALL       = 0xFFFFFFFF,
};

#define V4L2_VPQ_APPLY_FREEZABLE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef V4L2_CID_EXT_VPQ_VIDEO_LATENCY
#define V4L2_CID_EXT_VPQ_VIDEO_LATENCY (V4L2_CID_EXT_VPQ_BASE + 37)
#endif

#ifndef V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY (V4L2_CID_EXT_VPQ_BASE + 39)
#endif

#ifndef V4L2_CID_EXT_VPQ_REGISTER_CTRL
#define V4L2_CID_EXT_VPQ_REGISTER_CTRL (V4L2_CID_EXT_VPQ_BASE + 41)
#endif

#ifndef V4L2_CID_EXT_VPQ_BASE_COMMER
#define V4L2_CID_EXT_VPQ_BASE_COMMER (V4L2_CID_USER_EXT_PQ_BASE + 0xA00)
#endif

#ifndef V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL
#define V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL (V4L2_CID_EXT_VPQ_BASE_COMMER + 2)
#endif

/* 20231121, V4L2_CID_EXT_VPQ_GAMUT_ENABLE (SICREQ-536) */
#ifndef V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE
#define V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE (V4L2_CID_EXT_VPQ_BASE + 43)
#endif

/* V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR SICREQ-575 */
#ifndef V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR (V4L2_CID_EXT_VPQ_BASE + 44)
#endif

#define V4L2_VPQ_ERR_RPT_STR_NUM	10

/* SCDCR-4006 */
#define VPQ_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::vpq\n",\
			_level,"picturequality",V4L2_EXT_DEV_NO_PQ,_g_v4l2_vpq_open_count,\
			current->group_leader->comm,current->comm,_type,_result);\
	} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#if 0	//ref.
/* https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/vidioc-g-ctrl.html */
struct v4l2_control
{
	unsigned int id;
	int value;
};

/* https://www.kernel.org/doc/html/v4.12/media/uapi/v4l/vidioc-g-ext-ctrls.html */
struct v4l2_ext_control
{
	unsigned int id;
	unsigned int size;
	unsigned int reserved2[1];
	union
	{
		int value;
		signed long long value64;
		char *string;
		unsigned char *p_u8;
		unsigned short *p_u16;
		unsigned int *p_u32;
		void *ptr;
	};
};

/* https://www.kernel.org/doc/html/v4.12/media/uapi/v4l/vidioc-g-ext-ctrls.html */
struct v4l2_ext_controls
{
	union
	{
		unsigned int ctrl_class;
		unsigned int which;
	};
	unsigned int count;
	unsigned int error_idx;
	unsigned int reserved[2];
	struct v4l2_ext_control *controls;
};
#endif

struct vpq_priv
{
	struct list_head list;

	/* vpq  */
	int vpq_poll;
	wait_queue_head_t vpq_poll_wq;
	void (*process_poll)(struct vpq_priv *v);
	struct work_struct vpq_noti_work;
	struct video_device *vpq_vdev;
	unsigned int event;
	unsigned int ev_size;
//	unsigned int ev_data;
	unsigned char ev_data[64];
	struct task_struct *check_latency_thread;
	struct task_struct *err_rpt_thread;
	int err_rpt_cnt;

	unsigned int open_idx;
	union {
		UINT32 stat32;
		struct {
		UINT32 compat      :1;// 0
		UINT32 memc_init   :1;// 1
		};
	};
};
struct vpq_priv *new_vpq_priv(void);

struct vpq_fh {
	struct v4l2_fh fh;
// need to add some private data
	struct vpq_priv *vpq_priv;
};

struct vpq_bsp_err_rpt {
	int cnt;
	char str[V4L2_VPQ_ERR_RPT_STR_NUM][64];
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
static struct v4l2_device v4l2_vpq_dev;
struct mutex v4l2_vpq_video_device_lock;

struct vpq_dev {
	struct platform_device *pdev;
#ifdef INCLUDE_KDRV_PQE_PM
	struct pqe_pm_config *pqe_pm_cfg;
	int pqe_pm_id;
#endif
};

struct vpq_bsp_err_rpt _g_vpq_bsp_err_rpt;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
//static void __exit v4l2_vpq_device_exit(void);
static int v4l2_vpq_probe(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vpq_remove(struct platform_device *pdev);
#else
static int v4l2_vpq_remove(struct platform_device *pdev);
#endif
static int v4l2_vpq_resume(struct device *dev);
static int v4l2_vpq_suspend(struct device *dev);
static int v4l2_vpq_fh_open(struct file *flie);
static int v4l2_vpq_fh_release(struct file *flie);
static int v4l2_vpq_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_vpq_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_vpq_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl);
static int vpq_set_ext_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_vpq_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int vpq_get_ext_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_vpq_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int v4l2_vpq_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap);
static int v4l2_vpq_vidioc_s_input(struct file *file, void *__fh, unsigned int i);
static int v4l2_vpq_vidioc_g_input(struct file *file, void *__fh, unsigned int *i);
static int v4l2_vpq_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub);
static int v4l2_vpq_vidioc_unsubscribe_event(struct v4l2_fh *__fh,	const struct v4l2_event_subscription *sub);
static unsigned int v4l2_vpq_poll(struct file *file, poll_table *wait);
static int v4l2_vpq_register(void *arg);
//static int v4l2_vpq_mmap(struct file *file, struct vm_area_struct *vma);
static int v4l2_vpq_runtime_resume(struct device *dev);
static int v4l2_vpq_runtime_suspend(struct device *dev);
static int vpq_check_latency_thread(void *data);
static int vpq_init_err_rpt_str(void);
static int vpq_err_rpt_thread(void *data);

int v4l2_vpq_get_ioctl_mask(char* buffer);
int v4l2_vpq_set_ioctl_mask(int mask);
int v4l2_vpq_insert_ioctl_mask_bit(int bit);
int v4l2_vpq_extract_ioctl_mask_bit(int bit);
int v4l2_vpq_init_ioctl_mask(void);
int v4l2_vpq_ready_ioctl(void);
int v4l2_vpq_get_cid_mask(char* buffer);
int v4l2_vpq_set_cid_mask(int mask);
int v4l2_vpq_pm_runtime_help(char* buffer);
int v4l2_vpq_pm_runtime_test(char* command);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct platform_device v4l2_vpq_pdev = {
	.name = "v4l2_vpq",
	.id = -1,
};

static struct dev_pm_ops const vpq_pm_ops = {
        .resume = v4l2_vpq_resume,
        .suspend = v4l2_vpq_suspend,
        .runtime_resume = v4l2_vpq_runtime_resume,
        .runtime_suspend = v4l2_vpq_runtime_suspend,
};

static struct platform_driver v4l2_vpq_driver = {
	.probe      = v4l2_vpq_probe,
	.driver     = {
		.name   = "v4l2_vpq",
		.owner  = THIS_MODULE,
		.pm     = &vpq_pm_ops,
	},
	.remove		= v4l2_vpq_remove,
};

static struct v4l2_file_operations v4l2_vpq_fops = {
   .owner          = THIS_MODULE,
   .open           = v4l2_vpq_fh_open,
   .release        = v4l2_vpq_fh_release,
   .unlocked_ioctl = video_ioctl2,
// .read = vb2_fop_read,
// .mmap = vb2_fop_mmap,
// .mmap = v4l2_vpq_mmap,
   .poll = v4l2_vpq_poll,
};

static struct v4l2_ioctl_ops v4l2_vpq_ioctl_ops = {
   .vidioc_querycap                = v4l2_vpq_vidioc_querycap,
   .vidioc_s_ctrl                  = v4l2_vpq_vidioc_s_ctrl,
   .vidioc_g_ctrl                  = v4l2_vpq_vidioc_g_ctrl,
   .vidioc_s_ext_ctrls             = v4l2_vpq_vidioc_s_ext_ctrls,
   .vidioc_g_ext_ctrls             = v4l2_vpq_vidioc_g_ext_ctrls,
   .vidioc_s_input                 = v4l2_vpq_vidioc_s_input,
   .vidioc_g_input                 = v4l2_vpq_vidioc_g_input,
   .vidioc_log_status = v4l2_ctrl_log_status,
   .vidioc_subscribe_event = v4l2_vpq_vidioc_subscribe_event,
   .vidioc_unsubscribe_event = v4l2_vpq_vidioc_unsubscribe_event,
};

static struct video_device v4l2_vpq_video_dev = {
   .v4l2_dev  = &v4l2_vpq_dev,
   .fops      = &v4l2_vpq_fops,
   .ioctl_ops = &v4l2_vpq_ioctl_ops,
   .release   = video_device_release_empty,
   .lock      = &v4l2_vpq_video_device_lock,
   .vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
   .device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

static uint _g_v4l2_vpq_ioctl_mparam = 0x0;//see v4l2_vpq_ioctl_mask_type
module_param_named(vpq_ioctl_mask, _g_v4l2_vpq_ioctl_mparam, uint, 0644);

static uint _g_v4l2_vpq_cid_mask = 0x0;
module_param_named(vpq_cid_mask, _g_v4l2_vpq_cid_mask, uint, 0644);

static unsigned int _g_v4l2_vpq_ioctl_mask = 0x0;//see v4l2_vpq_ioctl_mask_type
static int _g_v4l2_vpq_open_count = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
/* see v4l2_vpq_ioctl_mask_type */
int v4l2_vpq_get_ioctl_mask(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_CMN  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_CMN );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_PE   = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_PE  );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_BE   = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_BE  );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_HDR  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_HDR );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_DOVI = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_DOVI);
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_S_SLT  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_S_SLT);
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_LAT  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_LAT);
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_DOVI = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_DOVI);
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_HDR  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_HDR );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_BE   = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_BE  );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_PE   = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_PE  );
	len += sprintf( buffer+len, "V4L2_VPQ_IOCTL_MASK_G_CMN  = 0x%08x\n", V4L2_VPQ_IOCTL_MASK_G_CMN );
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, "curr mask = 0x%08x\n", _g_v4l2_vpq_ioctl_mask);
	len += sprintf( buffer+len, "----------------------------------------\n");
	len += sprintf( buffer+len, "< boot param >\n");
	len += sprintf( buffer+len, "set bootopts lg1k.vpq_ioctl_mask=0xf\n");
	len += sprintf( buffer+len, "cat /sys/module/lg1k/parameters/vpq_ioctl_mask\n");
	len += sprintf( buffer+len, "mparam = 0x%08x\n", _g_v4l2_vpq_ioctl_mparam);
	len += sprintf( buffer+len, "----------------------------------------\n");
	return len;
}

/* see v4l2_vpq_ioctl_mask_type */
int v4l2_vpq_set_ioctl_mask(int mask)
{
	_g_v4l2_vpq_ioctl_mask = mask;
	return 0;
}

int v4l2_vpq_insert_ioctl_mask_bit(int bit)
{
	_g_v4l2_vpq_ioctl_mask |= bit;
	return 0;
}

int v4l2_vpq_extract_ioctl_mask_bit(int bit)
{
	_g_v4l2_vpq_ioctl_mask &= (~bit);
	return 0;
}

int v4l2_vpq_init_ioctl_mask(void)
{
	int bit = 0;

	/* SLT skip init(w/ task),default,ioctl(AVTASK-890) */
	if (lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		bit |= V4L2_VPQ_IOCTL_MASK_S_SLT;
		PE_PRINT_NOTI("SLT skip ioctl\n");
	}

	bit |= V4L2_VPQ_IOCTL_MASK_S_CMN;
	bit |= V4L2_VPQ_IOCTL_MASK_S_PE;
	bit |= V4L2_VPQ_IOCTL_MASK_S_HDR;
	bit |= V4L2_VPQ_IOCTL_MASK_G_HDR;
	bit |= V4L2_VPQ_IOCTL_MASK_G_PE;
	bit |= V4L2_VPQ_IOCTL_MASK_G_CMN;

	v4l2_vpq_insert_ioctl_mask_bit(bit);
	PE_PRINT_NOTI("init ioctl mask (0x%08x)\n",_g_v4l2_vpq_ioctl_mask);
	return 0;
}

int v4l2_vpq_ready_ioctl(void)
{
	int bit = 0;

	bit |= V4L2_VPQ_IOCTL_MASK_S_CMN;
	bit |= V4L2_VPQ_IOCTL_MASK_S_PE;
	bit |= V4L2_VPQ_IOCTL_MASK_S_HDR;
	bit |= V4L2_VPQ_IOCTL_MASK_G_HDR;
	bit |= V4L2_VPQ_IOCTL_MASK_G_PE;
	bit |= V4L2_VPQ_IOCTL_MASK_G_CMN;

	v4l2_vpq_extract_ioctl_mask_bit(bit);
	v4l2_vpq_insert_ioctl_mask_bit(_g_v4l2_vpq_ioctl_mparam);
	PE_PRINT_NOTI("ready ioctl (0x%08x)(0x%08x)\n",bit,_g_v4l2_vpq_ioctl_mask);
	return 0;
}

int v4l2_vpq_get_cid_mask(char* buffer)
{
	int len = 0;
	len += sprintf( buffer+len, "--------------------------------------------\n");
	len += sprintf( buffer+len, "curr mask = 0x%08x (%d)\n", _g_v4l2_vpq_cid_mask, _g_v4l2_vpq_cid_mask);
	len += sprintf( buffer+len, "--------------------------------------------\n");
	len += sprintf( buffer+len, "< usage >\n");
	len += sprintf( buffer+len, "see cat /proc/lg/pe/cid_list\n");
	len += sprintf( buffer+len, "set bootopts lg1k.vpq_cid_mask=0x??\n");
	len += sprintf( buffer+len, "echo 0x?? > /proc/lg/pe/cid_mask\n");
	len += sprintf( buffer+len, "cat /sys/module/lg1k/parameters/vpq_cid_mask\n");
	len += sprintf( buffer+len, "--------------------------------------------\n");
	return len;
}

int v4l2_vpq_set_cid_mask(int mask)
{
	_g_v4l2_vpq_cid_mask = mask;
	return 0;
}

#if 0	//not used
static int v4l2_vpq_mmap(struct file *file, struct vm_area_struct *vma)
{
	#if 0
	int ret = RET_OK;
	unsigned long start;
	unsigned long len;
	unsigned long off = ((vma->vm_pgoff) << PAGE_SHIFT);
	unsigned int mem_base = 0;
	unsigned int mem_size = 0;
	LX_PE_IPC_SYSTEM_MEM_T lgsr_mem[11];

	PE_PRINT_NOTI("%s entered \n", __func__);

	ret = PE_LGSR_GetMemInfo(lgsr_mem);
	if (ret != RET_OK){
		PE_PRINT_ERROR("PE_LGSR_GetMemInfo() error.\n");
		return -EINVAL;
	}
	mem_base = lgsr_mem[0].base;
	mem_size = lgsr_mem[0].size;
	if (!mem_base){
		PE_PRINT_ERROR("mem_base(%d) error.\n",mem_base);
		return -EINVAL;
	}

	if (!mem_size){
		PE_PRINT_ERROR("mem_size(%d) error.\n",mem_size);
		return -EINVAL;
	}

	start = mem_base & PAGE_MASK; // or 0
	len = PAGE_ALIGN((start & ~PAGE_MASK) + mem_size);

	PE_PRINT_NOTI("MMAP : start - %08lx, len - %08lx, off - %08lx ", start, len, off);

	if ((vma->vm_end - vma->vm_start + off) > len)
	{
		PE_PRINT_ERROR("length is over. start : %lx end : %lx offset : %lx len : %lx\n",
		vma->vm_start, vma->vm_end, off, len);

		return -EINVAL;
	}

	off += start;

	PE_PRINT_NOTI("MMAP : start - %08lx, len - %08lx, off - %08lx ", start, len, vma->vm_pgoff);

	vma->vm_pgoff = off >> PAGE_SHIFT;
	vma->vm_flags |= VM_IO;
	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	return io_remap_pfn_range(vma,vma->vm_start,off >> PAGE_SHIFT,vma->vm_end - vma->vm_start,vma->vm_page_prot);
	#else
	return 0;
	#endif
}
#endif

int v4l2_vpq_device_init(void)
{
	PE_PRINT_NOTI("vpq  %s\n", __func__);

	//video_set_drvdata(&v4l2_vpq_video_dev, &vpq_pdev);
	v4l2_vpq_register(NULL);
	//v4l2_lgsr_register(NULL);

	return 0;
}

#if 0	//not used
static void __exit v4l2_vpq_device_exit(void)
{
	PE_PRINT_NOTI("vpq  %s\n", __func__);

	platform_device_unregister(&v4l2_vpq_pdev);
	platform_driver_unregister(&v4l2_vpq_driver);
}
#endif

#ifdef INCLUDE_KDRV_PQE_PM
static int v4l2_vpq_pqe_pm_cb(int action)
{
	PE_PRINT_NOTI("(%d) start\n",action);

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
		/* stop thread */
		PE_CMN_ResumeModule(0);
		/* ipc block */
		v4l2_vpq_set_ioctl_mask(V4L2_VPQ_IOCTL_MASK_ALL);
		/* unregister handler,ipc */
		//vpq_hwrap_uninitialize();//no need for fw resume
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
		/* TODO : start apb access */
		/* register handler,ipc, start thread */
		v4l2_vpq_set_ioctl_mask(V4L2_VPQ_IOCTL_MASK_NONE);
		//vpq_hwrap_initialize(1);//no need for fw resume
		PE_CMN_ResumeModule(1);
	}

	PE_PRINT_NOTI("(%d) end\n",action);
	return 0;
}

static struct pqe_pm_config v4l2_vpq_pqe_pm_cfg = {
	.name = "v4l2_vpq",
	.opt = PQE_PM_OPT_NONE,
	.order = 50,
	.callback = v4l2_vpq_pqe_pm_cb,
};
#endif

static int v4l2_vpq_probe(struct platform_device *pdev)
{
	struct vpq_dev *drv;

	PE_PRINT_NOTI("start\n");

	v4l2_vpq_init_ioctl_mask();

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (drv)
	{
		drv->pdev = &v4l2_vpq_pdev;
#ifdef INCLUDE_KDRV_PQE_PM
		drv->pqe_pm_cfg = &v4l2_vpq_pqe_pm_cfg;
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
#endif
		platform_set_drvdata(pdev, drv);
	}
	//else	return -ENOMEM;
	vpq_init_err_rpt_str();

	do {
		#ifdef INCLUDE_KDRV_DE
		if (0 != vsc_fw_get_user_bin_num()) break;
		#endif
		vpq_hwrap_initialize(0);
	} while(0);

	PE_PRINT_NOTI("end\n");
	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_vpq_remove(struct platform_device *pdev)
#else
static int v4l2_vpq_remove(struct platform_device *pdev)
#endif
{
	struct vpq_dev *drv = platform_get_drvdata(pdev);

	PE_PRINT_NOTI("start\n");

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_unregister(drv->pqe_pm_id);
#endif
		kfree(drv);
	}

	pm_runtime_disable(&pdev->dev);

	PE_PRINT_NOTI("end\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_vpq_resume(struct device *dev)
{
	PE_PRINT_NOTI("%s\n", __func__);
    return 0;
}

static int v4l2_vpq_suspend(struct device *dev)
{
	PE_PRINT_NOTI("%s\n", __func__);
    return 0;
}

static int v4l2_vpq_runtime_resume(struct device *dev)
{
	struct vpq_dev *drv = dev_get_drvdata(dev);

	PE_PRINT_NOTI("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_resume(drv->pqe_pm_id);
#endif
	}

	VPQ_PM_INFO("info","resume","ok");

	return 0;
}

static int v4l2_vpq_runtime_suspend(struct device *dev)
{
	struct vpq_dev *drv = dev_get_drvdata(dev);

	PE_PRINT_NOTI("start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_suspend(drv->pqe_pm_id);
#endif
	}

	VPQ_PM_INFO("info","suspend","ok");

	return 0;
}

int v4l2_vpq_pm_runtime_help(char* buffer)
{
	int len = 0;
	struct vpq_dev *drv = platform_get_drvdata(&v4l2_vpq_pdev);

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "dev name : %s\n",v4l2_vpq_pdev.name);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- open_count : %d\n",_g_v4l2_vpq_open_count);
	len += sprintf( buffer+len, "- vdev node name : %s\n",video_device_node_name(&v4l2_vpq_video_dev));
#ifdef INCLUDE_KDRV_PQE_PM
	if (!drv)					len += sprintf( buffer+len, "drv null\n");
	else if (!drv->pqe_pm_cfg)	len += sprintf( buffer+len, "pqe_pm_cfg null\n");
	else						len += sprintf( buffer+len, "pqe_pm_name : %s, pqe_pm_id : %d\n",drv->pqe_pm_cfg->name,drv->pqe_pm_id);
#endif
	len += sprintf( buffer+len, "- usage_count : %d\n",atomic_read(&v4l2_vpq_pdev.dev.power.usage_count));
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo runtime_suspend > /proc/lg/pe/pm_test\n");
	len += sprintf( buffer+len, "echo runtime_resume > /proc/lg/pe/pm_test\n");
	len += sprintf( buffer+len, "- others\n");
	len += sprintf( buffer+len, "cat /sys/devices/platform/v4l2_vpq/power/runtime_status\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int v4l2_vpq_pm_runtime_test(char* command)
{
	int ret = 0;
	struct vpq_dev *drv = platform_get_drvdata(&v4l2_vpq_pdev);

	if (!strncasecmp(command, "pm_runtime_put", strlen("pm_runtime_put"))) {
		ret = pm_runtime_put(&v4l2_vpq_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_put : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get_sync", strlen("pm_runtime_get_sync"))) {
		ret = pm_runtime_get_sync(&v4l2_vpq_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_get_sync : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_get", strlen("pm_runtime_get"))) {
		ret = pm_runtime_get(&v4l2_vpq_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_get : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_suspend", strlen("pm_runtime_suspend"))) {
		ret = pm_runtime_suspend(&v4l2_vpq_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_suspend : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "pm_runtime_resume", strlen("pm_runtime_resume"))) {
		ret = pm_runtime_resume(&v4l2_vpq_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_resume : ret:%d\n",ret);
	}
#ifdef INCLUDE_KDRV_PQE_PM
	else if (!strncasecmp(command, "pqe_pm_register", strlen("pqe_pm_register"))) {
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
		PE_PRINT_NOTI("pqe_pm_register : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_suspend", strlen("pqe_pm_request_suspend"))) {
		ret = pqe_pm_request_suspend(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_request_suspend : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_request_resume", strlen("pqe_pm_request_resume"))) {
		ret = pqe_pm_request_resume(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_request_resume : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "pqe_pm_unregister", strlen("pqe_pm_unregister"))) {
		ret = pqe_pm_unregister(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_unregister : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
#endif
	else if (!strncasecmp(command, "runtime_suspend", strlen("runtime_suspend"))) {
		while (atomic_read(&v4l2_vpq_pdev.dev.power.usage_count) > 0) {
			PE_PRINT_NOTI("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_vpq_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_vpq_pdev.dev);
			//msleep(1);
		}
	}
	else if (!strncasecmp(command, "runtime_resume", strlen("runtime_resume"))) {
		while (atomic_read(&v4l2_vpq_pdev.dev.power.usage_count) <= 0) {
			PE_PRINT_NOTI("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_vpq_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_vpq_pdev.dev);
			//msleep(1);
		}
	}
	else {
		printk("do nothing\n");
	}

	return ret;
}

static int vpq_notification(struct vpq_priv *p)
{
	struct v4l2_event evt;

//	if(p->ev_size > 64) return -1;

	memset(&evt, 0, sizeof(evt));
	evt.type = V4L2_EVENT_CTRL;
	evt.id	 = p->event;

	//if (p->event == V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR)	DE_NOTI("[%d][%s]\n",p->ev_size,p->ev_data);

	memcpy(evt.u.data, p->ev_data, p->ev_size);
	v4l2_event_queue(p->vpq_vdev, &evt);

	return 0;
}

static void process_poll(struct vpq_priv *p)
{
	//queue_work(system_wq, &p->vsc_noti_work);
	vpq_notification(p);
}

struct vpq_priv *new_vpq_priv(void)
{
	struct vpq_priv *p;

	p = kcalloc(1, sizeof(struct vpq_priv), GFP_KERNEL);
	if(!p)
	{
		PE_PRINT_ERROR("alloc error for vpq priv.");
		return NULL;
	}
	INIT_LIST_HEAD(&p->list);
	init_waitqueue_head(&p->vpq_poll_wq);

	return p;
}

static int v4l2_vpq_fh_open(struct file *flie)
{
	int ret=0;
	int ret0=0;
	static unsigned int open_idx = 1;
	struct vpq_dev *dev  = video_drvdata(flie);
	struct vpq_fh *fh;
	struct vpq_priv *p;

	PE_PRINT_NOTI("vpq: open (%s-%s) (open_idx:%d)\n",current->group_leader->comm,current->comm,open_idx);

	ret0 = pm_runtime_get_sync(&dev->pdev->dev);
	PE_PRINT_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct vpq_fh), GFP_KERNEL);
	if (!fh)
	{
		PE_PRINT_NOTI("vpq: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	p = new_vpq_priv();
	if(!p)
	{
		PE_PRINT_ERROR("alloc of vsc priv failed");
		ret = -ENOMEM;
		goto fail_fh;
	}

	p->check_latency_thread = NULL;
	p->err_rpt_thread = NULL;
	p->err_rpt_cnt = -1;

	p->process_poll = process_poll;
	p->vpq_vdev = video_devdata(flie);
	p->open_idx = open_idx++;
	fh->vpq_priv = p;

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* increment open counter */
	_g_v4l2_vpq_open_count++;
	VPQ_PM_INFO("info","open","ok");

	return ret;

fail_fh:
	kfree(fh);
	return ret;

}

static int v4l2_vpq_fh_release(struct file *flie)
{
	int ret=0;
	int ret0=0;
	struct vpq_dev *dev  = video_drvdata(flie);
	//struct vpq_fh *fh = flie->private_data;
	struct vpq_fh *fh = flie->private_data;
	struct vpq_priv *p = fh->vpq_priv;
	struct video_device *vpq_vdev;

	PE_PRINT_NOTI("vpq: close (%s-%s) (open_idx:%d)\n",current->group_leader->comm,current->comm,p->open_idx);

	if(p->check_latency_thread) {
		send_sig(SIGUSR1, p->check_latency_thread, 0); // send signal to thread
		kthread_stop(p->check_latency_thread);
		p->check_latency_thread = NULL;
	}
	if(p->err_rpt_thread) {
		send_sig(SIGUSR1, p->err_rpt_thread, 0); // send signal to thread
		kthread_stop(p->err_rpt_thread);
		p->err_rpt_thread = NULL;
	}
	vpq_vdev = video_devdata(flie);
	if(vpq_vdev)
	{
		kfree(fh->vpq_priv);
		fh->vpq_priv = NULL;
	}

	v4l2_fh_release(flie);

	ret0 = pm_runtime_put(&dev->pdev->dev);
	PE_PRINT_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	/* decrement open counter */
	_g_v4l2_vpq_open_count--;
	VPQ_PM_INFO("info","close","ok");

	return ret;
}

static int v4l2_vpq_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	struct vpq_fh *fh = (struct vpq_fh *)file->private_data;
	struct vpq_priv *p = fh->vpq_priv;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	PE_PRINT_TRACE("id:0x%x(%s), value:%d, mask:0x%08x\n",ctrl->id,vpq_ctrl_id_to_str(ctrl->id),ctrl->value,_g_v4l2_vpq_ioctl_mask);

	if (_g_v4l2_vpq_ioctl_mask == V4L2_VPQ_IOCTL_MASK_ALL) {
		//PE_PRINT_NOTI("cid_mask(all) skip\n");
		return 0;
	}

	/* SLT skip init(w/ task),default,ioctl(AVTASK-890) */
	if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_SLT)
	{
		PE_PRINT_NOTI("SLT skip ioctl (id:0x%08x)\n",ctrl->id);
		return 0;
	}

	if (_g_v4l2_vpq_cid_mask == ctrl->id)
	{
		PE_PRINT_TRACE("cid_mask(%s) skip\n",vpq_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_MEMC_INIT:
			if (p->memc_init == 1 && ctrl->value != 0) {
				char systemd_opt[24];
				OS_ScanKernelCmdline("systemd.unit=%s", systemd_opt);
				if (strstr(systemd_opt,"socts.target")) {
					PE_PRINT_NOTI("ret = -EBUSY\n");
					ret = -EBUSY;
				}
			}
			PE_PRINT_NOTI("set memc_init:%d -> value:%d (open_idx:%d) (ret:%d)\n",p->memc_init,ctrl->value,p->open_idx,ret);
			p->memc_init = (ctrl->value!=0)? 1:0;
			break;
		case V4L2_CID_EXT_VPQ_INIT:
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		case V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_PE)	break;
			ret = v4l2_vpq_vidioc_s_ctrl_pe(file, __fh, ctrl);
			break;
		case V4L2_CID_EXT_LED_DB_IDX:
		case V4L2_CID_EXT_LED_EN:
		case V4L2_CID_EXT_LED_FIN:
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		case V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT:
		case V4L2_CID_EXT_LED_ABI:
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_BE)	break;
#ifdef INCLUDE_KDRV_BE
			ret = v4l2_vpq_vidioc_s_ctrl_be(file, __fh, ctrl);
#endif
			break;
		case V4L2_CID_EXT_HDR_INV_GAMMA:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_HDR)	break;
			ret = v4l2_vpq_vidioc_s_ctrl_hdr(file, __fh, ctrl);
			break;
		case V4L2_CID_EXT_AIPQ_SQM_MODE:
		case V4L2_CID_EXT_AIPQ_SR_MODE:
			ret = 0;
			break;
		case V4L2_CID_EXT_DOLBY_PD_CTRL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_DOVI) break;
#ifdef INCLUDE_KDRV_DE
			if (vpq_v4l2_set_ctrl_dolby(ctrl) != 0) {
				PE_PRINT_ERROR("vpq:id 0x%x set failed",ctrl->id);
				ret = -EINVAL;
			}
#endif
			break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_vpq_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	struct vpq_fh *fh = (struct vpq_fh *)file->private_data;
	struct vpq_priv *p = fh->vpq_priv;
	//struct vpq_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	PE_PRINT_TRACE("id:0x%x(%s), value:%d, mask:0x%08x\n",ctrl->id,vpq_ctrl_id_to_str(ctrl->id),ctrl->value,_g_v4l2_vpq_ioctl_mask);

	if (_g_v4l2_vpq_ioctl_mask == V4L2_VPQ_IOCTL_MASK_ALL) {
		//PE_PRINT_NOTI("cid_mask(all) skip\n");
		return 0;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_MEMC_INIT:
			ctrl->value = p->memc_init;
			PE_PRINT_NOTI("get value:%d (open_idx:%d)\n",ctrl->value,p->open_idx);
			break;
		case V4L2_CID_EXT_VPQ_INIT:
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
		case V4L2_CID_EXT_VPQ_NOISE_LEVEL:
		case V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_PE)	break;
			ret = v4l2_vpq_vidioc_g_ctrl_pe(file, __fh, ctrl);
			break;
		case V4L2_CID_EXT_LED_DB_IDX:
		case V4L2_CID_EXT_LED_EN:
		case V4L2_CID_EXT_LED_FIN:
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		case V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT:
		case V4L2_CID_EXT_LED_ABI:
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_BE)	break;
#ifdef INCLUDE_KDRV_BE
			ret = v4l2_vpq_vidioc_g_ctrl_be(file, __fh, ctrl);
#endif
			break;
		case V4L2_CID_EXT_HDR_INV_GAMMA:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_HDR)	break;
			ret = v4l2_vpq_vidioc_g_ctrl_hdr(file, __fh, ctrl);
			break;
		case V4L2_CID_EXT_VPQ_VIDEO_LATENCY:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_LAT)	break;
			ret = v4l2_vpq_vidioc_g_ctrl_latency(file, __fh, ctrl);
			break;
		default:
			ret = -EINVAL;
	}

	return 0;
}

static int v4l2_vpq_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
			break;
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		case V4L2_CID_EXT_VPQ_PSP:
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		case V4L2_CID_EXT_VPQ_HISTO_DATA:
		case V4L2_CID_EXT_VPQ_DB_DATA:
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
			ret = v4l2_vpq_compat_vidioc_ext_ctrls_pe(ctrl);
			break;
		case V4L2_CID_EXT_LED_INIT:
		case V4L2_CID_EXT_LED_DEMOMODE:
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		case V4L2_CID_EXT_LED_APL_DATA:
		case V4L2_CID_EXT_LED_BPL_DATA:
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		case V4L2_CID_EXT_VPQ_LUMINANCE_BOOST:
		case V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT:
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		case V4L2_CID_EXT_LED_DB_DATA:
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		case V4L2_CID_EXT_VPQ_GAMUT_3DLUT:
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		case V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO:
//#ifdef ENABLE_UCR
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
//#endif
//#ifdef ENABLE_EOTF_OETF_LUT
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
//#endif
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_MCC_DATA:
		case V4L2_CID_EXT_VPQ_MCC_LUT:
#ifdef INCLUDE_KDRV_BE
			ret = v4l2_vpq_compat_vidioc_ext_ctrls_be(ctrl);
#endif
			break;
		case V4L2_CID_EXT_HDR_EOTF:
		case V4L2_CID_EXT_HDR_TONEMAP:
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		case V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL:
			ret = v4l2_vpq_compat_vidioc_ext_ctrls_hdr(ctrl);
			break;
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
			ret = v4l2_vpq_compat_vidioc_ext_ctrls_cmn(ctrl);
			break;
		case V4L2_CID_EXT_DOLBY_CFG_PATH:
		case V4L2_CID_EXT_DOLBY_PICTURE_MODE:
		case V4L2_CID_EXT_DOLBY_PICTURE_MENU:
		case V4L2_CID_EXT_DOLBY_SW_VERSION:
		case V4L2_CID_EXT_DOLBY_GD_DELAY:
		case V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT:
		case V4L2_CID_EXT_DOLBY_CONTENTS_TYPE:
			#ifdef INCLUDE_KDRV_DE
			ret = vpq_v4l2_compat_ext_ctrl_dolby(ctrl);
			#endif
			break;
		default:
			break;
	}

	return ret;
}

static int vpq_set_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	/* SLT skip init(w/ task),default,ioctl(AVTASK-890) */
	if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_SLT)
	{
		PE_PRINT_NOTI("SLT skip ioctl (id:0x%08x)\n",ctrl->id);
		return 0;
	}

	if (_g_v4l2_vpq_cid_mask == ctrl->id)
	{
		PE_PRINT_TRACE("cid_mask(%s) skip\n",vpq_ctrl_id_to_str(ctrl->id));
		return 0;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_vpq_compat_vidioc_ext_ctrls(ctrl);
	}
	#endif

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
			break;
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		case V4L2_CID_EXT_VPQ_PSP:
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		case V4L2_CID_EXT_VPQ_DB_DATA:
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_PE)	break;
			ret = vpq_set_ext_ctrl_pe(ctrl);
			break;
		case V4L2_CID_EXT_LED_INIT:
		case V4L2_CID_EXT_LED_DEMOMODE:
		case V4L2_CID_EXT_LED_DB_DATA:
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		case V4L2_CID_EXT_LED_BPL_DATA:
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		case V4L2_CID_EXT_VPQ_GAMUT_3DLUT:
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		case V4L2_CID_EXT_VPQ_LUMINANCE_BOOST:
		case V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT:
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
//#ifdef ENABLE_UCR
		case V4L2_CID_EXT_ID_VBE_UCR_DATA:
//#endif
//#ifdef ENABLE_EOTF_OETF_LUT
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
//#endif
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_MCC_DATA:
		case V4L2_CID_EXT_VPQ_MCC_LUT:

			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_BE)	break;
#ifdef INCLUDE_KDRV_BE
			ret = vpq_set_ext_ctrl_be(ctrl);
#endif
			break;
		case V4L2_CID_EXT_HDR_3DLUT:
		case V4L2_CID_EXT_HDR_EOTF:
		case V4L2_CID_EXT_HDR_OETF:
		case V4L2_CID_EXT_HDR_TONEMAP:
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_HDR)	break;
			ret = vpq_set_ext_ctrl_hdr(ctrl);
			break;
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_CMN)	break;
			ret = vpq_set_ext_ctrl_cmn(ctrl);
			break;
		case V4L2_CID_EXT_DOLBY_CFG_PATH:
		case V4L2_CID_EXT_DOLBY_PICTURE_MODE:
		case V4L2_CID_EXT_DOLBY_PICTURE_MENU:
		case V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT:
		case V4L2_CID_EXT_DOLBY_GD_DELAY:
		case V4L2_CID_EXT_DOLBY_CONTENTS_TYPE:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_S_DOVI)	break;
			#ifdef INCLUDE_KDRV_DE
			ret = vpq_v4l2_set_ext_ctrl_dolby(ctrl);
			#endif
			break;
		default:
			return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_vpq_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct vpq_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			PE_PRINT_TRACE("(%s)(%s) [%d]id:0x%x(%s) mask:0x%08x\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,vpq_ctrl_id_to_str(ctrl->id),_g_v4l2_vpq_ioctl_mask);
			#endif

			if (_g_v4l2_vpq_ioctl_mask == V4L2_VPQ_IOCTL_MASK_ALL) {
				//PE_PRINT_NOTI("cid_mask(all) skip\n");
				continue;
			}

			ret = vpq_set_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int vpq_get_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_vpq_compat_vidioc_ext_ctrls(ctrl);
	}
	#endif

	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_SUPER_RESOLUTION:
			break;
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_SHARPNESS:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT:
		case V4L2_CID_EXT_VPQ_CM_DB_DATA:
		case V4L2_CID_EXT_VPQ_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE:
		case V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA:
		case V4L2_CID_EXT_VPQ_PSP:
		case V4L2_CID_EXT_VPQ_OBC_LUT:
		case V4L2_CID_EXT_VPQ_OBC_CTRL:
		case V4L2_CID_EXT_VPQ_DECONTOUR:
		case V4L2_CID_EXT_VPQ_HISTO_DATA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT:
		case V4L2_CID_EXT_VPQ_OBC_DATA:
		case V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_PE)	break;
			ret = vpq_get_ext_ctrl_pe(ctrl);
			break;
		case V4L2_CID_EXT_LED_APL_DATA:
		case V4L2_CID_EXT_LED_BPL_DATA:
		case V4L2_CID_EXT_VPQ_GAMMA_DATA:
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		case V4L2_CID_EXT_VPQ_OD_TABLE:
		case V4L2_CID_EXT_VPQ_OD_EXTENSION:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		case V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE:
		case V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA:
		case V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO:
		case V4L2_CID_EXT_VPQ_MCC_DATA:
		case V4L2_CID_EXT_VPQ_MCC_LUT:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_BE)	break;
#ifdef INCLUDE_KDRV_BE
			ret = vpq_get_ext_ctrl_be(ctrl);
#endif
			break;
		case V4L2_CID_EXT_HDR_3DLUT:
		case V4L2_CID_EXT_HDR_EOTF:
		case V4L2_CID_EXT_HDR_OETF:
		case V4L2_CID_EXT_HDR_TONEMAP:
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
		case V4L2_CID_EXT_HDR_PIC_INFO:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE:
		case V4L2_CID_EXT_VPQ_READ_INPUT_PIXEL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_HDR)	break;
			ret = vpq_get_ext_ctrl_hdr(ctrl);
			break;
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		case V4L2_CID_EXT_VPQ_EXTRA_PATTERN:
		case V4L2_CID_EXT_VPQ_REGISTER_CTRL:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_CMN)	break;
			ret = vpq_get_ext_ctrl_cmn(ctrl);
			break;
		case V4L2_CID_EXT_DOLBY_CFG_PATH:
		case V4L2_CID_EXT_DOLBY_SW_VERSION:
		case V4L2_CID_EXT_DOLBY_PICTURE_MODE:
		case V4L2_CID_EXT_DOLBY_PICTURE_MENU:
		case V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT:
		case V4L2_CID_EXT_DOLBY_GD_DELAY:
		case V4L2_CID_EXT_DOLBY_CONTENTS_TYPE:
			if (_g_v4l2_vpq_ioctl_mask & V4L2_VPQ_IOCTL_MASK_G_DOVI)	break;
			#ifdef INCLUDE_KDRV_DE
			ret = dolby_get_ext_ctrl(ctrl);
			#endif
			break;
		default:
			return -EINVAL;
	}
	return 0;
}


static int v4l2_vpq_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct vpq_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			PE_PRINT_TRACE("(%s)(%s) [%d]id:0x%x(%s) mask:0x%08x\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,vpq_ctrl_id_to_str(ctrl->id),_g_v4l2_vpq_ioctl_mask);
			#endif

			if (_g_v4l2_vpq_ioctl_mask == V4L2_VPQ_IOCTL_MASK_ALL) {
				//PE_PRINT_NOTI("cid_mask(all) skip\n");
				continue;
			}

			ret = vpq_get_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;
}

static int v4l2_vpq_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	//struct vpq_fh *fh = __fh;

	strncpy(cap->card, "v4l2_vpq", sizeof(cap->card)-1);
	//strncpy(cap->driver, "v4l2_vpq", sizeof(cap->driver)-1);

	if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O24)){
		strncpy(cap->driver, "o24", sizeof(cap->driver)-1);//SOCTSSIC-82109
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_M23)){
		strncpy(cap->driver, "m23", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O22)){
		strncpy(cap->driver, "o22n", sizeof(cap->driver)-1);//o22->o22n request by SCDCR-5296
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_E60)){
		strncpy(cap->driver, "e60", sizeof(cap->driver)-1);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(),LX_CHIP_O20)){
		strncpy(cap->driver, "o20", sizeof(cap->driver)-1);
	}
	else { // default
		strncpy(cap->driver, "m16p3", sizeof(cap->driver)-1);
	}

	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	return 0;

}

static int v4l2_vpq_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	//struct vpq_fh *fh = __fh;
	//int ret;

	PE_PRINT_NOTI("vpq: set input %d\n", i);

	return 0;
}

static int v4l2_vpq_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	//struct vpq_fh *fh = __fh;
	//int ret;

	PE_PRINT_NOTI("vpq: get input %d\n", *i);

	return 0;
}

static int v4l2_vpq_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub)
{
	int err = 0;
	struct vpq_fh *pvpq_fh = container_of(__fh, struct vpq_fh, fh);
	struct vpq_priv *p = pvpq_fh->vpq_priv;

	PE_PRINT_NOTI("type 0x%x, id 0x%x\n", sub->type, sub->id);

//	switch (sub->type)
	if (!__fh)	{PE_PRINT_ERROR("__fh null\n"); return -EINVAL;}
	if (!sub)	{PE_PRINT_ERROR("sub null\n");	return -EINVAL;}
	if (!pvpq_fh){PE_PRINT_ERROR("pvpq_fh null\n");return -EINVAL;}

	PE_PRINT_NOTI("vpq type 0x%x, id 0x%x \n",sub->type,sub->id);

	if(sub->id == V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY)
	{
		if(!p->check_latency_thread) {
			p->check_latency_thread = kthread_run(vpq_check_latency_thread, p, "%s", "latency");
			if (IS_ERR(p->check_latency_thread)) {
				err = PTR_ERR(p->check_latency_thread);
				PE_PRINT_ERROR("kthread_run err(%d)\n",err);
				p->check_latency_thread = NULL;
				return err;
			}
		}
	}
	else if (sub->id == V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR)
	{
		if(!p->err_rpt_thread) {
			p->err_rpt_thread = kthread_run(vpq_err_rpt_thread, p, "vpq_err_rpt");
		}
	}
	return v4l2_event_subscribe(__fh, sub, 32, NULL);
}

static int v4l2_vpq_vidioc_unsubscribe_event(struct v4l2_fh *__fh,	const struct v4l2_event_subscription *sub)
{
//	int ret = 0;
	struct vpq_fh *pvpq_fh = container_of(__fh, struct vpq_fh, fh);
	struct vpq_priv *p = pvpq_fh->vpq_priv;

	if(sub->id == V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY)
	{
		if(p->check_latency_thread) {
			send_sig(SIGUSR1, p->check_latency_thread, 0); // send signal to thread
			kthread_stop(p->check_latency_thread);
			p->check_latency_thread = NULL;
		}
	}
	else if (sub->id == V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR)
	{
		if(p->err_rpt_thread) {
			send_sig(SIGUSR1, p->err_rpt_thread, 0); // send signal to thread
			kthread_stop(p->err_rpt_thread);
			p->err_rpt_thread = NULL;
		}
	}
	return v4l2_event_unsubscribe(__fh, sub);
}

static unsigned int v4l2_vpq_poll(struct file *file, poll_table *wait)
{
	struct vpq_fh *fh = (struct vpq_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	PE_PRINT_NOTI("vpq:req_events 0x%lx\n", req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
		/*
		poll_wait(file, &p->vpq_poll_wq, wait);

		if (p->vpq_poll & POLLIN)
			rc |= POLLIN;
		if (p->vpq_poll & POLLOUT)
			rc |= POLLOUT;
		if (p->vpq_poll & POLLERR)
			rc |= POLLERR;
			*/
	}

	PE_PRINT_NOTI("vpq: rc 0x%x\n", rc);

	return rc;
}

char *vpq_ctrl_id_to_str(int id)
{
	#define VPQ_CASE_ID_TO_STR(_x)		case (_x):return #_x
    #define V4L2_CID_EXT_HLG_Y_GAIN_TBL V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL

    switch (id)
	{
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_INIT                       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_DB_IDX                     );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_DEMOMODE                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_EN                         );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_FIN                        );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_DB_DATA                    );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_CONTROL_SPI                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_APL_DATA                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_BPL_DATA                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_MEMC_INIT                      );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_MEMC_LOW_DELAY_MODE            );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_MEMC_MOTION_COMP               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_MEMC_MOTION_PRO                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_LED_ABI                        );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_INV_GAMMA                  );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_PIC_INFO                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_3DLUT                      );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_EOTF                       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_OETF                       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_TONEMAP                    );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HDR_COLOR_CORRECTION           );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_HLG_Y_GAIN_TBL                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_CFG_PATH                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_PICTURE_MODE             );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_PICTURE_MENU             );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_SW_VERSION               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_AMBIENT_LIGHT			   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_CONTENTS_TYPE			   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_PWM_RATIO                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_DOLBY_GD_DELAY                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_INIT                       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_PICTURE_CTRL               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_SHARPNESS                  );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_HISTO_DATA                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST           );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_LUT       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_CM_DB_DATA                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_NOISE_REDUCTION            );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_MPEG_NOISE_REDUCTION       );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_BYPASS_BLOCK               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_BLACK_LEVEL                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_GAMMA_DATA                 );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_SUPER_RESOLUTION           );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_NOISE_LEVEL                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_LOW_DELAY_MODE             );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_BYPASS_LUT);
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN);
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_TESTPATTERN                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_COLORTEMP_DATA             );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_REAL_CINEMA                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_GAMUT_3DLUT                );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_MULTIWINDOW_GAMUT_ENABLE   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OD_TABLE                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OD_EXTENSION               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_LOCALCONTRAST_TABLE        );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_LOCALCONTRAST_DATA         );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_PSP                        );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_GAMUT_MATRIX_PRE           );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST          );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_PQ_MODE_INFO               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DEGAMMA_DATA               );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_LUMINANCE_BOOST            );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_PHDR_APL_GAIN_LUT          );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OBC_DATA                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OBC_LUT                    );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OBC_CTRL                   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DECONTOUR                  );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_EXTRA_PATTERN              );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_STEREO_FACE_CTRL           );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_VIDEO_PATTERN_INFO         );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DB_DATA                    );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DELTA_BRIGHTNESS_CONPENSATION_LUT);
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_OLED_APL_MAX_WEIGHT);
//#ifdef ENABLE_UCR
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_ID_VBE_UCR_DATA           	   );
//#endif
//#ifdef ENABLE_EOTF_OETF_LUT
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_DEGAMMA_REGAMMA            );
//#endif
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_FRAME_DELAY_MODE		   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_REGISTER_CTRL         	   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_MCC_DATA    	     	   );
		VPQ_CASE_ID_TO_STR(V4L2_CID_EXT_VPQ_MCC_LUT    	  		   	   );
		default:                            return "V4L2_CID_EXT_UNKOWN";
	}
}

static int v4l2_vpq_register(void *arg)
{
	int ret;
	struct vpq_dev *dev;

	PE_PRINT_NOTI("vpq  %s\n", __func__);

	mutex_init(&v4l2_vpq_video_device_lock);
	platform_driver_register(&v4l2_vpq_driver);
	platform_device_register(&v4l2_vpq_pdev);

    /* allocate main vivid state structure */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_vpq_pdev.dev, &v4l2_vpq_dev);
		if(ret < 0){
			PE_PRINT_WARN("vpq : v4l2_device_register error[%d]\n", ret);
			break;
		}

		dev->pdev = &v4l2_vpq_pdev;
#ifdef INCLUDE_KDRV_PQE_PM
		dev->pqe_pm_cfg = &v4l2_vpq_pqe_pm_cfg;
#endif
		video_set_drvdata(&v4l2_vpq_video_dev, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(&v4l2_vpq_video_dev, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_PQ);
#else
		ret = video_register_device(&v4l2_vpq_video_dev, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_PQ);
#endif
		if (ret < 0) {
			PE_PRINT_ERROR("video device register error: %d\n", ret);
			return -1;
		}
	} while(0);

	return ret;
}

static int vpq_check_latency_thread(void *data)
{
	struct vpq_priv *p = data;
	int ret;
#ifdef V4L2_VPQ_APPLY_FREEZABLE
	bool was_frozen;
#endif
#ifdef V4L2_VPQ_APPLY_FREEZABLE
	set_freezable();
#endif

	allow_signal(SIGUSR1);
	while(!kthread_should_stop())
	{
		#ifdef V4L2_VPQ_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	PE_PRINT_NOTI("wakes up\n");
		#endif

		msleep_interruptible(50);
		ret = v4l2_vpq_event_latency();

		if(ret > 0)
		{
			if(p)
			{
				p->event = V4L2_CID_EXT_VPQ_SUBSCRIBE_VIDEO_LATENCY;
				p->ev_data[0] = ret & 0xFF;
				p->ev_data[1] = (ret >> 8) & 0xFF;
				p->ev_size = 2;
		/*
				* // data[0] - low bit of time
				* // data[1] - high bit of time.
				* // data[2~63] - reserved
		*/
				if(p->process_poll)
				{
					p->process_poll(p);
					PE_PRINT_NOTI("======== vupdate_video_latency_event poll !!! [%d ms]", ret);
				}
			}
		}
	}
	return ret;
}

static int vpq_init_err_rpt_str(void)
{
	memset(&_g_vpq_bsp_err_rpt,0,sizeof(_g_vpq_bsp_err_rpt));
	_g_vpq_bsp_err_rpt.cnt = -1;
	return 0;
}

static int vpq_inc_err_rpt_cnt(int cnt)
{
	return (cnt >= 0 && (cnt+1) < V4L2_VPQ_ERR_RPT_STR_NUM)? (cnt+1):0;
}

int v4l2_vpq_update_err_rpt_str(char *str)
{
	int cnt,length;
	struct vpq_bsp_err_rpt *p_rpt = &_g_vpq_bsp_err_rpt;

	if (!str)	return -1;

	length = strlen(str);
	if (length <= 0)	return -1;
	if (length >= 64)	length = 63;

	cnt = vpq_inc_err_rpt_cnt(p_rpt->cnt);

	strncpy(p_rpt->str[cnt],str,length);
	p_rpt->str[cnt][length] = '\0';
	p_rpt->cnt = cnt;

	PE_PRINT_NOTI("[%d](%d)(%s)\n",cnt,length,p_rpt->str[cnt]);

	return 0;
}

static int vpq_err_rpt_thread(void *data)
{
	struct vpq_priv *p = data;
	int wr_cnt, rd_cnt, length;
	struct vpq_bsp_err_rpt *p_rpt = &_g_vpq_bsp_err_rpt;
#ifdef V4L2_VPQ_APPLY_FREEZABLE
	bool was_frozen;
#endif
#ifdef V4L2_VPQ_APPLY_FREEZABLE
	set_freezable();
#endif

	allow_signal(SIGUSR1);
	while(!kthread_should_stop())
	{
		#ifdef V4L2_VPQ_APPLY_FREEZABLE
		if (kthread_freezable_should_stop(&was_frozen))	break;
		if (was_frozen)	PE_PRINT_NOTI("wakes up\n");
		#endif

		msleep_interruptible(100);
		wr_cnt = p_rpt->cnt;
		rd_cnt = p->err_rpt_cnt;

		if (wr_cnt < 0 || wr_cnt >= V4L2_VPQ_ERR_RPT_STR_NUM)	continue;
		if (rd_cnt == wr_cnt)	continue;

		while (rd_cnt != wr_cnt)
		{
			rd_cnt = vpq_inc_err_rpt_cnt(rd_cnt);
			length = strlen(p_rpt->str[rd_cnt]);
			if (length <= 0)	continue;
			if (length >= 64)	length = 63;

			if(p)
			{
				p->event = V4L2_CID_EXT_VPQ_SUBSCRIBE_BSP_ERROR;
				strncpy(p->ev_data,p_rpt->str[rd_cnt],length);
				p->ev_data[length] = '\0';
				p->ev_size = length;

				if(p->process_poll)
				{
					p->process_poll(p);
					PE_PRINT_NOTI("(%2d-%2d) ev(%2d)(%s)\n",wr_cnt,rd_cnt,p->ev_size,p->ev_data);
				}
			}
		}

		p->err_rpt_cnt = rd_cnt;
	}
	return 0;
}
