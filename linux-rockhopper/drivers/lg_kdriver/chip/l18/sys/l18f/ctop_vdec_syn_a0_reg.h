#ifndef _CTOP_VDEC_SYN_A0_REG_H_
#define _CTOP_VDEC_SYN_A0_REG_H_

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
    0xC9C7_0400    syn_vdec00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c7_enable           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_audclk_out_enable     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_ext_intr_enable   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cpu_i2c2_disable      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_cpu_i2c1_disable      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_cpu_i2c0_disable      :  1,    //     20
                              : 11;    //  31:21 reserved
}VDEC_SYN_SYN_VDEC00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0404    syn_vdec01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    reg_use_cpu_gpio_15_5     :  1,    //     13
    reg_use_cpu_gpio_15_6     :  1,    //     14
    reg_use_cpu_gpio_15_7     :  1,    //     15
    reg_use_cpu_gpio_16_0     :  1,    //     16
    reg_use_cpu_gpio_16_1     :  1,    //     17
    reg_use_cpu_gpio_16_2     :  1,    //     18
    reg_use_cpu_gpio_16_3     :  1,    //     19
    reg_use_cpu_gpio_16_4     :  1,    //     20
    reg_use_cpu_gpio_16_5     :  1,    //     21
    reg_use_cpu_gpio_16_6     :  1,    //     22
    reg_use_cpu_gpio_16_7     :  1,    //     23
    reg_use_cpu_gpio_17_0     :  1,    //     24
    reg_use_cpu_gpio_17_1     :  1,    //     25
    reg_use_cpu_gpio_17_2     :  1,    //     26
    reg_use_cpu_gpio_17_3     :  1,    //     27
    reg_use_cpu_gpio_17_4     :  1,    //     28
    reg_use_cpu_gpio_17_5     :  1,    //     29
                              :  2;    //  31:30 reserved
}VDEC_SYN_SYN_VDEC01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0408    syn_vdec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_txd__ren    :  1,    //      0
    reg_pad_uart0_rxd__ren    :  1,    //      1
    reg_pad_spi_sclk1__ren    :  1,    //      2
    reg_pad_spi_do1__ren      :  1,    //      3
    reg_pad_spi_di1__ren      :  1,    //      4
    reg_pad_spi_cs1__ren      :  1,    //      5
    reg_pad_sda2__pd          :  1,    //      6
    reg_pad_sda2__pu          :  1,    //      7
    reg_pad_sda2__ds          :  1,    //      8
    reg_pad_sda1__pd          :  1,    //      9
    reg_pad_sda1__pu          :  1,    //     10
    reg_pad_sda1__ds          :  1,    //     11
    reg_pad_sda0__pd          :  1,    //     12
    reg_pad_sda0__pu          :  1,    //     13
    reg_pad_sda0__ds          :  1,    //     14
    reg_pad_scl2__pd          :  1,    //     15
    reg_pad_scl2__pu          :  1,    //     16
    reg_pad_scl2__ds          :  1,    //     17
    reg_pad_scl1__pd          :  1,    //     18
    reg_pad_scl1__pu          :  1,    //     19
    reg_pad_scl1__ds          :  1,    //     20
    reg_pad_scl0__pd          :  1,    //     21
    reg_pad_scl0__pu          :  1,    //     22
    reg_pad_scl0__ds          :  1,    //     23
    reg_pad_pwm_in__ren       :  1,    //     24
    reg_pad_pwm2__ren         :  1,    //     25
    reg_pad_pwm1__ren         :  1,    //     26
    reg_pad_pwm0__ren         :  1,    //     27
    reg_pad_ext_intr0__ren    :  1,    //     28
                              :  3;    //  31:29 reserved
}VDEC_SYN_SYN_VDEC02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_040C    syn_vdec03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_audclk_out__ren   :  1,    //      0
                              : 31;    //   31:1 reserved
}VDEC_SYN_SYN_VDEC03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0410    syn_vdec04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag0_sel             :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_jtag1_sel             :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_jtag_sel_te           :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_jtag_sel_pmcu         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_jtag_sel_aud          :  1,    //     16
                              : 15;    //  31:17 reserved
}VDEC_SYN_SYN_VDEC04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0414    syn_vdec05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_uart0_sel             :  4,    //   3: 0
    reg_uart1_sel             :  4,    //   7: 4
    reg_rx_sel_tz             :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_rx_sel_te             :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_rx_sel_pmcu           :  1,    //     16
                              : 15;    //  31:17 reserved
}VDEC_SYN_SYN_VDEC05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0418    syn_vdec22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ltx_sel_hs            :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ltx_sel_plllock       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ltx_cih               :  3,    //  10: 8
                              :  5,    //  15:11 reserved
    reg_ltx_adj_term          :  4,    //  19:16
    reg_ltx_sel_lock          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_ltx_rf                :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_ltx_pdb               :  1,    //     28
                              :  3;    //  31:29 reserved
}VDEC_SYN_SYN_VDEC22_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_041C    syn_vdec23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ltx_itune4            :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_ltx_itune3            :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_ltx_itune2            :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_ltx_itune1            :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_ltx_itune0            :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_ltx_lock_samp_ctl     :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_ltx_lock_div_ctl      :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_ltx_sel_lpf           :  1,    //     28
                              :  3;    //  31:29 reserved
}VDEC_SYN_SYN_VDEC23_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0420    syn_vdec24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_ltx_itune11           :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_ltx_itune10           :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_ltx_itune9            :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_ltx_itune8            :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_ltx_itune7            :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_ltx_itune6            :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_ltx_itune5            :  3,    //  30:28
                              :  1;    //  31:31 reserved
}VDEC_SYN_SYN_VDEC24_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0424    syn_vdec25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ltx_flip_en_ch0       :  1,    //      0
    reg_ltx_flip_en_ch1       :  1,    //      1
    reg_ltx_flip_en_ch2       :  1,    //      2
    reg_ltx_flip_en_ch3       :  1,    //      3
    reg_ltx_flip_en_ch4       :  1,    //      4
    reg_ltx_flip_en_ch5       :  1,    //      5
    reg_ltx_flip_en_ch6       :  1,    //      6
    reg_ltx_flip_en_ch7       :  1,    //      7
    reg_ltx_flip_en_ch8       :  1,    //      8
    reg_ltx_flip_en_ch9       :  1,    //      9
    reg_ltx_flip_en_ch10      :  1,    //     10
    reg_ltx_flip_en_ch11      :  1,    //     11
                              : 20;    //  31:12 reserved
}VDEC_SYN_SYN_VDEC25_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0428    syn_vdec26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ltx_pdb_ch0           :  1,    //      0
    reg_ltx_pdb_ch1           :  1,    //      1
    reg_ltx_pdb_ch2           :  1,    //      2
    reg_ltx_pdb_ch3           :  1,    //      3
    reg_ltx_pdb_ch4           :  1,    //      4
    reg_ltx_pdb_ch5           :  1,    //      5
    reg_ltx_pdb_ch6           :  1,    //      6
    reg_ltx_pdb_ch7           :  1,    //      7
    reg_ltx_pdb_ch8           :  1,    //      8
    reg_ltx_pdb_ch9           :  1,    //      9
    reg_ltx_pdb_ch10          :  1,    //     10
    reg_ltx_pdb_ch11          :  1,    //     11
                              : 20;    //  31:12 reserved
}VDEC_SYN_SYN_VDEC26_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_042C    syn_vdec27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 12,    //  11: 0 reserved
    ltx_rst_g                 :  1,    //     12
                              : 19;    //  31:13 reserved
}VDEC_SYN_SYN_VDEC27_L18F_A0;

/*-----------------------------------------------------------------------------------------
    vdec_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
VDEC_SYN_SYN_VDEC00_L18F_A0                  syn_vdec00               ;         // 0xC9C7_0400
VDEC_SYN_SYN_VDEC01_L18F_A0                  syn_vdec01               ;         // 0xC9C7_0404
VDEC_SYN_SYN_VDEC02_L18F_A0                  syn_vdec02               ;         // 0xC9C7_0408
VDEC_SYN_SYN_VDEC03_L18F_A0                  syn_vdec03               ;         // 0xC9C7_040C
VDEC_SYN_SYN_VDEC04_L18F_A0                  syn_vdec04               ;         // 0xC9C7_0410
VDEC_SYN_SYN_VDEC05_L18F_A0                  syn_vdec05               ;         // 0xC9C7_0414
VDEC_SYN_SYN_VDEC22_L18F_A0                  syn_vdec22               ;         // 0xC9C7_0418
VDEC_SYN_SYN_VDEC23_L18F_A0                  syn_vdec23               ;         // 0xC9C7_041C
VDEC_SYN_SYN_VDEC24_L18F_A0                  syn_vdec24               ;         // 0xC9C7_0420
VDEC_SYN_SYN_VDEC25_L18F_A0                  syn_vdec25               ;         // 0xC9C7_0424
VDEC_SYN_SYN_VDEC26_L18F_A0                  syn_vdec26               ;         // 0xC9C7_0428
VDEC_SYN_SYN_VDEC27_L18F_A0                  syn_vdec27               ;         // 0xC9C7_042C
} VDEC_SYN_REG_L18F_A0;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_VDEC_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

