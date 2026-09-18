#ifndef _SCRG_CTRL_HDR_REG_O26A0_H_
#define _SCRG_CTRL_HDR_REG_O26A0_H_

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
    0xCC24_0000    crg_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0004    crg_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0008    crg_hdr002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_h_imx_0__de_clk_gate_en: 1,    //  0
    reg_adaprx_h_imx_11__de_clk_gate_en: 1,    //  1
    reg_adaprx_h_imx_12__de_clk_gate_en: 1,    //  2
    reg_adaprx_h_imx_13__de_clk_gate_en: 1,    //  3
    reg_adaprx_h_imx_14__de_clk_gate_en: 1,    //  4
    reg_adaprx_h_imx_1__de_clk_gate_en: 1,    //  5
    reg_adaprx_h_imx_2__de_clk_gate_en: 1,    //  6
    reg_adaprx_h_imx_3__de_clk_gate_en: 1,    //  7
    reg_adaprx_h_imx_4__de_clk_gate_en: 1,    //  8
    reg_adaprx_h_imx_5__de_clk_gate_en: 1,    //  9
    reg_adaptx_h_hdr_0__de_clk_gate_en: 1,    //  10
    reg_adaptx_h_hdr_1__de_clk_gate_en: 1,    //  11
    reg_adaptx_h_hdr_2__de_clk_gate_en: 1,    //  12
    reg_adaptx_h_hdr_3__de_clk_gate_en: 1,    //  13
    reg_adaptx_h_hdr_4__de_clk_gate_en: 1,    //  14
    reg_adaptx_h_hdr_5__de_clk_gate_en: 1,    //  15
    reg_apb_clk_gate_en       :  1,    //     16
    reg_de_clk_gate_en        :  1,    //     17
    reg_hdr_clk_gate_en       :  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_HDR_CRG_HDR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_000C    crg_hdr003 ''
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
    reg_soft_rst_h_imx_11_de_bnd_n: 1,    //   9
    reg_soft_rst_h_imx_12_de_bnd_n: 1,    //  10
    reg_soft_rst_h_imx_13_de_bnd_n: 1,    //  11
    reg_soft_rst_h_imx_14_de_bnd_n: 1,    //  12
    reg_soft_rst_h_imx_1_de_bnd_n: 1,    //   13
    reg_soft_rst_h_imx_2_de_bnd_n: 1,    //   14
    reg_soft_rst_h_imx_3_de_bnd_n: 1,    //   15
    reg_soft_rst_h_imx_4_de_bnd_n: 1,    //   16
    reg_soft_rst_h_imx_5_de_bnd_n: 1,    //   17
    reg_soft_rst_hdr_n        :  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_HDR_CRG_HDR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0010    crg_hdr004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_clk_sel           :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_HDR_CRG_HDR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR000_O26A0_T    crg_hdr000;             // 0xCC24_0000
    SCRG_CTRL_HDR_CRG_HDR001_O26A0_T    crg_hdr001;             // 0xCC24_0004
    SCRG_CTRL_HDR_CRG_HDR002_O26A0_T    crg_hdr002;             // 0xCC24_0008
    SCRG_CTRL_HDR_CRG_HDR003_O26A0_T    crg_hdr003;             // 0xCC24_000C
    SCRG_CTRL_HDR_CRG_HDR004_O26A0_T    crg_hdr004;             // 0xCC24_0010
}SCRG_CTRL_HDR_REG_O26A0_T;
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

#define SCRG_CTRL_HDR_CRG_HDR000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDR_CRG_HDR001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDR_CRG_HDR002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDR_CRG_HDR003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDR_CRG_HDR004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC24_0000    crg_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0004    crg_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0008    crg_hdr002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_h_imx_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_h_imx_11__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_imx_12__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_imx_13__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_imx_14__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_imx_1__de_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_imx_2__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_h_imx_3__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaprx_h_imx_4__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaprx_h_imx_5__de_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_h_hdr_0__de_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_h_hdr_1__de_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_h_hdr_2__de_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_h_hdr_3__de_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_h_hdr_4__de_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_h_hdr_5__de_clk_gate_en: 1;    //  15
    UINT32 reg_apb_clk_gate_en:  1;    //     16
    UINT32 reg_de_clk_gate_en :  1;    //     17
    UINT32 reg_hdr_clk_gate_en:  1;    //     18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_000C    crg_hdr003 ''
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
    UINT32 reg_soft_rst_h_imx_11_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_imx_12_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_imx_13_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_imx_14_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_imx_1_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_imx_2_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_imx_3_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_imx_4_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_imx_5_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_hdr_n :  1;    //     18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC24_0010    crg_hdr004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_clk_sel    :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR000_O26A0_T    crg_hdr000;             // 0xCC24_0000
    SCRG_CTRL_HDR_CRG_HDR001_O26A0_T    crg_hdr001;             // 0xCC24_0004
    SCRG_CTRL_HDR_CRG_HDR002_O26A0_T    crg_hdr002;             // 0xCC24_0008
    SCRG_CTRL_HDR_CRG_HDR003_O26A0_T    crg_hdr003;             // 0xCC24_000C
    SCRG_CTRL_HDR_CRG_HDR004_O26A0_T    crg_hdr004;             // 0xCC24_0010
}SCRG_CTRL_HDR_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_HDR_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

