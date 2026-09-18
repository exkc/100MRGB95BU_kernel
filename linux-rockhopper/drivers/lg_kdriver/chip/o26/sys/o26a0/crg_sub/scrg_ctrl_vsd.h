#ifndef _SCRG_CTRL_VSD_REG_O26A0_H_
#define _SCRG_CTRL_VSD_REG_O26A0_H_

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
    0xCC96_0000    crg_vsd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_vsd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_vsd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_cco_8__disp_clk_gate_en: 1,    //  0
    reg_adaprx_f_imx_10__apb_clk_gate_en: 1,    //  1
    reg_adaprx_h_cco_10__de_clk_gate_en: 1,    //  2
    reg_adaprx_h_cco_1__obs_clk_gate_en: 1,    //  3
    reg_adaprx_h_cco_2__obs_clk_gate_en: 1,    //  4
    reg_adaprx_h_cco_3__obs_clk_gate_en: 1,    //  5
    reg_adaprx_h_gsc_5__de_clk_gate_en: 1,    //  6
    reg_adaprx_h_gsc_6__de_clk_gate_en: 1,    //  7
    reg_adaprx_h_gsc_7__de_clk_gate_en: 1,    //  8
    reg_adaprx_h_gsc_8__de_clk_gate_en: 1,    //  9
    reg_adaprx_h_sre_7__obs_clk_gate_en: 1,    //  10
    reg_adaprx_h_sre_8__obs_clk_gate_en: 1,    //  11
    reg_adaptx_f_vsd_3__de_clk_gate_en: 1,    //  12
    reg_adaptx_f_vsd_4__de_clk_gate_en: 1,    //  13
    reg_adaptx_f_vsd_5__disp_clk_gate_en: 1,    //  14
    reg_adaptx_h_vsd_0__de_clk_gate_en: 1,    //  15
    reg_adaptx_h_vsd_1__obs_clk_gate_en: 1,    //  16
    reg_adaptx_h_vsd_2__obs_clk_gate_en: 1,    //  17
    reg_apb_clk_gate_en       :  1,    //     18
    reg_de_clk_gate_en        :  1,    //     19
    reg_det_clk_gate_en       :  1,    //     20
    reg_disp_clk_gate_en      :  1,    //     21
    reg_obs_clk_gate_en       :  1,    //     22
                              :  9;    //  31:23 reserved
}SCRG_CTRL_VSD_CRG_VSD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_vsd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_det_n        :  1,    //      2
    reg_soft_rst_disp_n       :  1,    //      3
    reg_soft_rst_f_cco_8_disp_bnd_n: 1,    //  4
    reg_soft_rst_f_imx_10_apb_bnd_n: 1,    //  5
    reg_soft_rst_f_vsd_3_de_bnd_n: 1,    //    6
    reg_soft_rst_f_vsd_4_de_bnd_n: 1,    //    7
    reg_soft_rst_f_vsd_5_disp_bnd_n: 1,    //  8
    reg_soft_rst_h_cco_10_de_bnd_n: 1,    //   9
    reg_soft_rst_h_cco_1_obs_bnd_n: 1,    //  10
    reg_soft_rst_h_cco_2_obs_bnd_n: 1,    //  11
    reg_soft_rst_h_cco_3_obs_bnd_n: 1,    //  12
    reg_soft_rst_h_gsc_5_de_bnd_n: 1,    //   13
    reg_soft_rst_h_gsc_6_de_bnd_n: 1,    //   14
    reg_soft_rst_h_gsc_7_de_bnd_n: 1,    //   15
    reg_soft_rst_h_gsc_8_de_bnd_n: 1,    //   16
    reg_soft_rst_h_sre_7_obs_bnd_n: 1,    //  17
    reg_soft_rst_h_sre_8_obs_bnd_n: 1,    //  18
    reg_soft_rst_h_vsd_0_de_bnd_n: 1,    //   19
    reg_soft_rst_h_vsd_1_obs_bnd_n: 1,    //  20
    reg_soft_rst_h_vsd_2_obs_bnd_n: 1,    //  21
    reg_soft_rst_obs_n        :  1,    //     22
                              :  9;    //  31:23 reserved
}SCRG_CTRL_VSD_CRG_VSD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0010    crg_vsd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_det_clk_sel       :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_vsd_disp_clk_sel      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_vsd_obs_clk_sel       :  3,    //  10: 8
                              : 21;    //  31:11 reserved
}SCRG_CTRL_VSD_CRG_VSD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD000_O26A0_T    crg_vsd000;             // 0xCC96_0000
    SCRG_CTRL_VSD_CRG_VSD001_O26A0_T    crg_vsd001;             // 0xCC96_0004
    SCRG_CTRL_VSD_CRG_VSD002_O26A0_T    crg_vsd002;             // 0xCC96_0008
    SCRG_CTRL_VSD_CRG_VSD003_O26A0_T    crg_vsd003;             // 0xCC96_000C
    SCRG_CTRL_VSD_CRG_VSD004_O26A0_T    crg_vsd004;             // 0xCC96_0010
}SCRG_CTRL_VSD_REG_O26A0_T;
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

#define SCRG_CTRL_VSD_CRG_VSD000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_VSD_CRG_VSD001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_VSD_CRG_VSD002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_VSD_CRG_VSD003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_VSD_CRG_VSD004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC96_0000    crg_vsd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_vsd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_vsd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_cco_8__disp_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_imx_10__apb_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_cco_10__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_cco_1__obs_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_cco_2__obs_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_cco_3__obs_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_gsc_5__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_h_gsc_6__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaprx_h_gsc_7__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaprx_h_gsc_8__de_clk_gate_en: 1;    //  9
    UINT32 reg_adaprx_h_sre_7__obs_clk_gate_en: 1;    //  10
    UINT32 reg_adaprx_h_sre_8__obs_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_f_vsd_3__de_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_f_vsd_4__de_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_f_vsd_5__disp_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_h_vsd_0__de_clk_gate_en: 1;    //  15
    UINT32 reg_adaptx_h_vsd_1__obs_clk_gate_en: 1;    //  16
    UINT32 reg_adaptx_h_vsd_2__obs_clk_gate_en: 1;    //  17
    UINT32 reg_apb_clk_gate_en:  1;    //     18
    UINT32 reg_de_clk_gate_en :  1;    //     19
    UINT32 reg_det_clk_gate_en:  1;    //     20
    UINT32 reg_disp_clk_gate_en: 1;    //     21
    UINT32 reg_obs_clk_gate_en:  1;    //     22
    UINT32 resvd00            :  9;    //  31:23 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_vsd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_det_n :  1;    //      2
    UINT32 reg_soft_rst_disp_n:  1;    //      3
    UINT32 reg_soft_rst_f_cco_8_disp_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_imx_10_apb_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_vsd_3_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_vsd_4_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_vsd_5_disp_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_cco_10_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_cco_1_obs_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_cco_2_obs_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_cco_3_obs_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_gsc_5_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_6_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_7_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_8_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_sre_7_obs_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_sre_8_obs_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_vsd_0_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_vsd_1_obs_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_h_vsd_2_obs_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_obs_n :  1;    //     22
    UINT32 resvd00            :  9;    //  31:23 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0010    crg_vsd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_det_clk_sel:  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_vsd_disp_clk_sel: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_vsd_obs_clk_sel:  3;    //  10: 8
    UINT32 resvd02            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD000_O26A0_T    crg_vsd000;             // 0xCC96_0000
    SCRG_CTRL_VSD_CRG_VSD001_O26A0_T    crg_vsd001;             // 0xCC96_0004
    SCRG_CTRL_VSD_CRG_VSD002_O26A0_T    crg_vsd002;             // 0xCC96_0008
    SCRG_CTRL_VSD_CRG_VSD003_O26A0_T    crg_vsd003;             // 0xCC96_000C
    SCRG_CTRL_VSD_CRG_VSD004_O26A0_T    crg_vsd004;             // 0xCC96_0010
}SCRG_CTRL_VSD_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_VSD_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

