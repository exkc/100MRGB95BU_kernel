#ifndef _CTOP_MICOM_SYN_A0_REG_H_
#define _CTOP_MICOM_SYN_A0_REG_H_

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
    0xC930_C400    syn_micom00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_smv          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_rxclkdrv_outsel       :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}MICOM_SYN_SYN_MICOM00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C404    syn_micom01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_force_jtag1_control_disable: 1,    //  0
    reg_force_debug_control_disable: 1,    //  1
    reg_boot_mode_control_disable: 1,    //    2
    reg_cpu_spi_enable        :  1,    //      3
    reg_micom_spi_enable      :  1,    //      4
    reg_hdmi2_ddc_disable     :  1,    //      5
                              : 26;    //   31:6 reserved
}MICOM_SYN_SYN_MICOM01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C408    syn_micom02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_chsel            :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_sadc_test             :  4,    //   7: 4
    reg_sadc_isel             :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_sadc_cc               :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_pc               :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_soc              :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_sadc_pdb              :  1,    //     24
                              :  7;    //  31:25 reserved
}MICOM_SYN_SYN_MICOM02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C40C    syn_micom03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_uart1_sel             :  4,    //   3: 0
    reg_uart1_disable         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_i2c_sel               :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_jtag1_sel             :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_jtag1_enable          :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_hpd_out_sel           :  2,    //  21:20
                              :  2,    //  23:22 reserved
    reg_xtal_clk_gate_en      :  1,    //     24
                              :  7;    //  31:25 reserved
}MICOM_SYN_SYN_MICOM03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C410    syn_micom04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_micom_gpio_0_0    :  1,    //      0
    reg_use_micom_gpio_0_1    :  1,    //      1
                              :  8,    //   9: 2 reserved
    reg_use_micom_gpio_1_2    :  1,    //     10
    reg_use_micom_gpio_1_3    :  1,    //     11
    reg_use_micom_gpio_1_4    :  1,    //     12
    reg_use_micom_gpio_1_5    :  1,    //     13
    reg_use_micom_gpio_1_6    :  1,    //     14
    reg_use_micom_gpio_1_7    :  1,    //     15
    reg_use_micom_gpio_2_0    :  1,    //     16
    reg_use_micom_gpio_2_1    :  1,    //     17
    reg_use_micom_gpio_2_2    :  1,    //     18
    reg_use_micom_gpio_2_3    :  1,    //     19
    reg_use_micom_gpio_2_4    :  1,    //     20
    reg_use_micom_gpio_2_5    :  1,    //     21
    reg_use_micom_gpio_2_6    :  1,    //     22
                              :  9;    //  31:23 reserved
}MICOM_SYN_SYN_MICOM04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C414    syn_micom05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_0_0      :  1,    //      0
    reg_use_cpu_gpio_0_1      :  1,    //      1
    reg_use_cpu_gpio_0_2      :  1,    //      2
    reg_use_cpu_gpio_0_3      :  1,    //      3
    reg_use_cpu_gpio_0_4      :  1,    //      4
    reg_use_cpu_gpio_0_5      :  1,    //      5
    reg_use_cpu_gpio_0_6      :  1,    //      6
    reg_use_cpu_gpio_0_7      :  1,    //      7
    reg_use_cpu_gpio_1_0      :  1,    //      8
    reg_use_cpu_gpio_1_1      :  1,    //      9
    reg_use_cpu_gpio_1_2      :  1,    //     10
    reg_use_cpu_gpio_1_3      :  1,    //     11
    reg_use_cpu_gpio_1_4      :  1,    //     12
    reg_use_cpu_gpio_1_5      :  1,    //     13
    reg_use_cpu_gpio_1_6      :  1,    //     14
    reg_use_cpu_gpio_1_7      :  1,    //     15
    reg_use_cpu_gpio_2_0      :  1,    //     16
    reg_use_cpu_gpio_2_1      :  1,    //     17
    reg_use_cpu_gpio_2_2      :  1,    //     18
    reg_use_cpu_gpio_2_3      :  1,    //     19
    reg_use_cpu_gpio_2_4      :  1,    //     20
    reg_use_cpu_gpio_2_5      :  1,    //     21
                              : 10;    //  31:22 reserved
}MICOM_SYN_SYN_MICOM05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C418    syn_micom06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio0__ren        :  1,    //      0
    reg_pad_gpio1__ren        :  1,    //      1
    reg_pad_gpio2__ren        :  1,    //      2
    reg_pad_gpio3__ren        :  1,    //      3
    reg_pad_gpio4__ren        :  1,    //      4
    reg_pad_gpio5__ren        :  1,    //      5
    reg_pad_gpio6__ren        :  1,    //      6
    reg_pad_gpio7__ren        :  1,    //      7
    reg_pad_gpio8__ren        :  1,    //      8
    reg_pad_gpio9__ren        :  1,    //      9
    reg_pad_daclrch__ren      :  1,    //     10
    reg_pad_daclrck__ren      :  1,    //     11
    reg_pad_dacsck__ren       :  1,    //     12
    reg_pad_spi_cs0__ren      :  1,    //     13
    reg_pad_spi_di0__ren      :  1,    //     14
    reg_pad_spi_do0__ren      :  1,    //     15
    reg_pad_spi_sclk0__ren    :  1,    //     16
    reg_pad_cec__ren          :  1,    //     17
    reg_pad_hdmi2_2_sda__pd   :  1,    //     18
    reg_pad_hdmi2_2_sda__pu   :  1,    //     19
    reg_pad_hdmi2_2_sda__ds   :  1,    //     20
    reg_pad_hdmi2_2_scl__pd   :  1,    //     21
    reg_pad_hdmi2_2_scl__pu   :  1,    //     22
    reg_pad_hdmi2_2_scl__ds   :  1,    //     23
    reg_pad_hdmi2_2_hpd__pd   :  1,    //     24
    reg_pad_hdmi2_2_hpd__pu   :  1,    //     25
    reg_pad_hdmi2_2_hpd__ds   :  1,    //     26
    reg_pad_hdmi2_2_5v_in__pd :  1,    //     27
    reg_pad_hdmi2_2_5v_in__pu :  1,    //     28
    reg_pad_hdmi2_2_5v_in__ds :  1,    //     29
    reg_pad_opm__ren          :  1,    //     30
    reg_pad_pllset__ren       :  1;    //     31
}MICOM_SYN_SYN_MICOM06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C41C    syn_micom07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_edid                :  1,    //      0
    swrst_edid_comm_apb       :  1,    //      1
    swrst_edid_apb            :  1,    //      2
                              : 13,    //  15: 3 reserved
    edid_clk_sel              :  2,    //  17:16
                              :  6,    //  23:18 reserved
    edid_apb_clk_gate_en      :  1,    //     24
                              :  7;    //  31:25 reserved
}MICOM_SYN_SYN_MICOM07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C420    syn_micom08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_micom_peri          :  1,    //      0
    swrst_micom_adc           :  1,    //      1
    swrst_micom_bus           :  1,    //      2
    swrst_micom_cm0p          :  1,    //      3
    swrst_micom_bnd           :  1,    //      4
                              :  3,    //   7: 5 reserved
    micom_peri_clk_gate_en    :  1,    //      8
    micom_adc_clk_gate_en     :  1,    //      9
    micom_clk_gate_en         :  1,    //     10
                              :  5,    //  15:11 reserved
    micom_clk_sel             :  2,    //  17:16
                              : 14;    //  31:18 reserved
}MICOM_SYN_SYN_MICOM08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C424    syn_micom09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    micom_nisol_ctrl          :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SYN_SYN_MICOM09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C428    syn_micom10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_r0                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}MICOM_SYN_SYN_MICOM10_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C42C    syn_micom11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wdt_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SYN_SYN_MICOM11_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C430    syn_micom12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ignore_micom_reset    :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SYN_SYN_MICOM12_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C434    syn_micom13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_xtal_sel          :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SYN_SYN_MICOM13_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C438    syn_micom14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sw_reset_mux_sel      :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SYN_SYN_MICOM14_L18F_A0;

/*-----------------------------------------------------------------------------------------
    micom_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
MICOM_SYN_SYN_MICOM00_L18F_A0                syn_micom00              ;         // 0xC930_C400
MICOM_SYN_SYN_MICOM01_L18F_A0                syn_micom01              ;         // 0xC930_C404
MICOM_SYN_SYN_MICOM02_L18F_A0                syn_micom02              ;         // 0xC930_C408
MICOM_SYN_SYN_MICOM03_L18F_A0                syn_micom03              ;         // 0xC930_C40C
MICOM_SYN_SYN_MICOM04_L18F_A0                syn_micom04              ;         // 0xC930_C410
MICOM_SYN_SYN_MICOM05_L18F_A0                syn_micom05              ;         // 0xC930_C414
MICOM_SYN_SYN_MICOM06_L18F_A0                syn_micom06              ;         // 0xC930_C418
MICOM_SYN_SYN_MICOM07_L18F_A0                syn_micom07              ;         // 0xC930_C41C
MICOM_SYN_SYN_MICOM08_L18F_A0                syn_micom08              ;         // 0xC930_C420
MICOM_SYN_SYN_MICOM09_L18F_A0                syn_micom09              ;         // 0xC930_C424
MICOM_SYN_SYN_MICOM10_L18F_A0                syn_micom10              ;         // 0xC930_C428
MICOM_SYN_SYN_MICOM11_L18F_A0                syn_micom11              ;         // 0xC930_C42C
MICOM_SYN_SYN_MICOM12_L18F_A0                syn_micom12              ;         // 0xC930_C430
MICOM_SYN_SYN_MICOM13_L18F_A0                syn_micom13              ;         // 0xC930_C434
MICOM_SYN_SYN_MICOM14_L18F_A0                syn_micom14              ;         // 0xC930_C438
} MICOM_SYN_REG_L18F_A0;
/* 15 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_MICOM_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

