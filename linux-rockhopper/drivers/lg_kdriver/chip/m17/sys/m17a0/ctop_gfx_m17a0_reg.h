#ifndef _CTOP_GFX_M17A0_REG_H_
#define _CTOP_GFX_M17A0_REG_H_

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
    m1pll_fine_div            :  1,    //      1
    m1pll_dss                 :  1,    //      2
    m1pll_accuracy            :  2,    //   4: 3
    m1pll_updn_max            :  7,    //  11: 5
    m1pll_mod_freq            :  9,    //  20:12
    m1pll_m                   :  6,    //  26:21
                              :  1,    //     27 reserved
    m1pll_cih                 :  4;    //  31:28
}CTOP_GFX_CTOP_GFX_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0404    ctop_gfx_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    m1pll_freq_update         :  1,    //      0
    m1pll_sync_on             :  1,    //      1
                              :  2,    //   3: 2 reserved
    m1pll_ofs_mode            :  1,    //      4
    m1pll_fout3_od            :  3,    //   7: 5
    m1pll_fout2_od            :  3,    //  10: 8
    m1pll_fout_od             :  2,    //  12:11
    m1pll_pre_fout3_div       :  3,    //  15:13
    m1pll_pre_fout2_div       :  3,    //  18:16
    m1pll_nsc                 :  4,    //  22:19
    m1pll_npc                 :  6,    //  28:23
    m1pll_fine_control        :  3;    //  31:29
}CTOP_GFX_CTOP_GFX_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0408    ctop_gfx_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    m1pll_wakeup_bypass       :  1,    //     22
    m1pll_ddr_mode            :  1,    //     23
    m1pll_offset              :  8;    //  31:24
}CTOP_GFX_CTOP_GFX_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_040C    ctop_gfx_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    m2pll_fine_div            :  1,    //      1
    m2pll_dss                 :  1,    //      2
    m2pll_accuracy            :  2,    //   4: 3
    m2pll_updn_max            :  7,    //  11: 5
    m2pll_mod_freq            :  9,    //  20:12
    m2pll_m                   :  6,    //  26:21
                              :  1,    //     27 reserved
    m2pll_cih                 :  4;    //  31:28
}CTOP_GFX_CTOP_GFX_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0410    ctop_gfx_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    m2pll_freq_update         :  1,    //      0
    m2pll_sync_on             :  1,    //      1
                              :  2,    //   3: 2 reserved
    m2pll_ofs_mode            :  1,    //      4
    m2pll_fout3_od            :  3,    //   7: 5
    m2pll_fout2_od            :  3,    //  10: 8
    m2pll_fout_od             :  2,    //  12:11
    m2pll_pre_fout3_div       :  3,    //  15:13
    m2pll_pre_fout2_div       :  3,    //  18:16
    m2pll_nsc                 :  4,    //  22:19
    m2pll_npc                 :  6,    //  28:23
    m2pll_fine_control        :  3;    //  31:29
}CTOP_GFX_CTOP_GFX_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0414    ctop_gfx_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    m2pll_wakeup_bypass       :  1,    //     22
    m2pll_ddr_mode            :  1,    //     23
    m2pll_offset              :  8;    //  31:24
}CTOP_GFX_CTOP_GFX_R05_M17_A0;

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
}CTOP_GFX_CTOP_GFX_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_041C    ctop_gfx_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    codecpll_freq_update      :  1,    //      0
    codecpll_sync_on          :  1,    //      1
                              :  2,    //   3: 2 reserved
    codecpll_ofs_mode         :  1,    //      4
    codecpll_fout3_od         :  3,    //   7: 5
    codecpll_fout2_od         :  3,    //  10: 8
    codecpll_fout_od          :  2,    //  12:11
    codecpll_pre_fout3_div    :  3,    //  15:13
    codecpll_pre_fout2_div    :  3,    //  18:16
    codecpll_nsc              :  4,    //  22:19
    codecpll_npc              :  6,    //  28:23
    codecpll_fine_control     :  3;    //  31:29
}CTOP_GFX_CTOP_GFX_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0420    ctop_gfx_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    codecpll_wakeup_bypass    :  1,    //     22
    codecpll_ddr_mode         :  1,    //     23
    codecpll_offset           :  8;    //  31:24
}CTOP_GFX_CTOP_GFX_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0424    ctop_gfx_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    sc_ext_sel                :  3,    //   6: 4
    dco_ext_sel               :  1,    //      7
    f24_sel                   :  1,    //      8
    f27_18_sel                :  1,    //      9
    rxclkdrv2_smv_normal      :  1,    //     10
    rxclkdrv2_outsel_normal   :  3,    //  13:11
    rxclkdrv2_pdb_normal      :  1,    //     14
    txclkdrv1_icon_normal     :  3,    //  17:15
    txclkdrv1_pdb_normal      :  1,    //     18
    pqe_dco_g_ctrl            :  3,    //  21:19
    pqe_dco_lpf_ctrl          :  2,    //  23:22
    pqe_dco_rom_test_ctrl     :  1,    //     24
    te_dco_g_ctrl             :  3,    //  27:25
    te_dco_lpf_ctrl           :  2,    //  29:28
                              :  1,    //     30 reserved
    te_dco_rom_test_ctrl      :  1;    //     31
}CTOP_GFX_CTOP_GFX_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0428    ctop_gfx_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
	pll_sel_gpu_ddr				: 1,	//0
	ck_mux_pll_sel_emmc			: 2,    //2:1
								: 1,	//3
	ck_mux_pll_sel_gfx			: 2,    //5:4
	ck_mux_pll_sel_aud			: 2,    //7:6
	ck_mux_pll_sel_esm			: 2,    //9:8
	dcoin_clk_gate_en			: 2,    //11:10
								: 2,	//13:12
	ck_mux_pll_sel_vdec0		: 2,    //15:14
	ck_mux_pll_sel_lbus			: 2,    //17:16
	ck_mux_pll_sel_vdec528		: 2,    //19:18
	ck_mux_pll_sel_m1			: 1,    //20
	ck_mux_pll_sel_m0			: 1,    //21
								: 4,    //25:22
	ck_mux_pll_sel_dco			: 2,    //27:26
								: 2,	//29:28
	ck_mux_pll_sel_core			: 2;    //31:30
}CTOP_GFX_CTOP_GFX_R10_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_042C    ctop_gfx_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    swrst_edid                :  1,    //      3
    swrst_demod               :  1,    //      4
    swrst_hdmi                :  1,    //      5
    swrst_venc                :  1,    //      6
    swrst_vdec2               :  1,    //      7
    swrst_vdec1               :  1,    //      8
    swrst_vdec0               :  1,    //      9
    swrst_usb                 :  1,    //     10
    swrst_te                  :  1,    //     11
    swrst_pqe_vsd             :  1,    //     12
    swrst_pqe_sre             :  1,    //     13
    swrst_pqe_nd0             :  1,    //     14
    swrst_pqe_mcu             :  1,    //     15
    swrst_pqe_imx             :  1,    //     16
    swrst_pqe_gsc             :  1,    //     17
    swrst_pqe_fme             :  1,    //     18
    swrst_pqe_fmc             :  1,    //     19
    swrst_pqe_cvi             :  1,    //     20
    swrst_pqe_cco             :  1,    //     21
    swrst_m1                  :  1,    //     22
    swrst_m0                  :  1,    //     23
    swrst_pqe                 :  1,    //     24
    swrst_gfx                 :  1,    //     25
    swrst_lbus                :  1,    //     26
    swrst_gbus                :  1,    //     27
    swrst_emmc                :  1,    //     28
    swrst_dpe                 :  1,    //     29
    swrst_cpuperi             :  1,    //     30
    swrst_aud                 :  1;    //     31
}CTOP_GFX_CTOP_GFX_R11_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0430    ctop_gfx_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    swrst_edid_d100           :  1,    //      3
    swrst_demod_d100          :  1,    //      4
    swrst_hdmi_d100           :  1,    //      5
    swrst_venc_d100           :  1,    //      6
    swrst_vdec2_d100          :  1,    //      7
    swrst_vdec1_d100          :  1,    //      8
    swrst_vdec0_d100          :  1,    //      9
    swrst_usb_d100            :  1,    //     10
    swrst_te_d100             :  1,    //     11
    swrst_pqe_vsd_d100        :  1,    //     12
    swrst_pqe_sre_d100        :  1,    //     13
    swrst_pqe_nd0_d100        :  1,    //     14
    swrst_pqe_mcu_d100        :  1,    //     15
    swrst_pqe_imx_d100        :  1,    //     16
    swrst_pqe_gsc_d100        :  1,    //     17
    swrst_pqe_fme_d100        :  1,    //     18
    swrst_pqe_fmc_d100        :  1,    //     19
    swrst_pqe_cvi_d100        :  1,    //     20
    swrst_pqe_cco_d100        :  1,    //     21
    swrst_m1_d100             :  1,    //     22
    swrst_m0_d100             :  1,    //     23
    swrst_pqe_d100            :  1,    //     24
    swrst_gfx_d100            :  1,    //     25
    swrst_lbus_d100           :  1,    //     26
    swrst_gbus_d100           :  1,    //     27
    swrst_emmc_d100           :  1,    //     28
    swrst_dpe_d100            :  1,    //     29
    swrst_cpuperi_d100        :  1,    //     30
    swrst_aud_d100            :  1;    //     31
}CTOP_GFX_CTOP_GFX_R12_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0434    ctop_gfx_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    swrst_disp_pqe_vsd_d100   :  1,    //      5
    swrst_disp_pqe_sre_d100   :  1,    //      6
    swrst_disp_pqe_nd0_d100   :  1,    //      7
    swrst_disp_pqe_mcu_d100   :  1,    //      8
    swrst_disp_pqe_imx_d100   :  1,    //      9
    swrst_disp_pqe_gsc_d100   :  1,    //     10
    swrst_disp_pqe_fme_d100   :  1,    //     11
    swrst_disp_pqe_fmc_d100   :  1,    //     12
    swrst_disp_pqe_cvi_d100   :  1,    //     13
    swrst_disp_pqe_cco_d100   :  1,    //     14
    swrst_disp_dpe_d100       :  1,    //     15
                              :  5,    //  20:16 reserved
    swrst_disp_pqe_vsd        :  1,    //     21
    swrst_disp_pqe_sre        :  1,    //     22
    swrst_disp_pqe_nd0        :  1,    //     23
    swrst_disp_pqe_mcu        :  1,    //     24
    swrst_disp_pqe_imx        :  1,    //     25
    swrst_disp_pqe_gsc        :  1,    //     26
    swrst_disp_pqe_fme        :  1,    //     27
    swrst_disp_pqe_fmc        :  1,    //     28
    swrst_disp_pqe_cvi        :  1,    //     29
    swrst_disp_pqe_cco        :  1,    //     30
    swrst_disp_dpe            :  1;    //     31
}CTOP_GFX_CTOP_GFX_R13_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0438    ctop_gfx_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 12,    //  11: 0 reserved
    disp594_clk_gate_en       :  1,    //     12
    ddr1pll_pdb_ctrl          :  1,    //     13
    gpupll_xtal_gate_en       :  1,    //     14
    gpupll_pdb_ctrl           :  1,    //     15
    l528_sync_clk_gate_en     :  1,    //     16
    l528_sync_clk_sel         :  1,    //     17
    l396_sync_clk_gate_en     :  1,    //     18
    l396_sync_clk_sel         :  1,    //     19
    g396_sync_clk_gate_en     :  1,    //     20
    g396_sync_clk_sel         :  1,    //     21
    swrst_f396                :  1,    //     22
    f396_sync_clk_gate_en     :  1,    //     23
    f396_sync_clk_sel         :  1,    //     24
                              :  1,    //     25 reserved
    displl_pdb_ctrl           :  1,    //     26
    codecpll_pdb_ctrl         :  1,    //     27
    corepll_pdb_ctrl          :  1,    //     28
    ddr0pll_pdb_ctrl          :  1,    //     29
    sdec_dco_pdb_ctrl         :  1,    //     30
    de_dco_pdb_ctrl           :  1;    //     31
}CTOP_GFX_CTOP_GFX_R14_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_043C    ctop_gfx_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 19,    //  18: 0 reserved
    swrst_l528                :  1,    //     19
    swrst_l396                :  1,    //     20
    swrst_g396                :  1,    //     21
    swrst_gpu_d100            :  1,    //     22
    swrst_gpu                 :  1,    //     23
    swrst_gem_d100            :  1,    //     24
    swrst_gem                 :  1,    //     25
    swrst_disp_pqe_me1_d100   :  1,    //     26
    swrst_disp_pqe_me1        :  1,    //     27
    swrst_disp_pqe_me0_d100   :  1,    //     28
    swrst_disp_pqe_me0        :  1,    //     29
    swrst_disp_pqe_fms_d100   :  1,    //     30
    swrst_disp_pqe_fms        :  1;    //     31
}CTOP_GFX_CTOP_GFX_R15_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0440    ctop_gfx_r16 ''
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
}CTOP_GFX_CTOP_GFX_R16_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0444    ctop_gfx_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    m0pll_freq_update         :  1,    //      0
    m0pll_sync_on             :  1,    //      1
                              :  2,    //   3: 2 reserved
    m0pll_ofs_mode            :  1,    //      4
    m0pll_fout3_od            :  3,    //   7: 5
    m0pll_fout2_od            :  3,    //  10: 8
    m0pll_fout_od             :  2,    //  12:11
    m0pll_pre_fout3_div       :  3,    //  15:13
    m0pll_pre_fout2_div       :  3,    //  18:16
    m0pll_nsc                 :  4,    //  22:19
    m0pll_npc                 :  6,    //  28:23
    m0pll_fine_control        :  3;    //  31:29
}CTOP_GFX_CTOP_GFX_R17_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C1_0448    ctop_gfx_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    m0pll_wakeup_bypass       :  1,    //     22
    m0pll_ddr_mode            :  1,    //     23
    m0pll_offset              :  8;    //  31:24
}CTOP_GFX_CTOP_GFX_R18_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_GFX_CTOP_GFX_R00_M17_A0                 ctop_gfx_r00             ;         // 0xC9C1_0400
CTOP_GFX_CTOP_GFX_R01_M17_A0                 ctop_gfx_r01             ;         // 0xC9C1_0404
CTOP_GFX_CTOP_GFX_R02_M17_A0                 ctop_gfx_r02             ;         // 0xC9C1_0408
CTOP_GFX_CTOP_GFX_R03_M17_A0                 ctop_gfx_r03             ;         // 0xC9C1_040C
CTOP_GFX_CTOP_GFX_R04_M17_A0                 ctop_gfx_r04             ;         // 0xC9C1_0410
CTOP_GFX_CTOP_GFX_R05_M17_A0                 ctop_gfx_r05             ;         // 0xC9C1_0414
CTOP_GFX_CTOP_GFX_R06_M17_A0                 ctop_gfx_r06             ;         // 0xC9C1_0418
CTOP_GFX_CTOP_GFX_R07_M17_A0                 ctop_gfx_r07             ;         // 0xC9C1_041C
CTOP_GFX_CTOP_GFX_R08_M17_A0                 ctop_gfx_r08             ;         // 0xC9C1_0420
CTOP_GFX_CTOP_GFX_R09_M17_A0                 ctop_gfx_r09             ;         // 0xC9C1_0424
CTOP_GFX_CTOP_GFX_R10_M17_A0                 ctop_gfx_r10             ;         // 0xC9C1_0428
CTOP_GFX_CTOP_GFX_R11_M17_A0                 ctop_gfx_r11             ;         // 0xC9C1_042C
CTOP_GFX_CTOP_GFX_R12_M17_A0                 ctop_gfx_r12             ;         // 0xC9C1_0430
CTOP_GFX_CTOP_GFX_R13_M17_A0                 ctop_gfx_r13             ;         // 0xC9C1_0434
CTOP_GFX_CTOP_GFX_R14_M17_A0                 ctop_gfx_r14             ;         // 0xC9C1_0438
CTOP_GFX_CTOP_GFX_R15_M17_A0                 ctop_gfx_r15             ;         // 0xC9C1_043C
CTOP_GFX_CTOP_GFX_R16_M17_A0                 ctop_gfx_r16             ;         // 0xC9C1_0440
CTOP_GFX_CTOP_GFX_R17_M17_A0                 ctop_gfx_r17             ;         // 0xC9C1_0444
CTOP_GFX_CTOP_GFX_R18_M17_A0                 ctop_gfx_r18             ;         // 0xC9C1_0448
} CTOP_GFX_REG_M17_A0;
/* 19 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_GFX_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

