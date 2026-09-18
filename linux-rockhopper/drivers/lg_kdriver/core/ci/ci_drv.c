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
 *  main driver implementation for ci device.
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author		Srinivasan Shanmugam	(srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
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
#include <asm/uaccess.h>
#include <linux/platform_device.h>

#include "../sys/sys_regs.h"	//for CTOP CTRL Reg. map

#include "ci_regdefs.h"

#include "ci_util.h"
#include "ci_dev.h"
#include "ci_drv.h"
#include "ci_core.h"
#include "ci_ioctl.h"
#include "ci_proc.h"
#include "ci_hw_cis.h"
#include "ci_hw_ops.h"

static CI_DEV_T *ci_devices = NULL;

static const ci_chrdev_data_t ci_chrdev_data_base = {	\
	.name	= CI_MODULE,
	.major	= CI_MAJOR,
	.minor	= CI_MINOR,
	.num	= CI_MAX_DEVICE,
};

#if defined(CI_CIS_ADDR_LIMIT)
#define CIS_ADDR_LIMIT	0x1000
#else
#define CIS_ADDR_LIMIT	0
#endif

static int ci_chk_chip_rev(CI_DEV_T *cidev)
{
	u32 chip_rev;
	u32 chip;

	chip_rev = lx_chip_rev();
	if (!chip_rev) {
		LOG_ERROR("No chip_rev!!!\n");
		return -ENODEV;
	}

	chip = (chip_rev>>8)&0xFF;
	cidev->chip_rev = chip_rev;
	cidev->chip_sub = chip_rev & 0xFF;

	LOG_DRV2("chip_rev = 0x%04X\n", chip_rev);
	LOG_DRV2("chip_sub = 0x%04X\n", chip_rev & 0xFF);

	return 0;
}

static int ci_init_opt_flag(CI_DEV_T *cidev)
{
	ci_opt_flag(cidev) = 0;

#if defined(CI_POL_CHECK_ON)
	ci_opt_cd_pol(cidev) = 1;
#endif

#if defined(CI_OPT_CHK_MODE)
	ci_opt_io_mode_on(cidev) = 1;
#endif
	ci_opt_io_mode(cidev) = CI_ERR_CHK_MODE_FULL;

#if defined(CI_IO_TIME_PRINT)
	ci_opt_io_time_show(cidev) = 1;
#endif

#if defined(CI_OS_PROC_BASE)
	ci_opt_os_proc_base(cidev) = 1;
#endif

	LOG_DRV2("opt_flag - opt_cd_pol       = %d\n", ci_opt_cd_pol(cidev));
	LOG_DRV2("         - opt_io_mode_on   = %d\n", ci_opt_io_mode_on(cidev));
	LOG_DRV2("         - opt_io_mode      = %d\n", ci_opt_io_mode(cidev));
	LOG_DRV2("         - opt_io_time_show = %d\n", ci_opt_io_time_show(cidev));
	LOG_DRV2("         - opt_os_proc_base = %d\n", ci_opt_os_proc_base(cidev));
	return 0;
}

/* Pull up register (IREQ, VCCEN) */
/* Pull up register (REG, CD1, CD2, WAIT) */
#ifdef INCLUDE_M17_CHIP_KDRV
static int M17_CI_REG_CTOP_PullUp(void)
{

	CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r03);
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r03, reg_cam_ireq_n_pu, 1);
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r03, reg_cam_vccen_n_pu, 1);
	CTOP_CTRL_M17A0_WrFL(FME0, ctop_fme0_r03);

	CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r04);
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r04, reg_cam_reg_n_pu, 1);
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r04, reg_cam_cd1_n_pu, 0); //0: Enable
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r04, reg_cam_cd2_n_pu, 0); //0: Enable
	CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r04, reg_cam_wait_n_pu, 1);
	CTOP_CTRL_M17A0_WrFL(FME0, ctop_fme0_r04);

	return 0;
}
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
static int L18_CI_REG_CTOP_PullUp(void)
{
	CTOP_CTRL_L18A0_RdFL(PQE, syn_pqe18);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_ireq_n__pu, 1);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_vccen_n__pu, 1);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_reg_n__pu, 1);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_cd1_n__pu, 1);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_cd2_n__pu, 1);
	CTOP_CTRL_L18A0_Wr01(PQE, syn_pqe18, reg_pad_cam_wait_n__pu, 1);
	CTOP_CTRL_L18A0_WrFL(PQE, syn_pqe18);

	return 0;
}
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
static int O18_CI_REG_CTOP_PullUp(void)
{
	CTOP_CTRL_O18A0_RdFL(CTOP_ME1, ctr30);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_cd1_n_pu, 1);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_cd2_n_pu, 1);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_ireq_n_pu, 1);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_reg_n_pu, 1);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_vccen_n_pu, 1);
	CTOP_CTRL_O18A0_Wr01(CTOP_ME1, ctr30, pad_cam_wait_n_pu, 1);
	CTOP_CTRL_O18A0_WrFL(CTOP_ME1, ctr30);

	return 0;
}
#endif

#ifdef INCLUDE_M19_CHIP_KDRV
static int M19_CI_REG_CTOP_Pullup(void)
{
	CTOP_CTRL_M19Ax_RdFL(CTOP_AUD, ctop_aud_r03);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r03, reg_cam_ireq_n_pu, 1);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r03, reg_cam_vccen_n_pu, 1);
	CTOP_CTRL_M19Ax_WrFL(CTOP_AUD, ctop_aud_r03);

	CTOP_CTRL_M19Ax_RdFL(CTOP_AUD, ctop_aud_r04);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r04, reg_cam_reg_n_pu, 1);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r04, reg_cam_cd1_n_pu, 1);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r04, reg_cam_cd2_n_pu, 1);
	CTOP_CTRL_M19Ax_Wr01(CTOP_AUD, ctop_aud_r04, reg_cam_wait_n_pu, 1);
	CTOP_CTRL_M19Ax_WrFL(CTOP_AUD, ctop_aud_r04);

	return 0;
}
#endif

static int ci_init_pull_up(CI_DEV_T *cidev)
{
	int ret;
	UINT32 chip = lx_chip();

	if(0) {}
	else if(chip == LX_CHIP_O20)
	{
		//nothing to do
	}
#ifdef INCLUDE_L18_CHIP_KDRV
	else if(chip == LX_CHIP_L18F)
	{
		ret = L18_CI_REG_CTOP_PullUp();
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if(chip == LX_CHIP_M17)
	{
		ret = M17_CI_REG_CTOP_PullUp();
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if(chip == LX_CHIP_O18)
	{
		ret = O18_CI_REG_CTOP_PullUp();
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if(chip == LX_CHIP_M19)
	{
		ret = M19_CI_REG_CTOP_Pullup();
	}
#endif
	else
	{
		LOG_ERROR("not defined chip!!!");
		ret = RET_ERROR;
	}

	CHECK_ERROR(ret != 0, return ret, "pull up failed");

	LOG_DRV2("pull up done\n");

	return 0;
}

static int DisableGPIORemux(void)
{
#ifdef INCLUDE_M17_CHIP_KDRV
	if(lx_chip() == LX_CHIP_M17)
	{
		CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r12);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_0_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_1_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_2_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_3_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_4_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_5_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_6_mux_en, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r12, gp15_7_mux_en, 0);
		CTOP_CTRL_M17A0_WrFL(FME0, ctop_fme0_r12);
	}
#endif

	return RET_OK;
}

static int ci_init_reg_irq(CI_DEV_T *cidev)
{
	CI_CFG_T *cfg = CI_GetConfig();

	CHECK_ERROR(!cfg->irq_num, return -EFAULT, "irq num not defined");
	CHECK_ERROR(!cfg->reg_base, return -EFAULT, "reg base not defined");

	cidev->irq = cfg->irq_num;
	LOG_DRV2("irq_num = %d\n", cfg->irq_num);

	ci_opt_burst_mode(cidev) = 0;

	if(!cfg->cis_addr_limit)
		cfg->cis_addr_limit = cfg->mod_size; //Not used

	LOG_DRV2("burst_mode = 0x%X\n", ci_opt_burst_mode(cidev));
	LOG_DRV2("reg_base   = 0x%08X\n", cfg->reg_base);
	LOG_DRV2("reg_size   = 0x%08X\n", cfg->reg_size);
	LOG_DRV2("mod_base   = 0x%08X\n", cfg->mod_base);
	LOG_DRV2("mod_size   = 0x%08X\n", cfg->mod_size);
	LOG_DRV2("cis_addr_limit = 0x%08X\n", cfg->cis_addr_limit);
	if (!cfg->reg_base) {
		LOG_ERROR("failed!!!\n");
		return -ENODEV;
	}

	return 0;
}

static void ci_uninit_config(CI_DEV_T *cidev)
{
	BUG_ON(cidev == NULL);

	ci_uninit_delay_op(cidev);
}


static int ci_init_config(CI_DEV_T *cidev)
{
	int ret = 0;

	BUG_ON(cidev == NULL);

	ret = ci_chk_chip_rev(cidev);
	CHECK_ERROR(ret != 0, goto out, "Error in ci_chk_chip_rev");

	ret = ci_init_opt_flag(cidev);
	CHECK_ERROR(ret != 0, goto out, "Error in ci_init_opt_flag");

	ret = ci_init_reg_irq(cidev);
	CHECK_ERROR(ret != 0, goto out, "Error in ci_init_reg_irq");

	ret = ci_init_pull_up(cidev);
	CHECK_ERROR(ret != 0, goto out, "Error in ci_init_pull_up");

	ret = ci_init_delay_op(cidev);
	CHECK_ERROR(ret != 0, goto out, "Error in ci_init_delay_op");

	DisableGPIORemux();

	return 0;

out:
	ci_uninit_delay_op(cidev);
	return ret;
}

static int __ci_probe(CI_DEV_T *cidev)
{
	int ret = 0;

	ret = ci_init_config(cidev);
	if (ret != 0) {
		return ret;
	}

	ret = ci_init_proc(cidev);
	if (ret != 0) {
		goto out;
	}

	ret = CI_CORE_Init(cidev);
	if (ret != 0) {
		goto out_proc;
	}

	/* !!!after CI_CORE_Init */
	ret = ci_request_irq(cidev);
	if (ret != 0) {
		goto out_init;
	}

	ci_is_probe_done(cidev) = 1;

	LOG_NOTI("CI device[%d] initialized\n", cidev->idx);

	return 0;

out_init:
	CI_CORE_Uninit(cidev);

out_proc:
	ci_uninit_proc(cidev);

out:
	ci_uninit_config(cidev);
	return ret;
}

static int __ci_remove(CI_DEV_T *cidev)
{
	ci_release_irq(cidev);

	CI_CORE_Uninit(cidev);

	ci_uninit_proc(cidev);

	ci_uninit_config(cidev);

	LOG_NOTI("CI device[%d] uninitialized\n", cidev->idx);
	return 0;
}

#define CIM_TEST_LOG_ON

#if defined(CIM_TEST_LOG_ON)
#define cim_pm_test_log(fmt, args...)		printk(fmt, ##args)
#else
#define cim_pm_test_log(fmt, args...)		do{	}while(0)
#endif

static int __ci_plt_suspend(CI_DEV_T *cidev)
{
	int ret = 0;

	if (cidev == NULL) {
		LOG_WARNING("NULL cidev\n");
		return 0;
	}

#ifdef KDRV_CONFIG_PM_LEGACY_CI
	cim_pm_test_log("CI - suspend BEGIN\n");

	if (!ci_is_init_done(cidev)) {
		cim_pm_test_log("CI - suspend FAIL : not initialized\n");
		return 0;
	}

	if (ci_is_suspended(cidev)) {
		cim_pm_test_log("CI - suspend FAIL : alread suspened\n");
		return -1;	//If already in suspend state, so ignore
	}

	ci_free_irq(cidev);

	ret = CI_CORE_Suspend(cidev);
	if (ret != 0) {
		cim_pm_test_log("CI - suspend FAIL : core suspend (%d)\n", ret);
		return -1;
	}

	ci_is_suspended(cidev) = 1;
	cim_pm_test_log("CI - suspend OK\n");
#endif

	return ret;
}

static int __ci_plt_resume(CI_DEV_T *cidev)
{
	int ret = 0;

	if (cidev == NULL) {
		LOG_WARNING("NULL cidev");
		return 0;
	}

#ifdef KDRV_CONFIG_PM_LEGACY_CI
	cim_pm_test_log("CI - resume BEGIN\n");

	if (!ci_is_init_done(cidev)) {
		cim_pm_test_log("CI - suspend FAIL : not initialized\n");
		return 0;
	}

	if (!ci_is_suspended(cidev)) {
		cim_pm_test_log("CI - resume FAIL : already resumed\n");
		return -1;	//If already in resume state, so ignore
	}

	ret = ci_init_pull_up(cidev);
	if (ret != 0) {
		cim_pm_test_log("CI - resume FAIL : Pull-up (%d)\n", ret);
		return -1;
	}

	ret = DisableGPIORemux();
	if (ret != 0) {
		cim_pm_test_log("CI - fail gpio disable(%d)\n", ret);
	}

	ret = CI_CORE_Resume(cidev);
	if (ret != 0) {
		cim_pm_test_log("CI - resume FAIL : core resume (%d)\n", ret);
		return -1;
	}

	ret = ci_request_irq(cidev);
	if (ret != 0) {
		cim_pm_test_log("CI - resume FAIL : request irq (%d)\n", ret);
		return -1;
	}

	ci_is_suspended(cidev) = 0;
	cim_pm_test_log("CI - resume OK\n");
#endif

	return 0;
}

static int ci_plt_suspend(struct platform_device *pdev, pm_message_t state)
{
	CI_DEV_T *cidev = platform_get_drvdata(pdev);

	return __ci_plt_suspend(cidev);
}

static int ci_plt_resume(struct platform_device *pdev)
{
	CI_DEV_T *cidev = platform_get_drvdata(pdev);

	return __ci_plt_resume(cidev);
}

static int ci_plt_probe(struct platform_device *pdev)
{
	CI_DEV_T *cidev = platform_get_drvdata(pdev);
	int ret = 0;

	if (cidev == NULL) {
		LOG_ERROR("NULL cidev : pdev->id[%d]\n", pdev->id);
		return -ENODEV;
	}
	LOG_DRV2("pdev->id   = %d\n", pdev->id);
	LOG_DRV2("cidev->idx = %d\n", cidev->idx);

	ret = __ci_probe(cidev);
	if ((ret == -ENODEV) || (ret == -ENXIO)) {
		LOG_ERROR("Error in __ci_probe [%d]", ret);
		/* See really_probe ({kernel}/drivers/base/dd.c) */
		ret = -EIO;
	}

	return ret;
}

static int ci_plt_remove(struct platform_device *pdev)
{
	CI_DEV_T *cidev = platform_get_drvdata(pdev);
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev : pdev->id[%d]\n", pdev->id);
		return -ENODEV;
	}
	LOG_DRV2("pdev->id   = %d\n", pdev->id);
	LOG_DRV2("cidev->idx = %d\n", cidev->idx);

	__ci_remove(cidev);

	return 0;
}

static void ci_plt_release(struct device *dev)
{
	struct platform_device *pdev = container_of(dev, struct platform_device, dev);
	LOG_DRV2("pdev->dev[%d] released\n", pdev->id);
}

static struct platform_driver ci_plt_driver = {
	.probe          = ci_plt_probe,
	.remove         = ci_plt_remove,
	.suspend        = ci_plt_suspend,
	.resume         = ci_plt_resume,
	.driver = {
		.name   = CI_MODULE,
	},
};

static struct platform_device ci_plt_device = {
	.name			= CI_MODULE,
	.id				= -1,
	.dev = {
		.release	= ci_plt_release,
	},
};

static int ci_uninit_devs(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data)
{
	CI_DEV_T *cidev;
	int num = chrdev_data->num;
	int i;

	for (i = 0; i < num; i++)
	{
		cidev = &ci_devs[i];

		ci_free(cidev->fops);

		cidev->cfg = NULL;
		cidev->fops = NULL;
	}

	return 0;
}

static int ci_init_devs(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data)
{
	CI_CFG_T *cfg = CI_GetConfig();
	struct file_operations *fops;
	int fops_size;
	int i;

	fops_size   = sizeof(struct file_operations);

	for (i = 0; i < CI_MAX_DEVICE; i++) {
		ci_devs[i].cfg = cfg;

		fops = (void *)ci_malloc(fops_size);
		ci_devs[i].fops = fops;
		if (fops == NULL)
		{
			LOG_ERROR("unabled to allocate fops(%d)", i);
			goto out;
		}

		memcpy((void *)fops, (void *)&ci_fops_base, sizeof(struct file_operations));
	}

	return 0;

out:
	ci_uninit_devs(ci_devs, chrdev_data);
	return -ENOMEM;
}

/** @file
 *
 *  main driver implementation for ci device.
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author		Srinivasan Shanmugam	(srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */
static int _ci_init(void)
{
	ci_chrdev_data_t *chrdev_data = (ci_chrdev_data_t *)&ci_chrdev_data_base;
	int ret = 0;

	LOG_NOTI("CI driver use usleep_range \n");

	ci_devices = (CI_DEV_T *)ci_alloc_devs(chrdev_data);
	if (ci_devices == NULL) {
		goto out;
	}
	ret = ci_init_devs(ci_devices, chrdev_data);
	if (ret != 0) {
		goto out_alloc;
	}

	ret = ci_init_chrdev_region(chrdev_data);
	if (ret != 0) {
		goto out_dev;
	}

	ret = ci_add_chrdev(ci_devices, chrdev_data);
	if (ret != 0) {
		goto out_chrdev_region;
	}

	ret = ci_init_platform(&ci_plt_driver,
						&ci_plt_device,
						ci_devices,
						chrdev_data);
	if (ret != 0) {
		goto out_chrdev;
	}

	return 0;

out_chrdev:
	ci_del_chrdev(ci_devices, chrdev_data);

out_chrdev_region:
	ci_uninit_chrdev_region(chrdev_data);

out_dev:
	ci_uninit_devs(ci_devices, chrdev_data);

out_alloc:
	ci_free_devs(ci_devices, chrdev_data);
	ci_devices = NULL;

out:
	CI_DEBUG_Uninit();
	return ret;
}

/**
 *	Cleanup CI device
*/
static void _ci_cleanup(void)
{
	ci_chrdev_data_t *chrdev_data = (ci_chrdev_data_t *)&ci_chrdev_data_base;

	ci_uninit_platform(&ci_plt_driver,
					&ci_plt_device,
					ci_devices,
					chrdev_data);

	ci_del_chrdev(ci_devices, chrdev_data);

	ci_uninit_chrdev_region(chrdev_data);

	ci_uninit_devs(ci_devices, chrdev_data);

	ci_free_devs(ci_devices, chrdev_data);
	ci_devices = NULL;

	CI_DEBUG_Uninit();
}

CI_DEV_T* CI_GetDevs(void)
{
	return ci_devices;
}
/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void CI_PreInit(void)
{
	CI_DEBUG_Init(); //Init Logm
	CI_CFG_PreInit(); //Register CI Setting
}

int CI_Init(void)
{
	int rc;

	rc = _ci_init();
	CI_InitMonitor();

	return rc;
}

void CI_Cleanup(void)
{
	CI_StopMonitor();
	_ci_cleanup();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", _ci_init);
#else
module_init(_ci_init);
#endif
module_exit(_ci_cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

