#ifndef _BCRG_CTRL_DPE_REG_O26A0_H_
#define _BCRG_CTRL_DPE_REG_O26A0_H_

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
    0xCC97_1000    crg_bnd_dpe000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_1004    crg_bnd_dpe001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_1008    crg_bnd_dpe002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edptx_clk_gate_en: 1,    //    0
    reg_apb_ipw_emusb_clk_gate_en: 1,    //    1
    reg_apb_ipw_led_clk_gate_en: 1,    //      2
    reg_apb_ipw_tcon_clk_gate_en: 1,    //     3
    reg_apb_ipw_usb_ss_clk_gate_en: 1,    //   4
    reg_apb_ipw_vsd_clk_gate_en: 1,    //      5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_100C    crg_bnd_dpe003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edptx_n: 1,    //     0
    reg_soft_rst_apb_ipw_emusb_n: 1,    //     1
    reg_soft_rst_apb_ipw_led_n:  1,    //      2
    reg_soft_rst_apb_ipw_tcon_n: 1,    //      3
    reg_soft_rst_apb_ipw_usb_ss_n: 1,    //    4
    reg_soft_rst_apb_ipw_vsd_n:  1,    //      5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE000_O26A0_T    crg_bnd_dpe000;     // 0xCC97_1000
    BCRG_CTRL_DPE_CRG_BND_DPE001_O26A0_T    crg_bnd_dpe001;     // 0xCC97_1004
    BCRG_CTRL_DPE_CRG_BND_DPE002_O26A0_T    crg_bnd_dpe002;     // 0xCC97_1008
    BCRG_CTRL_DPE_CRG_BND_DPE003_O26A0_T    crg_bnd_dpe003;     // 0xCC97_100C
}BCRG_CTRL_DPE_REG_O26A0_T;
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

#define BCRG_CTRL_DPE_CRG_BND_DPE000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_DPE_CRG_BND_DPE001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_DPE_CRG_BND_DPE002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_DPE_CRG_BND_DPE003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC97_1000    crg_bnd_dpe000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_1004    crg_bnd_dpe001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_1008    crg_bnd_dpe002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edptx_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_emusb_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_led_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_tcon_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_usb_ss_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_vsd_clk_gate_en: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_100C    crg_bnd_dpe003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edptx_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_emusb_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_led_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_tcon_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_usb_ss_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_vsd_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE000_O26A0_T    crg_bnd_dpe000;     // 0xCC97_1000
    BCRG_CTRL_DPE_CRG_BND_DPE001_O26A0_T    crg_bnd_dpe001;     // 0xCC97_1004
    BCRG_CTRL_DPE_CRG_BND_DPE002_O26A0_T    crg_bnd_dpe002;     // 0xCC97_1008
    BCRG_CTRL_DPE_CRG_BND_DPE003_O26A0_T    crg_bnd_dpe003;     // 0xCC97_100C
}BCRG_CTRL_DPE_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_DPE_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

