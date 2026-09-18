#ifndef _SCRG_CTRL_USB_HS2_M23A0_REG_H_
#define _SCRG_CTRL_USB_HS2_M23A0_REG_H_

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
    0xC811_0000    crg_usb_hs200 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USB_HS2_CRG_USB_HS200_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_0004    crg_usb_hs201 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USB_HS2_CRG_USB_HS201_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_0008    crg_usb_hs202 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb12_hs2_i_clk_gate_en: 1,    //      0
    reg_usb48_hs2_i_clk_gate_en: 1,    //      1
    reg_usb_hs2_core_clk_gate_en: 1,    //     2
    reg_usb_utmi60_hs2_i_clk_gate_en: 1,    //  3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_USB_HS2_CRG_USB_HS202_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_000C    crg_usb_hs203 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_hs_0_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb_aux_i_n  :  1,    //      1
    reg_soft_rst_usb_core_n   :  1,    //      2
    reg_soft_rst_usb_hreset_i_n: 1,    //      3
    reg_soft_rst_usb_phy_i    :  1,    //      4
    reg_soft_rst_usb_utmi_i_n :  1,    //      5
    reg_soft_rst_x_usb_hs_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_usb_hs_0_axi_n: 1,    //    7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_USB_HS2_CRG_USB_HS203_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS2_CRG_USB_HS200_M23A0_T    crg_usb_hs200;    // 0xC811_0000
    SCRG_CTRL_USB_HS2_CRG_USB_HS201_M23A0_T    crg_usb_hs201;    // 0xC811_0004
    SCRG_CTRL_USB_HS2_CRG_USB_HS202_M23A0_T    crg_usb_hs202;    // 0xC811_0008
    SCRG_CTRL_USB_HS2_CRG_USB_HS203_M23A0_T    crg_usb_hs203;    // 0xC811_000C
}SCRG_CTRL_USB_HS2_REG_M23A0_T;
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

#define SCRG_CTRL_USB_HS2_CRG_USB_HS200_M23A0_T_OFF         (BASEADDRESS+0x0000)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS201_M23A0_T_OFF         (BASEADDRESS+0x0004)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS202_M23A0_T_OFF         (BASEADDRESS+0x0008)
#define SCRG_CTRL_USB_HS2_CRG_USB_HS203_M23A0_T_OFF         (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC811_0000    crg_usb_hs200 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS200_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_0004    crg_usb_hs201 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS201_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_0008    crg_usb_hs202 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb12_hs2_i_clk_gate_en: 1;    //  0
    UINT32 reg_usb48_hs2_i_clk_gate_en: 1;    //  1
    UINT32 reg_usb_hs2_core_clk_gate_en: 1;    //  2
    UINT32 reg_usb_utmi60_hs2_i_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS202_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC811_000C    crg_usb_hs203 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_hs_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb_aux_i_n: 1;    //  1
    UINT32 reg_soft_rst_usb_core_n: 1;    //   2
    UINT32 reg_soft_rst_usb_hreset_i_n: 1;    //  3
    UINT32 reg_soft_rst_usb_phy_i: 1;    //    4
    UINT32 reg_soft_rst_usb_utmi_i_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_hs_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_usb_hs_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_USB_HS2_CRG_USB_HS203_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_hs2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_HS2_CRG_USB_HS200_M23A0_T    crg_usb_hs200;    // 0xC811_0000
    SCRG_CTRL_USB_HS2_CRG_USB_HS201_M23A0_T    crg_usb_hs201;    // 0xC811_0004
    SCRG_CTRL_USB_HS2_CRG_USB_HS202_M23A0_T    crg_usb_hs202;    // 0xC811_0008
    SCRG_CTRL_USB_HS2_CRG_USB_HS203_M23A0_T    crg_usb_hs203;    // 0xC811_000C
}SCRG_CTRL_USB_HS2_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

