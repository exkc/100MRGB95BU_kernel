#ifndef _BCRG_CTRL_EDID_REG_H_
#define _BCRG_CTRL_EDID_REG_H_

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
    0x17_0000    crg_bnd_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_0004    crg_bnd_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_0008    crg_bnd_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edid_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_000C    crg_bnd_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edid_0: 1,    //      0
    reg_soft_rst_apb_ipw_edid_1: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID00_O22A0_T    crg_bnd_edid00;      // 0x17_0000
    BCRG_CTRL_EDID_CRG_BND_EDID01_O22A0_T    crg_bnd_edid01;      // 0x17_0004
    BCRG_CTRL_EDID_CRG_BND_EDID02_O22A0_T    crg_bnd_edid02;      // 0x17_0008
    BCRG_CTRL_EDID_CRG_BND_EDID03_O22A0_T    crg_bnd_edid03;      // 0x17_000C
}BCRG_CTRL_EDID_REG_O22A0_T;
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

#define BCRG_CTRL_EDID_CRG_BND_EDID00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_EDID_CRG_BND_EDID01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_EDID_CRG_BND_EDID02_O22A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_EDID_CRG_BND_EDID03_O22A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0x17_0000    crg_bnd_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_0004    crg_bnd_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_0008    crg_bnd_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edid_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x17_000C    crg_bnd_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edid_0: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_edid_1: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID00_O22A0_T    crg_bnd_edid00;      // 0x17_0000
    BCRG_CTRL_EDID_CRG_BND_EDID01_O22A0_T    crg_bnd_edid01;      // 0x17_0004
    BCRG_CTRL_EDID_CRG_BND_EDID02_O22A0_T    crg_bnd_edid02;      // 0x17_0008
    BCRG_CTRL_EDID_CRG_BND_EDID03_O22A0_T    crg_bnd_edid03;      // 0x17_000C
}BCRG_CTRL_EDID_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

