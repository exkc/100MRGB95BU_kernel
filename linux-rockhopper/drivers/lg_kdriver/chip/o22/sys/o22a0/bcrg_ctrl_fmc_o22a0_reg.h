#ifndef _BCRG_CTRL_FMC_REG_H_
#define _BCRG_CTRL_FMC_REG_H_

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
    0x1A_0000    crg_bnd_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0004    crg_bnd_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0008    crg_bnd_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fmc_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_000C    crg_bnd_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    0
    reg_soft_rst_fly_brdg_imx_16_n: 1,    //   1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0010    crg_bnd_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fmc_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC00_O22A0_T    crg_bnd_fmc00;         // 0x1A_0000
    BCRG_CTRL_FMC_CRG_BND_FMC01_O22A0_T    crg_bnd_fmc01;         // 0x1A_0004
    BCRG_CTRL_FMC_CRG_BND_FMC02_O22A0_T    crg_bnd_fmc02;         // 0x1A_0008
    BCRG_CTRL_FMC_CRG_BND_FMC03_O22A0_T    crg_bnd_fmc03;         // 0x1A_000C
    BCRG_CTRL_FMC_CRG_BND_FMC04_O22A0_T    crg_bnd_fmc04;         // 0x1A_0010
}BCRG_CTRL_FMC_REG_O22A0_T;
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

#define BCRG_CTRL_FMC_CRG_BND_FMC00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMC_CRG_BND_FMC01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMC_CRG_BND_FMC02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMC_CRG_BND_FMC03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMC_CRG_BND_FMC04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x1A_0000    crg_bnd_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0004    crg_bnd_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0008    crg_bnd_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fmc_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_000C    crg_bnd_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_imx_16_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1A_0010    crg_bnd_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fmc_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC00_O22A0_T    crg_bnd_fmc00;         // 0x1A_0000
    BCRG_CTRL_FMC_CRG_BND_FMC01_O22A0_T    crg_bnd_fmc01;         // 0x1A_0004
    BCRG_CTRL_FMC_CRG_BND_FMC02_O22A0_T    crg_bnd_fmc02;         // 0x1A_0008
    BCRG_CTRL_FMC_CRG_BND_FMC03_O22A0_T    crg_bnd_fmc03;         // 0x1A_000C
    BCRG_CTRL_FMC_CRG_BND_FMC04_O22A0_T    crg_bnd_fmc04;         // 0x1A_0010
}BCRG_CTRL_FMC_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

