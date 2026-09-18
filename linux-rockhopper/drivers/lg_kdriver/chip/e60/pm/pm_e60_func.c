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

#include "pm_e60common.h"

#include "reg_ctrl.h"
#include "i2c_core.h"
#include "gpio_core.h"


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
static DEFINE_SPINLOCK(g_e60_pm_lock);


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define FREQ_SAME				0
#define FREQ_UP					1
#define FREQ_DOWN				2
#define FREQ_ONLY				3
#define VOL_ONLY				4
#define ERROR_MASK			0xffff
#define E60_MODEL_OPT10			5

#define REGULATOR_TI 1
#define REGULATOR_MPS 2


/* TI vendor core regulator subddr info  */
#define OPERATION 0x01
	#define OPERATION_OPMARGIN_OFFSET 0x02
	#define OPERATION_OPMARGIN_OFF 0x0
	#define OPERATION_OPMARGIN_VOML 0x5
	#define OPERATION_OPMARGIN_VOMH 0x9
	#define OPERATION_ON_OFF (1 << 7)

#define ON_OFF_CONFIG 0x02
	#define ON_OFF_CONFIG_PU 	(1 << 4)	/* always should be set to 1 */
	#define ON_OFF_CONFIG_CMD 	(1 << 3)	/* act on ON_OFF set to 1 */
	#define ON_OFF_CONFIG_CP 	(1 << 2)	/* act on EN set to 1 */
	#define ON_OFF_CONFIG_PL 	(1 << 1)	/* always should be set to 1 */
	#define ON_OFF_CONFIG_SK 	(1 << 0)	/* always should be set to 1 */

#define	FREQUENCY_CONFIG 0xD3			/* DCDC switch frequency */
	#define	FREQUENCY_CONFIG_OFFSET	(0x0)
	#define FREQUENCY_CONFIG_250KHZ		0x0
	#define FREQUENCY_CONFIG_300KHZ		0x1
	#define FREQUENCY_CONFIG_400KHZ		0x2 	/*default */
	#define FREQUENCY_CONFIG_500KHZ		0x3
	#define FREQUENCY_CONFIG_600KHZ		0x4
	#define FREQUENCY_CONFIG_750KHZ		0x5
	#define FREQUENCY_CONFIG_850KHZ		0x6
	#define FREQUENCY_CONFIG___1MHZ		0x7


#define	VOUT_ADJUSTMENT 0xD4
	#define	VOUT_ADJUSTMENT_VOA_OFFSET (0x0)	/* ouput voltage adjustment */
	#define VOUT_ADJUSTMENT_UP_90		0x1f /* 1030 mV */
	#define VOUT_ADJUSTMENT_UP_82		0x1b /* 1020 mV */
	#define VOUT_ADJUSTMENT_UP_75		0x1a /* 1010 mV */
	#define VOUT_ADJUSTMENT_UP_67		0x19 /* 1005 mV*/
	#define VOUT_ADJUSTMENT_UP_60		0x18 /* 1000 mV*/
	#define VOUT_ADJUSTMENT_UP_52		0x17 /*  990 mV*/
	#define VOUT_ADJUSTMENT_UP_45		0x16 /*  985 mV*/
	#define VOUT_ADJUSTMENT_UP_37		0x15 /*  980 mV*/
	#define VOUT_ADJUSTMENT_UP_30		0x14 /*  970 mV*/
	#define VOUT_ADJUSTMENT_UP_22		0x13 /*  965 mV*/
	#define VOUT_ADJUSTMENT_UP_15		0x12 /*  960 mV*/
	#define VOUT_ADJUSTMENT_UP_07		0x11 /*  950 mV*/
	#define VOUT_ADJUSTMENT_UP_00		0x10 /*  946 mV*/
	#define VOUT_ADJUSTMENT_DN_00		0x0f /*  940 mV*/
	#define VOUT_ADJUSTMENT_DN_07		0x0e /*  930 mV*/
	#define VOUT_ADJUSTMENT_DN_15		0x0d /*  920 mV*/
	#define VOUT_ADJUSTMENT_DN_22		0x0c /*  915 mV*/
	#define VOUT_ADJUSTMENT_DN_30		0x0b /*  910 mV*/
	#define VOUT_ADJUSTMENT_DN_37		0x0a /*  900 mV*/
	#define VOUT_ADJUSTMENT_DN_45		0x09 /*  890 mV*/
	#define VOUT_ADJUSTMENT_DN_52		0x08 /*  885 mV*/
	#define VOUT_ADJUSTMENT_DN_60		0x07 /*  880 mV*/
	#define VOUT_ADJUSTMENT_DN_67		0x06 /*  870 mV*/
	#define VOUT_ADJUSTMENT_DN_75		0x05 /*  865 mV*/
	#define VOUT_ADJUSTMENT_DN_82		0x04 /*  860 mV*/
	#define VOUT_ADJUSTMENT_DN_90		0x00 /*  855 mV*/

#define	VOUT_MARGIN 0xD5
	#define VOUT_MARGIN_HIGH_OFFSET (0x4)	/* ouput margin high adjustment */
	#define VOUT_MARGIN_LOW_OFFSET (0x0)	/* ouput margin low adjustment */
	#define VOUT_MARGIN_HIGH_12_0		0x0f /*  mV*/
	#define VOUT_MARGIN_HIGH_10_9		0x0b /*  mV*/
	#define VOUT_MARGIN_HIGH_09_9 		0x0a /*  mV*/
	#define VOUT_MARGIN_HIGH_08_8		0x09 /*  mV*/
	#define VOUT_MARGIN_HIGH_07_7		0x08 /*  mV*/
	#define VOUT_MARGIN_HIGH_06_7		0x07 /*  mV*/
	#define VOUT_MARGIN_HIGH_05_7		0x06 /*  mV*/
	#define VOUT_MARGIN_HIGH_04_7		0x05 /*  mV*/
	#define VOUT_MARGIN_HIGH_03_7		0x04 /*  mV*/
	#define VOUT_MARGIN_HIGH_02_8		0x03 /*  mV*/
	#define VOUT_MARGIN_HIGH_01_8		0x02 /*  mV*/
	#define VOUT_MARGIN_HIGH_00_9		0x01 /*  mV*/
	#define VOUT_MARGIN_HIGH_00_0		0x00 /*  mV*/
	#define VOUT_MARGIN_LOW_00_0		0x00 /*  mV*/
	#define VOUT_MARGIN_LOW_01_1		0x01 /*  mV*/
	#define VOUT_MARGIN_LOW_02_1 		0x02 /*  mV*/
	#define VOUT_MARGIN_LOW_03_2		0x03 /*  mV*/
	#define VOUT_MARGIN_LOW_04_2		0x04 /*  mV*/
	#define VOUT_MARGIN_LOW_05_2		0x05 /*  mV*/
	#define VOUT_MARGIN_LOW_06_2		0x06 /*  mV*/
	#define VOUT_MARGIN_LOW_07_1		0x07 /*  mV*/
	#define VOUT_MARGIN_LOW_08_1		0x08 /*  mV*/
	#define VOUT_MARGIN_LOW_09_0		0x09 /*  mV*/
	#define VOUT_MARGIN_LOW_09_9		0x0a /*  mV*/
	#define VOUT_MARGIN_LOW_10_7		0x0b /*  mV*/
	#define VOUT_MARGIN_LOW_11_0		0x0f /*  mV*/

	#define VOUT_MARGIN_VOMH_OFFSET (4) /* voltage margin high*/
	#define VOUT_MARGIN_VOML_OFFSET (0) /* voltage margin low */

	#define VOUT_ADJUSTMENT_TI_MAX			1135 //mV
	#define VOUT_ADJUSTMENT_TI_MIN			 745 //mV

	/* MPS vendor core regulator subddr info  */

#define	VSEL 0x00
	#define VSEL_VBOOT_OFFSET	 	(0x7)	/* feedback contorl enable bit */
	#define VSEL_OUTREF_OFFSET		(0x0)	/* output voltage reference  */
	#define VSEL_OUTREF_600MV		(0x0)
	#define VSEL_OUTREF_945MV		(0x2e)
	#define VSEL_OUTREF_BASEMV		(600)
	#define BOARD_MARGIN_MV			(0)	/* board margin 0 mV */


#define	SYSCTRL1 0x01
	#define SYSCTRL1_EN_OFFSET	 		(0x7)	/* feedback contorl enable bit */
	#define SYSCTRL1_GOBIT_OFFSET		(0x6)	/* output voltage reference  */
	#define SYSCTRL1_SLEWRATE_OFFSET	(0x3)	/* output voltage reference  */
	#define SYSCTRL1_OVP_OFFSET			(0x2)	/* over voltage protection mode */
	#define SYSCTRL1_OVC_OFFSET			(0x1)	/* over current protection mode	*/

	#define SYSCTRL1_SLEWRATE_40000	0x0
	#define SYSCTRL1_SLEWRATE_30000	0x1
	#define SYSCTRL1_SLEWRATE_20000	0x2
	#define SYSCTRL1_SLEWRATE_10000	0x3
	#define SYSCTRL1_SLEWRATE_5000	0x3
	#define SYSCTRL1_SLEWRATE_2500	0x3
	#define SYSCTRL1_SLEWRATE_1250	0x3
	#define SYSCTRL1_SLEWRATE_625	0x3

#define	SYSCTRL2 0x02
	#define SYSCTRL2_SWITCHING_FREQ_OFFSET	 		(0x4)	/* operation switching freq  */

#define	OUTCURRENT 	0x03
	#define OUTCURRENT_OFFSET			(0x0)		/* operation current  */

#define	OUTVOLT 	0x04
	#define OUTVOLT_OFFSET				(0x0)		/* operation voltage  */

#define VOUT_ADJUSTMENT_MPS_MAX 		1550 //mV
#define VOUT_ADJUSTMENT_MPS_MIN 		 600 //mV




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


static int g_e60_pm_task_disable = 0; // 이 변수는 CM3 RECOVERY용 변수임
static pms_e60_work_t g_e60_pms;

static unsigned int g_e60_sampling_rate = 20; // 20ms
static unsigned int g_e60_core_vol = 0;

static unsigned int g_e60_err = 0;
static pms_e60_avs_t* pm_e60_avs = NULL;

static unsigned int regulator_vendor ;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/


#define E60_CORE_REGULATOR_IDX 2

#define E60_CORE_REGULATOR_DEVICE_ID_TI 0x3E
#define E60_CORE_REGULATOR_DEVICE_ID_MPS 0xc0



int E60_CORE_REGUL_WRI2C( UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
    int rc = -1;

	/* detect regulator type (ti/mps) */
	if (regulator_vendor == REGULATOR_TI)
	{
		rc = REG_WriteI2C( E60_CORE_REGULATOR_IDX , E60_CORE_REGULATOR_DEVICE_ID_TI,subaddr, data[0]);
	}
	else if (regulator_vendor == REGULATOR_MPS)
	{
		rc = REG_WriteI2C( E60_CORE_REGULATOR_IDX , E60_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data[0]);
	}

    return rc;
}

int E60_CORE_REGUL_RDI2C(UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
    int rc = -1;

	/* detect regulator type (ti/mps) */
	if (regulator_vendor == REGULATOR_TI)
	{
		rc = REG_ReadI2C( E60_CORE_REGULATOR_IDX , E60_CORE_REGULATOR_DEVICE_ID_TI,subaddr, data);

	}
	else if (regulator_vendor == REGULATOR_MPS)
	{
		rc = REG_ReadI2C( E60_CORE_REGULATOR_IDX , E60_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data);
	}

    return rc;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int e60_get_error_state(void)
{
	return g_e60_err;
}

int e60_set_error_state(unsigned int value)
{
	g_e60_err = value;

	return 0;
}

static void e60_set_work(pms_e60_work_t e60_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_e60_pm_lock, flags);
	g_e60_pms = e60_work;
	spin_unlock_irqrestore(&g_e60_pm_lock, flags);
}

static int e60_GetCPUType(void)
{
	int ret = 0;
	pms_e60_avsinto_t info;

	pm_e60_avs = get_e60_pm_avs();
	ret = pm_e60_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int e60_GetCPUOn(void)
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

unsigned int e60_GetCPUFreq(void)
{

	unsigned int MHz = 0;

#ifdef E60_DVFS_ENABLE
	unsigned int KHz = 0;
	KHz = cpufreq_generic_get(0);
	MHz = KHz / 1000;
#else
	MHz = E60_CPU_FREQ_ND;
#endif
	return MHz;
}

int e60_SetCPUFreq(unsigned int freq)
{

	int ret = 0;

#ifdef E60_DVFS_ENABLE
	struct cpufreq_policy *policy;
	policy = cpufreq_cpu_get(0);
	if (policy != NULL)
		ret = cpufreq_driver_target(policy, freq*1000, CPUFREQ_RELATION_H);
#endif
	if( freq == CPU_DFTFREQ) /* dft mode freq */
	{
		//if(e60_cpu_clk_base != NULL)
		//	writel(0x00000100, o20_cpu_clk_base);
	}
	else if( freq == CPU_NORMALFREQ) /* normal freq case */
	{
		//if(e60_cpu_clk_base != NULL)
		//	writel(0x00000000, o20_cpu_clk_base);
	}
	return ret;
}


int e60_SetCoreSwitchingFreq(unsigned int freq)
{
	return 0;
}



int e60_SetCoreVal(unsigned int volt)
{
	return 0;
}
unsigned int e60_GetCoreVal(void)
{
	unsigned int mV = g_e60_core_vol;
	return mV;
}


static unsigned int e60_get_sampling_rate(void)
{
	return g_e60_sampling_rate;
}

static int e60_set_sampling_rate(unsigned int ms)
{
	g_e60_sampling_rate = ms;

	return 0;
}

static int e60_pm_task_dvfs(pms_e60_work_t *pms_e60_work)
{
	int ret = 0;
#ifdef E60_DVFS_ENABLE
	struct cpufreq_policy *policy;
	if ((pms_e60_work->do_dvfs == 1) || (pms_e60_work->do_dvfs == 2))
	{
		pms_e60_work->do_dvfs = 0;
		policy = cpufreq_cpu_get(0);
		if (policy != NULL)
			ret = cpufreq_driver_target(policy, pms_e60_work->target_freq*1000, CPUFREQ_RELATION_H);
		else
			ret = 1;

		if(ret != 0)
			e60_set_error_state(0xF << 28 | pms_e60_work->target_freq << 16 | (ERROR_MASK & ret));
	}
	else if (pms_e60_work->do_dvfs == 3)
	{
		pms_e60_work->do_dvfs = 0;
		PM_DEBUG_PRINT("FREQ %ukHz\n",pms_e60_work->target_freq);
		ret = e60_SetCPUFreq(pms_e60_work->target_freq);
		if(ret != 0)
			e60_set_error_state(0xF << 28 | pms_e60_work->target_freq << 16 | (ERROR_MASK & ret));
	}
#endif
	return ret;
}

static int e60_pm_task_hotplug(pms_e60_work_t *pms_e60_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_e60_work->do_hotplug && (e60_get_error_state() == 0))
	{
		pms_e60_work->do_hotplug = 0;

		PM_DEBUG_PRINT("HOTPLUG DO cpu%u:%u\n",pms_e60_work->core_n,pms_e60_work->core_onoff);

		if (pms_e60_work->core_onoff == 0)
		{
			if (cpu_online(pms_e60_work->core_n))
			{
				ret = cpu_down(pms_e60_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						e60_set_error_state(0xD << 28 | pms_e60_work->core_n << 24 | pms_e60_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_e60_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 1;
					device_unlock(pCpudev);

					if (e60_GetCPUOn() & (1 << pms_e60_work->core_n))
					{
						PM_ERROR("CPU%u POWER do not DOWN\n",pms_e60_work->core_n);
						e60_set_error_state(0xD << 28 | pms_e60_work->core_n << 24 | pms_e60_work->core_onoff << 16 | (ERROR_MASK & ret));
					}
				}
			}
		}
		else
		{
			if (!cpu_online(pms_e60_work->core_n))
			{
				ret = cpu_up(pms_e60_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						e60_set_error_state(0xD << 28 | pms_e60_work->core_n << 24 | pms_e60_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_e60_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 0;
					device_unlock(pCpudev);
				}
			}
		}
	}

	return ret;
}


void e60_taskdisable_reset(void)
{
	g_e60_pm_task_disable = 0;
}

static void e60_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void e60_lgdtv_pm_task_call(pms_e60_work_t e60work)
{
	e60_set_work(e60work);
	complete(&cpu_hotplug_completion);
}

static void e60_lgdtv_regul_task_reset(void)
{
}

static void e60_lgdtv_regul_task_call(pms_e60_work_t e60work)
{
}


static int e60_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_e60_work_t pms_e60_work;

	PM_NOTI("e60 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("e60 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_e60_pm_task_disable == 1)
			continue;

		if (e60_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_e60_pm_lock, flags);
			memcpy((void *)&pms_e60_work, (void *)&g_e60_pms, sizeof(pms_e60_work_t));
			spin_unlock_irqrestore(&g_e60_pm_lock, flags);

			e60_pm_task_dvfs(&pms_e60_work);
			e60_pm_task_hotplug(&pms_e60_work);

#ifndef	ERROR_PRINT_LOOP
			if(e60_get_error_state() != 0)
			{
				PM_DEBUG("GOV[%x]\n", e60_get_error_state());
			}
#endif
		}

#ifdef	ERROR_PRINT_LOOP
		if(e60_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", e60_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}


void e60_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(e60_lgdtv_pm_task,
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

static void e60_AllCoreOn(void)
{
	pms_e60_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_e60_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			e60_lgdtv_pm_task_call(pms_work);
			msleep(30);		/* max cpu on time */
		}
	}
}

static void e60_SetMaxPerformance(void)
{
	pms_e60_work_t pms_work;

	reinit_completion(&cpu_hotplug_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	e60_AllCoreOn();

	memset(&pms_work, 0x0, sizeof(pms_e60_work_t));
	pms_work.target_freq = E60_CPU_FREQ_ND;
	pms_work.target_vol = 0;
	pms_work.do_dvfs = 1;
	pms_work.do_hotplug = 0;
	e60_lgdtv_pm_task_call(pms_work);

	e60_AllCoreOn();
}


void e60_FuncInit(void)
{

	/* e60 DCDC regulater vendor is fixed as TI
		detailed info: http://clm.lge.com/issue/browse/SCDCR-1798 */
	regulator_vendor = REGULATOR_TI;

	//if(o20_cpu_clk_base == NULL)
	//	o20_cpu_clk_base = ioremap( 0xc9230010, 0x4);
	e60_pmtask_init();

}

static pms_e60_func_t e60_pm_func =
{
	.init = e60_FuncInit,
	.getfreq = e60_GetCPUFreq,
	.setfreq = e60_SetCPUFreq,
	.setcorevolt = e60_SetCoreVal,
	.setcore_switching_freq = e60_SetCoreSwitchingFreq,
	.getcorevolt = e60_GetCoreVal,
	.get_cpu_on = e60_GetCPUOn,
	.get_cpu_type = e60_GetCPUType,
	.set_max_performance = e60_SetMaxPerformance,
	.run = e60_lgdtv_pm_task_call,
	.run_regul = e60_lgdtv_regul_task_call,
	.reset = e60_lgdtv_pm_task_reset,
	.reset_regul = e60_lgdtv_regul_task_reset,
	.taskdisable_reset = e60_taskdisable_reset,
	.get_sampling_rate = e60_get_sampling_rate,
	.set_sampling_rate = e60_set_sampling_rate,
	.get_error_state = e60_get_error_state,
	.set_error_state = e60_set_error_state,
};

pms_e60_func_t* get_e60_pm_func(void)
{
	return &e60_pm_func;
}

