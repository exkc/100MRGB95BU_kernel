#ifndef _CVI_SYN_M19A0_REG_H_
#define _CVI_SYN_M19A0_REG_H_

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
    0xC930_2000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvd_cvi3_clk_gate_en      :  1,    //      0
    cvd_cvi2_clk_gate_en      :  1,    //      1
    cvd_cvi1_clk_gate_en      :  1,    //      2
    cvd_cvi0_clk_gate_en      :  1,    //      3
    cvd27_clk_gate_en         :  1,    //      4
    cvd54_clk_gate_en         :  1,    //      5
    ch3pix_clk_gate_en        :  1,    //      6
    hdmi3_link_clk_gate_en    :  1,    //      7
    hdmi2_link_clk_gate_en    :  1,    //      8
    hdmi1_link_clk_gate_en    :  1,    //      9
    hdmi0_link_clk_gate_en    :  1,    //     10
    axi_clk_gate_en           :  1,    //     11
    de_clk_gate_en            :  1,    //     12
    apb_clk_gate_en           :  1,    //     13
    axi_soc_clk_gate_en       :  1,    //     14
                              : 17;    //  31:15 reserved
}CVI_SYN_CRG_CVI00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvd_cvi0_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    cvd_cvi1_clk_sel          :  3,    //   6: 4
                              :  1,    //      7 reserved
    cvd_cvi2_clk_sel          :  3,    //  10: 8
                              :  1,    //     11 reserved
    cvd_cvi3_clk_sel          :  3,    //  14:12
                              :  1,    //     15 reserved
    hdmi0_link_clk_sel        :  2,    //  17:16
    hdmi1_link_clk_sel        :  2,    //  19:18
    hdmi2_link_clk_sel        :  2,    //  21:20
    hdmi3_link_clk_sel        :  2,    //  23:22
                              :  2,    //  25:24 reserved
    disp594_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}CVI_SYN_CRG_CVI01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_phy1_ppll_clk_inv_sel   :  1,    //      0
    i_phy2_ppll_clk_inv_sel   :  1,    //      1
    i_phy3_ppll_clk_inv_sel   :  1,    //      2
    i_phy4_ppll_clk_inv_sel   :  1,    //      3
    i_ch3pix_clk_inv_sel      :  1,    //      4
    i_cvd54_clk_inv_sel       :  1,    //      5
                              : 26;    //   31:6 reserved
}CVI_SYN_CRG_CVI02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_200C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_de_bnd_n         :  1,    //      0
    soft_rst_axi_bnd_n        :  1,    //      1
    soft_rst_axi_soc_n        :  1,    //      2
    soft_rst_axi_sub_n        :  1,    //      3
    soft_rst_cvd_mif_n        :  1,    //      4
    soft_rst_cvd_vbi_n        :  1,    //      5
    soft_rst_cvi3_n           :  1,    //      6
    soft_rst_cvi2_n           :  1,    //      7
    soft_rst_cvi1_n           :  1,    //      8
    soft_rst_cvi0_n           :  1,    //      9
    soft_rst_cvd27_n          :  1,    //     10
    soft_rst_cvd54_n          :  1,    //     11
    soft_rst_ch3pix_n         :  1,    //     12
    soft_rst_hdmi3_n          :  1,    //     13
    soft_rst_hdmi2_n          :  1,    //     14
    soft_rst_hdmi1_n          :  1,    //     15
    soft_rst_hdmi0_n          :  1,    //     16
    soft_rst_axi_n            :  1,    //     17
    soft_rst_de_n             :  1,    //     18
    soft_rst_apb_n            :  1,    //     19
                              : 12;    //  31:20 reserved
}CVI_SYN_CRG_CVI03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2010    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy_i2c_clk_gate_en       :  1,    //      0
    hdmirx_prt3_tmdsrx_v_clk_gate_en: 1,    //  1
    hdmirx_prt3_tmdsrx_p_clk_gate_en: 1,    //  2
    hdmirx_prt3_tmdsrx_clk_gate_en: 1,    //   3
    hdmirx_prt3_pixfifo_wclk_gate_en: 1,    //  4
    hdmirx_prt3_phy_tmdsrx_ref_clk_gate_en: 1,    //  5
    hdmirx_prt2_tmdsrx_v_clk_gate_en: 1,    //  6
    hdmirx_prt2_tmdsrx_p_clk_gate_en: 1,    //  7
    hdmirx_prt2_tmdsrx_clk_gate_en: 1,    //   8
    hdmirx_prt2_pixfifo_wclk_gate_en: 1,    //  9
    hdmirx_prt2_phy_tmdsrx_ref_clk_gate_en: 1,    //  10
    hdmirx_prt1_tmdsrx_v_clk_gate_en: 1,    //  11
    hdmirx_prt1_tmdsrx_p_clk_gate_en: 1,    //  12
    hdmirx_prt1_tmdsrx_clk_gate_en: 1,    //  13
    hdmirx_prt1_pixfifo_wclk_gate_en: 1,    //  14
    hdmirx_prt1_phy_tmdsrx_ref_clk_gate_en: 1,    //  15
    hdmirx_prt0_tmdsrx_v_clk_gate_en: 1,    //  16
    hdmirx_prt0_tmdsrx_p_clk_gate_en: 1,    //  17
    hdmirx_prt0_tmdsrx_clk_gate_en: 1,    //  18
    hdmirx_prt0_pixfifo_wclk_gate_en: 1,    //  19
    hdmirx_prt0_phy_tmdsrx_ref_clk_gate_en: 1,    //  20
                              :  1,    //     21 reserved
    hdmirx_comm_sapb_clk_gate_en: 1,    //    22
    hdmirx_comm_imodet_clk_gate_en: 1,    //  23
    hdmirx_comm_icec_clk_gate_en: 1,    //    24
    hdmirx_comm_iapb_clk_gate_en: 1,    //    25
    hdmirx_comm_esm_clk_gate_en: 1,    //     26
                              :  1,    //     27 reserved
    hdmirx_comm_edid_clk_gate_en: 1,    //    28
                              :  3;    //  31:29 reserved
}CVI_SYN_CRG_HDMI00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2014    syn_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmirx_prt3_pixfifo_wclk_sel: 2,    //  1: 0
                              :  2,    //   3: 2 reserved
    hdmirx_prt2_pixfifo_wclk_sel: 2,    //  5: 4
                              :  2,    //   7: 6 reserved
    hdmirx_prt1_pixfifo_wclk_sel: 2,    //  9: 8
                              :  2,    //  11:10 reserved
    hdmirx_prt0_pixfifo_wclk_sel: 2,    //  13:12
                              :  2,    //  15:14 reserved
    hdmirx_prt3_tmdsrx_clk_sel:  2,    //  17:16
    hdmirx_prt2_tmdsrx_clk_sel:  2,    //  19:18
    hdmirx_prt1_tmdsrx_clk_sel:  2,    //  21:20
    hdmirx_prt0_tmdsrx_clk_sel:  2,    //  23:22
    phy_i2c_clk_sel           :  1,    //     24
    hdmirx_comm_sapb_clk_sel  :  1,    //     25
    hdmirx_comm_edid_clk_sel  :  1,    //     26
                              :  5;    //  31:27 reserved
}CVI_SYN_SYN_HDMI01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2018    syn_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy3_tmds_rx_ref_clk_inv_sel: 1,    //     0
    phy3_tmds_rx_clk_inv_sel  :  1,    //      1
    phy3_pixfifo_wclk_inv_sel :  1,    //      2
    phy2_tmds_rx_ref_clk_inv_sel: 1,    //     3
    phy2_tmds_rx_clk_inv_sel  :  1,    //      4
    phy2_pixfifo_wclk_inv_sel :  1,    //      5
    phy1_tmds_rx_ref_clk_inv_sel: 1,    //     6
    phy1_tmds_rx_clk_inv_sel  :  1,    //      7
    phy1_pixfifo_wclk_inv_sel :  1,    //      8
    phy0_tmds_rx_ref_clk_inv_sel: 1,    //     9
    phy0_tmds_rx_clk_inv_sel  :  1,    //     10
    phy0_pixfifo_wclk_inv_sel :  1,    //     11
                              : 20;    //  31:12 reserved
}CVI_SYN_SYN_HDMI02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_201C    syn_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_hdmirx_prt1_skp_rst_n:  1,    //      0
    soft_hdmirx_prt1_sapb_rst_n: 1,    //      1
    soft_hdmirx_prt1_phy_pixfifo_rst_n: 1,    //  2
    soft_hdmirx_prt1_phy_hdmirx_ref_rst_n: 1,    //  3
    soft_hdmirx_prt1_main_rst_n: 1,    //      4
    soft_hdmirx_prt1_icec_rst_n: 1,    //      5
    soft_hdmirx_prt1_iapb_top_rst_n: 1,    //  6
    soft_hdmirx_prt1_iapb_rst_n: 1,    //      7
    soft_hdmirx_prt1_iapb_hdmi_rst_n: 1,    //  8
    soft_hdmirx_prt1_iapb_crc_rst_n: 1,    //  9
    soft_hdmirx_prt1_esm_rst_n:  1,    //     10
    soft_hdmirx_prt1_edid_rst_n: 1,    //     11
    soft_hdmirx_prt1_base_rst_n: 1,    //     12
    soft_hdmirx_prt0_skp_rst_n:  1,    //     13
    soft_hdmirx_prt0_sapb_rst_n: 1,    //     14
    soft_hdmirx_prt0_phy_pixfifo_rst_n: 1,    //  15
    soft_hdmirx_prt0_phy_hdmirx_ref_rst_n: 1,    //  16
    soft_hdmirx_prt0_main_rst_n: 1,    //     17
    soft_hdmirx_prt0_icec_rst_n: 1,    //     18
    soft_hdmirx_prt0_iapb_top_rst_n: 1,    //  19
    soft_hdmirx_prt0_iapb_rst_n: 1,    //     20
    soft_hdmirx_prt0_iapb_hdmi_rst_n: 1,    //  21
    soft_hdmirx_prt0_iapb_crc_rst_n: 1,    //  22
    soft_hdmirx_prt0_esm_rst_n:  1,    //     23
    soft_hdmirx_prt0_edid_rst_n: 1,    //     24
    soft_hdmirx_prt0_base_rst_n: 1,    //     25
                              :  6;    //  31:26 reserved
}CVI_SYN_SYN_HDMI03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2020    syn_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_hdmirx_prt3_skp_rst_n:  1,    //      0
    soft_hdmirx_prt3_sapb_rst_n: 1,    //      1
    soft_hdmirx_prt3_phy_pixfifo_rst_n: 1,    //  2
    soft_hdmirx_prt3_phy_hdmirx_ref_rst_n: 1,    //  3
    soft_hdmirx_prt3_main_rst_n: 1,    //      4
    soft_hdmirx_prt3_icec_rst_n: 1,    //      5
    soft_hdmirx_prt3_iapb_top_rst_n: 1,    //  6
    soft_hdmirx_prt3_iapb_rst_n: 1,    //      7
    soft_hdmirx_prt3_iapb_hdmi_rst_n: 1,    //  8
    soft_hdmirx_prt3_iapb_crc_rst_n: 1,    //  9
    soft_hdmirx_prt3_esm_rst_n:  1,    //     10
    soft_hdmirx_prt3_edid_rst_n: 1,    //     11
    soft_hdmirx_prt3_base_rst_n: 1,    //     12
    soft_hdmirx_prt2_skp_rst_n:  1,    //     13
    soft_hdmirx_prt2_sapb_rst_n: 1,    //     14
    soft_hdmirx_prt2_phy_pixfifo_rst_n: 1,    //  15
    soft_hdmirx_prt2_phy_hdmirx_ref_rst_n: 1,    //  16
    soft_hdmirx_prt2_main_rst_n: 1,    //     17
    soft_hdmirx_prt2_icec_rst_n: 1,    //     18
    soft_hdmirx_prt2_iapb_top_rst_n: 1,    //  19
    soft_hdmirx_prt2_iapb_rst_n: 1,    //     20
    soft_hdmirx_prt2_iapb_hdmi_rst_n: 1,    //  21
    soft_hdmirx_prt2_iapb_crc_rst_n: 1,    //  22
    soft_hdmirx_prt2_esm_rst_n:  1,    //     23
    soft_hdmirx_prt2_edid_rst_n: 1,    //     24
    soft_hdmirx_prt2_base_rst_n: 1,    //     25
                              :  6;    //  31:26 reserved
}CVI_SYN_SYN_HDMI04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2024    syn_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_hdmirx_bus_rst_n     :  1,    //      0
    soft_rst_prt3_tmdsrx_v_n  :  1,    //      1
    soft_rst_prt3_tmdsrx_p_n  :  1,    //      2
    soft_rst_prt2_tmdsrx_v_n  :  1,    //      3
    soft_rst_prt2_tmdsrx_p_n  :  1,    //      4
    soft_rst_prt1_tmdsrx_v_n  :  1,    //      5
    soft_rst_prt1_tmdsrx_p_n  :  1,    //      6
    soft_rst_prt0_tmdsrx_v_n  :  1,    //      7
    soft_rst_prt0_tmdsrx_p_n  :  1,    //      8
    soft_reset_acrn_0         :  1,    //      9
    soft_reset_acrn_1         :  1,    //     10
    soft_reset_acrn_2         :  1,    //     11
    soft_reset_acrn_3         :  1,    //     12
                              : 19;    //  31:13 reserved
}CVI_SYN_SYN_HDMI05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2028    a_crg_check_cvi_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk0_value            : 16,    //  15: 0
    cvi_rst0_check            :  1,    //     16
    cvi_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk0_off_value        :  8,    //  27:20
    cvi_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk0_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_202C    a_crg_check_cvi_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk1_value            : 16,    //  15: 0
    cvi_rst1_check            :  1,    //     16
    cvi_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk1_off_value        :  8,    //  27:20
    cvi_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk1_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2030    a_crg_check_cvi_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk2_value            : 16,    //  15: 0
    cvi_rst2_check            :  1,    //     16
    cvi_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk2_off_value        :  8,    //  27:20
    cvi_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk2_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2034    a_crg_check_cvi_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk3_value            : 16,    //  15: 0
    cvi_rst3_check            :  1,    //     16
    cvi_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk3_off_value        :  8,    //  27:20
    cvi_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk3_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2038    a_crg_check_cvi_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk4_value            : 16,    //  15: 0
    cvi_rst4_check            :  1,    //     16
    cvi_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk4_off_value        :  8,    //  27:20
    cvi_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk4_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_203C    a_crg_check_cvi_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk5_value            : 16,    //  15: 0
    cvi_rst5_check            :  1,    //     16
    cvi_clk5_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk5_off_value        :  8,    //  27:20
    cvi_clk5_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk5_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2040    a_crg_check_cvi_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk6_value            : 16,    //  15: 0
    cvi_rst6_check            :  1,    //     16
    cvi_clk6_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk6_off_value        :  8,    //  27:20
    cvi_clk6_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk6_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2044    a_crg_check_cvi_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk7_value            : 16,    //  15: 0
    cvi_rst7_check            :  1,    //     16
    cvi_clk7_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk7_off_value        :  8,    //  27:20
    cvi_clk7_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk7_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_7_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2048    a_crg_check_cvi_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk8_value            : 16,    //  15: 0
    cvi_rst8_check            :  1,    //     16
    cvi_clk8_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk8_off_value        :  8,    //  27:20
    cvi_clk8_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk8_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_8_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_204C    a_crg_check_cvi_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk9_value            : 16,    //  15: 0
    cvi_rst9_check            :  1,    //     16
    cvi_clk9_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk9_off_value        :  8,    //  27:20
    cvi_clk9_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk9_gate             :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_9_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2050    a_crg_check_cvi_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk10_value           : 16,    //  15: 0
    cvi_rst10_check           :  1,    //     16
    cvi_clk10_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk10_off_value       :  8,    //  27:20
    cvi_clk10_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk10_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2054    a_crg_check_cvi_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk11_value           : 16,    //  15: 0
    cvi_rst11_check           :  1,    //     16
    cvi_clk11_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk11_off_value       :  8,    //  27:20
    cvi_clk11_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk11_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2058    a_crg_check_cvi_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk12_value           : 16,    //  15: 0
    cvi_rst12_check           :  1,    //     16
    cvi_clk12_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk12_off_value       :  8,    //  27:20
    cvi_clk12_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk12_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_205C    a_crg_check_cvi_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk13_value           : 16,    //  15: 0
    cvi_rst13_check           :  1,    //     16
    cvi_clk13_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk13_off_value       :  8,    //  27:20
    cvi_clk13_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk13_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2060    a_crg_check_cvi_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk14_value           : 16,    //  15: 0
    cvi_rst14_check           :  1,    //     16
    cvi_clk14_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk14_off_value       :  8,    //  27:20
    cvi_clk14_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk14_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2064    a_crg_check_cvi_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk15_value           : 16,    //  15: 0
    cvi_rst15_check           :  1,    //     16
    cvi_clk15_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk15_off_value       :  8,    //  27:20
    cvi_clk15_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk15_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2068    a_crg_check_cvi_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk16_value           : 16,    //  15: 0
    cvi_rst16_check           :  1,    //     16
    cvi_clk16_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk16_off_value       :  8,    //  27:20
    cvi_clk16_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk16_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_206C    a_crg_check_cvi_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk17_value           : 16,    //  15: 0
    cvi_rst17_check           :  1,    //     16
    cvi_clk17_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk17_off_value       :  8,    //  27:20
    cvi_clk17_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk17_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2070    a_crg_check_cvi_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk18_value           : 16,    //  15: 0
    cvi_rst18_check           :  1,    //     16
    cvi_clk18_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk18_off_value       :  8,    //  27:20
    cvi_clk18_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk18_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_18_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2074    a_crg_check_cvi_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk19_value           : 16,    //  15: 0
    cvi_rst19_check           :  1,    //     16
    cvi_clk19_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk19_off_value       :  8,    //  27:20
    cvi_clk19_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk19_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_19_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2078    a_crg_check_cvi_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk20_value           : 16,    //  15: 0
    cvi_rst20_check           :  1,    //     16
    cvi_clk20_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk20_off_value       :  8,    //  27:20
    cvi_clk20_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk20_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_20_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_207C    a_crg_check_cvi_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk21_value           : 16,    //  15: 0
    cvi_rst21_check           :  1,    //     16
    cvi_clk21_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk21_off_value       :  8,    //  27:20
    cvi_clk21_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk21_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_21_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2080    a_crg_check_cvi_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk22_value           : 16,    //  15: 0
    cvi_rst22_check           :  1,    //     16
    cvi_clk22_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk22_off_value       :  8,    //  27:20
    cvi_clk22_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk22_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_22_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2084    a_crg_check_cvi_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk23_value           : 16,    //  15: 0
    cvi_rst23_check           :  1,    //     16
    cvi_clk23_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk23_off_value       :  8,    //  27:20
    cvi_clk23_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk23_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_23_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2088    a_crg_check_cvi_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk24_value           : 16,    //  15: 0
    cvi_rst24_check           :  1,    //     16
    cvi_clk24_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk24_off_value       :  8,    //  27:20
    cvi_clk24_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk24_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_24_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_208C    a_crg_check_cvi_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi_clk25_value           : 16,    //  15: 0
    cvi_rst25_check           :  1,    //     16
    cvi_clk25_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    cvi_clk25_off_value       :  8,    //  27:20
    cvi_clk25_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    cvi_clk25_gate            :  1;    //     31
}CVI_SYN_A_CRG_CHECK_CVI_25_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2090    syn_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_i2c_en           :  1,    //      0
                              :  3,    //   3: 1 reserved
    regmod_hdmi20rx_h         :  1,    //      4
                              :  3,    //   7: 5 reserved
    uart_ctrl                 :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}CVI_SYN_SYN_HDMI06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2094    syn_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cvi_ctrl          : 32;    //  31: 0
}CVI_SYN_SYN_CVI00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_2098    syn_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    arcache_cvd               :  1,    //      0
    awcache_cvd               :  1,    //      1
    flush_en_cvd              :  1,    //      2
    arcache_hdmi3             :  1,    //      3
    awcache_hdmi3             :  1,    //      4
    flush_en_hdmi3            :  1,    //      5
    arcache_hdmi2             :  1,    //      6
    awcache_hdmi2             :  1,    //      7
    flush_en_hdmi2            :  1,    //      8
    arcache_hdmi1             :  1,    //      9
    awcache_hdmi1             :  1,    //     10
    flush_en_hdmi1            :  1,    //     11
    arcache_hdmi0             :  1,    //     12
    awcache_hdmi0             :  1,    //     13
    flush_en_hdmi0            :  1,    //     14
                              :  1,    //     15 reserved
    flush_done_cvd            :  1,    //     16
    flush_done_hdmi3          :  1,    //     17
    flush_done_hdmi2          :  1,    //     18
    flush_done_hdmi1          :  1,    //     19
    flush_done_hdmi0          :  1,    //     20
                              : 11;    //  31:21 reserved
}CVI_SYN_SYN_CVI01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_209C    syn_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bus_access_gating_cvd_aw  :  1,    //      0
    bus_access_gating_cvd_ar  :  1,    //      1
    bus_access_gating_hdmi3_aw:  1,    //      2
    bus_access_gating_hdmi3_ar:  1,    //      3
    bus_access_gating_hdmi2_aw:  1,    //      4
    bus_access_gating_hdmi2_ar:  1,    //      5
    bus_access_gating_hdmi1_aw:  1,    //      6
    bus_access_gating_hdmi1_ar:  1,    //      7
    bus_access_gating_hdmi0_aw:  1,    //      8
    bus_access_gating_hdmi0_ar:  1,    //      9
                              :  6,    //  15:10 reserved
    cvd_w_ag                  :  1,    //     16
    cvd_aw_ag                 :  1,    //     17
    cvd_ar_ag                 :  1,    //     18
    hdmi3_w_ag                :  1,    //     19
    hdmi3_aw_ag               :  1,    //     20
    hdmi3_ar_ag               :  1,    //     21
    hdmi2_w_ag                :  1,    //     22
    hdmi2_aw_ag               :  1,    //     23
    hdmi2_ar_ag               :  1,    //     24
    hdmi1_w_ag                :  1,    //     25
    hdmi1_aw_ag               :  1,    //     26
    hdmi1_ar_ag               :  1,    //     27
    hdmi0_w_ag                :  1,    //     28
    hdmi0_aw_ag               :  1,    //     29
    hdmi0_ar_ag               :  1,    //     30
                              :  1;    //  31:31 reserved
}CVI_SYN_SYN_CVI02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_20A0    syn_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}CVI_SYN_SYN_CVI03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_20A4    syn_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}CVI_SYN_SYN_CVI04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_20A8    syn_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_cvi        :  1,    //      0
    reg_ls_disable_link       :  1,    //      1
                              : 30;    //   31:2 reserved
}CVI_SYN_SYN_CVI05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    cvi_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CVI_SYN_CRG_CVI00_M19A0_T                    crg_cvi00                ;         // 0xC930_2000
CVI_SYN_CRG_CVI01_M19A0_T                    crg_cvi01                ;         // 0xC930_2004
CVI_SYN_CRG_CVI02_M19A0_T                    crg_cvi02                ;         // 0xC930_2008
CVI_SYN_CRG_CVI03_M19A0_T                    crg_cvi03                ;         // 0xC930_200C
CVI_SYN_CRG_HDMI00_M19A0_T                   crg_hdmi00               ;         // 0xC930_2010
CVI_SYN_SYN_HDMI01_M19A0_T                   syn_hdmi01               ;         // 0xC930_2014
CVI_SYN_SYN_HDMI02_M19A0_T                   syn_hdmi02               ;         // 0xC930_2018
CVI_SYN_SYN_HDMI03_M19A0_T                   syn_hdmi03               ;         // 0xC930_201C
CVI_SYN_SYN_HDMI04_M19A0_T                   syn_hdmi04               ;         // 0xC930_2020
CVI_SYN_SYN_HDMI05_M19A0_T                   syn_hdmi05               ;         // 0xC930_2024
CVI_SYN_A_CRG_CHECK_CVI_0_M19A0_T            a_crg_check_cvi_0        ;         // 0xC930_2028
CVI_SYN_A_CRG_CHECK_CVI_1_M19A0_T            a_crg_check_cvi_1        ;         // 0xC930_202C
CVI_SYN_A_CRG_CHECK_CVI_2_M19A0_T            a_crg_check_cvi_2        ;         // 0xC930_2030
CVI_SYN_A_CRG_CHECK_CVI_3_M19A0_T            a_crg_check_cvi_3        ;         // 0xC930_2034
CVI_SYN_A_CRG_CHECK_CVI_4_M19A0_T            a_crg_check_cvi_4        ;         // 0xC930_2038
CVI_SYN_A_CRG_CHECK_CVI_5_M19A0_T            a_crg_check_cvi_5        ;         // 0xC930_203C
CVI_SYN_A_CRG_CHECK_CVI_6_M19A0_T            a_crg_check_cvi_6        ;         // 0xC930_2040
CVI_SYN_A_CRG_CHECK_CVI_7_M19A0_T            a_crg_check_cvi_7        ;         // 0xC930_2044
CVI_SYN_A_CRG_CHECK_CVI_8_M19A0_T            a_crg_check_cvi_8        ;         // 0xC930_2048
CVI_SYN_A_CRG_CHECK_CVI_9_M19A0_T            a_crg_check_cvi_9        ;         // 0xC930_204C
CVI_SYN_A_CRG_CHECK_CVI_10_M19A0_T           a_crg_check_cvi_10       ;         // 0xC930_2050
CVI_SYN_A_CRG_CHECK_CVI_11_M19A0_T           a_crg_check_cvi_11       ;         // 0xC930_2054
CVI_SYN_A_CRG_CHECK_CVI_12_M19A0_T           a_crg_check_cvi_12       ;         // 0xC930_2058
CVI_SYN_A_CRG_CHECK_CVI_13_M19A0_T           a_crg_check_cvi_13       ;         // 0xC930_205C
CVI_SYN_A_CRG_CHECK_CVI_14_M19A0_T           a_crg_check_cvi_14       ;         // 0xC930_2060
CVI_SYN_A_CRG_CHECK_CVI_15_M19A0_T           a_crg_check_cvi_15       ;         // 0xC930_2064
CVI_SYN_A_CRG_CHECK_CVI_16_M19A0_T           a_crg_check_cvi_16       ;         // 0xC930_2068
CVI_SYN_A_CRG_CHECK_CVI_17_M19A0_T           a_crg_check_cvi_17       ;         // 0xC930_206C
CVI_SYN_A_CRG_CHECK_CVI_18_M19A0_T           a_crg_check_cvi_18       ;         // 0xC930_2070
CVI_SYN_A_CRG_CHECK_CVI_19_M19A0_T           a_crg_check_cvi_19       ;         // 0xC930_2074
CVI_SYN_A_CRG_CHECK_CVI_20_M19A0_T           a_crg_check_cvi_20       ;         // 0xC930_2078
CVI_SYN_A_CRG_CHECK_CVI_21_M19A0_T           a_crg_check_cvi_21       ;         // 0xC930_207C
CVI_SYN_A_CRG_CHECK_CVI_22_M19A0_T           a_crg_check_cvi_22       ;         // 0xC930_2080
CVI_SYN_A_CRG_CHECK_CVI_23_M19A0_T           a_crg_check_cvi_23       ;         // 0xC930_2084
CVI_SYN_A_CRG_CHECK_CVI_24_M19A0_T           a_crg_check_cvi_24       ;         // 0xC930_2088
CVI_SYN_A_CRG_CHECK_CVI_25_M19A0_T           a_crg_check_cvi_25       ;         // 0xC930_208C
CVI_SYN_SYN_HDMI06_M19A0_T                   syn_hdmi06               ;         // 0xC930_2090
CVI_SYN_SYN_CVI00_M19A0_T                    syn_cvi00                ;         // 0xC930_2094
CVI_SYN_SYN_CVI01_M19A0_T                    syn_cvi01                ;         // 0xC930_2098
CVI_SYN_SYN_CVI02_M19A0_T                    syn_cvi02                ;         // 0xC930_209C
CVI_SYN_SYN_CVI03_M19A0_T                    syn_cvi03                ;         // 0xC930_20A0
CVI_SYN_SYN_CVI04_M19A0_T                    syn_cvi04                ;         // 0xC930_20A4
CVI_SYN_SYN_CVI05_M19A0_T                    syn_cvi05                ;         // 0xC930_20A8
} CVI_SYN_REG_M19A0_T;
/* 43 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CVI_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

