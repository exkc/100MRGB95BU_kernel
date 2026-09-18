#ifndef _BCRG_CTRL_FMC_M23A0_REG_H_
#define _BCRG_CTRL_FMC_M23A0_REG_H_

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
    0xCC92_1000    crg_bnd_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1004    crg_bnd_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1008    crg_bnd_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ts_clk_gate_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_100C    crg_bnd_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fmc_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1010    crg_bnd_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_2_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    1
    reg_soft_rst_axi_brdg_ephy_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_micom_1_n: 1,    //  3
    reg_soft_rst_axi_brdg_pdm_0_n: 1,    //    4
    reg_soft_rst_sync_ts_clk_n:  1,    //      5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1014    crg_bnd_fmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fmc_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC00_M23A0_T    crg_bnd_fmc00;       // 0xCC92_1000
    BCRG_CTRL_FMC_CRG_BND_FMC01_M23A0_T    crg_bnd_fmc01;       // 0xCC92_1004
    BCRG_CTRL_FMC_CRG_BND_FMC02_M23A0_T    crg_bnd_fmc02;       // 0xCC92_1008
    BCRG_CTRL_FMC_CRG_BND_FMC03_M23A0_T    crg_bnd_fmc03;       // 0xCC92_100C
    BCRG_CTRL_FMC_CRG_BND_FMC04_M23A0_T    crg_bnd_fmc04;       // 0xCC92_1010
    BCRG_CTRL_FMC_CRG_BND_FMC05_M23A0_T    crg_bnd_fmc05;       // 0xCC92_1014
}BCRG_CTRL_FMC_REG_M23A0_T;
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

#define BCRG_CTRL_FMC_CRG_BND_FMC00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMC_CRG_BND_FMC01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMC_CRG_BND_FMC02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMC_CRG_BND_FMC03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMC_CRG_BND_FMC04_M23A0_T_OFF             (BASEADDRESS+0x0010)
#define BCRG_CTRL_FMC_CRG_BND_FMC05_M23A0_T_OFF             (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC92_1000    crg_bnd_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1004    crg_bnd_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1008    crg_bnd_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ts_clk_gate_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_100C    crg_bnd_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fmc_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1010    crg_bnd_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_2_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_ephy_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_micom_1_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_pdm_0_n: 1;    //  4
    UINT32 reg_soft_rst_sync_ts_clk_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1014    crg_bnd_fmc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fmc_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC00_M23A0_T    crg_bnd_fmc00;       // 0xCC92_1000
    BCRG_CTRL_FMC_CRG_BND_FMC01_M23A0_T    crg_bnd_fmc01;       // 0xCC92_1004
    BCRG_CTRL_FMC_CRG_BND_FMC02_M23A0_T    crg_bnd_fmc02;       // 0xCC92_1008
    BCRG_CTRL_FMC_CRG_BND_FMC03_M23A0_T    crg_bnd_fmc03;       // 0xCC92_100C
    BCRG_CTRL_FMC_CRG_BND_FMC04_M23A0_T    crg_bnd_fmc04;       // 0xCC92_1010
    BCRG_CTRL_FMC_CRG_BND_FMC05_M23A0_T    crg_bnd_fmc05;       // 0xCC92_1014
}BCRG_CTRL_FMC_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

