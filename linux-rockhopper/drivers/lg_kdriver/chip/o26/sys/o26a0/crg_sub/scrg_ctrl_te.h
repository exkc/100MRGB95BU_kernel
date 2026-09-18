#ifndef _SCRG_CTRL_TE_REG_O26A0_H_
#define _SCRG_CTRL_TE_REG_O26A0_H_

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
    0xCE7E_0000    crg_te000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TE_CRG_TE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0004    crg_te001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TE_CRG_TE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0008    crg_te002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_e_te_4__te_clk_gate_en: 1,    //  0
    reg_adaptx_e_te_5__te_clk_gate_en: 1,    //  1
    reg_adaptx_e_te_6__te_clk_gate_en: 1,    //  2
    reg_adaptx_e_te_7__te_clk_gate_en: 1,    //  3
    reg_adaptx_f_te_0__gstcc_if_clk_gate_en: 1,    //  4
    reg_adaptx_f_te_1__gstcc_if_clk_gate_en: 1,    //  5
    reg_adaptx_f_te_2__gstcc_if_clk_gate_en: 1,    //  6
    reg_adaptx_f_te_3__gstcc_if_clk_gate_en: 1,    //  7
    reg_adaptx_f_teipw_0__gstcc_if_clk_gate_en: 1,    //  8
    reg_adaptx_f_teipw_1__gstcc_if_clk_gate_en: 1,    //  9
    reg_adaptx_f_teipw_2__gstcc_if_clk_gate_en: 1,    //  10
    reg_adaptx_f_teipw_3__gstcc_if_clk_gate_en: 1,    //  11
    reg_adaptx_x_te_0__axi_clk_gate_en: 1,    //  12
    reg_axi_clk_gate_en       :  1,    //     13
    reg_fixed_s_clk_gate_en   :  1,    //     14
    reg_gstcc_if_clk_gate_en  :  1,    //     15
    reg_stpo_clk_gate_en      :  1,    //     16
    reg_te_ciout_clk_gate_en  :  1,    //     17
    reg_te_clk_gate_en        :  1,    //     18
    reg_temcu_clk_gate_en     :  1,    //     19
    reg_tpi_cam_clk_gate_en   :  1,    //     20
    reg_tpi_ext_demod_1_clk_gate_en: 1,    //  21
    reg_tpi_ext_demod_1_s_clk_gate_en: 1,    //  22
    reg_tpi_ext_demod_2_clk_gate_en: 1,    //  23
    reg_tpi_ext_demod_2_s_clk_gate_en: 1,    //  24
    reg_tpi_int_demod_clk_gate_en: 1,    //   25
                              :  6;    //  31:26 reserved
}SCRG_CTRL_TE_CRG_TE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_000C    crg_te003 ''
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
    reg_soft_rst_x_te_0_axi_n :  1,    //     20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_TE_CRG_TE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0010    crg_te004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_TE_CRG_TE004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_te Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TE_CRG_TE000_O26A0_T     crg_te000  ;             // 0xCE7E_0000
    SCRG_CTRL_TE_CRG_TE001_O26A0_T     crg_te001  ;             // 0xCE7E_0004
    SCRG_CTRL_TE_CRG_TE002_O26A0_T     crg_te002  ;             // 0xCE7E_0008
    SCRG_CTRL_TE_CRG_TE003_O26A0_T     crg_te003  ;             // 0xCE7E_000C
    SCRG_CTRL_TE_CRG_TE004_O26A0_T     crg_te004  ;             // 0xCE7E_0010
}SCRG_CTRL_TE_REG_O26A0_T;
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

#define SCRG_CTRL_TE_CRG_TE000_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_TE_CRG_TE001_O26A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_TE_CRG_TE002_O26A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_TE_CRG_TE003_O26A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_TE_CRG_TE004_O26A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE7E_0000    crg_te000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TE_CRG_TE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0004    crg_te001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TE_CRG_TE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0008    crg_te002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_e_te_4__te_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_e_te_5__te_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_e_te_6__te_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_e_te_7__te_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_f_te_0__gstcc_if_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_f_te_1__gstcc_if_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_f_te_2__gstcc_if_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_f_te_3__gstcc_if_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_f_teipw_0__gstcc_if_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_f_teipw_1__gstcc_if_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_f_teipw_2__gstcc_if_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_f_teipw_3__gstcc_if_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_x_te_0__axi_clk_gate_en: 1;    //  12
    UINT32 reg_axi_clk_gate_en:  1;    //     13
    UINT32 reg_fixed_s_clk_gate_en: 1;    //  14
    UINT32 reg_gstcc_if_clk_gate_en: 1;    //  15
    UINT32 reg_stpo_clk_gate_en: 1;    //     16
    UINT32 reg_te_ciout_clk_gate_en: 1;    //  17
    UINT32 reg_te_clk_gate_en :  1;    //     18
    UINT32 reg_temcu_clk_gate_en: 1;    //    19
    UINT32 reg_tpi_cam_clk_gate_en: 1;    //  20
    UINT32 reg_tpi_ext_demod_1_clk_gate_en: 1;    //  21
    UINT32 reg_tpi_ext_demod_1_s_clk_gate_en: 1;    //  22
    UINT32 reg_tpi_ext_demod_2_clk_gate_en: 1;    //  23
    UINT32 reg_tpi_ext_demod_2_s_clk_gate_en: 1;    //  24
    UINT32 reg_tpi_int_demod_clk_gate_en: 1;    //  25
    UINT32 resvd00            :  6;    //  31:26 reserved
    };
}SCRG_CTRL_TE_CRG_TE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_000C    crg_te003 ''
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
    UINT32 reg_soft_rst_x_te_0_axi_n: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_TE_CRG_TE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7E_0010    crg_te004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_TE_CRG_TE004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_te Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TE_CRG_TE000_O26A0_T     crg_te000  ;             // 0xCE7E_0000
    SCRG_CTRL_TE_CRG_TE001_O26A0_T     crg_te001  ;             // 0xCE7E_0004
    SCRG_CTRL_TE_CRG_TE002_O26A0_T     crg_te002  ;             // 0xCE7E_0008
    SCRG_CTRL_TE_CRG_TE003_O26A0_T     crg_te003  ;             // 0xCE7E_000C
    SCRG_CTRL_TE_CRG_TE004_O26A0_T     crg_te004  ;             // 0xCE7E_0010
}SCRG_CTRL_TE_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_TE_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

