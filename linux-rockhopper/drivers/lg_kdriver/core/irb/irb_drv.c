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
 *  main driver implementation for irb device.
 *	irb device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_irb
 */
/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_IRB_DEVICE_READ_WRITE_FOPS
#undef	IRB_DRV_PRINT_ENABLE

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_IRB	// added by SC Jung for quick booting
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
#include "irb_drv.h"
#include "irb_core.h"

#ifdef INCLUDE_O26_CHIP_KDRV
#include "../../chip/o26/irb/irb_o26common.h"
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/irb/irb_o24common.h"
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
#include "../../chip/m23/irb/irb_m23common.h"
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
#include "../../chip/o22/irb/irb_o22common.h"
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
#include "../../chip/o20/irb/irb_o20common.h"
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
#include "../../chip/e60/irb/irb_e60common.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define IRB_DEBUG_PRINT


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define IRBS_VER_MAGIC	0x190709

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for irb device.
 *	each minor device has unique control block
 *
 */
typedef struct IRB_DEVICE_t
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
IRB_DEVICE_T;


#ifdef KDRV_CONFIG_IRB
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}IRB_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	IRB_PROC_Init(void);
extern	void	IRB_PROC_Cleanup(void);
extern	void 	loglevel_change(unsigned int level);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_irb_debug_fd;
int 	g_irb_major = IRB_MAJOR;
int 	g_irb_minor = IRB_MINOR;

static irbs_driver_t* irbs_driver = NULL;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      IRB_Open(struct inode * inode, struct file * fp);
static int      IRB_Close(struct inode *inode, struct file * fp);
static long		IRB_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long		IRB_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg);
#endif

#ifdef SUPPORT_IRB_DEVICE_READ_WRITE_FOPS
static ssize_t  IRB_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  IRB_Write(struct file *, const char *, size_t, loff_t *);
#endif

//static unsigned int IRB_Poll(struct file *filp, poll_table *wait);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for irb device
*/
static IRB_DEVICE_T*		g_irb_device;

/**
 * file I/O description for irb device
 *
*/
static struct file_operations g_irb_fops =
{
	.open 	= IRB_Open,
	.release= IRB_Close,
	.unlocked_ioctl	= IRB_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= IRB_CompatIoctl,
#endif
#ifdef SUPPORT_IRB_DEVICE_READ_WRITE_FOPS
	.read 	= IRB_Read,
	.write 	= IRB_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_IRB	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev irb_message_t state
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
static int IRB_suspend(struct platform_device *pdev, irb_message_t state)
{
#ifdef KDRV_CONFIG_IRB
        IRB_DRVDATA_T    *drv_data;
        drv_data = platform_get_drvdata(pdev);

        printk("IRB - suspend BEGIN\n");

        IRB_DevSuspend();

        drv_data->is_suspended = 1;

		if (irbs_driver->suspend)
			irbs_driver->suspend();

        printk("IRB - suspend OK\n");
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
static int IRB_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_IRB
        IRB_DRVDATA_T    *drv_data;

        printk("IRB - resume BEGIN\n");

        drv_data = platform_get_drvdata(pdev);
        if(drv_data->is_suspended == 0)
        {
                printk("IRB - resume FAIL\n");
                return -1;
        }

        IRB_DevResume();

        drv_data->is_suspended = 0;

		if (irbs_driver->resume)
			irbs_driver->resume();

        printk("IRB - resume OK\n");
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
 int  IRB_probe(struct platform_device *pdev)
{

	IRB_DRVDATA_T *drv_data;

	drv_data = (IRB_DRVDATA_T *)kmalloc(sizeof(IRB_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	IRB_PRINT("[%s] done probe\n", IRB_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod irb module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void IRB_remove(struct platform_device* pdev)
#else
static int  IRB_remove(struct platform_device *pdev)
#endif
{
	IRB_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	IRB_PRINT("released\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
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
static void  IRB_release(struct device *dev)
{
	IRB_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver irb_driver =
{
	.probe		= IRB_probe,
	.suspend	= IRB_suspend,
	.remove		= IRB_remove,
	.resume		= IRB_resume,
	.driver		=
	{
		.name	= IRB_MODULE,
	},
};

static struct platform_device irb_device = {
	.name = IRB_MODULE,
	.id = -1,
	.dev = {
		.release = IRB_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void IRB_PreInit(void)
{
    /* TODO: do something */
}

int IRB_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;
	unsigned int  chip_rev;

	/* Get the handle of debug output for irb device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_irb_debug_fd = DBG_OPEN( IRB_MODULE );
	if(g_irb_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_irb_debug_fd );

#if 0
	OS_DEBUG_EnableModuleByIndex ( g_irb_debug_fd, IRB_MSG_TRACE, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_irb_debug_fd, IRB_MSG_TRACE, DBG_COLOR_NONE );
#endif
	//OS_DEBUG_EnableModuleByIndex ( g_irb_debug_fd, IRB_MSG_DEBUG, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_irb_debug_fd, IRB_MSG_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_irb_debug_fd, IRB_MSG_NOTI, DBG_COLOR_BLACK );
	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_IRB
	// added by SC Jung for quick booting
	if(platform_driver_register(&irb_driver) < 0)
	{
		IRB_PRINT("[%s] platform driver register failed\n",IRB_MODULE);
	}
	else
	{
		if(platform_device_register(&irb_device))
		{
			platform_driver_unregister(&irb_driver);
			IRB_PRINT("[%s] platform device register failed\n",IRB_MODULE);
		}
		else
		{
			IRB_PRINT("[%s] platform register done\n", IRB_MODULE);
		}
	}
#endif

	IRB_DevInit();

	g_irb_device = (IRB_DEVICE_T*)OS_KMalloc( sizeof(IRB_DEVICE_T)*IRB_MAX_DEVICE );

	if ( NULL == g_irb_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(IRB_DEVICE_T)* IRB_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_irb_device, 0x0, sizeof(IRB_DEVICE_T)* IRB_MAX_DEVICE );

	if (g_irb_major)
	{
		dev = MKDEV( g_irb_major, g_irb_minor );
		err = register_chrdev_region(dev, IRB_MAX_DEVICE, IRB_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_irb_minor, IRB_MAX_DEVICE, IRB_MODULE );
		g_irb_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register irb device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */
	for ( i=0; i<IRB_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_irb_major, g_irb_minor+i );
		cdev_init( &(g_irb_device[i].cdev), &g_irb_fops );
		g_irb_device[i].devno		= dev;
		g_irb_device[i].cdev.owner = THIS_MODULE;
		g_irb_device[i].cdev.ops   = &g_irb_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_irb_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding irb device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_irb_device[i].devno, "%s%d", IRB_MODULE, i );
	}

	/* initialize system */
	//IRB_NOTI("--------------------------------------------------\n");
	chip_rev = lx_chip_rev() & 0xFFFFFF00;

	KDRV_IRB_NOTI("IRBS KDRIVER VER[%8x]\n", IRBS_VER_MAGIC);


	if(0){}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
	{
		KDRV_IRB_NOTI("O26 IRB Driver Init\n");
		irbs_driver = get_o26_irb_driver();
		irbs_driver->init();
		IRB_PROC_Init();
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
	{
		KDRV_IRB_NOTI("O24 IRB Driver Init\n");
		irbs_driver = get_o24_irb_driver();
		irbs_driver->init();
		IRB_PROC_Init();
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) )
	{
		KDRV_IRB_NOTI("M23 IRB Driver Init\n");
		irbs_driver = get_m23_irb_driver();
		irbs_driver->init();
		IRB_PROC_Init();
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
	{
		KDRV_IRB_NOTI("O22 IRB Driver Init\n");
		irbs_driver = get_o22_irb_driver();
		irbs_driver->init();
		IRB_PROC_Init();
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		KDRV_IRB_NOTI("E60 IRB Driver Init\n");
		irbs_driver = get_e60_irb_driver();
		irbs_driver->init();

		IRB_PROC_Init();
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		KDRV_IRB_NOTI("O20 IRB Driver Init\n");
		irbs_driver = get_o20_irb_driver();
		irbs_driver->init();

		IRB_PROC_Init();
	}
#endif
	KDRV_IRB_PRINT("irb device initialized\n");
	//IRB_NOTI("--------------------------------------------------\n");
	return 0;
}

void IRB_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_irb_major, g_irb_minor );

#ifdef KDRV_CONFIG_IRB
	// added by SC Jung for quick booting
	platform_driver_unregister(&irb_driver);
	platform_device_unregister(&irb_device);
#endif

	/* cleanup proc system */
	IRB_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<IRB_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_irb_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, IRB_MAX_DEVICE );

	OS_Free( g_irb_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for irb device
 *
 */
static int IRB_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    IRB_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, IRB_DEVICE_T, cdev);

    /* TODO : add your device specific code */

	/* END */

	if(my_dev->dev_open_count == 0)
	{

	}

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    KDRV_IRB_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for irb device
 *
 */
static int IRB_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    IRB_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, IRB_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    KDRV_IRB_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}


/**
 * ioctl handler for irb device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long IRB_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	IRB_DEVICE_T*	irb_dev;
//	int err = 0;
	int ret = 0;

	/*
	  * get current irb device object
	  */
	irb_dev = (IRB_DEVICE_T*)file->private_data;

    /*
	  * check if IOCTL command is valid or not.
	  * - if magic value doesn't match, return error (-ENOTTY)
	  * - if command is out of range, return error (-ENOTTY)
	  *
	  * note) -ENOTTY means "Inappropriate ioctl for device.
	  */

    	//KDRV_IRB_NOTI("\n %x %x %x %x ",_IOC_TYPE(cmd),IRB_IOC_MAGIC,_IOC_NR(cmd),'L' );
	if ((_IOC_TYPE(cmd) != IRB_IOC_MAGIC))
		return -EINVAL;

	if (irbs_driver->ioctl)
	{
		ret = irbs_driver->ioctl(cmd, arg);
	}

    return ret;
}

#ifdef CONFIG_COMPAT
static long IRB_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd)
	{

	case IRB_IOW_COMMAND_SET:
	//case IRB_IORW_COMMAND_GET:
	{
		LX_IRB_PARAM_T arg_lx_irb_param_t;
		KDRV_IRB_DEBUG(" ioctl:IRB_SET\n");
		ret = copy_from_user(&arg_lx_irb_param_t, (void *)arg,
					   sizeof(LX_IRB_PARAM_T));
		if(ret)
		{
			return -EINVAL;
		}
		arg_lx_irb_param_t.chartime =
					(UINT8 *)(uintptr_t)arg_lx_irb_param_t.chartime_compat;
		arg_lx_irb_param_t.maketime =
					(UINT8 *)(uintptr_t)arg_lx_irb_param_t.maketime_compat;

		arg_lx_irb_param_t.reptime =
					(UINT8 *)(uintptr_t)arg_lx_irb_param_t.reptime_compat;
		arg_lx_irb_param_t.brtime =
					(UINT8 *)(uintptr_t)arg_lx_irb_param_t.brtime_compat;
		ret = copy_to_user((void *)arg, &arg_lx_irb_param_t,
					 sizeof(LX_IRB_PARAM_T));
		if(ret)
		{
			return -EINVAL;
		}
		break;
	}
	case IRB_INIT:
    	KDRV_IRB_DEBUG(" ioctl:IRB_INIT\n");
		break;
	default:
		break;
	}

	ret = IRB_Ioctl(file, cmd, arg);

	return ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",IRB_Init);
#else
module_init(IRB_Init);
#endif
module_exit(IRB_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("irb driver");
MODULE_LICENSE("GPL");

#endif

/** @} */


