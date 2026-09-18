/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  main driver implementation for lgbus device.
 *
 *  author		hwanwook.lee (hwanwook.lee@lge.com)
 *              bongrae.cho (bongrae.cho@lge.com)
 *  version		1.0
 *  date		2012.11.10
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/platform_device.h>


#include "os_util.h"
#include "base_device.h"
#include "sys_regs.h"

#include "lgbus_drv.h"
#include "lgbus_hw.h"
#include "lgbus_kapi.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/

typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}LGBUS_DRVDATA_T;


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/
extern void LGBUS_PROC_Init(void);
extern void LGBUS_PROC_Cleanup (void);

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  global Functions
  ----------------------------------------------------------------------------------------*/
int		LGBUS_Init(void);
void	LGBUS_Cleanup(void);

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
int		g_lgbus_debug_fd;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
int /*__init*/ LGBUS_probe(struct platform_device *pdev);
static int LGBUS_suspend(struct platform_device *pdev, pm_message_t state);
static int LGBUS_resume(struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void LGBUS_remove(struct platform_device *pdev);
#else
static int  LGBUS_remove(struct platform_device *pdev);
#endif
static void  LGBUS_release(struct device *dev);
/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
static char *notify_ignore
#ifdef CHIP_NAME_o22
= "GFX,CCO0,CCO1,VDO0,VDO1"
#endif
#ifdef CHIP_NAME_m23
= "GFX,CCO0,VDO0,VDO1"
#endif
#ifdef CHIP_NAME_o24
= "GFX,CCO0,CCO1,VDOIMXW0,VDOIMXW1"
#endif
#ifdef CHIP_NAME_o26
= "GFX"
#endif
;
module_param_named(lgbus_notify_ignore, notify_ignore, charp, 0644);

/*
 *	module platform driver structure
 */
static struct platform_driver lgbus_driver =
{
	.probe          = LGBUS_probe,
	.suspend        = LGBUS_suspend,
	.remove         = LGBUS_remove,
	.resume         = LGBUS_resume,
	.driver         =
	{
		.name   = LGBUS_MODULE,
	},
};

static struct platform_device lgbus_device = {
	.name = LGBUS_MODULE,
	.id = -1,
	.dev = {
		.release = LGBUS_release,
	},
};

/*========================================================================================
  Implementation Group
  ========================================================================================*/

bool LGBUS_ignore_notify(char *name, bool wr)
{
	char *p;

	if (wr)
		return false;

	p = notify_ignore;
	while (p && *p)
	{
		int len = INT_MAX;
		char *e;

		e = strpbrk(p, ",");
		if (e)
			len = e - p;

		if (!strncmp(p, name, len))
			return true;

		if (!e)
			break;

		p = e + 1;
	}

	return false;
}

/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int /*__init*/ LGBUS_probe(struct platform_device *pdev)
{
	LGBUS_DRVDATA_T *drv_data;

	drv_data = (LGBUS_DRVDATA_T *)vmalloc(sizeof(LGBUS_DRVDATA_T));

	// add here driver registering code & allocating resource code

	LGBUS_PRINT("lgbus dev probe\n");
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return RET_OK;
}

/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int LGBUS_suspend(struct platform_device *pdev, pm_message_t state)
{
#ifdef KDRV_CONFIG_PM_LGBUS
	LGBUS_DRVDATA_T *drv_data;

	printk("LGBUS - suspend BEGIN\n");

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code
	LGBUS_HW_Suspend();

	drv_data->is_suspended = 1;
	printk("LGBUS - suspend OK\n");
#endif
	return RET_OK;
}

/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int LGBUS_resume(struct platform_device *pdev)
{
#ifdef KDRV_CONFIG_PM_LGBUS
	LGBUS_DRVDATA_T *drv_data;

	printk("LGBUS - resume BEGIN\n");
	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0)
	{
		printk("LGBUS - resume FAIL\n");
	}

	// add here the resume code
	LGBUS_HW_Resume();

	drv_data->is_suspended = 0;
	printk("LGBUS - resume OK\n");
#endif
	return RET_OK;
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
static void LGBUS_remove(struct platform_device *pdev)
#else
static int  LGBUS_remove(struct platform_device *pdev)
#endif
{
	LGBUS_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	LGBUS_PRINT("lgbus dev remove\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
    // void, do nothing
#else
    return RET_OK;
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
static void  LGBUS_release(struct device *dev)
{
	LGBUS_PRINT("lgbus dev release\n");
}


void LGBUS_PreInit(void)
{
	/* TODO: */
}


int LGBUS_Init(void)
{
	int			err;

	/* Get the handle of debug output for lgbus device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_lgbus_debug_fd = DBG_OPEN(LGBUS_MODULE);

	if ( g_lgbus_debug_fd < 0 )
	{
		printk("[LGBUS] can't get debug handle\n");
	}
	else
	{
		OS_DEBUG_EnableModuleByIndex( g_lgbus_debug_fd, LX_LOGM_LEVEL_ERROR,    DBG_COLOR_RED );
		OS_DEBUG_EnableModuleByIndex( g_lgbus_debug_fd, LX_LOGM_LEVEL_WARNING,  DBG_COLOR_YELLOW );

		OS_DEBUG_EnableModuleByIndex( g_lgbus_debug_fd, LX_LOGM_LEVEL_NOTI,		DBG_COLOR_YELLOW );
		//OS_DEBUG_EnableModuleByIndex( g_lgbus_debug_fd, LGBUS_LOG_LEVEL_PRINT,	DBG_COLOR_YELLOW );//mpro_debug
	}

	/* register linux platform driver */
	err = platform_driver_register(&lgbus_driver);
	LGBUS_CHECK_CODE(err < 0, return RET_ERROR, "lgbus platform drv reg fail\n");

	err = platform_device_register(&lgbus_device);
	LGBUS_CHECK_CODE(err != RET_OK, return RET_ERROR, "lgbus platform dev reg fail\n");

	if(LGBUS_HW_Init() < 0)
	{
		LGBUS_ERROR("HAL_Init fail!\n");
	}

	LGBUS_PROC_Init();

	LGBUS_PRINT("lgbus device initialized\n");

	return 0;
}

void LGBUS_Cleanup(void)
{
	LGBUS_PROC_Cleanup();
	LGBUS_HW_Cleanup();

	platform_driver_unregister(&lgbus_driver);
	platform_device_unregister(&lgbus_device);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", LGBUS_Init);
#else
module_init(LGBUS_Init);
#endif
module_exit(LGBUS_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

