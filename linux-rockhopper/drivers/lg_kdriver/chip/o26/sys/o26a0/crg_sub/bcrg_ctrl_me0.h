#ifndef _BCRG_CTRL_ME0_REG_O26A0_H_
#define _BCRG_CTRL_ME0_REG_O26A0_H_

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
    0xCCCC_1000    crg_bnd_me0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_1004    crg_bnd_me0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_1008    crg_bnd_me0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fmesb_clk_gate_en: 1,    //    0
    reg_apb_ipw_me0_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME0_CRG_BND_ME0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_100C    crg_bnd_me0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fmesb_n: 1,    //     0
    reg_soft_rst_apb_ipw_me0_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME0_CRG_BND_ME0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME0000_O26A0_T    crg_bnd_me0000;     // 0xCCCC_1000
    BCRG_CTRL_ME0_CRG_BND_ME0001_O26A0_T    crg_bnd_me0001;     // 0xCCCC_1004
    BCRG_CTRL_ME0_CRG_BND_ME0002_O26A0_T    crg_bnd_me0002;     // 0xCCCC_1008
    BCRG_CTRL_ME0_CRG_BND_ME0003_O26A0_T    crg_bnd_me0003;     // 0xCCCC_100C
}BCRG_CTRL_ME0_REG_O26A0_T;
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

#define BCRG_CTRL_ME0_CRG_BND_ME0000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME0_CRG_BND_ME0001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME0_CRG_BND_ME0002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME0_CRG_BND_ME0003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCCC_1000    crg_bnd_me0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_1004    crg_bnd_me0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_1008    crg_bnd_me0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fmesb_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_me0_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_100C    crg_bnd_me0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fmesb_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_me0_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME0000_O26A0_T    crg_bnd_me0000;     // 0xCCCC_1000
    BCRG_CTRL_ME0_CRG_BND_ME0001_O26A0_T    crg_bnd_me0001;     // 0xCCCC_1004
    BCRG_CTRL_ME0_CRG_BND_ME0002_O26A0_T    crg_bnd_me0002;     // 0xCCCC_1008
    BCRG_CTRL_ME0_CRG_BND_ME0003_O26A0_T    crg_bnd_me0003;     // 0xCCCC_100C
}BCRG_CTRL_ME0_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_ME0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

