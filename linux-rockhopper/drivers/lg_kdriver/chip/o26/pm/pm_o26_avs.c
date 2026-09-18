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

#include "pm_o26common.h"

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


#define O26_GPIO_AVS_CPU0         21
#define O26_GPIO_AVS_CPU1         22

#define O26_GPIO_AVS_CPU0_B0         26
#define O26_GPIO_AVS_CPU1_B0         27


#define SIDD_CHECK_TABLE_AX     0
#define SIDD_CHECK_TABLE_BX     1
#define SIDD_CHECK_TABLE_NUM    5

//#define O26_CORE_SIDD_FF_MAX_TH_AX  400	//mA
#define O26_CORE_SIDD_FF_MIN_TH_AX  150	//mA
#define O26_CORE_SIDD_F_MIN_TH_AX   100	//mA
#define O26_CORE_SIDD_N_MIN_TH_AX   40	//mA


/* caution: core sidd is used for cpu avs range */
#ifdef O26_AVS_SLT
#define O26_CPU_SIDD_FF_MAX_TH_AX  70	//mA
#define O26_CPU_SIDD_FF_MIN_TH_AX  70	//mA
#define O26_CPU_SIDD_F_MIN_TH_AX  30	//mA
#define O26_CPU_SIDD_N_MIN_TH_AX   30	//mA
#else

#define O26_CPU_SIDD_FF_MAX_TH_AX  70	//mA
#define O26_CPU_SIDD_FF_MIN_TH_AX  70	//mA
#define O26_CPU_SIDD_F_MIN_TH_AX  30	//mA
#define O26_CPU_SIDD_N_MIN_TH_AX  30	//mA

#endif

#define O26_CORE_SIDD_VALID_MIN     1 //mA
#define O26_CORE_SIDD_VALID_MAX     1000 //mA

#define SIDD_CHECK_TABLE_AX	0
#define SIDD_CHECK_TABLE_BX	1
#define SIDD_CHECK_TABLE_NUM	5

//#define O26_REGUL_GET_MAX		30
struct device o26_gpiodev =
{
	.init_name = "gpio_kerneltable",
};

struct gpio_desc *o26_cpuvid0 = NULL;
struct gpio_desc *o26_cpuvid1 = NULL;

struct delayed_work o26_avs_cpu_dw;
struct delayed_work o26_avs_core_dw;
struct workqueue_struct *o26_avscputime_wq;
struct workqueue_struct *o26_avscoretime_wq;
struct workqueue_struct *o26_avscpu_wq;
struct workqueue_struct *o26_avscore_wq;

int o26_cpuwork_stage = 0;
int o26_cpuwork_target = 0;
int o26_corework_stage = 0;
int o26_corework_target = 0;
int o26_tempmax = 0;
/* high normal low verylow voltage */
static char * o26_cpu_avstype[6] = { "XXX","SLOW","NORMAL","FAST", "FFAST","FFF", };
char * cpu_volttype_o26[6] = { "XXX","920","890","860", "830","xxx", };
char * cpu_volttype_o26_sltlow[6] = { "XXX","880","850","820", "790","xxx", };
char * cpu_volttype_o26_slthigh[6] = { "XXX","960","930","900", "870","xxx", };
static char * o26_cpu_vidttype[6] = { "swgpio19[X]20[X]","swgpio19[out0]20[out0]","swgpio19[input]20[out0]","swgpio19[input]20[input]","swgpio19[x]20[x]", };

static char * o26_core_avstype[6] = { "XXX","SSLOW","SLOW","NORMAL","FAST", "FFAST", };
char * core_volttype_o26[6] = { "XXX","830","800","760","730", "710", };
char * core_volttype_high_o26[6] = { "XXX","810","780","740","710", "690", };

char * core_volttype_o26_sltlow[6] = { "XXX","770","770","700","670", "650",};
char * core_volttype_o26_slthigh[6] = { "XXX","870","870","800","770", "750", };

static char * o26_core_vidttype[6] = { "regul","regul","regul","regul","regul","regul",};

unsigned int o26_core_avs_volt[6]= {830,830,800,760,730,710};
unsigned int o26_core_avs_highvolt[6]= {810,810,780,740,710,690};

unsigned int o26_core_avs_volt_sltlow[6]= {770,770,740,700,670,650};
unsigned int o26_core_avs_volt_slthigh[6]= {870,870,840,800,770,750};

unsigned int o26_cpu_avs_volt_sltnormal[6]= {1110,1110,1060,1010,1110,1110}; /* 1.4ghz */

unsigned int o26_cpu_avs_volt_sltlow[6]= {880,880,850,820,790,880};     /* 1.4ghz */
unsigned int o26_cpu_avs_volt_slthigh[6]= {960,960,930,900,870,960};  /* 1.4ghz */

unsigned int o26_avsinfo = 0;
unsigned int o26_cpu_avs = 0;
unsigned int o26_core_avs = 0;
static unsigned int o26_cpuHS = 0;
static unsigned int o26_cpuNP = 0;
static unsigned int o26_gpuHS = 0;
static unsigned int o26_gpuNP = 0;
extern int o26_pms_tcorevol;
extern int o26_is_prepared;

//static UINT32 core_avs= 0, cpu_avs = 0;

module_param(o26_avsinfo, uint, S_IRUGO);
MODULE_PARM_DESC(o26_avsinfo, "o26_avsinfo");

module_param(o26_cpu_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o26_cpu_avs, "o26_cpu_avs");

module_param(o26_core_avs, uint, S_IRUGO);
MODULE_PARM_DESC(o26_core_avs, "o26_core_avs");

module_param(o26_cpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o26_cpuHS, "o26_cpuHS");

module_param(o26_cpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o26_cpuNP, "o26_cpuNP");

module_param(o26_gpuHS, uint, S_IRUGO);
MODULE_PARM_DESC(o26_gpuHS, "o26_gpuHS");

module_param(o26_gpuNP, uint, S_IRUGO);
MODULE_PARM_DESC(o26_gpuNP, "o26_gpuNP");

unsigned int o26_freq_change_cnt = 2;
module_param(o26_freq_change_cnt, uint, S_IRUGO);
MODULE_PARM_DESC(o26_freq_change_cnt, "o26_freq_change_cnt");

unsigned int o26_freq_delayms = 500;
module_param(o26_freq_delayms, uint, S_IRUGO);
MODULE_PARM_DESC(o26_freq_delayms, "o26_freq_delayms");

#if 0
static unsigned int cpu_sidd_ff_max_th;
static unsigned int cpu_sidd_ff_min_th;
static unsigned int cpu_sidd_f_min_th;

static unsigned int core_sidd_ff_max_th;
static unsigned int core_sidd_ff_min_th;
static unsigned int core_sidd_f_min_th;
static unsigned int core_sidd_n_min_th;
#endif

pms_o26_avsinto_t	o26_avs_info;

o26_sidd_t gSidd_check_table_o26[SIDD_CHECK_TABLE_NUM]={

	[SIDD_CHECK_TABLE_AX]={
		.cpu_sidd_ff_max = O26_CPU_SIDD_FF_MAX_TH_AX,
		.cpu_sidd_ff_min = O26_CPU_SIDD_FF_MIN_TH_AX,
		.cpu_sidd_f_min = O26_CPU_SIDD_F_MIN_TH_AX,

		//.core_sidd_ff_max = O26_CORE_SIDD_FF_MAX_TH_AX,
		.core_sidd_ff_min = O26_CORE_SIDD_FF_MIN_TH_AX,
		.core_sidd_f_min = O26_CORE_SIDD_F_MIN_TH_AX,
		.core_sidd_n_min = O26_CORE_SIDD_N_MIN_TH_AX,

		.core_sidd_valid_max = O26_CORE_SIDD_VALID_MAX,
		.core_sidd_valid_min = O26_CORE_SIDD_VALID_MIN
	},
};

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/
extern int o26_SetCoreVal(unsigned int volt, unsigned int ch);
extern int o26_SetCpuVal(unsigned int volt, unsigned int ch);
extern int o26_SetCPUFreq(unsigned int freq);
/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  global Functions
  ---------------------------------------------------------------------------------------*/
void o26_avs_corework_func(struct work_struct *work);
void o26_avs_cpuwork_func(struct work_struct *work);
int o26_set_cpu_vid_slt(int freq);
int o26_set_cpu_vid( int level);
int __pm_o26_set_vol(UINT32 core_cpu, UINT32 type, UINT32 ch, UINT32 is_step);
int pm_o26_check_sidd_valid( UINT32 core_siddl,  UINT32 cpu_siddl, o26_sidd_t * pSidd_check_table);
int pm_o26_get_cpu_avs(pms_o26_avsinto_t * info);
int pm_o26_get_core_avs(pms_o26_avsinto_t * info);
int pm_o26_set_avs_force(UINT32 core_cpu, UINT32 type);
int pm_o26_set_avs_in_resume(void);
int pm_o26_check_n_set(void);
int o26_pm_ioctl_avs (unsigned int cmd, unsigned long arg);
int o26_check_ts(void);
void o26_AvsReInit(void);
void o26_AvsInit(void);
int o26_set_avsinit_ext(void);
int pm_o26_set_avs(void);/*avscputime*/
int pm_o26_set_coreavs(void);/*avscoretime o26_avs_coretimework_func*/

unsigned char * pm_o26_get_cpu_avs_str(void);
unsigned char *  pm_o26_get_core_avs_str(void);
int pm_o26_get_cpu_avs(pms_o26_avsinto_t * info);
int pm_o26_get_core_avs(pms_o26_avsinto_t * info);

/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
struct gpio_desc *o26_sltgpiod = NULL;
static pms_o26_func_t* pm_o26_func = NULL;

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


unsigned int o26_change_avs_by_ts = 1;
module_param(o26_change_avs_by_ts, uint, S_IRUGO);
MODULE_PARM_DESC(o26_change_avs_by_ts, "o26_change_avs_by_ts");

unsigned int o26_high_ts_val = 50;
module_param(o26_high_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o26_high_ts_val, "o26_high_ts_val");

unsigned int o26_normal_ts_val = 20;
module_param(o26_normal_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o26_normal_ts_val, "o26_normal_ts_val");

unsigned int o26_hot_ts_val = 120;
module_param(o26_hot_ts_val, uint, S_IRUGO);
MODULE_PARM_DESC(o26_hot_ts_val, "o26_hot_ts_val");

unsigned int o26_avs_enable = 1;
module_param(o26_avs_enable, uint, S_IRUGO);
MODULE_PARM_DESC(o26_avs_enable, "o26_avs_enable");
static unsigned int ts_timer_count = 0;

static unsigned int ts_timer_1s = 5;  //check with sampling rate
static unsigned int ts_timer_1s_count = 0;
int o26_slt_high = 0;
//void __iomem *o26_ts_set_base = NULL;
void __iomem *o26_cpu_ts_base = NULL;
#if 0
void __iomem *o26_slt_hl_base = NULL;
#endif

extern unsigned int o26_cur_freq;

static void o26_avs_cpuwork_req(void) /*o26_avs_cpuwork_func*/
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(o26_avscpu_wq,&o26_avs_cpu_dw,msecs_to_jiffies(O26_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(o26_avscpu_wq,&o26_avs_cpu_dw,msecs_to_jiffies(O26_AVS_STEP_DELAY));
	return;
}

static void o26_avs_corework_req(void) /*o26_avs_corework_func*/
{
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
		queue_delayed_work(o26_avscore_wq,&o26_avs_core_dw,msecs_to_jiffies(O26_AVS_STEP_DELAY_SLT));
	else
		queue_delayed_work(o26_avscore_wq,&o26_avs_core_dw,msecs_to_jiffies(O26_AVS_STEP_DELAY));
	return;
}

void o26_avs_corework_func(struct work_struct *work)
{
	//struct regulator *coreregulator;
	int ret = 0;

	if(o26_is_prepared){
		PM_NOTI("SET CORE SKIP\n" );
		return;
	}

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o26_corework_target >= O26_CORE_AVS_SS && o26_corework_target <= O26_CORE_AVS_FF){

			if(o26_slt_high)
			{
					if(o26_corework_stage == 4){
						PM_NOTI("SET CORE FF H\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_slthigh[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 3){
						PM_NOTI("SET CORE F H\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_slthigh[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 2){
						PM_NOTI("SET CORE N H\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_slthigh[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 1){
						PM_NOTI("SET CORE S H\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_slthigh[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 0){
						PM_NOTI("SET CORE SS H\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_slthigh[o26_corework_stage],0);
						goto coreavs_subwork;
					}
			}
			else
			{
					if(o26_corework_stage == 4){
						PM_NOTI("SET CORE FF L\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_sltlow[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 3){
						PM_NOTI("SET CORE F L\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_sltlow[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 2){
						PM_NOTI("SET CORE N L\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_sltlow[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 1){
						PM_NOTI("SET CORE S L\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_sltlow[o26_corework_stage],0);
						goto coreavs_subwork;
					}
					else if(o26_corework_stage == 0){
						PM_NOTI("SET CORE SS L\n" );
						o26_corework_stage++;
						o26_SetCoreVal(o26_core_avs_volt_sltlow[o26_corework_stage],0);
						goto coreavs_subwork;
					}
			}
		}
		else{
			o26_corework_stage = 0;
			o26_corework_target = 0;
			goto end_coreavs_subowrk;
		}
	}
	else
	{
		if(o26_corework_target >= O26_CORE_AVS_SS && o26_corework_target <= O26_CORE_AVS_FF){
			if(o26_corework_stage == 4){
				PM_NOTI("SET CORE FF\n");
				o26_corework_stage++;
				PM_NOTI("[%d]\n", o26_core_avs_volt[o26_corework_stage] );
				o26_SetCoreVal(o26_core_avs_volt[o26_corework_stage],0);
				goto coreavs_subwork;
			}
			if(o26_corework_stage == 3){
				PM_NOTI("SET CORE F\n");
				o26_corework_stage++;
				PM_NOTI("[%d]\n", o26_core_avs_volt[o26_corework_stage] );
				o26_SetCoreVal(o26_core_avs_volt[o26_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o26_corework_stage == 2){
				PM_NOTI("SET CORE N\n" );
				o26_corework_stage++;
				o26_SetCoreVal(o26_core_avs_volt[o26_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o26_corework_stage == 1){
				PM_NOTI("SET CORE S\n" );
				o26_corework_stage++;
				o26_SetCoreVal(o26_core_avs_volt[o26_corework_stage],0);
				goto coreavs_subwork;
			}
			else if(o26_corework_stage == 0){
				PM_NOTI("SET CORE SS\n");
				o26_corework_stage++;
				PM_NOTI("[%d]\n", o26_core_avs_volt[o26_corework_stage] );
				o26_SetCoreVal(o26_core_avs_volt[o26_corework_stage],0);
				goto coreavs_subwork;
			}
		}
		else{
			o26_corework_stage = 0;
			o26_corework_target = 0;
			goto end_coreavs_subowrk;
		}

	}
coreavs_subwork:
	if(o26_corework_target != o26_corework_stage){
		o26_avs_corework_req();
	}
end_coreavs_subowrk:
	if(o26_corework_target == o26_corework_stage)
	{
		PM_NOTI("COREAVS[%d] [%d][%d]\n",ret,o26_corework_target,o26_corework_stage );
		o26_corework_stage = 0;
		o26_corework_target = 0;
	}
	if(o26_is_prepared)
		PM_NOTI("SET CORE SKIP\n" );
	return ;
}

void o26_avs_cpuwork_func(struct work_struct *work)
{
	int ret = 0;


	if(o26_is_prepared){
		PM_NOTI("SET CPU SKIP\n" );
		return;
	}

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		if(o26_cpuwork_target >= CPU_AVS_S && o26_cpuwork_target <= CPU_AVS_FF){

			if(o26_slt_high)
			{
				if(o26_cpuwork_stage == 3){
					PM_NOTI("SET CPU FF H\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_slthigh[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 2){
					PM_NOTI("SET CPU F H\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_slthigh[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 1){
					PM_NOTI("SET CPU N H\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_slthigh[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 0){
					PM_NOTI("SET CPU S H\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_slthigh[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
			}
			else
			{
				if(o26_cpuwork_stage == 3){
					PM_NOTI("SET CPU FF L\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_sltlow[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 2){
					PM_NOTI("SET CPU F L\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_sltlow[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 1){
					PM_NOTI("SET CPU N L\n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_sltlow[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
				else if(o26_cpuwork_stage == 0){
					PM_NOTI("SET CPU S L \n" );
					o26_cpuwork_stage++;
					o26_SetCpuVal(o26_cpu_avs_volt_sltlow[o26_cpuwork_stage],1);
					goto cpuavs_subwork;
				}
			}
		}
		else{
			PM_NOTI("SET CPU S\n" );

			o26_cpuwork_stage = 0;
			o26_cpuwork_target = 0;
			goto end_cpuavs_subowrk;
		}
	}
	else
	{
		if(o26_cpuwork_target >= CPU_AVS_S && o26_cpuwork_target <= CPU_AVS_FF){
			if(o26_cpuwork_stage == 3){
				PM_NOTI("SET CPU FF\n" );
				gpiod_direction_input(o26_cpuvid0);
				gpiod_direction_input(o26_cpuvid1);
				o26_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o26_cpuwork_stage == 2){
				gpiod_direction_output(o26_cpuvid1,0);
				gpiod_direction_input(o26_cpuvid0);
				PM_NOTI("SET CPU F\n" );
				o26_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o26_cpuwork_stage == 1){
				gpiod_direction_output(o26_cpuvid0,0);
				gpiod_direction_input(o26_cpuvid1);

				PM_NOTI("SET CPU N\n" );
				o26_cpuwork_stage++;
				goto cpuavs_subwork;
			}
			else if(o26_cpuwork_stage == 0){
				gpiod_direction_output(o26_cpuvid0,0);
				gpiod_direction_output(o26_cpuvid1,0);

				PM_NOTI("SET CPU S\n" );
				o26_cpuwork_stage++;
				goto cpuavs_subwork;
			}

		}
		else{
			gpiod_direction_output(o26_cpuvid0,0);
			gpiod_direction_output(o26_cpuvid1,0);
			PM_NOTI("SET CPU S\n" );

			o26_cpuwork_stage = 0;
			o26_cpuwork_target = 0;
			goto end_cpuavs_subowrk;
		}
	}

cpuavs_subwork:
	if(o26_cpuwork_target != o26_cpuwork_stage){
		o26_avs_cpuwork_req();
	}
end_cpuavs_subowrk:
	if(o26_cpuwork_target == o26_cpuwork_stage)
	{
		PM_NOTI("CPUAVS[%d] [%d][%d]\n",ret,o26_cpuwork_target,o26_cpuwork_stage );
		o26_cpuwork_stage = 0;
		o26_cpuwork_target = 0;
	}
	if(o26_is_prepared)
		PM_NOTI("SET CPU SKIP\n" );
	return ;
}

int o26_set_cpu_vid_slt(int freq)
{
	if(freq == 1400)
	{
		/* consider 1.4ghz top table volt */
		if(o26_slt_high)
		{
			o26_SetCpuVal(o26_cpu_avs_volt_slthigh[1],0);
		}
		else
		{
			o26_SetCpuVal(o26_cpu_avs_volt_sltlow[1],0);
		}
	}
	else if(freq == 1200)
	{
		/* consider 1.2ghz top table volt */
		if(o26_slt_high)
		{
			o26_SetCpuVal(o26_cpu_avs_volt_slthigh[2],0);
		}
		else
		{
			o26_SetCpuVal(o26_cpu_avs_volt_sltlow[2],0);
		}

	}
	return 0;
}

int o26_set_cpu_vid( int level)
{
	switch(level)
	{
		case 4:
			gpiod_direction_input(o26_cpuvid0);
			gpiod_direction_input(o26_cpuvid1);
			 break;
		case 3:
			gpiod_direction_output(o26_cpuvid1,0);
			gpiod_direction_input(o26_cpuvid0);
			 break;
		case 2:
			gpiod_direction_output(o26_cpuvid0,0);
			gpiod_direction_input(o26_cpuvid1);
			 break;
		case 1:
			gpiod_direction_output(o26_cpuvid0,0);
			gpiod_direction_output(o26_cpuvid1,0);
			 break;
		default:
			//gpiod_direction_output(o26_cpuvid0,0);
			//gpiod_direction_output(o26_cpuvid1,0);
			 break;
	}

	return 0;
}
struct regulator *o26_regulator = NULL;
struct regulator *o26_coreregulator = NULL;



/* cpuavs(regulator) is_step 0 run only in task*/
int __pm_o26_set_vol(UINT32 core_cpu, UINT32 type, UINT32 ch, UINT32 is_step)
{
	pms_o26_work_t pms_work ;

	memset(&pms_work, 0x0, sizeof(pms_o26_work_t));
	pm_o26_func = get_o26_pm_func();

	if ((is_step == 1) && (core_cpu == GPIO_AVS_CPU )){	/* set avs step  */
		o26_cpuwork_target = type;

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			o26_cpuwork_stage = 0;
		}
		else
		{
			#if 0
			if( type == CPU_AVS_S)
				o26_cpuwork_stage = 0;
			else
				o26_cpuwork_stage = 1;
			#endif
			o26_cpuwork_stage = 0;
		}

		queue_delayed_work(o26_avscpu_wq,&o26_avs_cpu_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 1) && core_cpu == I2C_AVS_CORE ){	/* set core avs: no step  */

		o26_corework_target = type;
		o26_corework_stage = 0;
		queue_delayed_work(o26_avscore_wq,&o26_avs_core_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 1) && core_cpu == I2C_AVS_CPU ){	/* set core avs: no step  */

		o26_cpuwork_target = type;
		o26_cpuwork_stage = 0;
		queue_delayed_work(o26_avscpu_wq,&o26_avs_cpu_dw, msecs_to_jiffies(1));
	}
	else if ((is_step == 0) && (core_cpu == GPIO_AVS_CPU)){
		pms_work.target_vol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = GPIO_AVS_CPU;
		pm_o26_func->run_regul(&pms_work);
	}
	else if ((is_step == 0) && (core_cpu == I2C_AVS_CPU )){
		pms_work.target_vol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = I2C_AVS_CPU;
		pm_o26_func->run_coreregul(&pms_work);
	}
	else if ((is_step == 0) && (core_cpu == I2C_AVS_CORE )){
		pms_work.target_corevol = (UINT32)type;
		pms_work.ch = ch;
		pms_work.do_avs = I2C_AVS_CORE;
		pm_o26_func->run_coreregul(&pms_work);
	}

	return 0;
}


int pm_o26_check_sidd_valid( UINT32 core_siddl,  UINT32 cpu_siddl, o26_sidd_t * pSidd_check_table)
{
	int core_sidd_valid_max = pSidd_check_table->core_sidd_valid_max;
	int core_sidd_valid_min = pSidd_check_table->core_sidd_valid_min;

	if(core_siddl >= core_sidd_valid_max || core_siddl <= core_sidd_valid_min) {
		//__pm_o26_set_vol(I2C_AVS_CORE,O26_CORE_AVS_SS, 0, 0);
		PM_ERROR("O26 AVS not valid sidd skipped! cpu[%s]V core[%s]V chip[%x] %d %d %d \n",cpu_volttype_o26[CPU_AVS_S],core_volttype_o26[O26_CORE_AVS_SS],lx_chip_rev(),core_siddl,core_sidd_valid_max,core_sidd_valid_min);
		return -1;
	}

	return 0;
}

int pm_o26_get_cpu_avs(pms_o26_avsinto_t * info)
{
	info->avstype = o26_cpu_avs;

	if(o26_avsinfo)
	{
		info->avscurrent = (o26_avsinfo >> 16 ) & 0xffff;
	}
	else
	{
		info->avscurrent = 0;
	}
	return (int)o26_cpu_avs;
}
unsigned char * pm_o26_get_cpu_avs_str(void)
{
	return o26_cpu_avstype[o26_cpu_avs];
}


int pm_o26_get_core_avs(pms_o26_avsinto_t * info)
{
	info->avstype = o26_core_avs;

	if(o26_avsinfo){
		info->avscurrent =  (o26_avsinfo) & 0xffff;

	}else{
		info->avscurrent = 0;
	}

	return (int)o26_core_avs;
}

unsigned char *  pm_o26_get_core_avs_str(void)
{
	return o26_core_avstype[o26_core_avs];
}

int pm_o26_set_avs(void)/*avscputime*/
{
	int ret = -1;
	unsigned int core_siddl = 0, cpu_siddl = 0;

	if(o26_avs_enable == 0)
	{
		printk("O26 CPUAVS skipped\n");
		return 0;
	}

	/* do avs using o26_core_avs,o26_cpu_avs of bootargs */
	if((o26_cpu_avs > 0) && (o26_cpu_avs < O26_CPU_AVS_INVALID_MAX))
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O24,A0) ){
			/*  correct AVS info case:  */
			core_siddl = o26_avsinfo & 0xffff;
			cpu_siddl  = (o26_avsinfo >> 16) & 0xffff;
			printk("O26 AVS info valid o26_avsinfo[%x] %d %d \n",o26_avsinfo,cpu_siddl,core_siddl);

		}
		else
		{
			__pm_o26_set_vol(GPIO_AVS_CPU,CPU_AVS_S,0,0);

			printk("O26 CPUAVS Kdriver lx_chip_rev[%x]  AVS cpu skipped! cpu[%s]V[%s] core[%s]V[%s]\n"
				,lx_chip_rev(),cpu_volttype_o26[CPU_AVS_S],o26_cpu_vidttype[CPU_AVS_S],core_volttype_o26[O26_CORE_AVS_SS],o26_core_vidttype[O26_CORE_AVS_SS]);
			return -1;
		}


		if (lx_chip_rev() >= LX_CHIP_REV(O26,A0)){
			ret = pm_o26_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o26[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
				return ret;
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			__pm_o26_set_vol(I2C_AVS_CPU,o26_cpu_avs,0,1);
		}
		else
		{
			__pm_o26_set_vol(GPIO_AVS_CPU,o26_cpu_avs,0,1);
		}

		printk("O26 CPUAVS bootparam cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d]\n",
				o26_cpu_avstype[o26_cpu_avs],o26_core_avstype[o26_core_avs],cpu_volttype_o26[o26_cpu_avs],o26_cpu_vidttype[o26_cpu_avs],
				core_volttype_o26[o26_core_avs],o26_core_vidttype[o26_core_avs],lx_chip_rev(),o26_slt_high);

		return 0;
	}
	else
	/* skip avs */
	{
		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			__pm_o26_set_vol(I2C_AVS_CPU,CPU_AVS_S, 0,0);
			/* crc fail or brank case :  default HV(Slow chip condition)  */
			if(o26_slt_high)
			{
				printk("O26 boot CPUAVS avs info is not valid, skipped! SLTH o26_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
					,o26_avsinfo,cpu_volttype_o26_slthigh[CPU_AVS_S],core_volttype_o26_slthigh[O26_CORE_AVS_SS],lx_chip_rev() );
			}
			else
			{
				printk("O26 boot CPUAVS avs info is not valid, skipped! SLTL o26_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
					,o26_avsinfo,cpu_volttype_o26_sltlow[CPU_AVS_S],core_volttype_o26_sltlow[O26_CORE_AVS_SS],lx_chip_rev() );
			}

		}
		else{
			__pm_o26_set_vol(GPIO_AVS_CPU,CPU_AVS_S, 0,0);
			/* crc fail or brank case :  default HV(Slow chip condition)  */
			printk("O26 boot CPUAVS avs info is not valid, skipped! o26_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
					,o26_avsinfo,cpu_volttype_o26[CPU_AVS_S],core_volttype_o26[O26_CORE_AVS_SS],lx_chip_rev() );

		}
		return -1;
	}
}

int pm_o26_set_coreavs(void)/*avscoretime o26_avs_coretimework_func*/
{
	int ret = -1;
	unsigned int core_siddl = 0U, cpu_siddl = 0U;

	if(o26_avs_enable == 0)
	{
		printk("O26 COREAVS skipped\n");
		return 0;
	}

	if(o26_pms_tcorevol > 0 && o26_pms_tcorevol < VOUT_MAX )
	{

		pms_o26_work_t pms_work ;
		memset(&pms_work, 0x0, sizeof(pms_o26_work_t));
		pms_work.target_corevol = (unsigned int)o26_pms_tcorevol;
		pms_work.do_avs = (UINT32)I2C_AVS_CORE;
		pms_work.ch = (UINT32)0;
		//pm_o26_func->run_coreregul(&pms_work);
		printk("O26 AVS bootparam tcorev[%d]mV cpu_avs[%d]\n",pms_work.target_corevol,o26_core_avs );

		return 0;
	}

	/* do avs using o26_core_avs,o26_cpu_avs of bootargs */
	else if((o26_core_avs > 0) && (o26_core_avs < ((UINT32)O26_CORE_AVS_INVALID_MAX)))
	{
		core_siddl = o26_avsinfo & ((UINT32)(0xffff));
		cpu_siddl  = (o26_avsinfo >> 16) & ((UINT32)0xffff);

		if (lx_chip_rev() >= ((UINT32)LX_CHIP_REV(O26,A0))){
			ret = pm_o26_check_sidd_valid(core_siddl, cpu_siddl, &gSidd_check_table_o26[SIDD_CHECK_TABLE_AX]);
			if(ret != 0)
			{
				__pm_o26_set_vol(I2C_AVS_CORE,O26_CORE_AVS_SS,(UINT32)0, (UINT32)1);
				return ret;
			}
		}

		if(lx_board_opt() & LX_BOARD_OPT_SLT)
		{
			__pm_o26_set_vol(I2C_AVS_CORE,o26_core_avs,(UINT32)0, (UINT32)1);
			printk("O26 COREAVS  cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d] \n",
				o26_cpu_avstype[o26_cpu_avs],o26_core_avstype[o26_core_avs],cpu_volttype_o26_sltlow[o26_cpu_avs],o26_cpu_vidttype[o26_cpu_avs],
				core_volttype_o26_sltlow[o26_core_avs],o26_core_vidttype[o26_core_avs],lx_chip_rev(),o26_slt_high);
		}
		else
		{
			__pm_o26_set_vol(I2C_AVS_CORE,o26_core_avs,(UINT32)0, (UINT32)1);
			printk("O26 COREAVS  cpu_avs[%s] core_avs[%s] cpu[%s]V[%s] core[%s]V[%s] chip[%x] highlow[%d] \n",
				o26_cpu_avstype[o26_cpu_avs],o26_core_avstype[o26_core_avs],cpu_volttype_o26_sltlow[o26_cpu_avs],o26_cpu_vidttype[o26_cpu_avs],
				core_volttype_o26[o26_core_avs],o26_core_vidttype[o26_core_avs],lx_chip_rev(),o26_slt_high);
		}


		return 0;
	}
	/* skip avs */
	else{

		//__pm_o26_set_vol(GPIO_AVS_CORE,O26_CORE_AVS_SS,(UINT32)0, (UINT32)1);
		__pm_o26_set_vol(I2C_AVS_CORE,O26_CORE_AVS_SS,(UINT32)0, (UINT32)1);
		/* crc fail or brank case :  default HV(Slow chip condition)  */
		printk("O26 COREAVS avs info is not valid, skipped! o26_avsinfo[%x] cpu[%s]V core[%s]V chip[%x]\n"
				,o26_avsinfo,cpu_volttype_o26[CPU_AVS_S],core_volttype_o26[O26_CORE_AVS_SS],lx_chip_rev() );
		return -1;
	}
}



int pm_o26_set_avs_force(UINT32 core_cpu, UINT32 type)
{
	UINT32 core_avs= 0, cpu_avs = 0;

#ifdef O26_AVS_SLT
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;
		//__pm_o26_set_vol(core_cpu,type, 0, 0);
	}
#else
	if (core_cpu == GPIO_AVS_CPU ){
		cpu_avs = type;

		__pm_o26_set_vol(core_cpu,type, 0, 0);
        PM_NOTI("O26 AVSFORCE cpu[%s][%s]V[%s] \n"
		    ,o26_cpu_avstype[cpu_avs],cpu_volttype_o26[cpu_avs],o26_cpu_vidttype[cpu_avs]);
	}
#endif
	if (core_cpu == I2C_AVS_CORE && type < O26_CPU_AVS_INVALID_MAX){

		core_avs = type;
		__pm_o26_set_vol(core_cpu,type, 0, 0);
	}
	else if ((core_cpu == I2C_AVS_CPU || core_cpu == I2C_AVS_CORE) && type >= O26_CPU_AVS_INVALID_MAX){
		__pm_o26_set_vol(core_cpu,type, 0, 0);
	}

	return 0;
}


int pm_o26_set_avs_in_resume(void)
{
	return 0;
}

int pm_o26_check_n_set(void)
{
	return 0;
}



/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o26_pm_ioctl_avs (unsigned int cmd, unsigned long arg)
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
extern unsigned int o26_kdrv_pm_runtime_suspend;
int o26_check_ts(void)
{
	int cpu_temp = 0;

	cpu_temp = readl((void *)((uintptr_t)o26_cpu_ts_base + (uintptr_t)0x40) );

	if( o26_avs_info.ts_debug_enable )
				PM_NOTI("O26 CPU TEMP[%d] MAXTEMP[%d] high[%d]\n",cpu_temp,o26_tempmax,o26_avs_info.is_avshigh);


	ts_timer_count++;

	if (ts_timer_count >= ts_timer_1s)
	{
		if(o26_kdrv_pm_runtime_suspend )
		{
			//writel(0, o26_ts_set_base);
			//cpu_rawts = readl((void *)((uintptr_t)o26_cpu_ts_base + (uintptr_t)0x14) );
		}
		ts_timer_1s_count ++;

		if( cpu_temp != 0  && (cpu_temp > 0 && cpu_temp < 300) )
		{
			o26_avs_info.temperature = cpu_temp;

			if( cpu_temp > o26_tempmax)
				o26_tempmax = cpu_temp;
			if(ts_timer_1s_count >= 5)
			{
				if( cpu_temp > o26_hot_ts_val)
					PM_NOTI("TEMP[%d] MAXTEMP[%d]\n",cpu_temp,o26_tempmax);

				ts_timer_1s_count = 0;
			}

			if( o26_avs_info.ts_debug_enable )
			{
				PM_NOTI("O26 CPU TEMP[%d] MAXTEMP[%d] high[%d]\n",cpu_temp,o26_tempmax,o26_avs_info.is_avshigh);
			}

			if( o26_change_avs_by_ts && o26_pm_get_gov_start())
			{
				/* high avs 50 <= ts */
				if(cpu_temp >= o26_high_ts_val)
				{
					if(o26_avs_info.is_avshigh == 0)
					{
						o26_avs_info.is_avshigh = 1;

						PM_NOTI("HIGH AVS[%d][%d][%d][%d]\n", o26_core_avs_highvolt[o26_core_avs],o26_core_avs,cpu_temp,o26_tempmax);
						__pm_o26_set_vol(I2C_AVS_CORE, o26_core_avs_highvolt[o26_core_avs],(UINT32)0, (UINT32)0);
					}
				}
				/* sustain 20 <= ts  <50 */
				else if(cpu_temp >= o26_normal_ts_val)
				{
				}
				/* normal avs ts  < 20 */
				else
				{
					if(o26_avs_info.is_avshigh == 1)
					{
						o26_avs_info.is_avshigh = 0;
						PM_NOTI("LOW AVS[%d][%d][%d][%d]\n", o26_core_avs_volt[o26_core_avs],o26_core_avs,cpu_temp,o26_tempmax);
						__pm_o26_set_vol(I2C_AVS_CORE, o26_core_avs_volt[o26_core_avs],(UINT32)0, (UINT32)0);
					}
				}
			}
		}

		if(o26_kdrv_pm_runtime_suspend )
		{
			//writel(1, o26_ts_set_base);
		}


		ts_timer_count = 0;
	}
	return 0 ;
}

static int o26_pm_set_cpu_ts_aparam(unsigned int value)
{
	o26_avs_info.cpu_ts_aparam = value;
	return 0;
}

static int o26_pm_set_cpu_ts_bparam(unsigned int value)
{
	o26_avs_info.cpu_ts_bparam = value;
	return 0;
}

static unsigned int o26_pm_get_cpu_ts_aparam(void)
{
	return o26_avs_info.cpu_ts_aparam;
}

static unsigned int o26_pm_get_cpu_ts_bparam(void)
{
	return o26_avs_info.cpu_ts_bparam;
}

static int o26_pm_set_gpu_ts_aparam(unsigned int value)
{
	o26_avs_info.gpu_ts_aparam = value;
	return 0;
}

static int o26_pm_set_gpu_ts_bparam(unsigned int value)
{
	o26_avs_info.gpu_ts_bparam = value;
	return 0;
}

static unsigned int o26_pm_get_gpu_ts_aparam(void)
{
	return o26_avs_info.gpu_ts_aparam;
}

static unsigned int o26_pm_get_gpu_ts_bparam(void)
{
	return o26_avs_info.gpu_ts_bparam;
}

static int o26_pm_set_ts_debug_enable(unsigned int value)
{
	o26_avs_info.ts_debug_enable = value;

	return 0;
}

static unsigned int o26_pm_get_ts_debug_enable(void)
{
	return o26_avs_info.ts_debug_enable;
}

static int o26_pm_get_temperature(void)
{
	return o26_avs_info.temperature;
}

static unsigned int o26_pm_get_high_ts(void)
{
	return o26_avs_info.is_avshigh;
}

void o26_AvsReInit(void)
{
	//unsigned int val;

	o26_avs_info.is_avshigh = 0U;
	if(o26_cpu_ts_base != NULL)
	{
		#if 0
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(o26_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));

		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, o26_cpu_ts_base );
		mdelay(2);
		PM_NOTI("O26 TSADC set [%d]\n",val);
		#endif

	}
}

void o26_AvsInit(void)
{
	unsigned int core_siddl = 0, cpu_siddl = 0,val =0;


	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		#if 0
		if(o26_slt_hl_base == NULL)
			o26_slt_hl_base = ioremap( 0xcec82118, 0x4);

		/* gpio 141 mux enable not set by pinctrl  */
		val = readl(o26_slt_hl_base );
		val &= (~0xf0000000);
		val |= 0x10000000;
		writel(val, o26_slt_hl_base );

		/* gpio 141 is used for slt low volt low high volt:high */
		o26_sltgpiod = gpiod_get(&o26_gpiodev, "141", GPIOD_ASIS);

		if (IS_ERR(o26_sltgpiod))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",141,o26_sltgpiod);
			return ;
		}
		val = gpiod_get_value(o26_sltgpiod);
		o26_slt_high = val;
		gpiod_put(o26_sltgpiod);
		o26_change_avs_by_ts = 0;
		PM_NOTI("o26_is_sltmode[%d]\n",o26_slt_high);
		#else
		o26_sltgpiod = gpiod_get(&o26_gpiodev, "68", GPIOD_ASIS);

		if (IS_ERR(o26_sltgpiod))
		{
			PM_ERROR("unable to get gpio desc[%d:%p]\n",68,o26_sltgpiod);
			return ;
		}
		val = gpiod_get_value(o26_sltgpiod);
		o26_slt_high = val;
		gpiod_put(o26_sltgpiod);
		o26_change_avs_by_ts = 0;
		PM_NOTI("o26_is_sltmode[%d]\n",o26_slt_high);

		#endif

	}
	else{

		pm_o26_func = get_o26_pm_func();

		if(o26_avs_enable == 1)
		{
			/* gpio 21 22 */
			o26_cpuvid0 = gpiod_get(&o26_gpiodev, "19", GPIOD_ASIS);
			if (IS_ERR(o26_cpuvid0))
			{
				PM_ERROR("unable to get gpio desc[%d:%p]\n",19,o26_cpuvid0);
			}
			o26_cpuvid1 = gpiod_get(&o26_gpiodev, "20", GPIOD_ASIS);
			if (IS_ERR(o26_cpuvid1))
			{
				PM_ERROR("unable to get gpio desc[%d:%p]\n",20,o26_cpuvid0);
			}
		}
	}

	if(o26_cpu_ts_base == NULL)
		o26_cpu_ts_base = ioremap( 0xbc400200, 0x40);
	#if 0
	if(o26_ts_set_base == NULL)
		o26_ts_set_base = ioremap( 0xCC60001C, 0x4);
	#endif
	if(o26_cpu_ts_base != NULL)
	{
		#if 0
		val = TS_BIAS_DFT;
		writel(val, (volatile void*)((uintptr_t)(o26_cpu_ts_base)+ (uintptr_t)(TS_BIAS_OFFSET)));

		val = TS_SEL_CHOP | TS_SET_CLK | TS_SEL_TRIM | TS_PDB ;
		writel(val, o26_cpu_ts_base );
		mdelay(2);
		PM_NOTI("O26 TSADC set [%d]\n",val);
		#endif
	}
	/* cpu_ts_aparam, cpu_ts_bparam can be changed by /proc/lg/pm/ proc */
	/* cpu temp =  -341.60(cpu_ts_bparam)  + 0.01510(cpu_ts_aparam)*(TSADC_CPU_RAW_DATA) */

	o26_avs_info.cpu_ts_aparam = 1350;
	o26_avs_info.cpu_ts_bparam = 33720000;

	/* avs table is changed when gpu temp reach 80'c */

	o26_avs_info.avshigh_th = o26_high_ts_val;
	o26_avs_info.is_avshigh = 0;
	o26_avs_info.avshigh_count = 0;

	o26_avs_info.ts_debug_enable = 0;

	if((o26_core_avs > 0) && (o26_core_avs < O26_CORE_AVS_INVALID_MAX) &&
			(o26_cpu_avs > 0) && (o26_cpu_avs < O26_CPU_AVS_INVALID_MAX))
	{
		/*  correct AVS info case:  */
		core_siddl = o26_avsinfo & 0xffff;
		cpu_siddl  = (o26_avsinfo >> 16) & 0xffff;
	}
}

int o26_set_avsinit_ext(void)
{
		#if 0
		int i = 0;

		if(o26_slt_high)
		{
			o26_SetCpuVal(o26_cpu_avs_volt_slthigh[1],0);
		}
		else
		{
			o26_SetCpuVal(o26_cpu_avs_volt_sltlow[1],0);
		}

		o26_cur_freq = 1200; /*for set*/

		for(i=0; i < o26_freq_change_cnt ; i++)
		{
			o26_SetCPUFreq(1400);
			msleep(o26_freq_delayms);
			o26_SetCPUFreq(1200);
			msleep(o26_freq_delayms);
		}

		o26_SetCPUFreq(1400);
		msleep(o26_freq_delayms);
		#endif
		return 0;
}

static pms_o26_avs_t o26_pm_avs =
{
	.init = o26_AvsInit,
	.reinit = o26_AvsReInit,
	.set_avs = pm_o26_set_avs,
	.set_coreavs = pm_o26_set_coreavs,
	.get_cpu_avs_type = pm_o26_get_cpu_avs,
	.get_cpu_avs_type_str = pm_o26_get_cpu_avs_str,
	.get_core_avs_type = pm_o26_get_core_avs,
	.get_core_avs_type_str = pm_o26_get_core_avs_str,
	.set_avs_in_resume = pm_o26_set_avs_in_resume,
	.set_avs_force = pm_o26_set_avs_force,
	.check_n_set = pm_o26_check_n_set,
	.ioctl = o26_pm_ioctl_avs,
	.check_ts = o26_check_ts,
	.get_cpu_ts_aparam = o26_pm_get_cpu_ts_aparam,
	.set_cpu_ts_aparam = o26_pm_set_cpu_ts_aparam,
	.get_cpu_ts_bparam = o26_pm_get_cpu_ts_bparam,
	.set_cpu_ts_bparam = o26_pm_set_cpu_ts_bparam,
	.get_gpu_ts_aparam = o26_pm_get_gpu_ts_aparam,
	.set_gpu_ts_aparam = o26_pm_set_gpu_ts_aparam,
	.get_gpu_ts_bparam = o26_pm_get_gpu_ts_bparam,
	.set_gpu_ts_bparam = o26_pm_set_gpu_ts_bparam,
	.get_ts_debug_enable = o26_pm_get_ts_debug_enable,
	.set_ts_debug_enable = o26_pm_set_ts_debug_enable,
	.get_temperature = o26_pm_get_temperature,
	.get_high_ts = o26_pm_get_high_ts,
	.init_ext = o26_set_avsinit_ext,
};

pms_o26_avs_t* get_o26_pm_avs(void)
{
	return &o26_pm_avs;
}


