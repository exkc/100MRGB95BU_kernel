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
 *  CTOP Register Access for O26
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#ifdef INCLUDE_O26_CHIP_KDRV
#include "te_impl.h"
#include "sys_regs.h"
#include "te_reg_o26.h"
#include "o26/ion/ion_reg_o26.h"

#define TRACE_ENTER(fmt, args...)                                           \
	do                                                                  \
	{                                                                   \
		if (unlikely(g_te_reg_log_mask & REG_LOG_CTOP_MASK))        \
		{                                                           \
			log_noti("@CTOP_REG : %s(" fmt ")", __F__, ##args); \
		}                                                           \
	} while (0)

#define TRACE_EXIT(fmt, args...)                                            \
	do                                                                  \
	{                                                                   \
		if (unlikely(g_te_reg_log_mask & REG_LOG_CTOP_MASK))        \
		{                                                           \
			log_noti("~CTOP_REG : %s(" fmt ")", __F__, ##args); \
		}                                                           \
	} while (0)

static DEFINE_SPINLOCK(ctop_reg_lock);
int O26_TE_REG_CTOP_SetInitValue(void)
{
	unsigned long flag;

	TRACE_ENTER("");

	spin_lock_irqsave(&ctop_reg_lock, flag);

	// TODO: Check for All TPI inputs

	// int_tpi: clk bypass
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud050);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud050,
			     reg_tpi_int_clk_bypass, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud050);

	// TODO: check for ION
	//  cam_tpi: flt_sel:1, flt_margin:2
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud038);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud038,
			     reg_tpi_cam_clk_bypass, 0);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud038);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud039);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud039,
			     reg_tpi_cam_clk_flt_margin, 2);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud039);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud040);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud040,
			     reg_tpi_cam_clk_flt_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud040);

	// ext1_tpi: flt_sel:1, flt_margin:3
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud042);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud042,
			     reg_tpi_ext1_clk_bypass, 0);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud042);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud043);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud043,
			     reg_tpi_ext1_clk_flt_margin, 3);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud043);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud044);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud044,
			     reg_tpi_ext1_clk_flt_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud044);

	// ext2_tpi: flt_sel:1, flt_margin:3
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud046);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud046,
			     reg_tpi_ext2_clk_bypass, 0);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud046);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud047);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud047,
			     reg_tpi_ext2_clk_flt_margin, 3);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud047);

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud048);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud048,
			     reg_tpi_ext2_clk_flt_sel, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud048);

	// sext1_tpi: clk bypass
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud054);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud054,
			     reg_tpi_sext1_clk_bypass, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud054);

	// sext2_tpi: clk bypass
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud058);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud058,
			     reg_tpi_sext2_clk_bypass, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud058);

	// sext3_tpi: clk bypass
	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud062);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud062,
			     reg_tpi_sext3_clk_bypass, 1);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud062);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

static int set_ci_out_clock(enum te_reg_out_clk clk)
{
	u8 v;

	switch (clk)
	{
	case OUTPUT_CLK_24MHZ:
		v = 0; // div16
		break;
	case OUTPUT_CLK_12MHZ:
		v = 1; // div32
		break;
	case OUTPUT_CLK_10MHZ:
		v = 2; // div40
		break;
	case OUTPUT_CLK_8MHZ:
		v = 3; // div50
		break;
	case OUTPUT_CLK_6MHZ:
		v = 4; // div64
		break;
	case OUTPUT_CLK_4MHZ:
		v = 5; // div100
		break;
	case OUTPUT_CLK_2MHZ:
		v = 6; // div200
		break;
	default:
		log_error("not supported clk(%d)", clk);
		return -EINVAL;
	}

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud037);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud037,
			     reg_te_ciout_clk_sel, v);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud037);

	return 0;
}

int O26_TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
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

	switch (clk)
	{
	case OUTPUT_CLK_198MHZ:
		v = 0; // div2
		break;
	case OUTPUT_CLK_99MHZ:
		v = 1; // div4
		break;
	case OUTPUT_CLK_66MHZ:
		v = 2; // div6
		break;
	case OUTPUT_CLK_49MHZ:
		v = 3; // div8
		break;
	case OUTPUT_CLK_33MHZ:
		v = 4; // div12
		break;
	case OUTPUT_CLK_24MHZ:
		v = 5; // div16
		break;
	case OUTPUT_CLK_12MHZ:
	case OUTPUT_CLK_10MHZ:
	case OUTPUT_CLK_8MHZ:
		v = 6; // div32
		break;
	case OUTPUT_CLK_6MHZ:
	case OUTPUT_CLK_4MHZ:
	case OUTPUT_CLK_2MHZ:
		v = 7; // div64
		break;
	default:
		log_error("not supported clk(%d)", clk);
		return -EINVAL;
	}

	CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud036);
	CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud036,
			     reg_stpo_clk_sel, v);
	CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud036);

	v = (mode == TPO_FORMAT_PARALLEL) ? 0 : 1;
	CTOP_CTRL_O26Ax_RdFL(BND_CTRL_AUD, aud_syn_00);
	CTOP_CTRL_O26Ax_Wr01(BND_CTRL_AUD, aud_syn_00, reg_tpo_outmux_sel, v);
	CTOP_CTRL_O26Ax_WrFL(BND_CTRL_AUD, aud_syn_00);

	return 0;
}

static void set_ext0_mux(enum te_reg_port_dir dir)
{
	u32 v = (dir == PORT_DIR_OUTPUT) ? 4 : 0;

	O26_ION_IO_Set_tpi_mux(0, v);
}

static void set_ext1_mux(enum te_reg_port_dir dir)
{
	u32 v = (dir == PORT_DIR_OUTPUT) ? 4 : 0;

	O26_ION_IO_Set_tpi_mux(1, v);
}

int O26_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	int ret = 0;
	unsigned long flags;
	u8 v = 0;

	TRACE_ENTER("port=%d,dir=%d,mode=%d,clk=%d", port, dir, mode, clk);

	spin_lock_irqsave(&ctop_reg_lock, flags);

	if (port == TPI_CAM_LOOP_BACK)
	{
		if (dir == PORT_DIR_OUTPUT)
		{
			ret = set_ci_out_clock(clk);
		}
		else
		{
			log_error("can't set cam loop back as input");
			ret = -EINVAL;
		}
	}
	else if (port == TPI_EXT_DEMOD0)
	{
		set_ext0_mux(dir);
		if (dir == PORT_DIR_OUTPUT) {
			v = (mode == TPO_FORMAT_SERIAL) ? 1 : 0;
			ret = set_tp_out(mode, clk);
		}

		O26_ION_CI_Set_tpo_mode(v);
	}
	else if (port == TPI_EXT_DEMOD1)
	{
		set_ext1_mux(dir);
		if (dir == PORT_DIR_OUTPUT) {
			v = (mode == TPO_FORMAT_SERIAL) ? 1 : 0;
			ret = set_tp_out(mode, clk);
		}

		O26_ION_CI_Set_tpo_mode(v);
	}
	else
	{
		log_error("invalid port[%d]", port);
		ret = -EINVAL;
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flags);

	return ret;
}

int O26_TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	const char *name;

	CTOP_CTRL_O26Ax_RdFL(CPU_BND_CTRL_WOC, mem6);

	switch (uart)
	{
	case TE_UART_MCU0:
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_uart_sel0, 8); // 8:te
		TE_REG_SetUartMux(0);
		name = "mcu0";
		break;
	case TE_UART_MCU1:
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_uart_sel0, 8); // 8:te
		TE_REG_SetUartMux(1);
		name = "mcu1";
		break;
	default: // for arm
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_uart_sel0, 2); // 2:cpu0
		name = "arm";
	}

	CTOP_CTRL_O26Ax_WrFL(CPU_BND_CTRL_WOC, mem6);

	TRACE_EXIT("uart0 is connected with %s", name);

	return 0;
}

int O26_TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	const char *name;

	CTOP_CTRL_O26Ax_RdFL(CPU_BND_CTRL_WOC, mem6);

	switch (jtag)
	{
	case TE_JTAG_MCU0:
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_jtag_sel0, 5);
		name = "mcu0";
		break;
	case TE_JTAG_MCU1: // Not exist
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_jtag_sel0, 6);
		name = "mcu1";
		break;
	default: // arm
		CTOP_CTRL_O26Ax_Wr01(CPU_BND_CTRL_WOC, mem6,
				     reg_main_jtag_sel0, 0);
		name = "arm";
	}

	CTOP_CTRL_O26Ax_WrFL(CPU_BND_CTRL_WOC, mem6);

	log_noti("jtag0 is connected with %s", name);
	return 0;
}

int O26_TE_REG_SetInputMux(enum te_reg_input_mux type)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("type=%d", type);

	/* 0: w_tpi_cam_clk, 1: w_tpi_ext_demod_3_s_clk */
	if (type == TE_INPUT_MUX_3_SERIAL) {
		v = 1; // for O26, it use cam clk. SICDTV-12925
	} else {
		v = 0; // TPI_CAM Enable
	}

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_TE, crg_te004);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te004,
			     reg_tpi_cam_clk_sel, v);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_TE, crg_te004);

	if (type == TE_INPUT_MUX_3_SERIAL)
	{
		// only set these registers to enable stpi3
		CTOP_CTRL_O26Ax_RdFL(CPU_IOMUX_CTRL_WOC, pad_woc66);
		CTOP_CTRL_O26Ax_Wr01(CPU_IOMUX_CTRL_WOC, pad_woc66,
				     reg_pad_diseqc_cmd_mux_sel, 2);
		CTOP_CTRL_O26Ax_Wr01(CPU_IOMUX_CTRL_WOC, pad_woc66,
				     reg_pad_diseqci_mux_sel, 2);
		CTOP_CTRL_O26Ax_Wr01(CPU_IOMUX_CTRL_WOC, pad_woc66,
				     reg_pad_fefctrl_mux_sel, 2);
		CTOP_CTRL_O26Ax_WrFL(CPU_IOMUX_CTRL_WOC, pad_woc66);

		CTOP_CTRL_O26Ax_RdFL(CPU_IOMUX_CTRL_WOC, pad_woc65);
		CTOP_CTRL_O26Ax_Wr01(CPU_IOMUX_CTRL_WOC, pad_woc65,
			reg_pad_diseqc_mux_sel, 2);
		CTOP_CTRL_O26Ax_WrFL(CPU_IOMUX_CTRL_WOC, pad_woc65);

		/* mux select between CAM and serial TP.
		   0:CAM, 1:serial TP */
		CTOP_CTRL_O26Ax_RdFL(BND_CTRL_AUD, aud_syn_01);
		CTOP_CTRL_O26Ax_Wr01(BND_CTRL_AUD, aud_syn_01,
				     reg_tpi_cam_mux_sel, 1);
		CTOP_CTRL_O26Ax_WrFL(BND_CTRL_AUD, aud_syn_01);

		/* set clk_flt_margin as 1 for arib 8K */
		// ext1_tpi: flt_margin:1
		CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud042);
		CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud042,
				     reg_tpi_ext1_clk_bypass, 0);
		CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud042);

		CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud043);
		CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud043,
				     reg_tpi_ext1_clk_flt_margin, 1);
		CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud043);

		// ext2_tpi: flt_margin:1
		CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud046);
		CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud046,
				     reg_tpi_ext2_clk_bypass, 0);
		CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud046);

		CTOP_CTRL_O26Ax_RdFL(MCRG_CTRL_AUD, crg_main_aud047);
		CTOP_CTRL_O26Ax_Wr01(MCRG_CTRL_AUD, crg_main_aud047,
				     reg_tpi_ext2_clk_flt_margin, 1);
		CTOP_CTRL_O26Ax_WrFL(MCRG_CTRL_AUD, crg_main_aud047);
	}

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}

int O26_TE_REG_ClockGate(bool disable)
{
	unsigned long flag;
	u8 v = (disable) ? 1 : 0;

	spin_lock_irqsave(&ctop_reg_lock, flag);

	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_TE, crg_te002);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_axi_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_stpo_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_te_ciout_clk_gate_en,
			     v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_te_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_temcu_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002, reg_tpi_cam_clk_gate_en,
			     v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002,
			     reg_tpi_ext_demod_1_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002,
			     reg_tpi_ext_demod_1_s_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002,
			     reg_tpi_ext_demod_2_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002,
			     reg_tpi_ext_demod_2_s_clk_gate_en, v);
	CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TE, crg_te002,
			     reg_tpi_int_demod_clk_gate_en, v);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_TE, crg_te002);

	spin_unlock_irqrestore(&ctop_reg_lock, flag);

	return 0;
}
#endif // INCLUDE_O26_CHIP_KDRV
