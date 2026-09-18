#ifndef _CTOP_CPU_SYN_A0_REG_H_
#define _CTOP_CPU_SYN_A0_REG_H_

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
    0xC923_0404    syn_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_fine_control :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_core_pll_fine_div     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_core_pll_cih          :  4,    //  11: 8
    reg_core_pll_nsc          :  4,    //  15:12
    reg_core_pll_npc          :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_core_pll_m            :  6,    //  29:24
                              :  1,    //     30 reserved
    core_pll_lock_out         :  1;    //     31
}CPU_SYN_SYN_CPU01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0408    syn_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_dss          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_core_pll_fout3_od     :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_core_pll_fout2_od     :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_core_pll_fout_od      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_core_pll_pre_fout3_div:  3,    //  18:16
                              :  1,    //     19 reserved
    reg_core_pll_pre_fout2_div:  3,    //  22:20
                              :  9;    //  31:23 reserved
}CPU_SYN_SYN_CPU02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_040C    syn_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_offset       :  8,    //   7: 0
    reg_core_pll_updn_max     :  7,    //  14: 8
                              :  1,    //     15 reserved
    reg_core_pll_mod_freq     :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CPU_SYN_SYN_CPU03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0410    syn_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core_pll_wakeup_bypass:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_core_pll_ddr_mode     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_core_pll_offset_mode  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_core_pll_accuracy     :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CPU_SYN_SYN_CPU04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0414    syn_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr_pll_fine_control  :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_ddr_pll_fine_div      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ddr_pll_cih           :  4,    //  11: 8
    reg_ddr_pll_nsc           :  4,    //  15:12
    reg_ddr_pll_npc           :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_ddr_pll_m             :  6,    //  29:24
                              :  1,    //     30 reserved
    ddr_pll_lock_out          :  1;    //     31
}CPU_SYN_SYN_CPU05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0418    syn_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr_pll_dss           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ddr_pll_fout3_od      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_ddr_pll_fout2_od      :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_ddr_pll_fout_od       :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_ddr_pll_pre_fout3_div :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_ddr_pll_pre_fout2_div :  3,    //  22:20
                              :  9;    //  31:23 reserved
}CPU_SYN_SYN_CPU06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_041C    syn_cpu07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr_pll_offset        :  8,    //   7: 0
    reg_ddr_pll_updn_max      :  7,    //  14: 8
                              :  1,    //     15 reserved
    reg_ddr_pll_mod_freq      :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CPU_SYN_SYN_CPU07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0420    syn_cpu08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr_pll_wakeup_bypass :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ddr_pll_ddr_mode      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ddr_pll_offset_mode   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_ddr_pll_accuracy      :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CPU_SYN_SYN_CPU08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0424    syn_cpu09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_pllm_fine_control :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_cpu_pllm_fine_div     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cpu_pllm_cih          :  4,    //  11: 8
    reg_cpu_pllm_nsc          :  4,    //  15:12
    reg_cpu_pllm_npc          :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_cpu_pllm_m            :  6,    //  29:24
                              :  2;    //  31:30 reserved
}CPU_SYN_SYN_CPU09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0428    syn_cpu10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_pllm_dss          :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_SYN_CPU10_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_042C    syn_cpu11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_pllm_offset       :  8,    //   7: 0
    reg_cpu_pllm_updn_max     :  7,    //  14: 8
                              :  1,    //     15 reserved
    reg_cpu_pllm_mod_freq     :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CPU_SYN_SYN_CPU11_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0430    syn_cpu12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_pllm_wakeup_bypass:  1,    //      0
                              :  7,    //   7: 1 reserved
    reg_cpu_pllm_offset_mode  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu_pllm_accuracy     :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CPU_SYN_SYN_CPU12_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0434    syn_cpu13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sdec_dco_bias_sel     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sdec_dco_g            :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sdec_dco_rom_test     :  1,    //      8
                              :  7,    //  15: 9 reserved
    reg_sdec_dco_lpf          :  2,    //  17:16
                              : 14;    //  31:18 reserved
}CPU_SYN_SYN_CPU13_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0438    syn_cpu14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_dco_pdb_ctrl       :  1,    //      0
    reg_sdec_dco_pdb_ctrl     :  1,    //      1
    reg_disppll_pdb_ctrl      :  1,    //      2
    reg_corepll_pdb_ctrl      :  1,    //      3
    reg_ddrpll_pdb_ctrl       :  1,    //      4
    reg_cpupll_pdb_ctrl       :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_dco_ext_sel           :  1,    //      8
                              : 23;    //   31:9 reserved
}CPU_SYN_SYN_CPU14_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_043C    syn_cpu15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_disp_pqe_d100   :  1,    //      0
    reg_swrst_disp_pqe        :  1,    //      1
    reg_swrst_micom_d100      :  1,    //      2
    reg_swrst_vdec_d100       :  1,    //      3
    reg_swrst_m_d100          :  1,    //      4
    reg_swrst_pqe_d100        :  1,    //      5
    reg_swrst_demod_d100      :  1,    //      6
    reg_swrst_cpuperi_d100    :  1,    //      7
    reg_swrst_codec_d100      :  1,    //      8
    reg_swrst_micom           :  1,    //      9
    reg_swrst_vdec            :  1,    //     10
    reg_swrst_m               :  1,    //     11
    reg_swrst_pqe             :  1,    //     12
    reg_swrst_demod           :  1,    //     13
    reg_swrst_cpuperi         :  1,    //     14
    reg_swrst_codec           :  1,    //     15
    reg_disp297_clk_gate_en   :  1,    //     16
    reg_swrst_edid            :  1,    //     17
    reg_swrst_edid_d100       :  1,    //     18
                              : 13;    //  31:19 reserved
}CPU_SYN_SYN_CPU15_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0440    syn_cpu16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bmc_400_clk_sel       :  2,    //   1: 0
    reg_aud_600_clk_sel       :  2,    //   3: 2
    reg_dco_clk_sel           :  2,    //   5: 4
    reg_core_400_clk_sel      :  2,    //   7: 6
    reg_cpu_clk_sel           :  2,    //   9: 8
    reg_bus_clk_sel           :  2,    //  11:10
                              :  4,    //  15:12 reserved
    reg_pll_sel_bus           :  1,    //     16
    reg_pll_sel_bmc           :  1,    //     17
    reg_pll_sel_dco           :  1,    //     18
    reg_pll_sel_aud           :  1,    //     19
    reg_pll_sel_cpu           :  1,    //     20
    reg_pll_sel_core          :  1,    //     21
    reg_pll_sel_ddr           :  1,    //     22
                              :  1,    //     23 reserved
    reg_dcoin_clk_gate_en     :  1,    //     24
                              :  7;    //  31:25 reserved
}CPU_SYN_SYN_CPU16_L18F_A0;

/*-----------------------------------------------------------------------------------------
    cpu_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
UINT32                                                 _rsvd_00[   1] ;         // 0xC923_0400
CPU_SYN_SYN_CPU01_L18F_A0                    syn_cpu01                ;         // 0xC923_0404
CPU_SYN_SYN_CPU02_L18F_A0                    syn_cpu02                ;         // 0xC923_0408
CPU_SYN_SYN_CPU03_L18F_A0                    syn_cpu03                ;         // 0xC923_040C
CPU_SYN_SYN_CPU04_L18F_A0                    syn_cpu04                ;         // 0xC923_0410
CPU_SYN_SYN_CPU05_L18F_A0                    syn_cpu05                ;         // 0xC923_0414
CPU_SYN_SYN_CPU06_L18F_A0                    syn_cpu06                ;         // 0xC923_0418
CPU_SYN_SYN_CPU07_L18F_A0                    syn_cpu07                ;         // 0xC923_041C
CPU_SYN_SYN_CPU08_L18F_A0                    syn_cpu08                ;         // 0xC923_0420
CPU_SYN_SYN_CPU09_L18F_A0                    syn_cpu09                ;         // 0xC923_0424
CPU_SYN_SYN_CPU10_L18F_A0                    syn_cpu10                ;         // 0xC923_0428
CPU_SYN_SYN_CPU11_L18F_A0                    syn_cpu11                ;         // 0xC923_042C
CPU_SYN_SYN_CPU12_L18F_A0                    syn_cpu12                ;         // 0xC923_0430
CPU_SYN_SYN_CPU13_L18F_A0                    syn_cpu13                ;         // 0xC923_0434
CPU_SYN_SYN_CPU14_L18F_A0                    syn_cpu14                ;         // 0xC923_0438
CPU_SYN_SYN_CPU15_L18F_A0                    syn_cpu15                ;         // 0xC923_043C
CPU_SYN_SYN_CPU16_L18F_A0                    syn_cpu16                ;         // 0xC923_0440
} CPU_SYN_REG_L18F_A0;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CPU_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

