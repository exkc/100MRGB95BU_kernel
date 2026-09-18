#ifndef _CTOP_SYN_EDID_E60A0_REG_H_
#define _CTOP_SYN_EDID_E60A0_REG_H_

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
    0xC98A_2400    syn_edid000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_wr_done          :  1,    //      0
                              :  2,    //   2: 1 reserved
    reg_hpd_out_prt4_edid     :  1,    //      3
    reg_hpd_out_prt3_edid     :  1,    //      4
    reg_hpd_out_prt2_edid     :  1,    //      5
    reg_hpd_out_prt1_edid     :  1,    //      6
                              :  1,    //      7 reserved
    reg_hpd_out_prt4          :  1,    //      8
    reg_hpd_out_prt3          :  1,    //      9
    reg_hpd_out_prt2          :  1,    //     10
    reg_hpd_out_prt1          :  1,    //     11
                              :  1,    //     12 reserved
    reg_hpd_sel               :  2,    //  14:13
                              :  1,    //     15 reserved
    reg_edid_prt1_hpd_oen     :  1,    //     16
    reg_edid_prt2_hpd_oen     :  1,    //     17
    reg_edid_prt3_hpd_oen     :  1,    //     18
    reg_edid_prt4_hpd_oen     :  1,    //     19
                              : 12;    //  31:20 reserved
}CTOP_EDID_SYN_EDID000_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2404    syn_edid001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}CTOP_EDID_SYN_EDID001_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2408    syn_edid002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_edid       :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_EDID_SYN_EDID002_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_240C    syn_edid003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_hdmi_4_scl__st        :  1,    //      0
    pad_hdmi_4_scl__pd        :  1,    //      1
    pad_hdmi_4_scl__pu        :  1,    //      2
    pad_hdmi_4_scl__ds3       :  1,    //      3
    pad_hdmi_4_scl__ds2       :  1,    //      4
    pad_hdmi_4_scl__ds1       :  1,    //      5
                              :  2,    //   7: 6 reserved
    pad_hdmi_4_scl__ds0       :  1,    //      8
    pad_hdmi_3_scl__st        :  1,    //      9
    pad_hdmi_3_scl__pd        :  1,    //     10
    pad_hdmi_3_scl__pu        :  1,    //     11
    pad_hdmi_3_scl__ds3       :  1,    //     12
    pad_hdmi_3_scl__ds2       :  1,    //     13
    pad_hdmi_3_scl__ds1       :  1,    //     14
    pad_hdmi_3_scl__ds0       :  1,    //     15
    pad_hdmi_2_scl__st        :  1,    //     16
    pad_hdmi_2_scl__pd        :  1,    //     17
    pad_hdmi_2_scl__pu        :  1,    //     18
    pad_hdmi_2_scl__ds3       :  1,    //     19
    pad_hdmi_2_scl__ds2       :  1,    //     20
    pad_hdmi_2_scl__ds1       :  1,    //     21
    pad_hdmi_2_scl__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    pad_hdmi_1_scl__st        :  1,    //     24
    pad_hdmi_1_scl__pd        :  1,    //     25
    pad_hdmi_1_scl__pu        :  1,    //     26
    pad_hdmi_1_scl__ds3       :  1,    //     27
    pad_hdmi_1_scl__ds2       :  1,    //     28
    pad_hdmi_1_scl__ds1       :  1,    //     29
    pad_hdmi_1_scl__ds0       :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_EDID_SYN_EDID003_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2430    syn_edid004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_hdmi_4_sda__st        :  1,    //      0
    pad_hdmi_4_sda__pd        :  1,    //      1
    pad_hdmi_4_sda__pu        :  1,    //      2
    pad_hdmi_4_sda__ds3       :  1,    //      3
    pad_hdmi_4_sda__ds2       :  1,    //      4
    pad_hdmi_4_sda__ds1       :  1,    //      5
                              :  2,    //   7: 6 reserved
    pad_hdmi_4_sda__ds0       :  1,    //      8
    pad_hdmi_3_sda__st        :  1,    //      9
    pad_hdmi_3_sda__pd        :  1,    //     10
    pad_hdmi_3_sda__pu        :  1,    //     11
    pad_hdmi_3_sda__ds3       :  1,    //     12
    pad_hdmi_3_sda__ds2       :  1,    //     13
    pad_hdmi_3_sda__ds1       :  1,    //     14
    pad_hdmi_3_sda__ds0       :  1,    //     15
    pad_hdmi_2_sda__st        :  1,    //     16
    pad_hdmi_2_sda__pd        :  1,    //     17
    pad_hdmi_2_sda__pu        :  1,    //     18
    pad_hdmi_2_sda__ds3       :  1,    //     19
    pad_hdmi_2_sda__ds2       :  1,    //     20
    pad_hdmi_2_sda__ds1       :  1,    //     21
    pad_hdmi_2_sda__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    pad_hdmi_1_sda__st        :  1,    //     24
    pad_hdmi_1_sda__pd        :  1,    //     25
    pad_hdmi_1_sda__pu        :  1,    //     26
    pad_hdmi_1_sda__ds3       :  1,    //     27
    pad_hdmi_1_sda__ds2       :  1,    //     28
    pad_hdmi_1_sda__ds1       :  1,    //     29
    pad_hdmi_1_sda__ds0       :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_EDID_SYN_EDID004_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2434    syn_edid005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_hdmi_4_5v_in__st      :  1,    //      0
    pad_hdmi_4_5v_in__pd      :  1,    //      1
    pad_hdmi_4_5v_in__pu      :  1,    //      2
    pad_hdmi_4_5v_in__ds3     :  1,    //      3
    pad_hdmi_4_5v_in__ds2     :  1,    //      4
    pad_hdmi_4_5v_in__ds1     :  1,    //      5
                              :  2,    //   7: 6 reserved
    pad_hdmi_4_5v_in__ds0     :  1,    //      8
    pad_hdmi_3_5v_in__st      :  1,    //      9
    pad_hdmi_3_5v_in__pd      :  1,    //     10
    pad_hdmi_3_5v_in__pu      :  1,    //     11
    pad_hdmi_3_5v_in__ds3     :  1,    //     12
    pad_hdmi_3_5v_in__ds2     :  1,    //     13
    pad_hdmi_3_5v_in__ds1     :  1,    //     14
    pad_hdmi_3_5v_in__ds0     :  1,    //     15
    pad_hdmi_2_5v_in__st      :  1,    //     16
    pad_hdmi_2_5v_in__pd      :  1,    //     17
    pad_hdmi_2_5v_in__pu      :  1,    //     18
    pad_hdmi_2_5v_in__ds3     :  1,    //     19
    pad_hdmi_2_5v_in__ds2     :  1,    //     20
    pad_hdmi_2_5v_in__ds1     :  1,    //     21
    pad_hdmi_2_5v_in__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    pad_hdmi_1_5v_in__st      :  1,    //     24
    pad_hdmi_1_5v_in__pd      :  1,    //     25
    pad_hdmi_1_5v_in__pu      :  1,    //     26
    pad_hdmi_1_5v_in__ds3     :  1,    //     27
    pad_hdmi_1_5v_in__ds2     :  1,    //     28
    pad_hdmi_1_5v_in__ds1     :  1,    //     29
    pad_hdmi_1_5v_in__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_EDID_SYN_EDID005_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2438    syn_edid006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_hdmi_4_hpd__st        :  1,    //      0
    pad_hdmi_4_hpd__pd        :  1,    //      1
    pad_hdmi_4_hpd__pu        :  1,    //      2
    pad_hdmi_4_hpd__ds3       :  1,    //      3
    pad_hdmi_4_hpd__ds2       :  1,    //      4
    pad_hdmi_4_hpd__ds1       :  1,    //      5
                              :  2,    //   7: 6 reserved
    pad_hdmi_4_hpd__ds0       :  1,    //      8
    pad_hdmi_3_hpd__st        :  1,    //      9
    pad_hdmi_3_hpd__pd        :  1,    //     10
    pad_hdmi_3_hpd__pu        :  1,    //     11
    pad_hdmi_3_hpd__ds3       :  1,    //     12
    pad_hdmi_3_hpd__ds2       :  1,    //     13
    pad_hdmi_3_hpd__ds1       :  1,    //     14
    pad_hdmi_3_hpd__ds0       :  1,    //     15
    pad_hdmi_2_hpd__st        :  1,    //     16
    pad_hdmi_2_hpd__pd        :  1,    //     17
    pad_hdmi_2_hpd__pu        :  1,    //     18
    pad_hdmi_2_hpd__ds3       :  1,    //     19
    pad_hdmi_2_hpd__ds2       :  1,    //     20
    pad_hdmi_2_hpd__ds1       :  1,    //     21
    pad_hdmi_2_hpd__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    pad_hdmi_1_hpd__st        :  1,    //     24
    pad_hdmi_1_hpd__pd        :  1,    //     25
    pad_hdmi_1_hpd__pu        :  1,    //     26
    pad_hdmi_1_hpd__ds3       :  1,    //     27
    pad_hdmi_1_hpd__ds2       :  1,    //     28
    pad_hdmi_1_hpd__ds1       :  1,    //     29
    pad_hdmi_1_hpd__ds0       :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_EDID_SYN_EDID006_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_243C    syn_edid007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_xin__rd1              :  1,    //      0
    pad_xin__rd0              :  1,    //      1
    pad_xin__ref1             :  1,    //      2
    pad_xin__ref0             :  1,    //      3
    pad_xin__ds3              :  1,    //      4
    pad_xin__ds2              :  1,    //      5
    pad_xin__ds1              :  1,    //      6
    pad_xin__ds0              :  1,    //      7
                              :  8,    //  15: 8 reserved
    pad_edid_nisol__st        :  1,    //     16
                              :  2,    //  18:17 reserved
    pad_edid_nisol__ds3       :  1,    //     19
    pad_edid_nisol__ds2       :  1,    //     20
    pad_edid_nisol__ds1       :  1,    //     21
    pad_edid_nisol__ds0       :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_EDID_SYN_EDID007_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2440    syn_edid008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_sda_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_2_scl_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_2_hpd_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_2_5v_in_mux_sel: 4,    //  15:12
    reg_pad_hdmi_1_sda_mux_sel:  4,    //  19:16
    reg_pad_hdmi_1_scl_mux_sel:  4,    //  23:20
    reg_pad_hdmi_1_hpd_mux_sel:  4,    //  27:24
    reg_pad_hdmi_1_5v_in_mux_sel: 4;    //  31:28
}CTOP_EDID_SYN_EDID008_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2444    syn_edid009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_sda_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_4_scl_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_4_hpd_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_4_5v_in_mux_sel: 4,    //  15:12
    reg_pad_hdmi_3_sda_mux_sel:  4,    //  19:16
    reg_pad_hdmi_3_scl_mux_sel:  4,    //  23:20
    reg_pad_hdmi_3_hpd_mux_sel:  4,    //  27:24
    reg_pad_hdmi_3_5v_in_mux_sel: 4;    //  31:28
}CTOP_EDID_SYN_EDID009_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2448    frpll00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_earc_frpll_in_divsel  :  1,    //      1
    reg_earc_frpll_lpf_on     :  1,    //      2
    reg_earc_frpll_fout2_en   :  1,    //      3
    reg_earc_frpll_wakeup_bypass: 1,    //     4
    reg_earc_frpll_divint     :  9,    //  13: 5
    reg_earc_frpll_pdb        :  1,    //     14
    reg_earc_frpll_dsmon      :  1,    //     15
    reg_earc_frpll_auto_freq  :  1,    //     16
    reg_earc_frpll_dsm_limit  :  1,    //     17
    reg_earc_frpll_fin_sel    :  1,    //     18
    reg_earc_frpll_icp        :  4,    //  22:19
    reg_earc_frpll_out_div    :  9;    //  31:23
}CTOP_EDID_FRPLL00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_244C    frpll01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_fout_en    :  1,    //      0
    reg_earc_frpll_syncon     :  1,    //      1
    reg_earc_frpll_m          :  6,    //   7: 2
    reg_earc_frpll_fcw        : 24;    //  31: 8
}CTOP_EDID_FRPLL01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2450    frpll02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_pll_fcw_mux_sel  :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}CTOP_EDID_FRPLL02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2454    frpll03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_lock       :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_earc_frpll_frequp     :  1,    //     23
    reg_earc_frpll_a          :  6,    //  29:24
    reg_earc_frpll_in_divrstb :  1,    //     30
    reg_earc_frpll_icp_g      :  1;    //     31
}CTOP_EDID_FRPLL03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2458    frpll04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_EDID_FRPLL04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_245C    txclkdrv0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_bot_icon     :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_txclkdrv_top_icon     :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}CTOP_EDID_TXCLKDRV0_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2460    txclkdrv1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_bot_pdb      :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_EDID_TXCLKDRV1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2464    sxtal_out ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_sxtal_out__st         :  1,    //      0
    pad_sxtal_out__pd         :  1,    //      1
    pad_sxtal_out__pu         :  1,    //      2
    pad_sxtal_out__ds3        :  1,    //      3
    pad_sxtal_out__ds2        :  1,    //      4
    pad_sxtal_out__ds1        :  1,    //      5
    pad_sxtal_out__ds0        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sxtal_out_mux_sel :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}CTOP_EDID_SXTAL_OUT_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2468    dpm_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_en         :  1,    //      0
    reg_phy_mon_all_ch        :  1,    //      1
    reg_phy_low_vsen          :  1,    //      2
    reg_phy_dpm_odt           :  1,    //      3
    reg_phy_tx_det_disable    :  4,    //   7: 4
    reg_phy_tx_det_bypass_mode:  4,    //  11: 8
                              :  4,    //  15:12 reserved
    reg_use_pad_for_dpm_tx_det_intr: 1,    //  16
                              : 15;    //  31:17 reserved
}CTOP_EDID_DPM_0_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_246C    dpm_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy1_tx_det_out       :  1,    //      0
    reg_phy2_tx_det_out       :  1,    //      1
    reg_phy3_tx_det_out       :  1,    //      2
    reg_phy4_tx_det_out       :  1,    //      3
    reg_dpm_tx_det_intr_status:  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_EDID_DPM_1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC98A_2470    tpi_data3_ext1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pad_tpi_data3_ext1__st    :  1,    //      0
    pad_tpi_data3_ext1__pd    :  1,    //      1
    pad_tpi_data3_ext1__pu    :  1,    //      2
    pad_tpi_data3_ext1__ds3   :  1,    //      3
    pad_tpi_data3_ext1__ds2   :  1,    //      4
    pad_tpi_data3_ext1__ds1   :  1,    //      5
    pad_tpi_data3_ext1__ds0   :  1,    //      6
    pad_tpi_data3_ext1__ie    :  1,    //      7
                              : 24;    //   31:8 reserved
}CTOP_EDID_TPI_DATA3_EXT1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_EDID_SYN_EDID000_E60_A0_T           syn_edid000              ;         // 0xC98A_2400
    CTOP_EDID_SYN_EDID001_E60_A0_T           syn_edid001              ;         // 0xC98A_2404
    CTOP_EDID_SYN_EDID002_E60_A0_T           syn_edid002              ;         // 0xC98A_2408
    CTOP_EDID_SYN_EDID003_E60_A0_T           syn_edid003              ;         // 0xC98A_240C
UINT32                                                 _rsvd_00[   8] ;         // 0xC98A_2410 ~ 0xC98A_242C
    CTOP_EDID_SYN_EDID004_E60_A0_T           syn_edid004              ;         // 0xC98A_2430
    CTOP_EDID_SYN_EDID005_E60_A0_T           syn_edid005              ;         // 0xC98A_2434
    CTOP_EDID_SYN_EDID006_E60_A0_T           syn_edid006              ;         // 0xC98A_2438
    CTOP_EDID_SYN_EDID007_E60_A0_T           syn_edid007              ;         // 0xC98A_243C
    CTOP_EDID_SYN_EDID008_E60_A0_T           syn_edid008              ;         // 0xC98A_2440
    CTOP_EDID_SYN_EDID009_E60_A0_T           syn_edid009              ;         // 0xC98A_2444
    CTOP_EDID_FRPLL00_E60_A0_T               frpll00                  ;         // 0xC98A_2448
    CTOP_EDID_FRPLL01_E60_A0_T               frpll01                  ;         // 0xC98A_244C
    CTOP_EDID_FRPLL02_E60_A0_T               frpll02                  ;         // 0xC98A_2450
    CTOP_EDID_FRPLL03_E60_A0_T               frpll03                  ;         // 0xC98A_2454
    CTOP_EDID_FRPLL04_E60_A0_T               frpll04                  ;         // 0xC98A_2458
    CTOP_EDID_TXCLKDRV0_E60_A0_T             txclkdrv0                ;         // 0xC98A_245C
    CTOP_EDID_TXCLKDRV1_E60_A0_T             txclkdrv1                ;         // 0xC98A_2460
    CTOP_EDID_SXTAL_OUT_E60_A0_T             sxtal_out                ;         // 0xC98A_2464
    CTOP_EDID_DPM_0_E60_A0_T                 dpm_0                    ;         // 0xC98A_2468
    CTOP_EDID_DPM_1_E60_A0_T                 dpm_1                    ;         // 0xC98A_246C
    CTOP_EDID_TPI_DATA3_EXT1_E60_A0_T        tpi_data3_ext1           ;         // 0xC98A_2470
} CTOP_SYN_EDID_REG_E60_A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_EDID_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191216.xlsm'  2019.12.17  KST by LGSiCRDV V3.0B*/

