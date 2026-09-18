#ifndef _CTOP_SYN_WOV_E60A0_REG_H_
#define _CTOP_SYN_WOV_E60A0_REG_H_

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
    0xF301_1400    syn_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__ls_disable_aud   :  1,    //      0
    reg_wov__ls_disable_micom :  1,    //      1
    reg_wov__ls_disable_wov   :  1,    //      2
                              : 29;    //   31:3 reserved
}CTOP_WOV_SYN_WOV00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1404    syn_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__m2_apb4_s0_prt   :  4,    //   3: 0
    reg_wov__m2_apb4_s1_prt   :  4,    //   7: 4
    reg_wov__m2_apb4_s2_prt   :  4,    //  11: 8
    reg_wov__m2_apb4_s3_prt   :  4,    //  15:12
    reg_wov__m2_apb4_s4_prt   :  4,    //  19:16
                              : 12;    //  31:20 reserved
}CTOP_WOV_SYN_WOV01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1408    syn_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__swrst_aud0_data  :  1,    //      0
    reg_wov__swrst_aud1_data  :  1,    //      1
    reg_wov__swrst_stcc01_data:  1,    //      2
    reg_wov__swrst_stcc23_data:  1,    //      3
                              : 28;    //   31:4 reserved
}CTOP_WOV_SYN_WOV02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_140C    syn_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__micom_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_wov__micom_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_wov__micom_ar_ag      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_wov__micom_aw_ag      :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_WOV_SYN_WOV03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1410    syn_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__micom_flush_en   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1414    syn_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__micom_flush_done :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1418    syn_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__ddr_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_wov__ddr_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_wov__ddr_ar_ag        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_wov__ddr_aw_ag        :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_WOV_SYN_WOV06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_141C    syn_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__ddr_flush_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1420    syn_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__ddr_flush_done   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1424    syn_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__aud_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_wov__aud_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_wov__aud_ar_ag        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_wov__aud_aw_ag        :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_WOV_SYN_WOV09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1428    syn_wov10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__aud_flush_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_142C    syn_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__aud_flush_done   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1430    syn_wov12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_wov__wov_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_wov__wov_ar_ag        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_wov__wov_aw_ag        :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_WOV_SYN_WOV12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1434    syn_wov13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_flush_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1438    syn_wov14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_flush_done   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV14_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_143C    syn_wov16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    nisol_en                  :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV16_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1440    syn_wov17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__sel0_aclk_div    :  3,    //   2: 0
    reg_wov__sel0_aclk_src    :  4,    //   6: 3
    reg_wov__sel1_aclk_div    :  3,    //   9: 7
    reg_wov__sel1_aclk_src    :  4,    //  13:10
    reg_wov__sel2_aclk_div    :  3,    //  16:14
    reg_wov__sel2_aclk_src    :  4,    //  20:17
    reg_wov__sel3_aclk_div    :  3,    //  23:21
    reg_wov__sel3_aclk_src    :  4,    //  27:24
                              :  4;    //  31:28 reserved
}CTOP_WOV_SYN_WOV17_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1444    syn_wov18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__adto0_swrst_adto :  1,    //      0
    reg_wov__adto1_swrst_adto :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_WOV_SYN_WOV18_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1448    syn_wov19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__outclk_en_0      :  1,    //      0
    reg_wov__outclk_en_1      :  1,    //      1
    reg_wov__outclk_en_2      :  1,    //      2
                              : 29;    //   31:3 reserved
}CTOP_WOV_SYN_WOV19_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_144C    syn_wov20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__outclk_div_0     : 10,    //   9: 0
    reg_wov__outclk_div_1     : 10,    //  19:10
    reg_wov__outclk_div_2     : 10,    //  29:20
                              :  2;    //  31:30 reserved
}CTOP_WOV_SYN_WOV20_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1450    syn_wov21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_daclrck__st       :  1,    //      0
    reg_pad_daclrck__pu       :  1,    //      1
    reg_pad_daclrck__pd       :  1,    //      2
    reg_pad_daclrck__ds3      :  1,    //      3
    reg_pad_daclrck__ds2      :  1,    //      4
    reg_pad_daclrck__ds1      :  1,    //      5
    reg_pad_daclrck__ds0      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_daclrch__st       :  1,    //      8
    reg_pad_daclrch__pu       :  1,    //      9
    reg_pad_daclrch__pd       :  1,    //     10
    reg_pad_daclrch__ds3      :  1,    //     11
    reg_pad_daclrch__ds2      :  1,    //     12
    reg_pad_daclrch__ds1      :  1,    //     13
    reg_pad_daclrch__ds0      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_audclk_out__st    :  1,    //     16
    reg_pad_audclk_out__pu    :  1,    //     17
    reg_pad_audclk_out__pd    :  1,    //     18
    reg_pad_audclk_out__ds3   :  1,    //     19
    reg_pad_audclk_out__ds2   :  1,    //     20
    reg_pad_audclk_out__ds1   :  1,    //     21
    reg_pad_audclk_out__ds0   :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_WOV_SYN_WOV21_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1454    syn_wov22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_01__st      :  1,    //      0
    reg_pad_micom_01__pu      :  1,    //      1
    reg_pad_micom_01__pd      :  1,    //      2
    reg_pad_micom_01__ds3     :  1,    //      3
    reg_pad_micom_01__ds2     :  1,    //      4
    reg_pad_micom_01__ds1     :  1,    //      5
    reg_pad_micom_01__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_00__st      :  1,    //      8
    reg_pad_micom_00__pu      :  1,    //      9
    reg_pad_micom_00__pd      :  1,    //     10
    reg_pad_micom_00__ds3     :  1,    //     11
    reg_pad_micom_00__ds2     :  1,    //     12
    reg_pad_micom_00__ds1     :  1,    //     13
    reg_pad_micom_00__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_cec__st      :  1,    //     16
    reg_pad_hdmi_cec__pu      :  1,    //     17
    reg_pad_hdmi_cec__pd      :  1,    //     18
    reg_pad_hdmi_cec__ds3     :  1,    //     19
    reg_pad_hdmi_cec__ds2     :  1,    //     20
    reg_pad_hdmi_cec__ds1     :  1,    //     21
    reg_pad_hdmi_cec__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dacsck__st        :  1,    //     24
    reg_pad_dacsck__pu        :  1,    //     25
    reg_pad_dacsck__pd        :  1,    //     26
    reg_pad_dacsck__ds3       :  1,    //     27
    reg_pad_dacsck__ds2       :  1,    //     28
    reg_pad_dacsck__ds1       :  1,    //     29
    reg_pad_dacsck__ds0       :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV22_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1458    syn_wov23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_05__st      :  1,    //      0
    reg_pad_micom_05__pu      :  1,    //      1
    reg_pad_micom_05__pd      :  1,    //      2
    reg_pad_micom_05__ds3     :  1,    //      3
    reg_pad_micom_05__ds2     :  1,    //      4
    reg_pad_micom_05__ds1     :  1,    //      5
    reg_pad_micom_05__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_04__st      :  1,    //      8
    reg_pad_micom_04__pu      :  1,    //      9
    reg_pad_micom_04__pd      :  1,    //     10
    reg_pad_micom_04__ds3     :  1,    //     11
    reg_pad_micom_04__ds2     :  1,    //     12
    reg_pad_micom_04__ds1     :  1,    //     13
    reg_pad_micom_04__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_03__st      :  1,    //     16
    reg_pad_micom_03__pu      :  1,    //     17
    reg_pad_micom_03__pd      :  1,    //     18
    reg_pad_micom_03__ds3     :  1,    //     19
    reg_pad_micom_03__ds2     :  1,    //     20
    reg_pad_micom_03__ds1     :  1,    //     21
    reg_pad_micom_03__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_02__st      :  1,    //     24
    reg_pad_micom_02__pu      :  1,    //     25
    reg_pad_micom_02__pd      :  1,    //     26
    reg_pad_micom_02__ds3     :  1,    //     27
    reg_pad_micom_02__ds2     :  1,    //     28
    reg_pad_micom_02__ds1     :  1,    //     29
    reg_pad_micom_02__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV23_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_145C    syn_wov24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_09__st      :  1,    //      0
    reg_pad_micom_09__pu      :  1,    //      1
    reg_pad_micom_09__pd      :  1,    //      2
    reg_pad_micom_09__ds3     :  1,    //      3
    reg_pad_micom_09__ds2     :  1,    //      4
    reg_pad_micom_09__ds1     :  1,    //      5
    reg_pad_micom_09__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_08__st      :  1,    //      8
    reg_pad_micom_08__pu      :  1,    //      9
    reg_pad_micom_08__pd      :  1,    //     10
    reg_pad_micom_08__ds3     :  1,    //     11
    reg_pad_micom_08__ds2     :  1,    //     12
    reg_pad_micom_08__ds1     :  1,    //     13
    reg_pad_micom_08__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_07__st      :  1,    //     16
    reg_pad_micom_07__pu      :  1,    //     17
    reg_pad_micom_07__pd      :  1,    //     18
    reg_pad_micom_07__ds3     :  1,    //     19
    reg_pad_micom_07__ds2     :  1,    //     20
    reg_pad_micom_07__ds1     :  1,    //     21
    reg_pad_micom_07__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_06__st      :  1,    //     24
    reg_pad_micom_06__pu      :  1,    //     25
    reg_pad_micom_06__pd      :  1,    //     26
    reg_pad_micom_06__ds3     :  1,    //     27
    reg_pad_micom_06__ds2     :  1,    //     28
    reg_pad_micom_06__ds1     :  1,    //     29
    reg_pad_micom_06__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV24_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1460    syn_wov25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_13__st      :  1,    //      0
    reg_pad_micom_13__pu      :  1,    //      1
    reg_pad_micom_13__pd      :  1,    //      2
    reg_pad_micom_13__ds3     :  1,    //      3
    reg_pad_micom_13__ds2     :  1,    //      4
    reg_pad_micom_13__ds1     :  1,    //      5
    reg_pad_micom_13__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_12__st      :  1,    //      8
    reg_pad_micom_12__pu      :  1,    //      9
    reg_pad_micom_12__pd      :  1,    //     10
    reg_pad_micom_12__ds3     :  1,    //     11
    reg_pad_micom_12__ds2     :  1,    //     12
    reg_pad_micom_12__ds1     :  1,    //     13
    reg_pad_micom_12__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_11__st      :  1,    //     16
    reg_pad_micom_11__pu      :  1,    //     17
    reg_pad_micom_11__pd      :  1,    //     18
    reg_pad_micom_11__ds3     :  1,    //     19
    reg_pad_micom_11__ds2     :  1,    //     20
    reg_pad_micom_11__ds1     :  1,    //     21
    reg_pad_micom_11__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_10__st      :  1,    //     24
    reg_pad_micom_10__pu      :  1,    //     25
    reg_pad_micom_10__pd      :  1,    //     26
    reg_pad_micom_10__ds3     :  1,    //     27
    reg_pad_micom_10__ds2     :  1,    //     28
    reg_pad_micom_10__ds1     :  1,    //     29
    reg_pad_micom_10__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV25_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1464    syn_wov26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_17__st      :  1,    //      0
    reg_pad_micom_17__pu      :  1,    //      1
    reg_pad_micom_17__pd      :  1,    //      2
    reg_pad_micom_17__ds3     :  1,    //      3
    reg_pad_micom_17__ds2     :  1,    //      4
    reg_pad_micom_17__ds1     :  1,    //      5
    reg_pad_micom_17__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_16__st      :  1,    //      8
    reg_pad_micom_16__pu      :  1,    //      9
    reg_pad_micom_16__pd      :  1,    //     10
    reg_pad_micom_16__ds3     :  1,    //     11
    reg_pad_micom_16__ds2     :  1,    //     12
    reg_pad_micom_16__ds1     :  1,    //     13
    reg_pad_micom_16__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_15__st      :  1,    //     16
    reg_pad_micom_15__pu      :  1,    //     17
    reg_pad_micom_15__pd      :  1,    //     18
    reg_pad_micom_15__ds3     :  1,    //     19
    reg_pad_micom_15__ds2     :  1,    //     20
    reg_pad_micom_15__ds1     :  1,    //     21
    reg_pad_micom_15__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_14__st      :  1,    //     24
    reg_pad_micom_14__pu      :  1,    //     25
    reg_pad_micom_14__pd      :  1,    //     26
    reg_pad_micom_14__ds3     :  1,    //     27
    reg_pad_micom_14__ds2     :  1,    //     28
    reg_pad_micom_14__ds1     :  1,    //     29
    reg_pad_micom_14__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV26_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1468    syn_wov27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_21__st      :  1,    //      0
    reg_pad_micom_21__pu      :  1,    //      1
    reg_pad_micom_21__pd      :  1,    //      2
    reg_pad_micom_21__ds3     :  1,    //      3
    reg_pad_micom_21__ds2     :  1,    //      4
    reg_pad_micom_21__ds1     :  1,    //      5
    reg_pad_micom_21__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_20__st      :  1,    //      8
    reg_pad_micom_20__pu      :  1,    //      9
    reg_pad_micom_20__pd      :  1,    //     10
    reg_pad_micom_20__ds3     :  1,    //     11
    reg_pad_micom_20__ds2     :  1,    //     12
    reg_pad_micom_20__ds1     :  1,    //     13
    reg_pad_micom_20__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_19__st      :  1,    //     16
    reg_pad_micom_19__pu      :  1,    //     17
    reg_pad_micom_19__pd      :  1,    //     18
    reg_pad_micom_19__ds3     :  1,    //     19
    reg_pad_micom_19__ds2     :  1,    //     20
    reg_pad_micom_19__ds1     :  1,    //     21
    reg_pad_micom_19__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_18__st      :  1,    //     24
    reg_pad_micom_18__pu      :  1,    //     25
    reg_pad_micom_18__pd      :  1,    //     26
    reg_pad_micom_18__ds3     :  1,    //     27
    reg_pad_micom_18__ds2     :  1,    //     28
    reg_pad_micom_18__ds1     :  1,    //     29
    reg_pad_micom_18__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV27_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_146C    syn_wov28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_25__st      :  1,    //      0
    reg_pad_micom_25__pu      :  1,    //      1
    reg_pad_micom_25__pd      :  1,    //      2
    reg_pad_micom_25__ds3     :  1,    //      3
    reg_pad_micom_25__ds2     :  1,    //      4
    reg_pad_micom_25__ds1     :  1,    //      5
    reg_pad_micom_25__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_24__st      :  1,    //      8
    reg_pad_micom_24__pu      :  1,    //      9
    reg_pad_micom_24__pd      :  1,    //     10
    reg_pad_micom_24__ds3     :  1,    //     11
    reg_pad_micom_24__ds2     :  1,    //     12
    reg_pad_micom_24__ds1     :  1,    //     13
    reg_pad_micom_24__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_23__st      :  1,    //     16
    reg_pad_micom_23__pu      :  1,    //     17
    reg_pad_micom_23__pd      :  1,    //     18
    reg_pad_micom_23__ds3     :  1,    //     19
    reg_pad_micom_23__ds2     :  1,    //     20
    reg_pad_micom_23__ds1     :  1,    //     21
    reg_pad_micom_23__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_22__st      :  1,    //     24
    reg_pad_micom_22__pu      :  1,    //     25
    reg_pad_micom_22__pd      :  1,    //     26
    reg_pad_micom_22__ds3     :  1,    //     27
    reg_pad_micom_22__ds2     :  1,    //     28
    reg_pad_micom_22__ds1     :  1,    //     29
    reg_pad_micom_22__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV28_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1470    syn_wov29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_clk__st :  1,    //      0
    reg_pad_micom_spi_clk__pu :  1,    //      1
    reg_pad_micom_spi_clk__pd :  1,    //      2
    reg_pad_micom_spi_clk__ds3:  1,    //      3
    reg_pad_micom_spi_clk__ds2:  1,    //      4
    reg_pad_micom_spi_clk__ds1:  1,    //      5
    reg_pad_micom_spi_clk__ds0:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_boot_mode__st: 1,    //      8
    reg_pad_micom_boot_mode__pu: 1,    //      9
    reg_pad_micom_boot_mode__pd: 1,    //     10
    reg_pad_micom_boot_mode__ds3: 1,    //    11
    reg_pad_micom_boot_mode__ds2: 1,    //    12
    reg_pad_micom_boot_mode__ds1: 1,    //    13
    reg_pad_micom_boot_mode__ds0: 1,    //    14
                              :  1,    //     15 reserved
    reg_pad_micom_27__st      :  1,    //     16
    reg_pad_micom_27__pu      :  1,    //     17
    reg_pad_micom_27__pd      :  1,    //     18
    reg_pad_micom_27__ds3     :  1,    //     19
    reg_pad_micom_27__ds2     :  1,    //     20
    reg_pad_micom_27__ds1     :  1,    //     21
    reg_pad_micom_27__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_26__st      :  1,    //     24
    reg_pad_micom_26__pu      :  1,    //     25
    reg_pad_micom_26__pd      :  1,    //     26
    reg_pad_micom_26__ds3     :  1,    //     27
    reg_pad_micom_26__ds2     :  1,    //     28
    reg_pad_micom_26__ds1     :  1,    //     29
    reg_pad_micom_26__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV29_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1474    syn_wov30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_opm__st           :  1,    //      0
    reg_pad_opm__ds3          :  1,    //      1
    reg_pad_opm__ds2          :  1,    //      2
    reg_pad_opm__ds1          :  1,    //      3
    reg_pad_opm__ds0          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_spi_do__st  :  1,    //      8
    reg_pad_micom_spi_do__pu  :  1,    //      9
    reg_pad_micom_spi_do__pd  :  1,    //     10
    reg_pad_micom_spi_do__ds3 :  1,    //     11
    reg_pad_micom_spi_do__ds2 :  1,    //     12
    reg_pad_micom_spi_do__ds1 :  1,    //     13
    reg_pad_micom_spi_do__ds0 :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_spi_di__st  :  1,    //     16
    reg_pad_micom_spi_di__pu  :  1,    //     17
    reg_pad_micom_spi_di__pd  :  1,    //     18
    reg_pad_micom_spi_di__ds3 :  1,    //     19
    reg_pad_micom_spi_di__ds2 :  1,    //     20
    reg_pad_micom_spi_di__ds1 :  1,    //     21
    reg_pad_micom_spi_di__ds0 :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_spi_cs__st  :  1,    //     24
    reg_pad_micom_spi_cs__pu  :  1,    //     25
    reg_pad_micom_spi_cs__pd  :  1,    //     26
    reg_pad_micom_spi_cs__ds3 :  1,    //     27
    reg_pad_micom_spi_cs__ds2 :  1,    //     28
    reg_pad_micom_spi_cs__ds1 :  1,    //     29
    reg_pad_micom_spi_cs__ds0 :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_WOV_SYN_WOV30_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1478    syn_wov31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm1_datain__st: 1,    //      0
    reg_pad_wov_pdm1_datain__pu: 1,    //      1
    reg_pad_wov_pdm1_datain__pd: 1,    //      2
    reg_pad_wov_pdm1_datain__ds3: 1,    //     3
    reg_pad_wov_pdm1_datain__ds2: 1,    //     4
    reg_pad_wov_pdm1_datain__ds1: 1,    //     5
    reg_pad_wov_pdm1_datain__ds0: 1,    //     6
                              :  1,    //      7 reserved
    reg_pad_wov_pdm0_datain__st: 1,    //      8
    reg_pad_wov_pdm0_datain__pu: 1,    //      9
    reg_pad_wov_pdm0_datain__pd: 1,    //     10
    reg_pad_wov_pdm0_datain__ds3: 1,    //    11
    reg_pad_wov_pdm0_datain__ds2: 1,    //    12
    reg_pad_wov_pdm0_datain__ds1: 1,    //    13
    reg_pad_wov_pdm0_datain__ds0: 1,    //    14
                              :  1,    //     15 reserved
    reg_pad_wov_pdm_clkout__st:  1,    //     16
    reg_pad_wov_pdm_clkout__pu:  1,    //     17
    reg_pad_wov_pdm_clkout__pd:  1,    //     18
    reg_pad_wov_pdm_clkout__ds3: 1,    //     19
    reg_pad_wov_pdm_clkout__ds2: 1,    //     20
    reg_pad_wov_pdm_clkout__ds1: 1,    //     21
    reg_pad_wov_pdm_clkout__ds0: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pores_n__st       :  1,    //     24
    reg_pad_pores_n__ds3      :  1,    //     25
    reg_pad_pores_n__ds2      :  1,    //     26
    reg_pad_pores_n__ds1      :  1,    //     27
    reg_pad_pores_n__ds0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_WOV_SYN_WOV31_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_147C    syn_wov32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_02_mux_sel  :  4,    //   3: 0
    reg_pad_micom_01_mux_sel  :  4,    //   7: 4
    reg_pad_micom_00_mux_sel  :  4,    //  11: 8
    reg_pad_hdmi_cec_mux_sel  :  4,    //  15:12
    reg_pad_dacsck_mux_sel    :  4,    //  19:16
    reg_pad_daclrck_mux_sel   :  4,    //  23:20
    reg_pad_daclrch_mux_sel   :  4,    //  27:24
    reg_pad_audclk_out_mux_sel:  4;    //  31:28
}CTOP_WOV_SYN_WOV32_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1480    syn_wov33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_10_mux_sel  :  4,    //   3: 0
    reg_pad_micom_09_mux_sel  :  4,    //   7: 4
    reg_pad_micom_08_mux_sel  :  4,    //  11: 8
    reg_pad_micom_07_mux_sel  :  4,    //  15:12
    reg_pad_micom_06_mux_sel  :  4,    //  19:16
    reg_pad_micom_05_mux_sel  :  4,    //  23:20
    reg_pad_micom_04_mux_sel  :  4,    //  27:24
    reg_pad_micom_03_mux_sel  :  4;    //  31:28
}CTOP_WOV_SYN_WOV33_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1484    syn_wov34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_18_mux_sel  :  4,    //   3: 0
    reg_pad_micom_17_mux_sel  :  4,    //   7: 4
    reg_pad_micom_16_mux_sel  :  4,    //  11: 8
    reg_pad_micom_15_mux_sel  :  4,    //  15:12
    reg_pad_micom_14_mux_sel  :  4,    //  19:16
    reg_pad_micom_13_mux_sel  :  4,    //  23:20
    reg_pad_micom_12_mux_sel  :  4,    //  27:24
    reg_pad_micom_11_mux_sel  :  4;    //  31:28
}CTOP_WOV_SYN_WOV34_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1488    syn_wov35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_26_mux_sel  :  4,    //   3: 0
    reg_pad_micom_25_mux_sel  :  4,    //   7: 4
    reg_pad_micom_24_mux_sel  :  4,    //  11: 8
    reg_pad_micom_23_mux_sel  :  4,    //  15:12
    reg_pad_micom_22_mux_sel  :  4,    //  19:16
    reg_pad_micom_21_mux_sel  :  4,    //  23:20
    reg_pad_micom_20_mux_sel  :  4,    //  27:24
    reg_pad_micom_19_mux_sel  :  4;    //  31:28
}CTOP_WOV_SYN_WOV35_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_148C    syn_wov36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm0_datain_mux_sel: 4,    //  3:0
    reg_pad_wov_pdm_clkout_mux_sel: 4,    //  7:4
    reg_pad_micom_spi_do_mux_sel: 4,    //  11:8
    reg_pad_micom_spi_di_mux_sel: 4,    //  15:12
    reg_pad_micom_spi_cs_mux_sel: 4,    //  19:16
    reg_pad_micom_spi_clk_mux_sel: 4,    //  23:20
    reg_pad_micom_boot_mode_mux_sel: 4,    //  27:24
    reg_pad_micom_27_mux_sel  :  4;    //  31:28
}CTOP_WOV_SYN_WOV36_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1490    syn_wov37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_uart_sel1       :  4,    //   3: 0
    reg_micom_uart_sel0       :  4,    //   7: 4
    reg_pad_wov_pdm1_datain_mux_sel: 4,    //  11:8
                              : 20;    //  31:12 reserved
}CTOP_WOV_SYN_WOV37_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1494    syn_wov38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__aiopll_wov_pdb_ctrl: 1,    //     0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV38_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1498    syn_wov39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__sw_reset_mux_sel :  1,    //      0
    reg_wov__wdt_reset_mux_sel:  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_WOV_SYN_WOV39_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_149C    syn_wov40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_wov_d100        :  1,    //      0
    reg_swrst_wov             :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_WOV_SYN_WOV40_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14A0    syn_wov41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__awaddr_s2_aud    :  2,    //   1: 0
    reg_wov__araddr_s2_aud    :  2,    //   3: 2
    reg_wov__awaddr_s1_wov    :  2,    //   5: 4
    reg_wov__araddr_s1_wov    :  2,    //   7: 6
                              : 24;    //   31:8 reserved
}CTOP_WOV_SYN_WOV41_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14A4    syn_wov42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__aclk_out_sel0_div:  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_wov__aclk_out_sel0_src:  4,    //   7: 4
    reg_wov__aclk_out_sel1_div:  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_wov__aclk_out_sel1_src:  4,    //  15:12
    reg_wov__aud_clk_out_0_inv_sel: 1,    //  16
    reg_wov__aud_clk_out_1_inv_sel: 1,    //  17
    reg_wov__aud_clk_out_sel  :  1,    //     18
                              : 13;    //  31:19 reserved
}CTOP_WOV_SYN_WOV42_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14A8    frpll00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_apll_frpll_in_divsel  :  1,    //      1
    reg_apll_frpll_lpf_on     :  1,    //      2
    reg_apll_frpll_fout2_en   :  1,    //      3
    reg_apll_frpll_wakeup_bypass: 1,    //     4
    reg_apll_frpll_divint     :  9,    //  13: 5
                              :  1,    //     14 reserved
    reg_apll_frpll_dsmon      :  1,    //     15
    reg_apll_frpll_auto_freq  :  1,    //     16
    reg_apll_frpll_dsm_limit  :  1,    //     17
    reg_apll_frpll_fin_sel    :  1,    //     18
    reg_apll_frpll_icp        :  4,    //  22:19
    reg_apll_frpll_out_div    :  9;    //  31:23
}CTOP_WOV_FRPLL00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14AC    frpll01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fout_en    :  1,    //      0
    reg_apll_frpll_syncon     :  1,    //      1
    reg_apll_frpll_m          :  6,    //   7: 2
    reg_apll_frpll_fcw        : 24;    //  31: 8
}CTOP_WOV_FRPLL01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14B0    frpll02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_lock       :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_apll_frpll_frequp     :  1,    //     23
    reg_apll_frpll_a          :  6,    //  29:24
    reg_apll_frpll_in_divrstb :  1,    //     30
    reg_apll_frpll_icp_g      :  1;    //     31
}CTOP_WOV_FRPLL02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14B4    aioplls21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aioplls_lock      :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_wov_aioplls_out_div   :  2,    //  12:11
                              :  1,    //     13 reserved
    reg_wov_aioplls_fout2_en  :  1,    //     14
    reg_wov_aioplls_fb_m      :  8,    //  22:15
    reg_wov_aioplls_cih       :  4,    //  26:23
    reg_wov_aioplls_fout1_en  :  1,    //     27
    reg_wov_aioplls_cih2      :  4;    //  31:28
}CTOP_WOV_AIOPLLS21_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14B8    aioplls22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_codec_ss_aiopll_npc   :  6,    //  13: 8
    reg_codec_ss_aiopll_cih   :  4,    //  17:14
    reg_codec_ss_aiopll_updn_max: 7,    //  24:18
    reg_codec_ss_aiopll_nsc   :  4,    //  28:25
    reg_codec_ss_aiopll_accuracy_1: 1,    //  29
    reg_codec_ss_aiopll_fout_od: 2;    //  31:30
}CTOP_WOV_AIOPLLS22_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14BC    aioplls23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fcw_sel    :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_spll_frpll_fcw_sel    :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CTOP_WOV_AIOPLLS23_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14C0    syn_wov43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_mod_speed_max: 9,    //  8: 0
                              :  7,    //  15: 9 reserved
    reg_apll_frpll_updn_max   :  8,    //  23:16
                              :  4,    //  27:24 reserved
    reg_apll_frpll_dss        :  1,    //     28
                              :  2,    //  30:29 reserved
    reg_apll_frpll_lock_cont  :  1;    //     31
}CTOP_WOV_SYN_WOV43_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14C4    syn_wov44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__pchkerr_lne      :  1,    //      0
    reg_wov__pchkerr_adec     :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_WOV_SYN_WOV44_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14C8    syn_wov45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_monitor_sel_3to0      :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_monitor_sel_7to4      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_monitor_shift1        :  1,    //      8
    reg_monitor_shift2        :  1,    //      9
    reg_monitor_shift3        :  1,    //     10
    micom_debug_jtag_sel      :  1,    //     11
    soft_rst_sscg_resetb      :  1,    //     12
    reg_core400_clk_sel       :  1,    //     13
    reg_rxclkdrv_wov_pd       :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_WOV_SYN_WOV45_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14CC    syn_wov46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__micom_jtag0_sel  :  4,    //   3: 0
    reg_wov__micom_jtag1_sel  :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}CTOP_WOV_SYN_WOV46_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14D0    syn_wov47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_uart_lock0      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_micom_uart_lock1      :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_WOV_SYN_WOV47_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14D4    syn_wov48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ephy_bist_mode_from_micom: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_ephy_mode_from_micom  :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CTOP_WOV_SYN_WOV48_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14D8    syn_wov49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_crg_top_reset_mux_sel :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_frpll_aud_pdb_ctrl    :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_WOV_SYN_WOV49_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14DC    syn_wov50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cec_gf_en             :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV50_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14E0    syn_wov51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_audio_dac_clk_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV51_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14E4    syn_wov52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aec_aud_input_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_SYN_WOV52_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14E8    xtal_clk_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_xtal_clk_sel          :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}CTOP_WOV_XTAL_CLK_MUX_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14EC    syn_wov54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m2pll_pdb_ctrl        :  1,    //      0
    reg_swrst_cpuav_i_d100_gem:  1,    //      1
    reg_swrst_cpuav_i_d100_m2 :  1,    //      2
    reg_swrst_cpuav_i_gem     :  1,    //      3
    reg_swrst_cpuav_i_m2      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_gating_m2_pll_n       :  1,    //      8
    reg_gating_cpuav_i_d100_gem: 1,    //      9
    reg_gating_cpuav_i_d100_m2:  1,    //     10
    reg_gating_cpuav_i_gem    :  1,    //     11
    reg_gating_cpuav_i_m2     :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_WOV_SYN_WOV54_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14F0    clkdrv ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_wov_icon     :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_txclkdrv_wov_cksel    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_rxclkdrv_wov_smv      :  1,    //      8
    reg_rxclkdrv_m2_smv       :  1,    //      9
                              :  2,    //  11:10 reserved
    reg_txclkdrv_c4tx_icon    :  3,    //  14:12
                              : 17;    //  31:15 reserved
}CTOP_WOV_CLKDRV_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14F4    nisol_en_gem ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_en_gem          :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_WOV_NISOL_EN_GEM_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14F8    rc_osc ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_osc_ena               :  1,    //      0
    reg_osc_prog_r            :  8,    //   8: 1
                              : 23;    //   31:9 reserved
}CTOP_WOV_RC_OSC_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_14FC    clk_speed_checker0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_speed_chk__chk_val_cnt: 32;    //  31:0
}CTOP_WOV_CLK_SPEED_CHECKER0_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1500    clk_speed_checker1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_speed_chk__chk_en :  1,    //      0
    reg_clk_speed_chk__intr_clear: 1,    //    1
                              : 30;    //   31:2 reserved
}CTOP_WOV_CLK_SPEED_CHECKER1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1504    clk_speed_checker2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_speed_chk__osc_clk_cnt: 32;    //  31:0
}CTOP_WOV_CLK_SPEED_CHECKER2_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xF301_1508    pad_sxtal_in ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sxtal_in__st      :  1,    //      0
    reg_pad_sxtal_in__pu      :  1,    //      1
    reg_pad_sxtal_in__pd      :  1,    //      2
    reg_pad_sxtal_in__ds3     :  1,    //      3
    reg_pad_sxtal_in__ds2     :  1,    //      4
    reg_pad_sxtal_in__ds1     :  1,    //      5
    reg_pad_sxtal_in__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sxtal_in_mux_sel  :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}CTOP_WOV_PAD_SXTAL_IN_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_WOV_SYN_WOV00_E60_A0_T              syn_wov00                ;         // 0xF301_1400
    CTOP_WOV_SYN_WOV01_E60_A0_T              syn_wov01                ;         // 0xF301_1404
    CTOP_WOV_SYN_WOV02_E60_A0_T              syn_wov02                ;         // 0xF301_1408
    CTOP_WOV_SYN_WOV03_E60_A0_T              syn_wov03                ;         // 0xF301_140C
    CTOP_WOV_SYN_WOV04_E60_A0_T              syn_wov04                ;         // 0xF301_1410
    CTOP_WOV_SYN_WOV05_E60_A0_T              syn_wov05                ;         // 0xF301_1414
    CTOP_WOV_SYN_WOV06_E60_A0_T              syn_wov06                ;         // 0xF301_1418
    CTOP_WOV_SYN_WOV07_E60_A0_T              syn_wov07                ;         // 0xF301_141C
    CTOP_WOV_SYN_WOV08_E60_A0_T              syn_wov08                ;         // 0xF301_1420
    CTOP_WOV_SYN_WOV09_E60_A0_T              syn_wov09                ;         // 0xF301_1424
    CTOP_WOV_SYN_WOV10_E60_A0_T              syn_wov10                ;         // 0xF301_1428
    CTOP_WOV_SYN_WOV11_E60_A0_T              syn_wov11                ;         // 0xF301_142C
    CTOP_WOV_SYN_WOV12_E60_A0_T              syn_wov12                ;         // 0xF301_1430
    CTOP_WOV_SYN_WOV13_E60_A0_T              syn_wov13                ;         // 0xF301_1434
    CTOP_WOV_SYN_WOV14_E60_A0_T              syn_wov14                ;         // 0xF301_1438
    CTOP_WOV_SYN_WOV16_E60_A0_T              syn_wov16                ;         // 0xF301_143C
    CTOP_WOV_SYN_WOV17_E60_A0_T              syn_wov17                ;         // 0xF301_1440
    CTOP_WOV_SYN_WOV18_E60_A0_T              syn_wov18                ;         // 0xF301_1444
    CTOP_WOV_SYN_WOV19_E60_A0_T              syn_wov19                ;         // 0xF301_1448
    CTOP_WOV_SYN_WOV20_E60_A0_T              syn_wov20                ;         // 0xF301_144C
    CTOP_WOV_SYN_WOV21_E60_A0_T              syn_wov21                ;         // 0xF301_1450
    CTOP_WOV_SYN_WOV22_E60_A0_T              syn_wov22                ;         // 0xF301_1454
    CTOP_WOV_SYN_WOV23_E60_A0_T              syn_wov23                ;         // 0xF301_1458
    CTOP_WOV_SYN_WOV24_E60_A0_T              syn_wov24                ;         // 0xF301_145C
    CTOP_WOV_SYN_WOV25_E60_A0_T              syn_wov25                ;         // 0xF301_1460
    CTOP_WOV_SYN_WOV26_E60_A0_T              syn_wov26                ;         // 0xF301_1464
    CTOP_WOV_SYN_WOV27_E60_A0_T              syn_wov27                ;         // 0xF301_1468
    CTOP_WOV_SYN_WOV28_E60_A0_T              syn_wov28                ;         // 0xF301_146C
    CTOP_WOV_SYN_WOV29_E60_A0_T              syn_wov29                ;         // 0xF301_1470
    CTOP_WOV_SYN_WOV30_E60_A0_T              syn_wov30                ;         // 0xF301_1474
    CTOP_WOV_SYN_WOV31_E60_A0_T              syn_wov31                ;         // 0xF301_1478
    CTOP_WOV_SYN_WOV32_E60_A0_T              syn_wov32                ;         // 0xF301_147C
    CTOP_WOV_SYN_WOV33_E60_A0_T              syn_wov33                ;         // 0xF301_1480
    CTOP_WOV_SYN_WOV34_E60_A0_T              syn_wov34                ;         // 0xF301_1484
    CTOP_WOV_SYN_WOV35_E60_A0_T              syn_wov35                ;         // 0xF301_1488
    CTOP_WOV_SYN_WOV36_E60_A0_T              syn_wov36                ;         // 0xF301_148C
    CTOP_WOV_SYN_WOV37_E60_A0_T              syn_wov37                ;         // 0xF301_1490
    CTOP_WOV_SYN_WOV38_E60_A0_T              syn_wov38                ;         // 0xF301_1494
    CTOP_WOV_SYN_WOV39_E60_A0_T              syn_wov39                ;         // 0xF301_1498
    CTOP_WOV_SYN_WOV40_E60_A0_T              syn_wov40                ;         // 0xF301_149C
    CTOP_WOV_SYN_WOV41_E60_A0_T              syn_wov41                ;         // 0xF301_14A0
    CTOP_WOV_SYN_WOV42_E60_A0_T              syn_wov42                ;         // 0xF301_14A4
    CTOP_WOV_FRPLL00_E60_A0_T                frpll00                  ;         // 0xF301_14A8
    CTOP_WOV_FRPLL01_E60_A0_T                frpll01                  ;         // 0xF301_14AC
    CTOP_WOV_FRPLL02_E60_A0_T                frpll02                  ;         // 0xF301_14B0
    CTOP_WOV_AIOPLLS21_E60_A0_T              aioplls21                ;         // 0xF301_14B4
    CTOP_WOV_AIOPLLS22_E60_A0_T              aioplls22                ;         // 0xF301_14B8
    CTOP_WOV_AIOPLLS23_E60_A0_T              aioplls23                ;         // 0xF301_14BC
    CTOP_WOV_SYN_WOV43_E60_A0_T              syn_wov43                ;         // 0xF301_14C0
    CTOP_WOV_SYN_WOV44_E60_A0_T              syn_wov44                ;         // 0xF301_14C4
    CTOP_WOV_SYN_WOV45_E60_A0_T              syn_wov45                ;         // 0xF301_14C8
    CTOP_WOV_SYN_WOV46_E60_A0_T              syn_wov46                ;         // 0xF301_14CC
    CTOP_WOV_SYN_WOV47_E60_A0_T              syn_wov47                ;         // 0xF301_14D0
    CTOP_WOV_SYN_WOV48_E60_A0_T              syn_wov48                ;         // 0xF301_14D4
    CTOP_WOV_SYN_WOV49_E60_A0_T              syn_wov49                ;         // 0xF301_14D8
    CTOP_WOV_SYN_WOV50_E60_A0_T              syn_wov50                ;         // 0xF301_14DC
    CTOP_WOV_SYN_WOV51_E60_A0_T              syn_wov51                ;         // 0xF301_14E0
    CTOP_WOV_SYN_WOV52_E60_A0_T              syn_wov52                ;         // 0xF301_14E4
    CTOP_WOV_XTAL_CLK_MUX_E60_A0_T           xtal_clk_mux             ;         // 0xF301_14E8
    CTOP_WOV_SYN_WOV54_E60_A0_T              syn_wov54                ;         // 0xF301_14EC
    CTOP_WOV_CLKDRV_E60_A0_T                 clkdrv                   ;         // 0xF301_14F0
    CTOP_WOV_NISOL_EN_GEM_E60_A0_T           nisol_en_gem             ;         // 0xF301_14F4
    CTOP_WOV_RC_OSC_E60_A0_T                 rc_osc                   ;         // 0xF301_14F8
    CTOP_WOV_CLK_SPEED_CHECKER0_E60_A0_T     clk_speed_checker0       ;         // 0xF301_14FC
    CTOP_WOV_CLK_SPEED_CHECKER1_E60_A0_T     clk_speed_checker1       ;         // 0xF301_1500
    CTOP_WOV_CLK_SPEED_CHECKER2_E60_A0_T     clk_speed_checker2       ;         // 0xF301_1504
    CTOP_WOV_PAD_SXTAL_IN_E60_A0_T           pad_sxtal_in             ;         // 0xF301_1508
} CTOP_SYN_WOV_REG_E60_A0_T;
/* 67 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_WOV_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

