#ifndef _BCRG_CTRL_ND0_M23A0_REG_H_
#define _BCRG_CTRL_ND0_M23A0_REG_H_

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
    0xCC66_1000    crg_bnd_nd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1004    crg_bnd_nd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1008    crg_bnd_nd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_hdr_clk_gate_en: 1,    //      0
    reg_apb_ipw_nd_clk_gate_en:  1,    //      1
    reg_apb_ipw_sre_clk_gate_en: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_ND0_CRG_BND_ND002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_100C    crg_bnd_nd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cvdsb_0_n: 1,    //  0
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_emusb_0_n: 1,    //  2
    reg_soft_rst_axi_brdg_gpu_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_imx_0_n: 1,    //    4
    reg_soft_rst_axi_brdg_imx_1_n: 1,    //    5
    reg_soft_rst_axi_brdg_vd0_0_n: 1,    //    6
    reg_soft_rst_axi_brdg_vd0_1_n: 1,    //    7
    reg_soft_rst_axi_brdg_vdo_0_n: 1,    //    8
    reg_soft_rst_axi_brdg_vdo_1_n: 1,    //    9
                              : 22;    //  31:10 reserved
}BCRG_CTRL_ND0_CRG_BND_ND003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1010    crg_bnd_nd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_hdr_n:  1,    //      0
    reg_soft_rst_apb_ipw_nd_n :  1,    //      1
    reg_soft_rst_apb_ipw_sre_n:  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_ND0_CRG_BND_ND004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND000_M23A0_T    crg_bnd_nd000;       // 0xCC66_1000
    BCRG_CTRL_ND0_CRG_BND_ND001_M23A0_T    crg_bnd_nd001;       // 0xCC66_1004
    BCRG_CTRL_ND0_CRG_BND_ND002_M23A0_T    crg_bnd_nd002;       // 0xCC66_1008
    BCRG_CTRL_ND0_CRG_BND_ND003_M23A0_T    crg_bnd_nd003;       // 0xCC66_100C
    BCRG_CTRL_ND0_CRG_BND_ND004_M23A0_T    crg_bnd_nd004;       // 0xCC66_1010
}BCRG_CTRL_ND0_REG_M23A0_T;
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

#define BCRG_CTRL_ND0_CRG_BND_ND000_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_ND0_CRG_BND_ND001_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_ND0_CRG_BND_ND002_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_ND0_CRG_BND_ND003_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_ND0_CRG_BND_ND004_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC66_1000    crg_bnd_nd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1004    crg_bnd_nd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1008    crg_bnd_nd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_hdr_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_nd_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sre_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_100C    crg_bnd_nd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cvdsb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_emusb_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_gpu_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_imx_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_imx_1_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_vd0_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_vd0_1_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vdo_0_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_vdo_1_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC66_1010    crg_bnd_nd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_hdr_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_nd_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sre_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND000_M23A0_T    crg_bnd_nd000;       // 0xCC66_1000
    BCRG_CTRL_ND0_CRG_BND_ND001_M23A0_T    crg_bnd_nd001;       // 0xCC66_1004
    BCRG_CTRL_ND0_CRG_BND_ND002_M23A0_T    crg_bnd_nd002;       // 0xCC66_1008
    BCRG_CTRL_ND0_CRG_BND_ND003_M23A0_T    crg_bnd_nd003;       // 0xCC66_100C
    BCRG_CTRL_ND0_CRG_BND_ND004_M23A0_T    crg_bnd_nd004;       // 0xCC66_1010
}BCRG_CTRL_ND0_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

