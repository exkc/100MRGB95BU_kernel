#ifndef _CRG_TOP_CTRL_M23A0_REG_H_
#define _CRG_TOP_CTRL_M23A0_REG_H_

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
    0xCC92_2000    disp_aiopll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_disp_aiopll_fine_div  :  1,    //      1
    reg_disp_aiopll_dss       :  1,    //      2
    reg_disp_aiopll_accuracy  :  2,    //   4: 3
    reg_disp_aiopll_updn_max  :  7,    //  11: 5
    reg_disp_aiopll_mod_freq_max: 9,    //  20:12
    reg_disp_aiopll_m         :  6,    //  26:21
                              :  1,    //     27 reserved
    reg_disp_aiopll_cih       :  4;    //  31:28
}CRG_TOP_CTRL_DISP_AIOPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2004    disp_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_disp_aiopll_offset_mode: 1,    //      4
    reg_disp_aiopll_fout3_post_od: 3,    //  7:5
    reg_disp_aiopll_fout2_post_od: 3,    //  10:8
    reg_disp_aiopll_fout_od   :  2,    //  12:11
    reg_disp_aiopll_fout3_pre_od: 3,    //  15:13
    reg_disp_aiopll_fout2_pre_od: 3,    //  18:16
    reg_disp_aiopll_nsc       :  4,    //  22:19
    reg_disp_aiopll_npc       :  6,    //  28:23
    reg_disp_aiopll_fine_control: 3;    //  31:29
}CRG_TOP_CTRL_DISP_AIOPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2008    disp_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_disp_aiopll_freq_update: 1,    //      1
    reg_disp_aiopll_sync_on   :  1,    //      2
    reg_disp_aiopll_in_sel    :  1,    //      3
                              : 18,    //  21: 4 reserved
    reg_disp_aiopll_wake_bypass: 1,    //     22
    reg_disp_aiopll_ddr_mode  :  1,    //     23
    reg_disp_aiopll_offset    :  8;    //  31:24
}CRG_TOP_CTRL_DISP_AIOPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_200C    f54pll_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_f54pll_frpll_in_divsel:  1,    //      1
    reg_f54pll_frpll_lpf_on   :  1,    //      2
    reg_f54pll_frpll_fout2_en :  1,    //      3
    reg_f54pll_frpll_wakeup_bypass: 1,    //   4
    reg_f54pll_frpll_divint   :  9,    //  13: 5
                              :  1,    //     14 reserved
    reg_f54pll_frpll_dsmon    :  1,    //     15
    reg_f54pll_frpll_auto_freq:  1,    //     16
    reg_f54pll_frpll_dsm_limit:  1,    //     17
    reg_f54pll_frpll_fin_sel  :  1,    //     18
    reg_f54pll_frpll_icp      :  4,    //  22:19
    reg_f54pll_frpll_out_div  :  9;    //  31:23
}CRG_TOP_CTRL_F54PLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2010    f54pll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f54pll_frpll_fout_en  :  1,    //      0
    reg_f54pll_frpll_syncon   :  1,    //      1
    reg_f54pll_frpll_m        :  6,    //   7: 2
    reg_f54pll_frpll_fcw      : 24;    //  31: 8
}CRG_TOP_CTRL_F54PLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2014    f54pll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f54pll_frpll_lock     :  1,    //      0
                              :  4,    //   4: 1 reserved
    reg_f54pll_frpll_out_div3 :  9,    //  13: 5
    reg_f54pll_frpll_out_div2 :  9,    //  22:14
    reg_f54pll_frpll_frequp   :  1,    //     23
    reg_f54pll_frpll_a        :  6,    //  29:24
    reg_f54pll_frpll_in_divrstb: 1,    //     30
    reg_f54pll_frpll_icp_g    :  1;    //     31
}CRG_TOP_CTRL_F54PLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2018    f54pll_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f54pll_divint_mux_sel :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_f54pll_fcw_mux_sel    :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CRG_TOP_CTRL_F54PLL_FRPLL_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_201C    apll_frpll_00 ''
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
}CRG_TOP_CTRL_APLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2020    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fout_en    :  1,    //      0
    reg_apll_frpll_syncon     :  1,    //      1
    reg_apll_frpll_m          :  6,    //   7: 2
    reg_apll_frpll_fcw        : 24;    //  31: 8
}CRG_TOP_CTRL_APLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2024    apll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_lock       :  1,    //      0
                              :  4,    //   4: 1 reserved
    reg_apll_frpll_out_div3   :  9,    //  13: 5
    reg_apll_frpll_out_div2   :  9,    //  22:14
    reg_apll_frpll_frequp     :  1,    //     23
    reg_apll_frpll_a          :  6,    //  29:24
    reg_apll_frpll_in_divrstb :  1,    //     30
    reg_apll_frpll_icp_g      :  1;    //     31
}CRG_TOP_CTRL_APLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2028    apll_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_updn_max   :  8,    //   7: 0
    reg_apll_frpll_mod_speed_max: 9,    //  16:8
                              :  7,    //  23:17 reserved
    reg_apll_frpll_lock_cont  :  1,    //     24
    reg_apll_frpll_dss        :  1,    //     25
                              :  5,    //  30:26 reserved
    reg_apll_soft_reset_frpll_sscg: 1;    //  31
}CRG_TOP_CTRL_APLL_FRPLL_SSCG_R00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_202C    earcpll_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_earcpll_frpll_in_divsel: 1,    //      1
    reg_earcpll_frpll_lpf_on  :  1,    //      2
    reg_earcpll_frpll_fout2_en:  1,    //      3
    reg_earcpll_frpll_wakeup_bypass: 1,    //  4
    reg_earcpll_frpll_divint  :  9,    //  13: 5
                              :  1,    //     14 reserved
    reg_earcpll_frpll_dsmon   :  1,    //     15
    reg_earcpll_frpll_auto_freq: 1,    //     16
    reg_earcpll_frpll_dsm_limit: 1,    //     17
    reg_earcpll_frpll_fin_sel :  1,    //     18
    reg_earcpll_frpll_icp     :  4,    //  22:19
    reg_earcpll_frpll_out_div :  9;    //  31:23
}CRG_TOP_CTRL_EARCPLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2030    earcpll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_frpll_fout_en :  1,    //      0
    reg_earcpll_frpll_syncon  :  1,    //      1
    reg_earcpll_frpll_m       :  6,    //   7: 2
    reg_earcpll_frpll_fcw     : 24;    //  31: 8
}CRG_TOP_CTRL_EARCPLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2034    earcpll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_frpll_lock    :  1,    //      0
                              :  4,    //   4: 1 reserved
    reg_earcpll_frpll_out_div3:  9,    //  13: 5
    reg_earcpll_frpll_out_div2:  9,    //  22:14
    reg_earcpll_frpll_frequp  :  1,    //     23
    reg_earcpll_frpll_a       :  6,    //  29:24
    reg_earcpll_frpll_in_divrstb: 1,    //    30
    reg_earcpll_frpll_icp_g   :  1;    //     31
}CRG_TOP_CTRL_EARCPLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2038    earcpll_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_frpll_updn_max:  8,    //   7: 0
    reg_earcpll_frpll_mod_speed_max: 9,    //  16:8
                              :  7,    //  23:17 reserved
    reg_earcpll_frpll_lock_cont: 1,    //     24
    reg_earcpll_frpll_dss     :  1,    //     25
                              :  5,    //  30:26 reserved
    reg_earcpll_soft_reset_frpll_sscg: 1;    //  31
}CRG_TOP_CTRL_EARCPLL_FRPLL_SSCG_R00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_203C    fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_fcw_mux_sel      :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_earcpll_fcw_mux_sel   :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CRG_TOP_CTRL_FCW_MUX_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2040    gcore_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcore_aiopllss_accuracy: 2,    //   1: 0
                              :  1,    //      2 reserved
    reg_gcore_aiopllss_dss    :  1,    //      3
    reg_gcore_aiopllss_cih2   :  4,    //   7: 4
    reg_gcore_aiopllss_cih    :  4,    //  11: 8
    reg_gcore_aiopllss_nsc    :  4,    //  15:12
    reg_gcore_aiopllss_npc    :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_gcore_aiopllss_m      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_GCORE_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2044    gcore_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcore_aiopllss_out_div:  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_gcore_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_gcore_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_GCORE_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2048    gcore_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcore_aiopllss_fout1_en: 1,    //      0
    reg_gcore_aiopllss_freq_update: 1,    //   1
    reg_gcore_aiopllss_sync_on:  1,    //      2
    reg_gcore_aiopllss_wake_bypass: 1,    //   3
    reg_gcore_aiopllss_offset_mode: 1,    //   4
    reg_gcore_aiopllss_fine_div: 1,    //      5
                              :  2,    //   7: 6 reserved
    reg_gcore_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_gcore_aiopllss_offset :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_GCORE_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_204C    pcore_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pcore_aiopllss_accuracy: 2,    //   1: 0
                              :  1,    //      2 reserved
    reg_pcore_aiopllss_dss    :  1,    //      3
    reg_pcore_aiopllss_cih2   :  4,    //   7: 4
    reg_pcore_aiopllss_cih    :  4,    //  11: 8
    reg_pcore_aiopllss_nsc    :  4,    //  15:12
    reg_pcore_aiopllss_npc    :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_pcore_aiopllss_m      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_PCORE_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2050    pcore_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pcore_aiopllss_out_div:  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_pcore_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_pcore_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_PCORE_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2054    pcore_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pcore_aiopllss_fout1_en: 1,    //      0
    reg_pcore_aiopllss_freq_update: 1,    //   1
    reg_pcore_aiopllss_sync_on:  1,    //      2
    reg_pcore_aiopllss_wake_bypass: 1,    //   3
    reg_pcore_aiopllss_offset_mode: 1,    //   4
    reg_pcore_aiopllss_fine_div: 1,    //      5
                              :  2,    //   7: 6 reserved
    reg_pcore_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_pcore_aiopllss_offset :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_PCORE_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2058    gcodec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcodec_aiopllss_accuracy: 2,    //  1: 0
                              :  1,    //      2 reserved
    reg_gcodec_aiopllss_dss   :  1,    //      3
    reg_gcodec_aiopllss_cih2  :  4,    //   7: 4
    reg_gcodec_aiopllss_cih   :  4,    //  11: 8
    reg_gcodec_aiopllss_nsc   :  4,    //  15:12
    reg_gcodec_aiopllss_npc   :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_gcodec_aiopllss_m     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_205C    gcodec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcodec_aiopllss_out_div: 7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_gcodec_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_gcodec_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2060    gcodec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gcodec_aiopllss_fout1_en: 1,    //     0
    reg_gcodec_aiopllss_freq_update: 1,    //  1
    reg_gcodec_aiopllss_sync_on: 1,    //      2
    reg_gcodec_aiopllss_wake_bypass: 1,    //  3
    reg_gcodec_aiopllss_offset_mode: 1,    //  4
    reg_gcodec_aiopllss_fine_div: 1,    //     5
                              :  2,    //   7: 6 reserved
    reg_gcodec_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_gcodec_aiopllss_offset:  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2064    vcodec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vcodec_aiopllss_accuracy: 2,    //  1: 0
                              :  1,    //      2 reserved
    reg_vcodec_aiopllss_dss   :  1,    //      3
    reg_vcodec_aiopllss_cih2  :  4,    //   7: 4
    reg_vcodec_aiopllss_cih   :  4,    //  11: 8
    reg_vcodec_aiopllss_nsc   :  4,    //  15:12
    reg_vcodec_aiopllss_npc   :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_vcodec_aiopllss_m     :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2068    vcodec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vcodec_aiopllss_out_div: 7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_vcodec_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_vcodec_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_206C    vcodec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vcodec_aiopllss_fout1_en: 1,    //     0
    reg_vcodec_aiopllss_freq_update: 1,    //  1
    reg_vcodec_aiopllss_sync_on: 1,    //      2
    reg_vcodec_aiopllss_wake_bypass: 1,    //  3
    reg_vcodec_aiopllss_offset_mode: 1,    //  4
    reg_vcodec_aiopllss_fine_div: 1,    //     5
                              :  2,    //   7: 6 reserved
    reg_vcodec_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_vcodec_aiopllss_offset:  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2070    cpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_cpu_aiopllss_dss      :  1,    //      3
    reg_cpu_aiopllss_cih2     :  4,    //   7: 4
    reg_cpu_aiopllss_cih      :  4,    //  11: 8
    reg_cpu_aiopllss_nsc      :  4,    //  15:12
    reg_cpu_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_cpu_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_CPU_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2074    cpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_cpu_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_cpu_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_CPU_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2078    cpu_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_fout1_en :  1,    //      0
    reg_cpu_aiopllss_freq_update: 1,    //     1
    reg_cpu_aiopllss_sync_on  :  1,    //      2
    reg_cpu_aiopllss_wake_bypass: 1,    //     3
    reg_cpu_aiopllss_offset_mode: 1,    //     4
    reg_cpu_aiopllss_fine_div :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_cpu_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_cpu_aiopllss_offset   :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_CPU_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_207C    gpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_gpu_aiopllss_dss      :  1,    //      3
    reg_gpu_aiopllss_cih2     :  4,    //   7: 4
    reg_gpu_aiopllss_cih      :  4,    //  11: 8
    reg_gpu_aiopllss_nsc      :  4,    //  15:12
    reg_gpu_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_gpu_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CRG_TOP_CTRL_GPU_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2080    gpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_gpu_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_gpu_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}CRG_TOP_CTRL_GPU_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2084    gpu_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_fout1_en :  1,    //      0
    reg_gpu_aiopllss_freq_update: 1,    //     1
    reg_gpu_aiopllss_sync_on  :  1,    //      2
    reg_gpu_aiopllss_wake_bypass: 1,    //     3
    reg_gpu_aiopllss_offset_mode: 1,    //     4
    reg_gpu_aiopllss_fine_div :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_gpu_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_gpu_aiopllss_offset   :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_GPU_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2088    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_pdb_ctrl     :  1,    //      0
    reg_earcpll_pll_pdb_ctrl  :  1,    //      1
    reg_apll_pll_pdb_ctrl     :  1,    //      2
    reg_f54pll_pll_pdb_ctrl   :  1,    //      3
    reg_gpu_pll_pdb_ctrl      :  1,    //      4
    reg_cpu_pll_pdb_ctrl      :  1,    //      5
    reg_vcodec_pll_pdb_ctrl   :  1,    //      6
    reg_gcodec_pll_pdb_ctrl   :  1,    //      7
    reg_pcore_pll_pdb_ctrl    :  1,    //      8
    reg_gcore_pll_pdb_ctrl    :  1,    //      9
    reg_m0_pll_pdb_ctrl       :  1,    //     10
                              : 21;    //  31:11 reserved
}CRG_TOP_CTRL_CRG_TOP_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_208C    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_pll_lock         :  1,    //      0
    reg_earcpll_pll_lock      :  1,    //      1
    reg_apll_pll_lock         :  1,    //      2
    reg_f54pll_pll_lock       :  1,    //      3
    reg_gpu_pll_lock          :  1,    //      4
    reg_cpu_pll_lock          :  1,    //      5
    reg_vcodec_pll_lock       :  1,    //      6
    reg_gcodec_pll_lock       :  1,    //      7
    reg_pcore_pll_lock        :  1,    //      8
    reg_gcore_pll_lock        :  1,    //      9
    reg_m0_pll_lock           :  1,    //     10
                              : 21;    //  31:11 reserved
}CRG_TOP_CTRL_CRG_TOP_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2090    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_lock_bypass   :  1,    //      0
    reg_apll_lock_bypass      :  1,    //      1
    reg_disp_pll_lock_bypass  :  1,    //      2
    reg_disp_frpll_lock_bypass:  1,    //      3
    reg_gpu_pll_lock_bypass   :  1,    //      4
    reg_cpu_pll_lock_bypass   :  1,    //      5
    reg_vcodec_pll_lock_bypass:  1,    //      6
    reg_gcodec_pll_lock_bypass:  1,    //      7
    reg_pcore_pll_lock_bypass :  1,    //      8
    reg_gcore_pll_lock_bypass :  1,    //      9
                              : 22;    //  31:10 reserved
}CRG_TOP_CTRL_CRG_TOP_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2094    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_core_660      :  2,    //   1: 0
    reg_pll_sel_core_660      :  2,    //   3: 2
    reg_clk_sel_core_533      :  2,    //   5: 4
    reg_pll_sel_core_533      :  2,    //   7: 6
    reg_clk_sel_core_600      :  2,    //   9: 8
    reg_pll_sel_core_600      :  2,    //  11:10
    reg_clk_sel_emmc_400      :  2,    //  13:12
    reg_pll_sel_emmc_400      :  2,    //  15:14
    reg_clk_sel_core_400      :  2,    //  17:16
    reg_pll_sel_core_400      :  2,    //  19:18
                              : 12;    //  31:20 reserved
}CRG_TOP_CTRL_CRG_TOP_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2098    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_core_800      :  2,    //   1: 0
    reg_pll_sel_core_800      :  2,    //   3: 2
    reg_clk_sel_core_560      :  2,    //   5: 4
    reg_pll_sel_core_560      :  2,    //   7: 6
    reg_clk_sel_pcore_400     :  2,    //   9: 8
    reg_pll_sel_pcore_400     :  2,    //  11:10
    reg_clk_sel_core_480      :  2,    //  13:12
    reg_pll_sel_core_480      :  2,    //  15:14
    reg_clk_sel_core_vd1_660  :  2,    //  17:16
    reg_pll_sel_core_vd1_660  :  2,    //  19:18
    reg_clk_sel_gpu           :  1,    //     20
                              : 11;    //  31:21 reserved
}CRG_TOP_CTRL_CRG_TOP_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_209C    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}CRG_TOP_CTRL_CRG_TOP_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CRG_TOP_CTRL_DISP_AIOPLL_00_M23A0_T    disp_aiopll_00;      // 0xCC92_2000
    CRG_TOP_CTRL_DISP_AIOPLL_01_M23A0_T    disp_aiopll_01;      // 0xCC92_2004
    CRG_TOP_CTRL_DISP_AIOPLL_02_M23A0_T    disp_aiopll_02;      // 0xCC92_2008
    CRG_TOP_CTRL_F54PLL_FRPLL_00_M23A0_T    f54pll_frpll_00;    // 0xCC92_200C
    CRG_TOP_CTRL_F54PLL_FRPLL_01_M23A0_T    f54pll_frpll_01;    // 0xCC92_2010
    CRG_TOP_CTRL_F54PLL_FRPLL_02_M23A0_T    f54pll_frpll_02;    // 0xCC92_2014
    CRG_TOP_CTRL_F54PLL_FRPLL_03_M23A0_T    f54pll_frpll_03;    // 0xCC92_2018
    CRG_TOP_CTRL_APLL_FRPLL_00_M23A0_T    apll_frpll_00;        // 0xCC92_201C
    CRG_TOP_CTRL_APLL_FRPLL_01_M23A0_T    apll_frpll_01;        // 0xCC92_2020
    CRG_TOP_CTRL_APLL_FRPLL_02_M23A0_T    apll_frpll_02;        // 0xCC92_2024
    CRG_TOP_CTRL_APLL_FRPLL_SSCG_R00_M23A0_T    apll_frpll_sscg_r00;    // 0xCC92_2028
    CRG_TOP_CTRL_EARCPLL_FRPLL_00_M23A0_T    earcpll_frpll_00;    // 0xCC92_202C
    CRG_TOP_CTRL_EARCPLL_FRPLL_01_M23A0_T    earcpll_frpll_01;    // 0xCC92_2030
    CRG_TOP_CTRL_EARCPLL_FRPLL_02_M23A0_T    earcpll_frpll_02;    // 0xCC92_2034
    CRG_TOP_CTRL_EARCPLL_FRPLL_SSCG_R00_M23A0_T    earcpll_frpll_sscg_r00;    // 0xCC92_2038
    CRG_TOP_CTRL_FCW_MUX_00_M23A0_T    fcw_mux_00 ;             // 0xCC92_203C
    CRG_TOP_CTRL_GCORE_AIOPLLSS_00_M23A0_T    gcore_aiopllss_00;    // 0xCC92_2040
    CRG_TOP_CTRL_GCORE_AIOPLLSS_01_M23A0_T    gcore_aiopllss_01;    // 0xCC92_2044
    CRG_TOP_CTRL_GCORE_AIOPLLSS_02_M23A0_T    gcore_aiopllss_02;    // 0xCC92_2048
    CRG_TOP_CTRL_PCORE_AIOPLLSS_00_M23A0_T    pcore_aiopllss_00;    // 0xCC92_204C
    CRG_TOP_CTRL_PCORE_AIOPLLSS_01_M23A0_T    pcore_aiopllss_01;    // 0xCC92_2050
    CRG_TOP_CTRL_PCORE_AIOPLLSS_02_M23A0_T    pcore_aiopllss_02;    // 0xCC92_2054
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_00_M23A0_T    gcodec_aiopllss_00;    // 0xCC92_2058
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_01_M23A0_T    gcodec_aiopllss_01;    // 0xCC92_205C
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_02_M23A0_T    gcodec_aiopllss_02;    // 0xCC92_2060
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_00_M23A0_T    vcodec_aiopllss_00;    // 0xCC92_2064
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_01_M23A0_T    vcodec_aiopllss_01;    // 0xCC92_2068
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_02_M23A0_T    vcodec_aiopllss_02;    // 0xCC92_206C
    CRG_TOP_CTRL_CPU_AIOPLLSS_00_M23A0_T    cpu_aiopllss_00;    // 0xCC92_2070
    CRG_TOP_CTRL_CPU_AIOPLLSS_01_M23A0_T    cpu_aiopllss_01;    // 0xCC92_2074
    CRG_TOP_CTRL_CPU_AIOPLLSS_02_M23A0_T    cpu_aiopllss_02;    // 0xCC92_2078
    CRG_TOP_CTRL_GPU_AIOPLLSS_00_M23A0_T    gpu_aiopllss_00;    // 0xCC92_207C
    CRG_TOP_CTRL_GPU_AIOPLLSS_01_M23A0_T    gpu_aiopllss_01;    // 0xCC92_2080
    CRG_TOP_CTRL_GPU_AIOPLLSS_02_M23A0_T    gpu_aiopllss_02;    // 0xCC92_2084
    CRG_TOP_CTRL_CRG_TOP_00_M23A0_T    crg_top_00 ;             // 0xCC92_2088
    CRG_TOP_CTRL_CRG_TOP_01_M23A0_T    crg_top_01 ;             // 0xCC92_208C
    CRG_TOP_CTRL_CRG_TOP_02_M23A0_T    crg_top_02 ;             // 0xCC92_2090
    CRG_TOP_CTRL_CRG_TOP_03_M23A0_T    crg_top_03 ;             // 0xCC92_2094
    CRG_TOP_CTRL_CRG_TOP_04_M23A0_T    crg_top_04 ;             // 0xCC92_2098
    CRG_TOP_CTRL_CRG_TOP_05_M23A0_T    crg_top_05 ;             // 0xCC92_209C
}CRG_TOP_CTRL_REG_M23A0_T;
/* 40 regs */

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

#define CRG_TOP_CTRL_DISP_AIOPLL_00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define CRG_TOP_CTRL_DISP_AIOPLL_01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define CRG_TOP_CTRL_DISP_AIOPLL_02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define CRG_TOP_CTRL_F54PLL_FRPLL_00_M23A0_T_OFF            (BASEADDRESS+0x000C)
#define CRG_TOP_CTRL_F54PLL_FRPLL_01_M23A0_T_OFF            (BASEADDRESS+0x0010)
#define CRG_TOP_CTRL_F54PLL_FRPLL_02_M23A0_T_OFF            (BASEADDRESS+0x0014)
#define CRG_TOP_CTRL_F54PLL_FRPLL_03_M23A0_T_OFF            (BASEADDRESS+0x0018)
#define CRG_TOP_CTRL_APLL_FRPLL_00_M23A0_T_OFF              (BASEADDRESS+0x001C)
#define CRG_TOP_CTRL_APLL_FRPLL_01_M23A0_T_OFF              (BASEADDRESS+0x0020)
#define CRG_TOP_CTRL_APLL_FRPLL_02_M23A0_T_OFF              (BASEADDRESS+0x0024)
#define CRG_TOP_CTRL_APLL_FRPLL_SSCG_R00_M23A0_T_OFF        (BASEADDRESS+0x0028)
#define CRG_TOP_CTRL_EARCPLL_FRPLL_00_M23A0_T_OFF           (BASEADDRESS+0x002C)
#define CRG_TOP_CTRL_EARCPLL_FRPLL_01_M23A0_T_OFF           (BASEADDRESS+0x0030)
#define CRG_TOP_CTRL_EARCPLL_FRPLL_02_M23A0_T_OFF           (BASEADDRESS+0x0034)
#define CRG_TOP_CTRL_EARCPLL_FRPLL_SSCG_R00_M23A0_T_OFF     (BASEADDRESS+0x0038)
#define CRG_TOP_CTRL_FCW_MUX_00_M23A0_T_OFF                 (BASEADDRESS+0x003C)
#define CRG_TOP_CTRL_GCORE_AIOPLLSS_00_M23A0_T_OFF          (BASEADDRESS+0x0040)
#define CRG_TOP_CTRL_GCORE_AIOPLLSS_01_M23A0_T_OFF          (BASEADDRESS+0x0044)
#define CRG_TOP_CTRL_GCORE_AIOPLLSS_02_M23A0_T_OFF          (BASEADDRESS+0x0048)
#define CRG_TOP_CTRL_PCORE_AIOPLLSS_00_M23A0_T_OFF          (BASEADDRESS+0x004C)
#define CRG_TOP_CTRL_PCORE_AIOPLLSS_01_M23A0_T_OFF          (BASEADDRESS+0x0050)
#define CRG_TOP_CTRL_PCORE_AIOPLLSS_02_M23A0_T_OFF          (BASEADDRESS+0x0054)
#define CRG_TOP_CTRL_GCODEC_AIOPLLSS_00_M23A0_T_OFF         (BASEADDRESS+0x0058)
#define CRG_TOP_CTRL_GCODEC_AIOPLLSS_01_M23A0_T_OFF         (BASEADDRESS+0x005C)
#define CRG_TOP_CTRL_GCODEC_AIOPLLSS_02_M23A0_T_OFF         (BASEADDRESS+0x0060)
#define CRG_TOP_CTRL_VCODEC_AIOPLLSS_00_M23A0_T_OFF         (BASEADDRESS+0x0064)
#define CRG_TOP_CTRL_VCODEC_AIOPLLSS_01_M23A0_T_OFF         (BASEADDRESS+0x0068)
#define CRG_TOP_CTRL_VCODEC_AIOPLLSS_02_M23A0_T_OFF         (BASEADDRESS+0x006C)
#define CRG_TOP_CTRL_CPU_AIOPLLSS_00_M23A0_T_OFF            (BASEADDRESS+0x0070)
#define CRG_TOP_CTRL_CPU_AIOPLLSS_01_M23A0_T_OFF            (BASEADDRESS+0x0074)
#define CRG_TOP_CTRL_CPU_AIOPLLSS_02_M23A0_T_OFF            (BASEADDRESS+0x0078)
#define CRG_TOP_CTRL_GPU_AIOPLLSS_00_M23A0_T_OFF            (BASEADDRESS+0x007C)
#define CRG_TOP_CTRL_GPU_AIOPLLSS_01_M23A0_T_OFF            (BASEADDRESS+0x0080)
#define CRG_TOP_CTRL_GPU_AIOPLLSS_02_M23A0_T_OFF            (BASEADDRESS+0x0084)
#define CRG_TOP_CTRL_CRG_TOP_00_M23A0_T_OFF                 (BASEADDRESS+0x0088)
#define CRG_TOP_CTRL_CRG_TOP_01_M23A0_T_OFF                 (BASEADDRESS+0x008C)
#define CRG_TOP_CTRL_CRG_TOP_02_M23A0_T_OFF                 (BASEADDRESS+0x0090)
#define CRG_TOP_CTRL_CRG_TOP_03_M23A0_T_OFF                 (BASEADDRESS+0x0094)
#define CRG_TOP_CTRL_CRG_TOP_04_M23A0_T_OFF                 (BASEADDRESS+0x0098)
#define CRG_TOP_CTRL_CRG_TOP_05_M23A0_T_OFF                 (BASEADDRESS+0x009C)

/*-----------------------------------------------------------------------------------------
    0xCC92_2000    disp_aiopll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_disp_aiopll_fine_div: 1;    //  1
    UINT32 reg_disp_aiopll_dss:  1;    //      2
    UINT32 reg_disp_aiopll_accuracy: 2;    //  4:3
    UINT32 reg_disp_aiopll_updn_max: 7;    //  11:5
    UINT32 reg_disp_aiopll_mod_freq_max: 9;    //  20:12
    UINT32 reg_disp_aiopll_m  :  6;    //  26:21
    UINT32 resvd01            :  1;    //     27 reserved
    UINT32 reg_disp_aiopll_cih:  4;    //  31:28
    };
}CRG_TOP_CTRL_DISP_AIOPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2004    disp_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_disp_aiopll_offset_mode: 1;    //  4
    UINT32 reg_disp_aiopll_fout3_post_od: 3;    //  7:5
    UINT32 reg_disp_aiopll_fout2_post_od: 3;    //  10:8
    UINT32 reg_disp_aiopll_fout_od: 2;    //  12:11
    UINT32 reg_disp_aiopll_fout3_pre_od: 3;    //  15:13
    UINT32 reg_disp_aiopll_fout2_pre_od: 3;    //  18:16
    UINT32 reg_disp_aiopll_nsc:  4;    //  22:19
    UINT32 reg_disp_aiopll_npc:  6;    //  28:23
    UINT32 reg_disp_aiopll_fine_control: 3;    //  31:29
    };
}CRG_TOP_CTRL_DISP_AIOPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2008    disp_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_disp_aiopll_freq_update: 1;    //  1
    UINT32 reg_disp_aiopll_sync_on: 1;    //   2
    UINT32 reg_disp_aiopll_in_sel: 1;    //    3
    UINT32 resvd01            : 18;    //  21: 4 reserved
    UINT32 reg_disp_aiopll_wake_bypass: 1;    //  22
    UINT32 reg_disp_aiopll_ddr_mode: 1;    //  23
    UINT32 reg_disp_aiopll_offset: 8;    //  31:24
    };
}CRG_TOP_CTRL_DISP_AIOPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_200C    f54pll_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_f54pll_frpll_in_divsel: 1;    //  1
    UINT32 reg_f54pll_frpll_lpf_on: 1;    //   2
    UINT32 reg_f54pll_frpll_fout2_en: 1;    //  3
    UINT32 reg_f54pll_frpll_wakeup_bypass: 1;    //  4
    UINT32 reg_f54pll_frpll_divint: 9;    //  13:5
    UINT32 resvd01            :  1;    //     14 reserved
    UINT32 reg_f54pll_frpll_dsmon: 1;    //   15
    UINT32 reg_f54pll_frpll_auto_freq: 1;    //  16
    UINT32 reg_f54pll_frpll_dsm_limit: 1;    //  17
    UINT32 reg_f54pll_frpll_fin_sel: 1;    //  18
    UINT32 reg_f54pll_frpll_icp: 4;    //  22:19
    UINT32 reg_f54pll_frpll_out_div: 9;    //  31:23
    };
}CRG_TOP_CTRL_F54PLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2010    f54pll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f54pll_frpll_fout_en: 1;    //  0
    UINT32 reg_f54pll_frpll_syncon: 1;    //   1
    UINT32 reg_f54pll_frpll_m :  6;    //   7: 2
    UINT32 reg_f54pll_frpll_fcw: 24;    //  31:8
    };
}CRG_TOP_CTRL_F54PLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2014    f54pll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f54pll_frpll_lock: 1;    //     0
    UINT32 resvd00            :  4;    //   4: 1 reserved
    UINT32 reg_f54pll_frpll_out_div3: 9;    //  13:5
    UINT32 reg_f54pll_frpll_out_div2: 9;    //  22:14
    UINT32 reg_f54pll_frpll_frequp: 1;    //  23
    UINT32 reg_f54pll_frpll_a :  6;    //  29:24
    UINT32 reg_f54pll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_f54pll_frpll_icp_g: 1;    //   31
    };
}CRG_TOP_CTRL_F54PLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2018    f54pll_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f54pll_divint_mux_sel: 2;    //  1:0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_f54pll_fcw_mux_sel: 2;    //  5:4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}CRG_TOP_CTRL_F54PLL_FRPLL_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_201C    apll_frpll_00 ''
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
}CRG_TOP_CTRL_APLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2020    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_fout_en: 1;    //    0
    UINT32 reg_apll_frpll_syncon: 1;    //     1
    UINT32 reg_apll_frpll_m   :  6;    //   7: 2
    UINT32 reg_apll_frpll_fcw : 24;    //  31: 8
    };
}CRG_TOP_CTRL_APLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2024    apll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_lock:  1;    //      0
    UINT32 resvd00            :  4;    //   4: 1 reserved
    UINT32 reg_apll_frpll_out_div3: 9;    //  13:5
    UINT32 reg_apll_frpll_out_div2: 9;    //  22:14
    UINT32 reg_apll_frpll_frequp: 1;    //    23
    UINT32 reg_apll_frpll_a   :  6;    //  29:24
    UINT32 reg_apll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_apll_frpll_icp_g: 1;    //     31
    };
}CRG_TOP_CTRL_APLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2028    apll_frpll_sscg_r00 ''
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
    UINT32 reg_apll_soft_reset_frpll_sscg: 1;    //  31
    };
}CRG_TOP_CTRL_APLL_FRPLL_SSCG_R00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_202C    earcpll_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_earcpll_frpll_in_divsel: 1;    //  1
    UINT32 reg_earcpll_frpll_lpf_on: 1;    //  2
    UINT32 reg_earcpll_frpll_fout2_en: 1;    //  3
    UINT32 reg_earcpll_frpll_wakeup_bypass: 1;    //  4
    UINT32 reg_earcpll_frpll_divint: 9;    //  13:5
    UINT32 resvd01            :  1;    //     14 reserved
    UINT32 reg_earcpll_frpll_dsmon: 1;    //  15
    UINT32 reg_earcpll_frpll_auto_freq: 1;    //  16
    UINT32 reg_earcpll_frpll_dsm_limit: 1;    //  17
    UINT32 reg_earcpll_frpll_fin_sel: 1;    //  18
    UINT32 reg_earcpll_frpll_icp: 4;    //  22:19
    UINT32 reg_earcpll_frpll_out_div: 9;    //  31:23
    };
}CRG_TOP_CTRL_EARCPLL_FRPLL_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2030    earcpll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_frpll_fout_en: 1;    //  0
    UINT32 reg_earcpll_frpll_syncon: 1;    //  1
    UINT32 reg_earcpll_frpll_m:  6;    //   7: 2
    UINT32 reg_earcpll_frpll_fcw: 24;    //  31:8
    };
}CRG_TOP_CTRL_EARCPLL_FRPLL_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2034    earcpll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_frpll_lock: 1;    //    0
    UINT32 resvd00            :  4;    //   4: 1 reserved
    UINT32 reg_earcpll_frpll_out_div3: 9;    //  13:5
    UINT32 reg_earcpll_frpll_out_div2: 9;    //  22:14
    UINT32 reg_earcpll_frpll_frequp: 1;    //  23
    UINT32 reg_earcpll_frpll_a:  6;    //  29:24
    UINT32 reg_earcpll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_earcpll_frpll_icp_g: 1;    //  31
    };
}CRG_TOP_CTRL_EARCPLL_FRPLL_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2038    earcpll_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_frpll_updn_max: 8;    //  7:0
    UINT32 reg_earcpll_frpll_mod_speed_max: 9;    //  16:8
    UINT32 resvd00            :  7;    //  23:17 reserved
    UINT32 reg_earcpll_frpll_lock_cont: 1;    //  24
    UINT32 reg_earcpll_frpll_dss: 1;    //    25
    UINT32 resvd01            :  5;    //  30:26 reserved
    UINT32 reg_earcpll_soft_reset_frpll_sscg: 1;    //  31
    };
}CRG_TOP_CTRL_EARCPLL_FRPLL_SSCG_R00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_203C    fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_fcw_mux_sel: 2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_earcpll_fcw_mux_sel: 2;    //  5:4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}CRG_TOP_CTRL_FCW_MUX_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2040    gcore_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcore_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_gcore_aiopllss_dss: 1;    //    3
    UINT32 reg_gcore_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_gcore_aiopllss_cih: 4;    //  11:8
    UINT32 reg_gcore_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_gcore_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_gcore_aiopllss_m: 6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_GCORE_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2044    gcore_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcore_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_gcore_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_gcore_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_GCORE_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2048    gcore_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcore_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_gcore_aiopllss_freq_update: 1;    //  1
    UINT32 reg_gcore_aiopllss_sync_on: 1;    //  2
    UINT32 reg_gcore_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_gcore_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_gcore_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_gcore_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_gcore_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_GCORE_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_204C    pcore_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pcore_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_pcore_aiopllss_dss: 1;    //    3
    UINT32 reg_pcore_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_pcore_aiopllss_cih: 4;    //  11:8
    UINT32 reg_pcore_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_pcore_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_pcore_aiopllss_m: 6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_PCORE_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2050    pcore_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pcore_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_pcore_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_pcore_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_PCORE_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2054    pcore_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pcore_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_pcore_aiopllss_freq_update: 1;    //  1
    UINT32 reg_pcore_aiopllss_sync_on: 1;    //  2
    UINT32 reg_pcore_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_pcore_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_pcore_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_pcore_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_pcore_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_PCORE_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2058    gcodec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcodec_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_gcodec_aiopllss_dss: 1;    //   3
    UINT32 reg_gcodec_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_gcodec_aiopllss_cih: 4;    //  11:8
    UINT32 reg_gcodec_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_gcodec_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_gcodec_aiopllss_m: 6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_205C    gcodec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcodec_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_gcodec_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_gcodec_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2060    gcodec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gcodec_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_gcodec_aiopllss_freq_update: 1;    //  1
    UINT32 reg_gcodec_aiopllss_sync_on: 1;    //  2
    UINT32 reg_gcodec_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_gcodec_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_gcodec_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_gcodec_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_gcodec_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_GCODEC_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2064    vcodec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vcodec_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_vcodec_aiopllss_dss: 1;    //   3
    UINT32 reg_vcodec_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_vcodec_aiopllss_cih: 4;    //  11:8
    UINT32 reg_vcodec_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_vcodec_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_vcodec_aiopllss_m: 6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2068    vcodec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vcodec_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_vcodec_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_vcodec_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_206C    vcodec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vcodec_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_vcodec_aiopllss_freq_update: 1;    //  1
    UINT32 reg_vcodec_aiopllss_sync_on: 1;    //  2
    UINT32 reg_vcodec_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_vcodec_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_vcodec_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_vcodec_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_vcodec_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_VCODEC_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2070    cpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_cpu_aiopllss_dss: 1;    //      3
    UINT32 reg_cpu_aiopllss_cih2: 4;    //  7: 4
    UINT32 reg_cpu_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_cpu_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_cpu_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_cpu_aiopllss_m :  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_CPU_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2074    cpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_cpu_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_cpu_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_CPU_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2078    cpu_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_cpu_aiopllss_freq_update: 1;    //  1
    UINT32 reg_cpu_aiopllss_sync_on: 1;    //  2
    UINT32 reg_cpu_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_cpu_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_cpu_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_cpu_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_cpu_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_CPU_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_207C    gpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_gpu_aiopllss_dss: 1;    //      3
    UINT32 reg_gpu_aiopllss_cih2: 4;    //  7: 4
    UINT32 reg_gpu_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_gpu_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_gpu_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_gpu_aiopllss_m :  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}CRG_TOP_CTRL_GPU_AIOPLLSS_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2080    gpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_gpu_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_gpu_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}CRG_TOP_CTRL_GPU_AIOPLLSS_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2084    gpu_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_gpu_aiopllss_freq_update: 1;    //  1
    UINT32 reg_gpu_aiopllss_sync_on: 1;    //  2
    UINT32 reg_gpu_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_gpu_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_gpu_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_gpu_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_gpu_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_GPU_AIOPLLSS_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2088    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_pll_pdb_ctrl: 1;    //     0
    UINT32 reg_earcpll_pll_pdb_ctrl: 1;    //  1
    UINT32 reg_apll_pll_pdb_ctrl: 1;    //     2
    UINT32 reg_f54pll_pll_pdb_ctrl: 1;    //   3
    UINT32 reg_gpu_pll_pdb_ctrl: 1;    //      4
    UINT32 reg_cpu_pll_pdb_ctrl: 1;    //      5
    UINT32 reg_vcodec_pll_pdb_ctrl: 1;    //   6
    UINT32 reg_gcodec_pll_pdb_ctrl: 1;    //   7
    UINT32 reg_pcore_pll_pdb_ctrl: 1;    //    8
    UINT32 reg_gcore_pll_pdb_ctrl: 1;    //    9
    UINT32 reg_m0_pll_pdb_ctrl:  1;    //     10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_208C    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_pll_lock  :  1;    //      0
    UINT32 reg_earcpll_pll_lock: 1;    //      1
    UINT32 reg_apll_pll_lock  :  1;    //      2
    UINT32 reg_f54pll_pll_lock:  1;    //      3
    UINT32 reg_gpu_pll_lock   :  1;    //      4
    UINT32 reg_cpu_pll_lock   :  1;    //      5
    UINT32 reg_vcodec_pll_lock:  1;    //      6
    UINT32 reg_gcodec_pll_lock:  1;    //      7
    UINT32 reg_pcore_pll_lock :  1;    //      8
    UINT32 reg_gcore_pll_lock :  1;    //      9
    UINT32 reg_m0_pll_lock    :  1;    //     10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2090    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_lock_bypass: 1;    //   0
    UINT32 reg_apll_lock_bypass: 1;    //      1
    UINT32 reg_disp_pll_lock_bypass: 1;    //  2
    UINT32 reg_disp_frpll_lock_bypass: 1;    //  3
    UINT32 reg_gpu_pll_lock_bypass: 1;    //   4
    UINT32 reg_cpu_pll_lock_bypass: 1;    //   5
    UINT32 reg_vcodec_pll_lock_bypass: 1;    //  6
    UINT32 reg_gcodec_pll_lock_bypass: 1;    //  7
    UINT32 reg_pcore_pll_lock_bypass: 1;    //  8
    UINT32 reg_gcore_pll_lock_bypass: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2094    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_core_660: 2;    //   1: 0
    UINT32 reg_pll_sel_core_660: 2;    //   3: 2
    UINT32 reg_clk_sel_core_533: 2;    //   5: 4
    UINT32 reg_pll_sel_core_533: 2;    //   7: 6
    UINT32 reg_clk_sel_core_600: 2;    //   9: 8
    UINT32 reg_pll_sel_core_600: 2;    //  11:10
    UINT32 reg_clk_sel_emmc_400: 2;    //  13:12
    UINT32 reg_pll_sel_emmc_400: 2;    //  15:14
    UINT32 reg_clk_sel_core_400: 2;    //  17:16
    UINT32 reg_pll_sel_core_400: 2;    //  19:18
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_2098    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_core_800: 2;    //   1: 0
    UINT32 reg_pll_sel_core_800: 2;    //   3: 2
    UINT32 reg_clk_sel_core_560: 2;    //   5: 4
    UINT32 reg_pll_sel_core_560: 2;    //   7: 6
    UINT32 reg_clk_sel_pcore_400: 2;    //  9: 8
    UINT32 reg_pll_sel_pcore_400: 2;    //  11:10
    UINT32 reg_clk_sel_core_480: 2;    //  13:12
    UINT32 reg_pll_sel_core_480: 2;    //  15:14
    UINT32 reg_clk_sel_core_vd1_660: 2;    //  17:16
    UINT32 reg_pll_sel_core_vd1_660: 2;    //  19:18
    UINT32 reg_clk_sel_gpu    :  1;    //     20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_209C    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}CRG_TOP_CTRL_CRG_TOP_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CRG_TOP_CTRL_DISP_AIOPLL_00_M23A0_T    disp_aiopll_00;      // 0xCC92_2000
    CRG_TOP_CTRL_DISP_AIOPLL_01_M23A0_T    disp_aiopll_01;      // 0xCC92_2004
    CRG_TOP_CTRL_DISP_AIOPLL_02_M23A0_T    disp_aiopll_02;      // 0xCC92_2008
    CRG_TOP_CTRL_F54PLL_FRPLL_00_M23A0_T    f54pll_frpll_00;    // 0xCC92_200C
    CRG_TOP_CTRL_F54PLL_FRPLL_01_M23A0_T    f54pll_frpll_01;    // 0xCC92_2010
    CRG_TOP_CTRL_F54PLL_FRPLL_02_M23A0_T    f54pll_frpll_02;    // 0xCC92_2014
    CRG_TOP_CTRL_F54PLL_FRPLL_03_M23A0_T    f54pll_frpll_03;    // 0xCC92_2018
    CRG_TOP_CTRL_APLL_FRPLL_00_M23A0_T    apll_frpll_00;        // 0xCC92_201C
    CRG_TOP_CTRL_APLL_FRPLL_01_M23A0_T    apll_frpll_01;        // 0xCC92_2020
    CRG_TOP_CTRL_APLL_FRPLL_02_M23A0_T    apll_frpll_02;        // 0xCC92_2024
    CRG_TOP_CTRL_APLL_FRPLL_SSCG_R00_M23A0_T    apll_frpll_sscg_r00;    // 0xCC92_2028
    CRG_TOP_CTRL_EARCPLL_FRPLL_00_M23A0_T    earcpll_frpll_00;    // 0xCC92_202C
    CRG_TOP_CTRL_EARCPLL_FRPLL_01_M23A0_T    earcpll_frpll_01;    // 0xCC92_2030
    CRG_TOP_CTRL_EARCPLL_FRPLL_02_M23A0_T    earcpll_frpll_02;    // 0xCC92_2034
    CRG_TOP_CTRL_EARCPLL_FRPLL_SSCG_R00_M23A0_T    earcpll_frpll_sscg_r00;    // 0xCC92_2038
    CRG_TOP_CTRL_FCW_MUX_00_M23A0_T    fcw_mux_00 ;             // 0xCC92_203C
    CRG_TOP_CTRL_GCORE_AIOPLLSS_00_M23A0_T    gcore_aiopllss_00;    // 0xCC92_2040
    CRG_TOP_CTRL_GCORE_AIOPLLSS_01_M23A0_T    gcore_aiopllss_01;    // 0xCC92_2044
    CRG_TOP_CTRL_GCORE_AIOPLLSS_02_M23A0_T    gcore_aiopllss_02;    // 0xCC92_2048
    CRG_TOP_CTRL_PCORE_AIOPLLSS_00_M23A0_T    pcore_aiopllss_00;    // 0xCC92_204C
    CRG_TOP_CTRL_PCORE_AIOPLLSS_01_M23A0_T    pcore_aiopllss_01;    // 0xCC92_2050
    CRG_TOP_CTRL_PCORE_AIOPLLSS_02_M23A0_T    pcore_aiopllss_02;    // 0xCC92_2054
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_00_M23A0_T    gcodec_aiopllss_00;    // 0xCC92_2058
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_01_M23A0_T    gcodec_aiopllss_01;    // 0xCC92_205C
    CRG_TOP_CTRL_GCODEC_AIOPLLSS_02_M23A0_T    gcodec_aiopllss_02;    // 0xCC92_2060
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_00_M23A0_T    vcodec_aiopllss_00;    // 0xCC92_2064
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_01_M23A0_T    vcodec_aiopllss_01;    // 0xCC92_2068
    CRG_TOP_CTRL_VCODEC_AIOPLLSS_02_M23A0_T    vcodec_aiopllss_02;    // 0xCC92_206C
    CRG_TOP_CTRL_CPU_AIOPLLSS_00_M23A0_T    cpu_aiopllss_00;    // 0xCC92_2070
    CRG_TOP_CTRL_CPU_AIOPLLSS_01_M23A0_T    cpu_aiopllss_01;    // 0xCC92_2074
    CRG_TOP_CTRL_CPU_AIOPLLSS_02_M23A0_T    cpu_aiopllss_02;    // 0xCC92_2078
    CRG_TOP_CTRL_GPU_AIOPLLSS_00_M23A0_T    gpu_aiopllss_00;    // 0xCC92_207C
    CRG_TOP_CTRL_GPU_AIOPLLSS_01_M23A0_T    gpu_aiopllss_01;    // 0xCC92_2080
    CRG_TOP_CTRL_GPU_AIOPLLSS_02_M23A0_T    gpu_aiopllss_02;    // 0xCC92_2084
    CRG_TOP_CTRL_CRG_TOP_00_M23A0_T    crg_top_00 ;             // 0xCC92_2088
    CRG_TOP_CTRL_CRG_TOP_01_M23A0_T    crg_top_01 ;             // 0xCC92_208C
    CRG_TOP_CTRL_CRG_TOP_02_M23A0_T    crg_top_02 ;             // 0xCC92_2090
    CRG_TOP_CTRL_CRG_TOP_03_M23A0_T    crg_top_03 ;             // 0xCC92_2094
    CRG_TOP_CTRL_CRG_TOP_04_M23A0_T    crg_top_04 ;             // 0xCC92_2098
    CRG_TOP_CTRL_CRG_TOP_05_M23A0_T    crg_top_05 ;             // 0xCC92_209C
}CRG_TOP_CTRL_REG_M23A0_T;
/* 40 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

