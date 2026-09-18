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

/** @file
 *
 *  main driver implementation for khal_demod device.
 *
 *  author		raxis.lim
 *  version     1.0
 *  date        20xx.xx.xx
 *
 *  @addtogroup lg115x_khal_demod
 *  @{
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
#include <linux/platform_device.h>
#include <linux/vmalloc.h>
#include <linux/cdev.h>

#include "demod_impl.h"
#include "khal_proc.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
static int khal_demod_freeze		(struct device* dev);
static int khal_demod_thaw			(struct device* dev);
static int khal_demod_restore		(struct device* dev);
static int khal_demod_suspend		(struct device* dev);
static int khal_demod_resume		(struct device* dev);

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define	KHAL_DEMOD_MODULE			"khal_demod"

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
//extern void		khal_demod_proc_init	(void);
//extern void		khal_demod_proc_cleanup	(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
extern  int     g_demod_debug_fd;
int	khal_demod_test_param = 0;
module_param_named( khal_demod_test_param, khal_demod_test_param, int, 0644 );

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int	khal_demod_probe(struct platform_device *pdev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void	khal_demod_remove(struct platform_device *pdev);
#else
static int	khal_demod_remove(struct platform_device *pdev);
#endif

static void khal_demod_release(struct device* dev);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
typedef struct
{
	int	rsvd;
}
KHAL_DEMOD_DRV_DATA_T;

static struct dev_pm_ops khal_demod_pm_ops =
{
	.freeze		= khal_demod_freeze,		// SnapshotBoot suspend
	.thaw		= khal_demod_thaw,			// SnapshotBoot resume right after making image
	.restore	= khal_demod_restore,		// SnapshotBoot boot

	.suspend	= khal_demod_suspend,		// InstantBoot suspend
	.resume		= khal_demod_resume ,		// InstnatBoot resume
};

static struct platform_driver g_khal_demod_plt_driver =
{
	.probe		= khal_demod_probe,
	.remove		= khal_demod_remove,
	.driver		=
	{
		.name   = KHAL_DEMOD_MODULE,
		.pm 	= &khal_demod_pm_ops,
	},
};

static struct platform_device g_khal_demod_plt_device =
{
	.name = KHAL_DEMOD_MODULE,
	.id = -1,
	.dev =
	{
		.release = khal_demod_release,
	},
};

/*========================================================================================
    Implementation Group (Device Core)
========================================================================================*/
static int	khal_demod_probe(struct platform_device *pdev)
{
	KHAL_DEMOD_DRV_DATA_T* drv_data = vmalloc(sizeof(KHAL_DEMOD_DRV_DATA_T));
	DEMOD_CHECK_CODE(drv_data==NULL, return RET_OUT_OF_MEMORY, "out of memory\n");

	printk("module (%s) - probe\n", KHAL_DEMOD_MODULE);

	platform_set_drvdata(pdev, drv_data);
	return RET_OK;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void  khal_demod_remove(struct platform_device *pdev)
#else
static int  khal_demod_remove(struct platform_device *pdev)
#endif
{
	KHAL_DEMOD_DRV_DATA_T* drv_data = platform_get_drvdata(pdev);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	DEMOD_CHECK_CODE(drv_data==NULL, return RET_ERROR, "null drv_data\n");
#endif


	printk("module (%s) - remove\n", KHAL_DEMOD_MODULE);

	vfree(drv_data);

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
	return RET_OK;
#endif

}

static void  khal_demod_release(struct device* dev)
{
	printk("module (%s) - release\n", KHAL_DEMOD_MODULE);
}

static int	khal_demod_init(void)
{
	printk("module (%s) - init\n", KHAL_DEMOD_MODULE);

	/* register module */
	DEMOD_CHECK_CODE(platform_driver_register(&g_khal_demod_plt_driver) < 0, return RET_ERROR,
			"khal_demod platform driver regster failed\n");

	DEMOD_CHECK_CODE(platform_device_register(&g_khal_demod_plt_device) != RET_OK, return RET_ERROR,
			"khal_demod platform device register failed\n");

	khal_demod_proc_init();

	return RET_OK;
}

static void  khal_demod_cleanup(void)
{
	printk("module (%s) - cleanup\n", KHAL_DEMOD_MODULE);

	khal_demod_proc_cleanup();

	platform_driver_unregister(&g_khal_demod_plt_driver);
	platform_device_unregister(&g_khal_demod_plt_device);
}

/*========================================================================================
    Implementation Group (Device Handler)
========================================================================================*/

/*========================================================================================
    Implementation Group (suspend/resume)
========================================================================================*/
static int khal_demod_freeze(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int khal_demod_restore(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int khal_demod_suspend(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int khal_demod_thaw(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int khal_demod_resume(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

module_init(khal_demod_init);
module_exit(khal_demod_cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("khal_demod driver");
MODULE_LICENSE("GPL");

/** @} */

