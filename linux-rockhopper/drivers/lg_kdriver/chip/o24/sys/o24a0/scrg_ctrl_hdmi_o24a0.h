#ifndef _SCRG_CTRL_HDMI_REG_O24A0_H_
#define _SCRG_CTRL_HDMI_REG_O24A0_H_

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
    0xC8D4_0000    crg_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDMI_CRG_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0004    crg_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDMI_CRG_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0008    crg_hdmi2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_comm_esm_clk_gate_en: 1,    //  0
    reg_hdmirx_cr_para_clk_gate_en: 1,    //   1
    reg_hdmirx_prt1_aud_clk_gate_en: 1,    //  2
    reg_hdmirx_prt1_frl_clk_gate_en: 1,    //  3
    reg_hdmirx_prt1_link_clk_gate_en: 1,    //  4
    reg_hdmirx_prt1_tmdsqp_clk_gate_en: 1,    //  5
    reg_hdmirx_prt2_aud_clk_gate_en: 1,    //  6
    reg_hdmirx_prt2_earc_aud_clk_gate_en: 1,    //  7
    reg_hdmirx_prt2_earc_bp_clk_gate_en: 1,    //  8
    reg_hdmirx_prt2_frl_clk_gate_en: 1,    //  9
    reg_hdmirx_prt2_link_clk_gate_en: 1,    //  10
    reg_hdmirx_prt2_tmdsqp_clk_gate_en: 1,    //  11
    reg_hdmirx_prt3_aud_clk_gate_en: 1,    //  12
    reg_hdmirx_prt3_frl_clk_gate_en: 1,    //  13
    reg_hdmirx_prt3_link_clk_gate_en: 1,    //  14
    reg_hdmirx_prt3_tmdsqp_clk_gate_en: 1,    //  15
    reg_hdmirx_prt4_aud_clk_gate_en: 1,    //  16
    reg_hdmirx_prt4_frl_clk_gate_en: 1,    //  17
    reg_hdmirx_prt4_link_clk_gate_en: 1,    //  18
    reg_hdmirx_prt4_tmdsqp_clk_gate_en: 1,    //  19
    reg_hdmirx_ref_clk_gate_en:  1,    //     20
    reg_hdmirx_sapb_clk_gate_en: 1,    //     21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_HDMI_CRG_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_000C    crg_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_f_hdmi_0_hdmirx_prt1_main_bnd_n: 1,    //  0
    reg_soft_rst_f_hdmi_1_hdmirx_prt2_main_bnd_n: 1,    //  1
    reg_soft_rst_f_hdmi_2_hdmirx_prt3_main_bnd_n: 1,    //  2
    reg_soft_rst_f_hdmi_3_hdmirx_prt4_main_bnd_n: 1,    //  3
    reg_soft_rst_f_hdmiipw_0_hdmirx_prt1_main_bnd_n: 1,    //  4
    reg_soft_rst_f_hdmiipw_1_hdmirx_prt2_main_bnd_n: 1,    //  5
    reg_soft_rst_f_hdmiipw_2_hdmirx_prt3_main_bnd_n: 1,    //  6
    reg_soft_rst_f_hdmiipw_3_hdmirx_prt4_main_bnd_n: 1,    //  7
    reg_soft_rst_hdmirx_esm_n :  1,    //      8
    reg_soft_rst_hdmirx_prt1_aud_n: 1,    //   9
    reg_soft_rst_hdmirx_prt1_base_n: 1,    //  10
    reg_soft_rst_hdmirx_prt1_frl_g_n: 1,    //  11
    reg_soft_rst_hdmirx_prt1_frl_n: 1,    //  12
    reg_soft_rst_hdmirx_prt1_frlpg_n: 1,    //  13
    reg_soft_rst_hdmirx_prt1_link_n: 1,    //  14
    reg_soft_rst_hdmirx_prt1_main_n: 1,    //  15
    reg_soft_rst_hdmirx_prt1_sapb_hdmi_n: 1,    //  16
    reg_soft_rst_hdmirx_prt1_sapb_n: 1,    //  17
    reg_soft_rst_hdmirx_prt1_sapb_top_n: 1,    //  18
    reg_soft_rst_hdmirx_prt1_tmdsqp_n: 1,    //  19
    reg_soft_rst_hdmirx_prt1_tmdsqp_p_n: 1,    //  20
    reg_soft_rst_hdmirx_prt1_tmdsqp_v_n: 1,    //  21
    reg_soft_rst_hdmirx_prt2_aud_n: 1,    //  22
    reg_soft_rst_hdmirx_prt2_base_n: 1,    //  23
    reg_soft_rst_hdmirx_prt2_frl_g_n: 1,    //  24
    reg_soft_rst_hdmirx_prt2_frl_n: 1,    //  25
    reg_soft_rst_hdmirx_prt2_frlpg_n: 1,    //  26
    reg_soft_rst_hdmirx_prt2_link_n: 1,    //  27
    reg_soft_rst_hdmirx_prt2_main_n: 1,    //  28
    reg_soft_rst_hdmirx_prt2_sapb_hdmi_n: 1,    //  29
    reg_soft_rst_hdmirx_prt2_sapb_n: 1,    //  30
    reg_soft_rst_hdmirx_prt2_sapb_top_n: 1;    //  31
}SCRG_CTRL_HDMI_CRG_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0010    crg_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_hdmirx_prt2_tmdsqp_n: 1,    //  0
    reg_soft_rst_hdmirx_prt2_tmdsqp_p_n: 1,    //  1
    reg_soft_rst_hdmirx_prt2_tmdsqp_v_n: 1,    //  2
    reg_soft_rst_hdmirx_prt3_aud_n: 1,    //   3
    reg_soft_rst_hdmirx_prt3_base_n: 1,    //  4
    reg_soft_rst_hdmirx_prt3_frl_g_n: 1,    //  5
    reg_soft_rst_hdmirx_prt3_frl_n: 1,    //   6
    reg_soft_rst_hdmirx_prt3_frlpg_n: 1,    //  7
    reg_soft_rst_hdmirx_prt3_link_n: 1,    //  8
    reg_soft_rst_hdmirx_prt3_main_n: 1,    //  9
    reg_soft_rst_hdmirx_prt3_sapb_hdmi_n: 1,    //  10
    reg_soft_rst_hdmirx_prt3_sapb_n: 1,    //  11
    reg_soft_rst_hdmirx_prt3_sapb_top_n: 1,    //  12
    reg_soft_rst_hdmirx_prt3_tmdsqp_n: 1,    //  13
    reg_soft_rst_hdmirx_prt3_tmdsqp_p_n: 1,    //  14
    reg_soft_rst_hdmirx_prt3_tmdsqp_v_n: 1,    //  15
    reg_soft_rst_hdmirx_prt4_aud_n: 1,    //  16
    reg_soft_rst_hdmirx_prt4_base_n: 1,    //  17
    reg_soft_rst_hdmirx_prt4_frl_g_n: 1,    //  18
    reg_soft_rst_hdmirx_prt4_frl_n: 1,    //  19
    reg_soft_rst_hdmirx_prt4_frlpg_n: 1,    //  20
    reg_soft_rst_hdmirx_prt4_link_n: 1,    //  21
    reg_soft_rst_hdmirx_prt4_main_n: 1,    //  22
    reg_soft_rst_hdmirx_prt4_sapb_hdmi_n: 1,    //  23
    reg_soft_rst_hdmirx_prt4_sapb_n: 1,    //  24
    reg_soft_rst_hdmirx_prt4_sapb_top_n: 1,    //  25
    reg_soft_rst_hdmirx_prt4_tmdsqp_n: 1,    //  26
    reg_soft_rst_hdmirx_prt4_tmdsqp_p_n: 1,    //  27
    reg_soft_rst_hdmirx_prt4_tmdsqp_v_n: 1,    //  28
    reg_soft_rst_hdmirx_sapb_n:  1,    //     29
    reg_soft_rst_p_hdmi_0_axi_bnd_n: 1,    //  30
    reg_soft_rst_x_hdmi_0_axi_bnd_n: 1;    //  31
}SCRG_CTRL_HDMI_CRG_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0014    crg_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_hdmi_0_axi_n: 1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_HDMI_CRG_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0018    crg_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_aud_clk_sel: 3,    //   2: 0
                              :  1,    //      3 reserved
    reg_hdmirx_prt2_aud_clk_sel: 3,    //   6: 4
                              :  1,    //      7 reserved
    reg_hdmirx_prt2_earc_aud_clk_sel: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_hdmirx_prt3_aud_clk_sel: 3,    //  14:12
                              :  1,    //     15 reserved
    reg_hdmirx_prt4_aud_clk_sel: 3,    //  18:16
                              : 13;    //  31:19 reserved
}SCRG_CTRL_HDMI_CRG_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDMI_CRG_HDMI0_O24A0_T    crg_hdmi0 ;             // 0xC8D4_0000
    SCRG_CTRL_HDMI_CRG_HDMI1_O24A0_T    crg_hdmi1 ;             // 0xC8D4_0004
    SCRG_CTRL_HDMI_CRG_HDMI2_O24A0_T    crg_hdmi2 ;             // 0xC8D4_0008
    SCRG_CTRL_HDMI_CRG_HDMI3_O24A0_T    crg_hdmi3 ;             // 0xC8D4_000C
    SCRG_CTRL_HDMI_CRG_HDMI4_O24A0_T    crg_hdmi4 ;             // 0xC8D4_0010
    SCRG_CTRL_HDMI_CRG_HDMI5_O24A0_T    crg_hdmi5 ;             // 0xC8D4_0014
    SCRG_CTRL_HDMI_CRG_HDMI6_O24A0_T    crg_hdmi6 ;             // 0xC8D4_0018
}SCRG_CTRL_HDMI_REG_O24A0_T;
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

#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI4_O24A0_T_OFF                (BASEADDRESS+0x0010)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI5_O24A0_T_OFF                (BASEADDRESS+0x0014)
#define SCRG_CTRL_HDMI_CRG_O24A0_HDMI6_O24A0_T_OFF                (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC8D4_0000    crg_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDMI_CRG_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0004    crg_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDMI_CRG_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0008    crg_hdmi2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_comm_esm_clk_gate_en: 1;    //  0
    UINT32 reg_hdmirx_cr_para_clk_gate_en: 1;    //  1
    UINT32 reg_hdmirx_prt1_aud_clk_gate_en: 1;    //  2
    UINT32 reg_hdmirx_prt1_frl_clk_gate_en: 1;    //  3
    UINT32 reg_hdmirx_prt1_link_clk_gate_en: 1;    //  4
    UINT32 reg_hdmirx_prt1_tmdsqp_clk_gate_en: 1;    //  5
    UINT32 reg_hdmirx_prt2_aud_clk_gate_en: 1;    //  6
    UINT32 reg_hdmirx_prt2_earc_aud_clk_gate_en: 1;    //  7
    UINT32 reg_hdmirx_prt2_earc_bp_clk_gate_en: 1;    //  8
    UINT32 reg_hdmirx_prt2_frl_clk_gate_en: 1;    //  9
    UINT32 reg_hdmirx_prt2_link_clk_gate_en: 1;    //  10
    UINT32 reg_hdmirx_prt2_tmdsqp_clk_gate_en: 1;    //  11
    UINT32 reg_hdmirx_prt3_aud_clk_gate_en: 1;    //  12
    UINT32 reg_hdmirx_prt3_frl_clk_gate_en: 1;    //  13
    UINT32 reg_hdmirx_prt3_link_clk_gate_en: 1;    //  14
    UINT32 reg_hdmirx_prt3_tmdsqp_clk_gate_en: 1;    //  15
    UINT32 reg_hdmirx_prt4_aud_clk_gate_en: 1;    //  16
    UINT32 reg_hdmirx_prt4_frl_clk_gate_en: 1;    //  17
    UINT32 reg_hdmirx_prt4_link_clk_gate_en: 1;    //  18
    UINT32 reg_hdmirx_prt4_tmdsqp_clk_gate_en: 1;    //  19
    UINT32 reg_hdmirx_ref_clk_gate_en: 1;    //  20
    UINT32 reg_hdmirx_sapb_clk_gate_en: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_000C    crg_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_f_hdmi_0_hdmirx_prt1_main_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_f_hdmi_1_hdmirx_prt2_main_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_f_hdmi_2_hdmirx_prt3_main_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_hdmi_3_hdmirx_prt4_main_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_hdmiipw_0_hdmirx_prt1_main_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_hdmiipw_1_hdmirx_prt2_main_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_hdmiipw_2_hdmirx_prt3_main_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_hdmiipw_3_hdmirx_prt4_main_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_hdmirx_esm_n: 1;    //  8
    UINT32 reg_soft_rst_hdmirx_prt1_aud_n: 1;    //  9
    UINT32 reg_soft_rst_hdmirx_prt1_base_n: 1;    //  10
    UINT32 reg_soft_rst_hdmirx_prt1_frl_g_n: 1;    //  11
    UINT32 reg_soft_rst_hdmirx_prt1_frl_n: 1;    //  12
    UINT32 reg_soft_rst_hdmirx_prt1_frlpg_n: 1;    //  13
    UINT32 reg_soft_rst_hdmirx_prt1_link_n: 1;    //  14
    UINT32 reg_soft_rst_hdmirx_prt1_main_n: 1;    //  15
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_hdmi_n: 1;    //  16
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_n: 1;    //  17
    UINT32 reg_soft_rst_hdmirx_prt1_sapb_top_n: 1;    //  18
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_n: 1;    //  19
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_p_n: 1;    //  20
    UINT32 reg_soft_rst_hdmirx_prt1_tmdsqp_v_n: 1;    //  21
    UINT32 reg_soft_rst_hdmirx_prt2_aud_n: 1;    //  22
    UINT32 reg_soft_rst_hdmirx_prt2_base_n: 1;    //  23
    UINT32 reg_soft_rst_hdmirx_prt2_frl_g_n: 1;    //  24
    UINT32 reg_soft_rst_hdmirx_prt2_frl_n: 1;    //  25
    UINT32 reg_soft_rst_hdmirx_prt2_frlpg_n: 1;    //  26
    UINT32 reg_soft_rst_hdmirx_prt2_link_n: 1;    //  27
    UINT32 reg_soft_rst_hdmirx_prt2_main_n: 1;    //  28
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_hdmi_n: 1;    //  29
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_n: 1;    //  30
    UINT32 reg_soft_rst_hdmirx_prt2_sapb_top_n: 1;    //  31
    };
}SCRG_CTRL_HDMI_CRG_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0010    crg_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_n: 1;    //  0
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_p_n: 1;    //  1
    UINT32 reg_soft_rst_hdmirx_prt2_tmdsqp_v_n: 1;    //  2
    UINT32 reg_soft_rst_hdmirx_prt3_aud_n: 1;    //  3
    UINT32 reg_soft_rst_hdmirx_prt3_base_n: 1;    //  4
    UINT32 reg_soft_rst_hdmirx_prt3_frl_g_n: 1;    //  5
    UINT32 reg_soft_rst_hdmirx_prt3_frl_n: 1;    //  6
    UINT32 reg_soft_rst_hdmirx_prt3_frlpg_n: 1;    //  7
    UINT32 reg_soft_rst_hdmirx_prt3_link_n: 1;    //  8
    UINT32 reg_soft_rst_hdmirx_prt3_main_n: 1;    //  9
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_hdmi_n: 1;    //  10
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_n: 1;    //  11
    UINT32 reg_soft_rst_hdmirx_prt3_sapb_top_n: 1;    //  12
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_n: 1;    //  13
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_p_n: 1;    //  14
    UINT32 reg_soft_rst_hdmirx_prt3_tmdsqp_v_n: 1;    //  15
    UINT32 reg_soft_rst_hdmirx_prt4_aud_n: 1;    //  16
    UINT32 reg_soft_rst_hdmirx_prt4_base_n: 1;    //  17
    UINT32 reg_soft_rst_hdmirx_prt4_frl_g_n: 1;    //  18
    UINT32 reg_soft_rst_hdmirx_prt4_frl_n: 1;    //  19
    UINT32 reg_soft_rst_hdmirx_prt4_frlpg_n: 1;    //  20
    UINT32 reg_soft_rst_hdmirx_prt4_link_n: 1;    //  21
    UINT32 reg_soft_rst_hdmirx_prt4_main_n: 1;    //  22
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_hdmi_n: 1;    //  23
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_n: 1;    //  24
    UINT32 reg_soft_rst_hdmirx_prt4_sapb_top_n: 1;    //  25
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_n: 1;    //  26
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_p_n: 1;    //  27
    UINT32 reg_soft_rst_hdmirx_prt4_tmdsqp_v_n: 1;    //  28
    UINT32 reg_soft_rst_hdmirx_sapb_n: 1;    //  29
    UINT32 reg_soft_rst_p_hdmi_0_axi_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_x_hdmi_0_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_HDMI_CRG_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0014    crg_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_hdmi_0_axi_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_0018    crg_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_aud_clk_sel: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_hdmirx_prt2_aud_clk_sel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_hdmirx_prt2_earc_aud_clk_sel: 3;    //  10:8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_hdmirx_prt3_aud_clk_sel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_hdmirx_prt4_aud_clk_sel: 3;    //  18:16
    UINT32 resvd04            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_HDMI_CRG_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDMI_CRG_HDMI0_O24A0_T    crg_hdmi0 ;             // 0xC8D4_0000
    SCRG_CTRL_HDMI_CRG_HDMI1_O24A0_T    crg_hdmi1 ;             // 0xC8D4_0004
    SCRG_CTRL_HDMI_CRG_HDMI2_O24A0_T    crg_hdmi2 ;             // 0xC8D4_0008
    SCRG_CTRL_HDMI_CRG_HDMI3_O24A0_T    crg_hdmi3 ;             // 0xC8D4_000C
    SCRG_CTRL_HDMI_CRG_HDMI4_O24A0_T    crg_hdmi4 ;             // 0xC8D4_0010
    SCRG_CTRL_HDMI_CRG_HDMI5_O24A0_T    crg_hdmi5 ;             // 0xC8D4_0014
    SCRG_CTRL_HDMI_CRG_HDMI6_O24A0_T    crg_hdmi6 ;             // 0xC8D4_0018
}SCRG_CTRL_HDMI_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_HDMI_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

