#ifndef _SCRG_CTRL_LNX0_REG_O26A0_H_
#define _SCRG_CTRL_LNX0_REG_O26A0_H_

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
    0xCC55_0000    crg_lnx0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LNX0_CRG_LNX0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0004    crg_lnx0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LNX0_CRG_LNX0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0008    crg_lnx0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx0_jtag_tck_gate_en :  1,    //      0
    reg_lnx0_axi_clk_gate_en  :  1,    //      1
    reg_lnx0_core_clk_gate_en :  1,    //      2
    reg_lnx0_apb_clk_gate_en  :  1,    //      3
    reg_adaptx_x_lnx0_0__lnx0_axi_clk_gate_en: 1,    //  4
    reg_adaprx_h_lnx1_3__lnx0_core_clk_gate_en: 1,    //  5
    reg_adaprx_h_lnx1_2__lnx0_core_clk_gate_en: 1,    //  6
    reg_adaprx_h_lnx1_1__lnx0_core_clk_gate_en: 1,    //  7
    reg_adaprx_h_lnx1_0__lnx0_core_clk_gate_en: 1,    //  8
    reg_adaptx_h_lnx0_3__lnx0_core_clk_gate_en: 1,    //  9
    reg_adaptx_h_lnx0_2__lnx0_core_clk_gate_en: 1,    //  10
    reg_adaptx_h_lnx0_1__lnx0_core_clk_gate_en: 1,    //  11
    reg_adaptx_h_lnx0_0__lnx0_core_clk_gate_en: 1,    //  12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_LNX0_CRG_LNX0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_000C    crg_lnx0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_lnx0_0_axi_bnd_n: 1,    //  0
    reg_soft_rst_x_lnx0_0_axi_n: 1,    //      1
    reg_soft_rst_lnx0_axi_flush_n: 1,    //    2
    reg_soft_rst_lnx0_axi_n   :  1,    //      3
    reg_soft_rst_lnx0_core_n  :  1,    //      4
    reg_soft_rst_lnx0_apb_async_n: 1,    //    5
    reg_soft_rst_lnx0_apb_n   :  1,    //      6
    reg_soft_rst_h_lnx1_3_lnx0_core_bnd_n: 1,    //  7
    reg_soft_rst_h_lnx1_2_lnx0_core_bnd_n: 1,    //  8
    reg_soft_rst_h_lnx1_1_lnx0_core_bnd_n: 1,    //  9
    reg_soft_rst_h_lnx1_0_lnx0_core_bnd_n: 1,    //  10
    reg_soft_rst_h_lnx0_3_lnx0_core_bnd_n: 1,    //  11
    reg_soft_rst_h_lnx0_2_lnx0_core_bnd_n: 1,    //  12
    reg_soft_rst_h_lnx0_1_lnx0_core_bnd_n: 1,    //  13
    reg_soft_rst_h_lnx0_0_lnx0_core_bnd_n: 1,    //  14
                              : 17;    //  31:15 reserved
}SCRG_CTRL_LNX0_CRG_LNX0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0010    crg_lnx0004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx0_core_clk_sel     :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LNX0_CRG_LNX0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX0_CRG_LNX0000_O26A0_T    crg_lnx0000;          // 0xCC55_0000
    SCRG_CTRL_LNX0_CRG_LNX0001_O26A0_T    crg_lnx0001;          // 0xCC55_0004
    SCRG_CTRL_LNX0_CRG_LNX0002_O26A0_T    crg_lnx0002;          // 0xCC55_0008
    SCRG_CTRL_LNX0_CRG_LNX0003_O26A0_T    crg_lnx0003;          // 0xCC55_000C
    SCRG_CTRL_LNX0_CRG_LNX0004_O26A0_T    crg_lnx0004;          // 0xCC55_0010
}SCRG_CTRL_LNX0_REG_O26A0_T;
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

#define SCRG_CTRL_LNX0_CRG_LNX0000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_LNX0_CRG_LNX0001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_LNX0_CRG_LNX0002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_LNX0_CRG_LNX0003_O26A0_T_OFF              (BASEADDRESS+0x000C)
#define SCRG_CTRL_LNX0_CRG_LNX0004_O26A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC55_0000    crg_lnx0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LNX0_CRG_LNX0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0004    crg_lnx0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LNX0_CRG_LNX0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0008    crg_lnx0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx0_jtag_tck_gate_en: 1;    //  0
    UINT32 reg_lnx0_axi_clk_gate_en: 1;    //  1
    UINT32 reg_lnx0_core_clk_gate_en: 1;    //  2
    UINT32 reg_lnx0_apb_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_x_lnx0_0__lnx0_axi_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_lnx1_3__lnx0_core_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_lnx1_2__lnx0_core_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_h_lnx1_1__lnx0_core_clk_gate_en: 1;    //  7
    UINT32 reg_adaprx_h_lnx1_0__lnx0_core_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_h_lnx0_3__lnx0_core_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_h_lnx0_2__lnx0_core_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_h_lnx0_1__lnx0_core_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_h_lnx0_0__lnx0_core_clk_gate_en: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_LNX0_CRG_LNX0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_000C    crg_lnx0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_lnx0_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_x_lnx0_0_axi_n: 1;    //  1
    UINT32 reg_soft_rst_lnx0_axi_flush_n: 1;    //  2
    UINT32 reg_soft_rst_lnx0_axi_n: 1;    //   3
    UINT32 reg_soft_rst_lnx0_core_n: 1;    //  4
    UINT32 reg_soft_rst_lnx0_apb_async_n: 1;    //  5
    UINT32 reg_soft_rst_lnx0_apb_n: 1;    //   6
    UINT32 reg_soft_rst_h_lnx1_3_lnx0_core_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_lnx1_2_lnx0_core_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_lnx1_1_lnx0_core_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_lnx1_0_lnx0_core_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_lnx0_3_lnx0_core_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_lnx0_2_lnx0_core_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_lnx0_1_lnx0_core_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_lnx0_0_lnx0_core_bnd_n: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_LNX0_CRG_LNX0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_0010    crg_lnx0004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx0_core_clk_sel: 2;    //  1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LNX0_CRG_LNX0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX0_CRG_LNX0000_O26A0_T    crg_lnx0000;          // 0xCC55_0000
    SCRG_CTRL_LNX0_CRG_LNX0001_O26A0_T    crg_lnx0001;          // 0xCC55_0004
    SCRG_CTRL_LNX0_CRG_LNX0002_O26A0_T    crg_lnx0002;          // 0xCC55_0008
    SCRG_CTRL_LNX0_CRG_LNX0003_O26A0_T    crg_lnx0003;          // 0xCC55_000C
    SCRG_CTRL_LNX0_CRG_LNX0004_O26A0_T    crg_lnx0004;          // 0xCC55_0010
}SCRG_CTRL_LNX0_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_LNX0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

