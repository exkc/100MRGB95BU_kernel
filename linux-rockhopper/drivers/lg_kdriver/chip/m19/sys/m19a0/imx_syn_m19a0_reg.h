#ifndef _IMX_SYN_M19A0_REG_H_
#define _IMX_SYN_M19A0_REG_H_

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
    0xC930_3000    crg_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    hdrh_clk_gate_en          :  1,    //      1
    hdr_clk_gate_en           :  1,    //      2
    hdr_de_clk_gate_en        :  1,    //      3
    hdr_apb_clk_gate_en       :  1,    //      4
    vdo2_clk_gate_en          :  1,    //      5
    vdo1_clk_gate_en          :  1,    //      6
    vdo0_clk_gate_en          :  1,    //      7
    axi_clk_gate_en           :  1,    //      8
    de_clk_gate_en            :  1,    //      9
    apb_clk_gate_en           :  1,    //     10
    usb_axi_clk_gate_en       :  1,    //     11
                              : 20;    //  31:12 reserved
}IMX_SYN_CRG_IMX00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3004    crg_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdrh_clk_sel              :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    hdr_clk_sel               :  2,    //   5: 4
                              : 20,    //  25: 6 reserved
    disp594_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}IMX_SYN_CRG_IMX01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3008    crg_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    soft_rst_de_bnd_n         :  1,    //      1
    soft_rst_imx_axi_bnd_n    :  1,    //      2
    soft_rst_hdrh_n           :  1,    //      3
    soft_rst_hdr_n            :  1,    //      4
    soft_rst_hdr_de_n         :  1,    //      5
    soft_rst_hdr_apb_n        :  1,    //      6
    soft_rst_vdo2_n           :  1,    //      7
    soft_rst_vdo1_n           :  1,    //      8
    soft_rst_vdo0_n           :  1,    //      9
    soft_rst_axi_sub_n        :  1,    //     10
    soft_rst_axi_n            :  1,    //     11
    soft_rst_de_n             :  1,    //     12
    soft_rst_apb_n            :  1,    //     13
    soft_rst_usb_axi_n        :  1,    //     14
    soft_rst_usb_axi_bnd_n    :  1,    //     15
                              : 16;    //  31:16 reserved
}IMX_SYN_CRG_IMX02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_300C    syn_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}IMX_SYN_SYN_IMX00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3010    syn_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}IMX_SYN_SYN_IMX01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3014    syn_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_imx_ctrl          : 32;    //  31: 0
}IMX_SYN_SYN_IMX02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3018    syn_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_hdr_ctrl          : 32;    //  31: 0
}IMX_SYN_SYN_IMX03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_301C    a_crg_check_imx_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk0_value            : 16,    //  15: 0
    imx_rst0_check            :  1,    //     16
    imx_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk0_off_value        :  8,    //  27:20
    imx_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk0_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3020    a_crg_check_imx_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk1_value            : 16,    //  15: 0
    imx_rst1_check            :  1,    //     16
    imx_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk1_off_value        :  8,    //  27:20
    imx_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk1_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3024    a_crg_check_imx_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk2_value            : 16,    //  15: 0
    imx_rst2_check            :  1,    //     16
    imx_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk2_off_value        :  8,    //  27:20
    imx_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk2_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3028    a_crg_check_imx_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk3_value            : 16,    //  15: 0
    imx_rst3_check            :  1,    //     16
    imx_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk3_off_value        :  8,    //  27:20
    imx_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk3_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_302C    a_crg_check_imx_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk4_value            : 16,    //  15: 0
    imx_rst4_check            :  1,    //     16
    imx_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk4_off_value        :  8,    //  27:20
    imx_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk4_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3030    a_crg_check_imx_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk5_value            : 16,    //  15: 0
    imx_rst5_check            :  1,    //     16
    imx_clk5_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk5_off_value        :  8,    //  27:20
    imx_clk5_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk5_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3034    a_crg_check_imx_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk6_value            : 16,    //  15: 0
    imx_rst6_check            :  1,    //     16
    imx_clk6_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk6_off_value        :  8,    //  27:20
    imx_clk6_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk6_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3038    a_crg_check_imx_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk7_value            : 16,    //  15: 0
    imx_rst7_check            :  1,    //     16
    imx_clk7_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk7_off_value        :  8,    //  27:20
    imx_clk7_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk7_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_7_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_303C    a_crg_check_imx_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk8_value            : 16,    //  15: 0
    imx_rst8_check            :  1,    //     16
    imx_clk8_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk8_off_value        :  8,    //  27:20
    imx_clk8_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk8_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_8_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3040    syn_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_imx        :  1,    //      0
    reg_ls_disable_hdr        :  1,    //      1
    reg_ls_disable_usb        :  1,    //      2
                              : 29;    //   31:3 reserved
}IMX_SYN_SYN_IMX04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3044    syn_imx05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_cvi_imx             :  1,    //      0
    swrst_msf0_c              :  1,    //      1
    swrst_msf0_y              :  1,    //      2
    swrst_msf1_c              :  1,    //      3
    swrst_msf1_y              :  1,    //      4
    swrst_cco_gcf             :  1,    //      5
                              : 26;    //   31:6 reserved
}IMX_SYN_SYN_IMX05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3048    a_crg_check_imx_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    imx_clk9_value            : 16,    //  15: 0
    imx_rst9_check            :  1,    //     16
    imx_clk9_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    imx_clk9_off_value        :  8,    //  27:20
    imx_clk9_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    imx_clk9_gate             :  1;    //     31
}IMX_SYN_A_CRG_CHECK_IMX_9_M19A0_T;

/*-----------------------------------------------------------------------------------------
    imx_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
IMX_SYN_CRG_IMX00_M19A0_T                    crg_imx00                ;         // 0xC930_3000
IMX_SYN_CRG_IMX01_M19A0_T                    crg_imx01                ;         // 0xC930_3004
IMX_SYN_CRG_IMX02_M19A0_T                    crg_imx02                ;         // 0xC930_3008
IMX_SYN_SYN_IMX00_M19A0_T                    syn_imx00                ;         // 0xC930_300C
IMX_SYN_SYN_IMX01_M19A0_T                    syn_imx01                ;         // 0xC930_3010
IMX_SYN_SYN_IMX02_M19A0_T                    syn_imx02                ;         // 0xC930_3014
IMX_SYN_SYN_IMX03_M19A0_T                    syn_imx03                ;         // 0xC930_3018
IMX_SYN_A_CRG_CHECK_IMX_0_M19A0_T            a_crg_check_imx_0        ;         // 0xC930_301C
IMX_SYN_A_CRG_CHECK_IMX_1_M19A0_T            a_crg_check_imx_1        ;         // 0xC930_3020
IMX_SYN_A_CRG_CHECK_IMX_2_M19A0_T            a_crg_check_imx_2        ;         // 0xC930_3024
IMX_SYN_A_CRG_CHECK_IMX_3_M19A0_T            a_crg_check_imx_3        ;         // 0xC930_3028
IMX_SYN_A_CRG_CHECK_IMX_4_M19A0_T            a_crg_check_imx_4        ;         // 0xC930_302C
IMX_SYN_A_CRG_CHECK_IMX_5_M19A0_T            a_crg_check_imx_5        ;         // 0xC930_3030
IMX_SYN_A_CRG_CHECK_IMX_6_M19A0_T            a_crg_check_imx_6        ;         // 0xC930_3034
IMX_SYN_A_CRG_CHECK_IMX_7_M19A0_T            a_crg_check_imx_7        ;         // 0xC930_3038
IMX_SYN_A_CRG_CHECK_IMX_8_M19A0_T            a_crg_check_imx_8        ;         // 0xC930_303C
IMX_SYN_SYN_IMX04_M19A0_T                    syn_imx04                ;         // 0xC930_3040
IMX_SYN_SYN_IMX05_M19A0_T                    syn_imx05                ;         // 0xC930_3044
IMX_SYN_A_CRG_CHECK_IMX_9_M19A0_T            a_crg_check_imx_9        ;         // 0xC930_3048
} IMX_SYN_REG_M19A0_T;
/* 19 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _IMX_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

