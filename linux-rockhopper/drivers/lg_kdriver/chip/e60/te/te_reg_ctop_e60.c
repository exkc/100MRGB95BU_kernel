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
 *  sdec driver
 *
 *  @author		Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2017-06-07
 *  @note		Additional information.
 */

#include <linux/kernel.h>
#include "sys_regs.h"
#include "te_impl.h"
#include "te_reg_e60.h"

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_CTOP_MASK)) {		\
		log_noti("@CTOP_REG : %s(" fmt ")", __F__, ##args);	\
	}								\
} while (0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_CTOP_MASK)) {		\
		log_noti("~CTOP_REG : %s(" fmt ")", __F__, ##args);	\
	}								\
} while (0)

static DEFINE_SPINLOCK(ctop_reg_lock);

int E60_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi04);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_int_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_cam_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_ext1_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_ext2_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext1_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext2_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext3_clk_bypass_mode, 1);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi04);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

static int set_ci_out_clock(enum te_reg_out_clk clk)
{
	u8 v;

	switch (clk) {
	case OUTPUT_CLK_24MHZ:
		v = 0;
		break;
	case OUTPUT_CLK_12MHZ:
		v = 1;
		break;
	case OUTPUT_CLK_10MHZ:
		v = 2;
		break;
	case OUTPUT_CLK_8MHZ:
		v = 3;
		break;
	case OUTPUT_CLK_6MHZ:
		v = 4;
		break;
	case OUTPUT_CLK_4MHZ:
		v = 5;
		break;
	case OUTPUT_CLK_2MHZ:
		v = 6;
		break;
	default:
		log_error("not supported clk(%d)", clk);
		return -EINVAL;
	}

	CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi05);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_cvi__te_ciout_clk_sel,
			     v);
	CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi05);

	return 0;
}

int E60_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
{
	int ret;
	unsigned long flags;

	TRACE_ENTER("clk=%d", clk);

	spin_lock_irqsave(&ctop_reg_lock, flags);
	ret = set_ci_out_clock(clk);
	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return ret;
}

int E60_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	unsigned long flags;
	u8 v;

	CHECK_PARAM(ch > 3, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flags);

	switch (ch) {
	case 0:
		CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi05);
		CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05,
				     reg_cvi__te_ch0_sclk_sel, v);
		CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi05);
		break;
	case 1:
		CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi06);
		CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi06,
				     reg_cvi__te_ch1_sclk_sel, v);
		CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi06);
		break;
	case 2:
		CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi05);
		CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05,
				     reg_cvi__te_ch2_sclk_sel, v);
		CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi05);
		break;
	case 3:
		CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi06);
		CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi06,
				     reg_cvi__te_ch3_sclk_sel, v);
		CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi06);
		break;
	default:
		break;
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return 0;
}

static int set_tp_out(enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	u32 v;

	switch (clk) {
	case OUTPUT_CLK_198MHZ:
		v = 0;
		break;
	case OUTPUT_CLK_99MHZ:
		v = 1;
		break;
	case OUTPUT_CLK_66MHZ:
		v = 2;
		break;
	case OUTPUT_CLK_49MHZ:
		v = 3;
		break;
	case OUTPUT_CLK_33MHZ:
		v = 4;
		break;
	case OUTPUT_CLK_24MHZ:
		v = 5;
		break;
	case OUTPUT_CLK_12MHZ:
	case OUTPUT_CLK_10MHZ:
	case OUTPUT_CLK_8MHZ:
		v = 6;
		break;
	case OUTPUT_CLK_6MHZ:
	case OUTPUT_CLK_4MHZ:
	case OUTPUT_CLK_2MHZ:
		v = 7;
		break;
	default:
		log_error("not supported clk(%d)", clk);
		return -EINVAL;
	}

	CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi06);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi06, reg_cvi__stpo_clk_sel, v);
	CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi06);

	v = (mode == TPO_FORMAT_PARALLEL) ? 0 : 1;
	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi27);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi27, reg_tpo_outmux_sel, v);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi27);

	return 0;
}

static void set_ext0_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v;

	v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi23);
	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi24);
	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi25);

	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
			     reg_pad_tpi_data0_ext1_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
				     reg_pad_tpi_data1_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
				     reg_pad_tpi_data2_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
				     reg_pad_tpi_data3_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
				     reg_pad_tpi_data4_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data5_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data6_ext1_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data7_ext1_mux_sel, v);
	}

	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi23,
			     reg_pad_tpi_clk_ext1_mux_sel, v);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi25,
			     reg_pad_tpi_sop_ext1_mux_sel, v);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi25,
			     reg_pad_tpi_val_ext1_mux_sel, v);

	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi23);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi24);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi25);

}

static void set_ext1_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v;

	v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_12);
	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi24);
	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi25);

	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_12,
			     reg_pad_tpi_data0_ext2_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_12,
				     reg_pad_tpi_data1_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_12,
				     reg_pad_tpi_data2_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_12,
				     reg_pad_tpi_data3_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data4_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data5_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data6_ext2_mux_sel, v);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi24,
				     reg_pad_tpi_data7_ext2_mux_sel, v);
	}

	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_12,
			     reg_pad_tpi_clk_ext2_mux_sel, v);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi25,
			     reg_pad_tpi_sop_ext2_mux_sel, v);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi25,
			     reg_pad_tpi_val_ext2_mux_sel, v);

	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_12);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi24);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi25);

}


int E60_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	int ret = 0;
	unsigned long flags;

	TRACE_ENTER("port=%d,dir=%d,mode=%d,clk=%d", port, dir, mode, clk);

	spin_lock_irqsave(&ctop_reg_lock, flags);

	if (port == TPI_CAM_LOOP_BACK) {
		if (dir == PORT_DIR_OUTPUT) {
			ret = set_ci_out_clock(clk);
		} else {
			log_error("can't set cam loop back as input");
			ret = -EINVAL;
		}
	} else if (port == TPI_EXT_DEMOD0) {
		set_ext0_mux(dir, mode);
		if (dir == PORT_DIR_OUTPUT)
			ret = set_tp_out(mode, clk);
	} else if (port == TPI_EXT_DEMOD1) {
		set_ext1_mux(dir, mode);
		if (dir == PORT_DIR_OUTPUT)
			ret = set_tp_out(mode, clk);
	} else {

		log_error("invalid port[%d]\n", port);
		ret = -EINVAL;
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return ret;
}

int E60_TE_REG_GetDcoInputClock(u32 *freq)
{
	return -ENODEV;
}

int E60_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_SRE, syn_sre_05);
	if (lx_chip_rev() >= LX_CHIP_REV(E60, B0)) { //E60B0 changes bits
		switch (uart) {
			case TE_UART_MCU0:
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel3, 9);
				TE_REG_SetUartMux(0);
				name = "mcu0";
				break;
			case TE_UART_MCU1:
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel3, 9);
				TE_REG_SetUartMux(1);
				name = "mcu1";
				break;
			default: //arm
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel3, 1);
				name = "arm";
		}
	} else {
		switch (uart) {
			case TE_UART_MCU0:
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel0, 9);
				TE_REG_SetUartMux(0);
				name = "mcu0";
				break;
			case TE_UART_MCU1:
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel0, 9);
				TE_REG_SetUartMux(1);
				name = "mcu1";
				break;
			default: //arm
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_05,
						reg_main_uart_sel0, 1);
				name = "arm";
		}
	}
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_SRE, syn_sre_05);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int E60_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_SRE, syn_sre_06);
	switch (jtag) {
	case TE_JTAG_MCU0:
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_06,
				     reg_main_jtag_sel0, 9);
		name = "mcu0";
		break;
	case TE_JTAG_MCU1:
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_06,
				     reg_main_jtag_sel0, 10);
		name = "mcu1";
		break;
	default: //arm
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_SRE, syn_sre_06,
				     reg_main_jtag_sel0, 0);
		name = "arm";
	}
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_SRE, syn_sre_06);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}

int E60_TE_REG_SetGlitchFreeFilter(bool en)
{
	unsigned long flags;
	u8 bypass, flt_sel;

	TRACE_ENTER("en=%d", en);

	if (en) {
		bypass = 0;
		flt_sel = 1;
	} else {
		bypass = 1;
		flt_sel = 0;
	}

	spin_lock_irqsave(&ctop_reg_lock, flags);

	CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_CVI, syn_cvi04);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_int_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_cam_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_ext1_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__tpi_ext2_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext1_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext2_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_CVI, syn_cvi04,
			     reg_cvi__stpi_ext3_clk_bypass_mode, bypass);
	CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_CVI, syn_cvi04);


	CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi05);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_tpi_int_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_tpi_cam_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_tpi_ext1_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_tpi_ext2_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_stpi_ext1_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_stpi_ext2_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05, reg_stpi_ext3_clk_flt_sel,
			     flt_sel);
	CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi05);

	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return 0;
}

int E60_TE_REG_SetInputMux(enum te_reg_input_mux type)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("type=%d", type);

	if (type == TE_INPUT_MUX_3_SERIAL) {
		v = 1; // STPI3 Enable
	} else {
		v = 0; // TPI_CAM Enable
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_E60Ax_RdFL(CRG_SUB_CVI, crg_cvi05);
	CTOP_CTRL_E60Ax_Wr01(CRG_SUB_CVI, crg_cvi05,
			     reg_cvi__te_tpi_cam_clk_sel, v);
	CTOP_CTRL_E60Ax_WrFL(CRG_SUB_CVI, crg_cvi05);

	if (type == TE_INPUT_MUX_3_SERIAL) {
		// only set these registers to enable stpi3
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_11);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_11,
				     reg_pad_diseqc_cmd_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_11,
				     reg_pad_diseqc_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_11,
				     reg_pad_diseqci_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_11,
				     reg_pad_fefctrl_mux_sel, 2);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_11);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}
