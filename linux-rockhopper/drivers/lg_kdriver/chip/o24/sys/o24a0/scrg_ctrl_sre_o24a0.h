#ifndef _SCRG_CTRL_SRE_REG_O24A0_H_
#define _SCRG_CTRL_SRE_REG_O24A0_H_

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
    0xCC63_0000    crg_sre0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0004    crg_sre1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0008    crg_sre2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_SRE_CRG_SRE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_000C    crg_sre3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_dnnr_0_de_bnd_n: 1,    //   3
    reg_soft_rst_h_dnsr_0_de_bnd_n: 1,    //   4
    reg_soft_rst_h_imx_10_de_bnd_n: 1,    //   5
    reg_soft_rst_h_imx_11_de_bnd_n: 1,    //   6
    reg_soft_rst_h_nd0_4_de_bnd_n: 1,    //    7
    reg_soft_rst_h_nd0_5_de_bnd_n: 1,    //    8
    reg_soft_rst_h_nd1_2_de_bnd_n: 1,    //    9
    reg_soft_rst_h_nd1_3_de_bnd_n: 1,    //   10
    reg_soft_rst_h_sre_0_de_bnd_n: 1,    //   11
    reg_soft_rst_h_sre_1_de_bnd_n: 1,    //   12
    reg_soft_rst_h_sre_2_de_bnd_n: 1,    //   13
    reg_soft_rst_h_sre_3_de_bnd_n: 1,    //   14
    reg_soft_rst_h_sre_4_de_bnd_n: 1,    //   15
    reg_soft_rst_h_sre_5_de_bnd_n: 1,    //   16
    reg_soft_rst_h_sre_6_de_bnd_n: 1,    //   17
    reg_soft_rst_h_sre_7_de_bnd_n: 1,    //   18
    reg_soft_rst_h_sre_8_de_bnd_n: 1,    //   19
    reg_soft_rst_p_sre_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_sre_1_axi_bnd_n: 1,    //  21
    reg_soft_rst_x_sre_0_axi_bnd_n: 1,    //  22
    reg_soft_rst_x_sre_0_axi_n:  1,    //     23
    reg_soft_rst_x_sre_1_axi_bnd_n: 1,    //  24
    reg_soft_rst_x_sre_1_axi_n:  1,    //     25
                              :  6;    //  31:26 reserved
}SCRG_CTRL_SRE_CRG_SRE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE0_O24A0_T     crg_sre0   ;             // 0xCC63_0000
    SCRG_CTRL_SRE_CRG_SRE1_O24A0_T     crg_sre1   ;             // 0xCC63_0004
    SCRG_CTRL_SRE_CRG_SRE2_O24A0_T     crg_sre2   ;             // 0xCC63_0008
    SCRG_CTRL_SRE_CRG_SRE3_O24A0_T     crg_sre3   ;             // 0xCC63_000C
}SCRG_CTRL_SRE_REG_O24A0_T;
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

#define SCRG_CTRL_SRE_CRG_SRE0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_SRE_CRG_SRE1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_SRE_CRG_SRE2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_SRE_CRG_SRE3_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC63_0000    crg_sre0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0004    crg_sre1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0008    crg_sre2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_000C    crg_sre3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_dnnr_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_dnsr_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_imx_10_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_imx_11_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd0_4_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd0_5_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd1_2_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_nd1_3_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_sre_0_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_sre_1_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_sre_2_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_sre_3_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_sre_4_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_sre_5_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_sre_6_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_sre_7_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_sre_8_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_sre_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_sre_1_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_x_sre_0_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_x_sre_0_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_sre_1_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_x_sre_1_axi_n: 1;    //  25
    UINT32 resvd00            :  6;    //  31:26 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE0_O24A0_T     crg_sre0   ;             // 0xCC63_0000
    SCRG_CTRL_SRE_CRG_SRE1_O24A0_T     crg_sre1   ;             // 0xCC63_0004
    SCRG_CTRL_SRE_CRG_SRE2_O24A0_T     crg_sre2   ;             // 0xCC63_0008
    SCRG_CTRL_SRE_CRG_SRE3_O24A0_T     crg_sre3   ;             // 0xCC63_000C
}SCRG_CTRL_SRE_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_SRE_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

