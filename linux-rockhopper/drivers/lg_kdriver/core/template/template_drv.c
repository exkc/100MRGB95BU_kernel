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
 *  main driver implementation for template device.
 *
 *  author      author
 *  version     1.0
 *  date        20xx.xx.xx
 *
 *  @addtogroup lg115x_template
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "template_impl.h"
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/irq.h>

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
static int TEMPLATE_freeze		(struct device* dev);
static int TEMPLATE_thaw			(struct device* dev);
static int TEMPLATE_restore		(struct device* dev);
static int TEMPLATE_suspend		(struct device* dev);
static int TEMPLATE_resume		(struct device* dev);

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void		TEMPLATE_PROC_Init	(void);
extern void		TEMPLATE_PROC_Cleanup	(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
int             g_template_debug_fd = -1;

int             g_template_major = 1822;
module_param_named( template_major, g_template_major, int, 0644 );

int             g_template_minor = 0;
module_param_named( template_minor, g_template_minor, int, 0644 );

int					g_template_test_param	= 0;
module_param_named( template_test_param, g_template_test_param, int, 0644 );

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static irqreturn_t TEMPLATE_ISRHandler(int irq, void *dev_id, struct pt_regs *regs);

static int	TEMPLATE_probe(struct platform_device *pdev);
static int	TEMPLATE_remove(struct platform_device *pdev);
static void TEMPLATE_release(struct device* dev);

static int	TEMPLATE_open	(struct inode* node , struct file* filp);
static int	TEMPLATE_close(struct inode* node, struct file* filp);
static int	TEMPLATE_mmap	(struct file* filp,  struct vm_area_struct *vma);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int	TEMPLATE_ioctl (struct inode* inode, struct file *filp, UINT32 cmd, ULONG arg);
#else
static long TEMPLATE_ioctl (struct file* filp, UINT32 cmd, ULONG arg );
#endif

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static TEMPLATE_DEV_CTX_T*	g_template_dev_ctx = NULL;

static struct file_operations g_template_fops =
{
	.open   = TEMPLATE_open,
	.release= TEMPLATE_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
	.ioctl  = TEMPLATE_ioctl,
#else
	.unlocked_ioctl = TEMPLATE_ioctl,
#endif
	.mmap   = TEMPLATE_mmap,
#ifdef SUPPORT_TEMPLATE_DEVICE_READ_WRITE_FOPS
	.read   = TEMPLATE_read,
	.write  = TEMPLATE_write,
#else
	.read   = NULL,
	.write  = NULL,
#endif
};

static struct dev_pm_ops template_pm_ops =
{
	.freeze		= TEMPLATE_freeze,		// SnapshotBoot suspend
	.thaw		= TEMPLATE_thaw,			// SnapshotBoot resume right after making image
	.restore	= TEMPLATE_restore,		// SnapshotBoot boot

	.suspend	= TEMPLATE_suspend,		// InstantBoot suspend
	.resume		= TEMPLATE_resume ,		// InstnatBoot resume
};

static struct platform_driver g_template_plt_driver =
{
	.probe		= TEMPLATE_probe,
	.remove		= TEMPLATE_remove,
	.driver		=
	{
		.name   = TEMPLATE_MODULE,
		.pm 	= &template_pm_ops,
	},
};

static struct platform_device g_template_plt_device =
{
	.name = TEMPLATE_MODULE,
	.id = -1,
	.dev =
	{
		.release = TEMPLATE_release,
	},
};

/*========================================================================================
    Implementation Group (IRQ)
========================================================================================*/
static irqreturn_t TEMPLATE_ISRHandler(int irq, void *dev_id, struct pt_regs *regs)
{
	return IRQ_HANDLED;
}

/*========================================================================================
    Implementation Group (Device Core)
========================================================================================*/
static int	TEMPLATE_probe(struct platform_device *pdev)
{
	TEMPLATE_DRV_DATA_T* drv_data = vmalloc(sizeof(TEMPLATE_DRV_DATA_T));
	TEMPLATE_CHECK_ERROR(drv_data==NULL, return RET_OUT_OF_MEMORY, "out of memory\n");

	printk("module (%s) - probe\n", TEMPLATE_MODULE);

	platform_set_drvdata(pdev, drv_data);
	return RET_OK;
}

static int  TEMPLATE_remove(struct platform_device *pdev)
{
	TEMPLATE_DRV_DATA_T* drv_data = platform_get_drvdata(pdev);
	TEMPLATE_CHECK_ERROR(drv_data==NULL, return RET_ERROR, "null drv_data\n");

	printk("module (%s) - remove\n", TEMPLATE_MODULE);

	vfree(drv_data);

	return RET_OK;
}

static void  TEMPLATE_release(struct device* dev)
{
	printk("module (%s) - release\n", TEMPLATE_MODULE);
}

static int	TEMPLATE_init(void)
{
	int	i;
	dev_t dev;

	printk("module (%s) - init\n", TEMPLATE_MODULE);

	/* init debug(logm) */
	g_template_debug_fd = DBG_OPEN( TEMPLATE_MODULE );
	if(g_template_debug_fd < 0) return RET_ERROR;

	OS_DEBUG_EnableModuleByIndex( g_template_debug_fd, LX_LOGM_LEVEL_ERROR,   DBG_COLOR_RED );
	OS_DEBUG_EnableModuleByIndex( g_template_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW );

	/* register module */
	TEMPLATE_CHECK_ERROR( platform_driver_register(&g_template_plt_driver) < 0, return RET_ERROR, "template platform driver regster failed\n");
	TEMPLATE_CHECK_ERROR( platform_device_register(&g_template_plt_device) != RET_OK, return RET_ERROR, "template platform device register failed\n");

    g_template_dev_ctx = (TEMPLATE_DEV_CTX_T*)vmalloc( sizeof(TEMPLATE_DEV_CTX_T)*TEMPLATE_MAX_DEVICE );
    TEMPLATE_CHECK_ERROR(g_template_dev_ctx==NULL, return RET_OUT_OF_MEMORY, "out of memory\n");
    memset( g_template_dev_ctx, 0x0, sizeof(TEMPLATE_OBJ_CTX_T)* TEMPLATE_MAX_DEVICE );

    if (g_template_major)
    {
		dev = MKDEV(g_template_major, g_template_minor);
		TEMPLATE_CHECK_ERROR( register_chrdev_region(dev, TEMPLATE_MAX_DEVICE, TEMPLATE_MODULE)<0, return RET_ERROR, "template chdev register failed\n");
    }
    else
    {
		TEMPLATE_CHECK_ERROR(alloc_chrdev_region(&dev, g_template_minor, TEMPLATE_MAX_DEVICE, TEMPLATE_MODULE)<0, return RET_ERROR, "template chdev alloc failed\n");
		g_template_major = MAJOR(dev);
    }

	/* TODO: initialize device module */
	TEMPLATE_PROC_Init();

	for(i=0; i<TEMPLATE_MAX_DEVICE; i++)
    {
		dev = MKDEV( g_template_major, g_template_minor+i);
		cdev_init( &(g_template_dev_ctx[i].cdev), &g_template_fops );
		g_template_dev_ctx[i].cdev.owner = THIS_MODULE;
		g_template_dev_ctx[i].cdev.ops = &g_template_fops;

		/* TODO: initialize each minor device */

        TEMPLATE_CHECK_ERROR( RET_OK != cdev_add (&(g_template_dev_ctx[i].cdev), dev, 1), return RET_ERROR, "can't add template device (%d.%d)\n", MAJOR(dev), MINOR(dev) );
        OS_CreateDeviceClass (dev, "%s%d", TEMPLATE_MODULE, i);
    }

	return RET_OK;
}

static void  TEMPLATE_cleanup(void)
{
	int i;
	dev_t dev = MKDEV(g_template_major, g_template_minor);

	printk("module (%s) - cleanup\n", TEMPLATE_MODULE);

	TEMPLATE_PROC_Cleanup();
	OS_DestroyDeviceClass(dev);

	platform_driver_unregister(&g_template_plt_driver);
	platform_device_unregister(&g_template_plt_device);

	for (i=0; i<TEMPLATE_MAX_DEVICE;i++)
	{
		cdev_del( &(g_template_dev_ctx[i].cdev) );
	}
    unregister_chrdev_region(dev,TEMPLATE_MAX_DEVICE);

    /* TODO : cleanup module data */

	vfree(g_template_dev_ctx);
	printk("module (%s) - cleanup done\n", TEMPLATE_MODULE);
}

/*========================================================================================
    Implementation Group (Device Handler)
========================================================================================*/
static int TEMPLATE_open(struct inode* node, struct file* filp)
{
	TEMPLATE_OBJ_CTX_T* obj_ctx;

	struct cdev* cdev = node->i_cdev;
	TEMPLATE_DEV_CTX_T* dev_ctx = container_of(cdev, TEMPLATE_DEV_CTX_T, cdev);

	printk("module (%s) - open\n", TEMPLATE_MODULE);

	/* TODO: implement code for the first open */
	if(dev_ctx->dev_open_cnt==0)
	{

	}

	dev_ctx->dev_open_cnt++;

	/* allocate object context for each open instance */
	obj_ctx = vmalloc(sizeof(TEMPLATE_OBJ_CTX_T));
	TEMPLATE_CHECK_ERROR(obj_ctx==NULL, return RET_OUT_OF_MEMORY, "out of memory\n");

	/* TODO: initialize your object context */
	obj_ctx->dev_ctx = dev_ctx;

	/* register file private data */
	filp->private_data = obj_ctx;

	return RET_OK;
}

static int TEMPLATE_close(struct inode* node, struct file *file)
{
    TEMPLATE_OBJ_CTX_T* obj_ctx;
	TEMPLATE_DEV_CTX_T* dev_ctx;

    obj_ctx = (TEMPLATE_OBJ_CTX_T*)file->private_data;
	TEMPLATE_CHECK_ERROR(obj_ctx==NULL, return RET_ERROR, "null obj_ctx\n");
	dev_ctx = obj_ctx->dev_ctx;
	TEMPLATE_CHECK_ERROR(dev_ctx==NULL, return RET_ERROR, "null dev_ctx\n");

	printk("module (%s) - close\n", TEMPLATE_MODULE);

	if(dev_ctx->dev_open_cnt>0) --dev_ctx->dev_open_cnt;

	/* TODO: add your device specific code */
	vfree(obj_ctx);

	return RET_OK;
}

static int TEMPLATE_mmap(struct file *filp,  struct vm_area_struct *vma)
{
	/* TODO: implement your own mmap */

	return RET_ERROR;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int	TEMPLATE_ioctl (struct inode* inode, struct file *filp, UINT32 cmd, ULONG arg)
#else
static long TEMPLATE_ioctl (struct file* filp, UINT32 cmd, ULONG arg )
#endif
{
	int	ret = RET_INVALID_IOCTL;
	UINT32 mem_sanity_errval = 0;
	TEMPLATE_OBJ_CTX_T* obj_ctx;
	TEMPLATE_DEV_CTX_T* dev_ctx;

    obj_ctx = (TEMPLATE_OBJ_CTX_T*)filp->private_data;
	TEMPLATE_CHECK_ERROR(obj_ctx==NULL, return RET_ERROR, "null obj_ctx\n");
	dev_ctx = obj_ctx->dev_ctx;
	TEMPLATE_CHECK_ERROR(dev_ctx==NULL, return RET_ERROR, "null dev_ctx\n");

	/* check ioctl */
	TEMPLATE_CHECK_ERROR(_IOC_TYPE(cmd) != TEMPLATE_IOC_MAGIC, return RET_INVALID_IOCTL, "invalid magic 0x%02x\n", _IOC_TYPE(cmd));
	TEMPLATE_CHECK_ERROR(_IOC_NR(cmd) > TEMPLATE_IOC_MAXNR-1, return RET_INVALID_IOCTL, "out of cmdidx %d\n", _IOC_NR(cmd));

	/* check user memory. if memory can't be accessed from kernel, return error(-EFAULT) */
	if (_IOC_DIR(cmd) & _IOC_READ)
	{
		mem_sanity_errval |= (access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd)))? 0x1:0x0;
	}
	if (_IOC_DIR(cmd) & _IOC_WRITE)
	{
		mem_sanity_errval |= (access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd)))? 0x2:0x0;
	}

	TEMPLATE_CHECK_ERROR(mem_sanity_errval, return RET_ERROR, "mem acess error. cmdidx %d, read(%c), write(%c) memptr=%p\n",
								_IOC_NR(cmd), (mem_sanity_errval&0x1)? 'x':'-', (mem_sanity_errval&0x2)? 'x':'-', (void*)arg );

	switch(cmd)
	{
		case TEMPLATE_IO_TEST_RESET:
		case TEMPLATE_IOR_TEST_READ:
		case TEMPLATE_IOW_TEST_WRITE:
		case TEMPLATE_IORW_TEST_READ_WRITE: ret = RET_OK; break;

		default: break;
	}

	return ret;
}

/*========================================================================================
    Implementation Group (suspend/resume)
========================================================================================*/
static int TEMPLATE_freeze(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int TEMPLATE_restore(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int TEMPLATE_suspend(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int TEMPLATE_thaw(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

static int TEMPLATE_resume(struct device* dev)
{
	//struct platform_deivce* plt_dev = to_platform_device(dev);
	return RET_OK;
}

#if 1
module_init(TEMPLATE_init);
module_exit(TEMPLATE_cleanup);
#else
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", TEMPLATE_init);
#else
module_init(TEMPLATE_init);
#endif
module_exit(TEMPLATE_cleanup);
#endif
#endif

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("TEMPLATE driver");
MODULE_LICENSE("GPL");

/** @} */

