#ifndef _SCRG_CTRL_HDMI_REG_H_
#define _SCRG_CTRL_HDMI_REG_H_

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
    0x24_0000    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDMI_CRG_HDMI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0004    crg_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDMI_CRG_HDMI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0008    crg_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_hdmi1_mclk_gate_en:  1,    //      0
    reg_aud_hdmi2_mclk_gate_en:  1,    //      1
    reg_aud_hdmi3_mclk_gate_en:  1,    //      2
    reg_aud_hdmi4_mclk_gate_en:  1,    //      3
    reg_earc_extern_aud_clk_gate_en: 1,    //  4
    reg_hdmirx_comm_esm_clk_gate_en: 1,    //  5
    reg_hdmirx_cr_para_clk_gate_en: 1,    //   6
    reg_hdmirx_prt1_aud_clk_gate_en: 1,    //  7
    reg_hdmirx_prt1_frl_clk_gate_en: 1,    //  8
    reg_hdmirx_prt1_link_clk_gate_en: 1,    //  9
    reg_hdmirx_prt1_tmdsqp_clk_gate_en: 1,    //  10
    reg_hdmirx_prt2_aud_clk_gate_en: 1,    //  11
    reg_hdmirx_prt2_frl_clk_gate_en: 1,    //  12
    reg_hdmirx_prt2_link_clk_gate_en: 1,    //  13
    reg_hdmirx_prt2_tmdsqp_clk_gate_en: 1,    //  14
    reg_hdmirx_prt3_aud_clk_gate_en: 1,    //  15
    reg_hdmirx_prt3_earc_aud_clk_gate_en: 1,    //  16
    reg_hdmirx_prt3_earc_bp_clk_gate_en: 1,    //  17
    reg_hdmirx_prt3_frl_clk_gate_en: 1,    //  18
    reg_hdmirx_prt3_link_clk_gate_en: 1,    //  19
    reg_hdmirx_prt3_tmdsqp_clk_gate_en: 1,    //  20
    reg_hdmirx_prt4_aud_clk_gate_en: 1,    //  21
    reg_hdmirx_prt4_frl_clk_gate_en: 1,    //  22
    reg_hdmirx_prt4_link_clk_gate_en: 1,    //  23
    reg_hdmirx_prt4_tmdsqp_clk_gate_en: 1,    //  24
    reg_hdmirx_ref_clk_gate_en:  1,    //     25
    reg_hdmirx_sapb_clk_gate_en: 1,    //     26
                              :  5;    //  31:27 reserved
}SCRG_CTRL_HDMI_CRG_HDMI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_000C    crg_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_f_hdmi_0_hdmirx_prt1_main_bnd_n: 1,    //  0
    reg_soft_rst_f_hdmi_1_hdmirx_prt2_main_bnd_n: 1,    //  1
    reg_soft_rst_f_hdmi_2_hdmirx_prt3_main_bnd_n: 1,    //  2
    reg_soft_rst_f_hdmi_3_hdmirx_prt4_main_bnd_n: 1,    //  3
    reg_soft_rst_hdmirx_esm_n :  1,    //      4
    reg_soft_rst_hdmirx_prt1_aud_n: 1,    //   5
    reg_soft_rst_hdmirx_prt1_base_n: 1,    //  6
    reg_soft_rst_hdmirx_prt1_frl_g_n: 1,    //  7
    reg_soft_rst_hdmirx_prt1_frl_n: 1,    //   8
    reg_soft_rst_hdmirx_prt1_frlpg_n: 1,    //  9
    reg_soft_rst_hdmirx_prt1_link_n: 1,    //  10
    reg_soft_rst_hdmirx_prt1_main_n: 1,    //  11
    reg_soft_rst_hdmirx_prt1_sapb_hdmi_n: 1,    //  12
    reg_soft_rst_hdmirx_prt1_sapb_n: 1,    //  13
    reg_soft_rst_hdmirx_prt1_sapb_top_n: 1,    //  14
    reg_soft_rst_hdmirx_prt1_tmdsqp_n: 1,    //  15
    reg_soft_rst_hdmirx_prt1_tmdsqp_p_n: 1,    //  16
    reg_soft_rst_hdmirx_prt1_tmdsqp_v_n: 1,    //  17
    reg_soft_rst_hdmirx_prt2_aud_n: 1,    //  18
    reg_soft_rst_hdmirx_prt2_base_n: 1,    //  19
    reg_soft_rst_hdmirx_prt2_frl_g_n: 1,    //  20
    reg_soft_rst_hdmirx_prt2_frl_n: 1,    //  21
    reg_soft_rst_hdmirx_prt2_frlpg_n: 1,    //  22
    reg_soft_rst_hdmirx_prt2_link_n: 1,    //  23
    reg_soft_rst_hdmirx_prt2_main_n: 1,    //  24
    reg_soft_rst_hdmirx_prt2_sapb_hdmi_n: 1,    //  25
    reg_soft_rst_hdmirx_prt2_sapb_n: 1,    //  26
    reg_soft_rst_hdmirx_prt2_sapb_top_n: 1,    //  27
    reg_soft_rst_hdmirx_prt2_tmdsqp_n: 1,    //  28
    reg_soft_rst_hdmirx_prt2_tmdsqp_p_n: 1,    //  29
    reg_soft_rst_hdmirx_prt2_tmdsqp_v_n: 1,    //  30
    reg_soft_rst_hdmirx_prt3_aud_n: 1;    //  31
}SCRG_CTRL_HDMI_CRG_HDMI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0010    crg_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_hdmirx_prt3_base_n: 1,    //  0
    reg_soft_rst_hdmirx_prt3_frl_g_n: 1,    //  1
    reg_soft_rst_hdmirx_prt3_frl_n: 1,    //   2
    reg_soft_rst_hdmirx_prt3_frlpg_n: 1,    //  3
    reg_soft_rst_hdmirx_prt3_link_n: 1,    //  4
    reg_soft_rst_hdmirx_prt3_main_n: 1,    //  5
    reg_soft_rst_hdmirx_prt3_sapb_hdmi_n: 1,    //  6
    reg_soft_rst_hdmirx_prt3_sapb_n: 1,    //  7
    reg_soft_rst_hdmirx_prt3_sapb_top_n: 1,    //  8
    reg_soft_rst_hdmirx_prt3_tmdsqp_n: 1,    //  9
    reg_soft_rst_hdmirx_prt3_tmdsqp_p_n: 1,    //  10
    reg_soft_rst_hdmirx_prt3_tmdsqp_v_n: 1,    //  11
    reg_soft_rst_hdmirx_prt4_aud_n: 1,    //  12
    reg_soft_rst_hdmirx_prt4_base_n: 1,    //  13
    reg_soft_rst_hdmirx_prt4_frl_g_n: 1,    //  14
    reg_soft_rst_hdmirx_prt4_frl_n: 1,    //  15
    reg_soft_rst_hdmirx_prt4_frlpg_n: 1,    //  16
    reg_soft_rst_hdmirx_prt4_link_n: 1,    //  17
    reg_soft_rst_hdmirx_prt4_main_n: 1,    //  18
    reg_soft_rst_hdmirx_prt4_sapb_hdmi_n: 1,    //  19
    reg_soft_rst_hdmirx_prt4_sapb_n: 1,    //  20
    reg_soft_rst_hdmirx_prt4_sapb_top_n: 1,    //  21
    reg_soft_rst_hdmirx_prt4_tmdsqp_n: 1,    //  22
    reg_soft_rst_hdmirx_prt4_tmdsqp_p_n: 1,    //  23
    reg_soft_rst_hdmirx_prt4_tmdsqp_v_n: 1,    //  24
    reg_soft_rst_hdmirx_sapb_n:  1,    //     25
    reg_soft_rst_p_hdmi_0_axi_bnd_n: 1,    //  26
    reg_soft_rst_x_hdmi_0_axi_bnd_n: 1,    //  27
    reg_soft_rst_x_hdmi_0_axi_n: 1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_HDMI_CRG_HDMI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0014    crg_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_i2c_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt1_aud_clk_sel: 3,    //   6: 4
                              :  1,    //      7 reserved
    reg_hdmirx_prt2_aud_clk_sel: 3,    //  10: 8
                              :  1,    //     11 reserved
    reg_earc_extern_aud_clk_sel: 3,    //  14:12
                              :  1,    //     15 reserved
    reg_hdmirx_prt3_aud_clk_sel: 3,    //  18:16
                              :  1,    //     19 reserved
    reg_hdmirx_prt3_earc_aud_clk_sel: 3,    //  22:20
                              :  1,    //     23 reserved
    reg_hdmirx_prt4_aud_clk_sel: 3,    //  26:24
                              :  5;    //  31:27 reserved
}SCRG_CTRL_HDMI_CRG_HDMI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0018    crg_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_comm_esm_clk_skip_ctrl: 9,    //  8:0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HDMI_CRG_HDMI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_001C    crg_hdmi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_ref_clk_skip_ctrl: 9,    //  8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HDMI_CRG_HDMI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0020    crg_hdmi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_sapb_clk_skip_ctrl: 9,    //  8:0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_HDMI_CRG_HDMI08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDMI_CRG_HDMI00_O22A0_T        crg_hdmi00 ;             // 0x24_0000
    SCRG_CTRL_HDMI_CRG_HDMI01_O22A0_T        crg_hdmi01 ;             // 0x24_0004
    SCRG_CTRL_HDMI_CRG_HDMI02_O22A0_T        crg_hdmi02 ;             // 0x24_0008
    SCRG_CTRL_HDMI_CRG_HDMI03_O22A0_T        crg_hdmi03 ;             // 0x24_000C
    SCRG_CTRL_HDMI_CRG_HDMI04_O22A0_T        crg_hdmi04 ;             // 0x24_0010
    SCRG_CTRL_HDMI_CRG_HDMI05_O22A0_T        crg_hdmi05 ;             // 0x24_0014
    SCRG_CTRL_HDMI_CRG_HDMI06_O22A0_T        crg_hdmi06 ;             // 0x24_0018
    SCRG_CTRL_HDMI_CRG_HDMI07_O22A0_T        crg_hdmi07 ;             // 0x24_001C
    SCRG_CTRL_HDMI_CRG_HDMI08_O22A0_T        crg_hdmi08 ;             // 0x24_0020
}SCRG_CTRL_HDMI_REG_O22A0_T;
/* 9 regs */

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

#define SCRG_CTRL_HDMI_CRG_HDMI00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDMI_CRG_HDMI01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDMI_CRG_HDMI02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDMI_CRG_HDMI03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDMI_CRG_HDMI04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_HDMI_CRG_HDMI05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define SCRG_CTRL_HDMI_CRG_HDMI06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define SCRG_CTRL_HDMI_CRG_HDMI07_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define SCRG_CTRL_HDMI_CRG_HDMI08_O22A0_T_OFF                     (BASEADDRESS+0x0020)

/*-----------------------------------------------------------------------------------------
    0x24_0000    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDMI_CRG_HDMI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0004    crg_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDMI_CRG_HDMI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0008    crg_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_hdmi1_mclk_gate_en: 1;    //  0
    UINT32 reg_aud_hdmi2_mclk_gate_en: 1;    //  1
    UINT32 reg_aud_hdmi3_mclk_gate_en: 1;    //  2
    UINT32 reg_aud_hdmi4_mclk_gate_en: 1;    //  3
    UINT32 reg_earc_extern_aud_clk_gate_en: 1;    //  4
    UINT32 reg_hdmirx_comm_esm_clk_gate_en: 1;    //  5
    UINT32 reg_hdmirx_cr_para_clk_gate_en: 1;    //  6
    UINT32 reg_hdmirx_prt1_aud_clk_gate_en: 1;    //  7
    UINT32 reg_hdmirx_prt1_frl_clk_gate_en: 1;    //  8
    UINT32 reg_hdmirx_prt1_link_clk_gate_en: 1;    //  9
    UINT32 reg_hdmirx_prt1_tmdsqp_clk_gate_en: 1;    //  10
    UINT32 reg_hdmirx_prt2_aud_clk_gate_en: 1;    //  11
    UINT32 reg_hdmirx_prt2_frl_clk_gate_en: 1;    //  12
    UINT32 reg_hdmirx_prt2_link_clk_gate_en: 1;    //  13
    UINT32 reg_hdmirx_prt2_tmdsqp_clk_gate_en: 1;    //  14
    UINT32 reg_hdmirx_prt3_aud_clk_gate_en: 1;    //  15
    UINT32 reg_hdmirx_prt3_earc_aud_clk_gate_en: 1;    //  16
    UINT32 reg_hdmirx_prt3_earc_bp_clk_gate_en: 1;    //  17
    UINT32 reg_hdmirx_prt3_frl_clk_gate_en: 1;    //  18
    UINT32 reg_hdmirx_prt3_link_clk_gate_en: 1;    //  19
    UINT32 reg_hdmirx_prt3_tmdsqp_clk_gate_en: 1;    //  20
    UINT32 reg_hdmirx_prt4_aud_clk_gate_en: 1;    //  21
    UINT32 reg_hdmirx_prt4_frl_clk_gate_en: 1;    //  22
    UINT32 reg_hdmirx_prt4_link_clk_gate_en: 1;    //  23
    UINT32 reg_hdmirx_prt4_tmdsqp_clk_gate_en: 1;    //  24
    UINT32 reg_hdmirx_ref_clk_gate_en: 1;    //  25
    UINT32 reg_hdmirx_sapb_clk_gate_en: 1;    //  26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_000C    crg_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_f_hdmi_0_hdmirx_prt1_main_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_f_hdmi_1_hdmirx_prt2_main_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_f_hdmi_2_hdmirx_prt3_main_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_hdmi_3_hdmirx_prt4_main_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_hdmirx_esm_n: 1;    //  4
    UINT32 reg_soft_rst_hdmirx_prt1_aud_n: 1;    //  5
    UINT32 reg_soft_rst_hdmirx_prt1_base_n: 1;    //  6
    UINT32 reg_soft_rst_hdmirx_prt1_frl_g_n: 1;    //  7
    UINT32 reg_soft_rst_hdmirx_prt1_frl_n: 1;    //  8
    UINT32 reg_soft_rst_hdmirx_prt1_frlpg_n: 1;    //  9
    UINT32 reg_soft_rst_hdmirx_prt1_link_n: 1;    //  10
    UINT32 reg_soft_rst_hdmirx_prt1_main_n: 1;    //  11
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_hdmi_n: 1;    //  12
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_n: 1;    //  13
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_top_n: 1;    //  14
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_n: 1;    //  15
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_p_n: 1;    //  16
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_v_n: 1;    //  17
    UINT32 reg_soft_rst_hdmirx_prt2_aud_n: 1;    //  18
    UINT32 reg_soft_rst_hdmirx_prt2_base_n: 1;    //  19
    UINT32 reg_soft_rst_hdmirx_prt2_frl_g_n: 1;    //  20
    UINT32 reg_soft_rst_hdmirx_prt2_frl_n: 1;    //  21
    UINT32 reg_soft_rst_hdmirx_prt2_frlpg_n: 1;    //  22
    UINT32 reg_soft_rst_hdmirx_prt2_link_n: 1;    //  23
    UINT32 reg_soft_rst_hdmirx_prt2_main_n: 1;    //  24
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_hdmi_n: 1;    //  25
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_n: 1;    //  26
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_top_n: 1;    //  27
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_n: 1;    //  28
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_p_n: 1;    //  29
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_v_n: 1;    //  30
    UINT32 reg_soft_rst_hdmirx_prt3_aud_n: 1;    //  31
    };
}SCRG_CTRL_HDMI_CRG_HDMI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0010    crg_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_hdmirx_prt3_base_n: 1;    //  0
    UINT32 reg_soft_rst_hdmirx_prt3_frl_g_n: 1;    //  1
    UINT32 reg_soft_rst_hdmirx_prt3_frl_n: 1;    //  2
    UINT32 reg_soft_rst_hdmirx_prt3_frlpg_n: 1;    //  3
    UINT32 reg_soft_rst_hdmirx_prt3_link_n: 1;    //  4
    UINT32 reg_soft_rst_hdmirx_prt3_main_n: 1;    //  5
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_hdmi_n: 1;    //  6
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_n: 1;    //  7
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_top_n: 1;    //  8
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_n: 1;    //  9
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_p_n: 1;    //  10
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_v_n: 1;    //  11
    UINT32 reg_soft_rst_hdmirx_prt4_aud_n: 1;    //  12
    UINT32 reg_soft_rst_hdmirx_prt4_base_n: 1;    //  13
    UINT32 reg_soft_rst_hdmirx_prt4_frl_g_n: 1;    //  14
    UINT32 reg_soft_rst_hdmirx_prt4_frl_n: 1;    //  15
    UINT32 reg_soft_rst_hdmirx_prt4_frlpg_n: 1;    //  16
    UINT32 reg_soft_rst_hdmirx_prt4_link_n: 1;    //  17
    UINT32 reg_soft_rst_hdmirx_prt4_main_n: 1;    //  18
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_hdmi_n: 1;    //  19
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_n: 1;    //  20
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_top_n: 1;    //  21
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_n: 1;    //  22
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_p_n: 1;    //  23
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_v_n: 1;    //  24
    UINT32 reg_soft_rst_hdmirx_sapb_n: 1;    //  25
    UINT32 reg_soft_rst_p_hdmi_0_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_x_hdmi_0_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_x_hdmi_0_axi_n: 1;    //  28
    UINT32 resvd00            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0014    crg_hdmi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_i2c_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt1_aud_clk_sel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_hdmirx_prt2_aud_clk_sel: 3;    //  10:8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_earc_extern_aud_clk_sel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_hdmirx_prt3_aud_clk_sel: 3;    //  18:16
    UINT32 resvd04            :  1;    //     19 reserved
    UINT32 reg_hdmirx_prt3_earc_aud_clk_sel: 3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_hdmirx_prt4_aud_clk_sel: 3;    //  26:24
    UINT32 resvd06            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0018    crg_hdmi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_comm_esm_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_001C    crg_hdmi07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_ref_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x24_0020    crg_hdmi08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_sapb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDMI_CRG_HDMI00_O22A0_T        crg_hdmi00 ;             // 0x24_0000
    SCRG_CTRL_HDMI_CRG_HDMI01_O22A0_T        crg_hdmi01 ;             // 0x24_0004
    SCRG_CTRL_HDMI_CRG_HDMI02_O22A0_T        crg_hdmi02 ;             // 0x24_0008
    SCRG_CTRL_HDMI_CRG_HDMI03_O22A0_T        crg_hdmi03 ;             // 0x24_000C
    SCRG_CTRL_HDMI_CRG_HDMI04_O22A0_T        crg_hdmi04 ;             // 0x24_0010
    SCRG_CTRL_HDMI_CRG_HDMI05_O22A0_T        crg_hdmi05 ;             // 0x24_0014
    SCRG_CTRL_HDMI_CRG_HDMI06_O22A0_T        crg_hdmi06 ;             // 0x24_0018
    SCRG_CTRL_HDMI_CRG_HDMI07_O22A0_T        crg_hdmi07 ;             // 0x24_001C
    SCRG_CTRL_HDMI_CRG_HDMI08_O22A0_T        crg_hdmi08 ;             // 0x24_0020
}SCRG_CTRL_HDMI_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

