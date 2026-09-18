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
 *  main driver implementation for emmc device.
 *	emmc device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2015.07.17
 *  note			Additional information.
 *
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_PM_DEVICE_READ_WRITE_FOPS
#undef	EMMC_DRV_PRINT_ENABLE

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_PM
#include <linux/platform_device.h>
#endif
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/io.h>

#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/suspend.h>

#include <linux/tick.h>
#include <trace/events/power.h>

#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>

#include "os_util.h"
#include "base_device.h"
#include "emmc_drv.h"
#include "emmc_core.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define EMMC_DEBUG_PRINT

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define EMMC_COPY_FROM_USER(d,s,l) 							\
		do {												\
			if (copy_from_user((void*)d, (void *)s, l)) {	\
				EMMC_ERROR("ioctl: copy_from_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

#define EMMC_COPY_TO_USER(d,s,l) 							\
		do {												\
			if (copy_to_user((void*)d, (void *)s, l)) { 	\
				EMMC_ERROR("ioctl: copy_to_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for emmc device.
 *	each minor device has unique control block
 *
 */
typedef struct EMMC_DEVICE_t
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

// BEGIN of device specific data
	OS_SEM_T				mutex;
// END of device specific data
}
EMMC_DEVICE_T;


#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}EMMC_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void loglevel_change(unsigned int level);
extern void EMMC_PROC_Init (void);
extern void EMMC_PROC_Cleanup (void);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_emmc_debug_fd;
int 	g_emmc_major = EMMC_MAJOR;
int 	g_emmc_minor = EMMC_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      EMMC_Open(struct inode *inode, struct file *filp);
static int      EMMC_Close(struct inode *inode, struct file *filp);
static long		EMMC_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);

#ifdef SUPPORT_PM_DEVICE_READ_WRITE_FOPS
static ssize_t  EMMC_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  EMMC_Write(struct file *, const char *, size_t, loff_t *);
#endif


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for emmc device
*/
static EMMC_DEVICE_T*		g_emmc_device;

/**
 * file I/O description for emmc device
 *
*/
static struct file_operations g_emmc_fops =
{
	.open 	= EMMC_Open,
	.release= EMMC_Close,
	.unlocked_ioctl	= EMMC_Ioctl,
#ifdef SUPPORT_PM_DEVICE_READ_WRITE_FOPS
	.read 	= EMMC_Read,
	.write 	= EMMC_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_PM
	/**
	 *
	 * suspending module.
	 *
	 * @param	struct platform_device *pdev pm_message_t state
	 * @return	int 0 : OK, -1 : NOT OK
	 *
	 */
static int EMMC_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_EMMC
		EMMC_DRVDATA_T	*drv_data;
		drv_data = platform_get_drvdata(pdev);

		printk("EMMC - suspend BEGIN\n");

		EMMC_DevSuspend();

		drv_data->is_suspended = 1;

		printk("EMMC - suspend OK\n");
#endif
		return 0;
}

/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int EMMC_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_EMMC
	EMMC_DRVDATA_T	*drv_data;

	printk("EMMC - resume BEGIN\n");

	drv_data = platform_get_drvdata(pdev);
	if(drv_data->is_suspended == 0)
	{
		printk("EMMC - resume FAIL\n");
		return -1;
	}

	EMMC_DevResume();

	drv_data->is_suspended = 0;

	printk("EMMC - resume OK\n");
#endif
	return 0;
}
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
int EMMC_probe(struct platform_device *pdev)
{

	EMMC_DRVDATA_T *drv_data;

	drv_data = (EMMC_DRVDATA_T *)kmalloc(sizeof(EMMC_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	EMMC_PRINT("[%s] done probe\n", EMMC_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod pm module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
static void EMMC_remove(struct platform_device *pdev)
#else
static int EMMC_remove(struct platform_device *pdev)
#endif
{
	EMMC_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	EMMC_PRINT("released\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,0,0)
	return 0;
#endif
}

/**
 *
 * module release function. this function will be called in rmmod module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void  EMMC_release(struct device *dev)
{
	EMMC_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver emmc_driver =
{
	.probe		= EMMC_probe,
	.suspend	= EMMC_suspend,
	.remove 	= EMMC_remove,
	.resume 	= EMMC_resume,
	.driver 	=
	{
		.name	= EMMC_MODULE,
	},
};

static struct platform_device emmc_device = {
	.name	= EMMC_MODULE,
	.id		= -1,
	.dev	=
	{
		.release = EMMC_release,
	},
};
#endif


/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */

void EMMC_PreInit(void)
{
    /* TODO: do something */
}

int EMMC_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for emmc device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_emmc_debug_fd = DBG_OPEN( EMMC_MODULE );
	if(g_emmc_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_emmc_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_emmc_debug_fd, EMMC_MSG_DEBUG, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_emmc_debug_fd, EMMC_MSG_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_emmc_debug_fd, EMMC_MSG_NOTI, DBG_COLOR_BLACK );
	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */

#ifdef KDRV_CONFIG_PM
	if(platform_driver_register(&emmc_driver) < 0)
	{
		EMMC_PRINT("[%s] platform driver register failed\n",EMMC_MODULE);
	}
	else
	{
		if(platform_device_register(&emmc_device))
		{
			platform_driver_unregister(&emmc_driver);
			EMMC_PRINT("[%s] platform device register failed\n",EMMC_MODULE);
		}
		else
		{
			EMMC_PRINT("[%s] platform register done\n", EMMC_MODULE);
		}
	}
#endif

	EMMC_DevInit();

	g_emmc_device = (EMMC_DEVICE_T*)OS_KMalloc( sizeof(EMMC_DEVICE_T)*EMMC_MAX_DEVICE );

	if ( NULL == g_emmc_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %u bytes\n", (unsigned int)sizeof(EMMC_DEVICE_T) * EMMC_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_emmc_device, 0x0, sizeof(EMMC_DEVICE_T)* EMMC_MAX_DEVICE );

	if (g_emmc_major)
	{
		dev = MKDEV( g_emmc_major, g_emmc_minor );
		err = register_chrdev_region(dev, EMMC_MAX_DEVICE, EMMC_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_emmc_minor, EMMC_MAX_DEVICE, EMMC_MODULE );
		g_emmc_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register emmc device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */
	for ( i=0; i<EMMC_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_emmc_major, g_emmc_minor+i );
		cdev_init( &(g_emmc_device[i].cdev), &g_emmc_fops );
		g_emmc_device[i].devno		= dev;
		g_emmc_device[i].cdev.owner = THIS_MODULE;
		g_emmc_device[i].cdev.ops   = &g_emmc_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_emmc_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding emmc device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_emmc_device[i].devno, "%s%d", EMMC_MODULE, i );
	}

	/* initialize system */
	EMMC_NOTI("EMMC DEGUG KDRV Init\n");
	EMMC_PROC_Init();

	return 0;
}

void EMMC_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_emmc_major, g_emmc_minor );

	/* cleanup proc system */
	EMMC_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<EMMC_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_emmc_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, EMMC_MAX_DEVICE );

	OS_Free( g_emmc_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for emmc device
 *
 */
static int EMMC_Open(struct inode *inode, struct file *filp)
{
	int				major,minor;
	struct cdev*   	cdev;
	EMMC_DEVICE_T*	my_dev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, EMMC_DEVICE_T, cdev);

	/* TODO : add your device specific code */

	/* END */
	my_dev->dev_open_count++;
	filp->private_data = my_dev;

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);
	EMMC_PRINT("device opened (%d:%d)\n", major, minor );

	return 0;
}

/**
 * release handler for emmc device
 *
 */
static int EMMC_Close(struct inode *inode, struct file *file)
{
	int				major,minor;
	EMMC_DEVICE_T*	my_dev;
	struct cdev*	cdev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, EMMC_DEVICE_T, cdev);

	if ( my_dev->dev_open_count > 0 )
	{
		--my_dev->dev_open_count;
	}

	/* TODO : add your device specific code */

	/* END */

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);
	EMMC_PRINT("device closed (%d:%d)\n", major, minor );

	return 0;
}

/**
 * ioctl handler for emmc device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long EMMC_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	EMMC_DEVICE_T*	emmc_dev;
	int ret = 0;

	/*
	  * get current emmc device object
	  */
	emmc_dev = (EMMC_DEVICE_T*)file->private_data;

	/*
	  * check if IOCTL command is valid or not.
	  * - if magic value doesn't match, return error (-ENOTTY)
	  * - if command is out of range, return error (-ENOTTY)
	  *
	  * note) -ENOTTY means "Inappropriate ioctl for device.
	  */

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", EMMC_Init);
#else
module_init(EMMC_Init);
#endif
module_exit(EMMC_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("emmc driver");
MODULE_LICENSE("GPL");

#endif

/** @} */

