#ifndef _BCRG_CTRL_LNX1_REG_O26A0_H_
#define _BCRG_CTRL_LNX1_REG_O26A0_H_

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
    0xCC5C_1000    crg_bnd_lnx1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LNX1_CRG_BND_LNX1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1004    crg_bnd_lnx1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LNX1_CRG_BND_LNX1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1008    crg_bnd_lnx1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lnx1_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX1_CRG_BND_LNX1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_100C    crg_bnd_lnx1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_lnx0_0_n: 1,    //   1
    reg_soft_rst_axi_brdg_te_0_n: 1,    //     2
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_LNX1_CRG_BND_LNX1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1010    crg_bnd_lnx1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lnx1_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX1_CRG_BND_LNX1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX1_CRG_BND_LNX1000_O26A0_T    crg_bnd_lnx1000;    // 0xCC5C_1000
    BCRG_CTRL_LNX1_CRG_BND_LNX1001_O26A0_T    crg_bnd_lnx1001;    // 0xCC5C_1004
    BCRG_CTRL_LNX1_CRG_BND_LNX1002_O26A0_T    crg_bnd_lnx1002;    // 0xCC5C_1008
    BCRG_CTRL_LNX1_CRG_BND_LNX1003_O26A0_T    crg_bnd_lnx1003;    // 0xCC5C_100C
    BCRG_CTRL_LNX1_CRG_BND_LNX1004_O26A0_T    crg_bnd_lnx1004;    // 0xCC5C_1010
}BCRG_CTRL_LNX1_REG_O26A0_T;
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

#define BCRG_CTRL_LNX1_CRG_BND_LNX1000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define BCRG_CTRL_LNX1_CRG_BND_LNX1001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define BCRG_CTRL_LNX1_CRG_BND_LNX1002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define BCRG_CTRL_LNX1_CRG_BND_LNX1003_O26A0_T_OFF          (BASEADDRESS+0x000C)
#define BCRG_CTRL_LNX1_CRG_BND_LNX1004_O26A0_T_OFF          (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC5C_1000    crg_bnd_lnx1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LNX1_CRG_BND_LNX1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1004    crg_bnd_lnx1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LNX1_CRG_BND_LNX1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1008    crg_bnd_lnx1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lnx1_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX1_CRG_BND_LNX1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_100C    crg_bnd_lnx1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_lnx0_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_te_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_LNX1_CRG_BND_LNX1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_1010    crg_bnd_lnx1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lnx1_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX1_CRG_BND_LNX1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX1_CRG_BND_LNX1000_O26A0_T    crg_bnd_lnx1000;    // 0xCC5C_1000
    BCRG_CTRL_LNX1_CRG_BND_LNX1001_O26A0_T    crg_bnd_lnx1001;    // 0xCC5C_1004
    BCRG_CTRL_LNX1_CRG_BND_LNX1002_O26A0_T    crg_bnd_lnx1002;    // 0xCC5C_1008
    BCRG_CTRL_LNX1_CRG_BND_LNX1003_O26A0_T    crg_bnd_lnx1003;    // 0xCC5C_100C
    BCRG_CTRL_LNX1_CRG_BND_LNX1004_O26A0_T    crg_bnd_lnx1004;    // 0xCC5C_1010
}BCRG_CTRL_LNX1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_LNX1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

