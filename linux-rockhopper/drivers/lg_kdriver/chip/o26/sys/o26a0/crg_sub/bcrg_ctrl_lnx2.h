#ifndef _BCRG_CTRL_LNX2_REG_O26A0_H_
#define _BCRG_CTRL_LNX2_REG_O26A0_H_

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
    0xCC60_1000    crg_bnd_lnx2000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LNX2_CRG_BND_LNX2000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1004    crg_bnd_lnx2001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LNX2_CRG_BND_LNX2001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1008    crg_bnd_lnx2002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_ion1_clk_gate_en: 1,    //     0
    reg_apb_ipw_lnx2_clk_gate_en: 1,    //     1
    reg_apb_ipw_usb_hs1_clk_gate_en: 1,    //  2
    reg_apb_ipw_usb_hs2_clk_gate_en: 1,    //  3
    reg_apb_ipw_usb_hs3_clk_gate_en: 1,    //  4
    reg_apb_ipw_usbsb_clk_gate_en: 1,    //    5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX2002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_100C    crg_bnd_lnx2003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_isol_apb_n   :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX2003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1010    crg_bnd_lnx2004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_ion1_n: 1,    //      0
    reg_soft_rst_apb_ipw_lnx2_n: 1,    //      1
    reg_soft_rst_apb_ipw_usb_hs1_n: 1,    //   2
    reg_soft_rst_apb_ipw_usb_hs2_n: 1,    //   3
    reg_soft_rst_apb_ipw_usb_hs3_n: 1,    //   4
    reg_soft_rst_apb_ipw_usbsb_n: 1,    //     5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX2004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX2_CRG_BND_LNX2000_O26A0_T    crg_bnd_lnx2000;    // 0xCC60_1000
    BCRG_CTRL_LNX2_CRG_BND_LNX2001_O26A0_T    crg_bnd_lnx2001;    // 0xCC60_1004
    BCRG_CTRL_LNX2_CRG_BND_LNX2002_O26A0_T    crg_bnd_lnx2002;    // 0xCC60_1008
    BCRG_CTRL_LNX2_CRG_BND_LNX2003_O26A0_T    crg_bnd_lnx2003;    // 0xCC60_100C
    BCRG_CTRL_LNX2_CRG_BND_LNX2004_O26A0_T    crg_bnd_lnx2004;    // 0xCC60_1010
}BCRG_CTRL_LNX2_REG_O26A0_T;
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

#define BCRG_CTRL_LNX2_CRG_BND_LNX2000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define BCRG_CTRL_LNX2_CRG_BND_LNX2001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define BCRG_CTRL_LNX2_CRG_BND_LNX2002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define BCRG_CTRL_LNX2_CRG_BND_LNX2003_O26A0_T_OFF          (BASEADDRESS+0x000C)
#define BCRG_CTRL_LNX2_CRG_BND_LNX2004_O26A0_T_OFF          (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC60_1000    crg_bnd_lnx2000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX2000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1004    crg_bnd_lnx2001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX2001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1008    crg_bnd_lnx2002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_ion1_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_lnx2_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_usb_hs1_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_usb_hs2_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_usb_hs3_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_usbsb_clk_gate_en: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX2002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_100C    crg_bnd_lnx2003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_isol_apb_n: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX2003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_1010    crg_bnd_lnx2004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_ion1_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_lnx2_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_usb_hs1_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_usb_hs2_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_usb_hs3_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_usbsb_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX2004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX2_CRG_BND_LNX2000_O26A0_T    crg_bnd_lnx2000;    // 0xCC60_1000
    BCRG_CTRL_LNX2_CRG_BND_LNX2001_O26A0_T    crg_bnd_lnx2001;    // 0xCC60_1004
    BCRG_CTRL_LNX2_CRG_BND_LNX2002_O26A0_T    crg_bnd_lnx2002;    // 0xCC60_1008
    BCRG_CTRL_LNX2_CRG_BND_LNX2003_O26A0_T    crg_bnd_lnx2003;    // 0xCC60_100C
    BCRG_CTRL_LNX2_CRG_BND_LNX2004_O26A0_T    crg_bnd_lnx2004;    // 0xCC60_1010
}BCRG_CTRL_LNX2_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_LNX2_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

