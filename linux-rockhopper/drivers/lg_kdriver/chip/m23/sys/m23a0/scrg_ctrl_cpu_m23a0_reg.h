#ifndef _SCRG_CTRL_CPU_M23A0_REG_H_
#define _SCRG_CTRL_CPU_M23A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure 
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xCA21_0000    crg_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_peri_200m_clk_gate_en :  1,    //      0
    reg_peri_200m_clk_n_gate_en: 1,    //      1
    reg_peri_25m_ci_clk_gate_en: 1,    //      2
    reg_peri_400m_clk_gate_en :  1,    //      3
    reg_peri_50m_ci_clk_gate_en: 1,    //      4
    reg_peri_533m_clk_gate_en :  1,    //      5
    reg_tzapb_clk_gate_en     :  1,    //      6
    reg_xtal_clk_w_gate_en    :  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_CPU_CRG_CPU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_matrix_200m_n: 1,    //   0
    reg_soft_rst_cnt_xtal_n   :  1,    //      1
    reg_soft_rst_core_apb_200m_n: 1,    //     2
    reg_soft_rst_cssys_200m_n :  1,    //      3
    reg_soft_rst_def_slave_200m_n: 1,    //    4
    reg_soft_rst_dma_apb0_200m_n: 1,    //     5
    reg_soft_rst_dma_apb1_200m_n: 1,    //     6
    reg_soft_rst_dmac_200m_n  :  1,    //      7
    reg_soft_rst_dvb_ci_25m_n :  1,    //      8
    reg_soft_rst_gic400_533m_n:  1,    //      9
    reg_soft_rst_gpio0_200m_n :  1,    //     10
    reg_soft_rst_gpio10_200m_n:  1,    //     11
    reg_soft_rst_gpio11_200m_n:  1,    //     12
    reg_soft_rst_gpio12_200m_n:  1,    //     13
    reg_soft_rst_gpio13_200m_n:  1,    //     14
    reg_soft_rst_gpio14_200m_n:  1,    //     15
    reg_soft_rst_gpio15_200m_n:  1,    //     16
    reg_soft_rst_gpio16_200m_n:  1,    //     17
    reg_soft_rst_gpio17_200m_n:  1,    //     18
    reg_soft_rst_gpio1_200m_n :  1,    //     19
    reg_soft_rst_gpio2_200m_n :  1,    //     20
    reg_soft_rst_gpio3_200m_n :  1,    //     21
    reg_soft_rst_gpio4_200m_n :  1,    //     22
    reg_soft_rst_gpio5_200m_n :  1,    //     23
    reg_soft_rst_gpio6_200m_n :  1,    //     24
    reg_soft_rst_gpio7_200m_n :  1,    //     25
    reg_soft_rst_gpio8_200m_n :  1,    //     26
    reg_soft_rst_gpio9_200m_n :  1,    //     27
    reg_soft_rst_i2c_0_200m_n :  1,    //     28
    reg_soft_rst_i2c_1_200m_n :  1,    //     29
    reg_soft_rst_i2c_2_200m_n :  1,    //     30
    reg_soft_rst_i2c_3_200m_n :  1;    //     31
}SCRG_CTRL_CPU_CRG_CPU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0010    crg_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_i2c_4_200m_n :  1,    //      0
    reg_soft_rst_i2c_5_200m_n :  1,    //      1
    reg_soft_rst_i2c_6_200m_n :  1,    //      2
    reg_soft_rst_i2c_7_200m_n :  1,    //      3
    reg_soft_rst_i2c_8_200m_n :  1,    //      4
    reg_soft_rst_i2c_9_200m_n :  1,    //      5
    reg_soft_rst_irblaster_200m_n: 1,    //    6
    reg_soft_rst_p_cpu_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_cpu_1_axi_bnd_n: 1,    //   8
    reg_soft_rst_p_cpu_2_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_emusb_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_epusb_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_isol_axi_bnd_n: 1,    //   12
    reg_soft_rst_p_micom_1_axi_bnd_n: 1,    //  13
    reg_soft_rst_peri_bus_200m_n: 1,    //    14
    reg_soft_rst_peri_bus_533m_n: 1,    //    15
    reg_soft_rst_remap_200m_n :  1,    //     16
    reg_soft_rst_sc_533m_n    :  1,    //     17
    reg_soft_rst_sci_200m_n   :  1,    //     18
    reg_soft_rst_smc_200m_n   :  1,    //     19
    reg_soft_rst_spi_0_200m_n :  1,    //     20
    reg_soft_rst_spi_0_apb_200m_n: 1,    //   21
    reg_soft_rst_spi_1_200m_n :  1,    //     22
    reg_soft_rst_spi_1_apb_200m_n: 1,    //   23
    reg_soft_rst_sram_ctrl_200m_n: 1,    //   24
    reg_soft_rst_timer64_200m_n: 1,    //     25
    reg_soft_rst_timer_200m_n :  1,    //     26
    reg_soft_rst_top_ctrl_200m_n: 1,    //    27
    reg_soft_rst_tzapb_n      :  1,    //     28
    reg_soft_rst_tzram_200m_n :  1,    //     29
    reg_soft_rst_tzrom_200m_n :  1,    //     30
    reg_soft_rst_uart0_200m_n :  1;    //     31
}SCRG_CTRL_CPU_CRG_CPU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0014    crg_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_uart0_apb_200m_n: 1,    //    0
    reg_soft_rst_uart1_200m_n :  1,    //      1
    reg_soft_rst_uart1_apb_200m_n: 1,    //    2
    reg_soft_rst_uart2_200m_n :  1,    //      3
    reg_soft_rst_uart2_apb_200m_n: 1,    //    4
    reg_soft_rst_wdt_200m_n   :  1,    //      5
    reg_soft_rst_wdt_apb_200m_n: 1,    //      6
    reg_soft_rst_x_cpu_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_cpu_0_axi_n:  1,    //      8
    reg_soft_rst_x_cpu_1_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_cpu_1_axi_n:  1,    //     10
    reg_soft_rst_x_cpu_2_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_cpu_2_axi_n:  1,    //     12
    reg_soft_rst_x_emusb_0_axi_n: 1,    //    13
    reg_soft_rst_x_epusb_0_axi_n: 1,    //    14
    reg_soft_rst_x_isol_axi_n :  1,    //     15
    reg_soft_rst_x_micom_1_axi_n: 1,    //    16
    reg_soft_rst_zdec_533m_n  :  1,    //     17
    reg_soft_rst_zenc_533m_n  :  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_CPU_CRG_CPU05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0018    crg_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_o_cpu_clk_sel         :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_CPU_CRG_CPU06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU00_M23A0_T    crg_cpu00  ;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU01_M23A0_T    crg_cpu01  ;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU02_M23A0_T    crg_cpu02  ;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU03_M23A0_T    crg_cpu03  ;             // 0xCA21_000C
    SCRG_CTRL_CPU_CRG_CPU04_M23A0_T    crg_cpu04  ;             // 0xCA21_0010
    SCRG_CTRL_CPU_CRG_CPU05_M23A0_T    crg_cpu05  ;             // 0xCA21_0014
    SCRG_CTRL_CPU_CRG_CPU06_M23A0_T    crg_cpu06  ;             // 0xCA21_0018
}SCRG_CTRL_CPU_REG_M23A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define SCRG_CTRL_CPU_CRG_CPU00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_CPU_CRG_CPU01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_CPU_CRG_CPU02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_CPU_CRG_CPU03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_CPU_CRG_CPU04_M23A0_T_OFF                 (BASEADDRESS+0x0010)
#define SCRG_CTRL_CPU_CRG_CPU05_M23A0_T_OFF                 (BASEADDRESS+0x0014)
#define SCRG_CTRL_CPU_CRG_CPU06_M23A0_T_OFF                 (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xCA21_0000    crg_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_peri_200m_clk_gate_en: 1;    //  0
    UINT32 reg_peri_200m_clk_n_gate_en: 1;    //  1
    UINT32 reg_peri_25m_ci_clk_gate_en: 1;    //  2
    UINT32 reg_peri_400m_clk_gate_en: 1;    //  3
    UINT32 reg_peri_50m_ci_clk_gate_en: 1;    //  4
    UINT32 reg_peri_533m_clk_gate_en: 1;    //  5
    UINT32 reg_tzapb_clk_gate_en: 1;    //     6
    UINT32 reg_xtal_clk_w_gate_en: 1;    //    7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_matrix_200m_n: 1;    //  0
    UINT32 reg_soft_rst_cnt_xtal_n: 1;    //   1
    UINT32 reg_soft_rst_core_apb_200m_n: 1;    //  2
    UINT32 reg_soft_rst_cssys_200m_n: 1;    //  3
    UINT32 reg_soft_rst_def_slave_200m_n: 1;    //  4
    UINT32 reg_soft_rst_dma_apb0_200m_n: 1;    //  5
    UINT32 reg_soft_rst_dma_apb1_200m_n: 1;    //  6
    UINT32 reg_soft_rst_dmac_200m_n: 1;    //  7
    UINT32 reg_soft_rst_dvb_ci_25m_n: 1;    //  8
    UINT32 reg_soft_rst_gic400_533m_n: 1;    //  9
    UINT32 reg_soft_rst_gpio0_200m_n: 1;    //  10
    UINT32 reg_soft_rst_gpio10_200m_n: 1;    //  11
    UINT32 reg_soft_rst_gpio11_200m_n: 1;    //  12
    UINT32 reg_soft_rst_gpio12_200m_n: 1;    //  13
    UINT32 reg_soft_rst_gpio13_200m_n: 1;    //  14
    UINT32 reg_soft_rst_gpio14_200m_n: 1;    //  15
    UINT32 reg_soft_rst_gpio15_200m_n: 1;    //  16
    UINT32 reg_soft_rst_gpio16_200m_n: 1;    //  17
    UINT32 reg_soft_rst_gpio17_200m_n: 1;    //  18
    UINT32 reg_soft_rst_gpio1_200m_n: 1;    //  19
    UINT32 reg_soft_rst_gpio2_200m_n: 1;    //  20
    UINT32 reg_soft_rst_gpio3_200m_n: 1;    //  21
    UINT32 reg_soft_rst_gpio4_200m_n: 1;    //  22
    UINT32 reg_soft_rst_gpio5_200m_n: 1;    //  23
    UINT32 reg_soft_rst_gpio6_200m_n: 1;    //  24
    UINT32 reg_soft_rst_gpio7_200m_n: 1;    //  25
    UINT32 reg_soft_rst_gpio8_200m_n: 1;    //  26
    UINT32 reg_soft_rst_gpio9_200m_n: 1;    //  27
    UINT32 reg_soft_rst_i2c_0_200m_n: 1;    //  28
    UINT32 reg_soft_rst_i2c_1_200m_n: 1;    //  29
    UINT32 reg_soft_rst_i2c_2_200m_n: 1;    //  30
    UINT32 reg_soft_rst_i2c_3_200m_n: 1;    //  31
    };
}SCRG_CTRL_CPU_CRG_CPU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0010    crg_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_i2c_4_200m_n: 1;    //  0
    UINT32 reg_soft_rst_i2c_5_200m_n: 1;    //  1
    UINT32 reg_soft_rst_i2c_6_200m_n: 1;    //  2
    UINT32 reg_soft_rst_i2c_7_200m_n: 1;    //  3
    UINT32 reg_soft_rst_i2c_8_200m_n: 1;    //  4
    UINT32 reg_soft_rst_i2c_9_200m_n: 1;    //  5
    UINT32 reg_soft_rst_irblaster_200m_n: 1;    //  6
    UINT32 reg_soft_rst_p_cpu_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_cpu_1_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_cpu_2_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_emusb_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_epusb_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_isol_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_micom_1_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_peri_bus_200m_n: 1;    //  14
    UINT32 reg_soft_rst_peri_bus_533m_n: 1;    //  15
    UINT32 reg_soft_rst_remap_200m_n: 1;    //  16
    UINT32 reg_soft_rst_sc_533m_n: 1;    //   17
    UINT32 reg_soft_rst_sci_200m_n: 1;    //  18
    UINT32 reg_soft_rst_smc_200m_n: 1;    //  19
    UINT32 reg_soft_rst_spi_0_200m_n: 1;    //  20
    UINT32 reg_soft_rst_spi_0_apb_200m_n: 1;    //  21
    UINT32 reg_soft_rst_spi_1_200m_n: 1;    //  22
    UINT32 reg_soft_rst_spi_1_apb_200m_n: 1;    //  23
    UINT32 reg_soft_rst_sram_ctrl_200m_n: 1;    //  24
    UINT32 reg_soft_rst_timer64_200m_n: 1;    //  25
    UINT32 reg_soft_rst_timer_200m_n: 1;    //  26
    UINT32 reg_soft_rst_top_ctrl_200m_n: 1;    //  27
    UINT32 reg_soft_rst_tzapb_n: 1;    //     28
    UINT32 reg_soft_rst_tzram_200m_n: 1;    //  29
    UINT32 reg_soft_rst_tzrom_200m_n: 1;    //  30
    UINT32 reg_soft_rst_uart0_200m_n: 1;    //  31
    };
}SCRG_CTRL_CPU_CRG_CPU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0014    crg_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_uart0_apb_200m_n: 1;    //  0
    UINT32 reg_soft_rst_uart1_200m_n: 1;    //  1
    UINT32 reg_soft_rst_uart1_apb_200m_n: 1;    //  2
    UINT32 reg_soft_rst_uart2_200m_n: 1;    //  3
    UINT32 reg_soft_rst_uart2_apb_200m_n: 1;    //  4
    UINT32 reg_soft_rst_wdt_200m_n: 1;    //   5
    UINT32 reg_soft_rst_wdt_apb_200m_n: 1;    //  6
    UINT32 reg_soft_rst_x_cpu_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_cpu_0_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_cpu_1_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_cpu_1_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_cpu_2_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_cpu_2_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_emusb_0_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_epusb_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_isol_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_micom_1_axi_n: 1;    //  16
    UINT32 reg_soft_rst_zdec_533m_n: 1;    //  17
    UINT32 reg_soft_rst_zenc_533m_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0018    crg_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_o_cpu_clk_sel  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU00_M23A0_T    crg_cpu00  ;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU01_M23A0_T    crg_cpu01  ;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU02_M23A0_T    crg_cpu02  ;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU03_M23A0_T    crg_cpu03  ;             // 0xCA21_000C
    SCRG_CTRL_CPU_CRG_CPU04_M23A0_T    crg_cpu04  ;             // 0xCA21_0010
    SCRG_CTRL_CPU_CRG_CPU05_M23A0_T    crg_cpu05  ;             // 0xCA21_0014
    SCRG_CTRL_CPU_CRG_CPU06_M23A0_T    crg_cpu06  ;             // 0xCA21_0018
}SCRG_CTRL_CPU_REG_M23A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

