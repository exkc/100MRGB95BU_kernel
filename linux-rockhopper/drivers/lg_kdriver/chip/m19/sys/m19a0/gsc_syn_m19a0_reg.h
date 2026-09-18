#ifndef _GSC_SYN_M19A0_REG_H_
#define _GSC_SYN_M19A0_REG_H_

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
    0xC930_7000    crg_gsc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    disp_h3d_le_clk_gate_en   :  1,    //      2
    disp_clk_gate_en          :  1,    //      3
    det_clk_gate_en           :  1,    //      4
    vsd__axi_clk_gate_en      :  1,    //      5
    vsd__de_clk_gate_en       :  1,    //      6
    vsd__apb_clk_gate_en      :  1,    //      7
    gsc__axi_clk_gate_en      :  1,    //      8
    gsc__de_clk_gate_en       :  1,    //      9
    gsc__apb_clk_gate_en      :  1,    //     10
    vsd__apb_crc_clk_gate_en  :  1,    //     11
                              : 20;    //  31:12 reserved
}GSC_SYN_CRG_GSC00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7004    crg_gsc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    det_clk_sel               :  3,    //   6: 4
                              : 19,    //  25: 7 reserved
    disp594_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}GSC_SYN_CRG_GSC01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7008    crg_gsc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_axi_bnd_n        :  1,    //      0
    soft_rst_de_bnd_n         :  1,    //      1
                              :  1,    //      2 reserved
    soft_rst_disp_bnd_n       :  1,    //      3
                              :  1,    //      4 reserved
    soft_rst_disp_h3d_le_n    :  1,    //      5
    soft_rst_disp_n           :  1,    //      6
    soft_rst_det_n            :  1,    //      7
    vsd__soft_rst_axi_n       :  1,    //      8
    vsd__soft_rst_de_n        :  1,    //      9
    vsd__soft_rst_apb_n       :  1,    //     10
    gsc__soft_rst_axi_n       :  1,    //     11
    gsc__soft_rst_de_n        :  1,    //     12
    gsc__soft_rst_apb_n       :  1,    //     13
    soft_rst_apb_crc_n        :  1,    //     14
                              : 17;    //  31:15 reserved
}GSC_SYN_CRG_GSC02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_700C    syn_gsc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vsd_h3d_detour_swap       :  1,    //      0
    vsd_h3d_detour_en         :  1,    //      1
    vsd_shp_detour_en         :  1,    //      2
                              : 29;    //   31:3 reserved
}GSC_SYN_SYN_GSC02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7010    syn_gsc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_gsc_ctrl          : 32;    //  31: 0
}GSC_SYN_SYN_GSC03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7014    syn_gsc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_vsd_ctrl          : 32;    //  31: 0
}GSC_SYN_SYN_GSC04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7018    syn_gsc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gbm_vsd_motion_gain :  1,    //      0
    swrst_fmc_gsc_yy          :  1,    //      1
    swrst_fmc_gsc_cc          :  1,    //      2
                              : 29;    //   31:3 reserved
}GSC_SYN_SYN_GSC05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_701C    a_crg_check_gsc_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_clk0_value            : 16,    //  15: 0
    gsc_rst0_check            :  1,    //     16
    gsc_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gsc_clk0_off_value        :  8,    //  27:20
    gsc_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gsc_clk0_gate             :  1;    //     31
}GSC_SYN_A_CRG_CHECK_GSC_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7020    a_crg_check_gsc_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_clk1_value            : 16,    //  15: 0
    gsc_rst1_check            :  1,    //     16
    gsc_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gsc_clk1_off_value        :  8,    //  27:20
    gsc_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gsc_clk1_gate             :  1;    //     31
}GSC_SYN_A_CRG_CHECK_GSC_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7024    a_crg_check_gsc_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_clk2_value            : 16,    //  15: 0
    gsc_rst2_check            :  1,    //     16
    gsc_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gsc_clk2_off_value        :  8,    //  27:20
    gsc_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gsc_clk2_gate             :  1;    //     31
}GSC_SYN_A_CRG_CHECK_GSC_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7028    a_crg_check_gsc_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_clk3_value            : 16,    //  15: 0
    gsc_rst3_check            :  1,    //     16
    gsc_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gsc_clk3_off_value        :  8,    //  27:20
    gsc_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gsc_clk3_gate             :  1;    //     31
}GSC_SYN_A_CRG_CHECK_GSC_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_702C    a_crg_check_gsc_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_clk4_value            : 16,    //  15: 0
    gsc_rst4_check            :  1,    //     16
    gsc_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gsc_clk4_off_value        :  8,    //  27:20
    gsc_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gsc_clk4_gate             :  1;    //     31
}GSC_SYN_A_CRG_CHECK_GSC_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7030    syn_gsc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}GSC_SYN_SYN_GSC06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7034    syn_gsc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}GSC_SYN_SYN_GSC07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_7038    syn_gsc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_gsc        :  1,    //      0
    reg_ls_disable_vsd        :  1,    //      1
                              : 30;    //   31:2 reserved
}GSC_SYN_SYN_GSC08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    gsc_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
GSC_SYN_CRG_GSC00_M19A0_T                    crg_gsc00                ;         // 0xC930_7000
GSC_SYN_CRG_GSC01_M19A0_T                    crg_gsc01                ;         // 0xC930_7004
GSC_SYN_CRG_GSC02_M19A0_T                    crg_gsc02                ;         // 0xC930_7008
GSC_SYN_SYN_GSC02_M19A0_T                    syn_gsc02                ;         // 0xC930_700C
GSC_SYN_SYN_GSC03_M19A0_T                    syn_gsc03                ;         // 0xC930_7010
GSC_SYN_SYN_GSC04_M19A0_T                    syn_gsc04                ;         // 0xC930_7014
GSC_SYN_SYN_GSC05_M19A0_T                    syn_gsc05                ;         // 0xC930_7018
GSC_SYN_A_CRG_CHECK_GSC_0_M19A0_T            a_crg_check_gsc_0        ;         // 0xC930_701C
GSC_SYN_A_CRG_CHECK_GSC_1_M19A0_T            a_crg_check_gsc_1        ;         // 0xC930_7020
GSC_SYN_A_CRG_CHECK_GSC_2_M19A0_T            a_crg_check_gsc_2        ;         // 0xC930_7024
GSC_SYN_A_CRG_CHECK_GSC_3_M19A0_T            a_crg_check_gsc_3        ;         // 0xC930_7028
GSC_SYN_A_CRG_CHECK_GSC_4_M19A0_T            a_crg_check_gsc_4        ;         // 0xC930_702C
GSC_SYN_SYN_GSC06_M19A0_T                    syn_gsc06                ;         // 0xC930_7030
GSC_SYN_SYN_GSC07_M19A0_T                    syn_gsc07                ;         // 0xC930_7034
GSC_SYN_SYN_GSC08_M19A0_T                    syn_gsc08                ;         // 0xC930_7038
} GSC_SYN_REG_M19A0_T;
/* 15 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _GSC_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

