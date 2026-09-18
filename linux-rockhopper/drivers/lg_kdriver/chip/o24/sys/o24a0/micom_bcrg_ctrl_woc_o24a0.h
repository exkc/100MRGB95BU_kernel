#ifndef _MICOM_BCRG_CTRL_WOC_REG_O24A0_H_
#define _MICOM_BCRG_CTRL_WOC_REG_O24A0_H_

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
    0xC63F_1000    crg_bnd_woc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_1004    crg_bnd_woc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_1008    crg_bnd_woc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_micom_clk_gate_en: 1,    //    0
    reg_micom_cm0p_clk_gate_en:  1,    //      1
                              : 30;    //   31:2 reserved
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_100C    crg_bnd_woc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_micom_n: 1,    //     0
                              : 31;    //   31:1 reserved
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC0_O24A0_T    crg_bnd_woc0;    // 0xC63F_1000
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC1_O24A0_T    crg_bnd_woc1;    // 0xC63F_1004
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC2_O24A0_T    crg_bnd_woc2;    // 0xC63F_1008
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC3_O24A0_T    crg_bnd_woc3;    // 0xC63F_100C
}MICOM_BCRG_CTRL_WOC_REG_O24A0_T;
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

#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC0_O24A0_T_OFF        (BASEADDRESS+0x0000)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC1_O24A0_T_OFF        (BASEADDRESS+0x0004)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC2_O24A0_T_OFF        (BASEADDRESS+0x0008)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC3_O24A0_T_OFF        (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC63F_1000    crg_bnd_woc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_1004    crg_bnd_woc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_1008    crg_bnd_woc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_micom_clk_gate_en: 1;    //  0
    UINT32 reg_micom_cm0p_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_100C    crg_bnd_woc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_micom_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC0_O24A0_T    crg_bnd_woc0;    // 0xC63F_1000
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC1_O24A0_T    crg_bnd_woc1;    // 0xC63F_1004
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC2_O24A0_T    crg_bnd_woc2;    // 0xC63F_1008
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC3_O24A0_T    crg_bnd_woc3;    // 0xC63F_100C
}MICOM_BCRG_CTRL_WOC_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MICOM_BCRG_CTRL_WOC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

