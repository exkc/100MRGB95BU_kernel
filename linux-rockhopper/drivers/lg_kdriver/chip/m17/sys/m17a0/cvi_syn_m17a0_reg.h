#ifndef _CVI_SYN_M17A0_REG_H_
#define _CVI_SYN_M17A0_REG_H_

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
    0xC930_2000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy1_ppll_clk_sel         :  2,    //   1: 0
    phy2_ppll_clk_sel         :  2,    //   3: 2
    phy3_ppll_clk_sel         :  2,    //   5: 4
    phy4_ppll_clk_sel         :  2,    //   7: 6
    hdmi0_clk_sel             :  1,    //      8
    hdmi1_clk_sel             :  1,    //      9
    hdmi2_clk_sel             :  1,    //     10
    hdmi3_clk_sel             :  1,    //     11
    phy1_ppll_inv_sel         :  1,    //     12
    phy2_ppll_inv_sel         :  1,    //     13
    phy3_ppll_inv_sel         :  1,    //     14
    phy4_ppll_inv_sel         :  1,    //     15
    ch3pix_inv_sel            :  1,    //     16
    cvd54_inv_sel             :  1,    //     17
    game_hdmi_clk_sel         :  2,    //  19:18
                              : 12;    //  31:20 reserved
}CVI_SYN_CRG_CVI00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cvi0_clk_sel              :  3,    //   2: 0
                              :  1,    //      3 reserved
    cvi1_clk_sel              :  3,    //   6: 4
                              :  1,    //      7 reserved
    cvi2_clk_sel              :  3,    //  10: 8
                              :  1,    //     11 reserved
    cvi3_clk_sel              :  3,    //  14:12
                              :  1,    //     15 reserved
    cvi4_clk_sel              :  3,    //  18:16
                              :  1,    //     19 reserved
    cvi5_clk_sel              :  3,    //  22:20
                              :  9;    //  31:23 reserved
}CVI_SYN_CRG_CVI01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_apb                 :  1,    //      0
    swrst_de                  :  1,    //      1
    swrst_axi                 :  1,    //      2
    swrst_hdmi0               :  1,    //      3
    swrst_hdmi0_link          :  1,    //      4
    swrst_hdmi1               :  1,    //      5
    swrst_hdmi1_link          :  1,    //      6
    swrst_hdmi2               :  1,    //      7
    swrst_hdmi2_link          :  1,    //      8
    swrst_hdmi3               :  1,    //      9
    swrst_hdmi3_link          :  1,    //     10
    swrst_ch3pix              :  1,    //     11
    swrst_cvd54               :  1,    //     12
    swrst_cvd27               :  1,    //     13
    swrst_cvd_vbi             :  1,    //     14
    swrst_cvd_mif             :  1,    //     15
    swrst_cvi0                :  1,    //     16
    swrst_cvi1                :  1,    //     17
    swrst_cvi2                :  1,    //     18
    swrst_cvi3                :  1,    //     19
    swrst_cvi4                :  1,    //     20
    swrst_cvi5                :  1,    //     21
    swrst_axi_sub             :  1,    //     22
    core_clk_gate_en          :  1,    //     23
    cvi0_clk_gate_en          :  1,    //     24
    cvi1_clk_gate_en          :  1,    //     25
    cvi2_clk_gate_en          :  1,    //     26
    cvi3_clk_gate_en          :  1,    //     27
    cvi4_clk_gate_en          :  1,    //     28
    cvi5_clk_gate_en          :  1,    //     29
                              :  2;    //  31:30 reserved
}CVI_SYN_CRG_CVI02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_200C    crg_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_hdmi_ctr00            : 32;    //  31: 0
}CVI_SYN_CRG_HDMI00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2010    crg_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    crg_hdmi_ctr01            : 32;    //  31: 0
}CVI_SYN_CRG_HDMI01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2014    crg_hdmi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy0_tmdsrx_inv_sel       :  1,    //      0
    phy1_tmdsrx_inv_sel       :  1,    //      1
    phy2_tmdsrx_inv_sel       :  1,    //      2
    phy3_tmdsrx_inv_sel       :  1,    //      3
    phy0_pixfifo_inv_sel      :  1,    //      4
    phy1_pixfifo_inv_sel      :  1,    //      5
    phy2_pixfifo_inv_sel      :  1,    //      6
    phy3_pixfifo_inv_sel      :  1,    //      7
    phy0_clk_sel              :  3,    //  10: 8
    phy1_clk_sel              :  3,    //  13:11
    phy2_clk_sel              :  3,    //  16:14
    phy3_clk_sel              :  3,    //  19:17
    phy_i2c_clk_sel           :  1,    //     20
    hdmirx_comm_spab_clk_sel  :  1,    //     21
    edid_clk_sel              :  1,    //     22
                              :  9;    //  31:23 reserved
}CVI_SYN_CRG_HDMI02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2018    syn_hdmi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_prt0_skp            :  1,    //      0
    swrst_prt0_base           :  1,    //      1
    swrst_prt0_tmdsrx_ref     :  1,    //      2
    swrst_prt0_icec           :  1,    //      3
    swrst_prt1_skp            :  1,    //      4
    swrst_prt1_base           :  1,    //      5
    swrst_prt1_tmdsrx_ref     :  1,    //      6
    swrst_prt1_icec           :  1,    //      7
    swrst_prt2_skp            :  1,    //      8
    swrst_prt2_base           :  1,    //      9
    swrst_prt2_tmdsrx_ref     :  1,    //     10
    swrst_prt2_icec           :  1,    //     11
    swrst_prt3_skp            :  1,    //     12
    swrst_prt3_base           :  1,    //     13
    swrst_prt3_tmdsrx_ref     :  1,    //     14
    swrst_prt3_icec           :  1,    //     15
    swrst_bus                 :  1,    //     16
                              : 15;    //  31:17 reserved
}CVI_SYN_SYN_HDMI03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_201C    syn_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}CVI_SYN_SYN_CVI02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2020    syn_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr01                     : 32;    //  31: 0
}CVI_SYN_SYN_CVI03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2024    syn_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr02                     : 32;    //  31: 0
}CVI_SYN_SYN_CVI04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2028    syn_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}CVI_SYN_SYN_CVI05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_202C    syn_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr01_ro                  : 32;    //  31: 0
}CVI_SYN_SYN_CVI06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_2030    syn_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cvi_ctrl          : 32;    //  31: 0
}CVI_SYN_SYN_CVI07_M17_A0;

/*-----------------------------------------------------------------------------------------
    cvi_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CVI_SYN_CRG_CVI00_M17_A0                     crg_cvi00                ;         // 0xC930_2000
CVI_SYN_CRG_CVI01_M17_A0                     crg_cvi01                ;         // 0xC930_2004
CVI_SYN_CRG_CVI02_M17_A0                     crg_cvi02                ;         // 0xC930_2008
CVI_SYN_CRG_HDMI00_M17_A0                    crg_hdmi00               ;         // 0xC930_200C
CVI_SYN_CRG_HDMI01_M17_A0                    crg_hdmi01               ;         // 0xC930_2010
CVI_SYN_CRG_HDMI02_M17_A0                    crg_hdmi02               ;         // 0xC930_2014
CVI_SYN_SYN_HDMI03_M17_A0                    syn_hdmi03               ;         // 0xC930_2018
CVI_SYN_SYN_CVI02_M17_A0                     syn_cvi02                ;         // 0xC930_201C
CVI_SYN_SYN_CVI03_M17_A0                     syn_cvi03                ;         // 0xC930_2020
CVI_SYN_SYN_CVI04_M17_A0                     syn_cvi04                ;         // 0xC930_2024
CVI_SYN_SYN_CVI05_M17_A0                     syn_cvi05                ;         // 0xC930_2028
CVI_SYN_SYN_CVI06_M17_A0                     syn_cvi06                ;         // 0xC930_202C
CVI_SYN_SYN_CVI07_M17_A0                     syn_cvi07                ;         // 0xC930_2030
} CVI_SYN_REG_M17_A0;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CVI_SYN_M17A0_REG_H_ */

/* from 'M16PP_CTOP_SYN_Register_Manual_52.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

