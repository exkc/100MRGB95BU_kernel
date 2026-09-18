#ifndef _CTOP_BMC_M19A0_REG_H_
#define _CTOP_BMC_M19A0_REG_H_

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
    0xC930_E400    ctop_bmc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag1_disable         :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E404    ctop_bmc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_scl2_pu               :  1,    //      1
    reg_scl2_pd               :  1,    //      2
                              :  2,    //   4: 3 reserved
    reg_sda2_pu               :  1,    //      5
    reg_sda2_pd               :  1,    //      6
                              :  2,    //   8: 7 reserved
    reg_scl1_pu               :  1,    //      9
    reg_scl1_pd               :  1,    //     10
                              :  2,    //  12:11 reserved
    reg_sda1_pu               :  1,    //     13
    reg_sda1_pd               :  1,    //     14
                              :  2,    //  16:15 reserved
    reg_scl0_pu               :  1,    //     17
    reg_scl0_pd               :  1,    //     18
                              :  2,    //  20:19 reserved
    reg_sda0_pu               :  1,    //     21
    reg_sda0_pd               :  1,    //     22
                              :  2,    //  24:23 reserved
    reg_scl4_pu               :  1,    //     25
    reg_scl4_pd               :  1,    //     26
                              :  2,    //  28:27 reserved
    reg_sda4_pu               :  1,    //     29
    reg_sda4_pd               :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E408    ctop_bmc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 17,    //  16: 0 reserved
    reg_scl3_pu               :  1,    //     17
    reg_scl3_pd               :  1,    //     18
                              :  2,    //  20:19 reserved
    reg_sda3_pu               :  1,    //     21
    reg_sda3_pd               :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E40C    ctop_bmc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_spi_cs1_pd            :  1,    //      2
    reg_spi_cs1_pu            :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_spi_di1_pu            :  1,    //      7
                              :  2,    //   9: 8 reserved
    reg_spi_cs0_pd            :  1,    //     10
    reg_spi_cs0_pu            :  1,    //     11
                              :  2,    //  13:12 reserved
    reg_spi_do0_pd            :  1,    //     14
    reg_spi_do0_pu            :  1,    //     15
                              :  2,    //  17:16 reserved
    reg_spi_sclk1_pd          :  1,    //     18
    reg_spi_sclk1_pu          :  1,    //     19
                              :  2,    //  21:20 reserved
    reg_spi_do1_pd            :  1,    //     22
    reg_spi_do1_pu            :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_spi_di0_pu            :  1,    //     27
                              :  2,    //  29:28 reserved
    reg_spi_sclk0_pd          :  1,    //     30
    reg_spi_sclk0_pu          :  1;    //     31
}CTOP_CTRL_BMC_CTOP_BMC_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E410    ctop_bmc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_use_cpu_gpio_17_0     :  1,    //      8
    reg_use_cpu_gpio_17_2     :  1,    //      9
    reg_use_cpu_gpio_17_1     :  1,    //     10
    reg_use_cpu_gpio_17_3     :  1,    //     11
                              :  6,    //  17:12 reserved
    reg_use_cpu_gpio_9_2      :  1,    //     18
    reg_use_cpu_gpio_9_3      :  1,    //     19
    reg_use_cpu_gpio_9_4      :  1,    //     20
    reg_use_cpu_gpio_9_5      :  1,    //     21
    reg_use_cpu_gpio_9_6      :  1,    //     22
    reg_use_cpu_gpio_9_7      :  1,    //     23
    reg_use_cpu_gpio_4_0      :  1,    //     24
    reg_use_cpu_gpio_4_1      :  1,    //     25
    reg_use_cpu_gpio_4_2      :  1,    //     26
    reg_use_cpu_gpio_4_3      :  1,    //     27
    reg_use_cpu_gpio_4_4      :  1,    //     28
    reg_use_cpu_gpio_4_5      :  1,    //     29
    reg_use_cpu_gpio_4_6      :  1,    //     30
    reg_use_cpu_gpio_4_7      :  1;    //     31
}CTOP_CTRL_BMC_CTOP_BMC_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E41C    ctop_bmc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_3_wordinterface0     :  1,    //      0
                              :  1,    //      1 reserved
    usb2_3_fsel               :  3,    //   4: 2
    usb2_3_txrestune0         :  2,    //   6: 5
    usb2_3_txhsxvtune0        :  2,    //   8: 7
    usb2_3_txvreftune0        :  4,    //  12: 9
    usb2_3_txrisetune0        :  2,    //  14:13
    usb2_3_txpreemppulsetune0 :  1,    //     15
    usb2_3_txpreempamptune0   :  2,    //  17:16
    usb2_3_txfslstune0        :  4,    //  21:18
    usb2_3_sqrxtune0          :  3,    //  24:22
    usb2_3_compdistune0       :  3,    //  27:25
    usb2_3_commononn          :  1,    //     28
    usb2_3_refclksel          :  2,    //  30:29
    usb2_3_portreset0         :  1;    //     31
}CTOP_CTRL_BMC_CTOP_BMC_R07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E420    ctop_bmc_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_3_bypasssel0         :  1,    //      0
    usb2_3_bypassdmen0        :  1,    //      1
    usb2_3_bypassdpen0        :  1,    //      2
    usb2_3_bypassdmdata0      :  1,    //      3
    usb2_3_bypassdpdata0      :  1,    //      4
    usb2_3_otgdisable0        :  1,    //      5
    usb2_3_vatestenb          :  2,    //   7: 6
    usb2_3_loopbackenb0       :  1,    //      8
    usb2_3_siddq              :  1,    //      9
    usb2_3_testclk0           :  1,    //     10
                              :  1,    //     11 reserved
    usb2_3_testdataout0       :  4,    //  15:12
    usb2_3_testdatain0        :  8,    //  23:16
    usb2_3_testaddr0          :  4,    //  27:24
    usb2_3_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_3_atereset           :  1;    //     31
}CTOP_CTRL_BMC_CTOP_BMC_R08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E424    ctop_bmc_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_3_por                :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E428    ctop_bmc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apll_dco_fcw              : 22,    //  21: 0
                              :  2,    //  23:22 reserved
    apll_dco_test             :  1,    //     24
                              :  3,    //  27:25 reserved
    apll_dco_lpf              :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E42C    ctop_bmc_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apll_cont                 :  1,    //      0
                              :  3,    //   3: 1 reserved
    apll_cpc                  :  1,    //      4
                              :  3,    //   7: 5 reserved
    apll_test                 :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    apll_ci                   :  3,    //  14:12
                              :  1,    //     15 reserved
    apll_od                   :  2,    //  17:16
                              :  2,    //  19:18 reserved
    apll_dco_g                :  3,    //  22:20
                              :  1,    //     23 reserved
    apll_pdb                  :  1,    //     24
    apll_rstb                 :  1,    //     25
    apll_dco_rstb             :  1,    //     26
                              :  5;    //  31:27 reserved
}CTOP_CTRL_BMC_CTOP_BMC_R11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E430    videoafe_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    videoafe_sel_fs           :  1,    //      3
    videoafe_bvclpsel         :  1,    //      4
    videoafe_bpdb             :  1,    //      5
    videoafe_decm             :  2,    //   7: 6
    videoafe_sel_invdatack    :  1,    //      8
    videoafe_sel_datack       :  1,    //      9
    videoafe_gvclpsel         :  1,    //     10
    videoafe_gpdb             :  1,    //     11
    videoafe_rvclpsel         :  1,    //     12
    videoafe_rpdb             :  1,    //     13
                              : 18;    //  31:14 reserved
}CTOP_CTRL_BMC_VIDEOAFE_00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E434    videoafe_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_sog_ssfil        :  2,    //   1: 0
    videoafe_sog_fil          :  3,    //   4: 2
    videoafe_soglvl           :  5,    //   9: 5
    videoafe_sog_soui         :  2,    //  11:10
    videoafe_sog_sinki        :  3,    //  14:12
    videoafe_sog_bw           :  2,    //  16:15
    videoafe_sog_hys          :  2,    //  18:17
                              : 13;    //  31:19 reserved
}CTOP_CTRL_BMC_VIDEOAFE_01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E438    videoafe_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_reserved         :  8,    //   7: 0
    videoafe_ire_test         :  1,    //      8
    videoafe_fblvl            :  2,    //  10: 9
                              :  4,    //  14:11 reserved
    videoafe_ibs_50u_sel      :  1,    //     15
    videoafe_ref_sel          :  2,    //  17:16
    videoafe_ire_sel          :  2,    //  19:18
    videoafe_biaspdb          :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_BMC_VIDEOAFE_02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E43C    videoafe_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_vclp_en          :  1,    //      0
    videoafe_icon_adc         :  3,    //   3: 1
    videoafe_icon_buf         :  3,    //   6: 4
    videoafe_clpcur           :  3,    //   9: 7
    videoafe_adcisel_f34      :  2,    //  11:10
    videoafe_adcisel_f12      :  2,    //  13:12
    videoafe_adcisel_m        :  2,    //  15:14
    videoafe_adcisel_ref      :  2,    //  17:16
    videoafe_adcisel_ps       :  2,    //  19:18
    videoafe_adc_fil          :  3,    //  22:20
    videoafe_selmux           :  1,    //     23
    videoafe_shield_on        :  2,    //  25:24
                              :  2,    //  27:26 reserved
    videoafe_sid1lvl          :  2,    //  29:28
    videoafe_sid2lvl          :  2;    //  31:30
}CTOP_CTRL_BMC_VIDEOAFE_03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E440    videoafe_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_cvbs_cksel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    videoafe_sog_deglitch     :  4,    //   7: 4
    videoafe_sog_outmux       :  1,    //      8
    videoafe_sog2dig_sel      :  1,    //      9
    videoafe_sog2dig          :  1,    //     10
    videoafe_sog_enwin        :  1,    //     11
    videoafe_ire_selrefck     :  1,    //     12
    videoafe_sel_ck           :  2,    //  14:13
                              : 17;    //  31:15 reserved
}CTOP_CTRL_BMC_VIDEOAFE_04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E444    videoafe_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_div_max             :  5,    //   4: 0
    llpll_cvbs_lock           :  2,    //   6: 5
    llpll_ref_lock_ctl        :  2,    //   8: 7
    llpll_cvbs_mc             :  1,    //      9
    llpll_nsc                 :  4,    //  13:10
    llpll_npc                 :  5,    //  18:14
    llpll_cpll_pdb            :  1,    //     19
    llpll_ref_vcon            :  1,    //     20
    refpll_pdb                :  1,    //     21
    llpll_icpcon              :  5,    //  26:22
                              :  5;    //  31:27 reserved
}CTOP_CTRL_BMC_VIDEOAFE_05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E448    videoafe_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_dco_control_monitor : 29,    //  28: 0
                              :  3;    //  31:29 reserved
}CTOP_CTRL_BMC_VIDEOAFE_06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E44C    videoafe_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_filter_status       :  2,    //   1: 0
    llpll_counter_monitor     : 12,    //  13: 2
    llpll_diff_monitor        : 12,    //  25:14
                              :  6;    //  31:26 reserved
}CTOP_CTRL_BMC_VIDEOAFE_07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E450    videoafe_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_g1_fine             :  5,    //   4: 0
    llpll_g2_fine             :  5,    //   9: 5
    llpll_g3_p_fine           :  5,    //  14:10
    llpll_g3_n_fine           :  5,    //  19:15
                              : 12;    //  31:20 reserved
}CTOP_CTRL_BMC_VIDEOAFE_08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E454    videoafe_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_g1_nom              :  5,    //   4: 0
    llpll_g2_nom              :  5,    //   9: 5
    llpll_g3_p_nom            :  5,    //  14:10
    llpll_g3_n_nom            :  5,    //  19:15
                              : 12;    //  31:20 reserved
}CTOP_CTRL_BMC_VIDEOAFE_09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E458    videoafe_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    llpll_counter_max         : 12,    //  11: 0
    llpll_dco_max             :  5,    //  16:12
    llpll_dco_min             :  5,    //  21:17
    llpll_sf_mode_control     :  4,    //  25:22
    llpll_coarse_scale        :  4,    //  29:26
                              :  2;    //  31:30 reserved
}CTOP_CTRL_BMC_VIDEOAFE_10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E45C    videoafe_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reset_n                   :  1,    //      0
                              : 10,    //  10: 1 reserved
    llpll_lpf_clk_sel         :  1,    //     11
    llpll_lpf_clk_div         :  2,    //  13:12
    llpll_dco_test_mode       :  1,    //     14
    llpll_disable_fm          :  1,    //     15
    llpll_disable_sfm         :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_BMC_VIDEOAFE_11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E460    videoafe_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_cvbs_shield_on   :  2,    //   1: 0
    videoafe_cvbs_insel       :  2,    //   3: 2
    videoafe_cvbs_clp         :  1,    //      4
    videoafe_cvbs_iclp        :  2,    //   6: 5
    videoafe_cvbs_ibuf        :  3,    //   9: 7
    videoafe_cvbs_iclp2       :  2,    //  11:10
    videoafe_cvbs_pdb         :  1,    //     12
    videoafe_cvbs_bw          :  1,    //     13
    videoafe_cvbs_lpf         :  1,    //     14
                              :  3,    //  17:15 reserved
    videoafe_cvbs_pdbm        :  1,    //     18
    videoafe_cvbs_dcsel       :  2,    //  20:19
    videoafe_cvbs_refsel      :  2,    //  22:21
    videoafe_cvbs_isel        :  3,    //  25:23
                              :  3,    //  28:26 reserved
    videoafe_cvbs_decm        :  2,    //  30:29
                              :  1;    //  31:31 reserved
}CTOP_CTRL_BMC_VIDEOAFE_12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E464    videoafe_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    videoafe_cvbs_adcisel_ps  :  2,    //   1: 0
    videoafe_cvbs_adcisel_ref :  2,    //   3: 2
    videoafe_cvbs_adcisel_m   :  2,    //   5: 4
    videoafe_cvbs_adcisel_f12 :  2,    //   7: 6
    videoafe_cvbs_adcisel_f34 :  2,    //   9: 8
    videoafe_cvbs_dcatt       :  1,    //     10
                              : 21;    //  31:11 reserved
}CTOP_CTRL_BMC_VIDEOAFE_13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E468    aad_afe_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aad_adc_rot               :  4,    //   3: 0
    aad_adc_rvs               :  1,    //      4
    aad_adc_selsif            :  1,    //      5
    aad_adc_ibias_res         :  3,    //   8: 6
    aad_adcclk_test           :  1,    //      9
    aad_adc_pdb               :  1,    //     10
    aad_adc_selref            :  2,    //  12:11
                              : 19;    //  31:13 reserved
}CTOP_CTRL_BMC_AAD_AFE_00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E46C    aad_afe_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aad_pll_test              :  2,    //   1: 0
    aad_pll_rstb              :  1,    //      2
    aad_pll_pdb               :  1,    //      3
    aad_pll_ci                :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}CTOP_CTRL_BMC_AAD_AFE_01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E470    acodec_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auad_ch_sel               :  2,    //   1: 0
    auad_div_sel              :  3,    //   4: 2
    auad_gcont                :  3,    //   7: 5
                              : 24;    //   31:8 reserved
}CTOP_CTRL_BMC_ACODEC_00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E474    acodec_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auad_c_pga                :  2,    //   1: 0
    auad_c_int2               :  2,    //   3: 2
    auad_c_int1               :  2,    //   5: 4
    auad_c_comp               :  2,    //   7: 6
    auad_ccont                :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}CTOP_CTRL_BMC_ACODEC_01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E478    acodec_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auad_mux_pdb              :  1,    //      0
    auad_adc_pdb              :  1,    //      1
    auad_bias_pdb             :  1,    //      2
    auad_pga_pdb              :  1,    //      3
    auad_chop_enb             :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_BMC_ACODEC_02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E47C    acodec_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    auda_pdb_bias             :  1,    //      1
    auda_sel_vref_out         :  1,    //      2
    auda_ft_mode              :  1,    //      3
    auda_pdb_dac              :  1,    //      4
    auda_pdb_clk              :  1,    //      5
                              :  6,    //  11: 6 reserved
    auda_ic_vcom              :  2,    //  13:12
    auda_ic_iref              :  2,    //  15:14
                              : 16;    //  31:16 reserved
}CTOP_CTRL_BMC_ACODEC_03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E480    acodec_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auda_chop_en              :  1,    //      0
    auda_chop_freq            :  2,    //   2: 1
    auda_chop_refp_en         :  1,    //      3
    auda_ic_d2s               :  2,    //   5: 4
    auda_ic_refp              :  2,    //   7: 6
    auda_ic_ref               :  2,    //   9: 8
    auda_ic_scf               :  2,    //  11:10
    auda_vcont_refp           :  3,    //  14:12
                              :  1,    //     15 reserved
    auda_ccont                :  2,    //  17:16
                              :  2,    //  19:18 reserved
    auda_chop_vbuf_en         :  1,    //     20
    auda_cnt_rdiv             :  1,    //     21
                              :  2,    //  23:22 reserved
    auda_ic_bgr               :  2,    //  25:24
                              :  2,    //  27:26 reserved
    auda_ic_vbuf              :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_BMC_ACODEC_04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E484    acodec_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auda_res                  :  3,    //   2: 0
                              :  1,    //      3 reserved
    auda_vcom_cont            :  2,    //   5: 4
                              :  3,    //   8: 6 reserved
    auad_pga_ref_pdb          :  1,    //      9
                              : 22;    //  31:10 reserved
}CTOP_CTRL_BMC_ACODEC_05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E488    dmdmip_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_pll_ort           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_dmd_pll_d_oen         :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_dmd_pll_d_odiv        :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_dmd_pll_mc            :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_dmd_pll_icp           :  4,    //  27:24
    reg_dmd_pll_pdb           :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_BMC_DMDMIP_00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E48C    dmdmip_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_dmd_pll_lock_sw       :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_dmd_pll_don_odiv      :  1,    //     24
    reg_dmd_pll_don_lpf       :  1,    //     25
    reg_dmd_pll_tcsel         :  1,    //     26
    reg_dmd_pll_div5sel       :  1,    //     27
    reg_dmd_pll_div2sel       :  1,    //     28
    reg_dmd_pll_divrst        :  1,    //     29
    reg_dmd_pll_finsel        :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_BMC_DMDMIP_01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E490    dmdmip_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_adc_refsel        :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_dmd_adc_icon          :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_dmd_bias_pdb          :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_BMC_DMDMIP_02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E494    dmdmip_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_sadc_q_clkinv     :  1,    //      0
    reg_dmd_sadc_i_clkinv     :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_dmd_sadc_q_decm       :  2,    //   5: 4
    reg_dmd_sadc_i_decm       :  2,    //   7: 6
    reg_dmd_sadc_q_pdb        :  1,    //      8
    reg_dmd_sadc_i_pdb        :  1,    //      9
    reg_dmd_tadc_clkinv       :  1,    //     10
                              :  1,    //     11 reserved
    reg_dmd_tadc_decm         :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_dmd_tadc_pdb          :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_BMC_DMDMIP_03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E498    dmdmip_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_pll_lock          :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_BMC_DMDMIP_04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E49C    adc_output ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_videoafe_rdout    :  1,    //      0
    reg_sel_videoafe_gdout    :  1,    //      1
    reg_sel_videoafe_bdout    :  1,    //      2
    reg_sel_dmd_tadc          :  1,    //      3
    reg_sel_dmd_sadc_i        :  1,    //      4
    reg_sel_dmd_sadc_q        :  1,    //      5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_BMC_ADC_OUTPUT_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A0    dbb_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_bbopermode        :  8,    //   7: 0
                              :  4,    //  11: 8 reserved
    reg_dbb_reg_init          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb_reset             :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_mcu_reset             :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dbb_i2csel            :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_BMC_DBB_00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A4    rxclkdrv_dmd ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_dmd_pdb      :  1,    //      0
    reg_rxclkdrv_dmd_smv      :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_BMC_RXCLKDRV_DMD_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A8    clkout_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aadafe_clkout_sel     :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_videoafe_clkout_sel   :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_BMC_CLKOUT_SEL_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_BMC_CTOP_BMC_R00_M19A0_T           ctop_bmc_r00             ;         // 0xC930_E400
CTOP_CTRL_BMC_CTOP_BMC_R01_M19A0_T           ctop_bmc_r01             ;         // 0xC930_E404
CTOP_CTRL_BMC_CTOP_BMC_R02_M19A0_T           ctop_bmc_r02             ;         // 0xC930_E408
CTOP_CTRL_BMC_CTOP_BMC_R03_M19A0_T           ctop_bmc_r03             ;         // 0xC930_E40C
CTOP_CTRL_BMC_CTOP_BMC_R04_M19A0_T           ctop_bmc_r04             ;         // 0xC930_E410
UINT32                                                 _rsvd_00[   2] ;         // 0xC930_E414 ~ 0xC930_E418
CTOP_CTRL_BMC_CTOP_BMC_R07_M19A0_T           ctop_bmc_r07             ;         // 0xC930_E41C
CTOP_CTRL_BMC_CTOP_BMC_R08_M19A0_T           ctop_bmc_r08             ;         // 0xC930_E420
CTOP_CTRL_BMC_CTOP_BMC_R09_M19A0_T           ctop_bmc_r09             ;         // 0xC930_E424
CTOP_CTRL_BMC_CTOP_BMC_R10_M19A0_T           ctop_bmc_r10             ;         // 0xC930_E428
CTOP_CTRL_BMC_CTOP_BMC_R11_M19A0_T           ctop_bmc_r11             ;         // 0xC930_E42C
CTOP_CTRL_BMC_VIDEOAFE_00_M19A0_T            videoafe_00              ;         // 0xC930_E430
CTOP_CTRL_BMC_VIDEOAFE_01_M19A0_T            videoafe_01              ;         // 0xC930_E434
CTOP_CTRL_BMC_VIDEOAFE_02_M19A0_T            videoafe_02              ;         // 0xC930_E438
CTOP_CTRL_BMC_VIDEOAFE_03_M19A0_T            videoafe_03              ;         // 0xC930_E43C
CTOP_CTRL_BMC_VIDEOAFE_04_M19A0_T            videoafe_04              ;         // 0xC930_E440
CTOP_CTRL_BMC_VIDEOAFE_05_M19A0_T            videoafe_05              ;         // 0xC930_E444
CTOP_CTRL_BMC_VIDEOAFE_06_M19A0_T            videoafe_06              ;         // 0xC930_E448
CTOP_CTRL_BMC_VIDEOAFE_07_M19A0_T            videoafe_07              ;         // 0xC930_E44C
CTOP_CTRL_BMC_VIDEOAFE_08_M19A0_T            videoafe_08              ;         // 0xC930_E450
CTOP_CTRL_BMC_VIDEOAFE_09_M19A0_T            videoafe_09              ;         // 0xC930_E454
CTOP_CTRL_BMC_VIDEOAFE_10_M19A0_T            videoafe_10              ;         // 0xC930_E458
CTOP_CTRL_BMC_VIDEOAFE_11_M19A0_T            videoafe_11              ;         // 0xC930_E45C
CTOP_CTRL_BMC_VIDEOAFE_12_M19A0_T            videoafe_12              ;         // 0xC930_E460
CTOP_CTRL_BMC_VIDEOAFE_13_M19A0_T            videoafe_13              ;         // 0xC930_E464
CTOP_CTRL_BMC_AAD_AFE_00_M19A0_T             aad_afe_00               ;         // 0xC930_E468
CTOP_CTRL_BMC_AAD_AFE_01_M19A0_T             aad_afe_01               ;         // 0xC930_E46C
CTOP_CTRL_BMC_ACODEC_00_M19A0_T              acodec_00                ;         // 0xC930_E470
CTOP_CTRL_BMC_ACODEC_01_M19A0_T              acodec_01                ;         // 0xC930_E474
CTOP_CTRL_BMC_ACODEC_02_M19A0_T              acodec_02                ;         // 0xC930_E478
CTOP_CTRL_BMC_ACODEC_03_M19A0_T              acodec_03                ;         // 0xC930_E47C
CTOP_CTRL_BMC_ACODEC_04_M19A0_T              acodec_04                ;         // 0xC930_E480
CTOP_CTRL_BMC_ACODEC_05_M19A0_T              acodec_05                ;         // 0xC930_E484
CTOP_CTRL_BMC_DMDMIP_00_M19A0_T              dmdmip_00                ;         // 0xC930_E488
CTOP_CTRL_BMC_DMDMIP_01_M19A0_T              dmdmip_01                ;         // 0xC930_E48C
CTOP_CTRL_BMC_DMDMIP_02_M19A0_T              dmdmip_02                ;         // 0xC930_E490
CTOP_CTRL_BMC_DMDMIP_03_M19A0_T              dmdmip_03                ;         // 0xC930_E494
CTOP_CTRL_BMC_DMDMIP_04_M19A0_T              dmdmip_04                ;         // 0xC930_E498
CTOP_CTRL_BMC_ADC_OUTPUT_M19A0_T             adc_output               ;         // 0xC930_E49C
CTOP_CTRL_BMC_DBB_00_M19A0_T                 dbb_00                   ;         // 0xC930_E4A0
CTOP_CTRL_BMC_RXCLKDRV_DMD_M19A0_T           rxclkdrv_dmd             ;         // 0xC930_E4A4
CTOP_CTRL_BMC_CLKOUT_SEL_M19A0_T             clkout_sel               ;         // 0xC930_E4A8
} CTOP_CTRL_BMC_REG_M19A0_T;
/* 41 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_BMC_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

