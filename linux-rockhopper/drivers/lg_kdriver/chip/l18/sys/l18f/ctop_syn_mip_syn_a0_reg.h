#ifndef _CTOP_SYN_MIP_SYN_A0_REG_H_
#define _CTOP_SYN_MIP_SYN_A0_REG_H_

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
    0xC930_E000    bmc_ctr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    swrst_axi                 :  1,    //      1
    swrst_apb                 :  1,    //      2
    swrst_axi_soc             :  1,    //      3
    axi_clk_gate_en           :  1,    //      4
    apb_clk_gate_en           :  1,    //      5
    axi_soc_clk_gate_en       :  1,    //      6
                              : 25;    //   31:7 reserved
}SYN_MIP_SYN_BMC_CTR00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E004    bmc_ctr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_f256fs_src          :  1,    //      0
    swrst_auda_f256fs_clk1    :  1,    //      1
    swrst_auda_f256fs_clk0    :  1,    //      2
    swrst_audclk_out_sub2     :  1,    //      3
    swrst_audclk_out_sub      :  1,    //      4
    swrst_aud_fs25clk         :  1,    //      5
    swrst_aud_fs24clk         :  1,    //      6
    swrst_aud_fs23clk         :  1,    //      7
    swrst_aud_fs22clk         :  1,    //      8
    swrst_aud_fs21clk         :  1,    //      9
    swrst_aud_fs20clk         :  1,    //     10
    swrst_audclk_out2         :  1,    //     11
    swrst_audclk_out          :  1,    //     12
    swrst_aclk_mux2           :  1,    //     13
    swrst_adto1               :  1,    //     14
    swrst_adto2               :  1,    //     15
    swrst_adto3               :  1,    //     16
    swrst_adto4               :  1,    //     17
    swrst_fs00                :  1,    //     18
    swrst_cvbs                :  1,    //     19
    swrst_f54m                :  1,    //     20
    swrst_vdac                :  1,    //     21
    swrst_f27m                :  1,    //     22
    swrst_auad                :  1,    //     23
    swrst_pix                 :  1,    //     24
    swrst_f24m                :  1,    //     25
    swrst_f24m_bb             :  1,    //     26
    swrst_aad_adc             :  1,    //     27
    swrst_dmd_s               :  1,    //     28
    swrst_dmd_tc              :  1,    //     29
                              :  2;    //  31:30 reserved
}SYN_MIP_SYN_BMC_CTR01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E008    bmc_ctr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux1_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux1_src             :  4,    //   7: 4
    aclk_mux2_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux2_src             :  4,    //  15:12
    aclk_mux3_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux3_src             :  4,    //  23:20
    aclk_mux4_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux4_src             :  4;    //  31:28
}SYN_MIP_SYN_BMC_CTR02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E00C    bmc_ctr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux5_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux5_src             :  4,    //   7: 4
    aclk_mux6_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux6_src             :  4,    //  15:12
    aclk_mux7_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux7_src             :  4,    //  23:20
    aclk_mux8_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux8_src             :  4;    //  31:28
}SYN_MIP_SYN_BMC_CTR03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E010    bmc_ctr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux9_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux9_src             :  4,    //   7: 4
    aclk_mux10_div            :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux10_src            :  4,    //  15:12
    aclk_mux11_div            :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux11_src            :  4,    //  23:20
    aclk_mux12_div            :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux12_src            :  4;    //  31:28
}SYN_MIP_SYN_BMC_CTR04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E014    bmc_ctr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux13_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux13_src            :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}SYN_MIP_SYN_BMC_CTR05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E018    bmc_ctr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto1_add_value           : 32;    //  31: 0
}SYN_MIP_SYN_BMC_CTR06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E01C    bmc_ctr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto1_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto1         :  1,    //     16
                              : 15;    //  31:17 reserved
}SYN_MIP_SYN_BMC_CTR07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E020    bmc_ctr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto2_add_value           : 32;    //  31: 0
}SYN_MIP_SYN_BMC_CTR08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E024    bmc_ctr09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto2_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto2         :  1,    //     16
                              : 15;    //  31:17 reserved
}SYN_MIP_SYN_BMC_CTR09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E028    bmc_ctr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto3_add_value           : 32;    //  31: 0
}SYN_MIP_SYN_BMC_CTR10_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E02C    bmc_ctr11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto3_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto3         :  1,    //     16
                              : 15;    //  31:17 reserved
}SYN_MIP_SYN_BMC_CTR11_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E030    bmc_ctr12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto4_add_value           : 32;    //  31: 0
}SYN_MIP_SYN_BMC_CTR12_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E034    bmc_ctr13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto4_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto4         :  1,    //     16
                              : 15;    //  31:17 reserved
}SYN_MIP_SYN_BMC_CTR13_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E038    bmc_ctr14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_afe3ch_ext_clock  :  2,    //   1: 0
    audclk_out_mux_sel        :  1,    //      2
    audclk_out_sub_mux_sel    :  1,    //      3
    sel_inv_aclk_mux11        :  1,    //      4
    sel_inv_aclk_mux12        :  1,    //      5
                              :  2,    //   7: 6 reserved
    sel_inv_aud_fsclk         :  8,    //  15: 8
    sel_inv_mclk0             :  1,    //     16
    sel_inv_mclk1             :  1,    //     17
    sel_inv_f54m_out_clock    :  1,    //     18
    sel_inv_f54m_clock        :  1,    //     19
    sel_inv_f27m_clock        :  1,    //     20
    sel_inv_vdac_clock        :  1,    //     21
    sel_inv_aud_fs20clk       :  1,    //     22
    sel_inv_aud_fs00_clk_out  :  1,    //     23
    sel_inv_aud_fs00_clk      :  1,    //     24
    sel_inv_aclk_mux2         :  1,    //     25
    sel_inv_cvbs_clk          :  1,    //     26
    sel_inv_aad_adc_clk       :  1,    //     27
    sel_inv_dmd_s_clk         :  1,    //     28
    sel_inv_dmd_tc_clk        :  1,    //     29
                              :  2;    //  31:30 reserved
}SYN_MIP_SYN_BMC_CTR14_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E03C    bmc_ctr15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f1fs_clk_sel              :  1,    //      0
    f64fs_clk_sel             :  1,    //      1
                              : 30;    //   31:2 reserved
}SYN_MIP_SYN_BMC_CTR15_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E040    bmc_ctr16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}SYN_MIP_SYN_BMC_CTR16_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_E044    bmc_ctr17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}SYN_MIP_SYN_BMC_CTR17_L18F_A0;

/*-----------------------------------------------------------------------------------------
    mip_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SYN_MIP_SYN_BMC_CTR00_L18F_A0            bmc_ctr00                ;         // 0xC930_E000
    SYN_MIP_SYN_BMC_CTR01_L18F_A0            bmc_ctr01                ;         // 0xC930_E004
    SYN_MIP_SYN_BMC_CTR02_L18F_A0            bmc_ctr02                ;         // 0xC930_E008
    SYN_MIP_SYN_BMC_CTR03_L18F_A0            bmc_ctr03                ;         // 0xC930_E00C
    SYN_MIP_SYN_BMC_CTR04_L18F_A0            bmc_ctr04                ;         // 0xC930_E010
    SYN_MIP_SYN_BMC_CTR05_L18F_A0            bmc_ctr05                ;         // 0xC930_E014
    SYN_MIP_SYN_BMC_CTR06_L18F_A0            bmc_ctr06                ;         // 0xC930_E018
    SYN_MIP_SYN_BMC_CTR07_L18F_A0            bmc_ctr07                ;         // 0xC930_E01C
    SYN_MIP_SYN_BMC_CTR08_L18F_A0            bmc_ctr08                ;         // 0xC930_E020
    SYN_MIP_SYN_BMC_CTR09_L18F_A0            bmc_ctr09                ;         // 0xC930_E024
    SYN_MIP_SYN_BMC_CTR10_L18F_A0            bmc_ctr10                ;         // 0xC930_E028
    SYN_MIP_SYN_BMC_CTR11_L18F_A0            bmc_ctr11                ;         // 0xC930_E02C
    SYN_MIP_SYN_BMC_CTR12_L18F_A0            bmc_ctr12                ;         // 0xC930_E030
    SYN_MIP_SYN_BMC_CTR13_L18F_A0            bmc_ctr13                ;         // 0xC930_E034
    SYN_MIP_SYN_BMC_CTR14_L18F_A0            bmc_ctr14                ;         // 0xC930_E038
    SYN_MIP_SYN_BMC_CTR15_L18F_A0            bmc_ctr15                ;         // 0xC930_E03C
    SYN_MIP_SYN_BMC_CTR16_L18F_A0            bmc_ctr16                ;         // 0xC930_E040
    SYN_MIP_SYN_BMC_CTR17_L18F_A0            bmc_ctr17                ;         // 0xC930_E044
} SYN_MIP_SYN_REG_L18F_A0;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_MIP_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_SYN_Register_Manual_55.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

