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

#include "pm_o20common.h"



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
static void o20_TimerHandler( unsigned long arg );
static void o20_TimerStart(void);
static void o20_TimerStop(void);


struct delayed_work o20_avs_work;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
static struct timer_list o20_pm_timer;
static volatile int o20_timer_work = 0;


/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int o20_pms_enable = 1;
static int o20_pm_inited = 0;

module_param(o20_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(o20_pms_enable, "o20 pms disable");

static int o20_pms_tfreq = 0;
module_param(o20_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(o20_pms_tfreq, "o20 cpu target freq");

int o20_pms_tcorevol = 0;
module_param(o20_pms_tcorevol, int, S_IRUGO);
MODULE_PARM_DESC(o20_pms_tcorevol, "o20 pms core volt");


// CPU Governor
static pms_o20_gov_t* 	pm_o20_gov = NULL;
static pms_o20_func_t* pm_o20_func = NULL;
static pms_o20_cg_t* 	pm_o20_cg = NULL;
static pms_o20_test_t* pm_o20_test = NULL;
static pms_o20_avs_t* 	pm_o20_avs = NULL;
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

static void o20_TimerHandler( unsigned long arg )
{
	mod_timer(&o20_pm_timer, jiffies + usecs_to_jiffies(pm_o20_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_o20_test->test_func();

	/* Governor */
	pm_o20_gov->check_cpu();

	return;
}

//static void o20_AvsCheckTimerHandler( unsigned long arg )
static void o20_avs_work_func(struct work_struct *work)
{
	/* need to enable after avs range test */
	pm_o20_avs->set_avs();

	return ;
}

static unsigned int o20_GetTargetFreq(void)
{
	return (unsigned int)o20_pms_tfreq;
}

static unsigned int o20_GetTargetCoreVol(void)
{
	return (unsigned int)o20_pms_tcorevol;
}


static int o20_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_o20_func->getfreq();
	pms_status->core_vol = pm_o20_func->getcorevolt();
	pms_status->cpu_on = pm_o20_func->get_cpu_on();
	pms_status->pm_inited = o20_pm_inited;

	return 0;
}

static int o20_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_o20_func->setfreq(pms_status->cpu_freq);
	}
	else if( pms_status->sel == PMS_CMD_CORE_VOL) {
		pm_o20_func->setcorevolt(pms_status->core_vol);
	}
	else if( pms_status->sel == PMS_CMD_CORE_SWITCHING_FREQ) {
		pm_o20_func->setcore_switching_freq(pms_status->core_switching_freq);
	}
	else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		o20_pm_inited = pms_status->pm_inited;
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
int o20_pm_ioctl_main (unsigned int cmd, unsigned long arg)
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
			o20_GetStatus(&pms_status);
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
			o20_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_o20_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
			break;
		case PM_SET_SAMPLING_RATE:
			pm_o20_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = o20_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
			break;
		case PM_GET_TARGET_COREVOL:
			temp = o20_GetTargetCoreVol();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_CORE_VOLT - DATA COPY FAIL\n");
			break;
		case PM_GET_TEST_MODE:
			temp = pm_o20_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
			break;
		case PM_CHECK_INIT:

			PM_NOTI("PM_CHECK_INIT [%d]\n",o20_pm_inited);
			if (o20_pm_inited == 0) {
				o20_pm_inited = 1;
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

static int o20_pm_ioctl (unsigned int cmd, unsigned long arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);

	ret = pm_o20_cg->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o20_test->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_o20_gov->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = o20_pm_ioctl_main(cmd_decode, arg);

    return ret;
}

static int o20_pm_suspend(void)
{
	pm_status_backup = pm_o20_gov->get_gov();

	pm_o20_gov->set_gov(PMS_GOV_DISABLE);
	pm_o20_gov->set_startup_timer(0);

	/* need to enable after avs range test */
	#if 0
	/* set max volatage */
	__pm_o20_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
	__pm_o20_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
	#endif

	o20_TimerStop();
	cancel_delayed_work_sync(&o20_avs_work);
	o20_pm_inited = 0;
	return 0;
}

static int o20_pm_resume(void)
{

	cancel_delayed_work_sync(&o20_avs_work);
	pm_o20_avs->reinit();
	pm_o20_func->set_error_state(0);
	pm_o20_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_o20_gov->set_gov(PMS_GOV_DISABLE);
		pm_o20_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		o20_TimerStart();

		PM_NOTI("O20 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DFT)
	{
		pm_o20_gov->set_gov(PMS_GOV_DFT);
		pm_o20_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DFT;
		o20_TimerStart();

		PM_NOTI("O20 CPU Governor disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_o20_gov->set_gov(pm_status_backup);
	pm_o20_gov->set_startup_timer(GOV_START_DELAY);
	o20_TimerStart();
	schedule_delayed_work(&o20_avs_work, msecs_to_jiffies(O20_AVS_SET_DELAY * 1000));

	return 0;
}

static void o20_TimerStart(void)
{
	if (o20_timer_work == 0)
	{
		o20_timer_work = 1;
		add_timer( &o20_pm_timer );
	}
}

void o20_TimerStop(void)
{
	if (o20_timer_work)
	{
		o20_timer_work = 0;
		del_timer_sync( &o20_pm_timer );
	}
}

static void o20_TimerInit(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	init_timer( &o20_pm_timer );

#endif

	if ( o20_pm_timer.function == NULL )
	{
		o20_pm_timer.function = o20_TimerHandler;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup( &o20_pm_timer, o20_pm_timer.function, 0);
#endif

	o20_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	INIT_DELAYED_WORK(&o20_avs_work, o20_avs_work_func);
	schedule_delayed_work(&o20_avs_work, msecs_to_jiffies(O20_AVS_SET_DELAY * 1000));


}

static void o20_pm_init(void)
{
	/* initialize pms control base */

	pm_o20_avs = get_o20_pm_avs();
	pm_o20_avs->init();

	pm_o20_func = get_o20_pm_func();
	pm_o20_func->init();

	pm_o20_gov = get_o20_pm_gov();
	pm_o20_gov->init();

	pm_o20_test = get_o20_pm_test();
	pm_o20_test->init();

	pm_o20_cg = get_o20_pm_cg();

	o20_TimerInit();
	pm_o20_gov->set_startup_timer(GOV_START_DELAY);

	if (o20_pms_enable) {
		/* CPU Governor Start */
		pm_o20_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_o20_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("O20LUS CPU PMS Governor Don't Start\n");
	}
	o20_TimerStart();

	return;
}

static pms_driver_t o20_pms_driver =
{
	.init = o20_pm_init,
	.ioctl = o20_pm_ioctl,
	.suspend = o20_pm_suspend,
	.resume = o20_pm_resume,
};

pms_driver_t* get_o20_pm_driver(void)
{
	return &o20_pms_driver;
}

