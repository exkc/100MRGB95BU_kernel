#ifndef _BCRG_CTRL_BMC_REG_H_
#define _BCRG_CTRL_BMC_REG_H_

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
    0x1_0000    crg_bnd_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0004    crg_bnd_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_BMC_CRG_BND_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0008    crg_bnd_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dbb_clk_gate_en: 1,    //      0
    reg_apb_ipw_usb_ss_bmc_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_000C    crg_bnd_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_lbm_pq3_n: 1,    //  0
    reg_soft_rst_apb_brdg_lbm_pv1_n: 1,    //  1
    reg_soft_rst_axi_brdg_ethernet_0_n: 1,    //  2
    reg_soft_rst_axi_brdg_me0_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_me0_1_n: 1,    //    4
    reg_soft_rst_axi_brdg_nd1_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_sre_0_n: 1,    //    6
    reg_soft_rst_axi_brdg_usb_0_n: 1,    //    7
    reg_soft_rst_axi_brdg_vd0_0_n: 1,    //    8
    reg_soft_rst_axi_brdg_vd0_1_n: 1,    //    9
    reg_soft_rst_fly_brdg_me0_0_n: 1,    //   10
    reg_soft_rst_fly_brdg_me0_1_n: 1,    //   11
    reg_soft_rst_fly_brdg_vd0_0_n: 1,    //   12
    reg_soft_rst_fly_brdg_vd1_0_n: 1,    //   13
    reg_soft_rst_hsp_brdg_dnnr_0_n: 1,    //  14
    reg_soft_rst_hsp_brdg_dnsr_0_n: 1,    //  15
    reg_soft_rst_hsp_brdg_nd0_2_n: 1,    //   16
    reg_soft_rst_hsp_brdg_nd0_3_n: 1,    //   17
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //   18
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //   19
    reg_soft_rst_hsp_brdg_sre_0_n: 1,    //   20
    reg_soft_rst_hsp_brdg_sre_1_n: 1,    //   21
    reg_soft_rst_hsp_brdg_sre_2_n: 1,    //   22
    reg_soft_rst_hsp_brdg_sre_3_n: 1,    //   23
                              :  8;    //  31:24 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0010    crg_bnd_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dbb_n:  1,    //      0
    reg_soft_rst_apb_ipw_usb_ss_bmc_n: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_BMC_CRG_BND_BMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC00_O22A0_T    crg_bnd_bmc00;         // 0x1_0000
    BCRG_CTRL_BMC_CRG_BND_BMC01_O22A0_T    crg_bnd_bmc01;         // 0x1_0004
    BCRG_CTRL_BMC_CRG_BND_BMC02_O22A0_T    crg_bnd_bmc02;         // 0x1_0008
    BCRG_CTRL_BMC_CRG_BND_BMC03_O22A0_T    crg_bnd_bmc03;         // 0x1_000C
    BCRG_CTRL_BMC_CRG_BND_BMC04_O22A0_T    crg_bnd_bmc04;         // 0x1_0010
}BCRG_CTRL_BMC_REG_O22A0_T;
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

#define BCRG_CTRL_BMC_CRG_BND_BMC00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_BMC_CRG_BND_BMC01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_BMC_CRG_BND_BMC02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_BMC_CRG_BND_BMC03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_BMC_CRG_BND_BMC04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x1_0000    crg_bnd_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0004    crg_bnd_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_BMC_CRG_BND_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0008    crg_bnd_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dbb_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_usb_ss_bmc_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_000C    crg_bnd_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_lbm_pq3_n: 1;    //  0
    UINT32 reg_soft_rst_apb_brdg_lbm_pv1_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_ethernet_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_me0_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_me0_1_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_nd1_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_sre_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_usb_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vd0_0_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_vd0_1_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_me0_0_n: 1;    //  10
    UINT32 reg_soft_rst_fly_brdg_me0_1_n: 1;    //  11
    UINT32 reg_soft_rst_fly_brdg_vd0_0_n: 1;    //  12
    UINT32 reg_soft_rst_fly_brdg_vd1_0_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_dnnr_0_n: 1;    //  14
    UINT32 reg_soft_rst_hsp_brdg_dnsr_0_n: 1;    //  15
    UINT32 reg_soft_rst_hsp_brdg_nd0_2_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_nd0_3_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  18
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  19
    UINT32 reg_soft_rst_hsp_brdg_sre_0_n: 1;    //  20
    UINT32 reg_soft_rst_hsp_brdg_sre_1_n: 1;    //  21
    UINT32 reg_soft_rst_hsp_brdg_sre_2_n: 1;    //  22
    UINT32 reg_soft_rst_hsp_brdg_sre_3_n: 1;    //  23
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0010    crg_bnd_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dbb_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_usb_ss_bmc_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_BMC_CRG_BND_BMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_BMC_CRG_BND_BMC00_O22A0_T    crg_bnd_bmc00;         // 0x1_0000
    BCRG_CTRL_BMC_CRG_BND_BMC01_O22A0_T    crg_bnd_bmc01;         // 0x1_0004
    BCRG_CTRL_BMC_CRG_BND_BMC02_O22A0_T    crg_bnd_bmc02;         // 0x1_0008
    BCRG_CTRL_BMC_CRG_BND_BMC03_O22A0_T    crg_bnd_bmc03;         // 0x1_000C
    BCRG_CTRL_BMC_CRG_BND_BMC04_O22A0_T    crg_bnd_bmc04;         // 0x1_0010
}BCRG_CTRL_BMC_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

