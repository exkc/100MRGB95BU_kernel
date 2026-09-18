#ifndef _BCRG_CTRL_VD1_REG_H_
#define _BCRG_CTRL_VD1_REG_H_

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
    0x52_0000    crg_bnd_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_0004    crg_bnd_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_0008    crg_bnd_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd1_clk_gate_en: 1,    //      0
    reg_lcu_ipw_vd1_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_VD1_CRG_BND_VD102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_000C    crg_bnd_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd1_n0: 1,    //      0
    reg_soft_rst_apb_ipw_vd1_n1: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_VD1_CRG_BND_VD103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD100_O22A0_T    crg_bnd_vd100;         // 0x52_0000
    BCRG_CTRL_VD1_CRG_BND_VD101_O22A0_T    crg_bnd_vd101;         // 0x52_0004
    BCRG_CTRL_VD1_CRG_BND_VD102_O22A0_T    crg_bnd_vd102;         // 0x52_0008
    BCRG_CTRL_VD1_CRG_BND_VD103_O22A0_T    crg_bnd_vd103;         // 0x52_000C
}BCRG_CTRL_VD1_REG_O22A0_T;
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

#define BCRG_CTRL_VD1_CRG_BND_VD100_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD1_CRG_BND_VD101_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD1_CRG_BND_VD102_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD1_CRG_BND_VD103_O22A0_T_OFF               (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0x52_0000    crg_bnd_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_0004    crg_bnd_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_0008    crg_bnd_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd1_clk_gate_en: 1;    //  0
    UINT32 reg_lcu_ipw_vd1_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x52_000C    crg_bnd_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd1_n0: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_vd1_n1: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD100_O22A0_T    crg_bnd_vd100;         // 0x52_0000
    BCRG_CTRL_VD1_CRG_BND_VD101_O22A0_T    crg_bnd_vd101;         // 0x52_0004
    BCRG_CTRL_VD1_CRG_BND_VD102_O22A0_T    crg_bnd_vd102;         // 0x52_0008
    BCRG_CTRL_VD1_CRG_BND_VD103_O22A0_T    crg_bnd_vd103;         // 0x52_000C
}BCRG_CTRL_VD1_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

