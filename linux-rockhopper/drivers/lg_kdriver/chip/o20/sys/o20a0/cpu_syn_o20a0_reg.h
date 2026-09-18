#ifndef _CPU_SYN_O20A0_REG_H_
#define _CPU_SYN_O20A0_REG_H_

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
    0xC923_0000    crg_cpuperi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__tzapb_clk_gate_en: 1,    //   0
    reg_cpuperi__peri_clk_533m_gate_en: 1,    //  1
    reg_cpuperi__peri_clk_200m_gate_en: 1,    //  2
    reg_cpuperi__peri_clk_200m_inv_gate_en: 1,    //  3
    reg_cpuperi__peri_clk_25m_ci_gate_en: 1,    //  4
    reg_cpuperi__peri_clk_50m_ci_gate_en: 1,    //  5
    reg_cpuperi__peri_clk_400m_gate_en: 1,    //  6
    reg_cpuperi__cssyclk_gate_en: 1,    //     7
    reg_cpuperi__tsclk_gate_en:  1,    //      8
    reg_cpuperi__xtal_i_cpu_gate_en: 1,    //  9
                              : 22;    //  31:10 reserved
}CPU_SYN_CRG_CPUPERI00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0004    crg_cpuperi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__soft_ncntreset: 1,    //      0
    reg_cpuperi__soft_ntsreset:  1,    //      1
    reg_cpuperi__soft_tzrom_rstn_200m: 1,    //  2
    reg_cpuperi__soft_peri_bus_rstn_200m: 1,    //  3
    reg_cpuperi__soft_zenc_rstn_533m: 1,    //  4
    reg_cpuperi__soft_sc_rstn_533m: 1,    //   5
    reg_cpuperi__soft_dma_apb1_rstn_200m: 1,    //  6
    reg_cpuperi__soft_core_apb_rstn_200m: 1,    //  7
    reg_cpuperi__soft_dvb_ci_rstn_25m: 1,    //  8
    reg_cpuperi__soft_dmac_rstn_200m: 1,    //  9
    reg_cpuperi__soft_def_slave_rstn_200m: 1,    //  10
    reg_cpuperi__soft_gpio_15_16_17_rstn_200m: 1,    //  11
    reg_cpuperi__soft_gpio_9_10_11_rstn_200m: 1,    //  12
    reg_cpuperi__soft_gpio_3_4_5_rstn_200m: 1,    //  13
    reg_cpuperi__soft_wdt_rstn_200m: 1,    //  14
    reg_cpuperi__soft_remap_rstn_200m: 1,    //  15
    reg_cpuperi__soft_irblaster_rstn_200m: 1,    //  16
    reg_cpuperi__soft_i2c_8_rstn_200m: 1,    //  17
    reg_cpuperi__soft_i2c_6_rstn_200m: 1,    //  18
    reg_cpuperi__soft_i2c_4_rstn_200m: 1,    //  19
    reg_cpuperi__soft_i2c_2_rstn_200m: 1,    //  20
    reg_cpuperi__soft_i2c_0_rstn_200m: 1,    //  21
    reg_cpuperi__soft_spi_1_apb_rstn_200m: 1,    //  22
    reg_cpuperi__soft_spi_0_apb_rstn_200m: 1,    //  23
    reg_cpuperi__soft_uart_2_rstn_200m: 1,    //  24
    reg_cpuperi__soft_uart_1_rstn_200m: 1,    //  25
    reg_cpuperi__soft_uart_0_rstn_200m: 1,    //  26
    reg_cpuperi__soft_top_ctrl_rstn_200m: 1,    //  27
    reg_cpuperi__soft_rst_axi_200m_bnd_n: 1,    //  28
    reg_cpuperi__soft_ncssysreset: 1,    //   29
    reg_cpuperi__soft_tzapb_rstn: 1,    //    30
    reg_cpuperi__soft_zdec_rstn_533m: 1;    //  31
}CPU_SYN_CRG_CPUPERI01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0008    crg_cpuperi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__soft_dma_apb0_rstn_200m: 1,    //  0
    reg_cpuperi__soft_smc_rstn_200m: 1,    //  1
    reg_cpuperi__soft_timer64_rstn_200m: 1,    //  2
    reg_cpuperi__soft_gpio_6_7_8_rstn_200m: 1,    //  3
    reg_cpuperi__soft_wdt_apb_rstn_200m: 1,    //  4
    reg_cpuperi__soft_i2c_9_rstn_200m: 1,    //  5
    reg_cpuperi__soft_i2c_5_rstn_200m: 1,    //  6
    reg_cpuperi__soft_i2c_1_rstn_200m: 1,    //  7
    reg_cpuperi__soft_spi_0_rstn_200m: 1,    //  8
    reg_cpuperi__soft_uart_2_apb_rstn_200m: 1,    //  9
    reg_cpuperi__soft_uart_0_apb_rstn_200m: 1,    //  10
    reg_cpuperi__soft_rst_axi_533m_bnd_n: 1,    //  11
    reg_cpuperi__soft_tzram_rstn_200m: 1,    //  12
    reg_cpuperi__soft_peri_bus_rstn_533m: 1,    //  13
    reg_cpuperi__soft_sram_ctrl_rstn_200m: 1,    //  14
    reg_cpuperi__soft_gpio_0_1_2_rstn_200m: 1,    //  15
    reg_cpuperi__soft_i2c_7_rstn_200m: 1,    //  16
    reg_cpuperi__soft_spi_1_rstn_200m: 1,    //  17
    reg_cpuperi__soft_uart_1_apb_rstn_200m: 1,    //  18
    reg_cpuperi__soft_gic400_rstn_533m: 1,    //  19
    reg_cpuperi__soft_gpio_12_13_14_rstn_200m: 1,    //  20
    reg_cpuperi__soft_i2c_3_rstn_200m: 1,    //  21
    reg_cpuperi__soft_rst_isol_n: 1,    //    22
    reg_cpuperi__soft_bus_matrix_rstn_200m: 1,    //  23
    reg_cpuperi__soft_sci_rstn_200m: 1,    //  24
    reg_cpuperi__soft_timer_rstn_200m: 1,    //  25
                              :  6;    //  31:26 reserved
}CPU_SYN_CRG_CPUPERI02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_000C    crg_cpuperi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__peri_clk_200m_inv_sel: 1,    //  0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0010    crg_cpuperi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__tzapb_clk_sel:  1,    //      0
    reg_cpuperi__peri_clk_200m_sel: 1,    //   1
    reg_cpuperi__peri_clk_50m_ci_sel: 1,    //  2
    reg_cpuperi__cpu_cssyclk_sel: 1,    //     3
    reg_cpuperi__peri_clk_533m_sel: 1,    //   4
    reg_cpuperi__peri_clk_400m_sel: 1,    //   5
    reg_cpuperi__peri_clk_25m_ci_sel: 1,    //  6
    reg_cpuperi__cpu_tsclk_sel:  1,    //      7
    reg_cpuperi__ayasofya_clkin_sel: 1,    //  8
                              : 23;    //   31:9 reserved
}CPU_SYN_CRG_CPUPERI04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0014    crg_cpuperi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__crg_freq_value: 18,    //  17:0
                              : 10,    //  27:18 reserved
    reg_cpuperi__crg_rst_high_check: 1,    //  28
                              :  1,    //     29 reserved
    reg_cpuperi__crg_clk_off_check: 1,    //  30
    reg_cpuperi__crg_clk_gate :  1;    //     31
}CPU_SYN_CRG_CPUPERI05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0018    crg_cpuperi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpuperi__crg_clk_rst_sel: 32;    //  31:0
}CPU_SYN_CRG_CPUPERI06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_001C    crg_cpuperi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}CPU_SYN_CRG_CPUPERI07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0020    crg_cpuperi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}CPU_SYN_CRG_CPUPERI08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0024    crg_cpuperi09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0028    crg_cpuperi10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pc1_tzspace_only          :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_002C    crg_cpuperi11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pc2_pchkerr               :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0030    crg_cpuperi12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pc1_pchkerr               :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0034    crg_cpuperi13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pc0_pchkerr               :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SYN_CRG_CPUPERI13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0038    crg_clk_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core533_clk_ctrl      :  9,    //   8: 0
                              :  7,    //  15: 9 reserved
    reg_core400_clk_ctrl      :  9,    //  24:16
                              :  7;    //  31:25 reserved
}CPU_SYN_CRG_CLK_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_003C    ayasofia_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ayasofya_ctr00            : 32;    //  31: 0
}CPU_SYN_AYASOFIA_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0040    ayasofia_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ayasofya_ctr01            : 32;    //  31: 0
}CPU_SYN_AYASOFIA_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CPU_SYN_CRG_CPUPERI00_O20A0_T                crg_cpuperi00            ;         // 0xC923_0000
CPU_SYN_CRG_CPUPERI01_O20A0_T                crg_cpuperi01            ;         // 0xC923_0004
CPU_SYN_CRG_CPUPERI02_O20A0_T                crg_cpuperi02            ;         // 0xC923_0008
CPU_SYN_CRG_CPUPERI03_O20A0_T                crg_cpuperi03            ;         // 0xC923_000C
CPU_SYN_CRG_CPUPERI04_O20A0_T                crg_cpuperi04            ;         // 0xC923_0010
CPU_SYN_CRG_CPUPERI05_O20A0_T                crg_cpuperi05            ;         // 0xC923_0014
CPU_SYN_CRG_CPUPERI06_O20A0_T                crg_cpuperi06            ;         // 0xC923_0018
CPU_SYN_CRG_CPUPERI07_O20A0_T                crg_cpuperi07            ;         // 0xC923_001C
CPU_SYN_CRG_CPUPERI08_O20A0_T                crg_cpuperi08            ;         // 0xC923_0020
CPU_SYN_CRG_CPUPERI09_O20A0_T                crg_cpuperi09            ;         // 0xC923_0024
CPU_SYN_CRG_CPUPERI10_O20A0_T                crg_cpuperi10            ;         // 0xC923_0028
CPU_SYN_CRG_CPUPERI11_O20A0_T                crg_cpuperi11            ;         // 0xC923_002C
CPU_SYN_CRG_CPUPERI12_O20A0_T                crg_cpuperi12            ;         // 0xC923_0030
CPU_SYN_CRG_CPUPERI13_O20A0_T                crg_cpuperi13            ;         // 0xC923_0034
CPU_SYN_CRG_CLK_CTRL01_O20A0_T               crg_clk_ctrl01           ;         // 0xC923_0038
CPU_SYN_AYASOFIA_CTRL00_O20A0_T              ayasofia_ctrl00          ;         // 0xC923_003C
CPU_SYN_AYASOFIA_CTRL01_O20A0_T              ayasofia_ctrl01          ;         // 0xC923_0040
} CPU_SYN_REG_O20A0_T;
/* 17 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CPU_SYN_O20A0_REG_H_ */

/* from 'O20_CTOP_SYN_Register_Manual.xlsx'  2019.4.16  KST by LGSiCRDV V2.2B*/

