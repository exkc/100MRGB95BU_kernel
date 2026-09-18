#ifndef _BCRG_CTRL_VD0_M23A0_REG_H_
#define _BCRG_CTRL_VD0_M23A0_REG_H_

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
    0xCE69_1000    crg_bnd_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_1004    crg_bnd_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_1008    crg_bnd_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd0_clk_gate_en: 1,    //      0
    reg_vvc_clk_gate_en       :  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_VD0_CRG_BND_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_100C    crg_bnd_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD000_M23A0_T    crg_bnd_vd000;       // 0xCE69_1000
    BCRG_CTRL_VD0_CRG_BND_VD001_M23A0_T    crg_bnd_vd001;       // 0xCE69_1004
    BCRG_CTRL_VD0_CRG_BND_VD002_M23A0_T    crg_bnd_vd002;       // 0xCE69_1008
    BCRG_CTRL_VD0_CRG_BND_VD003_M23A0_T    crg_bnd_vd003;       // 0xCE69_100C
}BCRG_CTRL_VD0_REG_M23A0_T;
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

#define BCRG_CTRL_VD0_CRG_BND_VD000_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD0_CRG_BND_VD001_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD0_CRG_BND_VD002_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD0_CRG_BND_VD003_M23A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE69_1000    crg_bnd_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_1004    crg_bnd_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_1008    crg_bnd_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd0_clk_gate_en: 1;    //  0
    UINT32 reg_vvc_clk_gate_en:  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE69_100C    crg_bnd_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD000_M23A0_T    crg_bnd_vd000;       // 0xCE69_1000
    BCRG_CTRL_VD0_CRG_BND_VD001_M23A0_T    crg_bnd_vd001;       // 0xCE69_1004
    BCRG_CTRL_VD0_CRG_BND_VD002_M23A0_T    crg_bnd_vd002;       // 0xCE69_1008
    BCRG_CTRL_VD0_CRG_BND_VD003_M23A0_T    crg_bnd_vd003;       // 0xCE69_100C
}BCRG_CTRL_VD0_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

