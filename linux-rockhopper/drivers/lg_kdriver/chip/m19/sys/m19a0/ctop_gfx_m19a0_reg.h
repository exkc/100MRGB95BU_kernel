#ifndef _CTOP_GFX_M19A0_REG_H_
#define _CTOP_GFX_M19A0_REG_H_

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
    0xC9C1_0400    ctop_gfx_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    m0pll_fine_div            :  1,    //      1
    m0pll_dss                 :  1,    //      2
    m0pll_accuracy            :  2,    //   4: 3
    m0pll_updn_max            :  7,    //  11: 5
    m0pll_mod_freq            :  9,    //  20:12
    m0pll_m                   :  6,    //  26:21
                              :  1,    //     27 reserved
    m0pll_cih                 :  4;    //  31:28
}CTOP_CTRL_GFX_CTOP_GFX_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0404    ctop_gfx_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    m0pll_ofs_mode            :  1,    //      4
    m0pll_fout3_od            :  3,    //   7: 5
    m0pll_fout2_od            :  3,    //  10: 8
    m0pll_fout_od             :  2,    //  12:11
    m0pll_pre_fout3_div       :  3,    //  15:13
    m0pll_pre_fout2_div       :  3,    //  18:16
    m0pll_nsc                 :  4,    //  22:19
    m0pll_npc                 :  6,    //  28:23
    m0pll_fine_control        :  3;    //  31:29
}CTOP_CTRL_GFX_CTOP_GFX_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0408    ctop_gfx_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    m0pll_wakeup_bypass       :  1,    //     22
    m0pll_ddr_mode            :  1,    //     23
    m0pll_offset              :  8;    //  31:24
}CTOP_CTRL_GFX_CTOP_GFX_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_040C    ctop_gfx_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    m1pll_fine_div            :  1,    //      1
    m1pll_dss                 :  1,    //      2
    m1pll_accuracy            :  2,    //   4: 3
    m1pll_updn_max            :  7,    //  11: 5
    m1pll_mod_freq            :  9,    //  20:12
    m1pll_m                   :  6,    //  26:21
                              :  1,    //     27 reserved
    m1pll_cih                 :  4;    //  31:28
}CTOP_CTRL_GFX_CTOP_GFX_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0410    ctop_gfx_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    m1pll_ofs_mode            :  1,    //      4
    m1pll_fout3_od            :  3,    //   7: 5
    m1pll_fout2_od            :  3,    //  10: 8
    m1pll_fout_od             :  2,    //  12:11
    m1pll_pre_fout3_div       :  3,    //  15:13
    m1pll_pre_fout2_div       :  3,    //  18:16
    m1pll_nsc                 :  4,    //  22:19
    m1pll_npc                 :  6,    //  28:23
    m1pll_fine_control        :  3;    //  31:29
}CTOP_CTRL_GFX_CTOP_GFX_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0414    ctop_gfx_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    m1pll_wakeup_bypass       :  1,    //     22
    m1pll_ddr_mode            :  1,    //     23
    m1pll_offset              :  8;    //  31:24
}CTOP_CTRL_GFX_CTOP_GFX_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0418    ctop_gfx_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    codecpll_fine_div         :  1,    //      1
    codecpll_dss              :  1,    //      2
    codecpll_accuracy         :  2,    //   4: 3
    codecpll_updn_max         :  7,    //  11: 5
    codecpll_mod_freq         :  9,    //  20:12
    codecpll_m                :  6,    //  26:21
                              :  1,    //     27 reserved
    codecpll_cih              :  4;    //  31:28
}CTOP_CTRL_GFX_CTOP_GFX_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_041C    ctop_gfx_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    codecpll_ofs_mode         :  1,    //      4
    codecpll_fout3_od         :  3,    //   7: 5
    codecpll_fout2_od         :  3,    //  10: 8
    codecpll_fout_od          :  2,    //  12:11
    codecpll_pre_fout3_div    :  3,    //  15:13
    codecpll_pre_fout2_div    :  3,    //  18:16
    codecpll_nsc              :  4,    //  22:19
    codecpll_npc              :  6,    //  28:23
    codecpll_fine_control     :  3;    //  31:29
}CTOP_CTRL_GFX_CTOP_GFX_R07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0420    ctop_gfx_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    codecpll_wakeup_bypass    :  1,    //     22
    codecpll_ddr_mode         :  1,    //     23
    codecpll_offset           :  8;    //  31:24
}CTOP_CTRL_GFX_CTOP_GFX_R08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0424    ctop_gfx_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    corepll_fine_div          :  1,    //      1
    corepll_dss               :  1,    //      2
    corepll_accuracy          :  2,    //   4: 3
    corepll_updn_max          :  7,    //  11: 5
    corepll_mod_freq          :  9,    //  20:12
    corepll_m                 :  6,    //  26:21
                              :  1,    //     27 reserved
    corepll_cih               :  4;    //  31:28
}CTOP_CTRL_GFX_CTOP_GFX_R09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0428    ctop_gfx_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    corepll_ofs_mode          :  1,    //      4
    corepll_fout3_od          :  3,    //   7: 5
    corepll_fout2_od          :  3,    //  10: 8
    corepll_fout_od           :  2,    //  12:11
    corepll_pre_fout3_div     :  3,    //  15:13
    corepll_pre_fout2_div     :  3,    //  18:16
    corepll_nsc               :  4,    //  22:19
    corepll_npc               :  6,    //  28:23
    corepll_fine_control      :  3;    //  31:29
}CTOP_CTRL_GFX_CTOP_GFX_R10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_042C    ctop_gfx_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    corepll_wakeup_bypass     :  1,    //     22
    corepll_ddr_mode          :  1,    //     23
    corepll_offset            :  8;    //  31:24
}CTOP_CTRL_GFX_CTOP_GFX_R11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0430    ctop_gfx_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 17,    //  16: 0 reserved
    de_dco_g                  :  3,    //  19:17
    de_dco_lpf                :  2,    //  21:20
    de_dco_bias_sel           :  1,    //     22
    de_dco_romtest            :  1,    //     23
                              :  1,    //     24 reserved
    sdec_dco_g                :  3,    //  27:25
    sdec_dco_lpf              :  2,    //  29:28
    sdec_dco_bias_sel         :  1,    //     30
    sdec_dco_romtest          :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0438    ctop_gfx_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 23,    //  22: 0 reserved
    ddr1pll_pdb_ctrl          :  1,    //     23
    gpupll_pdb_ctrl           :  1,    //     24
    cpupll_pdb_ctrl           :  1,    //     25
    displl_pdb_ctrl           :  1,    //     26
    codecpll_pdb_ctrl         :  1,    //     27
    corepll_pdb_ctrl          :  1,    //     28
    ddr0pll_pdb_ctrl          :  1,    //     29
    sdec_dco_pdb_ctrl         :  1,    //     30
    de_dco_pdb_ctrl           :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0440    ctop_gfx_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    sc_ext_sel                :  3,    //   6: 4
    dco_ext_sel               :  1,    //      7
    f24_sel                   :  1,    //      8
    f27_18_sel                :  1,    //      9
                              : 22;    //  31:10 reserved
}CTOP_CTRL_GFX_CTOP_GFX_R16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0444    ctop_gfx_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pll_sel_gpu_ddr           :  1,    //      0
    pll_sel_emmc              :  2,    //   2: 1
                              :  1,    //      3 reserved
    pll_sel_gfx               :  2,    //   5: 4
    pll_sel_aud               :  2,    //   7: 6
    pll_sel_esm               :  2,    //   9: 8
                              :  4,    //  13:10 reserved
    pll_sel_core480           :  2,    //  15:14
    pll_sel_lbus              :  2,    //  17:16
    pll_sel_vdec528           :  2,    //  19:18
    pll_sel_m1                :  1,    //     20
    pll_sel_m0                :  1,    //     21
                              :  4,    //  25:22 reserved
    pll_sel_dco               :  2,    //  27:26
                              :  2,    //  29:28 reserved
    pll_sel_core              :  2;    //  31:30
}CTOP_CTRL_GFX_CTOP_GFX_R17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0448    ctop_gfx_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_vdec528       :  2,    //   1: 0
    reg_clk_sel_core480       :  2,    //   3: 2
    reg_clk_sel_gfx           :  2,    //   5: 4
    reg_clk_sel_aud           :  2,    //   7: 6
    reg_clk_sel_dco           :  2,    //   9: 8
    reg_clk_sel_esm           :  2,    //  11:10
    reg_clk_sel_emmc          :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_clk_sel_core          :  2,    //  17:16
    reg_clk_sel_lbus          :  2,    //  19:18
                              : 12;    //  31:20 reserved
}CTOP_CTRL_GFX_CTOP_GFX_R18_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_044C    ctop_gfx_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phase_sel_core        :  2,    //   1: 0
    reg_phase_sel_core480     :  2,    //   3: 2
    reg_phase_sel_core528     :  2,    //   5: 4
    reg_phase_sel_vdec528     :  2,    //   7: 6
                              : 24;    //   31:8 reserved
}CTOP_CTRL_GFX_CTOP_GFX_R19_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0450    ctop_gfx_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_core_p0_clk_gate_en   :  1,    //     24
    reg_core480_p0_clk_gate_en:  1,    //     25
    reg_core528_p0_clk_gate_en:  1,    //     26
    reg_vdec528_p0_clk_gate_en:  1,    //     27
    reg_core_ps_clk_gate_en   :  1,    //     28
    reg_core480_ps_clk_gate_en:  1,    //     29
    reg_core528_ps_clk_gate_en:  1,    //     30
    reg_vdec528_ps_clk_gate_en:  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R20_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0454    ctop_gfx_r21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    swrst_edid                :  1,    //      3
    swrst_demod               :  1,    //      4
    swrst_hdmi                :  1,    //      5
    swrst_venc                :  1,    //      6
                              :  1,    //      7 reserved
    swrst_vdec1               :  1,    //      8
    swrst_vdec0               :  1,    //      9
    swrst_usb                 :  1,    //     10
    swrst_te                  :  1,    //     11
                              : 10,    //  21:12 reserved
    swrst_m1                  :  1,    //     22
    swrst_m0                  :  1,    //     23
                              :  1,    //     24 reserved
    swrst_gfx                 :  1,    //     25
    swrst_lbus                :  1,    //     26
    swrst_gbus                :  1,    //     27
    swrst_emmc                :  1,    //     28
    swrst_dpe                 :  1,    //     29
    swrst_cpuperi             :  1,    //     30
    swrst_aud                 :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R21_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0458    ctop_gfx_r22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    swrst_edid_d100           :  1,    //      3
    swrst_demod_d100          :  1,    //      4
    swrst_hdmi_d100           :  1,    //      5
    swrst_venc_d100           :  1,    //      6
                              :  1,    //      7 reserved
    swrst_vdec1_d100          :  1,    //      8
    swrst_vdec0_d100          :  1,    //      9
    swrst_usb_d100            :  1,    //     10
    swrst_te_d100             :  1,    //     11
                              : 10,    //  21:12 reserved
    swrst_m1_d100             :  1,    //     22
    swrst_m0_d100             :  1,    //     23
                              :  1,    //     24 reserved
    swrst_gfx_d100            :  1,    //     25
    swrst_lbus_d100           :  1,    //     26
    swrst_gbus_d100           :  1,    //     27
    swrst_emmc_d100           :  1,    //     28
    swrst_dpe_d100            :  1,    //     29
    swrst_cpuperi_d100        :  1,    //     30
    swrst_aud_d100            :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R22_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_045C    ctop_gfx_r23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    swrst_disp_pqe_nd0_d100   :  1,    //      7
    swrst_disp_pqe_mcu_d100   :  1,    //      8
    swrst_disp_pqe_imx_d100   :  1,    //      9
    swrst_disp_pqe_gsc_d100   :  1,    //     10
                              :  1,    //     11 reserved
    swrst_disp_pqe_fmc_d100   :  1,    //     12
    swrst_disp_pqe_cvi_d100   :  1,    //     13
    swrst_disp_pqe_cco_d100   :  1,    //     14
    swrst_disp_dpe_d100       :  1,    //     15
                              :  7,    //  22:16 reserved
    swrst_disp_pqe_nd0        :  1,    //     23
    swrst_disp_pqe_mcu        :  1,    //     24
    swrst_disp_pqe_imx        :  1,    //     25
    swrst_disp_pqe_gsc        :  1,    //     26
                              :  1,    //     27 reserved
    swrst_disp_pqe_fmc        :  1,    //     28
    swrst_disp_pqe_cvi        :  1,    //     29
    swrst_disp_pqe_cco        :  1,    //     30
    swrst_disp_dpe            :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R23_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0460    ctop_gfx_r24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 15,    //  14: 0 reserved
    swrst_disp_pqe_nd1_d100   :  1,    //     15
    swrst_disp_pqe_gbm_d100   :  1,    //     16
    swrst_disp_pqe_nd1        :  1,    //     17
    swrst_disp_pqe_gbm        :  1,    //     18
    swrst_l528                :  1,    //     19
    swrst_l396                :  1,    //     20
    swrst_g396                :  1,    //     21
    swrst_gpu_d100            :  1,    //     22
    swrst_gpu                 :  1,    //     23
    swrst_gem_d100            :  1,    //     24
    swrst_gem                 :  1,    //     25
                              :  2,    //  27:26 reserved
    swrst_disp_pqe_me0_d100   :  1,    //     28
    swrst_disp_pqe_me0        :  1,    //     29
    swrst_disp_pqe_fms_d100   :  1,    //     30
    swrst_disp_pqe_fms        :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R24_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0464    ctop_gfx_r28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 28,    //  27: 0 reserved
    gpu_clk_sel               :  1,    //     28
    l528_sync_clk_sel         :  1,    //     29
    l396_sync_clk_sel         :  1,    //     30
    g396_sync_clk_sel         :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R28_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0468    ctop_gfx_r29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 26,    //  25: 0 reserved
    dcoin_clk_gate_en         :  2,    //  27:26
                              :  1,    //     28 reserved
    l528_sync_clk_gate_en     :  1,    //     29
    l396_sync_clk_gate_en     :  1,    //     30
    g396_sync_clk_gate_en     :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R29_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_046C    ctop_gfx_r30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 31,    //  30: 0 reserved
    sdec_pqe_dco_sel          :  1;    //     31
}CTOP_CTRL_GFX_CTOP_GFX_R30_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0470    ctop_gfx_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_check_enable          :  1,    //      0
                              : 15,    //  15: 1 reserved
    crg_int_clear             :  1,    //     16
                              :  3,    //  19:17 reserved
    crg_int_enable            :  1,    //     20
                              :  3,    //  23:21 reserved
    crg_check_period          :  8;    //  31:24
}CTOP_CTRL_GFX_CTOP_GFX_R31_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0474    rxclkdrv_ddr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_rxclkdrv_ddr_smv      :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_GFX_RXCLKDRV_DDR_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0478    txclkdrv_c4tx ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_c4tx_pdb     :  1,    //      0
    reg_txclkdrv_c4tx_icon    :  3,    //   3: 1
                              : 28;    //   31:4 reserved
}CTOP_CTRL_GFX_TXCLKDRV_C4TX_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_GFX_CTOP_GFX_R00_M19A0_T           ctop_gfx_r00             ;         // 0xC9C1_0400
CTOP_CTRL_GFX_CTOP_GFX_R01_M19A0_T           ctop_gfx_r01             ;         // 0xC9C1_0404
CTOP_CTRL_GFX_CTOP_GFX_R02_M19A0_T           ctop_gfx_r02             ;         // 0xC9C1_0408
CTOP_CTRL_GFX_CTOP_GFX_R03_M19A0_T           ctop_gfx_r03             ;         // 0xC9C1_040C
CTOP_CTRL_GFX_CTOP_GFX_R04_M19A0_T           ctop_gfx_r04             ;         // 0xC9C1_0410
CTOP_CTRL_GFX_CTOP_GFX_R05_M19A0_T           ctop_gfx_r05             ;         // 0xC9C1_0414
CTOP_CTRL_GFX_CTOP_GFX_R06_M19A0_T           ctop_gfx_r06             ;         // 0xC9C1_0418
CTOP_CTRL_GFX_CTOP_GFX_R07_M19A0_T           ctop_gfx_r07             ;         // 0xC9C1_041C
CTOP_CTRL_GFX_CTOP_GFX_R08_M19A0_T           ctop_gfx_r08             ;         // 0xC9C1_0420
CTOP_CTRL_GFX_CTOP_GFX_R09_M19A0_T           ctop_gfx_r09             ;         // 0xC9C1_0424
CTOP_CTRL_GFX_CTOP_GFX_R10_M19A0_T           ctop_gfx_r10             ;         // 0xC9C1_0428
CTOP_CTRL_GFX_CTOP_GFX_R11_M19A0_T           ctop_gfx_r11             ;         // 0xC9C1_042C
CTOP_CTRL_GFX_CTOP_GFX_R12_M19A0_T           ctop_gfx_r12             ;         // 0xC9C1_0430
UINT32                                                 _rsvd_00[   1] ;         // 0xC9C1_0434
CTOP_CTRL_GFX_CTOP_GFX_R14_M19A0_T           ctop_gfx_r14             ;         // 0xC9C1_0438
UINT32                                                 _rsvd_01[   1] ;         // 0xC9C1_043C
CTOP_CTRL_GFX_CTOP_GFX_R16_M19A0_T           ctop_gfx_r16             ;         // 0xC9C1_0440
CTOP_CTRL_GFX_CTOP_GFX_R17_M19A0_T           ctop_gfx_r17             ;         // 0xC9C1_0444
CTOP_CTRL_GFX_CTOP_GFX_R18_M19A0_T           ctop_gfx_r18             ;         // 0xC9C1_0448
CTOP_CTRL_GFX_CTOP_GFX_R19_M19A0_T           ctop_gfx_r19             ;         // 0xC9C1_044C
CTOP_CTRL_GFX_CTOP_GFX_R20_M19A0_T           ctop_gfx_r20             ;         // 0xC9C1_0450
CTOP_CTRL_GFX_CTOP_GFX_R21_M19A0_T           ctop_gfx_r21             ;         // 0xC9C1_0454
CTOP_CTRL_GFX_CTOP_GFX_R22_M19A0_T           ctop_gfx_r22             ;         // 0xC9C1_0458
CTOP_CTRL_GFX_CTOP_GFX_R23_M19A0_T           ctop_gfx_r23             ;         // 0xC9C1_045C
CTOP_CTRL_GFX_CTOP_GFX_R24_M19A0_T           ctop_gfx_r24             ;         // 0xC9C1_0460
CTOP_CTRL_GFX_CTOP_GFX_R28_M19A0_T           ctop_gfx_r28             ;         // 0xC9C1_0464
CTOP_CTRL_GFX_CTOP_GFX_R29_M19A0_T           ctop_gfx_r29             ;         // 0xC9C1_0468
CTOP_CTRL_GFX_CTOP_GFX_R30_M19A0_T           ctop_gfx_r30             ;         // 0xC9C1_046C
CTOP_CTRL_GFX_CTOP_GFX_R31_M19A0_T           ctop_gfx_r31             ;         // 0xC9C1_0470
CTOP_CTRL_GFX_RXCLKDRV_DDR_M19A0_T           rxclkdrv_ddr             ;         // 0xC9C1_0474
CTOP_CTRL_GFX_TXCLKDRV_C4TX_M19A0_T          txclkdrv_c4tx            ;         // 0xC9C1_0478
} CTOP_CTRL_GFX_REG_M19A0_T;
/* 29 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_GFX_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

