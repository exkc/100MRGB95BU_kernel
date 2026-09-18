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
#include "te_reg_o20.h"

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

int O20_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O20Ax_RdFL(ATG_SYN, te01);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_stpi0_bypass_mode, 1);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi3_bypass_mode, 1);
//	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi2_bypass_mode, 1); //Not connected
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi1_bypass_mode, 1);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi0_bypass_mode, 1);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi4_bypass_mode, 1);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi5_bypass_mode, 1);
	CTOP_CTRL_O20Ax_WrFL(ATG_SYN, te01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O20_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
{
	unsigned long flag;
	u8 v;

	TRACE_ENTER("clk=%d", clk);
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
	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O20Ax_RdFL(ATG_SYN, crg_te09);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te_ciout_clk_sel, v);
	CTOP_CTRL_O20Ax_WrFL(ATG_SYN, crg_te09);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O20_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	unsigned long flag;
	u8 v;

	CHECK_PARAM(ch > 3, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);
	//TODO: Check with PCR recovery
	CTOP_CTRL_O20Ax_RdFL(ATG_SYN, crg_te09);
	switch (ch) {
	case 0:
		CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te__ch0_sclk_sel, v);
		break;
	case 1:
		CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te__ch1_sclk_sel, v);
		break;
	case 2:
		CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te__ch2_sclk_sel, v);
		break;
	case 3:
		CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te__ch3_sclk_sel, v);
		break;
	default:
		break;
	}
	CTOP_CTRL_O20Ax_WrFL(ATG_SYN, crg_te09);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O20_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	int ret = -EIO;
	unsigned long flag;

	TRACE_ENTER("port=%d,dir=%d,mode=%d,clk=%d", port, dir, mode, clk);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	if (dir == PORT_DIR_OUTPUT) {
		u32 val;

		if (port == TPI_CAM_LOOP_BACK) {
			switch (clk) {
			case OUTPUT_CLK_24MHZ:
				val = 0;
				break;
			case OUTPUT_CLK_12MHZ:
				val = 1;
				break;
			case OUTPUT_CLK_10MHZ:
				val = 2;
				break;
			case OUTPUT_CLK_8MHZ:
				val = 3;
				break;
			case OUTPUT_CLK_6MHZ:
				val = 4;
				break;
			case OUTPUT_CLK_4MHZ:
				val = 5;
				break;
			case OUTPUT_CLK_2MHZ:
				val = 6;
				break;
			default:
				log_error("not supported clk(%d)", clk);
				ret = -EINVAL;
				goto exit;
			}

			CTOP_CTRL_O20Ax_RdFL(ATG_SYN, crg_te09);
			CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_te_ciout_clk_sel,
					     val);
			CTOP_CTRL_O20Ax_WrFL(ATG_SYN, crg_te09);
		} else {
			switch (clk) {
			case OUTPUT_CLK_198MHZ:
				val = 0;
				break;
			case OUTPUT_CLK_99MHZ:
				val = 1;
				break;
			case OUTPUT_CLK_66MHZ:
				val = 2;
				break;
			case OUTPUT_CLK_49MHZ:
				val = 3;
				break;
			case OUTPUT_CLK_33MHZ:
				val = 4;
				break;
			case OUTPUT_CLK_24MHZ:
				val = 5;
				break;
			case OUTPUT_CLK_12MHZ:
			case OUTPUT_CLK_10MHZ:
			case OUTPUT_CLK_8MHZ:
				val = 6;
				break;
			case OUTPUT_CLK_6MHZ:
			case OUTPUT_CLK_4MHZ:
			case OUTPUT_CLK_2MHZ:
				val = 7;
				break;
			default:
				log_error("not supported clk(%d)", clk);
				ret = -EINVAL;
				goto exit;
			}

			CTOP_CTRL_O20Ax_RdFL(ATG_SYN, crg_te09);
			CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_stpo_clk_sel,
					     val);
			CTOP_CTRL_O20Ax_WrFL(ATG_SYN, crg_te09);
		}
	}

	if (port == TPI_EXT_DEMOD0) {
		CTOP_CTRL_O20Ax_RdFL(CTOP_FMS, iosel);
		//TODO: Check
		if (dir == PORT_DIR_OUTPUT) {
			if (mode == TPO_FORMAT_PARALLEL) {
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_dvb_out_ctrl0, 0);
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_dvb_out_ctrl1, 1);
			} else {
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_dvb_out_ctrl0, 1);
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_dvb_out_ctrl1, 0);
			}
		} else {
			CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
					     reg_dvb_out_ctrl0, 0);
			CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
					     reg_dvb_out_ctrl1, 0);
		}

		CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, iosel);
	} else if (port == TPI_EXT_DEMOD1) {
		CTOP_CTRL_O20Ax_RdFL(CTOP_FMS, iosel);
		//TODO: Check
		if (dir == PORT_DIR_OUTPUT) {
			if (mode == TPO_FORMAT_PARALLEL) {
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_stpi0_out_ctrl0, 0);
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_stpi0_out_ctrl1, 1);
			} else {
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_stpi0_out_ctrl0, 1);
				CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
						     reg_stpi0_out_ctrl1, 0);
			}
		} else {
			CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
					     reg_stpi0_out_ctrl0, 0);
			CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, iosel,
					     reg_stpi0_out_ctrl1, 0);
		}

		CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, iosel);
	} else if (port == TPI_CAM_LOOP_BACK) {
#if 0	// TODO: FIXME
		CTOP_CTRL_O20Ax_RdFL(CTOP_FME0, ctop_fme0_r07);

		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_O20Ax_Wr01(CTOP_FME0, ctop_fme0_r07,
					     reg_tpio_sel_ctrl, 0);
		} else {
			CTOP_CTRL_O20Ax_Wr01(CTOP_FME0, ctop_fme0_r07,
					     reg_tpio_sel_ctrl, 1);
		}

		CTOP_CTRL_O20Ax_WrFL(CTOP_FME0, ctop_fme0_r07);
#endif
	} else {
		log_error("invalid port[%d]\n", port);
		ret = -EINVAL;
		goto exit;
	}
	ret = 0;
 exit:
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return ret;
}

int O20_TE_REG_GetDcoInputClock(u32 *freq)
{
	*freq = 50;		//Default value 50 (190419)
	//TODO:Check and modify
	return 0;
}

int O20_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, uart_mux);

	if (uart == TE_UART_MCU0) {
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, uart_mux, reg_uart0_sel, 6);
		TE_REG_SetUartMux(0);
		name = "mcu0";
	} else if (uart == TE_UART_MCU1) {
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, uart_mux, reg_uart0_sel, 6);
		TE_REG_SetUartMux(1);
		name = "mcu1";
	} else {		//arm
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, uart_mux, reg_uart0_sel, 1);
		name = "arm";
	}

	CTOP_CTRL_O20Ax_WrFL(CTOP_ATG, uart_mux);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int O20_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, jtag_mux);

	//TODO: Check te0/te1
	if (jtag == TE_JTAG_MCU0) {
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, jtag_mux, reg_jtag0_sel, 3);

		name = "mcu0";
	} else if (jtag == TE_JTAG_MCU1) {
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, jtag_mux, reg_jtag0_sel, 4);

		name = "mcu1";
	} else {		//arm
		CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, jtag_mux, reg_jtag0_sel, 0);

		name = "arm";
	}

	CTOP_CTRL_O20Ax_WrFL(CTOP_ATG, jtag_mux);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}

int O20_TE_REG_SetGlitchFreeFilter(bool en)
{
	unsigned long flag;
	u8 bypass, flt_sel;

	TRACE_ENTER("en=%d", en);

	if (en) {
		bypass = 0;
		flt_sel = 1;
	} else {
		bypass = 1;
		flt_sel = 0;
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O20Ax_RdFL(ATG_SYN, te01);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi0_bypass_mode, bypass);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi1_bypass_mode, bypass);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi2_bypass_mode, bypass);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_tpi3_bypass_mode, bypass);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, te01, reg_stpi0_bypass_mode, bypass);
	CTOP_CTRL_O20Ax_WrFL(ATG_SYN, te01);

	CTOP_CTRL_O20Ax_RdFL(ATG_SYN, crg_te09);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_tpi0_clk_flt_sel, flt_sel);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_tpi1_clk_flt_sel, flt_sel);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_tpi2_clk_flt_sel, flt_sel);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_tpi3_clk_flt_sel, flt_sel);
	CTOP_CTRL_O20Ax_Wr01(ATG_SYN, crg_te09, reg_stpi0_clk_flt_sel, flt_sel);
	CTOP_CTRL_O20Ax_WrFL(ATG_SYN, crg_te09);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O20_TE_REG_SetInputMux(enum te_reg_input_mux type)
{
	unsigned long flag;
	u8 val;

	if (lx_chip_rev() < LX_CHIP_REV(O20, B0))
		return 0;

	TRACE_ENTER("type=%d", type);

	val = (type == TE_INPUT_MUX_3_SERIAL) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O20Bx_RdFL(ATG_SYN, te01);
	CTOP_CTRL_O20Bx_Wr01(ATG_SYN, te01, reg_te__tpi_mux_sel, val);
	CTOP_CTRL_O20Bx_WrFL(ATG_SYN, te01);

	CTOP_CTRL_O20Ax_RdFL(CTOP_FMS, gpio12_sel);
	CTOP_CTRL_O20Ax_Wr01(CTOP_FMS, gpio12_sel, reg_use_cpu_gpio_12_7, val);
	CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, gpio12_sel);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}
