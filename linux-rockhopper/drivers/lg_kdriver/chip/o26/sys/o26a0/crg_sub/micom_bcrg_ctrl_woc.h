#ifndef _MICOM_BCRG_CTRL_WOC_REG_O26A0_H_
#define _MICOM_BCRG_CTRL_WOC_REG_O26A0_H_

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
    0xF33A_1000    crg_bnd_woc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_1004    crg_bnd_woc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_1008    crg_bnd_woc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edid_clk_gate_en: 1,    //     0
    reg_apb_ipw_ephy_clk_gate_en: 1,    //     1
    reg_apb_ipw_ion0_clk_gate_en: 1,    //     2
    reg_apb_ipw_micom_clk_gate_en: 1,    //    3
    reg_micom_cm0p_clk_gate_en:  1,    //      4
                              : 27;    //   31:5 reserved
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_100C    crg_bnd_woc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edid_n: 1,    //      0
    reg_soft_rst_apb_ipw_ephy_n: 1,    //      1
    reg_soft_rst_apb_ipw_ion0_n: 1,    //      2
    reg_soft_rst_apb_ipw_micom_n: 1,    //     3
                              : 28;    //   31:4 reserved
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC000_O26A0_T    crg_bnd_woc000;    // 0xF33A_1000
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC001_O26A0_T    crg_bnd_woc001;    // 0xF33A_1004
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC002_O26A0_T    crg_bnd_woc002;    // 0xF33A_1008
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC003_O26A0_T    crg_bnd_woc003;    // 0xF33A_100C
}MICOM_BCRG_CTRL_WOC_REG_O26A0_T;
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

#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC000_O26A0_T_OFF      (BASEADDRESS+0x0000)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC001_O26A0_T_OFF      (BASEADDRESS+0x0004)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC002_O26A0_T_OFF      (BASEADDRESS+0x0008)
#define MICOM_BCRG_CTRL_WOC_CRG_BND_WOC003_O26A0_T_OFF      (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xF33A_1000    crg_bnd_woc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_1004    crg_bnd_woc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_1008    crg_bnd_woc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edid_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_ephy_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_ion0_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_micom_clk_gate_en: 1;    //  3
    UINT32 reg_micom_cm0p_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_100C    crg_bnd_woc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edid_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_ephy_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_ion0_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_micom_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BCRG_CTRL_WOC_CRG_BND_WOC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC000_O26A0_T    crg_bnd_woc000;    // 0xF33A_1000
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC001_O26A0_T    crg_bnd_woc001;    // 0xF33A_1004
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC002_O26A0_T    crg_bnd_woc002;    // 0xF33A_1008
    MICOM_BCRG_CTRL_WOC_CRG_BND_WOC003_O26A0_T    crg_bnd_woc003;    // 0xF33A_100C
}MICOM_BCRG_CTRL_WOC_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_BCRG_CTRL_WOC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

