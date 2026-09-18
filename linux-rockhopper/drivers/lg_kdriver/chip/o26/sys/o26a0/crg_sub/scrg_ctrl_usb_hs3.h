#ifndef _SCRG_CTRL_USB_HS3_REG_H_
#define _SCRG_CTRL_USB_HS3_REG_H_

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
    0xC465_0000    crg_usb_hs3000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USB_HS3_CRG_USB_HS3000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_0004    crg_usb_hs3001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USB_HS3_CRG_USB_HS3001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_0008    crg_usb_hs3002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_usb_hs_3__usb_core_clk_gate_en: 1,    //  0
    reg_hs3_usb12_i_clk_gate_en: 1,    //      1
    reg_hs3_usb48_i_clk_gate_en: 1,    //      2
    reg_hs3_usb_core_clk_gate_en: 1,    //     3
    reg_hs3_usb_utmi60_i_clk_gate_en: 1,    //  4
    reg_xtal_clk_gate_en      :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_USB_HS3_CRG_USB_HS3002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_000C    crg_usb_hs3003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_hs_3_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb_aux_i_n  :  1,    //      1
    reg_soft_rst_usb_core_n   :  1,    //      2
    reg_soft_rst_usb_hreset_i_n: 1,    //      3
    reg_soft_rst_usb_phy_i_n  :  1,    //      4
    reg_soft_rst_usb_utmi_i_n :  1,    //      5
    reg_soft_rst_x_usb_hs_3_axi_n: 1,    //    6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_USB_HS3_CRG_USB_HS3003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS3_CRG_USB_HS3000_O26A0_T    crg_usb_hs3000;    // 0xC465_0000
    SCRG_CTRL_USB_HS3_CRG_USB_HS3001_O26A0_T    crg_usb_hs3001;    // 0xC465_0004
    SCRG_CTRL_USB_HS3_CRG_USB_HS3002_O26A0_T    crg_usb_hs3002;    // 0xC465_0008
    SCRG_CTRL_USB_HS3_CRG_USB_HS3003_O26A0_T    crg_usb_hs3003;    // 0xC465_000C
}SCRG_CTRL_USB_HS3_REG_O26A0_T;
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

#define SCRG_CTRL_USB_HS3_CRG_USB_HS3000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define SCRG_CTRL_USB_HS3_CRG_USB_HS3001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define SCRG_CTRL_USB_HS3_CRG_USB_HS3002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define SCRG_CTRL_USB_HS3_CRG_USB_HS3003_O26A0_T_OFF        (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC465_0000    crg_usb_hs3000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS3_CRG_USB_HS3000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_0004    crg_usb_hs3001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS3_CRG_USB_HS3001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_0008    crg_usb_hs3002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_usb_hs_3__usb_core_clk_gate_en: 1;    //  0
    UINT32 reg_hs3_usb12_i_clk_gate_en: 1;    //  1
    UINT32 reg_hs3_usb48_i_clk_gate_en: 1;    //  2
    UINT32 reg_hs3_usb_core_clk_gate_en: 1;    //  3
    UINT32 reg_hs3_usb_utmi60_i_clk_gate_en: 1;    //  4
    UINT32 reg_xtal_clk_gate_en: 1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_USB_HS3_CRG_USB_HS3002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC465_000C    crg_usb_hs3003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_hs_3_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb_aux_i_n: 1;    //  1
    UINT32 reg_soft_rst_usb_core_n: 1;    //   2
    UINT32 reg_soft_rst_usb_hreset_i_n: 1;    //  3
    UINT32 reg_soft_rst_usb_phy_i_n: 1;    //  4
    UINT32 reg_soft_rst_usb_utmi_i_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_hs_3_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_USB_HS3_CRG_USB_HS3003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS3_CRG_USB_HS3000_O26A0_T    crg_usb_hs3000;    // 0xC465_0000
    SCRG_CTRL_USB_HS3_CRG_USB_HS3001_O26A0_T    crg_usb_hs3001;    // 0xC465_0004
    SCRG_CTRL_USB_HS3_CRG_USB_HS3002_O26A0_T    crg_usb_hs3002;    // 0xC465_0008
    SCRG_CTRL_USB_HS3_CRG_USB_HS3003_O26A0_T    crg_usb_hs3003;    // 0xC465_000C
}SCRG_CTRL_USB_HS3_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_USB_HS3_REG_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.28  KJH by LGSiCRDV V3.1C*/

