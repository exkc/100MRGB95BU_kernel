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

#include "pm_o22common.h"



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
static void o22_TimerHandler( struct timer_list * );
static void o22_TimerStart(void);
static void o22_TimerStop(void);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
static struct timer_list o22_pm_timer;
static volatile int o22_timer_work = 0;

struct delayed_work o22_avs_cputime_dw;
struct delayed_work o22_avs_coretime_dw;
struct delayed_work o22_maxperf_dw;
extern struct delayed_work o22_avs_cpu_dw;

extern struct workqueue_struct *o22_avscputime_wq;
extern struct workqueue_struct *o22_avscoretime_wq;
extern struct workqueue_struct *o22_avscpu_wq;
struct workqueue_struct *o22_maxperf_wq;

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int o22_pms_enable = 1;
static int o22_pm_inited = 0;

module_param(o22_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(o22_pms_enable, "o22 pms disable");

static int o22_pms_tfreq = 0;
module_param(o22_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(o22_pms_tfreq, "o22 cpu target freq");

int o22_pms_tcorevol = 0;
int o22_is_prepared = 0;

module_param(o22_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(o22_pms_tcorevol, "o22 pms core volt");


extern void o22_avs_cpuwork_func(struct work_struct *work);


// CPU Governor
static pms_o22_gov_t* 	pm_o22_gov = NULL;
static pms_o22_func_t* pm_o22_func = NULL;
static pms_o22_cg_t* 	pm_o22_cg = NULL;
static pms_o22_test_t* pm_o22_test = NULL;
static pms_o22_avs_t* 	pm_o22_avs = NULL;
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

static void o22_TimerHandler( struct timer_list * list )
{
	mod_timer(&o22_pm_timer, jiffies + usecs_to_jiffies(pm_o22_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_o22_test->test_func();

	/* Governor */
	pm_o22_gov->check_cpu();

	return;
}

//static void o22_AvsCheckTimerHandler( unsigned long arg )
static void o22_avs_cputimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_o22_avs->set_avs();

	return ;
}

static void o22_avs_coretimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_o22_avs->set_coreavs();

	return ;
}

static void o22_maxperf_func(struct work_struct *work)
{
	if(pm_o22_func->set_max_performance)
	{
		pm_o22_func->set_max_performance();
	}

	return ;
}
static unsigned int o22_GetTargetFreq(void)
{
	return (unsigned int)o22_pms_tfreq;
}

static unsigned int o22_GetTargetCoreVol(void)
{
	return (unsigned int)o22_pms_tcorevol;
}


static int o22_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_o22_func->getfreq();
	pms_status->core_vol = pm_o22_func->getcorevolt();
	pms_status->cpu_on = pm_o22_func->get_cpu_on();
	pms_status->pm_inited = o22_pm_inited;

	return 0;
}

static int o22_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_o22_func->setfreq(pms_status->cpu_freq);
	}
	else if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_o22_func->setcorevolt(pms_status->core_vol, 0);
	}
	else if( pms_status->sel == PMS_CMD_CORE_SWITCHING_FREQ) {
		pm_o22_func->setcore_switching_freq(pms_status->core_switching_freq);
	}
	else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		o22_pm_inited = pms_status->pm_inited;
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
int o22_pm_ioctl_main (unsigned int cmd, unsigned long arg)
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
			o22_GetStatus(&pms_status);
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
			o22_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_o22_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
			break;
		case PM_SET_SAMPLING_RATE:
			pm_o22_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = o22_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
			break;
		case PM_GET_TARGET_COREVOL:
			temp = o22_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
			break;
		case PM_GET_TEST_MODE:
			temp = pm_o22_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
			break;
		case PM_CHECK_INIT:

			PM_NOTI("PM_CHECK_INIT [%d]\n",o22_pm_inited);
			if (o22_pm_inited == 0) {
				o22_pm_inited = 1;
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

static int o22_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);

	ret = pm_o22_cg->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o22_test->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o22_gov->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = o22_pm_ioctl_main(cmd_decode, arg);

    return ret;
}

static int o22_pm_suspend(void)
{
	pm_status_backup = pm_o22_gov->get_gov();

	pm_o22_gov->set_gov(PMS_GOV_DISABLE);
	pm_o22_gov->set_startup_timer(0);

	/* need to enable after avs range test */
	#if 1
	/* set max volatage */
	__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0, 0);
	//__pm_o22_set_vol(GPIO_AVS_CORE,CORE_AVS_S,0, 0);
	#endif

	o22_TimerStop();
	cancel_delayed_work_sync(&o22_avs_cputime_dw);
	cancel_delayed_work_sync(&o22_avs_coretime_dw);
	cancel_delayed_work_sync(&o22_maxperf_dw);
	o22_pm_inited = 0;
	return 0;
}

static int o22_pm_resume(void)
{
	o22_is_prepared = 0;
	cancel_delayed_work_sync(&o22_avs_cputime_dw);
	cancel_delayed_work_sync(&o22_avs_coretime_dw);
	cancel_delayed_work_sync(&o22_maxperf_dw);
	pm_o22_avs->reinit();
	pm_o22_func->set_error_state(0);
	pm_o22_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_o22_gov->set_gov(PMS_GOV_DISABLE);
		pm_o22_gov->set_startup_timer(O22_GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		o22_TimerStart();

		PM_NOTI("O22 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DFT)
	{
		pm_o22_gov->set_gov(PMS_GOV_DFT);
		pm_o22_gov->set_startup_timer(O22_GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DFT;
		o22_TimerStart();

		PM_NOTI("O22 CPU Governor disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_o22_gov->set_gov(pm_status_backup);
	pm_o22_gov->set_startup_timer(O22_GOV_START_DELAY);
	o22_TimerStart();
	queue_delayed_work(o22_maxperf_wq,&o22_maxperf_dw, msecs_to_jiffies(8 * 1000));
	queue_delayed_work(o22_avscputime_wq,&o22_avs_cputime_dw, msecs_to_jiffies(O22_AVS_SET_DELAY * 1000));
	queue_delayed_work(o22_avscoretime_wq,&o22_avs_coretime_dw, msecs_to_jiffies((O22_AVS_SET_DELAY + 8)* 1000));

	return 0;
}

static int o22_pm_prepare(void)
{
	PM_NOTI("PM_prepare\n");
	o22_is_prepared = 1;
	cancel_delayed_work_sync(&o22_avs_cpu_dw);
	cancel_delayed_work_sync(&o22_avs_cputime_dw);
	cancel_delayed_work_sync(&o22_avs_coretime_dw);
	cancel_delayed_work_sync(&o22_maxperf_dw);
	return 0;
}

static void o22_TimerStart(void)
{
	if (o22_timer_work == 0)
	{
		o22_timer_work = 1;
		add_timer( &o22_pm_timer );
	}
}

void o22_TimerStop(void)
{
	if (o22_timer_work)
	{
		o22_timer_work = 0;
		del_timer_sync( &o22_pm_timer );
	}
}

static void o22_TimerInit(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	init_timer( &o22_pm_timer );

#endif

	if ( o22_pm_timer.function == NULL )
	{
		o22_pm_timer.function = o22_TimerHandler;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup( &o22_pm_timer, o22_pm_timer.function, 0);
#endif

	o22_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	INIT_DELAYED_WORK(&o22_avs_cputime_dw, o22_avs_cputimework_func);
	INIT_DELAYED_WORK(&o22_avs_coretime_dw, o22_avs_coretimework_func);
	INIT_DELAYED_WORK(&o22_avs_cpu_dw, o22_avs_cpuwork_func);
	INIT_DELAYED_WORK(&o22_maxperf_dw, o22_maxperf_func);

	o22_avscputime_wq = create_freezable_workqueue("avscputime_wq");
	o22_avscoretime_wq = create_freezable_workqueue("avscoretime_wq");
	o22_avscpu_wq = create_freezable_workqueue("avscpu_wq");
	o22_maxperf_wq = create_freezable_workqueue("maxp_wq");

	queue_delayed_work(o22_maxperf_wq,&o22_maxperf_dw, msecs_to_jiffies(8 * 1000));
	queue_delayed_work(o22_avscputime_wq,&o22_avs_cputime_dw, msecs_to_jiffies(O22_AVS_SET_DELAY * 1000));
	queue_delayed_work(o22_avscoretime_wq,&o22_avs_coretime_dw, msecs_to_jiffies((O22_AVS_SET_DELAY + 8) * 1000));



}

static void o22_pm_init(void)
{
	/* initialize pms control base */

	o22_is_prepared = 0;
	pm_o22_avs = get_o22_pm_avs();
	pm_o22_avs->init();

	pm_o22_func = get_o22_pm_func();
	pm_o22_func->init();

	pm_o22_gov = get_o22_pm_gov();
	pm_o22_gov->init();

	pm_o22_test = get_o22_pm_test();
	pm_o22_test->init();

	pm_o22_cg = get_o22_pm_cg();

	o22_TimerInit();
	pm_o22_gov->set_startup_timer(O22_GOV_START_DELAY);

	if (o22_pms_enable) {
		/* CPU Governor Start */
		pm_o22_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_o22_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("O22 CPU PMS Governor Don't Start\n");
	}
	o22_TimerStart();

	return;
}

static pms_driver_t o22_pms_driver =
{
	.init = o22_pm_init,
	.ioctl = o22_pm_ioctl,
	.suspend = o22_pm_suspend,
	.resume = o22_pm_resume,
	.prepare = o22_pm_prepare,
};

pms_driver_t* get_o22_pm_driver(void)
{
	return &o22_pms_driver;
}

