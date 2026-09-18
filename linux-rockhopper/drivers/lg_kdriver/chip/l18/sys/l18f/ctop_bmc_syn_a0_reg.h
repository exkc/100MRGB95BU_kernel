#ifndef _CTOP_BMC_SYN_A0_REG_H_
#define _CTOP_BMC_SYN_A0_REG_H_

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
    0xC930_E400    syn_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_abb_reset_n           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_abb_i2c_sel           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_dbb_reset             :  1,    //      8
                              :  7,    //  15: 9 reserved
    reg_bbopermode            :  8,    //  23:16
                              :  8;    //  31:24 reserved
}BMC_SYN_SYN_BMC00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E404    syn_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_md_smv       :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_SYN_BMC01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E408    syn_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_rstb             :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_apll_pdb              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_apll_od               :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_apll_dco_g            :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_apll_dco_test         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_apll_dco_rstb         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_apll_dco_lpf          :  2,    //  25:24
                              :  5,    //  30:26 reserved
    apll_lockd                :  1;    //     31
}BMC_SYN_SYN_BMC02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E40C    syn_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_reserved         :  8,    //   7: 0
    reg_apll_cont             :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_apll_cpc              :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_apll_test             :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_apll_ci               :  3,    //  22:20
                              :  9;    //  31:23 reserved
}BMC_SYN_SYN_BMC03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E410    syn_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_dco_fcw          : 22,    //  21: 0
                              : 10;    //  31:22 reserved
}BMC_SYN_SYN_BMC04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E414    syn_bmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_auda_ic_scf           :  2,    //   3: 2
                              :  2,    //   5: 4 reserved
    reg_auda_ic_ref           :  2,    //   7: 6
                              :  2,    //   9: 8 reserved
    reg_auda_ic_refp          :  2,    //  11:10
                              :  2,    //  13:12 reserved
    reg_auda_ic_d2s           :  2,    //  15:14
    reg_auda_chop_freq        :  2,    //  17:16
    reg_auda_chop_refp_en     :  1,    //     18
    reg_auda_chop_en          :  1,    //     19
                              :  1,    //     20 reserved
    reg_auda_pdb_scf          :  1,    //     21
                              :  1,    //     22 reserved
    reg_auda_pdb_ref          :  1,    //     23
                              :  1,    //     24 reserved
    reg_auda_pdb_refgen       :  1,    //     25
                              :  1,    //     26 reserved
    reg_auda_pdb_d2s          :  1,    //     27
                              :  1,    //     28 reserved
    reg_auda_pdb_clk          :  1,    //     29
                              :  2;    //  31:30 reserved
}BMC_SYN_SYN_BMC05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E418    syn_bmc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_chop_pga_ref_en  :  1,    //      0
    reg_auad_chop_refp_en     :  1,    //      1
    reg_auad_sdm_chop_en      :  1,    //      2
    reg_auad_pga_chop_en      :  1,    //      3
    reg_auad_refp_en          :  1,    //      4
    reg_auad_pdb_refp         :  1,    //      5
    reg_auad_adc_pdb          :  1,    //      6
    reg_auad_pga_pdb          :  1,    //      7
    reg_auad_pga_ref_pdb      :  1,    //      8
                              :  1,    //      9 reserved
    reg_auad_ic_pga           :  2,    //  11:10
    reg_auad_ic_quant         :  2,    //  13:12
    reg_auad_ic_int23         :  2,    //  15:14
    reg_auad_ic_int1          :  2,    //  17:16
    reg_auad_ic_pga_refr      :  2,    //  19:18
    reg_auad_ic_pga_refl      :  2,    //  21:20
    reg_auad_ic_refpr         :  2,    //  23:22
    reg_auad_ic_refpl         :  2,    //  25:24
    reg_auda_vcont_refp       :  3,    //  28:26
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E41C    syn_bmc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_vcom_cont         :  2,    //   1: 0
    reg_aud_sel_vref_out      :  1,    //      2
    reg_aud_pdb_bias          :  1,    //      3
    reg_aud_ic_bgr            :  2,    //   5: 4
    reg_aud_ic_vcom           :  2,    //   7: 6
    reg_aud_ic_vbuf           :  2,    //   9: 8
    reg_aud_ic_iref           :  2,    //  11:10
    reg_auad_pga_ref_en_int   :  1,    //     12
    reg_auad_pga_ref_en_ext   :  1,    //     13
                              :  2,    //  15:14 reserved
    reg_auad_vcont_refp       :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_auad_div_sel_sdm      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_auad_div_sel          :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_auad_pga_gcont        :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BMC_SYN_SYN_BMC07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E420    syn_bmc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_reserved              :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_aud_chop_bgr_en       :  1,    //      8
    reg_aud_chop_vcom_en      :  1,    //      9
    reg_aud_chop_vbuf_en      :  1,    //     10
                              :  1,    //     11 reserved
    reg_aud_ccont             :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_aud_ft_mode           :  1,    //     16
    reg_aud_cnt_rdiv          :  1,    //     17
                              :  2,    //  19:18 reserved
    reg_aud_res               :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_auad_refn_en          :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_auad_mclk_en          :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E424    syn_bmc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_adcclk_test       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aad_adc_pdb           :  1,    //      4
                              : 11,    //  15: 5 reserved
    reg_aad_adc_selsif        :  1,    //     16
    aad_adc_pga_icon          :  1,    //     17
    reg_aad_adc_clk_inv       :  1,    //     18
    reg_aad_adc_selref        :  3,    //  21:19
    reg_aad_adc_decm          :  2,    //  23:22
    reg_aad_adc_icon          :  3,    //  26:24
                              :  5;    //  31:27 reserved
}BMC_SYN_SYN_BMC09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E428    syn_bmc10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_pll_lock_sw       :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_aad_pll_div5sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_aad_pll_divrst        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_aad_pll_mc            :  6,    //  17:12
                              :  2,    //  19:18 reserved
    reg_aad_pll_icp           :  4,    //  23:20
    reg_aad_pll_pdb           :  1,    //     24
                              :  7;    //  31:25 reserved
}BMC_SYN_SYN_BMC10_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E42C    syn_bmc11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_pll_lock          :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_SYN_BMC11_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E430    syn_bmc12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_pll_a_oen         :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_aad_pll_a_odiv        :  5,    //   8: 4
                              :  3,    //  11: 9 reserved
    reg_aad_pll_aon_odiv      :  1,    //     12
                              : 19;    //  31:13 reserved
}BMC_SYN_SYN_BMC12_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E434    syn_bmc13 ''
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
}BMC_SYN_SYN_BMC13_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E438    syn_bmc14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_sifdac_lpfband    :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_dmd_sifdac_mute       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dmd_sifdac_icnt       :  4,    //  11: 8
    reg_dmd_sifdac_pdb        :  1,    //     12
                              :  7,    //  19:13 reserved
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
}BMC_SYN_SYN_BMC14_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E43C    syn_bmc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_adc_refsel        :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_dmd_adc_icon          :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_dmd_bias_pdb          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dmd_sifdac_ires       :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_dmd_sifdac_intflt     :  1,    //     16
                              : 15;    //  31:17 reserved
}BMC_SYN_SYN_BMC15_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E440    syn_bmc16 ''
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
}BMC_SYN_SYN_BMC16_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E444    syn_bmc17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_pll_lock          :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_SYN_BMC17_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E448    syn_bmc18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_bpdb         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_videoafe_decm         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_videoafe_sel_invdatack:  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_videoafe_sel_datack   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_videoafe_gvclpsel     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_gpdb         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_videoafe_rvclpsel     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_rpdb         :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC18_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E44C    syn_bmc19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_soglvl       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_videoafe_sog_soui     :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_videoafe_sog_sinki    :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_videoafe_sog_bw       :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_videoafe_sog_hys      :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_videoafe_sel_fs       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_bvclpsel     :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC19_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E450    syn_bmc20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_reserved     :  8,    //   7: 0
    reg_videoafe_ibs_50u_sel  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_videoafe_ref_sel      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_ire_sel      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_videoafe_biaspdb      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_videoafe_sog_ssfil    :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_videoafe_sog_fil      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BMC_SYN_SYN_BMC20_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E454    syn_bmc21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_adcisel_f34  :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_videoafe_adcisel_f12  :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_videoafe_adcisel_m    :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_videoafe_adcisel_ref  :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_adcisel_ps   :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_videoafe_adc_fil      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_videoafe_shield_on    :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_ire_test     :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC21_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E458    syn_bmc22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_sog2dig      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_videoafe_sog_enwin    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_videoafe_ire_selrefck :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_videoafe_sel_ck       :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_vclp_en      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_icon_adc     :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_videoafe_icon_buf     :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_videoafe_clpcur       :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BMC_SYN_SYN_BMC22_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E45C    syn_bmc23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_ref_vcon        :  1,    //      0
                              :  3,    //   3: 1 reserved
    refpll_pdb                :  1,    //      4
    llpll_cpll_pdb            :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_llpll_icpcon          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_videoafe_cvbs_cksel   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_sog_deglitch :  4,    //  23:20
    reg_videoafe_sog_outmux   :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_sog2dig_sel  :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC23_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E460    syn_bmc24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_div_max         :  5,    //   4: 0
                              :  7,    //  11: 5 reserved
    reg_llpll_ref_lock_ctl    :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_llpll_cvbs_mc         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_llpll_nsc             :  4,    //  23:20
    reg_llpll_npc             :  5,    //  28:24
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC24_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E464    syn_bmc25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_dco_control_monitor: 29,    //  28:0
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC25_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E468    syn_bmc26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_counter_monitor : 12,    //  11: 0
    reg_llpll_filter_status   :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_llpll_diff_monitor    : 12,    //  27:16
    reg_llpll_cvbs_lock       :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BMC_SYN_SYN_BMC26_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E46C    syn_bmc27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_g2_fine         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_llpll_g3_p_fine       :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_llpll_g3_n_fine       :  5,    //  20:16
                              : 11;    //  31:21 reserved
}BMC_SYN_SYN_BMC27_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E470    syn_bmc28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_g2_nom          :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_llpll_g3_p_nom        :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_llpll_g3_n_nom        :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_llpll_g1_fine         :  5,    //  28:24
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC28_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E474    syn_bmc29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_dco_min         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_llpll_sf_mode_control :  4,    //  11: 8
                              :  4,    //  15:12 reserved
    reg_llpll_coarse_scale    :  4,    //  19:16
                              :  4,    //  23:20 reserved
    reg_llpll_g1_nom          :  5,    //  28:24
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC29_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E478    syn_bmc30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_counter_max     : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    reg_llpll_dco_max         :  5,    //  20:16
                              : 11;    //  31:21 reserved
}BMC_SYN_SYN_BMC30_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E47C    syn_bmc31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_shift           : 10,    //   9: 0
                              :  2,    //  11:10 reserved
    reg_llpll_lpf_clk_sel     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_llpll_lpf_clk_div     :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_llpll_dco_test_mode   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_llpll_disable_fm      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_llpll_disable_sfm     :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC31_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E480    syn_bmc32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_cvbs_pdbm    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_videoafe_cvbs_dcsel   :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_videoafe_cvbs_refsel  :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_videoafe_cvbs_isel    :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_videoafe_cvbsafe_seldac: 1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_cvbsafe_selp :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_videoafe_cvbs_decm    :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_videoafe_reset_n      :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC32_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E484    syn_bmc33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_cvbs_clp     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_videoafe_cvbs_iclp    :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_videoafe_cvbs_ibuf    :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_videoafe_cvbs_iclp2   :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_cvbs_pdb     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_cvbs_bw      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_videoafe_cvbs_lpf     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_cvbs_gc      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BMC_SYN_SYN_BMC33_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E488    syn_bmc34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_cvbs_shield_on: 2,    //   1: 0
    reg_videoafe_cvbs_adcisel_ps: 2,    //  3: 2
    reg_videoafe_cvbs_adcisel_ref: 2,    //  5:4
                              :  2,    //   7: 6 reserved
    reg_videoafe_cvbs_adcisel_m: 2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_videoafe_cvbs_adcisel_f12: 2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_cvbs_adcisel_f34: 2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_videoafe_cvbs_dcatt   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_videoafe_cvbs_insel   :  1,    //     24
                              :  7;    //  31:25 reserved
}BMC_SYN_SYN_BMC34_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E490    syn_bmc36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_mon_enable4       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_mon_enable4       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_imx_mon_enable4       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc_mon_enable4       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_cvi_mon_enable4       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_cco_mon_enable4       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aud_mon_enable4       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aad_mon_enable4       :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC36_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E494    syn_bmc37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_abb2_mon_en4          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_abb1_mon_en4          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_abb0_mon_en4          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_te_mon_en4            :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_vsd_mon_enable4       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_vdec_mon_enable4      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_tcon_mon_enable4      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_pmcu_mon_enable4      :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC37_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E498    syn_bmc38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu3_mon_en4          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cpu2_mon_en4          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu1_mon_en4          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu0_mon_en4          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dbb2_mon_en4          :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_dbb1_mon_en4          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dbb0_mon_en4          :  1,    //     24
                              :  7;    //  31:25 reserved
}BMC_SYN_SYN_BMC38_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E49C    syn_bmc39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_use_cpu_gpio_2_6      :  1,    //      6
    reg_use_cpu_gpio_2_7      :  1,    //      7
                              :  1,    //      8 reserved
    reg_use_cpu_gpio_3_1      :  1,    //      9
    reg_use_cpu_gpio_3_2      :  1,    //     10
    reg_use_cpu_gpio_3_3      :  1,    //     11
    reg_use_cpu_gpio_3_4      :  1,    //     12
    reg_use_cpu_gpio_3_5      :  1,    //     13
    reg_use_cpu_gpio_3_6      :  1,    //     14
    reg_use_cpu_gpio_3_7      :  1,    //     15
    reg_use_cpu_gpio_4_0      :  1,    //     16
    reg_use_cpu_gpio_4_1      :  1,    //     17
    reg_use_cpu_gpio_4_2      :  1,    //     18
    reg_use_cpu_gpio_4_3      :  1,    //     19
    reg_use_cpu_gpio_4_4      :  1,    //     20
    reg_use_cpu_gpio_4_5      :  1,    //     21
    reg_use_cpu_gpio_17_6     :  1,    //     22
                              :  9;    //  31:23 reserved
}BMC_SYN_SYN_BMC39_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A0    syn_bmc40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_iec958out__ren    :  1,    //      0
    reg_pad_ifagc__ren        :  1,    //      1
    reg_pad_ifagc_s__ren      :  1,    //      2
    reg_pad_diseqc__ren       :  1,    //      3
    reg_pad_sda3__pd          :  1,    //      4
    reg_pad_sda3__pu          :  1,    //      5
    reg_pad_sda3__ds          :  1,    //      6
    reg_pad_scl3__pd          :  1,    //      7
    reg_pad_scl3__pu          :  1,    //      8
    reg_pad_scl3__ds          :  1,    //      9
    reg_pad_tp_dvb_val__ren   :  1,    //     10
    reg_pad_tp_dvb_sop__ren   :  1,    //     11
    reg_pad_tp_dvb_data7__ren :  1,    //     12
    reg_pad_tp_dvb_data6__ren :  1,    //     13
    reg_pad_tp_dvb_data5__ren :  1,    //     14
    reg_pad_tp_dvb_data4__ren :  1,    //     15
    reg_pad_tp_dvb_data3__ren :  1,    //     16
    reg_pad_tp_dvb_data2__ren :  1,    //     17
                              :  1,    //     18 reserved
    reg_pad_tp_dvb_data0__ren :  1,    //     19
    reg_pad_tp_dvb_clk__ren   :  1,    //     20
                              : 11;    //  31:21 reserved
}BMC_SYN_SYN_BMC40_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A4    syn_bmc41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_pd              :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_SYN_BMC41_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A8    syn_bmc42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_sel_rc                :  1,    //      2
    reg_sel_vdac              :  1,    //      3
    reg_sel_cvbs              :  1,    //      4
    reg_sel_sif               :  1,    //      5
    reg_sel_aad               :  1,    //      6
                              :  1,    //      7 reserved
    reg_sel_ifagc             :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_sel_ifagc_s           :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sel_diseqc            :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sel_fefctrl           :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_sel_diseqc_cmd        :  3,    //  26:24
                              :  5;    //  31:27 reserved
}BMC_SYN_SYN_BMC42_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4AC    syn_bmc43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_boot_mode_disable :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_i2c5_enable           :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_abb_i2c_enable        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu_i2c3_disable      :  1,    //     12
                              : 19;    //  31:13 reserved
}BMC_SYN_SYN_BMC43_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B0    syn_bmc44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_aud_dacrlrch      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_aud_dacclfch      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_aud_dacslrch      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_irblastertxd      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_uart1cts_n        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_uart1rts_n        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_dmd_pll_out_enable    :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aadafe_pll_out_enable :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_SYN_BMC44_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B4    syn_bmc48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tp_dvb_enable0        :  1,    //      0
    reg_tp_dvb_enable1        :  1,    //      1
    reg_tp_dvb_enable2        :  1,    //      2
    reg_tp_dvb_enable3        :  1,    //      3
    reg_tp_dvb_enable4        :  1,    //      4
                              :  7,    //  11: 5 reserved
    reg_tp_input_mux_sel      :  2,    //  13:12
                              : 18;    //  31:14 reserved
}BMC_SYN_SYN_BMC48_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B8    syn_bmc4c ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_dmd_s_adc         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sel_dmd_tc_adc        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_sel_aadafe_adcout     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sel_videoafe_cvbsdout :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_sel_videoafe_bdout    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_sel_videoafe_gdout    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_sel_videoafe_rdout    :  1,    //     24
                              :  7;    //  31:25 reserved
}BMC_SYN_SYN_BMC4C_L18F_A0;

/*-----------------------------------------------------------------------------------------
    bmc_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BMC_SYN_SYN_BMC00_L18F_A0                    syn_bmc00                ;         // 0xC930_E400
BMC_SYN_SYN_BMC01_L18F_A0                    syn_bmc01                ;         // 0xC930_E404
BMC_SYN_SYN_BMC02_L18F_A0                    syn_bmc02                ;         // 0xC930_E408
BMC_SYN_SYN_BMC03_L18F_A0                    syn_bmc03                ;         // 0xC930_E40C
BMC_SYN_SYN_BMC04_L18F_A0                    syn_bmc04                ;         // 0xC930_E410
BMC_SYN_SYN_BMC05_L18F_A0                    syn_bmc05                ;         // 0xC930_E414
BMC_SYN_SYN_BMC06_L18F_A0                    syn_bmc06                ;         // 0xC930_E418
BMC_SYN_SYN_BMC07_L18F_A0                    syn_bmc07                ;         // 0xC930_E41C
BMC_SYN_SYN_BMC08_L18F_A0                    syn_bmc08                ;         // 0xC930_E420
BMC_SYN_SYN_BMC09_L18F_A0                    syn_bmc09                ;         // 0xC930_E424
BMC_SYN_SYN_BMC10_L18F_A0                    syn_bmc10                ;         // 0xC930_E428
BMC_SYN_SYN_BMC11_L18F_A0                    syn_bmc11                ;         // 0xC930_E42C
BMC_SYN_SYN_BMC12_L18F_A0                    syn_bmc12                ;         // 0xC930_E430
BMC_SYN_SYN_BMC13_L18F_A0                    syn_bmc13                ;         // 0xC930_E434
BMC_SYN_SYN_BMC14_L18F_A0                    syn_bmc14                ;         // 0xC930_E438
BMC_SYN_SYN_BMC15_L18F_A0                    syn_bmc15                ;         // 0xC930_E43C
BMC_SYN_SYN_BMC16_L18F_A0                    syn_bmc16                ;         // 0xC930_E440
BMC_SYN_SYN_BMC17_L18F_A0                    syn_bmc17                ;         // 0xC930_E444
BMC_SYN_SYN_BMC18_L18F_A0                    syn_bmc18                ;         // 0xC930_E448
BMC_SYN_SYN_BMC19_L18F_A0                    syn_bmc19                ;         // 0xC930_E44C
BMC_SYN_SYN_BMC20_L18F_A0                    syn_bmc20                ;         // 0xC930_E450
BMC_SYN_SYN_BMC21_L18F_A0                    syn_bmc21                ;         // 0xC930_E454
BMC_SYN_SYN_BMC22_L18F_A0                    syn_bmc22                ;         // 0xC930_E458
BMC_SYN_SYN_BMC23_L18F_A0                    syn_bmc23                ;         // 0xC930_E45C
BMC_SYN_SYN_BMC24_L18F_A0                    syn_bmc24                ;         // 0xC930_E460
BMC_SYN_SYN_BMC25_L18F_A0                    syn_bmc25                ;         // 0xC930_E464
BMC_SYN_SYN_BMC26_L18F_A0                    syn_bmc26                ;         // 0xC930_E468
BMC_SYN_SYN_BMC27_L18F_A0                    syn_bmc27                ;         // 0xC930_E46C
BMC_SYN_SYN_BMC28_L18F_A0                    syn_bmc28                ;         // 0xC930_E470
BMC_SYN_SYN_BMC29_L18F_A0                    syn_bmc29                ;         // 0xC930_E474
BMC_SYN_SYN_BMC30_L18F_A0                    syn_bmc30                ;         // 0xC930_E478
BMC_SYN_SYN_BMC31_L18F_A0                    syn_bmc31                ;         // 0xC930_E47C
BMC_SYN_SYN_BMC32_L18F_A0                    syn_bmc32                ;         // 0xC930_E480
BMC_SYN_SYN_BMC33_L18F_A0                    syn_bmc33                ;         // 0xC930_E484
BMC_SYN_SYN_BMC34_L18F_A0                    syn_bmc34                ;         // 0xC930_E488
UINT32                                                 _rsvd_00[   1] ;         // 0xC930_E48C
BMC_SYN_SYN_BMC36_L18F_A0                    syn_bmc36                ;         // 0xC930_E490
BMC_SYN_SYN_BMC37_L18F_A0                    syn_bmc37                ;         // 0xC930_E494
BMC_SYN_SYN_BMC38_L18F_A0                    syn_bmc38                ;         // 0xC930_E498
BMC_SYN_SYN_BMC39_L18F_A0                    syn_bmc39                ;         // 0xC930_E49C
BMC_SYN_SYN_BMC40_L18F_A0                    syn_bmc40                ;         // 0xC930_E4A0
BMC_SYN_SYN_BMC41_L18F_A0                    syn_bmc41                ;         // 0xC930_E4A4
BMC_SYN_SYN_BMC42_L18F_A0                    syn_bmc42                ;         // 0xC930_E4A8
BMC_SYN_SYN_BMC43_L18F_A0                    syn_bmc43                ;         // 0xC930_E4AC
BMC_SYN_SYN_BMC44_L18F_A0                    syn_bmc44                ;         // 0xC930_E4B0
BMC_SYN_SYN_BMC48_L18F_A0                    syn_bmc48                ;         // 0xC930_E4B4
BMC_SYN_SYN_BMC4C_L18F_A0                    syn_bmc4c                ;         // 0xC930_E4B8
} BMC_SYN_REG_L18F_A0;
/* 46 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_BMC_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

