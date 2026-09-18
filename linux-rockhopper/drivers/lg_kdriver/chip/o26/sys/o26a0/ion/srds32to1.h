#ifndef _SRDS32TO1_REG_H_
#define _SRDS32TO1_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0x1_7000    swrst ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_swrst_sipo0_fst       :  1,    //      6
    reg_swrst_sipo0_slo       :  1,    //      7
                              :  2,    //   9: 8 reserved
    reg_swrst_piso0_fst       :  1,    //     10
    reg_swrst_piso0_slo       :  1,    //     11
                              :  1,    //     12 reserved
    reg_swrst_dan0            :  1,    //     13
                              :  1,    //     14 reserved
    reg_swrst_dap0            :  1,    //     15
                              : 16;    //  31:16 reserved
}SRDS32TO1_SWRST_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7004    mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_sel_sipo0_sd_in       :  1,    //      4
                              :  7,    //  11: 5 reserved
    reg_sel_piso0_sd_out      :  2,    //  13:12
                              :  6,    //  19:14 reserved
    reg_sel_sipo0_tp_out      :  2,    //  21:20
                              :  6,    //  27:22 reserved
    reg_sel_piso0_tp_in       :  1,    //     28
                              :  3;    //  31:29 reserved
}SRDS32TO1_MUX_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7008    align_cfg0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sw_dap_stop0          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sw_dap_en0            :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_sw_da_en0             :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sw_piso_ivalid0       :  1,    //     12
    reg_sw_sipo_ivalid0       :  1,    //     13
                              :  2,    //  15:14 reserved
    reg_sipo_out_dbgen0       :  1,    //     16
    reg_piso_in_dbgen0        :  1,    //     17
                              :  2,    //  19:18 reserved
    align_ok0                 :  1,    //     20
                              :  3,    //  23:21 reserved
    dap_complete0             :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_mode                  :  2,    //  29:28
    reg_tr_2nd                :  1,    //     30
                              :  1;    //  31:31 reserved
}SRDS32TO1_ALIGN_CFG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_700C    align_cfg1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sipo_out_dbg0             : 32;    //  31: 0
}SRDS32TO1_ALIGN_CFG1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7010    align_cfg2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    piso_in_dbg0              : 32;    //  31: 0
}SRDS32TO1_ALIGN_CFG2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7028    tstmp_err ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    err_tstmp_status          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_err_tstmp_en          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_err_tstmp_clr         :  1,    //      8
                              :  7,    //  15: 9 reserved
    err_tstmp_cur             :  8,    //  23:16
    err_tstmp_pre             :  8;    //  31:24
}SRDS32TO1_TSTMP_ERR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_702C    intr_cfg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    intr_tstmp_err            :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_intr_en               :  1,    //      4
    reg_intr_clear            :  1,    //      5
    reg_intr_edge_en          :  1,    //      6
    reg_intr_polar_high_en    :  1,    //      7
                              : 24;    //   31:8 reserved
}SRDS32TO1_INTR_CFG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7030    pd_igate_en0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_gate_en0        : 32;    //  31: 0
}SRDS32TO1_PD_IGATE_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7034    pd_igate_dat0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_gate_dat0       : 32;    //  31: 0
}SRDS32TO1_PD_IGATE_DAT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7038    pd_ogate_en0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_out_gate_en0       : 32;    //  31: 0
}SRDS32TO1_PD_OGATE_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_703C    pd_ogate_dat0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_out_gate_dat0      : 32;    //  31: 0
}SRDS32TO1_PD_OGATE_DAT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7040    scl_hold0_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold0_en          : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}SRDS32TO1_SCL_HOLD0_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7044    pd_i2c_en0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pullup_en        : 32;    //  31: 0
}SRDS32TO1_PD_I2C_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7048    pd_piso_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_piso_dly0          : 32;    //  31: 0
}SRDS32TO1_PD_PISO_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_704C    pd_piso_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_piso_dly1          : 32;    //  31: 0
}SRDS32TO1_PD_PISO_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7050    pd_sipo_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_sipo_dly0          : 32;    //  31: 0
}SRDS32TO1_PD_SIPO_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7054    pd_sipo_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_sipo_dly1          : 32;    //  31: 0
}SRDS32TO1_PD_SIPO_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7058    tstmp_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tstmp_piso                :  8,    //   7: 0
    reg_tstmp_piso_en         :  1,    //      8
    reg_autostop_tstmp_piso   :  1,    //      9
                              :  2,    //  11:10 reserved
    reg_reset_stmp_piso       :  1,    //     12
                              :  3,    //  15:13 reserved
    tstmp_sipo                :  8,    //  23:16
    reg_tstmp_sipo_en         :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_reset_stmp_sipo       :  1,    //     28
                              :  3;    //  31:29 reserved
}SRDS32TO1_TSTMP_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_705C    chg_tstmp ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_chg_tstmp_piso        :  8,    //   7: 0
                              :  8,    //  15: 8 reserved
    reg_chg_tstmp_sipo        :  8,    //  23:16
                              :  8;    //  31:24 reserved
}SRDS32TO1_CHG_TSTMP_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7060    chg_mode ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_chg_mode_piso         :  1,    //      0
                              : 15,    //  15: 1 reserved
    reg_chg_mode_sipo         :  1,    //     16
                              :  3,    //  19:17 reserved
    mode_chged_ok             :  1,    //     20
                              : 11;    //  31:21 reserved
}SRDS32TO1_CHG_MODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7068    pd_i2c_chg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_piso_i2c_chg       : 10,    //   9: 0
                              :  6,    //  15:10 reserved
    reg_pd_sipo_i2c_chg       : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_PD_I2C_CHG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_706C    pd_debnc_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_en        : 32;    //  31: 0
}SRDS32TO1_PD_DEBNC_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7070    pd_debnc_len7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len28     :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len29     :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len30     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len31     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7074    pd_debnc_len6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len24     :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len25     :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len26     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len27     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7078    pd_debnc_len5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len20     :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len21     :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len22     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len23     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_707C    pd_debnc_len4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len16     :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len17     :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len18     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len19     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7080    pd_debnc_len3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len12     :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len13     :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len14     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len15     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7084    pd_debnc_len2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len8      :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len9      :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len10     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len11     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7088    pd_debnc_len1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len4      :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len5      :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len6      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len7      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_708C    pd_debnc_len0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pd_in_debnc_len0      :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_pd_in_debnc_len1      :  6,    //  13: 8
                              :  2,    //  15:14 reserved
    reg_pd_in_debnc_len2      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pd_in_debnc_len3      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}SRDS32TO1_PD_DEBNC_LEN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7090    pd_pu_dly7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly28         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly29         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly30         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly31         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7094    pd_pu_dly6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly24         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly25         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly26         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly27         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7098    pd_pu_dly5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly20         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly21         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly22         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly23         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_709C    pd_pu_dly4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly16         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly17         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly18         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly19         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A0    pd_pu_dly3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly12         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly13         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly14         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly15         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A4    pd_pu_dly2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly8          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly9          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly10         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly11         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A8    pd_pu_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly4          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly5          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly6          :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly7          :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70AC    pd_pu_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pu_dly0          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pu_dly1          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pu_dly2          :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pu_dly3          :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PU_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B0    scl_low_cnt9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt9         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt9          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B4    scl_low_cnt8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt8         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt8          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B8    scl_low_cnt7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt7         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt7          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70BC    scl_low_cnt6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt6         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt6          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C0    scl_low_cnt5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt5         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt5          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C4    scl_low_cnt4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt4         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt4          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C8    scl_low_cnt3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt3         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt3          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70CC    scl_low_cnt2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt2         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt2          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70D0    scl_low_cnt1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt1         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt1          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70D4    scl_low_cnt0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl_hold_cnt0         :  7,    //   6: 0
                              :  9,    //  15: 7 reserved
    reg_scl_low_cnt0          : 10,    //  25:16
                              :  6;    //  31:26 reserved
}SRDS32TO1_SCL_LOW_CNT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E0    pd_pd_dly7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly28         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly29         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly30         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly31         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E4    pd_pd_dly6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly24         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly25         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly26         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly27         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E8    pd_pd_dly5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly20         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly21         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly22         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly23         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70EC    pd_pd_dly4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly16         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly17         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly18         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly19         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F0    pd_pd_dly3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly12         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly13         :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly14         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly15         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F4    pd_pd_dly2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly8          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly9          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly10         :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly11         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F8    pd_pd_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly4          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly5          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly6          :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly7          :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70FC    pd_pd_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_test_pd_dly0          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_test_pd_dly1          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_test_pd_dly2          :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_test_pd_dly3          :  5,    //  28:24
                              :  3;    //  31:29 reserved
}SRDS32TO1_PD_PD_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    srds32to1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRDS32TO1_SWRST_O26A0_T            swrst      ;             // 0x1_7000
    SRDS32TO1_MUX_O26A0_T              mux        ;             // 0x1_7004
    SRDS32TO1_ALIGN_CFG0_O26A0_T       align_cfg0 ;             // 0x1_7008
    SRDS32TO1_ALIGN_CFG1_O26A0_T       align_cfg1 ;             // 0x1_700C
    SRDS32TO1_ALIGN_CFG2_O26A0_T       align_cfg2 ;             // 0x1_7010
    UINT32                             _rsvd_00[5];             // 0x1_7014 ~ 0x1_7024
    SRDS32TO1_TSTMP_ERR_O26A0_T        tstmp_err  ;             // 0x1_7028
    SRDS32TO1_INTR_CFG_O26A0_T         intr_cfg   ;             // 0x1_702C
    SRDS32TO1_PD_IGATE_EN0_O26A0_T     pd_igate_en0;            // 0x1_7030
    SRDS32TO1_PD_IGATE_DAT0_O26A0_T    pd_igate_dat0;           // 0x1_7034
    SRDS32TO1_PD_OGATE_EN0_O26A0_T     pd_ogate_en0;            // 0x1_7038
    SRDS32TO1_PD_OGATE_DAT0_O26A0_T    pd_ogate_dat0;           // 0x1_703C
    SRDS32TO1_SCL_HOLD0_EN_O26A0_T     scl_hold0_en;            // 0x1_7040
    SRDS32TO1_PD_I2C_EN0_O26A0_T       pd_i2c_en0 ;             // 0x1_7044
    SRDS32TO1_PD_PISO_DLY0_O26A0_T     pd_piso_dly0;            // 0x1_7048
    SRDS32TO1_PD_PISO_DLY1_O26A0_T     pd_piso_dly1;            // 0x1_704C
    SRDS32TO1_PD_SIPO_DLY0_O26A0_T     pd_sipo_dly0;            // 0x1_7050
    SRDS32TO1_PD_SIPO_DLY1_O26A0_T     pd_sipo_dly1;            // 0x1_7054
    SRDS32TO1_TSTMP_CTRL_O26A0_T       tstmp_ctrl ;             // 0x1_7058
    SRDS32TO1_CHG_TSTMP_O26A0_T        chg_tstmp  ;             // 0x1_705C
    SRDS32TO1_CHG_MODE_O26A0_T         chg_mode   ;             // 0x1_7060
    UINT32                             _rsvd_01[1];             // 0x1_7064
    SRDS32TO1_PD_I2C_CHG_O26A0_T       pd_i2c_chg ;             // 0x1_7068
    SRDS32TO1_PD_DEBNC_EN_O26A0_T      pd_debnc_en;             // 0x1_706C
    SRDS32TO1_PD_DEBNC_LEN7_O26A0_T    pd_debnc_len7;           // 0x1_7070
    SRDS32TO1_PD_DEBNC_LEN6_O26A0_T    pd_debnc_len6;           // 0x1_7074
    SRDS32TO1_PD_DEBNC_LEN5_O26A0_T    pd_debnc_len5;           // 0x1_7078
    SRDS32TO1_PD_DEBNC_LEN4_O26A0_T    pd_debnc_len4;           // 0x1_707C
    SRDS32TO1_PD_DEBNC_LEN3_O26A0_T    pd_debnc_len3;           // 0x1_7080
    SRDS32TO1_PD_DEBNC_LEN2_O26A0_T    pd_debnc_len2;           // 0x1_7084
    SRDS32TO1_PD_DEBNC_LEN1_O26A0_T    pd_debnc_len1;           // 0x1_7088
    SRDS32TO1_PD_DEBNC_LEN0_O26A0_T    pd_debnc_len0;           // 0x1_708C
    SRDS32TO1_PD_PU_DLY7_O26A0_T       pd_pu_dly7 ;             // 0x1_7090
    SRDS32TO1_PD_PU_DLY6_O26A0_T       pd_pu_dly6 ;             // 0x1_7094
    SRDS32TO1_PD_PU_DLY5_O26A0_T       pd_pu_dly5 ;             // 0x1_7098
    SRDS32TO1_PD_PU_DLY4_O26A0_T       pd_pu_dly4 ;             // 0x1_709C
    SRDS32TO1_PD_PU_DLY3_O26A0_T       pd_pu_dly3 ;             // 0x1_70A0
    SRDS32TO1_PD_PU_DLY2_O26A0_T       pd_pu_dly2 ;             // 0x1_70A4
    SRDS32TO1_PD_PU_DLY1_O26A0_T       pd_pu_dly1 ;             // 0x1_70A8
    SRDS32TO1_PD_PU_DLY0_O26A0_T       pd_pu_dly0 ;             // 0x1_70AC
    SRDS32TO1_SCL_LOW_CNT9_O26A0_T     scl_low_cnt9;            // 0x1_70B0
    SRDS32TO1_SCL_LOW_CNT8_O26A0_T     scl_low_cnt8;            // 0x1_70B4
    SRDS32TO1_SCL_LOW_CNT7_O26A0_T     scl_low_cnt7;            // 0x1_70B8
    SRDS32TO1_SCL_LOW_CNT6_O26A0_T     scl_low_cnt6;            // 0x1_70BC
    SRDS32TO1_SCL_LOW_CNT5_O26A0_T     scl_low_cnt5;            // 0x1_70C0
    SRDS32TO1_SCL_LOW_CNT4_O26A0_T     scl_low_cnt4;            // 0x1_70C4
    SRDS32TO1_SCL_LOW_CNT3_O26A0_T     scl_low_cnt3;            // 0x1_70C8
    SRDS32TO1_SCL_LOW_CNT2_O26A0_T     scl_low_cnt2;            // 0x1_70CC
    SRDS32TO1_SCL_LOW_CNT1_O26A0_T     scl_low_cnt1;            // 0x1_70D0
    SRDS32TO1_SCL_LOW_CNT0_O26A0_T     scl_low_cnt0;            // 0x1_70D4
    UINT32                             _rsvd_02[2];             // 0x1_70D8 ~ 0x1_70DC
    SRDS32TO1_PD_PD_DLY7_O26A0_T       pd_pd_dly7 ;             // 0x1_70E0
    SRDS32TO1_PD_PD_DLY6_O26A0_T       pd_pd_dly6 ;             // 0x1_70E4
    SRDS32TO1_PD_PD_DLY5_O26A0_T       pd_pd_dly5 ;             // 0x1_70E8
    SRDS32TO1_PD_PD_DLY4_O26A0_T       pd_pd_dly4 ;             // 0x1_70EC
    SRDS32TO1_PD_PD_DLY3_O26A0_T       pd_pd_dly3 ;             // 0x1_70F0
    SRDS32TO1_PD_PD_DLY2_O26A0_T       pd_pd_dly2 ;             // 0x1_70F4
    SRDS32TO1_PD_PD_DLY1_O26A0_T       pd_pd_dly1 ;             // 0x1_70F8
    SRDS32TO1_PD_PD_DLY0_O26A0_T       pd_pd_dly0 ;             // 0x1_70FC
}SRDS32TO1_REG_O26A0_T;
/* 56 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define SRDS32TO1_SWRST_O26A0_T_OFF                         (BASEADDRESS+0x0000)
#define SRDS32TO1_MUX_O26A0_T_OFF                           (BASEADDRESS+0x0004)
#define SRDS32TO1_ALIGN_CFG0_O26A0_T_OFF                    (BASEADDRESS+0x0008)
#define SRDS32TO1_ALIGN_CFG1_O26A0_T_OFF                    (BASEADDRESS+0x000C)
#define SRDS32TO1_ALIGN_CFG2_O26A0_T_OFF                    (BASEADDRESS+0x0010)
#define SRDS32TO1_TSTMP_ERR_O26A0_T_OFF                     (BASEADDRESS+0x0028)
#define SRDS32TO1_INTR_CFG_O26A0_T_OFF                      (BASEADDRESS+0x002C)
#define SRDS32TO1_PD_IGATE_EN0_O26A0_T_OFF                  (BASEADDRESS+0x0030)
#define SRDS32TO1_PD_IGATE_DAT0_O26A0_T_OFF                 (BASEADDRESS+0x0034)
#define SRDS32TO1_PD_OGATE_EN0_O26A0_T_OFF                  (BASEADDRESS+0x0038)
#define SRDS32TO1_PD_OGATE_DAT0_O26A0_T_OFF                 (BASEADDRESS+0x003C)
#define SRDS32TO1_SCL_HOLD0_EN_O26A0_T_OFF                  (BASEADDRESS+0x0040)
#define SRDS32TO1_PD_I2C_EN0_O26A0_T_OFF                    (BASEADDRESS+0x0044)
#define SRDS32TO1_PD_PISO_DLY0_O26A0_T_OFF                  (BASEADDRESS+0x0048)
#define SRDS32TO1_PD_PISO_DLY1_O26A0_T_OFF                  (BASEADDRESS+0x004C)
#define SRDS32TO1_PD_SIPO_DLY0_O26A0_T_OFF                  (BASEADDRESS+0x0050)
#define SRDS32TO1_PD_SIPO_DLY1_O26A0_T_OFF                  (BASEADDRESS+0x0054)
#define SRDS32TO1_TSTMP_CTRL_O26A0_T_OFF                    (BASEADDRESS+0x0058)
#define SRDS32TO1_CHG_TSTMP_O26A0_T_OFF                     (BASEADDRESS+0x005C)
#define SRDS32TO1_CHG_MODE_O26A0_T_OFF                      (BASEADDRESS+0x0060)
#define SRDS32TO1_PD_I2C_CHG_O26A0_T_OFF                    (BASEADDRESS+0x0068)
#define SRDS32TO1_PD_DEBNC_EN_O26A0_T_OFF                   (BASEADDRESS+0x006C)
#define SRDS32TO1_PD_DEBNC_LEN7_O26A0_T_OFF                 (BASEADDRESS+0x0070)
#define SRDS32TO1_PD_DEBNC_LEN6_O26A0_T_OFF                 (BASEADDRESS+0x0074)
#define SRDS32TO1_PD_DEBNC_LEN5_O26A0_T_OFF                 (BASEADDRESS+0x0078)
#define SRDS32TO1_PD_DEBNC_LEN4_O26A0_T_OFF                 (BASEADDRESS+0x007C)
#define SRDS32TO1_PD_DEBNC_LEN3_O26A0_T_OFF                 (BASEADDRESS+0x0080)
#define SRDS32TO1_PD_DEBNC_LEN2_O26A0_T_OFF                 (BASEADDRESS+0x0084)
#define SRDS32TO1_PD_DEBNC_LEN1_O26A0_T_OFF                 (BASEADDRESS+0x0088)
#define SRDS32TO1_PD_DEBNC_LEN0_O26A0_T_OFF                 (BASEADDRESS+0x008C)
#define SRDS32TO1_PD_PU_DLY7_O26A0_T_OFF                    (BASEADDRESS+0x0090)
#define SRDS32TO1_PD_PU_DLY6_O26A0_T_OFF                    (BASEADDRESS+0x0094)
#define SRDS32TO1_PD_PU_DLY5_O26A0_T_OFF                    (BASEADDRESS+0x0098)
#define SRDS32TO1_PD_PU_DLY4_O26A0_T_OFF                    (BASEADDRESS+0x009C)
#define SRDS32TO1_PD_PU_DLY3_O26A0_T_OFF                    (BASEADDRESS+0x00A0)
#define SRDS32TO1_PD_PU_DLY2_O26A0_T_OFF                    (BASEADDRESS+0x00A4)
#define SRDS32TO1_PD_PU_DLY1_O26A0_T_OFF                    (BASEADDRESS+0x00A8)
#define SRDS32TO1_PD_PU_DLY0_O26A0_T_OFF                    (BASEADDRESS+0x00AC)
#define SRDS32TO1_SCL_LOW_CNT9_O26A0_T_OFF                  (BASEADDRESS+0x00B0)
#define SRDS32TO1_SCL_LOW_CNT8_O26A0_T_OFF                  (BASEADDRESS+0x00B4)
#define SRDS32TO1_SCL_LOW_CNT7_O26A0_T_OFF                  (BASEADDRESS+0x00B8)
#define SRDS32TO1_SCL_LOW_CNT6_O26A0_T_OFF                  (BASEADDRESS+0x00BC)
#define SRDS32TO1_SCL_LOW_CNT5_O26A0_T_OFF                  (BASEADDRESS+0x00C0)
#define SRDS32TO1_SCL_LOW_CNT4_O26A0_T_OFF                  (BASEADDRESS+0x00C4)
#define SRDS32TO1_SCL_LOW_CNT3_O26A0_T_OFF                  (BASEADDRESS+0x00C8)
#define SRDS32TO1_SCL_LOW_CNT2_O26A0_T_OFF                  (BASEADDRESS+0x00CC)
#define SRDS32TO1_SCL_LOW_CNT1_O26A0_T_OFF                  (BASEADDRESS+0x00D0)
#define SRDS32TO1_SCL_LOW_CNT0_O26A0_T_OFF                  (BASEADDRESS+0x00D4)
#define SRDS32TO1_PD_PD_DLY7_O26A0_T_OFF                    (BASEADDRESS+0x00E0)
#define SRDS32TO1_PD_PD_DLY6_O26A0_T_OFF                    (BASEADDRESS+0x00E4)
#define SRDS32TO1_PD_PD_DLY5_O26A0_T_OFF                    (BASEADDRESS+0x00E8)
#define SRDS32TO1_PD_PD_DLY4_O26A0_T_OFF                    (BASEADDRESS+0x00EC)
#define SRDS32TO1_PD_PD_DLY3_O26A0_T_OFF                    (BASEADDRESS+0x00F0)
#define SRDS32TO1_PD_PD_DLY2_O26A0_T_OFF                    (BASEADDRESS+0x00F4)
#define SRDS32TO1_PD_PD_DLY1_O26A0_T_OFF                    (BASEADDRESS+0x00F8)
#define SRDS32TO1_PD_PD_DLY0_O26A0_T_OFF                    (BASEADDRESS+0x00FC)

/*-----------------------------------------------------------------------------------------
    0x1_7000    swrst ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  6;    //   5: 0 reserved
    UINT32 reg_swrst_sipo0_fst:  1;    //      6
    UINT32 reg_swrst_sipo0_slo:  1;    //      7
    UINT32 resvd01            :  2;    //   9: 8 reserved
    UINT32 reg_swrst_piso0_fst:  1;    //     10
    UINT32 reg_swrst_piso0_slo:  1;    //     11
    UINT32 resvd02            :  1;    //     12 reserved
    UINT32 reg_swrst_dan0     :  1;    //     13
    UINT32 resvd03            :  1;    //     14 reserved
    UINT32 reg_swrst_dap0     :  1;    //     15
    UINT32 resvd04            : 16;    //  31:16 reserved
    };
}SRDS32TO1_SWRST_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7004    mux ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_sel_sipo0_sd_in:  1;    //      4
    UINT32 resvd01            :  7;    //  11: 5 reserved
    UINT32 reg_sel_piso0_sd_out: 2;    //  13:12
    UINT32 resvd02            :  6;    //  19:14 reserved
    UINT32 reg_sel_sipo0_tp_out: 2;    //  21:20
    UINT32 resvd03            :  6;    //  27:22 reserved
    UINT32 reg_sel_piso0_tp_in:  1;    //     28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}SRDS32TO1_MUX_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7008    align_cfg0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sw_dap_stop0   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sw_dap_en0     :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_sw_da_en0      :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_sw_piso_ivalid0:  1;    //     12
    UINT32 reg_sw_sipo_ivalid0:  1;    //     13
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_sipo_out_dbgen0:  1;    //     16
    UINT32 reg_piso_in_dbgen0 :  1;    //     17
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 align_ok0          :  1;    //     20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 dap_complete0      :  1;    //     24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_mode           :  2;    //  29:28
    UINT32 reg_tr_2nd         :  1;    //     30
    UINT32 resvd07            :  1;    //  31:31 reserved
    };
}SRDS32TO1_ALIGN_CFG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_700C    align_cfg1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sipo_out_dbg0      : 32;    //  31: 0
    };
}SRDS32TO1_ALIGN_CFG1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7010    align_cfg2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 piso_in_dbg0       : 32;    //  31: 0
    };
}SRDS32TO1_ALIGN_CFG2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7028    tstmp_err ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 err_tstmp_status   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_err_tstmp_en   :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_err_tstmp_clr  :  1;    //      8
    UINT32 resvd02            :  7;    //  15: 9 reserved
    UINT32 err_tstmp_cur      :  8;    //  23:16
    UINT32 err_tstmp_pre      :  8;    //  31:24
    };
}SRDS32TO1_TSTMP_ERR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_702C    intr_cfg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 intr_tstmp_err     :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_intr_en        :  1;    //      4
    UINT32 reg_intr_clear     :  1;    //      5
    UINT32 reg_intr_edge_en   :  1;    //      6
    UINT32 reg_intr_polar_high_en: 1;    //    7
    UINT32 resvd01            : 24;    //   31:8 reserved
    };
}SRDS32TO1_INTR_CFG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7030    pd_igate_en0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_gate_en0 : 32;    //  31: 0
    };
}SRDS32TO1_PD_IGATE_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7034    pd_igate_dat0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_gate_dat0: 32;    //  31: 0
    };
}SRDS32TO1_PD_IGATE_DAT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7038    pd_ogate_en0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_out_gate_en0: 32;    //  31: 0
    };
}SRDS32TO1_PD_OGATE_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_703C    pd_ogate_dat0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_out_gate_dat0: 32;    //  31:0
    };
}SRDS32TO1_PD_OGATE_DAT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7040    scl_hold0_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold0_en   : 10;    //   9: 0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SRDS32TO1_SCL_HOLD0_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7044    pd_i2c_en0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pullup_en : 32;    //  31: 0
    };
}SRDS32TO1_PD_I2C_EN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7048    pd_piso_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_piso_dly0   : 32;    //  31: 0
    };
}SRDS32TO1_PD_PISO_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_704C    pd_piso_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_piso_dly1   : 32;    //  31: 0
    };
}SRDS32TO1_PD_PISO_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7050    pd_sipo_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_sipo_dly0   : 32;    //  31: 0
    };
}SRDS32TO1_PD_SIPO_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7054    pd_sipo_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_sipo_dly1   : 32;    //  31: 0
    };
}SRDS32TO1_PD_SIPO_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7058    tstmp_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tstmp_piso         :  8;    //   7: 0
    UINT32 reg_tstmp_piso_en  :  1;    //      8
    UINT32 reg_autostop_tstmp_piso: 1;    //   9
    UINT32 resvd00            :  2;    //  11:10 reserved
    UINT32 reg_reset_stmp_piso:  1;    //     12
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 tstmp_sipo         :  8;    //  23:16
    UINT32 reg_tstmp_sipo_en  :  1;    //     24
    UINT32 resvd02            :  3;    //  27:25 reserved
    UINT32 reg_reset_stmp_sipo:  1;    //     28
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_TSTMP_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_705C    chg_tstmp ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_chg_tstmp_piso :  8;    //   7: 0
    UINT32 resvd00            :  8;    //  15: 8 reserved
    UINT32 reg_chg_tstmp_sipo :  8;    //  23:16
    UINT32 resvd01            :  8;    //  31:24 reserved
    };
}SRDS32TO1_CHG_TSTMP_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7060    chg_mode ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_chg_mode_piso  :  1;    //      0
    UINT32 resvd00            : 15;    //  15: 1 reserved
    UINT32 reg_chg_mode_sipo  :  1;    //     16
    UINT32 resvd01            :  3;    //  19:17 reserved
    UINT32 mode_chged_ok      :  1;    //     20
    UINT32 resvd02            : 11;    //  31:21 reserved
    };
}SRDS32TO1_CHG_MODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7068    pd_i2c_chg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_piso_i2c_chg: 10;    //   9: 0
    UINT32 resvd00            :  6;    //  15:10 reserved
    UINT32 reg_pd_sipo_i2c_chg: 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_PD_I2C_CHG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_706C    pd_debnc_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_en : 32;    //  31: 0
    };
}SRDS32TO1_PD_DEBNC_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7070    pd_debnc_len7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len28: 6;    //  5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len29: 6;    //  13:8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len30: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len31: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7074    pd_debnc_len6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len24: 6;    //  5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len25: 6;    //  13:8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len26: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len27: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7078    pd_debnc_len5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len20: 6;    //  5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len21: 6;    //  13:8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len22: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len23: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_707C    pd_debnc_len4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len16: 6;    //  5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len17: 6;    //  13:8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len18: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len19: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7080    pd_debnc_len3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len12: 6;    //  5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len13: 6;    //  13:8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len14: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len15: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7084    pd_debnc_len2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len8: 6;    //   5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len9: 6;    //  13: 8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len10: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len11: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7088    pd_debnc_len1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len4: 6;    //   5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len5: 6;    //  13: 8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len6: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len7: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_708C    pd_debnc_len0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pd_in_debnc_len0: 6;    //   5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pd_in_debnc_len1: 6;    //  13: 8
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_pd_in_debnc_len2: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_pd_in_debnc_len3: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}SRDS32TO1_PD_DEBNC_LEN0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7090    pd_pu_dly7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly28  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly29  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly30  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly31  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7094    pd_pu_dly6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly24  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly25  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly26  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly27  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_7098    pd_pu_dly5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly20  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly21  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly22  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly23  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_709C    pd_pu_dly4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly16  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly17  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly18  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly19  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A0    pd_pu_dly3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly12  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly13  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly14  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly15  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A4    pd_pu_dly2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly8   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly9   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly10  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly11  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70A8    pd_pu_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly4   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly5   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly6   :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly7   :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70AC    pd_pu_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pu_dly0   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pu_dly1   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pu_dly2   :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pu_dly3   :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PU_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B0    scl_low_cnt9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt9  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt9   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B4    scl_low_cnt8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt8  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt8   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70B8    scl_low_cnt7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt7  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt7   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70BC    scl_low_cnt6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt6  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt6   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C0    scl_low_cnt5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt5  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt5   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C4    scl_low_cnt4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt4  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt4   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70C8    scl_low_cnt3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt3  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt3   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70CC    scl_low_cnt2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt2  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt2   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70D0    scl_low_cnt1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt1  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt1   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70D4    scl_low_cnt0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_scl_hold_cnt0  :  7;    //   6: 0
    UINT32 resvd00            :  9;    //  15: 7 reserved
    UINT32 reg_scl_low_cnt0   : 10;    //  25:16
    UINT32 resvd01            :  6;    //  31:26 reserved
    };
}SRDS32TO1_SCL_LOW_CNT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E0    pd_pd_dly7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly28  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly29  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly30  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly31  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E4    pd_pd_dly6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly24  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly25  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly26  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly27  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70E8    pd_pd_dly5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly20  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly21  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly22  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly23  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70EC    pd_pd_dly4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly16  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly17  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly18  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly19  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F0    pd_pd_dly3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly12  :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly13  :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly14  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly15  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F4    pd_pd_dly2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly8   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly9   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly10  :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly11  :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70F8    pd_pd_dly1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly4   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly5   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly6   :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly7   :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_70FC    pd_pd_dly0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_test_pd_dly0   :  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_test_pd_dly1   :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_test_pd_dly2   :  5;    //  20:16
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_test_pd_dly3   :  5;    //  28:24
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}SRDS32TO1_PD_PD_DLY0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    srds32to1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRDS32TO1_SWRST_O26A0_T            swrst      ;             // 0x1_7000
    SRDS32TO1_MUX_O26A0_T              mux        ;             // 0x1_7004
    SRDS32TO1_ALIGN_CFG0_O26A0_T       align_cfg0 ;             // 0x1_7008
    SRDS32TO1_ALIGN_CFG1_O26A0_T       align_cfg1 ;             // 0x1_700C
    SRDS32TO1_ALIGN_CFG2_O26A0_T       align_cfg2 ;             // 0x1_7010
    UINT32                             _rsvd_00[5];             // 0x1_7014 ~ 0x1_7024
    SRDS32TO1_TSTMP_ERR_O26A0_T        tstmp_err  ;             // 0x1_7028
    SRDS32TO1_INTR_CFG_O26A0_T         intr_cfg   ;             // 0x1_702C
    SRDS32TO1_PD_IGATE_EN0_O26A0_T     pd_igate_en0;            // 0x1_7030
    SRDS32TO1_PD_IGATE_DAT0_O26A0_T    pd_igate_dat0;           // 0x1_7034
    SRDS32TO1_PD_OGATE_EN0_O26A0_T     pd_ogate_en0;            // 0x1_7038
    SRDS32TO1_PD_OGATE_DAT0_O26A0_T    pd_ogate_dat0;           // 0x1_703C
    SRDS32TO1_SCL_HOLD0_EN_O26A0_T     scl_hold0_en;            // 0x1_7040
    SRDS32TO1_PD_I2C_EN0_O26A0_T       pd_i2c_en0 ;             // 0x1_7044
    SRDS32TO1_PD_PISO_DLY0_O26A0_T     pd_piso_dly0;            // 0x1_7048
    SRDS32TO1_PD_PISO_DLY1_O26A0_T     pd_piso_dly1;            // 0x1_704C
    SRDS32TO1_PD_SIPO_DLY0_O26A0_T     pd_sipo_dly0;            // 0x1_7050
    SRDS32TO1_PD_SIPO_DLY1_O26A0_T     pd_sipo_dly1;            // 0x1_7054
    SRDS32TO1_TSTMP_CTRL_O26A0_T       tstmp_ctrl ;             // 0x1_7058
    SRDS32TO1_CHG_TSTMP_O26A0_T        chg_tstmp  ;             // 0x1_705C
    SRDS32TO1_CHG_MODE_O26A0_T         chg_mode   ;             // 0x1_7060
    UINT32                             _rsvd_01[1];             // 0x1_7064
    SRDS32TO1_PD_I2C_CHG_O26A0_T       pd_i2c_chg ;             // 0x1_7068
    SRDS32TO1_PD_DEBNC_EN_O26A0_T      pd_debnc_en;             // 0x1_706C
    SRDS32TO1_PD_DEBNC_LEN7_O26A0_T    pd_debnc_len7;           // 0x1_7070
    SRDS32TO1_PD_DEBNC_LEN6_O26A0_T    pd_debnc_len6;           // 0x1_7074
    SRDS32TO1_PD_DEBNC_LEN5_O26A0_T    pd_debnc_len5;           // 0x1_7078
    SRDS32TO1_PD_DEBNC_LEN4_O26A0_T    pd_debnc_len4;           // 0x1_707C
    SRDS32TO1_PD_DEBNC_LEN3_O26A0_T    pd_debnc_len3;           // 0x1_7080
    SRDS32TO1_PD_DEBNC_LEN2_O26A0_T    pd_debnc_len2;           // 0x1_7084
    SRDS32TO1_PD_DEBNC_LEN1_O26A0_T    pd_debnc_len1;           // 0x1_7088
    SRDS32TO1_PD_DEBNC_LEN0_O26A0_T    pd_debnc_len0;           // 0x1_708C
    SRDS32TO1_PD_PU_DLY7_O26A0_T       pd_pu_dly7 ;             // 0x1_7090
    SRDS32TO1_PD_PU_DLY6_O26A0_T       pd_pu_dly6 ;             // 0x1_7094
    SRDS32TO1_PD_PU_DLY5_O26A0_T       pd_pu_dly5 ;             // 0x1_7098
    SRDS32TO1_PD_PU_DLY4_O26A0_T       pd_pu_dly4 ;             // 0x1_709C
    SRDS32TO1_PD_PU_DLY3_O26A0_T       pd_pu_dly3 ;             // 0x1_70A0
    SRDS32TO1_PD_PU_DLY2_O26A0_T       pd_pu_dly2 ;             // 0x1_70A4
    SRDS32TO1_PD_PU_DLY1_O26A0_T       pd_pu_dly1 ;             // 0x1_70A8
    SRDS32TO1_PD_PU_DLY0_O26A0_T       pd_pu_dly0 ;             // 0x1_70AC
    SRDS32TO1_SCL_LOW_CNT9_O26A0_T     scl_low_cnt9;            // 0x1_70B0
    SRDS32TO1_SCL_LOW_CNT8_O26A0_T     scl_low_cnt8;            // 0x1_70B4
    SRDS32TO1_SCL_LOW_CNT7_O26A0_T     scl_low_cnt7;            // 0x1_70B8
    SRDS32TO1_SCL_LOW_CNT6_O26A0_T     scl_low_cnt6;            // 0x1_70BC
    SRDS32TO1_SCL_LOW_CNT5_O26A0_T     scl_low_cnt5;            // 0x1_70C0
    SRDS32TO1_SCL_LOW_CNT4_O26A0_T     scl_low_cnt4;            // 0x1_70C4
    SRDS32TO1_SCL_LOW_CNT3_O26A0_T     scl_low_cnt3;            // 0x1_70C8
    SRDS32TO1_SCL_LOW_CNT2_O26A0_T     scl_low_cnt2;            // 0x1_70CC
    SRDS32TO1_SCL_LOW_CNT1_O26A0_T     scl_low_cnt1;            // 0x1_70D0
    SRDS32TO1_SCL_LOW_CNT0_O26A0_T     scl_low_cnt0;            // 0x1_70D4
    UINT32                             _rsvd_02[2];             // 0x1_70D8 ~ 0x1_70DC
    SRDS32TO1_PD_PD_DLY7_O26A0_T       pd_pd_dly7 ;             // 0x1_70E0
    SRDS32TO1_PD_PD_DLY6_O26A0_T       pd_pd_dly6 ;             // 0x1_70E4
    SRDS32TO1_PD_PD_DLY5_O26A0_T       pd_pd_dly5 ;             // 0x1_70E8
    SRDS32TO1_PD_PD_DLY4_O26A0_T       pd_pd_dly4 ;             // 0x1_70EC
    SRDS32TO1_PD_PD_DLY3_O26A0_T       pd_pd_dly3 ;             // 0x1_70F0
    SRDS32TO1_PD_PD_DLY2_O26A0_T       pd_pd_dly2 ;             // 0x1_70F4
    SRDS32TO1_PD_PD_DLY1_O26A0_T       pd_pd_dly1 ;             // 0x1_70F8
    SRDS32TO1_PD_PD_DLY0_O26A0_T       pd_pd_dly0 ;             // 0x1_70FC
}SRDS32TO1_REG_O26A0_T;
/* 56 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SRDS32TO1_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/

