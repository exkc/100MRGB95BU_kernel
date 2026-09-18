#ifndef _SCRG_CTRL_TCON_REG_O24A0_H_
#define _SCRG_CTRL_TCON_REG_O24A0_H_

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
    0xCC92_0000    crg_tcon0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0004    crg_tcon1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0008    crg_tcon2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_c4_main_clk_pix1x_gate_en: 1,    //    2
    reg_demu_clk_gate_en      :  1,    //      3
    reg_epi_clk_gate_en       :  1,    //      4
    reg_fcic_clk_gate_en      :  1,    //      5
    reg_lvx_clk_gate_en       :  1,    //      6
    reg_mem2_clk_gate_en      :  1,    //      7
    reg_mem3_clk_gate_en      :  1,    //      8
    reg_mem_clk_gate_en       :  1,    //      9
    reg_op_clk_gate_en        :  1,    //     10
    reg_pclrc_clk_gate_en     :  1,    //     11
    reg_pix2_clk_gate_en      :  1,    //     12
    reg_pix_clk_gate_en       :  1,    //     13
    reg_pod_clk_gate_en       :  1,    //     14
    reg_tcon_clk_gate_en      :  1,    //     15
    reg_tgen_clk_gate_en      :  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_TCON_CRG_TCON2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_000C    crg_tcon3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_bist_pat_gen_pix_n: 1,    //  2
    reg_soft_rst_crc_tout_pix2_n: 1,    //     3
    reg_soft_rst_crc_vout_pix_n: 1,    //      4
    reg_soft_rst_demu_n       :  1,    //      5
    reg_soft_rst_epi_n        :  1,    //      6
    reg_soft_rst_f_cco_0_pix_bnd_n: 1,    //   7
    reg_soft_rst_f_cco_5_op_bnd_n: 1,    //    8
    reg_soft_rst_f_led_0_pix_bnd_n: 1,    //   9
    reg_soft_rst_f_led_1_pix2_bnd_n: 1,    //  10
    reg_soft_rst_f_tcon_0_pix_bnd_n: 1,    //  11
    reg_soft_rst_f_tcon_1_pix_bnd_n: 1,    //  12
    reg_soft_rst_fcic_n       :  1,    //     13
    reg_soft_rst_lvx_n        :  1,    //     14
    reg_soft_rst_op_n         :  1,    //     15
    reg_soft_rst_p_tcon_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_pclrc_n      :  1,    //     17
    reg_soft_rst_pix2_n       :  1,    //     18
    reg_soft_rst_pix_n        :  1,    //     19
    reg_soft_rst_pod_n        :  1,    //     20
    reg_soft_rst_tcon_n       :  1,    //     21
    reg_soft_rst_tgen_n       :  1,    //     22
    reg_soft_rst_x_tcon_0_axi_bnd_n: 1,    //  23
    reg_soft_rst_x_tcon_0_axi_n: 1,    //     24
                              :  7;    //  31:25 reserved
}SCRG_CTRL_TCON_CRG_TCON3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0010    crg_tcon4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_main_clk_pix1x_sel :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_demu_clk_sel          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_epi_clk_sel           :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_fcic_clk_sel          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_lvx_clk_sel           :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_mem2_clk_sel          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_mem3_clk_sel          :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_mem_clk_sel           :  1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_TCON_CRG_TCON4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0014    crg_tcon5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_op_clk_sel            :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_pclrc_clk_sel         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pix2_clk_sel          :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_pix_clk_sel           :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_pod_clk_sel           :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_tcon_clk_sel          :  1,    //     20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_TCON_CRG_TCON5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON0_O24A0_T    crg_tcon0 ;             // 0xCC92_0000
    SCRG_CTRL_TCON_CRG_TCON1_O24A0_T    crg_tcon1 ;             // 0xCC92_0004
    SCRG_CTRL_TCON_CRG_TCON2_O24A0_T    crg_tcon2 ;             // 0xCC92_0008
    SCRG_CTRL_TCON_CRG_TCON3_O24A0_T    crg_tcon3 ;             // 0xCC92_000C
    SCRG_CTRL_TCON_CRG_TCON4_O24A0_T    crg_tcon4 ;             // 0xCC92_0010
    SCRG_CTRL_TCON_CRG_TCON5_O24A0_T    crg_tcon5 ;             // 0xCC92_0014
}SCRG_CTRL_TCON_REG_O24A0_T;
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

#define SCRG_CTRL_TCON_CRG_TCON0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_TCON_CRG_TCON1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_TCON_CRG_TCON2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_TCON_CRG_TCON3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_TCON_CRG_TCON4_O24A0_T_OFF                (BASEADDRESS+0x0010)
#define SCRG_CTRL_TCON_CRG_TCON5_O24A0_T_OFF                (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC92_0000    crg_tcon0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0004    crg_tcon1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0008    crg_tcon2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_c4_main_clk_pix1x_gate_en: 1;    //  2
    UINT32 reg_demu_clk_gate_en: 1;    //      3
    UINT32 reg_epi_clk_gate_en:  1;    //      4
    UINT32 reg_fcic_clk_gate_en: 1;    //      5
    UINT32 reg_lvx_clk_gate_en:  1;    //      6
    UINT32 reg_mem2_clk_gate_en: 1;    //      7
    UINT32 reg_mem3_clk_gate_en: 1;    //      8
    UINT32 reg_mem_clk_gate_en:  1;    //      9
    UINT32 reg_op_clk_gate_en :  1;    //     10
    UINT32 reg_pclrc_clk_gate_en: 1;    //    11
    UINT32 reg_pix2_clk_gate_en: 1;    //     12
    UINT32 reg_pix_clk_gate_en:  1;    //     13
    UINT32 reg_pod_clk_gate_en:  1;    //     14
    UINT32 reg_tcon_clk_gate_en: 1;    //     15
    UINT32 reg_tgen_clk_gate_en: 1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_000C    crg_tcon3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_bist_pat_gen_pix_n: 1;    //  2
    UINT32 reg_soft_rst_crc_tout_pix2_n: 1;    //  3
    UINT32 reg_soft_rst_crc_vout_pix_n: 1;    //  4
    UINT32 reg_soft_rst_demu_n:  1;    //      5
    UINT32 reg_soft_rst_epi_n :  1;    //      6
    UINT32 reg_soft_rst_f_cco_0_pix_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_cco_5_op_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_led_0_pix_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_led_1_pix2_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_tcon_0_pix_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_tcon_1_pix_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_fcic_n:  1;    //     13
    UINT32 reg_soft_rst_lvx_n :  1;    //     14
    UINT32 reg_soft_rst_op_n  :  1;    //     15
    UINT32 reg_soft_rst_p_tcon_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_pclrc_n: 1;    //     17
    UINT32 reg_soft_rst_pix2_n:  1;    //     18
    UINT32 reg_soft_rst_pix_n :  1;    //     19
    UINT32 reg_soft_rst_pod_n :  1;    //     20
    UINT32 reg_soft_rst_tcon_n:  1;    //     21
    UINT32 reg_soft_rst_tgen_n:  1;    //     22
    UINT32 reg_soft_rst_x_tcon_0_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_x_tcon_0_axi_n: 1;    //  24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0010    crg_tcon4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_main_clk_pix1x_sel: 2;    //  1:0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_demu_clk_sel   :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_epi_clk_sel    :  2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_fcic_clk_sel   :  1;    //     12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_lvx_clk_sel    :  1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_mem2_clk_sel   :  1;    //     20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_mem3_clk_sel   :  1;    //     24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_mem_clk_sel    :  1;    //     28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0014    crg_tcon5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_op_clk_sel     :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_pclrc_clk_sel  :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_pix2_clk_sel   :  3;    //  10: 8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_pix_clk_sel    :  2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_pod_clk_sel    :  1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_tcon_clk_sel   :  1;    //     20
    UINT32 resvd05            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON0_O24A0_T    crg_tcon0 ;             // 0xCC92_0000
    SCRG_CTRL_TCON_CRG_TCON1_O24A0_T    crg_tcon1 ;             // 0xCC92_0004
    SCRG_CTRL_TCON_CRG_TCON2_O24A0_T    crg_tcon2 ;             // 0xCC92_0008
    SCRG_CTRL_TCON_CRG_TCON3_O24A0_T    crg_tcon3 ;             // 0xCC92_000C
    SCRG_CTRL_TCON_CRG_TCON4_O24A0_T    crg_tcon4 ;             // 0xCC92_0010
    SCRG_CTRL_TCON_CRG_TCON5_O24A0_T    crg_tcon5 ;             // 0xCC92_0014
}SCRG_CTRL_TCON_REG_O24A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_TCON_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

