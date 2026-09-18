/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *  ION0 IO CTOP(RX) Register Access for O26
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-17
 *  @note	Additional information.
 */

#ifdef INCLUDE_O26_CHIP_KDRV

#include <linux/types.h>
#include "te_impl.h"
#include "sys_regs.h"
#include "ion_reg_o26.h"

#include "o26/ucom/ucom_o26_common.h"

static int ion_trace = 0;

module_param_named(ion_io_ctop_trace, ion_trace, int, 0644);
MODULE_PARM_DESC(ion_io_ctop_trace, "enable verbose debug messages");

#define TRACE_ENTER(fmt, args...)                                           \
	do                                                                  \
	{                                                                   \
		if (unlikely(ion_trace))                                    \
		{                                                           \
			log_noti("@CTOP_REG : %s(" fmt ")", __F__, ##args); \
		}                                                           \
	} while (0)

#define TRACE_EXIT(fmt, args...)                                            \
	do                                                                  \
	{                                                                   \
		if (unlikely(ion_trace))                                    \
		{                                                           \
			log_noti("~CTOP_REG : %s(" fmt ")", __F__, ##args); \
		}                                                           \
	} while (0)

static DEFINE_SPINLOCK(ctop_reg_lock);

int O26_ION_IO_Set_ClockGate(u8 idx, u8 v)
{
	unsigned long flag;

	if (unlikely(idx > 1)) {
		log_error("invalid idx %u", idx);
		return -EINVAL;
	} else if (unlikely(v > 1)) {
		log_error("invalid v %u", v);
		return -EINVAL;
	}

	TRACE_ENTER("");

	//FIXME: gate variables are uncleared
	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(CPU_SCRG_CTRL_ION0, crg_ion0002);
	if (idx == 0) {
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0002,
				     reg_srds_12to3_sd_rx0_clk_gate_en, v);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0002,
				     reg_srds_12to3_tp_rx0_clk_gate_en, v);
	} else {
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0002,
				     reg_srds_12to3_sd_rx1_clk_gate_en, v);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0002,
				     reg_srds_12to3_tp_rx1_clk_gate_en, v);
	}
	CTOP_CTRL_O26Ax_WrFL(CPU_SCRG_CTRL_ION0, crg_ion0002);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Reset(u8 idx)
{
	unsigned long flag;

	if (unlikely(idx > 1)) {
		log_error("invalid idx %u", idx);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	// reset assert & deassert
	if (idx == 0) {
		CTOP_CTRL_O26Ax_RdFL(CPU_SCRG_CTRL_ION0, crg_ion0003);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_sd_rx0_n, 1);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_tp_rx0_n, 1);
		CTOP_CTRL_O26Ax_WrFL(CPU_SCRG_CTRL_ION0, crg_ion0003);

		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_sd_rx0_n, 0);
   		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_tp_rx0_n, 0);
   		CTOP_CTRL_O26Ax_WrFL(CPU_SCRG_CTRL_ION0, crg_ion0003);
	} else {
		CTOP_CTRL_O26Ax_RdFL(CPU_SCRG_CTRL_ION0, crg_ion0003);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_sd_rx1_n, 1);
		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_tp_rx1_n, 1);
		CTOP_CTRL_O26Ax_WrFL(CPU_SCRG_CTRL_ION0, crg_ion0003);

		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_sd_rx1_n, 0);
   		CTOP_CTRL_O26Ax_Wr01(CPU_SCRG_CTRL_ION0, crg_ion0003,
				     reg_soft_rst_srds_12to3_tp_rx1_n, 0);
   		CTOP_CTRL_O26Ax_WrFL(CPU_SCRG_CTRL_ION0, crg_ion0003);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Set_mux(u8 tpi_num)
{
	unsigned long flag;

	if (unlikely(tpi_num > 1)) {
		log_error("invalid tpi %u", tpi_num);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION0_SRDS12TO3, mux);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_sipo1_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_sipo0_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_piso0_sd_out, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_piso1_sd_out, 0);

	if (tpi_num == 0) {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_sipo0_tp_out,
				     1);
	} else {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_sipo1_tp_out,
				     1);
	}

	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_piso1_tp_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, mux, reg_sel_piso0_tp_in, 0);
	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, mux);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Set_ptg_cfg(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_chk1_mode, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_chk1_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_chk0_mode, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_chk0_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_ptg1_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, reg_ptg0_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, result_valid1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_cfg, result_valid0, 0);
	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, ptg_cfg);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Set_ptg_pkt0(u8 tpi_num)
{
	unsigned long flag;

	if (unlikely(tpi_num > 1)) {
		log_error("invalid tpi %u", tpi_num);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION0_SRDS12TO3, ptg_pkt0);
	if (tpi_num == 0) {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_pkt0,
				     reg_tp_pkt_size_ext0, ION_TP_PKT_SIZE);
	} else {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, ptg_pkt0,
				     reg_tp_pkt_size_ext1, ION_TP_PKT_SIZE);
	}
	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, ptg_pkt0);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Set_align_cfg0(u8 tpi_num, u8 is_serial, u8 check_sop)
{
	unsigned long flag;

	if (unlikely(tpi_num > 1)) {
		log_error("invalid tpi %u", tpi_num);
		return -EINVAL;
	} else if (unlikely(is_serial > 1)) {
		log_error("invalid is_serial %u", is_serial);
		return -EINVAL;
	} else if (unlikely(check_sop > 1)) {
		log_error("invalid check_sop %u", check_sop);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION0_SRDS12TO3, align_cfg0);

	if (tpi_num == 0) {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_idle_init_time0, ION_TP_PKT_SIZE);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_idle_init_en0, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_delete_sop0, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_invert_valid0, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_fifo0_bypass, 1);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_piso0_gate_en, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_check_sop0,
				     check_sop);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_mode_sipo0,
				     is_serial);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_mode_piso0,
				     is_serial);
	} else {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_idle_init_time1, ION_TP_PKT_SIZE);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_idle_init_en1, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_delete_sop1, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_invert_valid1, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_fifo1_bypass, 1);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0,
				     reg_piso1_gate_en, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_check_sop1,
				     check_sop);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_mode_sipo1,
				     is_serial);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, align_cfg0, reg_mode_piso1,
				     is_serial);
	}

	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, align_cfg0);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

//NOTE: tlv_en may be changed due to supporting the lgc mode
int O26_ION_IO_Set_start_code(u8 tpi_num, u8 tlv_en, u8 code)
{
	unsigned long flag;

	if (unlikely(tpi_num > 1)) {
		log_error("invalid tpi %u", tpi_num);
		return -EINVAL;
	} else if (unlikely(tlv_en > 1)) {
		log_error("invalid tlv_en %u", tlv_en);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION0_SRDS12TO3, start_code);
	CTOP_CTRL_O26Ax_RdFL(ION0_SRDS12TO3, st_code23_en);

	if (tpi_num == 0) {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, start_code,
				     reg_start_code0_ext0, code);

		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_tlv_en_ext0, tlv_en);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_st_code2_en_ext0, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_st_code3_en_ext0, 0);

	} else {
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, start_code,
				     reg_start_code0_ext1, code);

		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_tlv_en_ext1, tlv_en);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_st_code2_en_ext1, 0);
		CTOP_CTRL_O26Ax_Wr01(ION0_SRDS12TO3, st_code23_en,
				     reg_st_code3_en_ext1, 0);
	}

	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, start_code);
	CTOP_CTRL_O26Ax_WrFL(ION0_SRDS12TO3, st_code23_en);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_IO_Set_tpi_mux(u8 tpi_num, u8 val)
{
	unsigned long flag;

	if (unlikely(tpi_num > 1)) {
		log_error("invalid tpi %u", tpi_num);
		return -EINVAL;
	} else if (unlikely(val > 4)) {
		log_error("invalid mux sel %u", val);
		return -EINVAL;
	}

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	if (tpi_num == 0) {
		CTOP_CTRL_O26Ax_RdFL(ION0_IOMUX_CORE, pad_ion0_core66);
		CTOP_CTRL_O26Ax_RdFL(ION0_IOMUX_CORE, pad_ion0_core67);
		CTOP_CTRL_O26Ax_RdFL(ION0_IOMUX_CORE, pad_ion0_core68);

		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_data0_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data1_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data2_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data3_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data4_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data5_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data6_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_data7_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core67,
				     reg_pad_tpi_clk_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core68,
				     reg_pad_tpi_val_ext1_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core68,
				     reg_pad_tpi_sop_ext1_mux_sel, val);

		CTOP_CTRL_O26Ax_WrFL(ION0_IOMUX_CORE, pad_ion0_core66);
		CTOP_CTRL_O26Ax_WrFL(ION0_IOMUX_CORE, pad_ion0_core67);
		CTOP_CTRL_O26Ax_WrFL(ION0_IOMUX_CORE, pad_ion0_core68);
	} else { // tpi_num == 1
		CTOP_CTRL_O26Ax_RdFL(ION0_IOMUX_CORE, pad_ion0_core65);
		CTOP_CTRL_O26Ax_RdFL(ION0_IOMUX_CORE, pad_ion0_core66);

		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core65,
				     reg_pad_tpi_data0_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core65,
				     reg_pad_tpi_data1_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core65,
				     reg_pad_tpi_data2_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core65,
				     reg_pad_tpi_data3_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_data4_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_data5_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_data6_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_data7_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_clk_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_val_ext2_mux_sel, val);
		CTOP_CTRL_O26Ax_Wr01(ION0_IOMUX_CORE, pad_ion0_core66,
				     reg_pad_tpi_sop_ext2_mux_sel, val);

		CTOP_CTRL_O26Ax_WrFL(ION0_IOMUX_CORE, pad_ion0_core65);
		CTOP_CTRL_O26Ax_WrFL(ION0_IOMUX_CORE, pad_ion0_core66);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

u32 O26_ION_IO_reg_read(u32 addr)
{
	return o26_ucom_spi_read32(addr);
}
int O26_ION_IO_reg_write(u32 addr, u32 val)
{
	return o26_ucom_spi_write32(addr, val);
}

#endif // INCLUDE_O26_CHIP_KDRV
