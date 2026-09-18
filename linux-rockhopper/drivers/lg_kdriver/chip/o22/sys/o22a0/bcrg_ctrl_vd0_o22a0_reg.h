#ifndef _BCRG_CTRL_VD0_REG_H_
#define _BCRG_CTRL_VD0_REG_H_

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
    0x4F_0000    crg_bnd_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0004    crg_bnd_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0008    crg_bnd_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd0_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_000C    crg_bnd_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ethernet_0_n: 1,    //  0
    reg_soft_rst_fly_brdg_me0_0_n: 1,    //    1
    reg_soft_rst_fly_brdg_me0_1_n: 1,    //    2
    reg_soft_rst_hsp_brdg_dnnr_0_n: 1,    //   3
    reg_soft_rst_hsp_brdg_dnsr_0_n: 1,    //   4
    reg_soft_rst_hsp_brdg_sre_0_n: 1,    //    5
    reg_soft_rst_hsp_brdg_sre_1_n: 1,    //    6
    reg_soft_rst_pwm_24_n     :  1,    //      7
                              : 24;    //   31:8 reserved
}BCRG_CTRL_VD0_CRG_BND_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0010    crg_bnd_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD000_O22A0_T    crg_bnd_vd000;         // 0x4F_0000
    BCRG_CTRL_VD0_CRG_BND_VD001_O22A0_T    crg_bnd_vd001;         // 0x4F_0004
    BCRG_CTRL_VD0_CRG_BND_VD002_O22A0_T    crg_bnd_vd002;         // 0x4F_0008
    BCRG_CTRL_VD0_CRG_BND_VD003_O22A0_T    crg_bnd_vd003;         // 0x4F_000C
    BCRG_CTRL_VD0_CRG_BND_VD004_O22A0_T    crg_bnd_vd004;         // 0x4F_0010
}BCRG_CTRL_VD0_REG_O22A0_T;
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

#define BCRG_CTRL_VD0_CRG_BND_VD000_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD0_CRG_BND_VD001_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD0_CRG_BND_VD002_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD0_CRG_BND_VD003_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_VD0_CRG_BND_VD004_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x4F_0000    crg_bnd_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0004    crg_bnd_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0008    crg_bnd_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_000C    crg_bnd_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ethernet_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_me0_0_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_me0_1_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_dnnr_0_n: 1;    //  3
    UINT32 reg_soft_rst_hsp_brdg_dnsr_0_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_sre_0_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_sre_1_n: 1;    //  6
    UINT32 reg_soft_rst_pwm_24_n: 1;    //     7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4F_0010    crg_bnd_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD000_O22A0_T    crg_bnd_vd000;         // 0x4F_0000
    BCRG_CTRL_VD0_CRG_BND_VD001_O22A0_T    crg_bnd_vd001;         // 0x4F_0004
    BCRG_CTRL_VD0_CRG_BND_VD002_O22A0_T    crg_bnd_vd002;         // 0x4F_0008
    BCRG_CTRL_VD0_CRG_BND_VD003_O22A0_T    crg_bnd_vd003;         // 0x4F_000C
    BCRG_CTRL_VD0_CRG_BND_VD004_O22A0_T    crg_bnd_vd004;         // 0x4F_0010
}BCRG_CTRL_VD0_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

