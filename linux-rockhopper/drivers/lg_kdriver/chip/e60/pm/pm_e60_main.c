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

#include "pm_e60common.h"



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
static void e60_TimerHandler( unsigned long arg );
static void e60_TimerStart(void);
static void e60_TimerStop(void);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
static struct timer_list e60_pm_timer;
static volatile int e60_timer_work = 0;

struct delayed_work e60_avs_work;
extern struct delayed_work e60_avs_cpuwork;
extern struct delayed_work e60_avs_corework;

extern struct workqueue_struct *avsmain_wq;
extern struct workqueue_struct *avscpu_wq;
extern struct workqueue_struct *avscore_wq;

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int e60_pms_enable = 1;
static int e60_pm_inited = 0;

module_param(e60_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(e60_pms_enable, "e60 pms disable");

static int e60_pms_tfreq = 0;
module_param(e60_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(e60_pms_tfreq, "e60 cpu target freq");

int e60_pms_tcorevol = 0;
int e60_is_prepared = 0;

extern void e60_avs_cpuwork_func(struct work_struct *work);
extern void e60_avs_corework_func(struct work_struct *work);
module_param(e60_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(e60_pms_tcorevol, "e60 pms core volt");

// CPU Governor
static pms_e60_gov_t* 	pm_e60_gov = NULL;
static pms_e60_func_t* pm_e60_func = NULL;
static pms_e60_cg_t* 	pm_e60_cg = NULL;
static pms_e60_test_t* pm_e60_test = NULL;
static pms_e60_avs_t* 	pm_e60_avs = NULL;
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

static void e60_TimerHandler( unsigned long arg )
{
	mod_timer(&e60_pm_timer, jiffies + usecs_to_jiffies(pm_e60_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_e60_test->test_func();

	/* Governor */
	pm_e60_gov->check_cpu();

	return;
}

static void e60_avs_work_func(struct work_struct *work)
{
	pm_e60_avs->set_avs();
	return ;
}


static unsigned int e60_GetTargetFreq(void)
{
	return (unsigned int)e60_pms_tfreq;
}

static unsigned int e60_GetTargetCoreVol(void)
{
	return (unsigned int)e60_pms_tcorevol;
}


static int e60_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_e60_func->getfreq();
	pms_status->core_vol = pm_e60_func->getcorevolt();
	pms_status->cpu_on = pm_e60_func->get_cpu_on();
	pms_status->pm_inited = e60_pm_inited;

	return 0;
}

static int e60_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_e60_func->setfreq(pms_status->cpu_freq);
	}
	else if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_e60_func->setcorevolt(pms_status->core_vol);
	}
	else if( pms_status->sel == PMS_CMD_CORE_SWITCHING_FREQ) {
		pm_e60_func->setcore_switching_freq(pms_status->core_switching_freq);
	}
	else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		e60_pm_inited = pms_status->pm_inited;
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
int e60_pm_ioctl_main (unsigned int cmd, unsigned long arg)
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
			e60_GetStatus(&pms_status);
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
			e60_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_e60_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
			break;
		case PM_SET_SAMPLING_RATE:
			pm_e60_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = e60_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
			break;
		case PM_GET_TARGET_COREVOL:
			temp = e60_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
			break;
		case PM_GET_TEST_MODE:
			temp = pm_e60_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
			break;
		case PM_CHECK_INIT:

			PM_NOTI("PM_CHECK_INIT [%d]\n",e60_pm_inited);
			if (e60_pm_inited == 0) {
				e60_pm_inited = 1;
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

static int e60_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);

	ret = pm_e60_cg->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_e60_test->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_e60_gov->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = e60_pm_ioctl_main(cmd_decode, arg);

    return ret;
}

static int e60_pm_suspend(void)
{
	pm_status_backup = pm_e60_gov->get_gov();

	pm_e60_gov->set_gov(PMS_GOV_DISABLE);
	pm_e60_gov->set_startup_timer(0);

	__pm_e60_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0);
	__pm_e60_set_vol(GPIO_AVS_CORE,CORE_AVS_S,0);

	e60_TimerStop();
	cancel_delayed_work_sync(&e60_avs_work);
	e60_pm_inited = 0;

	return 0;
}

static int e60_pm_resume(void)
{

	e60_is_prepared = 0;
	cancel_delayed_work_sync(&e60_avs_work);
	pm_e60_avs->reinit();
	pm_e60_func->set_error_state(0);
	pm_e60_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_e60_gov->set_gov(PMS_GOV_DISABLE);
		pm_e60_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		e60_TimerStart();

		PM_NOTI("E60 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DFT)
	{
		pm_e60_gov->set_gov(PMS_GOV_DFT);
		pm_e60_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DFT;
		e60_TimerStart();

		PM_NOTI("E60 CPU Governor disable!\n");
		return 0;
	}
	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_e60_gov->set_gov(pm_status_backup);
	pm_e60_gov->set_startup_timer(GOV_START_DELAY);
	e60_TimerStart();
	queue_delayed_work(avsmain_wq,&e60_avs_work, msecs_to_jiffies(E60_AVS_SET_DELAY * 1000));

	return 0;
}

static int e60_pm_prepare(void)
{
	PM_NOTI("PM_prepare\n");
	e60_is_prepared = 1;
	cancel_delayed_work_sync(&e60_avs_cpuwork);
	cancel_delayed_work_sync(&e60_avs_corework);
	cancel_delayed_work_sync(&e60_avs_work);
	return 0;
}
static void e60_TimerStart(void)
{
	if (e60_timer_work == 0)
	{
		e60_timer_work = 1;
		e60_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);
		add_timer( &e60_pm_timer );
	}

}

void e60_TimerStop(void)
{
	if (e60_timer_work)
	{
		e60_timer_work = 0;
		del_timer_sync( &e60_pm_timer );
	}
}

static void e60_TimerInit(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	init_timer( &e60_pm_timer );
#endif

	if ( e60_pm_timer.function == NULL )
	{
		e60_pm_timer.function = e60_TimerHandler;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup(&e60_pm_timer, e60_pm_timer.function, 0);
#endif
	e60_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	INIT_DELAYED_WORK(&e60_avs_work, e60_avs_work_func);
	avsmain_wq = create_freezable_workqueue("avsmain_wq");
	avscpu_wq = create_freezable_workqueue("avscpu_wq");
	avscore_wq = create_freezable_workqueue("avscore_wq");

	queue_delayed_work(avsmain_wq,&e60_avs_work, msecs_to_jiffies(E60_AVS_SET_DELAY * 1000));

	INIT_DELAYED_WORK(&e60_avs_cpuwork, e60_avs_cpuwork_func);
	INIT_DELAYED_WORK(&e60_avs_corework, e60_avs_corework_func);
}

static void e60_pm_init(void)
{
	/* initialize pms control base */
	e60_is_prepared = 0;
	e60_TimerInit();

	pm_e60_avs = get_e60_pm_avs();
	pm_e60_avs->init();

	pm_e60_func = get_e60_pm_func();
	pm_e60_func->init();

	pm_e60_gov = get_e60_pm_gov();
	pm_e60_gov->init();

	pm_e60_test = get_e60_pm_test();
	pm_e60_test->init();

	pm_e60_cg = get_e60_pm_cg();

	pm_e60_gov->set_startup_timer(GOV_START_DELAY);

	if (e60_pms_enable) {
		/* CPU Governor Start */
		pm_e60_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_e60_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("E60LUS CPU PMS Governor Don't Start\n");
	}
	e60_TimerStart();

	return;
}

static pms_driver_t e60_pms_driver =
{
	.init = e60_pm_init,
	.ioctl = e60_pm_ioctl,
	.suspend = e60_pm_suspend,
	.resume = e60_pm_resume,
	.prepare = e60_pm_prepare,
};

pms_driver_t* get_e60_pm_driver(void)
{
	return &e60_pms_driver;
}

