#ifndef _BCRG_CTRL_BMC_M23A0_REG_H_
#define _BCRG_CTRL_BMC_M23A0_REG_H_

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
    0xC615_1000    crg_bnd_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1004    crg_bnd_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1008    crg_bnd_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fsc_clk_gate_en       :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_100C    crg_bnd_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dbb_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1010    crg_bnd_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_fly_brdg_cco_1_n: 1,    //    0
    reg_soft_rst_fly_brdg_hdmiphy3_n: 1,    //  1
    reg_soft_rst_fly_brdg_hdmiphy4_n: 1,    //  2
    reg_soft_rst_fly_brdg_imx_4_n: 1,    //    3
    reg_soft_rst_sync_fsc_clk_n: 1,    //      4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1014    crg_bnd_bmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dbb_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC00_M23A0_T    crg_bnd_bmc00;       // 0xC615_1000
    BCRG_CTRL_BMC_CRG_BND_BMC01_M23A0_T    crg_bnd_bmc01;       // 0xC615_1004
    BCRG_CTRL_BMC_CRG_BND_BMC02_M23A0_T    crg_bnd_bmc02;       // 0xC615_1008
    BCRG_CTRL_BMC_CRG_BND_BMC03_M23A0_T    crg_bnd_bmc03;       // 0xC615_100C
    BCRG_CTRL_BMC_CRG_BND_BMC04_M23A0_T    crg_bnd_bmc04;       // 0xC615_1010
    BCRG_CTRL_BMC_CRG_BND_BMC05_M23A0_T    crg_bnd_bmc05;       // 0xC615_1014
}BCRG_CTRL_BMC_REG_M23A0_T;
/* 6 regs */

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

#define BCRG_CTRL_BMC_CRG_BND_BMC00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_BMC_CRG_BND_BMC01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_BMC_CRG_BND_BMC02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_BMC_CRG_BND_BMC03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_BMC_CRG_BND_BMC04_M23A0_T_OFF             (BASEADDRESS+0x0010)
#define BCRG_CTRL_BMC_CRG_BND_BMC05_M23A0_T_OFF             (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC615_1000    crg_bnd_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1004    crg_bnd_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1008    crg_bnd_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fsc_clk_gate_en:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_100C    crg_bnd_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dbb_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1010    crg_bnd_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_fly_brdg_cco_1_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_hdmiphy3_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_hdmiphy4_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_imx_4_n: 1;    //  3
    UINT32 reg_soft_rst_sync_fsc_clk_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_1014    crg_bnd_bmc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dbb_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC00_M23A0_T    crg_bnd_bmc00;       // 0xC615_1000
    BCRG_CTRL_BMC_CRG_BND_BMC01_M23A0_T    crg_bnd_bmc01;       // 0xC615_1004
    BCRG_CTRL_BMC_CRG_BND_BMC02_M23A0_T    crg_bnd_bmc02;       // 0xC615_1008
    BCRG_CTRL_BMC_CRG_BND_BMC03_M23A0_T    crg_bnd_bmc03;       // 0xC615_100C
    BCRG_CTRL_BMC_CRG_BND_BMC04_M23A0_T    crg_bnd_bmc04;       // 0xC615_1010
    BCRG_CTRL_BMC_CRG_BND_BMC05_M23A0_T    crg_bnd_bmc05;       // 0xC615_1014
}BCRG_CTRL_BMC_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

