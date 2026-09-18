#ifndef _MCRG_CTRL_CVI_M23A0_REG_H_
#define _MCRG_CTRL_CVI_M23A0_REG_H_

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
    0xCC75_0000    crg_main_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_CVI_CRG_MAIN_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0004    crg_main_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_CVI_CRG_MAIN_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0008    crg_main_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_cvd54_clk_inv_sel :  1,    //      0
    reg_cvi_frpll_earc_clk_inv_sel: 1,    //   1
    reg_cvi_hdmir_earctx_bpclk_inv_sel: 1,    //  2
    reg_cvi_hdmirx_prt1_tmdsqp_clk_inv_sel: 1,    //  3
    reg_cvi_hdmirx_prt2_tmdsqp_clk_inv_sel: 1,    //  4
    reg_cvi_hdmirx_prt3_tmdsqp_clk_inv_sel: 1,    //  5
    reg_cvi_hdmirx_prt4_tmdsqp_clk_inv_sel: 1,    //  6
    reg_cvi_phy1_aud_ref_clk_inv_sel: 1,    //  7
    reg_cvi_phy1_hdmi_link_clk_inv_sel: 1,    //  8
    reg_cvi_phy2_aud_ref_clk_inv_sel: 1,    //  9
    reg_cvi_phy2_hdmi_link_clk_inv_sel: 1,    //  10
    reg_cvi_phy3_aud_ref_clk_inv_sel: 1,    //  11
    reg_cvi_phy3_hdmi_link_clk_inv_sel: 1,    //  12
    reg_cvi_phy4_aud_ref_clk_inv_sel: 1,    //  13
    reg_cvi_phy4_hdmi_link_clk_inv_sel: 1,    //  14
                              : 17;    //  31:15 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_000C    crg_main_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy1: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0010    crg_main_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy2: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0014    crg_main_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy3: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0018    crg_main_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_soft_reset_acrn_phy4: 1,    //    0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CVI_CRG_MAIN_CVI00_M23A0_T    crg_main_cvi00;     // 0xCC75_0000
    MCRG_CTRL_CVI_CRG_MAIN_CVI01_M23A0_T    crg_main_cvi01;     // 0xCC75_0004
    MCRG_CTRL_CVI_CRG_MAIN_CVI02_M23A0_T    crg_main_cvi02;     // 0xCC75_0008
    MCRG_CTRL_CVI_CRG_MAIN_CVI03_M23A0_T    crg_main_cvi03;     // 0xCC75_000C
    MCRG_CTRL_CVI_CRG_MAIN_CVI04_M23A0_T    crg_main_cvi04;     // 0xCC75_0010
    MCRG_CTRL_CVI_CRG_MAIN_CVI05_M23A0_T    crg_main_cvi05;     // 0xCC75_0014
    MCRG_CTRL_CVI_CRG_MAIN_CVI06_M23A0_T    crg_main_cvi06;     // 0xCC75_0018
}MCRG_CTRL_CVI_REG_M23A0_T;
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

#define MCRG_CTRL_CVI_CRG_MAIN_CVI00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI02_M23A0_T_OFF            (BASEADDRESS+0x0008)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI03_M23A0_T_OFF            (BASEADDRESS+0x000C)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI04_M23A0_T_OFF            (BASEADDRESS+0x0010)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI05_M23A0_T_OFF            (BASEADDRESS+0x0014)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI06_M23A0_T_OFF            (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xCC75_0000    crg_main_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0004    crg_main_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0008    crg_main_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_cvd54_clk_inv_sel: 1;    //  0
    UINT32 reg_cvi_frpll_earc_clk_inv_sel: 1;    //  1
    UINT32 reg_cvi_hdmir_earctx_bpclk_inv_sel: 1;    //  2
    UINT32 reg_cvi_hdmirx_prt1_tmdsqp_clk_inv_sel: 1;    //  3
    UINT32 reg_cvi_hdmirx_prt2_tmdsqp_clk_inv_sel: 1;    //  4
    UINT32 reg_cvi_hdmirx_prt3_tmdsqp_clk_inv_sel: 1;    //  5
    UINT32 reg_cvi_hdmirx_prt4_tmdsqp_clk_inv_sel: 1;    //  6
    UINT32 reg_cvi_phy1_aud_ref_clk_inv_sel: 1;    //  7
    UINT32 reg_cvi_phy1_hdmi_link_clk_inv_sel: 1;    //  8
    UINT32 reg_cvi_phy2_aud_ref_clk_inv_sel: 1;    //  9
    UINT32 reg_cvi_phy2_hdmi_link_clk_inv_sel: 1;    //  10
    UINT32 reg_cvi_phy3_aud_ref_clk_inv_sel: 1;    //  11
    UINT32 reg_cvi_phy3_hdmi_link_clk_inv_sel: 1;    //  12
    UINT32 reg_cvi_phy4_aud_ref_clk_inv_sel: 1;    //  13
    UINT32 reg_cvi_phy4_hdmi_link_clk_inv_sel: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_000C    crg_main_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy1: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0010    crg_main_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy2: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0014    crg_main_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy3: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_0018    crg_main_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_soft_reset_acrn_phy4: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CVI_CRG_MAIN_CVI00_M23A0_T    crg_main_cvi00;     // 0xCC75_0000
    MCRG_CTRL_CVI_CRG_MAIN_CVI01_M23A0_T    crg_main_cvi01;     // 0xCC75_0004
    MCRG_CTRL_CVI_CRG_MAIN_CVI02_M23A0_T    crg_main_cvi02;     // 0xCC75_0008
    MCRG_CTRL_CVI_CRG_MAIN_CVI03_M23A0_T    crg_main_cvi03;     // 0xCC75_000C
    MCRG_CTRL_CVI_CRG_MAIN_CVI04_M23A0_T    crg_main_cvi04;     // 0xCC75_0010
    MCRG_CTRL_CVI_CRG_MAIN_CVI05_M23A0_T    crg_main_cvi05;     // 0xCC75_0014
    MCRG_CTRL_CVI_CRG_MAIN_CVI06_M23A0_T    crg_main_cvi06;     // 0xCC75_0018
}MCRG_CTRL_CVI_REG_M23A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

