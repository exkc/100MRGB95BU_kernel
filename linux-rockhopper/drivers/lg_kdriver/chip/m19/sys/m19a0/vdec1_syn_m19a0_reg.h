#ifndef _VDEC1_SYN_M19A0_REG_H_
#define _VDEC1_SYN_M19A0_REG_H_

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
    0xC9C7_1200    crg_vdec100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    de_soc_clk_gate_en        :  1,    //      0
    gstcc_soc_clk_gate_en     :  1,    //      1
    vd_axi1_clk_gate_en       :  1,    //      2
    vd_axi0_clk_gate_en       :  1,    //      3
    vd_mem_clk_gate_en        :  1,    //      4
    g1clk_gate_en             :  1,    //      5
    hevcclk_gate_en           :  1,    //      6
    hevc_lcu_clk_gate_en      :  1,    //      7
    edclk_gate_en             :  1,    //      8
                              : 23;    //   31:9 reserved
}VDEC1_SYN_CRG_VDEC100_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1204    crg_vdec101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_mem_clk_sel            :  1,    //      0
                              : 25,    //  25: 1 reserved
    core528_clk_sel           :  2,    //  27:26
    core480_clk_sel           :  2,    //  29:28
    core396_clk_sel           :  2;    //  31:30
}VDEC1_SYN_CRG_VDEC101_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1208    crg_vdec102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_hevc_bnd_n       :  1,    //      0
    soft_rst_axi_bnd_n        :  1,    //      1
    soft_rst_gstcc_soc_n      :  1,    //      2
    soft_rst_de_soc_n         :  1,    //      3
    soft_rst_vd1_n            :  1,    //      4
    soft_rst_vd0_n            :  1,    //      5
    soft_rst_mem_n            :  1,    //      6
    soft_rst_g1_n             :  1,    //      7
    soft_rst_dec_n            :  1,    //      8
    soft_rst_hevc_n           :  1,    //      9
                              :  1,    //     10 reserved
    soft_rst_ed_n             :  1,    //     11
                              : 20;    //  31:12 reserved
}VDEC1_SYN_CRG_VDEC102_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_120C    syn_vdec100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_my_lf               :  1,    //      0
                              : 31;    //   31:1 reserved
}VDEC1_SYN_SYN_VDEC100_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1210    syn_vdec101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_your_lf             :  1,    //      0
                              : 31;    //   31:1 reserved
}VDEC1_SYN_SYN_VDEC101_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1214    a_crg_check_vdec1_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec1_clk0_value          : 16,    //  15: 0
    vdec1_rst0_check          :  1,    //     16
    vdec1_clk0_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec1_clk0_off_value      :  8,    //  27:20
    vdec1_clk0_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec1_clk0_gate           :  1;    //     31
}VDEC1_SYN_A_CRG_CHECK_VDEC1_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1218    a_crg_check_vdec1_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec1_clk1_value          : 16,    //  15: 0
    vdec1_rst1_check          :  1,    //     16
    vdec1_clk1_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec1_clk1_off_value      :  8,    //  27:20
    vdec1_clk1_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec1_clk1_gate           :  1;    //     31
}VDEC1_SYN_A_CRG_CHECK_VDEC1_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_121C    a_crg_check_vdec1_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec1_clk2_value          : 16,    //  15: 0
    vdec1_rst2_check          :  1,    //     16
    vdec1_clk2_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec1_clk2_off_value      :  8,    //  27:20
    vdec1_clk2_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec1_clk2_gate           :  1;    //     31
}VDEC1_SYN_A_CRG_CHECK_VDEC1_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1220    a_crg_check_vdec1_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec1_clk3_value          : 16,    //  15: 0
    vdec1_rst3_check          :  1,    //     16
    vdec1_clk3_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec1_clk3_off_value      :  8,    //  27:20
    vdec1_clk3_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec1_clk3_gate           :  1;    //     31
}VDEC1_SYN_A_CRG_CHECK_VDEC1_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1224    syn_vdec102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}VDEC1_SYN_SYN_VDEC102_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_1228    syn_vdec103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}VDEC1_SYN_SYN_VDEC103_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_122C    syn_vdec104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}VDEC1_SYN_SYN_VDEC104_M19A0_T;

/*-----------------------------------------------------------------------------------------
    vdec1_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
VDEC1_SYN_CRG_VDEC100_M19A0_T                crg_vdec100              ;         // 0xC9C7_1200
VDEC1_SYN_CRG_VDEC101_M19A0_T                crg_vdec101              ;         // 0xC9C7_1204
VDEC1_SYN_CRG_VDEC102_M19A0_T                crg_vdec102              ;         // 0xC9C7_1208
VDEC1_SYN_SYN_VDEC100_M19A0_T                syn_vdec100              ;         // 0xC9C7_120C
VDEC1_SYN_SYN_VDEC101_M19A0_T                syn_vdec101              ;         // 0xC9C7_1210
VDEC1_SYN_A_CRG_CHECK_VDEC1_0_M19A0_T        a_crg_check_vdec1_0      ;         // 0xC9C7_1214
VDEC1_SYN_A_CRG_CHECK_VDEC1_1_M19A0_T        a_crg_check_vdec1_1      ;         // 0xC9C7_1218
VDEC1_SYN_A_CRG_CHECK_VDEC1_2_M19A0_T        a_crg_check_vdec1_2      ;         // 0xC9C7_121C
VDEC1_SYN_A_CRG_CHECK_VDEC1_3_M19A0_T        a_crg_check_vdec1_3      ;         // 0xC9C7_1220
VDEC1_SYN_SYN_VDEC102_M19A0_T                syn_vdec102              ;         // 0xC9C7_1224
VDEC1_SYN_SYN_VDEC103_M19A0_T                syn_vdec103              ;         // 0xC9C7_1228
VDEC1_SYN_SYN_VDEC104_M19A0_T                syn_vdec104              ;         // 0xC9C7_122C
} VDEC1_SYN_REG_M19A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _VDEC1_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

