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
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include "os_util.h"

#include "gpio_core.h"

#include "pm_m23common.h"

#include "sys_regs.h"
#include "gpio_reg.h"

#include "sys_io.h"
#include <linux/regulator/consumer.h>
#include <linux/delay.h>

#include <linux/tick.h>
#include <linux/device.h>
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include <linux/regulator/consumer.h>
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

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/


#define M23_GPIO_AVS_CPU0         26
#define M23_GPIO_AVS_CPU1         27

#define M23_GPIO_AVS_CPU0_B0         26
#define M23_GPIO_AVS_CPU1_B0         27


#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

#define M23_CORE_SIDD_F_MIN_TH_AX   50     //mA

/* caution: core sidd is used for cpu avs range */
#ifdef M23_AVS_SLT
#define M23_CPU_SIDD_FF_MIN_TH_AX   150     //mA
#define M23_CPU_SIDD_F_MIN_TH_AX    100     //mA
#else
#define M23_CPU_SIDD_FF_MIN_TH_AX   150     //mA
#define M23_CPU_SIDD_F_MIN_TH_AX    100     //mA
#endif

#define M23_CORE_SIDD_VALID_MIN     1 //mA
#define M23_CORE_SIDD_VALID_MAX     1000 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5

//#define M23_REGUL_GET_MAX		30

struct delayed_work m23_avs_cpu_dw;
struct delayed_work m23_avs_core_dw;
struct workqueue_struct *m23_avscputime_wq;
struct workqueue_struct *m23_avscoretime_wq;
struct workqueue_struct *m23_avscpu_wq;
struct workqueue_struct *m23_avscore_wq;

int m23_cpuwork_stage = 0;
int m23_cpuwork_target = 0;
int m23_corework_stage = 0;
int m23_corework_target = 0;

/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_m23[6] = { "XXX","1000","970","940", "910","xxx", };
static char * cpu_vidttype[6] = { "GPIO26[1] 27[1]","GPIO 26[1] 27[1]","GPIO 26[1] 27[0]","GPIO 26[0] 27[1]","GPIO 26[0] 27[0]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_m23[6] = { "XXX","880","850","820", "790","xxx", };
char * core_volttype_high_m23[6] = { "XXX","880","850","820", "790","xxx", };
static char * core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

static unsigned int m23_avsinfo = 0;
static unsigned int m23_cpu_avs = 0;
static unsigned int m23_core_avs = 0;
static unsigned int m23_cpuHS = 0;
static unsigned int m23_cpuNP = 0;
static unsigned int m23_gpuHS = 0;
static unsigned int m23_gpuNP = 0;
extern int m23_pms_tcorevol;
extern int m23_is_prepared;

//static UINT32 core_avs= 0, cpu_avs = 0;

module_param(m23_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(m23_avsinfo, "m23_avsinfo");

module_param(m23_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(m23_cpu_avs, "m23_cpu_avs");

module_param(m23_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(m23_core_avs, "m23_core_avs");

module_param(m23_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(m23_cpuHS, "m23_cpuHS");

module_param(m23_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(m23_cpuNP, "m23_cpuNP");

module_param(m23_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(m23_gpuHS, "m23_gpuHS");

module_param(m23_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(m23_gpuNP, "m23_gpuNP");

static unsigned int cpu_sidd_ff_min_th;
static unsigned int cpu_sidd_f_min_th;

static unsigned int core_sidd_f_min_th;

pms_m23_avsinto_t	m23_avs_info;

m23_sidd_t gSidd_check_table_m23[SIDD_CHECK_TABLE_NUM]={

	[SIDD_CHECK_TABLE_AX]={
	.cpu_sidd_ff_min = M23_CPU_SIDD_FF_MIN_TH_AX,
	.cpu_sidd_f_min = M23_CPU_SIDD_F_MIN_TH_AX,

	.core_sidd_f_min = M23_CORE_SIDD_F_MIN_TH_AX,

	.core_sidd_valid_max = M23_CORE_SIDD_VALID_MAX,
	.core_sidd_valid_min = M23_CORE_SIDD_VALID_MIN
	},
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


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static pms_m23_func_t* pm_m23_func = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/

struct gpio_desc *m23_gpiod = NULL;
struct device m23_gpiodev =
{
	.init_name = "gpio_kerneltable",
};

#define TS_BIAS_OFFSET      (0x18)
#define TS_BIAS_DFT         (0x9EAA)

#define TS_MUX_ON           ( 1 << 29)
#define TS_SEL_CHOP         ( 1 << 15)
#define TS_SET_CLK          ( 1 << 9 )
#define TS_SEL_TRIM_DFT     (0x80)
#define TS_SEL_TRIM         ( TS_SEL_TRIM_DFT << 1)
#define TS_PDB              ( 1 << 0 )

static unsigned int ts_timer_count = 0;
static unsigned int	ts_timer_count_1s = HZ / ((HZ / 100) * (20 / 10));
int m23_slt_high = 0;
void __iomem *m23_cpu_ts_base = NULL;


static void m23_avs_cpuwork_req(void)
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(m23_avscpu_wq,&m23_avs_cpu_dw,msecs_to_jiffies(M23_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(m23_avscpu_wq,&m23_avs_cpu_dw,msecs_to_jiffies(M23_AVS_STEP_DELAY));
}

static void m23_avs_corework_req(void)
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(m23_avscore_wq,&m23_avs_core_dw,msecs_to_jiffies(M23_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(m23_avscore_wq,&m23_avs_core_dw,msecs_to_jiffies(M23_AVS_STEP_DELAY));


}

void m23_avs_corework_func(struct work_struct *work)
{
	struct regulator *coreregulator;
	int ret = 0;

	if(m23_is_prepared){
		PM_NOTI("SET CORE SKIP\n" );
		return;
	}
	coreregulator = regulator_get(NULL, "core-regulator");
	if (IS_ERR(coreregulator)) {
		PM_ERROR("couldn't get coreregulator\n");
		return ;
	}

	if(m23_corework_target >= CORE_AVS_S && m23_corework_target <= CORE_AVS_FF){
		if(m23_corework_stage == 3){
			ret = regulator_set_voltage(coreregulator, M23_CORE_AVS_FF_UV,M23_CORE_AVS_FF_UV);
			regulator_put(coreregulator);
			PM_NOTI("SET CORE FF\n" );
			m23_corework_stage++;
			goto coreavs_subwork;
		}
		else if(m23_corework_stage == 2){
			ret = regulator_set_voltage(coreregulator,M23_CORE_AVS_F_UV,M23_CORE_AVS_F_UV);
			regulator_put(coreregulator);
			PM_NOTI("SET CORE F\n" );
			m23_corework_stage++;
			goto coreavs_subwork;
		}
		else if(m23_corework_stage == 1){
			ret = regulator_set_voltage(coreregulator, M23_CORE_AVS_N_UV,M23_CORE_AVS_N_UV);
			regulator_put(coreregulator);
			PM_NOTI("SET CORE N\n" );
			m23_corework_stage++;
			goto coreavs_subwork;
		}
		else if(m23_corework_stage == 0){
			ret = regulator_set_voltage(coreregulator, M23_CORE_AVS_S_UV,M23_CORE_AVS_S_UV);
			regulator_put(coreregulator);
			PM_NOTI("SET CORE S\n" );
			m23_corework_stage++;
			goto coreavs_subwork;
		}
	}
	else{
		ret = regulator_set_voltage(coreregulator, M23_CORE_AVS_S_UV,M23_CORE_AVS_S_UV);
		regulator_put(coreregulator);
		m23_corework_stage = 0;
		m23_corework_target = 0;
		goto end_coreavs_subowrk;
	}

coreavs_subwork:
	if(m23_corework_target != m23_corework_stage){
		m23_avs_corework_req();
	}
end_coreavs_subowrk:
	if(m23_corework_target == m23_corework_stage)
	{
		PM_NOTI("COREAVS[%d] [%d][%d]\n",ret,m23_corework_target,m23_corework_stage );
		m23_corework_stage = 0;
		m23_corework_target = 0;
	}
	if(m23_is_prepared)
		PM_NOTI("SET CORE SKIP\n" );
	return ;
}

void m23_avs_cpuwork_func(struct work_struct *work)
{
	struct regulator *regulator;
	int ret = 0;

	if(m23_is_prepared){
		PM_NOTI("SET CPU SKIP\n" );
		return;
	}
	regulator = regulator_get(NULL, "cpu0");
	if (IS_ERR(regulator)) {
		PM_ERROR("couldn't get cpu0 regulator regulator\n");
		return ;
	}

	if(m23_cpuwork_target >= CPU_AVS_S && m23_cpuwork_target <= CPU_AVS_FF){
		if(m23_cpuwork_stage == 3){
			ret = regulator_set_voltage(regulator, M23_CPU_AVS_FF_UV,M23_CPU_AVS_FF_UV);
			regulator_put(regulator);
			PM_NOTI("SET CPU FF\n" );
			m23_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(m23_cpuwork_stage == 2){
			ret = regulator_set_voltage(regulator, M23_CPU_AVS_F_UV,M23_CPU_AVS_F_UV);
			regulator_put(regulator);
			PM_NOTI("SET CPU F\n" );
			m23_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(m23_cpuwork_stage == 1){
			ret = regulator_set_voltage(regulator, M23_CPU_AVS_N_UV,M23_CPU_AVS_N_UV);
			regulator_put(regulator);
			PM_NOTI("SET CPU N\n" );
			m23_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(m23_cpuwork_stage == 0){
			ret = regulator_set_voltage(regulator, M23_CPU_AVS_S_UV,M23_CPU_AVS_S_UV);
			regulator_put(regulator);
			PM_NOTI("SET CPU S\n" );
			m23_cpuwork_stage++;
			goto cpuavs_subwork;
		}

	}
	else{
		ret = regulator_set_voltage(regulator, M23_CPU_AVS_S_UV,M23_CPU_AVS_S_UV);
		regulator_put(regulator);
		m23_cpuwork_stage = 0;
		m23_cpuwork_target = 0;
		goto end_cpuavs_subowrk;
	}

cpuavs_subwork:
	if(m23_cpuwork_target != m23_cpuwork_stage){
		m23_avs_cpuwork_req();
	}
end_cpuavs_subowrk:
	if(m23_cpuwork_target == m23_cpuwork_stage)
	{
		PM_NOTI("CPUAVS[%d] [%d][%d]\n",ret,m23_cpuwork_target,m23_cpuwork_stage );
		m23_cpuwork_stage = 0;
		m23_cpuwork_target = 0;
	}
	if(m23_is_prepared)
		PM_NOTI("SET CPU SKIP\n" );
	return ;
}

struct regulator *m23_regulator = NULL;
struct regulator *m23_coreregulator = NULL;



/* cpuavs(regulator) is_step 0 run only in task*/
int __pm_m23_set_vol(UINT32 core_cpu, UINT32 type, UINT32 ch, UINT32 is_step)
{
	pms_m23_work_t pms_work ;

	memset(&pms_work, 0x0, sizeof(pms_m23_work_t));
	pm_m23_func = get_m23_pm_func();

	if ((is_step == 1) && (core_cpu == GPIO_AVS_CPU )){	/* set avs step  */
		m23_cpuwork_target = type;
		m23_cpuwork_stage = 0;
		queue_delayed_work(m23_avscpu_wq,&m23_avs_cpu_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 1) && (core_cpu == GPIO_AVS_CORE )){	/* set core avs step  */
		m23_corework_target = type;
		m23_corework_stage = 0;
		queue_delayed_work(m23_avscore_wq,&m23_avs_core_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CPU)){
		pms_work.target_vol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = 2;
		pm_m23_func->run_regul(&pms_work);
	}
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CORE )){
		pms_work.target_corevol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = 3;
		pm_m23_func->run_regul(&pms_work);
	}

	return 0;
}


int pm_m23_check_sidd_valid( UINT32 core_siddl,  UINT32 cpu_siddl, m23_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_siddl >= core_sidd_valid_max || core_siddl <= core_sidd_valid_min) {
		//__pm_m23_set_vol(I2C_AVS_CORE,CORE_AVS_S, 0, 0);
		 PM_ERROR("M23 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x] %d %d %d \n",cpu_volttype_m23[CPU_AVS_S],core_volttype_m23[CORE_AVS_S],lx_chip_rev(),core_siddl,core_sidd_valid_max,core_sidd_valid_min);
		return -1;
	}

	return 0;
}

int pm_m23_get_cpu_avs(pms_m23_avsinto_t * info)
{
	info->avstype = m23_cpu_avs;

	if(m23_avsinfo)
	{
		info->avscurrent = (m23_avsinfo >> 16 ) & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	return (int)m23_cpu_avs;
}
unsigned char * pm_m23_get_cpu_avs_str(void)
{
	return cpu_avstype[m23_cpu_avs];
}


int pm_m23_get_core_avs(pms_m23_avsinto_t * info)
{
	info->avstype = m23_core_avs;

	if(m23_avsinfo){
		info->avscurrent =  (m23_avsinfo) & 0xffff;

	}else{
		info->avscurrent = 0;
	}

	return (int)m23_core_avs;
}

unsigned char *  pm_m23_get_core_avs_str(void)
{
	return core_avstype[m23_core_avs];
}

int pm_m23_set_avs(void)/*avscputime*/
{
	int ret = -1;
	unsigned int core_siddl = 0, cpu_siddl = 0;
	/* do avs using m23_core_avs,m23_cpu_avs of bootargs */
	if((m23_cpu_avs > 0) && (m23_cpu_avs < M23_CPU_AVS_INVALID_MAX))
	{
		/* store avs info to suspend resume */
		/* store avs info from bootargs*/

		/*  correct AVS info case:  */
		core_siddl = m23_avsinfo & 0xffff;
		cpu_siddl  = (m23_avsinfo >> 16) & 0xffff;
		printk("M23 AVS info valid m23_avsinfo[%x] %d %d \n",m23_avsinfo,cpu_siddl,core_siddl);

		if (lx_chip_rev() >= LX_CHIP_REV(M23,A0) ){
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].core_sidd_f_min);

			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}
		else{
			__pm_m23_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0,0);

			printk("M23 CPUAVS Kdriver lx_chip_rev[%x]  AVS cpu skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
			,lx_chip_rev(),cpu_volttype_m23[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_m23[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}


		if (lx_chip_rev() >= LX_CHIP_REV(M23,A0)){
			ret = pm_m23_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_m23[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			return ret;
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			if(m23_slt_high) /*high volt*/
			{
			//	__pm_m23_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0,0);
				__pm_m23_set_vol(GPIO_AVS_CPU,m23_cpu_avs,0,1);
			}
			else /*low volt */
			{
				__pm_m23_set_vol(GPIO_AVS_CPU,m23_cpu_avs,0,1);
			}
		}
		else
		{
			__pm_m23_set_vol(GPIO_AVS_CPU,m23_cpu_avs,0,1);
		}

		printk("M23 CPUAVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d]\n",
			cpu_avstype[m23_cpu_avs],core_avstype[m23_core_avs],cpu_volttype_m23[m23_cpu_avs],cpu_vidttype[m23_cpu_avs],
			core_volttype_m23[m23_core_avs],core_vidttype[m23_core_avs],lx_chip_rev(),m23_slt_high);

		return 0;
	}
	/* skip avs */
	else
	{
		__pm_m23_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0,0);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("M23 CPUAVS avs info is not valid, skipped! m23_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,m23_avsinfo,cpu_volttype_m23[CPU_AVS_S],core_volttype_m23[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}

int pm_m23_set_coreavs(void)/*avscoretime*/
{
	int ret = -1;
	unsigned int core_siddl = 0U, cpu_siddl = 0U;


	if(m23_pms_tcorevol > 0 && m23_pms_tcorevol < VOUT_MAX )
	{

		pms_m23_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_m23_work_t));
		pms_work.target_corevol = (unsigned int)m23_pms_tcorevol;
		pms_work.do_avs = (UINT32)1;
		pms_work.ch = (UINT32)0;
		pm_m23_func->run_regul(&pms_work);
		printk("M23 AVS bootparam tcorev[%d]mV cpu_avs[%d]\n",pms_work.target_corevol,m23_cpu_avs );

		#if 0
		#ifdef M23_AVS_SLT
		mdelay(30);

		memset(&pms_work, 0x0, sizeof(pms_m23_work_t));
		pms_work.target_corevol = (unsigned int)m23_pms_tcorevol;
		pms_work.do_avs = 1;
		pms_work.ch = 4;
		pm_m23_func->run_regul(pms_work);
		#else
		if(m23_cpu_avs >0)
		{
			__pm_m23_set_vol(GPIO_AVS_CPU,m23_cpu_avs,0, 1);
		}
		#endif
		#endif
		return 0;
	}

	/* do avs using m23_core_avs,m23_cpu_avs of bootargs */
	else if((m23_core_avs > 0) && (m23_core_avs < ((UINT32)M23_CORE_AVS_INVALID_MAX)))
	{
		core_siddl = m23_avsinfo & ((UINT32)(0xffff));
		cpu_siddl  = (m23_avsinfo >> 16) & ((UINT32)0xffff);
		if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(M23,A0))){
			ret = pm_m23_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_m23[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			{
				__pm_m23_set_vol(GPIO_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)0);
				return ret;
			}
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			if(m23_slt_high) /*high volt*/
			{
				//__pm_m23_set_vol(GPIO_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)0);
				__pm_m23_set_vol(GPIO_AVS_CORE,m23_core_avs,(UINT32)0, (UINT32)1);
			}
			else /*low volt*/
			{
				__pm_m23_set_vol(GPIO_AVS_CORE,m23_core_avs,(UINT32)0, (UINT32)1);
			}
		}
		else
		{
			__pm_m23_set_vol(GPIO_AVS_CORE,m23_core_avs,(UINT32)0, (UINT32)1);
		}

		printk("M23 COREAVS  cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d] \n",
			cpu_avstype[m23_cpu_avs],core_avstype[m23_core_avs],cpu_volttype_m23[m23_cpu_avs],cpu_vidttype[m23_cpu_avs],
			core_volttype_m23[m23_core_avs],core_vidttype[m23_core_avs],lx_chip_rev(),m23_slt_high);

		return 0;
	}
	/* skip avs */
	else{
		#ifdef M23_AVS_SLT
		#else
		//__pm_m23_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0, 1);
		#endif
		__pm_m23_set_vol(GPIO_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)0);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("M23 COREAVS avs info is not valid, skipped! m23_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,m23_avsinfo,cpu_volttype_m23[CPU_AVS_S],core_volttype_m23[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}



int pm_m23_set_avs_force(UINT32 core_cpu, UINT32 type)
{
	UINT32 core_avs= 0, cpu_avs = 0;
	#ifdef M23_AVS_SLT
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		__pm_m23_set_vol(core_cpu,type, 0, 0);
	}
	#else
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		__pm_m23_set_vol(core_cpu,type, 0, 1);
	}
	#endif
	if (core_cpu == GPIO_AVS_CORE ){
		core_avs = type;
		__pm_m23_set_vol(core_cpu,type, 0, 1);
	}

	PM_NOTI("M23 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n"
	,cpu_avstype[cpu_avs],cpu_volttype_m23[cpu_avs],cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype_m23[core_avs],core_vidttype[core_avs]  );

	return 0;
}

int pm_m23_set_avs_in_resume(void)
{
	return 0;
}

int pm_m23_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int m23_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	switch (cmd)
	{
		default:
			ret = -1;
		break;
	}

    return ret;
}

int m23_check_ts(void)
{
	int cpu_temp = 0, cpu_rem = 0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s) {

		if(m23_cpu_ts_base != NULL) cpu_rawts = readl((void *)((uintptr_t)m23_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			m23_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)m23_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)m23_avs_info.cpu_ts_bparam );

			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem) ;

			if(cpu_rem > 50000)
				cpu_temp++;

			m23_avs_info.temperature = cpu_temp;

			if( m23_avs_info.ts_debug_enable )
			{
				PM_NOTI("------------------------------\n");
				PM_NOTI("M23 CPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
			}

			#ifdef M23_AVS_SLT
			#else
			#if 0
			if(cpu_temp > m23_avs_info.avshigh_th)
			{
				if(m23_avs_info.is_avshigh == 0)
				{
					m23_avs_info.avshigh_count++;

					if(m23_avs_info.avshigh_count > 5 )
					{
						m23_avs_info.is_avshigh = 1;
						m23_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("M23 SET AVS HIGH: CPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						//__pm_m23_set_vol(GPIO_AVS_CORE,m23_core_avs,0, 0);
						return 1 ;
					}
				}

			}
			#endif
			#endif
		}

		ts_timer_count = 0;
	}
	return 0 ;
}

static int m23_pm_set_cpu_ts_aparam(unsigned int value)
{
	m23_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int m23_pm_set_cpu_ts_bparam(unsigned int value)
{
	m23_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int m23_pm_get_cpu_ts_aparam(void)
{
	return m23_avs_info.cpu_ts_aparam;
}

static unsigned int m23_pm_get_cpu_ts_bparam(void)
{
	return m23_avs_info.cpu_ts_bparam;
}

static int m23_pm_set_gpu_ts_aparam(unsigned int value)
{
	m23_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int m23_pm_set_gpu_ts_bparam(unsigned int value)
{
	m23_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int m23_pm_get_gpu_ts_aparam(void)
{
	return m23_avs_info.gpu_ts_aparam;
}

static unsigned int m23_pm_get_gpu_ts_bparam(void)
{
	return m23_avs_info.gpu_ts_bparam;
}

static int m23_pm_set_ts_debug_enable(unsigned int value)
{
	m23_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int m23_pm_get_ts_debug_enable(void)
{
	return m23_avs_info.ts_debug_enable;
}

static int m23_pm_get_temperature(void)
{
	int cpu_temp = 0, cpu_rem=0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	if(m23_cpu_ts_base != NULL)
	{
		cpu_rawts = readl((void *)((uintptr_t)m23_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			m23_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)m23_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)m23_avs_info.cpu_ts_bparam );
			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem);
			if(cpu_rem > 50000 )
				cpu_temp++;

			m23_avs_info.temperature = cpu_temp;
		}
	}
	return m23_avs_info.temperature;
}

void m23_AvsReInit(void)
{
	unsigned int val;

	m23_avs_info.is_avshigh = 0U;
	if(m23_cpu_ts_base == NULL)
		m23_cpu_ts_base = ioremap( 0xcc924000, 0x18);

	if(m23_cpu_ts_base != NULL)
	{
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(m23_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));
		val = TS_MUX_ON | TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM ;
		writel(val, m23_cpu_ts_base );
		val = TS_MUX_ON | TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, m23_cpu_ts_base );
		mdelay(2);
		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, m23_cpu_ts_base );
		mdelay(2);
		PM_NOTI("M23 TSADC set [%d]\n",val);

	}
}

void m23_AvsInit(void)
{
	int ret;
	unsigned int core_siddl = 0, cpu_siddl = 0;
	unsigned int val = 0;

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{

		/* gpio 0 is used for slt low volt low high volt:high */
		m23_gpiod = gpiod_get(&m23_gpiodev, "0", GPIOD_ASIS);

		if (IS_ERR(m23_gpiod))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",0,m23_gpiod);
			return ;
		}
		val = gpiod_get_value(m23_gpiod);
		m23_slt_high = val;
		gpiod_put(m23_gpiod);
		PM_NOTI("m23_is_sltmode[%d]\n",m23_slt_high);
	}

	pm_m23_func = get_m23_pm_func();

	if(m23_cpu_ts_base == NULL)
		m23_cpu_ts_base = ioremap( 0xcc924000, 0x18);

	if(m23_cpu_ts_base != NULL)
	{
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(m23_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));
		val = TS_MUX_ON | TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM ;
		writel(val, m23_cpu_ts_base );
		val = TS_MUX_ON | TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, m23_cpu_ts_base );
		mdelay(2);
		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, m23_cpu_ts_base );
		mdelay(2);
		PM_NOTI("M23 TSADC set [%d]\n",val);
	}

	/* cpu_ts_aparam, cpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -276.05(cpu_ts_bparam)  + 0.01243(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */

	m23_avs_info.cpu_ts_aparam = 1243;
	m23_avs_info.cpu_ts_bparam = 27605000;

	/* avs table is changed when gpu temp reach 80'c */

	m23_avs_info.avshigh_th = 80;
	m23_avs_info.is_avshigh = 0;
	m23_avs_info.avshigh_count = 0;

	m23_avs_info.ts_debug_enable = 0;
	m23_avs_info.HVT_cpu = m23_cpuHS >> 16 & 0xffff;
	m23_avs_info.SVT_cpu = m23_cpuHS & 0xffff;
	m23_avs_info.Nskew_cpu = m23_cpuNP >> 16 & 0xffff;
	m23_avs_info.Pskew_cpu = m23_cpuNP & 0xffff;

	m23_avs_info.HVT_gpu = m23_gpuHS >> 16 & 0xffff;
	m23_avs_info.SVT_gpu = m23_gpuHS & 0xffff;
	m23_avs_info.Nskew_gpu = m23_gpuNP >> 16 & 0xffff;
	m23_avs_info.Pskew_gpu = m23_gpuNP & 0xffff;
	if((m23_core_avs > 0) && (m23_core_avs < M23_CORE_AVS_INVALID_MAX) &&
		(m23_cpu_avs > 0) && (m23_cpu_avs < M23_CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_siddl = m23_avsinfo & 0xffff;
		cpu_siddl  = (m23_avsinfo >> 16) & 0xffff;

		if (lx_chip_rev() >= LX_CHIP_REV(M23,A0) ){
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].core_sidd_f_min);

			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}
		else
		{
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].core_sidd_f_min);

			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_m23[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}

#if 0  	//* use regression param using normal,f sample*/
		if( core_siddl > core_sidd_ff_min_th){
			m23_avs_info.cpu_ts_aparam = 1341;
			m23_avs_info.cpu_ts_bparam = 30130000;
		}
		else if( core_siddl > core_sidd_f_min_th){
			m23_avs_info.cpu_ts_aparam = 1237;
			m23_avs_info.cpu_ts_bparam = 27973000;
		}
		else if( core_siddl > core_sidd_n_min_th){
			m23_avs_info.cpu_ts_aparam = 1237;
			m23_avs_info.cpu_ts_bparam = 27973000;
		}
		else if( core_siddl > core_sidd_s_min_th){
			m23_avs_info.cpu_ts_aparam = 1386;
			m23_avs_info.cpu_ts_bparam = 31210000;
		}
		else{
			m23_avs_info.cpu_ts_aparam = 1237;
			m23_avs_info.cpu_ts_bparam = 27973000;
		}
#endif

		if (lx_chip_rev() >= LX_CHIP_REV(M23,A0)){
			ret = pm_m23_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_m23[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ;
		}


	}
}

static pms_m23_avs_t m23_pm_avs =
{
	.init = m23_AvsInit,
	.reinit = m23_AvsReInit,
	.set_avs = pm_m23_set_avs,
	.set_coreavs = pm_m23_set_coreavs,
	.get_cpu_avs_type = pm_m23_get_cpu_avs,
	.get_cpu_avs_type_str = pm_m23_get_cpu_avs_str,
	.get_core_avs_type = pm_m23_get_core_avs,
	.get_core_avs_type_str = pm_m23_get_core_avs_str,
	.set_avs_in_resume = pm_m23_set_avs_in_resume,
	.set_avs_force = pm_m23_set_avs_force,
	.check_n_set = pm_m23_check_n_set,
	.ioctl = m23_pm_ioctl_avs,
	.check_ts = m23_check_ts,
	.get_cpu_ts_aparam = m23_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = m23_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = m23_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = m23_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = m23_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = m23_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = m23_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = m23_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = m23_pm_get_ts_debug_enable,
	.set_ts_debug_enable = m23_pm_set_ts_debug_enable,
	.get_temperature = m23_pm_get_temperature,

};

pms_m23_avs_t* get_m23_pm_avs(void)
{
	return &m23_pm_avs;
}


