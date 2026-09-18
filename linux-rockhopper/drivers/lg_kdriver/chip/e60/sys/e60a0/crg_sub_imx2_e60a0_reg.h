#ifndef _CRG_SUB_IMX2_E60A0_REG_H_
#define _CRG_SUB_IMX2_E60A0_REG_H_

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
    0xC93A_C000    crg_imx200 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx2__apb_clk_gate_en :  1,    //      0
    reg_imx2__axi_clk_gate_en :  1,    //      1
    reg_imx2__vd1_clk_gate_en :  1,    //      2
    reg_imx2__lne_core0_clk_gate_en: 1,    //  3
    reg_imx2__lne_core1_clk_gate_en: 1,    //  4
    reg_imx2__axi_soc_clk_gate_en: 1,    //    5
    reg_imx2__bodp0_clk_gate_en: 1,    //      6
    reg_imx2__bodp1_clk_gate_en: 1,    //      7
    reg_imx2__de_clk_gate_en  :  1,    //      8
    reg_imx2__lne_apb_clk_gate_en: 1,    //    9
    reg_imx2__vd2_clk_gate_en :  1,    //     10
    reg_imx2__vd0_clk_gate_en :  1,    //     11
    reg_imx2__lne_axi_clk_gate_en: 1,    //   12
                              : 19;    //  31:13 reserved
}CRG_SUB_IMX2_CRG_IMX200_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C004    crg_imx201 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx2__soft_rst_apb_n  :  1,    //      0
    reg_imx2__soft_rst_axi_n  :  1,    //      1
    reg_imx2__soft_rst_vdo0_n :  1,    //      2
    reg_imx2__soft_rst_lne_apb_n: 1,    //     3
    reg_imx2__soft_rst_lne_axi0_n: 1,    //    4
    reg_imx2__soft_rst_lne_axi1_n: 1,    //    5
    reg_imx2__soft_rst_lne_core0_sys_n: 1,    //  6
    reg_imx2__soft_rst_lne_core1_sys_n: 1,    //  7
    reg_imx2__soft_rst_lne_axi0_async_n: 1,    //  8
    reg_imx2__soft_rst_lne_axi_bus_n: 1,    //  9
    reg_imx2__soft_rst_axi_lne_bnd_n: 1,    //  10
    reg_imx2__soft_rst_de_bnd_n: 1,    //     11
    reg_imx2__soft_rst_bodp1_n:  1,    //     12
    reg_imx2__soft_rst_de_n   :  1,    //     13
    reg_imx2__soft_rst_vdo1_n :  1,    //     14
    reg_imx2__soft_rst_lne_core1_n: 1,    //  15
    reg_imx2__soft_rst_lne_core0_async_n: 1,    //  16
    reg_imx2__soft_rst_lne_axi1_async_n: 1,    //  17
    reg_imx2__soft_rst_axi_soc_n: 1,    //    18
    reg_imx2__soft_rst_axi_sbus_n: 1,    //   19
    reg_imx2__soft_rst_vdo2_n :  1,    //     20
    reg_imx2__soft_rst_axi_imx2_bnd_n: 1,    //  21
    reg_imx2__soft_rst_lne_core0_n: 1,    //  22
    reg_imx2__soft_rst_bodp0_n:  1,    //     23
    reg_imx2__soft_rst_lne_core1_async_n: 1,    //  24
                              :  7;    //  31:25 reserved
}CRG_SUB_IMX2_CRG_IMX201_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C008    crg_imx202 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx2__bodp0_clk_sel   :  1,    //      0
    reg_imx2__bodp1_clk_sel   :  1,    //      1
                              : 30;    //   31:2 reserved
}CRG_SUB_IMX2_CRG_IMX202_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C00C    crg_imx203 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_imx2 :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_IMX2_CRG_IMX203_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C010    crg_imx204 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core800_clk_ctrl_imx2 :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_IMX2_CRG_IMX204_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C014    crg_imx205 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_imx2 :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_IMX2_CRG_IMX205_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C018    crg_imx206 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx2__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_imx2__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_imx2__crg_clk_off_check: 1,    //     30
    reg_imx2__crg_clk_gate    :  1;    //     31
}CRG_SUB_IMX2_CRG_IMX206_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93A_C01C    crg_imx207 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx2__crg_clk_rst_sel : 32;    //  31: 0
}CRG_SUB_IMX2_CRG_IMX207_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    crg_sub_imx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CRG_SUB_IMX2_CRG_IMX200_E60_A0_T             crg_imx200               ;         // 0xC93A_C000
CRG_SUB_IMX2_CRG_IMX201_E60_A0_T             crg_imx201               ;         // 0xC93A_C004
CRG_SUB_IMX2_CRG_IMX202_E60_A0_T             crg_imx202               ;         // 0xC93A_C008
CRG_SUB_IMX2_CRG_IMX203_E60_A0_T             crg_imx203               ;         // 0xC93A_C00C
CRG_SUB_IMX2_CRG_IMX204_E60_A0_T             crg_imx204               ;         // 0xC93A_C010
CRG_SUB_IMX2_CRG_IMX205_E60_A0_T             crg_imx205               ;         // 0xC93A_C014
CRG_SUB_IMX2_CRG_IMX206_E60_A0_T             crg_imx206               ;         // 0xC93A_C018
CRG_SUB_IMX2_CRG_IMX207_E60_A0_T             crg_imx207               ;         // 0xC93A_C01C
} CRG_SUB_IMX2_REG_E60_A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_IMX2_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_Register_Manual.xlsx'  2020.1.9  KST by LGSiCRDV V3.0B*/

