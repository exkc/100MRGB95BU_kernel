#ifndef _CTOP_CTRL_FMS_O20A0_REG_H_
#define _CTOP_CTRL_FMS_O20A0_REG_H_

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
    0xC930_E400    disp_aiopll0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_aiopll_fine_div       :  1,    //      1
    reg_aiopll_dss            :  1,    //      2
    reg_aiopll_accuracy       :  2,    //   4: 3
    reg_aiopll_updn_max       :  7,    //  11: 5
    reg_aiopll_mod_freq_max   :  9,    //  20:12
    reg_aiopll_m              :  6,    //  26:21
                              :  1,    //     27 reserved
    reg_aiopll_cih            :  4;    //  31:28
}CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E404    disp_aiopll1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_lock           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aiopll_offset_mode    :  1,    //      4
    reg_aiopll_fout3_post_od  :  3,    //   7: 5
    reg_aiopll_fout2_post_od  :  3,    //  10: 8
    reg_aiopll_fout_od        :  2,    //  12:11
    reg_aiopll_fout3_pre_od   :  3,    //  15:13
    reg_aiopll_fout2_pre_od   :  3,    //  18:16
    reg_aiopll_nsc            :  4,    //  22:19
    reg_aiopll_npc            :  6,    //  28:23
    reg_aiopll_fine_control   :  3;    //  31:29
}CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E408    disp_aiopll2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_freq_update    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aiopll_sync_on        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_aiopll_in_sel         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_aiopll_pdb            :  1,    //     12
                              :  9,    //  21:13 reserved
    reg_aiopll_wake_bypass    :  1,    //     22
    reg_aiopll_ddr_mode       :  1,    //     23
    reg_aiopll_offset         :  8;    //  31:24
}CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E40C    gpu_aioplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aioplls_pdb           :  1,    //      0
    reg_aioplls_lock          :  1,    //      1
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
}CTOP_CTRL_FMS_GPU_AIOPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E410    pqe_frplls0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_fin_sel         :  1,    //      0
    reg_frpll_in_divsel       :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_frpll_fout_en         :  1,    //      4
    reg_frpll_fout2_en        :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_frpll_auto_freq       :  1,    //      8
    reg_frpll_frequp          :  1,    //      9
    reg_frpll_syncon          :  1,    //     10
                              :  1,    //     11 reserved
    reg_frpll_icp             :  4,    //  15:12
    reg_frpll_icp_g           :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_frpll_a               :  6,    //  25:20
                              :  2,    //  27:26 reserved
    reg_frpll_dsmon           :  1,    //     28
    reg_frpll_dsm_limit       :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_FMS_PQE_FRPLLS0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E414    pqe_frplls1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_fcw             : 24,    //  23: 0
    reg_frpll_m               :  6,    //  29:24
                              :  1,    //     30 reserved
    reg_frpll_lpf_on          :  1;    //     31
}CTOP_CTRL_FMS_PQE_FRPLLS1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E418    pqe_frplls2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_pdb             :  1,    //      0
    reg_frpll_lock            :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_frpll_in_divrstb      :  1,    //      4
    reg_frpll_wakeup_bypass   :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_frpll_divint          :  9,    //  16: 8
                              :  3,    //  19:17 reserved
    reg_frpll_out_div         :  9,    //  28:20
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_PQE_FRPLLS2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E41C    rxclkdrv8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_pdb          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_rxclkdrv_smv          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_rxclkdrv_cksel        :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}CTOP_CTRL_FMS_RXCLKDRV8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E420    crg_top00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_frpll_ext_sel         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_disp594_clk_gate_en   :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_FMS_CRG_TOP00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E424    iosel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mon3_en               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_jtag3_disable         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_jtag1_disable         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_fsc_en                :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_dvb_out_ctrl1         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_dvb_out_ctrl0         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_stpi0_out_ctrl1       :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_stpi0_out_ctrl0       :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_IOSEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E428    mon_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mon_sel0              :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_mon_sel1              :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_mon_sel2              :  5,    //  20:16
                              :  3,    //  23:21 reserved
    reg_mon_sel3              :  5,    //  28:24
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_MON_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E42C    gpio12_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_12_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_12_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_12_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_12_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_12_3     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_12_2     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_12_1     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_12_0     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO12_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E430    gpio13_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_13_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_13_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_13_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_13_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_13_3     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_13_2     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_13_1     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_13_0     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO13_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E434    gpio16_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_16_1     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_16_0     :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_FMS_GPIO16_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E438    gpio17_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_17_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_17_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_17_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_17_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_17_3     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_17_2     :  1,    //     20
                              :  7,    //  27:21 reserved
    reg_use_cpu_gpio_17_0     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO17_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E43C    gpio3_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_3_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_3_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_3_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_3_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_3_3      :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_FMS_GPIO3_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E440    gpio4_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_4_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_4_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_4_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_4_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_4_3      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_4_2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_4_1      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_4_0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO4_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E444    gpio5_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_5_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_5_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_5_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_5_4      :  1,    //     12
                              : 15,    //  27:13 reserved
    reg_use_cpu_gpio_5_0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO5_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E448    gpio8_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_8_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_8_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_8_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_8_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_8_3      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_8_2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_8_1      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_GPIO8_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E44C    gpio9_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_9_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_9_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_9_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_9_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_9_3      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_9_2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_9_1      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_9_0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FMS_GPIO9_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E450    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqc__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_diseqc__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_diseqc__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_diseqc__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_diseqc__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_diseqc__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_diseqc__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E454    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqc_cmd__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_diseqc_cmd__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_diseqc_cmd__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_diseqc_cmd__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_diseqc_cmd__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_diseqc_cmd__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_diseqc_cmd__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E458    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqci__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_diseqci__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_diseqci__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_diseqci__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_diseqci__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_diseqci__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_diseqci__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E45C    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_fefctrl__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_fefctrl__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_fefctrl__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_fefctrl__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_fefctrl__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_fefctrl__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_fefctrl__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E460    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio0__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio0__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio0__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio0__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio0__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio0__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio0__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E464    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio1__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio1__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio1__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio1__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio1__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio1__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio1__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E468    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio10__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio10__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio10__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio10__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio10__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio10__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio10__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E46C    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio11__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio11__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio11__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio11__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio11__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio11__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio11__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E470    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio12__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio12__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio12__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio12__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio12__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio12__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio12__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E474    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio13__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio13__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio13__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio13__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio13__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio13__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio13__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E478    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio14__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio14__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio14__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio14__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio14__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio14__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio14__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E47C    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio15__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio15__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio15__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio15__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio15__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio15__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio15__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E480    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio2__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio2__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio2__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio2__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio2__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio2__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio2__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E484    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio26__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio26__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio26__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio26__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio26__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio26__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio26__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E488    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio3__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio3__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio3__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio3__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio3__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio3__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio3__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E48C    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio4__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio4__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio4__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio4__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio4__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio4__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio4__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E490    ioctrl_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio5__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio5__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio5__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio5__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio5__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio5__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio5__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E494    ioctrl_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio6__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio6__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio6__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio6__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio6__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio6__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio6__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E498    ioctrl_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio7__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio7__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio7__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio7__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio7__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio7__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio7__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E49C    ioctrl_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio8__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio8__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio8__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio8__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio8__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio8__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio8__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A0    ioctrl_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio9__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio9__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio9__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio9__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio9__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio9__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio9__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A4    ioctrl_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_iec958out__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_iec958out__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_iec958out__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_iec958out__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_iec958out__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_iec958out__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_iec958out__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4A8    ioctrl_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ifagc__st         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_ifagc__pu         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_ifagc__pd         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_ifagc__ds3        :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_ifagc__ds2        :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_ifagc__ds1        :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_ifagc__ds0        :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4AC    ioctrl_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ifagc_s__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_ifagc_s__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_ifagc_s__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_ifagc_s__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_ifagc_s__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_ifagc_s__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_ifagc_s__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B0    ioctrl_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_mdc__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_mdc__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_mdc__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_mdc__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_mdc__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_mdc__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_mdc__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B4    ioctrl_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_mdio__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_mdio__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_mdio__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_mdio__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_mdio__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_mdio__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_mdio__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4B8    ioctrl_26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_ref_clk__st :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_ref_clk__pu :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_ref_clk__pd :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_ref_clk__ds3:  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_ref_clk__ds2:  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_ref_clk__ds1:  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_ref_clk__ds0:  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_26_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4BC    ioctrl_27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rx_clk__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rx_clk__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rx_clk__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rx_clk__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rx_clk__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rx_clk__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rx_clk__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_27_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4C0    ioctrl_28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rx_ctl__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rx_ctl__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rx_ctl__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rx_ctl__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rx_ctl__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rx_ctl__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rx_ctl__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_28_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4C4    ioctrl_29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_0__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rxd_0__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rxd_0__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rxd_0__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rxd_0__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rxd_0__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rxd_0__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_29_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4C8    ioctrl_30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_1__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rxd_1__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rxd_1__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rxd_1__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rxd_1__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rxd_1__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rxd_1__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_30_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4CC    ioctrl_31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_2__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rxd_2__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rxd_2__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rxd_2__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rxd_2__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rxd_2__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rxd_2__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_31_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4D0    ioctrl_32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_3__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_rxd_3__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_rxd_3__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_rxd_3__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_rxd_3__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_rxd_3__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_rxd_3__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_32_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4D4    ioctrl_33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_tx_clk__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_tx_clk__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_tx_clk__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_tx_clk__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_tx_clk__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_tx_clk__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_tx_clk__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_33_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4D8    ioctrl_34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_tx_ctl__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_tx_ctl__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_tx_ctl__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_tx_ctl__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_tx_ctl__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_tx_ctl__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_tx_ctl__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_34_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4DC    ioctrl_35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_0__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_txd_0__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_txd_0__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_txd_0__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_txd_0__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_txd_0__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_txd_0__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_35_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4E0    ioctrl_36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_1__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_txd_1__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_txd_1__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_txd_1__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_txd_1__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_txd_1__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_txd_1__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_36_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4E4    ioctrl_37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_2__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_txd_2__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_txd_2__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_txd_2__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_txd_2__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_txd_2__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_txd_2__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_37_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4E8    ioctrl_38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_3__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_rgmii_txd_3__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_rgmii_txd_3__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_rgmii_txd_3__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_rgmii_txd_3__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_rgmii_txd_3__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_rgmii_txd_3__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_38_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4EC    ioctrl_39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl0__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl0__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl0__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl0__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl0__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl0__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl0__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_39_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4F0    ioctrl_40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl1__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl1__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl1__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl1__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl1__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl1__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl1__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_40_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4F4    ioctrl_41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl2__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl2__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl2__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl2__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl2__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl2__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl2__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_41_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4F8    ioctrl_42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl3__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl3__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl3__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl3__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl3__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl3__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl3__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_42_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E4FC    ioctrl_43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl4__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl4__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl4__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl4__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl4__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl4__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl4__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_43_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E500    ioctrl_44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl5__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_scl5__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_scl5__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_scl5__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_scl5__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_scl5__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_scl5__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_44_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E504    ioctrl_45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda0__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda0__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda0__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda0__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda0__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda0__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda0__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_45_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E508    ioctrl_46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda1__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda1__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda1__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda1__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda1__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda1__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda1__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_46_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E50C    ioctrl_47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda2__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda2__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda2__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda2__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda2__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda2__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda2__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_47_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E510    ioctrl_48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda3__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda3__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda3__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda3__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda3__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda3__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda3__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_48_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E514    ioctrl_49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda4__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda4__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda4__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda4__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda4__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda4__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda4__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_49_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E518    ioctrl_50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda5__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_sda5__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_sda5__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_sda5__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_sda5__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_sda5__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_sda5__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_50_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E51C    ioctrl_51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_cs0__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_cs0__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_cs0__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_cs0__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_cs0__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_cs0__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_cs0__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_51_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E520    ioctrl_52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_cs1__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_cs1__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_cs1__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_cs1__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_cs1__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_cs1__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_cs1__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_52_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E524    ioctrl_53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_di0__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_di0__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_di0__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_di0__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_di0__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_di0__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_di0__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_53_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E528    ioctrl_54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_di1__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_di1__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_di1__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_di1__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_di1__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_di1__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_di1__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_54_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E52C    ioctrl_55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_do0__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_do0__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_do0__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_do0__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_do0__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_do0__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_do0__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_55_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E530    ioctrl_56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_do1__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_do1__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_do1__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_do1__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_do1__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_do1__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_do1__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_56_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E534    ioctrl_57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk0__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_sclk0__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_sclk0__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_sclk0__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_sclk0__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_sclk0__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_sclk0__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_57_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E538    ioctrl_58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk1__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_spi_sclk1__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_spi_sclk1__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_spi_sclk1__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_spi_sclk1__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_spi_sclk1__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_spi_sclk1__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_58_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E53C    ioctrl_59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_clk__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_clk__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_clk__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_clk__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_clk__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_clk__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_clk__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_59_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E540    ioctrl_60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data0__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data0__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data0__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data0__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data0__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data0__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data0__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_60_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E544    ioctrl_61 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data1__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data1__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data1__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data1__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data1__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data1__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data1__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_61_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E548    ioctrl_62 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data2__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data2__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data2__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data2__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data2__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data2__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data2__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_62_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E54C    ioctrl_63 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data3__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data3__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data3__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data3__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data3__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data3__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data3__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_63_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E550    ioctrl_64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data4__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data4__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data4__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data4__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data4__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data4__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data4__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_64_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E554    ioctrl_65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data5__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data5__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data5__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data5__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data5__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data5__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data5__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_65_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E558    ioctrl_66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data6__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data6__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data6__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data6__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data6__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data6__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data6__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_66_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E55C    ioctrl_67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_data7__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_data7__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_data7__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_data7__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_data7__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_data7__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_data7__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_67_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E560    ioctrl_68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_sop__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_sop__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_sop__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_sop__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_sop__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_sop__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_sop__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_68_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E564    ioctrl_69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_stpi0_val__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_stpi0_val__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_stpi0_val__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_stpi0_val__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_stpi0_val__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_stpi0_val__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_stpi0_val__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_69_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E568    ioctrl_70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_clk__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_clk__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_clk__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_clk__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_clk__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_clk__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_clk__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_70_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E56C    ioctrl_71 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data0__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data0__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data0__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data0__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data0__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data0__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data0__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_71_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E570    ioctrl_72 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data1__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data1__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data1__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data1__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data1__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data1__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data1__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_72_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E574    ioctrl_73 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data2__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data2__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data2__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data2__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data2__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data2__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data2__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_73_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E578    ioctrl_74 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data3__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data3__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data3__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data3__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data3__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data3__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data3__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_74_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E57C    ioctrl_75 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data4__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data4__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data4__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data4__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data4__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data4__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data4__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_75_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E580    ioctrl_76 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data5__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data5__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data5__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data5__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data5__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data5__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data5__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_76_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E584    ioctrl_77 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data6__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data6__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data6__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data6__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data6__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data6__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data6__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_77_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E58C    ioctrl_78 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_data7__st  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_data7__pu  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_data7__pd  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_data7__ds3 :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_data7__ds2 :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_data7__ds1 :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_data7__ds0 :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_78_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E590    ioctrl_79 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_sop__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_sop__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_sop__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_sop__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_sop__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_sop__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_sop__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_79_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E594    ioctrl_80 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tp_dvb_val__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tp_dvb_val__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tp_dvb_val__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tp_dvb_val__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tp_dvb_val__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tp_dvb_val__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tp_dvb_val__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_80_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E598    ioctrl_81 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_rxd__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart0_rxd__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart0_rxd__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart0_rxd__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart0_rxd__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart0_rxd__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart0_rxd__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_81_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E59C    ioctrl_82 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_txd__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart0_txd__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart0_txd__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart0_txd__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart0_txd__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart0_txd__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart0_txd__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_82_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5A0    ioctrl_83 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_cts__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart1_cts__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart1_cts__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart1_cts__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart1_cts__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart1_cts__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart1_cts__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_83_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5A4    ioctrl_84 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_rts__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart1_rts__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart1_rts__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart1_rts__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart1_rts__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart1_rts__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart1_rts__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_84_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5A8    ioctrl_85 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_rxd__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart1_rxd__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart1_rxd__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart1_rxd__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart1_rxd__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart1_rxd__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart1_rxd__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_85_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5AC    ioctrl_86 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_txd__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_uart1_txd__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_uart1_txd__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_uart1_txd__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_uart1_txd__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_uart1_txd__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_uart1_txd__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FMS_IOCTRL_86_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5B0    iomux_disable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_uart1_disable         :  1,    //      0
    reg_uart0_disable         :  1,    //      1
    reg_spi1_disable          :  1,    //      2
    reg_spi0_disable          :  1,    //      3
    reg_rgmii_disable         :  1,    //      4
    reg_i2c5_disable          :  1,    //      5
    reg_i2c4_disable          :  1,    //      6
    reg_i2c3_disable          :  1,    //      7
    reg_i2c2_disable          :  1,    //      8
    reg_i2c1_disable          :  1,    //      9
    reg_i2c0_disable          :  1,    //     10
    reg_aud_sub_en            :  1,    //     11
                              : 20;    //  31:12 reserved
}CTOP_CTRL_FMS_IOMUX_DISABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E5B4    fsc_gpio_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fsc_gpio_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_FMS_FSC_GPIO_SEL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T           disp_aiopll0             ;         // 0xC930_E400
CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T           disp_aiopll1             ;         // 0xC930_E404
CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T           disp_aiopll2             ;         // 0xC930_E408
CTOP_CTRL_FMS_GPU_AIOPLLS0_O20A0_T           gpu_aioplls0             ;         // 0xC930_E40C
CTOP_CTRL_FMS_PQE_FRPLLS0_O20A0_T            pqe_frplls0              ;         // 0xC930_E410
CTOP_CTRL_FMS_PQE_FRPLLS1_O20A0_T            pqe_frplls1              ;         // 0xC930_E414
CTOP_CTRL_FMS_PQE_FRPLLS2_O20A0_T            pqe_frplls2              ;         // 0xC930_E418
CTOP_CTRL_FMS_RXCLKDRV8_O20A0_T              rxclkdrv8                ;         // 0xC930_E41C
CTOP_CTRL_FMS_CRG_TOP00_O20A0_T              crg_top00                ;         // 0xC930_E420
CTOP_CTRL_FMS_IOSEL_O20A0_T                  iosel                    ;         // 0xC930_E424
CTOP_CTRL_FMS_MON_SEL_O20A0_T                mon_sel                  ;         // 0xC930_E428
CTOP_CTRL_FMS_GPIO12_SEL_O20A0_T             gpio12_sel               ;         // 0xC930_E42C
CTOP_CTRL_FMS_GPIO13_SEL_O20A0_T             gpio13_sel               ;         // 0xC930_E430
CTOP_CTRL_FMS_GPIO16_SEL_O20A0_T             gpio16_sel               ;         // 0xC930_E434
CTOP_CTRL_FMS_GPIO17_SEL_O20A0_T             gpio17_sel               ;         // 0xC930_E438
CTOP_CTRL_FMS_GPIO3_SEL_O20A0_T              gpio3_sel                ;         // 0xC930_E43C
CTOP_CTRL_FMS_GPIO4_SEL_O20A0_T              gpio4_sel                ;         // 0xC930_E440
CTOP_CTRL_FMS_GPIO5_SEL_O20A0_T              gpio5_sel                ;         // 0xC930_E444
CTOP_CTRL_FMS_GPIO8_SEL_O20A0_T              gpio8_sel                ;         // 0xC930_E448
CTOP_CTRL_FMS_GPIO9_SEL_O20A0_T              gpio9_sel                ;         // 0xC930_E44C
CTOP_CTRL_FMS_IOCTRL_0_O20A0_T               ioctrl_0                 ;         // 0xC930_E450
CTOP_CTRL_FMS_IOCTRL_1_O20A0_T               ioctrl_1                 ;         // 0xC930_E454
CTOP_CTRL_FMS_IOCTRL_2_O20A0_T               ioctrl_2                 ;         // 0xC930_E458
CTOP_CTRL_FMS_IOCTRL_3_O20A0_T               ioctrl_3                 ;         // 0xC930_E45C
CTOP_CTRL_FMS_IOCTRL_4_O20A0_T               ioctrl_4                 ;         // 0xC930_E460
CTOP_CTRL_FMS_IOCTRL_5_O20A0_T               ioctrl_5                 ;         // 0xC930_E464
CTOP_CTRL_FMS_IOCTRL_6_O20A0_T               ioctrl_6                 ;         // 0xC930_E468
CTOP_CTRL_FMS_IOCTRL_7_O20A0_T               ioctrl_7                 ;         // 0xC930_E46C
CTOP_CTRL_FMS_IOCTRL_8_O20A0_T               ioctrl_8                 ;         // 0xC930_E470
CTOP_CTRL_FMS_IOCTRL_9_O20A0_T               ioctrl_9                 ;         // 0xC930_E474
CTOP_CTRL_FMS_IOCTRL_10_O20A0_T              ioctrl_10                ;         // 0xC930_E478
CTOP_CTRL_FMS_IOCTRL_11_O20A0_T              ioctrl_11                ;         // 0xC930_E47C
CTOP_CTRL_FMS_IOCTRL_12_O20A0_T              ioctrl_12                ;         // 0xC930_E480
CTOP_CTRL_FMS_IOCTRL_13_O20A0_T              ioctrl_13                ;         // 0xC930_E484
CTOP_CTRL_FMS_IOCTRL_14_O20A0_T              ioctrl_14                ;         // 0xC930_E488
CTOP_CTRL_FMS_IOCTRL_15_O20A0_T              ioctrl_15                ;         // 0xC930_E48C
CTOP_CTRL_FMS_IOCTRL_16_O20A0_T              ioctrl_16                ;         // 0xC930_E490
CTOP_CTRL_FMS_IOCTRL_17_O20A0_T              ioctrl_17                ;         // 0xC930_E494
CTOP_CTRL_FMS_IOCTRL_18_O20A0_T              ioctrl_18                ;         // 0xC930_E498
CTOP_CTRL_FMS_IOCTRL_19_O20A0_T              ioctrl_19                ;         // 0xC930_E49C
CTOP_CTRL_FMS_IOCTRL_20_O20A0_T              ioctrl_20                ;         // 0xC930_E4A0
CTOP_CTRL_FMS_IOCTRL_21_O20A0_T              ioctrl_21                ;         // 0xC930_E4A4
CTOP_CTRL_FMS_IOCTRL_22_O20A0_T              ioctrl_22                ;         // 0xC930_E4A8
CTOP_CTRL_FMS_IOCTRL_23_O20A0_T              ioctrl_23                ;         // 0xC930_E4AC
CTOP_CTRL_FMS_IOCTRL_24_O20A0_T              ioctrl_24                ;         // 0xC930_E4B0
CTOP_CTRL_FMS_IOCTRL_25_O20A0_T              ioctrl_25                ;         // 0xC930_E4B4
CTOP_CTRL_FMS_IOCTRL_26_O20A0_T              ioctrl_26                ;         // 0xC930_E4B8
CTOP_CTRL_FMS_IOCTRL_27_O20A0_T              ioctrl_27                ;         // 0xC930_E4BC
CTOP_CTRL_FMS_IOCTRL_28_O20A0_T              ioctrl_28                ;         // 0xC930_E4C0
CTOP_CTRL_FMS_IOCTRL_29_O20A0_T              ioctrl_29                ;         // 0xC930_E4C4
CTOP_CTRL_FMS_IOCTRL_30_O20A0_T              ioctrl_30                ;         // 0xC930_E4C8
CTOP_CTRL_FMS_IOCTRL_31_O20A0_T              ioctrl_31                ;         // 0xC930_E4CC
CTOP_CTRL_FMS_IOCTRL_32_O20A0_T              ioctrl_32                ;         // 0xC930_E4D0
CTOP_CTRL_FMS_IOCTRL_33_O20A0_T              ioctrl_33                ;         // 0xC930_E4D4
CTOP_CTRL_FMS_IOCTRL_34_O20A0_T              ioctrl_34                ;         // 0xC930_E4D8
CTOP_CTRL_FMS_IOCTRL_35_O20A0_T              ioctrl_35                ;         // 0xC930_E4DC
CTOP_CTRL_FMS_IOCTRL_36_O20A0_T              ioctrl_36                ;         // 0xC930_E4E0
CTOP_CTRL_FMS_IOCTRL_37_O20A0_T              ioctrl_37                ;         // 0xC930_E4E4
CTOP_CTRL_FMS_IOCTRL_38_O20A0_T              ioctrl_38                ;         // 0xC930_E4E8
CTOP_CTRL_FMS_IOCTRL_39_O20A0_T              ioctrl_39                ;         // 0xC930_E4EC
CTOP_CTRL_FMS_IOCTRL_40_O20A0_T              ioctrl_40                ;         // 0xC930_E4F0
CTOP_CTRL_FMS_IOCTRL_41_O20A0_T              ioctrl_41                ;         // 0xC930_E4F4
CTOP_CTRL_FMS_IOCTRL_42_O20A0_T              ioctrl_42                ;         // 0xC930_E4F8
CTOP_CTRL_FMS_IOCTRL_43_O20A0_T              ioctrl_43                ;         // 0xC930_E4FC
CTOP_CTRL_FMS_IOCTRL_44_O20A0_T              ioctrl_44                ;         // 0xC930_E500
CTOP_CTRL_FMS_IOCTRL_45_O20A0_T              ioctrl_45                ;         // 0xC930_E504
CTOP_CTRL_FMS_IOCTRL_46_O20A0_T              ioctrl_46                ;         // 0xC930_E508
CTOP_CTRL_FMS_IOCTRL_47_O20A0_T              ioctrl_47                ;         // 0xC930_E50C
CTOP_CTRL_FMS_IOCTRL_48_O20A0_T              ioctrl_48                ;         // 0xC930_E510
CTOP_CTRL_FMS_IOCTRL_49_O20A0_T              ioctrl_49                ;         // 0xC930_E514
CTOP_CTRL_FMS_IOCTRL_50_O20A0_T              ioctrl_50                ;         // 0xC930_E518
CTOP_CTRL_FMS_IOCTRL_51_O20A0_T              ioctrl_51                ;         // 0xC930_E51C
CTOP_CTRL_FMS_IOCTRL_52_O20A0_T              ioctrl_52                ;         // 0xC930_E520
CTOP_CTRL_FMS_IOCTRL_53_O20A0_T              ioctrl_53                ;         // 0xC930_E524
CTOP_CTRL_FMS_IOCTRL_54_O20A0_T              ioctrl_54                ;         // 0xC930_E528
CTOP_CTRL_FMS_IOCTRL_55_O20A0_T              ioctrl_55                ;         // 0xC930_E52C
CTOP_CTRL_FMS_IOCTRL_56_O20A0_T              ioctrl_56                ;         // 0xC930_E530
CTOP_CTRL_FMS_IOCTRL_57_O20A0_T              ioctrl_57                ;         // 0xC930_E534
CTOP_CTRL_FMS_IOCTRL_58_O20A0_T              ioctrl_58                ;         // 0xC930_E538
CTOP_CTRL_FMS_IOCTRL_59_O20A0_T              ioctrl_59                ;         // 0xC930_E53C
CTOP_CTRL_FMS_IOCTRL_60_O20A0_T              ioctrl_60                ;         // 0xC930_E540
CTOP_CTRL_FMS_IOCTRL_61_O20A0_T              ioctrl_61                ;         // 0xC930_E544
CTOP_CTRL_FMS_IOCTRL_62_O20A0_T              ioctrl_62                ;         // 0xC930_E548
CTOP_CTRL_FMS_IOCTRL_63_O20A0_T              ioctrl_63                ;         // 0xC930_E54C
CTOP_CTRL_FMS_IOCTRL_64_O20A0_T              ioctrl_64                ;         // 0xC930_E550
CTOP_CTRL_FMS_IOCTRL_65_O20A0_T              ioctrl_65                ;         // 0xC930_E554
CTOP_CTRL_FMS_IOCTRL_66_O20A0_T              ioctrl_66                ;         // 0xC930_E558
CTOP_CTRL_FMS_IOCTRL_67_O20A0_T              ioctrl_67                ;         // 0xC930_E55C
CTOP_CTRL_FMS_IOCTRL_68_O20A0_T              ioctrl_68                ;         // 0xC930_E560
CTOP_CTRL_FMS_IOCTRL_69_O20A0_T              ioctrl_69                ;         // 0xC930_E564
CTOP_CTRL_FMS_IOCTRL_70_O20A0_T              ioctrl_70                ;         // 0xC930_E568
CTOP_CTRL_FMS_IOCTRL_71_O20A0_T              ioctrl_71                ;         // 0xC930_E56C
CTOP_CTRL_FMS_IOCTRL_72_O20A0_T              ioctrl_72                ;         // 0xC930_E570
CTOP_CTRL_FMS_IOCTRL_73_O20A0_T              ioctrl_73                ;         // 0xC930_E574
CTOP_CTRL_FMS_IOCTRL_74_O20A0_T              ioctrl_74                ;         // 0xC930_E578
CTOP_CTRL_FMS_IOCTRL_75_O20A0_T              ioctrl_75                ;         // 0xC930_E57C
CTOP_CTRL_FMS_IOCTRL_76_O20A0_T              ioctrl_76                ;         // 0xC930_E580
CTOP_CTRL_FMS_IOCTRL_77_O20A0_T              ioctrl_77                ;         // 0xC930_E584
UINT32                                                 _rsvd_00[   1] ;         // 0xC930_E588
CTOP_CTRL_FMS_IOCTRL_78_O20A0_T              ioctrl_78                ;         // 0xC930_E58C
CTOP_CTRL_FMS_IOCTRL_79_O20A0_T              ioctrl_79                ;         // 0xC930_E590
CTOP_CTRL_FMS_IOCTRL_80_O20A0_T              ioctrl_80                ;         // 0xC930_E594
CTOP_CTRL_FMS_IOCTRL_81_O20A0_T              ioctrl_81                ;         // 0xC930_E598
CTOP_CTRL_FMS_IOCTRL_82_O20A0_T              ioctrl_82                ;         // 0xC930_E59C
CTOP_CTRL_FMS_IOCTRL_83_O20A0_T              ioctrl_83                ;         // 0xC930_E5A0
CTOP_CTRL_FMS_IOCTRL_84_O20A0_T              ioctrl_84                ;         // 0xC930_E5A4
CTOP_CTRL_FMS_IOCTRL_85_O20A0_T              ioctrl_85                ;         // 0xC930_E5A8
CTOP_CTRL_FMS_IOCTRL_86_O20A0_T              ioctrl_86                ;         // 0xC930_E5AC
CTOP_CTRL_FMS_IOMUX_DISABLE01_O20A0_T        iomux_disable01          ;         // 0xC930_E5B0
CTOP_CTRL_FMS_FSC_GPIO_SEL_O20A0_T           fsc_gpio_sel             ;         // 0xC930_E5B4
} CTOP_CTRL_FMS_REG_O20A0_T;
/* 109 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_FMS_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

