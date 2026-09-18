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
 *  sci driver
 *
 *  @author	Yeonju Lee ( yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2019-04-22
 *  @note	Additional information.
 */

#include "os_util.h"

#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/log2.h>
#include <linux/bitops.h>

#include "sci_impl.h"
#include "sci_kapi.h"
#include "sci_reg.h"

#define INVERT_NS(n)	do { (n) = (n) ? 0 : 1;} while (0)
#define SCI_INPUT_CLK 198
#define SCI_INPUT_CLK_DIV 32

/* default value */
#define SCI_IFSD	254	/* ARIB_STD-B61 */
#define SCI_FS		372
#define SCI_DI		1
#define SCI_BWI		4

#define I_BLOCK				0x00
#define I_BLOCK_NS			0x40
#define I_BLOCK_MORE_DATA		0x20
#define GET_I_BLOCK_NS(pcb)		((pcb >> 6) & 0x01)

#define R_BLOCK				0x80
#define R_BLOCK_NR			0x10
#define GET_R_BLOCK_NS(pcb)		((pcb >> 4) & 0x01)
#define GET_R_BLOCK_ERROR(pcb)		(pcb & 0x0F)

#define S_BLOCK				0xC0
#define S_BLOCK_RESPONSE		0x20

#define S_BLOCK_TYPE			0x1F
#define S_BLOCK_RESYNC			0x00
#define S_BLOCK_IFS			0x01
#define S_BLOCK_ABORT			0x02
#define S_BLOCK_WTX			0x03
#define S_BLOCK_WTX_RESPONSE		(S_BLOCK_RESPONSE|S_BLOCK_WTX)

#define S_BLOCK_ERROR_VPP		(S_BLOCK|0x24)

#define RESYNC_REQUEST			(S_BLOCK|S_BLOCK_RESYNC)
#define RESYNC_RESPONSE			(S_BLOCK|S_BLOCK_RESYNC|S_BLOCK_RESPONSE)

#define IFS_REQUEST			(S_BLOCK|S_BLOCK_IFS)
#define IFS_RESPONSE			(S_BLOCK|S_BLOCK_IFS|S_BLOCK_RESPONSE)

#define ABORT_REQUEST			(S_BLOCK|S_BLOCK_ABORT)
#define ABORT_RESPONSE			(S_BLOCK|S_BLOCK_ABORT|S_BLOCK_RESPONSE)

#define WTX_REQUEST			(S_BLOCK|S_BLOCK_WTX)
#define WTX_RESPONSE			(S_BLOCK|S_BLOCK_WTX|S_BLOCK_RESPONSE)

#define BIT_TA1		0
#define BIT_TA2		1
#define BIT_TB1		2
#define BIT_TB2		3
#define BIT_TC1		4
#define BIT_TC2		5
#define BIT_TD1		6
#define BIT_TD2		7

#define DEBUG_PRINT_LEN	1024

static int activate(struct sci_dev *dev);
static int read_next_atr_data(struct sci_dev *dev, u8 *data, u8 len);
static void init_xfer_event(struct sci_dev *dev, u8 mask);
static int read_next_atr_data(struct sci_dev *dev, u8 *data, u8 len);

static void deactivate(struct sci_dev *dev);

#ifdef USE_ATR_POLLING_MODE
static int poll_atr_data(struct sci_dev *dev, u8 *data, u8 len, int timeout);
#endif

typedef int (*sub_decoder_t)(struct atr_decoder *d, struct atr *atr, u8 v);

static int timeout_atr = 895;
static int timeout_eor = 420;
static int timeout_recv = 250;

module_param_named(sci_atr_timeout, timeout_atr, int, 0644);
module_param_named(sci_eor_timeout, timeout_eor, int, 0644);
module_param_named(sci_frn_timeout, timeout_recv, int, 0644);

static const char *get_phase_str(enum sci_phase phase)
{
	switch (phase) {
	case SCI_PHASE_IDLE:
		return "PHASE-IDLE";
	case SCI_PHASE_COLD_RESET:
		return "PHASE-COLD_RESET";
	case SCI_PHASE_ATR:
		return "PHASE-ATR";
	case SCI_PHASE_BYTE_MESSAGE:
		return "PHASE-BYTE_MESSAGE";
	case SCI_PHASE_BLOCK_MESSAGE:
		return "PHASE-BLOCK_MESSAGE";
	case SCI_PHASE_DEACTIVATION:
		return "PHASE-DEACTIVATION";
	case SCI_PHASE_WARM_RESET:
		return "PHASE-WARM_RESET";
	default:
		return "Invalid";
	}
}

static const char *get_debug_print_str(enum sci_debug_print mode)
{
	switch (mode) {
	case SCI_DEBUG_PRINT_ATR:
		return "ATR";
	case SCI_DEBUG_PRINT_TX_APDU:
		return "TX";
	case SCI_DEBUG_PRINT_RX_APDU:
		return "RX";
	default:
		return "INVALID";
	}
}

void sci_set_debug_print(struct sci_dev *dev, bool enable)
{
	dev->debug.print_data = enable;
}

bool sci_get_debug_print(struct sci_dev *dev)
{
	return dev->debug.print_data;
}

static void sci_debug_print(struct sci_dev *dev, enum sci_debug_print mode,
			    u8 *data, u32 size)
{
	int i, len, str_len;
	char *str;

	str_len = DEBUG_PRINT_LEN;
	str = kcalloc(1, str_len, GFP_KERNEL);
	CHECK_ERROR(!str, return, "no memory");

	len = snprintf(str, str_len, "%s(%d): ", get_debug_print_str(mode),
		       size);

	for (i = 0; i < size; i++) {
		len += snprintf(str + len, str_len - len, "%02x ", data[i]);
		if (len >= str_len)
			break;
	}
	log_noti("%s", str);

	kfree(str);
}

static const char *get_reg_card_stat_str(enum sci_reg_status status)
{
	switch (status) {
	case SCI_REG_STATUS_READY:
		return "CARD-READY";
	case SCI_REG_STATUS_DETECTED:
		return "CARD-DETECTED";
	case SCI_REG_STATUS_ACTIVE:
		return "CARD-ACTIVE";
	case SCI_REG_STATUS_FAILED:
		return "CARD-FAILED";
	default:
		return "CARD-INVALID";
	}
}

static char *get_reg_intr_str(char *str, u8 intr, u8 mask)
{
	u8 val;
	const char *s[] = {"FRF", "FRNE", "FTF", "FTE", "EOR", "EOT", "ERR",
			   "CDPWR"};
	int v[] = {SCI_IRQ_FRF, SCI_IRQ_FRNE, SCI_IRQ_FTF, SCI_IRQ_FTE,
		   SCI_IRQ_EOR, SCI_IRQ_EOT, SCI_IRQ_ERR, SCI_IRQ_CDPWR};
	int str_len = DEBUG_PRINT_LEN;
	int i, len = 0;
	bool is_first = true;

	val = intr&mask;
	for (i = 0; i < ARRAY_SIZE(s); i++) {
		if (val & v[i]) {
			if (is_first) {
				is_first = false;
			} else {
				len += snprintf(str+len, str_len - len, " & ");
			}
			len += snprintf(str+len, str_len-len, "%s", s[i]);
		}
		if (len >= str_len)
			break;
	}

	if (!len)
		snprintf(str, str_len, "CLEAR");

	return str;
}

static char *get_reg_stat_str(char *str, u8 status)
{
	const char *s[] ={"RX_ON", "TX_ON", "OK", "BP"};
	int v[] = {SCI_STAT_RX_ON, SCI_STAT_TX_ON, SCI_STAT_OK, SCI_STAT_BP};
	int str_len = DEBUG_PRINT_LEN;
	int i, len = 0;
	bool is_first = true;

	for (i = 0; i < ARRAY_SIZE(s); i++) {
		if (status & v[i]) {
			if (is_first) {
				is_first = false;
			} else {
				len += snprintf(str+len, str_len - len, " & ");
			}
			len += snprintf(str+len, str_len-len, "%s", s[i]);
		}
		if (len >= str_len)
			break;
	}

	if (!len)
		snprintf(str, str_len, "CLEAR");

	return str;
}

static char *get_reg_err_stat_str(char *str, u8 err_status)
{
	const char *s[] = {"Parity_ERR", "Byte_ERR-ATR", "WWT_Timeout",
			   "CWT_Timeout-ATR", "BWT_Timeout", "Block_ERR"};
	int v[] = {SCI_ERR_INTR_PHY, SCI_ERR_INTR_BYTE, SCI_ERR_INTR_WWT,
		   SCI_ERR_INTR_CWT, SCI_ERR_INTR_BWT, SCI_ERR_INTR_BLOCK};
	int str_len = DEBUG_PRINT_LEN;
	int i, len = 0;
	bool is_first = true;

	for (i = 0; i < ARRAY_SIZE(s); i++) {
		if (err_status & v[i]) {
			if (is_first) {
				is_first = false;
			} else {
				len += snprintf(str+len, str_len - len, " & ");
			}
			len += snprintf(str+len, str_len-len, "%s", s[i]);
		}
		if (len >= str_len)
			break;
	}

	if (!len)
		snprintf(str, str_len, "CLEAR");

	return str;
}

static void debug_print_status(struct sci_debug *d)
{
	u8 card_status = sci_reg_get_card_status();
	u8 status = sci_reg_get_status();
	u8 err_status = sci_reg_get_error_status();
	u8 intr = sci_reg_get_interrupt_status();
	u8 mask = sci_reg_get_interrupt_mask();
	char *str;

	str = kcalloc(1, DEBUG_PRINT_LEN, GFP_KERNEL);
	CHECK_ERROR(!str, return, "no memory");

	log_noti("[INTR]STAT:%08x, MASK:%08x (%s)", intr, mask,
		 get_reg_intr_str(str, intr, mask));
	log_noti("[REG] %s, STAT:%s", get_reg_card_stat_str(card_status),
		 get_reg_stat_str(str, status));
	log_noti("[REG] ERR:%s", get_reg_err_stat_str(str, err_status));

	kfree(str);
}

static void init_xfer_event(struct sci_dev *dev, u8 mask)
{
	dev->event_status = 0;
	dev->event_mask = mask |
	    SCI_EVENT_CARD_POWER | SCI_EVENT_TX_ERROR | SCI_EVENT_RX_ERROR;
}

struct sci_dev *sci_get_device(struct te_device *dev)
{
	struct te_subdev *sd;
	sd = te_get_subdev(dev, SCI_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_sci_device(sd);
}

static void set_baudrate(u32 FS, u32 DI, u32 operating_clock_khz)
{
	unsigned int baud, br, ft;
	const unsigned int clk_div_table[8] = { 2, 4, 6, 8, 12, 16, 24, 32 };
	u8 div = sci_reg_get_clkdiv();

#define SCI_CRD_CLK_ADJ_MHZ_TO_KHZ 1000
#define SCI_INPUT_CLK 198

	CHECK_ERROR(div >= 8, return, "clock div error(%d)", div);

	baud = (SCI_INPUT_CLK * SCI_CRD_CLK_ADJ_MHZ_TO_KHZ * FS)
	    / (DI * clk_div_table[div] * operating_clock_khz);

	br = baud / 10;
	ft = baud % 10;

	r_log("%s(fs:%d,di:%d,clk:%d,br:0x%x,ft:0x%x)", __func__, FS, DI,
	      operating_clock_khz, br, ft);
	sci_reg_set_baud(br, ft);
}

static int decode_clock_rate_conversion(struct atr *atr, u8 v)
{
	u8 bits_8_5;
	u8 bits_4_1;
	struct {
		u16 Fi;
		u8 fmax;
	} Fi_fmax_list[16] = {
		{372, 4}, {372, 5}, {558, 6}, {744, 8},
		{1116, 12}, {1488, 16}, {1860, 20}, {0, 0},
		{0, 0}, {512, 5}, {768, 7 /*7.5 */ }, {1024, 10},
		{1536, 15}, {2048, 20}, {0, 0}, {0, 0},
	};
	u8 Di_list[16] = {
		0, 1, 2, 4, 8, 16, 32, 64,
		12, 20, 0, 0, 0, 0, 0, 0,
	};

	bits_8_5 = v >> 4;
	bits_4_1 = v & 0xF;

	atr->Fi = Fi_fmax_list[bits_8_5].Fi;
	atr->fmax = Fi_fmax_list[bits_8_5].fmax;
	if (atr->Fi == 0) {
		log_error("Fi is RFU\n");
		return -EINVAL;
	}
	atr->Di = Di_list[bits_4_1];
	if (atr->Di == 0) {
		log_error("Di is RFU\n");
		return -EINVAL;
	}

	r_log("Fi=%d, fmax=%d, Di=%d", atr->Fi, atr->fmax, atr->Di);

	return 0;
}

static int wait_xfer_event(struct sci_dev *dev, u32 timeout)
{
	int rc;
	if (!dev->event_mask)
		return 0;

	rc = wait_event_interruptible_timeout(dev->wq, dev->event_status != 0,
					      msecs_to_jiffies(timeout));

	if (rc == 0) {
		log_error("timeout occured(%d)", timeout);
		return -ETIME;
	} else if (rc < 0) {
		return rc;
	}

	return 0;
}

int sci_activate(struct sci_dev *dev)
{
	int rc;
	u8 status = sci_reg_get_card_status();

	log_noti("%s(%s)", __func__, get_reg_card_stat_str(status));

	switch (status) {
	case SCI_REG_STATUS_READY:
		log_error("card is not inserted\n");
		rc = -EIO;
		break;
	case SCI_REG_STATUS_DETECTED:
	case SCI_REG_STATUS_ACTIVE:
		rc = activate(dev);
		if (rc) {
			log_error("sci_activate failed(%d)", rc);
			rc = -EIO;
		}
		break;
	case SCI_REG_STATUS_FAILED:
	default:
		log_error("status is failed. ");
		rc = -EIO;
		break;
	}

	return rc;
}

/* start_atr == SCI_CoreRegInitforATR */

static void start_atr(struct sci_dev *dev)
{

	// Clear FIFO
	sci_reg_command(CMD_CLR_FR | CMD_CLR_FT);
	sci_reg_reset_low(SCI_REG_ENABLE);
	sci_reg_power_mon(SCI_REG_POWER_LOW);

	dev->rx_buffer.idx = 0;
	dev->rx_buffer.ridx = 0;

	/* Mask IRQs */
#ifdef USE_ATR_POLLING_MODE
	sci_reg_set_rxfifo_depth(MAX_RF_DEPTH);
	sci_reg_disable_interrupt(SCI_IRQ_ALL);
#else
	/* ATR Reception using burst mode for TS, TA0 */
	sci_reg_set_rxfifo_depth(2);
	sci_reg_disable_interrupt(SCI_IRQ_EOR);	/* Burst mode */
	sci_reg_enable_interrupt(SCI_IRQ_FRF | SCI_IRQ_ERR | SCI_IRQ_CDPWR);

	init_xfer_event(dev, SCI_EVENT_RXFIFO_FULL);
#endif
	sci_reg_command(CMD_POWER_ON);
	sci_reg_command(CMD_RX_EN);
}

static void stop_atr(struct sci_dev *dev)
{
	sci_reg_disable_interrupt(SCI_IRQ_ALL);
	sci_reg_command(CMD_NULL);
}

static void set_default_atr_value(struct atr *atr)
{
	atr->Fi = SCI_FS;
	atr->fmax = 5;
	atr->Di = 1;
	atr->guard_time = 0;
	atr->transmission_protocol = 0;

	atr->T1_params.ifsc = 32;
	atr->T1_params.cwi = 13;
	atr->T1_params.bwi = SCI_BWI;
	atr->T1_params.edc = 0;

	atr->T15_params.clock_stop = 0;
	atr->T15_params.class_supported = 1;
	atr->T15_params.spu = 0;

}

static int config_interface(struct sci_dev *dev, struct atr *atr)
{

	r_log("config interface - start");

	/* Refer to 6.3 information exchange in ISO7816-3 */
	if (!test_bit(BIT_TA2, &atr->data_bits)) {
		log_error("TA2 absent - Not support this mode\n");
		return -EIO;
	}

	/* only support T=1 */
	if (atr->transmission_protocol != 1) {
		log_error("transmission protocol != 1\n");
		return -EIO;
	}
	sci_reg_set_mode(SCI_REG_BLOCK_MODE);

	sci_reg_set_agt(atr->guard_time);
	sci_reg_set_bgt_delay(BGT_DLY_22_ETU);	/* block guard time */

	r_log("addtional guard time=%d", atr->guard_time);

	dev->cwi = atr->T1_params.cwi;
	dev->bwi = atr->T1_params.bwi;
	dev->Fi = atr->Fi;
	dev->Di = atr->Di;
	dev->wtx_bwt = 0;

	sci_reg_set_timeout(dev->bwi, dev->cwi);
	sci_reg_set_rx_change(false);
	sci_reg_set_endian(SCI_REG_BIG_ENDIAN);

	sci_reg_set_conversion(atr->conversion);
	sci_reg_set_max_repetition(0x03);

	if (atr->T1_params.edc)
		sci_reg_set_edc(EDC_CRC);
	else
		sci_reg_set_edc(EDC_LRC);	/* EDC of ARIB = LRC */

	// TODO: CHECK DI
	sci_reg_set_di(dev->Di);	/* Di or bit value ??? */
	set_baudrate(dev->Fi, dev->Di, dev->clock_supplied_khz);
	sci_reg_set_flow_control(3, SCI_REG_ENABLE, SCI_REG_ENABLE);

	sci_reg_set_rxfifo_depth(MAX_RF_DEPTH);
	sci_reg_set_txfifo_depth(MAX_TF_DEPTH);

	dev->phase = SCI_PHASE_BLOCK_MESSAGE;

	r_log("config interface - done");

	return 0;
}

static void set_tx_block(struct sci_dev *dev, u8 nad, u8 pcb, u8 len, u8 *inf)
{
	int i;
	struct block_frame *f = &dev->tx_block;

	f->nad = nad;
	f->pcb = pcb;
	f->len = len;
	for (i = 0; i < len; i++)
		f->inf[i] = inf[i];
}

static int read_first_atr_data(struct sci_dev *dev, u8 *data)
{
#ifdef USE_ATR_POLLING_MODE
	return poll_atr_data(dev, data, 2, timeout_atr);
#else
	int rc;
	rc = wait_xfer_event(dev, timeout_atr);
	if (rc) {
		return rc;
	}
	sci_reg_read_data(data, 2);
	return 0;
#endif
}

static int read_next_atr_data(struct sci_dev *dev, u8 *data, u8 len)
{
#ifdef USE_ATR_POLLING_MODE
	return poll_atr_data(dev, data, len, timeout_recv);
#else
	int rc;
	unsigned long flags;

	log_atr("next data length=%d\n", len);

	spin_lock_irqsave(&dev->lock, flags);

	init_xfer_event(dev, SCI_EVENT_RXFIFO_FULL);
	sci_reg_set_rxfifo_depth(len);

	spin_unlock_irqrestore(&dev->lock, flags);

	/* wait for full */
	rc = wait_xfer_event(dev, timeout_recv);
	if (rc < 0) {
		if (rc == -ETIME) {
			log_error("TIMEOUT(%d)", timeout_recv);
			debug_print_status(&dev->debug);
		}
		return rc;
	}

	sci_reg_read_data(data, len);

	return 0;
#endif
}

static int read_atr(struct sci_dev *dev, struct atr *atr)
{
	int i, widx, rc;
	u8 next_byte, historical_byte, Yi;
	u8 *data;

	if (dev->phase != SCI_PHASE_COLD_RESET) {
		log_error("invalid phase (%d)\n", dev->phase);
		return -EINVAL;
	}

	dev->phase = SCI_PHASE_ATR;

	start_atr(dev);

	data = atr->data;

	rc = read_first_atr_data(dev, data);
	if (rc) {
		log_error("ATR-0: TS, T0\n");
		goto failed;
	}
	widx = 2;
	historical_byte = data[1] & 0x0f;

	i = 1;
	while (1) {
		/* count TAi ~ TDi */
		Yi = data[widx - 1] >> 4;	// TDi-1
		next_byte = (Yi >> 0 & 0x1) + (Yi >> 1 & 0x1)
		    + (Yi >> 2 & 0x1) + (Yi >> 3 & 0x1);

		if (next_byte == 0)
			break;

		if (widx + next_byte <= MAX_ATR_LEN) {
			rc = read_next_atr_data(dev, data + widx, next_byte);
			if (rc < 0) {
				log_error("ATR-%d: widx=%d, next_byte=%d",
					  i, widx, next_byte);
				goto failed;
			}
			widx += next_byte;
		} else {
			log_error("over max atr length");
			goto failed;
		}
		i++;
	}

	next_byte = historical_byte + 1;	/* historical byte + TCK */

	if (widx + next_byte <= MAX_ATR_LEN) {
		rc = read_next_atr_data(dev, data + widx, next_byte);
		if (rc < 0) {
			log_error("ATR-TC\n");
			goto failed;
		}
		widx += next_byte;
	} else {
		log_error("ATR-TC: Over max ATR Length");
		goto failed;
	}

	stop_atr(dev);

	atr->len = widx;

	if (dev->debug.print_data) {
		sci_debug_print(dev, SCI_DEBUG_PRINT_ATR, &data[0], atr->len);
	}

	return 0;

 failed:
	sci_reg_disable_interrupt(SCI_IRQ_ALL);
	deactivate(dev);
	return -EIO;
}

static int decode_atr_ta(struct atr_decoder *d, struct atr *atr, u8 v)
{
	if (d->idx < 2) {
		atr->TA[d->idx] = v;
		set_bit(BIT_TA1 + d->idx, &atr->data_bits);

		if (d->idx == 0) {	// TA1
			return decode_clock_rate_conversion(atr, v);
		} else if (d->idx == 1) {	// TA2
			atr->negotiable = (v & 0x80) ? 0 : 1;
			atr->implicit_parameter = (v & 0x10) ? 1 : 0;
			atr->TA2_transmission_protocol = v & 0x0f;
			atr->transmission_protocol =
			    atr->TA2_transmission_protocol;

			r_log
			    ("TA2: negotiable=%d, implicit_params=%d, protocol=%d",
			     atr->negotiable, atr->implicit_parameter,
			     atr->TA2_transmission_protocol);
		}
	} else {
		if (d->T == 1) {
			struct atr_T1 *p = &atr->T1_params;

			if (p->count == 1) {	/* first TA for T=1 */
				p->TA = v;
				set_bit(BIT_TA1, &p->data_bits);

				if (v == 0 || v == 0xFF) {
					log_error("reserved IFSC value(%d)\n",
						  v);
					return -EINVAL;
				}
				p->ifsc = v;

				r_log("T=1 - IFSC=%d", v);
			} else {
				log_warning
				    ("Not defined parameter TA%d for T=1\n",
				     p->count);
			}
		} else if (d->T == 15) {
			struct atr_T15 *p = &atr->T15_params;

			if (p->count == 1) {	/* first TA for T=15 */
				p->TA = v;
				set_bit(BIT_TA1, &p->data_bits);

				p->clock_stop = v >> 6;
				p->class_supported = v & 0x3F;
				r_log("T=15 - clock stop=%d, class=0x%x",
				      p->clock_stop, p->class_supported);
			} else {
				log_warning
				    ("Not defined parameter TA%d for T=15\n",
				     p->count);
			}
		} else {
			log_warning("Not defined parameter TA for T=%d\n",
				    d->T);
		}
	}

	return 0;
}

static int decode_atr_tb(struct atr_decoder *d, struct atr *atr, u8 v)
{
	if (d->idx < 2) {
		atr->TB[d->idx] = v;
		set_bit(BIT_TB1 + d->idx, &atr->data_bits);
		/* TB1 and TB2 are deprecated from 7816-3-2006 */
	} else {
		//TB3, TB4
		if (d->T == 1) {
			struct atr_T1 *p = &atr->T1_params;

			if (p->count == 1) {	/* first TB for T=1 */
				p->TB = v;
				set_bit(BIT_TB1, &p->data_bits);

				p->cwi = v & 0x0F;
				p->bwi = v >> 4;
				if (p->bwi > 9) {
					log_error("reserved BWI value(%d)\n",
						  p->bwi);
					return -EINVAL;
				}
				r_log("T=1 - CWI=%d, BWI=%d", p->cwi, p->bwi);
			} else {
				log_warning
				    ("Not defined parameter TB%d for T=1\n",
				     p->count);
			}
		} else if (d->T == 15) {
			struct atr_T15 *p = &atr->T15_params;

			if (p->count == 1) {	/* first TB for T=15 */
				p->TB = v;
				set_bit(BIT_TB1, &p->data_bits);

				p->spu = v;
				r_log("T=15 - spu=0x%x", p->spu);
			} else {
				log_warning
				    ("Not defined parameter TB%d for T=15\n",
				     p->count);
			}
		} else {
			log_warning("Not defined parameter TB for T=%d\n",
				    d->T);
		}
	}

	return 0;
}

static int decode_atr_tc(struct atr_decoder *d, struct atr *atr, u8 v)
{
	if (d->idx < 2) {
		atr->TC[d->idx] = v;
		set_bit(BIT_TC1 + d->idx, &atr->data_bits);

		if (d->idx == 0) {	/* TC1 */
			atr->guard_time = v;
			r_log("ATR - guard time=%d", v);
		} else {	/* TC2 is specific to T=0 */
			r_log("T=0 - WI=%d", v);
		}
	} else {
		if (d->T == 1) {
			struct atr_T1 *p = &atr->T1_params;

			if (p->count == 1) {	/* first TB for T=1 */
				p->TC = v;
				set_bit(BIT_TC1, &p->data_bits);

				p->edc = v & 0x1;
				r_log("T=1 - EDC=%d", p->edc);
			} else {
				log_warning
				    ("Not defined parameter TC%d for T=1\n",
				     p->count);
			}
		} else {
			log_warning("Not defined parameter TC for T=%d\n",
				    d->T);
		}
	}

	return 0;
}

static int decode_atr_td(struct atr_decoder *d, struct atr *atr, u8 v)
{
	u8 T;

	T = v & 0xF;
	if (d->idx < 2) {
		atr->TD[d->idx] = v;
		set_bit(BIT_TD1 + d->idx, &atr->data_bits);

		if (d->idx == 0) {
			if (T == 15) {
				log_error("T=15 is invalid in TD1\n");
				return -EINVAL;
			}
			atr->TD1_transmission_protocol = T;
			atr->transmission_protocol = T;
		}
	}

	if (T < d->T) {
		log_error("not orderded T\n");
		return -EINVAL;
	}
	r_log("ATR - TD%d T=%d", d->idx + 1, T);

	d->T = T;
	d->Yi = (v >> 4) & 0xF;

	if (d->idx > 0) {
		if (T == 1) {
			atr->T1_params.count++;
		} else if (T == 15) {
			atr->T15_params.count++;
		}
	}

	return 0;
}

static int decode_atr_tck(struct atr *atr, u8 v, u8 len)
{
	int i;
	u8 calc;

	/* now we should just have TCK left */
	atr->TCK = v;

	/* now we calculate what the TCK should be so it can be checked
	 * by user logic if desired
	 */
	calc = 0;
	for (i = 1; i < len; i++) {
		calc ^= atr->data[i];
	}

	/* Validate TCK */
	if (calc != atr->TCK) {
		log_error("TCK(%d) != Calc_TCK(%d)", atr->TCK, calc);
		return -EINVAL;
	}

	return 0;
}

static int decode_atr(struct atr *atr)
{
	int i, rc, remained;
	u8 offset;
	u8 Yi, next_byte, v;
	struct atr_decoder d;
	const sub_decoder_t sub[4] = {
		decode_atr_ta, decode_atr_tb, decode_atr_tc, decode_atr_td,
	};

	g_log("decode atr - START");

	CHECK_ERROR(atr->len < 3, return -EINVAL, "ATR: len(%d)", atr->len);

	set_default_atr_value(atr);

	atr->TS = atr->data[0];
	atr->T0 = atr->data[1];

	offset = 2;

	/* check the first byte - it can have only two values */
	atr->conversion = (atr->TS == 0x3f) ? 0 : 1;
	atr->historical_bytes = atr->T0 & 0x0f;
	Yi = (atr->T0 >> 4) & 0xF;

	d.idx = 0;
	d.T = 0;

	while (Yi) {
		next_byte = (Yi >> 0 & 0x1) + (Yi >> 1 & 0x1)
		    + (Yi >> 2 & 0x1) + (Yi >> 3 & 0x1);

		if ((offset + next_byte) > atr->len) {
			log_error("idx:%d, offset:%d, len:%d",
				  d.idx, offset, atr->len);
			return -EINVAL;
		}
		/*
		   TA1, TB1, TC1, TA2, TB2 are global, TC2 is specific to T=0
		 */
		d.Yi = 0;
		for (i = 0; i < 4; i++) {
			if (Yi & (0x1 << i)) {
				v = atr->data[offset++];
				rc = sub[i] (&d, atr, v);
				if (rc) {
					log_error("decode ATR-T%c%d failed\n",
						  'A' + i, d.idx + 1);
					return rc;
				}

			}
		}
		Yi = d.Yi;
		d.idx++;
	}

	if (atr->historical_bytes) {
		if ((offset + atr->historical_bytes) > atr->len) {
			log_error("historical_bytes=%d, offset=%d, length=%d\n",
				  atr->historical_bytes, offset, atr->len);
			return -EINVAL;
		}
		memcpy(atr->historical, atr->data + offset,
		       atr->historical_bytes);
		offset += atr->historical_bytes;
	}

	remained = atr->len - offset;

	if (remained == 0) {
		if (atr->transmission_protocol != 0) {
			log_error("transmission_protocol != - but no TCK");
			return -EINVAL;
		}
		rc = 0;
	} else if (remained == 1) {
		v = atr->data[offset];
		rc = decode_atr_tck(atr, v, offset);
	} else {
		log_error("remianed length:%d", remained);
		return -EINVAL;
	}

#ifdef CHECK_ARIB_SPECIFICATION
	/* Validate T0 */
	if (atr->T0 != 0xF0 && atr->T0 != 0xF2) {
		log_error("Unexpected T0(0x%02x)\n", atr->T0);
		return -EINVAL;
	}

	// TODO: add here to check arib specifications
	if (atr->negotiable) {
		log_error("ARIB: negotiable\n");
	}

	if (atr->implicit_parameter) {
		log_error("ARIB: implicit_parameters\n");
	}

#endif
	g_log("decode atr - END");

	return rc;
}

static void cold_reset(struct sci_dev *dev)
{
	log_noti("%s(%s)", __func__, get_phase_str(dev->phase));

	sci_reg_disable_interrupt(SCI_IRQ_ALL);
	sci_reg_enable_interrupt(SCI_IRQ_CDPWR | SCI_IRQ_ERR);

	sci_reg_reset_low(SCI_REG_ENABLE);
	sci_reg_command(CMD_POWER_OFF);
	sci_reg_command(CMD_RESET);

	udelay(10);

	sci_reg_set_default_value();
	sci_reg_power_mon(SCI_REG_POWER_LOW);

	sci_reg_set_ext_sc_chip_if(IF_MOD_TDA8004);
	sci_reg_set_delay(RST_DUR_49_600_PERIOS, CLK_DIV_32);
	set_baudrate(SCI_FS, SCI_DI, dev->clock_supplied_khz);

	sci_reg_set_max_repetition(0x03);

	sci_reg_set_mode(SCI_REG_BYTE_MODE);

	sci_reg_set_flow_control(3, SCI_REG_DISABLE, SCI_REG_ENABLE);

	dev->phase = SCI_PHASE_COLD_RESET;
}

static u32 get_bwi(struct sci_dev *dev, u32 bwt)
{
	u32 bwi;
	u32 f = dev->clock_supplied_khz;

	bwi = (f * bwt - (11 * dev->Fi / dev->Di)) / (SCI_FS * 960);
	bwi = ilog2(roundup_pow_of_two(bwi));
	if (bwi > 9) {
		log_warning("BWI is invalid(%d)", bwi);
		bwi = 9;
	}

	return bwi;
}

static int xfer_block(struct sci_dev *dev)
{
	int rc, len;
	u8 intr_mask;
	unsigned long flags;
	struct block_frame *tb = &dev->tx_block;
	struct block_frame *rb = &dev->rx_block;
	ktime_t tick;
	u32 timeout;

	b_log("xfr block - NAD:%d PCB:%02X LEN:%d", tb->nad, tb->pcb, tb->len);
	if (tb->len > 2) {
		b_log("CLA:0x%x INS:0x%x", tb->inf[0], tb->inf[1]);
	}
	/* Rx, Tx Fifo Clear */
	sci_reg_command(CMD_CLR_FT | CMD_CLR_FR);

	/* Initialyze RxBlock */
	rb->idx = 0;
	rb->len = 0;

	dev->xfer_error = XFER_ERR_NONE;

	if (dev->wtx_bwt) {
		u32 bwi;

		timeout = dev->wtx_bwt;
		bwi = get_bwi(dev, dev->wtx_bwt);
		sci_reg_set_timeout((u8)bwi, dev->cwi);
		log_noti("WTX Protocol(timeout:%dmsec, bwi:%d)", timeout, bwi);
	} else {
		timeout = timeout_eor;
	}

	intr_mask = SCI_IRQ_ERR | SCI_IRQ_CDPWR;
	intr_mask |= (SCI_IRQ_FRNE | SCI_IRQ_FRF);
	intr_mask |= (SCI_IRQ_EOT | SCI_IRQ_EOR);
	intr_mask |= SCI_IRQ_FTE;

	if (tb->len > MAX_TF_DEPTH) {
		len = MAX_TF_DEPTH;
	} else {
		len = tb->len;
	}

	if (!len)
		dev->xfer_state = XFER_STATE_TX_WRITE_DONE;
	else
		dev->xfer_state = XFER_STATE_TX_WRITE;

	tick = ktime_get();

	/* TX on */
	spin_lock_irqsave(&dev->lock, flags);

	sci_reg_set_interrupt(intr_mask);
	sci_reg_set_block_frame_header(tb->nad, tb->pcb, tb->len);
	sci_reg_command(CMD_TX_EN);

	sci_reg_write_data(tb->inf, len);
	tb->idx = len;

	init_xfer_event(dev, SCI_EVENT_RX_DONE);

	spin_unlock_irqrestore(&dev->lock, flags);

	// Wait Event End (wait for Tx and Rx)
	rc = wait_xfer_event(dev, timeout);
	if (rc == -ETIME) {
		log_error("TIMEOUT(%d)", timeout);
		debug_print_status(&dev->debug);
	}
	sci_reg_disable_interrupt(SCI_IRQ_ALL);

	tick = ktime_sub(ktime_get(), tick);
	b_log("xfer block %dms elapsed", (int)ktime_to_ms(tick));

	if (rc < 0) {
		log_error("wait event error(%d)\n", rc);
		return rc;
	}

	if (dev->event_status & SCI_EVENT_CARD_POWER) {
		dev->xfer_error = XFER_ERR_CDPOWER;
		return -EIO;
	}

	if (dev->event_status & SCI_EVENT_TX_ERROR) {
		log_error("TX ERROR\n");
		dev->xfer_error = XFER_ERR_TX;
		return -EIO;
	}

	if (dev->event_status & SCI_EVENT_RX_ERROR) {
		log_error("RX ERROR\n");
		dev->xfer_error = XFER_ERR_RX;
		return -EIO;
	}

	/* rx transmission succeeded here. */
	if (dev->wtx_bwt) {
		dev->wtx_bwt = 0;
		sci_reg_set_timeout(dev->bwi, dev->cwi);
	}
	g_log("rxblock - NAD:%d PCB:%X LEN:%d", rb->nad, rb->pcb, rb->len);

	return 0;
}

static int request_ifs(struct sci_dev *dev)
{
	u8 ifs;
	int rc;

	g_log("REQ IFS - START(ifs:%d)", dev->ifs);

	ifs = SCI_IFSD;

	set_tx_block(dev, 0, IFS_REQUEST, 1, &ifs);

	rc = xfer_block(dev);
	if (rc)
		return rc;

	log_debug("RX nad : %02x, RX pcb : %02x, RX len : %02x\n",
		  dev->rx_block.nad, dev->rx_block.pcb, dev->rx_block.len);

	if (dev->rx_block.pcb != IFS_RESPONSE) {
		// TODO: display prologure data
		log_error("unexpected pcb(0x%x)\n", dev->rx_block.pcb);
		return -EIO;
	}

	if (dev->rx_block.inf[0] != ifs) {
		log_error("Different IFS_RESPONSE(%d) - REQ(%d)\n",
			  dev->rx_block.inf[0], ifs);
		return -EIO;
	}

	dev->ifs = ifs;
	g_log("REQ IFS - DONE");

	return 0;
}

static int activate(struct sci_dev *dev)
{
	struct atr *atr = &dev->atr;
	enum sci_reg_status s = sci_reg_get_card_status();
	int rc;

	if (s == SCI_REG_STATUS_READY || s == SCI_REG_STATUS_FAILED) {
		log_error("status error(%d)", s);
		return -EIO;
	}
	cold_reset(dev);

	dev->deviceNS = 0;
	dev->cardNS = 0;
	dev->ifs = 0;
	//TODO Check: info->deviceNS, cardNS
	memset(atr, 0, sizeof(*atr));

	sci_reg_set_voltage(SCI_REG_VOLTAGE_5V);

	rc = read_atr(dev, atr);
	if (rc < 0) {
		log_noti("atr error");
		return rc;
	}

	rc = decode_atr(atr);
	if (rc) {
		log_error("fail to decode atr");
		goto failed;
	}

	rc = config_interface(dev, atr);
	CHECK_ERROR(rc, goto failed, "failed to config_interface");

	return 0;

 failed:
	deactivate(dev);
	return rc;
}

/* if atr failed than have to set power off */
static void deactivate(struct sci_dev *dev)
{
	log_noti("%s", __func__);

	sci_reg_reset_low(SCI_REG_ENABLE);
	sci_reg_command(CMD_POWER_OFF);	/* it makes card status to DET */

	dev->phase = SCI_PHASE_IDLE;
}

#ifdef USE_ATR_POLLING_MODE
static int poll_atr_data(struct sci_dev *dev, u8 *data, u8 len, int timeout)
{
	int avail;
	unsigned long timeout_jiffies;
	u8 intr_status;
	struct rx_buffer *b = &dev->rx_buffer;

	if ((b->idx + len) > MAX_ATR_LEN) {
		log_error("Over max ATR length\n");
		return -EIO;
	}

	timeout_jiffies = jiffies + msecs_to_jiffies(timeout);
	while (1) {
		avail = b->idx - b->ridx;
		if (avail >= len) {
			memcpy(data, b->data + b->ridx, len);
			b->ridx += len;
			break;
		}

		msleep(2);

		while (avail < len) {
			intr_status = sci_reg_get_interrupt_status();

			if (intr_status & (SCI_IRQ_ERR | SCI_IRQ_CDPWR)) {
				if (intr_status & SCI_IRQ_ERR)
					log_error("err_status=0x%x\n",
						  sci_reg_get_error_status());

				if (intr_status & SCI_IRQ_CDPWR)
					log_error("status changed=0x%x\n",
						  sci_reg_get_status());

				return -EIO;
			} else if (intr_status & SCI_IRQ_FRNE) {
				sci_reg_read_data(b->data + b->idx, 1);
				b->idx++;
				avail++;

				log_atr("READ one bytes, Total=%d\n", b->idx);
			} else {
				/* No data in rxbuffer */
				break;
			}
		}

		if (time_is_before_jiffies(timeout_jiffies))
			return -ETIME;
	}

	return 0;
}
#endif

// unify i, r_block setting
static void set_i_block(struct sci_dev *dev)
{
	dev->tx_block.pcb = I_BLOCK;

	if (dev->cardNS) {
		dev->tx_block.pcb |= I_BLOCK_NS;
	} else {
		dev->tx_block.pcb &= ~I_BLOCK_NS;
	}
}

static void set_r_block(struct sci_dev *dev)
{
	dev->tx_block.pcb = R_BLOCK;

	if (dev->cardNS) {
		dev->tx_block.pcb |= R_BLOCK_NR;
	} else {
		dev->tx_block.pcb &= ~R_BLOCK_NR;
	}
}

// need?
static void set_pcb(struct sci_dev *dev, u8 pcb)
{
	dev->tx_block.pcb = pcb;
	if (dev->cardNS) {
		if (pcb == I_BLOCK) {
			dev->tx_block.pcb |= I_BLOCK_NS;	/* send sequence number */
		} else if (pcb == R_BLOCK) {
			dev->tx_block.pcb |= R_BLOCK_NR;	/* send sequence number */
		}
	}
}

static void copy_req_block(struct sci_dev *dev)
{
	u8 len;

	len = dev->tx_data.data[2];

	dev->tx_block.len = len;
	memcpy(dev->tx_block.inf, &dev->tx_data.data[3], len);
}

static int get_block_type(u8 pcb)
{
	if (!(pcb & 0x80)) {
		return I_BLOCK;
	} else if (!(pcb & 0x40)) {
		return R_BLOCK;
	} else {
		return S_BLOCK;
	}
}

static int start_transmit(struct sci_dev *dev, struct sci_transmit_param *param)
{
	u32 tx_len = param->tx.len;

	if (tx_len > MAX_CMD_APDU_LEN) {
		log_error("not support chaining function");
		return -EINVAL;
	}

	dev->xfer_done = false;

	dev->tx_data.idx = 0;
	dev->tx_data.len = tx_len;
	/* backup user data */
	memcpy(dev->tx_data.data, param->tx.buf, dev->tx_data.len);

	set_pcb(dev, I_BLOCK);
	copy_req_block(dev);

	memset(&dev->rx_data, 0, sizeof(dev->rx_data));

	dev->rx_data.max_len = param->rx.len;
	dev->xfer_state = XFER_STATE_READY;

	if (dev->debug.print_data) {
		sci_debug_print(dev, SCI_DEBUG_PRINT_TX_APDU, dev->tx_data.data,
				dev->tx_data.len);
	}

	return 0;
}

static void stop_transmit(struct sci_dev *dev, struct sci_transmit_param *param)
{
	if (dev->xfer_done) {
		memcpy(param->rx.buf, dev->rx_data.data, dev->rx_data.len);
		param->rx.len = dev->rx_data.len;

		if (dev->debug.print_data) {
			sci_debug_print(dev, SCI_DEBUG_PRINT_RX_APDU,
					dev->rx_data.data, dev->rx_data.len);
		}
	}
	dev->xfer_state = XFER_STATE_IDLE;
}

static int process_i_block(struct sci_dev *dev)
{
	struct block_frame *rb = &dev->rx_block;
	struct rx_data *data = &dev->rx_data;

	if (data->len + rb->len > data->max_len) {
		log_error("rx data length(%d) is over than max(%d)",
			  (data->len + rb->len), data->max_len);
		return -EIO;
	}

	if (GET_I_BLOCK_NS(rb->pcb) == dev->cardNS) {
		/* Success Transmission*/
		if (rb->pcb & 0x1F) {
			u8 pcb = (R_BLOCK | dev->cardNS << 4);
			log_debug("abnormal I block");
			set_tx_block(dev, 0, pcb, 0, NULL);

			return 0;
		}

		log_debug("Correct N(S). Transmit Success!");
		INVERT_NS(dev->cardNS);

		memcpy(data->data + data->len, rb->inf, rb->len);
		data->len += rb->len;

		if (rb->pcb & I_BLOCK_MORE_DATA) {
			log_warning("MORE_DATA bit is set - not supported");
			return -EIO;
		}

		INVERT_NS(dev->deviceNS);
		dev->xfer_done = true;
	} else {
		/* NS is different -> request R block. */
		log_noti("different N(S). check this");
		set_tx_block(dev, 0, (R_BLOCK | dev->cardNS << 4), 0, NULL);
	}

	return 0;
}

static void transmit_wtx(struct sci_dev *dev)
{
	u8 multi;
	u32 f, bwt;

	multi = dev->rx_block.inf[0];
	if (multi == 0) {
		log_warning("INF can't be zero");
		multi = 1;
	}
	set_tx_block(dev, 0, WTX_RESPONSE, 1, &dev->rx_block.inf[0]);

	f = dev->clock_supplied_khz;
	bwt = (((11 * dev->Fi) / dev->Di) + (1 << dev->bwi) * SCI_FS * 960) / f;
	bwt *= multi; /* 7816-3, Rule3 */
	dev->wtx_bwt = bwt;

	log_noti("multi:%d, updated bwt:%d", multi, bwt);
}

static int process_s_block(struct sci_dev *dev)
{
	struct block_frame *rb = &dev->rx_block;

	u8 type = rb->pcb & S_BLOCK_TYPE;

	switch (type) {
	case S_BLOCK_RESYNC:
		if (rb->pcb & S_BLOCK_RESPONSE) {
			if (dev->tx_block.pcb == RESYNC_REQUEST) {
				dev->deviceNS = 0;
				dev->cardNS = 0;

				set_pcb(dev, I_BLOCK);
				copy_req_block(dev);
			} else {
				log_error("Abnormal RESYNC");
			}
		} else if (rb->pcb & RESYNC_REQUEST) {
			// next Tx Data is Request Resynch
			set_tx_block(dev, 0, RESYNC_RESPONSE, 0, NULL);

			dev->cardNS = 0;
		}
		break;
	case S_BLOCK_WTX:
		transmit_wtx(dev);
		break;
	case S_BLOCK_IFS:
		break;
	case S_BLOCK_ABORT:
		break;
	default:
		log_error("unknown block type(0x%x)", type);
		return -EIO;
	}

	return 0;
}

static int process_r_block(struct sci_dev *dev)
{
	struct block_frame *rb = &dev->rx_block;

	if (GET_R_BLOCK_NS(rb->pcb) == dev->deviceNS) {
		if (GET_R_BLOCK_ERROR(rb->pcb) == 0) {
			/* retransmission i block */
			set_i_block(dev);
			copy_req_block(dev);
		} else {
			log_debug("r block error[%x]",
				  GET_R_BLOCK_ERROR(rb->pcb));
#if 0
			set_r_block(dev);
			dev->tx_block.len = 0;
#else
			set_pcb(dev, I_BLOCK);
			copy_req_block(dev);
#endif
		}
	} else {
		set_tx_block(dev, 0, RESYNC_REQUEST, 0, NULL);
		log_warning("N(R) is different");
	}
	return 0;
}

int sci_dev_transfer_apdu(struct sci_dev *dev, struct sci_transmit_param *param)
{
	struct block_frame *tb = &dev->tx_block;
	struct block_frame *rb = &dev->rx_block;
	int i, cnt, rc, timeout_cnt;

#define MAX_TRANSMISSION_TIMES 10

	if (dev->phase != SCI_PHASE_BLOCK_MESSAGE) {
		/* config_interface is not called.
		   it means activate is not performed. */
		log_warning("invalid phase(%s)", get_phase_str(dev->phase));

		sci_ctop_select_smartcard();
		sci_ctop_set_clock();
		msleep(200);

		for (i = 0; i < 3; i++) {
			rc = sci_activate(dev);
			if (rc == 0)
				break;

			msleep(100); /* 100ms */
		}

		if (i != 0) {
			log_noti("#%d tried for activate(%d)", i, rc);
		}
		CHECK_ERROR(rc, return -EIO, "sci_activate Error");
	}

	if (dev->ifs == 0) {
		for (i = 0; i < 3; i++) {
			rc = request_ifs(dev);
			if (!rc)
				break;
		}
		CHECK_ERROR(rc, return -EIO, "request_ifs failed");
	}

	rc = start_transmit(dev, param);
	CHECK_ERROR(rc, return rc, "start_transmit failed");
	cnt = 0;
	timeout_cnt = 0;
	while (1) {
		rc = xfer_block(dev);
		if (rc == 0) {
			if (tb->nad != rb->nad) {
				// next Tx Data is Request Resync
				log_debug("RESYNC_REQUEST, not-equal NAD");
				set_tx_block(dev, 0, RESYNC_REQUEST, 0, NULL);
			} else {
				u8 type = get_block_type(rb->pcb);

				if (type == I_BLOCK) {
					rc = process_i_block(dev);
					if (rc) {
						log_error("error in I blk");
						break;
					}
					if (READ_ONCE(dev->xfer_done)) {
						stop_transmit(dev, param);
						log_debug
						    ("sci transmit done(%d)",
						     cnt);
						return 0;
					}
				} else if (type == R_BLOCK) {
					rc = process_r_block(dev);
					if (rc) {
						log_error("error in R blk");
						break;
					}
				} else {
					rc = process_s_block(dev);
					if (rc) {
						log_error("error in S blk");
						break;
					}
				}
			}
		} else if (rc == -ERESTARTSYS) {
			log_noti("interrupted by a signal\n");
			break;
		} else if (rc == -ETIME) {
			if (timeout_cnt < 3) {
				set_pcb(dev, R_BLOCK);
				dev->tx_block.len = 0;
			} else {
				set_tx_block(dev, 0, RESYNC_REQUEST, 0, NULL);
			}
			timeout_cnt++;
		} else {
			if (dev->xfer_error == XFER_ERR_CDPOWER) {
				break;
			} else if (dev->xfer_error == XFER_ERR_TX) {
				msleep(5);
				r_log("Retransmit again");
			} else if (dev->xfer_error == XFER_ERR_RX) {
				msleep(5);
				r_log("send R-block");
				set_r_block(dev);
			}
		}
		cnt++;
		if (cnt > MAX_TRANSMISSION_TIMES) {
			rc = -ETIME;
			break;
		}
	}

	stop_transmit(dev, param);

	log_noti("sci transmit fail(%d/%d)", cnt, timeout_cnt);

	return rc;
}

void sci_deactivate(struct sci_dev *dev)
{
	log_noti("%s(%s)", __func__, get_phase_str(dev->phase));

	if (dev->phase != SCI_PHASE_IDLE) {
		deactivate(dev);
	}
}

int sci_get_reset_time(struct sci_dev *dev, s64 *param)
{
	struct atr *atr = &dev->atr;

	if (atr->historical_bytes) {
		if (atr->historical[0] != 0x90) {
			log_warning("T1 is not 0x90 (0x%02x)",
				    atr->historical[0]);
		}
		*param = atr->historical[1];
	} else {
		*param = 0;
	}
	log_noti("%s - %lld", __func__, *param);

	return 0;
}

