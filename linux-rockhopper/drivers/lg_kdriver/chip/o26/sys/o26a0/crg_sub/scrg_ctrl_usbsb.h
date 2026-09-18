#ifndef _SCRG_CTRL_USBSB_REG_O26A0_H_
#define _SCRG_CTRL_USBSB_REG_O26A0_H_

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
    0xC452_0000    crg_usbsb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_USBSB_CRG_USBSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0004    crg_usbsb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_USBSB_CRG_USBSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0008    crg_usbsb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_400_clk_gate_en   :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_USBSB_CRG_USBSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_000C    crg_usbsb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_400_n    :  1,    //      0
    reg_soft_rst_p_usbsb_0_axi_bnd_n: 1,    //  1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_USBSB_CRG_USBSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USBSB_CRG_USBSB000_O26A0_T    crg_usbsb000;       // 0xC452_0000
    SCRG_CTRL_USBSB_CRG_USBSB001_O26A0_T    crg_usbsb001;       // 0xC452_0004
    SCRG_CTRL_USBSB_CRG_USBSB002_O26A0_T    crg_usbsb002;       // 0xC452_0008
    SCRG_CTRL_USBSB_CRG_USBSB003_O26A0_T    crg_usbsb003;       // 0xC452_000C
}SCRG_CTRL_USBSB_REG_O26A0_T;
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

#define SCRG_CTRL_USBSB_CRG_USBSB000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_USBSB_CRG_USBSB001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_USBSB_CRG_USBSB002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_USBSB_CRG_USBSB003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC452_0000    crg_usbsb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_USBSB_CRG_USBSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0004    crg_usbsb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_USBSB_CRG_USBSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0008    crg_usbsb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_400_clk_gate_en: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_USBSB_CRG_USBSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_000C    crg_usbsb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_400_n: 1;    //    0
    UINT32 reg_soft_rst_p_usbsb_0_axi_bnd_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_USBSB_CRG_USBSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_usbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_USBSB_CRG_USBSB000_O26A0_T    crg_usbsb000;       // 0xC452_0000
    SCRG_CTRL_USBSB_CRG_USBSB001_O26A0_T    crg_usbsb001;       // 0xC452_0004
    SCRG_CTRL_USBSB_CRG_USBSB002_O26A0_T    crg_usbsb002;       // 0xC452_0008
    SCRG_CTRL_USBSB_CRG_USBSB003_O26A0_T    crg_usbsb003;       // 0xC452_000C
}SCRG_CTRL_USBSB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_USBSB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

