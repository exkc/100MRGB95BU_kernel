#ifndef _SCRG_CTRL_VSD_REG_H_
#define _SCRG_CTRL_VSD_REG_H_

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
    0x15_0000    crg_vsd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0004    crg_vsd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VSD_CRG_VSD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0008    crg_vsd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
    reg_det_clk_gate_en       :  1,    //      3
    reg_disp_clk_gate_en      :  1,    //      4
    reg_disp_mem_clk_gate_en  :  1,    //      5
    reg_spip_clk_gate_en      :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VSD_CRG_VSD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_000C    crg_vsd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_det_n        :  1,    //      3
    reg_soft_rst_disp_n       :  1,    //      4
    reg_soft_rst_f_cco_6_disp_bnd_n: 1,    //  5
    reg_soft_rst_f_imx_16_apb_bnd_n: 1,    //  6
    reg_soft_rst_f_me0_1_de_bnd_n: 1,    //    7
    reg_soft_rst_f_vsd_0_de_bnd_n: 1,    //    8
    reg_soft_rst_f_vsd_1_spip_bnd_n: 1,    //  9
    reg_soft_rst_f_vsd_2_disp_bnd_n: 1,    //  10
    reg_soft_rst_h_cco_1_disp_bnd_n: 1,    //  11
    reg_soft_rst_h_cco_2_disp_bnd_n: 1,    //  12
    reg_soft_rst_h_cco_3_disp_bnd_n: 1,    //  13
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //   14
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //   15
    reg_soft_rst_h_gsc_2_de_bnd_n: 1,    //   16
    reg_soft_rst_h_gsc_3_de_bnd_n: 1,    //   17
    reg_soft_rst_h_gsc_4_de_bnd_n: 1,    //   18
    reg_soft_rst_h_gsc_5_de_bnd_n: 1,    //   19
    reg_soft_rst_spip_n       :  1,    //     20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_VSD_CRG_VSD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0010    crg_vsd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_spip_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_disp_mem_clk_sel      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_det_clk_sel           :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_disp_clk_sel          :  3,    //  14:12
                              : 17;    //  31:15 reserved
}SCRG_CTRL_VSD_CRG_VSD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0014    crg_vsd05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VSD_CRG_VSD05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0018    crg_vsd06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VSD_CRG_VSD06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_001C    crg_vsd07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VSD_CRG_VSD07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD00_O22A0_T          crg_vsd00  ;             // 0x15_0000
    SCRG_CTRL_VSD_CRG_VSD01_O22A0_T          crg_vsd01  ;             // 0x15_0004
    SCRG_CTRL_VSD_CRG_VSD02_O22A0_T          crg_vsd02  ;             // 0x15_0008
    SCRG_CTRL_VSD_CRG_VSD03_O22A0_T          crg_vsd03  ;             // 0x15_000C
    SCRG_CTRL_VSD_CRG_VSD04_O22A0_T          crg_vsd04  ;             // 0x15_0010
    SCRG_CTRL_VSD_CRG_VSD05_O22A0_T          crg_vsd05  ;             // 0x15_0014
    SCRG_CTRL_VSD_CRG_VSD06_O22A0_T          crg_vsd06  ;             // 0x15_0018
    SCRG_CTRL_VSD_CRG_VSD07_O22A0_T          crg_vsd07  ;             // 0x15_001C
}SCRG_CTRL_VSD_REG_O22A0_T;
/* 8 regs */

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

#define SCRG_CTRL_VSD_CRG_VSD00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VSD_CRG_VSD01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VSD_CRG_VSD02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VSD_CRG_VSD03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VSD_CRG_VSD04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VSD_CRG_VSD05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VSD_CRG_VSD06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VSD_CRG_VSD07_O22A0_T_OFF                       (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0x15_0000    crg_vsd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0004    crg_vsd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VSD_CRG_VSD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0008    crg_vsd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 reg_det_clk_gate_en:  1;    //      3
    UINT32 reg_disp_clk_gate_en: 1;    //      4
    UINT32 reg_disp_mem_clk_gate_en: 1;    //  5
    UINT32 reg_spip_clk_gate_en: 1;    //      6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_000C    crg_vsd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_det_n :  1;    //      3
    UINT32 reg_soft_rst_disp_n:  1;    //      4
    UINT32 reg_soft_rst_f_cco_6_disp_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_imx_16_apb_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_me0_1_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_vsd_0_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_vsd_1_spip_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_vsd_2_disp_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_cco_1_disp_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_cco_2_disp_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_cco_3_disp_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_2_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_gsc_3_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_gsc_4_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_gsc_5_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_spip_n:  1;    //     20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0010    crg_vsd04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_spip_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_disp_mem_clk_sel: 3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_det_clk_sel    :  3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_disp_clk_sel   :  3;    //  14:12
    UINT32 resvd03            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0014    crg_vsd05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_0018    crg_vsd06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x15_001C    crg_vsd07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VSD_CRG_VSD07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VSD_CRG_VSD00_O22A0_T          crg_vsd00  ;             // 0x15_0000
    SCRG_CTRL_VSD_CRG_VSD01_O22A0_T          crg_vsd01  ;             // 0x15_0004
    SCRG_CTRL_VSD_CRG_VSD02_O22A0_T          crg_vsd02  ;             // 0x15_0008
    SCRG_CTRL_VSD_CRG_VSD03_O22A0_T          crg_vsd03  ;             // 0x15_000C
    SCRG_CTRL_VSD_CRG_VSD04_O22A0_T          crg_vsd04  ;             // 0x15_0010
    SCRG_CTRL_VSD_CRG_VSD05_O22A0_T          crg_vsd05  ;             // 0x15_0014
    SCRG_CTRL_VSD_CRG_VSD06_O22A0_T          crg_vsd06  ;             // 0x15_0018
    SCRG_CTRL_VSD_CRG_VSD07_O22A0_T          crg_vsd07  ;             // 0x15_001C
}SCRG_CTRL_VSD_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/


