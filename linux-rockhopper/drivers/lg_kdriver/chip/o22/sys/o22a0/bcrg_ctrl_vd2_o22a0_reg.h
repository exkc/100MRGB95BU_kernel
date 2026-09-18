#ifndef _BCRG_CTRL_VD2_REG_H_
#define _BCRG_CTRL_VD2_REG_H_

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
    0x55_0000    crg_bnd_vd200 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD2_CRG_BND_VD200_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0004    crg_bnd_vd201 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD2_CRG_BND_VD201_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0008    crg_bnd_vd202 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd2_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD2_CRG_BND_VD202_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_000C    crg_bnd_vd203 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_pes_fly_brdg_te_4_n: 1,    //     0
    reg_soft_pes_fly_brdg_te_5_n: 1,    //     1
    reg_soft_rst_apb_brdg_cpu_0_n: 1,    //    2
    reg_soft_rst_apb_brdg_lbm_0_n: 1,    //    3
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    4
    reg_soft_rst_axi_brdg_aud_1_n: 1,    //    5
    reg_soft_rst_axi_brdg_aud_2_n: 1,    //    6
    reg_soft_rst_axi_brdg_cco_0_n: 1,    //    7
    reg_soft_rst_axi_brdg_cco_1_n: 1,    //    8
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    9
    reg_soft_rst_axi_brdg_cpu_3_n: 1,    //   10
    reg_soft_rst_axi_brdg_fmc_0_n: 1,    //   11
    reg_soft_rst_axi_brdg_fmc_1_n: 1,    //   12
    reg_soft_rst_axi_brdg_fmc_2_n: 1,    //   13
    reg_soft_rst_axi_brdg_fmc_3_n: 1,    //   14
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //   15
    reg_soft_rst_axi_brdg_gpu_0_n: 1,    //   16
    reg_soft_rst_axi_brdg_gsc_0_n: 1,    //   17
    reg_soft_rst_axi_brdg_gsc_1_n: 1,    //   18
    reg_soft_rst_axi_brdg_lbus_4_n: 1,    //  19
    reg_soft_rst_axi_brdg_lbus_5_n: 1,    //  20
    reg_soft_rst_axi_brdg_lbus_6_n: 1,    //  21
    reg_soft_rst_axi_brdg_lbus_7_n: 1,    //  22
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //   23
    reg_soft_rst_axi_brdg_me1_0_n: 1,    //   24
    reg_soft_rst_axi_brdg_micom_1_n: 1,    //  25
    reg_soft_rst_axi_brdg_srnr_0_n: 1,    //  26
    reg_soft_rst_axi_brdg_ti_0_n: 1,    //    27
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //   28
    reg_soft_rst_fly_brdg_imx_16_n: 1,    //  29
    reg_soft_rst_fly_brdg_te_0_n: 1,    //    30
    reg_soft_rst_fly_brdg_te_1_n: 1;    //    31
}BCRG_CTRL_VD2_CRG_BND_VD203_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0010    crg_bnd_vd204 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_fly_brdg_te_2_n: 1,    //     0
    reg_soft_rst_fly_brdg_te_3_n: 1,    //     1
    reg_soft_rst_hsp_brdg_sre_2_n: 1,    //    2
    reg_soft_rst_hsp_brdg_sre_3_n: 1,    //    3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_VD2_CRG_BND_VD204_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0014    crg_bnd_vd205 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd2_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD2_CRG_BND_VD205_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD2_CRG_BND_VD200_O22A0_T    crg_bnd_vd200;         // 0x55_0000
    BCRG_CTRL_VD2_CRG_BND_VD201_O22A0_T    crg_bnd_vd201;         // 0x55_0004
    BCRG_CTRL_VD2_CRG_BND_VD202_O22A0_T    crg_bnd_vd202;         // 0x55_0008
    BCRG_CTRL_VD2_CRG_BND_VD203_O22A0_T    crg_bnd_vd203;         // 0x55_000C
    BCRG_CTRL_VD2_CRG_BND_VD204_O22A0_T    crg_bnd_vd204;         // 0x55_0010
    BCRG_CTRL_VD2_CRG_BND_VD205_O22A0_T    crg_bnd_vd205;         // 0x55_0014
}BCRG_CTRL_VD2_REG_O22A0_T;
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

#define BCRG_CTRL_VD2_CRG_BND_VD200_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD2_CRG_BND_VD201_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD2_CRG_BND_VD202_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD2_CRG_BND_VD203_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_VD2_CRG_BND_VD204_O22A0_T_OFF               (BASEADDRESS+0x0010)
#define BCRG_CTRL_VD2_CRG_BND_VD205_O22A0_T_OFF               (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x55_0000    crg_bnd_vd200 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD2_CRG_BND_VD200_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0004    crg_bnd_vd201 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD2_CRG_BND_VD201_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0008    crg_bnd_vd202 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd2_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD2_CRG_BND_VD202_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_000C    crg_bnd_vd203 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_pes_fly_brdg_te_4_n: 1;    //  0
    UINT32 reg_soft_pes_fly_brdg_te_5_n: 1;    //  1
    UINT32 reg_soft_rst_apb_brdg_cpu_0_n: 1;    //  2
    UINT32 reg_soft_rst_apb_brdg_lbm_0_n: 1;    //  3
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_aud_1_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_aud_2_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_cco_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_cco_1_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  9
    UINT32 reg_soft_rst_axi_brdg_cpu_3_n: 1;    //  10
    UINT32 reg_soft_rst_axi_brdg_fmc_0_n: 1;    //  11
    UINT32 reg_soft_rst_axi_brdg_fmc_1_n: 1;    //  12
    UINT32 reg_soft_rst_axi_brdg_fmc_2_n: 1;    //  13
    UINT32 reg_soft_rst_axi_brdg_fmc_3_n: 1;    //  14
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  15
    UINT32 reg_soft_rst_axi_brdg_gpu_0_n: 1;    //  16
    UINT32 reg_soft_rst_axi_brdg_gsc_0_n: 1;    //  17
    UINT32 reg_soft_rst_axi_brdg_gsc_1_n: 1;    //  18
    UINT32 reg_soft_rst_axi_brdg_lbus_4_n: 1;    //  19
    UINT32 reg_soft_rst_axi_brdg_lbus_5_n: 1;    //  20
    UINT32 reg_soft_rst_axi_brdg_lbus_6_n: 1;    //  21
    UINT32 reg_soft_rst_axi_brdg_lbus_7_n: 1;    //  22
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  23
    UINT32 reg_soft_rst_axi_brdg_me1_0_n: 1;    //  24
    UINT32 reg_soft_rst_axi_brdg_micom_1_n: 1;    //  25
    UINT32 reg_soft_rst_axi_brdg_srnr_0_n: 1;    //  26
    UINT32 reg_soft_rst_axi_brdg_ti_0_n: 1;    //  27
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  28
    UINT32 reg_soft_rst_fly_brdg_imx_16_n: 1;    //  29
    UINT32 reg_soft_rst_fly_brdg_te_0_n: 1;    //  30
    UINT32 reg_soft_rst_fly_brdg_te_1_n: 1;    //  31
    };
}BCRG_CTRL_VD2_CRG_BND_VD203_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0010    crg_bnd_vd204 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_fly_brdg_te_2_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_te_3_n: 1;    //  1
    UINT32 reg_soft_rst_hsp_brdg_sre_2_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_sre_3_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_VD2_CRG_BND_VD204_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x55_0014    crg_bnd_vd205 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd2_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD2_CRG_BND_VD205_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD2_CRG_BND_VD200_O22A0_T    crg_bnd_vd200;         // 0x55_0000
    BCRG_CTRL_VD2_CRG_BND_VD201_O22A0_T    crg_bnd_vd201;         // 0x55_0004
    BCRG_CTRL_VD2_CRG_BND_VD202_O22A0_T    crg_bnd_vd202;         // 0x55_0008
    BCRG_CTRL_VD2_CRG_BND_VD203_O22A0_T    crg_bnd_vd203;         // 0x55_000C
    BCRG_CTRL_VD2_CRG_BND_VD204_O22A0_T    crg_bnd_vd204;         // 0x55_0010
    BCRG_CTRL_VD2_CRG_BND_VD205_O22A0_T    crg_bnd_vd205;         // 0x55_0014
}BCRG_CTRL_VD2_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

