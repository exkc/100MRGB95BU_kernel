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
 *  Core driver implementation for ci device.
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2010.02.19
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define MAX_WAIT_TIME	100
#define MAX_OFF_COUNT	5
#define VCC_SW0			0x0004

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/cdev.h>
#include <linux/delay.h>	// for usleep_range, jinhwan.bae 20131018
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/platform_device.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/memory.h>

#include "ci_util.h"

#include "ci_dev.h"
#include "ci_drv.h"
#include "ci_core.h"
#include "ci_proc.h"
#include "ci_hw_ops.h"

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
int g_ci_debug_fd = -1;

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

static DEFINE_MUTEX(ci_dev_lock);
static struct task_struct *monitor_thread;

//#define CI_MAX_MINORS		4
//static CI_DEV_T *ci_base_minors[CI_MAX_MINORS] = {NULL, };

int CI_DEBUG_Uninit(void)
{
	int ret = 0;

	if (g_ci_debug_fd == -1) {
		goto out;
	}

	LOG_DRV("* CI Debug closed[%d]\n", g_ci_debug_fd);

//	OS_DEBUG_DisableModule(g_ci_debug_fd);
	DBG_CLOSE(g_ci_debug_fd);
	g_ci_debug_fd = -1;

out:
	return ret;
}

void CI_DEBUG_Init(void)
{
	if (g_ci_debug_fd != -1) {
		return;
	}

	/* Get the handle of debug output for ci device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using LOGM_ObjBitMaskEnable() function.
	 */
	g_ci_debug_fd = LOGM_ObjRegister(CI_MODULE);
	if (g_ci_debug_fd < 0) {
		DBG_PRINT_ERROR("CI DBG_OPEN failed\n");
		return;
	}

	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_ERROR);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_WARNING);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_NOTI);

#if defined(CI_DEBUG_PRINT_ON)

	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_INFO);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_DRV);
	//
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_INFO);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_TUPLE);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_PARSE);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_ERR);
	//
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_CIPLUS);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_TUPLE2);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_CIS_PARSE2);
	//
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_IO_INFO);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_DBG1);
	//
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_PROC_LVL1);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_PROC_LVL2);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_PROC_LVL3);
	LOGM_ObjBitMaskEnable(g_ci_debug_fd, LOG_LEVEL_PROC_LVL4);
	//
#endif

	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_DRV, "DRV");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_ISR, "ISR");
	//
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_INFO, "CIS_INFO");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_TUPLE, "CIS_TUPLE");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_PARSE, "CIS_PARSE");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_ERR, "CIS_ERR");
	//
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_CIPLUS, "CIS_CIPLUS");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_TUPLE2, "CIS_TUPLE2");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_CIS_PARSE2, "CIS_PARSE2");
	//
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_IO_INFO, "IO_INFO");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_DBG1, "DBG1");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_DBG2, "DBG2");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_DBG3, "DBG3");
	//
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_PROC_LVL1, "PROC_LVL1");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_PROC_LVL2, "PROC_LVL2");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_PROC_LVL3, "PROC_LVL3");
	LOGM_RegBitName(g_ci_debug_fd, LOG_LEVEL_PROC_LVL4, "PROC_LVL4");
	//

	LOG_DRV("* CI Debug opened[%d]\n", g_ci_debug_fd);
}

/**
 * @brief
 *   core bridge function : debugging log control
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 *   mask :bit-mask value for log on/off
 * @return
 *  int
 */
int CI_DEBUG_SetLog(CI_DEV_T *cidev, UINT32 mask)
{
	int idx;
	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	LOG_NOTI("CI enable log : 0x%08X\n", mask);

	mutex_lock(&ci_dev_lock);

	for (idx = 0; idx < 32; idx++) {
		if (mask & (1<<idx)) {
			LOGM_ObjBitMaskEnable(g_ci_debug_fd, idx);
		} else {
			LOGM_ObjBitMaskDisable(g_ci_debug_fd, idx);
		}
	}

	mutex_unlock(&ci_dev_lock);
	return 0;
}

int ci_free_irq(CI_DEV_T *cidev)
{
	if (cidev && cidev->irq) {
		free_irq(cidev->irq, cidev);
		LOG_INFO("cidev[0x%p] irq[%d] released\n",
				cidev, cidev->irq);
		return 0;
	}
	return -ENODEV;
}

int ci_release_irq(CI_DEV_T *cidev)
{
	if (cidev) {
		ci_free_irq(cidev);
		cidev->irq = 0;
		return 0;
	}
	return -ENODEV;
}

int ci_request_irq(CI_DEV_T *cidev)
{
	int ret = 0;

	if (cidev && cidev->irq) {
		ret = request_irq(cidev->irq, CI_irq_handler, 0,
					//	IRQF_SHARED | IRQF_TRIGGER_HIGH,
					//	IRQF_SHARED | IRQF_TRIGGER_RISING,
						ci_dev_name(cidev), cidev);
		LOG_INFO("request_irq[%d] %s, %d",
				cidev->irq, (ret)?"failed":"done", ret);
	}

	return ret;
}

void ci_uninit_chrdev_region(ci_chrdev_data_t *chrdev_data)
{
	dev_t devNo;
	char *name;
	int major, minor, num;

	mutex_lock(&ci_dev_lock);

	name = chrdev_data->name;
	major = chrdev_data->major;
	minor = chrdev_data->minor;
	num = chrdev_data->num;
	devNo = MKDEV(major, minor);

	unregister_chrdev_region(devNo, num);
	LOG_DRV2("ci uninit char region : dev_t[%d-%d] num[%d]\n",
				major, minor, num);

	mutex_unlock(&ci_dev_lock);
}

int ci_init_chrdev_region(ci_chrdev_data_t *chrdev_data)
{
	dev_t devNo;
	char *name;
	int major, minor, num;
	int ret = 0;

	mutex_lock(&ci_dev_lock);

	name = chrdev_data->name;
	major = chrdev_data->major;
	minor = chrdev_data->minor;
	num = chrdev_data->num;

	if (major) {
		devNo = MKDEV(major, minor);
		ret = register_chrdev_region(devNo, num, name);
		if (ret != 0) {
			LOG_ERROR("unable to register_chrdev_region[%d-%d, %d], %d\n",
					major, minor, num, ret);
			goto out;
		}
	} else {
		ret = alloc_chrdev_region(&devNo, minor, num, name);
		if (ret != 0) {
			LOG_ERROR("unable to alloc_chrdev_region, %d\n", ret);
			goto out;
		}
		major = MAJOR(devNo);
		chrdev_data->major = major;
	}
	LOG_DRV2("ci init char region : dev_t[%d-%d] num[%d]\n",
				major, minor, num);

out:
	mutex_unlock(&ci_dev_lock);
	return ret;
}

static void __ci_del_cdevs(CI_DEV_T *cidev, int num)
{
	dev_t devNo;
	int i;

	for (i = 0; i < num; i++) {
		devNo = cidev->cdev.dev;
		cdev_del(&cidev->cdev);
		LOG_DRV2("ci cdev[%d, %d-%d] deleted\n",
				i, MAJOR(devNo), MINOR(devNo));
		cidev++;
	}
}

void ci_del_chrdev(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data)
{
	__ci_del_cdevs(ci_devs, chrdev_data->num);
}

int ci_add_chrdev(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data)
{
	CI_DEV_T *cidev;
	dev_t devNo;
	char *name;
	int major, minor, num;
	int i;
	int ret = 0;

	mutex_lock(&ci_dev_lock);

	name = chrdev_data->name;
	major = chrdev_data->major;
	minor = chrdev_data->minor;
	num = chrdev_data->num;

	for (i=0; i<num; i++) {
		cidev = &ci_devs[i];

		devNo = MKDEV(major, minor + i);

		cdev_init(&cidev->cdev, cidev->fops);
		cidev->cdev.owner = cidev->fops->owner;
		ret = cdev_add(&cidev->cdev, devNo, 1);
		if (ret != 0) {
			LOG_ERROR("unable to add cdev[%d, %d-%d], %d\n",
					i, major, minor, ret);
			__ci_del_cdevs(ci_devs, i);
			goto out;
		}
		LOG_DRV2("ci cdev[%d, %d-%d] added\n", i, major, minor);
	}

out:
	mutex_unlock(&ci_dev_lock);
	return ret;

}

int ci_destroy_device_class(CI_DEV_T *cidev)
{
	OS_DestroyDeviceClass(cidev->devno);
	return 0;
}

int ci_create_device_class(CI_DEV_T *cidev)
{
	OS_CreateDeviceClass(cidev->devno, "%s", ci_dev_name(cidev));
	return 0;
}

void ci_free_devs(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data)
{
	CI_DEV_T *cidev;
	int i;

	mutex_lock(&ci_dev_lock);


	for ( i = 0; i<chrdev_data->num; i++) {
		cidev = &ci_devs[i];

		cidev->off_count = 0;
		cidev->on_init = 0;

	//	ci_clear_is_flag_all(cidev);
		ci_destroy_device_class(cidev);

		LOG_DRV2("ci cidev[%s, 0x%08X] removed\n",
					ci_dev_name(cidev), cidev->devno);
	}
	mutex_unlock(&ci_dev_lock);

	ci_free(ci_devs);
	LOG_DRV2("ci_devs removed\n");
}

CI_DEV_T *ci_alloc_devs(ci_chrdev_data_t *chrdev_data)
{
	CI_DEV_T *ci_devs = NULL;
	CI_DEV_T *cidev;
	char *name;
	int major, minor, num;
	int i;

	name = chrdev_data->name;
	major = chrdev_data->major;
	minor = chrdev_data->minor;
	num = chrdev_data->num;

	ci_devs = (CI_DEV_T *)ci_zalloc(sizeof(CI_DEV_T) * num);
	if (ci_devs == NULL) {
		LOG_ERROR("unable to allocate ci_devs\n");
		goto out;
	}
	LOG_DRV2("ci_devs allocated\n");

	mutex_lock(&ci_dev_lock);

	for (i = 0; i < num; i++) {
		cidev = &ci_devs[i];

		cidev->idx = i;

		ci_mutex_init(cidev);
		ci_lock_init(cidev);
		ci_io_lock_init(cidev);

		mutex_init(&cidev->access_mutex);
		cidev->power_on = 0; //Power Off when initialize
		cidev->off_count = 0;
		cidev->on_init = 0;

		snprintf(ci_dev_name(cidev), CI_MAX_NAME, "%s%d", name, i);
		cidev->devno = MKDEV(major, minor + i);

		ci_create_device_class(cidev);

		ci_is_flag(cidev) = 0;

		LOG_DRV2("ci cidev[%s, 0x%08X] added\n",
					ci_dev_name(cidev), cidev->devno);
	}

	mutex_unlock(&ci_dev_lock);

out:
	return ci_devs;
}

static void __ci_cancel_plt_devices(struct platform_device *pdev,
								CI_DEV_T *ci_devs, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		platform_device_unregister(pdev);
		LOG_DRV("* CI platform device[%d] unregistered\n", i);
		ci_devs->pdev = NULL;
		ci_devs->parent = NULL;

		pdev++;
		ci_devs++;
	}
}

void ci_uninit_platform(void *pdriver_priv,
						void *pdevices_priv,
						CI_DEV_T *ci_devs,
						ci_chrdev_data_t *chrdev_data)
{
	struct platform_driver *pdriver = (struct platform_driver *)pdriver_priv;
	struct platform_device *pdevices = (struct platform_device *)pdevices_priv;

	__ci_cancel_plt_devices(pdevices, ci_devs, chrdev_data->num);

	// added by SC Jung for quick booting
	platform_driver_unregister(pdriver);
	LOG_DRV("* CI platform driver unregistered\n");
}

int ci_init_platform(void *pdriver_priv,
					void *pdevices_priv,
					CI_DEV_T *ci_devs,
					ci_chrdev_data_t *chrdev_data)
{
	struct platform_driver *pdriver = (struct platform_driver *)pdriver_priv;
	struct platform_device *pdevices = (struct platform_device *)pdevices_priv;
	struct platform_device *pdev;
	CI_DEV_T *cidev;
//	char *name = chrdev_data->name;
	int num = chrdev_data->num;
	int probe_done;
	int i;
	int ret = 0;

	// added by SC Jung for quick booting
	ret = platform_driver_register(pdriver);
	if (ret != 0) {
		LOG_ERROR("CI platform driver register failed, %d\n", ret);
		goto out;
	}
	LOG_DRV("* CI platform driver registered\n");

	for (i = 0; i < num; i++) {
		pdev = &pdevices[i];
		cidev = &ci_devs[i];

		platform_set_drvdata(pdev, cidev);
		ret = platform_device_register(pdev);
		probe_done = ci_is_probe_done(cidev);
		if ((ret != 0) || !probe_done) {
			LOG_ERROR("CI platform err : ret[%d], probe[%d]\n", ret, probe_done);
			__ci_cancel_plt_devices(pdevices, ci_devs, i);
			ret = (!ret)? -ENODEV : ret;
			goto out_drv;
		}

		//Enable async suspend and resume/
		device_enable_async_suspend(&(pdev->dev));
		LOG_DRV("* CI device enabled async suspend/resume");

		cidev->pdev = pdev;
		cidev->parent = &pdev->dev;
		LOG_DRV("* CI platform device[%d] registered", i);
	}

	LOG_DRV("* CI platform init done\n");

	return 0;

out_drv:
	platform_driver_unregister(pdriver);
	LOG_DRV("* CI platform driver unregistered");

out:
	return ret;
}


void ci_uninit_delay_op(CI_DEV_T *cidev)
{
	//Nothing to do
}

int ci_init_delay_op(CI_DEV_T *cidev)
{
	//Nothing to do
	CI_CORE_ShowDelays(cidev, LOG_LEVEL_DBG1);

	return RET_OK;
}


static int CardDetectionMonitorThread(void *unused)
{
	bool frozen;
	int rc, timeout_jiffies;
	CI_DEV_T *dev = CI_GetDevs(); //Only one device

	timeout_jiffies = msecs_to_jiffies(MAX_WAIT_TIME);

	init_completion(&dev->completion);
	set_freezable();

	while(!kthread_freezable_should_stop(&frozen))
	{
		rc = wait_for_completion_timeout(&dev->completion ,timeout_jiffies);

		ci_hw_verify_card_detection(dev, 1, __func__); //Update card_detected variable

		mutex_lock(&dev->access_mutex);

		if(dev->on_init)
		{
			LOG_MONITOR("Monitoring Paused (Under Initialization)");
			mutex_unlock(&dev->access_mutex);
			continue;
		}

		if(rc >= 0) //By Interrupt and timeout
		{
			if (ci_is_card_detected(dev))
			{
				UINT16 reg_val;

				if(!dev->power_on)
				{
					reg_val = CI_READ16(dev, CREG_CTRL_STATUS_1);
					reg_val |= VCC_SW0; //VCC ON when it is considered as insert
					CI_WRITE16(dev, reg_val, CREG_CTRL_STATUS_1);
					ci_pcap_mon_hw_evt(dev, CI_PCAP_HW_EVT_POWER_ON);

					LOG_MONITOR("Power On");
					dev->power_on = 1;
				}

				dev->off_count = 0;
			}
			else
			{
				if(dev->power_on && dev->off_count < MAX_OFF_COUNT)
				{
					dev->off_count++; //Count for Power off detection
				}
			}
		}
		else //By signal
		{
			//Nothing to do
		}

		LOG_MONITOR("Monitoring (%s), count = %d", (rc == 0) ? "timeout":"sig/intr", dev->off_count);

		if(dev->power_on && dev->off_count >= MAX_OFF_COUNT) //card is turned off over MAX COUNT
		{
			ci_is_flag_reset_for_cam(dev);

			CI_WRITE16(dev, 0x0000, CREG_CTRL_STATUS_1);
			ci_pcap_mon_hw_evt(dev, CI_PCAP_HW_EVT_POWER_OFF);

			LOG_MONITOR("Power Off");
			dev->power_on = 0;
		}

		mutex_unlock(&dev->access_mutex);

		//init_completion(&dev->completion);
	}

	return 0;
}

//Monitor for card detection
int CI_InitMonitor(void)
{
	CHECK_ERROR(monitor_thread, goto exit, "already initialized");

	monitor_thread = kthread_create(CardDetectionMonitorThread, NULL, "card detection monitor");
	CHECK_ERROR(monitor_thread == NULL, goto exit, "can't create thread");

	wake_up_process(monitor_thread);

	return RET_OK;

exit:
	return RET_ERROR;
}

int CI_StopMonitor(void)
{
	CHECK_ERROR(!monitor_thread, return RET_ERROR, "thread not started");

	kthread_stop(monitor_thread);
	kfree(monitor_thread);

	monitor_thread = NULL;

	return RET_OK;
}


