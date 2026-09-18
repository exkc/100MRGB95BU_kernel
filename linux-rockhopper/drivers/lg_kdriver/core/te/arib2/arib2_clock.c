/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  arib2 driver clock functions
 *
 *  @author		Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version    0.1
 *  @date       2017-11-28
 *  @note       Additional information.
 */

#include "arib2_impl.h"

/* FIXME: Check all with ARIB2 */
#define CLOCK_ISR_DELAY_TICK	3

/* Clock Recovery control constants */
//#define WINDOW_SAMPLE_SIZE            50              /* sample count in window */
#define WINDOW_TICK_SIZE		2000	/* 2000ms - 60 samples per window in 33ms intreval timeinfo */
#define NUM_WINDOW			5
#define MAX_WINDOW_IDX			(NUM_WINDOW-1)

#if CONFIG_LX_BOARD_FPGA
#define MIN_TIMEINFO_INTERVAL		20	/* ms */
#define MAX_TIMEINFO_INTERVAL		50000	/* ms */

#define MAX_STABLE_JITTER_TICK		1
#define MAX_JITTER_THRESHOLD		MS_TO_TICK(50000)
#define MAX_JITTER_FOR_RESET		MS_TO_TICK(800)
#define MIN_OVERSHOOT_JITTER		MS_TO_TICK(50)	/* overshoot jitter if exceed it */
#define MAX_OVERSHOOT_JITTER		MS_TO_TICK(200)	/* strange overshoot jitter */
#else
#define MIN_TIMEINFO_INTERVAL		20	/* ms */	//TODO: Check
#define MAX_TIMEINFO_INTERVAL		5000	/* ms */	//TODO: Check

#define MAX_STABLE_JITTER_TICK		1
#define MAX_JITTER_THRESHOLD		MS_TO_TICK(5000)
#define MAX_JITTER_FOR_RESET		MS_TO_TICK(80)
#define MIN_OVERSHOOT_JITTER		MS_TO_TICK(5)	/* overshoot jitter if exceed it */
#define MAX_OVERSHOOT_JITTER		MS_TO_TICK(20)	/* strange overshoot jitter */
#endif

#define JITTER_FOR_RESET_COUNT		5
#define OVERSHOOT_JITTER_COUNT		10

#define CLK_FREQ			90000

#define BASE_INPUT_CLOCK		27000000	/* 27 MHz */

#define INPUT_CLOCK_THRESHOLD		100000	/* 100Khz */
#define MAX_INPUT_CLOCK			(BASE_INPUT_CLOCK + INPUT_CLOCK_THRESHOLD)
#define MIN_INPUT_CLOCK			(BASE_INPUT_CLOCK - INPUT_CLOCK_THRESHOLD)

#define POSITIVE_SLOPE		0x1
#define NEGATIVE_SLOPE		0x2

#define TICK_TO_MS(tick)	((tick)/90)
#define MS_TO_TICK(ms)		((ms)*90)

#ifndef abs64
#define abs64(x) ({				\
			s64 __x = (x);		\
			(__x < 0) ? -__x : __x;	\
		})
#endif

#ifndef div64
#define div64(n, div) ({	 		\
	typeof(n) _v;				\
	if((n) < 0 ) {				\
		u64 _s = (u64)(-n);		\
		do_div(_s, div);		\
		_v = (s64)(-_s);		\
	} else {				\
		_v = n;				\
		do_div(_v, div);		\
	}					\
	_v;					\
})
#endif

typedef union {
	u64 value;
	struct {
		u32 lo;
		u32 hi;
	};
} TICK64_T;

typedef struct {
	u32 base_31_0;
	u32 base_32;
} GSTCC_VALUE_T;

typedef struct {
	TICK64_T live_tick;	/* clock from signal (NTP) produced by timeinfo (isr) */
	TICK64_T system_tick;	/* clock for using recovery produced by gstcc (isr) */
	u32 capture_ms;
} CLOCK_INFO_T;

typedef struct {
	GSTCC_VALUE_T gstcc;	/* captured gstcc by isr handler or NTP parser */
	LX_ARIB2_TIME_T timeinfo;	/* clock from signal (NTP) */
	u32 capture_ms;
	u32 isr_delay;		/* adjust swtlv process delay (add to NTP clock) */
} CLOCK_ISR_INFO_T;

typedef struct {
	u32 count;		/* num of input sample in window - max = WINDOW_SAMPLE_SIZE */
	s32 sum_jitter;		/* sum of current window's jitter samples */
	u32 start_timestamp;	/* timestamp of first sample */
} RECOVERY_SAMPLE_T;

typedef struct {
	s32 jitter;		/* average value of jitter(pcr - stc) in window */
	u32 timestamp;
} RECOVERY_WINDOW_T;

typedef struct {
	s64 jitter;		/* 27MHz units */
	u32 timestamp;
} RECOVERY_WINDOW_SUM_T;

typedef struct {
	bool enable;
	u8 reset;		/* reset time info - copy timeinfo to gstc */
	u32 jitter_errors;	/* jitter count over MAX_JITTER_THRESHOLD */

	RECOVERY_SAMPLE_T sample;

	u32 window_count;	/* current window number */
	RECOVERY_WINDOW_T window_data[NUM_WINDOW];
	RECOVERY_WINDOW_T *window[MAX_WINDOW_IDX * 2];	/* in order to use linear array data */

	s32 overshoots;
} RECOVERY_CTRL_T;

typedef struct arib2_clock {
	u8 ch;
	u8 idx;
	u8 swtlv_ts_idx;	/* index for timestamp */
	s8 leap_second;		/* 0:none, -1:leap_61, 1:leap_59 */
	bool use_swtlv;

	u32 base_32;		/* wraparound detection */
	u32 tick_hi;		/* GSTCC : 32 ~ 63 */

	u64 leap_tick;
	struct hrtimer leap_timer;
	struct work_struct leap_work;

	spinlock_t spinlock;
	struct work_struct work;

	struct lx_arib2_clock_udp_info udp_info;
	RECOVERY_CTRL_T recovery;

	/* latched clock tick */
	CLOCK_INFO_T cur_info;
	CLOCK_INFO_T pre_info;
	CLOCK_ISR_INFO_T isr_info;

	bool latched;
	bool suspended;

	u32 freq;		/* target frequency */
	wait_queue_head_t wq; 	/* wait for wall clock */
	struct arib2_channel *channel;
} CLOCK_T;

static int swtlv_ntp_parser(struct arib2_channel *channel, u8 *buf, u32 len,
			    u32 timestamp);

#define clock_workqueue(c)		system_freezable_wq

static DEFINE_MUTEX(clock_mutex);

/* NTP default value */
static const LX_ARIB2_CLOCK_UDP_INFO_T default_udp_info = {
	.src_ip_v = {0x0, 0x0, 0x0, 0x0},
	.src_ip_m = {0x0, 0x0, 0x0, 0x0},
	.dst_ip_v = {0xff020000, 0x0, 0x0, 0x101},	// ff02::101
	.dst_ip_m = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff},

	.src_port_v = 456,
	.src_port_m = 0xffff,
	.dst_port_v = 123,
	.dst_port_m = 0xffff,
};

static const char *jitter_slope_str[] = { "=", "+", "-", "~" };

static void NTPToTick(LX_ARIB2_TIME_T *time, TICK64_T *tick)
{
/*
 * 1 tick
 * = 1 / 90000 sec
 * = 2^32 / 90000
 * = 47721.85884 fractions
 */

	tick->value = (u64)time->sec * 90000;
	tick->value += (time->fraction / 47722);
}

static void TickToNTP(TICK64_T *tick, LX_ARIB2_TIME_T *time)
{
	u64 v;
	u32 remainder;

	v = tick->value;
	remainder = do_div(v, 90000);

	time->sec = (u32)v;
	time->fraction = remainder * 47722;
}

static int SetClockRate(CLOCK_T *clk, u32 freq)
{
	struct te_config *cfg = te_get_config();
	int ret;

	if (!cfg->no_stcc_bug) {
		int unit_step;

		if (freq == BASE_INPUT_CLOCK) { // Prevent to divide by zero
			unit_step = 0;
		} else {
			unit_step = (BASE_INPUT_CLOCK) /
				    (s32)(freq - BASE_INPUT_CLOCK);
#if CONFIG_LX_BOARD_FPGA
			if (unit_step) {
				struct te_config *cfg = te_get_config();
				unit_step /= cfg->clk.divider;
			}
#endif
		}
		ret = TE_REG_SetGstccUnitStep(clk->idx, unit_step);
	} else {

		ret = te_ipc_set_stcc_freq(clk->idx, freq);

	}
	return ret;
}

/* check: protected by mutex clock_mutex */
static void _SetClockTick(CLOCK_T *clk, TICK64_T *tick)
{
	struct te_config *cfg = te_get_config();
	u32 base_32, base_31_0;

	base_32 = tick->hi & 0x1;
	base_31_0 = tick->lo;

	if (!cfg->no_stcc_bug) {
		TE_REG_SetGstcc(clk->idx, base_32, base_31_0, 0);
	} else {
		te_ipc_set_gstcc(clk->idx, base_32, base_31_0);
	}

	clk->tick_hi = tick->hi;
	clk->base_32 = base_32;

	log_noti("_SetClockTick(ch:%d,hi:0x%x,lo:0x%08x)= %llu",
		 clk->ch, tick->hi, tick->lo, tick->value);
}

/* CHECK: protected by mutex clock_mutex */
static void _GetClockTick(CLOCK_T *clk, TICK64_T *tick)
{
	struct te_config *cfg = te_get_config();
	u32 base_32, base_31_0, ext;

	if (!cfg->no_stcc_bug) {
		TE_REG_GetGstcc(clk->idx, &base_32, &base_31_0, &ext);
	} else {
		te_ipc_get_gstcc(clk->idx, &base_32, &base_31_0);
	}

	// Make upper 32bit tick by comparing base_32
	if (clk->base_32 != base_32) {	/* check wrap-around */
		clk->tick_hi++;
		clk->base_32 = base_32;

		log_noti("CH[%d] gstcc wraparound - hi:0x%x, lo:0x%08x",
			 clk->ch, clk->tick_hi, base_31_0);
	}

	tick->hi = clk->tick_hi;
	tick->lo = base_31_0;
}

static void ResetJitterSample(RECOVERY_SAMPLE_T *s)
{
	s->count = 0;
	s->sum_jitter = 0;
}

static void RestartGatherClockInfo(RECOVERY_CTRL_T *r)
{
	r->overshoots = 0;
	r->window_count = 0;
}

static void ResetClockRecovery(CLOCK_T *clk)
{
	RECOVERY_CTRL_T *r = &clk->recovery;

	clk->freq = BASE_INPUT_CLOCK;
	SetClockRate(clk, BASE_INPUT_CLOCK);

	RestartGatherClockInfo(r);
	ResetJitterSample(&r->sample);

	r->reset = true;
	r->jitter_errors = 0;
}

/* CHECK: protected by mutex clock_mutex */
static void _AdjustClockTick(CLOCK_T *clk, int value, TICK64_T *tick)
{
	struct te_config *cfg = te_get_config();
	unsigned long flag;

	/* added interrupt disable to reduce the latency between _GetClockTick
	 * and _SetClockTick because the parameter value is a relative tick
	 * from the current time tick */
	if (!cfg->no_stcc_bug) {
		local_irq_save(flag);
		_GetClockTick(clk, tick);
		tick->value += value;
		_SetClockTick(clk, tick);
		local_irq_restore(flag);

	} else {
		_GetClockTick(clk, tick);
		tick->value += value;
		_SetClockTick(clk, tick);
	}

}

static void LeapSecondCallbackWork(struct work_struct *work)
{
	CLOCK_T *clk;
	TICK64_T tick;

	clk = container_of(work, CLOCK_T, leap_work);

	mutex_lock(&clock_mutex);
	if (clk->leap_second) {
		int adjust = -((s32)clk->leap_second * CLK_FREQ);
		_AdjustClockTick(clk, adjust, &tick);

		log_noti("CH[%d] leap second(%d), tick(%llu)",
			 clk->ch, clk->leap_second, tick.value);
		clk->leap_second = 0;
	}
	mutex_unlock(&clock_mutex);
}

static enum hrtimer_restart LeapSecondTimerCallback(struct hrtimer *timer)
{
	CLOCK_T *clk;

	clk = container_of(timer, CLOCK_T, leap_timer);

	queue_work(clock_workqueue(clk), &clk->leap_work);

	return HRTIMER_NORESTART;
}

static int swtlv_clock_callback(void *arg, u32 timestamp, void *data, u32 len)
{
	struct arib2_channel *channel = arg;
	u8 *buf = data;

	return swtlv_ntp_parser(channel, buf, len, timestamp);
}

static void GetLatchedNTPInfo(CLOCK_T *clk)
{
	struct arib2_config *chip_cfg = arib2_get_config();
	unsigned long flag;
	CLOCK_INFO_T *clk_info = &clk->cur_info;
	CLOCK_ISR_INFO_T *isr_info = &clk->isr_info;
	TICK64_T tick;

	spin_lock_irqsave(&clk->spinlock, flag);

	clk_info->capture_ms = isr_info->capture_ms;

	NTPToTick(&isr_info->timeinfo, &clk_info->live_tick);	/* NTP => GSTCC */
	_GetClockTick(clk, &tick);

	if (chip_cfg->swtlv) {	// adjust swtlv process delay
		clk_info->live_tick.value += isr_info->isr_delay;
	}

	clk_info->system_tick.hi = clk->tick_hi;

	// system_tick.high should be adjusted once again since clk->tick_hi can be accumulated
	// by _GetClockTick function (restore original value)
	if (clk->base_32 != isr_info->gstcc.base_32) {	/* check wrap-around */
		log_noti("wraparound after gstcc latch\n");
		clk_info->system_tick.hi--;
	}
	clk_info->system_tick.lo = isr_info->gstcc.base_31_0;

	spin_unlock_irqrestore(&clk->spinlock, flag);
}

static void AddJitterSample(RECOVERY_SAMPLE_T *s, CLOCK_INFO_T *info,
			    s32 jitter)
{
#ifdef WINDOW_SAMPLE_SIZE
	if (s->count >= WINDOW_SAMPLE_SIZE) {
		LOG_WARNING("abnormal sample count(%d)\n", s->count);
		ResetJitterSample(s);
		return;
	}
#endif

	if (s->count == 0) {
		s->start_timestamp = info->capture_ms;
	}
	s->sum_jitter += jitter;
	s->count++;
}

#if (NUM_WINDOW == 5)
#define NUM_WINDOW_HALF		3
#define LEFT_WINDOW_MAX_IDX	2
#define RIGHT_WINDOW_MIN_IDX	2
#else
#error "define left & right window macros"
#endif
static void GetTwoWindowFromList(RECOVERY_WINDOW_T **list,
				 RECOVERY_WINDOW_SUM_T *left,
				 RECOVERY_WINDOW_SUM_T *right)
{
	RECOVERY_WINDOW_T *a;
	s64 jitter[2] = { 0, 0 };
	u32 timestamp[2] = { 0, 0 };
	int i;

	for (i = 0; i <= MAX_WINDOW_IDX; i++) {
		a = list[i];

		if (i <= LEFT_WINDOW_MAX_IDX) {
			jitter[0] += a->jitter;

			if (i == 0)
				timestamp[0] = a->timestamp;
			else if (i == LEFT_WINDOW_MAX_IDX)
				timestamp[0] +=
				    ((a->timestamp - timestamp[0]) / 2);
		}

		if (i >= RIGHT_WINDOW_MIN_IDX) {
			jitter[1] += a->jitter;

			if (i == RIGHT_WINDOW_MIN_IDX)
				timestamp[1] = a->timestamp;
			else if (i == MAX_WINDOW_IDX)
				timestamp[1] +=
				    ((a->timestamp - timestamp[1]) / 2);
		}
	}

	left->jitter = div64(jitter[0] * 300, NUM_WINDOW_HALF);
	left->timestamp = timestamp[0];

	right->jitter = div64(jitter[1] * 300, NUM_WINDOW_HALF);
	right->timestamp = timestamp[1];
}

static s32 AdjustWithSlope(CLOCK_T *clk, u32 sign_of_slope,
			   u32 abs_jitter_avg, RECOVERY_WINDOW_T **list)
{
	RECOVERY_WINDOW_T *w;
	bool adjust = false;
	s32 adjust_clk;
	int i;

	/* Ignore Condition */
	if (abs_jitter_avg < MAX_STABLE_JITTER_TICK) {
		log_timeinfo("CH[%d] stable jitter(%d) - do nothing", clk->ch,
			     abs_jitter_avg);

		return 0;
	}

	w = list[MAX_WINDOW_IDX];	/* last window to find jitter position */
	if ((sign_of_slope == POSITIVE_SLOPE && w->jitter > 0) ||	//steadily increased
	    (sign_of_slope == NEGATIVE_SLOPE && w->jitter < 0))	//steadily decreased
	{
		adjust = true;
	}

	if (adjust == true) {
		struct {
			u32 jitter;	/* 27Mhz units */
			u32 amp;	/* percetage */
		} adjust_amplifer[] = {
			{5 * 27000, 20},	/* >= 5ms - 20% */
			{3 * 27000, 16},	/* >= 3ms - 16% */
			{1 * 27000, 12},	/* >= 1ms - 12% */
			{2 * 2700, 6},	/* >= 200us - 6% */
			{5 * 270, 3},	/* >= 50us - 3% */
		};
		RECOVERY_WINDOW_SUM_T left, right;
		u64 abs_jitter;
		s64 delta;
		u32 base, amp = 0;

		GetTwoWindowFromList(list, &left, &right);

		abs_jitter = abs64(right.jitter);
		for (i = 0; i < ARRAY_SIZE(adjust_amplifer); i++) {
			if (abs_jitter >= adjust_amplifer[i].jitter) {
				amp = adjust_amplifer[i].amp;
				break;
			}
		}

		/* ADJUST CLOCK(HZ) = (jitter * 1000 / time) * (1 + amplifier)
		 * jitter = jitter[R] - jitter[L] : 27MHz units
		 * time = time[R] - time[L] : ms unit */
		delta = (s64)(right.jitter - left.jitter) * (10 * (100 + amp));
		base = right.timestamp - left.timestamp;

		adjust_clk = div64(delta, base);
		log_timeinfo
		    ("CH[%d] Adjust Clock[%dHz] - jitter slope : L[%lld] R[%lld] amp[%d%%]",
		     clk->ch, adjust_clk, left.jitter, right.jitter, amp);
	} else {
		// waiting
		log_timeinfo("CH[%d] %s slope and jitter get close to 0",
			     clk->ch,
			     (sign_of_slope ==
			      POSITIVE_SLOPE) ? "positive" : "negative");

		adjust_clk = 0;
	}

	return adjust_clk;
}

static s32 AdjustWithOvershoot(CLOCK_T *clk, u32 abs_jitter_avg,
			       RECOVERY_WINDOW_T **list)
{
	int i;
	s32 jitter, adjust_clk;
	s32 overshoots = 0;
	RECOVERY_CTRL_T *r = &clk->recovery;

	/* Ignore Condition */
	if (abs_jitter_avg < MIN_OVERSHOOT_JITTER) {
		log_timeinfo("CH[%d] stable jitter(%d) - do nothing", clk->ch,
			     abs_jitter_avg);

		r->overshoots = 0;
		return 0;
	}

	for (i = 0; i <= MAX_WINDOW_IDX; i++) {
		jitter = list[i]->jitter;

		if (jitter > MIN_OVERSHOOT_JITTER)
			overshoots++;
		else if (jitter < -MIN_OVERSHOOT_JITTER)
			overshoots--;
	}

	if (abs(overshoots) > MAX_WINDOW_IDX) {
		RECOVERY_WINDOW_SUM_T left, right;
		s64 delta;
		u32 base;
		bool adjust = false;

		GetTwoWindowFromList(list, &left, &right);

		log_timeinfo("CH[%d] jitter[R](%lld) - jitter[L](%lld) = %lld",
			     clk->ch, right.jitter, left.jitter,
			     (right.jitter - left.jitter));

		/* adjust for jitter divergence */
		if (abs64(right.jitter) > abs64(left.jitter))
			adjust = true;

		if (adjust == true) {
			/* ADJUST CLOCK(HZ) = (jitter * 1000 / time) * 1.20
			 * jitter = jitter[R] - jitter[L] : 27MHz units
			 * time = time[R] - time[L] : ms unit */

			delta = (s64)(right.jitter - left.jitter) * (10 * 120);
			base = right.timestamp - left.timestamp;
			adjust_clk = div64(delta, base);
			log_timeinfo("CH[%d] Overshoot - Adjust Clock[%dHz]",
				     clk->ch, adjust_clk);
		} else {
			r->overshoots += ((overshoots > 0) ? 1 : -1);
			log_timeinfo("CH[%d] Stable Overshoot(%d)...\n",
				     clk->ch, r->overshoots);

			adjust_clk = 0;
			if (abs(r->overshoots) > OVERSHOOT_JITTER_COUNT) {
				if (abs64(left.jitter) >
				    (MAX_OVERSHOOT_JITTER * 300)
				    && abs64(right.jitter) >
				    (MAX_OVERSHOOT_JITTER * 300)) {
					log_timeinfo
					    ("CH[%d] Big Overshoots... Adjust 2KHz\n",
					     clk->ch);
					adjust_clk = (overshoots > 0) ? 2000 : -2000;	/* adjust 2KHz */
				}
			}
		}
	} else {
		r->overshoots = 0;
		adjust_clk = 0;
	}

	return adjust_clk;
}

static int ClockRecoveryProcessWindow(CLOCK_T *clk, s32 jitter, u32 timestamp)
{
	RECOVERY_WINDOW_T *w, *a, *b;
	RECOVERY_CTRL_T *r = &clk->recovery;
	u32 wcount, idx;
	u32 sign_of_slope, abs_jitter_avg;
	s32 adjust_clk;
	int i;

	wcount = r->window_count;
	r->window_count++;

	idx = wcount % NUM_WINDOW;
	w = &r->window_data[idx];

	w->jitter = jitter;
	w->timestamp = timestamp;

	if (wcount < MAX_WINDOW_IDX) {	/* not sufficient window gathering */
		r->window[wcount] = w;
		return 0;
	}

	idx = wcount % MAX_WINDOW_IDX;	/* start index of window */
	r->window[idx + MAX_WINDOW_IDX] = w;	/* save the current window */

	/* calucarate sign of jitter slope & sum of jitter */
	sign_of_slope = 0;

	a = r->window[idx];
	abs_jitter_avg = abs(a->jitter);

	for (i = 1; i <= MAX_WINDOW_IDX; i++) {
		b = r->window[idx + i];

		if (b->jitter > a->jitter) {
			sign_of_slope |= POSITIVE_SLOPE;
		} else if (b->jitter < a->jitter) {
			sign_of_slope |= NEGATIVE_SLOPE;
		}

		abs_jitter_avg += abs(b->jitter);

		a = b;
	}
	abs_jitter_avg /= NUM_WINDOW;

	log_timeinfo("CH[%d] W[%u] jitter[%d %d %d %d %d] slope[%s]\n",
		     clk->ch, wcount,
		     r->window[idx + 0]->jitter, r->window[idx + 1]->jitter,
		     r->window[idx + 2]->jitter, r->window[idx + 3]->jitter,
		     r->window[idx + 4]->jitter,
		     jitter_slope_str[sign_of_slope]);

	if (sign_of_slope == POSITIVE_SLOPE || sign_of_slope == NEGATIVE_SLOPE) {
		/* CASE1 : Constantly increased or decreased */
		adjust_clk = AdjustWithSlope(clk, sign_of_slope, abs_jitter_avg,
					     &r->window[idx]);
	} else {
		/* CASE2 : Complex slope behavior */
		adjust_clk = AdjustWithOvershoot(clk, abs_jitter_avg,
						 &r->window[idx]);
	}

	if (adjust_clk) {
		u32 new_freq = clk->freq + adjust_clk;

		if (new_freq > MAX_INPUT_CLOCK)
			new_freq = MAX_INPUT_CLOCK;
		else if (new_freq < MIN_INPUT_CLOCK)
			new_freq = MIN_INPUT_CLOCK;

		SetClockRate(clk, new_freq);
		RestartGatherClockInfo(r);

		clk->freq = new_freq;
	} else {
		r->window[idx] = w;	/* save to make the linear array */
	}

	return 0;
}

static void ClockRecoveryWorkManual(CLOCK_T *clk)
{
	RECOVERY_CTRL_T *r = &clk->recovery;
	CLOCK_INFO_T *info = &clk->cur_info;
	CLOCK_INFO_T *pre_info;
	RECOVERY_SAMPLE_T *s;
	u32 timestamp, time_interval, elapsed;
	s64 jitter64;
	s32 jitter;

	log_debug("(DEBUG) NTP arrived");

	GetLatchedNTPInfo(clk);

	if (r->reset) {
		TICK64_T tick;
		struct te_time tm;

		te_tick_to_time(info->live_tick.value, CLK_FREQ, NTP_EPOCH_TIME,
				&tm);

		log_noti("1st live clock(%s),tick(%llu) is arrived",
			 te_get_readable_time(&tm), info->live_tick.value);

		tick.value = info->live_tick.value + CLOCK_ISR_DELAY_TICK;

		_SetClockTick(clk, &tick);

		clk->latched = true;
		r->reset = false;
		wake_up(&clk->wq);

		/* save current info */
		clk->pre_info = clk->cur_info;
		return;
	}

	pre_info = &clk->pre_info;

	time_interval = info->capture_ms - pre_info->capture_ms;
	if (time_interval < MIN_TIMEINFO_INTERVAL) {
		return;
	}

	if (time_interval > MAX_TIMEINFO_INTERVAL) {
		log_noti("discontinuous time info...\n");
		ResetClockRecovery(clk);
		return;
	}

	jitter64 = info->live_tick.value - info->system_tick.value;
	jitter = (s32)jitter64;

	log_timeinfo
	    ("CH[%d] %5dKHz(%dHz) LIVE:[%llu]-SYSTEM:[%llu]=[%lld](%dms)\n",
	     clk->ch, clk->freq / 1000, clk->freq - BASE_INPUT_CLOCK,
	     info->live_tick.value, info->system_tick.value, jitter64,
	     TICK_TO_MS(jitter));

	if (abs64(jitter64) > MAX_JITTER_THRESHOLD) {
		log_noti("CH[%d] TOO BIG JITTER => RESET\n", clk->ch);
		ResetClockRecovery(clk);
		return;
	}

	if (abs(jitter) > MAX_JITTER_FOR_RESET) {
		r->jitter_errors++;
		if (r->jitter_errors >= JITTER_FOR_RESET_COUNT) {
			log_noti("CH[%d] JITTER ERRORS => RESET\n", clk->ch);
			ResetClockRecovery(clk);
		}
		return;
	}
	if (r->jitter_errors)
		r->jitter_errors--;

	s = &r->sample;
	AddJitterSample(s, info, jitter);

	elapsed = info->capture_ms - s->start_timestamp;
#ifdef WINDOW_SAMPLE_SIZE
	if (s->count < WINDOW_SAMPLE_SIZE) {
		// wait...
	}
#else
	if (elapsed < WINDOW_TICK_SIZE) {

	}
#endif
	else {
		jitter = s->sum_jitter / (s32)s->count;
		timestamp = s->start_timestamp + elapsed / 2;

		ClockRecoveryProcessWindow(clk, jitter, timestamp);

		ResetJitterSample(s);
	}

	/* save current info */
	clk->pre_info = clk->cur_info;
}

static void SetLeapTimer(CLOCK_T *clk)
{
	u32 leap_indicator = clk->isr_info.timeinfo.leap_indicator;

	if (leap_indicator == 1 || leap_indicator == 2) {
		TICK64_T tick;
		u64 minutes;
		u32 adjust_seconds, remained_tick;
		u32 secs, nsecs;
		ktime_t ktime;

		_GetClockTick(clk, &tick);

		minutes = tick.value;
		do_div(minutes, (CLK_FREQ * 60));	// current minutes

		if (leap_indicator == 1) {
			clk->leap_second = 1;
			adjust_seconds = 60;
		} else {
			clk->leap_second = -1;
			adjust_seconds = 59;
		}

		clk->leap_tick = (minutes * 60 + adjust_seconds) * CLK_FREQ;	// The leap second

		if (clk->leap_tick <= tick.value) {
			clk->leap_tick += (60 * CLK_FREQ);
		}

		remained_tick = (u32)(clk->leap_tick - tick.value);

		secs = remained_tick / CLK_FREQ;
		nsecs = ((remained_tick % CLK_FREQ) * 10000 / 9) * 10;

		ktime = ktime_set(secs, nsecs);
		hrtimer_start(&clk->leap_timer, ktime, HRTIMER_MODE_REL);

		log_noti
		    ("CH[%d] leap second=%d, tick=%llu, secs=%u, nsecs=%u\n",
		     clk->ch, clk->leap_second, clk->leap_tick, secs, nsecs);
	}

}

static void ClockRecoveryWork(struct work_struct *work)
{
	CLOCK_T *clk;

	clk = container_of(work, CLOCK_T, work);

	mutex_lock(&clock_mutex);
	if (clk->recovery.enable != true) {
		log_timeinfo("CH[%d] Clock recovery is not started", clk->ch);
		goto exit;
	}

	ClockRecoveryWorkManual(clk);
	SetLeapTimer(clk);

 exit:
	mutex_unlock(&clock_mutex);
}

static void ClockIrqHandler(struct arib2_channel *channel)
{
	struct te_config *cfg = te_get_config();
	struct te_reg_arib2_ntp_info timestamp;
	u32 base_32, base_31_0, ext;
	CLOCK_T *clk = channel->clock;
	CLOCK_ISR_INFO_T *isr_info = &clk->isr_info;
	int rc;

	rc = te_reg_arib2_get_ntp_info(channel->num, &timestamp);
	CHECK_ERROR(rc != 0, return, "Error in get_ntp_info [%d]", rc);

	if (!cfg->no_stcc_bug) {
		TE_REG_GetLatchedGstcc(clk->idx, &base_32, &base_31_0, &ext);
	} else {
		te_ipc_get_gstcc(clk->idx, &base_32, &base_31_0);
	}

	spin_lock(&clk->spinlock);

	isr_info->capture_ms = (u32)te_get_ms_tick();
	isr_info->gstcc.base_31_0 = base_31_0;
	isr_info->gstcc.base_32 = base_32;

	isr_info->timeinfo.sec = timestamp.sec;
	isr_info->timeinfo.fraction = timestamp.fraction;
	isr_info->timeinfo.leap_indicator = timestamp.leap_indicator;
	isr_info->isr_delay = 0;

	spin_unlock(&clk->spinlock);

	te_reg_dumper_set_latch_enable(clk->ch, true);

	queue_work(clock_workqueue(clk), &clk->work);
}

static void EnableClockRecovery(CLOCK_T *clk)
{
	struct te_config *cfg = te_get_config();
	int ret;

	if (!clk->use_swtlv) {
		struct lx_arib2_clock_udp_info *info = &clk->udp_info;

		te_reg_arib2_set_ntp_src_addr(clk->ch, info->src_ip_v,
					      info->src_ip_m);
		te_reg_arib2_set_ntp_dst_addr(clk->ch, info->dst_ip_v,
					      info->dst_ip_m);
		te_reg_arib2_set_udp_port_val(clk->ch, info->src_port_v,
					      info->dst_port_v);
		te_reg_arib2_set_udp_port_mask(clk->ch, info->src_port_m,
					       info->dst_port_m);
	} else {
		arib2_swtlv_register_data_callback(clk->channel,
						   swtlv_clock_callback,
						   clk->channel);
	}

	/* Start Clock Recovery */
	if (!cfg->no_stcc_bug) {
		TE_REG_SetGstccMode(clk->idx, GSTCC_MODE_UNITSTEP);
	}
	ResetClockRecovery(clk);

	if (!clk->use_swtlv) {
		ret = te_reg_arib2_set_ntp_conf(clk->ch, true, false);	//Reset is not required
		CHECK_ERROR(ret != 0,, "Error in set_ntp_conf[%d]", ret);

		te_reg_dumper_set_latch_enable(clk->ch, true);

		te_reg_dumper_set_intr_enable(DUMPER_INTR_TIMESTAMP_CH0 <<
					      (clk->ch), true);
	}

	clk->latched = false;
	clk->recovery.enable = true;
}

static void DisableClockRecovery(CLOCK_T *clk)
{
	struct te_config *cfg = te_get_config();

	if (!clk->use_swtlv) {
		u32 v = DUMPER_INTR_TIMESTAMP_CH0;
		te_reg_dumper_set_intr_enable(v << (clk->ch), false);
	} else {
		arib2_swtlv_register_data_callback(clk->channel, NULL, NULL);
	}

	if (!cfg->no_stcc_bug) {
		TE_REG_SetGstccMode(clk->idx, GSTCC_MODE_EXTINCR);
	}

	clk->latched = false;
	clk->recovery.enable = false;
	clk->leap_second = 0;
}

static int SetClock(CLOCK_T *clk, LX_ARIB2_TIME_T *time)
{
	TICK64_T tick;

	NTPToTick(time, &tick);

	_SetClockTick(clk, &tick);

	return 0;
}

static int GetClock(CLOCK_T *clk, LX_ARIB2_TIME_T *time)
{
	TICK64_T tick;

	_GetClockTick(clk, &tick);
	time->latched = clk->latched;

	TickToNTP(&tick, time);

	return 0;
}

static void disable_other_clock(struct arib2_clock *clk)
{
	struct arib2_device *dev = clk->channel->dev;
	struct arib2_clock *clk2; //check others (need disable)
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		clk2 = dev->channels[i].clock;
		if (clk2 == clk)
			continue;

		if (clk2->recovery.enable) {
			log_warning("ch[%d] clk enabled -> disable (req:%d)",
				    i, clk->channel->num);
			DisableClockRecovery(clk2);
			break;	//done
		}
	}
}

static int SetClockRecovery(CLOCK_T *clk, enum lx_arib2_clock_recovery cmd)
{
	struct te_config *cfg = te_get_config();
	int ret;

	switch (cmd) {
	case LX_ARIB2_CLOCK_RECOVERY_ENABLE:
		disable_other_clock(clk);
		if (!cfg->no_stcc_bug) {
			TE_REG_SetGstccLatchSource(clk->ch, clk->idx);
		}

		EnableClockRecovery(clk);
		ret = 0;
		break;

	case LX_ARIB2_CLOCK_RECOVERY_DISABLE:
		if (clk->recovery.enable) {
			DisableClockRecovery(clk);
		}
		ret = 0;
		break;

	case LX_ARIB2_CLOCK_RECOVERY_RESET:
		if (clk->recovery.enable) {
			DisableClockRecovery(clk);
			EnableClockRecovery(clk);
		}
		ret = 0;
		break;

	default:
		ret = -EINVAL;
		log_error("Invalid Command[%d]", cmd);
		break;
	}

	return ret;
}

int arib2_clock_irq_handler(struct arib2_device *dev, u32 val)
{
	int i;
	struct arib2_channel *channel;
	u32 intr_mask[4] = {
		DUMPER_INTR_TIMESTAMP_CH0, DUMPER_INTR_TIMESTAMP_CH1,
		DUMPER_INTR_TIMESTAMP_CH2, DUMPER_INTR_TIMESTAMP_CH3
	};

	if ((val & DUMPER_INTR_TIMESTAMP_MASK)) {
		for (i = 0; i < 4; i++) {
			if (val & intr_mask[i]) {
				channel = arib2_get_channel(dev, i);
				if (!channel)
					continue;

				ClockIrqHandler(channel);
			}
		}
	}

	return 0;
}

int arib2_set_clock_recovery(struct arib2_channel *channel,
			     enum lx_arib2_clock_recovery param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = SetClockRecovery(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_set_clock_recovery(struct arib2_fh *fh, void *arg)
{
	int rc;
	LX_ARIB2_CLOCK_CONTROL_T *param = arg;
	CLOCK_T *clk = fh->channel->clock;

	rc = SetClockRecovery(clk, param->cmd);

	return rc;
}

int arib2_get_time(struct arib2_channel *channel, struct lx_arib2_time *param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = GetClock(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_get_time(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_TIME_T *param = arg;
	CLOCK_T *clk = fh->channel->clock;
	int rc;

	rc = GetClock(clk, param);
	CHECK_ERROR(rc, return rc, "Error in GetClock");

	return 0;
}

int arib2_set_time(struct arib2_channel *channel, struct lx_arib2_time *param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = SetClock(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_set_time(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_TIME_T *param = arg;
	CLOCK_T *clk = fh->channel->clock;
	int rc;

	rc = SetClock(clk, param);
	CHECK_ERROR(rc != 0, return rc, "Error in SetClock");

	return 0;
}

unsigned int arib2_wait_clock(struct arib2_channel *channel, struct file *file,
			      struct poll_table_struct *wait)
{
	struct arib2_clock *clk = channel->clock;
	unsigned int mask = 0;

	poll_wait(file, &clk->wq, wait);

	if (clk->latched) {
		mask |= (POLLIN | POLLRDNORM | POLLPRI);
	}

	return mask;
}

static int swtlv_ntp_parser(struct arib2_channel *channel, u8 *buf, u32 len,
			    u32 timestamp)
{
//NTP parsing parameters
#define TLV_START				0
#define TLV_HDR_LEN				4
#define IPV6_START				(TLV_START + TLV_HDR_LEN)
#define IPV6_HDR_LEN				40
#define UDP_START				(IPV6_START + IPV6_HDR_LEN)
#define UDP_HDR_LEN				8
#define NTP_START				(UDP_START + UDP_HDR_LEN)

	struct te_config *cfg = te_get_config();
	CLOCK_T *clk;
	CLOCK_ISR_INFO_T *isr_info;
	LX_ARIB2_CLOCK_UDP_INFO_T *udp;
	u8 ntp_hdr, leap, ver, mode;
	u32 base_32, base_31_0, ext;
	u32 diff_32, diff_31_0, diff_ext;
	u32 isr_delay;
	u32 sec, frac;
	u32 offset;
	unsigned long flag;
	int i;

	clk = channel->clock;
	isr_info = &clk->isr_info;

	if (clk->recovery.enable != true)
		return 0;	//return immediately if not enabled

	/* Error Check */
	CHECK_ERROR(buf[TLV_START + 0] != 0x7F, return -1,
		    "invalid magic[0x%02x]", buf[0]);

	if (len < (NTP_START + 48))
		return 0;	//Not enough length
	/* Parser before NTP */
	if (buf[TLV_START + 1] != 0x02)
		return 0;	// Packet_type = IPv6
	if (buf[IPV6_START + 6] != 0x11)
		return 0;	// Next Header = UDP

	udp = &clk->udp_info;
	for (i = 0; i < 4; i++) {
		// Source IP Check
		offset = IPV6_START + 8 + i * 4;
		if ((TE_GET32(buf + offset) & udp->src_ip_m[i]) !=
		    (udp->src_ip_v[i] & udp->src_ip_m[i]))
			return 0;

		// Destination IP Check
		offset = IPV6_START + 24 + i * 4;
		if ((TE_GET32(buf + offset) & udp->dst_ip_m[i]) !=
		    (udp->dst_ip_v[i] & udp->dst_ip_m[i]))
			return 0;
	}

	if ((TE_GET16(buf + (UDP_START + 0)) & udp->src_port_m) !=
	    (udp->src_port_v & udp->src_port_m))
		return 0;	// source port
	if ((TE_GET16(buf + (UDP_START + 2)) & udp->dst_port_m) !=
	    (udp->dst_port_v & udp->dst_port_m))
		return 0;	// destination port

	/* Parser for NTP */
	ntp_hdr = buf[NTP_START + 0];
	leap = (ntp_hdr >> 6) & 0x3;
	ver = (ntp_hdr >> 3) & 0x7;
	mode = (ntp_hdr) & 0x7;

	CHECK_ERROR(ver != 4
		    || mode != 5, return -1, "error NTP ver[%d] mode[%d]", ver,
		    mode);

	/* Calculate NTP and system clock */
	sec = TE_GET32(buf + (NTP_START + 40));
	frac = TE_GET32(buf + (NTP_START + 44));

	mutex_lock(&clock_mutex);
	spin_lock_irqsave(&clk->spinlock, flag);

	if (!cfg->no_stcc_bug) {
		TE_REG_GetGstcc(clk->swtlv_ts_idx, &diff_32, &diff_31_0,
				&diff_ext);	//NEW (for diff)
		TE_REG_GetGstcc(clk->idx, &base_32, &base_31_0, &ext);	//clock recovery
	} else {
		//TODO: implement
		diff_31_0 = 0;
		base_32 = 0;
		base_31_0 = 0;
		log_error("BUGFIX: Implement!");
	}

	isr_delay = (u32)(diff_31_0 - timestamp);

	isr_info->capture_ms = (u32)te_get_ms_tick();
	isr_info->gstcc.base_31_0 = base_31_0;
	isr_info->gstcc.base_32 = base_32;

	isr_info->timeinfo.sec = sec;
	isr_info->timeinfo.fraction = frac;
	isr_info->timeinfo.leap_indicator = leap;
	isr_info->isr_delay = isr_delay;	//for 1st live clock adjust

	spin_unlock_irqrestore(&clk->spinlock, flag);
	mutex_unlock(&clock_mutex);

	queue_work(clock_workqueue(clk), &clk->work);

	return 0;
}

/*------------------------------------------------------------------------------
 *   Debug Functions
 *----------------------------------------------------------------------------*/

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_ID_RECOVERY = 0,
	DEBUG_ID_LATCHED,
	DEBUG_ID_TIME,
	DEBUG_ID_TICK,
	DEBUG_ID_SRC_IP,
	DEBUG_ID_DST_IP,
	DEBUG_ID_SRC_PORT,
	DEBUG_ID_DST_PORT,
	DEBUG_ID_MAX,
};

static int debug_show_clock_status(struct arib2_device *dev, struct seq_file *m)
{
	int i;
	TICK64_T tick;
	struct te_time tm;

	dprintf("Clock Status\n");
	dprintf("%3s %3s %2s %5s %15s %23s\n",
		"Num", "Idx", "En", "Latch", "Tick", "Time(UTC)");

	mutex_lock(&clock_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		struct arib2_clock *c = dev->channels[i].clock;
		if (!c)
			continue;

		_GetClockTick(c, &tick);

		te_tick_to_time(tick.value, CLK_FREQ, NTP_EPOCH_TIME, &tm);

		dprintf("[%d] %3d %2d %5d %15llu %23s\n", i, c->idx,
			c->recovery.enable, c->latched, tick.value,
			te_get_readable_time(&tm));
	}
	mutex_unlock(&clock_mutex);

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct arib2_clock *clk = item->private;
	LX_ARIB2_CLOCK_UDP_INFO_T *u;
	struct lx_arib2_time time;
	TICK64_T tick;

	switch (item->flags) {
	case DEBUG_ID_RECOVERY:
		dprintf("%d\n", clk->recovery.enable);
		break;
	case DEBUG_ID_LATCHED:
		dprintf("%d\n", clk->latched);
		break;
	case DEBUG_ID_TIME:
		mutex_lock(&clock_mutex);
		ret = GetClock(clk, &time);
		mutex_unlock(&clock_mutex);
		if (!ret) {
			struct te_time tm;

			te_tick_to_time(time.sec, 1, NTP_EPOCH_TIME, &tm);
			tm.msec = ((__u64)time.fraction * 1000) >> 32;

			dprintf("%u(sec) %u(frac) - %s\n",
				time.sec, time.fraction,
				te_get_readable_time(&tm));
		}
		break;
	case DEBUG_ID_TICK:
		mutex_lock(&clock_mutex);
		_GetClockTick(clk, &tick);
		mutex_unlock(&clock_mutex);
		dprintf("%llu\n", tick.value);
		break;
	case DEBUG_ID_SRC_IP:
		u = &clk->udp_info;
		dprintf("value: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			u->src_ip_v[0], u->src_ip_v[1],
			u->src_ip_v[2], u->src_ip_v[3]);
		dprintf("mask : 0x%08x 0x%08x 0x%08x 0x%08x\n",
			u->src_ip_m[0], u->src_ip_m[1],
			u->src_ip_m[2], u->src_ip_m[3]);
		break;
	case DEBUG_ID_DST_IP:
		u = &clk->udp_info;
		dprintf("value: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			u->dst_ip_v[0], u->dst_ip_v[1],
			u->dst_ip_v[2], u->dst_ip_v[3]);
		dprintf("mask : 0x%08x 0x%08x 0x%08x 0x%08x\n",
			u->dst_ip_m[0], u->dst_ip_m[1],
			u->dst_ip_m[2], u->dst_ip_m[3]);
		break;
	case DEBUG_ID_SRC_PORT:
		u = &clk->udp_info;
		dprintf("value:%d\n", u->src_port_v);
		dprintf("mask :0x%04x\n", u->src_port_m);
		break;
	case DEBUG_ID_DST_PORT:
		u = &clk->udp_info;
		dprintf("value:%d\n", u->dst_port_v);
		dprintf("mask :0x%04x\n", u->dst_port_m);
		break;
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static void debug_write_ip(CLOCK_T *clk, const char *command, u8 type)
{
	int rc;
	LX_ARIB2_CLOCK_UDP_INFO_T *u;
	u32 val[4], mask[4];

	rc = sscanf(command, "%x %x %x %x %x %x %x %x",
		    &val[0], &val[1], &val[2], &val[3],
		    &mask[0], &mask[1], &mask[2], &mask[3]);

	if (rc == 1 && val[0] == 0)	//mask, val is not needed
	{
		memset(val, 0, sizeof(u32) * 4);
		memset(mask, 0, sizeof(u32) * 4);
	} else if (rc == 4)	//only mask setting
	{
		memset(mask, 0xFFFFFFFF, sizeof(u32) * 4);
	} else if (rc != 8) {
		goto usage;
	}

	u = &clk->udp_info;

	if (type == DEBUG_ID_SRC_IP) {
		memcpy(u->src_ip_v, val, sizeof(u32) * 4);
		memcpy(u->src_ip_m, mask, sizeof(u32) * 4);
	} else {
		memcpy(u->dst_ip_v, val, sizeof(u32) * 4);
		memcpy(u->dst_ip_m, mask, sizeof(u32) * 4);
	}

	return;

 usage:
	printk(KERN_ERR "\n");
	printk(KERN_ERR
	       "usage> v[0] v[1] v[2] v[3] v[4] (m[0] m[1] m[2] m[3]) (hex)\n");
	printk(KERN_ERR "set 0 disables values and masks\n");
	printk(KERN_ERR "can ignore mask setting (then set as full mask)\n");
}

static void debug_write_port(CLOCK_T *clk, const char *command, u8 type)
{
	int rc;
	LX_ARIB2_CLOCK_UDP_INFO_T *u;
	u32 val, mask;

	rc = sscanf(command, "%u %x", &val, &mask);

	if (rc == 1) {
		if (val == 0)
			mask = 0;	//mask, val is not needed
		mask = 0xFFFF;
	} else if (rc != 2) {
		goto usage;
	}

	u = &clk->udp_info;

	if (type == DEBUG_ID_SRC_PORT) {
		u->src_port_v = (u16)val;
		u->src_port_m = (u16)mask;
	} else {
		u->dst_port_v = (u16)val;
		u->dst_port_m = (u16)mask;
	}

	return;

 usage:
	printk(KERN_ERR "\n");
	printk(KERN_ERR "usage> val[=dec] (mask[=hex])\n");
	printk(KERN_ERR "set 0 disables values and masks\n");
	printk(KERN_ERR "can ignore mask setting (then set as full mask)\n");
}

static int debug_set_time(struct arib2_clock *clk, const char *str)
{
	int rc;
	struct te_time time;
	TICK64_T tick;

	rc = sscanf(str, "%d-%d-%d %d:%d:%d.%d",
		    &time.year, &time.mon, &time.day,
		    &time.hour, &time.min, &time.sec, &time.msec);
	if (rc != 7)
		return -EINVAL;

	rc = te_time_to_tick(&time, CLK_FREQ, NTP_EPOCH_TIME, &tick.value);
	if (rc)
		return rc;

	mutex_lock(&clock_mutex);
	_SetClockTick(clk, &tick);
	mutex_unlock(&clock_mutex);

	return 0;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	enum lx_arib2_clock_recovery cmd;
	struct arib2_clock *clk = item->private;
	TICK64_T tick;
	u32 val;

	switch (item->flags) {
	case DEBUG_ID_RECOVERY:
		val = simple_strtoul(str, NULL, 0);
		if (val == 1)
			cmd = LX_ARIB2_CLOCK_RECOVERY_ENABLE;
		else if (val == 2)
			cmd = LX_ARIB2_CLOCK_RECOVERY_RESET;
		else
			cmd = LX_ARIB2_CLOCK_RECOVERY_DISABLE;

		mutex_lock(&clock_mutex);
		SetClockRecovery(clk, cmd);
		mutex_unlock(&clock_mutex);
		break;
	case DEBUG_ID_TIME:
		ret = debug_set_time(clk, str);
		break;
	case DEBUG_ID_TICK:
		tick.value = simple_strtoull(str, (char **)NULL, 0);
		mutex_lock(&clock_mutex);
		_SetClockTick(clk, &tick);
		mutex_unlock(&clock_mutex);
		break;
	case DEBUG_ID_SRC_IP:
	case DEBUG_ID_DST_IP:
		debug_write_ip(clk, str, item->flags);
		break;
	case DEBUG_ID_SRC_PORT:
	case DEBUG_ID_DST_PORT:
		debug_write_port(clk, str, item->flags);
		break;
	default:
		ret = -EPERM;
		break;
	}
	return 0;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("clk_recovery", &debug_ops, DEBUG_ID_RECOVERY),
	DBGITM_SIM_R("clk_latched", &debug_ops, DEBUG_ID_LATCHED),
	DBGITM_SIM("clk_time", &debug_ops, DEBUG_ID_TIME),
	DBGITM_SIM("clk_tick", &debug_ops, DEBUG_ID_TICK),
	DBGITM_SIM("clk_src_ip", &debug_ops, DEBUG_ID_SRC_IP),
	DBGITM_SIM("clk_dst_ip", &debug_ops, DEBUG_ID_DST_IP),
	DBGITM_SIM("clk_src_port", &debug_ops, DEBUG_ID_SRC_PORT),
	DBGITM_SIM("clk_dst_port", &debug_ops, DEBUG_ID_DST_PORT),
};

static void init_debug(struct arib2_device *dev)
{
	int i;
	struct arib2_clock *clk;
	struct arib2_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		clk = channel->clock;
		debug_create_item_files(debug_list, clk, channel->debug_dir);
	}

	arib2_debug_register_status_show(dev, ARIB2_DEBUG_STATUS_CLOCK,
					 debug_show_clock_status);
}

static void cleanup_debug(CLOCK_T *clk)
{

}

static int clock_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct arib2_ioctl_info ioctls[] = {
		IOC_INFO(ARIB2_IOC_CLK_SET_RECOVERY, ioc_set_clock_recovery),
		IOC_INFO(ARIB2_IOC_CLK_GET_TIME, ioc_get_time),
		IOC_INFO(ARIB2_IOC_CLK_SET_TIME, ioc_set_time),
	};

	return arib2_do_ioctl(priv, cmd, arg, clock_mutex, ioctls);
}

static int clock_dev_suspend(struct arib2_device *dev)
{
	int i;
	CLOCK_T *clk;

	for (i = 0; i < dev->num_channel; i++) {
		clk = dev->channels[i].clock;
		if (clk->recovery.enable) {
			DisableClockRecovery(clk);
			clk->suspended = true;
		}
		hrtimer_cancel(&clk->leap_timer);
		clk->leap_second = 0;
	}

	return 0;
}

static int clock_dev_resume(struct arib2_device *dev)
{
	int i;
	CLOCK_T *clk;

	for (i = 0; i < dev->num_channel; i++) {
		clk = dev->channels[i].clock;
		if (clk->suspended) {
			log_noti("clk(%d) gstcc(%d) recovered", clk->ch,
				 clk->idx);
			EnableClockRecovery(clk);
		}
		clk->suspended = false;
	}

	return 0;
}

static int clock_dev_init(struct arib2_device *dev)
{
	int i;
	struct arib2_channel *channel;
	CLOCK_T *clk;

	for (i = 0; i < dev->num_channel; i++) {
		clk = kzalloc(sizeof(*clk), GFP_KERNEL);
		CHECK_ERROR(clk == NULL, goto error, "no memory");

		channel = &dev->channels[i];
		clk->ch = channel->num;
		clk->channel = channel;
		clk->use_swtlv = dev->use_swtlv;

		clk->idx = 1;	// see TVPLAT-40243
		clk->swtlv_ts_idx = 0;

		memcpy(&(clk->udp_info), &default_udp_info,
		       sizeof(LX_ARIB2_CLOCK_UDP_INFO_T));

		hrtimer_init(&clk->leap_timer, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		clk->leap_timer.function = LeapSecondTimerCallback;
		INIT_WORK(&clk->leap_work, LeapSecondCallbackWork);

		spin_lock_init(&clk->spinlock);
		INIT_WORK(&clk->work, ClockRecoveryWork);
		init_waitqueue_head(&clk->wq);

		channel->clock = clk;
	}

	init_debug(dev);

	return 0;

 error:
	//release alloc memory
	for (i = 0; i < dev->num_channel; i++) {
		clk = dev->channels[i].clock;
		if (!clk)
			kfree(clk);
	}

	return -EIO;
}

static void clock_dev_release(struct arib2_device *dev)
{
	int i;
	CLOCK_T *clk;

	for (i = 0; i < dev->num_channel; i++) {
		clk = dev->channels[i].clock;
		cleanup_debug(clk);
		kfree(clk);
	}
}

static const struct arib2_ioctl ioctl_clk = {
	.magic = ARIB2_IOC_CLK_MAGIC,
	.func = clock_dev_ioctl,
};

const struct arib2_sub_driver arib2_clock_driver = {
	.name = "arib2_clock",
	.init = clock_dev_init,
	.release = clock_dev_release,
	.suspend = clock_dev_suspend,
	.resume = clock_dev_resume,

	.ioctl = &ioctl_clk,
};
