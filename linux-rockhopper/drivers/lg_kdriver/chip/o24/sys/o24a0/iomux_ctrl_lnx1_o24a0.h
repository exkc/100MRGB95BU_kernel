#ifndef _IOMUX_CTRL_LNX1_REG_O24A0_H_
#define _IOMUX_CTRL_LNX1_REG_O24A0_H_

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
    0xCC97_2000    pad_lnx1_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch3__ds0    :  1,    //      0
    reg_pad_aec_lrch3__ds1    :  1,    //      1
    reg_pad_aec_lrch3__ds2    :  1,    //      2
    reg_pad_aec_lrch3__ds3    :  1,    //      3
    reg_pad_aec_lrch3__pd     :  1,    //      4
    reg_pad_aec_lrch3__pu     :  1,    //      5
    reg_pad_aec_lrch3__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_aec_lrch2__ds0    :  1,    //      8
    reg_pad_aec_lrch2__ds1    :  1,    //      9
    reg_pad_aec_lrch2__ds2    :  1,    //     10
    reg_pad_aec_lrch2__ds3    :  1,    //     11
    reg_pad_aec_lrch2__pd     :  1,    //     12
    reg_pad_aec_lrch2__pu     :  1,    //     13
    reg_pad_aec_lrch2__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_aec_lrch1__ds0    :  1,    //     16
    reg_pad_aec_lrch1__ds1    :  1,    //     17
    reg_pad_aec_lrch1__ds2    :  1,    //     18
    reg_pad_aec_lrch1__ds3    :  1,    //     19
    reg_pad_aec_lrch1__pd     :  1,    //     20
    reg_pad_aec_lrch1__pu     :  1,    //     21
    reg_pad_aec_lrch1__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_aec_lrch0__ds0    :  1,    //     24
    reg_pad_aec_lrch0__ds1    :  1,    //     25
    reg_pad_aec_lrch0__ds2    :  1,    //     26
    reg_pad_aec_lrch0__ds3    :  1,    //     27
    reg_pad_aec_lrch0__pd     :  1,    //     28
    reg_pad_aec_lrch0__pu     :  1,    //     29
    reg_pad_aec_lrch0__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2004    pad_lnx1_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_daclrck__ds0      :  1,    //      0
    reg_pad_daclrck__ds1      :  1,    //      1
    reg_pad_daclrck__ds2      :  1,    //      2
    reg_pad_daclrck__ds3      :  1,    //      3
    reg_pad_daclrck__pd       :  1,    //      4
    reg_pad_daclrck__pu       :  1,    //      5
    reg_pad_daclrck__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_daclrch__ds0      :  1,    //      8
    reg_pad_daclrch__ds1      :  1,    //      9
    reg_pad_daclrch__ds2      :  1,    //     10
    reg_pad_daclrch__ds3      :  1,    //     11
    reg_pad_daclrch__pd       :  1,    //     12
    reg_pad_daclrch__pu       :  1,    //     13
    reg_pad_daclrch__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dacclfch__ds0     :  1,    //     16
    reg_pad_dacclfch__ds1     :  1,    //     17
    reg_pad_dacclfch__ds2     :  1,    //     18
    reg_pad_dacclfch__ds3     :  1,    //     19
    reg_pad_dacclfch__pd      :  1,    //     20
    reg_pad_dacclfch__pu      :  1,    //     21
    reg_pad_dacclfch__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_do1__ds0      :  1,    //     24
    reg_pad_spi_do1__ds1      :  1,    //     25
    reg_pad_spi_do1__ds2      :  1,    //     26
    reg_pad_spi_do1__ds3      :  1,    //     27
    reg_pad_spi_do1__pd       :  1,    //     28
    reg_pad_spi_do1__pu       :  1,    //     29
    reg_pad_spi_do1__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2008    pad_lnx1_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_sclk__ds0    :  1,    //      0
    reg_pad_dim0_sclk__ds1    :  1,    //      1
    reg_pad_dim0_sclk__ds2    :  1,    //      2
    reg_pad_dim0_sclk__ds3    :  1,    //      3
    reg_pad_dim0_sclk__pd     :  1,    //      4
    reg_pad_dim0_sclk__pu     :  1,    //      5
    reg_pad_dim0_sclk__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim0_mosi__ds0    :  1,    //      8
    reg_pad_dim0_mosi__ds1    :  1,    //      9
    reg_pad_dim0_mosi__ds2    :  1,    //     10
    reg_pad_dim0_mosi__ds3    :  1,    //     11
    reg_pad_dim0_mosi__pd     :  1,    //     12
    reg_pad_dim0_mosi__pu     :  1,    //     13
    reg_pad_dim0_mosi__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dacslrch__ds0     :  1,    //     16
    reg_pad_dacslrch__ds1     :  1,    //     17
    reg_pad_dacslrch__ds2     :  1,    //     18
    reg_pad_dacslrch__ds3     :  1,    //     19
    reg_pad_dacslrch__pd      :  1,    //     20
    reg_pad_dacslrch__pu      :  1,    //     21
    reg_pad_dacslrch__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dacsck__ds0       :  1,    //     24
    reg_pad_dacsck__ds1       :  1,    //     25
    reg_pad_dacsck__ds2       :  1,    //     26
    reg_pad_dacsck__ds3       :  1,    //     27
    reg_pad_dacsck__pd        :  1,    //     28
    reg_pad_dacsck__pu        :  1,    //     29
    reg_pad_dacsck__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_200C    pad_lnx1_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim2_sclk__ds0    :  1,    //      0
    reg_pad_dim2_sclk__ds1    :  1,    //      1
    reg_pad_dim2_sclk__ds2    :  1,    //      2
    reg_pad_dim2_sclk__ds3    :  1,    //      3
    reg_pad_dim2_sclk__pd     :  1,    //      4
    reg_pad_dim2_sclk__pu     :  1,    //      5
    reg_pad_dim2_sclk__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim2_mosi__ds0    :  1,    //      8
    reg_pad_dim2_mosi__ds1    :  1,    //      9
    reg_pad_dim2_mosi__ds2    :  1,    //     10
    reg_pad_dim2_mosi__ds3    :  1,    //     11
    reg_pad_dim2_mosi__pd     :  1,    //     12
    reg_pad_dim2_mosi__pu     :  1,    //     13
    reg_pad_dim2_mosi__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim1_sclk__ds0    :  1,    //     16
    reg_pad_dim1_sclk__ds1    :  1,    //     17
    reg_pad_dim1_sclk__ds2    :  1,    //     18
    reg_pad_dim1_sclk__ds3    :  1,    //     19
    reg_pad_dim1_sclk__pd     :  1,    //     20
    reg_pad_dim1_sclk__pu     :  1,    //     21
    reg_pad_dim1_sclk__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim1_mosi__ds0    :  1,    //     24
    reg_pad_dim1_mosi__ds1    :  1,    //     25
    reg_pad_dim1_mosi__ds2    :  1,    //     26
    reg_pad_dim1_mosi__ds3    :  1,    //     27
    reg_pad_dim1_mosi__pd     :  1,    //     28
    reg_pad_dim1_mosi__pu     :  1,    //     29
    reg_pad_dim1_mosi__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2010    pad_lnx1_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ld_vs_out0__ds0   :  1,    //      0
    reg_pad_ld_vs_out0__ds1   :  1,    //      1
    reg_pad_ld_vs_out0__ds2   :  1,    //      2
    reg_pad_ld_vs_out0__ds3   :  1,    //      3
    reg_pad_ld_vs_out0__pd    :  1,    //      4
    reg_pad_ld_vs_out0__pu    :  1,    //      5
    reg_pad_ld_vs_out0__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_iec958out__ds0    :  1,    //      8
    reg_pad_iec958out__ds1    :  1,    //      9
    reg_pad_iec958out__ds2    :  1,    //     10
    reg_pad_iec958out__ds3    :  1,    //     11
    reg_pad_iec958out__pd     :  1,    //     12
    reg_pad_iec958out__pu     :  1,    //     13
    reg_pad_iec958out__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim3_sclk__ds0    :  1,    //     16
    reg_pad_dim3_sclk__ds1    :  1,    //     17
    reg_pad_dim3_sclk__ds2    :  1,    //     18
    reg_pad_dim3_sclk__ds3    :  1,    //     19
    reg_pad_dim3_sclk__pd     :  1,    //     20
    reg_pad_dim3_sclk__pu     :  1,    //     21
    reg_pad_dim3_sclk__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim3_mosi__ds0    :  1,    //     24
    reg_pad_dim3_mosi__ds1    :  1,    //     25
    reg_pad_dim3_mosi__ds2    :  1,    //     26
    reg_pad_dim3_mosi__ds3    :  1,    //     27
    reg_pad_dim3_mosi__pd     :  1,    //     28
    reg_pad_dim3_mosi__pu     :  1,    //     29
    reg_pad_dim3_mosi__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2014    pad_lnx1_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrch__ds0    :  1,    //      0
    reg_pad_pcmi3lrch__ds1    :  1,    //      1
    reg_pad_pcmi3lrch__ds2    :  1,    //      2
    reg_pad_pcmi3lrch__ds3    :  1,    //      3
    reg_pad_pcmi3lrch__pd     :  1,    //      4
    reg_pad_pcmi3lrch__pu     :  1,    //      5
    reg_pad_pcmi3lrch__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ld_vs_out3__ds0   :  1,    //      8
    reg_pad_ld_vs_out3__ds1   :  1,    //      9
    reg_pad_ld_vs_out3__ds2   :  1,    //     10
    reg_pad_ld_vs_out3__ds3   :  1,    //     11
    reg_pad_ld_vs_out3__pd    :  1,    //     12
    reg_pad_ld_vs_out3__pu    :  1,    //     13
    reg_pad_ld_vs_out3__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ld_vs_out2__ds0   :  1,    //     16
    reg_pad_ld_vs_out2__ds1   :  1,    //     17
    reg_pad_ld_vs_out2__ds2   :  1,    //     18
    reg_pad_ld_vs_out2__ds3   :  1,    //     19
    reg_pad_ld_vs_out2__pd    :  1,    //     20
    reg_pad_ld_vs_out2__pu    :  1,    //     21
    reg_pad_ld_vs_out2__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ld_vs_out1__ds0   :  1,    //     24
    reg_pad_ld_vs_out1__ds1   :  1,    //     25
    reg_pad_ld_vs_out1__ds2   :  1,    //     26
    reg_pad_ld_vs_out1__ds3   :  1,    //     27
    reg_pad_ld_vs_out1__pd    :  1,    //     28
    reg_pad_ld_vs_out1__pu    :  1,    //     29
    reg_pad_ld_vs_out1__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2018    pad_lnx1_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm0__ds0         :  1,    //      0
    reg_pad_pwm0__ds1         :  1,    //      1
    reg_pad_pwm0__ds2         :  1,    //      2
    reg_pad_pwm0__ds3         :  1,    //      3
    reg_pad_pwm0__pd          :  1,    //      4
    reg_pad_pwm0__pu          :  1,    //      5
    reg_pad_pwm0__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pwm_in__ds0       :  1,    //      8
    reg_pad_pwm_in__ds1       :  1,    //      9
    reg_pad_pwm_in__ds2       :  1,    //     10
    reg_pad_pwm_in__ds3       :  1,    //     11
    reg_pad_pwm_in__pd        :  1,    //     12
    reg_pad_pwm_in__pu        :  1,    //     13
    reg_pad_pwm_in__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_pcmi3sck__ds0     :  1,    //     16
    reg_pad_pcmi3sck__ds1     :  1,    //     17
    reg_pad_pcmi3sck__ds2     :  1,    //     18
    reg_pad_pcmi3sck__ds3     :  1,    //     19
    reg_pad_pcmi3sck__pd      :  1,    //     20
    reg_pad_pcmi3sck__pu      :  1,    //     21
    reg_pad_pcmi3sck__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pcmi3lrck__ds0    :  1,    //     24
    reg_pad_pcmi3lrck__ds1    :  1,    //     25
    reg_pad_pcmi3lrck__ds2    :  1,    //     26
    reg_pad_pcmi3lrck__ds3    :  1,    //     27
    reg_pad_pcmi3lrck__pd     :  1,    //     28
    reg_pad_pcmi3lrck__pu     :  1,    //     29
    reg_pad_pcmi3lrck__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_201C    pad_lnx1_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm2__ds0         :  1,    //      0
    reg_pad_pwm2__ds1         :  1,    //      1
    reg_pad_pwm2__ds2         :  1,    //      2
    reg_pad_pwm2__ds3         :  1,    //      3
    reg_pad_pwm2__pd          :  1,    //      4
    reg_pad_pwm2__pu          :  1,    //      5
    reg_pad_pwm2__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pwm1__ds0         :  1,    //      8
    reg_pad_pwm1__ds1         :  1,    //      9
    reg_pad_pwm1__ds2         :  1,    //     10
    reg_pad_pwm1__ds3         :  1,    //     11
    reg_pad_pwm1__pd          :  1,    //     12
    reg_pad_pwm1__pu          :  1,    //     13
    reg_pad_pwm1__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_do0__ds0      :  1,    //     16
    reg_pad_spi_do0__ds1      :  1,    //     17
    reg_pad_spi_do0__ds2      :  1,    //     18
    reg_pad_spi_do0__ds3      :  1,    //     19
    reg_pad_spi_do0__pd       :  1,    //     20
    reg_pad_spi_do0__pu       :  1,    //     21
    reg_pad_spi_do0__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_epi_mclk__ds0     :  1,    //     24
    reg_pad_epi_mclk__ds1     :  1,    //     25
    reg_pad_epi_mclk__ds2     :  1,    //     26
    reg_pad_epi_mclk__ds3     :  1,    //     27
    reg_pad_epi_mclk__pd      :  1,    //     28
    reg_pad_epi_mclk__pu      :  1,    //     29
    reg_pad_epi_mclk__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2020    pad_lnx1_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk1__ds0    :  1,    //      0
    reg_pad_spi_sclk1__ds1    :  1,    //      1
    reg_pad_spi_sclk1__ds2    :  1,    //      2
    reg_pad_spi_sclk1__ds3    :  1,    //      3
    reg_pad_spi_sclk1__pd     :  1,    //      4
    reg_pad_spi_sclk1__pu     :  1,    //      5
    reg_pad_spi_sclk1__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_sclk0__ds0    :  1,    //      8
    reg_pad_spi_sclk0__ds1    :  1,    //      9
    reg_pad_spi_sclk0__ds2    :  1,    //     10
    reg_pad_spi_sclk0__ds3    :  1,    //     11
    reg_pad_spi_sclk0__pd     :  1,    //     12
    reg_pad_spi_sclk0__pu     :  1,    //     13
    reg_pad_spi_sclk0__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_epi_gclk__ds0     :  1,    //     16
    reg_pad_epi_gclk__ds1     :  1,    //     17
    reg_pad_epi_gclk__ds2     :  1,    //     18
    reg_pad_epi_gclk__ds3     :  1,    //     19
    reg_pad_epi_gclk__pd      :  1,    //     20
    reg_pad_epi_gclk__pu      :  1,    //     21
    reg_pad_epi_gclk__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_epi_eo__ds0       :  1,    //     24
    reg_pad_epi_eo__ds1       :  1,    //     25
    reg_pad_epi_eo__ds2       :  1,    //     26
    reg_pad_epi_eo__ds3       :  1,    //     27
    reg_pad_epi_eo__pd        :  1,    //     28
    reg_pad_epi_eo__pu        :  1,    //     29
    reg_pad_epi_eo__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2024    pad_lnx1_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_di1__ds0      :  1,    //      0
    reg_pad_spi_di1__ds1      :  1,    //      1
    reg_pad_spi_di1__ds2      :  1,    //      2
    reg_pad_spi_di1__ds3      :  1,    //      3
    reg_pad_spi_di1__pd       :  1,    //      4
    reg_pad_spi_di1__pu       :  1,    //      5
    reg_pad_spi_di1__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_di0__ds0      :  1,    //      8
    reg_pad_spi_di0__ds1      :  1,    //      9
    reg_pad_spi_di0__ds2      :  1,    //     10
    reg_pad_spi_di0__ds3      :  1,    //     11
    reg_pad_spi_di0__pd       :  1,    //     12
    reg_pad_spi_di0__pu       :  1,    //     13
    reg_pad_spi_di0__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_cs1__ds0      :  1,    //     16
    reg_pad_spi_cs1__ds1      :  1,    //     17
    reg_pad_spi_cs1__ds2      :  1,    //     18
    reg_pad_spi_cs1__ds3      :  1,    //     19
    reg_pad_spi_cs1__pd       :  1,    //     20
    reg_pad_spi_cs1__pu       :  1,    //     21
    reg_pad_spi_cs1__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_cs0__ds0      :  1,    //     24
    reg_pad_spi_cs0__ds1      :  1,    //     25
    reg_pad_spi_cs0__ds2      :  1,    //     26
    reg_pad_spi_cs0__ds3      :  1,    //     27
    reg_pad_spi_cs0__pd       :  1,    //     28
    reg_pad_spi_cs0__pu       :  1,    //     29
    reg_pad_spi_cs0__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2028    pad_lnx1_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio25__ds0       :  1,    //      0
    reg_pad_gpio25__ds1       :  1,    //      1
    reg_pad_gpio25__ds2       :  1,    //      2
    reg_pad_gpio25__ds3       :  1,    //      3
    reg_pad_gpio25__pd        :  1,    //      4
    reg_pad_gpio25__pu        :  1,    //      5
    reg_pad_gpio25__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_epi_vst__ds0      :  1,    //      8
    reg_pad_epi_vst__ds1      :  1,    //      9
    reg_pad_epi_vst__ds2      :  1,    //     10
    reg_pad_epi_vst__ds3      :  1,    //     11
    reg_pad_epi_vst__pd       :  1,    //     12
    reg_pad_epi_vst__pu       :  1,    //     13
    reg_pad_epi_vst__st       :  1,    //     14
                              : 17;    //  31:15 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_202C    pad_lnx1_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_mclk2__ds0    :  1,    //      0
    reg_pad_epi_mclk2__ds1    :  1,    //      1
    reg_pad_epi_mclk2__ds2    :  1,    //      2
    reg_pad_epi_mclk2__ds3    :  1,    //      3
    reg_pad_epi_mclk2__pd     :  1,    //      4
    reg_pad_epi_mclk2__pu     :  1,    //      5
    reg_pad_epi_mclk2__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_epi_gclk2__ds0    :  1,    //      8
    reg_pad_epi_gclk2__ds1    :  1,    //      9
    reg_pad_epi_gclk2__ds2    :  1,    //     10
    reg_pad_epi_gclk2__ds3    :  1,    //     11
    reg_pad_epi_gclk2__pd     :  1,    //     12
    reg_pad_epi_gclk2__pu     :  1,    //     13
    reg_pad_epi_gclk2__st     :  1,    //     14
                              : 17;    //  31:15 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2100    pad_lnx1_64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacsck_mux_sel    :  4,    //   3: 0
    reg_pad_daclrck_mux_sel   :  4,    //   7: 4
    reg_pad_daclrch_mux_sel   :  4,    //  11: 8
    reg_pad_dacclfch_mux_sel  :  4,    //  15:12
    reg_pad_aec_lrch3_mux_sel :  4,    //  19:16
    reg_pad_aec_lrch2_mux_sel :  4,    //  23:20
    reg_pad_aec_lrch1_mux_sel :  4,    //  27:24
    reg_pad_aec_lrch0_mux_sel :  4;    //  31:28
}IOMUX_CTRL_LNX1_PAD_LNX1_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2104    pad_lnx1_65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim3_mosi_mux_sel :  4,    //   3: 0
    reg_pad_dim2_sclk_mux_sel :  4,    //   7: 4
    reg_pad_dim2_mosi_mux_sel :  4,    //  11: 8
    reg_pad_dim1_sclk_mux_sel :  4,    //  15:12
    reg_pad_dim1_mosi_mux_sel :  4,    //  19:16
    reg_pad_dim0_sclk_mux_sel :  4,    //  23:20
    reg_pad_dim0_mosi_mux_sel :  4,    //  27:24
    reg_pad_dacslrch_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_LNX1_PAD_LNX1_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2108    pad_lnx1_66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrck_mux_sel :  4,    //   3: 0
    reg_pad_pcmi3lrch_mux_sel :  4,    //   7: 4
    reg_pad_ld_vs_out3_mux_sel:  4,    //  11: 8
    reg_pad_ld_vs_out2_mux_sel:  4,    //  15:12
    reg_pad_ld_vs_out1_mux_sel:  4,    //  19:16
    reg_pad_ld_vs_out0_mux_sel:  4,    //  23:20
    reg_pad_iec958out_mux_sel :  4,    //  27:24
    reg_pad_dim3_sclk_mux_sel :  4;    //  31:28
}IOMUX_CTRL_LNX1_PAD_LNX1_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_210C    pad_lnx1_67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_di0_mux_sel   :  4,    //   3: 0
    reg_pad_spi_cs1_mux_sel   :  4,    //   7: 4
    reg_pad_spi_cs0_mux_sel   :  4,    //  11: 8
    reg_pad_pwm2_mux_sel      :  4,    //  15:12
    reg_pad_pwm1_mux_sel      :  4,    //  19:16
    reg_pad_pwm0_mux_sel      :  4,    //  23:20
    reg_pad_pwm_in_mux_sel    :  4,    //  27:24
    reg_pad_pcmi3sck_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_LNX1_PAD_LNX1_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2110    pad_lnx1_68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk1_mux_sel :  4,    //   3: 0
    reg_pad_spi_sclk0_mux_sel :  4,    //   7: 4
    reg_pad_spi_do1_mux_sel   :  4,    //  11: 8
    reg_pad_spi_do0_mux_sel   :  4,    //  15:12
    reg_pad_spi_di1_mux_sel   :  4,    //  19:16
                              : 12;    //  31:20 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2114    pad_lnx1_69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_vst_mux_sel   :  4,    //   3: 0
    reg_pad_epi_mclk2_mux_sel :  4,    //   7: 4
    reg_pad_epi_mclk_mux_sel  :  4,    //  11: 8
    reg_pad_epi_gclk2_mux_sel :  4,    //  15:12
    reg_pad_epi_gclk_mux_sel  :  4,    //  19:16
    reg_pad_epi_eo_mux_sel    :  4,    //  23:20
                              :  8;    //  31:24 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_69_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2118    pad_lnx1_70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio25_mux_sel    :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}IOMUX_CTRL_LNX1_PAD_LNX1_70_O24A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_LNX1_PAD_LNX1_00_O24A0_T    pad_lnx1_00;         // 0xCC97_2000
    IOMUX_CTRL_LNX1_PAD_LNX1_01_O24A0_T    pad_lnx1_01;         // 0xCC97_2004
    IOMUX_CTRL_LNX1_PAD_LNX1_02_O24A0_T    pad_lnx1_02;         // 0xCC97_2008
    IOMUX_CTRL_LNX1_PAD_LNX1_03_O24A0_T    pad_lnx1_03;         // 0xCC97_200C
    IOMUX_CTRL_LNX1_PAD_LNX1_04_O24A0_T    pad_lnx1_04;         // 0xCC97_2010
    IOMUX_CTRL_LNX1_PAD_LNX1_05_O24A0_T    pad_lnx1_05;         // 0xCC97_2014
    IOMUX_CTRL_LNX1_PAD_LNX1_06_O24A0_T    pad_lnx1_06;         // 0xCC97_2018
    IOMUX_CTRL_LNX1_PAD_LNX1_07_O24A0_T    pad_lnx1_07;         // 0xCC97_201C
    IOMUX_CTRL_LNX1_PAD_LNX1_08_O24A0_T    pad_lnx1_08;         // 0xCC97_2020
    IOMUX_CTRL_LNX1_PAD_LNX1_09_O24A0_T    pad_lnx1_09;         // 0xCC97_2024
    IOMUX_CTRL_LNX1_PAD_LNX1_10_O24A0_T    pad_lnx1_10;         // 0xCC97_2028
    IOMUX_CTRL_LNX1_PAD_LNX1_11_O24A0_T    pad_lnx1_11;         // 0xCC97_202C
    UINT32                             _rsvd_00[52];            // 0xCC97_2030 ~ 0xCC97_20FC
    IOMUX_CTRL_LNX1_PAD_LNX1_64_O24A0_T    pad_lnx1_64;         // 0xCC97_2100
    IOMUX_CTRL_LNX1_PAD_LNX1_65_O24A0_T    pad_lnx1_65;         // 0xCC97_2104
    IOMUX_CTRL_LNX1_PAD_LNX1_66_O24A0_T    pad_lnx1_66;         // 0xCC97_2108
    IOMUX_CTRL_LNX1_PAD_LNX1_67_O24A0_T    pad_lnx1_67;         // 0xCC97_210C
    IOMUX_CTRL_LNX1_PAD_LNX1_68_O24A0_T    pad_lnx1_68;         // 0xCC97_2110
    IOMUX_CTRL_LNX1_PAD_LNX1_69_O24A0_T    pad_lnx1_69;         // 0xCC97_2114
    IOMUX_CTRL_LNX1_PAD_LNX1_70_O24A0_T    pad_lnx1_70;         // 0xCC97_2118
}IOMUX_CTRL_LNX1_REG_O24A0_T;
/* 19 regs */

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

#define IOMUX_CTRL_LNX1_PAD_LNX1_00_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define IOMUX_CTRL_LNX1_PAD_LNX1_01_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define IOMUX_CTRL_LNX1_PAD_LNX1_02_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define IOMUX_CTRL_LNX1_PAD_LNX1_03_O24A0_T_OFF             (BASEADDRESS+0x000C)
#define IOMUX_CTRL_LNX1_PAD_LNX1_04_O24A0_T_OFF             (BASEADDRESS+0x0010)
#define IOMUX_CTRL_LNX1_PAD_LNX1_05_O24A0_T_OFF             (BASEADDRESS+0x0014)
#define IOMUX_CTRL_LNX1_PAD_LNX1_06_O24A0_T_OFF             (BASEADDRESS+0x0018)
#define IOMUX_CTRL_LNX1_PAD_LNX1_07_O24A0_T_OFF             (BASEADDRESS+0x001C)
#define IOMUX_CTRL_LNX1_PAD_LNX1_08_O24A0_T_OFF             (BASEADDRESS+0x0020)
#define IOMUX_CTRL_LNX1_PAD_LNX1_09_O24A0_T_OFF             (BASEADDRESS+0x0024)
#define IOMUX_CTRL_LNX1_PAD_LNX1_10_O24A0_T_OFF             (BASEADDRESS+0x0028)
#define IOMUX_CTRL_LNX1_PAD_LNX1_11_O24A0_T_OFF             (BASEADDRESS+0x002C)
#define IOMUX_CTRL_LNX1_PAD_LNX1_64_O24A0_T_OFF             (BASEADDRESS+0x0100)
#define IOMUX_CTRL_LNX1_PAD_LNX1_65_O24A0_T_OFF             (BASEADDRESS+0x0104)
#define IOMUX_CTRL_LNX1_PAD_LNX1_66_O24A0_T_OFF             (BASEADDRESS+0x0108)
#define IOMUX_CTRL_LNX1_PAD_LNX1_67_O24A0_T_OFF             (BASEADDRESS+0x010C)
#define IOMUX_CTRL_LNX1_PAD_LNX1_68_O24A0_T_OFF             (BASEADDRESS+0x0110)
#define IOMUX_CTRL_LNX1_PAD_LNX1_69_O24A0_T_OFF             (BASEADDRESS+0x0114)
#define IOMUX_CTRL_LNX1_PAD_LNX1_70_O24A0_T_OFF             (BASEADDRESS+0x0118)

/*-----------------------------------------------------------------------------------------
    0xCC97_2000    pad_lnx1_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_aec_lrch3__ds0: 1;    //    0
    UINT32 reg_pad_aec_lrch3__ds1: 1;    //    1
    UINT32 reg_pad_aec_lrch3__ds2: 1;    //    2
    UINT32 reg_pad_aec_lrch3__ds3: 1;    //    3
    UINT32 reg_pad_aec_lrch3__pd: 1;    //     4
    UINT32 reg_pad_aec_lrch3__pu: 1;    //     5
    UINT32 reg_pad_aec_lrch3__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_aec_lrch2__ds0: 1;    //    8
    UINT32 reg_pad_aec_lrch2__ds1: 1;    //    9
    UINT32 reg_pad_aec_lrch2__ds2: 1;    //   10
    UINT32 reg_pad_aec_lrch2__ds3: 1;    //   11
    UINT32 reg_pad_aec_lrch2__pd: 1;    //    12
    UINT32 reg_pad_aec_lrch2__pu: 1;    //    13
    UINT32 reg_pad_aec_lrch2__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_aec_lrch1__ds0: 1;    //   16
    UINT32 reg_pad_aec_lrch1__ds1: 1;    //   17
    UINT32 reg_pad_aec_lrch1__ds2: 1;    //   18
    UINT32 reg_pad_aec_lrch1__ds3: 1;    //   19
    UINT32 reg_pad_aec_lrch1__pd: 1;    //    20
    UINT32 reg_pad_aec_lrch1__pu: 1;    //    21
    UINT32 reg_pad_aec_lrch1__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_aec_lrch0__ds0: 1;    //   24
    UINT32 reg_pad_aec_lrch0__ds1: 1;    //   25
    UINT32 reg_pad_aec_lrch0__ds2: 1;    //   26
    UINT32 reg_pad_aec_lrch0__ds3: 1;    //   27
    UINT32 reg_pad_aec_lrch0__pd: 1;    //    28
    UINT32 reg_pad_aec_lrch0__pu: 1;    //    29
    UINT32 reg_pad_aec_lrch0__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2004    pad_lnx1_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_daclrck__ds0: 1;    //      0
    UINT32 reg_pad_daclrck__ds1: 1;    //      1
    UINT32 reg_pad_daclrck__ds2: 1;    //      2
    UINT32 reg_pad_daclrck__ds3: 1;    //      3
    UINT32 reg_pad_daclrck__pd:  1;    //      4
    UINT32 reg_pad_daclrck__pu:  1;    //      5
    UINT32 reg_pad_daclrck__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_daclrch__ds0: 1;    //      8
    UINT32 reg_pad_daclrch__ds1: 1;    //      9
    UINT32 reg_pad_daclrch__ds2: 1;    //     10
    UINT32 reg_pad_daclrch__ds3: 1;    //     11
    UINT32 reg_pad_daclrch__pd:  1;    //     12
    UINT32 reg_pad_daclrch__pu:  1;    //     13
    UINT32 reg_pad_daclrch__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dacclfch__ds0: 1;    //    16
    UINT32 reg_pad_dacclfch__ds1: 1;    //    17
    UINT32 reg_pad_dacclfch__ds2: 1;    //    18
    UINT32 reg_pad_dacclfch__ds3: 1;    //    19
    UINT32 reg_pad_dacclfch__pd: 1;    //     20
    UINT32 reg_pad_dacclfch__pu: 1;    //     21
    UINT32 reg_pad_dacclfch__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_spi_do1__ds0: 1;    //     24
    UINT32 reg_pad_spi_do1__ds1: 1;    //     25
    UINT32 reg_pad_spi_do1__ds2: 1;    //     26
    UINT32 reg_pad_spi_do1__ds3: 1;    //     27
    UINT32 reg_pad_spi_do1__pd:  1;    //     28
    UINT32 reg_pad_spi_do1__pu:  1;    //     29
    UINT32 reg_pad_spi_do1__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2008    pad_lnx1_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim0_sclk__ds0: 1;    //    0
    UINT32 reg_pad_dim0_sclk__ds1: 1;    //    1
    UINT32 reg_pad_dim0_sclk__ds2: 1;    //    2
    UINT32 reg_pad_dim0_sclk__ds3: 1;    //    3
    UINT32 reg_pad_dim0_sclk__pd: 1;    //     4
    UINT32 reg_pad_dim0_sclk__pu: 1;    //     5
    UINT32 reg_pad_dim0_sclk__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_dim0_mosi__ds0: 1;    //    8
    UINT32 reg_pad_dim0_mosi__ds1: 1;    //    9
    UINT32 reg_pad_dim0_mosi__ds2: 1;    //   10
    UINT32 reg_pad_dim0_mosi__ds3: 1;    //   11
    UINT32 reg_pad_dim0_mosi__pd: 1;    //    12
    UINT32 reg_pad_dim0_mosi__pu: 1;    //    13
    UINT32 reg_pad_dim0_mosi__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dacslrch__ds0: 1;    //    16
    UINT32 reg_pad_dacslrch__ds1: 1;    //    17
    UINT32 reg_pad_dacslrch__ds2: 1;    //    18
    UINT32 reg_pad_dacslrch__ds3: 1;    //    19
    UINT32 reg_pad_dacslrch__pd: 1;    //     20
    UINT32 reg_pad_dacslrch__pu: 1;    //     21
    UINT32 reg_pad_dacslrch__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dacsck__ds0:  1;    //     24
    UINT32 reg_pad_dacsck__ds1:  1;    //     25
    UINT32 reg_pad_dacsck__ds2:  1;    //     26
    UINT32 reg_pad_dacsck__ds3:  1;    //     27
    UINT32 reg_pad_dacsck__pd :  1;    //     28
    UINT32 reg_pad_dacsck__pu :  1;    //     29
    UINT32 reg_pad_dacsck__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_200C    pad_lnx1_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim2_sclk__ds0: 1;    //    0
    UINT32 reg_pad_dim2_sclk__ds1: 1;    //    1
    UINT32 reg_pad_dim2_sclk__ds2: 1;    //    2
    UINT32 reg_pad_dim2_sclk__ds3: 1;    //    3
    UINT32 reg_pad_dim2_sclk__pd: 1;    //     4
    UINT32 reg_pad_dim2_sclk__pu: 1;    //     5
    UINT32 reg_pad_dim2_sclk__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_dim2_mosi__ds0: 1;    //    8
    UINT32 reg_pad_dim2_mosi__ds1: 1;    //    9
    UINT32 reg_pad_dim2_mosi__ds2: 1;    //   10
    UINT32 reg_pad_dim2_mosi__ds3: 1;    //   11
    UINT32 reg_pad_dim2_mosi__pd: 1;    //    12
    UINT32 reg_pad_dim2_mosi__pu: 1;    //    13
    UINT32 reg_pad_dim2_mosi__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dim1_sclk__ds0: 1;    //   16
    UINT32 reg_pad_dim1_sclk__ds1: 1;    //   17
    UINT32 reg_pad_dim1_sclk__ds2: 1;    //   18
    UINT32 reg_pad_dim1_sclk__ds3: 1;    //   19
    UINT32 reg_pad_dim1_sclk__pd: 1;    //    20
    UINT32 reg_pad_dim1_sclk__pu: 1;    //    21
    UINT32 reg_pad_dim1_sclk__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dim1_mosi__ds0: 1;    //   24
    UINT32 reg_pad_dim1_mosi__ds1: 1;    //   25
    UINT32 reg_pad_dim1_mosi__ds2: 1;    //   26
    UINT32 reg_pad_dim1_mosi__ds3: 1;    //   27
    UINT32 reg_pad_dim1_mosi__pd: 1;    //    28
    UINT32 reg_pad_dim1_mosi__pu: 1;    //    29
    UINT32 reg_pad_dim1_mosi__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2010    pad_lnx1_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ld_vs_out0__ds0: 1;    //   0
    UINT32 reg_pad_ld_vs_out0__ds1: 1;    //   1
    UINT32 reg_pad_ld_vs_out0__ds2: 1;    //   2
    UINT32 reg_pad_ld_vs_out0__ds3: 1;    //   3
    UINT32 reg_pad_ld_vs_out0__pd: 1;    //    4
    UINT32 reg_pad_ld_vs_out0__pu: 1;    //    5
    UINT32 reg_pad_ld_vs_out0__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_iec958out__ds0: 1;    //    8
    UINT32 reg_pad_iec958out__ds1: 1;    //    9
    UINT32 reg_pad_iec958out__ds2: 1;    //   10
    UINT32 reg_pad_iec958out__ds3: 1;    //   11
    UINT32 reg_pad_iec958out__pd: 1;    //    12
    UINT32 reg_pad_iec958out__pu: 1;    //    13
    UINT32 reg_pad_iec958out__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dim3_sclk__ds0: 1;    //   16
    UINT32 reg_pad_dim3_sclk__ds1: 1;    //   17
    UINT32 reg_pad_dim3_sclk__ds2: 1;    //   18
    UINT32 reg_pad_dim3_sclk__ds3: 1;    //   19
    UINT32 reg_pad_dim3_sclk__pd: 1;    //    20
    UINT32 reg_pad_dim3_sclk__pu: 1;    //    21
    UINT32 reg_pad_dim3_sclk__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dim3_mosi__ds0: 1;    //   24
    UINT32 reg_pad_dim3_mosi__ds1: 1;    //   25
    UINT32 reg_pad_dim3_mosi__ds2: 1;    //   26
    UINT32 reg_pad_dim3_mosi__ds3: 1;    //   27
    UINT32 reg_pad_dim3_mosi__pd: 1;    //    28
    UINT32 reg_pad_dim3_mosi__pu: 1;    //    29
    UINT32 reg_pad_dim3_mosi__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2014    pad_lnx1_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pcmi3lrch__ds0: 1;    //    0
    UINT32 reg_pad_pcmi3lrch__ds1: 1;    //    1
    UINT32 reg_pad_pcmi3lrch__ds2: 1;    //    2
    UINT32 reg_pad_pcmi3lrch__ds3: 1;    //    3
    UINT32 reg_pad_pcmi3lrch__pd: 1;    //     4
    UINT32 reg_pad_pcmi3lrch__pu: 1;    //     5
    UINT32 reg_pad_pcmi3lrch__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ld_vs_out3__ds0: 1;    //   8
    UINT32 reg_pad_ld_vs_out3__ds1: 1;    //   9
    UINT32 reg_pad_ld_vs_out3__ds2: 1;    //  10
    UINT32 reg_pad_ld_vs_out3__ds3: 1;    //  11
    UINT32 reg_pad_ld_vs_out3__pd: 1;    //   12
    UINT32 reg_pad_ld_vs_out3__pu: 1;    //   13
    UINT32 reg_pad_ld_vs_out3__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ld_vs_out2__ds0: 1;    //  16
    UINT32 reg_pad_ld_vs_out2__ds1: 1;    //  17
    UINT32 reg_pad_ld_vs_out2__ds2: 1;    //  18
    UINT32 reg_pad_ld_vs_out2__ds3: 1;    //  19
    UINT32 reg_pad_ld_vs_out2__pd: 1;    //   20
    UINT32 reg_pad_ld_vs_out2__pu: 1;    //   21
    UINT32 reg_pad_ld_vs_out2__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ld_vs_out1__ds0: 1;    //  24
    UINT32 reg_pad_ld_vs_out1__ds1: 1;    //  25
    UINT32 reg_pad_ld_vs_out1__ds2: 1;    //  26
    UINT32 reg_pad_ld_vs_out1__ds3: 1;    //  27
    UINT32 reg_pad_ld_vs_out1__pd: 1;    //   28
    UINT32 reg_pad_ld_vs_out1__pu: 1;    //   29
    UINT32 reg_pad_ld_vs_out1__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2018    pad_lnx1_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pwm0__ds0  :  1;    //      0
    UINT32 reg_pad_pwm0__ds1  :  1;    //      1
    UINT32 reg_pad_pwm0__ds2  :  1;    //      2
    UINT32 reg_pad_pwm0__ds3  :  1;    //      3
    UINT32 reg_pad_pwm0__pd   :  1;    //      4
    UINT32 reg_pad_pwm0__pu   :  1;    //      5
    UINT32 reg_pad_pwm0__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_pwm_in__ds0:  1;    //      8
    UINT32 reg_pad_pwm_in__ds1:  1;    //      9
    UINT32 reg_pad_pwm_in__ds2:  1;    //     10
    UINT32 reg_pad_pwm_in__ds3:  1;    //     11
    UINT32 reg_pad_pwm_in__pd :  1;    //     12
    UINT32 reg_pad_pwm_in__pu :  1;    //     13
    UINT32 reg_pad_pwm_in__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_pcmi3sck__ds0: 1;    //    16
    UINT32 reg_pad_pcmi3sck__ds1: 1;    //    17
    UINT32 reg_pad_pcmi3sck__ds2: 1;    //    18
    UINT32 reg_pad_pcmi3sck__ds3: 1;    //    19
    UINT32 reg_pad_pcmi3sck__pd: 1;    //     20
    UINT32 reg_pad_pcmi3sck__pu: 1;    //     21
    UINT32 reg_pad_pcmi3sck__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_pcmi3lrck__ds0: 1;    //   24
    UINT32 reg_pad_pcmi3lrck__ds1: 1;    //   25
    UINT32 reg_pad_pcmi3lrck__ds2: 1;    //   26
    UINT32 reg_pad_pcmi3lrck__ds3: 1;    //   27
    UINT32 reg_pad_pcmi3lrck__pd: 1;    //    28
    UINT32 reg_pad_pcmi3lrck__pu: 1;    //    29
    UINT32 reg_pad_pcmi3lrck__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_201C    pad_lnx1_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pwm2__ds0  :  1;    //      0
    UINT32 reg_pad_pwm2__ds1  :  1;    //      1
    UINT32 reg_pad_pwm2__ds2  :  1;    //      2
    UINT32 reg_pad_pwm2__ds3  :  1;    //      3
    UINT32 reg_pad_pwm2__pd   :  1;    //      4
    UINT32 reg_pad_pwm2__pu   :  1;    //      5
    UINT32 reg_pad_pwm2__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_pwm1__ds0  :  1;    //      8
    UINT32 reg_pad_pwm1__ds1  :  1;    //      9
    UINT32 reg_pad_pwm1__ds2  :  1;    //     10
    UINT32 reg_pad_pwm1__ds3  :  1;    //     11
    UINT32 reg_pad_pwm1__pd   :  1;    //     12
    UINT32 reg_pad_pwm1__pu   :  1;    //     13
    UINT32 reg_pad_pwm1__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_spi_do0__ds0: 1;    //     16
    UINT32 reg_pad_spi_do0__ds1: 1;    //     17
    UINT32 reg_pad_spi_do0__ds2: 1;    //     18
    UINT32 reg_pad_spi_do0__ds3: 1;    //     19
    UINT32 reg_pad_spi_do0__pd:  1;    //     20
    UINT32 reg_pad_spi_do0__pu:  1;    //     21
    UINT32 reg_pad_spi_do0__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_epi_mclk__ds0: 1;    //    24
    UINT32 reg_pad_epi_mclk__ds1: 1;    //    25
    UINT32 reg_pad_epi_mclk__ds2: 1;    //    26
    UINT32 reg_pad_epi_mclk__ds3: 1;    //    27
    UINT32 reg_pad_epi_mclk__pd: 1;    //     28
    UINT32 reg_pad_epi_mclk__pu: 1;    //     29
    UINT32 reg_pad_epi_mclk__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2020    pad_lnx1_08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_sclk1__ds0: 1;    //    0
    UINT32 reg_pad_spi_sclk1__ds1: 1;    //    1
    UINT32 reg_pad_spi_sclk1__ds2: 1;    //    2
    UINT32 reg_pad_spi_sclk1__ds3: 1;    //    3
    UINT32 reg_pad_spi_sclk1__pd: 1;    //     4
    UINT32 reg_pad_spi_sclk1__pu: 1;    //     5
    UINT32 reg_pad_spi_sclk1__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_spi_sclk0__ds0: 1;    //    8
    UINT32 reg_pad_spi_sclk0__ds1: 1;    //    9
    UINT32 reg_pad_spi_sclk0__ds2: 1;    //   10
    UINT32 reg_pad_spi_sclk0__ds3: 1;    //   11
    UINT32 reg_pad_spi_sclk0__pd: 1;    //    12
    UINT32 reg_pad_spi_sclk0__pu: 1;    //    13
    UINT32 reg_pad_spi_sclk0__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_epi_gclk__ds0: 1;    //    16
    UINT32 reg_pad_epi_gclk__ds1: 1;    //    17
    UINT32 reg_pad_epi_gclk__ds2: 1;    //    18
    UINT32 reg_pad_epi_gclk__ds3: 1;    //    19
    UINT32 reg_pad_epi_gclk__pd: 1;    //     20
    UINT32 reg_pad_epi_gclk__pu: 1;    //     21
    UINT32 reg_pad_epi_gclk__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_epi_eo__ds0:  1;    //     24
    UINT32 reg_pad_epi_eo__ds1:  1;    //     25
    UINT32 reg_pad_epi_eo__ds2:  1;    //     26
    UINT32 reg_pad_epi_eo__ds3:  1;    //     27
    UINT32 reg_pad_epi_eo__pd :  1;    //     28
    UINT32 reg_pad_epi_eo__pu :  1;    //     29
    UINT32 reg_pad_epi_eo__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2024    pad_lnx1_09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_di1__ds0: 1;    //      0
    UINT32 reg_pad_spi_di1__ds1: 1;    //      1
    UINT32 reg_pad_spi_di1__ds2: 1;    //      2
    UINT32 reg_pad_spi_di1__ds3: 1;    //      3
    UINT32 reg_pad_spi_di1__pd:  1;    //      4
    UINT32 reg_pad_spi_di1__pu:  1;    //      5
    UINT32 reg_pad_spi_di1__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_spi_di0__ds0: 1;    //      8
    UINT32 reg_pad_spi_di0__ds1: 1;    //      9
    UINT32 reg_pad_spi_di0__ds2: 1;    //     10
    UINT32 reg_pad_spi_di0__ds3: 1;    //     11
    UINT32 reg_pad_spi_di0__pd:  1;    //     12
    UINT32 reg_pad_spi_di0__pu:  1;    //     13
    UINT32 reg_pad_spi_di0__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_spi_cs1__ds0: 1;    //     16
    UINT32 reg_pad_spi_cs1__ds1: 1;    //     17
    UINT32 reg_pad_spi_cs1__ds2: 1;    //     18
    UINT32 reg_pad_spi_cs1__ds3: 1;    //     19
    UINT32 reg_pad_spi_cs1__pd:  1;    //     20
    UINT32 reg_pad_spi_cs1__pu:  1;    //     21
    UINT32 reg_pad_spi_cs1__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_spi_cs0__ds0: 1;    //     24
    UINT32 reg_pad_spi_cs0__ds1: 1;    //     25
    UINT32 reg_pad_spi_cs0__ds2: 1;    //     26
    UINT32 reg_pad_spi_cs0__ds3: 1;    //     27
    UINT32 reg_pad_spi_cs0__pd:  1;    //     28
    UINT32 reg_pad_spi_cs0__pu:  1;    //     29
    UINT32 reg_pad_spi_cs0__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2028    pad_lnx1_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio25__ds0:  1;    //      0
    UINT32 reg_pad_gpio25__ds1:  1;    //      1
    UINT32 reg_pad_gpio25__ds2:  1;    //      2
    UINT32 reg_pad_gpio25__ds3:  1;    //      3
    UINT32 reg_pad_gpio25__pd :  1;    //      4
    UINT32 reg_pad_gpio25__pu :  1;    //      5
    UINT32 reg_pad_gpio25__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_epi_vst__ds0: 1;    //      8
    UINT32 reg_pad_epi_vst__ds1: 1;    //      9
    UINT32 reg_pad_epi_vst__ds2: 1;    //     10
    UINT32 reg_pad_epi_vst__ds3: 1;    //     11
    UINT32 reg_pad_epi_vst__pd:  1;    //     12
    UINT32 reg_pad_epi_vst__pu:  1;    //     13
    UINT32 reg_pad_epi_vst__st:  1;    //     14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_202C    pad_lnx1_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_epi_mclk2__ds0: 1;    //    0
    UINT32 reg_pad_epi_mclk2__ds1: 1;    //    1
    UINT32 reg_pad_epi_mclk2__ds2: 1;    //    2
    UINT32 reg_pad_epi_mclk2__ds3: 1;    //    3
    UINT32 reg_pad_epi_mclk2__pd: 1;    //     4
    UINT32 reg_pad_epi_mclk2__pu: 1;    //     5
    UINT32 reg_pad_epi_mclk2__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_epi_gclk2__ds0: 1;    //    8
    UINT32 reg_pad_epi_gclk2__ds1: 1;    //    9
    UINT32 reg_pad_epi_gclk2__ds2: 1;    //   10
    UINT32 reg_pad_epi_gclk2__ds3: 1;    //   11
    UINT32 reg_pad_epi_gclk2__pd: 1;    //    12
    UINT32 reg_pad_epi_gclk2__pu: 1;    //    13
    UINT32 reg_pad_epi_gclk2__st: 1;    //    14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2100    pad_lnx1_64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dacsck_mux_sel: 4;    //  3:0
    UINT32 reg_pad_daclrck_mux_sel: 4;    //  7:4
    UINT32 reg_pad_daclrch_mux_sel: 4;    //  11:8
    UINT32 reg_pad_dacclfch_mux_sel: 4;    //  15:12
    UINT32 reg_pad_aec_lrch3_mux_sel: 4;    //  19:16
    UINT32 reg_pad_aec_lrch2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_aec_lrch1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_aec_lrch0_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2104    pad_lnx1_65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim3_mosi_mux_sel: 4;    //  3:0
    UINT32 reg_pad_dim2_sclk_mux_sel: 4;    //  7:4
    UINT32 reg_pad_dim2_mosi_mux_sel: 4;    //  11:8
    UINT32 reg_pad_dim1_sclk_mux_sel: 4;    //  15:12
    UINT32 reg_pad_dim1_mosi_mux_sel: 4;    //  19:16
    UINT32 reg_pad_dim0_sclk_mux_sel: 4;    //  23:20
    UINT32 reg_pad_dim0_mosi_mux_sel: 4;    //  27:24
    UINT32 reg_pad_dacslrch_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2108    pad_lnx1_66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pcmi3lrck_mux_sel: 4;    //  3:0
    UINT32 reg_pad_pcmi3lrch_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ld_vs_out3_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ld_vs_out2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ld_vs_out1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ld_vs_out0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_iec958out_mux_sel: 4;    //  27:24
    UINT32 reg_pad_dim3_sclk_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_210C    pad_lnx1_67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_di0_mux_sel: 4;    //  3:0
    UINT32 reg_pad_spi_cs1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_spi_cs0_mux_sel: 4;    //  11:8
    UINT32 reg_pad_pwm2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_pwm1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_pwm0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_pwm_in_mux_sel: 4;    //  27:24
    UINT32 reg_pad_pcmi3sck_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2110    pad_lnx1_68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_sclk1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_spi_sclk0_mux_sel: 4;    //  7:4
    UINT32 reg_pad_spi_do1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_spi_do0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_spi_di1_mux_sel: 4;    //  19:16
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2114    pad_lnx1_69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_epi_vst_mux_sel: 4;    //  3:0
    UINT32 reg_pad_epi_mclk2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_epi_mclk_mux_sel: 4;    //  11:8
    UINT32 reg_pad_epi_gclk2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_epi_gclk_mux_sel: 4;    //  19:16
    UINT32 reg_pad_epi_eo_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_69_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2118    pad_lnx1_70 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio25_mux_sel: 4;    //  3:0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IOMUX_CTRL_LNX1_PAD_LNX1_70_O24A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_LNX1_PAD_LNX1_00_O24A0_T    pad_lnx1_00;         // 0xCC97_2000
    IOMUX_CTRL_LNX1_PAD_LNX1_01_O24A0_T    pad_lnx1_01;         // 0xCC97_2004
    IOMUX_CTRL_LNX1_PAD_LNX1_02_O24A0_T    pad_lnx1_02;         // 0xCC97_2008
    IOMUX_CTRL_LNX1_PAD_LNX1_03_O24A0_T    pad_lnx1_03;         // 0xCC97_200C
    IOMUX_CTRL_LNX1_PAD_LNX1_04_O24A0_T    pad_lnx1_04;         // 0xCC97_2010
    IOMUX_CTRL_LNX1_PAD_LNX1_05_O24A0_T    pad_lnx1_05;         // 0xCC97_2014
    IOMUX_CTRL_LNX1_PAD_LNX1_06_O24A0_T    pad_lnx1_06;         // 0xCC97_2018
    IOMUX_CTRL_LNX1_PAD_LNX1_07_O24A0_T    pad_lnx1_07;         // 0xCC97_201C
    IOMUX_CTRL_LNX1_PAD_LNX1_08_O24A0_T    pad_lnx1_08;         // 0xCC97_2020
    IOMUX_CTRL_LNX1_PAD_LNX1_09_O24A0_T    pad_lnx1_09;         // 0xCC97_2024
    IOMUX_CTRL_LNX1_PAD_LNX1_10_O24A0_T    pad_lnx1_10;         // 0xCC97_2028
    IOMUX_CTRL_LNX1_PAD_LNX1_11_O24A0_T    pad_lnx1_11;         // 0xCC97_202C
    UINT32                             _rsvd_00[52];            // 0xCC97_2030 ~ 0xCC97_20FC
    IOMUX_CTRL_LNX1_PAD_LNX1_64_O24A0_T    pad_lnx1_64;         // 0xCC97_2100
    IOMUX_CTRL_LNX1_PAD_LNX1_65_O24A0_T    pad_lnx1_65;         // 0xCC97_2104
    IOMUX_CTRL_LNX1_PAD_LNX1_66_O24A0_T    pad_lnx1_66;         // 0xCC97_2108
    IOMUX_CTRL_LNX1_PAD_LNX1_67_O24A0_T    pad_lnx1_67;         // 0xCC97_210C
    IOMUX_CTRL_LNX1_PAD_LNX1_68_O24A0_T    pad_lnx1_68;         // 0xCC97_2110
    IOMUX_CTRL_LNX1_PAD_LNX1_69_O24A0_T    pad_lnx1_69;         // 0xCC97_2114
    IOMUX_CTRL_LNX1_PAD_LNX1_70_O24A0_T    pad_lnx1_70;         // 0xCC97_2118
}IOMUX_CTRL_LNX1_REG_O24A0_T;
/* 19 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _IOMUX_CTRL_LNX1_REG_H_

/* from 'O24_CTOP_PAD_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

