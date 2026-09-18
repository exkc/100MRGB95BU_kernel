#ifndef _LBM_SYN_O20A0_REG_H_
#define _LBM_SYN_O20A0_REG_H_

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
    0xC930_0000    crg_gfx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx__gfx_pclk_gate_en :  1,    //      0
    reg_gfx__gfx_cclk_gate_en :  1,    //      1
                              : 30;    //   31:2 reserved
}LBM_SYN_CRG_GFX00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0004    crg_gfx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx__soft_rst_gfxp_n  :  1,    //      0
    reg_gfx__soft_rst_gfxpc_test_n: 1,    //   1
    reg_gfx__soft_rst_gfxc_n  :  1,    //      2
    reg_gfx__soft_rst_gfxc_bnd_n: 1,    //     3
                              : 28;    //   31:4 reserved
}LBM_SYN_CRG_GFX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0008    crg_gfx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_gfx__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_gfx__crg_clk_off_check:  1,    //     30
    reg_gfx__crg_clk_gate     :  1;    //     31
}LBM_SYN_CRG_GFX02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_000C    crg_gfx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx__crg_clk_rst_sel  : 32;    //  31: 0
}LBM_SYN_CRG_GFX03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0010    crg_lbus04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus__lbus400_clk_gate_en: 1,    //    0
    reg_lbus__de_soc_clk_gate_en: 1,    //     1
    reg_lbus__lbus533_clk_gate_en: 1,    //    2
                              : 29;    //   31:3 reserved
}LBM_SYN_CRG_LBUS04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0014    crg_lbus05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus__soft_rst_lbus400_n: 1,    //     0
    reg_lbus__soft_rst_de_soc_n: 1,    //      1
    reg_lbus__soft_rst_lbus533_n: 1,    //     2
                              : 29;    //   31:3 reserved
}LBM_SYN_CRG_LBUS05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0018    crg_lbus06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus__crg_freq_value  : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_lbus__crg_rst_high_check: 1,    //    28
                              :  1,    //     29 reserved
    reg_lbus__crg_clk_off_check: 1,    //     30
    reg_lbus__crg_clk_gate    :  1;    //     31
}LBM_SYN_CRG_LBUS06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_001C    crg_lbus07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus__crg_clk_rst_sel : 32;    //  31: 0
}LBM_SYN_CRG_LBUS07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0020    crg_mcu08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu__apb_clk_gate_en  :  1,    //      0
    reg_mcu__teclk_gate_en    :  1,    //      1
    reg_mcu__mcu_clk_gate_en  :  1,    //      2
                              : 29;    //   31:3 reserved
}LBM_SYN_CRG_MCU08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0024    crg_mcu09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu__soft_rst_apb_n   :  1,    //      0
    reg_mcu__soft_rst_te_n    :  1,    //      1
    reg_mcu__soft_rst_ipu_sbus_n: 1,    //     2
    reg_mcu__soft_rst_mcu_n   :  1,    //      3
    reg_mcu__soft_rst_ipu_n   :  1,    //      4
    reg_mcu__soft_rst_te_bnd_n:  1,    //      5
    reg_mcu__soft_rst_mcu_bnd_n: 1,    //      6
                              : 25;    //   31:7 reserved
}LBM_SYN_CRG_MCU09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0028    crg_mcu10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu__crg_freq_value   : 18,    //  17: 0
                              : 10,    //  27:18 reserved
    reg_mcu__crg_rst_high_check: 1,    //     28
                              :  1,    //     29 reserved
    reg_mcu__crg_clk_off_check:  1,    //     30
    reg_mcu__crg_clk_gate     :  1;    //     31
}LBM_SYN_CRG_MCU10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_002C    crg_mcu11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu__crg_clk_rst_sel  : 32;    //  31: 0
}LBM_SYN_CRG_MCU11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0030    crg_tsadc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus__soft_rst_ts_n   :  1,    //      0
    reg_lbus__tsadc_clk_gate_en: 1,    //      1
    reg_lbus__ts_clk_gate_en  :  1,    //      2
                              : 29;    //   31:3 reserved
}LBM_SYN_CRG_TSADC00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0034    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core533_clk_ctrl_lbus :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_lbus :  9,    //  24:16
                              :  7;    //  31:25 reserved
}LBM_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0038    crg_clk_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core600_clk_ctrl_gfx  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_gfx  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}LBM_SYN_CRG_CLK_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_003C    crg_clk_ctrl03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core533_clk_ctrl_gfx  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core480_clk_ctrl_gfx  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}LBM_SYN_CRG_CLK_CTRL03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0040    crg_clk_ctrl04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core480_clk_ctrl_mcu  :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl_mcu  :  9,    //  24:16
                              :  7;    //  31:25 reserved
}LBM_SYN_CRG_CLK_CTRL04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0044    crg_clk_ctrl05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx__gfx_cclk_sel     :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}LBM_SYN_CRG_CLK_CTRL05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0048    ip_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_lbus_lgarb     :  1,    //      0
    reg__swrst_gbus_lgarb     :  1,    //      1
                              : 30;    //   31:2 reserved
}LBM_SYN_IP_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_004C    ip_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg__swrst_gstcs0         :  1,    //      0
    reg__swrst_gstcs1         :  1,    //      1
    reg__swrst_te0            :  1,    //      2
    reg__swrst_te1            :  1,    //      3
                              : 28;    //   31:4 reserved
}LBM_SYN_IP_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_0050    lv_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_pqe_mcu    :  1,    //      0
    reg_ls_disable_gfx        :  1,    //      1
    reg_ls_disable_lbus       :  1,    //      2
                              : 29;    //   31:3 reserved
}LBM_SYN_LV_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    lbm_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
LBM_SYN_CRG_GFX00_O20A0_T                    crg_gfx00                ;         // 0xC930_0000
LBM_SYN_CRG_GFX01_O20A0_T                    crg_gfx01                ;         // 0xC930_0004
LBM_SYN_CRG_GFX02_O20A0_T                    crg_gfx02                ;         // 0xC930_0008
LBM_SYN_CRG_GFX03_O20A0_T                    crg_gfx03                ;         // 0xC930_000C
LBM_SYN_CRG_LBUS04_O20A0_T                   crg_lbus04               ;         // 0xC930_0010
LBM_SYN_CRG_LBUS05_O20A0_T                   crg_lbus05               ;         // 0xC930_0014
LBM_SYN_CRG_LBUS06_O20A0_T                   crg_lbus06               ;         // 0xC930_0018
LBM_SYN_CRG_LBUS07_O20A0_T                   crg_lbus07               ;         // 0xC930_001C
LBM_SYN_CRG_MCU08_O20A0_T                    crg_mcu08                ;         // 0xC930_0020
LBM_SYN_CRG_MCU09_O20A0_T                    crg_mcu09                ;         // 0xC930_0024
LBM_SYN_CRG_MCU10_O20A0_T                    crg_mcu10                ;         // 0xC930_0028
LBM_SYN_CRG_MCU11_O20A0_T                    crg_mcu11                ;         // 0xC930_002C
LBM_SYN_CRG_TSADC00_O20A0_T                  crg_tsadc00              ;         // 0xC930_0030
LBM_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC930_0034
LBM_SYN_CRG_CLK_CTRL02_O20A0_T               crg_clk_ctrl02           ;         // 0xC930_0038
LBM_SYN_CRG_CLK_CTRL03_O20A0_T               crg_clk_ctrl03           ;         // 0xC930_003C
LBM_SYN_CRG_CLK_CTRL04_O20A0_T               crg_clk_ctrl04           ;         // 0xC930_0040
LBM_SYN_CRG_CLK_CTRL05_O20A0_T               crg_clk_ctrl05           ;         // 0xC930_0044
LBM_SYN_IP_CTRL00_O20A0_T                    ip_ctrl00                ;         // 0xC930_0048
LBM_SYN_IP_CTRL01_O20A0_T                    ip_ctrl01                ;         // 0xC930_004C
LBM_SYN_LV_MUX01_O20A0_T                     lv_mux01                 ;         // 0xC930_0050
} LBM_SYN_REG_O20A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _LBM_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

