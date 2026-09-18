#ifndef _CTOP_PQE_SYN_A0_REG_H_
#define _CTOP_PQE_SYN_A0_REG_H_

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
    0xC930_0104    syn_pqe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_fine_control :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_disp_pll_fine_div     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_disp_pll_cih          :  4,    //  11: 8
    reg_disp_pll_nsc          :  4,    //  15:12
    reg_disp_pll_npc          :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_disp_pll_m            :  6,    //  29:24
                              :  1,    //     30 reserved
    disp_pll_lock_out         :  1;    //     31
}PQE_SYN_SYN_PQE01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0108    syn_pqe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_dss          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_disp_pll_fout3_od     :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_disp_pll_fout2_od     :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_disp_pll_fout_od      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_disp_pll_pre_fout3_div:  3,    //  18:16
                              :  1,    //     19 reserved
    reg_disp_pll_pre_fout2_div:  3,    //  22:20
                              :  9;    //  31:23 reserved
}PQE_SYN_SYN_PQE02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_010C    syn_pqe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_offset       :  8,    //   7: 0
    reg_disp_pll_updn_max     :  7,    //  14: 8
                              :  1,    //     15 reserved
    reg_disp_pll_mod_freq     :  9,    //  24:16
                              :  7;    //  31:25 reserved
}PQE_SYN_SYN_PQE03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0110    syn_pqe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_wakeup_bypass:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_disp_pll_ddr_mode     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_disp_pll_offset_mode  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_disp_pll_accuracy     :  2,    //  13:12
                              : 18;    //  31:14 reserved
}PQE_SYN_SYN_PQE04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0114    syn_pqe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_dco_bias_sel      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pqe_dco_g             :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_pqe_dco_rom_test      :  1,    //      8
                              :  7,    //  15: 9 reserved
    reg_pqe_dco_lpf           :  2,    //  17:16
                              : 14;    //  31:18 reserved
}PQE_SYN_SYN_PQE05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_011C    syn_pqe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpio_input_mode       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_d1_enable             :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_i2c4_enable           :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_hphy_i2c_enable       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_en_eb_addr            :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_hdmi_i2c_en           :  1,    //     20
                              : 11;    //  31:21 reserved
}PQE_SYN_SYN_PQE07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0138    syn_pqe14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_8_0      :  1,    //      0
    reg_use_cpu_gpio_8_1      :  1,    //      1
    reg_use_cpu_gpio_8_2      :  1,    //      2
    reg_use_cpu_gpio_8_3      :  1,    //      3
    reg_use_cpu_gpio_8_4      :  1,    //      4
    reg_use_cpu_gpio_8_5      :  1,    //      5
    reg_use_cpu_gpio_8_6      :  1,    //      6
    reg_use_cpu_gpio_8_7      :  1,    //      7
    reg_use_cpu_gpio_7_0      :  1,    //      8
    reg_use_cpu_gpio_7_1      :  1,    //      9
    reg_use_cpu_gpio_7_2      :  1,    //     10
    reg_use_cpu_gpio_7_3      :  1,    //     11
    reg_use_cpu_gpio_7_4      :  1,    //     12
    reg_use_cpu_gpio_7_5      :  1,    //     13
    reg_use_cpu_gpio_7_6      :  1,    //     14
    reg_use_cpu_gpio_7_7      :  1,    //     15
    reg_use_cpu_gpio_6_0      :  1,    //     16
    reg_use_cpu_gpio_6_1      :  1,    //     17
    reg_use_cpu_gpio_6_2      :  1,    //     18
    reg_use_cpu_gpio_6_3      :  1,    //     19
    reg_use_cpu_gpio_6_4      :  1,    //     20
    reg_use_cpu_gpio_6_5      :  1,    //     21
    reg_use_cpu_gpio_6_6      :  1,    //     22
    reg_use_cpu_gpio_6_7      :  1,    //     23
                              :  6,    //  29:24 reserved
    reg_use_cpu_gpio_5_6      :  1,    //     30
    reg_use_cpu_gpio_5_7      :  1;    //     31
}PQE_SYN_SYN_PQE14_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_013C    syn_pqe15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_12_0     :  1,    //      0
    reg_use_cpu_gpio_12_1     :  1,    //      1
    reg_use_cpu_gpio_12_2     :  1,    //      2
    reg_use_cpu_gpio_12_3     :  1,    //      3
    reg_use_cpu_gpio_12_4     :  1,    //      4
    reg_use_cpu_gpio_12_5     :  1,    //      5
    reg_use_cpu_gpio_12_6     :  1,    //      6
    reg_use_cpu_gpio_12_7     :  1,    //      7
    reg_use_cpu_gpio_11_0     :  1,    //      8
    reg_use_cpu_gpio_11_1     :  1,    //      9
    reg_use_cpu_gpio_11_2     :  1,    //     10
    reg_use_cpu_gpio_11_3     :  1,    //     11
    reg_use_cpu_gpio_11_4     :  1,    //     12
    reg_use_cpu_gpio_11_5     :  1,    //     13
    reg_use_cpu_gpio_11_6     :  1,    //     14
    reg_use_cpu_gpio_11_7     :  1,    //     15
    reg_use_cpu_gpio_10_0     :  1,    //     16
    reg_use_cpu_gpio_10_1     :  1,    //     17
    reg_use_cpu_gpio_10_2     :  1,    //     18
    reg_use_cpu_gpio_10_3     :  1,    //     19
    reg_use_cpu_gpio_10_4     :  1,    //     20
    reg_use_cpu_gpio_10_5     :  1,    //     21
    reg_use_cpu_gpio_10_6     :  1,    //     22
    reg_use_cpu_gpio_10_7     :  1,    //     23
    reg_use_cpu_gpio_9_0      :  1,    //     24
    reg_use_cpu_gpio_9_1      :  1,    //     25
    reg_use_cpu_gpio_9_2      :  1,    //     26
    reg_use_cpu_gpio_9_3      :  1,    //     27
    reg_use_cpu_gpio_9_4      :  1,    //     28
    reg_use_cpu_gpio_9_5      :  1,    //     29
    reg_use_cpu_gpio_9_6      :  1,    //     30
    reg_use_cpu_gpio_9_7      :  1;    //     31
}PQE_SYN_SYN_PQE15_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0140    syn_pqe16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_use_cpu_gpio_15_0     :  1,    //      8
    reg_use_cpu_gpio_15_1     :  1,    //      9
    reg_use_cpu_gpio_15_2     :  1,    //     10
    reg_use_cpu_gpio_15_3     :  1,    //     11
    reg_use_cpu_gpio_15_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_14_0     :  1,    //     16
    reg_use_cpu_gpio_14_1     :  1,    //     17
    reg_use_cpu_gpio_14_2     :  1,    //     18
    reg_use_cpu_gpio_14_3     :  1,    //     19
    reg_use_cpu_gpio_14_4     :  1,    //     20
    reg_use_cpu_gpio_14_5     :  1,    //     21
    reg_use_cpu_gpio_14_6     :  1,    //     22
    reg_use_cpu_gpio_14_7     :  1,    //     23
    reg_use_cpu_gpio_13_0     :  1,    //     24
    reg_use_cpu_gpio_13_1     :  1,    //     25
    reg_use_cpu_gpio_13_2     :  1,    //     26
    reg_use_cpu_gpio_13_3     :  1,    //     27
    reg_use_cpu_gpio_13_4     :  1,    //     28
    reg_use_cpu_gpio_13_5     :  1,    //     29
    reg_use_cpu_gpio_13_6     :  1,    //     30
    reg_use_cpu_gpio_13_7     :  1;    //     31
}PQE_SYN_SYN_PQE16_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0144    syn_pqe17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr0__ren     :  1,    //      0
    reg_pad_eb_addr1__ren     :  1,    //      1
    reg_pad_eb_addr2__ren     :  1,    //      2
    reg_pad_eb_addr3__ren     :  1,    //      3
    reg_pad_eb_addr4__ren     :  1,    //      4
    reg_pad_eb_addr5__ren     :  1,    //      5
    reg_pad_eb_addr6__ren     :  1,    //      6
    reg_pad_eb_addr7__ren     :  1,    //      7
    reg_pad_eb_addr8__ren     :  1,    //      8
    reg_pad_eb_addr9__ren     :  1,    //      9
    reg_pad_eb_addr10__ren    :  1,    //     10
    reg_pad_eb_addr11__ren    :  1,    //     11
    reg_pad_eb_addr12__ren    :  1,    //     12
    reg_pad_eb_addr13__ren    :  1,    //     13
    reg_pad_eb_addr14__ren    :  1,    //     14
    reg_pad_eb_addr15__ren    :  1,    //     15
    reg_pad_eb_be_n1__ren     :  1,    //     16
    reg_pad_eb_be_n0__ren     :  1,    //     17
    reg_pad_eb_cs3__ren       :  1,    //     18
    reg_pad_eb_cs2__ren       :  1,    //     19
    reg_pad_eb_cs1__ren       :  1,    //     20
    reg_pad_eb_cs0__ren       :  1,    //     21
    reg_pad_eb_we_n__ren      :  1,    //     22
    reg_pad_eb_wait__ren      :  1,    //     23
    reg_pad_eb_data0__ren     :  1,    //     24
    reg_pad_eb_data1__ren     :  1,    //     25
    reg_pad_eb_data2__ren     :  1,    //     26
    reg_pad_eb_data3__ren     :  1,    //     27
    reg_pad_eb_data4__ren     :  1,    //     28
    reg_pad_eb_data5__ren     :  1,    //     29
    reg_pad_eb_data6__ren     :  1,    //     30
    reg_pad_eb_data7__ren     :  1;    //     31
}PQE_SYN_SYN_PQE17_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0148    syn_pqe18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_wait_n__pd    :  1,    //      0
    reg_pad_cam_wait_n__pu    :  1,    //      1
    reg_pad_cam_wait_n__ds    :  1,    //      2
    reg_pad_cam_vccen_n__pd   :  1,    //      3
    reg_pad_cam_vccen_n__pu   :  1,    //      4
    reg_pad_cam_vccen_n__ds   :  1,    //      5
    reg_pad_cam_reset__pd     :  1,    //      6
    reg_pad_cam_reset__pu     :  1,    //      7
    reg_pad_cam_reset__ds     :  1,    //      8
    reg_pad_cam_reg_n__pd     :  1,    //      9
    reg_pad_cam_reg_n__pu     :  1,    //     10
    reg_pad_cam_reg_n__ds     :  1,    //     11
    reg_pad_cam_ireq_n__pd    :  1,    //     12
    reg_pad_cam_ireq_n__pu    :  1,    //     13
    reg_pad_cam_ireq_n__ds    :  1,    //     14
    reg_pad_cam_ce2_n__pd     :  1,    //     15
    reg_pad_cam_ce2_n__pu     :  1,    //     16
    reg_pad_cam_ce2_n__ds     :  1,    //     17
    reg_pad_cam_ce1_n__pd     :  1,    //     18
    reg_pad_cam_ce1_n__pu     :  1,    //     19
    reg_pad_cam_ce1_n__ds     :  1,    //     20
    reg_pad_cam_cd2_n__pd     :  1,    //     21
    reg_pad_cam_cd2_n__pu     :  1,    //     22
    reg_pad_cam_cd2_n__ds     :  1,    //     23
    reg_pad_cam_cd1_n__pd     :  1,    //     24
    reg_pad_cam_cd1_n__pu     :  1,    //     25
    reg_pad_cam_cd1_n__ds     :  1,    //     26
                              :  4,    //  30:27 reserved
    reg_pad_eb_oe_n__ren      :  1;    //     31
}PQE_SYN_SYN_PQE18_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_014C    syn_pqe19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_sop__pu       :  1,    //      0
    reg_pad_tpi_sop__ds       :  1,    //      1
                              :  3,    //   4: 2 reserved
    reg_pad_tpi_data7__pd     :  1,    //      5
    reg_pad_tpi_data7__pu     :  1,    //      6
    reg_pad_tpi_data7__ds     :  1,    //      7
    reg_pad_tpi_data6__pd     :  1,    //      8
    reg_pad_tpi_data6__pu     :  1,    //      9
    reg_pad_tpi_data6__ds     :  1,    //     10
    reg_pad_tpi_data5__pd     :  1,    //     11
    reg_pad_tpi_data5__pu     :  1,    //     12
    reg_pad_tpi_data5__ds     :  1,    //     13
    reg_pad_tpi_data4__pd     :  1,    //     14
    reg_pad_tpi_data4__pu     :  1,    //     15
    reg_pad_tpi_data4__ds     :  1,    //     16
    reg_pad_tpi_data3__pd     :  1,    //     17
    reg_pad_tpi_data3__pu     :  1,    //     18
    reg_pad_tpi_data3__ds     :  1,    //     19
    reg_pad_tpi_data2__pd     :  1,    //     20
    reg_pad_tpi_data2__pu     :  1,    //     21
    reg_pad_tpi_data2__ds     :  1,    //     22
    reg_pad_tpi_data1__pd     :  1,    //     23
    reg_pad_tpi_data1__pu     :  1,    //     24
    reg_pad_tpi_data1__ds     :  1,    //     25
    reg_pad_tpi_data0__pd     :  1,    //     26
    reg_pad_tpi_data0__pu     :  1,    //     27
    reg_pad_tpi_data0__ds     :  1,    //     28
    reg_pad_tpi_clk__pd       :  1,    //     29
    reg_pad_tpi_clk__pu       :  1,    //     30
    reg_pad_tpi_clk__ds       :  1;    //     31
}PQE_SYN_SYN_PQE19_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0150    syn_pqe20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_err__ds      :  1,    //      0
    reg_pad_tpio_data7__pd    :  1,    //      1
    reg_pad_tpio_data7__pu    :  1,    //      2
    reg_pad_tpio_data7__ds    :  1,    //      3
    reg_pad_tpio_data6__pd    :  1,    //      4
    reg_pad_tpio_data6__pu    :  1,    //      5
    reg_pad_tpio_data6__ds    :  1,    //      6
    reg_pad_tpio_data5__pd    :  1,    //      7
    reg_pad_tpio_data5__pu    :  1,    //      8
    reg_pad_tpio_data5__ds    :  1,    //      9
    reg_pad_tpio_data4__pd    :  1,    //     10
    reg_pad_tpio_data4__pu    :  1,    //     11
    reg_pad_tpio_data4__ds    :  1,    //     12
    reg_pad_tpio_data3__pd    :  1,    //     13
    reg_pad_tpio_data3__pu    :  1,    //     14
    reg_pad_tpio_data3__ds    :  1,    //     15
    reg_pad_tpio_data2__pd    :  1,    //     16
    reg_pad_tpio_data2__pu    :  1,    //     17
    reg_pad_tpio_data2__ds    :  1,    //     18
    reg_pad_tpio_data1__pd    :  1,    //     19
    reg_pad_tpio_data1__pu    :  1,    //     20
    reg_pad_tpio_data1__ds    :  1,    //     21
    reg_pad_tpio_data0__pd    :  1,    //     22
    reg_pad_tpio_data0__pu    :  1,    //     23
    reg_pad_tpio_data0__ds    :  1,    //     24
    reg_pad_tpio_clk__pd      :  1,    //     25
    reg_pad_tpio_clk__pu      :  1,    //     26
    reg_pad_tpio_clk__ds      :  1,    //     27
    reg_pad_tpi_val__pd       :  1,    //     28
    reg_pad_tpi_val__pu       :  1,    //     29
    reg_pad_tpi_val__ds       :  1,    //     30
    reg_pad_tpi_sop__pd       :  1;    //     31
}PQE_SYN_SYN_PQE20_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0154    syn_pqe21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  9,    //   8: 0 reserved
    reg_pad_edid_nisol_out__ren: 1,    //      9
    reg_pad_nand_wp__ren      :  1,    //     10
    reg_pad_nand_wen__ren     :  1,    //     11
    reg_pad_nand_ren__ren     :  1,    //     12
    reg_pad_nand_d7__ren      :  1,    //     13
    reg_pad_nand_d6__ren      :  1,    //     14
    reg_pad_nand_d5__ren      :  1,    //     15
    reg_pad_nand_d4__ren      :  1,    //     16
    reg_pad_nand_d3__ren      :  1,    //     17
    reg_pad_nand_d2__ren      :  1,    //     18
    reg_pad_nand_d1__ren      :  1,    //     19
    reg_pad_nand_d0__ren      :  1,    //     20
    reg_pad_nand_cs0__ren     :  1,    //     21
    reg_pad_nand_cle__ren     :  1,    //     22
    reg_pad_nand_ale__ren     :  1,    //     23
    reg_pad_tpio_val__pd      :  1,    //     24
    reg_pad_tpio_val__pu      :  1,    //     25
    reg_pad_tpio_val__ds      :  1,    //     26
    reg_pad_tpio_sop__pd      :  1,    //     27
    reg_pad_tpio_sop__pu      :  1,    //     28
    reg_pad_tpio_sop__ds      :  1,    //     29
    reg_pad_tpio_err__pd      :  1,    //     30
    reg_pad_tpio_err__pu      :  1;    //     31
}PQE_SYN_SYN_PQE21_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0158    syn_pqe28 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_015C    syn_pqe29 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_0160    syn_pqe30 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_0164    syn_pqe31 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_0168    syn_pqe32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_mon_enable1       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_mon_enable1       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_imx_mon_enable1       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc_mon_enable1       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_cvi_mon_enable1       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_cco_mon_enable1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aud_mon_enable1       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aad_mon_enable1       :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE32_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_016C    syn_pqe33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_abb2_mon_en1          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_abb1_mon_en1          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_abb0_mon_en1          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_te_mon_en1            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_vsd_mon_enable1       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_vdec_mon_enable1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_tcon_mon_enable1      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_pmcu_mon_enable1      :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE33_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0170    syn_pqe34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu3_mon_en1          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cpu2_mon_en1          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu1_mon_en1          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu0_mon_en1          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb2_mon_en1          :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_dbb1_mon_en1          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dbb0_mon_en1          :  1,    //     24
                              :  7;    //  31:25 reserved
}PQE_SYN_SYN_PQE34_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0174    syn_pqe35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_mon_enable2       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_mon_enable2       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_imx_mon_enable2       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc_mon_enable2       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_cvi_mon_enable2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_cco_mon_enable2       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aud_mon_enable2       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aad_mon_enable2       :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE35_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0178    syn_pqe36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_abb2_mon_en2          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_abb1_mon_en2          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_abb0_mon_en2          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_te_mon_en2            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_vsd_mon_enable2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_vdec_mon_enable2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_tcon_mon_enable2      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_pmcu_mon_enable2      :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE36_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_017C    syn_pqe37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu3_mon_en2          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cpu2_mon_en2          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu1_mon_en2          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu0_mon_en2          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb2_mon_en2          :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_dbb1_mon_en2          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dbb0_mon_en2          :  1,    //     24
                              :  7;    //  31:25 reserved
}PQE_SYN_SYN_PQE37_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0180    syn_pqe38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_mon_enable3       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_mon_enable3       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_imx_mon_enable3       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc_mon_enable3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_cvi_mon_enable3       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_cco_mon_enable3       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aud_mon_enable3       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aad_mon_enable3       :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE38_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0184    syn_pqe39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_abb2_mon_en3          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_abb1_mon_en3          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_abb0_mon_en3          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_te_mon_en3            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_vsd_mon_enable3       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_vdec_mon_enable3      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_tcon_mon_enable3      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_pmcu_mon_enable3      :  1,    //     28
                              :  3;    //  31:29 reserved
}PQE_SYN_SYN_PQE39_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0188    syn_pqe40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu3_mon_en3          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cpu2_mon_en3          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu1_mon_en3          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu0_mon_en3          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb2_mon_en3          :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_dbb1_mon_en3          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dbb0_mon_en3          :  1,    //     24
                              :  7;    //  31:25 reserved
}PQE_SYN_SYN_PQE40_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_018C    syn_pqe41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sdec_pqe_dco_sel          :  1,    //      0
                              : 31;    //   31:1 reserved
}PQE_SYN_SYN_PQE41_L18F_A0;

/*-----------------------------------------------------------------------------------------
    pqe_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
UINT32                                                 _rsvd_00[   1] ;         // 0xC930_0100
PQE_SYN_SYN_PQE01_L18F_A0                    syn_pqe01                ;         // 0xC930_0104
PQE_SYN_SYN_PQE02_L18F_A0                    syn_pqe02                ;         // 0xC930_0108
PQE_SYN_SYN_PQE03_L18F_A0                    syn_pqe03                ;         // 0xC930_010C
PQE_SYN_SYN_PQE04_L18F_A0                    syn_pqe04                ;         // 0xC930_0110
PQE_SYN_SYN_PQE05_L18F_A0                    syn_pqe05                ;         // 0xC930_0114
UINT32                                                 _rsvd_01[   1] ;         // 0xC930_0118
PQE_SYN_SYN_PQE07_L18F_A0                    syn_pqe07                ;         // 0xC930_011C
UINT32                                                 _rsvd_02[   6] ;         // 0xC930_0120 ~ 0xC930_0134
PQE_SYN_SYN_PQE14_L18F_A0                    syn_pqe14                ;         // 0xC930_0138
PQE_SYN_SYN_PQE15_L18F_A0                    syn_pqe15                ;         // 0xC930_013C
PQE_SYN_SYN_PQE16_L18F_A0                    syn_pqe16                ;         // 0xC930_0140
PQE_SYN_SYN_PQE17_L18F_A0                    syn_pqe17                ;         // 0xC930_0144
PQE_SYN_SYN_PQE18_L18F_A0                    syn_pqe18                ;         // 0xC930_0148
PQE_SYN_SYN_PQE19_L18F_A0                    syn_pqe19                ;         // 0xC930_014C
PQE_SYN_SYN_PQE20_L18F_A0                    syn_pqe20                ;         // 0xC930_0150
PQE_SYN_SYN_PQE21_L18F_A0                    syn_pqe21                ;         // 0xC930_0154
    UINT32                                   syn_pqe28                ;         // 0xC930_0158
    UINT32                                   syn_pqe29                ;         // 0xC930_015C
    UINT32                                   syn_pqe30                ;         // 0xC930_0160
    UINT32                                   syn_pqe31                ;         // 0xC930_0164
PQE_SYN_SYN_PQE32_L18F_A0                    syn_pqe32                ;         // 0xC930_0168
PQE_SYN_SYN_PQE33_L18F_A0                    syn_pqe33                ;         // 0xC930_016C
PQE_SYN_SYN_PQE34_L18F_A0                    syn_pqe34                ;         // 0xC930_0170
PQE_SYN_SYN_PQE35_L18F_A0                    syn_pqe35                ;         // 0xC930_0174
PQE_SYN_SYN_PQE36_L18F_A0                    syn_pqe36                ;         // 0xC930_0178
PQE_SYN_SYN_PQE37_L18F_A0                    syn_pqe37                ;         // 0xC930_017C
PQE_SYN_SYN_PQE38_L18F_A0                    syn_pqe38                ;         // 0xC930_0180
PQE_SYN_SYN_PQE39_L18F_A0                    syn_pqe39                ;         // 0xC930_0184
PQE_SYN_SYN_PQE40_L18F_A0                    syn_pqe40                ;         // 0xC930_0188
PQE_SYN_SYN_PQE41_L18F_A0                    syn_pqe41                ;         // 0xC930_018C
} PQE_SYN_REG_L18F_A0;
/* 28 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_PQE_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

