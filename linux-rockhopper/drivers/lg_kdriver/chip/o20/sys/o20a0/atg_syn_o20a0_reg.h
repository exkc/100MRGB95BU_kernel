#ifndef _ATG_SYN_O20A0_REG_H_
#define _ATG_SYN_O20A0_REG_H_

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
    0xC930_1000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__aud_apbclk_gate_en: 1,    //      0
    reg_aud__aud_aclk_gate_en :  1,    //      1
    reg_aud__aud_lneclk_gate_en: 1,    //      2
    reg_aud__aud_i2s_sclk_gate_en: 1,    //    3
    reg_aud__aud_fs21clk_gate_en: 1,    //     4
    reg_aud__aud_fs23clk_gate_en: 1,    //     5
    reg_aud__aud_fs25clk_gate_en: 1,    //     6
    reg_aud__aud_hmr0spdifclk_gate_en: 1,    //  7
    reg_aud__aud_hmr2spdifclk_gate_en: 1,    //  8
    reg_aud__aud_hmr4spdifclk_gate_en: 1,    //  9
    reg_aud__aud_teclk_gate_en:  1,    //     10
    reg_aud__aud_fs00clk_gate_en: 1,    //    11
    reg_aud__aud_fs22clk_gate_en: 1,    //    12
    reg_aud__aud_fs26clk_gate_en: 1,    //    13
    reg_aud__aud_hmr3spdifclk_gate_en: 1,    //  14
    reg_aud__aud_fs20clk_gate_en: 1,    //    15
    reg_aud__aud_hmr1spdifclk_gate_en: 1,    //  16
    reg_aud__aud_fs24clk_gate_en: 1,    //    17
    reg_aud__apb_bnd_clk_gate_en: 1,    //    18
    reg_axi_soc_clk_gate_en   :  1,    //     19
    reg_aud__aud_lne_axiclk_gate_en: 1,    //  20
                              : 11;    //  31:21 reserved
}ATG_SYN_CRG_AUD00_O20A0_T;

typedef struct {
    UINT32
    reg_aud__aud_apbclk_gate_en: 1,    //      0
    reg_aud__aud_aclk_gate_en :  1,    //      1
    reg_aud__aud_lneclk_gate_en: 1,    //      2
    reg_aud__aud_i2s_sclk_gate_en: 1,    //    3
    reg_aud__aud_fs21clk_gate_en: 1,    //     4
    reg_aud__aud_fs23clk_gate_en: 1,    //     5
    reg_aud__aud_fs25clk_gate_en: 1,    //     6
    reg_aud__aud_hmr0spdifclk_gate_en: 1,    //  7
    reg_aud__aud_hmr2spdifclk_gate_en: 1,    //  8
    reg_aud__aud_hmr4spdifclk_gate_en: 1,    //  9
    reg_aud__aud_teclk_gate_en:  1,    //     10
    reg_aud__aud_fs00clk_gate_en: 1,    //    11
    reg_aud__aud_fs22clk_gate_en: 1,    //    12
    reg_aud__aud_fs26clk_gate_en: 1,    //    13
    reg_aud__aud_hmr3spdifclk_gate_en: 1,    //  14
    reg_aud__aud_fs20clk_gate_en: 1,    //    15
    reg_aud__aud_hmr1spdifclk_gate_en: 1,    //  16
    reg_aud__aud_fs24clk_gate_en: 1,    //    17
    reg_aud__apb_bnd_clk_gate_en: 1,    //    18
    reg_axi_soc_clk_gate_en   :  1,    //     19
    reg_aud__aud_lne_axiclk_gate_en: 1,    //  20
    reg_aud__aud_lne_pclk_gate_en: 1,    //   21
                              : 10;    //  31:22 reserved
}ATG_SYN_CRG_AUD00_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__soft_rst_aud_apb_n: 1,    //      0
    reg_aud__soft_rst_aud_lne_n: 1,    //      1
    reg_aud__soft_rst_axi_n   :  1,    //      2
    reg_aud__soft_rst_axi_bnd_n: 1,    //      3
    reg_aud__soft_rst_aud_te_bnd_n: 1,    //   4
    reg_aud__soft_aud_lne_areset_n: 1,    //   5
                              : 26;    //   31:6 reserved
}ATG_SYN_CRG_AUD01_O20A0_T;

typedef struct {
    UINT32
    reg_aud__soft_rst_aud_apb_n: 1,    //      0
    reg_aud__soft_rst_aud_lne_n: 1,    //      1
    reg_aud__soft_rst_axi_n   :  1,    //      2
    reg_aud__soft_rst_axi_bnd_n: 1,    //      3
    reg_aud__soft_rst_aud_te_bnd_n: 1,    //   4
    reg_aud__soft_aud_lne_areset_n: 1,    //   5
    reg_aud__soft_aud_lne_preset_n: 1,    //   6
                              : 25;    //   31:7 reserved
}ATG_SYN_CRG_AUD01_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1008    crg_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__i_aud_fs20clk_inv_sel: 1,    //   0
    reg_aud__i_aud_fs22clk_inv_sel: 1,    //   1
    reg_aud__i_aud_fs24clk_inv_sel: 1,    //   2
    reg_aud__i_aud_fs26clk_inv_sel: 1,    //   3
    reg_aud__i_aud_hmr0spdifclk_inv_sel: 1,    //  4
    reg_aud__i_aud_hmr2spdifclk_inv_sel: 1,    //  5
    reg_aud__i_aud_hmr4spdifclk_inv_sel: 1,    //  6
    reg_aud__i_aud_fs21clk_inv_sel: 1,    //   7
    reg_aud__i_aud_fs25clk_inv_sel: 1,    //   8
    reg_aud__i_aud_hmr1spdifclk_inv_sel: 1,    //  9
    reg_aud__i_aud_fs23clk_inv_sel: 1,    //  10
    reg_aud__i_aud_hmr3spdifclk_inv_sel: 1,    //  11
    reg_aud__i_fs00_clk_inv_sel: 1,    //     12
    reg_aud__aud_lne_axiclk_sel: 2,    //  14:13
                              : 17;    //  31:15 reserved
}ATG_SYN_CRG_AUD02_O20A0_T;

typedef struct {
    UINT32
    reg_aud__i_aud_fs20clk_inv_sel: 1,    //   0
    reg_aud__i_aud_fs22clk_inv_sel: 1,    //   1
    reg_aud__i_aud_fs24clk_inv_sel: 1,    //   2
    reg_aud__i_aud_fs26clk_inv_sel: 1,    //   3
    reg_aud__i_aud_hmr0spdifclk_inv_sel: 1,    //  4
    reg_aud__i_aud_hmr2spdifclk_inv_sel: 1,    //  5
    reg_aud__i_aud_hmr4spdifclk_inv_sel: 1,    //  6
    reg_aud__i_aud_fs21clk_inv_sel: 1,    //   7
    reg_aud__i_aud_fs25clk_inv_sel: 1,    //   8
    reg_aud__i_aud_hmr1spdifclk_inv_sel: 1,    //  9
    reg_aud__i_aud_fs23clk_inv_sel: 1,    //  10
    reg_aud__i_aud_hmr3spdifclk_inv_sel: 1,    //  11
    reg_aud__i_fs00_clk_inv_sel: 1,    //     12
    reg_aud__aud_lne_axiclk_sel: 2,    //  14:13
    reg_aud__aud_lne_pclk_sel :  2,    //  16:15
                              : 15;    //  31:17 reserved
}ATG_SYN_CRG_AUD02_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_100C    crg_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__aud_aclk_sel     :  1,    //      0
    reg_aud__aud_lneclk_sel   :  2,    //   2: 1
                              : 29;    //   31:3 reserved
}ATG_SYN_CRG_AUD03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1010    crg_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_aud__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_aud__crg_clk_off_check:  1,    //     30
    reg_aud__crg_clk_gate     :  1;    //     31
}ATG_SYN_CRG_AUD04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1014    crg_aud05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__crg_clk_rst_sel  : 32;    //  31: 0
}ATG_SYN_CRG_AUD05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1018    crg_te06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te__axi_clk_gate_en   :  1,    //      0
    reg_te__temcu_clk_gate_en :  1,    //      1
    reg_te__ch0_sclk_gate_en  :  1,    //      2
    reg_te__ch1_sclk_gate_en  :  1,    //      3
    reg_te__ch2_sclk_gate_en  :  1,    //      4
    reg_te__ch3_sclk_gate_en  :  1,    //      5
    reg_te__te_ciout_clk_gate_en: 1,    //     6
    reg_te__gstcc_if_clk_gate_en: 1,    //     7
    reg_te__tpi1_clk_gate_en  :  1,    //      8
    reg_te__tpi3_clk_gate_en  :  1,    //      9
    reg_te__tiv_axi_clk_gate_en: 1,    //     10
    reg_te__ti_axi_bnd_clk_gate_en: 1,    //  11
    reg_te__te_clk_gate_en    :  1,    //     12
    reg_te__stpo_clk_gate_en  :  1,    //     13
    reg_te__tpi0_clk_gate_en  :  1,    //     14
    reg_te__stpi0_clk_gate_en :  1,    //     15
    reg_te__fixed_sclk_gate_en:  1,    //     16
    reg_te__tpi2_clk_gate_en  :  1,    //     17
    reg_te__tpi4_clk_gate_en  :  1,    //     18
    reg_te__tpi5_clk_gate_en  :  1,    //     19
                              : 12;    //  31:20 reserved
}ATG_SYN_CRG_TE06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_101C    crg_te07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te__soft_rst_axi_n    :  1,    //      0
    reg_te__soft_rst_temcu_n  :  1,    //      1
    reg_te__soft_rst_ch0_s_n  :  1,    //      2
    reg_te__soft_rst_ch2_s_n  :  1,    //      3
    reg_te__soft_rst_stpo_n   :  1,    //      4
    reg_te__soft_rst_gstcc_if_n: 1,    //      5
    reg_te__soft_rst_te_axi_bnd_n: 1,    //    6
    reg_te__soft_rst_gstcc_bnd_n: 1,    //     7
    reg_te__soft_rst_te_n     :  1,    //      8
    reg_te__soft_rst_ch1_s_n  :  1,    //      9
    reg_te__soft_rst_ciout_n  :  1,    //     10
    reg_te__soft_rst_ti_axi_bnd_n: 1,    //   11
    reg_te__soft_rst_f_s_n    :  1,    //     12
    reg_te__soft_rst_te_bnd_n :  1,    //     13
    reg_te__soft_rst_ch3_s_n  :  1,    //     14
    reg_te__soft_rst_te_axi_n :  1,    //     15
                              : 16;    //  31:16 reserved
}ATG_SYN_CRG_TE07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1020    crg_te08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te__i_sdco27_clk_inv_sel: 1,    //     0
    reg_te__tpi_clk_gf_1_inv_sel: 1,    //     1
    reg_te__tpi_clk_gf_3_inv_sel: 1,    //     2
    reg_te__tpi_clk_gf_5_inv_sel: 1,    //     3
    reg_te__i_f27m_clk_inv_sel:  1,    //      4
    reg_te__tpi_clk_gf_4_inv_sel: 1,    //     5
    reg_te__tpi_clk_gf_2_inv_sel: 1,    //     6
    reg_te__tpi_clk_gf_6_inv_sel: 1,    //     7
    reg_te__tpi_clk_gf_7_inv_sel: 1,    //     8
    reg_tpi4_filter_margin_sel:  2,    //  10: 9
    reg_tpi5_filter_margin_sel:  2,    //  12:11
    reg_tpi4_clk_flt_sel      :  1,    //     13
    reg_tpi5_clk_flt_sel      :  1,    //     14
                              : 17;    //  31:15 reserved
}ATG_SYN_CRG_TE08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1024    crg_te09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi0_clk_flt_sel      :  1,    //      0
    reg_tpi1_clk_flt_sel      :  1,    //      1
    reg_tpi2_clk_flt_sel      :  1,    //      2
    reg_tpi3_clk_flt_sel      :  1,    //      3
    reg_stpi0_clk_flt_sel     :  1,    //      4
    reg_te_ciout_clk_sel      :  3,    //   7: 5
    reg_te__ch0_sclk_sel      :  1,    //      8
    reg_te__ch2_sclk_sel      :  1,    //      9
    reg_te__gstcc_if_clk_sel  :  1,    //     10
    reg_te__aud_apb_bnd_clk_sel: 1,    //     11
    reg_tpi0_filter_margin_sel:  2,    //  13:12
    reg_tpi1_filter_margin_sel:  2,    //  15:14
    reg_tpi2_filter_margin_sel:  2,    //  17:16
    reg_tpi3_filter_margin_sel:  2,    //  19:18
    reg_stpi0_filter_margin_sel: 2,    //  21:20
    reg_stpo_clk_sel          :  3,    //  24:22
    reg_te__ch1_sclk_sel      :  1,    //     25
    reg_te__te_apb_bnd_clk_sel:  1,    //     26
    reg_te__ch3_sclk_sel      :  1,    //     27
    reg_te__ti_axi_bnd_clk_sel:  1,    //     28
                              :  3;    //  31:29 reserved
}ATG_SYN_CRG_TE09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1028    crg_te10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te__crg_freq_value    : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_te__crg_rst_high_check:  1,    //     28
                              :  1,    //     29 reserved
    reg_te__crg_clk_off_check :  1,    //     30
    reg_te__crg_clk_gate      :  1;    //     31
}ATG_SYN_CRG_TE10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_102C    crg_te11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te__crg_clk_rst_sel   : 32;    //  31: 0
}ATG_SYN_CRG_TE11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1030    crg_venc12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc__ve_clk_gate_en  :  1,    //      0
    reg_venc__ve_apb_clk_gate_en: 1,    //     1
    reg_venc__jpeg_clk_gate_en:  1,    //      2
    reg_venc__de_soc_clk_gate_en: 1,    //     3
    reg_venc__axi_soc_clk_gate_en: 1,    //    4
                              : 27;    //   31:5 reserved
}ATG_SYN_CRG_VENC12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1034    crg_venc13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc__soft_rst_ve_n   :  1,    //      0
    reg_venc__soft_rst_jpeg_n :  1,    //      1
    reg_venc__soft_rst_ve_apb_n: 1,    //      2
    reg_venc__soft_rst_de_soc_n: 1,    //      3
    reg_venc__soft_rst_axi_soc_n: 1,    //     4
                              : 27;    //   31:5 reserved
}ATG_SYN_CRG_VENC13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1038    crg_venc14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc__ve_clk_sel      :  1,    //      0
    reg_venc__jpeg_clk_sel    :  1,    //      1
    reg_venc__ve_apb_clk_sel  :  1,    //      2
                              : 29;    //   31:3 reserved
}ATG_SYN_CRG_VENC14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_103C    crg_venc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_venc__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_venc__crg_clk_off_check: 1,    //     30
    reg_venc__crg_clk_gate    :  1;    //     31
}ATG_SYN_CRG_VENC15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1040    crg_venc16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc__crg_clk_rst_sel : 32;    //  31: 0
}ATG_SYN_CRG_VENC16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1044    crg_gbus17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gbus__gbus400_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}ATG_SYN_CRG_GBUS17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1048    crg_gbus18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gbus__soft_rst_gbus400_n: 1,    //     0
                              : 31;    //   31:1 reserved
}ATG_SYN_CRG_GBUS18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_104C    crg_gbus19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gbus__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_gbus__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_gbus__crg_clk_off_check: 1,    //     30
    reg_gbus__crg_clk_gate    :  1;    //     31
}ATG_SYN_CRG_GBUS19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1050    crg_gbus20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gbus__crg_clk_rst_sel : 32;    //  31: 0
}ATG_SYN_CRG_GBUS20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1054    te01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_stpi0_bypass_mode     :  1,    //      0
    reg_tpi3_bypass_mode      :  1,    //      1
    reg_tpi2_bypass_mode      :  1,    //      2
    reg_tpi1_bypass_mode      :  1,    //      3
    reg_tpi0_bypass_mode      :  1,    //      4
    reg_tpi4_bypass_mode      :  1,    //      5
    reg_tpi5_bypass_mode      :  1,    //      6
                              : 25;    //   31:7 reserved
}ATG_SYN_TE01_O20A0_T;

typedef struct {
    UINT32
    reg_stpi0_bypass_mode     :  1,    //      0
    reg_tpi3_bypass_mode      :  1,    //      1
    reg_tpi2_bypass_mode      :  1,    //      2
    reg_tpi1_bypass_mode      :  1,    //      3
    reg_tpi0_bypass_mode      :  1,    //      4
    reg_tpi4_bypass_mode      :  1,    //      5
    reg_tpi5_bypass_mode      :  1,    //      6
                              :  9,    //  15: 7 reserved
    reg_te__tpi_mux_sel       :  1,    //     16
                              : 15;    //  31:17 reserved
}ATG_SYN_TE01_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1058    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_gbus :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}ATG_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_105C    crg_clk_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_aud  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_aud  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}ATG_SYN_CRG_CLK_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1060    crg_clk_ctrl03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_te   :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_te   :  9,    //  24:16
                              :  7;    //  31:25 reserved
}ATG_SYN_CRG_CLK_CTRL03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1064    crg_clk_ctrl04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_venc :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_icod :  9,    //  24:16
                              :  7;    //  31:25 reserved
}ATG_SYN_CRG_CLK_CTRL04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1068    crg_clk_ctrl05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core800_clk_ctrl_aud  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core660_clk_ctrl_aud  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}ATG_SYN_CRG_CLK_CTRL05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_106C    ip_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_gbus_lgarb     :  1,    //      0
    reg__swrst_lbus_lgarb     :  1,    //      1
                              : 30;    //   31:2 reserved
}ATG_SYN_IP_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1070    ip_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_gstcm0         :  1,    //      0
    reg__swrst_gstcm1         :  1,    //      1
    reg__swrst_te0            :  1,    //      2
    reg__swrst_te1            :  1,    //      3
                              : 28;    //   31:4 reserved
}ATG_SYN_IP_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1074    aud_power_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__npwrupsram           :  1,    //      0
                              : 31;    //   31:1 reserved
}ATG_SYN_AUD_POWER_00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1078    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_gbus       :  1,    //      0
    reg_ls_disable_te         :  1,    //      1
    reg_ls_disable_icod       :  1,    //      2
    reg_ls_disable_venc       :  1,    //      3
    reg_ls_disable_aud        :  1,    //      4
                              : 27;    //   31:5 reserved
}ATG_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_107C    rgmii_rs ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rgmii_tx_rs_bypass    :  1,    //      0
    reg_rgmii_rx_rs_bypass    :  1,    //      1
                              : 30;    //   31:2 reserved
}ATG_SYN_RGMII_RS_O20B0_T;

/*-----------------------------------------------------------------------------------------
    atg_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
union {
ATG_SYN_CRG_AUD00_O20A0_T                    crg_aud00                ;         // 0xC930_1000
ATG_SYN_CRG_AUD00_O20B0_T                    crg_aud00_B0             ;         // 0xC930_1000
};
union {
ATG_SYN_CRG_AUD01_O20A0_T                    crg_aud01                ;         // 0xC930_1004
ATG_SYN_CRG_AUD01_O20B0_T                    crg_aud01_B0             ;         // 0xC930_1004
};
union {
ATG_SYN_CRG_AUD02_O20A0_T                    crg_aud02                ;         // 0xC930_1008
ATG_SYN_CRG_AUD02_O20B0_T                    crg_aud02_B0             ;         // 0xC930_1008
};
ATG_SYN_CRG_AUD03_O20A0_T                    crg_aud03                ;         // 0xC930_100C
ATG_SYN_CRG_AUD04_O20A0_T                    crg_aud04                ;         // 0xC930_1010
ATG_SYN_CRG_AUD05_O20A0_T                    crg_aud05                ;         // 0xC930_1014
ATG_SYN_CRG_TE06_O20A0_T                     crg_te06                 ;         // 0xC930_1018
ATG_SYN_CRG_TE07_O20A0_T                     crg_te07                 ;         // 0xC930_101C
ATG_SYN_CRG_TE08_O20A0_T                     crg_te08                 ;         // 0xC930_1020
ATG_SYN_CRG_TE09_O20A0_T                     crg_te09                 ;         // 0xC930_1024
ATG_SYN_CRG_TE10_O20A0_T                     crg_te10                 ;         // 0xC930_1028
ATG_SYN_CRG_TE11_O20A0_T                     crg_te11                 ;         // 0xC930_102C
ATG_SYN_CRG_VENC12_O20A0_T                   crg_venc12               ;         // 0xC930_1030
ATG_SYN_CRG_VENC13_O20A0_T                   crg_venc13               ;         // 0xC930_1034
ATG_SYN_CRG_VENC14_O20A0_T                   crg_venc14               ;         // 0xC930_1038
ATG_SYN_CRG_VENC15_O20A0_T                   crg_venc15               ;         // 0xC930_103C
ATG_SYN_CRG_VENC16_O20A0_T                   crg_venc16               ;         // 0xC930_1040
ATG_SYN_CRG_GBUS17_O20A0_T                   crg_gbus17               ;         // 0xC930_1044
ATG_SYN_CRG_GBUS18_O20A0_T                   crg_gbus18               ;         // 0xC930_1048
ATG_SYN_CRG_GBUS19_O20A0_T                   crg_gbus19               ;         // 0xC930_104C
ATG_SYN_CRG_GBUS20_O20A0_T                   crg_gbus20               ;         // 0xC930_1050
union {
ATG_SYN_TE01_O20A0_T                         te01                     ;         // 0xC930_1054
ATG_SYN_TE01_O20B0_T                         te01_B0                  ;         // 0xC930_1054
};
ATG_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC930_1058
ATG_SYN_CRG_CLK_CTRL02_O20A0_T               crg_clk_ctrl02           ;         // 0xC930_105C
ATG_SYN_CRG_CLK_CTRL03_O20A0_T               crg_clk_ctrl03           ;         // 0xC930_1060
ATG_SYN_CRG_CLK_CTRL04_O20A0_T               crg_clk_ctrl04           ;         // 0xC930_1064
ATG_SYN_CRG_CLK_CTRL05_O20A0_T               crg_clk_ctrl05           ;         // 0xC930_1068
ATG_SYN_IP_CTRL00_O20A0_T                    ip_ctrl00                ;         // 0xC930_106C
ATG_SYN_IP_CTRL01_O20A0_T                    ip_ctrl01                ;         // 0xC930_1070
ATG_SYN_AUD_POWER_00_O20A0_T                 aud_power_00             ;         // 0xC930_1074
ATG_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC930_1078
ATG_SYN_RGMII_RS_O20B0_T                     rgmii_rs_B0              ;         // 0xC930_107C
} ATG_SYN_REG_O20A0_T;
/* 31 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _ATG_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

