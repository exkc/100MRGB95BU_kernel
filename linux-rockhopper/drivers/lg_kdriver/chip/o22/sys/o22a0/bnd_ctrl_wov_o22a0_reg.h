#ifndef _BND_CTRL_WOV_REG_H_
#define _BND_CTRL_WOV_REG_H_

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
    0xF308_5000    bnd_wov_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_m1_pdb       :  1,    //      0
                              :  2,    //   2: 1 reserved
    reg_rxclkdrv_m1_smv       :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5010    bnd_wov_tx_lo_drv ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tx_lo_drv_ephy_shutdown_pdb: 1,    //  0
    reg_tx_lo_drv_ephy_shutdown_ck_div: 1,    //  1
    reg_tx_lo_drv_nisol_ephy_pdb: 1,    //     2
    reg_tx_lo_drv_nisol_ephy_ck_div: 1,    //  3
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_TX_LO_DRV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_501C    bnd_wov_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopllss_cih      :  4,    //   3: 0
    reg_wov_aiopllss_fine_control: 3,    //  6:4
    reg_wov_aiopllss_fine_div :  1,    //      7
    reg_wov_aiopllss_cih2     :  4,    //  11: 8
    reg_wov_aiopllss_nsc      :  4,    //  15:12
    reg_wov_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_wov_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5020    bnd_wov_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_wov_aiopllss_updn_max :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_wov_aiopllss_accuracy :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_wov_aiopllss_dss      :  1,    //     23
    reg_wov_aiopllss_offset   :  8;    //  31:24
}BND_CTRL_WOV_SYN_BND_WOV_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5024    bnd_wov_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_aiopllss_freq_update: 1,    //     0
    reg_wov_aiopllss_fout1_en :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_wov_aiopllss_lock     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_wov_aiopllss_out_div  :  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_wov_aiopllss_sync_on  :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_wov_aiopllss_wake_bypass: 1,    //    27
    reg_wov_aiopllss_offset_mode: 1,    //    28
                              :  3;    //  31:29 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5028    bnd_wov_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_micom_pdb        :  1,    //      0
                              : 11,    //  11: 1 reserved
    reg_sadc_micom_pc         :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_micom_cc         :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_micom_isel       :  3,    //  22:20
                              :  9;    //  31:23 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_502C    bnd_wov_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_micom_lpf_soc    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_micom_lpf_chsel  :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sadc_micom_lpf_start  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sadc_micom_lpf_dsel   :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_micom_lpf_mode   :  3,    //  18:16
                              :  5,    //  23:19 reserved
    reg_sadc_micom_lpf_eoc_inv:  1,    //     24
                              :  3,    //  27:25 reserved
    reg_sadc_micom_lpf_manual :  1,    //     28
                              :  3;    //  31:29 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5030    bnd_wov_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_micom_lpf_data_clear: 1,    //    0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5034    bnd_wov_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data012          : 32;    //  31: 0
}BND_CTRL_WOV_SYN_BND_WOV_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5038    bnd_wov_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data345          : 32;    //  31: 0
}BND_CTRL_WOV_SYN_BND_WOV_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_503C    bnd_wov_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_micom_lpf_debug_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5040    bnd_wov_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_debug_data       :  8,    //   7: 0
                              : 20,    //  27: 8 reserved
    sadc_micon_lpf_adc_done   :  1,    //     28
                              :  3;    //  31:29 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5060    apll_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_updn_max   :  8,    //   7: 0
    reg_apll_frpll_mod_speed_max: 9,    //  16:8
                              :  7,    //  23:17 reserved
    reg_apll_frpll_lock_cont  :  1,    //     24
    reg_apll_frpll_dss        :  1,    //     25
                              :  5,    //  30:26 reserved
    reg_soft_reset_frpll_sscg :  1;    //     31
}BND_CTRL_WOV_APLL_FRPLL_SSCG_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5068    apll_frpll_r00 ''
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
}BND_CTRL_WOV_APLL_FRPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_506C    apll_frpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fout_en    :  1,    //      0
    reg_apll_frpll_syncon     :  1,    //      1
    reg_apll_frpll_m          :  6,    //   7: 2
    reg_apll_frpll_fcw        : 24;    //  31: 8
}BND_CTRL_WOV_APLL_FRPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5070    apll_frpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_lock       :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_apll_frpll_frequp     :  1,    //     23
    reg_apll_frpll_a          :  6,    //  29:24
    reg_apll_frpll_in_divrstb :  1,    //     30
    reg_apll_frpll_icp_g      :  1;    //     31
}BND_CTRL_WOV_APLL_FRPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5074    apll_frpll_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_out2_div   :  9,    //   8: 0
                              :  3,    //  11: 9 reserved
    reg_apll_frpll_out3_div   :  9,    //  20:12
                              : 11;    //  31:21 reserved
}BND_CTRL_WOV_APLL_FRPLL_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5078    bnd_wov_r024 ''
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
}BND_CTRL_WOV_SYN_BND_WOV_R024_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5084    bnd_wov_r026 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_apll_fcw              : 24,    //  23: 0
    reg_apll_fcw_mux_sel      :  2,    //  25:24
                              :  6;    //  31:26 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R026_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5090    bnd_wov_r029 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cec_gf_en             :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R029_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5094    bnd_wov_r030 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 16,    //  15: 0 reserved
    reg_vdec_aud_apb_31_16    : 16;    //  31:16
}BND_CTRL_WOV_SYN_BND_WOV_R030_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5098    bnd_wov_r031 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aec_aud_input_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R031_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_509C    bnd_wov_r032 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R032_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5100    bnd_wov_r034 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_jtag_sel0            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R034_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5104    bnd_wov_r035 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_jtag_sel1            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R035_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5108    bnd_wov_r036 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_jtag_sel2            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R036_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_510C    bnd_wov_r037 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_jtag_sel3            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R037_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5110    bnd_wov_r038 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_jtag_sel4            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R038_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5114    bnd_wov_r039 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_uart_sel0            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R039_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5118    bnd_wov_r040 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_uart_sel1            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R040_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_511C    bnd_wov_r041 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_uart_sel2            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R041_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5120    bnd_wov_r042 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_uart_sel3            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R042_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5124    bnd_wov_r043 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    main_uart_sel4            :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R043_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5128    bnd_wov_r044 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_araddr_s2_aud         :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_awaddr_s2_aud         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_araddr_s1_aud         :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_awaddr_s1_aud         :  2,    //  13:12
                              : 18;    //  31:14 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R044_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5200    wov_por_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_m12wov          :  1,    //      0
    reg_nisol_top2m1          :  1,    //      1
    reg_nisol_ephy            :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_WOV_WOV_POR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5204    wov_por_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_aud_pdb_ctrl    :  1,    //      0
    reg_aiopll_wov_pdb_ctrl   :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_WOV_WOV_POR_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5208    wov_por_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gating_m1_pll_n       :  1,    //      0
    reg_gating_cpuav_i_m1     :  1,    //      1
    reg_gating_cpuav_i_d100_m1:  1,    //      2
                              :  1,    //      3 reserved
    reg_gating_aiopll_400_clk_out: 1,    //    4
                              : 27;    //   31:5 reserved
}BND_CTRL_WOV_WOV_POR_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_520C    wov_por_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m1pll_pdb_ctrl        :  1,    //      0
    reg_swrst_cpuav_i_d100_m1 :  1,    //      1
    reg_swrst_cpuav_i_m1      :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_WOV_WOV_POR_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5210    wov_por_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_wov             :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_WOV_POR_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5214    bnd_wov_r045 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd2_pv0_wov_hub_flush_en: 1,    //     0
                              :  3,    //   3: 1 reserved
    reg_vd2_pv0_wov_hub_flush_done: 1,    //   4
                              : 27;    //   31:5 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R045_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5218    bnd_wov_r046 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_edid_apb_bnd_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R046_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_521C    bnd_wov_r047 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_topapb_gate_en  :  1,    //      0
    reg_micom_to_m1_apb_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_WOV_SYN_BND_WOV_R047_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5220    crg_top_wov_aon_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sw_reset_from_micom   :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_WOV_CRG_TOP_WOV_AON_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOV_SYN_BND_WOV_RXCLK_MD_R00_O22A0_T    bnd_wov_rxclk_md_r00;    // 0xF308_5000
    UINT32                             _rsvd_00[3];             // 0xF308_5004 ~ 0xF308_500C
    BND_CTRL_WOV_SYN_BND_WOV_TX_LO_DRV_O22A0_T    bnd_wov_tx_lo_drv;     // 0xF308_5010
    UINT32                             _rsvd_01[2];             // 0xF308_5014 ~ 0xF308_5018
    BND_CTRL_WOV_SYN_BND_WOV_R06_O22A0_T        bnd_wov_r06;             // 0xF308_501C
    BND_CTRL_WOV_SYN_BND_WOV_R07_O22A0_T        bnd_wov_r07;             // 0xF308_5020
    BND_CTRL_WOV_SYN_BND_WOV_R08_O22A0_T        bnd_wov_r08;             // 0xF308_5024
    BND_CTRL_WOV_SYN_BND_WOV_R09_O22A0_T        bnd_wov_r09;             // 0xF308_5028
    BND_CTRL_WOV_SYN_BND_WOV_R10_O22A0_T        bnd_wov_r10;             // 0xF308_502C
    BND_CTRL_WOV_SYN_BND_WOV_R11_O22A0_T        bnd_wov_r11;             // 0xF308_5030
    BND_CTRL_WOV_SYN_BND_WOV_R12_O22A0_T        bnd_wov_r12;             // 0xF308_5034
    BND_CTRL_WOV_SYN_BND_WOV_R13_O22A0_T        bnd_wov_r13;             // 0xF308_5038
    BND_CTRL_WOV_SYN_BND_WOV_R14_O22A0_T        bnd_wov_r14;             // 0xF308_503C
    BND_CTRL_WOV_SYN_BND_WOV_R15_O22A0_T        bnd_wov_r15;             // 0xF308_5040
    UINT32                             _rsvd_02[7];             // 0xF308_5044 ~ 0xF308_505C
    BND_CTRL_WOV_APLL_FRPLL_SSCG_R00_O22A0_T    apll_frpll_sscg_r00;    // 0xF308_5060
    UINT32                             _rsvd_03[1];             // 0xF308_5064
    BND_CTRL_WOV_APLL_FRPLL_R00_O22A0_T     apll_frpll_r00;          // 0xF308_5068
    BND_CTRL_WOV_APLL_FRPLL_R01_O22A0_T     apll_frpll_r01;          // 0xF308_506C
    BND_CTRL_WOV_APLL_FRPLL_R02_O22A0_T     apll_frpll_r02;          // 0xF308_5070
    BND_CTRL_WOV_APLL_FRPLL_R03_O22A0_T     apll_frpll_r03;          // 0xF308_5074
    BND_CTRL_WOV_SYN_BND_WOV_R024_O22A0_T       bnd_wov_r024;            // 0xF308_5078
    UINT32                             _rsvd_04[2];             // 0xF308_507C ~ 0xF308_5080
    BND_CTRL_WOV_SYN_BND_WOV_R026_O22A0_T       bnd_wov_r026;            // 0xF308_5084
    UINT32                             _rsvd_05[2];             // 0xF308_5088 ~ 0xF308_508C
    BND_CTRL_WOV_SYN_BND_WOV_R029_O22A0_T       bnd_wov_r029;            // 0xF308_5090
    BND_CTRL_WOV_SYN_BND_WOV_R030_O22A0_T       bnd_wov_r030;            // 0xF308_5094
    BND_CTRL_WOV_SYN_BND_WOV_R031_O22A0_T       bnd_wov_r031;            // 0xF308_5098
    BND_CTRL_WOV_SYN_BND_WOV_R032_O22A0_T       bnd_wov_r032;            // 0xF308_509C
    UINT32                             _rsvd_06[24];            // 0xF308_50A0 ~ 0xF308_50FC
    BND_CTRL_WOV_SYN_BND_WOV_R034_O22A0_T       bnd_wov_r034;            // 0xF308_5100
    BND_CTRL_WOV_SYN_BND_WOV_R035_O22A0_T       bnd_wov_r035;            // 0xF308_5104
    BND_CTRL_WOV_SYN_BND_WOV_R036_O22A0_T       bnd_wov_r036;            // 0xF308_5108
    BND_CTRL_WOV_SYN_BND_WOV_R037_O22A0_T       bnd_wov_r037;            // 0xF308_510C
    BND_CTRL_WOV_SYN_BND_WOV_R038_O22A0_T       bnd_wov_r038;            // 0xF308_5110
    BND_CTRL_WOV_SYN_BND_WOV_R039_O22A0_T       bnd_wov_r039;            // 0xF308_5114
    BND_CTRL_WOV_SYN_BND_WOV_R040_O22A0_T       bnd_wov_r040;            // 0xF308_5118
    BND_CTRL_WOV_SYN_BND_WOV_R041_O22A0_T       bnd_wov_r041;            // 0xF308_511C
    BND_CTRL_WOV_SYN_BND_WOV_R042_O22A0_T       bnd_wov_r042;            // 0xF308_5120
    BND_CTRL_WOV_SYN_BND_WOV_R043_O22A0_T       bnd_wov_r043;            // 0xF308_5124
    BND_CTRL_WOV_SYN_BND_WOV_R044_O22A0_T       bnd_wov_r044;            // 0xF308_5128
    UINT32                             _rsvd_07[53];            // 0xF308_512C ~ 0xF308_51FC
    BND_CTRL_WOV_WOV_POR_R01_O22A0_T        wov_por_r01;             // 0xF308_5200
    BND_CTRL_WOV_WOV_POR_R02_O22A0_T        wov_por_r02;             // 0xF308_5204
    BND_CTRL_WOV_WOV_POR_R03_O22A0_T        wov_por_r03;             // 0xF308_5208
    BND_CTRL_WOV_WOV_POR_R04_O22A0_T        wov_por_r04;             // 0xF308_520C
    BND_CTRL_WOV_WOV_POR_R05_O22A0_T        wov_por_r05;             // 0xF308_5210
    BND_CTRL_WOV_SYN_BND_WOV_R045_O22A0_T       bnd_wov_r045;            // 0xF308_5214
    BND_CTRL_WOV_SYN_BND_WOV_R046_O22A0_T       bnd_wov_r046;            // 0xF308_5218
    BND_CTRL_WOV_SYN_BND_WOV_R047_O22A0_T       bnd_wov_r047;            // 0xF308_521C
    BND_CTRL_WOV_CRG_TOP_WOV_AON_R06_O22A0_T    crg_top_wov_aon_r06;    // 0xF308_5220
}BND_CTRL_WOV_REG_O22A0_T;
/* 43 regs */

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

#define BND_CTRL_WOV_SYN_BND_WOV_RXCLK_MD_R00_O22A0_T_OFF            (BASEADDRESS+0x0000)
#define BND_CTRL_WOV_SYN_BND_WOV_TX_LO_DRV_O22A0_T_OFF               (BASEADDRESS+0x0010)
#define BND_CTRL_WOV_SYN_BND_WOV_R06_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define BND_CTRL_WOV_SYN_BND_WOV_R07_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define BND_CTRL_WOV_SYN_BND_WOV_R08_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define BND_CTRL_WOV_SYN_BND_WOV_R09_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define BND_CTRL_WOV_SYN_BND_WOV_R10_O22A0_T_OFF                     (BASEADDRESS+0x002C)
#define BND_CTRL_WOV_SYN_BND_WOV_R11_O22A0_T_OFF                     (BASEADDRESS+0x0030)
#define BND_CTRL_WOV_SYN_BND_WOV_R12_O22A0_T_OFF                     (BASEADDRESS+0x0034)
#define BND_CTRL_WOV_SYN_BND_WOV_R13_O22A0_T_OFF                     (BASEADDRESS+0x0038)
#define BND_CTRL_WOV_SYN_BND_WOV_R14_O22A0_T_OFF                     (BASEADDRESS+0x003C)
#define BND_CTRL_WOV_SYN_BND_WOV_R15_O22A0_T_OFF                     (BASEADDRESS+0x0040)
#define BND_CTRL_WOV_APLL_FRPLL_SSCG_R00_O22A0_T_OFF             (BASEADDRESS+0x0060)
#define BND_CTRL_WOV_APLL_FRPLL_R00_O22A0_T_OFF                  (BASEADDRESS+0x0068)
#define BND_CTRL_WOV_APLL_FRPLL_R01_O22A0_T_OFF                  (BASEADDRESS+0x006C)
#define BND_CTRL_WOV_APLL_FRPLL_R02_O22A0_T_OFF                  (BASEADDRESS+0x0070)
#define BND_CTRL_WOV_APLL_FRPLL_R03_O22A0_T_OFF                  (BASEADDRESS+0x0074)
#define BND_CTRL_WOV_SYN_BND_WOV_R024_O22A0_T_OFF                    (BASEADDRESS+0x0078)
#define BND_CTRL_WOV_SYN_BND_WOV_R026_O22A0_T_OFF                    (BASEADDRESS+0x0084)
#define BND_CTRL_WOV_SYN_BND_WOV_R029_O22A0_T_OFF                    (BASEADDRESS+0x0090)
#define BND_CTRL_WOV_SYN_BND_WOV_R030_O22A0_T_OFF                    (BASEADDRESS+0x0094)
#define BND_CTRL_WOV_SYN_BND_WOV_R031_O22A0_T_OFF                    (BASEADDRESS+0x0098)
#define BND_CTRL_WOV_SYN_BND_WOV_R032_O22A0_T_OFF                    (BASEADDRESS+0x009C)
#define BND_CTRL_WOV_SYN_BND_WOV_R034_O22A0_T_OFF                    (BASEADDRESS+0x0100)
#define BND_CTRL_WOV_SYN_BND_WOV_R035_O22A0_T_OFF                    (BASEADDRESS+0x0104)
#define BND_CTRL_WOV_SYN_BND_WOV_R036_O22A0_T_OFF                    (BASEADDRESS+0x0108)
#define BND_CTRL_WOV_SYN_BND_WOV_R037_O22A0_T_OFF                    (BASEADDRESS+0x010C)
#define BND_CTRL_WOV_SYN_BND_WOV_R038_O22A0_T_OFF                    (BASEADDRESS+0x0110)
#define BND_CTRL_WOV_SYN_BND_WOV_R039_O22A0_T_OFF                    (BASEADDRESS+0x0114)
#define BND_CTRL_WOV_SYN_BND_WOV_R040_O22A0_T_OFF                    (BASEADDRESS+0x0118)
#define BND_CTRL_WOV_SYN_BND_WOV_R041_O22A0_T_OFF                    (BASEADDRESS+0x011C)
#define BND_CTRL_WOV_SYN_BND_WOV_R042_O22A0_T_OFF                    (BASEADDRESS+0x0120)
#define BND_CTRL_WOV_SYN_BND_WOV_R043_O22A0_T_OFF                    (BASEADDRESS+0x0124)
#define BND_CTRL_WOV_SYN_BND_WOV_R044_O22A0_T_OFF                    (BASEADDRESS+0x0128)
#define BND_CTRL_WOV_WOV_POR_R01_O22A0_T_OFF                     (BASEADDRESS+0x0200)
#define BND_CTRL_WOV_WOV_POR_R02_O22A0_T_OFF                     (BASEADDRESS+0x0204)
#define BND_CTRL_WOV_WOV_POR_R03_O22A0_T_OFF                     (BASEADDRESS+0x0208)
#define BND_CTRL_WOV_WOV_POR_R04_O22A0_T_OFF                     (BASEADDRESS+0x020C)
#define BND_CTRL_WOV_WOV_POR_R05_O22A0_T_OFF                     (BASEADDRESS+0x0210)
#define BND_CTRL_WOV_SYN_BND_WOV_R045_O22A0_T_OFF                    (BASEADDRESS+0x0214)
#define BND_CTRL_WOV_SYN_BND_WOV_R046_O22A0_T_OFF                    (BASEADDRESS+0x0218)
#define BND_CTRL_WOV_SYN_BND_WOV_R047_O22A0_T_OFF                    (BASEADDRESS+0x021C)
#define BND_CTRL_WOV_CRG_TOP_WOV_AON_R06_O22A0_T_OFF             (BASEADDRESS+0x0220)

/*-----------------------------------------------------------------------------------------
    0xF308_5000    bnd_wov_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_m1_pdb:  1;    //      0
    UINT32 resvd00            :  2;    //   2: 1 reserved
    UINT32 reg_rxclkdrv_m1_smv:  1;    //      3
    UINT32 resvd01            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5010    bnd_wov_tx_lo_drv ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tx_lo_drv_ephy_shutdown_pdb: 1;    //  0
    UINT32 reg_tx_lo_drv_ephy_shutdown_ck_div: 1;    //  1
    UINT32 reg_tx_lo_drv_nisol_ephy_pdb: 1;    //  2
    UINT32 reg_tx_lo_drv_nisol_ephy_ck_div: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_TX_LO_DRV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_501C    bnd_wov_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wov_aiopllss_cih: 4;    //   3: 0
    UINT32 reg_wov_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_wov_aiopllss_fine_div: 1;    //  7
    UINT32 reg_wov_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_wov_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_wov_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_wov_aiopllss_m :  6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5020    bnd_wov_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wov_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_wov_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_wov_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_wov_aiopllss_dss: 1;    //     23
    UINT32 reg_wov_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_WOV_SYN_BND_WOV_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5024    bnd_wov_r08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wov_aiopllss_freq_update: 1;    //  0
    UINT32 reg_wov_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_wov_aiopllss_lock: 1;    //     4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_wov_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_wov_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_wov_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_wov_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5028    bnd_wov_r09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_micom_pdb :  1;    //      0
    UINT32 resvd00            : 11;    //  11: 1 reserved
    UINT32 reg_sadc_micom_pc  :  3;    //  14:12
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_sadc_micom_cc  :  3;    //  18:16
    UINT32 resvd02            :  1;    //     19 reserved
    UINT32 reg_sadc_micom_isel:  3;    //  22:20
    UINT32 resvd03            :  9;    //  31:23 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_502C    bnd_wov_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_micom_lpf_soc: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sadc_micom_lpf_chsel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_sadc_micom_lpf_start: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_sadc_micom_lpf_dsel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_sadc_micom_lpf_mode: 3;    //  18:16
    UINT32 resvd04            :  5;    //  23:19 reserved
    UINT32 reg_sadc_micom_lpf_eoc_inv: 1;    //  24
    UINT32 resvd05            :  3;    //  27:25 reserved
    UINT32 reg_sadc_micom_lpf_manual: 1;    //  28
    UINT32 resvd06            :  3;    //  31:29 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5030    bnd_wov_r11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_micom_lpf_data_clear: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5034    bnd_wov_r12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_lpf_data012   : 32;    //  31: 0
    };
}BND_CTRL_WOV_SYN_BND_WOV_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5038    bnd_wov_r13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_lpf_data345   : 32;    //  31: 0
    };
}BND_CTRL_WOV_SYN_BND_WOV_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_503C    bnd_wov_r14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_micom_lpf_debug_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5040    bnd_wov_r15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_lpf_debug_data:  8;    //   7: 0
    UINT32 resvd00            : 20;    //  27: 8 reserved
    UINT32 sadc_micon_lpf_adc_done: 1;    //  28
    UINT32 resvd01            :  3;    //  31:29 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5060    apll_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_updn_max: 8;    //  7:0
    UINT32 reg_apll_frpll_mod_speed_max: 9;    //  16:8
    UINT32 resvd00            :  7;    //  23:17 reserved
    UINT32 reg_apll_frpll_lock_cont: 1;    //  24
    UINT32 reg_apll_frpll_dss :  1;    //     25
    UINT32 resvd01            :  5;    //  30:26 reserved
    UINT32 reg_soft_reset_frpll_sscg: 1;    //  31
    };
}BND_CTRL_WOV_APLL_FRPLL_SSCG_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5068    apll_frpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_apll_frpll_in_divsel: 1;    //  1
    UINT32 reg_apll_frpll_lpf_on: 1;    //     2
    UINT32 reg_apll_frpll_fout2_en: 1;    //   3
    UINT32 reg_apll_frpll_wakeup_bypass: 1;    //  4
    UINT32 reg_apll_frpll_divint: 9;    //  13:5
    UINT32 resvd01            :  1;    //     14 reserved
    UINT32 reg_apll_frpll_dsmon: 1;    //     15
    UINT32 reg_apll_frpll_auto_freq: 1;    //  16
    UINT32 reg_apll_frpll_dsm_limit: 1;    //  17
    UINT32 reg_apll_frpll_fin_sel: 1;    //   18
    UINT32 reg_apll_frpll_icp :  4;    //  22:19
    UINT32 reg_apll_frpll_out_div: 9;    //  31:23
    };
}BND_CTRL_WOV_APLL_FRPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_506C    apll_frpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_fout_en: 1;    //    0
    UINT32 reg_apll_frpll_syncon: 1;    //     1
    UINT32 reg_apll_frpll_m   :  6;    //   7: 2
    UINT32 reg_apll_frpll_fcw : 24;    //  31: 8
    };
}BND_CTRL_WOV_APLL_FRPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5070    apll_frpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_lock:  1;    //      0
    UINT32 resvd00            : 22;    //  22: 1 reserved
    UINT32 reg_apll_frpll_frequp: 1;    //    23
    UINT32 reg_apll_frpll_a   :  6;    //  29:24
    UINT32 reg_apll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_apll_frpll_icp_g: 1;    //     31
    };
}BND_CTRL_WOV_APLL_FRPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5074    apll_frpll_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_out2_div: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_apll_frpll_out3_div: 9;    //  20:12
    UINT32 resvd01            : 11;    //  31:21 reserved
    };
}BND_CTRL_WOV_APLL_FRPLL_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5078    bnd_wov_r024 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_monitor_sel_3to0: 3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_monitor_sel_7to4: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_monitor_shift1 :  1;    //      8
    UINT32 reg_monitor_shift2 :  1;    //      9
    UINT32 reg_monitor_shift3 :  1;    //     10
    UINT32 reg_monitor_shift4 :  1;    //     11
    UINT32 reg_monitor_shift5 :  1;    //     12
    UINT32 reg_monitor_shift6 :  1;    //     13
    UINT32 reg_monitor_shift7 :  1;    //     14
    UINT32 resvd02            : 17;    //  31:15 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R024_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5084    bnd_wov_r026 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 aud_apll_fcw       : 24;    //  23: 0
    UINT32 reg_apll_fcw_mux_sel: 2;    //  25:24
    UINT32 resvd00            :  6;    //  31:26 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R026_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5090    bnd_wov_r029 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cec_gf_en      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R029_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5094    bnd_wov_r030 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 16;    //  15: 0 reserved
    UINT32 reg_vdec_aud_apb_31_16: 16;    //  31:16
    };
}BND_CTRL_WOV_SYN_BND_WOV_R030_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5098    bnd_wov_r031 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aec_aud_input_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R031_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_509C    bnd_wov_r032 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R032_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5100    bnd_wov_r034 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_jtag_sel0     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R034_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5104    bnd_wov_r035 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_jtag_sel1     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R035_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5108    bnd_wov_r036 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_jtag_sel2     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R036_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_510C    bnd_wov_r037 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_jtag_sel3     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R037_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5110    bnd_wov_r038 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_jtag_sel4     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R038_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5114    bnd_wov_r039 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_uart_sel0     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R039_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5118    bnd_wov_r040 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_uart_sel1     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R040_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_511C    bnd_wov_r041 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_uart_sel2     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R041_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5120    bnd_wov_r042 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_uart_sel3     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R042_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5124    bnd_wov_r043 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 main_uart_sel4     :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R043_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5128    bnd_wov_r044 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_araddr_s2_aud  :  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_awaddr_s2_aud  :  2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_araddr_s1_aud  :  2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_awaddr_s1_aud  :  2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R044_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5200    wov_por_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_m12wov   :  1;    //      0
    UINT32 reg_nisol_top2m1   :  1;    //      1
    UINT32 reg_nisol_ephy     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_WOV_WOV_POR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5204    wov_por_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_frpll_aud_pdb_ctrl: 1;    //    0
    UINT32 reg_aiopll_wov_pdb_ctrl: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_WOV_WOV_POR_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5208    wov_por_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gating_m1_pll_n:  1;    //      0
    UINT32 reg_gating_cpuav_i_m1: 1;    //     1
    UINT32 reg_gating_cpuav_i_d100_m1: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_gating_aiopll_400_clk_out: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_WOV_WOV_POR_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_520C    wov_por_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_m1pll_pdb_ctrl :  1;    //      0
    UINT32 reg_swrst_cpuav_i_d100_m1: 1;    //  1
    UINT32 reg_swrst_cpuav_i_m1: 1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_WOV_WOV_POR_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5210    wov_por_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_wov      :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_WOV_POR_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5214    bnd_wov_r045 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd2_pv0_wov_hub_flush_en: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_vd2_pv0_wov_hub_flush_done: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R045_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5218    bnd_wov_r046 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_edid_apb_bnd_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R046_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_521C    bnd_wov_r047 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_topapb_gate_en: 1;    //  0
    UINT32 reg_micom_to_m1_apb_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_WOV_SYN_BND_WOV_R047_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_5220    crg_top_wov_aon_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sw_reset_from_micom: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_WOV_CRG_TOP_WOV_AON_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOV_SYN_BND_WOV_RXCLK_MD_R00_O22A0_T    bnd_wov_rxclk_md_r00;    // 0xF308_5000
    UINT32                             _rsvd_00[3];             // 0xF308_5004 ~ 0xF308_500C
    BND_CTRL_WOV_SYN_BND_WOV_TX_LO_DRV_O22A0_T    bnd_wov_tx_lo_drv;     // 0xF308_5010
    UINT32                             _rsvd_01[2];             // 0xF308_5014 ~ 0xF308_5018
    BND_CTRL_WOV_SYN_BND_WOV_R06_O22A0_T        bnd_wov_r06;             // 0xF308_501C
    BND_CTRL_WOV_SYN_BND_WOV_R07_O22A0_T        bnd_wov_r07;             // 0xF308_5020
    BND_CTRL_WOV_SYN_BND_WOV_R08_O22A0_T        bnd_wov_r08;             // 0xF308_5024
    BND_CTRL_WOV_SYN_BND_WOV_R09_O22A0_T        bnd_wov_r09;             // 0xF308_5028
    BND_CTRL_WOV_SYN_BND_WOV_R10_O22A0_T        bnd_wov_r10;             // 0xF308_502C
    BND_CTRL_WOV_SYN_BND_WOV_R11_O22A0_T        bnd_wov_r11;             // 0xF308_5030
    BND_CTRL_WOV_SYN_BND_WOV_R12_O22A0_T        bnd_wov_r12;             // 0xF308_5034
    BND_CTRL_WOV_SYN_BND_WOV_R13_O22A0_T        bnd_wov_r13;             // 0xF308_5038
    BND_CTRL_WOV_SYN_BND_WOV_R14_O22A0_T        bnd_wov_r14;             // 0xF308_503C
    BND_CTRL_WOV_SYN_BND_WOV_R15_O22A0_T        bnd_wov_r15;             // 0xF308_5040
    UINT32                             _rsvd_02[7];             // 0xF308_5044 ~ 0xF308_505C
    BND_CTRL_WOV_APLL_FRPLL_SSCG_R00_O22A0_T    apll_frpll_sscg_r00;    // 0xF308_5060
    UINT32                             _rsvd_03[1];             // 0xF308_5064
    BND_CTRL_WOV_APLL_FRPLL_R00_O22A0_T     apll_frpll_r00;          // 0xF308_5068
    BND_CTRL_WOV_APLL_FRPLL_R01_O22A0_T     apll_frpll_r01;          // 0xF308_506C
    BND_CTRL_WOV_APLL_FRPLL_R02_O22A0_T     apll_frpll_r02;          // 0xF308_5070
    BND_CTRL_WOV_APLL_FRPLL_R03_O22A0_T     apll_frpll_r03;          // 0xF308_5074
    BND_CTRL_WOV_SYN_BND_WOV_R024_O22A0_T       bnd_wov_r024;            // 0xF308_5078
    UINT32                             _rsvd_04[2];             // 0xF308_507C ~ 0xF308_5080
    BND_CTRL_WOV_SYN_BND_WOV_R026_O22A0_T       bnd_wov_r026;            // 0xF308_5084
    UINT32                             _rsvd_05[2];             // 0xF308_5088 ~ 0xF308_508C
    BND_CTRL_WOV_SYN_BND_WOV_R029_O22A0_T       bnd_wov_r029;            // 0xF308_5090
    BND_CTRL_WOV_SYN_BND_WOV_R030_O22A0_T       bnd_wov_r030;            // 0xF308_5094
    BND_CTRL_WOV_SYN_BND_WOV_R031_O22A0_T       bnd_wov_r031;            // 0xF308_5098
    BND_CTRL_WOV_SYN_BND_WOV_R032_O22A0_T       bnd_wov_r032;            // 0xF308_509C
    UINT32                             _rsvd_06[24];            // 0xF308_50A0 ~ 0xF308_50FC
    BND_CTRL_WOV_SYN_BND_WOV_R034_O22A0_T       bnd_wov_r034;            // 0xF308_5100
    BND_CTRL_WOV_SYN_BND_WOV_R035_O22A0_T       bnd_wov_r035;            // 0xF308_5104
    BND_CTRL_WOV_SYN_BND_WOV_R036_O22A0_T       bnd_wov_r036;            // 0xF308_5108
    BND_CTRL_WOV_SYN_BND_WOV_R037_O22A0_T       bnd_wov_r037;            // 0xF308_510C
    BND_CTRL_WOV_SYN_BND_WOV_R038_O22A0_T       bnd_wov_r038;            // 0xF308_5110
    BND_CTRL_WOV_SYN_BND_WOV_R039_O22A0_T       bnd_wov_r039;            // 0xF308_5114
    BND_CTRL_WOV_SYN_BND_WOV_R040_O22A0_T       bnd_wov_r040;            // 0xF308_5118
    BND_CTRL_WOV_SYN_BND_WOV_R041_O22A0_T       bnd_wov_r041;            // 0xF308_511C
    BND_CTRL_WOV_SYN_BND_WOV_R042_O22A0_T       bnd_wov_r042;            // 0xF308_5120
    BND_CTRL_WOV_SYN_BND_WOV_R043_O22A0_T       bnd_wov_r043;            // 0xF308_5124
    BND_CTRL_WOV_SYN_BND_WOV_R044_O22A0_T       bnd_wov_r044;            // 0xF308_5128
    UINT32                             _rsvd_07[53];            // 0xF308_512C ~ 0xF308_51FC
    BND_CTRL_WOV_WOV_POR_R01_O22A0_T        wov_por_r01;             // 0xF308_5200
    BND_CTRL_WOV_WOV_POR_R02_O22A0_T        wov_por_r02;             // 0xF308_5204
    BND_CTRL_WOV_WOV_POR_R03_O22A0_T        wov_por_r03;             // 0xF308_5208
    BND_CTRL_WOV_WOV_POR_R04_O22A0_T        wov_por_r04;             // 0xF308_520C
    BND_CTRL_WOV_WOV_POR_R05_O22A0_T        wov_por_r05;             // 0xF308_5210
    BND_CTRL_WOV_SYN_BND_WOV_R045_O22A0_T       bnd_wov_r045;            // 0xF308_5214
    BND_CTRL_WOV_SYN_BND_WOV_R046_O22A0_T       bnd_wov_r046;            // 0xF308_5218
    BND_CTRL_WOV_SYN_BND_WOV_R047_O22A0_T       bnd_wov_r047;            // 0xF308_521C
    BND_CTRL_WOV_CRG_TOP_WOV_AON_R06_O22A0_T    crg_top_wov_aon_r06;    // 0xF308_5220
}BND_CTRL_WOV_REG_O22A0_T;
/* 43 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_WOV_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

