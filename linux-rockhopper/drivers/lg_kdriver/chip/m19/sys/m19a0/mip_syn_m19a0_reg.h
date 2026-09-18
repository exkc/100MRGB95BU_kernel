#ifndef _MIP_SYN_M19A0_REG_H_
#define _MIP_SYN_M19A0_REG_H_

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
    bus_clk_gate_en           :  1,    //      7
    hsusb3_clk12mohci_gate_en :  1,    //      8
    hsusb3_clk48mohci_gate_en :  1,    //      9
    hsusb3_freeclk_gate_en    :  1,    //     10
    hsusb3_phy_clock_gate_en  :  1,    //     11
                              : 20;    //  31:12 reserved
}MIP_SYN_BMC_CTR00_M19A0_T;

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
    soft_resetn_bus_n         :  1,    //     30
    soft_rst_usb_axi_bnd_n    :  1;    //     31
}MIP_SYN_BMC_CTR01_M19A0_T;

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
}MIP_SYN_BMC_CTR02_M19A0_T;

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
}MIP_SYN_BMC_CTR03_M19A0_T;

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
}MIP_SYN_BMC_CTR04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E014    bmc_ctr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux13_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux13_src            :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}MIP_SYN_BMC_CTR05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E018    bmc_ctr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto1_add_value           : 32;    //  31: 0
}MIP_SYN_BMC_CTR06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E01C    bmc_ctr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto1_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto1         :  1,    //     16
                              : 15;    //  31:17 reserved
}MIP_SYN_BMC_CTR07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E020    bmc_ctr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto2_add_value           : 32;    //  31: 0
}MIP_SYN_BMC_CTR08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E024    bmc_ctr09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto2_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto2         :  1,    //     16
                              : 15;    //  31:17 reserved
}MIP_SYN_BMC_CTR09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E028    bmc_ctr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto3_add_value           : 32;    //  31: 0
}MIP_SYN_BMC_CTR10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E02C    bmc_ctr11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto3_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto3         :  1,    //     16
                              : 15;    //  31:17 reserved
}MIP_SYN_BMC_CTR11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E030    bmc_ctr12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto4_add_value           : 32;    //  31: 0
}MIP_SYN_BMC_CTR12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E034    bmc_ctr13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    adto4_err_value           : 12,    //  11: 0
                              :  4,    //  15:12 reserved
    sync_update_adto4         :  1,    //     16
                              : 15;    //  31:17 reserved
}MIP_SYN_BMC_CTR13_M19A0_T;

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
}MIP_SYN_BMC_CTR14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E03C    bmc_ctr15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f1fs_clk_sel              :  1,    //      0
    f64fs_clk_sel             :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_SYN_BMC_CTR15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E040    bmc_ctr16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}MIP_SYN_BMC_CTR16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E044    bmc_ctr17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}MIP_SYN_BMC_CTR17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E048    a_crg_check_bmc_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk0_value            : 16,    //  15: 0
    bmc_rst0_check            :  1,    //     16
    bmc_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk0_off_value        :  8,    //  27:20
    bmc_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk0_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E04C    a_crg_check_bmc_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk1_value            : 16,    //  15: 0
    bmc_rst1_check            :  1,    //     16
    bmc_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk1_off_value        :  8,    //  27:20
    bmc_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk1_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E050    a_crg_check_bmc_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk2_value            : 16,    //  15: 0
    bmc_rst2_check            :  1,    //     16
    bmc_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk2_off_value        :  8,    //  27:20
    bmc_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk2_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E054    a_crg_check_bmc_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk3_value            : 16,    //  15: 0
    bmc_rst3_check            :  1,    //     16
    bmc_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk3_off_value        :  8,    //  27:20
    bmc_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk3_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E058    a_crg_check_bmc_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk4_value            : 16,    //  15: 0
    bmc_rst4_check            :  1,    //     16
    bmc_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk4_off_value        :  8,    //  27:20
    bmc_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk4_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E05C    a_crg_check_bmc_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk5_value            : 16,    //  15: 0
    bmc_rst5_check            :  1,    //     16
    bmc_clk5_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk5_off_value        :  8,    //  27:20
    bmc_clk5_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk5_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E060    a_crg_check_bmc_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk6_value            : 16,    //  15: 0
    bmc_rst6_check            :  1,    //     16
    bmc_clk6_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk6_off_value        :  8,    //  27:20
    bmc_clk6_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk6_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E064    a_crg_check_bmc_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk7_value            : 16,    //  15: 0
    bmc_rst7_check            :  1,    //     16
    bmc_clk7_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk7_off_value        :  8,    //  27:20
    bmc_clk7_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk7_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_7_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E068    a_crg_check_bmc_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk8_value            : 16,    //  15: 0
    bmc_rst8_check            :  1,    //     16
    bmc_clk8_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk8_off_value        :  8,    //  27:20
    bmc_clk8_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk8_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_8_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E06C    a_crg_check_bmc_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk9_value            : 16,    //  15: 0
    bmc_rst9_check            :  1,    //     16
    bmc_clk9_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk9_off_value        :  8,    //  27:20
    bmc_clk9_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk9_gate             :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_9_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E070    a_crg_check_bmc_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk10_value           : 16,    //  15: 0
    bmc_rst10_check           :  1,    //     16
    bmc_clk10_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk10_off_value       :  8,    //  27:20
    bmc_clk10_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk10_gate            :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E074    a_crg_check_bmc_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bmc_clk11_value           : 16,    //  15: 0
    bmc_rst11_check           :  1,    //     16
    bmc_clk11_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    bmc_clk11_off_value       :  8,    //  27:20
    bmc_clk11_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    bmc_clk11_gate            :  1;    //     31
}MIP_SYN_A_CRG_CHECK_BMC_11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E078    bmc_ctr18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_dbb        :  1,    //      0
    reg_ls_disable_usb        :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_SYN_BMC_CTR18_M19A0_T;

/*-----------------------------------------------------------------------------------------
    mip_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
MIP_SYN_BMC_CTR00_M19A0_T                    bmc_ctr00                ;         // 0xC930_E000
MIP_SYN_BMC_CTR01_M19A0_T                    bmc_ctr01                ;         // 0xC930_E004
MIP_SYN_BMC_CTR02_M19A0_T                    bmc_ctr02                ;         // 0xC930_E008
MIP_SYN_BMC_CTR03_M19A0_T                    bmc_ctr03                ;         // 0xC930_E00C
MIP_SYN_BMC_CTR04_M19A0_T                    bmc_ctr04                ;         // 0xC930_E010
MIP_SYN_BMC_CTR05_M19A0_T                    bmc_ctr05                ;         // 0xC930_E014
MIP_SYN_BMC_CTR06_M19A0_T                    bmc_ctr06                ;         // 0xC930_E018
MIP_SYN_BMC_CTR07_M19A0_T                    bmc_ctr07                ;         // 0xC930_E01C
MIP_SYN_BMC_CTR08_M19A0_T                    bmc_ctr08                ;         // 0xC930_E020
MIP_SYN_BMC_CTR09_M19A0_T                    bmc_ctr09                ;         // 0xC930_E024
MIP_SYN_BMC_CTR10_M19A0_T                    bmc_ctr10                ;         // 0xC930_E028
MIP_SYN_BMC_CTR11_M19A0_T                    bmc_ctr11                ;         // 0xC930_E02C
MIP_SYN_BMC_CTR12_M19A0_T                    bmc_ctr12                ;         // 0xC930_E030
MIP_SYN_BMC_CTR13_M19A0_T                    bmc_ctr13                ;         // 0xC930_E034
MIP_SYN_BMC_CTR14_M19A0_T                    bmc_ctr14                ;         // 0xC930_E038
MIP_SYN_BMC_CTR15_M19A0_T                    bmc_ctr15                ;         // 0xC930_E03C
MIP_SYN_BMC_CTR16_M19A0_T                    bmc_ctr16                ;         // 0xC930_E040
MIP_SYN_BMC_CTR17_M19A0_T                    bmc_ctr17                ;         // 0xC930_E044
MIP_SYN_A_CRG_CHECK_BMC_0_M19A0_T            a_crg_check_bmc_0        ;         // 0xC930_E048
MIP_SYN_A_CRG_CHECK_BMC_1_M19A0_T            a_crg_check_bmc_1        ;         // 0xC930_E04C
MIP_SYN_A_CRG_CHECK_BMC_2_M19A0_T            a_crg_check_bmc_2        ;         // 0xC930_E050
MIP_SYN_A_CRG_CHECK_BMC_3_M19A0_T            a_crg_check_bmc_3        ;         // 0xC930_E054
MIP_SYN_A_CRG_CHECK_BMC_4_M19A0_T            a_crg_check_bmc_4        ;         // 0xC930_E058
MIP_SYN_A_CRG_CHECK_BMC_5_M19A0_T            a_crg_check_bmc_5        ;         // 0xC930_E05C
MIP_SYN_A_CRG_CHECK_BMC_6_M19A0_T            a_crg_check_bmc_6        ;         // 0xC930_E060
MIP_SYN_A_CRG_CHECK_BMC_7_M19A0_T            a_crg_check_bmc_7        ;         // 0xC930_E064
MIP_SYN_A_CRG_CHECK_BMC_8_M19A0_T            a_crg_check_bmc_8        ;         // 0xC930_E068
MIP_SYN_A_CRG_CHECK_BMC_9_M19A0_T            a_crg_check_bmc_9        ;         // 0xC930_E06C
MIP_SYN_A_CRG_CHECK_BMC_10_M19A0_T           a_crg_check_bmc_10       ;         // 0xC930_E070
MIP_SYN_A_CRG_CHECK_BMC_11_M19A0_T           a_crg_check_bmc_11       ;         // 0xC930_E074
MIP_SYN_BMC_CTR18_M19A0_T                    bmc_ctr18                ;         // 0xC930_E078
} MIP_SYN_REG_M19A0_T;
/* 31 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _MIP_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

