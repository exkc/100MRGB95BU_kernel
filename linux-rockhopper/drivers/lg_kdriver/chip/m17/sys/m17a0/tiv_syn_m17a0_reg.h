#ifndef _TIV_SYN_M17A0_REG_H_
#define _TIV_SYN_M17A0_REG_H_

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
    0xC9C5_0000    crg_te00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    axi_clk_gate_en           :  1,    //      0
    te_clk_gate_en            :  1,    //      1
    temcu_clk_gate_en         :  1,    //      2
    ch0_sclk_gate_en          :  1,    //      3
    ch1_sclk_gate_en          :  1,    //      4
    ch2_sclk_gate_en          :  1,    //      5
    ch3_sclk_gate_en          :  1,    //      6
    stpo_clk_gate_en          :  1,    //      7
    te_ciout_clk_gate_en      :  1,    //      8
    gstcc_if_clk_gate_en      :  1,    //      9
    icod_clk_gate_en          :  1,    //     10
                              :  1,    //     11 reserved
    ch0_sclk_sel              :  1,    //     12
    ch1_sclk_sel              :  1,    //     13
    ch2_sclk_sel              :  1,    //     14
    ch3_sclk_sel              :  1,    //     15
    stpo_clk_sel              :  3,    //  18:16
    te_ciout_clk_sel          :  3,    //  21:19
    tpi0_clk_inv_sel          :  1,    //     22
    tpi1_clk_inv_sel          :  1,    //     23
    tpi2_clk_inv_sel          :  1,    //     24
    tpi3_clk_inv_sel          :  1,    //     25
                              :  1,    //     26 reserved
    stpi0_clk_inv_sel         :  1,    //     27
                              :  4;    //  31:28 reserved
}TIV_SYN_CRG_TE00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_0004    crg_te01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_axi                 :  1,    //      0
    swrst_ch0_s               :  1,    //      1
    swrst_ch1_s               :  1,    //      2
    swrst_ch2_s               :  1,    //      3
    swrst_ch3_s               :  1,    //      4
    swrst_f_s                 :  1,    //      5
    swrst_temcu               :  1,    //      6
    swrst_te                  :  1,    //      7
    swrst_stpo                :  1,    //      8
    swrst_ciout               :  1,    //      9
    swrst_gstcc_if            :  1,    //     10
    swrst_icod_jpeg           :  1,    //     11
                              : 20;    //  31:12 reserved
}TIV_SYN_CRG_TE01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_0008    syn_tiv00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}TIV_SYN_SYN_TIV00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_000C    syn_tiv01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}TIV_SYN_SYN_TIV01_M17_A0;

/*-----------------------------------------------------------------------------------------
    tiv_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
TIV_SYN_CRG_TE00_M17_A0                      crg_te00                 ;         // 0xC9C5_0000
TIV_SYN_CRG_TE01_M17_A0                      crg_te01                 ;         // 0xC9C5_0004
TIV_SYN_SYN_TIV00_M17_A0                     syn_tiv00                ;         // 0xC9C5_0008
TIV_SYN_SYN_TIV01_M17_A0                     syn_tiv01                ;         // 0xC9C5_000C
} TIV_SYN_REG_M17_A0;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _TIV_SYN_M17A0_REG_H_ */

/* from 'M16PP_CTOP_SYN_Register_Manual_52.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

