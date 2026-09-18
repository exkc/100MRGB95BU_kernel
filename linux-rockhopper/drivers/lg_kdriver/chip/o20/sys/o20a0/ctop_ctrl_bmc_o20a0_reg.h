#ifndef _CTOP_CTRL_BMC_O20A0_REG_H_
#define _CTOP_CTRL_BMC_O20A0_REG_H_

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
    0xC34E_0800    acodec0 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC34E_0804    acodec1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_pga_ref_pdb      :  1,    //      0
    reg_aud_ccont             :  2,    //   2: 1
    reg_auad_refp_pdb         :  1,    //      3
    reg_auda_ic_scfr          :  2,    //   5: 4
    reg_auad_ic_ref           :  2,    //   7: 6
    reg_auda_pdb_clk          :  1,    //      8
    reg_auda_chop_en_ref      :  1,    //      9
    reg_auad_ic_int2          :  2,    //  11:10
    reg_auda_chop_freq_scf    :  2,    //  13:12
    reg_auad_ic_refp          :  2,    //  15:14
    reg_auda_chop_en_refp     :  1,    //     16
    reg_auad_ic_quant         :  2,    //  18:17
    reg_auda_vcont_refp       :  3,    //  21:19
    reg_auda_chop_en          :  1,    //     22
    reg_auda_chop_en_scf      :  1,    //     23
    reg_auad_ic_pga           :  2,    //  25:24
    reg_auda_pdb_dac          :  1,    //     26
    reg_auda_chop_en_d2s      :  1,    //     27
    reg_auad_ic_int1          :  2,    //  29:28
    reg_auda_chop_freq_d2s    :  2;    //  31:30
}CTOP_CTRL_BMC_ACODEC1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0808    acodec2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_d_inv_enb        :  1,    //      0
    reg_auad_mclk_en          :  1,    //      1
    reg_auad_adc_pdb          :  1,    //      2
    reg_aud_ic_vcom           :  2,    //   4: 3
    reg_auad_ch1_sel          :  1,    //      5
    reg_auda_ic_refpr         :  2,    //   7: 6
    reg_auda_ic_d2sl          :  2,    //   9: 8
    reg_auad_refp_en          :  1,    //     10
    reg_auad_sel_pga          :  2,    //  12:11
    reg_aud_ft_mode           :  1,    //     13
    reg_auad_en_int_pga       :  1,    //     14
    reg_auda_ic_scfl          :  2,    //  16:15
    reg_auad_chen_amp         :  1,    //     17
    reg_auad_en_ext           :  1,    //     18
    reg_auad_pga_chop_en      :  1,    //     19
    reg_aud_res               :  3,    //  22:20
    reg_auad_chen_cmfb        :  1,    //     23
    reg_auad_ch2_sel          :  1,    //     24
    reg_aud_ic_vbuf           :  2,    //  26:25
    reg_auda_ic_d2sr          :  2,    //  28:27
    reg_auad_refp_ch_en       :  1,    //     29
    reg_auad_sel_refp         :  2;    //  31:30
}CTOP_CTRL_BMC_ACODEC2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_080C    acodec3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_auad_ch_out_enb       :  1,    //      1
    reg_aud_pdb_bias          :  1,    //      2
    reg_auda_ic_refl          :  2,    //   4: 3
    reg_auad_refn_en          :  1,    //      5
    reg_auad_div_sel_sdm      :  3,    //   8: 6
    reg_auad_pga_pdb          :  1,    //      9
    reg_aud_ic_bgr            :  2,    //  11:10
    reg_auad_vcont_refp       :  3,    //  14:12
    reg_auda_ic_refpl         :  2,    //  16:15
    reg_auad_ref_chop_en      :  1,    //     17
    reg_auad_pga_gcont        :  3,    //  20:18
    reg_reserve_in2           :  5,    //  25:21
    reg_aud_vcom_cont         :  2,    //  27:26
    reg_aud_cnt_rdiv          :  1,    //     28
    reg_auad_en_ext_pga       :  1,    //     29
    reg_auda_ic_refr          :  2;    //  31:30
}CTOP_CTRL_BMC_ACODEC3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0810    acodec4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_auad_en_int           :  1,    //     24
    reg_auad_sdm_chop_en      :  1,    //     25
    reg_aud_sel_vref_out      :  1,    //     26
    reg_reserve_in1           :  5;    //  31:27
}CTOP_CTRL_BMC_ACODEC4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0814    admd_mip5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_admd_t_sel_clkinv     :  1,    //      5
    reg_admd_i_pdb            :  1,    //      6
    reg_admd_a_sel_sif        :  1,    //      7
    reg_admd_a_adc_icon       :  3,    //  10: 8
    reg_admd_apll_icp         :  4,    //  14:11
    reg_admd_a_gc             :  5,    //  19:15
    reg_admd_apll_autofreq    :  1,    //     20
    reg_admd_a_adc_refsel     :  2,    //  22:21
    reg_admd_apll_icp_g       :  1,    //     23
    reg_admd_a_pdb            :  1,    //     24
    reg_admd_apll_outsel      :  1,    //     25
    reg_admd_a_bias_pdb       :  1,    //     26
    reg_admd_apll_lpf_on      :  1,    //     27
    reg_admd_a_sel_clkinv     :  1,    //     28
    reg_admd_apll_frequp      :  1,    //     29
    reg_admd_a_decm           :  2;    //  31:30
}CTOP_CTRL_BMC_ADMD_MIP5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0818    admd_mip6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_apll_insel       :  1,    //      1
    reg_admd_apll_cken        :  3,    //   4: 2
    reg_admd_dpll_wakebypass  :  1,    //      5
    reg_admd_dpll_lpf_on      :  1,    //      6
    reg_admd_t_pdb            :  1,    //      7
    reg_admd_i_decm           :  2,    //   9: 8
    reg_admd_apll_lockf       :  1,    //     10
    reg_admd_apll_wakebypass  :  1,    //     11
    reg_admd_dpll_od_en       :  1,    //     12
    reg_admd_dpll_frequp      :  1,    //     13
    reg_admd_q_pdb            :  1,    //     14
    reg_admd_adc_icon         :  3,    //  17:15
    reg_admd_dpll_lockc       :  1,    //     18
    reg_admd_apll_od_en       :  1,    //     19
    reg_admd_dpll_odpre       :  6,    //  25:20
    reg_admd_dpll_m           :  6;    //  31:26
}CTOP_CTRL_BMC_ADMD_MIP6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_081C    admd_mip7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_dpll_autofreq    :  1,    //      1
    reg_admd_i_sel_clkinv     :  1,    //      2
    reg_admd_apll_odpost      :  6,    //   8: 3
    reg_admd_apll_divint      :  9,    //  17: 9
    reg_admd_dpll_syncon      :  1,    //     18
    reg_admd_dpll_icp_g       :  1,    //     19
    reg_admd_t_decm           :  2,    //  21:20
    reg_admd_bias_pdb         :  1,    //     22
    reg_admd_apll_lockc       :  1,    //     23
    reg_admd_dpll_insel       :  1,    //     24
    reg_admd_apll_syncon      :  1,    //     25
    reg_admd_dpll_cken        :  3,    //  28:26
    reg_admd_dpll_outsel      :  1,    //     29
    reg_admd_q_decm           :  2;    //  31:30
}CTOP_CTRL_BMC_ADMD_MIP7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0820    admd_mip8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_apll_m           :  6,    //   6: 1
    reg_admd_dpll_pdb         :  1,    //      7
    reg_admd_dpll_icp         :  4,    //  11: 8
    reg_admd_q_sel_clkinv     :  1,    //     12
    reg_admd_adc_refsel       :  2,    //  14:13
    reg_admd_dpll_lockf       :  1,    //     15
    reg_admd_apll_pdb         :  1,    //     16
    reg_admd_dpll_odpost      :  6,    //  22:17
    reg_admd_dpll_divint      :  9;    //  31:23
}CTOP_CTRL_BMC_ADMD_MIP8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0824    admd_mip9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 26,    //  25: 0 reserved
    reg_admd_apll_odpre       :  6;    //  31:26
}CTOP_CTRL_BMC_ADMD_MIP9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0828    videoafe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_reset_n               :  1,    //      0
    reg_llpll_lpf_clk_div     :  2,    //   2: 1
    reg_videoafe_cvbs_pdbm    :  1,    //      3
    reg_videoafe_cvbs_decm    :  2,    //   5: 4
    reg_llpll_sf_mode_control :  4,    //   9: 6
    reg_videoafe_cvbs_dcsel   :  2,    //  11:10
    reg_videoafe_adcisel_m    :  2,    //  13:12
    reg_videoafe_rpdb         :  1,    //     14
    reg_videoafe_adc_fil      :  3,    //  17:15
    reg_videoafe_cvbs_adcisel_ps: 2,    //  19:18
    reg_videoafe_adcisel_f3   :  2,    //  21:20
    reg_llpll_shift           : 10;    //  31:22
}CTOP_CTRL_BMC_VIDEOAFE10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_082C    videoafe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_ref_sel      :  2,    //   1: 0
    reg_videoafe_sog_soui     :  2,    //   3: 2
    reg_videoafe_clpcur       :  3,    //   6: 4
    reg_videoafe_cvbs_iclp2   :  2,    //   8: 7
    reg_videoafe_sog_hys      :  2,    //  10: 9
    reg_videoafe_cvbs_clp     :  1,    //     11
    reg_videoafe_sel_invdatack:  1,    //     12
    reg_llpll_dco_max         :  5,    //  17:13
    reg_videoafe_cvbs_bw      :  1,    //     18
    reg_videoafe_sog_bw       :  2,    //  20:19
    reg_videoafe_ire_test     :  1,    //     21
    reg_videoafe_icon_buf     :  3,    //  24:22
    reg_refpll_pdb            :  1,    //     25
    reg_videoafe_adcisel_ps   :  2,    //  27:26
    reg_llpll_nsc             :  4;    //  31:28
}CTOP_CTRL_BMC_VIDEOAFE11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0830    videoafe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_videoafe_cvbs_adcisel_f3: 2,    //  2: 1
    reg_videoafe_ire_sel      :  2,    //   4: 3
    reg_videoafe_gvclpsel     :  1,    //      5
    reg_videoafe_biaspdb      :  1,    //      6
    reg_videoafe_cvbs_adcisel_m: 2,    //   8: 7
    reg_llpll_coarse_scale    :  4,    //  12: 9
    reg_videoafe_cvbs_dcatt   :  1,    //     13
    reg_videoafe_sog_deglitch :  4,    //  17:14
    reg_llpll_diff_monitor    : 12,    //  29:18
    reg_videoafe_adcisel_ref  :  2;    //  31:30
}CTOP_CTRL_BMC_VIDEOAFE12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0834    videoafe13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_div10_sel       :  1,    //      0
    reg_videoafe_ibs_50u_sel  :  1,    //      1
    reg_videoafe_sel_fs       :  1,    //      2
    reg_videoafe_vclp_en      :  1,    //      3
    reg_llpll_ref_lock_ctl    :  2,    //   5: 4
    reg_videoafe_sog_fil      :  3,    //   8: 6
    reg_llpll_g3_p_nom        :  5,    //  13: 9
    reg_llpll_disable_fm      :  1,    //     14
    reg_llpll_cvbs_lock       :  2,    //  16:15
    reg_llpll_ref_vcon        :  1,    //     17
    reg_llpll_g2_fine         :  5,    //  22:18
    reg_videoafe_cvbs_gc      :  3,    //  25:23
    reg_videoafe_sog2dig_sel  :  1,    //     26
    reg_llpll_npc             :  5;    //  31:27
}CTOP_CTRL_BMC_VIDEOAFE13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0838    videoafe14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_reserved     :  8,    //   7: 0
    reg_videoafe_cvbs_adcisel_ref: 2,    //  9:8
    reg_llpll_g1_fine         :  5,    //  14:10
    reg_videoafe_bvclpsel     :  1,    //     15
    reg_videoafe_sel_datack   :  1,    //     16
    reg_videoafe_sog_enwin    :  1,    //     17
    reg_llpll_g3_n_fine       :  5,    //  22:18
    reg_videoafe_rvclpsel     :  1,    //     23
    reg_llpll_icpcon          :  5,    //  28:24
    reg_videoafe_cvbs_shield_on: 2,    //  30:29
    reg_llpll_div12_sel       :  1;    //     31
}CTOP_CTRL_BMC_VIDEOAFE14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_083C    videoafe15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_videoafe_soglvl       :  5,    //   7: 3
    reg_llpll_lpfr_dis        :  1,    //      8
    reg_videoafe_cvbs_isel    :  3,    //  11: 9
    reg_llpll_g1_nom          :  5,    //  16:12
    reg_llpll_g3_p_fine       :  5,    //  21:17
    reg_videoafe_icon_adc     :  3,    //  24:22
    reg_llpll_cpll_pdb        :  1,    //     25
    reg_videoafe_sog_ssfil    :  2,    //  27:26
    reg_videoafe_shield_on    :  1,    //     28
    reg_videoafe_cvbs_cksel   :  1,    //     29
    reg_videoafe_gpdb         :  1,    //     30
    reg_videoafe_sog_outmux   :  1;    //     31
}CTOP_CTRL_BMC_VIDEOAFE15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0840    videoafe16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 11,    //  10: 0 reserved
    reg_videoafe_sel_ck       :  2,    //  12:11
    reg_videoafe_sog_sinki    :  3,    //  15:13
    reg_videoafe_cvbs_refsel  :  2,    //  17:16
    reg_llpll_filter_status   :  2,    //  19:18
    reg_llpll_counter_max     : 12;    //  31:20
}CTOP_CTRL_BMC_VIDEOAFE16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0844    videoafe17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_videoafe_cvbs_ibuf    :  3,    //   5: 3
    reg_videoafe_cvbs_lpf     :  1,    //      6
    reg_videoafe_cvbs_iclp    :  2,    //   8: 7
    reg_llpll_div_max         :  6,    //  14: 9
    reg_videoafe_adcisel_f12  :  2,    //  16:15
    reg_llpll_lpf_clk_sel     :  1,    //     17
    reg_llpll_in_sel          :  1,    //     18
    reg_videoafe_cvbs_pdb     :  1,    //     19
    reg_llpll_counter_monitor : 12;    //  31:20
}CTOP_CTRL_BMC_VIDEOAFE17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0848    videoafe18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 19,    //  18: 0 reserved
    reg_videoafe_cvbs_insel   :  1,    //     19
    reg_llpll_dco_min         :  5,    //  24:20
    reg_llpll_dco_test_mode   :  1,    //     25
    reg_videoafe_bpdb         :  1,    //     26
    reg_llpll_g2_nom          :  5;    //  31:27
}CTOP_CTRL_BMC_VIDEOAFE18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_084C    videoafe19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_videoafe_cvbs_adcisel_f12: 2,    //  2:1
    reg_llpll_dco_control_monitor: 29;    //  31:3
}CTOP_CTRL_BMC_VIDEOAFE19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0850    videoafe20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 23,    //  22: 0 reserved
    reg_llpll_disable_sfm     :  1,    //     23
    reg_llpll_g3_n_nom        :  5,    //  28:24
    reg_videoafe_ire_selrefck :  1,    //     29
    reg_videoafe_decm         :  2;    //  31:30
}CTOP_CTRL_BMC_VIDEOAFE20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0854    aioplls21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aioplls_aad_lock      :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_aioplls_aad_out_div   :  2,    //  12:11
    reg_aioplls_aad_pdb       :  1,    //     13
    reg_aioplls_aad_fout2_en  :  1,    //     14
    reg_aioplls_aad_fb_m      :  8,    //  22:15
    reg_aioplls_aad_cih       :  4,    //  26:23
    reg_aioplls_aad_fout1_en  :  1,    //     27
    reg_aioplls_aad_cih2      :  4;    //  31:28
}CTOP_CTRL_BMC_AIOPLLS21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0858    rxclkdrv_md22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 28,    //  27: 0 reserved
    reg_rxclkdrv_md_smv       :  1,    //     28
    reg_rxclkdrv_md_cksel     :  2,    //  30:29
    reg_rxclkdrv_md_pdb       :  1;    //     31
}CTOP_CTRL_BMC_RXCLKDRV_MD22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_085C    frpll23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_earc_divider_update: 1,    //    0
    reg_frpll_earc_in_divsel  :  1,    //      1
    reg_frpll_earc_lpf_on     :  1,    //      2
    reg_frpll_earc_fout2_en   :  1,    //      3
    reg_frpll_earc_wakeup_bypass: 1,    //     4
    reg_frpll_earc_divint     :  9,    //  13: 5
    reg_frpll_earc_pdb        :  1,    //     14
    reg_frpll_earc_dsmon      :  1,    //     15
    reg_frpll_earc_auto_freq  :  1,    //     16
    reg_frpll_earc_dsm_limit  :  1,    //     17
    reg_frpll_earc_fin_sel    :  1,    //     18
    reg_frpll_earc_icp        :  4,    //  22:19
    reg_frpll_earc_out_div    :  9;    //  31:23
}CTOP_CTRL_BMC_FRPLL23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0860    frpll24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_earc_fout_en    :  1,    //      0
    reg_frpll_earc_syncon     :  1,    //      1
    reg_frpll_earc_m          :  6,    //   7: 2
    reg_frpll_earc_fcw        : 24;    //  31: 8
}CTOP_CTRL_BMC_FRPLL24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0864    frpll25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_earc_lock       :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_frpll_earc_frequp     :  1,    //     23
    reg_frpll_earc_a          :  6,    //  29:24
    reg_frpll_earc_in_divrstb :  1,    //     30
    reg_frpll_earc_icp_g      :  1;    //     31
}CTOP_CTRL_BMC_FRPLL25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0868    frpll26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_aud_divider_update: 1,    //     0
    reg_frpll_aud_in_divsel   :  1,    //      1
    reg_frpll_aud_lpf_on      :  1,    //      2
    reg_frpll_aud_fout2_en    :  1,    //      3
    reg_frpll_aud_wakeup_bypass: 1,    //      4
    reg_frpll_aud_divint      :  9,    //  13: 5
    reg_frpll_aud_pdb         :  1,    //     14
    reg_frpll_aud_dsmon       :  1,    //     15
    reg_frpll_aud_auto_freq   :  1,    //     16
    reg_frpll_aud_dsm_limit   :  1,    //     17
    reg_frpll_aud_fin_sel     :  1,    //     18
    reg_frpll_aud_icp         :  4,    //  22:19
    reg_frpll_aud_out_div     :  9;    //  31:23
}CTOP_CTRL_BMC_FRPLL26_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_086C    frpll27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_aud_fout_en     :  1,    //      0
    reg_frpll_aud_syncon      :  1,    //      1
    reg_frpll_aud_m           :  6,    //   7: 2
    reg_frpll_aud_fcw         : 24;    //  31: 8
}CTOP_CTRL_BMC_FRPLL27_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0870    frpll28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_aud_lock        :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_frpll_aud_frequp      :  1,    //     23
    reg_frpll_aud_a           :  6,    //  29:24
    reg_frpll_aud_in_divrstb  :  1,    //     30
    reg_frpll_aud_icp_g       :  1;    //     31
}CTOP_CTRL_BMC_FRPLL28_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0874    adc_output ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adc_output_mex_sel    :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}CTOP_CTRL_BMC_ADC_OUTPUT_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                                   acodec0                  ;         // 0xC34E_0800
CTOP_CTRL_BMC_ACODEC1_O20A0_T                acodec1                  ;         // 0xC34E_0804
CTOP_CTRL_BMC_ACODEC2_O20A0_T                acodec2                  ;         // 0xC34E_0808
CTOP_CTRL_BMC_ACODEC3_O20A0_T                acodec3                  ;         // 0xC34E_080C
CTOP_CTRL_BMC_ACODEC4_O20A0_T                acodec4                  ;         // 0xC34E_0810
CTOP_CTRL_BMC_ADMD_MIP5_O20A0_T              admd_mip5                ;         // 0xC34E_0814
CTOP_CTRL_BMC_ADMD_MIP6_O20A0_T              admd_mip6                ;         // 0xC34E_0818
CTOP_CTRL_BMC_ADMD_MIP7_O20A0_T              admd_mip7                ;         // 0xC34E_081C
CTOP_CTRL_BMC_ADMD_MIP8_O20A0_T              admd_mip8                ;         // 0xC34E_0820
CTOP_CTRL_BMC_ADMD_MIP9_O20A0_T              admd_mip9                ;         // 0xC34E_0824
CTOP_CTRL_BMC_VIDEOAFE10_O20A0_T             videoafe10               ;         // 0xC34E_0828
CTOP_CTRL_BMC_VIDEOAFE11_O20A0_T             videoafe11               ;         // 0xC34E_082C
CTOP_CTRL_BMC_VIDEOAFE12_O20A0_T             videoafe12               ;         // 0xC34E_0830
CTOP_CTRL_BMC_VIDEOAFE13_O20A0_T             videoafe13               ;         // 0xC34E_0834
CTOP_CTRL_BMC_VIDEOAFE14_O20A0_T             videoafe14               ;         // 0xC34E_0838
CTOP_CTRL_BMC_VIDEOAFE15_O20A0_T             videoafe15               ;         // 0xC34E_083C
CTOP_CTRL_BMC_VIDEOAFE16_O20A0_T             videoafe16               ;         // 0xC34E_0840
CTOP_CTRL_BMC_VIDEOAFE17_O20A0_T             videoafe17               ;         // 0xC34E_0844
CTOP_CTRL_BMC_VIDEOAFE18_O20A0_T             videoafe18               ;         // 0xC34E_0848
CTOP_CTRL_BMC_VIDEOAFE19_O20A0_T             videoafe19               ;         // 0xC34E_084C
CTOP_CTRL_BMC_VIDEOAFE20_O20A0_T             videoafe20               ;         // 0xC34E_0850
CTOP_CTRL_BMC_AIOPLLS21_O20A0_T              aioplls21                ;         // 0xC34E_0854
CTOP_CTRL_BMC_RXCLKDRV_MD22_O20A0_T          rxclkdrv_md22            ;         // 0xC34E_0858
CTOP_CTRL_BMC_FRPLL23_O20A0_T                frpll23                  ;         // 0xC34E_085C
CTOP_CTRL_BMC_FRPLL24_O20A0_T                frpll24                  ;         // 0xC34E_0860
CTOP_CTRL_BMC_FRPLL25_O20A0_T                frpll25                  ;         // 0xC34E_0864
CTOP_CTRL_BMC_FRPLL26_O20A0_T                frpll26                  ;         // 0xC34E_0868
CTOP_CTRL_BMC_FRPLL27_O20A0_T                frpll27                  ;         // 0xC34E_086C
CTOP_CTRL_BMC_FRPLL28_O20A0_T                frpll28                  ;         // 0xC34E_0870
CTOP_CTRL_BMC_ADC_OUTPUT_O20A0_T             adc_output               ;         // 0xC34E_0874
} CTOP_CTRL_BMC_REG_O20A0_T;
/* 30 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_BMC_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

