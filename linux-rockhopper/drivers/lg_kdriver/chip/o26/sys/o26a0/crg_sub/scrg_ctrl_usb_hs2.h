#ifndef _SCRG_CTRL_USB_HS2_REG_H_
#define _SCRG_CTRL_USB_HS2_REG_H_

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
    0xC463_0000    crg_usb_hs2000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USB_HS2_CRG_USB_HS2000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_0004    crg_usb_hs2001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USB_HS2_CRG_USB_HS2001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_0008    crg_usb_hs2002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_usb_hs_2__usb_core_clk_gate_en: 1,    //  0
    reg_hs2_usb12_i_clk_gate_en: 1,    //      1
    reg_hs2_usb48_i_clk_gate_en: 1,    //      2
    reg_hs2_usb_core_clk_gate_en: 1,    //     3
    reg_hs2_usb_utmi60_i_clk_gate_en: 1,    //  4
    reg_xtal_clk_gate_en      :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_USB_HS2_CRG_USB_HS2002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_000C    crg_usb_hs2003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_hs_2_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb_aux_i_n  :  1,    //      1
    reg_soft_rst_usb_core_n   :  1,    //      2
    reg_soft_rst_usb_hreset_i_n: 1,    //      3
    reg_soft_rst_usb_phy_i_n  :  1,    //      4
    reg_soft_rst_usb_utmi_i_n :  1,    //      5
    reg_soft_rst_x_usb_hs_2_axi_n: 1,    //    6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_USB_HS2_CRG_USB_HS2003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS2_CRG_USB_HS2000_O26A0_T    crg_usb_hs2000;    // 0xC463_0000
    SCRG_CTRL_USB_HS2_CRG_USB_HS2001_O26A0_T    crg_usb_hs2001;    // 0xC463_0004
    SCRG_CTRL_USB_HS2_CRG_USB_HS2002_O26A0_T    crg_usb_hs2002;    // 0xC463_0008
    SCRG_CTRL_USB_HS2_CRG_USB_HS2003_O26A0_T    crg_usb_hs2003;    // 0xC463_000C
}SCRG_CTRL_USB_HS2_REG_O26A0_T;
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

#define SCRG_CTRL_USB_HS2_CRG_USB_HS2000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS2001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS2002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS2003_O26A0_T_OFF        (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC463_0000    crg_usb_hs2000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS2000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_0004    crg_usb_hs2001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS2001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_0008    crg_usb_hs2002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_usb_hs_2__usb_core_clk_gate_en: 1;    //  0
    UINT32 reg_hs2_usb12_i_clk_gate_en: 1;    //  1
    UINT32 reg_hs2_usb48_i_clk_gate_en: 1;    //  2
    UINT32 reg_hs2_usb_core_clk_gate_en: 1;    //  3
    UINT32 reg_hs2_usb_utmi60_i_clk_gate_en: 1;    //  4
    UINT32 reg_xtal_clk_gate_en: 1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS2002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC463_000C    crg_usb_hs2003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_hs_2_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb_aux_i_n: 1;    //  1
    UINT32 reg_soft_rst_usb_core_n: 1;    //   2
    UINT32 reg_soft_rst_usb_hreset_i_n: 1;    //  3
    UINT32 reg_soft_rst_usb_phy_i_n: 1;    //  4
    UINT32 reg_soft_rst_usb_utmi_i_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_hs_2_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS2003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS2_CRG_USB_HS2000_O26A0_T    crg_usb_hs2000;    // 0xC463_0000
    SCRG_CTRL_USB_HS2_CRG_USB_HS2001_O26A0_T    crg_usb_hs2001;    // 0xC463_0004
    SCRG_CTRL_USB_HS2_CRG_USB_HS2002_O26A0_T    crg_usb_hs2002;    // 0xC463_0008
    SCRG_CTRL_USB_HS2_CRG_USB_HS2003_O26A0_T    crg_usb_hs2003;    // 0xC463_000C
}SCRG_CTRL_USB_HS2_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_USB_HS2_REG_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.28  KJH by LGSiCRDV V3.1C*/

