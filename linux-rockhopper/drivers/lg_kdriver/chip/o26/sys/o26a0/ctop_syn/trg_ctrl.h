#ifndef _TRG_CTRL_REG_O26A0_H_
#define _TRG_CTRL_REG_O26A0_H_

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
    0xCC4C_4000    apll_frpll_00 ''
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
}TRG_CTRL_APLL_FRPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4004    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apll_frpll_fout_en    :  1,    //      0
    reg_apll_frpll_syncon     :  1,    //      1
    reg_apll_frpll_m          :  6,    //   7: 2
    reg_apll_frpll_fcw        : 24;    //  31: 8
}TRG_CTRL_APLL_FRPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4008    apll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_apll_frpll_out_div3   :  9,    //  13: 5
    reg_apll_frpll_out_div2   :  9,    //  22:14
    reg_apll_frpll_frequp     :  1,    //     23
    reg_apll_frpll_a          :  6,    //  29:24
    reg_apll_frpll_in_divrstb :  1,    //     30
    reg_apll_frpll_icp_g      :  1;    //     31
}TRG_CTRL_APLL_FRPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_400C    apll_frpll_sscg_r00 ''
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
}TRG_CTRL_APLL_FRPLL_SSCG_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4020    core_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_core_aiopllss_dss     :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_core_aiopllss_cih     :  4,    //  11: 8
    reg_core_aiopllss_nsc     :  4,    //  15:12
    reg_core_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_core_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CORE_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4024    core_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_core_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_core_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CORE_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4028    core_aiopllss_02 ''
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
}TRG_CTRL_CORE_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4030    emmc_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_emmc_aiopllss_dss     :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_emmc_aiopllss_cih     :  4,    //  11: 8
    reg_emmc_aiopllss_nsc     :  4,    //  15:12
    reg_emmc_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_emmc_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_EMMC_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4034    emmc_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_emmc_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_emmc_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_EMMC_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4038    emmc_aiopllss_02 ''
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
}TRG_CTRL_EMMC_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4040    bus_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_bus_aiopllss_dss      :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_bus_aiopllss_cih      :  4,    //  11: 8
    reg_bus_aiopllss_nsc      :  4,    //  15:12
    reg_bus_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_bus_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_BUS_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4044    bus_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_bus_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_bus_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_BUS_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4048    bus_aiopllss_02 ''
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
}TRG_CTRL_BUS_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4050    codec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_accuracy: 2,    //   1: 0
                              :  1,    //      2 reserved
    reg_codec_aiopllss_dss    :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_codec_aiopllss_cih    :  4,    //  11: 8
    reg_codec_aiopllss_nsc    :  4,    //  15:12
    reg_codec_aiopllss_npc    :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_codec_aiopllss_m      :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CODEC_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4054    codec_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_codec_aiopllss_out_div:  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_codec_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_codec_aiopllss_updn_max: 7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CODEC_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4058    codec_aiopllss_02 ''
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
}TRG_CTRL_CODEC_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4060    cpu0_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu0_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_cpu0_aiopllss_dss     :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_cpu0_aiopllss_cih     :  4,    //  11: 8
    reg_cpu0_aiopllss_nsc     :  4,    //  15:12
    reg_cpu0_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_cpu0_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CPU0_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4064    cpu0_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu0_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_cpu0_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_cpu0_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CPU0_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4068    cpu0_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu0_aiopllss_fout1_en:  1,    //      0
    reg_cpu0_aiopllss_freq_update: 1,    //    1
    reg_cpu0_aiopllss_sync_on :  1,    //      2
    reg_cpu0_aiopllss_wake_bypass: 1,    //    3
    reg_cpu0_aiopllss_offset_mode: 1,    //    4
    reg_cpu0_aiopllss_fine_div:  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_cpu0_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_cpu0_aiopllss_offset  :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_CPU0_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4070    cpu1_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu1_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_cpu1_aiopllss_dss     :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_cpu1_aiopllss_cih     :  4,    //  11: 8
    reg_cpu1_aiopllss_nsc     :  4,    //  15:12
    reg_cpu1_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_cpu1_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_CPU1_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4074    cpu1_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu1_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_cpu1_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_cpu1_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_CPU1_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4078    cpu1_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu1_aiopllss_fout1_en:  1,    //      0
    reg_cpu1_aiopllss_freq_update: 1,    //    1
    reg_cpu1_aiopllss_sync_on :  1,    //      2
    reg_cpu1_aiopllss_wake_bypass: 1,    //    3
    reg_cpu1_aiopllss_offset_mode: 1,    //    4
    reg_cpu1_aiopllss_fine_div:  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_cpu1_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_cpu1_aiopllss_offset  :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_CPU1_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4080    gpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_gpu_aiopllss_dss      :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_gpu_aiopllss_cih      :  4,    //  11: 8
    reg_gpu_aiopllss_nsc      :  4,    //  15:12
    reg_gpu_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_gpu_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_GPU_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4084    gpu_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpu_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_gpu_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_gpu_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_GPU_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4088    gpu_aiopllss_02 ''
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
}TRG_CTRL_GPU_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4090    ion_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_ion_aiopllss_dss      :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_ion_aiopllss_cih      :  4,    //  11: 8
    reg_ion_aiopllss_nsc      :  4,    //  15:12
    reg_ion_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_ion_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_ION_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4094    ion_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_ion_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_ion_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_ION_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4098    ion_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion_aiopllss_fout1_en :  1,    //      0
    reg_ion_aiopllss_freq_update: 1,    //     1
    reg_ion_aiopllss_sync_on  :  1,    //      2
    reg_ion_aiopllss_wake_bypass: 1,    //     3
    reg_ion_aiopllss_offset_mode: 1,    //     4
    reg_ion_aiopllss_fine_div :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_ion_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_ion_aiopllss_offset   :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_ION_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A0    ext_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ext_aiopllss_accuracy :  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_ext_aiopllss_dss      :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_ext_aiopllss_cih      :  4,    //  11: 8
    reg_ext_aiopllss_nsc      :  4,    //  15:12
    reg_ext_aiopllss_npc      :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_ext_aiopllss_m        :  6,    //  29:24
                              :  2;    //  31:30 reserved
}TRG_CTRL_EXT_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A4    ext_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ext_aiopllss_out_div  :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_ext_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_ext_aiopllss_updn_max :  7,    //  30:24
                              :  1;    //  31:31 reserved
}TRG_CTRL_EXT_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A8    ext_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ext_aiopllss_fout1_en :  1,    //      0
    reg_ext_aiopllss_freq_update: 1,    //     1
    reg_ext_aiopllss_sync_on  :  1,    //      2
    reg_ext_aiopllss_wake_bypass: 1,    //     3
    reg_ext_aiopllss_offset_mode: 1,    //     4
    reg_ext_aiopllss_fine_div :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_ext_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_ext_aiopllss_offset   :  8,    //  19:12
                              : 12;    //  31:20 reserved
}TRG_CTRL_EXT_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B0    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_pdb_ctrl     :  1,    //      0
    reg_apll_pll_pdb_ctrl     :  1,    //      1
    reg_gpu_pll_pdb_ctrl      :  1,    //      2
    reg_cpu0_pll_pdb_ctrl     :  1,    //      3
    reg_codec_pll_pdb_ctrl    :  1,    //      4
    reg_emmc_pll_pdb_ctrl     :  1,    //      5
    reg_bus_pll_pdb_ctrl      :  1,    //      6
    reg_disp_pll_pdb_ctrl     :  1,    //      7
    reg_oif_pll_pdb_ctrl      :  1,    //      8
    reg_pqe_pll_pdb_ctrl      :  1,    //      9
    reg_cpu1_pll_pdb_ctrl     :  1,    //     10
    reg_ion_pll_pdb_ctrl      :  1,    //     11
    reg_ext_pll_pdb_ctrl      :  1,    //     12
    reg_m0_pll_pdb_ctrl       :  1,    //     13
    reg_m1_pll_pdb_ctrl       :  1,    //     14
                              : 17;    //  31:15 reserved
}TRG_CTRL_CRG_TOP_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B4    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_lock         :  1,    //      0
    reg_apll_pll_lock         :  1,    //      1
    reg_gpu_pll_lock          :  1,    //      2
    reg_cpu0_pll_lock         :  1,    //      3
    reg_codec_pll_lock        :  1,    //      4
    reg_emmc_pll_lock         :  1,    //      5
    reg_bus_pll_lock          :  1,    //      6
    reg_disp_pll_lock         :  1,    //      7
    reg_oif_pll_lock          :  1,    //      8
    reg_pqe_pll_lock          :  1,    //      9
    reg_cpu1_pll_lock         :  1,    //     10
    reg_ion_pll_lock          :  1,    //     11
    reg_ext_pll_lock          :  1,    //     12
    reg_m0_pll_lock           :  1,    //     13
    reg_m1_pll_lock           :  1,    //     14
                              : 17;    //  31:15 reserved
}TRG_CTRL_CRG_TOP_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B8    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_lock_bypass  :  1,    //      0
    reg_apll_lock_bypass      :  1,    //      1
    reg_gpu_pll_lock_bypass   :  1,    //      2
    reg_cpu0_pll_lock_bypass  :  1,    //      3
    reg_codec_pll_lock_bypass :  1,    //      4
    reg_emmc_pll_lock_bypass  :  1,    //      5
    reg_bus_pll_lock_bypass   :  1,    //      6
    reg_disp_pll_lock_bypass  :  1,    //      7
    reg_oif_pll_lock_bypass   :  1,    //      8
    reg_pqe_frpll_lock_bypass :  1,    //      9
    reg_cpu1_pll_lock_bypass  :  1,    //     10
    reg_ion_pll_lock_bypass   :  1,    //     11
    reg_ext_pll_lock_bypass   :  1,    //     12
    reg_earc_frpll_lock_bypass:  1,    //     13
                              : 18;    //  31:14 reserved
}TRG_CTRL_CRG_TOP_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40BC    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_core_600      :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_pll_sel_core_600      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_clk_sel_emmc_400      :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_pll_sel_emmc_400      :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_clk_sel_core_884      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_pll_sel_core_884      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_clk_sel_core_400      :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_pll_sel_core_400      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}TRG_CTRL_CRG_TOP_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C0    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_ext_900       :  1,    //      0
                              :  7,    //   7: 1 reserved
    reg_clk_sel_core_660      :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_pll_sel_core_660      :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_clk_sel_core_800      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_pll_sel_core_800      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_clk_sel_core_480      :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_pll_sel_core_480      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}TRG_CTRL_CRG_TOP_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C4    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_ion_480       :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C8    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_sel_cpu_pll0      :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40CC    crg_top_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40D0    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_watchdog_reset_sel    :  1,    //      0
                              : 31;    //   31:1 reserved
}TRG_CTRL_CRG_TOP_WOV_AON_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40E8    pl_clkdrv_md_trg0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_md_trg0_pdb  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_md_trg0_div2_enb: 1,    //    4
                              : 27;    //   31:5 reserved
}TRG_CTRL_PL_CLKDRV_MD_TRG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40EC    pl_clkdrv_md_trg1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_md_trg1_pdb  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_md_trg1_div2_enb: 1,    //    4
                              : 27;    //   31:5 reserved
}TRG_CTRL_PL_CLKDRV_MD_TRG1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40F0    aiopllss_icp_g ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_aiopllss_icp_g    :  1,    //      0
    reg_emmc_aiopllss_icp_g   :  1,    //      1
    reg_gpu_aiopllss_icp_g    :  1,    //      2
    reg_core_aiopllss_icp_g   :  1,    //      3
    reg_codec_aiopllss_icp_g  :  1,    //      4
    reg_ion_aiopllss_icp_g    :  1,    //      5
    reg_cpu1_aiopllss_icp_g   :  1,    //      6
    reg_cpu0_aiopllss_icp_g   :  1,    //      7
    reg_disp_aiopllss_icp_g   :  1,    //      8
    reg_ext_aiopllss_icp_g    :  1,    //      9
                              : 22;    //  31:10 reserved
}TRG_CTRL_AIOPLLSS_ICP_G_O26A0_T;

/*-----------------------------------------------------------------------------------------
    trg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TRG_CTRL_APLL_FRPLL_00_O26A0_T     apll_frpll_00;           // 0xCC4C_4000
    TRG_CTRL_APLL_FRPLL_01_O26A0_T     apll_frpll_01;           // 0xCC4C_4004
    TRG_CTRL_APLL_FRPLL_02_O26A0_T     apll_frpll_02;           // 0xCC4C_4008
    TRG_CTRL_APLL_FRPLL_SSCG_R00_O26A0_T    apll_frpll_sscg_r00;    // 0xCC4C_400C
    UINT32                             _rsvd_00[4];             // 0xCC4C_4010 ~ 0xCC4C_401C
    TRG_CTRL_CORE_AIOPLLSS_00_O26A0_T    core_aiopllss_00;      // 0xCC4C_4020
    TRG_CTRL_CORE_AIOPLLSS_01_O26A0_T    core_aiopllss_01;      // 0xCC4C_4024
    TRG_CTRL_CORE_AIOPLLSS_02_O26A0_T    core_aiopllss_02;      // 0xCC4C_4028
    UINT32                             _rsvd_01[1];             // 0xCC4C_402C
    TRG_CTRL_EMMC_AIOPLLSS_00_O26A0_T    emmc_aiopllss_00;      // 0xCC4C_4030
    TRG_CTRL_EMMC_AIOPLLSS_01_O26A0_T    emmc_aiopllss_01;      // 0xCC4C_4034
    TRG_CTRL_EMMC_AIOPLLSS_02_O26A0_T    emmc_aiopllss_02;      // 0xCC4C_4038
    UINT32                             _rsvd_02[1];             // 0xCC4C_403C
    TRG_CTRL_BUS_AIOPLLSS_00_O26A0_T    bus_aiopllss_00;        // 0xCC4C_4040
    TRG_CTRL_BUS_AIOPLLSS_01_O26A0_T    bus_aiopllss_01;        // 0xCC4C_4044
    TRG_CTRL_BUS_AIOPLLSS_02_O26A0_T    bus_aiopllss_02;        // 0xCC4C_4048
    UINT32                             _rsvd_03[1];             // 0xCC4C_404C
    TRG_CTRL_CODEC_AIOPLLSS_00_O26A0_T    codec_aiopllss_00;    // 0xCC4C_4050
    TRG_CTRL_CODEC_AIOPLLSS_01_O26A0_T    codec_aiopllss_01;    // 0xCC4C_4054
    TRG_CTRL_CODEC_AIOPLLSS_02_O26A0_T    codec_aiopllss_02;    // 0xCC4C_4058
    UINT32                             _rsvd_04[1];             // 0xCC4C_405C
    TRG_CTRL_CPU0_AIOPLLSS_00_O26A0_T    cpu0_aiopllss_00;      // 0xCC4C_4060
    TRG_CTRL_CPU0_AIOPLLSS_01_O26A0_T    cpu0_aiopllss_01;      // 0xCC4C_4064
    TRG_CTRL_CPU0_AIOPLLSS_02_O26A0_T    cpu0_aiopllss_02;      // 0xCC4C_4068
    UINT32                             _rsvd_05[1];             // 0xCC4C_406C
    TRG_CTRL_CPU1_AIOPLLSS_00_O26A0_T    cpu1_aiopllss_00;      // 0xCC4C_4070
    TRG_CTRL_CPU1_AIOPLLSS_01_O26A0_T    cpu1_aiopllss_01;      // 0xCC4C_4074
    TRG_CTRL_CPU1_AIOPLLSS_02_O26A0_T    cpu1_aiopllss_02;      // 0xCC4C_4078
    UINT32                             _rsvd_06[1];             // 0xCC4C_407C
    TRG_CTRL_GPU_AIOPLLSS_00_O26A0_T    gpu_aiopllss_00;        // 0xCC4C_4080
    TRG_CTRL_GPU_AIOPLLSS_01_O26A0_T    gpu_aiopllss_01;        // 0xCC4C_4084
    TRG_CTRL_GPU_AIOPLLSS_02_O26A0_T    gpu_aiopllss_02;        // 0xCC4C_4088
    UINT32                             _rsvd_07[1];             // 0xCC4C_408C
    TRG_CTRL_ION_AIOPLLSS_00_O26A0_T    ion_aiopllss_00;        // 0xCC4C_4090
    TRG_CTRL_ION_AIOPLLSS_01_O26A0_T    ion_aiopllss_01;        // 0xCC4C_4094
    TRG_CTRL_ION_AIOPLLSS_02_O26A0_T    ion_aiopllss_02;        // 0xCC4C_4098
    UINT32                             _rsvd_08[1];             // 0xCC4C_409C
    TRG_CTRL_EXT_AIOPLLSS_00_O26A0_T    ext_aiopllss_00;        // 0xCC4C_40A0
    TRG_CTRL_EXT_AIOPLLSS_01_O26A0_T    ext_aiopllss_01;        // 0xCC4C_40A4
    TRG_CTRL_EXT_AIOPLLSS_02_O26A0_T    ext_aiopllss_02;        // 0xCC4C_40A8
    UINT32                             _rsvd_09[1];             // 0xCC4C_40AC
    TRG_CTRL_CRG_TOP_00_O26A0_T        crg_top_00 ;             // 0xCC4C_40B0
    TRG_CTRL_CRG_TOP_01_O26A0_T        crg_top_01 ;             // 0xCC4C_40B4
    TRG_CTRL_CRG_TOP_02_O26A0_T        crg_top_02 ;             // 0xCC4C_40B8
    TRG_CTRL_CRG_TOP_03_O26A0_T        crg_top_03 ;             // 0xCC4C_40BC
    TRG_CTRL_CRG_TOP_04_O26A0_T        crg_top_04 ;             // 0xCC4C_40C0
    TRG_CTRL_CRG_TOP_05_O26A0_T        crg_top_05 ;             // 0xCC4C_40C4
    TRG_CTRL_CRG_TOP_06_O26A0_T        crg_top_06 ;             // 0xCC4C_40C8
    TRG_CTRL_CRG_TOP_07_O26A0_T        crg_top_07 ;             // 0xCC4C_40CC
    TRG_CTRL_CRG_TOP_WOV_AON_R01_O26A0_T    crg_top_wov_aon_r01;    // 0xCC4C_40D0
    UINT32                             _rsvd_10[5];             // 0xCC4C_40D4 ~ 0xCC4C_40E4
    TRG_CTRL_PL_CLKDRV_MD_TRG0_O26A0_T    pl_clkdrv_md_trg0;    // 0xCC4C_40E8
    TRG_CTRL_PL_CLKDRV_MD_TRG1_O26A0_T    pl_clkdrv_md_trg1;    // 0xCC4C_40EC
    TRG_CTRL_AIOPLLSS_ICP_G_O26A0_T    aiopllss_icp_g;          // 0xCC4C_40F0
}TRG_CTRL_REG_O26A0_T;
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

#define TRG_CTRL_APLL_FRPLL_00_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define TRG_CTRL_APLL_FRPLL_01_O26A0_T_OFF                  (BASEADDRESS+0x0004)
#define TRG_CTRL_APLL_FRPLL_02_O26A0_T_OFF                  (BASEADDRESS+0x0008)
#define TRG_CTRL_APLL_FRPLL_SSCG_R00_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define TRG_CTRL_CORE_AIOPLLSS_00_O26A0_T_OFF               (BASEADDRESS+0x0020)
#define TRG_CTRL_CORE_AIOPLLSS_01_O26A0_T_OFF               (BASEADDRESS+0x0024)
#define TRG_CTRL_CORE_AIOPLLSS_02_O26A0_T_OFF               (BASEADDRESS+0x0028)
#define TRG_CTRL_EMMC_AIOPLLSS_00_O26A0_T_OFF               (BASEADDRESS+0x0030)
#define TRG_CTRL_EMMC_AIOPLLSS_01_O26A0_T_OFF               (BASEADDRESS+0x0034)
#define TRG_CTRL_EMMC_AIOPLLSS_02_O26A0_T_OFF               (BASEADDRESS+0x0038)
#define TRG_CTRL_BUS_AIOPLLSS_00_O26A0_T_OFF                (BASEADDRESS+0x0040)
#define TRG_CTRL_BUS_AIOPLLSS_01_O26A0_T_OFF                (BASEADDRESS+0x0044)
#define TRG_CTRL_BUS_AIOPLLSS_02_O26A0_T_OFF                (BASEADDRESS+0x0048)
#define TRG_CTRL_CODEC_AIOPLLSS_00_O26A0_T_OFF              (BASEADDRESS+0x0050)
#define TRG_CTRL_CODEC_AIOPLLSS_01_O26A0_T_OFF              (BASEADDRESS+0x0054)
#define TRG_CTRL_CODEC_AIOPLLSS_02_O26A0_T_OFF              (BASEADDRESS+0x0058)
#define TRG_CTRL_CPU0_AIOPLLSS_00_O26A0_T_OFF               (BASEADDRESS+0x0060)
#define TRG_CTRL_CPU0_AIOPLLSS_01_O26A0_T_OFF               (BASEADDRESS+0x0064)
#define TRG_CTRL_CPU0_AIOPLLSS_02_O26A0_T_OFF               (BASEADDRESS+0x0068)
#define TRG_CTRL_CPU1_AIOPLLSS_00_O26A0_T_OFF               (BASEADDRESS+0x0070)
#define TRG_CTRL_CPU1_AIOPLLSS_01_O26A0_T_OFF               (BASEADDRESS+0x0074)
#define TRG_CTRL_CPU1_AIOPLLSS_02_O26A0_T_OFF               (BASEADDRESS+0x0078)
#define TRG_CTRL_GPU_AIOPLLSS_00_O26A0_T_OFF                (BASEADDRESS+0x0080)
#define TRG_CTRL_GPU_AIOPLLSS_01_O26A0_T_OFF                (BASEADDRESS+0x0084)
#define TRG_CTRL_GPU_AIOPLLSS_02_O26A0_T_OFF                (BASEADDRESS+0x0088)
#define TRG_CTRL_ION_AIOPLLSS_00_O26A0_T_OFF                (BASEADDRESS+0x0090)
#define TRG_CTRL_ION_AIOPLLSS_01_O26A0_T_OFF                (BASEADDRESS+0x0094)
#define TRG_CTRL_ION_AIOPLLSS_02_O26A0_T_OFF                (BASEADDRESS+0x0098)
#define TRG_CTRL_EXT_AIOPLLSS_00_O26A0_T_OFF                (BASEADDRESS+0x00A0)
#define TRG_CTRL_EXT_AIOPLLSS_01_O26A0_T_OFF                (BASEADDRESS+0x00A4)
#define TRG_CTRL_EXT_AIOPLLSS_02_O26A0_T_OFF                (BASEADDRESS+0x00A8)
#define TRG_CTRL_CRG_TOP_00_O26A0_T_OFF                     (BASEADDRESS+0x00B0)
#define TRG_CTRL_CRG_TOP_01_O26A0_T_OFF                     (BASEADDRESS+0x00B4)
#define TRG_CTRL_CRG_TOP_02_O26A0_T_OFF                     (BASEADDRESS+0x00B8)
#define TRG_CTRL_CRG_TOP_03_O26A0_T_OFF                     (BASEADDRESS+0x00BC)
#define TRG_CTRL_CRG_TOP_04_O26A0_T_OFF                     (BASEADDRESS+0x00C0)
#define TRG_CTRL_CRG_TOP_05_O26A0_T_OFF                     (BASEADDRESS+0x00C4)
#define TRG_CTRL_CRG_TOP_06_O26A0_T_OFF                     (BASEADDRESS+0x00C8)
#define TRG_CTRL_CRG_TOP_07_O26A0_T_OFF                     (BASEADDRESS+0x00CC)
#define TRG_CTRL_CRG_TOP_WOV_AON_R01_O26A0_T_OFF            (BASEADDRESS+0x00D0)
#define TRG_CTRL_PL_CLKDRV_MD_TRG0_O26A0_T_OFF              (BASEADDRESS+0x00E8)
#define TRG_CTRL_PL_CLKDRV_MD_TRG1_O26A0_T_OFF              (BASEADDRESS+0x00EC)
#define TRG_CTRL_AIOPLLSS_ICP_G_O26A0_T_OFF                 (BASEADDRESS+0x00F0)

/*-----------------------------------------------------------------------------------------
    0xCC4C_4000    apll_frpll_00 ''
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
}TRG_CTRL_APLL_FRPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4004    apll_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apll_frpll_fout_en: 1;    //    0
    UINT32 reg_apll_frpll_syncon: 1;    //     1
    UINT32 reg_apll_frpll_m   :  6;    //   7: 2
    UINT32 reg_apll_frpll_fcw : 24;    //  31: 8
    };
}TRG_CTRL_APLL_FRPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4008    apll_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_apll_frpll_out_div3: 9;    //  13:5
    UINT32 reg_apll_frpll_out_div2: 9;    //  22:14
    UINT32 reg_apll_frpll_frequp: 1;    //    23
    UINT32 reg_apll_frpll_a   :  6;    //  29:24
    UINT32 reg_apll_frpll_in_divrstb: 1;    //  30
    UINT32 reg_apll_frpll_icp_g: 1;    //     31
    };
}TRG_CTRL_APLL_FRPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_400C    apll_frpll_sscg_r00 ''
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
}TRG_CTRL_APLL_FRPLL_SSCG_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4020    core_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_core_aiopllss_dss: 1;    //     3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_core_aiopllss_cih: 4;    //  11:8
    UINT32 reg_core_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_core_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_core_aiopllss_m:  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CORE_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4024    core_aiopllss_01 ''
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
}TRG_CTRL_CORE_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4028    core_aiopllss_02 ''
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
}TRG_CTRL_CORE_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4030    emmc_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_emmc_aiopllss_dss: 1;    //     3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_emmc_aiopllss_cih: 4;    //  11:8
    UINT32 reg_emmc_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_emmc_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_emmc_aiopllss_m:  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_EMMC_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4034    emmc_aiopllss_01 ''
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
}TRG_CTRL_EMMC_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4038    emmc_aiopllss_02 ''
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
}TRG_CTRL_EMMC_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4040    bus_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_bus_aiopllss_dss: 1;    //      3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_bus_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_bus_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_bus_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_bus_aiopllss_m :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_BUS_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4044    bus_aiopllss_01 ''
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
}TRG_CTRL_BUS_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4048    bus_aiopllss_02 ''
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
}TRG_CTRL_BUS_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4050    codec_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_codec_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_codec_aiopllss_dss: 1;    //    3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_codec_aiopllss_cih: 4;    //  11:8
    UINT32 reg_codec_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_codec_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_codec_aiopllss_m: 6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CODEC_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4054    codec_aiopllss_01 ''
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
}TRG_CTRL_CODEC_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4058    codec_aiopllss_02 ''
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
}TRG_CTRL_CODEC_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4060    cpu0_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu0_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_cpu0_aiopllss_dss: 1;    //     3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_cpu0_aiopllss_cih: 4;    //  11:8
    UINT32 reg_cpu0_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_cpu0_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_cpu0_aiopllss_m:  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CPU0_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4064    cpu0_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu0_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_cpu0_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_cpu0_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CPU0_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4068    cpu0_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu0_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_cpu0_aiopllss_freq_update: 1;    //  1
    UINT32 reg_cpu0_aiopllss_sync_on: 1;    //  2
    UINT32 reg_cpu0_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_cpu0_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_cpu0_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_cpu0_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_cpu0_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_CPU0_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4070    cpu1_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu1_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_cpu1_aiopllss_dss: 1;    //     3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_cpu1_aiopllss_cih: 4;    //  11:8
    UINT32 reg_cpu1_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_cpu1_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_cpu1_aiopllss_m:  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_CPU1_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4074    cpu1_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu1_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_cpu1_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_cpu1_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CPU1_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4078    cpu1_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu1_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_cpu1_aiopllss_freq_update: 1;    //  1
    UINT32 reg_cpu1_aiopllss_sync_on: 1;    //  2
    UINT32 reg_cpu1_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_cpu1_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_cpu1_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_cpu1_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_cpu1_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_CPU1_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4080    gpu_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gpu_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_gpu_aiopllss_dss: 1;    //      3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_gpu_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_gpu_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_gpu_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_gpu_aiopllss_m :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_GPU_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4084    gpu_aiopllss_01 ''
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
}TRG_CTRL_GPU_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4088    gpu_aiopllss_02 ''
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
}TRG_CTRL_GPU_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4090    ion_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_ion_aiopllss_dss: 1;    //      3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_ion_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_ion_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_ion_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_ion_aiopllss_m :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_ION_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4094    ion_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_ion_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_ion_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_ION_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_4098    ion_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_ion_aiopllss_freq_update: 1;    //  1
    UINT32 reg_ion_aiopllss_sync_on: 1;    //  2
    UINT32 reg_ion_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_ion_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_ion_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_ion_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_ion_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_ION_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A0    ext_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ext_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_ext_aiopllss_dss: 1;    //      3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_ext_aiopllss_cih: 4;    //  11: 8
    UINT32 reg_ext_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_ext_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_ext_aiopllss_m :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}TRG_CTRL_EXT_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A4    ext_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ext_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_ext_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_ext_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}TRG_CTRL_EXT_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40A8    ext_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ext_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_ext_aiopllss_freq_update: 1;    //  1
    UINT32 reg_ext_aiopllss_sync_on: 1;    //  2
    UINT32 reg_ext_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_ext_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_ext_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_ext_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_ext_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}TRG_CTRL_EXT_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B0    crg_top_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_pdb_ctrl: 1;    //     0
    UINT32 reg_apll_pll_pdb_ctrl: 1;    //     1
    UINT32 reg_gpu_pll_pdb_ctrl: 1;    //      2
    UINT32 reg_cpu0_pll_pdb_ctrl: 1;    //     3
    UINT32 reg_codec_pll_pdb_ctrl: 1;    //    4
    UINT32 reg_emmc_pll_pdb_ctrl: 1;    //     5
    UINT32 reg_bus_pll_pdb_ctrl: 1;    //      6
    UINT32 reg_disp_pll_pdb_ctrl: 1;    //     7
    UINT32 reg_oif_pll_pdb_ctrl: 1;    //      8
    UINT32 reg_pqe_pll_pdb_ctrl: 1;    //      9
    UINT32 reg_cpu1_pll_pdb_ctrl: 1;    //    10
    UINT32 reg_ion_pll_pdb_ctrl: 1;    //     11
    UINT32 reg_ext_pll_pdb_ctrl: 1;    //     12
    UINT32 reg_m0_pll_pdb_ctrl:  1;    //     13
    UINT32 reg_m1_pll_pdb_ctrl:  1;    //     14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}TRG_CTRL_CRG_TOP_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B4    crg_top_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_lock  :  1;    //      0
    UINT32 reg_apll_pll_lock  :  1;    //      1
    UINT32 reg_gpu_pll_lock   :  1;    //      2
    UINT32 reg_cpu0_pll_lock  :  1;    //      3
    UINT32 reg_codec_pll_lock :  1;    //      4
    UINT32 reg_emmc_pll_lock  :  1;    //      5
    UINT32 reg_bus_pll_lock   :  1;    //      6
    UINT32 reg_disp_pll_lock  :  1;    //      7
    UINT32 reg_oif_pll_lock   :  1;    //      8
    UINT32 reg_pqe_pll_lock   :  1;    //      9
    UINT32 reg_cpu1_pll_lock  :  1;    //     10
    UINT32 reg_ion_pll_lock   :  1;    //     11
    UINT32 reg_ext_pll_lock   :  1;    //     12
    UINT32 reg_m0_pll_lock    :  1;    //     13
    UINT32 reg_m1_pll_lock    :  1;    //     14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}TRG_CTRL_CRG_TOP_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40B8    crg_top_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core_pll_lock_bypass: 1;    //  0
    UINT32 reg_apll_lock_bypass: 1;    //      1
    UINT32 reg_gpu_pll_lock_bypass: 1;    //   2
    UINT32 reg_cpu0_pll_lock_bypass: 1;    //  3
    UINT32 reg_codec_pll_lock_bypass: 1;    //  4
    UINT32 reg_emmc_pll_lock_bypass: 1;    //  5
    UINT32 reg_bus_pll_lock_bypass: 1;    //   6
    UINT32 reg_disp_pll_lock_bypass: 1;    //  7
    UINT32 reg_oif_pll_lock_bypass: 1;    //   8
    UINT32 reg_pqe_frpll_lock_bypass: 1;    //  9
    UINT32 reg_cpu1_pll_lock_bypass: 1;    //  10
    UINT32 reg_ion_pll_lock_bypass: 1;    //  11
    UINT32 reg_ext_pll_lock_bypass: 1;    //  12
    UINT32 reg_earc_frpll_lock_bypass: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}TRG_CTRL_CRG_TOP_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40BC    crg_top_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_core_600: 2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_pll_sel_core_600: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_clk_sel_emmc_400: 2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_pll_sel_emmc_400: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_clk_sel_core_884: 2;    //  17:16
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 reg_pll_sel_core_884: 3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_clk_sel_core_400: 2;    //  25:24
    UINT32 resvd06            :  2;    //  27:26 reserved
    UINT32 reg_pll_sel_core_400: 3;    //  30:28
    UINT32 resvd07            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CRG_TOP_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C0    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_ext_900:  1;    //      0
    UINT32 resvd00            :  7;    //   7: 1 reserved
    UINT32 reg_clk_sel_core_660: 2;    //   9: 8
    UINT32 resvd01            :  2;    //  11:10 reserved
    UINT32 reg_pll_sel_core_660: 3;    //  14:12
    UINT32 resvd02            :  1;    //     15 reserved
    UINT32 reg_clk_sel_core_800: 2;    //  17:16
    UINT32 resvd03            :  2;    //  19:18 reserved
    UINT32 reg_pll_sel_core_800: 3;    //  22:20
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 reg_clk_sel_core_480: 2;    //  25:24
    UINT32 resvd05            :  2;    //  27:26 reserved
    UINT32 reg_pll_sel_core_480: 3;    //  30:28
    UINT32 resvd06            :  1;    //  31:31 reserved
    };
}TRG_CTRL_CRG_TOP_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C4    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_ion_480:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40C8    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_clk_sel_cpu_pll0: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40CC    crg_top_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40D0    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_watchdog_reset_sel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}TRG_CTRL_CRG_TOP_WOV_AON_R01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40E8    pl_clkdrv_md_trg0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_md_trg0_pdb: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_md_trg0_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}TRG_CTRL_PL_CLKDRV_MD_TRG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40EC    pl_clkdrv_md_trg1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_md_trg1_pdb: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_md_trg1_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}TRG_CTRL_PL_CLKDRV_MD_TRG1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_40F0    aiopllss_icp_g ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_aiopllss_icp_g: 1;    //    0
    UINT32 reg_emmc_aiopllss_icp_g: 1;    //   1
    UINT32 reg_gpu_aiopllss_icp_g: 1;    //    2
    UINT32 reg_core_aiopllss_icp_g: 1;    //   3
    UINT32 reg_codec_aiopllss_icp_g: 1;    //  4
    UINT32 reg_ion_aiopllss_icp_g: 1;    //    5
    UINT32 reg_cpu1_aiopllss_icp_g: 1;    //   6
    UINT32 reg_cpu0_aiopllss_icp_g: 1;    //   7
    UINT32 reg_disp_aiopllss_icp_g: 1;    //   8
    UINT32 reg_ext_aiopllss_icp_g: 1;    //    9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}TRG_CTRL_AIOPLLSS_ICP_G_O26A0_T;

/*-----------------------------------------------------------------------------------------
    trg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TRG_CTRL_APLL_FRPLL_00_O26A0_T     apll_frpll_00;           // 0xCC4C_4000
    TRG_CTRL_APLL_FRPLL_01_O26A0_T     apll_frpll_01;           // 0xCC4C_4004
    TRG_CTRL_APLL_FRPLL_02_O26A0_T     apll_frpll_02;           // 0xCC4C_4008
    TRG_CTRL_APLL_FRPLL_SSCG_R00_O26A0_T    apll_frpll_sscg_r00;    // 0xCC4C_400C
    UINT32                             _rsvd_00[4];             // 0xCC4C_4010 ~ 0xCC4C_401C
    TRG_CTRL_CORE_AIOPLLSS_00_O26A0_T    core_aiopllss_00;      // 0xCC4C_4020
    TRG_CTRL_CORE_AIOPLLSS_01_O26A0_T    core_aiopllss_01;      // 0xCC4C_4024
    TRG_CTRL_CORE_AIOPLLSS_02_O26A0_T    core_aiopllss_02;      // 0xCC4C_4028
    UINT32                             _rsvd_01[1];             // 0xCC4C_402C
    TRG_CTRL_EMMC_AIOPLLSS_00_O26A0_T    emmc_aiopllss_00;      // 0xCC4C_4030
    TRG_CTRL_EMMC_AIOPLLSS_01_O26A0_T    emmc_aiopllss_01;      // 0xCC4C_4034
    TRG_CTRL_EMMC_AIOPLLSS_02_O26A0_T    emmc_aiopllss_02;      // 0xCC4C_4038
    UINT32                             _rsvd_02[1];             // 0xCC4C_403C
    TRG_CTRL_BUS_AIOPLLSS_00_O26A0_T    bus_aiopllss_00;        // 0xCC4C_4040
    TRG_CTRL_BUS_AIOPLLSS_01_O26A0_T    bus_aiopllss_01;        // 0xCC4C_4044
    TRG_CTRL_BUS_AIOPLLSS_02_O26A0_T    bus_aiopllss_02;        // 0xCC4C_4048
    UINT32                             _rsvd_03[1];             // 0xCC4C_404C
    TRG_CTRL_CODEC_AIOPLLSS_00_O26A0_T    codec_aiopllss_00;    // 0xCC4C_4050
    TRG_CTRL_CODEC_AIOPLLSS_01_O26A0_T    codec_aiopllss_01;    // 0xCC4C_4054
    TRG_CTRL_CODEC_AIOPLLSS_02_O26A0_T    codec_aiopllss_02;    // 0xCC4C_4058
    UINT32                             _rsvd_04[1];             // 0xCC4C_405C
    TRG_CTRL_CPU0_AIOPLLSS_00_O26A0_T    cpu0_aiopllss_00;      // 0xCC4C_4060
    TRG_CTRL_CPU0_AIOPLLSS_01_O26A0_T    cpu0_aiopllss_01;      // 0xCC4C_4064
    TRG_CTRL_CPU0_AIOPLLSS_02_O26A0_T    cpu0_aiopllss_02;      // 0xCC4C_4068
    UINT32                             _rsvd_05[1];             // 0xCC4C_406C
    TRG_CTRL_CPU1_AIOPLLSS_00_O26A0_T    cpu1_aiopllss_00;      // 0xCC4C_4070
    TRG_CTRL_CPU1_AIOPLLSS_01_O26A0_T    cpu1_aiopllss_01;      // 0xCC4C_4074
    TRG_CTRL_CPU1_AIOPLLSS_02_O26A0_T    cpu1_aiopllss_02;      // 0xCC4C_4078
    UINT32                             _rsvd_06[1];             // 0xCC4C_407C
    TRG_CTRL_GPU_AIOPLLSS_00_O26A0_T    gpu_aiopllss_00;        // 0xCC4C_4080
    TRG_CTRL_GPU_AIOPLLSS_01_O26A0_T    gpu_aiopllss_01;        // 0xCC4C_4084
    TRG_CTRL_GPU_AIOPLLSS_02_O26A0_T    gpu_aiopllss_02;        // 0xCC4C_4088
    UINT32                             _rsvd_07[1];             // 0xCC4C_408C
    TRG_CTRL_ION_AIOPLLSS_00_O26A0_T    ion_aiopllss_00;        // 0xCC4C_4090
    TRG_CTRL_ION_AIOPLLSS_01_O26A0_T    ion_aiopllss_01;        // 0xCC4C_4094
    TRG_CTRL_ION_AIOPLLSS_02_O26A0_T    ion_aiopllss_02;        // 0xCC4C_4098
    UINT32                             _rsvd_08[1];             // 0xCC4C_409C
    TRG_CTRL_EXT_AIOPLLSS_00_O26A0_T    ext_aiopllss_00;        // 0xCC4C_40A0
    TRG_CTRL_EXT_AIOPLLSS_01_O26A0_T    ext_aiopllss_01;        // 0xCC4C_40A4
    TRG_CTRL_EXT_AIOPLLSS_02_O26A0_T    ext_aiopllss_02;        // 0xCC4C_40A8
    UINT32                             _rsvd_09[1];             // 0xCC4C_40AC
    TRG_CTRL_CRG_TOP_00_O26A0_T        crg_top_00 ;             // 0xCC4C_40B0
    TRG_CTRL_CRG_TOP_01_O26A0_T        crg_top_01 ;             // 0xCC4C_40B4
    TRG_CTRL_CRG_TOP_02_O26A0_T        crg_top_02 ;             // 0xCC4C_40B8
    TRG_CTRL_CRG_TOP_03_O26A0_T        crg_top_03 ;             // 0xCC4C_40BC
    TRG_CTRL_CRG_TOP_04_O26A0_T        crg_top_04 ;             // 0xCC4C_40C0
    TRG_CTRL_CRG_TOP_05_O26A0_T        crg_top_05 ;             // 0xCC4C_40C4
    TRG_CTRL_CRG_TOP_06_O26A0_T        crg_top_06 ;             // 0xCC4C_40C8
    TRG_CTRL_CRG_TOP_07_O26A0_T        crg_top_07 ;             // 0xCC4C_40CC
    TRG_CTRL_CRG_TOP_WOV_AON_R01_O26A0_T    crg_top_wov_aon_r01;    // 0xCC4C_40D0
    UINT32                             _rsvd_10[5];             // 0xCC4C_40D4 ~ 0xCC4C_40E4
    TRG_CTRL_PL_CLKDRV_MD_TRG0_O26A0_T    pl_clkdrv_md_trg0;    // 0xCC4C_40E8
    TRG_CTRL_PL_CLKDRV_MD_TRG1_O26A0_T    pl_clkdrv_md_trg1;    // 0xCC4C_40EC
    TRG_CTRL_AIOPLLSS_ICP_G_O26A0_T    aiopllss_icp_g;          // 0xCC4C_40F0
}TRG_CTRL_REG_O26A0_T;
/* 43 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_TRG_CTRL_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

