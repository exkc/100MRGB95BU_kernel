/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file pe_drv.c
 *
 *  main driver implementation for pe device.
 *
 *	@author
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/dma-mapping.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "pe_cfg.h"
#include "pe_def.h"
#include "pe_drv.h"
#include "pe_io.h"
#include "pe_hal.h"
#include "pe_spd.h"
#include "vpq_hwrap.h"
#include "v4l2_vpq.h"
#include "v4l2_lgsr.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_DRV_CHECK_CODE(_checker, _action, fmt, args...)		\
	if(_checker)\
	{\
		PE_PRINT_ERROR(fmt, ##args);\
		_action;\
	}

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
/**
 *	main control block for pe device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
	int 			dev_open_count; ///< check if device is opened or not
	dev_t			devno;			///< device number
	struct cdev 	cdev;			///< char device structure
}
PE_DEVICE_T;

typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}PE_DRVDATA_T;

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern void PE_PROC_Init(void);
extern void PE_PROC_Cleanup(void);
extern void vpq_proc_init(void);
extern int pe_test_command(unsigned long arg,unsigned int flag);

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------*/
int  PE_probe(struct platform_device *pdev);

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
int 	g_pe_debug_fd;
int 	g_pe_dbg_fd;//chip level dbg
int 	g_pe_dbg_pq_fd;
int 	g_pe_major = PE_MAJOR;
int 	g_pe_minor = PE_MINOR;
#ifdef	KDRV_CONFIG_PM
bool	g_pe_open_done = false;
#endif
int 	g_pe_init = 0;

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
static int		PE_Open(struct inode *, struct file *);
static int		PE_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
static int		PE_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long		PE_Ioctl (struct file *, unsigned int, unsigned long );
#ifdef CONFIG_COMPAT
static long		PE_CompatIoctl (struct file *, unsigned int, unsigned long );
#endif
#endif
static int		PE_MMap(struct file *, struct vm_area_struct *);
/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
/**
 * main control block for pe device
*/
static PE_DEVICE_T*		g_pe_device;

/**
 * file I/O description for pe device
 *
*/
static struct file_operations g_pe_fops =
{
	.open	= PE_Open,
	.release= PE_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
	.ioctl	= PE_Ioctl,
#else
	.unlocked_ioctl = PE_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = PE_CompatIoctl,
#endif
#endif
	.mmap	= PE_MMap,
	.read	= NULL,
	.write	= NULL,
};

static PE_DRVDATA_T *g_pe_drv_data = NULL;

/*============================================================================
	Implementation Group
============================================================================*/

#ifdef	KDRV_CONFIG_PM
#if 0	//legacy
static int PE_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_PE
	PE_DRVDATA_T *drv_data;

	printk("PE - suspend BEGIN\n");

	if (g_pe_open_done == false)
	{
		printk("PE - suspend ignore\n");
		return 0;
	}

	drv_data = platform_get_drvdata(pdev);

	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_suspend();
	#endif
	PE_IO_Suspend();

	drv_data->is_suspended = 1;

	printk("PE - suspend OK\n");
#endif

	return 0;
}

static int PE_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_PE
	PE_DRVDATA_T *drv_data;

	printk("PE - resume BEGIN\n");

	vpq_hwrap_initialize(1);

	if (g_pe_open_done == false)
	{
		printk("PE - resume ignore\n");
		return 0;
	}

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0)
	{
		printk("PE - resume FAIL\n");
	}

	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_resume();
	#endif
	PE_IO_ResumeInit();

	drv_data->is_suspended = 0;
	printk("PE - resume OK\n");
#endif
	return 0;
}
#else
// suspend(snapshot)
static int PE_freeze(struct device *dev)
{
	printk("PE - freeze ok\n");
	return 0;
}

// resume(snapshot)
static int PE_restore(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_PE
	printk("PE - restore begin\n");

	vpq_hwrap_initialize(2);

	printk("PE - restore ok\n");
#endif
	return 0;
}

// resume(after snapshot image)
static int PE_thaw(struct device *dev)
{
	printk("PE - thaw ok\n");
	return 0;
}

// suspend(instant)
static int PE_suspend(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_PE
	printk("PE - suspend begin\n");

	PE_IO_Suspend();

	g_pe_drv_data->is_suspended = 1;

	printk("PE - suspend ok\n");
#endif
	return 0;
}

// resume(instant)
static int PE_resume(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_PE
	printk("PE - resume begin\n");

	vpq_hwrap_initialize(1);

	if(g_pe_drv_data->is_suspended == 0)
	{
		printk("PE - resume (not suspended)\n");
	}
	g_pe_drv_data->is_suspended = 0;
	printk("PE - resume ok\n");
#endif
	return 0;
}

#if 0	//ready
// pre_resume(instant)
static int PE_resume_early(struct device *dev)
{
	printk("PE - resume_early ok\n");
	return 0;
}
#endif
#endif
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int  PE_probe(struct platform_device *pdev)
{
	g_pe_drv_data = (PE_DRVDATA_T *)kmalloc(sizeof(PE_DRVDATA_T) , GFP_KERNEL);

	PE_PRINT_NOTI("[%s] done probe\n", PE_MODULE);

	g_pe_drv_data->is_suspended = 0;

	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_probe();
	#endif

	platform_set_drvdata(pdev, g_pe_drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod pe module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void	PE_remove(struct platform_device *pdev)
#else
static int	PE_remove(struct platform_device *pdev)
#endif
{
	PE_DRVDATA_T *drv_data;

	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_remove();
	#endif

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	PE_PRINT_NOTI("[%s] removed\n", PE_MODULE);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

/**
 *
 * module release function. this function will be called in rmmod pe module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void PE_release(struct device *dev)
{
	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_release();
	#endif

	PE_PRINT_NOTI("[%s] device released\n", PE_MODULE);
}

/*
 *	module platform driver structure
 */
static struct dev_pm_ops pm_ops =
{
	.suspend    = PE_suspend,
    .resume     = PE_resume,
    .freeze     = PE_freeze,
    .restore    = PE_restore,
    .thaw       = PE_thaw,
	//.resume_early	= PE_resume_early,
};

/*
 *	module platform driver structure
 */
static struct platform_driver pe_driver =
{
	.probe          = PE_probe,
	.remove         = PE_remove,
	//.suspend        = PE_suspend,
	//.resume         = PE_resume,
	.driver         =
	{
		.name   = PE_MODULE,
		.pm 	= &pm_ops,
	},
};

static struct platform_device pe_device = {
	.name = PE_MODULE,
	.id = 0,
	.dev =
	{
		.release = PE_release,
	},
};
#endif

/**
 * open handler for pe device
 *
 * @param   *inode [in] inode
 * @param   *filp [in] file
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int
PE_Open(struct inode *inode, struct file *filp)
{
	int ret = RET_OK;
	int 			major, minor;
	struct cdev*	cdev;
	PE_DEVICE_T*	my_dev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, PE_DEVICE_T, cdev);

	/* add your device specific code */
	if(my_dev->dev_open_count == 0)
	{
		ret = PE_DRV_OpenPicEnhanceModule();
		if(ret)
		{
			PE_PRINT_ERROR("PE_DRV_OpenPicEnhanceModule() error..\n");
			return RET_ERROR;
		}
	}
	/* end */

	my_dev->dev_open_count++;
	filp->private_data = my_dev;

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);

	PE_PRINT_NOTI("device opened (%d:%d, cnt:%d)\n", \
		major, minor, my_dev->dev_open_count);

	#ifdef	KDRV_CONFIG_PM
	g_pe_open_done = true;
	#endif

	return ret;
}

/**
 * pe close
 *
 * @param   *inode [in] inode
 * @param   *file [in] file
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int
PE_Close(struct inode *inode, struct file *file)
{
	int ret = RET_OK;
	int 			major, minor;
	PE_DEVICE_T*	my_dev;
	struct cdev*	cdev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, PE_DEVICE_T, cdev);

	if ( my_dev->dev_open_count > 0 )
	{
		--my_dev->dev_open_count;
	}

	/* add your device specific code */
	if(my_dev->dev_open_count <= 0)
	{
		ret = PE_DRV_ClosePicEnhanceModule();
		if(ret)
		{
			PE_PRINT_ERROR("PE_DRV_ClosePicEnhanceModule() error..\n");
			return RET_ERROR;
		}
	}
	/* end */

	major = imajor(inode);
	minor = iminor(inode);

	PE_PRINT_NOTI("device closed (%d:%d, cnt:%d)\n", \
		major, minor, my_dev->dev_open_count);

	return RET_OK;
}

/**
 * memory mapping to virtual region
 *
 */
static int PE_MMap(struct file *file, struct vm_area_struct *vma)
{
	int ret = RET_OK;
	unsigned long start;
	unsigned long len;
	unsigned long off = ((vma->vm_pgoff) << PAGE_SHIFT);
	unsigned int mem_base = 0;
	unsigned int mem_size = 0;

	PE_PRINT_NOTI("%s entered \n", __func__);

	ret = PE_IO_GetMemInfo(&mem_base,&mem_size);
	if (ret != RET_OK){
		PE_PRINT_ERROR("PE_IO_GetMemInfo() error.\n");
		return -EINVAL;
	}

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
	vm_flags_set (vma, VM_IO);
#else
	vma->vm_flags |= VM_IO;
#endif
	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	return io_remap_pfn_range(vma,vma->vm_start,off >> PAGE_SHIFT,vma->vm_end - vma->vm_start,vma->vm_page_prot);
}

/**
 * ioctl handler for pe device.
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 * @note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
static int
PE_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long
PE_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
#endif
{
    int err = 0, ret = 0;

    PE_DEVICE_T*	my_dev;
    struct cdev*		cdev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
#else
		struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current pe device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PE_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != PE_IOC_MAGIC)
    {
    	PE_PRINT_WARN("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > PE_IOC_MAXNR)
    {
    	PE_PRINT_WARN("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
    	return -ENOTTY;
    }

	/* TODO : add some check routine for your device */
    /*
     * check if user memory is valid or not.
     * if memory can't be accessed from kernel, return error (-EFAULT)
     */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    if (_IOC_DIR(cmd) & (_IOC_READ | _IOC_WRITE))
        err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
#else
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
#endif
    if (err)
    {
    	PE_PRINT_WARN("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n", \
										_IOC_NR(cmd), \
										(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-', \
										(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-', \
										(void*)arg );
        return -EFAULT;
	}

	PE_PRINT_DEBUG("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case PE_IOWR_PKT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			PE_PRINT_DEBUG("PE_IOWR_PKT IOCTL\n");
			ret = 0;
#else
			ret = PE_DRV_ProcessPkt(arg);
#endif
		}
		break;

		case PE_IOWR_TEST_CMD:
		{
			ret = pe_test_command(arg,0);
		}
		break;

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36)
#ifdef CONFIG_COMPAT
static long
PE_CompatIoctl ( struct file *filp, unsigned int cmd, unsigned long arg )
{
	long ret;

	switch (cmd)
	{
	case PE_IOWR_PKT:
	{
		LX_PE_PKT_T arg_buf;
		LX_PE_PKT_T rcvpkt;
		unsigned int rw_type, module_type, func_type, data_size;

		ret = copy_from_user(&arg_buf, (void __user *)arg, sizeof(LX_PE_PKT_T));
		if (ret)
		{
			return -EINVAL;
		}

		arg_buf.data = (void *)(uintptr_t)arg_buf.compat_data;

		ret = copy_to_user((void __user *)arg, &arg_buf, sizeof(LX_PE_PKT_T));
		if (ret)
		{
			return -EINVAL;
		}

		ret = copy_from_user(&rcvpkt, (void __user *)arg, sizeof(LX_PE_PKT_T));
		if (ret)
		{
			return -EINVAL;
		}

		rw_type = PE_GET_PKTINFO_RWTYPE(rcvpkt.info);
		module_type = PE_GET_PKTINFO_MODLTYPE(rcvpkt.info);
		func_type = PE_GET_PKTINFO_FUNCTYPE(rcvpkt.info);
		data_size = rcvpkt.size;

		switch (rw_type)
		{
		case PE_ITEM_PKTRW(SET):
		case PE_ITEM_PKTRW(GET):
		{
			switch (module_type)
			{
			case PE_ITEM_PKTMODL(CCM):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_CCM_GAMMALUT_T):
				{
					LX_PE_CCM_GAMMALUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(DCM):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_LUT_T):
				{
					LX_PE_DCM_DCE_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_LUT_T):
				{
					LX_PE_DCM_DSE_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_DCM_HDR_LUT_T):
				{
					LX_PE_DCM_HDR_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(NRD):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_CMN_T):
				{
					LX_PE_NRD_DNR_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_DETAIL_T):
				{
					LX_PE_NRD_DNR_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_CMN_T):
				{
					LX_PE_NRD_TNR_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_DETAIL_T):
				{
					LX_PE_NRD_TNR_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_CMN_T):
				{
					LX_PE_NRD_TNR2ND_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_DETAIL_T):
				{
					LX_PE_NRD_TNR2ND_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_CMN_T):
				{
					LX_PE_NRD_DCNT_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_DETAIL_T):
				{
					LX_PE_NRD_DCNT_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_CMN_T):
				{
					LX_PE_LED_DCNT_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_DETAIL_T):
				{
					LX_PE_LED_DCNT_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_SQM_CMN_T):
				{
					LX_PE_NRD_TNR_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2ND_SQM_CMN_T):
				{
					LX_PE_NRD_TNR2ND_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DNR_SQM_CMN_T):
				{
					LX_PE_NRD_DNR_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_NRD_DCNT_SQM_CMN_T):
				{
					LX_PE_NRD_DCNT_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_LED_DCNT_SQM_CMN_T):
				{
					LX_PE_LED_DCNT_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(SHP):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_SHP_RE_SQM_CMN_T):
				{
					LX_PE_SHP_RE_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_SHP_RE_SQM_DETAIL_T):
				{
					LX_PE_SHP_RE_SQM_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_SQM_CMN_T):
				{
					LX_PE_SHP_SR2K_SQM_CMN_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_SHP_SR2K_SQM_DETAIL_T):
				{
					LX_PE_SHP_SR2K_SQM_DETAIL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(HST):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_HST_BLK_APL_T):
				{
					LX_PE_HST_BLK_APL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(ETC):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_ETC_TBL_T):
				{
					LX_PE_ETC_TBL_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			case PE_ITEM_PKTMODL(HDR):
				switch (func_type)
				{
				case PE_ITEM_PKTFUNC(LX_PE_HDR_INFO_T):
				{
					LX_PE_HDR_INFO_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_HDR_3D_LUT_INFO_T):
				{
					LX_PE_HDR_3D_LUT_INFO_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_HDR_TONEMAP_LUT_T):
				{
					LX_PE_HDR_TONEMAP_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_HDR_EOTF_LUT_T):
				{
					LX_PE_HDR_EOTF_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_HDR_OETF_LUT_T):
				{
					LX_PE_HDR_OETF_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				case PE_ITEM_PKTFUNC(LX_PE_HDR_YGAIN_LUT_T):
				{
					LX_PE_HDR_YGAIN_LUT_T recv_data;

					ret =
						copy_from_user((void *)&recv_data,
									   (void __user *)rcvpkt.data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					recv_data.data = (UINT32 *)(uintptr_t)recv_data.compat_data;

					ret = copy_to_user((void __user *)rcvpkt.data,
									   (void *)&recv_data, rcvpkt.size);
					if (ret)
					{
						return -EINVAL;
					}

					break;
				}
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		ret = copy_to_user((void __user *)arg, &rcvpkt, sizeof(LX_PE_PKT_T));
		if (ret)
		{
			return -EINVAL;
		}

		break;
	}
	default:
		break;
	}

	ret = PE_Ioctl(filp, cmd, arg);

	return ret;
}
#endif
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is
 * 	to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void PE_PreInit(void)
{
    /* TODO: do something */
}

/**
 * init pe drv
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for pe device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_pe_debug_fd = DBG_OPEN( PE_MODULE );
	if (g_pe_debug_fd < 0) {
		PE_PRINT_ERROR("can't open g_pe_debug_fd\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_pe_debug_fd );
	OS_DEBUG_EnableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_INFO);
	OS_DEBUG_DisableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_DEBUG);
	OS_DEBUG_DisableModuleByIndex ( g_pe_debug_fd, LX_LOGM_LEVEL_TRACE);

	g_pe_dbg_fd = DBG_OPEN( "pe-dbg" );
	if (g_pe_dbg_fd < 0) {
		PE_PRINT_ERROR("can't open g_pe_dbg_fd\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_pe_dbg_fd );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_INFO);
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_DEBUG);
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_fd, LX_LOGM_LEVEL_TRACE);

	g_pe_dbg_pq_fd = DBG_OPEN( "pe-pq-dbg" );
	if (g_pe_dbg_pq_fd < 0) {
		PE_PRINT_ERROR("can't open g_pe_dbg_pq_fd\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_pe_dbg_pq_fd );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_INFO);
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_DEBUG);
	OS_DEBUG_DisableModuleByIndex ( g_pe_dbg_pq_fd, LX_LOGM_LEVEL_TRACE);

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&pe_driver) < 0)
	{
		PE_PRINT_WARN("[%s] platform driver register failed\n", PE_MODULE);

	}
	else
	{
		if(platform_device_register(&pe_device))
		{
			platform_driver_unregister(&pe_driver);
			PE_PRINT_WARN("[%s] platform device register failed\n", PE_MODULE);
		}
		else
		{
#ifdef INCLUDE_KDRV_DE
			extern struct platform_device * de_get_platform_device(void);

			pe_device.dev.parent = &de_get_platform_device()->dev;
#endif

			PE_PRINT_NOTI("[%s] platform register done\n", PE_MODULE);
		}


	}
#endif

	g_pe_device = (PE_DEVICE_T*)OS_KMalloc( sizeof(PE_DEVICE_T)*PE_MAX_DEVICE );

	if ( NULL == g_pe_device )
	{
		PE_PRINT_ERROR("out of memory. can't allocate %zu bytes\n", sizeof(PE_DEVICE_T)* PE_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_pe_device, 0x0, sizeof(PE_DEVICE_T)* PE_MAX_DEVICE );

	if (g_pe_major)
	{
		dev = MKDEV( g_pe_major, g_pe_minor );
		err = register_chrdev_region(dev, PE_MAX_DEVICE, PE_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_pe_minor, PE_MAX_DEVICE, PE_MODULE );
		g_pe_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		PE_PRINT_ERROR("can't register pe device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */
	PE_InitCfg();
	PE_IO_InitPicEnhanceModule();

	/* END */

	for ( i=0; i<PE_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_pe_major, g_pe_minor+i );
		cdev_init( &(g_pe_device[i].cdev), &g_pe_fops );
		g_pe_device[i].devno		= dev;
		g_pe_device[i].cdev.owner = THIS_MODULE;
		g_pe_device[i].cdev.ops   = &g_pe_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_pe_device[i].cdev), dev, 1 );

		if (err)
		{
			PE_PRINT_ERROR("error (%d) while adding pe device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_pe_device[i].devno, "%s%d", PE_MODULE, i );
	}

#ifndef	KDRV_CONFIG_PM
	#ifdef PE_KDRV_USE_SPD_FUNC
	PE_SPD_probe();	//don't remove, if you use PE_SPD_copy_from_user.
	#endif
#endif

	pe_hal_init();

	/* initialize proc system */
	PE_PROC_Init();
	vpq_proc_init();
	/* v4l2 init */
	v4l2_vpq_device_init();
	v4l2_lgsr_device_init();

	g_pe_init = 1;
	PE_PRINT_NOTI("pe device initialized\n");

	return 0;
}

int PE_IsInit(void)
{
	return g_pe_init;
}

/**
 * pe cleanup
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
void PE_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_pe_major, g_pe_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&pe_driver);
	platform_device_unregister(&pe_device);
#endif

	/* cleanup proc system */
	PE_PROC_Cleanup();

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<PE_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_pe_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */
	PE_IO_CleanupPicEnhanceModule();

	unregister_chrdev_region(dev, PE_MAX_DEVICE );

	OS_Free( g_pe_device );
	PE_PRINT_NOTI("pe device cleanup\n");
	return;
}

/**
 * ioctl handler for pe pkt.
 *
 * @param   arg [in] unsigned long
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int	PE_DRV_ProcessPkt( unsigned long arg )
{
	int ret = RET_ERROR;
	LX_PE_PKT_T		recv_pkt={0, 0, {NULL}};
	unsigned int	*recv_data=NULL;

	do{
		PE_PRINT_TRACE("S\n");
		ret = copy_from_user(&recv_pkt, (void __user *)arg, sizeof(LX_PE_PKT_T));
		PE_DRV_CHECK_CODE(ret, break, "[%s,%d]copy_from_user error. \n", __F__, __L__);

		PE_DRV_CHECK_CODE(!(recv_pkt.size), break, \
			"[%s,%d]recv_pkt.size is zero. \n", __F__, __L__);
		PE_DRV_CHECK_CODE(!(recv_pkt.data), break, \
			"[%s,%d]recv_pkt.data is null. \n", __F__, __L__);

		recv_data = (unsigned int *)OS_Malloc(recv_pkt.size);
		PE_DRV_CHECK_CODE(!recv_data, break, \
			"[%s,%d]recv_data is null. \n", __F__, __L__);
		ret = copy_from_user(recv_data, (void __user *)recv_pkt.data, recv_pkt.size);
		PE_DRV_CHECK_CODE(ret, break, \
			"[%s,%d]copy_from_user error. \n", __F__, __L__);

		/* io functon call */
		ret = PE_IO_ProcessPkt(recv_data, &recv_pkt);
		PE_DRV_CHECK_CODE(ret, break, \
			"[%s,%d]PE_IO_ProcessPkt() error. \n", __F__, __L__);

		if(PE_GET_PKTINFO_RWTYPE(recv_pkt.info)==PE_ITEM_PKTRW(GET))
		{
			PE_PRINT_TRACE("PE_ITEM_PKTRW(GET) case..\n");
			ret = copy_to_user((void __user *)recv_pkt.data, recv_data, recv_pkt.size);
			PE_DRV_CHECK_CODE(ret, break, \
				"[%s,%d]copy_to_user error. \n", __F__, __L__);
		}
		PE_PRINT_TRACE("E\n");
	}while(0);

	if(recv_data)	OS_Free(recv_data);

	return ret;
}

/**
 * PE_DRV_OpenPicEnhanceModule
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int	PE_DRV_OpenPicEnhanceModule(void)
{
	return PE_IO_OpenPicEnhanceModule();
}
/**
 * PE_DRV_ClosePicEnhanceModule
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int	PE_DRV_ClosePicEnhanceModule(void)
{
	return PE_IO_ClosePicEnhanceModule();
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", PE_Init);
#else
module_init(PE_Init);
#endif
module_exit(PE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

