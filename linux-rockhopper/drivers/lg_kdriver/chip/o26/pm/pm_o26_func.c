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

#include "pm_o26common.h"

#include "reg_ctrl.h"
#include "i2c_core.h"
#include "gpio_core.h"

#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include <linux/regulator/consumer.h>

extern struct regulator *o26_regulator;
extern struct regulator *o26_coreregulator;

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
static DEFINE_SPINLOCK(g_o26_pm_lock);
static DEFINE_SPINLOCK(g_o26_regul_lock);
static DEFINE_SPINLOCK(g_o26_coreregul_lock);
static DEFINE_SPINLOCK(g_o26_clk_lock);

DEFINE_MUTEX(o26_onoff_mutex);
DEFINE_MUTEX(o26_clk_mutex);
DEFINE_MUTEX(o26_kdrvpm_runtime_mutex);
//static DEFINE_SPINLOCK(g_o26_cpuregul_lock);
static DEFINE_SPINLOCK(g_o26_freq_lock);

static unsigned int o26_regul = 1;

unsigned int o26_is_onoff = 0;

module_param(o26_regul, uint, S_IRUGO);
MODULE_PARM_DESC(o26_gpuNP, "o26_regul");

extern struct device o26_gpiodev;

extern struct gpio_desc *o26_cpuvid0;
extern struct gpio_desc *o26_cpuvid1;


//struct gpio_desc *o26_freqtest = NULL;
/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
#define FREQ_SAME			0
#define FREQ_UP				1
#define FREQ_DOWN			2
#define FREQ_ONLY			3
#define VOL_ONLY			4
#define ERROR_MASK			0xffff
#define O26_MODEL_OPT10			5

#define REGULATOR_NONE			0
#define REGULATOR_TPS549A20 		1
#define REGULATOR_TPS549B22 		2
#define REGULATOR_MPS 			3


/* TPS549A20 , TPS549B22 common */

#define OPERATION			0x01
#define OPERATION_OPMARGIN_OFFSET	0x02
#define OPERATION_OPMARGIN_OFF		0x0
#define OPERATION_OPMARGIN_VOML		0x5
#define OPERATION_OPMARGIN_VOMH		0x9
#define OPERATION_ON_OFF		(1 << 7)

#define ON_OFF_CONFIG			0x02
#define ON_OFF_CONFIG_PU		(1 << 4)	/* always should be set to 1 */
#define ON_OFF_CONFIG_CMD		(1 << 3)	/* act on ON_OFF set to 1 */
#define ON_OFF_CONFIG_CP		(1 << 2)	/* act on EN set to 1 */
#define ON_OFF_CONFIG_PL		(1 << 1)	/* always should be set to 1 */
#define ON_OFF_CONFIG_SK		(1 << 0)	/* always should be set to 1 */

#define	FREQUENCY_CONFIG		0xD3		/* DCDC switch frequency */
#define	FREQUENCY_CONFIG_OFFSET		(0x0)
#define FREQUENCY_CONFIG_250KHZ		0x0
#define FREQUENCY_CONFIG_300KHZ		0x1
#define FREQUENCY_CONFIG_400KHZ		0x2		/*default */
#define FREQUENCY_CONFIG_500KHZ		0x3
#define FREQUENCY_CONFIG_600KHZ		0x4
#define FREQUENCY_CONFIG_750KHZ		0x5
#define FREQUENCY_CONFIG_850KHZ		0x6
#define FREQUENCY_CONFIG___1MHZ		0x7


#define	VOUT_ADJUSTMENT			0xD4
#define	VOUT_ADJUSTMENT_VOA_OFFSET	(0x0)		/* ouput voltage adjustment */
#define VOUT_ADJUSTMENT_UP_90		0x1f		/* 1030 mV */
#define VOUT_ADJUSTMENT_UP_82		0x1b		/* 1020 mV */
#define VOUT_ADJUSTMENT_UP_75		0x1a		/* 1010 mV */
#define VOUT_ADJUSTMENT_UP_67		0x19		/* 1005 mV*/
#define VOUT_ADJUSTMENT_UP_60		0x18		/* 1000 mV*/
#define VOUT_ADJUSTMENT_UP_52		0x17		/*  990 mV*/
#define VOUT_ADJUSTMENT_UP_45		0x16		/*  985 mV*/
#define VOUT_ADJUSTMENT_UP_37		0x15		/*  980 mV*/
#define VOUT_ADJUSTMENT_UP_30		0x14		/*  970 mV*/
#define VOUT_ADJUSTMENT_UP_22		0x13		/*  965 mV*/
#define VOUT_ADJUSTMENT_UP_15		0x12		/*  960 mV*/
#define VOUT_ADJUSTMENT_UP_07		0x11		/*  950 mV*/
#define VOUT_ADJUSTMENT_UP_00		0x10		/*  946 mV*/
#define VOUT_ADJUSTMENT_DN_00		0x0f		/*  940 mV*/
#define VOUT_ADJUSTMENT_DN_07		0x0e		/*  930 mV*/
#define VOUT_ADJUSTMENT_DN_15		0x0d		/*  920 mV*/
#define VOUT_ADJUSTMENT_DN_22		0x0c		/*  915 mV*/
#define VOUT_ADJUSTMENT_DN_30		0x0b		/*  910 mV*/
#define VOUT_ADJUSTMENT_DN_37		0x0a		/*  900 mV*/
#define VOUT_ADJUSTMENT_DN_45		0x09		/*  890 mV*/
#define VOUT_ADJUSTMENT_DN_52		0x08		/*  885 mV*/
#define VOUT_ADJUSTMENT_DN_60		0x07		/*  880 mV*/
#define VOUT_ADJUSTMENT_DN_67		0x06		/*  870 mV*/
#define VOUT_ADJUSTMENT_DN_75		0x05		/*  865 mV*/
#define VOUT_ADJUSTMENT_DN_82		0x04		/*  860 mV*/
#define VOUT_ADJUSTMENT_DN_90		0x00		/*  855 mV*/

#define	VOUT_MARGIN			0xD5
#define VOUT_MARGIN_HIGH_OFFSET		(0x4)		/* ouput margin high adjustment */
#define VOUT_MARGIN_LOW_OFFSET		(0x0)		/* ouput margin low adjustment */
#define VOUT_MARGIN_HIGH_12_0		0x0f		/*  mV*/
#define VOUT_MARGIN_HIGH_10_9		0x0b	    	/*  mV*/
#define VOUT_MARGIN_HIGH_09_9 		0x0a		/*  mV*/
#define VOUT_MARGIN_HIGH_08_8		0x09		/*  mV*/
#define VOUT_MARGIN_HIGH_07_7		0x08		/*  mV*/
#define VOUT_MARGIN_HIGH_06_7		0x07		/*  mV*/
#define VOUT_MARGIN_HIGH_05_7		0x06		/*  mV*/
#define VOUT_MARGIN_HIGH_04_7		0x05		/*  mV*/
#define VOUT_MARGIN_HIGH_03_7		0x04		/*  mV*/
#define VOUT_MARGIN_HIGH_02_8		0x03		/*  mV*/
#define VOUT_MARGIN_HIGH_01_8		0x02		/*  mV*/
#define VOUT_MARGIN_HIGH_00_9		0x01		/*  mV*/
#define VOUT_MARGIN_HIGH_00_0		0x00		/*  mV*/
#define VOUT_MARGIN_LOW_00_0		0x00		/*  mV*/
#define VOUT_MARGIN_LOW_01_1		0x01		/*  mV*/
#define VOUT_MARGIN_LOW_02_1 		0x02		/*  mV*/
#define VOUT_MARGIN_LOW_03_2		0x03		/*  mV*/
#define VOUT_MARGIN_LOW_04_2		0x04		/*  mV*/
#define VOUT_MARGIN_LOW_05_2		0x05		/*  mV*/
#define VOUT_MARGIN_LOW_06_2		0x06		/*  mV*/
#define VOUT_MARGIN_LOW_07_1		0x07		/*  mV*/
#define VOUT_MARGIN_LOW_08_1		0x08		/*  mV*/
#define VOUT_MARGIN_LOW_09_0		0x09		/*  mV*/
#define VOUT_MARGIN_LOW_09_9		0x0a		/*  mV*/
#define VOUT_MARGIN_LOW_10_7		0x0b		/*  mV*/
#define VOUT_MARGIN_LOW_11_0		0x0f		/*  mV*/

#define VOUT_MARGIN_VOMH_OFFSET		(4) 		/* voltage margin high*/
#define VOUT_MARGIN_VOML_OFFSET		(0) 		/* voltage margin low */

/* vref =883 mv in boot debug mode */
#define VOUT_ADJUSTMENT_TI_MAX		990		/*mV*/
#define VOUT_ADJUSTMENT_TI_MIN		650		/*mV*/

/* TPS549B22 only */

#define VOUT_MODE			0x20
#define VOUT_MODE_MODE_OFFSET		(0x5)
#define VOUT_MODE_EXPONENT_OFFSET	(0x0)

#define VOUT_COMMAND			0x21
#define VOUT_COMMAND_H_OFFSET		(0x9)
#define VOUT_COMMAND_L_OFFSET		(0x0)

#define VOUT_MARGIN_HIGH		0x25
#define VOUT_MARGIN_LOW			0x26
#define STATUS_BYTE			0x78

#define MFR_SPECIFIC_01			0xD1
#define MFR_SPECIFIC_01_PGD_OFFSET	(3)
#define MFR_SPECIFIC_01_POD_OFFSET	(0)

#define MFR_SPECIFIC_02			0xD1
#define MFR_SPECIFIC_02_TRK_OFFSET	(7)
#define MFR_SPECIFIC_02_SEQ_OFFSET	(6)
#define MFR_SPECIFIC_02_FSKIPS_OFFSET	(4)
#define MFR_SPECIFIC_02_SST_OFFSET	(2)
#define MFR_SPECIFIC_02_HICLOFF_OFFSET	(1)
#define MFR_SPECIFIC_02_CM_OFFSET	(0)


#define MFR_SPECIFIC_03			0xD3
#define MFR_SPECIFIC_03_DCAP3_OFFSET	(0x7)
#define MFR_SPECIFIC_03_RSCP_OFFSET	(0x4)
#define MFR_SPECIFIC_03_FS_OFFSET	(0x0)

#define MFR_SPECIFIC_03_FS_315K		(0x0)
#define MFR_SPECIFIC_03_FS_425K		(0x1)
#define MFR_SPECIFIC_03_FS_550K		(0x2)
#define MFR_SPECIFIC_03_FS_650K		(0x3)
#define MFR_SPECIFIC_03_FS_825K		(0x4)
#define MFR_SPECIFIC_03_FS_900K		(0x5)
#define MFR_SPECIFIC_03_FS_1025K	(0x6)
#define MFR_SPECIFIC_03_FS_1125K	(0x7)

#define MFR_SPECIFIC_04			0xD4
#define MFR_SPECIFIC_04_D3Sel_OFFSET	(7)
#define MFR_SPECIFIC_04_D3Offset_OFFSET	(5)

#define TPS549B22_VOUT_MAX		1150		/*mV*/
#define TPS549B22_VOUT_MIN		710		/*mV*/


/* MPS vendor core regulator subddr info  */

#define VSEL				0x00
#define VSEL_VBOOT_OFFSET		(0x7)	/* feedback contorl enable bit */
#define VSEL_OUTREF_OFFSET		(0x0)	/* output voltage reference  */

#define SYSCTRL1			0x01
#define SYSCTRL1_EN_OFFSET		(0x7)	/* feedback contorl enable bit */
#define SYSCTRL1_GOBIT_OFFSET		(0x6)	/* output voltage reference  */
#define SYSCTRL1_SLEWRATE_OFFSET	(0x3)	/* output voltage reference  */
#define SYSCTRL1_OVP_OFFSET		(0x2)	/* over voltage protection mode */
#define SYSCTRL1_OVC_OFFSET		(0x1)	/* over current protection mode */
#define SYSCTRL1_MODE_OFFSET		(0x0)	/* over current protection mode */

#define SYSCTRL1_SLEWRATE_40000		(0x0)
#define SYSCTRL1_SLEWRATE_30000		(0x1)
#define SYSCTRL1_SLEWRATE_20000		(0x2)
#define SYSCTRL1_SLEWRATE_10000		(0x3)
#define SYSCTRL1_SLEWRATE_5000		(0x4)
#define SYSCTRL1_SLEWRATE_2500		(0x5)
#define SYSCTRL1_SLEWRATE_1250		(0x6)
#define SYSCTRL1_SLEWRATE_625		(0x7)

#define SYSCTRL2			0x02
#define SYSCTRL2_PG_DEGLITCH_OFFSET	(0x6)
#define SYSCTRL2_PG_DEGLITCH_DFT	(0x3)

#define SYSCTRL2_SWITCHING_FREQ_OFFSET	(0x4)	/* operation switching freq  */
#define SYSCTRL2_SWITCHING_F_1250KHZ	(0x3)
#define SYSCTRL2_SWITCHING_F_1000KHZ	(0x2)
#define SYSCTRL2_SWITCHING_F_750KHZ	(0x1)
#define SYSCTRL2_SWITCHING_F_500KHZ	(0x0)

#define SYSCTRL2_SOFTSTOP_OFFSET	(0x3)
#define SYSCTRL2_SOFTSTOP_DFT		(0x0)

#define SYSCTRL2_CUR_LIMIT_ADJ_OFFSET	(0x0)
#define SYSCTRL2_CUR_LIMIT_DFT		(0x1)


#define REGULATOR_RETRY_CNT		2


#define	OUTCURRENT			0x03
#define OUTCURRENT_OFFSET		(0x0)	/* operation current  */

#define	OUTVOLT				0x04
#define OUTVOLT_OFFSET			(0x0)	/* operation voltage  */

#define VOUT_ADJUSTMENT_MPS_MAX		1000	/*mV*/
#define VOUT_ADJUSTMENT_MPS_MIN		600	/*mV*/


#if 0
void __iomem *o26_clk0_base = NULL;
void __iomem *o26_clk_pdb_base = NULL;
void __iomem *o26_clk_src_base = NULL;
#endif



static  pms_o26_regulator_t  _stsltcpuRegulator[] =
{
	//vref 820mv
    {990,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_12_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {985,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {975,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {965,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {955,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {950,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {940,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {930,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {925,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {915,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {910,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_01_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {900,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {895,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {890,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {880,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {875,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {870,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {865,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {855,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {850,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {845,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {840,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {830,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {825,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {820,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {820,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {815,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {810,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {800,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {795,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {790,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {785,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {775,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {770,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {765,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {760,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {750,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {745,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {735,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
    {730,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
    {720,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
    {710,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
    {705,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
    {695,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
    {690,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
    {680,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
    {670,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
    {665,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
    {660,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
    {650,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },



};


typedef struct
{
	UINT32 vout_ref;
	UINT32 vout_set;
}pms_o26_regulatorB_t;

/* TPS549B22 table */
static  pms_o26_regulatorB_t  _stRegulatorB[] =
{
	/*mv, set*/
	{1150,540},
	{1140,535},
	{1130,530},
	{1120,525},
	{1110,522},
	{1100,517},
	{1090,512},
	{1080,506},
	{1070,501},
	{1060,496},
	{1050,491},
	{1040,488},
	{1030,483},
	{1020,478},
	{1010,473},
	{1000,468},
	{990 ,463},
	{980 ,460},
	{970 ,455},
	{960 ,450},
	{950 ,445},
	{940 ,440},
	{930 ,435},
	{920 ,430},
	{910 ,426},
	{900 ,422},
	{890 ,417},
	{880 ,412},
	{870 ,407},
	{860 ,401},
	{850 ,398},
	{840 ,393},
	{830 ,388},
	{820 ,384},
	{810 ,379},
	{800 ,374},
	{790 ,369},
	{780 ,365},
	{770 ,360},
	{760 ,355},
	{750 ,348},
	{740 ,346},
	{730 ,340},
	{720 ,334},
	{710 ,332},
};

/* MP8876 table */
static  pms_o26_regulatorB_t  _stRegulatorMPS[] =
{
	{1000 ,0x36},
    {995 ,0x35},
    {990 ,0x34},
    {985 ,0x34},
    {980 ,0x33},
    {975 ,0x32},
    {970 ,0x32},
    {965 ,0x31},
    {960 ,0x30},
    {955 ,0x30},
    {950 ,0x2f},
    {945 ,0x2e},
    {940 ,0x2e},
    {935 ,0x2d},
    {930 ,0x2c},
    {925 ,0x2c},
    {920 ,0x2b},
    {915 ,0x2a},
    {910 ,0x2a},
    {905 ,0x29},
    {900 ,0x28},
    {895 ,0x28},
    {890 ,0x27},
    {885 ,0x26},
    {880 ,0x26},
    {875 ,0x25},
    {870 ,0x24},
    {865 ,0x24},
    {860 ,0x23},
    {855 ,0x22},
    {850 ,0x22},
    {845 ,0x21},
    {840 ,0x20},
    {835 ,0x20},
    {830 ,0x1f},
    {825 ,0x1e},
    {820 ,0x1e},
    {815 ,0x1d},
    {810 ,0x1c},
    {805 ,0x1c},
    {800 ,0x1b},
    {795 ,0x1a},
    {790 ,0x1a},
    {785 ,0x19},
    {780 ,0x18},
    {775 ,0x18},
    {770 ,0x17},
    {765 ,0x16},
    {760 ,0x16},
    {755 ,0x15},
    {750 ,0x14},
    {745 ,0x14},
    {740 ,0x13},
    {735 ,0x12},
    {730 ,0x12},
    {725 ,0x11},
    {720 ,0x10},
    {715 ,0x10},
    {710 ,0x0f},
    {705 ,0x0e},
    {700 ,0x0e},
    {695 ,0x0d},
    {690 ,0x0c},
    {685 ,0x0c},
    {680 ,0x0b},
    {675 ,0x0a},
    {670 ,0x0a},
    {665 ,0x09},
    {660 ,0x08},
    {655 ,0x08},
    {650 ,0x07},
    {645 ,0x06},
    {640 ,0x06},
    {635 ,0x05},
    {630 ,0x04},
    {625 ,0x04},
    {620 ,0x03},
    {615 ,0x02},
    {610 ,0x02},
    {605 ,0x01},
    {600 ,0x00},
};


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/

extern unsigned int o26_cpu_avs;
extern unsigned int o26_core_avs;

extern int o26_set_cpu_vid( int level);
extern int o26_set_cpu_vid_slt(int freq);
extern int o26_SetCoreVal(unsigned int volt, unsigned int ch);
extern int o26_SetCpuVal(unsigned int volt, unsigned int ch);
extern unsigned int o26_pm_get_debug_enable(void) ;
extern int o26_pm_set_debug_enable(unsigned int val) ;
/*----------------------------------------------------------------------------------------
  global Functions
  ---------------------------------------------------------------------------------------*/
int O26_CORE_REGUL_WRI2C_SLTCPU( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte);
int O26_CORE_REGUL_RDI2C_SLTCPU(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte);

int O26_CORE_REGUL_WRI2C( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte);
int O26_CORE_REGUL_RDI2C(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte);
int o26_set_error_state(unsigned int value);
unsigned int o26_get_error_state(void);
unsigned int o26_GetCPUOn(void);
unsigned int o26_GetCPUFreq(void);
unsigned int o26_GetCoreVal(void);
int o26_SetCPUFreq(unsigned int freq);
int o26_SetCoreSwitchingFreq(unsigned int freq);
int __O26_TPS549A20_set_volt(unsigned int volt, unsigned int ch);
int __O26_TPS549B22_set_volt(unsigned int volt, unsigned int ch);
int __O26_MPS_set_volt(unsigned int volt, unsigned int ch);
int o26_SetCpuVal(unsigned int volt, unsigned int ch);
int o26_SetCoreVal(unsigned int volt, unsigned int ch);
void o26_taskdisable_reset(void);
void o26_pmtask_init(void);
void o26_set_kdrv_pm_runtime_suspend(void);
void o26_set_kdrv_pm_runtime_resume(void);
void o26_FuncInit(void);

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/

static struct task_struct *cpu_hotplug_pm_task;
static struct completion   cpu_hotplug_completion;

static struct task_struct *clk_pm_task;
static struct completion   clk_completion;

static struct task_struct *regulator_pm_task;
static struct completion   regulator_completion;

static struct task_struct *coreregulator_pm_task;
static struct completion   coreregulator_completion;
static int g_o26_pm_task_disable = 0;
static pms_o26_work_t g_o26_pms;
static pms_o26_work_t g_o26_clk;
static pms_o26_work_t g_o26_regul;
static pms_o26_work_t g_o26_coreregul;

unsigned int g_o26_sampling_rate = 200; // 20ms 200ms
static unsigned int g_o26_core_vol = 0;

static unsigned int g_o26_err = 0;
static pms_o26_avs_t* pm_o26_avs = NULL;
static pms_o26_gov_t* pm_o26_gov = NULL;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/


#define O26_CORE_REGULATOR_IDX			2

#define O26_CPU_REGULATOR_DEVICE_ID_TPS549A20	0x3E
#define O26_CORE_REGULATOR_DEVICE_ID_TPS549A20	0x3E
#define O26_CORE_REGULATOR_DEVICE_ID_TPS549B22	0x3A
#define O26_CORE_REGULATOR_DEVICE_ID_MPS	0xc0


//static LX_I2C_DEV_HANDLE _i2c_core_regulator_handle;

int O26_CORE_REGUL_WRI2C_SLTCPU( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
	int rc = 0;
	rc = REG_WriteI2CL(ch, O26_CPU_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data, nbyte);
	return rc;
}

int O26_CORE_REGUL_RDI2C_SLTCPU(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
	int rc = 0;
		rc = REG_ReadI2CL(ch , O26_CPU_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	return rc;
}

int O26_CORE_REGUL_WRI2C( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (ch == 0 && o26_regul == REGULATOR_TPS549A20)
	{
		rc = REG_WriteI2CL(ch, O26_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data, nbyte);
	}
	else if (ch ==0 && o26_regul == REGULATOR_TPS549B22)
	{
		rc = REG_WriteI2CL(ch, O26_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (ch == 0 && o26_regul == REGULATOR_MPS)
	{
		rc = REG_WriteI2CL(ch, O26_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else if (ch == 1 && o26_regul == REGULATOR_TPS549A20)
	{
		rc = REG_WriteI2CL(ch, O26_CPU_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o26_regul);
	}

	return rc;
}

int O26_CORE_REGUL_RDI2C(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (o26_regul == REGULATOR_TPS549A20)
	{
		rc = REG_ReadI2CL(ch , O26_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	}
	else if (o26_regul == REGULATOR_TPS549B22)
	{
		rc = REG_ReadI2CL(ch, O26_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (o26_regul == REGULATOR_MPS)
	{
		rc = REG_ReadI2CL(ch, O26_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o26_regul);
	}

	return rc;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int o26_get_error_state(void)
{
	return g_o26_err;
}

int o26_set_error_state(unsigned int value)
{
	g_o26_err = value;

	return 0;
}

static void o26_set_work(pms_o26_work_t *o26_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o26_pm_lock, flags);
	memcpy( &g_o26_pms,o26_work , sizeof(pms_o26_work_t));
	spin_unlock_irqrestore(&g_o26_pm_lock, flags);
}

static void o26_set_clk_work(pms_o26_work_t *o26_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o26_clk_lock, flags);
	memcpy( &g_o26_clk, o26_work , sizeof(pms_o26_work_t));
	spin_unlock_irqrestore(&g_o26_clk_lock, flags);
}

static void o26_set_regul_work(pms_o26_work_t * o26_regulwork)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o26_regul_lock, flags);
	memcpy( &g_o26_regul, o26_regulwork , sizeof(pms_o26_work_t));
	spin_unlock_irqrestore(&g_o26_regul_lock, flags);
}

static void o26_set_coreregul_work(pms_o26_work_t * o26_coreregulwork)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o26_coreregul_lock, flags);
	memcpy( &g_o26_coreregul, o26_coreregulwork , sizeof(pms_o26_work_t));
	spin_unlock_irqrestore(&g_o26_coreregul_lock, flags);
}

static int o26_GetCPUType(void)
{
	int ret = 0;
	pms_o26_avsinto_t info;

	pm_o26_avs = get_o26_pm_avs();
	ret = pm_o26_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int o26_GetCPUOn(void)
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

unsigned int o26_cur_freq = 1400;
unsigned int o26_GetCPUFreq(void)
{

	unsigned int MHz = 0;
	MHz = o26_cur_freq;
	return MHz;
}

int o26_SetCPUFreq(unsigned int freq)
{
	#if 0
	int fv_time = 0;


	if(pm_o26_gov != NULL)
		fv_time =  pm_o26_gov->get_fv_time();
	else
		fv_time = 100;

	if(freq == o26_cur_freq)
		return 0;

    if( freq > o26_cur_freq)
    {
	    PM_TRACE("high freq[%d] cur [%d] o26_cpu_avs-1[%d] \n", freq,o26_cur_freq,o26_cpu_avs-1);
		if(o26_cpu_avs >= 1)
		{
			if(lx_board_opt() & LX_BOARD_OPT_SLT)
				o26_set_cpu_vid_slt(freq);
			else
				o26_set_cpu_vid(o26_cpu_avs-1);
		}
		/* hw request  0.1 ms betw clk chang and volt change */
	    usleep_range(fv_time,fv_time);
    }

	//(1) cpu core clock source change ( ---> alive clock(core660))
	if(o26_clk_src_base != NULL)
		writel(0x00000001, o26_clk_src_base);

	//(2) CPU PLL powerdown [3] : 0x0
	if(o26_clk_pdb_base != NULL)
		writel(0x00007FF7, o26_clk_pdb_base);

	if(freq == 1400 && o26_clk0_base != NULL)
	{
		//gpiod_direction_output(o26_freqtest,1);
		//(3) freq setting change
		writel(0x000D455A, o26_clk0_base);
		writel(0x1005B002, o26_clk0_base + 4);
		writel(0x00000001, o26_clk0_base + 8);

	}
	else if(freq == 1200 && o26_clk0_base != NULL)
	{
		//gpiod_direction_output(o26_freqtest,0);
		//(3) freq setting change
		writel(0x000B444A, o26_clk0_base);
		writel(0x1005B002, o26_clk0_base + 4);
		writel(0x00000001, o26_clk0_base + 8);
	}

	//(4) CPU PLL power up
	if(o26_clk_pdb_base != NULL)
		writel(0x00007FFF, o26_clk_pdb_base);

	//(5) Wait 100us
	usleep_range(150,150);

	//(6) clock change to CPU PLL
	if(o26_clk_src_base != NULL)
		writel(0x00000000, o26_clk_src_base);

    if(freq < o26_cur_freq)
    {
	    PM_TRACE("low freq[%d] cur [%d] o26_cpu_avs[%d] \n", freq,o26_cur_freq,o26_cpu_avs);

		/* hw request  0.1 ms betw clk chang and volt change */
	    usleep_range(fv_time,fv_time);
		if(o26_cpu_avs)
		{
			if(lx_board_opt() & LX_BOARD_OPT_SLT)
				o26_set_cpu_vid_slt(freq);
			else
				o26_set_cpu_vid(o26_cpu_avs);
		}
    }

	o26_cur_freq = freq;
	if(pm_o26_gov != NULL && pm_o26_gov->get_freq_debug_enable() )
		PM_NOTI(" %d freq\n", freq);

	#endif

	return 0;
}


int o26_SetCoreSwitchingFreq(unsigned int freq)
{
	int ret = 0;
	UINT8  freq_set = FREQUENCY_CONFIG_400KHZ; /* default */
	unsigned data[5];

	if(freq > 1000 || freq < 250 )
	{
		PM_ERROR("check core switching freq[%d]mV\n",freq);
		return -1;
	}
	if(o26_regul == REGULATOR_TPS549B22)
	{

		if(0){}
		else if(freq >= 1125){ freq_set = MFR_SPECIFIC_03_FS_1125K; }
		else if(freq >= 1025){ freq_set = MFR_SPECIFIC_03_FS_1025K; }
		else if(freq >= 900){ freq_set = MFR_SPECIFIC_03_FS_900K; }
		else if(freq >= 825){ freq_set = MFR_SPECIFIC_03_FS_825K; }
		else if(freq >= 650){ freq_set = MFR_SPECIFIC_03_FS_650K; }
		else if(freq >= 550){ freq_set = MFR_SPECIFIC_03_FS_550K; }
		else if(freq >= 425){ freq_set = MFR_SPECIFIC_03_FS_425K; }
		else if(freq >= 315){ freq_set = MFR_SPECIFIC_03_FS_315K; }

		data[0]= 1 << MFR_SPECIFIC_03_DCAP3_OFFSET| 0 << MFR_SPECIFIC_03_RSCP_OFFSET |  freq_set <<  MFR_SPECIFIC_03_FS_OFFSET ;
		O26_CORE_REGUL_WRI2C(0, MFR_SPECIFIC_03, (UINT8 *)data ,1);
		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o26_regul);
	}
	return ret;
}

int __O26_TPS549A20_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0, i = 0;
	pms_o26_regulator_t * regul = NULL ;
	UINT8 vout_set = VOUT_ADJUSTMENT_UP_00; /* 920 mV */
	UINT8 vout_margin_high = VOUT_MARGIN_HIGH_00_0; /* 0% up margin */
	UINT8 vout_margin_low = VOUT_MARGIN_LOW_00_0; /* 0% down margin*/
	UINT8 opmargin  =       OPERATION_OPMARGIN_OFF;
	UINT8 data[5];

	if(volt > VOUT_ADJUSTMENT_TI_MAX || volt < VOUT_ADJUSTMENT_TI_MIN )
	{
		PM_ERROR("check core volt[%d]mV ch[%d]\n",volt,ch);
		return -1;
	}

	if(ch == 0 || ch == 1)
	{
		for(i=0; i < sizeof(_stsltcpuRegulator)/sizeof(pms_o26_regulator_t); i++)
		{
			if(volt >= _stsltcpuRegulator[i].vout_ref)
			{
				regul = &_stsltcpuRegulator[i];
				break;
			}
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


	//printf("opmargin[%x]\n",opmargin);
	/* switch converter on | turn off output voltage margin function */
	data[0]= OPERATION_ON_OFF | opmargin << OPERATION_OPMARGIN_OFFSET;
	ret = O26_CORE_REGUL_WRI2C((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_NOTI("check tpsA\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	O26_CORE_REGUL_WRI2C((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/* change switching frequency of DCDC from 400khz (default)
	   to 500khz as requested by HE */
	data[0]= FREQUENCY_CONFIG_500KHZ << FREQUENCY_CONFIG_OFFSET;
	O26_CORE_REGUL_WRI2C((UINT8)ch, FREQUENCY_CONFIG, (UINT8 *)data ,1);

	data[0]= vout_margin_high << VOUT_MARGIN_VOMH_OFFSET | vout_margin_low << VOUT_MARGIN_VOML_OFFSET ;
	O26_CORE_REGUL_WRI2C((UINT8)ch, VOUT_MARGIN,(UINT8 *)data,1);
	//printf("vout_margin_high[%x] vout_margin_low[%x]\n",vout_margin_high,vout_margin_low);

	data[0]= vout_set;
	O26_CORE_REGUL_WRI2C((UINT8)ch, VOUT_ADJUSTMENT,(UINT8 *)data,1);
	PM_NOTI("tiA ch [%d] volt[%d]mV set[0x%x:%d h:%d l:%d]\n",ch,volt,vout_set,vout_set,vout_margin_high, vout_margin_low);

	return ret;


}

int __O26_TPS549B22_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0;
	int i = 0;
	pms_o26_regulatorB_t * regul = NULL ;
	UINT32 vout_set  = 0;
	u8 data[5];


	if(volt> TPS549B22_VOUT_MAX  || volt < TPS549B22_VOUT_MIN )
	{
		PM_ERROR("check core volt[%d]mV\n",volt);
		return -1;
	}

#if 0
	vout_set = (mv * 10000) / 19531;
	printf("%dmv vout_set [%d:0x%x]  [0x%x] [0x%x] \n",mv,vout_set,vout_set,vout_set/256, vout_set%256);
#endif

	for(i=0; i < sizeof(_stRegulatorB)/sizeof(pms_o26_regulatorB_t); i++)
	{
		if(volt >= _stRegulatorB[i].vout_ref)
		{
			regul = &_stRegulatorB[i];
			break;
		}
	}

	if( regul != NULL)
	{
		vout_set = regul->vout_set;
	}
	else
	{
		PM_ERROR("check core volt[%d]mV i[%d] \n",volt,i);
		return -1;
	}
	g_o26_core_vol  = volt;

	data[0]= OPERATION_ON_OFF | 0 << OPERATION_OPMARGIN_OFFSET;
	ret = O26_CORE_REGUL_WRI2C((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_ERROR("check tpsB\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	//PM_DEBUG( "ON_OFF_CONFIG [%x]\n",data[0]);
	O26_CORE_REGUL_WRI2C((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/*set DCAP3 switching frequency of DCDC from 550khz as requested by HE */

	data[0]= 1 << MFR_SPECIFIC_03_DCAP3_OFFSET| 0 << MFR_SPECIFIC_03_RSCP_OFFSET |  MFR_SPECIFIC_03_FS_550K <<  MFR_SPECIFIC_03_FS_OFFSET ;
	//PM_DEBUG( "MFR_SPECIFIC_03 [%x]\n",data[0]);
	O26_CORE_REGUL_WRI2C((UINT8)ch, MFR_SPECIFIC_03, (UINT8 *)data ,1);

	data[0]= vout_set % 256;
	data[1]= vout_set / 256;
	//PM_DEBUG( "VOUT_COMMAND [%x] [%x]\n",data[0],data[1]);
	O26_CORE_REGUL_WRI2C((UINT8)ch, VOUT_COMMAND,(UINT8 *)data,2);
	PM_NOTI("tiB volt[%d]mV set[0x%x:%d]\n",volt,vout_set,vout_set);
	return ret;
}

int __O26_MPS_set_volt(unsigned int mv, unsigned int ch)
{
    int ret = 0;
    int i = 0;
    UINT8 data[5];
    UINT8 done = 0;
    pms_o26_regulatorB_t * regul = NULL ;
    UINT32 vout_set  = 0;

    if(mv > VOUT_ADJUSTMENT_MPS_MAX || mv < VOUT_ADJUSTMENT_MPS_MIN )
    {
        PM_NOTI("check core volt[%d]mV\n",mv);
        return -1;
    }

    for(i=0; i < sizeof(_stRegulatorMPS)/sizeof(pms_o26_regulatorB_t); i++)
    {
        if(mv >= _stRegulatorMPS[i].vout_ref)
        {
            regul = &_stRegulatorMPS[i];
            break;
        }
    }

    if( regul != NULL)
    {
        vout_set = regul->vout_set;
    }
    else
    {
        PM_NOTI("check core volt[%d]mV i[%d]\n",mv,i);
    }

    /* switching freq as 500khz */
    data[0] = 3 << SYSCTRL2_PG_DEGLITCH_OFFSET | 0 << SYSCTRL2_SWITCHING_FREQ_OFFSET |
            0 << SYSCTRL2_SOFTSTOP_OFFSET | 1 << SYSCTRL2_CUR_LIMIT_ADJ_OFFSET;
	ret = O26_CORE_REGUL_WRI2C((UINT8)ch, SYSCTRL2, (UINT8 *)data ,1);

    if(ret < 0 )
    {
        PM_NOTI("check mps regulator vendor\n");
        return -1;
    }

    data[0] = 1 << SYSCTRL1_EN_OFFSET | 1 << SYSCTRL1_GOBIT_OFFSET | 4 << SYSCTRL1_SLEWRATE_OFFSET |
        1 << SYSCTRL1_OVP_OFFSET | 1 << SYSCTRL1_OVC_OFFSET | 0 << SYSCTRL1_MODE_OFFSET ;
	O26_CORE_REGUL_WRI2C((UINT8)ch, SYSCTRL1, (UINT8 *)data ,1);

    /* need to find valid vset table in mps */
    data[0] = vout_set << VSEL_OUTREF_OFFSET ;
    data[0] &= ~(1 << VSEL_VBOOT_OFFSET) ;
    //regulator_write(VSEL, (UINT8 *)data ,1);
	O26_CORE_REGUL_WRI2C((UINT8)ch,VSEL, (UINT8 *)data ,1);
    PM_NOTI("mps volt[%d]mV vsel set[0x%x:%d] \n",mv,data[0],data[0]);

    while( done == 0)
    {
		O26_CORE_REGUL_RDI2C(0, SYSCTRL1, (UINT8 *)data ,1);
        if(( data[0] & (1 <<SYSCTRL1_GOBIT_OFFSET)) == 0 )
        {
            done = 1;
            break;
        }
        i++;
        if(i == REGULATOR_RETRY_CNT)
        {
            PM_NOTI("check mps %d\n",i);
            return -1;
        }
        udelay(200);
    }


    return ret;

}


int o26_SetCpuVal(unsigned int volt, unsigned int ch)
{
	int ret = 0;

	ret = __O26_TPS549A20_set_volt(volt,ch);

	PM_NOTI("o26_sltcpu[%d]mv ret[%d]\n",volt ,ret);
	return ret;
}
int o26_SetCoreVal(unsigned int volt, unsigned int ch)
{
	int ret = 0;

	if (o26_regul == REGULATOR_TPS549A20)
	{
		ret = __O26_TPS549A20_set_volt(volt,ch);
	}
	else if (o26_regul == REGULATOR_TPS549B22)
	{
		ret = __O26_TPS549B22_set_volt(volt,ch);
	}
	else if (o26_regul == REGULATOR_MPS)
	{
		ret = __O26_MPS_set_volt(volt,ch);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d:%d]\n",o26_regul,ch);
	}


	PM_DEBUG("o26_regul[%x] v[%d] ret[%d]\n",o26_regul,volt ,ret);
	return ret;
}
unsigned int o26_GetCoreVal(void)
{
	unsigned int mV = g_o26_core_vol;
	return mV;
}


static unsigned int o26_get_sampling_rate(void)
{
	return g_o26_sampling_rate;
}

static int o26_set_sampling_rate(unsigned int ms)
{
	g_o26_sampling_rate = ms;

	return 0;
}

static int o26_pm_task_dvfs(pms_o26_work_t *pms_o26_work)
{
	int ret = 0;
	if (pms_o26_work->do_dvfs)
    {
		mutex_lock(&o26_clk_mutex);
        if( pms_o26_work->target_freq != 0 && pms_o26_work->target_freq != o26_cur_freq)
        {
			if( pms_o26_work->target_freq == 1400)
			{
				if(o26_pm_get_debug_enable())
					PM_NOTI("loadsum %d  freq_UP_1400\n", pms_o26_work->loadsum);	
			}
			else if( pms_o26_work->target_freq == 1200)
			{
				if(o26_pm_get_debug_enable())
					PM_NOTI("loadsum %d 2sec_freq_DN_1200\n", pms_o26_work->loadsum);	
			}

            ret = o26_SetCPUFreq(pms_o26_work->target_freq);
            if(ret != 0)
                PM_ERROR("check freq change[%d]\n", ret);
        }
		mutex_unlock(&o26_clk_mutex);
		pms_o26_work->do_dvfs = 0;
    }

	return ret;
}

static int o26_pm_task_hotplug(pms_o26_work_t *pms_o26_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_o26_work->do_hotplug && (o26_get_error_state() == 0))
	{
		pms_o26_work->do_hotplug = 0;
		mutex_lock(&o26_onoff_mutex);
		o26_is_onoff = 1;	
		if (pms_o26_work->core_onoff == 0)
		{
			if(o26_pm_get_debug_enable())
				PM_NOTI("loadsum %d 2sec_cpu_num_%d -> cpu_turn_OFF \n", pms_o26_work->loadsum,pms_o26_work->cpunum);
			if (cpu_online(pms_o26_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = remove_cpu(pms_o26_work->core_n);
#else
				ret = cpu_down(pms_o26_work->core_n);
#endif
				if(ret != 0)
				{
					if (ret != -EBUSY)
						o26_set_error_state(0xD << 28 | pms_o26_work->core_n << 24 | pms_o26_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o26_work->core_n);
					if(pCpudev != NULL)
					{
						device_lock(pCpudev);
						pCpudev->offline = 1;
						device_unlock(pCpudev);
					}
				}
			}
		}
		else
		{
			if(o26_pm_get_debug_enable())
				PM_NOTI("loadsum %d cpu_num_%d -> cpu_turn_ON \n", pms_o26_work->loadsum,pms_o26_work->cpunum);
			if (!cpu_online(pms_o26_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = add_cpu(pms_o26_work->core_n);
#else
				ret = cpu_up(pms_o26_work->core_n);
#endif

				if(ret != 0)
				{
					if (ret != -EBUSY)
						o26_set_error_state(0xD << 28 | pms_o26_work->core_n << 24 | pms_o26_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o26_work->core_n);
					if(pCpudev != NULL)
					{
						device_lock(pCpudev);
						pCpudev->offline = 0;
						device_unlock(pCpudev);
					}
				}
			}
		}
		o26_is_onoff = 0;	
		mutex_unlock(&o26_onoff_mutex);
	}

	return ret;
}

static int o26_pm_task_avs(pms_o26_work_t *pms_o26_work)
{
	int ret = 0;
	unsigned int type = 0;

	if (pms_o26_work->do_avs == I2C_AVS_CPU) /* cpu i2c regul */
	{
		pms_o26_work->do_avs = 0;

		o26_SetCpuVal(pms_o26_work->target_vol,pms_o26_work->ch);
	}
	else if (pms_o26_work->do_avs == GPIO_AVS_CPU) /* cpu gpio regul */
	{
		pms_o26_work->do_avs = 0;
		type = pms_o26_work->target_vol;
#if 1
		switch(type){
			case CPU_AVS_FF:
				//VLV
				gpiod_direction_input(o26_cpuvid0);
				gpiod_direction_input(o26_cpuvid1);
				PM_NOTI("SET CPU ff\n" );
				break;
			case CPU_AVS_F:
				//LV
				gpiod_direction_output(o26_cpuvid1,0);
				gpiod_direction_input(o26_cpuvid0);
				PM_NOTI("SET CPU f\n" );
				break;
			case CPU_AVS_N:
				//MV
				gpiod_direction_output(o26_cpuvid0,0);
				gpiod_direction_input(o26_cpuvid1);
				PM_NOTI("SET CPU n\n" );
				break;
			case CPU_AVS_S:
				//HV
				gpiod_direction_output(o26_cpuvid0,0);
				gpiod_direction_output(o26_cpuvid1,0);
				PM_NOTI("SET CPU s\n" );
				break;
			case CPU_AVS_FF_HIGH_TEMP:
				//VLV
				//ret = regulator_set_voltage(o26_regulator, O26_CPU_AVS_FF_HTEMP_UV,O26_CPU_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CPU hff slt\n" );
				break;
			default:
				//HV
				gpiod_direction_output(o26_cpuvid0,0);
				gpiod_direction_output(o26_cpuvid1,0);
				PM_NOTI("SET CPU s\n" );
				break;
		}
#endif

	}
	else if (pms_o26_work->do_avs == I2C_AVS_CORE) /* core i2c regul */
	{
		pms_o26_work->do_avs = 0;
		type = pms_o26_work->target_corevol;
		o26_SetCoreVal(pms_o26_work->target_corevol,pms_o26_work->ch);

#if 0
		o26_coreregulator = regulator_get(NULL, "core-regulator");
		if (IS_ERR(o26_coreregulator)) {
			PM_ERROR("couldn't get coreregulator\n");
			return 0;
		}

		prevMV = regulator_get_voltage(o26_coreregulator) ;

		switch(type){
			case CORE_AVS_S:
				//HV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_S_UV,O26_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
			case CORE_AVS_N:
				//MV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_N_UV,O26_CORE_AVS_N_UV);
				PM_NOTI("SET CORE n\n" );
				break;
			case CORE_AVS_F:
				//LV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_F_UV,O26_CORE_AVS_F_UV);
				PM_NOTI("SET CORE f\n" );
				break;
			case CORE_AVS_FF:
				//VLV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_FF_UV,O26_CORE_AVS_FF_UV);
				PM_NOTI("SET CORE ff\n" );
				break;

			case CORE_AVS_S_HIGH_TEMP:
				//HV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_S_HTEMP_UV,O26_CORE_AVS_S_HTEMP_UV);
				PM_NOTI("SET CORE hs\n" );
				break;
			case CORE_AVS_N_HIGH_TEMP:
				//MV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_N_HTEMP_UV,O26_CORE_AVS_N_HTEMP_UV);
				PM_NOTI("SET CORE hn\n" );
				break;
			case CORE_AVS_F_HIGH_TEMP:
				//LV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_F_HTEMP_UV,O26_CORE_AVS_F_HTEMP_UV);
				PM_NOTI("SET CORE hf\n" );
				break;
			case CORE_AVS_FF_HIGH_TEMP:
				//VLV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_FF_HTEMP_UV,O26_CORE_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CORE hff\n" );
				break;

			default:
				//HV
				ret = regulator_set_voltage(o26_coreregulator, O26_CORE_AVS_S_UV,O26_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
		}
		PM_NOTI("CORE ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(o26_coreregulator) );
		regulator_put(o26_coreregulator);
#endif
	}
	return ret;
}

void o26_taskdisable_reset(void)
{
	g_o26_pm_task_disable = 0;
}

static void o26_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void o26_lgdtv_pm_task_call(pms_o26_work_t * o26work)
{
	if( o26_is_onoff == 0)
	{
		o26_set_work(o26work);
		complete(&cpu_hotplug_completion);
	}
}

static void o26_lgdtv_regul_task_reset(void)
{
	reinit_completion(&regulator_completion);
}
#if 0
static void o26_lgdtv_coreregul_task_reset(void)
{
	reinit_completion(&coreregulator_completion);
}
#endif

static void o26_lgdtv_regul_task_call(pms_o26_work_t  * o26_regulwork)
{
	o26_set_regul_work(o26_regulwork);
	complete(&regulator_completion);
}
static void o26_clk_task_call(pms_o26_work_t  * o26_work)
{
	if(spin_trylock(&g_o26_freq_lock))
	{
		o26_set_clk_work(o26_work);
		complete(&clk_completion);
		spin_unlock(&g_o26_freq_lock);
	}
}

static void o26_lgdtv_coreregul_task_call(pms_o26_work_t  * o26_coreregulwork)
{
	o26_set_coreregul_work(o26_coreregulwork);
	complete(&coreregulator_completion);
}

static int o26_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o26_work_t pms_o26_work;

	PM_NOTI("o26 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o26 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_o26_pm_task_disable == 1)
			continue;

		if (o26_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_o26_pm_lock, flags);
			memcpy((void *)&pms_o26_work, (void *)&g_o26_pms, sizeof(pms_o26_work_t));
			spin_unlock_irqrestore(&g_o26_pm_lock, flags);

			if(pm_o26_gov->get_mp_enable())
				o26_pm_task_hotplug(&pms_o26_work);
		//	if(pm_o26_gov->get_freq_enable())
		//		o26_pm_task_dvfs(&pms_o26_work);
		}

#ifdef	ERROR_PRINT_LOOP
		if(o26_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", o26_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}

static int o26_clk_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o26_work_t pms_o26_work;

	do {
		if (kthread_should_stop()) {
			PM_NOTI("o26_clk_pm_task - exit!\n");
			break;
		}
		reinit_completion(&clk_completion);
		wait_for_completion(&clk_completion);

		if (g_o26_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o26_clk_lock, flags);
		memcpy((void *)&pms_o26_work, (void *)&g_o26_clk, sizeof(pms_o26_work_t));
		spin_unlock_irqrestore(&g_o26_clk_lock, flags);
		if(pm_o26_gov->get_freq_enable())
		    o26_pm_task_dvfs(&pms_o26_work);

	} while (1);

	return 0;
}


static int o26_regulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o26_work_t pms_o26_work;

	PM_NOTI("o26_regulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o26_regulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&regulator_completion);
		wait_for_completion(&regulator_completion);

		PM_DEBUG_PRINT("regul task run in cpu%d\n", smp_processor_id());

		if (g_o26_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o26_regul_lock, flags);
		memcpy((void *)&pms_o26_work, (void *)&g_o26_regul, sizeof(pms_o26_work_t));
		spin_unlock_irqrestore(&g_o26_regul_lock, flags);
		o26_pm_task_avs(&pms_o26_work);

		PM_DEBUG_PRINT("REGUL TASK END\n");
	} while (1);

	return 0;
}

static int o26_coreregulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o26_work_t pms_o26_work;

	PM_NOTI("o26_coreregulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o26_coreregulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&coreregulator_completion);
		wait_for_completion(&coreregulator_completion);

		PM_DEBUG_PRINT("core regul task run in cpu%d\n", smp_processor_id());

		if (g_o26_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o26_coreregul_lock, flags);
		memcpy((void *)&pms_o26_work, (void *)&g_o26_coreregul, sizeof(pms_o26_work_t));
		spin_unlock_irqrestore(&g_o26_coreregul_lock, flags);
		o26_pm_task_avs(&pms_o26_work);

		PM_DEBUG_PRINT("COREREGUL TASK END\n");
	} while (1);

	return 0;
}

void o26_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(o26_lgdtv_pm_task,
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

	if (clk_pm_task == NULL) {
		init_completion(&clk_completion);
		clk_pm_task = kthread_create_on_node(o26_clk_pm_task,
				NULL,
				cpu,
				"PM2_TASK/%lu", targetcpu);

		if (likely(!IS_ERR(clk_pm_task))) {
			kthread_bind(clk_pm_task, targetcpu);
			wake_up_process(clk_pm_task);
			PM_NOTI("PM2_TASK create successed\n");
		} else
			PM_NOTI("PM2_TASK create failed\n");
	}

	if (regulator_pm_task == NULL) {
		init_completion(&regulator_completion);
		regulator_pm_task = kthread_create_on_node(o26_regulator_pm_task,
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

	if (coreregulator_pm_task == NULL) {
		init_completion(&coreregulator_completion);
		coreregulator_pm_task = kthread_create_on_node(o26_coreregulator_pm_task,
				NULL,
				cpu,
				"CREGUL-PM-TASK/%lu", targetcpu);

		if (likely(!IS_ERR(coreregulator_pm_task))) {
			kthread_bind(coreregulator_pm_task, targetcpu);
			wake_up_process(coreregulator_pm_task);
			PM_NOTI("REGUL-PM-TASK create successed\n");
		} else
			PM_NOTI("REGUL-PM-TASK create failed\n");
	}

}

static void o26_AllCoreOn(void)
{
	pms_o26_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_o26_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			o26_lgdtv_pm_task_call(&pms_work);
			msleep(150);	/* max cpu on time */
			if(cpu_online(i) == 0)
			{
				msleep(2000);
			}
		}
	}
}

static void o26_SetMaxPerformance(void)
{
	reinit_completion(&cpu_hotplug_completion);
	reinit_completion(&clk_completion);
	reinit_completion(&regulator_completion);
	reinit_completion(&coreregulator_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	o26_AllCoreOn();

}

unsigned int o26_kdrv_pm_runtime_suspend = 0;
unsigned int o26_mp_backup = 0;
void o26_set_kdrv_pm_runtime_suspend(void)
{
	pms_o26_work_t pms_work;
	int i;

	mutex_lock(&o26_kdrvpm_runtime_mutex);
	o26_kdrv_pm_runtime_suspend = 1;
	o26_mp_backup = pm_o26_gov->get_mp_enable();
	pm_o26_gov->set_gov(PMS_GOV_DISABLE);
	pm_o26_gov->set_mp_enable(1);
	reinit_completion(&cpu_hotplug_completion);
	cpu_maps_update_begin();
	cpu_maps_update_done();

	memset(&pms_work, 0x0, sizeof(pms_o26_work_t));
	for(i=3; i>0; i--)
	{
		if (cpu_online(i) == 1)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = 0;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			o26_lgdtv_pm_task_call(&pms_work);
			msleep(250);
			if(cpu_online(i))
			{
				msleep(2000);
			}
		}
	}
	//o26_SetCPUFreq(1200);
	mutex_unlock(&o26_kdrvpm_runtime_mutex);
	PM_NOTI("kdrv_pm - runtime suspend OK\n");
}
void o26_set_kdrv_pm_runtime_resume(void)
{
	mutex_lock(&o26_kdrvpm_runtime_mutex);
	o26_SetMaxPerformance();
	pm_o26_gov->init();
	pm_o26_gov->set_mp_enable(o26_mp_backup);

	pm_o26_gov->set_gov(PMS_GOV_ENABLE);
	o26_kdrv_pm_runtime_suspend = 0;
	mutex_unlock(&o26_kdrvpm_runtime_mutex);
	PM_NOTI("kdrv_pm - runtime resume OK\n");

}
void o26_FuncInit(void)
{

	/* o26 DCDC regulater vendor is fixed as TI
	   detailed info: http://clm.lge.com/issue/browse/SCDCR-1798 */

	#if 0
	if(o26_clk0_base == NULL)
		o26_clk0_base = ioremap(0xCC6A2060,0xc);
	if(o26_clk_pdb_base == NULL)
		o26_clk_pdb_base = ioremap(0xCC6A2090,0x4);
	if(o26_clk_src_base == NULL)
		o26_clk_src_base = ioremap(0xCA21000C,0x4);
	o26_freqtest = gpiod_get(&o26_gpiodev, "9", GPIOD_ASIS);
	if (IS_ERR(o26_freqtest))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",9,o26_freqtest);
	}
	#endif


	pm_o26_gov = get_o26_pm_gov();
	o26_pmtask_init();


}

static pms_o26_func_t o26_pm_func =
{
	.init = o26_FuncInit,
	.getfreq = o26_GetCPUFreq,
	.setfreq = o26_SetCPUFreq,
	.setcorevolt = o26_SetCoreVal,
	.setcore_switching_freq = o26_SetCoreSwitchingFreq,
	.getcorevolt = o26_GetCoreVal,
	.get_cpu_on = o26_GetCPUOn,
	.get_cpu_type = o26_GetCPUType,
	.set_max_performance = o26_SetMaxPerformance,
	.run = o26_lgdtv_pm_task_call,
	.run_clk = o26_clk_task_call,
	.run_regul = o26_lgdtv_regul_task_call,           //cpuregul
	.run_coreregul = o26_lgdtv_coreregul_task_call,   //coreregul
	.reset = o26_lgdtv_pm_task_reset,
	.reset_regul = o26_lgdtv_regul_task_reset,
	.taskdisable_reset = o26_taskdisable_reset,
	.get_sampling_rate = o26_get_sampling_rate,
	.set_sampling_rate = o26_set_sampling_rate,
	.get_error_state = o26_get_error_state,
	.set_error_state = o26_set_error_state,
};

pms_o26_func_t* get_o26_pm_func(void)
{
	return &o26_pm_func;
}

