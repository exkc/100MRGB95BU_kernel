#ifndef _CVI_SYN_O20A0_REG_H_
#define _CVI_SYN_O20A0_REG_H_

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
    0xC930_5000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__apb_clk_gate_en  :  1,    //      0
    reg_cvi__axi_clk_gate_en  :  1,    //      1
    reg_cvi__cvd54_clk_gate_en:  1,    //      2
    reg_cvi__cvi0_clk_gate_en :  1,    //      3
    reg_cvi__cvi1_clk_gate_en :  1,    //      4
    reg_cvi__cvi2_clk_gate_en :  1,    //      5
    reg_cvi__cvi3_clk_gate_en :  1,    //      6
    reg_cvi__de_clk_gate_en   :  1,    //      7
    reg_cvi__cvd27_clk_gate_en:  1,    //      8
    reg_cvi__ch3pix_clk_gate_en: 1,    //      9
    reg_cvi__de_soc_clk_gate_en: 1,    //     10
    reg_cvi__axi_soc_clk_gate_en: 1,    //    11
                              : 20;    //  31:12 reserved
}CVI_SYN_CRG_CVI00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__soft_rst_apb_n   :  1,    //      0
    reg_cvi__soft_rst_axi_n   :  1,    //      1
    reg_cvi__soft_rst_ch3pix_n:  1,    //      2
    reg_cvi__soft_rst_cvd27_n :  1,    //      3
    reg_cvi__soft_rst_cvd_mif_n: 1,    //      4
    reg_cvi__soft_rst_cvi1_n  :  1,    //      5
    reg_cvi__soft_rst_cvi3_n  :  1,    //      6
    reg_cvi__soft_rst_de_n    :  1,    //      7
    reg_cvi__soft_rst_cvd54_n :  1,    //      8
    reg_cvi__soft_rst_cvi0_n  :  1,    //      9
    reg_cvi__soft_rst_axi_sbus_n: 1,    //    10
    reg_cvi__soft_rst_cvi2_n  :  1,    //     11
    reg_cvi__soft_rst_cvd_vbi_n: 1,    //     12
    reg_cvi__soft_rst_axi_bnd_n: 1,    //     13
    reg_cvi__soft_rst_de_bnd_n:  1,    //     14
    reg_cvi__axi_bnd_clk_gate_en: 1,    //    15
    reg_cvi__soft_rst_axi_soc_n: 1,    //     16
    reg_cvi__soft_rst_de_soc_n:  1,    //     17
                              : 14;    //  31:18 reserved
}CVI_SYN_CRG_CVI01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__i_phy1_ppll_clk_inv_sel: 1,    //  0
    reg_cvi__i_phy3_ppll_clk_inv_sel: 1,    //  1
    reg_cvi__i_phy5_ppll_clk_inv_sel: 1,    //  2
    reg_cvi__i_ch3pix_clk_inv_sel: 1,    //    3
    reg_cvi__i_phy2_ppll_clk_inv_sel: 1,    //  4
    reg_cvi__i_cvd54_clk_inv_sel: 1,    //     5
    reg_cvi__i_phy4_ppll_clk_inv_sel: 1,    //  6
                              : 25;    //   31:7 reserved
}CVI_SYN_CRG_CVI02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_500C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__cvi0_clk_sel     :  4,    //   3: 0
    reg_cvi__cvi2_clk_sel     :  4,    //   7: 4
    reg_cvi__cvi1_clk_sel     :  4,    //  11: 8
    reg_cvi__cvi3_clk_sel     :  4,    //  15:12
                              : 16;    //  31:16 reserved
}CVI_SYN_CRG_CVI03_O20A0_T;

typedef struct {
    UINT32
    reg_cvi__cvi0_clk_sel     :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_cvi__cvi2_clk_sel     :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_cvi__cvi1_clk_sel     :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_cvi__cvi3_clk_sel     :  5,    //  28:24
                              :  3;    //  31:29 reserved
}CVI_SYN_CRG_CVI03_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_cvi__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_cvi__crg_clk_off_check:  1,    //     30
    reg_cvi__crg_clk_gate     :  1;    //     31
}CVI_SYN_CRG_CVI04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5014    crg_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__crg_clk_rst_sel  : 32;    //  31: 0
}CVI_SYN_CRG_CVI05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5018    crg_usb_hs06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_hs__usb_bus_clk_gate_en: 1,    //  0
    reg_usb0_hs__usb_clk12mohci_gate_en: 1,    //  1
    reg_usb0_hs__usb_clk48mohci_gate_en: 1,    //  2
    reg_usb0_hs__usb_freeclk_gate_en: 1,    //  3
    reg_usb0_hs__usb_xtal_clk_20m_gate_en: 1,    //  4
    reg_usb0_hs__usb_phy_clock_gate_en: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_501C    crg_usb_hs07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_hs__soft_rst_usb_bus_n: 1,    //  0
    reg_usb0_hs__soft_rst_usb_phy_i_n: 1,    //  1
    reg_usb0_hs__soft_rst_usb_utmi_i_n: 1,    //  2
    reg_usb0_hs__soft_rst_usb_core_i_n: 1,    //  3
    reg_usb0_hs__soft_rst_usb_bus_i_n: 1,    //  4
    reg_usb0_hs__soft_rst_usb_bus_bnd_n: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5020    crg_usb_hs08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_hs__usb_freeclk_sel: 1,    //     0
                              : 31;    //   31:1 reserved
}CVI_SYN_CRG_USB_HS08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5024    crg_usb_hs09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_hs__crg_freq_value: 18,    //  17:0
                              : 10,    //  27:18 reserved
    reg_usb0_hs__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_usb0_hs__crg_clk_off_check: 1,    //  30
    reg_usb0_hs__crg_clk_gate :  1;    //     31
}CVI_SYN_CRG_USB_HS09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5028    crg_usb_hs10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_hs__crg_clk_rst_sel: 32;    //  31:0
}CVI_SYN_CRG_USB_HS10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_502C    crg_usb_hs11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb1_hs__usb_bus_clk_gate_en: 1,    //  0
    reg_usb1_hs__usb_clk12mohci_gate_en: 1,    //  1
    reg_usb1_hs__usb_clk48mohci_gate_en: 1,    //  2
    reg_usb1_hs__usb_freeclk_gate_en: 1,    //  3
    reg_usb1_hs__usb_xtal_clk_20m_gate_en: 1,    //  4
    reg_usb1_hs__usb_phy_clock_gate_en: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5030    crg_usb_hs12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb1_hs__soft_rst_usb_bus_n: 1,    //  0
    reg_usb1_hs__soft_rst_usb_phy_i_n: 1,    //  1
    reg_usb1_hs__soft_rst_usb_utmi_i_n: 1,    //  2
    reg_usb1_hs__soft_rst_usb_core_i_n: 1,    //  3
    reg_usb1_hs__soft_rst_usb_bus_i_n: 1,    //  4
    reg_usb1_hs__soft_rst_usb_bus_bnd_n: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5034    crg_usb_hs13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb1_hs__usb_freeclk_sel: 1,    //     0
                              : 31;    //   31:1 reserved
}CVI_SYN_CRG_USB_HS13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5038    crg_usb_hs14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb1_hs__crg_freq_value: 18,    //  17:0
                              : 10,    //  27:18 reserved
    reg_usb1_hs__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_usb1_hs__crg_clk_off_check: 1,    //  30
    reg_usb1_hs__crg_clk_gate :  1;    //     31
}CVI_SYN_CRG_USB_HS14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_503C    crg_usb_hs15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb1_hs__crg_clk_rst_sel: 32;    //  31:0
}CVI_SYN_CRG_USB_HS15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5040    crg_usb_hs16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb2_hs__usb_bus_clk_gate_en: 1,    //  0
    reg_usb2_hs__usb_clk12mohci_gate_en: 1,    //  1
    reg_usb2_hs__usb_clk48mohci_gate_en: 1,    //  2
    reg_usb2_hs__usb_freeclk_gate_en: 1,    //  3
    reg_usb2_hs__usb_xtal_clk_20m_gate_en: 1,    //  4
    reg_usb2_hs__usb_phy_clock_gate_en: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5044    crg_usb_hs17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb2_hs__soft_rst_usb_bus_n: 1,    //  0
    reg_usb2_hs__soft_rst_usb_phy_i_n: 1,    //  1
    reg_usb2_hs__soft_rst_usb_utmi_i_n: 1,    //  2
    reg_usb2_hs__soft_rst_usb_core_i_n: 1,    //  3
    reg_usb2_hs__soft_rst_usb_bus_i_n: 1,    //  4
    reg_usb2_hs__soft_rst_usb_bus_bnd_n: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_USB_HS17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5048    crg_usb_hs18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb2_hs__usb_freeclk_sel: 1,    //     0
                              : 31;    //   31:1 reserved
}CVI_SYN_CRG_USB_HS18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_504C    crg_usb_hs19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb2_hs__crg_freq_value: 18,    //  17:0
                              : 10,    //  27:18 reserved
    reg_usb2_hs__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_usb2_hs__crg_clk_off_check: 1,    //  30
    reg_usb2_hs__crg_clk_gate :  1;    //     31
}CVI_SYN_CRG_USB_HS19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5050    crg_usb_hs20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb2_hs__crg_clk_rst_sel: 32;    //  31:0
}CVI_SYN_CRG_USB_HS20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5054    crg_usb_drd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_drd__usb_bus_clk_gate_en: 1,    //  0
    reg_usb_drd__usb_ohci_clk48m_gate_en: 1,    //  1
    reg_usb_drd__usb_phyclock_gate_en: 1,    //  2
    reg_usb_drd__usb_phy_xtal_clk_gate_en: 1,    //  3
                              : 28;    //   31:4 reserved
}CVI_SYN_CRG_USB_DRD01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5058    crg_usb_drd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_drd__soft_rst_usb_bus_n: 1,    //  0
    reg_usb_drd__soft_rst_usb_utmi_i_n: 1,    //  1
    reg_usb_drd__soft_rst_usb_bus_i_n: 1,    //  2
    reg_usb_drd__soft_rst_usb_phy_i_n: 1,    //  3
                              : 28;    //   31:4 reserved
}CVI_SYN_CRG_USB_DRD02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_505C    crg_usb_drd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_drd__crg_freq_value: 18,    //  17:0
                              : 10,    //  27:18 reserved
    reg_usb_drd__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_usb_drd__crg_clk_off_check: 1,    //  30
    reg_usb_drd__crg_clk_gate :  1;    //     31
}CVI_SYN_CRG_USB_DRD03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5060    crg_usb_drd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_drd__crg_clk_rst_sel: 32;    //  31:0
}CVI_SYN_CRG_USB_DRD04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5064    crg_dsc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__dsc_hdmirx_tmdspq_clk_gate_en: 1,    //  0
    reg_dsc__fec_enc_clk_gate_en: 1,    //     1
    reg_dsc__dsc_cvi_clk_gate_en: 1,    //     2
    reg_dsc__dsc_clk_gate_en  :  1,    //      3
    reg_dsc__to_cvi__fec_enc_clk_gate_en: 1,    //  4
    reg_dsc__to_cvi__dsc_cvi_clk_gate_en: 1,    //  5
    reg_dsc__dsc_apb_clk_gate_en: 1,    //     6
                              : 25;    //   31:7 reserved
}CVI_SYN_CRG_DSC15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5068    crg_dsc16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__soft_rst_dsc_apb_n: 1,    //      0
    reg_dsc__soft_rst_dsc_cvi_n: 1,    //      1
    reg_dsc__soft_rst_hdmirx_tsdspq_n: 1,    //  2
    reg_dsc__soft_rst_dsc_cvi_apb_n: 1,    //  3
    reg_dsc__soft_rst_fec_enc_n: 1,    //      4
    reg_dsc__soft_rst_to_cvi_fec_enc_n: 1,    //  5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_DSC16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_506C    crg_dsc17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__i_hdmirx_prt1_tmdsqp_clk_inv_sel: 1,    //  0
    reg_dsc__i_hdmirx_prt3_tmdsqp_clk_inv_sel: 1,    //  1
    reg_dsc__i_hdmirx_prt5_tmdsqp_clk_inv_sel: 1,    //  2
    reg_dsc__i_hdmirx_prt2_tmdsqp_clk_inv_sel: 1,    //  3
    reg_dsc__i_hdmirx_prt4_tmdsqp_clk_inv_sel: 1,    //  4
    reg_dsc__hdmirx_prt0_tmdsqp_bnd_clk_gate_en: 1,    //  5
    reg_dsc__hdmirx_prt1_tmdsqp_bnd_clk_gate_en: 1,    //  6
    reg_dsc__hdmirx_prt2_tmdsqp_bnd_clk_gate_en: 1,    //  7
    reg_dsc__hdmirx_prt3_tmdsqp_bnd_clk_gate_en: 1,    //  8
    reg_dsc__hdmirx_prt4_tmdsqp_bnd_clk_gate_en: 1,    //  9
    reg_dsc__soft_rst_hdmirx_prt0_tmdsqp_bnd_n: 1,    //  10
    reg_dsc__soft_rst_hdmirx_prt1_tmdsqp_bnd_n: 1,    //  11
    reg_dsc__soft_rst_hdmirx_prt2_tmdsqp_bnd_n: 1,    //  12
    reg_dsc__soft_rst_hdmirx_prt3_tmdsqp_bnd_n: 1,    //  13
    reg_dsc__soft_rst_hdmirx_prt4_tmdsqp_bnd_n: 1,    //  14
    reg_dsc__soft_rst_hdmirx_tmdsqp_n: 1,    //  15
    reg_dsc__soft_rst_fec_enc_bnd_n: 1,    //  16
                              : 15;    //  31:17 reserved
}CVI_SYN_CRG_DSC17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5070    crg_dsc18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__dsc_hdmirx_tsdspq_clk_sel: 3,    //  2:0
    reg_dsc__dsc_cvi_clk_sel  :  2,    //   4: 3
    reg_dsc__to_cvi__fec_enc_clk_sel: 1,    //  5
    reg_dsc__fec_enc_clk_sel  :  1,    //      6
    reg_dsc__to_cvi__dsc_cvi_clk_sel: 2,    //  8:7
    reg_dsc__dsc_clk_sel      :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}CVI_SYN_CRG_DSC18_O20A0_T;

typedef struct {
    UINT32
    reg_dsc__dsc_hdmirx_tsdspq_clk_sel: 3,    //  2:0
                              :  1,    //      3 reserved
    reg_dsc__dsc_cvi_clk_sel  :  1,    //      4
    reg_dsc__to_cvi__fec_enc_clk_sel: 1,    //  5
    reg_dsc__fec_enc_clk_sel  :  1,    //      6
    reg_dsc__to_cvi__dsc_cvi_clk_sel: 2,    //  8:7
    reg_dsc__dsc_clk_sel      :  2,    //  10: 9
                              :  1,    //     11 reserved
    reg_dsc__dsc_apb_clk_sel  :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CVI_SYN_CRG_DSC18_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5074    crg_dsc19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_dsc__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_dsc__crg_clk_off_check:  1,    //     30
    reg_dsc__crg_clk_gate     :  1;    //     31
}CVI_SYN_CRG_DSC19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5078    crg_dsc20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc__crg_clk_rst_sel  : 32;    //  31: 0
}CVI_SYN_CRG_DSC20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_507C    crg_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cvi_ctrl          : 32;    //  31: 0
}CVI_SYN_CRG_CVI06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5080    usb_axi_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb0_axi_addr_33      :  1,    //      0
    reg_usb1_axi_addr_33      :  1,    //      1
    reg_usb2_axi_addr_33      :  1,    //      2
    reg_usb_drd_axi_addr_33   :  1,    //      3
                              : 28;    //   31:4 reserved
}CVI_SYN_USB_AXI_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5084    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_dsc  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_cvi  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CVI_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5088    crg_clk_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core800_clk_ctrl_dsc  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core600_clk_ctrl_dsc  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CVI_SYN_CRG_CLK_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_508C    crg_clk_ctrl03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_usb2_hs: 9,    //  8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_usb_drd: 9,    //  24:16
                              :  7;    //  31:25 reserved
}CVI_SYN_CRG_CLK_CTRL03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5090    crg_clk_ctrl04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_usb0_hs: 9,    //  8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_usb1_hs: 9,    //  24:16
                              :  7;    //  31:25 reserved
}CVI_SYN_CRG_CLK_CTRL04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5094    adapter_ctr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmirx_prt4_de_combined   :  1,    //      0
    reg__swrst_hdmirx_prt4    :  1,    //      1
    hdmirx_prt3_de_combined   :  1,    //      2
    reg__swrst_hdmirx_prt3    :  1,    //      3
    hdmirx_prt2_de_combined   :  1,    //      4
    reg__swrst_hdmirx_prt2    :  1,    //      5
    hdmirx_prt1_de_combined   :  1,    //      6
    reg__swrst_hdmirx_prt1    :  1,    //      7
    hdmirx_prt0_de_combined   :  1,    //      8
    reg__swrst_hdmirx_prt0    :  1,    //      9
                              : 22;    //  31:10 reserved
}CVI_SYN_ADAPTER_CTR00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_5098    dft01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb_hs_0_bist_error       :  1,    //      0
    usb_hs_0_bist_done        :  1,    //      1
    usb_hs_1_bist_error       :  1,    //      2
    usb_hs_1_bist_done        :  1,    //      3
    usb_hs_2_bist_error       :  1,    //      4
    usb_hs_2_bist_done        :  1,    //      5
    usb_drd_bist_error        :  1,    //      6
    usb_drd_bist_done         :  1,    //      7
                              : 24;    //   31:8 reserved
}CVI_SYN_DFT01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_509C    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_cvi        :  1,    //      0
    reg_ls_disable_usb        :  1,    //      1
    reg_ls_disable_dsc        :  1,    //      2
                              : 29;    //   31:3 reserved
}CVI_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_50A0    dsc_tcon_detour_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_dsc_tcon_detour:  1,    //      0
                              : 31;    //   31:1 reserved
}CVI_SYN_DSC_TCON_DETOUR_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_50A4    rgmii_rs ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rgmii_tx_rs_bypass    :  1,    //      0
    reg_rgmii_rx_rs_bypass    :  1,    //      1
                              : 30;    //   31:2 reserved
}CVI_SYN_RGMII_RS_O20B0_T;

/*-----------------------------------------------------------------------------------------
    cvi_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CVI_SYN_CRG_CVI00_O20A0_T                    crg_cvi00                ;         // 0xC930_5000
CVI_SYN_CRG_CVI01_O20A0_T                    crg_cvi01                ;         // 0xC930_5004
CVI_SYN_CRG_CVI02_O20A0_T                    crg_cvi02                ;         // 0xC930_5008
union {
CVI_SYN_CRG_CVI03_O20A0_T                    crg_cvi03                ;         // 0xC930_500C
CVI_SYN_CRG_CVI03_O20B0_T                    crg_cvi03_B0             ;         // 0xC930_500C
};
CVI_SYN_CRG_CVI04_O20A0_T                    crg_cvi04                ;         // 0xC930_5010
CVI_SYN_CRG_CVI05_O20A0_T                    crg_cvi05                ;         // 0xC930_5014
CVI_SYN_CRG_USB_HS06_O20A0_T                 crg_usb_hs06             ;         // 0xC930_5018
CVI_SYN_CRG_USB_HS07_O20A0_T                 crg_usb_hs07             ;         // 0xC930_501C
CVI_SYN_CRG_USB_HS08_O20A0_T                 crg_usb_hs08             ;         // 0xC930_5020
CVI_SYN_CRG_USB_HS09_O20A0_T                 crg_usb_hs09             ;         // 0xC930_5024
CVI_SYN_CRG_USB_HS10_O20A0_T                 crg_usb_hs10             ;         // 0xC930_5028
CVI_SYN_CRG_USB_HS11_O20A0_T                 crg_usb_hs11             ;         // 0xC930_502C
CVI_SYN_CRG_USB_HS12_O20A0_T                 crg_usb_hs12             ;         // 0xC930_5030
CVI_SYN_CRG_USB_HS13_O20A0_T                 crg_usb_hs13             ;         // 0xC930_5034
CVI_SYN_CRG_USB_HS14_O20A0_T                 crg_usb_hs14             ;         // 0xC930_5038
CVI_SYN_CRG_USB_HS15_O20A0_T                 crg_usb_hs15             ;         // 0xC930_503C
CVI_SYN_CRG_USB_HS16_O20A0_T                 crg_usb_hs16             ;         // 0xC930_5040
CVI_SYN_CRG_USB_HS17_O20A0_T                 crg_usb_hs17             ;         // 0xC930_5044
CVI_SYN_CRG_USB_HS18_O20A0_T                 crg_usb_hs18             ;         // 0xC930_5048
CVI_SYN_CRG_USB_HS19_O20A0_T                 crg_usb_hs19             ;         // 0xC930_504C
CVI_SYN_CRG_USB_HS20_O20A0_T                 crg_usb_hs20             ;         // 0xC930_5050
CVI_SYN_CRG_USB_DRD01_O20A0_T                crg_usb_drd01            ;         // 0xC930_5054
CVI_SYN_CRG_USB_DRD02_O20A0_T                crg_usb_drd02            ;         // 0xC930_5058
CVI_SYN_CRG_USB_DRD03_O20A0_T                crg_usb_drd03            ;         // 0xC930_505C
CVI_SYN_CRG_USB_DRD04_O20A0_T                crg_usb_drd04            ;         // 0xC930_5060
CVI_SYN_CRG_DSC15_O20A0_T                    crg_dsc15                ;         // 0xC930_5064
CVI_SYN_CRG_DSC16_O20A0_T                    crg_dsc16                ;         // 0xC930_5068
CVI_SYN_CRG_DSC17_O20A0_T                    crg_dsc17                ;         // 0xC930_506C
union {
CVI_SYN_CRG_DSC18_O20A0_T                    crg_dsc18                ;         // 0xC930_5070
CVI_SYN_CRG_DSC18_O20B0_T                    crg_dsc18_B0             ;         // 0xC930_5070
};
CVI_SYN_CRG_DSC19_O20A0_T                    crg_dsc19                ;         // 0xC930_5074
CVI_SYN_CRG_DSC20_O20A0_T                    crg_dsc20                ;         // 0xC930_5078
CVI_SYN_CRG_CVI06_O20A0_T                    crg_cvi06                ;         // 0xC930_507C
CVI_SYN_USB_AXI_00_O20A0_T                   usb_axi_00               ;         // 0xC930_5080
CVI_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC930_5084
CVI_SYN_CRG_CLK_CTRL02_O20A0_T               crg_clk_ctrl02           ;         // 0xC930_5088
CVI_SYN_CRG_CLK_CTRL03_O20A0_T               crg_clk_ctrl03           ;         // 0xC930_508C
CVI_SYN_CRG_CLK_CTRL04_O20A0_T               crg_clk_ctrl04           ;         // 0xC930_5090
CVI_SYN_ADAPTER_CTR00_O20A0_T                adapter_ctr00            ;         // 0xC930_5094
CVI_SYN_DFT01_O20A0_T                        dft01                    ;         // 0xC930_5098
CVI_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC930_509C
CVI_SYN_DSC_TCON_DETOUR_00_O20A0_T           dsc_tcon_detour_00       ;         // 0xC930_50A0
CVI_SYN_RGMII_RS_O20B0_T                     rgmii_rs_B0              ;         // 0xC930_50A4
} CVI_SYN_REG_O20A0_T;
/* 41 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CVI_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

