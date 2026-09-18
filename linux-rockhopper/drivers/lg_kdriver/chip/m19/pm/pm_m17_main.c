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

#include "pm_m17common.h"



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
static void m17_TimerHandler( unsigned long arg );
static void m17_TimerStart(void);
static void m17_TimerStop(void);


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
static struct timer_list m17_pm_timer;
static volatile int m17_timer_work = 0;

static struct timer_list m17_avscheck_timer;
static volatile int m17_avschecktimer_work = 0;


/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/
static int m16p_pms_enable = 1;
static int m17_pm_inited = 0;

module_param(m16p_pms_enable, int, S_IRUGO);
MODULE_PARM_DESC(m16p_pms_enable, "m16+ pms disable");

static int m16p_pms_tfreq = 0;
module_param(m16p_pms_tfreq, int, S_IRUGO);
MODULE_PARM_DESC(m16p_pms_tfreq, "m16+ cpu target freq");

// CPU Governor
static pms_m17_gov_t* 	pm_m17_gov = NULL;
static pms_m17_func_t* pm_m17_func = NULL;
static pms_m17_cg_t* 	pm_m17_cg = NULL;
static pms_m17_test_t* pm_m17_test = NULL;
static pms_m17_avs_t* 	pm_m17_avs = NULL;
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

static void m17_TimerHandler( unsigned long arg )
{
	mod_timer(&m17_pm_timer, jiffies + usecs_to_jiffies(pm_m17_func->get_sampling_rate() * 1000));

	/* Tester */
	pm_m17_test->test_func();

	/* Governor */
	pm_m17_gov->check_cpu();

	return;
}

static void m17_AvsCheckTimerHandler( unsigned long arg )
{
	pm_m17_avs->set_avs();

	return ;
}

static unsigned int m17_GetTargetFreq(void)
{
	return (unsigned int)m16p_pms_tfreq;
}

static int m17_GetStatus(LX_PM_STATUS_T *pms_status)
{
	pms_status->cpu_freq = pm_m17_func->getfreq();
	pms_status->cpu_on = pm_m17_func->get_cpu_on();
	pms_status->pm_inited = m17_pm_inited;

	return 0;
}

static int m17_SetStatus(LX_PM_STATUS_T *pms_status)
{
	if( pms_status->sel == PMS_CMD_CPU_FREQ) {
		pm_m17_func->setfreq(pms_status->cpu_freq);
	} else if( pms_status->sel == PMS_CMD_CHECK_INIT) {
		m17_pm_inited = pms_status->pm_inited;
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
int m17_pm_ioctl_main (unsigned int cmd, unsigned int arg)
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
			m17_GetStatus(&pms_status);
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
			m17_SetStatus(&pms_status);
			break;
		case PM_GET_SAMPLING_RATE:
			temp = pm_m17_func->get_sampling_rate();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_SAMPLING_RATE - DATA COPY FAIL\n");
			break;
		case PM_SET_SAMPLING_RATE:
			pm_m17_func->set_sampling_rate(arg);
			break;
		case PM_GET_TARGET_FREQ:
			temp = m17_GetTargetFreq();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TARGET_FREQ - DATA COPY FAIL\n");
			break;
		case PM_GET_TEST_MODE:
			temp = pm_m17_test->test_boot();
			result = copy_to_user((void __user*)(arg), (void *)(&temp), sizeof(temp));
			if (result)
				PM_ERROR("PM_GET_TEST_MODE - DATA COPY FAIL\n");
			break;
		case PM_CHECK_INIT:

			PM_ERROR("PM_CHECK_INIT [%d]\n",m17_pm_inited);
			if (m17_pm_inited == 0) {
				m17_pm_inited = 1;
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

static int m17_pm_ioctl (unsigned int cmd, unsigned int arg)
{
	unsigned int cmd_decode;
	int ret = 0;

	if ((_IOC_TYPE(cmd) != PM_DEV_MAJOR) || (_IOC_NR(cmd) != 'L'))
		return -EINVAL;

	cmd_decode = _IOC_SIZE(cmd);

	ret = pm_m17_cg->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_m17_test->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = pm_m17_gov->ioctl(cmd_decode, arg);
	if (ret < 0)
		ret = m17_pm_ioctl_main(cmd_decode, arg);

    return ret;
}

static int m17_pm_suspend(void)
{
	pm_status_backup = pm_m17_gov->get_gov();

	pm_m17_gov->set_gov(PMS_GOV_DISABLE);
	pm_m17_gov->set_startup_timer(0);

	if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
	{
		/* set max voltage */
		__pm_m17_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
		__pm_m17_set_vol(GPIO_AVS_CORE,CORE_AVS_S );

	}
	else
	{
		/* set max volatage */
		__pm_m17_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
		__pm_m17_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
	}

	m17_TimerStop();

	return 0;
}

static int m17_pm_resume(void)
{

	pm_m17_func->set_error_state(0);
	pm_m17_func->taskdisable_reset();

	if ((pm_status_backup & PMS_GOV_MASK) == PMS_GOV_DISABLE)
	{
		pm_m17_gov->set_gov(PMS_GOV_DISABLE);
		pm_m17_gov->set_startup_timer(GOV_START_DELAY);
		pm_status_backup = PMS_GOV_DISABLE;
		m17_TimerStart();

		printk("M16 CPU Governor Disable!\n");
		return 0;
	}

	if ((pm_status_backup & PMS_GOV_TOSUSPEND_FLAG) == PMS_GOV_TOSUSPEND_FLAG)
		pm_status_backup = pm_status_backup & PMS_GOV_MASK;

	pm_m17_gov->set_gov(pm_status_backup);
	pm_m17_gov->set_startup_timer(GOV_START_DELAY);
	m17_TimerStart();

	return 0;
}

static void m17_TimerStart(void)
{
	if (m17_timer_work == 0)
	{
		m17_timer_work = 1;
		add_timer( &m17_pm_timer );
	}

	if (m17_avschecktimer_work == 0)
	{
		m17_avschecktimer_work = 1;
		m17_avscheck_timer.expires = jiffies + usecs_to_jiffies(M16PC0_AVS_SET_DELAY * 1000 * 1000);
		add_timer( &m17_avscheck_timer );
	}
}

void m17_TimerStop(void)
{
	if (m17_timer_work)
	{
		m17_timer_work = 0;
		del_timer_sync( &m17_pm_timer );
	}

	if (m17_avschecktimer_work)
	{
		m17_avschecktimer_work = 0;
		del_timer_sync( &m17_avscheck_timer );
	}
}

static void m17_TimerInit(void)
{
	init_timer( &m17_pm_timer );

	if ( m17_pm_timer.function == NULL )
	{
		m17_pm_timer.function = m17_TimerHandler;
	}

	m17_pm_timer.expires = jiffies + usecs_to_jiffies(20 * 1000);

	init_timer( &m17_avscheck_timer );

	if ( m17_avscheck_timer.function == NULL )
	{
		m17_avscheck_timer.function = m17_AvsCheckTimerHandler;
	}

	m17_avscheck_timer.expires = jiffies + usecs_to_jiffies(M16PC0_AVS_SET_DELAY * 1000 * 1000);


}

static void m17_pm_init(void)
{
	/* initialize pms control base */
	m17_TimerInit();

	pm_m17_avs = get_m17_pm_avs();
	pm_m17_avs->init();

	pm_m17_func = get_m17_pm_func();
	pm_m17_func->init();

	pm_m17_gov = get_m17_pm_gov();
	pm_m17_gov->init();

	pm_m17_test = get_m17_pm_test();
	pm_m17_test->init();

	pm_m17_cg = get_m17_pm_cg();

	pm_m17_gov->set_startup_timer(GOV_START_DELAY);

	if (m16p_pms_enable) {
		/* CPU Governor Start */
		pm_m17_gov->set_gov(PMS_GOV_ENABLE);
	} else {
		pm_m17_gov->set_gov(PMS_GOV_DISABLE);
		PM_ERROR("M16PLUS CPU PMS Governor Don't Start\n");
	}
	m17_TimerStart();

	return;
}

static pms_driver_t m17_pms_driver =
{
	.init = m17_pm_init,
	.ioctl = m17_pm_ioctl,
	.suspend = m17_pm_suspend,
	.resume = m17_pm_resume,
};

pms_driver_t* get_m17_pm_driver(void)
{
	return &m17_pms_driver;
}

