/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
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
 *  @date		2022-03-28
 *  @note		Additional information.
 */

#include <linux/kernel.h>
#include "sys_regs.h"
#include "te_impl.h"
#include "te_reg_m23.h"

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

int M23_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	/* int bypass off, see SICDTV-11128 */
	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud46);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud46,
			     reg_tpi_int_clk_bypass, 0);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud46);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud47);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud47,
			     reg_tpi_int_clk_flt_margin, 3);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud47);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud48);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud48,
			     reg_tpi_int_clk_flt_sel, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud48);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud34);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud34,
			     reg_tpi_cam_clk_bypass, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud34);

	if (lx_chip_rev() >= LX_CHIP_REV(M23, A1)) {
		CTOP_CTRL_M23Ax_RdFL(SCRG_CTRL_TE, crg_te00);
		CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te00,
				     reg_tpi_int_demod_clk_inv, 1);
		CTOP_CTRL_M23Ax_WrFL(SCRG_CTRL_TE, crg_te00);

		/* CAM clk pad strength = 1; see SICDTV-11128 */
		CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_VD0, pad_vd002);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds3, 0);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds2, 0);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds1, 0);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds0, 1);
		CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_VD0, pad_vd002);
	} else {
		/* CAM clk pad strength = 5; see SICDTV-11128 */
		CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_VD0, pad_vd002);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds3, 0);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds2, 1);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds1, 0);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd002,
				     reg_pad_tpo_clk_cam__ds0, 1);
		CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_VD0, pad_vd002);
	}

	/* clk bypass:0, filter margin:1nsec. see SICDTV-11187  */
	/* clk flt_sel:1, (0: 100Mhz, 1:480Mhz) see SCDCR-4568 */
	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud38);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud38,
			     reg_tpi_ext1_clk_bypass, 0);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud38);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud39);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud39,
			     reg_tpi_ext1_clk_flt_margin, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud39);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud40);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud40,
			     reg_tpi_ext1_clk_flt_sel, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud40);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud42);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud42,
			     reg_tpi_ext2_clk_bypass, 0);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud42);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud43);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud43,
			     reg_tpi_ext2_clk_flt_margin, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud43);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud44);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud44,
			     reg_tpi_ext2_clk_flt_sel, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud44);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud50);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud50,
			     reg_tpi_sext1_clk_bypass, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud50);

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud54);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud54,
			     reg_tpi_sext2_clk_bypass, 1);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud54);

	// no sext3 in M23

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

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud33);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud33,
			     reg_te_ciout_clk_sel, v);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud33);

	return 0;
}

int M23_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
{

	int ret;
	unsigned long flags;

	TRACE_ENTER("clk=%d", clk);

	spin_lock_irqsave(&ctop_reg_lock, flags);
	ret = set_ci_out_clock(clk);
	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return ret;
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

	CTOP_CTRL_M23Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud32);
	CTOP_CTRL_M23Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud32,
			     reg_stpo_clk_sel, v);
	CTOP_CTRL_M23Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud32);

	v = (mode == TPO_FORMAT_PARALLEL) ? 0 : 1;
	CTOP_CTRL_M23Ax_RdFL(BND_CTRL_AUD, aud_syn_00);
	CTOP_CTRL_M23Ax_Wr01(BND_CTRL_AUD, aud_syn_00, reg_tpo_outmux_sel, v);
	CTOP_CTRL_M23Ax_WrFL(BND_CTRL_AUD, aud_syn_00);

	return 0;
}

static void set_ext0_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_BMC, pad_bmc65);
	CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_BMC, pad_bmc66);
	CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_BMC, pad_bmc67);

	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc65,
			     reg_pad_tpi_data0_ext1_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data1_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data2_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data3_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data4_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data5_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data6_ext1_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
				     reg_pad_tpi_data7_ext1_mux_sel, v);
	}

	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc65,
			     reg_pad_tpi_clk_ext1_mux_sel, v);
	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc66,
			     reg_pad_tpi_sop_ext1_mux_sel, v);
	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
			     reg_pad_tpi_val_ext1_mux_sel, v);

	CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_BMC, pad_bmc65);
	CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_BMC, pad_bmc66);
	CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_BMC, pad_bmc67);
}

static void set_ext1_mux(enum te_reg_port_dir dir, enum te_reg_tpo_mode mode)
{
	u32 v = (dir == PORT_DIR_OUTPUT) ? 3 : 0;

	CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_BMC, pad_bmc67);
	CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_BMC, pad_bmc68);

	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
			     reg_pad_tpi_data0_ext2_mux_sel, v);
	if (mode == TPO_FORMAT_PARALLEL) {
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
				     reg_pad_tpi_data1_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
				     reg_pad_tpi_data2_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
				     reg_pad_tpi_data3_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
				     reg_pad_tpi_data4_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
				     reg_pad_tpi_data5_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc68,
				     reg_pad_tpi_data6_ext2_mux_sel, v);
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc68,
				     reg_pad_tpi_data7_ext2_mux_sel, v);
	}

	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc67,
			     reg_pad_tpi_clk_ext2_mux_sel, v);
	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc68,
			     reg_pad_tpi_sop_ext2_mux_sel, v);
	CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_BMC, pad_bmc68,
			     reg_pad_tpi_val_ext2_mux_sel, v);

	CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_BMC, pad_bmc67);
	CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_BMC, pad_bmc68);
}

int M23_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
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

//TODO: check uart/jtag number and selection value
int M23_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_M23Ax_RdFL(MICOM_BND_CTRL_WOC, woc_syn_07);

	switch (uart) {
	case TE_UART_MCU0:
		CTOP_CTRL_M23Ax_Wr01(MICOM_BND_CTRL_WOC, woc_syn_07,
				     reg_main_uart_sel0, 7);
		TE_REG_SetUartMux(0);
		name = "mcu0";
		break;
	case TE_UART_MCU1: //Not exist
		name = "mcu1-disabled";
		break;
	default: //for arm
		CTOP_CTRL_M23Ax_Wr01(MICOM_BND_CTRL_WOC, woc_syn_07,
				     reg_main_uart_sel0, 2);
		name = "arm";
	}

	CTOP_CTRL_M23Ax_WrFL(MICOM_BND_CTRL_WOC, woc_syn_07);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

//TODO: check uart/jtag number and selection value
int M23_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_M23Ax_RdFL(MICOM_BND_CTRL_WOC, woc_syn_04);

	switch (jtag) {
	case TE_JTAG_MCU0:
		CTOP_CTRL_M23Ax_Wr01(MICOM_BND_CTRL_WOC, woc_syn_04,
				     reg_main_jtag_sel0, 4);
		name = "mcu0";
		break;
	case TE_JTAG_MCU1: //Not exist
		name = "mcu1-disabled";
		break;
	default: //arm
		CTOP_CTRL_M23Ax_Wr01(MICOM_BND_CTRL_WOC, woc_syn_04,
				     reg_main_jtag_sel0, 0);
		name = "arm";
	}

	CTOP_CTRL_M23Ax_WrFL(MICOM_BND_CTRL_WOC, woc_syn_04);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}

//M23 does not support 3 tuner
int M23_TE_REG_SetInputMux(enum te_reg_input_mux type)
{
	TRACE_ENTER("type=%d", type);
	log_error("No support for 3 tuner option");

	return -ENODEV;
}

int M23_TE_REG_ClockGate(bool disable)
{
	unsigned long flag;
	u8 v = (disable) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M23Ax_RdFL(SCRG_CTRL_TE, crg_te02);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_axi_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_stpo_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_te_ciout_clk_gate_en,
			     v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_te_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_temcu_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02, reg_tpi_cam_clk_gate_en,
			     v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_1_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_1_s_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_2_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_ext_demod_2_s_clk_gate_en, v);
	CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_TE, crg_te02,
			     reg_tpi_int_demod_clk_gate_en, v);
	CTOP_CTRL_M23Ax_WrFL(SCRG_CTRL_TE, crg_te02);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

