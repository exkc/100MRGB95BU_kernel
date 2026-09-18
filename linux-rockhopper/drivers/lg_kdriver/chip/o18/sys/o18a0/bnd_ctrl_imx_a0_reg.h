#ifndef _BND_CTRL_IMX_A0_REG_H_
#define _BND_CTRL_IMX_A0_REG_H_

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
    0xC90F_E000    crg_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    axi_soc_clk_gate_en       :  1,    //      0
    hdrh_clk_gate_en          :  1,    //      1
    hdr_clk_gate_en           :  1,    //      2
    hdr_de_clk_gate_en        :  1,    //      3
    vdo2_clk_gate_en          :  1,    //      4
    vdo1_clk_gate_en          :  1,    //      5
    vdo0_clk_gate_en          :  1,    //      6
    core_clk_gate_en          :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_IMX_CRG_IMX00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_E004    crg_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdrh_clk_sel              :  2,    //   1: 0
    hdr_clk_sel               :  2,    //   3: 2
                              : 28;    //   31:4 reserved
}BND_CTRL_IMX_CRG_IMX01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_E008    crg_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_axi_soc             :  1,    //      0
    swrst_hdrh                :  1,    //      1
    swrst_hdr                 :  1,    //      2
    swrst_hdr_de              :  1,    //      3
    swrst_hdr_apb             :  1,    //      4
    swrst_vdo2                :  1,    //      5
    swrst_vdo1                :  1,    //      6
    swrst_vdo0                :  1,    //      7
    swrst_axi_sub             :  1,    //      8
    swrst_axi                 :  1,    //      9
    swrst_de                  :  1,    //     10
    swrst_apb                 :  1,    //     11
                              : 20;    //  31:12 reserved
}BND_CTRL_IMX_CRG_IMX02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_E010    crg_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_hdr_ctrl          : 32;    //  31: 0
}BND_CTRL_IMX_CRG_IMX03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_E014    crg_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_imx_ctrl          : 32;    //  31: 0
}BND_CTRL_IMX_CRG_IMX04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_E018    crg_imx05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_sre_imx_msf0_cc     :  1,    //      0
    swrst_sre_imx_msf0_yy     :  1,    //      1
    swrst_sre_imx_msf1_cc     :  1,    //      2
    swrst_sre_imx_msf1_yy     :  1,    //      3
    swrst_cco_gcf             :  1,    //      4
    swrst_cvi_imx             :  1,    //      5
                              : 26;    //   31:6 reserved
}BND_CTRL_IMX_CRG_IMX05_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_IMX_CRG_IMX00_O18_A0                crg_imx00                ;         // 0xC90F_E000
BND_CTRL_IMX_CRG_IMX01_O18_A0                crg_imx01                ;         // 0xC90F_E004
BND_CTRL_IMX_CRG_IMX02_O18_A0                crg_imx02                ;         // 0xC90F_E008
UINT32                                                 _rsvd_00[   1] ;         // 0xC90F_E00C
BND_CTRL_IMX_CRG_IMX03_O18_A0                crg_imx03                ;         // 0xC90F_E010
BND_CTRL_IMX_CRG_IMX04_O18_A0                crg_imx04                ;         // 0xC90F_E014
BND_CTRL_IMX_CRG_IMX05_O18_A0                crg_imx05                ;         // 0xC90F_E018
} BND_CTRL_IMX_REG_O18_A0;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_IMX_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

