#ifndef _SCRG_CTRL_VSD_REG_O24A0_H_
#define _SCRG_CTRL_VSD_REG_O24A0_H_

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
    0xCCA3_0000    crg_vsd0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0004    crg_vsd1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0008    crg_vsd2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_de_clk_gate_en        :  1,    //      1
    reg_det_clk_gate_en       :  1,    //      2
    reg_disp_clk_gate_en      :  1,    //      3
    reg_disp_mem_clk_gate_en  :  1,    //      4
    reg_spip_clk_gate_en      :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_VSD_CRG_VSD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_000C    crg_vsd3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_det_n        :  1,    //      2
    reg_soft_rst_disp_n       :  1,    //      3
    reg_soft_rst_f_cco_8_disp_bnd_n: 1,    //  4
    reg_soft_rst_f_imx_12_apb_bnd_n: 1,    //  5
    reg_soft_rst_f_vsd_1_de_bnd_n: 1,    //    6
    reg_soft_rst_f_vsd_2_disp_bnd_n: 1,    //  7
    reg_soft_rst_f_vsd_3_spip_bnd_n: 1,    //  8
    reg_soft_rst_f_vsd_4_de_bnd_n: 1,    //    9
    reg_soft_rst_h_cco_2_disp_bnd_n: 1,    //  10
    reg_soft_rst_h_cco_3_disp_bnd_n: 1,    //  11
    reg_soft_rst_h_cco_4_disp_bnd_n: 1,    //  12
    reg_soft_rst_h_cco_9_de_bnd_n: 1,    //   13
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //   14
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //   15
    reg_soft_rst_h_gsc_2_de_bnd_n: 1,    //   16
    reg_soft_rst_h_gsc_3_de_bnd_n: 1,    //   17
    reg_soft_rst_h_vsd_0_de_bnd_n: 1,    //   18
    reg_soft_rst_spip_n       :  1,    //     19
                              : 12;    //  31:20 reserved
}SCRG_CTRL_VSD_CRG_VSD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0010    crg_vsd4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_det_clk_sel       :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_vsd_disp_clk_sel      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_vsd_disp_mem_clk_sel  :  4,    //  11: 8
    reg_vsd_spip_clk_sel      :  3,    //  14:12
                              : 17;    //  31:15 reserved
}SCRG_CTRL_VSD_CRG_VSD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD0_O24A0_T     crg_vsd0   ;             // 0xCCA3_0000
    SCRG_CTRL_VSD_CRG_VSD1_O24A0_T     crg_vsd1   ;             // 0xCCA3_0004
    SCRG_CTRL_VSD_CRG_VSD2_O24A0_T     crg_vsd2   ;             // 0xCCA3_0008
    SCRG_CTRL_VSD_CRG_VSD3_O24A0_T     crg_vsd3   ;             // 0xCCA3_000C
    SCRG_CTRL_VSD_CRG_VSD4_O24A0_T     crg_vsd4   ;             // 0xCCA3_0010
}SCRG_CTRL_VSD_REG_O24A0_T;
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

#define SCRG_CTRL_VSD_CRG_VSD0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_VSD_CRG_VSD1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_VSD_CRG_VSD2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_VSD_CRG_VSD3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_VSD_CRG_VSD4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCA3_0000    crg_vsd0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0004    crg_vsd1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0008    crg_vsd2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_de_clk_gate_en :  1;    //      1
    UINT32 reg_det_clk_gate_en:  1;    //      2
    UINT32 reg_disp_clk_gate_en: 1;    //      3
    UINT32 reg_disp_mem_clk_gate_en: 1;    //  4
    UINT32 reg_spip_clk_gate_en: 1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_000C    crg_vsd3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_det_n :  1;    //      2
    UINT32 reg_soft_rst_disp_n:  1;    //      3
    UINT32 reg_soft_rst_f_cco_8_disp_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_imx_12_apb_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_vsd_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_vsd_2_disp_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_vsd_3_spip_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_vsd_4_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_cco_2_disp_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_cco_3_disp_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_cco_4_disp_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_cco_9_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_2_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_gsc_3_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_vsd_0_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_spip_n:  1;    //     19
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA3_0010    crg_vsd4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_det_clk_sel:  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_vsd_disp_clk_sel: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_vsd_disp_mem_clk_sel: 4;    //  11:8
    UINT32 reg_vsd_spip_clk_sel: 3;    //  14:12
    UINT32 resvd02            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD0_O24A0_T     crg_vsd0   ;             // 0xCCA3_0000
    SCRG_CTRL_VSD_CRG_VSD1_O24A0_T     crg_vsd1   ;             // 0xCCA3_0004
    SCRG_CTRL_VSD_CRG_VSD2_O24A0_T     crg_vsd2   ;             // 0xCCA3_0008
    SCRG_CTRL_VSD_CRG_VSD3_O24A0_T     crg_vsd3   ;             // 0xCCA3_000C
    SCRG_CTRL_VSD_CRG_VSD4_O24A0_T     crg_vsd4   ;             // 0xCCA3_0010
}SCRG_CTRL_VSD_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_VSD_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

