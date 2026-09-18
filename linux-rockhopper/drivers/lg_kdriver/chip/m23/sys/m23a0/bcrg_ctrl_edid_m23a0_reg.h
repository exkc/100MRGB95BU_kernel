#ifndef _BCRG_CTRL_EDID_M23A0_REG_H_
#define _BCRG_CTRL_EDID_M23A0_REG_H_

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
    0xC61B_1000    crg_bnd_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_1004    crg_bnd_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_1008    crg_bnd_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edid0_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_100C    crg_bnd_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edid0_n: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID00_M23A0_T    crg_bnd_edid00;    // 0xC61B_1000
    BCRG_CTRL_EDID_CRG_BND_EDID01_M23A0_T    crg_bnd_edid01;    // 0xC61B_1004
    BCRG_CTRL_EDID_CRG_BND_EDID02_M23A0_T    crg_bnd_edid02;    // 0xC61B_1008
    BCRG_CTRL_EDID_CRG_BND_EDID03_M23A0_T    crg_bnd_edid03;    // 0xC61B_100C
}BCRG_CTRL_EDID_REG_M23A0_T;
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

#define BCRG_CTRL_EDID_CRG_BND_EDID00_M23A0_T_OFF           (BASEADDRESS+0x0000)
#define BCRG_CTRL_EDID_CRG_BND_EDID01_M23A0_T_OFF           (BASEADDRESS+0x0004)
#define BCRG_CTRL_EDID_CRG_BND_EDID02_M23A0_T_OFF           (BASEADDRESS+0x0008)
#define BCRG_CTRL_EDID_CRG_BND_EDID03_M23A0_T_OFF           (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC61B_1000    crg_bnd_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_1004    crg_bnd_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_1008    crg_bnd_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edid0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_100C    crg_bnd_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edid0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID00_M23A0_T    crg_bnd_edid00;    // 0xC61B_1000
    BCRG_CTRL_EDID_CRG_BND_EDID01_M23A0_T    crg_bnd_edid01;    // 0xC61B_1004
    BCRG_CTRL_EDID_CRG_BND_EDID02_M23A0_T    crg_bnd_edid02;    // 0xC61B_1008
    BCRG_CTRL_EDID_CRG_BND_EDID03_M23A0_T    crg_bnd_edid03;    // 0xC61B_100C
}BCRG_CTRL_EDID_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

