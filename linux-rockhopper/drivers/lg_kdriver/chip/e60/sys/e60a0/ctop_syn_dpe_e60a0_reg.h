#ifndef _CTOP_SYN_DPE_E60A0_REG_H_
#define _CTOP_SYN_DPE_E60A0_REG_H_

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
    0xC924_3400    syn_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gem__ls_disable_led1  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_gem__ls_disable_led0  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_gem__ls_disable_tcon  :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_DPE_SYN_DPE00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3404    syn_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_led0_ctrl         : 32;    //  31: 0
}CTOP_DPE_SYN_DPE01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3408    syn_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_led1_ctrl         : 32;    //  31: 0
}CTOP_DPE_SYN_DPE02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_340C    syn_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_cco2_led_vid    :  1,    //      0
    reg_osd_swrst             :  1,    //      1
    reg_swrst_vsd_dpe_stb     :  1,    //      2
                              :  1,    //      3 reserved
    reg_swrst_cco0_led1_chip_info_c: 1,    //  4
    reg_swrst_cco0_led1_chip_info_y: 1,    //  5
                              : 26;    //   31:6 reserved
}CTOP_DPE_SYN_DPE03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3410    syn_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_intr_polar_high_en: 1,    //    0
    reg_c4_vx1_intr_edge_en   :  1,    //      1
    reg_c4_vx1_intr_clear     :  1,    //      2
                              :  1,    //      3 reserved
    reg_c4_vx1_lockn_intr_en  :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CTOP_DPE_SYN_DPE04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3414    syn_dpe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_main_counter_0: 4,    //  3:0
    reg_c4_vx1_lockn_main_counter_clear_0: 1,    //  4
    reg_c4_vx1_lockn_main_counter_rising_edge_0: 1,    //  5
                              :  2,    //   7: 6 reserved
    reg_c4_vx1_lockn_main_counter_1: 4,    //  11:8
    reg_c4_vx1_lockn_main_counter_clear_1: 1,    //  12
    reg_c4_vx1_lockn_main_counter_rising_edge_1: 1,    //  13
                              : 18;    //  31:14 reserved
}CTOP_DPE_SYN_DPE05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3418    syn_dpe06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ext_reg_wrdata     :  8,    //   7: 0
    reg_c4_ext_reg_addr       :  8,    //  15: 8
    reg_c4_ext_reg_wren       :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_DPE_SYN_DPE06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_341C    syn_dpe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_link0_ext_reg_en :  1,    //      0
    reg_c4_0_link1_ext_reg_en :  1,    //      1
    reg_c4_0_link2_ext_reg_en :  1,    //      2
    reg_c4_0_link3_ext_reg_en :  1,    //      3
    reg_c4_1_link0_ext_reg_en :  1,    //      4
    reg_c4_1_link1_ext_reg_en :  1,    //      5
    reg_c4_1_link2_ext_reg_en :  1,    //      6
    reg_c4_1_link3_ext_reg_en :  1,    //      7
    reg_c4_0_pll_ext_reg_en   :  1,    //      8
    reg_c4_1_pll_ext_reg_en   :  1,    //      9
                              : 22;    //  31:10 reserved
}CTOP_DPE_SYN_DPE07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3420    syn_dpe08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_pdb_ch0          :  1,    //      0
    reg_c4_0_pdb_ch1          :  1,    //      1
    reg_c4_0_pdb_ch2          :  1,    //      2
    reg_c4_0_pdb_ch3          :  1,    //      3
    reg_c4_0_pdb_ch4          :  1,    //      4
    reg_c4_0_pdb_ch5          :  1,    //      5
    reg_c4_0_pdb_ch6          :  1,    //      6
    reg_c4_0_pdb_ch7          :  1,    //      7
    reg_c4_0_pdb_ch8          :  1,    //      8
    reg_c4_0_pdb_ch9          :  1,    //      9
    reg_c4_0_pdb_ch10         :  1,    //     10
    reg_c4_0_pdb_ch11         :  1,    //     11
    reg_c4_0_pdb_ch12         :  1,    //     12
    reg_c4_0_pdb_ch13         :  1,    //     13
    reg_c4_0_pdb_ch14         :  1,    //     14
    reg_c4_0_pdb_ch15         :  1,    //     15
    reg_c4_1_pdb_ch0          :  1,    //     16
    reg_c4_1_pdb_ch1          :  1,    //     17
    reg_c4_1_pdb_ch2          :  1,    //     18
    reg_c4_1_pdb_ch3          :  1,    //     19
    reg_c4_1_pdb_ch4          :  1,    //     20
    reg_c4_1_pdb_ch5          :  1,    //     21
    reg_c4_1_pdb_ch6          :  1,    //     22
    reg_c4_1_pdb_ch7          :  1,    //     23
    reg_c4_1_pdb_ch8          :  1,    //     24
    reg_c4_1_pdb_ch9          :  1,    //     25
    reg_c4_1_pdb_ch10         :  1,    //     26
    reg_c4_1_pdb_ch11         :  1,    //     27
    reg_c4_1_pdb_ch12         :  1,    //     28
    reg_c4_1_pdb_ch13         :  1,    //     29
    reg_c4_1_pdb_ch14         :  1,    //     30
    reg_c4_1_pdb_ch15         :  1;    //     31
}CTOP_DPE_SYN_DPE08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3424    syn_dpe09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_pdb              :  1,    //      0
    reg_c4_1_pdb              :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_c4_rstn_vtxlink       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_clk_sel               :  1,    //      8
                              : 19,    //  27: 9 reserved
    reg_c4_ext_reg_rstb       :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_DPE_SYN_DPE09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3428    syn_dpe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_link0_ext_reg_rddata: 8,    //  7:0
    reg_c4_0_link1_ext_reg_rddata: 8,    //  15:8
    reg_c4_0_link2_ext_reg_rddata: 8,    //  23:16
    reg_c4_0_link3_ext_reg_rddata: 8;    //  31:24
}CTOP_DPE_SYN_DPE10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_342C    syn_dpe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_pll_ext_reg_rddata: 8,    //   7: 0
                              : 24;    //   31:8 reserved
}CTOP_DPE_SYN_DPE11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3430    syn_dpe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_1_link0_ext_reg_rddata: 8,    //  7:0
    reg_c4_1_link1_ext_reg_rddata: 8,    //  15:8
    reg_c4_1_link2_ext_reg_rddata: 8,    //  23:16
    reg_c4_1_link3_ext_reg_rddata: 8;    //  31:24
}CTOP_DPE_SYN_DPE12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3434    syn_dpe13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_1_pll_ext_reg_rddata: 8,    //   7: 0
                              : 24;    //   31:8 reserved
}CTOP_DPE_SYN_DPE13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3438    syn_dpe14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_0_epi_lock_tomain  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_0_vx1_lockn_tomain :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_c4_0_pll_rstb_g       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_c4_0_pll_lock         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_c4_1_epi_lock_tomain  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_c4_1_vx1_lockn_tomain :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_c4_1_pll_rstb_g       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_c4_1_pll_lock         :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_DPE_SYN_DPE14_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_343C    syn_dpe17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_1_test_di3             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE17_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3440    syn_dpe18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_1_test_di2             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE18_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3444    syn_dpe19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_1_test_di1             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE19_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3448    syn_dpe20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_1_test_di0             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE20_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_344C    syn_dpe21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_0_test_di3             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE21_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3450    syn_dpe22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_0_test_di2             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE22_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3454    syn_dpe23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_0_test_di1             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE23_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3458    syn_dpe24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_0_test_di0             : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_DPE_SYN_DPE24_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_345C    syn_dpe25 ''
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
    reg_monitor_shift4        :  1,    //     11
    reg_monitor_shift5        :  1,    //     12
    reg_monitor_shift6        :  1,    //     13
    reg_monitor_shift7        :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_DPE_SYN_DPE25_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_DPE_SYN_DPE00_E60_A0_T              syn_dpe00                ;         // 0xC924_3400
    CTOP_DPE_SYN_DPE01_E60_A0_T              syn_dpe01                ;         // 0xC924_3404
    CTOP_DPE_SYN_DPE02_E60_A0_T              syn_dpe02                ;         // 0xC924_3408
    CTOP_DPE_SYN_DPE03_E60_A0_T              syn_dpe03                ;         // 0xC924_340C
    CTOP_DPE_SYN_DPE04_E60_A0_T              syn_dpe04                ;         // 0xC924_3410
    CTOP_DPE_SYN_DPE05_E60_A0_T              syn_dpe05                ;         // 0xC924_3414
    CTOP_DPE_SYN_DPE06_E60_A0_T              syn_dpe06                ;         // 0xC924_3418
    CTOP_DPE_SYN_DPE07_E60_A0_T              syn_dpe07                ;         // 0xC924_341C
    CTOP_DPE_SYN_DPE08_E60_A0_T              syn_dpe08                ;         // 0xC924_3420
    CTOP_DPE_SYN_DPE09_E60_A0_T              syn_dpe09                ;         // 0xC924_3424
    CTOP_DPE_SYN_DPE10_E60_A0_T              syn_dpe10                ;         // 0xC924_3428
    CTOP_DPE_SYN_DPE11_E60_A0_T              syn_dpe11                ;         // 0xC924_342C
    CTOP_DPE_SYN_DPE12_E60_A0_T              syn_dpe12                ;         // 0xC924_3430
    CTOP_DPE_SYN_DPE13_E60_A0_T              syn_dpe13                ;         // 0xC924_3434
    CTOP_DPE_SYN_DPE14_E60_A0_T              syn_dpe14                ;         // 0xC924_3438
    CTOP_DPE_SYN_DPE17_E60_A0_T              syn_dpe17                ;         // 0xC924_343C
    CTOP_DPE_SYN_DPE18_E60_A0_T              syn_dpe18                ;         // 0xC924_3440
    CTOP_DPE_SYN_DPE19_E60_A0_T              syn_dpe19                ;         // 0xC924_3444
    CTOP_DPE_SYN_DPE20_E60_A0_T              syn_dpe20                ;         // 0xC924_3448
    CTOP_DPE_SYN_DPE21_E60_A0_T              syn_dpe21                ;         // 0xC924_344C
    CTOP_DPE_SYN_DPE22_E60_A0_T              syn_dpe22                ;         // 0xC924_3450
    CTOP_DPE_SYN_DPE23_E60_A0_T              syn_dpe23                ;         // 0xC924_3454
    CTOP_DPE_SYN_DPE24_E60_A0_T              syn_dpe24                ;         // 0xC924_3458
    CTOP_DPE_SYN_DPE25_E60_A0_T              syn_dpe25                ;         // 0xC924_345C
} CTOP_SYN_DPE_REG_E60_A0_T;
/* 24 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_DPE_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

