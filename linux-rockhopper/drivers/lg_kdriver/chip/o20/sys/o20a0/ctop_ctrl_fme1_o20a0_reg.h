#ifndef _CTOP_CTRL_FME1_O20A0_REG_H_
#define _CTOP_CTRL_FME1_O20A0_REG_H_

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
    0xC930_B400    ctr00 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_B404    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch0__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_aec_lrch0__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_aec_lrch0__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_aec_lrch0__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_aec_lrch0__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_aec_lrch0__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_aec_lrch0__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B408    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch1__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_aec_lrch1__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_aec_lrch1__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_aec_lrch1__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_aec_lrch1__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_aec_lrch1__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_aec_lrch1__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B40C    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrck__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_aec_lrck__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_aec_lrck__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_aec_lrck__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_aec_lrck__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_aec_lrck__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_aec_lrck__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B410    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_sck__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_aec_sck__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_aec_sck__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_aec_sck__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_aec_sck__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_aec_sck__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_aec_sck__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B414    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_boot_mode__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_boot_mode__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_boot_mode__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_boot_mode__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_boot_mode__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_boot_mode__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_boot_mode__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B418    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacclfch__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dacclfch__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dacclfch__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dacclfch__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dacclfch__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dacclfch__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dacclfch__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B41C    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacslrch__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dacslrch__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dacslrch__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dacslrch__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dacslrch__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dacslrch__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dacslrch__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B420    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_mosi__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dim0_mosi__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dim0_mosi__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dim0_mosi__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dim0_mosi__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dim0_mosi__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dim0_mosi__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B424    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_sclk__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dim0_sclk__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dim0_sclk__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dim0_sclk__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dim0_sclk__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dim0_sclk__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dim0_sclk__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B428    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim1_mosi__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dim1_mosi__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dim1_mosi__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dim1_mosi__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dim1_mosi__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dim1_mosi__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dim1_mosi__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B42C    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim1_sclk__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_dim1_sclk__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_dim1_sclk__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_dim1_sclk__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_dim1_sclk__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_dim1_sclk__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_dim1_sclk__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B430    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_eo__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_epi_eo__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_epi_eo__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_epi_eo__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_epi_eo__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_epi_eo__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_epi_eo__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B434    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_gclk__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_epi_gclk__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_epi_gclk__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_epi_gclk__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_epi_gclk__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_epi_gclk__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_epi_gclk__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B438    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_mclk__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_epi_mclk__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_epi_mclk__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_epi_mclk__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_epi_mclk__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_epi_mclk__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_epi_mclk__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B43C    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_vst__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_epi_vst__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_epi_vst__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_epi_vst__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_epi_vst__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_epi_vst__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_epi_vst__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B440    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_l_vsout_ld__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_l_vsout_ld__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_l_vsout_ld__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_l_vsout_ld__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_l_vsout_ld__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_l_vsout_ld__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_l_vsout_ld__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B444    ioctrl_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrch__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pcmi3lrch__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pcmi3lrch__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pcmi3lrch__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pcmi3lrch__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pcmi3lrch__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pcmi3lrch__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B448    ioctrl_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrck__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pcmi3lrck__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pcmi3lrck__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pcmi3lrck__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pcmi3lrck__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pcmi3lrck__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pcmi3lrck__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B44C    ioctrl_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3sck__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pcmi3sck__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pcmi3sck__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pcmi3sck__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pcmi3sck__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pcmi3sck__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pcmi3sck__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B450    ioctrl_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm_in__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pwm_in__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pwm_in__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pwm_in__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pwm_in__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pwm_in__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pwm_in__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B454    ioctrl_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm0__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pwm0__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pwm0__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pwm0__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pwm0__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pwm0__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pwm0__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B458    ioctrl_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm1__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pwm1__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pwm1__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pwm1__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pwm1__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pwm1__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pwm1__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B45C    ioctrl_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm2__st          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_pwm2__pu          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pwm2__pd          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_pwm2__ds3         :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_pwm2__ds2         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_pwm2__ds1         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_pwm2__ds0         :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_FME1_IOCTRL_22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B460    ioctrl_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_10_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_10_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_10_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_10_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_10_3     :  1,    //     16
                              : 15;    //  31:17 reserved
}CTOP_CTRL_FME1_IOCTRL_23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B464    ioctrl_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_5_3      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_5_1      :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_FME1_IOCTRL_24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B468    ioctrl_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_7_7      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_7_6      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_7_5      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_7_4      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_7_3      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_7_2      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_7_1      :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_7_0      :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_FME1_IOCTRL_25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_B46C    iomux_disable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag2_disable         :  1,    //      0
    reg_boot_mode_disable     :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_FME1_IOMUX_DISABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_fme1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                                   ctr00                    ;         // 0xC930_B400
CTOP_CTRL_FME1_IOCTRL_0_O20A0_T              ioctrl_0                 ;         // 0xC930_B404
CTOP_CTRL_FME1_IOCTRL_1_O20A0_T              ioctrl_1                 ;         // 0xC930_B408
CTOP_CTRL_FME1_IOCTRL_2_O20A0_T              ioctrl_2                 ;         // 0xC930_B40C
CTOP_CTRL_FME1_IOCTRL_3_O20A0_T              ioctrl_3                 ;         // 0xC930_B410
CTOP_CTRL_FME1_IOCTRL_4_O20A0_T              ioctrl_4                 ;         // 0xC930_B414
CTOP_CTRL_FME1_IOCTRL_5_O20A0_T              ioctrl_5                 ;         // 0xC930_B418
CTOP_CTRL_FME1_IOCTRL_6_O20A0_T              ioctrl_6                 ;         // 0xC930_B41C
CTOP_CTRL_FME1_IOCTRL_7_O20A0_T              ioctrl_7                 ;         // 0xC930_B420
CTOP_CTRL_FME1_IOCTRL_8_O20A0_T              ioctrl_8                 ;         // 0xC930_B424
CTOP_CTRL_FME1_IOCTRL_9_O20A0_T              ioctrl_9                 ;         // 0xC930_B428
CTOP_CTRL_FME1_IOCTRL_10_O20A0_T             ioctrl_10                ;         // 0xC930_B42C
CTOP_CTRL_FME1_IOCTRL_11_O20A0_T             ioctrl_11                ;         // 0xC930_B430
CTOP_CTRL_FME1_IOCTRL_12_O20A0_T             ioctrl_12                ;         // 0xC930_B434
CTOP_CTRL_FME1_IOCTRL_13_O20A0_T             ioctrl_13                ;         // 0xC930_B438
CTOP_CTRL_FME1_IOCTRL_14_O20A0_T             ioctrl_14                ;         // 0xC930_B43C
CTOP_CTRL_FME1_IOCTRL_15_O20A0_T             ioctrl_15                ;         // 0xC930_B440
CTOP_CTRL_FME1_IOCTRL_16_O20A0_T             ioctrl_16                ;         // 0xC930_B444
CTOP_CTRL_FME1_IOCTRL_17_O20A0_T             ioctrl_17                ;         // 0xC930_B448
CTOP_CTRL_FME1_IOCTRL_18_O20A0_T             ioctrl_18                ;         // 0xC930_B44C
CTOP_CTRL_FME1_IOCTRL_19_O20A0_T             ioctrl_19                ;         // 0xC930_B450
CTOP_CTRL_FME1_IOCTRL_20_O20A0_T             ioctrl_20                ;         // 0xC930_B454
CTOP_CTRL_FME1_IOCTRL_21_O20A0_T             ioctrl_21                ;         // 0xC930_B458
CTOP_CTRL_FME1_IOCTRL_22_O20A0_T             ioctrl_22                ;         // 0xC930_B45C
CTOP_CTRL_FME1_IOCTRL_23_O20A0_T             ioctrl_23                ;         // 0xC930_B460
CTOP_CTRL_FME1_IOCTRL_24_O20A0_T             ioctrl_24                ;         // 0xC930_B464
CTOP_CTRL_FME1_IOCTRL_25_O20A0_T             ioctrl_25                ;         // 0xC930_B468
CTOP_CTRL_FME1_IOMUX_DISABLE01_O20A0_T       iomux_disable01          ;         // 0xC930_B46C
} CTOP_CTRL_FME1_REG_O20A0_T;
/* 28 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_FME1_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

