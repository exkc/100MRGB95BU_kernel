#ifndef _CCO_SYN_O20A0_REG_H_
#define _CCO_SYN_O20A0_REG_H_

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
    0xC930_C000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__apb_clk_gate_en  :  1,    //      0
    reg_cco__axi_clk_gate_en  :  1,    //      1
    reg_cco__det_clk_gate_en  :  1,    //      2
    reg_cco__disp_dsc_clk_gate_en: 1,    //    3
    reg_cco__disp_osd_clk_gate_en: 1,    //    4
    reg_cco__sosd_clk_gate_en :  1,    //      5
    reg_cco__axi_soc_clk_gate_en: 1,    //     6
    reg_cco__de_clk_gate_en   :  1,    //      7
    reg_cco__disp_clk_gate_en :  1,    //      8
    reg_cco__fms_clk_gate_en  :  1,    //      9
    reg_cco__de_soc_clk_gate_en: 1,    //     10
                              : 21;    //  31:11 reserved
}CCO_SYN_CRG_CCO00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__soft_rst_apb_n   :  1,    //      0
    reg_cco__soft_rst_axi_n   :  1,    //      1
    reg_cco__soft_rst_disp_n  :  1,    //      2
    reg_cco__soft_rst_disp_osd_n: 1,    //     3
    reg_cco__soft_rst_sosd_n  :  1,    //      4
    reg_cco__soft_rst_axi_bnd_n: 1,    //      5
    reg_cco__soft_rst_disp_dsc_bnd_n: 1,    //  6
    reg_cco__soft_rst_sosd_bnd_n: 1,    //     7
    reg_cco__soft_rst_apb_bnd_n: 1,    //      8
    reg_cco__soft_rst_de_n    :  1,    //      9
    reg_cco__soft_rst_disp_dsc_n: 1,    //    10
    reg_cco__soft_rst_de_soc_n:  1,    //     11
    reg_cco__soft_rst_disp_bnd_n: 1,    //    12
    reg_cco__soft_rst_fms_bnd_n: 1,    //     13
    reg_cco__soft_rst_det_n   :  1,    //     14
    reg_cco__soft_rst_axi_soc_n: 1,    //     15
    reg_cco__soft_rst_fms_n   :  1,    //     16
    reg_cco__soft_rst_de_bnd_n:  1,    //     17
                              : 14;    //  31:18 reserved
}CCO_SYN_CRG_CCO01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__disp_clk_sel     :  3,    //   2: 0
    reg_cco__disp_osd_clk_sel :  3,    //   5: 3
    reg_cco__disp_dsc_clk_sel :  3,    //   8: 6
                              : 23;    //   31:9 reserved
}CCO_SYN_CRG_CCO02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C00C    crg_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__sosd_clk_sel     :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}CCO_SYN_CRG_CCO03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_cco__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_cco__crg_clk_off_check:  1,    //     30
    reg_cco__crg_clk_gate     :  1;    //     31
}CCO_SYN_CRG_CCO04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C014    crg_cco05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco__crg_clk_rst_sel  : 32;    //  31: 0
}CCO_SYN_CRG_CCO05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C018    pqe_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cco_ctrl          : 32;    //  31: 0
}CCO_SYN_PQE_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C01C    pqe_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cco_ctrl1         : 32;    //  31: 0
}CCO_SYN_PQE_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C020    bnd_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_cco_detour_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CCO_SYN_BND_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C024    bnd_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_led_cco_sync_mon: 1,    //      0
    reg__swrst_fmc_cco_oled_logo: 1,    //     1
    reg__swrst_vsd_cco_vid    :  1,    //      2
                              : 29;    //   31:3 reserved
}CCO_SYN_BND_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C028    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CCO_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C02C    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}CCO_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C030    dsc_tcon_detour_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__cco_rgb_src_sel      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg__dsc_tcon_detour_enable: 1,    //      4
                              : 27;    //   31:5 reserved
}CCO_SYN_DSC_TCON_DETOUR_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C034    rgmii_rs ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rgmii_tx_rs_bypass    :  1,    //      0
    reg_rgmii_rx_rs_bypass    :  1,    //      1
                              : 30;    //   31:2 reserved
}CCO_SYN_RGMII_RS_O20B0_T;

/*-----------------------------------------------------------------------------------------
    cco_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CCO_SYN_CRG_CCO00_O20A0_T                    crg_cco00                ;         // 0xC930_C000
CCO_SYN_CRG_CCO01_O20A0_T                    crg_cco01                ;         // 0xC930_C004
CCO_SYN_CRG_CCO02_O20A0_T                    crg_cco02                ;         // 0xC930_C008
CCO_SYN_CRG_CCO03_O20A0_T                    crg_cco03                ;         // 0xC930_C00C
CCO_SYN_CRG_CCO04_O20A0_T                    crg_cco04                ;         // 0xC930_C010
CCO_SYN_CRG_CCO05_O20A0_T                    crg_cco05                ;         // 0xC930_C014
CCO_SYN_PQE_CTRL01_O20A0_T                   pqe_ctrl01               ;         // 0xC930_C018
CCO_SYN_PQE_CTRL02_O20A0_T                   pqe_ctrl02               ;         // 0xC930_C01C
CCO_SYN_BND_CTRL01_O20A0_T                   bnd_ctrl01               ;         // 0xC930_C020
CCO_SYN_BND_CTRL02_O20A0_T                   bnd_ctrl02               ;         // 0xC930_C024
CCO_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC930_C028
CCO_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC930_C02C
CCO_SYN_DSC_TCON_DETOUR_00_O20A0_T           dsc_tcon_detour_00       ;         // 0xC930_C030
CCO_SYN_RGMII_RS_O20B0_T                     rgmii_rs_B0              ;         // 0xC930_C034
} CCO_SYN_REG_O20A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CCO_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

