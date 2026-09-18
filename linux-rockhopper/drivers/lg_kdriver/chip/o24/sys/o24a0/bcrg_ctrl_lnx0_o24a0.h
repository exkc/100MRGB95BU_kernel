#ifndef _BCRG_CTRL_LNX0_REG_O24A0_H_
#define _BCRG_CTRL_LNX0_REG_O24A0_H_

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
    0xCC9E_1000    crg_bnd_lnx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LNX0_CRG_BND_LNX00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1004    crg_bnd_lnx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LNX0_CRG_BND_LNX01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1008    crg_bnd_lnx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lnx0_clk_gate_en: 1,    //     0
    reg_apb_ipw_usb_ss4_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_100C    crg_bnd_lnx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_lnx2_0_n: 1,    //   0
    reg_soft_rst_axi_brdg_usb_ss4_n: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1010    crg_bnd_lnx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lnx0_n: 1,    //      0
    reg_soft_rst_apb_ipw_usb_ss4_n: 1,    //   1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LNX0_CRG_BND_LNX04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX0_CRG_BND_LNX00_O24A0_T    crg_bnd_lnx00;      // 0xCC9E_1000
    BCRG_CTRL_LNX0_CRG_BND_LNX01_O24A0_T    crg_bnd_lnx01;      // 0xCC9E_1004
    BCRG_CTRL_LNX0_CRG_BND_LNX02_O24A0_T    crg_bnd_lnx02;      // 0xCC9E_1008
    BCRG_CTRL_LNX0_CRG_BND_LNX03_O24A0_T    crg_bnd_lnx03;      // 0xCC9E_100C
    BCRG_CTRL_LNX0_CRG_BND_LNX04_O24A0_T    crg_bnd_lnx04;      // 0xCC9E_1010
}BCRG_CTRL_LNX0_REG_O24A0_T;
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

#define BCRG_CTRL_LNX0_CRG_BND_LNX00_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_LNX0_CRG_BND_LNX01_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_LNX0_CRG_BND_LNX02_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_LNX0_CRG_BND_LNX03_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_LNX0_CRG_BND_LNX04_O24A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC9E_1000    crg_bnd_lnx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1004    crg_bnd_lnx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1008    crg_bnd_lnx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lnx0_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_usb_ss4_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_100C    crg_bnd_lnx03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_lnx2_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_usb_ss4_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_1010    crg_bnd_lnx04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lnx0_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_usb_ss4_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LNX0_CRG_BND_LNX04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX0_CRG_BND_LNX00_O24A0_T    crg_bnd_lnx00;      // 0xCC9E_1000
    BCRG_CTRL_LNX0_CRG_BND_LNX01_O24A0_T    crg_bnd_lnx01;      // 0xCC9E_1004
    BCRG_CTRL_LNX0_CRG_BND_LNX02_O24A0_T    crg_bnd_lnx02;      // 0xCC9E_1008
    BCRG_CTRL_LNX0_CRG_BND_LNX03_O24A0_T    crg_bnd_lnx03;      // 0xCC9E_100C
    BCRG_CTRL_LNX0_CRG_BND_LNX04_O24A0_T    crg_bnd_lnx04;      // 0xCC9E_1010
}BCRG_CTRL_LNX0_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_LNX0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

