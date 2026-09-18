#ifndef _SCRG_CTRL_DDR1SB_REG_O24A0_H_
#define _SCRG_CTRL_DDR1SB_REG_O24A0_H_

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
    0xC41D_0000    crg_sb_ddr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DDR1SB_CRG_SB_DDR10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_0004    crg_sb_ddr11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DDR1SB_CRG_SB_DDR11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_0008    crg_sb_ddr12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_884_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_DDR1SB_CRG_SB_DDR12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_000C    crg_sb_ddr13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_884_n: 1,    //     0
    reg_soft_rst_p_cpu_1_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_ddr_1_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_lbus_4_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_cpu_1_axi_n:  1,    //      4
    reg_soft_rst_x_ddr_1_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_ddr_1_axi_n:  1,    //      6
    reg_soft_rst_x_lbus_4_axi_n: 1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_DDR1SB_CRG_SB_DDR13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr1sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR1SB_CRG_SB_DDR10_O24A0_T    crg_sb_ddr10;      // 0xC41D_0000
    SCRG_CTRL_DDR1SB_CRG_SB_DDR11_O24A0_T    crg_sb_ddr11;      // 0xC41D_0004
    SCRG_CTRL_DDR1SB_CRG_SB_DDR12_O24A0_T    crg_sb_ddr12;      // 0xC41D_0008
    SCRG_CTRL_DDR1SB_CRG_SB_DDR13_O24A0_T    crg_sb_ddr13;      // 0xC41D_000C
}SCRG_CTRL_DDR1SB_REG_O24A0_T;
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

#define SCRG_CTRL_DDR1SB_CRG_SB_DDR10_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define SCRG_CTRL_DDR1SB_CRG_SB_DDR11_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define SCRG_CTRL_DDR1SB_CRG_SB_DDR12_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define SCRG_CTRL_DDR1SB_CRG_SB_DDR13_O24A0_T_OFF           (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC41D_0000    crg_sb_ddr10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DDR1SB_CRG_SB_DDR10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_0004    crg_sb_ddr11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DDR1SB_CRG_SB_DDR11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_0008    crg_sb_ddr12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_DDR1SB_CRG_SB_DDR12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41D_000C    crg_sb_ddr13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_884_n: 1;    //  0
    UINT32 reg_soft_rst_p_cpu_1_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_ddr_1_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_lbus_4_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_cpu_1_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_ddr_1_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_ddr_1_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lbus_4_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_DDR1SB_CRG_SB_DDR13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddr1sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDR1SB_CRG_SB_DDR10_O24A0_T    crg_sb_ddr10;      // 0xC41D_0000
    SCRG_CTRL_DDR1SB_CRG_SB_DDR11_O24A0_T    crg_sb_ddr11;      // 0xC41D_0004
    SCRG_CTRL_DDR1SB_CRG_SB_DDR12_O24A0_T    crg_sb_ddr12;      // 0xC41D_0008
    SCRG_CTRL_DDR1SB_CRG_SB_DDR13_O24A0_T    crg_sb_ddr13;      // 0xC41D_000C
}SCRG_CTRL_DDR1SB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DDR1SB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

