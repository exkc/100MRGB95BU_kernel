#ifndef _TRG_CTRL_REG_O24A0_H_
#define _TRG_CTRL_REG_O24A0_H_

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
    0xCC6A_2000    apll_frpll_00 ''
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
}TRG_CTRL_APLL_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2004    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fout_en    :  1,    //      0
    reg_apll_frpll_syncon     :  1,    //      1
    reg_apll_frpll_m          :  6,    //   7: 2
    reg_apll_frpll_fcw        : 24;    //  31: 8
}TRG_CTRL_APLL_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2008    apll_frpll_02 ''
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
}TRG_CTRL_APLL_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_200C    apll_frpll_sscg_r00 ''
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
}TRG_CTRL_APLL_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2010    apll_fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_fcw_mux_sel      :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}TRG_CTRL_APLL_FCW_MUX_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2020    core_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_core_aiopllss_dss     :  1,    //      3
    reg_core_aiopllss_cih2    :  4,    //   7: 4
    reg_core_aiopllss_cih     :  4,    //  11: 8
    reg_core_aiopllss_nsc     :  4,    //  15:12
    reg_core_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_core_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CORE_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2024    core_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_core_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_core_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CORE_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2028    core_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_fout1_en:  1,    //      0
    reg_core_aiopllss_freq_update: 1,    //    1
    reg_core_aiopllss_sync_on :  1,    //      2
    reg_core_aiopllss_wake_bypass: 1,    //    3
    reg_core_aiopllss_offset_mode: 1,    //    4
    reg_core_aiopllss_fine_div:  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_core_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_core_aiopllss_offset  :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_CORE_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2030    emmc_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_emmc_aiopllss_dss     :  1,    //      3
    reg_emmc_aiopllss_cih2    :  4,    //   7: 4
    reg_emmc_aiopllss_cih     :  4,    //  11: 8
    reg_emmc_aiopllss_nsc     :  4,    //  15:12
    reg_emmc_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_emmc_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_EMMC_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2034    emmc_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_emmc_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_emmc_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_EMMC_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2038    emmc_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_fout1_en:  1,    //      0
    reg_emmc_aiopllss_freq_update: 1,    //    1
    reg_emmc_aiopllss_sync_on :  1,    //      2
    reg_emmc_aiopllss_wake_bypass: 1,    //    3
    reg_emmc_aiopllss_offset_mode: 1,    //    4
    reg_emmc_aiopllss_fine_div:  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_emmc_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_emmc_aiopllss_offset  :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_EMMC_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2040    bus_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_bus_aiopllss_dss      :  1,    //      3
    reg_bus_aiopllss_cih2     :  4,    //   7: 4
    reg_bus_aiopllss_cih      :  4,    //  11: 8
    reg_bus_aiopllss_nsc      :  4,    //  15:12
    reg_bus_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_bus_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_BUS_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2044    bus_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_bus_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_bus_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_BUS_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2048    bus_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_fout1_en :  1,    //      0
    reg_bus_aiopllss_freq_update: 1,    //     1
    reg_bus_aiopllss_sync_on  :  1,    //      2
    reg_bus_aiopllss_wake_bypass: 1,    //     3
    reg_bus_aiopllss_offset_mode: 1,    //     4
    reg_bus_aiopllss_fine_div :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_bus_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_bus_aiopllss_offset   :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_BUS_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2050    codec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_accuracy: 2,    //   1: 0
                              :  1,    //      2 reserved
    reg_codec_aiopllss_dss    :  1,    //      3
    reg_codec_aiopllss_cih2   :  4,    //   7: 4
    reg_codec_aiopllss_cih    :  4,    //  11: 8
    reg_codec_aiopllss_nsc    :  4,    //  15:12
    reg_codec_aiopllss_npc    :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_codec_aiopllss_m      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CODEC_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2054    codec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_out_div:  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_codec_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_codec_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CODEC_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2058    codec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_fout1_en: 1,    //      0
    reg_codec_aiopllss_freq_update: 1,    //   1
    reg_codec_aiopllss_sync_on:  1,    //      2
    reg_codec_aiopllss_wake_bypass: 1,    //   3
    reg_codec_aiopllss_offset_mode: 1,    //   4
    reg_codec_aiopllss_fine_div: 1,    //      5
                              :  2,    //   7: 6 reserved
    reg_codec_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_codec_aiopllss_offset :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_CODEC_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2060    cpu_aiopllss_00 ''
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
}TRG_CTRL_CPU_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2064    cpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_cpu_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_cpu_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CPU_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2068    cpu_aiopllss_02 ''
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
}TRG_CTRL_CPU_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2070    gpu_aiopllss_00 ''
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
}TRG_CTRL_GPU_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2074    gpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_gpu_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_gpu_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_GPU_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2078    gpu_aiopllss_02 ''
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
}TRG_CTRL_GPU_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2090    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_pdb_ctrl     :  1,    //      0
    reg_apll_pll_pdb_ctrl     :  1,    //      1
    reg_gpu_pll_pdb_ctrl      :  1,    //      2
    reg_cpu_pll_pdb_ctrl      :  1,    //      3
    reg_codec_pll_pdb_ctrl    :  1,    //      4
    reg_emmc_pll_pdb_ctrl     :  1,    //      5
    reg_bus_pll_pdb_ctrl      :  1,    //      6
    reg_disp_pll_pdb_ctrl     :  1,    //      7
    reg_oif_pll_pdb_ctrl      :  1,    //      8
                              :  1,    //      9 reserved
    reg_pqe_pll_pdb_ctrl      :  1,    //     10
    reg_earc_pll_pdb_ctrl     :  1,    //     11
    reg_m0_pll_pdb_ctrl       :  1,    //     12
    reg_m1_pll_pdb_ctrl       :  1,    //     13
    reg_m2_pll_pdb_ctrl       :  1,    //     14
                              : 17;    //  31:15 reserved
}TRG_CTRL_CRG_TOP_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2094    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_lock         :  1,    //      0
    reg_apll_pll_lock         :  1,    //      1
    reg_gpu_pll_lock          :  1,    //      2
    reg_cpu_pll_lock          :  1,    //      3
    reg_codec_pll_lock        :  1,    //      4
    reg_emmc_pll_lock         :  1,    //      5
    reg_bus_pll_lock          :  1,    //      6
    reg_disp_pll_lock         :  1,    //      7
    reg_oif_pll_lock          :  1,    //      8
                              :  1,    //      9 reserved
    reg_pqe_pll_lock          :  1,    //     10
    reg_earc_pll_lock         :  1,    //     11
                              : 20;    //  31:12 reserved
}TRG_CTRL_CRG_TOP_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2098    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_lock_bypass  :  1,    //      0
    reg_apll_lock_bypass      :  1,    //      1
    reg_gpu_pll_lock_bypass   :  1,    //      2
    reg_cpu_pll_lock_bypass   :  1,    //      3
    reg_codec_pll_lock_bypass :  1,    //      4
    reg_emmc_pll_lock_bypass  :  1,    //      5
    reg_bus_pll_lock_bypass   :  1,    //      6
    reg_disp_pll_lock_bypass  :  1,    //      7
    reg_oif_pll_lock_bypass   :  1,    //      8
                              :  1,    //      9 reserved
    reg_pqe_frpll_lock_bypass :  1,    //     10
    reg_earc_frpll_lock_bypass:  1,    //     11
                              : 20;    //  31:12 reserved
}TRG_CTRL_CRG_TOP_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_209C    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_core_660      :  2,    //   1: 0
    reg_pll_sel_core_660      :  2,    //   3: 2
    reg_clk_sel_core_800      :  2,    //   5: 4
    reg_pll_sel_core_800      :  2,    //   7: 6
    reg_clk_sel_core_480      :  2,    //   9: 8
    reg_pll_sel_core_480      :  2,    //  11:10
                              :  4,    //  15:12 reserved
    reg_clk_sel_core_600      :  2,    //  17:16
    reg_pll_sel_core_600      :  2,    //  19:18
    reg_clk_sel_emmc_400      :  2,    //  21:20
    reg_pll_sel_emmc_400      :  2,    //  23:22
    reg_clk_sel_core_884      :  2,    //  25:24
    reg_pll_sel_core_884      :  2,    //  27:26
    reg_clk_sel_core_400      :  2,    //  29:28
    reg_pll_sel_core_400      :  2;    //  31:30
}TRG_CTRL_CRG_TOP_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20A4    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B0    earcpll_frpll_00 ''
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
}TRG_CTRL_EARCPLL_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B4    earcpll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_frpll_fout_en :  1,    //      0
    reg_earcpll_frpll_syncon  :  1,    //      1
    reg_earcpll_frpll_m       :  6,    //   7: 2
    reg_earcpll_frpll_fcw     : 24;    //  31: 8
}TRG_CTRL_EARCPLL_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B8    earcpll_frpll_02 ''
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
}TRG_CTRL_EARCPLL_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20BC    earcpll_frpll_sscg_r00 ''
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
}TRG_CTRL_EARCPLL_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20C0    earcpll_fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earcpll_fcw_mux_sel   :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}TRG_CTRL_EARCPLL_FCW_MUX_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20D0    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_watchdog_reset_sel    :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_WOV_AON_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20D4    rxclkdrv_md_trg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_md_trg_pdb   :  1,    //      0
    reg_rxclkdrv_md_trg_smv   :  1,    //      1
                              : 30;    //   31:2 reserved
}TRG_CTRL_RXCLKDRV_MD_TRG_O24A0_T;

/*-----------------------------------------------------------------------------------------
    trg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TRG_CTRL_APLL_FRPLL_00_O24A0_T     apll_frpll_00;           // 0xCC6A_2000
    TRG_CTRL_APLL_FRPLL_01_O24A0_T     apll_frpll_01;           // 0xCC6A_2004
    TRG_CTRL_APLL_FRPLL_02_O24A0_T     apll_frpll_02;           // 0xCC6A_2008
    TRG_CTRL_APLL_FRPLL_SSCG_R00_O24A0_T    apll_frpll_sscg_r00;    // 0xCC6A_200C
    TRG_CTRL_APLL_FCW_MUX_00_O24A0_T    apll_fcw_mux_00;        // 0xCC6A_2010
    UINT32                             _rsvd_00[3];             // 0xCC6A_2014 ~ 0xCC6A_201C
    TRG_CTRL_CORE_AIOPLLSS_00_O24A0_T    core_aiopllss_00;      // 0xCC6A_2020
    TRG_CTRL_CORE_AIOPLLSS_01_O24A0_T    core_aiopllss_01;      // 0xCC6A_2024
    TRG_CTRL_CORE_AIOPLLSS_02_O24A0_T    core_aiopllss_02;      // 0xCC6A_2028
    UINT32                             _rsvd_01[1];             // 0xCC6A_202C
    TRG_CTRL_EMMC_AIOPLLSS_00_O24A0_T    emmc_aiopllss_00;      // 0xCC6A_2030
    TRG_CTRL_EMMC_AIOPLLSS_01_O24A0_T    emmc_aiopllss_01;      // 0xCC6A_2034
    TRG_CTRL_EMMC_AIOPLLSS_02_O24A0_T    emmc_aiopllss_02;      // 0xCC6A_2038
    UINT32                             _rsvd_02[1];             // 0xCC6A_203C
    TRG_CTRL_BUS_AIOPLLSS_00_O24A0_T    bus_aiopllss_00;        // 0xCC6A_2040
    TRG_CTRL_BUS_AIOPLLSS_01_O24A0_T    bus_aiopllss_01;        // 0xCC6A_2044
    TRG_CTRL_BUS_AIOPLLSS_02_O24A0_T    bus_aiopllss_02;        // 0xCC6A_2048
    UINT32                             _rsvd_03[1];             // 0xCC6A_204C
    TRG_CTRL_CODEC_AIOPLLSS_00_O24A0_T    codec_aiopllss_00;    // 0xCC6A_2050
    TRG_CTRL_CODEC_AIOPLLSS_01_O24A0_T    codec_aiopllss_01;    // 0xCC6A_2054
    TRG_CTRL_CODEC_AIOPLLSS_02_O24A0_T    codec_aiopllss_02;    // 0xCC6A_2058
    UINT32                             _rsvd_04[1];             // 0xCC6A_205C
    TRG_CTRL_CPU_AIOPLLSS_00_O24A0_T    cpu_aiopllss_00;        // 0xCC6A_2060
    TRG_CTRL_CPU_AIOPLLSS_01_O24A0_T    cpu_aiopllss_01;        // 0xCC6A_2064
    TRG_CTRL_CPU_AIOPLLSS_02_O24A0_T    cpu_aiopllss_02;        // 0xCC6A_2068
    UINT32                             _rsvd_05[1];             // 0xCC6A_206C
    TRG_CTRL_GPU_AIOPLLSS_00_O24A0_T    gpu_aiopllss_00;        // 0xCC6A_2070
    TRG_CTRL_GPU_AIOPLLSS_01_O24A0_T    gpu_aiopllss_01;        // 0xCC6A_2074
    TRG_CTRL_GPU_AIOPLLSS_02_O24A0_T    gpu_aiopllss_02;        // 0xCC6A_2078
    UINT32                             _rsvd_06[5];             // 0xCC6A_207C ~ 0xCC6A_208C
    TRG_CTRL_CRG_TOP_00_O24A0_T        crg_top_00 ;             // 0xCC6A_2090
    TRG_CTRL_CRG_TOP_01_O24A0_T        crg_top_01 ;             // 0xCC6A_2094
    TRG_CTRL_CRG_TOP_02_O24A0_T        crg_top_02 ;             // 0xCC6A_2098
    TRG_CTRL_CRG_TOP_03_O24A0_T        crg_top_03 ;             // 0xCC6A_209C
    UINT32                             _rsvd_07[1];             // 0xCC6A_20A0
    TRG_CTRL_CRG_TOP_05_O24A0_T        crg_top_05 ;             // 0xCC6A_20A4
    UINT32                             _rsvd_08[2];             // 0xCC6A_20A8 ~ 0xCC6A_20AC
    TRG_CTRL_EARCPLL_FRPLL_00_O24A0_T    earcpll_frpll_00;      // 0xCC6A_20B0
    TRG_CTRL_EARCPLL_FRPLL_01_O24A0_T    earcpll_frpll_01;      // 0xCC6A_20B4
    TRG_CTRL_EARCPLL_FRPLL_02_O24A0_T    earcpll_frpll_02;      // 0xCC6A_20B8
    TRG_CTRL_EARCPLL_FRPLL_SSCG_R00_O24A0_T    earcpll_frpll_sscg_r00;    // 0xCC6A_20BC
    TRG_CTRL_EARCPLL_FCW_MUX_00_O24A0_T    earcpll_fcw_mux_00;    // 0xCC6A_20C0
    UINT32                             _rsvd_09[3];             // 0xCC6A_20C4 ~ 0xCC6A_20CC
    TRG_CTRL_CRG_TOP_WOV_AON_R01_O24A0_T    crg_top_wov_aon_r01;    // 0xCC6A_20D0
    TRG_CTRL_RXCLKDRV_MD_TRG_O24A0_T    rxclkdrv_md_trg;        // 0xCC6A_20D4
}TRG_CTRL_REG_O24A0_T;
/* 35 regs */

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

#define TRG_CTRL_APLL_FRPLL_00_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define TRG_CTRL_APLL_FRPLL_01_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define TRG_CTRL_APLL_FRPLL_02_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define TRG_CTRL_APLL_FRPLL_SSCG_R00_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define TRG_CTRL_APLL_FCW_MUX_00_O24A0_T_OFF                (BASEADDRESS+0x0010)
#define TRG_CTRL_CORE_AIOPLLSS_00_O24A0_T_OFF               (BASEADDRESS+0x0020)
#define TRG_CTRL_CORE_AIOPLLSS_01_O24A0_T_OFF               (BASEADDRESS+0x0024)
#define TRG_CTRL_CORE_AIOPLLSS_02_O24A0_T_OFF               (BASEADDRESS+0x0028)
#define TRG_CTRL_EMMC_AIOPLLSS_00_O24A0_T_OFF               (BASEADDRESS+0x0030)
#define TRG_CTRL_EMMC_AIOPLLSS_01_O24A0_T_OFF               (BASEADDRESS+0x0034)
#define TRG_CTRL_EMMC_AIOPLLSS_02_O24A0_T_OFF               (BASEADDRESS+0x0038)
#define TRG_CTRL_BUS_AIOPLLSS_00_O24A0_T_OFF                (BASEADDRESS+0x0040)
#define TRG_CTRL_BUS_AIOPLLSS_01_O24A0_T_OFF                (BASEADDRESS+0x0044)
#define TRG_CTRL_BUS_AIOPLLSS_02_O24A0_T_OFF                (BASEADDRESS+0x0048)
#define TRG_CTRL_CODEC_AIOPLLSS_00_O24A0_T_OFF              (BASEADDRESS+0x0050)
#define TRG_CTRL_CODEC_AIOPLLSS_01_O24A0_T_OFF              (BASEADDRESS+0x0054)
#define TRG_CTRL_CODEC_AIOPLLSS_02_O24A0_T_OFF              (BASEADDRESS+0x0058)
#define TRG_CTRL_CPU_AIOPLLSS_00_O24A0_T_OFF                (BASEADDRESS+0x0060)
#define TRG_CTRL_CPU_AIOPLLSS_01_O24A0_T_OFF                (BASEADDRESS+0x0064)
#define TRG_CTRL_CPU_AIOPLLSS_02_O24A0_T_OFF                (BASEADDRESS+0x0068)
#define TRG_CTRL_GPU_AIOPLLSS_00_O24A0_T_OFF                (BASEADDRESS+0x0070)
#define TRG_CTRL_GPU_AIOPLLSS_01_O24A0_T_OFF                (BASEADDRESS+0x0074)
#define TRG_CTRL_GPU_AIOPLLSS_02_O24A0_T_OFF                (BASEADDRESS+0x0078)
#define TRG_CTRL_CRG_TOP_00_O24A0_T_OFF                     (BASEADDRESS+0x0090)
#define TRG_CTRL_CRG_TOP_01_O24A0_T_OFF                     (BASEADDRESS+0x0094)
#define TRG_CTRL_CRG_TOP_02_O24A0_T_OFF                     (BASEADDRESS+0x0098)
#define TRG_CTRL_CRG_TOP_03_O24A0_T_OFF                     (BASEADDRESS+0x009C)
#define TRG_CTRL_CRG_TOP_05_O24A0_T_OFF                     (BASEADDRESS+0x00A4)
#define TRG_CTRL_EARCPLL_FRPLL_00_O24A0_T_OFF               (BASEADDRESS+0x00B0)
#define TRG_CTRL_EARCPLL_FRPLL_01_O24A0_T_OFF               (BASEADDRESS+0x00B4)
#define TRG_CTRL_EARCPLL_FRPLL_02_O24A0_T_OFF               (BASEADDRESS+0x00B8)
#define TRG_CTRL_EARCPLL_FRPLL_SSCG_R00_O24A0_T_OFF         (BASEADDRESS+0x00BC)
#define TRG_CTRL_EARCPLL_FCW_MUX_00_O24A0_T_OFF             (BASEADDRESS+0x00C0)
#define TRG_CTRL_CRG_TOP_WOV_AON_R01_O24A0_T_OFF            (BASEADDRESS+0x00D0)
#define TRG_CTRL_RXCLKDRV_MD_TRG_O24A0_T_OFF                (BASEADDRESS+0x00D4)

/*-----------------------------------------------------------------------------------------
    0xCC6A_2000    apll_frpll_00 ''
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
}TRG_CTRL_APLL_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2004    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_fout_en: 1;    //    0
    UINT32 reg_apll_frpll_syncon: 1;    //     1
    UINT32 reg_apll_frpll_m   :  6;    //   7: 2
    UINT32 reg_apll_frpll_fcw : 24;    //  31: 8
    };
}TRG_CTRL_APLL_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2008    apll_frpll_02 ''
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
}TRG_CTRL_APLL_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_200C    apll_frpll_sscg_r00 ''
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
}TRG_CTRL_APLL_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2010    apll_fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_fcw_mux_sel: 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}TRG_CTRL_APLL_FCW_MUX_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2020    core_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_core_aiopllss_dss: 1;    //     3
    UINT32 reg_core_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_core_aiopllss_cih: 4;    //  11:8
    UINT32 reg_core_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_core_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_core_aiopllss_m:  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CORE_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2024    core_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_core_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_core_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CORE_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2028    core_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_core_aiopllss_freq_update: 1;    //  1
    UINT32 reg_core_aiopllss_sync_on: 1;    //  2
    UINT32 reg_core_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_core_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_core_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_core_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_core_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_CORE_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2030    emmc_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_emmc_aiopllss_dss: 1;    //     3
    UINT32 reg_emmc_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_emmc_aiopllss_cih: 4;    //  11:8
    UINT32 reg_emmc_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_emmc_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_emmc_aiopllss_m:  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}TRG_CTRL_EMMC_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2034    emmc_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_emmc_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_emmc_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_EMMC_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2038    emmc_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_emmc_aiopllss_freq_update: 1;    //  1
    UINT32 reg_emmc_aiopllss_sync_on: 1;    //  2
    UINT32 reg_emmc_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_emmc_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_emmc_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_emmc_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_emmc_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_EMMC_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2040    bus_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_bus_aiopllss_dss: 1;    //      3
    UINT32 reg_bus_aiopllss_cih2: 4;    //  7: 4
    UINT32 reg_bus_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_bus_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_bus_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_bus_aiopllss_m :  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}TRG_CTRL_BUS_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2044    bus_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_bus_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_bus_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_BUS_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2048    bus_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_bus_aiopllss_freq_update: 1;    //  1
    UINT32 reg_bus_aiopllss_sync_on: 1;    //  2
    UINT32 reg_bus_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_bus_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_bus_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_bus_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_bus_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_BUS_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2050    codec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_codec_aiopllss_dss: 1;    //    3
    UINT32 reg_codec_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_codec_aiopllss_cih: 4;    //  11:8
    UINT32 reg_codec_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_codec_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_codec_aiopllss_m: 6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CODEC_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2054    codec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_codec_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_codec_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CODEC_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2058    codec_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_codec_aiopllss_freq_update: 1;    //  1
    UINT32 reg_codec_aiopllss_sync_on: 1;    //  2
    UINT32 reg_codec_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_codec_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_codec_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_codec_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_codec_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_CODEC_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2060    cpu_aiopllss_00 ''
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
}TRG_CTRL_CPU_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2064    cpu_aiopllss_01 ''
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
}TRG_CTRL_CPU_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2068    cpu_aiopllss_02 ''
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
}TRG_CTRL_CPU_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2070    gpu_aiopllss_00 ''
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
}TRG_CTRL_GPU_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2074    gpu_aiopllss_01 ''
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
}TRG_CTRL_GPU_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2078    gpu_aiopllss_02 ''
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
}TRG_CTRL_GPU_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2090    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_pdb_ctrl: 1;    //     0
    UINT32 reg_apll_pll_pdb_ctrl: 1;    //     1
    UINT32 reg_gpu_pll_pdb_ctrl: 1;    //      2
    UINT32 reg_cpu_pll_pdb_ctrl: 1;    //      3
    UINT32 reg_codec_pll_pdb_ctrl: 1;    //    4
    UINT32 reg_emmc_pll_pdb_ctrl: 1;    //     5
    UINT32 reg_bus_pll_pdb_ctrl: 1;    //      6
    UINT32 reg_disp_pll_pdb_ctrl: 1;    //     7
    UINT32 reg_oif_pll_pdb_ctrl: 1;    //      8
    UINT32 resvd00            :  1;    //      9 reserved
    UINT32 reg_pqe_pll_pdb_ctrl: 1;    //     10
    UINT32 reg_earc_pll_pdb_ctrl: 1;    //    11
    UINT32 reg_m0_pll_pdb_ctrl:  1;    //     12
    UINT32 reg_m1_pll_pdb_ctrl:  1;    //     13
    UINT32 reg_m2_pll_pdb_ctrl:  1;    //     14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}TRG_CTRL_CRG_TOP_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2094    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_lock  :  1;    //      0
    UINT32 reg_apll_pll_lock  :  1;    //      1
    UINT32 reg_gpu_pll_lock   :  1;    //      2
    UINT32 reg_cpu_pll_lock   :  1;    //      3
    UINT32 reg_codec_pll_lock :  1;    //      4
    UINT32 reg_emmc_pll_lock  :  1;    //      5
    UINT32 reg_bus_pll_lock   :  1;    //      6
    UINT32 reg_disp_pll_lock  :  1;    //      7
    UINT32 reg_oif_pll_lock   :  1;    //      8
    UINT32 resvd00            :  1;    //      9 reserved
    UINT32 reg_pqe_pll_lock   :  1;    //     10
    UINT32 reg_earc_pll_lock  :  1;    //     11
    UINT32 resvd01            : 20;    //  31:12 reserved
    };
}TRG_CTRL_CRG_TOP_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_2098    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_lock_bypass: 1;    //  0
    UINT32 reg_apll_lock_bypass: 1;    //      1
    UINT32 reg_gpu_pll_lock_bypass: 1;    //   2
    UINT32 reg_cpu_pll_lock_bypass: 1;    //   3
    UINT32 reg_codec_pll_lock_bypass: 1;    //  4
    UINT32 reg_emmc_pll_lock_bypass: 1;    //  5
    UINT32 reg_bus_pll_lock_bypass: 1;    //   6
    UINT32 reg_disp_pll_lock_bypass: 1;    //  7
    UINT32 reg_oif_pll_lock_bypass: 1;    //   8
    UINT32 resvd00            :  1;    //      9 reserved
    UINT32 reg_pqe_frpll_lock_bypass: 1;    //  10
    UINT32 reg_earc_frpll_lock_bypass: 1;    //  11
    UINT32 resvd01            : 20;    //  31:12 reserved
    };
}TRG_CTRL_CRG_TOP_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_209C    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_core_660: 2;    //   1: 0
    UINT32 reg_pll_sel_core_660: 2;    //   3: 2
    UINT32 reg_clk_sel_core_800: 2;    //   5: 4
    UINT32 reg_pll_sel_core_800: 2;    //   7: 6
    UINT32 reg_clk_sel_core_480: 2;    //   9: 8
    UINT32 reg_pll_sel_core_480: 2;    //  11:10
    UINT32 resvd00            :  4;    //  15:12 reserved
    UINT32 reg_clk_sel_core_600: 2;    //  17:16
    UINT32 reg_pll_sel_core_600: 2;    //  19:18
    UINT32 reg_clk_sel_emmc_400: 2;    //  21:20
    UINT32 reg_pll_sel_emmc_400: 2;    //  23:22
    UINT32 reg_clk_sel_core_884: 2;    //  25:24
    UINT32 reg_pll_sel_core_884: 2;    //  27:26
    UINT32 reg_clk_sel_core_400: 2;    //  29:28
    UINT32 reg_pll_sel_core_400: 2;    //  31:30
    };
}TRG_CTRL_CRG_TOP_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20A4    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B0    earcpll_frpll_00 ''
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
}TRG_CTRL_EARCPLL_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B4    earcpll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_frpll_fout_en: 1;    //  0
    UINT32 reg_earcpll_frpll_syncon: 1;    //  1
    UINT32 reg_earcpll_frpll_m:  6;    //   7: 2
    UINT32 reg_earcpll_frpll_fcw: 24;    //  31:8
    };
}TRG_CTRL_EARCPLL_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20B8    earcpll_frpll_02 ''
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
}TRG_CTRL_EARCPLL_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20BC    earcpll_frpll_sscg_r00 ''
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
}TRG_CTRL_EARCPLL_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20C0    earcpll_fcw_mux_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earcpll_fcw_mux_sel: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}TRG_CTRL_EARCPLL_FCW_MUX_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20D0    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_watchdog_reset_sel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_WOV_AON_R01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_20D4    rxclkdrv_md_trg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_md_trg_pdb: 1;    //   0
    UINT32 reg_rxclkdrv_md_trg_smv: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}TRG_CTRL_RXCLKDRV_MD_TRG_O24A0_T;

/*-----------------------------------------------------------------------------------------
    trg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TRG_CTRL_APLL_FRPLL_00_O24A0_T     apll_frpll_00;           // 0xCC6A_2000
    TRG_CTRL_APLL_FRPLL_01_O24A0_T     apll_frpll_01;           // 0xCC6A_2004
    TRG_CTRL_APLL_FRPLL_02_O24A0_T     apll_frpll_02;           // 0xCC6A_2008
    TRG_CTRL_APLL_FRPLL_SSCG_R00_O24A0_T    apll_frpll_sscg_r00;    // 0xCC6A_200C
    TRG_CTRL_APLL_FCW_MUX_00_O24A0_T    apll_fcw_mux_00;        // 0xCC6A_2010
    UINT32                             _rsvd_00[3];             // 0xCC6A_2014 ~ 0xCC6A_201C
    TRG_CTRL_CORE_AIOPLLSS_00_O24A0_T    core_aiopllss_00;      // 0xCC6A_2020
    TRG_CTRL_CORE_AIOPLLSS_01_O24A0_T    core_aiopllss_01;      // 0xCC6A_2024
    TRG_CTRL_CORE_AIOPLLSS_02_O24A0_T    core_aiopllss_02;      // 0xCC6A_2028
    UINT32                             _rsvd_01[1];             // 0xCC6A_202C
    TRG_CTRL_EMMC_AIOPLLSS_00_O24A0_T    emmc_aiopllss_00;      // 0xCC6A_2030
    TRG_CTRL_EMMC_AIOPLLSS_01_O24A0_T    emmc_aiopllss_01;      // 0xCC6A_2034
    TRG_CTRL_EMMC_AIOPLLSS_02_O24A0_T    emmc_aiopllss_02;      // 0xCC6A_2038
    UINT32                             _rsvd_02[1];             // 0xCC6A_203C
    TRG_CTRL_BUS_AIOPLLSS_00_O24A0_T    bus_aiopllss_00;        // 0xCC6A_2040
    TRG_CTRL_BUS_AIOPLLSS_01_O24A0_T    bus_aiopllss_01;        // 0xCC6A_2044
    TRG_CTRL_BUS_AIOPLLSS_02_O24A0_T    bus_aiopllss_02;        // 0xCC6A_2048
    UINT32                             _rsvd_03[1];             // 0xCC6A_204C
    TRG_CTRL_CODEC_AIOPLLSS_00_O24A0_T    codec_aiopllss_00;    // 0xCC6A_2050
    TRG_CTRL_CODEC_AIOPLLSS_01_O24A0_T    codec_aiopllss_01;    // 0xCC6A_2054
    TRG_CTRL_CODEC_AIOPLLSS_02_O24A0_T    codec_aiopllss_02;    // 0xCC6A_2058
    UINT32                             _rsvd_04[1];             // 0xCC6A_205C
    TRG_CTRL_CPU_AIOPLLSS_00_O24A0_T    cpu_aiopllss_00;        // 0xCC6A_2060
    TRG_CTRL_CPU_AIOPLLSS_01_O24A0_T    cpu_aiopllss_01;        // 0xCC6A_2064
    TRG_CTRL_CPU_AIOPLLSS_02_O24A0_T    cpu_aiopllss_02;        // 0xCC6A_2068
    UINT32                             _rsvd_05[1];             // 0xCC6A_206C
    TRG_CTRL_GPU_AIOPLLSS_00_O24A0_T    gpu_aiopllss_00;        // 0xCC6A_2070
    TRG_CTRL_GPU_AIOPLLSS_01_O24A0_T    gpu_aiopllss_01;        // 0xCC6A_2074
    TRG_CTRL_GPU_AIOPLLSS_02_O24A0_T    gpu_aiopllss_02;        // 0xCC6A_2078
    UINT32                             _rsvd_06[5];             // 0xCC6A_207C ~ 0xCC6A_208C
    TRG_CTRL_CRG_TOP_00_O24A0_T        crg_top_00 ;             // 0xCC6A_2090
    TRG_CTRL_CRG_TOP_01_O24A0_T        crg_top_01 ;             // 0xCC6A_2094
    TRG_CTRL_CRG_TOP_02_O24A0_T        crg_top_02 ;             // 0xCC6A_2098
    TRG_CTRL_CRG_TOP_03_O24A0_T        crg_top_03 ;             // 0xCC6A_209C
    UINT32                             _rsvd_07[1];             // 0xCC6A_20A0
    TRG_CTRL_CRG_TOP_05_O24A0_T        crg_top_05 ;             // 0xCC6A_20A4
    UINT32                             _rsvd_08[2];             // 0xCC6A_20A8 ~ 0xCC6A_20AC
    TRG_CTRL_EARCPLL_FRPLL_00_O24A0_T    earcpll_frpll_00;      // 0xCC6A_20B0
    TRG_CTRL_EARCPLL_FRPLL_01_O24A0_T    earcpll_frpll_01;      // 0xCC6A_20B4
    TRG_CTRL_EARCPLL_FRPLL_02_O24A0_T    earcpll_frpll_02;      // 0xCC6A_20B8
    TRG_CTRL_EARCPLL_FRPLL_SSCG_R00_O24A0_T    earcpll_frpll_sscg_r00;    // 0xCC6A_20BC
    TRG_CTRL_EARCPLL_FCW_MUX_00_O24A0_T    earcpll_fcw_mux_00;    // 0xCC6A_20C0
    UINT32                             _rsvd_09[3];             // 0xCC6A_20C4 ~ 0xCC6A_20CC
    TRG_CTRL_CRG_TOP_WOV_AON_R01_O24A0_T    crg_top_wov_aon_r01;    // 0xCC6A_20D0
    TRG_CTRL_RXCLKDRV_MD_TRG_O24A0_T    rxclkdrv_md_trg;        // 0xCC6A_20D4
}TRG_CTRL_REG_O24A0_T;
/* 35 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _TRG_CTRL_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

