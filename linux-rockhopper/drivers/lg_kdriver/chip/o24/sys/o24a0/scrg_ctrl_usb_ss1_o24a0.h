#ifndef _SCRG_CTRL_USB_SS1_REG_O24A0_H_
#define _SCRG_CTRL_USB_SS1_REG_O24A0_H_

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
    0xC8DB_0000    crg_usb_ss10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USB_SS1_CRG_USB_SS10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_0004    crg_usb_ss11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USB_SS1_CRG_USB_SS11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_0008    crg_usb_ss12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb3_core_clk_gate_en :  1,    //      0
    reg_usb3_ctrl_xtal_clk_gate_en: 1,    //   1
    reg_usb3_pipe_i_clk_gate_en: 1,    //      2
    reg_usb3_suspend_clk_gate_en: 1,    //     3
    reg_usb3_utmi_i_clk_gate_en: 1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_USB_SS1_CRG_USB_SS12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_000C    crg_usb_ss13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb2_phy_i   :  1,    //      1
    reg_soft_rst_usb3_con_i_n :  1,    //      2
    reg_soft_rst_usb3_core_n  :  1,    //      3
    reg_soft_rst_usb3_phy_i_n :  1,    //      4
    reg_soft_rst_x_usb_ss_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_usb_ss_0_axi_n: 1,    //    6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_USB_SS1_CRG_USB_SS13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_ss1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_SS1_CRG_USB_SS10_O24A0_T    crg_usb_ss10;     // 0xC8DB_0000
    SCRG_CTRL_USB_SS1_CRG_USB_SS11_O24A0_T    crg_usb_ss11;     // 0xC8DB_0004
    SCRG_CTRL_USB_SS1_CRG_USB_SS12_O24A0_T    crg_usb_ss12;     // 0xC8DB_0008
    SCRG_CTRL_USB_SS1_CRG_USB_SS13_O24A0_T    crg_usb_ss13;     // 0xC8DB_000C
}SCRG_CTRL_USB_SS1_REG_O24A0_T;
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

#define SCRG_CTRL_USB_SS1_CRG_USB_SS10_O24A0_T_OFF          (BASEADDRESS+0x0000)
#define SCRG_CTRL_USB_SS1_CRG_USB_SS11_O24A0_T_OFF          (BASEADDRESS+0x0004)
#define SCRG_CTRL_USB_SS1_CRG_USB_SS12_O24A0_T_OFF          (BASEADDRESS+0x0008)
#define SCRG_CTRL_USB_SS1_CRG_USB_SS13_O24A0_T_OFF          (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC8DB_0000    crg_usb_ss10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USB_SS1_CRG_USB_SS10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_0004    crg_usb_ss11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USB_SS1_CRG_USB_SS11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_0008    crg_usb_ss12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb3_core_clk_gate_en: 1;    //  0
    UINT32 reg_usb3_ctrl_xtal_clk_gate_en: 1;    //  1
    UINT32 reg_usb3_pipe_i_clk_gate_en: 1;    //  2
    UINT32 reg_usb3_suspend_clk_gate_en: 1;    //  3
    UINT32 reg_usb3_utmi_i_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_USB_SS1_CRG_USB_SS12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8DB_000C    crg_usb_ss13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb2_phy_i: 1;    //   1
    UINT32 reg_soft_rst_usb3_con_i_n: 1;    //  2
    UINT32 reg_soft_rst_usb3_core_n: 1;    //  3
    UINT32 reg_soft_rst_usb3_phy_i_n: 1;    //  4
    UINT32 reg_soft_rst_x_usb_ss_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_ss_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_USB_SS1_CRG_USB_SS13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_ss1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_SS1_CRG_USB_SS10_O24A0_T    crg_usb_ss10;     // 0xC8DB_0000
    SCRG_CTRL_USB_SS1_CRG_USB_SS11_O24A0_T    crg_usb_ss11;     // 0xC8DB_0004
    SCRG_CTRL_USB_SS1_CRG_USB_SS12_O24A0_T    crg_usb_ss12;     // 0xC8DB_0008
    SCRG_CTRL_USB_SS1_CRG_USB_SS13_O24A0_T    crg_usb_ss13;     // 0xC8DB_000C
}SCRG_CTRL_USB_SS1_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_USB_SS1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

