#ifndef _SCRG_CTRL_AUD_REG_O24A0_H_
#define _SCRG_CTRL_AUD_REG_O24A0_H_

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
    0xCE44_0000    crg_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0004    crg_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0008    crg_aud2 ''
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
    reg_aud_hmr1spdif_clk_gate_en: 1,    //    9
    reg_aud_hmr2spdif_clk_gate_en: 1,    //   10
    reg_aud_hmr3spdif_clk_gate_en: 1,    //   11
    reg_aud_hmr4spdif_clk_gate_en: 1,    //   12
    reg_aud_main_clk_gate_en  :  1,    //     13
    reg_aud_pc_clk_gate_en    :  1,    //     14
    reg_aud_pdm_clk_gate_en   :  1,    //     15
    reg_aud_spdif_clk_gate_en :  1,    //     16
    reg_aud_te0_clk_gate_en   :  1,    //     17
    reg_aud_te1_clk_gate_en   :  1,    //     18
    reg_aud_te2_clk_gate_en   :  1,    //     19
                              : 12;    //  31:20 reserved
}SCRG_CTRL_AUD_CRG_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_000C    crg_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_aud_ahb_n    :  1,    //      1
    reg_soft_rst_aud_fs_n     :  1,    //      2
    reg_soft_rst_aud_hw_n     :  1,    //      3
    reg_soft_rst_aud_pdm_n    :  1,    //      4
    reg_soft_rst_e_te_4_aud_hw_bnd_n: 1,    //  5
    reg_soft_rst_e_te_5_aud_hw_bnd_n: 1,    //  6
    reg_soft_rst_f_te_0_apb_bnd_n: 1,    //    7
    reg_soft_rst_f_te_1_apb_bnd_n: 1,    //    8
    reg_soft_rst_f_te_2_apb_bnd_n: 1,    //    9
    reg_soft_rst_f_te_3_apb_bnd_n: 1,    //   10
    reg_soft_rst_p_aud_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_cpu_4_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_aud_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_aud_0_axi_n:  1,    //     14
    reg_soft_rst_x_cpu_4_axi_n:  1,    //     15
                              : 16;    //  31:16 reserved
}SCRG_CTRL_AUD_CRG_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0010    crg_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_dsp0_clk_sel      :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_aud_dsp1_clk_sel      :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_aud_dsp2_clk_sel      :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_aud_dsp3_clk_sel      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_aud_te0_clk_sel       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_aud_te1_clk_sel       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aud_te2_clk_sel       :  1,    //     24
                              :  7;    //  31:25 reserved
}SCRG_CTRL_AUD_CRG_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD0_O24A0_T     crg_aud0   ;             // 0xCE44_0000
    SCRG_CTRL_AUD_CRG_AUD1_O24A0_T     crg_aud1   ;             // 0xCE44_0004
    SCRG_CTRL_AUD_CRG_AUD2_O24A0_T     crg_aud2   ;             // 0xCE44_0008
    SCRG_CTRL_AUD_CRG_AUD3_O24A0_T     crg_aud3   ;             // 0xCE44_000C
    SCRG_CTRL_AUD_CRG_AUD4_O24A0_T     crg_aud4   ;             // 0xCE44_0010
}SCRG_CTRL_AUD_REG_O24A0_T;
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

#define SCRG_CTRL_AUD_CRG_AUD0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_AUD_CRG_AUD1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_AUD_CRG_AUD2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_AUD_CRG_AUD3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_AUD_CRG_AUD4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE44_0000    crg_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0004    crg_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0008    crg_aud2 ''
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
    UINT32 reg_aud_hmr1spdif_clk_gate_en: 1;    //  9
    UINT32 reg_aud_hmr2spdif_clk_gate_en: 1;    //  10
    UINT32 reg_aud_hmr3spdif_clk_gate_en: 1;    //  11
    UINT32 reg_aud_hmr4spdif_clk_gate_en: 1;    //  12
    UINT32 reg_aud_main_clk_gate_en: 1;    //  13
    UINT32 reg_aud_pc_clk_gate_en: 1;    //   14
    UINT32 reg_aud_pdm_clk_gate_en: 1;    //  15
    UINT32 reg_aud_spdif_clk_gate_en: 1;    //  16
    UINT32 reg_aud_te0_clk_gate_en: 1;    //  17
    UINT32 reg_aud_te1_clk_gate_en: 1;    //  18
    UINT32 reg_aud_te2_clk_gate_en: 1;    //  19
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_000C    crg_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_aud_ahb_n: 1;    //    1
    UINT32 reg_soft_rst_aud_fs_n: 1;    //     2
    UINT32 reg_soft_rst_aud_hw_n: 1;    //     3
    UINT32 reg_soft_rst_aud_pdm_n: 1;    //    4
    UINT32 reg_soft_rst_e_te_4_aud_hw_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_e_te_5_aud_hw_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_te_0_apb_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_te_1_apb_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_2_apb_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_te_3_apb_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_aud_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_cpu_4_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_aud_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_cpu_4_axi_n: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE44_0010    crg_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_dsp0_clk_sel: 2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_aud_dsp1_clk_sel: 2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_aud_dsp2_clk_sel: 2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_aud_dsp3_clk_sel: 2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_aud_te0_clk_sel:  1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_aud_te1_clk_sel:  1;    //     20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_aud_te2_clk_sel:  1;    //     24
    UINT32 resvd06            :  7;    //  31:25 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD0_O24A0_T     crg_aud0   ;             // 0xCE44_0000
    SCRG_CTRL_AUD_CRG_AUD1_O24A0_T     crg_aud1   ;             // 0xCE44_0004
    SCRG_CTRL_AUD_CRG_AUD2_O24A0_T     crg_aud2   ;             // 0xCE44_0008
    SCRG_CTRL_AUD_CRG_AUD3_O24A0_T     crg_aud3   ;             // 0xCE44_000C
    SCRG_CTRL_AUD_CRG_AUD4_O24A0_T     crg_aud4   ;             // 0xCE44_0010
}SCRG_CTRL_AUD_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_AUD_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

