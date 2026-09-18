#ifndef _SCRG_CTRL_VSD_M23A0_REG_H_
#define _SCRG_CTRL_VSD_M23A0_REG_H_

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
    0xCC50_0000    crg_vsd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0004    crg_vsd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0008    crg_vsd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_apb_clk_gate_en   :  1,    //      0
    reg_vsd_de_clk_gate_en    :  1,    //      1
    reg_vsd_det_clk_gate_en   :  1,    //      2
    reg_vsd_disp_clk_gate_en  :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_VSD_CRG_VSD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_000C    crg_vsd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_det_n        :  1,    //      2
    reg_soft_rst_disp_n       :  1,    //      3
    reg_soft_rst_f_cco_2_disp_bnd_n: 1,    //  4
    reg_soft_rst_f_imx_4_apb_bnd_n: 1,    //   5
    reg_soft_rst_f_me_0_de_bnd_n: 1,    //     6
    reg_soft_rst_f_vsd_0_de_bnd_n: 1,    //    7
    reg_soft_rst_f_vsd_1_disp_bnd_n: 1,    //  8
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //    9
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //   10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_VSD_CRG_VSD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0010    crg_vsd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_det_clk_sel       :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_vsd_disp_clk_sel      :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}SCRG_CTRL_VSD_CRG_VSD04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD00_M23A0_T    crg_vsd00  ;             // 0xCC50_0000
    SCRG_CTRL_VSD_CRG_VSD01_M23A0_T    crg_vsd01  ;             // 0xCC50_0004
    SCRG_CTRL_VSD_CRG_VSD02_M23A0_T    crg_vsd02  ;             // 0xCC50_0008
    SCRG_CTRL_VSD_CRG_VSD03_M23A0_T    crg_vsd03  ;             // 0xCC50_000C
    SCRG_CTRL_VSD_CRG_VSD04_M23A0_T    crg_vsd04  ;             // 0xCC50_0010
}SCRG_CTRL_VSD_REG_M23A0_T;
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

#define SCRG_CTRL_VSD_CRG_VSD00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_VSD_CRG_VSD01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_VSD_CRG_VSD02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_VSD_CRG_VSD03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_VSD_CRG_VSD04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC50_0000    crg_vsd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0004    crg_vsd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0008    crg_vsd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_apb_clk_gate_en: 1;    //   0
    UINT32 reg_vsd_de_clk_gate_en: 1;    //    1
    UINT32 reg_vsd_det_clk_gate_en: 1;    //   2
    UINT32 reg_vsd_disp_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_000C    crg_vsd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_det_n :  1;    //      2
    UINT32 reg_soft_rst_disp_n:  1;    //      3
    UINT32 reg_soft_rst_f_cco_2_disp_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_imx_4_apb_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_me_0_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_vsd_0_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_vsd_1_disp_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_0010    crg_vsd04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_det_clk_sel:  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_vsd_disp_clk_sel: 2;    //   5: 4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD00_M23A0_T    crg_vsd00  ;             // 0xCC50_0000
    SCRG_CTRL_VSD_CRG_VSD01_M23A0_T    crg_vsd01  ;             // 0xCC50_0004
    SCRG_CTRL_VSD_CRG_VSD02_M23A0_T    crg_vsd02  ;             // 0xCC50_0008
    SCRG_CTRL_VSD_CRG_VSD03_M23A0_T    crg_vsd03  ;             // 0xCC50_000C
    SCRG_CTRL_VSD_CRG_VSD04_M23A0_T    crg_vsd04  ;             // 0xCC50_0010
}SCRG_CTRL_VSD_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

