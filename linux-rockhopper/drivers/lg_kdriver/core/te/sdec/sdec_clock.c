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
 *  sdec driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2019-10-10
 *  @note	Additional information.
 */

#include "sdec_impl.h"

/**
 * DOC: PCR recovery for MPEG2 system stream
 *
 * PCR and STC values in units of 45kHz are used to recover the system clock
 * more effectively, unsing integer type and processing wrap-around,
 * and the 27MHz base jitter value is used to calculate as below:
 *  PCR = latched PCR(33 bits 90kHz base value) >> 1 ==> 32 bit 45kHz base value
 *  jitter = |PCR - STC| * 600 ==> 27MHz base value
 *
 * slope adjustment:
 *  min time = WINDOW_TIME_SIZE * NUM_WINDOW = 1500 * 5 = 7500ms
 *  if |pcr clock - stc_clock| is 50Khz, jitter will be 375000
 *  in units of 27Mhz(13.8ms) after 7500ms later.
 *
 * stable overshoot adjust:
 *  min time = WINDOW_TIME_SIZE * (NUM_WINDOW + STABLE_OVERSHOOT_JITTER_COUNT)
 *           = 1500 * (5 + 5) = 15000ms = 15Sec
 *  if |pcr clock - stc_clock| is 50Khz, jitter will be 750000
 *  in units of 27Mhz(27.7ms) after 15 seconds later.
 *
 * For more information,
 * see http://collab.lge.com/main/display/DNA/10.+PCR+Recovery
 *
 */

static int use_dco = 0;
module_param_named(sdec_use_dco, use_dco, int, 0644);

/* PCR and STC should be latched only when latch_en bit in STCC_CONF register
 * is set, but PCR is always latched evenif latch_en bit is cleared. And this
 * bug begins from M16+ not M16(added sub module in M16+).
 * It is needed to check the validation of latched values.
 */
static bool fixup_pcr_latch_bug = false;

#define FREQ_KHZ(n) ((n)*1000)
#define FREQ_MHZ(n) (FREQ_KHZ(n) * 1000)

/* jitter value in units of 27MHz */
#define delta_to_jitter(delta) ((s64)(delta)*600)
#define ms_to_jitter(ms) ((ms)*27000)
#define us_to_jitter(us) ((us)*27)
#define jitter_to_ms(tick) te_div64(tick, 27000)
#define jitter_to_90khz(tick) te_div64(tick, 300)

#define PCR_STANDARD_CLOCK FREQ_MHZ(27) /* 27MHz */
#define INPUT_CLOCK_THRESHOLD FREQ_KHZ(108) /* 0.4%(4000ppm) of 27M */
#define MAX_INPUT_CLOCK (PCR_STANDARD_CLOCK + INPUT_CLOCK_THRESHOLD)
#define MIN_INPUT_CLOCK (PCR_STANDARD_CLOCK - INPUT_CLOCK_THRESHOLD)

#define MIN_TIME_INTERVAL 50 /* ms */
#define MAX_TIME_INTERVAL 5000 /* ms */

#define RESET_DISCARD_COUNT 5

#define MAX_FIRST_STABLE_JITTER us_to_jitter(800)
#define MAX_RUNNING_STABLE_JITTER us_to_jitter(50)

#define MAX_JITTER_THRESHOLD ms_to_jitter(5000)
#define MAX_JITTER_FOR_RESET ms_to_jitter(30) /* a/v lip sync offset = 150ms */
#define MAX_PVR_INPUT_JITTER_FOR_RESET ms_to_jitter(200)

#define OVERSHOOT_JITTER ms_to_jitter(2) /* overshoot jitter if exceed it */

#define SLOPE_ERROR_HPF 2700 /* high pass filter, units of 27MHz */
#define SLOPE_ERROR_PERCENTAGE 30

#define MIN_PCR_INPUT_INTERVAL 45 /* in units of 45Khz (PCR LATCH BUG) */

#define MAX_JITTER_AUTO_PCR_RECOVERY ms_to_jitter(3)
#define MAX_OVERSHOOT_AUTO_PCR_RECOVERY 10

#define JITTER_FOR_RESET_COUNT 10 /* > 500ms = 10 * MIN_TIME_INTERVAL(50) */

#define NUM_WINDOW 5

#if (NUM_WINDOW == 5)
#define WINDOW_TIME_SIZE 1500 /* ms */
#define WINDOW_JITTER_FMT "%lld %lld %lld %lld %lld"
#define WINDOW_JITTER_ARGS(l)                                           \
	(l)[0]->jitter, (l)[1]->jitter, (l)[2]->jitter, (l)[3]->jitter, \
		(l)[4]->jitter

#define STABLE_OVERSHOOT_JITTER_COUNT 5

#elif (NUM_WINDOW == 7)
#define WINDOW_TIME_SIZE 1000 /* ms */
#define WINDOW_JITTER_FMT "%lld %lld %lld %lld %lld %lld %lld"
#define WINDOW_JITTER_ARGS(l)                                           \
	(l)[0]->jitter, (l)[1]->jitter, (l)[2]->jitter, (l)[3]->jitter, \
		(l)[4]->jitter, (l)[5]->jitter, (l)[6]->jitter

#define STABLE_OVERSHOOT_JITTER_COUNT 7

#else
#error "define NUM_WINDOW macros"
#endif

#define PCR_FMT "PCR[0x%08x]-STC[0x%08x]=%d(%lldms) "
#define PCR_ARGS(_i_) \
	(_i_)->latched.pcr, (_i_)->latched.stc, (_i_)->delta, jitter_to_ms((_i_)->jitter)

#define POSITIVE_SLOPE 0x1
#define NEGATIVE_SLOPE 0x2

#define clk_err(clk, fmt, args...) log_noti("CH[%d] " fmt, (clk)->idx, ##args)
#define clk_noti(clk, fmt, args...) log_noti("CH[%d] " fmt, (clk)->idx, ##args)
#define clk_dbg(clk, fmt, args...) log_pcr("CH[%d] " fmt, (clk)->idx, ##args)
#define clk_dbg_y(clk, fmt, args...) \
	log_pcr(TE_COLOR_YELLOW "CH[%d] " fmt TE_COLOR_NONE, (clk)->idx, ##args)

static int max_pvr_input_jitter = MAX_PVR_INPUT_JITTER_FOR_RESET;
module_param_named(sdec_max_pvr_input_jitter, max_pvr_input_jitter, int, 0644);

enum recovery_mode {
	MANUAL_RECOVERY_MODE = 0, // manual rate control using unit step
	AUTO_RECOVERY_MODE, // auto rate control by h/w
};

enum input_mode {
	INPUT_FROM_DEMOD = 0,
	INPUT_FROM_PVR,
	INPUT_FROM_USBCI,
};

union clock_tick {
	u64 value;
	struct {
		u32 lo;
		u32 hi;
	};
};

struct sample_data {
	u32 count; /* num of input samples in a window */
	s64 sum_jitter; /* sum of current window's jitter samples */
	u32 start_timestamp; /* timestamp of the first sample */
	u32 elapsed; /* elapsed time from the first sample */
};

struct window_data {
	s64 jitter; /* average value of jitter(pcr - stc) in window */
	u32 timestamp;
};

struct window_variation {
	u32 sign_of_slope;
	s32 overshoots;
	u64 abs_jitter_avg; /* average value of absoulte jitter values */
	s64 jitter_avg; /* average value of jitter values */
};

struct clock_data {
	u32 pcr; /* 45KHz base */
	u32 stc; /* 45KHz base */
	u32 time; /* capture time in ms */
};

struct clock_irq_data {
	union clock_tick pcr; /* latched value */
	union clock_tick stc; /* latched value */
	union clock_tick isr_stc; /* live stc in isr (PCR LATCH BUG) */
	u32 isr_time; /* time in isr */
};

struct clock_info {
	struct clock_data latched;
	u32 isr_stc; /* PCR LATCH BUG */
	s32 delta; /* pcr - stc */
	s64 jitter; /* delta in units of 27MHz */
};

struct sdec_clock {
	u8 idx; /* channel number */

	bool enable; /* pcr recovery enable */
	bool stcc_enable;
	bool is_main; /* only used if use DCO */

	u16 pid; /* pcr pid */
	enum recovery_mode mode;

	spinlock_t spinlock;
	struct work_struct work;

	u16 reset_discard; /* discarding count after reset recovery */
	bool first_adjustment; /* first adjustment after reset recovery */
	u32 max_stable_jitter;
	u32 jitter_errors; /* jitter count over MAX_JITTER_FOR_RESET */

	struct sample_data sample;

	u32 window_count; /* current window number */
	struct window_data window_data[NUM_WINDOW];
	struct window_data *window[NUM_WINDOW * 2 - 1]; /* linear array data */

	s32 overshoots;

	struct clock_irq_data irq_data;
	struct clock_data last_data;

	u32 freq; /* current stc frequency */

	enum input_mode input_mode;
	bool delayed_mode;
	u32 delay; /* pcr delay for usb ci handling (45 kHz tick) */
};

struct dco_dev {
	bool exist;
	u32 input_clock; /* HZ, DCO input clock */
	u32 freq; /* HZ, current frequency */
	struct sdec_clock *clk;
};

#define clock_workqueue(c) system_freezable_wq

static struct dco_dev dco_dev;
static DEFINE_MUTEX(clock_mutex);

#define clk_source_is_dco(c) (dco_dev.clk == (c))

static const char *jitter_slope_str(u32 slope)
{
	const char *str[] = { "=", "+", "-", "~" };

	if (slope < ARRAY_SIZE(str))
		return str[slope];

	return "X";
}

static int set_dco_freq(u32 freq)
{
	int ret;

	if (!dco_dev.exist) {
		log_error("no dco\n");
		return -ENODEV;
	}

	log_clock("DCO Freq : %u ==> %u", dco_dev.freq, freq);

	ret = TE_REG_SetDcoFcw(freq, dco_dev.input_clock);
	CHECK_ERROR(ret, return ret, "Error(%d) in TE_REG_SetDcoFcw\n", ret);

	dco_dev.freq = freq;

	return 0;
}

static int set_stcc_input_clock(struct sdec_clock *clk, u32 freq)
{
	int ret = 0;
	int unit_step, diff;

	clk_dbg(clk, "STCC Input Clock = %u", freq);

	if (clk_source_is_dco(clk)) {
		ret = set_dco_freq(freq);
	} else if (clk->mode == MANUAL_RECOVERY_MODE) {
		struct te_config *cfg = te_get_config();

		if (!cfg->no_stcc_bug) {
			diff = (int)freq - PCR_STANDARD_CLOCK;

			if (diff == 0) // Prevent to divide by zero
				unit_step = 0;
			else
				unit_step = PCR_STANDARD_CLOCK / diff;

			ret = TE_REG_SetStccSubPcrUnitStep(clk->idx, unit_step);
		} else {
			ret = te_ipc_set_stcc_freq(clk->idx, freq);
		}
	}

	if (!ret) {
		clk->freq = freq;
	}

	return ret;
}

static void reset_stcc_input_clock(struct sdec_clock *clk)
{
	set_stcc_input_clock(clk, PCR_STANDARD_CLOCK);
}

static void reset_jitter_sample(struct sample_data *s)
{
	s->count = 0;
	s->sum_jitter = 0;
}

static void reset_windows(struct sdec_clock *clk)
{
	clk->overshoots = 0;
	clk->window_count = 0;
}

/**
 * reset_pcr_recovery - status clear and data structure init for PCR Recovery
 *
 */
static void reset_pcr_recovery(struct sdec_clock *clk)
{
	struct te_config *cfg = te_get_config();

	log_pcr("%s(%d)", __FUNCTION__, clk->idx);

	reset_stcc_input_clock(clk);

	clk->reset_discard = RESET_DISCARD_COUNT;
	clk->first_adjustment = true;
	clk->max_stable_jitter = MAX_FIRST_STABLE_JITTER;
	clk->jitter_errors = 0;

	reset_jitter_sample(&clk->sample);
	reset_windows(clk);

	if (!clk_source_is_dco(clk)) {
		if (clk->mode == AUTO_RECOVERY_MODE) {
			u32 v = jitter_to_90khz(MAX_JITTER_AUTO_PCR_RECOVERY);

			/* rate control only run when pcr jitter is smaller
			 * than the configured jitter value. */
			if (!cfg->no_stcc_bug) {
				TE_REG_SetPcrJitter(clk->idx, false, v);
				TE_REG_ResetStcc(clk->idx);
			} else {
				te_ipc_reset_stcc(clk->idx);
			}
		} else {
			if (!cfg->no_stcc_bug)
				TE_REG_ResetStcc(clk->idx);
			else
				te_ipc_reset_stcc(clk->idx);
		}
	}

	TE_REG_SetStccLatchEnable(clk->idx, true);

	if (clk->delayed_mode) // do not copy by hardware
		return;

	if (!cfg->no_stcc_bug) {
		TE_REG_SetStccEnableCopy(clk->idx);
	} else  {
		te_ipc_set_stcc_copy_enable(clk->idx);
	}
}

static void set_stcc_mode(struct sdec_clock *clk, bool is_main)
{
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		if (clk->stcc_enable)
			TE_REG_EnableStcc(clk->idx, false);

		if (is_main) {
			TE_REG_SetStccClockSource(clk->idx, STCC_CLK_SRC_DCO);

			/* main means not using sdec rate control module,
			 * and rate controlled by dco clock */
			TE_REG_SetStccMain(clk->idx, true);
		} else {
			u8 val;

			TE_REG_SetStccClockSource(clk->idx, STCC_CLK_SRC_FIXED);
			TE_REG_SetStccMain(clk->idx, false);

			switch (clk->mode) {
			case AUTO_RECOVERY_MODE:
				val = PCR_MODE_AUTORATE;
				break;
			case MANUAL_RECOVERY_MODE:
				val = PCR_MODE_MANUAL;
				break;
			default:
				log_error("CH[%d] invalid sub mode(%d)",
					  clk->idx, clk->mode);
				return;
			}
			TE_REG_SetStccSubMode(clk->idx, val);
		}

		if (clk->stcc_enable)
			TE_REG_EnableStcc(clk->idx, true);
	} else {
		// Nothing to do!
	}
}

static void set_pcr_recovery_mode(struct sdec_clock *clk, bool is_main)
{
	if (use_dco && dco_dev.exist && is_main &&
	    clk->mode == MANUAL_RECOVERY_MODE) {
		struct sdec_clock *c = dco_dev.clk;

		if (c != NULL && c != clk) {
			log_noti("Change STC Main from %d to %d\n", c->idx,
				 clk->idx);
			c->is_main = false;
			dco_dev.clk = NULL;

			set_stcc_mode(c, false);
			reset_pcr_recovery(c);
		}

		set_stcc_mode(clk, true);

		dco_dev.clk = clk;
		clk->is_main = true;
	} else {
		if (clk_source_is_dco(clk)) {
			clk_noti(clk, "Changed from stc main to sub");

			reset_stcc_input_clock(clk);
			dco_dev.clk = NULL;
		}

		set_stcc_mode(clk, false);
		clk->is_main = false;
	}

	reset_pcr_recovery(clk); // is it correct ?
}

static void cancel_pcr_recovery(struct sdec_clock *clk)
{
	clk->enable = false;

	reset_stcc_input_clock(clk);

	if (clk_source_is_dco(clk)) {
		dco_dev.clk = NULL;
	}
}

static int init_dco_clock(void)
{
	int ret;
	u32 clock = 0;

	ret = TE_REG_GetDcoInputClock(&clock);
	if (ret || clock == 0) {
		log_noti("not exist dco");
		dco_dev.exist = false;
		return 0;
	}

	dco_dev.input_clock = clock * 1000 * 1000;
	dco_dev.exist = true;

	set_dco_freq(PCR_STANDARD_CLOCK);

	log_noti("SDEC DCO Input Clock : %dMhz\n", clock);

	return 0;
}

/**
 * add_jitter_sample - add jitter value of clock_info to sum_jitter of sample
 *
 */
static void add_jitter_sample(struct sample_data *s, struct clock_info *info)
{
	if (s->count == 0) {
		s->start_timestamp = info->latched.time;
		s->elapsed = 0;
	} else {
		s->elapsed = info->latched.time - s->start_timestamp;
	}

	s->sum_jitter += info->jitter;
	s->count++;
}

static void save_last_data(struct sdec_clock *clk, struct clock_info *info)
{
	clk->last_data = info->latched;
}

/**
 * check_reset_discard - check reset discard status and 1st pcr packet
 *
 * After reset_pcr_recovery, we would skip RESET_DISCARD_COUNT pcr
 * interrupt to start recovery.
 *
 * Return: true if it is discarded, false if not
 */
static bool check_reset_discard(struct sdec_clock *clk, struct clock_info *info)
{
	if (!clk->reset_discard)
		return false;

	if (clk->reset_discard == RESET_DISCARD_COUNT)
		clk_noti(clk, "1st pcr packet is arrived");

	clk->reset_discard--;
	if (clk->reset_discard == 0) {
		save_last_data(clk, info);

		clk_dbg(clk, "%dth pcr after reset - start next time",
			RESET_DISCARD_COUNT);
	}

	return true;
}

static inline u64 get_max_reset_jitter(struct sdec_clock *clk)
{
	if (clk->input_mode == INPUT_FROM_DEMOD)
		return MAX_JITTER_FOR_RESET;
	else
		return max_pvr_input_jitter;
}

/**
 * check_jitter_errors - check jitter errors and update status
 *
 * Return: true if it has jitter errors, false if not
 */
static bool check_jitter_errors(struct sdec_clock *clk, struct clock_info *info)
{
	u64 abs_jitter;

	abs_jitter = abs(info->jitter);

	if (abs_jitter > MAX_JITTER_THRESHOLD) {
		clk_noti(clk, PCR_FMT "> MAX_JITTER_THRESHOLD ==> RESET",
			 PCR_ARGS(info));

		reset_pcr_recovery(clk);

		return true;
	}

	if (abs_jitter > get_max_reset_jitter(clk)) {
		clk->jitter_errors++;

		clk_dbg(clk, PCR_FMT "> MAX_JITTER_FOR_RESET %d times",
			PCR_ARGS(info), clk->jitter_errors);

		if (clk->jitter_errors > JITTER_FOR_RESET_COUNT) {
			clk_noti(clk, PCR_FMT "JITTER ERRORS ==> RESET",
				 PCR_ARGS(info));
			reset_pcr_recovery(clk);
		}
		return true;
	}

	if (clk->jitter_errors)
		clk->jitter_errors--;

	return false;
}

static u32 get_slope_adjust_amplifier(s64 jitter)
{
	int i;
	u64 abs_jitter;
	const struct {
		u32 jitter;
		u32 amp; /* percetage */
	} adjust_amplifer[] = {
		{ ms_to_jitter(5), 20 }, /* >= 5ms - 20% */
		{ ms_to_jitter(2), 15 }, /* >= 2ms - 15% */
		{ ms_to_jitter(1), 12 }, /* >= 1ms - 12% */
		{ us_to_jitter(500), 9 }, /* >= 500us - 9% */
		{ us_to_jitter(200), 6 }, /* >= 200us - 6% */
		{ us_to_jitter(70), 3 }, /* >= 70us - 3% */
	};
	u32 amp = 0;

	abs_jitter = abs(jitter);
	for (i = 0; i < ARRAY_SIZE(adjust_amplifer); i++) {
		if (abs_jitter >= adjust_amplifer[i].jitter) {
			amp = adjust_amplifer[i].amp;
			break;
		}
	}

	return amp;
}

static s32 get_overshoot_adjust_clock(s64 jitter)
{
	int i;
	u64 abs_jitter;
	s32 adj;
	const struct {
		u32 jitter;
		u32 clock; /* HZ */
	} overshoot_adjust_clk[] = {
		{ ms_to_jitter(20), 9000 }, /* >= 20ms - 9KHz */
		{ ms_to_jitter(15), 6750 }, /* >= 15ms */
		{ ms_to_jitter(10), 4500 }, /* >= 10ms */
		{ ms_to_jitter(5), 2250 }, /* >= 5ms */
		{ ms_to_jitter(3), 1350 }, /* >= 3ms */
		{ ms_to_jitter(2), 900 }, /* >= 2ms */
		{ ms_to_jitter(1), 450 }, /* >= 1ms */
	};

	/* overshoot_adjust_clk table is calcuated as below:
	 * adjust_clock = jitter / 60
	 *
	 * It means jitter will be 0 after 60 seconds, if input clock is stable.
	 * If no issue happen, remove overshoot_adjust_clk table and
	 * add a simple arithmetic. */

	adj = 0;
	abs_jitter = abs(jitter);
	for (i = 0; i < ARRAY_SIZE(overshoot_adjust_clk); i++) {
		if (abs_jitter >= overshoot_adjust_clk[i].jitter) {
			s32 sign = (jitter > 0) ? 1 : -1;
			adj = sign * overshoot_adjust_clk[i].clock;
			break;
		}
	}

	return adj;
}

static s32 get_slope_adjust_clock(struct sdec_clock *clk,
				  struct window_data **list)
{
	int i;
	s32 adj;
	u32 amp, t;
	s64 n, a, e;
	struct window_data *l, *r;
	u64 sum_e, avg_e;

	l = list[0];
	r = list[NUM_WINDOW - 1];

	/* ADJUST CLOCK(HZ) = (jitter * 1000 / time) * (1 + amplifier)
	 * jitter = jitter[R] - jitter[L] : 27MHz units
	 * time = time[R] - time[L] : ms unit */
	n = r->jitter - l->jitter;
	t = r->timestamp - l->timestamp;

	/*
	 * Y = a * X + b
	 *
	 * a = Calculated Slope in units of 27MHz
	 *
	 *      (jitter[R] - jitter[L]) * 1000
	 *   = --------------------------------
	 *              time[R] - time[L]
	 *
	 * x = {0, ..., NUM_WINDOW - 2}
	 *
	 * a2(x) = Slope Between window(x) and window(x + 1)
	 *
	 *          (jitter[x + 1] - jitter[x]) * 1000
	 *       = ------------------------------------
	 *                 time[x + 1] - time[x]
	 *
	 * e(x) = Slope Error
	 *      = abs(a - a2(x))
	 *
	 * avg_e = Average Slope Error
	 *       = sum(e) / (NUM_WINDOW - 1)
	 *
	 * percent_e = Percent Error
	 *           = avg_e * 100 / abs(a)
	 *
	 * In Error Case, the percent error is over 90(90 ~ 150) but
	 * normally it is under 10 in normal case.
	 *
	 */
	a = te_div64(n * 1000, t);

	sum_e = 0;
	for (i = 0; i < NUM_WINDOW - 1; i++) {
		n = list[i + 1]->jitter - list[i]->jitter;
		t = list[i + 1]->timestamp - list[i]->timestamp;
		e = a - te_div64(n * 1000, t);
		sum_e += abs(e);
	}
	avg_e = te_div64(sum_e, NUM_WINDOW - 1);

	if (avg_e > SLOPE_ERROR_HPF) {
		u64 percent;
		if (a) { //prevent divided by zero
			percent = div64_u64(avg_e * 100, abs(a));
		} else {
			percent = 0;
		}

		clk_dbg(clk, "a=%lld, avg_e=%llu, percent=%llu", a, avg_e,
			percent);

		if (percent >= SLOPE_ERROR_PERCENTAGE) {
			adj = get_overshoot_adjust_clock(r->jitter);
			clk_dbg(clk, "Adjust[%dHz] - slope error", adj);
			return adj;
		}
	}

	amp = get_slope_adjust_amplifier(r->jitter);
	if (amp) {
		n = a * (100 + amp);
		adj = te_div64(n, 100);
	} else {
		adj = a;
	}

	clk_dbg(clk, "Adjust[%dHz] - jitter slope : L[%lld] R[%lld] amp[%u%%]",
		adj, l->jitter, r->jitter, amp);

	return adj;
}

static s32 adjust_with_slope(struct sdec_clock *clk, struct window_variation *v,
			     struct window_data **list)
{
	bool do_adjust;
	s32 adj;
	struct window_data *w;

	if (v->sign_of_slope != POSITIVE_SLOPE &&
	    v->sign_of_slope != NEGATIVE_SLOPE)
		return 0;

	if (v->abs_jitter_avg < clk->max_stable_jitter) {
		if (clk->first_adjustment) {
			clk_dbg(clk, "First adjustment - stable jitter(%llu)",
				v->abs_jitter_avg);
		} else {
			clk_dbg(clk, "stable jitter(%llu) - do nothing",
				v->abs_jitter_avg);
		}

		return 0;
	}

	do_adjust = false;
	w = list[NUM_WINDOW - 1]; /* last window to find the jitter postion */
	if (v->sign_of_slope == POSITIVE_SLOPE) {
		if (w->jitter > 0) /* steady incresing above 0 */
			do_adjust = true;
	} else {
		if (w->jitter < 0) /* steady decreasing below 0 */
			do_adjust = true;
	}

	if (!do_adjust) {
		// waiting
		clk_dbg(clk, "'%s' slope and jitter get close to 0",
			jitter_slope_str(v->sign_of_slope));
		return 0;
	}

	adj = get_slope_adjust_clock(clk, list);

	return adj;
}

static s32 adjust_with_overshoot(struct sdec_clock *clk,
				 struct window_variation *v,
				 struct window_data **list)
{
	s32 adj;

	if (abs(v->overshoots) < NUM_WINDOW) {
		clk->overshoots = 0;
		return 0;
	}

	if (v->overshoots > 0) {
		if (clk->overshoots < 0)
			clk->overshoots = 1;
		else
			clk->overshoots++;
	} else {
		if (clk->overshoots > 0)
			clk->overshoots = -1;
		else
			clk->overshoots--;
	}

	clk_dbg(clk, "Stable Overshoot(%d)...\n", clk->overshoots);

	if (abs(clk->overshoots) <= STABLE_OVERSHOOT_JITTER_COUNT)
		return 0;

	adj = get_overshoot_adjust_clock(v->jitter_avg);

	clk_dbg(clk, "Adjust[%dHz] - overshoot jitter(%lld)", adj,
		v->jitter_avg);

	return adj;
}

static s32 get_adjust_clock(struct sdec_clock *clk, struct window_variation *v,
			    struct window_data **list)
{
	s32 adj;

	adj = adjust_with_overshoot(clk, v, list);
	if (!adj)
		adj = adjust_with_slope(clk, v, list);

	return adj;
}

static void get_window_variation(struct window_data **list,
				 struct window_variation *v)
{
	int i;
	s64 jitter_sum = 0;
	u64 abs_jitter_sum = 0;
	struct window_data *a = NULL;
	struct window_data *w;

	v->sign_of_slope = 0;
	v->overshoots = 0;
	for (i = 0; i < NUM_WINDOW; i++) {
		w = list[i];
		if (a) {
			if (w->jitter > a->jitter) {
				v->sign_of_slope |= POSITIVE_SLOPE;
			} else if (w->jitter < a->jitter) {
				v->sign_of_slope |= NEGATIVE_SLOPE;
			}
		}

		if (w->jitter > OVERSHOOT_JITTER) {
			v->overshoots++;
		} else if (w->jitter < -OVERSHOOT_JITTER) {
			v->overshoots--;
		}

		jitter_sum += w->jitter;
		abs_jitter_sum += abs(w->jitter);
		a = w;
	}
	v->jitter_avg = te_div64(jitter_sum, NUM_WINDOW);
	v->abs_jitter_avg = te_div64(abs_jitter_sum, NUM_WINDOW);
}

static void process_window(struct sdec_clock *clk, struct clock_info *info)
{
	u32 widx, idx;
	struct window_data *w;
	struct window_data **list;
	struct window_variation v;
	u32 new_freq;
	s32 adj;
	struct sample_data *s = &clk->sample;

	add_jitter_sample(s, info);

	if (s->elapsed < WINDOW_TIME_SIZE)
		return;

	widx = clk->window_count;

	/* add window data */
	idx = widx % NUM_WINDOW;
	w = &clk->window_data[idx];

	w->jitter = te_div64(s->sum_jitter, s->count);
	w->timestamp = s->start_timestamp + s->elapsed / 2;

	clk->window_count++;

	reset_jitter_sample(s);

	/* wait for the next window */
	if (clk->window_count < NUM_WINDOW) {
		clk_dbg(clk, "W[%u] waiting... jitter[%lld]", widx, w->jitter);
		return;
	}

	/* start index of window */
	idx = (idx + 1) % NUM_WINDOW;
	list = &clk->window[idx];

	/* calculate sign of jitter slope & sum of jitter */
	get_window_variation(list, &v);

	clk_dbg(clk, "W[%u] jitter[" WINDOW_JITTER_FMT "] slope[%s]", widx,
		WINDOW_JITTER_ARGS(list), jitter_slope_str(v.sign_of_slope));

	adj = get_adjust_clock(clk, &v, list);
	if (!adj)
		return;

	new_freq = clk->freq + adj;
	clk_dbg_y(clk, "FREQ %u ==> %u, adjust(%d)", clk->freq, new_freq, adj);

	if (new_freq > MAX_INPUT_CLOCK)
		new_freq = MAX_INPUT_CLOCK;
	else if (new_freq < MIN_INPUT_CLOCK)
		new_freq = MIN_INPUT_CLOCK;

	set_stcc_input_clock(clk, new_freq);

	if (clk->first_adjustment) {
		clk->max_stable_jitter = MAX_RUNNING_STABLE_JITTER;
		clk->first_adjustment = false;
	}

	reset_windows(clk);
}

/**
 * check_latched_value - check latched values
 *
 * Return: true if it has an error, false if not
 */
static bool check_latched_value(struct sdec_clock *clk, struct clock_info *info)
{
	u32 delta_stc, delta_pcr, diff;
	u32 isr_delay;

	if (!fixup_pcr_latch_bug)
		return false;

	isr_delay = info->isr_stc - info->latched.stc;

	/* PCR would not be latched again if isr delay is smaller than
	 * the minimum PCR interval */
	if (isr_delay < MIN_PCR_INPUT_INTERVAL)
		return false;

	delta_stc = info->latched.stc - clk->last_data.stc;
	delta_pcr = info->latched.pcr - clk->last_data.pcr;

	clk_dbg(clk, "ISR_DELAY=%u STC_DELTA=%u PCR_DELTA=%u",
		isr_delay, delta_stc, delta_pcr);

	/* If PCR is latched again, the difference of PCRs is bigger than
	 * the difference of STCs because PCR is the last value but STC is
	 * the previous one.
	 * In order to calcuate more accurate, the difference of clock
	 * frequecny is considered, but ignored here. */
	if (delta_pcr < delta_stc)
		return false;

	diff = delta_pcr - delta_stc;

	/* The difference of delta value is bigger than the PCR interval
	 * and smaller than the isr delay if PCR is latched again. */
	if (diff < MIN_PCR_INPUT_INTERVAL || diff > isr_delay)
		return false;

	clk_dbg(clk, "DELTA DIFF=%u ==> PCR is latched again", diff);

	return true;
}

static void pcr_recovery_manual(struct sdec_clock *clk, struct clock_info *info)
{
	u32 time_interval;

	if (check_reset_discard(clk, info))
		return;

	time_interval = info->latched.time - clk->last_data.time;

	/* reduce the frequency of pcr recovery */
	if (time_interval < MIN_TIME_INTERVAL)
		return;

	if (time_interval > MAX_TIME_INTERVAL) {
		clk_noti(clk, "discontinuous(%ums) PCR ==> RESET",
			 time_interval);
		reset_pcr_recovery(clk);
		return;
	}

	clk_dbg(clk, "(%5dKHz) ADJ(%dHZ) PCR[0x%08x]-STC[0x%08x]=[%d]",
		clk->freq / 1000, clk->freq - PCR_STANDARD_CLOCK,
		info->latched.pcr, info->latched.stc, info->delta);

	if (check_latched_value(clk, info))
		return;

	if (check_jitter_errors(clk, info))
		return;

	process_window(clk, info);

	save_last_data(clk, info);
}

static void pcr_recovery_auto(struct sdec_clock *clk, struct clock_info *info)
{
	u32 time_interval;
	u64 abs_jitter;

	if (check_reset_discard(clk, info))
		return;

	time_interval = info->latched.time - clk->last_data.time;

	/* reduce the frequency of pcr recovery */
	if (time_interval < MIN_TIME_INTERVAL)
		return;

	clk_dbg(clk, "PCR[0x%08x]-STC[0x%08x]=[%d]", info->latched.pcr,
		info->latched.stc, info->delta);

	abs_jitter = abs(info->jitter);
	if (abs_jitter >= MAX_JITTER_THRESHOLD) {
		clk_noti(clk, PCR_FMT "> MAX_JITTER_THRESHOLD ==> RESET",
			 PCR_ARGS(info));

		reset_pcr_recovery(clk);
		return;
	}

	if (abs_jitter > MAX_JITTER_AUTO_PCR_RECOVERY) {
		clk->overshoots++;

		clk_dbg(clk, "overshoot[%d]", clk->overshoots);
		if (clk->overshoots > MAX_OVERSHOOT_AUTO_PCR_RECOVERY) {
			clk_noti(clk, "JITTER ERRORS ==> RESET");
			reset_pcr_recovery(clk);
			return;
		}
	} else {
		if (clk->overshoots > 0)
			clk->overshoots--;
	}

	save_last_data(clk, info);
}

static void pcr_recovery_work(struct work_struct *work)
{
	struct sdec_clock *clk;
	struct clock_irq_data *data;
	struct clock_info info;
	unsigned long flags;

	clk = container_of(work, struct sdec_clock, work);

	mutex_lock(&clock_mutex);

	if (!clk->enable) {
		clk_dbg(clk, "PCR recovery is not started");
		mutex_unlock(&clock_mutex);
		return;
	}

	spin_lock_irqsave(&clk->spinlock, flags);
	data = &clk->irq_data;
	info.latched.pcr = data->pcr.value >> 1;
	info.latched.stc = data->stc.value >> 1;
	info.latched.time = data->isr_time;
	if (fixup_pcr_latch_bug)
		info.isr_stc = data->isr_stc.value >> 1;

	if (clk->delayed_mode)
		info.latched.stc += clk->delay;

	spin_unlock_irqrestore(&clk->spinlock, flags);

	info.delta = (s32)(info.latched.pcr - info.latched.stc);
	info.jitter = delta_to_jitter(info.delta);

	if (clk_source_is_dco(clk)) {
		pcr_recovery_manual(clk, &info);
	} else {
		if (clk->mode == MANUAL_RECOVERY_MODE) {
			pcr_recovery_manual(clk, &info);
		} else {
			pcr_recovery_auto(clk, &info);
		}
	}

	mutex_unlock(&clock_mutex);
}

#define te_get_input_port_type(p)	((p)&0xF0)
static void set_clock_input_mode(struct sdec_clock *clk,
				 enum lx_te_input_port port)
{
	unsigned long flags;

	spin_lock_irqsave(&clk->spinlock, flags); // spinlock for delayed_mode

	if (te_get_input_port_type(port) != LX_TE_INPUT_PORT_DVR) {
		clk->input_mode = INPUT_FROM_DEMOD;
	} else if (clk->delayed_mode) {
		clk->input_mode = INPUT_FROM_USBCI;
	} else {
		clk->input_mode = INPUT_FROM_PVR;
	}

	spin_unlock_irqrestore(&clk->spinlock, flags);
}

static int set_pcr_pid(struct sdec_clock *clk, u16 pid, bool is_main)
{
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		TE_REG_EnableStcc(clk->idx, false);
		clk->stcc_enable = false;

		//TODO: Consider Manual Mode
		//TODO: Recheck Submode when it is enabled
		TE_REG_SetPcrPid(clk->idx, pid, true);

		set_pcr_recovery_mode(clk, is_main);

		TE_REG_SetStccLatchEnable(clk->idx, true);

		TE_REG_EnableStcc(clk->idx, true);
	} else {
		te_ipc_enable_stcc(clk->idx, false);
		clk->stcc_enable = false;

		te_ipc_request_pcr_pid(clk->idx, pid);

		set_pcr_recovery_mode(clk, is_main);

		te_ipc_enable_stcc(clk->idx, true);
	}

	clk->pid = pid;
	clk->stcc_enable = true;

	return 0;
}

static int cancel_pcr_pid(struct sdec_clock *clk)
{
	struct te_config *cfg = te_get_config();


	if (!cfg->no_stcc_bug) {
		TE_REG_SetPcrPid(clk->idx, 0x1fff, false);
		TE_REG_EnableStcc(clk->idx, false);
	} else {
		te_ipc_cancel_pcr_pid(clk->idx);
		te_ipc_enable_stcc(clk->idx, false);
	}

	cancel_pcr_recovery(clk);

	clk->pid = 0x1fff;
	clk->stcc_enable = false;

	return 0;
}

static int ioc_set_pcr_pid(struct sdec_fh *fh, void *arg)
{
	LX_SDEC_PCR_PID_T *param = arg;
	struct sdec_channel *channel = fh->channel;

	CHECK_PARAM(param->pid >= 0x1fff, "invalid pid(0x%x)", param->pid);
	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);

	log_clock("%s(ch=%d,pid=0x%x)", __FUNCTION__, channel->num, param->pid);

	set_clock_input_mode(channel->clk, channel->input_port);
	return set_pcr_pid(channel->clk, param->pid, param->main);
}

static int ioc_cancel_pcr_pid(struct sdec_fh *fh, void *arg)
{
	struct sdec_channel *channel = fh->channel;

	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);

	log_clock("%s(ch=%d)", __FUNCTION__, channel->num);

	return cancel_pcr_pid(channel->clk);
}

static int pcr_recovery_command(struct sdec_clock *clk,
				enum lx_sdec_pcr_cmd cmd)
{
	struct te_config *cfg = te_get_config();
	int ret = 0;

	switch (cmd) {
	case LX_SDEC_PCR_CMD_DISABLE:
		clk->enable = false;
		reset_stcc_input_clock(clk);
		break;

	case LX_SDEC_PCR_CMD_ENABLE:
		reset_pcr_recovery(clk);
		clk->enable = true;
		break;

	case LX_SDEC_PCR_CMD_RESET:
		log_warning("deprecated cmd[RESET]");
		if (!cfg->no_stcc_bug) {
			TE_REG_ResetStcc(clk->idx);
			TE_REG_SetStccEnableCopy(clk->idx);
		} else {
			te_ipc_reset_stcc(clk->idx);
			te_ipc_set_stcc_copy_enable(clk->idx);
		}
		break;

	case LX_SDEC_PCR_CMD_SET_MAIN:
		log_warning("deprecated cmd[SET_MAIN]");
		if (!clk->is_main) {
			set_pcr_recovery_mode(clk, true);
		}
		break;

	case LX_SDEC_PCR_CMD_SET_SUB:
		log_warning("deprecated cmd[SET_SUB]");
		if (clk->is_main) {
			set_pcr_recovery_mode(clk, false);
		}
		break;

	default:
		log_error("Invalid PCR cmd:[%d]", cmd);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int ioc_set_pcr_recovery(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_channel *channel = fh->channel;
	struct lx_sdec_pcr_recovery_cfg *cfg = arg;

	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);

	log_clock("%s(ch=%d,cmd=%d)", __FUNCTION__, channel->num, cfg->cmd);

	ret = pcr_recovery_command(channel->clk, cfg->cmd);

	return ret;
}

/**
 * Get the current latched STCC & PCR Value
 *
 */
static int ioc_get_stc_pcr(struct sdec_fh *fh, void *arg)
{
	struct sdec_channel *channel = fh->channel;
	struct lx_sdec_stc_pcr *param = arg;
	unsigned long flags;
	struct sdec_clock *clk = channel->clk;

	CHECK_PARAM(!clk, "invalid ch(%d)", channel->num);

	spin_lock_irqsave(&clk->spinlock, flags);
	param->stc.base_32 = clk->irq_data.stc.hi;
	param->stc.base_31_0 = clk->irq_data.stc.lo;
	param->stc.ext = 0;

	param->pcr.base_32 = clk->irq_data.pcr.hi;
	param->pcr.base_31_0 = clk->irq_data.pcr.lo;
	param->pcr.ext = 0;
	spin_unlock_irqrestore(&clk->spinlock, flags);

	return 0;
}

static int get_live_stc(u8 idx, struct lx_sdec_clk_value *v)
{
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		return TE_REG_GetLiveStcc(idx, &v->base_32, &v->base_31_0,
					  &v->ext);
	} else {
		int ret = te_ipc_get_stcc(idx, &v->base_32, &v->base_31_0);
		v->ext = 0;
		return ret;
	}
}

/**
 * Get the current live stcc
 *
 */
static int ioc_get_live_stc(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_channel *channel = fh->channel;
	struct lx_sdec_clk_value *param = arg;
	struct sdec_clock *clk = channel->clk;

	CHECK_PARAM(!clk, "invalid ch(%d)", channel->num);

	ret = get_live_stc(clk->idx, param);

	return ret;
}

static int get_gstc(u8 idx, struct lx_sdec_clk_value *v)
{
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		return TE_REG_GetGstcc(idx, &v->base_32, &v->base_31_0, &v->ext);
	} else {
		int ret = te_ipc_get_gstcc(idx, &v->base_32, &v->base_31_0);
		v->ext = 0;
		return ret;
	}
}

/**
 * Get the current GSTCC value
 *
 */
static int ioc_get_gstc(struct sdec_fh *fh, void *arg)
{
	int ret;
	LX_SDEC_GSTC_PARAM_T *param = arg;
	LX_SDEC_CLK_VALUE_T *val = param->value;

	FUNC_TRACE_ENTER();

	ret = get_gstc(param->index, val);
	CHECK_ERROR(ret, return ret, "Error(%d) in get_gstc", ret);

	FUNC_TRACE_EXIT();

	return 0;
}

/**
 * Set the current GSTCC value
 *
 * @def SDEC_IOC_CLK_GET_GSTC
 * @param	ch_ctrl 		[in	] ch_ctrl handle for channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_set_gstc(struct sdec_fh *fh, void *arg)
{
	struct te_config *cfg = te_get_config();
	int ret;
	LX_SDEC_GSTC_PARAM_T *param = arg;
	LX_SDEC_CLK_VALUE_T *val = param->value;
	u32 ext_incr, ext_unit;

	switch (param->time_base) {
	case LX_SDEC_GSTC_TIME_BASE_45KHZ:
		ext_incr = 1;
		ext_unit = 600;
		break;

	case LX_SDEC_GSTC_TIME_BASE_180KHZ:
		ext_incr = 1;
		ext_unit = 150;
		break;

	case LX_SDEC_GSTC_TIME_BASE_90KHZ:
	default:
		ext_incr = 1;
		ext_unit = 300;
		break;
	}

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_SetGstccConf(param->index, ext_incr, ext_unit,
					  true);
		CHECK_ERROR(ret, return ret,
			    "Error(%d) in TE_REG_SetGstccConf", ret);

		ret = TE_REG_SetGstcc(param->index, val->base_32,
				      val->base_31_0, val->ext);
		CHECK_ERROR(ret, return ret,
			    "Error(%d) in TE_REG_SetGstcc", ret);
	} else {
		log_error("Not Support in this environment");
		return -EPERM;
	}

	return 0;
}

static int ioc_set_freq(struct sdec_fh *fh, void *arg)
{
	u32 *frequency = arg;

	return set_dco_freq(*frequency);
}

int sdec_debug_stcc_enable(struct sdec_channel *channel, bool en)
{
	struct sdec_clock *clk = channel->clk;
	struct te_config *cfg = te_get_config();

	CHECK_PARAM(!clk, "invalid ch(%d)", channel->num);
	CHECK_PARAM(clk->enable, "[%d]pcr recovery enabled - disable first",
				 channel->num);

	if (!cfg->no_stcc_bug) {
		TE_REG_EnableStcc(clk->idx, en);
	} else {
		te_ipc_enable_stcc(clk->idx, en);
	}

	return 0;
}

// TOOD: MODIFY PCR RECOVERY CONTROL !!!
int sdec_set_pcr_pid(struct sdec_channel *channel, u16 pid, bool is_main)
{
	struct sdec_clock *clk = channel->clk;

	CHECK_PARAM(pid >= 0x1fff, "invalid pid(0x%x)", pid);
	CHECK_PARAM(!clk, "invalid ch(%d)", channel->num);

	log_clock("%s(ch=%d,pid=0x%x)", __FUNCTION__, channel->num, pid);

	mutex_lock(&clock_mutex);
	set_clock_input_mode(clk, channel->input_port);
	set_pcr_pid(clk, pid, is_main);
	clk->enable = true;
	mutex_unlock(&clock_mutex);

	return 0;
}

int sdec_cancel_pcr_pid(struct sdec_channel *channel)
{
	struct sdec_clock *clk = channel->clk;

	CHECK_PARAM(!clk, "invalid ch(%d)", channel->num);

	mutex_lock(&clock_mutex);
	cancel_pcr_pid(clk);
	mutex_unlock(&clock_mutex);

	return 0;
}

static inline void set_delayed_pcr_to_stc(struct sdec_clock *clk)
{
	union clock_tick *stc = &clk->irq_data.stc;
	u32 tick_45khz = clk->irq_data.pcr.value >> 1;

	tick_45khz -= clk->delay;
	stc->value = (u64)tick_45khz << 1;

	TE_REG_SetStcc(clk->idx, stc->hi, stc->lo);
}

/* isr function */
int sdec_clock_irq_handler(struct sdec_channel *channel)
{
	struct te_config *cfg = te_get_config();
	struct sdec_clock *clk = channel->clk;
	union clock_tick *tick;
	u32 e;

	if (cfg->no_stcc_bug) {
		log_error("no stcc & isr, it must be error!");
		return -ENODEV;
	}

	if (!clk)
		return -ENODEV;

	spin_lock(&clk->spinlock);

	tick = &clk->irq_data.pcr;
	TE_REG_GetLatchedPcr(clk->idx, &tick->hi, &tick->lo, &e);

	if (clk->delayed_mode && clk->reset_discard == RESET_DISCARD_COUNT) {
		set_delayed_pcr_to_stc(clk);
	} else { //normal operation
		tick = &clk->irq_data.stc;
		TE_REG_GetLatchedStcc(clk->idx, &tick->hi, &tick->lo, &e);
	}

	clk->irq_data.isr_time = (u32)te_get_ms_tick();

	if (fixup_pcr_latch_bug) {
		tick = &clk->irq_data.isr_stc;
		TE_REG_GetLiveStcc(clk->idx, &tick->hi, &tick->lo, &e);
	}

	spin_unlock(&clk->spinlock);

	TE_REG_SetStccLatchEnable(clk->idx, true);

	queue_work(clock_workqueue(channel), &clk->work);

	return 0;
}

int sdec_get_stc(struct sdec_channel *channel, struct lx_sdec_clk_value *value)
{
	int ret;

	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);

	mutex_lock(&clock_mutex);
	ret = get_live_stc(channel->num, value);
	mutex_unlock(&clock_mutex);

	return ret;
}

/* Debug function for checking clock precision
 * Due to precise checking disable irq when check the time */
int sdec_debug_get_stc_systime(struct sdec_channel *channel,
			       struct lx_sdec_clk_value *value,
			       u64 *ktime_us)
{
	int ret;
	unsigned long flags;

	mutex_lock(&clock_mutex);

	local_irq_save(flags);
	ret = get_live_stc(channel->num, value);
	*ktime_us = te_get_us_tick();
	local_irq_restore(flags);

	mutex_unlock(&clock_mutex);

	return ret;
}

int sdec_debug_get_gstc_systime(struct sdec_channel *channel, u8 idx,
			        struct lx_sdec_clk_value *value,
			        u64 *ktime_us)
{
	int ret;
	unsigned long flags;

	mutex_lock(&clock_mutex);

	local_irq_save(flags);
	ret = get_gstc(idx, value);
	*ktime_us = te_get_us_tick();
	local_irq_restore(flags);

	mutex_unlock(&clock_mutex);

	return ret;
}

int sdec_set_pcr_recovery(struct sdec_channel *channel,
			  enum lx_sdec_pcr_cmd cmd)
{
	int ret;

	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);

	mutex_lock(&clock_mutex);
	ret = pcr_recovery_command(channel->clk, cmd);
	mutex_unlock(&clock_mutex);

	return ret;
}

/* set usb ci delay in ms */
int sdec_set_pcr_delay(struct sdec_channel *channel, u32 delay)
{
	unsigned long flags;
	struct sdec_clock *clk;

	CHECK_PARAM(!channel->clk, "invalid ch(%d)", channel->num);
	log_noti("set pcr delay = %u ms", delay);

	clk = channel->clk;

	spin_lock_irqsave(&clk->spinlock, flags);

	if (delay) {
		clk->delay = delay * 45; // 45 Khz tick
		clk->delayed_mode = true;
	} else {
		clk->delay = 0;
		clk->delayed_mode = false;
	}

	spin_unlock_irqrestore(&clk->spinlock, flags);

	return 0;
}

/* debug functions */
#define dprintf(fmt, args...) seq_printf(m, fmt, ##args)

static int debug_show_pcr_recovery(struct sdec_device *dev, struct seq_file *m)
{
	int i;
	unsigned long flags;
	struct clock_irq_data data;

	dprintf("PCR RECOVERY STATUS\n");
	dprintf("%3s %2s %4s %6s %9s %9s %8s %8s %8s\n", "Num", "En", "Main",
		"PID", "STC", "PCR", "Freq", "Time", "Input");

	mutex_lock(&clock_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_clock *clk = dev->channels[i].clk;
		if (!clk)
			continue;

		spin_lock_irqsave(&clk->spinlock, flags);
		data = clk->irq_data;
		spin_unlock_irqrestore(&clk->spinlock, flags);

		dprintf("[%d] %2d %4d 0x%04x %d%08x %d%08x %8d %08x ",
			clk->idx, clk->enable, clk->is_main, clk->pid,
			data.stc.hi, data.stc.lo, data.pcr.hi, data.pcr.lo,
			clk->freq, data.isr_time);
		switch (clk->input_mode) {
		case INPUT_FROM_PVR:
			dprintf("PVR\n");
			break;
		case INPUT_FROM_USBCI:
			dprintf("USBCI\n");
			break;
		case INPUT_FROM_DEMOD:
		default:
			dprintf("DEMOD\n");
			break;
		}
	}
	mutex_unlock(&clock_mutex);

	return 0;
}

enum {
	CLK_DEBUG_ID_DCO_FREQUENCY = 0,
	CLK_DEBUG_ID_MAX,
};

static int debug_dev_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;

	switch (item->flags) {
	case CLK_DEBUG_ID_DCO_FREQUENCY:
		dprintf("%u\n", dco_dev.freq);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_dev_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	u32 freq;

	switch (item->flags) {
	case CLK_DEBUG_ID_DCO_FREQUENCY:
		freq = simple_strtoul(str, (char **)NULL, 0);
		ret = set_dco_freq(freq);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_dev_ops = {
	.show = debug_dev_show,
	.write = debug_dev_write,
};

static const struct te_debug_item_info debug_dev_list[] = {
	DBGITM_SIM("dco_freq", &debug_dev_ops, CLK_DEBUG_ID_DCO_FREQUENCY),
};

static void init_debug(struct sdec_device *dev)
{
	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_PCR_RECOVERY,
					debug_show_pcr_recovery);

	debug_create_item_files(debug_dev_list, dev, dev->debug.dir);
}

static int dev_ioctl_param(void *priv, unsigned int cmd, void *arg,
			   struct te_ioctl_ptr_param *param)
{
	if (cmd == SDEC_IOC_CLK_GET_GSTC) {
		LX_SDEC_GSTC_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->value);
		param->kernel_ptr = (void **)&p->value;
		param->size = sizeof(*p->value);
		param->dir = _IOC_READ;
	} else if (cmd == SDEC_IOC_CLK_SET_GSTC) {
		LX_SDEC_GSTC_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->value);
		param->kernel_ptr = (void **)&p->value;
		param->size = sizeof(*p->value);
		param->dir = _IOC_WRITE;
	}

	return 0;
}

static const struct sdec_ioctl_info ioctls[] = {
	IOC_INFO(SDEC_IOC_CLK_SET_PCR_PID, ioc_set_pcr_pid),
	IOC_INFO(SDEC_IOC_CLK_SET_PCR_RECOVERY, ioc_set_pcr_recovery),
	IOC_INFO(SDEC_IOC_CLK_CANCEL_PCR_PID, ioc_cancel_pcr_pid),
	IOC_INFO(SDEC_IOC_CLK_GET_STC_PCR, ioc_get_stc_pcr),
	IOC_INFO(SDEC_IOC_CLK_GET_LIVE_STC, ioc_get_live_stc),

	IOC_INFO(SDEC_IOC_CLK_SET_GSTC, ioc_set_gstc, true),
	IOC_INFO(SDEC_IOC_CLK_GET_GSTC, ioc_get_gstc, true),
	IOC_INFO(SDEC_IOC_CLK_SET_DCO_FREQ, ioc_set_freq, true),
};

static int dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return sdec_do_ioctl(priv, cmd, arg, clock_mutex, ioctls);
}

/* isr callback */
static int ts_pcr_callback(void *msg, void *arg)
{
	IPC_MSG_TS_PCR_DATA_T *data = msg;
	struct sdec_device *dev = arg;
	struct sdec_channel *channel;
	struct sdec_clock *clk;
	union clock_tick *tick;

	channel = sdec_get_channel(dev, data->ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", data->ch);

	clk = channel->clk;
	if (!clk)
		return -ENODEV;

	spin_lock(&clk->spinlock);

	tick = &clk->irq_data.pcr;
	tick->hi = (data->pcr & 0x80000000UL) ? 1 : 0;
	tick->lo = data->pcr << 1;

	tick = &clk->irq_data.stc;
	tick->hi = (data->stcc & 0x80000000UL) ? 1 : 0;
	tick->lo = data->stcc << 1;

	clk->irq_data.isr_time = (u32)te_get_ms_tick();

	spin_unlock(&clk->spinlock);

	//log_error("stc:%08x pcr:%08x", data->stcc, data->pcr);
	queue_work(clock_workqueue(channel), &clk->work);
	return 0;
}

static int dev_suspend(struct sdec_device *dev)
{
	te_ipc_register_pcr_callback(NULL, NULL);
	return 0;
}

static void resume_pcr_recovery(struct sdec_clock *clk)
{
	struct te_config *cfg = te_get_config();

	if (clk->pid == 0x1FFF)
		return;

	clk_noti(clk, "Resume PcrRecovery");

	if (!cfg->no_stcc_bug) {
		TE_REG_ResetStcc(clk->idx);
	} else {
		te_ipc_reset_stcc(clk->idx);
	}
	set_pcr_pid(clk, clk->pid, clk->is_main);
}

static int dev_resume(struct sdec_device *dev)
{
	int i;
	struct sdec_channel *channel;

	init_dco_clock();
	te_ipc_register_pcr_callback(ts_pcr_callback, dev);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		if (channel->clk) {
			set_clock_input_mode(channel->clk, channel->input_port);
			resume_pcr_recovery(channel->clk);
		}
	}

	return 0;
}

static int dev_init(struct sdec_device *dev)
{
	int i, j;
	struct sdec_channel *channel;
	struct sdec_clock *clk;
	struct sdec_config *cfg = sdec_get_config();

	fixup_pcr_latch_bug = cfg->fixup_pcr_latch_bug;

	/* init pcr recovery variables */
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		if (channel->info->is_sub_channel)
			continue;

		clk = kzalloc(sizeof(*clk), GFP_KERNEL);
		CHECK_ERROR(!clk, return -ENOMEM, "no memory");

		clk->idx = channel->num;
		clk->pid = 0x1FFF;

		for (j = 0; j < NUM_WINDOW; j++)
			clk->window[j] = &clk->window_data[j];

		for (j = NUM_WINDOW; j < (NUM_WINDOW * 2 - 1); j++)
			clk->window[j] = &clk->window_data[j % NUM_WINDOW];

		clk->mode = MANUAL_RECOVERY_MODE;

		/* pcr recovery work */
		INIT_WORK(&clk->work, pcr_recovery_work);
		spin_lock_init(&clk->spinlock);

		channel->clk = clk;
	}

	init_dco_clock();
	te_ipc_register_pcr_callback(ts_pcr_callback, dev);

	init_debug(dev);

	return 0;
}

static void dev_release(struct sdec_device *dev)
{
}

static const struct sdec_ioctl ioctl_clock = {
	.magic = SDEC_IOC_CLK_MAGIC,
	.func = dev_ioctl,
	.get_user_param = dev_ioctl_param,
};

const struct sdec_sub_driver sdec_clock_driver = {
	.name = "sdec_clock",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,

	.ioctl = &ioctl_clock,
};
