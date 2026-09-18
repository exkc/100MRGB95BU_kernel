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
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1313_pm
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
#include <linux/platform_device.h>

#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include "pm_drv.h"
#include "pm_core.h"
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

#include <generated/uapi/linux/version.h>

#include <linux/lg1k/pms.h>

#include "pm_m17common.h"

#include <linux/cpufreq.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static LX_PM_TEST_FACTOR_T m17_pms_test_factor;
static pms_m17_func_t *pm_m17_func;

static int m17_pms_test_boot = 0;
module_param(m17_pms_test_boot, int, S_IRUGO);
MODULE_PARM_DESC(m17_pms_test_boot, "m17lus test boot mode");

static int m17_pms_test_boot_delay = 30;
module_param(m17_pms_test_boot_delay, int, S_IRUGO);
MODULE_PARM_DESC(m17_pms_test_boot_delay, "m17lus test boot mode start delay");

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static unsigned int m17_test_boot(void)
{
	return (unsigned int)m17_pms_test_boot;
}

static void m17_test_cpu_random(LX_PM_TEST_FACTOR_T *test_factor)
{
	unsigned int freq;
	unsigned long long random;

	unsigned int core_n;
	unsigned int core_onoff;
	static unsigned int core_stats[4] = {1,1,1,1};

	pms_m17_work_t pms_work;

	memset(&pms_work, 0x0, sizeof(pms_m17_work_t));

	freq = pm_m17_func->getfreq();

#ifdef M17_DVFS_ENABLE
	if (freq == M17_CPU_FREQ_ND) {
		new_freq = M17_CPU_FREQ_UD;
	} else {
		new_freq = M17_CPU_FREQ_ND;
	}
#endif

	random = sched_clock();

#ifdef M17_DVFS_ENABLE
	if ((test_factor->testmode == CPU_FULL_RANDOM) || (test_factor->testmode == CPU_DVFS_RANDOM)) {
		if (new_freq > freq) {
			pms_work.target_freq = new_freq;
			pms_work.do_dvfs = 1;
		} else if (new_freq < freq) {
			pms_work.target_freq = new_freq;
			pms_work.do_dvfs = 2;
		}
	}
#endif

	if ((test_factor->testmode == CPU_FULL_RANDOM) || (test_factor->testmode == CPU_HOTPLUG_STRESS)) {
		core_n = ((unsigned int)(random) % 3) + 1;
		if (core_stats[core_n] == 1)
			core_onoff = 0;
		else
			core_onoff = 1;

		core_stats[core_n] =  core_onoff;

		pms_work.core_n = core_n;
		pms_work.core_onoff = core_onoff;
		pms_work.do_hotplug = 1;
	}


	pm_m17_func->run(pms_work);

	return;
}

void m17_test_func(void)
{
	unsigned int testmode;
	unsigned int count;
	unsigned int count200ms_max = 0;
	static unsigned int count200ms = 0;
	static unsigned int count1s = 0;
	static unsigned int boot_delay = 0;
	static unsigned int started = 0;
	LX_PM_TEST_FACTOR_T *test_factor;

	test_factor = &m17_pms_test_factor;
	testmode = test_factor->testmode;

	if (testmode == 0)
		return;

	if (m17_pms_test_boot && (started == 0)) {
		if (pm_m17_func->get_sampling_rate() < 1000)
			count = 1000 / pm_m17_func->get_sampling_rate();
		else
			count = 1;

		if (count1s >= count) {
			count1s = 0;

			boot_delay++;
			if (boot_delay >= m17_pms_test_boot_delay) {
				started = 1;
			} else {
				printk("M17 PM TEST COUNTDOWN %u\n", m17_pms_test_boot_delay - boot_delay);
				return;
			}

		} else {
			count1s++;
			return;
		}
	}

	if (pm_m17_func->get_sampling_rate() < 200)
		count200ms_max = 200 / pm_m17_func->get_sampling_rate();
	else
		count200ms_max = 1;

	count200ms++;

	if (count200ms >= count200ms_max) {
		count200ms = 0;

		if ((testmode >= CPU_FULL_RANDOM) && (testmode <= CPU_VOL_RANDOM)) {
			m17_test_cpu_random(test_factor);
		}
	}


	return;
}

void m17_set_testmode(unsigned int mode)
{
	m17_pms_test_factor.testmode = mode;
}

unsigned int m17_get_testmode(void)
{
	return m17_pms_test_factor.testmode;
}

void m17_set_testinterval(unsigned int interval)
{
	m17_pms_test_factor.interval = interval;
}

unsigned int m17_get_testinterval(void)
{
	return m17_pms_test_factor.interval;
}


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int m17_pm_ioctl_test (unsigned int cmd, unsigned long arg)
{
	LX_PM_TEST_FACTOR_T test_factor;

	int ret = 0;
	int result = 0;

	switch (cmd) {
		case PM_GET_TEST_FACTOR:
			result = copy_from_user((void *)&test_factor, (void __user *)arg, sizeof(test_factor));
			if (result) {
				PM_ERROR("PM_GET_TEST_FACTOR - CONFIG DATA COPY FAIL - FROM USER\n");
				break;
			}

			test_factor.interval = m17_pms_test_factor.interval;

			result = copy_to_user((void __user*)(arg), (void *)(&test_factor), sizeof(test_factor));
			if (result)
				PM_ERROR("PM_GET_TEST_FACTOR - CONFIG DATA COPY FAIL - TO USER\n");
			break;
		case PM_SET_TEST_FACTOR:
			result = copy_from_user((void *)&test_factor, (void __user *)arg, sizeof(test_factor));
			if (result) {
				PM_ERROR("PM_SET_TEST_FACTOR - CONFIG DATA COPY FAIL\n");
				break;
			}

			m17_pms_test_factor.interval =  test_factor.interval;
			break;
		case PM_GO_TEST:
			result = copy_from_user((void *)&test_factor, (void __user *)arg, sizeof(test_factor));
			if (result) {
				PM_ERROR("PM_GO_TEST - CONFIG DATA COPY FAIL\n");
				break;
			}

			m17_set_testmode(test_factor.testmode);
			break;
		case PM_STOP_TEST:
			m17_set_testmode(0);
			pm_m17_func->set_max_performance();
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

void m17_TestInit(void)
{
	 pm_m17_func = get_m17_pm_func();
}

static pms_m17_test_t m17_pm_test =
{
	.init = m17_TestInit,
	.set_testmode = m17_set_testmode,
	.get_testmode = m17_get_testmode,
	.set_testinterval = m17_set_testinterval,
	.get_testinterval = m17_get_testinterval,
	.test_func = m17_test_func,
	.test_boot = m17_test_boot,
	.ioctl = m17_pm_ioctl_test,
};

pms_m17_test_t* get_m17_pm_test(void)
{
	return &m17_pm_test;
}


