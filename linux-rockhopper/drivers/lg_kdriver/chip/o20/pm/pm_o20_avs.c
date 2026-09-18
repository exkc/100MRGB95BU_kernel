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
//#include <linux/delay.h>
#include "os_util.h"

#include "gpio_core.h"

#include "pm_o20common.h"

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


#define GPIO_AVS_CORE0        9
#define GPIO_AVS_CORE1        10

#define O20_GPIO_AVS_CPU0         9
#define O20_GPIO_AVS_CPU1         10

#define O20_GPIO_AVS_CPU0_B0         9
#define O20_GPIO_AVS_CPU1_B0         6


#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

#define O20_CORE_SIDD_FFF_MIN_TH_AX  211     //mA
#define O20_CORE_SIDD_FF_MIN_TH_AX  137     //mA
#define O20_CORE_SIDD_F_MIN_TH_AX   100     //mA
#define O20_CORE_SIDD_N_MIN_TH_AX   60      //mA

/* caution: core sidd is used for cpu avs range */
#define O20_CPU_SIDD_FF_MIN_TH_AX   140     //mA
#define O20_CPU_SIDD_F_MIN_TH_AX    100     //mA
#define O20_CPU_SIDD_N_MIN_TH_AX    60      //mA

#define O20_CORE_SIDD_VALID_MIN     10 //mA
#define O20_CORE_SIDD_VALID_MAX     500 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5

//#define O20_REGUL_GET_MAX		30

/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_o20[6] = { "XXX","0.94","0.92","0.90", "0.86","0.86", };
static char * cpu_vidttype[6] = { "GPIO 9[1] 6[1]","GPIO 9[1] 6[1]","GPIO 9[1] 6[0]","GPIO 9[0] 6[1]","GPIO 9[0] 6[0]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_o20[6] = { "XXX","0.87","0.85","0.83", "0.80","0.80", };
char * core_volttype_high_o20[6] = { "XXX","0.85","0.83","0.81", "0.78","0.78", };
static char * core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

static unsigned int o20_avsinfo = 0;
static unsigned int o20_cpu_avs = 0;
static unsigned int o20_core_avs = 0;
static unsigned int o20_cpuHS = 0;
static unsigned int o20_cpuNP = 0;
static unsigned int o20_gpuHS = 0;
static unsigned int o20_gpuNP = 0;
extern int o20_pms_tcorevol;

static UINT32 core_avs= 0, cpu_avs = 0;

module_param(o20_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(o20_avsinfo, "o20_avsinfo");

module_param(o20_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o20_cpu_avs, "o20_cpu_avs");

module_param(o20_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o20_core_avs, "o20_core_avs");

module_param(o20_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o20_cpuHS, "o20_cpuHS");

module_param(o20_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o20_cpuNP, "o20_cpuNP");

module_param(o20_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o20_gpuHS, "o20_gpuHS");

module_param(o20_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o20_gpuNP, "o20_gpuNP");

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
pms_o20_avsinto_t	o20_avs_info;

o20_sidd_t gSidd_check_table_o20[SIDD_CHECK_TABLE_NUM]={

        [SIDD_CHECK_TABLE_AX]={
        .cpu_sidd_ff_min = O20_CPU_SIDD_FF_MIN_TH_AX,
        .cpu_sidd_f_min = O20_CPU_SIDD_F_MIN_TH_AX,
        .cpu_sidd_n_min = O20_CPU_SIDD_N_MIN_TH_AX,

        .core_sidd_fff_min = O20_CORE_SIDD_FFF_MIN_TH_AX,
        .core_sidd_ff_min = O20_CORE_SIDD_FF_MIN_TH_AX,
        .core_sidd_f_min = O20_CORE_SIDD_F_MIN_TH_AX,
        .core_sidd_n_min = O20_CORE_SIDD_N_MIN_TH_AX,

		.core_sidd_valid_max = O20_CORE_SIDD_VALID_MAX,
		.core_sidd_valid_min = O20_CORE_SIDD_VALID_MIN
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
static pms_o20_func_t* pm_o20_func = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/

//BEGIN GPIO_KERNEL_API

#define CORE_AVS_S_MV		870
#define CORE_AVS_N_MV		850
#define CORE_AVS_F_MV		830
#define CORE_AVS_FF_MV		800
#define CORE_AVS_FFF_MV		800

#define CORE_AVS_S_MV_HIGH_TEMP		850
#define CORE_AVS_N_MV_HIGH_TEMP		830
#define CORE_AVS_F_MV_HIGH_TEMP		810
#define CORE_AVS_FF_MV_HIGH_TEMP	780
#define CORE_AVS_FFF_MV_HIGH_TEMP	780

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
//int o20_is_get = 0;

void __iomem *o20_cpu_ts_base = NULL;

static struct gpiod_lookup_table pm_gpio_table = {

        .dev_id = "pm_gpio",

        .table = {
					GPIO_LOOKUP_IDX("fd410000.gpio", 1, "9", 0, GPIO_ACTIVE_HIGH),
					GPIO_LOOKUP_IDX("fd410000.gpio", 2, "10", 0, GPIO_ACTIVE_HIGH),

		 { },

		},


};

static struct gpiod_lookup_table pm_gpio_table_b0 = {

        .dev_id = "pm_gpio",

        .table = {
					GPIO_LOOKUP_IDX("fd410000.gpio", 1, "9", 0, GPIO_ACTIVE_HIGH),
					GPIO_LOOKUP_IDX("fd400000.gpio", 6, "6", 0, GPIO_ACTIVE_HIGH),

		 { },

		},

};

struct regulator *o20_regulator = NULL;

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

//END GPIO_KERNEL_API

int __pm_o20_set_vol(UINT32 core_cpu, UINT32 type)
{

	pms_o20_work_t pms_work ;

	memset(&pms_work, 0x0, sizeof(pms_o20_work_t));
	pm_o20_func = get_o20_pm_func();

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		if (core_cpu == GPIO_AVS_CPU ){

			switch(type){
				case CPU_AVS_S:
					//HV
					_GPIO_SetValue(O20_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O20_GPIO_AVS_CPU1,1);
					break;
				case CPU_AVS_N:
					//MV
					_GPIO_SetValue(O20_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O20_GPIO_AVS_CPU1,0);
					break;
				case CPU_AVS_F:
					//LV
					_GPIO_SetValue(O20_GPIO_AVS_CPU1,1);
					_GPIO_SetValue(O20_GPIO_AVS_CPU0,0);
					break;
				case CPU_AVS_FF:
					//VLV
					_GPIO_SetValue(O20_GPIO_AVS_CPU0,0);
					_GPIO_SetValue(O20_GPIO_AVS_CPU1,0);
					break;
				default:
					//HV
					_GPIO_SetValue(O20_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O20_GPIO_AVS_CPU1,1);
					break;
			}
		}
		else if (core_cpu == GPIO_AVS_CORE && o20_avs_info.is_avshigh == 0){

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
			pm_o20_func->run_regul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && o20_avs_info.is_avshigh == 1){

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
			pm_o20_func->run_regul(pms_work);
		}
	}
	else // GPIO_KERNEL_API
	{
		if (core_cpu == GPIO_AVS_CPU ){

			pms_work.target_vol = type;
			pms_work.do_avs = 2;
			pm_o20_func->run_cpuregul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && o20_avs_info.is_avshigh == 0 ){

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
			pm_o20_func->run_regul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && o20_avs_info.is_avshigh == 1 ){
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
				case CORE_AVS_FFF:
					pms_work.target_corevol = CORE_AVS_FFF_MV_HIGH_TEMP;

					break;
				default:
					//HV
					pms_work.target_corevol = CORE_AVS_S_MV_HIGH_TEMP;
					break;
			}
			pms_work.do_avs = 1;
			pm_o20_func->run_regul(pms_work);
		}
	}

	return 0;
}


int pm_o20_check_sidd_valid( UINT32 core_sidd,  UINT32 cpu_sidd, o20_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_sidd > core_sidd_valid_max || core_sidd < core_sidd_valid_min) {
		__pm_o20_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
		__pm_o20_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
		 PM_ERROR("O20 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x]\n",cpu_volttype_o20[CPU_AVS_S],core_volttype_o20[CORE_AVS_S],lx_chip_rev());
		return -1;
	}

	return 0;
}

int pm_o20_get_cpu_avs(pms_o20_avsinto_t * info)
{
	info->avstype = cpu_avs;

	if(o20_avsinfo)
	{
		info->avscurrent = (o20_avsinfo >> 16 ) & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	info->HVT_cpu = o20_cpuHS >> 16 & 0xffff;
	info->SVT_cpu = o20_cpuHS & 0xffff;
	info->Nskew_cpu = o20_cpuNP >> 16 & 0xffff;
	info->Pskew_cpu = o20_cpuNP & 0xffff;
	info->HVT_gpu = o20_gpuHS >> 16 & 0xffff;
	info->SVT_gpu = o20_gpuHS & 0xffff;
	info->Nskew_gpu = o20_gpuNP >> 16 & 0xffff;
	info->Pskew_gpu = o20_gpuNP & 0xffff;

	return (int)cpu_avs;
}
unsigned char * pm_o20_get_cpu_avs_str(void)
{
	return cpu_avstype[cpu_avs];
}


int pm_o20_get_core_avs(pms_o20_avsinto_t * info)
{
	info->avstype = core_avs;

	if(o20_avsinfo)
	{
		info->avscurrent =  (o20_avsinfo >> 16) & 0xffff;

	}else
	{
		info->avscurrent = 0;
	}

	return (int)core_avs;
}

unsigned char *  pm_o20_get_core_avs_str(void)
{
		return core_avstype[core_avs];
}

int pm_o20_set_avs(void)
{
	int ret = -1;
	UINT32 core_sidd = 0, cpu_sidd = 0;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		GPIO_DevSetPinMux(O20_GPIO_AVS_CPU0, 1);
		GPIO_DevSetPinMux(O20_GPIO_AVS_CPU1, 1);

		/* FIXME: need to implementation using regulator */

		_GPIO_SetMode(O20_GPIO_AVS_CPU0, 1);
		_GPIO_SetMode(O20_GPIO_AVS_CPU1, 1);
	}
	else // GPIO_KERNEL_API
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O20,B0)){
			_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU0_B0, 1);
			_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU1_B0, 1);
		}
		else if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
			_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU0, 1);
			_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU1, 1);
		}
	}


	if(o20_pms_tcorevol > 0 && o20_pms_tcorevol < VOUT_MAX )
	{

		pms_o20_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_o20_work_t));
		pms_work.target_corevol = o20_pms_tcorevol;
		pms_work.do_avs = 1;
		pm_o20_func->run_regul(pms_work);
		printk("O20 AVS bootparam tcorev[%d]mV cpu_avs[%d]\n",pms_work.target_corevol,o20_cpu_avs );
		if(o20_cpu_avs >0)
			__pm_o20_set_vol(GPIO_AVS_CPU,o20_cpu_avs);
		return 0;
	}

	/* do avs using o20_core_avs,o20_cpu_avs of bootargs */
	else if((o20_core_avs > 0) && (o20_core_avs < CORE_AVS_INVALID_MAX) &&
		(o20_cpu_avs > 0) && (o20_cpu_avs < O20_CPU_AVS_INVALID_MAX))
	{
		/* store avs info to suspend resume */
		cpu_avs = o20_cpu_avs;
		core_avs = o20_core_avs;

		/*  correct AVS info case:  */
		core_sidd = o20_avsinfo & 0xffff;
		cpu_sidd  = (o20_avsinfo >> 16) & 0xffff;
		printk("O20 AVS avs info valid o20_avsinfo[%x] \n",o20_avsinfo);

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
		}
		else{
			__pm_o20_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_o20_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
			printk("O20 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
			,lx_chip_rev(),cpu_volttype_o20[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o20[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
			ret = pm_o20_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_o20[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			return ret;
		}

		/* core voltage table is different from cpu voltage table */
		if( core_sidd >= core_sidd_ff_min_th){
			core_avs =	CORE_AVS_FF;
			o20_avs_info.cpu_ts_aparam = 1221;
			o20_avs_info.cpu_ts_bparam = 27206000;
		}
		else if( core_sidd >= core_sidd_f_min_th){
			core_avs =	CORE_AVS_F;
			o20_avs_info.cpu_ts_aparam = 1240;
			o20_avs_info.cpu_ts_bparam = 27856000;
		}
		else if( core_sidd >= core_sidd_n_min_th){
			core_avs =	CORE_AVS_N;
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}
		else{
			core_avs =	CORE_AVS_S;
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}
		/* caution: cpu avs is determined depending on core sidd */
		if( core_sidd >= cpu_sidd_ff_min_th){
			cpu_avs =  CPU_AVS_FF;
		}
		else if( core_sidd >= cpu_sidd_f_min_th){
			cpu_avs =  CPU_AVS_F;
		}
		else if( core_sidd >= cpu_sidd_n_min_th){
			cpu_avs =  CPU_AVS_N;
		}
		else{
			cpu_avs =  CPU_AVS_S;
		}
		/* o20 ignore kdrv  chip range , just use boot arg chip range */
		__pm_o20_set_vol(GPIO_AVS_CPU,o20_cpu_avs);
		__pm_o20_set_vol(GPIO_AVS_CORE,o20_core_avs);
		printk("O20 AVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype_o20[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_o20[core_avs],core_vidttype[core_avs],lx_chip_rev());

		return 0;
	}
	/* do avs using kdriver avs param */
	else if(o20_avsinfo)
	{
		/*  correct AVS infocase:  */
		core_sidd = o20_avsinfo & 0xffff;
		cpu_sidd  = (o20_avsinfo >> 16) & 0xffff;
		printk("O20 AVS avs info valid o20_avsinfo[%x] \n",o20_avsinfo);

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
		}
		else{
			__pm_o20_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_o20_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
			printk("O20 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
			,lx_chip_rev(),cpu_volttype_o20[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o20[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
			ret = pm_o20_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_o20[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			return ret;
		}

		/* core voltage table is different from cpu voltage table */
		if( core_sidd >= core_sidd_ff_min_th){
			core_avs =      CORE_AVS_FF;
			o20_avs_info.cpu_ts_aparam = 1221;
			o20_avs_info.cpu_ts_bparam = 27206000;
		}
		else if( core_sidd >= core_sidd_f_min_th){
			core_avs =      CORE_AVS_F;
			o20_avs_info.cpu_ts_aparam = 1240;
			o20_avs_info.cpu_ts_bparam = 27856000;
		}
		else if( core_sidd >= core_sidd_n_min_th){
			core_avs =      CORE_AVS_N;
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}
		else{
			core_avs =      CORE_AVS_S;
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}
		/* caution: cpu avs is determined depending on core sidd */
		if( core_sidd >= cpu_sidd_ff_min_th){
			cpu_avs =  CPU_AVS_FF;
		}
		else if( core_sidd >= cpu_sidd_f_min_th){
			cpu_avs =  CPU_AVS_F;
		}
		else if( core_sidd >= cpu_sidd_n_min_th){
			cpu_avs =  CPU_AVS_N;
		}
		else{
			cpu_avs =  CPU_AVS_S;
		}

		__pm_o20_set_vol(GPIO_AVS_CORE,core_avs );
		__pm_o20_set_vol(GPIO_AVS_CPU,cpu_avs );

		if(o20_avs_info.is_avshigh)
		{
			printk("O20 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_o20[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_high_o20[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}
		else
		{
			printk("O20 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_o20[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_o20[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}

		return 0;

	}
	/* skip avs */
	else{
		__pm_o20_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
		__pm_o20_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O20 AVS avs info is not valid, skipped! o20_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,o20_avsinfo,cpu_volttype_o20[CPU_AVS_S],core_volttype_o20[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}


int pm_o20_set_avs_force(UINT32 core_cpu, UINT32 type)
{

	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
	}
	else if (core_cpu == GPIO_AVS_CORE ){
		core_avs = type;
	}
	__pm_o20_set_vol(core_cpu,type);

	PM_NOTI("O20 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n"
	,cpu_avstype[cpu_avs],cpu_volttype_o20[cpu_avs],cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype_o20[core_avs],core_vidttype[core_avs]  );

	return 0;
}

int pm_o20_set_avs_in_resume(void)
{
	UINT32 core_sidd = 0, cpu_sidd = 0;
	if(o20_pms_tcorevol > 0 && o20_pms_tcorevol < VOUT_MAX )
	{
			pms_o20_work_t pms_work ;
			memset(&pms_work, 0x0, sizeof(pms_o20_work_t));
			pms_work.target_corevol = o20_pms_tcorevol;
			pms_work.do_avs = 1;
			pm_o20_func->run_regul(pms_work);
			printk("O20 AVS bootparam tcorev[%d]mV\n",pms_work.target_corevol );
			return 0;
	}
	else if((core_avs > 0) && (core_avs < CORE_AVS_INVALID_MAX) && (cpu_avs > 0) && (cpu_avs < O20_CPU_AVS_INVALID_MAX))
	{
		if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
		{

			GPIO_DevSetPinMux(O20_GPIO_AVS_CPU0, 1);
			GPIO_DevSetPinMux(O20_GPIO_AVS_CPU1, 1);

			/* FIXME: need to implementation using regulator */

			_GPIO_SetMode(O20_GPIO_AVS_CPU0, 1);
			_GPIO_SetMode(O20_GPIO_AVS_CPU1, 1);

		}
		else // GPIO_KERNEL_API
		{
			if (lx_chip_rev() >= LX_CHIP_REV(O20,B0)){
				_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU0_B0, 1);
				_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU1_B0, 1);
			}
			else if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
				_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU0, 1);
				_PM_GPIO_DevSetMode(O20_GPIO_AVS_CPU1, 1);
			}
		}

		if(o20_avsinfo)
		{
			/*	correct AVS info case:	*/
			core_sidd = o20_avsinfo & 0xffff;
			cpu_sidd  = (o20_avsinfo >> 16) & 0xffff;
		}
		__pm_o20_set_vol(GPIO_AVS_CPU,cpu_avs);
		__pm_o20_set_vol(GPIO_AVS_CORE,core_avs);

		PM_NOTI("O20 AVSRESUME cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n"
		,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th
		,core_sidd,core_avstype[core_avs],cpu_volttype_o20[cpu_avs],cpu_vidttype[cpu_avs],core_volttype_o20[core_avs],core_vidttype[core_avs],lx_chip_rev() );

	}


	return 0;
}

int pm_o20_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o20_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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

int o20_check_ts(void)
{
	int cpu_temp = 0, cpu_rem = 0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s) {

		/* OS_RdReg call ioremap which is restricted in soft isr */
		if(o20_cpu_ts_base != NULL) cpu_rawts = readl((void *)((uintptr_t)o20_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			o20_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)o20_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)o20_avs_info.cpu_ts_bparam );

			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem) ;

			if(cpu_rem > 50000)
				cpu_temp++;

			o20_avs_info.temperature = cpu_temp;

			if( o20_avs_info.ts_debug_enable )
			{
				PM_NOTI("------------------------------\n");
				PM_NOTI("O20 CPU TTEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
			}

			if(cpu_temp > o20_avs_info.avshigh_th)
			{
				if(o20_avs_info.is_avshigh == 0)
				{
					o20_avs_info.avshigh_count++;

					if(o20_avs_info.avshigh_count > 5 )
					{
						o20_avs_info.is_avshigh = 1;
						o20_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("O20 SET AVS HIGH: GPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						pm_o20_set_avs();
						return 1 ;
					}
				}

			}
		}

		ts_timer_count = 0;
	}
	return 0 ;
}

static int o20_pm_set_cpu_ts_aparam(unsigned int value)
{
	o20_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int o20_pm_set_cpu_ts_bparam(unsigned int value)
{
	o20_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int o20_pm_get_cpu_ts_aparam(void)
{
	return o20_avs_info.cpu_ts_aparam;
}

static unsigned int o20_pm_get_cpu_ts_bparam(void)
{
	return o20_avs_info.cpu_ts_bparam;
}

static int o20_pm_set_gpu_ts_aparam(unsigned int value)
{
	o20_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int o20_pm_set_gpu_ts_bparam(unsigned int value)
{
	o20_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int o20_pm_get_gpu_ts_aparam(void)
{
	return o20_avs_info.gpu_ts_aparam;
}

static unsigned int o20_pm_get_gpu_ts_bparam(void)
{
	return o20_avs_info.gpu_ts_bparam;
}

static int o20_pm_set_ts_debug_enable(unsigned int value)
{
	o20_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int o20_pm_get_ts_debug_enable(void)
{
	return o20_avs_info.ts_debug_enable;
}

static int o20_pm_get_temperature(void)
{
	int cpu_temp = 0, cpu_rem=0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;

	if(o20_cpu_ts_base != NULL)
	{
		cpu_rawts = readl((void *)((uintptr_t)o20_cpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			o20_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)o20_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)o20_avs_info.cpu_ts_bparam );
			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem);
			if(cpu_rem > 50000 )
				cpu_temp++;

			o20_avs_info.temperature = cpu_temp;
		}
	}
	return o20_avs_info.temperature;
}

void o20_AvsReInit(void)
{
	unsigned int val;

	if(o20_cpu_ts_base == NULL)		o20_cpu_ts_base = ioremap( 0xc9c21000, 0x18);

	//reg = readl(o20_cpu_ts_base);
	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, o20_cpu_ts_base);
}

void o20_AvsInit(void)
{
	unsigned int val;
	int ret;
	UINT32 core_sidd = 0, cpu_sidd = 0;
	//int tcnt = 0;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		/* do nothing */
	}
	else
	{
		/* need to be declared in kernel */
		if (lx_chip_rev() >= LX_CHIP_REV(O20,B0)){
			gpiod_add_lookup_table(&pm_gpio_table_b0);
		}
		else if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
			gpiod_add_lookup_table(&pm_gpio_table);
		}
	}

	#if 0
	/* need to fix regul_get fail*/
	if(o20_regulator == NULL)
	{
		while( o20_is_get == 0 && tcnt < O20_REGUL_GET_MAX  )
		{
			o20_regulator = regulator_get(NULL, "cpu0");
			if (IS_ERR(o20_regulator)) {
				msleep(1000);
				tcnt++;
				if( tcnt >= O20_REGUL_GET_MAX)
				{
					PM_ERROR("couldn't get cpu0 regulator regulator\n");
					break;
				}
			}
			else
			{
				PM_NOTI("regulator_init[%d]\n",tcnt);
				o20_is_get = 1;
				break;
			}
		}
	}
	#endif

	pm_o20_func = get_o20_pm_func();

	if(o20_cpu_ts_base == NULL)
		o20_cpu_ts_base = ioremap( 0xc9c21000, 0x18);

	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, o20_cpu_ts_base);

	/* cpu_ts_aparam, cpu_ts_bparam, gpu_ts_aparam, gpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -434(cpu_ts_bparam)  + 186(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */
	/* gpu temp =  -434(gpu_ts_bparam)  + 186(gpu_ts_aparam)*(TSADC_GPU_RAW_DATA) */

	o20_avs_info.cpu_ts_aparam = 1229;
	o20_avs_info.cpu_ts_bparam = 27510000;

	/* avs table is changed when gpu temp reach 80'c */

	o20_avs_info.avshigh_th = 80;
	o20_avs_info.is_avshigh = 0;
	o20_avs_info.avshigh_count = 0;

	o20_avs_info.ts_debug_enable = 0;
	o20_avs_info.HVT_cpu = o20_cpuHS >> 16 & 0xffff;
	o20_avs_info.SVT_cpu = o20_cpuHS & 0xffff;
	o20_avs_info.Nskew_cpu = o20_cpuNP >> 16 & 0xffff;
	o20_avs_info.Pskew_cpu = o20_cpuNP & 0xffff;

	o20_avs_info.HVT_gpu = o20_gpuHS >> 16 & 0xffff;
	o20_avs_info.SVT_gpu = o20_gpuHS & 0xffff;
	o20_avs_info.Nskew_gpu = o20_gpuNP >> 16 & 0xffff;
	o20_avs_info.Pskew_gpu = o20_gpuNP & 0xffff;
	//pm_o20_set_avs();
	if((o20_core_avs > 0) && (o20_core_avs < CORE_AVS_INVALID_MAX) &&
		(o20_cpu_avs > 0) && (o20_cpu_avs < O20_CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_sidd = o20_avsinfo & 0xffff;
		cpu_sidd  = (o20_avsinfo >> 16) & 0xffff;

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
		}
		else
		{
			core_sidd_fff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_o20[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;

		}

		if (lx_chip_rev() >= LX_CHIP_REV(O20,A0)){
			ret = pm_o20_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_o20[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ;
		}

		if( core_sidd >= core_sidd_ff_min_th){
			o20_avs_info.cpu_ts_aparam = 1221;
			o20_avs_info.cpu_ts_bparam = 27206000;
		}
		else if( core_sidd >= core_sidd_f_min_th){
			o20_avs_info.cpu_ts_aparam = 1240;
			o20_avs_info.cpu_ts_bparam = 27856000;
		}
		else if( core_sidd >= core_sidd_n_min_th){
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}
		else{
			o20_avs_info.cpu_ts_aparam = 1229;
			o20_avs_info.cpu_ts_bparam = 27510000;
		}


	}
}

static pms_o20_avs_t o20_pm_avs =
{
	.init = o20_AvsInit,
	.reinit = o20_AvsReInit,
	.set_avs = pm_o20_set_avs,
	.get_cpu_avs_type = pm_o20_get_cpu_avs,
	.get_cpu_avs_type_str = pm_o20_get_cpu_avs_str,
	.get_core_avs_type = pm_o20_get_core_avs,
	.get_core_avs_type_str = pm_o20_get_core_avs_str,
	.set_avs_in_resume = pm_o20_set_avs_in_resume,
	.set_avs_force = pm_o20_set_avs_force,
	.check_n_set = pm_o20_check_n_set,
	.ioctl = o20_pm_ioctl_avs,
	.check_ts = o20_check_ts,
	.get_cpu_ts_aparam = o20_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = o20_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = o20_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = o20_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = o20_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = o20_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = o20_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = o20_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = o20_pm_get_ts_debug_enable,
	.set_ts_debug_enable = o20_pm_set_ts_debug_enable,
	.get_temperature = o20_pm_get_temperature,

};

pms_o20_avs_t* get_o20_pm_avs(void)
{
	return &o20_pm_avs;
}


