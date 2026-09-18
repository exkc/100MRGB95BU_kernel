#ifndef _BCRG_CTRL_DPE_REG_O24A0_H_
#define _BCRG_CTRL_DPE_REG_O24A0_H_

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
    0xCC93_1000    crg_bnd_dpe0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_1004    crg_bnd_dpe1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_1008    crg_bnd_dpe2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_led_clk_gate_en: 1,    //      0
    reg_apb_ipw_tcon_clk_gate_en: 1,    //     1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_100C    crg_bnd_dpe3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_led_n:  1,    //      0
    reg_soft_rst_apb_ipw_tcon_n: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE0_O24A0_T    crg_bnd_dpe0;         // 0xCC93_1000
    BCRG_CTRL_DPE_CRG_BND_DPE1_O24A0_T    crg_bnd_dpe1;         // 0xCC93_1004
    BCRG_CTRL_DPE_CRG_BND_DPE2_O24A0_T    crg_bnd_dpe2;         // 0xCC93_1008
    BCRG_CTRL_DPE_CRG_BND_DPE3_O24A0_T    crg_bnd_dpe3;         // 0xCC93_100C
}BCRG_CTRL_DPE_REG_O24A0_T;
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

#define BCRG_CTRL_DPE_CRG_BND_DPE0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_DPE_CRG_BND_DPE1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_DPE_CRG_BND_DPE2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_DPE_CRG_BND_DPE3_O24A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC93_1000    crg_bnd_dpe0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_1004    crg_bnd_dpe1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_1008    crg_bnd_dpe2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_led_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_tcon_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_100C    crg_bnd_dpe3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_led_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_tcon_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE0_O24A0_T    crg_bnd_dpe0;         // 0xCC93_1000
    BCRG_CTRL_DPE_CRG_BND_DPE1_O24A0_T    crg_bnd_dpe1;         // 0xCC93_1004
    BCRG_CTRL_DPE_CRG_BND_DPE2_O24A0_T    crg_bnd_dpe2;         // 0xCC93_1008
    BCRG_CTRL_DPE_CRG_BND_DPE3_O24A0_T    crg_bnd_dpe3;         // 0xCC93_100C
}BCRG_CTRL_DPE_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_DPE_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

