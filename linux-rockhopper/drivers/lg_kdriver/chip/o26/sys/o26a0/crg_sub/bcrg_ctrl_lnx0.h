#ifndef _BCRG_CTRL_LNX0_REG_O26A0_H_
#define _BCRG_CTRL_LNX0_REG_O26A0_H_

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
    0xCC58_1000    crg_bnd_lnx0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LNX0_CRG_BND_LNX0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1004    crg_bnd_lnx0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LNX0_CRG_BND_LNX0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1008    crg_bnd_lnx0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_brdg_aud_0_clk_gate_en: 1,    //   0
    reg_axi_brdg_te_0_clk_gate_en: 1,    //    1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_100C    crg_bnd_lnx0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lnx0_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1010    crg_bnd_lnx0004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_te_0_n: 1,    //     1
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1014    crg_bnd_lnx0005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lnx0_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX0005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX0_CRG_BND_LNX0000_O26A0_T    crg_bnd_lnx0000;    // 0xCC58_1000
    BCRG_CTRL_LNX0_CRG_BND_LNX0001_O26A0_T    crg_bnd_lnx0001;    // 0xCC58_1004
    BCRG_CTRL_LNX0_CRG_BND_LNX0002_O26A0_T    crg_bnd_lnx0002;    // 0xCC58_1008
    BCRG_CTRL_LNX0_CRG_BND_LNX0003_O26A0_T    crg_bnd_lnx0003;    // 0xCC58_100C
    BCRG_CTRL_LNX0_CRG_BND_LNX0004_O26A0_T    crg_bnd_lnx0004;    // 0xCC58_1010
    BCRG_CTRL_LNX0_CRG_BND_LNX0005_O26A0_T    crg_bnd_lnx0005;    // 0xCC58_1014
}BCRG_CTRL_LNX0_REG_O26A0_T;
/* 6 regs */

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

#define BCRG_CTRL_LNX0_CRG_BND_LNX0000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define BCRG_CTRL_LNX0_CRG_BND_LNX0001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define BCRG_CTRL_LNX0_CRG_BND_LNX0002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define BCRG_CTRL_LNX0_CRG_BND_LNX0003_O26A0_T_OFF          (BASEADDRESS+0x000C)
#define BCRG_CTRL_LNX0_CRG_BND_LNX0004_O26A0_T_OFF          (BASEADDRESS+0x0010)
#define BCRG_CTRL_LNX0_CRG_BND_LNX0005_O26A0_T_OFF          (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC58_1000    crg_bnd_lnx0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1004    crg_bnd_lnx0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1008    crg_bnd_lnx0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_brdg_aud_0_clk_gate_en: 1;    //  0
    UINT32 reg_axi_brdg_te_0_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_100C    crg_bnd_lnx0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lnx0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1010    crg_bnd_lnx0004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_te_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_1014    crg_bnd_lnx0005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lnx0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX0005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX0_CRG_BND_LNX0000_O26A0_T    crg_bnd_lnx0000;    // 0xCC58_1000
    BCRG_CTRL_LNX0_CRG_BND_LNX0001_O26A0_T    crg_bnd_lnx0001;    // 0xCC58_1004
    BCRG_CTRL_LNX0_CRG_BND_LNX0002_O26A0_T    crg_bnd_lnx0002;    // 0xCC58_1008
    BCRG_CTRL_LNX0_CRG_BND_LNX0003_O26A0_T    crg_bnd_lnx0003;    // 0xCC58_100C
    BCRG_CTRL_LNX0_CRG_BND_LNX0004_O26A0_T    crg_bnd_lnx0004;    // 0xCC58_1010
    BCRG_CTRL_LNX0_CRG_BND_LNX0005_O26A0_T    crg_bnd_lnx0005;    // 0xCC58_1014
}BCRG_CTRL_LNX0_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_LNX0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

