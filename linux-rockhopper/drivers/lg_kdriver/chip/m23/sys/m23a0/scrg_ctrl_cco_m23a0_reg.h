#ifndef _SCRG_CTRL_CCO_M23A0_REG_H_
#define _SCRG_CTRL_CCO_M23A0_REG_H_

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
    0xCC4C_0000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco_apb_clk_gate_en   :  1,    //      0
    reg_cco_axi_clk_gate_en   :  1,    //      1
    reg_cco_de_clk_gate_en    :  1,    //      2
    reg_cco_det_clk_gate_en   :  1,    //      3
    reg_cco_disp_clk_gate_en  :  1,    //      4
    reg_cco_disp_dsc_clk_gate_en: 1,    //     5
    reg_cco_disp_osd_clk_gate_en: 1,    //     6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_CCO_CRG_CCO02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_000C    crg_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_det_n        :  1,    //      3
    reg_soft_rst_disp_dsc_n   :  1,    //      4
    reg_soft_rst_disp_n       :  1,    //      5
    reg_soft_rst_disp_osd_n   :  1,    //      6
    reg_soft_rst_f_cco_0_disp_dsc_bnd_n: 1,    //  7
    reg_soft_rst_f_cco_1_de_bnd_n: 1,    //    8
    reg_soft_rst_f_cco_2_disp_bnd_n: 1,    //  9
    reg_soft_rst_f_led_1_disp_dsc_bnd_n: 1,    //  10
    reg_soft_rst_f_vsd_1_disp_bnd_n: 1,    //  11
    reg_soft_rst_p_cco_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_cco_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_cco_0_axi_n:  1,    //     14
                              : 17;    //  31:15 reserved
}SCRG_CTRL_CCO_CRG_CCO03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco_det_clk_sel       :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_cco_disp_clk_sel      :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_cco_disp_dsc_clk_sel  :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_cco_disp_osd_clk_sel  :  2,    //  13:12
                              : 18;    //  31:14 reserved
}SCRG_CTRL_CCO_CRG_CCO04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO00_M23A0_T    crg_cco00  ;             // 0xCC4C_0000
    SCRG_CTRL_CCO_CRG_CCO01_M23A0_T    crg_cco01  ;             // 0xCC4C_0004
    SCRG_CTRL_CCO_CRG_CCO02_M23A0_T    crg_cco02  ;             // 0xCC4C_0008
    SCRG_CTRL_CCO_CRG_CCO03_M23A0_T    crg_cco03  ;             // 0xCC4C_000C
    SCRG_CTRL_CCO_CRG_CCO04_M23A0_T    crg_cco04  ;             // 0xCC4C_0010
}SCRG_CTRL_CCO_REG_M23A0_T;
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

#define SCRG_CTRL_CCO_CRG_CCO00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_CCO_CRG_CCO01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_CCO_CRG_CCO02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_CCO_CRG_CCO03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_CCO_CRG_CCO04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC4C_0000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cco_apb_clk_gate_en: 1;    //   0
    UINT32 reg_cco_axi_clk_gate_en: 1;    //   1
    UINT32 reg_cco_de_clk_gate_en: 1;    //    2
    UINT32 reg_cco_det_clk_gate_en: 1;    //   3
    UINT32 reg_cco_disp_clk_gate_en: 1;    //  4
    UINT32 reg_cco_disp_dsc_clk_gate_en: 1;    //  5
    UINT32 reg_cco_disp_osd_clk_gate_en: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_000C    crg_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_det_n :  1;    //      3
    UINT32 reg_soft_rst_disp_dsc_n: 1;    //   4
    UINT32 reg_soft_rst_disp_n:  1;    //      5
    UINT32 reg_soft_rst_disp_osd_n: 1;    //   6
    UINT32 reg_soft_rst_f_cco_0_disp_dsc_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_cco_1_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_cco_2_disp_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_led_1_disp_dsc_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_vsd_1_disp_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_cco_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_0010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cco_det_clk_sel:  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_cco_disp_clk_sel: 2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_cco_disp_dsc_clk_sel: 2;    //  9:8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_cco_disp_osd_clk_sel: 2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO00_M23A0_T    crg_cco00  ;             // 0xCC4C_0000
    SCRG_CTRL_CCO_CRG_CCO01_M23A0_T    crg_cco01  ;             // 0xCC4C_0004
    SCRG_CTRL_CCO_CRG_CCO02_M23A0_T    crg_cco02  ;             // 0xCC4C_0008
    SCRG_CTRL_CCO_CRG_CCO03_M23A0_T    crg_cco03  ;             // 0xCC4C_000C
    SCRG_CTRL_CCO_CRG_CCO04_M23A0_T    crg_cco04  ;             // 0xCC4C_0010
}SCRG_CTRL_CCO_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

