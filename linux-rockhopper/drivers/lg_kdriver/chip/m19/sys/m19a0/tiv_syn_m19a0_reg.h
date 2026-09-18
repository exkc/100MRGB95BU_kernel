#ifndef _TIV_SYN_M19A0_REG_H_
#define _TIV_SYN_M19A0_REG_H_

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
    0xC9C6_0400    crg_te00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tiv_axi_clk_gate_en       :  1,    //      0
    jpeg_clk_gate_en          :  1,    //      1
    stpi0_clk_gate_en         :  1,    //      2
    tpi3_clk_gate_en          :  1,    //      3
    tpi2_clk_gate_en          :  1,    //      4
    tpi1_clk_gate_en          :  1,    //      5
    tpi0_clk_gate_en          :  1,    //      6
    gstcc_if_clk_gate_en      :  1,    //      7
    te_ciout_clk_gate_en      :  1,    //      8
    stpo_clk_gate_en          :  1,    //      9
    ch3_sclk_gate_en          :  1,    //     10
    ch2_sclk_gate_en          :  1,    //     11
    ch1_sclk_gate_en          :  1,    //     12
    ch0_sclk_gate_en          :  1,    //     13
    fixed_sclk_gate_en        :  1,    //     14
    temcu_clk_gate_en         :  1,    //     15
    te_clk_gate_en            :  1,    //     16
    axi_clk_gate_en           :  1,    //     17
    ti_axi_bnd_clk_gate_en    :  1,    //     18
                              : 13;    //  31:19 reserved
}TIV_SYN_CRG_TE00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0404    crg_te01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    te_ciout_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    te__stpo_clk_sel          :  3,    //   6: 4
                              :  1,    //      7 reserved
    te__ch3_sclk_sel          :  1,    //      8
    te__ch2_sclk_sel          :  1,    //      9
    te__ch1_sclk_sel          :  1,    //     10
    te__ch0_sclk_sel          :  1,    //     11
    stpi0_clk_sel             :  1,    //     12
    tpi3_clk_sel              :  1,    //     13
    tpi2_clk_sel              :  1,    //     14
    tpi1_clk_sel              :  1,    //     15
    tpi0_clk_sel              :  1,    //     16
                              : 11,    //  27:17 reserved
    core480_clk_sel           :  2,    //  29:28
    core396_clk_sel           :  2;    //  31:30
}TIV_SYN_CRG_TE01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0408    crg_te02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tpi_clk_gf_5_inv_sel      :  1,    //      0
    tpi_clk_gf_4_inv_sel      :  1,    //      1
    tpi_clk_gf_3_inv_sel      :  1,    //      2
    tpi_clk_gf_2_inv_sel      :  1,    //      3
    tpi_clk_gf_1_inv_sel      :  1,    //      4
    i_f27m_clk_inv_sel        :  1,    //      5
    i_sdco27_clk_inv_sel      :  1,    //      6
                              : 25;    //   31:7 reserved
}TIV_SYN_CRG_TE02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_040C    crg_te03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_ti_axi_bnd_n     :  1,    //      0
    soft_rst_te_axi_bnd_n     :  1,    //      1
    soft_rst_te_bnd_n         :  1,    //      2
    soft_rst_jpeg_n           :  1,    //      3
    soft_rst_gstcc_if_n       :  1,    //      4
    soft_rst_ciout_n          :  1,    //      5
    soft_rst_stpo_n           :  1,    //      6
    soft_rst_ch3_s_n          :  1,    //      7
    soft_rst_ch2_s_n          :  1,    //      8
    soft_rst_ch1_s_n          :  1,    //      9
    soft_rst_ch0_s_n          :  1,    //     10
    soft_rst_f_s_n            :  1,    //     11
    soft_rst_gstcc_bnd_n      :  1,    //     12
    soft_rst_temcu_n          :  1,    //     13
    soft_rst_axi_n            :  1,    //     14
    soft_rst_te_n             :  1,    //     15
    soft_rst_te_axi_n         :  1,    //     16
                              : 15;    //  31:17 reserved
}TIV_SYN_CRG_TE03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0410    syn_tiv00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}TIV_SYN_SYN_TIV00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0414    syn_tiv01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}TIV_SYN_SYN_TIV01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0418    a_crg_check_ti_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk0_value             : 16,    //  15: 0
    ti_rst0_check             :  1,    //     16
    ti_clk0_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk0_off_value         :  8,    //  27:20
    ti_clk0_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk0_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_041C    a_crg_check_ti_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk1_value             : 16,    //  15: 0
    ti_rst1_check             :  1,    //     16
    ti_clk1_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk1_off_value         :  8,    //  27:20
    ti_clk1_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk1_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0420    a_crg_check_ti_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk2_value             : 16,    //  15: 0
    ti_rst2_check             :  1,    //     16
    ti_clk2_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk2_off_value         :  8,    //  27:20
    ti_clk2_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk2_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0424    a_crg_check_ti_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk3_value             : 16,    //  15: 0
    ti_rst3_check             :  1,    //     16
    ti_clk3_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk3_off_value         :  8,    //  27:20
    ti_clk3_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk3_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0428    a_crg_check_ti_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk4_value             : 16,    //  15: 0
    ti_rst4_check             :  1,    //     16
    ti_clk4_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk4_off_value         :  8,    //  27:20
    ti_clk4_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk4_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_042C    a_crg_check_ti_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk5_value             : 16,    //  15: 0
    ti_rst5_check             :  1,    //     16
    ti_clk5_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk5_off_value         :  8,    //  27:20
    ti_clk5_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk5_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0430    a_crg_check_ti_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ti_clk6_value             : 16,    //  15: 0
    ti_rst6_check             :  1,    //     16
    ti_clk6_off_check         :  1,    //     17
                              :  2,    //  19:18 reserved
    ti_clk6_off_value         :  8,    //  27:20
    ti_clk6_sel               :  2,    //  29:28
                              :  1,    //     30 reserved
    ti_clk6_gate              :  1;    //     31
}TIV_SYN_A_CRG_CHECK_TI_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    tiv_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
TIV_SYN_CRG_TE00_M19A0_T                     crg_te00                 ;         // 0xC9C6_0400
TIV_SYN_CRG_TE01_M19A0_T                     crg_te01                 ;         // 0xC9C6_0404
TIV_SYN_CRG_TE02_M19A0_T                     crg_te02                 ;         // 0xC9C6_0408
TIV_SYN_CRG_TE03_M19A0_T                     crg_te03                 ;         // 0xC9C6_040C
TIV_SYN_SYN_TIV00_M19A0_T                    syn_tiv00                ;         // 0xC9C6_0410
TIV_SYN_SYN_TIV01_M19A0_T                    syn_tiv01                ;         // 0xC9C6_0414
TIV_SYN_A_CRG_CHECK_TI_0_M19A0_T             a_crg_check_ti_0         ;         // 0xC9C6_0418
TIV_SYN_A_CRG_CHECK_TI_1_M19A0_T             a_crg_check_ti_1         ;         // 0xC9C6_041C
TIV_SYN_A_CRG_CHECK_TI_2_M19A0_T             a_crg_check_ti_2         ;         // 0xC9C6_0420
TIV_SYN_A_CRG_CHECK_TI_3_M19A0_T             a_crg_check_ti_3         ;         // 0xC9C6_0424
TIV_SYN_A_CRG_CHECK_TI_4_M19A0_T             a_crg_check_ti_4         ;         // 0xC9C6_0428
TIV_SYN_A_CRG_CHECK_TI_5_M19A0_T             a_crg_check_ti_5         ;         // 0xC9C6_042C
TIV_SYN_A_CRG_CHECK_TI_6_M19A0_T             a_crg_check_ti_6         ;         // 0xC9C6_0430
} TIV_SYN_REG_M19A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _TIV_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

