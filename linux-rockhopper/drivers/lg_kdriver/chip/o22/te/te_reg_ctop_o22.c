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
#include "te_reg_o22.h"

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

int O22_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu17);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu17,
			     reg_tpi_int_clk_bypass, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu17);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu05);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu05,
			     reg_tpi_cam_clk_bypass, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu05);

	/* clk bypass:0, filter margin:3nsec. see SICDTV-10092 */
	/* clk flt_sel:1, (0: 100Mhz, 1:480Mhz) see SCDCR-4568 */
	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu09);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu09,
			     reg_tpi_ext1_clk_bypass, 0);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu09);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu10);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu10,
			     reg_tpi_ext1_clk_flt_margin, 3);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu10);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu11);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu11,
			     reg_tpi_ext1_clk_flt_sel, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu11);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu13);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu13,
			     reg_tpi_ext2_clk_bypass, 0);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu13);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu14);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu14,
			     reg_tpi_ext2_clk_flt_margin, 3);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu14);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu15);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu15,
			     reg_tpi_ext2_clk_flt_sel, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu15);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu21);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu21,
			     reg_tpi_sext1_clk_bypass, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu21);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu25);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu25,
			     reg_tpi_sext2_clk_bypass, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu25);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu29);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu29,
			     reg_tpi_sext3_clk_bypass, 1);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu29);

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

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu04);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu04,
			     reg_te_ciout_clk_sel, v);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu04);

	return 0;
}

int O22_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
{

	int ret;
	unsigned long flags;

	TRACE_ENTER("clk=%d", clk);

	spin_lock_irqsave(&ctop_reg_lock, flags);
	ret = set_ci_out_clock(clk);
	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return ret;
}

int O22_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	return -ENODEV;
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

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu03);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu03,
			     reg_stpo_clk_sel, v);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu03);

	v = (mode == TPO_FORMAT_PARALLEL) ? 0 : 1;
	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_CPU, bnd_cpu_r18);
	CTOP_CTRL_O22Ax_Wr01(BND_CTRL_CPU, bnd_cpu_r18, reg_tpo_outmux_sel, v);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_CPU, bnd_cpu_r18);

	return 0;
}

static void set_ext0_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v;

	v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd068);
	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd069);

	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
			     reg_pad_tpi_data0_ext1_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
				     reg_pad_tpi_data1_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
				     reg_pad_tpi_data2_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
				     reg_pad_tpi_data3_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
				     reg_pad_tpi_data4_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069,
				     reg_pad_tpi_data5_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069,
				     reg_pad_tpi_data6_ext1_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069,
				     reg_pad_tpi_data7_ext1_mux_sel, v);
	}

	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
			     reg_pad_tpi_clk_ext1_mux_sel, v);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069,
			     reg_pad_tpi_sop_ext1_mux_sel, v);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd069,
			     reg_pad_tpi_val_ext1_mux_sel, v);

	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd068);
	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd069);
}

static void set_ext1_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v;

	v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd066);
	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd067);
	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd068);

	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
			     reg_pad_tpi_data0_ext2_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data1_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data2_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data3_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data4_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data5_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data6_ext2_mux_sel, v);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd067,
				     reg_pad_tpi_data7_ext2_mux_sel, v);
	}

	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd066,
			     reg_pad_tpi_clk_ext2_mux_sel, v);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
			     reg_pad_tpi_sop_ext2_mux_sel, v);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd068,
			     reg_pad_tpi_val_ext2_mux_sel, v);

	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd066);
	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd067);
	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd068);
}


int O22_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
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

int O22_TE_REG_GetDcoInputClock(u32 *freq)
{
	return -ENODEV;
}

int O22_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

#if 0 //use if mux_sel is used for gpio
	CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_WOV, pad_wov68);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_WOV, pad_wov68,
			     reg_pad_micom_26_mux_sel, 1);
	CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_WOV, pad_wov68,
			     reg_pad_micom_27_mux_sel, 0);
	CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_WOV, pad_wov68);
#endif

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_WOV, bnd_wov_r042);
	switch (uart) {
	case TE_UART_MCU0:
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r042,
				     main_uart_sel3, 8);
		TE_REG_SetUartMux(0);
		name = "mcu0";
		break;
	case TE_UART_MCU1:
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r042,
				     main_uart_sel3, 8);
		TE_REG_SetUartMux(1);
		name = "mcu1";
		break;
	default: //for arm
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r042,
				     main_uart_sel3, 1);
		name = "arm";
	}

	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_WOV, bnd_wov_r042);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int O22_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_WOV, bnd_wov_r034);

	switch (jtag) {
	case TE_JTAG_MCU0:
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r034,
				     main_jtag_sel0, 9);
		name = "mcu0";
		break;
	case TE_JTAG_MCU1:
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r034,
				     main_jtag_sel0, 10);
		name = "mcu1";
		break;
	default: //arm
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_WOV, bnd_wov_r034,
				     main_jtag_sel0, 0);
		name = "arm";
	}

	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_WOV, bnd_wov_r034);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}

int O22_TE_REG_SetGlitchFreeFilter(bool en)
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

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu17);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu17,
			     reg_tpi_int_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu17);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu05);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu05,
			     reg_tpi_cam_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu05);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu09);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu09,
			     reg_tpi_ext1_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu09);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu13);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu13,
			     reg_tpi_ext2_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu13);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu21);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu21,
			     reg_tpi_sext1_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu21);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu25);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu25,
			     reg_tpi_sext2_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu25);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu29);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu29,
			     reg_tpi_sext3_clk_bypass, bypass);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu29);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu19);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu19,
			     reg_tpi_int_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu19);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu07);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu07,
			     reg_tpi_cam_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu07);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu11);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu11,
			     reg_tpi_ext1_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu11);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu15);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu15,
			     reg_tpi_ext2_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu15);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu23);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu23,
			     reg_tpi_sext1_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu23);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu27);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu27,
			     reg_tpi_sext2_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu27);

	CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu31);
	CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu31,
			     reg_tpi_sext3_clk_flt_sel, flt_sel);
	CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu31);

	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return 0;
}

int O22_TE_REG_SetInputMux(enum te_reg_input_mux type)
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

	CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_TE, crg_te04);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te04,
			     reg_tpi_cam_clk_sel, v);
	CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_TE, crg_te04);

	if (type == TE_INPUT_MUX_3_SERIAL) {
		// only set these registers to enable stpi3
		CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_VD0, pad_vd065);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd065,
				     reg_pad_diseqc_cmd_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd065,
				     reg_pad_diseqc_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd065,
				     reg_pad_diseqci_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_VD0, pad_vd065,
				     reg_pad_fefctrl_mux_sel, 2);
		CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_VD0, pad_vd065);

		/* mux select between CAM and serial TP.
		   0:CAM, 1:serial TP */
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_CPU, bnd_cpu_r18);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_CPU, bnd_cpu_r18,
				     reg_tpi_cam_mux_sel, 1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_CPU, bnd_cpu_r18);


		/* set clk_flt_margin as 1 for arib 8K */
		CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu09);
		CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu09,
				     reg_tpi_ext1_clk_bypass, 0);
		CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu09);

		CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu10);
		CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu10,
				     reg_tpi_ext1_clk_flt_margin, 1);
		CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu10);


		CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu13);
		CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu13,
				     reg_tpi_ext2_clk_bypass, 0);
		CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu13);

		CTOP_CTRL_O22Ax_RdFL(MCRG_CTRL_CPU, crg_main_cpu14);
		CTOP_CTRL_O22Ax_Wr01(MCRG_CTRL_CPU, crg_main_cpu14,
				     reg_tpi_ext2_clk_flt_margin, 1);
		CTOP_CTRL_O22Ax_WrFL(MCRG_CTRL_CPU, crg_main_cpu14);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O22_TE_REG_ClockGate(bool disable)
{
	unsigned long flag;
	u8 v = (disable) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_TE, crg_te02);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_axi_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_stpo_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_te_ciout_clk_gate_en,
			     v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_te_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_temcu_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_tpi_cam_clk_gate_en,
			     v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_1_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_1_s_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_2_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_2_s_clk_gate_en, v);
	CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_int_demod_clk_gate_en, v);
	CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_TE, crg_te02);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}
