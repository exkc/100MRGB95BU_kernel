#ifndef _BCRG_CTRL_SRE_REG_O26A0_H_
#define _BCRG_CTRL_SRE_REG_O26A0_H_

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
    0xCCA2_1000    crg_bnd_sre000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_SRE_CRG_BND_SRE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1004    crg_bnd_sre001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_SRE_CRG_BND_SRE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1008    crg_bnd_sre002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_gpu_clk_gate_en: 1,    //      0
    reg_apb_ipw_sre_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_100C    crg_bnd_sre003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_emusb_0_n: 1,    //  0
    reg_soft_rst_fly_brdg_cco_7_n: 1,    //    1
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //    2
    reg_soft_rst_fly_brdg_imx_10_n: 1,    //   3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1010    crg_bnd_sre004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_gpu_n:  1,    //      0
    reg_soft_rst_apb_ipw_sre_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_SRE_CRG_BND_SRE000_O26A0_T    crg_bnd_sre000;     // 0xCCA2_1000
    BCRG_CTRL_SRE_CRG_BND_SRE001_O26A0_T    crg_bnd_sre001;     // 0xCCA2_1004
    BCRG_CTRL_SRE_CRG_BND_SRE002_O26A0_T    crg_bnd_sre002;     // 0xCCA2_1008
    BCRG_CTRL_SRE_CRG_BND_SRE003_O26A0_T    crg_bnd_sre003;     // 0xCCA2_100C
    BCRG_CTRL_SRE_CRG_BND_SRE004_O26A0_T    crg_bnd_sre004;     // 0xCCA2_1010
}BCRG_CTRL_SRE_REG_O26A0_T;
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

#define BCRG_CTRL_SRE_CRG_BND_SRE000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_SRE_CRG_BND_SRE001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_SRE_CRG_BND_SRE002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_SRE_CRG_BND_SRE003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_SRE_CRG_BND_SRE004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCA2_1000    crg_bnd_sre000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_SRE_CRG_BND_SRE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1004    crg_bnd_sre001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_SRE_CRG_BND_SRE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1008    crg_bnd_sre002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_gpu_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sre_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_100C    crg_bnd_sre003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_emusb_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_cco_7_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_imx_10_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_1010    crg_bnd_sre004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_gpu_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sre_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_SRE_CRG_BND_SRE000_O26A0_T    crg_bnd_sre000;     // 0xCCA2_1000
    BCRG_CTRL_SRE_CRG_BND_SRE001_O26A0_T    crg_bnd_sre001;     // 0xCCA2_1004
    BCRG_CTRL_SRE_CRG_BND_SRE002_O26A0_T    crg_bnd_sre002;     // 0xCCA2_1008
    BCRG_CTRL_SRE_CRG_BND_SRE003_O26A0_T    crg_bnd_sre003;     // 0xCCA2_100C
    BCRG_CTRL_SRE_CRG_BND_SRE004_O26A0_T    crg_bnd_sre004;     // 0xCCA2_1010
}BCRG_CTRL_SRE_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_SRE_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

