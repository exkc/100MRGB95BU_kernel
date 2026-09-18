#ifndef _MCRG_CTRL_HDMI_REG_H_
#define _MCRG_CTRL_HDMI_REG_H_

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
    0x22_0000    crg_main_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0004    crg_main_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0008    crg_main_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_frpll_earc_clk_inv_sel: 1,    //  0
    reg_hdmi_phy1_aud_ref_clk_inv_sel: 1,    //  1
    reg_hdmi_phy1_frl_clk_inv_sel: 1,    //    2
    reg_hdmi_phy1_hdmi_link_clk_inv_sel: 1,    //  3
    reg_hdmi_phy1_tmdsqp_clk_inv_sel: 1,    //  4
    reg_hdmi_phy2_aud_ref_clk_inv_sel: 1,    //  5
    reg_hdmi_phy2_frl_clk_inv_sel: 1,    //    6
    reg_hdmi_phy2_hdmi_link_clk_inv_sel: 1,    //  7
    reg_hdmi_phy2_tmdsqp_clk_inv_sel: 1,    //  8
    reg_hdmi_phy3_aud_ref_clk_inv_sel: 1,    //  9
    reg_hdmi_phy3_frl_clk_inv_sel: 1,    //   10
    reg_hdmi_phy3_hdmi_link_clk_inv_sel: 1,    //  11
    reg_hdmi_phy3_tmdsqp_clk_inv_sel: 1,    //  12
    reg_hdmi_phy4_aud_ref_clk_inv_sel: 1,    //  13
    reg_hdmi_phy4_frl_clk_inv_sel: 1,    //   14
    reg_hdmi_phy4_hdmi_link_clk_inv_sel: 1,    //  15
    reg_hdmi_phy4_tmdsqp_clk_inv_sel: 1,    //  16
    reg_hdmi_r_earctx_bpclk_inv_sel: 1,    //  17
                              : 14;    //  31:18 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_000C    crg_main_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy1: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0010    crg_main_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy2: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0014    crg_main_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy3: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0018    crg_main_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy4: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_mian_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI00_O22A0_T    crg_main_hdmi00;    // 0x22_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI01_O22A0_T    crg_main_hdmi01;    // 0x22_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI02_O22A0_T    crg_main_hdmi02;    // 0x22_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI03_O22A0_T    crg_main_hdmi03;    // 0x22_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI04_O22A0_T    crg_main_hdmi04;    // 0x22_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI05_O22A0_T    crg_main_hdmi05;    // 0x22_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI06_O22A0_T    crg_main_hdmi06;    // 0x22_0018
}MCRG_CTRL_HDMI_REG_O22A0_T;
/* 7 regs */

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

#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI00_O22A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI01_O22A0_T_OFF           (BASEADDRESS+0x0004)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI02_O22A0_T_OFF           (BASEADDRESS+0x0008)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI03_O22A0_T_OFF           (BASEADDRESS+0x000C)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI04_O22A0_T_OFF           (BASEADDRESS+0x0010)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI05_O22A0_T_OFF           (BASEADDRESS+0x0014)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI06_O22A0_T_OFF           (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x22_0000    crg_main_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0004    crg_main_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0008    crg_main_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_frpll_earc_clk_inv_sel: 1;    //  0
    UINT32 reg_hdmi_phy1_aud_ref_clk_inv_sel: 1;    //  1
    UINT32 reg_hdmi_phy1_frl_clk_inv_sel: 1;    //  2
    UINT32 reg_hdmi_phy1_hdmi_link_clk_inv_sel: 1;    //  3
    UINT32 reg_hdmi_phy1_tmdsqp_clk_inv_sel: 1;    //  4
    UINT32 reg_hdmi_phy2_aud_ref_clk_inv_sel: 1;    //  5
    UINT32 reg_hdmi_phy2_frl_clk_inv_sel: 1;    //  6
    UINT32 reg_hdmi_phy2_hdmi_link_clk_inv_sel: 1;    //  7
    UINT32 reg_hdmi_phy2_tmdsqp_clk_inv_sel: 1;    //  8
    UINT32 reg_hdmi_phy3_aud_ref_clk_inv_sel: 1;    //  9
    UINT32 reg_hdmi_phy3_frl_clk_inv_sel: 1;    //  10
    UINT32 reg_hdmi_phy3_hdmi_link_clk_inv_sel: 1;    //  11
    UINT32 reg_hdmi_phy3_tmdsqp_clk_inv_sel: 1;    //  12
    UINT32 reg_hdmi_phy4_aud_ref_clk_inv_sel: 1;    //  13
    UINT32 reg_hdmi_phy4_frl_clk_inv_sel: 1;    //  14
    UINT32 reg_hdmi_phy4_hdmi_link_clk_inv_sel: 1;    //  15
    UINT32 reg_hdmi_phy4_tmdsqp_clk_inv_sel: 1;    //  16
    UINT32 reg_hdmi_r_earctx_bpclk_inv_sel: 1;    //  17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_000C    crg_main_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy1: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0010    crg_main_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy2: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0014    crg_main_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy3: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x22_0018    crg_main_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy4: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_mian_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI00_O22A0_T    crg_main_hdmi00;    // 0x22_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI01_O22A0_T    crg_main_hdmi01;    // 0x22_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI02_O22A0_T    crg_main_hdmi02;    // 0x22_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI03_O22A0_T    crg_main_hdmi03;    // 0x22_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI04_O22A0_T    crg_main_hdmi04;    // 0x22_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI05_O22A0_T    crg_main_hdmi05;    // 0x22_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI06_O22A0_T    crg_main_hdmi06;    // 0x22_0018
}MCRG_CTRL_HDMI_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

