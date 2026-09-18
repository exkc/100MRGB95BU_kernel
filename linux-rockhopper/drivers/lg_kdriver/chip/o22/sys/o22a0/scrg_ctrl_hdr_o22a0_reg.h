#ifndef _SCRG_CTRL_HDR_REG_H_
#define _SCRG_CTRL_HDR_REG_H_

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
    0x27_0000    crg_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0004    crg_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0008    crg_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_de_clk_gate_en        :  1,    //      1
    reg_hdr_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_HDR_CRG_HDR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_000C    crg_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_h_hdr_0_de_bnd_n: 1,    //    2
    reg_soft_rst_h_hdr_1_de_bnd_n: 1,    //    3
    reg_soft_rst_h_hdr_2_de_bnd_n: 1,    //    4
    reg_soft_rst_h_hdr_3_de_bnd_n: 1,    //    5
    reg_soft_rst_h_hdr_4_de_bnd_n: 1,    //    6
    reg_soft_rst_h_hdr_5_de_bnd_n: 1,    //    7
    reg_soft_rst_h_imx_0_de_bnd_n: 1,    //    8
    reg_soft_rst_h_imx_1_de_bnd_n: 1,    //    9
    reg_soft_rst_h_imx_2_de_bnd_n: 1,    //   10
    reg_soft_rst_h_imx_3_de_bnd_n: 1,    //   11
    reg_soft_rst_h_imx_4_de_bnd_n: 1,    //   12
    reg_soft_rst_h_imx_5_de_bnd_n: 1,    //   13
    reg_soft_rst_h_imx_6_de_bnd_n: 1,    //   14
    reg_soft_rst_h_imx_7_de_bnd_n: 1,    //   15
    reg_soft_rst_h_imx_8_de_bnd_n: 1,    //   16
    reg_soft_rst_h_imx_9_de_bnd_n: 1,    //   17
    reg_soft_rst_hdr_n        :  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_HDR_CRG_HDR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0010    crg_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_clk_sel           :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_HDR_CRG_HDR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0014    crg_hdr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HDR_CRG_HDR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0018    crg_hdr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HDR_CRG_HDR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR00_O22A0_T          crg_hdr00  ;             // 0x27_0000
    SCRG_CTRL_HDR_CRG_HDR01_O22A0_T          crg_hdr01  ;             // 0x27_0004
    SCRG_CTRL_HDR_CRG_HDR02_O22A0_T          crg_hdr02  ;             // 0x27_0008
    SCRG_CTRL_HDR_CRG_HDR03_O22A0_T          crg_hdr03  ;             // 0x27_000C
    SCRG_CTRL_HDR_CRG_HDR04_O22A0_T          crg_hdr04  ;             // 0x27_0010
    SCRG_CTRL_HDR_CRG_HDR05_O22A0_T          crg_hdr05  ;             // 0x27_0014
    SCRG_CTRL_HDR_CRG_HDR06_O22A0_T          crg_hdr06  ;             // 0x27_0018
}SCRG_CTRL_HDR_REG_O22A0_T;
/* 7 regs */

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

#define SCRG_CTRL_HDR_CRG_HDR00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDR_CRG_HDR01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDR_CRG_HDR02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDR_CRG_HDR03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDR_CRG_HDR04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_HDR_CRG_HDR05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_HDR_CRG_HDR06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x27_0000    crg_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0004    crg_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0008    crg_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_de_clk_gate_en :  1;    //      1
    UINT32 reg_hdr_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_000C    crg_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_h_hdr_0_de_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_hdr_1_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_hdr_2_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_hdr_3_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_hdr_4_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_hdr_5_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_imx_0_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_imx_1_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_imx_2_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_imx_3_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_imx_4_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_imx_5_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_imx_6_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_imx_7_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_imx_8_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_imx_9_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_hdr_n :  1;    //     18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0010    crg_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_clk_sel    :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0014    crg_hdr05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x27_0018    crg_hdr06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR00_O22A0_T          crg_hdr00  ;             // 0x27_0000
    SCRG_CTRL_HDR_CRG_HDR01_O22A0_T          crg_hdr01  ;             // 0x27_0004
    SCRG_CTRL_HDR_CRG_HDR02_O22A0_T          crg_hdr02  ;             // 0x27_0008
    SCRG_CTRL_HDR_CRG_HDR03_O22A0_T          crg_hdr03  ;             // 0x27_000C
    SCRG_CTRL_HDR_CRG_HDR04_O22A0_T          crg_hdr04  ;             // 0x27_0010
    SCRG_CTRL_HDR_CRG_HDR05_O22A0_T          crg_hdr05  ;             // 0x27_0014
    SCRG_CTRL_HDR_CRG_HDR06_O22A0_T          crg_hdr06  ;             // 0x27_0018
}SCRG_CTRL_HDR_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

