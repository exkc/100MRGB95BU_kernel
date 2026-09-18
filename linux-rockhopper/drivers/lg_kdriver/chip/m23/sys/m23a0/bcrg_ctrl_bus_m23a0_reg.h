#ifndef _BCRG_CTRL_BUS_M23A0_REG_H_
#define _BCRG_CTRL_BUS_M23A0_REG_H_

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
    0xCC7A_1000    crg_bnd_bus00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_BUS_CRG_BND_BUS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1004    crg_bnd_bus01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_BUS_CRG_BND_BUS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1008    crg_bnd_bus02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dne_clk_gate_en: 1,    //      0
    reg_apb_ipw_gfx_clk_gate_en: 1,    //      1
    reg_apb_ipw_lbus_clk_gate_en: 1,    //     2
    reg_apb_ipw_sb_ddr_clk_gate_en: 1,    //   3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_BUS_CRG_BND_BUS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_100C    crg_bnd_bus03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_emusb_0_n: 1,    //  0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BUS_CRG_BND_BUS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1010    crg_bnd_bus04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dne_n:  1,    //      0
    reg_soft_rst_apb_ipw_gfx_n:  1,    //      1
    reg_soft_rst_apb_ipw_lbus_n: 1,    //      2
    reg_soft_rst_apb_ipw_sb_ddr_n: 1,    //    3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_BUS_CRG_BND_BUS04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BUS_CRG_BND_BUS00_M23A0_T    crg_bnd_bus00;       // 0xCC7A_1000
    BCRG_CTRL_BUS_CRG_BND_BUS01_M23A0_T    crg_bnd_bus01;       // 0xCC7A_1004
    BCRG_CTRL_BUS_CRG_BND_BUS02_M23A0_T    crg_bnd_bus02;       // 0xCC7A_1008
    BCRG_CTRL_BUS_CRG_BND_BUS03_M23A0_T    crg_bnd_bus03;       // 0xCC7A_100C
    BCRG_CTRL_BUS_CRG_BND_BUS04_M23A0_T    crg_bnd_bus04;       // 0xCC7A_1010
}BCRG_CTRL_BUS_REG_M23A0_T;
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

#define BCRG_CTRL_BUS_CRG_BND_BUS00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_BUS_CRG_BND_BUS01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_BUS_CRG_BND_BUS02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_BUS_CRG_BND_BUS03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_BUS_CRG_BND_BUS04_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC7A_1000    crg_bnd_bus00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_BUS_CRG_BND_BUS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1004    crg_bnd_bus01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_BUS_CRG_BND_BUS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1008    crg_bnd_bus02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dne_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_gfx_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_lbus_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_sb_ddr_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_BUS_CRG_BND_BUS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_100C    crg_bnd_bus03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_emusb_0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BUS_CRG_BND_BUS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC7A_1010    crg_bnd_bus04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dne_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_gfx_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_lbus_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_sb_ddr_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_BUS_CRG_BND_BUS04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BUS_CRG_BND_BUS00_M23A0_T    crg_bnd_bus00;       // 0xCC7A_1000
    BCRG_CTRL_BUS_CRG_BND_BUS01_M23A0_T    crg_bnd_bus01;       // 0xCC7A_1004
    BCRG_CTRL_BUS_CRG_BND_BUS02_M23A0_T    crg_bnd_bus02;       // 0xCC7A_1008
    BCRG_CTRL_BUS_CRG_BND_BUS03_M23A0_T    crg_bnd_bus03;       // 0xCC7A_100C
    BCRG_CTRL_BUS_CRG_BND_BUS04_M23A0_T    crg_bnd_bus04;       // 0xCC7A_1010
}BCRG_CTRL_BUS_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

