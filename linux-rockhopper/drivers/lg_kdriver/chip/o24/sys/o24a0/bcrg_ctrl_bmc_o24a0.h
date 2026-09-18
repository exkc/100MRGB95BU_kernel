#ifndef _BCRG_CTRL_BMC_REG_O24A0_H_
#define _BCRG_CTRL_BMC_REG_O24A0_H_

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
    0xC68A_1000    crg_bnd_bmc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_1004    crg_bnd_bmc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_1008    crg_bnd_bmc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dbb_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_100C    crg_bnd_bmc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dbb_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC0_O24A0_T    crg_bnd_bmc0;         // 0xC68A_1000
    BCRG_CTRL_BMC_CRG_BND_BMC1_O24A0_T    crg_bnd_bmc1;         // 0xC68A_1004
    BCRG_CTRL_BMC_CRG_BND_BMC2_O24A0_T    crg_bnd_bmc2;         // 0xC68A_1008
    BCRG_CTRL_BMC_CRG_BND_BMC3_O24A0_T    crg_bnd_bmc3;         // 0xC68A_100C
}BCRG_CTRL_BMC_REG_O24A0_T;
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

#define BCRG_CTRL_BMC_CRG_BND_BMC0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_BMC_CRG_BND_BMC1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_BMC_CRG_BND_BMC2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_BMC_CRG_BND_BMC3_O24A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC68A_1000    crg_bnd_bmc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_1004    crg_bnd_bmc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_1008    crg_bnd_bmc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dbb_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_100C    crg_bnd_bmc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dbb_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC0_O24A0_T    crg_bnd_bmc0;         // 0xC68A_1000
    BCRG_CTRL_BMC_CRG_BND_BMC1_O24A0_T    crg_bnd_bmc1;         // 0xC68A_1004
    BCRG_CTRL_BMC_CRG_BND_BMC2_O24A0_T    crg_bnd_bmc2;         // 0xC68A_1008
    BCRG_CTRL_BMC_CRG_BND_BMC3_O24A0_T    crg_bnd_bmc3;         // 0xC68A_100C
}BCRG_CTRL_BMC_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_BMC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

