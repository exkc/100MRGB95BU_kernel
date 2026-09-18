#ifndef _MICOM_CRG_TOP_WOC_CTRL_REG_O24A0_H_
#define _MICOM_CRG_TOP_WOC_CTRL_REG_O24A0_H_

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
    0xF33F_4000    crg_top_woc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_only_watchdog_rst: 1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4004    crg_top_woc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_watchdog_reset_disable: 1,    //   0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4008    crg_top_woc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wdt_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_400C    crg_top_woc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_crg_top_reset_mux_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4010    crg_top_woc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_sw_reset_mux_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4014    crg_top_woc_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_sw_reset_mux_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4018    nisol_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_edid            :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_401C    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_woc             :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4024    crg_top_woc_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_from_micom      :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4028    crg_top_woc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_woc             :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_402C    crg_top_woc_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_woc_pdb     :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4030    crg_top_woc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_reg33to1808_lv_d08    :  4,    //   3: 0
    reg_reg33to1808_lv_d18    :  4,    //   7: 4
                              :  8,    //  15: 8 reserved
    reg_reg33to1808_lv_d08_sel:  1,    //     16
                              :  3,    //  19:17 reserved
    reg_reg33to1808_lv_d18_sel:  1,    //     20
                              : 11;    //  31:21 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4034    crg_top_woc_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    efv_reg33to1808_lv_d08    :  4,    //   3: 0
    efv_reg33to1808_lv_d18    :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4038    crg_top_woc_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rst_cpuav_i_ldo_woc   :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4100    crg_top_woc_dummy_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_0     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4104    crg_top_woc_dummy_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_1     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4108    crg_top_woc_dummy_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_2     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_410C    crg_top_woc_dummy_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_3     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4110    crg_top_woc_dummy_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_4     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4114    crg_top_woc_dummy_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_5     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4118    crg_top_woc_dummy_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_6     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_411C    crg_top_woc_dummy_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_7     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4120    crg_top_woc_dummy_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_8     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4124    crg_top_woc_dummy_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_9     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4128    crg_top_woc_dummy_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_10    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_412C    crg_top_woc_dummy_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_11    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4130    crg_top_woc_dummy_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_12    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4134    crg_top_woc_dummy_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_13    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4138    crg_top_woc_dummy_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_14    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_413C    crg_top_woc_dummy_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_15    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4140    crg_top_woc_dummy_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_16    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4144    crg_top_woc_dummy_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_17    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4148    crg_top_woc_dummy_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_18    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_414C    crg_top_woc_dummy_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_19    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4150    crg_top_woc_dummy_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_20    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4154    crg_top_woc_dummy_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_21    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4158    crg_top_woc_dummy_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_22    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_415C    crg_top_woc_dummy_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_23    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4160    crg_top_woc_dummy_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_24    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4164    crg_top_woc_dummy_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_25    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4168    crg_top_woc_dummy_26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_26    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_416C    crg_top_woc_dummy_27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_27    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4170    crg_top_woc_dummy_28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_28    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4174    crg_top_woc_dummy_29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_29    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4178    crg_top_woc_dummy_30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_30    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_417C    crg_top_woc_dummy_31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_31    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_crg_top_woc_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O24A0_T    crg_top_woc_r00;    // 0xF33F_4000
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O24A0_T    crg_top_woc_r01;    // 0xF33F_4004
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O24A0_T    crg_top_woc_r02;    // 0xF33F_4008
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O24A0_T    crg_top_woc_r03;    // 0xF33F_400C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O24A0_T    crg_top_woc_r04;    // 0xF33F_4010
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O24A0_T    crg_top_woc_r05;    // 0xF33F_4014
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O24A0_T    nisol_r00;      // 0xF33F_4018
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O24A0_T    nisol_r01;      // 0xF33F_401C
    UINT32                             _rsvd_00[1];             // 0xF33F_4020
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O24A0_T    crg_top_woc_r06;    // 0xF33F_4024
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O24A0_T    crg_top_woc_r07;    // 0xF33F_4028
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R08_O24A0_T    crg_top_woc_r08;    // 0xF33F_402C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O24A0_T    crg_top_woc_r10;    // 0xF33F_4030
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O24A0_T    crg_top_woc_r11;    // 0xF33F_4034
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O24A0_T    crg_top_woc_r12;    // 0xF33F_4038
    UINT32                             _rsvd_01[49];            // 0xF33F_403C ~ 0xF33F_40FC
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O24A0_T    crg_top_woc_dummy_0;    // 0xF33F_4100
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O24A0_T    crg_top_woc_dummy_1;    // 0xF33F_4104
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O24A0_T    crg_top_woc_dummy_2;    // 0xF33F_4108
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O24A0_T    crg_top_woc_dummy_3;    // 0xF33F_410C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O24A0_T    crg_top_woc_dummy_4;    // 0xF33F_4110
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O24A0_T    crg_top_woc_dummy_5;    // 0xF33F_4114
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O24A0_T    crg_top_woc_dummy_6;    // 0xF33F_4118
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O24A0_T    crg_top_woc_dummy_7;    // 0xF33F_411C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O24A0_T    crg_top_woc_dummy_8;    // 0xF33F_4120
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O24A0_T    crg_top_woc_dummy_9;    // 0xF33F_4124
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O24A0_T    crg_top_woc_dummy_10;    // 0xF33F_4128
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O24A0_T    crg_top_woc_dummy_11;    // 0xF33F_412C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O24A0_T    crg_top_woc_dummy_12;    // 0xF33F_4130
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O24A0_T    crg_top_woc_dummy_13;    // 0xF33F_4134
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O24A0_T    crg_top_woc_dummy_14;    // 0xF33F_4138
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O24A0_T    crg_top_woc_dummy_15;    // 0xF33F_413C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O24A0_T    crg_top_woc_dummy_16;    // 0xF33F_4140
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O24A0_T    crg_top_woc_dummy_17;    // 0xF33F_4144
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O24A0_T    crg_top_woc_dummy_18;    // 0xF33F_4148
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O24A0_T    crg_top_woc_dummy_19;    // 0xF33F_414C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O24A0_T    crg_top_woc_dummy_20;    // 0xF33F_4150
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O24A0_T    crg_top_woc_dummy_21;    // 0xF33F_4154
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O24A0_T    crg_top_woc_dummy_22;    // 0xF33F_4158
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O24A0_T    crg_top_woc_dummy_23;    // 0xF33F_415C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O24A0_T    crg_top_woc_dummy_24;    // 0xF33F_4160
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O24A0_T    crg_top_woc_dummy_25;    // 0xF33F_4164
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O24A0_T    crg_top_woc_dummy_26;    // 0xF33F_4168
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O24A0_T    crg_top_woc_dummy_27;    // 0xF33F_416C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O24A0_T    crg_top_woc_dummy_28;    // 0xF33F_4170
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O24A0_T    crg_top_woc_dummy_29;    // 0xF33F_4174
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O24A0_T    crg_top_woc_dummy_30;    // 0xF33F_4178
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O24A0_T    crg_top_woc_dummy_31;    // 0xF33F_417C
}MICOM_CRG_TOP_WOC_CTRL_REG_O24A0_T;
/* 46 regs */

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

#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O24A0_T_OFF  (BASEADDRESS+0x0000)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O24A0_T_OFF  (BASEADDRESS+0x0004)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O24A0_T_OFF  (BASEADDRESS+0x0008)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O24A0_T_OFF  (BASEADDRESS+0x000C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O24A0_T_OFF  (BASEADDRESS+0x0010)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O24A0_T_OFF  (BASEADDRESS+0x0014)
#define MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O24A0_T_OFF        (BASEADDRESS+0x0018)
#define MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O24A0_T_OFF        (BASEADDRESS+0x001C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O24A0_T_OFF  (BASEADDRESS+0x0024)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O24A0_T_OFF  (BASEADDRESS+0x0028)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R08_O24A0_T_OFF  (BASEADDRESS+0x002C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O24A0_T_OFF  (BASEADDRESS+0x0030)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O24A0_T_OFF  (BASEADDRESS+0x0034)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O24A0_T_OFF  (BASEADDRESS+0x0038)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O24A0_T_OFF(BASEADDRESS+0x0100)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O24A0_T_OFF(BASEADDRESS+0x0104)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O24A0_T_OFF(BASEADDRESS+0x0108)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O24A0_T_OFF(BASEADDRESS+0x010C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O24A0_T_OFF(BASEADDRESS+0x0110)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O24A0_T_OFF(BASEADDRESS+0x0114)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O24A0_T_OFF(BASEADDRESS+0x0118)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O24A0_T_OFF(BASEADDRESS+0x011C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O24A0_T_OFF(BASEADDRESS+0x0120)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O24A0_T_OFF(BASEADDRESS+0x0124)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O24A0_T_OFF(BASEADDRESS+0x0128)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O24A0_T_OFF(BASEADDRESS+0x012C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O24A0_T_OFF(BASEADDRESS+0x0130)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O24A0_T_OFF(BASEADDRESS+0x0134)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O24A0_T_OFF(BASEADDRESS+0x0138)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O24A0_T_OFF(BASEADDRESS+0x013C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O24A0_T_OFF(BASEADDRESS+0x0140)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O24A0_T_OFF(BASEADDRESS+0x0144)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O24A0_T_OFF(BASEADDRESS+0x0148)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O24A0_T_OFF(BASEADDRESS+0x014C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O24A0_T_OFF(BASEADDRESS+0x0150)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O24A0_T_OFF(BASEADDRESS+0x0154)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O24A0_T_OFF(BASEADDRESS+0x0158)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O24A0_T_OFF(BASEADDRESS+0x015C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O24A0_T_OFF(BASEADDRESS+0x0160)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O24A0_T_OFF(BASEADDRESS+0x0164)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O24A0_T_OFF(BASEADDRESS+0x0168)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O24A0_T_OFF(BASEADDRESS+0x016C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O24A0_T_OFF(BASEADDRESS+0x0170)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O24A0_T_OFF(BASEADDRESS+0x0174)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O24A0_T_OFF(BASEADDRESS+0x0178)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O24A0_T_OFF(BASEADDRESS+0x017C)

/*-----------------------------------------------------------------------------------------
    0xF33F_4000    crg_top_woc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_only_watchdog_rst: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4004    crg_top_woc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_watchdog_reset_disable: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4008    crg_top_woc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wdt_reset_mux_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_400C    crg_top_woc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_crg_top_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4010    crg_top_woc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4014    crg_top_woc_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4018    nisol_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_edid     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_401C    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_woc      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4024    crg_top_woc_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_from_micom: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4028    crg_top_woc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_woc      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_402C    crg_top_woc_r08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_woc_pdb: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4030    crg_top_woc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_reg33to1808_lv_d08: 4;    //  3:0
    UINT32 reg_reg33to1808_lv_d18: 4;    //  7:4
    UINT32 resvd00            :  8;    //  15: 8 reserved
    UINT32 reg_reg33to1808_lv_d08_sel: 1;    //  16
    UINT32 resvd01            :  3;    //  19:17 reserved
    UINT32 reg_reg33to1808_lv_d18_sel: 1;    //  20
    UINT32 resvd02            : 11;    //  31:21 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4034    crg_top_woc_r11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 efv_reg33to1808_lv_d08: 4;    //  3:0
    UINT32 efv_reg33to1808_lv_d18: 4;    //  7:4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4038    crg_top_woc_r12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rst_cpuav_i_ldo_woc: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4100    crg_top_woc_dummy_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_0: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4104    crg_top_woc_dummy_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_1: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4108    crg_top_woc_dummy_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_2: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_410C    crg_top_woc_dummy_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_3: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4110    crg_top_woc_dummy_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_4: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4114    crg_top_woc_dummy_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_5: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4118    crg_top_woc_dummy_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_6: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_411C    crg_top_woc_dummy_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_7: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4120    crg_top_woc_dummy_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_8: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4124    crg_top_woc_dummy_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_9: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4128    crg_top_woc_dummy_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_10: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_412C    crg_top_woc_dummy_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_11: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4130    crg_top_woc_dummy_12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_12: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4134    crg_top_woc_dummy_13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_13: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4138    crg_top_woc_dummy_14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_14: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_413C    crg_top_woc_dummy_15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_15: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4140    crg_top_woc_dummy_16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_16: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4144    crg_top_woc_dummy_17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_17: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4148    crg_top_woc_dummy_18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_18: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_414C    crg_top_woc_dummy_19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_19: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4150    crg_top_woc_dummy_20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_20: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4154    crg_top_woc_dummy_21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_21: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4158    crg_top_woc_dummy_22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_22: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_415C    crg_top_woc_dummy_23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_23: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4160    crg_top_woc_dummy_24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_24: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4164    crg_top_woc_dummy_25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_25: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4168    crg_top_woc_dummy_26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_26: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_416C    crg_top_woc_dummy_27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_27: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4170    crg_top_woc_dummy_28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_28: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4174    crg_top_woc_dummy_29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_29: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_4178    crg_top_woc_dummy_30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_30: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_417C    crg_top_woc_dummy_31 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_31: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_crg_top_woc_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O24A0_T    crg_top_woc_r00;    // 0xF33F_4000
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O24A0_T    crg_top_woc_r01;    // 0xF33F_4004
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O24A0_T    crg_top_woc_r02;    // 0xF33F_4008
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O24A0_T    crg_top_woc_r03;    // 0xF33F_400C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O24A0_T    crg_top_woc_r04;    // 0xF33F_4010
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O24A0_T    crg_top_woc_r05;    // 0xF33F_4014
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O24A0_T    nisol_r00;      // 0xF33F_4018
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O24A0_T    nisol_r01;      // 0xF33F_401C
    UINT32                             _rsvd_00[1];             // 0xF33F_4020
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O24A0_T    crg_top_woc_r06;    // 0xF33F_4024
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O24A0_T    crg_top_woc_r07;    // 0xF33F_4028
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R08_O24A0_T    crg_top_woc_r08;    // 0xF33F_402C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O24A0_T    crg_top_woc_r10;    // 0xF33F_4030
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O24A0_T    crg_top_woc_r11;    // 0xF33F_4034
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O24A0_T    crg_top_woc_r12;    // 0xF33F_4038
    UINT32                             _rsvd_01[49];            // 0xF33F_403C ~ 0xF33F_40FC
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O24A0_T    crg_top_woc_dummy_0;    // 0xF33F_4100
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O24A0_T    crg_top_woc_dummy_1;    // 0xF33F_4104
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O24A0_T    crg_top_woc_dummy_2;    // 0xF33F_4108
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O24A0_T    crg_top_woc_dummy_3;    // 0xF33F_410C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O24A0_T    crg_top_woc_dummy_4;    // 0xF33F_4110
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O24A0_T    crg_top_woc_dummy_5;    // 0xF33F_4114
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O24A0_T    crg_top_woc_dummy_6;    // 0xF33F_4118
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O24A0_T    crg_top_woc_dummy_7;    // 0xF33F_411C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O24A0_T    crg_top_woc_dummy_8;    // 0xF33F_4120
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O24A0_T    crg_top_woc_dummy_9;    // 0xF33F_4124
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O24A0_T    crg_top_woc_dummy_10;    // 0xF33F_4128
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O24A0_T    crg_top_woc_dummy_11;    // 0xF33F_412C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O24A0_T    crg_top_woc_dummy_12;    // 0xF33F_4130
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O24A0_T    crg_top_woc_dummy_13;    // 0xF33F_4134
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O24A0_T    crg_top_woc_dummy_14;    // 0xF33F_4138
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O24A0_T    crg_top_woc_dummy_15;    // 0xF33F_413C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O24A0_T    crg_top_woc_dummy_16;    // 0xF33F_4140
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O24A0_T    crg_top_woc_dummy_17;    // 0xF33F_4144
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O24A0_T    crg_top_woc_dummy_18;    // 0xF33F_4148
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O24A0_T    crg_top_woc_dummy_19;    // 0xF33F_414C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O24A0_T    crg_top_woc_dummy_20;    // 0xF33F_4150
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O24A0_T    crg_top_woc_dummy_21;    // 0xF33F_4154
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O24A0_T    crg_top_woc_dummy_22;    // 0xF33F_4158
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O24A0_T    crg_top_woc_dummy_23;    // 0xF33F_415C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O24A0_T    crg_top_woc_dummy_24;    // 0xF33F_4160
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O24A0_T    crg_top_woc_dummy_25;    // 0xF33F_4164
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O24A0_T    crg_top_woc_dummy_26;    // 0xF33F_4168
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O24A0_T    crg_top_woc_dummy_27;    // 0xF33F_416C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O24A0_T    crg_top_woc_dummy_28;    // 0xF33F_4170
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O24A0_T    crg_top_woc_dummy_29;    // 0xF33F_4174
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O24A0_T    crg_top_woc_dummy_30;    // 0xF33F_4178
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O24A0_T    crg_top_woc_dummy_31;    // 0xF33F_417C
}MICOM_CRG_TOP_WOC_CTRL_REG_O24A0_T;
/* 46 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MICOM_CRG_TOP_WOC_CTRL_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

