#ifndef _SCRG_CTRL_ND1_REG_O26A0_H_
#define _SCRG_CTRL_ND1_REG_O26A0_H_

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
    0xCC2D_0000    crg_nd1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0004    crg_nd1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0008    crg_nd1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_h_imx_15__nd_clk_gate_en: 1,    //  0
    reg_adaprx_h_imx_16__nd_clk_gate_en: 1,    //  1
    reg_adaprx_h_imx_8__nd_clk_gate_en: 1,    //  2
    reg_adaprx_h_imx_9__nd_clk_gate_en: 1,    //  3
    reg_adaprx_h_nd0_2__nd_clk_gate_en: 1,    //  4
    reg_adaprx_h_nd0_3__nd_clk_gate_en: 1,    //  5
    reg_adaptx_h_nd1_0__nd_clk_gate_en: 1,    //  6
    reg_adaptx_h_nd1_1__nd_clk_gate_en: 1,    //  7
    reg_adaptx_h_nd1_2__nd_clk_gate_en: 1,    //  8
    reg_adaptx_h_nd1_3__nd_clk_gate_en: 1,    //  9
    reg_adaptx_h_nd1_4__nd_clk_gate_en: 1,    //  10
    reg_adaptx_h_nd1_5__nd_clk_gate_en: 1,    //  11
    reg_adaptx_x_nd1_0__axi_nd_clk_gate_en: 1,    //  12
    reg_apb_nd_clk_gate_en    :  1,    //     13
    reg_axi_nd_clk_gate_en    :  1,    //     14
    reg_nd_clk_gate_en        :  1,    //     15
                              : 16;    //  31:16 reserved
}SCRG_CTRL_ND1_CRG_ND1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_000C    crg_nd1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_nd_n     :  1,    //      0
    reg_soft_rst_axi_nd_n     :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_h_imx_15_nd_bnd_n: 1,    //   3
    reg_soft_rst_h_imx_16_nd_bnd_n: 1,    //   4
    reg_soft_rst_h_imx_8_nd_bnd_n: 1,    //    5
    reg_soft_rst_h_imx_9_nd_bnd_n: 1,    //    6
    reg_soft_rst_h_nd0_2_nd_bnd_n: 1,    //    7
    reg_soft_rst_h_nd0_3_nd_bnd_n: 1,    //    8
    reg_soft_rst_h_nd1_0_nd_bnd_n: 1,    //    9
    reg_soft_rst_h_nd1_1_nd_bnd_n: 1,    //   10
    reg_soft_rst_h_nd1_2_nd_bnd_n: 1,    //   11
    reg_soft_rst_h_nd1_3_nd_bnd_n: 1,    //   12
    reg_soft_rst_h_nd1_4_nd_bnd_n: 1,    //   13
    reg_soft_rst_h_nd1_5_nd_bnd_n: 1,    //   14
    reg_soft_rst_nd_n         :  1,    //     15
    reg_soft_rst_p_nd1_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     17
                              : 14;    //  31:18 reserved
}SCRG_CTRL_ND1_CRG_ND1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0010    crg_nd1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND1_CRG_ND1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND1000_O26A0_T    crg_nd1000;             // 0xCC2D_0000
    SCRG_CTRL_ND1_CRG_ND1001_O26A0_T    crg_nd1001;             // 0xCC2D_0004
    SCRG_CTRL_ND1_CRG_ND1002_O26A0_T    crg_nd1002;             // 0xCC2D_0008
    SCRG_CTRL_ND1_CRG_ND1003_O26A0_T    crg_nd1003;             // 0xCC2D_000C
    SCRG_CTRL_ND1_CRG_ND1004_O26A0_T    crg_nd1004;             // 0xCC2D_0010
}SCRG_CTRL_ND1_REG_O26A0_T;
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

#define SCRG_CTRL_ND1_CRG_ND1000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND1_CRG_ND1001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND1_CRG_ND1002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND1_CRG_ND1003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_ND1_CRG_ND1004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC2D_0000    crg_nd1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0004    crg_nd1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0008    crg_nd1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_h_imx_15__nd_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_h_imx_16__nd_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_imx_8__nd_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_imx_9__nd_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_nd0_2__nd_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_nd0_3__nd_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_h_nd1_0__nd_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_h_nd1_1__nd_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_h_nd1_2__nd_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_h_nd1_3__nd_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_h_nd1_4__nd_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_h_nd1_5__nd_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_x_nd1_0__axi_nd_clk_gate_en: 1;    //  12
    UINT32 reg_apb_nd_clk_gate_en: 1;    //   13
    UINT32 reg_axi_nd_clk_gate_en: 1;    //   14
    UINT32 reg_nd_clk_gate_en :  1;    //     15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}SCRG_CTRL_ND1_CRG_ND1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_000C    crg_nd1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_nd_n: 1;    //     0
    UINT32 reg_soft_rst_axi_nd_n: 1;    //     1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_h_imx_15_nd_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_imx_16_nd_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_imx_8_nd_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_imx_9_nd_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd0_2_nd_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd0_3_nd_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd1_0_nd_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_nd1_1_nd_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_nd1_2_nd_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_nd1_3_nd_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_nd1_4_nd_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_nd1_5_nd_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_nd_n  :  1;    //     15
    UINT32 reg_soft_rst_p_nd1_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}SCRG_CTRL_ND1_CRG_ND1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC2D_0010    crg_nd1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nd_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND1_CRG_ND1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND1000_O26A0_T    crg_nd1000;             // 0xCC2D_0000
    SCRG_CTRL_ND1_CRG_ND1001_O26A0_T    crg_nd1001;             // 0xCC2D_0004
    SCRG_CTRL_ND1_CRG_ND1002_O26A0_T    crg_nd1002;             // 0xCC2D_0008
    SCRG_CTRL_ND1_CRG_ND1003_O26A0_T    crg_nd1003;             // 0xCC2D_000C
    SCRG_CTRL_ND1_CRG_ND1004_O26A0_T    crg_nd1004;             // 0xCC2D_0010
}SCRG_CTRL_ND1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_ND1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

