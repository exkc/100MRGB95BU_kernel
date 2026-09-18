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
#include "te_reg_m19.h"

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

int M19_TE_REG_CTOP_SetInitValue(void)
{
	//unsigned long flag;

	TRACE_ENTER("");

	return 0;
}

int M19_TE_REG_SetCiInput(enum te_reg_ci_input src)
{
	unsigned long flag;
	int ret = 0;

	TRACE_ENTER("src=%d", src);

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M19Ax_RdFL(CTOP_FME0, ctop_fme0_r04);
	switch (src) {
	case CI_INPUT_SRC_TE:
		CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r04,
				     reg_tpo_outmux_sel, 0);
		break;

	case CI_INPUT_SRC_IN_DEMOD:
		CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r04,
				     reg_tpo_outmux_sel, 1);
		break;

	case CI_INPUT_SRC_EXT_INPUT0:
		CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r04,
				     reg_tpo_outmux_sel, 2);
		break;

	case CI_INPUT_SRC_EXT_INPUT1:
		CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r04,
				     reg_tpo_outmux_sel, 3);
		break;

	default:
		ret = RET_ERROR;
		goto exit;
	}
	CTOP_CTRL_M19Ax_WrFL(CTOP_FME0, ctop_fme0_r04);

 exit:
	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return ret;
}

int M19_TE_REG_GetCiInput(enum te_reg_ci_input *src)
{
	u8 val;
	unsigned long flag;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M19Ax_RdFL(CTOP_FME0, ctop_fme0_r04);
	CTOP_CTRL_M19Ax_Rd01(CTOP_FME0, ctop_fme0_r04, reg_tpo_outmux_sel, val);

	if (val == 0)
		*src = CI_INPUT_SRC_TE;
	else if (val == 1)
		*src = CI_INPUT_SRC_IN_DEMOD;
	else if (val == 2)
		*src = CI_INPUT_SRC_EXT_INPUT0;
	else if (val == 3)
		*src = CI_INPUT_SRC_EXT_INPUT1;
	else
		*src = CI_INPUT_SRC_NONE;

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	TRACE_EXIT("*src=%d", *src);

	return 0;
}

int M19_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
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

	CTOP_CTRL_M19Ax_RdFL(TI_SYN, crg_te01);
	CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te_ciout_clk_sel, v);
	CTOP_CTRL_M19Ax_WrFL(TI_SYN, crg_te01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int M19_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	unsigned long flag;
	u8 v;

	CHECK_PARAM(ch > 3, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = (src == STCC_CLK_SRC_FIXED) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_M19Ax_RdFL(TI_SYN, crg_te01);
	switch (ch) {
	case 0:
		CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te__ch0_sclk_sel, v);
		break;
	case 1:
		CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te__ch1_sclk_sel, v);
		break;
	case 2:
		CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te__ch2_sclk_sel, v);
		break;
	case 3:
		CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te__ch3_sclk_sel, v);
		break;
	default:
		break;
	}
	CTOP_CTRL_M19Ax_WrFL(TI_SYN, crg_te01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int M19_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
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

			CTOP_CTRL_M19Ax_RdFL(TI_SYN, crg_te01);
			CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te_ciout_clk_sel,
					     val);
			CTOP_CTRL_M19Ax_WrFL(TI_SYN, crg_te01);
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

			CTOP_CTRL_M19Ax_RdFL(TI_SYN, crg_te01);
			CTOP_CTRL_M19Ax_Wr01(TI_SYN, crg_te01, te__stpo_clk_sel,
					     val);
			CTOP_CTRL_M19Ax_WrFL(TI_SYN, crg_te01);
		}
	}

	if (port == TPI_EXT_DEMOD0) {
		CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r05);

		if (dir == PORT_DIR_OUTPUT) {
			if (mode == TPO_FORMAT_PARALLEL) {
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_dvb_out_ctrl0, 0);
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_dvb_out_ctrl1, 1);
			} else {
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_dvb_out_ctrl0, 1);
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_dvb_out_ctrl1, 0);
			}
		} else {
			CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
					     reg_dvb_out_ctrl0, 0);
			CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
					     reg_dvb_out_ctrl1, 0);
		}

		CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r05);
	} else if (port == TPI_EXT_DEMOD1) {
		CTOP_CTRL_M19Ax_RdFL(CTOP_ND0, ctop_nd0_r05);

		if (dir == PORT_DIR_OUTPUT) {
			if (mode == TPO_FORMAT_PARALLEL) {
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_stpi0_out_ctrl0, 0);
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_stpi0_out_ctrl1, 1);
			} else {
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_stpi0_out_ctrl0, 1);
				CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
						     reg_stpi0_out_ctrl1, 0);
			}
		} else {
			CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
					     reg_stpi0_out_ctrl0, 0);
			CTOP_CTRL_M19Ax_Wr01(CTOP_ND0, ctop_nd0_r05,
					     reg_stpi0_out_ctrl1, 0);
		}

		CTOP_CTRL_M19Ax_WrFL(CTOP_ND0, ctop_nd0_r05);
	} else if (port == TPI_CAM_LOOP_BACK) {
		CTOP_CTRL_M19Ax_RdFL(CTOP_FME0, ctop_fme0_r07);

		if (dir == PORT_DIR_OUTPUT) {
			CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r07,
					     reg_tpio_sel_ctrl, 0);
		} else {
			CTOP_CTRL_M19Ax_Wr01(CTOP_FME0, ctop_fme0_r07,
					     reg_tpio_sel_ctrl, 1);
		}

		CTOP_CTRL_M19Ax_WrFL(CTOP_FME0, ctop_fme0_r07);
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

int M19_TE_REG_GetDcoInputClock(u32 *freq)
{
	*freq = 200;		//Default: 2400 / 12 = 200 (180423)
	return 0;
}

int M19_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_M19Ax_RdFL(CTOP_GBM, ctop_gbm0_r04);

	if (uart == TE_UART_MCU0) {
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r04, reg_uart0_sel, 6);
		TE_REG_SetUartMux(0);
		name = "mcu0";
	} else if (uart == TE_UART_MCU1) {
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r04, reg_uart0_sel, 6);
		TE_REG_SetUartMux(1);
		name = "mcu1";
	} else {		//arm
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r04, reg_uart0_sel, 1);
		name = "arm";
	}

	CTOP_CTRL_M19Ax_WrFL(CTOP_GBM, ctop_gbm0_r04);

	TRACE_EXIT("uart0 is connected with %s\n", name);

	return 0;
}

int M19_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_M19Ax_RdFL(CTOP_GBM, ctop_gbm0_r01);

	if (jtag == TE_JTAG_MCU0) {
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r01, reg_jtag0_sel, 4);

		name = "mcu0";
	} else if (jtag == TE_JTAG_MCU1) {
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r01, reg_jtag0_sel, 5);

		name = "mcu1";
	} else {		//arm
		CTOP_CTRL_M19Ax_Wr01(CTOP_GBM, ctop_gbm0_r01, reg_jtag0_sel, 0);

		name = "arm";
	}

	CTOP_CTRL_M19Ax_WrFL(CTOP_GBM, ctop_gbm0_r01);

	log_noti("jtag0 is connected with %s\n", name);

	return 0;
}

int M19_TE_REG_SetGlitchFreeFilter(bool en)
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

	CTOP_CTRL_M19Ax_RdFL(AUD_SYN, syn_aud01);

	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi0_clk_bypass, bypass);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi1_clk_bypass, bypass);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi2_clk_bypass, bypass);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi3_clk_bypass, bypass);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, stpi0_clk_bypass, bypass);

	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi0_clk_flt_sel, flt_sel);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi1_clk_flt_sel, flt_sel);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi2_clk_flt_sel, flt_sel);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, tpi3_clk_flt_sel, flt_sel);
	CTOP_CTRL_M19Ax_Wr01(AUD_SYN, syn_aud01, stpi0_clk_flt_sel, flt_sel);

	CTOP_CTRL_M19Ax_WrFL(AUD_SYN, syn_aud01);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}
