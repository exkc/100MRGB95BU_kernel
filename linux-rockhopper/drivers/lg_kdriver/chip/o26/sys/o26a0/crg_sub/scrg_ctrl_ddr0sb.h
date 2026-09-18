#ifndef _SCRG_CTRL_DDR0SB_REG_H_
#define _SCRG_CTRL_DDR0SB_REG_H_

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
    0xC450_0000    crg_ddr0sb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DDR0SB_CRG_DDR0SB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_0004    crg_ddr0sb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DDR0SB_CRG_DDR0SB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_0008    crg_ddr0sb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x__cpu__bus_884_clk_gate_en: 1,    //  0
    reg_adaprx_x__lbus__bus_884_clk_gate_en: 1,    //  1
    reg_adaptx_x_ddr_0__bus_884_clk_gate_en: 1,    //  2
    reg_bus_884_clk_gate_en   :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_DDR0SB_CRG_DDR0SB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_000C    crg_ddr0sb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_884_n    :  1,    //      0
    reg_soft_rst_p__cpu_axi_bnd_n: 1,    //    1
    reg_soft_rst_p__lbus_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_ddr_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x__cpu_axi_n :  1,    //      4
    reg_soft_rst_x__lbus_axi_n:  1,    //      5
    reg_soft_rst_x_ddr_0_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_DDR0SB_CRG_DDR0SB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR0SB_CRG_DDR0SB000_O26A0_T    crg_ddr0sb000;    // 0xC450_0000
    SCRG_CTRL_DDR0SB_CRG_DDR0SB001_O26A0_T    crg_ddr0sb001;    // 0xC450_0004
    SCRG_CTRL_DDR0SB_CRG_DDR0SB002_O26A0_T    crg_ddr0sb002;    // 0xC450_0008
    SCRG_CTRL_DDR0SB_CRG_DDR0SB003_O26A0_T    crg_ddr0sb003;    // 0xC450_000C
}SCRG_CTRL_DDR0SB_REG_O26A0_T;
/* 4 regs */

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

#define SCRG_CTRL_DDR0SB_CRG_DDR0SB000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define SCRG_CTRL_DDR0SB_CRG_DDR0SB001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define SCRG_CTRL_DDR0SB_CRG_DDR0SB002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define SCRG_CTRL_DDR0SB_CRG_DDR0SB003_O26A0_T_OFF          (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC450_0000    crg_ddr0sb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DDR0SB_CRG_DDR0SB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_0004    crg_ddr0sb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DDR0SB_CRG_DDR0SB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_0008    crg_ddr0sb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x__cpu__bus_884_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x__lbus__bus_884_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_ddr_0__bus_884_clk_gate_en: 1;    //  2
    UINT32 reg_bus_884_clk_gate_en: 1;    //   3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_DDR0SB_CRG_DDR0SB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC450_000C    crg_ddr0sb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_884_n: 1;    //    0
    UINT32 reg_soft_rst_p__cpu_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p__lbus_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_ddr_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x__cpu_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x__lbus_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_ddr_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_DDR0SB_CRG_DDR0SB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR0SB_CRG_DDR0SB000_O26A0_T    crg_ddr0sb000;    // 0xC450_0000
    SCRG_CTRL_DDR0SB_CRG_DDR0SB001_O26A0_T    crg_ddr0sb001;    // 0xC450_0004
    SCRG_CTRL_DDR0SB_CRG_DDR0SB002_O26A0_T    crg_ddr0sb002;    // 0xC450_0008
    SCRG_CTRL_DDR0SB_CRG_DDR0SB003_O26A0_T    crg_ddr0sb003;    // 0xC450_000C
}SCRG_CTRL_DDR0SB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DDR0SB_REG_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.28  KJH by LGSiCRDV V3.1C*/

