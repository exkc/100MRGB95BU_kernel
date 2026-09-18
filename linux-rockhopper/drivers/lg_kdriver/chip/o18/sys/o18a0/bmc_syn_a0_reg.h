#ifndef _BMC_SYN_A0_REG_H_
#define _BMC_SYN_A0_REG_H_

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
    0xC7FC_0000    bmc_ctr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_pdb          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_rxclkdrv_smv          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_rxclkdrv_outsel       :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}BMC_SYN_BMC_CTR01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0004    bmc_ctr02 ''
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
    reg_reserved              :  5,    //  30:26
                              :  1;    //  31:31 reserved
}BMC_SYN_BMC_CTR02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0008    bmc_ctr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_apll_cont             :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_apll_cpc              :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_apll_test             :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_apll_ci               :  3,    //  22:20
                              :  9;    //  31:23 reserved
}BMC_SYN_BMC_CTR03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_000C    bmc_ctr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_dco_fcw          : 22,    //  21: 0
                              : 10;    //  31:22 reserved
}BMC_SYN_BMC_CTR04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0010    bmc_ctr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auda_chop_freq        :  2,    //   1: 0
    reg_auda_chop_refp_en     :  1,    //      2
    reg_auda_chop_en          :  1,    //      3
    reg_auda_pdb_scf          :  1,    //      4
    reg_auda_pdb_ref          :  1,    //      5
    reg_auda_pdb_refgen       :  1,    //      6
    reg_auda_pdb_d2s          :  1,    //      7
    reg_auda_pdb_clk          :  1,    //      8
                              : 23;    //   31:9 reserved
}BMC_SYN_BMC_CTR05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0014    bmc_ctr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auda_vcont_refp       :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_auda_ic_scf           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auda_ic_ref           :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_auda_ic_refp          :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_auda_ic_d2s           :  2,    //  17:16
                              : 14;    //  31:18 reserved
}BMC_SYN_BMC_CTR06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0018    bmc_ctr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_ic_pga           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_auad_ic_quant         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auad_ic_int23         :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_auad_ic_int1          :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_auad_ic_pga_refr      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_auad_ic_pga_refl      :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_auad_ic_refpr         :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_auad_ic_refpl         :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BMC_SYN_BMC_CTR07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_001C    bmc_ctr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_refn_en          :  1,    //      0
    reg_auad_mclk_en          :  1,    //      1
    reg_auad_pga_ref_en_int   :  1,    //      2
    reg_auad_pga_ref_en_ext   :  1,    //      3
    reg_auad_vcont_refp       :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_auad_div_sel_sdm      :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_auad_div_sel          :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_auad_pga_gcont        :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_auad_chop_pga_ref_en  :  1,    //     20
    reg_auad_chop_refp_en     :  1,    //     21
    reg_auad_sdm_chop_en      :  1,    //     22
    reg_auad_pga_chop_en      :  1,    //     23
    reg_auad_refp_en          :  1,    //     24
    reg_auad_pdb_refp         :  1,    //     25
    reg_auad_adc_pdb          :  1,    //     26
    reg_auad_pga_pdb          :  1,    //     27
    reg_auad_pga_ref_pdb      :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_BMC_CTR08_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0020    bmc_ctr09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_reg_aud_reserved  :  5,    //   4: 0
    reg_aud_chop_bgr_en       :  1,    //      5
    reg_aud_chop_vcom_en      :  1,    //      6
    reg_aud_chop_vbuf_en      :  1,    //      7
    reg_aud_ccont             :  2,    //   9: 8
    reg_aud_ft_mode           :  1,    //     10
    reg_aud_cnt_rdiv          :  1,    //     11
    reg_aud_res               :  3,    //  14:12
    reg_aud_vcom_cont         :  2,    //  16:15
    reg_aud_sel_vref_out      :  1,    //     17
    reg_aud_pdb_bias          :  1,    //     18
    reg_aud_ic_bgr            :  2,    //  20:19
    reg_aud_ic_vcom           :  2,    //  22:21
    reg_aud_ic_vbuf           :  2,    //  24:23
    reg_aud_ic_iref           :  2,    //  26:25
                              :  5;    //  31:27 reserved
}BMC_SYN_BMC_CTR09_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0024    bmc_ctr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dig_32                :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_BMC_CTR10_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0028    bmc_ctr11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dig_31_0              : 32;    //  31: 0
}BMC_SYN_BMC_CTR11_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_002C    bmc_ctr12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_adcclk_test       :  1,    //      0
    invalid_reg_aad_adc_clk_inv: 1,    //      1
                              :  2,    //   3: 2 reserved
    invalid_reg_aad_adc_icon  :  3,    //   6: 4
    invalid_reg_aad_adc_pga_icon: 1,    //     7
    invalid_reg_aad_adc_decm  :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_aad_adc_pdb           :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_aad_adc_selsif        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_aad_adc_selref        :  3,    //  22:20
    reg_aad_adc_ibias_res     :  3,    //  25:23
    reg_aad_adc_rot           :  4,    //  29:26
    reg_aad_adc_rvs           :  1,    //     30
                              :  1;    //  31:31 reserved
}BMC_SYN_BMC_CTR12_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0030    bmc_ctr13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_reg_aad_pll_a_oen :  3,    //   2: 0
                              :  1,    //      3 reserved
    invalid_reg_aad_pll_a_odiv:  5,    //   8: 4
    invalid_reg_aad_pll_aon_odiv: 1,    //     9
    invalid_reg_aad_pll_lock_sw: 2,    //  11:10
    invalid_reg_aad_pll_div5sel: 1,    //     12
    invalid_reg_aad_pll_divrst:  1,    //     13
    invalid_reg_aad_pll_mc    :  6,    //  19:14
    invalid_reg_aad_pll_icp   :  4,    //  23:20
                              :  1,    //     24 reserved
    reg_aad_pll_ci            :  3,    //  27:25
    reg_aad_pll_pdb           :  1,    //     28
    reg_aad_pll_rstb          :  1,    //     29
    reg_aad_pll_test          :  2;    //  31:30
}BMC_SYN_BMC_CTR13_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0034    bmc_ctr14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_reg_aad_pll_lock  :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_BMC_CTR14_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0038    bmc_ctr15 ''
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
}BMC_SYN_BMC_CTR15_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_003C    bmc_ctr16 ''
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
}BMC_SYN_BMC_CTR16_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0040    bmc_ctr17 ''
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
}BMC_SYN_BMC_CTR17_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0044    bmc_ctr18 ''
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
}BMC_SYN_BMC_CTR18_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0048    bmc_ctr19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dmd_pll_lock          :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_BMC_CTR19_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_004C    bmc_ctr20 ''
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
}BMC_SYN_BMC_CTR20_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0050    bmc_ctr21 ''
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
}BMC_SYN_BMC_CTR21_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0054    bmc_ctr22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_reserved     :  8,    //   7: 0
    reg_videoafe_fblvl        :  2,    //   9: 8
    reg_videoafe_sid1lvl      :  2,    //  11:10
    reg_videoafe_sid2lvl      :  2,    //  13:12
    reg_videoafe_ibs_50u_sel  :  1,    //     14
    reg_videoafe_ref_sel      :  2,    //  16:15
    reg_videoafe_ire_sel      :  2,    //  18:17
    reg_videoafe_biaspdb      :  1,    //     19
                              :  4,    //  23:20 reserved
    reg_videoafe_sog_ssfil    :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_videoafe_sog_fil      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BMC_SYN_BMC_CTR22_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0058    bmc_ctr23 ''
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
    reg_videoafe_selmux       :  1,    //     23
    reg_videoafe_shield_on    :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_videoafe_ire_test     :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_BMC_CTR23_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_005C    bmc_ctr24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
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
}BMC_SYN_BMC_CTR24_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0064    bmc_ctr26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_cpll_pdb        :  1,    //      0
    reg_llpll_ref_vcon        :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_refpll_pdb            :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_llpll_icpcon          :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_videoafe_cvbs_cksel   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_videoafe_sog_deglitch :  4,    //  23:20
    reg_videoafe_sog_outmux   :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_videoafe_sog2dig_sel  :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_BMC_CTR26_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0068    bmc_ctr27 ''
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
}BMC_SYN_BMC_CTR27_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_006C    bmc_ctr28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_dco_control_monitor: 29,    //  28:0
    reg_videoafe_sc1_sid1     :  1,    //     29
    reg_videoafe_sc1_sid2     :  1,    //     30
    reg_videoafe_sc1_fb       :  1;    //     31
}BMC_SYN_BMC_CTR28_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0070    bmc_ctr29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_counter_monitor : 12,    //  11: 0
    reg_llpll_filter_status   :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_llpll_diff_monitor    : 12,    //  27:16
    reg_llpll_cvbs_lock       :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BMC_SYN_BMC_CTR29_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0074    bmc_ctr30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_g2_fine         :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_llpll_g3_p_fine       :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_llpll_g3_n_fine       :  5,    //  20:16
                              : 11;    //  31:21 reserved
}BMC_SYN_BMC_CTR30_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0078    bmc_ctr31 ''
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
}BMC_SYN_BMC_CTR31_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_007C    bmc_ctr32 ''
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
}BMC_SYN_BMC_CTR32_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0080    bmc_ctr33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_counter_max     : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    reg_llpll_dco_max         :  5,    //  20:16
                              : 11;    //  31:21 reserved
}BMC_SYN_BMC_CTR33_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0084    bmc_ctr34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_shift           : 10,    //   9: 0
    reg_reset_n               :  1,    //     10
                              :  1,    //     11 reserved
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
}BMC_SYN_BMC_CTR34_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0088    bmc_ctr35 ''
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
    invalid_reg_videoafe_cvbsafe_seldac: 1,    //  16
                              :  3,    //  19:17 reserved
    invalid_reg_videoafe_cvbsafe_selp: 2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_videoafe_cvbs_decm    :  2,    //  25:24
                              :  2,    //  27:26 reserved
    invalid_reg_videoafe_reset_n: 1,    //    28
                              :  3;    //  31:29 reserved
}BMC_SYN_BMC_CTR35_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_008C    bmc_ctr36 ''
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
}BMC_SYN_BMC_CTR36_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0090    bmc_ctr37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_cvbs_adcisel_ps: 2,    //  1: 0
                              :  2,    //   3: 2 reserved
    reg_videoafe_cvbs_adcisel_ref: 2,    //  5:4
                              :  2,    //   7: 6 reserved
    reg_videoafe_cvbs_adcisel_m: 2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_videoafe_cvbs_adcisel_f12: 2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_videoafe_cvbs_adcisel_f34: 2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_videoafe_cvbs_shield_on: 2,    //  21:20
    reg_videoafe_cvbs_dcatt   :  1,    //     22
    invalid_reg_videoafe_cvbs_ycm: 1,    //   23
    invalid_reg_videoafe_vbuf_sel: 1,    //   24
    reg_videoafe_cvbs_insel   :  2,    //  26:25
                              :  5;    //  31:27 reserved
}BMC_SYN_BMC_CTR37_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0094    ctr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gp12_0_mux_en             :  1,    //      0
    gp12_1_mux_en             :  1,    //      1
    gp12_2_mux_en             :  1,    //      2
    gp12_3_mux_en             :  1,    //      3
    gp12_4_mux_en             :  1,    //      4
    gp12_5_mux_en             :  1,    //      5
    gp12_6_mux_en             :  1,    //      6
    gp12_7_mux_en             :  1,    //      7
    gp4_0_mux_en              :  1,    //      8
    gp4_1_mux_en              :  1,    //      9
    gp4_2_mux_en              :  1,    //     10
    gp4_3_mux_en              :  1,    //     11
    gp4_4_mux_en              :  1,    //     12
    gp4_5_mux_en              :  1,    //     13
    gp4_6_mux_en              :  1,    //     14
    gp4_7_mux_en              :  1,    //     15
    gp5_5_mux_en              :  1,    //     16
    gp5_6_mux_en              :  1,    //     17
    gp5_7_mux_en              :  1,    //     18
    gp9_0_mux_en              :  1,    //     19
    gp9_1_mux_en              :  1,    //     20
    gp9_2_mux_en              :  1,    //     21
    gp9_3_mux_en              :  1,    //     22
    gp9_4_mux_en              :  1,    //     23
    gp9_5_mux_en              :  1,    //     24
    reg_i2c3_off              :  1,    //     25
    reg_i2c4_off              :  1,    //     26
    reg_i2c5_off              :  1,    //     27
    reg_spi0_off              :  1,    //     28
    reg_spi1_off              :  1,    //     29
                              :  2;    //  31:30 reserved
}BMC_SYN_CTR00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_0098    ctr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aad_mon_en4           :  1,    //      0
    reg_abb0_mon_en4          :  1,    //      1
    reg_abb1_mon_en4          :  1,    //      2
    reg_abb2_mon_en4          :  1,    //      3
    reg_aud_mon_en4           :  1,    //      4
    reg_cco_mon_en4           :  1,    //      5
    reg_cpu0_mon_en4          :  1,    //      6
    reg_cpu1_mon_en4          :  1,    //      7
    reg_cpu2_mon_en4          :  1,    //      8
    reg_cpu3_mon_en4          :  1,    //      9
    reg_cvi_mon_en4           :  1,    //     10
    reg_dbb0_mon_en4          :  1,    //     11
    reg_dbb1_mon_en4          :  1,    //     12
    reg_dbb2_mon_en4          :  1,    //     13
    reg_fmc_mon_en4           :  1,    //     14
    reg_fms_mon_en4           :  1,    //     15
    reg_gpu_mon_en4           :  1,    //     16
    reg_gsc_mon_en4           :  1,    //     17
    reg_hdmi20rx_mon_en4      :  1,    //     18
    reg_hdr_mon_en4           :  1,    //     19
    reg_imx_mon_en4           :  1,    //     20
    reg_led_mon_en4           :  1,    //     21
    reg_me0_mon_en4           :  1,    //     22
    reg_me1_mon_en4           :  1,    //     23
    reg_nd0_mon_en4           :  1,    //     24
    reg_nd1_mon_en4           :  1,    //     25
    reg_pmcu_mon_en4          :  1,    //     26
    reg_sre_mon_en4           :  1,    //     27
    reg_tcon_mon_en4          :  1,    //     28
    reg_te_mon_en4            :  1,    //     29
    reg_vdec0_mon_en4         :  1,    //     30
    reg_vdec1_mon_en4         :  1;    //     31
}BMC_SYN_CTR01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_009C    ctr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_reg_venc_mon_en4        :  1,    //      0
    i_reg_vsd_mon_en4         :  1,    //      1
    i_stpi0_out_ctrl_0        :  1,    //      2
    i_stpi0_out_ctrl_1        :  1,    //      3
    i_tp_dvd_out_ctrl_0       :  1,    //      4
    i_tp_dvd_out_ctrl_1       :  1,    //      5
                              : 10,    //  15: 6 reserved
    i_tpio_sel_ctrl           :  1,    //     16
    i_tpo_sel_ctrl0           :  1,    //     17
    i_tpo_sel_ctrl1           :  1,    //     18
                              : 13;    //  31:19 reserved
}BMC_SYN_CTR02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00A0    ctr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_gp11_6_mux_en           :  1,    //      0
    i_gp11_7_mux_en           :  1,    //      1
                              :  2,    //   3: 2 reserved
    jtag1_disable             :  1,    //      4
                              :  3,    //   7: 5 reserved
    i_pll_mon_en              :  1,    //      8
                              : 23;    //   31:9 reserved
}BMC_SYN_CTR03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00A4    ctr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_rxclkdrv_reg_pdb        :  1,    //      0
    i_rxclkdrv_reg_outsel     :  2,    //   2: 1
    i_rxclkdrv_reg_smv        :  1,    //      3
                              : 28;    //   31:4 reserved
}BMC_SYN_CTR04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00A8    ctr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_txclkdrv_ddr_reg_pdb    :  1,    //      0
    i_txclkdrv_ddr_reg_icon   :  3,    //   3: 1
    i_txclkdrv_ddr_reg_ckin_sel: 1,    //      4
                              : 27;    //   31:5 reserved
}BMC_SYN_CTR05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00AC    ctr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_txclkdrv_dmd_reg_pdb    :  1,    //      0
    i_txclkdrv_dmd_reg_icon   :  3,    //   3: 1
    i_txclkdrv_dmd_reg_ckin_sel: 1,    //      4
                              : 27;    //   31:5 reserved
}BMC_SYN_CTR06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00B0    ctr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fan_ctrl_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_CTR07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00B4    ctr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr08                     : 32;    //  31: 0
}BMC_SYN_CTR08_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00B8    ctr09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr09                     : 32;    //  31: 0
}BMC_SYN_CTR09_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00BC    ctr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_scl3_ds               :  1,    //      0
    pad_scl3_pu               :  1,    //      1
    pad_sda3_ds               :  1,    //      2
    pad_sda3_pu               :  1,    //      3
    pad_scl4_ds               :  1,    //      4
    pad_scl4_pu               :  1,    //      5
    pad_sda4_ds               :  1,    //      6
    pad_sda4_pu               :  1,    //      7
    pad_scl5_ds               :  1,    //      8
    pad_scl5_pu               :  1,    //      9
    pad_sda5_ds               :  1,    //     10
    pad_sda5_pu               :  1,    //     11
    pad_spi_cs0_ren           :  1,    //     12
    pad_spi_sclk0_ren         :  1,    //     13
    pad_spi_di0_ren           :  1,    //     14
    pad_spi_do0_ren           :  1,    //     15
    pad_spi_cs1_ren           :  1,    //     16
    pad_spi_sclk1_ren         :  1,    //     17
    pad_spi_di1_ren           :  1,    //     18
    pad_spi_do1_ren           :  1,    //     19
    pad_diseqc_cmd_ren        :  1,    //     20
    pad_diseqci_ren           :  1,    //     21
    pad_diseqc_ren            :  1,    //     22
    pad_ifagc_ren             :  1,    //     23
    pad_ifagc_s_ren           :  1,    //     24
    pad_fefctrl_ren           :  1,    //     25
                              :  1,    //     26 reserved
    pad_stpi0_data0_ren       :  1,    //     27
    pad_stpi0_data1_ren       :  1,    //     28
    pad_stpi0_data2_ren       :  1,    //     29
    pad_stpi0_data3_ren       :  1,    //     30
    pad_stpi0_data4_ren       :  1;    //     31
}BMC_SYN_CTR10_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00C0    ctr11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_stpi0_data5_ren       :  1,    //      0
    pad_stpi0_data6_ren       :  1,    //      1
    pad_stpi0_data7_ren       :  1,    //      2
    pad_stpi0_sop_ren         :  1,    //      3
    pad_stpi0_val_ren         :  1,    //      4
                              :  1,    //      5 reserved
    pad_tp_dvb_data0_ren      :  1,    //      6
    pad_tp_dvb_data1_ren      :  1,    //      7
    pad_tp_dvb_data2_ren      :  1,    //      8
    pad_tp_dvb_data3_ren      :  1,    //      9
    pad_tp_dvb_data4_ren      :  1,    //     10
    pad_tp_dvb_data5_ren      :  1,    //     11
    pad_tp_dvb_data6_ren      :  1,    //     12
    i_reg_ext_i2c_en          :  1,    //     13
    pad_tp_dvb_sop_ren        :  1,    //     14
    pad_tp_dvb_val_ren        :  1,    //     15
    pad_xin_main_ds0          :  1,    //     16
    pad_xin_main_ds1          :  1,    //     17
    pad_xin_main_ds2          :  1,    //     18
    pad_edid_isol_ren         :  1,    //     19
    pad_ephy_isol_ren         :  1,    //     20
    pad_ephy_intr_ren         :  1,    //     21
    pad_tpi_clk_ds            :  1,    //     22
    pad_tpi_clk_pu            :  1,    //     23
    pad_tpi_clk_pd            :  1,    //     24
    pad_tpi_data0_ds          :  1,    //     25
    pad_tpi_data0_pu          :  1,    //     26
    pad_tpi_data0_pd          :  1,    //     27
    pad_tpi_data1_ds          :  1,    //     28
    pad_tpi_data1_pu          :  1,    //     29
    pad_tpi_data1_pd          :  1,    //     30
    pad_tpi_data2_ds          :  1;    //     31
}BMC_SYN_CTR11_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00C4    ctr12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_tpi_data2_pu          :  1,    //      0
    pad_tpi_data2_pd          :  1,    //      1
    pad_tpi_data3_ds          :  1,    //      2
    pad_tpi_data3_pu          :  1,    //      3
    pad_tpi_data3_pd          :  1,    //      4
    pad_tpi_data4_ds          :  1,    //      5
    pad_tpi_data4_pu          :  1,    //      6
    pad_tpi_data4_pd          :  1,    //      7
    pad_tpi_data5_ds          :  1,    //      8
    pad_tpi_data5_pu          :  1,    //      9
    pad_tpi_data5_pd          :  1,    //     10
    pad_tpi_data6_ds          :  1,    //     11
    pad_tpi_data6_pu          :  1,    //     12
    pad_tpi_data6_pd          :  1,    //     13
    pad_tpi_data7_ds          :  1,    //     14
    pad_tpi_data7_pu          :  1,    //     15
    pad_tpi_data7_pd          :  1,    //     16
    pad_tpi_sop_ds            :  1,    //     17
    pad_tpi_sop_pu            :  1,    //     18
    pad_tpi_sop_pd            :  1,    //     19
    pad_tpi_val_ds            :  1,    //     20
    pad_tpi_val_pu            :  1,    //     21
    pad_tpi_val_pd            :  1,    //     22
    pad_tpio_clk_ds           :  1,    //     23
    pad_tpio_clk_pu           :  1,    //     24
    pad_tpio_clk_pd           :  1,    //     25
    pad_tpio_data0_ds         :  1,    //     26
    pad_tpio_data0_pu         :  1,    //     27
    pad_tpio_data0_pd         :  1,    //     28
    pad_tpio_data1_ds         :  1,    //     29
    pad_tpio_data1_pu         :  1,    //     30
    pad_tpio_data1_pd         :  1;    //     31
}BMC_SYN_CTR12_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00C8    ctr13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_tpio_data2_ds         :  1,    //      0
    pad_tpio_data2_pu         :  1,    //      1
    pad_tpio_data2_pd         :  1,    //      2
    pad_tpio_data3_ds         :  1,    //      3
    pad_tpio_data3_pu         :  1,    //      4
    pad_tpio_data3_pd         :  1,    //      5
    pad_tpio_data4_ds         :  1,    //      6
    pad_tpio_data4_pu         :  1,    //      7
    pad_tpio_data4_pd         :  1,    //      8
    pad_tpio_data5_ds         :  1,    //      9
    pad_tpio_data5_pu         :  1,    //     10
    pad_tpio_data5_pd         :  1,    //     11
    pad_tpio_data6_ds         :  1,    //     12
    pad_tpio_data6_pu         :  1,    //     13
    pad_tpio_data6_pd         :  1,    //     14
    pad_tpio_data7_ds         :  1,    //     15
    pad_tpio_data7_pu         :  1,    //     16
    pad_tpio_data7_pd         :  1,    //     17
    pad_tpio_sop_ds           :  1,    //     18
    pad_tpio_sop_pu           :  1,    //     19
    pad_tpio_sop_pd           :  1,    //     20
    pad_tpio_val_ds           :  1,    //     21
    pad_tpio_val_pu           :  1,    //     22
    pad_tpio_val_pd           :  1,    //     23
    pad_hub_port_over0_ds     :  1,    //     24
    pad_hub_port_over0_pu     :  1,    //     25
    pad_hub_port_over0_pd     :  1,    //     26
    pad_hub_vbus_ctrl0_ds     :  1,    //     27
    pad_hub_vbus_ctrl0_pu     :  1,    //     28
    pad_hub_vbus_ctrl0_pd     :  1,    //     29
                              :  2;    //  31:30 reserved
}BMC_SYN_CTR13_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00CC    ctr14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_earc_ds               :  1,    //      0
    pad_earc_pu               :  1,    //      1
    pad_earc_pd               :  1,    //      2
    pad_earc_clk_ds           :  1,    //      3
    pad_earc_clk_pu           :  1,    //      4
    pad_earc_clk_pd           :  1,    //      5
    stpi0_clk_ds              :  1,    //      6
    stpi0_clk_pu              :  1,    //      7
    stpi0_clk_pd              :  1,    //      8
    tp_dvb_clk_ds             :  1,    //      9
    tp_dvb_clk_pu             :  1,    //     10
    tp_dvb_clk_pd             :  1,    //     11
    tp_dvb_data7_ds           :  1,    //     12
    tp_dvb_data7_pu           :  1,    //     13
    tp_dvb_data7_pd           :  1,    //     14
                              : 17;    //  31:15 reserved
}BMC_SYN_CTR14_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00D0    ctr15_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr15_ro                  : 32;    //  31: 0
}BMC_SYN_CTR15_RO_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00D4    ctr16_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr16_ro                  : 32;    //  31: 0
}BMC_SYN_CTR16_RO_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00D8    ctr17_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr17_ro                  : 32;    //  31: 0
}BMC_SYN_CTR17_RO_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00DC    ctr18_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr18_ro                  : 32;    //  31: 0
}BMC_SYN_CTR18_RO_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_00E0    ctr19_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr19_ro                  : 32;    //  31: 0
}BMC_SYN_CTR19_RO_O18_A0;

/*-----------------------------------------------------------------------------------------
    bmc_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BMC_SYN_BMC_CTR01_O18_A0                     bmc_ctr01                ;         // 0xC7FC_0000
BMC_SYN_BMC_CTR02_O18_A0                     bmc_ctr02                ;         // 0xC7FC_0004
BMC_SYN_BMC_CTR03_O18_A0                     bmc_ctr03                ;         // 0xC7FC_0008
BMC_SYN_BMC_CTR04_O18_A0                     bmc_ctr04                ;         // 0xC7FC_000C
BMC_SYN_BMC_CTR05_O18_A0                     bmc_ctr05                ;         // 0xC7FC_0010
BMC_SYN_BMC_CTR06_O18_A0                     bmc_ctr06                ;         // 0xC7FC_0014
BMC_SYN_BMC_CTR07_O18_A0                     bmc_ctr07                ;         // 0xC7FC_0018
BMC_SYN_BMC_CTR08_O18_A0                     bmc_ctr08                ;         // 0xC7FC_001C
BMC_SYN_BMC_CTR09_O18_A0                     bmc_ctr09                ;         // 0xC7FC_0020
BMC_SYN_BMC_CTR10_O18_A0                     bmc_ctr10                ;         // 0xC7FC_0024
BMC_SYN_BMC_CTR11_O18_A0                     bmc_ctr11                ;         // 0xC7FC_0028
BMC_SYN_BMC_CTR12_O18_A0                     bmc_ctr12                ;         // 0xC7FC_002C
BMC_SYN_BMC_CTR13_O18_A0                     bmc_ctr13                ;         // 0xC7FC_0030
BMC_SYN_BMC_CTR14_O18_A0                     bmc_ctr14                ;         // 0xC7FC_0034
BMC_SYN_BMC_CTR15_O18_A0                     bmc_ctr15                ;         // 0xC7FC_0038
BMC_SYN_BMC_CTR16_O18_A0                     bmc_ctr16                ;         // 0xC7FC_003C
BMC_SYN_BMC_CTR17_O18_A0                     bmc_ctr17                ;         // 0xC7FC_0040
BMC_SYN_BMC_CTR18_O18_A0                     bmc_ctr18                ;         // 0xC7FC_0044
BMC_SYN_BMC_CTR19_O18_A0                     bmc_ctr19                ;         // 0xC7FC_0048
BMC_SYN_BMC_CTR20_O18_A0                     bmc_ctr20                ;         // 0xC7FC_004C
BMC_SYN_BMC_CTR21_O18_A0                     bmc_ctr21                ;         // 0xC7FC_0050
BMC_SYN_BMC_CTR22_O18_A0                     bmc_ctr22                ;         // 0xC7FC_0054
BMC_SYN_BMC_CTR23_O18_A0                     bmc_ctr23                ;         // 0xC7FC_0058
BMC_SYN_BMC_CTR24_O18_A0                     bmc_ctr24                ;         // 0xC7FC_005C
UINT32                                                 _rsvd_00[   1] ;         // 0xC7FC_0060
BMC_SYN_BMC_CTR26_O18_A0                     bmc_ctr26                ;         // 0xC7FC_0064
BMC_SYN_BMC_CTR27_O18_A0                     bmc_ctr27                ;         // 0xC7FC_0068
BMC_SYN_BMC_CTR28_O18_A0                     bmc_ctr28                ;         // 0xC7FC_006C
BMC_SYN_BMC_CTR29_O18_A0                     bmc_ctr29                ;         // 0xC7FC_0070
BMC_SYN_BMC_CTR30_O18_A0                     bmc_ctr30                ;         // 0xC7FC_0074
BMC_SYN_BMC_CTR31_O18_A0                     bmc_ctr31                ;         // 0xC7FC_0078
BMC_SYN_BMC_CTR32_O18_A0                     bmc_ctr32                ;         // 0xC7FC_007C
BMC_SYN_BMC_CTR33_O18_A0                     bmc_ctr33                ;         // 0xC7FC_0080
BMC_SYN_BMC_CTR34_O18_A0                     bmc_ctr34                ;         // 0xC7FC_0084
BMC_SYN_BMC_CTR35_O18_A0                     bmc_ctr35                ;         // 0xC7FC_0088
BMC_SYN_BMC_CTR36_O18_A0                     bmc_ctr36                ;         // 0xC7FC_008C
BMC_SYN_BMC_CTR37_O18_A0                     bmc_ctr37                ;         // 0xC7FC_0090
BMC_SYN_CTR00_O18_A0                         ctr00                    ;         // 0xC7FC_0094
BMC_SYN_CTR01_O18_A0                         ctr01                    ;         // 0xC7FC_0098
BMC_SYN_CTR02_O18_A0                         ctr02                    ;         // 0xC7FC_009C
BMC_SYN_CTR03_O18_A0                         ctr03                    ;         // 0xC7FC_00A0
BMC_SYN_CTR04_O18_A0                         ctr04                    ;         // 0xC7FC_00A4
BMC_SYN_CTR05_O18_A0                         ctr05                    ;         // 0xC7FC_00A8
BMC_SYN_CTR06_O18_A0                         ctr06                    ;         // 0xC7FC_00AC
BMC_SYN_CTR07_O18_A0                         ctr07                    ;         // 0xC7FC_00B0
BMC_SYN_CTR08_O18_A0                         ctr08                    ;         // 0xC7FC_00B4
BMC_SYN_CTR09_O18_A0                         ctr09                    ;         // 0xC7FC_00B8
BMC_SYN_CTR10_O18_A0                         ctr10                    ;         // 0xC7FC_00BC
BMC_SYN_CTR11_O18_A0                         ctr11                    ;         // 0xC7FC_00C0
BMC_SYN_CTR12_O18_A0                         ctr12                    ;         // 0xC7FC_00C4
BMC_SYN_CTR13_O18_A0                         ctr13                    ;         // 0xC7FC_00C8
BMC_SYN_CTR14_O18_A0                         ctr14                    ;         // 0xC7FC_00CC
BMC_SYN_CTR15_RO_O18_A0                      ctr15_ro                 ;         // 0xC7FC_00D0
BMC_SYN_CTR16_RO_O18_A0                      ctr16_ro                 ;         // 0xC7FC_00D4
BMC_SYN_CTR17_RO_O18_A0                      ctr17_ro                 ;         // 0xC7FC_00D8
BMC_SYN_CTR18_RO_O18_A0                      ctr18_ro                 ;         // 0xC7FC_00DC
BMC_SYN_CTR19_RO_O18_A0                      ctr19_ro                 ;         // 0xC7FC_00E0
} BMC_SYN_REG_O18_A0;
/* 56 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BMC_SYN_A0_REG_H_ */

/* from 'O18_CTOP_Register_Manual_For_SW_01.xlsm'  2017.6.8  KST by LGSiCRDV V2.1B*/

