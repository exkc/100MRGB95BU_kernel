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
*  driver register implementation for sci device.
*	sci device will teach you how to make device driver with new platform.
*
*  author		yeonju.lee (yeonju.lee@lge.com)
*  version		1.0
*  date		2019.04.18
*  note		Additional information.
*
*/

#include <linux/slab.h>		/* kfree, kzalloc */

#include "sci_impl.h"
#include "sci_reg.h"

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (g_sci_reg_log_mask) {					\
		log_noti("@SCI_REG: %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (g_sci_reg_log_mask) {					\
		log_noti("~SCI_REG: %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define __reg_write(base, offset, value) \
__raw_writel(value, ((void __iomem *)(uintptr_t)(base) + (offset)))

#define __reg_read(base, offset) \
__raw_readl((void __iomem *)((uintptr_t)(base) + (offset)))

struct sci_reg_ctrl g_sci_reg_ctrl;
static u32 g_sci_reg_log_mask;

static DEFINE_SPINLOCK(sci_reg_lock);

void sci_reg_cleanup(void)
{
	log_noti("%s", __func__);
	iounmap(g_sci_reg_ctrl.phys.addr);
	kfree(g_sci_reg_ctrl.shdw.addr);
}

int sci_reg_init(void)
{
	u32 base, size;
	struct sci_cfg *cfg;

	cfg = sci_get_config();
	CHECK_ERROR(!cfg, return -EIO, "cfg init is not");

	base = cfg->reg_base_addr;
	size = sizeof(SCI_REG_T);

	g_sci_reg_ctrl.phys.addr = ioremap(base, size);
	CHECK_ERROR(!g_sci_reg_ctrl.phys.addr, return -ENOMEM, "ioremap fail");

	/* Init Shadow SCI Register access */
	g_sci_reg_ctrl.shdw.addr = kzalloc(sizeof(SCI_REG_T), GFP_KERNEL);
	if (!g_sci_reg_ctrl.shdw.addr) {
		log_error("no mem\n");
		iounmap(g_sci_reg_ctrl.phys.addr);
		g_sci_reg_ctrl.phys.addr = NULL;
		return -ENOMEM;
	}

	return 0;
}

void sci_reg_set_default_value(void)
{
	SCI_RdFL(sci_intr_stat);

	SCI_Wr(sci_fc, 0x01);
	SCI_Wr(sci_ext, 0x03);
	SCI_Wr(sci_dds, 0x00);
	SCI_Wr(sci_set, 0x00);
	SCI_Wr(sci_conf, 0xFF);
	SCI_Wr(sci_mode, 0x00);
	SCI_Wr(sci_di, 0x01);
	SCI_Wr(sci_tos, 0x4D);
	SCI_Wr(sci_br, 0x25);
	SCI_Wr(sci_ft, 0x02);
	SCI_Wr(sci_intr_mask, 0x3F);
	SCI_Wr(sci_agt, 0x00);
	SCI_Wr(sci_wi, 0x0a);
#if 0
	SCI_Wr(sci_dly, 0x03);
#else
	/* 20131210 jinhwan.bae to support New BCAS card type A, ACK after RST is about 6.75ms
	   make HW IP wait time is 49600*2 ticks / 6.25M = 15.8ms
	   before , 40000*2 ticks / 6.25M = 12.8 ms
	   IP raise ATR-timeout after that, regardless of Driver Wait time */
	SCI_Wr(sci_dly, 0x1F);
#endif
	SCI_Wr(sci_pol_crc_l, 0x0A);
	SCI_Wr(sci_pol_crc_h, 0x0A);
	SCI_Wr(sci_rf_depth, 0x3F);
	SCI_Wr(sci_tf_depth, 0x1F);

	SCI_WrFL(sci_fc);
	SCI_WrFL(sci_ext);
	SCI_WrFL(sci_dds);
	SCI_WrFL(sci_set);
	SCI_WrFL(sci_conf);
	SCI_WrFL(sci_mode);
	SCI_WrFL(sci_di);
	SCI_WrFL(sci_tos);
	SCI_WrFL(sci_br);
	SCI_WrFL(sci_ft);
	SCI_WrFL(sci_intr_mask);
	SCI_WrFL(sci_agt);
	SCI_WrFL(sci_wi);
	SCI_WrFL(sci_dly);
	SCI_WrFL(sci_pol_crc_l);
	SCI_WrFL(sci_pol_crc_h);
	SCI_WrFL(sci_rf_depth);
	SCI_WrFL(sci_tf_depth);
}

struct sci_reg {
	const char *name;
	u16 offset;
};

static struct sci_reg list[] = {
	{"DATA", 0x00}, {"NAD", 0x04}, {"PCB", 0x08}, {"LEN", 0x0c},
	{"EDC1", 0x10}, {"EDC2", 0x14}, {"ERR", 0x18}, {"STAT", 0x1c},
	{"INTR_STAT", 0x20}, {"CMD", 0x24}, {"FC", 0x28}, {"EXT", 0x2c},
	{"RSVD", 0x30}, {"RSVD", 0x34}, {"RSVD", 0x38}, {"RSVD", 0x3c},
	{"DDS", 0x40}, {"SET", 0x44}, {"CONF", 0x48}, {"MODE", 0x4c},
	{"DI", 0x50}, {"TOS", 0x54}, {"BR", 0x58}, {"FT", 0x5c},
	{"INTR_MASK", 0x60}, {"AGT", 0x64}, {"WI", 0x68}, {"DLY", 0x6c},
	{"POL_CRC_L", 0x70}, {"POL_CRC_H", 0x74}, {"RF_DEPTH", 0x78},
	{"TF_DEPTH", 0x7c},
};

void sci_reg_dump(printf_func_t prfn, void *arg)
{
	u32 size = sizeof(SCI_REG_T);

	uintptr_t base;
	u32 offset, value;

	base = (uintptr_t)SCI_REG_SHDW;

	SCI_RdFL(sci_stat);
	SCI_RdFL(sci_err);
	SCI_RdFL(sci_intr_stat);

	for (offset = 0; offset < size; offset += 4) {
		value = __reg_read(base, offset);

		if ((offset % 16) == 0) {
			if (offset == 0)
				prfn(arg, "%04x : ", offset);
			else
				prfn(arg, "\n%04x : ", offset);
		}
		prfn(arg, "%08x ", value);
	}
	prfn(arg, "\n");
}

void sci_reg_write(u32 offset, u32 value)
{
	uintptr_t base;
	int i, found;
	struct sci_reg *l = list;

	if (offset & 0x3) {
		log_error("not alligned offset");
		return;
	}

	found = 0;
	for (i = 0; i < ARRAY_SIZE(list); i++) {
		if (offset == l[i].offset) {

			base = (uintptr_t)SCI_REG_SHDW;

			log_noti("%s(%04x) : %08x->%08x",
				 l[i].name, l[i].offset,
				 __reg_read(base, offset), value);

			found = 1;
			break;
		}
	}
	if (!found) {
		log_noti("not matched offset");
		return;
	}

	__reg_write(SCI_REG_SHDW, offset, value);
	__reg_write(SCI_REG_PHYS, offset, value);

}

void sci_reg_read_data(u8 *data, u8 len)
{
	int i;

	for (i = 0; i < len; i++)
		data[i] = SCI_REG_READ32(sci_data);
}

void sci_reg_write_data(u8 *data, u8 len)
{
	int i;

	for (i = 0; i < len; i++)
		SCI_REG_WRITE32(sci_data, data[i]);
}

void sci_reg_set_block_frame_header(u8 nad, u8 pcb, u8 len)
{
	TRACE_ENTER("nad:0x%x, pcb:0x%x, len:0x%x", nad, pcb, len);

	SCI_Wr(sci_nad, nad);
	SCI_Wr(sci_pcb, pcb);
	SCI_Wr(sci_len, len);

	SCI_WrFL(sci_nad);
	SCI_WrFL(sci_pcb);
	SCI_WrFL(sci_len);
}

void sci_reg_get_block_frame_header(u8 *nad, u8 *pcb, u8 *len)
{
	*nad = SCI_REG_READ32(sci_nad);
	*pcb = SCI_REG_READ32(sci_pcb);
	*len = SCI_REG_READ32(sci_len);
}

u8 sci_reg_get_error_status(void)
{
	u8 v;

	v = SCI_REG_READ32(sci_err);

	return v;
}

u8 sci_reg_get_status(void)
{
	u8 v;
	unsigned long flag;

	spin_lock_irqsave(&sci_reg_lock, flag);
	v = SCI_REG_READ32(sci_stat);
	spin_unlock_irqrestore(&sci_reg_lock, flag);

	return v;
}

u8 sci_reg_get_card_status(void)
{
	u8 v;
	unsigned long flag;

	spin_lock_irqsave(&sci_reg_lock, flag);
	SCI_RdFL(sci_stat);
	SCI_Rd01(sci_stat, card, v);
	spin_unlock_irqrestore(&sci_reg_lock, flag);

	return v;
}

/* Prologue field of block frame */
void sci_reg_command(u8 cmd)
{
	TRACE_ENTER("cmd:0x%x", cmd);

	SCI_Wr(sci_cmd, cmd);
	SCI_WrFL(sci_cmd);
}

void sci_reg_set_flow_control(u8 parity, u8 rx, u8 tx)
{
	TRACE_ENTER("parity:0x%x, rx:0x%x, tx:0x%x", parity, rx, tx);

	SCI_Wr01(sci_fc, par_retry, parity);
	SCI_Wr01(sci_fc, r_fc_en, rx);
	SCI_Wr01(sci_fc, t_fc_en, tx);
	SCI_WrFL(sci_fc);
}

void sci_reg_set_ext_sc_chip_if(u8 flag)
{
	TRACE_ENTER("flag:0x%x", flag);

	SCI_Wr01(sci_ext, if_mod, flag);
	SCI_WrFL(sci_ext);
}

void sci_reg_reset_low(u8 flag)
{
	TRACE_ENTER("flag:0x%x", flag);

	SCI_Wr01(sci_dds, reset_low, flag);
	SCI_WrFL(sci_dds);
}

void sci_reg_power_mon(enum sci_reg_pwr pwr)
{
	TRACE_ENTER("pwr:0x%x", pwr);

	SCI_Wr01(sci_dds, p_mon_hi, pwr);
	SCI_WrFL(sci_dds);
}

/* BGT = Block Guard Time */
void sci_reg_set_bgt_delay(u8 delay)
{
	TRACE_ENTER("delay:0x%x", delay);

	SCI_Wr01(sci_set, bgt_dly, delay);
	SCI_WrFL(sci_set);
}

void sci_reg_set_parity(enum sci_reg_parity parity)
{
	TRACE_ENTER("parity:0x%x", parity);

	SCI_Wr01(sci_set, poe, parity);
	SCI_WrFL(sci_set);
}

void sci_reg_set_voltage(enum sci_reg_voltage vol)
{
	TRACE_ENTER("voltage:0x%x", vol);

	SCI_Wr01(sci_set, vcc_sel, vol);
	SCI_WrFL(sci_set);
}

enum sci_reg_voltage sci_reg_get_voltage(void)
{
	u8 val;

	SCI_Rd01(sci_set, vcc_sel, val);

	return val;
}

void sci_reg_set_mode(u8 flag)
{
	TRACE_ENTER("mode:0x%x", flag);

	SCI_Wr01(sci_mode, t, flag);
	SCI_WrFL(sci_mode);
}

/* EDC = Error Detection Code */
void sci_reg_set_edc(u8 value)
{
	TRACE_ENTER("value:0x%x", value);

	SCI_Wr01(sci_mode, edc, value);
	SCI_WrFL(sci_mode);
}

void sci_reg_set_max_repetition(u8 max)
{
	TRACE_ENTER("max:0x%x", max);

	SCI_Wr01(sci_mode, max_rpt, max);
	SCI_WrFL(sci_mode);
}

void sci_reg_set_conversion(u8 value)
{
	TRACE_ENTER("conversion:0x%x", value);

	SCI_Wr01(sci_mode, conv, value);
	SCI_WrFL(sci_mode);
}

void sci_reg_set_endian(enum sci_reg_endian endian)
{
	TRACE_ENTER("endian:0x%x", endian);

	SCI_Wr01(sci_mode, lbe, endian);
	SCI_WrFL(sci_mode);
}

void sci_reg_set_rx_change(bool en)
{
	TRACE_ENTER("change:0x%x", en);

	en = (en == 0 ? 0 : 1);

	SCI_Wr01(sci_mode, tx_to_rx, en);
	SCI_WrFL(sci_mode);
}

void sci_reg_set_di(u8 value)
{
	TRACE_ENTER("di:0x%x", value);

	SCI_Wr01(sci_di, di, value);
	SCI_WrFL(sci_di);
}

void sci_reg_set_timeout(u8 bwi, u8 cwi)
{
	TRACE_ENTER("bwi:0x%x, cwi:0x%x", bwi, cwi);

	SCI_Wr01(sci_tos, bwi, bwi);
	SCI_Wr01(sci_tos, cwi, cwi);
	SCI_WrFL(sci_tos);
}

void sci_reg_set_baud(u8 bv, u8 fv)
{
	TRACE_ENTER("bv:0x%x, fv:0x%x", bv, fv);

	SCI_Wr01(sci_br, br, bv);
	SCI_WrFL(sci_br);

	SCI_Wr01(sci_ft, ft, fv);
	SCI_WrFL(sci_ft);
}

void sci_reg_enable_interrupt(u8 mask)
{
	u8 dis;

	TRACE_ENTER("mask:0x%x", mask);

	dis = SCI_Rd(sci_intr_mask);
	dis &= ~mask;

	SCI_Wr(sci_intr_mask, dis);
	SCI_WrFL(sci_intr_mask);
}

void sci_reg_disable_interrupt(u8 mask)
{
	u8 dis;

	TRACE_ENTER("mask:0x%x", mask);

	dis = SCI_Rd(sci_intr_mask);
	dis |= mask;

	SCI_Wr(sci_intr_mask, dis);
	SCI_WrFL(sci_intr_mask);
}

u8 sci_reg_get_interrupt_status(void)
{
	u8 v;

	v = SCI_REG_READ32(sci_intr_stat);

	return v;
}

void sci_reg_set_interrupt(u8 mask)
{
	u8 dis = ~mask;

	TRACE_ENTER("mask:0x%x", mask);

	SCI_Wr(sci_intr_mask, dis);
	SCI_WrFL(sci_intr_mask);
}

u8 sci_reg_get_interrupt_mask(void)
{
	u8 mask;

	mask = SCI_Rd(sci_intr_mask);

	return mask;
}

void sci_reg_set_agt(u8 guard_time)
{
	TRACE_ENTER("guard_time:0x%x", guard_time);

	SCI_Wr01(sci_agt, agt, guard_time);
	SCI_WrFL(sci_agt);
}

u8 sci_reg_get_clkdiv(void)
{
	u8 clkdiv;

	SCI_Rd01(sci_dly, clk_div, clkdiv);

	return clkdiv;
}

void sci_reg_set_delay(u8 duration, u8 div)
{
	TRACE_ENTER("dur:0x%x, div:0x%x", duration, div);

	SCI_Wr(sci_dly, 0);
	SCI_Wr01(sci_dly, rst_dur, duration);
	SCI_Wr01(sci_dly, clk_div, div);
	SCI_WrFL(sci_dly);
}

void sci_reg_set_rxfifo_depth(u8 depth)
{
	TRACE_ENTER("depth:0x%x", depth);

	SCI_Wr01(sci_rf_depth, rf_depth, depth);
	SCI_WrFL(sci_rf_depth);
}

void sci_reg_set_txfifo_depth(u8 depth)
{
	TRACE_ENTER("depth:0x%x", depth);

	SCI_Wr01(sci_tf_depth, tf_depth, depth);
	SCI_WrFL(sci_tf_depth);
}

u32 sci_reg_get_log_mask(void)
{
	return g_sci_reg_log_mask;
}

void sci_reg_set_log_mask(int en)
{
	g_sci_reg_log_mask = (en == 0 ? 0 : 1);
}
