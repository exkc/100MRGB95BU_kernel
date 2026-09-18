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
 *  ION1 CI CTOP(RX) Register Access for O26
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-17
 *  @note	Additional information.
 */

#ifdef INCLUDE_O26_CHIP_KDRV
#include "te_impl.h"
#include "sys_regs.h"
#include "ion_reg_o26.h"

static int ion_trace = 0;

module_param_named(ion_ci_ctop_trace, ion_trace, int, 0644);
MODULE_PARM_DESC(ion_ci_ctop_trace, "enable verbose debug messages");

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

int O26_ION_CI_REG_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	// 0x00000000, 0xCC600014
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_LNX2, crg_main_lnx2005,
		reg_sel_fb_clk_src, 0);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_LNX2, crg_main_lnx2005);

	// 0x11111111, 0xC4672100
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_data3_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_data4_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_data7_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_data6_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_val_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_data1_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_tpo_clk_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core64,
			     reg_pad_ci_intr_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_CORE, pad_ion1_core64);

	// 0x11111111, 0xC4672104
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpi_data5_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpi_clk_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpi_data7_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpi_data2_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpo_data5_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpo_sop_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpo_data2_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core65,
			     reg_pad_tpo_data0_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_CORE, pad_ion1_core65);

	// 0x11111111, 0xC4672108
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_ion1_gpio00_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_val_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_data6_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_data4_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_sop_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_data1_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_data3_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core66,
			     reg_pad_tpi_data0_cam_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_CORE, pad_ion1_core66);

	// 0x00111111, 0xC467210C
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio06_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio05_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio04_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio03_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio02_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_CORE, pad_ion1_core67,
			     reg_pad_ion1_gpio01_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_CORE, pad_ion1_core67);

	// 0x11111111, 0xC4671100
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_sd04_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_sd03_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_sd02_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_sd01_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_sd00_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_pores_n_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_ci_io_clk_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad64,
			     reg_pad_cicam_clk_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_PAD, pad_ion1_pad64);

	// 0x01111211, 0xC4671104
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_spi_do_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_spi_di_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_spi_cs_mux_sel, 2);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_spi_clk_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_sd07_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_sd06_mux_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_IOMUX_PAD, pad_ion1_pad65,
			     reg_pad_ci_io_sd05_mux_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_IOMUX_PAD, pad_ion1_pad65);

	// 0x00000001, 0xCC600014
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_LNX2, crg_main_lnx2005,
			     reg_sel_fb_clk_src, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_LNX2, crg_main_lnx2005);

	// 0x00100002, 0xC4680010
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion1_cicam_clk_sel, 2);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_sd_12to3_rx1_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_sd_12to3_tx0_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_sd_32to1_rx_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_sd_32to1_tx_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_tp_12to3_rx1_clk_sel, 1);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_ion_tp_12to3_tx0_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1004,
			     reg_skew_ff_sd0_clk_sel, 0);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1004);

	// 0x00111100, 0xC4676004
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo1_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo0_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso1_sd_out, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso0_sd_out, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo1_tp_out, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo0_tp_out, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso1_tp_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso0_tp_in, 0);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, mux);

	// 0x00000000, 0xC4676014
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_mode, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk0_mode, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk0_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_ptg1_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_ptg0_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, result_valid1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, result_valid0, 0);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, ptg_cfg);

	// 0x000000bb, 0xC4676018
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_pkt0, reg_tp_pkt_size_ext0,
			     ION_TP_PKT_SIZE); // 188 Bytes
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, ptg_pkt0);

	// 0x04002828, 0xC4676008
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_idle_init_time1,
			     0x28);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_idle_init_time0,
			     0x28);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_idle_init_en1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_idle_init_en0, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_check_sop1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_check_sop0, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_delete_sop1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_delete_sop0, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_invert_valid1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_invert_valid0, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_fifo1_bypass, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_fifo0_bypass, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_piso1_gate_en, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_piso0_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo0, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso1, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso0, 0);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, align_cfg0);

	// 0x00000000, 0xC4680008
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_apb_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_ion1_cicam_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_ion1_main_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd0_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd1_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd2_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd3_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd4_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd5_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd6_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_skew_ff_sd7_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_12to3_sd_rx1_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_12to3_sd_tx0_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_12to3_tp_rx1_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_12to3_tp_tx0_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_32to1_sd_rx_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1002,
			     reg_srds_32to1_sd_tx_clk_gate_en, 0);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1002);

	// 0x00000000, 0xC468000C
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_apb_clk_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_ion1_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd0_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd1_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd2_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd3_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd4_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd5_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd6_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_skew_ff_sd7_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_12to3_sd_rx1_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_12to3_sd_tx0_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_12to3_tp_rx1_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_12to3_tp_tx0_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_32to1_sd_rx_n, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003,
			     reg_soft_rst_srds_32to1_sd_tx_n, 0);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1003);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

/* Pro:Idiom API */
int O26_ION_CI_Set_tpo_mode(u8 is_serial)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, align_cfg0);

	if (is_serial) {
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo1,
				     1);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo0,
				     0);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso1,
				     0);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso0,
				     1);
	} else { // parallel
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo1,
				     0);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_sipo0,
				     0);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso1,
				     0);
		CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_mode_piso0,
				     0);
	}

	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, align_cfg0);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_CI_Reset(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_ION1, crg_ion1003);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003, reg_soft_rst_ion1_n,
			     1);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1003);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	// 2ms sleep before de-assert
	usleep_range(2 * 1000, 2 * 1000);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_ION1, crg_ion1003);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1003, reg_soft_rst_ion1_n,
			     0);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1003);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_CI_Reset_TP(bool assert)
{
	unsigned long flag;
	u8 v = (assert) ? 1 : 0;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, swrst);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_sipo1_sd, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_sipo1_tp, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_sipo0_sd, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_sipo0_tp, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_piso1_sd, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_piso1_tp, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_piso0_sd, v);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, swrst, reg_swrst_piso0_tp, v);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, swrst);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

//TODO: consider channel
int O26_ION_CI_Init_TP_Checker(u16 pkt_cnt)
{
	unsigned long flag;
	u32 timeout; // 20Mhz tick

	if (!pkt_cnt)
		return -EINVAL;

	// 4000 tick = 0.2 ms for 1 packet
	timeout = pkt_cnt * 4000;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	//0xc4676008: 0x0c0c2828 #check sop
	// omit the values which is already set in hw_init
	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, align_cfg0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_check_sop1, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_check_sop0, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_piso1_gate_en, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, align_cfg0, reg_piso0_gate_en, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, align_cfg0);

	//#SIPO0/1 crg
	//0xc4680010: 0x00100002 (same with init)
	//0xc4680014: 0x00000000
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd1_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd2_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd3_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd4_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd5_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd6_clk_sel, 0);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_ION1, crg_ion1005,
			     reg_skew_ff_sd7_clk_sel, 0);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_ION1, crg_ion1005);

	//#check cnt & timer
	// 80 / 4 = 20 Mhz tick: 4000(0.1ms) * pkt_cnt
	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, ptg_pkt1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_pkt1, reg_tp_pkt_num, pkt_cnt);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, ptg_pkt1);

	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, chk_tm1, reg_chk1_timer, timeout);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, chk_tm1);

	//#checker reset
	//0xc4676014: 0x00000000 (same with init)

	//#SIPO0/1 path set
	//0xc4676004: 0x10021000
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo1_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo0_sd_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso1_sd_out, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso0_sd_out, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo1_tp_out, 2);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_sipo0_tp_out, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso1_tp_in, 0);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, mux, reg_sel_piso0_tp_in, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, mux);

#if 0
	//#SIPO1 checker enable
	//0xc4676014: 0x00000003
	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, ptg_cfg);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_mode, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_en, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, ptg_cfg);
#endif

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_ION_CI_Start_TP_Checker(u16 pkt_cnt, u16 *pkt, u16 *err)
{
	unsigned long flag;
	u32 timeout; // ms
	u8 val;

	if (!pkt_cnt)
		return -EINVAL;
	if (!pkt || !err)
		return -EFAULT;

	// 200 us for 1 pkt = pkt_cnt * 200
	timeout = pkt_cnt * 200;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	//#SIPO1 checker & ptg enable
	//0xc4676014: 0x00000203
	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, ptg_cfg);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_mode, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_chk1_en, 1);
	CTOP_CTRL_O26Ax_Wr01(ION1_SRDS12TO3, ptg_cfg, reg_ptg0_en, 1);
	CTOP_CTRL_O26Ax_WrFL(ION1_SRDS12TO3, ptg_cfg);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	usleep_range(timeout, timeout);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, ptg_cfg);
	CTOP_CTRL_O26Ax_Rd01(ION1_SRDS12TO3, ptg_cfg, result_valid1, val);

	CTOP_CTRL_O26Ax_RdFL(ION1_SRDS12TO3, chk_cnt1);
	CTOP_CTRL_O26Ax_Rd01(ION1_SRDS12TO3, chk_cnt1, rx_pkt_cnt1, *pkt);
	CTOP_CTRL_O26Ax_Rd01(ION1_SRDS12TO3, chk_cnt1, err_pkt_cnt1, *err);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	if (!val) // valid is not arrived yet
		return -EAGAIN;

	return 0;
}
#endif // INCLUDE_O26_CHIP_KDRV
