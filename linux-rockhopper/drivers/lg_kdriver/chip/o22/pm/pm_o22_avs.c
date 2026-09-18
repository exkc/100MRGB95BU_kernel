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
 *  author		jun.kong (jun.kong@lge.com)
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
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include "os_util.h"

#include "gpio_core.h"

#include "pm_o22common.h"

#include "sys_regs.h"
#include "gpio_reg.h"

#include "sys_io.h"
#include <linux/regulator/consumer.h>

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


#define O22_GPIO_AVS_CPU0         26
#define O22_GPIO_AVS_CPU1         27

#define O22_GPIO_AVS_CPU0_B0         26
#define O22_GPIO_AVS_CPU1_B0         27


#define SIDD_CHECK_TABLE_AX     0  /* A0 A1 A2 */
#define SIDD_CHECK_TABLE_A3     1
#define SIDD_CHECK_TABLE_NUM    5

#define O22_CORE_SIDD_FF_MIN_TH_AX  230     //mA
#define O22_CORE_SIDD_F_MIN_TH_AX   160     //mA
#define O22_CORE_SIDD_N_MIN_TH_AX   80      //mA
#define O22_CORE_SIDD_S_MIN_TH_AX   1      //mA

#define O22_CORE_SIDD_FF_MIN_TH_A3  230     //mA
#define O22_CORE_SIDD_F_MIN_TH_A3   160     //mA
#define O22_CORE_SIDD_N_MIN_TH_A3   80      //mA
#define O22_CORE_SIDD_S_MIN_TH_A3   1      //mA

/* caution: core sidd is used for cpu avs range */
#ifdef O22_CPUCTRL_I2C_SLT
#define O22_CPU_SIDD_FF_MIN_TH_AX   60     //mA
#define O22_CPU_SIDD_F_MIN_TH_AX    35     //mA
#define O22_CPU_SIDD_N_MIN_TH_AX    20      //mA
#define O22_CPU_SIDD_S_MIN_TH_AX    1      //mA

#else
#define O22_CPU_SIDD_FF_MIN_TH_AX   60     //mA
#define O22_CPU_SIDD_F_MIN_TH_AX    35     //mA
#define O22_CPU_SIDD_N_MIN_TH_AX    20      //mA
#define O22_CPU_SIDD_S_MIN_TH_AX    1      //mA

#define O22_CPU_SIDD_FF_MIN_TH_A3   140     //mA
#define O22_CPU_SIDD_F_MIN_TH_A3    100     //mA
#define O22_CPU_SIDD_N_MIN_TH_A3    60      //mA
#define O22_CPU_SIDD_S_MIN_TH_A3    1      //mA
#endif

#define O22_CORE_SIDD_VALID_MIN     1 //mA
#define O22_CORE_SIDD_VALID_MAX     1000 //mA


//#define O22_REGUL_GET_MAX		30

struct delayed_work o22_avs_cpu_dw;
struct workqueue_struct *o22_avscputime_wq;
struct workqueue_struct *o22_avscoretime_wq;
struct workqueue_struct *o22_avscpu_wq;

int o22_cpuwork_stage = 0;
int o22_cpuwork_target = 0;

/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_o22[6] = { "XXX","0.94","0.92","0.90", "0.86","0.86", };
static char * cpu_vidttype[6] = { "GPIO26[1] 27[1]","GPIO 26[1] 27[1]","GPIO 26[1] 27[0]","GPIO 26[0] 27[1]","GPIO 26[0] 27[0]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_o22[6] = { "XXX","870","850","810", "780","780", };
char * core_volttype_high_o22[6] = { "XXX","870","830","790", "760","760", };
static char * core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

static unsigned int o22_avsinfo = 0;
static unsigned int o22_cpu_avs = 0;
static unsigned int o22_core_avs = 0;
static unsigned int o22_cpuHS = 0;
static unsigned int o22_cpuNP = 0;
static unsigned int o22_gpuHS = 0;
static unsigned int o22_gpuNP = 0;
extern int o22_pms_tcorevol;
extern int o22_is_prepared;

//static UINT32 core_avs= 0, cpu_avs = 0;

module_param(o22_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(o22_avsinfo, "o22_avsinfo");

module_param(o22_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o22_cpu_avs, "o22_cpu_avs");

module_param(o22_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o22_core_avs, "o22_core_avs");

module_param(o22_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o22_cpuHS, "o22_cpuHS");

module_param(o22_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o22_cpuNP, "o22_cpuNP");

module_param(o22_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o22_gpuHS, "o22_gpuHS");

module_param(o22_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o22_gpuNP, "o22_gpuNP");

                                                /* ffast */
static unsigned int cpu_sidd_ff_min_th;
                                                /* fast */
static unsigned int cpu_sidd_f_min_th;
                                                /* normal */
static unsigned int cpu_sidd_n_min_th;
                                                /* slow */
static unsigned int cpu_sidd_s_min_th;


                                                /* ffast ~ 230 */
static unsigned int core_sidd_ff_min_th;
                                                /* fast 160 ~ 229*/
static unsigned int core_sidd_f_min_th;
                                                /* normal 80 ~ 159*/
static unsigned int core_sidd_n_min_th;
                                                /* slow   ~ 79 */
static unsigned int core_sidd_s_min_th;		/* not used */

pms_o22_avsinto_t	o22_avs_info;

o22_sidd_t gSidd_check_table_o22[SIDD_CHECK_TABLE_NUM]={

        [SIDD_CHECK_TABLE_AX]={
        .cpu_sidd_ff_min = O22_CPU_SIDD_FF_MIN_TH_AX,
        .cpu_sidd_f_min = O22_CPU_SIDD_F_MIN_TH_AX,
        .cpu_sidd_n_min = O22_CPU_SIDD_N_MIN_TH_AX,
        .cpu_sidd_s_min = O22_CPU_SIDD_S_MIN_TH_AX,

        .core_sidd_ff_min = O22_CORE_SIDD_FF_MIN_TH_AX,
        .core_sidd_f_min = O22_CORE_SIDD_F_MIN_TH_AX,
        .core_sidd_n_min = O22_CORE_SIDD_N_MIN_TH_AX,
        .core_sidd_s_min = O22_CORE_SIDD_S_MIN_TH_AX, /* not used */

        .core_sidd_valid_max = O22_CORE_SIDD_VALID_MAX,
        .core_sidd_valid_min = O22_CORE_SIDD_VALID_MIN
        },

#ifndef O22_CPUCTRL_I2C_SLT
        [SIDD_CHECK_TABLE_A3]={
        .cpu_sidd_ff_min = O22_CPU_SIDD_FF_MIN_TH_A3,
        .cpu_sidd_f_min = O22_CPU_SIDD_F_MIN_TH_A3,
        .cpu_sidd_n_min = O22_CPU_SIDD_N_MIN_TH_A3,
        .cpu_sidd_s_min = O22_CPU_SIDD_S_MIN_TH_A3,

        .core_sidd_ff_min = O22_CORE_SIDD_FF_MIN_TH_A3,
        .core_sidd_f_min = O22_CORE_SIDD_F_MIN_TH_A3,
        .core_sidd_n_min = O22_CORE_SIDD_N_MIN_TH_A3,
        .core_sidd_s_min = O22_CORE_SIDD_S_MIN_TH_A3, /* not used */

        .core_sidd_valid_max = O22_CORE_SIDD_VALID_MAX,
        .core_sidd_valid_min = O22_CORE_SIDD_VALID_MIN
        },
#endif

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
static pms_o22_func_t* pm_o22_func = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/

//BEGIN GPIO_KERNEL_API


struct device o22_gpiodev =
{
	.init_name = "gpio_kerneltable",
};

#ifdef O22_CPUCTRL_I2C_SLT
struct gpio_desc *o22_gpiod = NULL;
#endif
struct gpio_desc *o22_y23_gpiod = NULL;
static int o22_y23 = 0;

#define CORE_AVS_S_MV_HIGH_TEMP		870
#define CORE_AVS_N_MV_HIGH_TEMP		830
#define CORE_AVS_F_MV_HIGH_TEMP		790
#define CORE_AVS_FF_MV_HIGH_TEMP	760

#define CPU_TS_EN			(1 << 0)
#define GPU_TS_EN			(1 << 0)

#define CPU_TS_RAW_INTR_EN			(1 << 24)
#define GPU_TS_RAW_INTR_EN			(1 << 24)



static unsigned int ts_timer_count = 0;
static unsigned int	ts_timer_count_1s = HZ / ((HZ / 100) * (20 / 10));
//int o22_is_get = 0;

void __iomem *o22_cpu_ts_base = NULL;

#if 0
static struct gpiod_lookup_table pm_gpio_table = {

        .dev_id = "pm_gpio",

        .table = {
					GPIO_LOOKUP_IDX("fd430000.gpio", 2, "26", 0, GPIO_ACTIVE_HIGH),
					GPIO_LOOKUP_IDX("fd430000.gpio", 3, "27", 0, GPIO_ACTIVE_HIGH),

		 { },

		},


};
#endif

static void o22_avs_cpuwork_req(void)
{
	queue_delayed_work(o22_avscpu_wq,&o22_avs_cpu_dw,msecs_to_jiffies(O22_AVS_STEP_DELAY));
}

void o22_avs_cpuwork_func(struct work_struct *work)
{
	#ifdef O22_CPUCTRL_I2C_SLT
	pms_o22_work_t pms_work ;
	#else
	struct regulator *regulator;
	#endif
	int ret = 0;

	if(o22_is_prepared){
		PM_NOTI("SET CPU SKIP\n" );
		return;
	}
	#ifdef O22_CPUCTRL_I2C_SLT
	#else
	regulator = regulator_get(NULL, "cpu0");
	if (IS_ERR(regulator)) {
		PM_ERROR("couldn't get cpu0 regulator regulator\n");
		return ;
	}
	#endif

	if(o22_cpuwork_target >= CPU_AVS_S &&  o22_cpuwork_target <=CPU_AVS_FF){
		if(o22_cpuwork_stage == 3){
	#ifdef O22_CPUCTRL_I2C_SLT
			pms_work.ch = (UINT32)4;
			pms_work.target_corevol = (UINT32)O22_CPU_AVS_FF_UV;
			pms_work.do_avs = (UINT32)1;
			pm_o22_func->run_regul(pms_work);
	#else
			ret = regulator_set_voltage(regulator, O22_CPU_AVS_FF_UV,O22_CPU_AVS_FF_UV);
			regulator_put(regulator);
	#endif
			PM_NOTI("SET CPU FF\n" );
			o22_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(o22_cpuwork_stage == 2){
	#ifdef O22_CPUCTRL_I2C_SLT
			pms_work.ch = 4;
			pms_work.target_corevol = O22_CPU_AVS_F_UV;
			pms_work.do_avs = 1;
			pm_o22_func->run_regul(pms_work);
	#else
			ret = regulator_set_voltage(regulator, O22_CPU_AVS_F_UV,O22_CPU_AVS_F_UV);
			regulator_put(regulator);
	#endif
			PM_NOTI("SET CPU F\n" );
			o22_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(o22_cpuwork_stage == 1){
	#ifdef O22_CPUCTRL_I2C_SLT
			pms_work.ch = (UINT32)4;
			pms_work.target_corevol = (UINT32)O22_CPU_AVS_N_UV;
			pms_work.do_avs = (UINT32)1;
			pm_o22_func->run_regul(pms_work);
	#else
			ret = regulator_set_voltage(regulator, O22_CPU_AVS_N_UV,O22_CPU_AVS_N_UV);
			regulator_put(regulator);
	#endif
			PM_NOTI("SET CPU N\n" );
			o22_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(o22_cpuwork_stage == 0){
	#ifdef O22_CPUCTRL_I2C_SLT
			pms_work.ch = (UINT32)4;
			pms_work.target_corevol = (UINT32)O22_CPU_AVS_S_UV;
			pms_work.do_avs = (UINT32)1;
			pm_o22_func->run_regul(pms_work);
	#else

			ret = regulator_set_voltage(regulator, O22_CPU_AVS_S_UV,O22_CPU_AVS_S_UV);
			regulator_put(regulator);
	#endif
			PM_NOTI("SET CPU S\n" );
			o22_cpuwork_stage++;
			goto cpuavs_subwork;
		}

	}
	else{
	#ifdef O22_CPUCTRL_I2C_SLT
		pms_work.ch = (UINT32)4;
		pms_work.target_corevol = (UINT32)O22_CPU_AVS_S_UV;
		pms_work.do_avs = (UINT32)1;
		pm_o22_func->run_regul(pms_work);
	#else
		ret = regulator_set_voltage(regulator, O22_CPU_AVS_S_UV,O22_CPU_AVS_S_UV);
		regulator_put(regulator);
	#endif
		o22_cpuwork_stage = 0;
		o22_cpuwork_target = 0;
		goto end_cpuavs_subowrk;
	}

cpuavs_subwork:
	if(o22_cpuwork_target != o22_cpuwork_stage){
		o22_avs_cpuwork_req();
	}
end_cpuavs_subowrk:
	if(o22_cpuwork_target == o22_cpuwork_stage)
	{
		PM_NOTI("CPUAVS[%d] [%d][%d]\n",ret,o22_cpuwork_target,o22_cpuwork_stage );
		o22_cpuwork_stage = 0;
		o22_cpuwork_target = 0;
	}
	if(o22_is_prepared)
		PM_NOTI("SET CPU SKIP\n" );
	return ;
}

struct regulator *o22_regulator = NULL;

#if 0
static int _PM_GPIO_DevSetMode(UINT32 port, UINT32 mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);

	mask = 1 << (port % 8);
	direction = (mode == LX_GPIO_MODE_INPUT) ?
				direction & (~mask) : direction | mask;
	GPIONDIR(port/8) = direction;
	return 0;
}
#endif

//END GPIO_KERNEL_API

/* cpuavs(regulator) is_step 0 run only in task*/
int __pm_o22_set_vol(UINT32 core_cpu, UINT32 type, UINT32 ch, UINT32 is_step)
{
	pms_o22_work_t pms_work ;
#ifndef O22_CPUCTRL_I2C_SLT
	struct regulator *regulator;
	int ret;
#else
	int val = 0;
	if( o22_gpiod != NULL)
		val = gpiod_get_value(o22_gpiod);
#endif

	memset(&pms_work, 0x0, sizeof(pms_o22_work_t));
	pm_o22_func = get_o22_pm_func();

	if ((is_step == 1) && (core_cpu == GPIO_AVS_CPU )){	/* set avs step  */
		if (core_cpu == GPIO_AVS_CPU ){
			o22_cpuwork_target = type;
			o22_cpuwork_stage = 0;
			queue_delayed_work(o22_avscpu_wq,&o22_avs_cpu_dw, msecs_to_jiffies(1));
		}
	}
#ifdef O22_CPUCTRL_I2C_SLT
	if ((is_step == 1) && (core_cpu == I2C_AVS_CPU)){	/* set avs step  */
			o22_cpuwork_target = type;
			o22_cpuwork_stage = 0;
			queue_delayed_work(o22_avscpu_wq,&o22_avs_cpu_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 0) && (core_cpu == I2C_AVS_CPU)){
		if(type == CPU_AVS_FF){
			pms_work.target_corevol = (UINT32)O22_CPU_AVS_FFHIGH_UV;
			pms_work.ch = (UINT32)ch;
			pms_work.do_avs = (UINT32)1;
			pm_o22_func->run_regul(pms_work);
			PM_NOTI("SET CPU hff\n" );
		}
	}
	else if (core_cpu == I2C_AVS_CORE && val == 1){
		if(type == CORE_AVS_FF){
			pms_work.target_corevol = (UINT32)CORE_AVS_FFHIGH_MV;
			pms_work.ch = (UINT32)ch;
			pms_work.do_avs = (UINT32)1;
			pm_o22_func->run_regul(pms_work);
			PM_NOTI("SET CORE hff\n" );
		}
	}
#else
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CPU )){
	/* set avs direct : task only, not isr  */

		regulator = regulator_get(NULL, "cpu0");
		if (IS_ERR(regulator)) {
			PM_ERROR("couldn't get cpu0 regulator regulator\n");
			return 0;
		}


		switch(type){
			case CPU_AVS_S:
				//HV
				ret = regulator_set_voltage(regulator, O22_CPU_AVS_S_UV,O22_CPU_AVS_S_UV);
				regulator_put(regulator);
				PM_NOTI("SET CPU s\n" );
				break;
			case CPU_AVS_N:
				//MV
				ret = regulator_set_voltage(regulator, O22_CPU_AVS_N_UV,O22_CPU_AVS_N_UV);
				regulator_put(regulator);
				PM_NOTI("SET CPU n\n" );
				break;
			case CPU_AVS_F:
				//LV
				ret = regulator_set_voltage(regulator, O22_CPU_AVS_F_UV,O22_CPU_AVS_F_UV);
				regulator_put(regulator);
				PM_NOTI("SET CPU f\n" );
				break;
			case CPU_AVS_FF:
				//VLV
				ret = regulator_set_voltage(regulator, O22_CPU_AVS_FF_UV,O22_CPU_AVS_FF_UV);
				regulator_put(regulator);
				PM_NOTI("SET CPU ff\n" );
				break;
			default:
				//HV
				ret = regulator_set_voltage(regulator, O22_CPU_AVS_S_UV,O22_CPU_AVS_S_UV);
				regulator_put(regulator);
				break;
		}
		PM_NOTI("cpu ret[%d]\n",ret);

	}
#endif
	else if (core_cpu == I2C_AVS_CORE && o22_avs_info.is_avshigh == 0 ){

		switch(type){
			case CORE_AVS_S:
				//HV
				pms_work.target_corevol = CORE_AVS_S_MV;
				break;
			case CORE_AVS_N:
				pms_work.target_corevol = CORE_AVS_N_MV;

				break;
			case CORE_AVS_F:
				pms_work.target_corevol = CORE_AVS_F_MV;

				break;
			case CORE_AVS_FF:
				pms_work.target_corevol = CORE_AVS_FF_MV;

				break;
			default:
				//HV
				pms_work.target_corevol = CORE_AVS_S_MV;
				break;
		}
		pms_work.ch = ch;
		pms_work.do_avs = 1;
		pm_o22_func->run_regul(pms_work);
	}
	else if (core_cpu == I2C_AVS_CORE && o22_avs_info.is_avshigh == 1 ){
		pms_work.do_avs = 1;
		switch(type){
			case CORE_AVS_S:
				//HV
				pms_work.target_corevol = CORE_AVS_S_MV_HIGH_TEMP;
				break;
			case CORE_AVS_N:
				pms_work.target_corevol = CORE_AVS_N_MV_HIGH_TEMP;

				break;
			case CORE_AVS_F:
				pms_work.target_corevol = CORE_AVS_F_MV_HIGH_TEMP;

				break;
			case CORE_AVS_FF:
				pms_work.target_corevol = CORE_AVS_FF_MV_HIGH_TEMP;

				break;
			default:
				//HV
				pms_work.target_corevol = CORE_AVS_S_MV_HIGH_TEMP;
				break;
		}
		pms_work.ch = ch;
		pms_work.do_avs = 1;
		pm_o22_func->run_regul(pms_work);
	}

	return 0;
}


int pm_o22_check_sidd_valid( UINT32 core_siddl,  UINT32 cpu_siddl, o22_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_siddl >= core_sidd_valid_max || core_siddl <= core_sidd_valid_min) {
		//__pm_o22_set_vol(I2C_AVS_CORE,CORE_AVS_S, 0, 0);
		 PM_ERROR("O22 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x] %d %d %d \n",cpu_volttype_o22[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],lx_chip_rev(),core_siddl,core_sidd_valid_max,core_sidd_valid_min);
		return -1;
	}

	return 0;
}

int pm_o22_get_cpu_avs(pms_o22_avsinto_t * info)
{
	info->avstype = o22_cpu_avs;

	if(o22_avsinfo)
	{
		info->avscurrent = (o22_avsinfo >> 16 ) & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	info->HVT_cpu = o22_cpuHS >> 16 & 0xffff;
	info->SVT_cpu = o22_cpuHS & 0xffff;
	info->Nskew_cpu = o22_cpuNP >> 16 & 0xffff;
	info->Pskew_cpu = o22_cpuNP & 0xffff;
	info->HVT_gpu = o22_gpuHS >> 16 & 0xffff;
	info->SVT_gpu = o22_gpuHS & 0xffff;
	info->Nskew_gpu = o22_gpuNP >> 16 & 0xffff;
	info->Pskew_gpu = o22_gpuNP & 0xffff;

	return (int)o22_cpu_avs;
}
unsigned char * pm_o22_get_cpu_avs_str(void)
{
	return cpu_avstype[o22_cpu_avs];
}


int pm_o22_get_core_avs(pms_o22_avsinto_t * info)
{
	info->avstype = o22_core_avs;

	if(o22_avsinfo)
	{
		info->avscurrent =  (o22_avsinfo) & 0xffff;

	}else
	{
		info->avscurrent = 0;
	}

	return (int)o22_core_avs;
}

unsigned char *  pm_o22_get_core_avs_str(void)
{
		return core_avstype[o22_core_avs];
}

int pm_o22_set_avs(void)/*avscputime*/
{
	int ret = -1;
	UINT32 core_siddl = 0, cpu_siddl = 0;

	#ifdef O22_CPUCTRL_I2C_SLT
	int val = 0;
	if(o22_gpiod != NULL)
		val = gpiod_get_value(o22_gpiod);
	#endif

	/* do avs using o22_core_avs,o22_cpu_avs of bootargs */
	if((o22_cpu_avs > 0) && (o22_cpu_avs < O22_CPU_AVS_INVALID_MAX))
	{
		/* store avs info to suspend resume */
		/* store avs info from bootargs*/

		/*  correct AVS info case:  */
		core_siddl = o22_avsinfo & 0xffff;
		cpu_siddl  = (o22_avsinfo >> 16) & 0xffff;
		printk("O22 AVS info valid o22_avsinfo[%x] %d %d \n",o22_avsinfo,cpu_siddl,core_siddl);

		#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A3) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_s_min);
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O22,A0) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
			}
			else{
				__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0, 1);

				printk("O22 CPUAVS Kdriver lx_chip_rev[%x]  AVS cpu skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_o22[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				return -1;
			}
		}
		else
		#endif
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A0) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
			}
			else{
				#ifdef O22_CPUCTRL_I2C_SLT
				if(val)
					__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,0);
				else
					__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,1);
				#else
				__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0, 1);
				#endif

				printk("O22 CPUAVS Kdriver lx_chip_rev[%x]  AVS cpu skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_o22[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				return -1;
			}
		}

		#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A3)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_A3]);
				if(ret != 0)
					return ret;
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ret;
			}
		}
		else
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ret;
			}

		}
		__pm_o22_set_vol(GPIO_AVS_CPU,o22_cpu_avs,0, 1);

		#else

		if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
			ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ret;
		}

		if(val)
			__pm_o22_set_vol(I2C_AVS_CPU,o22_cpu_avs,4,0);
		else
			__pm_o22_set_vol(I2C_AVS_CPU,o22_cpu_avs,4,1);

		#endif

		printk("O22 CPUAVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_avstype[o22_cpu_avs],core_avstype[o22_core_avs],cpu_volttype_o22[o22_cpu_avs],cpu_vidttype[o22_cpu_avs],
			core_volttype_o22[o22_core_avs],core_vidttype[o22_core_avs],lx_chip_rev());

		return 0;
	}
	/* do avs using kdriver avs param */
	else if(o22_avsinfo)
	{
		/*  correct AVS infocase:  */
		core_siddl = o22_avsinfo & 0xffff;
		cpu_siddl  = (o22_avsinfo >> 16) & 0xffff;
		printk("O22 CPUAVS avs info valid o22_avsinfo[%x] %d %d\n",o22_avsinfo,cpu_siddl,core_siddl);

		#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A3) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_A3].cpu_sidd_s_min);
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O22,A0) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
			}
			else{
				__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0,1);

				printk("O22 CPUAVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_o22[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				return -1;
			}
		}
		else
		#endif
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A0) ){
				core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
				core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
				core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
				core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

				cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
				cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
				cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
				cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
			}
			else{
				#ifdef O22_CPUCTRL_I2C_SLT
				if(val)
					__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,0);
				else
					__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,1);
				#else
				__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0,1);
				#endif

				printk("O22 CPUAVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_o22[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
				return -1;
			}
		}

		/* core voltage table is different from cpu voltage table */
		if( core_siddl >= core_sidd_ff_min_th){
			o22_core_avs =      CORE_AVS_FF;
		}
		else if( core_siddl >= core_sidd_f_min_th){
			o22_core_avs =      CORE_AVS_F;
		}
		else if( core_siddl >= core_sidd_n_min_th){
			o22_core_avs =      CORE_AVS_N;
		}
		else{
			o22_core_avs =      CORE_AVS_S;
		}
		/* caution: cpu avs is determined depending on core sidd */
		if( cpu_siddl >= cpu_sidd_ff_min_th){
			o22_cpu_avs =  CPU_AVS_FF;
		}
		else if( cpu_siddl >= cpu_sidd_f_min_th){
			o22_cpu_avs =  CPU_AVS_F;
		}
		else if( cpu_siddl >= cpu_sidd_n_min_th){
			o22_cpu_avs =  CPU_AVS_N;
		}
		else if( cpu_siddl >= cpu_sidd_s_min_th){
			o22_cpu_avs =  CPU_AVS_S;
		}
		else{
			o22_cpu_avs =  CPU_AVS_S;
		}


		#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A3)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_A3]);
				if(ret != 0)
					return ret;
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ret;
			}
		}
		else{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ret;
			}

		}
		__pm_o22_set_vol(GPIO_AVS_CPU,o22_cpu_avs, 0, 1);
		#else
		if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
			ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ret;
		}

		if(val)
			__pm_o22_set_vol(I2C_AVS_CPU,o22_cpu_avs,4,0);
		else
			__pm_o22_set_vol(I2C_AVS_CPU,o22_cpu_avs,4,1);
		#endif

		if(o22_avs_info.is_avshigh)
		{
			printk("O22 CPUAVS cpu_siddl[%d:%d|%d][%dmA:%s] core_siddl[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_siddl,
			cpu_avstype[o22_cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_siddl,core_avstype[o22_core_avs],cpu_volttype_o22[o22_cpu_avs],cpu_vidttype[o22_cpu_avs],
			core_volttype_high_o22[o22_core_avs],core_vidttype[o22_core_avs],lx_chip_rev());
		}
		else
		{
			printk("O22 CPUAVS cpu_siddl[%d:%d|%d][%dmA:%s] core_siddl[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_siddl,
			cpu_avstype[o22_cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_siddl,core_avstype[o22_core_avs],cpu_volttype_o22[o22_cpu_avs],cpu_vidttype[o22_cpu_avs],
			core_volttype_o22[o22_core_avs],core_vidttype[o22_core_avs],lx_chip_rev());
		}

		return 0;

	}
	/* skip avs */
	else{
		#ifdef O22_CPUCTRL_I2C_SLT
		if(val)
			__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,0);
		else
			__pm_o22_set_vol(I2C_AVS_CPU,CPU_AVS_S,4,1);
		#else
		__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0, 1);
		#endif
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O22 CPUAVS avs info is not valid, skipped! o22_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,o22_avsinfo,cpu_volttype_o22[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}

int pm_o22_set_coreavs(void)/*avscoretime*/
{
	int ret = -1;
	UINT32 core_siddl = 0U, cpu_siddl = 0U;


	if(o22_pms_tcorevol > 0 && o22_pms_tcorevol < VOUT_MAX )
	{

		pms_o22_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_o22_work_t));
		pms_work.target_corevol = (unsigned int)o22_pms_tcorevol;
		pms_work.do_avs = (UINT32)1;
		pms_work.ch = (UINT32)0;
		pm_o22_func->run_regul(pms_work);
		printk("O22 AVS bootparam tcorev[%d]mV cpu_avs[%d]\n",pms_work.target_corevol,o22_cpu_avs );

		#if 0
		#ifdef O22_CPUCTRL_I2C_SLT
		mdelay(30);

		memset(&pms_work, 0x0, sizeof(pms_o22_work_t));
		pms_work.target_corevol = (unsigned int)o22_pms_tcorevol;
		pms_work.do_avs = 1;
		pms_work.ch = 4;
		pm_o22_func->run_regul(pms_work);
		#else
		if(o22_cpu_avs >0)
		{
			__pm_o22_set_vol(GPIO_AVS_CPU,o22_cpu_avs,0, 1);
		}
		#endif
		#endif
		return 0;
	}

	/* do avs using o22_core_avs,o22_cpu_avs of bootargs */
	else if((o22_core_avs > 0) && (o22_core_avs < ((UINT32)O22_CORE_AVS_INVALID_MAX)))
	{
		core_siddl = o22_avsinfo & ((UINT32)(0xffff));
		cpu_siddl  = (o22_avsinfo >> 16) & ((UINT32)0xffff);

		#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(O22,A3))){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_A3]);
				if(ret != 0)
				return ret;
			}
			else if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(O22,A0))){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
				return ret;
			}
		}
		else
		#endif
		{
			if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(O22,A0))){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
				return ret;
			}
		}

		__pm_o22_set_vol(I2C_AVS_CORE,o22_core_avs,(UINT32)0, (UINT32)0);
		printk("O22 COREAVS  cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_avstype[o22_cpu_avs],core_avstype[o22_core_avs],cpu_volttype_o22[o22_cpu_avs],cpu_vidttype[o22_cpu_avs],
			core_volttype_o22[o22_core_avs],core_vidttype[o22_core_avs],lx_chip_rev());

		return 0;
	}
	/* skip avs */
	else{
		#ifdef O22_CPUCTRL_I2C_SLT
		#else
		//__pm_o22_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0, 1);
		#endif
		__pm_o22_set_vol(I2C_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)0);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O22 COREAVS avs info is not valid, skipped! o22_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
			,o22_avsinfo,cpu_volttype_o22[CPU_AVS_S],core_volttype_o22[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}



int pm_o22_set_avs_force(UINT32 core_cpu, UINT32 type)
{
	UINT32 core_avs= 0, cpu_avs = 0;
	#ifdef O22_CPUCTRL_I2C_SLT
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		__pm_o22_set_vol(core_cpu,type, 0, 0);
	}
	#else
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		__pm_o22_set_vol(core_cpu,type, 0, 1);
	}
	#endif
	if (core_cpu == I2C_AVS_CORE ){
		core_avs = type;
		__pm_o22_set_vol(core_cpu,type, 0, 0);
	}

	PM_NOTI("O22 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n"
	,cpu_avstype[cpu_avs],cpu_volttype_o22[cpu_avs],cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype_o22[core_avs],core_vidttype[core_avs]  );

	return 0;
}

int pm_o22_set_avs_in_resume(void)
{
	return 0;
}

int pm_o22_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o22_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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

int o22_check_ts(void)
{
	int cpu_temp = 0, cpu_rem = 0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s) {

		if(o22_cpu_ts_base != NULL) cpu_rawts = readl((void *)((uintptr_t)o22_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			o22_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)o22_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)o22_avs_info.cpu_ts_bparam );

			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem) ;

			if(cpu_rem > 50000)
				cpu_temp++;

			o22_avs_info.temperature = cpu_temp;

			if( o22_avs_info.ts_debug_enable )
			{
				PM_NOTI("------------------------------\n");
				PM_NOTI("O22 CPU TTEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
			}

			#ifdef O22_CPUCTRL_I2C_SLT
			#else
			if(cpu_temp > o22_avs_info.avshigh_th)
			{
				if(o22_avs_info.is_avshigh == 0)
				{
					o22_avs_info.avshigh_count++;

					if(o22_avs_info.avshigh_count > 5 )
					{
						o22_avs_info.is_avshigh = 1;
						o22_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("O22 SET AVS HIGH: GPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						__pm_o22_set_vol(I2C_AVS_CORE,o22_core_avs,0, 0);
						return 1 ;
					}
				}

			}
			#endif
		}

		ts_timer_count = 0;
	}
	return 0 ;
}

static int o22_pm_set_cpu_ts_aparam(unsigned int value)
{
	o22_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int o22_pm_set_cpu_ts_bparam(unsigned int value)
{
	o22_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int o22_pm_get_cpu_ts_aparam(void)
{
	return o22_avs_info.cpu_ts_aparam;
}

static unsigned int o22_pm_get_cpu_ts_bparam(void)
{
	return o22_avs_info.cpu_ts_bparam;
}

static int o22_pm_set_gpu_ts_aparam(unsigned int value)
{
	o22_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int o22_pm_set_gpu_ts_bparam(unsigned int value)
{
	o22_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int o22_pm_get_gpu_ts_aparam(void)
{
	return o22_avs_info.gpu_ts_aparam;
}

static unsigned int o22_pm_get_gpu_ts_bparam(void)
{
	return o22_avs_info.gpu_ts_bparam;
}

static int o22_pm_set_ts_debug_enable(unsigned int value)
{
	o22_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int o22_pm_get_ts_debug_enable(void)
{
	return o22_avs_info.ts_debug_enable;
}

static int o22_pm_get_temperature(void)
{
	int cpu_temp = 0, cpu_rem=0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	if(o22_cpu_ts_base != NULL)
	{
		cpu_rawts = readl((void *)((uintptr_t)o22_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			o22_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)o22_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)o22_avs_info.cpu_ts_bparam );
			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem);
			if(cpu_rem > 50000 )
				cpu_temp++;

			o22_avs_info.temperature = cpu_temp;
		}
	}
	return o22_avs_info.temperature;
}

void o22_AvsReInit(void)
{
	unsigned int val;

	o22_avs_info.is_avshigh = 0U;
	if(o22_cpu_ts_base == NULL)		o22_cpu_ts_base = ioremap( 0xc6032000, 0x18);
	//reg = readl(o22_cpu_ts_base);
	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, o22_cpu_ts_base);
}

void o22_AvsInit(void)
{
	unsigned int val;
	int ret;
	UINT32 core_siddl = 0, cpu_siddl = 0;
	char hw_opt[32];

#ifdef O22_CPUCTRL_I2C_SLT
	UINT8 portstr[10];
	sprintf(portstr, "%d", 8);

	o22_gpiod = gpiod_get(&o22_gpiodev, portstr, GPIOD_ASIS);

	if (IS_ERR(o22_gpiod))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",8,o22_gpiod);
		return ;
	}
#endif
	//int tcnt = 0;

	/* http://clm.lge.com/issue/browse/SCDCRID-3876 */
	/* gpio69 is used for spi in id nmled, so skip to use gpio69 */
	if(RET_OK==OS_ScanKernelCmdline("id_disptype=%s", hw_opt))
	{
		PM_NOTI("o22 id_disptype=%s skip to use gpio\n",hw_opt);
		o22_y23 = 1;
	}
	/* HE*/
	else
	{
		/* gpio 69 1:y23 0:y22 */
		o22_y23_gpiod = gpiod_get(&o22_gpiodev, "69", GPIOD_ASIS);

		if (IS_ERR(o22_y23_gpiod))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",69,o22_y23_gpiod);
			return ;
		}

		o22_y23 = gpiod_get_value(o22_y23_gpiod);
		gpiod_put(o22_y23_gpiod);

		PM_NOTI("o22_y23[%d]\n",o22_y23);
	}

	#if 0
	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		/* do nothing */
	}
	else
	{
		/* need to be declared in kernel */
		if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
			gpiod_add_lookup_table(&pm_gpio_table);
		}
	}

	/* need to fix regul_get fail*/
	if(o22_regulator == NULL)
	{
		while( o22_is_get == 0 && tcnt < O22_REGUL_GET_MAX  )
		{
			o22_regulator = regulator_get(NULL, "cpu0");
			if (IS_ERR(o22_regulator)) {
				msleep(1000);
				tcnt++;
				if( tcnt >= O22_REGUL_GET_MAX)
				{
					PM_ERROR("couldn't get cpu0 regulator regulator\n");
					break;
				}
			}
			else
			{
				PM_NOTI("regulator_init[%d]\n",tcnt);
				o22_is_get = 1;
				break;
			}
		}
	}
	#endif

	pm_o22_func = get_o22_pm_func();

	if(o22_cpu_ts_base == NULL)
		o22_cpu_ts_base = ioremap( 0xc6032000, 0x18);

	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, o22_cpu_ts_base);


	/* cpu_ts_aparam, cpu_ts_bparam, gpu_ts_aparam, gpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -434(cpu_ts_bparam)  + 186(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */
	/* gpu temp =  -434(gpu_ts_bparam)  + 186(gpu_ts_aparam)*(TSADC_GPU_RAW_DATA) */

	o22_avs_info.cpu_ts_aparam = 1497;
	o22_avs_info.cpu_ts_bparam = 33720000;

	/* avs table is changed when gpu temp reach 80'c */

	o22_avs_info.avshigh_th = 80;
	o22_avs_info.is_avshigh = 0;
	o22_avs_info.avshigh_count = 0;

	o22_avs_info.ts_debug_enable = 0;
	o22_avs_info.HVT_cpu = o22_cpuHS >> 16 & 0xffff;
	o22_avs_info.SVT_cpu = o22_cpuHS & 0xffff;
	o22_avs_info.Nskew_cpu = o22_cpuNP >> 16 & 0xffff;
	o22_avs_info.Pskew_cpu = o22_cpuNP & 0xffff;

	o22_avs_info.HVT_gpu = o22_gpuHS >> 16 & 0xffff;
	o22_avs_info.SVT_gpu = o22_gpuHS & 0xffff;
	o22_avs_info.Nskew_gpu = o22_gpuNP >> 16 & 0xffff;
	o22_avs_info.Pskew_gpu = o22_gpuNP & 0xffff;
	if((o22_core_avs > 0) && (o22_core_avs < O22_CORE_AVS_INVALID_MAX) &&
		(o22_cpu_avs > 0) && (o22_cpu_avs < O22_CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_siddl = o22_avsinfo & 0xffff;
		cpu_siddl  = (o22_avsinfo >> 16) & 0xffff;

		/* temperature param is determined by A0-A2 range , no change in A3*/
		if (lx_chip_rev() >= LX_CHIP_REV(O22,A0) ){
			core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
			core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
			core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
			cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
			cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
		}
		else
		{
			core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
			core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_n_min);
			core_sidd_s_min_th =(unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].core_sidd_s_min);

			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
			cpu_sidd_n_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min);
			cpu_sidd_s_min_th = (unsigned int)(gSidd_check_table_o22[SIDD_CHECK_TABLE_AX].cpu_sidd_s_min);
		}

		if( core_siddl > core_sidd_ff_min_th){
			o22_avs_info.cpu_ts_aparam = 1438;
			o22_avs_info.cpu_ts_bparam = 32190000;
		}
		else if( core_siddl > core_sidd_f_min_th){
			o22_avs_info.cpu_ts_aparam = 1524;
			o22_avs_info.cpu_ts_bparam = 34770000;
		}
		else if( core_siddl > core_sidd_n_min_th){
			o22_avs_info.cpu_ts_aparam = 1524;
			o22_avs_info.cpu_ts_bparam = 34770000;
		}
		else if( core_siddl > core_sidd_s_min_th){
			o22_avs_info.cpu_ts_aparam = 1497;
			o22_avs_info.cpu_ts_bparam = 33720000;
		}
		else{
			o22_avs_info.cpu_ts_aparam = 1497;
			o22_avs_info.cpu_ts_bparam = 33720000;
		}

#ifndef O22_CPUCTRL_I2C_SLT
		if(o22_y23)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A3)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_A3]);
				if(ret != 0)
					return ;
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ;
			}
		}
		else
#endif
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O22,A0)){
				ret = pm_o22_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o22[SIDD_CHECK_TABLE_AX]);
				if(ret != 0)
					return ;
			}
		}


	}
}

static pms_o22_avs_t o22_pm_avs =
{
	.init = o22_AvsInit,
	.reinit = o22_AvsReInit,
	.set_avs = pm_o22_set_avs,
	.set_coreavs = pm_o22_set_coreavs,
	.get_cpu_avs_type = pm_o22_get_cpu_avs,
	.get_cpu_avs_type_str = pm_o22_get_cpu_avs_str,
	.get_core_avs_type = pm_o22_get_core_avs,
	.get_core_avs_type_str = pm_o22_get_core_avs_str,
	.set_avs_in_resume = pm_o22_set_avs_in_resume,
	.set_avs_force = pm_o22_set_avs_force,
	.check_n_set = pm_o22_check_n_set,
	.ioctl = o22_pm_ioctl_avs,
	.check_ts = o22_check_ts,
	.get_cpu_ts_aparam = o22_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = o22_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = o22_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = o22_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = o22_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = o22_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = o22_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = o22_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = o22_pm_get_ts_debug_enable,
	.set_ts_debug_enable = o22_pm_set_ts_debug_enable,
	.get_temperature = o22_pm_get_temperature,

};

pms_o22_avs_t* get_o22_pm_avs(void)
{
	return &o22_pm_avs;
}


