#ifndef _SCRG_CTRL_TCON_M23A0_REG_H_
#define _SCRG_CTRL_TCON_M23A0_REG_H_

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
    0xCC48_0000    crg_tcon00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0004    crg_tcon01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0008    crg_tcon02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_main_clk_pix1x_gate_en: 1,    //    0
    reg_demu_clk_gate_en      :  1,    //      1
    reg_epi_clk_gate_en       :  1,    //      2
    reg_fcic_clk_gate_en      :  1,    //      3
    reg_lvx_clk_gate_en       :  1,    //      4
    reg_mem2_clk_gate_en      :  1,    //      5
    reg_mem3_clk_gate_en      :  1,    //      6
    reg_mem_clk_gate_en       :  1,    //      7
    reg_pclrc_clk_gate_en     :  1,    //      8
    reg_pix1_clk_gate_en      :  1,    //      9
    reg_pix2_clk_gate_en      :  1,    //     10
    reg_pix_clk_gate_en       :  1,    //     11
    reg_pod_clk_gate_en       :  1,    //     12
    reg_tcon_apb_clk_gate_en  :  1,    //     13
    reg_tcon_axi_clk_gate_en  :  1,    //     14
    reg_tcon_clk_gate_en      :  1,    //     15
    reg_tgen_clk_gate_en      :  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_TCON_CRG_TCON02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_000C    crg_tcon03 ''
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
    reg_soft_rst_f_led_0_pix1_bnd_n: 1,    //  7
    reg_soft_rst_fcic_n       :  1,    //      8
    reg_soft_rst_lvx_n        :  1,    //      9
    reg_soft_rst_p_tcon_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_pclrc_n      :  1,    //     11
    reg_soft_rst_pix1_n       :  1,    //     12
    reg_soft_rst_pix2_n       :  1,    //     13
    reg_soft_rst_pix_n        :  1,    //     14
    reg_soft_rst_pod_n        :  1,    //     15
    reg_soft_rst_tcon_n       :  1,    //     16
    reg_soft_rst_tgen_n       :  1,    //     17
    reg_soft_rst_x_tcon_0_axi_bnd_n: 1,    //  18
    reg_soft_rst_x_tcon_0_axi_n: 1,    //     19
                              : 12;    //  31:20 reserved
}SCRG_CTRL_TCON_CRG_TCON03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0010    crg_tcon04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem2_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_mem3_clk_sel          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_mem_clk_sel           :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pix1_clk_sel          :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_pix2_clk_sel          :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_lvx_clk_sel           :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_epi_clk_sel           :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_c4_main_clk_pix1x_sel :  3,    //  30:28
                              :  1;    //  31:31 reserved
}SCRG_CTRL_TCON_CRG_TCON04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0014    crg_tcon05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pix_clk_sel           :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}SCRG_CTRL_TCON_CRG_TCON05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON00_M23A0_T    crg_tcon00;            // 0xCC48_0000
    SCRG_CTRL_TCON_CRG_TCON01_M23A0_T    crg_tcon01;            // 0xCC48_0004
    SCRG_CTRL_TCON_CRG_TCON02_M23A0_T    crg_tcon02;            // 0xCC48_0008
    SCRG_CTRL_TCON_CRG_TCON03_M23A0_T    crg_tcon03;            // 0xCC48_000C
    SCRG_CTRL_TCON_CRG_TCON04_M23A0_T    crg_tcon04;            // 0xCC48_0010
    SCRG_CTRL_TCON_CRG_TCON05_M23A0_T    crg_tcon05;            // 0xCC48_0014
}SCRG_CTRL_TCON_REG_M23A0_T;
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

#define SCRG_CTRL_TCON_CRG_TCON00_M23A0_T_OFF               (BASEADDRESS+0x0000)
#define SCRG_CTRL_TCON_CRG_TCON01_M23A0_T_OFF               (BASEADDRESS+0x0004)
#define SCRG_CTRL_TCON_CRG_TCON02_M23A0_T_OFF               (BASEADDRESS+0x0008)
#define SCRG_CTRL_TCON_CRG_TCON03_M23A0_T_OFF               (BASEADDRESS+0x000C)
#define SCRG_CTRL_TCON_CRG_TCON04_M23A0_T_OFF               (BASEADDRESS+0x0010)
#define SCRG_CTRL_TCON_CRG_TCON05_M23A0_T_OFF               (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC48_0000    crg_tcon00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0004    crg_tcon01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0008    crg_tcon02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_main_clk_pix1x_gate_en: 1;    //  0
    UINT32 reg_demu_clk_gate_en: 1;    //      1
    UINT32 reg_epi_clk_gate_en:  1;    //      2
    UINT32 reg_fcic_clk_gate_en: 1;    //      3
    UINT32 reg_lvx_clk_gate_en:  1;    //      4
    UINT32 reg_mem2_clk_gate_en: 1;    //      5
    UINT32 reg_mem3_clk_gate_en: 1;    //      6
    UINT32 reg_mem_clk_gate_en:  1;    //      7
    UINT32 reg_pclrc_clk_gate_en: 1;    //     8
    UINT32 reg_pix1_clk_gate_en: 1;    //      9
    UINT32 reg_pix2_clk_gate_en: 1;    //     10
    UINT32 reg_pix_clk_gate_en:  1;    //     11
    UINT32 reg_pod_clk_gate_en:  1;    //     12
    UINT32 reg_tcon_apb_clk_gate_en: 1;    //  13
    UINT32 reg_tcon_axi_clk_gate_en: 1;    //  14
    UINT32 reg_tcon_clk_gate_en: 1;    //     15
    UINT32 reg_tgen_clk_gate_en: 1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_000C    crg_tcon03 ''
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
    UINT32 reg_soft_rst_f_led_0_pix1_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_fcic_n:  1;    //      8
    UINT32 reg_soft_rst_lvx_n :  1;    //      9
    UINT32 reg_soft_rst_p_tcon_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_pclrc_n: 1;    //     11
    UINT32 reg_soft_rst_pix1_n:  1;    //     12
    UINT32 reg_soft_rst_pix2_n:  1;    //     13
    UINT32 reg_soft_rst_pix_n :  1;    //     14
    UINT32 reg_soft_rst_pod_n :  1;    //     15
    UINT32 reg_soft_rst_tcon_n:  1;    //     16
    UINT32 reg_soft_rst_tgen_n:  1;    //     17
    UINT32 reg_soft_rst_x_tcon_0_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_x_tcon_0_axi_n: 1;    //  19
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0010    crg_tcon04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem2_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_mem3_clk_sel   :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_mem_clk_sel    :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_pix1_clk_sel   :  2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_pix2_clk_sel   :  2;    //  17:16
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 reg_lvx_clk_sel    :  2;    //  21:20
    UINT32 resvd05            :  2;    //  23:22 reserved
    UINT32 reg_epi_clk_sel    :  2;    //  25:24
    UINT32 resvd06            :  2;    //  27:26 reserved
    UINT32 reg_c4_main_clk_pix1x_sel: 3;    //  30:28
    UINT32 resvd07            :  1;    //  31:31 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_0014    crg_tcon05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pix_clk_sel    :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON00_M23A0_T    crg_tcon00;            // 0xCC48_0000
    SCRG_CTRL_TCON_CRG_TCON01_M23A0_T    crg_tcon01;            // 0xCC48_0004
    SCRG_CTRL_TCON_CRG_TCON02_M23A0_T    crg_tcon02;            // 0xCC48_0008
    SCRG_CTRL_TCON_CRG_TCON03_M23A0_T    crg_tcon03;            // 0xCC48_000C
    SCRG_CTRL_TCON_CRG_TCON04_M23A0_T    crg_tcon04;            // 0xCC48_0010
    SCRG_CTRL_TCON_CRG_TCON05_M23A0_T    crg_tcon05;            // 0xCC48_0014
}SCRG_CTRL_TCON_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

