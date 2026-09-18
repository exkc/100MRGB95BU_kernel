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

#include "pm_m23common.h"

#include "reg_ctrl.h"
#include "i2c_core.h"
#include "gpio_core.h"

#include <linux/regulator/consumer.h>

extern struct regulator *m23_regulator;
extern struct regulator *m23_coreregulator;

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
static DEFINE_SPINLOCK(g_m23_pm_lock);
static DEFINE_SPINLOCK(g_m23_regul_lock);

DEFINE_MUTEX(m23_onoff_mutex);

//static DEFINE_SPINLOCK(g_m23_cpuregul_lock);
//static DEFINE_SPINLOCK(g_m23_freq_lock);

static unsigned int m23_regul = 0;

unsigned int m23_is_onoff = 0;

module_param(m23_regul, uint, S_IRUGO);
MODULE_PARM_DESC(m23_gpuNP, "m23_regul");

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/
#define FREQ_SAME				0
#define FREQ_UP					1
#define FREQ_DOWN				2
#define FREQ_ONLY				3
#define VOL_ONLY				4
#define ERROR_MASK			0xffff
#define M23_MODEL_OPT10			5

#define REGULATOR_NONE	0
#define REGULATOR_TPS549A20 1
#define REGULATOR_TPS549B22 2
#define REGULATOR_MPS 3


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
#define VOUT_ADJUSTMENT_TI_MAX		1066		/*mV*/
#define VOUT_ADJUSTMENT_TI_MIN		699		/*mV*/

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

#define TPS549B22_VOUT_MAX		1140		/*mV*/
#define TPS549B22_VOUT_MIN		750		/*mV*/


/* MPS vendor core regulator subddr info  */

#define VSEL							0x00
#define VSEL_VBOOT_OFFSET				(0x7)	/* feedback contorl enable bit */
#define VSEL_OUTREF_OFFSET				(0x0)	/* output voltage reference  */

#define SYSCTRL1						0x01
#define SYSCTRL1_EN_OFFSET				(0x7)	/* feedback contorl enable bit */
#define SYSCTRL1_GOBIT_OFFSET			(0x6)	/* output voltage reference  */
#define SYSCTRL1_SLEWRATE_OFFSET		(0x3)	/* output voltage reference  */
#define SYSCTRL1_OVP_OFFSET				(0x2)	/* over voltage protection mode */
#define SYSCTRL1_OVC_OFFSET				(0x1)	/* over current protection mode */
#define SYSCTRL1_MODE_OFFSET			(0x0)	/* over current protection mode */

#define SYSCTRL1_SLEWRATE_40000			(0x0)
#define SYSCTRL1_SLEWRATE_30000			(0x1)
#define SYSCTRL1_SLEWRATE_20000			(0x2)
#define SYSCTRL1_SLEWRATE_10000			(0x3)
#define SYSCTRL1_SLEWRATE_5000			(0x4)
#define SYSCTRL1_SLEWRATE_2500			(0x5)
#define SYSCTRL1_SLEWRATE_1250			(0x6)
#define SYSCTRL1_SLEWRATE_625			(0x7)

#define SYSCTRL2						0x02
#define SYSCTRL2_PG_DEGLITCH_OFFSET		(0x6)
#define SYSCTRL2_PG_DEGLITCH_DFT		(0x3)

#define SYSCTRL2_SWITCHING_FREQ_OFFSET	(0x4)	/* operation switching freq  */
#define SYSCTRL2_SWITCHING_F_1250KHZ	(0x3)
#define SYSCTRL2_SWITCHING_F_1000KHZ	(0x2)
#define SYSCTRL2_SWITCHING_F_750KHZ		(0x1)
#define SYSCTRL2_SWITCHING_F_500KHZ		(0x0)

#define SYSCTRL2_SOFTSTOP_OFFSET		(0x3)
#define SYSCTRL2_SOFTSTOP_DFT			(0x0)

#define SYSCTRL2_CUR_LIMIT_ADJ_OFFSET	(0x0)
#define SYSCTRL2_CUR_LIMIT_DFT			(0x1)


#define REGULATOR_RETRY_CNT				2

#define VOUT_ADJUSTMENT_MPS_MAX			1140	/*mV*/
#define VOUT_ADJUSTMENT_MPS_MIN			750		/*mV*/

#define	OUTCURRENT						0x03
#define OUTCURRENT_OFFSET				(0x0)	/* operation current  */

#define	OUTVOLT							0x04
#define OUTVOLT_OFFSET					(0x0)	/* operation voltage  */

#define VOUT_ADJUSTMENT_MPS_MAX 		1140	/*mV*/
#define VOUT_ADJUSTMENT_MPS_MIN 		750		/*mV*/

#if 0
void __iomem *m23_clk0_base = NULL;
void __iomem *m23_clk1_base = NULL;
void __iomem *m23_clk_pdb_base = NULL;
void __iomem *m23_clk_src_base = NULL;
#endif



#ifdef M23_AVS_SLT
static  pms_m23_regulator_t  _stsltcpuRegulator[] =
{
	/* vbase== 1030->1040 mV */
	{1260,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_12_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1245,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1235,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1225,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1215,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1205,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1195,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1180,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1170,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1165,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1150,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1145,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1135,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1125,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1120,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1110,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1100,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1095,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1085,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1080,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1070,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1065,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1055,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1050,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1040,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1040,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1030,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1025,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1015,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1010,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{1000,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{995 ,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{985 ,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{980 ,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{970 ,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{960 ,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{955 ,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{945 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{935 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
	{925 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
	{915 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_03_2,OPERATION_OPMARGIN_VOML },
	{905 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
	{890 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
	{880 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
	{875 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
	{860 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
	{855 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
	{845 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
	{835 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
	{825 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },
};

static  pms_m23_regulator_t  _stsltcoreRegulator[] =
{
	/* vbase== 900->910 mV */
	{1100,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_12_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1090,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1080,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1070,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1060,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1055,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1045,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1035,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1025,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1015,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1010,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1000,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{990 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{985 ,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{980 ,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{970 ,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{965 ,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{960 ,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{950 ,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{945 ,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{935 ,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{930 ,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{925 ,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{915 ,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{910 ,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{910 ,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{905 ,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{895 ,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{890 ,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{885 ,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{875 ,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{870 ,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{860 ,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{855 ,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{850 ,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{840 ,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{835 ,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{830 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{820 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
	{810 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
	{800 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_03_2,OPERATION_OPMARGIN_VOML },
	{790 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
	{780 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
	{770 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
	{765 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
	{755 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
	{745 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
	{740 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
	{730 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
	{725 ,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },
}   ;

#else
static	pms_m23_regulator_t  _stRegulator[] =
{
	/* vbase== 883 mV */
	{1065,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1050,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_10_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1045,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_09_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1040,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_08_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1030,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_07_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1020,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_06_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1010,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_05_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{1000,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_04_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{ 995 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_03_7,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{ 985 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_02_8,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{ 975 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },
	{ 970 ,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_9,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_VOMH },

	{ 960,VOUT_ADJUSTMENT_UP_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 955,VOUT_ADJUSTMENT_UP_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 945,VOUT_ADJUSTMENT_UP_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 940,VOUT_ADJUSTMENT_UP_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 935,VOUT_ADJUSTMENT_UP_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 925,VOUT_ADJUSTMENT_UP_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 920,VOUT_ADJUSTMENT_UP_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 915,VOUT_ADJUSTMENT_UP_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 905,VOUT_ADJUSTMENT_UP_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 900,VOUT_ADJUSTMENT_UP_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 895,VOUT_ADJUSTMENT_UP_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 885,VOUT_ADJUSTMENT_UP_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 880,VOUT_ADJUSTMENT_UP_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 880,VOUT_ADJUSTMENT_DN_00,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 875,VOUT_ADJUSTMENT_DN_07,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 865,VOUT_ADJUSTMENT_DN_15,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 860,VOUT_ADJUSTMENT_DN_22,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 855,VOUT_ADJUSTMENT_DN_30,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 845,VOUT_ADJUSTMENT_DN_37,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 840,VOUT_ADJUSTMENT_DN_45,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 835,VOUT_ADJUSTMENT_DN_52,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 830,VOUT_ADJUSTMENT_DN_60,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 820,VOUT_ADJUSTMENT_DN_67,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 815,VOUT_ADJUSTMENT_DN_75,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 810,VOUT_ADJUSTMENT_DN_82,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },
	{ 800,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_00_0,OPERATION_OPMARGIN_OFF },

	{ 790,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_01_1,OPERATION_OPMARGIN_VOML },
	{ 780,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_02_1,OPERATION_OPMARGIN_VOML },
	{ 775,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_03_2,OPERATION_OPMARGIN_VOML },
	{ 765,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_04_2,OPERATION_OPMARGIN_VOML },
	{ 755,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_05_2,OPERATION_OPMARGIN_VOML },
	{ 745,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_06_2,OPERATION_OPMARGIN_VOML },
	{ 740,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_07_1,OPERATION_OPMARGIN_VOML },
	{ 730,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_08_1,OPERATION_OPMARGIN_VOML },
	{ 720,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_0,OPERATION_OPMARGIN_VOML },
	{ 715,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_09_9,OPERATION_OPMARGIN_VOML },
	{ 705,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_10_7,OPERATION_OPMARGIN_VOML },
	{ 700,VOUT_ADJUSTMENT_DN_90,VOUT_MARGIN_HIGH_00_0,VOUT_MARGIN_LOW_11_0,OPERATION_OPMARGIN_VOML },
}   ;
#endif

typedef struct
{
	UINT32 vout_ref;
	UINT32 vout_set;
}pms_m23_regulatorB_t;

/* TPS549B22 table */
static  pms_m23_regulatorB_t  _stRegulatorB[] =
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
};

/* MP8876 table */
static  pms_m23_regulatorB_t  _stRegulatorMPS[] =
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

#if 0
static struct task_struct *cpu_regulator_task;
static struct completion   cpu_regulator_completion;
static pms_m23_work_t g_m23_cpuregul;
#endif
static int g_m23_pm_task_disable = 0; 
static pms_m23_work_t g_m23_pms;
static pms_m23_work_t g_m23_regul;

static unsigned int g_m23_sampling_rate = 20; // 20ms
static unsigned int g_m23_core_vol = 0;

static unsigned int g_m23_err = 0;
static pms_m23_avs_t* pm_m23_avs = NULL;
static pms_m23_gov_t* pm_m23_gov = NULL;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/


#define M23_CORE_REGULATOR_IDX			2

#define M23_CORE_REGULATOR_DEVICE_ID_TPS549A20	0x3E
#define M23_CORE_REGULATOR_DEVICE_ID_TPS549B22	0x3A
#define M23_CORE_REGULATOR_DEVICE_ID_MPS	0xc0


static LX_I2C_DEV_HANDLE _i2c_core_regulator_handle;

int M23_CORE_REGUL_WRI2C( UINT8 ch, UINT8 subaddr,UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (m23_regul == REGULATOR_TPS549A20)
	{
		rc = REG_WriteI2CL(ch, M23_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data, nbyte);
	}
	else if (m23_regul == REGULATOR_TPS549B22)
	{
		rc = REG_WriteI2CL(ch, M23_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (m23_regul == REGULATOR_MPS)
	{
		rc = REG_WriteI2CL(ch, M23_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",m23_regul);
	}

	return rc;
}

int M23_CORE_REGUL_RDI2C(UINT8 ch, UINT8 subaddr, UINT8* data, UINT8 nbyte)
{
	int rc = 0;

	/* detect regulator type (ti/mps) */
	if (m23_regul == REGULATOR_TPS549A20)
	{
		rc = REG_ReadI2CL(ch , M23_CORE_REGULATOR_DEVICE_ID_TPS549A20,subaddr, data,nbyte);
	}
	else if (m23_regul == REGULATOR_TPS549B22)
	{
		rc = REG_ReadI2CL(ch, M23_CORE_REGULATOR_DEVICE_ID_TPS549B22,subaddr, data,nbyte);
	}
	else if (m23_regul == REGULATOR_MPS)
	{
		rc = REG_ReadI2CL(ch, M23_CORE_REGULATOR_DEVICE_ID_MPS,subaddr, data,nbyte);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",m23_regul);
	}

	return rc;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */

unsigned int m23_get_error_state(void)
{
	return g_m23_err;
}

int m23_set_error_state(unsigned int value)
{
	g_m23_err = value;

	return 0;
}

static void m23_set_work(pms_m23_work_t *m23_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_m23_pm_lock, flags);
	memcpy( &g_m23_pms,m23_work , sizeof(pms_m23_work_t));
	spin_unlock_irqrestore(&g_m23_pm_lock, flags);
}

static void m23_set_regul_work(pms_m23_work_t * m23_regulwork)
{
	unsigned long flags;

	spin_lock_irqsave(&g_m23_regul_lock, flags);
	memcpy( &g_m23_regul, m23_regulwork , sizeof(pms_m23_work_t));
	spin_unlock_irqrestore(&g_m23_regul_lock, flags);
}
#if 0
static void m23_set_cpuregul_work(pms_m23_work_t m23_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_m23_cpuregul_lock, flags);
	g_m23_cpuregul = m23_work;
	spin_unlock_irqrestore(&g_m23_cpuregul_lock, flags);
}
#endif

static int m23_GetCPUType(void)
{
	int ret = 0;
	pms_m23_avsinto_t info;

	pm_m23_avs = get_m23_pm_avs();
	ret = pm_m23_avs->get_cpu_avs_type(&info);

	return ret;
}

unsigned int m23_GetCPUOn(void)
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

unsigned int m23_cur_freq = 1400;
unsigned int m23_GetCPUFreq(void)
{

	unsigned int MHz = 0;

#ifdef USE_KER_CPUFREQ
	unsigned int KHz = 0;
	KHz = cpufreq_generic_get(0);
	MHz = KHz / 1000;
#else
	MHz = m23_cur_freq;
#endif
	return MHz;
}

int m23_SetCPUFreq(unsigned int freq)
{

#if 0
	unsigned long flags;
	int ret = 0;

	unsigned long long start,cur;
	unsigned long timeout = 100 * 1000000;
#ifdef USE_KER_CPUFREQ
	struct cpufreq_policy *policy;
	policy = cpufreq_cpu_get(0);
	if (policy != NULL)
		ret = cpufreq_driver_target(policy, freq*1000, CPUFREQ_RELATION_H);
#else
	if(freq == m23_cur_freq)
		return 0;
	spin_lock_irqsave(&g_m23_freq_lock, flags);

	//(1) cpu core clock source change (AIOPLLSS_CPU ---> core533_clk, 533MHz)
	if(m23_clk_src_base != NULL)
		writel(0x00000001, m23_clk_src_base);
	//(2) AIOPLLS_CPU pdb(power-down bar) enable, power-off(reset)
	if(m23_clk_pdb_base != NULL)
		writel(0x000007BF, m23_clk_pdb_base);

	if( freq == 1400) /* dft mode freq */
	{
		//(3) AIOPLLSS_CPU setting change
		if(m23_clk0_base != NULL)
			writel(0x000D4404, m23_clk0_base);
		if(m23_clk1_base != NULL)
			writel(0x18000212, m23_clk1_base);
		m23_cur_freq = freq;
	}
	else if( freq == 1050) /* normal freq case */
	{
		//(3) AIOPLLSS_CPU setting change
		if(m23_clk0_base != NULL)
			writel(0x000E7505, m23_clk0_base);
		if(m23_clk1_base != NULL)
			writel(0x18000312, m23_clk1_base);
		m23_cur_freq = freq;
	}
	//(4) AIOPLLSS_CPU pdb disable
	if(m23_clk_pdb_base != NULL)
		writel(0x000007FF, m23_clk_pdb_base);

	//(5) Wait 1ms
	mdelay(1);

	//(6) pll lock check (read)
	start = sched_clock();

	while ( (readl(m23_clk1_base) & 0x10) != 0x10) {  // PLL LOCK
		cur = sched_clock();
		if (cur - start > timeout) {
			printk("%s: freq timed out\n", __func__);
			return 0;
		}
	}

	//(7) cpu core clock source change
	if(m23_clk_src_base != NULL)
		writel(0x00000000, m23_clk_src_base);
	spin_unlock_irqrestore(&g_m23_freq_lock, flags);

	printk("Freq[%d]\n",freq);
#endif

	return ret;
#else
	return 0;
#endif
}


int m23_SetCoreSwitchingFreq(unsigned int freq)
{
	int ret = 0;
	UINT8  freq_set = FREQUENCY_CONFIG_400KHZ; /* default */
	unsigned data[5];

	if(freq > 1000 || freq < 250 )
	{
		PM_ERROR("check core switching freq[%d]mV\n",freq);
		return -1;
	}


	if(lx_i2c_cfg() & LX_I2C_CFG_LEGACY_MODE)
	{
		_i2c_core_regulator_handle= I2C_DevOpenPriv(0, 0);/* i2c0 */
		I2C_DevSetClock(_i2c_core_regulator_handle,I2C_CLOCK_400KHZ);
	}

	if (m23_regul == REGULATOR_TPS549A20)
	{
		if(0){}
		else if(freq >= 1000){ freq_set = FREQUENCY_CONFIG___1MHZ; }
		else if(freq >= 850){ freq_set = FREQUENCY_CONFIG_850KHZ; }
		else if(freq >= 750){ freq_set = FREQUENCY_CONFIG_750KHZ; }
		else if(freq >= 600){ freq_set = FREQUENCY_CONFIG_600KHZ; }
		else if(freq >=	500){ freq_set = FREQUENCY_CONFIG_500KHZ; }
		else if(freq >=	400){ freq_set = FREQUENCY_CONFIG_400KHZ; }
		else if(freq >=	300){ freq_set = FREQUENCY_CONFIG_300KHZ; }
		else if(freq >=	250){ freq_set = FREQUENCY_CONFIG_250KHZ; }
		/* switching frequency of DCDC	*/
		data[0]= freq_set << FREQUENCY_CONFIG_OFFSET;
		M23_CORE_REGUL_WRI2C(0, FREQUENCY_CONFIG, (UINT8 *)data ,1);

		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else if(m23_regul == REGULATOR_TPS549B22)
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
		M23_CORE_REGUL_WRI2C(0, MFR_SPECIFIC_03, (UINT8 *)data ,1);
		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else if(m23_regul == REGULATOR_MPS)
	{

		if(0){}

		else if(freq >= 1250){ freq_set =  SYSCTRL2_SWITCHING_F_1250KHZ; }
		else if(freq >= 1000){ freq_set =  SYSCTRL2_SWITCHING_F_1000KHZ; }
		else if(freq >= 750){ freq_set =  SYSCTRL2_SWITCHING_F_750KHZ; }
		else if(freq >= 500){ freq_set =  SYSCTRL2_SWITCHING_F_500KHZ; }
		data[0]=  SYSCTRL2_PG_DEGLITCH_DFT << SYSCTRL2_PG_DEGLITCH_OFFSET | freq_set << SYSCTRL2_SWITCHING_FREQ_OFFSET |
			SYSCTRL2_SOFTSTOP_DFT << SYSCTRL2_SOFTSTOP_OFFSET | SYSCTRL2_CUR_LIMIT_DFT << SYSCTRL2_CUR_LIMIT_ADJ_OFFSET;
		M23_CORE_REGUL_WRI2C(0, SYSCTRL2, (UINT8 *)data ,1);
		PM_NOTI("freq[%d]khz set[%d]\n",freq,freq_set);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d]\n",m23_regul);
	}


	return ret;
}

int __M23_TPS549A20_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0, i = 0;
	pms_m23_regulator_t * regul = NULL ;
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

#ifdef M23_AVS_SLT
	if(ch == 0)
	{
		for(i=0; i < sizeof(_stsltcoreRegulator)/sizeof(pms_m23_regulator_t); i++)
		{
			if(volt > _stsltcoreRegulator[i].vout_ref)
			{
				if( i == 0)
					regul = &_stsltcoreRegulator[0];
				else
					regul = &_stsltcoreRegulator[i-1];
				break;
			}
		}
	}
	else if(ch == 4)
	{
		for(i=0; i < sizeof(_stsltcpuRegulator)/sizeof(pms_m23_regulator_t); i++)
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
#else
	for(i=0; i < sizeof(_stRegulator)/sizeof(pms_m23_regulator_t); i++)
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
#endif

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

	g_m23_core_vol  = volt;

	//printf("opmargin[%x]\n",opmargin);
	/* switch converter on | turn off output voltage margin function */
	data[0]= OPERATION_ON_OFF | opmargin << OPERATION_OPMARGIN_OFFSET;
	ret = M23_CORE_REGUL_WRI2C((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_NOTI("check tpsA\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	M23_CORE_REGUL_WRI2C((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/* change switching frequency of DCDC from 400khz (default)
	   to 500khz as requested by HE */
	data[0]= FREQUENCY_CONFIG_500KHZ << FREQUENCY_CONFIG_OFFSET;
	M23_CORE_REGUL_WRI2C((UINT8)ch, FREQUENCY_CONFIG, (UINT8 *)data ,1);

	data[0]= vout_margin_high << VOUT_MARGIN_VOMH_OFFSET | vout_margin_low << VOUT_MARGIN_VOML_OFFSET ;
	M23_CORE_REGUL_WRI2C((UINT8)ch, VOUT_MARGIN,(UINT8 *)data,1);
	//printf("vout_margin_high[%x] vout_margin_low[%x]\n",vout_margin_high,vout_margin_low);

	data[0]= vout_set;
	M23_CORE_REGUL_WRI2C((UINT8)ch, VOUT_ADJUSTMENT,(UINT8 *)data,1);
	PM_NOTI("tiA ch [%d] volt[%d]mV set[0x%x:%d]\n",ch,volt,vout_set,vout_set);

	return ret;

}

int __M23_TPS549B22_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0;
	int i = 0;
	pms_m23_regulatorB_t * regul = NULL ;
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

	for(i=0; i < sizeof(_stRegulatorB)/sizeof(pms_m23_regulatorB_t); i++)
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
	g_m23_core_vol  = volt;

	data[0]= OPERATION_ON_OFF | 0 << OPERATION_OPMARGIN_OFFSET;
	ret = M23_CORE_REGUL_WRI2C((UINT8)ch, OPERATION, (UINT8 *)data ,1);
	if(ret < 0 )
	{
		PM_ERROR("check tpsB\n");
		return -1;
	}

	data[0]= ON_OFF_CONFIG_PU | ON_OFF_CONFIG_CMD | ON_OFF_CONFIG_CP | ON_OFF_CONFIG_PL | ON_OFF_CONFIG_SK;
	//PM_DEBUG( "ON_OFF_CONFIG [%x]\n",data[0]);
	M23_CORE_REGUL_WRI2C((UINT8)ch, ON_OFF_CONFIG, (UINT8 *)data ,1);

	/*set DCAP3 switching frequency of DCDC from 550khz as requested by HE */

	data[0]= 1 << MFR_SPECIFIC_03_DCAP3_OFFSET| 0 << MFR_SPECIFIC_03_RSCP_OFFSET |  MFR_SPECIFIC_03_FS_550K <<  MFR_SPECIFIC_03_FS_OFFSET ;
	//PM_DEBUG( "MFR_SPECIFIC_03 [%x]\n",data[0]);
	M23_CORE_REGUL_WRI2C((UINT8)ch, MFR_SPECIFIC_03, (UINT8 *)data ,1);

	data[0]= vout_set % 256;
	data[1]= vout_set / 256;
	//PM_DEBUG( "VOUT_COMMAND [%x] [%x]\n",data[0],data[1]);
	M23_CORE_REGUL_WRI2C((UINT8)ch, VOUT_COMMAND,(UINT8 *)data,2);
	PM_NOTI("tiB volt[%d]mV set[0x%x:%d]\n",volt,vout_set,vout_set);
	return ret;

}

int __M23_MPS_set_volt(unsigned int volt, unsigned int ch)
{
	int ret = 0;
	int i = 0;
	UINT8 data[5];
	UINT8 done = 0;
	pms_m23_regulatorB_t * regul = NULL ;
	UINT32 vout_set  = 0;

	//PM_NOTI("mps skip\n");
	//return 0;

	if(volt > VOUT_ADJUSTMENT_MPS_MAX || volt < VOUT_ADJUSTMENT_MPS_MIN )
	{
		PM_ERROR("check core volt[%d]mV\n",volt);
		return -1;
	}

	for(i=0; i < sizeof(_stRegulatorMPS)/sizeof(pms_m23_regulatorB_t); i++)
	{
		if(volt > _stRegulatorMPS[i].vout_ref)
		{
			if( i == 0)
				regul = &_stRegulatorMPS[0];
			else
				regul = &_stRegulatorMPS[i-1];
			break;
		}
	}

	if( regul != NULL)
	{
		vout_set = regul->vout_set;
	}
	else
	{
		PM_ERROR("check core volt[%d]mV i[%d]\n",volt,i);
	}
	g_m23_core_vol  = volt;

	/* switching freq as 500khz */
	data[0] = 3 << SYSCTRL2_PG_DEGLITCH_OFFSET | 0 << SYSCTRL2_SWITCHING_FREQ_OFFSET |
		0 << SYSCTRL2_SOFTSTOP_OFFSET | 1 << SYSCTRL2_CUR_LIMIT_ADJ_OFFSET;
	ret = M23_CORE_REGUL_WRI2C((UINT8)ch, SYSCTRL2, (UINT8 *)data,1);

	if(ret < 0 )
	{
		PM_ERROR("check mps\n");
		return -1;
	}

	data[0] = 1 << SYSCTRL1_EN_OFFSET | 1 << SYSCTRL1_GOBIT_OFFSET | 4 << SYSCTRL1_SLEWRATE_OFFSET |
		1 << SYSCTRL1_OVP_OFFSET | 1 << SYSCTRL1_OVC_OFFSET | 0 << SYSCTRL1_MODE_OFFSET ;
	M23_CORE_REGUL_WRI2C((UINT8)ch, SYSCTRL1, (UINT8 *)data,1);

	/* need to find valid vset table in mps */
	data[0] = vout_set << VSEL_OUTREF_OFFSET ;
	data[0] &= ~(1 << VSEL_VBOOT_OFFSET) ;
	M23_CORE_REGUL_WRI2C((UINT8)ch, VSEL, (UINT8 *)data ,1);
	PM_NOTI("mps volt[%d]mV vsel set[0x%x:%d] \n",volt,data[0],data[0]);

	while( done == 0)
	{
		M23_CORE_REGUL_RDI2C((UINT8)ch, SYSCTRL1, (UINT8 *)data ,1);
		if(( data[0] & (1 <<SYSCTRL1_GOBIT_OFFSET)) == 0 )
		{
			done = 1;
			break;
		}
		i++;
		if(i == REGULATOR_RETRY_CNT)
		{
			PM_ERROR("check mps done %d\n",i);
			return -1;
		}
		udelay(200);

	}

	return 0;
}


int m23_SetCoreVal(unsigned int volt, unsigned int ch)
{
	int ret = 0;

	if(lx_i2c_cfg() & LX_I2C_CFG_LEGACY_MODE)
	{
		_i2c_core_regulator_handle= I2C_DevOpenPriv(0, 0);/* i2c0 */
		I2C_DevSetClock(_i2c_core_regulator_handle,I2C_CLOCK_400KHZ);
	}


	if (m23_regul == REGULATOR_TPS549A20)
	{
		ret =__M23_TPS549A20_set_volt(volt, ch);
	}
	else if (m23_regul == REGULATOR_TPS549B22)
	{
		ret = __M23_TPS549B22_set_volt(volt,ch);
	}
	else if (m23_regul == REGULATOR_MPS)
	{
		ret = __M23_MPS_set_volt(volt, ch);
	}
	else
	{
		PM_NOTI("check DCDC vendor[%d:%d]\n",m23_regul,ch);
	}
#if 0
	else if (m23_regul == REGULATOR_MPS)
	{
		if(volt > VOUT_ADJUSTMENT_MPS_MAX || volt < VOUT_ADJUSTMENT_MPS_MIN )
		{
			PM_ERROR("check mps core volt[%d]mV\n",volt);
			return -1;
		}

		data[0]= 1 << VSEL_VBOOT_OFFSET || VSEL_OUTREF_945MV << VSEL_OUTREF_OFFSET;
		ret = M23_CORE_REGUL_WRI2C(VSEL, (UINT8 *)data ,1);
		if(ret < 0 )
		{
			PM_NOTI("check hwopt(10) for mps regulator vendor\n");
			return -1;
		}

		if( volt >	VSEL_OUTREF_BASEMV )
		{
			M23_CORE_REGUL_RDI2C(SYSCTRL1, data ,1);

			data[0] |= 1 << SYSCTRL1_EN_OFFSET | 1 << SYSCTRL1_GOBIT_OFFSET;
			PM_NOTI("sysctrl1  data[%x] \n",data[0]);
			M23_CORE_REGUL_WRI2C(SYSCTRL1, (UINT8 *)data,1);

			M23_CORE_REGUL_RDI2C(VSEL, data ,1);

			data[0] =  (127 *(volt - VSEL_OUTREF_BASEMV - BOARD_MARGIN_MV )/950) << VSEL_OUTREF_OFFSET & 0xff;
			data[0] &=  ~(1 << VSEL_VBOOT_OFFSET) ;

			PM_NOTI("mps volt[%d]mV set[0x%x] opt[%d]\n",volt,data[0],m23_regul);
			M23_CORE_REGUL_WRI2C(VSEL, (UINT8 *)data ,1);
		}
		else
		{
			PM_NOTI("check mps volt[%d]mV \n",volt);
		}
	}
#endif
	PM_DEBUG("m23_regul[%x] ret[%d]\n",m23_regul ,ret);


	return ret;
}
unsigned int m23_GetCoreVal(void)
{
	unsigned int mV = g_m23_core_vol;
	return mV;
}


static unsigned int m23_get_sampling_rate(void)
{
	return g_m23_sampling_rate;
}

static int m23_set_sampling_rate(unsigned int ms)
{
	g_m23_sampling_rate = ms;

	return 0;
}

static int m23_pm_task_dvfs(pms_m23_work_t *pms_m23_work)
{
	int ret = 0;
#ifdef USE_KER_CPUFREQ
	struct cpufreq_policy *policy;
	if ((pms_m23_work->do_dvfs == 1) || (pms_m23_work->do_dvfs == 2))
	{
		pms_m23_work->do_dvfs = 0;
		policy = cpufreq_cpu_get(0);
		if (policy != NULL)
			ret = cpufreq_driver_target(policy, pms_m23_work->target_freq*1000, CPUFREQ_RELATION_H);
		else
			ret = 1;

		if(ret != 0)
			m23_set_error_state(0xF << 28 | pms_m23_work->target_freq << 16 | (ERROR_MASK & ret));
	}
	else if (pms_m23_work->do_dvfs == 3)
#else
		if (pms_m23_work->do_dvfs == 1)
		{
			pms_m23_work->do_dvfs = 0;
			ret = m23_SetCPUFreq(pms_m23_work->target_freq);
			if(ret != 0)
				m23_set_error_state(0xF << 28 | pms_m23_work->target_freq << 16 | (ERROR_MASK & ret));
		}
#endif
	return ret;
}

static int m23_pm_task_hotplug(pms_m23_work_t *pms_m23_work)
{
	struct device * pCpudev = NULL;
	int ret = 0;

	if (pms_m23_work->do_hotplug && (m23_get_error_state() == 0))
	{
		pms_m23_work->do_hotplug = 0;
		mutex_lock(&m23_onoff_mutex);
		m23_is_onoff = 1;	
		if (pms_m23_work->core_onoff == 0)
		{
			if (cpu_online(pms_m23_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = remove_cpu(pms_m23_work->core_n);
#else
				ret = cpu_down(pms_m23_work->core_n);
#endif
				if(ret != 0)
				{
					if (ret != -EBUSY)
						m23_set_error_state(0xD << 28 | pms_m23_work->core_n << 24 | pms_m23_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_m23_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 1;
					device_unlock(pCpudev);
				}
			}
		}
		else
		{
			if (!cpu_online(pms_m23_work->core_n))
			{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0))
				ret = add_cpu(pms_m23_work->core_n);
#else
				ret = cpu_up(pms_m23_work->core_n);
#endif
				if(ret != 0)
				{
					if (ret != -EBUSY)
						m23_set_error_state(0xD << 28 | pms_m23_work->core_n << 24 | pms_m23_work->core_onoff << 16 | (ERROR_MASK & ret));
				}
				else
				{
					pCpudev = get_cpu_device(pms_m23_work->core_n);
					device_lock(pCpudev);
					pCpudev->offline = 0;
					device_unlock(pCpudev);
				}
			}
		}
		m23_is_onoff = 0;	
		mutex_unlock(&m23_onoff_mutex);
	}

	return ret;
}

static int m23_pm_task_avs(pms_m23_work_t *pms_m23_work)
{
	int ret = 0;
	int prevMV = 0;
	unsigned int type = 0;

	if (pms_m23_work->do_avs == 1) /* i2c */
	{
		pms_m23_work->do_avs = 0;
		m23_SetCoreVal(pms_m23_work->target_corevol,pms_m23_work->ch);
	}
	else if (pms_m23_work->do_avs == 2) /* cpu regul */
	{
		pms_m23_work->do_avs = 0;
		type = pms_m23_work->target_vol;

		m23_regulator = regulator_get(NULL, "cpu0");
		if (IS_ERR(m23_regulator)) {
			PM_ERROR("couldn't get cpu0 regulator regulator\n");
			return 0;
		}

		prevMV = regulator_get_voltage(m23_regulator) ;

		switch(type){
			case CPU_AVS_S:
				//HV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_S_UV,M23_CPU_AVS_S_UV);
				PM_NOTI("SET CPU s\n" );
				break;
			case CPU_AVS_N:
				//MV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_N_UV,M23_CPU_AVS_N_UV);
				PM_NOTI("SET CPU n\n" );
				break;
			case CPU_AVS_F:
				//LV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_F_UV,M23_CPU_AVS_F_UV);
				PM_NOTI("SET CPU f\n" );
				break;
			case CPU_AVS_FF:
				//VLV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_FF_UV,M23_CPU_AVS_FF_UV);
				PM_NOTI("SET CPU ff\n" );
				break;
			case CPU_AVS_FF_HIGH_TEMP:
				//VLV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_FF_HTEMP_UV,M23_CPU_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CPU hff slt\n" );
				break;
			default:
				//HV
				ret = regulator_set_voltage(m23_regulator, M23_CPU_AVS_S_UV,M23_CPU_AVS_S_UV);
				PM_NOTI("SET CPU s\n" );
				break;
		}
		PM_NOTI("CPU ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(m23_regulator) );
		regulator_put(m23_regulator);

	}
	else if (pms_m23_work->do_avs == 3) /* core regul */
	{
		pms_m23_work->do_avs = 0;
		type = pms_m23_work->target_corevol;

		m23_coreregulator = regulator_get(NULL, "core-regulator");
		if (IS_ERR(m23_coreregulator)) {
			PM_ERROR("couldn't get coreregulator\n");
			return 0;
		}

		prevMV = regulator_get_voltage(m23_coreregulator) ;

		switch(type){
			case CORE_AVS_S:
				//HV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_S_UV,M23_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
			case CORE_AVS_N:
				//MV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_N_UV,M23_CORE_AVS_N_UV);
				PM_NOTI("SET CORE n\n" );
				break;
			case CORE_AVS_F:
				//LV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_F_UV,M23_CORE_AVS_F_UV);
				PM_NOTI("SET CORE f\n" );
				break;
			case CORE_AVS_FF:
				//VLV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_FF_UV,M23_CORE_AVS_FF_UV);
				PM_NOTI("SET CORE ff\n" );
				break;

			case CORE_AVS_S_HIGH_TEMP:
				//HV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_S_HTEMP_UV,M23_CORE_AVS_S_HTEMP_UV);
				PM_NOTI("SET CORE hs\n" );
				break;
			case CORE_AVS_N_HIGH_TEMP:
				//MV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_N_HTEMP_UV,M23_CORE_AVS_N_HTEMP_UV);
				PM_NOTI("SET CORE hn\n" );
				break;
			case CORE_AVS_F_HIGH_TEMP:
				//LV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_F_HTEMP_UV,M23_CORE_AVS_F_HTEMP_UV);
				PM_NOTI("SET CORE hf\n" );
				break;
			case CORE_AVS_FF_HIGH_TEMP:
				//VLV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_FF_HTEMP_UV,M23_CORE_AVS_FF_HTEMP_UV);
				PM_NOTI("SET CORE hff\n" );
				break;

			default:
				//HV
				ret = regulator_set_voltage(m23_coreregulator, M23_CORE_AVS_S_UV,M23_CORE_AVS_S_UV);
				PM_NOTI("SET CORE s\n" );
				break;
		}
		PM_NOTI("CORE ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(m23_coreregulator) );
		regulator_put(m23_coreregulator);
	}
	return ret;
}

#if 0
static void m23_cpuregul_task_call(pms_m23_work_t m23work)
{
	m23_set_cpuregul_work(m23work);
	complete(&cpu_regulator_completion);
}
#endif
void m23_taskdisable_reset(void)
{
	g_m23_pm_task_disable = 0;
}

static void m23_lgdtv_pm_task_reset(void)
{
	reinit_completion(&cpu_hotplug_completion);
}

static void m23_lgdtv_pm_task_call(pms_m23_work_t * m23work)
{
	if( m23_is_onoff == 0)
	{
		m23_set_work(m23work);
		complete(&cpu_hotplug_completion);
	}
}

static void m23_lgdtv_regul_task_reset(void)
{
	reinit_completion(&regulator_completion);
}

static void m23_lgdtv_regul_task_call(pms_m23_work_t  * m23_regulwork)
{
	m23_set_regul_work(m23_regulwork);
	complete(&regulator_completion);
}


static int m23_lgdtv_pm_task(void *pParam)
{
	unsigned long flags;

	pms_m23_work_t pms_m23_work;

	PM_NOTI("m23 lgdtv_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("m23 lgdtv_pm_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_hotplug_completion);
		wait_for_completion(&cpu_hotplug_completion);

		PM_DEBUG_PRINT("PM TASK START\n");
		PM_DEBUG_PRINT("task run in cpu%d\n", smp_processor_id());

		if (g_m23_pm_task_disable == 1)
			continue;

		if (m23_get_error_state()== 0)
		{
			spin_lock_irqsave(&g_m23_pm_lock, flags);
			memcpy((void *)&pms_m23_work, (void *)&g_m23_pms, sizeof(pms_m23_work_t));
			spin_unlock_irqrestore(&g_m23_pm_lock, flags);

			if(pm_m23_gov->get_freq_enable())
				m23_pm_task_dvfs(&pms_m23_work);
			if(pm_m23_gov->get_mp_enable())
				m23_pm_task_hotplug(&pms_m23_work);

#ifndef	ERROR_PRINT_LOOP
			if(m23_get_error_state() != 0)
			{
				PM_DEBUG("GOV[%x]\n", m23_get_error_state());
			}
#endif
		}

#ifdef	ERROR_PRINT_LOOP
		if(m23_get_error_state() != 0)
		{
			PM_DEBUG("GOV[%x]\n", m23_get_error_state());
		}
#endif

		PM_DEBUG_PRINT("PM TASK END\n");
	} while (1);

	return 0;
}

#if 0
static int m23_cpu_regulator_task(void *pParam)
{
	unsigned long flags;

	pms_m23_work_t pms_m23_work;

	PM_NOTI("m23_cpuregul_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("m23_cpuregul_task - exit!\n");
			break;
		}

		reinit_completion(&cpu_regulator_completion);
		wait_for_completion(&cpu_regulator_completion);

		PM_DEBUG_PRINT("cpu regul task run in cpu%d\n", smp_processor_id());

		if (g_m23_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_m23_cpuregul_lock, flags);
		memcpy((void *)&pms_m23_work, (void *)&g_m23_cpuregul, sizeof(pms_m23_work_t));
		spin_unlock_irqrestore(&g_m23_cpuregul_lock, flags);
		m23_pm_task_avs(&pms_m23_work);

		PM_DEBUG_PRINT("CPUREGUL TASK END\n");
	} while (1);

	return 0;
}
#endif

static int m23_regulator_pm_task(void *pParam)
{
	unsigned long flags;

	pms_m23_work_t pms_m23_work;

	PM_NOTI("m23_regulator_pm_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			PM_NOTI("m23_regulator_pm_task - exit!\n");
			break;
		}

		reinit_completion(&regulator_completion);
		wait_for_completion(&regulator_completion);

		PM_DEBUG_PRINT("regul task run in cpu%d\n", smp_processor_id());

		if (g_m23_pm_task_disable == 1)
			continue;

		spin_lock_irqsave(&g_m23_regul_lock, flags);
		memcpy((void *)&pms_m23_work, (void *)&g_m23_regul, sizeof(pms_m23_work_t));
		spin_unlock_irqrestore(&g_m23_regul_lock, flags);
		m23_pm_task_avs(&pms_m23_work);

		PM_DEBUG_PRINT("REGUL TASK END\n");
	} while (1);

	return 0;
}


void m23_pmtask_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;

	cpu = 0;	// fix cpu 0

	// pmdrv_task_init
	if (cpu_hotplug_pm_task == NULL) {
		init_completion(&cpu_hotplug_completion);
		cpu_hotplug_pm_task = kthread_create_on_node(m23_lgdtv_pm_task,
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
		regulator_pm_task = kthread_create_on_node(m23_regulator_pm_task,
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

#if 0
	if (cpu_regulator_task == NULL) {
		init_completion(&cpu_regulator_completion);
		cpu_regulator_task = kthread_create_on_node(m23_cpu_regulator_task,
				NULL,
				cpu,
				"CPUREGULTASK/%lu", targetcpu);

		if (likely(!IS_ERR(cpu_regulator_task))) {
			kthread_bind(cpu_regulator_task, targetcpu);
			wake_up_process(cpu_regulator_task);
			PM_NOTI("CPUREGUL create successed\n");
		} else
			PM_NOTI("CPUREGUL create failed\n");
	}
#endif
}

static void m23_AllCoreOn(void)
{
	pms_m23_work_t pms_work;
	int i;

#define CPU_OFF 			0
#define CPU_ON				1

	memset(&pms_work, 0x0, sizeof(pms_m23_work_t));

	for(i=1; i<4; i++)
	{
		if (cpu_online(i) == 0)
		{
			pms_work.core_n = i;
			pms_work.core_onoff = CPU_ON;
			pms_work.do_hotplug = 1;
			pms_work.do_dvfs = 0;
			m23_lgdtv_pm_task_call(&pms_work);
			msleep(100);		/* max cpu on time */
		}
	}
}

static void m23_SetMaxPerformance(void)
{
	reinit_completion(&cpu_hotplug_completion);
	reinit_completion(&regulator_completion);

	cpu_maps_update_begin();
	cpu_maps_update_done();

	m23_AllCoreOn();

}


void m23_FuncInit(void)
{

	/* m23 DCDC regulater vendor is fixed as TI
	   detailed info: http://clm.lge.com/issue/browse/SCDCR-1798 */

#if 0
	if(m23_clk0_base == NULL)
		m23_clk0_base = ioremap(0xC6033010,0x4);
	if(m23_clk1_base == NULL)
		m23_clk1_base = ioremap(0xC6033018,0x4);
	if(m23_clk_pdb_base == NULL)
		m23_clk_pdb_base = ioremap(0xC603306C,0x4);
	if(m23_clk_src_base == NULL)
		m23_clk_src_base = ioremap(0xCAA10018,0x4);
#endif

	pm_m23_gov = get_m23_pm_gov();
	m23_pmtask_init();


}

static pms_m23_func_t m23_pm_func =
{
	.init = m23_FuncInit,
	.getfreq = m23_GetCPUFreq,
	.setfreq = m23_SetCPUFreq,
	.setcorevolt = m23_SetCoreVal,
	.setcore_switching_freq = m23_SetCoreSwitchingFreq,
	.getcorevolt = m23_GetCoreVal,
	.get_cpu_on = m23_GetCPUOn,
	.get_cpu_type = m23_GetCPUType,
	.set_max_performance = m23_SetMaxPerformance,
	.run = m23_lgdtv_pm_task_call,
	.run_regul = m23_lgdtv_regul_task_call,
	.reset = m23_lgdtv_pm_task_reset,
	.reset_regul = m23_lgdtv_regul_task_reset,
	.taskdisable_reset = m23_taskdisable_reset,
	.get_sampling_rate = m23_get_sampling_rate,
	.set_sampling_rate = m23_set_sampling_rate,
	.get_error_state = m23_get_error_state,
	.set_error_state = m23_set_error_state,
};

pms_m23_func_t* get_m23_pm_func(void)
{
	return &m23_pm_func;
}

