#ifndef _BND_CTRL_CVI_A0_REG_H_
#define _BND_CTRL_CVI_A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC90F_D000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    cvi3_clk_gate_en          :  1,    //      2
    cvi2_clk_gate_en          :  1,    //      3
    cvi1_clk_gate_en          :  1,    //      4
    cvi0_clk_gate_en          :  1,    //      5
    core_clk_gate_en          :  1,    //      6
    hdmirx_dbg_iaud_clk_gate_en: 1,    //      7
    hdmirx_dbg_ipixel_clk_gate_en: 1,    //    8
    hdmirx_dbg_ihdmi_clk_gate_en: 1,    //     9
    hdmirx_dbg_sys_clk_gate_en:  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_CVI_CRG_CVI00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy4_ppll_clk_sel         :  2,    //   1: 0
    phy3_ppll_clk_sel         :  2,    //   3: 2
    phy2_ppll_clk_sel         :  2,    //   5: 4
    phy1_ppll_clk_sel         :  2,    //   7: 6
    game_hdmi_clk_sel         :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}BND_CTRL_CVI_CRG_CVI01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmi3_clk_sel             :  1,    //      0
    hdmi2_clk_sel             :  1,    //      1
    hdmi1_clk_sel             :  1,    //      2
    hdmi0_clk_sel             :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_CVI_CRG_CVI02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D00C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    cvi3_clk_sel              :  3,    //   8: 6
    cvi2_clk_sel              :  3,    //  11: 9
    cvi1_clk_sel              :  3,    //  14:12
    cvi0_clk_sel              :  3,    //  17:15
                              : 14;    //  31:18 reserved
}BND_CTRL_CVI_CRG_CVI03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvd54_inv_sel             :  1,    //      0
    ch3pix_inv_sel            :  1,    //      1
    phy4_ppll_inv_sel         :  1,    //      2
    phy3_ppll_inv_sel         :  1,    //      3
    phy2_ppll_inv_sel         :  1,    //      4
    phy1_ppll_inv_sel         :  1,    //      5
                              : 26;    //   31:6 reserved
}BND_CTRL_CVI_CRG_CVI04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D014    crg_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    swrst_cvi3                :  1,    //      2
    swrst_cvi2                :  1,    //      3
    swrst_cvi1                :  1,    //      4
    swrst_cvi0                :  1,    //      5
    swrst_cvd_mif             :  1,    //      6
    swrst_cvd_vbi             :  1,    //      7
    swrst_cvd27               :  1,    //      8
    swrst_cvd54               :  1,    //      9
    swrst_ch3pix              :  1,    //     10
    swrst_hdmi3_link          :  1,    //     11
                              :  1,    //     12 reserved
    swrst_hdmi2_link          :  1,    //     13
                              :  1,    //     14 reserved
    swrst_hdmi1_link          :  1,    //     15
                              :  1,    //     16 reserved
    swrst_hdmi0_link          :  1,    //     17
                              :  1,    //     18 reserved
    swrst_axi_sub             :  1,    //     19
    swrst_axi                 :  1,    //     20
    swrst_de                  :  1,    //     21
    swrst_apb                 :  1,    //     22
                              :  9;    //  31:23 reserved
}BND_CTRL_CVI_CRG_CVI05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D018    crg_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_reg_dco_sel             :  1,    //      0
    i_game_mode_en            :  1,    //      1
                              :  2,    //   3: 2 reserved
    i_clk_sel                 :  3,    //   6: 4
    i_intr_clear              :  1,    //      7
                              :  8,    //  15: 8 reserved
    i_reg_clk_off_det         : 11,    //  26:16
                              :  5;    //  31:27 reserved
}BND_CTRL_CVI_CRG_CVI06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D01C    crg_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cvi_ctrl          : 32;    //  31: 0
}BND_CTRL_CVI_CRG_CVI07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D020    crg_cvi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmi0_s_arcache           :  1,    //      0
    hdmi0_s_awcache           :  1,    //      1
    hdmi0_flush_en            :  1,    //      2
    hdmi1_s_arcache           :  1,    //      3
    hdmi1_s_awcache           :  1,    //      4
    hdmi1_flush_en            :  1,    //      5
    hdmi2_s_arcache           :  1,    //      6
    hdmi2_s_awcache           :  1,    //      7
    hdmi2_flush_en            :  1,    //      8
    hdmi3_s_arcache           :  1,    //      9
    hdmi3_s_awcache           :  1,    //     10
    hdmi3_flush_en            :  1,    //     11
    cvd_s_arcache             :  1,    //     12
    cvd_s_awcache             :  1,    //     13
    cvd_flush_en              :  1,    //     14
    hdmi0_ar_bus_access_gating:  1,    //     15
    hdmi0_aw_bus_access_gating:  1,    //     16
    hdmi1_ar_bus_access_gating:  1,    //     17
    hdmi1_aw_bus_access_gating:  1,    //     18
    hdmi2_ar_bus_access_gating:  1,    //     19
    hdmi2_aw_bus_access_gating:  1,    //     20
    hdmi3_ar_bus_access_gating:  1,    //     21
    hdmi3_aw_bus_access_gating:  1,    //     22
    cvd_ar_bus_access_gating  :  1,    //     23
    cvd_aw_bus_access_gating  :  1,    //     24
                              :  7;    //  31:25 reserved
}BND_CTRL_CVI_CRG_CVI08_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D024    crg_cvi09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    o_cnt_low                 : 11,    //  10: 0
    o_cnt_high                : 11,    //  21:11
    o_hdmi_clk_cnt            :  6,    //  27:22
                              :  4;    //  31:28 reserved
}BND_CTRL_CVI_CRG_CVI09_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D028    crg_cvi10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmi0_w_ag                :  1,    //      0
    hdmi0_aw_ag               :  1,    //      1
    hdmi0_ar_ag               :  1,    //      2
    hdmi1_w_ag                :  1,    //      3
    hdmi1_aw_ag               :  1,    //      4
    hdmi1_ar_ag               :  1,    //      5
    hdmi2_w_ag                :  1,    //      6
    hdmi2_aw_ag               :  1,    //      7
    hdmi2_ar_ag               :  1,    //      8
    hdmi3_w_ag                :  1,    //      9
    hdmi3_aw_ag               :  1,    //     10
    hdmi3_ar_ag               :  1,    //     11
    cvd_w_ag                  :  1,    //     12
    cvd_aw_ag                 :  1,    //     13
    cvd_ar_ag                 :  1,    //     14
    flush_done_hdmi0          :  1,    //     15
    flush_done_hdmi1          :  1,    //     16
    flush_done_hdmi2          :  1,    //     17
    flush_done_hdmi3          :  1,    //     18
    flush_done_cvd            :  1,    //     19
                              : 12;    //  31:20 reserved
}BND_CTRL_CVI_CRG_CVI10_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D02C    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy3_clk_sel              :  3,    //   2: 0
                              :  1,    //      3 reserved
    phy2_clk_sel              :  3,    //   6: 4
    phy1_clk_sel              :  3,    //   9: 7
    phy0_clk_sel              :  3,    //  12:10
    hdmirx_comm_sapb_clk_sel  :  1,    //     13
    phy_i2c_clk_sel           :  1,    //     14
    phy3_pixfifo_inv_sel      :  1,    //     15
    phy2_pixfifo_inv_sel      :  1,    //     16
    phy1_pixfifo_inv_sel      :  1,    //     17
    phy0_pixfifo_inv_sel      :  1,    //     18
    phy3_tmdsrx_inv_sel       :  1,    //     19
    phy2_tmdsrx_inv_sel       :  1,    //     20
    phy1_tmdsrx_inv_sel       :  1,    //     21
    phy0_tmdsrx_inv_sel       :  1,    //     22
    edid_clk_sel              :  1,    //     23
    esm_clk_sel               :  1,    //     24
                              :  7;    //  31:25 reserved
}BND_CTRL_CVI_CRG_HDMI00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D030    crg_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_bus                 :  1,    //      0
    swrst_prt3_icec           :  1,    //      1
    swrst_prt3_tmdsrx_ref     :  1,    //      2
    swrst_prt3_base           :  1,    //      3
    swrst_prt3_skp            :  1,    //      4
    swrst_prt2_icec           :  1,    //      5
    swrst_prt2_tmdsrx_ref     :  1,    //      6
    swrst_prt2_base           :  1,    //      7
    swrst_prt2_skp            :  1,    //      8
    swrst_prt1_icec           :  1,    //      9
    swrst_prt1_tmdsrx_ref     :  1,    //     10
    swrst_prt1_base           :  1,    //     11
    swrst_prt1_skp            :  1,    //     12
    swrst_prt0_icec           :  1,    //     13
    swrst_prt0_tmdsrx_ref     :  1,    //     14
    swrst_prt0_base           :  1,    //     15
    swrst_prt0_skp            :  1,    //     16
    swrst_hdmirx_dbg_afifo_r  :  1,    //     17
    swrst_hdmirx_dbg_afifo_w  :  1,    //     18
    swrst_hdmirx_dbg_vfifo_r  :  1,    //     19
    swrst_hdmirx_dbg_vfifo_w  :  1,    //     20
    swrst_hdmirx_dbg_ipixel   :  1,    //     21
    swrst_hdmirx_dbg_ihdmi    :  1,    //     22
    swrst_hdmirx_dbg_iaud     :  1,    //     23
    swrst_hdmirx_dbg_sys      :  1,    //     24
    swrst_hdmirx_dbg_sapb     :  1,    //     25
                              :  6;    //  31:26 reserved
}BND_CTRL_CVI_CRG_HDMI01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D034    crg_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_hdmi_ctr00            : 32;    //  31: 0
}BND_CTRL_CVI_CRG_HDMI02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D038    crg_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_hdmi_ctr01            : 32;    //  31: 0
}BND_CTRL_CVI_CRG_HDMI03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC90F_D03C    crg_hdmi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_hdmi_ctr02            : 32;    //  31: 0
}BND_CTRL_CVI_CRG_HDMI04_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_CVI_CRG_CVI00_O18_A0                crg_cvi00                ;         // 0xC90F_D000
BND_CTRL_CVI_CRG_CVI01_O18_A0                crg_cvi01                ;         // 0xC90F_D004
BND_CTRL_CVI_CRG_CVI02_O18_A0                crg_cvi02                ;         // 0xC90F_D008
BND_CTRL_CVI_CRG_CVI03_O18_A0                crg_cvi03                ;         // 0xC90F_D00C
BND_CTRL_CVI_CRG_CVI04_O18_A0                crg_cvi04                ;         // 0xC90F_D010
BND_CTRL_CVI_CRG_CVI05_O18_A0                crg_cvi05                ;         // 0xC90F_D014
BND_CTRL_CVI_CRG_CVI06_O18_A0                crg_cvi06                ;         // 0xC90F_D018
BND_CTRL_CVI_CRG_CVI07_O18_A0                crg_cvi07                ;         // 0xC90F_D01C
BND_CTRL_CVI_CRG_CVI08_O18_A0                crg_cvi08                ;         // 0xC90F_D020
BND_CTRL_CVI_CRG_CVI09_O18_A0                crg_cvi09                ;         // 0xC90F_D024
BND_CTRL_CVI_CRG_CVI10_O18_A0                crg_cvi10                ;         // 0xC90F_D028
BND_CTRL_CVI_CRG_HDMI00_O18_A0               crg_hdmi00               ;         // 0xC90F_D02C
BND_CTRL_CVI_CRG_HDMI01_O18_A0               crg_hdmi01               ;         // 0xC90F_D030
BND_CTRL_CVI_CRG_HDMI02_O18_A0               crg_hdmi02               ;         // 0xC90F_D034
BND_CTRL_CVI_CRG_HDMI03_O18_A0               crg_hdmi03               ;         // 0xC90F_D038
BND_CTRL_CVI_CRG_HDMI04_O18_A0               crg_hdmi04               ;         // 0xC90F_D03C
} BND_CTRL_CVI_REG_O18_A0;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_CVI_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

