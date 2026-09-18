#ifndef _SCRG_CTRL_CVI_REG_H_
#define _SCRG_CTRL_CVI_REG_H_

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
    0xE_0000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CVI_CRG_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CVI_CRG_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_cvd27_clk_gate_en     :  1,    //      2
    reg_cvd54_clk_gate_en     :  1,    //      3
    reg_cvi0_clk_gate_en      :  1,    //      4
    reg_cvi1_clk_gate_en      :  1,    //      5
    reg_cvi2_clk_gate_en      :  1,    //      6
    reg_cvi3_clk_gate_en      :  1,    //      7
    reg_cvi4_clk_gate_en      :  1,    //      8
    reg_de_clk_gate_en        :  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_CVI_CRG_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_000C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_cvd27_n      :  1,    //      3
    reg_soft_rst_cvd54_n      :  1,    //      4
    reg_soft_rst_cvd_mif_n    :  1,    //      5
    reg_soft_rst_cvd_vbi_n    :  1,    //      6
    reg_soft_rst_cvi0_n       :  1,    //      7
    reg_soft_rst_cvi1_n       :  1,    //      8
    reg_soft_rst_cvi2_n       :  1,    //      9
    reg_soft_rst_cvi3_n       :  1,    //     10
    reg_soft_rst_cvi4_n       :  1,    //     11
    reg_soft_rst_de_n         :  1,    //     12
    reg_soft_rst_f_cvi_0_de_bnd_n: 1,    //   13
    reg_soft_rst_f_cvi_1_de_bnd_n: 1,    //   14
    reg_soft_rst_f_cvi_2_de_bnd_n: 1,    //   15
    reg_soft_rst_f_cvi_3_de_bnd_n: 1,    //   16
    reg_soft_rst_f_cvi_4_de_bnd_n: 1,    //   17
    reg_soft_rst_f_dsc_1_cvi0_bnd_n: 1,    //  18
    reg_soft_rst_f_dsc_2_cvi0_bnd_n: 1,    //  19
    reg_soft_rst_f_hdmi_0_cvi0_bnd_n: 1,    //  20
    reg_soft_rst_f_hdmi_1_cvi1_bnd_n: 1,    //  21
    reg_soft_rst_f_hdmi_2_cvi2_bnd_n: 1,    //  22
    reg_soft_rst_f_hdmi_3_cvi3_bnd_n: 1,    //  23
    reg_soft_rst_p_cvi_0_axi_bnd_n: 1,    //  24
    reg_soft_rst_x_cvi_0_axi_bnd_n: 1,    //  25
    reg_soft_rst_x_cvi_0_axi_n:  1,    //     26
                              :  5;    //  31:27 reserved
}SCRG_CTRL_CVI_CRG_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi0_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_cvi1_clk_sel          :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_cvi2_clk_sel          :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_cvi3_clk_sel          :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_cvi4_clk_sel          :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SCRG_CTRL_CVI_CRG_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0014    crg_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CVI_CRG_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0018    crg_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CVI_CRG_CVI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_001C    crg_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_CVI_CRG_CVI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVI_CRG_CVI00_O22A0_T          crg_cvi00  ;             // 0xE_0000
    SCRG_CTRL_CVI_CRG_CVI01_O22A0_T          crg_cvi01  ;             // 0xE_0004
    SCRG_CTRL_CVI_CRG_CVI02_O22A0_T          crg_cvi02  ;             // 0xE_0008
    SCRG_CTRL_CVI_CRG_CVI03_O22A0_T          crg_cvi03  ;             // 0xE_000C
    SCRG_CTRL_CVI_CRG_CVI04_O22A0_T          crg_cvi04  ;             // 0xE_0010
    SCRG_CTRL_CVI_CRG_CVI05_O22A0_T          crg_cvi05  ;             // 0xE_0014
    SCRG_CTRL_CVI_CRG_CVI06_O22A0_T          crg_cvi06  ;             // 0xE_0018
    SCRG_CTRL_CVI_CRG_CVI07_O22A0_T          crg_cvi07  ;             // 0xE_001C
}SCRG_CTRL_CVI_REG_O22A0_T;
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

#define SCRG_CTRL_CVI_CRG_CVI00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_CVI_CRG_CVI01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_CVI_CRG_CVI02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_CVI_CRG_CVI03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_CVI_CRG_CVI04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_CVI_CRG_CVI05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_CVI_CRG_CVI06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_CVI_CRG_CVI07_O22A0_T_OFF                       (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xE_0000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CVI_CRG_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CVI_CRG_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_cvd27_clk_gate_en: 1;    //     2
    UINT32 reg_cvd54_clk_gate_en: 1;    //     3
    UINT32 reg_cvi0_clk_gate_en: 1;    //      4
    UINT32 reg_cvi1_clk_gate_en: 1;    //      5
    UINT32 reg_cvi2_clk_gate_en: 1;    //      6
    UINT32 reg_cvi3_clk_gate_en: 1;    //      7
    UINT32 reg_cvi4_clk_gate_en: 1;    //      8
    UINT32 reg_de_clk_gate_en :  1;    //      9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_000C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_cvd27_n: 1;    //      3
    UINT32 reg_soft_rst_cvd54_n: 1;    //      4
    UINT32 reg_soft_rst_cvd_mif_n: 1;    //    5
    UINT32 reg_soft_rst_cvd_vbi_n: 1;    //    6
    UINT32 reg_soft_rst_cvi0_n:  1;    //      7
    UINT32 reg_soft_rst_cvi1_n:  1;    //      8
    UINT32 reg_soft_rst_cvi2_n:  1;    //      9
    UINT32 reg_soft_rst_cvi3_n:  1;    //     10
    UINT32 reg_soft_rst_cvi4_n:  1;    //     11
    UINT32 reg_soft_rst_de_n  :  1;    //     12
    UINT32 reg_soft_rst_f_cvi_0_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_cvi_1_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_cvi_2_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_f_cvi_3_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_f_cvi_4_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_f_dsc_1_cvi0_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_f_dsc_2_cvi0_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_f_hdmi_0_cvi0_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_f_hdmi_1_cvi1_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_f_hdmi_2_cvi2_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_f_hdmi_3_cvi3_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_cvi_0_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_x_cvi_0_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_x_cvi_0_axi_n: 1;    //  26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi0_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_cvi1_clk_sel   :  3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_cvi2_clk_sel   :  3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_cvi3_clk_sel   :  3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_cvi4_clk_sel   :  3;    //  18:16
    UINT32 resvd04            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0014    crg_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_0018    crg_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xE_001C    crg_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVI_CRG_CVI00_O22A0_T          crg_cvi00  ;             // 0xE_0000
    SCRG_CTRL_CVI_CRG_CVI01_O22A0_T          crg_cvi01  ;             // 0xE_0004
    SCRG_CTRL_CVI_CRG_CVI02_O22A0_T          crg_cvi02  ;             // 0xE_0008
    SCRG_CTRL_CVI_CRG_CVI03_O22A0_T          crg_cvi03  ;             // 0xE_000C
    SCRG_CTRL_CVI_CRG_CVI04_O22A0_T          crg_cvi04  ;             // 0xE_0010
    SCRG_CTRL_CVI_CRG_CVI05_O22A0_T          crg_cvi05  ;             // 0xE_0014
    SCRG_CTRL_CVI_CRG_CVI06_O22A0_T          crg_cvi06  ;             // 0xE_0018
    SCRG_CTRL_CVI_CRG_CVI07_O22A0_T          crg_cvi07  ;             // 0xE_001C
}SCRG_CTRL_CVI_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

