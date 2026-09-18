#ifndef _BCRG_CTRL_GSC_REG_O24A0_H_
#define _BCRG_CTRL_GSC_REG_O24A0_H_

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
    0xCC48_1000    crg_bnd_gsc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_GSC_CRG_BND_GSC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1004    crg_bnd_gsc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_GSC_CRG_BND_GSC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1008    crg_bnd_gsc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_gsc_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_fmgse_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_GSC_CRG_BND_GSC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_100C    crg_bnd_gsc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_gsc_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_fmgse_n: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_GSC_CRG_BND_GSC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_GSC_CRG_BND_GSC0_O24A0_T    crg_bnd_gsc0;         // 0xCC48_1000
    BCRG_CTRL_GSC_CRG_BND_GSC1_O24A0_T    crg_bnd_gsc1;         // 0xCC48_1004
    BCRG_CTRL_GSC_CRG_BND_GSC2_O24A0_T    crg_bnd_gsc2;         // 0xCC48_1008
    BCRG_CTRL_GSC_CRG_BND_GSC3_O24A0_T    crg_bnd_gsc3;         // 0xCC48_100C
}BCRG_CTRL_GSC_REG_O24A0_T;
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

#define BCRG_CTRL_GSC_CRG_BND_GSC0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_GSC_CRG_BND_GSC1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_GSC_CRG_BND_GSC2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_GSC_CRG_BND_GSC3_O24A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC48_1000    crg_bnd_gsc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_GSC_CRG_BND_GSC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1004    crg_bnd_gsc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_GSC_CRG_BND_GSC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1008    crg_bnd_gsc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_gsc_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_fmgse_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_GSC_CRG_BND_GSC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_100C    crg_bnd_gsc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_gsc_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_fmgse_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_GSC_CRG_BND_GSC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_GSC_CRG_BND_GSC0_O24A0_T    crg_bnd_gsc0;         // 0xCC48_1000
    BCRG_CTRL_GSC_CRG_BND_GSC1_O24A0_T    crg_bnd_gsc1;         // 0xCC48_1004
    BCRG_CTRL_GSC_CRG_BND_GSC2_O24A0_T    crg_bnd_gsc2;         // 0xCC48_1008
    BCRG_CTRL_GSC_CRG_BND_GSC3_O24A0_T    crg_bnd_gsc3;         // 0xCC48_100C
}BCRG_CTRL_GSC_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_GSC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

