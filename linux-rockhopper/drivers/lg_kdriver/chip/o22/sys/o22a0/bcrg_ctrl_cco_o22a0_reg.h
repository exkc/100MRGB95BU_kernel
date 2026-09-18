#ifndef _BCRG_CTRL_CCO_REG_H_
#define _BCRG_CTRL_CCO_REG_H_

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
    0x5_0000    crg_bnd_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CCO_CRG_BND_CCO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0004    crg_bnd_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CCO_CRG_BND_CCO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0008    crg_bnd_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cco_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_000C    crg_bnd_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_lbm_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_gpu_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_gsc_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_gsc_1_n: 1,    //    4
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_me1_0_n: 1,    //    6
    reg_soft_rst_axi_brdg_srnr_0_n: 1,    //   7
                              : 24;    //   31:8 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0010    crg_bnd_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cco_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CCO_CRG_BND_CCO00_O22A0_T    crg_bnd_cco00;         // 0x5_0000
    BCRG_CTRL_CCO_CRG_BND_CCO01_O22A0_T    crg_bnd_cco01;         // 0x5_0004
    BCRG_CTRL_CCO_CRG_BND_CCO02_O22A0_T    crg_bnd_cco02;         // 0x5_0008
    BCRG_CTRL_CCO_CRG_BND_CCO03_O22A0_T    crg_bnd_cco03;         // 0x5_000C
    BCRG_CTRL_CCO_CRG_BND_CCO04_O22A0_T    crg_bnd_cco04;         // 0x5_0010
}BCRG_CTRL_CCO_REG_O22A0_T;
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

#define BCRG_CTRL_CCO_CRG_BND_CCO00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_CCO_CRG_BND_CCO01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_CCO_CRG_BND_CCO02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_CCO_CRG_BND_CCO03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_CCO_CRG_BND_CCO04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x5_0000    crg_bnd_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CCO_CRG_BND_CCO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0004    crg_bnd_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CCO_CRG_BND_CCO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0008    crg_bnd_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cco_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_000C    crg_bnd_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_lbm_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_gpu_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_gsc_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_gsc_1_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_me1_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_srnr_0_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5_0010    crg_bnd_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cco_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CCO_CRG_BND_CCO00_O22A0_T    crg_bnd_cco00;         // 0x5_0000
    BCRG_CTRL_CCO_CRG_BND_CCO01_O22A0_T    crg_bnd_cco01;         // 0x5_0004
    BCRG_CTRL_CCO_CRG_BND_CCO02_O22A0_T    crg_bnd_cco02;         // 0x5_0008
    BCRG_CTRL_CCO_CRG_BND_CCO03_O22A0_T    crg_bnd_cco03;         // 0x5_000C
    BCRG_CTRL_CCO_CRG_BND_CCO04_O22A0_T    crg_bnd_cco04;         // 0x5_0010
}BCRG_CTRL_CCO_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

