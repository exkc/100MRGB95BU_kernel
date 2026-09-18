#ifndef _SCRG_CTRL_EMUSB_REG_O26A0_H_
#define _SCRG_CTRL_EMUSB_REG_O26A0_H_

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
    0xC618_0000    crg_emusb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EMUSB_CRG_EMUSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_0004    crg_emusb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EMUSB_CRG_EMUSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_0008    crg_emusb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_400_clk_gate_en   :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EMUSB_CRG_EMUSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_000C    crg_emusb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_400_n    :  1,    //      0
    reg_soft_rst_p_emusb_0_axi_bnd_n: 1,    //  1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_EMUSB_CRG_EMUSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_emusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMUSB_CRG_EMUSB000_O26A0_T    crg_emusb000;       // 0xC618_0000
    SCRG_CTRL_EMUSB_CRG_EMUSB001_O26A0_T    crg_emusb001;       // 0xC618_0004
    SCRG_CTRL_EMUSB_CRG_EMUSB002_O26A0_T    crg_emusb002;       // 0xC618_0008
    SCRG_CTRL_EMUSB_CRG_EMUSB003_O26A0_T    crg_emusb003;       // 0xC618_000C
}SCRG_CTRL_EMUSB_REG_O26A0_T;
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

#define SCRG_CTRL_EMUSB_CRG_EMUSB000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_EMUSB_CRG_EMUSB001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_EMUSB_CRG_EMUSB002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_EMUSB_CRG_EMUSB003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC618_0000    crg_emusb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EMUSB_CRG_EMUSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_0004    crg_emusb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EMUSB_CRG_EMUSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_0008    crg_emusb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_400_clk_gate_en: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EMUSB_CRG_EMUSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC618_000C    crg_emusb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_400_n: 1;    //    0
    UINT32 reg_soft_rst_p_emusb_0_axi_bnd_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_EMUSB_CRG_EMUSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_emusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMUSB_CRG_EMUSB000_O26A0_T    crg_emusb000;       // 0xC618_0000
    SCRG_CTRL_EMUSB_CRG_EMUSB001_O26A0_T    crg_emusb001;       // 0xC618_0004
    SCRG_CTRL_EMUSB_CRG_EMUSB002_O26A0_T    crg_emusb002;       // 0xC618_0008
    SCRG_CTRL_EMUSB_CRG_EMUSB003_O26A0_T    crg_emusb003;       // 0xC618_000C
}SCRG_CTRL_EMUSB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_EMUSB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

