#ifndef _GSC_SYN_O20A0_REG_H_
#define _GSC_SYN_O20A0_REG_H_

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
    0xC930_D000    crg_gsc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc__apb_clk_gate_en  :  1,    //      0
    reg_gsc__axi_clk_gate_en  :  1,    //      1
    reg_gsc__apb_bnd_clk_gate_en: 1,    //     2
    reg_gsc__de_clk_gate_en   :  1,    //      3
    reg_gsc__axi_soc_clk_gate_en: 1,    //     4
    reg_gsc__de_soc_clk_gate_en: 1,    //      5
                              : 26;    //   31:6 reserved
}GSC_SYN_CRG_GSC00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D004    crg_gsc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc__soft_rst_apb_n   :  1,    //      0
    reg_gsc__soft_rst_axi_n   :  1,    //      1
    reg_gsc__soft_rst_apb_bnd_n: 1,    //      2
    reg_gsc__soft_rst_axi_bnd_n: 1,    //      3
    reg_gsc__soft_rst_de_n    :  1,    //      4
    reg_gsc__soft_rst_de_bnd_n:  1,    //      5
    reg_gsc__soft_rst_de_soc_n:  1,    //      6
    reg_gsc__soft_rst_axi_soc_n: 1,    //      7
                              : 24;    //   31:8 reserved
}GSC_SYN_CRG_GSC01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D008    crg_gsc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_gsc__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_gsc__crg_clk_off_check:  1,    //     30
    reg_gsc__crg_clk_gate     :  1;    //     31
}GSC_SYN_CRG_GSC02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D00C    crg_gsc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc__crg_clk_rst_sel  : 32;    //  31: 0
}GSC_SYN_CRG_GSC03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D010    crg_vsd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__apb_clk_gate_en  :  1,    //      0
    reg_vsd__axi_clk_gate_en  :  1,    //      1
    reg_vsd__det_clk_gate_en  :  1,    //      2
    reg_vsd__sosd_clk_gate_en :  1,    //      3
    reg_vsd__de_clk_gate_en   :  1,    //      4
    reg_vsd__disp_clk_gate_en :  1,    //      5
                              : 26;    //   31:6 reserved
}GSC_SYN_CRG_VSD04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D014    crg_vsd05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__soft_rst_apb_n   :  1,    //      0
    reg_vsd__soft_rst_axi_n   :  1,    //      1
    reg_vsd__soft_rst_disp_n  :  1,    //      2
    reg_vsd__soft_rst_disp_bnd_n: 1,    //     3
    reg_vsd__soft_rst_de_n    :  1,    //      4
    reg_vsd__soft_rst_sosd_n  :  1,    //      5
    reg_vsd__soft_rst_det_n   :  1,    //      6
    reg_vsd__soft_rst_sosd_bnd_n: 1,    //     7
                              : 24;    //   31:8 reserved
}GSC_SYN_CRG_VSD05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D018    crg_vsd06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__disp_clk_sel     :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}GSC_SYN_CRG_VSD06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D01C    crg_vsd07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__sosd_clk_sel     :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}GSC_SYN_CRG_VSD07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D020    crg_vsd08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_vsd__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_vsd__crg_clk_off_check:  1,    //     30
    reg_vsd__crg_clk_gate     :  1;    //     31
}GSC_SYN_CRG_VSD08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D024    crg_vsd09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd__crg_clk_rst_sel  : 32;    //  31: 0
}GSC_SYN_CRG_VSD09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D028    bnd_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_cco_vsd_sync_mon: 1,    //      0
    reg__swrst_me0_vsd_motion_gain: 1,    //   1
    reg__swrst_fmc_gsc_c      :  1,    //      2
    reg__swrst_fmc_gsc_y      :  1,    //      3
    reg_sync_gen_disable      :  1,    //      4
    reg_vsd_shp_detour_en     :  1,    //      5
                              : 26;    //   31:6 reserved
}GSC_SYN_BND_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D02C    pqe_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_gsc_ctrl          : 32;    //  31: 0
}GSC_SYN_PQE_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D030    pqe_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_vsd_ctrl          : 32;    //  31: 0
}GSC_SYN_PQE_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D034    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_gsc  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}GSC_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D038    crg_clk_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core600_clk_ctrl_vsd  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_vsd  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}GSC_SYN_CRG_CLK_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_D03C    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_vsd        :  1,    //      0
    reg_ls_disable_gsc        :  1,    //      1
                              : 30;    //   31:2 reserved
}GSC_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    gsc_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
GSC_SYN_CRG_GSC00_O20A0_T                    crg_gsc00                ;         // 0xC930_D000
GSC_SYN_CRG_GSC01_O20A0_T                    crg_gsc01                ;         // 0xC930_D004
GSC_SYN_CRG_GSC02_O20A0_T                    crg_gsc02                ;         // 0xC930_D008
GSC_SYN_CRG_GSC03_O20A0_T                    crg_gsc03                ;         // 0xC930_D00C
GSC_SYN_CRG_VSD04_O20A0_T                    crg_vsd04                ;         // 0xC930_D010
GSC_SYN_CRG_VSD05_O20A0_T                    crg_vsd05                ;         // 0xC930_D014
GSC_SYN_CRG_VSD06_O20A0_T                    crg_vsd06                ;         // 0xC930_D018
GSC_SYN_CRG_VSD07_O20A0_T                    crg_vsd07                ;         // 0xC930_D01C
GSC_SYN_CRG_VSD08_O20A0_T                    crg_vsd08                ;         // 0xC930_D020
GSC_SYN_CRG_VSD09_O20A0_T                    crg_vsd09                ;         // 0xC930_D024
GSC_SYN_BND_CTRL01_O20A0_T                   bnd_ctrl01               ;         // 0xC930_D028
GSC_SYN_PQE_CTRL01_O20A0_T                   pqe_ctrl01               ;         // 0xC930_D02C
GSC_SYN_PQE_CTRL02_O20A0_T                   pqe_ctrl02               ;         // 0xC930_D030
GSC_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC930_D034
GSC_SYN_CRG_CLK_CTRL02_O20A0_T               crg_clk_ctrl02           ;         // 0xC930_D038
GSC_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC930_D03C
} GSC_SYN_REG_O20A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _GSC_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

