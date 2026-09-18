#ifndef _BND_CTRL_LBM_REG_H_
#define _BND_CTRL_LBM_REG_H_

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
    0xC603_3000    bnd_lbm_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_md_topplls_pdb: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_rxclkdrv_md_topplls_smv: 1,    //      4
                              :  3,    //   7: 5 reserved
    reg_rxclkdrv_md_m0_pdb    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_rxclkdrv_md_m0_smv    :  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_LBM_SYN_BND_LBM_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3010    bnd_lbm_cpupll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_cih      :  4,    //   3: 0
    reg_cpu_aiopllss_fine_control: 3,    //  6:4
    reg_cpu_aiopllss_fine_div :  1,    //      7
    reg_cpu_aiopllss_cih2     :  4,    //  11: 8
    reg_cpu_aiopllss_nsc      :  4,    //  15:12
    reg_cpu_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_cpu_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3014    bnd_lbm_cpupll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_cpu_aiopllss_updn_max :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_cpu_aiopllss_accuracy :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_cpu_aiopllss_dss      :  1,    //     23
    reg_cpu_aiopllss_offset   :  8;    //  31:24
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3018    bnd_lbm_cpupll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_freq_update: 1,    //     0
    reg_cpu_aiopllss_fout1_en :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_cpu_aiopllss_lock     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu_aiopllss_out_div  :  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_cpu_aiopllss_sync_on  :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_cpu_aiopllss_wake_bypass: 1,    //    27
    reg_cpu_aiopllss_offset_mode: 1,    //    28
                              :  3;    //  31:29 reserved
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3020    bnd_lbm_corepll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_cih     :  4,    //   3: 0
    reg_core_aiopllss_fine_control: 3,    //  6:4
    reg_core_aiopllss_fine_div:  1,    //      7
    reg_core_aiopllss_cih2    :  4,    //  11: 8
    reg_core_aiopllss_nsc     :  4,    //  15:12
    reg_core_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_core_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3024    bnd_lbm_corepll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_core_aiopllss_updn_max:  7,    //  18:12
                              :  1,    //     19 reserved
    reg_core_aiopllss_accuracy:  2,    //  21:20
                              :  1,    //     22 reserved
    reg_core_aiopllss_dss     :  1,    //     23
    reg_core_aiopllss_offset  :  8;    //  31:24
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3028    bnd_lbm_corepll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_freq_update: 1,    //    0
    reg_core_aiopllss_fout1_en:  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_core_aiopllss_lock    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_core_aiopllss_out_div :  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_core_aiopllss_sync_on :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_core_aiopllss_wake_bypass: 1,    //   27
    reg_core_aiopllss_offset_mode: 1,    //   28
                              :  3;    //  31:29 reserved
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3030    bnd_lbm_emmcpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_cih     :  4,    //   3: 0
    reg_emmc_aiopllss_fine_control: 3,    //  6:4
    reg_emmc_aiopllss_fine_div:  1,    //      7
    reg_emmc_aiopllss_cih2    :  4,    //  11: 8
    reg_emmc_aiopllss_nsc     :  4,    //  15:12
    reg_emmc_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_emmc_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3034    bnd_lbm_emmcpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_emmc_aiopllss_updn_max:  7,    //  18:12
                              :  1,    //     19 reserved
    reg_emmc_aiopllss_accuracy:  2,    //  21:20
                              :  1,    //     22 reserved
    reg_emmc_aiopllss_dss     :  1,    //     23
    reg_emmc_aiopllss_offset  :  8;    //  31:24
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3038    bnd_lbm_emmcpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_freq_update: 1,    //    0
    reg_emmc_aiopllss_fout1_en:  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_emmc_aiopllss_lock    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_emmc_aiopllss_out_div :  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_emmc_aiopllss_sync_on :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_emmc_aiopllss_wake_bypass: 1,    //   27
    reg_emmc_aiopllss_offset_mode: 1,    //   28
                              :  3;    //  31:29 reserved
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3040    bnd_lbm_codecpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_cih    :  4,    //   3: 0
    reg_codec_aiopllss_fine_control: 3,    //  6:4
    reg_codec_aiopllss_fine_div: 1,    //      7
    reg_codec_aiopllss_cih2   :  4,    //  11: 8
    reg_codec_aiopllss_nsc    :  4,    //  15:12
    reg_codec_aiopllss_npc    :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_codec_aiopllss_m      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3044    bnd_lbm_codecpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_codec_aiopllss_updn_max: 7,    //  18:12
                              :  1,    //     19 reserved
    reg_codec_aiopllss_accuracy: 2,    //  21:20
                              :  1,    //     22 reserved
    reg_codec_aiopllss_dss    :  1,    //     23
    reg_codec_aiopllss_offset :  8;    //  31:24
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3048    bnd_lbm_codecpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_freq_update: 1,    //   0
    reg_codec_aiopllss_fout1_en: 1,    //      1
                              :  2,    //   3: 2 reserved
    reg_codec_aiopllss_lock   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_codec_aiopllss_out_div:  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_codec_aiopllss_sync_on:  1,    //     24
                              :  2,    //  26:25 reserved
    reg_codec_aiopllss_wake_bypass: 1,    //  27
    reg_codec_aiopllss_offset_mode: 1,    //  28
                              :  3;    //  31:29 reserved
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_304C    syn_tx_lo_drv_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tx_lo_drv_nisol_top2m0_pdb: 1,    //   0
    reg_tx_lo_drv_nisol_top2m0_ck_div: 1,    //  1
                              : 30;    //   31:2 reserved
}BND_CTRL_LBM_SYN_TX_LO_DRV_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3050    syn_pll_sel_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    reg_pll_sel_core960       :  2,    //  23:22
    reg_clk_sel_core960       :  2,    //  25:24
    reg_pll_sel_core600       :  2,    //  27:26
    reg_clk_sel_core600       :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_PLL_SEL_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3054    syn_pll_sel_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_vdec660_3a_clk_gate_enb: 1,    //      1
    reg_clk_sel_core660       :  2,    //   3: 2
    reg_clk_sel_core480       :  2,    //   5: 4
    reg_clk_sel_vdec660       :  2,    //   7: 6
    reg_clk_sel_core400       :  2,    //   9: 8
    reg_clk_sel_core533       :  2,    //  11:10
    reg_clk_sel_emmc400       :  2,    //  13:12
    reg_pll_sel_core800       :  2,    //  15:14
    reg_pll_sel_core660       :  2,    //  17:16
    reg_pll_sel_core480       :  2,    //  19:18
                              :  2,    //  21:20 reserved
    reg_pll_sel_core400       :  2,    //  23:22
    reg_pll_sel_core533       :  2,    //  25:24
    reg_pll_sel_emmc400       :  2,    //  27:26
    reg_clk_sel_core800       :  2,    //  29:28
                              :  2;    //  31:30 reserved
}BND_CTRL_LBM_SYN_PLL_SEL_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3060    syn_swrst_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_swrst_cpuav_i_hdr     :  1,    //      3
    reg_swrst_cpuav_i_gpu_d100:  1,    //      4
                              :  1,    //      5 reserved
    reg_swrst_cpuav_i_vd3_d100:  1,    //      6
    reg_swrst_cpuav_i_vd2_d100:  1,    //      7
    reg_swrst_cpuav_i_vd1_d100:  1,    //      8
    reg_swrst_cpuav_i_vd0_d100:  1,    //      9
    reg_swrst_cpuav_i_m1_d100 :  1,    //     10
    reg_swrst_cpuav_i_m0_d100 :  1,    //     11
    reg_swrst_cpuav_i_lgsr_d100: 1,    //     12
    reg_swrst_cpuav_i_lbm_d100:  1,    //     13
    reg_swrst_cpuav_i_gem_d100:  1,    //     14
    reg_swrst_cpuav_i_edid_d100: 1,    //     15
    reg_swrst_cpuav_i_cpu_d100:  1,    //     16
    reg_swrst_cpuav_i_bmc_d100:  1,    //     17
                              :  1,    //     18 reserved
    reg_swrst_cpuav_i_vd3     :  1,    //     19
    reg_swrst_cpuav_i_vd2     :  1,    //     20
    reg_swrst_cpuav_i_vd1     :  1,    //     21
    reg_swrst_cpuav_i_vd0     :  1,    //     22
    reg_swrst_cpuav_i_nd0     :  1,    //     23
    reg_swrst_cpuav_i_m1      :  1,    //     24
    reg_swrst_cpuav_i_m0      :  1,    //     25
    reg_swrst_cpuav_i_lgsr    :  1,    //     26
    reg_swrst_cpuav_i_lbm     :  1,    //     27
    reg_swrst_cpuav_i_gem     :  1,    //     28
    reg_swrst_cpuav_i_edid    :  1,    //     29
    reg_swrst_cpuav_i_cpu     :  1,    //     30
    reg_swrst_cpuav_i_bmc     :  1;    //     31
}BND_CTRL_LBM_SYN_SWRST_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3064    syn_swrst_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_swrst_disp_i_nd1      :  1,    //     20
    reg_swrst_disp_i_nd0      :  1,    //     21
    reg_swrst_disp_i_me1      :  1,    //     22
    reg_swrst_disp_i_me0      :  1,    //     23
    reg_swrst_disp_i_imx      :  1,    //     24
    reg_swrst_disp_i_hdr      :  1,    //     25
    reg_swrst_disp_i_hdmi     :  1,    //     26
    reg_swrst_disp_i_fms      :  1,    //     27
    reg_swrst_disp_i_fmc      :  1,    //     28
    reg_swrst_disp_i_dpe      :  1,    //     29
    reg_swrst_disp_i_cvi      :  1,    //     30
    reg_swrst_disp_i_cco      :  1;    //     31
}BND_CTRL_LBM_SYN_SWRST_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3068    syn_swrst_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_swrst_disp_i_nd1_d100 :  1,    //     20
    reg_swrst_disp_i_nd0_d100 :  1,    //     21
    reg_swrst_disp_i_me1_d100 :  1,    //     22
    reg_swrst_disp_i_me0_d100 :  1,    //     23
    reg_swrst_disp_i_imx_d100 :  1,    //     24
    reg_swrst_disp_i_hdr_d100 :  1,    //     25
    reg_swrst_disp_i_hdmi_d100:  1,    //     26
    reg_swrst_disp_i_fms_d100 :  1,    //     27
    reg_swrst_disp_i_fmc_d100 :  1,    //     28
    reg_swrst_disp_i_dpe_d100 :  1,    //     29
    reg_swrst_disp_i_cvi_d100 :  1,    //     30
    reg_swrst_disp_i_cco_d100 :  1;    //     31
}BND_CTRL_LBM_SYN_SWRST_02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_306C    syn_swrst_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aadpll_pdb_ctrl       :  1,    //      0
    reg_gpupll_pdb_ctrl       :  1,    //      1
    reg_pqepll_pdb_ctrl       :  1,    //      2
    reg_displl_pdb_ctrl       :  1,    //      3
    reg_codecpll_ss_pdb_ctrl  :  1,    //      4
    reg_emmcpll_pdb_ctrl      :  1,    //      5
    reg_cpupll_pdb_ctrl       :  1,    //      6
    reg_codecpll_pdb_ctrl     :  1,    //      7
    reg_corepll_pdb_ctrl      :  1,    //      8
    reg_m1pll_pdb_ctrl        :  1,    //      9
    reg_m0pll_pdb_ctrl        :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_LBM_SYN_SWRST_04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3070    syn_swrst_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_spll_divint_mux_sel   :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}BND_CTRL_LBM_SYN_SWRST_05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3074    syn_swrst_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nwd_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_LBM_SYN_SWRST_06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3200    bnd_lbm_urart_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel0        :  4,    //   3: 0
    reg_main_uart_sel1        :  4,    //   7: 4
    reg_main_uart_sel2        :  4,    //  11: 8
    reg_main_uart_sel3        :  4,    //  15:12
    reg_main_uart_sel4        :  4,    //  19:16
    reg_monitor_sel_0         :  4,    //  23:20
    reg_monitor_sel_1         :  4,    //  27:24
                              :  4;    //  31:28 reserved
}BND_CTRL_LBM_SYN_BND_LBM_URART_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3210    bnd_lbm_jtag_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel0        :  4,    //   3: 0
    reg_main_jtag_sel1        :  4,    //   7: 4
    reg_main_jtag_sel2        :  4,    //  11: 8
    reg_main_jtag_sel3        :  4,    //  15:12
    reg_main_jtag_sel4        :  4,    //  19:16
                              : 12;    //  31:20 reserved
}BND_CTRL_LBM_SYN_BND_LBM_JTAG_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3220    bnd_lbm_urart_lock_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_lock0       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_main_uart_lock1       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_main_uart_lock2       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_main_uart_lock3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_main_uart_lock4       :  1,    //     16
                              : 15;    //  31:17 reserved
}BND_CTRL_LBM_SYN_BND_LBM_URART_LOCK_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3300    bnd_lbm_ft_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
    main_debug_jtag_sel       :  1,    //      1
    regmod_ts                 :  1,    //      2
    regmod_saradc_wov         :  1,    //      3
    regmod_pvm                :  1,    //      4
    regmod_hdmi_isol          :  1,    //      5
    regmod_hdmi_earc          :  1,    //      6
    regmod_ethernet           :  1,    //      7
    regmod_c4tx_isol          :  1,    //      8
    regmod_c4tx_bist          :  1,    //      9
    regmod_acodec             :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_LBM_SYN_BND_LBM_FT_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3304    bnd_vd1_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_npwrup_sram       :  8,    //   7: 0
    reg_vd1_pwrup             :  4,    //  11: 8
    reg_vd1_pwrup_ack         :  4,    //  15:12
    reg_vd1_nisol_en          :  1,    //     16
                              : 15;    //  31:17 reserved
}BND_CTRL_LBM_BND_VD1_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3308    bnd_vd1_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_apb_auto_resp_disable: 1,    //  0
                              : 31;    //   31:1 reserved
}BND_CTRL_LBM_BND_VD1_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LBM_SYN_BND_LBM_RXCLK_MD_R00_O22A0_T    bnd_lbm_rxclk_md_r00;    // 0xC603_3000
    UINT32                             _rsvd_00[3];             // 0xC603_3004 ~ 0xC603_300C
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R00_O22A0_T    bnd_lbm_cpupll_r00;    // 0xC603_3010
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R01_O22A0_T    bnd_lbm_cpupll_r01;    // 0xC603_3014
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R02_O22A0_T    bnd_lbm_cpupll_r02;    // 0xC603_3018
    UINT32                             _rsvd_01[1];             // 0xC603_301C
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R00_O22A0_T    bnd_lbm_corepll_r00;    // 0xC603_3020
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R01_O22A0_T    bnd_lbm_corepll_r01;    // 0xC603_3024
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R02_O22A0_T    bnd_lbm_corepll_r02;    // 0xC603_3028
    UINT32                             _rsvd_02[1];             // 0xC603_302C
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R00_O22A0_T    bnd_lbm_emmcpll_r00;    // 0xC603_3030
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R01_O22A0_T    bnd_lbm_emmcpll_r01;    // 0xC603_3034
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R02_O22A0_T    bnd_lbm_emmcpll_r02;    // 0xC603_3038
    UINT32                             _rsvd_03[1];             // 0xC603_303C
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R00_O22A0_T    bnd_lbm_codecpll_r00;    // 0xC603_3040
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R01_O22A0_T    bnd_lbm_codecpll_r01;    // 0xC603_3044
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R02_O22A0_T    bnd_lbm_codecpll_r02;    // 0xC603_3048
    BND_CTRL_LBM_SYN_TX_LO_DRV_00_O22A0_T    syn_tx_lo_drv_00;       // 0xC603_304C
    BND_CTRL_LBM_SYN_PLL_SEL_00_O22A0_T     syn_pll_sel_00;          // 0xC603_3050
    BND_CTRL_LBM_SYN_PLL_SEL_01_O22A0_T     syn_pll_sel_01;          // 0xC603_3054
    UINT32                             _rsvd_04[2];             // 0xC603_3058 ~ 0xC603_305C
    BND_CTRL_LBM_SYN_SWRST_00_O22A0_T       syn_swrst_00;            // 0xC603_3060
    BND_CTRL_LBM_SYN_SWRST_01_O22A0_T       syn_swrst_01;            // 0xC603_3064
    BND_CTRL_LBM_SYN_SWRST_02_O22A0_T       syn_swrst_02;            // 0xC603_3068
    BND_CTRL_LBM_SYN_SWRST_04_O22A0_T       syn_swrst_04;            // 0xC603_306C
    BND_CTRL_LBM_SYN_SWRST_05_O22A0_T       syn_swrst_05;            // 0xC603_3070
    BND_CTRL_LBM_SYN_SWRST_06_O22A0_T       syn_swrst_06;            // 0xC603_3074
    UINT32                             _rsvd_05[98];            // 0xC603_3078 ~ 0xC603_31FC
    BND_CTRL_LBM_SYN_BND_LBM_URART_MUX_R00_O22A0_T    bnd_lbm_urart_mux_r00;    // 0xC603_3200
    UINT32                             _rsvd_06[3];             // 0xC603_3204 ~ 0xC603_320C
    BND_CTRL_LBM_SYN_BND_LBM_JTAG_MUX_R00_O22A0_T    bnd_lbm_jtag_mux_r00;    // 0xC603_3210
    UINT32                             _rsvd_07[3];             // 0xC603_3214 ~ 0xC603_321C
    BND_CTRL_LBM_SYN_BND_LBM_URART_LOCK_R00_O22A0_T    bnd_lbm_urart_lock_r00;    // 0xC603_3220
    UINT32                             _rsvd_08[55];            // 0xC603_3224 ~ 0xC603_32FC
    BND_CTRL_LBM_SYN_BND_LBM_FT_MUX_R00_O22A0_T    bnd_lbm_ft_mux_r00;    // 0xC603_3300
    BND_CTRL_LBM_BND_VD1_R00_O22A0_T        bnd_vd1_r00;             // 0xC603_3304
    BND_CTRL_LBM_BND_VD1_R01_O22A0_T        bnd_vd1_r01;             // 0xC603_3308
}BND_CTRL_LBM_REG_O22A0_T;
/* 28 regs */

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

#define BND_CTRL_LBM_SYN_BND_LBM_RXCLK_MD_R00_O22A0_T_OFF            (BASEADDRESS+0x0000)
#define BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R00_O22A0_T_OFF              (BASEADDRESS+0x0010)
#define BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R01_O22A0_T_OFF              (BASEADDRESS+0x0014)
#define BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R02_O22A0_T_OFF              (BASEADDRESS+0x0018)
#define BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R00_O22A0_T_OFF             (BASEADDRESS+0x0020)
#define BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R01_O22A0_T_OFF             (BASEADDRESS+0x0024)
#define BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R02_O22A0_T_OFF             (BASEADDRESS+0x0028)
#define BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R00_O22A0_T_OFF             (BASEADDRESS+0x0030)
#define BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R01_O22A0_T_OFF             (BASEADDRESS+0x0034)
#define BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R02_O22A0_T_OFF             (BASEADDRESS+0x0038)
#define BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R00_O22A0_T_OFF            (BASEADDRESS+0x0040)
#define BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R01_O22A0_T_OFF            (BASEADDRESS+0x0044)
#define BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R02_O22A0_T_OFF            (BASEADDRESS+0x0048)
#define BND_CTRL_LBM_SYN_TX_LO_DRV_00_O22A0_T_OFF                (BASEADDRESS+0x004C)
#define BND_CTRL_LBM_SYN_PLL_SEL_00_O22A0_T_OFF                  (BASEADDRESS+0x0050)
#define BND_CTRL_LBM_SYN_PLL_SEL_01_O22A0_T_OFF                  (BASEADDRESS+0x0054)
#define BND_CTRL_LBM_SYN_SWRST_00_O22A0_T_OFF                    (BASEADDRESS+0x0060)
#define BND_CTRL_LBM_SYN_SWRST_01_O22A0_T_OFF                    (BASEADDRESS+0x0064)
#define BND_CTRL_LBM_SYN_SWRST_02_O22A0_T_OFF                    (BASEADDRESS+0x0068)
#define BND_CTRL_LBM_SYN_SWRST_04_O22A0_T_OFF                    (BASEADDRESS+0x006C)
#define BND_CTRL_LBM_SYN_SWRST_05_O22A0_T_OFF                    (BASEADDRESS+0x0070)
#define BND_CTRL_LBM_SYN_SWRST_06_O22A0_T_OFF                    (BASEADDRESS+0x0074)
#define BND_CTRL_LBM_SYN_BND_LBM_URART_MUX_R00_O22A0_T_OFF           (BASEADDRESS+0x0200)
#define BND_CTRL_LBM_SYN_BND_LBM_JTAG_MUX_R00_O22A0_T_OFF            (BASEADDRESS+0x0210)
#define BND_CTRL_LBM_SYN_BND_LBM_URART_LOCK_R00_O22A0_T_OFF          (BASEADDRESS+0x0220)
#define BND_CTRL_LBM_SYN_BND_LBM_FT_MUX_R00_O22A0_T_OFF              (BASEADDRESS+0x0300)
#define BND_CTRL_LBM_BND_VD1_R00_O22A0_T_OFF                     (BASEADDRESS+0x0304)
#define BND_CTRL_LBM_BND_VD1_R01_O22A0_T_OFF                     (BASEADDRESS+0x0308)

/*-----------------------------------------------------------------------------------------
    0xC603_3000    bnd_lbm_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_md_topplls_pdb: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_rxclkdrv_md_topplls_smv: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_rxclkdrv_md_m0_pdb: 1;    //    8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_rxclkdrv_md_m0_smv: 1;    //   12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3010    bnd_lbm_cpupll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_cih: 4;    //   3: 0
    UINT32 reg_cpu_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_cpu_aiopllss_fine_div: 1;    //  7
    UINT32 reg_cpu_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_cpu_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_cpu_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_cpu_aiopllss_m :  6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3014    bnd_lbm_cpupll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_cpu_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_cpu_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_cpu_aiopllss_dss: 1;    //     23
    UINT32 reg_cpu_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3018    bnd_lbm_cpupll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_freq_update: 1;    //  0
    UINT32 reg_cpu_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_cpu_aiopllss_lock: 1;    //     4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_cpu_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_cpu_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_cpu_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_cpu_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3020    bnd_lbm_corepll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_cih: 4;    //  3: 0
    UINT32 reg_core_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_core_aiopllss_fine_div: 1;    //  7
    UINT32 reg_core_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_core_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_core_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_core_aiopllss_m:  6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3024    bnd_lbm_corepll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_core_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_core_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_core_aiopllss_dss: 1;    //    23
    UINT32 reg_core_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3028    bnd_lbm_corepll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_freq_update: 1;    //  0
    UINT32 reg_core_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_core_aiopllss_lock: 1;    //    4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_core_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_core_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_core_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_core_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3030    bnd_lbm_emmcpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_cih: 4;    //  3: 0
    UINT32 reg_emmc_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_emmc_aiopllss_fine_div: 1;    //  7
    UINT32 reg_emmc_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_emmc_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_emmc_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_emmc_aiopllss_m:  6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3034    bnd_lbm_emmcpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_emmc_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_emmc_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_emmc_aiopllss_dss: 1;    //    23
    UINT32 reg_emmc_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3038    bnd_lbm_emmcpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_freq_update: 1;    //  0
    UINT32 reg_emmc_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_emmc_aiopllss_lock: 1;    //    4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_emmc_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_emmc_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_emmc_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_emmc_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3040    bnd_lbm_codecpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_cih: 4;    //  3:0
    UINT32 reg_codec_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_codec_aiopllss_fine_div: 1;    //  7
    UINT32 reg_codec_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_codec_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_codec_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_codec_aiopllss_m: 6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3044    bnd_lbm_codecpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_codec_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_codec_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_codec_aiopllss_dss: 1;    //   23
    UINT32 reg_codec_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3048    bnd_lbm_codecpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_freq_update: 1;    //  0
    UINT32 reg_codec_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_codec_aiopllss_lock: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_codec_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_codec_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_codec_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_codec_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_304C    syn_tx_lo_drv_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tx_lo_drv_nisol_top2m0_pdb: 1;    //  0
    UINT32 reg_tx_lo_drv_nisol_top2m0_ck_div: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_LBM_SYN_TX_LO_DRV_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3050    syn_pll_sel_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 22;    //  21: 0 reserved
    UINT32 reg_pll_sel_core960:  2;    //  23:22
    UINT32 reg_clk_sel_core960:  2;    //  25:24
    UINT32 reg_pll_sel_core600:  2;    //  27:26
    UINT32 reg_clk_sel_core600:  2;    //  29:28
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_PLL_SEL_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3054    syn_pll_sel_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_vdec660_3a_clk_gate_enb: 1;    //  1
    UINT32 reg_clk_sel_core660:  2;    //   3: 2
    UINT32 reg_clk_sel_core480:  2;    //   5: 4
    UINT32 reg_clk_sel_vdec660:  2;    //   7: 6
    UINT32 reg_clk_sel_core400:  2;    //   9: 8
    UINT32 reg_clk_sel_core533:  2;    //  11:10
    UINT32 reg_clk_sel_emmc400:  2;    //  13:12
    UINT32 reg_pll_sel_core800:  2;    //  15:14
    UINT32 reg_pll_sel_core660:  2;    //  17:16
    UINT32 reg_pll_sel_core480:  2;    //  19:18
    UINT32 resvd01            :  2;    //  21:20 reserved
    UINT32 reg_pll_sel_core400:  2;    //  23:22
    UINT32 reg_pll_sel_core533:  2;    //  25:24
    UINT32 reg_pll_sel_emmc400:  2;    //  27:26
    UINT32 reg_clk_sel_core800:  2;    //  29:28
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}BND_CTRL_LBM_SYN_PLL_SEL_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3060    syn_swrst_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  3;    //   2: 0 reserved
    UINT32 reg_swrst_cpuav_i_hdr: 1;    //     3
    UINT32 reg_swrst_cpuav_i_gpu_d100: 1;    //  4
    UINT32 resvd01            :  1;    //      5 reserved
    UINT32 reg_swrst_cpuav_i_vd3_d100: 1;    //  6
    UINT32 reg_swrst_cpuav_i_vd2_d100: 1;    //  7
    UINT32 reg_swrst_cpuav_i_vd1_d100: 1;    //  8
    UINT32 reg_swrst_cpuav_i_vd0_d100: 1;    //  9
    UINT32 reg_swrst_cpuav_i_m1_d100: 1;    //  10
    UINT32 reg_swrst_cpuav_i_m0_d100: 1;    //  11
    UINT32 reg_swrst_cpuav_i_lgsr_d100: 1;    //  12
    UINT32 reg_swrst_cpuav_i_lbm_d100: 1;    //  13
    UINT32 reg_swrst_cpuav_i_gem_d100: 1;    //  14
    UINT32 reg_swrst_cpuav_i_edid_d100: 1;    //  15
    UINT32 reg_swrst_cpuav_i_cpu_d100: 1;    //  16
    UINT32 reg_swrst_cpuav_i_bmc_d100: 1;    //  17
    UINT32 resvd02            :  1;    //     18 reserved
    UINT32 reg_swrst_cpuav_i_vd3: 1;    //    19
    UINT32 reg_swrst_cpuav_i_vd2: 1;    //    20
    UINT32 reg_swrst_cpuav_i_vd1: 1;    //    21
    UINT32 reg_swrst_cpuav_i_vd0: 1;    //    22
    UINT32 reg_swrst_cpuav_i_nd0: 1;    //    23
    UINT32 reg_swrst_cpuav_i_m1: 1;    //     24
    UINT32 reg_swrst_cpuav_i_m0: 1;    //     25
    UINT32 reg_swrst_cpuav_i_lgsr: 1;    //   26
    UINT32 reg_swrst_cpuav_i_lbm: 1;    //    27
    UINT32 reg_swrst_cpuav_i_gem: 1;    //    28
    UINT32 reg_swrst_cpuav_i_edid: 1;    //   29
    UINT32 reg_swrst_cpuav_i_cpu: 1;    //    30
    UINT32 reg_swrst_cpuav_i_bmc: 1;    //    31
    };
}BND_CTRL_LBM_SYN_SWRST_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3064    syn_swrst_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 20;    //  19: 0 reserved
    UINT32 reg_swrst_disp_i_nd1: 1;    //     20
    UINT32 reg_swrst_disp_i_nd0: 1;    //     21
    UINT32 reg_swrst_disp_i_me1: 1;    //     22
    UINT32 reg_swrst_disp_i_me0: 1;    //     23
    UINT32 reg_swrst_disp_i_imx: 1;    //     24
    UINT32 reg_swrst_disp_i_hdr: 1;    //     25
    UINT32 reg_swrst_disp_i_hdmi: 1;    //    26
    UINT32 reg_swrst_disp_i_fms: 1;    //     27
    UINT32 reg_swrst_disp_i_fmc: 1;    //     28
    UINT32 reg_swrst_disp_i_dpe: 1;    //     29
    UINT32 reg_swrst_disp_i_cvi: 1;    //     30
    UINT32 reg_swrst_disp_i_cco: 1;    //     31
    };
}BND_CTRL_LBM_SYN_SWRST_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3068    syn_swrst_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 20;    //  19: 0 reserved
    UINT32 reg_swrst_disp_i_nd1_d100: 1;    //  20
    UINT32 reg_swrst_disp_i_nd0_d100: 1;    //  21
    UINT32 reg_swrst_disp_i_me1_d100: 1;    //  22
    UINT32 reg_swrst_disp_i_me0_d100: 1;    //  23
    UINT32 reg_swrst_disp_i_imx_d100: 1;    //  24
    UINT32 reg_swrst_disp_i_hdr_d100: 1;    //  25
    UINT32 reg_swrst_disp_i_hdmi_d100: 1;    //  26
    UINT32 reg_swrst_disp_i_fms_d100: 1;    //  27
    UINT32 reg_swrst_disp_i_fmc_d100: 1;    //  28
    UINT32 reg_swrst_disp_i_dpe_d100: 1;    //  29
    UINT32 reg_swrst_disp_i_cvi_d100: 1;    //  30
    UINT32 reg_swrst_disp_i_cco_d100: 1;    //  31
    };
}BND_CTRL_LBM_SYN_SWRST_02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_306C    syn_swrst_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aadpll_pdb_ctrl:  1;    //      0
    UINT32 reg_gpupll_pdb_ctrl:  1;    //      1
    UINT32 reg_pqepll_pdb_ctrl:  1;    //      2
    UINT32 reg_displl_pdb_ctrl:  1;    //      3
    UINT32 reg_codecpll_ss_pdb_ctrl: 1;    //  4
    UINT32 reg_emmcpll_pdb_ctrl: 1;    //      5
    UINT32 reg_cpupll_pdb_ctrl:  1;    //      6
    UINT32 reg_codecpll_pdb_ctrl: 1;    //     7
    UINT32 reg_corepll_pdb_ctrl: 1;    //      8
    UINT32 reg_m1pll_pdb_ctrl :  1;    //      9
    UINT32 reg_m0pll_pdb_ctrl :  1;    //     10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}BND_CTRL_LBM_SYN_SWRST_04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3070    syn_swrst_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_spll_divint_mux_sel: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_LBM_SYN_SWRST_05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3074    syn_swrst_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nwd_reset_mux_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_LBM_SYN_SWRST_06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3200    bnd_lbm_urart_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel0 :  4;    //   3: 0
    UINT32 reg_main_uart_sel1 :  4;    //   7: 4
    UINT32 reg_main_uart_sel2 :  4;    //  11: 8
    UINT32 reg_main_uart_sel3 :  4;    //  15:12
    UINT32 reg_main_uart_sel4 :  4;    //  19:16
    UINT32 reg_monitor_sel_0  :  4;    //  23:20
    UINT32 reg_monitor_sel_1  :  4;    //  27:24
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_URART_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3210    bnd_lbm_jtag_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel0 :  4;    //   3: 0
    UINT32 reg_main_jtag_sel1 :  4;    //   7: 4
    UINT32 reg_main_jtag_sel2 :  4;    //  11: 8
    UINT32 reg_main_jtag_sel3 :  4;    //  15:12
    UINT32 reg_main_jtag_sel4 :  4;    //  19:16
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_JTAG_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3220    bnd_lbm_urart_lock_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_lock0:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_main_uart_lock1:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_main_uart_lock2:  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_main_uart_lock3:  1;    //     12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_main_uart_lock4:  1;    //     16
    UINT32 resvd04            : 15;    //  31:17 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_URART_LOCK_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3300    bnd_lbm_ft_mux_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 main_debug_jtag_sel:  1;    //      1
    UINT32 regmod_ts          :  1;    //      2
    UINT32 regmod_saradc_wov  :  1;    //      3
    UINT32 regmod_pvm         :  1;    //      4
    UINT32 regmod_hdmi_isol   :  1;    //      5
    UINT32 regmod_hdmi_earc   :  1;    //      6
    UINT32 regmod_ethernet    :  1;    //      7
    UINT32 regmod_c4tx_isol   :  1;    //      8
    UINT32 regmod_c4tx_bist   :  1;    //      9
    UINT32 regmod_acodec      :  1;    //     10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}BND_CTRL_LBM_SYN_BND_LBM_FT_MUX_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3304    bnd_vd1_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_npwrup_sram:  8;    //   7: 0
    UINT32 reg_vd1_pwrup      :  4;    //  11: 8
    UINT32 reg_vd1_pwrup_ack  :  4;    //  15:12
    UINT32 reg_vd1_nisol_en   :  1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}BND_CTRL_LBM_BND_VD1_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC603_3308    bnd_vd1_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_apb_auto_resp_disable: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_LBM_BND_VD1_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LBM_SYN_BND_LBM_RXCLK_MD_R00_O22A0_T    bnd_lbm_rxclk_md_r00;    // 0xC603_3000
    UINT32                             _rsvd_00[3];             // 0xC603_3004 ~ 0xC603_300C
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R00_O22A0_T    bnd_lbm_cpupll_r00;    // 0xC603_3010
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R01_O22A0_T    bnd_lbm_cpupll_r01;    // 0xC603_3014
    BND_CTRL_LBM_SYN_BND_LBM_CPUPLL_R02_O22A0_T    bnd_lbm_cpupll_r02;    // 0xC603_3018
    UINT32                             _rsvd_01[1];             // 0xC603_301C
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R00_O22A0_T    bnd_lbm_corepll_r00;    // 0xC603_3020
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R01_O22A0_T    bnd_lbm_corepll_r01;    // 0xC603_3024
    BND_CTRL_LBM_SYN_BND_LBM_COREPLL_R02_O22A0_T    bnd_lbm_corepll_r02;    // 0xC603_3028
    UINT32                             _rsvd_02[1];             // 0xC603_302C
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R00_O22A0_T    bnd_lbm_emmcpll_r00;    // 0xC603_3030
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R01_O22A0_T    bnd_lbm_emmcpll_r01;    // 0xC603_3034
    BND_CTRL_LBM_SYN_BND_LBM_EMMCPLL_R02_O22A0_T    bnd_lbm_emmcpll_r02;    // 0xC603_3038
    UINT32                             _rsvd_03[1];             // 0xC603_303C
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R00_O22A0_T    bnd_lbm_codecpll_r00;    // 0xC603_3040
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R01_O22A0_T    bnd_lbm_codecpll_r01;    // 0xC603_3044
    BND_CTRL_LBM_SYN_BND_LBM_CODECPLL_R02_O22A0_T    bnd_lbm_codecpll_r02;    // 0xC603_3048
    BND_CTRL_LBM_SYN_TX_LO_DRV_00_O22A0_T    syn_tx_lo_drv_00;       // 0xC603_304C
    BND_CTRL_LBM_SYN_PLL_SEL_00_O22A0_T     syn_pll_sel_00;          // 0xC603_3050
    BND_CTRL_LBM_SYN_PLL_SEL_01_O22A0_T     syn_pll_sel_01;          // 0xC603_3054
    UINT32                             _rsvd_04[2];             // 0xC603_3058 ~ 0xC603_305C
    BND_CTRL_LBM_SYN_SWRST_00_O22A0_T       syn_swrst_00;            // 0xC603_3060
    BND_CTRL_LBM_SYN_SWRST_01_O22A0_T       syn_swrst_01;            // 0xC603_3064
    BND_CTRL_LBM_SYN_SWRST_02_O22A0_T       syn_swrst_02;            // 0xC603_3068
    BND_CTRL_LBM_SYN_SWRST_04_O22A0_T       syn_swrst_04;            // 0xC603_306C
    BND_CTRL_LBM_SYN_SWRST_05_O22A0_T       syn_swrst_05;            // 0xC603_3070
    BND_CTRL_LBM_SYN_SWRST_06_O22A0_T       syn_swrst_06;            // 0xC603_3074
    UINT32                             _rsvd_05[98];            // 0xC603_3078 ~ 0xC603_31FC
    BND_CTRL_LBM_SYN_BND_LBM_URART_MUX_R00_O22A0_T    bnd_lbm_urart_mux_r00;    // 0xC603_3200
    UINT32                             _rsvd_06[3];             // 0xC603_3204 ~ 0xC603_320C
    BND_CTRL_LBM_SYN_BND_LBM_JTAG_MUX_R00_O22A0_T    bnd_lbm_jtag_mux_r00;    // 0xC603_3210
    UINT32                             _rsvd_07[3];             // 0xC603_3214 ~ 0xC603_321C
    BND_CTRL_LBM_SYN_BND_LBM_URART_LOCK_R00_O22A0_T    bnd_lbm_urart_lock_r00;    // 0xC603_3220
    UINT32                             _rsvd_08[55];            // 0xC603_3224 ~ 0xC603_32FC
    BND_CTRL_LBM_SYN_BND_LBM_FT_MUX_R00_O22A0_T    bnd_lbm_ft_mux_r00;    // 0xC603_3300
    BND_CTRL_LBM_BND_VD1_R00_O22A0_T        bnd_vd1_r00;             // 0xC603_3304
    BND_CTRL_LBM_BND_VD1_R01_O22A0_T        bnd_vd1_r01;             // 0xC603_3308
}BND_CTRL_LBM_REG_O22A0_T;
/* 28 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_LBM_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

