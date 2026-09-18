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
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
 */


#ifndef	_PM_M16P_COMMON_H_
#define	_PM_M16P_COMMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "pm_cfg.h"
#include "pm_kapi.h"
#include "pm_drv.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PMS_GOV_MASK			0xF
#define PMS_GOV_TOSUSPEND_FLAG	0x10

#define PMS_GOV_DISABLE			0x0
#define PMS_GOV_ENABLE			0x1
#define PMS_GOV_MONITOR			0x2
#define PMS_GOV_EN_N_MON		0x3
#define PMS_GOV_DEBUG			0x4
#define PMS_GOV_DEBUG_FREQ			0x5

#define GOV_START_DELAY 	60

#define GPIO_AVS_CPU       	 1
#define GPIO_AVS_CORE        2

#define M16PC0_AVS_SET_DELAY 	30	/* sec */

#define GPIO_AVS_CORE0        31
#define GPIO_AVS_CORE1        13

#define GPIO_AVS_CPU0         107
#define GPIO_AVS_CPU1         108

#define CORE_AVS_FF 4   /* ffast */
#define CORE_AVS_F 3    /* fast */
#define CORE_AVS_N 2    /* normal */
#define CORE_AVS_S 1    /* slow */
#define CORE_AVS_X 0    /* not determined */

#define CPU_AVS_FF 4    /* ffast */
#define CPU_AVS_F 3     /* fast */
#define CPU_AVS_N 2     /* normal */
#define CPU_AVS_S 1     /* slow */
#define CPU_AVS_X 0     /* not determined */


#define AVS_NOT_INITED 0

/* m17_load_dump related*/

#define UD_CNT 0
#define ND_CNT 1
#define UD_PER 2
#define ND_PER 3

/* m17_cpu_load related */
#define LOAD_CPU0		0
#define LOAD_CPU1		1
#define LOAD_CPU2		2
#define LOAD_CPU3		3
#define LOAD_MAX		4
#define LOAD_AVG		5

#define CPU_OFF				0
#define CPU_ON				1

#define M17_CPU_FREQ_ND			1008
#define M17_CPU_FREQ_UD			600

#define M17_CPU_VOL_ND			940
#define M17_CPU_VOL_UD			800




/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	volatile unsigned int	current_freq;
	volatile unsigned int	target_freq;
	volatile unsigned int	target_vol;
	volatile unsigned int	do_dvfs;
	volatile unsigned int	core_onoff;
	volatile unsigned int	core_n;
	volatile unsigned int	do_hotplug;
}pms_m17_work_t;

typedef struct
{
	unsigned int governor;
	unsigned int boost;
	unsigned int startup_timer;
	unsigned int count_1s;
	unsigned int up_threshold;
	unsigned int hard_up_threshold;
	unsigned int easy_up_threshold;
	unsigned int easy_count;
	unsigned int freqdown_count;
	unsigned int mpd_count;
	unsigned int min_freq;
	unsigned int max_freq;
	unsigned int mp_enable;
	unsigned int cpu_load[6];
	unsigned int load_dump[4];
	unsigned int core_n;
}pms_m17_govstatus_t;

typedef struct
{
	unsigned int corecpu;
	unsigned int avstype;
	unsigned int avscurrent;
}pms_m17_avsinto_t;


typedef struct
{
	void  			(*init)(void);
	unsigned int	(*get_fw_copied)(void);
	void			(*set_fw_copied)(void);
	void  			(*run)(pms_m17_work_t m17work);
	void  			(*reset)(void);
	void			(*taskdisable_reset)(void);
	unsigned int	(*getfreq)(void);
	int				(*setfreq)(unsigned int freq);
	unsigned int	(*get_cpu_on)(void);
	int				(*get_cpu_type)(void);
	void			(*set_max_performance)	(void);
	unsigned int	(*get_sampling_rate)(void);
	int				(*set_sampling_rate)(unsigned int ms);
	unsigned int	(*get_error_state)(void);
	int				(*set_error_state)(unsigned int value);
} pms_m17_func_t;

typedef struct
{
	void  			(*init)(void);
	void  			(*boost)(void);
	void 			(*check_cpu)(void);
	int				(*ioctl)(unsigned int cmd, unsigned int arg);
	unsigned int	(*get_gov)(void);
	unsigned char *	(*get_gov_str)(unsigned int cpunum);
	int				(*set_gov)(unsigned int status);
	unsigned int	(*get_cpunum)(void);
	unsigned int 	(*get_startup_timer)(void);
	int 			(*set_startup_timer)(unsigned int startup_time);
	int 			(*set_avscheck_timer)(unsigned int avscheck_time);
	unsigned int	(*get_load)(unsigned int cpu);
	void			(*reset_load_monitor)(void);
	unsigned int	(*get_hard_up_threshold)(void);
	int 			(*set_hard_up_threshold)(unsigned int threshold);
	unsigned int	(*get_easy_up_threshold)(void);
	int 			(*set_easy_up_threshold)(unsigned int threshold);
	unsigned int	(*get_easy_count)(void);
	int 			(*set_easy_count)(unsigned int count);
	unsigned int 	(*get_freqdown_count)(void);
	int 			(*set_freqdown_count)(unsigned int value);
	unsigned int 	(*get_mpd_count)(void);
	int 			(*set_mpd_count)(unsigned int value);
	unsigned int 	(*get_min_freq)(void);
	int 			(*set_min_freq)(unsigned int value);
	unsigned int 	(*get_max_freq)(void);
	int				(*set_max_freq)(unsigned int value);
	unsigned int 	(*get_mp_enable)(void);
	int				(*set_mp_enable)(unsigned int value);
	unsigned int 	(*get_gpu_detect)(void);
	int				(*set_gpu_detect)(unsigned int value);
} pms_m17_gov_t;

typedef struct
{
	int cpu_sidd_ff_min;
	int cpu_sidd_f_min;
	int cpu_sidd_n_min;

	int core_sidd_ff_min;
	int core_sidd_f_min;
	int core_sidd_n_min;

	int core_sidd_valid_max;
	int core_sidd_valid_min;
}m16p_sidd_t;


typedef struct
{
	void  			(*init)(void);
	void 			(*set_testmode)(unsigned int mode);
	unsigned int	(*get_testmode)(void);
	void 			(*set_testinterval)(unsigned int interval);
	unsigned int	(*get_testinterval)(void);
	void 			(*test_func)(void);
	unsigned int	(*test_boot)(void);
	int				(*ioctl)(unsigned int cmd, unsigned int arg);
} pms_m17_test_t;

typedef struct
{
	int				(*ioctl)(unsigned int cmd, unsigned int arg);
} pms_m17_cg_t;

typedef struct
{
	void  			(*init)(void);
	int 			(*set_avs)(void);
	int 			(*get_cpu_avs_type)(pms_m17_avsinto_t *);
	int 			(*get_core_avs_type)(pms_m17_avsinto_t *);
	unsigned char * (*get_cpu_avs_type_str)(void);
	unsigned char *	(*get_core_avs_type_str)(void);
	int				(*set_avs_in_resume)(void);
	int 			(*set_avs_force)(UINT32 core_cpu, UINT32 type);
	int 			(*check_n_set)(void);
	int				(*ioctl)(unsigned int cmd, unsigned int arg);
} pms_m17_avs_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
pms_proc_t* get_m17_pm_proc(void);
pms_m17_func_t* get_m17_pm_func(void);
pms_m17_gov_t* get_m17_pm_gov(void);
pms_m17_cg_t* get_m17_pm_cg(void);
pms_m17_avs_t* get_m17_pm_avs(void);
pms_m17_test_t* get_m17_pm_test(void);
pms_driver_t* get_m17_pm_driver(void);

int __pm_m17_set_vol(UINT32 core_cpu, UINT32 type);

int m17_set_clock_gating(unsigned int module, unsigned int sub, unsigned int state);
int m17_get_clock_gating(unsigned int module, unsigned int sub, unsigned int *state);

void m17_boost(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PM_DRV_H_ */

/** @} */
