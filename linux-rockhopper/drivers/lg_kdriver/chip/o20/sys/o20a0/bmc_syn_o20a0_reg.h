#ifndef _BMC_SYN_O20A0_REG_H_
#define _BMC_SYN_O20A0_REG_H_

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
    0xC34E_0000    crg_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apb_clk_gate_en           :  1,    //      0
    axi_clk_gate_en           :  1,    //      1
    axi_soc_clk_gate_en       :  1,    //      2
    fsc_pwm_clk_gate_en       :  1,    //      3
    fsc_apb_clk_gate_en       :  1,    //      4
                              : 27;    //   31:5 reserved
}BMC_SYN_CRG_BMC00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0004    crg_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__soft_rst_usb_bus_bnd_n: 1,    //  0
                              :  3,    //   3: 1 reserved
    swrst_auad                :  1,    //      4
    swrst_pix                 :  1,    //      5
    swrst_f24m                :  1,    //      6
    swrst_axi_soc             :  1,    //      7
    swrst_axi                 :  1,    //      8
    swrst_apb                 :  1,    //      9
    soft_rst_pwm_n            :  1,    //     10
    soft_rst_fsc_apb_n        :  1,    //     11
                              : 20;    //  31:12 reserved
}BMC_SYN_CRG_BMC01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0008    crg_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    swrst_audclk_out_sub2     :  1,    //      1
    swrst_audclk_out2         :  1,    //      2
    swrst_auda_f256fs_clk1    :  1,    //      3
    swrst_auda_f256fs_clk0    :  1,    //      4
    swrst_audclk_out_sub      :  1,    //      5
    swrst_aud_fs26clk         :  1,    //      6
    swrst_aud_fs25clk         :  1,    //      7
    swrst_aud_fs24clk         :  1,    //      8
    swrst_aud_fs23clk         :  1,    //      9
    swrst_aud_fs22clk         :  1,    //     10
    swrst_aud_fs21clk         :  1,    //     11
    swrst_aud_fs20clk         :  1,    //     12
    swrst_audclk_out          :  1,    //     13
    swrst_aclk_mux2           :  1,    //     14
    swrst_adto4               :  1,    //     15
    swrst_adto3               :  1,    //     16
    swrst_adto2               :  1,    //     17
    swrst_adto1               :  1,    //     18
    swrst_f256fs_src          :  1,    //     19
    swrst_aad_adc             :  1,    //     20
    swrst_dmd_s               :  1,    //     21
    swrst_dmd_tc              :  1,    //     22
    swrst_fs00                :  1,    //     23
    swrst_cvbs                :  1,    //     24
    swrst_f54m                :  1,    //     25
    swrst_f27m                :  1,    //     26
    swrst_vdac                :  1,    //     27
    swrst_f24m_bb             :  1,    //     28
                              :  3;    //  31:29 reserved
}BMC_SYN_CRG_BMC02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_000C    crg_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_afe3ch_ext_clock  :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    f64fs_clk_sel             :  1,    //      4
    f1fs_clk_sel              :  1,    //      5
                              : 26;    //   31:6 reserved
}BMC_SYN_CRG_BMC03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0010    crg_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value       : 32;    //  31: 0
}BMC_SYN_CRG_BMC04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0014    crg_bmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BMC_SYN_CRG_BMC05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_001C    crg_bmc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value       : 32;    //  31: 0
}BMC_SYN_CRG_BMC06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0020    crg_bmc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BMC_SYN_CRG_BMC07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0024    crg_bmc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_add_value       : 32;    //  31: 0
}BMC_SYN_CRG_BMC08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0028    crg_bmc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BMC_SYN_CRG_BMC09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_002C    crg_bmc11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_add_value       : 32;    //  31: 0
}BMC_SYN_CRG_BMC11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0030    crg_bmc12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BMC_SYN_CRG_BMC12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0034    crg_bmc10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux4_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux4_src             :  4,    //   7: 4
    aclk_mux3_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux3_src             :  4,    //  15:12
    aclk_mux2_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux2_src             :  4,    //  23:20
    aclk_mux1_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux1_src             :  4;    //  31:28
}BMC_SYN_CRG_BMC10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0038    crg_bmc13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux8_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux8_src             :  4,    //   7: 4
    aclk_mux7_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux7_src             :  4,    //  15:12
    aclk_mux6_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux6_src             :  4,    //  23:20
    aclk_mux5_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux5_src             :  4;    //  31:28
}BMC_SYN_CRG_BMC13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_003C    crg_bmc14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux12_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux12_src            :  4,    //   7: 4
    aclk_mux11_div            :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux11_src            :  4,    //  15:12
    aclk_mux10_div            :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux10_src            :  4,    //  23:20
    aclk_mux9_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux9_src             :  4;    //  31:28
}BMC_SYN_CRG_BMC14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0040    crg_bmc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux14_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux14_src            :  4,    //   7: 4
    aclk_mux13_div            :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux13_src            :  4,    //  15:12
                              : 16;    //  31:16 reserved
}BMC_SYN_CRG_BMC15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0044    crg_bmc16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    audclk_out_mux_sel        :  1,    //      0
    audclk_out_sub_mux_sel    :  1,    //      1
                              : 30;    //   31:2 reserved
}BMC_SYN_CRG_BMC16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0048    crg_bmc17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sel_inv_aud_fsclk         : 10,    //   9: 0
    sel_inv_aud_fs20clk       :  1,    //     10
    sel_inv_aud_fs00_clk      :  1,    //     11
    sel_inv_aud_fs00_clk_out  :  1,    //     12
    sel_inv_aclk_mux12        :  1,    //     13
    sel_inv_aclk_mux11        :  1,    //     14
    sel_inv_mclk1             :  1,    //     15
    sel_inv_mclk0             :  1,    //     16
    sel_inv_f54m_clock        :  1,    //     17
    sel_inv_f54m_out_clock    :  1,    //     18
    sel_inv_f27m_clock        :  1,    //     19
    sel_inv_vdac_clock        :  1,    //     20
    sel_inv_cvbs_clk          :  1,    //     21
    sel_inv_aclk_mux2         :  1,    //     22
    sel_inv_aad_adc_clk       :  1,    //     23
    sel_inv_dmd_s_clk         :  1,    //     24
    sel_inv_dmd_tc_clk        :  1,    //     25
                              :  6;    //  31:26 reserved
}BMC_SYN_CRG_BMC17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_004C    crg_bmc18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sync_update_adto4         :  1,    //      0
    sync_update_adto3         :  1,    //      1
    sync_update_adto2         :  1,    //      2
    sync_update_adto1         :  1,    //      3
                              : 28;    //   31:4 reserved
}BMC_SYN_CRG_BMC18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0050    crg_bmc19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 25,    //  24: 0 reserved
    sel_dbb_i2c_sel           :  1,    //     25
                              :  6;    //  31:26 reserved
}BMC_SYN_CRG_BMC19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0054    crg_bmc20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_opermode          :  8,    //   7: 0
    reg_dbb_reg_init          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dbb_reset             :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_mcu_reset             :  1,    //     16
                              : 15;    //  31:17 reserved
}BMC_SYN_CRG_BMC20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0058    crg_bmc21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_earc_add_value_pos: 17,    //  16:0
                              : 15;    //  31:17 reserved
}BMC_SYN_CRG_BMC21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_005C    crg_bmc22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_earc_add_value_neg: 17,    //  16:0
                              : 15;    //  31:17 reserved
}BMC_SYN_CRG_BMC22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0060    crg_usb_hs00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__usb_bus_clk_gate_en: 1,    //  0
    reg_usb_hs__usb_freeclk_gate_en: 1,    //  1
    reg_usb_hs__usb_clk12mohci_gate_en: 1,    //  2
    reg_usb_hs__usb_phy_clock_gate_en: 1,    //  3
    reg_usb_hs__usb_clk48mohci_gate_en: 1,    //  4
    reg_usb_hs__usb_xtal_clk_20m_gate_en: 1,    //  5
                              : 26;    //   31:6 reserved
}BMC_SYN_CRG_USB_HS00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0068    crg_usb_hs02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__usb_freeclk_sel: 1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_CRG_USB_HS02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_006C    crg_usb_hs03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__crg_freq_value: 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_usb_hs__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_usb_hs__crg_clk_off_check: 1,    //   30
    reg_usb_hs__crg_clk_gate  :  1;    //     31
}BMC_SYN_CRG_USB_HS03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0070    crg_usb_hs04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs__crg_clk_rst_sel: 32;    //  31:0
}BMC_SYN_CRG_USB_HS04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_007C    usb_axi_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_hs_axi_addr_33    :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_USB_AXI_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0080    dbb_apb_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_apb_base_sel      :  1,    //      0
                              : 31;    //   31:1 reserved
}BMC_SYN_DBB_APB_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0084    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_usb_hs: 9,    //   8: 0
                              : 23;    //   31:9 reserved
}BMC_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0088    dft01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb_hs_4_bist_error       :  1,    //      0
    usb_hs_4_bist_done        :  1,    //      1
                              : 30;    //   31:2 reserved
}BMC_SYN_DFT01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_008C    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_dbb        :  1,    //      0
    reg_ls_disable_usb_hs     :  1,    //      1
                              : 30;    //   31:2 reserved
}BMC_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC34E_0090    dbb_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__mcuclk_sel           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg__pll_cgen             :  1,    //      4
                              : 27;    //   31:5 reserved
}BMC_SYN_DBB_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    bmc_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BMC_SYN_CRG_BMC00_O20A0_T                    crg_bmc00                ;         // 0xC34E_0000
BMC_SYN_CRG_BMC01_O20A0_T                    crg_bmc01                ;         // 0xC34E_0004
BMC_SYN_CRG_BMC02_O20A0_T                    crg_bmc02                ;         // 0xC34E_0008
BMC_SYN_CRG_BMC03_O20A0_T                    crg_bmc03                ;         // 0xC34E_000C
BMC_SYN_CRG_BMC04_O20A0_T                    crg_bmc04                ;         // 0xC34E_0010
BMC_SYN_CRG_BMC05_O20A0_T                    crg_bmc05                ;         // 0xC34E_0014
UINT32                                                 _rsvd_00[   1] ;         // 0xC34E_0018
BMC_SYN_CRG_BMC06_O20A0_T                    crg_bmc06                ;         // 0xC34E_001C
BMC_SYN_CRG_BMC07_O20A0_T                    crg_bmc07                ;         // 0xC34E_0020
BMC_SYN_CRG_BMC08_O20A0_T                    crg_bmc08                ;         // 0xC34E_0024
BMC_SYN_CRG_BMC09_O20A0_T                    crg_bmc09                ;         // 0xC34E_0028
BMC_SYN_CRG_BMC11_O20A0_T                    crg_bmc11                ;         // 0xC34E_002C
BMC_SYN_CRG_BMC12_O20A0_T                    crg_bmc12                ;         // 0xC34E_0030
BMC_SYN_CRG_BMC10_O20A0_T                    crg_bmc10                ;         // 0xC34E_0034
BMC_SYN_CRG_BMC13_O20A0_T                    crg_bmc13                ;         // 0xC34E_0038
BMC_SYN_CRG_BMC14_O20A0_T                    crg_bmc14                ;         // 0xC34E_003C
BMC_SYN_CRG_BMC15_O20A0_T                    crg_bmc15                ;         // 0xC34E_0040
BMC_SYN_CRG_BMC16_O20A0_T                    crg_bmc16                ;         // 0xC34E_0044
BMC_SYN_CRG_BMC17_O20A0_T                    crg_bmc17                ;         // 0xC34E_0048
BMC_SYN_CRG_BMC18_O20A0_T                    crg_bmc18                ;         // 0xC34E_004C
BMC_SYN_CRG_BMC19_O20A0_T                    crg_bmc19                ;         // 0xC34E_0050
BMC_SYN_CRG_BMC20_O20A0_T                    crg_bmc20                ;         // 0xC34E_0054
BMC_SYN_CRG_BMC21_O20A0_T                    crg_bmc21                ;         // 0xC34E_0058
BMC_SYN_CRG_BMC22_O20A0_T                    crg_bmc22                ;         // 0xC34E_005C
BMC_SYN_CRG_USB_HS00_O20A0_T                 crg_usb_hs00             ;         // 0xC34E_0060
UINT32                                                 _rsvd_01[   1] ;         // 0xC34E_0064
BMC_SYN_CRG_USB_HS02_O20A0_T                 crg_usb_hs02             ;         // 0xC34E_0068
BMC_SYN_CRG_USB_HS03_O20A0_T                 crg_usb_hs03             ;         // 0xC34E_006C
BMC_SYN_CRG_USB_HS04_O20A0_T                 crg_usb_hs04             ;         // 0xC34E_0070
UINT32                                                 _rsvd_02[   2] ;         // 0xC34E_0074 ~ 0xC34E_0078
BMC_SYN_USB_AXI_00_O20A0_T                   usb_axi_00               ;         // 0xC34E_007C
BMC_SYN_DBB_APB_00_O20A0_T                   dbb_apb_00               ;         // 0xC34E_0080
BMC_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC34E_0084
BMC_SYN_DFT01_O20A0_T                        dft01                    ;         // 0xC34E_0088
BMC_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC34E_008C
BMC_SYN_DBB_CTRL00_O20A0_T                   dbb_ctrl00               ;         // 0xC34E_0090
} BMC_SYN_REG_O20A0_T;
/* 33 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BMC_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

