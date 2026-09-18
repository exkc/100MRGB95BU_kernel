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
//#include "pm_reg.h"
#include "pm_core.h"
//#include "pm_cfg.h"
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
#include <linux/irqchip/arm-gic.h>

#include "pm_o24common.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

//#define PM_DEBUG_PRINT
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define HARD_UP_THRESHOLD		90
#define EASY_UP_THRESHOLD		75

#define	MP_TASK_GO				0
#define	MP_TASK_NONEED			1

#define O24_GPU_IRQ				101		//102//103
#define O24_BOOST_TIME			10000	// 10sec

									 /* high normal low verylow voltage */
static char * governor_str[7] = { "GOV_DISABLE","GOV_ENABLE", "GOV_MON", "GOV_EN_N_MON","GOV_DEBUG", "DEBUG_FREQ", "DFT_MODE" };


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static pms_o24_func_t* pm_o24_func = NULL;
static pms_o24_avs_t* pm_o24_avs = NULL;
static pms_o24_test_t* pm_o24_test = NULL;

extern int o24_SetCPUFreq(unsigned int freq);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static pms_o24_govstatus_t	o24_gov_status;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
unsigned int o24_pm_get_debug_enable(void) ;
int o24_pm_set_debug_enable(unsigned int val) ;
static unsigned int o24_pm_get_hist(void) ;
static int o24_pm_set_hist(unsigned int val) ;
static unsigned int o24_pm_get_freq_up_threshold(void);
static unsigned int o24_pm_get_freq_dn_threshold(void);

unsigned int o24_hotplug_enable = 1;
module_param(o24_hotplug_enable, uint, S_IRUGO);
MODULE_PARM_DESC(o24_hotplug_enable, "o24_hotplug_enable");

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static void PM_print_cpuload(unsigned int max_load, unsigned int *cpu_load, unsigned int *load_data, unsigned int freq)
{

	printk("f:%4u:l:%3u:%3u:%3u:%3u[%x]m:%3u:a:%3u:per:%u:%u\n ",
		freq,cpu_load[LOAD_CPU0],cpu_load[LOAD_CPU1],cpu_load[LOAD_CPU2],cpu_load[LOAD_CPU3],
		1|cpu_online(1)<<1| cpu_online(2)<<2|cpu_online(3)<<3, max_load,o24_gov_status.cpu_load[LOAD_AVG],load_data[UD_PER],load_data[ND_PER] );
}

static inline u64 PM_get_cpu_idle_time_jiffy(unsigned int cpu, u64 *wall)
{
	u64 idle_time;
	u64 cur_wall_time;
	u64 busy_time;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	cur_wall_time = jiffies64_to_cputime64(get_jiffies_64());
#else
	cur_wall_time = jiffies64_to_nsecs(get_jiffies_64());
#endif

	busy_time = kcpustat_cpu(cpu).cpustat[CPUTIME_USER];
	busy_time += kcpustat_cpu(cpu).cpustat[CPUTIME_SYSTEM];
	busy_time += kcpustat_cpu(cpu).cpustat[CPUTIME_IRQ];
	busy_time += kcpustat_cpu(cpu).cpustat[CPUTIME_SOFTIRQ];
	busy_time += kcpustat_cpu(cpu).cpustat[CPUTIME_STEAL];
	busy_time += kcpustat_cpu(cpu).cpustat[CPUTIME_NICE];

	idle_time = cur_wall_time - busy_time;
	if (wall)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	*wall = cputime_to_usecs(cur_wall_time);
#else
	*wall = div_u64(cur_wall_time, NSEC_PER_USEC);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
	return cputime_to_usecs(idle_time);
#else
	return div_u64(idle_time, (unsigned int)NSEC_PER_USEC);
#endif
}

static u64 PM_get_cpu_idle_time(unsigned int cpu, u64 *wall, int io_busy)
{
extern u64 get_cpu_idle_time_us(int cpu, u64 *last_update_time);
extern u64 get_cpu_iowait_time_us(int cpu, u64 *last_update_time);

	u64 idle_time = get_cpu_idle_time_us((int)cpu, io_busy ? wall : NULL);

	if (idle_time == -1ULL)
		return PM_get_cpu_idle_time_jiffy((int)cpu, wall);
	else if (!io_busy)
		idle_time += get_cpu_iowait_time_us((int)cpu, wall);

	return idle_time;
}

unsigned int o24_get_cpuload(void)
{
	unsigned int avg_load = 0;
	unsigned int max_load = 0;
	unsigned int min_load = 0;
	unsigned int j;

	static u64 prev_cpu_wall[4] = {0,0,0,0}, prev_cpu_idle[4] = {0,0,0,0};
	unsigned int cpu_load[4];
	static unsigned int cpu_on_backup[4] = {0,0,0,0};
	unsigned int count_on;
	//unsigned int cputype =	pm_o24func->get_cpu_type();

	/* Get CPU Load */
	for(j=0,count_on=0; j<nr_cpu_ids; j++) {
		u64 cur_wall_time, cur_idle_time;
		unsigned int idle_time, wall_time;
		unsigned int load;
		int io_busy = 0;

		if (!cpu_online(j))
		{
			cpu_on_backup[j] = 0;
			cpu_load[j] = 0;
			o24_gov_status.cpu_load[j] = 0;
			continue;
		}
		count_on++;

		cur_idle_time = PM_get_cpu_idle_time(j, &cur_wall_time, io_busy);
		wall_time = (unsigned int)
			(cur_wall_time - prev_cpu_wall[j]);
		prev_cpu_wall[j] = cur_wall_time;

		idle_time = (unsigned int)
			(cur_idle_time - prev_cpu_idle[j]);
		prev_cpu_idle[j] = cur_idle_time;

		if (unlikely(!wall_time || wall_time < idle_time)) {
			cpu_on_backup[j] = 1;
			cpu_load[j] = 0;
			o24_gov_status.cpu_load[j] = 0;
			continue;
		}

		if (cpu_on_backup[j]) {
			load = 100 * (wall_time - idle_time) / wall_time;
			if (load > 100)
				load = 100;
		} else {
			load = 0;
		}

		cpu_on_backup[j] = 1;

		cpu_load[j] = load;

		o24_gov_status.cpu_load[j] =  load;

		if (load > max_load)
			max_load = load;

		if (load < min_load)
			min_load = load;


		o24_gov_status.cpu_load[LOAD_MAX] = max_load;

	}


	o24_gov_status.cpu_load[LOAD_AVG] = 0;

	for(j=0 ; j< count_on; j++) {
		o24_gov_status.cpu_load[LOAD_AVG] += o24_gov_status.cpu_load[j];
	}

	if(count_on) {
		o24_gov_status.core_n = count_on;
		o24_gov_status.cpu_load[LOAD_AVG] = o24_gov_status.cpu_load[LOAD_AVG] / count_on ;
		avg_load = o24_gov_status.cpu_load[LOAD_AVG] ;
	}

	return 0;
}



unsigned int o24_freq_governor(pms_o24_work_t *pms_o24_work, unsigned int * cpu_load)
{

	unsigned int cpu_on_count = 0;
	unsigned int loadsum = 0;
	static unsigned int dn_count = 0;
	cpu_on_count = o24_gov_status.core_n;

	if (cpu_on_count == 4) {
		loadsum = cpu_load[0] + cpu_load[1] + cpu_load[2] + cpu_load[3];
		pms_o24_work->loadsum = loadsum;

        if((loadsum  > o24_pm_get_freq_up_threshold())  && pms_o24_work->current_freq != 1400)
        {
			#if 0
			if(o24_pm_get_debug_enable())
				PM_NOTI("loadsum %d  freq_UP\n", loadsum);
			#endif
			dn_count = 0;
			pms_o24_work->target_freq = 1400;
			pms_o24_work->do_dvfs = 1;
        }
        else if((loadsum  < o24_pm_get_freq_dn_threshold()) && pms_o24_work->current_freq != 1200)
        {
			dn_count++;
			if (dn_count > o24_gov_status.freqdown_count)
			{
			#if 0
				if(o24_pm_get_debug_enable())
					PM_NOTI("loadsum %d 2sec_freq_DN\n", loadsum);
			#endif
				pms_o24_work->target_freq = 1200;
				pms_o24_work->do_dvfs = 1;
				dn_count = 0;
			}
		}
		else
		{
			/* sustain current freq */
		}
	}
    else
    {
		if (cpu_on_count == 3) {
			loadsum = cpu_load[0] + cpu_load[1] + cpu_load[2];
		}
		else if(cpu_on_count == 2) {
			loadsum = cpu_load[0] + cpu_load[1];
		}
		pms_o24_work->loadsum = loadsum;

		dn_count = 0;
        if( pms_o24_work->current_freq != 1200)
        {
			pms_o24_work->target_freq = 1200;
			pms_o24_work->do_dvfs = 1;
        }
    }


	return 0;
}



void o24_mp_governor(pms_o24_work_t *pms_o24_work, unsigned int *cpu_load)
{

	static unsigned int cpu_on_target = 4;
	unsigned int cpu_on_count;
	unsigned int i;
	static unsigned int hotplug_count = 0;
	unsigned int loadsum;
	unsigned int threshold;
	unsigned int threshold_l;

#define CPU_4TH				3
#define CPU_3RD				2
#define CPU_2ND				1
#define CPU_1ST				0

	cpu_on_count = o24_gov_status.core_n;

	if (cpu_on_count == 4) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD] + cpu_load[CPU_4TH];
		threshold = 400;;
		threshold_l = o24_gov_status.mpd_dn_threshold;
	} else if (cpu_on_count == 3) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD];
		threshold =  o24_gov_status.mpd_up_threshold;
		threshold_l = o24_gov_status.mpd_dn_threshold2;

	} else {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND];
		threshold = o24_gov_status.mpd_up_threshold2;
		threshold_l = 0;
	}

	if (loadsum > threshold)
    {
		cpu_on_target = cpu_on_count + 1;
    }

	if (loadsum < threshold_l) {
		hotplug_count++;
		if (hotplug_count > o24_gov_status.mpd_count) {
			cpu_on_target = cpu_on_count - 1;
			hotplug_count = 0;
		}
	}else
		hotplug_count = 0;

	pms_o24_work->cpunum = cpu_on_count;
	pms_o24_work->loadsum = loadsum;
	pms_o24_work->core_onoff = 0;

	//PM_TRACE("loadsum %d th %d thl %d cpu_on_target %d  cpu_on_count %d \n", loadsum,threshold,threshold_l, cpu_on_target, cpu_on_count);
	PM_TRACE("loadsum %d", loadsum);

	if (cpu_on_count < cpu_on_target && loadsum > threshold) {

			
		for(i=1; i<4; i++) {
			if (cpu_online(i) == 0) {
				pms_o24_work->core_n = i;
				pms_o24_work->core_onoff = CPU_ON;
				pms_o24_work->do_hotplug = 1;
				return;
			}
		}
	} else if (cpu_on_count > cpu_on_target && loadsum < threshold_l) {

		for(i=3; i>0; i--) {
			if (cpu_online(i)) {
				pms_o24_work->core_n = i;
				pms_o24_work->core_onoff = CPU_OFF;
				pms_o24_work->do_hotplug = 1;
				return;
			}
		}
	}

	return;
}

static int o24_governor_run_checker(void)
{
	static unsigned int timer_count = 0;

	if ((o24_gov_status.governor == PMS_GOV_DISABLE) ||
		(o24_gov_status.governor & PMS_GOV_TOSUSPEND_FLAG) )
		return -1;

	if (o24_gov_status.startup_timer > 0) {
		timer_count++;
		if (timer_count >= o24_gov_status.count_1s) {
			timer_count = 0;
			o24_gov_status.startup_timer--;
		}
		return -1;
	} else {
		if (timer_count == 0) {
			printk("O24 CPU Governor Start!\n");
			o24_gov_status.start = 1;
			timer_count = 1;
		}
	}

	return 0;
}

void o24_boost(void)
{
	o24_gov_status.boost = 1;
}

void o24_check_cpu(void)
{
	static unsigned int boost_time = 0;

	pms_o24_work_t pms_o24_work;

	if(o24_gov_status.ts_enable)
	{
		pm_o24_avs->check_ts();
	}

	if (o24_governor_run_checker() < 0)
		return;

	memset(&pms_o24_work, 0x0, sizeof(pms_o24_work_t));

	if (o24_gov_status.boost) {
		o24_gov_status.boost = 0;
		boost_time = O24_BOOST_TIME / pm_o24_func->get_sampling_rate();
	}

	pms_o24_work.do_dvfs = 0;
	pms_o24_work.do_hotplug = 0;
	pms_o24_work.current_freq = pm_o24_func->getfreq();
	pms_o24_work.target_freq = 0;
	pms_o24_work.target_vol = 0;

	// calculate CPU Load
	o24_get_cpuload();

	if (o24_gov_status.governor == PMS_GOV_MONITOR) {
		PM_print_cpuload(o24_gov_status.cpu_load[LOAD_MAX], o24_gov_status.cpu_load, o24_gov_status.load_dump, pms_o24_work.current_freq);
		return;
	}

	if(pm_o24_test->get_testmode() != 0)
		return;

	if (o24_gov_status.freq_enable && (pm_o24_avs->get_high_ts() == 0))
	{
		o24_freq_governor(&pms_o24_work, o24_gov_status.cpu_load);
    }

	// call MP Decision Governor
	if (o24_gov_status.mp_enable)
		o24_mp_governor(&pms_o24_work, o24_gov_status.cpu_load);

	if (o24_gov_status.governor == PMS_GOV_EN_N_MON)
		PM_print_cpuload(o24_gov_status.cpu_load[LOAD_MAX], o24_gov_status.cpu_load,
						o24_gov_status.load_dump, pms_o24_work.target_freq ? pms_o24_work.target_freq : pms_o24_work.current_freq);


	if (pms_o24_work.do_hotplug)
		pm_o24_func->run(&pms_o24_work);
	if (pms_o24_work.do_dvfs)
		pm_o24_func->run_clk(&pms_o24_work);

	return;
}

static unsigned int o24_pm_get_gov(void)
{
	return o24_gov_status.governor;
}

static unsigned int o24_pm_get_cpunum(void)
{
	unsigned int j,cpunum;

	/* Get CPU Load */
	for(j=0,cpunum=0; j<nr_cpu_ids; j++) {

		if (!cpu_online(j))
		{
			continue;
		}else
			cpunum++;
	}

	return cpunum;
}

static unsigned char * o24_pm_get_gov_str(unsigned int gov)
{
	return governor_str[o24_gov_status.governor];
}

static void o24_pm_reset_load_monitor(void)
{
	o24_gov_status.load_dump[UD_CNT] = 0;
	o24_gov_status.load_dump[ND_CNT] = 0;
}
static int o24_pm_set_gov(unsigned int value)
{
	o24_gov_status.governor =  value;
	if(value == 0)
		o24_pm_reset_load_monitor();
	return 0;
}

static unsigned int o24_pm_get_startup_timer(void)
{
	// return value unit is second
	return o24_gov_status.startup_timer;
}

static int o24_pm_set_startup_timer(unsigned int startup_timer)
{
	// input value unit is second
	o24_gov_status.startup_timer = startup_timer;

	return 0;
}


static unsigned int o24_pm_get_hard_upthreshold(void)
{
	return o24_gov_status.hard_up_threshold;
}

static int o24_pm_set_hard_upthreshold(unsigned int up_threshold)
{
	if (o24_gov_status.up_threshold == o24_gov_status.hard_up_threshold)
		o24_gov_status.up_threshold = up_threshold;

	o24_gov_status.hard_up_threshold = up_threshold;

	return 0;
}


static unsigned int o24_pm_get_easy_upthreshold(void)
{
	return o24_gov_status.easy_up_threshold;
}

static int o24_pm_set_easy_upthreshold(unsigned int up_threshold)
{
	if (o24_gov_status.up_threshold == o24_gov_status.easy_up_threshold)
		o24_gov_status.up_threshold = up_threshold;

	o24_gov_status.easy_up_threshold = up_threshold;

	return 0;
}


static unsigned int o24_pm_get_easy_count(void)
{
	return o24_gov_status.easy_count;
}

static int o24_pm_set_easy_count(unsigned int count)
{
	o24_gov_status.easy_count = count;

	return 0;
}


static unsigned int o24_pm_get_freqdown_count(void)
{
	return o24_gov_status.freqdown_count;
}

static int o24_pm_set_freqdown_count(unsigned int value)
{
	o24_gov_status.freqdown_count = value;

	return 0;
}

static unsigned int o24_pm_get_mpd_count(void)
{
	return o24_gov_status.mpd_count;
}

static int o24_pm_set_mpd_count(unsigned int value)
{
	o24_gov_status.mpd_count = value;

	return 0;
}

static unsigned int o24_pm_get_mpd_up_threshold(void)
{
	return o24_gov_status.mpd_up_threshold;
}

static int o24_pm_set_mpd_up_threshold(unsigned int value)
{
	o24_gov_status.mpd_up_threshold = value;
	return 0;
}

static unsigned int o24_pm_get_mpd_dn_threshold(void)
{
	return o24_gov_status.mpd_dn_threshold;
}

static int o24_pm_set_mpd_dn_threshold(unsigned int value)
{
	o24_gov_status.mpd_dn_threshold = value;
	return 0;
}

static unsigned int o24_pm_get_mpd_up_threshold2(void)
{
	return o24_gov_status.mpd_up_threshold2;
}

static int o24_pm_set_mpd_up_threshold2(unsigned int value)
{
	o24_gov_status.mpd_up_threshold2 = value;
	return 0;
}

static unsigned int o24_pm_get_mpd_dn_threshold2(void)
{
	return o24_gov_status.mpd_dn_threshold2;
}

static int o24_pm_set_mpd_dn_threshold2(unsigned int value)
{
	o24_gov_status.mpd_dn_threshold2 = value;
	return 0;
}


static unsigned int o24_pm_get_freq_up_threshold(void)
{
	return o24_gov_status.freq_up_threshold;
}

static int o24_pm_set_freq_up_threshold(unsigned int value)
{
	o24_gov_status.freq_up_threshold = value;
	return 0;
}

static unsigned int o24_pm_get_freq_dn_threshold(void)
{
	return o24_gov_status.freq_dn_threshold;
}

static int o24_pm_set_freq_dn_threshold(unsigned int value)
{
	o24_gov_status.freq_dn_threshold = value;
	return 0;
}

static int o24_pm_set_fv_time(unsigned int us)
{
	o24_gov_status.fv_time = us;
	return 0;
}
static unsigned int o24_pm_get_fv_time(void)
{
	return o24_gov_status.fv_time;
}

static int o24_pm_set_hist(unsigned int val)
{
	o24_gov_status.hist = val;
	return 0;
}
static unsigned int o24_pm_get_hist(void)
{
	return o24_gov_status.hist;
}

static unsigned int o24_pm_get_min_freq(void)
{
	return o24_gov_status.min_freq;
}

static int o24_pm_set_min_freq(unsigned int value)
{
	o24_gov_status.min_freq = value;

	return 0;
}

static unsigned int o24_pm_get_max_freq(void)
{
	return o24_gov_status.max_freq;
}

static int o24_pm_set_max_freq(unsigned int value)
{
	o24_gov_status.max_freq = value;

	return 0;
}


static unsigned int o24_pm_get_load(unsigned int cpu)
{
	return o24_gov_status.cpu_load[cpu];
}

static int o24_pm_set_mp_enable(unsigned int value)
{
	o24_gov_status.mp_enable = value;

	return 0;
}

static unsigned int o24_pm_get_freq_enable(void)
{
	return o24_gov_status.freq_enable;
}

static int o24_pm_set_freq_enable(unsigned int value)
{
	o24_gov_status.freq_enable = value;
	return 0;
}

static unsigned int o24_pm_get_freq_debug_enable(void)
{
	return o24_gov_status.freq_debug_enable;
}

static int o24_pm_set_freq_debug_enable(unsigned int value)
{
	o24_gov_status.freq_debug_enable = value;
	return 0;
}

unsigned int o24_pm_get_debug_enable(void)
{
	return o24_gov_status.debug_enable;
}

int o24_pm_set_debug_enable(unsigned int value)
{
	o24_gov_status.debug_enable = value;
	return 0;
}

static unsigned int o24_pm_get_mp_enable(void)
{
	return o24_gov_status.mp_enable;
}

static int o24_pm_set_ts_enable(unsigned int value)
{
	o24_gov_status.ts_enable = value;
	return 0;
}

static unsigned int o24_pm_get_ts_enable(void)
{
	return o24_gov_status.ts_enable;
}

static unsigned int o24_pm_get_gov_start(void)
{
	return o24_gov_status.start;
}

static void o24_gov_init(void)
{
	pm_o24_func = get_o24_pm_func();
	pm_o24_avs = get_o24_pm_avs();
	pm_o24_test = get_o24_pm_test();

	o24_gov_status.startup_timer = O24_GOV_START_DELAY;
	o24_gov_status.governor = PMS_GOV_DISABLE;
	o24_gov_status.up_threshold = HARD_UP_THRESHOLD;
	o24_gov_status.hard_up_threshold = HARD_UP_THRESHOLD;
	o24_gov_status.easy_up_threshold = EASY_UP_THRESHOLD;
	o24_gov_status.easy_count = 48;

	o24_gov_status.freqdown_count = 1;
	o24_gov_status.mpd_count = 8;
	o24_gov_status.count_1s = 5;

	o24_gov_status.mpd_up_threshold = 200;
	o24_gov_status.mpd_dn_threshold = 160;
	o24_gov_status.mpd_up_threshold2 = 140;
	o24_gov_status.mpd_dn_threshold2 = 100;
	o24_gov_status.freq_up_threshold = 300;
	o24_gov_status.freq_dn_threshold = 250;
	o24_gov_status.fv_time = 100;
	o24_gov_status.hist = 0;
	o24_gov_status.min_freq = O24_CPU_FREQ_UD;
	o24_gov_status.max_freq = O24_CPU_FREQ_ND;

	o24_gov_status.freq_enable = o24_hotplug_enable;

	o24_gov_status.freq_debug_enable = 1;
	o24_gov_status.debug_enable = 0;

	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		o24_gov_status.mp_enable = 0;
	}
	else
	{
		o24_gov_status.mp_enable = o24_hotplug_enable;
	}

	o24_gov_status.ts_enable = 1;

	o24_gov_status.start = 0;
	memset(o24_gov_status.cpu_load, 0x0, sizeof(o24_gov_status.cpu_load));
	memset(o24_gov_status.load_dump, 0x0, sizeof(o24_gov_status.load_dump));

	return;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o24_pm_ioctl_governor (unsigned int cmd, unsigned long arg)
{
	unsigned int status;
	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_CPU_GOV_WORK:		// 0 : Disable, 1 : Enable, 2 : Monitor
			if (arg <= 3)
			{
				o24_pm_set_gov(arg);
				o24_pm_set_startup_timer(0);
				if (arg == 0)
				{
					pm_o24_func->set_max_performance();
					o24_SetCPUFreq(1200);
				}
			}
			break;
		case PM_GET_CPU_GOV_STATUS:	// 0 : Disable, 1 : Enable, 2: Monitor, 3: Enable & Monutor
			status = o24_pm_get_gov();
			result = copy_to_user((void __user*)(arg), (void *)(&status), sizeof(status));
			if (result)
			{
				PM_ERROR("PM_GET_CPU_GOV_STATUS - CONFIG DATA COPY FAIL\n");
				ret = -EINVAL;
			}
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

static pms_o24_gov_t o24_pm_gov =
{
	.init = o24_gov_init,
	.boost = o24_boost,
	.check_cpu = o24_check_cpu,
	.ioctl = o24_pm_ioctl_governor,
	.get_gov = o24_pm_get_gov,
	.get_gov_str = o24_pm_get_gov_str,
	.get_cpunum = o24_pm_get_cpunum,
	.set_gov = o24_pm_set_gov,
	.get_startup_timer = o24_pm_get_startup_timer,
	.set_startup_timer = o24_pm_set_startup_timer,
	.reset_load_monitor = o24_pm_reset_load_monitor,
	.get_load = o24_pm_get_load,
	.get_hard_up_threshold = o24_pm_get_hard_upthreshold,
	.set_hard_up_threshold = o24_pm_set_hard_upthreshold,
	.get_easy_up_threshold = o24_pm_get_easy_upthreshold,
	.set_easy_up_threshold = o24_pm_set_easy_upthreshold,
	.get_easy_count = o24_pm_get_easy_count,
	.set_easy_count = o24_pm_set_easy_count,
	.get_freqdown_count = o24_pm_get_freqdown_count,
	.set_freqdown_count = o24_pm_set_freqdown_count,
	.get_mpd_count = o24_pm_get_mpd_count,
	.set_mpd_count = o24_pm_set_mpd_count,
	.get_mpd_up_threshold = o24_pm_get_mpd_up_threshold,
	.set_mpd_up_threshold = o24_pm_set_mpd_up_threshold,
	.get_mpd_dn_threshold = o24_pm_get_mpd_dn_threshold,
	.set_mpd_dn_threshold = o24_pm_set_mpd_dn_threshold,
	.get_mpd_up_threshold2 = o24_pm_get_mpd_up_threshold2,
	.set_mpd_up_threshold2 = o24_pm_set_mpd_up_threshold2,
	.get_mpd_dn_threshold2 = o24_pm_get_mpd_dn_threshold2,
	.set_mpd_dn_threshold2 = o24_pm_set_mpd_dn_threshold2,
	.get_freq_up_threshold = o24_pm_get_freq_up_threshold,
	.set_freq_up_threshold = o24_pm_set_freq_up_threshold,
	.get_freq_dn_threshold = o24_pm_get_freq_dn_threshold,
	.set_freq_dn_threshold = o24_pm_set_freq_dn_threshold,

	.get_fv_time = o24_pm_get_fv_time,
	.set_fv_time = o24_pm_set_fv_time,
	.get_hist = o24_pm_get_hist,
	.set_hist = o24_pm_set_hist,
	.get_min_freq = o24_pm_get_min_freq,
	.set_min_freq = o24_pm_set_min_freq,
	.get_max_freq = o24_pm_get_max_freq,
	.set_max_freq = o24_pm_set_max_freq,
	.get_mp_enable = o24_pm_get_mp_enable,
	.set_mp_enable = o24_pm_set_mp_enable,
	.get_freq_enable = o24_pm_get_freq_enable,
	.set_freq_enable = o24_pm_set_freq_enable,
	.get_freq_debug_enable = o24_pm_get_freq_debug_enable,
	.set_freq_debug_enable = o24_pm_set_freq_debug_enable,
	.get_debug_enable = o24_pm_get_debug_enable,
	.set_debug_enable = o24_pm_set_debug_enable,
	.get_ts_enable = o24_pm_get_ts_enable,
	.get_ts_enable = o24_pm_get_ts_enable,
	.set_ts_enable = o24_pm_set_ts_enable,
	.get_gov_start = o24_pm_get_gov_start,
};

pms_o24_gov_t* get_o24_pm_gov(void)
{
	return &o24_pm_gov;
}

