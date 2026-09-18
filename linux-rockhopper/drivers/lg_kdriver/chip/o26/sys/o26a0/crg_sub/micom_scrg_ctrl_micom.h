#ifndef _MICOM_SCRG_CTRL_MICOM_REG_O26A0_H_
#define _MICOM_SCRG_CTRL_MICOM_REG_O26A0_H_

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
    0xF339_0000    crg_micom000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0004    crg_micom001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0008    crg_micom002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_cpu_4__micom_bus_clk_gate_en: 1,    //  0
    reg_adaptx_x_micom_0__micom_bus_clk_gate_en: 1,    //  1
    reg_micom_bus_clk_gate_en :  1,    //      2
    reg_micom_peri_clk_gate_en:  1,    //      3
    reg_micom_rtc_ir_clk_gate_en: 1,    //     4
    reg_micom_spi_clk_gate_en :  1,    //      5
                              : 26;    //   31:6 reserved
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_000C    crg_micom003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_micom_bus_apbtout_n: 1,    //  0
    reg_soft_rst_micom_bus_n  :  1,    //      1
    reg_soft_rst_micom_cm0p_n :  1,    //      2
    reg_soft_rst_micom_peri_bdp_n: 1,    //    3
    reg_soft_rst_micom_peri_gpio0_n: 1,    //  4
    reg_soft_rst_micom_peri_gpio1_n: 1,    //  5
    reg_soft_rst_micom_peri_gpio2_n: 1,    //  6
    reg_soft_rst_micom_peri_gpio3_n: 1,    //  7
    reg_soft_rst_micom_peri_gpio4_n: 1,    //  8
    reg_soft_rst_micom_peri_gpio5_n: 1,    //  9
    reg_soft_rst_micom_peri_i2c0_n: 1,    //  10
    reg_soft_rst_micom_peri_i2c1_n: 1,    //  11
    reg_soft_rst_micom_peri_ir_n: 1,    //    12
    reg_soft_rst_micom_peri_n :  1,    //     13
    reg_soft_rst_micom_peri_p2i_n: 1,    //   14
    reg_soft_rst_micom_peri_p2r_n: 1,    //   15
    reg_soft_rst_micom_peri_pwm0_n: 1,    //  16
    reg_soft_rst_micom_peri_pwm1_n: 1,    //  17
    reg_soft_rst_micom_peri_pwm2_n: 1,    //  18
    reg_soft_rst_micom_peri_rtc_n: 1,    //   19
    reg_soft_rst_micom_peri_sadcintr_n: 1,    //  20
    reg_soft_rst_micom_peri_spi_n: 1,    //   21
    reg_soft_rst_micom_peri_timer0_n: 1,    //  22
    reg_soft_rst_micom_peri_timer1_n: 1,    //  23
    reg_soft_rst_micom_peri_topctrl_n: 1,    //  24
    reg_soft_rst_micom_peri_uart0_n: 1,    //  25
    reg_soft_rst_micom_peri_uart1_n: 1,    //  26
    reg_soft_rst_micom_peri_wdt_n: 1,    //   27
    reg_soft_rst_p_cpu_4_axi_bnd_n: 1,    //  28
    reg_soft_rst_p_micom_0_axi_bnd_n: 1,    //  29
    reg_soft_rst_x_cpu_4_axi_n:  1,    //     30
    reg_soft_rst_x_micom_0_axi_n: 1;    //    31
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0010    crg_micom004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_spi_clk_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_micom Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM000_O26A0_T    crg_micom000;    // 0xF339_0000
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM001_O26A0_T    crg_micom001;    // 0xF339_0004
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM002_O26A0_T    crg_micom002;    // 0xF339_0008
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM003_O26A0_T    crg_micom003;    // 0xF339_000C
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM004_O26A0_T    crg_micom004;    // 0xF339_0010
}MICOM_SCRG_CTRL_MICOM_REG_O26A0_T;
/* 5 regs */

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

#define MICOM_SCRG_CTRL_MICOM_CRG_MICOM000_O26A0_T_OFF      (BASEADDRESS+0x0000)
#define MICOM_SCRG_CTRL_MICOM_CRG_MICOM001_O26A0_T_OFF      (BASEADDRESS+0x0004)
#define MICOM_SCRG_CTRL_MICOM_CRG_MICOM002_O26A0_T_OFF      (BASEADDRESS+0x0008)
#define MICOM_SCRG_CTRL_MICOM_CRG_MICOM003_O26A0_T_OFF      (BASEADDRESS+0x000C)
#define MICOM_SCRG_CTRL_MICOM_CRG_MICOM004_O26A0_T_OFF      (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xF339_0000    crg_micom000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0004    crg_micom001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0008    crg_micom002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_cpu_4__micom_bus_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_micom_0__micom_bus_clk_gate_en: 1;    //  1
    UINT32 reg_micom_bus_clk_gate_en: 1;    //  2
    UINT32 reg_micom_peri_clk_gate_en: 1;    //  3
    UINT32 reg_micom_rtc_ir_clk_gate_en: 1;    //  4
    UINT32 reg_micom_spi_clk_gate_en: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_000C    crg_micom003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_micom_bus_apbtout_n: 1;    //  0
    UINT32 reg_soft_rst_micom_bus_n: 1;    //  1
    UINT32 reg_soft_rst_micom_cm0p_n: 1;    //  2
    UINT32 reg_soft_rst_micom_peri_bdp_n: 1;    //  3
    UINT32 reg_soft_rst_micom_peri_gpio0_n: 1;    //  4
    UINT32 reg_soft_rst_micom_peri_gpio1_n: 1;    //  5
    UINT32 reg_soft_rst_micom_peri_gpio2_n: 1;    //  6
    UINT32 reg_soft_rst_micom_peri_gpio3_n: 1;    //  7
    UINT32 reg_soft_rst_micom_peri_gpio4_n: 1;    //  8
    UINT32 reg_soft_rst_micom_peri_gpio5_n: 1;    //  9
    UINT32 reg_soft_rst_micom_peri_i2c0_n: 1;    //  10
    UINT32 reg_soft_rst_micom_peri_i2c1_n: 1;    //  11
    UINT32 reg_soft_rst_micom_peri_ir_n: 1;    //  12
    UINT32 reg_soft_rst_micom_peri_n: 1;    //  13
    UINT32 reg_soft_rst_micom_peri_p2i_n: 1;    //  14
    UINT32 reg_soft_rst_micom_peri_p2r_n: 1;    //  15
    UINT32 reg_soft_rst_micom_peri_pwm0_n: 1;    //  16
    UINT32 reg_soft_rst_micom_peri_pwm1_n: 1;    //  17
    UINT32 reg_soft_rst_micom_peri_pwm2_n: 1;    //  18
    UINT32 reg_soft_rst_micom_peri_rtc_n: 1;    //  19
    UINT32 reg_soft_rst_micom_peri_sadcintr_n: 1;    //  20
    UINT32 reg_soft_rst_micom_peri_spi_n: 1;    //  21
    UINT32 reg_soft_rst_micom_peri_timer0_n: 1;    //  22
    UINT32 reg_soft_rst_micom_peri_timer1_n: 1;    //  23
    UINT32 reg_soft_rst_micom_peri_topctrl_n: 1;    //  24
    UINT32 reg_soft_rst_micom_peri_uart0_n: 1;    //  25
    UINT32 reg_soft_rst_micom_peri_uart1_n: 1;    //  26
    UINT32 reg_soft_rst_micom_peri_wdt_n: 1;    //  27
    UINT32 reg_soft_rst_p_cpu_4_axi_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_p_micom_0_axi_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_x_cpu_4_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_micom_0_axi_n: 1;    //  31
    };
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF339_0010    crg_micom004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_spi_clk_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_SCRG_CTRL_MICOM_CRG_MICOM004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_micom Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM000_O26A0_T    crg_micom000;    // 0xF339_0000
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM001_O26A0_T    crg_micom001;    // 0xF339_0004
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM002_O26A0_T    crg_micom002;    // 0xF339_0008
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM003_O26A0_T    crg_micom003;    // 0xF339_000C
    MICOM_SCRG_CTRL_MICOM_CRG_MICOM004_O26A0_T    crg_micom004;    // 0xF339_0010
}MICOM_SCRG_CTRL_MICOM_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_SCRG_CTRL_MICOM_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

