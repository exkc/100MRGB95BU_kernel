#ifndef _BND_CTRL_BMC_REG_H_
#define _BND_CTRL_BMC_REG_H_

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
    0xCA83_3000    acodec0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_afe_pdb     :  1,    //      0
                              :  2,    //   2: 1 reserved
    reg_pl_drv_aon_pdb        :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_tx_lo_drv_usb_wifi_pdb:  1,    //      8
    reg_tx_lo_drv_usb_wifi_ck_div: 1,    //    9
                              : 22;    //  31:10 reserved
}BND_CTRL_BMC_ACODEC0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3004    acodec1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_ic_vcom           :  2,    //   1: 0
    reg_aud_ic_vbuf           :  2,    //   3: 2
    reg_aud_ic_bgr            :  2,    //   5: 4
    reg_aud_ft_mode           :  1,    //      6
    reg_aud_cnt_rdiv          :  1,    //      7
    reg_aud_ccont             :  2,    //   9: 8
    reg_auda_chop_freq_scf    :  2,    //  11:10
    reg_auda_chop_freq_d2s    :  2,    //  13:12
    reg_auda_chop_en          :  1,    //     14
    reg_auda_pdb_clk          :  1,    //     15
    reg_auda_ic_scfr          :  2,    //  17:16
    reg_auda_ic_scfl          :  2,    //  19:18
    reg_auda_ic_refpr         :  2,    //  21:20
    reg_auda_ic_refpl         :  2,    //  23:22
    reg_auda_ic_refr          :  2,    //  25:24
    reg_auda_ic_refl          :  2,    //  27:26
    reg_auda_ic_d2sr          :  2,    //  29:28
    reg_auda_ic_d2sl          :  2;    //  31:30
}BND_CTRL_BMC_ACODEC1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3008    acodec2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auda_pdb_dac          :  1,    //      0
                              :  4,    //   4: 1 reserved
    reg_auda_ramp_res         :  3,    //   7: 5
    reg_auda_pdb_ref_gen_r    :  1,    //      8
    reg_auda_pdb_ref_gen_l    :  1,    //      9
    reg_auda_vcont_refp_r     :  3,    //  12:10
    reg_auda_vcont_refp_l     :  3,    //  15:13
    reg_auda_rstb_r           :  1,    //     16
    reg_auda_rstb_l           :  1,    //     17
    reg_auda_pdb_scf_r        :  1,    //     18
    reg_auda_pdb_scf_l        :  1,    //     19
    reg_auda_chop_en_scf_r    :  1,    //     20
    reg_auda_chop_en_scf_l    :  1,    //     21
    reg_auda_chop_en_refp_r   :  1,    //     22
    reg_auda_chop_en_refp_l   :  1,    //     23
    reg_auda_chop_en_ref      :  1,    //     24
    reg_auda_chop_en_d2s      :  1,    //     25
    reg_aud_vcom_cont         :  2,    //  27:26
    reg_aud_sel_vref_out      :  1,    //     28
    reg_aud_res               :  3;    //  31:29
}BND_CTRL_BMC_ACODEC2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_300C    acodec3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    reg_aud_pdb_bias          :  1,    //     13
                              :  2,    //  15:14 reserved
    reg_auda_i_con            :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_reserve_in2           :  5,    //  24:20
                              :  3,    //  27:25 reserved
    reg_ic_ramp               :  2,    //  29:28
    reg_ic_comp               :  2;    //  31:30
}BND_CTRL_BMC_ACODEC3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3010    admd_mip5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_admd_t_sel_clkinv     :  1,    //      5
    reg_admd_i_pdb            :  1,    //      6
    reg_admd_a_sel_sif        :  1,    //      7
    reg_admd_a_adc_icon       :  3,    //  10: 8
    reg_admd_apll_icp         :  4,    //  14:11
                              :  5,    //  19:15 reserved
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
}BND_CTRL_BMC_ADMD_MIP5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3014    admd_mip6 ''
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
}BND_CTRL_BMC_ADMD_MIP6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3018    admd_mip7 ''
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
}BND_CTRL_BMC_ADMD_MIP7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_301C    admd_mip8 ''
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
}BND_CTRL_BMC_ADMD_MIP8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3020    admd_mip9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_admd_apll_odpre       :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_admd_apll_dto_en      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_admd_apll_dto_divsel  :  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_BMC_ADMD_MIP9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3030    videoafe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_cpll_pdb        :  1,    //      0
    reg_llpll_regpdb          :  1,    //      1
    reg_refpll_pdb            :  1,    //      2
    reg_videoafe_cvbs_pdbm    :  1,    //      3
    reg_videoafe_cvbs_reg_pdb :  1,    //      4
    reg_videoafe_cvbs_pdb     :  1,    //      5
                              : 26;    //   31:6 reserved
}BND_CTRL_BMC_VIDEOAFE10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3034    videoafe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_videoafe_cvbs_adcisel_bs2: 2,    //  1:0
    reg_videoafe_cvbs_dcatt   :  1,    //      2
    reg_videoafe_cvbs_cmlfsel :  3,    //   5: 3
    reg_videoafe_cvbs_isel    :  3,    //   8: 6
                              :  3,    //  11: 9 reserved
    reg_videoafe_cvbs_refsel  :  2,    //  13:12
    reg_llpll_cvbs_lock       :  2,    //  15:14
    reg_videoafe_cvbs_decm    :  2,    //  17:16
    reg_llpll_nsc             :  4,    //  21:18
    reg_videoafe_cvbs_clp     :  1,    //     22
    reg_videoafe_cvbs_iclp2   :  2,    //  24:23
    reg_videoafe_cvbs_adcisel_bs1: 2,    //  26:25
    reg_videoafe_cvbs_bw      :  1,    //     27
    reg_videoafe_cvbs_dcsel   :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BND_CTRL_BMC_VIDEOAFE11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3038    videoafe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_llpll_icpcon          :  5,    //   4: 0
    reg_videoafe_cvbs_regsel  :  2,    //   6: 5
    reg_videoafe_cvbs_iclp    :  2,    //   8: 7
    reg_videoafe_cvbs_shield_on: 2,    //  10: 9
    reg_videoafe_cvbs_insel   :  1,    //     11
    reg_videoafe_cvbs_adcisel_vref_bs: 2,    //  13:12
    reg_videoafe_cvbs_cksel   :  1,    //     14
    reg_videoafe_cvbs_adcisel_bs3: 2,    //  16:15
    reg_llpll_npc             :  5,    //  21:17
    reg_llpll_lpfr_dis        :  1,    //     22
    reg_llpll_ref_vcon        :  1,    //     23
    reg_llpll_ref_lock_ctl    :  2,    //  25:24
    reg_llpll_div10_sel       :  1,    //     26
    reg_videoafe_cvbs_lpf     :  1,    //     27
    reg_videoafe_cvbs_ibuf    :  3,    //  30:28
                              :  1;    //  31:31 reserved
}BND_CTRL_BMC_VIDEOAFE12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3050    bnd_bmc_vd3_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd3_npwrup_sram       :  8,    //   7: 0
    reg_vd3_pwrup             :  4,    //  11: 8
    reg_vd3_pwrup_ack         :  4,    //  15:12
    reg_vd3_nisol_en          :  1,    //     16
                              : 15;    //  31:17 reserved
}BND_CTRL_BMC_SYN_BND_BMC_VD3_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3054    bnd_bmc_r21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_SYN_BND_BMC_R21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3058    bnd_bmc_r22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_305C    bnd_bmc_r23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_SYN_BND_BMC_R23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3060    bnd_bmc_r24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3064    bnd_bmc_r25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_SYN_BND_BMC_R25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3068    bnd_bmc_r26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_306C    bnd_bmc_r27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_inv_aud_fs00_clk  :  1,    //      0
    reg_sel_inv_mclk2         :  1,    //      1
    reg_sel_inv_mclk1         :  1,    //      2
    reg_sel_inv_mclk0         :  1,    //      3
    reg_sel_inv_f27m_clock    :  1,    //      4
    reg_sel_inv_aclk_mux_mip_dig: 1,    //     5
                              : 26;    //   31:6 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3070    bnd_bmc_r28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f1fs_clk_sel          :  1,    //      0
    reg_f64fs_clk_sel         :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3074    bnd_bmc_r29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_auda_f256fs_clk2:  1,    //      0
    reg_swrst_auda_f256fs_clk1:  1,    //      1
    reg_swrst_auda_f256fs_clk0:  1,    //      2
    reg_swrst_aclk_mux_mip_dig:  1,    //      3
    reg_swrst_adto3           :  1,    //      4
    reg_swrst_adto2           :  1,    //      5
    reg_swrst_adto1           :  1,    //      6
    reg_swrst_auad            :  1,    //      7
    reg_swrst_pix             :  1,    //      8
    reg_swrst_f50m            :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3078    bnd_bmc_r30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aclk_mux_auda_clk2_div:  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_aclk_mux_auda_clk2_src:  4,    //   7: 4
    reg_aclk_mux_auda_clk1_div:  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_aclk_mux_auda_clk1_src:  4,    //  15:12
    reg_aclk_mux_auda_clk0_div:  3,    //  18:16
                              :  1,    //     19 reserved
    reg_aclk_mux_auda_clk0_src:  4,    //  23:20
    reg_aclk_mux_mip_dig_div  :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_aclk_mux_mip_dig_src  :  4;    //  31:28
}BND_CTRL_BMC_SYN_BND_BMC_R30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_307C    bnd_bmc_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sync_update_adto3     :  1,    //      0
    reg_sync_update_adto2     :  1,    //      1
    reg_sync_update_adto1     :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R31_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3084    bnd_bmc_r33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f200_sel              :  1,    //      0
    reg_f50_sel               :  1,    //      1
    reg_f27_18_sel            :  1,    //      2
                              :  1,    //      3 reserved
    reg_sc_ext_sel            :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R33_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3088    bnd_bmc_r34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_pop_en                :  1,    //     24
                              :  7;    //  31:25 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R34_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C0    bnd_bmc_r47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R47_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C4    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_monitor_sel_0         :  4,    //   3: 0
    reg_monitor_sel_1         :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}BND_CTRL_BMC_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C8    bnd_bmc_r48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_pga_gcont        :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_auad_ic_quant         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auad_sel_pga          :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_auad_adc_pdb          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_auad_pga_ref_pdb      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_auad_refp_pdb         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_auad_pga_pdb          :  1,    //     24
                              :  7;    //  31:25 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R48_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30CC    bnd_bmc_r49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_ch1_sel          :  1,    //      0
    reg_auad_refp_en          :  1,    //      1
    reg_auad_en_int_pga       :  1,    //      2
    reg_auad_pga_chop_en      :  1,    //      3
    reg_auad_ic_pga           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auad_ic_int1          :  2,    //   9: 8
                              :  6,    //  15:10 reserved
    reg_auad_ic_ref           :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_auad_sdm_chop_en      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_auad_ic_int2          :  2,    //  25:24
    reg_auad_ic_refp          :  2,    //  27:26
                              :  4;    //  31:28 reserved
}BND_CTRL_BMC_SYN_BND_BMC_R49_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30D0    bnd_bmc_r50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_chen_amp         :  1,    //      0
    reg_auad_en_ext           :  1,    //      1
    reg_auad_chen_cmfb        :  1,    //      2
    reg_auad_ch2_sel          :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_reserve_in1           :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_auad_ch_out_enb       :  1,    //     16
    reg_auad_refn_en          :  1,    //     17
    reg_auad_en_int           :  1,    //     18
    reg_auad_refp_ch_en       :  1,    //     19
    reg_auad_div_sel_sdm      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_auad_vcont_refp       :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_auad_ref_chop_en      :  1,    //     28
    reg_auad_en_ext_pga       :  1,    //     29
    reg_auad_d_inv_enb        :  1,    //     30
    reg_auad_mclk_en          :  1;    //     31
}BND_CTRL_BMC_SYN_BND_BMC_R50_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_BMC_ACODEC0_O22A0_T            acodec0    ;             // 0xCA83_3000
    BND_CTRL_BMC_ACODEC1_O22A0_T            acodec1    ;             // 0xCA83_3004
    BND_CTRL_BMC_ACODEC2_O22A0_T            acodec2    ;             // 0xCA83_3008
    BND_CTRL_BMC_ACODEC3_O22A0_T            acodec3    ;             // 0xCA83_300C
    BND_CTRL_BMC_ADMD_MIP5_O22A0_T          admd_mip5  ;             // 0xCA83_3010
    BND_CTRL_BMC_ADMD_MIP6_O22A0_T          admd_mip6  ;             // 0xCA83_3014
    BND_CTRL_BMC_ADMD_MIP7_O22A0_T          admd_mip7  ;             // 0xCA83_3018
    BND_CTRL_BMC_ADMD_MIP8_O22A0_T          admd_mip8  ;             // 0xCA83_301C
    BND_CTRL_BMC_ADMD_MIP9_O22A0_T          admd_mip9  ;             // 0xCA83_3020
    UINT32                             _rsvd_00[3];             // 0xCA83_3024 ~ 0xCA83_302C
    BND_CTRL_BMC_VIDEOAFE10_O22A0_T         videoafe10 ;             // 0xCA83_3030
    BND_CTRL_BMC_VIDEOAFE11_O22A0_T         videoafe11 ;             // 0xCA83_3034
    BND_CTRL_BMC_VIDEOAFE12_O22A0_T         videoafe12 ;             // 0xCA83_3038
    UINT32                             _rsvd_01[5];             // 0xCA83_303C ~ 0xCA83_304C
    BND_CTRL_BMC_SYN_BND_BMC_VD3_R01_O22A0_T    bnd_bmc_vd3_r01;         // 0xCA83_3050
    BND_CTRL_BMC_SYN_BND_BMC_R21_O22A0_T        bnd_bmc_r21;             // 0xCA83_3054
    BND_CTRL_BMC_SYN_BND_BMC_R22_O22A0_T        bnd_bmc_r22;             // 0xCA83_3058
    BND_CTRL_BMC_SYN_BND_BMC_R23_O22A0_T        bnd_bmc_r23;             // 0xCA83_305C
    BND_CTRL_BMC_SYN_BND_BMC_R24_O22A0_T        bnd_bmc_r24;             // 0xCA83_3060
    BND_CTRL_BMC_SYN_BND_BMC_R25_O22A0_T        bnd_bmc_r25;             // 0xCA83_3064
    BND_CTRL_BMC_SYN_BND_BMC_R26_O22A0_T        bnd_bmc_r26;             // 0xCA83_3068
    BND_CTRL_BMC_SYN_BND_BMC_R27_O22A0_T        bnd_bmc_r27;             // 0xCA83_306C
    BND_CTRL_BMC_SYN_BND_BMC_R28_O22A0_T        bnd_bmc_r28;             // 0xCA83_3070
    BND_CTRL_BMC_SYN_BND_BMC_R29_O22A0_T        bnd_bmc_r29;             // 0xCA83_3074
    BND_CTRL_BMC_SYN_BND_BMC_R30_O22A0_T        bnd_bmc_r30;             // 0xCA83_3078
    BND_CTRL_BMC_SYN_BND_BMC_R31_O22A0_T        bnd_bmc_r31;             // 0xCA83_307C
    UINT32                             _rsvd_02[1];             // 0xCA83_3080
    BND_CTRL_BMC_SYN_BND_BMC_R33_O22A0_T        bnd_bmc_r33;             // 0xCA83_3084
    BND_CTRL_BMC_SYN_BND_BMC_R34_O22A0_T        bnd_bmc_r34;             // 0xCA83_3088
    UINT32                             _rsvd_03[13];            // 0xCA83_308C ~ 0xCA83_30BC
    BND_CTRL_BMC_SYN_BND_BMC_R47_O22A0_T        bnd_bmc_r47;             // 0xCA83_30C0
    BND_CTRL_BMC_SYN_BND_HDMI_R01_O22A0_T       bnd_hdmi_r01;            // 0xCA83_30C4
    BND_CTRL_BMC_SYN_BND_BMC_R48_O22A0_T        bnd_bmc_r48;             // 0xCA83_30C8
    BND_CTRL_BMC_SYN_BND_BMC_R49_O22A0_T        bnd_bmc_r49;             // 0xCA83_30CC
    BND_CTRL_BMC_SYN_BND_BMC_R50_O22A0_T        bnd_bmc_r50;             // 0xCA83_30D0
}BND_CTRL_BMC_REG_O22A0_T;
/* 31 regs */

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

#define BND_CTRL_BMC_ACODEC0_O22A0_T_OFF                         (BASEADDRESS+0x0000)
#define BND_CTRL_BMC_ACODEC1_O22A0_T_OFF                         (BASEADDRESS+0x0004)
#define BND_CTRL_BMC_ACODEC2_O22A0_T_OFF                         (BASEADDRESS+0x0008)
#define BND_CTRL_BMC_ACODEC3_O22A0_T_OFF                         (BASEADDRESS+0x000C)
#define BND_CTRL_BMC_ADMD_MIP5_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define BND_CTRL_BMC_ADMD_MIP6_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define BND_CTRL_BMC_ADMD_MIP7_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define BND_CTRL_BMC_ADMD_MIP8_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define BND_CTRL_BMC_ADMD_MIP9_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define BND_CTRL_BMC_VIDEOAFE10_O22A0_T_OFF                      (BASEADDRESS+0x0030)
#define BND_CTRL_BMC_VIDEOAFE11_O22A0_T_OFF                      (BASEADDRESS+0x0034)
#define BND_CTRL_BMC_VIDEOAFE12_O22A0_T_OFF                      (BASEADDRESS+0x0038)
#define BND_CTRL_BMC_SYN_BND_BMC_VD3_R01_O22A0_T_OFF                 (BASEADDRESS+0x0050)
#define BND_CTRL_BMC_SYN_BND_BMC_R21_O22A0_T_OFF                     (BASEADDRESS+0x0054)
#define BND_CTRL_BMC_SYN_BND_BMC_R22_O22A0_T_OFF                     (BASEADDRESS+0x0058)
#define BND_CTRL_BMC_SYN_BND_BMC_R23_O22A0_T_OFF                     (BASEADDRESS+0x005C)
#define BND_CTRL_BMC_SYN_BND_BMC_R24_O22A0_T_OFF                     (BASEADDRESS+0x0060)
#define BND_CTRL_BMC_SYN_BND_BMC_R25_O22A0_T_OFF                     (BASEADDRESS+0x0064)
#define BND_CTRL_BMC_SYN_BND_BMC_R26_O22A0_T_OFF                     (BASEADDRESS+0x0068)
#define BND_CTRL_BMC_SYN_BND_BMC_R27_O22A0_T_OFF                     (BASEADDRESS+0x006C)
#define BND_CTRL_BMC_SYN_BND_BMC_R28_O22A0_T_OFF                     (BASEADDRESS+0x0070)
#define BND_CTRL_BMC_SYN_BND_BMC_R29_O22A0_T_OFF                     (BASEADDRESS+0x0074)
#define BND_CTRL_BMC_SYN_BND_BMC_R30_O22A0_T_OFF                     (BASEADDRESS+0x0078)
#define BND_CTRL_BMC_SYN_BND_BMC_R31_O22A0_T_OFF                     (BASEADDRESS+0x007C)
#define BND_CTRL_BMC_SYN_BND_BMC_R33_O22A0_T_OFF                     (BASEADDRESS+0x0084)
#define BND_CTRL_BMC_SYN_BND_BMC_R34_O22A0_T_OFF                     (BASEADDRESS+0x0088)
#define BND_CTRL_BMC_SYN_BND_BMC_R47_O22A0_T_OFF                     (BASEADDRESS+0x00C0)
#define BND_CTRL_BMC_SYN_BND_HDMI_R01_O22A0_T_OFF                    (BASEADDRESS+0x00C4)
#define BND_CTRL_BMC_SYN_BND_BMC_R48_O22A0_T_OFF                     (BASEADDRESS+0x00C8)
#define BND_CTRL_BMC_SYN_BND_BMC_R49_O22A0_T_OFF                     (BASEADDRESS+0x00CC)
#define BND_CTRL_BMC_SYN_BND_BMC_R50_O22A0_T_OFF                     (BASEADDRESS+0x00D0)

/*-----------------------------------------------------------------------------------------
    0xCA83_3000    acodec0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_afe_pdb: 1;    //     0
    UINT32 resvd00            :  2;    //   2: 1 reserved
    UINT32 reg_pl_drv_aon_pdb :  1;    //      3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_tx_lo_drv_usb_wifi_pdb: 1;    //  8
    UINT32 reg_tx_lo_drv_usb_wifi_ck_div: 1;    //  9
    UINT32 resvd02            : 22;    //  31:10 reserved
    };
}BND_CTRL_BMC_ACODEC0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3004    acodec1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_ic_vcom    :  2;    //   1: 0
    UINT32 reg_aud_ic_vbuf    :  2;    //   3: 2
    UINT32 reg_aud_ic_bgr     :  2;    //   5: 4
    UINT32 reg_aud_ft_mode    :  1;    //      6
    UINT32 reg_aud_cnt_rdiv   :  1;    //      7
    UINT32 reg_aud_ccont      :  2;    //   9: 8
    UINT32 reg_auda_chop_freq_scf: 2;    //  11:10
    UINT32 reg_auda_chop_freq_d2s: 2;    //  13:12
    UINT32 reg_auda_chop_en   :  1;    //     14
    UINT32 reg_auda_pdb_clk   :  1;    //     15
    UINT32 reg_auda_ic_scfr   :  2;    //  17:16
    UINT32 reg_auda_ic_scfl   :  2;    //  19:18
    UINT32 reg_auda_ic_refpr  :  2;    //  21:20
    UINT32 reg_auda_ic_refpl  :  2;    //  23:22
    UINT32 reg_auda_ic_refr   :  2;    //  25:24
    UINT32 reg_auda_ic_refl   :  2;    //  27:26
    UINT32 reg_auda_ic_d2sr   :  2;    //  29:28
    UINT32 reg_auda_ic_d2sl   :  2;    //  31:30
    };
}BND_CTRL_BMC_ACODEC1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3008    acodec2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auda_pdb_dac   :  1;    //      0
    UINT32 resvd00            :  4;    //   4: 1 reserved
    UINT32 reg_auda_ramp_res  :  3;    //   7: 5
    UINT32 reg_auda_pdb_ref_gen_r: 1;    //    8
    UINT32 reg_auda_pdb_ref_gen_l: 1;    //    9
    UINT32 reg_auda_vcont_refp_r: 3;    //  12:10
    UINT32 reg_auda_vcont_refp_l: 3;    //  15:13
    UINT32 reg_auda_rstb_r    :  1;    //     16
    UINT32 reg_auda_rstb_l    :  1;    //     17
    UINT32 reg_auda_pdb_scf_r :  1;    //     18
    UINT32 reg_auda_pdb_scf_l :  1;    //     19
    UINT32 reg_auda_chop_en_scf_r: 1;    //   20
    UINT32 reg_auda_chop_en_scf_l: 1;    //   21
    UINT32 reg_auda_chop_en_refp_r: 1;    //  22
    UINT32 reg_auda_chop_en_refp_l: 1;    //  23
    UINT32 reg_auda_chop_en_ref: 1;    //     24
    UINT32 reg_auda_chop_en_d2s: 1;    //     25
    UINT32 reg_aud_vcom_cont  :  2;    //  27:26
    UINT32 reg_aud_sel_vref_out: 1;    //     28
    UINT32 reg_aud_res        :  3;    //  31:29
    };
}BND_CTRL_BMC_ACODEC2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_300C    acodec3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 13;    //  12: 0 reserved
    UINT32 reg_aud_pdb_bias   :  1;    //     13
    UINT32 resvd01            :  2;    //  15:14 reserved
    UINT32 reg_auda_i_con     :  2;    //  17:16
    UINT32 resvd02            :  2;    //  19:18 reserved
    UINT32 reg_reserve_in2    :  5;    //  24:20
    UINT32 resvd03            :  3;    //  27:25 reserved
    UINT32 reg_ic_ramp        :  2;    //  29:28
    UINT32 reg_ic_comp        :  2;    //  31:30
    };
}BND_CTRL_BMC_ACODEC3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3010    admd_mip5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_admd_t_sel_clkinv: 1;    //     5
    UINT32 reg_admd_i_pdb     :  1;    //      6
    UINT32 reg_admd_a_sel_sif :  1;    //      7
    UINT32 reg_admd_a_adc_icon:  3;    //  10: 8
    UINT32 reg_admd_apll_icp  :  4;    //  14:11
    UINT32 resvd01            :  5;    //  19:15 reserved
    UINT32 reg_admd_apll_autofreq: 1;    //   20
    UINT32 reg_admd_a_adc_refsel: 2;    //  22:21
    UINT32 reg_admd_apll_icp_g:  1;    //     23
    UINT32 reg_admd_a_pdb     :  1;    //     24
    UINT32 reg_admd_apll_outsel: 1;    //     25
    UINT32 reg_admd_a_bias_pdb:  1;    //     26
    UINT32 reg_admd_apll_lpf_on: 1;    //     27
    UINT32 reg_admd_a_sel_clkinv: 1;    //    28
    UINT32 reg_admd_apll_frequp: 1;    //     29
    UINT32 reg_admd_a_decm    :  2;    //  31:30
    };
}BND_CTRL_BMC_ADMD_MIP5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3014    admd_mip6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_apll_insel:  1;    //      1
    UINT32 reg_admd_apll_cken :  3;    //   4: 2
    UINT32 reg_admd_dpll_wakebypass: 1;    //  5
    UINT32 reg_admd_dpll_lpf_on: 1;    //      6
    UINT32 reg_admd_t_pdb     :  1;    //      7
    UINT32 reg_admd_i_decm    :  2;    //   9: 8
    UINT32 reg_admd_apll_lockf:  1;    //     10
    UINT32 reg_admd_apll_wakebypass: 1;    //  11
    UINT32 reg_admd_dpll_od_en:  1;    //     12
    UINT32 reg_admd_dpll_frequp: 1;    //     13
    UINT32 reg_admd_q_pdb     :  1;    //     14
    UINT32 reg_admd_adc_icon  :  3;    //  17:15
    UINT32 reg_admd_dpll_lockc:  1;    //     18
    UINT32 reg_admd_apll_od_en:  1;    //     19
    UINT32 reg_admd_dpll_odpre:  6;    //  25:20
    UINT32 reg_admd_dpll_m    :  6;    //  31:26
    };
}BND_CTRL_BMC_ADMD_MIP6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3018    admd_mip7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_dpll_autofreq: 1;    //    1
    UINT32 reg_admd_i_sel_clkinv: 1;    //     2
    UINT32 reg_admd_apll_odpost: 6;    //   8: 3
    UINT32 reg_admd_apll_divint: 9;    //  17: 9
    UINT32 reg_admd_dpll_syncon: 1;    //     18
    UINT32 reg_admd_dpll_icp_g:  1;    //     19
    UINT32 reg_admd_t_decm    :  2;    //  21:20
    UINT32 reg_admd_bias_pdb  :  1;    //     22
    UINT32 reg_admd_apll_lockc:  1;    //     23
    UINT32 reg_admd_dpll_insel:  1;    //     24
    UINT32 reg_admd_apll_syncon: 1;    //     25
    UINT32 reg_admd_dpll_cken :  3;    //  28:26
    UINT32 reg_admd_dpll_outsel: 1;    //     29
    UINT32 reg_admd_q_decm    :  2;    //  31:30
    };
}BND_CTRL_BMC_ADMD_MIP7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_301C    admd_mip8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_apll_m    :  6;    //   6: 1
    UINT32 reg_admd_dpll_pdb  :  1;    //      7
    UINT32 reg_admd_dpll_icp  :  4;    //  11: 8
    UINT32 reg_admd_q_sel_clkinv: 1;    //    12
    UINT32 reg_admd_adc_refsel:  2;    //  14:13
    UINT32 reg_admd_dpll_lockf:  1;    //     15
    UINT32 reg_admd_apll_pdb  :  1;    //     16
    UINT32 reg_admd_dpll_odpost: 6;    //  22:17
    UINT32 reg_admd_dpll_divint: 9;    //  31:23
    };
}BND_CTRL_BMC_ADMD_MIP8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3020    admd_mip9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_admd_apll_odpre:  6;    //   5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_admd_apll_dto_en: 1;    //      8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_admd_apll_dto_divsel: 1;    //  12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}BND_CTRL_BMC_ADMD_MIP9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3030    videoafe10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_llpll_cpll_pdb :  1;    //      0
    UINT32 reg_llpll_regpdb   :  1;    //      1
    UINT32 reg_refpll_pdb     :  1;    //      2
    UINT32 reg_videoafe_cvbs_pdbm: 1;    //    3
    UINT32 reg_videoafe_cvbs_reg_pdb: 1;    //  4
    UINT32 reg_videoafe_cvbs_pdb: 1;    //     5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_BMC_VIDEOAFE10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3034    videoafe11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_videoafe_cvbs_adcisel_bs2: 2;    //  1:0
    UINT32 reg_videoafe_cvbs_dcatt: 1;    //   2
    UINT32 reg_videoafe_cvbs_cmlfsel: 3;    //  5:3
    UINT32 reg_videoafe_cvbs_isel: 3;    //  8:6
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_videoafe_cvbs_refsel: 2;    //  13:12
    UINT32 reg_llpll_cvbs_lock:  2;    //  15:14
    UINT32 reg_videoafe_cvbs_decm: 2;    //  17:16
    UINT32 reg_llpll_nsc      :  4;    //  21:18
    UINT32 reg_videoafe_cvbs_clp: 1;    //    22
    UINT32 reg_videoafe_cvbs_iclp2: 2;    //  24:23
    UINT32 reg_videoafe_cvbs_adcisel_bs1: 2;    //  26:25
    UINT32 reg_videoafe_cvbs_bw: 1;    //     27
    UINT32 reg_videoafe_cvbs_dcsel: 2;    //  29:28
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_BMC_VIDEOAFE11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3038    videoafe12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_llpll_icpcon   :  5;    //   4: 0
    UINT32 reg_videoafe_cvbs_regsel: 2;    //  6:5
    UINT32 reg_videoafe_cvbs_iclp: 2;    //  8:7
    UINT32 reg_videoafe_cvbs_shield_on: 2;    //  10:9
    UINT32 reg_videoafe_cvbs_insel: 1;    //  11
    UINT32 reg_videoafe_cvbs_adcisel_vref_bs: 2;    //  13:12
    UINT32 reg_videoafe_cvbs_cksel: 1;    //  14
    UINT32 reg_videoafe_cvbs_adcisel_bs3: 2;    //  16:15
    UINT32 reg_llpll_npc      :  5;    //  21:17
    UINT32 reg_llpll_lpfr_dis :  1;    //     22
    UINT32 reg_llpll_ref_vcon :  1;    //     23
    UINT32 reg_llpll_ref_lock_ctl: 2;    //  25:24
    UINT32 reg_llpll_div10_sel:  1;    //     26
    UINT32 reg_videoafe_cvbs_lpf: 1;    //    27
    UINT32 reg_videoafe_cvbs_ibuf: 3;    //  30:28
    UINT32 resvd00            :  1;    //  31:31 reserved
    };
}BND_CTRL_BMC_VIDEOAFE12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3050    bnd_bmc_vd3_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd3_npwrup_sram:  8;    //   7: 0
    UINT32 reg_vd3_pwrup      :  4;    //  11: 8
    UINT32 reg_vd3_pwrup_ack  :  4;    //  15:12
    UINT32 reg_vd3_nisol_en   :  1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_VD3_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3054    bnd_bmc_r21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_add_value: 32;    //  31: 0
    };
}BND_CTRL_BMC_SYN_BND_BMC_R21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3058    bnd_bmc_r22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_err_value: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_305C    bnd_bmc_r23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_add_value: 32;    //  31: 0
    };
}BND_CTRL_BMC_SYN_BND_BMC_R23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3060    bnd_bmc_r24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_err_value: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3064    bnd_bmc_r25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto3_add_value: 32;    //  31: 0
    };
}BND_CTRL_BMC_SYN_BND_BMC_R25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3068    bnd_bmc_r26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto3_err_value: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_306C    bnd_bmc_r27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel_inv_aud_fs00_clk: 1;    //  0
    UINT32 reg_sel_inv_mclk2  :  1;    //      1
    UINT32 reg_sel_inv_mclk1  :  1;    //      2
    UINT32 reg_sel_inv_mclk0  :  1;    //      3
    UINT32 reg_sel_inv_f27m_clock: 1;    //    4
    UINT32 reg_sel_inv_aclk_mux_mip_dig: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3070    bnd_bmc_r28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f1fs_clk_sel   :  1;    //      0
    UINT32 reg_f64fs_clk_sel  :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3074    bnd_bmc_r29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_auda_f256fs_clk2: 1;    //  0
    UINT32 reg_swrst_auda_f256fs_clk1: 1;    //  1
    UINT32 reg_swrst_auda_f256fs_clk0: 1;    //  2
    UINT32 reg_swrst_aclk_mux_mip_dig: 1;    //  3
    UINT32 reg_swrst_adto3    :  1;    //      4
    UINT32 reg_swrst_adto2    :  1;    //      5
    UINT32 reg_swrst_adto1    :  1;    //      6
    UINT32 reg_swrst_auad     :  1;    //      7
    UINT32 reg_swrst_pix      :  1;    //      8
    UINT32 reg_swrst_f50m     :  1;    //      9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3078    bnd_bmc_r30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aclk_mux_auda_clk2_div: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_aclk_mux_auda_clk2_src: 4;    //  7:4
    UINT32 reg_aclk_mux_auda_clk1_div: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_aclk_mux_auda_clk1_src: 4;    //  15:12
    UINT32 reg_aclk_mux_auda_clk0_div: 3;    //  18:16
    UINT32 resvd02            :  1;    //     19 reserved
    UINT32 reg_aclk_mux_auda_clk0_src: 4;    //  23:20
    UINT32 reg_aclk_mux_mip_dig_div: 3;    //  26:24
    UINT32 resvd03            :  1;    //     27 reserved
    UINT32 reg_aclk_mux_mip_dig_src: 4;    //  31:28
    };
}BND_CTRL_BMC_SYN_BND_BMC_R30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_307C    bnd_bmc_r31 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sync_update_adto3: 1;    //     0
    UINT32 reg_sync_update_adto2: 1;    //     1
    UINT32 reg_sync_update_adto1: 1;    //     2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R31_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3084    bnd_bmc_r33 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f200_sel       :  1;    //      0
    UINT32 reg_f50_sel        :  1;    //      1
    UINT32 reg_f27_18_sel     :  1;    //      2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_sc_ext_sel     :  3;    //   6: 4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R33_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_3088    bnd_bmc_r34 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 24;    //  23: 0 reserved
    UINT32 reg_pop_en         :  1;    //     24
    UINT32 resvd01            :  7;    //  31:25 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R34_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C0    bnd_bmc_r47 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R47_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C4    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_monitor_sel_0  :  4;    //   3: 0
    UINT32 reg_monitor_sel_1  :  4;    //   7: 4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_BMC_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30C8    bnd_bmc_r48 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_pga_gcont :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_auad_ic_quant  :  2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_auad_sel_pga   :  3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_auad_adc_pdb   :  1;    //     12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_auad_pga_ref_pdb: 1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_auad_refp_pdb  :  1;    //     20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_auad_pga_pdb   :  1;    //     24
    UINT32 resvd06            :  7;    //  31:25 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R48_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30CC    bnd_bmc_r49 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_ch1_sel   :  1;    //      0
    UINT32 reg_auad_refp_en   :  1;    //      1
    UINT32 reg_auad_en_int_pga:  1;    //      2
    UINT32 reg_auad_pga_chop_en: 1;    //      3
    UINT32 reg_auad_ic_pga    :  2;    //   5: 4
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_auad_ic_int1   :  2;    //   9: 8
    UINT32 resvd01            :  6;    //  15:10 reserved
    UINT32 reg_auad_ic_ref    :  2;    //  17:16
    UINT32 resvd02            :  2;    //  19:18 reserved
    UINT32 reg_auad_sdm_chop_en: 1;    //     20
    UINT32 resvd03            :  3;    //  23:21 reserved
    UINT32 reg_auad_ic_int2   :  2;    //  25:24
    UINT32 reg_auad_ic_refp   :  2;    //  27:26
    UINT32 resvd04            :  4;    //  31:28 reserved
    };
}BND_CTRL_BMC_SYN_BND_BMC_R49_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA83_30D0    bnd_bmc_r50 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_chen_amp  :  1;    //      0
    UINT32 reg_auad_en_ext    :  1;    //      1
    UINT32 reg_auad_chen_cmfb :  1;    //      2
    UINT32 reg_auad_ch2_sel   :  1;    //      3
    UINT32 resvd00            :  4;    //   7: 4 reserved
    UINT32 reg_reserve_in1    :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_auad_ch_out_enb:  1;    //     16
    UINT32 reg_auad_refn_en   :  1;    //     17
    UINT32 reg_auad_en_int    :  1;    //     18
    UINT32 reg_auad_refp_ch_en:  1;    //     19
    UINT32 reg_auad_div_sel_sdm: 3;    //  22:20
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_auad_vcont_refp:  3;    //  26:24
    UINT32 resvd03            :  1;    //     27 reserved
    UINT32 reg_auad_ref_chop_en: 1;    //     28
    UINT32 reg_auad_en_ext_pga:  1;    //     29
    UINT32 reg_auad_d_inv_enb :  1;    //     30
    UINT32 reg_auad_mclk_en   :  1;    //     31
    };
}BND_CTRL_BMC_SYN_BND_BMC_R50_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_BMC_ACODEC0_O22A0_T            acodec0    ;             // 0xCA83_3000
    BND_CTRL_BMC_ACODEC1_O22A0_T            acodec1    ;             // 0xCA83_3004
    BND_CTRL_BMC_ACODEC2_O22A0_T            acodec2    ;             // 0xCA83_3008
    BND_CTRL_BMC_ACODEC3_O22A0_T            acodec3    ;             // 0xCA83_300C
    BND_CTRL_BMC_ADMD_MIP5_O22A0_T          admd_mip5  ;             // 0xCA83_3010
    BND_CTRL_BMC_ADMD_MIP6_O22A0_T          admd_mip6  ;             // 0xCA83_3014
    BND_CTRL_BMC_ADMD_MIP7_O22A0_T          admd_mip7  ;             // 0xCA83_3018
    BND_CTRL_BMC_ADMD_MIP8_O22A0_T          admd_mip8  ;             // 0xCA83_301C
    BND_CTRL_BMC_ADMD_MIP9_O22A0_T          admd_mip9  ;             // 0xCA83_3020
    UINT32                             _rsvd_00[3];             // 0xCA83_3024 ~ 0xCA83_302C
    BND_CTRL_BMC_VIDEOAFE10_O22A0_T         videoafe10 ;             // 0xCA83_3030
    BND_CTRL_BMC_VIDEOAFE11_O22A0_T         videoafe11 ;             // 0xCA83_3034
    BND_CTRL_BMC_VIDEOAFE12_O22A0_T         videoafe12 ;             // 0xCA83_3038
    UINT32                             _rsvd_01[5];             // 0xCA83_303C ~ 0xCA83_304C
    BND_CTRL_BMC_SYN_BND_BMC_VD3_R01_O22A0_T    bnd_bmc_vd3_r01;         // 0xCA83_3050
    BND_CTRL_BMC_SYN_BND_BMC_R21_O22A0_T        bnd_bmc_r21;             // 0xCA83_3054
    BND_CTRL_BMC_SYN_BND_BMC_R22_O22A0_T        bnd_bmc_r22;             // 0xCA83_3058
    BND_CTRL_BMC_SYN_BND_BMC_R23_O22A0_T        bnd_bmc_r23;             // 0xCA83_305C
    BND_CTRL_BMC_SYN_BND_BMC_R24_O22A0_T        bnd_bmc_r24;             // 0xCA83_3060
    BND_CTRL_BMC_SYN_BND_BMC_R25_O22A0_T        bnd_bmc_r25;             // 0xCA83_3064
    BND_CTRL_BMC_SYN_BND_BMC_R26_O22A0_T        bnd_bmc_r26;             // 0xCA83_3068
    BND_CTRL_BMC_SYN_BND_BMC_R27_O22A0_T        bnd_bmc_r27;             // 0xCA83_306C
    BND_CTRL_BMC_SYN_BND_BMC_R28_O22A0_T        bnd_bmc_r28;             // 0xCA83_3070
    BND_CTRL_BMC_SYN_BND_BMC_R29_O22A0_T        bnd_bmc_r29;             // 0xCA83_3074
    BND_CTRL_BMC_SYN_BND_BMC_R30_O22A0_T        bnd_bmc_r30;             // 0xCA83_3078
    BND_CTRL_BMC_SYN_BND_BMC_R31_O22A0_T        bnd_bmc_r31;             // 0xCA83_307C
    UINT32                             _rsvd_02[1];             // 0xCA83_3080
    BND_CTRL_BMC_SYN_BND_BMC_R33_O22A0_T        bnd_bmc_r33;             // 0xCA83_3084
    BND_CTRL_BMC_SYN_BND_BMC_R34_O22A0_T        bnd_bmc_r34;             // 0xCA83_3088
    UINT32                             _rsvd_03[13];            // 0xCA83_308C ~ 0xCA83_30BC
    BND_CTRL_BMC_SYN_BND_BMC_R47_O22A0_T        bnd_bmc_r47;             // 0xCA83_30C0
    BND_CTRL_BMC_SYN_BND_HDMI_R01_O22A0_T       bnd_hdmi_r01;            // 0xCA83_30C4
    BND_CTRL_BMC_SYN_BND_BMC_R48_O22A0_T        bnd_bmc_r48;             // 0xCA83_30C8
    BND_CTRL_BMC_SYN_BND_BMC_R49_O22A0_T        bnd_bmc_r49;             // 0xCA83_30CC
    BND_CTRL_BMC_SYN_BND_BMC_R50_O22A0_T        bnd_bmc_r50;             // 0xCA83_30D0
}BND_CTRL_BMC_REG_O22A0_T;
/* 31 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_BMC_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

