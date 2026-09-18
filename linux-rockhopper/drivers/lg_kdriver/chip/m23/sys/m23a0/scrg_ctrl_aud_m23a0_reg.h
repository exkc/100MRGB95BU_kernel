#ifndef _SCRG_CTRL_AUD_M23A0_REG_H_
#define _SCRG_CTRL_AUD_M23A0_REG_H_

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
    0xCED1_0000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_0004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_0008    crg_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_aad_clk_gate_en   :  1,    //      0
    reg_aud_apb_clk_gate_en   :  1,    //      1
    reg_aud_arc_clk_gate_en   :  1,    //      2
    reg_aud_dsp_clk_gate_en   :  1,    //      3
    reg_aud_hdp_clk_gate_en   :  1,    //      4
    reg_aud_hmr1spdif_clk_gate_en: 1,    //    5
    reg_aud_hmr2spdif_clk_gate_en: 1,    //    6
    reg_aud_hmr3spdif_clk_gate_en: 1,    //    7
    reg_aud_hmr4spdif_clk_gate_en: 1,    //    8
    reg_aud_main_clk_gate_en  :  1,    //      9
    reg_aud_spdif_clk_gate_en :  1,    //     10
    reg_aud_te_clk_gate_en    :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_AUD_CRG_AUD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_000C    crg_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_aud_fs_n     :  1,    //      1
    reg_soft_rst_aud_hw_n     :  1,    //      2
    reg_soft_rst_e_te_4_aud_hw_bnd_n: 1,    //  3
    reg_soft_rst_e_te_5_aud_hw_bnd_n: 1,    //  4
    reg_soft_rst_f_te_0_apb_bnd_n: 1,    //    5
    reg_soft_rst_f_te_1_apb_bnd_n: 1,    //    6
    reg_soft_rst_f_te_2_apb_bnd_n: 1,    //    7
    reg_soft_rst_f_te_3_apb_bnd_n: 1,    //    8
    reg_soft_rst_p_aud_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_aud_1_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_aud_2_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_cpu_2_axi_bnd_n: 1,    //  12
    reg_soft_rst_p_pdm_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_aud_0_axi_bnd_n: 1,    //  14
    reg_soft_rst_x_aud_0_axi_n:  1,    //     15
    reg_soft_rst_x_aud_1_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_aud_1_axi_n:  1,    //     17
    reg_soft_rst_x_aud_2_axi_bnd_n: 1,    //  18
    reg_soft_rst_x_aud_2_axi_n:  1,    //     19
    reg_soft_rst_x_cpu_2_axi_n:  1,    //     20
    reg_soft_rst_x_pdm_0_axi_n:  1,    //     21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_AUD_CRG_AUD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD00_M23A0_T    crg_aud00  ;             // 0xCED1_0000
    SCRG_CTRL_AUD_CRG_AUD01_M23A0_T    crg_aud01  ;             // 0xCED1_0004
    SCRG_CTRL_AUD_CRG_AUD02_M23A0_T    crg_aud02  ;             // 0xCED1_0008
    SCRG_CTRL_AUD_CRG_AUD03_M23A0_T    crg_aud03  ;             // 0xCED1_000C
}SCRG_CTRL_AUD_REG_M23A0_T;
/* 4 regs */

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

#define SCRG_CTRL_AUD_CRG_AUD00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_AUD_CRG_AUD01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_AUD_CRG_AUD02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_AUD_CRG_AUD03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCED1_0000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_0004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_0008    crg_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_aad_clk_gate_en: 1;    //   0
    UINT32 reg_aud_apb_clk_gate_en: 1;    //   1
    UINT32 reg_aud_arc_clk_gate_en: 1;    //   2
    UINT32 reg_aud_dsp_clk_gate_en: 1;    //   3
    UINT32 reg_aud_hdp_clk_gate_en: 1;    //   4
    UINT32 reg_aud_hmr1spdif_clk_gate_en: 1;    //  5
    UINT32 reg_aud_hmr2spdif_clk_gate_en: 1;    //  6
    UINT32 reg_aud_hmr3spdif_clk_gate_en: 1;    //  7
    UINT32 reg_aud_hmr4spdif_clk_gate_en: 1;    //  8
    UINT32 reg_aud_main_clk_gate_en: 1;    //  9
    UINT32 reg_aud_spdif_clk_gate_en: 1;    //  10
    UINT32 reg_aud_te_clk_gate_en: 1;    //   11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED1_000C    crg_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_aud_fs_n: 1;    //     1
    UINT32 reg_soft_rst_aud_hw_n: 1;    //     2
    UINT32 reg_soft_rst_e_te_4_aud_hw_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_e_te_5_aud_hw_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_te_0_apb_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_te_1_apb_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_te_2_apb_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_te_3_apb_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_aud_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_aud_1_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_aud_2_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_cpu_2_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_pdm_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_aud_0_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_aud_1_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_aud_1_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_aud_2_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_x_aud_2_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_cpu_2_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_pdm_0_axi_n: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD00_M23A0_T    crg_aud00  ;             // 0xCED1_0000
    SCRG_CTRL_AUD_CRG_AUD01_M23A0_T    crg_aud01  ;             // 0xCED1_0004
    SCRG_CTRL_AUD_CRG_AUD02_M23A0_T    crg_aud02  ;             // 0xCED1_0008
    SCRG_CTRL_AUD_CRG_AUD03_M23A0_T    crg_aud03  ;             // 0xCED1_000C
}SCRG_CTRL_AUD_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

