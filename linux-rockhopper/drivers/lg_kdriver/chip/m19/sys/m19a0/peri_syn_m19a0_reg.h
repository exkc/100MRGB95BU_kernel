#ifndef _PERI_SYN_M19A0_REG_H_
#define _PERI_SYN_M19A0_REG_H_

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
    tsclk_gate_en             :  1,    //      0
    cssyclk_gate_en           :  1,    //      1
    peri_clk_400m_gate_en     :  1,    //      2
    peri_clk_50m_ci_gate_en   :  1,    //      3
    peri_clk_25m_ci_gate_en   :  1,    //      4
    peri_clk_200m_inv_gate_en :  1,    //      5
    peri_clk_200m_gate_en     :  1,    //      6
    peri_clk_528m_gate_en     :  1,    //      7
    xtal_i_cpu_gate_en        :  1,    //      8
    tzapb_clk_gate_en         :  1,    //      9
                              : 22;    //  31:10 reserved
}PERI_SYN_CRG_CPUPERI00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0004    crg_cpuperi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cpu_tsclk_sel             :  1,    //      0
    cpu_cssyclk_sel           :  1,    //      1
    peri_clk_400m_sel         :  1,    //      2
    peri_clk_50m_ci_sel       :  1,    //      3
    peri_clk_25m_ci_sel       :  1,    //      4
    peri_clk_200m_inv_sel     :  1,    //      5
    peri_clk_200m_sel         :  1,    //      6
    peri_clk_528m_sel         :  1,    //      7
    tzapb_clk_sel             :  1,    //      8
                              :  3,    //  11: 9 reserved
    sanpietro_clkin_sel       :  1,    //     12
                              : 13,    //  25:13 reserved
    core528_clk_sel           :  2,    //  27:26
                              :  2,    //  29:28 reserved
    core396_clk_sel           :  2;    //  31:30
}PERI_SYN_CRG_CPUPERI01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0008    crg_cpuperi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_wdt_apb_rstn_200m    :  1,    //      0
    soft_wdt_rstn_200m        :  1,    //      1
    soft_gpio_0_1_2_rstn_200m :  1,    //      2
    soft_gpio_3_4_5_rstn_200m :  1,    //      3
    soft_gpio_6_7_8_rstn_200m :  1,    //      4
    soft_gpio_9_10_11_rstn_200m: 1,    //      5
    soft_gpio_12_13_14_rstn_200m: 1,    //     6
    soft_gpio_15_16_17_rstn_200m: 1,    //     7
    soft_timer64_rstn_200m    :  1,    //      8
    soft_def_slave_rstn_200m  :  1,    //      9
    soft_sram_ctrl_rstn_200m  :  1,    //     10
    soft_dmac_rstn_200m       :  1,    //     11
    soft_sdhc_rstn_200m       :  1,    //     12
    soft_smc_rstn_200m        :  1,    //     13
    soft_dvb_ci_rstn_25m      :  1,    //     14
    soft_bus_matrix_rstn_200m :  1,    //     15
    soft_core_apb_rstn_200m   :  1,    //     16
    soft_dma_apb0_rstn_200m   :  1,    //     17
    soft_dma_apb1_rstn_200m   :  1,    //     18
    soft_peri_bus_rstn_528m   :  1,    //     19
                              :  1,    //     20 reserved
    soft_sc_rstn_528m         :  1,    //     21
    soft_zdec_rstn_528m       :  1,    //     22
    soft_zenc_rstn_528m       :  1,    //     23
    soft_gic400_rstn_528m     :  1,    //     24
    soft_peri_bus_rstn_200m   :  1,    //     25
    soft_tzapb_rstn           :  1,    //     26
    soft_tzrom_rstn_200m      :  1,    //     27
    soft_tzram_rstn_200m      :  1,    //     28
    soft_ntsreset             :  1,    //     29
    soft_ncssysreset          :  1,    //     30
    soft_ncntreset            :  1;    //     31
}PERI_SYN_CRG_CPUPERI02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_000C    crg_cpuperi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_top_ctrl_rstn_200m   :  1,    //      0
    soft_uart_0_apb_rstn_200m :  1,    //      1
    soft_uart_0_rstn_200m     :  1,    //      2
    soft_uart_1_apb_rstn_200m :  1,    //      3
    soft_uart_1_rstn_200m     :  1,    //      4
    soft_uart_2_apb_rstn_200m :  1,    //      5
    soft_uart_2_rstn_200m     :  1,    //      6
    soft_sci_rstn_200m        :  1,    //      7
    soft_spi_0_apb_rstn_200m  :  1,    //      8
    soft_spi_0_rstn_200m      :  1,    //      9
    soft_spi_1_apb_rstn_200m  :  1,    //     10
    soft_spi_1_rstn_200m      :  1,    //     11
    soft_i2c_0_rstn_200m      :  1,    //     12
    soft_i2c_1_rstn_200m      :  1,    //     13
    soft_i2c_2_rstn_200m      :  1,    //     14
    soft_i2c_3_rstn_200m      :  1,    //     15
    soft_i2c_4_rstn_200m      :  1,    //     16
    soft_i2c_5_rstn_200m      :  1,    //     17
    soft_i2c_6_rstn_200m      :  1,    //     18
    soft_i2c_7_rstn_200m      :  1,    //     19
    soft_i2c_8_rstn_200m      :  1,    //     20
    soft_i2c_9_rstn_200m      :  1,    //     21
    soft_irblaster_rstn_200m  :  1,    //     22
    soft_timer_rstn_200m      :  1,    //     23
    soft_remap_rstn_200m      :  1,    //     24
    soft_isol_n               :  1,    //     25
    soft_rst_axi_200m_bnd_n   :  1,    //     26
    soft_rst_axi_528m_bnd_n   :  1,    //     27
                              :  4;    //  31:28 reserved
}PERI_SYN_CRG_CPUPERI03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0020    sanpietro_ctr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sanpietro_ctr00           : 32;    //  31: 0
}PERI_SYN_SANPIETRO_CTR00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0024    sanpietro_ctr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sanpietro_ctr01           : 32;    //  31: 0
}PERI_SYN_SANPIETRO_CTR01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0028    syn_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}PERI_SYN_SYN_CPU00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_002C    syn_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}PERI_SYN_SYN_CPU01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0030    a_crg_check_peri_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk0_value           : 16,    //  15: 0
    peri_rst0_check           :  1,    //     16
    peri_clk0_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk0_off_value       :  8,    //  27:20
    peri_clk0_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk0_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0034    a_crg_check_peri_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk1_value           : 16,    //  15: 0
    peri_rst1_check           :  1,    //     16
    peri_clk1_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk1_off_value       :  8,    //  27:20
    peri_clk1_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk1_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0038    a_crg_check_peri_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk2_value           : 16,    //  15: 0
    peri_rst2_check           :  1,    //     16
    peri_clk2_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk2_off_value       :  8,    //  27:20
    peri_clk2_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk2_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_003C    a_crg_check_peri_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk3_value           : 16,    //  15: 0
    peri_rst3_check           :  1,    //     16
    peri_clk3_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk3_off_value       :  8,    //  27:20
    peri_clk3_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk3_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0040    a_crg_check_peri_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk4_value           : 16,    //  15: 0
    peri_rst4_check           :  1,    //     16
    peri_clk4_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk4_off_value       :  8,    //  27:20
    peri_clk4_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk4_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0044    a_crg_check_peri_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk5_value           : 16,    //  15: 0
    peri_rst5_check           :  1,    //     16
    peri_clk5_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk5_off_value       :  8,    //  27:20
    peri_clk5_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk5_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0048    a_crg_check_peri_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk6_value           : 16,    //  15: 0
    peri_rst6_check           :  1,    //     16
    peri_clk6_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk6_off_value       :  8,    //  27:20
    peri_clk6_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk6_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_004C    a_crg_check_peri_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk7_value           : 16,    //  15: 0
    peri_rst7_check           :  1,    //     16
    peri_clk7_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk7_off_value       :  8,    //  27:20
    peri_clk7_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk7_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_7_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0050    a_crg_check_peri_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk8_value           : 16,    //  15: 0
    peri_rst8_check           :  1,    //     16
    peri_clk8_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk8_off_value       :  8,    //  27:20
    peri_clk8_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk8_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_8_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0054    a_crg_check_peri_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk9_value           : 16,    //  15: 0
    peri_rst9_check           :  1,    //     16
    peri_clk9_off_check       :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk9_off_value       :  8,    //  27:20
    peri_clk9_sel             :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk9_gate            :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_9_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0058    a_crg_check_peri_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk10_value          : 16,    //  15: 0
    peri_rst10_check          :  1,    //     16
    peri_clk10_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk10_off_value      :  8,    //  27:20
    peri_clk10_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk10_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_005C    a_crg_check_peri_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk11_value          : 16,    //  15: 0
    peri_rst11_check          :  1,    //     16
    peri_clk11_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk11_off_value      :  8,    //  27:20
    peri_clk11_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk11_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0060    a_crg_check_peri_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk12_value          : 16,    //  15: 0
    peri_rst12_check          :  1,    //     16
    peri_clk12_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk12_off_value      :  8,    //  27:20
    peri_clk12_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk12_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0064    a_crg_check_peri_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk13_value          : 16,    //  15: 0
    peri_rst13_check          :  1,    //     16
    peri_clk13_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk13_off_value      :  8,    //  27:20
    peri_clk13_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk13_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0068    a_crg_check_peri_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk14_value          : 16,    //  15: 0
    peri_rst14_check          :  1,    //     16
    peri_clk14_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk14_off_value      :  8,    //  27:20
    peri_clk14_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk14_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_006C    a_crg_check_peri_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_clk15_value          : 16,    //  15: 0
    peri_rst15_check          :  1,    //     16
    peri_clk15_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    peri_clk15_off_value      :  8,    //  27:20
    peri_clk15_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    peri_clk15_gate           :  1;    //     31
}PERI_SYN_A_CRG_CHECK_PERI_15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0070    syn_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}PERI_SYN_SYN_CPU02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC923_0074    syn_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pc0_pchkerr               :  1,    //      0
    pc1_pchkerr               :  1,    //      1
    pc2_pchkerr               :  1,    //      2
    pc1_tzspace_only          :  1,    //      3
                              : 28;    //   31:4 reserved
}PERI_SYN_SYN_CPU03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    peri_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
PERI_SYN_CRG_CPUPERI00_M19A0_T               crg_cpuperi00            ;         // 0xC923_0000
PERI_SYN_CRG_CPUPERI01_M19A0_T               crg_cpuperi01            ;         // 0xC923_0004
PERI_SYN_CRG_CPUPERI02_M19A0_T               crg_cpuperi02            ;         // 0xC923_0008
PERI_SYN_CRG_CPUPERI03_M19A0_T               crg_cpuperi03            ;         // 0xC923_000C
UINT32                                                 _rsvd_00[   4] ;         // 0xC923_0010 ~ 0xC923_001C
PERI_SYN_SANPIETRO_CTR00_M19A0_T             sanpietro_ctr00          ;         // 0xC923_0020
PERI_SYN_SANPIETRO_CTR01_M19A0_T             sanpietro_ctr01          ;         // 0xC923_0024
PERI_SYN_SYN_CPU00_M19A0_T                   syn_cpu00                ;         // 0xC923_0028
PERI_SYN_SYN_CPU01_M19A0_T                   syn_cpu01                ;         // 0xC923_002C
PERI_SYN_A_CRG_CHECK_PERI_0_M19A0_T          a_crg_check_peri_0       ;         // 0xC923_0030
PERI_SYN_A_CRG_CHECK_PERI_1_M19A0_T          a_crg_check_peri_1       ;         // 0xC923_0034
PERI_SYN_A_CRG_CHECK_PERI_2_M19A0_T          a_crg_check_peri_2       ;         // 0xC923_0038
PERI_SYN_A_CRG_CHECK_PERI_3_M19A0_T          a_crg_check_peri_3       ;         // 0xC923_003C
PERI_SYN_A_CRG_CHECK_PERI_4_M19A0_T          a_crg_check_peri_4       ;         // 0xC923_0040
PERI_SYN_A_CRG_CHECK_PERI_5_M19A0_T          a_crg_check_peri_5       ;         // 0xC923_0044
PERI_SYN_A_CRG_CHECK_PERI_6_M19A0_T          a_crg_check_peri_6       ;         // 0xC923_0048
PERI_SYN_A_CRG_CHECK_PERI_7_M19A0_T          a_crg_check_peri_7       ;         // 0xC923_004C
PERI_SYN_A_CRG_CHECK_PERI_8_M19A0_T          a_crg_check_peri_8       ;         // 0xC923_0050
PERI_SYN_A_CRG_CHECK_PERI_9_M19A0_T          a_crg_check_peri_9       ;         // 0xC923_0054
PERI_SYN_A_CRG_CHECK_PERI_10_M19A0_T         a_crg_check_peri_10      ;         // 0xC923_0058
PERI_SYN_A_CRG_CHECK_PERI_11_M19A0_T         a_crg_check_peri_11      ;         // 0xC923_005C
PERI_SYN_A_CRG_CHECK_PERI_12_M19A0_T         a_crg_check_peri_12      ;         // 0xC923_0060
PERI_SYN_A_CRG_CHECK_PERI_13_M19A0_T         a_crg_check_peri_13      ;         // 0xC923_0064
PERI_SYN_A_CRG_CHECK_PERI_14_M19A0_T         a_crg_check_peri_14      ;         // 0xC923_0068
PERI_SYN_A_CRG_CHECK_PERI_15_M19A0_T         a_crg_check_peri_15      ;         // 0xC923_006C
PERI_SYN_SYN_CPU02_M19A0_T                   syn_cpu02                ;         // 0xC923_0070
PERI_SYN_SYN_CPU03_M19A0_T                   syn_cpu03                ;         // 0xC923_0074
} PERI_SYN_REG_M19A0_T;
/* 26 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _PERI_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

