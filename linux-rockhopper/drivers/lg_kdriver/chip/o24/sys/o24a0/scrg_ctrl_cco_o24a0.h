#ifndef _SCRG_CTRL_CCO_REG_O24A0_H_
#define _SCRG_CTRL_CCO_REG_O24A0_H_

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
    0xCC87_0000    crg_cco0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0004    crg_cco1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CCO_CRG_CCO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0008    crg_cco2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_bosd_clk_gate_en      :  1,    //      2
    reg_de_clk_gate_en        :  1,    //      3
    reg_det_clk_gate_en       :  1,    //      4
    reg_disp_clk_gate_en      :  1,    //      5
    reg_disp_dds_clk_gate_en  :  1,    //      6
    reg_disp_in_clk_gate_en   :  1,    //      7
    reg_disp_osd_clk_gate_en  :  1,    //      8
    reg_disp_out_clk_gate_en  :  1,    //      9
    reg_fms_clk_gate_en       :  1,    //     10
    reg_gcf_clk_gate_en       :  1,    //     11
    reg_sosd_clk_gate_en      :  1,    //     12
    reg_spip_clk_gate_en      :  1,    //     13
    reg_vx1_clk_gate_en       :  1,    //     14
                              : 17;    //  31:15 reserved
}SCRG_CTRL_CCO_CRG_CCO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_000C    crg_cco3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_bosd_n       :  1,    //      2
    reg_soft_rst_de_n         :  1,    //      3
    reg_soft_rst_det_n        :  1,    //      4
    reg_soft_rst_disp_dds_n   :  1,    //      5
    reg_soft_rst_disp_in_n    :  1,    //      6
    reg_soft_rst_disp_n       :  1,    //      7
    reg_soft_rst_disp_osd_n   :  1,    //      8
    reg_soft_rst_disp_out_n   :  1,    //      9
    reg_soft_rst_f_cco_0_vx1_bnd_n: 1,    //  10
    reg_soft_rst_f_cco_10_disp_bnd_n: 1,    //  11
    reg_soft_rst_f_cco_5_sosd_bnd_n: 1,    //  12
    reg_soft_rst_f_cco_6_disp_out_bnd_n: 1,    //  13
    reg_soft_rst_f_cco_7_de_bnd_n: 1,    //   14
    reg_soft_rst_f_cco_8_disp_bnd_n: 1,    //  15
    reg_soft_rst_f_fms_0_fms_bnd_n: 1,    //  16
    reg_soft_rst_f_led_2_disp_osd_bnd_n: 1,    //  17
    reg_soft_rst_f_led_3_disp_bnd_n: 1,    //  18
    reg_soft_rst_f_tcon_1_vx1_bnd_n: 1,    //  19
    reg_soft_rst_f_vsd_2_disp_bnd_n: 1,    //  20
    reg_soft_rst_f_vsd_3_spip_bnd_n: 1,    //  21
    reg_soft_rst_f_vsd_4_de_bnd_n: 1,    //   22
    reg_soft_rst_fms_n        :  1,    //     23
    reg_soft_rst_gcf_n        :  1,    //     24
    reg_soft_rst_h_cco_1_de_bnd_n: 1,    //   25
    reg_soft_rst_h_cco_2_disp_bnd_n: 1,    //  26
    reg_soft_rst_h_cco_3_disp_bnd_n: 1,    //  27
    reg_soft_rst_h_cco_4_disp_bnd_n: 1,    //  28
    reg_soft_rst_h_cco_9_de_bnd_n: 1,    //   29
    reg_soft_rst_h_vsd_0_de_bnd_n: 1,    //   30
    reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  31
}SCRG_CTRL_CCO_CRG_CCO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0010    crg_cco4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_cco_1_axi_bnd_n: 1,    //   0
    reg_soft_rst_sosd_n       :  1,    //      1
    reg_soft_rst_spip_n       :  1,    //      2
    reg_soft_rst_vx1_n        :  1,    //      3
    reg_soft_rst_x_cco_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_cco_0_axi_n:  1,    //      5
    reg_soft_rst_x_cco_1_axi_bnd_n: 1,    //   6
    reg_soft_rst_x_cco_1_axi_n:  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_CCO_CRG_CCO4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0014    crg_cco5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bosd_clk_sel          :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_cco_det_clk_sel       :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_cco_disp_clk_sel      :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_cco_disp_dds_clk_sel  :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_cco_disp_in_clk_sel   :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_cco_disp_osd_clk_sel  :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_cco_gcf_clk_sel       :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_cco_sosd_clk_sel      :  3,    //  30:28
                              :  1;    //  31:31 reserved
}SCRG_CTRL_CCO_CRG_CCO5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0018    crg_cco6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cco_spip_clk_sel      :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_disp_out_clk_sel      :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}SCRG_CTRL_CCO_CRG_CCO6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO0_O24A0_T     crg_cco0   ;             // 0xCC87_0000
    SCRG_CTRL_CCO_CRG_CCO1_O24A0_T     crg_cco1   ;             // 0xCC87_0004
    SCRG_CTRL_CCO_CRG_CCO2_O24A0_T     crg_cco2   ;             // 0xCC87_0008
    SCRG_CTRL_CCO_CRG_CCO3_O24A0_T     crg_cco3   ;             // 0xCC87_000C
    SCRG_CTRL_CCO_CRG_CCO4_O24A0_T     crg_cco4   ;             // 0xCC87_0010
    SCRG_CTRL_CCO_CRG_CCO5_O24A0_T     crg_cco5   ;             // 0xCC87_0014
    SCRG_CTRL_CCO_CRG_CCO6_O24A0_T     crg_cco6   ;             // 0xCC87_0018
}SCRG_CTRL_CCO_REG_O24A0_T;
/* 7 regs */

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

#define SCRG_CTRL_CCO_CRG_CCO0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_CCO_CRG_CCO1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_CCO_CRG_CCO2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_CCO_CRG_CCO3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_CCO_CRG_CCO4_O24A0_T_OFF                  (BASEADDRESS+0x0010)
#define SCRG_CTRL_CCO_CRG_CCO5_O24A0_T_OFF                  (BASEADDRESS+0x0014)
#define SCRG_CTRL_CCO_CRG_CCO6_O24A0_T_OFF                  (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xCC87_0000    crg_cco0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0004    crg_cco1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CCO_CRG_CCO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0008    crg_cco2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_bosd_clk_gate_en: 1;    //      2
    UINT32 reg_de_clk_gate_en :  1;    //      3
    UINT32 reg_det_clk_gate_en:  1;    //      4
    UINT32 reg_disp_clk_gate_en: 1;    //      5
    UINT32 reg_disp_dds_clk_gate_en: 1;    //  6
    UINT32 reg_disp_in_clk_gate_en: 1;    //   7
    UINT32 reg_disp_osd_clk_gate_en: 1;    //  8
    UINT32 reg_disp_out_clk_gate_en: 1;    //  9
    UINT32 reg_fms_clk_gate_en:  1;    //     10
    UINT32 reg_gcf_clk_gate_en:  1;    //     11
    UINT32 reg_sosd_clk_gate_en: 1;    //     12
    UINT32 reg_spip_clk_gate_en: 1;    //     13
    UINT32 reg_vx1_clk_gate_en:  1;    //     14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_000C    crg_cco3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_bosd_n:  1;    //      2
    UINT32 reg_soft_rst_de_n  :  1;    //      3
    UINT32 reg_soft_rst_det_n :  1;    //      4
    UINT32 reg_soft_rst_disp_dds_n: 1;    //   5
    UINT32 reg_soft_rst_disp_in_n: 1;    //    6
    UINT32 reg_soft_rst_disp_n:  1;    //      7
    UINT32 reg_soft_rst_disp_osd_n: 1;    //   8
    UINT32 reg_soft_rst_disp_out_n: 1;    //   9
    UINT32 reg_soft_rst_f_cco_0_vx1_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_cco_10_disp_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_cco_5_sosd_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_cco_6_disp_out_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_cco_7_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_cco_8_disp_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_f_fms_0_fms_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_f_led_2_disp_osd_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_f_led_3_disp_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_f_tcon_1_vx1_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_f_vsd_2_disp_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_f_vsd_3_spip_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_f_vsd_4_de_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_fms_n :  1;    //     23
    UINT32 reg_soft_rst_gcf_n :  1;    //     24
    UINT32 reg_soft_rst_h_cco_1_de_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_h_cco_2_disp_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_h_cco_3_disp_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_h_cco_4_disp_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_h_cco_9_de_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_h_vsd_0_de_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_CCO_CRG_CCO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0010    crg_cco4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_cco_1_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_sosd_n:  1;    //      1
    UINT32 reg_soft_rst_spip_n:  1;    //      2
    UINT32 reg_soft_rst_vx1_n :  1;    //      3
    UINT32 reg_soft_rst_x_cco_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_cco_1_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_cco_1_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0014    crg_cco5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bosd_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_cco_det_clk_sel:  3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_cco_disp_clk_sel: 3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_cco_disp_dds_clk_sel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_cco_disp_in_clk_sel: 3;    //  18:16
    UINT32 resvd04            :  1;    //     19 reserved
    UINT32 reg_cco_disp_osd_clk_sel: 3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_cco_gcf_clk_sel:  3;    //  26:24
    UINT32 resvd06            :  1;    //     27 reserved
    UINT32 reg_cco_sosd_clk_sel: 3;    //  30:28
    UINT32 resvd07            :  1;    //  31:31 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_0018    crg_cco6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cco_spip_clk_sel: 3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_disp_out_clk_sel: 3;    //   6: 4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_CCO_CRG_CCO6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CCO_CRG_CCO0_O24A0_T     crg_cco0   ;             // 0xCC87_0000
    SCRG_CTRL_CCO_CRG_CCO1_O24A0_T     crg_cco1   ;             // 0xCC87_0004
    SCRG_CTRL_CCO_CRG_CCO2_O24A0_T     crg_cco2   ;             // 0xCC87_0008
    SCRG_CTRL_CCO_CRG_CCO3_O24A0_T     crg_cco3   ;             // 0xCC87_000C
    SCRG_CTRL_CCO_CRG_CCO4_O24A0_T     crg_cco4   ;             // 0xCC87_0010
    SCRG_CTRL_CCO_CRG_CCO5_O24A0_T     crg_cco5   ;             // 0xCC87_0014
    SCRG_CTRL_CCO_CRG_CCO6_O24A0_T     crg_cco6   ;             // 0xCC87_0018
}SCRG_CTRL_CCO_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_CCO_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

