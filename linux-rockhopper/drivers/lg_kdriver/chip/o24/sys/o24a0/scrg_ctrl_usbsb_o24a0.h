#ifndef _SCRG_CTRL_USBSB_REG_O24A0_H_
#define _SCRG_CTRL_USBSB_REG_O24A0_H_

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
    0xC8E1_0000    crg_sb_usb0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USBSB_CRG_SB_USB0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_0004    crg_sb_usb1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USBSB_CRG_SB_USB1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_0008    crg_sb_usb2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_400_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_USBSB_CRG_SB_USB2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_000C    crg_sb_usb3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_400_n: 1,    //     0
    reg_soft_rst_p_usb_0_axi_bnd_n: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_USBSB_CRG_SB_USB3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USBSB_CRG_SB_USB0_O24A0_T    crg_sb_usb0;         // 0xC8E1_0000
    SCRG_CTRL_USBSB_CRG_SB_USB1_O24A0_T    crg_sb_usb1;         // 0xC8E1_0004
    SCRG_CTRL_USBSB_CRG_SB_USB2_O24A0_T    crg_sb_usb2;         // 0xC8E1_0008
    SCRG_CTRL_USBSB_CRG_SB_USB3_O24A0_T    crg_sb_usb3;         // 0xC8E1_000C
}SCRG_CTRL_USBSB_REG_O24A0_T;
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

#define SCRG_CTRL_USBSB_CRG_SB_USB0_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_USBSB_CRG_SB_USB1_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_USBSB_CRG_SB_USB2_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_USBSB_CRG_SB_USB3_O24A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC8E1_0000    crg_sb_usb0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USBSB_CRG_SB_USB0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_0004    crg_sb_usb1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USBSB_CRG_SB_USB1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_0008    crg_sb_usb2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_400_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_USBSB_CRG_SB_USB2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8E1_000C    crg_sb_usb3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_400_n: 1;    //  0
    UINT32 reg_soft_rst_p_usb_0_axi_bnd_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_USBSB_CRG_SB_USB3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USBSB_CRG_SB_USB0_O24A0_T    crg_sb_usb0;         // 0xC8E1_0000
    SCRG_CTRL_USBSB_CRG_SB_USB1_O24A0_T    crg_sb_usb1;         // 0xC8E1_0004
    SCRG_CTRL_USBSB_CRG_SB_USB2_O24A0_T    crg_sb_usb2;         // 0xC8E1_0008
    SCRG_CTRL_USBSB_CRG_SB_USB3_O24A0_T    crg_sb_usb3;         // 0xC8E1_000C
}SCRG_CTRL_USBSB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_USBSB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

