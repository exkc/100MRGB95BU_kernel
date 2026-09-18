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

#include "pm_o24common.h"

#include "reg_ctrl.h"
#include "i2c_core.h"
#include "gpio_core.h"

#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include <linux/regulator/consumer.h>

extern struct regulator *o24_regulator;
extern struct regulator *o24_coreregulator;

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
static DEFINE_SPINLOCK(g_o24_pm_lock);
static DEFINE_SPINLOCK(g_o24_regul_lock);
static DEFINE_SPINLOCK(g_o24_coreregul_lock);
static DEFINE_SPINLOCK(g_o24_clk_lock);

DEFINE_MUTEX(o24_onoff_mutex);
DEFINE_MUTEX(o24_clk_mutex);
DEFINE_MUTEX(o24_kdrvpm_runtime_mutex);
//static DEFINE_SPINLOCK(g_o24_cpuregul_lock);
static DEFINE_SPINLOCK(g_o24_freq_lock);

static unsigned int o24_regul = 0;

unsigned int o24_is_onoff = 0;

module_param(o24_regul, uint, S_IRUGO);
MODULE_PARM_DESC(o24_gpuNP, "o24_regul");

extern struct device o24_gpiodev;

extern struct gpio_desc *o24_cpuvid0;
extern struct gpio_desc *o24_cpuvid1;
extern struct gpio_desc *o24_gpio71;


//struct gpio_desc *o24_freqtest = NULL;
/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
#define FREQ_SAME			0
#define FREQ_UP				1
#define FREQ_DOWN			2
#define FREQ_ONLY			3
#define VOL_ONLY			4
#define ERROR_MASK			0xffff
#define O24_MODEL_OPT10			5

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
#define VOUT_ADJUSTMENT_TI_MAX		1290		/*mV*/
#define VOUT_ADJUSTMENT_TI_MIN		850		/*mV*/

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

#define VOUT_ADJUSTMENT_MPS_MAX		1140	/*mV*/
#define VOUT_ADJUSTMENT_MPS_MIN		750	/*mV*/

#define	OUTCURRENT			0x03
#define OUTCURRENT_OFFSET		(0x0)	/* operation current  */

#define	OUTVOLT				0x04
#define OUTVOLT_OFFSET			(0x0)	/* operation voltage  */

#define VOUT_ADJUSTMENT_MPS_MAX 	1140	/*mV*/
#define VOUT_ADJUSTMENT_MPS_MIN 	750	/*mV*/

void __iomem *o24_clk0_base = NULL;
void __iomem *o24_clk_pdb_base = NULL;
void __iomem *o24_clk_src_base = NULL;



static  pms_o24_regulator_t  _stsltcpuRegulator[] =
{
	//base 1070mv
    {1295   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_12_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1283   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1272   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1260   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1249   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1238   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1227   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1217   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1206   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1196   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1186   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_01_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1176   ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
    {1166    ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1158    ,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1150    ,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1142    ,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1134    ,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1126    ,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1118    ,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1110    ,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1102    ,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1094    ,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1086    ,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1078    ,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1070    ,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1070    ,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1062   ,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1054   ,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1046   ,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1038   ,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1030   ,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1022   ,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1014   ,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {1006   ,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {998    ,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {990    ,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {982    ,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {974    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
    {962    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
    {951    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
    {939    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },//tune
    {929    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
    {918    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
    {907    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
    {898    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
    {887    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
    {877    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
    {868    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
    {859    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
    {850    ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },

};


typedef struct
{
	UINT32 vout_ref;
	UINT32 vout_set;
}pms_o24_regulatorB_t;

/* TPS549B22 table */
static  pms_o24_regulatorB_t  _stRegulatorB[] =
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

#if 0
/* MP8876 table */
static  pms_o24_regulatorB_t  _stRegulatorMPS[] =
{
	/*mv, set*/
	{1150,85},
	{1140,84},
	{1130,82},
	{1120,80},
	{1110,79},
	{1100,77},
	{1090,75},
	{1080,74},
	{1070,72},
	{1060,71},
	{1050,69},
	{1040,68},
	{1030,66},
	{1020,64},
	{1010,63},
	{1000,62},
	{990, 60},
	{980, 59},
	{970, 57},
	{960, 56},
	{950, 54},
	{940, 53},
	{930, 51},
	{920, 50},
	{910, 49},
	{900, 47},
	{890, 46},
	{880, 44},
	{870, 43},
	{860, 41},
	{850, 40},
	{840, 38},
	{830, 37},
	{820, 36},
	{810, 35},
	{800, 34},
	{790, 33},
	{780, 31},
	{770, 29},
	{760, 28},
	{750, 25},
	{740, 24},
	{730, 22},

};
#endif


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/

extern unsigned int o24_cpu_avs;
extern unsigned int o24_core_avs;

extern int o24_set_cpu_vid( int level);
extern int o24_SetCoreVal(unsigned int volt, unsigned int ch);
extern int o24_SetCpuVal(unsigned int volt, unsigned int ch);
extern unsigned int o24_pm_get_debug_enable(void) ;
extern int o24_pm_set_debug_enable(unsigned int val) ;
/*----------------------------------------------------------------------------------------
  global Functions
  ---------------------------------------------------------------------------------------*/

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
static int g_o24_pm_task_disable = 0;
static pms_o24_work_t g_o24_pms;
static pms_o24_work_t g_o24_clk;
static pms_o24_work_t g_o24_regul;
static pms_o24_work_t g_o24_coreregul;

unsigned int g_o24_sampling_rate = 200; // 20ms 200ms
static unsigned int g_o24_core_vol = 0;

static unsigned int g_o24_err = 0;
static pms_o24_avs_t* pm_o24_avs = NULL;
static pms_o24_gov_t* pm_o24_gov = NULL;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/


#define O24_CORE_REGULATOR_IDX			2

#define O24_CORE_REGULATOR_DEVICE_ID_TPS549A20	0x3E
#define O24_CORE_REGULATOR_DEVICE_ID_TPS549B22	0x3A
#define O24_CORE_REGULATOR_DEVICE_ID_MPS	0xc0


//static LX_I2C_DEV_HANDLE _i2c_core_regulator_handle;

int O24_CORE_REGUL_WRI2C_SLTCPU( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
	int rc = 0;
	rc = REG_WriteI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data, nbyte);
	return rc;
}

int O24_CORE_REGUL_RDI2C_SLTCPU(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
	int rc = 0;
		rc = REG_ReadI2CL(ch , O24_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	return rc;
}

int O24_CORE_REGUL_WRI2C( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (o24_regul == REGULATOR_TPS549A20)
	{
		rc = REG_WriteI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data, nbyte);
	}
	else if (o24_regul == REGULATOR_TPS549B22)
	{
		rc = REG_WriteI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (o24_regul == REGULATOR_MPS)
	{
		rc = REG_WriteI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o24_regul);
	}

	return rc;
}

int O24_CORE_REGUL_RDI2C(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (o24_regul == REGULATOR_TPS549A20)
	{
		rc = REG_ReadI2CL(ch , O24_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	}
	else if (o24_regul == REGULATOR_TPS549B22)
	{
		rc = REG_ReadI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (o24_regul == REGULATOR_MPS)
	{
		rc = REG_ReadI2CL(ch, O24_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o24_regul);
	}

	return rc;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int o24_get_error_state(void)
{
	return g_o24_err;
}

int o24_set_error_state(unsigned int value)
{
	g_o24_err = value;

	return 0;
}

static void o24_set_work(pms_o24_work_t *o24_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o24_pm_lock, flags);
	memcpy( &g_o24_pms,o24_work , sizeof(pms_o24_work_t));
	spin_unlock_irqrestore(&g_o24_pm_lock, flags);
}

static void o24_set_clk_work(pms_o24_work_t *o24_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o24_clk_lock, flags);
	memcpy( &g_o24_clk, o24_work , sizeof(pms_o24_work_t));
	spin_unlock_irqrestore(&g_o24_clk_lock, flags);
}

static void o24_set_regul_work(pms_o24_work_t * o24_regulwork)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o24_regul_lock, flags);
	memcpy( &g_o24_regul, o24_regulwork , sizeof(pms_o24_work_t));
	spin_unlock_irqrestore(&g_o24_regul_lock, flags);
}

static void o24_set_coreregul_work(pms_o24_work_t * o24_coreregulwork)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o24_coreregul_lock, flags);
	memcpy( &g_o24_coreregul, o24_coreregulwork , sizeof(pms_o24_work_t));
	spin_unlock_irqrestore(&g_o24_coreregul_lock, flags);
}

static int o24_GetCPUType(void)
{
	int ret = 0;
	pms_o24_avsinto_t info;

	pm_o24_avs = get_o24_pm_avs();
	ret = pm_o24_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int o24_GetCPUOn(void)
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

unsigned int o24_cur_freq = 1400;
unsigned int o24_GetCPUFreq(void)
{

	unsigned int MHz = 0;
	MHz = o24_cur_freq;
	return MHz;
}

int o24_SetCPUFreq(unsigned int freq)
{
	int fv_time = 0;


	if(pm_o24_gov != NULL)
		fv_time =  pm_o24_gov->get_fv_time();
	else
		fv_time = 100;

	if(freq == o24_cur_freq)
		return 0;

    if( freq > o24_cur_freq)
    {
	    PM_TRACE("high freq[%d] cur [%d] o24_cpu_avs-1[%d] \n", freq,o24_cur_freq,o24_cpu_avs-1);
		if(o24_cpu_avs >= 1)
        	o24_set_cpu_vid(o24_cpu_avs-1);
		/* hw request  0.1 ms betw clk chang and volt change */
	    usleep_range(fv_time,fv_time);
    }

	//(1) cpu core clock source change ( ---> alive clock(core660))
	if(o24_clk_src_base != NULL)
		writel(0x00000001, o24_clk_src_base);

	//(2) CPU PLL powerdown [3] : 0x0
	if(o24_clk_pdb_base != NULL)
		writel(0x00007FF7, o24_clk_pdb_base);

	if(freq == 1400 && o24_clk0_base != NULL)
	{
		//gpiod_direction_output(o24_freqtest,1);
		//(3) freq setting change
		writel(0x000D455A, o24_clk0_base);
		writel(0x1005B002, o24_clk0_base + 4);
		writel(0x00000001, o24_clk0_base + 8);

	}
	else if(freq == 1200 && o24_clk0_base != NULL)
	{
		//gpiod_direction_output(o24_freqtest,0);
		//(3) freq setting change
		writel(0x000B444A, o24_clk0_base);
		writel(0x1005B002, o24_clk0_base + 4);
		writel(0x00000001, o24_clk0_base + 8);
	}

	//(4) CPU PLL power up
	if(o24_clk_pdb_base != NULL)
		writel(0x00007FFF, o24_clk_pdb_base);

	//(5) Wait 100us
	usleep_range(150,150);

	//(6) clock change to CPU PLL
	if(o24_clk_src_base != NULL)
		writel(0x00000000, o24_clk_src_base);

    if(freq < o24_cur_freq)
    {
	    PM_TRACE("low freq[%d] cur [%d] o24_cpu_avs[%d] \n", freq,o24_cur_freq,o24_cpu_avs);

		/* hw request  0.1 ms betw clk chang and volt change */
	    usleep_range(fv_time,fv_time);
		if(o24_cpu_avs)
        	o24_set_cpu_vid(o24_cpu_avs);
    }

	o24_cur_freq = freq;
	if(pm_o24_gov != NULL && pm_o24_gov->get_freq_debug_enable() )
		PM_NOTI(" %d freq\n", freq);


	return 0;
}


int o24_SetCoreSwitchingFreq(unsigned int freq)
{
	int ret = 0;
	UINT8  freq_set = FREQUENCY_CONFIG_400KHZ; /* default */
	unsigned data[5];

	if(freq > 1000 || freq < 250 )
	{
		PM_ERROR("check core switching freq[%d]mV\n",freq);
		return -1;
	}
	if(o24_regul == REGULATOR_TPS549B22)
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
		O24_CORE_REGUL_WRI2C(0, MFR_SPECIFIC_03, (UINT8 *)data ,1);
		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",o24_regul);
	}
	return ret;
}

int __O24_TPS549A20_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0, i = 0;
	pms_o24_regulator_t * regul = NULL ;
	UINT8 vout_set = VOUT_ADJUSTMENT_UP_00; /* 920 mV */
	UINT8 vout_margin_high = VOUT_MARGIN_HIGH_00_0; /* 0% up margin */
	UINT8 vout_margin_low = VOUT_MARGIN_LOW_00_0; /* 0% down margin*/
	UINT8 opmargin  =       OPERATION_OPMARGIN_OFF;
	UINT8 data[5];

	if(volt > VOUT_ADJUSTMENT_TI_MAX || volt < VOUT_ADJUSTMENT_TI_MIN )
	{
		PM_ERROR("check core volt[%d]mV\n",volt);
		return -1;
	}

	if(ch == 0)
	{
		for(i=0; i < sizeof(_stsltcpuRegulator)/sizeof(pms_o24_regulator_t); i++)
		{
			if(volt > _stsltcpuRegulator[i].vout_ref)
			{
				if( i == 0)
					regul = &_stsltcpuRegulator[0];
				else
					regul = &_stsltcpuRegulator[i-1];
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
	ret = O24_CORE_REGUL_WRI2C_SLTCPU((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_NOTI("check tpsA\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	O24_CORE_REGUL_WRI2C_SLTCPU((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/* change switching frequency of DCDC from 400khz (default)
	   to 500khz as requested by HE */
	data[0]= FREQUENCY_CONFIG_500KHZ << FREQUENCY_CONFIG_OFFSET;
	O24_CORE_REGUL_WRI2C_SLTCPU((UINT8)ch, FREQUENCY_CONFIG, (UINT8 *)data ,1);

	data[0]= vout_margin_high << VOUT_MARGIN_VOMH_OFFSET | vout_margin_low << VOUT_MARGIN_VOML_OFFSET ;
	O24_CORE_REGUL_WRI2C_SLTCPU((UINT8)ch, VOUT_MARGIN,(UINT8 *)data,1);
	//printf("vout_margin_high[%x] vout_margin_low[%x]\n",vout_margin_high,vout_margin_low);

	data[0]= vout_set;
	O24_CORE_REGUL_WRI2C_SLTCPU((UINT8)ch, VOUT_ADJUSTMENT,(UINT8 *)data,1);
	PM_NOTI("tiA ch [%d] volt[%d]mV set[0x%x:%d h:%d l:%d]\n",ch,volt,vout_set,vout_set,vout_margin_high, vout_margin_low);

	return ret;


}

int __O24_TPS549B22_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0;
	int i = 0;
	pms_o24_regulatorB_t * regul = NULL ;
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

	for(i=0; i < sizeof(_stRegulatorB)/sizeof(pms_o24_regulatorB_t); i++)
	{
		if(volt > _stRegulatorB[i].vout_ref)
		{
			if( i == 0)
				regul = &_stRegulatorB[0];
			else
				regul = &_stRegulatorB[i-1];
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
	g_o24_core_vol  = volt;

	data[0]= OPERATION_ON_OFF | 0 << OPERATION_OPMARGIN_OFFSET;
	ret = O24_CORE_REGUL_WRI2C((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_ERROR("check tpsB\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	//PM_DEBUG( "ON_OFF_CONFIG [%x]\n",data[0]);
	O24_CORE_REGUL_WRI2C((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/*set DCAP3 switching frequency of DCDC from 550khz as requested by HE */

	data[0]= 1 << MFR_SPECIFIC_03_DCAP3_OFFSET| 0 << MFR_SPECIFIC_03_RSCP_OFFSET |  MFR_SPECIFIC_03_FS_550K <<  MFR_SPECIFIC_03_FS_OFFSET ;
	//PM_DEBUG( "MFR_SPECIFIC_03 [%x]\n",data[0]);
	O24_CORE_REGUL_WRI2C((UINT8)ch, MFR_SPECIFIC_03, (UINT8 *)data ,1);

	data[0]= vout_set % 256;
	data[1]= vout_set / 256;
	//PM_DEBUG( "VOUT_COMMAND [%x] [%x]\n",data[0],data[1]);
	O24_CORE_REGUL_WRI2C((UINT8)ch, VOUT_COMMAND,(UINT8 *)data,2);
	PM_NOTI("tiB volt[%d]mV set[0x%x:%d]\n",volt,vout_set,vout_set);
	return ret;
}

int __O24_MPS_set_volt(unsigned int volt, unsigned int ch)
{
	return 0;
}


int o24_SetCpuVal(unsigned int volt, unsigned int ch)
{
	int ret = 0;

	ret = __O24_TPS549A20_set_volt(volt,ch);

	PM_NOTI("o24_sltcpu[%d]mv ret[%d]\n",volt ,ret);
	return ret;
}
int o24_SetCoreVal(unsigned int volt, unsigned int ch)
{
	int ret = 0;

	if (o24_regul == REGULATOR_TPS549A20)
	{
		ret = __O24_TPS549A20_set_volt(volt,ch);
	}
	else if (o24_regul == REGULATOR_TPS549B22)
	{
		ret = __O24_TPS549B22_set_volt(volt,ch);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d:%d]\n",o24_regul,ch);
	}


	PM_DEBUG("o24_regul[%x] v[%d] ret[%d]\n",o24_regul,volt ,ret);
	return ret;
}
unsigned int o24_GetCoreVal(void)
{
	unsigned int mV = g_o24_core_vol;
	return mV;
}


static unsigned int o24_get_sampling_rate(void)
{
	return g_o24_sampling_rate;
}

static int o24_set_sampling_rate(unsigned int ms)
{
	g_o24_sampling_rate = ms;

	return 0;
}

static int o24_pm_task_dvfs(pms_o24_work_t *pms_o24_work)
{
	int ret = 0;
	if (pms_o24_work->do_dvfs)
    {
		mutex_lock(&o24_clk_mutex);
        if( pms_o24_work->target_freq != 0 && pms_o24_work->target_freq != o24_cur_freq)
        {
			if( pms_o24_work->target_freq == 1400)
			{
				if(o24_pm_get_debug_enable())
					PM_NOTI("loadsum %d  freq_UP_1400\n", pms_o24_work->loadsum);	
			}
			else if( pms_o24_work->target_freq == 1200)
			{
				if(o24_pm_get_debug_enable())
					PM_NOTI("loadsum %d 2sec_freq_DN_1200\n", pms_o24_work->loadsum);	
			}

            ret = o24_SetCPUFreq(pms_o24_work->target_freq);
            if(ret != 0)
                PM_ERROR("check freq change[%d]\n", ret);
        }
		mutex_unlock(&o24_clk_mutex);
		pms_o24_work->do_dvfs = 0;
    }

	return ret;
}

static int o24_pm_task_hotplug(pms_o24_work_t *pms_o24_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_o24_work->do_hotplug && (o24_get_error_state() == 0))
	{
		pms_o24_work->do_hotplug = 0;
		mutex_lock(&o24_onoff_mutex);
		o24_is_onoff = 1;	
		if (pms_o24_work->core_onoff == 0)
		{
			if(o24_pm_get_debug_enable())
				PM_NOTI("loadsum %d 2sec_cpu_num_%d -> cpu_turn_OFF \n", pms_o24_work->loadsum,pms_o24_work->cpunum);
			if (cpu_online(pms_o24_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = remove_cpu(pms_o24_work->core_n);
#else
				ret = cpu_down(pms_o24_work->core_n);
#endif
				if(ret != 0)
				{
					if (ret != -EBUSY)
						o24_set_error_state(0xD << 28 | pms_o24_work->core_n << 24 | pms_o24_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o24_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 1;
					device_unlock(pCpudev);
				}
			}
		}
		else
		{
			if(o24_pm_get_debug_enable())
				PM_NOTI("loadsum %d cpu_num_%d -> cpu_turn_ON \n", pms_o24_work->loadsum,pms_o24_work->cpunum);
			if (!cpu_online(pms_o24_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = add_cpu(pms_o24_work->core_n);
#else
				ret = cpu_up(pms_o24_work->core_n);
#endif

				if(ret != 0)
				{
					if (ret != -EBUSY)
						o24_set_error_state(0xD << 28 | pms_o24_work->core_n << 24 | pms_o24_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_o24_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 0;
					device_unlock(pCpudev);
				}
			}
		}
		o24_is_onoff = 0;	
		mutex_unlock(&o24_onoff_mutex);
	}

	return ret;
}

static int o24_pm_task_avs(pms_o24_work_t *pms_o24_work)
{
	int ret = 0;
	unsigned int type = 0;

	if (pms_o24_work->do_avs == 1) /* i2c */
	{
		pms_o24_work->do_avs = 0;
		//PM_NOTI("target_corevol[%d]\n",pms_o24_work->target_corevol );

		o24_SetCoreVal(pms_o24_work->target_corevol,pms_o24_work->ch);
	}
	else if (pms_o24_work->do_avs == 2) /* cpu regul */
	{
		pms_o24_work->do_avs = 0;
		type = pms_o24_work->target_vol;
#if 1
		switch(type){
			case CPU_AVS_S:
				//HV
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				PM_NOTI("SET CPU s\n" );
				break;
			case CPU_AVS_N:
				//MV
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_input(o24_cpuvid1);
				//gpiod_direction_input(o24_gpio71);
				gpiod_direction_output(o24_gpio71,0);
				PM_NOTI("SET CPU n\n" );
				break;
			case CPU_AVS_F:
				//LV
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				gpiod_direction_input(o24_cpuvid0);
				PM_NOTI("SET CPU f\n" );
				break;
			case CPU_AVS_FF:
				//VLV
				gpiod_direction_input(o24_cpuvid0);
				gpiod_direction_input(o24_cpuvid1);
				gpiod_direction_output(o24_gpio71,0);
				//gpiod_direction_input(o24_gpio71);
				PM_NOTI("SET CPU ff\n" );
				break;
			case CPU_AVS_FF_HIGH_TEMP:
				//VLV
				//ret = regulator_set_voltage(o24_regulator, O24_CPU_AVS_FF_HTEMP_UV,O24_CPU_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CPU hff slt\n" );
				break;
			default:
				//HV
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				PM_NOTI("SET CPU s\n" );
				break;
		}
#endif

	}
	else if (pms_o24_work->do_avs == 3) /* core regul */
	{
		pms_o24_work->do_avs = 0;
		type = pms_o24_work->target_corevol;

#if 0
		o24_coreregulator = regulator_get(NULL, "core-regulator");
		if (IS_ERR(o24_coreregulator)) {
			PM_ERROR("couldn't get coreregulator\n");
			return 0;
		}

		prevMV = regulator_get_voltage(o24_coreregulator) ;

		switch(type){
			case CORE_AVS_S:
				//HV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_S_UV,O24_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
			case CORE_AVS_N:
				//MV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_N_UV,O24_CORE_AVS_N_UV);
				PM_NOTI("SET CORE n\n" );
				break;
			case CORE_AVS_F:
				//LV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_F_UV,O24_CORE_AVS_F_UV);
				PM_NOTI("SET CORE f\n" );
				break;
			case CORE_AVS_FF:
				//VLV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_FF_UV,O24_CORE_AVS_FF_UV);
				PM_NOTI("SET CORE ff\n" );
				break;

			case CORE_AVS_S_HIGH_TEMP:
				//HV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_S_HTEMP_UV,O24_CORE_AVS_S_HTEMP_UV);
				PM_NOTI("SET CORE hs\n" );
				break;
			case CORE_AVS_N_HIGH_TEMP:
				//MV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_N_HTEMP_UV,O24_CORE_AVS_N_HTEMP_UV);
				PM_NOTI("SET CORE hn\n" );
				break;
			case CORE_AVS_F_HIGH_TEMP:
				//LV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_F_HTEMP_UV,O24_CORE_AVS_F_HTEMP_UV);
				PM_NOTI("SET CORE hf\n" );
				break;
			case CORE_AVS_FF_HIGH_TEMP:
				//VLV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_FF_HTEMP_UV,O24_CORE_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CORE hff\n" );
				break;

			default:
				//HV
				ret = regulator_set_voltage(o24_coreregulator, O24_CORE_AVS_S_UV,O24_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
		}
		PM_NOTI("CORE ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(o24_coreregulator) );
		regulator_put(o24_coreregulator);
#endif
	}
	return ret;
}

void o24_taskdisable_reset(void)
{
	g_o24_pm_task_disable = 0;
}

static void o24_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void o24_lgdtv_pm_task_call(pms_o24_work_t * o24work)
{
	if( o24_is_onoff == 0)
	{
		o24_set_work(o24work);
		complete(&cpu_hotplug_completion);
	}
}

static void o24_lgdtv_regul_task_reset(void)
{
	reinit_completion(&regulator_completion);
}
#if 0
static void o24_lgdtv_coreregul_task_reset(void)
{
	reinit_completion(&coreregulator_completion);
}
#endif

static void o24_lgdtv_regul_task_call(pms_o24_work_t  * o24_regulwork)
{
	o24_set_regul_work(o24_regulwork);
	complete(&regulator_completion);
}
static void o24_clk_task_call(pms_o24_work_t  * o24_work)
{
	if(spin_trylock(&g_o24_freq_lock))
	{
		o24_set_clk_work(o24_work);
		complete(&clk_completion);
		spin_unlock(&g_o24_freq_lock);
	}
}

static void o24_lgdtv_coreregul_task_call(pms_o24_work_t  * o24_coreregulwork)
{
	o24_set_coreregul_work(o24_coreregulwork);
	complete(&coreregulator_completion);
}

static int o24_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o24_work_t pms_o24_work;

	PM_NOTI("o24 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o24 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_o24_pm_task_disable == 1)
			continue;

		if (o24_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_o24_pm_lock, flags);
			memcpy((void *)&pms_o24_work, (void *)&g_o24_pms, sizeof(pms_o24_work_t));
			spin_unlock_irqrestore(&g_o24_pm_lock, flags);

			if(pm_o24_gov->get_mp_enable())
				o24_pm_task_hotplug(&pms_o24_work);
		//	if(pm_o24_gov->get_freq_enable())
		//		o24_pm_task_dvfs(&pms_o24_work);
		}

#ifdef	ERROR_PRINT_LOOP
		if(o24_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", o24_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}

static int o24_clk_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o24_work_t pms_o24_work;

	do {
		if (kthread_should_stop()) {
			PM_NOTI("o24_clk_pm_task - exit!\n");
			break;
		}
		reinit_completion(&clk_completion);
		wait_for_completion(&clk_completion);

		if (g_o24_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o24_clk_lock, flags);
		memcpy((void *)&pms_o24_work, (void *)&g_o24_clk, sizeof(pms_o24_work_t));
		spin_unlock_irqrestore(&g_o24_clk_lock, flags);
		if(pm_o24_gov->get_freq_enable())
		    o24_pm_task_dvfs(&pms_o24_work);

	} while (1);

	return 0;
}


static int o24_regulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o24_work_t pms_o24_work;

	PM_NOTI("o24_regulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o24_regulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&regulator_completion);
		wait_for_completion(&regulator_completion);

		PM_DEBUG_PRINT("regul task run in cpu%d\n", smp_processor_id());

		if (g_o24_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o24_regul_lock, flags);
		memcpy((void *)&pms_o24_work, (void *)&g_o24_regul, sizeof(pms_o24_work_t));
		spin_unlock_irqrestore(&g_o24_regul_lock, flags);
		o24_pm_task_avs(&pms_o24_work);

		PM_DEBUG_PRINT("REGUL TASK END\n");
	} while (1);

	return 0;
}

static int o24_coreregulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_o24_work_t pms_o24_work;

	PM_NOTI("o24_coreregulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("o24_coreregulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&coreregulator_completion);
		wait_for_completion(&coreregulator_completion);

		PM_DEBUG_PRINT("core regul task run in cpu%d\n", smp_processor_id());

		if (g_o24_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_o24_coreregul_lock, flags);
		memcpy((void *)&pms_o24_work, (void *)&g_o24_coreregul, sizeof(pms_o24_work_t));
		spin_unlock_irqrestore(&g_o24_coreregul_lock, flags);
		o24_pm_task_avs(&pms_o24_work);

		PM_DEBUG_PRINT("COREREGUL TASK END\n");
	} while (1);

	return 0;
}

void o24_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(o24_lgdtv_pm_task,
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
		clk_pm_task = kthread_create_on_node(o24_clk_pm_task,
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
		regulator_pm_task = kthread_create_on_node(o24_regulator_pm_task,
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
		coreregulator_pm_task = kthread_create_on_node(o24_coreregulator_pm_task,
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

static void o24_AllCoreOn(void)
{
	pms_o24_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_o24_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			o24_lgdtv_pm_task_call(&pms_work);
			msleep(100);		/* max cpu on time */
		}
	}
}

static void o24_SetMaxPerformance(void)
{
	reinit_completion(&cpu_hotplug_completion);
	reinit_completion(&clk_completion);
	reinit_completion(&regulator_completion);
	reinit_completion(&coreregulator_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	o24_AllCoreOn();

}

unsigned int o24_kdrv_pm_runtime_suspend = 0;
unsigned int mp_backup = 0;
void o24_set_kdrv_pm_runtime_suspend(void)
{
	pms_o24_work_t pms_work;
	int i;

	mutex_lock(&o24_kdrvpm_runtime_mutex);
	o24_kdrv_pm_runtime_suspend = 1;
	mp_backup = pm_o24_gov->get_mp_enable();
	pm_o24_gov->set_gov(PMS_GOV_DISABLE);
	pm_o24_gov->set_mp_enable(1);
	reinit_completion(&cpu_hotplug_completion);
	cpu_maps_update_begin();
	cpu_maps_update_done();

	memset(&pms_work, 0x0, sizeof(pms_o24_work_t));
	for(i=3; i>0; i--)
	{
		if (cpu_online(i) == 1)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = 0;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			o24_lgdtv_pm_task_call(&pms_work);
			msleep(200);
		}
	}
	o24_SetCPUFreq(1200);
	mutex_unlock(&o24_kdrvpm_runtime_mutex);
	PM_NOTI("kdrv_pm - runtime suspend OK\n");
}
void o24_set_kdrv_pm_runtime_resume(void)
{
	mutex_lock(&o24_kdrvpm_runtime_mutex);
	o24_SetMaxPerformance();
	pm_o24_gov->init();
	pm_o24_gov->set_mp_enable(mp_backup);
	pm_o24_gov->set_gov(PMS_GOV_ENABLE);
	o24_kdrv_pm_runtime_suspend = 0;
	mutex_unlock(&o24_kdrvpm_runtime_mutex);
	PM_NOTI("kdrv_pm - runtime resume OK\n");

}
void o24_FuncInit(void)
{

	/* o24 DCDC regulater vendor is fixed as TI
	   detailed info: http://clm.lge.com/issue/browse/SCDCR-1798 */

	if(o24_clk0_base == NULL)
		o24_clk0_base = ioremap(0xCC6A2060,0xc);
	if(o24_clk_pdb_base == NULL)
		o24_clk_pdb_base = ioremap(0xCC6A2090,0x4);
	if(o24_clk_src_base == NULL)
		o24_clk_src_base = ioremap(0xCA21000C,0x4);
	#if 0
	o24_freqtest = gpiod_get(&o24_gpiodev, "9", GPIOD_ASIS);
	if (IS_ERR(o24_freqtest))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",9,o24_freqtest);
	}
	#endif

	pm_o24_gov = get_o24_pm_gov();
	o24_pmtask_init();


}

static pms_o24_func_t o24_pm_func =
{
	.init = o24_FuncInit,
	.getfreq = o24_GetCPUFreq,
	.setfreq = o24_SetCPUFreq,
	.setcorevolt = o24_SetCoreVal,
	.setcore_switching_freq = o24_SetCoreSwitchingFreq,
	.getcorevolt = o24_GetCoreVal,
	.get_cpu_on = o24_GetCPUOn,
	.get_cpu_type = o24_GetCPUType,
	.set_max_performance = o24_SetMaxPerformance,
	.run = o24_lgdtv_pm_task_call,
	.run_clk = o24_clk_task_call,
	.run_regul = o24_lgdtv_regul_task_call,           //cpuregul
	.run_coreregul = o24_lgdtv_coreregul_task_call,   //coreregul
	.reset = o24_lgdtv_pm_task_reset,
	.reset_regul = o24_lgdtv_regul_task_reset,
	.taskdisable_reset = o24_taskdisable_reset,
	.get_sampling_rate = o24_get_sampling_rate,
	.set_sampling_rate = o24_set_sampling_rate,
	.get_error_state = o24_get_error_state,
	.set_error_state = o24_set_error_state,
};

pms_o24_func_t* get_o24_pm_func(void)
{
	return &o24_pm_func;
}

