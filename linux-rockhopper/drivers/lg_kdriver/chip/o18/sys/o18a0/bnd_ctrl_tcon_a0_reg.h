#ifndef _BND_CTRL_TCON_A0_REG_H_
#define _BND_CTRL_TCON_A0_REG_H_

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
    0xC917_D000    crg_tcon00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_osc_clk_gate_en      :  1,    //      0
    tcon_osd_clk_gate_en      :  1,    //      1
    tcon_pix_clk_gate_en      :  1,    //      2
    tcon_pix2_clk_gate_en     :  1,    //      3
    tcon_axi_clk_gate_en      :  1,    //      4
    tcon_apb_clk_gate_en      :  1,    //      5
    tcon_fcic_clk_gate_en     :  1,    //      6
    tcon_clk_gate_en          :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_TCON_CRG_TCON00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D004    crg_tcon01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    tcon_osd_clk_sel          :  2,    //   3: 2
    tcon_pix_clk_sel          :  3,    //   6: 4
    tcon_pix2_clk_sel         :  3,    //   9: 7
    tcon_fcic_clk_sel         :  1,    //     10
    tcon_clk_sel              :  2,    //  12:11
                              : 19;    //  31:13 reserved
}BND_CTRL_TCON_CRG_TCON01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D008    crg_tcon02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_tcon_osd            :  1,    //      0
    swrst_tcon_pix            :  1,    //      1
    swrst_tcon_pix2           :  1,    //      2
    swrst_tcon_axi            :  1,    //      3
    swrst_tcon_apb_hm         :  1,    //      4
    swrst_tcon_apb            :  1,    //      5
    swrst_tcon_fcic           :  1,    //      6
    swrst_tcon                :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_TCON_CRG_TCON02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D00C    crg_tcon03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_TCON_CRG_TCON03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D010    crg_tcon04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ts_clk_gate_en            :  1,    //      0
    tsadc_clk_gate_en         :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_TCON_CRG_TCON04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D014    crg_tcon05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_ts                  :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_TCON_CRG_TCON05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D018    crg_tcon06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_clk_gate_en          :  1,    //      0
    sar_adc_clk_out_gate_en   :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_TCON_CRG_TCON06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D01C    crg_tcon07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_sadc                :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_TCON_CRG_TCON07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC917_D020    crg_tcon08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_cco_tcon_osd        :  1,    //      0
    tcon_gmau_flush_done      :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_TCON_CRG_TCON08_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_TCON_CRG_TCON00_O18_A0              crg_tcon00               ;         // 0xC917_D000
BND_CTRL_TCON_CRG_TCON01_O18_A0              crg_tcon01               ;         // 0xC917_D004
BND_CTRL_TCON_CRG_TCON02_O18_A0              crg_tcon02               ;         // 0xC917_D008
BND_CTRL_TCON_CRG_TCON03_O18_A0              crg_tcon03               ;         // 0xC917_D00C
BND_CTRL_TCON_CRG_TCON04_O18_A0              crg_tcon04               ;         // 0xC917_D010
BND_CTRL_TCON_CRG_TCON05_O18_A0              crg_tcon05               ;         // 0xC917_D014
BND_CTRL_TCON_CRG_TCON06_O18_A0              crg_tcon06               ;         // 0xC917_D018
BND_CTRL_TCON_CRG_TCON07_O18_A0              crg_tcon07               ;         // 0xC917_D01C
BND_CTRL_TCON_CRG_TCON08_O18_A0              crg_tcon08               ;         // 0xC917_D020
} BND_CTRL_TCON_REG_O18_A0;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_TCON_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

