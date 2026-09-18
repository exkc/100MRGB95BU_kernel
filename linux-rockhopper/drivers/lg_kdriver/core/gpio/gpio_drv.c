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
 *  main driver implementation for gpio device.
 *	gpio device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  				jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gpio
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
#undef	GPIO_DRV_PRINT_ENABLE
#define USE_KERNEL_INTR
//#define GPIO_DRV_PRINT_ENABLE
//static void Debug_GPIO_Print(void);

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include "gpio_drv.h"
#include "gpio_reg.h"
#include "gpio_core.h"
#include <linux/vmalloc.h>

#ifdef INCLUDE_O18_CHIP_KDRV
#include "../../chip/o18/gpio/gpio_hal_o18.h"
#endif	//#ifdef INCLUDE_O18_CHIP_KDRV

#ifdef INCLUDE_M17_CHIP_KDRV
#include "../../chip/m17/gpio/gpio_hal_m17.h"
#endif	//#ifdef INCLUDE_M17_CHIP_KDRV


#ifdef INCLUDE_L18_CHIP_KDRV
#include "../../chip/l18/gpio/gpio_hal_l18.h"
#endif	//#ifdef INCLUDE_L18_CHIP_KDRV

#include <linux/irq.h>
#include <linux/interrupt.h>
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GPIO_COPY_FROM_USER(d,s,l) 							\
		do {												\
			if (copy_from_user((void*)d, (void *)s, l)) {	\
				GPIO_ERROR("ioctl: copy_from_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

#define GPIO_COPY_TO_USER(d,s,l) 							\
		do {												\
			if (copy_to_user((void*)d, (void *)s, l)) { 	\
				GPIO_ERROR("ioctl: copy_to_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)



/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for gpio device.
 *	each minor device has unique control block
 *
 */

typedef struct GPIO_DEVICE_t
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
	int	 					isrArray[INT_ARRAY_NUM];
// END of command device

// BEGIN of device specific data
	OS_SEM_T				mutex;
// END of device specific data
}
GPIO_DEVICE_T;


#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}GPIO_DRVDATA_T;
#endif




//GPIO_INTR_CALLBACK_T _gpio_isr_func[GPIO_PIN_MAX]= {{NULL},};
GPIO_INTR_INFO_T	 gpio_isr_info[GPIO_PIN_MAX] = {{0,0},};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	GPIO_CFG_Init(void);
extern	void	GPIO_PROC_Init(void);
extern	void	GPIO_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		GPIO_Init(void);
void	GPIO_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int	g_gpio_debug_fd;
int 	g_gpio_major = GPIO_MAJOR;
int 	g_gpio_minor = GPIO_MINOR;
int gpio_intr_pin = 0;
int gpio_intr_pin_value = 0;
int debugpin;
int debugpindir;
int debugpinval;


UINT32 g_poll_intr_idx = 0;

spinlock_t gpioPoll_lock;

#if defined (CHIP_NAME_o18) || defined (CHIP_NAME_m19)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_00);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_01);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_02);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_03);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_04);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_05);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_06);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_07);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_08);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_09);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_10);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_11);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_12);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_13);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_14);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_15);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_16);
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_17);

#else
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_00_02); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_03_05); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_06_08); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_09_11); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_12_14); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue_15_17); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
#endif

DECLARE_WAIT_QUEUE_HEAD(gGPIOIntrDurWaitQueue); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)



wait_queue_head_t * gGPIOPollWaitQueueT[GPIO_IRQ_NUM_NR + 1] =
{
#if defined (CHIP_NAME_o18) || defined (CHIP_NAME_m19)
	&gGPIOPollWaitQueue_00,
	&gGPIOPollWaitQueue_01,
	&gGPIOPollWaitQueue_02,
	&gGPIOPollWaitQueue_03,
	&gGPIOPollWaitQueue_04,
	&gGPIOPollWaitQueue_05,
	&gGPIOPollWaitQueue_06,
	&gGPIOPollWaitQueue_07,
	&gGPIOPollWaitQueue_08,
	&gGPIOPollWaitQueue_09,
	&gGPIOPollWaitQueue_10,
	&gGPIOPollWaitQueue_11,
	&gGPIOPollWaitQueue_12,
	&gGPIOPollWaitQueue_13,
	&gGPIOPollWaitQueue_14,
	&gGPIOPollWaitQueue_15,
	&gGPIOPollWaitQueue_16,
	&gGPIOPollWaitQueue_17,
#else
	&gGPIOPollWaitQueue_00_02,
	&gGPIOPollWaitQueue_03_05,
	&gGPIOPollWaitQueue_06_08,
	&gGPIOPollWaitQueue_09_11,
	&gGPIOPollWaitQueue_12_14,
	&gGPIOPollWaitQueue_15_17,
#endif
};

DECLARE_WAIT_QUEUE_HEAD(gGPIOPollWaitQueue); //wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
UINT32 * 		gpio_intr_num;

UINT8 *		gpio_intr_num_str[GPIO_IRQ_NUM_NR] ={
#if defined (CHIP_NAME_o18) || defined (CHIP_NAME_m19)
"gpioarray_00",	// 8 pin share 1 interrupt
"gpioarray_01",
"gpioarray_02",
"gpioarray_03",
"gpioarray_04",
"gpioarray_05",
"gpioarray_06",
"gpioarray_07",
"gpioarray_08",
"gpioarray_09",
"gpioarray_10",
"gpioarray_11",
"gpioarray_12",
"gpioarray_13",
"gpioarray_14",
"gpioarray_15",
"gpioarray_16",
"gpioarray_17",
#else
"gpioarray_00_02",	// 24 pin share 1 interrupt
"gpioarray_03_05",
"gpioarray_06_08",
"gpioarray_09_11",
"gpioarray_12_14",
"gpioarray_15_17",
#endif
};

//intr callback use
UINT32 gpio_intrarray_used[GPIO_IRQ_NUM_NR]={0,};		/* 23~0 bit: gpio pin num */
UINT32 gpio_pollarray_context[GPIO_IRQ_NUM_NR]={0,};	/* 0~15 bit: pid    16 bit: (0: no create task ,1: create task) */


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      GPIO_Open(struct inode * inode, struct file * fp);
static int      GPIO_Close(struct inode * inode, struct file * fp);
static long		GPIO_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long		GPIO_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg);
#endif

#ifdef SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
static ssize_t  GPIO_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  GPIO_Write(struct file *, const char *, size_t, loff_t *);
#endif

static unsigned int GPIO_Poll(struct file *filp, poll_table *wait);
int  GPIO_probe(struct platform_device *pdev);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for gpio device
*/
static GPIO_DEVICE_T*		g_gpio_device;

/**
 * file I/O description for gpio device
 *
*/
static struct file_operations g_gpio_fops =
{
	.open 	= GPIO_Open,
	.release= GPIO_Close,
	.unlocked_ioctl	= GPIO_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= GPIO_CompatIoctl,
#endif
#ifdef SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
	.read 	= GPIO_Read,
	.write 	= GPIO_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
	.poll	= GPIO_Poll,
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK, -1 : NOT OK
 *
 */


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))
static int __GPIO_suspend(struct device *dev, int sel_before)
{
#ifdef KDRV_CONFIG_PM_GPIO
    GPIO_DRVDATA_T  *drv_data;
	struct platform_device *pdev = to_platform_device(dev);

    printk("GPIO - suspend(%d) BEGIN\n", sel_before);
    drv_data = platform_get_drvdata(pdev);

	if (sel_before) {
		GPIO_DevBeforeSuspend();
	}
    GPIO_DevSuspend();

    drv_data->is_suspended = 1;
    printk("GPIO - suspend(%d) OK\n", sel_before);
#endif
	return 0;
}

/* for instant boot */
static int GPIO_suspend(struct device *dev)
{
	return __GPIO_suspend(dev, 1);
}

/* for cold booting snapshot */
static int GPIO_suspend_else(struct device *dev)
{
	return __GPIO_suspend(dev, 0);
}

#else

static int __GPIO_suspend(struct platform_device *pdev, pm_message_t state,
						int sel_before)
{
#ifdef KDRV_CONFIG_PM_GPIO
    GPIO_DRVDATA_T  *drv_data;

    printk("GPIO - suspend(%d) BEGIN\n", sel_before);
    drv_data = platform_get_drvdata(pdev);

	if (sel_before) {
		GPIO_DevBeforeSuspend();
	}
    GPIO_DevSuspend();

    drv_data->is_suspended = 1;
    printk("GPIO - suspend(%d) OK\n", sel_before);
#endif

    return 0;
}

/* for instant boot */
static int GPIO_suspend(struct platform_device *pdev, pm_message_t state)
{
	return __GPIO_suspend(pdev, state, 1);
}

/* for cold booting snapshot */
static int GPIO_suspend_else(struct platform_device *pdev, pm_message_t state)
{
	return __GPIO_suspend(pdev, state, 0);
}
#endif


/**
 *
 * resuming module.
 *
 * @param   struct platform_device *
 * @return  int 0 : OK , -1 : NOT OK
 *
 */



 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))

static int GPIO_resume(struct device *dev)
{
#ifdef KDRV_CONFIG_PM_GPIO
    GPIO_DRVDATA_T  *drv_data;
	struct platform_device *pdev = to_platform_device(dev);

    printk("GPIO - resume BEGIN [160820]\n");

    drv_data = platform_get_drvdata(pdev);
    if(drv_data->is_suspended == 0)
    {
        printk("GPIO - resume FAIL\n");
        return -1;
    }

    GPIO_DevResume();

    drv_data->is_suspended = 0;
    printk("GPIO - resume OK\n");
#endif
    return 0;
}

#else
static int GPIO_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_GPIO
    GPIO_DRVDATA_T  *drv_data;

    printk("GPIO - resume BEGIN\n");

    drv_data = platform_get_drvdata(pdev);
    if(drv_data->is_suspended == 0)
    {
        printk("GPIO - resume FAIL\n");
        return -1;
    }

    GPIO_DevResume();

    drv_data->is_suspended = 0;
    printk("GPIO - resume OK\n");
#endif
    return 0;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))
#ifdef KDRV_CONFIG_PM_GPIO

	#ifdef CONFIG_PM_SLEEP
/*
 * suspend_late, resume_early : for instant boot
 * else : for cold booting snapshot
 */
	#define SET_LATE_SYSTEM_SLEEP_PM_OPS_GPIO(suspend_fn, resume_fn,	\
										suspend_fn_else, resume_fn_else) \
	.suspend_late = suspend_fn, \
	.resume_early = resume_fn, \
	.freeze_late = suspend_fn_else, \
	.thaw_early = resume_fn_else, \
	.poweroff_late = suspend_fn_else, \
	.restore_early = resume_fn_else,
	#else
		#define SET_LATE_SYSTEM_SLEEP_PM_OPS_GPIO(suspend_fn, resume_fn, suspend_fn_else, resume_fn_else)
	#endif

static struct dev_pm_ops pm_ops = {
       SET_LATE_SYSTEM_SLEEP_PM_OPS_GPIO(GPIO_suspend, GPIO_resume,
       							GPIO_suspend_else, GPIO_resume)
};
#endif
#endif
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
 int  GPIO_probe(struct platform_device *pdev)
{

	GPIO_DRVDATA_T *drv_data;

	drv_data = (GPIO_DRVDATA_T *)vmalloc(sizeof(GPIO_DRVDATA_T));

	// add here driver registering code & allocating resource code

	GPIO_NOTI("[%s] done probe\n", GPIO_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod gpio module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
static void  GPIO_remove(struct platform_device *pdev)
#else
static int  GPIO_remove(struct platform_device *pdev)
#endif
{
	GPIO_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	GPIO_NOTI("released\n");

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
#else
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
static void  GPIO_release(struct device *dev)
{
	GPIO_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,16,0))

static struct platform_driver gpio_driver =
{
	.probe		= GPIO_probe,
	.remove		= GPIO_remove,

	/* suspend move late suspend */
	/* resume  move ealry resume */
	.driver		=
	{
		.name	= GPIO_MODULE,
		.pm = &pm_ops,
	},
};

#else
static struct platform_driver gpio_driver =
{
	.probe		= GPIO_probe,
	.remove		= GPIO_remove,

	.suspend		= GPIO_suspend,
	.resume		= GPIO_resume,
	.driver		=
	{
		.name	= GPIO_MODULE,
	},
};
#endif




static struct platform_device gpio_device = {
	.name = GPIO_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = GPIO_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void GPIO_PreInit(void)
{
	GPIO_CFG_Init();
}

int GPIO_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for gpio device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_gpio_debug_fd = DBG_OPEN( GPIO_MODULE );
	if(g_gpio_debug_fd < 0) return -1;


	OS_DEBUG_EnableModule ( g_gpio_debug_fd );

#if 0
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, GPIO_MSG_TRACE, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, GPIO_MSG_TRACE, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, GPIO_MSG_DEBUG, DBG_COLOR_NONE );
#endif
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, GPIO_MSG_ERROR, DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, GPIO_MSG_NOTI, DBG_COLOR_NONE );

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&gpio_driver) < 0)
	{
		GPIO_NOTI("[%s] platform driver register failed\n",GPIO_MODULE);
	}
	else
	{
		if(platform_device_register(&gpio_device))
		{
			platform_driver_unregister(&gpio_driver);
			GPIO_NOTI("[%s] platform device register failed\n",GPIO_MODULE);
		}
		else
		{
			GPIO_NOTI("[%s] platform register done\n", GPIO_MODULE);
		}
	}
#endif

	GPIO_DevInit();

	g_gpio_device = (GPIO_DEVICE_T*)OS_KMalloc( sizeof(GPIO_DEVICE_T)*GPIO_MAX_DEVICE );

	if ( NULL == g_gpio_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(GPIO_DEVICE_T)* GPIO_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_gpio_device, 0x0, sizeof(GPIO_DEVICE_T)* GPIO_MAX_DEVICE );

	if (g_gpio_major)
	{
		dev = MKDEV( g_gpio_major, g_gpio_minor );
		err = register_chrdev_region(dev, GPIO_MAX_DEVICE, GPIO_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_gpio_minor, GPIO_MAX_DEVICE, GPIO_MODULE );
		g_gpio_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register gpio device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<GPIO_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_gpio_major, g_gpio_minor+i );
		cdev_init( &(g_gpio_device[i].cdev), &g_gpio_fops );
		g_gpio_device[i].devno		= dev;
		g_gpio_device[i].cdev.owner = THIS_MODULE;
		g_gpio_device[i].cdev.ops   = &g_gpio_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_gpio_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding gpio device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_gpio_device[i].devno, "%s%d", GPIO_MODULE, i );
	}

	if(0)
	{}
	#ifdef INCLUDE_O26_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O26)
	{
	}
	#endif
	#ifdef INCLUDE_O24_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O24)
	{
	}
	#endif
	#ifdef INCLUDE_M23_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M23)
	{
	}
	#endif
	#ifdef INCLUDE_O22_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O22)
	{
	}
	#endif
	#ifdef INCLUDE_E60_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_E60)
	{
	}
	#endif
	#ifdef INCLUDE_O20_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O20)
	{
	}
	#endif
	#ifdef INCLUDE_L18_CHIP_KDRV
	else if(lx_chip_rev() >= LX_CHIP_REV(L18, A0))
	{
			gpio_intr_num =  gpio_intr_num_l18;
	}
	#endif
	#ifdef INCLUDE_M17_CHIP_KDRV
	else if(lx_chip_rev() >= LX_CHIP_REV(M17, A0))
	{
			gpio_intr_num =  gpio_intr_num_m17;
	}
	#endif
	else
	{
		GPIO_ERROR("<<< %s : LX_CHIP_REV => Unknown(0x%X)\n", __F__, lx_chip_rev());
	}

	#ifndef  USE_KERNEL_INTR
	for( i= 0; i < GPIO_IRQ_NUM_NR; i++)
	{
		//Initialize IRQ0 of ADEC DSP0
		err = request_irq(gpio_intr_num[i], (irq_handler_t)GPIO_interrupt, 0, gpio_intr_num_str[i], NULL);
		if (err)
		{
			DBG_PRINT_ERROR("request_irq IRQ_AUD0 in %s is failed %d\n", "GPIO0 ", err);
			return -1;
		}

	}
	#endif

	/* initialize proc system */
	GPIO_PROC_Init ( );

	GPIO_NOTI("gpio device initialized[160725\n");

	return 0;
}

void GPIO_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_gpio_major, g_gpio_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&gpio_driver);
	platform_device_unregister(&gpio_device);
#endif

	/* cleanup proc system */
	GPIO_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<GPIO_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_gpio_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, GPIO_MAX_DEVICE );

	OS_Free( g_gpio_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for gpio device
 *
 */
static int GPIO_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    GPIO_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, GPIO_DEVICE_T, cdev);

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
    GPIO_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for gpio device
 *
 */
static int GPIO_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    GPIO_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, GPIO_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    GPIO_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}



/**
 * ioctl handler for gpio device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long GPIO_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	GPIO_DEVICE_T*	gpio_dev;
	LX_GPIO_PARAM_T param;
	#ifndef  USE_KERNEL_INTR
	LX_GPIO_INFO_T  infok, * pinfou;
	unsigned int intnum = 0;
	#endif
	int err = 0, ret = 0;

	/*
	 * get current gpio device object
	 */
	gpio_dev = (GPIO_DEVICE_T*)file->private_data;

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != GPIO_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > GPIO_IOC_MAXNR)
    {
    	DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
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
    	DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
    													_IOC_NR(cmd),
    													(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
    													(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
    													(void*)arg );
        return -EFAULT;
	}

	GPIO_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case GPIO_IOW_COMMAND_SET:
		{
			GPIO_TRACE("GPIO_IOW_COMMAND_SET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevSetPinMux(param.pin_number, (BOOLEAN)param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevSetMode(param.pin_number, (LX_GPIO_MODE_T)param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevSetValue(param.pin_number, (LX_GPIO_VALUE_T)param.data);
					if( debugpin != 0 && debugpin == param.pin_number)
						GPIO_NOTI("SET[%d] PINVAL[%u]\n", debugpin,param.data);
					break;
	#ifndef  USE_KERNEL_INTR
				case LX_GPIO_COMMAND_ISR:

						pinfou = param.info;
						GPIO_COPY_FROM_USER(&infok,(void __user *)pinfou,sizeof(LX_GPIO_INFO_T));

						if(param.pin_number > 0 && param.pin_number  < GPIO_PIN_MAX)
						{
							intnum = param.pin_number/GPIO_NUM_IN_INT_ARRAY;
							if(intnum >= INT_ARRAY_NUM)
								intnum = INT_ARRAY_NUM - 1;

							if(gpio_intr_num[intnum] != 0 )
							{
								//Initialize IRQ of gpio pin
								err = request_irq(gpio_intr_num[intnum], (irq_handler_t)GPIO_interrupt, IRQF_SHARED, gpio_intr_num_str[intnum], &(gpio_dev->devno));
								if (err)
								{
									GPIO_NOTI("request_irq  gpio pin in %s is failed %d\n", "GPIO ", err);
									return -1;
								}
								else
								{
									/* mark the success of gpio isr registeration */
									gpio_intr_num[param.pin_number/GPIO_NUM_IN_INT_ARRAY] = 0;
								}
							}
						}
						ret = GPIO_DevSetPinMux(param.pin_number, (BOOLEAN)param.data);
						ret = GPIO_DevSetISR(param.pin_number, param.cb.pfnGPIO_CB, param.intr_enable,&infok);
						GPIO_COPY_TO_USER((void __user *)pinfou, (void*)&infok,sizeof(LX_GPIO_INFO_T));

					break;
				case LX_GPIO_COMMAND_INTR_ARRAY_NUM:

						ret = GPIO_DevSetIntrArrayNum(param.data);
					break;
	#endif

				default: GPIO_ERROR("GPIO_IOW_COMMAND_SET: unknown\n"); return -EFAULT;
			}
			break;
		}

		case GPIO_IORW_COMMAND_GET:
		{
			GPIO_TRACE("GPIO_IORW_COMMAND_GET\n");

			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevGetPinMux(param.pin_number, (BOOLEAN*)&param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevGetMode(param.pin_number, (LX_GPIO_MODE_T*)&param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevGetValue(param.pin_number, (LX_GPIO_VALUE_T*)&param.data);
					if( debugpin != 0 && debugpin == param.pin_number)
						GPIO_NOTI("GET[%d]PINVAL[%u]\n", debugpin,param.data);
					break;
	#ifndef  USE_KERNEL_INTR
				case LX_GPIO_COMMAND_INTR_VALUE:
					ret = GPIO_DevGetIntrValue((UINT32*)&param.pin_number, (LX_GPIO_VALUE_T*)&param.pin_value);
					break;
				case LX_GPIO_COMMAND_INTR_COUNT:
					pinfou = param.info;
					GPIO_COPY_FROM_USER(&infok,(void __user *)pinfou,sizeof(LX_GPIO_INFO_T));
					if(param.pin_number > 0 && param.pin_number  < GPIO_PIN_MAX)
					{
						intnum = param.pin_number/GPIO_NUM_IN_INT_ARRAY;
						if(intnum >= INT_ARRAY_NUM)
							intnum = INT_ARRAY_NUM - 1;

						if(gpio_intr_num[intnum] != 0 )
						{
							//Initialize IRQ of gpio pin
							err = request_irq(gpio_intr_num[intnum], (irq_handler_t)GPIO_interrupt, IRQF_SHARED, gpio_intr_num_str[intnum], &(gpio_dev->devno));
							if (err)
							{
								GPIO_NOTI("request_irq  gpio pin in %s is failed %d\n", "GPIO ", err);
								return -1;
							}
							else
							{
								/* mark the success of gpio isr registeration */
								gpio_intr_num[param.pin_number/GPIO_NUM_IN_INT_ARRAY] = 0;
							}
						}
					}
					ret =GPIO_DevGetIntrCntDur(param.pin_number, param.intr_count.count ,&param.intr_count.usec);
					GPIO_COPY_TO_USER((void __user *)pinfou, (void*)&infok,sizeof(LX_GPIO_INFO_T));
					break;
	#endif

				default: GPIO_ERROR("GPIO_IORW_COMMAND_GET: unknown\n"); return -EFAULT;
			}
			GPIO_COPY_TO_USER(arg, &param, sizeof(LX_GPIO_PARAM_T));
			break;
		}

		case GPIO_IOW_EX_COMMAND_SET:
		{
			GPIO_TRACE("GPIO_IOW_EX_COMMAND_SET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevExSetPinMux(param.pin_number, (BOOLEAN)param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevExSetMode(param.pin_number, (LX_GPIO_MODE_T)param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevExSetValue(param.pin_number, (LX_GPIO_VALUE_T)param.data);
					break;
				default: GPIO_ERROR("GPIO_IOW_EX_COMMAND_SET: unknown\n"); return -EFAULT;
			}
			break;
		}

		case GPIO_IORW_EX_COMMAND_GET:
		{
			GPIO_TRACE("GPIO_IORW_EX_COMMAND_GET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevExGetPinMux(param.pin_number, (BOOLEAN*)&param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevExGetMode(param.pin_number, (LX_GPIO_MODE_T*)&param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevExGetValue(param.pin_number, (LX_GPIO_VALUE_T*)&param.data);
					break;
				default: GPIO_ERROR("GPIO_IORW_EX_COMMAND_GET: unknown\n"); return -EFAULT;
			}
			GPIO_COPY_TO_USER(arg, &param, sizeof(LX_GPIO_PARAM_T));
			break;
		}

	    default:
	    {
	    	GPIO_ERROR("ioctl: default\n");
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

#ifdef CONFIG_COMPAT
static long GPIO_CompatIoctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd)
	{
	case GPIO_IOW_COMMAND_SET:
	case GPIO_IORW_COMMAND_GET:
	case GPIO_IOW_EX_COMMAND_SET:
	case GPIO_IORW_EX_COMMAND_GET:
	{
		LX_GPIO_PARAM_T arg_buf;
		ret = copy_from_user((void *)&arg_buf, (void __user *)arg,
							 sizeof(LX_GPIO_PARAM_T));
		if (ret)
		{
			return -EINVAL;
		}

		arg_buf.info = (LX_GPIO_INFO_T *)(uintptr_t)arg_buf.compat_info;
		arg_buf.cb.pfnGPIO_CB =
			(void (*)(UINT32))(uintptr_t)arg_buf.cb.compat_pfnGPIO_CB;

		ret = copy_to_user((void __user *)arg, (void *)&arg_buf,
						   sizeof(LX_GPIO_PARAM_T));
		if (ret)
		{
			return -EINVAL;
		}

		break;
	}
	default:
		break;
	}

	ret = GPIO_Ioctl(file, cmd, arg);

	return ret;
}
#endif

static unsigned int GPIO_Poll(struct file *filp, poll_table *wait)
{
	int i = 0, founded =0;
	UINT32 pollcontext = 0;

	for( i = 0 ; i < INT_ARRAY_NUM ; i++)
	{
		pollcontext = gpio_pollarray_context[i] & 0xffff;
		if ( gpio_intrarray_used[i] > 0 &&  ((gpio_pollarray_context[i] >> 16) == 0))
		{
			GPIO_DEBUG("#  [%8x][%8x] pollarray_context[%x]=[%8x] \n",gpio_intrarray_used[i],pollcontext,i,gpio_pollarray_context[i]);
			poll_wait(filp, gGPIOPollWaitQueueT[i], wait);
			gpio_pollarray_context[i] |=  1 << 16;
			founded = 1;
		}
	}

	if( founded == 0)
	{
		pollcontext = gpio_pollarray_context[g_poll_intr_idx] & 0xffff;
			GPIO_DEBUG("## [%8x][%8x] pollarray_context[%x]=[%8x]\n",gpio_intrarray_used[g_poll_intr_idx],pollcontext,g_poll_intr_idx, gpio_pollarray_context[g_poll_intr_idx]);
			poll_wait(filp, gGPIOPollWaitQueueT[g_poll_intr_idx], wait);
	}

	//Set a audio GET event type for next event.
	if (gpio_intr_pin != 0)
	{
	 	return POLLIN;
	}
	else
	   	return 0;
}


irqreturn_t GPIO_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	#if defined(INCLUDE_M17_CHIP_KDRV) || defined(INCLUDE_O18_CHIP_KDRV) || defined(INCLUDE_L18_CHIP_KDRV)
	unsigned int intr_data = 0;
	#endif

	if(0)
	{}
	#ifdef INCLUDE_O26_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O26)
	{
	}
	#endif
	#ifdef INCLUDE_O24_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O24)
	{
	}
	#endif
	#ifdef INCLUDE_M23_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M23)
	{
	}
	#endif
	#ifdef INCLUDE_O22_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O22)
	{
	}
	#endif
	#ifdef INCLUDE_E60_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_E60)
	{
	}
	#endif
	#ifdef INCLUDE_O20_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O20)
	{
	}
	#endif
	#ifdef INCLUDE_M19_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M19)
	{
	}
	#endif
	#ifdef INCLUDE_O18_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_O18)
	{
		if(*((dev_t *)dev_id) == g_gpio_device[0].devno)
			_GPIO_ISR_GPIO_O18(irq,intr_data );
	}
	#endif
	#ifdef INCLUDE_L18_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_L18)
	{
		if(*((dev_t *)dev_id) == g_gpio_device[0].devno)
			_GPIO_ISR_GPIO_L18(irq,intr_data );
	}
	#endif
	#ifdef INCLUDE_M17_CHIP_KDRV
	else if(lx_chip() == LX_CHIP_M17)
	{
		if(*((dev_t *)dev_id) == g_gpio_device[0].devno)
			_GPIO_ISR_GPIO_M17(irq,intr_data );
	}
	#endif
	else
	{
		GPIO_ERROR("<<< %s : LX_CHIP_REV => Unknown(0x%X)\n", __F__, lx_chip_rev());
	}

	return IRQ_HANDLED;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",GPIO_Init);
#else
module_init(GPIO_Init);
#endif
module_exit(GPIO_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("gpio driver");
MODULE_LICENSE("GPL");



#endif

/** @} */

