#ifndef _BCRG_CTRL_VD1_M23A0_REG_H_
#define _BCRG_CTRL_VD1_M23A0_REG_H_

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
    0xCE52_1000    crg_bnd_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1004    crg_bnd_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1008    crg_bnd_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd1_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD1_CRG_BND_VD102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_100C    crg_bnd_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd1_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD1_CRG_BND_VD103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD100_M23A0_T    crg_bnd_vd100;       // 0xCE52_1000
    BCRG_CTRL_VD1_CRG_BND_VD101_M23A0_T    crg_bnd_vd101;       // 0xCE52_1004
    BCRG_CTRL_VD1_CRG_BND_VD102_M23A0_T    crg_bnd_vd102;       // 0xCE52_1008
    BCRG_CTRL_VD1_CRG_BND_VD103_M23A0_T    crg_bnd_vd103;       // 0xCE52_100C
}BCRG_CTRL_VD1_REG_M23A0_T;
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

#define BCRG_CTRL_VD1_CRG_BND_VD100_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD1_CRG_BND_VD101_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD1_CRG_BND_VD102_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD1_CRG_BND_VD103_M23A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE52_1000    crg_bnd_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1004    crg_bnd_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1008    crg_bnd_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd1_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_100C    crg_bnd_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd1_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD100_M23A0_T    crg_bnd_vd100;       // 0xCE52_1000
    BCRG_CTRL_VD1_CRG_BND_VD101_M23A0_T    crg_bnd_vd101;       // 0xCE52_1004
    BCRG_CTRL_VD1_CRG_BND_VD102_M23A0_T    crg_bnd_vd102;       // 0xCE52_1008
    BCRG_CTRL_VD1_CRG_BND_VD103_M23A0_T    crg_bnd_vd103;       // 0xCE52_100C
}BCRG_CTRL_VD1_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

