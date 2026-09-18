#ifndef _MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_H_
#define _MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_H_

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
    0xCA3A_7000    crg_top_woc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_only_watchdog_rst: 1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7004    crg_top_woc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_watchdog_reset_disable: 1,    //   0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7008    crg_top_woc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wdt_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_700C    crg_top_woc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_crg_top_reset_mux_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7010    crg_top_woc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_sw_reset_mux_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7014    crg_top_woc_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_sw_reset_mux_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7018    nisol_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_edid            :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_701C    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_woc             :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7024    crg_top_woc_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_from_micom      :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7028    crg_top_woc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_woc             :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7030    crg_top_woc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_reg33to18075_lv_d075  :  4,    //   3: 0
    reg_reg33to18075_lv_d18   :  4,    //   7: 4
                              :  8,    //  15: 8 reserved
    reg_reg33to18075_lv_d075_sel: 1,    //    16
                              :  3,    //  19:17 reserved
    reg_reg33to18075_lv_d18_sel: 1,    //     20
                              : 11;    //  31:21 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7034    crg_top_woc_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    efv_reg33to18075_lv_d075  :  4,    //   3: 0
    efv_reg33to18075_lv_d18   :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7038    crg_top_woc_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rst_cpuav_i_ldo_woc   :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7040    txp_clkdrv_dual_top ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_dual_top_pdb :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_dual_top_icon0: 2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_txclkdrv_dual_top_icon1: 2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_txclkdrv_dual_top_sel0:  1,    //     12
                              :  3,    //  15:13 reserved
    reg_txclkdrv_dual_top_sel1:  1,    //     16
                              : 15;    //  31:17 reserved
}MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_TOP_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7044    txp_clkdrv_dual_bot ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_dual_bot_pdb :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_dual_bot_icon0: 2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_txclkdrv_dual_bot_icon1: 2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_txclkdrv_dual_bot_sel0:  1,    //     12
                              :  3,    //  15:13 reserved
    reg_txclkdrv_dual_bot_sel1:  1,    //     16
                              : 15;    //  31:17 reserved
}MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_BOT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7100    crg_top_woc_dummy_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_0     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7104    crg_top_woc_dummy_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_1     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7108    crg_top_woc_dummy_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_2     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_710C    crg_top_woc_dummy_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_3     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7110    crg_top_woc_dummy_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_4     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7114    crg_top_woc_dummy_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_5     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7118    crg_top_woc_dummy_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_6     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_711C    crg_top_woc_dummy_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_7     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7120    crg_top_woc_dummy_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_8     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7124    crg_top_woc_dummy_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_9     : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7128    crg_top_woc_dummy_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_10    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_712C    crg_top_woc_dummy_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_11    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7130    crg_top_woc_dummy_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_12    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7134    crg_top_woc_dummy_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_13    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7138    crg_top_woc_dummy_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_14    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_713C    crg_top_woc_dummy_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_15    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7140    crg_top_woc_dummy_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_16    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7144    crg_top_woc_dummy_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_17    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7148    crg_top_woc_dummy_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_18    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_714C    crg_top_woc_dummy_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_19    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7150    crg_top_woc_dummy_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_20    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7154    crg_top_woc_dummy_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_21    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7158    crg_top_woc_dummy_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_22    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_715C    crg_top_woc_dummy_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_23    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7160    crg_top_woc_dummy_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_24    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7164    crg_top_woc_dummy_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_25    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7168    crg_top_woc_dummy_26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_26    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_716C    crg_top_woc_dummy_27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_27    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7170    crg_top_woc_dummy_28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_28    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7174    crg_top_woc_dummy_29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_29    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7178    crg_top_woc_dummy_30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_30    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_717C    crg_top_woc_dummy_31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_non_reset_dummy_31    : 32;    //  31: 0
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_crg_top_woc_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O26A0_T    crg_top_woc_r00;    // 0xCA3A_7000
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O26A0_T    crg_top_woc_r01;    // 0xCA3A_7004
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O26A0_T    crg_top_woc_r02;    // 0xCA3A_7008
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O26A0_T    crg_top_woc_r03;    // 0xCA3A_700C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O26A0_T    crg_top_woc_r04;    // 0xCA3A_7010
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O26A0_T    crg_top_woc_r05;    // 0xCA3A_7014
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O26A0_T    nisol_r00;      // 0xCA3A_7018
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O26A0_T    nisol_r01;      // 0xCA3A_701C
    UINT32                             _rsvd_00[1];             // 0xCA3A_7020
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O26A0_T    crg_top_woc_r06;    // 0xCA3A_7024
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O26A0_T    crg_top_woc_r07;    // 0xCA3A_7028
    UINT32                             _rsvd_01[1];             // 0xCA3A_702C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O26A0_T    crg_top_woc_r10;    // 0xCA3A_7030
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O26A0_T    crg_top_woc_r11;    // 0xCA3A_7034
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O26A0_T    crg_top_woc_r12;    // 0xCA3A_7038
    UINT32                             _rsvd_02[1];             // 0xCA3A_703C
    MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_TOP_O26A0_T    txp_clkdrv_dual_top;    // 0xCA3A_7040
    MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_BOT_O26A0_T    txp_clkdrv_dual_bot;    // 0xCA3A_7044
    UINT32                             _rsvd_03[46];            // 0xCA3A_7048 ~ 0xCA3A_70FC
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O26A0_T    crg_top_woc_dummy_0;    // 0xCA3A_7100
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O26A0_T    crg_top_woc_dummy_1;    // 0xCA3A_7104
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O26A0_T    crg_top_woc_dummy_2;    // 0xCA3A_7108
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O26A0_T    crg_top_woc_dummy_3;    // 0xCA3A_710C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O26A0_T    crg_top_woc_dummy_4;    // 0xCA3A_7110
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O26A0_T    crg_top_woc_dummy_5;    // 0xCA3A_7114
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O26A0_T    crg_top_woc_dummy_6;    // 0xCA3A_7118
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O26A0_T    crg_top_woc_dummy_7;    // 0xCA3A_711C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O26A0_T    crg_top_woc_dummy_8;    // 0xCA3A_7120
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O26A0_T    crg_top_woc_dummy_9;    // 0xCA3A_7124
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O26A0_T    crg_top_woc_dummy_10;    // 0xCA3A_7128
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O26A0_T    crg_top_woc_dummy_11;    // 0xCA3A_712C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O26A0_T    crg_top_woc_dummy_12;    // 0xCA3A_7130
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O26A0_T    crg_top_woc_dummy_13;    // 0xCA3A_7134
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O26A0_T    crg_top_woc_dummy_14;    // 0xCA3A_7138
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O26A0_T    crg_top_woc_dummy_15;    // 0xCA3A_713C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O26A0_T    crg_top_woc_dummy_16;    // 0xCA3A_7140
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O26A0_T    crg_top_woc_dummy_17;    // 0xCA3A_7144
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O26A0_T    crg_top_woc_dummy_18;    // 0xCA3A_7148
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O26A0_T    crg_top_woc_dummy_19;    // 0xCA3A_714C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O26A0_T    crg_top_woc_dummy_20;    // 0xCA3A_7150
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O26A0_T    crg_top_woc_dummy_21;    // 0xCA3A_7154
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O26A0_T    crg_top_woc_dummy_22;    // 0xCA3A_7158
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O26A0_T    crg_top_woc_dummy_23;    // 0xCA3A_715C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O26A0_T    crg_top_woc_dummy_24;    // 0xCA3A_7160
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O26A0_T    crg_top_woc_dummy_25;    // 0xCA3A_7164
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O26A0_T    crg_top_woc_dummy_26;    // 0xCA3A_7168
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O26A0_T    crg_top_woc_dummy_27;    // 0xCA3A_716C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O26A0_T    crg_top_woc_dummy_28;    // 0xCA3A_7170
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O26A0_T    crg_top_woc_dummy_29;    // 0xCA3A_7174
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O26A0_T    crg_top_woc_dummy_30;    // 0xCA3A_7178
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O26A0_T    crg_top_woc_dummy_31;    // 0xCA3A_717C
}MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T;
/* 47 regs */

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

#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O26A0_T_OFF  (BASEADDRESS+0x0000)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O26A0_T_OFF  (BASEADDRESS+0x0004)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O26A0_T_OFF  (BASEADDRESS+0x0008)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O26A0_T_OFF  (BASEADDRESS+0x000C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O26A0_T_OFF  (BASEADDRESS+0x0010)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O26A0_T_OFF  (BASEADDRESS+0x0014)
#define MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O26A0_T_OFF        (BASEADDRESS+0x0018)
#define MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O26A0_T_OFF        (BASEADDRESS+0x001C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O26A0_T_OFF  (BASEADDRESS+0x0024)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O26A0_T_OFF  (BASEADDRESS+0x0028)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O26A0_T_OFF  (BASEADDRESS+0x0030)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O26A0_T_OFF  (BASEADDRESS+0x0034)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O26A0_T_OFF  (BASEADDRESS+0x0038)
#define MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_TOP_O26A0_T_OFF(BASEADDRESS+0x0040)
#define MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_BOT_O26A0_T_OFF(BASEADDRESS+0x0044)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O26A0_T_OFF(BASEADDRESS+0x0100)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O26A0_T_OFF(BASEADDRESS+0x0104)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O26A0_T_OFF(BASEADDRESS+0x0108)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O26A0_T_OFF(BASEADDRESS+0x010C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O26A0_T_OFF(BASEADDRESS+0x0110)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O26A0_T_OFF(BASEADDRESS+0x0114)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O26A0_T_OFF(BASEADDRESS+0x0118)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O26A0_T_OFF(BASEADDRESS+0x011C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O26A0_T_OFF(BASEADDRESS+0x0120)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O26A0_T_OFF(BASEADDRESS+0x0124)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O26A0_T_OFF(BASEADDRESS+0x0128)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O26A0_T_OFF(BASEADDRESS+0x012C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O26A0_T_OFF(BASEADDRESS+0x0130)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O26A0_T_OFF(BASEADDRESS+0x0134)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O26A0_T_OFF(BASEADDRESS+0x0138)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O26A0_T_OFF(BASEADDRESS+0x013C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O26A0_T_OFF(BASEADDRESS+0x0140)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O26A0_T_OFF(BASEADDRESS+0x0144)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O26A0_T_OFF(BASEADDRESS+0x0148)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O26A0_T_OFF(BASEADDRESS+0x014C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O26A0_T_OFF(BASEADDRESS+0x0150)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O26A0_T_OFF(BASEADDRESS+0x0154)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O26A0_T_OFF(BASEADDRESS+0x0158)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O26A0_T_OFF(BASEADDRESS+0x015C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O26A0_T_OFF(BASEADDRESS+0x0160)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O26A0_T_OFF(BASEADDRESS+0x0164)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O26A0_T_OFF(BASEADDRESS+0x0168)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O26A0_T_OFF(BASEADDRESS+0x016C)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O26A0_T_OFF(BASEADDRESS+0x0170)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O26A0_T_OFF(BASEADDRESS+0x0174)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O26A0_T_OFF(BASEADDRESS+0x0178)
#define MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O26A0_T_OFF(BASEADDRESS+0x017C)

/*-----------------------------------------------------------------------------------------
    0xCA3A_7000    crg_top_woc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_only_watchdog_rst: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7004    crg_top_woc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_watchdog_reset_disable: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7008    crg_top_woc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wdt_reset_mux_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_700C    crg_top_woc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_crg_top_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7010    crg_top_woc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7014    crg_top_woc_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7018    nisol_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_edid     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_701C    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_woc      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7024    crg_top_woc_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_from_micom: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7028    crg_top_woc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_woc      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7030    crg_top_woc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_reg33to18075_lv_d075: 4;    //  3:0
    UINT32 reg_reg33to18075_lv_d18: 4;    //  7:4
    UINT32 resvd00            :  8;    //  15: 8 reserved
    UINT32 reg_reg33to18075_lv_d075_sel: 1;    //  16
    UINT32 resvd01            :  3;    //  19:17 reserved
    UINT32 reg_reg33to18075_lv_d18_sel: 1;    //  20
    UINT32 resvd02            : 11;    //  31:21 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7034    crg_top_woc_r11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 efv_reg33to18075_lv_d075: 4;    //  3:0
    UINT32 efv_reg33to18075_lv_d18: 4;    //  7:4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7038    crg_top_woc_r12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rst_cpuav_i_ldo_woc: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7040    txp_clkdrv_dual_top ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_dual_top_pdb: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_dual_top_icon0: 2;    //  5:4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_txclkdrv_dual_top_icon1: 2;    //  9:8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_txclkdrv_dual_top_sel0: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_txclkdrv_dual_top_sel1: 1;    //  16
    UINT32 resvd04            : 15;    //  31:17 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_TOP_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7044    txp_clkdrv_dual_bot ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_dual_bot_pdb: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_dual_bot_icon0: 2;    //  5:4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_txclkdrv_dual_bot_icon1: 2;    //  9:8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_txclkdrv_dual_bot_sel0: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_txclkdrv_dual_bot_sel1: 1;    //  16
    UINT32 resvd04            : 15;    //  31:17 reserved
    };
}MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_BOT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7100    crg_top_woc_dummy_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_0: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7104    crg_top_woc_dummy_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_1: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7108    crg_top_woc_dummy_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_2: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_710C    crg_top_woc_dummy_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_3: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7110    crg_top_woc_dummy_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_4: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7114    crg_top_woc_dummy_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_5: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7118    crg_top_woc_dummy_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_6: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_711C    crg_top_woc_dummy_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_7: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7120    crg_top_woc_dummy_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_8: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7124    crg_top_woc_dummy_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_9: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7128    crg_top_woc_dummy_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_10: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_712C    crg_top_woc_dummy_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_11: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7130    crg_top_woc_dummy_12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_12: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7134    crg_top_woc_dummy_13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_13: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7138    crg_top_woc_dummy_14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_14: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_713C    crg_top_woc_dummy_15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_15: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7140    crg_top_woc_dummy_16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_16: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7144    crg_top_woc_dummy_17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_17: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7148    crg_top_woc_dummy_18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_18: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_714C    crg_top_woc_dummy_19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_19: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7150    crg_top_woc_dummy_20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_20: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7154    crg_top_woc_dummy_21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_21: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7158    crg_top_woc_dummy_22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_22: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_715C    crg_top_woc_dummy_23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_23: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7160    crg_top_woc_dummy_24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_24: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7164    crg_top_woc_dummy_25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_25: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7168    crg_top_woc_dummy_26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_26: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_716C    crg_top_woc_dummy_27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_27: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7170    crg_top_woc_dummy_28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_28: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7174    crg_top_woc_dummy_29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_29: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_7178    crg_top_woc_dummy_30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_30: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_717C    crg_top_woc_dummy_31 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_non_reset_dummy_31: 32;    //  31:0
    };
}MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_crg_top_woc_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R00_O26A0_T    crg_top_woc_r00;    // 0xCA3A_7000
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R01_O26A0_T    crg_top_woc_r01;    // 0xCA3A_7004
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R02_O26A0_T    crg_top_woc_r02;    // 0xCA3A_7008
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R03_O26A0_T    crg_top_woc_r03;    // 0xCA3A_700C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R04_O26A0_T    crg_top_woc_r04;    // 0xCA3A_7010
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R05_O26A0_T    crg_top_woc_r05;    // 0xCA3A_7014
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R00_O26A0_T    nisol_r00;      // 0xCA3A_7018
    MICOM_CRG_TOP_WOC_CTRL_NISOL_R01_O26A0_T    nisol_r01;      // 0xCA3A_701C
    UINT32                             _rsvd_00[1];             // 0xCA3A_7020
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R06_O26A0_T    crg_top_woc_r06;    // 0xCA3A_7024
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R07_O26A0_T    crg_top_woc_r07;    // 0xCA3A_7028
    UINT32                             _rsvd_01[1];             // 0xCA3A_702C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R10_O26A0_T    crg_top_woc_r10;    // 0xCA3A_7030
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R11_O26A0_T    crg_top_woc_r11;    // 0xCA3A_7034
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_R12_O26A0_T    crg_top_woc_r12;    // 0xCA3A_7038
    UINT32                             _rsvd_02[1];             // 0xCA3A_703C
    MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_TOP_O26A0_T    txp_clkdrv_dual_top;    // 0xCA3A_7040
    MICOM_CRG_TOP_WOC_CTRL_TXP_CLKDRV_DUAL_BOT_O26A0_T    txp_clkdrv_dual_bot;    // 0xCA3A_7044
    UINT32                             _rsvd_03[46];            // 0xCA3A_7048 ~ 0xCA3A_70FC
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_0_O26A0_T    crg_top_woc_dummy_0;    // 0xCA3A_7100
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_1_O26A0_T    crg_top_woc_dummy_1;    // 0xCA3A_7104
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_2_O26A0_T    crg_top_woc_dummy_2;    // 0xCA3A_7108
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_3_O26A0_T    crg_top_woc_dummy_3;    // 0xCA3A_710C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_4_O26A0_T    crg_top_woc_dummy_4;    // 0xCA3A_7110
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_5_O26A0_T    crg_top_woc_dummy_5;    // 0xCA3A_7114
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_6_O26A0_T    crg_top_woc_dummy_6;    // 0xCA3A_7118
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_7_O26A0_T    crg_top_woc_dummy_7;    // 0xCA3A_711C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_8_O26A0_T    crg_top_woc_dummy_8;    // 0xCA3A_7120
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_9_O26A0_T    crg_top_woc_dummy_9;    // 0xCA3A_7124
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_10_O26A0_T    crg_top_woc_dummy_10;    // 0xCA3A_7128
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_11_O26A0_T    crg_top_woc_dummy_11;    // 0xCA3A_712C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_12_O26A0_T    crg_top_woc_dummy_12;    // 0xCA3A_7130
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_13_O26A0_T    crg_top_woc_dummy_13;    // 0xCA3A_7134
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_14_O26A0_T    crg_top_woc_dummy_14;    // 0xCA3A_7138
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_15_O26A0_T    crg_top_woc_dummy_15;    // 0xCA3A_713C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_16_O26A0_T    crg_top_woc_dummy_16;    // 0xCA3A_7140
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_17_O26A0_T    crg_top_woc_dummy_17;    // 0xCA3A_7144
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_18_O26A0_T    crg_top_woc_dummy_18;    // 0xCA3A_7148
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_19_O26A0_T    crg_top_woc_dummy_19;    // 0xCA3A_714C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_20_O26A0_T    crg_top_woc_dummy_20;    // 0xCA3A_7150
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_21_O26A0_T    crg_top_woc_dummy_21;    // 0xCA3A_7154
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_22_O26A0_T    crg_top_woc_dummy_22;    // 0xCA3A_7158
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_23_O26A0_T    crg_top_woc_dummy_23;    // 0xCA3A_715C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_24_O26A0_T    crg_top_woc_dummy_24;    // 0xCA3A_7160
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_25_O26A0_T    crg_top_woc_dummy_25;    // 0xCA3A_7164
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_26_O26A0_T    crg_top_woc_dummy_26;    // 0xCA3A_7168
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_27_O26A0_T    crg_top_woc_dummy_27;    // 0xCA3A_716C
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_28_O26A0_T    crg_top_woc_dummy_28;    // 0xCA3A_7170
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_29_O26A0_T    crg_top_woc_dummy_29;    // 0xCA3A_7174
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_30_O26A0_T    crg_top_woc_dummy_30;    // 0xCA3A_7178
    MICOM_CRG_TOP_WOC_CTRL_CRG_TOP_WOC_DUMMY_31_O26A0_T    crg_top_woc_dummy_31;    // 0xCA3A_717C
}MICOM_CRG_TOP_WOC_CTRL_REG_O26A0_T;
/* 47 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_CRG_TOP_WOC_CTRL_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

