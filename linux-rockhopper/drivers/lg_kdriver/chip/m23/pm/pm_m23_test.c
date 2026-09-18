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
#include <linux/version.h>
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
#include <linux/sched/clock.h>
#endif
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

#include "pm_m23common.h"

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
static LX_PM_TEST_FACTOR_T m23_pms_test_factor;
static pms_m23_func_t *pm_m23_func;
static pms_m23_gov_t *pm_m23_gov;

static int m23_pms_test = 0;
module_param(m23_pms_test, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_test, "m23 test boot mode");

static int m23_pms_test_boot_delay = 30;
module_param(m23_pms_test_boot_delay, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_test_boot_delay, "m23  test boot mode start delay");

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static unsigned int m23_test_boot(void)
{
	return (unsigned int)m23_pms_test;
}

static void m23_test_cpu_random(LX_PM_TEST_FACTOR_T *test_factor)
{
	unsigned long long random;

	unsigned int core_n;
	unsigned int core_onoff;
	static unsigned int core_stats[4] = {1,1,1,1};

	pms_m23_work_t pms_work;

	memset(&pms_work, 0x0, sizeof(pms_m23_work_t));

	random = sched_clock();

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

	pm_m23_func->run(&pms_work);

	return;
}

static void m23_test_freq_random(LX_PM_TEST_FACTOR_T *test_factor)
{
	unsigned long long random;

	unsigned int freq_n;
	static unsigned int freqs[2] = {1400,1050};

	pms_m23_work_t pms_work;
	memset(&pms_work, 0x0, sizeof(pms_m23_work_t));
	random = sched_clock();

	if ((test_factor->testmode == CPU_DVFS_RANDOM ) || (test_factor->testmode == CPU_FULL_RANDOM) ) {
		freq_n = ((unsigned int)(random) % 2) ;
		//pms_work.do_dvfs = 1;
		pms_work.target_freq = freqs[freq_n] ;
		//pm_m23_func->run(pms_work);
		pm_m23_func->setfreq(pms_work.target_freq);
	}
	return;
}

void m23_test_func(void)
{
	unsigned int testmode = 0;
	unsigned int count200ms_max = 0;
	static unsigned int count200ms = 0;
	#if 0
	unsigned int count;
	static unsigned int count1s = 0;
	static unsigned int boot_delay = 0;
	static unsigned int started = 0;
	#endif
	LX_PM_TEST_FACTOR_T *test_factor;

	test_factor = &m23_pms_test_factor;
	testmode = test_factor->testmode;

	if(m23_pms_test)
	{
		testmode = m23_pms_test;
		test_factor->testmode = m23_pms_test;

		if(!pm_m23_gov->get_gov_start())
			return;
		if( pm_m23_gov->get_gov() != PMS_GOV_DISABLE)
			 pm_m23_gov->set_gov(PMS_GOV_DISABLE);
	}
	else{
		if (testmode == 0 ){
			return;
		}
	}

	#if 0
	if (m23_pms_test && (started == 0)) {
		if (pm_m23_func->get_sampling_rate() < 1000)
			count = 1000 / pm_m23_func->get_sampling_rate();
		else
			count = 1;

		if (count1s >= count) {
			count1s = 0;

			boot_delay++;
			if (boot_delay >= m23_pms_test_boot_delay) {
				started = 1;
			} else {
				printk("M23 PM TEST COUNTDOWN %u\n", m23_pms_test_boot_delay - boot_delay);
				return;
			}

		} else {
			count1s++;
			return;
		}
	}
	#endif

	if (pm_m23_func->get_sampling_rate() < 200)
		count200ms_max = 200 / pm_m23_func->get_sampling_rate();
	else
		count200ms_max = 1;

	count200ms++;

	if (count200ms >= count200ms_max) {
		count200ms = 0;

		if ((testmode >= CPU_FULL_RANDOM) && (testmode <= CPU_VOL_RANDOM)) {
			if(testmode ==  CPU_FULL_RANDOM)
			{
				pm_m23_gov->set_mp_enable(1);
				m23_test_cpu_random(test_factor);
				m23_test_freq_random(test_factor);

			}
			else if(testmode ==  CPU_HOTPLUG_STRESS)
			{
				pm_m23_gov->set_mp_enable(1);

				m23_test_cpu_random(test_factor);
			}
			else if(testmode == CPU_DVFS_RANDOM)
			{
				m23_test_freq_random(test_factor);
			}
		}
	}


	return;
}

void m23_set_testmode(unsigned int mode)
{
	m23_pms_test_factor.testmode = mode;
}

unsigned int m23_get_testmode(void)
{
	return m23_pms_test_factor.testmode;
}

void m23_set_testinterval(unsigned int interval)
{
	m23_pms_test_factor.interval = interval;
}

unsigned int m23_get_testinterval(void)
{
	return m23_pms_test_factor.interval;
}


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int m23_pm_ioctl_test (unsigned int cmd, unsigned long arg)
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

			test_factor.interval = m23_pms_test_factor.interval;

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

			m23_pms_test_factor.interval =  test_factor.interval;
			break;
		case PM_GO_TEST:
			result = copy_from_user((void *)&test_factor, (void __user *)arg, sizeof(test_factor));
			if (result) {
				PM_ERROR("PM_GO_TEST - CONFIG DATA COPY FAIL\n");
				break;
			}

			m23_set_testmode(test_factor.testmode);
			break;
		case PM_STOP_TEST:
			m23_set_testmode(0);
			pm_m23_func->set_max_performance();
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

void m23_TestInit(void)
{
	 pm_m23_func = get_m23_pm_func();
	 pm_m23_gov = get_m23_pm_gov();
	m23_pms_test_factor.testmode = 0;
}

static pms_m23_test_t m23_pm_test =
{
	.init = m23_TestInit,
	.set_testmode = m23_set_testmode,
	.get_testmode = m23_get_testmode,
	.set_testinterval = m23_set_testinterval,
	.get_testinterval = m23_get_testinterval,
	.test_func = m23_test_func,
	.test_boot = m23_test_boot,
	.ioctl = m23_pm_ioctl_test,
};

pms_m23_test_t* get_m23_pm_test(void)
{
	return &m23_pm_test;
}


