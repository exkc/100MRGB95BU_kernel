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

#include "pm_o24common.h"



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
static void o24_TimerHandler( struct timer_list * );
static void o24_TimerStart(void);
static void o24_TimerStop(void);


/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
static struct timer_list o24_pm_timer;
static volatile int o24_timer_work = 0;

struct delayed_work o24_avs_cputime_dw;
struct delayed_work o24_avs_coretime_dw;
struct delayed_work o24_maxperf_dw;
extern struct delayed_work o24_avs_cpu_dw;
extern struct delayed_work o24_avs_core_dw;

extern struct workqueue_struct *o24_avscputime_wq;
extern struct workqueue_struct *o24_avscoretime_wq;
extern struct workqueue_struct *o24_avscpu_wq;
extern struct workqueue_struct *o24_avscore_wq;

struct workqueue_struct *o24_maxperf_wq;

/*----------------------------------------------------------------------------------------
  global Functions
  ---------------------------------------------------------------------------------------*/
static int o24_pms_enable = 1;
static int o24_pm_inited = 0;

module_param(o24_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(o24_pms_enable, "o24 pms disable");

static int o24_pms_tfreq = 0;
module_param(o24_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(o24_pms_tfreq, "o24 cpu target freq");

int o24_pms_tcorevol = 0;
int o24_is_prepared = 0;

module_param(o24_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(o24_pms_tcorevol, "o24 pms core volt");


extern int core_avs_volt[6];

extern int o24_tempmax ;
extern int o24_slt_high;/*get in avs_init*/
extern void o24_avs_cpuwork_func(struct work_struct *work);
extern void o24_avs_corework_func(struct work_struct *work);
extern int o24_SetCPUFreq(unsigned int freq);
extern int o24_set_cpu_vid( int level);
extern int o24_SetCoreVal(unsigned int volt, unsigned int ch);



// CPU Governor
static pms_o24_gov_t* 	pm_o24_gov = NULL;
static pms_o24_func_t* pm_o24_func = NULL;
//static pms_o24_cg_t* 	pm_o24_cg = NULL;
static pms_o24_test_t* pm_o24_test = NULL;
static pms_o24_avs_t* 	pm_o24_avs = NULL;
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

static void o24_TimerHandler( struct timer_list * list )
{
	mod_timer(&o24_pm_timer, jiffies + usecs_to_jiffies(pm_o24_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_o24_test->test_func();

	/* Governor */
	pm_o24_gov->check_cpu();

	return;
}

//static void o24_AvsCheckTimerHandler( unsigned long arg )
static void o24_avs_cputimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_o24_avs->set_avs();

	return ;
}

static void o24_avs_coretimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_o24_avs->set_coreavs();

	return ;
}

static void o24_maxperf_func(struct work_struct *work)
{
	if(pm_o24_func->set_max_performance)
	{
		pm_o24_func->set_max_performance();
	}

	return ;
}
static unsigned int o24_GetTargetFreq(void)
{
	return (unsigned int)o24_pms_tfreq;
}

static unsigned int o24_GetTargetCoreVol(void)
{
	return (unsigned int)o24_pms_tcorevol;
}


static int o24_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_o24_func->getfreq();
	pms_status->core_vol = pm_o24_func->getcorevolt();
	pms_status->cpu_on = pm_o24_func->get_cpu_on();
	pms_status->pm_inited = o24_pm_inited;

	return 0;
}

static int o24_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_o24_func->setcorevolt(pms_status->core_vol, 0);
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
int o24_pm_ioctl_main (unsigned int cmd, unsigned long arg)
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
				ret = -EINVAL;
				break;
			}
			o24_GetStatus(&pms_status);
			result = copy_to_user((void __user*)(arg), (void *)(&pms_status), sizeof(pms_status));
			if (result)
			{
				PM_ERROR("PM_GET_STATUS - CONFIG DATA COPY FAIL TO USER\n");
				ret = -EINVAL;
			}
			break;
		case PM_SET_STATUS:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_SET_STATUS - CONFIG DATA COPY FAIL\n");
				ret = -EINVAL;
				break;
			}
			o24_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_o24_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_SET_SAMPLING_RATE:
			pm_o24_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = o24_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_GET_TARGET_COREVOL:
			temp = o24_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_GET_TEST_MODE:
			temp = pm_o24_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_CHECK_INIT:

			PM_NOTI("PM_CHECK_INIT [%d]\n",o24_pm_inited);
			if (o24_pm_inited == 0) {
				o24_pm_inited = 1;
				temp = 0;
			} else {
				temp = 1;
			}
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_CHECK_INIT - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret;
}

static int o24_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	LX_PM_STATUS_T		pms_status;
	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_IORW_INIT:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_IORW_INIT- CONFIG DATA COPY FAIL FROM USER\n");
				ret = -EINVAL;
				break;
			}
			if (o24_pm_inited == 0) {
				o24_pm_inited = 1;
				pms_status.pm_inited = 0;
			} else {
				pms_status.pm_inited = 1;
			}

			result = copy_to_user((void __user*)(arg), (void *)(&pms_status), sizeof(pms_status));
			if (result)
			{
				PM_ERROR("PM_IORW_INIT - CONFIG DATA COPY FAIL TO USER\n");
				ret = -EINVAL;
			}
			break;
		case PM_IORW_COMMAND_GET:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_GET_STATUS- CONFIG DATA COPY FAIL FROM USER\n");
				ret = -EINVAL;
				break;
			}
			o24_GetStatus(&pms_status);
			result = copy_to_user((void __user*)(arg), (void *)(&pms_status), sizeof(pms_status));
			if (result)
			{
				PM_ERROR("PM_GET_STATUS - CONFIG DATA COPY FAIL TO USER\n");
				ret = -EINVAL;
			}
			break;
		case PM_IOW_COMMAND_SET:
			result = copy_from_user((void *)&pms_status, (void __user *)arg, sizeof(pms_status));
			if (result) {
				PM_ERROR("PM_SET_STATUS - CONFIG DATA COPY FAIL\n");
				ret = -EINVAL;
				break;
			}
			o24_SetStatus(&pms_status);
			break;

		default:
			ret = -EINVAL;
			break;
	}


	return ret;
}

static int o24_pm_suspend(void)
{
	pm_status_backup = pm_o24_gov->get_gov();

	pm_o24_gov->set_gov(PMS_GOV_DISABLE);
	pm_o24_gov->set_startup_timer(0);


	/* set 1.2Ghz requested by hw */
	o24_SetCPUFreq(1200);
	/* set 1.02V requested by hw */
	o24_set_cpu_vid(2);
	PM_NOTI("o24_set_cpu_vid\n");
	o24_SetCoreVal(core_avs_volt[CORE_AVS_S],0);

	o24_TimerStop();
	o24_pm_inited = 0;
	return 0;
}

static int o24_pm_resume(void)
{
	o24_is_prepared = 0;
	o24_tempmax = 0;
	cancel_delayed_work_sync(&o24_avs_cpu_dw);
	cancel_delayed_work_sync(&o24_avs_core_dw);
	cancel_delayed_work_sync(&o24_avs_cputime_dw);
	cancel_delayed_work_sync(&o24_avs_coretime_dw);
	cancel_delayed_work_sync(&o24_maxperf_dw);

	pm_o24_avs->reinit();
	pm_o24_func->set_error_state(0);
	pm_o24_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_o24_gov->set_gov(PMS_GOV_DISABLE);
		pm_o24_gov->set_startup_timer(O24_GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		o24_TimerStart();

		PM_NOTI("O24 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_o24_gov->set_gov(pm_status_backup);
	pm_o24_gov->set_startup_timer(O24_GOV_START_DELAY);
	o24_TimerStart();
	queue_delayed_work(o24_maxperf_wq,&o24_maxperf_dw, msecs_to_jiffies(8 * 1000));

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o24_slt_high)
		{
			queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw,
				msecs_to_jiffies(O24_SLT_HIGH_AVS_SET_DELAY * 1000));
			queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw,
				msecs_to_jiffies((O24_SLT_HIGH_AVS_SET_DELAY + 2) * 1000));
		}
		else
		{
			queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw,
				msecs_to_jiffies(O24_SLT_LOW_AVS_SET_DELAY * 1000));
			queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw,
				msecs_to_jiffies((O24_SLT_LOW_AVS_SET_DELAY + 2) * 1000));
		}
	}
	else
	{
		queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw, msecs_to_jiffies(O24_AVS_SET_DELAY * 1000));
		queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw, msecs_to_jiffies((O24_AVS_SET_DELAY + 8) * 1000));
	}
	return 0;
}

static int o24_pm_prepare(void)
{
	PM_NOTI("PM_prepare\n");
	o24_is_prepared = 1;
	cancel_delayed_work_sync(&o24_avs_cpu_dw);
	cancel_delayed_work_sync(&o24_avs_core_dw);
	cancel_delayed_work_sync(&o24_avs_cputime_dw);
	cancel_delayed_work_sync(&o24_avs_coretime_dw);
	cancel_delayed_work_sync(&o24_maxperf_dw);
	return 0;
}

static void o24_TimerStart(void)
{
	if (o24_timer_work == 0)
	{
		o24_timer_work = 1;
		mod_timer(&o24_pm_timer, jiffies + usecs_to_jiffies(pm_o24_func->get_sampling_rate() * 1000));
	}
}

void o24_TimerStop(void)
{
	if (o24_timer_work)
	{
		o24_timer_work = 0;
		del_timer_sync( &o24_pm_timer );
	}
}

static void o24_TimerInit(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	init_timer( &o24_pm_timer );

#endif

	if ( o24_pm_timer.function == NULL )
	{
		o24_pm_timer.function = o24_TimerHandler;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup( &o24_pm_timer, o24_pm_timer.function, 0);
#endif

	o24_pm_timer.expires = jiffies + usecs_to_jiffies(pm_o24_func->get_sampling_rate() * 1000);

	INIT_DELAYED_WORK(&o24_avs_cputime_dw, o24_avs_cputimework_func);
	INIT_DELAYED_WORK(&o24_avs_coretime_dw, o24_avs_coretimework_func);
	INIT_DELAYED_WORK(&o24_avs_cpu_dw, o24_avs_cpuwork_func);
	INIT_DELAYED_WORK(&o24_avs_core_dw, o24_avs_corework_func);

	INIT_DELAYED_WORK(&o24_maxperf_dw, o24_maxperf_func);

	o24_avscputime_wq = create_freezable_workqueue("avscputime_wq");
	o24_avscoretime_wq = create_freezable_workqueue("avscoretime_wq");
	o24_avscpu_wq = create_freezable_workqueue("avscpu_wq");
	o24_avscore_wq = create_freezable_workqueue("avscore_wq");

	o24_maxperf_wq = create_freezable_workqueue("maxp_wq");

	queue_delayed_work(o24_maxperf_wq,&o24_maxperf_dw, msecs_to_jiffies(8 * 1000));

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o24_slt_high)
		{
			queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw,
				msecs_to_jiffies(O24_SLT_HIGH_AVS_SET_DELAY * 1000));
			queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw,
				msecs_to_jiffies((O24_SLT_HIGH_AVS_SET_DELAY + 2) * 1000));
		}
		else
		{
			queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw,
				msecs_to_jiffies(O24_SLT_LOW_AVS_SET_DELAY * 1000));
			queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw,
				msecs_to_jiffies((O24_SLT_LOW_AVS_SET_DELAY + 2) * 1000));
		}
	}
	else
	{
		queue_delayed_work(o24_avscoretime_wq,&o24_avs_coretime_dw, msecs_to_jiffies(O24_AVS_SET_DELAY * 1000));
		queue_delayed_work(o24_avscputime_wq,&o24_avs_cputime_dw, msecs_to_jiffies((O24_AVS_SET_DELAY + 8) * 1000));
	}
}

static void o24_pm_init(void)
{
	/* initialize pms control base */

	o24_is_prepared = 0;
	pm_o24_avs = get_o24_pm_avs();
	pm_o24_avs->init();

	pm_o24_func = get_o24_pm_func();
	pm_o24_func->init();

	pm_o24_gov = get_o24_pm_gov();
	pm_o24_gov->init();

	pm_o24_test = get_o24_pm_test();
	pm_o24_test->init();


	o24_TimerInit();
	pm_o24_gov->set_startup_timer(O24_GOV_START_DELAY);

	if (o24_pms_enable) {
		/* CPU Governor Start */
		pm_o24_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_o24_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("O24 CPU PMS Governor Don't Start\n");
	}
	o24_TimerStart();

	return;
}

static pms_driver_t o24_pms_driver =
{
	.init = o24_pm_init,
	.ioctl = o24_pm_ioctl,
	.suspend = o24_pm_suspend,
	.resume = o24_pm_resume,
	.prepare = o24_pm_prepare,
};

pms_driver_t* get_o24_pm_driver(void)
{
	return &o24_pms_driver;
}

