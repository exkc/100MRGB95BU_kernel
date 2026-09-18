#ifndef _BCRG_CTRL_ND0_REG_O26A0_H_
#define _BCRG_CTRL_ND0_REG_O26A0_H_

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
    0xCC2B_1000    crg_bnd_nd0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1004    crg_bnd_nd0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1008    crg_bnd_nd0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_nd0_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ND0_CRG_BND_ND0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_100C    crg_bnd_nd0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_4_n: 1,    //    0
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_ephy_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_micom_0_n: 1,    //  4
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //    5
    reg_soft_rst_fly_brdg_tp_int_n: 1,    //   6
    reg_soft_rst_hsp_brdg_dnsr0_0_n: 1,    //  7
    reg_soft_rst_hsp_brdg_dnsr1_0_n: 1,    //  8
    reg_soft_rst_hsp_brdg_sre_0_n: 1,    //    9
    reg_soft_rst_hsp_brdg_sre_1_n: 1,    //   10
                              : 21;    //  31:11 reserved
}BCRG_CTRL_ND0_CRG_BND_ND0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1010    crg_bnd_nd0004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_nd0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ND0_CRG_BND_ND0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND0000_O26A0_T    crg_bnd_nd0000;     // 0xCC2B_1000
    BCRG_CTRL_ND0_CRG_BND_ND0001_O26A0_T    crg_bnd_nd0001;     // 0xCC2B_1004
    BCRG_CTRL_ND0_CRG_BND_ND0002_O26A0_T    crg_bnd_nd0002;     // 0xCC2B_1008
    BCRG_CTRL_ND0_CRG_BND_ND0003_O26A0_T    crg_bnd_nd0003;     // 0xCC2B_100C
    BCRG_CTRL_ND0_CRG_BND_ND0004_O26A0_T    crg_bnd_nd0004;     // 0xCC2B_1010
}BCRG_CTRL_ND0_REG_O26A0_T;
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

#define BCRG_CTRL_ND0_CRG_BND_ND0000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_ND0_CRG_BND_ND0001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_ND0_CRG_BND_ND0002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_ND0_CRG_BND_ND0003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_ND0_CRG_BND_ND0004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC2B_1000    crg_bnd_nd0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1004    crg_bnd_nd0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1008    crg_bnd_nd0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_nd0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_100C    crg_bnd_nd0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_4_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_ephy_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_micom_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_tp_int_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_dnsr0_0_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_dnsr1_0_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_sre_0_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_sre_1_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2B_1010    crg_bnd_nd0004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_nd0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND0000_O26A0_T    crg_bnd_nd0000;     // 0xCC2B_1000
    BCRG_CTRL_ND0_CRG_BND_ND0001_O26A0_T    crg_bnd_nd0001;     // 0xCC2B_1004
    BCRG_CTRL_ND0_CRG_BND_ND0002_O26A0_T    crg_bnd_nd0002;     // 0xCC2B_1008
    BCRG_CTRL_ND0_CRG_BND_ND0003_O26A0_T    crg_bnd_nd0003;     // 0xCC2B_100C
    BCRG_CTRL_ND0_CRG_BND_ND0004_O26A0_T    crg_bnd_nd0004;     // 0xCC2B_1010
}BCRG_CTRL_ND0_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_ND0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

