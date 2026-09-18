#ifndef _MCRG_CTRL_AUD_REG_O24A0_H_
#define _MCRG_CTRL_AUD_REG_O24A0_H_

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
    0xCE49_0000    crg_main_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reserved             :  4,    //   3: 0
    reg_sel8_aclk_src         :  4,    //   7: 4
    reg_sel8_aclk_div         :  3,    //  10: 8
    test_reserved             : 21;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0004    crg_main_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0008    crg_main_aud2 ''
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
}MCRG_CTRL_AUD_CRG_MAIN_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_000C    crg_main_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0010    crg_main_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0014    crg_main_aud5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0018    crg_main_aud6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_001C    crg_main_aud7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0020    crg_main_aud8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD8_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0024    crg_main_aud9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD9_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0028    crg_main_aud10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_002C    crg_main_aud11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_AUD_CRG_MAIN_AUD11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0030    crg_main_aud12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0034    crg_main_aud13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0038    crg_main_aud14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_003C    crg_main_aud15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud__pdm_div_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0040    crg_main_aud16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD16_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0044    crg_main_aud17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD17_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0048    crg_main_aud18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD18_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_004C    crg_main_aud19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD19_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0050    crg_main_aud20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0054    crg_main_aud21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0058    crg_main_aud22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_005C    crg_main_aud23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0060    crg_main_aud24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel4_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0064    crg_main_aud25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel4_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD25_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0068    crg_main_aud26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel5_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD26_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_006C    crg_main_aud27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel5_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD27_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0070    crg_main_aud28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel6_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD28_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0074    crg_main_aud29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel6_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD29_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0078    crg_main_aud30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel7_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD30_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_007C    crg_main_aud31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel7_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD31_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0080    crg_main_aud32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_stpo_clk_sel          :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD32_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0084    crg_main_aud33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_ciout_clk_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD33_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0088    crg_main_aud34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD34_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_008C    crg_main_aud35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD35_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0090    crg_main_aud36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD36_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0094    crg_main_aud37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD37_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0098    crg_main_aud38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD38_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_009C    crg_main_aud39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD39_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A0    crg_main_aud40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD40_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A4    crg_main_aud41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD41_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A8    crg_main_aud42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD42_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00AC    crg_main_aud43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD43_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B0    crg_main_aud44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD44_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B4    crg_main_aud45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD45_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B8    crg_main_aud46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD46_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00BC    crg_main_aud47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD47_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C0    crg_main_aud48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD48_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C4    crg_main_aud49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD49_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C8    crg_main_aud50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD50_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00CC    crg_main_aud51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD51_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D0    crg_main_aud52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD52_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D4    crg_main_aud53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD53_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D8    crg_main_aud54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD54_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00DC    crg_main_aud55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD55_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E0    crg_main_aud56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD56_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E4    crg_main_aud57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD57_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E8    crg_main_aud58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD58_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00EC    crg_main_aud59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD59_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00F0    crg_main_aud60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD60_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00F4    crg_main_aud61 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_AUD_CRG_MAIN_AUD61_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_AUD_CRG_MAIN_AUD0_O24A0_T    crg_main_aud0;       // 0xCE49_0000
    MCRG_CTRL_AUD_CRG_MAIN_AUD1_O24A0_T    crg_main_aud1;       // 0xCE49_0004
    MCRG_CTRL_AUD_CRG_MAIN_AUD2_O24A0_T    crg_main_aud2;       // 0xCE49_0008
    MCRG_CTRL_AUD_CRG_MAIN_AUD3_O24A0_T    crg_main_aud3;       // 0xCE49_000C
    MCRG_CTRL_AUD_CRG_MAIN_AUD4_O24A0_T    crg_main_aud4;       // 0xCE49_0010
    MCRG_CTRL_AUD_CRG_MAIN_AUD5_O24A0_T    crg_main_aud5;       // 0xCE49_0014
    MCRG_CTRL_AUD_CRG_MAIN_AUD6_O24A0_T    crg_main_aud6;       // 0xCE49_0018
    MCRG_CTRL_AUD_CRG_MAIN_AUD7_O24A0_T    crg_main_aud7;       // 0xCE49_001C
    MCRG_CTRL_AUD_CRG_MAIN_AUD8_O24A0_T    crg_main_aud8;       // 0xCE49_0020
    MCRG_CTRL_AUD_CRG_MAIN_AUD9_O24A0_T    crg_main_aud9;       // 0xCE49_0024
    MCRG_CTRL_AUD_CRG_MAIN_AUD10_O24A0_T    crg_main_aud10;     // 0xCE49_0028
    MCRG_CTRL_AUD_CRG_MAIN_AUD11_O24A0_T    crg_main_aud11;     // 0xCE49_002C
    MCRG_CTRL_AUD_CRG_MAIN_AUD12_O24A0_T    crg_main_aud12;     // 0xCE49_0030
    MCRG_CTRL_AUD_CRG_MAIN_AUD13_O24A0_T    crg_main_aud13;     // 0xCE49_0034
    MCRG_CTRL_AUD_CRG_MAIN_AUD14_O24A0_T    crg_main_aud14;     // 0xCE49_0038
    MCRG_CTRL_AUD_CRG_MAIN_AUD15_O24A0_T    crg_main_aud15;     // 0xCE49_003C
    MCRG_CTRL_AUD_CRG_MAIN_AUD16_O24A0_T    crg_main_aud16;     // 0xCE49_0040
    MCRG_CTRL_AUD_CRG_MAIN_AUD17_O24A0_T    crg_main_aud17;     // 0xCE49_0044
    MCRG_CTRL_AUD_CRG_MAIN_AUD18_O24A0_T    crg_main_aud18;     // 0xCE49_0048
    MCRG_CTRL_AUD_CRG_MAIN_AUD19_O24A0_T    crg_main_aud19;     // 0xCE49_004C
    MCRG_CTRL_AUD_CRG_MAIN_AUD20_O24A0_T    crg_main_aud20;     // 0xCE49_0050
    MCRG_CTRL_AUD_CRG_MAIN_AUD21_O24A0_T    crg_main_aud21;     // 0xCE49_0054
    MCRG_CTRL_AUD_CRG_MAIN_AUD22_O24A0_T    crg_main_aud22;     // 0xCE49_0058
    MCRG_CTRL_AUD_CRG_MAIN_AUD23_O24A0_T    crg_main_aud23;     // 0xCE49_005C
    MCRG_CTRL_AUD_CRG_MAIN_AUD24_O24A0_T    crg_main_aud24;     // 0xCE49_0060
    MCRG_CTRL_AUD_CRG_MAIN_AUD25_O24A0_T    crg_main_aud25;     // 0xCE49_0064
    MCRG_CTRL_AUD_CRG_MAIN_AUD26_O24A0_T    crg_main_aud26;     // 0xCE49_0068
    MCRG_CTRL_AUD_CRG_MAIN_AUD27_O24A0_T    crg_main_aud27;     // 0xCE49_006C
    MCRG_CTRL_AUD_CRG_MAIN_AUD28_O24A0_T    crg_main_aud28;     // 0xCE49_0070
    MCRG_CTRL_AUD_CRG_MAIN_AUD29_O24A0_T    crg_main_aud29;     // 0xCE49_0074
    MCRG_CTRL_AUD_CRG_MAIN_AUD30_O24A0_T    crg_main_aud30;     // 0xCE49_0078
    MCRG_CTRL_AUD_CRG_MAIN_AUD31_O24A0_T    crg_main_aud31;     // 0xCE49_007C
    MCRG_CTRL_AUD_CRG_MAIN_AUD32_O24A0_T    crg_main_aud32;     // 0xCE49_0080
    MCRG_CTRL_AUD_CRG_MAIN_AUD33_O24A0_T    crg_main_aud33;     // 0xCE49_0084
    MCRG_CTRL_AUD_CRG_MAIN_AUD34_O24A0_T    crg_main_aud34;     // 0xCE49_0088
    MCRG_CTRL_AUD_CRG_MAIN_AUD35_O24A0_T    crg_main_aud35;     // 0xCE49_008C
    MCRG_CTRL_AUD_CRG_MAIN_AUD36_O24A0_T    crg_main_aud36;     // 0xCE49_0090
    MCRG_CTRL_AUD_CRG_MAIN_AUD37_O24A0_T    crg_main_aud37;     // 0xCE49_0094
    MCRG_CTRL_AUD_CRG_MAIN_AUD38_O24A0_T    crg_main_aud38;     // 0xCE49_0098
    MCRG_CTRL_AUD_CRG_MAIN_AUD39_O24A0_T    crg_main_aud39;     // 0xCE49_009C
    MCRG_CTRL_AUD_CRG_MAIN_AUD40_O24A0_T    crg_main_aud40;     // 0xCE49_00A0
    MCRG_CTRL_AUD_CRG_MAIN_AUD41_O24A0_T    crg_main_aud41;     // 0xCE49_00A4
    MCRG_CTRL_AUD_CRG_MAIN_AUD42_O24A0_T    crg_main_aud42;     // 0xCE49_00A8
    MCRG_CTRL_AUD_CRG_MAIN_AUD43_O24A0_T    crg_main_aud43;     // 0xCE49_00AC
    MCRG_CTRL_AUD_CRG_MAIN_AUD44_O24A0_T    crg_main_aud44;     // 0xCE49_00B0
    MCRG_CTRL_AUD_CRG_MAIN_AUD45_O24A0_T    crg_main_aud45;     // 0xCE49_00B4
    MCRG_CTRL_AUD_CRG_MAIN_AUD46_O24A0_T    crg_main_aud46;     // 0xCE49_00B8
    MCRG_CTRL_AUD_CRG_MAIN_AUD47_O24A0_T    crg_main_aud47;     // 0xCE49_00BC
    MCRG_CTRL_AUD_CRG_MAIN_AUD48_O24A0_T    crg_main_aud48;     // 0xCE49_00C0
    MCRG_CTRL_AUD_CRG_MAIN_AUD49_O24A0_T    crg_main_aud49;     // 0xCE49_00C4
    MCRG_CTRL_AUD_CRG_MAIN_AUD50_O24A0_T    crg_main_aud50;     // 0xCE49_00C8
    MCRG_CTRL_AUD_CRG_MAIN_AUD51_O24A0_T    crg_main_aud51;     // 0xCE49_00CC
    MCRG_CTRL_AUD_CRG_MAIN_AUD52_O24A0_T    crg_main_aud52;     // 0xCE49_00D0
    MCRG_CTRL_AUD_CRG_MAIN_AUD53_O24A0_T    crg_main_aud53;     // 0xCE49_00D4
    MCRG_CTRL_AUD_CRG_MAIN_AUD54_O24A0_T    crg_main_aud54;     // 0xCE49_00D8
    MCRG_CTRL_AUD_CRG_MAIN_AUD55_O24A0_T    crg_main_aud55;     // 0xCE49_00DC
    MCRG_CTRL_AUD_CRG_MAIN_AUD56_O24A0_T    crg_main_aud56;     // 0xCE49_00E0
    MCRG_CTRL_AUD_CRG_MAIN_AUD57_O24A0_T    crg_main_aud57;     // 0xCE49_00E4
    MCRG_CTRL_AUD_CRG_MAIN_AUD58_O24A0_T    crg_main_aud58;     // 0xCE49_00E8
    MCRG_CTRL_AUD_CRG_MAIN_AUD59_O24A0_T    crg_main_aud59;     // 0xCE49_00EC
    MCRG_CTRL_AUD_CRG_MAIN_AUD60_O24A0_T    crg_main_aud60;     // 0xCE49_00F0
    MCRG_CTRL_AUD_CRG_MAIN_AUD61_O24A0_T    crg_main_aud61;     // 0xCE49_00F4
}MCRG_CTRL_AUD_REG_O24A0_T;
/* 62 regs */

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

#define MCRG_CTRL_AUD_CRG_MAIN_AUD0_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD1_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD2_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD3_O24A0_T_OFF             (BASEADDRESS+0x000C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD4_O24A0_T_OFF             (BASEADDRESS+0x0010)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD5_O24A0_T_OFF             (BASEADDRESS+0x0014)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD6_O24A0_T_OFF             (BASEADDRESS+0x0018)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD7_O24A0_T_OFF             (BASEADDRESS+0x001C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD8_O24A0_T_OFF             (BASEADDRESS+0x0020)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD9_O24A0_T_OFF             (BASEADDRESS+0x0024)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD10_O24A0_T_OFF            (BASEADDRESS+0x0028)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD11_O24A0_T_OFF            (BASEADDRESS+0x002C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD12_O24A0_T_OFF            (BASEADDRESS+0x0030)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD13_O24A0_T_OFF            (BASEADDRESS+0x0034)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD14_O24A0_T_OFF            (BASEADDRESS+0x0038)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD15_O24A0_T_OFF            (BASEADDRESS+0x003C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD16_O24A0_T_OFF            (BASEADDRESS+0x0040)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD17_O24A0_T_OFF            (BASEADDRESS+0x0044)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD18_O24A0_T_OFF            (BASEADDRESS+0x0048)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD19_O24A0_T_OFF            (BASEADDRESS+0x004C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD20_O24A0_T_OFF            (BASEADDRESS+0x0050)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD21_O24A0_T_OFF            (BASEADDRESS+0x0054)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD22_O24A0_T_OFF            (BASEADDRESS+0x0058)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD23_O24A0_T_OFF            (BASEADDRESS+0x005C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD24_O24A0_T_OFF            (BASEADDRESS+0x0060)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD25_O24A0_T_OFF            (BASEADDRESS+0x0064)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD26_O24A0_T_OFF            (BASEADDRESS+0x0068)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD27_O24A0_T_OFF            (BASEADDRESS+0x006C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD28_O24A0_T_OFF            (BASEADDRESS+0x0070)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD29_O24A0_T_OFF            (BASEADDRESS+0x0074)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD30_O24A0_T_OFF            (BASEADDRESS+0x0078)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD31_O24A0_T_OFF            (BASEADDRESS+0x007C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD32_O24A0_T_OFF            (BASEADDRESS+0x0080)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD33_O24A0_T_OFF            (BASEADDRESS+0x0084)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD34_O24A0_T_OFF            (BASEADDRESS+0x0088)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD35_O24A0_T_OFF            (BASEADDRESS+0x008C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD36_O24A0_T_OFF            (BASEADDRESS+0x0090)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD37_O24A0_T_OFF            (BASEADDRESS+0x0094)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD38_O24A0_T_OFF            (BASEADDRESS+0x0098)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD39_O24A0_T_OFF            (BASEADDRESS+0x009C)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD40_O24A0_T_OFF            (BASEADDRESS+0x00A0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD41_O24A0_T_OFF            (BASEADDRESS+0x00A4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD42_O24A0_T_OFF            (BASEADDRESS+0x00A8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD43_O24A0_T_OFF            (BASEADDRESS+0x00AC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD44_O24A0_T_OFF            (BASEADDRESS+0x00B0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD45_O24A0_T_OFF            (BASEADDRESS+0x00B4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD46_O24A0_T_OFF            (BASEADDRESS+0x00B8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD47_O24A0_T_OFF            (BASEADDRESS+0x00BC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD48_O24A0_T_OFF            (BASEADDRESS+0x00C0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD49_O24A0_T_OFF            (BASEADDRESS+0x00C4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD50_O24A0_T_OFF            (BASEADDRESS+0x00C8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD51_O24A0_T_OFF            (BASEADDRESS+0x00CC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD52_O24A0_T_OFF            (BASEADDRESS+0x00D0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD53_O24A0_T_OFF            (BASEADDRESS+0x00D4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD54_O24A0_T_OFF            (BASEADDRESS+0x00D8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD55_O24A0_T_OFF            (BASEADDRESS+0x00DC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD56_O24A0_T_OFF            (BASEADDRESS+0x00E0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD57_O24A0_T_OFF            (BASEADDRESS+0x00E4)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD58_O24A0_T_OFF            (BASEADDRESS+0x00E8)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD59_O24A0_T_OFF            (BASEADDRESS+0x00EC)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD60_O24A0_T_OFF            (BASEADDRESS+0x00F0)
#define MCRG_CTRL_AUD_CRG_MAIN_AUD61_O24A0_T_OFF            (BASEADDRESS+0x00F4)

/*-----------------------------------------------------------------------------------------
    0xCE49_0000    crg_main_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0004    crg_main_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0008    crg_main_aud2 ''
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
}MCRG_CTRL_AUD_CRG_MAIN_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_000C    crg_main_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0010    crg_main_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0014    crg_main_aud5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0018    crg_main_aud6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_001C    crg_main_aud7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0020    crg_main_aud8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD8_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0024    crg_main_aud9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD9_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0028    crg_main_aud10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_002C    crg_main_aud11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0030    crg_main_aud12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0034    crg_main_aud13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0038    crg_main_aud14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_003C    crg_main_aud15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud__pdm_div_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0040    crg_main_aud16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD16_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0044    crg_main_aud17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD17_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0048    crg_main_aud18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD18_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_004C    crg_main_aud19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD19_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0050    crg_main_aud20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0054    crg_main_aud21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0058    crg_main_aud22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_005C    crg_main_aud23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0060    crg_main_aud24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel4_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0064    crg_main_aud25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel4_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD25_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0068    crg_main_aud26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel5_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD26_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_006C    crg_main_aud27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel5_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD27_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0070    crg_main_aud28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel6_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD28_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0074    crg_main_aud29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel6_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD29_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0078    crg_main_aud30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel7_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD30_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_007C    crg_main_aud31 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel7_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD31_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0080    crg_main_aud32 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_stpo_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD32_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0084    crg_main_aud33 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_ciout_clk_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD33_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0088    crg_main_aud34 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD34_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_008C    crg_main_aud35 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD35_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0090    crg_main_aud36 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD36_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0094    crg_main_aud37 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD37_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0098    crg_main_aud38 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD38_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_009C    crg_main_aud39 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD39_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A0    crg_main_aud40 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD40_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A4    crg_main_aud41 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD41_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00A8    crg_main_aud42 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD42_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00AC    crg_main_aud43 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD43_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B0    crg_main_aud44 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD44_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B4    crg_main_aud45 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD45_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00B8    crg_main_aud46 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD46_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00BC    crg_main_aud47 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD47_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C0    crg_main_aud48 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD48_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C4    crg_main_aud49 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD49_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00C8    crg_main_aud50 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD50_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00CC    crg_main_aud51 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD51_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D0    crg_main_aud52 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD52_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D4    crg_main_aud53 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD53_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00D8    crg_main_aud54 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD54_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00DC    crg_main_aud55 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD55_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E0    crg_main_aud56 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD56_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E4    crg_main_aud57 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD57_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00E8    crg_main_aud58 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD58_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00EC    crg_main_aud59 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD59_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00F0    crg_main_aud60 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD60_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_00F4    crg_main_aud61 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_AUD_CRG_MAIN_AUD61_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_AUD_CRG_MAIN_AUD0_O24A0_T    crg_main_aud0;       // 0xCE49_0000
    MCRG_CTRL_AUD_CRG_MAIN_AUD1_O24A0_T    crg_main_aud1;       // 0xCE49_0004
    MCRG_CTRL_AUD_CRG_MAIN_AUD2_O24A0_T    crg_main_aud2;       // 0xCE49_0008
    MCRG_CTRL_AUD_CRG_MAIN_AUD3_O24A0_T    crg_main_aud3;       // 0xCE49_000C
    MCRG_CTRL_AUD_CRG_MAIN_AUD4_O24A0_T    crg_main_aud4;       // 0xCE49_0010
    MCRG_CTRL_AUD_CRG_MAIN_AUD5_O24A0_T    crg_main_aud5;       // 0xCE49_0014
    MCRG_CTRL_AUD_CRG_MAIN_AUD6_O24A0_T    crg_main_aud6;       // 0xCE49_0018
    MCRG_CTRL_AUD_CRG_MAIN_AUD7_O24A0_T    crg_main_aud7;       // 0xCE49_001C
    MCRG_CTRL_AUD_CRG_MAIN_AUD8_O24A0_T    crg_main_aud8;       // 0xCE49_0020
    MCRG_CTRL_AUD_CRG_MAIN_AUD9_O24A0_T    crg_main_aud9;       // 0xCE49_0024
    MCRG_CTRL_AUD_CRG_MAIN_AUD10_O24A0_T    crg_main_aud10;     // 0xCE49_0028
    MCRG_CTRL_AUD_CRG_MAIN_AUD11_O24A0_T    crg_main_aud11;     // 0xCE49_002C
    MCRG_CTRL_AUD_CRG_MAIN_AUD12_O24A0_T    crg_main_aud12;     // 0xCE49_0030
    MCRG_CTRL_AUD_CRG_MAIN_AUD13_O24A0_T    crg_main_aud13;     // 0xCE49_0034
    MCRG_CTRL_AUD_CRG_MAIN_AUD14_O24A0_T    crg_main_aud14;     // 0xCE49_0038
    MCRG_CTRL_AUD_CRG_MAIN_AUD15_O24A0_T    crg_main_aud15;     // 0xCE49_003C
    MCRG_CTRL_AUD_CRG_MAIN_AUD16_O24A0_T    crg_main_aud16;     // 0xCE49_0040
    MCRG_CTRL_AUD_CRG_MAIN_AUD17_O24A0_T    crg_main_aud17;     // 0xCE49_0044
    MCRG_CTRL_AUD_CRG_MAIN_AUD18_O24A0_T    crg_main_aud18;     // 0xCE49_0048
    MCRG_CTRL_AUD_CRG_MAIN_AUD19_O24A0_T    crg_main_aud19;     // 0xCE49_004C
    MCRG_CTRL_AUD_CRG_MAIN_AUD20_O24A0_T    crg_main_aud20;     // 0xCE49_0050
    MCRG_CTRL_AUD_CRG_MAIN_AUD21_O24A0_T    crg_main_aud21;     // 0xCE49_0054
    MCRG_CTRL_AUD_CRG_MAIN_AUD22_O24A0_T    crg_main_aud22;     // 0xCE49_0058
    MCRG_CTRL_AUD_CRG_MAIN_AUD23_O24A0_T    crg_main_aud23;     // 0xCE49_005C
    MCRG_CTRL_AUD_CRG_MAIN_AUD24_O24A0_T    crg_main_aud24;     // 0xCE49_0060
    MCRG_CTRL_AUD_CRG_MAIN_AUD25_O24A0_T    crg_main_aud25;     // 0xCE49_0064
    MCRG_CTRL_AUD_CRG_MAIN_AUD26_O24A0_T    crg_main_aud26;     // 0xCE49_0068
    MCRG_CTRL_AUD_CRG_MAIN_AUD27_O24A0_T    crg_main_aud27;     // 0xCE49_006C
    MCRG_CTRL_AUD_CRG_MAIN_AUD28_O24A0_T    crg_main_aud28;     // 0xCE49_0070
    MCRG_CTRL_AUD_CRG_MAIN_AUD29_O24A0_T    crg_main_aud29;     // 0xCE49_0074
    MCRG_CTRL_AUD_CRG_MAIN_AUD30_O24A0_T    crg_main_aud30;     // 0xCE49_0078
    MCRG_CTRL_AUD_CRG_MAIN_AUD31_O24A0_T    crg_main_aud31;     // 0xCE49_007C
    MCRG_CTRL_AUD_CRG_MAIN_AUD32_O24A0_T    crg_main_aud32;     // 0xCE49_0080
    MCRG_CTRL_AUD_CRG_MAIN_AUD33_O24A0_T    crg_main_aud33;     // 0xCE49_0084
    MCRG_CTRL_AUD_CRG_MAIN_AUD34_O24A0_T    crg_main_aud34;     // 0xCE49_0088
    MCRG_CTRL_AUD_CRG_MAIN_AUD35_O24A0_T    crg_main_aud35;     // 0xCE49_008C
    MCRG_CTRL_AUD_CRG_MAIN_AUD36_O24A0_T    crg_main_aud36;     // 0xCE49_0090
    MCRG_CTRL_AUD_CRG_MAIN_AUD37_O24A0_T    crg_main_aud37;     // 0xCE49_0094
    MCRG_CTRL_AUD_CRG_MAIN_AUD38_O24A0_T    crg_main_aud38;     // 0xCE49_0098
    MCRG_CTRL_AUD_CRG_MAIN_AUD39_O24A0_T    crg_main_aud39;     // 0xCE49_009C
    MCRG_CTRL_AUD_CRG_MAIN_AUD40_O24A0_T    crg_main_aud40;     // 0xCE49_00A0
    MCRG_CTRL_AUD_CRG_MAIN_AUD41_O24A0_T    crg_main_aud41;     // 0xCE49_00A4
    MCRG_CTRL_AUD_CRG_MAIN_AUD42_O24A0_T    crg_main_aud42;     // 0xCE49_00A8
    MCRG_CTRL_AUD_CRG_MAIN_AUD43_O24A0_T    crg_main_aud43;     // 0xCE49_00AC
    MCRG_CTRL_AUD_CRG_MAIN_AUD44_O24A0_T    crg_main_aud44;     // 0xCE49_00B0
    MCRG_CTRL_AUD_CRG_MAIN_AUD45_O24A0_T    crg_main_aud45;     // 0xCE49_00B4
    MCRG_CTRL_AUD_CRG_MAIN_AUD46_O24A0_T    crg_main_aud46;     // 0xCE49_00B8
    MCRG_CTRL_AUD_CRG_MAIN_AUD47_O24A0_T    crg_main_aud47;     // 0xCE49_00BC
    MCRG_CTRL_AUD_CRG_MAIN_AUD48_O24A0_T    crg_main_aud48;     // 0xCE49_00C0
    MCRG_CTRL_AUD_CRG_MAIN_AUD49_O24A0_T    crg_main_aud49;     // 0xCE49_00C4
    MCRG_CTRL_AUD_CRG_MAIN_AUD50_O24A0_T    crg_main_aud50;     // 0xCE49_00C8
    MCRG_CTRL_AUD_CRG_MAIN_AUD51_O24A0_T    crg_main_aud51;     // 0xCE49_00CC
    MCRG_CTRL_AUD_CRG_MAIN_AUD52_O24A0_T    crg_main_aud52;     // 0xCE49_00D0
    MCRG_CTRL_AUD_CRG_MAIN_AUD53_O24A0_T    crg_main_aud53;     // 0xCE49_00D4
    MCRG_CTRL_AUD_CRG_MAIN_AUD54_O24A0_T    crg_main_aud54;     // 0xCE49_00D8
    MCRG_CTRL_AUD_CRG_MAIN_AUD55_O24A0_T    crg_main_aud55;     // 0xCE49_00DC
    MCRG_CTRL_AUD_CRG_MAIN_AUD56_O24A0_T    crg_main_aud56;     // 0xCE49_00E0
    MCRG_CTRL_AUD_CRG_MAIN_AUD57_O24A0_T    crg_main_aud57;     // 0xCE49_00E4
    MCRG_CTRL_AUD_CRG_MAIN_AUD58_O24A0_T    crg_main_aud58;     // 0xCE49_00E8
    MCRG_CTRL_AUD_CRG_MAIN_AUD59_O24A0_T    crg_main_aud59;     // 0xCE49_00EC
    MCRG_CTRL_AUD_CRG_MAIN_AUD60_O24A0_T    crg_main_aud60;     // 0xCE49_00F0
    MCRG_CTRL_AUD_CRG_MAIN_AUD61_O24A0_T    crg_main_aud61;     // 0xCE49_00F4
}MCRG_CTRL_AUD_REG_O24A0_T;
/* 62 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MCRG_CTRL_AUD_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

