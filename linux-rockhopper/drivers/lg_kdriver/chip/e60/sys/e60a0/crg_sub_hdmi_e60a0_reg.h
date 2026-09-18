#ifndef _CRG_SUB_HDMI_E60A0_REG_H_
#define _CRG_SUB_HDMI_E60A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC332_0000    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__hdmirx_sapb_clk_gate_en: 1,    //  0
    reg_hdmi__hdmirx_comm_esm_clk_gate_en: 1,    //  1
    reg_hdmi__hdmirx_edid_clk_gate_en: 1,    //  2
    reg_hdmi__hdmirx_prt1_aud_clk_gate_en: 1,    //  3
    reg_hdmi__hdmirx_prt1_frl_clk_gate_en: 1,    //  4
    reg_hdmi__hdmirx_prt2_aud_clk_gate_en: 1,    //  5
    reg_hdmi__hdmirx_prt2_frl_clk_gate_en: 1,    //  6
    reg_hdmi__hdmirx_prt3_aud_clk_gate_en: 1,    //  7
    reg_hdmi__hdmirx_prt3_frl_clk_gate_en: 1,    //  8
    reg_hdmi__hdmirx_prt4_aud_clk_gate_en: 1,    //  9
    reg_hdmi__hdmirx_prt4_frl_clk_gate_en: 1,    //  10
    reg_hdmi__hdmirx_prt1_earc_aud_clk_gate_en: 1,    //  11
    reg_hdmi__aud_hdmi1_mclk_gate_en: 1,    //  12
    reg_hdmi__aud_hdmi3_mclk_gate_en: 1,    //  13
    reg_hdmi__phy_i2c_clk_gate_en: 1,    //   14
    reg_hdmi__mip_apb_clk_gate_en: 1,    //   15
    reg_hdmi__earc_extern_aud_clk_gate_en: 1,    //  16
    reg_hdmi__hdmirx_ref_clk_gate_en: 1,    //  17
    reg_hdmi__hdmirx_cr_para_clk_gate_en: 1,    //  18
    reg_hdmi__hdmirx_prt1_tmdsqp_clk_gate_en: 1,    //  19
    reg_hdmi__hdmirx_prt2_tmdsqp_clk_gate_en: 1,    //  20
    reg_hdmi__hdmirx_prt3_tmdsqp_clk_gate_en: 1,    //  21
    reg_hdmi__hdmirx_prt4_tmdsqp_clk_gate_en: 1,    //  22
    reg_hdmi__hdmirx_prt1_earc_bp_clk_gate_en: 1,    //  23
    reg_hdmi__aud_hdmi4_mclk_gate_en: 1,    //  24
    reg_hdmi__phy_osc_clk_gate_en: 1,    //   25
    reg_hdmi__de_soc_clk_gate_en: 1,    //    26
    reg_hdmi__hdmirx_prt1_link_clk_gate_en: 1,    //  27
    reg_hdmi__hdmirx_prt2_link_clk_gate_en: 1,    //  28
    reg_hdmi__hdmirx_prt3_link_clk_gate_en: 1,    //  29
    reg_hdmi__hdmirx_prt4_link_clk_gate_en: 1,    //  30
    reg_hdmi__aud_hdmi2_mclk_gate_en: 1;    //  31
}CRG_SUB_HDMI_CRG_HDMI00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0004    crg_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__soft_reset_acrn_phy1: 1,    //   0
    reg_hdmi__soft_reset_acrn_phy2: 1,    //   1
    reg_hdmi__soft_reset_acrn_phy3: 1,    //   2
    reg_hdmi__soft_reset_acrn_phy4: 1,    //   3
    reg_hdmi__soft_rst_hdmirx_esm_n: 1,    //  4
    reg_hdmi__soft_rst_hdmirx_prt1_aud_n: 1,    //  5
    reg_hdmi__soft_rst_hdmirx_prt1_frl_n: 1,    //  6
    reg_hdmi__soft_rst_hdmirx_prt1_main_n: 1,    //  7
    reg_hdmi__soft_rst_hdmirx_prt1_sapb_hdmi_n: 1,    //  8
    reg_hdmi__soft_rst_hdmirx_prt1_edid_n: 1,    //  9
    reg_hdmi__soft_rst_hdmirx_prt2_tmdsqp_n: 1,    //  10
    reg_hdmi__soft_rst_hdmirx_prt2_link_n: 1,    //  11
    reg_hdmi__soft_rst_hdmirx_prt2_sapb_n: 1,    //  12
    reg_hdmi__soft_rst_hdmirx_prt2_sapb_top_n: 1,    //  13
    reg_hdmi__soft_rst_hdmirx_prt3_aud_n: 1,    //  14
    reg_hdmi__soft_rst_hdmirx_prt3_frl_n: 1,    //  15
    reg_hdmi__soft_rst_hdmirx_prt3_main_n: 1,    //  16
    reg_hdmi__soft_rst_hdmirx_prt3_sapb_hdmi_n: 1,    //  17
    reg_hdmi__soft_rst_hdmirx_prt3_edid_n: 1,    //  18
    reg_hdmi__soft_rst_hdmirx_prt4_tmdsqp_n: 1,    //  19
    reg_hdmi__soft_rst_hdmirx_prt4_link_n: 1,    //  20
    reg_hdmi__soft_rst_hdmirx_prt4_sapb_n: 1,    //  21
    reg_hdmi__soft_rst_hdmirx_prt4_sapb_top_n: 1,    //  22
    reg_hdmi__soft_rst_hdmirx_prt1_base_n: 1,    //  23
    reg_hdmi__soft_rst_hdmirx_prt3_base_n: 1,    //  24
    reg_hdmi__soft_rst_de_soc_n: 1,    //     25
    reg_hdmi__soft_rst_hdmirx_prt1_main_bnd_n: 1,    //  26
    reg_hdmi__soft_rst_hdmirx_prt3_main_bnd_n: 1,    //  27
    reg_hdmi__soft_rst_hdmirx_prt1_tmdsqp_v_n: 1,    //  28
    reg_hdmi__soft_rst_hdmirx_prt3_tmdsqp_v_n: 1,    //  29
    reg_hdmi__soft_rst_hdmirx_prt1_tmdsqp_p_n: 1,    //  30
    reg_hdmi__soft_rst_hdmirx_prt3_tmdsqp_p_n: 1;    //  31
}CRG_SUB_HDMI_CRG_HDMI01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0008    crg_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__soft_rst_hdmirx_prt1_frl_g_n: 1,    //  0
    reg_hdmi__soft_rst_hdmirx_prt3_frl_g_n: 1,    //  1
    reg_hdmi__soft_rst_hdmirx_sapb_n: 1,    //  2
    reg_hdmi__soft_rst_hdmirx_prt1_link_n: 1,    //  3
    reg_hdmi__soft_rst_hdmirx_prt1_sapb_top_n: 1,    //  4
    reg_hdmi__soft_rst_hdmirx_prt2_frl_n: 1,    //  5
    reg_hdmi__soft_rst_hdmirx_prt2_sapb_hdmi_n: 1,    //  6
    reg_hdmi__soft_rst_hdmirx_prt3_tmdsqp_n: 1,    //  7
    reg_hdmi__soft_rst_hdmirx_prt3_sapb_n: 1,    //  8
    reg_hdmi__soft_rst_hdmirx_prt4_aud_n: 1,    //  9
    reg_hdmi__soft_rst_hdmirx_prt4_main_n: 1,    //  10
    reg_hdmi__soft_rst_hdmirx_prt4_edid_n: 1,    //  11
    reg_hdmi__soft_rst_hdmirx_prt4_base_n: 1,    //  12
    reg_hdmi__soft_rst_hdmirx_prt2_main_bnd_n: 1,    //  13
    reg_hdmi__soft_rst_hdmirx_prt2_tmdsqp_v_n: 1,    //  14
    reg_hdmi__soft_rst_hdmirx_prt2_tmdsqp_p_n: 1,    //  15
    reg_hdmi__soft_rst_hdmirx_prt2_frl_g_n: 1,    //  16
    reg_hdmi__soft_rst_hdmirx_prt1_tmdsqp_n: 1,    //  17
    reg_hdmi__soft_rst_hdmirx_prt2_aud_n: 1,    //  18
    reg_hdmi__soft_rst_hdmirx_prt2_edid_n: 1,    //  19
    reg_hdmi__soft_rst_hdmirx_prt3_sapb_top_n: 1,    //  20
    reg_hdmi__soft_rst_hdmirx_prt4_sapb_hdmi_n: 1,    //  21
    reg_hdmi__soft_rst_hdmirx_esm_bnd_n: 1,    //  22
    reg_hdmi__soft_rst_hdmirx_prt4_tmdsqp_v_n: 1,    //  23
    reg_hdmi__soft_rst_hdmirx_prt4_frl_g_n: 1,    //  24
    reg_hdmi__soft_rst_hdmirx_prt1_sapb_n: 1,    //  25
    reg_hdmi__soft_rst_hdmirx_prt3_link_n: 1,    //  26
    reg_hdmi__soft_rst_hdmirx_prt2_base_n: 1,    //  27
    reg_hdmi__soft_rst_hdmirx_prt4_tmdsqp_p_n: 1,    //  28
    reg_hdmi__soft_rst_hdmirx_prt2_main_n: 1,    //  29
    reg_hdmi__soft_rst_hdmirx_prt4_main_bnd_n: 1,    //  30
    reg_hdmi__soft_rst_hdmirx_prt4_frl_n: 1;    //  31
}CRG_SUB_HDMI_CRG_HDMI02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_000C    crg_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__phy1_frl_clk_inv_sel: 1,    //   0
    reg_hdmi__phy3_frl_clk_inv_sel: 1,    //   1
    reg_hdmi__phy1_tmdsqp_clk_inv_sel: 1,    //  2
    reg_hdmi__phy3_tmdsqp_clk_inv_sel: 1,    //  3
    reg_hdmi__phy1_hdmi_link_clk_inv_sel: 1,    //  4
    reg_hdmi__phy3_hdmi_link_clk_inv_sel: 1,    //  5
    reg_hdmi__phy1_aud_ref_clk_inv_sel: 1,    //  6
    reg_hdmi__phy3_aud_ref_clk_inv_sel: 1,    //  7
    reg_hdmi__hdmir_earctx_bpclk_inv_sel: 1,    //  8
    reg_hdmi__i_frpll_earc_clk_inv_sel: 1,    //  9
    reg_hdmi__phy2_frl_clk_inv_sel: 1,    //  10
    reg_hdmi__phy2_tmdsqp_clk_inv_sel: 1,    //  11
    reg_hdmi__phy2_hdmi_link_clk_inv_sel: 1,    //  12
    reg_hdmi__phy2_aud_ref_clk_inv_sel: 1,    //  13
    reg_hdmi__hdmi_earctx_audclk_inv_sel: 1,    //  14
    reg_hdmi__phy4_frl_clk_inv_sel: 1,    //  15
    reg_hdmi__phy4_hdmi_link_clk_inv_sel: 1,    //  16
    reg_hdmi__phy4_tmdsqp_clk_inv_sel: 1,    //  17
    reg_hdmi__phy4_aud_ref_clk_inv_sel: 1,    //  18
                              : 13;    //  31:19 reserved
}CRG_SUB_HDMI_CRG_HDMI03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0010    crg_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__hdmirx_edid_clk_sel: 1,    //    0
    reg_hdmi__hdmirx_prt2_aud_clk_sel: 2,    //  2:1
    reg_hdmi__hdmirx_prt4_aud_clk_sel: 2,    //  4:3
    reg_hdmi__phy_i2c_clk_sel :  1,    //      5
    reg_hdmi__hdmirx_prt1_aud_clk_sel: 2,    //  7:6
    reg_hdmi__hdmirx_prt1_earc_aud_clk_sel: 3,    //  10:8
    reg_hdmi__hdmirx_prt3_aud_clk_sel: 2,    //  12:11
    reg_hdmi__earc_extern_aud_clk_sel: 3,    //  15:13
                              : 16;    //  31:16 reserved
}CRG_SUB_HDMI_CRG_HDMI04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0014    crg_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_hdmi :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_HDMI_CRG_HDMI05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0018    crg_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_hdmi :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_HDMI_CRG_HDMI06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_001C    crg_hdmi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_hdmi__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_hdmi__crg_clk_off_check: 1,    //     30
    reg_hdmi__crg_clk_gate    :  1;    //     31
}CRG_SUB_HDMI_CRG_HDMI07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC332_0020    crg_hdmi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__crg_clk_rst_sel : 32;    //  31: 0
}CRG_SUB_HDMI_CRG_HDMI08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    crg_sub_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CRG_SUB_HDMI_CRG_HDMI00_E60_A0_T             crg_hdmi00               ;         // 0xC332_0000
CRG_SUB_HDMI_CRG_HDMI01_E60_A0_T             crg_hdmi01               ;         // 0xC332_0004
CRG_SUB_HDMI_CRG_HDMI02_E60_A0_T             crg_hdmi02               ;         // 0xC332_0008
CRG_SUB_HDMI_CRG_HDMI03_E60_A0_T             crg_hdmi03               ;         // 0xC332_000C
CRG_SUB_HDMI_CRG_HDMI04_E60_A0_T             crg_hdmi04               ;         // 0xC332_0010
CRG_SUB_HDMI_CRG_HDMI05_E60_A0_T             crg_hdmi05               ;         // 0xC332_0014
CRG_SUB_HDMI_CRG_HDMI06_E60_A0_T             crg_hdmi06               ;         // 0xC332_0018
CRG_SUB_HDMI_CRG_HDMI07_E60_A0_T             crg_hdmi07               ;         // 0xC332_001C
CRG_SUB_HDMI_CRG_HDMI08_E60_A0_T             crg_hdmi08               ;         // 0xC332_0020
} CRG_SUB_HDMI_REG_E60_A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_HDMI_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_Register_Manual.xlsx'  2020.1.9  KST by LGSiCRDV V3.0B*/

