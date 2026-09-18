#ifndef _DPE_SYN_M19A0_REG_H_
#define _DPE_SYN_M19A0_REG_H_

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
    0xC930_A800    crg_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apb_mcu_bnd_clk_gate_en   :  1,    //      0
    apb_bnd_clk_gate_en       :  1,    //      1
    sar_adc_clk_gate_en       :  1,    //      2
    tcon_osc_clk_gate_en      :  1,    //      3
    tcon_osd_clk_gate_en      :  1,    //      4
    tcon_pix_clk_gate_en      :  1,    //      5
    tcon_pix4_clk_gate_en     :  1,    //      6
    tcon_pix2_clk_gate_en     :  1,    //      7
    tcon_axi_clk_gate_en      :  1,    //      8
    tcon_mcu_clk_gate_en      :  1,    //      9
    tcon_apb_clk_gate_en      :  1,    //     10
                              :  1,    //     11 reserved
    tcon_wpr_clk_gate_en      :  1,    //     12
    tcon_siw_clk_gate_en      :  1,    //     13
    tcon_fcic_clk_gate_en     :  1,    //     14
    tcon_clk_gate_en          :  1,    //     15
    tcon_odc_clk_gate_en      :  1,    //     16
    tcon_lvx_clk_gate_en      :  1,    //     17
    tcon_epi_clk_gate_en      :  1,    //     18
    tcon_tgen_clk_gate_en     :  1,    //     19
    tcon_pod_clk_gate_en      :  1,    //     20
    tcon_ldiv_clk_gate_en     :  1,    //     21
    tcon_mem0_clk_gate_en     :  1,    //     22
    tcon_mem1_clk_gate_en     :  1,    //     23
    tcon_mem2_clk_gate_en     :  1,    //     24
                              :  7;    //  31:25 reserved
}DPE_SYN_CRG_DPE00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A804    crg_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_osd_clk_sel          :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    tcon_pix_clk_sel          :  3,    //   6: 4
                              :  1,    //      7 reserved
    tcon_pix2_clk_sel         :  3,    //  10: 8
                              :  1,    //     11 reserved
    tcon_mem_clk_sel          :  1,    //     12
                              :  3,    //  15:13 reserved
    tcon_siw_clk_sel          :  1,    //     16
    tcon_fcic_clk_sel         :  1,    //     17
    tcon_pod_clk_sel          :  1,    //     18
    tcon_odc_clk_sel          :  1,    //     19
    tcon_epi_clk_sel          :  2,    //  21:20
    tcon_lvx_clk_sel          :  2,    //  23:22
    tcon_wpr_clk_sel          :  1,    //     24
                              :  1,    //     25 reserved
    disp594_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}DPE_SYN_CRG_DPE01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A808    crg_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_tcon_osd_bnd_n   :  1,    //      0
    soft_rst_tcon_pix2_bnd_n  :  1,    //      1
    soft_rst_apb_mcu_bnd_n    :  1,    //      2
    soft_rst_tcon_osd_n       :  1,    //      3
    soft_rst_tcon_pix_n       :  1,    //      4
    soft_rst_tcon_pix4_n      :  1,    //      5
    soft_rst_tcon_pix2_n      :  1,    //      6
    soft_rst_tcon_apb_hm_n    :  1,    //      7
    soft_rst_tcon_axi_n       :  1,    //      8
    soft_rst_tcon_mcu_n       :  1,    //      9
    soft_rst_tcon_apb_n       :  1,    //     10
    soft_rst_tcon_wpr_n       :  1,    //     11
    soft_rst_tcon_siw_n       :  1,    //     12
    soft_rst_tcon_fcic_n      :  1,    //     13
    soft_rst_tcon_n           :  1,    //     14
    soft_rst_tcon_odc_n       :  1,    //     15
    soft_rst_tcon_lvx_n       :  1,    //     16
    soft_rst_tcon_epi_n       :  1,    //     17
    soft_rst_tcon_tgen_n      :  1,    //     18
    soft_rst_tcon_pod_n       :  1,    //     19
    soft_rst_tcon_ldiv_n      :  1,    //     20
    soft_rst_tcon_axi_bnd_n   :  1,    //     21
                              : 10;    //  31:22 reserved
}DPE_SYN_CRG_DPE02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A80C    syn_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}DPE_SYN_SYN_DPE03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A810    syn_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}DPE_SYN_SYN_DPE04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A814    syn_dpe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_pdb              :  1,    //      0
                              : 11,    //  11: 1 reserved
    reg_sadc_pc               :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_cc               :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_isel             :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_sadc_test             :  4,    //  27:24
                              :  4;    //  31:28 reserved
}DPE_SYN_SYN_DPE05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A818    syn_dpe06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_soc          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_lpf_chsel        :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sadc_lpf_start        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dsel                  :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_lpf_mode         :  3,    //  18:16
                              :  5,    //  23:19 reserved
    reg_sadc_lpf_eoc_inv      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_sadc_lpf_manual       :  1,    //     28
                              :  3;    //  31:29 reserved
}DPE_SYN_SYN_DPE06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A81C    syn_dpe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_data_clear   :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A820    syn_dpe08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_valid            :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A824    syn_dpe09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data012          : 32;    //  31: 0
}DPE_SYN_SYN_DPE09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A828    syn_dpe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data345          : 32;    //  31: 0
}DPE_SYN_SYN_DPE10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A82C    syn_dpe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_debug_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A830    syn_dpe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_debug_data       :  8,    //   7: 0
                              : 20,    //  27: 8 reserved
    sadc_lpf_adc_done         :  1,    //     28
                              :  3;    //  31:29 reserved
}DPE_SYN_SYN_DPE12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A834    syn_dpe13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_trig_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A838    a_crg_check_dpe_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk0_value            : 16,    //  15: 0
    dpe_rst0_check            :  1,    //     16
    dpe_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk0_off_value        :  8,    //  27:20
    dpe_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk0_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A83C    a_crg_check_dpe_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk1_value            : 16,    //  15: 0
    dpe_rst1_check            :  1,    //     16
    dpe_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk1_off_value        :  8,    //  27:20
    dpe_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk1_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A840    a_crg_check_dpe_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk2_value            : 16,    //  15: 0
    dpe_rst2_check            :  1,    //     16
    dpe_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk2_off_value        :  8,    //  27:20
    dpe_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk2_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A844    a_crg_check_dpe_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk3_value            : 16,    //  15: 0
    dpe_rst3_check            :  1,    //     16
    dpe_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk3_off_value        :  8,    //  27:20
    dpe_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk3_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A848    a_crg_check_dpe_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk4_value            : 16,    //  15: 0
    dpe_rst4_check            :  1,    //     16
    dpe_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk4_off_value        :  8,    //  27:20
    dpe_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk4_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A84C    a_crg_check_dpe_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk5_value            : 16,    //  15: 0
    dpe_rst5_check            :  1,    //     16
    dpe_clk5_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk5_off_value        :  8,    //  27:20
    dpe_clk5_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk5_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A850    syn_dpe14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A854    syn_dpe15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_osd                 :  1,    //      0
    swrst_led_tcon            :  1,    //      1
    tcon_gmau_flush_done      :  1,    //      2
                              : 29;    //   31:3 reserved
}DPE_SYN_SYN_DPE15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A858    syn_dpe16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A85C    syn_dpe17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4tx_intr_status          :  1,    //      0
                              :  7,    //   7: 1 reserved
    c4tx_intr_enable          :  1,    //      8
                              :  7,    //  15: 9 reserved
    c4tx_intr_clear           :  1,    //     16
                              :  7,    //  23:17 reserved
    c4tx_lockn_tomain_level   :  1,    //     24
                              :  7;    //  31:25 reserved
}DPE_SYN_SYN_DPE17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A860    a_crg_check_dpe_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk6_value            : 16,    //  15: 0
    dpe_rst6_check            :  1,    //     16
    dpe_clk6_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk6_off_value        :  8,    //  27:20
    dpe_clk6_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk6_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A864    a_crg_check_dpe_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk7_value            : 16,    //  15: 0
    dpe_rst7_check            :  1,    //     16
    dpe_clk7_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk7_off_value        :  8,    //  27:20
    dpe_clk7_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk7_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_7_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A868    a_crg_check_dpe_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk8_value            : 16,    //  15: 0
    dpe_rst8_check            :  1,    //     16
    dpe_clk8_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk8_off_value        :  8,    //  27:20
    dpe_clk8_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk8_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_8_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A86C    a_crg_check_dpe_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk9_value            : 16,    //  15: 0
    dpe_rst9_check            :  1,    //     16
    dpe_clk9_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk9_off_value        :  8,    //  27:20
    dpe_clk9_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk9_gate             :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_9_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A870    a_crg_check_dpe_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk10_value           : 16,    //  15: 0
    dpe_rst10_check           :  1,    //     16
    dpe_clk10_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk10_off_value       :  8,    //  27:20
    dpe_clk10_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk10_gate            :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A874    a_crg_check_dpe_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dpe_clk11_value           : 16,    //  15: 0
    dpe_rst11_check           :  1,    //     16
    dpe_clk11_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    dpe_clk11_off_value       :  8,    //  27:20
    dpe_clk11_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    dpe_clk11_gate            :  1;    //     31
}DPE_SYN_A_CRG_CHECK_DPE_11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    dpe_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
DPE_SYN_CRG_DPE00_M19A0_T                    crg_dpe00                ;         // 0xC930_A800
DPE_SYN_CRG_DPE01_M19A0_T                    crg_dpe01                ;         // 0xC930_A804
DPE_SYN_CRG_DPE02_M19A0_T                    crg_dpe02                ;         // 0xC930_A808
DPE_SYN_SYN_DPE03_M19A0_T                    syn_dpe03                ;         // 0xC930_A80C
DPE_SYN_SYN_DPE04_M19A0_T                    syn_dpe04                ;         // 0xC930_A810
DPE_SYN_SYN_DPE05_M19A0_T                    syn_dpe05                ;         // 0xC930_A814
DPE_SYN_SYN_DPE06_M19A0_T                    syn_dpe06                ;         // 0xC930_A818
DPE_SYN_SYN_DPE07_M19A0_T                    syn_dpe07                ;         // 0xC930_A81C
DPE_SYN_SYN_DPE08_M19A0_T                    syn_dpe08                ;         // 0xC930_A820
DPE_SYN_SYN_DPE09_M19A0_T                    syn_dpe09                ;         // 0xC930_A824
DPE_SYN_SYN_DPE10_M19A0_T                    syn_dpe10                ;         // 0xC930_A828
DPE_SYN_SYN_DPE11_M19A0_T                    syn_dpe11                ;         // 0xC930_A82C
DPE_SYN_SYN_DPE12_M19A0_T                    syn_dpe12                ;         // 0xC930_A830
DPE_SYN_SYN_DPE13_M19A0_T                    syn_dpe13                ;         // 0xC930_A834
DPE_SYN_A_CRG_CHECK_DPE_0_M19A0_T            a_crg_check_dpe_0        ;         // 0xC930_A838
DPE_SYN_A_CRG_CHECK_DPE_1_M19A0_T            a_crg_check_dpe_1        ;         // 0xC930_A83C
DPE_SYN_A_CRG_CHECK_DPE_2_M19A0_T            a_crg_check_dpe_2        ;         // 0xC930_A840
DPE_SYN_A_CRG_CHECK_DPE_3_M19A0_T            a_crg_check_dpe_3        ;         // 0xC930_A844
DPE_SYN_A_CRG_CHECK_DPE_4_M19A0_T            a_crg_check_dpe_4        ;         // 0xC930_A848
DPE_SYN_A_CRG_CHECK_DPE_5_M19A0_T            a_crg_check_dpe_5        ;         // 0xC930_A84C
DPE_SYN_SYN_DPE14_M19A0_T                    syn_dpe14                ;         // 0xC930_A850
DPE_SYN_SYN_DPE15_M19A0_T                    syn_dpe15                ;         // 0xC930_A854
DPE_SYN_SYN_DPE16_M19A0_T                    syn_dpe16                ;         // 0xC930_A858
DPE_SYN_SYN_DPE17_M19A0_T                    syn_dpe17                ;         // 0xC930_A85C
DPE_SYN_A_CRG_CHECK_DPE_6_M19A0_T            a_crg_check_dpe_6        ;         // 0xC930_A860
DPE_SYN_A_CRG_CHECK_DPE_7_M19A0_T            a_crg_check_dpe_7        ;         // 0xC930_A864
DPE_SYN_A_CRG_CHECK_DPE_8_M19A0_T            a_crg_check_dpe_8        ;         // 0xC930_A868
DPE_SYN_A_CRG_CHECK_DPE_9_M19A0_T            a_crg_check_dpe_9        ;         // 0xC930_A86C
DPE_SYN_A_CRG_CHECK_DPE_10_M19A0_T           a_crg_check_dpe_10       ;         // 0xC930_A870
DPE_SYN_A_CRG_CHECK_DPE_11_M19A0_T           a_crg_check_dpe_11       ;         // 0xC930_A874
} DPE_SYN_REG_M19A0_T;
/* 30 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _DPE_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

