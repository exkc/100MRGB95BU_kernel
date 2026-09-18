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
 *  main driver implementation for ucom device.
 *	ucom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_ucom
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_UCOM_DEVICE_READ_WRITE_FOPS
#undef	UCOM_DRV_PRINT_ENABLE

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
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
bool g_ucom_open_done = false;
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
#include "ucom_drv.h"
#include "ucom_core.h"
#include <linux/vmalloc.h>

#ifdef INCLUDE_O26_CHIP_KDRV
#include "../../chip/o26/ucom/ucom_o26_common.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/ucom/ucom_o24_common.h"
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#include "../../chip/m23/ucom/ucom_m23_common.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "../../chip/o22/ucom/ucom_o22_common.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "../../chip/e60/ucom/ucom_e60_common.h"
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
#include "../../chip/o20/ucom/ucom_o20_common.h"
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define UCOM_VER_MAGIC	0x160725A0

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for ucom device.
 *	each minor device has unique control block
 *
 */
typedef struct UCOM_DEVICE_t
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
UCOM_DEVICE_T;


#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}UCOM_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	UCOM_PROC_Init(void);
extern	void	UCOM_PROC_Cleanup(void);
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
int		g_ucom_debug_fd;
int 	g_ucom_major = UCOM_MAJOR;
int 	g_ucom_minor = UCOM_MINOR;

static ucom_driver_t* ucom_driver = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      UCOM_Open(struct inode * inode, struct file * fp);
static int      UCOM_Close(struct inode *inode, struct file * fp);
static long		UCOM_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);

#ifdef CONFIG_COMPAT
static long		UCOM_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg);
#endif

#ifdef SUPPORT_UCOM_DEVICE_READ_WRITE_FOPS
static ssize_t  UCOM_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  UCOM_Write(struct file *, const char *, size_t, loff_t *);
#endif
void UCOM_PreInit(void);
void UCOM_Cleanup(void);
int UCOM_Init(void);
int  UCOM_probe(struct platform_device *pdev);

UCOM_DEVICE_T gMicom_dev;;

UCOM_DEVICE_T* gpMicom_dev = NULL;

//static unsigned int UCOM_Poll(struct file *filp, poll_table *wait);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int	ucom_drv_inited = 0;

/**
 * main control block for ucom device
*/
static UCOM_DEVICE_T*		g_ucom_device;

/**
 * file I/O description for ucom device
 *
*/
static struct file_operations g_ucom_fops =
{
	.open 	= UCOM_Open,
	.release= UCOM_Close,
	.unlocked_ioctl	= UCOM_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= UCOM_CompatIoctl,
#endif
#ifdef SUPPORT_UCOM_DEVICE_READ_WRITE_FOPS
	.read 	= UCOM_Read,
	.write 	= UCOM_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

struct file *g_ucomfp	=NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev ucom_message_t state
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
static int UCOM_suspend(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_UCOM
        UCOM_DRVDATA_T    *drv_data;

	struct platform_device *pdev = to_platform_device(dev);

	printk("UCOM - suspend BEGIN\n");

	if(g_ucom_open_done == false)
	{
		printk("UCOM - suspend ignore\n");
		return 0;
	}
        drv_data = platform_get_drvdata(pdev);

       //UCOM_DevSuspend();


	if (ucom_driver->suspend)
	{
		ucom_driver->suspend();
	}
	drv_data->is_suspended = 1;


        printk("UCOM - suspend OK\n");

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
static int UCOM_resume(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_UCOM
        UCOM_DRVDATA_T    *drv_data;

	struct platform_device *pdev = to_platform_device(dev);


	printk("UCOM - resume BEGIN\n");

	if(g_ucom_open_done == false)
	{
		printk("UOCM - resume ignore\n");
		return 0;
	}
        drv_data = platform_get_drvdata(pdev);
        if(drv_data->is_suspended == 0)
        {
                printk("UCOM - resume FAIL\n");
                return -1;
        }

        //UCOM_DevResume();

	if (ucom_driver->resume)
	{
		ucom_driver->resume();
	}
        drv_data->is_suspended = 0;




        printk("UCOM - resume OK\n");
#endif
        return 0;
}
#ifdef KDRV_CONFIG_PM_UCOM
static struct dev_pm_ops pm_ops = {
       SET_LATE_SYSTEM_SLEEP_PM_OPS(UCOM_suspend, UCOM_resume)
};
#endif
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
 int  UCOM_probe(struct platform_device *pdev)
{

	UCOM_DRVDATA_T *drv_data;

	drv_data = (UCOM_DRVDATA_T *)kmalloc(sizeof(UCOM_DRVDATA_T),GFP_KERNEL);

	// add here driver registering code & allocating resource code

	KDRV_UCOM_PRINT("[%s] done probe\n", UCOM_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod ucom module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void UCOM_remove(struct platform_device* pdev)
#else
static int  UCOM_remove(struct platform_device *pdev)
#endif
{
	UCOM_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	KDRV_UCOM_PRINT("released\n");

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
static void  UCOM_release(struct device *dev)
{
	KDRV_UCOM_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver ucom_pm_driver =
{
	.probe		= UCOM_probe,

	.remove		= UCOM_remove,

	.driver		=
	{
		.name	= UCOM_MODULE,
		.pm = &pm_ops,
	},
};

static struct platform_device ucom_device = {
	.name = UCOM_MODULE,
	.id = -1,
	.dev = {
		.release = UCOM_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void UCOM_PreInit(void)
{
    /* TODO: do something */
}

int UCOM_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;
	unsigned int  chip_rev;
	if(ucom_drv_inited) return 0;
	/* Get the handle of debug output for ucom device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_ucom_debug_fd = DBG_OPEN( UCOM_MODULE );
	if(g_ucom_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_ucom_debug_fd );

	//OS_DEBUG_EnableModuleByIndex ( g_ucom_debug_fd, UCOM_MSG_DEBUG, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_ucom_debug_fd, UCOM_MSG_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_ucom_debug_fd, UCOM_MSG_NOTI, DBG_COLOR_BLACK );
	//OS_DEBUG_EnableModuleByIndex ( g_ucom_debug_fd, UCOM_MSG_DEBUG, DBG_COLOR_BLACK );
	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&ucom_pm_driver) < 0)
	{
		KDRV_UCOM_ERROR("[%s] platform driver register failed\n",UCOM_MODULE);
	}
	else
	{
		if(platform_device_register(&ucom_device))
		{
			platform_driver_unregister(&ucom_pm_driver);
			KDRV_UCOM_ERROR("[%s] platform device register failed\n",UCOM_MODULE);
		}
		else
		{
			KDRV_UCOM_NOTI("[%s] platform register done\n", UCOM_MODULE);
		}
	}
#endif

	UCOM_DevInit();

	g_ucom_device = (UCOM_DEVICE_T*)OS_KMalloc( sizeof(UCOM_DEVICE_T)*UCOM_MAX_DEVICE );

	if ( NULL == g_ucom_device )
	{
		KDRV_UCOM_ERROR("out of memory. can't allocate %lu bytes\n", sizeof(UCOM_DEVICE_T)* UCOM_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_ucom_device, 0x0, sizeof(UCOM_DEVICE_T)* UCOM_MAX_DEVICE );

	if (g_ucom_major)
	{
		dev = MKDEV( g_ucom_major, g_ucom_minor );
		err = register_chrdev_region(dev, UCOM_MAX_DEVICE, UCOM_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_ucom_minor, UCOM_MAX_DEVICE, UCOM_MODULE );
		g_ucom_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		KDRV_UCOM_ERROR("can't register ucom device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */
	for ( i=0; i<UCOM_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_ucom_major, g_ucom_minor+i );
		cdev_init( &(g_ucom_device[i].cdev), &g_ucom_fops );
		g_ucom_device[i].devno		= dev;
		g_ucom_device[i].cdev.owner = THIS_MODULE;
		g_ucom_device[i].cdev.ops   = &g_ucom_fops;

		/* TODO: initialize minor device */
		/* END */

		err = cdev_add (&(g_ucom_device[i].cdev), dev, 1 );

		if (err)
		{
			KDRV_UCOM_ERROR("error (%d) while adding ucom device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_ucom_device[i].devno, "%s%d", UCOM_MODULE, i );
	}

	/* initialize system */
	chip_rev = lx_chip_rev() & 0xFFFFFF00;


	if (0){}
	#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26))
	{
		ucom_driver = get_o26_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24))
	{
		ucom_driver = get_o24_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	#ifdef INCLUDE_M23_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23))
	{
		ucom_driver = get_m23_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22))
	{
		ucom_driver = get_o22_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60))
	{
		ucom_driver = get_e60_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	#ifdef INCLUDE_O20_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20))
	{
		ucom_driver = get_o20_ucom_driver();
		ucom_driver->init();
		UCOM_PROC_Init();
	}
	#endif
	else
	{
		KDRV_UCOM_NOTI("check chip: ucom init skiped\n");
	}
	ucom_drv_inited = 1;
	KDRV_UCOM_NOTI("ucom device initialized\n");
	return 0;
}

void UCOM_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_ucom_major, g_ucom_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&ucom_pm_driver);
	platform_device_unregister(&ucom_device);
#endif

	/* cleanup proc system */
	UCOM_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<UCOM_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_ucom_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, UCOM_MAX_DEVICE );

	OS_Free( g_ucom_device );


	ucom_drv_inited = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for ucom device
 *
 */
static int UCOM_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    UCOM_DEVICE_T*	my_dev;

	if( g_ucomfp == NULL)
			g_ucomfp = filp;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, UCOM_DEVICE_T, cdev);

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
#ifdef KDRV_CONFIG_PM
 g_ucom_open_done = true;
#endif
    KDRV_UCOM_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for ucom device
 *
 */
static int UCOM_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    UCOM_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, UCOM_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }
    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    KDRV_UCOM_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for ucom device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

static long UCOM_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	UCOM_DEVICE_T*	ucom_dev;
	int err = 0;
	int ret = 0;


	/*
	  * get current ucom device object
	  */
	ucom_dev = (UCOM_DEVICE_T*)file->private_data;


    /*
	  * check if IOCTL command is valid or not.
	  * - if magic value doesn't match, return error (-ENOTTY)
	  * - if command is out of range, return error (-ENOTTY)
	  *
	  * note) -ENOTTY means "Inappropriate ioctl for device.
	  */

	//KDRV_UCOM_ERROR("xxxx=0x%02X\n", _IOC_TYPE(cmd) );


    if (_IOC_TYPE(cmd) != UCOM_IOC_MAGIC)
    {
    	KDRV_UCOM_ERROR("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > UCOM_IOC_MAXNR)
    {
    	KDRV_UCOM_ERROR("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
    	return -ENOTTY;
    }


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
    	KDRV_UCOM_ERROR("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
    													_IOC_NR(cmd),
    													(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
    													(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
    													(void*)arg );
        return -EFAULT;
	}

	if (ucom_driver->ioctl)
	{
		ret = ucom_driver->ioctl(cmd, arg,file);
	}

    return ret;
}

#ifdef CONFIG_COMPAT
static long UCOM_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd)
	{

	case UCOM_IOW_COMMAND_SET:
	case UCOM_IORW_COMMAND_GET:
	{
		LX_UCOM_PARAM_T arg_lx_ucom_param_t;
		ret = copy_from_user(&arg_lx_ucom_param_t, (void *)arg,
					   sizeof(LX_UCOM_PARAM_T));
		if(ret)
		{
			return -EINVAL;
		}
		arg_lx_ucom_param_t.ubuf =
					(UINT8 *)(uintptr_t)arg_lx_ucom_param_t.ubuf_compat;

		ret = copy_to_user((void *)arg, &arg_lx_ucom_param_t,
					 sizeof(LX_UCOM_PARAM_T));
		if(ret)
		{
			return -EINVAL;
		}
		break;
	}
	case UCOM_INIT:
		break;
	default:
		break;
	}

	ret = UCOM_Ioctl(file, cmd, arg);

	return ret;
}
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",UCOM_Init);
#else
module_init(UCOM_Init);
#endif
module_exit(UCOM_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("ucom driver");
MODULE_LICENSE("GPL");

#endif

/** @} */


