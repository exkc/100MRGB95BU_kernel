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
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2012.04.16
 *  note		Additional information.
 *
 *  @addtogroup lg115x_hdmi20
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_HDMI20_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/dma-mapping.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#if defined(CONFIG_ARM64) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0)
#include <linux/of_device.h>
#endif
#include "os_util.h"
#include "base_device.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
#endif

#include "hdmi20_cfg.h"
#include "hdmi20_drv.h"
#include "hdmi20_module.h"

#include "./v4l2_hdmi20/v4l2_hdmi20.h"
#include "./v4l2_earc/v4l2_earc.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	main control block for hdmi20 device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;		    	///< device number
	struct cdev				cdev;			    ///< char device structure
	int						dev_initialized;	///< check if device is initialized or not
}
HDMI20_DEVICE_T;

#ifdef KDRV_CONFIG_PM
typedef struct
{
	bool	is_suspended;
}HDMI20_DRVDATA_T;
#endif

static char print_buf[128];

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void hdmi20_thread_print(struct tasklet_struct *t);
DECLARE_TASKLET(hdmi20_isr2tasklet_print, hdmi20_thread_print);
#else
void hdmi20_thread_print(unsigned long data);
DECLARE_TASKLET(hdmi20_isr2tasklet_print, hdmi20_thread_print, (unsigned long)print_buf);
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	HDMI20_PROC_Init(void);
extern	void	HDMI20_PROC_Cleanup(void);

extern int v4l2_hdmi20_device_init(void);
extern int v4l2_earc_device_init(void);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		HDMI20_Init(void);
void	HDMI20_Cleanup(void);

dma_addr_t gEsm_Dma_codebase = 0xFFFFFFFF;
dma_addr_t gEsm_Dma_database = 0xFFFFFFFF;

UINT8 *pEsm_codeVirtAddr = NULL;
UINT8 *pEsm_dataVirtAddr = NULL;


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_hdmi20_debug_fd;
int 	g_hdmi20_major = HDMI20_MAJOR;
int 	g_hdmi20_minor = HDMI20_MINOR;
bool 	g_hdmi20_open_done = false;

int		g_hdmi20_number_of_ports = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      HDMI20_Open(struct inode *, struct file *);
static int      HDMI20_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int 		HDMI20_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long     HDMI20_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long     HDMI20_CompatIoctl (struct file * filp, unsigned int cmd, unsigned long arg);
#endif
#endif
#ifdef SUPPORT_HDMI20_DEVICE_READ_WRITE_FOPS
static ssize_t  HDMI20_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  HDMI20_Write(struct file *, const char *, size_t, loff_t *);
#endif

static int __HDMI20_SetLogmPrint(unsigned long arg, int isInternal);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for hdmi20 device
*/
HDMI20_DEVICE_T*		g_hdmi20_device;

/**
 * file I/O description for hdmi20 device
 *
*/
static struct file_operations g_hdmi20_fops =
{
	.open 	= HDMI20_Open,
	.release= HDMI20_Close,
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= HDMI20_Ioctl,
	#else
	.unlocked_ioctl	= HDMI20_Ioctl,
	#ifdef CONFIG_COMPAT
	.compat_ioctl	= HDMI20_CompatIoctl,
	#endif
	#endif
	#ifdef SUPPORT_HDMI20_DEVICE_READ_WRITE_FOPS
	.read 	= HDMI20_Read,
	.write 	= HDMI20_Write,
	#else
	.read	= NULL,
	.write	= NULL,
	#endif
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
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int HDMI20_suspend(struct platform_device *pdev, pm_message_t state)
{
	int ret = RET_OK;
#ifdef KDRV_CONFIG_PM_HDMI20
	HDMI20_DRVDATA_T *drv_data;

	printk("HDMI20 - suspend BEGIN\n");

	if(g_hdmi20_open_done == false)
	{
		printk("HDMI20 - suspend ignore\n");
		return 0;
	}

	drv_data = platform_get_drvdata(pdev);
	// add here the suspend code
	ret = HDMI20_Module_Suspend();

	drv_data->is_suspended = 1;
	printk("HDMI20 - suspend OK\n");
#endif
	return ret;
}


/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int HDMI20_resume(struct platform_device *pdev)
{
	int ret = RET_OK;
#ifdef KDRV_CONFIG_PM_HDMI20
	HDMI20_DRVDATA_T *drv_data;

	printk("HDMI20 - resume BEGIN\n");

	if(g_hdmi20_open_done == false)
	{
		printk("HDMI20 - resume ignore\n");
		return 0;
	}
	
	drv_data = platform_get_drvdata(pdev);
	if(drv_data->is_suspended == 0){
		printk("HDMI20 - resume FAIL\n");
		return -1;
	}

	ret = HDMI20_Module_Resume();

	drv_data->is_suspended = 0;

	printk("HDMI20 - resume OK\n");
#endif
	return ret;
}

/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
 int  HDMI20_probe(struct platform_device *pdev)
{
	HDMI20_DRVDATA_T *drv_data;

	drv_data = (HDMI20_DRVDATA_T *)kmalloc(sizeof(HDMI20_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code


	HDMI20_INFO("[%s] done probe\n", HDMI20_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void  HDMI20_remove(struct platform_device *pdev)
#else
static int  HDMI20_remove(struct platform_device *pdev)
#endif
{
	HDMI20_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	HDMI20_INFO("released\n");

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
static void  HDMI20_release(struct device *dev)
{
	HDMI20_INFO("device released\n");
}

/*
 *	module platform driver structure
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static struct platform_driver hdmi20_driver =
#else
static struct platform_driver hdmi20_driver __refdata =
#endif
{
	.probe          = HDMI20_probe,
	.suspend        = HDMI20_suspend,
	.remove         = HDMI20_remove,
	.resume         = HDMI20_resume,
	.driver         =
	{
		.name   = HDMI20_MODULE,
	},
};

struct platform_device hdmi20_device = {
	.name = HDMI20_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = HDMI20_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void HDMI20_PreInit(void)
{
	HDMI20_InitCfg( );
    
	/* TODO: do something */
	HDMI20_Module_PreInit();
}

int HDMI20_Init(void)
{
	int 		ret;
	int			i;
	int			err;
	dev_t		dev;
	int 		__attribute__((unused)) esm_code_size;

	HDMI20_INFO("%s entered \n" , __func__);

	/* Get the handle of debug output for hdmi20 device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_hdmi20_debug_fd = DBG_OPEN( HDMI20_MODULE );
	if( g_hdmi20_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_hdmi20_debug_fd );

	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_NOTI, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_ERROR );	// ERR
	//OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_INFO, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_NONE );
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+0 );	// AUDIO
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+1 );	// SWWA
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+2 );	// VIDEO
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+3 );	// PACKET
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+4 );	// LINK PACKET
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+5 );	// INTR
	//OS_DEBUG_EnableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+6,DBG_COLOR_NONE );	// PHY
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+6 );	// PHY
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+7 );	// SNPS
	OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+8 );	// SNPS ERR

	
	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+9, DBG_COLOR_NONE );	//CEC INFO
//	OS_DEBUG_EnableModuleByIndex ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+10 , DBG_COLOR_NONE);	// CEC DEBUG
	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+11, DBG_COLOR_NONE );	//CEC ERROR
	OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, LX_LOGM_LEVEL_TRACE+12, DBG_COLOR_NONE );	// ADEF => Audio Default ON Print
	
	ret = HDMI20_Module_InitChipRev();
	if(ret != RET_OK){
		HDMI20_ERROR(" Warning! HDMI20 chip initiation failed[%d]\n", ret);
	}

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
	#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&hdmi20_driver) < 0)
	{
		HDMI20_ERROR("[%s] platform driver register failed\n",HDMI20_MODULE);
	}
	else
	{
		if(platform_device_register(&hdmi20_device))
		{
			platform_driver_unregister(&hdmi20_driver);
			HDMI20_ERROR("[%s] platform device register failed\n",HDMI20_MODULE);
		}
		else
		{
			HDMI20_INFO("[%s] platform register done\n", HDMI20_MODULE);
		}
	}
	#endif

	g_hdmi20_device = (HDMI20_DEVICE_T*)OS_KMalloc( sizeof(HDMI20_DEVICE_T)*HDMI20_MAX_DEVICE );

	if ( NULL == g_hdmi20_device )
	{
		HDMI20_ERROR("out of memory. can't allocate [%zu] bytes\n", sizeof(HDMI20_DEVICE_T)* HDMI20_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_hdmi20_device, 0x0, sizeof(HDMI20_DEVICE_T)* HDMI20_MAX_DEVICE );

	/* ESM Code mem DMA Alloc */
	#if defined(CONFIG_ARM64) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0)
	hdmi20_device.dev.coherent_dma_mask = DMA_BIT_MASK(32);
	#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,18,0)
	of_dma_configure(&hdmi20_device.dev, hdmi20_device.dev.of_node, true);
	#else
	of_dma_configure(&hdmi20_device.dev, hdmi20_device.dev.of_node);
	#endif

	/* If device memory is allocated in platform_init */
	if(gpEsmCodeMem->base && gpEsmDataMem->base )
	{
		HDMI20_INFO("ESM_CODE name: %s, base: 0x%x, size: 0x%x",gpEsmCodeMem->name, gpEsmCodeMem->base, gpEsmCodeMem->size);
		HDMI20_INFO("ESM_DATA name: %s, base: 0x%x, size: 0x%x",gpEsmDataMem->name, gpEsmDataMem->base, gpEsmDataMem->size);

		gEsm_Dma_codebase = gpEsmCodeMem->base;
		gEsm_Dma_database = gpEsmDataMem->base;

		pEsm_codeVirtAddr = (UINT8 *)vmap_phys(gpEsmCodeMem->base, gpEsmCodeMem->size);
		pEsm_dataVirtAddr = (UINT8 *)vmap_phys(gpEsmDataMem->base, gpEsmDataMem->size);
	}
	else {
		pEsm_codeVirtAddr = dma_alloc_coherent(&hdmi20_device.dev, gpEsmCodeMem->size, &gEsm_Dma_codebase, GFP_KERNEL);
		pEsm_dataVirtAddr = dma_alloc_coherent(&hdmi20_device.dev, gpEsmDataMem->size, &gEsm_Dma_database, GFP_KERNEL);
	#else
		of_dma_configure(&hdmi20_device.dev, hdmi20_device.dev.of_node);

		pEsm_codeVirtAddr = dma_alloc_coherent(0, gpEsmCodeMem->size, &gEsm_Dma_codebase, GFP_KERNEL);
		pEsm_dataVirtAddr = dma_alloc_coherent(0, gpEsmDataMem->size, &gEsm_Dma_database, GFP_KERNEL);
	#endif
	}

	if(pEsm_codeVirtAddr != NULL) {
		HDMI20_PRINT("hdmi20 device successfully dma allocated ESM code memory!\n");
	}
	else {
		HDMI20_PRINT("hdmi20 device failed to dma allocated ESM code memory!\n");
	}
	
	if(pEsm_dataVirtAddr != NULL) {
		HDMI20_PRINT("hdmi20 device successfully dma allocated ESM data memory!\n");
	}
	else {
		HDMI20_PRINT("hdmi20 device failed to dma allocated ESM data memory!\n");
	}


	if (g_hdmi20_major)
	{
		dev = MKDEV( g_hdmi20_major, g_hdmi20_minor );
		err = register_chrdev_region(dev, HDMI20_MAX_DEVICE, HDMI20_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_hdmi20_minor, HDMI20_MAX_DEVICE, HDMI20_MODULE );
		g_hdmi20_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		HDMI20_ERROR("can't register hdmi20 device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<HDMI20_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_hdmi20_major, g_hdmi20_minor+i );
		cdev_init( &(g_hdmi20_device[i].cdev), &g_hdmi20_fops );
		g_hdmi20_device[i].devno		= dev;
		g_hdmi20_device[i].cdev.owner = THIS_MODULE;
		g_hdmi20_device[i].cdev.ops   = &g_hdmi20_fops;

		/* TODO: initialize minor device */

		/* END */

		err = cdev_add (&(g_hdmi20_device[i].cdev), dev, 1 );

		if (err)
		{
			HDMI20_ERROR("error (%d) while adding hdmi20 device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_hdmi20_device[i].devno, "%s%d", HDMI20_MODULE, i );
	}

	/* initialize proc system */
	HDMI20_PROC_Init();

	HDMI20_PRINT("hdmi20 device initialized\n");

	/* V4L2 Test Only */
	v4l2_hdmi20_device_init();
	v4l2_earc_device_init();




	return 0;
}

void HDMI20_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_hdmi20_major, g_hdmi20_minor );

	if(gpEsmCodeMem->base && gpEsmDataMem->base )
	{
		if(pEsm_codeVirtAddr)
			vunmap_phys(pEsm_codeVirtAddr);
		if(pEsm_dataVirtAddr)
			vunmap_phys(pEsm_dataVirtAddr);
	}
	else	
	{
		#if defined(CONFIG_ARM64) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 0)
		dma_free_coherent(&hdmi20_device.dev, gpEsmCodeMem->size, pEsm_codeVirtAddr, gEsm_Dma_codebase);
		dma_free_coherent(&hdmi20_device.dev, gpEsmDataMem->size, pEsm_dataVirtAddr, gEsm_Dma_database);
		#else
		dma_free_coherent(0, gpEsmCodeMem->size, pEsm_codeVirtAddr, gEsm_Dma_codebase);
		dma_free_coherent(0, gpEsmDataMem->size, pEsm_dataVirtAddr, gEsm_Dma_database);
		#endif
	}

	#ifdef KDRV_CONFIG_PM
	platform_driver_unregister(&hdmi20_driver);
	platform_device_unregister(&hdmi20_device);
	#endif

	/* cleanup proc system */
	HDMI20_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<HDMI20_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */

		/* END */
		cdev_del( &(g_hdmi20_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, HDMI20_MAX_DEVICE );
	OS_Free( g_hdmi20_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * open handler for hdmi20 device
 *
 */
static int HDMI20_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
	struct cdev*    	cdev;
    HDMI20_DEVICE_T*	    my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, HDMI20_DEVICE_T, cdev);

	HDMI20_INFO("%s entered \n" , __func__);

    /* TODO : add your device specific code */

	/* END */
	g_hdmi20_open_done = true;

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    HDMI20_INFO("device opened (%d:%d)\n", major, minor );

    return 0;
}


/**
 * release handler for hdmi20 device
 *
 */
static int HDMI20_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    HDMI20_DEVICE_T*   	my_dev;
    struct cdev*		cdev;

	HDMI20_INFO("%s entered \n" , __func__);
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, HDMI20_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    HDMI20_INFO("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for hdmi20 device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int HDMI20_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long HDMI20_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
#endif
{
    int err = 0, ret = RET_OK;

    HDMI20_DEVICE_T*	    my_dev;
    struct cdev*		cdev;
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	#else
	struct inode *inode = filp->f_path.dentry->d_inode;
	#endif

	LX_HDMI20_CMD_T hdmi20_msg;

	cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, HDMI20_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if ((_IOC_TYPE(cmd)) != HDMI20_IOC_MAGIC)
    {
    	HDMI20_ERROR("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if ((_IOC_NR(cmd)) > (HDMI20_IOC_MAXNR))
    {
    	HDMI20_ERROR("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
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
    	HDMI20_ERROR("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
    													_IOC_NR(cmd),
    													(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
    													(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
    													(void*)arg );
        return -EFAULT;
	}

	switch(cmd)
	{
 		case HDMI20_IOC_COMMAND:
		{
			/* Step 1. Copy data from user */
			ret = copy_from_user(&hdmi20_msg, (LX_HDMI20_CMD_T *)arg, sizeof(LX_HDMI20_CMD_T));
			if(ret) {
				HDMI20_ERROR("[%s:%d] Error during copying from user\n", __F__, __L__);
				ret = RET_ERROR;
				break;
			}

			/* Step 2. Process cmd */
			ret = HDMI20_Module_Process_Cmd(&hdmi20_msg);

			if(ret < 0){
				HDMI20_ERROR("[%s:%d] Error during CMD process. Ret = [%d]\n", __F__, __L__, ret);
				hdmi20_msg.status = HDMI20_CMD_STATUS_PROCESS_ERROR;
			}

			/* Step 3. Copy data to user */
			ret = copy_to_user((void __user *)arg, &hdmi20_msg, sizeof(LX_HDMI20_CMD_T));
			if(ret) {
				HDMI20_ERROR("[%s:%d] Error during copying to user\n", __F__, __L__);
				ret = RET_ERROR;
				break;
			}

			/* Step 4. End */
			ret = RET_OK;
		}
		break;

		case HDMI20_IOC_SET_LOGM:
		{
			ret = __HDMI20_SetLogmPrint(arg, 0);
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
static long HDMI20_CompatIoctl(struct file *filp, unsigned int cmd,
							   unsigned long arg)
{
	long ret;

	switch (cmd)
	{
	case HDMI20_IOC_COMMAND:
	{
		LX_HDMI20_CMD_T arg_buf;

		ret = copy_from_user(&arg_buf, compat_ptr(arg), sizeof(LX_HDMI20_CMD_T));
		if (ret)
		{
			return -EINVAL;
		}

		arg_buf.handle = (void *)(uintptr_t)arg_buf.compat_handle;

		ret = copy_to_user(compat_ptr(arg), &arg_buf, sizeof(LX_HDMI20_CMD_T));
		if (ret)
		{
			return -EINVAL;
		}

		break;
	}
	default:
		break;
	}

	ret = HDMI20_Ioctl(filp, cmd, arg);

	return ret;
}
#endif
#endif

static int __HDMI20_SetLogmPrint(unsigned long arg, int isInternal)
{
	int ret = RET_ERROR;
	LX_HDMI20_LOGM_SETTING_T stParams;

	do{
		/* Step 1. Copy data from application */
		if(isInternal)  {
			memcpy(&stParams, (LX_HDMI20_LOGM_SETTING_T *)arg, sizeof(LX_HDMI20_LOGM_SETTING_T));
		}
		else{
			ret = copy_from_user(&stParams, (LX_HDMI20_LOGM_SETTING_T *)arg, sizeof(LX_HDMI20_LOGM_SETTING_T));
			if (ret) break;
		}

		/* Step 2. Check validty of logLevel, whether it is in the LOGM Level*/
		if(stParams.logLevel >= LX_LOGM_LEVEL_MAX){
			HDMI20_ERROR("Unknown LOGM Level[%d]\n", stParams.logLevel);
			ret = RET_ERROR;
			break;
		}

		/* Step 3. Operate Logm Setting */
		if(stParams.onOff){
			OS_DEBUG_EnableModuleByIndex  ( g_hdmi20_debug_fd, stParams.logLevel, DBG_COLOR_NONE );
			HDMI20_INFO("HDMI20 LOGM Enabled for LogLevel[%d]\n", stParams.logLevel);
		}
		else{
			OS_DEBUG_DisableModuleByIndex ( g_hdmi20_debug_fd, stParams.logLevel);
			HDMI20_INFO("HDMI20 LOGM disabled for LogLevel[%d]\n", stParams.logLevel);
		}

		ret = RET_OK;
	} while(0);

	return ret;

}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void hdmi20_thread_print(struct tasklet_struct *t)
{
	HDMI20_INFO("%s\n", print_buf);
}
#else
void hdmi20_thread_print(unsigned long data)
{

	char *buf = (char *)data;
	HDMI20_INFO("%s\n", buf);

}
#endif

int hdmi20_isr2thread_print(const char *fmt, ...)
{
	int ret;
	va_list     		args;
	char buf[128];
	unsigned long sec, usec;
	unsigned long clock;

	clock = sched_clock();
	sec = (clock / 1000000000);
	if(sec >= 100000)
		sec %= 100000;
	usec = (clock / 1000);
	if(usec >= 1000000)
		usec %= 1000000;

	ret = sprintf(buf, "[%5lu.%6lu][ISR] ", sec, usec);
	
	va_start(args, fmt);
	ret |= vsnprintf(&buf[20], sizeof(buf)-20, fmt, args);				
	va_end(args);

	memcpy(print_buf, buf, sizeof(buf));

	tasklet_hi_schedule(&hdmi20_isr2tasklet_print);

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",HDMI20_Init);
#else
module_init(HDMI20_Init);
#endif
module_exit(HDMI20_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("HDMI20 driver");
MODULE_LICENSE("GPL");
#endif

/* @} */

