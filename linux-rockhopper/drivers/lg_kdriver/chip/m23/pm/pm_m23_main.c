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

#include "pm_m23common.h"



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
static void m23_TimerHandler( struct timer_list * );
static void m23_TimerStart(void);
static void m23_TimerStop(void);


/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
static struct timer_list m23_pm_timer;
static volatile int m23_timer_work = 0;

struct delayed_work m23_avs_cputime_dw;
struct delayed_work m23_avs_coretime_dw;
struct delayed_work m23_maxperf_dw;
extern struct delayed_work m23_avs_cpu_dw;
extern struct delayed_work m23_avs_core_dw;

extern struct workqueue_struct *m23_avscputime_wq;
extern struct workqueue_struct *m23_avscoretime_wq;
extern struct workqueue_struct *m23_avscpu_wq;
extern struct workqueue_struct *m23_avscore_wq;

struct workqueue_struct *m23_maxperf_wq;

/*----------------------------------------------------------------------------------------
  global Functions
  ---------------------------------------------------------------------------------------*/
static int m23_pms_enable = 1;
static int m23_pm_inited = 0;

module_param(m23_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_enable, "m23 pms disable");

static int m23_pms_tfreq = 0;
module_param(m23_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_tfreq, "m23 cpu target freq");

int m23_pms_tcorevol = 0;
int m23_is_prepared = 0;

module_param(m23_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_tcorevol, "m23 pms core volt");


extern int m23_slt_high;/*get in avs_init*/
extern void m23_avs_cpuwork_func(struct work_struct *work);
extern void m23_avs_corework_func(struct work_struct *work);


// CPU Governor
static pms_m23_gov_t* 	pm_m23_gov = NULL;
static pms_m23_func_t* pm_m23_func = NULL;
//static pms_m23_cg_t* 	pm_m23_cg = NULL;
static pms_m23_test_t* pm_m23_test = NULL;
static pms_m23_avs_t* 	pm_m23_avs = NULL;
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

static void m23_TimerHandler( struct timer_list * list )
{
	mod_timer(&m23_pm_timer, jiffies + usecs_to_jiffies(pm_m23_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_m23_test->test_func();

	/* Governor */
	pm_m23_gov->check_cpu();

	return;
}

//static void m23_AvsCheckTimerHandler( unsigned long arg )
static void m23_avs_cputimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_m23_avs->set_avs();

	return ;
}

static void m23_avs_coretimework_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_m23_avs->set_coreavs();

	return ;
}

static void m23_maxperf_func(struct work_struct *work)
{
	if(pm_m23_func->set_max_performance)
	{
		pm_m23_func->set_max_performance();
	}

	return ;
}
static unsigned int m23_GetTargetFreq(void)
{
	return (unsigned int)m23_pms_tfreq;
}

static unsigned int m23_GetTargetCoreVol(void)
{
	return (unsigned int)m23_pms_tcorevol;
}


static int m23_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_m23_func->getfreq();
	pms_status->core_vol = pm_m23_func->getcorevolt();
	pms_status->cpu_on = pm_m23_func->get_cpu_on();
	pms_status->pm_inited = m23_pm_inited;

	return 0;
}

static int m23_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_m23_func->setfreq(pms_status->cpu_freq);
	}
	else if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_m23_func->setcorevolt(pms_status->core_vol, 0);
	}
	else if( pms_status->sel == PMS_CMD_CORE_SWITCHING_FREQ) {
		pm_m23_func->setcore_switching_freq(pms_status->core_switching_freq);
	}
	else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		m23_pm_inited = pms_status->pm_inited;
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
int m23_pm_ioctl_main (unsigned int cmd, unsigned long arg)
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
			m23_GetStatus(&pms_status);
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
			m23_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_m23_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_SET_SAMPLING_RATE:
			pm_m23_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = m23_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_GET_TARGET_COREVOL:
			temp = m23_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_GET_TEST_MODE:
			temp = pm_m23_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
			{
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		case PM_CHECK_INIT:

			PM_NOTI("PM_CHECK_INIT [%d]\n",m23_pm_inited);
			if (m23_pm_inited == 0) {
				m23_pm_inited = 1;
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

static int m23_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);


	switch ( cmd)
	{
		case PM_GET_STATUS:
		case PM_SET_STATUS:
		case PM_GET_SAMPLING_RATE:
		case PM_GET_TARGET_COREVOL:
		case PM_GET_TEST_MODE:
		case PM_CHECK_INIT:
			ret = m23_pm_ioctl_main(cmd_decode, arg);
			break;
		case PM_GET_TEST_FACTOR:
		case PM_SET_TEST_FACTOR:
		case PM_GO_TEST:
		case PM_STOP_TEST:
			ret = pm_m23_test->ioctl(cmd_decode, arg);
			break;

		case PM_CPU_GOV_WORK:
		case PM_GET_CPU_GOV_STATUS:
			ret = pm_m23_gov->ioctl(cmd_decode, arg);
			break;
		default:
			ret = -1;
			break;

	}

	return ret;
}

static int m23_pm_suspend(void)
{
	pm_status_backup = pm_m23_gov->get_gov();

	pm_m23_gov->set_gov(PMS_GOV_DISABLE);
	pm_m23_gov->set_startup_timer(0);

	/* set max volatage */
	__pm_m23_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0, 0);
	__pm_m23_set_vol(GPIO_AVS_CORE,CORE_AVS_S,0, 0);

	m23_TimerStop();
	m23_pm_inited = 0;
	return 0;
}

static int m23_pm_resume(void)
{
	m23_is_prepared = 0;
	cancel_delayed_work_sync(&m23_avs_cpu_dw);
	cancel_delayed_work_sync(&m23_avs_core_dw);
	cancel_delayed_work_sync(&m23_avs_cputime_dw);
	cancel_delayed_work_sync(&m23_avs_coretime_dw);
	cancel_delayed_work_sync(&m23_maxperf_dw);
	pm_m23_avs->reinit();
	pm_m23_func->set_error_state(0);
	pm_m23_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_m23_gov->set_gov(PMS_GOV_DISABLE);
		pm_m23_gov->set_startup_timer(M23_GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		m23_TimerStart();

		PM_NOTI("M23 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DFT)
	{
		pm_m23_gov->set_gov(PMS_GOV_DFT);
		pm_m23_gov->set_startup_timer(M23_GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DFT;
		m23_TimerStart();

		PM_NOTI("M23 CPU Governor disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_m23_gov->set_gov(pm_status_backup);
	pm_m23_gov->set_startup_timer(M23_GOV_START_DELAY);
	m23_TimerStart();
	queue_delayed_work(m23_maxperf_wq,&m23_maxperf_dw, msecs_to_jiffies(8 * 1000));

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(m23_slt_high)
		{
			queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw,
				msecs_to_jiffies(M23_SLT_HIGH_AVS_SET_DELAY * 1000));
			queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw,
				msecs_to_jiffies((M23_SLT_HIGH_AVS_SET_DELAY + 2) * 1000));
		}
		else
		{
			queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw,
				msecs_to_jiffies(M23_SLT_LOW_AVS_SET_DELAY * 1000));
			queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw,
				msecs_to_jiffies((M23_SLT_LOW_AVS_SET_DELAY + 2) * 1000));
		}
	}
	else
	{
		queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw, msecs_to_jiffies(M23_AVS_SET_DELAY * 1000));
		queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw, msecs_to_jiffies((M23_AVS_SET_DELAY + 8) * 1000));
	}
	return 0;
}

static int m23_pm_prepare(void)
{
	PM_NOTI("PM_prepare\n");
	m23_is_prepared = 1;
	cancel_delayed_work_sync(&m23_avs_cpu_dw);
	cancel_delayed_work_sync(&m23_avs_core_dw);
	cancel_delayed_work_sync(&m23_avs_cputime_dw);
	cancel_delayed_work_sync(&m23_avs_coretime_dw);
	cancel_delayed_work_sync(&m23_maxperf_dw);
	return 0;
}

static void m23_TimerStart(void)
{
	if (m23_timer_work == 0)
	{
		m23_timer_work = 1;
		mod_timer(&m23_pm_timer, jiffies + usecs_to_jiffies(20 * 1000));
	}
}

void m23_TimerStop(void)
{
	if (m23_timer_work)
	{
		m23_timer_work = 0;
		del_timer_sync( &m23_pm_timer );
	}
}

static void m23_TimerInit(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	init_timer( &m23_pm_timer );

#endif

	if ( m23_pm_timer.function == NULL )
	{
		m23_pm_timer.function = m23_TimerHandler;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup( &m23_pm_timer, m23_pm_timer.function, 0);
#endif

	m23_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	INIT_DELAYED_WORK(&m23_avs_cputime_dw, m23_avs_cputimework_func);
	INIT_DELAYED_WORK(&m23_avs_coretime_dw, m23_avs_coretimework_func);
	INIT_DELAYED_WORK(&m23_avs_cpu_dw, m23_avs_cpuwork_func);
	INIT_DELAYED_WORK(&m23_avs_core_dw, m23_avs_corework_func);

	INIT_DELAYED_WORK(&m23_maxperf_dw, m23_maxperf_func);

	m23_avscputime_wq = create_freezable_workqueue("avscputime_wq");
	m23_avscoretime_wq = create_freezable_workqueue("avscoretime_wq");
	m23_avscpu_wq = create_freezable_workqueue("avscpu_wq");
	m23_avscore_wq = create_freezable_workqueue("avscore_wq");

	m23_maxperf_wq = create_freezable_workqueue("maxp_wq");

	queue_delayed_work(m23_maxperf_wq,&m23_maxperf_dw, msecs_to_jiffies(8 * 1000));
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(m23_slt_high)
		{
			queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw,
				msecs_to_jiffies(M23_SLT_HIGH_AVS_SET_DELAY * 1000));
			queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw,
				msecs_to_jiffies((M23_SLT_HIGH_AVS_SET_DELAY + 2) * 1000));
		}
		else
		{
			queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw,
				msecs_to_jiffies(M23_SLT_LOW_AVS_SET_DELAY * 1000));
			queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw,
				msecs_to_jiffies((M23_SLT_LOW_AVS_SET_DELAY + 2) * 1000));
		}
	}
	else
	{
		queue_delayed_work(m23_avscoretime_wq,&m23_avs_coretime_dw, msecs_to_jiffies(M23_AVS_SET_DELAY * 1000));
		queue_delayed_work(m23_avscputime_wq,&m23_avs_cputime_dw, msecs_to_jiffies((M23_AVS_SET_DELAY + 8) * 1000));
	}
}

static void m23_pm_init(void)
{
	/* initialize pms control base */

	m23_is_prepared = 0;
	pm_m23_avs = get_m23_pm_avs();
	pm_m23_avs->init();

	pm_m23_func = get_m23_pm_func();
	pm_m23_func->init();

	pm_m23_gov = get_m23_pm_gov();
	pm_m23_gov->init();

	pm_m23_test = get_m23_pm_test();
	pm_m23_test->init();

	//pm_m23_cg = get_m23_pm_cg();

	m23_TimerInit();
	pm_m23_gov->set_startup_timer(M23_GOV_START_DELAY);

	if (m23_pms_enable) {
		/* CPU Governor Start */
		pm_m23_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_m23_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("M23 CPU PMS Governor Don't Start\n");
	}
	m23_TimerStart();

	return;
}

static pms_driver_t m23_pms_driver =
{
	.init = m23_pm_init,
	.ioctl = m23_pm_ioctl,
	.suspend = m23_pm_suspend,
	.resume = m23_pm_resume,
	.prepare = m23_pm_prepare,
};

pms_driver_t* get_m23_pm_driver(void)
{
	return &m23_pms_driver;
}

