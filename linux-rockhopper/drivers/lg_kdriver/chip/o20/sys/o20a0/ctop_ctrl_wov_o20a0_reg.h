#ifndef _CTOP_CTRL_WOV_O20A0_REG_H_
#define _CTOP_CTRL_WOV_O20A0_REG_H_

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
    0xC330_0800    aioplls0 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC330_0804    aioplls1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aioplls_lockf         :  1,    //      0
    reg_aioplls_pdb           :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_aioplls_out_div       :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_aioplls_fb_m          :  8,    //  15: 8
    reg_aioplls_cih           :  4,    //  19:16
    reg_aioplls_fout1_en      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_aioplls_cih2          :  4,    //  27:24
    reg_aioplls_fout2_en      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_WOV_AIOPLLS1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0808    saradc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_pdb              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_sc               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_sadc_isel             :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_sadc_chsel            :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_pc               :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_cc               :  3,    //  22:20
                              :  9;    //  31:23 reserved
}CTOP_CTRL_WOV_SARADC2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_080C    txclkdrv3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_bottom_pdb   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_bottom_cksel :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_txclkdrv_bottom_icon  :  3,    //  10: 8
                              :  5,    //  15:11 reserved
    reg_txclkdrv_top_pdb      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_txclkdrv_top_cksel    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_txclkdrv_top_icon     :  3,    //  26:24
                              :  5;    //  31:27 reserved
}CTOP_CTRL_WOV_TXCLKDRV3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0810    jtag_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag1_sel             :  4,    //   3: 0
    reg_jtag0_sel             :  4,    //   7: 4
    reg_jtag1_lock            :  1,    //      8
    reg_jtag0_lock            :  1,    //      9
                              : 22;    //  31:10 reserved
}CTOP_CTRL_WOV_JTAG_MUX_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0814    uart_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_uart_sel              :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_WOV_UART_MUX_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0818    interrupt_en0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_wifi_wakeup_intr  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_reserved_intr1    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_reserved_intr0    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_ex_ethernet_wakeup_intr: 1,    //  12
                              :  3,    //  15:13 reserved
    reg_use_ewbs_wakeup_intr  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_bdp_intr          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_am_mode_intr      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_INTERRUPT_EN0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_081C    gem_ft_mux01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ephy_bist_mode_from_micom: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_ephy_mode_from_micom  :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_ephy_shutdown_from_micom: 1,    //     8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_WOV_GEM_FT_MUX01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0820    power_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_nisolate_ethernet     :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_WOV_POWER_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0828    edid_reg01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_reg_in_l         :  4,    //   3: 0
    reg_edid_reg_out_l        :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}CTOP_CTRL_WOV_EDID_REG01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_082C    iomux_disable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_micom_i2c2        :  1,    //      0
    reg_pdm_disable           :  1,    //      1
    reg_micom_uart0_disable   :  1,    //      2
    reg_micom_spi_disable     :  1,    //      3
    reg_use_gpio_cec          :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_WOV_IOMUX_DISABLE01_O20A0_T;

typedef struct {
    UINT32
    reg_use_micom_i2c2        :  1,    //      0
    reg_pdm_disable           :  1,    //      1
    reg_micom_uart0_disable   :  1,    //      2
    reg_micom_spi_disable     :  1,    //      3
    reg_use_gpio_cec          :  1,    //      4
    reg_cec_gf_en             :  1,    //      5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_WOV_IOMUX_DISABLE01_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0830    enable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi21_off            :  1,    //      0
    reg_hdmi22_off            :  1,    //      1
    reg_hdmi23_off            :  1,    //      2
    reg_hdmi24_off            :  1,    //      3
    reg_hdmi25_off            :  1,    //      4
                              : 11,    //  15: 5 reserved
    reg_use_hdmi_link_cec     :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_WOV_ENABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0834    jtag01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag_hdmi_dbg         :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_WOV_JTAG01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0838    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_5v_in__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_1_5v_in__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_1_5v_in__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_1_5v_in__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_1_5v_in__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_1_5v_in__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_1_5v_in__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_083C    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_hpd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_1_hpd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_1_hpd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_1_hpd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_1_hpd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_1_hpd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_1_hpd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0840    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_scl__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_1_scl__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_1_scl__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_1_scl__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_1_scl__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_1_scl__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_1_scl__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0844    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_sda__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_1_sda__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_1_sda__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_1_sda__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_1_sda__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_1_sda__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_1_sda__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0848    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_5v_in__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_2_5v_in__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_2_5v_in__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_2_5v_in__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_2_5v_in__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_2_5v_in__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_2_5v_in__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_084C    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_hpd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_2_hpd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_2_hpd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_2_hpd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_2_hpd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_2_hpd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_2_hpd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0850    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_scl__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_2_scl__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_2_scl__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_2_scl__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_2_scl__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_2_scl__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_2_scl__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0854    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_sda__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_2_sda__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_2_sda__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_2_sda__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_2_sda__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_2_sda__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_2_sda__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0858    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_5v_in__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_3_5v_in__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_3_5v_in__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_3_5v_in__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_3_5v_in__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_3_5v_in__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_3_5v_in__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_085C    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_hpd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_3_hpd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_3_hpd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_3_hpd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_3_hpd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_3_hpd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_3_hpd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0860    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_scl__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_3_scl__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_3_scl__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_3_scl__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_3_scl__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_3_scl__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_3_scl__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0864    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_sda__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_3_sda__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_3_sda__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_3_sda__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_3_sda__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_3_sda__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_3_sda__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0868    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_5v_in__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_4_5v_in__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_4_5v_in__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_4_5v_in__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_4_5v_in__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_4_5v_in__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_4_5v_in__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_086C    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_hpd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_4_hpd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_4_hpd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_4_hpd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_4_hpd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_4_hpd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_4_hpd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0870    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_scl__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_4_scl__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_4_scl__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_4_scl__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_4_scl__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_4_scl__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_4_scl__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0874    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_sda__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_4_sda__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_4_sda__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_4_sda__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_4_sda__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_4_sda__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_4_sda__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0878    ioctrl_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_5_5v_in__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_5_5v_in__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_5_5v_in__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_5_5v_in__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_5_5v_in__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_5_5v_in__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_5_5v_in__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_087C    ioctrl_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_5_hpd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_5_hpd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_5_hpd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_5_hpd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_5_hpd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_5_hpd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_5_hpd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0880    ioctrl_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_5_scl__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_5_scl__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_5_scl__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_5_scl__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_5_scl__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_5_scl__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_5_scl__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0884    ioctrl_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_5_sda__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_5_sda__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_5_sda__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_5_sda__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_5_sda__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_5_sda__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_5_sda__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0888    ioctrl_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_cec__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_hdmi_cec__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_hdmi_cec__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_hdmi_cec__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_hdmi_cec__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_hdmi_cec__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_hdmi_cec__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_088C    ioctrl_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_00__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_00__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_00__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_00__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_00__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_00__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_00__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0890    ioctrl_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_01__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_01__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_01__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_01__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_01__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_01__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_01__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0894    ioctrl_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_02__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_02__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_02__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_02__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_02__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_02__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_02__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0898    ioctrl_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_03__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_03__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_03__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_03__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_03__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_03__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_03__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_089C    ioctrl_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_04__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_04__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_04__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_04__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_04__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_04__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_04__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08A0    ioctrl_26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_05__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_05__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_05__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_05__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_05__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_05__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_05__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_26_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08A4    ioctrl_27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_06__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_06__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_06__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_06__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_06__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_06__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_06__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_27_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08A8    ioctrl_28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_07__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_07__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_07__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_07__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_07__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_07__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_07__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_28_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08AC    ioctrl_29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_08__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_08__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_08__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_08__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_08__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_08__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_08__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_29_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08B0    ioctrl_30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_09__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_09__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_09__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_09__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_09__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_09__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_09__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_30_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08B4    ioctrl_31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_10__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_10__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_10__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_10__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_10__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_10__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_10__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_31_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08B8    ioctrl_32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_11__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_11__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_11__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_11__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_11__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_11__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_11__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_32_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08BC    ioctrl_33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_12__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_12__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_12__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_12__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_12__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_12__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_12__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_33_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08C0    ioctrl_34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_13__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_13__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_13__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_13__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_13__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_13__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_13__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_34_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08C4    ioctrl_35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_14__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_14__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_14__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_14__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_14__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_14__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_14__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_35_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08C8    ioctrl_36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_15__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_15__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_15__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_15__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_15__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_15__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_15__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_36_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08D0    ioctrl_37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_16__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_16__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_16__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_16__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_16__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_16__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_16__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_37_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08D4    ioctrl_38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_17__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_17__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_17__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_17__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_17__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_17__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_17__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_38_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08D8    ioctrl_39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_18__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_18__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_18__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_18__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_18__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_18__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_18__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_39_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08DC    ioctrl_40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_19__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_19__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_19__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_19__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_19__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_19__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_19__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_40_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08E0    ioctrl_41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_20__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_20__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_20__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_20__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_20__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_20__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_20__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_41_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08E4    ioctrl_42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_21__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_21__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_21__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_21__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_21__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_21__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_21__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_42_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08E8    ioctrl_43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_22__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_22__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_22__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_22__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_22__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_22__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_22__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_43_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08EC    ioctrl_44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_23__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_23__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_23__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_23__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_23__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_23__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_23__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_44_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08F0    ioctrl_45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_24__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_24__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_24__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_24__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_24__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_24__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_24__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_45_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08F4    ioctrl_46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_25__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_25__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_25__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_25__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_25__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_25__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_25__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_46_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08F8    ioctrl_47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_26__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_26__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_26__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_26__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_26__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_26__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_26__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_47_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_08FC    ioctrl_48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_boot_mode__st: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_boot_mode__pu: 1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_boot_mode__pd: 1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_boot_mode__ds3: 1,    //    12
                              :  3,    //  15:13 reserved
    reg_pad_micom_boot_mode__ds2: 1,    //    16
                              :  3,    //  19:17 reserved
    reg_pad_micom_boot_mode__ds1: 1,    //    20
                              :  3,    //  23:21 reserved
    reg_pad_micom_boot_mode__ds0: 1,    //    24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_48_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0900    ioctrl_49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_debug_mode__st: 1,    //     0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_debug_mode__pu: 1,    //     4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_debug_mode__pd: 1,    //     8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_debug_mode__ds3: 1,    //   12
                              :  3,    //  15:13 reserved
    reg_pad_micom_debug_mode__ds2: 1,    //   16
                              :  3,    //  19:17 reserved
    reg_pad_micom_debug_mode__ds1: 1,    //   20
                              :  3,    //  23:21 reserved
    reg_pad_micom_debug_mode__ds0: 1,    //   24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_49_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0904    ioctrl_50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_clk__st :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_spi_clk__pu :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_spi_clk__pd :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_spi_clk__ds3:  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_spi_clk__ds2:  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_spi_clk__ds1:  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_spi_clk__ds0:  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_50_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0908    ioctrl_51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_cs__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_spi_cs__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_spi_cs__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_spi_cs__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_spi_cs__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_spi_cs__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_spi_cs__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_51_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_090C    ioctrl_52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_di__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_spi_di__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_spi_di__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_spi_di__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_spi_di__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_spi_di__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_spi_di__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_52_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0910    ioctrl_53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_do__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_micom_spi_do__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_micom_spi_do__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_micom_spi_do__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_micom_spi_do__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_micom_spi_do__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_micom_spi_do__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_53_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0914    ioctrl_54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm_clkout__st:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_wov_pdm_clkout__pu:  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_wov_pdm_clkout__pd:  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_wov_pdm_clkout__ds3: 1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_wov_pdm_clkout__ds2: 1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_wov_pdm_clkout__ds1: 1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_wov_pdm_clkout__ds0: 1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_54_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0918    ioctrl_55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm0_datain__st: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_wov_pdm0_datain__pu: 1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_wov_pdm0_datain__pd: 1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_wov_pdm0_datain__ds3: 1,    //    12
                              :  3,    //  15:13 reserved
    reg_pad_wov_pdm0_datain__ds2: 1,    //    16
                              :  3,    //  19:17 reserved
    reg_pad_wov_pdm0_datain__ds1: 1,    //    20
                              :  3,    //  23:21 reserved
    reg_pad_wov_pdm0_datain__ds0: 1,    //    24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_55_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_091C    ioctrl_56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm1_datain__st: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_wov_pdm1_datain__pu: 1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_wov_pdm1_datain__pd: 1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_wov_pdm1_datain__ds3: 1,    //    12
                              :  3,    //  15:13 reserved
    reg_pad_wov_pdm1_datain__ds2: 1,    //    16
                              :  3,    //  19:17 reserved
    reg_pad_wov_pdm1_datain__ds1: 1,    //    20
                              :  3,    //  23:21 reserved
    reg_pad_wov_pdm1_datain__ds0: 1,    //    24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_WOV_IOCTRL_56_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0920    ioctrl_57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_6_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_6_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_6_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_6_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_6_3      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_6_2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_6_1      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_6_0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_WOV_IOCTRL_57_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0924    ioctrl_58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_micom_gpio_4_1    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_micom_gpio_4_0    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_micom_gpio_3_7    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_micom_gpio_3_6    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_micom_gpio_3_5    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_micom_gpio_3_4    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_micom_gpio_3_3    :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_micom_gpio_3_2    :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_WOV_IOCTRL_58_O20A0_T;

typedef struct {
    UINT32
    reg_use_micom_gpio_4_1    :  1,    //      0
    reg_use_micom_gpio_4_2    :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_use_micom_gpio_4_0    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_micom_gpio_3_7    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_micom_gpio_3_6    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_micom_gpio_3_5    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_micom_gpio_3_4    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_micom_gpio_3_3    :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_micom_gpio_3_2    :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_WOV_IOCTRL_58_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0928    ioctrl_59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_micom_uart1       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_micom_pwm2        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_micom_pwm1        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_micom_pwm0        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_micom_jtag        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_micom_i2c1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_micom_i2c0        :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_micom_i2c_2_master_sel:  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_WOV_IOCTRL_59_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_092C    ioctrl_60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_xtal__rd0         :  1,    //      0
    reg_pad_xtal__rd1         :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_pad_xtal__ref0        :  1,    //      4
    reg_pad_xtal__ref1        :  1,    //      5
                              : 10,    //  15: 6 reserved
    reg_pad_xtal__ds0         :  1,    //     16
    reg_pad_xtal__ds1         :  1,    //     17
    reg_pad_xtal__ds2         :  1,    //     18
    reg_pad_xtal__ds3         :  1,    //     19
                              : 12;    //  31:20 reserved
}CTOP_CTRL_WOV_IOCTRL_60_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                                   aioplls0                 ;         // 0xC330_0800
CTOP_CTRL_WOV_AIOPLLS1_O20A0_T               aioplls1                 ;         // 0xC330_0804
CTOP_CTRL_WOV_SARADC2_O20A0_T                saradc2                  ;         // 0xC330_0808
CTOP_CTRL_WOV_TXCLKDRV3_O20A0_T              txclkdrv3                ;         // 0xC330_080C
CTOP_CTRL_WOV_JTAG_MUX_O20A0_T               jtag_mux                 ;         // 0xC330_0810
CTOP_CTRL_WOV_UART_MUX_O20A0_T               uart_mux                 ;         // 0xC330_0814
CTOP_CTRL_WOV_INTERRUPT_EN0_O20A0_T          interrupt_en0            ;         // 0xC330_0818
CTOP_CTRL_WOV_GEM_FT_MUX01_O20A0_T           gem_ft_mux01             ;         // 0xC330_081C
CTOP_CTRL_WOV_POWER_CTRL00_O20A0_T           power_ctrl00             ;         // 0xC330_0820
UINT32                                                 _rsvd_00[   1] ;         // 0xC330_0824
CTOP_CTRL_WOV_EDID_REG01_O20A0_T             edid_reg01               ;         // 0xC330_0828
union {
CTOP_CTRL_WOV_IOMUX_DISABLE01_O20A0_T        iomux_disable01          ;         // 0xC330_082C
CTOP_CTRL_WOV_IOMUX_DISABLE01_O20B0_T        iomux_disable01_B0       ;         // 0xC330_082C
};
CTOP_CTRL_WOV_ENABLE01_O20A0_T               enable01                 ;         // 0xC330_0830
CTOP_CTRL_WOV_JTAG01_O20A0_T                 jtag01                   ;         // 0xC330_0834
CTOP_CTRL_WOV_IOCTRL_0_O20A0_T               ioctrl_0                 ;         // 0xC330_0838
CTOP_CTRL_WOV_IOCTRL_1_O20A0_T               ioctrl_1                 ;         // 0xC330_083C
CTOP_CTRL_WOV_IOCTRL_2_O20A0_T               ioctrl_2                 ;         // 0xC330_0840
CTOP_CTRL_WOV_IOCTRL_3_O20A0_T               ioctrl_3                 ;         // 0xC330_0844
CTOP_CTRL_WOV_IOCTRL_4_O20A0_T               ioctrl_4                 ;         // 0xC330_0848
CTOP_CTRL_WOV_IOCTRL_5_O20A0_T               ioctrl_5                 ;         // 0xC330_084C
CTOP_CTRL_WOV_IOCTRL_6_O20A0_T               ioctrl_6                 ;         // 0xC330_0850
CTOP_CTRL_WOV_IOCTRL_7_O20A0_T               ioctrl_7                 ;         // 0xC330_0854
CTOP_CTRL_WOV_IOCTRL_8_O20A0_T               ioctrl_8                 ;         // 0xC330_0858
CTOP_CTRL_WOV_IOCTRL_9_O20A0_T               ioctrl_9                 ;         // 0xC330_085C
CTOP_CTRL_WOV_IOCTRL_10_O20A0_T              ioctrl_10                ;         // 0xC330_0860
CTOP_CTRL_WOV_IOCTRL_11_O20A0_T              ioctrl_11                ;         // 0xC330_0864
CTOP_CTRL_WOV_IOCTRL_12_O20A0_T              ioctrl_12                ;         // 0xC330_0868
CTOP_CTRL_WOV_IOCTRL_13_O20A0_T              ioctrl_13                ;         // 0xC330_086C
CTOP_CTRL_WOV_IOCTRL_14_O20A0_T              ioctrl_14                ;         // 0xC330_0870
CTOP_CTRL_WOV_IOCTRL_15_O20A0_T              ioctrl_15                ;         // 0xC330_0874
CTOP_CTRL_WOV_IOCTRL_16_O20A0_T              ioctrl_16                ;         // 0xC330_0878
CTOP_CTRL_WOV_IOCTRL_17_O20A0_T              ioctrl_17                ;         // 0xC330_087C
CTOP_CTRL_WOV_IOCTRL_18_O20A0_T              ioctrl_18                ;         // 0xC330_0880
CTOP_CTRL_WOV_IOCTRL_19_O20A0_T              ioctrl_19                ;         // 0xC330_0884
CTOP_CTRL_WOV_IOCTRL_20_O20A0_T              ioctrl_20                ;         // 0xC330_0888
CTOP_CTRL_WOV_IOCTRL_21_O20A0_T              ioctrl_21                ;         // 0xC330_088C
CTOP_CTRL_WOV_IOCTRL_22_O20A0_T              ioctrl_22                ;         // 0xC330_0890
CTOP_CTRL_WOV_IOCTRL_23_O20A0_T              ioctrl_23                ;         // 0xC330_0894
CTOP_CTRL_WOV_IOCTRL_24_O20A0_T              ioctrl_24                ;         // 0xC330_0898
CTOP_CTRL_WOV_IOCTRL_25_O20A0_T              ioctrl_25                ;         // 0xC330_089C
CTOP_CTRL_WOV_IOCTRL_26_O20A0_T              ioctrl_26                ;         // 0xC330_08A0
CTOP_CTRL_WOV_IOCTRL_27_O20A0_T              ioctrl_27                ;         // 0xC330_08A4
CTOP_CTRL_WOV_IOCTRL_28_O20A0_T              ioctrl_28                ;         // 0xC330_08A8
CTOP_CTRL_WOV_IOCTRL_29_O20A0_T              ioctrl_29                ;         // 0xC330_08AC
CTOP_CTRL_WOV_IOCTRL_30_O20A0_T              ioctrl_30                ;         // 0xC330_08B0
CTOP_CTRL_WOV_IOCTRL_31_O20A0_T              ioctrl_31                ;         // 0xC330_08B4
CTOP_CTRL_WOV_IOCTRL_32_O20A0_T              ioctrl_32                ;         // 0xC330_08B8
CTOP_CTRL_WOV_IOCTRL_33_O20A0_T              ioctrl_33                ;         // 0xC330_08BC
CTOP_CTRL_WOV_IOCTRL_34_O20A0_T              ioctrl_34                ;         // 0xC330_08C0
CTOP_CTRL_WOV_IOCTRL_35_O20A0_T              ioctrl_35                ;         // 0xC330_08C4
CTOP_CTRL_WOV_IOCTRL_36_O20A0_T              ioctrl_36                ;         // 0xC330_08C8
UINT32                                                 _rsvd_01[   1] ;         // 0xC330_08CC
CTOP_CTRL_WOV_IOCTRL_37_O20A0_T              ioctrl_37                ;         // 0xC330_08D0
CTOP_CTRL_WOV_IOCTRL_38_O20A0_T              ioctrl_38                ;         // 0xC330_08D4
CTOP_CTRL_WOV_IOCTRL_39_O20A0_T              ioctrl_39                ;         // 0xC330_08D8
CTOP_CTRL_WOV_IOCTRL_40_O20A0_T              ioctrl_40                ;         // 0xC330_08DC
CTOP_CTRL_WOV_IOCTRL_41_O20A0_T              ioctrl_41                ;         // 0xC330_08E0
CTOP_CTRL_WOV_IOCTRL_42_O20A0_T              ioctrl_42                ;         // 0xC330_08E4
CTOP_CTRL_WOV_IOCTRL_43_O20A0_T              ioctrl_43                ;         // 0xC330_08E8
CTOP_CTRL_WOV_IOCTRL_44_O20A0_T              ioctrl_44                ;         // 0xC330_08EC
CTOP_CTRL_WOV_IOCTRL_45_O20A0_T              ioctrl_45                ;         // 0xC330_08F0
CTOP_CTRL_WOV_IOCTRL_46_O20A0_T              ioctrl_46                ;         // 0xC330_08F4
CTOP_CTRL_WOV_IOCTRL_47_O20A0_T              ioctrl_47                ;         // 0xC330_08F8
CTOP_CTRL_WOV_IOCTRL_48_O20A0_T              ioctrl_48                ;         // 0xC330_08FC
CTOP_CTRL_WOV_IOCTRL_49_O20A0_T              ioctrl_49                ;         // 0xC330_0900
CTOP_CTRL_WOV_IOCTRL_50_O20A0_T              ioctrl_50                ;         // 0xC330_0904
CTOP_CTRL_WOV_IOCTRL_51_O20A0_T              ioctrl_51                ;         // 0xC330_0908
CTOP_CTRL_WOV_IOCTRL_52_O20A0_T              ioctrl_52                ;         // 0xC330_090C
CTOP_CTRL_WOV_IOCTRL_53_O20A0_T              ioctrl_53                ;         // 0xC330_0910
CTOP_CTRL_WOV_IOCTRL_54_O20A0_T              ioctrl_54                ;         // 0xC330_0914
CTOP_CTRL_WOV_IOCTRL_55_O20A0_T              ioctrl_55                ;         // 0xC330_0918
CTOP_CTRL_WOV_IOCTRL_56_O20A0_T              ioctrl_56                ;         // 0xC330_091C
CTOP_CTRL_WOV_IOCTRL_57_O20A0_T              ioctrl_57                ;         // 0xC330_0920
union {
CTOP_CTRL_WOV_IOCTRL_58_O20A0_T              ioctrl_58                ;         // 0xC330_0924
CTOP_CTRL_WOV_IOCTRL_58_O20B0_T              ioctrl_58_B0             ;         // 0xC330_0924
};
CTOP_CTRL_WOV_IOCTRL_59_O20A0_T              ioctrl_59                ;         // 0xC330_0928
CTOP_CTRL_WOV_IOCTRL_60_O20A0_T              ioctrl_60                ;         // 0xC330_092C
} CTOP_CTRL_WOV_REG_O20A0_T;
/* 74 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_WOV_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

