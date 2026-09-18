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

#include "pm_o18common.h"

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

#define O18_GPU_IRQ				101		//102//103
#define O18_BOOST_TIME			10000	// 10sec


static DEFINE_SPINLOCK(g_o18_gov_lock);
									 /* high normal low verylow voltage */
static char * governor_str[5] = { "GOV_DISABLE","GOV_ENABLE","GOV_EN_N_MON","GOV_DEBUG", "DEBUG_FREQ", };


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static pms_o18_func_t* pm_o18_func = NULL;
static pms_o18_avs_t* pm_o18_avs = NULL;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static pms_o18_govstatus_t	o18_gov_status;
static unsigned int load_history_pointer = 0;
static unsigned int load_history_pointer_wrap = 0;
static LX_PM_O18_LOADINFO_T o18_load_history[50];
static LX_PM_O18_LOAD_HISTORY_T o18_dump_history;

static int o18_pms_gdetect = 0;
module_param(o18_pms_gdetect, int, S_IRUGO);
MODULE_PARM_DESC(o18_pms_gdetect, "o18lus pms gpu detect");

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static void PM_print_cpuload(unsigned int max_load, unsigned int *cpu_load, unsigned int *load_data, unsigned int freq)
{
	unsigned int cpu_count = 1;

	printk("f:%4u:", freq);
	printk("l:%3u:",cpu_load[LOAD_CPU0]);

	if (cpu_online(1)) {
		printk("%3u:",cpu_load[LOAD_CPU1]);
		cpu_count++;
	}
	else
		printk(" x :");

	if (cpu_online(2)) {
		printk("%3u:",cpu_load[LOAD_CPU2]);
		cpu_count++;
	}
	else
		printk(" x :");

	if (cpu_online(3)) {
		printk("%3u: ",cpu_load[LOAD_CPU3]);
		cpu_count++;
	}
	else
		printk(" x :");

	printk("m:%3u:a:%3u:", max_load, o18_gov_status.cpu_load[LOAD_AVG]);
	printk(":on:%u:", cpu_count);
	printk("per:%u:%u\n",load_data[UD_PER],load_data[ND_PER]);
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
	return div_u64(idle_time, NSEC_PER_USEC);
#endif
}

static u64 PM_get_cpu_idle_time(unsigned int cpu, u64 *wall, int io_busy)
{
extern u64 get_cpu_idle_time_us(int cpu, u64 *last_update_time);
extern u64 get_cpu_iowait_time_us(int cpu, u64 *last_update_time);

	u64 idle_time = get_cpu_idle_time_us(cpu, io_busy ? wall : NULL);

	if (idle_time == -1ULL)
		return PM_get_cpu_idle_time_jiffy(cpu, wall);
	else if (!io_busy)
		idle_time += get_cpu_iowait_time_us(cpu, wall);

	return idle_time;
}

unsigned int o18_get_cpuload(void)
{
	unsigned int avg_load = 0;
	unsigned int max_load = 0;
	unsigned int min_load = 0;
	unsigned int j;

	static u64 prev_cpu_wall[4] = {0,0,0,0}, prev_cpu_idle[4] = {0,0,0,0};
	unsigned int cpu_load[4];
	static unsigned int cpu_on_backup[4] = {0,0,0,0};
	unsigned int count_on;
	//unsigned int cputype =	pm_o18func->get_cpu_type();

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
			o18_gov_status.cpu_load[j] = 0;
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
			o18_gov_status.cpu_load[j] = 0;
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

		o18_gov_status.cpu_load[j] =  load;

		if (load > max_load)
			max_load = load;

		if (load < min_load)
			min_load = load;


		o18_gov_status.cpu_load[LOAD_MAX] = max_load;

	}


	o18_gov_status.cpu_load[LOAD_AVG] = 0;

	for(j=0 ; j< count_on; j++) {
		o18_gov_status.cpu_load[LOAD_AVG] += o18_gov_status.cpu_load[j];
	}

	if(count_on) {
		o18_gov_status.core_n = count_on;
		o18_gov_status.cpu_load[LOAD_AVG] = o18_gov_status.cpu_load[LOAD_AVG] / count_on ;
		avg_load = o18_gov_status.cpu_load[LOAD_AVG] ;
	}

	return 0;
}



unsigned int o18_freq_governor(pms_o18_work_t *pms_o18_work, unsigned int load)
{
	unsigned int target;
	static unsigned int freqdown_count = 0;
	static unsigned int easy_up_count = 0;
	unsigned int threshold;

	// CPU Freq Up Condition
	if (o18_gov_status.up_threshold == o18_gov_status.easy_up_threshold) {
		easy_up_count++;
		if (easy_up_count >= o18_gov_status.easy_count) {
			o18_gov_status.up_threshold = o18_gov_status.hard_up_threshold;
			easy_up_count = 0;
		}

		if (pms_o18_work->current_freq == O18_CPU_FREQ_ND)
			easy_up_count = 0;
	} else {
		easy_up_count = 0;
	}

	pms_o18_work->target_freq = 0;

	if (load > o18_gov_status.up_threshold) {
		pms_o18_work->target_freq = O18_CPU_FREQ_ND;
		freqdown_count = 0;

		o18_gov_status.up_threshold = o18_gov_status.easy_up_threshold;
	} else {
		freqdown_count++;
		if (pms_o18_work->current_freq > O18_CPU_FREQ_UD) {
			threshold = o18_gov_status.freqdown_count;

			if (freqdown_count >= threshold) {
				freqdown_count = 0;
				target = ((load * O18_CPU_FREQ_ND) * 120) / 10000;
				if (target <= O18_CPU_FREQ_UD) {
					pms_o18_work->target_freq = O18_CPU_FREQ_UD;
				}
			}
		}
	}

	if (pms_o18_work->target_freq) {
		if (pms_o18_work->target_freq < o18_gov_status.min_freq)
			pms_o18_work->target_freq = o18_gov_status.min_freq;

		if (pms_o18_work->target_freq > o18_gov_status.max_freq)
			pms_o18_work->target_freq = o18_gov_status.max_freq;
	} else  {
		pms_o18_work->target_freq = pms_o18_work->current_freq;
	}

	if (pms_o18_work->target_freq > pms_o18_work->current_freq)
		pms_o18_work->do_dvfs = 1;
	else if (pms_o18_work->target_freq < pms_o18_work->current_freq)
		pms_o18_work->do_dvfs = 2;

	return 0;
}



void o18_mp_governor(pms_o18_work_t *pms_o18_work, unsigned int *cpu_load)
{

	static unsigned int hotplug_count = 0;
	static unsigned int cpu_on_target = 4;
	unsigned int cpu_on_count;

	unsigned int i;
	unsigned int loadsum;
	unsigned int threshold;
	unsigned int threshold_l;


#define CPU_4TH				3
#define CPU_3RD				2
#define CPU_2ND				1
#define CPU_1ST				0

cpu_on_count = o18_gov_status.core_n;
#ifdef O18_DVFS_ENABLE
{
	static unsigned int current_clock_backup = 0;
	unsigned int hotplug_condition = 0;
	unsigned int cpu_3rd = 0;

	// ND -> UD로 클럭 변화가 생길경우 HOTPLUG COUNT를 초기화 한다.
	if (pms_o18_work->current_freq != current_clock_backup) {
		if (current_clock_backup != CPU_FREQ_UD)
			hotplug_count = 0;
		current_clock_backup = pms_o18_work->current_freq;
	}

	if (pms_o18_work->current_freq == O18_CPU_FREQ_ND) {
		hotplug_condition = 1;

		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + ((cpu_on_count == 3) ? cpu_load[cpu_3rd] : 0);
		threshold = (cpu_on_count == 3) ? 180 : 120;

		if ((loadsum >= threshold) && (cpu_on_count < 4)) {
			hotplug_count++;
			if (hotplug_count >= hotplug_condition) {
				cpu_on_target = (cpu_on_count == 3) ? 4 : 3;
				hotplug_count = 0;
			}
		} else {
			hotplug_count = 0;
		}
	} else {
		hotplug_condition = o18_gov_status.mpd_count;
		hotplug_count++;

		if (hotplug_count >= hotplug_condition)
		{
			if (cpu_on_count == 4) {
				cpu_on_target = 3;
				hotplug_count = 0;
			} else if (cpu_on_count == 3) {
				cpu_on_target = 2;
				hotplug_count = 0;
			}
		}
	}
}
#else

	if (cpu_on_count == 4) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD] + cpu_load[CPU_4TH];
		threshold = 400;;
		threshold_l = 180;
	} else if (cpu_on_count == 3) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD];
		threshold = 200;
		threshold_l = 100;
	} else {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND];
		threshold = 120;
		threshold_l = 0;
	}

	if (loadsum > threshold)
		cpu_on_target = cpu_on_count + 1;

	if (loadsum < threshold_l) {
		hotplug_count++;
		if (hotplug_count > o18_gov_status.mpd_count) {
			cpu_on_target = cpu_on_count - 1;
			hotplug_count = 0;
		}
	} else
		hotplug_count = 0;
#endif

	pms_o18_work->core_onoff = 0;

	if (cpu_on_count < cpu_on_target) {
		for(i=1; i<4; i++) {
			if (cpu_online(i) == 0) {
				pms_o18_work->core_n = i;
				pms_o18_work->core_onoff = CPU_ON;
				pms_o18_work->do_hotplug = 1;
				return;
			}
		}
	} else if (cpu_on_count > cpu_on_target) {
		for(i=3; i>0; i--) {
			if (cpu_online(i)) {
				pms_o18_work->core_n = i;
				pms_o18_work->core_onoff = CPU_OFF;
				pms_o18_work->do_hotplug = 1;
				return;
			}
		}
	}

	return;
}

static int o18_governor_run_checker(void)
{
	static unsigned int timer_count = 0;

	if ((o18_gov_status.governor == PMS_GOV_DISABLE) || (o18_gov_status.governor & PMS_GOV_TOSUSPEND_FLAG))
		return -1;

	if (o18_gov_status.startup_timer > 0) {
		timer_count++;
		if (timer_count >= o18_gov_status.count_1s) {
			timer_count = 0;
			o18_gov_status.startup_timer--;
		}
		return -1;
	} else {
		if (timer_count == 0) {
			printk("O18 CPU Governor Start!\n");
			timer_count = 1;
		}
	}

	return 0;
}

void o18_boost(void)
{
	o18_gov_status.boost = 1;
}

static unsigned int cpu_load_dump(pms_o18_work_t *pms_o18_work)
{
	unsigned int mode_cnt_sum ;

	if (pms_o18_work->current_freq == O18_CPU_FREQ_UD) {
		o18_gov_status.load_dump[UD_CNT]++;
	} else if (pms_o18_work->current_freq == O18_CPU_FREQ_ND) {
		o18_gov_status.load_dump[ND_CNT]++;
	}

	if ((o18_gov_status.load_dump[UD_CNT] == 0) || (o18_gov_status.load_dump[ND_CNT] == 0)) {
		o18_gov_status.load_dump[UD_CNT] = 1;
		o18_gov_status.load_dump[ND_CNT] = 1;
	}

	mode_cnt_sum = o18_gov_status.load_dump[UD_CNT] + o18_gov_status.load_dump[ND_CNT];

	o18_gov_status.load_dump[UD_PER] = o18_gov_status.load_dump[UD_CNT] * 100 /  mode_cnt_sum;
	o18_gov_status.load_dump[ND_PER] = 100 - o18_gov_status.load_dump[UD_PER];


	return 0;
}

static void put_load_history(pms_o18_work_t *pms_o18_work)
{
	unsigned long flags;

	spin_lock_irqsave(&g_o18_gov_lock, flags);

	o18_load_history[load_history_pointer].timestamp = (unsigned int)(sched_clock() >> 20);
	o18_load_history[load_history_pointer].freq = pms_o18_work->current_freq;
	o18_load_history[load_history_pointer].cpu0 = o18_gov_status.cpu_load[LOAD_CPU0];
	o18_load_history[load_history_pointer].cpu1 = o18_gov_status.cpu_load[LOAD_CPU1];
	o18_load_history[load_history_pointer].cpu2 = o18_gov_status.cpu_load[LOAD_CPU2];
	o18_load_history[load_history_pointer].cpu3 = o18_gov_status.cpu_load[LOAD_CPU3];
	o18_load_history[load_history_pointer].max = o18_gov_status.cpu_load[LOAD_MAX];
	o18_load_history[load_history_pointer].avg = o18_gov_status.cpu_load[LOAD_AVG];
	o18_load_history[load_history_pointer].core_number = o18_gov_status.core_n;
	o18_load_history[load_history_pointer].nd_per = o18_gov_status.load_dump[ND_PER];
	o18_load_history[load_history_pointer].ud_per = o18_gov_status.load_dump[UD_PER];

	load_history_pointer++;
	if (load_history_pointer >= 50) {
		load_history_pointer = 0;
		load_history_pointer_wrap = 1;
	}

	spin_unlock_irqrestore(&g_o18_gov_lock, flags);
}

static int copy_load_history(void)
{
	unsigned int unit_size = sizeof(LX_PM_O18_LOADINFO_T);
	unsigned int pointer;
	unsigned long flags;

	spin_lock_irqsave(&g_o18_gov_lock, flags);

	pointer = load_history_pointer;

	if (load_history_pointer_wrap) {
		if (pointer == 0) {
			memcpy((char *)o18_dump_history.history, (char *)o18_load_history, 50 * unit_size);
		} else {
			memcpy((char *)o18_dump_history.history, (char *)o18_load_history + (pointer * unit_size), (50 - pointer) * unit_size);
			memcpy((char *)o18_dump_history.history + ((50 - pointer) * unit_size), (char *)o18_load_history, unit_size + (pointer * unit_size));
		}

		o18_dump_history.count = 50;
	} else {
		if (pointer == 0) {
			o18_dump_history.count = 0;
		} else {
			memcpy((char *)o18_dump_history.history, (char *)o18_load_history, pointer * unit_size);
			o18_dump_history.count = pointer;
		}
	}

	load_history_pointer = 0;
	load_history_pointer_wrap = 0;

	spin_unlock_irqrestore(&g_o18_gov_lock, flags);

	return 0;
}

void o18_check_cpu(void)
{
	static unsigned int boost_time = 0;

	pms_o18_work_t pms_o18_work;

	if (o18_governor_run_checker() < 0)
		return;

	memset(&pms_o18_work, 0x0, sizeof(pms_o18_work_t));

	if (o18_gov_status.boost) {
		o18_gov_status.boost = 0;
		boost_time = O18_BOOST_TIME / pm_o18_func->get_sampling_rate();
	}

	pms_o18_work.do_dvfs = 0;
	pms_o18_work.do_hotplug = 0;
	pms_o18_work.current_freq = pm_o18_func->getfreq();
	pms_o18_work.target_freq = 0;
	pms_o18_work.target_vol = 0;

	// calculate CPU Load
	o18_get_cpuload();

	cpu_load_dump(&pms_o18_work);
	put_load_history(&pms_o18_work);

	if (o18_gov_status.governor == PMS_GOV_MONITOR) {
		PM_print_cpuload(o18_gov_status.cpu_load[LOAD_MAX], o18_gov_status.cpu_load, o18_gov_status.load_dump, pms_o18_work.current_freq);
		return;
	}

	if (pms_o18_work.current_freq == 0) {
		pms_o18_work.target_freq = O18_CPU_FREQ_ND;
#ifdef O18_DVFS_ENABLE
		pms_o18_work.do_dvfs = 1;
#endif
		pms_o18_work.do_hotplug = 0;
		pm_o18_func->run(pms_o18_work);
		return;
	}

#ifdef O18_DVFS_ENABLE
	if (boost_time > 0) {
		boost_time--;
		if (pms_o18_work.current_freq < O18_CPU_FREQ_ND) {
			pms_o18_work.target_freq = O18_CPU_FREQ_ND;
			pms_o18_work.do_dvfs = 1;
		} else {
			pms_o18_work.target_freq = 0;
			pms_o18_work.do_dvfs = 0;
		}
	} else {
		o18_freq_governor(&pms_o18_work, o18_gov_status.cpu_load[LOAD_MAX]);
	}
#endif

	// call MP Decision Governor
	if (o18_gov_status.mp_enable)
		o18_mp_governor(&pms_o18_work, o18_gov_status.cpu_load);

	if (o18_gov_status.governor == PMS_GOV_EN_N_MON)
		PM_print_cpuload(o18_gov_status.cpu_load[LOAD_MAX], o18_gov_status.cpu_load,
						o18_gov_status.load_dump, pms_o18_work.target_freq ? pms_o18_work.target_freq : pms_o18_work.current_freq);

	if(o18_gov_status.ts_enable)
	{
		pm_o18_avs->check_ts();
	}

	if (pms_o18_work.do_dvfs || pms_o18_work.do_hotplug )
		pm_o18_func->run(pms_o18_work);

	return;
}

static unsigned int o18_pm_get_gov(void)
{
	return o18_gov_status.governor;
}

static unsigned int o18_pm_get_cpunum(void)
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

static unsigned char * o18_pm_get_gov_str(unsigned int gov)
{
	return governor_str[o18_gov_status.governor];
}

static void o18_pm_reset_load_monitor(void)
{
	o18_gov_status.load_dump[UD_CNT] = 0;
	o18_gov_status.load_dump[ND_CNT] = 0;
}
static int o18_pm_set_gov(unsigned int value)
{
	o18_gov_status.governor =  value;
	if( value == 0 )
		o18_pm_reset_load_monitor();
	return 0;
}

static unsigned int o18_pm_get_startup_timer(void)
{
	// return value unit is second
	return o18_gov_status.startup_timer;
}

static int o18_pm_set_startup_timer(unsigned int startup_timer)
{
	// input value unit is second
	o18_gov_status.startup_timer = startup_timer;

	return 0;
}


static unsigned int o18_pm_get_hard_upthreshold(void)
{
	return o18_gov_status.hard_up_threshold;
}

static int o18_pm_set_hard_upthreshold(unsigned int up_threshold)
{
	if (o18_gov_status.up_threshold == o18_gov_status.hard_up_threshold)
		o18_gov_status.up_threshold = up_threshold;

	o18_gov_status.hard_up_threshold = up_threshold;

	return 0;
}


static unsigned int o18_pm_get_easy_upthreshold(void)
{
	return o18_gov_status.easy_up_threshold;
}

static int o18_pm_set_easy_upthreshold(unsigned int up_threshold)
{
	if (o18_gov_status.up_threshold == o18_gov_status.easy_up_threshold)
		o18_gov_status.up_threshold = up_threshold;

	o18_gov_status.easy_up_threshold = up_threshold;

	return 0;
}


static unsigned int o18_pm_get_easy_count(void)
{
	return o18_gov_status.easy_count;
}

static int o18_pm_set_easy_count(unsigned int count)
{
	o18_gov_status.easy_count = count;

	return 0;
}


static unsigned int o18_pm_get_freqdown_count(void)
{
	return o18_gov_status.freqdown_count;
}

static int o18_pm_set_freqdown_count(unsigned int value)
{
	o18_gov_status.freqdown_count = value;

	return 0;
}

static unsigned int o18_pm_get_mpd_count(void)
{
	return o18_gov_status.mpd_count;
}

static int o18_pm_set_mpd_count(unsigned int value)
{
	o18_gov_status.mpd_count = value;

	return 0;
}


static unsigned int o18_pm_get_min_freq(void)
{
	return o18_gov_status.min_freq;
}

static int o18_pm_set_min_freq(unsigned int value)
{
	o18_gov_status.min_freq = value;

	return 0;
}

static unsigned int o18_pm_get_max_freq(void)
{
	return o18_gov_status.max_freq;
}

static int o18_pm_set_max_freq(unsigned int value)
{
	o18_gov_status.max_freq = value;

	return 0;
}


static unsigned int o18_pm_get_load(unsigned int cpu)
{
	return o18_gov_status.cpu_load[cpu];
}

static int o18_pm_set_mp_enable(unsigned int value)
{
	o18_gov_status.mp_enable = value;

	return 0;
}

static unsigned int o18_pm_get_mp_enable(void)
{
	return o18_gov_status.mp_enable;
}

static int o18_pm_set_ts_enable(unsigned int value)
{
	o18_gov_status.ts_enable = value;

	return 0;
}

static unsigned int o18_pm_get_ts_enable(void)
{
	return o18_gov_status.ts_enable;
}


static void o18_gov_init(void)
{
	pm_o18_func = get_o18_pm_func();
	pm_o18_avs = get_o18_pm_avs();

	o18_gov_status.startup_timer = GOV_START_DELAY;
	o18_gov_status.count_1s = HZ / ((HZ / 100) * (20 / 10));
	o18_gov_status.governor = PMS_GOV_DISABLE;
	o18_gov_status.up_threshold = HARD_UP_THRESHOLD;
	o18_gov_status.hard_up_threshold = HARD_UP_THRESHOLD;
	o18_gov_status.easy_up_threshold = EASY_UP_THRESHOLD;
	o18_gov_status.easy_count = 48;
	o18_gov_status.freqdown_count = 24;
	o18_gov_status.mpd_count = 100;
	o18_gov_status.min_freq = O18_CPU_FREQ_UD;
	o18_gov_status.max_freq = O18_CPU_FREQ_ND;
	o18_gov_status.mp_enable = 1;
	o18_gov_status.ts_enable = 1;
	memset(o18_gov_status.cpu_load, 0x0, sizeof(o18_gov_status.cpu_load));
	memset(o18_gov_status.load_dump, 0x0, sizeof(o18_gov_status.load_dump));

	return;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o18_pm_ioctl_governor (unsigned int cmd, unsigned long arg)
{
	unsigned int status;
	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_CPU_GOV_WORK:		// 0 : Disable, 1 : Enable, 2 : Monitor
			if (arg <= 3)
			{
				o18_pm_set_gov(arg);
				o18_pm_set_startup_timer(0);
				if (arg == 0)
					pm_o18_func->set_max_performance();
			}
			break;
		case PM_GET_CPU_GOV_STATUS:	// 0 : Disable, 1 : Enable, 2: Monitor, 3: Enable & Monutor
			status = o18_pm_get_gov();
			result = copy_to_user((void __user*)(arg), (void *)(&status), sizeof(status));
			if (result)
				PM_ERROR("PM_GET_CPU_GOV_STATUS - CONFIG DATA COPY FAIL\n");
			break;
		case PM_GET_LOAD_HISTORY:
			ret = copy_load_history();
			result = copy_to_user((void __user*)(arg), (void *)(&o18_dump_history), sizeof(o18_dump_history));
			if (result)
				PM_ERROR("PM_GET_STATUS - CONFIG DATA COPY FAIL TO USER\n");
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

static pms_o18_gov_t o18_pm_gov =
{
	.init = o18_gov_init,
	.boost = o18_boost,
	.check_cpu = o18_check_cpu,
	.ioctl = o18_pm_ioctl_governor,
	.get_gov = o18_pm_get_gov,
	.get_gov_str = o18_pm_get_gov_str,
	.get_cpunum = o18_pm_get_cpunum,
	.set_gov = o18_pm_set_gov,
	.get_startup_timer = o18_pm_get_startup_timer,
	.set_startup_timer = o18_pm_set_startup_timer,
	.reset_load_monitor = o18_pm_reset_load_monitor,
	.get_load = o18_pm_get_load,
	.get_hard_up_threshold = o18_pm_get_hard_upthreshold,
	.set_hard_up_threshold = o18_pm_set_hard_upthreshold,
	.get_easy_up_threshold = o18_pm_get_easy_upthreshold,
	.set_easy_up_threshold = o18_pm_set_easy_upthreshold,
	.get_easy_count = o18_pm_get_easy_count,
	.set_easy_count = o18_pm_set_easy_count,
	.get_freqdown_count = o18_pm_get_freqdown_count,
	.set_freqdown_count = o18_pm_set_freqdown_count,
	.get_mpd_count = o18_pm_get_mpd_count,
	.set_mpd_count = o18_pm_set_mpd_count,
	.get_min_freq = o18_pm_get_min_freq,
	.set_min_freq = o18_pm_set_min_freq,
	.get_max_freq = o18_pm_get_max_freq,
	.set_max_freq = o18_pm_set_max_freq,
	.get_mp_enable = o18_pm_get_mp_enable,
	.set_mp_enable = o18_pm_set_mp_enable,
	.get_ts_enable = o18_pm_get_ts_enable,
	.set_ts_enable = o18_pm_set_ts_enable,
};

pms_o18_gov_t* get_o18_pm_gov(void)
{
	return &o18_pm_gov;
}

