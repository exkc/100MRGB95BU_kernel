#ifndef _SCRG_CTRL_GSC_REG_O26A0_H_
#define _SCRG_CTRL_GSC_REG_O26A0_H_

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
    0xCCC8_0000    crg_gsc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GSC_CRG_GSC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_0004    crg_gsc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GSC_CRG_GSC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_0008    crg_gsc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_cco_5__de_clk_gate_en: 1,    //  0
    reg_adaprx_f_vsd_4__de_clk_gate_en: 1,    //  1
    reg_adaprx_h_fmc_0__de_clk_gate_en: 1,    //  2
    reg_adaprx_h_fmc_1__de_clk_gate_en: 1,    //  3
    reg_adaprx_h_fmc_2__de_clk_gate_en: 1,    //  4
    reg_adaprx_h_fmc_3__de_clk_gate_en: 1,    //  5
    reg_adaprx_h_fmc_4__de_clk_gate_en: 1,    //  6
    reg_adaptx_f_gsc_10__de_clk_gate_en: 1,    //  7
    reg_adaptx_f_gsc_9__de_clk_gate_en: 1,    //  8
    reg_adaptx_h_gsc_0__de_clk_gate_en: 1,    //  9
    reg_adaptx_h_gsc_1__de_clk_gate_en: 1,    //  10
    reg_adaptx_h_gsc_2__de_clk_gate_en: 1,    //  11
    reg_adaptx_h_gsc_3__de_clk_gate_en: 1,    //  12
    reg_adaptx_h_gsc_4__de_clk_gate_en: 1,    //  13
    reg_adaptx_h_gsc_5__de_clk_gate_en: 1,    //  14
    reg_adaptx_h_gsc_6__de_clk_gate_en: 1,    //  15
    reg_adaptx_h_gsc_7__de_clk_gate_en: 1,    //  16
    reg_adaptx_h_gsc_8__de_clk_gate_en: 1,    //  17
    reg_adaptx_x_gsc_0__axi_clk_gate_en: 1,    //  18
    reg_adaptx_x_gsc_1__axi_clk_gate_en: 1,    //  19
    reg_adaptx_x_gsc_2__axi_clk_gate_en: 1,    //  20
    reg_adaptx_x_gsc_3__axi_clk_gate_en: 1,    //  21
    reg_apb_clk_gate_en       :  1,    //     22
    reg_axi_clk_gate_en       :  1,    //     23
    reg_de_clk_gate_en        :  1,    //     24
                              :  7;    //  31:25 reserved
}SCRG_CTRL_GSC_CRG_GSC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_000C    crg_gsc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_de_sbus_n    :  1,    //      3
    reg_soft_rst_f_cco_5_de_bnd_n: 1,    //    4
    reg_soft_rst_f_gsc_10_de_bnd_n: 1,    //   5
    reg_soft_rst_f_gsc_9_de_bnd_n: 1,    //    6
    reg_soft_rst_f_vsd_4_de_bnd_n: 1,    //    7
    reg_soft_rst_h_fmc_0_de_bnd_n: 1,    //    8
    reg_soft_rst_h_fmc_1_de_bnd_n: 1,    //    9
    reg_soft_rst_h_fmc_2_de_bnd_n: 1,    //   10
    reg_soft_rst_h_fmc_3_de_bnd_n: 1,    //   11
    reg_soft_rst_h_fmc_4_de_bnd_n: 1,    //   12
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //   13
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //   14
    reg_soft_rst_h_gsc_2_de_bnd_n: 1,    //   15
    reg_soft_rst_h_gsc_3_de_bnd_n: 1,    //   16
    reg_soft_rst_h_gsc_4_de_bnd_n: 1,    //   17
    reg_soft_rst_h_gsc_5_de_bnd_n: 1,    //   18
    reg_soft_rst_h_gsc_6_de_bnd_n: 1,    //   19
    reg_soft_rst_h_gsc_7_de_bnd_n: 1,    //   20
    reg_soft_rst_h_gsc_8_de_bnd_n: 1,    //   21
    reg_soft_rst_p_gsc_0_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_gsc_1_axi_bnd_n: 1,    //  23
    reg_soft_rst_p_gsc_2_axi_bnd_n: 1,    //  24
    reg_soft_rst_p_gsc_3_axi_bnd_n: 1,    //  25
    reg_soft_rst_sbus_n       :  1,    //     26
    reg_soft_rst_x_gsc_0_axi_n:  1,    //     27
    reg_soft_rst_x_gsc_1_axi_n:  1,    //     28
    reg_soft_rst_x_gsc_2_axi_n:  1,    //     29
    reg_soft_rst_x_gsc_3_axi_n:  1,    //     30
                              :  1;    //  31:31 reserved
}SCRG_CTRL_GSC_CRG_GSC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GSC_CRG_GSC000_O26A0_T    crg_gsc000;             // 0xCCC8_0000
    SCRG_CTRL_GSC_CRG_GSC001_O26A0_T    crg_gsc001;             // 0xCCC8_0004
    SCRG_CTRL_GSC_CRG_GSC002_O26A0_T    crg_gsc002;             // 0xCCC8_0008
    SCRG_CTRL_GSC_CRG_GSC003_O26A0_T    crg_gsc003;             // 0xCCC8_000C
}SCRG_CTRL_GSC_REG_O26A0_T;
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

#define SCRG_CTRL_GSC_CRG_GSC000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_GSC_CRG_GSC001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_GSC_CRG_GSC002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_GSC_CRG_GSC003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCC8_0000    crg_gsc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GSC_CRG_GSC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_0004    crg_gsc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GSC_CRG_GSC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_0008    crg_gsc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_cco_5__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_vsd_4__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_fmc_0__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_fmc_1__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_fmc_2__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_h_fmc_3__de_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_h_fmc_4__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_f_gsc_10__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_f_gsc_9__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_h_gsc_0__de_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_h_gsc_1__de_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_h_gsc_2__de_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_h_gsc_3__de_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_h_gsc_4__de_clk_gate_en: 1;    //  13
    UINT32 reg_adaptx_h_gsc_5__de_clk_gate_en: 1;    //  14
    UINT32 reg_adaptx_h_gsc_6__de_clk_gate_en: 1;    //  15
    UINT32 reg_adaptx_h_gsc_7__de_clk_gate_en: 1;    //  16
    UINT32 reg_adaptx_h_gsc_8__de_clk_gate_en: 1;    //  17
    UINT32 reg_adaptx_x_gsc_0__axi_clk_gate_en: 1;    //  18
    UINT32 reg_adaptx_x_gsc_1__axi_clk_gate_en: 1;    //  19
    UINT32 reg_adaptx_x_gsc_2__axi_clk_gate_en: 1;    //  20
    UINT32 reg_adaptx_x_gsc_3__axi_clk_gate_en: 1;    //  21
    UINT32 reg_apb_clk_gate_en:  1;    //     22
    UINT32 reg_axi_clk_gate_en:  1;    //     23
    UINT32 reg_de_clk_gate_en :  1;    //     24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_000C    crg_gsc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_de_sbus_n: 1;    //    3
    UINT32 reg_soft_rst_f_cco_5_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_gsc_10_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_gsc_9_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_vsd_4_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_fmc_0_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_fmc_1_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_fmc_2_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_fmc_3_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_fmc_4_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_2_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_3_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_gsc_4_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_gsc_5_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_gsc_6_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_gsc_7_de_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_h_gsc_8_de_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_gsc_0_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_gsc_1_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_gsc_2_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_p_gsc_3_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_sbus_n:  1;    //     26
    UINT32 reg_soft_rst_x_gsc_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_gsc_1_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_gsc_2_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_gsc_3_axi_n: 1;    //  30
    UINT32 resvd00            :  1;    //  31:31 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GSC_CRG_GSC000_O26A0_T    crg_gsc000;             // 0xCCC8_0000
    SCRG_CTRL_GSC_CRG_GSC001_O26A0_T    crg_gsc001;             // 0xCCC8_0004
    SCRG_CTRL_GSC_CRG_GSC002_O26A0_T    crg_gsc002;             // 0xCCC8_0008
    SCRG_CTRL_GSC_CRG_GSC003_O26A0_T    crg_gsc003;             // 0xCCC8_000C
}SCRG_CTRL_GSC_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_GSC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

