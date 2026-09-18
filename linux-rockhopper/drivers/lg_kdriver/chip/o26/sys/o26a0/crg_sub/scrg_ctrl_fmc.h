#ifndef _SCRG_CTRL_FMC_REG_O26A0_H_
#define _SCRG_CTRL_FMC_REG_O26A0_H_

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
    0xCCC5_0000    crg_fmc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0004    crg_fmc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0008    crg_fmc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_gsc_9__de_clk_gate_en: 1,    //  0
    reg_adaprx_h_gsc_1__de_clk_gate_en: 1,    //  1
    reg_adaprx_h_gsc_2__de_clk_gate_en: 1,    //  2
    reg_adaprx_h_gsc_3__de_clk_gate_en: 1,    //  3
    reg_adaprx_h_gsc_4__de_clk_gate_en: 1,    //  4
    reg_adaptx_h_fmc_0__de_clk_gate_en: 1,    //  5
    reg_adaptx_h_fmc_1__de_clk_gate_en: 1,    //  6
    reg_adaptx_h_fmc_2__de_clk_gate_en: 1,    //  7
    reg_adaptx_h_fmc_3__de_clk_gate_en: 1,    //  8
    reg_adaptx_h_fmc_4__de_clk_gate_en: 1,    //  9
    reg_adaptx_x_fmc_0__axi_clk_gate_en: 1,    //  10
    reg_adaptx_x_fmc_1__axi_clk_gate_en: 1,    //  11
    reg_adaptx_x_fmc_2__axi_clk_gate_en: 1,    //  12
    reg_adaptx_x_fmc_3__axi_clk_gate_en: 1,    //  13
    reg_apb_clk_gate_en       :  1,    //     14
    reg_axi_clk_gate_en       :  1,    //     15
    reg_de_clk_gate_en        :  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_FMC_CRG_FMC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_000C    crg_fmc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_gsc_9_de_bnd_n: 1,    //    3
    reg_soft_rst_h_fmc_0_de_bnd_n: 1,    //    4
    reg_soft_rst_h_fmc_1_de_bnd_n: 1,    //    5
    reg_soft_rst_h_fmc_2_de_bnd_n: 1,    //    6
    reg_soft_rst_h_fmc_3_de_bnd_n: 1,    //    7
    reg_soft_rst_h_fmc_4_de_bnd_n: 1,    //    8
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //    9
    reg_soft_rst_h_gsc_2_de_bnd_n: 1,    //   10
    reg_soft_rst_h_gsc_3_de_bnd_n: 1,    //   11
    reg_soft_rst_h_gsc_4_de_bnd_n: 1,    //   12
    reg_soft_rst_p_fmc_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_fmc_1_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_fmc_2_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_fmc_3_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_fmc_0_axi_n:  1,    //     17
    reg_soft_rst_x_fmc_1_axi_n:  1,    //     18
    reg_soft_rst_x_fmc_2_axi_n:  1,    //     19
    reg_soft_rst_x_fmc_3_axi_n:  1,    //     20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_FMC_CRG_FMC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC000_O26A0_T    crg_fmc000;             // 0xCCC5_0000
    SCRG_CTRL_FMC_CRG_FMC001_O26A0_T    crg_fmc001;             // 0xCCC5_0004
    SCRG_CTRL_FMC_CRG_FMC002_O26A0_T    crg_fmc002;             // 0xCCC5_0008
    SCRG_CTRL_FMC_CRG_FMC003_O26A0_T    crg_fmc003;             // 0xCCC5_000C
}SCRG_CTRL_FMC_REG_O26A0_T;
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

#define SCRG_CTRL_FMC_CRG_FMC000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMC_CRG_FMC001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMC_CRG_FMC002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMC_CRG_FMC003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000    crg_fmc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0004    crg_fmc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0008    crg_fmc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_gsc_9__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_h_gsc_1__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_h_gsc_2__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_gsc_3__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_h_gsc_4__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_h_fmc_0__de_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_h_fmc_1__de_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_h_fmc_2__de_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_h_fmc_3__de_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_h_fmc_4__de_clk_gate_en: 1;    //  9
    UINT32 reg_adaptx_x_fmc_0__axi_clk_gate_en: 1;    //  10
    UINT32 reg_adaptx_x_fmc_1__axi_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_x_fmc_2__axi_clk_gate_en: 1;    //  12
    UINT32 reg_adaptx_x_fmc_3__axi_clk_gate_en: 1;    //  13
    UINT32 reg_apb_clk_gate_en:  1;    //     14
    UINT32 reg_axi_clk_gate_en:  1;    //     15
    UINT32 reg_de_clk_gate_en :  1;    //     16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_000C    crg_fmc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_gsc_9_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_fmc_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_fmc_1_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_fmc_2_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_fmc_3_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_fmc_4_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_gsc_2_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_gsc_3_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_gsc_4_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_fmc_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_fmc_1_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_fmc_2_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_fmc_3_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_fmc_0_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_fmc_1_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_fmc_2_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_fmc_3_axi_n: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC000_O26A0_T    crg_fmc000;             // 0xCCC5_0000
    SCRG_CTRL_FMC_CRG_FMC001_O26A0_T    crg_fmc001;             // 0xCCC5_0004
    SCRG_CTRL_FMC_CRG_FMC002_O26A0_T    crg_fmc002;             // 0xCCC5_0008
    SCRG_CTRL_FMC_CRG_FMC003_O26A0_T    crg_fmc003;             // 0xCCC5_000C
}SCRG_CTRL_FMC_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_FMC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

