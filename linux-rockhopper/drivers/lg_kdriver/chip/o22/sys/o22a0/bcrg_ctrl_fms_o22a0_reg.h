#ifndef _BCRG_CTRL_FMS_REG_H_
#define _BCRG_CTRL_FMS_REG_H_

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
    0x1D_0000    crg_bnd_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0004    crg_bnd_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0008    crg_bnd_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fms_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_000C    crg_bnd_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_ethernet_0_n: 1,    //  1
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_srnr_0_n: 1,    //   3
    reg_soft_rst_fly_brdg_me0_0_n: 1,    //    4
    reg_soft_rst_fly_brdg_me0_1_n: 1,    //    5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0010    crg_bnd_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fms_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS00_O22A0_T    crg_bnd_fms00;         // 0x1D_0000
    BCRG_CTRL_FMS_CRG_BND_FMS01_O22A0_T    crg_bnd_fms01;         // 0x1D_0004
    BCRG_CTRL_FMS_CRG_BND_FMS02_O22A0_T    crg_bnd_fms02;         // 0x1D_0008
    BCRG_CTRL_FMS_CRG_BND_FMS03_O22A0_T    crg_bnd_fms03;         // 0x1D_000C
    BCRG_CTRL_FMS_CRG_BND_FMS04_O22A0_T    crg_bnd_fms04;         // 0x1D_0010
}BCRG_CTRL_FMS_REG_O22A0_T;
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

#define BCRG_CTRL_FMS_CRG_BND_FMS00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMS_CRG_BND_FMS01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMS_CRG_BND_FMS02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMS_CRG_BND_FMS03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMS_CRG_BND_FMS04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x1D_0000    crg_bnd_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0004    crg_bnd_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0008    crg_bnd_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fms_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_000C    crg_bnd_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_ethernet_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_srnr_0_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_me0_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_me0_1_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1D_0010    crg_bnd_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fms_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS00_O22A0_T    crg_bnd_fms00;         // 0x1D_0000
    BCRG_CTRL_FMS_CRG_BND_FMS01_O22A0_T    crg_bnd_fms01;         // 0x1D_0004
    BCRG_CTRL_FMS_CRG_BND_FMS02_O22A0_T    crg_bnd_fms02;         // 0x1D_0008
    BCRG_CTRL_FMS_CRG_BND_FMS03_O22A0_T    crg_bnd_fms03;         // 0x1D_000C
    BCRG_CTRL_FMS_CRG_BND_FMS04_O22A0_T    crg_bnd_fms04;         // 0x1D_0010
}BCRG_CTRL_FMS_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

