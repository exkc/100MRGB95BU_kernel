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
 *  author		Yeonju Lee
 *  author		Ilkyu Kim
 *  version		1.0
 *  date		2025-04-04
 *  note		Additional information.
 */

#include "sci_impl.h"
#include "sys_regs.h"
#include "os_util.h"

static u32 clock;

u32 sci_ctop_get_clock(void)
{
	return clock;
}

void sci_ctop_select_smartcard(void)
{
	u32 chip = lx_chip();

	log_noti("%s", __func__);

	/* disable jtag and select smart card */
	if (0) {
	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (chip == LX_CHIP_O26) {
		CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_HDMI, pad_hdmi64);
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_HDMI, pad_hdmi64,
				     reg_pad_sc_vcc_sel_mux_sel, 1); // 1: sc_vcc_sel
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_HDMI, pad_hdmi64,
				     reg_pad_sc_rst_mux_sel, 1); // 1: sc_rst
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_HDMI, pad_hdmi64,
				     reg_pad_sc_data_mux_sel, 1); // 1: sc_data_o / sc_data_i
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_HDMI, pad_hdmi64,
				     reg_pad_sc_clk_out_mux_sel, 4); // 4: o_sc_ext_clk
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_HDMI, pad_hdmi64,
				     reg_pad_sc_vccen_mux_sel, 1); // 1: sc_vccen
		CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_HDMI, pad_hdmi64);

		CTOP_CTRL_O26Ax_RdFL(IOMUX_CTRL_AUD, pad_aud64);
		CTOP_CTRL_O26Ax_Wr01(IOMUX_CTRL_AUD, pad_aud64,
				     reg_pad_sc_detect_mux_sel, 1); // 1: sc_detect
		CTOP_CTRL_O26Ax_WrFL(IOMUX_CTRL_AUD, pad_aud64);
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (chip == LX_CHIP_O24) {
		CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_70);
		CTOP_CTRL_O24Ax_RdFL(IOMUX_CTRL_VD0, pad_vd0_71);

		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_70,
				     reg_pad_eb_addr15_mux_sel, 1); /* 1: i_sc_vccen */
		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_70,
				     reg_pad_eb_cs0_mux_sel, 4); /* 4: i_sc_ext_clk */
		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_71,
				     reg_pad_eb_cs1_mux_sel, 1); /* 1: i_sc_data0 */
		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_71,
				     reg_pad_eb_cs2_mux_sel, 1); /* 1: i_sc_detect */
		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_70,
				     reg_pad_eb_cs3_mux_sel, 1); /* 1: i_sc_rst */
		CTOP_CTRL_O24Ax_Wr01(IOMUX_CTRL_VD0, pad_vd0_71,
				     reg_pad_eb_wait_mux_sel, 1); /* 1: i_sc_vcc_sel */

		CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_70);
		CTOP_CTRL_O24Ax_WrFL(IOMUX_CTRL_VD0, pad_vd0_71);
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (chip == LX_CHIP_M23) {
		//M23 shared pin with DVB CAM
		CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_VD0, pad_vd069);
		CTOP_CTRL_M23Ax_RdFL(IOMUX_CTRL_VD0, pad_vd070);

		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd069,
				     reg_pad_eb_addr15_mux_sel, 0); //0:sc_vccen
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd069,
				     reg_pad_eb_cs0_mux_sel, 4); //4:o_sc_ext_clk
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd069,
				     reg_pad_eb_cs1_mux_sel, 1); //1:sc_data_i/o
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd070,
				     reg_pad_eb_cs2_mux_sel, 1); //1:sc_detect
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd070,
				     reg_pad_eb_cs3_mux_sel, 1); //1:sc_rst
		CTOP_CTRL_M23Ax_Wr01(IOMUX_CTRL_VD0, pad_vd070,
				     reg_pad_eb_wait_mux_sel, 0); //0:sc_vcc_sel

		CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_VD0, pad_vd069);
		CTOP_CTRL_M23Ax_WrFL(IOMUX_CTRL_VD0, pad_vd070);
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (chip == LX_CHIP_O22) {

		CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_CVI, pad_cvi69);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi69,
				     reg_pad_sc_clk_out_mux_sel, 3);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi69,
				     reg_pad_sc_data_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi69,
				     reg_pad_sc_detect_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi69,
				     reg_pad_sc_rst_mux_sel, 2);
		CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_CVI, pad_cvi69);

		CTOP_CTRL_O22Ax_RdFL(FUNC_IOMUX_CVI, pad_cvi70);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi70,
				     reg_pad_sc_vcc_sel_mux_sel, 2);
		CTOP_CTRL_O22Ax_Wr01(FUNC_IOMUX_CVI, pad_cvi70,
				     reg_pad_sc_vccen_mux_sel, 2);
		CTOP_CTRL_O22Ax_WrFL(FUNC_IOMUX_CVI, pad_cvi70);
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (chip == LX_CHIP_E60) {

		// TODO: CHECK
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_FMS, crg_fms014);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_FMS, crg_fms014,
				     reg_pad_sc_clk_out_mux_sel, 3); // 2:sc_clk_out, 3:sc_ext_clk
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_FMS, crg_fms014,
				     reg_pad_sc_data_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_FMS, crg_fms014,
				     reg_pad_sc_rst_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_FMS, crg_fms014,
				     reg_pad_sc_vcc_sel_mux_sel, 2);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_FMS, crg_fms014,
				     reg_pad_sc_vccen_mux_sel, 2);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_FMS, crg_fms014);
	}
#endif
	else {
		panic("Not supported chip!!![0x%x]\n", chip);
	}
}

/* to support 3 tuner */
void sci_ctop_external_inputmode(void)
{
	//u32 chip = lx_chip();

	if (0) {
	}
#ifdef INCLUDE_O18_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O18) {
		CTOP_CTRL_O18A0_RdFL(CTRL_TIV, crg_tiv06);
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv06, j3_tuner_clk_sel, 1);
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv06, j3_tuner_int_sel, 1);
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv06, j3_tuner_sop_sel, 1);
		CTOP_CTRL_O18A0_Wr01(CTRL_TIV, crg_tiv06, j3_tuner_data_sel, 1);
		CTOP_CTRL_O18A0_WrFL(CTRL_TIV, crg_tiv06);
	}
#endif
}

void sci_ctop_set_clock(void)
{
	u32 chip = lx_chip();

	log_noti("%s", __func__);

	if (0) {
	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (chip == LX_CHIP_O26) {
		CTOP_CTRL_O26Ax_RdFL(MIP_DIG_CTRL, bmc_syn_3);
		CTOP_CTRL_O26Ax_Wr01(MIP_DIG_CTRL, bmc_syn_3,
				     reg_f200_sel ,1); // 1:i_core200_clk_d50
		CTOP_CTRL_O26Ax_Wr01(MIP_DIG_CTRL, bmc_syn_3,
				     reg_f50_sel ,0); // 0: f50m_sc_ext
		CTOP_CTRL_O26Ax_Wr01(MIP_DIG_CTRL, bmc_syn_3,
				     reg_f27_18_sel ,0); // 0: f27m_sc_ext
		CTOP_CTRL_O26Ax_Wr01(MIP_DIG_CTRL, bmc_syn_3,
				     reg_sc_ext_sel ,0); // 0: df50m_sc = 0,	df27m_sc = 0, df18p432_sc = 0
		CTOP_CTRL_O26Ax_WrFL(MIP_DIG_CTRL, bmc_syn_3);

		clock = 4000;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (chip == LX_CHIP_O24) {
		CTOP_CTRL_O24Ax_RdFL(BND_CTRL_LNX0, bnd_lnx0_3);
		CTOP_CTRL_O24Ax_Wr01(BND_CTRL_LNX0, bnd_lnx0_3, reg_sc_ext_sel, 0);
		CTOP_CTRL_O24Ax_Wr01(BND_CTRL_LNX0, bnd_lnx0_3, reg_f27_18_sel, 0);
		CTOP_CTRL_O24Ax_Wr01(BND_CTRL_LNX0, bnd_lnx0_3, reg_f50_sel, 0);
		CTOP_CTRL_O24Ax_Wr01(BND_CTRL_LNX0, bnd_lnx0_3, reg_f200_sel, 1);
		CTOP_CTRL_O24Ax_WrFL(BND_CTRL_LNX0, bnd_lnx0_3);
		clock = 4000;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (chip == LX_CHIP_M23) {
		//TODO: check reg and clock value
		CTOP_CTRL_M23Ax_RdFL(BND_CTRL_BMC, bnd_bmc_3);
		CTOP_CTRL_M23Ax_Wr01(BND_CTRL_BMC, bnd_bmc_3,reg_sc_ext_sel, 0);
		CTOP_CTRL_M23Ax_Wr01(BND_CTRL_BMC, bnd_bmc_3,reg_f27_18_sel, 0);
		CTOP_CTRL_M23Ax_Wr01(BND_CTRL_BMC, bnd_bmc_3,reg_f50_sel, 0);
		CTOP_CTRL_M23Ax_Wr01(BND_CTRL_BMC, bnd_bmc_3,reg_f200_sel, 1);
		CTOP_CTRL_M23Ax_WrFL(BND_CTRL_BMC, bnd_bmc_3);
		clock = 4000;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (chip == LX_CHIP_O22) {
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_BMC, bnd_bmc_r33);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, bnd_bmc_r33,
				     reg_sc_ext_sel, 0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, bnd_bmc_r33,
				     reg_f27_18_sel, 0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, bnd_bmc_r33,
				     reg_f50_sel, 0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_BMC, bnd_bmc_r33,
				     reg_f200_sel, 1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_BMC, bnd_bmc_r33);
		clock = 4000;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (chip == LX_CHIP_E60) {
		// TODO: FIXME
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, dbb_syn_control1);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, dbb_syn_control1,
				     reg_sc_ext_sel, 0);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, dbb_syn_control1,
				     reg_f27_18_sel, 0);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, dbb_syn_control1,
				     reg_f50_sel, 0);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, dbb_syn_control1,
				     reg_f200_sel, 1);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, dbb_syn_control1);
		clock = 4000;
	}
#endif
	else {
		panic("Not supported chip!!![0x%x]\n", chip);
	}
}
