#ifndef _SCRG_CTRL_USB_SS_REG_O26A0_H_
#define _SCRG_CTRL_USB_SS_REG_O26A0_H_

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
    0xC611_0000    crg_usb_ss000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USB_SS_CRG_USB_SS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0004    crg_usb_ss001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USB_SS_CRG_USB_SS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0008    crg_usb_ss002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_usb_ss_0__usb3_core_clk_gate_en: 1,    //  0
    reg_usb3_core_clk_gate_en :  1,    //      1
    reg_usb3_ctrl_xtal_clk_gate_en: 1,    //   2
    reg_usb3_pipe_i_clk_gate_en: 1,    //      3
    reg_usb3_suspend_clk_gate_en: 1,    //     4
    reg_usb3_utmi_i_clk_gate_en: 1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_USB_SS_CRG_USB_SS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_000C    crg_usb_ss003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1,    //  0
    reg_soft_rst_usb2_phy_i_n :  1,    //      1
    reg_soft_rst_usb3_con_i_n :  1,    //      2
    reg_soft_rst_usb3_core_n  :  1,    //      3
    reg_soft_rst_usb3_phy_i_n :  1,    //      4
    reg_soft_rst_x_usb_ss_0_axi_n: 1,    //    5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_USB_SS_CRG_USB_SS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_ss Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_SS_CRG_USB_SS000_O26A0_T    crg_usb_ss000;    // 0xC611_0000
    SCRG_CTRL_USB_SS_CRG_USB_SS001_O26A0_T    crg_usb_ss001;    // 0xC611_0004
    SCRG_CTRL_USB_SS_CRG_USB_SS002_O26A0_T    crg_usb_ss002;    // 0xC611_0008
    SCRG_CTRL_USB_SS_CRG_USB_SS003_O26A0_T    crg_usb_ss003;    // 0xC611_000C
}SCRG_CTRL_USB_SS_REG_O26A0_T;
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

#define SCRG_CTRL_USB_SS_CRG_USB_SS000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define SCRG_CTRL_USB_SS_CRG_USB_SS001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define SCRG_CTRL_USB_SS_CRG_USB_SS002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define SCRG_CTRL_USB_SS_CRG_USB_SS003_O26A0_T_OFF          (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC611_0000    crg_usb_ss000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USB_SS_CRG_USB_SS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0004    crg_usb_ss001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USB_SS_CRG_USB_SS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0008    crg_usb_ss002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_usb_ss_0__usb3_core_clk_gate_en: 1;    //  0
    UINT32 reg_usb3_core_clk_gate_en: 1;    //  1
    UINT32 reg_usb3_ctrl_xtal_clk_gate_en: 1;    //  2
    UINT32 reg_usb3_pipe_i_clk_gate_en: 1;    //  3
    UINT32 reg_usb3_suspend_clk_gate_en: 1;    //  4
    UINT32 reg_usb3_utmi_i_clk_gate_en: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_USB_SS_CRG_USB_SS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_000C    crg_usb_ss003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_ss_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_usb2_phy_i_n: 1;    //  1
    UINT32 reg_soft_rst_usb3_con_i_n: 1;    //  2
    UINT32 reg_soft_rst_usb3_core_n: 1;    //  3
    UINT32 reg_soft_rst_usb3_phy_i_n: 1;    //  4
    UINT32 reg_soft_rst_x_usb_ss_0_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_USB_SS_CRG_USB_SS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usb_ss Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USB_SS_CRG_USB_SS000_O26A0_T    crg_usb_ss000;    // 0xC611_0000
    SCRG_CTRL_USB_SS_CRG_USB_SS001_O26A0_T    crg_usb_ss001;    // 0xC611_0004
    SCRG_CTRL_USB_SS_CRG_USB_SS002_O26A0_T    crg_usb_ss002;    // 0xC611_0008
    SCRG_CTRL_USB_SS_CRG_USB_SS003_O26A0_T    crg_usb_ss003;    // 0xC611_000C
}SCRG_CTRL_USB_SS_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_USB_SS_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

