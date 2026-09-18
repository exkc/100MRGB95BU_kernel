#ifndef _SCRG_CTRL_AUD_REG_H_
#define _SCRG_CTRL_AUD_REG_H_

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
    0x5D_0000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0008    crg_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_aad_clk_gate_en   :  1,    //      0
    reg_aud_ahb_clk_gate_en   :  1,    //      1
    reg_aud_apb_clk_gate_en   :  1,    //      2
    reg_aud_arc_clk_gate_en   :  1,    //      3
    reg_aud_dsp0_clk_gate_en  :  1,    //      4
    reg_aud_dsp1_clk_gate_en  :  1,    //      5
    reg_aud_dsp2_clk_gate_en  :  1,    //      6
    reg_aud_dsp3_clk_gate_en  :  1,    //      7
    reg_aud_hdp_clk_gate_en   :  1,    //      8
    reg_aud_hmr1spdifclk_gate_en: 1,    //     9
    reg_aud_hmr2spdifclk_gate_en: 1,    //    10
    reg_aud_hmr3spdifclk_gate_en: 1,    //    11
    reg_aud_hmr4spdifclk_gate_en: 1,    //    12
    reg_aud_main_clk_gate_en  :  1,    //     13
    reg_aud_micom_clk_gate_en :  1,    //     14
    reg_aud_pdm_clk_gate_en   :  1,    //     15
    reg_aud_spdif_clk_gate_en :  1,    //     16
    reg_aud_te0_clk_gate_en   :  1,    //     17
    reg_aud_te1_clk_gate_en   :  1,    //     18
    reg_aud_te2_clk_gate_en   :  1,    //     19
                              : 12;    //  31:20 reserved
}SCRG_CTRL_AUD_CRG_AUD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_000C    crg_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_axi_apb_ipw_n: 1,    //   0
    reg_soft_rst_apb_n        :  1,    //      1
    reg_soft_rst_aud_ahb_n    :  1,    //      2
    reg_soft_rst_aud_fs_n     :  1,    //      3
    reg_soft_rst_aud_hw_n     :  1,    //      4
    reg_soft_rst_aud_micom_n  :  1,    //      5
    reg_soft_rst_aud_pdm_n    :  1,    //      6
    reg_soft_rst_e_te_4_aud_hw_bnd_n: 1,    //  7
    reg_soft_rst_e_te_5_aud_hw_bnd_n: 1,    //  8
    reg_soft_rst_f_te_0_apb_bnd_n: 1,    //    9
    reg_soft_rst_f_te_1_apb_bnd_n: 1,    //   10
    reg_soft_rst_f_te_2_apb_bnd_n: 1,    //   11
    reg_soft_rst_f_te_3_apb_bnd_n: 1,    //   12
    reg_soft_rst_lne_apb_ipw_n:  1,    //     13
    reg_soft_rst_p_aud_1_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_aud_2_axi_bnd_n: 1,    //  15
    reg_soft_rst_te_apb_ipw_n :  1,    //     16
    reg_soft_rst_x_aud_1_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_aud_1_axi_n:  1,    //     18
    reg_soft_rst_x_aud_2_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_aud_2_axi_n:  1,    //     20
    reg_soft_rst_x_micom_0_axi_n: 1,    //    21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_AUD_CRG_AUD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0010    crg_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_apb_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aud_micom_clk_sel     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_aud_te0_clk_sel       :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_aud_te1_clk_sel       :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_aud_te2_clk_sel       :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_aud_dsp0_clk_sel      :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_aud_dsp1_clk_sel      :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_aud_dsp2_clk_sel      :  2,    //  29:28
                              :  2;    //  31:30 reserved
}SCRG_CTRL_AUD_CRG_AUD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0014    crg_aud05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp3_clk_sel      :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_AUD_CRG_AUD05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0018    crg_aud06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_ahb_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_001C    crg_aud07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_apb_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0020    crg_aud08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp0_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0024    crg_aud09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp1_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0028    crg_aud10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp2_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_002C    crg_aud11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp3_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0030    crg_aud12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_micom_clk_skip_ctrl: 9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0034    crg_aud13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_te0_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0038    crg_aud14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_te1_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_003C    crg_aud15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_te2_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_AUD_CRG_AUD15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD00_O22A0_T          crg_aud00  ;             // 0x5D_0000
    SCRG_CTRL_AUD_CRG_AUD01_O22A0_T          crg_aud01  ;             // 0x5D_0004
    SCRG_CTRL_AUD_CRG_AUD02_O22A0_T          crg_aud02  ;             // 0x5D_0008
    SCRG_CTRL_AUD_CRG_AUD03_O22A0_T          crg_aud03  ;             // 0x5D_000C
    SCRG_CTRL_AUD_CRG_AUD04_O22A0_T          crg_aud04  ;             // 0x5D_0010
    SCRG_CTRL_AUD_CRG_AUD05_O22A0_T          crg_aud05  ;             // 0x5D_0014
    SCRG_CTRL_AUD_CRG_AUD06_O22A0_T          crg_aud06  ;             // 0x5D_0018
    SCRG_CTRL_AUD_CRG_AUD07_O22A0_T          crg_aud07  ;             // 0x5D_001C
    SCRG_CTRL_AUD_CRG_AUD08_O22A0_T          crg_aud08  ;             // 0x5D_0020
    SCRG_CTRL_AUD_CRG_AUD09_O22A0_T          crg_aud09  ;             // 0x5D_0024
    SCRG_CTRL_AUD_CRG_AUD10_O22A0_T          crg_aud10  ;             // 0x5D_0028
    SCRG_CTRL_AUD_CRG_AUD11_O22A0_T          crg_aud11  ;             // 0x5D_002C
    SCRG_CTRL_AUD_CRG_AUD12_O22A0_T          crg_aud12  ;             // 0x5D_0030
    SCRG_CTRL_AUD_CRG_AUD13_O22A0_T          crg_aud13  ;             // 0x5D_0034
    SCRG_CTRL_AUD_CRG_AUD14_O22A0_T          crg_aud14  ;             // 0x5D_0038
    SCRG_CTRL_AUD_CRG_AUD15_O22A0_T          crg_aud15  ;             // 0x5D_003C
}SCRG_CTRL_AUD_REG_O22A0_T;
/* 16 regs */

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

#define SCRG_CTRL_AUD_CRG_AUD00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_AUD_CRG_AUD01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_AUD_CRG_AUD02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_AUD_CRG_AUD03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_AUD_CRG_AUD04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_AUD_CRG_AUD05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_AUD_CRG_AUD06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_AUD_CRG_AUD07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_AUD_CRG_AUD08_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_AUD_CRG_AUD09_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_AUD_CRG_AUD10_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_AUD_CRG_AUD11_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define SCRG_CTRL_AUD_CRG_AUD12_O22A0_T_OFF                       (BASEADDRESS+0x0030)
#define SCRG_CTRL_AUD_CRG_AUD13_O22A0_T_OFF                       (BASEADDRESS+0x0034)
#define SCRG_CTRL_AUD_CRG_AUD14_O22A0_T_OFF                       (BASEADDRESS+0x0038)
#define SCRG_CTRL_AUD_CRG_AUD15_O22A0_T_OFF                       (BASEADDRESS+0x003C)

/*-----------------------------------------------------------------------------------------
    0x5D_0000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0008    crg_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_aad_clk_gate_en: 1;    //   0
    UINT32 reg_aud_ahb_clk_gate_en: 1;    //   1
    UINT32 reg_aud_apb_clk_gate_en: 1;    //   2
    UINT32 reg_aud_arc_clk_gate_en: 1;    //   3
    UINT32 reg_aud_dsp0_clk_gate_en: 1;    //  4
    UINT32 reg_aud_dsp1_clk_gate_en: 1;    //  5
    UINT32 reg_aud_dsp2_clk_gate_en: 1;    //  6
    UINT32 reg_aud_dsp3_clk_gate_en: 1;    //  7
    UINT32 reg_aud_hdp_clk_gate_en: 1;    //   8
    UINT32 reg_aud_hmr1spdifclk_gate_en: 1;    //  9
    UINT32 reg_aud_hmr2spdifclk_gate_en: 1;    //  10
    UINT32 reg_aud_hmr3spdifclk_gate_en: 1;    //  11
    UINT32 reg_aud_hmr4spdifclk_gate_en: 1;    //  12
    UINT32 reg_aud_main_clk_gate_en: 1;    //  13
    UINT32 reg_aud_micom_clk_gate_en: 1;    //  14
    UINT32 reg_aud_pdm_clk_gate_en: 1;    //  15
    UINT32 reg_aud_spdif_clk_gate_en: 1;    //  16
    UINT32 reg_aud_te0_clk_gate_en: 1;    //  17
    UINT32 reg_aud_te1_clk_gate_en: 1;    //  18
    UINT32 reg_aud_te2_clk_gate_en: 1;    //  19
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_000C    crg_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_axi_apb_ipw_n: 1;    //  0
    UINT32 reg_soft_rst_apb_n :  1;    //      1
    UINT32 reg_soft_rst_aud_ahb_n: 1;    //    2
    UINT32 reg_soft_rst_aud_fs_n: 1;    //     3
    UINT32 reg_soft_rst_aud_hw_n: 1;    //     4
    UINT32 reg_soft_rst_aud_micom_n: 1;    //  5
    UINT32 reg_soft_rst_aud_pdm_n: 1;    //    6
    UINT32 reg_soft_rst_e_te_4_aud_hw_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_e_te_5_aud_hw_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_0_apb_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_te_1_apb_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_te_2_apb_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_te_3_apb_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_lne_apb_ipw_n: 1;    //  13
    UINT32 reg_soft_rst_p_aud_1_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_aud_2_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_te_apb_ipw_n: 1;    //  16
    UINT32 reg_soft_rst_x_aud_1_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_aud_1_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_aud_2_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_aud_2_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_micom_0_axi_n: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0010    crg_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_apb_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_aud_micom_clk_sel: 1;    //     4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_aud_te0_clk_sel:  2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_aud_te1_clk_sel:  2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_aud_te2_clk_sel:  2;    //  17:16
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 reg_aud_dsp0_clk_sel: 2;    //  21:20
    UINT32 resvd05            :  2;    //  23:22 reserved
    UINT32 reg_aud_dsp1_clk_sel: 2;    //  25:24
    UINT32 resvd06            :  2;    //  27:26 reserved
    UINT32 reg_aud_dsp2_clk_sel: 2;    //  29:28
    UINT32 resvd07            :  2;    //  31:30 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0014    crg_aud05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp3_clk_sel: 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0018    crg_aud06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_ahb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_001C    crg_aud07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_apb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0020    crg_aud08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0024    crg_aud09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0028    crg_aud10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp2_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_002C    crg_aud11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp3_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0030    crg_aud12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_micom_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0034    crg_aud13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_te0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_0038    crg_aud14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_te1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5D_003C    crg_aud15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_te2_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD00_O22A0_T          crg_aud00  ;             // 0x5D_0000
    SCRG_CTRL_AUD_CRG_AUD01_O22A0_T          crg_aud01  ;             // 0x5D_0004
    SCRG_CTRL_AUD_CRG_AUD02_O22A0_T          crg_aud02  ;             // 0x5D_0008
    SCRG_CTRL_AUD_CRG_AUD03_O22A0_T          crg_aud03  ;             // 0x5D_000C
    SCRG_CTRL_AUD_CRG_AUD04_O22A0_T          crg_aud04  ;             // 0x5D_0010
    SCRG_CTRL_AUD_CRG_AUD05_O22A0_T          crg_aud05  ;             // 0x5D_0014
    SCRG_CTRL_AUD_CRG_AUD06_O22A0_T          crg_aud06  ;             // 0x5D_0018
    SCRG_CTRL_AUD_CRG_AUD07_O22A0_T          crg_aud07  ;             // 0x5D_001C
    SCRG_CTRL_AUD_CRG_AUD08_O22A0_T          crg_aud08  ;             // 0x5D_0020
    SCRG_CTRL_AUD_CRG_AUD09_O22A0_T          crg_aud09  ;             // 0x5D_0024
    SCRG_CTRL_AUD_CRG_AUD10_O22A0_T          crg_aud10  ;             // 0x5D_0028
    SCRG_CTRL_AUD_CRG_AUD11_O22A0_T          crg_aud11  ;             // 0x5D_002C
    SCRG_CTRL_AUD_CRG_AUD12_O22A0_T          crg_aud12  ;             // 0x5D_0030
    SCRG_CTRL_AUD_CRG_AUD13_O22A0_T          crg_aud13  ;             // 0x5D_0034
    SCRG_CTRL_AUD_CRG_AUD14_O22A0_T          crg_aud14  ;             // 0x5D_0038
    SCRG_CTRL_AUD_CRG_AUD15_O22A0_T          crg_aud15  ;             // 0x5D_003C
}SCRG_CTRL_AUD_REG_O22A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

