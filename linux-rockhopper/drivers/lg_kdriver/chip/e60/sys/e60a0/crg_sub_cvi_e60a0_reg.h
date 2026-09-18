#ifndef _CRG_SUB_CVI_E60A0_REG_H_
#define _CRG_SUB_CVI_E60A0_REG_H_

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
    0xC93B_8000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__dsc_hdmirx_tmdsqp_clk_gate_en: 1,    //  0
    reg_cvi__dsc_cvi_clk_gate_en: 1,    //     1
    reg_cvi__dsc_clk_gate_en  :  1,    //      2
    reg_cvi__dsc_fec_clk_gate_en: 1,    //     3
    reg_cvi__cvi_apb_clk_gate_en: 1,    //     4
    reg_cvi__cvi_axi_clk_gate_en: 1,    //     5
    reg_cvi__cvi_cvd54_clk_gate_en: 1,    //   6
    reg_cvi__cvi_cvi0_clk_gate_en: 1,    //    7
    reg_cvi__cvi_cvi1_clk_gate_en: 1,    //    8
    reg_cvi__cvi_cvi2_clk_gate_en: 1,    //    9
    reg_cvi__cvi_cvi3_clk_gate_en: 1,    //   10
    reg_cvi__te_clk_gate_en   :  1,    //     11
    reg_cvi__te_fixed_sclk_gate_en: 1,    //  12
    reg_cvi__te_ch0_sclk_gate_en: 1,    //    13
    reg_cvi__te_ch1_sclk_gate_en: 1,    //    14
    reg_cvi__te_ch2_sclk_gate_en: 1,    //    15
    reg_cvi__te_ch3_sclk_gate_en: 1,    //    16
    reg_cvi__te_ciout_clk_gate_en: 1,    //   17
    reg_cvi__te_tpi_int_clk_gate_en: 1,    //  18
    reg_cvi__te_tpi_cam_clk_gate_en: 1,    //  19
    reg_cvi__te_tpi_ext2_clk_gate_en: 1,    //  20
    reg_cvi__te_stpi_ext2_clk_gate_en: 1,    //  21
    reg_cvi__venc_apb_clk_gate_en: 1,    //   22
    reg_cvi__vi_axi_soc_clk_gate_en: 1,    //  23
    reg_cvi__dsc_cvi_imx_muxed_clk_gate_en: 1,    //  24
    reg_cvi__cvi_axi_soc_clk_gate_en: 1,    //  25
    reg_cvi__apb_bnd_480_clk_gate_en: 1,    //  26
    reg_cvi__dsc_hdmirx_tmdsqp_bnd_2_clk_gate_en: 1,    //  27
    reg_cvi__dsc_hdmirx_tmdsqp_bnd_4_clk_gate_en: 1,    //  28
    reg_cvi__dsc_apb_clk_gate_en: 1,    //    29
    reg_cvi__icod_clk_gate_en :  1,    //     30
    reg_cvi__cvi_ch3pix_clk_gate_en: 1;    //  31
}CRG_SUB_CVI_CRG_CVI00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__te_axi_clk_gate_en: 1,    //      0
    reg_cvi__te_stpo_clk_gate_en: 1,    //     1
    reg_cvi__te_tpi_ext1_clk_gate_en: 1,    //  2
    reg_cvi__venc_clk_gate_en :  1,    //      3
    reg_cvi__te_axi_soc_clk_gate_en: 1,    //  4
    reg_cvi__fsc_pwm_clk_gate_en: 1,    //     5
    reg_cvi__dsc_hdmirx_tmdsqp_bnd_1_clk_gate_en: 1,    //  6
    reg_cvi__cvi_de_clk_gate_en: 1,    //      7
    reg_cvi__te_mcu_clk_gate_en: 1,    //      8
    reg_cvi__te_gstcc_if_clk_gate_en: 1,    //  9
    reg_cvi__te_stpi_ext1_clk_gate_en: 1,    //  10
    reg_cvi__hdmirx_comm_esm_bnd_clk_gate_en: 1,    //  11
    reg_cvi__cvi_cvd27_clk_gate_en: 1,    //  12
    reg_cvi__dsc_imx_clk_gate_en: 1,    //    13
    reg_cvi__dsc_hdmirx_tmdsqp_bnd_3_clk_gate_en: 1,    //  14
                              : 17;    //  31:15 reserved
}CRG_SUB_CVI_CRG_CVI01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__soft_rst_dsc_apb_n: 1,    //      0
    reg_cvi__soft_rst_dsc_fec_n: 1,    //      1
    reg_cvi__soft_rst_dsc_core_n: 1,    //     2
    reg_cvi__soft_rst_dsc_cvi_n: 1,    //      3
    reg_cvi__soft_rst_cvi_apb_n: 1,    //      4
    reg_cvi__soft_rst_cvi_axi_n: 1,    //      5
    reg_cvi__soft_rst_cvi_ch3pix_n: 1,    //   6
    reg_cvi__soft_rst_cvi_cvd27_n: 1,    //    7
    reg_cvi__soft_rst_cvi_cvd_mif_n: 1,    //  8
    reg_cvi__soft_rst_cvi_cvi1_n: 1,    //     9
    reg_cvi__soft_rst_cvi_cvi3_n: 1,    //    10
    reg_cvi__soft_rst_te_n    :  1,    //     11
    reg_cvi__soft_rst_te_f_s_n:  1,    //     12
    reg_cvi__soft_rst_te_ch1_s_n: 1,    //    13
    reg_cvi__soft_rst_te_ch3_s_n: 1,    //    14
    reg_cvi__soft_rst_te_ciout_n: 1,    //    15
    reg_cvi__soft_rst_ve_n    :  1,    //     16
    reg_cvi__soft_rst_dsc_imx_n: 1,    //     17
    reg_cvi__soft_rst_cvi_cvi1_bnd_n: 1,    //  18
    reg_cvi__soft_rst_cvi_cvi3_bnd_n: 1,    //  19
    reg_cvi__soft_rst_te_gstcc_if_bnd_n: 1,    //  20
    reg_cvi__soft_rst_de_bnd_n:  1,    //     21
    reg_cvi__soft_rst_te_axi_soc_n: 1,    //  22
    reg_cvi__soft_rst_pwm_n   :  1,    //     23
    reg_cvi__soft_rst_tiv_axi_bnd_n: 1,    //  24
    reg_cvi__soft_rst_hdmirx_esm_bnd_n: 1,    //  25
    reg_cvi__soft_rst_hdmirx_tmdsqp_bnd_1_n: 1,    //  26
    reg_cvi__soft_rst_hdmirx_tmdsqp_bnd_3_n: 1,    //  27
    reg_cvi__soft_rst_hdmirx_tmdsqp_n: 1,    //  28
    reg_cvi__soft_rst_dsc_core_apb_n: 1,    //  29
    reg_cvi__soft_rst_cvi_de_n:  1,    //     30
    reg_cvi__soft_rst_cvi_cvd54_n: 1;    //   31
}CRG_SUB_CVI_CRG_CVI02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_800C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__soft_rst_cvi_cvi0_n: 1,    //     0
    reg_cvi__soft_rst_te_axi_n:  1,    //      1
    reg_cvi__soft_rst_te_ch0_s_n: 1,    //     2
    reg_cvi__soft_rst_te_stpo_n: 1,    //      3
    reg_cvi__soft_rst_ve_apb_n:  1,    //      4
    reg_cvi__soft_rst_cvi_cvi2_bnd_n: 1,    //  5
    reg_cvi__soft_rst_dsc_imx_bnd_n: 1,    //  6
    reg_cvi__soft_rst_dsc_cvi_imx_muxed_n: 1,    //  7
    reg_cvi__soft_rst_cvi_axi_bnd_n: 1,    //  8
    reg_cvi__soft_rst_hdmirx_tmdsqp_bnd_2_n: 1,    //  9
    reg_cvi__soft_rst_dsc_fec_apb_n: 1,    //  10
    reg_cvi__soft_rst_cvi_axi_sbus_n: 1,    //  11
    reg_cvi__soft_rst_cvi_cvi2_n: 1,    //    12
    reg_cvi__soft_rst_te_ch2_s_n: 1,    //    13
    reg_cvi__soft_rst_cvi_cvi0_bnd_n: 1,    //  14
    reg_cvi__soft_rst_vi_axi_soc_n: 1,    //  15
    reg_cvi__soft_rst_apb_bnd_480_n: 1,    //  16
    reg_cvi__soft_rst_icod_n  :  1,    //     17
    reg_cvi__soft_rst_te_mcu_n:  1,    //     18
    reg_cvi__soft_rst_te_bnd_n:  1,    //     19
    reg_cvi__soft_rst_hdmirx_tmdsqp_bnd_4_n: 1,    //  20
    reg_cvi__soft_rst_cvi_cvd_vbi_n: 1,    //  21
    reg_cvi__soft_rst_cvi_axi_soc_n: 1,    //  22
    reg_cvi__soft_rst_te_gstcc_if_n: 1,    //  23
                              :  8;    //  31:24 reserved
}CRG_SUB_CVI_CRG_CVI03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__i_hdmirx_prt1_tmdsqp_clk_inv_sel: 1,    //  0
    reg_cvi__i_hdmirx_prt3_tmdsqp_clk_inv_sel: 1,    //  1
    reg_cvi__i_cvd54_clk_inv_sel: 1,    //     2
    reg_cvi__i_sdco27_clk_inv_sel: 1,    //    3
    reg_cvi__tpi_clk_gf_1_inv_sel: 1,    //    4
    reg_cvi__tpi_clk_gf_3_inv_sel: 1,    //    5
    reg_cvi__tpi_clk_gf_5_inv_sel: 1,    //    6
    reg_cvi__tpi_clk_gf_7_inv_sel: 1,    //    7
    reg_cvi__i_hdmirx_prt2_tmdsqp_clk_inv_sel: 1,    //  8
    reg_cvi__i_ch3pix_clk_inv_sel: 1,    //    9
    reg_cvi__tpi_clk_gf_2_inv_sel: 1,    //   10
    reg_cvi__tpi_clk_gf_6_inv_sel: 1,    //   11
    reg_cvi__i_hdmirx_prt4_tmdsqp_clk_inv_sel: 1,    //  12
    reg_cvi__tpi_clk_gf_4_inv_sel: 1,    //   13
    reg_cvi__i_f27m_clk_inv_sel: 1,    //     14
                              : 17;    //  31:15 reserved
}CRG_SUB_CVI_CRG_CVI04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8014    crg_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_sel   :  1,    //      0
    reg_tpi_cam_clk_flt_sel   :  1,    //      1
    reg_tpi_ext1_clk_flt_sel  :  1,    //      2
    reg_tpi_ext2_clk_flt_sel  :  1,    //      3
    reg_stpi_ext1_clk_flt_sel :  1,    //      4
    reg_stpi_ext2_clk_flt_sel :  1,    //      5
    reg_cvi__te_ciout_clk_sel :  3,    //   8: 6
    reg_stpi_ext3_clk_flt_sel :  1,    //      9
    reg_cvi__dsc_hdmirx_tmdsqp_clk_sel: 2,    //  11:10
    reg_cvi__dsc_clk_sel      :  2,    //  13:12
    reg_cvi__cvi_cvi0_clk_sel :  4,    //  17:14
    reg_cvi__cvi_cvi2_clk_sel :  4,    //  21:18
    reg_cvi__te_ch0_sclk_sel  :  1,    //     22
    reg_cvi__te_ch2_sclk_sel  :  1,    //     23
    reg_cvi__te_tpi_cam_clk_sel: 1,    //     24
    reg_tpi_int_clk_filter_margin_sel: 2,    //  26:25
    reg_tpi_cam_clk_filter_margin_sel: 2,    //  28:27
    reg_tpi_ext1_clk_filter_margin_sel: 2,    //  30:29
    reg_cvi__dsc_cvi_clk_sel  :  1;    //     31
}CRG_SUB_CVI_CRG_CVI05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8018    crg_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__cvi_cvi1_clk_sel :  4,    //   3: 0
    reg_cvi__te_ch1_sclk_sel  :  1,    //      4
    reg_cvi__dsc_cvi_imx_muxed_clk_sel: 2,    //  6:5
    reg_tpi_ext2_clk_filter_margin_sel: 2,    //  8:7
    reg_stpi_ext1_clk_filter_margin_sel: 2,    //  10:9
    reg_stpi_ext2_clk_filter_margin_sel: 2,    //  12:11
    reg_cvi__stpo_clk_sel     :  3,    //  15:13
    reg_stpi_ext3_clk_filter_margin_sel: 2,    //  17:16
    reg_cvi__dsc_fec_clk_sel  :  1,    //     18
    reg_cvi__te_ch3_sclk_sel  :  1,    //     19
    reg_cvi__cvi_cvi3_clk_sel :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CRG_SUB_CVI_CRG_CVI06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_801C    crg_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_cvi  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_CVI_CRG_CVI07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8020    crg_cvi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_cvi  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_CVI_CRG_CVI08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8024    crg_cvi09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_cvi__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_cvi__crg_clk_off_check:  1,    //     30
    reg_cvi__crg_clk_gate     :  1;    //     31
}CRG_SUB_CVI_CRG_CVI09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8028    crg_cvi10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__crg_clk_rst_sel  : 32;    //  31: 0
}CRG_SUB_CVI_CRG_CVI10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CRG_SUB_CVI_CRG_CVI00_E60_A0_T           crg_cvi00                ;         // 0xC93B_8000
    CRG_SUB_CVI_CRG_CVI01_E60_A0_T           crg_cvi01                ;         // 0xC93B_8004
    CRG_SUB_CVI_CRG_CVI02_E60_A0_T           crg_cvi02                ;         // 0xC93B_8008
    CRG_SUB_CVI_CRG_CVI03_E60_A0_T           crg_cvi03                ;         // 0xC93B_800C
    CRG_SUB_CVI_CRG_CVI04_E60_A0_T           crg_cvi04                ;         // 0xC93B_8010
    CRG_SUB_CVI_CRG_CVI05_E60_A0_T           crg_cvi05                ;         // 0xC93B_8014
    CRG_SUB_CVI_CRG_CVI06_E60_A0_T           crg_cvi06                ;         // 0xC93B_8018
    CRG_SUB_CVI_CRG_CVI07_E60_A0_T           crg_cvi07                ;         // 0xC93B_801C
    CRG_SUB_CVI_CRG_CVI08_E60_A0_T           crg_cvi08                ;         // 0xC93B_8020
    CRG_SUB_CVI_CRG_CVI09_E60_A0_T           crg_cvi09                ;         // 0xC93B_8024
    CRG_SUB_CVI_CRG_CVI10_E60_A0_T           crg_cvi10                ;         // 0xC93B_8028
} CRG_SUB_CVI_REG_E60_A0_T;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_CVI_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_Register_Manual_20190723.xlsx'  2019.12.12  KST by LGSiCRDV V3.0B*/

