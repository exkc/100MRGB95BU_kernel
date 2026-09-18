#ifndef _SCRG_CTRL_HS0_REG_H_
#define _SCRG_CTRL_HS0_REG_H_

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
    0x42_0000    crg_usb_hs_me000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HS0_CRG_USB_HS_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0004    crg_usb_hs_me001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HS0_CRG_USB_HS_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0008    crg_usb_hs_me002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb12_i_clk_gate_en   :  1,    //      0
    reg_usb48_i_clk_gate_en   :  1,    //      1
    reg_usb_core_clk_gate_en  :  1,    //      2
    reg_usb_utmi60_i_clk_gate_en: 1,    //     3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_HS0_CRG_USB_HS_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_000C    crg_usb_hs_me003 ''
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
}SCRG_CTRL_HS0_CRG_USB_HS_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0010    crg_usb_hs_me004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_core_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HS0_CRG_USB_HS_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_hs_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HS0_CRG_USB_HS_ME000_O22A0_T    crg_usb_hs_me000;    // 0x42_0000
    SCRG_CTRL_HS0_CRG_USB_HS_ME001_O22A0_T    crg_usb_hs_me001;    // 0x42_0004
    SCRG_CTRL_HS0_CRG_USB_HS_ME002_O22A0_T    crg_usb_hs_me002;    // 0x42_0008
    SCRG_CTRL_HS0_CRG_USB_HS_ME003_O22A0_T    crg_usb_hs_me003;    // 0x42_000C
    SCRG_CTRL_HS0_CRG_USB_HS_ME004_O22A0_T    crg_usb_hs_me004;    // 0x42_0010
}SCRG_CTRL_HS0_REG_O22A0_T;
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

#define SCRG_CTRL_HS0_CRG_USB_HS_ME000_O22A0_T_OFF         (BASEADDRESS+0x0000)
#define SCRG_CTRL_HS0_CRG_USB_HS_ME001_O22A0_T_OFF         (BASEADDRESS+0x0004)
#define SCRG_CTRL_HS0_CRG_USB_HS_ME002_O22A0_T_OFF         (BASEADDRESS+0x0008)
#define SCRG_CTRL_HS0_CRG_USB_HS_ME003_O22A0_T_OFF         (BASEADDRESS+0x000C)
#define SCRG_CTRL_HS0_CRG_USB_HS_ME004_O22A0_T_OFF         (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x42_0000    crg_usb_hs_me000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HS0_CRG_USB_HS_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0004    crg_usb_hs_me001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HS0_CRG_USB_HS_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0008    crg_usb_hs_me002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb12_i_clk_gate_en: 1;    //   0
    UINT32 reg_usb48_i_clk_gate_en: 1;    //   1
    UINT32 reg_usb_core_clk_gate_en: 1;    //  2
    UINT32 reg_usb_utmi60_i_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_HS0_CRG_USB_HS_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_000C    crg_usb_hs_me003 ''
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
}SCRG_CTRL_HS0_CRG_USB_HS_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x42_0010    crg_usb_hs_me004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb_core_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HS0_CRG_USB_HS_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_usb_hs_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HS0_CRG_USB_HS_ME000_O22A0_T    crg_usb_hs_me000;    // 0x42_0000
    SCRG_CTRL_HS0_CRG_USB_HS_ME001_O22A0_T    crg_usb_hs_me001;    // 0x42_0004
    SCRG_CTRL_HS0_CRG_USB_HS_ME002_O22A0_T    crg_usb_hs_me002;    // 0x42_0008
    SCRG_CTRL_HS0_CRG_USB_HS_ME003_O22A0_T    crg_usb_hs_me003;    // 0x42_000C
    SCRG_CTRL_HS0_CRG_USB_HS_ME004_O22A0_T    crg_usb_hs_me004;    // 0x42_0010
}SCRG_CTRL_HS0_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

