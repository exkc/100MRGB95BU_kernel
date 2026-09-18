#ifndef _BND_CTRL_EDID_REG_H_
#define _BND_CTRL_EDID_REG_H_

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
    0xCA43_2000    syn_edid000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hpd_out_prt1_edid     :  1,    //      0
    reg_hpd_out_prt2_edid     :  1,    //      1
    reg_hpd_out_prt3_edid     :  1,    //      2
    reg_hpd_out_prt4_edid     :  1,    //      3
    reg_hpd_out_prt1          :  1,    //      4
    reg_hpd_out_prt2          :  1,    //      5
    reg_hpd_out_prt3          :  1,    //      6
    reg_hpd_out_prt4          :  1,    //      7
    reg_hpd_out_prt1_polarity_ctrl: 1,    //   8
    reg_hpd_out_prt2_polarity_ctrl: 1,    //   9
    reg_hpd_out_prt3_polarity_ctrl: 1,    //  10
    reg_hpd_out_prt4_polarity_ctrl: 1,    //  11
                              :  1,    //     12 reserved
    reg_hpd_sel               :  2,    //  14:13
                              : 17;    //  31:15 reserved
}BND_CTRL_EDID_SYN_EDID000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2004    syn_edid001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}BND_CTRL_EDID_SYN_EDID001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2014    pad_xin ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_xin__rd1          :  1,    //      0
    reg_pad_xin__rd0          :  1,    //      1
    reg_pad_xin__ref1         :  1,    //      2
    reg_pad_xin__ref0         :  1,    //      3
    reg_pad_xin__ds3          :  1,    //      4
    reg_pad_xin__ds2          :  1,    //      5
    reg_pad_xin__ds1          :  1,    //      6
    reg_pad_xin__ds0          :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_EDID_PAD_XIN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2020    earc_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_a          :  6,    //   5: 0
    reg_earc_frpll_frequp     :  1,    //      6
    reg_earc_frpll_auto_freq  :  1,    //      7
    reg_earc_frpll_dsmon      :  1,    //      8
    reg_earc_frpll_syncon     :  1,    //      9
    reg_earc_frpll_lpf_on     :  1,    //     10
    reg_earc_frpll_dsm_limit  :  1,    //     11
    reg_earc_frpll_icp        :  4,    //  15:12
    reg_earc_frpll_icp_g      :  1,    //     16
    reg_earc_frpll_m          :  6,    //  22:17
    reg_earc_frpll_divint     :  9;    //  31:23
}BND_CTRL_EDID_EARC_FRPLL_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2024    earc_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_fcw        : 24,    //  23: 0
    reg_earc_frpll_wakeup_bypass: 1,    //    24
                              :  7;    //  31:25 reserved
}BND_CTRL_EDID_EARC_FRPLL_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2028    earc_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_out_div    :  9,    //   8: 0
    reg_earc_frpll_out2_div   :  9,    //  17: 9
    reg_earc_frpll_out3_div   :  9,    //  26:18
    reg_earc_frpll_in_divrstb :  1,    //     27
    reg_earc_frpll_fout_en    :  1,    //     28
    reg_earc_frpll_fout2_en   :  1,    //     29
    reg_earc_frpll_fin_sel    :  1,    //     30
    reg_earc_frpll_in_divsel  :  1;    //     31
}BND_CTRL_EDID_EARC_FRPLL_02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2030    earc_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_pdb        :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EARC_FRPLL_03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2038    earc_frpll_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_frpll_lock       :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EARC_FRPLL_06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_203C    earc_frpll_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_pll_fcw_mux_sel  :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}BND_CTRL_EDID_EARC_FRPLL_07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2040    earc_frpll_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EARC_FRPLL_08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2050    txp_clkdrv ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txp_clkdrv_bot_pdb    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txp_clkdrv_bot_icon   :  2,    //   5: 4
                              : 10,    //  15: 6 reserved
    reg_txp_clkdrv_top_pdb    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_txp_clkdrv_top_icon   :  2,    //  21:20
                              : 10;    //  31:22 reserved
}BND_CTRL_EDID_TXP_CLKDRV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2060    dpm_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_en         :  1,    //      0
    reg_phy_mon_all_ch        :  1,    //      1
    reg_phy_low_vsen          :  1,    //      2
    reg_phy_dpm_odt           :  1,    //      3
    reg_phy_tx_det_disable    :  4,    //   7: 4
    reg_phy_tx_det_bypass_mode:  4,    //  11: 8
                              :  4,    //  15:12 reserved
    reg_use_pad_for_dpm_tx_det_intr: 1,    //  16
                              : 15;    //  31:17 reserved
}BND_CTRL_EDID_DPM_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2064    dpm_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy1_tx_det_out       :  1,    //      0
    reg_phy2_tx_det_out       :  1,    //      1
    reg_phy3_tx_det_out       :  1,    //      2
    reg_phy4_tx_det_out       :  1,    //      3
    reg_dpm_tx_det_intr_status:  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_EDID_DPM_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2070    clk_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_sel           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_apb_clk_gete_en       :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_EDID_CLK_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2074    edid_soft_rst_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    edid_soft_rst_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_SOFT_RST_MUX_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2078    edid_soft_rst ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_bnd_mx_n :  1,    //      0
    reg_soft_rst_apb_ipw_edid_bnd_n: 1,    //  1
    reg_soft_rst_apb_ipw_edid_ip_ctrl_n: 1,    //  2
                              : 29;    //   31:3 reserved
}BND_CTRL_EDID_EDID_SOFT_RST_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_SYN_EDID000_O22A0_T       syn_edid000;             // 0xCA43_2000
    BND_CTRL_EDID_SYN_EDID001_O22A0_T       syn_edid001;             // 0xCA43_2004
    UINT32                             _rsvd_00[3];             // 0xCA43_2008 ~ 0xCA43_2010
    BND_CTRL_EDID_PAD_XIN_O22A0_T           pad_xin    ;             // 0xCA43_2014
    UINT32                             _rsvd_01[2];             // 0xCA43_2018 ~ 0xCA43_201C
    BND_CTRL_EDID_EARC_FRPLL_00_O22A0_T     earc_frpll_00;           // 0xCA43_2020
    BND_CTRL_EDID_EARC_FRPLL_01_O22A0_T     earc_frpll_01;           // 0xCA43_2024
    BND_CTRL_EDID_EARC_FRPLL_02_O22A0_T     earc_frpll_02;           // 0xCA43_2028
    UINT32                             _rsvd_02[1];             // 0xCA43_202C
    BND_CTRL_EDID_EARC_FRPLL_03_O22A0_T     earc_frpll_03;           // 0xCA43_2030
    UINT32                             _rsvd_03[1];             // 0xCA43_2034
    BND_CTRL_EDID_EARC_FRPLL_06_O22A0_T     earc_frpll_06;           // 0xCA43_2038
    BND_CTRL_EDID_EARC_FRPLL_07_O22A0_T     earc_frpll_07;           // 0xCA43_203C
    BND_CTRL_EDID_EARC_FRPLL_08_O22A0_T     earc_frpll_08;           // 0xCA43_2040
    UINT32                             _rsvd_04[3];             // 0xCA43_2044 ~ 0xCA43_204C
    BND_CTRL_EDID_TXP_CLKDRV_O22A0_T        txp_clkdrv ;             // 0xCA43_2050
    UINT32                             _rsvd_05[3];             // 0xCA43_2054 ~ 0xCA43_205C
    BND_CTRL_EDID_DPM_0_O22A0_T             dpm_0      ;             // 0xCA43_2060
    BND_CTRL_EDID_DPM_1_O22A0_T             dpm_1      ;             // 0xCA43_2064
    UINT32                             _rsvd_06[2];             // 0xCA43_2068 ~ 0xCA43_206C
    BND_CTRL_EDID_CLK_01_O22A0_T            clk_01     ;             // 0xCA43_2070
    BND_CTRL_EDID_EDID_SOFT_RST_MUX_O22A0_T    edid_soft_rst_mux;    // 0xCA43_2074
    BND_CTRL_EDID_EDID_SOFT_RST_O22A0_T     edid_soft_rst;           // 0xCA43_2078
}BND_CTRL_EDID_REG_O22A0_T;
/* 16 regs */

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

#define BND_CTRL_EDID_SYN_EDID000_O22A0_T_OFF                    (BASEADDRESS+0x0000)
#define BND_CTRL_EDID_SYN_EDID001_O22A0_T_OFF                    (BASEADDRESS+0x0004)
#define BND_CTRL_EDID_PAD_XIN_O22A0_T_OFF                        (BASEADDRESS+0x0014)
#define BND_CTRL_EDID_EARC_FRPLL_00_O22A0_T_OFF                  (BASEADDRESS+0x0020)
#define BND_CTRL_EDID_EARC_FRPLL_01_O22A0_T_OFF                  (BASEADDRESS+0x0024)
#define BND_CTRL_EDID_EARC_FRPLL_02_O22A0_T_OFF                  (BASEADDRESS+0x0028)
#define BND_CTRL_EDID_EARC_FRPLL_03_O22A0_T_OFF                  (BASEADDRESS+0x0030)
#define BND_CTRL_EDID_EARC_FRPLL_06_O22A0_T_OFF                  (BASEADDRESS+0x0038)
#define BND_CTRL_EDID_EARC_FRPLL_07_O22A0_T_OFF                  (BASEADDRESS+0x003C)
#define BND_CTRL_EDID_EARC_FRPLL_08_O22A0_T_OFF                  (BASEADDRESS+0x0040)
#define BND_CTRL_EDID_TXP_CLKDRV_O22A0_T_OFF                     (BASEADDRESS+0x0050)
#define BND_CTRL_EDID_DPM_0_O22A0_T_OFF                          (BASEADDRESS+0x0060)
#define BND_CTRL_EDID_DPM_1_O22A0_T_OFF                          (BASEADDRESS+0x0064)
#define BND_CTRL_EDID_CLK_01_O22A0_T_OFF                         (BASEADDRESS+0x0070)
#define BND_CTRL_EDID_EDID_SOFT_RST_MUX_O22A0_T_OFF              (BASEADDRESS+0x0074)
#define BND_CTRL_EDID_EDID_SOFT_RST_O22A0_T_OFF                  (BASEADDRESS+0x0078)

/*-----------------------------------------------------------------------------------------
    0xCA43_2000    syn_edid000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hpd_out_prt1_edid: 1;    //     0
    UINT32 reg_hpd_out_prt2_edid: 1;    //     1
    UINT32 reg_hpd_out_prt3_edid: 1;    //     2
    UINT32 reg_hpd_out_prt4_edid: 1;    //     3
    UINT32 reg_hpd_out_prt1   :  1;    //      4
    UINT32 reg_hpd_out_prt2   :  1;    //      5
    UINT32 reg_hpd_out_prt3   :  1;    //      6
    UINT32 reg_hpd_out_prt4   :  1;    //      7
    UINT32 reg_hpd_out_prt1_polarity_ctrl: 1;    //  8
    UINT32 reg_hpd_out_prt2_polarity_ctrl: 1;    //  9
    UINT32 reg_hpd_out_prt3_polarity_ctrl: 1;    //  10
    UINT32 reg_hpd_out_prt4_polarity_ctrl: 1;    //  11
    UINT32 resvd00            :  1;    //     12 reserved
    UINT32 reg_hpd_sel        :  2;    //  14:13
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}BND_CTRL_EDID_SYN_EDID000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2004    syn_edid001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i2c_edid_gating:  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_i2c_link_gating:  5;    //  12: 8
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}BND_CTRL_EDID_SYN_EDID001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2014    pad_xin ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_xin__rd1   :  1;    //      0
    UINT32 reg_pad_xin__rd0   :  1;    //      1
    UINT32 reg_pad_xin__ref1  :  1;    //      2
    UINT32 reg_pad_xin__ref0  :  1;    //      3
    UINT32 reg_pad_xin__ds3   :  1;    //      4
    UINT32 reg_pad_xin__ds2   :  1;    //      5
    UINT32 reg_pad_xin__ds1   :  1;    //      6
    UINT32 reg_pad_xin__ds0   :  1;    //      7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_EDID_PAD_XIN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2020    earc_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_frpll_a   :  6;    //   5: 0
    UINT32 reg_earc_frpll_frequp: 1;    //     6
    UINT32 reg_earc_frpll_auto_freq: 1;    //  7
    UINT32 reg_earc_frpll_dsmon: 1;    //      8
    UINT32 reg_earc_frpll_syncon: 1;    //     9
    UINT32 reg_earc_frpll_lpf_on: 1;    //    10
    UINT32 reg_earc_frpll_dsm_limit: 1;    //  11
    UINT32 reg_earc_frpll_icp :  4;    //  15:12
    UINT32 reg_earc_frpll_icp_g: 1;    //     16
    UINT32 reg_earc_frpll_m   :  6;    //  22:17
    UINT32 reg_earc_frpll_divint: 9;    //  31:23
    };
}BND_CTRL_EDID_EARC_FRPLL_00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2024    earc_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_frpll_fcw : 24;    //  23: 0
    UINT32 reg_earc_frpll_wakeup_bypass: 1;    //  24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}BND_CTRL_EDID_EARC_FRPLL_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2028    earc_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_frpll_out_div: 9;    //  8:0
    UINT32 reg_earc_frpll_out2_div: 9;    //  17:9
    UINT32 reg_earc_frpll_out3_div: 9;    //  26:18
    UINT32 reg_earc_frpll_in_divrstb: 1;    //  27
    UINT32 reg_earc_frpll_fout_en: 1;    //   28
    UINT32 reg_earc_frpll_fout2_en: 1;    //  29
    UINT32 reg_earc_frpll_fin_sel: 1;    //   30
    UINT32 reg_earc_frpll_in_divsel: 1;    //  31
    };
}BND_CTRL_EDID_EARC_FRPLL_02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2030    earc_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_frpll_pdb :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EARC_FRPLL_03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2038    earc_frpll_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_frpll_lock:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EARC_FRPLL_06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_203C    earc_frpll_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_pll_fcw_mux_sel: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_EDID_EARC_FRPLL_07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2040    earc_frpll_08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EARC_FRPLL_08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2050    txp_clkdrv ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txp_clkdrv_bot_pdb: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txp_clkdrv_bot_icon: 2;    //  5:4
    UINT32 resvd01            : 10;    //  15: 6 reserved
    UINT32 reg_txp_clkdrv_top_pdb: 1;    //   16
    UINT32 resvd02            :  3;    //  19:17 reserved
    UINT32 reg_txp_clkdrv_top_icon: 2;    //  21:20
    UINT32 resvd03            : 10;    //  31:22 reserved
    };
}BND_CTRL_EDID_TXP_CLKDRV_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2060    dpm_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_en  :  1;    //      0
    UINT32 reg_phy_mon_all_ch :  1;    //      1
    UINT32 reg_phy_low_vsen   :  1;    //      2
    UINT32 reg_phy_dpm_odt    :  1;    //      3
    UINT32 reg_phy_tx_det_disable: 4;    //  7:4
    UINT32 reg_phy_tx_det_bypass_mode: 4;    //  11:8
    UINT32 resvd00            :  4;    //  15:12 reserved
    UINT32 reg_use_pad_for_dpm_tx_det_intr: 1;    //  16
    UINT32 resvd01            : 15;    //  31:17 reserved
    };
}BND_CTRL_EDID_DPM_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2064    dpm_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy1_tx_det_out:  1;    //      0
    UINT32 reg_phy2_tx_det_out:  1;    //      1
    UINT32 reg_phy3_tx_det_out:  1;    //      2
    UINT32 reg_phy4_tx_det_out:  1;    //      3
    UINT32 reg_dpm_tx_det_intr_status: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BND_CTRL_EDID_DPM_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2070    clk_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_sel    :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_apb_clk_gete_en:  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_EDID_CLK_01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2074    edid_soft_rst_mux ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 edid_soft_rst_mux_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EDID_SOFT_RST_MUX_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_2078    edid_soft_rst ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_bnd_mx_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_edid_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_edid_ip_ctrl_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_EDID_EDID_SOFT_RST_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_SYN_EDID000_O22A0_T       syn_edid000;             // 0xCA43_2000
    BND_CTRL_EDID_SYN_EDID001_O22A0_T       syn_edid001;             // 0xCA43_2004
    UINT32                             _rsvd_00[3];             // 0xCA43_2008 ~ 0xCA43_2010
    BND_CTRL_EDID_PAD_XIN_O22A0_T           pad_xin    ;             // 0xCA43_2014
    UINT32                             _rsvd_01[2];             // 0xCA43_2018 ~ 0xCA43_201C
    BND_CTRL_EDID_EARC_FRPLL_00_O22A0_T     earc_frpll_00;           // 0xCA43_2020
    BND_CTRL_EDID_EARC_FRPLL_01_O22A0_T     earc_frpll_01;           // 0xCA43_2024
    BND_CTRL_EDID_EARC_FRPLL_02_O22A0_T     earc_frpll_02;           // 0xCA43_2028
    UINT32                             _rsvd_02[1];             // 0xCA43_202C
    BND_CTRL_EDID_EARC_FRPLL_03_O22A0_T     earc_frpll_03;           // 0xCA43_2030
    UINT32                             _rsvd_03[1];             // 0xCA43_2034
    BND_CTRL_EDID_EARC_FRPLL_06_O22A0_T     earc_frpll_06;           // 0xCA43_2038
    BND_CTRL_EDID_EARC_FRPLL_07_O22A0_T     earc_frpll_07;           // 0xCA43_203C
    BND_CTRL_EDID_EARC_FRPLL_08_O22A0_T     earc_frpll_08;           // 0xCA43_2040
    UINT32                             _rsvd_04[3];             // 0xCA43_2044 ~ 0xCA43_204C
    BND_CTRL_EDID_TXP_CLKDRV_O22A0_T        txp_clkdrv ;             // 0xCA43_2050
    UINT32                             _rsvd_05[3];             // 0xCA43_2054 ~ 0xCA43_205C
    BND_CTRL_EDID_DPM_0_O22A0_T             dpm_0      ;             // 0xCA43_2060
    BND_CTRL_EDID_DPM_1_O22A0_T             dpm_1      ;             // 0xCA43_2064
    UINT32                             _rsvd_06[2];             // 0xCA43_2068 ~ 0xCA43_206C
    BND_CTRL_EDID_CLK_01_O22A0_T            clk_01     ;             // 0xCA43_2070
    BND_CTRL_EDID_EDID_SOFT_RST_MUX_O22A0_T    edid_soft_rst_mux;    // 0xCA43_2074
    BND_CTRL_EDID_EDID_SOFT_RST_O22A0_T     edid_soft_rst;           // 0xCA43_2078
}BND_CTRL_EDID_REG_O22A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_EDID_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

