#ifndef _CRG_SUB_DBB_E60A0_REG_H_
#define _CRG_SUB_DBB_E60A0_REG_H_

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
    0xC30C_1000    crg_dbb_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__apb_clk_gate_en: 1,    //     0
    reg_dbb_syn__axi_clk_gate_en: 1,    //     1
                              : 30;    //   31:2 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1004    crg_dbb_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__swrst_auda_f256fs_clk1: 1,    //  0
    reg_dbb_syn__swrst_auda_f256fs_clk0: 1,    //  1
    reg_dbb_syn__swrst_aclk_mux_mip_dig: 1,    //  2
    reg_dbb_syn__swrst_adto3  :  1,    //      3
    reg_dbb_syn__swrst_adto2  :  1,    //      4
    reg_dbb_syn__swrst_adto1  :  1,    //      5
    reg_dbb_syn__swrst_auad   :  1,    //      6
    reg_dbb_syn__swrst_pix    :  1,    //      7
    reg_dbb_syn__swrst_f50m   :  1,    //      8
    reg_dbb_syn__swrst_axi    :  1,    //      9
    reg_dbb_syn__swrst_apb    :  1,    //     10
                              : 21;    //  31:11 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1008    crg_dbb_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__f64fs_clk_sel:  1,    //      0
    reg_dbb_syn__f1fs_clk_sel :  1,    //      1
                              : 30;    //   31:2 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_100C    crg_dbb_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__sel_inv_aud_fs00_clk: 1,    //  0
    reg_dbb_syn__sel_inv_mclk1:  1,    //      1
    reg_dbb_syn__sel_inv_mclk0:  1,    //      2
    reg_dbb_syn__sel_inv_f27m_clock: 1,    //  3
    reg_dbb_syn__sel_inv_aclk_mux_mip_dig: 1,    //  4
                              : 27;    //   31:5 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1010    crg_dbb_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto1_add_value: 32;    //  31:0
}CRG_SUB_DBB_CRG_DBB_SYN_04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1014    crg_dbb_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto1_err_value: 12,    //  11:0
                              : 20;    //  31:12 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_101C    crg_dbb_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto2_add_value: 32;    //  31:0
}CRG_SUB_DBB_CRG_DBB_SYN_06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1020    crg_dbb_syn_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto2_err_value: 12,    //  11:0
                              : 20;    //  31:12 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1024    crg_dbb_syn_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto3_add_value: 32;    //  31:0
}CRG_SUB_DBB_CRG_DBB_SYN_08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1028    crg_dbb_syn_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__adto3_err_value: 12,    //  11:0
                              : 20;    //  31:12 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_102C    crg_dbb_syn_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__aclk_mux_auda_clk1_div: 3,    //  2:0
                              :  1,    //      3 reserved
    reg_dbb_syn__aclk_mux_auda_clk1_src: 4,    //  7:4
    reg_dbb_syn__aclk_mux_auda_clk0_div: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_dbb_syn__aclk_mux_auda_clk0_src: 4,    //  15:12
    reg_dbb_syn__aclk_mux_mip_dig_div: 3,    //  18:16
                              :  1,    //     19 reserved
    reg_dbb_syn__aclk_mux_mip_dig_src: 4,    //  23:20
                              :  8;    //  31:24 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1030    crg_dbb_syn_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_syn__sync_update_adto3: 1,    //   0
    reg_dbb_syn__sync_update_adto2: 1,    //   1
    reg_dbb_syn__sync_update_adto1: 1,    //   2
                              : 29;    //   31:3 reserved
}CRG_SUB_DBB_CRG_DBB_SYN_11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CRG_SUB_DBB_CRG_DBB_SYN_00_E60_A0_T      crg_dbb_syn_00           ;         // 0xC30C_1000
    CRG_SUB_DBB_CRG_DBB_SYN_01_E60_A0_T      crg_dbb_syn_01           ;         // 0xC30C_1004
    CRG_SUB_DBB_CRG_DBB_SYN_02_E60_A0_T      crg_dbb_syn_02           ;         // 0xC30C_1008
    CRG_SUB_DBB_CRG_DBB_SYN_03_E60_A0_T      crg_dbb_syn_03           ;         // 0xC30C_100C
    CRG_SUB_DBB_CRG_DBB_SYN_04_E60_A0_T      crg_dbb_syn_04           ;         // 0xC30C_1010
    CRG_SUB_DBB_CRG_DBB_SYN_05_E60_A0_T      crg_dbb_syn_05           ;         // 0xC30C_1014
UINT32                                                 _rsvd_00[   1] ;         // 0xC30C_1018
    CRG_SUB_DBB_CRG_DBB_SYN_06_E60_A0_T      crg_dbb_syn_06           ;         // 0xC30C_101C
    CRG_SUB_DBB_CRG_DBB_SYN_07_E60_A0_T      crg_dbb_syn_07           ;         // 0xC30C_1020
    CRG_SUB_DBB_CRG_DBB_SYN_08_E60_A0_T      crg_dbb_syn_08           ;         // 0xC30C_1024
    CRG_SUB_DBB_CRG_DBB_SYN_09_E60_A0_T      crg_dbb_syn_09           ;         // 0xC30C_1028
    CRG_SUB_DBB_CRG_DBB_SYN_10_E60_A0_T      crg_dbb_syn_10           ;         // 0xC30C_102C
    CRG_SUB_DBB_CRG_DBB_SYN_11_E60_A0_T      crg_dbb_syn_11           ;         // 0xC30C_1030
} CRG_SUB_DBB_REG_E60_A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_DBB_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_DBB_SYN_Register_Manual_20190723.xlsx'  2019.12.13  KST by LGSiCRDV V3.0B*/

