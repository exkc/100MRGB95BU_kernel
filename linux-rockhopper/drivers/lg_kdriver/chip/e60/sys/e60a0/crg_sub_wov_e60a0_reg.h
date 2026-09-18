#ifndef _CRG_SUB_WOV_E60A0_REG_H_
#define _CRG_SUB_WOV_E60A0_REG_H_

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
    0xF301_1000    crg_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_micomclk_gate_en: 1,    //    0
    reg_wov__wov_axiclk_gate_en: 1,    //      1
    reg_wov__wov_pdmclk_gate_en: 1,    //      2
    reg_wov__wov_dspclk_gate_en: 1,    //      3
    reg_wov__aud_micom_clk_gate_en: 1,    //   4
    reg_wov__aud_apb_clk_gate_en: 1,    //     5
    reg_wov__aud_teclk_gate_en:  1,    //      6
    reg_wov__aud_aad_clk_gate_en: 1,    //     7
    reg_wov__aud_spdif_clk_gate_en: 1,    //   8
    reg_wov__aud_hdp_clk_gate_en: 1,    //     9
    reg_wov__aud_hmr2spdifclk_gate_en: 1,    //  10
    reg_wov__aud_hmr4spdifclk_gate_en: 1,    //  11
    reg_wov__micom_cm0p_clk_gate_en: 1,    //  12
    reg_wov__micom_bus_clk_gate_en: 1,    //  13
    reg_wov__micom_peri_clk_gate_en: 1,    //  14
    reg_wov__micom_rtc_ir_clk_gate_en: 1,    //  15
    reg_wov__axi_3x3_sbus_clk_gate_en: 1,    //  16
    reg_wov__axi_soc600_clk_gate_en: 1,    //  17
    reg_wov__aud_clk_out_gate_en: 1,    //    18
    reg_wov__wov_ahbclk_gate_en: 1,    //     19
    reg_wov__aud_aclk_gate_en :  1,    //     20
    reg_wov__aud_dsp_clk_gate_en: 1,    //    21
    reg_wov__aud_arc_clk_gate_en: 1,    //    22
    reg_wov__aud_hmr3spdifclk_gate_en: 1,    //  23
    reg_wov__micom_sadc_clk_gate_en: 1,    //  24
    reg_wov__axi_600_clk_gate_en: 1,    //    25
    reg_wov__aud_main_clk_gate_en: 1,    //   26
    reg_wov__axi_soc_clk_gate_en: 1,    //    27
    reg_wov__aud_hmr1spdifclk_gate_en: 1,    //  28
    reg_wov__micom_bus_soc_clk_gate_en: 1,    //  29
                              :  2;    //  31:30 reserved
}CRG_SUB_WOV_CRG_WOV00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1004    crg_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__soft_rst_wov_axi_n: 1,    //      0
    reg_wov__soft_rst_wov_pdm_n: 1,    //      1
    reg_wov__soft_rst_aud_micom_n: 1,    //    2
    reg_wov__soft_rst_aud_fs_n:  1,    //      3
    reg_wov__soft_rst_micom_bus_n: 1,    //    4
    reg_wov__soft_rst_micom_rtc_ir_n: 1,    //  5
    reg_wov__soft_aud_hwreset_bnd_adpt_n: 1,    //  6
    reg_wov__soft_rst_wov_dsp_n: 1,    //      7
    reg_wov__soft_rst_wov_axi_bnd_adpt_n: 1,    //  8
    reg_wov__soft_rst_aud_hw_adpt_n: 1,    //  9
    reg_wov__soft_rst_aud_te_hw_n: 1,    //   10
    reg_wov__soft_rst_apb_bnd_adpt_p1_n: 1,    //  11
    reg_wov__soft_rst_apb_bnd_adpt_a79_n: 1,    //  12
    reg_wov__soft_rst_axi_bnd_adpt_a85_n: 1,    //  13
    reg_wov__soft_rst_axi_bnd600_adpt_a2_n: 1,    //  14
    reg_wov__soft_rst_aud_te_hw_adpt_d5_n: 1,    //  15
    reg_wov__soft_rst_aud_apb_bnd_adpt_d1_n: 1,    //  16
    reg_wov__soft_rst_axi_soc_adpt_a122_n: 1,    //  17
    reg_wov__soft_rst_axi_soc_adpt_a34_n: 1,    //  18
    reg_wov__soft_rst_apb_bnd_p0_n: 1,    //  19
    reg_wov__soft_rst_axi_soc600_n: 1,    //  20
    reg_wov__soft_rst_axi_soc_a34_n: 1,    //  21
    reg_wov__soft_rst_axi_soc_a122_n: 1,    //  22
    reg_wov__soft_rst_wov_micom_n: 1,    //   23
    reg_wov__soft_rst_aud_hw_n:  1,    //     24
    reg_wov__soft_rst_micom_peri_n: 1,    //  25
    reg_wov__soft_rst_axi_3x3_sbus_n: 1,    //  26
    reg_wov__soft_rst_micom_bus_soc_n: 1,    //  27
    reg_wov__soft_rst_apb_bnd_adpt_p0_n: 1,    //  28
    reg_wov__soft_rst_axi_bnd_adpt_a84_n: 1,    //  29
    reg_wov__soft_rst_aud_te_hw_adpt_d4_n: 1,    //  30
    reg_wov__soft_rst_axi_soc_adpt_a121_n: 1;    //  31
}CRG_SUB_WOV_CRG_WOV01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1008    crg_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__soft_rst_apb_bnd_n: 1,    //      0
    reg_wov__soft_rst_axi_soc600_a35_n: 1,    //  1
    reg_wov__soft_rst_axi_soc_a123_n: 1,    //  2
    reg_wov__soft_rst_wov_ahb_n: 1,    //      3
    reg_wov__soft_rst_aud_apb_n: 1,    //      4
    reg_wov__soft_rst_wov_axi_adpt_n: 1,    //  5
    reg_wov__soft_rst_axi_bnd600_adpt_a120_n: 1,    //  6
    reg_wov__soft_rst_axi_soc_adpt_a123_n: 1,    //  7
    reg_wov__soft_rst_axi_soc_a121_n: 1,    //  8
    reg_wov__soft_rst_micom_cm0p_n: 1,    //   9
    reg_wov__soft_rst_apb_bnd_adpt_a78_n: 1,    //  10
    reg_wov__soft_rst_apb_bnd_p1_n: 1,    //  11
    reg_wov__soft_rst_axi_bnd600_n: 1,    //  12
    reg_wov__soft_rst_aud_apb_bnd_adpt_d0_n: 1,    //  13
                              : 18;    //  31:14 reserved
}CRG_SUB_WOV_CRG_WOV02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_100C    crg_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__i_aud_hmr1spdifclk_inv_sel: 1,    //  0
    reg_wov__i_aud_hmr3spdifclk_inv_sel: 1,    //  1
    reg_wov__i_earc_frpll_clk_inv_sel: 1,    //  2
    reg_wov__i_apll_f_clk_inv_sel: 1,    //    3
    reg_wov__i_aud_hmr2spdifclk_inv_sel: 1,    //  4
    reg_wov__i_sdec_f_clk_inv_sel: 1,    //    5
    reg_wov__i_aud_hmr4spdifclk_inv_sel: 1,    //  6
    reg_wov__i_fs00_clk_inv_sel: 1,    //      7
                              : 24;    //   31:8 reserved
}CRG_SUB_WOV_CRG_WOV03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1010    crg_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__pdm_clk_sel      :  2,    //   1: 0
    reg_wov__wov_micomclk_sel :  1,    //      2
    reg_wov__wov_dspclk_sel   :  2,    //   4: 3
    reg_wov__aud_teclk_sel    :  1,    //      5
    reg_wov__micom_bus_clk_sel:  2,    //   7: 6
    reg_wov__pdm_div_sel      :  3,    //  10: 8
    reg_wov__wov_axiclk_sel   :  1,    //     11
    reg_wov__micom_cm0p_clk_sel: 2,    //  13:12
    reg_wov__aud_micom_clk_sel:  1,    //     14
    reg_wov__micom_peri_clk_sel: 1,    //     15
                              : 16;    //  31:16 reserved
}CRG_SUB_WOV_CRG_WOV04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1014    crg_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_wov  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_WOV_CRG_WOV05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1018    crg_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopll_800_clk_ctrl_wov: 9,    //  8:0
                              : 23;    //   31:9 reserved
}CRG_SUB_WOV_CRG_WOV06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_101C    crg_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopll_600_clk_ctrl_wov: 9,    //  8:0
                              : 23;    //   31:9 reserved
}CRG_SUB_WOV_CRG_WOV07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1020    crg_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopll_480_clk_ctrl_wov: 9,    //  8:0
                              : 23;    //   31:9 reserved
}CRG_SUB_WOV_CRG_WOV08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1024    crg_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopll_400_clk_ctrl_wov: 9,    //  8:0
                              : 23;    //   31:9 reserved
}CRG_SUB_WOV_CRG_WOV09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1028    crg_wov10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_wov__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_wov__crg_clk_off_check:  1,    //     30
    reg_wov__crg_clk_gate     :  1;    //     31
}CRG_SUB_WOV_CRG_WOV10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_102C    crg_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__crg_clk_rst_sel  : 32;    //  31: 0
}CRG_SUB_WOV_CRG_WOV11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    crg_sub_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CRG_SUB_WOV_CRG_WOV00_E60_A0_T               crg_wov00                ;         // 0xF301_1000
CRG_SUB_WOV_CRG_WOV01_E60_A0_T               crg_wov01                ;         // 0xF301_1004
CRG_SUB_WOV_CRG_WOV02_E60_A0_T               crg_wov02                ;         // 0xF301_1008
CRG_SUB_WOV_CRG_WOV03_E60_A0_T               crg_wov03                ;         // 0xF301_100C
CRG_SUB_WOV_CRG_WOV04_E60_A0_T               crg_wov04                ;         // 0xF301_1010
CRG_SUB_WOV_CRG_WOV05_E60_A0_T               crg_wov05                ;         // 0xF301_1014
CRG_SUB_WOV_CRG_WOV06_E60_A0_T               crg_wov06                ;         // 0xF301_1018
CRG_SUB_WOV_CRG_WOV07_E60_A0_T               crg_wov07                ;         // 0xF301_101C
CRG_SUB_WOV_CRG_WOV08_E60_A0_T               crg_wov08                ;         // 0xF301_1020
CRG_SUB_WOV_CRG_WOV09_E60_A0_T               crg_wov09                ;         // 0xF301_1024
CRG_SUB_WOV_CRG_WOV10_E60_A0_T               crg_wov10                ;         // 0xF301_1028
CRG_SUB_WOV_CRG_WOV11_E60_A0_T               crg_wov11                ;         // 0xF301_102C
} CRG_SUB_WOV_REG_E60_A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_WOV_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_Register_Manual.xlsx'  2020.1.8  KST by LGSiCRDV V3.0B*/

