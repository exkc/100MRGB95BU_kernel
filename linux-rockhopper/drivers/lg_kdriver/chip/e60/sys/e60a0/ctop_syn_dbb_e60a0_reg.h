#ifndef _CTOP_SYN_DBB_E60A0_REG_H_
#define _CTOP_SYN_DBB_E60A0_REG_H_

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
    0xC30C_1800    acodec0 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC30C_1804    acodec1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__auad_pga_ref_pdb :  1,    //      0
    reg_dbb__aud_ccont        :  2,    //   2: 1
    reg_dbb__auad_refp_pdb    :  1,    //      3
    reg_dbb__auda_ic_scfr     :  2,    //   5: 4
    reg_dbb__auad_ic_ref      :  2,    //   7: 6
    reg_dbb__auda_pdb_clk     :  1,    //      8
    reg_dbb__auda_chop_en_ref :  1,    //      9
    reg_dbb__auad_ic_int2     :  2,    //  11:10
    reg_dbb__auda_chop_freq_scf: 2,    //  13:12
    reg_dbb__auad_ic_refp     :  2,    //  15:14
    reg_dbb__auda_chop_en_refp:  1,    //     16
    reg_dbb__auad_ic_quant    :  2,    //  18:17
    reg_dbb__auda_vcont_refp  :  3,    //  21:19
    reg_dbb__auda_chop_en     :  1,    //     22
    reg_dbb__auda_chop_en_scf :  1,    //     23
    reg_dbb__auad_ic_pga      :  2,    //  25:24
    reg_dbb__auda_pdb_dac     :  1,    //     26
    reg_dbb__auda_chop_en_d2s :  1,    //     27
    reg_dbb__auad_ic_int1     :  2,    //  29:28
    reg_dbb__auda_chop_freq_d2s: 2;    //  31:30
}CTOP_DBB_ACODEC1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1808    acodec2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__auad_d_inv_enb   :  1,    //      0
    reg_dbb__auad_mclk_en     :  1,    //      1
    reg_dbb__auad_adc_pdb     :  1,    //      2
    reg_dbb__aud_ic_vcom      :  2,    //   4: 3
    reg_dbb__auad_ch1_sel     :  1,    //      5
    reg_dbb__auda_ic_refpr    :  2,    //   7: 6
    reg_dbb__auda_ic_d2sl     :  2,    //   9: 8
    reg_dbb__auad_refp_en     :  1,    //     10
    reg_dbb__auad_sel_pga     :  2,    //  12:11
    reg_dbb__aud_ft_mode      :  1,    //     13
    reg_dbb__auad_en_int_pga  :  1,    //     14
    reg_dbb__auda_ic_scfl     :  2,    //  16:15
    reg_dbb__auad_chen_amp    :  1,    //     17
    reg_dbb__auad_en_ext      :  1,    //     18
    reg_dbb__auad_pga_chop_en :  1,    //     19
    reg_dbb__aud_res          :  3,    //  22:20
    reg_dbb__auad_chen_cmfb   :  1,    //     23
    reg_dbb__auad_ch2_sel     :  1,    //     24
    reg_dbb__aud_ic_vbuf      :  2,    //  26:25
    reg_dbb__auda_ic_d2sr     :  2,    //  28:27
    reg_dbb__auad_refp_ch_en  :  1,    //     29
    reg_dbb__auad_sel_refp    :  2;    //  31:30
}CTOP_DBB_ACODEC2_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_180C    acodec3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__auad_ch_out_enb  :  1,    //      1
    reg_dbb__aud_pdb_bias     :  1,    //      2
    reg_dbb__auda_ic_refl     :  2,    //   4: 3
    reg_dbb__auad_refn_en     :  1,    //      5
    reg_dbb__auad_div_sel_sdm :  3,    //   8: 6
    reg_dbb__auad_pga_pdb     :  1,    //      9
    reg_dbb__aud_ic_bgr       :  2,    //  11:10
    reg_dbb__auad_vcont_refp  :  3,    //  14:12
    reg_dbb__auda_ic_refpl    :  2,    //  16:15
    reg_dbb__auad_ref_chop_en :  1,    //     17
    reg_dbb__auad_pga_gcont   :  3,    //  20:18
    reg_dbb__reserve_in2      :  5,    //  25:21
    reg_dbb__aud_vcom_cont    :  2,    //  27:26
    reg_dbb__aud_cnt_rdiv     :  1,    //     28
    reg_dbb__auad_en_ext_pga  :  1,    //     29
    reg_dbb__auda_ic_refr     :  2;    //  31:30
}CTOP_DBB_ACODEC3_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1810    acodec4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_dbb__auad_en_int      :  1,    //     24
    reg_dbb__auad_sdm_chop_en :  1,    //     25
    reg_dbb__aud_sel_vref_out :  1,    //     26
    reg_dbb__reserve_in1      :  5;    //  31:27
}CTOP_DBB_ACODEC4_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1814    admd_mip5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_dbb__admd_t_sel_clkinv:  1,    //      5
    reg_dbb__admd_i_pdb       :  1,    //      6
    reg_dbb__admd_a_sel_sif   :  1,    //      7
    reg_dbb__admd_a_adc_icon  :  3,    //  10: 8
    reg_dbb__admd_apll_icp    :  4,    //  14:11
    reg_dbb__admd_a_gc        :  5,    //  19:15
    reg_dbb__admd_apll_autofreq: 1,    //     20
    reg_dbb__admd_a_adc_refsel:  2,    //  22:21
    reg_dbb__admd_apll_icp_g  :  1,    //     23
    reg_dbb__admd_a_pdb       :  1,    //     24
    reg_dbb__admd_apll_outsel :  1,    //     25
    reg_dbb__admd_a_bias_pdb  :  1,    //     26
    reg_dbb__admd_apll_lpf_on :  1,    //     27
    reg_dbb__admd_a_sel_clkinv:  1,    //     28
    reg_dbb__admd_apll_frequp :  1,    //     29
    reg_dbb__admd_a_decm      :  2;    //  31:30
}CTOP_DBB_ADMD_MIP5_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1818    admd_mip6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__admd_apll_insel  :  1,    //      1
    reg_dbb__admd_apll_cken   :  3,    //   4: 2
    reg_dbb__admd_dpll_wakebypass: 1,    //    5
    reg_dbb__admd_dpll_lpf_on :  1,    //      6
    reg_dbb__admd_t_pdb       :  1,    //      7
    reg_dbb__admd_i_decm      :  2,    //   9: 8
    reg_dbb__admd_apll_lockf  :  1,    //     10
    reg_dbb__admd_apll_wakebypass: 1,    //   11
    reg_dbb__admd_dpll_od_en  :  1,    //     12
    reg_dbb__admd_dpll_frequp :  1,    //     13
    reg_dbb__admd_q_pdb       :  1,    //     14
    reg_dbb__admd_adc_icon    :  3,    //  17:15
    reg_dbb__admd_dpll_lockc  :  1,    //     18
    reg_dbb__admd_apll_od_en  :  1,    //     19
    reg_dbb__admd_dpll_odpre  :  6,    //  25:20
    reg_dbb__admd_dpll_m      :  6;    //  31:26
}CTOP_DBB_ADMD_MIP6_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_181C    admd_mip7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__admd_dpll_autofreq: 1,    //      1
    reg_dbb__admd_i_sel_clkinv:  1,    //      2
    reg_dbb__admd_apll_odpost :  6,    //   8: 3
    reg_dbb__admd_apll_divint :  9,    //  17: 9
    reg_dbb__admd_dpll_syncon :  1,    //     18
    reg_dbb__admd_dpll_icp_g  :  1,    //     19
    reg_dbb__admd_t_decm      :  2,    //  21:20
    reg_dbb__admd_bias_pdb    :  1,    //     22
    reg_dbb__admd_apll_lockc  :  1,    //     23
    reg_dbb__admd_dpll_insel  :  1,    //     24
    reg_dbb__admd_apll_syncon :  1,    //     25
    reg_dbb__admd_dpll_cken   :  3,    //  28:26
    reg_dbb__admd_dpll_outsel :  1,    //     29
    reg_dbb__admd_q_decm      :  2;    //  31:30
}CTOP_DBB_ADMD_MIP7_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1820    admd_mip8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__admd_apll_m      :  6,    //   6: 1
    reg_dbb__admd_dpll_pdb    :  1,    //      7
    reg_dbb__admd_dpll_icp    :  4,    //  11: 8
    reg_dbb__admd_q_sel_clkinv:  1,    //     12
    reg_dbb__admd_adc_refsel  :  2,    //  14:13
    reg_dbb__admd_dpll_lockf  :  1,    //     15
    reg_dbb__admd_apll_pdb    :  1,    //     16
    reg_dbb__admd_dpll_odpost :  6,    //  22:17
    reg_dbb__admd_dpll_divint :  9;    //  31:23
}CTOP_DBB_ADMD_MIP8_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1824    admd_mip9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 26,    //  25: 0 reserved
    reg_dbb__admd_apll_odpre  :  6;    //  31:26
}CTOP_DBB_ADMD_MIP9_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1828    videoafe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__reset_n          :  1,    //      0
    reg_dbb__llpll_lpf_clk_div:  2,    //   2: 1
    reg_dbb__videoafe_cvbs_pdbm: 1,    //      3
    reg_dbb__videoafe_cvbs_decm: 2,    //   5: 4
    reg_dbb__llpll_sf_mode_control: 4,    //  9:6
    reg_dbb__videoafe_cvbs_dcsel: 2,    //  11:10
    reg_dbb__videoafe_adcisel_m: 2,    //  13:12
    reg_dbb__videoafe_rpdb    :  1,    //     14
    reg_dbb__videoafe_adc_fil :  3,    //  17:15
    reg_dbb__videoafe_cvbs_adcisel_ps: 2,    //  19:18
    reg_dbb__videoafe_adcisel_f3: 2,    //  21:20
    reg_dbb__llpll_shift      : 10;    //  31:22
}CTOP_DBB_VIDEOAFE10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_182C    videoafe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__videoafe_ref_sel :  2,    //   1: 0
    reg_dbb__videoafe_sog_soui:  2,    //   3: 2
    reg_dbb__videoafe_clpcur  :  3,    //   6: 4
    reg_dbb__videoafe_cvbs_iclp2: 2,    //  8: 7
    reg_dbb__videoafe_sog_hys :  2,    //  10: 9
    reg_dbb__videoafe_cvbs_clp:  1,    //     11
    reg_dbb__videoafe_sel_invdatack: 1,    //  12
    reg_dbb__llpll_dco_max    :  5,    //  17:13
    reg_dbb__videoafe_cvbs_bw :  1,    //     18
    reg_dbb__videoafe_sog_bw  :  2,    //  20:19
    reg_dbb__videoafe_ire_test:  1,    //     21
    reg_dbb__videoafe_icon_buf:  3,    //  24:22
    reg_dbb__refpll_pdb       :  1,    //     25
    reg_dbb__videoafe_adcisel_ps: 2,    //  27:26
    reg_dbb__llpll_nsc        :  4;    //  31:28
}CTOP_DBB_VIDEOAFE11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1830    videoafe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__videoafe_cvbs_adcisel_f3: 2,    //  2:1
    reg_dbb__videoafe_ire_sel :  2,    //   4: 3
    reg_dbb__videoafe_gvclpsel:  1,    //      5
    reg_dbb__videoafe_biaspdb :  1,    //      6
    reg_dbb__videoafe_cvbs_adcisel_m: 2,    //  8:7
    reg_dbb__llpll_coarse_scale: 4,    //  12: 9
    reg_dbb__videoafe_cvbs_dcatt: 1,    //    13
    reg_dbb__videoafe_sog_deglitch: 4,    //  17:14
    reg_dbb__llpll_diff_monitor: 12,    //  29:18
    reg_dbb__videoafe_adcisel_ref: 2;    //  31:30
}CTOP_DBB_VIDEOAFE12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1834    videoafe13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__llpll_div10_sel  :  1,    //      0
    reg_dbb__videoafe_ibs_50u_sel: 1,    //    1
    reg_dbb__videoafe_sel_fs  :  1,    //      2
    reg_dbb__videoafe_vclp_en :  1,    //      3
    reg_dbb__llpll_ref_lock_ctl: 2,    //   5: 4
    reg_dbb__videoafe_sog_fil :  3,    //   8: 6
    reg_dbb__llpll_g3_p_nom   :  5,    //  13: 9
    reg_dbb__llpll_disable_fm :  1,    //     14
    reg_dbb__llpll_cvbs_lock  :  2,    //  16:15
    reg_dbb__llpll_ref_vcon   :  1,    //     17
    reg_dbb__llpll_g2_fine    :  5,    //  22:18
    reg_dbb__videoafe_cvbs_gc :  3,    //  25:23
    reg_dbb__videoafe_sog2dig_sel: 1,    //   26
    reg_dbb__llpll_npc        :  5;    //  31:27
}CTOP_DBB_VIDEOAFE13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1838    videoafe14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__videoafe_reserved:  8,    //   7: 0
    reg_dbb__videoafe_cvbs_adcisel_ref: 2,    //  9:8
    reg_dbb__llpll_g1_fine    :  5,    //  14:10
    reg_dbb__videoafe_bvclpsel:  1,    //     15
    reg_dbb__videoafe_sel_datack: 1,    //    16
    reg_dbb__videoafe_sog_enwin: 1,    //     17
    reg_dbb__llpll_g3_n_fine  :  5,    //  22:18
    reg_dbb__videoafe_rvclpsel:  1,    //     23
    reg_dbb__llpll_icpcon     :  5,    //  28:24
    reg_dbb__videoafe_cvbs_shield_on: 2,    //  30:29
    reg_dbb__llpll_div12_sel  :  1;    //     31
}CTOP_DBB_VIDEOAFE14_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_183C    videoafe15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_dbb__videoafe_soglvl  :  5,    //   7: 3
    reg_dbb__llpll_lpfr_dis   :  1,    //      8
    reg_dbb__videoafe_cvbs_isel: 3,    //  11: 9
    reg_dbb__llpll_g1_nom     :  5,    //  16:12
    reg_dbb__llpll_g3_p_fine  :  5,    //  21:17
    reg_dbb__videoafe_icon_adc:  3,    //  24:22
    reg_dbb__llpll_cpll_pdb   :  1,    //     25
    reg_dbb__videoafe_sog_ssfil: 2,    //  27:26
    reg_dbb__videoafe_shield_on: 1,    //     28
    reg_dbb__videoafe_cvbs_cksel: 1,    //    29
    reg_dbb__videoafe_gpdb    :  1,    //     30
    reg_dbb__videoafe_sog_outmux: 1;    //    31
}CTOP_DBB_VIDEOAFE15_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1840    videoafe16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 11,    //  10: 0 reserved
    reg_dbb__videoafe_sel_ck  :  2,    //  12:11
    reg_dbb__videoafe_sog_sinki: 3,    //  15:13
    reg_dbb__videoafe_cvbs_refsel: 2,    //  17:16
    reg_dbb__llpll_filter_status: 2,    //  19:18
    reg_dbb__llpll_counter_max: 12;    //  31:20
}CTOP_DBB_VIDEOAFE16_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1844    videoafe17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_dbb__videoafe_cvbs_ibuf: 3,    //   5: 3
    reg_dbb__videoafe_cvbs_lpf:  1,    //      6
    reg_dbb__videoafe_cvbs_iclp: 2,    //   8: 7
    reg_dbb__llpll_div_max    :  6,    //  14: 9
    reg_dbb__videoafe_adcisel_f12: 2,    //  16:15
    reg_dbb__llpll_lpf_clk_sel:  1,    //     17
    reg_dbb__llpll_in_sel     :  1,    //     18
    reg_dbb__videoafe_cvbs_pdb:  1,    //     19
    reg_dbb__llpll_counter_monitor: 12;    //  31:20
}CTOP_DBB_VIDEOAFE17_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1848    videoafe18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 19,    //  18: 0 reserved
    reg_dbb__videoafe_cvbs_insel: 1,    //    19
    reg_dbb__llpll_dco_min    :  5,    //  24:20
    reg_dbb__llpll_dco_test_mode: 1,    //    25
    reg_dbb__videoafe_bpdb    :  1,    //     26
    reg_dbb__llpll_g2_nom     :  5;    //  31:27
}CTOP_DBB_VIDEOAFE18_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_184C    videoafe19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_dbb__videoafe_cvbs_adcisel_f12: 2,    //  2:1
    reg_dbb__llpll_dco_control_monitor: 29;    //  31:3
}CTOP_DBB_VIDEOAFE19_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1850    videoafe20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 23,    //  22: 0 reserved
    reg_dbb__llpll_disable_sfm:  1,    //     23
    reg_dbb__llpll_g3_n_nom   :  5,    //  28:24
    reg_dbb__videoafe_ire_selrefck: 1,    //  29
    reg_dbb__videoafe_decm    :  2;    //  31:30
}CTOP_DBB_VIDEOAFE20_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1854    rxclkdrv_md22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 28,    //  27: 0 reserved
    reg_dbb__rxclkdrv_md_smv  :  1,    //     28
    reg_dbb__rxclkdrv_md_cksel:  2,    //  30:29
    reg_dbb__rxclkdrv_md_pdb  :  1;    //     31
}CTOP_DBB_RXCLKDRV_MD22_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1858    adc_output ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__adc_output_mex_sel: 4,    //   3: 0
                              : 28;    //   31:4 reserved
}CTOP_DBB_ADC_OUTPUT_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_185C    emmcsyn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 25,    //  24: 0 reserved
    reg_dbb__dbbi2csel        :  1,    //     25
                              :  6;    //  31:26 reserved
}CTOP_DBB_EMMCSYN_00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1860    emmcsyn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__usb0_axi_addr_31 :  1,    //      0
    reg_dbb__usb1_axi_addr_31 :  1,    //      1
    reg_dbb__usb2_axi_addr_31 :  1,    //      2
    reg_dbb__usb3_axi_addr_31 :  1,    //      3
                              : 28;    //   31:4 reserved
}CTOP_DBB_EMMCSYN_01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1864    emmcsyn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__ls_disable_dbb   :  1,    //      0
    reg_dbb__ls_disable_usb   :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_DBB_EMMCSYN_02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1868    emmcsyn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__bbopermode       :  8,    //   7: 0
    reg_dbb__dbbreg_init      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dbb__reset            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb__mcu_reset        :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_DBB_EMMCSYN_03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_186C    emmcsyn_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}CTOP_DBB_EMMCSYN_04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1870    emmcsyn_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}CTOP_DBB_EMMCSYN_05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1874    emmcsyn_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__usb_hs_0_usb_bist_error: 1,    //  0
    reg_usb_hs__usb_hs_0_usb_bist_done: 1,    //  1
    reg_usb_hs__usb_hs_1_usb_bist_error: 1,    //  2
    reg_usb_hs__usb_hs_1_usb_bist_done: 1,    //  3
    reg_usb_hs__usb_hs_2_usb_bist_error: 1,    //  4
    reg_usb_hs__usb_hs_2_usb_bist_done: 1,    //  5
    reg_usb_hs__usb_hs_3_usb_bist_error: 1,    //  6
    reg_usb_hs__usb_hs_3_usb_bist_done: 1,    //  7
                              : 24;    //   31:8 reserved
}CTOP_DBB_EMMCSYN_06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1878    emmcsyn_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqci__st       :  1,    //      0
    reg_pad_diseqci__pu       :  1,    //      1
    reg_pad_diseqci__pd       :  1,    //      2
    reg_pad_diseqci__ds3      :  1,    //      3
    reg_pad_diseqci__ds2      :  1,    //      4
    reg_pad_diseqci__ds1      :  1,    //      5
    reg_pad_diseqci__ds0      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_diseqc_cmd__st    :  1,    //      8
    reg_pad_diseqc_cmd__pu    :  1,    //      9
    reg_pad_diseqc_cmd__pd    :  1,    //     10
    reg_pad_diseqc_cmd__ds3   :  1,    //     11
    reg_pad_diseqc_cmd__ds2   :  1,    //     12
    reg_pad_diseqc_cmd__ds1   :  1,    //     13
    reg_pad_diseqc_cmd__ds0   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_diseqc__st        :  1,    //     16
    reg_pad_diseqc__pu        :  1,    //     17
    reg_pad_diseqc__pd        :  1,    //     18
    reg_pad_diseqc__ds3       :  1,    //     19
    reg_pad_diseqc__ds2       :  1,    //     20
    reg_pad_diseqc__ds1       :  1,    //     21
    reg_pad_diseqc__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_uart0_txd__st     :  1,    //     24
    reg_pad_uart0_txd__pu     :  1,    //     25
    reg_pad_uart0_txd__pd     :  1,    //     26
    reg_pad_uart0_txd__ds3    :  1,    //     27
    reg_pad_uart0_txd__ds2    :  1,    //     28
    reg_pad_uart0_txd__ds1    :  1,    //     29
    reg_pad_uart0_txd__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_DBB_EMMCSYN_07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_187C    emmcsyn_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio28__st        :  1,    //      0
    reg_pad_gpio28__pu        :  1,    //      1
    reg_pad_gpio28__pd        :  1,    //      2
    reg_pad_gpio28__ds3       :  1,    //      3
    reg_pad_gpio28__ds2       :  1,    //      4
    reg_pad_gpio28__ds1       :  1,    //      5
    reg_pad_gpio28__ds0       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio27__st        :  1,    //      8
    reg_pad_gpio27__pu        :  1,    //      9
    reg_pad_gpio27__pd        :  1,    //     10
    reg_pad_gpio27__ds3       :  1,    //     11
    reg_pad_gpio27__ds2       :  1,    //     12
    reg_pad_gpio27__ds1       :  1,    //     13
    reg_pad_gpio27__ds0       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio26__st        :  1,    //     16
    reg_pad_gpio26__pu        :  1,    //     17
    reg_pad_gpio26__pd        :  1,    //     18
    reg_pad_gpio26__ds3       :  1,    //     19
    reg_pad_gpio26__ds2       :  1,    //     20
    reg_pad_gpio26__ds1       :  1,    //     21
    reg_pad_gpio26__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_fefctrl__st       :  1,    //     24
    reg_pad_fefctrl__pu       :  1,    //     25
    reg_pad_fefctrl__pd       :  1,    //     26
    reg_pad_fefctrl__ds3      :  1,    //     27
    reg_pad_fefctrl__ds2      :  1,    //     28
    reg_pad_fefctrl__ds1      :  1,    //     29
    reg_pad_fefctrl__ds0      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_DBB_EMMCSYN_08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1880    emmcsyn_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_ext2__st:  1,    //      0
    reg_pad_tpi_data0_ext2__pu:  1,    //      1
    reg_pad_tpi_data0_ext2__pd:  1,    //      2
    reg_pad_tpi_data0_ext2__ds3: 1,    //      3
    reg_pad_tpi_data0_ext2__ds2: 1,    //      4
    reg_pad_tpi_data0_ext2__ds1: 1,    //      5
    reg_pad_tpi_data0_ext2__ds0: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_clk_ext2__st  :  1,    //      8
    reg_pad_tpi_clk_ext2__pu  :  1,    //      9
    reg_pad_tpi_clk_ext2__pd  :  1,    //     10
    reg_pad_tpi_clk_ext2__ds3 :  1,    //     11
    reg_pad_tpi_clk_ext2__ds2 :  1,    //     12
    reg_pad_tpi_clk_ext2__ds1 :  1,    //     13
    reg_pad_tpi_clk_ext2__ds0 :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ifagc_s__st       :  1,    //     16
    reg_pad_ifagc_s__pu       :  1,    //     17
    reg_pad_ifagc_s__pd       :  1,    //     18
    reg_pad_ifagc_s__ds3      :  1,    //     19
    reg_pad_ifagc_s__ds2      :  1,    //     20
    reg_pad_ifagc_s__ds1      :  1,    //     21
    reg_pad_ifagc_s__ds0      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ifagc__st         :  1,    //     24
    reg_pad_ifagc__pu         :  1,    //     25
    reg_pad_ifagc__pd         :  1,    //     26
    reg_pad_ifagc__ds3        :  1,    //     27
    reg_pad_ifagc__ds2        :  1,    //     28
    reg_pad_ifagc__ds1        :  1,    //     29
    reg_pad_ifagc__ds0        :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_DBB_EMMCSYN_09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1884    emmcsyn_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_rxd__st     :  1,    //      0
    reg_pad_uart0_rxd__pu     :  1,    //      1
    reg_pad_uart0_rxd__pd     :  1,    //      2
    reg_pad_uart0_rxd__ds3    :  1,    //      3
    reg_pad_uart0_rxd__ds2    :  1,    //      4
    reg_pad_uart0_rxd__ds1    :  1,    //      5
    reg_pad_uart0_rxd__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data3_ext2__st:  1,    //      8
    reg_pad_tpi_data3_ext2__pu:  1,    //      9
    reg_pad_tpi_data3_ext2__pd:  1,    //     10
    reg_pad_tpi_data3_ext2__ds3: 1,    //     11
    reg_pad_tpi_data3_ext2__ds2: 1,    //     12
    reg_pad_tpi_data3_ext2__ds1: 1,    //     13
    reg_pad_tpi_data3_ext2__ds0: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data2_ext2__st:  1,    //     16
    reg_pad_tpi_data2_ext2__pu:  1,    //     17
    reg_pad_tpi_data2_ext2__pd:  1,    //     18
    reg_pad_tpi_data2_ext2__ds3: 1,    //     19
    reg_pad_tpi_data2_ext2__ds2: 1,    //     20
    reg_pad_tpi_data2_ext2__ds1: 1,    //     21
    reg_pad_tpi_data2_ext2__ds0: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data1_ext2__st:  1,    //     24
    reg_pad_tpi_data1_ext2__pu:  1,    //     25
    reg_pad_tpi_data1_ext2__pd:  1,    //     26
    reg_pad_tpi_data1_ext2__ds3: 1,    //     27
    reg_pad_tpi_data1_ext2__ds2: 1,    //     28
    reg_pad_tpi_data1_ext2__ds1: 1,    //     29
    reg_pad_tpi_data1_ext2__ds0: 1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_DBB_EMMCSYN_10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1888    emmcsyn_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_txd_mux_sel :  4,    //   3: 0
    reg_pad_gpio28_mux_sel    :  4,    //   7: 4
    reg_pad_gpio27_mux_sel    :  4,    //  11: 8
    reg_pad_gpio26_mux_sel    :  4,    //  15:12
    reg_pad_fefctrl_mux_sel   :  4,    //  19:16
    reg_pad_diseqci_mux_sel   :  4,    //  23:20
    reg_pad_diseqc_mux_sel    :  4,    //  27:24
    reg_pad_diseqc_cmd_mux_sel:  4;    //  31:28
}CTOP_DBB_EMMCSYN_11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_188C    emmcsyn_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ifagc_s_mux_sel   :  4,    //   3: 0
    reg_pad_ifagc_mux_sel     :  4,    //   7: 4
    reg_pad_uart0_rxd_mux_sel :  4,    //  11: 8
    reg_pad_tpi_data3_ext2_mux_sel: 4,    //  15:12
    reg_pad_tpi_data2_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data1_ext2_mux_sel: 4,    //  23:20
    reg_pad_tpi_data0_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_clk_ext2_mux_sel: 4;    //  31:28
}CTOP_DBB_EMMCSYN_12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1890    emmcsyn_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb__apb_base_sel     :  1,    //      0
    reg_dbb__pll_cgen         :  1,    //      1
    reg_dbb__mcuclk_sel       :  2,    //   3: 2
                              : 28;    //   31:4 reserved
}CTOP_DBB_EMMCSYN_13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1894    aad_pll ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aioplls_aad_lock      :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_aioplls_aad_out_div   :  2,    //  12:11
                              :  1,    //     13 reserved
    reg_aioplls_aad_fout2_en  :  1,    //     14
    reg_aioplls_aad_fb_m      :  8,    //  22:15
    reg_aioplls_aad_cih       :  4,    //  26:23
    reg_aioplls_aad_fout1_en  :  1,    //     27
    reg_aioplls_aad_cih2      :  4;    //  31:28
}CTOP_DBB_AAD_PLL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_1898    dbb_syn_control ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_DBB_DBB_SYN_CONTROL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_189C    dbb_syn_control1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f50_sel               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_f27_18_sel            :  1,    //      4
    reg_f200_sel              :  1,    //      5
                              :  6,    //  11: 6 reserved
    reg_sc_ext_sel            :  3,    //  14:12
                              : 17;    //  31:15 reserved
}CTOP_DBB_DBB_SYN_CONTROL1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC30C_18A0    frpll29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_aad_smv      :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_DBB_FRPLL29_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                                   acodec0                  ;         // 0xC30C_1800
    CTOP_DBB_ACODEC1_E60_A0_T                acodec1                  ;         // 0xC30C_1804
    CTOP_DBB_ACODEC2_E60_A0_T                acodec2                  ;         // 0xC30C_1808
    CTOP_DBB_ACODEC3_E60_A0_T                acodec3                  ;         // 0xC30C_180C
    CTOP_DBB_ACODEC4_E60_A0_T                acodec4                  ;         // 0xC30C_1810
    CTOP_DBB_ADMD_MIP5_E60_A0_T              admd_mip5                ;         // 0xC30C_1814
    CTOP_DBB_ADMD_MIP6_E60_A0_T              admd_mip6                ;         // 0xC30C_1818
    CTOP_DBB_ADMD_MIP7_E60_A0_T              admd_mip7                ;         // 0xC30C_181C
    CTOP_DBB_ADMD_MIP8_E60_A0_T              admd_mip8                ;         // 0xC30C_1820
    CTOP_DBB_ADMD_MIP9_E60_A0_T              admd_mip9                ;         // 0xC30C_1824
    CTOP_DBB_VIDEOAFE10_E60_A0_T             videoafe10               ;         // 0xC30C_1828
    CTOP_DBB_VIDEOAFE11_E60_A0_T             videoafe11               ;         // 0xC30C_182C
    CTOP_DBB_VIDEOAFE12_E60_A0_T             videoafe12               ;         // 0xC30C_1830
    CTOP_DBB_VIDEOAFE13_E60_A0_T             videoafe13               ;         // 0xC30C_1834
    CTOP_DBB_VIDEOAFE14_E60_A0_T             videoafe14               ;         // 0xC30C_1838
    CTOP_DBB_VIDEOAFE15_E60_A0_T             videoafe15               ;         // 0xC30C_183C
    CTOP_DBB_VIDEOAFE16_E60_A0_T             videoafe16               ;         // 0xC30C_1840
    CTOP_DBB_VIDEOAFE17_E60_A0_T             videoafe17               ;         // 0xC30C_1844
    CTOP_DBB_VIDEOAFE18_E60_A0_T             videoafe18               ;         // 0xC30C_1848
    CTOP_DBB_VIDEOAFE19_E60_A0_T             videoafe19               ;         // 0xC30C_184C
    CTOP_DBB_VIDEOAFE20_E60_A0_T             videoafe20               ;         // 0xC30C_1850
    CTOP_DBB_RXCLKDRV_MD22_E60_A0_T          rxclkdrv_md22            ;         // 0xC30C_1854
    CTOP_DBB_ADC_OUTPUT_E60_A0_T             adc_output               ;         // 0xC30C_1858
    CTOP_DBB_EMMCSYN_00_E60_A0_T             emmcsyn_00               ;         // 0xC30C_185C
    CTOP_DBB_EMMCSYN_01_E60_A0_T             emmcsyn_01               ;         // 0xC30C_1860
    CTOP_DBB_EMMCSYN_02_E60_A0_T             emmcsyn_02               ;         // 0xC30C_1864
    CTOP_DBB_EMMCSYN_03_E60_A0_T             emmcsyn_03               ;         // 0xC30C_1868
    CTOP_DBB_EMMCSYN_04_E60_A0_T             emmcsyn_04               ;         // 0xC30C_186C
    CTOP_DBB_EMMCSYN_05_E60_A0_T             emmcsyn_05               ;         // 0xC30C_1870
    CTOP_DBB_EMMCSYN_06_E60_A0_T             emmcsyn_06               ;         // 0xC30C_1874
    CTOP_DBB_EMMCSYN_07_E60_A0_T             emmcsyn_07               ;         // 0xC30C_1878
    CTOP_DBB_EMMCSYN_08_E60_A0_T             emmcsyn_08               ;         // 0xC30C_187C
    CTOP_DBB_EMMCSYN_09_E60_A0_T             emmcsyn_09               ;         // 0xC30C_1880
    CTOP_DBB_EMMCSYN_10_E60_A0_T             emmcsyn_10               ;         // 0xC30C_1884
    CTOP_DBB_EMMCSYN_11_E60_A0_T             emmcsyn_11               ;         // 0xC30C_1888
    CTOP_DBB_EMMCSYN_12_E60_A0_T             emmcsyn_12               ;         // 0xC30C_188C
    CTOP_DBB_EMMCSYN_13_E60_A0_T             emmcsyn_13               ;         // 0xC30C_1890
    CTOP_DBB_AAD_PLL_E60_A0_T                aad_pll                  ;         // 0xC30C_1894
    CTOP_DBB_DBB_SYN_CONTROL_E60_A0_T        dbb_syn_control          ;         // 0xC30C_1898
    CTOP_DBB_DBB_SYN_CONTROL1_E60_A0_T       dbb_syn_control1         ;         // 0xC30C_189C
    CTOP_DBB_FRPLL29_E60_A0_T                frpll29                  ;         // 0xC30C_18A0
} CTOP_SYN_DBB_REG_E60_A0_T;
/* 41 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_DBB_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

