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

#include "pm_m23common.h"

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

#define M23_GPU_IRQ				101		//102//103
#define M23_BOOST_TIME			10000	// 10sec

									 /* high normal low verylow voltage */
static char * governor_str[7] = { "GOV_DISABLE","GOV_ENABLE", "GOV_MON", "GOV_EN_N_MON","GOV_DEBUG", "DEBUG_FREQ", "DFT_MODE" };


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static pms_m23_func_t* pm_m23_func = NULL;
static pms_m23_avs_t* pm_m23_avs = NULL;
static pms_m23_test_t* pm_m23_test = NULL;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static pms_m23_govstatus_t	m23_gov_status;

static int m23_pms_gdetect = 0;
module_param(m23_pms_gdetect, int, S_IRUGO);
MODULE_PARM_DESC(m23_pms_gdetect, "m23lus pms gpu detect");

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

	printk("f:%4u:l:%3u:%3u:%3u:%3u[%x]m:%3u:a:%3u:per:%u:%u\n ",
		freq,cpu_load[LOAD_CPU0],cpu_load[LOAD_CPU1],cpu_load[LOAD_CPU2],cpu_load[LOAD_CPU3],
		1|cpu_online(1)<<1| cpu_online(2)<<2|cpu_online(3)<<3, max_load,m23_gov_status.cpu_load[LOAD_AVG],load_data[UD_PER],load_data[ND_PER] );
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

unsigned int m23_get_cpuload(void)
{
	unsigned int avg_load = 0;
	unsigned int max_load = 0;
	unsigned int min_load = 0;
	unsigned int j;

	static u64 prev_cpu_wall[4] = {0,0,0,0}, prev_cpu_idle[4] = {0,0,0,0};
	unsigned int cpu_load[4];
	static unsigned int cpu_on_backup[4] = {0,0,0,0};
	unsigned int count_on;
	//unsigned int cputype =	pm_m23func->get_cpu_type();

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
			m23_gov_status.cpu_load[j] = 0;
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
			m23_gov_status.cpu_load[j] = 0;
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

		m23_gov_status.cpu_load[j] =  load;

		if (load > max_load)
			max_load = load;

		if (load < min_load)
			min_load = load;


		m23_gov_status.cpu_load[LOAD_MAX] = max_load;

	}


	m23_gov_status.cpu_load[LOAD_AVG] = 0;

	for(j=0 ; j< count_on; j++) {
		m23_gov_status.cpu_load[LOAD_AVG] += m23_gov_status.cpu_load[j];
	}

	if(count_on) {
		m23_gov_status.core_n = count_on;
		m23_gov_status.cpu_load[LOAD_AVG] = m23_gov_status.cpu_load[LOAD_AVG] / count_on ;
		avg_load = m23_gov_status.cpu_load[LOAD_AVG] ;
	}

	return 0;
}



unsigned int m23_freq_governor(pms_m23_work_t *pms_m23_work, unsigned int load)
{
	unsigned int target;
	static unsigned int freqdown_count = 0;
	static unsigned int easy_up_count = 0;
	unsigned int threshold;

	// CPU Freq Up Condition
	if (m23_gov_status.up_threshold == m23_gov_status.easy_up_threshold) {
		easy_up_count++;
		if (easy_up_count >= m23_gov_status.easy_count) {
			m23_gov_status.up_threshold = m23_gov_status.hard_up_threshold;
			easy_up_count = 0;
		}

		if (pms_m23_work->current_freq == M23_CPU_FREQ_ND)
			easy_up_count = 0;
	} else {
		easy_up_count = 0;
	}

	pms_m23_work->target_freq = 0;

	if (load > m23_gov_status.up_threshold) {
		pms_m23_work->target_freq = M23_CPU_FREQ_ND;
		freqdown_count = 0;

		m23_gov_status.up_threshold = m23_gov_status.easy_up_threshold;
	} else {
		freqdown_count++;
		if (pms_m23_work->current_freq > M23_CPU_FREQ_UD) {
			threshold = m23_gov_status.freqdown_count;

			if (freqdown_count >= threshold) {
				freqdown_count = 0;
				target = ((load * M23_CPU_FREQ_ND) * 120) / 10000;
				if (target <= M23_CPU_FREQ_UD) {
					pms_m23_work->target_freq = M23_CPU_FREQ_UD;
				}
			}
		}
	}

	if (pms_m23_work->target_freq) {
		if (pms_m23_work->target_freq < m23_gov_status.min_freq)
			pms_m23_work->target_freq = m23_gov_status.min_freq;

		if (pms_m23_work->target_freq > m23_gov_status.max_freq)
			pms_m23_work->target_freq = m23_gov_status.max_freq;
	} else  {
		pms_m23_work->target_freq = pms_m23_work->current_freq;
	}

	#if 0
	if (pms_m23_work->target_freq > pms_m23_work->current_freq)
		pms_m23_work->do_dvfs = 1;
	else if (pms_m23_work->target_freq < pms_m23_work->current_freq)
		pms_m23_work->do_dvfs = 2;
	#else

	pm_m23_func->setfreq(pms_m23_work->target_freq);
	#endif

	return 0;
}



void m23_mp_governor(pms_m23_work_t *pms_m23_work, unsigned int *cpu_load)
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

	cpu_on_count = m23_gov_status.core_n;

	if (cpu_on_count == 4) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD] + cpu_load[CPU_4TH];
		threshold = 400;;
		threshold_l = m23_gov_status.mpd_dn_threshold;

	} else if (cpu_on_count == 3) {
		loadsum = cpu_load[CPU_1ST] + cpu_load[CPU_2ND] + cpu_load[CPU_3RD];
		threshold =  m23_gov_status.mpd_up_threshold;
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
		if (hotplug_count > m23_gov_status.mpd_count) {
			cpu_on_target = cpu_on_count - 1;
			hotplug_count = 0;
		}
	}else
		hotplug_count = 0;

	pms_m23_work->core_onoff = 0;

	PM_TRACE("loadsum %d th %d thl %d cpu_on_target %d  cpu_on_count %d \n", loadsum, threshold,threshold_l, cpu_on_target, cpu_on_count);

	if (cpu_on_count < cpu_on_target) {
		for(i=1; i<4; i++) {
			if (cpu_online(i) == 0) {
				pms_m23_work->core_n = i;
				pms_m23_work->core_onoff = CPU_ON;
				pms_m23_work->do_hotplug = 1;
				return;
			}
		}
	} else if (cpu_on_count > cpu_on_target) {
		for(i=3; i>0; i--) {
			if (cpu_online(i)) {
				pms_m23_work->core_n = i;
				pms_m23_work->core_onoff = CPU_OFF;
				pms_m23_work->do_hotplug = 1;
				return;
			}
		}
	}

	return;
}

static int m23_governor_run_checker(void)
{
	static unsigned int timer_count = 0;

	if ((m23_gov_status.governor == PMS_GOV_DISABLE) ||
		(m23_gov_status.governor & PMS_GOV_TOSUSPEND_FLAG) ||
		(m23_gov_status.governor == PMS_GOV_DFT))
		return -1;

	if (m23_gov_status.startup_timer > 0) {
		timer_count++;
		if (timer_count >= m23_gov_status.count_1s) {
			timer_count = 0;
			m23_gov_status.startup_timer--;
		}
		return -1;
	} else {
		if (timer_count == 0) {
			printk("M23 CPU Governor Start!\n");
			m23_gov_status.start = 1;
			timer_count = 1;
		}
	}

	return 0;
}

void m23_boost(void)
{
	m23_gov_status.boost = 1;
}

void m23_check_cpu(void)
{
	static unsigned int boost_time = 0;

	pms_m23_work_t pms_m23_work;

	if (m23_governor_run_checker() < 0)
		return;

	memset(&pms_m23_work, 0x0, sizeof(pms_m23_work_t));

	if (m23_gov_status.boost) {
		m23_gov_status.boost = 0;
		boost_time = M23_BOOST_TIME / pm_m23_func->get_sampling_rate();
	}

	pms_m23_work.do_dvfs = 0;
	pms_m23_work.do_hotplug = 0;
	pms_m23_work.current_freq = pm_m23_func->getfreq();
	pms_m23_work.target_freq = 0;
	pms_m23_work.target_vol = 0;

	// calculate CPU Load
	m23_get_cpuload();

	if (m23_gov_status.governor == PMS_GOV_MONITOR) {
		PM_print_cpuload(m23_gov_status.cpu_load[LOAD_MAX], m23_gov_status.cpu_load, m23_gov_status.load_dump, pms_m23_work.current_freq);
		return;
	}

	if(pm_m23_test->get_testmode() != 0)
		return;

	if (m23_gov_status.freq_enable)
	{
		if (pms_m23_work.current_freq == 0) {
			pm_m23_func->setfreq(M23_CPU_FREQ_ND);
		}


		if (boost_time > 0) {
			boost_time--;
			if (pms_m23_work.current_freq < M23_CPU_FREQ_ND) {
				pms_m23_work.target_freq = M23_CPU_FREQ_ND;
				pms_m23_work.do_dvfs = 1;
			} else {
				pms_m23_work.target_freq = 0;
				pms_m23_work.do_dvfs = 0;
			}
		} else {
			if (m23_gov_status.freq_enable)
				m23_freq_governor(&pms_m23_work, m23_gov_status.cpu_load[LOAD_MAX]);
		}
	}

	// call MP Decision Governor
	if (m23_gov_status.mp_enable)
		m23_mp_governor(&pms_m23_work, m23_gov_status.cpu_load);

	if (m23_gov_status.governor == PMS_GOV_EN_N_MON)
		PM_print_cpuload(m23_gov_status.cpu_load[LOAD_MAX], m23_gov_status.cpu_load,
						m23_gov_status.load_dump, pms_m23_work.target_freq ? pms_m23_work.target_freq : pms_m23_work.current_freq);

	if(m23_gov_status.ts_enable)
	{
		pm_m23_avs->check_ts();
	}

	if (pms_m23_work.do_dvfs || pms_m23_work.do_hotplug )
		pm_m23_func->run(&pms_m23_work);

	return;
}

static unsigned int m23_pm_get_gov(void)
{
	return m23_gov_status.governor;
}

static unsigned int m23_pm_get_cpunum(void)
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

static unsigned char * m23_pm_get_gov_str(unsigned int gov)
{
	return governor_str[m23_gov_status.governor];
}

static void m23_pm_reset_load_monitor(void)
{
	m23_gov_status.load_dump[UD_CNT] = 0;
	m23_gov_status.load_dump[ND_CNT] = 0;
}
static int m23_pm_set_gov(unsigned int value)
{
	m23_gov_status.governor =  value;
	if( value == 0 || value == 6) /* 0:disable |6:disable+dft setting */
		m23_pm_reset_load_monitor();
	return 0;
}

static unsigned int m23_pm_get_startup_timer(void)
{
	// return value unit is second
	return m23_gov_status.startup_timer;
}

static int m23_pm_set_startup_timer(unsigned int startup_timer)
{
	// input value unit is second
	m23_gov_status.startup_timer = startup_timer;

	return 0;
}


static unsigned int m23_pm_get_hard_upthreshold(void)
{
	return m23_gov_status.hard_up_threshold;
}

static int m23_pm_set_hard_upthreshold(unsigned int up_threshold)
{
	if (m23_gov_status.up_threshold == m23_gov_status.hard_up_threshold)
		m23_gov_status.up_threshold = up_threshold;

	m23_gov_status.hard_up_threshold = up_threshold;

	return 0;
}


static unsigned int m23_pm_get_easy_upthreshold(void)
{
	return m23_gov_status.easy_up_threshold;
}

static int m23_pm_set_easy_upthreshold(unsigned int up_threshold)
{
	if (m23_gov_status.up_threshold == m23_gov_status.easy_up_threshold)
		m23_gov_status.up_threshold = up_threshold;

	m23_gov_status.easy_up_threshold = up_threshold;

	return 0;
}


static unsigned int m23_pm_get_easy_count(void)
{
	return m23_gov_status.easy_count;
}

static int m23_pm_set_easy_count(unsigned int count)
{
	m23_gov_status.easy_count = count;

	return 0;
}


static unsigned int m23_pm_get_freqdown_count(void)
{
	return m23_gov_status.freqdown_count;
}

static int m23_pm_set_freqdown_count(unsigned int value)
{
	m23_gov_status.freqdown_count = value;

	return 0;
}

static unsigned int m23_pm_get_mpd_count(void)
{
	return m23_gov_status.mpd_count;
}

static int m23_pm_set_mpd_count(unsigned int value)
{
	m23_gov_status.mpd_count = value;

	return 0;
}

static unsigned int m23_pm_get_mpd_up_threshold(void)
{
	return m23_gov_status.mpd_up_threshold;
}

static int m23_pm_set_mpd_up_threshold(unsigned int value)
{
	m23_gov_status.mpd_up_threshold = value;
	return 0;
}

static unsigned int m23_pm_get_mpd_dn_threshold(void)
{
	return m23_gov_status.mpd_dn_threshold;
}

static int m23_pm_set_mpd_dn_threshold(unsigned int value)
{
	m23_gov_status.mpd_dn_threshold = value;
	return 0;
}


static unsigned int m23_pm_get_min_freq(void)
{
	return m23_gov_status.min_freq;
}

static int m23_pm_set_min_freq(unsigned int value)
{
	m23_gov_status.min_freq = value;

	return 0;
}

static unsigned int m23_pm_get_max_freq(void)
{
	return m23_gov_status.max_freq;
}

static int m23_pm_set_max_freq(unsigned int value)
{
	m23_gov_status.max_freq = value;

	return 0;
}


static unsigned int m23_pm_get_load(unsigned int cpu)
{
	return m23_gov_status.cpu_load[cpu];
}

static int m23_pm_set_mp_enable(unsigned int value)
{
	m23_gov_status.mp_enable = value;

	return 0;
}

static unsigned int m23_pm_get_freq_enable(void)
{
	return m23_gov_status.freq_enable;
}

static int m23_pm_set_freq_enable(unsigned int value)
{
	m23_gov_status.freq_enable = value;
	return 0;
}

static unsigned int m23_pm_get_mp_enable(void)
{
	return m23_gov_status.mp_enable;
}

static int m23_pm_set_ts_enable(unsigned int value)
{
	m23_gov_status.ts_enable = value;
	return 0;
}

static unsigned int m23_pm_get_ts_enable(void)
{
	return m23_gov_status.ts_enable;
}

static unsigned int m23_pm_get_gov_start(void)
{
	return m23_gov_status.start;
}

static void m23_gov_init(void)
{
	pm_m23_func = get_m23_pm_func();
	pm_m23_avs = get_m23_pm_avs();
	pm_m23_test = get_m23_pm_test();

	m23_gov_status.startup_timer = M23_GOV_START_DELAY;
	m23_gov_status.count_1s = 50;
	m23_gov_status.governor = PMS_GOV_DISABLE;
	m23_gov_status.up_threshold = HARD_UP_THRESHOLD;
	m23_gov_status.hard_up_threshold = HARD_UP_THRESHOLD;
	m23_gov_status.easy_up_threshold = EASY_UP_THRESHOLD;
	m23_gov_status.easy_count = 48;
	m23_gov_status.freqdown_count = 24;
	m23_gov_status.mpd_count = 100;
	m23_gov_status.mpd_up_threshold = 220;
	m23_gov_status.mpd_dn_threshold = 200;
	m23_gov_status.min_freq = M23_CPU_FREQ_UD;
	m23_gov_status.max_freq = M23_CPU_FREQ_ND;
	m23_gov_status.freq_enable = 0;
	if(lx_board_opt() & LX_BOARD_OPT_SLT)
	{
		m23_gov_status.mp_enable = 0;
	}
	else
	{
		m23_gov_status.mp_enable = 0;
	}
	m23_gov_status.ts_enable = 1;
	m23_gov_status.start = 0;
	memset(m23_gov_status.cpu_load, 0x0, sizeof(m23_gov_status.cpu_load));
	memset(m23_gov_status.load_dump, 0x0, sizeof(m23_gov_status.load_dump));

	return;
}

/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int m23_pm_ioctl_governor (unsigned int cmd, unsigned long arg)
{
	unsigned int status;
	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_CPU_GOV_WORK:		// 0 : Disable, 1 : Enable, 2 : Monitor
			if (arg <= 3)
			{
				m23_pm_set_gov(arg);
				m23_pm_set_startup_timer(0);
				if (arg == 0)
					pm_m23_func->set_max_performance();
			}
			break;
		case PM_GET_CPU_GOV_STATUS:	// 0 : Disable, 1 : Enable, 2: Monitor, 3: Enable & Monutor
			status = m23_pm_get_gov();
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

static pms_m23_gov_t m23_pm_gov =
{
	.init = m23_gov_init,
	.boost = m23_boost,
	.check_cpu = m23_check_cpu,
	.ioctl = m23_pm_ioctl_governor,
	.get_gov = m23_pm_get_gov,
	.get_gov_str = m23_pm_get_gov_str,
	.get_cpunum = m23_pm_get_cpunum,
	.set_gov = m23_pm_set_gov,
	.get_startup_timer = m23_pm_get_startup_timer,
	.set_startup_timer = m23_pm_set_startup_timer,
	.reset_load_monitor = m23_pm_reset_load_monitor,
	.get_load = m23_pm_get_load,
	.get_hard_up_threshold = m23_pm_get_hard_upthreshold,
	.set_hard_up_threshold = m23_pm_set_hard_upthreshold,
	.get_easy_up_threshold = m23_pm_get_easy_upthreshold,
	.set_easy_up_threshold = m23_pm_set_easy_upthreshold,
	.get_easy_count = m23_pm_get_easy_count,
	.set_easy_count = m23_pm_set_easy_count,
	.get_freqdown_count = m23_pm_get_freqdown_count,
	.set_freqdown_count = m23_pm_set_freqdown_count,
	.get_mpd_count = m23_pm_get_mpd_count,
	.set_mpd_count = m23_pm_set_mpd_count,
	.get_mpd_up_threshold = m23_pm_get_mpd_up_threshold,
	.set_mpd_up_threshold = m23_pm_set_mpd_up_threshold,
	.get_mpd_dn_threshold = m23_pm_get_mpd_dn_threshold,
	.set_mpd_dn_threshold = m23_pm_set_mpd_dn_threshold,
	.get_min_freq = m23_pm_get_min_freq,
	.set_min_freq = m23_pm_set_min_freq,
	.get_max_freq = m23_pm_get_max_freq,
	.set_max_freq = m23_pm_set_max_freq,
	.get_mp_enable = m23_pm_get_mp_enable,
	.set_mp_enable = m23_pm_set_mp_enable,
	.get_freq_enable = m23_pm_get_freq_enable,
	.set_freq_enable = m23_pm_set_freq_enable,
	.get_ts_enable = m23_pm_get_ts_enable,
	.get_ts_enable = m23_pm_get_ts_enable,
	.set_ts_enable = m23_pm_set_ts_enable,
	.get_gov_start = m23_pm_get_gov_start,
};

pms_m23_gov_t* get_m23_pm_gov(void)
{
	return &m23_pm_gov;
}

