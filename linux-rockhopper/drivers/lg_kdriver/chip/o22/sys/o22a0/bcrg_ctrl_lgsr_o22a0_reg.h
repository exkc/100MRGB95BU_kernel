#ifndef _BCRG_CTRL_LGSR_REG_H_
#define _BCRG_CTRL_LGSR_REG_H_

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
    0x33_0000    crg_bnd_lgsr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LGSR_CRG_BND_LGSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0004    crg_bnd_lgsr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LGSR_CRG_BND_LGSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0008    crg_bnd_lgsr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dnnr_clk_gate_en: 1,    //     0
    reg_apb_ipw_dnsr_clk_gate_en: 1,    //     1
    reg_apb_ipw_lne_clk_gate_en: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_LGSR_CRG_BND_LGSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_000C    crg_bnd_lgsr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ethernet_0_n: 1,    //  0
    reg_soft_rst_fly_brdg_me0_0_n: 1,    //    1
    reg_soft_rst_fly_brdg_me0_1_n: 1,    //    2
    reg_soft_rst_pwm_24_n     :  1,    //      3
    reg_soft_sbw_aresetn_400  :  1,    //      4
    reg_soft_sbw_aresetn_480  :  1,    //      5
    reg_soft_sbw_aresetn_660  :  1,    //      6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_LGSR_CRG_BND_LGSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0010    crg_bnd_lgsr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dnnr_n: 1,    //      0
    reg_soft_rst_apb_ipw_dnsr_n: 1,    //      1
    reg_soft_rst_apb_ipw_lne_n:  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_LGSR_CRG_BND_LGSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0014    crg_bnd_lgsr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sbw_aclk_480_sel      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sbw_aclk_660_sel      :  1,    //      4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_LGSR_CRG_BND_LGSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LGSR_CRG_BND_LGSR00_O22A0_T    crg_bnd_lgsr00;      // 0x33_0000
    BCRG_CTRL_LGSR_CRG_BND_LGSR01_O22A0_T    crg_bnd_lgsr01;      // 0x33_0004
    BCRG_CTRL_LGSR_CRG_BND_LGSR02_O22A0_T    crg_bnd_lgsr02;      // 0x33_0008
    BCRG_CTRL_LGSR_CRG_BND_LGSR03_O22A0_T    crg_bnd_lgsr03;      // 0x33_000C
    BCRG_CTRL_LGSR_CRG_BND_LGSR04_O22A0_T    crg_bnd_lgsr04;      // 0x33_0010
    BCRG_CTRL_LGSR_CRG_BND_LGSR05_O22A0_T    crg_bnd_lgsr05;      // 0x33_0014
}BCRG_CTRL_LGSR_REG_O22A0_T;
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

#define BCRG_CTRL_LGSR_CRG_BND_LGSR00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_LGSR_CRG_BND_LGSR01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_LGSR_CRG_BND_LGSR02_O22A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_LGSR_CRG_BND_LGSR03_O22A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_LGSR_CRG_BND_LGSR04_O22A0_T_OFF             (BASEADDRESS+0x0010)
#define BCRG_CTRL_LGSR_CRG_BND_LGSR05_O22A0_T_OFF             (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x33_0000    crg_bnd_lgsr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0004    crg_bnd_lgsr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0008    crg_bnd_lgsr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dnnr_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dnsr_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_lne_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_000C    crg_bnd_lgsr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ethernet_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_me0_0_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_me0_1_n: 1;    //  2
    UINT32 reg_soft_rst_pwm_24_n: 1;    //     3
    UINT32 reg_soft_sbw_aresetn_400: 1;    //  4
    UINT32 reg_soft_sbw_aresetn_480: 1;    //  5
    UINT32 reg_soft_sbw_aresetn_660: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0010    crg_bnd_lgsr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dnnr_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dnsr_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_lne_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x33_0014    crg_bnd_lgsr05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sbw_aclk_480_sel: 1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sbw_aclk_660_sel: 1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_LGSR_CRG_BND_LGSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LGSR_CRG_BND_LGSR00_O22A0_T    crg_bnd_lgsr00;      // 0x33_0000
    BCRG_CTRL_LGSR_CRG_BND_LGSR01_O22A0_T    crg_bnd_lgsr01;      // 0x33_0004
    BCRG_CTRL_LGSR_CRG_BND_LGSR02_O22A0_T    crg_bnd_lgsr02;      // 0x33_0008
    BCRG_CTRL_LGSR_CRG_BND_LGSR03_O22A0_T    crg_bnd_lgsr03;      // 0x33_000C
    BCRG_CTRL_LGSR_CRG_BND_LGSR04_O22A0_T    crg_bnd_lgsr04;      // 0x33_0010
    BCRG_CTRL_LGSR_CRG_BND_LGSR05_O22A0_T    crg_bnd_lgsr05;      // 0x33_0014
}BCRG_CTRL_LGSR_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

