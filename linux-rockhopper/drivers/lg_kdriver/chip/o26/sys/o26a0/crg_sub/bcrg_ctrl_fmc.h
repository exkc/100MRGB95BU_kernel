#ifndef _BCRG_CTRL_FMC_REG_O26A0_H_
#define _BCRG_CTRL_FMC_REG_O26A0_H_

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
    0xCCC6_1000    crg_bnd_fmc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1004    crg_bnd_fmc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1008    crg_bnd_fmc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fmc_clk_gate_en: 1,    //      0
    reg_apb_ipw_srcosb_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_100C    crg_bnd_fmc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_fmesb_0_n: 1,    //  0
    reg_soft_rst_axi_brdg_gpu_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_gpu_1_n: 1,    //    2
    reg_soft_rst_axi_brdg_sre_0_n: 1,    //    3
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //    4
    reg_soft_rst_fly_brdg_gsc_10_n: 1,    //   5
    reg_soft_rst_fly_brdg_vsd_4_n: 1,    //    6
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //    7
    reg_soft_rst_hsp_brdg_gsc_5_n: 1,    //    8
    reg_soft_rst_hsp_brdg_gsc_6_n: 1,    //    9
    reg_soft_rst_hsp_brdg_gsc_7_n: 1,    //   10
    reg_soft_rst_hsp_brdg_gsc_8_n: 1,    //   11
                              : 20;    //  31:12 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1010    crg_bnd_fmc004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fmc_n:  1,    //      0
    reg_soft_rst_apb_ipw_srcosb_n: 1,    //    1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC000_O26A0_T    crg_bnd_fmc000;     // 0xCCC6_1000
    BCRG_CTRL_FMC_CRG_BND_FMC001_O26A0_T    crg_bnd_fmc001;     // 0xCCC6_1004
    BCRG_CTRL_FMC_CRG_BND_FMC002_O26A0_T    crg_bnd_fmc002;     // 0xCCC6_1008
    BCRG_CTRL_FMC_CRG_BND_FMC003_O26A0_T    crg_bnd_fmc003;     // 0xCCC6_100C
    BCRG_CTRL_FMC_CRG_BND_FMC004_O26A0_T    crg_bnd_fmc004;     // 0xCCC6_1010
}BCRG_CTRL_FMC_REG_O26A0_T;
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

#define BCRG_CTRL_FMC_CRG_BND_FMC000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMC_CRG_BND_FMC001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMC_CRG_BND_FMC002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMC_CRG_BND_FMC003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMC_CRG_BND_FMC004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC6_1000    crg_bnd_fmc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1004    crg_bnd_fmc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1008    crg_bnd_fmc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fmc_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_srcosb_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_100C    crg_bnd_fmc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_fmesb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_gpu_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_gpu_1_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_sre_0_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_gsc_10_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_vsd_4_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_gsc_5_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_gsc_6_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_gsc_7_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_gsc_8_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC6_1010    crg_bnd_fmc004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fmc_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_srcosb_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC000_O26A0_T    crg_bnd_fmc000;     // 0xCCC6_1000
    BCRG_CTRL_FMC_CRG_BND_FMC001_O26A0_T    crg_bnd_fmc001;     // 0xCCC6_1004
    BCRG_CTRL_FMC_CRG_BND_FMC002_O26A0_T    crg_bnd_fmc002;     // 0xCCC6_1008
    BCRG_CTRL_FMC_CRG_BND_FMC003_O26A0_T    crg_bnd_fmc003;     // 0xCCC6_100C
    BCRG_CTRL_FMC_CRG_BND_FMC004_O26A0_T    crg_bnd_fmc004;     // 0xCCC6_1010
}BCRG_CTRL_FMC_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_FMC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

