#ifndef _CTOP_CTRL_LBMS_O20A0_REG_H_
#define _CTOP_CTRL_LBMS_O20A0_REG_H_

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
    0xC930_0C00    core_aiopll0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopll_lock      :  1,    //      0
    reg_core_aiopll_fine_div  :  1,    //      1
    reg_core_aiopll_dss       :  1,    //      2
    reg_core_aiopll_accuracy  :  2,    //   4: 3
    reg_core_aiopll_updn_max  :  7,    //  11: 5
    reg_core_aiopll_mod_freq_max: 9,    //  20:12
    reg_core_aiopll_m         :  6,    //  26:21
                              :  1,    //     27 reserved
    reg_core_aiopll_cih       :  4;    //  31:28
}CTOP_CTRL_LBMS_CORE_AIOPLL0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C04    core_aiopll1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_core_aiopll_offset_mode: 1,    //      4
    reg_core_aiopll_fout3_post_od: 3,    //  7:5
    reg_core_aiopll_fout2_post_od: 3,    //  10:8
    reg_core_aiopll_fout_od   :  2,    //  12:11
    reg_core_aiopll_fout3_pre_od: 3,    //  15:13
    reg_core_aiopll_fout2_pre_od: 3,    //  18:16
    reg_core_aiopll_nsc       :  4,    //  22:19
    reg_core_aiopll_npc       :  6,    //  28:23
    reg_core_aiopll_fine_control: 3;    //  31:29
}CTOP_CTRL_LBMS_CORE_AIOPLL1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C08    core_aiopll2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopll_freq_update: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_core_aiopll_sync_on   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_core_aiopll_in_sel    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_core_aiopll_pdb       :  1,    //     12
                              :  9,    //  21:13 reserved
    reg_core_aiopll_wake_bypass: 1,    //     22
    reg_core_aiopll_ddr_mode  :  1,    //     23
    reg_core_aiopll_offset    :  8;    //  31:24
}CTOP_CTRL_LBMS_CORE_AIOPLL2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C0C    codec_aioplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aioplls_pdb     :  1,    //      0
    reg_codec_aioplls_lock    :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_codec_aioplls_out_div :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_codec_aioplls_fb_m    :  8,    //  15: 8
    reg_codec_aioplls_cih     :  4,    //  19:16
    reg_codec_aioplls_fout1_en:  1,    //     20
                              :  3,    //  23:21 reserved
    reg_codec_aioplls_cih2    :  4,    //  27:24
    reg_codec_aioplls_fout2_en:  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_LBMS_CODEC_AIOPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C10    cpu_aioplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aioplls_pdb       :  1,    //      0
    reg_cpu_aioplls_lock      :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_cpu_aioplls_out_div   :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_cpu_aioplls_fb_m      :  8,    //  15: 8
    reg_cpu_aioplls_cih       :  4,    //  19:16
    reg_cpu_aioplls_fout1_en  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_cpu_aioplls_cih2      :  4,    //  27:24
    reg_cpu_aioplls_fout2_en  :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_LBMS_CPU_AIOPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C14    emmc_aioplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aioplls_pdb      :  1,    //      0
    reg_emmc_aioplls_lock     :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_emmc_aioplls_out_div  :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_emmc_aioplls_fb_m     :  8,    //  15: 8
    reg_emmc_aioplls_cih      :  4,    //  19:16
    reg_emmc_aioplls_fout1_en :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_emmc_aioplls_cih2     :  4,    //  27:24
    reg_emmc_aioplls_fout2_en :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_LBMS_EMMC_AIOPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C18    sdec_frplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sdec_frpll_fin_sel    :  1,    //      0
    reg_sdec_frpll_in_divsel  :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_sdec_frpll_fout_en    :  1,    //      4
    reg_sdec_frpll_fout2_en   :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_sdec_frpll_auto_freq  :  1,    //      8
    reg_sdec_frpll_frequp     :  1,    //      9
    reg_sdec_frpll_syncon     :  1,    //     10
                              :  1,    //     11 reserved
    reg_sdec_frpll_icp        :  4,    //  15:12
    reg_sdec_frpll_icp_g      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_sdec_frpll_a          :  6,    //  25:20
                              :  2,    //  27:26 reserved
    reg_sdec_frpll_dsmon      :  1,    //     28
    reg_sdec_frpll_dsm_limit  :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_LBMS_SDEC_FRPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C1C    sdec_frplls1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sdec_frpll_fcw        : 24,    //  23: 0
    reg_sdec_frpll_m          :  6,    //  29:24
                              :  1,    //     30 reserved
    reg_sdec_frpll_lpf_on     :  1;    //     31
}CTOP_CTRL_LBMS_SDEC_FRPLLS1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C20    sdec_frplls2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sdec_frpll_pdb        :  1,    //      0
    reg_sdec_frpll_lock       :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_sdec_frpll_in_divrstb :  1,    //      4
    reg_sdec_frpll_wakeup_bypass: 1,    //     5
                              :  2,    //   7: 6 reserved
    reg_sdec_frpll_divint     :  9,    //  16: 8
                              :  3,    //  19:17 reserved
    reg_sdec_frpll_out_div    :  9,    //  28:20
                              :  3;    //  31:29 reserved
}CTOP_CTRL_LBMS_SDEC_FRPLLS2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C24    m0_m1_rxclkdrv ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m1_rxclkdrv_pdb       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_m1_rxclkdrv_smv       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_m1_rxclkdrv_cksel     :  2,    //   9: 8
                              :  6,    //  15:10 reserved
    reg_m0_rxclkdrv_pdb       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_m0_rxclkdrv_smv       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_m0_rxclkdrv_cksel     :  2,    //  25:24
                              :  6;    //  31:26 reserved
}CTOP_CTRL_LBMS_M0_M1_RXCLKDRV_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C28    rxclkdrv10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_pdb          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_rxclkdrv_smv          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_rxclkdrv_cksel        :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}CTOP_CTRL_LBMS_RXCLKDRV10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C2C    txclkdrv13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_pdb          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_cksel        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_txclkdrv_icon         :  3,    //  10: 8
                              : 21;    //  31:11 reserved
}CTOP_CTRL_LBMS_TXCLKDRV13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C30    crg_top00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    frpll_sdec_pdb_ctrl       :  1,    //      0
    frpll_pqe_pdb_ctrl        :  1,    //      1
    frpll_earc_pdb_ctrl       :  1,    //      2
    frpll_aud_pdb_ctrl        :  1,    //      3
    aiopll_m1_pdb_ctrl        :  1,    //      4
    aiopll_m0_pdb_ctrl        :  1,    //      5
    aiopll_gpu_pdb_ctrl       :  1,    //      6
    aiopll_emmc_pdb_ctrl      :  1,    //      7
    aiopll_disp_pdb_ctrl      :  1,    //      8
    aiopll_cpu_pdb_ctrl       :  1,    //      9
    aiopll_core_pdb_ctrl      :  1,    //     10
    aiopll_codec_pdb_ctrl     :  1,    //     11
    aiopll_aud_pdb_ctrl       :  1,    //     12
    aiopll_aad_pdb_ctrl       :  1,    //     13
                              : 18;    //  31:14 reserved
}CTOP_CTRL_LBMS_CRG_TOP00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C34    crg_top01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_disp_bmc            :  1,    //      0
    swrst_disp_cco            :  1,    //      1
    swrst_disp_cvi            :  1,    //      2
    swrst_disp_dpe            :  1,    //      3
    swrst_disp_hdmi           :  1,    //      4
    swrst_disp_lgsr           :  1,    //      5
    swrst_disp_vsd            :  1,    //      6
                              :  9,    //  15: 7 reserved
    swrst_disp_d100_cco       :  1,    //     16
    swrst_disp_d100_cvi       :  1,    //     17
    swrst_disp_d100_dsc       :  1,    //     18
    swrst_disp_d100_fsc       :  1,    //     19
    swrst_disp_d100_hdmi      :  1,    //     20
    swrst_disp_d100_led       :  1,    //     21
    swrst_disp_d100_lgsr      :  1,    //     22
    swrst_disp_d100_sd        :  1,    //     23
    swrst_disp_d100_tcon      :  1,    //     24
    swrst_disp_d100_vsd       :  1,    //     25
                              :  6;    //  31:26 reserved
}CTOP_CTRL_LBMS_CRG_TOP01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C38    crg_top02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_cpuav_atg           :  1,    //      0
    swrst_cpuav_cpuperi       :  1,    //      1
    swrst_cpuav_cvi           :  1,    //      2
    swrst_cpuav_demod         :  1,    //      3
    swrst_cpuav_dpe           :  1,    //      4
    swrst_cpuav_dram0         :  1,    //      5
    swrst_cpuav_dram1         :  1,    //      6
    swrst_cpuav_fmc           :  1,    //      7
    swrst_cpuav_fme0          :  1,    //      8
    swrst_cpuav_fme1          :  1,    //      9
    swrst_cpuav_fms           :  1,    //     10
    swrst_cpuav_gem           :  1,    //     11
    swrst_cpuav_gsc           :  1,    //     12
    swrst_cpuav_hdr           :  1,    //     13
    swrst_cpuav_imx           :  1,    //     14
    swrst_cpuav_lbm           :  1,    //     15
    swrst_cpuav_ldo           :  1,    //     16
    swrst_cpuav_lgsr          :  1,    //     17
    swrst_cpuav_nd0           :  1,    //     18
    swrst_cpuav_nd1           :  1,    //     19
    swrst_cpuav_usb2          :  1,    //     20
    swrst_cpuav_vd0           :  1,    //     21
    swrst_cpuav_vd1           :  1,    //     22
    swrst_cpuav_vd2           :  1,    //     23
    swrst_cpuav_wov           :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_LBMS_CRG_TOP02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C3C    crg_top03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_cpuav_d100_aud      :  1,    //      0
    swrst_cpuav_d100_cpuperi  :  1,    //      1
    swrst_cpuav_d100_demod    :  1,    //      2
    swrst_cpuav_d100_dram0    :  1,    //      3
    swrst_cpuav_d100_dram1    :  1,    //      4
    swrst_cpuav_d100_emmc     :  1,    //      5
    swrst_cpuav_d100_fmc      :  1,    //      6
    swrst_cpuav_d100_fme0     :  1,    //      7
    swrst_cpuav_d100_fme1     :  1,    //      8
    swrst_cpuav_d100_fms      :  1,    //      9
    swrst_cpuav_d100_gbus     :  1,    //     10
    swrst_cpuav_d100_gem      :  1,    //     11
    swrst_cpuav_d100_gsc      :  1,    //     12
    swrst_cpuav_d100_hdr      :  1,    //     13
    swrst_cpuav_d100_imx      :  1,    //     14
    swrst_cpuav_d100_lbm      :  1,    //     15
    swrst_cpuav_d100_lbus     :  1,    //     16
    swrst_cpuav_d100_mcu      :  1,    //     17
    swrst_cpuav_d100_nd0      :  1,    //     18
    swrst_cpuav_d100_nd1      :  1,    //     19
    swrst_cpuav_d100_sre      :  1,    //     20
    swrst_cpuav_d100_usb_drd  :  1,    //     21
    swrst_cpuav_d100_usb_hs   :  1,    //     22
    swrst_cpuav_d100_usb0_hs  :  1,    //     23
    swrst_cpuav_d100_usb1_hs  :  1,    //     24
    swrst_cpuav_d100_usb2_hs  :  1,    //     25
    swrst_cpuav_d100_vd0      :  1,    //     26
    swrst_cpuav_d100_vd1      :  1,    //     27
    swrst_cpuav_d100_vd2      :  1,    //     28
    swrst_cpuav_d100_wov      :  1,    //     29
    swrst_cpuav_d100_gpu      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_LBMS_CRG_TOP03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C40    crg_top04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f24_sel                   :  1,    //      0
                              :  3,    //   3: 1 reserved
    f27_18_sel                :  1,    //      4
                              :  3,    //   7: 5 reserved
    sc_ext_sel                :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_frpll_ext_sel         :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CTRL_LBMS_CRG_TOP04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C44    pll_ckmux00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pll_sel_core400           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    pll_sel_core480           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    pll_sel_core533           :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    pll_sel_dsc600            :  2,    //  13:12
                              :  2,    //  15:14 reserved
    pll_sel_emmc400           :  2,    //  17:16
                              :  2,    //  19:18 reserved
    pll_sel_gfx600            :  2,    //  21:20
                              :  2,    //  23:22 reserved
    pll_sel_lgsr800           :  2,    //  25:24
                              :  2,    //  27:26 reserved
    pll_sel_vdec533           :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_LBMS_PLL_CKMUX00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C48    pll_ckmux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    clk_sel_core400           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    clk_sel_core480           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    clk_sel_core533           :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    clk_sel_dsc600            :  2,    //  13:12
                              :  2,    //  15:14 reserved
    clk_sel_emmc400           :  2,    //  17:16
                              :  2,    //  19:18 reserved
    clk_sel_gfx600            :  2,    //  21:20
                              :  2,    //  23:22 reserved
    clk_sel_lgsr800           :  2,    //  25:24
                              :  2,    //  27:26 reserved
    clk_sel_vdec533           :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_LBMS_PLL_CKMUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0C4C    efuse_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_pd              :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_LBMS_EFUSE_CTRL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_lbms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_LBMS_CORE_AIOPLL0_O20A0_T          core_aiopll0             ;         // 0xC930_0C00
CTOP_CTRL_LBMS_CORE_AIOPLL1_O20A0_T          core_aiopll1             ;         // 0xC930_0C04
CTOP_CTRL_LBMS_CORE_AIOPLL2_O20A0_T          core_aiopll2             ;         // 0xC930_0C08
CTOP_CTRL_LBMS_CODEC_AIOPLLS0_O20A0_T        codec_aioplls0           ;         // 0xC930_0C0C
CTOP_CTRL_LBMS_CPU_AIOPLLS0_O20A0_T          cpu_aioplls0             ;         // 0xC930_0C10
CTOP_CTRL_LBMS_EMMC_AIOPLLS0_O20A0_T         emmc_aioplls0            ;         // 0xC930_0C14
CTOP_CTRL_LBMS_SDEC_FRPLLS0_O20A0_T          sdec_frplls0             ;         // 0xC930_0C18
CTOP_CTRL_LBMS_SDEC_FRPLLS1_O20A0_T          sdec_frplls1             ;         // 0xC930_0C1C
CTOP_CTRL_LBMS_SDEC_FRPLLS2_O20A0_T          sdec_frplls2             ;         // 0xC930_0C20
CTOP_CTRL_LBMS_M0_M1_RXCLKDRV_O20A0_T        m0_m1_rxclkdrv           ;         // 0xC930_0C24
CTOP_CTRL_LBMS_RXCLKDRV10_O20A0_T            rxclkdrv10               ;         // 0xC930_0C28
CTOP_CTRL_LBMS_TXCLKDRV13_O20A0_T            txclkdrv13               ;         // 0xC930_0C2C
CTOP_CTRL_LBMS_CRG_TOP00_O20A0_T             crg_top00                ;         // 0xC930_0C30
CTOP_CTRL_LBMS_CRG_TOP01_O20A0_T             crg_top01                ;         // 0xC930_0C34
CTOP_CTRL_LBMS_CRG_TOP02_O20A0_T             crg_top02                ;         // 0xC930_0C38
CTOP_CTRL_LBMS_CRG_TOP03_O20A0_T             crg_top03                ;         // 0xC930_0C3C
CTOP_CTRL_LBMS_CRG_TOP04_O20A0_T             crg_top04                ;         // 0xC930_0C40
CTOP_CTRL_LBMS_PLL_CKMUX00_O20A0_T           pll_ckmux00              ;         // 0xC930_0C44
CTOP_CTRL_LBMS_PLL_CKMUX01_O20A0_T           pll_ckmux01              ;         // 0xC930_0C48
CTOP_CTRL_LBMS_EFUSE_CTRL_O20A0_T            efuse_ctrl               ;         // 0xC930_0C4C
} CTOP_CTRL_LBM_REG_O20A0_T;
/* 20 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_LBMS_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

