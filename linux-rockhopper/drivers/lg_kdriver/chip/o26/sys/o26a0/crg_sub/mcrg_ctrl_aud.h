#ifndef _MCRG_CTRL_AUD_REG_H_
#define _MCRG_CTRL_AUD_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure 
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xCE7B_0000    crg_main_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0004    crg_main_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0008    crg_main_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_apll_f_clk_inv_sel:  1,    //      0
    reg_aud_earc_frpll_clk_inv_sel: 1,    //   1
    reg_aud_f27m_clk_inv_sel  :  1,    //      2
    reg_aud_fs00_clk_inv_sel  :  1,    //      3
    reg_aud_hmr1spdif_m_clk_inv_sel: 1,    //  4
    reg_aud_hmr2spdif_m_clk_inv_sel: 1,    //  5
    reg_aud_hmr3spdif_m_clk_inv_sel: 1,    //  6
    reg_aud_hmr4spdif_m_clk_inv_sel: 1,    //  7
    reg_tpo_cam_out_clk_inv_sel: 1,    //      8
                              : 23;    //   31:9 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_000C    crg_main_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0010    crg_main_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0014    crg_main_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0018    crg_main_aud006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_001C    crg_main_aud007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD007_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0020    crg_main_aud008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD008_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0024    crg_main_aud009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD009_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0028    crg_main_aud010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD010_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_002C    crg_main_aud011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD011_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0030    crg_main_aud012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD012_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0034    crg_main_aud013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD013_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0038    crg_main_aud014 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD014_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_003C    crg_main_aud015 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__pdm_div_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD015_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0040    crg_main_aud016 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD016_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0044    crg_main_aud017 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD017_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0048    crg_main_aud018 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD018_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_004C    crg_main_aud019 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD019_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0050    crg_main_aud020 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD020_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0054    crg_main_aud021 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD021_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0058    crg_main_aud022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_005C    crg_main_aud023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0060    crg_main_aud024 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel4_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD024_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0064    crg_main_aud025 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel4_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD025_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0068    crg_main_aud026 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel5_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD026_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_006C    crg_main_aud027 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel5_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD027_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0070    crg_main_aud028 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel6_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD028_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0074    crg_main_aud029 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel6_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD029_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0078    crg_main_aud030 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel7_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD030_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_007C    crg_main_aud031 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel7_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD031_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0080    crg_main_aud032 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel8_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD032_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0084    crg_main_aud033 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel8_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD033_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0088    crg_main_aud034 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel9_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD034_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_008C    crg_main_aud035 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel9_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD035_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0090    crg_main_aud036 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_stpo_clk_sel          :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD036_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0094    crg_main_aud037 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_ciout_clk_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD037_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0098    crg_main_aud038 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD038_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_009C    crg_main_aud039 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD039_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A0    crg_main_aud040 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD040_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A4    crg_main_aud041 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD041_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A8    crg_main_aud042 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD042_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00AC    crg_main_aud043 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD043_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B0    crg_main_aud044 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD044_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B4    crg_main_aud045 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD045_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B8    crg_main_aud046 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD046_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00BC    crg_main_aud047 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD047_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C0    crg_main_aud048 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD048_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C4    crg_main_aud049 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD049_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C8    crg_main_aud050 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD050_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00CC    crg_main_aud051 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD051_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D0    crg_main_aud052 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD052_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D4    crg_main_aud053 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD053_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D8    crg_main_aud054 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD054_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00DC    crg_main_aud055 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD055_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E0    crg_main_aud056 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD056_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E4    crg_main_aud057 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD057_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E8    crg_main_aud058 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD058_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00EC    crg_main_aud059 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD059_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F0    crg_main_aud060 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD060_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F4    crg_main_aud061 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD061_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F8    crg_main_aud062 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD062_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00FC    crg_main_aud063 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD063_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0100    crg_main_aud064 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD064_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0104    crg_main_aud065 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD065_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_AUD_CRG_MAIN_AUD000_O26A0_T    crg_main_aud000;    // 0xCE7B_0000
    MCRG_CTRL_AUD_CRG_MAIN_AUD001_O26A0_T    crg_main_aud001;    // 0xCE7B_0004
    MCRG_CTRL_AUD_CRG_MAIN_AUD002_O26A0_T    crg_main_aud002;    // 0xCE7B_0008
    MCRG_CTRL_AUD_CRG_MAIN_AUD003_O26A0_T    crg_main_aud003;    // 0xCE7B_000C
    MCRG_CTRL_AUD_CRG_MAIN_AUD004_O26A0_T    crg_main_aud004;    // 0xCE7B_0010
    MCRG_CTRL_AUD_CRG_MAIN_AUD005_O26A0_T    crg_main_aud005;    // 0xCE7B_0014
    MCRG_CTRL_AUD_CRG_MAIN_AUD006_O26A0_T    crg_main_aud006;    // 0xCE7B_0018
    MCRG_CTRL_AUD_CRG_MAIN_AUD007_O26A0_T    crg_main_aud007;    // 0xCE7B_001C
    MCRG_CTRL_AUD_CRG_MAIN_AUD008_O26A0_T    crg_main_aud008;    // 0xCE7B_0020
    MCRG_CTRL_AUD_CRG_MAIN_AUD009_O26A0_T    crg_main_aud009;    // 0xCE7B_0024
    MCRG_CTRL_AUD_CRG_MAIN_AUD010_O26A0_T    crg_main_aud010;    // 0xCE7B_0028
    MCRG_CTRL_AUD_CRG_MAIN_AUD011_O26A0_T    crg_main_aud011;    // 0xCE7B_002C
    MCRG_CTRL_AUD_CRG_MAIN_AUD012_O26A0_T    crg_main_aud012;    // 0xCE7B_0030
    MCRG_CTRL_AUD_CRG_MAIN_AUD013_O26A0_T    crg_main_aud013;    // 0xCE7B_0034
    MCRG_CTRL_AUD_CRG_MAIN_AUD014_O26A0_T    crg_main_aud014;    // 0xCE7B_0038
    MCRG_CTRL_AUD_CRG_MAIN_AUD015_O26A0_T    crg_main_aud015;    // 0xCE7B_003C
    MCRG_CTRL_AUD_CRG_MAIN_AUD016_O26A0_T    crg_main_aud016;    // 0xCE7B_0040
    MCRG_CTRL_AUD_CRG_MAIN_AUD017_O26A0_T    crg_main_aud017;    // 0xCE7B_0044
    MCRG_CTRL_AUD_CRG_MAIN_AUD018_O26A0_T    crg_main_aud018;    // 0xCE7B_0048
    MCRG_CTRL_AUD_CRG_MAIN_AUD019_O26A0_T    crg_main_aud019;    // 0xCE7B_004C
    MCRG_CTRL_AUD_CRG_MAIN_AUD020_O26A0_T    crg_main_aud020;    // 0xCE7B_0050
    MCRG_CTRL_AUD_CRG_MAIN_AUD021_O26A0_T    crg_main_aud021;    // 0xCE7B_0054
    MCRG_CTRL_AUD_CRG_MAIN_AUD022_O26A0_T    crg_main_aud022;    // 0xCE7B_0058
    MCRG_CTRL_AUD_CRG_MAIN_AUD023_O26A0_T    crg_main_aud023;    // 0xCE7B_005C
    MCRG_CTRL_AUD_CRG_MAIN_AUD024_O26A0_T    crg_main_aud024;    // 0xCE7B_0060
    MCRG_CTRL_AUD_CRG_MAIN_AUD025_O26A0_T    crg_main_aud025;    // 0xCE7B_0064
    MCRG_CTRL_AUD_CRG_MAIN_AUD026_O26A0_T    crg_main_aud026;    // 0xCE7B_0068
    MCRG_CTRL_AUD_CRG_MAIN_AUD027_O26A0_T    crg_main_aud027;    // 0xCE7B_006C
    MCRG_CTRL_AUD_CRG_MAIN_AUD028_O26A0_T    crg_main_aud028;    // 0xCE7B_0070
    MCRG_CTRL_AUD_CRG_MAIN_AUD029_O26A0_T    crg_main_aud029;    // 0xCE7B_0074
    MCRG_CTRL_AUD_CRG_MAIN_AUD030_O26A0_T    crg_main_aud030;    // 0xCE7B_0078
    MCRG_CTRL_AUD_CRG_MAIN_AUD031_O26A0_T    crg_main_aud031;    // 0xCE7B_007C
    MCRG_CTRL_AUD_CRG_MAIN_AUD032_O26A0_T    crg_main_aud032;    // 0xCE7B_0080
    MCRG_CTRL_AUD_CRG_MAIN_AUD033_O26A0_T    crg_main_aud033;    // 0xCE7B_0084
    MCRG_CTRL_AUD_CRG_MAIN_AUD034_O26A0_T    crg_main_aud034;    // 0xCE7B_0088
    MCRG_CTRL_AUD_CRG_MAIN_AUD035_O26A0_T    crg_main_aud035;    // 0xCE7B_008C
    MCRG_CTRL_AUD_CRG_MAIN_AUD036_O26A0_T    crg_main_aud036;    // 0xCE7B_0090
    MCRG_CTRL_AUD_CRG_MAIN_AUD037_O26A0_T    crg_main_aud037;    // 0xCE7B_0094
    MCRG_CTRL_AUD_CRG_MAIN_AUD038_O26A0_T    crg_main_aud038;    // 0xCE7B_0098
    MCRG_CTRL_AUD_CRG_MAIN_AUD039_O26A0_T    crg_main_aud039;    // 0xCE7B_009C
    MCRG_CTRL_AUD_CRG_MAIN_AUD040_O26A0_T    crg_main_aud040;    // 0xCE7B_00A0
    MCRG_CTRL_AUD_CRG_MAIN_AUD041_O26A0_T    crg_main_aud041;    // 0xCE7B_00A4
    MCRG_CTRL_AUD_CRG_MAIN_AUD042_O26A0_T    crg_main_aud042;    // 0xCE7B_00A8
    MCRG_CTRL_AUD_CRG_MAIN_AUD043_O26A0_T    crg_main_aud043;    // 0xCE7B_00AC
    MCRG_CTRL_AUD_CRG_MAIN_AUD044_O26A0_T    crg_main_aud044;    // 0xCE7B_00B0
    MCRG_CTRL_AUD_CRG_MAIN_AUD045_O26A0_T    crg_main_aud045;    // 0xCE7B_00B4
    MCRG_CTRL_AUD_CRG_MAIN_AUD046_O26A0_T    crg_main_aud046;    // 0xCE7B_00B8
    MCRG_CTRL_AUD_CRG_MAIN_AUD047_O26A0_T    crg_main_aud047;    // 0xCE7B_00BC
    MCRG_CTRL_AUD_CRG_MAIN_AUD048_O26A0_T    crg_main_aud048;    // 0xCE7B_00C0
    MCRG_CTRL_AUD_CRG_MAIN_AUD049_O26A0_T    crg_main_aud049;    // 0xCE7B_00C4
    MCRG_CTRL_AUD_CRG_MAIN_AUD050_O26A0_T    crg_main_aud050;    // 0xCE7B_00C8
    MCRG_CTRL_AUD_CRG_MAIN_AUD051_O26A0_T    crg_main_aud051;    // 0xCE7B_00CC
    MCRG_CTRL_AUD_CRG_MAIN_AUD052_O26A0_T    crg_main_aud052;    // 0xCE7B_00D0
    MCRG_CTRL_AUD_CRG_MAIN_AUD053_O26A0_T    crg_main_aud053;    // 0xCE7B_00D4
    MCRG_CTRL_AUD_CRG_MAIN_AUD054_O26A0_T    crg_main_aud054;    // 0xCE7B_00D8
    MCRG_CTRL_AUD_CRG_MAIN_AUD055_O26A0_T    crg_main_aud055;    // 0xCE7B_00DC
    MCRG_CTRL_AUD_CRG_MAIN_AUD056_O26A0_T    crg_main_aud056;    // 0xCE7B_00E0
    MCRG_CTRL_AUD_CRG_MAIN_AUD057_O26A0_T    crg_main_aud057;    // 0xCE7B_00E4
    MCRG_CTRL_AUD_CRG_MAIN_AUD058_O26A0_T    crg_main_aud058;    // 0xCE7B_00E8
    MCRG_CTRL_AUD_CRG_MAIN_AUD059_O26A0_T    crg_main_aud059;    // 0xCE7B_00EC
    MCRG_CTRL_AUD_CRG_MAIN_AUD060_O26A0_T    crg_main_aud060;    // 0xCE7B_00F0
    MCRG_CTRL_AUD_CRG_MAIN_AUD061_O26A0_T    crg_main_aud061;    // 0xCE7B_00F4
    MCRG_CTRL_AUD_CRG_MAIN_AUD062_O26A0_T    crg_main_aud062;    // 0xCE7B_00F8
    MCRG_CTRL_AUD_CRG_MAIN_AUD063_O26A0_T    crg_main_aud063;    // 0xCE7B_00FC
    MCRG_CTRL_AUD_CRG_MAIN_AUD064_O26A0_T    crg_main_aud064;    // 0xCE7B_0100
    MCRG_CTRL_AUD_CRG_MAIN_AUD065_O26A0_T    crg_main_aud065;    // 0xCE7B_0104
}MCRG_CTRL_AUD_REG_O26A0_T;
/* 66 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define MCRG_CTRL_AUD_CRG_MAIN_AUD000_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD001_O26A0_T_OFF           (BASEADDRESS+0x0004)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD002_O26A0_T_OFF           (BASEADDRESS+0x0008)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD003_O26A0_T_OFF           (BASEADDRESS+0x000C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD004_O26A0_T_OFF           (BASEADDRESS+0x0010)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD005_O26A0_T_OFF           (BASEADDRESS+0x0014)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD006_O26A0_T_OFF           (BASEADDRESS+0x0018)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD007_O26A0_T_OFF           (BASEADDRESS+0x001C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD008_O26A0_T_OFF           (BASEADDRESS+0x0020)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD009_O26A0_T_OFF           (BASEADDRESS+0x0024)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD010_O26A0_T_OFF           (BASEADDRESS+0x0028)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD011_O26A0_T_OFF           (BASEADDRESS+0x002C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD012_O26A0_T_OFF           (BASEADDRESS+0x0030)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD013_O26A0_T_OFF           (BASEADDRESS+0x0034)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD014_O26A0_T_OFF           (BASEADDRESS+0x0038)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD015_O26A0_T_OFF           (BASEADDRESS+0x003C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD016_O26A0_T_OFF           (BASEADDRESS+0x0040)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD017_O26A0_T_OFF           (BASEADDRESS+0x0044)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD018_O26A0_T_OFF           (BASEADDRESS+0x0048)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD019_O26A0_T_OFF           (BASEADDRESS+0x004C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD020_O26A0_T_OFF           (BASEADDRESS+0x0050)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD021_O26A0_T_OFF           (BASEADDRESS+0x0054)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD022_O26A0_T_OFF           (BASEADDRESS+0x0058)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD023_O26A0_T_OFF           (BASEADDRESS+0x005C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD024_O26A0_T_OFF           (BASEADDRESS+0x0060)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD025_O26A0_T_OFF           (BASEADDRESS+0x0064)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD026_O26A0_T_OFF           (BASEADDRESS+0x0068)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD027_O26A0_T_OFF           (BASEADDRESS+0x006C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD028_O26A0_T_OFF           (BASEADDRESS+0x0070)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD029_O26A0_T_OFF           (BASEADDRESS+0x0074)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD030_O26A0_T_OFF           (BASEADDRESS+0x0078)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD031_O26A0_T_OFF           (BASEADDRESS+0x007C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD032_O26A0_T_OFF           (BASEADDRESS+0x0080)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD033_O26A0_T_OFF           (BASEADDRESS+0x0084)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD034_O26A0_T_OFF           (BASEADDRESS+0x0088)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD035_O26A0_T_OFF           (BASEADDRESS+0x008C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD036_O26A0_T_OFF           (BASEADDRESS+0x0090)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD037_O26A0_T_OFF           (BASEADDRESS+0x0094)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD038_O26A0_T_OFF           (BASEADDRESS+0x0098)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD039_O26A0_T_OFF           (BASEADDRESS+0x009C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD040_O26A0_T_OFF           (BASEADDRESS+0x00A0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD041_O26A0_T_OFF           (BASEADDRESS+0x00A4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD042_O26A0_T_OFF           (BASEADDRESS+0x00A8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD043_O26A0_T_OFF           (BASEADDRESS+0x00AC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD044_O26A0_T_OFF           (BASEADDRESS+0x00B0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD045_O26A0_T_OFF           (BASEADDRESS+0x00B4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD046_O26A0_T_OFF           (BASEADDRESS+0x00B8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD047_O26A0_T_OFF           (BASEADDRESS+0x00BC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD048_O26A0_T_OFF           (BASEADDRESS+0x00C0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD049_O26A0_T_OFF           (BASEADDRESS+0x00C4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD050_O26A0_T_OFF           (BASEADDRESS+0x00C8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD051_O26A0_T_OFF           (BASEADDRESS+0x00CC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD052_O26A0_T_OFF           (BASEADDRESS+0x00D0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD053_O26A0_T_OFF           (BASEADDRESS+0x00D4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD054_O26A0_T_OFF           (BASEADDRESS+0x00D8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD055_O26A0_T_OFF           (BASEADDRESS+0x00DC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD056_O26A0_T_OFF           (BASEADDRESS+0x00E0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD057_O26A0_T_OFF           (BASEADDRESS+0x00E4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD058_O26A0_T_OFF           (BASEADDRESS+0x00E8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD059_O26A0_T_OFF           (BASEADDRESS+0x00EC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD060_O26A0_T_OFF           (BASEADDRESS+0x00F0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD061_O26A0_T_OFF           (BASEADDRESS+0x00F4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD062_O26A0_T_OFF           (BASEADDRESS+0x00F8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD063_O26A0_T_OFF           (BASEADDRESS+0x00FC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD064_O26A0_T_OFF           (BASEADDRESS+0x0100)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD065_O26A0_T_OFF           (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xCE7B_0000    crg_main_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0004    crg_main_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0008    crg_main_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_apll_f_clk_inv_sel: 1;    //  0
    UINT32 reg_aud_earc_frpll_clk_inv_sel: 1;    //  1
    UINT32 reg_aud_f27m_clk_inv_sel: 1;    //  2
    UINT32 reg_aud_fs00_clk_inv_sel: 1;    //  3
    UINT32 reg_aud_hmr1spdif_m_clk_inv_sel: 1;    //  4
    UINT32 reg_aud_hmr2spdif_m_clk_inv_sel: 1;    //  5
    UINT32 reg_aud_hmr3spdif_m_clk_inv_sel: 1;    //  6
    UINT32 reg_aud_hmr4spdif_m_clk_inv_sel: 1;    //  7
    UINT32 reg_tpo_cam_out_clk_inv_sel: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_000C    crg_main_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0010    crg_main_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0014    crg_main_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0018    crg_main_aud006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_001C    crg_main_aud007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD007_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0020    crg_main_aud008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD008_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0024    crg_main_aud009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD009_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0028    crg_main_aud010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD010_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_002C    crg_main_aud011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD011_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0030    crg_main_aud012 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD012_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0034    crg_main_aud013 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD013_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0038    crg_main_aud014 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD014_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_003C    crg_main_aud015 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud__pdm_div_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD015_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0040    crg_main_aud016 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD016_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0044    crg_main_aud017 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD017_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0048    crg_main_aud018 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD018_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_004C    crg_main_aud019 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD019_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0050    crg_main_aud020 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD020_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0054    crg_main_aud021 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD021_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0058    crg_main_aud022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_005C    crg_main_aud023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0060    crg_main_aud024 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel4_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD024_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0064    crg_main_aud025 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel4_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD025_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0068    crg_main_aud026 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel5_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD026_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_006C    crg_main_aud027 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel5_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD027_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0070    crg_main_aud028 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel6_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD028_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0074    crg_main_aud029 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel6_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD029_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0078    crg_main_aud030 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel7_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD030_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_007C    crg_main_aud031 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel7_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD031_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0080    crg_main_aud032 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel8_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD032_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0084    crg_main_aud033 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel8_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD033_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0088    crg_main_aud034 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel9_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD034_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_008C    crg_main_aud035 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel9_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD035_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0090    crg_main_aud036 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_stpo_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD036_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0094    crg_main_aud037 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_ciout_clk_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD037_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0098    crg_main_aud038 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD038_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_009C    crg_main_aud039 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD039_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A0    crg_main_aud040 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD040_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A4    crg_main_aud041 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD041_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00A8    crg_main_aud042 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD042_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00AC    crg_main_aud043 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD043_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B0    crg_main_aud044 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD044_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B4    crg_main_aud045 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD045_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00B8    crg_main_aud046 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD046_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00BC    crg_main_aud047 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD047_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C0    crg_main_aud048 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD048_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C4    crg_main_aud049 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD049_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00C8    crg_main_aud050 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD050_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00CC    crg_main_aud051 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD051_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D0    crg_main_aud052 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD052_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D4    crg_main_aud053 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD053_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00D8    crg_main_aud054 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD054_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00DC    crg_main_aud055 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD055_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E0    crg_main_aud056 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD056_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E4    crg_main_aud057 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD057_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00E8    crg_main_aud058 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD058_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00EC    crg_main_aud059 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD059_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F0    crg_main_aud060 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD060_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F4    crg_main_aud061 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD061_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00F8    crg_main_aud062 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD062_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_00FC    crg_main_aud063 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD063_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0100    crg_main_aud064 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD064_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_0104    crg_main_aud065 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD065_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_AUD_CRG_MAIN_AUD000_O26A0_T    crg_main_aud000;    // 0xCE7B_0000
    MCRG_CTRL_AUD_CRG_MAIN_AUD001_O26A0_T    crg_main_aud001;    // 0xCE7B_0004
    MCRG_CTRL_AUD_CRG_MAIN_AUD002_O26A0_T    crg_main_aud002;    // 0xCE7B_0008
    MCRG_CTRL_AUD_CRG_MAIN_AUD003_O26A0_T    crg_main_aud003;    // 0xCE7B_000C
    MCRG_CTRL_AUD_CRG_MAIN_AUD004_O26A0_T    crg_main_aud004;    // 0xCE7B_0010
    MCRG_CTRL_AUD_CRG_MAIN_AUD005_O26A0_T    crg_main_aud005;    // 0xCE7B_0014
    MCRG_CTRL_AUD_CRG_MAIN_AUD006_O26A0_T    crg_main_aud006;    // 0xCE7B_0018
    MCRG_CTRL_AUD_CRG_MAIN_AUD007_O26A0_T    crg_main_aud007;    // 0xCE7B_001C
    MCRG_CTRL_AUD_CRG_MAIN_AUD008_O26A0_T    crg_main_aud008;    // 0xCE7B_0020
    MCRG_CTRL_AUD_CRG_MAIN_AUD009_O26A0_T    crg_main_aud009;    // 0xCE7B_0024
    MCRG_CTRL_AUD_CRG_MAIN_AUD010_O26A0_T    crg_main_aud010;    // 0xCE7B_0028
    MCRG_CTRL_AUD_CRG_MAIN_AUD011_O26A0_T    crg_main_aud011;    // 0xCE7B_002C
    MCRG_CTRL_AUD_CRG_MAIN_AUD012_O26A0_T    crg_main_aud012;    // 0xCE7B_0030
    MCRG_CTRL_AUD_CRG_MAIN_AUD013_O26A0_T    crg_main_aud013;    // 0xCE7B_0034
    MCRG_CTRL_AUD_CRG_MAIN_AUD014_O26A0_T    crg_main_aud014;    // 0xCE7B_0038
    MCRG_CTRL_AUD_CRG_MAIN_AUD015_O26A0_T    crg_main_aud015;    // 0xCE7B_003C
    MCRG_CTRL_AUD_CRG_MAIN_AUD016_O26A0_T    crg_main_aud016;    // 0xCE7B_0040
    MCRG_CTRL_AUD_CRG_MAIN_AUD017_O26A0_T    crg_main_aud017;    // 0xCE7B_0044
    MCRG_CTRL_AUD_CRG_MAIN_AUD018_O26A0_T    crg_main_aud018;    // 0xCE7B_0048
    MCRG_CTRL_AUD_CRG_MAIN_AUD019_O26A0_T    crg_main_aud019;    // 0xCE7B_004C
    MCRG_CTRL_AUD_CRG_MAIN_AUD020_O26A0_T    crg_main_aud020;    // 0xCE7B_0050
    MCRG_CTRL_AUD_CRG_MAIN_AUD021_O26A0_T    crg_main_aud021;    // 0xCE7B_0054
    MCRG_CTRL_AUD_CRG_MAIN_AUD022_O26A0_T    crg_main_aud022;    // 0xCE7B_0058
    MCRG_CTRL_AUD_CRG_MAIN_AUD023_O26A0_T    crg_main_aud023;    // 0xCE7B_005C
    MCRG_CTRL_AUD_CRG_MAIN_AUD024_O26A0_T    crg_main_aud024;    // 0xCE7B_0060
    MCRG_CTRL_AUD_CRG_MAIN_AUD025_O26A0_T    crg_main_aud025;    // 0xCE7B_0064
    MCRG_CTRL_AUD_CRG_MAIN_AUD026_O26A0_T    crg_main_aud026;    // 0xCE7B_0068
    MCRG_CTRL_AUD_CRG_MAIN_AUD027_O26A0_T    crg_main_aud027;    // 0xCE7B_006C
    MCRG_CTRL_AUD_CRG_MAIN_AUD028_O26A0_T    crg_main_aud028;    // 0xCE7B_0070
    MCRG_CTRL_AUD_CRG_MAIN_AUD029_O26A0_T    crg_main_aud029;    // 0xCE7B_0074
    MCRG_CTRL_AUD_CRG_MAIN_AUD030_O26A0_T    crg_main_aud030;    // 0xCE7B_0078
    MCRG_CTRL_AUD_CRG_MAIN_AUD031_O26A0_T    crg_main_aud031;    // 0xCE7B_007C
    MCRG_CTRL_AUD_CRG_MAIN_AUD032_O26A0_T    crg_main_aud032;    // 0xCE7B_0080
    MCRG_CTRL_AUD_CRG_MAIN_AUD033_O26A0_T    crg_main_aud033;    // 0xCE7B_0084
    MCRG_CTRL_AUD_CRG_MAIN_AUD034_O26A0_T    crg_main_aud034;    // 0xCE7B_0088
    MCRG_CTRL_AUD_CRG_MAIN_AUD035_O26A0_T    crg_main_aud035;    // 0xCE7B_008C
    MCRG_CTRL_AUD_CRG_MAIN_AUD036_O26A0_T    crg_main_aud036;    // 0xCE7B_0090
    MCRG_CTRL_AUD_CRG_MAIN_AUD037_O26A0_T    crg_main_aud037;    // 0xCE7B_0094
    MCRG_CTRL_AUD_CRG_MAIN_AUD038_O26A0_T    crg_main_aud038;    // 0xCE7B_0098
    MCRG_CTRL_AUD_CRG_MAIN_AUD039_O26A0_T    crg_main_aud039;    // 0xCE7B_009C
    MCRG_CTRL_AUD_CRG_MAIN_AUD040_O26A0_T    crg_main_aud040;    // 0xCE7B_00A0
    MCRG_CTRL_AUD_CRG_MAIN_AUD041_O26A0_T    crg_main_aud041;    // 0xCE7B_00A4
    MCRG_CTRL_AUD_CRG_MAIN_AUD042_O26A0_T    crg_main_aud042;    // 0xCE7B_00A8
    MCRG_CTRL_AUD_CRG_MAIN_AUD043_O26A0_T    crg_main_aud043;    // 0xCE7B_00AC
    MCRG_CTRL_AUD_CRG_MAIN_AUD044_O26A0_T    crg_main_aud044;    // 0xCE7B_00B0
    MCRG_CTRL_AUD_CRG_MAIN_AUD045_O26A0_T    crg_main_aud045;    // 0xCE7B_00B4
    MCRG_CTRL_AUD_CRG_MAIN_AUD046_O26A0_T    crg_main_aud046;    // 0xCE7B_00B8
    MCRG_CTRL_AUD_CRG_MAIN_AUD047_O26A0_T    crg_main_aud047;    // 0xCE7B_00BC
    MCRG_CTRL_AUD_CRG_MAIN_AUD048_O26A0_T    crg_main_aud048;    // 0xCE7B_00C0
    MCRG_CTRL_AUD_CRG_MAIN_AUD049_O26A0_T    crg_main_aud049;    // 0xCE7B_00C4
    MCRG_CTRL_AUD_CRG_MAIN_AUD050_O26A0_T    crg_main_aud050;    // 0xCE7B_00C8
    MCRG_CTRL_AUD_CRG_MAIN_AUD051_O26A0_T    crg_main_aud051;    // 0xCE7B_00CC
    MCRG_CTRL_AUD_CRG_MAIN_AUD052_O26A0_T    crg_main_aud052;    // 0xCE7B_00D0
    MCRG_CTRL_AUD_CRG_MAIN_AUD053_O26A0_T    crg_main_aud053;    // 0xCE7B_00D4
    MCRG_CTRL_AUD_CRG_MAIN_AUD054_O26A0_T    crg_main_aud054;    // 0xCE7B_00D8
    MCRG_CTRL_AUD_CRG_MAIN_AUD055_O26A0_T    crg_main_aud055;    // 0xCE7B_00DC
    MCRG_CTRL_AUD_CRG_MAIN_AUD056_O26A0_T    crg_main_aud056;    // 0xCE7B_00E0
    MCRG_CTRL_AUD_CRG_MAIN_AUD057_O26A0_T    crg_main_aud057;    // 0xCE7B_00E4
    MCRG_CTRL_AUD_CRG_MAIN_AUD058_O26A0_T    crg_main_aud058;    // 0xCE7B_00E8
    MCRG_CTRL_AUD_CRG_MAIN_AUD059_O26A0_T    crg_main_aud059;    // 0xCE7B_00EC
    MCRG_CTRL_AUD_CRG_MAIN_AUD060_O26A0_T    crg_main_aud060;    // 0xCE7B_00F0
    MCRG_CTRL_AUD_CRG_MAIN_AUD061_O26A0_T    crg_main_aud061;    // 0xCE7B_00F4
    MCRG_CTRL_AUD_CRG_MAIN_AUD062_O26A0_T    crg_main_aud062;    // 0xCE7B_00F8
    MCRG_CTRL_AUD_CRG_MAIN_AUD063_O26A0_T    crg_main_aud063;    // 0xCE7B_00FC
    MCRG_CTRL_AUD_CRG_MAIN_AUD064_O26A0_T    crg_main_aud064;    // 0xCE7B_0100
    MCRG_CTRL_AUD_CRG_MAIN_AUD065_O26A0_T    crg_main_aud065;    // 0xCE7B_0104
}MCRG_CTRL_AUD_REG_O26A0_T;
/* 66 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MCRG_CTRL_AUD_REG_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.28  KJH by LGSiCRDV V3.1C*/

