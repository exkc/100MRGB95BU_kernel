/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  lgnpu driver
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.04.13
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <asm/io.h>
#include <asm/cacheflush.h>
#include <linux/dma-mapping.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/workqueue.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>
#ifdef USE_IOMMU
#include <linux/mm.h>
#include <linux/of.h>
#include <linux/version.h>
#endif
#include <linux/kernel.h>
#include <linux/types.h>

#include <linux/delay.h>
#include <linux/pm_runtime.h>

#include "os_util.h"
#include "base_device.h"
#include "hma_alloc.h"
#include "logm.h"

#include "npu_api.h"
#include "npu_drv.h"
#include "npu_que.h"
#include "base_types.h"
#include "os_util.h"
#include "npu_hwc_loader.h"
#include "npu_utilization.h"
/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#ifndef USE_IOMMU
#define USE_CACHE_DATA
#endif
#define DBG_MTD
#define PRIORITY_SCHEDULER
//#define ENABLE_FILE_LOAD
//#define ENABLE_DATA_DUMP
//#define _NOT_USE_DEV_MEM  /* Only use npu_hwc_emul */

#define MODULE_NAME             "npu"
#define NPU_MAJOR               (0)
#define NPU_MINOR               (0)

#define MAX_RETRIES             5
#define RUN_WAIT_TIMEOUT        5000
#define _ALIGN(value, align) ( (value + (align -1))& ~(align-1) )
#define NPU_CORE_MAX             2
#define EXTRA_POOL_IDX           0
/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
logm_define (npu_drv, log_level_noti);
#define trace(fmt,args...)      logm_trace(npu_drv, fmt, ##args)
#define debug(fmt,args...)      logm_debug(npu_drv, fmt, ##args)
#define info(fmt,args...)       logm_info(npu_drv, fmt, ##args)
#define noti(fmt,args...)       logm_noti(npu_drv, fmt, ##args)
#define warn(fmt,args...)       logm_warning(npu_drv, fmt, ##args)
#define error(fmt,args...)      logm_error(npu_drv, fmt, ##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct npu_hw_control
{
    struct npu_hw *npu_hw;
#ifdef USE_IOMMU
    struct platform_device *pdev;
#else
    struct platform_device pdev;
#endif
    struct npu_hw_control *next;
    unsigned int chip;
    unsigned int core_num;
    char name[0];
};

typedef struct
{
    // add here extra parameter
    bool	is_suspended;
}NPU_DRVDATA_T;

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
DEFINE_MUTEX(npu_inst_list_lock);
LIST_HEAD(npu_inst_list);
/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int npu_drv_open(struct inode *inode, struct file *file);
static long npu_drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long npu_drv_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#endif
static int npu_drv_release(struct inode *inode, struct file *file);
static int _npu_probe(struct platform_device *pdev);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
static void _npu_remove(struct platform_device *pdev);
#else
static int _npu_remove(struct platform_device *pdev);
#endif
static int _npu_module_init(void);
static void _npu_module_exit(void);

static bool _npu_have_work_task(void);
static bool _npu_have_work_req(void);

static int _npu_suspend(struct platform_device *pdev, pm_message_t state);
static int _npu_resume(struct platform_device *pdev);

static int _npu_runtime_suspend(struct device *dev);
static int _npu_runtime_resume(struct device *dev);

struct mutex _npu_device_lock;
/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct dev_pm_ops _npu_pm_ops = {
    .runtime_suspend = _npu_runtime_suspend,
    .runtime_resume = _npu_runtime_resume,
};

#ifdef USE_IOMMU
static const struct of_device_id npu_dt_ids[] = {
	{ .compatible = "lge,npu", },
	{},
};
MODULE_DEVICE_TABLE(of, npu_dt_ids);
#endif

static struct platform_driver _npu_platform_driver =
{
    .probe = _npu_probe,
    .suspend = _npu_suspend,
    .remove = _npu_remove,
    .resume = _npu_resume,
    .driver = {
            .name = MODULE_NAME,
            .pm = &_npu_pm_ops,
        #ifdef USE_IOMMU
            .of_match_table = of_match_ptr(npu_dt_ids),
		#endif
        },
};

static struct file_operations npu_fops =
{
    .open              = npu_drv_open,
    .unlocked_ioctl  = npu_drv_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl    = npu_drv_compat_ioctl,
#endif
    .release         = npu_drv_release,
};

static struct cdev _cdev;
static struct npu_hw_control *npu_hw_controls = NULL;
static int _npu_major = NPU_MAJOR;
static int _npu_minor = NPU_MINOR;

static unsigned int _inst_cnt = 0;

struct npu_work_thread
{
    unsigned int core_idx;
    unsigned int run_cnt;
    struct work_struct _work;
    struct workqueue_struct *_work_highpri_wq;
    bool   thread_stop;
};
static struct npu_work_thread _npu_work[NPU_CORE_MAX];
static char *_npu_work_name[] = {"npu_run_0","npu_run_1"};

struct npu_pool_info
{
	char *name;
	char *type;
};

#ifdef USE_CACHE_DATA
#ifdef CHIP_NAME_o22
static struct npu_pool_info _npu_pool[] = {
    {"npu",   "HMA"},
    {"npu1",  "HMA"},
};
#else   // from o24 (m1/m0 order) onwards, use m1, m0 memory map order
static struct npu_pool_info _npu_pool[] = {
    {"npu1",  "HMA"},
    {"npu",   "HMA"},
};
#endif
#endif

struct mutex wait_queue_lock;

#ifdef USE_IOMMU
static struct class* npu_class;
#endif

static void *_work_task_que; /* queue for list of scheduled to work */
static void *_work_req_que; /* queue for send request to IP */
static void *_work_rsp_que; /* queue for get response about IP work */
static wait_queue_head_t _work_wait_req;

/*==============================================================================
    Implementation Group
==============================================================================*/
#ifdef USE_IOMMU
int npu_hw_register(struct platform_device *pdev, struct npu_hw *hw)
#else
int npu_hw_register(struct npu_hw *hw)
#endif
{
    struct npu_hw_control *control;
    dev_t dev;
#ifndef USE_IOMMU
    struct platform_device *pdev;
#endif
    int ret = 0;
    size_t buf_size;

    /* register char. dev. */
    if(_npu_major)
    {
        dev = MKDEV(_npu_major, _npu_minor);
        ret = register_chrdev_region(dev, 1, MODULE_NAME);
    }
    else
    {
        ret = alloc_chrdev_region(&dev, _npu_minor, 1, MODULE_NAME);
        _npu_major = MAJOR (dev);
    }

    cdev_init(&_cdev, &npu_fops);
    _cdev.owner = THIS_MODULE;

    ret = cdev_add(&_cdev, dev, 1);
    if(ret)
    {
        error("adding npu device (%d.%d) failed, %d\n", MAJOR(dev), MINOR(dev), ret);
        return -EIO;
    }

#ifdef USE_IOMMU
    device_create(npu_class, NULL, dev, NULL, "%s%d", MODULE_NAME, _npu_minor);
#endif
    buf_size = strlen(hw->name) + strlen(MODULE_NAME) + 1;
    control = kzalloc(sizeof (struct npu_hw_control) + buf_size, GFP_KERNEL);
    if(!control)
    {
        error ("no memory\n");
        return -ENOMEM;
    }

    ret = snprintf(control->name, buf_size, MODULE_NAME "%s", hw->name);
    if (ret < 0) {
        error("snprintf error. ret:%d, buf_size:%zu\n", ret, buf_size);
        kfree(control);
        return -EINVAL;
    } else if ((size_t)ret >= buf_size) {
        error("snprintf truncated(%s). ret:%d, buf_size:%zu\n", control->name,
              ret, buf_size);
        kfree(control);
        return -EINVAL;
    }

    control->npu_hw = hw;
    control->next = npu_hw_controls;
    npu_hw_controls = control;

#ifdef USE_IOMMU
    control->pdev = pdev;
    ret = 0;
#else
    pdev = &control->pdev;
    pdev->name = control->name;
    pdev->id = PLATFORM_DEVID_NONE;
    device_initialize (&pdev->dev);
    pdev->driver_override = MODULE_NAME;
    pdev->dev.devt = MKDEV(_npu_major, _npu_minor);
    ret = platform_device_add(pdev);
    if(ret < 0)
    {
        error ("cannot add device %s\n", hw->name);
        kfree(control);
        return ret;
    }
#endif
    _npu_minor++;

    info("%s initialized.\n", hw->name);

    return ret;
}
EXPORT_SYMBOL(npu_hw_register);

int npu_get_utilization(void)
{
    int val = 0;

    if(_npu_have_work_task() || _npu_have_work_req())
    {
        val = 30;
    }

    debug("%s : %d\n", __func__, val);

    return val;
}
EXPORT_SYMBOL(npu_get_utilization);

int iommuinfo_get_utilization(void)
{
    int val = 0;

    debug("%s : %d\n", __func__, val);

    return val;
}
EXPORT_SYMBOL(iommuinfo_get_utilization);

static int _npu_suspend(struct platform_device *pdev, pm_message_t state)
{
	NPU_DRVDATA_T *drv_data;
	drv_data = platform_get_drvdata(pdev);

	noti("NPU - suspend BEGIN\n");

	// add here the suspend code

	if(drv_data->is_suspended == true) {
		noti("NPU - suspend FAIL\n");
		return -1; //If already in suspend state, so ignore
	}

	drv_data->is_suspended = true;
	noti("NPU - suspend OK\n");

	return 0;
}

static int _npu_resume(struct platform_device *pdev)
{
	NPU_DRVDATA_T *drv_data;
	drv_data = platform_get_drvdata(pdev);

	noti("NPU - resume BEGIN\n");

	if(drv_data->is_suspended == false) {
		noti("NPU - resume FAIL\n");
		return -1;
	}

	// add here the resume code

	drv_data->is_suspended = false;
	noti("NPU - resume OK\n");

	return 0;
}

static void _npu_pm_suspend(struct device *dev)
{
    info("%s\n",dev->driver->name);

    pm_runtime_put_sync(dev);
}

static void _npu_pm_resume(struct device *dev)
{
    info("%s\n",dev->driver->name);

    pm_runtime_get_sync(dev);
}

static int _npu_runtime_suspend(struct device *dev)
{
    struct npu_hw *npu_hw = npu_hw_controls->npu_hw;

#ifdef BRINGUP
    return 0;
#endif
    info("_npu_runtime_suspend, usage_count %d\n",
        atomic_read(&dev->power.usage_count));

    if (_inst_cnt > 0) {
        warn("invalid call (inst_cnt %d)\n", _inst_cnt);
    }

    //clockgate enbale
    npu_hw->pmctrl(npu_hw, true);

    pr_info("LowPower::info::groupother::npu::%d::%s-%s::suspend::ok\n",
            _inst_cnt, current->group_leader->comm, current->comm);
    return 0;
}

static int _npu_runtime_resume(struct device *dev)
{
    struct npu_hw *npu_hw = npu_hw_controls->npu_hw;

#ifdef BRINGUP
    return 0;
#endif
    info("_npu_runtime_resume, usage_count %d\n",
        atomic_read(&dev->power.usage_count));

    if (_inst_cnt > 1) {
        warn("invalid call (inst_cnt %d)\n", _inst_cnt);
    }

    //clockgate disble
    npu_hw->pmctrl(npu_hw, false);

    pr_info("LowPower::info::groupother::npu::%d::%s-%s::resume::ok\n",
            _inst_cnt, current->group_leader->comm, current->comm);
    return 0;
}

static void kfree_null(void **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        kfree(*ptr);
        *ptr = NULL;
    }
}

#ifdef USE_IOMMU
static void dma_cache_flush(struct npu_buffer *buf, unsigned int size, const char *name)
{
    debug("[DMA][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);
    dma_sync_sg_for_device(&npu_hw_controls->pdev->dev, buf->sgt.sgl, buf->sgt.nents, DMA_TO_DEVICE);
    debug("[cache_flush done][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, size);
}


static void dma_cache_invalidate(struct npu_buffer *buf, unsigned int size, const char *name)
{
    debug("[DMA][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);
    dma_sync_sg_for_device(&npu_hw_controls->pdev->dev, buf->sgt.sgl, buf->sgt.nents, DMA_FROM_DEVICE);
    debug("[cache_invalidate done][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, size);
}
#endif

static void cache_flush(const void *addr, unsigned int size)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
    dcache_clean_poc((unsigned long)addr, (unsigned long)(addr + size));
#else
	__dma_map_area(addr, size, DMA_TO_DEVICE);
#endif
#ifndef __aarch64__
	outer_clean_range((phys_addr_t)addr, (phys_addr_t)addr + size);
#endif
}

#if 0
static void cache_invalidate(const void *addr, unsigned int size)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
    dcache_inval_poc((unsigned long)addr, (unsigned long)(addr + size));
#else
	__dma_map_area(addr, size, DMA_FROM_DEVICE);
#endif
#ifndef __aarch64__
	outer_inv_range((phys_addr_t)addr, (phys_addr_t)addr + size);
#endif
}
#endif

static int _alloc_buffer(struct npu_buffer *buf, int size, unsigned int idx, const char *name)
{
#ifdef USE_IOMMU
    int ret, i;
    struct scatterlist *s;

    if(size <= 0)
    {
        error("invalid size (%d) \n", size);
        return -EFAULT;
    }

    buf->size = _ALIGN(size, 4096);
    buf->va_addr = dma_alloc_attrs(&npu_hw_controls->pdev->dev, buf->size, &buf->phys_addr, GFP_KERNEL, 0);
    //buf->va_addr = dma_alloc_attrs(&npu_hw_controls->pdev->dev, buf->size, &buf->phys_addr, GFP_KERNEL, DMA_ATTR_ALLOC_SINGLE_PAGES); //4k page
    if(!buf->va_addr)
    {
        error("alloc fail %s. %d\n", name, buf->size);
        return -EFAULT;
    }

    //memset(buf->va_addr, 0, buf->size);

    buf->magic_num = USE_MAGIC;

    info("[DMA][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);

    ret = dma_get_sgtable_attrs(&npu_hw_controls->pdev->dev, &buf->sgt, buf->va_addr, buf->phys_addr, size, 0);
    if (ret)
    {
        error("dma_get_sgtable_attrs() failed. %d\n", ret);
        dma_free_attrs(&npu_hw_controls->pdev->dev, buf->size, buf->va_addr, buf->phys_addr, 0);
    }
    debug("sgt.nents %d\n", buf->sgt.nents);

    for_each_sg(buf->sgt.sgl, s, buf->sgt.orig_nents, i)
    {
        struct page *page = sg_page(s);
        dma_addr_t daddr = page_to_phys(page);
        dma_addr_t daddr2 = sg_dma_address(s);
        unsigned int len = sg_dma_len(s);
        unsigned int len2 = s->length;
        debug("dma address %d. daddr 0x%016lx, daddr2 0x%016lx, len 0x%x len2 0x%x\n", i, (long)daddr, (long)daddr2, len, len2);
    }

    debug("[DMA][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);

    return 0;
#else
#ifdef _NOT_USE_DEV_MEM
    if(size <= 0)
    {
        error("invalid size (%d) \n", size);
        return -EFAULT;
    }

    buf->phys_addr = 0xFFFFFFFF;

    buf->size = _ALIGN(size, 4096);

    buf->va_addr = vzalloc(buf->size);
    if(!buf->va_addr)
    {
        error("alloc fail %s. %d\n", name, buf->size);
        return -EFAULT;
    }

    memset(buf->va_addr, 0, buf->size);

    debug("[Cache][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);

    return 0;
#else
    char *pool_name;

    mutex_init(&buf->mutex_lock);
    mutex_lock(&buf->mutex_lock);

#ifdef USE_CACHE_DATA
    pool_name = _npu_pool[idx].name;
#else
    if(!strcmp(name, "input") || !strcmp(name, "output"))
    {
        pool_name = _npu_pool[EXTRA_POOL_IDX].name;
    }
    else
    {
        pool_name = _npu_pool[idx].name;
    }
#endif

    buf->size = _ALIGN(size, 4096);

    buf->phys_addr = hma_alloc_user(pool_name, buf->size, 4096, name);
    if(!buf->phys_addr)
    {
        error("[POOL] no mem for %s. %d\n", name, buf->size);
        mutex_unlock(&buf->mutex_lock);
        return -ENOMEM;
    }

    buf->va_addr = hma_map(buf->phys_addr, buf->size);
    if(!buf->va_addr)
    {
        hma_free(pool_name, buf->phys_addr);
        buf->phys_addr = 0;
        error("map fail %s. %d\n", name, buf->size);
        mutex_unlock(&buf->mutex_lock);
        return -EFAULT;
    }

    //memset(buf->va_addr, 0, buf->size);

    buf->core_idx = idx;
    buf->magic_num = USE_MAGIC;
    info("[Alloc][%s] phys_:0x%llX : var_:0x%p : size(0x%X)\n", name, buf->phys_addr, buf->va_addr, buf->size);

    mutex_unlock(&buf->mutex_lock);

    return 0;
#endif
#endif
}

#ifdef USE_CACHE_DATA
static int _cache_buffer(struct npu_cache_data *data, int size, const char *name)
{
    debug("_cache_buffer[%s] (0x%X)\n", name, size);

    if(size <= 0)
    {
        error("invalid size (%d) \n", size);
        return -EFAULT;
    }

    data->size = _ALIGN(size, 4096);

    data->ptr = vzalloc(data->size);
    if(!data->ptr)
    {
        error("alloc fail %s. %d\n", name, data->size);
        return -EFAULT;
    }

    info("[Cache][%s] addr_:0x%p : size(0x%X)\n", name, data->ptr, data->size);

    return 0;
}
#endif

static void _free_buffer(struct npu_buffer *buf)
{
#ifdef USE_IOMMU
    info("[DMA free] phys_:0x%llX : var_:0x%p : size(0x%X)\n", buf->phys_addr, buf->va_addr, buf->size);

    if(buf->size <= 0)
        error("invalid size(%d) ignored \n", buf->size);
    else
    {
        if(buf->va_addr)
        {
            dma_free_attrs(&npu_hw_controls->pdev->dev, buf->size, buf->va_addr, buf->phys_addr, 0);
            sg_free_table(&buf->sgt);
            buf->va_addr = NULL;
        }
    }
    buf->magic_num = IDL_MAGIC;
#else
#ifdef _NOT_USE_DEV_MEM
    info("[vfree] phys_:0x%llX : var_:0x%p : size(0x%X)\n", buf->phys_addr, buf->va_addr, buf->size);

    if(buf->size <= 0)
        error("invalid size(%d) ignored \n", buf->size);
    else
    {
        if(buf->va_addr)
        {
            vfree(buf->va_addr);
            buf->va_addr = NULL;
        }
    }
#else
    mutex_lock(&buf->mutex_lock);
    debug("[Free][core%d] phys_:0x%llX : var_:0x%p : size(0x%X)\n", buf->core_idx, buf->phys_addr, buf->va_addr, buf->size);

    if(buf->va_addr)
    {
        hma_unmap(buf->va_addr);
        buf->va_addr = NULL;
    }

    if(buf->phys_addr)
    {
        hma_free(_npu_pool[buf->core_idx].name, buf->phys_addr);
        buf->phys_addr = 0;
    }
    buf->magic_num = IDL_MAGIC;
    mutex_unlock(&buf->mutex_lock);

    if (&buf->mutex_lock) {
        mutex_destroy(&buf->mutex_lock);
    }
#endif
#endif
}

#ifdef USE_CACHE_DATA
static void _uncache_buffer(struct npu_cache_data *data)
{
    info("[uncache] addr_:0x%p : size(0x%X)\n", data->ptr, data->size);

    if(data->size <= 0)
        error("invalid size(%d) ignored \n", data->size);
    else
    {
        if(data->ptr)
        {
            vfree(data->ptr);
            data->ptr = NULL;
        }
    }
}
#endif

static void _copy_buffer(struct npu_buffer *to, struct npu_buffer *from)
{
    if((from->memory_type == MEMORY_TYPE_DEVICE)&&(from->magic_num != USE_MAGIC))
        error("magic number error(0x%X)\n", from->magic_num);

    to->magic_num = from->magic_num;
    to->memory_type = from->memory_type;
    to->phys_addr = from->phys_addr;
    to->va_addr = from->va_addr;
    to->size = from->size;
#ifdef USE_CACHE_DATA
    to->cache_data.ptr = from->cache_data.ptr;
    to->cache_data.size = from->cache_data.size;
#endif
    to->core_idx = from->core_idx;
#ifdef USE_IOMMU
    to->sgt.nents = from->sgt.nents;
    to->sgt.orig_nents = from->sgt.orig_nents;
    to->sgt.sgl = from->sgt.sgl;
#endif
}

static bool _npu_have_work_task(void)
{
    if(!npu_que_get_node_cnt(_work_task_que))
        return false;

    return true;
}

static bool _npu_have_work_req(void)
{
    if(!npu_que_get_node_cnt(_work_req_que))
        return false;

    return true;
}

static bool _npu_have_work_rsp(struct npu_inst *inst)
{
    return npu_que_check_node_by_id(_work_rsp_que, inst);
}

#if 0 //Not Used
static bool _npu_check_npu_done_from_rsp(struct npu_inst *inst)
{
    return npu_que_check_npu_done_by_id(_work_rsp_que, inst);
}
#endif

#ifdef USE_CACHE_DATA
static int _npu_copy_binary(struct npu_inst *inst, unsigned int idx)
{
#ifdef ENABLE_DATA_DUMP
    unsigned char *pBuf;
#endif
    unsigned long long time_1;
    unsigned long long time_2;

    debug("[%p][core%d] _npu_copy_binary \n", inst, idx);

    inst->prepare_param.core_idx = idx;

    if(inst->cache_prog.ptr)
    {
        if(inst->prepare_param.program.magic_num == IDL_MAGIC)
        {
#ifdef DBG_MTD
            inst->prog_dbg_mtd.num_cnt++;
#endif
            if(_alloc_buffer(&inst->prepare_param.program,
                inst->cache_prog.size, idx, "program"))
            {
                error("[%p][core%d] program buffer allocation fail - %d\n", inst, idx, inst->cache_prog.size);
                return -ENOMEM;
            }

            time_1 = ktime_get_real_ns();
            mutex_lock(&inst->prepare_param.program.mutex_lock);
            if(inst->prepare_param.program.magic_num != USE_MAGIC)
            {
                error("[%p][core%d] program magic number error(0x%X)", inst, idx, inst->prepare_param.program.magic_num);
                mutex_unlock(&inst->prepare_param.program.mutex_lock);
                return -EFAULT;
            }
            memcpy(inst->prepare_param.program.va_addr,inst->cache_prog.ptr,inst->cache_prog.size);

#ifdef ENABLE_FILE_LOAD
            debug("[%p] [NPU_BINARY_TYPE_PROGRAM] Program FILE COPY (0x%X)\n", inst, inst->cache_prog.size);
            read_file("/mnt/lg/flash/data/_liblgnpu/DNE_PRG_ID3_2CORE_DEPTH.bin", inst->prepare_param.program.va_addr, 0xC400);
#endif
#ifdef ENABLE_DATA_DUMP
            pBuf = (unsigned char *)inst->prepare_param.program.va_addr;
            debug("[%p][KDM][Program_Data] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                inst,
                pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif

#ifdef USE_IOMMU
            dma_cache_flush(&inst->prepare_param.program, inst->cache_prog.size, "program");
#else
            cache_flush(inst->prepare_param.program.va_addr, inst->cache_prog.size);
#endif
            time_2 = ktime_get_real_ns();

#ifdef DBG_MTD
            inst->prog_dbg_mtd.acc_ms = time_2 - time_1;
            if(inst->prog_dbg_mtd.sum_ms + inst->prog_dbg_mtd.acc_ms >= ULLONG_MAX)
            {
                noti("[%p] prog_dbg_mtd.sum_ms's value is out of range. It will reset.\n", inst);
                inst->prog_dbg_mtd.sum_ms = 0;
                inst->prog_dbg_mtd.num_cnt = 1;
            }
            inst->prog_dbg_mtd.sum_ms += inst->prog_dbg_mtd.acc_ms;
            debug("[%p][TEST_prog][%d] memcpy time: %lld ns\n", inst, inst->prog_dbg_mtd.num_cnt,
                inst->prog_dbg_mtd.sum_ms/inst->prog_dbg_mtd.num_cnt);
#endif

#ifdef ENABLE_DATA_DUMP
            pBuf = (unsigned char *)inst->prepare_param.program.va_addr;
            debug("[%p] [Program_Data] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                inst,
                pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
            mutex_unlock(&inst->prepare_param.program.mutex_lock);
        }
        else
        {
            error("[%p][core%d] prog_alloc access fail(0x%X)", inst, idx, inst->prepare_param.program.magic_num);
            return -EFAULT;
        }
    }

    if(inst->cache_param.ptr)
    {
        if(inst->prepare_param.weight.magic_num == IDL_MAGIC)
        {
#ifdef DBG_MTD
            inst->weigh_dbg_mtd.num_cnt++;
#endif

            if (_alloc_buffer(&inst->prepare_param.weight,
                inst->cache_param.size, idx, "weight"))
            {
                error("[%p][core%d] weight buffer allocation fail - %d\n", inst, idx, inst->cache_param.size);
                return -ENOMEM;
            }

            time_1 = ktime_get_real_ns();
            mutex_lock(&inst->prepare_param.weight.mutex_lock);
            if(inst->prepare_param.weight.magic_num != USE_MAGIC)
            {
                error("[%p][core%d] weight magic number error(0x%X)", inst, idx, inst->prepare_param.weight.magic_num);
                mutex_unlock(&inst->prepare_param.weight.mutex_lock);
                return -EFAULT;
            }

            memcpy(inst->prepare_param.weight.va_addr,inst->cache_param.ptr,inst->cache_param.size);

#ifdef ENABLE_FILE_LOAD
            debug ("[%p] [NPU_BINARY_TYPE_PARAMETERS] Weight FILE COPY (0x%X)\n", inst, inst->cache_param.size);
            read_file("/mnt/lg/flash/data/_liblgnpu/DNE_WGT_ID3_2CORE_DEPTH.bin", inst->prepare_param.weight.va_addr, 0x436000);
#endif
#ifdef ENABLE_DATA_DUMP
            pBuf = (unsigned char *)inst->prepare_param.weight.va_addr;
            debug("[%p] [Weight_Data] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                inst,
                pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif

#ifdef USE_IOMMU

#else
            cache_flush(inst->prepare_param.weight.va_addr, inst->cache_param.size);
#endif
            time_2 = ktime_get_real_ns();

#ifdef DBG_MTD
            inst->weigh_dbg_mtd.acc_ms = time_2 - time_1;
            if(inst->weigh_dbg_mtd.sum_ms + inst->weigh_dbg_mtd.acc_ms >= ULLONG_MAX)
            {
                noti("[%p]weigh_dbg_mtd.sum_ms's value is out of range. It will reset.\n", inst);
                inst->weigh_dbg_mtd.sum_ms = 0;
                inst->weigh_dbg_mtd.num_cnt = 1;
            }

            inst->weigh_dbg_mtd.sum_ms += inst->weigh_dbg_mtd.acc_ms;
            debug("[%p][TEST][KDM_weigh][%d] memcpy time: %lld ns\n", inst, inst->weigh_dbg_mtd.num_cnt,
                inst->weigh_dbg_mtd.sum_ms/inst->weigh_dbg_mtd.num_cnt);
#endif

#ifdef ENABLE_DATA_DUMP
            pBuf = (unsigned char *)inst->prepare_param.weight.va_addr;
            debug("[%p][KDM][Weight_Data] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                inst,
                pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
            mutex_unlock(&inst->prepare_param.weight.mutex_lock);
        }
        else
        {
            error("[%p][core%d] weight_alloc access fail(0x%X)", inst, idx, inst->prepare_param.weight.magic_num);
            return -EFAULT;
        }
    }

    if(inst->feature_size)
    {
        if(inst->prepare_param.feature.magic_num == IDL_MAGIC)
        {
            if(_alloc_buffer(&inst->prepare_param.feature,
                inst->feature_size, idx, "feature"))
            {
                error("[%p] feature buffer allocation fail - %d\n", inst, inst->feature_size);
                return -ENOMEM;
            }
        }
        else
        {
            error("[%p][core%d] feature_alloc access fail(0x%X)", inst, idx,
                inst->prepare_param.feature.magic_num);
            return -EFAULT;
        }
    }

    debug("[%p][core%d] program.phys_addr[0x%llx] weight.phys_addr[0x%llx]\n", inst, inst->prepare_param.core_idx,
        inst->prepare_param.program.phys_addr,inst->prepare_param.weight.phys_addr);
    info("[%p][core%d][%s] done \n", inst, idx, __func__);

    return 0;
}

static void _npu_free_binary(struct npu_inst *inst)
{
    if(inst->prepare_param.core_idx >= 0)
    {
        if (inst->prepare_param.program.memory_type != MEMORY_TYPE_PHYSICAL) {
            if(inst->prepare_param.program.magic_num == USE_MAGIC)
            {
                _free_buffer(&inst->prepare_param.program);
            }
            if(inst->prepare_param.program.magic_num != IDL_MAGIC)
                error("[%p][core%d] program free fail(0x%X)\n", inst, inst->prepare_param.core_idx, inst->prepare_param.program.magic_num);
        }

        if (inst->prepare_param.weight.memory_type != MEMORY_TYPE_PHYSICAL) {
            if(inst->prepare_param.weight.magic_num == USE_MAGIC)
            {
                _free_buffer(&inst->prepare_param.weight);
            }
            if(inst->prepare_param.weight.magic_num != IDL_MAGIC)
                error("[%p][core%d] weight free fail(0x%X)\n", inst, inst->prepare_param.core_idx, inst->prepare_param.weight.magic_num);
        }

        if (inst->prepare_param.feature.memory_type != MEMORY_TYPE_PHYSICAL) {
            if(inst->prepare_param.feature.magic_num == USE_MAGIC)
            {
                _free_buffer(&inst->prepare_param.feature);
            }
            if(inst->prepare_param.feature.magic_num != IDL_MAGIC)
                error("[%p][core%d] feature free fail(0x%X)\n", inst, inst->prepare_param.core_idx, inst->prepare_param.feature.magic_num);
        }

        info("[%p][core%d] done\n", inst, inst->prepare_param.core_idx);
        inst->prepare_param.core_idx = -1;
    }
    else
        error("[%p][core%d] invalid core idx\n", inst, inst->prepare_param.core_idx);
}

static void _npu_copy_output(struct npu_buffer_info * buf_info)
{
    if((buf_info->inter_output_buf.phys_addr)&&(buf_info->inter_output_buf.magic_num == USE_MAGIC))
    {
        if(buf_info->inter_output_buf.cache_data.ptr)
        {
            memcpy(buf_info->inter_output_buf.cache_data.ptr,buf_info->inter_output_buf.va_addr,buf_info->inter_output_buf.size);
        }
        else
        {
            error("[%p][core%d] inter_output_cache no exit\n", buf_info->inst_id, buf_info->inter_output_buf.core_idx);
        }
    }
    else
    {
        error("[%p][core%d] inter_output_buf no exit(0x%X)\n", buf_info->inst_id, buf_info->inter_output_buf.core_idx, buf_info->inter_output_buf.magic_num);
    }

    debug("[%p][core%d] _npu_copy_output done\n", buf_info->inst_id, buf_info->inter_output_buf.core_idx);
}
#endif

static void _npu_free_input(struct npu_buffer_info * buf_info)
{
	int i = 0;
	for(i=0; i< buf_info->number_of_input_buf; i++)
	{
		if(buf_info->input_buf[i].memory_type != MEMORY_TYPE_PHYSICAL)
		{
#ifdef USE_CACHE_DATA
			if (i==0) {
				if(buf_info->input_buf[i].magic_num == USE_MAGIC)
				{
					_free_buffer(&buf_info->input_buf[i]);
				}
				else
				{
					error("[%p][core%d] input buffer free fail(0x%X)\n", buf_info->inst_id, buf_info->input_buf[i].core_idx, buf_info->input_buf[i].magic_num);
				}

				if(buf_info->input_buf[i].cache_data.ptr != NULL)
				{
					_uncache_buffer(&buf_info->input_buf[i].cache_data);
				}
				else
				{
					error("[%p][core%d] input cache_data free fail(0x%X)\n", buf_info->inst_id, buf_info->input_buf[i].core_idx, buf_info->input_buf[i].cache_data.size);
				}
			}
#else
			if(buf_info->input_buf[i].magic_num == USE_MAGIC)
			{
				_free_buffer(&buf_info->input_buf[i]);
			}
			else
			{
				error("[%p][core%d] input buffer free fail(0x%X)\n", buf_info->inst_id, buf_info->input_buf[i].core_idx, buf_info->input_buf[i].magic_num);
			}
#endif
		}
	}
	info("[%p][core%d] _npu_free_input done\n", buf_info->inst_id, buf_info->input_buf[0].core_idx);
}

static void _npu_free_inter_output(struct npu_buffer_info * buf_info)
{
    if((buf_info->inter_output_buf.phys_addr)&&(buf_info->inter_output_buf.magic_num == USE_MAGIC))
    {
        _free_buffer(&buf_info->inter_output_buf);
    }
    if(buf_info->inter_output_buf.magic_num != IDL_MAGIC)
    {
        error("[%p] inter_output_buf free fail(0x%X)\n", buf_info->inst_id, buf_info->inter_output_buf.magic_num);
    }

    info("[%p][core%d] _npu_free_inter_output done\n", buf_info->inst_id, buf_info->inter_output_buf.core_idx);
}

static bool _thread_should_stop(unsigned int core)
{
    if(_npu_work[core].thread_stop)
        return true;

    return false;
}

static int _npu_run_work_thread(struct work_struct *data)
{
    struct npu_inst *npu_inst;
    struct npu_inst *tmp_inst;
    struct npu_hw *npu_hw = npu_hw_controls->npu_hw;
	int i = 0;
#ifdef ENABLE_DATA_DUMP
    unsigned char *pBuf;
#endif
#ifdef DBG_MTD
    unsigned int avg_ms = 0;
#endif
    unsigned int idx_val;
    struct npu_work_thread *temp_npu_work;
    struct npu_prepare_param *prepare_param;
    struct npu_run_param *run_param;

	temp_npu_work = container_of(data, struct npu_work_thread, _work);
    idx_val = temp_npu_work->core_idx;

    while(!temp_npu_work->thread_stop)
    {
        struct npu_buffer_info *chk_info = NULL;
        struct npu_buffer_info *buf_info = NULL;

        mutex_lock(&wait_queue_lock);
        if (wait_event_interruptible(_work_wait_req,
                _npu_have_work_req() || _thread_should_stop(idx_val)) < 0)
        {
            debug("interrupt [%d / %d ]\n", _npu_have_work_req(), _thread_should_stop(idx_val));
            mutex_unlock(&wait_queue_lock);
            continue;
        }

        if(_thread_should_stop(idx_val))
        {
            mutex_unlock(&wait_queue_lock);
            break;
        }

        chk_info = npu_que_peek(_work_req_que);
        if(chk_info == NULL)
        {
            error("Oops!!\n");
            mutex_unlock(&wait_queue_lock);
            continue;
        }
        else
            tmp_inst = chk_info->inst_id;

        if(tmp_inst->prepare_param.affinity >= 0)
        {
            if(tmp_inst->prepare_param.affinity != idx_val)
            {
                mutex_unlock(&wait_queue_lock);
                debug("affinity mismatch(%d:%d). retry\n", tmp_inst->prepare_param.affinity, idx_val);
                continue;
            }
        }

        mutex_lock(&tmp_inst->sync_lock);

        buf_info = npu_que_find_pop_by_id(_work_req_que, tmp_inst);
        if(buf_info == NULL)
        {
            error("Oops!!!\n");
            mutex_unlock(&tmp_inst->sync_lock);
            mutex_unlock(&wait_queue_lock);
            continue;
        }
        mutex_unlock(&wait_queue_lock);

        npu_inst = buf_info->inst_id;
        buf_info->npu_done = false;

#ifdef DBG_MTD
        npu_inst->cpy_dbg_mtd.start_time = ktime_get_real_ns() / NSEC_PER_MSEC;
#endif

        npu_inst->run_param.number_of_input = buf_info->number_of_input_buf;
        if(npu_inst->run_param.input == NULL)
        {
            npu_inst->run_param.input = kzalloc(sizeof(struct npu_buffer)*buf_info->number_of_input_buf, GFP_KERNEL);
            if (npu_inst->run_param.input == NULL)
            {
                warn("[%p] no memory\n", npu_inst);
                wake_up_interruptible(&npu_inst->work_wait_rsp);
                mutex_unlock(&npu_inst->sync_lock);
                continue;
            }
        }
        for(i=0; i< npu_inst->run_param.number_of_input; i++)
        {
#ifdef USE_CACHE_DATA
			if(buf_info->input_buf[i].memory_type != MEMORY_TYPE_PHYSICAL)
			{
				int total_size=0, j=0;
				for (j=0 ; j<npu_inst->run_param.number_of_input; j++) {
					debug("%s:%d: input tensor %d size : %d\n", __func__, __LINE__, j, buf_info->input_buf[j].cache_data.size);
					total_size += buf_info->input_buf[j].cache_data.size;
				}
				if(buf_info->input_buf[i].cache_data.ptr)
				{
					if (i==0) {
						if(_alloc_buffer(&buf_info->input_buf[i],
									total_size, idx_val, "input"))
						{
							error("[%p][core%d] input buffer allocation fail - %d\n", npu_inst, idx_val, buf_info->input_buf[i].cache_data.size);
							wake_up_interruptible(&npu_inst->work_wait_rsp);
							mutex_unlock(&npu_inst->sync_lock);
							continue;
						}
						buf_info->input_buf[i].size = buf_info->input_buf[i].cache_data.size;
					} else {
						buf_info->input_buf[i].phys_addr = buf_info->input_buf[i-1].phys_addr + buf_info->input_buf[i-1].size;
						buf_info->input_buf[i].va_addr = buf_info->input_buf[i-1].va_addr + buf_info->input_buf[i-1].size;
						buf_info->input_buf[i].magic_num = USE_MAGIC;
					}
				}
				else
				{
					error("[%p][core%d] buf_info->input_buf[%d].cache_data.ptr = NULL\n", npu_inst, idx_val, i);
					wake_up_interruptible(&npu_inst->work_wait_rsp);
					mutex_unlock(&npu_inst->sync_lock);
					continue;
				}
				if(buf_info->input_buf[i].magic_num == USE_MAGIC)
				{
					memcpy(buf_info->input_buf[i].va_addr,buf_info->input_buf[i].cache_data.ptr,buf_info->input_buf[i].cache_data.size);
				}
				else
				{
					error("[%p][core%d] input buffer copy fail - %d\n", npu_inst, idx_val, buf_info->input_buf[i].cache_data.size);
				}
			}
#endif
            _copy_buffer(&npu_inst->run_param.input[i], &buf_info->input_buf[i]);
            if(npu_inst->run_param.input[i].memory_type != MEMORY_TYPE_PHYSICAL)
            {
                mutex_lock(&npu_inst->run_param.input[i].mutex_lock);
                if(npu_inst->run_param.input[i].magic_num != USE_MAGIC)
                {
                    error("[%p] input[%d] magic number error(0x%X)", npu_inst, i, npu_inst->run_param.input[i].magic_num);
                }
                else
                {
#ifdef USE_IOMMU
                    info("input va_addr %p, size %x\n", npu_inst->run_param.input[i].va_addr, npu_inst->run_param.input[i].size);
                    dma_cache_flush(&npu_inst->run_param.input[i], npu_inst->run_param.input[i].size, "input");
#else
                    cache_flush(npu_inst->run_param.input[i].va_addr, npu_inst->run_param.input[i].size);
#endif
                }
                mutex_unlock(&npu_inst->run_param.input[i].mutex_lock);
            }
            debug("[%p] run_param input[%d]->phys_addr[0x%llx]\n", npu_inst,
                    i, npu_inst->run_param.input[i].phys_addr);
        }

        if(buf_info->output_buf[0].memory_type != MEMORY_TYPE_PHYSICAL)
        {
            if((buf_info->inter_output_buf.cache_data.ptr != NULL)
                        &&(buf_info->inter_output_buf.magic_num != USE_MAGIC))
            {
                if(_alloc_buffer(&buf_info->inter_output_buf,
                        npu_inst->output_size, idx_val, "output"))
                {
                    error("[%p][core%d] inter output buffer allocation fail - %d\n", npu_inst, idx_val, npu_inst->output_size);
                    for(i=0; i< npu_inst->run_param.number_of_input; i++)
                    {
                        if(buf_info->input_buf[i].magic_num == USE_MAGIC)
                        {
                            _free_buffer(&buf_info->input_buf[i]);
                        }
                    }
                    wake_up_interruptible(&npu_inst->work_wait_rsp);
                    mutex_unlock(&npu_inst->sync_lock);
                    continue;
                }
            }
            _copy_buffer(&npu_inst->run_param.output, &buf_info->inter_output_buf);
        }
        else
        {
            _copy_buffer(&npu_inst->run_param.output, &buf_info->output_buf[0]);
        }

#ifdef ENABLE_DATA_DUMP
        for(i=0; i< buf_info->number_of_input_buf; i++)
        {
            if(npu_inst->run_param.input[i].memory_type != MEMORY_TYPE_PHYSICAL)
            {
                pBuf = (unsigned char *)npu_inst->run_param.input[i].va_addr;
                debug("[%p] [Input_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                        npu_inst,i,
                        pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                        pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
            }
            else
                error("input_%d data dump is not supported by MEMORY_TYPE_PHYSICAL\n", i);
        }
        if(npu_inst->run_param.output.memory_type != MEMORY_TYPE_PHYSICAL)
        {
            pBuf = (unsigned char *)npu_inst->run_param.output.va_addr;
            debug("[%p] [Output_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
                    npu_inst,i,
                    pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                    pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
        }
        else
            error("output_%d data dump is not supported by MEMORY_TYPE_PHYSICAL\n");
#endif

        debug("[%p] run_param output.phys_addr[0x%llx]\n", npu_inst,
                npu_inst->run_param.output.phys_addr);

#ifdef USE_CACHE_DATA
        if(_npu_copy_binary(npu_inst, idx_val))
        {
            error("[%p] binary data copy fail\n", npu_inst);
            _npu_free_binary(npu_inst);
            _npu_free_input(buf_info);
            _npu_free_inter_output(buf_info);
            wake_up_interruptible(&npu_inst->work_wait_rsp);
            mutex_unlock(&npu_inst->sync_lock);
            continue;
        }

        if(npu_hw->prepare(npu_hw, idx_val, &npu_inst->prepare_param) == 0)
        {
            info("[%p][npu_hw] prepare_param done\n", npu_inst);
        }
        else
        {
            error("[%p][npu_hw] prepare_param fail\n", npu_inst);
            npu_hw->reset(npu_hw, idx_val);

            _npu_free_inter_output(buf_info);

            if(buf_info->output_buf != NULL)
                kfree_null((void **)&buf_info->output_buf);
        }
#else
        npu_inst->prepare_param.core_idx = idx_val;

        if(npu_hw->prepare(npu_hw, idx_val, &npu_inst->prepare_param) == 0)
        {
            info("[%p][npu_hw] prepare_param done\n", npu_inst);
        }
        else
        {
            error("[%p][npu_hw] prepare_param fail\n", npu_inst);
            npu_hw->reset(npu_hw, idx_val);

            _npu_free_inter_output(buf_info);
            if(buf_info->output_buf != NULL)
                kfree_null((void **)&buf_info->output_buf);
        }
#endif

        prepare_param = &npu_inst->prepare_param;
        run_param = &npu_inst->run_param;
        run_param->program = &prepare_param->program;
        run_param->weight = &prepare_param->weight;
        run_param->feature = &prepare_param->feature;

#ifdef DBG_MTD
        npu_inst->dbg_mtd.start_time = ktime_get_real_ns() / NSEC_PER_MSEC;
        npu_inst->dbg_mtd.npu_latency = 0;
#endif

        if(npu_hw->run(npu_hw, idx_val, &npu_inst->run_param) == 0)
        {
            unsigned long flag;

            info("[%p][npu_hw] run done\n", npu_inst);
            buf_info->npu_done = true;
            npu_inst->dbg_mtd.npu_latency = npu_inst->run_param.npu_latency;

#ifdef USE_IOMMU
            if ((buf_info->inter_output_buf.memory_type != MEMORY_TYPE_PHYSICAL))
                dma_cache_invalidate(&buf_info->inter_output_buf, buf_info->inter_output_buf.size, "output");

            // dma unmap for physical address
            for(i=0; i< npu_inst->run_param.number_of_input; i++)
            {
                if (buf_info->input_buf[i].memory_type == MEMORY_TYPE_PHYSICAL) {
                    if (buf_info->input_buf[i].phys_addr > 0) {
                        dma_unmap_resource(&npu_hw_controls->pdev->dev, buf_info->input_buf[i].phys_addr,
                            buf_info->input_buf[i].size, DMA_BIDIRECTIONAL,0);
                    }
                }
            }

            if(buf_info->output_buf[0].memory_type == MEMORY_TYPE_PHYSICAL) {
                if (buf_info->output_buf[0].phys_addr > 0) {
                    if (buf_info->output_buf[0].phys_addr > 0) {
                        dma_unmap_resource(&npu_hw_controls->pdev->dev, buf_info->output_buf[0].phys_addr,
                            npu_inst->output_size, DMA_BIDIRECTIONAL,0);
                    }
                }
            }
#endif

#ifdef USE_CACHE_DATA
            _npu_free_input(buf_info);
            if(buf_info->inter_output_buf.cache_data.ptr != NULL)
            {
                _npu_copy_output(buf_info);
                _npu_free_inter_output(buf_info);
            }

            for(i=0; i< npu_inst->run_param.number_of_input; i++) {
                if(npu_inst->run_param.input[i].memory_type != MEMORY_TYPE_PHYSICAL) {
                    npu_inst->run_param.input[i].phys_addr = 0;
                }
            }
            if(npu_inst->run_param.output.memory_type != MEMORY_TYPE_PHYSICAL) {
                npu_inst->run_param.output.phys_addr = 0;
            }
#else
            _npu_free_input(buf_info);
#endif
            if(npu_que_push(_work_rsp_que, buf_info) < 0)
            {
                error("Fail to push _work_rsp_que \n");
            }

#ifdef USE_CACHE_DATA
            _npu_free_binary(npu_inst);
#endif

            wake_up_interruptible(&npu_inst->work_wait_rsp);

            mutex_unlock(&npu_inst->sync_lock);

#ifdef DBG_MTD
            npu_inst->dbg_mtd.end_time = ktime_get_real_ns() / NSEC_PER_MSEC;
            npu_inst->dbg_mtd.acc_ms = npu_inst->dbg_mtd.end_time - npu_inst->dbg_mtd.start_time;
            spin_lock_irqsave(&npu_inst->dbg_mtd.dbg_mtd_lock, flag);
            if(npu_inst->dbg_mtd.sum_ms + npu_inst->dbg_mtd.acc_ms >= ULLONG_MAX)
            {
                noti("[%p] dbg_mtd.sum_ms's value is out of range. It will reset.\n", npu_inst);
                npu_inst->dbg_mtd.sum_ms = 0;
                npu_inst->dbg_mtd.num_cnt = 0;
            }
            npu_inst->dbg_mtd.sum_ms += npu_inst->dbg_mtd.acc_ms;
            npu_inst->dbg_mtd.num_cnt++;

            npu_inst->cpy_dbg_mtd.acc_ms = npu_inst->dbg_mtd.end_time - npu_inst->cpy_dbg_mtd.start_time;
            if(npu_inst->cpy_dbg_mtd.sum_ms + npu_inst->cpy_dbg_mtd.acc_ms >= ULLONG_MAX)
            {
                noti("[%p] cpy_dbg_mtd.sum_ms's value is out of range. It will reset.\n", npu_inst);
                npu_inst->cpy_dbg_mtd.sum_ms = 0;
                npu_inst->cpy_dbg_mtd.num_cnt = 0;
            }
            npu_inst->cpy_dbg_mtd.sum_ms += npu_inst->cpy_dbg_mtd.acc_ms;
            npu_inst->cpy_dbg_mtd.num_cnt++;

            avg_ms = (unsigned int)(npu_inst->dbg_mtd.sum_ms / npu_inst->dbg_mtd.num_cnt);
            npu_inst->dbg_mtd.fps = 1000 / avg_ms;

            if(!(npu_inst->dbg_mtd.num_cnt % 5000))
            {
                debug("[%p] NPU time: %llums, avg time : %dms, executed tensors: %d, FPS:%d\n", npu_inst,
                    npu_inst->dbg_mtd.acc_ms, avg_ms, npu_inst->dbg_mtd.num_cnt, npu_inst->dbg_mtd.fps);
            }
            spin_unlock_irqrestore(&npu_inst->dbg_mtd.dbg_mtd_lock, flag);
#endif
        }
        else
        {
            error("[%p] fail to run \n", npu_inst);
            buf_info->npu_done = false;
#ifdef USE_IOMMU
            // dma unmap for physical address
            for(i=0; i< npu_inst->run_param.number_of_input; i++)
            {
                if (buf_info->input_buf[i].memory_type == MEMORY_TYPE_PHYSICAL) {
                    if (buf_info->input_buf[i].phys_addr > 0) {
                        dma_unmap_resource(&npu_hw_controls->pdev->dev, buf_info->input_buf[i].phys_addr,
                            buf_info->input_buf[i].size, DMA_BIDIRECTIONAL,0);
                    }
                }
            }

            if(buf_info->output_buf[0].memory_type == MEMORY_TYPE_PHYSICAL) {
                if (buf_info->output_buf[0].phys_addr > 0) {
                    if (buf_info->output_buf[0].phys_addr > 0) {
                        dma_unmap_resource(&npu_hw_controls->pdev->dev, buf_info->output_buf[0].phys_addr,
                            npu_inst->output_size, DMA_BIDIRECTIONAL,0);
                    }
                }
            }
#endif
#ifdef USE_CACHE_DATA
            _npu_free_input(buf_info);
            if(buf_info->inter_output_buf.cache_data.ptr != NULL)
            {
                _npu_free_inter_output(buf_info);
            }

            for(i=0; i< npu_inst->run_param.number_of_input; i++) {
                if(npu_inst->run_param.input[i].memory_type != MEMORY_TYPE_PHYSICAL) {
                    npu_inst->run_param.input[i].phys_addr = 0;
                }
            }
            if(npu_inst->run_param.output.memory_type != MEMORY_TYPE_PHYSICAL) {
                npu_inst->run_param.output.phys_addr = 0;
            }
#else
            _npu_free_input(buf_info);
            _npu_free_inter_output(buf_info);
#endif
            if(npu_que_push(_work_rsp_que, buf_info) < 0)
            {
                error("Fail to push _work_rsp_que \n");
            }

#ifdef USE_CACHE_DATA
            _npu_free_binary(npu_inst);
#endif

            wake_up_interruptible(&npu_inst->work_wait_rsp);
            mutex_unlock(&npu_inst->sync_lock);

            npu_hw->reset(npu_hw, idx_val);

        }

        temp_npu_work->run_cnt++;
        if(!(temp_npu_work->run_cnt%50000))
            noti("npu_work_thread(core%d) running [%d]\n", temp_npu_work->core_idx, temp_npu_work->run_cnt);
    }

    noti("npu_run_work thread - exit\n");

    return 0;

}

static void cb_timer_utilization(struct timer_list *timer) {
    unsigned long flag;
    struct npu_inst *npu_inst = from_timer(npu_inst, timer, timer_utilization);
    spin_lock_irqsave(&npu_inst->dbg_mtd.dbg_mtd_lock, flag);
    npu_inst->dbg_mtd.avg_ms = npu_inst->dbg_mtd.sum_ms / npu_inst->dbg_mtd.num_cnt;
    npu_inst->dbg_mtd.sum_ms = 0;
    npu_inst->dbg_mtd.num_cnt = 0;
    mod_timer(&npu_inst->timer_utilization, jiffies + msecs_to_jiffies(1000));
    spin_unlock_irqrestore(&npu_inst->dbg_mtd.dbg_mtd_lock, flag);

    debug("avg_ms %llu\n", npu_inst->dbg_mtd.avg_ms);
}

static int npu_drv_open(struct inode *inode, struct file *file)
{
    int minor = iminor(inode);
    int ret, i;
    struct npu_inst *inst = NULL;
    struct npu_hw_control *control = npu_hw_controls;
    struct npu_hw *hw;
    struct npu_work_thread *temp_npu_work;

    info("%s (%d)\n", __func__, minor);

    while(control)
    {
    #ifdef USE_IOMMU
        if(MINOR(control->pdev->dev.devt) == minor)
    #else
        if(MINOR(control->pdev.dev.devt) == minor)
    #endif
        {
            break;
        }

        control = control->next;
    }

    mutex_lock(&_npu_device_lock);
    if(!control)
    {
        error("no such npu_hw for minor %d\n", minor);
        mutex_unlock(&_npu_device_lock);
        return -ENODEV;
    }
    else
    {
        hw = control->npu_hw;
        ret = hw->init(hw);
        if(ret < 0)
        {
            error("%s init failed.\n", hw->name);
            mutex_unlock(&_npu_device_lock);
            return -EFAULT;
        }
        else
        {
            control->chip = ret;
            debug("%s init(0x%X) done.\n", hw->name, control->chip);
        }
    }

    if(!_inst_cnt)
    {
        debug("%s Work Init(only once)\n", __func__);
    #ifdef USE_IOMMU
        _npu_pm_resume(&control->pdev->dev);
    #else
        _npu_pm_resume(&control->pdev.dev);
    #endif

        _work_task_que = npu_que_open();
        if(!_work_task_que) {
            error("_work_task_que, npu_que_open fail\n");
            mutex_unlock(&_npu_device_lock);
            return -ENODEV;
        }
        _work_req_que = npu_que_open();
        if(!_work_req_que) {
            error("_work_req_que, npu_que_open fail\n");
            mutex_unlock(&_npu_device_lock);
            return -ENODEV;
        }
        _work_rsp_que = npu_que_open();
        if(!_work_rsp_que) {
            error("_work_rsp_que, npu_que_open fail\n");
            mutex_unlock(&_npu_device_lock);
            return -ENODEV;
        }

        init_waitqueue_head(&_work_wait_req);

        if(control->chip >= LX_CHIP_O24)
            control->core_num = NPU_CORE_MAX;
        else
            control->core_num = 1; //LX_CHIP_O22 case

        mutex_init(&wait_queue_lock);
        for(i = 0; i < control->core_num; i++)
        {
            temp_npu_work = &_npu_work[i];
            if(temp_npu_work->_work_highpri_wq == NULL)
                temp_npu_work->_work_highpri_wq = alloc_workqueue(_npu_work_name[i], WQ_UNBOUND, 0);

            if(!temp_npu_work->_work_highpri_wq)
            {
                error("npu_highpri_workque creation fail\n");
                mutex_unlock(&_npu_device_lock);
                return -EFAULT;
            }

            temp_npu_work->core_idx = i;
            temp_npu_work->run_cnt = 0;
            temp_npu_work->thread_stop = false;
            INIT_WORK(&temp_npu_work->_work, (void *)_npu_run_work_thread);
            queue_work(temp_npu_work->_work_highpri_wq, &temp_npu_work->_work);
            debug("%s Work[%d] Init Done. \n", __func__, temp_npu_work->core_idx);
        }
    }

    inst = kzalloc(sizeof (struct npu_inst), GFP_KERNEL);
    if (!inst)
    {
        error("no memory\n");
        mutex_unlock(&_npu_device_lock);
        return -ENOMEM;
    }

    _inst_cnt++;
    mutex_unlock(&_npu_device_lock);

    mutex_init(&inst->mutex_lock);
    mutex_init(&inst->sync_lock);

    mutex_lock(&inst->mutex_lock);
    inst->period = -1;
    inst->last_req_id = 0;
    inst->set_exec_mem = false;
    init_waitqueue_head(&inst->work_wait_rsp);

    mutex_lock(&npu_inst_list_lock);
    list_add(&inst->list, &npu_inst_list);
    mutex_unlock(&npu_inst_list_lock);

#ifdef DBG_MTD
    inst->dbg_mtd.num_cnt = 0;
    inst->dbg_mtd.overflow_cnt = 0;
    inst->dbg_mtd.sum_ms = 0;
	inst->prog_dbg_mtd.num_cnt=0;
	inst->prog_dbg_mtd.sum_ms=0;
	inst->weigh_dbg_mtd.num_cnt=0;
	inst->weigh_dbg_mtd.sum_ms=0;
    inst->sche_dbg_mtd.num_cnt = 0;
    inst->sche_dbg_mtd.overflow_cnt = 0;
    inst->sche_dbg_mtd.sum_ms = 0;
#endif
    inst->prepare_param.program.magic_num = IDL_MAGIC;
    inst->prepare_param.weight.magic_num = IDL_MAGIC;
    inst->prepare_param.feature.magic_num = IDL_MAGIC;
    inst->prepare_param.affinity = -1;
    inst->prepare_param.core_idx = -1;

    file->private_data = inst;

    spin_lock_init(&inst->dbg_mtd.dbg_mtd_lock);
    timer_setup(&inst->timer_utilization, cb_timer_utilization, 0);
    mod_timer(&inst->timer_utilization, jiffies + msecs_to_jiffies(1000));

    noti("%s, pid=%d, tgid=%d)\n", current->comm, task_pid_nr(current), task_tgid_nr(current));
    inst->procces_id = task_tgid_nr(current);

    noti("[%p] %s done. cnt(%d)\n", inst, __func__, _inst_cnt);
    mutex_unlock(&inst->mutex_lock);

    return 0;

}

#ifdef ENABLE_FILE_LOAD
static int read_file( char *filename, char *data, int len)
{
	struct file *pFILE;
	static int offset = 0;
	mm_segment_t old_fs = get_fs();
	loff_t  pos = 0;
    int ret = 0;

	set_fs(KERNEL_DS);

	pFILE = filp_open( filename, O_RDONLY, 0);

	if(IS_ERR(pFILE) || !pFILE->f_op) {
		error(" filp_open error!!!\n");
		return -1;
	}

    pFILE->f_pos = 0;
    ret = vfs_read(pFILE, data, len, &pFILE->f_pos);
    debug("[read_file] vfs_read = %d\n", ret);

	filp_close( pFILE, 0);
	set_fs(old_fs);

    return 0;
}
#endif

#ifdef ENABLE_DATA_DUMP
static int dump_file(char *filename, char *data, int len)
{
	struct file *pFILE;
	static int offset=0;
	mm_segment_t old_fs = get_fs();
	loff_t  pos =0;
    int ret=0;

    debug("dump file ... %s. len=0x%X).\n",
        filename, len);

	set_fs(KERNEL_DS);

	pFILE = filp_open(filename, O_WRONLY|O_CREAT, 0644);

	if(IS_ERR(pFILE) || !pFILE->f_op) {
		error(" filp_open error!!!\n");
		return -1;
	}

    pFILE->f_pos = 0;
    if(pFILE)
    {
        ret = vfs_write(pFILE, data, len, &pFILE->f_pos);
        debug("[dump_file] vfs_write = %d\n", ret);
    }

	filp_close( pFILE, NULL);
	set_fs(old_fs);

    return 0;
}
#endif

static int _npu_set_binary(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;
    NPU_BINARY_T param;
#ifdef ENABLE_DATA_DUMP
    unsigned char *pBuf;
#endif

    info("[%p] _npu_set_binary\n", inst);

    if(inst->set_exec_mem == true)
    {
        inst->set_exec_mem = false;
    }

    ret = copy_from_user((void*)&param, (const void __user*)arg, sizeof(NPU_BINARY_T));
    if(ret)
    {
        error ("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    switch(param.type)
    {
        case NPU_BINARY_TYPE_PROGRAM:
            debug("[%p] _npu_set_binary[NPU_BINARY_TYPE_PROGRAM]\n", inst);

#ifdef USE_CACHE_DATA
            ret = _cache_buffer(&inst->cache_prog,
                            param.size, "program");
#else
            ret = _alloc_buffer(&inst->prepare_param.program,
                            param.size, EXTRA_POOL_IDX, "program");
#endif
            if(ret)
            {
                error("[%p] program buffer allocation fail - %d\n", inst, param.size);
                return -EFAULT;
            }
            debug("[%p] program buffer allocated - %d\n", inst, param.size);

#ifdef USE_CACHE_DATA
            ret = copy_from_user(inst->cache_prog.ptr, param.data, param.size);
#else
            ret = copy_from_user(inst->prepare_param.program.va_addr, param.data, param.size);
#endif
            if(ret)
            {
                error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                return -EFAULT;
            }

#ifdef ENABLE_FILE_LOAD
            debug("[%p] [NPU_BINARY_TYPE_PROGRAM] Program FILE COPY (0x%X)\n", inst, param.size);
#ifdef USE_CACHE_DATA
            read_file("/mnt/lg/flash/data/_liblgnpu/20210928.1.DNE_PRG_ID3_2CORE_DEPTH_YC420.bin", inst->cache_prog.ptr, param.size);
#else
            read_file("/mnt/lg/flash/data/_liblgnpu/20210928.1.DNE_PRG_ID3_2CORE_DEPTH_YC420.bin", inst->prepare_param.program.va_addr, param.size);
#endif
#endif
#ifdef ENABLE_DATA_DUMP
#ifdef USE_CACHE_DATA
            pBuf = (unsigned char *)inst->cache_prog.ptr;
#else
            pBuf = (unsigned char *)inst->prepare_param.program.va_addr;
#endif
            debug("[%p] [Program_Data] 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X \n",
                    inst,
                    pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                    pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif

#ifndef USE_CACHE_DATA
            cache_flush(inst->prepare_param.program.va_addr, param.size);
#endif
        break;

        case NPU_BINARY_TYPE_PARAMETERS:
            debug("[%p] _npu_set_binary[NPU_BINARY_TYPE_PARAMETERS]\n", inst);

#ifdef USE_CACHE_DATA
            ret = _cache_buffer(&inst->cache_param, param.size, "weight");
#else
            ret = _alloc_buffer(&inst->prepare_param.weight, param.size, EXTRA_POOL_IDX, "weight");
#endif
            if(ret)
            {
                error("[%p] weight buffer allocation fail - %d\n", inst, param.size);
                return -EFAULT;
            }
            debug("[%p] weight buffer allocated - %d\n", inst, param.size);

#ifdef USE_CACHE_DATA
            ret = copy_from_user (inst->cache_param.ptr, param.data, param.size);
#else
            ret = copy_from_user (inst->prepare_param.weight.va_addr, param.data, param.size);
#endif
            if(ret)
            {
                error("[%p] copy_from_user failed\n", inst);
                return -EFAULT;
            }
#ifdef ENABLE_FILE_LOAD
            debug("[%p] [NPU_BINARY_TYPE_PARAMETER] Parameter FILE COPY (0x%X)\n", inst, param.size);
#ifdef USE_CACHE_DATA
            read_file("/mnt/lg/flash/data/_liblgnpu/AI_Lab_MobileNet_V2_wgtmem_1.bin", inst->cache_param.ptr, param.size);
#else
            read_file("/mnt/lg/flash/data/_liblgnpu/AI_Lab_MobileNet_V2_wgtmem_1.bin", inst->prepare_param.weight.va_addr, param.size);
#endif
#endif
#ifdef ENABLE_DATA_DUMP
#ifdef USE_CACHE_DATA
            pBuf = (unsigned char *)inst->cache_param.ptr;
#else
            pBuf = (unsigned char *)inst->prepare_param.weight.va_addr;
#endif
            debug("[%p] [Parameter_Data] 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X \n",
                    inst,
                    pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
                    pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif

#ifndef USE_CACHE_DATA
            cache_flush(inst->prepare_param.weight.va_addr, param.size);
#endif
        break;

        default:
            error("[%p] unkonwn type command, %d\n", inst, param.type);
            return -ENOIOCTLCMD;
    }

    return ret;
}

static int _npu_get_tensor_type_size(TENSOR_TYPE_T type) {
    int size = 0;
    switch(type) {
    case TENSOR_TYPE_INT8:
        size = sizeof(int8_t);
        break;
    case TENSOR_TYPE_INT16:
        size = sizeof(int16_t);
        break;
    case TENSOR_TYPE_INT32:
        size = sizeof(int32_t);
        break;
    case TENSOR_TYPE_INT64:
        size = sizeof(int64_t);
        break;
    case TENSOR_TYPE_FLOAT32:
        size = sizeof(float);
        break;
    case TENSOR_TYPE_UINT8:
        size = sizeof(uint8_t);
        break;
    case TENSOR_TYPE_NONE:
    case TENSOR_TYPE_FLOAT16:
    case TENSOR_TYPE_STRING:
    case TENSOR_TYPE_BOOL:
    case TENSOR_TYPE_COMPLEX64:
    default:
        size = 0;
        break;
    }
    debug("tensor_type(%d) size(%d)\n", type, size);
    return size;
}

static int _npu_set_input_tensor_info(struct npu_inst *inst, unsigned long arg)
{
    int ret, i, j = 0;
    unsigned int cal, type_size = 0;
    TENSOR_INFO_T param;
    TENSOR_SHAPE_T* shapes = NULL;
    int* dim = NULL;

    inst->input_num = 0;

    ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(TENSOR_INFO_T));
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    shapes = kzalloc(sizeof(TENSOR_SHAPE_T)*param.number_of_shape, GFP_KERNEL);
    if(!shapes)
    {
        error("[%p] kzalloc failed. \n", inst);
        return -ENOMEM;
    }

    ret = copy_from_user(shapes, (void __user*) param.tensor_shape, sizeof(TENSOR_SHAPE_T)*param.number_of_shape);
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        if(shapes)
            kfree_null((void **)&shapes);
        return -EFAULT;
    }

    inst->input_num = param.number_of_shape;
    debug("[%p] inst->input_num (%d)\n", inst, inst->input_num);

    if((inst->input_info == NULL)&&(inst->input_num))
    {
        inst->input_info =
            kzalloc(sizeof(struct npu_tensor_info)*(inst->input_num), GFP_KERNEL);
        if(inst->input_info == NULL)
        {
            error("[%p] no memory\n", inst);
            if(shapes)
                kfree_null((void **)&shapes);
            return -ENOMEM;
        }

        for(i = 0; i < inst->input_num; i++)
        {
            cal = 1;
            inst->input_info[i].type = shapes[i].type;
            inst->input_info[i].dim_size = shapes[i].dim_size;
            dim = kzalloc(shapes[i].dim_size*sizeof(int), GFP_KERNEL);
            if(!dim)
            {
                error("[%p] kzalloc failed. \n", inst);
                ret = -ENOMEM;
                break;
            }
            shapes[i].dim = compat_ptr(shapes[i].compat_dim);
            ret = copy_from_user(dim, (void __user*) shapes[i].dim, sizeof(int)*shapes[i].dim_size);
            if (ret)
            {
                error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                if(dim)
                    kfree_null((void **)&dim);
                ret = -EFAULT;
                break;
            }
            for (j = 0; j < shapes[i].dim_size; j++)
            {
                debug("[%p] [input_tensor_%d] dim[%d] = %d", inst, i, j, dim[j]);
                if(cal > INT_MAX / dim[j])
                {
                    error("[%p] potential overflow input_tensor_%d dim[%d](%d)\n", inst, i, j, dim[j]);
                    ret = -EFAULT;
                    break;
                }
                cal *= dim[j];
#if 1 //byDM__WA
                if( ((i==0)&&(j==2)&&(dim[j]==4))
					|| ((i==1)&&(j==2)&&(dim[j]==1)) )
                {
                    debug("[%p] This Network is IMAGE_DATA\n", inst);
                    inst->prepare_param.data_img = true;
                }
#endif
            }
            kfree_null((void **)&dim);

            if(ret)
            {
                break;
            }

            type_size = _npu_get_tensor_type_size(inst->input_info[i].type);
            if(type_size)
            {
                if(cal > INT_MAX / type_size)
                {
                    error("[%p] potential overflow with type size[%d]\n", inst, type_size);
                    ret = -EFAULT;
                    break;
                }
                cal *= type_size;
            }
            else
            {
                error("[%p] not support tensor type[%d]\n", inst, inst->input_info[i].type);
                ret = -EFAULT;
                break;
            }

            inst->input_info[i].data_size = cal;
            debug("[%p] inst->input_info[%d].data_size = %d", inst, i, cal);
        }
    }
    else
    {
        error("[%p] _npu_set_input_tensor_info [ERR]\n", inst);
        ret = -EINVAL;
    }

    kfree_null((void **)&shapes);

    return ret;
}

static int _npu_set_output_tensor_info(struct npu_inst *inst, unsigned long arg)
{
    int ret, i, j = 0;
    unsigned int cal, type_size = 0;
    TENSOR_INFO_T param;
    TENSOR_SHAPE_T* shapes = NULL;
    int* dim = NULL;

    inst->output_num = 0;

    ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(TENSOR_INFO_T));
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    shapes = kzalloc(sizeof(TENSOR_SHAPE_T)*param.number_of_shape, GFP_KERNEL);
    if(!shapes)
    {
        error("[%p] kzalloc failed. \n", inst);
        return -ENOMEM;
    }

    ret = copy_from_user(shapes, (void __user*) param.tensor_shape, sizeof(TENSOR_SHAPE_T)*param.number_of_shape);
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        if(shapes)
            kfree_null((void **)&shapes);
        return -EFAULT;
    }

    inst->output_num = param.number_of_shape;
    debug("[%p] inst->output_num (%d)\n", inst, inst->output_num);

    if((inst->output_info == NULL)&&(inst->output_num))
    {
        inst->output_info =
            kzalloc(sizeof(struct npu_tensor_info)*(inst->output_num), GFP_KERNEL);
        if(inst->output_info == NULL)
        {
            error("[%p] no memory\n", inst);
            if(shapes)
                kfree_null((void **)&shapes);
            return -ENOMEM;
        }

        for(i=0; i< inst->output_num; i++)
        {
            cal = 1;
            inst->output_info[i].type = shapes[i].type;
            inst->output_info[i].dim_size = shapes[i].dim_size;
            dim = kzalloc(shapes[i].dim_size*sizeof(int), GFP_KERNEL);
            if(!dim)
            {
                error("[%p] kzalloc failed. \n", inst);
                ret = -ENOMEM;
                break;
            }
            shapes[i].dim = compat_ptr(shapes[i].compat_dim);
            ret = copy_from_user(dim, (void __user*) shapes[i].dim, sizeof(int)*shapes[i].dim_size);
            if(ret)
            {
                error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                if(dim)
                    kfree_null((void **)&dim);
                ret = -EFAULT;
                break;
            }
            for(j = 0; j < shapes[i].dim_size; j++)
            {
                debug("[%p] [output_tensor_%d] dim[%d] = %d", inst, i, j, dim[j]);
                if(cal > INT_MAX / dim[j])
                {
                    error("[%p] potential overflow output_tensor_%d dim[%d](%d)\n", inst, i, j, dim[j]);
                    ret = -EFAULT;
                    break;
                }
                cal *= dim[j];
            }
            kfree_null((void **)&dim);

            if(ret)
            {
                break;
            }

            type_size = _npu_get_tensor_type_size(inst->output_info[i].type);
            if(type_size)
            {
                if(cal > INT_MAX / type_size)
                {
                    error("[%p] potential overflow with type size[%d]\n", inst, type_size);
                    ret = -EFAULT;
                    break;
                }
                cal *= type_size;
            }
            else
            {
                error("[%p] not support tensor type[%d]\n", inst, inst->output_info[i].type);
                ret = -EFAULT;
                break;
            }

            inst->output_info[i].data_size = cal;
            debug("[%p] inst->output_info[%d].data_size = %d", inst, i, cal);
        }
    }
    else
    {
        error("[%p] _npu_set_output_tensor_info Error\n", inst);
        ret = -EINVAL;
    }

    kfree_null((void **)&shapes);

    return ret;
}

static int _npu_set_feature_buffer(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;

#ifndef USE_CACHE_DATA
    ret = _alloc_buffer(&inst->prepare_param.feature, arg, EXTRA_POOL_IDX, "feature");
    if(ret)
    {
        error("[%p] feature buffer allocation fail - %ld\n", inst, arg);
        return -EFAULT;
    }
#else
    inst->feature_size = arg;
    debug("[%p] inst->feature_size = %d\n", inst, inst->feature_size);
#endif

    return ret;
}

static int _npu_set_private_data(struct npu_inst *inst, unsigned long arg)
{
    int ret, i = 0;
    unsigned int    stride_size;
    PRIVATE_DATA_T  param;
    DNE_PRIVATE_T*  dne_private = NULL;
    LNX_PRIVATE_T*  lnx_private = NULL;
    REGISTER_MAP_T* registers = NULL;
    STRIDE_T*       strides = NULL;
    struct npu_hw_control *control = npu_hw_controls;

    inst->input_size = 0;
    inst->output_size = 0;

    ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(PRIVATE_DATA_T));
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    debug("[%p] [_npu_set_private_data] type(%d) size(%d)\n", inst, param.type, param.size);

    if(param.type != NPU_PRIVATE_NONE)
    {
        switch(param.type)
        {
            case NPU_PRIVATE_DNE:
            {
                if(control->chip != 0x26) //LX_CHIP_O22
                {
                    error("[%p] %s param.type mismatch. (0x%X) \n", inst, __func__, control->chip);
                    return -EFAULT;
                }

                dne_private = kzalloc(sizeof(DNE_PRIVATE_T), GFP_KERNEL);

                ret = copy_from_user(dne_private, (void __user*) param.data, sizeof(DNE_PRIVATE_T));

                if(ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(dne_private)
                        kfree_null((void **)&dne_private);
                    return -EFAULT;
                }

                debug("[%p] [_npu_set_private_data] dne_private::reg_num(%d) str_num(%d) in_off(%d) out_off(%d)\n", inst,
                dne_private->number_of_registers, dne_private->number_of_strides,
                dne_private->number_of_input_offsets, dne_private->number_of_output_offsets);

                if(dne_private->number_of_registers > 0)
                {
                    registers = kzalloc(sizeof(REGISTER_MAP_T)*dne_private->number_of_registers, GFP_KERNEL);

                    dne_private->registers = compat_ptr(dne_private->compat_registers);

                    ret = copy_from_user(registers, (void __user*) dne_private->registers,
                            sizeof(REGISTER_MAP_T)*dne_private->number_of_registers);
                    if(ret)
                    {
                        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                        if(registers)
                            kfree_null((void **)&registers);
                        if(dne_private)
                            kfree_null((void **)&dne_private);
                        return -EFAULT;
                    }

                    inst->prepare_param.reg_num = dne_private->number_of_registers;
                }
                else
                    inst->prepare_param.reg_num = 0;

                debug("[%p] inst->prepare_param.reg_num (%d)\n", inst, inst->prepare_param.reg_num);

                if((inst->prepare_param.reg_info == NULL)&&(inst->prepare_param.reg_num))
                {
                    inst->prepare_param.reg_info = kzalloc(sizeof(REGISTER_MAP_T)*inst->prepare_param.reg_num, GFP_KERNEL);
                    if(inst->prepare_param.reg_info == NULL)
                    {
                        error("[%p] no memory\n", inst);
                        if(registers)
                            kfree_null((void **)&registers);
                        if(dne_private)
                            kfree_null((void **)&dne_private);
                        return -ENOMEM;
                    }

                    for(i=0; i< inst->prepare_param.reg_num; i++)
                    {
                        inst->prepare_param.reg_info[i].address = registers[i].address;
                        inst->prepare_param.reg_info[i].value = registers[i].value;
                        debug("[%p] inst->reg_info[%d] [0x%X:0x%X] \n", inst, i, inst->prepare_param.reg_info[i].address,
                                inst->prepare_param.reg_info[i].value);
                    }
                }
                else
                    debug("[%p] [_npu_set_private_data] dne_private->registers no_setting\n", inst);

                if(registers)
                    kfree_null((void **)&registers);

                if(dne_private->number_of_strides > 0)
                {
                    strides = kzalloc(sizeof(STRIDE_T)*dne_private->number_of_strides, GFP_KERNEL);

                    dne_private->strides = compat_ptr(dne_private->compat_strides);

                    ret = copy_from_user(strides, (void __user*) dne_private->strides,
                                        sizeof(STRIDE_T)*dne_private->number_of_strides);
                    if(ret)
                    {
                        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                        if(strides)
                            kfree_null((void **)&strides);
                        if(dne_private)
                            kfree_null((void **)&dne_private);
                        return -EFAULT;
                    }

                    inst->prepare_param.stride_num = dne_private->number_of_strides;
                }
                else
                    inst->prepare_param.stride_num = 0;

                debug("[%p] inst->prepare_param.stride_num (%d)\n", inst, inst->prepare_param.stride_num);

                if((inst->prepare_param.stride_info == NULL)&&(inst->prepare_param.stride_num))
                {
                    inst->prepare_param.stride_info = kzalloc(sizeof(unsigned int)*inst->prepare_param.stride_num, GFP_KERNEL);
                    if(inst->prepare_param.stride_info == NULL)
                    {
                        error("[%p] no memory\n", inst);
                        if(strides)
                            kfree_null((void **)&strides);
                        if(dne_private)
                            kfree_null((void **)&dne_private);
                        return -ENOMEM;
                    }

                    for(i=0; i< inst->prepare_param.stride_num; i++)
                    {
                        debug("[%p] stride_info[%d] = %d \n", inst, strides[i].type, strides[i].value);
                        inst->prepare_param.stride_info[strides[i].type] = strides[i].value;
                    }
                }
                else
                    debug("[%p] [_npu_set_private_data] dne_private->stride no_setting\n", inst);

                if(strides)
                    kfree_null((void **)&strides);

                if(dne_private->number_of_input_offsets <= 0)
                {
                    error("[%p] wrong setting of input_offsets\n", inst);
                    if(dne_private)
                        kfree_null((void **)&dne_private);
                    return -EFAULT;
                }

                inst->input_offset = kzalloc(sizeof(unsigned int)*dne_private->number_of_input_offsets, GFP_KERNEL);

                dne_private->input_offsets = compat_ptr(dne_private->compat_input_offsets);

                ret = copy_from_user(inst->input_offset, (void __user*) dne_private->input_offsets,
                sizeof(unsigned int)*dne_private->number_of_input_offsets);
                if(ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(dne_private)
                        kfree_null((void **)&dne_private);
                    return -EFAULT;
                }

                for(i=0; i< dne_private->number_of_input_offsets; i++)
                {
                    debug("[%p] input_offset[%d] = %d \n", inst, i, inst->input_offset[i]);
                }

                for(i=0; i< inst->input_num; i++)
                {
                    if(inst->prepare_param.stride_num)
                    {
                        stride_size = _ALIGN(inst->input_info[i].data_size,
                                        inst->prepare_param.stride_info[STRIDE_TYPE_INPUT]);
                        inst->input_size += stride_size;
                    }
                    else
                        inst->input_size += inst->input_info[i].data_size;
                }
                debug("[%p] inst->Total input_size = 0x%X\n", inst, inst->input_size);

                if(dne_private->number_of_output_offsets <= 0)
                {
                    error("[%p] wrong setting of output_offsets\n", inst);
                    if(dne_private)
                        kfree_null((void **)&dne_private);
                    return -EFAULT;
                }

                inst->output_offset = kzalloc(sizeof(unsigned int)*dne_private->number_of_output_offsets, GFP_KERNEL);

                dne_private->output_offsets = compat_ptr(dne_private->compat_output_offsets);

                ret = copy_from_user(inst->output_offset, (void __user*) dne_private->output_offsets,
                        sizeof(unsigned int)*dne_private->number_of_output_offsets);
                if(ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(dne_private)
                        kfree_null((void **)&dne_private);
                    return -EFAULT;
                }

                for(i=0; i< dne_private->number_of_output_offsets; i++)
                {
                    debug("[%p] output_offset[%d] = %d \n", inst, i, inst->output_offset[i]);
                }

                for(i=0; i< inst->output_num; i++)
                {
                    if(inst->prepare_param.stride_num)
                    {
                        stride_size = _ALIGN(inst->output_info[i].data_size,
                                        inst->prepare_param.stride_info[STRIDE_TYPE_OUTPUT]);
                        inst->output_size += stride_size;
                    }
                    else
                        inst->output_size += inst->output_info[i].data_size;
                }
                debug("[%p] inst->Total output_size = 0x%X\n", inst, inst->output_size);

                if(dne_private)
                    kfree_null((void **)&dne_private);

                break;
            }
            case NPU_PRIVATE_LNX:
            {
                if(control->chip < LX_CHIP_O24)
                {
                    error("[%p] %s param.type mismatch. (0x%X) \n", inst, __func__, control->chip);
                    return -EFAULT;
                }

                lnx_private = kzalloc(sizeof(LNX_PRIVATE_T), GFP_KERNEL);

                ret = copy_from_user(lnx_private, (void __user*) param.lnx_private, sizeof(LNX_PRIVATE_T));
                if (ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(lnx_private)
                        kfree_null((void **)&lnx_private);
                    return -EFAULT;
                }

                if(lnx_private->number_of_registers > 0)
                {
                    registers = kzalloc(sizeof(REGISTER_MAP_T)*lnx_private->number_of_registers, GFP_KERNEL);

                    lnx_private->registers = compat_ptr(lnx_private->compat_registers);

                    ret = copy_from_user(registers, (void __user*) lnx_private->registers,
                                sizeof(REGISTER_MAP_T)*lnx_private->number_of_registers);
                    if (ret)
                    {
                        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                        if(registers)
                            kfree_null((void **)&registers);
                        if(lnx_private)
                            kfree_null((void **)&lnx_private);
                        return -EFAULT;
                    }

                    inst->prepare_param.reg_num = lnx_private->number_of_registers;
                }
                else
                    inst->prepare_param.reg_num = 0;

                debug("[%p] inst->prepare_param.reg_num (%d)\n", inst, inst->prepare_param.reg_num);

                if((inst->prepare_param.reg_info == NULL)&&(inst->prepare_param.reg_num))
                {
                    inst->prepare_param.reg_info = kzalloc(sizeof(REGISTER_MAP_T)*inst->prepare_param.reg_num, GFP_KERNEL);
                    if(inst->prepare_param.reg_info == NULL)
                    {
                        error("[%p] no memory\n", inst);
                        if(registers)
                            kfree_null((void **)&registers);
                        if(lnx_private)
                            kfree_null((void **)&lnx_private);
                        return -ENOMEM;
                    }

                    for(i=0; i< inst->prepare_param.reg_num; i++)
                    {
                        inst->prepare_param.reg_info[i].address = registers[i].address;
                        inst->prepare_param.reg_info[i].value = registers[i].value;
                        debug("[%p] inst->reg_info[%d] [0x%X:0x%X] \n", inst, i, inst->prepare_param.reg_info[i].address,
                                inst->prepare_param.reg_info[i].value);
                    }
                }
                else
                    debug("[%p] [_npu_set_private_data] lnx_private->registers no_setting\n", inst);

                if(registers)
                    kfree_null((void **)&registers);

                debug("[%p] lnx_private->number_of_strides (%d)\n", inst, lnx_private->number_of_strides);
                if(lnx_private->number_of_strides > 0)
                {
                    strides = kzalloc(sizeof(STRIDE_T)*lnx_private->number_of_strides, GFP_KERNEL);

                    lnx_private->strides = compat_ptr(lnx_private->compat_strides);

                    ret = copy_from_user(strides, (void __user*) lnx_private->strides,
                                    sizeof(STRIDE_T)*lnx_private->number_of_strides);
                    if(ret)
                    {
                        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                        if(strides)
                            kfree_null((void **)&strides);
                        if(lnx_private)
                            kfree_null((void **)&lnx_private);
                        return -EFAULT;
                    }

                    inst->prepare_param.stride_num = lnx_private->number_of_strides;
                }
                else
                    inst->prepare_param.stride_num = 0;

                debug("[%p] inst->prepare_param.stride_num (%d)\n", inst, inst->prepare_param.stride_num);

                if((inst->prepare_param.stride_info == NULL)&&(inst->prepare_param.stride_num))
                {
                    inst->prepare_param.stride_info = kzalloc(sizeof(unsigned int)*inst->prepare_param.stride_num, GFP_KERNEL);
                    if(inst->prepare_param.stride_info == NULL)
                    {
                        error("[%p] no memory\n", inst);
                        if(strides)
                            kfree_null((void **)&strides);
                        if(lnx_private)
                            kfree_null((void **)&lnx_private);
                        return -ENOMEM;
                    }

                    for(i=0; i< inst->prepare_param.stride_num; i++)
                    {
                        debug("[%p] stride_info[%d] = %d \n", inst, strides[i].type, strides[i].value);
                                inst->prepare_param.stride_info[strides[i].type] = strides[i].value;
                    }
                }
                else
                    debug("[%p] [_npu_set_private_data] lnx_private->stride no_setting\n", inst);

                if(strides)
                    kfree_null((void **)&strides);

                inst->input_offset = kzalloc(sizeof(unsigned int)*lnx_private->number_of_input_offsets, GFP_KERNEL);

                lnx_private->input_offsets = compat_ptr(lnx_private->compat_input_offsets);

                ret = copy_from_user(inst->input_offset, (void __user*) lnx_private->input_offsets,
                            sizeof(unsigned int)*lnx_private->number_of_input_offsets);
                if(ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(lnx_private)
                        kfree_null((void **)&lnx_private);
                    return -EFAULT;
                }

                for(i=0; i< lnx_private->number_of_input_offsets; i++)
                {
                    debug("[%p] input_offset[%d] = %d \n", inst, i, inst->input_offset[i]);
                }

                for(i=0; i< inst->input_num; i++)
                {
                    if(inst->prepare_param.stride_num)
                    {
                        stride_size = _ALIGN(inst->input_info[i].data_size,
                                        inst->prepare_param.stride_info[STRIDE_TYPE_INPUT]);
                        inst->input_size += stride_size;
                    }
                    else
                        inst->input_size += inst->input_info[i].data_size;
                }
                    debug("[%p] inst->Total input_size = 0x%X\n", inst, inst->input_size);

                inst->output_offset = kzalloc(sizeof(unsigned int)*lnx_private->number_of_output_offsets, GFP_KERNEL);

                lnx_private->output_offsets = compat_ptr(lnx_private->compat_output_offsets);

                ret = copy_from_user(inst->output_offset, (void __user*) lnx_private->output_offsets,
                            sizeof(unsigned int)*lnx_private->number_of_output_offsets);
                if(ret)
                {
                    error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
                    if(lnx_private)
                        kfree_null((void **)&lnx_private);
                    return -EFAULT;
                }

                for(i=0; i< lnx_private->number_of_output_offsets; i++)
                {
                    debug("[%p] output_offset[%d] = %d \n", inst, i, inst->output_offset[i]);
                }

                for(i=0; i< inst->output_num; i++)
                {
                    if(inst->prepare_param.stride_num)
                    {
                        stride_size = _ALIGN(inst->output_info[i].data_size,
                                        inst->prepare_param.stride_info[STRIDE_TYPE_OUTPUT]);
                        inst->output_size += stride_size;
                    }
                    else
                        inst->output_size += inst->output_info[i].data_size;
                }
                debug("[%p] inst->Total output_size = 0x%X\n", inst, inst->output_size);

                if(lnx_private)
                    kfree_null((void **)&lnx_private);

                break;
            }
            default:
                error("[%p] not support npu_type \n", inst);
                ret = -EFAULT;
                break;
        }
    }
    else
    {
        error("[%p] not support npu_type[NPU_PRIVATE_NONE] \n", inst);
        return -EFAULT;
    }

    return ret;
}

static int _npu_request_job(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;
    JOB_T param;
    struct npu_buffer_info *buffer_info = NULL;

    ret = copy_from_user((void*)&param, (const void __user*)arg, sizeof(JOB_T));
    if(ret)
    {
        ret = -EFAULT;
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return ret;
    }

	inst->last_req_id = param.job_id;

	buffer_info = npu_que_find_pop_by_job_id(_work_task_que, param.job_id);
	if(buffer_info == NULL)
	{
        ret = -EFAULT;
        error("[%p] npu_buffer_info NOT find. ret:%d \n", inst, ret);
        return ret;
	}
	debug("npu_que_get_node_cnt(_work_task_que) = %d\n", npu_que_get_node_cnt(_work_task_que));


//////////////////////////////////////////////////////
// will arrange reordering of _work_req_que
//////////////////////////////////////////////////////
#ifdef PRIORITY_SCHEDULER
    if(npu_que_asc_sort_push(_work_req_que, buffer_info) < 0)
    {
        error("Fail to asc_sort_push (_work_req_que) \n");
    }
#else
    if(npu_que_push(_work_req_que, buffer_info) < 0)
    {
        error("Fail to npu_que_push (_work_req_que) \n");
    }
#endif
	debug("npu_que_get_node_cnt(_work_req_que) = %d\n", npu_que_get_node_cnt(_work_req_que));

    wake_up_interruptible(&_work_wait_req);

#ifdef DBG_MTD
    inst->sche_dbg_mtd.start_time = ktime_get_real_ns() / NSEC_PER_MSEC;
#endif

    debug("[%p] job request done\n", inst);

    return ret;

}

static int _npu_set_output_data(struct npu_inst *inst, struct npu_buffer_info *buffer_info)
{
    int ret, i = 0;
    size_t size = 0;
#if 1//def ENABLE_DATA_DUMP
    unsigned char *pBuf;
#endif
	void *tmp_ptr = NULL;

	if(buffer_info->inter_output_buf.cache_data.ptr)
	    tmp_ptr = buffer_info->inter_output_buf.cache_data.ptr;
	else
	    tmp_ptr = buffer_info->inter_output_buf.va_addr;

	if(tmp_ptr)
	{
	    size = inst->output_size;
	    debug("[%p] %s size(%ld)\n", inst, __func__, size);

#if 0 //DUMP_TEST
	    debug("[KDM] dump_file(output_tensor_dump.bin)\n");
	    dump_file("/mnt/lg/flash/data/_liblgnpu/output_tensor_dump.bin",
	            (unsigned char *)buffer_info->inter_output_buf.va_addr, inst->output_size);

//	    cache_invalidate(inst->prepare_param.feature.va_addr, inst->prepare_param.feature.size);
//	    debug("[KDM] dump_file(feature_mem_dump.bin)\n");
//	    dump_file("/mnt/lg/flash/data/_liblgnpu/feature_mem_dump.bin",
//	            (unsigned char *)inst->prepare_param.feature.va_addr, inst->prepare_param.feature.size);
#endif

	    for(i=0; i < buffer_info->number_of_output_buf; i++)
	    {
            if(inst->output_offset[i]+(buffer_info->output_buf[i].size) > buffer_info->inter_output_buf.size)
            {
                error("[%p] output_buf[%d] offset(0x%x)+tensor_size(0x%x) overflow[0x%x : 0x%x] error", inst, i,
                    inst->output_offset[i], buffer_info->output_buf[i].size,
                    inst->output_offset[i]+(buffer_info->output_buf[i].size), buffer_info->output_buf[i].size);
	            return -EFAULT;
            }

	        ret = copy_to_user((void __user*)buffer_info->output_buf[i].va_addr, tmp_ptr+inst->output_offset[i], buffer_info->output_buf[i].size);
	        if (ret)
	        {
	            error ("[%p] copy_to_user failed(output_buf[%d]). ret:%d \n", inst, i, ret);
	            return -EFAULT;
	        }

#if 1//def ENABLE_DATA_DUMP
	        pBuf = (unsigned char *)tmp_ptr+inst->output_offset[i];
	        info("[%p] [Output_Data_Dump] 0x%p + %x = 0x%p\n", inst, tmp_ptr, inst->output_offset[i], (void *)pBuf);
	        info("[%p] [Output_Data_%d] 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X \n",
	            inst, i, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4]);
#endif
	    }

        debug("[%p] inter_output_buf list/cache is free [0x%p] \n", inst, (void *) &(buffer_info->inter_output_buf));

#ifdef USE_CACHE_DATA
        if(tmp_ptr)
        {
            _uncache_buffer(&buffer_info->inter_output_buf.cache_data);
        }
#else
        _npu_free_inter_output(buffer_info);
#endif

        if(buffer_info->output_buf != NULL)
            kfree_null((void **)&buffer_info->output_buf);

        debug("[%p] write done %zu\n", inst, size);
	}
	else {
	    ret = -EFAULT;
	    error("[%p] output_buf pointer NOT find. ret:%d \n", inst, ret);
	    if(buffer_info->output_buf != NULL)
            kfree_null((void **)&buffer_info->output_buf);
	    return ret;
	}

    return 0;
}

static void _npu_free_buffer_data(struct npu_inst *inst, struct npu_buffer_info *buffer_info)
{
    int i = 0;

    for(i=0; i<buffer_info->number_of_input_buf; i++)
    {
        if((buffer_info->inst_id == inst)&&
            (buffer_info->input_buf[i].memory_type != MEMORY_TYPE_PHYSICAL))
        {
            if((buffer_info->input_buf[i].va_addr)&&(buffer_info->input_buf[i].magic_num == USE_MAGIC))
            {
                _free_buffer(&buffer_info->input_buf[i]);
            }
            if(buffer_info->input_buf[i].magic_num != IDL_MAGIC)
                error("[%p] input_buf[%d] free fail(0x%X)\n", inst, i, buffer_info->input_buf[i].magic_num);
        }
#ifdef USE_CACHE_DATA
        if(buffer_info->input_buf[i].cache_data.ptr != NULL)
            _uncache_buffer(&buffer_info->input_buf[i].cache_data);
#endif
    }

    if((buffer_info->inst_id == inst)&&(buffer_info->inter_output_buf.phys_addr)
        &&(buffer_info->inter_output_buf.magic_num == USE_MAGIC))
    {
        _free_buffer(&buffer_info->inter_output_buf);
    }
    if(buffer_info->inter_output_buf.magic_num != IDL_MAGIC)
        error("[%p] inter_output_buf free fail(0x%X)\n", inst, buffer_info->inter_output_buf.magic_num);

    if(buffer_info->output_buf != NULL)
        kfree_null((void **)&buffer_info->output_buf);

    if(buffer_info->input_buf != NULL)
        kfree_null((void **)&buffer_info->input_buf);

}

static int _npu_free_buffer_node(struct npu_inst *inst, void *que_ctx)
{
	struct npu_que_ctx* ctx = NULL;
	struct npu_que_node* tmp = NULL;
	struct npu_que_node* node = NULL;
    struct npu_buffer_info *buffer_info = NULL;
	int i = 0;

	ctx = (struct npu_que_ctx *)que_ctx;
	if(ctx == NULL)
    {
		error("ctx invalid argument\n");
		return 0;
	}

	mutex_lock(&ctx->lock);
	list_for_each_entry_safe(node, tmp, &ctx->head, list) {
        buffer_info = (struct npu_buffer_info *)node->data;
        if(buffer_info == NULL)
        {
            error("buffer invalid argument\n");
            mutex_unlock(&ctx->lock);
            return 0;
        }
        for(i=0; i<buffer_info->number_of_input_buf; i++)
        {
	        if((buffer_info->inst_id == inst)&&
				(buffer_info->input_buf[i].memory_type != MEMORY_TYPE_PHYSICAL))
	        {
                if((buffer_info->input_buf[i].va_addr)&&(buffer_info->input_buf[i].magic_num == USE_MAGIC))
                    {
                        _free_buffer(&buffer_info->input_buf[i]);
                    }
                if(buffer_info->input_buf[i].magic_num != IDL_MAGIC)
                    error("[%p] input_buf[%d] free fail(0x%X)\n", inst, i, buffer_info->input_buf[i].magic_num);
	        }
        }
        if((buffer_info->inst_id == inst)&&(buffer_info->inter_output_buf.phys_addr)
            &&(buffer_info->inter_output_buf.magic_num == USE_MAGIC))
        {
            _free_buffer(&buffer_info->inter_output_buf);
        }
        if(buffer_info->inter_output_buf.magic_num != IDL_MAGIC)
            error("[%p] inter_output_buf free fail(0x%X)\n", inst, buffer_info->inter_output_buf.magic_num);

	}
	mutex_unlock(&ctx->lock);

    return 0;
}

static int _npu_cancel_all_jobs(struct npu_inst *inst)
{
    int cnt = 0;

    if(_npu_free_buffer_node(inst, _work_req_que) < 0)
    {
        error("[%p] _work_req_que buffer_node free fail\n", inst);
    }
    cnt = npu_que_find_clear_by_id(_work_req_que, inst);
    debug("[%p] _work_req_que clear done %d\n", inst, cnt);

    if(_npu_free_buffer_node(inst, _work_rsp_que) < 0)
    {
        error("[%p] _work_rsp_que buffer_noe free fail\n", inst);
    }
    cnt = npu_que_find_clear_by_id(_work_rsp_que, inst);
    debug("[%p] _work_rsp_que clear done %d\n", inst, cnt);

    return 0;
}

#ifdef USE_IOMMU
static dma_addr_t _npu_map_dma_address(struct npu_inst *inst, phys_addr_t addr, int size)
{
    dma_addr_t dma_addr = 0;
    dma_addr = dma_map_resource(&npu_hw_controls->pdev->dev, addr, size, DMA_BIDIRECTIONAL,0);
    info("[%p] %llx (%x) -> %llx\n", inst, addr, size, dma_addr);
    if (dma_mapping_error(&npu_hw_controls->pdev->dev, dma_addr)) {
        dma_addr = 0x0;
        error("dma_map_resource() failed.\n");
    }
    return dma_addr;
}
#endif

static int _npu_get_job_result(struct npu_inst *inst, unsigned long arg)
{
    int ret, retry_count = 0;
    long wait_ret = 0;
    JOB_T param;
    struct npu_buffer_info *buffer_info = NULL;

#ifdef DBG_MTD
    unsigned int run_avg_ms = 0;
#endif

    ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(JOB_T));
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    debug("[%p][%s] \n", inst, __func__);

    wait_ret = wait_event_interruptible_timeout(inst->work_wait_rsp,
            _npu_have_work_rsp(inst), msecs_to_jiffies(RUN_WAIT_TIMEOUT));

    while (wait_ret < 0 && retry_count < MAX_RETRIES)
    {
        noti("[%p][%s] wait_event_interruptible_timeout retry[%d]\n", inst, __func__, retry_count);
        msleep(1);  // secure SIGNAL processing time
        wait_ret = wait_event_interruptible_timeout(inst->work_wait_rsp,
                    _npu_have_work_rsp(inst), msecs_to_jiffies(RUN_WAIT_TIMEOUT));

        retry_count++;
    }

    if(wait_ret <= 0)
    {
        error("[%p] wait_run timeout!! [%ld][%s]\n", inst, wait_ret, _npu_have_work_rsp(inst)? "true" : "false");

        mutex_lock(&inst->sync_lock);
        buffer_info = npu_que_find_pop_by_job_id(_work_req_que, inst->last_req_id);
        if(buffer_info)
        {
            noti("[%p] job_id[%d] discard from _work_req_que.\n", inst, inst->last_req_id);
            _npu_free_buffer_data(inst, buffer_info);
        }
        buffer_info = npu_que_find_pop_by_job_id(_work_task_que, inst->last_req_id);
        if(buffer_info)
        {
            noti("[%p] job_id[%d] discard from _work_task_que.\n", inst, inst->last_req_id);
            _npu_free_buffer_data(inst, buffer_info);
        }
        buffer_info = npu_que_find_pop_by_id(_work_rsp_que, inst);
        if(buffer_info)
        {
            noti("[%p] discard from _work_rsp_que.\n", inst);
            _npu_free_buffer_data(inst, buffer_info);
        }
        else
        {
            noti("[%p] npu_que_find_pop_by_id() = NULL.\n", inst);
        }
        mutex_unlock(&inst->sync_lock);

        return -ETIMEDOUT;
    }

    debug("[%p][%s] WAKE wait_rsp\n", inst, __func__);

	buffer_info = npu_que_find_pop_by_id(_work_rsp_que, inst);
	if(buffer_info == NULL)
	{
		error("[%p] npu_que_find_pop_by_id failed.\n", inst);
        buffer_info = npu_que_find_pop_by_job_id(_work_req_que, inst->last_req_id);
        if(buffer_info)
        {
            noti("[%p] job_id[%d] discard from _work_req_que.\n", inst, inst->last_req_id);
            _npu_free_buffer_data(inst, buffer_info);
        }
        buffer_info = npu_que_find_pop_by_job_id(_work_task_que, inst->last_req_id);
        if(buffer_info)
        {
            noti("[%p] job_id[%d] discard from _work_task_que.\n", inst, inst->last_req_id);
            _npu_free_buffer_data(inst, buffer_info);
        }
		return -EFAULT;
	}

    if(!buffer_info->npu_done)
    {
        error("[%p] run fail!! npu_done[%d]\n", inst, buffer_info->npu_done);
        _npu_free_buffer_data(inst, buffer_info);
        if(buffer_info != NULL)
            kfree_null((void **)&buffer_info);

        return -EFAULT;
    }

	param.job_id = buffer_info->job_id;

	if(inst->run_param.output.memory_type != MEMORY_TYPE_PHYSICAL)
	{
		ret = _npu_set_output_data(inst, buffer_info);
	    if(ret)
	    {
	        error("[%p] _npu_set_output_data failed. ret:%d\n", inst, ret);
	        if(buffer_info->inter_output_buf.magic_num == USE_MAGIC)
            {
                _free_buffer(&buffer_info->inter_output_buf);
            }
	        if(buffer_info->inter_output_buf.magic_num != IDL_MAGIC)
                error("[%p] inter_output_buf free fail(0x%X)\n", inst, buffer_info->inter_output_buf.magic_num);
	        if(buffer_info->output_buf != NULL)
                kfree_null((void **)&buffer_info->output_buf);
	        if(buffer_info != NULL)
                kfree_null((void **)&buffer_info);
	        return -EFAULT;
	    }
	}
	else
	{
		debug("[%p][%s] _npu_set_output_data skip!\n", inst, __func__);
		if(buffer_info->output_buf != NULL)
			kfree_null((void **)&buffer_info->output_buf);
	}

#if 0
    debug("[%p] %s input buf mem is free \n", inst, __func__);
    for(i=0; i<buffer_info->number_of_input_buf; i++)
    {
        if((buffer_info->inst_id == inst)&&
            (buffer_info->input_buf[i].memory_type != MEMORY_TYPE_PHYSICAL))
        {
            if((buffer_info->input_buf[i].va_addr)&&(buffer_info->input_buf[i].magic_num == USE_MAGIC))
            {
                _free_buffer(&buffer_info->input_buf[i]);
            }
            if(buffer_info->input_buf[i].magic_num != IDL_MAGIC)
                error("[%p] input_buf[%d] free fail(0x%X)\n", inst, i, buffer_info->input_buf[i].magic_num);

        }
    }
#endif

    if(buffer_info->input_buf != NULL)
    {
        kfree_null((void **)&buffer_info->input_buf);
    }

	if(buffer_info != NULL)
    {
		kfree_null((void **)&buffer_info);
    }

#ifdef DBG_MTD
    param.latency.npu = inst->dbg_mtd.npu_latency;
    param.latency.kmd = inst->dbg_mtd.acc_ms;
    debug("[%p] Profile::latency.npu(%d) latency.kmd(%d)\n",
            inst, param.latency.npu, param.latency.kmd);


    inst->sche_dbg_mtd.end_time = ktime_get_real_ns() / NSEC_PER_MSEC;
    inst->sche_dbg_mtd.acc_ms = inst->sche_dbg_mtd.end_time - inst->sche_dbg_mtd.start_time;
    if(inst->sche_dbg_mtd.sum_ms + inst->sche_dbg_mtd.acc_ms >= ULLONG_MAX)
    {
        noti("sche_dbg_mtd.sum_ms's value is out of range. It will reset.\n");
        inst->sche_dbg_mtd.sum_ms = 0;
        inst->sche_dbg_mtd.num_cnt = 0;
    }
    inst->sche_dbg_mtd.sum_ms += inst->sche_dbg_mtd.acc_ms;
    inst->sche_dbg_mtd.num_cnt++;

    if(inst->period > 0)
    {
        if(inst->period < inst->sche_dbg_mtd.acc_ms)
            inst->sche_dbg_mtd.overflow_cnt++;
    }
    run_avg_ms = (unsigned int)(inst->sche_dbg_mtd.sum_ms / inst->sche_dbg_mtd.num_cnt);

    if(!(inst->sche_dbg_mtd.num_cnt % 5000))
    {
        debug("[%p] RUN time: %llums, avg time : %dms, executed count: %d\n", inst,
            inst->sche_dbg_mtd.acc_ms, run_avg_ms, inst->sche_dbg_mtd.num_cnt);
        if(inst->period > 0)
        {
            info("[%p] DRV avg time: %dms, NPU avg time: %llums, executed count: %d, oveflow(%d)\n", inst,
                run_avg_ms, inst->dbg_mtd.sum_ms / inst->dbg_mtd.num_cnt, inst->sche_dbg_mtd.num_cnt,
                inst->sche_dbg_mtd.overflow_cnt);
        }
        else
        {
            info("[%p] DRV avg time: %dms, THR avg time : %llums, NPU avg time: %llums, executed count: %d\n", inst,
                run_avg_ms, inst->cpy_dbg_mtd.sum_ms / inst->cpy_dbg_mtd.num_cnt, inst->dbg_mtd.sum_ms / inst->dbg_mtd.num_cnt, inst->sche_dbg_mtd.num_cnt);
        }
    }
#endif

    ret = copy_to_user((void __user*)arg, &param, sizeof(JOB_T));
    if(ret)
    {
        error("[%p] copy_to_user failed. ret:%d\n", inst, ret);
        return -EFAULT;
    }

    return 0;
}

static int _npu_set_period(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;

    inst->period = arg;
    debug("[%p][%s] period = %d\n", inst, __func__, inst->period);
    if(inst->period)
    {
        inst->period = 1000 / inst->period;
    }

    noti("[%p][%s] threshold = %d\n", inst, __func__, inst->period);

    return ret;
}

static int _npu_set_job_input_tensors(struct npu_inst *inst, unsigned long arg)
{
	int ret, i=0, j=0, type_size = 0;
	JOB_TENSORS_T param;
	TENSOR_T* tensors;
	struct npu_buffer_info *buffer_info = NULL;
#ifdef ENABLE_FILE_LOAD
	void *write_pointer = NULL;
#endif
#ifdef ENABLE_DATA_DUMP
	unsigned char *pBuf;
#endif

	ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(JOB_TENSORS_T));
	if(ret)
	{
		error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
		return -EFAULT;
	}

	tensors = kzalloc(sizeof(TENSOR_T)*param.number_of_tensor, GFP_KERNEL);

    ret = copy_from_user(tensors, (void __user*) param.tensor, sizeof(TENSOR_T)*param.number_of_tensor);
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        if(tensors)
            kfree_null((void **)&tensors);

		return -EFAULT;
	}

	buffer_info = kzalloc(sizeof(struct npu_buffer_info), GFP_KERNEL);
	if (buffer_info == NULL)
	{
		warn("[%p] no memory\n", inst);
		ret = -ENOMEM;
		goto GOTO_ERROR;
	}

	buffer_info->inter_output_buf.magic_num = IDL_MAGIC;
	buffer_info->inter_output_buf.phys_addr = 0;
	buffer_info->inter_output_buf.cache_data.ptr = NULL;
	buffer_info->inter_output_buf.cache_data.size = 0;
	buffer_info->npu_done = false;
	buffer_info->inst_id = inst;
	buffer_info->job_id = param.job_id;
	buffer_info->number_of_input_buf = param.number_of_tensor;
	buffer_info->input_buf = kzalloc(sizeof(struct npu_buffer)*buffer_info->number_of_input_buf, GFP_KERNEL);
	if(buffer_info->input_buf == NULL)
	{
		warn("[%p] no memory\n", inst);
		ret = -ENOMEM;
		goto GOTO_ERROR;
	}

	for(i=0; i< buffer_info->number_of_input_buf; i++)
	{
		debug("[%p][%s] tensor[%d] : type(%d) size(%d)\n", inst, __func__, i,
				tensors[i].memory_type, tensors[i].size);

		type_size = _npu_get_tensor_type_size(inst->input_info[i].type);

		if(type_size == 0)
		{
			error("[%p] input_tensor[%d] has invalid type_size (0)\n",inst, i);
			ret = -EINVAL;
			goto GOTO_ERROR;
		}

		if(tensors[i].size != inst->input_info[i].data_size/type_size)
		{
			error("[%p] input_tensor[%d].size mismatch(%d|%d)\n",inst, i,
					tensors[i].size, inst->input_info[i].data_size/type_size);
			ret = -EFAULT;
			goto GOTO_ERROR;
		}


		if(tensors[i].memory_type == MEMORY_TYPE_PHYSICAL)
		{
			buffer_info->input_buf[i].memory_type = MEMORY_TYPE_PHYSICAL;
#ifdef USE_IOMMU
            buffer_info->input_buf[i].phys_addr = _npu_map_dma_address(inst, tensors[i].physical_address, tensors[i].size);
            if (buffer_info->input_buf[i].phys_addr == 0) {
                ret = -EFAULT;
                goto GOTO_ERROR;
            }
#else
            buffer_info->input_buf[i].phys_addr = tensors[i].physical_address;
#endif
			buffer_info->input_buf[i].va_addr = NULL;
#ifdef USE_CACHE_DATA
			buffer_info->input_buf[i].cache_data.ptr = NULL;
			buffer_info->input_buf[i].cache_data.size = 0;
#endif
			buffer_info->input_buf[i].size = tensors[i].size;
			info("[%p][%s] input_buf[%d] : phys(0x%llX) size(%d)\n", inst, __func__, i,
					buffer_info->input_buf[i].phys_addr, buffer_info->input_buf[i].size);
		}
		else
		{
			buffer_info->input_buf[i].memory_type = MEMORY_TYPE_DEVICE;

			tensors[i].data = compat_ptr(tensors[i].compat_data);
			buffer_info->input_buf[i].size = tensors[i].size;

#ifdef USE_CACHE_DATA
			if (i==0) {
				int total_size=0;
				for (j=0 ; j<buffer_info->number_of_input_buf ; j++) {
					debug("%s:%d: input tensor %d size : %d\n", __func__, __LINE__, j, inst->input_info[j].data_size);
					total_size += inst->input_info[j].data_size;
				}

				if(_cache_buffer(&buffer_info->input_buf[0].cache_data, total_size, "input"))
				{
					error("[%p] input cache allocation fail - %d\n", inst, total_size);
					ret = -ENOMEM;
					goto GOTO_ERROR;
				}
				buffer_info->input_buf[0].cache_data.size = inst->input_info[0].data_size;
			} else {
				buffer_info->input_buf[i].cache_data.ptr = buffer_info->input_buf[i-1].cache_data.ptr + inst->input_info[i-1].data_size;
				buffer_info->input_buf[i].cache_data.size = inst->input_info[i].data_size;
			}

			mutex_lock(&buffer_info->input_buf[i].mutex_lock);
			if(copy_from_user(buffer_info->input_buf[i].cache_data.ptr, tensors[i].data,
						type_size*tensors[i].size))
			{
				error("[%p] copy_from_user fail\n", inst);
				ret = -EFAULT;
				mutex_unlock(&buffer_info->input_buf[i].mutex_lock);
				goto GOTO_ERROR;
			}

#ifdef ENABLE_FILE_LOAD
			read_file("/mnt/lg/flash/data/_liblgnpu/DNE_IMG_480x270_RGBA.bin", write_pointer,
					type_size*tensors[i].size);
			pBuf = (unsigned char *)write_pointer;
			debug("[%p] [Input_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
					inst, i, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
					pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
#ifdef ENABLE_DATA_DUMP
			pBuf = (unsigned char *)buffer_info->input_buf[i].cache_data.ptr;
			debug("[%p] [Input_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
					inst, i, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
					pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
			mutex_unlock(&buffer_info->input_buf[i].mutex_lock);
#else
			if(_alloc_buffer(&buffer_info->input_buf[i], tensors[i].size, EXTRA_POOL_IDX, "input"))
			{
				error("[%p] input buffer allocation fail - %d\n", inst, tensors[i].size);
				ret = -ENOMEM;
				goto GOTO_ERROR;
			}

			debug("[%p] input buffer mem is allocated \n", inst);

			mutex_lock(&buffer_info->input_buf[i].mutex_lock);
			if(buffer_info->input_buf[i].magic_num != USE_MAGIC)
			{
				error("[%p] input_buf magic number error(0x%X)", inst, buffer_info->input_buf[i].magic_num);
				ret = -EFAULT;
				mutex_unlock(&buffer_info->input_buf[i].mutex_lock);
				goto GOTO_ERROR;
			}
			if(copy_from_user(buffer_info->input_buf[i].va_addr, tensors[i].data,
						type_size*tensors[i].size))
			{
				error("[%p] copy_from_user fail\n", inst);
				ret = -EFAULT;
				mutex_unlock(&buffer_info->input_buf[i].mutex_lock);
				goto GOTO_ERROR;
			}

#if 0 //DUMP_TEST
			debug("[KDM] dump_file(input_tensor_dump.bin)\n");
			dump_file("/mnt/lg/flash/data/_liblgnpu/input_tensor_dump.bin",
					(unsigned char *)buffer_info->input_buf[0].va_addr, buffer_info->input_buf[0].size);
#endif

#ifdef ENABLE_FILE_LOAD
			read_file("/mnt/lg/flash/data/_liblgnpu/DNE_IMG_480x270_RGBA.bin", write_pointer,
					sizeof(char)*tensors[i].size);
			pBuf = (unsigned char *)write_pointer;
			debug("[%p] [Input_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
					inst, i, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
					pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
#ifdef ENABLE_DATA_DUMP
			pBuf = (unsigned char *)buffer_info->input_buf[i].va_addr;
			debug("[%p] [Input_Data_%d] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X \n",
					inst, i, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4],
					pBuf[5], pBuf[6], pBuf[7], pBuf[8], pBuf[9]);
#endif
			cache_flush(buffer_info->input_buf[i].va_addr, type_size*buffer_info->input_buf[i].size);
			mutex_unlock(&buffer_info->input_buf[i].mutex_lock);
#endif
		}
	}

	if(npu_que_find_by_job_id(_work_task_que, buffer_info->job_id) == NULL)
	{
		if(npu_que_push(_work_task_que, buffer_info) < 0)
		{
			error("Fail to push _work_task_que \n");
		}
	}
	else
		warn("[%p] already pushed to _work_task_que[job_id:%d]\n", inst, buffer_info->job_id);

	debug("npu_que_get_node_cnt(_work_task_que) =%d\n", npu_que_get_node_cnt(_work_task_que));

	debug("[%p][%s] read done\n", inst, __func__);

GOTO_ERROR:
	if (ret < 0 && (buffer_info != NULL))
	{
		error("[%p] %s err occured. \n", inst, __func__);
		for(j=0; j <= i; j++)
		{
#ifdef USE_CACHE_DATA
			if (j==0) {
				if((buffer_info->input_buf[j].memory_type != MEMORY_TYPE_PHYSICAL)
						&&(buffer_info->input_buf[j].cache_data.ptr))
				{
					_uncache_buffer(&buffer_info->input_buf[j].cache_data);
				}
			}
#else

#ifdef USE_IOMMU
            if(buffer_info->input_buf[j].memory_type == MEMORY_TYPE_PHYSICAL) {
                if (buffer_info->input_buf[j].phys_addr > 0) {
                    dma_unmap_resource(&npu_hw_controls->pdev->dev, buffer_info->input_buf[j].phys_addr,
                        buffer_info->input_buf[j].size, DMA_BIDIRECTIONAL,0);
                }
            }
#endif
			if((buffer_info->input_buf[j].memory_type != MEMORY_TYPE_PHYSICAL)
					&&(buffer_info->input_buf[j].va_addr)&&(buffer_info->input_buf[j].magic_num == USE_MAGIC))
			{
				_free_buffer(&buffer_info->input_buf[j]);
                if(buffer_info->input_buf[j].magic_num != IDL_MAGIC)
                {
                    error("[%p] input_buf[%d] free fail(0x%X)\n", inst, j, buffer_info->input_buf[i].magic_num);
                }
			}
#endif
        }
        if(buffer_info->input_buf != NULL)
        {
            kfree_null((void **)&buffer_info->input_buf);
        }
        kfree_null((void **)&buffer_info);
    }

    kfree_null((void **)&tensors);

	return ret;
}


static int _npu_set_job_output_tensors(struct npu_inst *inst, unsigned long arg)
{
    int ret, i, type_size = 0;
    JOB_TENSORS_T param;
    TENSOR_T* tensors;
    struct npu_buffer_info *buffer_info = NULL;

    ret = copy_from_user ((void*)&param, (const void __user*)arg, sizeof(JOB_TENSORS_T));
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    tensors = kzalloc(sizeof(TENSOR_T)*param.number_of_tensor, GFP_KERNEL);

    ret = copy_from_user(tensors, (void __user*) param.tensor, sizeof(TENSOR_T)*param.number_of_tensor);
    if(ret)
    {
        error("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        if(tensors)
        kfree_null((void **)&tensors);
        return -EFAULT;
    }

    buffer_info = npu_que_find_by_job_id(_work_task_que, param.job_id);
    if(buffer_info == NULL)
    {
        ret = -EFAULT;
        error("[%p] npu_buffer_info NOT find. ret:%d \n", inst, ret);
        if(tensors)
        kfree_null((void **)&tensors);
        return ret;
    }

    buffer_info->number_of_output_buf = param.number_of_tensor;
    buffer_info->output_buf = kzalloc(sizeof(struct npu_buffer)*buffer_info->number_of_output_buf, GFP_KERNEL);
    if(buffer_info->output_buf == NULL)
    {
        warn("[%p] no memory\n", inst);
        ret = -ENOMEM;
        goto GOTO_ERROR;
    }

    for(i=0; i< buffer_info->number_of_output_buf; i++)
    {
        debug("[%p][%s] tensor[%d] : type(%d) size(%d)\n", inst, __func__, i,
        tensors[i].memory_type, tensors[i].size);

        type_size = _npu_get_tensor_type_size(inst->output_info[i].type);

        if(type_size == 0)
        {
            error("[%p] output_tensor[%d] has invalid type_size (0)\n",inst, i);
            ret = -EINVAL;
            goto GOTO_ERROR;
        }

        if(tensors[i].size != inst->output_info[i].data_size/type_size)
        {
            error("[%p] output_tensor[%d].size mismatch(%d|%d)\n", inst, i,
                    tensors[i].size, inst->output_info[i].data_size/type_size);
            ret = -EFAULT;
            goto GOTO_ERROR;
        }

        if(tensors[i].memory_type == MEMORY_TYPE_PHYSICAL)
        {
            buffer_info->output_buf[i].magic_num = USE_MAGIC;
            buffer_info->output_buf[i].memory_type = MEMORY_TYPE_PHYSICAL;
#ifdef USE_IOMMU
            if (i==0) {
                buffer_info->output_buf[i].phys_addr = _npu_map_dma_address(inst, tensors[i].physical_address, inst->output_size);
                if (buffer_info->output_buf[i].phys_addr == 0) {
                    ret = -EFAULT;
                    goto GOTO_ERROR;
                }
            }
#else
            buffer_info->output_buf[i].phys_addr = tensors[i].physical_address;
#endif
            buffer_info->output_buf[i].va_addr = NULL;
#ifdef USE_CACHE_DATA
            buffer_info->output_buf[i].cache_data.ptr = NULL;
#endif
            buffer_info->output_buf[i].size = tensors[i].size;
            info("[%p][%s] output_buf[%d] : phys(0x%llX) size(%d)\n", inst, __func__, i,
                buffer_info->output_buf[i].phys_addr, buffer_info->output_buf[i].size);
        }
        else
        {
#ifdef USE_CACHE_DATA
            tensors[i].data = compat_ptr(tensors[i].compat_data);

            buffer_info->output_buf[i].magic_num = USE_MAGIC;
            buffer_info->output_buf[i].memory_type = MEMORY_TYPE_MALLOC;
            buffer_info->output_buf[i].phys_addr = 0;
            buffer_info->output_buf[i].va_addr = tensors[i].data;
            buffer_info->output_buf[i].size = type_size*tensors[i].size;

            if(i == 0)
            {
                if(_cache_buffer(&buffer_info->inter_output_buf.cache_data, inst->output_size, "output"))
                {
                    error("[%p] inter output cache allocation fail - %d\n", inst, inst->output_size);
                    ret = -ENOMEM;
                    goto GOTO_ERROR;
                }
                debug("[%p] inter output buf cache is allocated \n", inst);
            }
#else
            tensors[i].data = compat_ptr(tensors[i].compat_data);

            buffer_info->output_buf[i].magic_num = USE_MAGIC;
            buffer_info->output_buf[i].memory_type = MEMORY_TYPE_MALLOC;
            buffer_info->output_buf[i].phys_addr = 0;
            buffer_info->output_buf[i].va_addr = tensors[i].data;
            buffer_info->output_buf[i].size = type_size*tensors[i].size;

            if(i == 0)
            {
                if(_alloc_buffer(&buffer_info->inter_output_buf, inst->output_size, EXTRA_POOL_IDX, "output"))
                {
                    error("[%p] inter output buffer allocation fail - %d\n", inst, inst->output_size);
                    ret = -ENOMEM;
                    goto GOTO_ERROR;
                }
                buffer_info->inter_output_buf.memory_type = MEMORY_TYPE_DEVICE;

                debug("[%p] inter output buf mem is allocated \n", inst);
            }
#endif
        }
    }

    debug("[%p][%s] done\n", inst, __func__);

    GOTO_ERROR:
    if(ret < 0 && (buffer_info != NULL))
    {
        error("[%p] %s err occured. \n", inst, __func__);

#ifndef USE_CACHE_DATA
        if((buffer_info->inter_output_buf.phys_addr)&&(buffer_info->inter_output_buf.magic_num == USE_MAGIC))
        {
            _free_buffer(&buffer_info->inter_output_buf);
        }
        if(buffer_info->inter_output_buf.magic_num != IDL_MAGIC)
        {
            error("[%p] inter_output_buf free fail(0x%X)\n", inst, buffer_info->inter_output_buf.magic_num);
        }
#endif
#ifdef USE_IOMMU
        if(buffer_info->output_buf[0].memory_type == MEMORY_TYPE_PHYSICAL) {
            if (buffer_info->output_buf[0].phys_addr > 0) {
                dma_unmap_resource(&npu_hw_controls->pdev->dev, buffer_info->output_buf[0].phys_addr,
                    inst->output_size, DMA_BIDIRECTIONAL,0);
            }
        }
#endif

        if(buffer_info->output_buf != NULL)
        {
            kfree_null((void **)&buffer_info->output_buf);
        }
        kfree_null((void **)&buffer_info);
    }

    kfree_null((void **)&tensors);

    return ret;
}

static int _npu_set_affinity(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;

    inst->prepare_param.affinity = arg;
    debug("[%p][%s] affinity = %d\n", inst, __func__, inst->prepare_param.affinity);

    return ret;
}

static int _npu_enable_protected_mode(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;

    inst->prepare_param.enable_prot = arg;
    debug("[%p][%s] enable_protect = %s\n", inst, __func__,
            inst->prepare_param.enable_prot? "true" : "false");

    return ret;
}

static int _npu_set_exec_memory(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;
    NPU_EXEC_MEMORY_T param;

    info("[%p] _npu_set_exec_memory\n", inst);

    if(inst->set_exec_mem == false)
    {
        inst->set_exec_mem = true;
    }

    ret = copy_from_user((void*)&param, (const void __user*)arg, sizeof(NPU_EXEC_MEMORY_T));
    if(ret)
    {
        error ("[%p] copy_from_user failed. ret:%d \n", inst, ret);
        return -EFAULT;
    }

    switch(param.type)
    {
        case NPU_EXEC_MEMORY_TYPE_PROGRAM:
            debug("[%p] _npu_set_exec_memory[NPU_EXEC_MEMORY_TYPE_PROGRAM]\n", inst);

            if(!param.physical_address)
            {
                error("[%p] [program] invaild physical_address - 0x%llX\n", inst, param.physical_address);
                return -EFAULT;
            }

            info("[%p][program] physical_address - %llx (%x)\n", inst, param.physical_address, param.size);
            inst->prepare_param.program.magic_num = USE_MAGIC;
            inst->prepare_param.program.memory_type = MEMORY_TYPE_PHYSICAL;
#ifdef USE_IOMMU
            inst->prepare_param.program.phys_addr = _npu_map_dma_address(inst, param.physical_address, param.size);
#else
            inst->prepare_param.program.phys_addr = param.physical_address;
#endif
            inst->prepare_param.program.va_addr = NULL;
#ifdef USE_CACHE_DATA
            inst->prepare_param.program.cache_data.ptr = NULL;
            inst->prepare_param.program.cache_data.size = 0;
#endif
        break;

        case NPU_EXEC_MEMORY_TYPE_PARAMETERS:
            debug("[%p] _npu_set_exec_memory[NPU_EXEC_MEMORY_TYPE_PARAMETERS]\n", inst);

            if(!param.physical_address)
            {
                error("[%p] [parameters] invaild physical_address - 0x%llX\n", inst, param.physical_address);
                return -EFAULT;
            }

            info("[%p][parameters] physical_address - %llx (%x)\n", inst, param.physical_address, param.size);
            inst->prepare_param.weight.magic_num = USE_MAGIC;
            inst->prepare_param.weight.memory_type = MEMORY_TYPE_PHYSICAL;
#ifdef USE_IOMMU
            inst->prepare_param.weight.phys_addr = _npu_map_dma_address(inst, param.physical_address, param.size);
#else
            inst->prepare_param.weight.phys_addr = param.physical_address;
#endif
            inst->prepare_param.weight.va_addr = NULL;
#ifdef USE_CACHE_DATA
            inst->prepare_param.weight.cache_data.ptr = NULL;
            inst->prepare_param.weight.cache_data.size = 0;
#endif
        break;

        case NPU_EXEC_MEMORY_TYPE_FEATURE_BUFFER:
            debug("[%p] _npu_set_exec_memory[NPU_EXEC_MEMORY_TYPE_FEATURE_BUFFER]\n", inst);

            if(!param.physical_address)
            {
                error("[%p] [feature] invaild physical_address - 0x%llX\n", inst, param.physical_address);
                return -EFAULT;
            }

            info("[%p][feature] physical_address - %llx (%x)\n", inst, param.physical_address, param.size);
            inst->prepare_param.feature.magic_num = USE_MAGIC;
            inst->prepare_param.feature.memory_type = MEMORY_TYPE_PHYSICAL;
#ifdef USE_IOMMU
            inst->prepare_param.feature.phys_addr = _npu_map_dma_address(inst, param.physical_address, param.size);
#else
            inst->prepare_param.feature.phys_addr = param.physical_address;
#endif
            inst->prepare_param.feature.va_addr = NULL;
#ifdef USE_CACHE_DATA
            inst->prepare_param.feature.cache_data.ptr = NULL;
            inst->prepare_param.feature.cache_data.size = 0;
#endif
        break;

        default:
            error("[%p] unkonwn type command, %d\n", inst, param.type);
            return -ENOIOCTLCMD;
    }

    return ret;
}

static int _npu_set_user_process_type(struct npu_inst *inst, unsigned long arg)
{
    int ret = 0;
    NPU_USER_PROCESS_T param;

    param = arg;

    inst->user_procces_type = param;
    debug("[%p] user_process_type = %d\n", inst, param);

    return ret;
}

static long npu_drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct npu_inst *inst = file->private_data;
	int ret = 0;

	mutex_lock(&inst->mutex_lock);

	if(_IOC_TYPE (cmd) != NPU_IOC_MAGIC)
	{
		error ("[%p] invalid magic. magic=0x%02x\n", inst, _IOC_TYPE (cmd));
		mutex_unlock(&inst->mutex_lock);
		return -ENOIOCTLCMD;
	}

    switch(cmd)
    {
        case NPU_IOCTL_RESET:
            info("[%p][%s] RESET\n", inst, __func__);
            break;

        case NPU_IOCTL_LOAD_BINARY:
            info("[%p][%s] LOAD_BINARY\n", inst, __func__);
            ret = _npu_set_binary(inst, arg);
            break;

        case NPU_IOCTL_SET_INPUT_TENSOR_INFO:
            info("[%p][%s] SET_INPUT_TENSOR_INFO\n", inst, __func__);
            ret = _npu_set_input_tensor_info(inst, arg);
            break;

        case NPU_IOCTL_SET_OUTPUT_TENSOR_INFO:
            info("[%p][%s] SET_OUTPUT_TENSOR_INFO\n", inst, __func__);
            ret = _npu_set_output_tensor_info(inst, arg);
            break;

        case NPU_IOCTL_SET_FEATURE_BUFFER_SIZE:
            info("[%p][%s] SET_FEATURE_BUFFER_SIZE\n", inst, __func__);
            ret = _npu_set_feature_buffer(inst, arg);
            break;

        case NPU_IOCTL_SET_PRIVATE_DATA:
            info("[%p][%s] NPU_IOCTL_SET_PRIVATE_DATA\n", inst, __func__);
            ret = _npu_set_private_data(inst, arg);
            break;

        case NPU_IOCTL_REQUEST_JOB:
            info("[%p][%s] REQUEST_JOB\n", inst, __func__);
            ret = _npu_request_job(inst, arg);
            debug("[%p][%s] Read Input tensor\n", inst, __func__);
            break;

        case NPU_IOCTL_CANCEL_JOB:
            info("[%p][%s] CANCEL_JOB\n", inst, __func__);
            break;

        case NPU_IOCTL_CANCEL_ALL_JOBS:
            info("[%p][%s] CANCEL_ALL_JOBS\n", inst, __func__);
            ret = _npu_cancel_all_jobs(inst);
            break;

        case NPU_IOCTL_GET_JOB_RESULT:
            info("[%p][%s] GET_JOB_RESULT\n", inst, __func__);
            ret = _npu_get_job_result(inst, arg);
            debug("[%p][%s] write Output tensor\n", inst, __func__);
            break;

        case NPU_IOCTL_SET_PERIOD:
            info("[%p][%s] SET_PERIOD\n", inst, __func__);
            ret = _npu_set_period(inst, arg);
            break;

        case NPU_IOCTL_SET_JOB_INPUT_TENSORS:
            info("[%p][%s] SET_JOB_INPUT_TENSORS\n", inst, __func__);
            ret = _npu_set_job_input_tensors(inst, arg);
            break;

        case NPU_IOCTL_SET_JOB_OUTPUT_TENSORS:
            info("[%p][%s] SET_JOB_OUTPUT_TENSORS\n", inst, __func__);
            ret = _npu_set_job_output_tensors(inst, arg);
            break;

        case NPU_IOCTL_SET_AFFINITY:
            info("[%p][%s] SET_AFFINITY\n", inst, __func__);
            ret = _npu_set_affinity(inst, arg);
            break;

        case NPU_IOCTL_SET_USER_PROCESS_TYPE:
            info("[%p][%s] SET_USER_PROCESS_TYPE\n", inst, __func__);
            ret = _npu_set_user_process_type(inst, arg);
            break;

        case NPU_IOCTL_SET_EXEC_MEMORY:
            info("[%p][%s] SET_EXEC_MEMORY\n", inst, __func__);
            ret = _npu_set_exec_memory(inst, arg);
            break;

        case NPU_IOCTL_ENABLE_PROTECTED_MODE:
            info("[%p][%s] ENABLE_PROTECTED_MODE\n", inst, __func__);
            ret = _npu_enable_protected_mode(inst, arg);
            break;

        default:
            error("[%p][%s] unkonwn ioctl command, %08x\n", inst, __func__, cmd);
            mutex_unlock(&inst->mutex_lock);
            return -ENOIOCTLCMD;
    }

    if(ret < 0)
    {
		error("[%p][%s] ioctl error %d for cmd %08x\n", inst, __func__, ret, cmd);
    }
    else
        info("[%p][%s] ioctl return %d for cmd %08x\n", inst, __func__, ret, cmd);

    mutex_unlock(&inst->mutex_lock);

    return ret;
}

#ifdef CONFIG_COMPAT
static long npu_drv_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long ret;

    switch(cmd)
    {
        case NPU_IOCTL_LOAD_BINARY:
        {
            NPU_BINARY_T arg_buf;

            info("[%s] NPU_IOCTL_LOAD_BINARY\n", __func__);

            ret = copy_from_user(&arg_buf, (void __user *)arg, sizeof(NPU_BINARY_T));
            if(ret)
            {
                error("copy_from_user error, %ld\n", ret);
                return -EINVAL;
            }

            arg_buf.data = compat_ptr(arg_buf.compat_data);

            ret = copy_to_user((void __user *)arg, &arg_buf, sizeof(NPU_BINARY_T));
            if(ret)
            {
                error("copy_to_user error, %ld\n", ret);
                return -EINVAL;
            }

            break;
        }

        case NPU_IOCTL_SET_FEATURE_BUFFER_SIZE:
        {
            info("[%s] NPU_IOCTL_SET_FEATURE_BUFFER_SIZE\n", __func__);
            break;
        }

        case NPU_IOCTL_SET_INPUT_TENSOR_INFO:
        case NPU_IOCTL_SET_OUTPUT_TENSOR_INFO:
        {
            TENSOR_INFO_T arg_buf;

            info("[%s] NPU_IOCTL_SET_TENSOR_INFO\n", __func__);

            ret = copy_from_user(&arg_buf, (void __user *)arg, sizeof(TENSOR_INFO_T));
            if(ret)
            {
                error("copy_from_user error, %ld\n", ret);
                return -EINVAL;
            }

            arg_buf.tensor_shape = compat_ptr(arg_buf.compat_shape);

            ret = copy_to_user((void __user *)arg, &arg_buf, sizeof(TENSOR_INFO_T));
            if(ret)
            {
                error("copy_to_user error, %ld\n", ret);
                return -EINVAL;
            }

            break;
        }

        case NPU_IOCTL_SET_PRIVATE_DATA:
        {
            PRIVATE_DATA_T arg_buf;

            info("[%s] NPU_IOCTL_SET_PRIVATE_DATA\n", __func__);

            ret = copy_from_user(&arg_buf, (void __user *)arg, sizeof(PRIVATE_DATA_T));
            if(ret)
            {
                return -EINVAL;
            }

            arg_buf.data = compat_ptr(arg_buf.compat_data);

            ret = copy_to_user((void __user *)arg, &arg_buf, sizeof(PRIVATE_DATA_T));

            if(ret)
            {
                return -EINVAL;
            }

            break;
        }

        case NPU_IOCTL_REQUEST_JOB:
        case NPU_IOCTL_CANCEL_JOB:
        case NPU_IOCTL_GET_JOB_RESULT:
        {
            info("[%s] JOB SCHEDULE CMD\n", __func__);
            break;
        }

        case NPU_IOCTL_SET_PERIOD:
        {
            info("[%s] NPU_IOCTL_SET_PERIOD\n", __func__);
            break;
        }

        case NPU_IOCTL_SET_JOB_INPUT_TENSORS:
        case NPU_IOCTL_SET_JOB_OUTPUT_TENSORS:
        {
            JOB_TENSORS_T arg_buf;

            info("[%s] SET JOB INPUT/OUTPUT TENSORS CMD\n", __func__);

            ret = copy_from_user (&arg_buf, (void __user *)arg, sizeof (JOB_TENSORS_T));
            if(ret)
            {
                return -EINVAL;
            }

            arg_buf.tensor = compat_ptr(arg_buf.compat_data);

            ret = copy_to_user((void __user *) arg, &arg_buf, sizeof(JOB_TENSORS_T));

            if(ret)
            {
                return -EINVAL;
            }

            break;
        }

        case NPU_IOCTL_SET_AFFINITY:
        {
            info("[%s] NPU_IOCTL_SET_AFFINITY\n", __func__);
            break;
        }

        case NPU_IOCTL_SET_USER_PROCESS_TYPE:
        {
            info("[%s] NPU_IOCTL_SET_USER_PROCESS_TYPE\n", __func__);
            break;
        }

        case NPU_IOCTL_SET_EXEC_MEMORY:
        {
            NPU_EXEC_MEMORY_T   exec_mem;

            ret = copy_from_user (&exec_mem, (void __user *)arg, sizeof (NPU_EXEC_MEMORY_T));
            if(ret)
            {
                return -EINVAL;
            }
            info("[%s] SET_EXEC_MEMORY type(%d) addr(0x%llx)\n", __func__, exec_mem.type, exec_mem.physical_address);

            break;
        }

        case NPU_IOCTL_ENABLE_PROTECTED_MODE:
        {
            bool enable;
            enable = arg;
            info("[%s] ENABLE_PROTECTED_MODE enable(%d)\n", __func__, enable);
            break;
        }

        default:
            error("[%s] unkonwn compat_ioctl command, %08x\n", __func__, cmd);
            return -ENOIOCTLCMD;
    }

    ret = npu_drv_ioctl(file, cmd, arg);

    info("[%s] compat_ioctl return %ld for cmd %08x\n", __func__, ret, cmd);

    return ret;
}
#endif

static int npu_drv_release(struct inode *inode, struct file *file)
{

    struct npu_inst *npu_inst = file->private_data, *cur, *n;
    struct npu_hw *npu_hw = npu_hw_controls->npu_hw;
    unsigned int i = 0;
    struct npu_work_thread *temp_npu_work;
    bool found = false;

    mutex_lock(&npu_inst->mutex_lock);
    info("[%p] %s\n", npu_inst, __func__);

    del_timer(&npu_inst->timer_utilization);
#ifdef USE_CACHE_DATA
    _uncache_buffer(&npu_inst->cache_prog);
    _uncache_buffer(&npu_inst->cache_param);

    for(i=0; i<npu_inst->run_param.number_of_input; i++) {
        if(npu_inst->run_param.input[i].memory_type != MEMORY_TYPE_PHYSICAL)
        {
            if((npu_inst->run_param.input[i].phys_addr)&&(npu_inst->run_param.input[i].magic_num == USE_MAGIC))
            {
                info("[%p] %llxn", npu_inst, npu_inst->run_param.input[i].phys_addr);
                _free_buffer(&npu_inst->run_param.input[i]);
            }
        }
    }

    if(npu_inst->run_param.output.memory_type != MEMORY_TYPE_PHYSICAL)
    {
        if((npu_inst->run_param.output.phys_addr)&&(npu_inst->run_param.output.magic_num == USE_MAGIC))
        {
            info("[%p] %llxn", npu_inst, npu_inst->run_param.output.phys_addr);
            _free_buffer(&npu_inst->run_param.output);
        }
    }
#endif

    if(npu_inst->prepare_param.core_idx >= 0)
    {
#ifdef USE_IOMMU
        if (npu_inst->prepare_param.program.phys_addr == MEMORY_TYPE_PHYSICAL) {
            info("0x%llX\n", npu_inst->prepare_param.program.phys_addr);
            if (npu_inst->prepare_param.program.phys_addr > 0) {
                dma_unmap_resource(&npu_hw_controls->pdev->dev, npu_inst->prepare_param.program.phys_addr,
                    npu_inst->prepare_param.program.size, DMA_BIDIRECTIONAL,0);
            }
        }
        if (npu_inst->prepare_param.weight.phys_addr == MEMORY_TYPE_PHYSICAL) {
            info("0x%llX\n", npu_inst->prepare_param.weight.phys_addr);
            if (npu_inst->prepare_param.weight.phys_addr > 0) {
                dma_unmap_resource(&npu_hw_controls->pdev->dev, npu_inst->prepare_param.weight.phys_addr,
                    npu_inst->prepare_param.weight.size, DMA_BIDIRECTIONAL,0);
            }
        }
        if (npu_inst->prepare_param.feature.phys_addr == MEMORY_TYPE_PHYSICAL) {
            info("0x%llX\n", npu_inst->prepare_param.feature.phys_addr);
            if (npu_inst->prepare_param.feature.phys_addr > 0) {
                dma_unmap_resource(&npu_hw_controls->pdev->dev, npu_inst->prepare_param.feature.phys_addr,
                    npu_inst->prepare_param.feature.size, DMA_BIDIRECTIONAL,0);
            }
        }
#endif

        if((npu_inst->prepare_param.program.phys_addr)&&(npu_inst->prepare_param.program.magic_num == USE_MAGIC))
        {
            _free_buffer(&npu_inst->prepare_param.program);
        }
        if(npu_inst->prepare_param.program.magic_num != IDL_MAGIC)
        {
            error("[%p] program free fail(0x%X)\n", npu_inst, npu_inst->prepare_param.program.magic_num);
        }

        if((npu_inst->prepare_param.weight.phys_addr)&&(npu_inst->prepare_param.weight.magic_num == USE_MAGIC))
        {
            _free_buffer(&npu_inst->prepare_param.weight);
        }

        if(npu_inst->prepare_param.weight.magic_num != IDL_MAGIC)
        {
            error("[%p] weight free fail(0x%X)\n", npu_inst, npu_inst->prepare_param.weight.magic_num);
        }

        if((npu_inst->prepare_param.feature.phys_addr)&&(npu_inst->prepare_param.feature.magic_num == USE_MAGIC))
        {
            _free_buffer(&npu_inst->prepare_param.feature);
        }
        if(npu_inst->prepare_param.feature.magic_num != IDL_MAGIC)
        {
            error("[%p] feature free fail(0x%X)\n", npu_inst, npu_inst->prepare_param.feature.magic_num);
        }

        npu_inst->prepare_param.core_idx = -1;
    }
    else
    {
        info("[%p][core%d] Already free buffer\n", npu_inst, npu_inst->prepare_param.core_idx);
    }

	if(npu_inst->prepare_param.reg_info != NULL)
    {
		kfree_null((void **)&npu_inst->prepare_param.reg_info);
    }
	if(npu_inst->prepare_param.stride_info != NULL)
    {
		kfree_null((void **)&npu_inst->prepare_param.stride_info);
    }

	if(npu_inst->run_param.input != NULL)
    {
		kfree_null((void **)&npu_inst->run_param.input);
    }

    _npu_cancel_all_jobs(npu_inst);

    mutex_lock(&_npu_device_lock);
    npu_hw->release(npu_hw);

    if (_inst_cnt > 0)
    {
        _inst_cnt--;
    }
    else
    {
        error("Handle error: _inst_cnt is already at minimum");
    }

    if(_inst_cnt == 0)
    {
        for(i = 0; i < npu_hw_controls->core_num; i++)
        {
            _npu_work[i].thread_stop = true;
        }

        for(i = 0; i < npu_hw_controls->core_num; i++)
        {
            temp_npu_work = &_npu_work[i];
            /* Stop service thread first. */
            if(temp_npu_work->_work_highpri_wq)
            {
                wake_up_interruptible(&_work_wait_req);
                flush_workqueue(temp_npu_work->_work_highpri_wq);
                destroy_workqueue(temp_npu_work->_work_highpri_wq);
                temp_npu_work->_work_highpri_wq = NULL;
                temp_npu_work->run_cnt = 0;
            }
        }
        mutex_destroy(&wait_queue_lock);
    #ifdef USE_IOMMU
        _npu_pm_suspend(&npu_hw_controls->pdev->dev);
    #else
        _npu_pm_suspend(&npu_hw_controls->pdev.dev);
    #endif

        if(npu_que_close(_work_task_que) < 0)
        {
            error("_work_task_que close failed\n");
        }
        else
        {
            _work_task_que = NULL;
            debug("_work_task_que close done\n");
        }

        if(npu_que_close(_work_req_que) < 0)
        {
            error("_work_req_que close failed\n");
        }
        else
        {
            _work_req_que = NULL;
            debug("_work_req_que close done\n");
        }

        if(npu_que_close(_work_rsp_que) < 0)
        {
            error("_work_rsp_que close failed\n");
        }
        else
        {
            _work_rsp_que = NULL;
            debug("_work_rsp_que close done\n");
        }
    }
    mutex_unlock(&_npu_device_lock);

    if(npu_inst->input_info)
    {
        kfree_null((void **)&npu_inst->input_info);
    }

    if(npu_inst->output_info)
    {
        kfree_null((void **)&npu_inst->output_info);
    }

    if(npu_inst->input_offset)
    {
        kfree_null((void **)&npu_inst->input_offset);
    }

    if(npu_inst->output_offset)
    {
        kfree_null((void **)&npu_inst->output_offset);
    }
    mutex_unlock(&npu_inst->mutex_lock);

    mutex_destroy(&npu_inst->mutex_lock);
    mutex_destroy(&npu_inst->sync_lock);

    mutex_lock(&npu_inst_list_lock);
    list_for_each_entry_safe (cur, n, &npu_inst_list, list) {
        if (cur == npu_inst) {
            found = true;
            list_del(&npu_inst->list);
            break;
        }
    }

    if (!found) {
        warn("no npu_inst (%p) in list\n", npu_inst);
    }

    mutex_unlock(&npu_inst_list_lock);

    kfree_null((void **)&npu_inst);

    noti("%s done. cnt(%d)\n", __func__, _inst_cnt);

    return 0;
}

/**
 * probe/remove npu device.
*/
static int _npu_probe(struct platform_device *pdev)
{
    int ret;

#ifndef USE_IOMMU
    struct npu_hw_control *control;
    struct npu_hw *hw;

    control = container_of(pdev, struct npu_hw_control, pdev);
    hw = control->npu_hw;
    noti("%s probe done\n", hw->name);
#else

    ret = npu_hwc_module_init(pdev);
    if(ret)
    {
        error("npu_hwc_module_init failed, %d\n", ret);
        return ret;
    }

    noti("_npu_probe pdev 0x%016lx, dev 0x%016lx\n", (long)pdev, (long)&pdev->dev);
#endif
    ret = npu_utilization_proc_init();
    if(ret)
    {
        error("npu_utilization_proc_init failed, %d\n", ret);
        npu_utilization_proc_exit();
    }

    ret = iommuinfo_utilization_proc_init();
    if(ret)
    {
        error("iommuinfo_utilization_proc_init failed, %d\n", ret);
        iommuinfo_utilization_proc_exit();
    }

    pm_runtime_enable(&pdev->dev);
    pm_runtime_forbid(&pdev->dev);

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
static void _npu_remove(struct platform_device *pdev)
#else
static int _npu_remove(struct platform_device *pdev)
#endif
{
    //struct npu_hw_control *control;

    //control = container_of(pdev, struct npu_hw_control, pdev);

    //platform_device_put(&control->pdev);

    pm_runtime_disable(&pdev->dev);

    noti("_npu_remove done\n");

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
    return 0;
#endif
}

/**
 * initialize npu device.
*/
static int __init _npu_module_init(void)
{
    int ret;

    noti("npu init.\n");

#ifdef USE_IOMMU
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
    npu_class = class_create("npu" );
#else
    npu_class = class_create(THIS_MODULE, "npu" );
#endif
#endif

    ret = platform_driver_register(&_npu_platform_driver);
    if(ret)
    {
        error("platform_driver_register failed, %d\n", ret);
        return ret;
    }

    mutex_init(&_npu_device_lock);

#ifndef USE_IOMMU
    ret = npu_hwc_module_init();
    if(ret)
    {
        error("npu_hwc_module_init failed, %d\n", ret);
        return ret;
    }
#endif

    noti("done\n");

    return 0;
}

/**
 * cleanup npu device.
*/
static void __exit _npu_module_exit(void)
{
    dev_t dev = MKDEV(NPU_MAJOR, NPU_MINOR);

    noti("npu exit.\n");

    if(npu_hw_controls)
    {
    #ifdef USE_IOMMU
        platform_device_del(npu_hw_controls->pdev);
    #else
        platform_device_del(&npu_hw_controls->pdev);
    #endif
        kfree_null((void **)&npu_hw_controls);
    }

    iommuinfo_utilization_proc_exit();
    npu_utilization_proc_exit();
    platform_driver_unregister(&_npu_platform_driver);
    cdev_del(&_cdev);
    unregister_chrdev_region(dev, 1);

    mutex_destroy(&_npu_device_lock);

    npu_hwc_module_exit();
}


module_init(_npu_module_init);
module_exit(_npu_module_exit);

MODULE_AUTHOR("Dongmin Kwon <dongmin.kwon@lge.com>");
MODULE_DESCRIPTION("LG NPU driver");
MODULE_LICENSE("GPL");
