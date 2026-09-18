#ifndef _SCRG_CTRL_IOMMU_REG_O26A0_H_
#define _SCRG_CTRL_IOMMU_REG_O26A0_H_

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
    0xC411_0000    crg_iommu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_IOMMU_CRG_IOMMU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_0004    crg_iommu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_IOMMU_CRG_IOMMU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_0008    crg_iommu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_lnx0_0__iommu_clk_gate_en: 1,    //  0
    reg_adaprx_x_lnx1_0__iommu_clk_gate_en: 1,    //  1
    reg_adaprx_x_npp_0__iommu_clk_gate_en: 1,    //  2
    reg_adaptx_x_iommu_0__iommu_clk_gate_en: 1,    //  3
    reg_adaptx_x_iommu_1__iommu_clk_gate_en: 1,    //  4
    reg_adaptx_x_iommu_2__iommu_clk_gate_en: 1,    //  5
    reg_iommu_clk_gate_en     :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_IOMMU_CRG_IOMMU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_000C    crg_iommu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_bas_switch_n :  1,    //      1
    reg_soft_rst_iommu_sbus_n :  1,    //      2
    reg_soft_rst_lnx0_tbu_n   :  1,    //      3
    reg_soft_rst_lnx1_tbu_n   :  1,    //      4
    reg_soft_rst_npp_tbu_n    :  1,    //      5
    reg_soft_rst_p_iommu_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_iommu_1_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_iommu_2_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_lnx0_0_axi_bnd_n: 1,    //  9
    reg_soft_rst_p_lnx1_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_npp_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_tcu_n        :  1,    //     12
    reg_soft_rst_x_iommu_0_axi_n: 1,    //    13
    reg_soft_rst_x_iommu_1_axi_n: 1,    //    14
    reg_soft_rst_x_iommu_2_axi_n: 1,    //    15
    reg_soft_rst_x_lnx0_0_axi_n: 1,    //     16
    reg_soft_rst_x_lnx1_0_axi_n: 1,    //     17
    reg_soft_rst_x_npp_0_axi_n:  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_IOMMU_CRG_IOMMU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_iommu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IOMMU_CRG_IOMMU000_O26A0_T    crg_iommu000;       // 0xC411_0000
    SCRG_CTRL_IOMMU_CRG_IOMMU001_O26A0_T    crg_iommu001;       // 0xC411_0004
    SCRG_CTRL_IOMMU_CRG_IOMMU002_O26A0_T    crg_iommu002;       // 0xC411_0008
    SCRG_CTRL_IOMMU_CRG_IOMMU003_O26A0_T    crg_iommu003;       // 0xC411_000C
}SCRG_CTRL_IOMMU_REG_O26A0_T;
/* 4 regs */

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

#define SCRG_CTRL_IOMMU_CRG_IOMMU000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_IOMMU_CRG_IOMMU001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_IOMMU_CRG_IOMMU002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_IOMMU_CRG_IOMMU003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC411_0000    crg_iommu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_IOMMU_CRG_IOMMU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_0004    crg_iommu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_IOMMU_CRG_IOMMU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_0008    crg_iommu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_lnx0_0__iommu_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_lnx1_0__iommu_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_npp_0__iommu_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_x_iommu_0__iommu_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_x_iommu_1__iommu_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_x_iommu_2__iommu_clk_gate_en: 1;    //  5
    UINT32 reg_iommu_clk_gate_en: 1;    //     6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_IOMMU_CRG_IOMMU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC411_000C    crg_iommu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_bas_switch_n: 1;    //  1
    UINT32 reg_soft_rst_iommu_sbus_n: 1;    //  2
    UINT32 reg_soft_rst_lnx0_tbu_n: 1;    //   3
    UINT32 reg_soft_rst_lnx1_tbu_n: 1;    //   4
    UINT32 reg_soft_rst_npp_tbu_n: 1;    //    5
    UINT32 reg_soft_rst_p_iommu_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_iommu_1_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_iommu_2_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_lnx0_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_lnx1_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_npp_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_tcu_n :  1;    //     12
    UINT32 reg_soft_rst_x_iommu_0_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_iommu_1_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_iommu_2_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_lnx0_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_lnx1_0_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_npp_0_axi_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_IOMMU_CRG_IOMMU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_iommu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IOMMU_CRG_IOMMU000_O26A0_T    crg_iommu000;       // 0xC411_0000
    SCRG_CTRL_IOMMU_CRG_IOMMU001_O26A0_T    crg_iommu001;       // 0xC411_0004
    SCRG_CTRL_IOMMU_CRG_IOMMU002_O26A0_T    crg_iommu002;       // 0xC411_0008
    SCRG_CTRL_IOMMU_CRG_IOMMU003_O26A0_T    crg_iommu003;       // 0xC411_000C
}SCRG_CTRL_IOMMU_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_IOMMU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

