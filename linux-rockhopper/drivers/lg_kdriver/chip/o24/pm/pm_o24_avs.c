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

#include "pm_o24common.h"

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


#define O24_GPIO_AVS_CPU0         21
#define O24_GPIO_AVS_CPU1         22

#define O24_GPIO_AVS_CPU0_B0         26
#define O24_GPIO_AVS_CPU1_B0         27


#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

#define O24_CORE_SIDD_FF_MAX_TH_AX  400	//mA
#define O24_CORE_SIDD_FF_MIN_TH_AX  160	//mA
#define O24_CORE_SIDD_F_MIN_TH_AX   90	//mA
#define O24_CORE_SIDD_N_MIN_TH_AX   50	//mA


/* caution: core sidd is used for cpu avs range */
#ifdef O24_AVS_SLT
#define O24_CPU_SIDD_FF_MAX_TH_AX  400	//mA
#define O24_CPU_SIDD_FF_MIN_TH_AX  120	//mA
#define O24_CPU_SIDD_F_MIN_TH_AX   80	//mA
#else

#define O24_CPU_SIDD_FF_MAX_TH_AX  400	//mA
#define O24_CPU_SIDD_FF_MIN_TH_AX  120	//mA
#define O24_CPU_SIDD_F_MIN_TH_AX   80	//mA

#endif

#define O24_CORE_SIDD_VALID_MIN     1 //mA
#define O24_CORE_SIDD_VALID_MAX     1000 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5

//#define O24_REGUL_GET_MAX		30
struct device o24_gpiodev =
{
	.init_name = "gpio_kerneltable",
};

struct gpio_desc *o24_cpuvid0 = NULL;
struct gpio_desc *o24_cpuvid1 = NULL;
struct gpio_desc *o24_gpio71 = NULL;

struct delayed_work o24_avs_cpu_dw;
struct delayed_work o24_avs_core_dw;
struct workqueue_struct *o24_avscputime_wq;
struct workqueue_struct *o24_avscoretime_wq;
struct workqueue_struct *o24_avscpu_wq;
struct workqueue_struct *o24_avscore_wq;

int o24_cpuwork_stage = 0;
int o24_cpuwork_target = 0;
int o24_corework_stage = 0;
int o24_corework_target = 0;
int o24_tempmax = 0;
/* high normal low verylow voltage */
static char * cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_o24[6] = { "XXX","1000","970","940", "910","xxx", };
static char * cpu_vidttype[6] = { "GPIO21[X]22[X]","GPIO21[out0]22[input]","GPIO21[input]22[out0]","GPIO21[input]22[input]","GPIO21[x]22[x]", };

static char * core_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * core_volttype_o24[6] = { "XXX","870","840","810", "770","xxx", };
char * core_volttype_high_o24[6] = { "XXX","870","840","810", "770","xxx", };
static char * core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

unsigned int core_avs_volt[6]= {870,870,840,810,770,870};

unsigned int core_avs_volt_sltlow[6]= {870,830,800,770,730,870};
unsigned int core_avs_volt_slthigh[6]= {870,910,880,850,810,870};

unsigned int cpu_avs_volt_sltnormal[6]= {1110,1110,1060,1010,1110,1110}; /* 1.4ghz */

unsigned int cpu_avs_volt_sltlow[6]= {1070,1030,980,930,1070,1070};     /* 1.4ghz */
unsigned int cpu_avs_volt_slthigh[6]= {1070,1110,1060,1010,1070,1070};  /* 1.4ghz */

unsigned int o24_avsinfo = 0;
unsigned int o24_cpu_avs = 0;
unsigned int o24_core_avs = 0;
static unsigned int o24_cpuHS = 0;
static unsigned int o24_cpuNP = 0;
static unsigned int o24_gpuHS = 0;
static unsigned int o24_gpuNP = 0;
extern int o24_pms_tcorevol;
extern int o24_is_prepared;

//static UINT32 core_avs= 0, cpu_avs = 0;

module_param(o24_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(o24_avsinfo, "o24_avsinfo");

module_param(o24_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o24_cpu_avs, "o24_cpu_avs");

module_param(o24_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o24_core_avs, "o24_core_avs");

module_param(o24_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o24_cpuHS, "o24_cpuHS");

module_param(o24_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o24_cpuNP, "o24_cpuNP");

module_param(o24_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o24_gpuHS, "o24_gpuHS");

module_param(o24_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o24_gpuNP, "o24_gpuNP");

static unsigned int cpu_sidd_ff_max_th;
static unsigned int cpu_sidd_ff_min_th;
static unsigned int cpu_sidd_f_min_th;

static unsigned int core_sidd_ff_max_th;
static unsigned int core_sidd_ff_min_th;
static unsigned int core_sidd_f_min_th;
static unsigned int core_sidd_n_min_th;

pms_o24_avsinto_t	o24_avs_info;

o24_sidd_t gSidd_check_table_o24[SIDD_CHECK_TABLE_NUM]={

	[SIDD_CHECK_TABLE_AX]={
		.cpu_sidd_ff_max = O24_CPU_SIDD_FF_MAX_TH_AX,
		.cpu_sidd_ff_min = O24_CPU_SIDD_FF_MIN_TH_AX,
		.cpu_sidd_f_min = O24_CPU_SIDD_F_MIN_TH_AX,

		.core_sidd_ff_max = O24_CORE_SIDD_FF_MAX_TH_AX,
		.core_sidd_ff_min = O24_CORE_SIDD_FF_MIN_TH_AX,
		.core_sidd_f_min = O24_CORE_SIDD_F_MIN_TH_AX,
		.core_sidd_n_min = O24_CORE_SIDD_N_MIN_TH_AX,

		.core_sidd_valid_max = O24_CORE_SIDD_VALID_MAX,
		.core_sidd_valid_min = O24_CORE_SIDD_VALID_MIN
	},
};

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/
extern int o24_SetCoreVal(unsigned int volt, unsigned int ch);
extern int o24_SetCpuVal(unsigned int volt, unsigned int ch);
extern int o24_SetCPUFreq(unsigned int freq);
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
struct gpio_desc *o24_sltgpiod = NULL;
static pms_o24_func_t* pm_o24_func = NULL;

/*========================================================================================
  Implementation Group
  ========================================================================================*/



#define TS_BIAS_OFFSET      (0x18)
#define TS_BIAS_DFT         (0x9EAA)

#define TS_MUX_ON           ( 1 << 29)

#define TS_SEL_CHOP         ( 1 << 15)
#define TS_SET_CLK          ( 1 << 9 )
#define TS_SEL_TRIM_DFT     (0x80)
#define TS_SEL_TRIM         ( TS_SEL_TRIM_DFT << 1)
#define TS_PDB              ( 1 << 0 )


unsigned int o24_freq_fix_by_ts = 1;
module_param(o24_freq_fix_by_ts, uint, S_IRUGO);
MODULE_PARM_DESC(o24_freq_fix_by_ts, "o24_freq_fix_by_ts");

unsigned int o24_freq_fix_ts_val = 130;
module_param(o24_freq_fix_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o24_freq_fix_ts_val, "o24_freq_fix_ts_val");

unsigned int o24_freq_normal_ts_val = 105;
module_param(o24_freq_normal_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o24_freq_normal_ts_val, "o24_freq_normal_ts_val");

unsigned int o24_hot_ts_val = 120;
module_param(o24_hot_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o24_hot_ts_val, "o24_hot_ts_val");

unsigned int o24_avs_enable = 1;
module_param(o24_avs_enable, uint, S_IRUGO);
MODULE_PARM_DESC(o24_avs_enable, "o24_avs_enable");
static unsigned int ts_timer_count = 0;

static unsigned int ts_timer_1s = 5;  //check with sampling rate
static unsigned int ts_timer_1s_count = 0;
int o24_slt_high = 0;
void __iomem *o24_ts_set_base = NULL;
void __iomem *o24_cpu_ts_base = NULL;
void __iomem *o24_slt_hl_base = NULL;

extern unsigned int o24_cur_freq;

static void o24_avs_cpuwork_req(void) /*o24_avs_cpuwork_func*/
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(o24_avscpu_wq,&o24_avs_cpu_dw,msecs_to_jiffies(O24_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(o24_avscpu_wq,&o24_avs_cpu_dw,msecs_to_jiffies(O24_AVS_STEP_DELAY));
	return;
}

static void o24_avs_corework_req(void) /*o24_avs_corework_func*/
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(o24_avscore_wq,&o24_avs_core_dw,msecs_to_jiffies(O24_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(o24_avscore_wq,&o24_avs_core_dw,msecs_to_jiffies(O24_AVS_STEP_DELAY));
	return;
}

void o24_avs_corework_func(struct work_struct *work)
{
	//struct regulator *coreregulator;
	int ret = 0;

	if(o24_is_prepared){
		PM_NOTI("SET CORE SKIP\n" );
		return;
	}

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o24_corework_target >= CORE_AVS_S && o24_corework_target <= CORE_AVS_FF){

			if(o24_slt_high)
			{
					if(o24_corework_stage == 3){
						PM_NOTI("SET CORE FF H\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_slthigh[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 2){
						PM_NOTI("SET CORE F H\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_slthigh[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 1){
						PM_NOTI("SET CORE N H\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_slthigh[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 0){
						PM_NOTI("SET CORE S H\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_slthigh[o24_corework_stage],0);
						goto coreavs_subwork;
					}
			}
			else
			{
					if(o24_corework_stage == 3){
						PM_NOTI("SET CORE FF L\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_sltlow[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 2){
						PM_NOTI("SET CORE F L\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_sltlow[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 1){
						PM_NOTI("SET CORE N L\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_sltlow[o24_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o24_corework_stage == 0){
						PM_NOTI("SET CORE S L\n" );
						o24_corework_stage++;
						o24_SetCoreVal(core_avs_volt_sltlow[o24_corework_stage],0);
						goto coreavs_subwork;
					}
			}
		}
		else{
			o24_corework_stage = 0;
			o24_corework_target = 0;
			goto end_coreavs_subowrk;
		}
	}
	else
	{
		if(o24_corework_target >= CORE_AVS_S && o24_corework_target <= CORE_AVS_FF){
			if(o24_corework_stage == 3){
				PM_NOTI("SET CORE FF\n" );
				o24_corework_stage++;
				o24_SetCoreVal(core_avs_volt[o24_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o24_corework_stage == 2){
				PM_NOTI("SET CORE F\n" );
				o24_corework_stage++;
				o24_SetCoreVal(core_avs_volt[o24_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o24_corework_stage == 1){
				PM_NOTI("SET CORE N\n" );
				o24_corework_stage++;
				o24_SetCoreVal(core_avs_volt[o24_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o24_corework_stage == 0){
				PM_NOTI("SET CORE S\n" );
				o24_corework_stage++;
				o24_SetCoreVal(core_avs_volt[o24_corework_stage],0);
				goto coreavs_subwork;
			}
		}
		else{
			o24_corework_stage = 0;
			o24_corework_target = 0;
			goto end_coreavs_subowrk;
		}

	}
coreavs_subwork:
	if(o24_corework_target != o24_corework_stage){
		o24_avs_corework_req();
	}
end_coreavs_subowrk:
	if(o24_corework_target == o24_corework_stage)
	{
		PM_NOTI("COREAVS[%d] [%d][%d]\n",ret,o24_corework_target,o24_corework_stage );
		o24_corework_stage = 0;
		o24_corework_target = 0;
	}
	if(o24_is_prepared)
		PM_NOTI("SET CORE SKIP\n" );
	return ;
}

void o24_avs_cpuwork_func(struct work_struct *work)
{
	int ret = 0;


	if(o24_is_prepared){
		PM_NOTI("SET CPU SKIP\n" );
		return;
	}

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o24_cpuwork_target >= CPU_AVS_S && o24_cpuwork_target <= CPU_AVS_FF){

			if(o24_slt_high)
			{
				if(o24_cpuwork_stage == 3){
					PM_NOTI("SET CPU FF H\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_slthigh[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 2){
					PM_NOTI("SET CPU F H\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_slthigh[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 1){
					PM_NOTI("SET CPU N H\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_slthigh[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 0){
					PM_NOTI("SET CPU S H\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_slthigh[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
			}
			else
			{
				if(o24_cpuwork_stage == 3){
					PM_NOTI("SET CPU FF L\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_sltlow[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 2){
					PM_NOTI("SET CPU F L\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_sltlow[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 1){
					PM_NOTI("SET CPU N L\n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_sltlow[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
				else if(o24_cpuwork_stage == 0){
					PM_NOTI("SET CPU S L \n" );
					o24_cpuwork_stage++;
					o24_SetCpuVal(cpu_avs_volt_sltlow[o24_cpuwork_stage],0);
					goto cpuavs_subwork;
				}
			}
		}
		else{
			PM_NOTI("SET CPU S\n" );

			o24_cpuwork_stage = 0;
			o24_cpuwork_target = 0;
			goto end_cpuavs_subowrk;
		}
	}
	else
	{
		if(o24_cpuwork_target >= CPU_AVS_S && o24_cpuwork_target <= CPU_AVS_FF){
			if(o24_cpuwork_stage == 3){
				PM_NOTI("SET CPU FF\n" );
				gpiod_direction_input(o24_cpuvid0);
				gpiod_direction_input(o24_cpuvid1);
				//gpiod_direction_input(o24_gpio71);
				gpiod_direction_output(o24_gpio71,0);
				o24_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o24_cpuwork_stage == 2){
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				gpiod_direction_input(o24_cpuvid0);
				PM_NOTI("SET CPU F\n" );
				o24_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o24_cpuwork_stage == 1){
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_input(o24_cpuvid1);
				//gpiod_direction_input(o24_gpio71);
				gpiod_direction_output(o24_gpio71,0);

				PM_NOTI("SET CPU N\n" );
				o24_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o24_cpuwork_stage == 0){
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);

				PM_NOTI("SET CPU S\n" );
				o24_cpuwork_stage++;
				goto cpuavs_subwork;
			}

		}
		else{
			gpiod_direction_output(o24_cpuvid0,0);
			gpiod_direction_output(o24_cpuvid1,0);
			//gpiod_direction_output(o24_gpio71,0);
			gpiod_direction_output(o24_gpio71,1);
			PM_NOTI("SET CPU S\n" );

			o24_cpuwork_stage = 0;
			o24_cpuwork_target = 0;
			goto end_cpuavs_subowrk;
		}
	}

cpuavs_subwork:
	if(o24_cpuwork_target != o24_cpuwork_stage){
		o24_avs_cpuwork_req();
	}
end_cpuavs_subowrk:
	if(o24_cpuwork_target == o24_cpuwork_stage)
	{
		PM_NOTI("CPUAVS[%d] [%d][%d]\n",ret,o24_cpuwork_target,o24_cpuwork_stage );
		o24_cpuwork_stage = 0;
		o24_cpuwork_target = 0;
	}
	if(o24_is_prepared)
		PM_NOTI("SET CPU SKIP\n" );
	return ;
}

int o24_set_cpu_vid( int level)
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		/* consider 1.4ghz top table volt */
		level = 1;

		if(o24_slt_high)
		{
			PM_NOTI("SET CPU 1.4 H avs[%d]\n",level );
			o24_SetCpuVal(cpu_avs_volt_slthigh[level],0);
		}
		else
		{
			PM_NOTI("SET CPU 1.4 L avs[%d]\n",level );
			o24_SetCpuVal(cpu_avs_volt_sltlow[level],0);
		}
	}
	else
	{
		switch(level)
		{
			case 1:
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				 break;
			case 2:
				gpiod_direction_output(o24_cpuvid0,0);
				gpiod_direction_input(o24_cpuvid1);
				//gpiod_direction_input(o24_gpio71);
				gpiod_direction_output(o24_gpio71,0);
				 break;

			case 3:
				gpiod_direction_output(o24_cpuvid1,0);
				//gpiod_direction_output(o24_gpio71,0);
				gpiod_direction_output(o24_gpio71,1);
				gpiod_direction_input(o24_cpuvid0);
				 break;
			case 4:
				gpiod_direction_input(o24_cpuvid0);
				gpiod_direction_input(o24_cpuvid1);
				//gpiod_direction_input(o24_gpio71);
				gpiod_direction_output(o24_gpio71,0);
				 break;
			default:
				//gpiod_direction_output(o24_cpuvid0,0);
				//gpiod_direction_output(o24_cpuvid1,0);
				 break;
		}

	}
	return 0;
}
struct regulator *o24_regulator = NULL;
struct regulator *o24_coreregulator = NULL;



/* cpuavs(regulator) is_step 0 run only in task*/
int __pm_o24_set_vol(UINT32 core_cpu, UINT32 type, UINT32 ch, UINT32 is_step)
{
	pms_o24_work_t pms_work ;

	memset(&pms_work, 0x0, sizeof(pms_o24_work_t));
	pm_o24_func = get_o24_pm_func();

	if ((is_step == 1) && (core_cpu == GPIO_AVS_CPU )){	/* set avs step  */
		o24_cpuwork_target = type;

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			o24_cpuwork_stage = 0;
		}
		else
		{
			if( type == CPU_AVS_S)
				o24_cpuwork_stage = 0;
			else
				o24_cpuwork_stage = 1;
		}

		queue_delayed_work(o24_avscpu_wq,&o24_avs_cpu_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 1) && core_cpu == I2C_AVS_CORE ){	/* set core avs: no step  */

		o24_corework_target = type;
		o24_corework_stage = 0;
		queue_delayed_work(o24_avscore_wq,&o24_avs_core_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CPU)){
		pms_work.target_vol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = 2;
		pm_o24_func->run_regul(&pms_work);
	}
	#if 0
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CORE )){
		pms_work.target_corevol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = 3;
		pm_o24_func->run_coreregul(&pms_work);
	}
	#endif

	return 0;
}


int pm_o24_check_sidd_valid( UINT32 core_siddl,  UINT32 cpu_siddl, o24_sidd_t * pSidd_check_table)
{
	int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_siddl >= core_sidd_valid_max || core_siddl <= core_sidd_valid_min) {
		//__pm_o24_set_vol(I2C_AVS_CORE,CORE_AVS_S, 0, 0);
		PM_ERROR("O24 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x] %d %d %d \n",cpu_volttype_o24[CPU_AVS_S],core_volttype_o24[CORE_AVS_S],lx_chip_rev(),core_siddl,core_sidd_valid_max,core_sidd_valid_min);
		return -1;
	}

	return 0;
}

int pm_o24_get_cpu_avs(pms_o24_avsinto_t * info)
{
	info->avstype = o24_cpu_avs;

	if(o24_avsinfo)
	{
		info->avscurrent = (o24_avsinfo >> 16 ) & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	return (int)o24_cpu_avs;
}
unsigned char * pm_o24_get_cpu_avs_str(void)
{
	return cpu_avstype[o24_cpu_avs];
}


int pm_o24_get_core_avs(pms_o24_avsinto_t * info)
{
	info->avstype = o24_core_avs;

	if(o24_avsinfo){
		info->avscurrent =  (o24_avsinfo) & 0xffff;

	}else{
		info->avscurrent = 0;
	}

	return (int)o24_core_avs;
}

unsigned char *  pm_o24_get_core_avs_str(void)
{
	return core_avstype[o24_core_avs];
}

int pm_o24_set_avs(void)/*avscputime*/
{
	int ret = -1;
	unsigned int core_siddl = 0, cpu_siddl = 0;

	if(o24_avs_enable == 0)
	{
		printk("O24 CPUAVS skipped\n");
		return 0;
	}

	/* do avs using o24_core_avs,o24_cpu_avs of bootargs */
	if((o24_cpu_avs > 0) && (o24_cpu_avs < O24_CPU_AVS_INVALID_MAX))
	{


		/*  correct AVS info case:  */
		core_siddl = o24_avsinfo & 0xffff;
		cpu_siddl  = (o24_avsinfo >> 16) & 0xffff;
		printk("O24 AVS info valid o24_avsinfo[%x] %d %d \n",o24_avsinfo,cpu_siddl,core_siddl);

		if (lx_chip_rev() >= LX_CHIP_REV(O24,A0) ){
			core_sidd_ff_max_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_max);
			core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
			core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_n_min);

			cpu_sidd_ff_max_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_max);
			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}
		else{
			__pm_o24_set_vol(GPIO_AVS_CPU,CPU_AVS_N,0,0);

			printk("O24 CPUAVS Kdriver lx_chip_rev[%x]  AVS cpu skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
					,lx_chip_rev(),cpu_volttype_o24[CPU_AVS_S],cpu_vidttype[CPU_AVS_S],core_volttype_o24[CORE_AVS_S],core_vidttype[CORE_AVS_S]);
			return -1;
		}


		if (lx_chip_rev() >= LX_CHIP_REV(O24,A0)){
			ret = pm_o24_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o24[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ret;
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			/* boot give 1.2ghz avs, change to 1.4ghz avs */
			if(o24_cpu_avs > 1)
				__pm_o24_set_vol(GPIO_AVS_CPU,o24_cpu_avs-1,0,1);
		}
		else
		{
			__pm_o24_set_vol(GPIO_AVS_CPU,o24_cpu_avs,0,1);
		}

		printk("O24 CPUAVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d]\n",
				cpu_avstype[o24_cpu_avs],core_avstype[o24_core_avs],cpu_volttype_o24[o24_cpu_avs],cpu_vidttype[o24_cpu_avs],
				core_volttype_o24[o24_core_avs],core_vidttype[o24_core_avs],lx_chip_rev(),o24_slt_high);

		return 0;
	}
	/* skip avs */
	else
	{
		__pm_o24_set_vol(GPIO_AVS_CPU,CPU_AVS_N, 0,0);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O24 boot CPUAVS avs info is not valid, skipped! o24_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
				,o24_avsinfo,cpu_volttype_o24[CPU_AVS_S],core_volttype_o24[CORE_AVS_S],lx_chip_rev() );
		return -1;
	}
}

int pm_o24_set_coreavs(void)/*avscoretime o24_avs_coretimework_func*/
{
	int ret = -1;
	unsigned int core_siddl = 0U, cpu_siddl = 0U;

	if(o24_avs_enable == 0)
	{
		printk("O24 COREAVS skipped\n");
		return 0;
	}

	if(o24_pms_tcorevol > 0 && o24_pms_tcorevol < VOUT_MAX )
	{

		pms_o24_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_o24_work_t));
		pms_work.target_corevol = (unsigned int)o24_pms_tcorevol;
		pms_work.do_avs = (UINT32)1;
		pms_work.ch = (UINT32)0;
		//pm_o24_func->run_coreregul(&pms_work);
		printk("O24 AVS bootparam tcorev[%d]mV cpu_avs[%d]\n",pms_work.target_corevol,o24_cpu_avs );

		return 0;
	}

	/* do avs using o24_core_avs,o24_cpu_avs of bootargs */
	else if((o24_core_avs > 0) && (o24_core_avs < ((UINT32)O24_CORE_AVS_INVALID_MAX)))
	{
		core_siddl = o24_avsinfo & ((UINT32)(0xffff));
		cpu_siddl  = (o24_avsinfo >> 16) & ((UINT32)0xffff);
		if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(O24,A0))){
			ret = pm_o24_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o24[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			{
				__pm_o24_set_vol(I2C_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)1);
				return ret;
			}
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			__pm_o24_set_vol(I2C_AVS_CORE,o24_core_avs,(UINT32)0, (UINT32)1);
		}
		else
		{
			__pm_o24_set_vol(I2C_AVS_CORE,o24_core_avs,(UINT32)0, (UINT32)1);
		}

		printk("O24 COREAVS  cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d] \n",
				cpu_avstype[o24_cpu_avs],core_avstype[o24_core_avs],cpu_volttype_o24[o24_cpu_avs],cpu_vidttype[o24_cpu_avs],
				core_volttype_o24[o24_core_avs],core_vidttype[o24_core_avs],lx_chip_rev(),o24_slt_high);

		return 0;
	}
	/* skip avs */
	else{

		__pm_o24_set_vol(GPIO_AVS_CORE,CORE_AVS_S,(UINT32)0, (UINT32)1);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O24 COREAVS avs info is not valid, skipped! o24_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
				,o24_avsinfo,cpu_volttype_o24[CPU_AVS_S],core_volttype_o24[CORE_AVS_S],lx_chip_rev() );
		return -1;
	}
}



int pm_o24_set_avs_force(UINT32 core_cpu, UINT32 type)
{
	UINT32 core_avs= 0, cpu_avs = 0;

#ifdef O24_AVS_SLT
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		//__pm_o24_set_vol(core_cpu,type, 0, 0);
	}
#else
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;

		__pm_o24_set_vol(core_cpu,type, 0, 1);
        PM_NOTI("O24 AVSFORCE cpu[%s][%s]V[%s] \n"
		    ,cpu_avstype[cpu_avs],cpu_volttype_o24[cpu_avs],cpu_vidttype[cpu_avs]);
	}
#endif
	if (core_cpu == I2C_AVS_CORE ){
		core_avs = type;
		__pm_o24_set_vol(core_cpu,type, 0, 1);
	}


	return 0;
}

int pm_o24_set_avs_in_resume(void)
{
	return 0;
}

int pm_o24_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o24_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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
#define MAX_TASADCVAL 	0x30000
extern unsigned int o24_kdrv_pm_runtime_suspend;
int o24_check_ts(void)
{
	int cpu_temp = 0, cpu_rem = 0;
	s64 cpu_tempa = 0;
	unsigned int cpu_rawts = 0;
	unsigned int check_rawts = 0;

	cpu_rawts = readl((void *)((uintptr_t)o24_cpu_ts_base + (uintptr_t)0x14) );
	check_rawts = cpu_rawts;

	ts_timer_count++;

	if (ts_timer_count >= ts_timer_1s)
	{
		if(o24_kdrv_pm_runtime_suspend || check_rawts > MAX_TASADCVAL)
		{
			writel(0, o24_ts_set_base);
			cpu_rawts = readl((void *)((uintptr_t)o24_cpu_ts_base + (uintptr_t)0x14) );
		}
		ts_timer_1s_count ++;

		if( cpu_rawts != 0 &&
			o24_avs_info.cpu_ts_aparam != 0 )
		{
			cpu_tempa = ( (s64)o24_avs_info.cpu_ts_aparam * (s64)cpu_rawts  - (s64)o24_avs_info.cpu_ts_bparam );

			cpu_temp = div_s64_rem(cpu_tempa,100000,&cpu_rem) ;

			if(cpu_rem > 50000)
				cpu_temp++;

			o24_avs_info.temperature = cpu_temp;

			if( cpu_temp > o24_tempmax)
				o24_tempmax = cpu_temp;


			if( o24_avs_info.ts_debug_enable )
			{
				PM_NOTI("O24 CPU TEMP[%d] MAXTEMP[%d] RAW[%d:%d:%d]\n",cpu_temp,o24_tempmax,cpu_rawts,o24_avs_info.is_avshigh,o24_cur_freq);
			}

			if(ts_timer_1s_count >= 5)
			{
				if( cpu_temp > o24_hot_ts_val)
					PM_NOTI("TEMP[%d] MAXTEMP[%d]\n",cpu_temp,o24_tempmax);
				ts_timer_1s_count = 0;
			}
		}

		if(o24_kdrv_pm_runtime_suspend || check_rawts > MAX_TASADCVAL)
		{
			writel(1, o24_ts_set_base);
		}

		if( o24_freq_fix_by_ts)
		{
			/* fix freq 1.2ghz at high temp 130 <= ts */
			if(cpu_temp >= o24_freq_fix_ts_val)
			{
				if(o24_avs_info.is_avshigh == 0)
				{
					pms_o24_work_t pms_o24_work;
					pm_o24_func = get_o24_pm_func();
					memset(&pms_o24_work, 0x0, sizeof(pms_o24_work_t));

					o24_avs_info.is_avshigh = 1;

					pms_o24_work.target_freq = 1200;
					pms_o24_work.do_dvfs = 1;
					pm_o24_func->run_clk(&pms_o24_work);
				}
			}
			/* sustain 105 <= ts  <130 */
			else if(cpu_temp >= o24_freq_normal_ts_val)
			{
				if(o24_cur_freq == 1400)
				{
					pms_o24_work_t pms_o24_work;
					pm_o24_func = get_o24_pm_func();
					memset(&pms_o24_work, 0x0, sizeof(pms_o24_work_t));
					pms_o24_work.target_freq = 1200;
					pms_o24_work.do_dvfs = 1;
					pm_o24_func->run_clk(&pms_o24_work);

				}
			}
			/* normal ts  <105 */
			else
			{
				if(o24_avs_info.is_avshigh == 1)
				{
					o24_avs_info.is_avshigh = 0;
				}
			}
		}

		ts_timer_count = 0;
	}
	return 0 ;
}

static int o24_pm_set_cpu_ts_aparam(unsigned int value)
{
	o24_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int o24_pm_set_cpu_ts_bparam(unsigned int value)
{
	o24_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int o24_pm_get_cpu_ts_aparam(void)
{
	return o24_avs_info.cpu_ts_aparam;
}

static unsigned int o24_pm_get_cpu_ts_bparam(void)
{
	return o24_avs_info.cpu_ts_bparam;
}

static int o24_pm_set_gpu_ts_aparam(unsigned int value)
{
	o24_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int o24_pm_set_gpu_ts_bparam(unsigned int value)
{
	o24_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int o24_pm_get_gpu_ts_aparam(void)
{
	return o24_avs_info.gpu_ts_aparam;
}

static unsigned int o24_pm_get_gpu_ts_bparam(void)
{
	return o24_avs_info.gpu_ts_bparam;
}

static int o24_pm_set_ts_debug_enable(unsigned int value)
{
	o24_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int o24_pm_get_ts_debug_enable(void)
{
	return o24_avs_info.ts_debug_enable;
}

static int o24_pm_get_temperature(void)
{
	return o24_avs_info.temperature;
}

static unsigned int o24_pm_get_high_ts(void)
{
	return o24_avs_info.is_avshigh;
}

void o24_AvsReInit(void)
{
	unsigned int val;

	o24_avs_info.is_avshigh = 0U;
	if(o24_cpu_ts_base != NULL)
	{
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(o24_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));

		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, o24_cpu_ts_base );
		mdelay(2);
		PM_NOTI("O24 TSADC set [%d]\n",val);

	}
}

void o24_AvsInit(void)
{
	int ret;
	unsigned int core_siddl = 0, cpu_siddl = 0;
	unsigned int val = 0;

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o24_slt_hl_base == NULL)
			o24_slt_hl_base = ioremap( 0xcec82118, 0x4);

		/* gpio 141 mux enable not set by pinctrl  */
		val = readl(o24_slt_hl_base );
		val &= (~0xf0000000);
		val |= 0x10000000;
		writel(val, o24_slt_hl_base );

		/* gpio 141 is used for slt low volt low high volt:high */
		o24_sltgpiod = gpiod_get(&o24_gpiodev, "141", GPIOD_ASIS);

		if (IS_ERR(o24_sltgpiod))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",141,o24_sltgpiod);
			return ;
		}
		val = gpiod_get_value(o24_sltgpiod);

		/* temp slt code */
		if(val == 1)
			o24_slt_high = 0;
		else if(val == 0)
			o24_slt_high = 1;

		gpiod_put(o24_sltgpiod);
		PM_NOTI("o24_is_sltmode[%d]\n",o24_slt_high);
		o24_cur_freq = 0; /*for setting*/
		o24_SetCPUFreq(1400);
		PM_NOTI("freq change 1400\n");
	}

	pm_o24_func = get_o24_pm_func();

	/* gpio 21 22 */
	o24_cpuvid0 = gpiod_get(&o24_gpiodev, "21", GPIOD_ASIS);
	if (IS_ERR(o24_cpuvid0))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",21,o24_cpuvid0);
    }
	o24_cpuvid1 = gpiod_get(&o24_gpiodev, "22", GPIOD_ASIS);
	if (IS_ERR(o24_cpuvid1))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",22,o24_cpuvid0);
    }
	o24_gpio71 = gpiod_get(&o24_gpiodev, "71", GPIOD_ASIS);
	if (IS_ERR(o24_gpio71))
	{
		PM_ERROR("unable to get gpio desc[%d:%p]\n",71,o24_gpio71);
    }


	if(o24_cpu_ts_base == NULL)
		o24_cpu_ts_base = ioremap( 0xcc6a3000, 0x18);
	if(o24_ts_set_base == NULL)
		o24_ts_set_base = ioremap( 0xCC60001C, 0x4);
	if(o24_cpu_ts_base != NULL)
	{
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(o24_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));

		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, o24_cpu_ts_base );
		mdelay(2);
		PM_NOTI("O24 TSADC set [%d]\n",val);
	}
	/* cpu_ts_aparam, cpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -341.60(cpu_ts_bparam)  + 0.01510(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */

	o24_avs_info.cpu_ts_aparam = 1510;
	o24_avs_info.cpu_ts_bparam = 34160000;

	/* avs table is changed when gpu temp reach 80'c */

	o24_avs_info.avshigh_th = o24_freq_fix_ts_val;
	o24_avs_info.is_avshigh = 0;
	o24_avs_info.avshigh_count = 0;

	o24_avs_info.ts_debug_enable = 0;
	o24_avs_info.HVT_cpu = o24_cpuHS >> 16 & 0xffff;
	o24_avs_info.SVT_cpu = o24_cpuHS & 0xffff;
	o24_avs_info.Nskew_cpu = o24_cpuNP >> 16 & 0xffff;
	o24_avs_info.Pskew_cpu = o24_cpuNP & 0xffff;

	o24_avs_info.HVT_gpu = o24_gpuHS >> 16 & 0xffff;
	o24_avs_info.SVT_gpu = o24_gpuHS & 0xffff;
	o24_avs_info.Nskew_gpu = o24_gpuNP >> 16 & 0xffff;
	o24_avs_info.Pskew_gpu = o24_gpuNP & 0xffff;

	if((o24_core_avs > 0) && (o24_core_avs < O24_CORE_AVS_INVALID_MAX) &&
			(o24_cpu_avs > 0) && (o24_cpu_avs < O24_CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_siddl = o24_avsinfo & 0xffff;
		cpu_siddl  = (o24_avsinfo >> 16) & 0xffff;

		if (lx_chip_rev() >= LX_CHIP_REV(O24,A0) ){
			core_sidd_ff_max_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_max);
			core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
			core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_n_min);

			cpu_sidd_ff_max_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_max);
			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}
		else
		{
			core_sidd_ff_max_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_max);
			core_sidd_ff_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_ff_min);
			core_sidd_f_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_f_min);
			core_sidd_n_min_th = (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].core_sidd_n_min);

			cpu_sidd_ff_max_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_max);
			cpu_sidd_ff_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_ff_min);
			cpu_sidd_f_min_th =  (unsigned int)(gSidd_check_table_o24[SIDD_CHECK_TABLE_AX].cpu_sidd_f_min);
		}

		if (lx_chip_rev() >= LX_CHIP_REV(O24,A0)){
			ret = pm_o24_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o24[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ;
		}
	}
}

static pms_o24_avs_t o24_pm_avs =
{
	.init = o24_AvsInit,
	.reinit = o24_AvsReInit,
	.set_avs = pm_o24_set_avs,
	.set_coreavs = pm_o24_set_coreavs,
	.get_cpu_avs_type = pm_o24_get_cpu_avs,
	.get_cpu_avs_type_str = pm_o24_get_cpu_avs_str,
	.get_core_avs_type = pm_o24_get_core_avs,
	.get_core_avs_type_str = pm_o24_get_core_avs_str,
	.set_avs_in_resume = pm_o24_set_avs_in_resume,
	.set_avs_force = pm_o24_set_avs_force,
	.check_n_set = pm_o24_check_n_set,
	.ioctl = o24_pm_ioctl_avs,
	.check_ts = o24_check_ts,
	.get_cpu_ts_aparam = o24_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = o24_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = o24_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = o24_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = o24_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = o24_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = o24_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = o24_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = o24_pm_get_ts_debug_enable,
	.set_ts_debug_enable = o24_pm_set_ts_debug_enable,
	.get_temperature = o24_pm_get_temperature,
	.get_high_ts = o24_pm_get_high_ts,

};

pms_o24_avs_t* get_o24_pm_avs(void)
{
	return &o24_pm_avs;
}


