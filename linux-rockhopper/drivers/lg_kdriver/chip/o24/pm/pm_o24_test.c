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

#include "pm_o24common.h"

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
static LX_PM_TEST_FACTOR_T o24_pms_test_factor;
static pms_o24_func_t *pm_o24_func;
static pms_o24_gov_t *pm_o24_gov;

static int o24_pms_test = 0;
module_param(o24_pms_test, int, S_IRUGO);
MODULE_PARM_DESC(o24_pms_test, "o24 test boot mode");

static int o24_pms_test_boot_delay = 30;
module_param(o24_pms_test_boot_delay, int, S_IRUGO);
MODULE_PARM_DESC(o24_pms_test_boot_delay, "o24  test boot mode start delay");

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

unsigned int o24_get_testmode(void);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static void o24_test_cpu_random(LX_PM_TEST_FACTOR_T *test_factor)
{
	unsigned long long random;

	unsigned int core_n;
	unsigned int core_onoff;
	static unsigned int core_stats[4] = {1,1,1,1};

	pms_o24_work_t pms_work;

	memset(&pms_work, 0x0, sizeof(pms_o24_work_t));

	random = sched_clock();


	if ((test_factor->testmode == 1) || (test_factor->testmode == 2)) {
		core_n = ((unsigned int)(random) % 2) + 2;
		if (core_stats[core_n] == 1)
			core_onoff = 0;
		else
			core_onoff = 1;

		core_stats[core_n] =  core_onoff;

		pms_work.core_n = core_n;
		pms_work.core_onoff = core_onoff;
		pms_work.do_hotplug = 1;
	}

	pm_o24_func->run(&pms_work);

	return;
}

static void o24_test_freq_random(LX_PM_TEST_FACTOR_T *test_factor)
{
	unsigned long long random;

	unsigned int freq_n;
	static unsigned int freqs[2] = {1400,1200};
	pms_o24_work_t pms_work;
	memset(&pms_work, 0x0, sizeof(pms_o24_work_t));

	random = sched_clock();


	if ((test_factor->testmode == 2 ) || (test_factor->testmode == 3) ) {
		freq_n = ((unsigned int)(random) % 2) ;
		pms_work.do_dvfs = 1;
		pms_work.target_freq = freqs[freq_n] ;
		pm_o24_func->run_clk(&pms_work);
		//pm_o24_func->setfreq(pms_work.target_freq);
	}
	return;
}


static unsigned int o24_test_boot(void)
{
	return (unsigned int)o24_pms_test;
}

void o24_test_func(void)
{
	unsigned int testmode;
	unsigned int count200ms_max = 0;
	static unsigned int count200ms = 0;

	LX_PM_TEST_FACTOR_T *test_factor;

	test_factor = &o24_pms_test_factor;
	testmode = test_factor->testmode;

	if(o24_pms_test)
	{
		testmode = o24_pms_test;
		test_factor->testmode = o24_pms_test;

		if(!pm_o24_gov->get_gov_start())
			return;
		if( pm_o24_gov->get_gov() != PMS_GOV_DISABLE)
			 pm_o24_gov->set_gov(PMS_GOV_DISABLE);
	}
	else if(o24_get_testmode())
	{
		testmode = o24_get_testmode();
		if(!pm_o24_gov->get_gov_start())
			return;
		if( pm_o24_gov->get_gov() != PMS_GOV_DISABLE)
			 pm_o24_gov->set_gov(PMS_GOV_DISABLE);
	}
	else{
		if (testmode == 0 ){
			return;
		}
	}

	if (pm_o24_func->get_sampling_rate() < 200)
		count200ms_max = 200 / pm_o24_func->get_sampling_rate();
	else
		count200ms_max = 1;

	count200ms++;

	if (count200ms >= count200ms_max) {
		count200ms = 0;

		if(testmode ==  1)
		{
			pm_o24_gov->set_mp_enable(1);
			o24_test_cpu_random(test_factor);
		}
		else if(testmode == 2)
		{
			pm_o24_gov->set_mp_enable(1);
		    pm_o24_gov->set_freq_enable(1);
			o24_test_cpu_random(test_factor);
			o24_test_freq_random(test_factor);
		}
		else if(testmode == 3)
        {
		     pm_o24_gov->set_freq_enable(1);
			o24_test_freq_random(test_factor);
		}

	}
	return ;

}

void o24_set_testmode(unsigned int mode)
{
	o24_pms_test_factor.testmode = mode;
}

unsigned int o24_get_testmode(void)
{
	return o24_pms_test_factor.testmode;
}

void o24_set_testinterval(unsigned int interval)
{
	o24_pms_test_factor.interval = interval;
}

unsigned int o24_get_testinterval(void)
{
	return o24_pms_test_factor.interval;
}


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o24_pm_ioctl_test (unsigned int cmd, unsigned long arg)
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

			test_factor.interval = o24_pms_test_factor.interval;

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

			o24_pms_test_factor.interval =  test_factor.interval;
			break;
		case PM_GO_TEST:
			result = copy_from_user((void *)&test_factor, (void __user *)arg, sizeof(test_factor));
			if (result) {
				PM_ERROR("PM_GO_TEST - CONFIG DATA COPY FAIL\n");
				break;
			}

			o24_set_testmode(test_factor.testmode);
			break;
		case PM_STOP_TEST:
			o24_set_testmode(0);
			pm_o24_func->set_max_performance();
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

void o24_TestInit(void)
{
	 pm_o24_func = get_o24_pm_func();
	 pm_o24_gov = get_o24_pm_gov();
	o24_pms_test_factor.testmode = 0;
}

static pms_o24_test_t o24_pm_test =
{
	.init = o24_TestInit,
	.set_testmode = o24_set_testmode,
	.get_testmode = o24_get_testmode,
	.set_testinterval = o24_set_testinterval,
	.get_testinterval = o24_get_testinterval,
	.test_func = o24_test_func,
	.test_boot = o24_test_boot,
	.ioctl = o24_pm_ioctl_test,
};

pms_o24_test_t* get_o24_pm_test(void)
{
	return &o24_pm_test;
}


