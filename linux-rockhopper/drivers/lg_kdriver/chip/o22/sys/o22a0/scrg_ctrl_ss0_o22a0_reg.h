#ifndef _SCRG_CTRL_SS0_REG_H_
#define _SCRG_CTRL_SS0_REG_H_

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
    0x3_0000    crg_usb_ss_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SS0_CRG_USB_SS_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0004    crg_usb_ss_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SS0_CRG_USB_SS_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0008    crg_usb_ss_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb3_core_clk_gate_en :  1,    //      0
    reg_usb3_ctrl_xtal_clk_gate_en: 1,    //   1
    reg_usb3_pipe_i_clk_gate_en: 1,    //      2
    reg_usb3_suspend_clk_gate_en: 1,    //     3
    reg_usb3_utmi_i_clk_gate_en: 1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_SS0_CRG_USB_SS_BMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_000C    crg_usb_ss_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb2_phy_i   :  1,    //      1
    reg_soft_rst_usb3_con_i_n :  1,    //      2
    reg_soft_rst_usb3_phy_i_n :  1,    //      3
    reg_soft_rst_usb_core_n   :  1,    //      4
    reg_soft_rst_x_usb_ss_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_usb_ss_0_axi_n: 1,    //    6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_SS0_CRG_USB_SS_BMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0010    crg_usb_ss_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb3_core_clk_skip_ctrl: 9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_SS0_CRG_USB_SS_BMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_ss_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SS0_CRG_USB_SS_BMC00_O22A0_T    crg_usb_ss_bmc00;    // 0x3_0000
    SCRG_CTRL_SS0_CRG_USB_SS_BMC01_O22A0_T    crg_usb_ss_bmc01;    // 0x3_0004
    SCRG_CTRL_SS0_CRG_USB_SS_BMC02_O22A0_T    crg_usb_ss_bmc02;    // 0x3_0008
    SCRG_CTRL_SS0_CRG_USB_SS_BMC03_O22A0_T    crg_usb_ss_bmc03;    // 0x3_000C
    SCRG_CTRL_SS0_CRG_USB_SS_BMC04_O22A0_T    crg_usb_ss_bmc04;    // 0x3_0010
}SCRG_CTRL_SS0_REG_O22A0_T;
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

#define SCRG_CTRL_SS0_CRG_USB_SS_BMC00_O22A0_T_OFF         (BASEADDRESS+0x0000)
#define SCRG_CTRL_SS0_CRG_USB_SS_BMC01_O22A0_T_OFF         (BASEADDRESS+0x0004)
#define SCRG_CTRL_SS0_CRG_USB_SS_BMC02_O22A0_T_OFF         (BASEADDRESS+0x0008)
#define SCRG_CTRL_SS0_CRG_USB_SS_BMC03_O22A0_T_OFF         (BASEADDRESS+0x000C)
#define SCRG_CTRL_SS0_CRG_USB_SS_BMC04_O22A0_T_OFF         (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x3_0000    crg_usb_ss_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SS0_CRG_USB_SS_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0004    crg_usb_ss_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SS0_CRG_USB_SS_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0008    crg_usb_ss_bmc02 ''
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
}SCRG_CTRL_SS0_CRG_USB_SS_BMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_000C    crg_usb_ss_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb2_phy_i: 1;    //   1
    UINT32 reg_soft_rst_usb3_con_i_n: 1;    //  2
    UINT32 reg_soft_rst_usb3_phy_i_n: 1;    //  3
    UINT32 reg_soft_rst_usb_core_n: 1;    //   4
    UINT32 reg_soft_rst_x_usb_ss_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_ss_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_SS0_CRG_USB_SS_BMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3_0010    crg_usb_ss_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb3_core_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_SS0_CRG_USB_SS_BMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_ss_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SS0_CRG_USB_SS_BMC00_O22A0_T    crg_usb_ss_bmc00;    // 0x3_0000
    SCRG_CTRL_SS0_CRG_USB_SS_BMC01_O22A0_T    crg_usb_ss_bmc01;    // 0x3_0004
    SCRG_CTRL_SS0_CRG_USB_SS_BMC02_O22A0_T    crg_usb_ss_bmc02;    // 0x3_0008
    SCRG_CTRL_SS0_CRG_USB_SS_BMC03_O22A0_T    crg_usb_ss_bmc03;    // 0x3_000C
    SCRG_CTRL_SS0_CRG_USB_SS_BMC04_O22A0_T    crg_usb_ss_bmc04;    // 0x3_0010
}SCRG_CTRL_SS0_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

