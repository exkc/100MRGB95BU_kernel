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
#include "os_util.h"

#include "gpio_core.h"

#include "pm_o18common.h"

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

#define O18_GPIO_AVS_CPU0         9
#define O18_GPIO_AVS_CPU1         10

#define CORE_AVS_INVALID_MAX   6  /* invalid max */
#define CORE_AVS_FFF 5   /* ffast */
#define CORE_AVS_FF 4   /* ffast */
#define CORE_AVS_F 3    /* fast */
#define CORE_AVS_N 2    /* normal */
#define CORE_AVS_S 1    /* slow */
#define CORE_AVS_X 0    /* not determined */

#define CPU_AVS_INVALID_MAX   5  /* invalid max */
#define CPU_AVS_FF 4    /* ffast */
#define CPU_AVS_F 3     /* fast */
#define CPU_AVS_N 2     /* normal */
#define CPU_AVS_S 1     /* slow */
#define CPU_AVS_X 0     /* not determined */

#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

#define O18_CORE_SIDD_FFF_MIN_TH_AX  211     //mA
#define O18_CORE_SIDD_FF_MIN_TH_AX  160     //mA
#define O18_CORE_SIDD_F_MIN_TH_AX   130     //mA
#define O18_CORE_SIDD_N_MIN_TH_AX   103      //mA

/* caution: core sidd is used for cpu avs range */
#define O18_CPU_SIDD_FF_MIN_TH_AX   221     //mA
#define O18_CPU_SIDD_F_MIN_TH_AX    191     //mA
#define O18_CPU_SIDD_N_MIN_TH_AX    161      //mA

#define O18_CORE_SIDD_VALID_MIN     10 //mA
#define O18_CORE_SIDD_VALID_MAX     500 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5

/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_o18[6] = { "XXX","1.10","1.00","0.97", "0.93","0.93", };
static char * cpu_vidttype[6] = { "GPIO 9[1] 10[1]","GPIO 9[1] 10[1]","GPIO 9[1] 10[0]","GPIO 9[0] 10[1]","GPIO 9[0] 10[0]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_o18[6] = { "XXX","0.94","0.92","0.90", "0.88","0.86", };
char * core_volttype_high_o18[6] = { "XXX","0.92","0.90","0.87", "0.85","0.84", };
static char * core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

static unsigned int o18_avsinfo = 0;
static unsigned int o18_cpu_avs = 0;
static unsigned int o18_core_avs = 0;
static unsigned int o18_cpuHS = 0;
static unsigned int o18_cpuNP = 0;
static unsigned int o18_gpuHS = 0;
static unsigned int o18_gpuNP = 0;
extern int o18_pms_tcorevol;

static UINT32 core_avs= 0, cpu_avs = 0;

module_param(o18_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(o18_avsinfo, "o18_avsinfo");

module_param(o18_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o18_cpu_avs, "o18_cpu_avs");

module_param(o18_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o18_core_avs, "o18_core_avs");

module_param(o18_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o18_cpuHS, "o18_cpuHS");

module_param(o18_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o18_cpuNP, "o18_cpuNP");

module_param(o18_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o18_gpuHS, "o18_gpuHS");

module_param(o18_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o18_gpuNP, "o18_gpuNP");

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
pms_o18_avsinto_t	o18_avs_info;

o18_sidd_t gSidd_check_table_o18[SIDD_CHECK_TABLE_NUM]={

        [SIDD_CHECK_TABLE_AX]={
        .cpu_sidd_ff_min = O18_CPU_SIDD_FF_MIN_TH_AX,
        .cpu_sidd_f_min = O18_CPU_SIDD_F_MIN_TH_AX,
        .cpu_sidd_n_min = O18_CPU_SIDD_N_MIN_TH_AX,

        .core_sidd_fff_min = O18_CORE_SIDD_FFF_MIN_TH_AX,
        .core_sidd_ff_min = O18_CORE_SIDD_FF_MIN_TH_AX,
        .core_sidd_f_min = O18_CORE_SIDD_F_MIN_TH_AX,
        .core_sidd_n_min = O18_CORE_SIDD_N_MIN_TH_AX,

		.core_sidd_valid_max = O18_CORE_SIDD_VALID_MAX,
		.core_sidd_valid_min = O18_CORE_SIDD_VALID_MIN
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
static pms_o18_func_t* pm_o18_func = NULL;

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

void __iomem *cpu_ts_base = NULL;
void __iomem *gpu_ts_base = NULL;

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

//END GPIO_KERNEL_API

int __pm_o18_set_vol(UINT32 core_cpu, UINT32 type)
{

	pms_o18_work_t pms_work ;

	memset(&pms_work, 0x0, sizeof(pms_o18_work_t));
	pm_o18_func = get_o18_pm_func();

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		if (core_cpu == GPIO_AVS_CPU ){

			switch(type){
				case CPU_AVS_S:
					//HV
					_GPIO_SetValue(O18_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O18_GPIO_AVS_CPU1,1);
					break;
				case CPU_AVS_N:
					//MV
					_GPIO_SetValue(O18_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O18_GPIO_AVS_CPU1,0);
					break;
				case CPU_AVS_F:
					//LV
					_GPIO_SetValue(O18_GPIO_AVS_CPU1,1);
					_GPIO_SetValue(O18_GPIO_AVS_CPU0,0);
					break;
				case CPU_AVS_FF:
					//VLV
					_GPIO_SetValue(O18_GPIO_AVS_CPU0,0);
					_GPIO_SetValue(O18_GPIO_AVS_CPU1,0);
					break;
				default:
					//HV
					_GPIO_SetValue(O18_GPIO_AVS_CPU0,1);
					_GPIO_SetValue(O18_GPIO_AVS_CPU1,1);
					break;
			}
		}
		else if (core_cpu == GPIO_AVS_CORE && o18_avs_info.is_avshigh == 0){

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
			pm_o18_func->run_regul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && o18_avs_info.is_avshigh == 1){

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
			pm_o18_func->run_regul(pms_work);
		}
	}
	else // GPIO_KERNEL_API
	{
		static struct regulator *regulator;
		int ret,prevMV;

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
					break;
				case CPU_AVS_N:
					//MV
					ret = regulator_set_voltage(regulator, CPU_AVS_N_UV,CPU_AVS_N_UV);
					break;
				case CPU_AVS_F:
					//LV
					ret = regulator_set_voltage(regulator, CPU_AVS_F_UV,CPU_AVS_F_UV);
					break;
				case CPU_AVS_FF:
					//VLV
					ret = regulator_set_voltage(regulator, CPU_AVS_FF_UV,CPU_AVS_FF_UV);

					break;
				default:
					//HV
					ret = regulator_set_voltage(regulator, CPU_AVS_S_UV,CPU_AVS_S_UV);
					break;
			}
			PM_ERROR("cpu ret[%d] mV[%d] => mV[%d]\n",ret,prevMV,regulator_get_voltage(regulator) );
			regulator_put(regulator);
		}
		else if (core_cpu == GPIO_AVS_CORE && o18_avs_info.is_avshigh == 0 ){

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
			pm_o18_func->run_regul(pms_work);
		}
		else if (core_cpu == GPIO_AVS_CORE && o18_avs_info.is_avshigh == 1 ){
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
			pm_o18_func->run_regul(pms_work);
		}
	}

	return 0;
}


int pm_o18_check_sidd_valid( UINT32 core_sidd,  UINT32 cpu_sidd, o18_sidd_t * pSidd_check_table)
{
	 int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	 int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_sidd > core_sidd_valid_max || core_sidd < core_sidd_valid_min) {
		__pm_o18_set_vol(GPIO_AVS_CPU,CPU_AVS_S );
		__pm_o18_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
		 PM_ERROR("O18 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x]\n",cpu_volttype_o18[CPU_AVS_S],core_volttype_o18[CORE_AVS_S],lx_chip_rev());
		return -1;
	}

	return 0;
}

int pm_o18_get_cpu_avs(pms_o18_avsinto_t * info)
{
	info->avstype = cpu_avs;

	if(o18_avsinfo)
	{
		info->avscurrent = o18_avsinfo & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	info->HVT_cpu = o18_cpuHS >> 16 & 0xffff;
	info->SVT_cpu = o18_cpuHS & 0xffff;
	info->Nskew_cpu = o18_cpuNP >> 16 & 0xffff;
	info->Pskew_cpu = o18_cpuNP & 0xffff;
	info->HVT_gpu = o18_gpuHS >> 16 & 0xffff;
	info->SVT_gpu = o18_gpuHS & 0xffff;
	info->Nskew_gpu = o18_gpuNP >> 16 & 0xffff;
	info->Pskew_gpu = o18_gpuNP & 0xffff;

	return (int)cpu_avs;
}
unsigned char * pm_o18_get_cpu_avs_str(void)
{
	return cpu_avstype[cpu_avs];
}


int pm_o18_get_core_avs(pms_o18_avsinto_t * info)
{
	info->avstype = core_avs;

	if(o18_avsinfo)
	{
		info->avscurrent =  (o18_avsinfo >> 16) & 0xffff;

	}else
	{
		info->avscurrent = 0;
	}

	return (int)core_avs;
}

unsigned char *  pm_o18_get_core_avs_str(void)
{
		return core_avstype[core_avs];
}

int pm_o18_set_avs(void)
{
	int ret = -1;
	UINT32 core_sidd = 0, cpu_sidd = 0;
	UINT32 mask = 0, value = 0;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		GPIO_DevSetPinMux(O18_GPIO_AVS_CPU0, 1);
		GPIO_DevSetPinMux(O18_GPIO_AVS_CPU1, 1);

		/* FIXME: need to implementation using regulator */

		_GPIO_SetMode(O18_GPIO_AVS_CPU0, 1);
		_GPIO_SetMode(O18_GPIO_AVS_CPU1, 1);
	}
	else // GPIO_KERNEL_API
	{
		/* GPIO_DevSetPinMux is not working in GPIO_KERNEL_API */
		/* gpio9 mux enable */
		value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
		mask = 1 << 21 ;
		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);

		/* gpio10 mux enable */
		value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0x84);
		mask = 1 << 8;
		value &= (~mask);
		CTOP_CTRL_O18A0_WRITE(CTOP_DPE,0x84,value);

		_PM_GPIO_DevSetMode(O18_GPIO_AVS_CPU0, 1);
		_PM_GPIO_DevSetMode(O18_GPIO_AVS_CPU1, 1);
	}


	if(o18_pms_tcorevol > 0 && o18_pms_tcorevol < VOUT_MAX )
	{

		pms_o18_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_o18_work_t));
		pms_work.target_corevol = o18_pms_tcorevol;
		pms_work.do_avs = 1;
		pm_o18_func->run_regul(pms_work);
		printk("O18 AVS bootparam tcorev[%d]mV\n",pms_work.target_corevol );
		return 0;
	}

	/* do avs using o18_core_avs,o18_cpu_avs of bootargs */
	else if((o18_core_avs > 0) && (o18_core_avs < CORE_AVS_INVALID_MAX) &&
		(o18_cpu_avs > 0) && (o18_cpu_avs < CPU_AVS_INVALID_MAX))
	{
		/* store avs info to suspend resume */
		cpu_avs = o18_cpu_avs;
		core_avs = o18_core_avs;

		__pm_o18_set_vol(GPIO_AVS_CPU,o18_cpu_avs);
		__pm_o18_set_vol(GPIO_AVS_CORE,o18_core_avs);
		printk("O18 AVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_avstype[cpu_avs],core_avstype[core_avs],cpu_volttype_o18[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_o18[core_avs],core_vidttype[core_avs],lx_chip_rev());

		return 0;
	}

	/* do avs using kdriver avs param */
	else if(o18_avsinfo)
	{
		/*  correct AVS info case:  */
		cpu_sidd = o18_avsinfo & 0xffff;
		core_sidd  = (o18_avsinfo >> 16) & 0xffff;
		printk("O18 AVS avs info valid o18_avsinfo[%x] \n",o18_avsinfo);

		if (lx_chip_rev() >= LX_CHIP_REV(O18,A0) ){
			core_sidd_fff_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].core_sidd_fff_min;
			core_sidd_ff_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_ff_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].core_sidd_ff_min;
			core_sidd_f_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].core_sidd_f_min;
			core_sidd_n_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].core_sidd_n_min;

			cpu_sidd_ff_min_th =  gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min;
			cpu_sidd_f_min_th =  gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min;
			cpu_sidd_n_min_th = gSidd_check_table_o18[SIDD_CHECK_TABLE_AX].cpu_sidd_n_min;;
		}
		else{
			__pm_o18_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
			__pm_o18_set_vol(GPIO_AVS_CORE,CORE_AVS_S);
			printk("O18 AVS Kdriver lx_chip_rev[%x]  AVS skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
			,lx_chip_rev(),cpu_volttype_o18[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o18[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(O18,A0)){
			ret = pm_o18_check_sidd_valid(core_sidd, cpu_sidd, &gSidd_check_table_o18[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			return ret;
		}

		/* core voltage table is different from cpu voltage table */
		if( core_sidd >= core_sidd_fff_min_th){
				core_avs =	CORE_AVS_FFF;
		}
		else if( core_sidd >= core_sidd_ff_min_th){
				core_avs =	CORE_AVS_FF;
		}
		else if( core_sidd >= core_sidd_f_min_th){
				core_avs =	CORE_AVS_F;
		}
		else if( core_sidd >= core_sidd_n_min_th){
				core_avs =	CORE_AVS_N;
		}
		else{
				core_avs =	CORE_AVS_S;
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

		__pm_o18_set_vol(GPIO_AVS_CORE,core_avs );
		__pm_o18_set_vol(GPIO_AVS_CPU,cpu_avs );

		if(o18_avs_info.is_avshigh)
		{
			printk("O18 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_o18[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_high_o18[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}
		else
		{
			printk("O18 AVS cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] \n",
			cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,
			cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th,
			core_sidd,core_avstype[core_avs],cpu_volttype_o18[cpu_avs],cpu_vidttype[cpu_avs],
			core_volttype_o18[core_avs],core_vidttype[core_avs],lx_chip_rev());
		}

		return 0;

	}
	/* skip avs */
	else{
		__pm_o18_set_vol(GPIO_AVS_CPU,CPU_AVS_S);
		__pm_o18_set_vol(GPIO_AVS_CORE,CORE_AVS_S );
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O18 AVS avs info is not valid, skipped! o18_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
		,o18_avsinfo,cpu_volttype_o18[CPU_AVS_S],core_volttype_o18[CORE_AVS_S],lx_chip_rev() );
		return -1;
     }
}


int pm_o18_set_avs_force(UINT32 core_cpu, UINT32 type)
{

	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
	}
	else if (core_cpu == GPIO_AVS_CORE ){
		core_avs = type;
	}
	__pm_o18_set_vol(core_cpu,type);

	PM_NOTI("O18 AVSFORCE cpu[%s][%s]V[%s] core[%s][%s]V[%s] \n"
	,cpu_avstype[cpu_avs],cpu_volttype_o18[cpu_avs],cpu_vidttype[cpu_avs],core_avstype[core_avs],core_volttype_o18[core_avs],core_vidttype[core_avs]  );

	return 0;
}

int pm_o18_set_avs_in_resume(void)
{
	UINT32 core_sidd = 0, cpu_sidd = 0;
	UINT32 mask = 0, value = 0;
	if(o18_pms_tcorevol > 0 && o18_pms_tcorevol < VOUT_MAX )
	{
			pms_o18_work_t pms_work ;
			memset(&pms_work, 0x0, sizeof(pms_o18_work_t));
			pms_work.target_corevol = o18_pms_tcorevol;
			pms_work.do_avs = 1;
			pm_o18_func->run_regul(pms_work);
			printk("O18 AVS bootparam tcorev[%d]mV\n",pms_work.target_corevol );
			return 0;
	}
	else if((core_avs > 0) && (core_avs < CORE_AVS_INVALID_MAX) && (cpu_avs > 0) && (cpu_avs < CPU_AVS_INVALID_MAX))
	{
		if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
		{

			GPIO_DevSetPinMux(O18_GPIO_AVS_CPU0, 1);
			GPIO_DevSetPinMux(O18_GPIO_AVS_CPU1, 1);

			/* FIXME: need to implementation using regulator */

			_GPIO_SetMode(O18_GPIO_AVS_CPU0, 1);
			_GPIO_SetMode(O18_GPIO_AVS_CPU1, 1);

		}
		else // GPIO_KERNEL_API
		{
			/* GPIO_DevSetPinMux is not working in GPIO_KERNEL_API */
			/* gpio9 mux enable */
			value = CTOP_CTRL_O18A0_READ(CTOP_ND0,0x10);
			mask = 1 << 21 ;
			value &= (~mask);
			CTOP_CTRL_O18A0_WRITE(CTOP_ND0,0x10,value);

			/* gpio10 mux enable */
			value = CTOP_CTRL_O18A0_READ(CTOP_DPE,0x84);
			mask = 1 << 8;
			value &= (~mask);
			CTOP_CTRL_O18A0_WRITE(CTOP_DPE,0x84,value);

			_PM_GPIO_DevSetMode(O18_GPIO_AVS_CPU0, 1);
			_PM_GPIO_DevSetMode(O18_GPIO_AVS_CPU1, 1);
		}

		if(o18_avsinfo)
		{
			/*	correct AVS info case:	*/
			cpu_sidd = o18_avsinfo & 0xffff;
			core_sidd  = (o18_avsinfo >> 16) & 0xffff;
		}
		__pm_o18_set_vol(GPIO_AVS_CPU,cpu_avs);
		__pm_o18_set_vol(GPIO_AVS_CORE,core_avs);

		PM_NOTI("O18 AVSRESUME cpu_sidd[%d:%d|%d][%dmA:%s] core_sidd[%d:%d:%d][%dmA:%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x]\n"
		,cpu_sidd_n_min_th,cpu_sidd_f_min_th,cpu_sidd_ff_min_th,cpu_sidd,cpu_avstype[cpu_avs],core_sidd_n_min_th,core_sidd_f_min_th,core_sidd_ff_min_th
		,core_sidd,core_avstype[core_avs],cpu_volttype_o18[cpu_avs],cpu_vidttype[cpu_avs],core_volttype_o18[core_avs],core_vidttype[core_avs],lx_chip_rev() );

	}


	return 0;
}

int pm_o18_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o18_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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

int o18_check_ts(void)
{
	int cpu_temp = 0, cpu_tempa = 0,gpu_temp = 0, gpu_tempa = 0;
	unsigned int cpu_rawts = 0, gpu_rawts = 0;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_count_1s) {

		/* OS_RdReg call ioremap which is restricted in soft isr */
		if(cpu_ts_base != NULL) cpu_rawts = readl((void *)((uintptr_t)cpu_ts_base + (uintptr_t)0x14) );
		if(gpu_ts_base != NULL) gpu_rawts = readl((void *)((uintptr_t)gpu_ts_base + (uintptr_t)0x14) );

		if( cpu_rawts != 0 &&
			o18_avs_info.cpu_ts_aparam != 0  &&
			gpu_rawts != 0 &&
			o18_avs_info.gpu_ts_aparam != 0 )
		{
			cpu_tempa = (o18_avs_info.cpu_ts_aparam * cpu_rawts) / 10000;
			gpu_tempa = (o18_avs_info.gpu_ts_aparam * gpu_rawts) / 10000;

			cpu_temp = cpu_tempa - o18_avs_info.cpu_ts_bparam ;
			gpu_temp = gpu_tempa - o18_avs_info.gpu_ts_bparam ;

			o18_avs_info.temperature = cpu_temp;

			if( o18_avs_info.ts_debug_enable )
			{
				PM_NOTI("------------------------------\n");
				PM_NOTI("O18 CPU TEMP[%d]'C  RAW[%d]\n",cpu_temp,cpu_rawts);
				PM_NOTI("O18 GPU TEMP[%d]'C  RAW[%d]\n",gpu_temp,gpu_rawts);
			}

			if(gpu_temp > o18_avs_info.avshigh_th)
			{
				if(o18_avs_info.is_avshigh == 0)
				{
					o18_avs_info.avshigh_count++;

					if(o18_avs_info.avshigh_count > 5 )
					{
						o18_avs_info.is_avshigh = 1;
						o18_avs_info.avshigh_count = 0;
						PM_NOTI("---------------------------------------------\n");
						PM_NOTI("O18 SET AVS HIGH: GPU TEMP[%d]'C  RAW[%d]\n",gpu_temp,gpu_rawts);
						PM_NOTI("---------------------------------------------\n");
						pm_o18_set_avs();
						return 1 ;
					}
				}

			}
		}

		ts_timer_count = 0;
	}
	return 0 ;
}

static int o18_pm_set_cpu_ts_aparam(unsigned int value)
{
	o18_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int o18_pm_set_cpu_ts_bparam(unsigned int value)
{
	o18_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int o18_pm_get_cpu_ts_aparam(void)
{
	return o18_avs_info.cpu_ts_aparam;
}

static unsigned int o18_pm_get_cpu_ts_bparam(void)
{
	return o18_avs_info.cpu_ts_bparam;
}

static int o18_pm_set_gpu_ts_aparam(unsigned int value)
{
	o18_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int o18_pm_set_gpu_ts_bparam(unsigned int value)
{
	o18_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int o18_pm_get_gpu_ts_aparam(void)
{
	return o18_avs_info.gpu_ts_aparam;
}

static unsigned int o18_pm_get_gpu_ts_bparam(void)
{
	return o18_avs_info.gpu_ts_bparam;
}

static int o18_pm_set_ts_debug_enable(unsigned int value)
{
	o18_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int o18_pm_get_ts_debug_enable(void)
{
	return o18_avs_info.ts_debug_enable;
}

static unsigned int o18_pm_get_temperature(void)
{
	return o18_avs_info.temperature;
}

void o18_AvsReInit(void)
{
	unsigned int val;

	if(cpu_ts_base == NULL)		cpu_ts_base = ioremap( 0xc5ff0400, 0x18);
	if(gpu_ts_base == NULL)		gpu_ts_base = ioremap( 0xc97c9800, 0x18);

	//reg = readl(cpu_ts_base);
	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, cpu_ts_base);

	//reg = readl(gpu_ts_base);
	val = GPU_TS_RAW_INTR_EN | GPU_TS_EN;
	writel(val, gpu_ts_base);

}

void o18_AvsInit(void)
{
	unsigned int val;

	if(lx_gpio_cfg() & LX_GPIO_CFG_LEGACY_MODE)
	{
		/* do nothing */
	}
	else
	{
		/* need to be declared in kernel */
		gpiod_add_lookup_table(&pm_gpio_table);
	}

	pm_o18_func = get_o18_pm_func();

	if(cpu_ts_base == NULL)
		cpu_ts_base = ioremap( 0xc5ff0400, 0x18);
	if(gpu_ts_base == NULL)
		gpu_ts_base = ioremap( 0xc97c9800, 0x18);

	val = CPU_TS_RAW_INTR_EN | CPU_TS_EN;
	writel(val, cpu_ts_base);
	val = GPU_TS_RAW_INTR_EN | GPU_TS_EN;
	writel(val, gpu_ts_base);

	/* cpu_ts_aparam, cpu_ts_bparam, gpu_ts_aparam, gpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -434(cpu_ts_bparam)  + 186(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */
	/* gpu temp =  -434(gpu_ts_bparam)  + 186(gpu_ts_aparam)*(TSADC_GPU_RAW_DATA) */

	o18_avs_info.cpu_ts_aparam = 186;
	o18_avs_info.cpu_ts_bparam = 434;
	o18_avs_info.gpu_ts_aparam = 176;
	o18_avs_info.gpu_ts_bparam = 404;

	/* avs table is changed when gpu temp reach 80'c */

	o18_avs_info.avshigh_th = 80;
	o18_avs_info.is_avshigh = 0;
	o18_avs_info.avshigh_count = 0;

	o18_avs_info.ts_debug_enable = 0;
	o18_avs_info.HVT_cpu = o18_cpuHS >> 16 & 0xffff;
	o18_avs_info.SVT_cpu = o18_cpuHS & 0xffff;
	o18_avs_info.Nskew_cpu = o18_cpuNP >> 16 & 0xffff;
	o18_avs_info.Pskew_cpu = o18_cpuNP & 0xffff;

	o18_avs_info.HVT_gpu = o18_gpuHS >> 16 & 0xffff;
	o18_avs_info.SVT_gpu = o18_gpuHS & 0xffff;
	o18_avs_info.Nskew_gpu = o18_gpuNP >> 16 & 0xffff;
	o18_avs_info.Pskew_gpu = o18_gpuNP & 0xffff;
	//pm_o18_set_avs();
}

static pms_o18_avs_t o18_pm_avs =
{
	.init = o18_AvsInit,
	.reinit = o18_AvsReInit,
	.set_avs = pm_o18_set_avs,
	.get_cpu_avs_type = pm_o18_get_cpu_avs,
	.get_cpu_avs_type_str = pm_o18_get_cpu_avs_str,
	.get_core_avs_type = pm_o18_get_core_avs,
	.get_core_avs_type_str = pm_o18_get_core_avs_str,
	.set_avs_in_resume = pm_o18_set_avs_in_resume,
	.set_avs_force = pm_o18_set_avs_force,
	.check_n_set = pm_o18_check_n_set,
	.ioctl = o18_pm_ioctl_avs,
	.check_ts = o18_check_ts,
	.get_cpu_ts_aparam = o18_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = o18_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = o18_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = o18_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = o18_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = o18_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = o18_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = o18_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = o18_pm_get_ts_debug_enable,
	.set_ts_debug_enable = o18_pm_set_ts_debug_enable,
	.get_temperature = o18_pm_get_temperature,

};

pms_o18_avs_t* get_o18_pm_avs(void)
{
	return &o18_pm_avs;
}


