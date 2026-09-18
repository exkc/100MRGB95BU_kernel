#ifndef _SCRG_CTRL_TCON_REG_O26A0_H_
#define _SCRG_CTRL_TCON_REG_O26A0_H_

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
    0xCC94_0000    crg_tcon000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0004    crg_tcon001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0008    crg_tcon002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_edptx_0__c4tx_clk_gate_en: 1,    //  0
    reg_adaprx_f_led_1__pix2_clk_gate_en: 1,    //  1
    reg_adaprx_f_led_3__pix_clk_gate_en: 1,    //  2
    reg_adaptx_f_tcon_0__pix_clk_gate_en: 1,    //  3
    reg_adaptx_f_tcon_10__pix_clk_gate_en: 1,    //  4
    reg_adaptx_f_tcon_11__pix_clk_gate_en: 1,    //  5
    reg_adaptx_f_tcon_12__pix_clk_gate_en: 1,    //  6
    reg_adaptx_f_tcon_1__pix_clk_gate_en: 1,    //  7
    reg_adaptx_f_tcon_2__pix_clk_gate_en: 1,    //  8
    reg_adaptx_f_tcon_3__pix_clk_gate_en: 1,    //  9
    reg_adaptx_f_tcon_4__pix_clk_gate_en: 1,    //  10
    reg_adaptx_f_tcon_5__pix_clk_gate_en: 1,    //  11
    reg_adaptx_f_tcon_6__pix_clk_gate_en: 1,    //  12
    reg_adaptx_f_tcon_7__pix_clk_gate_en: 1,    //  13
    reg_adaptx_f_tcon_8__pix_clk_gate_en: 1,    //  14
    reg_adaptx_f_tcon_9__pix_clk_gate_en: 1,    //  15
    reg_apb_clk_gate_en       :  1,    //     16
    reg_c4_main_clk_pix1x_gate_en: 1,    //   17
    reg_c4tx_clk_gate_en      :  1,    //     18
    reg_pix2_clk_gate_en      :  1,    //     19
    reg_pix_clk_gate_en       :  1,    //     20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_TCON_CRG_TCON002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_000C    crg_tcon003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_bist_pat_gen_c4tx_n: 1,    //  1
    reg_soft_rst_c4tx_n       :  1,    //      2
    reg_soft_rst_crc_tout_pix2_n: 1,    //     3
    reg_soft_rst_crc_vout_c4tx_n: 1,    //     4
    reg_soft_rst_f_edptx_0_c4tx_bnd_n: 1,    //  5
    reg_soft_rst_f_led_1_pix2_bnd_n: 1,    //  6
    reg_soft_rst_f_led_3_pix_bnd_n: 1,    //   7
    reg_soft_rst_f_tcon_0_pix_bnd_n: 1,    //  8
    reg_soft_rst_f_tcon_10_pix_bnd_n: 1,    //  9
    reg_soft_rst_f_tcon_11_pix_bnd_n: 1,    //  10
    reg_soft_rst_f_tcon_12_pix_bnd_n: 1,    //  11
    reg_soft_rst_f_tcon_1_pix_bnd_n: 1,    //  12
    reg_soft_rst_f_tcon_2_pix_bnd_n: 1,    //  13
    reg_soft_rst_f_tcon_3_pix_bnd_n: 1,    //  14
    reg_soft_rst_f_tcon_4_pix_bnd_n: 1,    //  15
    reg_soft_rst_f_tcon_5_pix_bnd_n: 1,    //  16
    reg_soft_rst_f_tcon_6_pix_bnd_n: 1,    //  17
    reg_soft_rst_f_tcon_7_pix_bnd_n: 1,    //  18
    reg_soft_rst_f_tcon_8_pix_bnd_n: 1,    //  19
    reg_soft_rst_f_tcon_9_pix_bnd_n: 1,    //  20
    reg_soft_rst_pix2_n       :  1,    //     21
    reg_soft_rst_pix_n        :  1,    //     22
                              :  9;    //  31:23 reserved
}SCRG_CTRL_TCON_CRG_TCON003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0010    crg_tcon004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_pix2_clk_sel          :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_pix_clk_sel           :  3,    //  10: 8
                              : 21;    //  31:11 reserved
}SCRG_CTRL_TCON_CRG_TCON004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON000_O26A0_T    crg_tcon000;          // 0xCC94_0000
    SCRG_CTRL_TCON_CRG_TCON001_O26A0_T    crg_tcon001;          // 0xCC94_0004
    SCRG_CTRL_TCON_CRG_TCON002_O26A0_T    crg_tcon002;          // 0xCC94_0008
    SCRG_CTRL_TCON_CRG_TCON003_O26A0_T    crg_tcon003;          // 0xCC94_000C
    SCRG_CTRL_TCON_CRG_TCON004_O26A0_T    crg_tcon004;          // 0xCC94_0010
}SCRG_CTRL_TCON_REG_O26A0_T;
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

#define SCRG_CTRL_TCON_CRG_TCON000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_TCON_CRG_TCON001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_TCON_CRG_TCON002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_TCON_CRG_TCON003_O26A0_T_OFF              (BASEADDRESS+0x000C)
#define SCRG_CTRL_TCON_CRG_TCON004_O26A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC94_0000    crg_tcon000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0004    crg_tcon001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0008    crg_tcon002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_edptx_0__c4tx_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_led_1__pix2_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_led_3__pix_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_f_tcon_0__pix_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_f_tcon_10__pix_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_f_tcon_11__pix_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_f_tcon_12__pix_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_f_tcon_1__pix_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_f_tcon_2__pix_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_f_tcon_3__pix_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_f_tcon_4__pix_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_f_tcon_5__pix_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_f_tcon_6__pix_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_f_tcon_7__pix_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_f_tcon_8__pix_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_f_tcon_9__pix_clk_gate_en: 1;    //  15
    UINT32 reg_apb_clk_gate_en:  1;    //     16
    UINT32 reg_c4_main_clk_pix1x_gate_en: 1;    //  17
    UINT32 reg_c4tx_clk_gate_en: 1;    //     18
    UINT32 reg_pix2_clk_gate_en: 1;    //     19
    UINT32 reg_pix_clk_gate_en:  1;    //     20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_000C    crg_tcon003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_bist_pat_gen_c4tx_n: 1;    //  1
    UINT32 reg_soft_rst_c4tx_n:  1;    //      2
    UINT32 reg_soft_rst_crc_tout_pix2_n: 1;    //  3
    UINT32 reg_soft_rst_crc_vout_c4tx_n: 1;    //  4
    UINT32 reg_soft_rst_f_edptx_0_c4tx_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_led_1_pix2_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_led_3_pix_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_tcon_0_pix_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_tcon_10_pix_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_tcon_11_pix_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_tcon_12_pix_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_tcon_1_pix_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_tcon_2_pix_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_tcon_3_pix_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_tcon_4_pix_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_f_tcon_5_pix_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_f_tcon_6_pix_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_f_tcon_7_pix_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_f_tcon_8_pix_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_f_tcon_9_pix_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_pix2_n:  1;    //     21
    UINT32 reg_soft_rst_pix_n :  1;    //     22
    UINT32 resvd00            :  9;    //  31:23 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_0010    crg_tcon004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4tx_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_pix2_clk_sel   :  3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_pix_clk_sel    :  3;    //  10: 8
    UINT32 resvd02            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON000_O26A0_T    crg_tcon000;          // 0xCC94_0000
    SCRG_CTRL_TCON_CRG_TCON001_O26A0_T    crg_tcon001;          // 0xCC94_0004
    SCRG_CTRL_TCON_CRG_TCON002_O26A0_T    crg_tcon002;          // 0xCC94_0008
    SCRG_CTRL_TCON_CRG_TCON003_O26A0_T    crg_tcon003;          // 0xCC94_000C
    SCRG_CTRL_TCON_CRG_TCON004_O26A0_T    crg_tcon004;          // 0xCC94_0010
}SCRG_CTRL_TCON_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_TCON_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

