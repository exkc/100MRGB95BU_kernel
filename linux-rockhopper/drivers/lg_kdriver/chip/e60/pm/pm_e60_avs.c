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
#include <linux/delay.h>
#include "os_util.h"

#include "gpio_core.h"

#include "pm_e60common.h"

#include "sys_regs.h"
#include "gpio_reg.h"

#include "sys_io.h"

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


#define E60_GPIO_AVS_CORE0        21
#define E60_GPIO_AVS_CORE1        22

#define E60_GPIO_AVS_CPU0         9
#define E60_GPIO_AVS_CPU1         10

#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

#define E60_CORE_SIDD_FFF_MIN_TH_AX  400     //mA
#define E60_CORE_SIDD_FF_MIN_TH_AX  200     //mA
#define E60_CORE_SIDD_F_MIN_TH_AX   150     //mA
#define E60_CORE_SIDD_N_MIN_TH_AX   100      //mA

/* caution: core sidd is used for cpu avs range */
#define E60_CPU_SIDD_FF_MIN_TH_AX   200     //mA
#define E60_CPU_SIDD_F_MIN_TH_AX    150     //mA
#define E60_CPU_SIDD_N_MIN_TH_AX    100      //mA

#define E60_TS_SIDD_FF_MIN_TH_AX   200     //mA
#define E60_TS_SIDD_F_MIN_TH_AX    150     //mA
#define E60_TS_SIDD_N_MIN_TH_AX    100      //mA

#define E60_CORE_SIDD_VALID_MIN     5 //mA
#define E60_CORE_SIDD_VALID_MAX     600 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5


/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_e60[6] = { "XXX","0.93","0.89","0.89", "0.89","0.89", };
static char * cpu_vidttype[6] = { "GPIO 9[1] 10[1]","GPIO 9[1] 10[1]","GPIO 9[1] 10[0]","GPIO 9[0] 10[1]","GPIO 9[0] 10[0]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_e60[6] = { "XXX","0.83","0.77","0.77", "0.77","0.77", };
char * core_volttype_high_e60[6] = { "XXX","0.83","0.77","0.77", "0.77","0.77", };
static char * core_vidttype[6] = { "GPIO 21[1] 22[1]","GPIO 21[1] 22[1]","GPIO 21[1] 22[0]","GPIO 21[0] 22[1]","GPIO 21[0] 22[0]", };

static unsigned int e60_avsinfo = 0;
static unsigned int e60_cpu_avs = 0;
static unsigned int e60_core_avs = 0;
static unsigned int e60_cpuHS = 0;
static unsigned int e60_cpuNP = 0;
static unsigned int e60_gpuHS = 0;
static unsigned int e60_gpuNP = 0;
extern int e60_pms_tcorevol;
extern int e60_is_prepared;
static UINT32 core_avs= 0, cpu_avs = 0;

module_param(e60_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(e60_avsinfo, "e60_avsinfo");

module_param(e60_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(e60_cpu_avs, "e60_cpu_avs");

module_param(e60_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(e60_core_avs, "e60_core_avs");

module_param(e60_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(e60_cpuHS, "e60_cpuHS");

module_param(e60_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(e60_cpuNP, "e60_cpuNP");

module_param(e60_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(e60_gpuHS, "e60_gpuHS");

module_param(e60_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(e60_gpuNP, "e60_gpuNP");

                                                /* ffast */
static unsigned int cpu_sidd_ff_min_th;
                                                /* fast */
static unsigned int cpu_sidd_f_min_th;
                                                /* normal */
static unsigned int cpu_sidd_n_min_th;
                                                /* slow */


                                                /* fff */
static unsigned int core_sidd_fff_min_th;
                                                /* ffast */
static unsigned int core_sidd_ff_min_th;
                                                /* fast */
static unsigned int core_sidd_f_min_th;
                                                /* normal */
static unsigned int core_sidd_n_min_th;
                                                /* slow */


                                                /* ffast */
static unsigned int ts_sidd_ff_min_th;
                                                /* fast */
static unsigned int ts_sidd_f_min_th;
                                                /* normal */
static unsigned int ts_sidd_n_min_th;
                                                /* slow */

pms_e60_avsinto_t	e60_avs_info;

e60_sidd_t gSidd_check_table_e60[SIDD_CHECK_TABLE_NUM]={

        [SIDD_CHECK_TABLE_AX]={
        .cpu_sidd_ff_min = E60_CPU_SIDD_FF_MIN_TH_AX,
        .cpu_sidd_f_min = E60_CPU_SIDD_F_MIN_TH_AX,
        .cpu_sidd_n_min = E60_CPU_SIDD_N_MIN_TH_AX,

        .core_sidd_fff_min = E60_CORE_SIDD_FFF_MIN_TH_AX,
        .core_sidd_ff_min = E60_CORE_SIDD_FF_MIN_TH_AX,
        .core_sidd_f_min = E60_CORE_SIDD_F_MIN_TH_AX,
        .core_sidd_n_min = E60_CORE_SIDD_N_MIN_TH_AX,

	.core_sidd_valid_max = E60_CORE_SIDD_VALID_MAX,
	.core_sidd_valid_min = E60_CORE_SIDD_VALID_MIN,

        .ts_sidd_ff_min = E60_TS_SIDD_FF_MIN_TH_AX,
        .ts_sidd_f_min = E60_TS_SIDD_F_MIN_TH_AX,
        .ts_sidd_n_min = E60_TS_SIDD_N_MIN_TH_AX
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
static pms_e60_func_t* pm_e60_func = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/

//BEGIN GPIO_KERNEL_API
#define CPU_AVS_S_UV		981000
#define CPU_AVS_N_UV		941000  /* action vol is 941 */
#define CPU_AVS_F_UV		960000 	/* action vol is 960 */
#define CPU_AVS_FF_UV		920000

#define CORE_AVS_S_MV		940
#define CORE_AVS_N_MV		920
#define CORE_AVS_F_MV		900
#define CORE_AVS_FF_MV		880
#define CORE_AVS_FFF_MV		860

#define CORE_AVS_S_MV_HIGH_TEMP		920
#define CORE_AVS_N_MV_HIGH_TEMP		900
#define CORE_AVS_F_MV_HIGH_TEMP		870
#define CORE_AVS_FF_MV_HIGH_TEMP	850
#define CORE_AVS_FFF_MV_HIGH_TEMP	840

#define CPU_TS_EN			(1 << 0)
#define GPU_TS_EN			(1 << 0)

#define CPU_TS_RAW_INTR_EN			(1 << 24)
#define GPU_TS_RAW_INTR_EN			(1 << 24)


#include <linux/tick.h>
#include <linux/device.h>
#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>
#include <linux/regulator/consumer.h>

static unsigned int ts_timer_count = 0;
static unsigned int	ts_timer_count_1s = HZ / ((HZ / 100) * (20 / 10));

struct delayed_work e60_avs_cpuwork;
struct delayed_work e60_avs_corework;
struct workqueue_struct *avsmain_wq;
struct workqueue_struct *avscpu_wq;
struct workqueue_struct *avscore_wq;

int e60_cpuwork_stage = 0;
int e60_cpuwork_target = 0;
int e60_corework_stage = 0;
int e60_corework_target = 0;

void __iomem *e60_cpu_ts_base = NULL;
void __iomem *e60_gpu_ts_base = NULL;

struct gpio_desc * gpiod_corevid0 = NULL;
struct gpio_desc * gpiod_corevid1 = NULL;
struct device corevid0_dev = { .init_name = "gpio_kerneltable", }; //GPIO INIT CONTROL;
struct device corevid1_dev = { .init_name = "gpio_kerneltable", }; //GPIO INIT CONTROL;

#if 0
static struct gpiod_lookup_table pm_gpio_table = {

        .dev_id = "pm_gpio",

        .table = {
					GPIO_LOOKUP_IDX("fd410000.gpio", 1, "9", 0, GPIO_ACTIVE_HIGH),
					GPIO_LOOKUP_IDX("fd410000.gpio", 2, "10", 0, GPIO_ACTIVE_HIGH),

		 { },

		},


};

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

static void e60_avs_cpuwork_req(void)
{
	queue_delayed_work(avscpu_wq,&e60_avs_cpuwork,msecs_to_jiffies(E60_AVS_STEP_DELAY));
}
static void e60_avs_corework_req(void)
{

	queue_delayed_work(avscore_wq,&e60_avs_corework, msecs_to_jiffies(E60_AVS_STEP_DELAY));
}

void e60_avs_cpuwork_func(struct work_struct *work)
{
	struct regulator *regulator;
	int ret;

	if(e60_is_prepared){
		PM_NOTI("SET CPU SKIP\n" );
		return;
	}
	regulator = regulator_get(NULL, "cpu0");
	if (IS_ERR(regulator)) {
		PM_ERROR("couldn't get cpu0 regulator regulator\n");
		return ;
	}

	if(e60_cpuwork_target >= CPU_AVS_S &&  e60_cpuwork_target <=CPU_AVS_FF){
		if(e60_cpuwork_stage == 3){
			ret = regulator_set_voltage(regulator, CPU_AVS_FF_UV,CPU_AVS_FF_UV);
			PM_NOTI("SET CPU FF\n" );
			e60_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(e60_cpuwork_stage == 2){
			ret = regulator_set_voltage(regulator, CPU_AVS_F_UV,CPU_AVS_F_UV);
			PM_NOTI("SET CPU F\n" );
			e60_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(e60_cpuwork_stage == 1){
			ret = regulator_set_voltage(regulator, CPU_AVS_N_UV,CPU_AVS_N_UV);
			PM_NOTI("SET CPU N\n" );
			e60_cpuwork_stage++;
			goto cpuavs_subwork;
		}
		else if(e60_cpuwork_stage == 0){
			ret = regulator_set_voltage(regulator, CPU_AVS_S_UV,CPU_AVS_S_UV);
			PM_NOTI("SET CPU S\n" );
			e60_cpuwork_stage++;
			goto cpuavs_subwork;
		}

	}
	else{
		ret = regulator_set_voltage(regulator, CPU_AVS_S_UV,CPU_AVS_S_UV);
		e60_cpuwork_stage = 0;
		e60_cpuwork_target = 0;
		goto end_cpuavs_subowrk;
	}

cpuavs_subwork:
	if(e60_cpuwork_target != e60_cpuwork_stage){
		e60_avs_cpuwork_req();
	}
end_cpuavs_subowrk:
	regulator_put(regulator);
	if(e60_cpuwork_target == e60_cpuwork_stage)
	{
		PM_NOTI("CPUAVS[%d] [%d][%d]\n",ret,e60_cpuwork_target,e60_cpuwork_stage );
		e60_cpuwork_stage = 0;
		e60_cpuwork_target = 0;
	}
	if(e60_is_prepared)
		PM_NOTI("SET CPU SKIP\n" );
	return ;
}

void e60_avs_corework_func(struct work_struct *work)
{
	if(e60_is_prepared){
		PM_NOTI("SET CORE SKIP\n" );
		return;
	}

	if(e60_corework_target >= CORE_AVS_S  && e60_corework_target <= CORE_AVS_FF){
		if(e60_corework_stage == 3){
			gpiod_set_value(gpiod_corevid1, (int) 0 );
			gpiod_set_value(gpiod_corevid0, (int) 0 );
			PM_NOTI("SET CORE FF\n" );
			e60_corework_stage++;
			goto coreavs_subwork;
		}
		else if(e60_corework_stage == 2){
			gpiod_set_value(gpiod_corevid1, (int) 1 );
			gpiod_set_value(gpiod_corevid0, (int) 0 );
			PM_NOTI("SET CORE F\n" );
			e60_corework_stage++;
			goto coreavs_subwork;
		}
		else if(e60_corework_stage == 1){
			gpiod_set_value(gpiod_corevid0, (int) 1 );
			gpiod_set_value(gpiod_corevid1, (int) 0 );
			PM_NOTI("SET CORE N\n" );
			e60_corework_stage++;
			goto coreavs_subwork;
		}
		else if(e60_corework_stage == 0){
			gpiod_set_value(gpiod_corevid0, (int) 1 );
			gpiod_set_value(gpiod_corevid1, (int) 1 );
			PM_NOTI("SET CORE S\n" );
			e60_corework_stage++;
			goto coreavs_subwork;
		}

	}else{
		//HV
		gpiod_set_value(gpiod_corevid0, (int) 1 );
		gpiod_set_value(gpiod_corevid1, (int) 1 );
		e60_corework_stage = 0;
		e60_corework_target = 0;
		goto end_coreavs_subwork;
	}

coreavs_subwork:
	if(e60_corework_target != e60_corework_stage)
	{
		e60_avs_corework_req();
	}
end_coreavs_subwork:
	if(e60_corework_target == e60_corework_stage)
	{
		e60_corework_stage = 0;
		e60_corework_target = 0;
	}
	if(e60_is_prepared)
		PM_NOTI("SET CORE SKIP\n" );
	return ;
}



int __pm_e60_set_vol(UINT32 core_cpu, UINT32 type, UINT32 is_step)
{
	pms_e60_work_t pms_work ;
	int stabletime = 20; /* ms */
	struct regulator *regulator;
	int ret,prevMV;

	memset(&pms_work, 0x0, sizeof(pms_e60_work_t));
	pm_e60_func = get_e60_pm_func();

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		if (core_cpu == GPIO_AVS_CPU ){

			switch(type){
				case CPU_AVS_S:
					//HV
					_GPIO_SetValue(E60_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(E60_GPIO_AVS_CPU1,1);
					break;
				case CPU_AVS_N:
					//MV
					_GPIO_SetValue(E60_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(E60_GPIO_AVS_CPU1,0);
					break;
				case CPU_AVS_F:
					//LV
					_GPIO_SetValue(E60_GPIO_AVS_CPU1,1);
					_GPIO_SetValue(E60_GPIO_AVS_CPU0,0);
					break;
				case CPU_AVS_FF:
					//VLV
					_GPIO_SetValue(E60_GPIO_AVS_CPU0,0);
					_GPIO_SetValue(E60_GPIO_AVS_CPU1,0);
					break;
				default:
					//HV
					_GPIO_SetValue(E60_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(E60_GPIO_AVS_CPU1,1);
					break;
			}
		}
		else if (core_cpu == GPIO_AVS_CORE && e60_avs_info.is_avshigh == 0){

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
				case CORE_AVS_FFF:
					pms_work.target_corevol = CORE_AVS_FFF_MV;

					break;
				default:
					//HV
					pms_work.target_corevol = CORE_AVS_S_MV;
					break;
			}
			pms_work.do_avs = 1;
			/* fixme : e60  not use pmic at initial */
			//pm_e60_func->run_regul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && e60_avs_info.is_avshigh == 1){

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
				case CORE_AVS_FFF:
					pms_work.target_corevol = CORE_AVS_FFF_MV_HIGH_TEMP;

					break;
				default:
					//HV
					pms_work.target_corevol = CORE_AVS_S_MV_HIGH_TEMP;
					break;
			}
			pms_work.do_avs = 1;
			/* fixme : e60  not use pmic at initial */
			//pm_e60_func->run_regul(pms_work);
		}
	}
	else // GPIO_KERNEL_API
	{
		if(is_step == 1) { /* before step set case: avs step set */
			if (core_cpu == GPIO_AVS_CPU ){
				e60_cpuwork_target = type;
				e60_cpuwork_stage = 0;
				queue_delayed_work(avscpu_wq,&e60_avs_cpuwork, msecs_to_jiffies(1));
			}
			else if (core_cpu == GPIO_AVS_CORE){
				e60_corework_target = type;
				e60_corework_stage = 0;
				if(e60_corework_target >= CORE_AVS_S && e60_corework_target <= CORE_AVS_FF )
					stabletime = 20 + (e60_corework_target) * 2000;
				queue_delayed_work(avscore_wq,&e60_avs_corework, msecs_to_jiffies(stabletime));
			}

		}
		else if (is_step == 0){	/* set avs direct   */
				if (core_cpu == GPIO_AVS_CPU ){
				regulator = regulator_get(NULL, "cpu0");
				if (IS_ERR(regulator)) {
					PM_ERROR("couldn't get cpu0 regulator regulator\n");
					return 0;
				}

				prevMV = regulator_get_voltage(regulator) ;


				switch(type){
					case CPU_AVS_S:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_S_UV,CPU_AVS_S_UV);
						PM_NOTI("SET CPU s\n" );
						break;
					case CPU_AVS_N:
						//MV
						ret = regulator_set_voltage(regulator, CPU_AVS_N_UV,CPU_AVS_N_UV);
						PM_NOTI("SET CPU n\n" );
						break;
					case CPU_AVS_F:
						//LV
						ret = regulator_set_voltage(regulator, CPU_AVS_F_UV,CPU_AVS_F_UV);
						PM_NOTI("SET CPU f\n" );
						break;
					case CPU_AVS_FF:
						//VLV
						ret = regulator_set_voltage(regulator, CPU_AVS_FF_UV,CPU_AVS_FF_UV);
						PM_NOTI("SET CPU ff\n" );
						break;
					default:
						//HV
						ret = regulator_set_voltage(regulator, CPU_AVS_S_UV,CPU_AVS_S_UV);
						break;
				}
				PM_NOTI("cpu ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(regulator) );
				regulator_put(regulator);
			}
			else if (core_cpu == GPIO_AVS_CORE ){
				switch(type){
					case CORE_AVS_S:
						//HV
						gpiod_set_value(gpiod_corevid0, (int) 1 );
						gpiod_set_value(gpiod_corevid1, (int) 1 );
						PM_NOTI("SET CORE s\n" );
						break;
					case CORE_AVS_N:
						//MV
						gpiod_set_value(gpiod_corevid0, (int) 1 );
						gpiod_set_value(gpiod_corevid1, (int) 0 );
						PM_NOTI("SET CORE n\n" );

						break;
					case CORE_AVS_F:
						//LV
						gpiod_set_value(gpiod_corevid1, (int) 1 );
						gpiod_set_value(gpiod_corevid0, (int) 0 );
						PM_NOTI("SET CORE f\n" );
						break;
					case CORE_AVS_FF:
						//VLV
						gpiod_set_value(gpiod_corevid1, (int) 0 );
						gpiod_set_value(gpiod_corevid0, (int) 0 );
						PM_NOTI("SET CORE ff\n" );
						break;
					default:
						//HV
						gpiod_set_value(gpiod_corevid0, (int) 1 );
						gpiod_set_value(gpiod_corevid1, (int) 1 );
						break;
				}
			}
		}
	}

	return 0;
}


int pm_e60_check_sidd_valid( UINT32 core_sidd,  UINT32 cpu_sidd, e60_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_sidd > core_sidd_valid_max || core_sidd < core_sidd_valid_min) {
		__pm_e60_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 1 );
		__pm_e60_set_vol(GPIO_AVS_CORE,CORE_AVS_S,1);
		 PM_ERROR("E60 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x] core[%d:%x] cpu[%d:%x]\n",cpu_volttype_e60[CPU_AVS_S],core_volttype_e60[CORE_AVS_S],lx_chip_rev(),core_sidd,core_sidd,cpu_sidd,cpu_sidd);
		return -1;
	}

	return 0;
}

int pm_e60_get_cpu_avs(pms_e60_avsinto_t * info)
{
	info->avstype = cpu_avs;

	if(e60_avsinfo)
	{
		info->avscurrent = e60_avsinfo & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	info->HVT_cpu = e60_cpuHS >> 16 & 0xffff;
	info->SVT_cpu = e60_cpuHS & 0xffff;
	info->Nskew_cpu = e60_cpuNP >> 16 & 0xffff;
	info->Pskew_cpu = e60_cpuNP & 0xffff;
	info->HVT_gpu = e60_gpuHS >> 16 & 0xffff;
	info->SVT_gpu = e60_gpuHS & 0xffff;
	info->Nskew_gpu = e60_gpuNP >> 16 & 0xffff;
	info->Pskew_gpu = e60_gpuNP & 0xffff;

	return (int)cpu_avs;
}
unsigned char * pm_e60_get_cpu_avs_str(void)
{
	return cpu_avstype[cpu_avs];
}

unsigned char * pm_e60_get_cpu_volt_str(void)
{
	return cpu_volttype_e60[cpu_avs];
}


int pm_e60_get_core_avs(pms_e60_avsinto_t * info)
{
	info->avstype = core_avs;

	if(e60_avsinfo)
	{
		info->avscurrent =  (e60_avsinfo >> 16) & 0xffff;

	}else
	{
		info->avscurrent = 0;
	}

	return (int)core_avs;
}

unsigned char *  pm_e60_get_core_avs_str(void)
{
		return core_avstype[core_avs];
}

unsigned char *  pm_e60_get_core_volt_str(void)
{
		return core_volttype_e60[core_avs];
}

int pm_e60_set_avs(void)
{
	int ret = -1;
	UINT32 core_sidd = 0, cpu_sidd = 0;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		GPIO_DevSetPinMux(E60_GPIO_AVS_CPU0, 1);
		GPIO_DevSetPinMux(E60_GPIO_AVS_CPU1, 1);

		/* FIXME: need to implementation using regulator */

		_GPIO_SetMode(E60_GPIO_AVS_CPU0, 1);
		_GPIO_SetMode(E60_GPIO_AVS_CPU1, 1);
	}
	else // GPIO_KERNEL_API
	{
		/* GPIO_DevSetPinMux is not working in GPIO_KERNEL_API */
		/* need to check */
	}


	/* do avs using e60_core_avs,e60_cpu_avs of bootargs */
	if((e60_core_avs > 0) && (e60_core_avs < CORE_AVS_INVALID_MAX) &&
		(e60_cpu_avs > 0) && (e60_cpu_avs < CPU_AVS_INVALID_MAX))
	{

		/*  correct AVS info case:  */
		core_sidd = e60_avsinfo & 0xffff;
		cpu_sidd  = (e60_avsinfo >> 16) & 0xffff;
		printk("e60 AVS info valid e60_avsinfo[%x] \n",e60_avsinfo);

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;

			ts_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_ff_min;
			ts_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_f_min;
			ts_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_n_min;;
		}
		else{
			__pm_e60_set_vol(GPIO_AVS_CPU,CPU_AVS_S,1);
			__pm_e60_set_vol(GPIO_AVS_CORE,CORE_AVS_S,1);
			printk("E60 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_e60[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_e60[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0)){
			ret = pm_e60_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_e60[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ret;
		}

		/* core voltage table is different from ts table */

		if( core_sidd > ts_sidd_ff_min_th){
			e60_avs_info.cpu_ts_aparam = 1332;
			e60_avs_info.cpu_ts_bparam = 30634000;
		}
		else if( core_sidd > ts_sidd_f_min_th){
			e60_avs_info.cpu_ts_aparam = 1357;
			e60_avs_info.cpu_ts_bparam = 31409000;
		}
		else if( core_sidd > ts_sidd_n_min_th){
			e60_avs_info.cpu_ts_aparam = 1417;
			e60_avs_info.cpu_ts_bparam = 32941000;
		}
		else{
			e60_avs_info.cpu_ts_aparam = 1566;
			e60_avs_info.cpu_ts_bparam = 37264000;
		}

		/* use coresidd only for core,cpu voltage table */
		if( core_sidd > core_sidd_ff_min_th){
				core_avs =	CORE_AVS_FF;
				cpu_avs =	CPU_AVS_FF;
		}
		else if( core_sidd > core_sidd_f_min_th){
				core_avs =	CORE_AVS_F;
				cpu_avs =	CPU_AVS_F;
		}
		else if( core_sidd > core_sidd_n_min_th){
				core_avs =	CORE_AVS_N;
				cpu_avs =	CPU_AVS_N;
		}
		else{
				core_avs =	CORE_AVS_S;
				cpu_avs =	CPU_AVS_S;
		}
		/* store avs info to suspend resume */
		//cpu_avs = e60_cpu_avs;
		//core_avs = e60_core_avs;

		__pm_e60_set_vol(GPIO_AVS_CPU,cpu_avs,1);
		__pm_e60_set_vol(GPIO_AVS_CORE,core_avs,1);
		/* crc fail or brank case :  default HV(Slow chip condition)  */

		printk("E60 AVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype_e60[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_e60[core_avs],core_vidttype[core_avs],lx_chip_rev());
		return 0;
	}

	/* do avs using kdriver avs param */
	else if(e60_avsinfo)
	{
		/*  correct AVS info case:  */
		cpu_sidd = e60_avsinfo & 0xffff;
		core_sidd  = (e60_avsinfo >> 16) & 0xffff;
		printk("E60 AVS avs info valid e60_avsinfo[%x] \n",e60_avsinfo);

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
		}
		else{
			__pm_e60_set_vol(GPIO_AVS_CPU,CPU_AVS_S,1);
			__pm_e60_set_vol(GPIO_AVS_CORE,CORE_AVS_S,1);
			printk("E60 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
			,lx_chip_rev(),cpu_volttype_e60[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_e60[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0)){
			ret = pm_e60_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_e60[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			return ret;
		}

		/* core voltage table is different from cpu voltage table */
		if( core_sidd > core_sidd_fff_min_th){
				core_avs =	CORE_AVS_FFF;
		}
		else if( core_sidd > core_sidd_ff_min_th){
				core_avs =	CORE_AVS_FF;
		}
		else if( core_sidd > core_sidd_f_min_th){
				core_avs =	CORE_AVS_F;
		}
		else if( core_sidd > core_sidd_n_min_th){
				core_avs =	CORE_AVS_N;
		}
		else{
				core_avs =	CORE_AVS_S;
		}

		/* caution: cpu avs is determined depending on core sidd */
		if( core_sidd > cpu_sidd_ff_min_th){
				cpu_avs =  CPU_AVS_FF;
		}
		else if( core_sidd > cpu_sidd_f_min_th){
				cpu_avs =  CPU_AVS_F;
		}
		else if( core_sidd > cpu_sidd_n_min_th){
				cpu_avs =  CPU_AVS_N;
		}
		else{
				cpu_avs =  CPU_AVS_S;
		}

		__pm_e60_set_vol(GPIO_AVS_CORE,core_avs,1);
		__pm_e60_set_vol(GPIO_AVS_CPU,cpu_avs,1);

		if(e60_avs_info.is_avshigh)
		{
			printk("E60 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_e60[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_high_e60[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}
		else
		{
			printk("E60 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_e60[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_e60[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}
		return 0;

	}
	/* skip avs */
	else{
		__pm_e60_set_vol(GPIO_AVS_CPU,CPU_AVS_S,1);
		__pm_e60_set_vol(GPIO_AVS_CORE,CORE_AVS_S,1);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("E60 AVS avs info is not valid, skipped! e60_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,e60_avsinfo,cpu_volttype_e60[CPU_AVS_S],core_volttype_e60[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}


int pm_e60_set_avs_force(UINT32 core_cpu, UINT32 type)
{

	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
	}
	else if (core_cpu == GPIO_AVS_CORE ){
		core_avs = type;
	}
	__pm_e60_set_vol(core_cpu,type,1);

	PM_NOTI("E60 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n"
	,cpu_avstype[cpu_avs],cpu_volttype_e60[cpu_avs],cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype_e60[core_avs],core_vidttype[core_avs]  );

	return 0;
}

int pm_e60_set_avs_in_resume(void)
{
	UINT32 core_sidd = 0, cpu_sidd = 0;
	//UINT32 mask = 0, value = 0;
	if((core_avs > 0) && (core_avs < CORE_AVS_INVALID_MAX) && (cpu_avs > 0) && (cpu_avs < CPU_AVS_INVALID_MAX))
	{
		if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
		{

			GPIO_DevSetPinMux(E60_GPIO_AVS_CPU0, 1);
			GPIO_DevSetPinMux(E60_GPIO_AVS_CPU1, 1);

			/* FIXME: need to implementation using regulator */

			_GPIO_SetMode(E60_GPIO_AVS_CPU0, 1);
			_GPIO_SetMode(E60_GPIO_AVS_CPU1, 1);

		}
		else // GPIO_KERNEL_API
		{

		}

		if(e60_avsinfo)
		{
			/*	correct AVS info case:	*/
			cpu_sidd = e60_avsinfo & 0xffff;
			core_sidd  = (e60_avsinfo >> 16) & 0xffff;
		}
		__pm_e60_set_vol(GPIO_AVS_CPU,cpu_avs,1);
		__pm_e60_set_vol(GPIO_AVS_CORE,core_avs,1);

		PM_NOTI("E60 AVSRESUME cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n"
		,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th
		,core_sidd,core_avstype[core_avs],cpu_volttype_e60[cpu_avs],cpu_vidttype[cpu_avs],core_volttype_e60[core_avs],core_vidttype[core_avs],lx_chip_rev() );

	}


	return 0;
}

int pm_e60_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int e60_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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

int e60_check_ts(void)
{
	int cpu_temp = 0, gpu_temp = 0, cpu_rem =0,gpu_rem =0;
	s64 cpu_tempa = 0, gpu_tempa = 0;
	unsigned int cpu_rawts = 0, gpu_rawts = 0;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s) {

#if 1
		/* OS_RdReg call ioremap which is restricted in soft isr */
		if(e60_cpu_ts_base != NULL) cpu_rawts = readl((void *)((uintptr_t)e60_cpu_ts_base + (uintptr_t)0x14) );
		if(e60_gpu_ts_base != NULL) gpu_rawts = readl((void *)((uintptr_t)e60_gpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			e60_avs_info.cpu_ts_aparam != 0  &&
			gpu_rawts != 0 &&
			e60_avs_info.gpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)e60_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)e60_avs_info.cpu_ts_bparam );
			gpu_tempa = ( (s64)e60_avs_info.gpu_ts_aparam * (s64)gpu_rawts  - (s64)e60_avs_info.gpu_ts_bparam );

			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem) ;
			gpu_temp = div_s64_rem(gpu_tempa,100000,&gpu_rem) ;

			if(cpu_rem > 50000)
				cpu_temp++;
			/*TS2 temp(0xc924e014) is more reliable*/
			e60_avs_info.temperature = cpu_temp;

			if( e60_avs_info.ts_debug_enable )
			{
				//PM_NOTI("------------------------------\n");
				PM_NOTI("E60 TEMP[%d]'C[%d] \n",cpu_temp,cpu_rawts);
			}

			if(gpu_temp > e60_avs_info.avshigh_th)
			{
				if(e60_avs_info.is_avshigh == 0)
				{
					e60_avs_info.avshigh_count++;

					if(e60_avs_info.avshigh_count > 5 )
					{
						e60_avs_info.is_avshigh = 1;
						e60_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("E60 HIGH: GPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						//pm_e60_set_avs();
						return 1 ;
					}
				}

			}
		}
#endif

		ts_timer_count = 0;
	}
	return 0 ;
}

static int e60_pm_set_cpu_ts_aparam(unsigned int value)
{
	e60_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int e60_pm_set_cpu_ts_bparam(unsigned int value)
{
	e60_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int e60_pm_get_cpu_ts_aparam(void)
{
	return e60_avs_info.cpu_ts_aparam;
}

static unsigned int e60_pm_get_cpu_ts_bparam(void)
{
	return e60_avs_info.cpu_ts_bparam;
}

static int e60_pm_set_gpu_ts_aparam(unsigned int value)
{
	e60_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int e60_pm_set_gpu_ts_bparam(unsigned int value)
{
	e60_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int e60_pm_get_gpu_ts_aparam(void)
{
	return e60_avs_info.gpu_ts_aparam;
}

static unsigned int e60_pm_get_gpu_ts_bparam(void)
{
	return e60_avs_info.gpu_ts_bparam;
}

static int e60_pm_set_ts_debug_enable(unsigned int value)
{
	e60_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int e60_pm_get_ts_debug_enable(void)
{
	return e60_avs_info.ts_debug_enable;
}

static int e60_pm_get_temperature(void)
{
	int cpu_temp = 0,cpu_rem=0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	if(e60_cpu_ts_base != NULL)
	{
		cpu_rawts = readl((void *)((uintptr_t)e60_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			e60_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)e60_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)e60_avs_info.cpu_ts_bparam );
			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem);
			if(cpu_rem > 50000)
				cpu_temp++;

			e60_avs_info.temperature = cpu_temp;
		}
	}

	return e60_avs_info.temperature;



}

void e60_AvsReInit(void)
{
	unsigned int val;

	if(e60_cpu_ts_base == NULL)		e60_cpu_ts_base = ioremap( 0xc932b000, 0x18);
	if(e60_gpu_ts_base == NULL)		e60_gpu_ts_base = ioremap( 0xc924e000, 0x18);

	//reg = readl(e60_cpu_ts_base);
	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, e60_cpu_ts_base);

	//reg = readl(e60_gpu_ts_base);
	val = GPU_TS_RAW_INTR_EN | GPU_TS_EN;
	writel(val, e60_gpu_ts_base);

}

void e60_AvsInit(void)
{
	unsigned int val;
	int ret;
	UINT32 core_sidd = 0, cpu_sidd = 0;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		/* do nothing */
	}
	else
	{
		/* need to be declared in kernel */
		//gpiod_add_lookup_table(&pm_gpio_table);
	}

	pm_e60_func = get_e60_pm_func();

	if(e60_cpu_ts_base == NULL)		e60_cpu_ts_base = ioremap( 0xc932b000, 0x18);
	if(e60_gpu_ts_base == NULL)		e60_gpu_ts_base = ioremap( 0xc924e000, 0x18);

	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, e60_cpu_ts_base);
	val = GPU_TS_RAW_INTR_EN | GPU_TS_EN;
	writel(val, e60_gpu_ts_base);

	if(gpiod_corevid0 == NULL && gpiod_corevid1 == NULL){
		gpiod_corevid0 = gpiod_get(&corevid0_dev, "21", GPIOD_OUT_HIGH);
		if (IS_ERR(gpiod_corevid0))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",21,gpiod_corevid0);
		}

		gpiod_corevid1 = gpiod_get(&corevid1_dev, "22", GPIOD_OUT_HIGH);
		if (IS_ERR(gpiod_corevid1))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",22,gpiod_corevid1);
		}
	}

	/* cpu_ts_aparam, cpu_ts_bparam, gpu_ts_aparam, gpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -434(cpu_ts_bparam)  + 186(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */
	/* gpu temp =  -434(gpu_ts_bparam)  + 186(gpu_ts_aparam)*(TSADC_GPU_RAW_DATA) */

	e60_avs_info.cpu_ts_aparam = 1417;
	e60_avs_info.cpu_ts_bparam = 32941000;
	e60_avs_info.gpu_ts_aparam = 1417;
	e60_avs_info.gpu_ts_bparam = 32941000;

	/* avs table is changed when gpu temp reach 80'c */

	e60_avs_info.avshigh_th = 80;
	e60_avs_info.is_avshigh = 0;
	e60_avs_info.avshigh_count = 0;

	e60_avs_info.ts_debug_enable = 0;
	e60_avs_info.HVT_cpu = e60_cpuHS >> 16 & 0xffff;
	e60_avs_info.SVT_cpu = e60_cpuHS & 0xffff;
	e60_avs_info.Nskew_cpu = e60_cpuNP >> 16 & 0xffff;
	e60_avs_info.Pskew_cpu = e60_cpuNP & 0xffff;

	e60_avs_info.HVT_gpu = e60_gpuHS >> 16 & 0xffff;
	e60_avs_info.SVT_gpu = e60_gpuHS & 0xffff;
	e60_avs_info.Nskew_gpu = e60_gpuNP >> 16 & 0xffff;
	e60_avs_info.Pskew_gpu = e60_gpuNP & 0xffff;
	//pm_e60_set_avs();

	if((e60_core_avs > 0) && (e60_core_avs < CORE_AVS_INVALID_MAX) &&
		(e60_cpu_avs > 0) && (e60_cpu_avs < CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_sidd = e60_avsinfo & 0xffff;
		cpu_sidd  = (e60_avsinfo >> 16) & 0xffff;

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;

			ts_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_ff_min;
			ts_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_f_min;
			ts_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_n_min;;
		}
		else
		{
			core_sidd_fff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;

			ts_sidd_ff_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_ff_min;
			ts_sidd_f_min_th =  gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_f_min;
			ts_sidd_n_min_th = gSidd_check_table_e60[SIDD_CHECK_TABLE_AX].ts_sidd_n_min;;

		}

		if (lx_chip_rev() >= LX_CHIP_REV(E60,A0)){
			ret = pm_e60_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_e60[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ;
		}

		/* core voltage table is different from ts table */
		if( core_sidd > ts_sidd_ff_min_th){
			e60_avs_info.cpu_ts_aparam = 1332;
			e60_avs_info.cpu_ts_bparam = 30634000;
		}
		else if( core_sidd > ts_sidd_f_min_th){
			e60_avs_info.cpu_ts_aparam = 1357;
			e60_avs_info.cpu_ts_bparam = 31409000;
		}
		else if( core_sidd > ts_sidd_n_min_th){
			e60_avs_info.cpu_ts_aparam = 1417;
			e60_avs_info.cpu_ts_bparam = 32941000;
		}
		else{
			e60_avs_info.cpu_ts_aparam = 1566;
			e60_avs_info.cpu_ts_bparam = 37264000;
		}

	}
}

static pms_e60_avs_t e60_pm_avs =
{
	.init = e60_AvsInit,
	.reinit = e60_AvsReInit,
	.set_avs = pm_e60_set_avs,
	.get_cpu_avs_type = pm_e60_get_cpu_avs,
	.get_cpu_avs_type_str = pm_e60_get_cpu_avs_str,
	.get_cpu_volt_str = pm_e60_get_cpu_volt_str,
	.get_core_avs_type = pm_e60_get_core_avs,
	.get_core_avs_type_str = pm_e60_get_core_avs_str,
	.get_core_volt_str = pm_e60_get_core_volt_str,
	.set_avs_in_resume = pm_e60_set_avs_in_resume,
	.set_avs_force = pm_e60_set_avs_force,
	.check_n_set = pm_e60_check_n_set,
	.ioctl = e60_pm_ioctl_avs,
	.check_ts = e60_check_ts,
	.get_cpu_ts_aparam = e60_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = e60_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = e60_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = e60_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = e60_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = e60_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = e60_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = e60_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = e60_pm_get_ts_debug_enable,
	.set_ts_debug_enable = e60_pm_set_ts_debug_enable,
	.get_temperature = e60_pm_get_temperature,

};

pms_e60_avs_t* get_e60_pm_avs(void)
{
	return &e60_pm_avs;
}


