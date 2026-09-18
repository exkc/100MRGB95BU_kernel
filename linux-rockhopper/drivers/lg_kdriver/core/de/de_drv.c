/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

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
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author		dongho7.park (dongho7.park@lge.com)
 *	version		1.0
 *	date		2009.12.30
 *	note		Additional information.
 *
 *	@addtogroup lg1150_de
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_qkb.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "de_drv.h"
#include "de_mem.h"

#include "de_model.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "mcu/de_int.h"
#include "de_io.h"
#include "de_hal.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include "v4l2_vsc_event.h"
#endif
#include "vsc_fw.h"
#include "cg/vsc_cg.h"
#include "vsc_bbd.h"
#include "vsc_print.h"

#include "resource_mgr.h"
#include "history_mgr.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define BSP_DE_VERSION "20221104"

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	main control block for de device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count; ///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

// BEGIN of device specific data
	int						dev_de_initialized;   ///< check if device is initialized or not
	int						dev_de_fw_downloaded; ///< check if de firmware is initialized or not

// END of device specific data
}
DE_DEVICE_T;

#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool is_suspended;
}DE_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	DE_PROC_Init(void);
extern	void	DE_PROC_Cleanup(void);

extern int vsc_suspend(int type);
extern int vsc_resume(int type);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int gUseHistory;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		DE_Init(void);
void	DE_Cleanup(void);
int DE_probe(struct platform_device *pdev);
struct platform_device * de_get_platform_device(void);
int DE_Get_BufferInfo(UINT32 *addr0, UINT32 *size0, UINT32 *addr1, UINT32 *size1);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_de_debug_fd;
int		g_de_major = DE_MAJOR;
int		g_de_minor = DE_MINOR;
int		g_de_suspended = FALSE;
int		g_de_device_opened = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int		DE_Open(struct inode *inode, struct file *filp);
static int		DE_Close(struct inode *inode, struct file *file);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int		DE_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long     DE_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long     DE_Compat_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#endif
#endif
static int      DE_Mmap(struct file *file, struct vm_area_struct *vma);
static int		DE_Thread    (void *data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for de device
*/
static DE_DEVICE_T*		g_de_device;

/**
 * file I/O description for de device
 *
*/
static struct file_operations g_de_fops =
{
	.open	= DE_Open,
	.release= DE_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= DE_Ioctl,
#else
	.unlocked_ioctl = DE_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= DE_Compat_Ioctl,
#endif
#endif
	.mmap	= DE_Mmap,
	.read	= NULL,
	.write	= NULL,
};

static struct task_struct *stDE_Thread;

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,14,0)
static int pm_suspend_target_state = PM_SUSPEND_ON;
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting

static int _de_suspend(struct platform_device *pdev, int type)
{
	#ifdef KDRV_CONFIG_PM_DE
	DE_DRVDATA_T *drv_data = platform_get_drvdata(pdev);

	vsc_suspend(type);
	DE_HAL_ResetDE(TRUE);
	resource_mgr_suspend();

	drv_data->is_suspended = 1;
	g_de_suspended = 1;
	#endif
	return 0;
}

static int _de_resume(struct platform_device *pdev, int type)
{
	#ifdef KDRV_CONFIG_PM_DE
	DE_DRVDATA_T *drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0)
	{
		printk("%s - not ready (%d)\n",__func__,type);
		return -1;
	}

	vsc_resume(type);
	resource_mgr_resume();

	drv_data->is_suspended = 0;
	g_de_suspended = 0;
	#endif
	return 0;
}

static int de_prepare(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	if (pm_suspend_target_state == PM_SUSPEND_ON)
	{
		vsc_fw_alloc_backup_all();
	}
	printk("%s - end\n",__func__);
	return 0;
}

static int de_freeze(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	_de_suspend(to_platform_device(dev), DE_DRV_PM_TYPE_FREEZE);
	printk("%s - end\n",__func__);
	return 0;
}

static int de_freeze_late(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_freeze_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_thaw_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_thaw_early(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_thaw(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	_de_resume(to_platform_device(dev), DE_DRV_PM_TYPE_THAW);
	printk("%s - end\n",__func__);
	return 0;
}

static void de_complete(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	if (pm_suspend_target_state == PM_SUSPEND_ON)
	{
		vsc_fw_free_backup_all();
	}
	printk("%s - end\n",__func__);
	return;
}

static int de_suspend(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	_de_suspend(to_platform_device(dev), DE_DRV_PM_TYPE_SUSPEND);
	printk("%s - end\n",__func__);
	return 0;
}

static int de_suspend_late(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_suspend_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_resume_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_resume_early(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_resume(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	_de_resume(to_platform_device(dev), DE_DRV_PM_TYPE_RESUME);
	printk("%s - end\n",__func__);
	return 0;
}

static int de_poweroff(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_restore_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_restore_early(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_restore(struct device *dev)
{
	printk("%s(%x) - start\n",__func__,pm_suspend_target_state);
	_de_resume(to_platform_device(dev), DE_DRV_PM_TYPE_RESTORE);
	printk("%s - end\n",__func__);
	return 0;
}

static int de_poweroff_late(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_poweroff_noirq(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_runtime_suspend(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_runtime_resume(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

static int de_runtime_idle(struct device *dev)
{
	printk("%s(%x)\n",__func__,pm_suspend_target_state);
	return 0;
}

/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int DE_probe(struct platform_device *pdev)
{
	DE_DRVDATA_T *drv_data;

	drv_data = (DE_DRVDATA_T *)kmalloc(sizeof(DE_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	DE_PRINT("[%s] done probe\n", DE_MODULE);
	drv_data->is_suspended = 0;
	g_de_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return RET_OK;
}


/**
 *
 * module remove function. this function will be called in rmmod de module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void	DE_remove(struct platform_device *pdev)
#else
static int	DE_remove(struct platform_device *pdev)
#endif
{
	DE_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code
	resource_mgr_cleanup();

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	DE_PRINT("removed\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return 0;
#endif
}

/**
 *
 * module release function. this function will be called in rmmod de module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void DE_release(struct device *dev)
{
	DE_PRINT("device released\n");
}

/**
** pm_suspend_target_state
* PM_SUSPEND_ON(0:normal), PM_SUSPEND_TO_IDLE(1), PM_SUSPEND_STANBY(2), PM_SUSPEND_MEM(3:qsm)
*/
/**
** suspend to ram state  : call pm_suspend()
* de_prepare
* de_suspend
* de_suspend_late
* de_suspend_noirq
* de_resume_noirq
* de_resume_early
* de_resume
* de_complete
*/
/**
** suspend to disk state : call hibernate()
* freeze -> creat ther snapshot image -> thaw (undo the freeze operation)
* de_prepare
* de_freeze
* de_freeze_late
* de_freeze_noirq
* create hibernation image
* de_thaw_noirq
* de_thaw_early
* de_thaw
* de_complete
*
* boot from snapshot image -> restore (similar to resume)
* de_freeze
* de_freeze_late
* de_freeze_noirq
* de_restore_noirq
* de_restore_early
* de_restore
* de_complete
*/
static struct dev_pm_ops pm_ops = {
	.prepare = de_prepare,
	.complete = de_complete,
	.suspend = de_suspend,
	.resume = de_resume,
	.freeze = de_freeze,
	.thaw = de_thaw,
	.poweroff = de_poweroff,
	.restore = de_restore,
	.suspend_late = de_suspend_late,
	.resume_early = de_resume_early,
	.freeze_late = de_freeze_late,
	.thaw_early = de_thaw_early,
	.poweroff_late = de_poweroff_late,
	.restore_early = de_restore_early,
	.suspend_noirq = de_suspend_noirq,
	.resume_noirq = de_resume_noirq,
	.freeze_noirq = de_freeze_noirq,
	.thaw_noirq = de_thaw_noirq,
	.poweroff_noirq = de_poweroff_noirq,
	.restore_noirq = de_restore_noirq,
	.runtime_suspend = de_runtime_suspend,
	.runtime_resume = de_runtime_resume,
	.runtime_idle = de_runtime_idle,
};

/*
 *	module platform driver structure
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static struct platform_driver de_driver =
#else
static struct platform_driver de_driver __refdata =
#endif
{
	.probe			= DE_probe,
	.remove			= DE_remove,
	.driver			=
	{
		.name	= DE_MODULE,
		.pm 	= &pm_ops,
	},
};

static struct platform_device de_device = {
	.name = DE_MODULE,
	.id = 0,
	.dev =
	{
		.release = DE_release,
	},
};
#endif

struct platform_device * de_get_platform_device(void)
{
	return &de_device;
}

void DE_MEM_PreInit(void)
{
	de_cfg_preinit();
}

int DE_MEM_Init(void)
{
	de_cfg_init();
	return 0;
}

void DE_MEM_Cleanup(void)
{
	de_cfg_cleanup();
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void DE_PreInit(void)
{
    /* TODO: do something */
	DE_HAL_PreInit();
}

extern int v4l2_vsc_device_init(void);
int DE_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	DE_NOTI("version : %s\n", BSP_DE_VERSION);

	/* Get the handle of debug output for de device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_de_debug_fd = DBG_OPEN( DE_MODULE );
	if (g_de_debug_fd < 0) {
		DE_ERROR("can't open de module\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_de_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_INFO, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, LX_LOGM_LEVEL_TRACE, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex( g_de_debug_fd, LX_LOGM_LEVEL_TRACE);

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&de_driver) < 0)
	{
		DE_ERROR("[%s] platform driver register failed\n",DE_MODULE);

	}
	else
	{
		if(platform_device_register(&de_device))
		{
			platform_driver_unregister(&de_driver);
			DE_ERROR("[%s] platform device register failed\n",DE_MODULE);
		}
		else
		{
			device_enable_async_suspend(&((&de_device)->dev));
			DE_NOTI("[%s] platform register done\n", DE_MODULE);
		}


	}
#endif
	g_de_device = (DE_DEVICE_T*)OS_KMalloc( sizeof(DE_DEVICE_T)*DE_MAX_DEVICE );

	if ( NULL == g_de_device )
	{
		DE_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(DE_DEVICE_T)* DE_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_de_device, 0x0, sizeof(DE_DEVICE_T)* DE_MAX_DEVICE );

	if (g_de_major)
	{
		dev = MKDEV( g_de_major, g_de_minor );
		err = register_chrdev_region(dev, DE_MAX_DEVICE, DE_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_de_minor, DE_MAX_DEVICE, DE_MODULE );
		g_de_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DE_ERROR("can't register de device\n" );
		return -EIO;
	}

	vsc_print_init();

	/* TODO : initialize your module not specific minor device */
	resource_mgr_init();

	DE_IPC_Init();
	DE_HAL_InitPHY2VIRT();
	DE_HAL_GPIO_Init();
	DE_HAL_HDMI_Init();
	DE_HAL_LVDS_Init();
	DE_HAL_MISC_Init();
	DE_HAL_OSD_Init();
	DE_HAL_InitRegister();

	de_mem_init();
	DE_INT_Init();//20190527, moved here(front of v4l2_fw_de_init)

	vsc_fw_init();//20221115, front of v4l2_vsc_probe
	vsc_cg_init();
	vsc_bbd_init();
	v4l2_vsc_device_init();
	/* END */

	for ( i=0; i<DE_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_de_major, g_de_minor+i );
		cdev_init( &(g_de_device[i].cdev), &g_de_fops );
		g_de_device[i].devno		= dev;
		g_de_device[i].cdev.owner = THIS_MODULE;
		g_de_device[i].cdev.ops   = &g_de_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_de_device[i].cdev), dev, 1 );

		if (err)
		{
			DE_ERROR("error (%d) while adding de device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
		OS_CreateDeviceClass ( g_de_device[i].devno, "%s%d", DE_MODULE, i );
	}

	/* initialize proc system */
	DE_PROC_Init ( );
	//DE_INT_Init();//20190527, moved above

	stDE_Thread = kthread_create(DE_Thread, (void*)NULL, "de_thread");
	if(stDE_Thread)
	{
		wake_up_process(stDE_Thread);
	}
	else
	{
		DE_PRINT("DE Thread alreadu created\n");
	}

	DE_NOTI("de device initialized\n");

	return 0;
}

void DE_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_de_major, g_de_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&de_driver);
	platform_device_unregister(&de_device);
#endif
	/* cleanup proc system */
	DE_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<DE_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_de_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */
	DE_IPC_Free();
	DE_HAL_FreePHY2VIRT();

	if(stDE_Thread != NULL)
		kthread_stop(stDE_Thread);

	unregister_chrdev_region(dev, DE_MAX_DEVICE );

	OS_Free( g_de_device );

	DE_PRINT("de device cleanup\n");
}

/**
 * DE Thread
 *
 * @param
 * @return
 * @see
 * @author
 */
static int DE_Thread(void *data)
{
	static int ret = RET_OK;

	while(1)
	{
		resource_mgr_thread();
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for de device
 *
 */
static int DE_Open(struct inode *inode, struct file *filp)
{
	int					major,minor;
	struct cdev*		cdev;
	DE_DEVICE_T*	my_dev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	major = imajor(inode);
	minor = iminor(inode);

	if(minor >= DE_MAX_DEVICE)
	{
		DE_ERROR( "Invalid device num[%d] for Open!!\n", minor);
		return -1;
	}

	/*	TODO : add your device specific code */
	/*	support multi-process system */
	if (g_de_device_opened == 0 )
	{
		my_dev->dev_de_initialized = 0;
		my_dev->dev_de_fw_downloaded = 0;
	}

	/* END */

	g_de_device_opened++;
	filp->private_data = my_dev;

	/* some debug */
	DE_PRINT("device opened (%d:%d)\n", major, minor );

	return 0;
}

/**
 * release handler for de device
 *
 */
static int DE_Close(struct inode *inode, struct file *file)
{
	int					major,minor;
	DE_DEVICE_T*	my_dev;
	struct cdev*		cdev;


	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	if ( my_dev->dev_open_count > 0 )
	{
		--my_dev->dev_open_count;
	}
	DE_IO_ReleaseVTM(0);

	/* TODO : add your device specific code */
	/*	support multi-process system */
	if ( my_dev->dev_open_count < 0 )
	{
		DE_INT_Cleanup();
	}

	/* END */

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);
	DE_PRINT("device closed (%d:%d)\n", major, minor );
	return 0;
}

static int de_mmap_to_phys(struct vm_area_struct *vma)
{
	ULONG offset = vma->vm_pgoff << PAGE_SHIFT;
	ULONG vm_size = vma->vm_end - vma->vm_start;
	UINT32 is_entry = 0;
	LX_MEMCFG_T **p;
	LX_MEMCFG_T *entry[] = {
		&g_m0_pqe_nsv,
		&g_m1_pqe_nsv,
		&g_m2_pqe_nsv,
		NULL
	};

	DE_NOTI("%-20s: 0x%08lx ~ 0x%08lx, size:0x%08lx\n","vm phys",offset,(offset+vm_size),vm_size);

	p = entry;
	while (*p) {
		DE_NOTI("%-20s: 0x%08x ~ 0x%08x, size:0x%08x\n",(*p)->name,(*p)->base,((*p)->base + (*p)->size),(*p)->size);
		if (((*p)->base > 0) && ((*p)->size > 0) && (offset >= (*p)->base) && ((offset+vm_size) <= ((*p)->base + (*p)->size))) {
			DE_NOTI("entry check\n");
			is_entry = 1;
			break;
		}
		p++;
	}

	if (!is_entry) {
		DE_NOTI("invalid phys : not in entry\n");
		return -EINVAL;
	}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
	vm_flags_set(vma, VM_IO);
#else
	vma->vm_flags |= VM_IO;
#endif
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	if (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, vm_size, vma->vm_page_prot)) {
		return -EAGAIN;
	}

	DE_NOTI("done\n");
	return 0;
}
/**
 * memory mapping to virtual region
 *
 */
#define DE_MMAP_TO_PHYS 0x10000000
static int DE_Mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int	minor;
	ULONG phy_start,phy_end;
	ULONG offset= vma->vm_pgoff << PAGE_SHIFT;
	ULONG size	= vma->vm_end - vma->vm_start;
	ULONG end   = PAGE_ALIGN(offset + size);
	UINT32 cap_mem_0, cap_mem_1, cap_size;
	UINT32 *mem_info[3];


	minor = iminor(inode);
	if(0){//minor != 1) {
		DE_ERROR("only dev_minor_num_1 (req. num %d)\n", minor);
		return -EINVAL;
	}

	if (size & (PAGE_SIZE-1)) {
		DE_ERROR("invalid size : 0x%lx\n",size);
		return -EINVAL;
	}

	DE_NOTI("vma : start:%08lx, end:%08lx, offset:%08lx",vma->vm_start,vma->vm_end,offset);

	if (offset >= DE_MMAP_TO_PHYS) {
		return de_mmap_to_phys(vma);
	}

	// get & check the range of shared-mem
	mem_info[0] = &cap_mem_0;
	mem_info[1] = &cap_mem_1;
	mem_info[2] = &cap_size;
	if(DE_HAL_GetSharedMem(vma->vm_pgoff<<PAGE_SHIFT, mem_info)) return -EINVAL;
	if(cap_mem_0 == 0 || cap_mem_1 == 0 || cap_size == 0) return -EINVAL;

	// check offset is allowed range or not.
	phy_start = cap_mem_0 & PAGE_MASK;
	phy_end   = PAGE_ALIGN( phy_start + cap_size);
	if ( phy_start <= offset && end <= phy_end ) goto allowed;

	phy_start = cap_mem_1 & PAGE_MASK;
	phy_end   = PAGE_ALIGN( phy_start + cap_size);
	if ( phy_start <= offset && end <= phy_end ) goto allowed;

	return -EINVAL;

allowed:
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
	vm_flags_set (vma, VM_IO);
#else
	vma->vm_flags |= VM_IO;
#endif
// rm at kernel 3.10	vma->vm_flags |= VM_RESERVED;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	if (io_remap_pfn_range(vma, vma->vm_start, \
				vma->vm_pgoff, size, vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}

int DE_Get_BufferInfo(UINT32 *addr0, UINT32 *size0, UINT32 *addr1, UINT32 *size1)
{
	unsigned long arg;
	LX_DE_MEM_SYS_INFO_T stParams;

	if(!addr0 || !size0 || !addr1 || !size1) return -1;

	memset(&stParams, 0, sizeof(LX_DE_MEM_SYS_INFO_T));
	arg = (unsigned long)&stParams;
	DE_IO_GetMEMInfo(arg, 1);

	*addr0 = stParams.de_frm_m1.base + stParams.de_prew.size;
	*size0 = stParams.de_hdr.base - *addr0;
	*addr1 = stParams.de_frm_m2.base;
	*size1 = stParams.de_frm_m2.size;

	DE_NOTI("%x %x %x %x\n", *addr0, *size0, *addr1, *size1);
	return 0;
}
/**
 * ioctl handler for de device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int DE_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long DE_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
#endif
{
	int err = 0, ret = 0;

	DE_DEVICE_T*	my_dev;
	struct cdev*		cdev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current de device object
	 */
	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	/*
	 * check if IOCTL command is valid or not.
	 * - if magic value doesn't match, return error (-ENOTTY)
	 * - if command is out of range, return error (-ENOTTY)
	 *
	 * note) -ENOTTY means "Inappropriate ioctl for device.
	 */
	if (_IOC_TYPE(cmd) != DE_IOC_MAGIC)
	{
		DE_WARN("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > DE_IOC_MAXNR)
	{
		DE_WARN("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
		return -ENOTTY;
	}
	if(gUseHistory){
		Push_Ioc_Hist(cmd,arg);
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
		DE_WARN("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
									_IOC_NR(cmd),
									(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
									(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
									(void*)arg );
		return -EFAULT;
	}

	/*	support multi-process system */
	{
		int pid;
		pid = task_tgid_vnr(current);
		DE_VTV("cmd[0x%08X] from pid = %d\n", cmd, pid);
		if (my_dev->dev_de_initialized == 0)
		{
			//DE_INT_Init();//20190527, removed, because of vsync_cb null
			my_dev->dev_de_initialized++;
		}
	}
	ret = resource_mgr_ioctl(cmd, arg,CALL_FROM_USER);
#if 0
	// for o20 SLT (SICDTV-7378)
	if(cmd == DE_IOR_GET_SRC_STATUS)
	{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
		#include "v4l2_vsc_event.h"
#endif
		kwrap_vp_timing_info_t ti;
		UINT16 h, v, s, f;
		LX_DE_SRC_STATUS_T *pstParams = (LX_DE_SRC_STATUS_T *)arg;

		vsc_get_timinginfo(0, &ti);
		h = ti.hActive;
		v = ti.vActive;
		f = ti.vFreq;
		s = ti.scanType;
		copy_to_user(&pstParams->vdecInfo.h_size, &h, sizeof(UINT16));
		copy_to_user(&pstParams->vdecInfo.v_size, &v, sizeof(UINT16));
		copy_to_user(&pstParams->vdecInfo.v_freq, &f, sizeof(UINT16));
		copy_to_user(&pstParams->vdecInfo.isProg, &s, sizeof(UINT16));
	}
#endif
	return ret;
}

#ifdef CONFIG_COMPAT
static long DE_Compat_Ioctl(struct file *filp, unsigned int cmd,
							unsigned long arg)
{
	long ret;

	switch (cmd)
	{
	case DE_IOW_FW_DOWNLOAD:
	{
		LX_DE_FW_DWLD_T arg_lx_de_fw_dwld_t;
		ret = copy_from_user(&arg_lx_de_fw_dwld_t, (void __user *)arg, sizeof(LX_DE_FW_DWLD_T));
		arg_lx_de_fw_dwld_t.pData = (char *)(uintptr_t)arg_lx_de_fw_dwld_t.compat_pData;
		ret = copy_to_user((void __user *)arg, &arg_lx_de_fw_dwld_t, sizeof(LX_DE_FW_DWLD_T));
		break;
	}
	case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER:
	{
// remove legacy code(20190311) - use kadp code
		break;
	}
	case DE_IOR_GET_SCALER_INFO:
	{
// remove legacy code(20190311) 
		break;
	}
	case DE_IOW_SET_CAPTURE:
	{
// remove legacy code(20190311) - use vt
		break;
	}
	case DE_DHDR_IP_IORW_INIT:
	{
		LX_DOLBY_IOCTL_INIT_T arg_lx_dolby_ioctl_init_t;
		ret = copy_from_user(&arg_lx_dolby_ioctl_init_t, (void __user *)arg, sizeof(LX_DOLBY_IOCTL_INIT_T));
		arg_lx_dolby_ioctl_init_t.sptrDolbyInit =
			(LX_DOLBY_IO_MAP_T *)(uintptr_t)arg_lx_dolby_ioctl_init_t.compat_sptrDolbyInit;
		ret = copy_to_user((void __user *)arg, &arg_lx_dolby_ioctl_init_t, sizeof(LX_DOLBY_IOCTL_INIT_T));
		break;
	}
	case DE_DHDR_IP_IOR_HDMI_MD_READ:
	{
		LX_DOLBY_IOCTL_HDMI_MD_T arg_lx_dolby_ioctl_hdmi_md_t;
		ret = copy_from_user(&arg_lx_dolby_ioctl_hdmi_md_t, (void __user *)arg, sizeof(LX_DOLBY_IOCTL_HDMI_MD_T));
		arg_lx_dolby_ioctl_hdmi_md_t.eMDType =
			(LX_DOLBY_DM_MD_TYPE *)(uintptr_t)arg_lx_dolby_ioctl_hdmi_md_t.compat_eMDType;
		arg_lx_dolby_ioctl_hdmi_md_t.sptrMetadata =
			(LX_DOLBY_DM_MD_T *)
				(uintptr_t)arg_lx_dolby_ioctl_hdmi_md_t.compat_sptrMetadata;
		ret = copy_to_user((void __user *)arg, &arg_lx_dolby_ioctl_hdmi_md_t, sizeof(LX_DOLBY_IOCTL_HDMI_MD_T));
		break;
	}
	case DE_DHDR_IP_IOR_OTT_MD_READ:
	{
		LX_DOLBY_OTT_MD_IOCTL_T arg_lx_dolby_ott_md_ioctl_t;
		ret = copy_from_user(&arg_lx_dolby_ott_md_ioctl_t, (void __user *)arg, sizeof(LX_DOLBY_OTT_MD_IOCTL_T));
		arg_lx_dolby_ott_md_ioctl_t.nptrInfo =
			(UINT32 *)arg_lx_dolby_ott_md_ioctl_t.nptrInfo;
		ret = copy_to_user((void __user *)arg, &arg_lx_dolby_ott_md_ioctl_t, sizeof(LX_DOLBY_OTT_MD_IOCTL_T));
		break;
	};
	default:
		break;
	}

	ret = DE_Ioctl(filp, cmd, arg);

	return ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", DE_Init);
#else
module_init(DE_Init);
#endif
module_exit(DE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("DE driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

