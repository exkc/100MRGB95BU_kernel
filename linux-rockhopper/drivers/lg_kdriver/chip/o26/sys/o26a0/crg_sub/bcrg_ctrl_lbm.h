#ifndef _BCRG_CTRL_LBM_REG_O26A0_H_
#define _BCRG_CTRL_LBM_REG_O26A0_H_

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
    0xC404_1000    crg_bnd_lbm000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1004    crg_bnd_lbm001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1008    crg_bnd_lbm002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ts_clk_gate_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_100C    crg_bnd_lbm003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_ddr0sb_clk_gate_en: 1,    //   0
    reg_apb_ipw_ddr1sb_clk_gate_en: 1,    //   1
    reg_apb_ipw_gfx_clk_gate_en: 1,    //      2
    reg_apb_ipw_iommu_clk_gate_en: 1,    //    3
    reg_apb_ipw_lbus_clk_gate_en: 1,    //     4
    reg_apb_ipw_npp_clk_gate_en: 1,    //      5
    reg_apb_ipw_tivvmsb_clk_gate_en: 1,    //  6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1010    crg_bnd_lbm004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_ts_n         :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1014    crg_bnd_lbm005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_ddr0sb_n: 1,    //    0
    reg_soft_rst_apb_ipw_ddr1sb_n: 1,    //    1
    reg_soft_rst_apb_ipw_gfx_n:  1,    //      2
    reg_soft_rst_apb_ipw_iommu_n: 1,    //     3
    reg_soft_rst_apb_ipw_lbus_n: 1,    //      4
    reg_soft_rst_apb_ipw_npp_n:  1,    //      5
    reg_soft_rst_apb_ipw_tivvmsb_n: 1,    //   6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM000_O26A0_T    crg_bnd_lbm000;     // 0xC404_1000
    BCRG_CTRL_LBM_CRG_BND_LBM001_O26A0_T    crg_bnd_lbm001;     // 0xC404_1004
    BCRG_CTRL_LBM_CRG_BND_LBM002_O26A0_T    crg_bnd_lbm002;     // 0xC404_1008
    BCRG_CTRL_LBM_CRG_BND_LBM003_O26A0_T    crg_bnd_lbm003;     // 0xC404_100C
    BCRG_CTRL_LBM_CRG_BND_LBM004_O26A0_T    crg_bnd_lbm004;     // 0xC404_1010
    BCRG_CTRL_LBM_CRG_BND_LBM005_O26A0_T    crg_bnd_lbm005;     // 0xC404_1014
}BCRG_CTRL_LBM_REG_O26A0_T;
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

#define BCRG_CTRL_LBM_CRG_BND_LBM000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_LBM_CRG_BND_LBM001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_LBM_CRG_BND_LBM002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_LBM_CRG_BND_LBM003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_LBM_CRG_BND_LBM004_O26A0_T_OFF            (BASEADDRESS+0x0010)
#define BCRG_CTRL_LBM_CRG_BND_LBM005_O26A0_T_OFF            (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC404_1000    crg_bnd_lbm000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1004    crg_bnd_lbm001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1008    crg_bnd_lbm002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ts_clk_gate_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_100C    crg_bnd_lbm003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_ddr0sb_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_ddr1sb_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_gfx_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_iommu_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_lbus_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_npp_clk_gate_en: 1;    //  5
    UINT32 reg_apb_ipw_tivvmsb_clk_gate_en: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1010    crg_bnd_lbm004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_ts_n  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_1014    crg_bnd_lbm005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_ddr0sb_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_ddr1sb_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_gfx_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_iommu_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_lbus_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_npp_n: 1;    //  5
    UINT32 reg_soft_rst_apb_ipw_tivvmsb_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM000_O26A0_T    crg_bnd_lbm000;     // 0xC404_1000
    BCRG_CTRL_LBM_CRG_BND_LBM001_O26A0_T    crg_bnd_lbm001;     // 0xC404_1004
    BCRG_CTRL_LBM_CRG_BND_LBM002_O26A0_T    crg_bnd_lbm002;     // 0xC404_1008
    BCRG_CTRL_LBM_CRG_BND_LBM003_O26A0_T    crg_bnd_lbm003;     // 0xC404_100C
    BCRG_CTRL_LBM_CRG_BND_LBM004_O26A0_T    crg_bnd_lbm004;     // 0xC404_1010
    BCRG_CTRL_LBM_CRG_BND_LBM005_O26A0_T    crg_bnd_lbm005;     // 0xC404_1014
}BCRG_CTRL_LBM_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_LBM_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

