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
 *  main driver implementation for sys device.
 *	sys device will teach you how to make device driver with new platform.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *  note		Additional information.
 *
 *  @addtogroup lg1150_sys
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_SYS_DEVICE_READ_WRITE_FOPS

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
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include "os_util.h"
#include "base_device.h"
#include "sys_drv.h"
#include "reg_ctrl.h"
#include "sys_io.h"
#include "sys_diag.h"
#include "sys_regs.h"

#include "sys_bwm.h"
#include "sys_shadow.h"
#include "alp_ctrl.h"


#include "sys_log.h"
logm_define(sys, log_level_info);

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
 *	main control block for sys device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

// BEGIN of device specific data


// END of device specific data
}
SYS_DEVICE_T;


struct sys_plt_drvdata
{
#if defined(INCLUDE_M16_CHIP_KDRV)
	bool is_disp_hdmi;
#endif
};

/*----------------------------------------------------------------------------------------
	Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void SYS_PROC_Init(void);
extern void SYS_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		SYS_Init(void);
void	SYS_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int 	g_sys_major = SYS_MAJOR;
int 	g_sys_minor = SYS_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      SYS_Open(struct inode *inode, struct file *filp);
static int      SYS_Close(struct inode *inode, struct file *file);
static long     SYS_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg );
#ifdef SUPPORT_SYS_DEVICE_READ_WRITE_FOPS
static ssize_t  SYS_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  SYS_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for sys device
*/
static SYS_DEVICE_T*		g_sys_device;

/**
 * file I/O description for sys device
 *
*/
static struct file_operations g_sys_fops =
{
	.open 	= SYS_Open,
	.release= SYS_Close,
	.unlocked_ioctl	= SYS_Ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = SYS_Ioctl,
#endif
#ifdef SUPPORT_SYS_DEVICE_READ_WRITE_FOPS
	.read 	= SYS_Read,
	.write 	= SYS_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 *
 * resuming module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int _lgsoc_resume_chip_setup(struct device * dev)
{
	struct platform_device  *pdev = to_platform_device(dev);
	struct sys_plt_drvdata * drv_data;

	drv_data = (struct sys_plt_drvdata *)platform_get_drvdata(pdev);

	printk("%s\n", __func__);

#if defined(INCLUDE_O24_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_O24) {
		// TODO: +++ implement O24 +++

	}
#endif

#if defined(INCLUDE_M23_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_M23) {
		// TODO: +++ implement M23 +++

	}
#endif

#if defined(INCLUDE_O22_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_O22) {
		CTOP_CTRL_O22Ax_RdFL (BND_CTRL_BMC, bnd_bmc_r29);
		CTOP_CTRL_O22Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_r29, reg_swrst_f50m, 0);
		CTOP_CTRL_O22Ax_WrFL (BND_CTRL_BMC, bnd_bmc_r29);

		OS_UsecDelay(10);

		CTOP_CTRL_O22Ax_RdFL (BND_CTRL_BMC, videoafe10);
		CTOP_CTRL_O22Ax_Wr01 (BND_CTRL_BMC, videoafe10, reg_refpll_pdb, 1);
		CTOP_CTRL_O22Ax_WrFL (BND_CTRL_BMC, videoafe10);

		CTOP_CTRL_O22Ax_RdFL (BND_CTRL_BMC, videoafe12);
		CTOP_CTRL_O22Ax_Wr01 (BND_CTRL_BMC, videoafe12, reg_videoafe_cvbs_cksel, 1);	//default 0
		CTOP_CTRL_O22Ax_WrFL (BND_CTRL_BMC, videoafe12);
	}
#endif

#if defined(INCLUDE_O20_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_O20) {
		MIP_REG_O20Ax_RdFL(crg_bmc01);
		MIP_REG_O20Ax_Wr01(crg_bmc01, swrst_f24m, 0);
		MIP_REG_O20Ax_WrFL(crg_bmc01);
		MIP_REG_O20Ax_RdFL(crg_bmc02);
		MIP_REG_O20Ax_Wr01(crg_bmc02, swrst_f24m_bb,0);
		MIP_REG_O20Ax_WrFL(crg_bmc02);
		BMC_REG_O20Ax_RdFL(videoafe12);
		BMC_REG_O20Ax_Wr01(videoafe12, reg_videoafe_biaspdb, 1);
		BMC_REG_O20Ax_WrFL(videoafe12);
		OS_UsecDelay(10);
		BMC_REG_O20Ax_RdFL(videoafe10);
		BMC_REG_O20Ax_Wr01(videoafe10, reg_reset_n, 1);
		BMC_REG_O20Ax_WrFL(videoafe10);
		BMC_REG_O20Ax_RdFL(videoafe11);
		BMC_REG_O20Ax_Wr01(videoafe11, reg_refpll_pdb, 1);
		BMC_REG_O20Ax_WrFL(videoafe11);
		BMC_REG_O20Ax_RdFL(videoafe15);
		BMC_REG_O20Ax_Wr01(videoafe15, reg_videoafe_cvbs_cksel, 1);	//default 0
		BMC_REG_O20Ax_WrFL(videoafe15);
	}
#endif

#if defined(INCLUDE_E60_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_E60) {
		MIP_REG_E60Ax_RdFL(crg_dbb_syn_01);
		MIP_REG_E60Ax_Wr01(crg_dbb_syn_01, reg_dbb_syn__swrst_f50m, 0);
		MIP_REG_E60Ax_WrFL(crg_dbb_syn_01);
#if 0	// no swrst_f24m_bb from E60 , auto clear??
		MIP_REG_E60Ax_RdFL(crg_bmc02);
		MIP_REG_E60Ax_Wr01(crg_bmc02, swrst_f24m_bb,0);
		MIP_REG_E60Ax_WrFL(crg_bmc02);
#endif
		BMC_REG_E60Ax_RdFL(videoafe12);
		BMC_REG_E60Ax_Wr01(videoafe12, reg_dbb__videoafe_biaspdb, 1);
		BMC_REG_E60Ax_WrFL(videoafe12);
		OS_UsecDelay(10);
		BMC_REG_E60Ax_RdFL(videoafe10);
		BMC_REG_E60Ax_Wr01(videoafe10, reg_dbb__reset_n, 1);
		BMC_REG_E60Ax_WrFL(videoafe10);
		BMC_REG_E60Ax_RdFL(videoafe11);
		BMC_REG_E60Ax_Wr01(videoafe11, reg_dbb__refpll_pdb, 1);
		BMC_REG_E60Ax_WrFL(videoafe11);
		BMC_REG_E60Ax_RdFL(videoafe15);
		BMC_REG_E60Ax_Wr01(videoafe15, reg_dbb__videoafe_cvbs_cksel, 1);	//default 0
		BMC_REG_E60Ax_WrFL(videoafe15);
	}
#endif

#if defined(INCLUDE_O18_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_O18) {
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr22);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr22, reg_videoafe_biaspdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr22);
		OS_UsecDelay(10);
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr34);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr34, reg_reset_n, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr34);
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, bmc_ctr26);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, bmc_ctr26, reg_refpll_pdb, 1);
		CTOP_CTRL_O18A0_WrFL(BMC_SYN, bmc_ctr26);
	}
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
	if(lx_chip() == LX_CHIP_L18)	/* L18 */
	{
		MIP_REG_L18A0_RdFL(bmc_ctr01);
		MIP_REG_L18A0_Wr01(bmc_ctr01,swrst_f24m,0);
		MIP_REG_L18A0_Wr01(bmc_ctr01,swrst_f24m_bb,0);
		MIP_REG_L18A0_WrFL(bmc_ctr01);
		BMC_REG_L18A0_RdFL(syn_bmc20);
		BMC_REG_L18A0_Wr01(syn_bmc20, reg_videoafe_biaspdb, 1);
		BMC_REG_L18A0_WrFL(syn_bmc20);
		OS_UsecDelay(10);
		BMC_REG_L18A0_RdFL(syn_bmc32);
		BMC_REG_L18A0_Wr01(syn_bmc32, reg_videoafe_reset_n, 1);
		BMC_REG_L18A0_WrFL(syn_bmc32);
		BMC_REG_L18A0_RdFL(syn_bmc23);
		BMC_REG_L18A0_Wr01(syn_bmc23, refpll_pdb, 1);
		BMC_REG_L18A0_WrFL(syn_bmc23);
	}
#endif


#if defined(INCLUDE_M17_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_M17) {
		ACE_REG_M17A0_RdFL(soft_reset_00);
		ACE_REG_M17A0_Wr01(soft_reset_00,swrst_f24m,0);
		ACE_REG_M17A0_Wr01(soft_reset_00,swrst_f24m_bb,0);
		ACE_REG_M17A0_WrFL(soft_reset_00);
		ACE_REG_M17A0_RdFL(videoafe_02);
		ACE_REG_M17A0_Wr01(videoafe_02, videoafe_biaspdb, 1);
		ACE_REG_M17A0_WrFL(videoafe_02);
		OS_UsecDelay(10);
		ACE_REG_M17A0_RdFL(videoafe_11);
		ACE_REG_M17A0_Wr01(videoafe_11, reset_n, 1);
		ACE_REG_M17A0_WrFL(videoafe_11);
		ACE_REG_M17A0_RdFL(videoafe_05);
		ACE_REG_M17A0_Wr01(videoafe_05, refpll_pdb, 1);
		ACE_REG_M17A0_WrFL(videoafe_05);
	}
#endif

#if defined(INCLUDE_M19_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_M19) {
		MIP_REG_M19Ax_RdFL(bmc_ctr01);
		MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_f24m, 0);
		MIP_REG_M19Ax_Wr01(bmc_ctr01, swrst_f24m_bb,0);
		MIP_REG_M19Ax_WrFL(bmc_ctr01);
		BMC_REG_M19Ax_RdFL(videoafe_02);
		BMC_REG_M19Ax_Wr01(videoafe_02, videoafe_biaspdb, 1);
		BMC_REG_M19Ax_WrFL(videoafe_02);
		OS_UsecDelay(10);
		BMC_REG_M19Ax_RdFL(videoafe_11);
		BMC_REG_M19Ax_Wr01(videoafe_11, reset_n, 1);
		BMC_REG_M19Ax_WrFL(videoafe_11);
		BMC_REG_M19Ax_RdFL(videoafe_05);
		BMC_REG_M19Ax_Wr01(videoafe_05, refpll_pdb, 1);
		BMC_REG_M19Ax_WrFL(videoafe_05);
	}
#endif


#if defined(INCLUDE_M16_CHIP_KDRV)
	if(lx_chip() == LX_CHIP_M16)
		if (drv_data->is_disp_hdmi == 1)
		{
			printk("because of disp=hdmi, SS is off...\n");
			CTOP_CTRL_M16A0_Wr(DPE, ctop_r05, 0xfff);
			CTOP_CTRL_M16A0_WrFL(DPE, ctop_r05);

			CTOP_CTRL_M16A0_Wr(VENC, ctop_r03, 0x480124f4);
			CTOP_CTRL_M16A0_WrFL(VENC, ctop_r03);

			CTOP_CTRL_M16A0_Wr(FMC, ctop_r06, 0x58213654);
			CTOP_CTRL_M16A0_WrFL(FMC, ctop_r06);

			CTOP_CTRL_M16A0_Wr(DPE, ctop_r05, 0xff0fff);
			CTOP_CTRL_M16A0_WrFL(DPE, ctop_r05);
		}
#endif

	printk("%s - done\n", __func__);

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
static int sys_probe(struct platform_device *pdev)
{
	struct sys_plt_drvdata * drv_data;
#if defined(INCLUDE_M16_CHIP_KDRV)
	char str[8];
#endif

	drv_data = (struct sys_plt_drvdata *)kmalloc(sizeof(*drv_data), GFP_KERNEL);

	// add here driver registering code & allocating resource code

	SYS_DEBUG("sys dev probe\n");

#if defined(INCLUDE_M16_CHIP_KDRV)
	drv_data->is_disp_hdmi = 0;

	if(RET_OK==OS_ScanKernelCmdline("disp=%s", str))
	{
		if(!strncmp(str,"hdmi",4))
			drv_data->is_disp_hdmi = 1;
	}
#endif

	platform_set_drvdata(pdev, drv_data);

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
static void	sys_remove(struct platform_device *pdev)
#else
static int	sys_remove(struct platform_device *pdev)
#endif
{
	struct sys_plt_drvdata * drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	SYS_DEBUG("sys dev remove\n");

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
static void  sys_release(struct device *dev)
{
	SYS_DEBUG("sys dev release\n");
}

/*
 *	module platform driver structure
 */

static int kdrv_sys_suspend_noirq(struct device * dev)
{
	printk("%s\n", __func__);

	sys_shadow_pm_function(dev, "suspend");
	sys_bwm_pm_function(dev, "suspend");

	return 0;
}

static int kdrv_sys_resume_noirq(struct device * dev)
{
	printk("%s\n", __func__);

	sys_shadow_pm_function(dev, "resume");
	sys_bwm_pm_function(dev, "resume");

	return _lgsoc_resume_chip_setup(dev);
}

static int kdrv_sys_freeze_noirq(struct device * dev)
{
	printk("%s\n", __func__);

	sys_shadow_pm_function(dev, "freeze");
	sys_bwm_pm_function(dev, "freeze");

	return 0;
}

static int kdrv_sys_restore_noirq(struct device * dev)
{
	printk("%s\n", __func__);

	sys_shadow_pm_function(dev, "restore");
	sys_bwm_pm_function(dev, "restore");

	return _lgsoc_resume_chip_setup(dev);
}

static void report_runtime_status(const char* msg_type, const char* msg_result)
{
	pr_info("%s::%s::%s::%s::%d::%s-%s::%s::%s ::%s\n",
		"LowPower",
		"info",
		"groupother",
		"none",
		0,
		current->group_leader->comm,
		current->comm,
		msg_type,
		msg_result,
		"lg1k_sys" );
}

static int kdrv_sys_runtime_resume(struct device* dev)
{
	int ret; 
	ret = sys_alp_ctrl_runtime_resume(dev);
	report_runtime_status("resume", "ok");

	SYS_NOTI("kdrv_sys_runtime_resume() ret=%d\n", ret);
	return ret;
}

static int kdrv_sys_runtime_suspend(struct device* dev)
{
	int ret;
	ret = sys_alp_ctrl_runtime_suspend(dev);
	report_runtime_status("suspend", "ok");

	SYS_NOTI("sys_alp_ctrl_runtime_suspend() ret=%d\n", ret);
	return ret;
}

static struct dev_pm_ops sys_pm_ops = {
	.suspend_noirq = kdrv_sys_suspend_noirq,
	.resume_noirq = kdrv_sys_resume_noirq,
	.freeze_noirq = kdrv_sys_freeze_noirq,
	.restore_noirq = kdrv_sys_restore_noirq,

	.runtime_suspend = kdrv_sys_runtime_suspend,
	.runtime_resume = kdrv_sys_runtime_resume,
};

static struct platform_driver sys_driver =
{
	.probe			= sys_probe,
	.remove 		= sys_remove,
	.driver 		=
	{
		.name	= "lg1k-sys",
		.pm 	= &sys_pm_ops,
	},
};

static struct platform_device sys_device = {
	.name = "lg1k-sys",
	.id = -1,
	.dev = {
		.release = sys_release,
	},
};

// see http://clm.lge.com/issue/browse/AVTASK-683
// some devices (pqepm) wants to wake up system before its own action.
void SYS_RequestForceRuntimeResume(void)
{
	pm_runtime_forbid(&sys_device.dev);
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void SYS_PreInit(void)
{
    diag_init();
}

int SYS_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */

	if (platform_driver_register(&sys_driver) < 0)
	{
		DBG_PRINT_ERROR("SYS platform drv reg fail\n");
		return -EIO;
	}
	if (platform_device_register(&sys_device) != 0)
	{
		DBG_PRINT_ERROR("SYS platform dev reg fail\n");
		return -EIO;
	}

	g_sys_device = (SYS_DEVICE_T*)OS_KMalloc( sizeof(SYS_DEVICE_T)*SYS_MAX_DEVICE );

	if ( NULL == g_sys_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", (int)sizeof(SYS_DEVICE_T)* SYS_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_sys_device, 0x0, sizeof(SYS_DEVICE_T)* SYS_MAX_DEVICE );

	if (g_sys_major)
	{
		dev = MKDEV( g_sys_major, g_sys_minor );
		err = register_chrdev_region(dev, SYS_MAX_DEVICE, SYS_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_sys_minor, SYS_MAX_DEVICE, SYS_MODULE );
		g_sys_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register sys device\n" );
		return -EIO;
	}

	/* enable PM runtime */
	pm_runtime_set_active(&sys_device.dev);
	pm_runtime_enable(&sys_device.dev);
	/* change control mode from "auto" to "on" */
	pm_runtime_forbid(&sys_device.dev);

	SYS_NOTI("lg1k-sys, pm_runtime start. enable=%d, active=%d\n",
		pm_runtime_enabled(&sys_device.dev), pm_runtime_active(&sys_device.dev));

	/* initialize shadow rom registers */
	sys_shadow_init();

	/* TODO : initialize your module not specific minor device */
#if (!defined BUILD_FEATURE_fpga)
	REG_CTRL_Init();
#endif

	/* END */

	for ( i=0; i<SYS_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_sys_major, g_sys_minor+i );
		cdev_init( &(g_sys_device[i].cdev), &g_sys_fops );
		g_sys_device[i].devno		= dev;
		g_sys_device[i].cdev.owner = THIS_MODULE;
		g_sys_device[i].cdev.ops   = &g_sys_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_sys_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding sys device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_sys_device[i].devno, "%s%d", SYS_MODULE, i );
	}

	/* initialize proc system */
	SYS_PROC_Init ( );

	SYS_PRINT("sys device initialized\n");

	sys_alp_ctrl_init();
	sys_bwm_init();
	sys_shadow_init_proc();

	return 0;
}

void SYS_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_sys_major, g_sys_minor );

	/* cleanup proc system */
	SYS_PROC_Cleanup( );

	REG_CTRL_Free();

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<SYS_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_sys_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, SYS_MAX_DEVICE );

	platform_driver_unregister(&sys_driver);
	platform_device_unregister(&sys_device);

	OS_Free( g_sys_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for sys device
 *
 */
static int SYS_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    SYS_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SYS_DEVICE_T, cdev);

    /* TODO : add your device specific code */


	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    SYS_DEBUG("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for sys device
 *
 */
static int SYS_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    SYS_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SYS_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count <= 0 )
	{

	}

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    SYS_DEBUG("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for sys device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long SYS_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
{
    int err = 0, ret = 0;

    SYS_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    /*
     * get current sys device object
     */
	my_dev	= (SYS_DEVICE_T *)filp->private_data;
	cdev	= &my_dev->cdev;

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != SYS_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > SYS_IOC_MAXNR)
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

//	SYS_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case SYS_IO_RESET:
		{
			SYS_PRINT("reset ok\n");
			ret = 0;
		}
		break;

		case SYS_IOR_CHIP_REV_INFO:
		{
			CHIP_REV_INFO_T	rev_info;

			rev_info.version = 0x100;
			rev_info.date[0] =  9;	/* 2009/11/24 */
			rev_info.date[1] = 11;
			rev_info.date[2] = 24;

			SYS_PRINT("rev_info (%0X, %d:%d:%d)\n", rev_info.version,
														rev_info.date[0], rev_info.date[1], rev_info.date[2] );

	        if ( copy_to_user((void __user *)arg, &rev_info, sizeof(CHIP_REV_INFO_T)) )
    	        return -EFAULT;

			ret = 0;
		}
		break;

		case SYS_IOW_WRITE_MEM:
		{
			LX_SYS_MEM_T mem;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_T)) != 0)
				return -EFAULT;

			ret = SYS_IO_WriteMemArray(mem.addr, 4, &mem.value);
		}
		break;

		case SYS_IORW_READ_MEM:
		{
			UINT32 addr, value;
			LX_SYS_MEM_T *in_mem = (LX_SYS_MEM_T*)arg;

			if(__get_user(addr, &in_mem->addr) != 0)
				return -EFAULT;

			ret = SYS_IO_ReadMemArray(addr, 4, &value);

			if(__put_user(value, &in_mem->value) != 0)
				return -EFAULT;
		}
		break;

		case SYS_IOW_WRITE_MEM_ARRAY:
		{
			LX_SYS_MEM_ARRAY_T mem;
			UINT8 *data;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_ARRAY_T)) != 0)
				return -EFAULT;

			if(mem.size == 0 || mem.data == 0x0)
				return -EFAULT;

			if((data = (UINT8*)OS_Malloc(mem.size)) == NULL)
				return -ENOMEM;

			if(copy_from_user((void __user *)data, (void*)mem.data, mem.size) != 0)
			{
				OS_Free(data);
				return -EFAULT;
			}

			ret = SYS_IO_WriteMemArray(mem.addr, mem.size, data);

			OS_Free(data);
		}
		break;

		case SYS_IORW_READ_MEM_ARRAY:
		{
			LX_SYS_MEM_ARRAY_T mem;
			UINT8 *data;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_ARRAY_T)) != 0)
				return -EFAULT;

			if(mem.size == 0 || mem.data == 0x0)
				return -EFAULT;

			if((data = (UINT8*)OS_Malloc(mem.size)) == NULL)
				return -ENOMEM;

			ret = SYS_IO_ReadMemArray(mem.addr, mem.size, data);

			if(copy_to_user((void __user *)mem.data, (void*)data, mem.size) != 0)
			{
				OS_Free(data);
				return -EFAULT;
			}

			OS_Free(data);
		}
		break;

		case SYS_IOW_WRITE_REG:
		{
			LX_SYS_MEM_T mem;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_T)) != 0)
				return -EFAULT;

			ret = SYS_IO_WriteRegArray(mem.addr, 4, &mem.value);
		}
		break;

		case SYS_IORW_READ_REG:
		{
			UINT32 addr, value;
			LX_SYS_MEM_T *in_mem = (LX_SYS_MEM_T*)arg;

			if(__get_user(addr, &in_mem->addr) != 0)
				return -EFAULT;

			ret = SYS_IO_ReadRegArray(addr, 4, &value);

			if(__put_user(value, &in_mem->value) != 0)
				return -EFAULT;
		}
		break;

		case SYS_IOW_WRITE_REG_ARRAY:
		{
			LX_SYS_MEM_ARRAY_T mem;
			UINT8 *data;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_ARRAY_T)) != 0)
				return -EFAULT;

			if(mem.size == 0 || mem.data == 0x0)
				return -EFAULT;

			if((data = (UINT8*)OS_Malloc(mem.size)) == NULL)
				return -ENOMEM;

			if(copy_from_user((void __user *)data, (void*)mem.data, mem.size) != 0)
			{
				OS_Free(data);
				return -EFAULT;
			}

			ret = SYS_IO_WriteRegArray(mem.addr, mem.size, data);

			OS_Free(data);
		}
		break;

		case SYS_IORW_READ_REG_ARRAY:
		{
			LX_SYS_MEM_ARRAY_T mem;
			UINT8 *data;

			if(__copy_from_user((void*)&mem, (void __user *)arg, sizeof(LX_SYS_MEM_ARRAY_T)) != 0)
				return -EFAULT;

			if(mem.size == 0 || mem.data == 0x0)
				return -EFAULT;

			if((data = (UINT8*)OS_Malloc(mem.size)) == NULL)
				return -ENOMEM;

			ret = SYS_IO_ReadRegArray(mem.addr, mem.size, data);

			if(copy_to_user((void __user *)mem.data, (void*)data, mem.size) != 0)
			{
				OS_Free(data);
				return -EFAULT;
			}

			OS_Free(data);
		}
		break;


		case SYS_IOW_SPREAD_SPRECTRUM:
		{
			LX_SPREAD_SPECTRUM_T ss;

			if(__copy_from_user((void*)&ss, (void __user *)arg, sizeof(LX_SPREAD_SPECTRUM_T)) != 0)
				return -EFAULT;

			ret = SYS_IO_SetSpreadSpectrum(&ss);
		}
		break;

		case SYS_IORW_DIAGNOSIS:
			diag_invoke_reset();
			diag_invoke_all();
			diag_report(LX_DIAG_REPORT_TYPE_PRINT);
			break;

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",SYS_Init);
#else
module_init(SYS_Init);
#endif
module_exit(SYS_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

