#ifndef _SCRG_CTRL_M0_REG_O26A0_H_
#define _SCRG_CTRL_M0_REG_O26A0_H_

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
    0xC492_0000    crg_m0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_M0_CRG_M0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_0004    crg_m0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_M0_CRG_M0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_0008    crg_m0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_ddr0sb_0__i_dmc_clk_gate_en: 1,    //  0
    reg_adaprx_x_lbus_1__i_dmc_clk_gate_en: 1,    //  1
    reg_adaprx_x_lbus_2__i_dmc_clk_gate_en: 1,    //  2
    reg_adaprx_x_lbus_3__i_dmc_clk_gate_en: 1,    //  3
    reg_apb_clk_gate_en       :  1,    //      4
    reg_i_dmc_clk_gate_en     :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_M0_CRG_M0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_000C    crg_m0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_apb_phy_n    :  1,    //      1
    reg_soft_rst_dmc_n        :  1,    //      2
    reg_soft_rst_p_ddr0sb_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lbus_1_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lbus_2_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_lbus_3_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_ddr0sb_0_axi_n: 1,    //    7
    reg_soft_rst_x_lbus_1_axi_n: 1,    //      8
    reg_soft_rst_x_lbus_2_axi_n: 1,    //      9
    reg_soft_rst_x_lbus_3_axi_n: 1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_M0_CRG_M0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M0_CRG_M0000_O26A0_T     crg_m0000  ;             // 0xC492_0000
    SCRG_CTRL_M0_CRG_M0001_O26A0_T     crg_m0001  ;             // 0xC492_0004
    SCRG_CTRL_M0_CRG_M0002_O26A0_T     crg_m0002  ;             // 0xC492_0008
    SCRG_CTRL_M0_CRG_M0003_O26A0_T     crg_m0003  ;             // 0xC492_000C
}SCRG_CTRL_M0_REG_O26A0_T;
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

#define SCRG_CTRL_M0_CRG_M0000_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_M0_CRG_M0001_O26A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_M0_CRG_M0002_O26A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_M0_CRG_M0003_O26A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC492_0000    crg_m0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_M0_CRG_M0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_0004    crg_m0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_M0_CRG_M0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_0008    crg_m0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_ddr0sb_0__i_dmc_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_lbus_1__i_dmc_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_lbus_2__i_dmc_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_x_lbus_3__i_dmc_clk_gate_en: 1;    //  3
    UINT32 reg_apb_clk_gate_en:  1;    //      4
    UINT32 reg_i_dmc_clk_gate_en: 1;    //     5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_M0_CRG_M0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC492_000C    crg_m0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_apb_phy_n: 1;    //    1
    UINT32 reg_soft_rst_dmc_n :  1;    //      2
    UINT32 reg_soft_rst_p_ddr0sb_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lbus_1_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lbus_2_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_lbus_3_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_ddr0sb_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_lbus_1_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lbus_2_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_3_axi_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_M0_CRG_M0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M0_CRG_M0000_O26A0_T     crg_m0000  ;             // 0xC492_0000
    SCRG_CTRL_M0_CRG_M0001_O26A0_T     crg_m0001  ;             // 0xC492_0004
    SCRG_CTRL_M0_CRG_M0002_O26A0_T     crg_m0002  ;             // 0xC492_0008
    SCRG_CTRL_M0_CRG_M0003_O26A0_T     crg_m0003  ;             // 0xC492_000C
}SCRG_CTRL_M0_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_M0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

