#ifndef _BCRG_CTRL_ND1_REG_O24A0_H_
#define _BCRG_CTRL_ND1_REG_O24A0_H_

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
    0xCCCB_1000    crg_bnd_nd10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ND1_CRG_BND_ND10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_1004    crg_bnd_nd11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ND1_CRG_BND_ND11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_1008    crg_bnd_nd12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_nd1_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_usb_clk_gate_en: 1,    //   1
    reg_apb_ipw_usb_ss1_clk_gate_en: 1,    //  2
    reg_apb_ipw_usb_ss2_clk_gate_en: 1,    //  3
    reg_apb_ipw_usb_ss3_clk_gate_en: 1,    //  4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_ND1_CRG_BND_ND12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_100C    crg_bnd_nd13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_nd1_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_usb_n: 1,    //    1
    reg_soft_rst_apb_ipw_usb_ss1_n: 1,    //   2
    reg_soft_rst_apb_ipw_usb_ss2_n: 1,    //   3
    reg_soft_rst_apb_ipw_usb_ss3_n: 1,    //   4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_ND1_CRG_BND_ND13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND1_CRG_BND_ND10_O24A0_T    crg_bnd_nd10;         // 0xCCCB_1000
    BCRG_CTRL_ND1_CRG_BND_ND11_O24A0_T    crg_bnd_nd11;         // 0xCCCB_1004
    BCRG_CTRL_ND1_CRG_BND_ND12_O24A0_T    crg_bnd_nd12;         // 0xCCCB_1008
    BCRG_CTRL_ND1_CRG_BND_ND13_O24A0_T    crg_bnd_nd13;         // 0xCCCB_100C
}BCRG_CTRL_ND1_REG_O24A0_T;
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

#define BCRG_CTRL_ND1_CRG_BND_ND10_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_ND1_CRG_BND_ND11_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_ND1_CRG_BND_ND12_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_ND1_CRG_BND_ND13_O24A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCCB_1000    crg_bnd_nd10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ND1_CRG_BND_ND10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_1004    crg_bnd_nd11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ND1_CRG_BND_ND11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_1008    crg_bnd_nd12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_nd1_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_usb_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_usb_ss1_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_usb_ss2_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_usb_ss3_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_ND1_CRG_BND_ND12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_100C    crg_bnd_nd13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_nd1_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_usb_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_usb_ss1_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_usb_ss2_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_usb_ss3_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_ND1_CRG_BND_ND13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND1_CRG_BND_ND10_O24A0_T    crg_bnd_nd10;         // 0xCCCB_1000
    BCRG_CTRL_ND1_CRG_BND_ND11_O24A0_T    crg_bnd_nd11;         // 0xCCCB_1004
    BCRG_CTRL_ND1_CRG_BND_ND12_O24A0_T    crg_bnd_nd12;         // 0xCCCB_1008
    BCRG_CTRL_ND1_CRG_BND_ND13_O24A0_T    crg_bnd_nd13;         // 0xCCCB_100C
}BCRG_CTRL_ND1_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_ND1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

