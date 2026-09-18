#ifndef _SCRG_CTRL_EPUSB_REG_O24A0_H_
#define _SCRG_CTRL_EPUSB_REG_O24A0_H_

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
    0xC60A_0000    crg_sb_epu0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EPUSB_CRG_SB_EPU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_0004    crg_sb_epu1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EPUSB_CRG_SB_EPU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_0008    crg_sb_epu2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_400_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EPUSB_CRG_SB_EPU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_000C    crg_sb_epu3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_ch_mux_epusb_0_axi_n: 1,    //  0
    reg_soft_rst_p_usb_ss4_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_usb_ss4_0_ch_mux_axi_n: 1,    //  2
    reg_soft_rst_x_ch_mux_epusb_0_axi_n: 1,    //  3
    reg_soft_rst_x_usb_ss4_0_axi_n: 1,    //   4
    reg_soft_rst_x_usb_ss4_0_ch_mux_axi_n: 1,    //  5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_EPUSB_CRG_SB_EPU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_epusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EPUSB_CRG_SB_EPU0_O24A0_T    crg_sb_epu0;         // 0xC60A_0000
    SCRG_CTRL_EPUSB_CRG_SB_EPU1_O24A0_T    crg_sb_epu1;         // 0xC60A_0004
    SCRG_CTRL_EPUSB_CRG_SB_EPU2_O24A0_T    crg_sb_epu2;         // 0xC60A_0008
    SCRG_CTRL_EPUSB_CRG_SB_EPU3_O24A0_T    crg_sb_epu3;         // 0xC60A_000C
}SCRG_CTRL_EPUSB_REG_O24A0_T;
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

#define SCRG_CTRL_EPUSB_CRG_SB_EPU0_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_EPUSB_CRG_SB_EPU1_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_EPUSB_CRG_SB_EPU2_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_EPUSB_CRG_SB_EPU3_O24A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC60A_0000    crg_sb_epu0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EPUSB_CRG_SB_EPU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_0004    crg_sb_epu1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EPUSB_CRG_SB_EPU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_0008    crg_sb_epu2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_400_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EPUSB_CRG_SB_EPU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC60A_000C    crg_sb_epu3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_ch_mux_epusb_0_axi_n: 1;    //  0
    UINT32 reg_soft_rst_p_usb_ss4_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_usb_ss4_0_ch_mux_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_ch_mux_epusb_0_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_usb_ss4_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_usb_ss4_0_ch_mux_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_EPUSB_CRG_SB_EPU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_epusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EPUSB_CRG_SB_EPU0_O24A0_T    crg_sb_epu0;         // 0xC60A_0000
    SCRG_CTRL_EPUSB_CRG_SB_EPU1_O24A0_T    crg_sb_epu1;         // 0xC60A_0004
    SCRG_CTRL_EPUSB_CRG_SB_EPU2_O24A0_T    crg_sb_epu2;         // 0xC60A_0008
    SCRG_CTRL_EPUSB_CRG_SB_EPU3_O24A0_T    crg_sb_epu3;         // 0xC60A_000C
}SCRG_CTRL_EPUSB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_EPUSB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

