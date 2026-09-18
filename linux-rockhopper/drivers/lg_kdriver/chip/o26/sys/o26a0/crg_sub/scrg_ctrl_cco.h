#ifndef _SCRG_CTRL_CCO_REG_O26A0_H_
#define _SCRG_CTRL_CCO_REG_O26A0_H_

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
    0xCC89_0000    crg_cco000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0004    crg_cco001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0008    crg_cco002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_fms_0__fms_clk_gate_en: 1,    //  0
    reg_adaprx_f_gsc_10__de_clk_gate_en: 1,    //  1
    reg_adaprx_f_led_0__disp_clk_gate_en: 1,    //  2
    reg_adaprx_f_led_2__disp_clk_gate_en: 1,    //  3
    reg_adaprx_f_vsd_3__de_clk_gate_en: 1,    //  4
    reg_adaprx_f_vsd_5__disp_clk_gate_en: 1,    //  5
    reg_adaprx_h_gsc_0__de_clk_gate_en: 1,    //  6
    reg_adaprx_h_vsd_0__de_clk_gate_en: 1,    //  7
    reg_adaptx_f_cco_5__de_clk_gate_en: 1,    //  8
    reg_adaptx_f_cco_6__disp_clk_gate_en: 1,    //  9
    reg_adaptx_f_cco_7__de_clk_gate_en: 1,    //  10
    reg_adaptx_f_cco_8__disp_clk_gate_en: 1,    //  11
    reg_adaptx_f_cco_9__disp_clk_gate_en: 1,    //  12
    reg_adaptx_h_cco_0__de_clk_gate_en: 1,    //  13
    reg_adaptx_h_cco_10__de_clk_gate_en: 1,    //  14
    reg_adaptx_h_cco_1__disp_clk_gate_en: 1,    //  15
    reg_adaptx_h_cco_2__disp_clk_gate_en: 1,    //  16
    reg_adaptx_h_cco_3__disp_clk_gate_en: 1,    //  17
    reg_adaptx_x_cco_0__axi_clk_gate_en: 1,    //  18
    reg_apb_clk_gate_en       :  1,    //     19
    reg_axi_clk_gate_en       :  1,    //     20
    reg_bosd_clk_gate_en      :  1,    //     21
    reg_de_clk_gate_en        :  1,    //     22
    reg_disp_clk_gate_en      :  1,    //     23
    reg_disp_osd_clk_gate_en  :  1,    //     24
    reg_fms_clk_gate_en       :  1,    //     25
    reg_gcf_clk_gate_en       :  1,    //     26
                              :  5;    //  31:27 reserved
}SCRG_CTRL_CCO_CRG_CCO002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_000C    crg_cco003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_bosd_n       :  1,    //      2
    reg_soft_rst_de_n         :  1,    //      3
    reg_soft_rst_disp_n       :  1,    //      4
    reg_soft_rst_disp_osd_n   :  1,    //      5
    reg_soft_rst_f_cco_5_de_bnd_n: 1,    //    6
    reg_soft_rst_f_cco_6_disp_bnd_n: 1,    //  7
    reg_soft_rst_f_cco_7_de_bnd_n: 1,    //    8
    reg_soft_rst_f_cco_8_disp_bnd_n: 1,    //  9
    reg_soft_rst_f_cco_9_disp_bnd_n: 1,    //  10
    reg_soft_rst_f_fms_0_fms_bnd_n: 1,    //  11
    reg_soft_rst_f_gsc_10_de_bnd_n: 1,    //  12
    reg_soft_rst_f_led_0_disp_bnd_n: 1,    //  13
    reg_soft_rst_f_led_2_disp_bnd_n: 1,    //  14
    reg_soft_rst_f_vsd_3_de_bnd_n: 1,    //   15
    reg_soft_rst_f_vsd_5_disp_bnd_n: 1,    //  16
    reg_soft_rst_fms_n        :  1,    //     17
    reg_soft_rst_gcf_n        :  1,    //     18
    reg_soft_rst_h_cco_0_de_bnd_n: 1,    //   19
    reg_soft_rst_h_cco_10_de_bnd_n: 1,    //  20
    reg_soft_rst_h_cco_1_disp_bnd_n: 1,    //  21
    reg_soft_rst_h_cco_2_disp_bnd_n: 1,    //  22
    reg_soft_rst_h_cco_3_disp_bnd_n: 1,    //  23
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //   24
    reg_soft_rst_h_vsd_0_de_bnd_n: 1,    //   25
    reg_soft_rst_p_cco_0_axi_bnd_n: 1,    //  26
    reg_soft_rst_x_cco_0_axi_n:  1,    //     27
                              :  4;    //  31:28 reserved
}SCRG_CTRL_CCO_CRG_CCO003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0010    crg_cco004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bosd_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_cco_disp_clk_sel      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_cco_disp_osd_clk_sel  :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_cco_gcf_clk_sel       :  3,    //  14:12
                              : 17;    //  31:15 reserved
}SCRG_CTRL_CCO_CRG_CCO004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO000_O26A0_T    crg_cco000;             // 0xCC89_0000
    SCRG_CTRL_CCO_CRG_CCO001_O26A0_T    crg_cco001;             // 0xCC89_0004
    SCRG_CTRL_CCO_CRG_CCO002_O26A0_T    crg_cco002;             // 0xCC89_0008
    SCRG_CTRL_CCO_CRG_CCO003_O26A0_T    crg_cco003;             // 0xCC89_000C
    SCRG_CTRL_CCO_CRG_CCO004_O26A0_T    crg_cco004;             // 0xCC89_0010
}SCRG_CTRL_CCO_REG_O26A0_T;
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

#define SCRG_CTRL_CCO_CRG_CCO000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_CCO_CRG_CCO001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_CCO_CRG_CCO002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_CCO_CRG_CCO003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_CCO_CRG_CCO004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC89_0000    crg_cco000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0004    crg_cco001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0008    crg_cco002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_fms_0__fms_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_gsc_10__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_led_0__disp_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_f_led_2__disp_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_f_vsd_3__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_f_vsd_5__disp_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_gsc_0__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_h_vsd_0__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_f_cco_5__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_f_cco_6__disp_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_f_cco_7__de_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_f_cco_8__disp_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_f_cco_9__disp_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_h_cco_0__de_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_h_cco_10__de_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_h_cco_1__disp_clk_gate_en: 1;    //  15
    UINT32 reg_adaptx_h_cco_2__disp_clk_gate_en: 1;    //  16
    UINT32 reg_adaptx_h_cco_3__disp_clk_gate_en: 1;    //  17
    UINT32 reg_adaptx_x_cco_0__axi_clk_gate_en: 1;    //  18
    UINT32 reg_apb_clk_gate_en:  1;    //     19
    UINT32 reg_axi_clk_gate_en:  1;    //     20
    UINT32 reg_bosd_clk_gate_en: 1;    //     21
    UINT32 reg_de_clk_gate_en :  1;    //     22
    UINT32 reg_disp_clk_gate_en: 1;    //     23
    UINT32 reg_disp_osd_clk_gate_en: 1;    //  24
    UINT32 reg_fms_clk_gate_en:  1;    //     25
    UINT32 reg_gcf_clk_gate_en:  1;    //     26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_000C    crg_cco003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_bosd_n:  1;    //      2
    UINT32 reg_soft_rst_de_n  :  1;    //      3
    UINT32 reg_soft_rst_disp_n:  1;    //      4
    UINT32 reg_soft_rst_disp_osd_n: 1;    //   5
    UINT32 reg_soft_rst_f_cco_5_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_cco_6_disp_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_cco_7_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_cco_8_disp_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_cco_9_disp_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_fms_0_fms_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_gsc_10_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_led_0_disp_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_led_2_disp_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_vsd_3_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_f_vsd_5_disp_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_fms_n :  1;    //     17
    UINT32 reg_soft_rst_gcf_n :  1;    //     18
    UINT32 reg_soft_rst_h_cco_0_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_cco_10_de_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_h_cco_1_disp_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_h_cco_2_disp_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_h_cco_3_disp_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_h_vsd_0_de_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  27
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC89_0010    crg_cco004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bosd_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_cco_disp_clk_sel: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_cco_disp_osd_clk_sel: 3;    //  10:8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_cco_gcf_clk_sel:  3;    //  14:12
    UINT32 resvd03            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO000_O26A0_T    crg_cco000;             // 0xCC89_0000
    SCRG_CTRL_CCO_CRG_CCO001_O26A0_T    crg_cco001;             // 0xCC89_0004
    SCRG_CTRL_CCO_CRG_CCO002_O26A0_T    crg_cco002;             // 0xCC89_0008
    SCRG_CTRL_CCO_CRG_CCO003_O26A0_T    crg_cco003;             // 0xCC89_000C
    SCRG_CTRL_CCO_CRG_CCO004_O26A0_T    crg_cco004;             // 0xCC89_0010
}SCRG_CTRL_CCO_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_CCO_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

