#ifndef _SCRG_CTRL_ND_M23A0_REG_H_
#define _SCRG_CTRL_ND_M23A0_REG_H_

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
    0xCC5C_0000    crg_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND_CRG_ND00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_0004    crg_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND_CRG_ND01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_0008    crg_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd_apb_clk_gate_en    :  1,    //      0
    reg_nd_axi_clk_gate_en    :  1,    //      1
    reg_nd_de_clk_gate_en     :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ND_CRG_ND02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_000C    crg_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_imx_2_de_bnd_n: 1,    //    3
    reg_soft_rst_h_imx_3_de_bnd_n: 1,    //    4
    reg_soft_rst_h_nd_0_de_bnd_n: 1,    //     5
    reg_soft_rst_h_nd_1_de_bnd_n: 1,    //     6
    reg_soft_rst_h_nd_2_de_bnd_n: 1,    //     7
    reg_soft_rst_h_nd_3_de_bnd_n: 1,    //     8
    reg_soft_rst_p_nd_0_axi_bnd_n: 1,    //    9
    reg_soft_rst_x_nd_0_axi_bnd_n: 1,    //   10
    reg_soft_rst_x_nd_0_axi_n :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_ND_CRG_ND03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND_CRG_ND00_M23A0_T      crg_nd00   ;             // 0xCC5C_0000
    SCRG_CTRL_ND_CRG_ND01_M23A0_T      crg_nd01   ;             // 0xCC5C_0004
    SCRG_CTRL_ND_CRG_ND02_M23A0_T      crg_nd02   ;             // 0xCC5C_0008
    SCRG_CTRL_ND_CRG_ND03_M23A0_T      crg_nd03   ;             // 0xCC5C_000C
}SCRG_CTRL_ND_REG_M23A0_T;
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

#define SCRG_CTRL_ND_CRG_ND00_M23A0_T_OFF                   (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND_CRG_ND01_M23A0_T_OFF                   (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND_CRG_ND02_M23A0_T_OFF                   (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND_CRG_ND03_M23A0_T_OFF                   (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC5C_0000    crg_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND_CRG_ND00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_0004    crg_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND_CRG_ND01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_0008    crg_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nd_apb_clk_gate_en: 1;    //    0
    UINT32 reg_nd_axi_clk_gate_en: 1;    //    1
    UINT32 reg_nd_de_clk_gate_en: 1;    //     2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ND_CRG_ND02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_000C    crg_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_imx_2_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_imx_3_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_nd_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_nd_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_x_nd_0_axi_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_ND_CRG_ND03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND_CRG_ND00_M23A0_T      crg_nd00   ;             // 0xCC5C_0000
    SCRG_CTRL_ND_CRG_ND01_M23A0_T      crg_nd01   ;             // 0xCC5C_0004
    SCRG_CTRL_ND_CRG_ND02_M23A0_T      crg_nd02   ;             // 0xCC5C_0008
    SCRG_CTRL_ND_CRG_ND03_M23A0_T      crg_nd03   ;             // 0xCC5C_000C
}SCRG_CTRL_ND_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

