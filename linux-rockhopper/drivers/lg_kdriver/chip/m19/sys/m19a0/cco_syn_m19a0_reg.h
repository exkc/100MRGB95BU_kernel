#ifndef _CCO_SYN_M19A0_REG_H_
#define _CCO_SYN_M19A0_REG_H_

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
    0xC930_8000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    axi_soc_clk_gate_en       :  1,    //      0
    disp_dsc_clk_gate_en      :  1,    //      1
    disp_clk_gate_en          :  1,    //      2
    sosd_clk_gate_en          :  1,    //      3
    det_clk_gate_en           :  1,    //      4
                              :  1,    //      5 reserved
    led_pxl_clk_gate_en       :  1,    //      6
    led_apb_clk_gate_en       :  1,    //      7
    fms_clk_gate_en           :  1,    //      8
    axi_clk_gate_en           :  1,    //      9
    de_clk_gate_en            :  1,    //     10
    apb_clk_gate_en           :  1,    //     11
    disp_osd_clk_gate_en      :  1,    //     12
                              : 19;    //  31:13 reserved
}CCO_SYN_CRG_CCO00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    disp_clk_sel              :  3,    //   2: 0
                              :  1,    //      3 reserved
    cco__sosd_clk_sel         :  3,    //   6: 4
                              :  1,    //      7 reserved
    led_pxl_clk_sel           :  3,    //  10: 8
                              :  1,    //     11 reserved
    led_fbc_clk_sel           :  3,    //  14:12
                              :  1,    //     15 reserved
    cco__disp_dsc_clk_sel     :  3,    //  18:16
                              :  1,    //     19 reserved
    disp_osd_clk_sel          :  3,    //  22:20
                              :  3,    //  25:23 reserved
    disp594_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}CCO_SYN_CRG_CCO01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_led_pxl_bnd_n    :  1,    //      0
    soft_rst_fms_bnd_n        :  1,    //      1
    soft_rst_de_bnd_n         :  1,    //      2
    soft_rst_sosd_bnd_n       :  1,    //      3
    soft_rst_disp_bnd_n       :  1,    //      4
    soft_rst_axi_bnd_n        :  1,    //      5
    soft_rst_axi_soc_n        :  1,    //      6
    soft_rst_disp_dsc_n       :  1,    //      7
    soft_rst_disp_n           :  1,    //      8
    soft_rst_sosd_n           :  1,    //      9
    soft_rst_det_n            :  1,    //     10
                              :  1,    //     11 reserved
    soft_rst_led_pxl_n        :  1,    //     12
    soft_rst_led_apb_n        :  1,    //     13
    soft_rst_fms_n            :  1,    //     14
    soft_rst_axi_n            :  1,    //     15
    soft_rst_de_n             :  1,    //     16
    soft_rst_apb_n            :  1,    //     17
    soft_rst_disp_osd_n       :  1,    //     18
                              : 13;    //  31:19 reserved
}CCO_SYN_CRG_CCO02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_800C    syn_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}CCO_SYN_SYN_CCO00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8010    syn_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}CCO_SYN_SYN_CCO01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8014    syn_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cco_ctrl          : 32;    //  31: 0
}CCO_SYN_SYN_CCO02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8018    syn_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_led_ctrl          : 32;    //  31: 0
}CCO_SYN_SYN_CCO03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_801C    a_crg_check_cco_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cco_clk0_value            : 16,    //  15: 0
    cco_rst0_check            :  1,    //     16
    cco_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cco_clk0_off_value        :  8,    //  27:20
    cco_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cco_clk0_gate             :  1;    //     31
}CCO_SYN_A_CRG_CHECK_CCO_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8020    a_crg_check_cco_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cco_clk1_value            : 16,    //  15: 0
    cco_rst1_check            :  1,    //     16
    cco_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cco_clk1_off_value        :  8,    //  27:20
    cco_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cco_clk1_gate             :  1;    //     31
}CCO_SYN_A_CRG_CHECK_CCO_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8024    a_crg_check_cco_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cco_clk2_value            : 16,    //  15: 0
    cco_rst2_check            :  1,    //     16
    cco_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cco_clk2_off_value        :  8,    //  27:20
    cco_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cco_clk2_gate             :  1;    //     31
}CCO_SYN_A_CRG_CHECK_CCO_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8028    a_crg_check_cco_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cco_clk3_value            : 16,    //  15: 0
    cco_rst3_check            :  1,    //     16
    cco_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cco_clk3_off_value        :  8,    //  27:20
    cco_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cco_clk3_gate             :  1;    //     31
}CCO_SYN_A_CRG_CHECK_CCO_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_802C    a_crg_check_cco_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cco_clk4_value            : 16,    //  15: 0
    cco_rst4_check            :  1,    //     16
    cco_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cco_clk4_off_value        :  8,    //  27:20
    cco_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cco_clk4_gate             :  1;    //     31
}CCO_SYN_A_CRG_CHECK_CCO_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8030    syn_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    logo_swrst                :  1,    //      0
    gsc_cco_vid_swrst         :  1,    //      1
                              :  2,    //   3: 2 reserved
    cpu_cco_detour_en         :  1,    //      4
                              : 27;    //   31:5 reserved
}CCO_SYN_SYN_CCO04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8034    syn_cco05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_cco        :  1,    //      0
    reg_ls_disable_led        :  1,    //      1
                              : 30;    //   31:2 reserved
}CCO_SYN_SYN_CCO05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    cco_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CCO_SYN_CRG_CCO00_M19A0_T                    crg_cco00                ;         // 0xC930_8000
CCO_SYN_CRG_CCO01_M19A0_T                    crg_cco01                ;         // 0xC930_8004
CCO_SYN_CRG_CCO02_M19A0_T                    crg_cco02                ;         // 0xC930_8008
CCO_SYN_SYN_CCO00_M19A0_T                    syn_cco00                ;         // 0xC930_800C
CCO_SYN_SYN_CCO01_M19A0_T                    syn_cco01                ;         // 0xC930_8010
CCO_SYN_SYN_CCO02_M19A0_T                    syn_cco02                ;         // 0xC930_8014
CCO_SYN_SYN_CCO03_M19A0_T                    syn_cco03                ;         // 0xC930_8018
CCO_SYN_A_CRG_CHECK_CCO_0_M19A0_T            a_crg_check_cco_0        ;         // 0xC930_801C
CCO_SYN_A_CRG_CHECK_CCO_1_M19A0_T            a_crg_check_cco_1        ;         // 0xC930_8020
CCO_SYN_A_CRG_CHECK_CCO_2_M19A0_T            a_crg_check_cco_2        ;         // 0xC930_8024
CCO_SYN_A_CRG_CHECK_CCO_3_M19A0_T            a_crg_check_cco_3        ;         // 0xC930_8028
CCO_SYN_A_CRG_CHECK_CCO_4_M19A0_T            a_crg_check_cco_4        ;         // 0xC930_802C
CCO_SYN_SYN_CCO04_M19A0_T                    syn_cco04                ;         // 0xC930_8030
CCO_SYN_SYN_CCO05_M19A0_T                    syn_cco05                ;         // 0xC930_8034
} CCO_SYN_REG_M19A0_T;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CCO_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

