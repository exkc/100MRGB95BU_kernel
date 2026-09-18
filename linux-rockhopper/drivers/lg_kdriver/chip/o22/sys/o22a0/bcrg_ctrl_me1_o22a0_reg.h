#ifndef _BCRG_CTRL_ME1_REG_H_
#define _BCRG_CTRL_ME1_REG_H_

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
    0x44_0000    crg_bnd_me100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0004    crg_bnd_me101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0008    crg_bnd_me102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_gsc_clk_gate_en: 1,    //      0
    reg_apb_ipw_me1_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME1_CRG_BND_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_000C    crg_bnd_me103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_cco_0_n: 1,    //    0
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_srnr_0_n: 1,    //   4
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //    5
    reg_soft_rst_fly_brdg_me0_1_n: 1,    //    6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_ME1_CRG_BND_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0010    crg_bnd_me104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_gsc_n:  1,    //      0
    reg_soft_rst_apb_ipw_me1_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME1_CRG_BND_ME104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME100_O22A0_T    crg_bnd_me100;         // 0x44_0000
    BCRG_CTRL_ME1_CRG_BND_ME101_O22A0_T    crg_bnd_me101;         // 0x44_0004
    BCRG_CTRL_ME1_CRG_BND_ME102_O22A0_T    crg_bnd_me102;         // 0x44_0008
    BCRG_CTRL_ME1_CRG_BND_ME103_O22A0_T    crg_bnd_me103;         // 0x44_000C
    BCRG_CTRL_ME1_CRG_BND_ME104_O22A0_T    crg_bnd_me104;         // 0x44_0010
}BCRG_CTRL_ME1_REG_O22A0_T;
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

#define BCRG_CTRL_ME1_CRG_BND_ME100_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME1_CRG_BND_ME101_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME1_CRG_BND_ME102_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME1_CRG_BND_ME103_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME1_CRG_BND_ME104_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x44_0000    crg_bnd_me100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0004    crg_bnd_me101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0008    crg_bnd_me102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_gsc_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_me1_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_000C    crg_bnd_me103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_cco_0_n: 1;    //  0
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_srnr_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_me0_1_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x44_0010    crg_bnd_me104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_gsc_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_me1_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME100_O22A0_T    crg_bnd_me100;         // 0x44_0000
    BCRG_CTRL_ME1_CRG_BND_ME101_O22A0_T    crg_bnd_me101;         // 0x44_0004
    BCRG_CTRL_ME1_CRG_BND_ME102_O22A0_T    crg_bnd_me102;         // 0x44_0008
    BCRG_CTRL_ME1_CRG_BND_ME103_O22A0_T    crg_bnd_me103;         // 0x44_000C
    BCRG_CTRL_ME1_CRG_BND_ME104_O22A0_T    crg_bnd_me104;         // 0x44_0010
}BCRG_CTRL_ME1_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

