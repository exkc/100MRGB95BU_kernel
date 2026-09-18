#ifndef _MCRG_CTRL_HDMI_REG_O24A0_H_
#define _MCRG_CTRL_HDMI_REG_O24A0_H_

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
    0xC8D7_0000    crg_main_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0004    crg_main_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0008    crg_main_hdmi2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_core400_clk_inv_sel: 1,    //     0
    reg_hdmi_frpll_earc_clk_inv_sel: 1,    //  1
    reg_m_earc_hdmi_earctx_bpclk_inv_sel: 1,    //  2
    reg_m_hdmi_phy1_aud_clk_ref_inv_sel: 1,    //  3
    reg_m_hdmi_phy1_frl_clk_inv_sel: 1,    //  4
    reg_m_hdmi_phy1_tmdsqp_clk_inv_sel: 1,    //  5
    reg_m_hdmi_phy1_tmdsrx_clk_inv_sel: 1,    //  6
    reg_m_hdmi_phy2_aud_clk_ref_inv_sel: 1,    //  7
    reg_m_hdmi_phy2_frl_clk_inv_sel: 1,    //  8
    reg_m_hdmi_phy2_tmdsqp_clk_inv_sel: 1,    //  9
    reg_m_hdmi_phy2_tmdsrx_clk_inv_sel: 1,    //  10
    reg_m_hdmi_phy3_aud_clk_ref_inv_sel: 1,    //  11
    reg_m_hdmi_phy3_frl_clk_inv_sel: 1,    //  12
    reg_m_hdmi_phy3_tmdsqp_clk_inv_sel: 1,    //  13
    reg_m_hdmi_phy3_tmdsrx_clk_inv_sel: 1,    //  14
    reg_m_hdmi_phy4_aud_clk_ref_inv_sel: 1,    //  15
    reg_m_hdmi_phy4_frl_clk_inv_sel: 1,    //  16
    reg_m_hdmi_phy4_tmdsqp_clk_inv_sel: 1,    //  17
    reg_m_hdmi_phy4_tmdsrx_clk_inv_sel: 1,    //  18
                              : 13;    //  31:19 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_000C    crg_main_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy1: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0010    crg_main_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy2: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0014    crg_main_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy3: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0018    crg_main_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy4: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI0_O24A0_T    crg_main_hdmi0;    // 0xC8D7_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI1_O24A0_T    crg_main_hdmi1;    // 0xC8D7_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI2_O24A0_T    crg_main_hdmi2;    // 0xC8D7_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI3_O24A0_T    crg_main_hdmi3;    // 0xC8D7_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI4_O24A0_T    crg_main_hdmi4;    // 0xC8D7_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI5_O24A0_T    crg_main_hdmi5;    // 0xC8D7_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI6_O24A0_T    crg_main_hdmi6;    // 0xC8D7_0018
}MCRG_CTRL_HDMI_REG_O24A0_T;
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

#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI0_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI1_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI2_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI3_O24A0_T_OFF           (BASEADDRESS+0x000C)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI4_O24A0_T_OFF           (BASEADDRESS+0x0010)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI5_O24A0_T_OFF           (BASEADDRESS+0x0014)
#define MCRG_CTRL_HDMI_CRG_MAIN_O24A0_HDMI6_O24A0_T_OFF           (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC8D7_0000    crg_main_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0004    crg_main_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0008    crg_main_hdmi2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_core400_clk_inv_sel: 1;    //  0
    UINT32 reg_hdmi_frpll_earc_clk_inv_sel: 1;    //  1
    UINT32 reg_m_earc_hdmi_earctx_bpclk_inv_sel: 1;    //  2
    UINT32 reg_m_hdmi_phy1_aud_clk_ref_inv_sel: 1;    //  3
    UINT32 reg_m_hdmi_phy1_frl_clk_inv_sel: 1;    //  4
    UINT32 reg_m_hdmi_phy1_tmdsqp_clk_inv_sel: 1;    //  5
    UINT32 reg_m_hdmi_phy1_tmdsrx_clk_inv_sel: 1;    //  6
    UINT32 reg_m_hdmi_phy2_aud_clk_ref_inv_sel: 1;    //  7
    UINT32 reg_m_hdmi_phy2_frl_clk_inv_sel: 1;    //  8
    UINT32 reg_m_hdmi_phy2_tmdsqp_clk_inv_sel: 1;    //  9
    UINT32 reg_m_hdmi_phy2_tmdsrx_clk_inv_sel: 1;    //  10
    UINT32 reg_m_hdmi_phy3_aud_clk_ref_inv_sel: 1;    //  11
    UINT32 reg_m_hdmi_phy3_frl_clk_inv_sel: 1;    //  12
    UINT32 reg_m_hdmi_phy3_tmdsqp_clk_inv_sel: 1;    //  13
    UINT32 reg_m_hdmi_phy3_tmdsrx_clk_inv_sel: 1;    //  14
    UINT32 reg_m_hdmi_phy4_aud_clk_ref_inv_sel: 1;    //  15
    UINT32 reg_m_hdmi_phy4_frl_clk_inv_sel: 1;    //  16
    UINT32 reg_m_hdmi_phy4_tmdsqp_clk_inv_sel: 1;    //  17
    UINT32 reg_m_hdmi_phy4_tmdsrx_clk_inv_sel: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_000C    crg_main_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy1: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0010    crg_main_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy2: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0014    crg_main_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy3: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_0018    crg_main_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy4: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI0_O24A0_T    crg_main_hdmi0;    // 0xC8D7_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI1_O24A0_T    crg_main_hdmi1;    // 0xC8D7_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI2_O24A0_T    crg_main_hdmi2;    // 0xC8D7_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI3_O24A0_T    crg_main_hdmi3;    // 0xC8D7_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI4_O24A0_T    crg_main_hdmi4;    // 0xC8D7_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI5_O24A0_T    crg_main_hdmi5;    // 0xC8D7_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI6_O24A0_T    crg_main_hdmi6;    // 0xC8D7_0018
}MCRG_CTRL_HDMI_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MCRG_CTRL_HDMI_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

