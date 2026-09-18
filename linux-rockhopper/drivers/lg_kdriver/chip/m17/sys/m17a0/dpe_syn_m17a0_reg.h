#ifndef _DPE_SYN_M17A0_REG_H_
#define _DPE_SYN_M17A0_REG_H_

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
    0xC930_A000    crg_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_apb_clk_gate_en      :  1,    //      0
    tcon_axi_clk_gate_en      :  1,    //      1
    tcon_pix2_clk_gate_en     :  1,    //      2
    tcon_pix_clk_gate_en      :  1,    //      3
    tcon_osd_clk_gate_en      :  1,    //      4
    tcon_osc_clk_gate_en      :  1,    //      5
    tcon_pix4_clk_gate_en     :  1,    //      6
    tcon_mcu_clk_gate_en      :  1,    //      7
    tcon_mem_clk_gate_en      :  1,    //      8
    tcon_fcic_clk_gate_en     :  1,    //      9
    tcon_siw_clk_gate_en      :  1,    //     10
    tcon_wpr_clk_gate_en      :  1,    //     11
    tcon_clk_gate_en          :  1,    //     12
    tcon_fcic_clk_sel         :  1,    //     13
    tcon_siw_clk_sel          :  1,    //     14
    tcon_wpr_clk_sel          :  1,    //     15
    tcon_pix2_clk_sel         :  3,    //  18:16
                              :  1,    //     19 reserved
    tcon_pix_clk_sel          :  3,    //  22:20
                              :  1,    //     23 reserved
    tcon_osd_clk_sel          :  2,    //  25:24
                              :  2,    //  27:26 reserved
    tcon_mem_clk_sel          :  2,    //  29:28
    sar_adc_clk_gate_en       :  1,    //     30
                              :  1;    //  31:31 reserved
}DPE_SYN_CRG_DPE00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A004    crg_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_tcon_apb            :  1,    //      0
    swrst_tcon_axi            :  1,    //      1
    swrst_tcon_pix2           :  1,    //      2
    swrst_tcon_pix            :  1,    //      3
    swrst_tcon_osd            :  1,    //      4
    swrst_tcon_pix4           :  1,    //      5
    swrst_tcon_mcu            :  1,    //      6
    swrst_tcon_apb_hm         :  1,    //      7
    swrst_tcon_fcic           :  1,    //      8
    swrst_tcon_siw            :  1,    //      9
    swrst_tcon_wpr            :  1,    //     10
    swrst_tcon                :  1,    //     11
                              : 20;    //  31:12 reserved
}DPE_SYN_CRG_DPE01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A008    syn_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}DPE_SYN_SYN_DPE02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A00C    syn_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}DPE_SYN_SYN_DPE03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A010    syn_dpe04 ''
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
}DPE_SYN_SYN_DPE04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A014    syn_dpe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_soc          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_lpf_chsel        :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sadc_lpf_start        :  1,    //      8
                              :  7,    //  15: 9 reserved
    reg_sadc_lpf_mode         :  3,    //  18:16
                              :  5,    //  23:19 reserved
    reg_sadc_lpf_eoc_inv      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_sadc_lpf_manual       :  1,    //     28
                              :  3;    //  31:29 reserved
}DPE_SYN_SYN_DPE05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A018    syn_dpe06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_data_clear   :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A01C    syn_dpe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_valid            :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A020    syn_dpe08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data012          : 32;    //  31: 0
}DPE_SYN_SYN_DPE08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A024    syn_dpe09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data345          : 32;    //  31: 0
}DPE_SYN_SYN_DPE09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A028    syn_dpe10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_debug_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE10_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A02C    syn_dpe11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_debug_data       :  8,    //   7: 0
                              : 20,    //  27: 8 reserved
    sadc_lpf_adc_done         :  1,    //     28
                              :  3;    //  31:29 reserved
}DPE_SYN_SYN_DPE11_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A030    syn_dpe12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_trig_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}DPE_SYN_SYN_DPE12_M17_A0;

/*-----------------------------------------------------------------------------------------
    dpe_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
DPE_SYN_CRG_DPE00_M17_A0                     crg_dpe00                ;         // 0xC930_A000
DPE_SYN_CRG_DPE01_M17_A0                     crg_dpe01                ;         // 0xC930_A004
DPE_SYN_SYN_DPE02_M17_A0                     syn_dpe02                ;         // 0xC930_A008
DPE_SYN_SYN_DPE03_M17_A0                     syn_dpe03                ;         // 0xC930_A00C
DPE_SYN_SYN_DPE04_M17_A0                     syn_dpe04                ;         // 0xC930_A010
DPE_SYN_SYN_DPE05_M17_A0                     syn_dpe05                ;         // 0xC930_A014
DPE_SYN_SYN_DPE06_M17_A0                     syn_dpe06                ;         // 0xC930_A018
DPE_SYN_SYN_DPE07_M17_A0                     syn_dpe07                ;         // 0xC930_A01C
DPE_SYN_SYN_DPE08_M17_A0                     syn_dpe08                ;         // 0xC930_A020
DPE_SYN_SYN_DPE09_M17_A0                     syn_dpe09                ;         // 0xC930_A024
DPE_SYN_SYN_DPE10_M17_A0                     syn_dpe10                ;         // 0xC930_A028
DPE_SYN_SYN_DPE11_M17_A0                     syn_dpe11                ;         // 0xC930_A02C
DPE_SYN_SYN_DPE12_M17_A0                     syn_dpe12                ;         // 0xC930_A030
} DPE_SYN_REG_M17_A0;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _DPE_SYN_M17A0_REG_H_ */

/* from 'M16PP_CTOP_SYN_Register_Manual_52.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

