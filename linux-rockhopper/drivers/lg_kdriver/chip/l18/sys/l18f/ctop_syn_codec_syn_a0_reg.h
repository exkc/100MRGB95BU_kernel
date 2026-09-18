#ifndef _CTOP_SYN_CODEC_SYN_A0_REG_H_
#define _CTOP_SYN_CODEC_SYN_A0_REG_H_

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
    0xC9C5_0000    crg_codec00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    te_ciout_clk_sel          :  2,    //   1: 0
    te_ch2_sclk_sel           :  1,    //      2
    te_ch1_sclk_sel           :  1,    //      3
    te_ch0_sclk_sel           :  1,    //      4
                              :  3,    //   7: 5 reserved
    tpi4_clk_inv_sel          :  1,    //      8
    tpi3_clk_inv_sel          :  1,    //      9
    tpi2_clk_inv_sel          :  1,    //     10
    tpi1_clk_inv_sel          :  1,    //     11
    tpi0_clk_inv_sel          :  1,    //     12
    fs00_clk_inv_sel          :  1,    //     13
    aud_hmr1spdifclk_inv_sel  :  1,    //     14
    aud_hmr0spdifclk_inv_sel  :  1,    //     15
    aud_fs25clk_inv_sel       :  1,    //     16
    aud_fs24clk_inv_sel       :  1,    //     17
    aud_fs23clk_inv_sel       :  1,    //     18
    aud_fs22clk_inv_sel       :  1,    //     19
    aud_fs21clk_inv_sel       :  1,    //     20
    aud_fs20clk_inv_sel       :  1,    //     21
                              : 10;    //  31:22 reserved
}SYN_CODEC_SYN_CRG_CODEC00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_0004    crg_codec01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    icod_jpeg_clk_gate_en     :  1,    //      0
                              :  3,    //   3: 1 reserved
    lbus_aclk_400clk_gate_en  :  1,    //      4
    lbus_aclk_264clk_gate_en  :  1,    //      5
                              :  2,    //   7: 6 reserved
    te_ch2_sclk_gate_en       :  1,    //      8
    te_ch1_sclk_gate_en       :  1,    //      9
    te_ch0_sclk_gate_en       :  1,    //     10
    te_ciout_clk_gate_en      :  1,    //     11
    te_mcu_clk_gate_en        :  1,    //     12
    te_gstcc_if_clk_gate_en   :  1,    //     13
    te_fixed_sclk_gate_en     :  1,    //     14
    te_clk_gate_en            :  1,    //     15
    te_axi_clk_gate_en        :  1,    //     16
    aud_fs25clk_gate_en       :  1,    //     17
    aud_fs24clk_gate_en       :  1,    //     18
    aud_fs23clk_gate_en       :  1,    //     19
    aud_fs22clk_gate_en       :  1,    //     20
    aud_fs21clk_gate_en       :  1,    //     21
    aud_fs20clk_gate_en       :  1,    //     22
    aud_fs00clk_gate_en       :  1,    //     23
    aud_nicclk_gate_en        :  1,    //     24
    aud_hmr0spdifclk_gate_en  :  1,    //     25
    aud_teclk_gate_en         :  1,    //     26
    aud_apb_clk_gate_en       :  1,    //     27
    aud_aclk_gate_en          :  1,    //     28
    aud_i2s_sclk_gate_en      :  1,    //     29
    codec_apb_bnd_clk_gate_en :  1,    //     30
    lbus_apb_bnd_clk_gate_en  :  1;    //     31
}SYN_CODEC_SYN_CRG_CODEC01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_0008    crg_codec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_te_mcu              :  1,    //      0
    swrst_aud_aclk            :  1,    //      1
    swrst_te_gstcc_if         :  1,    //      2
    swrst_te_fixed            :  1,    //      3
    swrst_te                  :  1,    //      4
    swrst_te_axi              :  1,    //      5
    swrst_icod_jpeg           :  1,    //      6
    swrst_aud_apb             :  1,    //      7
    swrst_te_ch0_n            :  1,    //      8
    swrst_te_ch1_n            :  1,    //      9
    swrst_te_ch2_n            :  1,    //     10
    swrst_te_ciout_n          :  1,    //     11
                              : 20;    //  31:12 reserved
}SYN_CODEC_SYN_CRG_CODEC02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C5_000C    syn_codec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gstcc_tx            :  1,    //      0
    swrst_te_tx               :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_tp_output_mux_sel     :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_tp_input_mux_sel      :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}SYN_CODEC_SYN_SYN_CODEC02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    codec_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SYN_CODEC_SYN_CRG_CODEC00_L18F_A0        crg_codec00              ;         // 0xC9C5_0000
    SYN_CODEC_SYN_CRG_CODEC01_L18F_A0        crg_codec01              ;         // 0xC9C5_0004
    SYN_CODEC_SYN_CRG_CODEC02_L18F_A0        crg_codec02              ;         // 0xC9C5_0008
    SYN_CODEC_SYN_SYN_CODEC02_L18F_A0        syn_codec02              ;         // 0xC9C5_000C
} SYN_CODEC_SYN_REG_L18F_A0;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_CODEC_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_SYN_Register_Manual_55.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

