#ifndef _SCRG_CTRL_CCO_REG_H_
#define _SCRG_CTRL_CCO_REG_H_

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
    0x6_0000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
    reg_det_clk_gate_en       :  1,    //      3
    reg_disp_clk_gate_en      :  1,    //      4
    reg_disp_dsc_clk_gate_en  :  1,    //      5
    reg_disp_osd_clk_gate_en  :  1,    //      6
    reg_fms_clk_gate_en       :  1,    //      7
    reg_gcf_clk_gate_en       :  1,    //      8
    reg_sosd_clk_gate_en      :  1,    //      9
    reg_spip_clk_gate_en      :  1,    //     10
    reg_vx1_clk_gate_en       :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_CCO_CRG_CCO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_000C    crg_cco03 ''
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
    reg_soft_rst_f_cco_4_sosd_bnd_n: 1,    //  7
    reg_soft_rst_f_cco_5_de_bnd_n: 1,    //    8
    reg_soft_rst_f_cco_6_disp_bnd_n: 1,    //  9
    reg_soft_rst_f_cco_7_disp_dsc_bnd_n: 1,    //  10
    reg_soft_rst_f_fms_0_fms_bnd_n: 1,    //  11
    reg_soft_rst_f_led_1_disp_dsc_bnd_n: 1,    //  12
    reg_soft_rst_f_vsd_1_spip_bnd_n: 1,    //  13
    reg_soft_rst_f_vsd_2_disp_bnd_n: 1,    //  14
    reg_soft_rst_fms_n        :  1,    //     15
    reg_soft_rst_gcf_n        :  1,    //     16
    reg_soft_rst_h_cco_0_de_bnd_n: 1,    //   17
    reg_soft_rst_h_cco_1_disp_bnd_n: 1,    //  18
    reg_soft_rst_h_cco_2_disp_bnd_n: 1,    //  19
    reg_soft_rst_h_cco_3_disp_bnd_n: 1,    //  20
    reg_soft_rst_h_cco_8_vx1_bnd_n: 1,    //  21
    reg_soft_rst_p_cco_0_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_cco_1_axi_bnd_n: 1,    //  23
    reg_soft_rst_sosd_n       :  1,    //     24
    reg_soft_rst_spip_n       :  1,    //     25
    reg_soft_rst_vx1_n        :  1,    //     26
    reg_soft_rst_x_cco_0_axi_bnd_n: 1,    //  27
    reg_soft_rst_x_cco_0_axi_n:  1,    //     28
    reg_soft_rst_x_cco_1_axi_bnd_n: 1,    //  29
    reg_soft_rst_x_cco_1_axi_n:  1,    //     30
                              :  1;    //  31:31 reserved
}SCRG_CTRL_CCO_CRG_CCO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_spip_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_det_clk_sel           :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_disp_clk_sel          :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_disp_dsc_clk_sel      :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_disp_osd_clk_sel      :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_gcf_clk_sel           :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_sosd_clk_sel          :  3,    //  26:24
                              :  5;    //  31:27 reserved
}SCRG_CTRL_CCO_CRG_CCO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0014    crg_cco05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CCO_CRG_CCO05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0018    crg_cco06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CCO_CRG_CCO06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_001C    crg_cco07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CCO_CRG_CCO07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0020    crg_cco08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CCO_CRG_CCO08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO00_O22A0_T          crg_cco00  ;             // 0x6_0000
    SCRG_CTRL_CCO_CRG_CCO01_O22A0_T          crg_cco01  ;             // 0x6_0004
    SCRG_CTRL_CCO_CRG_CCO02_O22A0_T          crg_cco02  ;             // 0x6_0008
    SCRG_CTRL_CCO_CRG_CCO03_O22A0_T          crg_cco03  ;             // 0x6_000C
    SCRG_CTRL_CCO_CRG_CCO04_O22A0_T          crg_cco04  ;             // 0x6_0010
    SCRG_CTRL_CCO_CRG_CCO05_O22A0_T          crg_cco05  ;             // 0x6_0014
    SCRG_CTRL_CCO_CRG_CCO06_O22A0_T          crg_cco06  ;             // 0x6_0018
    SCRG_CTRL_CCO_CRG_CCO07_O22A0_T          crg_cco07  ;             // 0x6_001C
    SCRG_CTRL_CCO_CRG_CCO08_O22A0_T          crg_cco08  ;             // 0x6_0020
}SCRG_CTRL_CCO_REG_O22A0_T;
/* 9 regs */

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

#define SCRG_CTRL_CCO_CRG_CCO00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_CCO_CRG_CCO01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_CCO_CRG_CCO02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_CCO_CRG_CCO03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_CCO_CRG_CCO04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_CCO_CRG_CCO05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_CCO_CRG_CCO06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_CCO_CRG_CCO07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_CCO_CRG_CCO08_O22A0_T_OFF                       (BASEADDRESS+0x0020)

/*-----------------------------------------------------------------------------------------
    0x6_0000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 reg_det_clk_gate_en:  1;    //      3
    UINT32 reg_disp_clk_gate_en: 1;    //      4
    UINT32 reg_disp_dsc_clk_gate_en: 1;    //  5
    UINT32 reg_disp_osd_clk_gate_en: 1;    //  6
    UINT32 reg_fms_clk_gate_en:  1;    //      7
    UINT32 reg_gcf_clk_gate_en:  1;    //      8
    UINT32 reg_sosd_clk_gate_en: 1;    //      9
    UINT32 reg_spip_clk_gate_en: 1;    //     10
    UINT32 reg_vx1_clk_gate_en:  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_000C    crg_cco03 ''
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
    UINT32 reg_soft_rst_f_cco_4_sosd_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_cco_5_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_cco_6_disp_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_cco_7_disp_dsc_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_fms_0_fms_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_led_1_disp_dsc_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_vsd_1_spip_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_vsd_2_disp_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_fms_n :  1;    //     15
    UINT32 reg_soft_rst_gcf_n :  1;    //     16
    UINT32 reg_soft_rst_h_cco_0_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_cco_1_disp_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_cco_2_disp_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_cco_3_disp_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_h_cco_8_vx1_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_cco_1_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_sosd_n:  1;    //     24
    UINT32 reg_soft_rst_spip_n:  1;    //     25
    UINT32 reg_soft_rst_vx1_n :  1;    //     26
    UINT32 reg_soft_rst_x_cco_0_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_cco_1_axi_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_x_cco_1_axi_n: 1;    //  30
    UINT32 resvd00            :  1;    //  31:31 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_spip_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_det_clk_sel    :  3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_disp_clk_sel   :  3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_disp_dsc_clk_sel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_disp_osd_clk_sel: 3;    //  18:16
    UINT32 resvd04            :  1;    //     19 reserved
    UINT32 reg_gcf_clk_sel    :  3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_sosd_clk_sel   :  3;    //  26:24
    UINT32 resvd06            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0014    crg_cco05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0018    crg_cco06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_001C    crg_cco07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x6_0020    crg_cco08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO00_O22A0_T          crg_cco00  ;             // 0x6_0000
    SCRG_CTRL_CCO_CRG_CCO01_O22A0_T          crg_cco01  ;             // 0x6_0004
    SCRG_CTRL_CCO_CRG_CCO02_O22A0_T          crg_cco02  ;             // 0x6_0008
    SCRG_CTRL_CCO_CRG_CCO03_O22A0_T          crg_cco03  ;             // 0x6_000C
    SCRG_CTRL_CCO_CRG_CCO04_O22A0_T          crg_cco04  ;             // 0x6_0010
    SCRG_CTRL_CCO_CRG_CCO05_O22A0_T          crg_cco05  ;             // 0x6_0014
    SCRG_CTRL_CCO_CRG_CCO06_O22A0_T          crg_cco06  ;             // 0x6_0018
    SCRG_CTRL_CCO_CRG_CCO07_O22A0_T          crg_cco07  ;             // 0x6_001C
    SCRG_CTRL_CCO_CRG_CCO08_O22A0_T          crg_cco08  ;             // 0x6_0020
}SCRG_CTRL_CCO_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

