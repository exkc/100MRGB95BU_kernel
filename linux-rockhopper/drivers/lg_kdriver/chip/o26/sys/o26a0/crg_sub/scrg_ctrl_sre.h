#ifndef _SCRG_CTRL_SRE_REG_O26A0_H_
#define _SCRG_CTRL_SRE_REG_O26A0_H_

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
    0xCCA1_0000    crg_sre000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_0004    crg_sre001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_0008    crg_sre002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_h_dnsr0_0__de_clk_gate_en: 1,    //  0
    reg_adaprx_h_dnsr1_0__de_clk_gate_en: 1,    //  1
    reg_adaprx_h_nd0_4__de_clk_gate_en: 1,    //  2
    reg_adaprx_h_nd0_5__de_clk_gate_en: 1,    //  3
    reg_adaprx_h_nd1_2__de_clk_gate_en: 1,    //  4
    reg_adaprx_h_nd1_3__de_clk_gate_en: 1,    //  5
    reg_adaprx_h_vsd_1__de_clk_gate_en: 1,    //  6
    reg_adaprx_h_vsd_2__de_clk_gate_en: 1,    //  7
    reg_adaptx_h_sre_0__de_clk_gate_en: 1,    //  8
    reg_adaptx_h_sre_1__de_clk_gate_en: 1,    //  9
    reg_adaptx_h_sre_2__de_clk_gate_en: 1,    //  10
    reg_adaptx_h_sre_3__de_clk_gate_en: 1,    //  11
    reg_adaptx_h_sre_4__de_clk_gate_en: 1,    //  12
    reg_adaptx_h_sre_5__de_clk_gate_en: 1,    //  13
    reg_adaptx_h_sre_6__de_clk_gate_en: 1,    //  14
    reg_adaptx_h_sre_7__de_clk_gate_en: 1,    //  15
    reg_adaptx_h_sre_8__de_clk_gate_en: 1,    //  16
    reg_adaptx_x_sre_0__axi_clk_gate_en: 1,    //  17
    reg_adaptx_x_sre_1__axi_clk_gate_en: 1,    //  18
    reg_apb_clk_gate_en       :  1,    //     19
    reg_axi_clk_gate_en       :  1,    //     20
    reg_de_clk_gate_en        :  1,    //     21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_SRE_CRG_SRE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_000C    crg_sre003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_dnsr0_0_de_bnd_n: 1,    //  3
    reg_soft_rst_h_dnsr1_0_de_bnd_n: 1,    //  4
    reg_soft_rst_h_nd0_4_de_bnd_n: 1,    //    5
    reg_soft_rst_h_nd0_5_de_bnd_n: 1,    //    6
    reg_soft_rst_h_nd1_2_de_bnd_n: 1,    //    7
    reg_soft_rst_h_nd1_3_de_bnd_n: 1,    //    8
    reg_soft_rst_h_sre_0_de_bnd_n: 1,    //    9
    reg_soft_rst_h_sre_1_de_bnd_n: 1,    //   10
    reg_soft_rst_h_sre_2_de_bnd_n: 1,    //   11
    reg_soft_rst_h_sre_3_de_bnd_n: 1,    //   12
    reg_soft_rst_h_sre_4_de_bnd_n: 1,    //   13
    reg_soft_rst_h_sre_5_de_bnd_n: 1,    //   14
    reg_soft_rst_h_sre_6_de_bnd_n: 1,    //   15
    reg_soft_rst_h_sre_7_de_bnd_n: 1,    //   16
    reg_soft_rst_h_sre_8_de_bnd_n: 1,    //   17
    reg_soft_rst_h_vsd_1_de_bnd_n: 1,    //   18
    reg_soft_rst_h_vsd_2_de_bnd_n: 1,    //   19
    reg_soft_rst_p_sre_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_sre_1_axi_bnd_n: 1,    //  21
    reg_soft_rst_x_sre_0_axi_n:  1,    //     22
    reg_soft_rst_x_sre_1_axi_n:  1,    //     23
                              :  8;    //  31:24 reserved
}SCRG_CTRL_SRE_CRG_SRE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE000_O26A0_T    crg_sre000;             // 0xCCA1_0000
    SCRG_CTRL_SRE_CRG_SRE001_O26A0_T    crg_sre001;             // 0xCCA1_0004
    SCRG_CTRL_SRE_CRG_SRE002_O26A0_T    crg_sre002;             // 0xCCA1_0008
    SCRG_CTRL_SRE_CRG_SRE003_O26A0_T    crg_sre003;             // 0xCCA1_000C
}SCRG_CTRL_SRE_REG_O26A0_T;
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

#define SCRG_CTRL_SRE_CRG_SRE000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_SRE_CRG_SRE001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_SRE_CRG_SRE002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_SRE_CRG_SRE003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCA1_0000    crg_sre000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_0004    crg_sre001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_0008    crg_sre002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_h_dnsr0_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_h_dnsr1_0__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_nd0_4__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_nd0_5__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_nd1_2__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_nd1_3__de_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_vsd_1__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_h_vsd_2__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_h_sre_0__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_h_sre_1__de_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_h_sre_2__de_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_h_sre_3__de_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_h_sre_4__de_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_h_sre_5__de_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_h_sre_6__de_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_h_sre_7__de_clk_gate_en: 1;    //  15
    UINT32 reg_adaptx_h_sre_8__de_clk_gate_en: 1;    //  16
    UINT32 reg_adaptx_x_sre_0__axi_clk_gate_en: 1;    //  17
    UINT32 reg_adaptx_x_sre_1__axi_clk_gate_en: 1;    //  18
    UINT32 reg_apb_clk_gate_en:  1;    //     19
    UINT32 reg_axi_clk_gate_en:  1;    //     20
    UINT32 reg_de_clk_gate_en :  1;    //     21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA1_000C    crg_sre003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_dnsr0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_dnsr1_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd0_4_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd0_5_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd1_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd1_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_sre_0_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_sre_1_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_sre_2_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_sre_3_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_sre_4_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_sre_5_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_sre_6_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_sre_7_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_sre_8_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_vsd_1_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_vsd_2_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_sre_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_sre_1_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_x_sre_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_sre_1_axi_n: 1;    //  23
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE000_O26A0_T    crg_sre000;             // 0xCCA1_0000
    SCRG_CTRL_SRE_CRG_SRE001_O26A0_T    crg_sre001;             // 0xCCA1_0004
    SCRG_CTRL_SRE_CRG_SRE002_O26A0_T    crg_sre002;             // 0xCCA1_0008
    SCRG_CTRL_SRE_CRG_SRE003_O26A0_T    crg_sre003;             // 0xCCA1_000C
}SCRG_CTRL_SRE_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_SRE_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

