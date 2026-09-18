#ifndef _BCRG_CTRL_FMC_REG_O24A0_H_
#define _BCRG_CTRL_FMC_REG_O24A0_H_

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
    0xCC44_1000    crg_bnd_fmc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1004    crg_bnd_fmc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMC_CRG_BND_FMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1008    crg_bnd_fmc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fmc_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_lb1_clk_gate_en: 1,    //   1
    reg_apb_ipw_sb_vd2vm_clk_gate_en: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_100C    crg_bnd_fmc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_2_n: 1,    //    1
    reg_soft_rst_axi_brdg_emmc_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_nd1_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  4
    reg_soft_rst_axi_brdg_vd0_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_vd0_1_n: 1,    //    6
    reg_soft_rst_axi_brdg_vd1_0_n: 1,    //    7
    reg_soft_rst_axi_brdg_vd1_1_n: 1,    //    8
    reg_soft_rst_axi_brdg_vd2_1_n: 1,    //    9
    reg_soft_rst_hsp_brdg_imx_10_n: 1,    //  10
    reg_soft_rst_hsp_brdg_imx_11_n: 1,    //  11
    reg_soft_rst_hsp_brdg_imx_8_n: 1,    //   12
    reg_soft_rst_hsp_brdg_imx_9_n: 1,    //   13
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //   14
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //   15
    reg_soft_rst_hsp_brdg_nd1_0_n: 1,    //   16
    reg_soft_rst_hsp_brdg_nd1_1_n: 1,    //   17
    reg_soft_rst_hsp_brdg_sre_4_n: 1,    //   18
    reg_soft_rst_hsp_brdg_sre_5_n: 1,    //   19
    reg_soft_rst_hsp_brdg_sre_6_n: 1,    //   20
    reg_soft_rst_hsp_brdg_sre_7_n: 1,    //   21
    reg_soft_rst_hsp_brdg_sre_8_n: 1,    //   22
                              :  9;    //  31:23 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1010    crg_bnd_fmc4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fmc_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_lb1_n: 1,    //    1
    reg_soft_rst_apb_ipw_sb_vd2vm_n: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_FMC_CRG_BND_FMC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC0_O24A0_T    crg_bnd_fmc0;         // 0xCC44_1000
    BCRG_CTRL_FMC_CRG_BND_FMC1_O24A0_T    crg_bnd_fmc1;         // 0xCC44_1004
    BCRG_CTRL_FMC_CRG_BND_FMC2_O24A0_T    crg_bnd_fmc2;         // 0xCC44_1008
    BCRG_CTRL_FMC_CRG_BND_FMC3_O24A0_T    crg_bnd_fmc3;         // 0xCC44_100C
    BCRG_CTRL_FMC_CRG_BND_FMC4_O24A0_T    crg_bnd_fmc4;         // 0xCC44_1010
}BCRG_CTRL_FMC_REG_O24A0_T;
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

#define BCRG_CTRL_FMC_CRG_BND_FMC0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMC_CRG_BND_FMC1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMC_CRG_BND_FMC2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMC_CRG_BND_FMC3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMC_CRG_BND_FMC4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC44_1000    crg_bnd_fmc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1004    crg_bnd_fmc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMC_CRG_BND_FMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1008    crg_bnd_fmc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fmc_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_lb1_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sb_vd2vm_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_100C    crg_bnd_fmc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_2_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_emmc_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_nd1_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_vd0_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_vd0_1_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_vd1_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vd1_1_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_vd2_1_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_imx_10_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_imx_11_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_imx_8_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_imx_9_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  14
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  15
    UINT32 reg_soft_rst_hsp_brdg_nd1_0_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_nd1_1_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_sre_4_n: 1;    //  18
    UINT32 reg_soft_rst_hsp_brdg_sre_5_n: 1;    //  19
    UINT32 reg_soft_rst_hsp_brdg_sre_6_n: 1;    //  20
    UINT32 reg_soft_rst_hsp_brdg_sre_7_n: 1;    //  21
    UINT32 reg_soft_rst_hsp_brdg_sre_8_n: 1;    //  22
    UINT32 resvd00            :  9;    //  31:23 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_1010    crg_bnd_fmc4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fmc_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_lb1_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sb_vd2vm_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_FMC_CRG_BND_FMC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMC_CRG_BND_FMC0_O24A0_T    crg_bnd_fmc0;         // 0xCC44_1000
    BCRG_CTRL_FMC_CRG_BND_FMC1_O24A0_T    crg_bnd_fmc1;         // 0xCC44_1004
    BCRG_CTRL_FMC_CRG_BND_FMC2_O24A0_T    crg_bnd_fmc2;         // 0xCC44_1008
    BCRG_CTRL_FMC_CRG_BND_FMC3_O24A0_T    crg_bnd_fmc3;         // 0xCC44_100C
    BCRG_CTRL_FMC_CRG_BND_FMC4_O24A0_T    crg_bnd_fmc4;         // 0xCC44_1010
}BCRG_CTRL_FMC_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_FMC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

