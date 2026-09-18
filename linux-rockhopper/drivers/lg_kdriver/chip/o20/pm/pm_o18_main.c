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
#include "gpio_core.h"

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

#include "pm_o18common.h"



/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PM_USE_KERNEL_FUNC

#undef PM_DEBUG_PRINT_ENABLE
#ifdef PM_DEBUG_PRINT_ENABLE
#define PM_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define PM_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static void o18_TimerHandler( unsigned long arg );
static void o18_TimerStart(void);
static void o18_TimerStop(void);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
static struct timer_list o18_pm_timer;
static volatile int o18_timer_work = 0;

static struct timer_list o18_avscheck_timer;
static volatile int o18_avschecktimer_work = 0;


/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int o18_pms_enable = 1;
static int o18_pm_inited = 0;

module_param(o18_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(o18_pms_enable, "o18 pms disable");

static int o18_pms_tfreq = 0;
module_param(o18_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(o18_pms_tfreq, "o18 cpu target freq");

int o18_pms_tcorevol = 0;
module_param(o18_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(o18_pms_tcorevol, "o18lus pms core volt");


// CPU Governor
static pms_o18_gov_t* 	pm_o18_gov = NULL;
static pms_o18_func_t* pm_o18_func = NULL;
static pms_o18_cg_t* 	pm_o18_cg = NULL;
static pms_o18_test_t* pm_o18_test = NULL;
static pms_o18_avs_t* 	pm_o18_avs = NULL;
static unsigned int 	pm_status_backup;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

static void o18_TimerHandler( unsigned long arg )
{
	mod_timer(&o18_pm_timer, jiffies + usecs_to_jiffies(pm_o18_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_o18_test->test_func();

	/* Governor */
	pm_o18_gov->check_cpu();

	return;
}

static void o18_AvsCheckTimerHandler( unsigned long arg )
{
	/* need to enable after avs range test */
	pm_o18_avs->set_avs();

	return ;
}

static unsigned int o18_GetTargetFreq(void)
{
	return (unsigned int)o18_pms_tfreq;
}

static unsigned int o18_GetTargetCoreVol(void)
{
	return (unsigned int)o18_pms_tcorevol;
}


static int o18_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_o18_func->getfreq();
	pms_status->core_vol = pm_o18_func->getcorevolt();
	pms_status->cpu_on = pm_o18_func->get_cpu_on();
	pms_status->pm_inited = o18_pm_inited;

	return 0;
}

static int o18_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_o18_func->setfreq(pms_status->cpu_freq);
	}
	else if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_o18_func->setcorevolt(pms_status->core_vol);
	}
	else if( pms_status->sel == PMS_CMD_CORE_SWITCHING_FREQ) {
		pm_o18_func->setcore_switching_freq(pms_status->core_switching_freq);
	}
	else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		o18_pm_inited = pms_status->pm_inited;
	} else
		return -1;

	return 0;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o18_pm_ioctl_main (unsigned int cmd, unsigned long arg)
{
	LX_PM_STATUS_T		pms_status;
	unsigned int		temp;

	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_GET_STATUS:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_GET_STATUS- CONFIG DATA COPY FAIL FROM USER\n");
				break;
			}
			o18_GetStatus(&pms_status);
			result = copy_to_user((void __user*)(arg), (void *)(&pms_status), sizeof(pms_status));
			if (result)
				PM_ERROR("PM_GET_STATUS - CONFIG DATA COPY FAIL TO USER\n");
			break;
		case PM_SET_STATUS:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_SET_STATUS - CONFIG DATA COPY FAIL\n");
				break;
			}
			o18_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_o18_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
			break;
		case PM_SET_SAMPLING_RATE:
			pm_o18_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = o18_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
			break;
		case PM_GET_TARGET_COREVOL:
			temp = o18_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
			break;
		case PM_GET_TEST_MODE:
			temp = pm_o18_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
			break;
		case PM_CHECK_INIT:

			PM_ERROR("PM_CHECK_INIT [%d]\n",o18_pm_inited);
			if (o18_pm_inited == 0) {
				o18_pm_inited = 1;
				temp = 0;
			} else {
				temp = 1;
			}
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_CHECK_INIT - DATA COPY FAIL\n");
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret;
}

static int o18_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);

	ret = pm_o18_cg->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o18_test->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o18_gov->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = o18_pm_ioctl_main(cmd_decode, arg);

    return ret;
}

static int o18_pm_suspend(void)
{
	pm_status_backup = pm_o18_gov->get_gov();

	pm_o18_gov->set_gov(PMS_GOV_DISABLE);
	pm_o18_gov->set_startup_timer(0);

	/* need to enable after avs range test */
	#if 0
	/* set max volatage */
	__pm_o18_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
	__pm_o18_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
	#endif

	o18_TimerStop();

	return 0;
}

static int o18_pm_resume(void)
{

	pm_o18_avs->reinit();
	pm_o18_func->set_error_state(0);
	pm_o18_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_o18_gov->set_gov(PMS_GOV_DISABLE);
		pm_o18_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		o18_TimerStart();

		PM_NOTI("O18 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_o18_gov->set_gov(pm_status_backup);
	pm_o18_gov->set_startup_timer(GOV_START_DELAY);
	o18_TimerStart();

	return 0;
}

static void o18_TimerStart(void)
{
	if (o18_timer_work == 0)
	{
		o18_timer_work = 1;
		add_timer( &o18_pm_timer );
	}

	if (o18_avschecktimer_work == 0)
	{
		o18_avschecktimer_work = 1;
		o18_avscheck_timer.expires = jiffies + usecs_to_jiffies(O18_AVS_SET_DELAY * 1000 * 1000);
		add_timer( &o18_avscheck_timer );
	}
}

void o18_TimerStop(void)
{
	if (o18_timer_work)
	{
		o18_timer_work = 0;
		del_timer_sync( &o18_pm_timer );
	}

	if (o18_avschecktimer_work)
	{
		o18_avschecktimer_work = 0;
		del_timer_sync( &o18_avscheck_timer );
	}
}

static void o18_TimerInit(void)
{
	init_timer( &o18_pm_timer );

	if ( o18_pm_timer.function == NULL )
	{
		o18_pm_timer.function = o18_TimerHandler;
	}

	o18_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	init_timer( &o18_avscheck_timer );

	if ( o18_avscheck_timer.function == NULL )
	{
		o18_avscheck_timer.function = o18_AvsCheckTimerHandler;
	}

	o18_avscheck_timer.expires = jiffies + usecs_to_jiffies(O18_AVS_SET_DELAY * 1000 * 1000);


}

static void o18_pm_init(void)
{
	/* initialize pms control base */
	o18_TimerInit();

	pm_o18_avs = get_o18_pm_avs();
	pm_o18_avs->init();

	pm_o18_func = get_o18_pm_func();
	pm_o18_func->init();

	pm_o18_gov = get_o18_pm_gov();
	pm_o18_gov->init();

	pm_o18_test = get_o18_pm_test();
	pm_o18_test->init();

	pm_o18_cg = get_o18_pm_cg();

	pm_o18_gov->set_startup_timer(GOV_START_DELAY);

	if (o18_pms_enable) {
		/* CPU Governor Start */
		pm_o18_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_o18_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("O18LUS CPU PMS Governor Don't Start\n");
	}
	o18_TimerStart();

	return;
}

static pms_driver_t o18_pms_driver =
{
	.init = o18_pm_init,
	.ioctl = o18_pm_ioctl,
	.suspend = o18_pm_suspend,
	.resume = o18_pm_resume,
};

pms_driver_t* get_o18_pm_driver(void)
{
	return &o18_pms_driver;
}

