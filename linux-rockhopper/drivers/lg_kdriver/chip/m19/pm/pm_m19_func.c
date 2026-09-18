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
#include <linux/cpufreq.h>
#include <linux/lg1k/pms.h>
#include <linux/clk.h>

#include "pm_m19common.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef PM_DEBUG_PRINT_ENABLE
#ifdef PM_DEBUG_PRINT_ENABLE
#define PM_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define PM_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_m19_pm_lock);

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define FREQ_SAME				0
#define FREQ_UP					1
#define FREQ_DOWN				2
#define FREQ_ONLY				3
#define VOL_ONLY				4
#define ERROR_MASK			0xffff


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

static struct task_struct *cpu_hotplug_pm_task;
static struct completion   cpu_hotplug_completion;
static int g_m19_pm_task_disable = 0; // 이 변수는 CM3 RECOVERY용 변수임
static pms_m19_work_t g_m19_pms;
static unsigned int g_m19_sampling_rate = 20; // 20ms
static unsigned int g_m19_err = 0;
static pms_m19_avs_t* pm_m19_avs = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int m19_get_error_state(void)
{
	return g_m19_err;
}

int m19_set_error_state(unsigned int value)
{
	g_m19_err = value;

	return 0;
}

static void m19_set_work(pms_m19_work_t m19_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_m19_pm_lock, flags);
	g_m19_pms = m19_work;
	spin_unlock_irqrestore(&g_m19_pm_lock, flags);
}

static int m19_GetCPUType(void)
{
	int ret = 0;
	pms_m19_avsinto_t info;

	pm_m19_avs = get_m19_pm_avs();
	ret = pm_m19_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int m19_GetCPUOn(void)
{
	unsigned int core_on = 1;

#define CPU_ON				1

	if (cpu_online(1) == CPU_ON)
		core_on |= 2;
	if (cpu_online(2) == CPU_ON)
		core_on |= 4;
	if (cpu_online(3) == CPU_ON)
		core_on |= 8;

	return core_on;
}

unsigned int m19_GetCPUFreq(void)
{

	unsigned int MHz = 0;

#ifdef M19_DVFS_ENABLE
	unsigned int KHz = 0;
	KHz = cpufreq_generic_get(0);
	MHz = KHz / 1000;
#else
	MHz = M19_CPU_FREQ_ND;
#endif
	return MHz;
}

int m19_SetCPUFreq(unsigned int freq)
{

	int ret = 0;

#ifdef M19_DVFS_ENABLE
	struct cpufreq_policy *policy;
	policy = cpufreq_cpu_get(0);
	if (policy != NULL)
		ret = cpufreq_driver_target(policy, freq*1000, CPUFREQ_RELATION_H);
#endif
	return ret;
}

static unsigned int m19_get_sampling_rate(void)
{
	return g_m19_sampling_rate;
}

static int m19_set_sampling_rate(unsigned int ms)
{
	g_m19_sampling_rate = ms;

	return 0;
}

static int m19_pm_task_dvfs(pms_m19_work_t *pms_m19_work)
{
	int ret = 0;
#ifdef M19_DVFS_ENABLE
	struct cpufreq_policy *policy;
	if ((pms_m19_work->do_dvfs == 1) || (pms_m19_work->do_dvfs == 2))
	{
		pms_m19_work->do_dvfs = 0;
		policy = cpufreq_cpu_get(0);
		if (policy != NULL)
			ret = cpufreq_driver_target(policy, pms_m19_work->target_freq*1000, CPUFREQ_RELATION_H);
		else
			ret = 1;

		if(ret != 0)
			m19_set_error_state(0xF << 28 | pms_m19_work->target_freq << 16 | (ERROR_MASK & ret));
	}
	else if (pms_m19_work->do_dvfs == 3)
	{
		pms_m19_work->do_dvfs = 0;
		PM_DEBUG_PRINT("FREQ %ukHz\n",pms_m19_work->target_freq);
		ret = m19_SetCPUFreq(pms_m19_work->target_freq);
		if(ret != 0)
			m19_set_error_state(0xF << 28 | pms_m19_work->target_freq << 16 | (ERROR_MASK & ret));
	}
#endif
	return ret;
}

static int m19_pm_task_hotplug(pms_m19_work_t *pms_m19_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_m19_work->do_hotplug && (m19_get_error_state() == 0))
	{
		pms_m19_work->do_hotplug = 0;

		PM_DEBUG_PRINT("HOTPLUG DO cpu%u:%u\n",pms_m19_work->core_n,pms_m19_work->core_onoff);

		if (pms_m19_work->core_onoff == 0)
		{
			if (cpu_online(pms_m19_work->core_n))
			{
				ret = cpu_down(pms_m19_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						m19_set_error_state(0xD << 28 | pms_m19_work->core_n << 24 | pms_m19_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_m19_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 1;
					device_unlock(pCpudev);

					if (m19_GetCPUOn() & (1 << pms_m19_work->core_n))
					{
						PM_ERROR("CPU%u POWER do not DOWN\n",pms_m19_work->core_n);
						m19_set_error_state(0xD << 28 | pms_m19_work->core_n << 24 | pms_m19_work->core_onoff << 16 | (ERROR_MASK & ret));
					}
				}
			}
		}
		else
		{
			if (!cpu_online(pms_m19_work->core_n))
			{
				ret = cpu_up(pms_m19_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						m19_set_error_state(0xD << 28 | pms_m19_work->core_n << 24 | pms_m19_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_m19_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 0;
					device_unlock(pCpudev);
				}
			}
		}
	}

	return ret;
}

void m19_taskdisable_reset(void)
{
	g_m19_pm_task_disable = 0;
}

static void m19_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void m19_lgdtv_pm_task_call(pms_m19_work_t m19work)
{
	m19_set_work(m19work);
	complete(&cpu_hotplug_completion);
}

static int m19_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_m19_work_t pms_m19_work;

	PM_NOTI("m19 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("m19 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_m19_pm_task_disable == 1)
			continue;

		if (m19_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_m19_pm_lock, flags);
			memcpy((void *)&pms_m19_work, (void *)&g_m19_pms, sizeof(pms_m19_work_t));
			spin_unlock_irqrestore(&g_m19_pm_lock, flags);

			m19_pm_task_dvfs(&pms_m19_work);
			m19_pm_task_hotplug(&pms_m19_work);

#ifndef	ERROR_PRINT_LOOP
			if(m19_get_error_state() != 0)
			{
				PM_DEBUG("GOV[%x]\n", m19_get_error_state());
			}
#endif
		}

#ifdef	ERROR_PRINT_LOOP
		if(m19_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", m19_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}

void m19_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(m19_lgdtv_pm_task,
					NULL,
					cpu,
					"LGDTV-PMDRV-TASK/%lu", targetcpu);

		if (likely(!IS_ERR(cpu_hotplug_pm_task))) {
			kthread_bind(cpu_hotplug_pm_task, targetcpu);
			wake_up_process(cpu_hotplug_pm_task);
			PM_NOTI("LGDTV-PM-TASK create successed\n");
		} else
			PM_NOTI("LGDTV-PM-TASK create failed\n");
	}
}

static void m19_AllCoreOn(void)
{
	pms_m19_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_m19_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;

			m19_lgdtv_pm_task_call(pms_work);
			msleep(30);		/* max cpu on time */
		}
	}
}

static void m19_SetMaxPerformance(void)
{
	pms_m19_work_t pms_work;

	reinit_completion(&cpu_hotplug_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	m19_AllCoreOn();

	memset(&pms_work, 0x0, sizeof(pms_m19_work_t));
	pms_work.target_freq = M19_CPU_FREQ_ND;
	pms_work.target_vol = 0;
	pms_work.do_dvfs = 1;
	pms_work.do_hotplug = 0;
	m19_lgdtv_pm_task_call(pms_work);

	m19_AllCoreOn();
}


void m19_FuncInit(void)
{
	m19_pmtask_init();
}

static pms_m19_func_t m19_pm_func =
{
	.init = m19_FuncInit,
	.getfreq = m19_GetCPUFreq,
	.setfreq = m19_SetCPUFreq,
	.get_cpu_on = m19_GetCPUOn,
	.get_cpu_type = m19_GetCPUType,
	.set_max_performance = m19_SetMaxPerformance,
	.run = m19_lgdtv_pm_task_call,
	.reset = m19_lgdtv_pm_task_reset,
	.taskdisable_reset = m19_taskdisable_reset,
	.get_sampling_rate = m19_get_sampling_rate,
	.set_sampling_rate = m19_set_sampling_rate,
	.get_error_state = m19_get_error_state,
	.set_error_state = m19_set_error_state,
};

pms_m19_func_t* get_m19_pm_func(void)
{
	return &m19_pm_func;
}

