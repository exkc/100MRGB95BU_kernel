#ifndef _BND_CTRL_DPE_REG_H_
#define _BND_CTRL_DPE_REG_H_

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
    0xCC43_2000    bnd_dpe_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_intr_edge_en_rise: 1,    //     0
    reg_c4_vx1_intr_clear_rise:  1,    //      1
    reg_c4_vx1_lockn_intr_en_rise: 1,    //    2
                              :  5,    //   7: 3 reserved
    reg_c4_vx1_intr_edge_en_fall: 1,    //     8
    reg_c4_vx1_intr_clear_fall:  1,    //      9
    reg_c4_vx1_lockn_intr_en_fall: 1,    //   10
                              : 21;    //  31:11 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2004    bnd_dpe_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_main_counter: 4,    //  3:0
    reg_c4_vx1_lockn_main_counter_clear: 1,    //  4
    reg_c4_vx1_lockn_main_counter_rising_edge: 1,    //  5
                              : 26;    //   31:6 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2008    bnd_dpe_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ext_reg_wrdata     :  8,    //   7: 0
    reg_c4_ext_reg_addr       :  8,    //  15: 8
    reg_c4_ext_reg_wren       :  1,    //     16
                              : 15;    //  31:17 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_200C    bnd_dpe_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link0_ext_reg_en   :  1,    //      0
    reg_c4_link1_ext_reg_en   :  1,    //      1
    reg_c4_link2_ext_reg_en   :  1,    //      2
    reg_c4_link3_ext_reg_en   :  1,    //      3
    reg_c4_link4_ext_reg_en   :  1,    //      4
    reg_c4_link5_ext_reg_en   :  1,    //      5
    reg_c4_pll_ext_reg_en     :  1,    //      6
                              : 25;    //   31:7 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2010    bnd_dpe_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb_ch0            :  1,    //      0
    reg_c4_pdb_ch1            :  1,    //      1
    reg_c4_pdb_ch2            :  1,    //      2
    reg_c4_pdb_ch3            :  1,    //      3
    reg_c4_pdb_ch4            :  1,    //      4
    reg_c4_pdb_ch5            :  1,    //      5
    reg_c4_pdb_ch6            :  1,    //      6
    reg_c4_pdb_ch7            :  1,    //      7
    reg_c4_pdb_ch8            :  1,    //      8
    reg_c4_pdb_ch9            :  1,    //      9
    reg_c4_pdb_ch10           :  1,    //     10
    reg_c4_pdb_ch11           :  1,    //     11
    reg_c4_pdb_ch12           :  1,    //     12
    reg_c4_pdb_ch13           :  1,    //     13
    reg_c4_pdb_ch14           :  1,    //     14
    reg_c4_pdb_ch15           :  1,    //     15
    reg_c4_pdb_ch16           :  1,    //     16
    reg_c4_pdb_ch17           :  1,    //     17
    reg_c4_pdb_ch18           :  1,    //     18
    reg_c4_pdb_ch19           :  1,    //     19
    reg_c4_pdb_ch20           :  1,    //     20
    reg_c4_pdb_ch21           :  1,    //     21
    reg_c4_pdb_ch22           :  1,    //     22
    reg_c4_pdb_ch23           :  1,    //     23
                              :  8;    //  31:24 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2014    bnd_dpe_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_rstn_vtxlink       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_clk_sel               :  1,    //      8
                              : 19,    //  27: 9 reserved
    reg_c4_ext_reg_rstb       :  1,    //     28
                              :  3;    //  31:29 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2018    bnd_dpe_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link0_ext_reg_rddata: 8,    //   7: 0
    reg_c4_link1_ext_reg_rddata: 8,    //  15: 8
    reg_c4_link2_ext_reg_rddata: 8,    //  23:16
    reg_c4_link3_ext_reg_rddata: 8;    //  31:24
}BND_CTRL_DPE_SYN_BND_DPE_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_201C    pqe_frpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link4_ext_reg_rddata: 8,    //   7: 0
    reg_c4_link5_ext_reg_rddata: 8,    //  15: 8
                              : 16;    //  31:16 reserved
}BND_CTRL_DPE_PQE_FRPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2020    bnd_dpe_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pll_ext_reg_rddata :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2024    bnd_dpe_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_tomain   :  1,    //      0
                              : 15,    //  15: 1 reserved
    reg_c4_epi_lock_tomain    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_c4_pll_rstb_g         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_c4_pll_lock           :  1,    //     24
                              :  7;    //  31:25 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2028    bnd_dpe_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di5               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_202C    bnd_dpe_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di4               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2030    bnd_dpe_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di3               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2034    bnd_dpe_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di2               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2038    bnd_dpe_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di1               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_203C    bnd_dpe_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di0               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2040    bnd_dpe_r15 ''
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
}BND_CTRL_DPE_SYN_BND_DPE_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2044    bnd_dpe_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sel_mode           :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2048    bnd_dpe_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mon_led1                  :  8,    //   7: 0
    mon_led0                  :  8,    //  15: 8
                              : 16;    //  31:16 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_204C    bnd_dpe_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mon_tcon                  :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}BND_CTRL_DPE_SYN_BND_DPE_R18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2050    pqe_frpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f54pll_frpll_fout_en  :  1,    //      0
    reg_f54pll_frpll_syncon   :  1,    //      1
    reg_f54pll_frpll_m        :  6,    //   7: 2
    reg_f54pll_frpll_fcw      : 24;    //  31: 8
}BND_CTRL_DPE_PQE_FRPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2054    pqe_frpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f54pll_frpll_lock     :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_f54pll_frpll_frequp   :  1,    //     23
    reg_f54pll_frpll_a        :  6,    //  29:24
    reg_f54pll_frpll_in_divrstb: 1,    //     30
    reg_f54pll_frpll_icp_g    :  1;    //     31
}BND_CTRL_DPE_PQE_FRPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2058    disp_aiopll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopll_cih       :  4,    //   3: 0
    reg_disp_aiopll_fine_control: 3,    //  6: 4
                              :  1,    //      7 reserved
    reg_disp_aiopll_fine_div  :  1,    //      8
    reg_disp_aiopll_fout_od   :  2,    //  10: 9
                              :  1,    //     11 reserved
    reg_disp_aiopll_nsc       :  4,    //  15:12
    reg_disp_aiopll_npc       :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_disp_aiopll_m         :  6,    //  29:24
                              :  1,    //     30 reserved
    reg_disp_aiopll_out_sel   :  1;    //     31
}BND_CTRL_DPE_DISP_AIOPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_205C    disp_aiopll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopll_mod_freq_max: 9,    //  8: 0
                              :  3,    //  11: 9 reserved
    reg_disp_aiopll_updn_max  :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_disp_aiopll_accuracy  :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_disp_aiopll_dss       :  1,    //     23
    reg_disp_aiopll_offset    :  8;    //  31:24
}BND_CTRL_DPE_DISP_AIOPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2060    disp_aiopll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopll_freq_update: 1,    //      0
    reg_disp_aiopll_lock      :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_disp_aiopll_fout3_post_od: 3,    //  6:4
                              :  5,    //  11: 7 reserved
    reg_disp_aiopll_fout3_pre_od: 3,    //  14:12
                              :  1,    //     15 reserved
    reg_disp_aiopll_fout2_post_od: 3,    //  18:16
                              :  1,    //     19 reserved
    reg_disp_aiopll_fout2_pre_od: 3,    //  22:20
                              :  1,    //     23 reserved
    reg_disp_aiopll_sync_on   :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_disp_aiopll_wake_bypass: 1,    //     27
    reg_disp_aiopll_offset_mode: 1,    //     28
                              :  2,    //  30:29 reserved
    reg_disp_aiopll_ddr_mode  :  1;    //     31
}BND_CTRL_DPE_DISP_AIOPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2064    gpu_aiopllss_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_cih      :  4,    //   3: 0
    reg_gpu_aiopllss_fine_control: 3,    //  6:4
    reg_gpu_aiopllss_fine_div :  1,    //      7
    reg_gpu_aiopllss_cih2     :  4,    //  11: 8
    reg_gpu_aiopllss_nsc      :  4,    //  15:12
    reg_gpu_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_gpu_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_DPE_GPU_AIOPLLSS_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2068    gpu_aiopllss_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_mod_freq_max: 9,    //  8:0
                              :  3,    //  11: 9 reserved
    reg_gpu_aiopllss_updn_max :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_gpu_aiopllss_accuracy :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_gpu_aiopllss_dss      :  1,    //     23
    reg_gpu_aiopllss_offset   :  8;    //  31:24
}BND_CTRL_DPE_GPU_AIOPLLSS_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_206C    gpu_aiopllss_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_freq_update: 1,    //     0
    reg_gpu_aiopllss_fout1_en :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_gpu_aiopllss_lock     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_gpu_aiopllss_out_div  :  7,    //  14: 8
                              :  9,    //  23:15 reserved
    reg_gpu_aiopllss_sync_on  :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_gpu_aiopllss_wake_bypass: 1,    //    27
    reg_gpu_aiopllss_offset_mode: 1,    //    28
                              :  3;    //  31:29 reserved
}BND_CTRL_DPE_GPU_AIOPLLSS_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2070    pqe_frpll_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopll_in_sel    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pqepll_fcw_mux_sel    :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_pqepll_divint_mux_sel :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}BND_CTRL_DPE_PQE_FRPLL_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2074    pqe_frpll_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpll_mon_en           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_disp594_clk_gate_en   :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_DPE_PQE_FRPLL_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2078    pqe_frpll_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqepll_frpll_out3_div :  9,    //   8: 0
                              :  3,    //  11: 9 reserved
    reg_pqepll_frpll_out2_div :  9,    //  20:12
                              : 11;    //  31:21 reserved
}BND_CTRL_DPE_PQE_FRPLL_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_207C    pqe_frpll_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pqepll_frpll_in_divsel:  1,    //      1
    reg_pqepll_frpll_lpf_on   :  1,    //      2
    reg_pqepll_frpll_fout2_en :  1,    //      3
    reg_pqepll_frpll_wakeup_bypass: 1,    //   4
    reg_pqepll_frpll_divint   :  9,    //  13: 5
                              :  1,    //     14 reserved
    reg_pqepll_frpll_dsmon    :  1,    //     15
    reg_pqepll_frpll_auto_freq:  1,    //     16
    reg_pqepll_frpll_dsm_limit:  1,    //     17
    reg_pqepll_frpll_fin_sel  :  1,    //     18
    reg_pqepll_frpll_icp      :  4,    //  22:19
    reg_pqepll_frpll_out_div  :  9;    //  31:23
}BND_CTRL_DPE_PQE_FRPLL_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2080    pqe_frpll_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqepll_frpll_fout_en  :  1,    //      0
    reg_pqepll_frpll_syncon   :  1,    //      1
    reg_pqepll_frpll_m        :  6,    //   7: 2
    reg_pqepll_frpll_fcw      : 24;    //  31: 8
}BND_CTRL_DPE_PQE_FRPLL_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2084    pqe_frpll_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqepll_frpll_lock     :  1,    //      0
                              : 22,    //  22: 1 reserved
    reg_pqepll_frpll_frequp   :  1,    //     23
    reg_pqepll_frpll_a        :  6,    //  29:24
    reg_pqepll_frpll_in_divrstb: 1,    //     30
    reg_pqepll_frpll_icp_g    :  1;    //     31
}BND_CTRL_DPE_PQE_FRPLL_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2088    rxclk_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    reg_rxclkdrv_smv          :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_DPE_RXCLK_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_208C    tx_lo_drv_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tx_lo_drv_pdb         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tx_lo_drv_ck_div      :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_DPE_TX_LO_DRV_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2090    pat_gen_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pat_gen_en            :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pat_gen               :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_DPE_PAT_GEN_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_DPE_SYN_BND_DPE_R00_O22A0_T        bnd_dpe_r00;             // 0xCC43_2000
    BND_CTRL_DPE_SYN_BND_DPE_R01_O22A0_T        bnd_dpe_r01;             // 0xCC43_2004
    BND_CTRL_DPE_SYN_BND_DPE_R02_O22A0_T        bnd_dpe_r02;             // 0xCC43_2008
    BND_CTRL_DPE_SYN_BND_DPE_R03_O22A0_T        bnd_dpe_r03;             // 0xCC43_200C
    BND_CTRL_DPE_SYN_BND_DPE_R04_O22A0_T        bnd_dpe_r04;             // 0xCC43_2010
    BND_CTRL_DPE_SYN_BND_DPE_R05_O22A0_T        bnd_dpe_r05;             // 0xCC43_2014
    BND_CTRL_DPE_SYN_BND_DPE_R06_O22A0_T        bnd_dpe_r06;             // 0xCC43_2018
    BND_CTRL_DPE_PQE_FRPLL_R00_O22A0_T      pqe_frpll_r00;           // 0xCC43_201C
    BND_CTRL_DPE_SYN_BND_DPE_R07_O22A0_T        bnd_dpe_r07;             // 0xCC43_2020
    BND_CTRL_DPE_SYN_BND_DPE_R08_O22A0_T        bnd_dpe_r08;             // 0xCC43_2024
    BND_CTRL_DPE_SYN_BND_DPE_R09_O22A0_T        bnd_dpe_r09;             // 0xCC43_2028
    BND_CTRL_DPE_SYN_BND_DPE_R10_O22A0_T        bnd_dpe_r10;             // 0xCC43_202C
    BND_CTRL_DPE_SYN_BND_DPE_R11_O22A0_T        bnd_dpe_r11;             // 0xCC43_2030
    BND_CTRL_DPE_SYN_BND_DPE_R12_O22A0_T        bnd_dpe_r12;             // 0xCC43_2034
    BND_CTRL_DPE_SYN_BND_DPE_R13_O22A0_T        bnd_dpe_r13;             // 0xCC43_2038
    BND_CTRL_DPE_SYN_BND_DPE_R14_O22A0_T        bnd_dpe_r14;             // 0xCC43_203C
    BND_CTRL_DPE_SYN_BND_DPE_R15_O22A0_T        bnd_dpe_r15;             // 0xCC43_2040
    BND_CTRL_DPE_SYN_BND_DPE_R16_O22A0_T        bnd_dpe_r16;             // 0xCC43_2044
    BND_CTRL_DPE_SYN_BND_DPE_R17_O22A0_T        bnd_dpe_r17;             // 0xCC43_2048
    BND_CTRL_DPE_SYN_BND_DPE_R18_O22A0_T        bnd_dpe_r18;             // 0xCC43_204C
    BND_CTRL_DPE_PQE_FRPLL_R01_O22A0_T      pqe_frpll_r01;           // 0xCC43_2050
    BND_CTRL_DPE_PQE_FRPLL_R02_O22A0_T      pqe_frpll_r02;           // 0xCC43_2054
    BND_CTRL_DPE_DISP_AIOPLL_R00_O22A0_T    disp_aiopll_r00;         // 0xCC43_2058
    BND_CTRL_DPE_DISP_AIOPLL_R01_O22A0_T    disp_aiopll_r01;         // 0xCC43_205C
    BND_CTRL_DPE_DISP_AIOPLL_R02_O22A0_T    disp_aiopll_r02;         // 0xCC43_2060
    BND_CTRL_DPE_GPU_AIOPLLSS_R00_O22A0_T    gpu_aiopllss_r00;       // 0xCC43_2064
    BND_CTRL_DPE_GPU_AIOPLLSS_R01_O22A0_T    gpu_aiopllss_r01;       // 0xCC43_2068
    BND_CTRL_DPE_GPU_AIOPLLSS_R02_O22A0_T    gpu_aiopllss_r02;       // 0xCC43_206C
    BND_CTRL_DPE_PQE_FRPLL_R03_O22A0_T      pqe_frpll_r03;           // 0xCC43_2070
    BND_CTRL_DPE_PQE_FRPLL_R04_O22A0_T      pqe_frpll_r04;           // 0xCC43_2074
    BND_CTRL_DPE_PQE_FRPLL_R07_O22A0_T      pqe_frpll_r07;           // 0xCC43_2078
    BND_CTRL_DPE_PQE_FRPLL_R08_O22A0_T      pqe_frpll_r08;           // 0xCC43_207C
    BND_CTRL_DPE_PQE_FRPLL_R09_O22A0_T      pqe_frpll_r09;           // 0xCC43_2080
    BND_CTRL_DPE_PQE_FRPLL_R10_O22A0_T      pqe_frpll_r10;           // 0xCC43_2084
    BND_CTRL_DPE_RXCLK_R00_O22A0_T          rxclk_r00  ;             // 0xCC43_2088
    BND_CTRL_DPE_TX_LO_DRV_R00_O22A0_T      tx_lo_drv_r00;           // 0xCC43_208C
    BND_CTRL_DPE_PAT_GEN_R00_O22A0_T        pat_gen_r00;             // 0xCC43_2090
}BND_CTRL_DPE_REG_O22A0_T;
/* 37 regs */

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

#define BND_CTRL_DPE_SYN_BND_DPE_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_DPE_SYN_BND_DPE_R01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define BND_CTRL_DPE_SYN_BND_DPE_R02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define BND_CTRL_DPE_SYN_BND_DPE_R03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define BND_CTRL_DPE_SYN_BND_DPE_R04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define BND_CTRL_DPE_SYN_BND_DPE_R05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define BND_CTRL_DPE_SYN_BND_DPE_R06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define BND_CTRL_DPE_PQE_FRPLL_R00_O22A0_T_OFF                   (BASEADDRESS+0x001C)
#define BND_CTRL_DPE_SYN_BND_DPE_R07_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define BND_CTRL_DPE_SYN_BND_DPE_R08_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define BND_CTRL_DPE_SYN_BND_DPE_R09_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define BND_CTRL_DPE_SYN_BND_DPE_R10_O22A0_T_OFF                     (BASEADDRESS+0x002C)
#define BND_CTRL_DPE_SYN_BND_DPE_R11_O22A0_T_OFF                     (BASEADDRESS+0x0030)
#define BND_CTRL_DPE_SYN_BND_DPE_R12_O22A0_T_OFF                     (BASEADDRESS+0x0034)
#define BND_CTRL_DPE_SYN_BND_DPE_R13_O22A0_T_OFF                     (BASEADDRESS+0x0038)
#define BND_CTRL_DPE_SYN_BND_DPE_R14_O22A0_T_OFF                     (BASEADDRESS+0x003C)
#define BND_CTRL_DPE_SYN_BND_DPE_R15_O22A0_T_OFF                     (BASEADDRESS+0x0040)
#define BND_CTRL_DPE_SYN_BND_DPE_R16_O22A0_T_OFF                     (BASEADDRESS+0x0044)
#define BND_CTRL_DPE_SYN_BND_DPE_R17_O22A0_T_OFF                     (BASEADDRESS+0x0048)
#define BND_CTRL_DPE_SYN_BND_DPE_R18_O22A0_T_OFF                     (BASEADDRESS+0x004C)
#define BND_CTRL_DPE_PQE_FRPLL_R01_O22A0_T_OFF                   (BASEADDRESS+0x0050)
#define BND_CTRL_DPE_PQE_FRPLL_R02_O22A0_T_OFF                   (BASEADDRESS+0x0054)
#define BND_CTRL_DPE_DISP_AIOPLL_R00_O22A0_T_OFF                 (BASEADDRESS+0x0058)
#define BND_CTRL_DPE_DISP_AIOPLL_R01_O22A0_T_OFF                 (BASEADDRESS+0x005C)
#define BND_CTRL_DPE_DISP_AIOPLL_R02_O22A0_T_OFF                 (BASEADDRESS+0x0060)
#define BND_CTRL_DPE_GPU_AIOPLLSS_R00_O22A0_T_OFF                (BASEADDRESS+0x0064)
#define BND_CTRL_DPE_GPU_AIOPLLSS_R01_O22A0_T_OFF                (BASEADDRESS+0x0068)
#define BND_CTRL_DPE_GPU_AIOPLLSS_R02_O22A0_T_OFF                (BASEADDRESS+0x006C)
#define BND_CTRL_DPE_PQE_FRPLL_R03_O22A0_T_OFF                   (BASEADDRESS+0x0070)
#define BND_CTRL_DPE_PQE_FRPLL_R04_O22A0_T_OFF                   (BASEADDRESS+0x0074)
#define BND_CTRL_DPE_PQE_FRPLL_R07_O22A0_T_OFF                   (BASEADDRESS+0x0078)
#define BND_CTRL_DPE_PQE_FRPLL_R08_O22A0_T_OFF                   (BASEADDRESS+0x007C)
#define BND_CTRL_DPE_PQE_FRPLL_R09_O22A0_T_OFF                   (BASEADDRESS+0x0080)
#define BND_CTRL_DPE_PQE_FRPLL_R10_O22A0_T_OFF                   (BASEADDRESS+0x0084)
#define BND_CTRL_DPE_RXCLK_R00_O22A0_T_OFF                       (BASEADDRESS+0x0088)
#define BND_CTRL_DPE_TX_LO_DRV_R00_O22A0_T_OFF                   (BASEADDRESS+0x008C)
#define BND_CTRL_DPE_PAT_GEN_R00_O22A0_T_OFF                     (BASEADDRESS+0x0090)

/*-----------------------------------------------------------------------------------------
    0xCC43_2000    bnd_dpe_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_intr_edge_en_rise: 1;    //  0
    UINT32 reg_c4_vx1_intr_clear_rise: 1;    //  1
    UINT32 reg_c4_vx1_lockn_intr_en_rise: 1;    //  2
    UINT32 resvd00            :  5;    //   7: 3 reserved
    UINT32 reg_c4_vx1_intr_edge_en_fall: 1;    //  8
    UINT32 reg_c4_vx1_intr_clear_fall: 1;    //  9
    UINT32 reg_c4_vx1_lockn_intr_en_fall: 1;    //  10
    UINT32 resvd01            : 21;    //  31:11 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2004    bnd_dpe_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_lockn_main_counter: 4;    //  3:0
    UINT32 reg_c4_vx1_lockn_main_counter_clear: 1;    //  4
    UINT32 reg_c4_vx1_lockn_main_counter_rising_edge: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2008    bnd_dpe_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_ext_reg_wrdata: 8;    //  7: 0
    UINT32 reg_c4_ext_reg_addr:  8;    //  15: 8
    UINT32 reg_c4_ext_reg_wren:  1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_200C    bnd_dpe_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link0_ext_reg_en: 1;    //   0
    UINT32 reg_c4_link1_ext_reg_en: 1;    //   1
    UINT32 reg_c4_link2_ext_reg_en: 1;    //   2
    UINT32 reg_c4_link3_ext_reg_en: 1;    //   3
    UINT32 reg_c4_link4_ext_reg_en: 1;    //   4
    UINT32 reg_c4_link5_ext_reg_en: 1;    //   5
    UINT32 reg_c4_pll_ext_reg_en: 1;    //     6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2010    bnd_dpe_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pdb_ch0     :  1;    //      0
    UINT32 reg_c4_pdb_ch1     :  1;    //      1
    UINT32 reg_c4_pdb_ch2     :  1;    //      2
    UINT32 reg_c4_pdb_ch3     :  1;    //      3
    UINT32 reg_c4_pdb_ch4     :  1;    //      4
    UINT32 reg_c4_pdb_ch5     :  1;    //      5
    UINT32 reg_c4_pdb_ch6     :  1;    //      6
    UINT32 reg_c4_pdb_ch7     :  1;    //      7
    UINT32 reg_c4_pdb_ch8     :  1;    //      8
    UINT32 reg_c4_pdb_ch9     :  1;    //      9
    UINT32 reg_c4_pdb_ch10    :  1;    //     10
    UINT32 reg_c4_pdb_ch11    :  1;    //     11
    UINT32 reg_c4_pdb_ch12    :  1;    //     12
    UINT32 reg_c4_pdb_ch13    :  1;    //     13
    UINT32 reg_c4_pdb_ch14    :  1;    //     14
    UINT32 reg_c4_pdb_ch15    :  1;    //     15
    UINT32 reg_c4_pdb_ch16    :  1;    //     16
    UINT32 reg_c4_pdb_ch17    :  1;    //     17
    UINT32 reg_c4_pdb_ch18    :  1;    //     18
    UINT32 reg_c4_pdb_ch19    :  1;    //     19
    UINT32 reg_c4_pdb_ch20    :  1;    //     20
    UINT32 reg_c4_pdb_ch21    :  1;    //     21
    UINT32 reg_c4_pdb_ch22    :  1;    //     22
    UINT32 reg_c4_pdb_ch23    :  1;    //     23
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2014    bnd_dpe_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pdb         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_c4_rstn_vtxlink:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_clk_sel        :  1;    //      8
    UINT32 resvd02            : 19;    //  27: 9 reserved
    UINT32 reg_c4_ext_reg_rstb:  1;    //     28
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2018    bnd_dpe_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link0_ext_reg_rddata: 8;    //  7:0
    UINT32 reg_c4_link1_ext_reg_rddata: 8;    //  15:8
    UINT32 reg_c4_link2_ext_reg_rddata: 8;    //  23:16
    UINT32 reg_c4_link3_ext_reg_rddata: 8;    //  31:24
    };
}BND_CTRL_DPE_SYN_BND_DPE_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_201C    pqe_frpll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link4_ext_reg_rddata: 8;    //  7:0
    UINT32 reg_c4_link5_ext_reg_rddata: 8;    //  15:8
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}BND_CTRL_DPE_PQE_FRPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2020    bnd_dpe_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pll_ext_reg_rddata: 8;    //  7:0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2024    bnd_dpe_r08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_lockn_tomain: 1;    //   0
    UINT32 resvd00            : 15;    //  15: 1 reserved
    UINT32 reg_c4_epi_lock_tomain: 1;    //   16
    UINT32 resvd01            :  3;    //  19:17 reserved
    UINT32 reg_c4_pll_rstb_g  :  1;    //     20
    UINT32 resvd02            :  3;    //  23:21 reserved
    UINT32 reg_c4_pll_lock    :  1;    //     24
    UINT32 resvd03            :  7;    //  31:25 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2028    bnd_dpe_r09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di5        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_202C    bnd_dpe_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di4        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2030    bnd_dpe_r11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di3        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2034    bnd_dpe_r12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di2        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2038    bnd_dpe_r13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di1        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_203C    bnd_dpe_r14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_test_di0        : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2040    bnd_dpe_r15 ''
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
}BND_CTRL_DPE_SYN_BND_DPE_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2044    bnd_dpe_r16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_sel_mode    :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2048    bnd_dpe_r17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 mon_led1           :  8;    //   7: 0
    UINT32 mon_led0           :  8;    //  15: 8
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_204C    bnd_dpe_r18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 mon_tcon           :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_DPE_SYN_BND_DPE_R18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2050    pqe_frpll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f54pll_frpll_fout_en: 1;    //  0
    UINT32 reg_f54pll_frpll_syncon: 1;    //   1
    UINT32 reg_f54pll_frpll_m :  6;    //   7: 2
    UINT32 reg_f54pll_frpll_fcw: 24;    //  31:8
    };
}BND_CTRL_DPE_PQE_FRPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2054    pqe_frpll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f54pll_frpll_lock: 1;    //     0
    UINT32 resvd00            : 22;    //  22: 1 reserved
    UINT32 reg_f54pll_frpll_frequp: 1;    //  23
    UINT32 reg_f54pll_frpll_a :  6;    //  29:24
    UINT32 reg_f54pll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_f54pll_frpll_icp_g: 1;    //   31
    };
}BND_CTRL_DPE_PQE_FRPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2058    disp_aiopll_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopll_cih:  4;    //   3: 0
    UINT32 reg_disp_aiopll_fine_control: 3;    //  6:4
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_disp_aiopll_fine_div: 1;    //  8
    UINT32 reg_disp_aiopll_fout_od: 2;    //  10:9
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_disp_aiopll_nsc:  4;    //  15:12
    UINT32 reg_disp_aiopll_npc:  6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_disp_aiopll_m  :  6;    //  29:24
    UINT32 resvd03            :  1;    //     30 reserved
    UINT32 reg_disp_aiopll_out_sel: 1;    //  31
    };
}BND_CTRL_DPE_DISP_AIOPLL_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_205C    disp_aiopll_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopll_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_disp_aiopll_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_disp_aiopll_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_disp_aiopll_dss:  1;    //     23
    UINT32 reg_disp_aiopll_offset: 8;    //  31:24
    };
}BND_CTRL_DPE_DISP_AIOPLL_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2060    disp_aiopll_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopll_freq_update: 1;    //  0
    UINT32 reg_disp_aiopll_lock: 1;    //      1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_disp_aiopll_fout3_post_od: 3;    //  6:4
    UINT32 resvd01            :  5;    //  11: 7 reserved
    UINT32 reg_disp_aiopll_fout3_pre_od: 3;    //  14:12
    UINT32 resvd02            :  1;    //     15 reserved
    UINT32 reg_disp_aiopll_fout2_post_od: 3;    //  18:16
    UINT32 resvd03            :  1;    //     19 reserved
    UINT32 reg_disp_aiopll_fout2_pre_od: 3;    //  22:20
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 reg_disp_aiopll_sync_on: 1;    //  24
    UINT32 resvd05            :  2;    //  26:25 reserved
    UINT32 reg_disp_aiopll_wake_bypass: 1;    //  27
    UINT32 reg_disp_aiopll_offset_mode: 1;    //  28
    UINT32 resvd06            :  2;    //  30:29 reserved
    UINT32 reg_disp_aiopll_ddr_mode: 1;    //  31
    };
}BND_CTRL_DPE_DISP_AIOPLL_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2064    gpu_aiopllss_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_cih: 4;    //   3: 0
    UINT32 reg_gpu_aiopllss_fine_control: 3;    //  6:4
    UINT32 reg_gpu_aiopllss_fine_div: 1;    //  7
    UINT32 reg_gpu_aiopllss_cih2: 4;    //  11:8
    UINT32 reg_gpu_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_gpu_aiopllss_npc: 6;    //  21:16
    UINT32 resvd00            :  2;    //  23:22 reserved
    UINT32 reg_gpu_aiopllss_m :  6;    //  29:24
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}BND_CTRL_DPE_GPU_AIOPLLSS_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2068    gpu_aiopllss_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_gpu_aiopllss_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_gpu_aiopllss_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_gpu_aiopllss_dss: 1;    //     23
    UINT32 reg_gpu_aiopllss_offset: 8;    //  31:24
    };
}BND_CTRL_DPE_GPU_AIOPLLSS_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_206C    gpu_aiopllss_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_freq_update: 1;    //  0
    UINT32 reg_gpu_aiopllss_fout1_en: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_gpu_aiopllss_lock: 1;    //     4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_gpu_aiopllss_out_div: 7;    //  14:8
    UINT32 resvd02            :  9;    //  23:15 reserved
    UINT32 reg_gpu_aiopllss_sync_on: 1;    //  24
    UINT32 resvd03            :  2;    //  26:25 reserved
    UINT32 reg_gpu_aiopllss_wake_bypass: 1;    //  27
    UINT32 reg_gpu_aiopllss_offset_mode: 1;    //  28
    UINT32 resvd04            :  3;    //  31:29 reserved
    };
}BND_CTRL_DPE_GPU_AIOPLLSS_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2070    pqe_frpll_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopll_in_sel: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_pqepll_fcw_mux_sel: 2;    //  5:4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_pqepll_divint_mux_sel: 2;    //  9:8
    UINT32 resvd02            : 22;    //  31:10 reserved
    };
}BND_CTRL_DPE_PQE_FRPLL_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2074    pqe_frpll_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dpll_mon_en    :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_disp594_clk_gate_en: 1;    //   4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_DPE_PQE_FRPLL_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2078    pqe_frpll_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqepll_frpll_out3_div: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_pqepll_frpll_out2_div: 9;    //  20:12
    UINT32 resvd01            : 11;    //  31:21 reserved
    };
}BND_CTRL_DPE_PQE_FRPLL_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_207C    pqe_frpll_r08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pqepll_frpll_in_divsel: 1;    //  1
    UINT32 reg_pqepll_frpll_lpf_on: 1;    //   2
    UINT32 reg_pqepll_frpll_fout2_en: 1;    //  3
    UINT32 reg_pqepll_frpll_wakeup_bypass: 1;    //  4
    UINT32 reg_pqepll_frpll_divint: 9;    //  13:5
    UINT32 resvd01            :  1;    //     14 reserved
    UINT32 reg_pqepll_frpll_dsmon: 1;    //   15
    UINT32 reg_pqepll_frpll_auto_freq: 1;    //  16
    UINT32 reg_pqepll_frpll_dsm_limit: 1;    //  17
    UINT32 reg_pqepll_frpll_fin_sel: 1;    //  18
    UINT32 reg_pqepll_frpll_icp: 4;    //  22:19
    UINT32 reg_pqepll_frpll_out_div: 9;    //  31:23
    };
}BND_CTRL_DPE_PQE_FRPLL_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2080    pqe_frpll_r09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqepll_frpll_fout_en: 1;    //  0
    UINT32 reg_pqepll_frpll_syncon: 1;    //   1
    UINT32 reg_pqepll_frpll_m :  6;    //   7: 2
    UINT32 reg_pqepll_frpll_fcw: 24;    //  31:8
    };
}BND_CTRL_DPE_PQE_FRPLL_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2084    pqe_frpll_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqepll_frpll_lock: 1;    //     0
    UINT32 resvd00            : 22;    //  22: 1 reserved
    UINT32 reg_pqepll_frpll_frequp: 1;    //  23
    UINT32 reg_pqepll_frpll_a :  6;    //  29:24
    UINT32 reg_pqepll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_pqepll_frpll_icp_g: 1;    //   31
    };
}BND_CTRL_DPE_PQE_FRPLL_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2088    rxclk_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  7;    //   6: 0 reserved
    UINT32 reg_rxclkdrv_smv   :  1;    //      7
    UINT32 resvd01            : 24;    //   31:8 reserved
    };
}BND_CTRL_DPE_RXCLK_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_208C    tx_lo_drv_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tx_lo_drv_pdb  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tx_lo_drv_ck_div: 1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_DPE_TX_LO_DRV_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_2090    pat_gen_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pat_gen_en     :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_pat_gen        :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_DPE_PAT_GEN_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_DPE_SYN_BND_DPE_R00_O22A0_T        bnd_dpe_r00;             // 0xCC43_2000
    BND_CTRL_DPE_SYN_BND_DPE_R01_O22A0_T        bnd_dpe_r01;             // 0xCC43_2004
    BND_CTRL_DPE_SYN_BND_DPE_R02_O22A0_T        bnd_dpe_r02;             // 0xCC43_2008
    BND_CTRL_DPE_SYN_BND_DPE_R03_O22A0_T        bnd_dpe_r03;             // 0xCC43_200C
    BND_CTRL_DPE_SYN_BND_DPE_R04_O22A0_T        bnd_dpe_r04;             // 0xCC43_2010
    BND_CTRL_DPE_SYN_BND_DPE_R05_O22A0_T        bnd_dpe_r05;             // 0xCC43_2014
    BND_CTRL_DPE_SYN_BND_DPE_R06_O22A0_T        bnd_dpe_r06;             // 0xCC43_2018
    BND_CTRL_DPE_PQE_FRPLL_R00_O22A0_T      pqe_frpll_r00;           // 0xCC43_201C
    BND_CTRL_DPE_SYN_BND_DPE_R07_O22A0_T        bnd_dpe_r07;             // 0xCC43_2020
    BND_CTRL_DPE_SYN_BND_DPE_R08_O22A0_T        bnd_dpe_r08;             // 0xCC43_2024
    BND_CTRL_DPE_SYN_BND_DPE_R09_O22A0_T        bnd_dpe_r09;             // 0xCC43_2028
    BND_CTRL_DPE_SYN_BND_DPE_R10_O22A0_T        bnd_dpe_r10;             // 0xCC43_202C
    BND_CTRL_DPE_SYN_BND_DPE_R11_O22A0_T        bnd_dpe_r11;             // 0xCC43_2030
    BND_CTRL_DPE_SYN_BND_DPE_R12_O22A0_T        bnd_dpe_r12;             // 0xCC43_2034
    BND_CTRL_DPE_SYN_BND_DPE_R13_O22A0_T        bnd_dpe_r13;             // 0xCC43_2038
    BND_CTRL_DPE_SYN_BND_DPE_R14_O22A0_T        bnd_dpe_r14;             // 0xCC43_203C
    BND_CTRL_DPE_SYN_BND_DPE_R15_O22A0_T        bnd_dpe_r15;             // 0xCC43_2040
    BND_CTRL_DPE_SYN_BND_DPE_R16_O22A0_T        bnd_dpe_r16;             // 0xCC43_2044
    BND_CTRL_DPE_SYN_BND_DPE_R17_O22A0_T        bnd_dpe_r17;             // 0xCC43_2048
    BND_CTRL_DPE_SYN_BND_DPE_R18_O22A0_T        bnd_dpe_r18;             // 0xCC43_204C
    BND_CTRL_DPE_PQE_FRPLL_R01_O22A0_T      pqe_frpll_r01;           // 0xCC43_2050
    BND_CTRL_DPE_PQE_FRPLL_R02_O22A0_T      pqe_frpll_r02;           // 0xCC43_2054
    BND_CTRL_DPE_DISP_AIOPLL_R00_O22A0_T    disp_aiopll_r00;         // 0xCC43_2058
    BND_CTRL_DPE_DISP_AIOPLL_R01_O22A0_T    disp_aiopll_r01;         // 0xCC43_205C
    BND_CTRL_DPE_DISP_AIOPLL_R02_O22A0_T    disp_aiopll_r02;         // 0xCC43_2060
    BND_CTRL_DPE_GPU_AIOPLLSS_R00_O22A0_T    gpu_aiopllss_r00;       // 0xCC43_2064
    BND_CTRL_DPE_GPU_AIOPLLSS_R01_O22A0_T    gpu_aiopllss_r01;       // 0xCC43_2068
    BND_CTRL_DPE_GPU_AIOPLLSS_R02_O22A0_T    gpu_aiopllss_r02;       // 0xCC43_206C
    BND_CTRL_DPE_PQE_FRPLL_R03_O22A0_T      pqe_frpll_r03;           // 0xCC43_2070
    BND_CTRL_DPE_PQE_FRPLL_R04_O22A0_T      pqe_frpll_r04;           // 0xCC43_2074
    BND_CTRL_DPE_PQE_FRPLL_R07_O22A0_T      pqe_frpll_r07;           // 0xCC43_2078
    BND_CTRL_DPE_PQE_FRPLL_R08_O22A0_T      pqe_frpll_r08;           // 0xCC43_207C
    BND_CTRL_DPE_PQE_FRPLL_R09_O22A0_T      pqe_frpll_r09;           // 0xCC43_2080
    BND_CTRL_DPE_PQE_FRPLL_R10_O22A0_T      pqe_frpll_r10;           // 0xCC43_2084
    BND_CTRL_DPE_RXCLK_R00_O22A0_T          rxclk_r00  ;             // 0xCC43_2088
    BND_CTRL_DPE_TX_LO_DRV_R00_O22A0_T      tx_lo_drv_r00;           // 0xCC43_208C
    BND_CTRL_DPE_PAT_GEN_R00_O22A0_T        pat_gen_r00;             // 0xCC43_2090
}BND_CTRL_DPE_REG_O22A0_T;
/* 37 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_DPE_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

