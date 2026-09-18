#ifndef _BCRG_CTRL_ME1_REG_O26A0_H_
#define _BCRG_CTRL_ME1_REG_O26A0_H_

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
    0xCCCF_1000    crg_bnd_me1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1004    crg_bnd_me1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1008    crg_bnd_me1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_me1_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ME1_CRG_BND_ME1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_100C    crg_bnd_me1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_emmc_0_n: 1,    //   0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ME1_CRG_BND_ME1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1010    crg_bnd_me1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_me1_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ME1_CRG_BND_ME1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME1000_O26A0_T    crg_bnd_me1000;     // 0xCCCF_1000
    BCRG_CTRL_ME1_CRG_BND_ME1001_O26A0_T    crg_bnd_me1001;     // 0xCCCF_1004
    BCRG_CTRL_ME1_CRG_BND_ME1002_O26A0_T    crg_bnd_me1002;     // 0xCCCF_1008
    BCRG_CTRL_ME1_CRG_BND_ME1003_O26A0_T    crg_bnd_me1003;     // 0xCCCF_100C
    BCRG_CTRL_ME1_CRG_BND_ME1004_O26A0_T    crg_bnd_me1004;     // 0xCCCF_1010
}BCRG_CTRL_ME1_REG_O26A0_T;
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

#define BCRG_CTRL_ME1_CRG_BND_ME1000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME1_CRG_BND_ME1001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME1_CRG_BND_ME1002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME1_CRG_BND_ME1003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME1_CRG_BND_ME1004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCCF_1000    crg_bnd_me1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1004    crg_bnd_me1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1008    crg_bnd_me1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_me1_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_100C    crg_bnd_me1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_emmc_0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_1010    crg_bnd_me1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_me1_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME1000_O26A0_T    crg_bnd_me1000;     // 0xCCCF_1000
    BCRG_CTRL_ME1_CRG_BND_ME1001_O26A0_T    crg_bnd_me1001;     // 0xCCCF_1004
    BCRG_CTRL_ME1_CRG_BND_ME1002_O26A0_T    crg_bnd_me1002;     // 0xCCCF_1008
    BCRG_CTRL_ME1_CRG_BND_ME1003_O26A0_T    crg_bnd_me1003;     // 0xCCCF_100C
    BCRG_CTRL_ME1_CRG_BND_ME1004_O26A0_T    crg_bnd_me1004;     // 0xCCCF_1010
}BCRG_CTRL_ME1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_ME1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

