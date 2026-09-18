#ifndef _MCRG_CTRL_HDMI_REG_O26A0_H_
#define _MCRG_CTRL_HDMI_REG_O26A0_H_

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
    0xC877_0000    crg_main_hdmi000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0004    crg_main_hdmi001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0008    crg_main_hdmi002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_core400_clk_inv_sel: 1,    //     0
    reg_hdmi_cvd54_clk_inv_sel:  1,    //      1
    reg_hdmi_frpll_earc_clk_inv_sel: 1,    //  2
    reg_hdmi_tpi_int_clk_inv_sel: 1,    //     3
    reg_m_earc_hdmi_earctx_bpclk_inv_sel: 1,    //  4
    reg_m_hdmi_phy1_aud_clk_ref_inv_sel: 1,    //  5
    reg_m_hdmi_phy1_frl_clk_inv_sel: 1,    //  6
    reg_m_hdmi_phy1_tmdsqp_clk_inv_sel: 1,    //  7
    reg_m_hdmi_phy1_tmdsrx_clk_inv_sel: 1,    //  8
    reg_m_hdmi_phy2_aud_clk_ref_inv_sel: 1,    //  9
    reg_m_hdmi_phy2_frl_clk_inv_sel: 1,    //  10
    reg_m_hdmi_phy2_tmdsqp_clk_inv_sel: 1,    //  11
    reg_m_hdmi_phy2_tmdsrx_clk_inv_sel: 1,    //  12
    reg_m_hdmi_phy3_aud_clk_ref_inv_sel: 1,    //  13
    reg_m_hdmi_phy3_frl_clk_inv_sel: 1,    //  14
    reg_m_hdmi_phy3_tmdsqp_clk_inv_sel: 1,    //  15
    reg_m_hdmi_phy3_tmdsrx_clk_inv_sel: 1,    //  16
    reg_m_hdmi_phy4_aud_clk_ref_inv_sel: 1,    //  17
    reg_m_hdmi_phy4_frl_clk_inv_sel: 1,    //  18
    reg_m_hdmi_phy4_tmdsqp_clk_inv_sel: 1,    //  19
    reg_m_hdmi_phy4_tmdsrx_clk_inv_sel: 1,    //  20
                              : 11;    //  31:21 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_000C    crg_main_hdmi003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy1: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0010    crg_main_hdmi004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy2: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0014    crg_main_hdmi005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy3: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0018    crg_main_hdmi006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy4: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI000_O26A0_T    crg_main_hdmi000;    // 0xC877_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI001_O26A0_T    crg_main_hdmi001;    // 0xC877_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI002_O26A0_T    crg_main_hdmi002;    // 0xC877_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI003_O26A0_T    crg_main_hdmi003;    // 0xC877_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI004_O26A0_T    crg_main_hdmi004;    // 0xC877_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI005_O26A0_T    crg_main_hdmi005;    // 0xC877_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI006_O26A0_T    crg_main_hdmi006;    // 0xC877_0018
}MCRG_CTRL_HDMI_REG_O26A0_T;
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

#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI000_O26A0_T_OFF         (BASEADDRESS+0x0000)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI001_O26A0_T_OFF         (BASEADDRESS+0x0004)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI002_O26A0_T_OFF         (BASEADDRESS+0x0008)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI003_O26A0_T_OFF         (BASEADDRESS+0x000C)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI004_O26A0_T_OFF         (BASEADDRESS+0x0010)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI005_O26A0_T_OFF         (BASEADDRESS+0x0014)
#define MCRG_CTRL_HDMI_CRG_MAIN_HDMI006_O26A0_T_OFF         (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC877_0000    crg_main_hdmi000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0004    crg_main_hdmi001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0008    crg_main_hdmi002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_core400_clk_inv_sel: 1;    //  0
    UINT32 reg_hdmi_cvd54_clk_inv_sel: 1;    //  1
    UINT32 reg_hdmi_frpll_earc_clk_inv_sel: 1;    //  2
    UINT32 reg_hdmi_tpi_int_clk_inv_sel: 1;    //  3
    UINT32 reg_m_earc_hdmi_earctx_bpclk_inv_sel: 1;    //  4
    UINT32 reg_m_hdmi_phy1_aud_clk_ref_inv_sel: 1;    //  5
    UINT32 reg_m_hdmi_phy1_frl_clk_inv_sel: 1;    //  6
    UINT32 reg_m_hdmi_phy1_tmdsqp_clk_inv_sel: 1;    //  7
    UINT32 reg_m_hdmi_phy1_tmdsrx_clk_inv_sel: 1;    //  8
    UINT32 reg_m_hdmi_phy2_aud_clk_ref_inv_sel: 1;    //  9
    UINT32 reg_m_hdmi_phy2_frl_clk_inv_sel: 1;    //  10
    UINT32 reg_m_hdmi_phy2_tmdsqp_clk_inv_sel: 1;    //  11
    UINT32 reg_m_hdmi_phy2_tmdsrx_clk_inv_sel: 1;    //  12
    UINT32 reg_m_hdmi_phy3_aud_clk_ref_inv_sel: 1;    //  13
    UINT32 reg_m_hdmi_phy3_frl_clk_inv_sel: 1;    //  14
    UINT32 reg_m_hdmi_phy3_tmdsqp_clk_inv_sel: 1;    //  15
    UINT32 reg_m_hdmi_phy3_tmdsrx_clk_inv_sel: 1;    //  16
    UINT32 reg_m_hdmi_phy4_aud_clk_ref_inv_sel: 1;    //  17
    UINT32 reg_m_hdmi_phy4_frl_clk_inv_sel: 1;    //  18
    UINT32 reg_m_hdmi_phy4_tmdsqp_clk_inv_sel: 1;    //  19
    UINT32 reg_m_hdmi_phy4_tmdsrx_clk_inv_sel: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_000C    crg_main_hdmi003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy1: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0010    crg_main_hdmi004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy2: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0014    crg_main_hdmi005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy3: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_0018    crg_main_hdmi006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy4: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_HDMI_CRG_MAIN_HDMI006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI000_O26A0_T    crg_main_hdmi000;    // 0xC877_0000
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI001_O26A0_T    crg_main_hdmi001;    // 0xC877_0004
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI002_O26A0_T    crg_main_hdmi002;    // 0xC877_0008
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI003_O26A0_T    crg_main_hdmi003;    // 0xC877_000C
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI004_O26A0_T    crg_main_hdmi004;    // 0xC877_0010
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI005_O26A0_T    crg_main_hdmi005;    // 0xC877_0014
    MCRG_CTRL_HDMI_CRG_MAIN_HDMI006_O26A0_T    crg_main_hdmi006;    // 0xC877_0018
}MCRG_CTRL_HDMI_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MCRG_CTRL_HDMI_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

