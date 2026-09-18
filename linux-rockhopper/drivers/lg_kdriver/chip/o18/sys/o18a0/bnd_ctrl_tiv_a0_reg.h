#ifndef _BND_CTRL_TIV_A0_REG_H_
#define _BND_CTRL_TIV_A0_REG_H_

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
    0xC987_8000    crg_tiv00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ve_clk_gate_en            :  1,    //      0
    icod_clk_gate_en          :  1,    //      1
    gstcc_if_clk_gate_en      :  1,    //      2
    te_ciout_clk_gate_en      :  1,    //      3
    stpo_clk_gate_en          :  1,    //      4
    ch3_sclk_gate_en          :  1,    //      5
    ch2_sclk_gate_en          :  1,    //      6
    ch1_sclk_gate_en          :  1,    //      7
    ch0_sclk_gate_en          :  1,    //      8
    temcu_clk_gate_en         :  1,    //      9
    te_clk_gate_en            :  1,    //     10
    axi_clk_gate_en           :  1,    //     11
                              : 20;    //  31:12 reserved
}BND_CTRL_TIV_CRG_TIV00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8004    crg_tiv01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    stpi0_clk_inv_sel         :  1,    //      0
    tpi3_clk_inv_sel          :  1,    //      1
    tpi2_clk_inv_sel          :  1,    //      2
    tpi1_clk_inv_sel          :  1,    //      3
    tpi0_clk_inv_sel          :  1,    //      4
    te_ciout_clk_sel          :  3,    //   7: 5
    stpo_clk_sel              :  3,    //  10: 8
    ch3_sclk_sel              :  1,    //     11
    ch2_sclk_sel              :  1,    //     12
    ch1_sclk_sel              :  1,    //     13
    ch0_sclk_sel              :  1,    //     14
                              : 17;    //  31:15 reserved
}BND_CTRL_TIV_CRG_TIV01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8008    crg_tiv02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_ve                  :  1,    //      0
    swrst_ve_apb              :  1,    //      1
    swrst_icod_jpeg           :  1,    //      2
    swrst_gstcc_if            :  1,    //      3
    swrst_ciout               :  1,    //      4
    swrst_stpo                :  1,    //      5
    swrst_te                  :  1,    //      6
    swrst_temcu               :  1,    //      7
    swrst_f_s                 :  1,    //      8
    swrst_ch3_s               :  1,    //      9
    swrst_ch2_s               :  1,    //     10
    swrst_ch1_s               :  1,    //     11
    swrst_ch0_s               :  1,    //     12
    swrst_axi                 :  1,    //     13
                              : 18;    //  31:14 reserved
}BND_CTRL_TIV_CRG_TIV02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_800C    crg_tiv03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_te_wrap0            :  1,    //      0
    swrst_te_wrap1            :  1,    //      1
    swrst_gstc_wrap           :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_TIV_CRG_TIV03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8010    crg_tiv04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    bypass_mode_ch0           :  1,    //      0
    bypass_mode_ch1           :  1,    //      1
    bypass_mode_ch2           :  1,    //      2
    bypass_mode_ch3           :  1,    //      3
    bypass_mode_ch4           :  1,    //      4
    filter_margin_sel_ch0     :  2,    //   6: 5
    filter_margin_sel_ch1     :  2,    //   8: 7
    filter_margin_sel_ch2     :  2,    //  10: 9
    filter_margin_sel_ch3     :  2,    //  12:11
    filter_margin_sel_ch4     :  2,    //  14:13
                              : 17;    //  31:15 reserved
}BND_CTRL_TIV_CRG_TIV04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8014    crg_tiv05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_ch0_gf              :  1,    //      0
    swrst_ch1_gf              :  1,    //      1
    swrst_ch2_gf              :  1,    //      2
    swrst_ch3_gf              :  1,    //      3
    swrst_ch4_gf              :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_TIV_CRG_TIV05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8018    crg_tiv06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    j3_tuner_clk_sel          :  1,    //      0
    j3_tuner_int_sel          :  1,    //      1
    j3_tuner_sop_sel          :  1,    //      2
    j3_tuner_data_sel         :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_TIV_CRG_TIV06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_801C    flush_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    te_flush_en               :  1,    //      0
    icod_flush_en             :  1,    //      1
    venc_flush_en             :  1,    //      2
    icod_awcache              :  1,    //      3
    icod_arcache              :  1,    //      4
    venc_awcache              :  1,    //      5
    venc_arcache              :  1,    //      6
                              : 25;    //   31:7 reserved
}BND_CTRL_TIV_FLUSH_CTRL00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC987_8020    flush_done00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    te_flush_done             :  1,    //      0
    icod_flush_done           :  1,    //      1
    venc_flush_done           :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_TIV_FLUSH_DONE00_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_tiv Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_TIV_CRG_TIV00_O18_A0                crg_tiv00                ;         // 0xC987_8000
BND_CTRL_TIV_CRG_TIV01_O18_A0                crg_tiv01                ;         // 0xC987_8004
BND_CTRL_TIV_CRG_TIV02_O18_A0                crg_tiv02                ;         // 0xC987_8008
BND_CTRL_TIV_CRG_TIV03_O18_A0                crg_tiv03                ;         // 0xC987_800C
BND_CTRL_TIV_CRG_TIV04_O18_A0                crg_tiv04                ;         // 0xC987_8010
BND_CTRL_TIV_CRG_TIV05_O18_A0                crg_tiv05                ;         // 0xC987_8014
BND_CTRL_TIV_CRG_TIV06_O18_A0                crg_tiv06                ;         // 0xC987_8018
BND_CTRL_TIV_FLUSH_CTRL00_O18_A0             flush_ctrl00             ;         // 0xC987_801C
BND_CTRL_TIV_FLUSH_DONE00_O18_A0             flush_done00             ;         // 0xC987_8020
} BND_CTRL_TIV_REG_O18_A0;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_TIV_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

