#ifndef _BCRG_CTRL_ND1_REG_O26A0_H_
#define _BCRG_CTRL_ND1_REG_O26A0_H_

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
    0xCC2E_1000    crg_bnd_nd1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ND1_CRG_BND_ND1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1004    crg_bnd_nd1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ND1_CRG_BND_ND1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1008    crg_bnd_nd1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_nd1_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ND1_CRG_BND_ND1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_100C    crg_bnd_nd1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_4_n: 1,    //    1
    reg_soft_rst_axi_brdg_ephy_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_lb0sb_0_n: 1,    //  3
    reg_soft_rst_axi_brdg_micom_0_n: 1,    //  4
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  5
    reg_soft_rst_fly_brdg_cvi_0_n: 1,    //    6
    reg_soft_rst_fly_brdg_cvi_1_n: 1,    //    7
    reg_soft_rst_fly_brdg_cvi_2_n: 1,    //    8
    reg_soft_rst_fly_brdg_cvi_3_n: 1,    //    9
    reg_soft_rst_fly_brdg_teipw_0_n: 1,    //  10
    reg_soft_rst_fly_brdg_teipw_1_n: 1,    //  11
    reg_soft_rst_fly_brdg_teipw_2_n: 1,    //  12
    reg_soft_rst_fly_brdg_teipw_3_n: 1,    //  13
    reg_soft_rst_pes_brdg_te_6_n: 1,    //    14
    reg_soft_rst_pes_brdg_te_7_n: 1,    //    15
                              : 16;    //  31:16 reserved
}BCRG_CTRL_ND1_CRG_BND_ND1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1010    crg_bnd_nd1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_nd1_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ND1_CRG_BND_ND1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND1_CRG_BND_ND1000_O26A0_T    crg_bnd_nd1000;     // 0xCC2E_1000
    BCRG_CTRL_ND1_CRG_BND_ND1001_O26A0_T    crg_bnd_nd1001;     // 0xCC2E_1004
    BCRG_CTRL_ND1_CRG_BND_ND1002_O26A0_T    crg_bnd_nd1002;     // 0xCC2E_1008
    BCRG_CTRL_ND1_CRG_BND_ND1003_O26A0_T    crg_bnd_nd1003;     // 0xCC2E_100C
    BCRG_CTRL_ND1_CRG_BND_ND1004_O26A0_T    crg_bnd_nd1004;     // 0xCC2E_1010
}BCRG_CTRL_ND1_REG_O26A0_T;
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

#define BCRG_CTRL_ND1_CRG_BND_ND1000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_ND1_CRG_BND_ND1001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_ND1_CRG_BND_ND1002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_ND1_CRG_BND_ND1003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_ND1_CRG_BND_ND1004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC2E_1000    crg_bnd_nd1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ND1_CRG_BND_ND1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1004    crg_bnd_nd1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ND1_CRG_BND_ND1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1008    crg_bnd_nd1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_nd1_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ND1_CRG_BND_ND1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_100C    crg_bnd_nd1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_4_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_ephy_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lb0sb_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_micom_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_cvi_0_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_cvi_1_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_cvi_2_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_cvi_3_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_teipw_0_n: 1;    //  10
    UINT32 reg_soft_rst_fly_brdg_teipw_1_n: 1;    //  11
    UINT32 reg_soft_rst_fly_brdg_teipw_2_n: 1;    //  12
    UINT32 reg_soft_rst_fly_brdg_teipw_3_n: 1;    //  13
    UINT32 reg_soft_rst_pes_brdg_te_6_n: 1;    //  14
    UINT32 reg_soft_rst_pes_brdg_te_7_n: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}BCRG_CTRL_ND1_CRG_BND_ND1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2E_1010    crg_bnd_nd1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_nd1_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ND1_CRG_BND_ND1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND1_CRG_BND_ND1000_O26A0_T    crg_bnd_nd1000;     // 0xCC2E_1000
    BCRG_CTRL_ND1_CRG_BND_ND1001_O26A0_T    crg_bnd_nd1001;     // 0xCC2E_1004
    BCRG_CTRL_ND1_CRG_BND_ND1002_O26A0_T    crg_bnd_nd1002;     // 0xCC2E_1008
    BCRG_CTRL_ND1_CRG_BND_ND1003_O26A0_T    crg_bnd_nd1003;     // 0xCC2E_100C
    BCRG_CTRL_ND1_CRG_BND_ND1004_O26A0_T    crg_bnd_nd1004;     // 0xCC2E_1010
}BCRG_CTRL_ND1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_ND1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

