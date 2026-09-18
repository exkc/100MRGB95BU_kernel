#ifndef _SCRG_CTRL_SS1_REG_H_
#define _SCRG_CTRL_SS1_REG_H_

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
    0x40_0000    crg_usb_ss_u1_me000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0004    crg_usb_ss_u1_me001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0008    crg_usb_ss_u1_me002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb3_core_u1_clk_gate_en: 1,    //     0
    reg_usb3_ctrl_xtal_clk_gate_en: 1,    //   1
    reg_usb3_pipe_i_u1_clk_gate_en: 1,    //   2
    reg_usb3_suspend_u1_clk_gate_en: 1,    //  3
    reg_usb3_utmi_i_u1_clk_gate_en: 1,    //   4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_000C    crg_usb_ss_u1_me003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_usb_ss_0_axi_bnd_u1_n: 1,    //  0
    reg_soft_rst_usb2_phy_u1_i:  1,    //      1
    reg_soft_rst_usb3_con_i_u1_n: 1,    //     2
    reg_soft_rst_usb3_phy_i_u1_n: 1,    //     3
    reg_soft_rst_usb_core_u1_n:  1,    //      4
    reg_soft_rst_x_usb_ss_0_axi_bnd_u1_n: 1,    //  5
    reg_soft_rst_x_usb_ss_0_axi_u1_n: 1,    //  6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0010    crg_usb_ss_u1_me004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb3_core_u1_clk_skip_ctrl: 9,    //  8:0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_ss_u1_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME000_O22A0_T    crg_usb_ss_u1_me000;    // 0x40_0000
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME001_O22A0_T    crg_usb_ss_u1_me001;    // 0x40_0004
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME002_O22A0_T    crg_usb_ss_u1_me002;    // 0x40_0008
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME003_O22A0_T    crg_usb_ss_u1_me003;    // 0x40_000C
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME004_O22A0_T    crg_usb_ss_u1_me004;    // 0x40_0010
}SCRG_CTRL_SS1_REG_O22A0_T;
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

#define SCRG_CTRL_SS1_CRG_USB_SS_U1_ME000_O22A0_T_OFF   (BASEADDRESS+0x0000)
#define SCRG_CTRL_SS1_CRG_USB_SS_U1_ME001_O22A0_T_OFF   (BASEADDRESS+0x0004)
#define SCRG_CTRL_SS1_CRG_USB_SS_U1_ME002_O22A0_T_OFF   (BASEADDRESS+0x0008)
#define SCRG_CTRL_SS1_CRG_USB_SS_U1_ME003_O22A0_T_OFF   (BASEADDRESS+0x000C)
#define SCRG_CTRL_SS1_CRG_USB_SS_U1_ME004_O22A0_T_OFF   (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x40_0000    crg_usb_ss_u1_me000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0004    crg_usb_ss_u1_me001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0008    crg_usb_ss_u1_me002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb3_core_u1_clk_gate_en: 1;    //  0
    UINT32 reg_usb3_ctrl_xtal_clk_gate_en: 1;    //  1
    UINT32 reg_usb3_pipe_i_u1_clk_gate_en: 1;    //  2
    UINT32 reg_usb3_suspend_u1_clk_gate_en: 1;    //  3
    UINT32 reg_usb3_utmi_i_u1_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_000C    crg_usb_ss_u1_me003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_usb_ss_0_axi_bnd_u1_n: 1;    //  0
    UINT32 reg_soft_rst_usb2_phy_u1_i: 1;    //  1
    UINT32 reg_soft_rst_usb3_con_i_u1_n: 1;    //  2
    UINT32 reg_soft_rst_usb3_phy_i_u1_n: 1;    //  3
    UINT32 reg_soft_rst_usb_core_u1_n: 1;    //  4
    UINT32 reg_soft_rst_x_usb_ss_0_axi_bnd_u1_n: 1;    //  5
    UINT32 reg_soft_rst_x_usb_ss_0_axi_u1_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x40_0010    crg_usb_ss_u1_me004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb3_core_u1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_SS1_CRG_USB_SS_U1_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_ss_u1_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME000_O22A0_T    crg_usb_ss_u1_me000;    // 0x40_0000
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME001_O22A0_T    crg_usb_ss_u1_me001;    // 0x40_0004
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME002_O22A0_T    crg_usb_ss_u1_me002;    // 0x40_0008
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME003_O22A0_T    crg_usb_ss_u1_me003;    // 0x40_000C
    SCRG_CTRL_SS1_CRG_USB_SS_U1_ME004_O22A0_T    crg_usb_ss_u1_me004;    // 0x40_0010
}SCRG_CTRL_SS1_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

