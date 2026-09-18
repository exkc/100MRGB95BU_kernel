#ifndef _CTOP_FME0_M17A0_REG_H_
#define _CTOP_FME0_M17A0_REG_H_

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
    0xC930_8800    ctop_fme0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_eb_data4_ds           :  1,    //      0
    reg_eb_data4_pu           :  1,    //      1
    reg_eb_data4_pd           :  1,    //      2
                              :  1,    //      3 reserved
    reg_eb_data3_ds           :  1,    //      4
    reg_eb_data3_pu           :  1,    //      5
    reg_eb_data3_pd           :  1,    //      6
                              :  1,    //      7 reserved
    reg_eb_data2_ds           :  1,    //      8
    reg_eb_data2_pu           :  1,    //      9
    reg_eb_data2_pd           :  1,    //     10
                              :  1,    //     11 reserved
    reg_eb_data1_ds           :  1,    //     12
    reg_eb_data1_pu           :  1,    //     13
    reg_eb_data1_pd           :  1,    //     14
                              :  1,    //     15 reserved
    reg_eb_data0_ds           :  1,    //     16
    reg_eb_data0_pu           :  1,    //     17
    reg_eb_data0_pd           :  1,    //     18
                              :  1,    //     19 reserved
    reg_eb_oe_n_ds            :  1,    //     20
    reg_eb_oe_n_pu            :  1,    //     21
    reg_eb_oe_n_pd            :  1,    //     22
                              :  1,    //     23 reserved
    reg_eb_we_n_ds            :  1,    //     24
    reg_eb_we_n_pu            :  1,    //     25
    reg_eb_we_n_pd            :  1,    //     26
                              :  1,    //     27 reserved
    reg_eb_wait_ds            :  1,    //     28
    reg_eb_wait_pu            :  1,    //     29
    reg_eb_wait_pd            :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8804    ctop_fme0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_eb_addr13_ds          :  1,    //      0
    reg_eb_addr13_pu          :  1,    //      1
    reg_eb_addr13_pd          :  1,    //      2
                              :  1,    //      3 reserved
    reg_eb_addr9_ds           :  1,    //      4
    reg_eb_addr9_pu           :  1,    //      5
    reg_eb_addr9_pd           :  1,    //      6
                              :  1,    //      7 reserved
    reg_eb_addr10_ds          :  1,    //      8
    reg_eb_addr10_pu          :  1,    //      9
    reg_eb_addr10_pd          :  1,    //     10
                              :  1,    //     11 reserved
    reg_eb_addr11_ds          :  1,    //     12
    reg_eb_addr11_pu          :  1,    //     13
    reg_eb_addr11_pd          :  1,    //     14
                              :  1,    //     15 reserved
    reg_eb_addr12_ds          :  1,    //     16
    reg_eb_addr12_pu          :  1,    //     17
    reg_eb_addr12_pd          :  1,    //     18
                              :  1,    //     19 reserved
    reg_eb_data7_ds           :  1,    //     20
    reg_eb_data7_pu           :  1,    //     21
    reg_eb_data7_pd           :  1,    //     22
                              :  1,    //     23 reserved
    reg_eb_data5_ds           :  1,    //     24
    reg_eb_data5_pu           :  1,    //     25
    reg_eb_data5_pd           :  1,    //     26
                              :  1,    //     27 reserved
    reg_eb_data6_ds           :  1,    //     28
    reg_eb_data6_pu           :  1,    //     29
    reg_eb_data6_pd           :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8808    ctop_fme0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_eb_addr4_ds           :  1,    //      0
    reg_eb_addr4_pu           :  1,    //      1
    reg_eb_addr4_pd           :  1,    //      2
                              :  1,    //      3 reserved
    reg_eb_addr3_ds           :  1,    //      4
    reg_eb_addr3_pu           :  1,    //      5
    reg_eb_addr3_pd           :  1,    //      6
                              :  1,    //      7 reserved
    reg_eb_addr5_ds           :  1,    //      8
    reg_eb_addr5_pu           :  1,    //      9
    reg_eb_addr5_pd           :  1,    //     10
                              :  1,    //     11 reserved
    reg_eb_addr6_ds           :  1,    //     12
    reg_eb_addr6_pu           :  1,    //     13
    reg_eb_addr6_pd           :  1,    //     14
                              :  1,    //     15 reserved
    reg_eb_addr8_ds           :  1,    //     16
    reg_eb_addr8_pu           :  1,    //     17
    reg_eb_addr8_pd           :  1,    //     18
                              :  1,    //     19 reserved
    reg_eb_addr7_ds           :  1,    //     20
    reg_eb_addr7_pu           :  1,    //     21
    reg_eb_addr7_pd           :  1,    //     22
                              :  1,    //     23 reserved
    reg_eb_addr15_ds          :  1,    //     24
    reg_eb_addr15_pu          :  1,    //     25
    reg_eb_addr15_pd          :  1,    //     26
                              :  1,    //     27 reserved
    reg_eb_addr14_ds          :  1,    //     28
    reg_eb_addr14_pu          :  1,    //     29
    reg_eb_addr14_pd          :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_880C    ctop_fme0_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cam_ireq_n_ds         :  1,    //      0
    reg_cam_ireq_n_pu         :  1,    //      1
    reg_cam_ireq_n_pd         :  1,    //      2
                              :  1,    //      3 reserved
    reg_cam_ce1_n_ds          :  1,    //      4
    reg_cam_ce1_n_pu          :  1,    //      5
    reg_cam_ce1_n_pd          :  1,    //      6
                              :  1,    //      7 reserved
    reg_cam_ce2_n_ds          :  1,    //      8
    reg_cam_ce2_n_pu          :  1,    //      9
    reg_cam_ce2_n_pd          :  1,    //     10
                              :  1,    //     11 reserved
    reg_cam_reset_ds          :  1,    //     12
    reg_cam_reset_pu          :  1,    //     13
    reg_cam_reset_pd          :  1,    //     14
                              :  1,    //     15 reserved
    reg_cam_vccen_n_ds        :  1,    //     16
    reg_cam_vccen_n_pu        :  1,    //     17
    reg_cam_vccen_n_pd        :  1,    //     18
                              :  1,    //     19 reserved
    reg_eb_addr1_ds           :  1,    //     20
    reg_eb_addr1_pu           :  1,    //     21
    reg_eb_addr1_pd           :  1,    //     22
                              :  1,    //     23 reserved
    reg_eb_addr2_ds           :  1,    //     24
    reg_eb_addr2_pu           :  1,    //     25
    reg_eb_addr2_pd           :  1,    //     26
                              :  1,    //     27 reserved
    reg_eb_addr0_ds           :  1,    //     28
    reg_eb_addr0_pu           :  1,    //     29
    reg_eb_addr0_pd           :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8810    ctop_fme0_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    reg_sd_clk_ds             :  1,    //     13
    reg_sd_clk_pu             :  1,    //     14
    reg_sd_clk_pd             :  1,    //     15
    reg_sd_cd_n_ds            :  1,    //     16
    reg_sd_cd_n_pu            :  1,    //     17
    reg_sd_cd_n_pd            :  1,    //     18
    reg_cam_reg_n_ds          :  1,    //     19
    reg_cam_reg_n_pu          :  1,    //     20
    reg_cam_reg_n_pd          :  1,    //     21
    reg_cam_cd1_n_ds          :  1,    //     22
    reg_cam_cd1_n_pu          :  1,    //     23
    reg_cam_cd1_n_pd          :  1,    //     24
    reg_cam_cd2_n_ds          :  1,    //     25
    reg_cam_cd2_n_pu          :  1,    //     26
    reg_cam_cd2_n_pd          :  1,    //     27
    reg_cam_wait_n_ds         :  1,    //     28
    reg_cam_wait_n_pu         :  1,    //     29
    reg_cam_wait_n_pd         :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8814    ctop_fme0_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 12,    //  11: 0 reserved
    reg_sd_data0_ds           :  1,    //     12
    reg_sd_data0_pu           :  1,    //     13
    reg_sd_data0_pd           :  1,    //     14
                              :  1,    //     15 reserved
    reg_sd_data1_ds           :  1,    //     16
    reg_sd_data1_pu           :  1,    //     17
    reg_sd_data1_pd           :  1,    //     18
                              :  1,    //     19 reserved
    reg_sd_data2_ds           :  1,    //     20
    reg_sd_data2_pu           :  1,    //     21
    reg_sd_data2_pd           :  1,    //     22
                              :  1,    //     23 reserved
    reg_sd_data3_ds           :  1,    //     24
    reg_sd_data3_pu           :  1,    //     25
    reg_sd_data3_pd           :  1,    //     26
                              :  1,    //     27 reserved
    reg_sd_cmd_ds             :  1,    //     28
    reg_sd_cmd_pu             :  1,    //     29
    reg_sd_cmd_pd             :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8818    ctop_fme0_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_sd_wp_n_ds            :  1,    //     20
    reg_sd_wp_n_pu            :  1,    //     21
    reg_sd_wp_n_pd            :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_FME0_CTOP_FME0_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_881C    ctop_fme0_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hub_vbus_ctrl0_ds     :  1,    //      0
    reg_hub_vbus_ctrl0_pu     :  1,    //      1
    reg_hub_vbus_ctrl0_pd     :  1,    //      2
                              : 29;    //   31:3 reserved
}CTOP_FME0_CTOP_FME0_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8820    ctop_fme0_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpio_data0_ds         :  1,    //      0
    reg_tpio_data0_pu         :  1,    //      1
    reg_tpio_data0_pd         :  1,    //      2
                              :  1,    //      3 reserved
    reg_tpio_data1_ds         :  1,    //      4
    reg_tpio_data1_pu         :  1,    //      5
    reg_tpio_data1_pd         :  1,    //      6
                              :  1,    //      7 reserved
    reg_tpio_sop_ds           :  1,    //      8
    reg_tpio_sop_pu           :  1,    //      9
    reg_tpio_sop_pd           :  1,    //     10
                              :  1,    //     11 reserved
    reg_tpio_clk_ds           :  1,    //     12
    reg_tpio_clk_pu           :  1,    //     13
    reg_tpio_clk_pd           :  1,    //     14
                              :  1,    //     15 reserved
    reg_tpio_err_ds           :  1,    //     16
    reg_tpio_err_pu           :  1,    //     17
    reg_tpio_err_pd           :  1,    //     18
                              :  1,    //     19 reserved
    reg_tpio_val_ds           :  1,    //     20
    reg_tpio_val_pu           :  1,    //     21
    reg_tpio_val_pd           :  1,    //     22
                              :  5,    //  27:23 reserved
    reg_hub_port_over0_ds     :  1,    //     28
    reg_hub_port_over0_pu     :  1,    //     29
    reg_hub_port_over0_pd     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8824    ctop_fme0_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_data1_ds          :  1,    //      0
    reg_tpi_data1_pu          :  1,    //      1
    reg_tpi_data1_pd          :  1,    //      2
                              :  1,    //      3 reserved
    reg_tpi_data0_ds          :  1,    //      4
    reg_tpi_data0_pu          :  1,    //      5
    reg_tpi_data0_pd          :  1,    //      6
                              :  1,    //      7 reserved
    reg_tpio_data7_ds         :  1,    //      8
    reg_tpio_data7_pu         :  1,    //      9
    reg_tpio_data7_pd         :  1,    //     10
                              :  1,    //     11 reserved
    reg_tpio_data6_ds         :  1,    //     12
    reg_tpio_data6_pu         :  1,    //     13
    reg_tpio_data6_pd         :  1,    //     14
                              :  1,    //     15 reserved
    reg_tpio_data5_ds         :  1,    //     16
    reg_tpio_data5_pu         :  1,    //     17
    reg_tpio_data5_pd         :  1,    //     18
                              :  1,    //     19 reserved
    reg_tpio_data4_ds         :  1,    //     20
    reg_tpio_data4_pu         :  1,    //     21
    reg_tpio_data4_pd         :  1,    //     22
                              :  1,    //     23 reserved
    reg_tpio_data3_ds         :  1,    //     24
    reg_tpio_data3_pu         :  1,    //     25
    reg_tpio_data3_pd         :  1,    //     26
                              :  1,    //     27 reserved
    reg_tpio_data2_ds         :  1,    //     28
    reg_tpio_data2_pu         :  1,    //     29
    reg_tpio_data2_pd         :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8828    ctop_fme0_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_err_ds            :  1,    //      0
    reg_tpi_err_pu            :  1,    //      1
    reg_tpi_err_pd            :  1,    //      2
                              :  1,    //      3 reserved
    reg_tpi_sop_ds            :  1,    //      4
    reg_tpi_sop_pu            :  1,    //      5
    reg_tpi_sop_pd            :  1,    //      6
                              :  1,    //      7 reserved
    reg_tpi_data7_ds          :  1,    //      8
    reg_tpi_data7_pu          :  1,    //      9
    reg_tpi_data7_pd          :  1,    //     10
                              :  1,    //     11 reserved
    reg_tpi_data5_ds          :  1,    //     12
    reg_tpi_data5_pu          :  1,    //     13
    reg_tpi_data5_pd          :  1,    //     14
                              :  1,    //     15 reserved
    reg_tpi_data6_ds          :  1,    //     16
    reg_tpi_data6_pu          :  1,    //     17
    reg_tpi_data6_pd          :  1,    //     18
                              :  1,    //     19 reserved
    reg_tpi_data4_ds          :  1,    //     20
    reg_tpi_data4_pu          :  1,    //     21
    reg_tpi_data4_pd          :  1,    //     22
                              :  1,    //     23 reserved
    reg_tpi_data3_ds          :  1,    //     24
    reg_tpi_data3_pu          :  1,    //     25
    reg_tpi_data3_pd          :  1,    //     26
                              :  1,    //     27 reserved
    reg_tpi_data2_ds          :  1,    //     28
    reg_tpi_data2_pu          :  1,    //     29
    reg_tpi_data2_pd          :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R10_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_882C    ctop_fme0_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_eb_be_n0_ds           :  1,    //      0
    reg_eb_be_n0_pu           :  1,    //      1
    reg_eb_be_n0_pd           :  1,    //      2
                              :  1,    //      3 reserved
    reg_eb_be_n1_ds           :  1,    //      4
    reg_eb_be_n1_pu           :  1,    //      5
    reg_eb_be_n1_pd           :  1,    //      6
                              :  1,    //      7 reserved
    reg_eb_cs3_ds             :  1,    //      8
    reg_eb_cs3_pu             :  1,    //      9
    reg_eb_cs3_pd             :  1,    //     10
                              :  1,    //     11 reserved
    reg_eb_cs2_ds             :  1,    //     12
    reg_eb_cs2_pu             :  1,    //     13
    reg_eb_cs2_pd             :  1,    //     14
                              :  1,    //     15 reserved
    reg_eb_cs1_ds             :  1,    //     16
    reg_eb_cs1_pu             :  1,    //     17
    reg_eb_cs1_pd             :  1,    //     18
                              :  1,    //     19 reserved
    reg_eb_cs0_ds             :  1,    //     20
    reg_eb_cs0_pu             :  1,    //     21
    reg_eb_cs0_pd             :  1,    //     22
                              :  1,    //     23 reserved
    reg_tpi_clk_ds            :  1,    //     24
    reg_tpi_clk_pu            :  1,    //     25
    reg_tpi_clk_pd            :  1,    //     26
                              :  1,    //     27 reserved
    reg_tpi_val_ds            :  1,    //     28
    reg_tpi_val_pu            :  1,    //     29
    reg_tpi_val_pd            :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R11_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8830    ctop_fme0_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    gp16_2_mux_en             :  1,    //      2
    gp16_3_mux_en             :  1,    //      3
    gp16_4_mux_en             :  1,    //      4
    gp16_5_mux_en             :  1,    //      5
    gp16_6_mux_en             :  1,    //      6
    gp16_7_mux_en             :  1,    //      7
    gp15_0_mux_en             :  1,    //      8
    gp15_1_mux_en             :  1,    //      9
    gp15_2_mux_en             :  1,    //     10
    gp15_3_mux_en             :  1,    //     11
    gp15_4_mux_en             :  1,    //     12
    gp15_5_mux_en             :  1,    //     13
    gp15_6_mux_en             :  1,    //     14
    gp15_7_mux_en             :  1,    //     15
    gp14_0_mux_en             :  1,    //     16
    gp14_1_mux_en             :  1,    //     17
    gp14_2_mux_en             :  1,    //     18
    gp14_3_mux_en             :  1,    //     19
    gp14_4_mux_en             :  1,    //     20
    gp14_5_mux_en             :  1,    //     21
    gp14_6_mux_en             :  1,    //     22
    gp14_7_mux_en             :  1,    //     23
    gp11_0_mux_en             :  1,    //     24
    gp11_1_mux_en             :  1,    //     25
    gp11_2_mux_en             :  1,    //     26
    gp11_3_mux_en             :  1,    //     27
    gp11_4_mux_en             :  1,    //     28
    gp11_5_mux_en             :  1,    //     29
    gp11_6_mux_en             :  1,    //     30
    gp11_7_mux_en             :  1;    //     31
}CTOP_FME0_CTOP_FME0_R12_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8834    ctop_fme0_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    cpupll_fine_div           :  1,    //      1
    cpupll_dss                :  1,    //      2
    cpupll_accuracy           :  2,    //   4: 3
    cpupll_updn_max           :  7,    //  11: 5
    cpupll_mod_freq           :  9,    //  20:12
    cpupll_m                  :  6,    //  26:21
    cpupll_pdb_ctrl           :  1,    //     27
    cpupll_cih                :  4;    //  31:28
}CTOP_FME0_CTOP_FME0_R13_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8838    ctop_fme0_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cpupll_freq_update        :  1,    //      0
    cpupll_sync_on            :  1,    //      1
                              :  2,    //   3: 2 reserved
    cpupll_ofs_mode           :  1,    //      4
    cpupll_fout3_od           :  3,    //   7: 5
    cpupll_fout2_od           :  3,    //  10: 8
    cpupll_fout_od            :  2,    //  12:11
    cpupll_pre_fout3_div      :  3,    //  15:13
    cpupll_pre_fout2_div      :  3,    //  18:16
    cpupll_nsc                :  4,    //  22:19
    cpupll_npc                :  6,    //  28:23
    cpupll_fine_control       :  3;    //  31:29
}CTOP_FME0_CTOP_FME0_R14_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_883C    ctop_fme0_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    cpupll_wakeup_bypass      :  1,    //     22
    cpupll_ddr_mode           :  1,    //     23
    cpupll_offset             :  8;    //  31:24
}CTOP_FME0_CTOP_FME0_R15_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8840    ctop_fme0_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tpo_sel_ctrl1             :  1,    //      0
    sc_clk_sel                :  1,    //      1
    ir_enable                 :  1,    //      2
    vccen_n_pol               :  1,    //      3
    tpio_sel_ctrl             :  1,    //      4
    tpo_sel_ctrl0             :  1,    //      5
    sdio_en                   :  1,    //      6
    ef_pd_normal              :  1,    //      7
    en_eb_addr                :  1,    //      8
                              : 19,    //  27: 9 reserved
    jtag0_enable              :  1,    //     28
    dbb_tst_enable            :  1,    //     29
    ext_eth_enable            :  1,    //     30
    d1_enable                 :  1;    //     31
}CTOP_FME0_CTOP_FME0_R16_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8844    ctop_fme0_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_te_internal         :  1,    //      0
    swrst_auda_internal       :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_FME0_CTOP_FME0_R17_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_8848    ctop_fme0_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 28,    //  27: 0 reserved
    rxclkdrv1_smv_normal      :  1,    //     28
    rxclkdrv1_outsel_normal   :  2,    //  30:29
    rxclkdrv1_pdb_normal      :  1;    //     31
}CTOP_FME0_CTOP_FME0_R18_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_fme0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_FME0_CTOP_FME0_R00_M17_A0               ctop_fme0_r00            ;         // 0xC930_8800
CTOP_FME0_CTOP_FME0_R01_M17_A0               ctop_fme0_r01            ;         // 0xC930_8804
CTOP_FME0_CTOP_FME0_R02_M17_A0               ctop_fme0_r02            ;         // 0xC930_8808
CTOP_FME0_CTOP_FME0_R03_M17_A0               ctop_fme0_r03            ;         // 0xC930_880C
CTOP_FME0_CTOP_FME0_R04_M17_A0               ctop_fme0_r04            ;         // 0xC930_8810
CTOP_FME0_CTOP_FME0_R05_M17_A0               ctop_fme0_r05            ;         // 0xC930_8814
CTOP_FME0_CTOP_FME0_R06_M17_A0               ctop_fme0_r06            ;         // 0xC930_8818
CTOP_FME0_CTOP_FME0_R07_M17_A0               ctop_fme0_r07            ;         // 0xC930_881C
CTOP_FME0_CTOP_FME0_R08_M17_A0               ctop_fme0_r08            ;         // 0xC930_8820
CTOP_FME0_CTOP_FME0_R09_M17_A0               ctop_fme0_r09            ;         // 0xC930_8824
CTOP_FME0_CTOP_FME0_R10_M17_A0               ctop_fme0_r10            ;         // 0xC930_8828
CTOP_FME0_CTOP_FME0_R11_M17_A0               ctop_fme0_r11            ;         // 0xC930_882C
CTOP_FME0_CTOP_FME0_R12_M17_A0               ctop_fme0_r12            ;         // 0xC930_8830
CTOP_FME0_CTOP_FME0_R13_M17_A0               ctop_fme0_r13            ;         // 0xC930_8834
CTOP_FME0_CTOP_FME0_R14_M17_A0               ctop_fme0_r14            ;         // 0xC930_8838
CTOP_FME0_CTOP_FME0_R15_M17_A0               ctop_fme0_r15            ;         // 0xC930_883C
CTOP_FME0_CTOP_FME0_R16_M17_A0               ctop_fme0_r16            ;         // 0xC930_8840
CTOP_FME0_CTOP_FME0_R17_M17_A0               ctop_fme0_r17            ;         // 0xC930_8844
CTOP_FME0_CTOP_FME0_R18_M17_A0               ctop_fme0_r18            ;         // 0xC930_8848
} CTOP_FME0_REG_M17_A0;
/* 19 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_FME0_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

