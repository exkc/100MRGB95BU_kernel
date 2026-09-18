#ifndef _SCRG_CTRL_HDR_M23A0_REG_H_
#define _SCRG_CTRL_HDR_M23A0_REG_H_

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
    0xCC63_0000    crg_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0004    crg_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0008    crg_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_apb_clk_gate_en   :  1,    //      0
    reg_hdr_clk_gate_en       :  1,    //      1
    reg_hdr_de_clk_gate_en    :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_HDR_CRG_HDR02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_000C    crg_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_h_hdr_0_de_bnd_n: 1,    //    2
    reg_soft_rst_h_hdr_1_de_bnd_n: 1,    //    3
    reg_soft_rst_h_imx_5_de_bnd_n: 1,    //    4
    reg_soft_rst_h_imx_6_de_bnd_n: 1,    //    5
    reg_soft_rst_hdr_n        :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_HDR_CRG_HDR03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0010    crg_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_clk_sel           :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_HDR_CRG_HDR04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR00_M23A0_T    crg_hdr00  ;             // 0xCC63_0000
    SCRG_CTRL_HDR_CRG_HDR01_M23A0_T    crg_hdr01  ;             // 0xCC63_0004
    SCRG_CTRL_HDR_CRG_HDR02_M23A0_T    crg_hdr02  ;             // 0xCC63_0008
    SCRG_CTRL_HDR_CRG_HDR03_M23A0_T    crg_hdr03  ;             // 0xCC63_000C
    SCRG_CTRL_HDR_CRG_HDR04_M23A0_T    crg_hdr04  ;             // 0xCC63_0010
}SCRG_CTRL_HDR_REG_M23A0_T;
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

#define SCRG_CTRL_HDR_CRG_HDR00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDR_CRG_HDR01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDR_CRG_HDR02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDR_CRG_HDR03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDR_CRG_HDR04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC63_0000    crg_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0004    crg_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0008    crg_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_apb_clk_gate_en: 1;    //   0
    UINT32 reg_hdr_clk_gate_en:  1;    //      1
    UINT32 reg_hdr_de_clk_gate_en: 1;    //    2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_000C    crg_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_h_hdr_0_de_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_hdr_1_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_imx_5_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_imx_6_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_hdr_n :  1;    //      6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC63_0010    crg_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_clk_sel    :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR00_M23A0_T    crg_hdr00  ;             // 0xCC63_0000
    SCRG_CTRL_HDR_CRG_HDR01_M23A0_T    crg_hdr01  ;             // 0xCC63_0004
    SCRG_CTRL_HDR_CRG_HDR02_M23A0_T    crg_hdr02  ;             // 0xCC63_0008
    SCRG_CTRL_HDR_CRG_HDR03_M23A0_T    crg_hdr03  ;             // 0xCC63_000C
    SCRG_CTRL_HDR_CRG_HDR04_M23A0_T    crg_hdr04  ;             // 0xCC63_0010
}SCRG_CTRL_HDR_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

