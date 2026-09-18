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
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-02-09
 *  @note		Additional information.
 */

#include "sys_regs.h"
#include "te_impl.h"
#include "te_reg_m17.h"

#define TE_AXI_READ_ACCESS		0x1
#define TE_AXI_WRITE_ACCESS		(0x1 << 1)
#define ICOD_AXI_READ_ACCESS	(0x1 << 2)
#define ICOD_AXI_WRITE_ACCESS	(0x1 << 3)

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

int M17_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("");

	/* M16+ External Demod 1 requires below GPIO as enable */
	spin_lock_irqsave(&ctop_reg_lock, flag);

	v = TE_AXI_READ_ACCESS | TE_AXI_WRITE_ACCESS | ICOD_AXI_READ_ACCESS |
	    ICOD_AXI_WRITE_ACCESS;
	CTOP_CTRL_M17A0_RdFL(TIV_SYN, syn_tiv00);
	CTOP_CTRL_M17A0_Wr01(TIV_SYN, syn_tiv00, ctr00, v);	// from TE block
	CTOP_CTRL_M17A0_WrFL(TIV_SYN, syn_tiv00);

	CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r11);
	CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, gp5_6_mux_en, 0x1);	/* STPI0_SOP_GPIO (Enable) */
	CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, gp5_5_mux_en, 0x1);	/* STPI0_VAL_GPIO (Enable) */
	CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r11);

	if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))	// Turn off glitch free control
	{
		CTOP_CTRL_M17A0_RdFL(AUD_SYN, syn_aud00);
		CTOP_CTRL_M17A0_Wr01(AUD_SYN, syn_aud00, tpi_int_clk_bypass, 1);
		CTOP_CTRL_M17A0_Wr01(AUD_SYN, syn_aud00, tpi_ext_clk_bypass, 1);
		CTOP_CTRL_M17A0_Wr01(AUD_SYN, syn_aud00,
				     tpi_cam_demod_clk_bypass, 1);
		CTOP_CTRL_M17A0_Wr01(AUD_SYN, syn_aud00, tpi_cam_clk_bypass, 1);
		CTOP_CTRL_M17A0_Wr01(AUD_SYN, syn_aud00, stpi0_clk_bypass, 1);
		CTOP_CTRL_M17A0_WrFL(AUD_SYN, syn_aud00);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int M17_TE_REG_SetCiInput(enum te_reg_ci_input src)
{
	unsigned long flag;
	int ret = 0;

	TRACE_ENTER("src=%d", src);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r16);
	switch (src) {
	case CI_INPUT_SRC_IN_DEMOD:
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl0, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl1, 1);	// from DEMOD block
		break;

	case CI_INPUT_SRC_EXT_INPUT0:
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl0, 0);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl1, 0);
		break;

	case CI_INPUT_SRC_EXT_INPUT1:
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl0, 1);
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl1, 0);
		break;

	case CI_INPUT_SRC_TE:
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl0, 1);	// from TE block
		CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpo_sel_ctrl1, 1);
		break;

	default:
		ret = -EINVAL;
		goto exit;
	}
	CTOP_CTRL_M17A0_WrFL(FME0, ctop_fme0_r16);

 exit:
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return ret;
}

int M17_TE_REG_GetCiInput(enum te_reg_ci_input *src)
{
	u8 ctrl0, ctrl1;
	unsigned long flag;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r16);
	CTOP_CTRL_M17A0_Rd01(FME0, ctop_fme0_r16, tpo_sel_ctrl0, ctrl0);
	CTOP_CTRL_M17A0_Rd01(FME0, ctop_fme0_r16, tpo_sel_ctrl1, ctrl1);

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

int M17_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
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
		return RET_ERROR;
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M17A0_RdFL(TIV_SYN, crg_te00);
	CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, te_ciout_clk_sel, v);
	CTOP_CTRL_M17A0_WrFL(TIV_SYN, crg_te00);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int M17_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	unsigned long flag;
	u8 v;

	CHECK_PARAM(ch > 3, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M17A0_RdFL(TIV_SYN, crg_te00);
	switch (ch) {
	case 0:
		CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, ch0_sclk_sel, v);
		break;
	case 1:
		CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, ch1_sclk_sel, v);
		break;
	case 2:
		CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, ch2_sclk_sel, v);
		break;
	case 3:
		CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, ch3_sclk_sel, v);
		break;
	default:
		break;
	}
	CTOP_CTRL_M17A0_WrFL(TIV_SYN, crg_te00);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

static void SetSTPI0GPIOControl(u8 en)
{
	CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r11);
	CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, gp5_6_mux_en, en);	/* STPI0_SOP_GPIO */
	CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, gp5_5_mux_en, en);	/* STPI0_VAL_GPIO */
	CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r11);
}

int M17_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	int ret = -EIO;
	unsigned long flag;
	int v = (mode == TPO_FORMAT_PARALLEL) ? 0x3 : 0x1;

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

			CTOP_CTRL_M17A0_RdFL(TIV_SYN, crg_te00);
			CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00,
					     te_ciout_clk_sel, val);
			CTOP_CTRL_M17A0_WrFL(TIV_SYN, crg_te00);
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
			default:
				log_error("not supported clk(%d)", clk);
				ret = -EINVAL;
				goto exit;
			}
			CTOP_CTRL_M17A0_RdFL(TIV_SYN, crg_te00);
			CTOP_CTRL_M17A0_Wr01(TIV_SYN, crg_te00, stpo_clk_sel,
					     val);
			CTOP_CTRL_M17A0_WrFL(TIV_SYN, crg_te00);
		}
	}

	if (port == TPI_EXT_DEMOD0) {
		CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r11);
		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, tp_dvb_out_ctrl,
					     v);
		} else {
			CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, tp_dvb_out_ctrl,
					     0);
		}
		CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r11);
	} else if (port == TPI_EXT_DEMOD1) {
		CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r11);
		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, stpi0_out_ctrl,
					     v);
			SetSTPI0GPIOControl(0x0);
		} else {
			CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r11, stpi0_out_ctrl,
					     0);
			SetSTPI0GPIOControl(0x1);
		}
		CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r11);
	} else if (port == TPI_CAM_LOOP_BACK) {
		CTOP_CTRL_M17A0_RdFL(FME0, ctop_fme0_r16);
		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpio_sel_ctrl,
					     0);
		} else {
			CTOP_CTRL_M17A0_Wr01(FME0, ctop_fme0_r16, tpio_sel_ctrl,
					     1);
		}
		CTOP_CTRL_M17A0_WrFL(FME0, ctop_fme0_r16);
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

int M17_TE_REG_GetDcoInputClock(u32 *freq)
{
	*freq = 200;		//Modified 198 Mhz to 200 Mhz(160506)
	return 0;
}

int M17_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r04);
	if (uart == TE_UART_MCU0) {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r04, uart0_sel, 6);
		TE_REG_SetUartMux(0);
		name = "mcu0";
	} else if (uart == TE_UART_MCU1) {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r04, uart0_sel, 6);
		TE_REG_SetUartMux(1);
		name = "mcu1";
	} else {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r04, uart0_sel, 1);
		name = "arm";
	}
	CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r04);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int M17_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_M17A0_RdFL(FMS, ctop_fms_r05);
	if (jtag == TE_JTAG_MCU0) {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r05, jtag0_sel, 4);
		name = "mcu0";
	} else if (jtag == TE_JTAG_MCU1) {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r05, jtag0_sel, 5);
		name = "mcu1";
	} else {
		CTOP_CTRL_M17A0_Wr01(FMS, ctop_fms_r05, jtag0_sel, 0);
		name = "arm";
	}
	CTOP_CTRL_M17A0_WrFL(FMS, ctop_fms_r05);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}
