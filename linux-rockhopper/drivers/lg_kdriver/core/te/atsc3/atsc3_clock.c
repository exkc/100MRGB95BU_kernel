/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  atsc3 device driver
 *
 *  @author		Yeonju Lee ( yeonju.lee@lge.com)
 *  @version    0.1
 *  @date       2016-02-25
 *  @note       Additional information.
 */

#include "atsc3_impl.h"

#define TAI_UTC_OFFSET		37	/* From December 31, 2016 */
#define CLK_FREQ		90000

#define BASE_INPUT_CLOCK	27000000	/* 27 MHz */

#define INPUT_CLOCK_THRESHOLD	100000	/* 100Khz */
#define MAX_INPUT_CLOCK		(BASE_INPUT_CLOCK + INPUT_CLOCK_THRESHOLD)
#define MIN_INPUT_CLOCK		(BASE_INPUT_CLOCK - INPUT_CLOCK_THRESHOLD)

#define MAX_STABLE_JITTER_TICK		1
#define MAX_JITTER_THRESHOLD		MS_TO_TICK(5000)
#define MAX_JITTER_FOR_RESET		MS_TO_TICK(80)
#define MIN_OVERSHOOT_JITTER		MS_TO_TICK(5)	/* overshoot jitter if exceed it */
#define MAX_OVERSHOOT_JITTER		MS_TO_TICK(20)	/* strange overshoot jitter */

#define MIN_TIMEINFO_INTERVAL		50	/* ms */
#define MAX_TIMEINFO_INTERVAL		5000	/* ms */

#define JITTER_FOR_RESET_COUNT		5
#define OVERSHOOT_JITTER_COUNT		10

/* clock recovery constant */
//#define WINDOW_SAMPLE_SIZE            12      /* sample count in window */
#define WINDOW_TICK_SIZE		2000	/* 2000ms - 10 samples per window in 200ms intreval timeinfo */
#define NUM_WINDOW			5
#define MAX_WINDOW_IDX			(NUM_WINDOW-1)

#define LEFT_WINDOW			0
#define RIGHT_WINDOW			1

#define POSITIVE_SLOPE		0x1
#define NEGATIVE_SLOPE		0x2

#define TICK_TO_MS(tick)	((tick)/90)
#define MS_TO_TICK(ms)		((ms)*90)

#ifndef abs64
#define abs64(x)		\
({				\
	s64 __x = (x);		\
	(__x < 0) ? -__x : __x;	\
})
#endif

#define div64(n, div)			\
({				 	\
	typeof(n) _v;			\
	if((n) < 0 ) {			\
		u64 _s = (u64)(-n);	\
		do_div(_s, div);	\
		_v = (s64)(-_s);	\
	} else {			\
		_v = n;			\
		do_div(_v, div);	\
	}				\
	_v;				\
})

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
	u8 enable;
	u8 reset;		/* reset time info - copy timeinfo to gstc */
	u32 jitter_errors;	/* jitter count over MAX_JITTER_THRESHOLD */

	RECOVERY_SAMPLE_T sample;

	u32 window_count;	/* current window number */
	RECOVERY_WINDOW_T window_data[NUM_WINDOW];
	RECOVERY_WINDOW_T *window[MAX_WINDOW_IDX * 2];	/* in order to use linear array data */

	s32 overshoots;
} RECOVERY_CTRL_T;

typedef struct {
	TICK64_T live_tick;	/* clock from signal (NTP) produced by timeinfo (isr) */
	TICK64_T system_tick;	/* clock for using recovery produced by gstcc (isr) */
	u32 capture_ms;
} CLOCK_INFO_T;

typedef struct {
	GSTCC_VALUE_T gstcc;	/* captured gstcc by isr handler or NTP parser */
	LX_ATSC3_TIME_T timeinfo;	/* clock from signal (L1 time) */
	u32 capture_ms;
} CLOCK_ISR_INFO_T;

struct debug_adjust_clock {
	u32 idx;
	u32 eptr;
	int *table;
};

struct atsc3_clock {
	u8 ch;
	u8 idx;			/* GSTC index */
	u8 utc_offset;
	s8 leap_second;		/* 0:none, -1:leap_61, 1:leap_59 */

	u32 base_32;		/* wraparound detection */
	u32 tick_hi;		/* GSTCC : 32 ~ 63 */

	u64 leap_tick;
	struct hrtimer leap_timer;
	struct work_struct leap_work;

	spinlock_t spinlock;
	struct work_struct work;

	RECOVERY_CTRL_T recovery;

	u32 freq;		/* current stc frequency */

	/* latched clock tick */
	CLOCK_INFO_T cur_info;
	CLOCK_INFO_T pre_info;

	CLOCK_ISR_INFO_T isr_info;

	struct debug_adjust_clock debug_adjust;

	bool latched;
	bool suspended;
	wait_queue_head_t wq; //wait for wall clock
};

#define clock_workqueue(c)		system_freezable_wq

static DEFINE_MUTEX(clock_mutex);

static const char *jitter_slope_str[] = { "=", "+", "-", "~" };

static void TickToTime(TICK64_T *tick, LX_ATSC3_TIME_T *time)
{
	u64 remainder;
	u64 v;

	v = tick->value;
	remainder = do_div(v, 90000);

	time->sec = (u32)v;

	v = remainder * 100000;
	do_div(v, 9);
	time->nsec = (u32)v;
}

static void TimeToTick(LX_ATSC3_TIME_T *time, TICK64_T *tick)
{
/*
 * 1ns = (90000/1000000000) tick
 * 1us = (90000/1000000) tick
 * xus = x * (9/100) tick
 */
	tick->value = (u64)time->sec * 90000;
	tick->value += (((time->nsec / 1000) * 9) / 100);
}

/* CHECK: protected by mutex clock_mutex */
static void _SetClockTick(struct atsc3_clock *clk, TICK64_T *tick)
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

	log_noti("_SetClockTick(ch:%d,hi:0x%x,lo:0x%08x)", clk->ch, tick->hi,
		 tick->lo);
}

/* CHECK: protected by mutex clock_mutex */
static void _GetClockTick(struct atsc3_clock *clk, TICK64_T *tick)
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

/* CHECK: protected by mutex clock_mutex */
static void _AdjustClockTick(struct atsc3_clock *clk, int value, TICK64_T *tick)
{
	struct te_config *cfg = te_get_config();
	unsigned long flag;
	TICK64_T _tick;

	if (!tick)
		tick = &_tick;

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
	struct atsc3_clock *clk;
	TICK64_T tick;

	clk = container_of(work, struct atsc3_clock, leap_work);

	mutex_lock(&clock_mutex);
	if (clk->leap_second) {
		int adjust = -((s32)clk->leap_second * CLK_FREQ);

		_AdjustClockTick(clk, adjust, &tick);

		log_noti("CH[%d] leap second(%d), tick(%llu), UTC offset(%d)\n",
			 clk->ch, clk->leap_second, tick.value,
			 clk->utc_offset);

		clk->utc_offset += clk->leap_second;
		clk->leap_second = 0;
	}
	mutex_unlock(&clock_mutex);

}

static enum hrtimer_restart LeapSecondTimerCallback(struct hrtimer *timer)
{
	struct atsc3_clock *clk;

	clk = container_of(timer, struct atsc3_clock, leap_timer);

	queue_work(clock_workqueue(clk), &clk->leap_work);

	return HRTIMER_NORESTART;
}

static int SetSystemTimeInfo(struct atsc3_clock *clk,
			     LX_ATSC3_SYSTEM_TIME_INFO_T *info)
{
	if (clk->utc_offset != info->current_utc_offset) {
		int adjust;

		log_noti("CH[%d] change utc offset from (%d) to (%d)\n",
			 clk->ch, clk->utc_offset, info->current_utc_offset);

		adjust = ((int)clk->utc_offset - info->current_utc_offset) *
			 CLK_FREQ;

		_AdjustClockTick(clk, adjust, NULL);

		clk->utc_offset = info->current_utc_offset;
	}

	if (info->leap59 || info->leap61) {
		TICK64_T tick;
		u64 minutes;
		u32 adjust_seconds;
		u32 remained_tick;
		ktime_t ktime;
		u32 secs, nsecs;

		_GetClockTick(clk, &tick);

		minutes = tick.value;
		do_div(minutes, (CLK_FREQ * 60));	// current minutes

		if (info->leap61) {
			clk->leap_second = 1;
			adjust_seconds = 60;
		} else {
			clk->leap_second = -1;
			adjust_seconds = 59;
		}
		clk->leap_tick = (minutes * 60 + adjust_seconds) * CLK_FREQ;	// leap second

		if (clk->leap_tick <= tick.value) {
			clk->leap_tick += (60 * CLK_FREQ);
		}

		remained_tick = (u32)(clk->leap_tick - tick.value);

		secs = remained_tick / CLK_FREQ;
		nsecs = ((remained_tick % CLK_FREQ) * 10000 / 9) * 10;

		ktime = ktime_set(secs, nsecs);
		hrtimer_start(&clk->leap_timer, ktime, HRTIMER_MODE_REL);

		log_noti("CH[%d] leap=%d, tick=%llu, secs=%u, nsecs=%u\n",
			 clk->ch, clk->leap_second, clk->leap_tick, secs,
			 nsecs);
	}

	return 0;
}

static int SetClock(struct atsc3_clock *clk, LX_ATSC3_TIME_T *time)
{
	TICK64_T tick;

	TimeToTick(time, &tick);

	_SetClockTick(clk, &tick);

	return 0;
}

static int GetClock(struct atsc3_clock *clk, LX_ATSC3_TIME_T *time)
{
	TICK64_T tick;

	_GetClockTick(clk, &tick);
	time->wall_clock = clk->latched;

	TickToTime(&tick, time);

	return 0;
}

/* Clock Recovery */

static int SetClockRate(struct atsc3_clock *clk, u32 freq)
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

static void ResetJitterSample(RECOVERY_SAMPLE_T *s)
{
	s->count = 0;
	s->sum_jitter = 0;
}

static void AddJitterSample(RECOVERY_SAMPLE_T *s, CLOCK_INFO_T *info,
			    s32 jitter)
{
#ifdef WINDOW_SAMPLE_SIZE
	if (s->count >= WINDOW_SAMPLE_SIZE) {
		LOG_WARNING("abnoraml sample count(%d)\n", s->count);
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

static void ResetClockRecovery(struct atsc3_clock *clk)
{
	RECOVERY_CTRL_T *r = &clk->recovery;

	clk->freq = BASE_INPUT_CLOCK;
	SetClockRate(clk, BASE_INPUT_CLOCK);

	r->reset = true;
	r->jitter_errors = 0;

	r->overshoots = 0;
	r->window_count = 0;
	ResetJitterSample(&r->sample);
}

static void GetTwoWindowFromList(RECOVERY_WINDOW_T **list,
				 RECOVERY_WINDOW_SUM_T *left,
				 RECOVERY_WINDOW_SUM_T *right)
{
#if (NUM_WINDOW == 5)
#define NUM_WINDOW_HALF		3
#define LEFT_WINDOW_MAX_IDX	2
#define RIGHT_WINDOW_MIN_IDX	2
#else
#error "define left & right window macros"
#endif
	int i;
	s64 jitter[2] = { 0, 0 };
	u32 time[2] = { 0, 0 };

	for (i = 0; i <= MAX_WINDOW_IDX; i++) {
		RECOVERY_WINDOW_T *a = list[i];

		if (i <= LEFT_WINDOW_MAX_IDX) {
			jitter[0] += a->jitter;

			if (i == 0)
				time[0] = a->timestamp;
			else if (i == LEFT_WINDOW_MAX_IDX)
				time[0] += ((a->timestamp - time[0]) / 2);
		}

		if (i >= RIGHT_WINDOW_MIN_IDX) {
			jitter[1] += list[i]->jitter;

			if (i == RIGHT_WINDOW_MIN_IDX)
				time[1] = a->timestamp;
			else if (i == MAX_WINDOW_IDX)
				time[1] += ((a->timestamp - time[1]) / 2);
		}
	}

	left->jitter = div64(jitter[0] * 300, NUM_WINDOW_HALF);
	left->timestamp = time[0];

	right->jitter = div64(jitter[1] * 300, NUM_WINDOW_HALF);
	right->timestamp = time[1];

}

static s32 AdjustWithSignOfJitterSlope(struct atsc3_clock *clk,
				       u32 sign_of_slope, u32 abs_jitter_avg,
				       RECOVERY_WINDOW_T **list)
{
	int i;
	bool adjust;
	s64 n;
	u32 base;
	s32 adjust_clk;
	RECOVERY_WINDOW_T *w;

	if (abs_jitter_avg < MAX_STABLE_JITTER_TICK) {
		log_timeinfo("CH[%d] stable jitter(%d) - do nothing\n", clk->ch,
			     abs_jitter_avg);
		return 0;
	}

	adjust = false;
	w = list[MAX_WINDOW_IDX];	/* last window to find the jitter postion */
	if (sign_of_slope == POSITIVE_SLOPE) {
		/* steady incresing above 0 */
		if (w->jitter > 0)
			adjust = true;
	} else {
		/* steady decreasing below 0 */
		if (w->jitter < 0)
			adjust = true;
	}

	if (adjust) {
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
		u32 amp = 0;
		RECOVERY_WINDOW_SUM_T left, right;
		u64 abs_jitter;

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
		n = (s64)(right.jitter - left.jitter) * (10 * (100 + amp));
		base = right.timestamp - left.timestamp;

		adjust_clk = div64(n, base);

		log_timeinfo("CH[%d] Adjust Clock[%dHz] - "
			     "jitter slope : L[%lld] R[%lld] amp[%d%%]\n",
			     clk->ch, adjust_clk,
			     left.jitter, right.jitter, amp);
	} else {
		// waiting
		log_timeinfo("CH[%d] %s slope and jitter get close to 0\n",
			     clk->ch,
			     (sign_of_slope ==
			      POSITIVE_SLOPE) ? "positive" : "negative");

		adjust_clk = 0;
	}

	return adjust_clk;
}

static s32 AdjustWithJitterOvershoot(struct atsc3_clock *clk,
				     u32 abs_jitter_avg,
				     RECOVERY_WINDOW_T **list)
{
	int i;
	s32 adjust_clk;
	s32 overshoots = 0;
	RECOVERY_CTRL_T *r = &clk->recovery;

	if (abs_jitter_avg < MIN_OVERSHOOT_JITTER) {
		r->overshoots = 0;
		return 0;
	}

	for (i = 0; i <= MAX_WINDOW_IDX; i++) {
		s32 jitter = list[i]->jitter;

		if (jitter > MIN_OVERSHOOT_JITTER)
			overshoots++;
		else if (jitter < -MIN_OVERSHOOT_JITTER)
			overshoots--;
	}

	if (abs(overshoots) > MAX_WINDOW_IDX) {
		s64 n;
		u32 base;
		RECOVERY_WINDOW_SUM_T left, right;
		int adjust = false;

		GetTwoWindowFromList(list, &left, &right);

		log_timeinfo
		    ("CH[%d] jitter[R](%lld) - jitter[L](%lld) = %lld\n",
		     clk->ch, right.jitter, left.jitter,
		     (right.jitter - left.jitter));

		/* adjust for jitter divergence */
		if (abs64(right.jitter) > abs64(left.jitter))
			adjust = true;

		if (adjust) {
			/* ADJUST CLOCK(HZ) = (jitter * 1000 / time) * 1.20
			 * jitter = jitter[R] - jitter[L] : 27MHz units
			 * time = time[R] - time[L] : ms unit */

			n = (s64)(right.jitter - left.jitter) * (10 * 120);
			base = right.timestamp - left.timestamp;
			adjust_clk = div64(n, base);
			log_timeinfo("CH[%d] Overshoot - Adjust Clock[%dHz] \n",
				     clk->ch, adjust_clk);
		} else {
			r->overshoots += ((overshoots > 0) ? 1 : -1);
			adjust_clk = 0;
			log_timeinfo("CH[%d] Stable Overshoot(%d)...\n",
				     clk->ch, r->overshoots);

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
		/* do nothing */
		adjust_clk = 0;
	}

	return adjust_clk;
}

static int ClockRecoveryProcessWindow(struct atsc3_clock *clk, s32 jitter,
				      u32 timestamp)
{
	u32 wcount, idx;
	RECOVERY_WINDOW_T *w;
	RECOVERY_WINDOW_T *a, *b;
	u32 sign_of_slope;
	s32 adjust_clk;
	u32 abs_jitter_avg;
	int i;
	RECOVERY_CTRL_T *r = &clk->recovery;

	wcount = r->window_count;
	r->window_count++;

	idx = wcount % NUM_WINDOW;
	w = &r->window_data[idx];

	w->jitter = jitter;
	w->timestamp = timestamp;

	if (wcount < MAX_WINDOW_IDX) {	/* wait for the next window */
		r->window[wcount] = w;
		return 0;
	}

	idx = wcount % MAX_WINDOW_IDX;	/* start index of window */
	r->window[idx + MAX_WINDOW_IDX] = w;	/* save current window */

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

	if (sign_of_slope == POSITIVE_SLOPE || sign_of_slope == NEGATIVE_SLOPE) {	/* CASE1 */
		adjust_clk = AdjustWithSignOfJitterSlope(clk, sign_of_slope,
							 abs_jitter_avg,
							 &r->window[idx]);
	} else {		/* CASE2 */
		adjust_clk = AdjustWithJitterOvershoot(clk, abs_jitter_avg,
						       &r->window[idx]);
	}

	if (adjust_clk) {
		u32 new_freq = clk->freq + adjust_clk;

		if (new_freq > MAX_INPUT_CLOCK)
			new_freq = MAX_INPUT_CLOCK;
		else if (new_freq < MIN_INPUT_CLOCK)
			new_freq = MIN_INPUT_CLOCK;

		SetClockRate(clk, new_freq);

		clk->freq = new_freq;

		r->window_count = 0;	// TODO: add function
		r->overshoots = 0;
	} else {
		r->window[idx] = w;	/* save to make the linear array */
	}

	return 0;
}

/* Debug clock conversion; only used on debug purposes */
static void debug_adjust_timeinfo(struct atsc3_clock *clk)
{
	struct debug_adjust_clock *info = &clk->debug_adjust;
	TICK64_T *tick = &clk->cur_info.live_tick;
	int val;

	if (likely(!info->table))
		return;

	/* table data is signed msec value */
	val = info->table[info->idx];

	log_warning("(DEBUG) adjust wall clock %d ms (idx:%u/%u)", val,
		    info->idx, info->eptr);
	tick->value += val * 90; // 1ms = 90 tick; signed value

	info->idx++;
	if (info->idx == info->eptr) { //done work (free allocated table)
		kfree(info->table);
		info->table = NULL;
	}
}

static void GetLatchedClockInfo(struct atsc3_clock *clk)
{
	unsigned long flag;
	TICK64_T tick;
	CLOCK_INFO_T *clk_info;
	CLOCK_ISR_INFO_T *isr_info;

	clk_info = &clk->cur_info;
	isr_info = &clk->isr_info;

	spin_lock_irqsave(&clk->spinlock, flag);

	clk_info->capture_ms = isr_info->capture_ms;

	isr_info->timeinfo.sec -= clk->utc_offset;	/* TAI => UTC */
	TimeToTick(&isr_info->timeinfo, &clk_info->live_tick);	/* UTC => GSTCC */
	debug_adjust_timeinfo(clk);

	_GetClockTick(clk, &tick);

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

static void ClockRecoveryWorkManual(struct atsc3_clock *clk)
{
	RECOVERY_CTRL_T *r;
	CLOCK_INFO_T *info, *pre_info;
	TICK64_T tick;
	s64 jitter64;
	s32 jitter;
	u32 timestamp, time_interval;
	u32 elapsed;
	RECOVERY_SAMPLE_T *s;

	r = &clk->recovery;
	info = &clk->cur_info;
	pre_info = &clk->pre_info;

	GetLatchedClockInfo(clk);

	if (r->reset) {
#define CLOCK_ISR_DELAY_TICK	3
		struct te_time tm;

		te_tick_to_time(info->live_tick.value, CLK_FREQ,
				UNIX_EPOCH_TIME, &tm);

		log_noti("1st live clock(%s),tick(%llu) is arrived",
			 te_get_readable_time(&tm), info->live_tick.value);

		/* how to calculate the delay from h/w to s/w */
		tick.value = info->live_tick.value + CLOCK_ISR_DELAY_TICK;
		_SetClockTick(clk, &tick);
		clk->latched = true;	//latched when 1st clock is arrived
		wake_up(&clk->wq);

		r->reset = false;

		/* save current info */
		clk->pre_info = clk->cur_info;
		return;
	}

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

static void ClockRecoveryWork(struct work_struct *work)
{
	struct atsc3_clock *clk;

	clk = container_of(work, struct atsc3_clock, work);

	mutex_lock(&clock_mutex);
	if (clk->recovery.enable != true) {
		log_timeinfo("CH[%d] Clock recovery is not started", clk->ch);
		goto exit;
	}

	ClockRecoveryWorkManual(clk);

exit:
	mutex_unlock(&clock_mutex);
}

static void clock_irq_handler(struct atsc3_channel *channel)
{
	struct te_config *cfg = te_get_config();
	struct te_reg_atsc3_timestamp timestamp;
	u32 base_32, base_31_0, ext;
	struct atsc3_clock *clk;
	CLOCK_ISR_INFO_T *isr_info;
	int ret;

	ret = te_reg_atsc3_get_timestamp(channel->num, &timestamp);
	CHECK_ERROR(ret != 0, return, "Error in get_timestamp[%d]", ret);

	if (timestamp.mode == ATSC3_TIMESTAMP_NONE) {
		log_clock("no timestamp !!!\n");
		return;
	}

	clk = channel->clock;
	isr_info = &clk->isr_info;

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
	isr_info->timeinfo.nsec = (timestamp.msec * 1000000) +
				  (timestamp.usec * 1000) + timestamp.nsec;

	spin_unlock(&clk->spinlock);
	te_reg_dumper_set_latch_enable(clk->ch, true);

	queue_work(clock_workqueue(clk), &clk->work);
}

int atsc3_clock_irq_handler(struct atsc3_device *dev, u32 val)
{
	int i;

	if (val & DUMPER_INTR_TIMESTAMP_MASK) {
		u32 a3_ts_mask[4] = {
			DUMPER_INTR_TIMESTAMP_CH0,
			DUMPER_INTR_TIMESTAMP_CH1,
			DUMPER_INTR_TIMESTAMP_CH2,
			DUMPER_INTR_TIMESTAMP_CH3
		};
		struct atsc3_channel *channel;

		for (i = 0; i < 4; i++) {
			if (val & a3_ts_mask[i]) {
				channel = atsc3_get_channel(dev, i);
				if (!channel)
					continue;

				clock_irq_handler(channel);
			}
		}
	}

	return 0;
}

static void EnableClockRecovery(struct atsc3_clock *clk)
{
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		TE_REG_SetGstccMode(clk->idx, GSTCC_MODE_UNITSTEP);
	}

	ResetClockRecovery(clk);

	te_reg_dumper_set_latch_enable(clk->ch, true);
	te_reg_dumper_set_intr_enable(DUMPER_INTR_TIMESTAMP_CH0 << (clk->ch),
				      true);

	clk->latched = false;
	clk->recovery.enable = true;
}

static void DisableClockRecovery(struct atsc3_clock *clk)
{
	struct te_config *cfg = te_get_config();

	te_reg_dumper_set_intr_enable(DUMPER_INTR_TIMESTAMP_CH0 << (clk->ch),
				      false);

	if (!cfg->no_stcc_bug) {
		TE_REG_SetGstccMode(clk->idx, GSTCC_MODE_EXTINCR);
	}

	clk->latched = false;
	clk->recovery.enable = false;
	clk->leap_second = 0;
}

static void destroy_adjust_timeinfo(struct atsc3_clock *clk)
{
	struct debug_adjust_clock *info = &clk->debug_adjust;
	unsigned long flags;

	spin_lock_irqsave(&clk->spinlock, flags);

	if (info->table) {
		kfree(info->table);
		info->table = NULL;
	}

	spin_unlock_irqrestore(&clk->spinlock, flags);
}

static int SetClockRecovery(struct atsc3_clock *clk,
			    LX_ATSC3_CLOCK_RECOVERY_T command)
{
	struct te_config *cfg = te_get_config();
	int ret;

	switch (command) {
	case LX_ATSC3_CLOCK_RECOVERY_ENABLE:
		if (!cfg->no_stcc_bug) {
			ret = te_reg_dumper_set_time_src(clk->ch, clk->idx);
			CHECK_ERROR(ret != 0,, "Error in set_time_src [%d]",
				    ret);
		}
		EnableClockRecovery(clk);
		ret = 0;
		break;

	case LX_ATSC3_CLOCK_RECOVERY_DISABLE:
		DisableClockRecovery(clk);
		destroy_adjust_timeinfo(clk);
		ret = 0;
		break;

	case LX_ATSC3_CLOCK_RECOVERY_RESET:
		if (clk->recovery.enable) {
			DisableClockRecovery(clk);
			EnableClockRecovery(clk);
		}
		ret = 0;
		break;

	default:
		log_error("Invalid Command[%d]", command);
		ret = -EINVAL;
		break;
	}

	return ret;
}

int atsc3_set_clock_recovery(struct atsc3_channel *channel,
			     enum lx_atsc3_clock_recovery param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = SetClockRecovery(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_set_clock_recovery(struct atsc3_fh *fh, void *arg)
{
	int ret;
	LX_ATSC3_CLOCK_RECOVERY_T *param = arg;
	struct atsc3_clock *clk = fh->channel->clock;

	ret = SetClockRecovery(clk, *param);

	return ret;
}

static int set_debug_adjust_clock_table(struct atsc3_channel *channel,
					int *table, u32 size)
{
	struct atsc3_clock *clk = channel->clock;
	struct debug_adjust_clock *info = &clk->debug_adjust;
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&clk->spinlock, flags);

	if (info->table) {
		log_error("already running adjustment(idx:%u/%u)", info->idx,
			  info->eptr);
		rc = -EBUSY;
		goto error;
	}

	info->table = kmalloc(size, GFP_ATOMIC);
	if (!info->table) {
		log_error("fail to alloc memory");
		rc = -ENOMEM;
		goto error;
	}

	memcpy(info->table, table, size);
	info->idx = 0;
	info->eptr = size / sizeof(int);

error:
	spin_unlock_irqrestore(&clk->spinlock, flags);
	return rc;
}

int atsc3_set_debug_adjust_clock(struct atsc3_channel *channel, int *table,
				 u32 size)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = set_debug_adjust_clock_table(channel, table, size);
	mutex_unlock(&clock_mutex);
	return ret;
}

int atsc3_get_time(struct atsc3_channel *channel, struct lx_atsc3_time *param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = GetClock(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_get_time(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_TIME_T *param = arg;
	struct atsc3_clock *clk = fh->channel->clock;
	int ret;

	ret = GetClock(clk, param);
	CHECK_ERROR(ret != 0, return ret, "Error in GetClock");

	return 0;
}

int atsc3_set_system_time_info(struct atsc3_channel *channel,
			       struct lx_atsc3_system_time_info *param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = SetSystemTimeInfo(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_set_system_time_info(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_SYSTEM_TIME_INFO_T *param = arg;
	struct atsc3_clock *clk = fh->channel->clock;
	int ret;

	ret = SetSystemTimeInfo(clk, param);
	CHECK_ERROR(ret != 0, return ret, "Error in SetSystemTimeInfo");

	return 0;
}

int atsc3_set_time(struct atsc3_channel *channel, struct lx_atsc3_time *param)
{
	int ret;

	mutex_lock(&clock_mutex);
	ret = SetClock(channel->clock, param);
	mutex_unlock(&clock_mutex);

	return ret;
}

static int ioc_set_time(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_TIME_T *param = arg;
	struct atsc3_clock *clk = fh->channel->clock;
	int ret;

	ret = SetClock(clk, param);
	CHECK_ERROR(ret != 0, return ret, "Error in SetClock");

	return 0;
}

unsigned int atsc3_wait_clock(struct atsc3_channel *channel, struct file *file,
			      struct poll_table_struct *wait)
{
	struct atsc3_clock *clk = channel->clock;
	unsigned int mask = 0;

	poll_wait(file, &clk->wq, wait);

	if (clk->latched)
		mask |= (POLLIN | POLLRDNORM | POLLPRI);

	return mask;
}

/**
 * ioc_wait_for_wallclock - Wait until wall clock is delivered
 *
 * When the ioctl calls, it waits for wall clock from inputs for specific
 * timeouts, returns immediately when the clock is delivered
 *
 * Returns: 0 if the clock is arrived in time, -ETIME if the clock is not
 * arrived after timeout, -ERESTARTSYS if the signal is received
 */
static int ioc_wait_for_wallclock(struct atsc3_fh *fh, void *arg)
{
	u32 *timeout = arg;
	struct atsc3_clock *clk = fh->channel->clock;
	int rc;

	if (*timeout) {
		rc = wait_event_interruptible_timeout(clk->wq, clk->latched,
						      msecs_to_jiffies(*timeout));
		if (!rc)
			rc = -ETIME;
	} else {
		rc = wait_event_interruptible(clk->wq, clk->latched);
	}

	if (rc < 0)
		return rc;

	return 0;
}

/* For B17B0 workaround */
typedef struct {
	u32 dummy:2, time_nsec:10, time_usec:10, time_msec:10;
	u32 time_sec;
} TIME_INFO_T;

void ATSC3_CLOCK_SetTimeInfo(u64 timeinfo, u32 diff_usec)
{
#if 0
	struct atsc3_channel *channel;
	struct atsc3_clock *clk;
	u32 base_32, base_31_0, ext;
	TIME_INFO_T *ti;
	CLOCK_ISR_INFO_T *isr_info;
	LX_ATSC3_TIME_T *time;

	channel = ATSC3_GetChCtrl(0);	/* only one channel */
	CHECK_ERROR(!channel, return, "NULL channel (ch:0)");

	clk = channel->clock;
	isr_info = &clk->isr_info;

	// TODO: adjust difference latch time between demod and gstcc
	TE_REG_GetGstcc(clk->idx, &base_32, &base_31_0, &ext);

	log_clock("timeinfo:0x%llx, diff_usec:%u\n", timeinfo, diff_usec);

	if (diff_usec > (500 * 1000)) {
		log_error("too big diff_usec : %uusec\n", diff_usec);
		return;
	}

	mutex_lock(&clock_mutex);
	isr_info->capture_ms = (u32)OS_GetMsecTicks();
	isr_info->gstcc.base_31_0 = base_31_0;
	isr_info->gstcc.base_32 = base_32;

	ti = (TIME_INFO_T *)&timeinfo;
	time = &isr_info->timeinfo;

	time->sec = ti->time_sec;
	time->nsec =
	    ti->time_msec * (1000 * 1000) + ti->time_usec * 1000 +
	    ti->time_nsec;
	time->nsec += (diff_usec * 1000);
	if (time->nsec >= (1000 * 1000 * 1000)) {
		time->sec += 1;
		time->nsec -= (1000 * 1000 * 1000);
	}
	mutex_unlock(&clock_mutex);

	queue_work(channel->dev->workqueue, &clk->work);
#endif
}
EXPORT_SYMBOL(ATSC3_CLOCK_SetTimeInfo);

/* DEBUG Functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	CLOCK_DEBUG_ID_RECOVERY = 0,
	CLOCK_DEBUG_ID_UTC_OFFSET,
	CLOCK_DEBUG_ID_LATCHED,
	CLOCK_DEBUG_ID_TIME,
	CLOCK_DEBUG_ID_TICK,
	CLOCK_DEBUG_ID_MAX,
};

static int debug_show_clock_status(struct atsc3_device *dev, struct seq_file *m)
{
	int i;
	TICK64_T tick;
	struct te_time tm;

	dprintf("Clock Status\n");
	dprintf("%3s %3s %2s %5s %6s %15s %23s\n",
		"Num", "Idx", "En", "Latch", "Offset", "Tick", "Time(UTC)");

	mutex_lock(&clock_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		struct atsc3_clock *c = dev->channels[i].clock;
		if (!c)
			continue;

		_GetClockTick(c, &tick);

		te_tick_to_time(tick.value, CLK_FREQ, UNIX_EPOCH_TIME, &tm);

		dprintf("[%d] %3d %2d %5d %6d %15llu %23s\n", i, c->idx,
			c->recovery.enable, c->latched,	c->utc_offset,
			tick.value, te_get_readable_time(&tm));
	}
	mutex_unlock(&clock_mutex);

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	LX_ATSC3_TIME_T time;
	TICK64_T tick;
	struct atsc3_clock *clk = item->private;

	switch (item->flags) {
	case CLOCK_DEBUG_ID_RECOVERY:
		dprintf("%d\n", clk->recovery.enable);
		break;

	case CLOCK_DEBUG_ID_UTC_OFFSET:
		dprintf("%d\n", clk->utc_offset);
		break;

	case CLOCK_DEBUG_ID_LATCHED:
		dprintf("%d\n", clk->latched);
		break;

	case CLOCK_DEBUG_ID_TIME:
		mutex_lock(&clock_mutex);
		ret = GetClock(clk, &time);
		mutex_unlock(&clock_mutex);
		if (!ret) {
			struct te_time tm;
			te_tick_to_time(time.sec, 1, UNIX_EPOCH_TIME, &tm);
			tm.msec = time.nsec / 1000000;
			dprintf("%s\n", te_get_readable_time(&tm));
		}
		break;

	case CLOCK_DEBUG_ID_TICK:
		mutex_lock(&clock_mutex);
		_GetClockTick(clk, &tick);
		mutex_unlock(&clock_mutex);
		dprintf("%llu\n", tick.value);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_set_time(struct atsc3_clock *clk, const char *str)
{
	int rc;
	struct te_time time;
	TICK64_T tick;

	rc = sscanf(str, "%d-%d-%d %d:%d:%d.%d",
		    &time.year, &time.mon, &time.day,
		    &time.hour, &time.min, &time.sec, &time.msec);
	if (rc != 7)
		return -EINVAL;

	rc = te_time_to_tick(&time, CLK_FREQ, UNIX_EPOCH_TIME, &tick.value);
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
	u32 val;
	LX_ATSC3_CLOCK_RECOVERY_T cmd;
	LX_ATSC3_SYSTEM_TIME_INFO_T info;
	TICK64_T tick;
	struct atsc3_clock *clk = item->private;

	switch (item->flags) {
	case CLOCK_DEBUG_ID_RECOVERY:
		val = simple_strtoul(str, (char **)NULL, 0);
		if (val == 1)
			cmd = LX_ATSC3_CLOCK_RECOVERY_ENABLE;
		else if (val == 2)
			cmd = LX_ATSC3_CLOCK_RECOVERY_RESET;
		else
			cmd = LX_ATSC3_CLOCK_RECOVERY_DISABLE;

		mutex_lock(&clock_mutex);
		ret = SetClockRecovery(clk, cmd);
		mutex_unlock(&clock_mutex);
		break;

	case CLOCK_DEBUG_ID_UTC_OFFSET:
		val = simple_strtoul(str, (char **)NULL, 0);
		memset(&info, 0, sizeof(info));
		info.current_utc_offset = val;

		mutex_unlock(&clock_mutex);
		SetSystemTimeInfo(clk, &info);
		mutex_unlock(&clock_mutex);
		break;

	case CLOCK_DEBUG_ID_TIME:
		ret = debug_set_time(clk, str);
		break;

	case CLOCK_DEBUG_ID_TICK:
		tick.value = simple_strtoull(str, (char **)NULL, 0);
		mutex_lock(&clock_mutex);
		_SetClockTick(clk, &tick);
		mutex_unlock(&clock_mutex);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("clk_recovery", &debug_ops, CLOCK_DEBUG_ID_RECOVERY),
	DBGITM_SIM("clk_utc_offset", &debug_ops, CLOCK_DEBUG_ID_UTC_OFFSET),
	DBGITM_SIM_R("clk_latched", &debug_ops, CLOCK_DEBUG_ID_LATCHED),
	DBGITM_SIM("clk_time", &debug_ops, CLOCK_DEBUG_ID_TIME),
	DBGITM_SIM("clk_tick", &debug_ops, CLOCK_DEBUG_ID_TICK),
};

static void init_debug(struct atsc3_device *dev)
{
	int i;
	struct atsc3_clock *clk;
	struct atsc3_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		clk = channel->clock;
		debug_create_item_files(debug_list, clk, channel->debug_dir);
	}

	atsc3_debug_register_status_show(dev, ATSC3_DEBUG_STATUS_CLOCK,
					 debug_show_clock_status);
}

/* atsc3 sub driver */

static int clock_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct atsc3_ioctl_info ioctls[] = {
		IOC_INFO(ATSC3_IOC_CLK_SET_RECOVERY, ioc_set_clock_recovery),
		IOC_INFO(ATSC3_IOC_CLK_GET_TIME, ioc_get_time),
		IOC_INFO(ATSC3_IOC_CLK_SET_TIME_INFO, ioc_set_system_time_info),
		IOC_INFO(ATSC3_IOC_CLK_SET_TIME, ioc_set_time),
		IOC_INFO_NOLOCK(ATSC3_IOC_CLK_WAIT_WALLCLOCK, ioc_wait_for_wallclock),
	};

	return atsc3_do_ioctl(priv, cmd, arg, clock_mutex, ioctls);
}

static int clock_dev_suspend(struct atsc3_device *dev)
{
	int i;
	struct atsc3_channel *channel;
	struct atsc3_clock *clk;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		clk = channel->clock;
		if (clk->recovery.enable) {
			DisableClockRecovery(clk);
			clk->suspended = true;
		}
		hrtimer_cancel(&clk->leap_timer);
		clk->leap_second = 0;
	}

	return 0;
}

static int clock_dev_resume(struct atsc3_device *dev)
{
	int i;
	struct atsc3_channel *channel;
	struct atsc3_clock *clk;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		clk = channel->clock;
		if (clk->suspended) {
			log_noti("clk(%d) gstcc(%d) recovered", clk->ch,
				 clk->idx);
			clk->latched = false;
			EnableClockRecovery(clk);
		}
		clk->suspended = false;
	}

	return 0;
}

static int clock_dev_init(struct atsc3_device *dev)
{
	int i;
	struct atsc3_channel *channel;
	struct atsc3_clock *clk;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		clk = kzalloc(sizeof(*clk), GFP_KERNEL);
		CHECK_ERROR(!clk, return -ENOMEM, "no memory");

		clk->ch = channel->num;
		clk->idx = 1;
		clk->utc_offset = TAI_UTC_OFFSET;

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
}

static void clock_dev_release(struct atsc3_device *dev)
{

}

static const struct atsc3_ioctl ioctl_clock = {
	.magic = ATSC3_IOC_CLK_MAGIC,
	.func = clock_dev_ioctl,
};

const struct atsc3_sub_driver atsc3_clock_driver = {
	.name = "atsc3_clock",
	.init = clock_dev_init,
	.release = clock_dev_release,
	.suspend = clock_dev_suspend,
	.resume = clock_dev_resume,

	.ioctl = &ioctl_clock,
};
