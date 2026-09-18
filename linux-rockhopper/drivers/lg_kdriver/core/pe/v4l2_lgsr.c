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

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"


#include "os_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "v4l2_lgsr.h"
#include "vpq_hwrap.h"
#include "v4l2_vpq.h"
#include "v4l2_vpq_cmn.h"
#include "v4l2_vpq_be.h"
#include "v4l2_vpq_hdr.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_dolby.h"
#include "pe_kapi.h"
#include "pe_io.h"
#include "pe_cmn.h"
#include "pe_reg.h"

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* SCDCR-4006 */
#define LGSR_PM_INFO(_level,_type,_result)	\
	do {\
		pr_info("LowPower::%s::%s::video%d::%d::%s-%s::%s::%s::lgsr\n",\
			_level,"picturequality",V4L2_EXT_DEV_NO_LGSR,_g_v4l2_lgsr_open_count,\
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

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device v4l2_lgsr_dev;
struct mutex v4l2_lgsr_video_device_lock;

struct lgsr_dev {
	struct platform_device *pdev;
#ifdef INCLUDE_KDRV_PQE_PM
	struct pqe_pm_config *pqe_pm_cfg;
	int pqe_pm_id;
#endif
};

struct lgsr_fh {
	struct v4l2_fh fh;
// need to add some private data
//	struct lgsr_priv *lgsr_priv;
};
UINT32 g_v4l2_lgsr_resume_status = 0xff;
UINT32 g_v4l2_lgsr_init_status = 0xff;
UINT32 g_v4l2_lgsr_done_download_ddr_status = 0x0;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
// static void __exit v4l2_lgsr_device_exit(void);
static int v4l2_lgsr_probe(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_lgsr_remove(struct platform_device *pdev);
#else
static int v4l2_lgsr_remove(struct platform_device *pdev);
#endif
static int v4l2_lgsr_resume(struct device *dev);
static int v4l2_lgsr_suspend(struct device *dev);
static int v4l2_lgsr_fh_open(struct file *flie);
static int v4l2_lgsr_fh_release(struct file *flie);
static int v4l2_lgsr_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_lgsr_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl);
static int v4l2_lgsr_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl);
static int lgsr_set_ext_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_lgsr_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int lgsr_get_ext_ctrl(struct v4l2_ext_control *ctrl);
static int v4l2_lgsr_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls);
static int v4l2_lgsr_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap);
static int v4l2_lgsr_vidioc_s_input(struct file *file, void *__fh, unsigned int i);
static int v4l2_lgsr_vidioc_g_input(struct file *file, void *__fh, unsigned int *i);
static int v4l2_lgsr_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub);
static unsigned int v4l2_lgsr_poll(struct file *file, poll_table *wait);
static int v4l2_lgsr_register(void *arg);
static int v4l2_lgsr_mmap(struct file *file, struct vm_area_struct *vma);
static int v4l2_lgsr_runtime_resume(struct device *dev);
static int v4l2_lgsr_runtime_suspend(struct device *dev);

int v4l2_lgsr_pm_runtime_help(char* buffer);
int v4l2_lgsr_pm_runtime_test(char* command);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_ACCL_TRA - V4L2_CID_EXT_LGSR_BASE +1] = { 0, };

static struct platform_device v4l2_lgsr_pdev = {
	.name = "v4l2_lgsr",
	.id = -1,
};

static struct dev_pm_ops const lgsr_pm_ops = {
        .resume = v4l2_lgsr_resume,
        .suspend = v4l2_lgsr_suspend,
        .runtime_resume = v4l2_lgsr_runtime_resume,
        .runtime_suspend = v4l2_lgsr_runtime_suspend,
};

static struct platform_driver v4l2_lgsr_driver = {
	.probe      = v4l2_lgsr_probe,
	.driver     = {
		.name   = "v4l2_lgsr",
		.owner  = THIS_MODULE,
		.pm     = &lgsr_pm_ops,
	},
	.remove		= v4l2_lgsr_remove,
};

static struct v4l2_file_operations v4l2_lgsr_fops = {
   .owner          = THIS_MODULE,
   .open           = v4l2_lgsr_fh_open,
   .release        = v4l2_lgsr_fh_release,
   .unlocked_ioctl = video_ioctl2,
// .read = vb2_fop_read,
// .mmap = vb2_fop_mmap,
   .mmap = v4l2_lgsr_mmap,
   .poll = v4l2_lgsr_poll,
};

static struct v4l2_ioctl_ops v4l2_lgsr_ioctl_ops = {
   .vidioc_querycap                = v4l2_lgsr_vidioc_querycap,
   .vidioc_s_ctrl                  = v4l2_lgsr_vidioc_s_ctrl,
   .vidioc_g_ctrl                  = v4l2_lgsr_vidioc_g_ctrl,
   .vidioc_s_ext_ctrls             = v4l2_lgsr_vidioc_s_ext_ctrls,
   .vidioc_g_ext_ctrls             = v4l2_lgsr_vidioc_g_ext_ctrls,
   .vidioc_s_input                 = v4l2_lgsr_vidioc_s_input,
   .vidioc_g_input                 = v4l2_lgsr_vidioc_g_input,
   .vidioc_log_status = v4l2_ctrl_log_status,
   .vidioc_subscribe_event = v4l2_lgsr_vidioc_subscribe_event,
   .vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static struct video_device v4l2_lgsr_video_dev = {
   .v4l2_dev  = &v4l2_lgsr_dev,
   .fops      = &v4l2_lgsr_fops,
   .ioctl_ops = &v4l2_lgsr_ioctl_ops,
   .release   = video_device_release_empty,
   .lock      = &v4l2_lgsr_video_device_lock,
   .vfl_dir   = VFL_DIR_RX,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
   .device_caps = V4L2_CAP_VIDEO_CAPTURE
#endif
};

static int _g_v4l2_lgsr_open_count = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static int v4l2_lgsr_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret = RET_OK;
	unsigned long start;
	unsigned long len;
	unsigned long off = ((vma->vm_pgoff) << PAGE_SHIFT);
	unsigned int mem_base = 0;
	unsigned int mem_size = 0;
	LX_MEMCFG_T lgsr_mem;

	PE_PRINT_NOTI("%s entered \n", __func__);

	ret = PE_LGSR_GetMemInfo(&lgsr_mem);
	if (ret != RET_OK){
		PE_PRINT_ERROR("PE_LGSR_GetMemInfo() error.\n");
		return -EINVAL;
	}
	mem_base = lgsr_mem.base;
	mem_size = lgsr_mem.size;
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
	vm_flags_set(vma, VM_IO);
#else
	vma->vm_flags |= VM_IO;
#endif
	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	return io_remap_pfn_range(vma,vma->vm_start,off >> PAGE_SHIFT,vma->vm_end - vma->vm_start,vma->vm_page_prot);
}
int v4l2_lgsr_device_init(void)
{
	PE_PRINT_NOTI("lgsr  %s\n", __func__);

	//video_set_drvdata(&v4l2_vpq_video_dev, &vpq_pdev);
	v4l2_lgsr_register(NULL);

	return 0;
}

#if 0
static void __exit v4l2_lgsr_device_exit(void)
{
	PE_PRINT_NOTI("lgsr  %s\n", __func__);

	platform_device_unregister(&v4l2_lgsr_pdev);
	platform_driver_unregister(&v4l2_lgsr_driver);
}
#endif

#ifdef INCLUDE_KDRV_PQE_PM
static int v4l2_lgsr_pqe_pm_cb(int action)
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
		//PE_CMN_ResumeModule(0);
		/* unregister handler,ipc */
		//lgsr_hwrap_uninitialize();//no need for fw resume
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
		//lgsr_hwrap_initialize(1);//no need for fw resume
		//PE_CMN_ResumeModule(1);
	}

	PE_PRINT_NOTI("(%d) end\n",action);
	return 0;
}

static struct pqe_pm_config v4l2_lgsr_pqe_pm_cfg = {
	.name = "v4l2_lgsr",
	.opt = PQE_PM_OPT_NONE,
	.order = 241,
	.callback = v4l2_lgsr_pqe_pm_cb,
};
#endif
static int v4l2_lgsr_probe(struct platform_device *pdev)
{
	struct lgsr_dev *drv;

	PE_PRINT_NOTI("lgsr start\n");

	pm_runtime_enable(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (drv)
	{
		drv->pdev = &v4l2_lgsr_pdev;
#ifdef INCLUDE_KDRV_PQE_PM
		drv->pqe_pm_cfg = &v4l2_lgsr_pqe_pm_cfg;
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
#endif
		platform_set_drvdata(pdev, drv);
	}
	//else	return -ENOMEM;
	//lgsr_hwrap_initialize(0);

	PE_PRINT_NOTI("lgsr end\n");
	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void v4l2_lgsr_remove(struct platform_device *pdev)
#else
static int v4l2_lgsr_remove(struct platform_device *pdev)
#endif
{
	struct lgsr_dev *drv = platform_get_drvdata(pdev);

	PE_PRINT_NOTI("lgsr start\n");

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_unregister(drv->pqe_pm_id);
#endif
		kfree(drv);
	}

	pm_runtime_disable(&pdev->dev);

	PE_PRINT_NOTI("lgsr end\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

static int v4l2_lgsr_resume(struct device *dev)
{
	g_v4l2_lgsr_init_status = 0x1;
	g_v4l2_lgsr_done_download_ddr_status = 0x0;
	PE_PRINT_NOTI("%s  status init: %d, done_download: %d\n", __func__, g_v4l2_lgsr_init_status, g_v4l2_lgsr_done_download_ddr_status);
    return 0;
}

static int v4l2_lgsr_suspend(struct device *dev)
{
	PE_PRINT_NOTI("%s\n", __func__);
    return 0;
}

static int v4l2_lgsr_runtime_resume(struct device *dev)
{
	struct lgsr_dev *drv = dev_get_drvdata(dev);

	PE_PRINT_NOTI("lgsr start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_resume(drv->pqe_pm_id);
#endif
	}

	LGSR_PM_INFO("info","resume","ok");

	return 0;
}

static int v4l2_lgsr_runtime_suspend(struct device *dev)
{
	struct lgsr_dev *drv = dev_get_drvdata(dev);

	PE_PRINT_NOTI("lgsr start (%s-%s)\n",current->group_leader->comm,current->comm);

	if (drv)
	{
#ifdef INCLUDE_KDRV_PQE_PM
		pqe_pm_request_suspend(drv->pqe_pm_id);
#endif
	}

	LGSR_PM_INFO("info","suspend","ok");

	return 0;
}

int v4l2_lgsr_pm_runtime_help(char* buffer)
{
	int len = 0;
	struct lgsr_dev *drv = platform_get_drvdata(&v4l2_lgsr_pdev);

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "dev name : %s\n",v4l2_lgsr_pdev.name);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- open_count : %d\n",_g_v4l2_lgsr_open_count);
	len += sprintf( buffer+len, "- vdev node name : %s\n",video_device_node_name(&v4l2_lgsr_video_dev));
#ifdef INCLUDE_KDRV_PQE_PM
	if (!drv)					len += sprintf( buffer+len, "drv null\n");
	else if (!drv->pqe_pm_cfg)	len += sprintf( buffer+len, "pqe_pm_cfg null\n");
	else						len += sprintf( buffer+len, "pqe_pm_name : %s, pqe_pm_id : %d\n",drv->pqe_pm_cfg->name,drv->pqe_pm_id);
#endif
	len += sprintf( buffer+len, "- usage_count : %d\n",atomic_read(&v4l2_lgsr_pdev.dev.power.usage_count));
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo lgsr_runtime_suspend > /proc/lg/pe/pm_test\n");
	len += sprintf( buffer+len, "echo lgsr_runtime_resume > /proc/lg/pe/pm_test\n");
	len += sprintf( buffer+len, "- others\n");
	len += sprintf( buffer+len, "cat /sys/devices/platform/v4l2_lgsr/power/runtime_status\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int v4l2_lgsr_pm_runtime_test(char* command)
{
	int ret = 0;
	struct lgsr_dev *drv = platform_get_drvdata(&v4l2_lgsr_pdev);

	if (!strncasecmp(command, "lgsr_pm_runtime_put", strlen("lgsr_pm_runtime_put"))) {
		ret = pm_runtime_put(&v4l2_lgsr_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_put : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "lgsr_pm_runtime_get_sync", strlen("lgsr_pm_runtime_get_sync"))) {
		ret = pm_runtime_get_sync(&v4l2_lgsr_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_get_sync : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "lgsr_pm_runtime_get", strlen("lgsr_pm_runtime_get"))) {
		ret = pm_runtime_get(&v4l2_lgsr_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_get : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "lgsr_pm_runtime_suspend", strlen("lgsr_pm_runtime_suspend"))) {
		ret = pm_runtime_suspend(&v4l2_lgsr_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_suspend : ret:%d\n",ret);
	}
	else if (!strncasecmp(command, "lgsr_pm_runtime_resume", strlen("lgsr_pm_runtime_resume"))) {
		ret = pm_runtime_resume(&v4l2_lgsr_pdev.dev);
		PE_PRINT_NOTI("pm_runtime_resume : ret:%d\n",ret);
	}
#ifdef INCLUDE_KDRV_PQE_PM
	else if (!strncasecmp(command, "lgsr_pqe_pm_register", strlen("lgsr_pqe_pm_register"))) {
		drv->pqe_pm_id = pqe_pm_register(drv->pqe_pm_cfg);
		PE_PRINT_NOTI("pqe_pm_register : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "lgsr_pqe_pm_request_suspend", strlen("lgsr_pqe_pm_request_suspend"))) {
		ret = pqe_pm_request_suspend(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_request_suspend : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "lgsr_pqe_pm_request_resume", strlen("lgsr_pqe_pm_request_resume"))) {
		ret = pqe_pm_request_resume(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_request_resume : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
	else if (!strncasecmp(command, "lgsr_pqe_pm_unregister", strlen("lgsr_pqe_pm_unregister"))) {
		ret = pqe_pm_unregister(drv->pqe_pm_id);
		PE_PRINT_NOTI("pqe_pm_unregister : pqe_pm_id:%d\n",drv->pqe_pm_id);
	}
#endif
	else if (!strncasecmp(command, "lgsr_runtime_suspend", strlen("lgsr_runtime_suspend"))) {
		while (atomic_read(&v4l2_lgsr_pdev.dev.power.usage_count) > 0) {
			PE_PRINT_NOTI("call pm_runtime_put (usage_count:%d)\n",atomic_read(&v4l2_lgsr_pdev.dev.power.usage_count));
			ret = pm_runtime_put(&v4l2_lgsr_pdev.dev);
			//msleep(1);
		}
	}
	else if (!strncasecmp(command, "lgsr_runtime_resume", strlen("lgsr_runtime_resume"))) {
		while (atomic_read(&v4l2_lgsr_pdev.dev.power.usage_count) <= 0) {
			PE_PRINT_NOTI("call pm_runtime_get_sync (usage_count:%d)\n",atomic_read(&v4l2_lgsr_pdev.dev.power.usage_count));
			ret = pm_runtime_get_sync(&v4l2_lgsr_pdev.dev);
			//msleep(1);
		}
	}
	else {
		printk("do nothing\n");
	}

	return ret;
}

static int v4l2_lgsr_fh_open(struct file *flie)
{
	int ret=0;
	int ret0=0;
	struct lgsr_dev *dev  = video_drvdata(flie);
	struct lgsr_fh *fh;

	PE_PRINT_NOTI("lgsr: open (%s-%s)\n",current->group_leader->comm,current->comm);

	ret0 = pm_runtime_get_sync(&dev->pdev->dev);
	PE_PRINT_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	fh = kzalloc(sizeof(struct lgsr_fh), GFP_KERNEL);
	if (!fh)
	{
		PE_PRINT_NOTI("lgsr: allocation of file handle failed \n");
		ret = -ENOMEM;
		return ret;
	}

	v4l2_fh_init(&fh->fh, video_devdata(flie));

	flie->private_data = fh;
	v4l2_fh_add(&fh->fh);

	/* increment open counter */
	_g_v4l2_lgsr_open_count++;
	LGSR_PM_INFO("info","open","ok");

	return ret;
}

static int v4l2_lgsr_fh_release(struct file *flie)
{
	int ret=0;
	int ret0=0;
	struct lgsr_dev *dev  = video_drvdata(flie);
	//struct lgsr_fh *fh = flie->private_data;

	PE_PRINT_NOTI("lgsr: close (%s-%s)\n",current->group_leader->comm,current->comm);

	v4l2_fh_release(flie);

	ret0 = pm_runtime_put(&dev->pdev->dev);
	PE_PRINT_NOTI("%s : ret0:%d, usage_count:%d\n",(dev->pdev->name)? (dev->pdev->name):"na",ret0,atomic_read(&dev->pdev->dev.power.usage_count));

	/* decrement open counter */
	_g_v4l2_lgsr_open_count--;
	LGSR_PM_INFO("info","close","ok");

	return ret;
}

static int v4l2_lgsr_vidioc_s_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret=0;
	//struct lgsr_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	PE_PRINT_TRACE("lgsr:id 0x%x (%s), value %d, n",ctrl->id,lgsr_ctrl_id_to_str(ctrl->id),ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_LGSR_SRSQM:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_SRSQM- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("SRSQM:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("SRSQM:enable = %d\n",  onoff);

			ret = PE_LGSR_SetSrSQM(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_SetSrSQM: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_TRA_HALT:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_TRA_HALT- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("TRA_HALT:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("TRA_HALT:enable = %d\n",  onoff);

			ret = PE_LGSR_HaltTRA(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_SetSrSQM: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_TRA_RUN:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_TRA_RUN- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("TRA_RUN:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("TRA_RUN:enable = %d\n", onoff);

			ret = PE_LGSR_RunTRA(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_SetSrSQM: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_DDR_DOWNLOAD_DONE:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_DDR_DOWNLOAD_DONE- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("DOWNLOAD_DONE:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("DOWNLOAD_DONE:enable = %d\n", onoff);

			ret = PE_LGSR_DoneDownloadDdr(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_SetSrSQM: error(%d)\n", ret);
			}
			else
			{
				g_v4l2_lgsr_done_download_ddr_status = 0x1;
				PE_PRINT_NOTI("LGSR_DDR_DOWNLOAD_DONE  status init: %d, done_download: %d\n", g_v4l2_lgsr_init_status, g_v4l2_lgsr_done_download_ddr_status);
			}
		} break;
		case V4L2_CID_EXT_LGSR_USER_READY:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_USER_READY- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("USER_READY:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("USER_READY:enable = %d\n", onoff);

			ret = PE_LGSR_UserReady(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_UserReadys: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_VALID_RUN:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_VALID_RUN- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value ? 1 : 0;
			PE_PRINT_ETC("VALID_RUN:ctrl->value = %d\n",ctrl->value);
			PE_PRINT_ETC("VALID_RUN:enable = %d\n", onoff);

			ret = PE_LGSR_ValidRun(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_ValidRun: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_DEMO_MODE:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_DEMO_MODE- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value;
			PE_PRINT_ETC("DEMO_MODE:ctrl->value = %d\n",onoff);

			ret = PE_LGSR_Demomode(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_HW_O20_DemoMode: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_UI_ONOFF:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_UI_ONOFF- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value;
			PE_PRINT_ETC("UI_ONOFF:ctrl->value = %d\n",onoff);

			ret = PE_LGSR_UIOnoff(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_UIOnoff: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_ACCL_SRSQM:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_ACCL_SRSQM- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value;
			PE_PRINT_ETC("ACCL_SRSQM:ctrl->value = %d\n",onoff);

			ret = PE_LGSR_AcclSrsqm(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_AcclSrsqm: error(%d)\n", ret);
			}
		} break;
		case V4L2_CID_EXT_LGSR_ACCL_TRA:
		{
			UINT32 onoff;
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_ACCL_TRA- V4L2_CID_EXT_LGSR_BASE])
				break;
			onoff = ctrl->value;
			PE_PRINT_ETC("ACCL_SRSQM:ctrl->value = %d\n",onoff);

			ret = PE_LGSR_AcclTra(onoff);
			if (ret)
			{
				PE_PRINT_ERROR("PE_LGSR_AcclTra: error(%d)\n", ret);
			}
		} break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int v4l2_lgsr_vidioc_g_ctrl(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	PE_REG_PARAM_T param_lne;
	PE_REG_PARAM_T param_tra;
	__attribute__((unused)) UINT32 addr0=0;
	__attribute__((unused)) UINT32 val0=0;
	//struct lgsr_fh *fh = __fh;

	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}

	PE_PRINT_TRACE("lgsr:id 0x%x (%s), value %d, \n", ctrl->id, lgsr_ctrl_id_to_str(ctrl->id), ctrl->value);

	switch (ctrl->id) {
		case V4L2_CID_EXT_LGSR_LNE_STATUS:
		{
			if(PE_KDRV_VER_O20)
			{
				param_lne.addr = 0xC90260E4;
				ret = PE_REG_GetTable(&param_lne,0,sizeof(param_lne));
				ctrl->value = param_lne.data;
				PE_PRINT_INFO("addr: 0x%08x, data: 0x%08x\n", param_lne.addr, param_lne.data);
			}
		}break;
		case V4L2_CID_EXT_LGSR_TRA_STATUS:
		{
			if(PE_KDRV_VER_O20)
			{
				param_tra.addr = 0xC90260E0;
				ret = PE_REG_GetTable(&param_tra,0,sizeof(param_tra));
				ctrl->value = param_tra.data;
				PE_PRINT_INFO("addr: 0x%08x, data: 0x%08x\n", param_tra.addr, param_tra.data);
			}
		}break;
		case V4L2_CID_EXT_LGSR_RESUME_STATUS:
		{
			/*
			  g_v4l2_lgsr_done_download_ddr_status : 0 no success donwload ddr after booting
			                                  1 already success donwload ddr after booting
			  g_v4l2_lgsr_init_status       : 0xff variable initial value
			                                : 0x0 cold booting, normal init
			                                : 0x1 instance booting, resume init
			  g_v4l2_lgsr_resume_status[31:16] = g_v4l2_lgsr_done_download_ddr_status
			  g_v4l2_lgsr_resume_status[15: 0] = g_v4l2_lgsr_init_status
			  
			*/
			g_v4l2_lgsr_resume_status = (g_v4l2_lgsr_done_download_ddr_status<<16)| g_v4l2_lgsr_init_status;
			ctrl->value = g_v4l2_lgsr_resume_status;
			PE_PRINT_INFO("%s g_v4l2_lgsr_resume_status :%d, status init: %d, done_download: %d\n", \
				__func__, g_v4l2_lgsr_resume_status, g_v4l2_lgsr_init_status, g_v4l2_lgsr_done_download_ddr_status);
		}break;
		default:
			ret = -EINVAL;
	}

	return 0;
}

static int v4l2_lgsr_compat_vidioc_ext_ctrls(struct v4l2_ext_control *ctrl)
{
	int ret = 0;
	struct v4l2_ext_vpq_cmn_data arg_buf;
	if (!ctrl)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_LGSR_CROP_POSITION:
		{
			if(_g_v4l2_lgsr_block_func[V4L2_CID_EXT_LGSR_CROP_POSITION- V4L2_CID_EXT_LGSR_BASE])
				break;
			if(copy_from_user(&arg_buf,(void __user *)ctrl->string,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			//PE_PRINT_VPQ_PE("[0] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			arg_buf.p_data = (unsigned char *)(uintptr_t)arg_buf.compat_data;
			//PE_PRINT_VPQ_PE("[1] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
			if(copy_to_user((void __user *)ctrl->string,&arg_buf,sizeof(struct v4l2_ext_vpq_cmn_data)))
			{
				PE_PRINT_ERROR("copy_to_user error\n");
			}
			//PE_PRINT_VPQ_PE("[2] v:%d,l:%d,wid:%d, p:%p\n",arg_buf.version,arg_buf.length,arg_buf.wid,arg_buf.p_data);
		}break;
		default:
			break;
	}

	return ret;
}

static int lgsr_set_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	struct v4l2_ext_vpq_cmn_data pqData;
 	int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_lgsr_compat_vidioc_ext_ctrls(ctrl);\
	}
	#endif

	if (copy_from_user(&pqData, (void __user *)ctrl->ptr, sizeof(pqData)))
	{
		PE_PRINT_ERROR("copy_from_user error\n");
		return -EINVAL;
	}

	switch (ctrl->id) {
		case V4L2_CID_EXT_LGSR_CROP_POSITION:
		{
			UINT32 pos_param[2];

			memset(&pos_param, 0x0, sizeof(UINT32)*2);

			if (copy_from_user(&pos_param, (void __user *)pqData.p_data, pqData.length))
			{
				PE_PRINT_ERROR("copy_from_user error\n");
			}
			PE_PRINT_ETC("[%s.%d] position x, y: 0x%08x,0x%08x \n",\
				__F__, __L__,pos_param[0], pos_param[1]);
			ret = PE_LGSR_CropPosition(pos_param);
			if (ret)
			{
				PE_PRINT_ERROR("KWRAP_PE_SetObcParam error(%d)\n", ret);
			}
		}
		break;
 		default:
			return -EINVAL;
	}

	/* TODO: Update the hardware */

	return ret;
}

static int v4l2_lgsr_vidioc_s_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct lgsr_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			PE_PRINT_TRACE("(%s)(%s) [%d]id:0x%x(%s)\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,lgsr_ctrl_id_to_str(ctrl->id));
			#endif

			ret = lgsr_set_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}
	return ret;

}

static int lgsr_get_ext_ctrl(struct v4l2_ext_control *ctrl)
{
	// int ret = 0;

	if (!ctrl || !ctrl->string)
	{
		PE_PRINT_ERROR("ctrl is null\n");
		return -EINVAL;
	}

	#ifdef CONFIG_COMPAT
	if (is_compat_task())
	{
		v4l2_lgsr_compat_vidioc_ext_ctrls(ctrl);
	}
	#endif

	switch (ctrl->id) {
 		default:
			return -EINVAL;
	}
	return 0;
}


static int v4l2_lgsr_vidioc_g_ext_ctrls(struct file *file, void *__fh, struct v4l2_ext_controls *ctrls)
{
	//struct lgsr_fh *fh = __fh;
	int i, ret = 0;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	if (ctrls->which == V4L2_CTRL_CLASS_USER) {
#else
	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_USER) {
#endif
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			#ifdef CONFIG_COMPAT
			PE_PRINT_TRACE("(%s)(%s) [%d]id:0x%x(%s)\n",current->comm,(is_compat_task())? "32b":"64b",i,ctrl->id,lgsr_ctrl_id_to_str(ctrl->id));
			#endif

			ret = lgsr_get_ext_ctrl(ctrl);
			if (ret) {
				ctrls->error_idx = i;
				break;
			}
		}
		return ret;

	}

	return -EINVAL;
}

static int v4l2_lgsr_vidioc_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	//struct lgsr_fh *fh = __fh;

	strncpy(cap->card, "v4l2_lgsr", sizeof(cap->card)-1);
	strncpy(cap->driver, "v4l2_lgsr", sizeof(cap->driver)-1);
	cap->bus_info[0] = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
#endif

	return 0;

}

static int v4l2_lgsr_vidioc_s_input(struct file *file, void *__fh, unsigned int i)
{
	//struct lgsr_fh *fh = __fh;
	//int ret;

	PE_PRINT_NOTI("lgsr: set input %d\n", i);

	return 0;
}

static int v4l2_lgsr_vidioc_g_input(struct file *file, void *__fh, unsigned int *i)
{
	//struct lgsr_fh *fh = __fh;
	//int ret;

	PE_PRINT_NOTI("lgsr: get input %d\n", *i);

	return 0;
}


static int v4l2_lgsr_vidioc_subscribe_event(struct v4l2_fh *__fh, const struct v4l2_event_subscription *sub)
{
	PE_PRINT_NOTI("de type 0x%x, id 0x%x\n", sub->type, sub->id);

	switch (sub->type)
	{
		/*
		case V4L_LGSR_1_EVENT:  // internal mute off
		case V4L_LGSR_2_EVENT:  // active window
			return v4l2_event_subscribe(__fh, sub, 32, NULL);
			*/
		default:
			return -EINVAL;
	}
}

static unsigned int v4l2_lgsr_poll(struct file *file, poll_table *wait)
{
	struct lgsr_fh *fh = (struct lgsr_fh *)file->private_data;
	int rc = 0;
	unsigned long req_events = poll_requested_events(wait);

	PE_PRINT_NOTI("lgsr:req_events 0x%lx\n", req_events);

	if (v4l2_event_pending(&fh->fh))
		rc |= POLLPRI;
	else
	{
		poll_wait(file, &fh->fh.wait, wait);
		/*
		poll_wait(file, &p->lgsr_poll_wq, wait);

		if (p->lgsr_poll & POLLIN)
			rc |= POLLIN;
		if (p->lgsr_poll & POLLOUT)
			rc |= POLLOUT;
		if (p->lgsr_poll & POLLERR)
			rc |= POLLERR;
			*/
	}

	PE_PRINT_NOTI("lgsr: rc 0x%x\n", rc);

	return rc;
}

char *lgsr_ctrl_id_to_str(int id)
{
	#define LGSR_CASE_ID_TO_STR(_x)		case (_x):return #_x

    switch (id)
	{
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_UI_ONOFF 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_DDR_ADDR 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_DDR_DOWNLOAD_DONE );
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_SRSQM 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_CROP_POSITION 	);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_TRA_HALT 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_TRA_RUN 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_USER_READY 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_LNE_STATUS 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_TRA_STATUS 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_VALID_RUN 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_DEMO_MODE 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_ACCL_SRSQM 		);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_ACCL_TRA 			);
		LGSR_CASE_ID_TO_STR(V4L2_CID_EXT_LGSR_RESUME_STATUS);
		default:	return "UNKOWN";
	}
}

static int v4l2_lgsr_register(void *arg)
{
	int ret;
	struct lgsr_dev *dev;

	PE_PRINT_NOTI("lgsr  %s\n", __func__);
	mutex_init(&v4l2_lgsr_video_device_lock);
	platform_driver_register(&v4l2_lgsr_driver);
	platform_device_register(&v4l2_lgsr_pdev);

    /* allocate main vivid state structure */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_lgsr_pdev.dev, &v4l2_lgsr_dev);
		if(ret < 0){
			PE_PRINT_WARN("lgsr : v4l2_device_register error[%d]\n", ret);
			break;
		}

		dev->pdev = &v4l2_lgsr_pdev;
#ifdef INCLUDE_KDRV_PQE_PM
		dev->pqe_pm_cfg = &v4l2_lgsr_pqe_pm_cfg;
#endif
		video_set_drvdata(&v4l2_lgsr_video_dev, dev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
		ret = video_register_device(&v4l2_lgsr_video_dev, VFL_TYPE_VIDEO, V4L2_EXT_DEV_NO_LGSR);
#else
		ret = video_register_device(&v4l2_lgsr_video_dev, VFL_TYPE_GRABBER, V4L2_EXT_DEV_NO_LGSR);
#endif
		if (ret < 0) {
			PE_PRINT_ERROR("video device register error: %d\n", ret);
			return -1;
		}
		g_v4l2_lgsr_init_status = 0x0;
		g_v4l2_lgsr_done_download_ddr_status= 0x0;
		PE_PRINT_NOTI("%s  status init: %d, done_download: %d\n", __func__, g_v4l2_lgsr_init_status, g_v4l2_lgsr_done_download_ddr_status);
	} while(0);

	return ret;
}

int lgsr_proc_init_block_func_pe(void)
{
	memset(_g_v4l2_lgsr_block_func, 0x0, sizeof(UINT32)*14);
	return 0;
}

int lgsr_proc_show_func_status_lgsr(void)
{
	int i;
	for(i = 0 ; i < 14; i++)
	{
		printk("[%d] %s  : %d\n", i, lgsr_ctrl_id_to_str(V4L2_CID_EXT_LGSR_BASE +i),\
			_g_v4l2_lgsr_block_func[i]);
	}
	return 0;
}
int lgsr_proc_set_block_func_lgsr(int num_func)
{
	if(_g_v4l2_lgsr_block_func[num_func] == 0x0)
		_g_v4l2_lgsr_block_func[num_func] = 0x1;
	else
		_g_v4l2_lgsr_block_func[num_func] = 0x0;
	return 0;
}

int lgsr_proc_set_block_func_dftmode(int mode)
{
	if(mode)
	{
		memset(&_g_v4l2_lgsr_block_func, 0x1, sizeof(UINT32)*14);
		PE_PRINT_NOTI("[DFT MODE] LGSR func block!!\n");
	}
	return 0;
}

