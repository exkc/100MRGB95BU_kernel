#ifndef _CTOP_SYN_PQE_SYN_A0_REG_H_
#define _CTOP_SYN_PQE_SYN_A0_REG_H_

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
    0xC930_0000    crg_pqe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_pix2_clk_sel         :  2,    //   1: 0
    tcon_pix_clk_sel          :  2,    //   3: 2
    cvd27_clk_sel             :  1,    //      4
    cvd54_clk_sel             :  1,    //      5
    hdmi_clk_sel              :  1,    //      6
    pqe_cvd_vdo_mem_clk_sel   :  1,    //      7
    pqe_cvi0_clk_sel          :  2,    //   9: 8
    pqe_disp_clk_sel          :  2,    //  11:10
    pqe_de_clk_sel            :  2,    //  13:12
                              :  2,    //  15:14 reserved
    ch3pix_clk_inv_sel        :  1,    //     16
    cvd54_clk_inv_sel         :  1,    //     17
    phy_ppll_clk_inv_sel      :  1,    //     18
                              : 13;    //  31:19 reserved
}SYN_PQE_SYN_CRG_PQE00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0004    crg_pqe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pqe_apb_bnd_clk_gate_en   :  1,    //      0
    pqe_apb_clk_gate_en       :  1,    //      1
    pqe_axi_clk_gate_en       :  1,    //      2
    pqe_ch3pix_clk_gate_en    :  1,    //      3
    pqe_cvd27_clk_gate_en     :  1,    //      4
    pqe_cvd54_clk_gate_en     :  1,    //      5
    pqe_cvi0_clk_gate_en      :  1,    //      6
    pqe_de_clk_gate_en        :  1,    //      7
    pqe_det_clk_gate_en       :  1,    //      8
    pqe_disp_clk_gate_en      :  1,    //      9
    pqe_hdmi_clk_gate_en      :  1,    //     10
    pqe_hdmi_link_clk_gate_en :  1,    //     11
    pqe_mcu_clk_gate_en       :  1,    //     12
    pqe_te_clk_gate_en        :  1,    //     13
    pqe_vdo_clk_gate_en       :  1,    //     14
    pqe_cvd_vdo_mem_clk_gate_en: 1,    //     15
    tcon_apb_clk_gate_en      :  1,    //     16
    tcon_axi_clk_gate_en      :  1,    //     17
    tcon_pix_clk_gate_en      :  1,    //     18
    tcon_pix2_clk_gate_en     :  1,    //     19
    pqe_apb_bnd_200_clk_gate_en: 1,    //     20
                              : 11;    //  31:21 reserved
}SYN_PQE_SYN_CRG_PQE01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0008    crg_pqe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_pqo_apb             :  1,    //      0
    swrst_pqo_axi             :  1,    //      1
    swrst_pqo_de              :  1,    //      2
    swrst_pqi_apb             :  1,    //      3
    swrst_pqi_axi             :  1,    //      4
    swrst_pqi_de              :  1,    //      5
    swrst_pqe_cvd_mif         :  1,    //      6
    swrst_pqe_cvd_sbus        :  1,    //      7
    swrst_pqe_cvd_vbi         :  1,    //      8
    swrst_pqe_cvd27           :  1,    //      9
    swrst_pqe_cvd54           :  1,    //     10
    swrst_pqe_cvi0            :  1,    //     11
    swrst_pqe_pix             :  1,    //     12
    swrst_pqe_det             :  1,    //     13
    swrst_pqe_disp            :  1,    //     14
    swrst_hdmi_link           :  1,    //     15
    swrst_mcu                 :  1,    //     16
    swrst_mcu_apb             :  1,    //     17
    swrst_te                  :  1,    //     18
    swrst_vdo_sbus            :  1,    //     19
    swrst_vdo                 :  1,    //     20
    swrst_cvd_vdo_mem         :  1,    //     21
    swrst_tcon_apb            :  1,    //     22
    swrst_tcon_axi            :  1,    //     23
    swrst_tcon_pix            :  1,    //     24
    swrst_tcon_pix2           :  1,    //     25
                              :  6;    //  31:26 reserved
}SYN_PQE_SYN_CRG_PQE02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_000C    crg_pqe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmi_link_tmds_prt_clk_sel:  2,    //   1: 0
    hdmi_link_pix_prt_clk_sel :  2,    //   3: 2
    hdmi_link_aud_prt_clk_sel :  2,    //   5: 4
    hdmi_link_sys_clk_sel     :  1,    //      6
    phy_i2c_clk_sel           :  1,    //      7
                              :  8,    //  15: 8 reserved
    phy2_tmds_clk_inv_sel     :  1,    //     16
    phy2_ppll_clk_inv_sel     :  1,    //     17
    phy2_aud_clk_inv_sel      :  1,    //     18
    phy1_tmds_clk_inv_sel     :  1,    //     19
    phy1_ppll_clk_inv_sel     :  1,    //     20
    phy1_aud_clk_inv_sel      :  1,    //     21
    phy0_tmds_clk_inv_sel     :  1,    //     22
    phy0_ppll_clk_inv_sel     :  1,    //     23
    phy0_aud_clk_inv_sel      :  1,    //     24
                              :  7;    //  31:25 reserved
}SYN_PQE_SYN_CRG_PQE03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0010    crg_pqe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hdmi_link_tmds_prt1_clk_gate_en: 1,    //  0
    hdmi_link_pix_prt1_clk_gate_en: 1,    //   1
    hdmi_link_sys_clk_gate_en :  1,    //      2
    hdmi_link_tmds_prt0_clk_gate_en: 1,    //  3
    hdmi_link_pix_prt0_clk_gate_en: 1,    //   4
    hdmi_apb_clk_gate_en      :  1,    //      5
                              : 26;    //   31:6 reserved
}SYN_PQE_SYN_CRG_PQE04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0014    crg_pqe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_vfifo_w             :  1,    //      0
    swrst_vfifo_r             :  1,    //      1
    swrst_tmds                :  1,    //      2
    swrst_pix                 :  1,    //      3
    swrst_link                :  1,    //      4
    swrst_hdcp                :  1,    //      5
    swrst_edid                :  1,    //      6
    swrst_aud                 :  1,    //      7
    swrst_apb                 :  1,    //      8
    swrst_afifo_w             :  1,    //      9
    swrst_afifo_r             :  1,    //     10
    swrst_acrn                :  1,    //     11
                              : 20;    //  31:12 reserved
}SYN_PQE_SYN_CRG_PQE05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0018    crg_pqe06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hsusb1_phy_core_clk_gate_en: 1,    //      0
    hsusb1_phy_clock_o_gate_en:  1,    //      1
    hsusb1_freeclk_o_gate_en  :  1,    //      2
    hsusb1_clk48mohci_o_gate_en: 1,    //      3
    hsusb1_clk12mohci_o_gate_en: 1,    //      4
    bus_clk_o_gate_en         :  1,    //      5
                              : 26;    //   31:6 reserved
}SYN_PQE_SYN_CRG_PQE06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_001C    crg_pqe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_hsusb1_utmi         :  1,    //      0
    swrst_hsusb1_phy_por      :  1,    //      1
    swrst_hsusb1_core         :  1,    //      2
    swrst_hsusb1_bus          :  1,    //      3
    swrst_bus                 :  1,    //      4
                              : 27;    //   31:5 reserved
}SYN_PQE_SYN_CRG_PQE07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0020    syn_pqe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cvi_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0024    syn_pqe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_imx_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0028    syn_pqe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_nd0_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_002C    syn_pqe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_gsc_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0030    syn_pqe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_vsd_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0034    syn_pqe05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cco_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0038    syn_pqe06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_led_ctrl          : 32;    //  31: 0
}SYN_PQE_SYN_SYN_PQE06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_003C    syn_pqe07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vsd_shp_detour_en         :  1,    //      0
    cpu_cco_detour_en         :  1,    //      1
    tcon_gmau_flush_en        :  1,    //      2
    hdmi_phy_sel              :  1,    //      3
                              : 28;    //   31:4 reserved
}SYN_PQE_SYN_SYN_PQE07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0044    syn_pqe08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_clk_off_det           : 11,    //  10: 0
    reg_dco_sel               :  1,    //     11
    game_mode_en              :  1,    //     12
    intr_clear                :  1,    //     13
    clk_sel                   :  3,    //  16:14
                              : 15;    //  31:17 reserved
}SYN_PQE_SYN_SYN_PQE08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_0048    syn_pqe09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_phy2_rx             :  1,    //      0
    swrst_gstcc               :  1,    //      1
    swrst_stcc                :  1,    //      2
    tcon_gmau_flush_done      :  1,    //      3
    reg_phy_prt_sel           :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}SYN_PQE_SYN_SYN_PQE09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    pqe_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SYN_PQE_SYN_CRG_PQE00_L18F_A0            crg_pqe00                ;         // 0xC930_0000
    SYN_PQE_SYN_CRG_PQE01_L18F_A0            crg_pqe01                ;         // 0xC930_0004
    SYN_PQE_SYN_CRG_PQE02_L18F_A0            crg_pqe02                ;         // 0xC930_0008
    SYN_PQE_SYN_CRG_PQE03_L18F_A0            crg_pqe03                ;         // 0xC930_000C
    SYN_PQE_SYN_CRG_PQE04_L18F_A0            crg_pqe04                ;         // 0xC930_0010
    SYN_PQE_SYN_CRG_PQE05_L18F_A0            crg_pqe05                ;         // 0xC930_0014
    SYN_PQE_SYN_CRG_PQE06_L18F_A0            crg_pqe06                ;         // 0xC930_0018
    SYN_PQE_SYN_CRG_PQE07_L18F_A0            crg_pqe07                ;         // 0xC930_001C
    SYN_PQE_SYN_SYN_PQE00_L18F_A0            syn_pqe00                ;         // 0xC930_0020
    SYN_PQE_SYN_SYN_PQE01_L18F_A0            syn_pqe01                ;         // 0xC930_0024
    SYN_PQE_SYN_SYN_PQE02_L18F_A0            syn_pqe02                ;         // 0xC930_0028
    SYN_PQE_SYN_SYN_PQE03_L18F_A0            syn_pqe03                ;         // 0xC930_002C
    SYN_PQE_SYN_SYN_PQE04_L18F_A0            syn_pqe04                ;         // 0xC930_0030
    SYN_PQE_SYN_SYN_PQE05_L18F_A0            syn_pqe05                ;         // 0xC930_0034
    SYN_PQE_SYN_SYN_PQE06_L18F_A0            syn_pqe06                ;         // 0xC930_0038
    SYN_PQE_SYN_SYN_PQE07_L18F_A0            syn_pqe07                ;         // 0xC930_003C
UINT32                                                 _rsvd_00[   1] ;         // 0xC930_0040
    SYN_PQE_SYN_SYN_PQE08_L18F_A0            syn_pqe08                ;         // 0xC930_0044
    SYN_PQE_SYN_SYN_PQE09_L18F_A0            syn_pqe09                ;         // 0xC930_0048
} SYN_PQE_SYN_REG_L18F_A0;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_PQE_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_SYN_Register_Manual_55.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

