#ifndef _SCRG_CTRL_DDR0SB_REG_O24A0_H_
#define _SCRG_CTRL_DDR0SB_REG_O24A0_H_

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
    0xC41C_0000    crg_sb_ddr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DDR0SB_CRG_SB_DDR00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_0004    crg_sb_ddr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DDR0SB_CRG_SB_DDR01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_0008    crg_sb_ddr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_884_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_DDR0SB_CRG_SB_DDR02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_000C    crg_sb_ddr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_884_n: 1,    //     0
    reg_soft_rst_p_cpu_0_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_ddr_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_lbus_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_cpu_0_axi_n:  1,    //      4
    reg_soft_rst_x_ddr_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_ddr_0_axi_n:  1,    //      6
    reg_soft_rst_x_lbus_0_axi_n: 1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_DDR0SB_CRG_SB_DDR03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR0SB_CRG_SB_DDR00_O24A0_T    crg_sb_ddr00;      // 0xC41C_0000
    SCRG_CTRL_DDR0SB_CRG_SB_DDR01_O24A0_T    crg_sb_ddr01;      // 0xC41C_0004
    SCRG_CTRL_DDR0SB_CRG_SB_DDR02_O24A0_T    crg_sb_ddr02;      // 0xC41C_0008
    SCRG_CTRL_DDR0SB_CRG_SB_DDR03_O24A0_T    crg_sb_ddr03;      // 0xC41C_000C
}SCRG_CTRL_DDR0SB_REG_O24A0_T;
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

#define SCRG_CTRL_DDR0SB_CRG_SB_DDR00_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define SCRG_CTRL_DDR0SB_CRG_SB_DDR01_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define SCRG_CTRL_DDR0SB_CRG_SB_DDR02_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define SCRG_CTRL_DDR0SB_CRG_SB_DDR03_O24A0_T_OFF           (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC41C_0000    crg_sb_ddr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DDR0SB_CRG_SB_DDR00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_0004    crg_sb_ddr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DDR0SB_CRG_SB_DDR01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_0008    crg_sb_ddr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_DDR0SB_CRG_SB_DDR02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41C_000C    crg_sb_ddr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_884_n: 1;    //  0
    UINT32 reg_soft_rst_p_cpu_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_ddr_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_lbus_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_cpu_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_ddr_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_ddr_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lbus_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_DDR0SB_CRG_SB_DDR03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR0SB_CRG_SB_DDR00_O24A0_T    crg_sb_ddr00;      // 0xC41C_0000
    SCRG_CTRL_DDR0SB_CRG_SB_DDR01_O24A0_T    crg_sb_ddr01;      // 0xC41C_0004
    SCRG_CTRL_DDR0SB_CRG_SB_DDR02_O24A0_T    crg_sb_ddr02;      // 0xC41C_0008
    SCRG_CTRL_DDR0SB_CRG_SB_DDR03_O24A0_T    crg_sb_ddr03;      // 0xC41C_000C
}SCRG_CTRL_DDR0SB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DDR0SB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

