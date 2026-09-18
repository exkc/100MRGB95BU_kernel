#ifndef _WOV_SYN_O20A0_REG_H_
#define _WOV_SYN_O20A0_REG_H_

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
    0xC330_0000    crg_micom00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom__micom_clk_gate_en: 1,    //     0
    reg_micom__micom_peri_clk_gate_en: 1,    //  1
    reg_micom__micom_saradc_clk_gate_en: 1,    //  2
    reg_micom__micom_peri_bnd_clk_gate_en: 1,    //  3
                              : 28;    //   31:4 reserved
}WOV_SYN_CRG_MICOM00_O20A0_T;

typedef struct {
    UINT32
    reg_micom__micom_clk_gate_en: 1,    //     0
    reg_micom__micom_peri_clk_gate_en: 1,    //  1
    reg_micom__micom_saradc_clk_gate_en: 1,    //  2
    reg_micom__micom_peri_bnd_clk_gate_en: 1,    //  3
    reg_micom__micom_rtc_clk_gate_en: 1,    //  4
                              : 27;    //   31:5 reserved
}WOV_SYN_CRG_MICOM00_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0004    crg_micom01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom__soft_rst_micom_cm0p_n: 1,    //  0
    reg_micom__soft_rst_micom_peri_n: 1,    //  1
    reg_micom__soft_rst_micom_bus_n: 1,    //  2
    reg_micom__soft_rst_micom_saradc_n: 1,    //  3
    reg_micom__soft_rst_micom_peri_bnd_n: 1,    //  4
    reg_micom__soft_rst_micom_bnd_n: 1,    //  5
                              : 26;    //   31:6 reserved
}WOV_SYN_CRG_MICOM01_O20A0_T;

typedef struct {
    UINT32
    reg_micom__soft_rst_micom_cm0p_n: 1,    //  0
    reg_micom__soft_rst_micom_peri_n: 1,    //  1
    reg_micom__soft_rst_micom_bus_n: 1,    //  2
    reg_micom__soft_rst_micom_saradc_n: 1,    //  3
    reg_micom__soft_rst_micom_peri_bnd_n: 1,    //  4
    reg_micom__soft_rst_micom_bnd_n: 1,    //  5
    reg_micom__soft_rst_micom_rtc_n: 1,    //  6
    reg_micom__soft_rst_micom_bus_bnd_n: 1,    //  7
                              : 24;    //   31:8 reserved
}WOV_SYN_CRG_MICOM01_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0008    crg_micom02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom__micom_clk_sel  :  2,    //   1: 0
    reg_micom__micom_peri_clk_sel: 1,    //    2
                              : 29;    //   31:3 reserved
}WOV_SYN_CRG_MICOM02_O20A0_T;

typedef struct {
    UINT32
    reg_micom__micom_clk_sel  :  2,    //   1: 0
    reg_micom__micom_peri_clk_sel: 1,    //    2
                              :  1,    //      3 reserved
    reg_micom__micom_rtc_clk_sel: 1,    //     4
                              : 27;    //   31:5 reserved
}WOV_SYN_CRG_MICOM02_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_000C    crg_micom03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom__crg_freq_value : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_micom__crg_rst_high_check: 1,    //   28
                              :  1,    //     29 reserved
    reg_micom__crg_clk_off_check: 1,    //    30
    reg_micom__crg_clk_gate   :  1;    //     31
}WOV_SYN_CRG_MICOM03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0010    crg_micom04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom__crg_clk_rst_sel: 32;    //  31: 0
}WOV_SYN_CRG_MICOM04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0014    crg_edid05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid__edid_comm_apb_clk_gate_en: 1,    //  0
    reg_edid__edid_comm_smpl_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}WOV_SYN_CRG_EDID05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0018    crg_edid06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid__soft_rst_edid_prt5_smpl_n: 1,    //  0
    reg_edid__soft_rst_edid_prt5_apb_n: 1,    //  1
    reg_edid__soft_rst_edid_prt4_smpl_n: 1,    //  2
    reg_edid__soft_rst_edid_prt4_apb_n: 1,    //  3
    reg_edid__soft_rst_edid_prt3_smpl_n: 1,    //  4
    reg_edid__soft_rst_edid_prt3_apb_n: 1,    //  5
    reg_edid__soft_rst_edid_prt2_smpl_n: 1,    //  6
    reg_edid__soft_rst_edid_prt2_apb_n: 1,    //  7
    reg_edid__soft_rst_edid_prt1_smpl_n: 1,    //  8
    reg_edid__soft_rst_edid_prt1_apb_n: 1,    //  9
    reg_edid__soft_rst_edid_comm_apb_n: 1,    //  10
                              : 21;    //  31:11 reserved
}WOV_SYN_CRG_EDID06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_001C    crg_edid07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid__edid_comm_smpl_clk_sel: 1,    //  0
                              : 31;    //   31:1 reserved
}WOV_SYN_CRG_EDID07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0020    crg_edid08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_edid__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_edid__crg_clk_off_check: 1,    //     30
    reg_edid__crg_clk_gate    :  1;    //     31
}WOV_SYN_CRG_EDID08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0024    crg_edid09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid__crg_clk_rst_sel : 32;    //  31: 0
}WOV_SYN_CRG_EDID09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0028    crg_wov10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_pdmclk_gate_en: 1,    //      0
    reg_wov__wov_micomclk_gate_en: 1,    //    1
    reg_wov__wov_cpuclk_gate_en: 1,    //      2
    reg_wov__wov_axiclk_gate_en: 1,    //      3
    reg_wov__wov_ahbclk_gate_en: 1,    //      4
                              : 27;    //   31:5 reserved
}WOV_SYN_CRG_WOV10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_002C    crg_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__soft_rst_wov_pdm_n: 1,    //      0
    reg_wov__soft_rst_wov_micom_n: 1,    //    1
    reg_wov__soft_rst_wov_cpu_n: 1,    //      2
    reg_wov__soft_rst_wov_axi_n: 1,    //      3
    reg_wov__soft_rst_wov_ahb_n: 1,    //      4
                              : 27;    //   31:5 reserved
}WOV_SYN_CRG_WOV11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0030    crg_wov12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__wov_cpuclk_sel   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_wov__wov_pdmclk_sel   :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}WOV_SYN_CRG_WOV12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0034    crg_wov13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_wov__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_wov__crg_clk_off_check:  1,    //     30
    reg_wov__crg_clk_gate     :  1;    //     31
}WOV_SYN_CRG_WOV13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0038    crg_wov14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__crg_clk_rst_sel  : 32;    //  31: 0
}WOV_SYN_CRG_WOV14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0040    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_micom:  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_edid :  9,    //  24:16
                              :  7;    //  31:25 reserved
}WOV_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0044    crg_clk_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core660_clk_ctrl_wov  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_wov  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}WOV_SYN_CRG_CLK_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0048    edid_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_wr_done          :  1,    //      0
    reg_hpd_out_micom         :  1,    //      1
                              :  1,    //      2 reserved
    reg_hpd_out_prt4_edid     :  1,    //      3
    reg_hpd_out_prt3_edid     :  1,    //      4
    reg_hpd_out_prt2_edid     :  1,    //      5
    reg_hpd_out_prt1_edid     :  1,    //      6
    reg_hpd_out_prt0_edid     :  1,    //      7
    reg_hpd_out_prt4          :  1,    //      8
    reg_hpd_out_prt3          :  1,    //      9
    reg_hpd_out_prt2          :  1,    //     10
    reg_hpd_out_prt1          :  1,    //     11
    reg_hpd_out_prt0          :  1,    //     12
    reg_i2c_ch_for_micom_sel  :  3,    //  15:13
                              :  3,    //  18:16 reserved
    reg_i2c_micom_input_sel   :  1,    //     19
                              :  1,    //     20 reserved
    reg_hpd_ch_for_micom_sel  :  3,    //  23:21
    reg_hpd_sel               :  2,    //  25:24
                              :  6;    //  31:26 reserved
}WOV_SYN_EDID_CTRL00_O20A0_T;

typedef struct {
    UINT32
    reg_edid_wr_done          :  1,    //      0
    reg_hpd_out_micom         :  1,    //      1
                              :  1,    //      2 reserved
    reg_hpd_out_prt4_edid     :  1,    //      3
    reg_hpd_out_prt3_edid     :  1,    //      4
    reg_hpd_out_prt2_edid     :  1,    //      5
    reg_hpd_out_prt1_edid     :  1,    //      6
    reg_hpd_out_prt0_edid     :  1,    //      7
    reg_hpd_out_prt4          :  1,    //      8
    reg_hpd_out_prt3          :  1,    //      9
    reg_hpd_out_prt2          :  1,    //     10
    reg_hpd_out_prt1          :  1,    //     11
    reg_hpd_out_prt0          :  1,    //     12
    reg_i2c_ch_for_micom_sel  :  3,    //  15:13
                              :  3,    //  18:16 reserved
    reg_i2c_micom_input_sel   :  1,    //     19
                              :  1,    //     20 reserved
    reg_hpd_ch_for_micom_sel  :  3,    //  23:21
    reg_hpd_sel               :  2,    //  25:24
    reg_hdmi1_hpd_en          :  1,    //     26
    reg_hdmi2_hpd_en          :  1,    //     27
    reg_hdmi3_hpd_en          :  1,    //     28
    reg_hdmi4_hpd_en          :  1,    //     29
    reg_hdmi5_hpd_en          :  1,    //     30
                              :  1;    //  31:31 reserved
}WOV_SYN_EDID_CTRL00_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_004C    i2c_path_ctrl_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_2x1_m1_gating     :  1,    //      0
    reg_i2c_2x1_m2_gating     :  1,    //      1
    reg_i2c_2x1_s_gating      :  1,    //      2
                              :  1,    //      3 reserved
    reg_i2c_micom0_gating     :  1,    //      4
                              : 11,    //  15: 5 reserved
    reg_i2c_edid_gating       :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_i2c_link_gating       :  5,    //  28:24
                              :  3;    //  31:29 reserved
}WOV_SYN_I2C_PATH_CTRL_00_O20A0_T;

typedef struct {
    UINT32
    reg_i2c_2x1_m1_gating     :  1,    //      0
    reg_i2c_2x1_m2_gating     :  1,    //      1
    reg_i2c_2x1_s_gating      :  1,    //      2
                              :  1,    //      3 reserved
    reg_i2c_micom2_gating     :  1,    //      4
                              : 11,    //  15: 5 reserved
    reg_i2c_edid_gating       :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_i2c_link_gating       :  5,    //  28:24
                              :  3;    //  31:29 reserved
}WOV_SYN_I2C_PATH_CTRL_00_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0050    i2c_path_ctrl_01 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC330_0054    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_wov        :  1,    //      0
    reg_ls_disable_edid       :  1,    //      1
    reg_ls_disable_micom      :  1,    //      2
                              : 29;    //   31:3 reserved
}WOV_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0058    micom_clk_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_outclk_div      : 10,    //   9: 0
                              :  2,    //  11:10 reserved
    reg_micom_outclk_en       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_micom_peri_clk_div    : 10,    //  25:16
                              :  2,    //  27:26 reserved
    reg_micom_peri_clk_en     :  1,    //     28
                              :  3;    //  31:29 reserved
}WOV_SYN_MICOM_CLK_CTRL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_005C    isol_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_psel_masking_cpu_to_wov_bnd: 1,    //  0
    reg_psel_masking_cpu_to_edid: 1,    //     1
                              :  2,    //   3: 2 reserved
    reg_valid_masking_micom_arvalid_c2m: 1,    //  4
    reg_valid_masking_micom_wvalid_c2m: 1,    //  5
    reg_valid_masking_micom_awvalid_c2m: 1,    //  6
    reg_valid_masking_micom_rvalid_m2w: 1,    //  7
    reg_valid_masking_micom_bvalid_m2w: 1,    //  8
    reg_valid_masking_micom_rvalid_m2c: 1,    //  9
    reg_valid_masking_micom_bvalid_m2c: 1,    //  10
                              :  1,    //     11 reserved
    reg_valid_masking_wov_lne_arvalid_adec_lne: 1,    //  12
    reg_valid_masking_wov_lne_wvalid_adec_lne: 1,    //  13
    reg_valid_masking_wov_lne_awvalid_adec_lne: 1,    //  14
    reg_valid_masking_wov_lgsr_rvalid: 1,    //  15
    reg_valid_masking_wov_lgsr_bvalid: 1,    //  16
    reg_valid_masking_wov_aud_rvalid: 1,    //  17
    reg_valid_masking_wov_aud_bvalid: 1,    //  18
    reg_valid_masking_wov_cpu_wvalid: 1,    //  19
    reg_valid_masking_wov_cpu_awvalid: 1,    //  20
    reg_valid_masking_wov_cpu_arvalid: 1,    //  21
    reg_valid_masking_wov_ddr_rvalid: 1,    //  22
    reg_valid_masking_wov_ddr_bvalid: 1,    //  23
                              :  8;    //  31:24 reserved
}WOV_SYN_ISOL_CTRL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    wov_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
union {
WOV_SYN_CRG_MICOM00_O20A0_T                  crg_micom00              ;         // 0xC330_0000
WOV_SYN_CRG_MICOM00_O20B0_T                  crg_micom00_B0           ;         // 0xC330_0000
};
union {
WOV_SYN_CRG_MICOM01_O20A0_T                  crg_micom01              ;         // 0xC330_0004
WOV_SYN_CRG_MICOM01_O20B0_T                  crg_micom01_B0           ;         // 0xC330_0004
};
union {
WOV_SYN_CRG_MICOM02_O20A0_T                  crg_micom02              ;         // 0xC330_0008
WOV_SYN_CRG_MICOM02_O20B0_T                  crg_micom02_B0           ;         // 0xC330_0008
};
WOV_SYN_CRG_MICOM03_O20A0_T                  crg_micom03              ;         // 0xC330_000C
WOV_SYN_CRG_MICOM04_O20A0_T                  crg_micom04              ;         // 0xC330_0010
WOV_SYN_CRG_EDID05_O20A0_T                   crg_edid05               ;         // 0xC330_0014
WOV_SYN_CRG_EDID06_O20A0_T                   crg_edid06               ;         // 0xC330_0018
WOV_SYN_CRG_EDID07_O20A0_T                   crg_edid07               ;         // 0xC330_001C
WOV_SYN_CRG_EDID08_O20A0_T                   crg_edid08               ;         // 0xC330_0020
WOV_SYN_CRG_EDID09_O20A0_T                   crg_edid09               ;         // 0xC330_0024
WOV_SYN_CRG_WOV10_O20A0_T                    crg_wov10                ;         // 0xC330_0028
WOV_SYN_CRG_WOV11_O20A0_T                    crg_wov11                ;         // 0xC330_002C
WOV_SYN_CRG_WOV12_O20A0_T                    crg_wov12                ;         // 0xC330_0030
WOV_SYN_CRG_WOV13_O20A0_T                    crg_wov13                ;         // 0xC330_0034
WOV_SYN_CRG_WOV14_O20A0_T                    crg_wov14                ;         // 0xC330_0038
UINT32                                                 _rsvd_00[   1] ;         // 0xC330_003C
WOV_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC330_0040
WOV_SYN_CRG_CLK_CTRL02_O20A0_T               crg_clk_ctrl02           ;         // 0xC330_0044
union {
WOV_SYN_EDID_CTRL00_O20A0_T                  edid_ctrl00              ;         // 0xC330_0048
WOV_SYN_EDID_CTRL00_O20B0_T                  edid_ctrl00_B0           ;         // 0xC330_0048
};
union {
WOV_SYN_I2C_PATH_CTRL_00_O20A0_T             i2c_path_ctrl_00         ;         // 0xC330_004C
WOV_SYN_I2C_PATH_CTRL_00_O20B0_T             i2c_path_ctrl_00_B0      ;         // 0xC330_004C
};
    UINT32                                   i2c_path_ctrl_01         ;         // 0xC330_0050
WOV_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC330_0054
WOV_SYN_MICOM_CLK_CTRL_O20A0_T               micom_clk_ctrl           ;         // 0xC330_0058
WOV_SYN_ISOL_CTRL_O20A0_T                    isol_ctrl                ;         // 0xC330_005C
} WOV_SYN_REG_O20A0_T;
/* 23 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _WOV_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

