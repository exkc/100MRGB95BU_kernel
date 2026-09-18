#ifndef _CRG_SUB_DPE_E60A0_REG_H_
#define _CRG_SUB_DPE_E60A0_REG_H_

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
    0xC924_3000    crg_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpe__tcon_apb_clk_gate_en: 1,    //    0
    reg_dpe__tcon_pix2_clk_gate_en: 1,    //   1
    reg_dpe__tcon_osd_clk_gate_en: 1,    //    2
    reg_dpe__led_de_clk_gate_en: 1,    //      3
    reg_dpe__led_pxl_clk_gate_en: 1,    //     4
    reg_dpe__tcon_pip_clk_gate_en: 1,    //    5
    reg_dpe__led_oif_clk_gate_en: 1,    //     6
    reg_dpe__tcon_pix_clk_gate_en: 1,    //    7
    reg_dpe__led_apb_clk_gate_en: 1,    //     8
    reg_dpe__led_vx1_clk_gate_en: 1,    //     9
    reg_dpe__axi_soc_clk_gate_en: 1,    //    10
                              : 21;    //  31:11 reserved
}CRG_SUB_DPE_CRG_DPE00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3004    crg_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpe__soft_rst_apb_n   :  1,    //      0
    reg_dpe__soft_rst_pix_n   :  1,    //      1
    reg_dpe__soft_rst_led0_apb_n: 1,    //     2
    reg_dpe__soft_rst_led1_apb_n: 1,    //     3
    reg_dpe__soft_rst_led1_de_n: 1,    //      4
    reg_dpe__soft_rst_pip_n   :  1,    //      5
    reg_dpe__soft_rst_led1_pxl_bnd_n: 1,    //  6
    reg_dpe__soft_rst_led1_de_bnd_n: 1,    //  7
    reg_dpe__soft_rst_tcon_pip_bnd_n: 1,    //  8
    reg_dpe__soft_rst_pix2_n  :  1,    //      9
    reg_dpe__soft_rst_led0_pxl_n: 1,    //    10
    reg_dpe__soft_rst_led1_vx1_n: 1,    //    11
    reg_dpe__soft_rst_osd_bnd_n: 1,    //     12
    reg_dpe__soft_rst_led_oif_n: 1,    //     13
    reg_dpe__soft_rst_osd_n   :  1,    //     14
    reg_dpe__soft_rst_led0_pxl_bnd_n: 1,    //  15
    reg_dpe__soft_rst_led1_pxl_n: 1,    //    16
    reg_dpe__soft_rst_axi_soc_n: 1,    //     17
                              : 14;    //  31:18 reserved
}CRG_SUB_DPE_CRG_DPE01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3008    crg_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpe__tcon_pix2_clk_sel:  2,    //   1: 0
    reg_dpe__tcon_osd_clk_sel :  2,    //   3: 2
    reg_dpe__led_oif_clk_sel  :  2,    //   5: 4
    reg_dpe__led_pxl_clk_sel  :  2,    //   7: 6
                              : 24;    //   31:8 reserved
}CRG_SUB_DPE_CRG_DPE02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_300C    crg_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_ctrl_dpe  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}CRG_SUB_DPE_CRG_DPE03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3010    crg_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpe__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_dpe__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_dpe__crg_clk_off_check:  1,    //     30
    reg_dpe__crg_clk_gate     :  1;    //     31
}CRG_SUB_DPE_CRG_DPE04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC924_3014    crg_dpe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpe__crg_clk_rst_sel  : 32;    //  31: 0
}CRG_SUB_DPE_CRG_DPE05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CRG_SUB_DPE_CRG_DPE00_E60_A0_T           crg_dpe00                ;         // 0xC924_3000
    CRG_SUB_DPE_CRG_DPE01_E60_A0_T           crg_dpe01                ;         // 0xC924_3004
    CRG_SUB_DPE_CRG_DPE02_E60_A0_T           crg_dpe02                ;         // 0xC924_3008
    CRG_SUB_DPE_CRG_DPE03_E60_A0_T           crg_dpe03                ;         // 0xC924_300C
    CRG_SUB_DPE_CRG_DPE04_E60_A0_T           crg_dpe04                ;         // 0xC924_3010
    CRG_SUB_DPE_CRG_DPE05_E60_A0_T           crg_dpe05                ;         // 0xC924_3014
} CRG_SUB_DPE_REG_E60_A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CRG_SUB_DPE_E60A0_REG_H_ */

/* from 'E60_CRG_SUB_Register_Manual_20191213.xlsx'  2019.12.17  KST by LGSiCRDV V3.0B*/

