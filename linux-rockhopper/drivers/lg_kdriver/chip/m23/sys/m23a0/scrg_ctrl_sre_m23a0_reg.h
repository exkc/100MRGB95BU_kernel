#ifndef _SCRG_CTRL_SRE_M23A0_REG_H_
#define _SCRG_CTRL_SRE_M23A0_REG_H_

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
    0xCC58_0000    crg_sre00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_0004    crg_sre01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SRE_CRG_SRE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_0008    crg_sre02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_apb_clk_gate_en   :  1,    //      0
    reg_sre_axi_clk_gate_en   :  1,    //      1
    reg_sre_de_clk_gate_en    :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_SRE_CRG_SRE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_000C    crg_sre03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_nd_2_de_bnd_n: 1,    //     3
    reg_soft_rst_h_nd_3_de_bnd_n: 1,    //     4
    reg_soft_rst_h_sre_2_de_bnd_n: 1,    //    5
    reg_soft_rst_h_sre_3_de_bnd_n: 1,    //    6
    reg_soft_rst_p_sre_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_sre_0_axi_bnd_n: 1,    //   8
    reg_soft_rst_x_sre_0_axi_n:  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_SRE_CRG_SRE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE00_M23A0_T    crg_sre00  ;             // 0xCC58_0000
    SCRG_CTRL_SRE_CRG_SRE01_M23A0_T    crg_sre01  ;             // 0xCC58_0004
    SCRG_CTRL_SRE_CRG_SRE02_M23A0_T    crg_sre02  ;             // 0xCC58_0008
    SCRG_CTRL_SRE_CRG_SRE03_M23A0_T    crg_sre03  ;             // 0xCC58_000C
}SCRG_CTRL_SRE_REG_M23A0_T;
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

#define SCRG_CTRL_SRE_CRG_SRE00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_SRE_CRG_SRE01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_SRE_CRG_SRE02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_SRE_CRG_SRE03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC58_0000    crg_sre00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_0004    crg_sre01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SRE_CRG_SRE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_0008    crg_sre02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre_apb_clk_gate_en: 1;    //   0
    UINT32 reg_sre_axi_clk_gate_en: 1;    //   1
    UINT32 reg_sre_de_clk_gate_en: 1;    //    2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC58_000C    crg_sre03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_nd_2_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_nd_3_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_sre_2_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_sre_3_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_sre_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_sre_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_sre_0_axi_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_SRE_CRG_SRE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRE_CRG_SRE00_M23A0_T    crg_sre00  ;             // 0xCC58_0000
    SCRG_CTRL_SRE_CRG_SRE01_M23A0_T    crg_sre01  ;             // 0xCC58_0004
    SCRG_CTRL_SRE_CRG_SRE02_M23A0_T    crg_sre02  ;             // 0xCC58_0008
    SCRG_CTRL_SRE_CRG_SRE03_M23A0_T    crg_sre03  ;             // 0xCC58_000C
}SCRG_CTRL_SRE_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

