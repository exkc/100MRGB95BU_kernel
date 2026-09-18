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

#include "sys_regs.h"
#include "te_impl.h"
#include "te_reg_o18.h"

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

int O18_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);
	CTOP_CTRL_O18A0_RdFL(CTOP_TIVG, ctr39);
	CTOP_CTRL_O18A0_Wr01(CTOP_TIVG, ctr39, j3_glitch_free_filter, 1);
	CTOP_CTRL_O18A0_WrFL(CTOP_TIVG, ctr39);
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O18_TE_REG_SetCiInput(enum te_reg_ci_input src)
{
	unsigned long flag;
	int ret = 0;

	TRACE_ENTER("src=%d", src);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, ctr02);
	switch (src) {
	case CI_INPUT_SRC_IN_DEMOD:
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl0, 0);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl1, 1);
		break;

	case CI_INPUT_SRC_EXT_INPUT0:
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl0, 0);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl1, 0);
		break;

	case CI_INPUT_SRC_EXT_INPUT1:
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl0, 1);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl1, 0);
		break;

	case CI_INPUT_SRC_TE:
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl0, 1);
		CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpo_sel_ctrl1, 1);
		break;

	default:
		ret = RET_ERROR;
		goto exit;
	}
	CTOP_CTRL_O18A0_WrFL(BMC_SYN, ctr02);

 exit:
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return ret;
}

int O18_TE_REG_GetCiInput(enum te_reg_ci_input *src)
{
	u8 ctrl0, ctrl1;
	unsigned long flag;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O18A0_RdFL(BMC_SYN, ctr02);
	CTOP_CTRL_O18A0_Rd01(BMC_SYN, ctr02, i_tpo_sel_ctrl0, ctrl0);
	CTOP_CTRL_O18A0_Rd01(BMC_SYN, ctr02, i_tpo_sel_ctrl1, ctrl1);

	if (ctrl0 == 0 && ctrl1 == 1)
		*src = CI_INPUT_SRC_IN_DEMOD;
	else if (ctrl0 == 0 && ctrl1 == 0)
		*src = CI_INPUT_SRC_EXT_INPUT0;
	else if (ctrl0 == 1 && ctrl1 == 0)
		*src = CI_INPUT_SRC_EXT_INPUT1;
	else if (ctrl0 == 1 && ctrl1 == 1)
		*src = CI_INPUT_SRC_TE;
	else
		*src = CI_INPUT_SRC_NONE;

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	TRACE_EXIT("*src=%d", *src);

	return 0;
}

int O18_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
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

	CTOP_CTRL_O18A0_RdFL(CTRL_TIV, crg_tiv01);
	CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, te_ciout_clk_sel, v);
	CTOP_CTRL_O18A0_WrFL(CTRL_TIV, crg_tiv01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O18_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	unsigned long flag;
	u8 v;

	CHECK_PARAM(ch > 3, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O18A0_RdFL(CTRL_TIV, crg_tiv01);
	switch (ch) {
	case 0:
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, ch0_sclk_sel, v);
		break;
	case 1:
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, ch1_sclk_sel, v);
		break;
	case 2:
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, ch2_sclk_sel, v);
		break;
	case 3:
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, ch3_sclk_sel, v);
		break;
	default:
		break;
	}
	CTOP_CTRL_O18A0_WrFL(CTRL_TIV, crg_tiv01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O18_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	int ret = -EIO;
	unsigned long flag;
	int v = (mode == TPO_FORMAT_PARALLEL) ? 0x1 : 0x0;

	TRACE_ENTER("port=%d,dir=%d,mode=%d,clk=%d", port, dir, mode, clk);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	if (dir == PORT_DIR_OUTPUT) {
		UINT32 val;

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

			CTOP_CTRL_O18A0_RdFL(CTRL_TIV, crg_tiv01);
			CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01,
					     te_ciout_clk_sel, val);
			CTOP_CTRL_O18A0_WrFL(CTRL_TIV, crg_tiv01);
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
				val = 6;
				break;
			case OUTPUT_CLK_6MHZ:
				val = 7;
				break;
			default:
				log_error("not supported clk(%d)", clk);
				ret = -EINVAL;
				goto exit;
			}

			CTOP_CTRL_O18A0_RdFL(CTRL_TIV, crg_tiv01);
			CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv01, stpo_clk_sel,
					     val);
			CTOP_CTRL_O18A0_WrFL(CTRL_TIV, crg_tiv01);
		}
	}

	if (port == TPI_EXT_DEMOD0) {
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, ctr02);

		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02,
					     i_tp_dvd_out_ctrl_0, 1);
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02,
					     i_tp_dvd_out_ctrl_1, v);
		} else {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02,
					     i_tp_dvd_out_ctrl_0, 0);
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02,
					     i_tp_dvd_out_ctrl_1, 0);
		}

		CTOP_CTRL_O18A0_WrFL(BMC_SYN, ctr02);
	} else if (port == TPI_EXT_DEMOD1) {
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, ctr02);

		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_stpi0_out_ctrl_0,
					     1);
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_stpi0_out_ctrl_1,
					     v);
		} else {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_stpi0_out_ctrl_0,
					     0);
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_stpi0_out_ctrl_1,
					     0);
		}

		CTOP_CTRL_O18A0_WrFL(BMC_SYN, ctr02);
	} else if (port == TPI_CAM_LOOP_BACK) {
		CTOP_CTRL_O18A0_RdFL(BMC_SYN, ctr02);

		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpio_sel_ctrl,
					     0);
		} else {
			CTOP_CTRL_O18A0_Wr01(BMC_SYN, ctr02, i_tpio_sel_ctrl,
					     1);
		}

		CTOP_CTRL_O18A0_WrFL(BMC_SYN, ctr02);
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

int O18_TE_REG_GetDcoInputClock(UINT32 * freq)
{
	*freq = 200;		//Default: 2400 / 12 = 200 (160607)
	return 0;
}

int O18_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_O18A0_RdFL(CTOP_SRE, ctr01);
	if (uart == TE_UART_MCU0) {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart0_sel, 8);
		TE_REG_SetUartMux(0);
		name = "mcu0";
	} else if (uart == TE_UART_MCU1) {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart0_sel, 8);
		TE_REG_SetUartMux(1);
		name = "mcu1";
	} else {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr01, uart0_sel, 1);
		name = "arm";
	}
	CTOP_CTRL_O18A0_WrFL(CTOP_SRE, ctr01);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int O18_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_O18A0_RdFL(CTOP_SRE, ctr00);

	if (jtag == TE_JTAG_MCU0) {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 5);

		name = "mcu0";
	} else if (jtag == TE_JTAG_MCU1) {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 6);

		name = "mcu1";
	} else {
		CTOP_CTRL_O18A0_Wr01(CTOP_SRE, ctr00, jtag0_sel, 0);

		name = "arm";
	}

	CTOP_CTRL_O18A0_WrFL(CTOP_SRE, ctr00);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}
