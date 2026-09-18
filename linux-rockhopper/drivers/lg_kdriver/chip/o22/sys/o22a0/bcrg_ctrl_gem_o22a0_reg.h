#ifndef _BCRG_CTRL_GEM_REG_H_
#define _BCRG_CTRL_GEM_REG_H_

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
    0x20_0000    crg_bnd_gem00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_GEM_CRG_BND_GEM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_0004    crg_bnd_gem01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_GEM_CRG_BND_GEM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_0008    crg_bnd_gem02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_ephy_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_GEM_CRG_BND_GEM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_000C    crg_bnd_gem03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_ephy_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_GEM_CRG_BND_GEM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_gem Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_GEM_CRG_BND_GEM00_O22A0_T    crg_bnd_gem00;         // 0x20_0000
    BCRG_CTRL_GEM_CRG_BND_GEM01_O22A0_T    crg_bnd_gem01;         // 0x20_0004
    BCRG_CTRL_GEM_CRG_BND_GEM02_O22A0_T    crg_bnd_gem02;         // 0x20_0008
    BCRG_CTRL_GEM_CRG_BND_GEM03_O22A0_T    crg_bnd_gem03;         // 0x20_000C
}BCRG_CTRL_GEM_REG_O22A0_T;
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

#define BCRG_CTRL_GEM_CRG_BND_GEM00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_GEM_CRG_BND_GEM01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_GEM_CRG_BND_GEM02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_GEM_CRG_BND_GEM03_O22A0_T_OFF               (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0x20_0000    crg_bnd_gem00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_GEM_CRG_BND_GEM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_0004    crg_bnd_gem01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_GEM_CRG_BND_GEM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_0008    crg_bnd_gem02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_ephy_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_GEM_CRG_BND_GEM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x20_000C    crg_bnd_gem03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_ephy_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_GEM_CRG_BND_GEM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_gem Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_GEM_CRG_BND_GEM00_O22A0_T    crg_bnd_gem00;         // 0x20_0000
    BCRG_CTRL_GEM_CRG_BND_GEM01_O22A0_T    crg_bnd_gem01;         // 0x20_0004
    BCRG_CTRL_GEM_CRG_BND_GEM02_O22A0_T    crg_bnd_gem02;         // 0x20_0008
    BCRG_CTRL_GEM_CRG_BND_GEM03_O22A0_T    crg_bnd_gem03;         // 0x20_000C
}BCRG_CTRL_GEM_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

