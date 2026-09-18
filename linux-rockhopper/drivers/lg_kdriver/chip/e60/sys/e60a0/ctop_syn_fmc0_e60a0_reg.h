#ifndef _CTOP_SYN_FMC0_E60A0_REG_H_
#define _CTOP_SYN_FMC0_E60A0_REG_H_

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
    0xC932_2400    syn_fmc0_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_fmc0_ctrl         : 32;    //  31: 0
}CTOP_FMC0_SYN_FMC0_00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2404    syn_fmc0_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_fmc0_ctrl1        : 32;    //  31: 0
}CTOP_FMC0_SYN_FMC0_01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2408    syn_fmc0_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_fmc0       :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FMC0_SYN_FMC0_02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_240C    syn_fmc0_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_cc_fmc_cur_l3   :  1,    //      0
    reg_swrst_yy_fmc_cur_l3   :  1,    //      1
    reg_swrst_cc_fmc_cur_l2   :  1,    //      2
    reg_swrst_yy_fmc_cur_l2   :  1,    //      3
    reg_swrst_cc_fmc_cur_l1   :  1,    //      4
    reg_swrst_yy_fmc_cur_l1   :  1,    //      5
    reg_swrst_cc_fmc_cur_l0   :  1,    //      6
    reg_swrst_yy_fmc_cur_l0   :  1,    //      7
    reg_swrst_cc_fmc_prv_l3   :  1,    //      8
    reg_swrst_yy_fmc_prv_l3   :  1,    //      9
    reg_swrst_cc_fmc_prv_l2   :  1,    //     10
    reg_swrst_yy_fmc_prv_l2   :  1,    //     11
    reg_swrst_cc_fmc_prv_l1   :  1,    //     12
    reg_swrst_yy_fmc_prv_l1   :  1,    //     13
    reg_swrst_cc_fmc_prv_l0_rd:  1,    //     14
    reg_swrst_yy_fmc_prv_l0_rd:  1,    //     15
    reg_swrst_yy_fmc_mc       :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_FMC0_SYN_FMC0_03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2430    saradc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_pdb              :  1,    //      0
                              : 11,    //  11: 1 reserved
    reg_sadc_pc               :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_cc               :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_isel             :  3,    //  22:20
                              :  9;    //  31:23 reserved
}CTOP_FMC0_SARADC00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2434    saradc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_soc          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_lpf_chsel        :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sadc_lpf_start        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dsel                  :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_lpf_mode         :  3,    //  18:16
                              :  5,    //  23:19 reserved
    reg_sadc_lpf_eoc_inv      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_sadc_lpf_manual       :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_FMC0_SARADC01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2438    saradc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_data_clear   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FMC0_SARADC02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_243C    saradc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data012          : 32;    //  31: 0
}CTOP_FMC0_SARADC04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2440    saradc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_data345          : 32;    //  31: 0
}CTOP_FMC0_SARADC05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2444    saradc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_lpf_debug_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FMC0_SARADC06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2448    saradc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_lpf_debug_data       :  8,    //   7: 0
                              : 20,    //  27: 8 reserved
    sadc_lpf_adc_done         :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_FMC0_SARADC07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_244C    pad_reg01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim2_sclk__st     :  1,    //      0
    reg_pad_dim2_sclk__pu     :  1,    //      1
    reg_pad_dim2_sclk__pd     :  1,    //      2
    reg_pad_dim2_sclk__ds3    :  1,    //      3
    reg_pad_dim2_sclk__ds2    :  1,    //      4
    reg_pad_dim2_sclk__ds1    :  1,    //      5
    reg_pad_dim2_sclk__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim2_mosi__st     :  1,    //      8
    reg_pad_dim2_mosi__pu     :  1,    //      9
    reg_pad_dim2_mosi__pd     :  1,    //     10
    reg_pad_dim2_mosi__ds3    :  1,    //     11
    reg_pad_dim2_mosi__ds2    :  1,    //     12
    reg_pad_dim2_mosi__ds1    :  1,    //     13
    reg_pad_dim2_mosi__ds0    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim1_sclk__st     :  1,    //     16
    reg_pad_dim1_sclk__pu     :  1,    //     17
    reg_pad_dim1_sclk__pd     :  1,    //     18
    reg_pad_dim1_sclk__ds3    :  1,    //     19
    reg_pad_dim1_sclk__ds2    :  1,    //     20
    reg_pad_dim1_sclk__ds1    :  1,    //     21
    reg_pad_dim1_sclk__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim1_mosi__st     :  1,    //     24
    reg_pad_dim1_mosi__pu     :  1,    //     25
    reg_pad_dim1_mosi__pd     :  1,    //     26
    reg_pad_dim1_mosi__ds3    :  1,    //     27
    reg_pad_dim1_mosi__ds2    :  1,    //     28
    reg_pad_dim1_mosi__ds1    :  1,    //     29
    reg_pad_dim1_mosi__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2450    pad_reg02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio1__st         :  1,    //      0
    reg_pad_gpio1__pu         :  1,    //      1
    reg_pad_gpio1__pd         :  1,    //      2
    reg_pad_gpio1__ds3        :  1,    //      3
    reg_pad_gpio1__ds2        :  1,    //      4
    reg_pad_gpio1__ds1        :  1,    //      5
    reg_pad_gpio1__ds0        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio0__st         :  1,    //      8
    reg_pad_gpio0__pu         :  1,    //      9
    reg_pad_gpio0__pd         :  1,    //     10
    reg_pad_gpio0__ds3        :  1,    //     11
    reg_pad_gpio0__ds2        :  1,    //     12
    reg_pad_gpio0__ds1        :  1,    //     13
    reg_pad_gpio0__ds0        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim3_sclk__st     :  1,    //     16
    reg_pad_dim3_sclk__pu     :  1,    //     17
    reg_pad_dim3_sclk__pd     :  1,    //     18
    reg_pad_dim3_sclk__ds3    :  1,    //     19
    reg_pad_dim3_sclk__ds2    :  1,    //     20
    reg_pad_dim3_sclk__ds1    :  1,    //     21
    reg_pad_dim3_sclk__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim3_mosi__st     :  1,    //     24
    reg_pad_dim3_mosi__pu     :  1,    //     25
    reg_pad_dim3_mosi__pd     :  1,    //     26
    reg_pad_dim3_mosi__ds3    :  1,    //     27
    reg_pad_dim3_mosi__ds2    :  1,    //     28
    reg_pad_dim3_mosi__ds1    :  1,    //     29
    reg_pad_dim3_mosi__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2454    pad_reg03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio13__st        :  1,    //      0
    reg_pad_gpio13__pu        :  1,    //      1
    reg_pad_gpio13__pd        :  1,    //      2
    reg_pad_gpio13__ds3       :  1,    //      3
    reg_pad_gpio13__ds2       :  1,    //      4
    reg_pad_gpio13__ds1       :  1,    //      5
    reg_pad_gpio13__ds0       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio12__st        :  1,    //      8
    reg_pad_gpio12__pu        :  1,    //      9
    reg_pad_gpio12__pd        :  1,    //     10
    reg_pad_gpio12__ds3       :  1,    //     11
    reg_pad_gpio12__ds2       :  1,    //     12
    reg_pad_gpio12__ds1       :  1,    //     13
    reg_pad_gpio12__ds0       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio11__st        :  1,    //     16
    reg_pad_gpio11__pu        :  1,    //     17
    reg_pad_gpio11__pd        :  1,    //     18
    reg_pad_gpio11__ds3       :  1,    //     19
    reg_pad_gpio11__ds2       :  1,    //     20
    reg_pad_gpio11__ds1       :  1,    //     21
    reg_pad_gpio11__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio10__st        :  1,    //     24
    reg_pad_gpio10__pu        :  1,    //     25
    reg_pad_gpio10__pd        :  1,    //     26
    reg_pad_gpio10__ds3       :  1,    //     27
    reg_pad_gpio10__ds2       :  1,    //     28
    reg_pad_gpio10__ds1       :  1,    //     29
    reg_pad_gpio10__ds0       :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2458    pad_reg04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio5__st         :  1,    //      0
    reg_pad_gpio5__pu         :  1,    //      1
    reg_pad_gpio5__pd         :  1,    //      2
    reg_pad_gpio5__ds3        :  1,    //      3
    reg_pad_gpio5__ds2        :  1,    //      4
    reg_pad_gpio5__ds1        :  1,    //      5
    reg_pad_gpio5__ds0        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio4__st         :  1,    //      8
    reg_pad_gpio4__pu         :  1,    //      9
    reg_pad_gpio4__pd         :  1,    //     10
    reg_pad_gpio4__ds3        :  1,    //     11
    reg_pad_gpio4__ds2        :  1,    //     12
    reg_pad_gpio4__ds1        :  1,    //     13
    reg_pad_gpio4__ds0        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio3__st         :  1,    //     16
    reg_pad_gpio3__pu         :  1,    //     17
    reg_pad_gpio3__pd         :  1,    //     18
    reg_pad_gpio3__ds3        :  1,    //     19
    reg_pad_gpio3__ds2        :  1,    //     20
    reg_pad_gpio3__ds1        :  1,    //     21
    reg_pad_gpio3__ds0        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio2__st         :  1,    //     24
    reg_pad_gpio2__pu         :  1,    //     25
    reg_pad_gpio2__pd         :  1,    //     26
    reg_pad_gpio2__ds3        :  1,    //     27
    reg_pad_gpio2__ds2        :  1,    //     28
    reg_pad_gpio2__ds1        :  1,    //     29
    reg_pad_gpio2__ds0        :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_245C    pad_reg05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio9__st         :  1,    //      0
    reg_pad_gpio9__pu         :  1,    //      1
    reg_pad_gpio9__pd         :  1,    //      2
    reg_pad_gpio9__ds3        :  1,    //      3
    reg_pad_gpio9__ds2        :  1,    //      4
    reg_pad_gpio9__ds1        :  1,    //      5
    reg_pad_gpio9__ds0        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio8__st         :  1,    //      8
    reg_pad_gpio8__pu         :  1,    //      9
    reg_pad_gpio8__pd         :  1,    //     10
    reg_pad_gpio8__ds3        :  1,    //     11
    reg_pad_gpio8__ds2        :  1,    //     12
    reg_pad_gpio8__ds1        :  1,    //     13
    reg_pad_gpio8__ds0        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio7__st         :  1,    //     16
    reg_pad_gpio7__pu         :  1,    //     17
    reg_pad_gpio7__pd         :  1,    //     18
    reg_pad_gpio7__ds3        :  1,    //     19
    reg_pad_gpio7__ds2        :  1,    //     20
    reg_pad_gpio7__ds1        :  1,    //     21
    reg_pad_gpio7__ds0        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio6__st         :  1,    //     24
    reg_pad_gpio6__pu         :  1,    //     25
    reg_pad_gpio6__pd         :  1,    //     26
    reg_pad_gpio6__ds3        :  1,    //     27
    reg_pad_gpio6__ds2        :  1,    //     28
    reg_pad_gpio6__ds1        :  1,    //     29
    reg_pad_gpio6__ds0        :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2460    pad_reg06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ld_vs_out1__st    :  1,    //      0
    reg_pad_ld_vs_out1__pu    :  1,    //      1
    reg_pad_ld_vs_out1__pd    :  1,    //      2
    reg_pad_ld_vs_out1__ds3   :  1,    //      3
    reg_pad_ld_vs_out1__ds2   :  1,    //      4
    reg_pad_ld_vs_out1__ds1   :  1,    //      5
    reg_pad_ld_vs_out1__ds0   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ld_vs_out0__st    :  1,    //      8
    reg_pad_ld_vs_out0__pu    :  1,    //      9
    reg_pad_ld_vs_out0__pd    :  1,    //     10
    reg_pad_ld_vs_out0__ds3   :  1,    //     11
    reg_pad_ld_vs_out0__ds2   :  1,    //     12
    reg_pad_ld_vs_out0__ds1   :  1,    //     13
    reg_pad_ld_vs_out0__ds0   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ld_vs_in__st      :  1,    //     16
    reg_pad_ld_vs_in__pu      :  1,    //     17
    reg_pad_ld_vs_in__pd      :  1,    //     18
    reg_pad_ld_vs_in__ds3     :  1,    //     19
    reg_pad_ld_vs_in__ds2     :  1,    //     20
    reg_pad_ld_vs_in__ds1     :  1,    //     21
    reg_pad_ld_vs_in__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_iec958out__st     :  1,    //     24
    reg_pad_iec958out__pu     :  1,    //     25
    reg_pad_iec958out__pd     :  1,    //     26
    reg_pad_iec958out__ds3    :  1,    //     27
    reg_pad_iec958out__ds2    :  1,    //     28
    reg_pad_iec958out__ds1    :  1,    //     29
    reg_pad_iec958out__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2464    pad_reg07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm0__st          :  1,    //      0
    reg_pad_pwm0__pu          :  1,    //      1
    reg_pad_pwm0__pd          :  1,    //      2
    reg_pad_pwm0__ds3         :  1,    //      3
    reg_pad_pwm0__ds2         :  1,    //      4
    reg_pad_pwm0__ds1         :  1,    //      5
    reg_pad_pwm0__ds0         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pwm_in__st        :  1,    //      8
    reg_pad_pwm_in__pu        :  1,    //      9
    reg_pad_pwm_in__pd        :  1,    //     10
    reg_pad_pwm_in__ds3       :  1,    //     11
    reg_pad_pwm_in__ds2       :  1,    //     12
    reg_pad_pwm_in__ds1       :  1,    //     13
    reg_pad_pwm_in__ds0       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ld_vs_out3__st    :  1,    //     16
    reg_pad_ld_vs_out3__pu    :  1,    //     17
    reg_pad_ld_vs_out3__pd    :  1,    //     18
    reg_pad_ld_vs_out3__ds3   :  1,    //     19
    reg_pad_ld_vs_out3__ds2   :  1,    //     20
    reg_pad_ld_vs_out3__ds1   :  1,    //     21
    reg_pad_ld_vs_out3__ds0   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ld_vs_out2__st    :  1,    //     24
    reg_pad_ld_vs_out2__pu    :  1,    //     25
    reg_pad_ld_vs_out2__pd    :  1,    //     26
    reg_pad_ld_vs_out2__ds3   :  1,    //     27
    reg_pad_ld_vs_out2__ds2   :  1,    //     28
    reg_pad_ld_vs_out2__ds1   :  1,    //     29
    reg_pad_ld_vs_out2__ds0   :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2468    pad_reg08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda0__st          :  1,    //      0
    reg_pad_sda0__pu          :  1,    //      1
    reg_pad_sda0__pd          :  1,    //      2
    reg_pad_sda0__ds3         :  1,    //      3
    reg_pad_sda0__ds2         :  1,    //      4
    reg_pad_sda0__ds1         :  1,    //      5
    reg_pad_sda0__ds0         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_scl0__st          :  1,    //      8
    reg_pad_scl0__pu          :  1,    //      9
    reg_pad_scl0__pd          :  1,    //     10
    reg_pad_scl0__ds3         :  1,    //     11
    reg_pad_scl0__ds2         :  1,    //     12
    reg_pad_scl0__ds1         :  1,    //     13
    reg_pad_scl0__ds0         :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_pwm2__st          :  1,    //     16
    reg_pad_pwm2__pu          :  1,    //     17
    reg_pad_pwm2__pd          :  1,    //     18
    reg_pad_pwm2__ds3         :  1,    //     19
    reg_pad_pwm2__ds2         :  1,    //     20
    reg_pad_pwm2__ds1         :  1,    //     21
    reg_pad_pwm2__ds0         :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pwm1__st          :  1,    //     24
    reg_pad_pwm1__pu          :  1,    //     25
    reg_pad_pwm1__pd          :  1,    //     26
    reg_pad_pwm1__ds3         :  1,    //     27
    reg_pad_pwm1__ds2         :  1,    //     28
    reg_pad_pwm1__ds1         :  1,    //     29
    reg_pad_pwm1__ds0         :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_246C    pad_reg09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk0__st     :  1,    //      0
    reg_pad_spi_sclk0__pu     :  1,    //      1
    reg_pad_spi_sclk0__pd     :  1,    //      2
    reg_pad_spi_sclk0__ds3    :  1,    //      3
    reg_pad_spi_sclk0__ds2    :  1,    //      4
    reg_pad_spi_sclk0__ds1    :  1,    //      5
    reg_pad_spi_sclk0__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_do0__st       :  1,    //      8
    reg_pad_spi_do0__pu       :  1,    //      9
    reg_pad_spi_do0__pd       :  1,    //     10
    reg_pad_spi_do0__ds3      :  1,    //     11
    reg_pad_spi_do0__ds2      :  1,    //     12
    reg_pad_spi_do0__ds1      :  1,    //     13
    reg_pad_spi_do0__ds0      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_di0__st       :  1,    //     16
    reg_pad_spi_di0__pu       :  1,    //     17
    reg_pad_spi_di0__pd       :  1,    //     18
    reg_pad_spi_di0__ds3      :  1,    //     19
    reg_pad_spi_di0__ds2      :  1,    //     20
    reg_pad_spi_di0__ds1      :  1,    //     21
    reg_pad_spi_di0__ds0      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_cs0__st       :  1,    //     24
    reg_pad_spi_cs0__pu       :  1,    //     25
    reg_pad_spi_cs0__pd       :  1,    //     26
    reg_pad_spi_cs0__ds3      :  1,    //     27
    reg_pad_spi_cs0__ds2      :  1,    //     28
    reg_pad_spi_cs0__ds1      :  1,    //     29
    reg_pad_spi_cs0__ds0      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC0_PAD_REG09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2470    pad_reg10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_sclk__st     :  1,    //      0
    reg_pad_dim0_sclk__pu     :  1,    //      1
    reg_pad_dim0_sclk__pd     :  1,    //      2
    reg_pad_dim0_sclk__ds3    :  1,    //      3
    reg_pad_dim0_sclk__ds2    :  1,    //      4
    reg_pad_dim0_sclk__ds1    :  1,    //      5
    reg_pad_dim0_sclk__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim0_mosi__st     :  1,    //      8
    reg_pad_dim0_mosi__pu     :  1,    //      9
    reg_pad_dim0_mosi__pd     :  1,    //     10
    reg_pad_dim0_mosi__ds3    :  1,    //     11
    reg_pad_dim0_mosi__ds2    :  1,    //     12
    reg_pad_dim0_mosi__ds1    :  1,    //     13
    reg_pad_dim0_mosi__ds0    :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_FMC0_PAD_REG10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2474    pad_reg11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim3_sclk_mux_sel :  4,    //   3: 0
    reg_pad_dim3_mosi_mux_sel :  4,    //   7: 4
    reg_pad_dim2_sclk_mux_sel :  4,    //  11: 8
    reg_pad_dim2_mosi_mux_sel :  4,    //  15:12
    reg_pad_dim1_sclk_mux_sel :  4,    //  19:16
    reg_pad_dim1_mosi_mux_sel :  4,    //  23:20
    reg_pad_dim0_sclk_mux_sel :  4,    //  27:24
    reg_pad_dim0_mosi_mux_sel :  4;    //  31:28
}CTOP_FMC0_PAD_REG11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2478    pad_reg12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio3_mux_sel     :  4,    //   3: 0
    reg_pad_gpio2_mux_sel     :  4,    //   7: 4
    reg_pad_gpio13_mux_sel    :  4,    //  11: 8
    reg_pad_gpio12_mux_sel    :  4,    //  15:12
    reg_pad_gpio11_mux_sel    :  4,    //  19:16
    reg_pad_gpio10_mux_sel    :  4,    //  23:20
    reg_pad_gpio1_mux_sel     :  4,    //  27:24
    reg_pad_gpio0_mux_sel     :  4;    //  31:28
}CTOP_FMC0_PAD_REG12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_247C    pad_reg13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ld_vs_out0_mux_sel:  4,    //   3: 0
    reg_pad_ld_vs_in_mux_sel  :  4,    //   7: 4
    reg_pad_gpio9_mux_sel     :  4,    //  11: 8
    reg_pad_gpio8_mux_sel     :  4,    //  15:12
    reg_pad_gpio7_mux_sel     :  4,    //  19:16
    reg_pad_gpio6_mux_sel     :  4,    //  23:20
    reg_pad_gpio5_mux_sel     :  4,    //  27:24
    reg_pad_gpio4_mux_sel     :  4;    //  31:28
}CTOP_FMC0_PAD_REG13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2480    pad_reg14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl0_mux_sel      :  4,    //   3: 0
    reg_pad_pwm2_mux_sel      :  4,    //   7: 4
    reg_pad_pwm1_mux_sel      :  4,    //  11: 8
    reg_pad_pwm0_mux_sel      :  4,    //  15:12
    reg_pad_pwm_in_mux_sel    :  4,    //  19:16
    reg_pad_ld_vs_out3_mux_sel:  4,    //  23:20
    reg_pad_ld_vs_out2_mux_sel:  4,    //  27:24
    reg_pad_ld_vs_out1_mux_sel:  4;    //  31:28
}CTOP_FMC0_PAD_REG14_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_2484    pad_reg15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_iec958out_mux_sel :  4,    //   3: 0
    reg_pad_spi_sclk0_mux_sel :  4,    //   7: 4
    reg_pad_spi_do0_mux_sel   :  4,    //  11: 8
    reg_pad_spi_di0_mux_sel   :  4,    //  15:12
    reg_pad_spi_cs0_mux_sel   :  4,    //  19:16
    reg_pad_sda0_mux_sel      :  4,    //  23:20
    reg_pad_pqe_ip_enb_mux_sel:  4,    //  27:24
                              :  4;    //  31:28 reserved
}CTOP_FMC0_PAD_REG15_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    fmc0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_FMC0_SYN_FMC0_00_E60_A0_T           syn_fmc0_00              ;         // 0xC932_2400
    CTOP_FMC0_SYN_FMC0_01_E60_A0_T           syn_fmc0_01              ;         // 0xC932_2404
    CTOP_FMC0_SYN_FMC0_02_E60_A0_T           syn_fmc0_02              ;         // 0xC932_2408
    CTOP_FMC0_SYN_FMC0_03_E60_A0_T           syn_fmc0_03              ;         // 0xC932_240C
UINT32                                                 _rsvd_00[   8] ;         // 0xC932_2410 ~ 0xC932_242C
    CTOP_FMC0_SARADC00_E60_A0_T              saradc00                 ;         // 0xC932_2430
    CTOP_FMC0_SARADC01_E60_A0_T              saradc01                 ;         // 0xC932_2434
    CTOP_FMC0_SARADC02_E60_A0_T              saradc02                 ;         // 0xC932_2438
    CTOP_FMC0_SARADC04_E60_A0_T              saradc04                 ;         // 0xC932_243C
    CTOP_FMC0_SARADC05_E60_A0_T              saradc05                 ;         // 0xC932_2440
    CTOP_FMC0_SARADC06_E60_A0_T              saradc06                 ;         // 0xC932_2444
    CTOP_FMC0_SARADC07_E60_A0_T              saradc07                 ;         // 0xC932_2448
    CTOP_FMC0_PAD_REG01_E60_A0_T             pad_reg01                ;         // 0xC932_244C
    CTOP_FMC0_PAD_REG02_E60_A0_T             pad_reg02                ;         // 0xC932_2450
    CTOP_FMC0_PAD_REG03_E60_A0_T             pad_reg03                ;         // 0xC932_2454
    CTOP_FMC0_PAD_REG04_E60_A0_T             pad_reg04                ;         // 0xC932_2458
    CTOP_FMC0_PAD_REG05_E60_A0_T             pad_reg05                ;         // 0xC932_245C
    CTOP_FMC0_PAD_REG06_E60_A0_T             pad_reg06                ;         // 0xC932_2460
    CTOP_FMC0_PAD_REG07_E60_A0_T             pad_reg07                ;         // 0xC932_2464
    CTOP_FMC0_PAD_REG08_E60_A0_T             pad_reg08                ;         // 0xC932_2468
    CTOP_FMC0_PAD_REG09_E60_A0_T             pad_reg09                ;         // 0xC932_246C
    CTOP_FMC0_PAD_REG10_E60_A0_T             pad_reg10                ;         // 0xC932_2470
    CTOP_FMC0_PAD_REG11_E60_A0_T             pad_reg11                ;         // 0xC932_2474
    CTOP_FMC0_PAD_REG12_E60_A0_T             pad_reg12                ;         // 0xC932_2478
    CTOP_FMC0_PAD_REG13_E60_A0_T             pad_reg13                ;         // 0xC932_247C
    CTOP_FMC0_PAD_REG14_E60_A0_T             pad_reg14                ;         // 0xC932_2480
    CTOP_FMC0_PAD_REG15_E60_A0_T             pad_reg15                ;         // 0xC932_2484
} CTOP_SYN_FMC0_REG_E60_A0_T;
/* 26 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_FMC0_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

