#ifndef _BCRG_CTRL_VD2_REG_O24A0_H_
#define _BCRG_CTRL_VD2_REG_O24A0_H_

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
    0xCECC_1000    crg_bnd_vd20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD2_CRG_BND_VD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_1004    crg_bnd_vd21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD2_CRG_BND_VD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_1008    crg_bnd_vd22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd2_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD2_CRG_BND_VD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_100C    crg_bnd_vd23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd2_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD2_CRG_BND_VD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD2_CRG_BND_VD20_O24A0_T    crg_bnd_vd20;         // 0xCECC_1000
    BCRG_CTRL_VD2_CRG_BND_VD21_O24A0_T    crg_bnd_vd21;         // 0xCECC_1004
    BCRG_CTRL_VD2_CRG_BND_VD22_O24A0_T    crg_bnd_vd22;         // 0xCECC_1008
    BCRG_CTRL_VD2_CRG_BND_VD23_O24A0_T    crg_bnd_vd23;         // 0xCECC_100C
}BCRG_CTRL_VD2_REG_O24A0_T;
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

#define BCRG_CTRL_VD2_CRG_BND_VD20_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD2_CRG_BND_VD21_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD2_CRG_BND_VD22_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD2_CRG_BND_VD23_O24A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCECC_1000    crg_bnd_vd20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD2_CRG_BND_VD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_1004    crg_bnd_vd21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD2_CRG_BND_VD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_1008    crg_bnd_vd22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd2_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD2_CRG_BND_VD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECC_100C    crg_bnd_vd23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd2_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD2_CRG_BND_VD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD2_CRG_BND_VD20_O24A0_T    crg_bnd_vd20;         // 0xCECC_1000
    BCRG_CTRL_VD2_CRG_BND_VD21_O24A0_T    crg_bnd_vd21;         // 0xCECC_1004
    BCRG_CTRL_VD2_CRG_BND_VD22_O24A0_T    crg_bnd_vd22;         // 0xCECC_1008
    BCRG_CTRL_VD2_CRG_BND_VD23_O24A0_T    crg_bnd_vd23;         // 0xCECC_100C
}BCRG_CTRL_VD2_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_VD2_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

