#ifndef _CTOP_SYN_FME1_E60A0_REG_H_
#define _CTOP_SYN_FME1_E60A0_REG_H_

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
    0xC932_A400    syn_fme1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_me1_ctrl          : 32;    //  31: 0
}CTOP_FME1_SYN_FME1000_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A404    syn_fme1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_me1        :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FME1_SYN_FME1001_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A408    syn_fme1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_me0_me1_scr_mv  :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FME1_SYN_FME1002_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A40C    syn_fme1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopll_cih       :  4,    //   3: 0
    reg_core_aiopll_fine_control: 3,    //  6: 4
                              :  1,    //      7 reserved
    reg_core_aiopll_fine_div  :  1,    //      8
    reg_core_aiopll_fout_od   :  2,    //  10: 9
                              :  1,    //     11 reserved
    reg_core_aiopll_nsc       :  4,    //  15:12
    reg_core_aiopll_npc       :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_core_aiopll_m         :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CTOP_FME1_SYN_FME1003_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A410    bnd_m0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopll_mod_freq_max: 9,    //  8: 0
                              :  3,    //  11: 9 reserved
    reg_core_aiopll_updn_max  :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_core_aiopll_accuracy  :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_core_aiopll_dss       :  1,    //     23
    reg_core_aiopll_offset    :  8;    //  31:24
}CTOP_FME1_BND_M0_R01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A414    bnd_m0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopll_freq_update: 1,    //      0
    reg_core_aiopll_lock      :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_core_aiopll_fout3_od  :  3,    //   6: 4
                              :  5,    //  11: 7 reserved
    reg_core_aiopll_fout3_pre_od: 3,    //  14:12
                              :  1,    //     15 reserved
    reg_core_aiopll_fout2_od  :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_core_aiopll_fout2_pre_od: 3,    //  22:20
                              :  1,    //     23 reserved
    reg_core_aiopll_sync_on   :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_core_aiopll_wake_bypass: 1,    //     27
    reg_core_aiopll_offset_mode: 1,    //     28
                              :  2,    //  30:29 reserved
    reg_core_aiopll_ddr_mode  :  1;    //     31
}CTOP_FME1_BND_M0_R02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A418    f54_pll_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_codec_ss_aiopll_offset_1: 1,    //     1
    reg_codec_ss_aiopll_offset_3: 1,    //     2
    reg_codec_ss_aiopll_offset_4: 1,    //     3
    reg_codec_ss_aiopll_wakeup_bypass: 1,    //  4
    reg_codec_ss_aiopll_fout2_pre_od: 3,    //  7:5
    reg_codec_ss_aiopll_fout3_pre_od: 3,    //  10:8
    reg_codec_ss_aiopll_dss   :  1,    //     11
    reg_codec_ss_aiopll_fine_div: 1,    //    12
    reg_codec_ss_aiopll_offset_mode: 1,    //  13
                              :  1,    //     14 reserved
    reg_codec_ss_aiopll_offset_5: 1,    //    15
    reg_codec_ss_aiopll_offset_0: 1,    //    16
    reg_codec_ss_aiopll_accuracy_0: 1,    //  17
    reg_codec_ss_aiopll_in_sel:  1,    //     18
    reg_codec_ss_aiopll_fine_control: 3,    //  21:19
    reg_codec_ss_aiopll_offset_7: 1,    //    22
    reg_codec_ss_aiopll_fout2_post_od: 3,    //  25:23
    reg_codec_ss_aiopll_mod_freq_max_8to6: 3,    //  28:26
    reg_codec_ss_aiopll_fout3_post_od: 3;    //  31:29
}CTOP_FME1_F54_PLL_0_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A41C    f54_pll_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_ss_aiopll_ddr_mode: 1,    //     0
    reg_codec_ss_aiopll_syncon:  1,    //      1
    reg_codec_ss_aiopll_m     :  6,    //   7: 2
                              : 24;    //   31:8 reserved
}CTOP_FME1_F54_PLL_1_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A420    f54_pll_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_ss_aiopll_lock  :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_codec_ss_aiopll_frequp:  1,    //     23
    reg_codec_ss_aiopll_mod_freq_max_5to0: 6,    //  29:24
    reg_codec_ss_aiopll_offset_2: 1,    //    30
    reg_codec_ss_aiopll_offset_6: 1;    //    31
}CTOP_FME1_F54_PLL_2_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A424    pll ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aioplls_lock     :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_emmc_aioplls_out_div  :  2,    //  12:11
                              :  1,    //     13 reserved
    reg_emmc_aioplls_fout2_en :  1,    //     14
    reg_emmc_aioplls_fb_m     :  8,    //  22:15
    reg_emmc_aioplls_cih      :  4,    //  26:23
    reg_emmc_aioplls_fout1_en :  1,    //     27
    reg_emmc_aioplls_cih2     :  4;    //  31:28
}CTOP_FME1_PLL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A428    cpu_pll ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aioplls_lock      :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_cpu_aioplls_out_div   :  2,    //  12:11
                              :  1,    //     13 reserved
    reg_cpu_aioplls_fout2_en  :  1,    //     14
    reg_cpu_aioplls_fb_m      :  8,    //  22:15
    reg_cpu_aioplls_cih       :  4,    //  26:23
    reg_cpu_aioplls_fout1_en  :  1,    //     27
    reg_cpu_aioplls_cih2      :  4;    //  31:28
}CTOP_FME1_CPU_PLL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A42C    codec_pll ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aioplls_lock    :  1,    //      0
                              : 10,    //  10: 1 reserved
    reg_codec_aioplls_out_div :  2,    //  12:11
                              :  1,    //     13 reserved
    reg_codec_aioplls_fout2_en:  1,    //     14
    reg_codec_aioplls_fb_m    :  8,    //  22:15
    reg_codec_aioplls_cih     :  4,    //  26:23
    reg_codec_aioplls_fout1_en:  1,    //     27
    reg_codec_aioplls_cih2    :  4;    //  31:28
}CTOP_FME1_CODEC_PLL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A430    syn_fmc1_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    txclkdrv_icon             :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FME1_SYN_FMC1_08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A434    syn_pll_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_core800       :  2,    //   1: 0
    reg_clk_sel_core660       :  2,    //   3: 2
    reg_clk_sel_core480       :  2,    //   5: 4
    reg_clk_sel_core440       :  2,    //   7: 6
    reg_clk_sel_core400       :  2,    //   9: 8
    reg_clk_sel_core533       :  2,    //  11:10
    reg_clk_sel_emmc400       :  2,    //  13:12
    reg_pll_sel_core800       :  2,    //  15:14
    reg_pll_sel_core660       :  2,    //  17:16
    reg_pll_sel_core480       :  2,    //  19:18
    inv_txclkdrv_icon         :  2,    //  21:20
    reg_pll_sel_core400       :  2,    //  23:22
    reg_pll_sel_core533       :  2,    //  25:24
    reg_pll_sel_emmc400       :  2,    //  27:26
                              :  4;    //  31:28 reserved
}CTOP_FME1_SYN_PLL_SEL_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A438    syn_swrst_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_disp_i_lgsr1a   :  1,    //      0
    reg_swrst_disp_i_lgsr0    :  1,    //      1
    reg_swrst_disp_i_hdmi     :  1,    //      2
    reg_swrst_disp_i_dpe      :  1,    //      3
    reg_swrst_disp_i_cvi      :  1,    //      4
    reg_swrst_disp_i_cco1     :  1,    //      5
    reg_swrst_disp_i_cco0     :  1,    //      6
    reg_swrst_cpuav_i_vd2b    :  1,    //      7
    reg_swrst_cpuav_i_vd2a    :  1,    //      8
    reg_swrst_cpuav_i_vd1     :  1,    //      9
    reg_swrst_cpuav_i_vd0     :  1,    //     10
    reg_swrst_cpuav_i_sre     :  1,    //     11
    reg_swrst_cpuav_i_obd     :  1,    //     12
    reg_swrst_cpuav_i_nd2     :  1,    //     13
    reg_swrst_cpuav_i_nd1     :  1,    //     14
    reg_swrst_cpuav_i_nd0     :  1,    //     15
    reg_swrst_cpuav_i_lbus    :  1,    //     16
    reg_swrst_cpuav_i_imx2    :  1,    //     17
    reg_swrst_cpuav_i_imx1    :  1,    //     18
    reg_swrst_cpuav_i_imx0    :  1,    //     19
    reg_swrst_cpuav_i_hdr     :  1,    //     20
    reg_swrst_cpuav_i_gsc1    :  1,    //     21
    reg_swrst_cpuav_i_gsc0    :  1,    //     22
    reg_swrst_cpuav_i_gem     :  1,    //     23
    reg_swrst_cpuav_i_fms     :  1,    //     24
    reg_swrst_cpuav_i_fme1    :  1,    //     25
    reg_swrst_cpuav_i_fme0    :  1,    //     26
    reg_swrst_cpuav_i_fmc1    :  1,    //     27
    reg_swrst_cpuav_i_fmc0    :  1,    //     28
    reg_swrst_cpuav_i_edid    :  1,    //     29
    reg_swrst_cpuav_i_dbb     :  1,    //     30
    reg_swrst_cpuav_i_cpuperi :  1;    //     31
}CTOP_FME1_SYN_SWRST_00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A43C    syn_swrst_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_cpuav_i_d100_vd2a: 1,    //      0
    reg_swrst_cpuav_i_d100_vd1:  1,    //      1
    reg_swrst_cpuav_i_d100_vd0:  1,    //      2
    reg_swrst_cpuav_i_d100_usb_hs: 1,    //    3
    reg_swrst_cpuav_i_d100_sre:  1,    //      4
    reg_swrst_cpuav_i_d100_obd:  1,    //      5
    reg_swrst_cpuav_i_d100_nd2:  1,    //      6
    reg_swrst_cpuav_i_d100_nd1:  1,    //      7
    reg_swrst_cpuav_i_d100_nd0:  1,    //      8
    reg_swrst_cpuav_i_d100_lbus: 1,    //      9
    reg_swrst_cpuav_i_d100_imx2: 1,    //     10
    reg_swrst_cpuav_i_d100_imx1: 1,    //     11
    reg_swrst_cpuav_i_d100_imx0: 1,    //     12
    reg_swrst_cpuav_i_d100_hdr:  1,    //     13
    reg_swrst_cpuav_i_d100_gsc1: 1,    //     14
    reg_swrst_cpuav_i_d100_gsc0: 1,    //     15
    reg_swrst_cpuav_i_d100_gem:  1,    //     16
    reg_swrst_cpuav_i_d100_fms:  1,    //     17
    reg_swrst_cpuav_i_d100_fme1: 1,    //     18
    reg_swrst_cpuav_i_d100_fme0: 1,    //     19
    reg_swrst_cpuav_i_d100_fmc1: 1,    //     20
    reg_swrst_cpuav_i_d100_fmc0: 1,    //     21
    reg_swrst_cpuav_i_d100_edid: 1,    //     22
    reg_swrst_cpuav_i_d100_dbb:  1,    //     23
    reg_swrst_cpuav_i_d100_cpuperi: 1,    //  24
    reg_swrst_disp_i_vsd1     :  1,    //     25
    reg_swrst_disp_i_vsd0     :  1,    //     26
    reg_swrst_disp_i_oysr     :  1,    //     27
    reg_swrst_disp_i_oasr     :  1,    //     28
    reg_swrst_disp_i_lgsr1d   :  1,    //     29
    reg_swrst_disp_i_lgsr1c   :  1,    //     30
    reg_swrst_disp_i_lgsr1b   :  1;    //     31
}CTOP_FME1_SYN_SWRST_01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A440    syn_swrst_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_cpuav_i_d100_vd3b: 1,    //      0
    reg_swrst_cpuav_i_d100_vd3a: 1,    //      1
    reg_swrst_cpuav_i_d100_gpu:  1,    //      2
    reg_swrst_cpuav_i_d100_m2 :  1,    //      3
    reg_swrst_cpuav_i_d100_m1 :  1,    //      4
    reg_swrst_cpuav_i_d100_m0 :  1,    //      5
    reg_swrst_cpuav_i_vd3b    :  1,    //      6
    reg_swrst_cpuav_i_vd3a    :  1,    //      7
    reg_swrst_cpuav_i_m2      :  1,    //      8
    reg_swrst_cpuav_i_m1      :  1,    //      9
    reg_swrst_cpuav_i_m0      :  1,    //     10
    reg_swrst_disp_i_d100_vsd1:  1,    //     11
    reg_swrst_disp_i_d100_vsd0:  1,    //     12
    reg_swrst_disp_i_d100_oysr:  1,    //     13
    reg_swrst_disp_i_d100_oasr:  1,    //     14
    reg_swrst_disp_i_d100_lgsr1d: 1,    //    15
    reg_swrst_disp_i_d100_lgsr1c: 1,    //    16
    reg_swrst_disp_i_d100_lgsr1b: 1,    //    17
    reg_swrst_disp_i_d100_lgsr1a: 1,    //    18
    reg_swrst_disp_i_d100_lgsr0: 1,    //     19
    reg_swrst_disp_i_d100_hdmi:  1,    //     20
    reg_swrst_disp_i_d100_dpe :  1,    //     21
    reg_swrst_disp_i_d100_cvi :  1,    //     22
    reg_swrst_disp_i_d100_cco1:  1,    //     23
    reg_swrst_disp_i_d100_cco0:  1,    //     24
    reg_swrst_cpuav_i_d100_vd2b: 1,    //     25
                              :  6;    //  31:26 reserved
}CTOP_FME1_SYN_SWRST_02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A444    syn_swrst_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aadpll_pdb_ctrl       :  1,    //      0
    reg_gpupll_pdb_ctrl       :  1,    //      1
    reg_f54pll_pdb_ctrl       :  1,    //      2
    reg_displl_pdb_ctrl       :  1,    //      3
    reg_codecpll_ss_pdb_ctrl  :  1,    //      4
    reg_emmcpll_pdb_ctrl      :  1,    //      5
    reg_cpupll_pdb_ctrl       :  1,    //      6
    reg_codecpll_pdb_ctrl     :  1,    //      7
    reg_corepll_pdb_ctrl      :  1,    //      8
    reg_m2pll_pdb_ctrl        :  1,    //      9
    reg_m1pll_pdb_ctrl        :  1,    //     10
    reg_m0pll_pdb_ctrl        :  1,    //     11
                              : 20;    //  31:12 reserved
}CTOP_FME1_SYN_SWRST_03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A448    syn_swrst_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_spll_divint_mux_sel   :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}CTOP_FME1_SYN_SWRST_04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A44C    syn_swrst_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nwd_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FME1_SYN_SWRST_05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_A450    rxclkdrv ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_md_pll1_smv  :  1,    //      0
    reg_rxclkdrv_md_pll0_smv  :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_FME1_RXCLKDRV_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    fme1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_FME1_SYN_FME1000_E60_A0_T           syn_fme1000              ;         // 0xC932_A400
    CTOP_FME1_SYN_FME1001_E60_A0_T           syn_fme1001              ;         // 0xC932_A404
    CTOP_FME1_SYN_FME1002_E60_A0_T           syn_fme1002              ;         // 0xC932_A408
    CTOP_FME1_SYN_FME1003_E60_A0_T           syn_fme1003              ;         // 0xC932_A40C
    CTOP_FME1_BND_M0_R01_E60_A0_T            bnd_m0_r01               ;         // 0xC932_A410
    CTOP_FME1_BND_M0_R02_E60_A0_T            bnd_m0_r02               ;         // 0xC932_A414
    CTOP_FME1_F54_PLL_0_E60_A0_T             f54_pll_0                ;         // 0xC932_A418
    CTOP_FME1_F54_PLL_1_E60_A0_T             f54_pll_1                ;         // 0xC932_A41C
    CTOP_FME1_F54_PLL_2_E60_A0_T             f54_pll_2                ;         // 0xC932_A420
    CTOP_FME1_PLL_E60_A0_T                   pll                      ;         // 0xC932_A424
    CTOP_FME1_CPU_PLL_E60_A0_T               cpu_pll                  ;         // 0xC932_A428
    CTOP_FME1_CODEC_PLL_E60_A0_T             codec_pll                ;         // 0xC932_A42C
    CTOP_FME1_SYN_FMC1_08_E60_A0_T           syn_fmc1_08              ;         // 0xC932_A430
    CTOP_FME1_SYN_PLL_SEL_E60_A0_T           syn_pll_sel              ;         // 0xC932_A434
    CTOP_FME1_SYN_SWRST_00_E60_A0_T          syn_swrst_00             ;         // 0xC932_A438
    CTOP_FME1_SYN_SWRST_01_E60_A0_T          syn_swrst_01             ;         // 0xC932_A43C
    CTOP_FME1_SYN_SWRST_02_E60_A0_T          syn_swrst_02             ;         // 0xC932_A440
    CTOP_FME1_SYN_SWRST_03_E60_A0_T          syn_swrst_03             ;         // 0xC932_A444
    CTOP_FME1_SYN_SWRST_04_E60_A0_T          syn_swrst_04             ;         // 0xC932_A448
    CTOP_FME1_SYN_SWRST_05_E60_A0_T          syn_swrst_05             ;         // 0xC932_A44C
    CTOP_FME1_RXCLKDRV_E60_A0_T              rxclkdrv                 ;         // 0xC932_A450
} CTOP_SYN_FME1_REG_E60_A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_FME1_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

