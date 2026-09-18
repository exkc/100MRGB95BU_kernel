#ifndef _SCRG_CTRL_TE_REG_O24A0_H_
#define _SCRG_CTRL_TE_REG_O24A0_H_

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
    0xCE48_0000    crg_te0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TE_CRG_TE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0004    crg_te1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TE_CRG_TE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0008    crg_te2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_gate_en       :  1,    //      0
    reg_fixed_s_clk_gate_en   :  1,    //      1
    reg_gstcc_if_clk_gate_en  :  1,    //      2
    reg_stpo_clk_gate_en      :  1,    //      3
    reg_te_ciout_clk_gate_en  :  1,    //      4
    reg_te_clk_gate_en        :  1,    //      5
    reg_temcu_clk_gate_en     :  1,    //      6
    reg_tpi_cam_clk_gate_en   :  1,    //      7
    reg_tpi_ext_demod_1_clk_gate_en: 1,    //  8
    reg_tpi_ext_demod_1_s_clk_gate_en: 1,    //  9
    reg_tpi_ext_demod_2_clk_gate_en: 1,    //  10
    reg_tpi_ext_demod_2_s_clk_gate_en: 1,    //  11
    reg_tpi_int_demod_clk_gate_en: 1,    //   12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_TE_CRG_TE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_000C    crg_te3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_n        :  1,    //      0
    reg_soft_rst_ciout_n      :  1,    //      1
    reg_soft_rst_e_te_4_te_bnd_n: 1,    //     2
    reg_soft_rst_e_te_5_te_bnd_n: 1,    //     3
    reg_soft_rst_e_te_6_te_bnd_n: 1,    //     4
    reg_soft_rst_e_te_7_te_bnd_n: 1,    //     5
    reg_soft_rst_f_s_n        :  1,    //      6
    reg_soft_rst_f_te_0_gstcc_if_bnd_n: 1,    //  7
    reg_soft_rst_f_te_1_gstcc_if_bnd_n: 1,    //  8
    reg_soft_rst_f_te_2_gstcc_if_bnd_n: 1,    //  9
    reg_soft_rst_f_te_3_gstcc_if_bnd_n: 1,    //  10
    reg_soft_rst_f_teipw_0_gstcc_if_bnd_n: 1,    //  11
    reg_soft_rst_f_teipw_1_gstcc_if_bnd_n: 1,    //  12
    reg_soft_rst_f_teipw_2_gstcc_if_bnd_n: 1,    //  13
    reg_soft_rst_f_teipw_3_gstcc_if_bnd_n: 1,    //  14
    reg_soft_rst_gstcc_if_n   :  1,    //     15
    reg_soft_rst_p_te_0_axi_bnd_n: 1,    //   16
    reg_soft_rst_stpo_n       :  1,    //     17
    reg_soft_rst_te_n         :  1,    //     18
    reg_soft_rst_temcu_n      :  1,    //     19
    reg_soft_rst_x_te_0_axi_bnd_n: 1,    //   20
    reg_soft_rst_x_te_0_axi_n :  1,    //     21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_TE_CRG_TE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0010    crg_te4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_TE_CRG_TE4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_te Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TE_CRG_TE0_O24A0_T       crg_te0    ;             // 0xCE48_0000
    SCRG_CTRL_TE_CRG_TE1_O24A0_T       crg_te1    ;             // 0xCE48_0004
    SCRG_CTRL_TE_CRG_TE2_O24A0_T       crg_te2    ;             // 0xCE48_0008
    SCRG_CTRL_TE_CRG_TE3_O24A0_T       crg_te3    ;             // 0xCE48_000C
    SCRG_CTRL_TE_CRG_TE4_O24A0_T       crg_te4    ;             // 0xCE48_0010
}SCRG_CTRL_TE_REG_O24A0_T;
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

#define SCRG_CTRL_TE_CRG_TE0_O24A0_T_OFF                    (BASEADDRESS+0x0000)
#define SCRG_CTRL_TE_CRG_TE1_O24A0_T_OFF                    (BASEADDRESS+0x0004)
#define SCRG_CTRL_TE_CRG_TE2_O24A0_T_OFF                    (BASEADDRESS+0x0008)
#define SCRG_CTRL_TE_CRG_TE3_O24A0_T_OFF                    (BASEADDRESS+0x000C)
#define SCRG_CTRL_TE_CRG_TE4_O24A0_T_OFF                    (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE48_0000    crg_te0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TE_CRG_TE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0004    crg_te1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TE_CRG_TE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0008    crg_te2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_gate_en:  1;    //      0
    UINT32 reg_fixed_s_clk_gate_en: 1;    //   1
    UINT32 reg_gstcc_if_clk_gate_en: 1;    //  2
    UINT32 reg_stpo_clk_gate_en: 1;    //      3
    UINT32 reg_te_ciout_clk_gate_en: 1;    //  4
    UINT32 reg_te_clk_gate_en :  1;    //      5
    UINT32 reg_temcu_clk_gate_en: 1;    //     6
    UINT32 reg_tpi_cam_clk_gate_en: 1;    //   7
    UINT32 reg_tpi_ext_demod_1_clk_gate_en: 1;    //  8
    UINT32 reg_tpi_ext_demod_1_s_clk_gate_en: 1;    //  9
    UINT32 reg_tpi_ext_demod_2_clk_gate_en: 1;    //  10
    UINT32 reg_tpi_ext_demod_2_s_clk_gate_en: 1;    //  11
    UINT32 reg_tpi_int_demod_clk_gate_en: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_TE_CRG_TE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_000C    crg_te3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_n :  1;    //      0
    UINT32 reg_soft_rst_ciout_n: 1;    //      1
    UINT32 reg_soft_rst_e_te_4_te_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_e_te_5_te_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_e_te_6_te_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_e_te_7_te_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_s_n :  1;    //      6
    UINT32 reg_soft_rst_f_te_0_gstcc_if_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_te_1_gstcc_if_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_2_gstcc_if_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_te_3_gstcc_if_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_teipw_0_gstcc_if_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_teipw_1_gstcc_if_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_teipw_2_gstcc_if_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_teipw_3_gstcc_if_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_gstcc_if_n: 1;    //  15
    UINT32 reg_soft_rst_p_te_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_stpo_n:  1;    //     17
    UINT32 reg_soft_rst_te_n  :  1;    //     18
    UINT32 reg_soft_rst_temcu_n: 1;    //     19
    UINT32 reg_soft_rst_x_te_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_x_te_0_axi_n: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_TE_CRG_TE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE48_0010    crg_te4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_TE_CRG_TE4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_te Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TE_CRG_TE0_O24A0_T       crg_te0    ;             // 0xCE48_0000
    SCRG_CTRL_TE_CRG_TE1_O24A0_T       crg_te1    ;             // 0xCE48_0004
    SCRG_CTRL_TE_CRG_TE2_O24A0_T       crg_te2    ;             // 0xCE48_0008
    SCRG_CTRL_TE_CRG_TE3_O24A0_T       crg_te3    ;             // 0xCE48_000C
    SCRG_CTRL_TE_CRG_TE4_O24A0_T       crg_te4    ;             // 0xCE48_0010
}SCRG_CTRL_TE_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_TE_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

