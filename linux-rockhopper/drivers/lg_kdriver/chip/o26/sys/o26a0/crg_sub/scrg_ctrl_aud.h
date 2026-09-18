#ifndef _SCRG_CTRL_AUD_REG_O26A0_H_
#define _SCRG_CTRL_AUD_REG_O26A0_H_

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
    0xCE7C_0000    crg_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0004    crg_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_AUD_CRG_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0008    crg_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_e_te_4__aud_te0_clk_gate_en: 1,    //  0
    reg_adaprx_e_te_5__aud_te0_clk_gate_en: 1,    //  1
    reg_adaprx_f_te_0__aud_apb_clk_gate_en: 1,    //  2
    reg_adaprx_f_te_1__aud_apb_clk_gate_en: 1,    //  3
    reg_adaprx_f_te_2__aud_apb_clk_gate_en: 1,    //  4
    reg_adaprx_f_te_3__aud_apb_clk_gate_en: 1,    //  5
    reg_adaprx_x_cpu_0__aud_te0_clk_gate_en: 1,    //  6
    reg_adaptx_x_aud_0__aud_te0_clk_gate_en: 1,    //  7
    reg_aud_aad_clk_gate_en   :  1,    //      8
    reg_aud_apb_clk_gate_en   :  1,    //      9
    reg_aud_arc_clk_gate_en   :  1,    //     10
    reg_aud_bus_clk_gate_en   :  1,    //     11
    reg_aud_dsp0_clk_gate_en  :  1,    //     12
    reg_aud_dsp1_clk_gate_en  :  1,    //     13
    reg_aud_dsp2_clk_gate_en  :  1,    //     14
    reg_aud_dsp3_clk_gate_en  :  1,    //     15
    reg_aud_dsp_clk_gate_en   :  1,    //     16
    reg_aud_hdp_clk_gate_en   :  1,    //     17
    reg_aud_hmr1spdif_clk_gate_en: 1,    //   18
    reg_aud_hmr2spdif_clk_gate_en: 1,    //   19
    reg_aud_hmr3spdif_clk_gate_en: 1,    //   20
    reg_aud_hmr4spdif_clk_gate_en: 1,    //   21
    reg_aud_main_clk_gate_en  :  1,    //     22
    reg_aud_pc_clk_gate_en    :  1,    //     23
    reg_aud_pdm_clk_gate_en   :  1,    //     24
    reg_aud_spdif_clk_gate_en :  1,    //     25
    reg_aud_te0_clk_gate_en   :  1,    //     26
    reg_aud_te1_clk_gate_en   :  1,    //     27
    reg_aud_te2_clk_gate_en   :  1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_AUD_CRG_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_000C    crg_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_aud_fs_n     :  1,    //      1
    reg_soft_rst_aud_hw_n     :  1,    //      2
    reg_soft_rst_aud_pdm_n    :  1,    //      3
    reg_soft_rst_e_te_4_aud_hw_bnd_n: 1,    //  4
    reg_soft_rst_e_te_5_aud_hw_bnd_n: 1,    //  5
    reg_soft_rst_f_te_0_apb_bnd_n: 1,    //    6
    reg_soft_rst_f_te_1_apb_bnd_n: 1,    //    7
    reg_soft_rst_f_te_2_apb_bnd_n: 1,    //    8
    reg_soft_rst_f_te_3_apb_bnd_n: 1,    //    9
    reg_soft_rst_p_aud_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_cpu_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_aud_0_axi_n:  1,    //     12
    reg_soft_rst_x_cpu_0_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_AUD_CRG_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0010    crg_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_bus_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aud_dsp0_clk_sel      :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_aud_dsp1_clk_sel      :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_aud_dsp2_clk_sel      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_aud_dsp3_clk_sel      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_aud_dsp_clk_sel       :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_aud_te0_clk_sel       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_aud_te1_clk_sel       :  1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_AUD_CRG_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0014    crg_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_te2_clk_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_AUD_CRG_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD000_O26A0_T    crg_aud000;             // 0xCE7C_0000
    SCRG_CTRL_AUD_CRG_AUD001_O26A0_T    crg_aud001;             // 0xCE7C_0004
    SCRG_CTRL_AUD_CRG_AUD002_O26A0_T    crg_aud002;             // 0xCE7C_0008
    SCRG_CTRL_AUD_CRG_AUD003_O26A0_T    crg_aud003;             // 0xCE7C_000C
    SCRG_CTRL_AUD_CRG_AUD004_O26A0_T    crg_aud004;             // 0xCE7C_0010
    SCRG_CTRL_AUD_CRG_AUD005_O26A0_T    crg_aud005;             // 0xCE7C_0014
}SCRG_CTRL_AUD_REG_O26A0_T;
/* 6 regs */

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

#define SCRG_CTRL_AUD_CRG_AUD000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_AUD_CRG_AUD001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_AUD_CRG_AUD002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_AUD_CRG_AUD003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_AUD_CRG_AUD004_O26A0_T_OFF                (BASEADDRESS+0x0010)
#define SCRG_CTRL_AUD_CRG_AUD005_O26A0_T_OFF                (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCE7C_0000    crg_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0004    crg_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_AUD_CRG_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0008    crg_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_e_te_4__aud_te0_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_e_te_5__aud_te0_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_te_0__aud_apb_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_f_te_1__aud_apb_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_f_te_2__aud_apb_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_f_te_3__aud_apb_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_x_cpu_0__aud_te0_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_x_aud_0__aud_te0_clk_gate_en: 1;    //  7
    UINT32 reg_aud_aad_clk_gate_en: 1;    //   8
    UINT32 reg_aud_apb_clk_gate_en: 1;    //   9
    UINT32 reg_aud_arc_clk_gate_en: 1;    //  10
    UINT32 reg_aud_bus_clk_gate_en: 1;    //  11
    UINT32 reg_aud_dsp0_clk_gate_en: 1;    //  12
    UINT32 reg_aud_dsp1_clk_gate_en: 1;    //  13
    UINT32 reg_aud_dsp2_clk_gate_en: 1;    //  14
    UINT32 reg_aud_dsp3_clk_gate_en: 1;    //  15
    UINT32 reg_aud_dsp_clk_gate_en: 1;    //  16
    UINT32 reg_aud_hdp_clk_gate_en: 1;    //  17
    UINT32 reg_aud_hmr1spdif_clk_gate_en: 1;    //  18
    UINT32 reg_aud_hmr2spdif_clk_gate_en: 1;    //  19
    UINT32 reg_aud_hmr3spdif_clk_gate_en: 1;    //  20
    UINT32 reg_aud_hmr4spdif_clk_gate_en: 1;    //  21
    UINT32 reg_aud_main_clk_gate_en: 1;    //  22
    UINT32 reg_aud_pc_clk_gate_en: 1;    //   23
    UINT32 reg_aud_pdm_clk_gate_en: 1;    //  24
    UINT32 reg_aud_spdif_clk_gate_en: 1;    //  25
    UINT32 reg_aud_te0_clk_gate_en: 1;    //  26
    UINT32 reg_aud_te1_clk_gate_en: 1;    //  27
    UINT32 reg_aud_te2_clk_gate_en: 1;    //  28
    UINT32 resvd00            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_000C    crg_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_aud_fs_n: 1;    //     1
    UINT32 reg_soft_rst_aud_hw_n: 1;    //     2
    UINT32 reg_soft_rst_aud_pdm_n: 1;    //    3
    UINT32 reg_soft_rst_e_te_4_aud_hw_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_e_te_5_aud_hw_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_te_0_apb_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_te_1_apb_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_te_2_apb_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_3_apb_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_aud_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_cpu_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_cpu_0_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0010    crg_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_bus_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_aud_dsp0_clk_sel: 2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_aud_dsp1_clk_sel: 2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_aud_dsp2_clk_sel: 2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_aud_dsp3_clk_sel: 2;    //  17:16
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 reg_aud_dsp_clk_sel:  2;    //  21:20
    UINT32 resvd05            :  2;    //  23:22 reserved
    UINT32 reg_aud_te0_clk_sel:  1;    //     24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_aud_te1_clk_sel:  1;    //     28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7C_0014    crg_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_te2_clk_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_AUD_CRG_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_AUD_CRG_AUD000_O26A0_T    crg_aud000;             // 0xCE7C_0000
    SCRG_CTRL_AUD_CRG_AUD001_O26A0_T    crg_aud001;             // 0xCE7C_0004
    SCRG_CTRL_AUD_CRG_AUD002_O26A0_T    crg_aud002;             // 0xCE7C_0008
    SCRG_CTRL_AUD_CRG_AUD003_O26A0_T    crg_aud003;             // 0xCE7C_000C
    SCRG_CTRL_AUD_CRG_AUD004_O26A0_T    crg_aud004;             // 0xCE7C_0010
    SCRG_CTRL_AUD_CRG_AUD005_O26A0_T    crg_aud005;             // 0xCE7C_0014
}SCRG_CTRL_AUD_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_AUD_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

