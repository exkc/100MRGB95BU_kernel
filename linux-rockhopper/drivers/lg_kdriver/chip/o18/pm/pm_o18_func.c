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

#include "pm_o18common.h"

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
static DEFINE_SPINLOCK(g_o18_pm_lock);
static DEFINE_SPINLOCK(g_o18_regul_lock);


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define FREQ_SAME				0
#define FREQ_UP					1
#define FREQ_DOWN				2
#define FREQ_ONLY				3
#define VOL_ONLY				4
#define ERROR_MASK			0xffff
#define O18_MODEL_OPT10			5

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


static	pms_o18_regulator_t  _stRegulator[] =
{
	/* vbase== 920 mV */
	{1110,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1090,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1090,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1080,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1070,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1060,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1055,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1045,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1035,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1025,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1015,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1010,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },

	{1000 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 995 ,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 985 ,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 980 ,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 975 ,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 965 ,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 960 ,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 950 ,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 945 ,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 940 ,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 930 ,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 925 ,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 920 ,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 920 ,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 910 ,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 905 ,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 895 ,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 890 ,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 885 ,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 875 ,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 870 ,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 860 ,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 855 ,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 850 ,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 840 ,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 835 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },

	{ 825,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
	{ 815,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
	{ 805,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_03_2,OPERATION_OPMARGIN_VOML },
	{ 795,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
	{ 785,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
	{ 780,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
	{ 770,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
	{ 760,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
	{ 750,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
	{ 745,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
	{ 735,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
	{ 730,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },
}   ;


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

static struct task_struct *regulator_pm_task;
static struct completion   regulator_completion;

static int g_o18_pm_task_disable = 0; // 이 변수는 CM3 RECOVERY용 변수임
static pms_o18_work_t g_o18_pms;
static pms_o18_work_t g_o18_regul;

static unsigned int g_o18_sampling_rate = 20; // 20ms
static unsigned int g_o18_core_vol = 0;

static unsigned int g_o18_err = 0;
static pms_o18_avs_t* pm_o18_avs = NULL;

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


#define CORE_REGULATOR_IDX 2

#define CORE_REGULATOR_DEVICE_ID_TI 0x3E
#define CORE_REGULATOR_DEVICE_ID_MPS 0xc0


static LX_I2C_DEV_HANDLE _i2c_core_regulator_handle;

int CORE_REGUL_WRI2C( UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
    int rc = -1;

	/* detect regulator type (ti/mps) */
	if (regulator_vendor == REGULATOR_TI)
	{
		rc = REG_WriteI2C( CORE_REGULATOR_IDX , CORE_REGULATOR_DEVICE_ID_TI,subaddr, data[0]);
	}
	else if (regulator_vendor == REGULATOR_MPS)
	{
		rc = REG_WriteI2C( CORE_REGULATOR_IDX , CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data[0]);
	}

    return rc;
}

int CORE_REGUL_RDI2C(UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
    int rc = -1;

	/* detect regulator type (ti/mps) */
	if (regulator_vendor == REGULATOR_TI)
	{
		rc = REG_ReadI2C( CORE_REGULATOR_IDX , CORE_REGULATOR_DEVICE_ID_TI,subaddr, data);

	}
	else if (regulator_vendor == REGULATOR_MPS)
	{
		rc = REG_ReadI2C( CORE_REGULATOR_IDX , CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data);
	}

    return rc;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int o18_get_error_state(void)
{
	return g_o18_err;
}

int o18_set_error_state(unsigned int value)
{
	g_o18_err = value;

	return 0;
}

static void o18_set_work(pms_o18_work_t o18_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o18_pm_lock, flags);
	g_o18_pms = o18_work;
	spin_unlock_irqrestore(&g_o18_pm_lock, flags);
}

static void o18_set_regul_work(pms_o18_work_t o18_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o18_regul_lock, flags);
	g_o18_regul = o18_work;
	spin_unlock_irqrestore(&g_o18_regul_lock, flags);
}

static int o18_GetCPUType(void)
{
	int ret = 0;
	pms_o18_avsinto_t info;

	pm_o18_avs = get_o18_pm_avs();
	ret = pm_o18_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int o18_GetCPUOn(void)
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

unsigned int o18_GetCPUFreq(void)
{

	unsigned int MHz = 0;

#ifdef O18_DVFS_ENABLE
	unsigned int KHz = 0;
	KHz = cpufreq_generic_get(0);
	MHz = KHz / 1000;
#else
	MHz = O18_CPU_FREQ_ND;
#endif
	return MHz;
}

int o18_SetCPUFreq(unsigned int freq)
{

	int ret = 0;

#ifdef O18_DVFS_ENABLE
	struct cpufreq_policy *policy;
	policy = cpufreq_cpu_get(0);
	if (policy != NULL)
		ret = cpufreq_driver_target(policy, freq*1000, CPUFREQ_RELATION_H);
#endif
	return ret;
}


int o18_SetCoreSwitchingFreq(unsigned int freq)
{
	int ret = 0;
	UINT8  freq_set = FREQUENCY_CONFIG_400KHZ; /* default */
	unsigned data[5];

	if(freq > 1000 || freq < 250 )
	{
		PM_ERROR("check core switching freq[%d]mV\n",freq);
		return -1;
	}

	if(0){}
	else if(freq >= 1000){ freq_set = FREQUENCY_CONFIG___1MHZ; }
	else if(freq >= 850){ freq_set = FREQUENCY_CONFIG_850KHZ; }
	else if(freq >= 750){ freq_set = FREQUENCY_CONFIG_750KHZ; }
	else if(freq >= 600){ freq_set = FREQUENCY_CONFIG_600KHZ; }
	else if(freq >=	500){ freq_set = FREQUENCY_CONFIG_500KHZ; }
	else if(freq >=	400){ freq_set = FREQUENCY_CONFIG_400KHZ; }
	else if(freq >=	300){ freq_set = FREQUENCY_CONFIG_300KHZ; }
	else if(freq >=	250){ freq_set = FREQUENCY_CONFIG_250KHZ; }

	if(lx_i2c_cfg() & LX_I2C_CFG_LEGACY_MODE)
	{
		_i2c_core_regulator_handle= I2C_DevOpenPriv(0, 0);/* i2c0 */
		I2C_DevSetClock(_i2c_core_regulator_handle,I2C_CLOCK_400KHZ);
	}

	if (regulator_vendor == REGULATOR_TI)
	{
		/* switching frequency of DCDC	*/
		data[0]= freq_set << FREQUENCY_CONFIG_OFFSET;
		CORE_REGUL_WRI2C(FREQUENCY_CONFIG, (UINT8 *)data ,1);

		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else if(regulator_vendor == REGULATOR_MPS)
	{

	}


	return ret;
}



int o18_SetCoreVal(unsigned int volt)
{
	int ret = 0, i = 0;
	pms_o18_regulator_t * regul = NULL ;
	unsigned char data[5];


	if (regulator_vendor == REGULATOR_TI)
	{

		UINT8 vout_set = VOUT_ADJUSTMENT_UP_00; /* 946 mV */
		UINT8 vout_margin_high = VOUT_MARGIN_HIGH_00_0; /* 0% up margin */
		UINT8 vout_margin_low = VOUT_MARGIN_LOW_00_0; /* 0% down margin*/
		UINT8 opmargin	=	OPERATION_OPMARGIN_OFF;


		if(volt > VOUT_ADJUSTMENT_TI_MAX || volt < VOUT_ADJUSTMENT_TI_MIN )
		{
			PM_ERROR("check core volt[%d]mV\n",volt);
			return -1;

		}

		for(i=0; i < sizeof(_stRegulator)/sizeof(pms_o18_regulator_t); i++)
		{
			if(volt > _stRegulator[i].vout_ref)
			{
				if( i == 0)
					regul = &_stRegulator[0];
				else
					regul = &_stRegulator[i-1];
				break;
			}
		}

		if( regul != NULL)
		{
			vout_set = regul->vout_set;
			vout_margin_high = regul->vout_margin_high;
			vout_margin_low = regul->vout_margin_low;
			opmargin = regul->opmargin;
		}
		else
		{
			PM_ERROR("check core volt[%d]mV i[%d]\n",volt,i);
			return -1;
		}

		g_o18_core_vol	= volt;

		if(lx_i2c_cfg() & LX_I2C_CFG_LEGACY_MODE)
		{
			_i2c_core_regulator_handle= I2C_DevOpenPriv(0, 0);/* i2c0 */
			I2C_DevSetClock(_i2c_core_regulator_handle,I2C_CLOCK_400KHZ);
		}

		PM_NOTI("opmargin[%x]\n",opmargin);

		/* switch converter on | turn off output voltage margin function */
		data[0]= OPERATION_ON_OFF | opmargin << OPERATION_OPMARGIN_OFFSET;
		ret = CORE_REGUL_WRI2C(OPERATION, (UINT8 *)data ,1);
		if(ret < 0 )
		{
			PM_NOTI("check hwopt(10) for ti regulator vendor\n");
			return -1;
		}

		data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
		CORE_REGUL_WRI2C(ON_OFF_CONFIG, (UINT8 *)data ,1);

		/* change switching frequency of DCDC from 400khz (default)
		to 500khz as requested by HE */
		data[0]= FREQUENCY_CONFIG_500KHZ << FREQUENCY_CONFIG_OFFSET;
		CORE_REGUL_WRI2C(FREQUENCY_CONFIG, (UINT8 *)data ,1);

		data[0]= vout_margin_high << VOUT_MARGIN_VOMH_OFFSET | vout_margin_low << VOUT_MARGIN_VOML_OFFSET ;
		CORE_REGUL_WRI2C(VOUT_MARGIN,(UINT8 *)data,1);
		PM_NOTI("vout_margin_high[%x] vout_margin_low[%x]\n",vout_margin_high,vout_margin_low);

		data[0]= vout_set;
		CORE_REGUL_WRI2C(VOUT_ADJUSTMENT,(UINT8 *)data,1);
		PM_NOTI("ti volt[%d]mV set[0x%x] opt[%d]\n",volt,vout_set,regulator_vendor);
	}
	else if (regulator_vendor == REGULATOR_MPS)
	{
		if(volt > VOUT_ADJUSTMENT_MPS_MAX || volt < VOUT_ADJUSTMENT_MPS_MIN )
		{
			PM_ERROR("check mps core volt[%d]mV\n",volt);
			return -1;
		}

		data[0]= 1 << VSEL_VBOOT_OFFSET || VSEL_OUTREF_945MV << VSEL_OUTREF_OFFSET;
		ret = CORE_REGUL_WRI2C(VSEL, (UINT8 *)data ,1);
		if(ret < 0 )
		{
			PM_NOTI("check hwopt(10) for mps regulator vendor\n");
			return -1;
		}

		if( volt >	VSEL_OUTREF_BASEMV )
		{
			CORE_REGUL_RDI2C(SYSCTRL1, data ,1);

			data[0] |= 1 << SYSCTRL1_EN_OFFSET | 1 << SYSCTRL1_GOBIT_OFFSET;
			PM_NOTI("sysctrl1  data[%x] \n",data[0]);
			CORE_REGUL_WRI2C(SYSCTRL1, (UINT8 *)data,1);

			CORE_REGUL_RDI2C(VSEL, data ,1);

			data[0] =  (127 *(volt - VSEL_OUTREF_BASEMV - BOARD_MARGIN_MV )/950) << VSEL_OUTREF_OFFSET & 0xff;
			data[0] &=  ~(1 << VSEL_VBOOT_OFFSET) ;

			PM_NOTI("mps volt[%d]mV set[0x%x] opt[%d]\n",volt,data[0],regulator_vendor);
			CORE_REGUL_WRI2C(VSEL, (UINT8 *)data ,1);
		}
		else
		{
			PM_NOTI("check mps volt[%d]mV \n",volt);
		}
	}


	return ret;
}
unsigned int o18_GetCoreVal(void)
{
	unsigned int mV = g_o18_core_vol;
	return mV;
}


static unsigned int o18_get_sampling_rate(void)
{
	return g_o18_sampling_rate;
}

static int o18_set_sampling_rate(unsigned int ms)
{
	g_o18_sampling_rate = ms;

	return 0;
}

static int o18_pm_task_dvfs(pms_o18_work_t *pms_o18_work)
{
	int ret = 0;
#ifdef O18_DVFS_ENABLE
	struct cpufreq_policy *policy;
	if ((pms_o18_work->do_dvfs == 1) || (pms_o18_work->do_dvfs == 2))
	{
		pms_o18_work->do_dvfs = 0;
		policy = cpufreq_cpu_get(0);
		if (policy != NULL)
			ret = cpufreq_driver_target(policy, pms_o18_work->target_freq*1000, CPUFREQ_RELATION_H);
		else
			ret = 1;

		if(ret != 0)
			o18_set_error_state(0xF << 28 | pms_o18_work->target_freq << 16 | (ERROR_MASK & ret));
	}
	else if (pms_o18_work->do_dvfs == 3)
	{
		pms_o18_work->do_dvfs = 0;
		PM_DEBUG_PRINT("FREQ %ukHz\n",pms_o18_work->target_freq);
		ret = o18_SetCPUFreq(pms_o18_work->target_freq);
		if(ret != 0)
			o18_set_error_state(0xF << 28 | pms_o18_work->target_freq << 16 | (ERROR_MASK & ret));
	}
#endif
	return ret;
}

static int o18_pm_task_hotplug(pms_o18_work_t *pms_o18_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_o18_work->do_hotplug && (o18_get_error_state() == 0))
	{
		pms_o18_work->do_hotplug = 0;

		PM_DEBUG_PRINT("HOTPLUG DO cpu%u:%u\n",pms_o18_work->core_n,pms_o18_work->core_onoff);

		if (pms_o18_work->core_onoff == 0)
		{
			if (cpu_online(pms_o18_work->core_n))
			{
				ret = cpu_down(pms_o18_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						o18_set_error_state(0xD << 28 | pms_o18_work->core_n << 24 | pms_o18_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o18_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 1;
					device_unlock(pCpudev);

					if (o18_GetCPUOn() & (1 << pms_o18_work->core_n))
					{
						PM_ERROR("CPU%u POWER do not DOWN\n",pms_o18_work->core_n);
						o18_set_error_state(0xD << 28 | pms_o18_work->core_n << 24 | pms_o18_work->core_onoff << 16 | (ERROR_MASK & ret));
					}
				}
			}
		}
		else
		{
			if (!cpu_online(pms_o18_work->core_n))
			{
				ret = cpu_up(pms_o18_work->core_n);
				if(ret != 0)
				{
					if (ret != -EBUSY)
						o18_set_error_state(0xD << 28 | pms_o18_work->core_n << 24 | pms_o18_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o18_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 0;
					device_unlock(pCpudev);
				}
			}
		}
	}

	return ret;
}

static int o18_pm_task_avs(pms_o18_work_t *pms_o18_work)
{
	int ret = 0;

	if (pms_o18_work->do_avs == 1)
	{
		pms_o18_work->do_avs = 0;
		o18_SetCoreVal(pms_o18_work->target_corevol);
	}
	return ret;
}


void o18_taskdisable_reset(void)
{
	g_o18_pm_task_disable = 0;
}

static void o18_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void o18_lgdtv_pm_task_call(pms_o18_work_t o18work)
{
	o18_set_work(o18work);
	complete(&cpu_hotplug_completion);
}

static void o18_lgdtv_regul_task_reset(void)
{
	reinit_completion(&regulator_completion);
}

static void o18_lgdtv_regul_task_call(pms_o18_work_t o18work)
{
	o18_set_regul_work(o18work);
	complete(&regulator_completion);
}


static int o18_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o18_work_t pms_o18_work;

	PM_NOTI("o18 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o18 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_o18_pm_task_disable == 1)
			continue;

		if (o18_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_o18_pm_lock, flags);
			memcpy((void *)&pms_o18_work, (void *)&g_o18_pms, sizeof(pms_o18_work_t));
			spin_unlock_irqrestore(&g_o18_pm_lock, flags);

			o18_pm_task_dvfs(&pms_o18_work);
			o18_pm_task_hotplug(&pms_o18_work);

#ifndef	ERROR_PRINT_LOOP
			if(o18_get_error_state() != 0)
			{
				PM_DEBUG("GOV[%x]\n", o18_get_error_state());
			}
#endif
		}

#ifdef	ERROR_PRINT_LOOP
		if(o18_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", o18_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}

static int o18_regulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o18_work_t pms_o18_work;

	PM_NOTI("o18_regulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o18_regulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&regulator_completion);
		wait_for_completion(&regulator_completion);

		PM_DEBUG_PRINT("regul task run in cpu%d\n", smp_processor_id());

		if (g_o18_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o18_regul_lock, flags);
		memcpy((void *)&pms_o18_work, (void *)&g_o18_regul, sizeof(pms_o18_work_t));
		spin_unlock_irqrestore(&g_o18_regul_lock, flags);
		o18_pm_task_avs(&pms_o18_work);

		PM_DEBUG_PRINT("REGUL TASK END\n");
	} while (1);

	return 0;
}


void o18_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(o18_lgdtv_pm_task,
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

	if (regulator_pm_task == NULL) {
		init_completion(&regulator_completion);
		regulator_pm_task = kthread_create_on_node(o18_regulator_pm_task,
					NULL,
					cpu,
					"REGUL-PM-TASK/%lu", targetcpu);

		if (likely(!IS_ERR(regulator_pm_task))) {
			kthread_bind(regulator_pm_task, targetcpu);
			wake_up_process(regulator_pm_task);
			PM_NOTI("REGUL-PM-TASK create successed\n");
		} else
			PM_NOTI("REGUL-PM-TASK create failed\n");
	}
}

static void o18_AllCoreOn(void)
{
	pms_o18_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_o18_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			o18_lgdtv_pm_task_call(pms_work);
			msleep(30);		/* max cpu on time */
		}
	}
}

static void o18_SetMaxPerformance(void)
{
	pms_o18_work_t pms_work;

	reinit_completion(&cpu_hotplug_completion);
	reinit_completion(&regulator_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	o18_AllCoreOn();

	memset(&pms_work, 0x0, sizeof(pms_o18_work_t));
	pms_work.target_freq = O18_CPU_FREQ_ND;
	pms_work.target_vol = 0;
	pms_work.do_dvfs = 1;
	pms_work.do_hotplug = 0;
	o18_lgdtv_pm_task_call(pms_work);

	o18_AllCoreOn();
}


void o18_FuncInit(void)
{

	/* o18 DCDC regulater vendor is fixed as TI
		detailed info: http://clm.lge.com/issue/browse/SCDCR-1798 */
	regulator_vendor = REGULATOR_TI;

	o18_pmtask_init();

}

static pms_o18_func_t o18_pm_func =
{
	.init = o18_FuncInit,
	.getfreq = o18_GetCPUFreq,
	.setfreq = o18_SetCPUFreq,
	.setcorevolt = o18_SetCoreVal,
	.setcore_switching_freq = o18_SetCoreSwitchingFreq,
	.getcorevolt = o18_GetCoreVal,
	.get_cpu_on = o18_GetCPUOn,
	.get_cpu_type = o18_GetCPUType,
	.set_max_performance = o18_SetMaxPerformance,
	.run = o18_lgdtv_pm_task_call,
	.run_regul = o18_lgdtv_regul_task_call,
	.reset = o18_lgdtv_pm_task_reset,
	.reset_regul = o18_lgdtv_regul_task_reset,
	.taskdisable_reset = o18_taskdisable_reset,
	.get_sampling_rate = o18_get_sampling_rate,
	.set_sampling_rate = o18_set_sampling_rate,
	.get_error_state = o18_get_error_state,
	.set_error_state = o18_set_error_state,
};

pms_o18_func_t* get_o18_pm_func(void)
{
	return &o18_pm_func;
}

