#ifndef _IOMUX_CTRL_VD1_M23A0_REG_H_
#define _IOMUX_CTRL_VD1_M23A0_REG_H_

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
    0x0    pad_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_epi_vst__ds0      :  1,    //      0
    reg_pad_epi_vst__ds1      :  1,    //      1
    reg_pad_epi_vst__ds2      :  1,    //      2
    reg_pad_epi_vst__ds3      :  1,    //      3
    reg_pad_epi_vst__pd       :  1,    //      4
    reg_pad_epi_vst__pu       :  1,    //      5
    reg_pad_epi_vst__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_epi_eo__ds0       :  1,    //      8
    reg_pad_epi_eo__ds1       :  1,    //      9
    reg_pad_epi_eo__ds2       :  1,    //     10
    reg_pad_epi_eo__ds3       :  1,    //     11
    reg_pad_epi_eo__pd        :  1,    //     12
    reg_pad_epi_eo__pu        :  1,    //     13
    reg_pad_epi_eo__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_epi_gclk__ds0     :  1,    //     16
    reg_pad_epi_gclk__ds1     :  1,    //     17
    reg_pad_epi_gclk__ds2     :  1,    //     18
    reg_pad_epi_gclk__ds3     :  1,    //     19
    reg_pad_epi_gclk__pd      :  1,    //     20
    reg_pad_epi_gclk__pu      :  1,    //     21
    reg_pad_epi_gclk__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_epi_mclk__ds0     :  1,    //     24
    reg_pad_epi_mclk__ds1     :  1,    //     25
    reg_pad_epi_mclk__ds2     :  1,    //     26
    reg_pad_epi_mclk__ds3     :  1,    //     27
    reg_pad_epi_mclk__pd      :  1,    //     28
    reg_pad_epi_mclk__pu      :  1,    //     29
    reg_pad_epi_mclk__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm1__ds0         :  1,    //      0
    reg_pad_pwm1__ds1         :  1,    //      1
    reg_pad_pwm1__ds2         :  1,    //      2
    reg_pad_pwm1__ds3         :  1,    //      3
    reg_pad_pwm1__pd          :  1,    //      4
    reg_pad_pwm1__pu          :  1,    //      5
    reg_pad_pwm1__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pwm0__ds0         :  1,    //      8
    reg_pad_pwm0__ds1         :  1,    //      9
    reg_pad_pwm0__ds2         :  1,    //     10
    reg_pad_pwm0__ds3         :  1,    //     11
    reg_pad_pwm0__pd          :  1,    //     12
    reg_pad_pwm0__pu          :  1,    //     13
    reg_pad_pwm0__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_epi_gclk2__ds0    :  1,    //     16
    reg_pad_epi_gclk2__ds1    :  1,    //     17
    reg_pad_epi_gclk2__ds2    :  1,    //     18
    reg_pad_epi_gclk2__ds3    :  1,    //     19
    reg_pad_epi_gclk2__pd     :  1,    //     20
    reg_pad_epi_gclk2__pu     :  1,    //     21
    reg_pad_epi_gclk2__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_epi_mclk2__ds0    :  1,    //     24
    reg_pad_epi_mclk2__ds1    :  1,    //     25
    reg_pad_epi_mclk2__ds2    :  1,    //     26
    reg_pad_epi_mclk2__ds3    :  1,    //     27
    reg_pad_epi_mclk2__pd     :  1,    //     28
    reg_pad_epi_mclk2__pu     :  1,    //     29
    reg_pad_epi_mclk2__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_do0__ds0      :  1,    //      0
    reg_pad_spi_do0__ds1      :  1,    //      1
    reg_pad_spi_do0__ds2      :  1,    //      2
    reg_pad_spi_do0__ds3      :  1,    //      3
    reg_pad_spi_do0__pd       :  1,    //      4
    reg_pad_spi_do0__pu       :  1,    //      5
    reg_pad_spi_do0__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_di0__ds0      :  1,    //      8
    reg_pad_spi_di0__ds1      :  1,    //      9
    reg_pad_spi_di0__ds2      :  1,    //     10
    reg_pad_spi_di0__ds3      :  1,    //     11
    reg_pad_spi_di0__pd       :  1,    //     12
    reg_pad_spi_di0__pu       :  1,    //     13
    reg_pad_spi_di0__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_cs0__ds0      :  1,    //     16
    reg_pad_spi_cs0__ds1      :  1,    //     17
    reg_pad_spi_cs0__ds2      :  1,    //     18
    reg_pad_spi_cs0__ds3      :  1,    //     19
    reg_pad_spi_cs0__pd       :  1,    //     20
    reg_pad_spi_cs0__pu       :  1,    //     21
    reg_pad_spi_cs0__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pwm2__ds0         :  1,    //     24
    reg_pad_pwm2__ds1         :  1,    //     25
    reg_pad_pwm2__ds2         :  1,    //     26
    reg_pad_pwm2__ds3         :  1,    //     27
    reg_pad_pwm2__pd          :  1,    //     28
    reg_pad_pwm2__pu          :  1,    //     29
    reg_pad_pwm2__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch0__ds0    :  1,    //      0
    reg_pad_aec_lrch0__ds1    :  1,    //      1
    reg_pad_aec_lrch0__ds2    :  1,    //      2
    reg_pad_aec_lrch0__ds3    :  1,    //      3
    reg_pad_aec_lrch0__pd     :  1,    //      4
    reg_pad_aec_lrch0__pu     :  1,    //      5
    reg_pad_aec_lrch0__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_iec958out__ds0    :  1,    //      8
    reg_pad_iec958out__ds1    :  1,    //      9
    reg_pad_iec958out__ds2    :  1,    //     10
    reg_pad_iec958out__ds3    :  1,    //     11
    reg_pad_iec958out__pd     :  1,    //     12
    reg_pad_iec958out__pu     :  1,    //     13
    reg_pad_iec958out__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_boot_mode__ds0    :  1,    //     16
    reg_pad_boot_mode__ds1    :  1,    //     17
    reg_pad_boot_mode__ds2    :  1,    //     18
    reg_pad_boot_mode__ds3    :  1,    //     19
    reg_pad_boot_mode__pd     :  1,    //     20
    reg_pad_boot_mode__pu     :  1,    //     21
    reg_pad_boot_mode__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_sclk0__ds0    :  1,    //     24
    reg_pad_spi_sclk0__ds1    :  1,    //     25
    reg_pad_spi_sclk0__ds2    :  1,    //     26
    reg_pad_spi_sclk0__ds3    :  1,    //     27
    reg_pad_spi_sclk0__pd     :  1,    //     28
    reg_pad_spi_sclk0__pu     :  1,    //     29
    reg_pad_spi_sclk0__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_vd104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacsck__ds0       :  1,    //      0
    reg_pad_dacsck__ds1       :  1,    //      1
    reg_pad_dacsck__ds2       :  1,    //      2
    reg_pad_dacsck__ds3       :  1,    //      3
    reg_pad_dacsck__pd        :  1,    //      4
    reg_pad_dacsck__pu        :  1,    //      5
    reg_pad_dacsck__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_daclrck__ds0      :  1,    //      8
    reg_pad_daclrck__ds1      :  1,    //      9
    reg_pad_daclrck__ds2      :  1,    //     10
    reg_pad_daclrck__ds3      :  1,    //     11
    reg_pad_daclrck__pd       :  1,    //     12
    reg_pad_daclrck__pu       :  1,    //     13
    reg_pad_daclrck__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_daclrch__ds0      :  1,    //     16
    reg_pad_daclrch__ds1      :  1,    //     17
    reg_pad_daclrch__ds2      :  1,    //     18
    reg_pad_daclrch__ds3      :  1,    //     19
    reg_pad_daclrch__pd       :  1,    //     20
    reg_pad_daclrch__pu       :  1,    //     21
    reg_pad_daclrch__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_aec_lrch1__ds0    :  1,    //     24
    reg_pad_aec_lrch1__ds1    :  1,    //     25
    reg_pad_aec_lrch1__ds2    :  1,    //     26
    reg_pad_aec_lrch1__ds3    :  1,    //     27
    reg_pad_aec_lrch1__pd     :  1,    //     28
    reg_pad_aec_lrch1__pu     :  1,    //     29
    reg_pad_aec_lrch1__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD104_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_vd105 ''
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
    reg_pad_ld_vs_out0__ds0   :  1,    //     16
    reg_pad_ld_vs_out0__ds1   :  1,    //     17
    reg_pad_ld_vs_out0__ds2   :  1,    //     18
    reg_pad_ld_vs_out0__ds3   :  1,    //     19
    reg_pad_ld_vs_out0__pd    :  1,    //     20
    reg_pad_ld_vs_out0__pu    :  1,    //     21
    reg_pad_ld_vs_out0__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dacslrch__ds0     :  1,    //     24
    reg_pad_dacslrch__ds1     :  1,    //     25
    reg_pad_dacslrch__ds2     :  1,    //     26
    reg_pad_dacslrch__ds3     :  1,    //     27
    reg_pad_dacslrch__pd      :  1,    //     28
    reg_pad_dacslrch__pu      :  1,    //     29
    reg_pad_dacslrch__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD105_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_vd106 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl0__ds0         :  1,    //      0
    reg_pad_scl0__ds1         :  1,    //      1
    reg_pad_scl0__ds2         :  1,    //      2
    reg_pad_scl0__ds3         :  1,    //      3
    reg_pad_scl0__pd          :  1,    //      4
    reg_pad_scl0__pu          :  1,    //      5
    reg_pad_scl0__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim1_sclk__ds0    :  1,    //      8
    reg_pad_dim1_sclk__ds1    :  1,    //      9
    reg_pad_dim1_sclk__ds2    :  1,    //     10
    reg_pad_dim1_sclk__ds3    :  1,    //     11
    reg_pad_dim1_sclk__pd     :  1,    //     12
    reg_pad_dim1_sclk__pu     :  1,    //     13
    reg_pad_dim1_sclk__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim1_mosi__ds0    :  1,    //     16
    reg_pad_dim1_mosi__ds1    :  1,    //     17
    reg_pad_dim1_mosi__ds2    :  1,    //     18
    reg_pad_dim1_mosi__ds3    :  1,    //     19
    reg_pad_dim1_mosi__pd     :  1,    //     20
    reg_pad_dim1_mosi__pu     :  1,    //     21
    reg_pad_dim1_mosi__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ld_vs_out1__ds0   :  1,    //     24
    reg_pad_ld_vs_out1__ds1   :  1,    //     25
    reg_pad_ld_vs_out1__ds2   :  1,    //     26
    reg_pad_ld_vs_out1__ds3   :  1,    //     27
    reg_pad_ld_vs_out1__pd    :  1,    //     28
    reg_pad_ld_vs_out1__pu    :  1,    //     29
    reg_pad_ld_vs_out1__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD106_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_vd107 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl2__ds0         :  1,    //      0
    reg_pad_scl2__ds1         :  1,    //      1
    reg_pad_scl2__ds2         :  1,    //      2
    reg_pad_scl2__ds3         :  1,    //      3
    reg_pad_scl2__pd          :  1,    //      4
    reg_pad_scl2__pu          :  1,    //      5
    reg_pad_scl2__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda1__ds0         :  1,    //      8
    reg_pad_sda1__ds1         :  1,    //      9
    reg_pad_sda1__ds2         :  1,    //     10
    reg_pad_sda1__ds3         :  1,    //     11
    reg_pad_sda1__pd          :  1,    //     12
    reg_pad_sda1__pu          :  1,    //     13
    reg_pad_sda1__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl1__ds0         :  1,    //     16
    reg_pad_scl1__ds1         :  1,    //     17
    reg_pad_scl1__ds2         :  1,    //     18
    reg_pad_scl1__ds3         :  1,    //     19
    reg_pad_scl1__pd          :  1,    //     20
    reg_pad_scl1__pu          :  1,    //     21
    reg_pad_scl1__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda0__ds0         :  1,    //     24
    reg_pad_sda0__ds1         :  1,    //     25
    reg_pad_sda0__ds2         :  1,    //     26
    reg_pad_sda0__ds3         :  1,    //     27
    reg_pad_sda0__pd          :  1,    //     28
    reg_pad_sda0__pu          :  1,    //     29
    reg_pad_sda0__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD107_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_vd108 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio00__ds0       :  1,    //      0
    reg_pad_gpio00__ds1       :  1,    //      1
    reg_pad_gpio00__ds2       :  1,    //      2
    reg_pad_gpio00__ds3       :  1,    //      3
    reg_pad_gpio00__pd        :  1,    //      4
    reg_pad_gpio00__pu        :  1,    //      5
    reg_pad_gpio00__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_uart1_txd__ds0    :  1,    //      8
    reg_pad_uart1_txd__ds1    :  1,    //      9
    reg_pad_uart1_txd__ds2    :  1,    //     10
    reg_pad_uart1_txd__ds3    :  1,    //     11
    reg_pad_uart1_txd__pd     :  1,    //     12
    reg_pad_uart1_txd__pu     :  1,    //     13
    reg_pad_uart1_txd__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_uart1_rxd__ds0    :  1,    //     16
    reg_pad_uart1_rxd__ds1    :  1,    //     17
    reg_pad_uart1_rxd__ds2    :  1,    //     18
    reg_pad_uart1_rxd__ds3    :  1,    //     19
    reg_pad_uart1_rxd__pd     :  1,    //     20
    reg_pad_uart1_rxd__pu     :  1,    //     21
    reg_pad_uart1_rxd__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda2__ds0         :  1,    //     24
    reg_pad_sda2__ds1         :  1,    //     25
    reg_pad_sda2__ds2         :  1,    //     26
    reg_pad_sda2__ds3         :  1,    //     27
    reg_pad_sda2__pd          :  1,    //     28
    reg_pad_sda2__pu          :  1,    //     29
    reg_pad_sda2__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD108_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_vd109 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio04__ds0       :  1,    //      0
    reg_pad_gpio04__ds1       :  1,    //      1
    reg_pad_gpio04__ds2       :  1,    //      2
    reg_pad_gpio04__ds3       :  1,    //      3
    reg_pad_gpio04__pd        :  1,    //      4
    reg_pad_gpio04__pu        :  1,    //      5
    reg_pad_gpio04__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio03__ds0       :  1,    //      8
    reg_pad_gpio03__ds1       :  1,    //      9
    reg_pad_gpio03__ds2       :  1,    //     10
    reg_pad_gpio03__ds3       :  1,    //     11
    reg_pad_gpio03__pd        :  1,    //     12
    reg_pad_gpio03__pu        :  1,    //     13
    reg_pad_gpio03__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio02__ds0       :  1,    //     16
    reg_pad_gpio02__ds1       :  1,    //     17
    reg_pad_gpio02__ds2       :  1,    //     18
    reg_pad_gpio02__ds3       :  1,    //     19
    reg_pad_gpio02__pd        :  1,    //     20
    reg_pad_gpio02__pu        :  1,    //     21
    reg_pad_gpio02__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio01__ds0       :  1,    //     24
    reg_pad_gpio01__ds1       :  1,    //     25
    reg_pad_gpio01__ds2       :  1,    //     26
    reg_pad_gpio01__ds3       :  1,    //     27
    reg_pad_gpio01__pd        :  1,    //     28
    reg_pad_gpio01__pu        :  1,    //     29
    reg_pad_gpio01__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD109_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x28    pad_vd110 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio08__ds0       :  1,    //      0
    reg_pad_gpio08__ds1       :  1,    //      1
    reg_pad_gpio08__ds2       :  1,    //      2
    reg_pad_gpio08__ds3       :  1,    //      3
    reg_pad_gpio08__pd        :  1,    //      4
    reg_pad_gpio08__pu        :  1,    //      5
    reg_pad_gpio08__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio07__ds0       :  1,    //      8
    reg_pad_gpio07__ds1       :  1,    //      9
    reg_pad_gpio07__ds2       :  1,    //     10
    reg_pad_gpio07__ds3       :  1,    //     11
    reg_pad_gpio07__pd        :  1,    //     12
    reg_pad_gpio07__pu        :  1,    //     13
    reg_pad_gpio07__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio06__ds0       :  1,    //     16
    reg_pad_gpio06__ds1       :  1,    //     17
    reg_pad_gpio06__ds2       :  1,    //     18
    reg_pad_gpio06__ds3       :  1,    //     19
    reg_pad_gpio06__pd        :  1,    //     20
    reg_pad_gpio06__pu        :  1,    //     21
    reg_pad_gpio06__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio05__ds0       :  1,    //     24
    reg_pad_gpio05__ds1       :  1,    //     25
    reg_pad_gpio05__ds2       :  1,    //     26
    reg_pad_gpio05__ds3       :  1,    //     27
    reg_pad_gpio05__pd        :  1,    //     28
    reg_pad_gpio05__pu        :  1,    //     29
    reg_pad_gpio05__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD110_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C    pad_vd111 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio12__ds0       :  1,    //      0
    reg_pad_gpio12__ds1       :  1,    //      1
    reg_pad_gpio12__ds2       :  1,    //      2
    reg_pad_gpio12__ds3       :  1,    //      3
    reg_pad_gpio12__pd        :  1,    //      4
    reg_pad_gpio12__pu        :  1,    //      5
    reg_pad_gpio12__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio11__ds0       :  1,    //      8
    reg_pad_gpio11__ds1       :  1,    //      9
    reg_pad_gpio11__ds2       :  1,    //     10
    reg_pad_gpio11__ds3       :  1,    //     11
    reg_pad_gpio11__pd        :  1,    //     12
    reg_pad_gpio11__pu        :  1,    //     13
    reg_pad_gpio11__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio10__ds0       :  1,    //     16
    reg_pad_gpio10__ds1       :  1,    //     17
    reg_pad_gpio10__ds2       :  1,    //     18
    reg_pad_gpio10__ds3       :  1,    //     19
    reg_pad_gpio10__pd        :  1,    //     20
    reg_pad_gpio10__pu        :  1,    //     21
    reg_pad_gpio10__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio09__ds0       :  1,    //     24
    reg_pad_gpio09__ds1       :  1,    //     25
    reg_pad_gpio09__ds2       :  1,    //     26
    reg_pad_gpio09__ds3       :  1,    //     27
    reg_pad_gpio09__pd        :  1,    //     28
    reg_pad_gpio09__pu        :  1,    //     29
    reg_pad_gpio09__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD111_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x30    pad_vd112 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio15__ds0       :  1,    //      0
    reg_pad_gpio15__ds1       :  1,    //      1
    reg_pad_gpio15__ds2       :  1,    //      2
    reg_pad_gpio15__ds3       :  1,    //      3
    reg_pad_gpio15__pd        :  1,    //      4
    reg_pad_gpio15__pu        :  1,    //      5
    reg_pad_gpio15__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio14__ds0       :  1,    //      8
    reg_pad_gpio14__ds1       :  1,    //      9
    reg_pad_gpio14__ds2       :  1,    //     10
    reg_pad_gpio14__ds3       :  1,    //     11
    reg_pad_gpio14__pd        :  1,    //     12
    reg_pad_gpio14__pu        :  1,    //     13
    reg_pad_gpio14__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio13__ds0       :  1,    //     16
    reg_pad_gpio13__ds1       :  1,    //     17
    reg_pad_gpio13__ds2       :  1,    //     18
    reg_pad_gpio13__ds3       :  1,    //     19
    reg_pad_gpio13__pd        :  1,    //     20
    reg_pad_gpio13__pu        :  1,    //     21
    reg_pad_gpio13__st        :  1,    //     22
                              :  9;    //  31:23 reserved
}IOMUX_CTRL_VD1_PAD_VD112_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x38    pad_vd114 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 30,    //  29: 0 reserved
    reg_isol_apb_en           :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD1_PAD_VD114_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_vd164 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm1_mux_sel      :  4,    //   3: 0
    reg_pad_pwm0_mux_sel      :  4,    //   7: 4
    reg_pad_epi_gclk2_mux_sel :  4,    //  11: 8
    reg_pad_epi_mclk2_mux_sel :  4,    //  15:12
    reg_pad_epi_vst_mux_sel   :  4,    //  19:16
    reg_pad_epi_eo_mux_sel    :  4,    //  23:20
    reg_pad_epi_gclk_mux_sel  :  4,    //  27:24
    reg_pad_epi_mclk_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD164_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_vd165 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch0_mux_sel :  4,    //   3: 0
    reg_pad_iec958out_mux_sel :  4,    //   7: 4
    reg_pad_boot_mode_mux_sel :  4,    //  11: 8
    reg_pad_spi_sclk0_mux_sel :  4,    //  15:12
    reg_pad_spi_do0_mux_sel   :  4,    //  19:16
    reg_pad_spi_di0_mux_sel   :  4,    //  23:20
    reg_pad_spi_cs0_mux_sel   :  4,    //  27:24
    reg_pad_pwm2_mux_sel      :  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD165_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_vd166 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_sclk_mux_sel :  4,    //   3: 0
    reg_pad_dim0_mosi_mux_sel :  4,    //   7: 4
    reg_pad_ld_vs_out0_mux_sel:  4,    //  11: 8
    reg_pad_dacslrch_mux_sel  :  4,    //  15:12
    reg_pad_dacsck_mux_sel    :  4,    //  19:16
    reg_pad_daclrck_mux_sel   :  4,    //  23:20
    reg_pad_daclrch_mux_sel   :  4,    //  27:24
    reg_pad_aec_lrch1_mux_sel :  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD166_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_vd167 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl2_mux_sel      :  4,    //   3: 0
    reg_pad_sda1_mux_sel      :  4,    //   7: 4
    reg_pad_scl1_mux_sel      :  4,    //  11: 8
    reg_pad_sda0_mux_sel      :  4,    //  15:12
    reg_pad_scl0_mux_sel      :  4,    //  19:16
    reg_pad_dim1_sclk_mux_sel :  4,    //  23:20
    reg_pad_dim1_mosi_mux_sel :  4,    //  27:24
    reg_pad_ld_vs_out1_mux_sel:  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD167_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_vd168 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio04_mux_sel    :  4,    //   3: 0
    reg_pad_gpio03_mux_sel    :  4,    //   7: 4
    reg_pad_gpio02_mux_sel    :  4,    //  11: 8
    reg_pad_gpio01_mux_sel    :  4,    //  15:12
    reg_pad_gpio00_mux_sel    :  4,    //  19:16
    reg_pad_uart1_txd_mux_sel :  4,    //  23:20
    reg_pad_uart1_rxd_mux_sel :  4,    //  27:24
    reg_pad_sda2_mux_sel      :  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD168_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x114    pad_vd169 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio12_mux_sel    :  4,    //   3: 0
    reg_pad_gpio11_mux_sel    :  4,    //   7: 4
    reg_pad_gpio10_mux_sel    :  4,    //  11: 8
    reg_pad_gpio09_mux_sel    :  4,    //  15:12
    reg_pad_gpio08_mux_sel    :  4,    //  19:16
    reg_pad_gpio07_mux_sel    :  4,    //  23:20
    reg_pad_gpio06_mux_sel    :  4,    //  27:24
    reg_pad_gpio05_mux_sel    :  4;    //  31:28
}IOMUX_CTRL_VD1_PAD_VD169_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x118    pad_vd170 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio15_mux_sel    :  4,    //   3: 0
    reg_pad_gpio14_mux_sel    :  4,    //   7: 4
    reg_pad_gpio13_mux_sel    :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}IOMUX_CTRL_VD1_PAD_VD170_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_VD1_PAD_VD100_M23A0_T     pad_vd100  ;             // 0x0
    IOMUX_CTRL_VD1_PAD_VD101_M23A0_T     pad_vd101  ;             // 0x4
    IOMUX_CTRL_VD1_PAD_VD102_M23A0_T     pad_vd102  ;             // 0x8
    IOMUX_CTRL_VD1_PAD_VD103_M23A0_T     pad_vd103  ;             // 0xC
    IOMUX_CTRL_VD1_PAD_VD104_M23A0_T     pad_vd104  ;             // 0x10
    IOMUX_CTRL_VD1_PAD_VD105_M23A0_T     pad_vd105  ;             // 0x14
    IOMUX_CTRL_VD1_PAD_VD106_M23A0_T     pad_vd106  ;             // 0x18
    IOMUX_CTRL_VD1_PAD_VD107_M23A0_T     pad_vd107  ;             // 0x1C
    IOMUX_CTRL_VD1_PAD_VD108_M23A0_T     pad_vd108  ;             // 0x20
    IOMUX_CTRL_VD1_PAD_VD109_M23A0_T     pad_vd109  ;             // 0x24
    IOMUX_CTRL_VD1_PAD_VD110_M23A0_T     pad_vd110  ;             // 0x28
    IOMUX_CTRL_VD1_PAD_VD111_M23A0_T     pad_vd111  ;             // 0x2C
    IOMUX_CTRL_VD1_PAD_VD112_M23A0_T     pad_vd112  ;             // 0x30
    UINT32                             _rsvd_00[1];             // 0x34
    IOMUX_CTRL_VD1_PAD_VD114_M23A0_T     pad_vd114  ;             // 0x38
    UINT32                             _rsvd_01[49];            // 0x3C ~ 0xFC
    IOMUX_CTRL_VD1_PAD_VD164_M23A0_T     pad_vd164  ;             // 0x100
    IOMUX_CTRL_VD1_PAD_VD165_M23A0_T     pad_vd165  ;             // 0x104
    IOMUX_CTRL_VD1_PAD_VD166_M23A0_T     pad_vd166  ;             // 0x108
    IOMUX_CTRL_VD1_PAD_VD167_M23A0_T     pad_vd167  ;             // 0x10C
    IOMUX_CTRL_VD1_PAD_VD168_M23A0_T     pad_vd168  ;             // 0x110
    IOMUX_CTRL_VD1_PAD_VD169_M23A0_T     pad_vd169  ;             // 0x114
    IOMUX_CTRL_VD1_PAD_VD170_M23A0_T     pad_vd170  ;             // 0x118
}IOMUX_CTRL_VD1_REG_M23A0_T;
/* 21 regs */

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

#define IOMUX_CTRL_VD1_PAD_VD100_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define IOMUX_CTRL_VD1_PAD_VD101_M23A0_T_OFF                  (BASEADDRESS+0x0004)
#define IOMUX_CTRL_VD1_PAD_VD102_M23A0_T_OFF                  (BASEADDRESS+0x0008)
#define IOMUX_CTRL_VD1_PAD_VD103_M23A0_T_OFF                  (BASEADDRESS+0x000C)
#define IOMUX_CTRL_VD1_PAD_VD104_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define IOMUX_CTRL_VD1_PAD_VD105_M23A0_T_OFF                  (BASEADDRESS+0x0014)
#define IOMUX_CTRL_VD1_PAD_VD106_M23A0_T_OFF                  (BASEADDRESS+0x0018)
#define IOMUX_CTRL_VD1_PAD_VD107_M23A0_T_OFF                  (BASEADDRESS+0x001C)
#define IOMUX_CTRL_VD1_PAD_VD108_M23A0_T_OFF                  (BASEADDRESS+0x0020)
#define IOMUX_CTRL_VD1_PAD_VD109_M23A0_T_OFF                  (BASEADDRESS+0x0024)
#define IOMUX_CTRL_VD1_PAD_VD110_M23A0_T_OFF                  (BASEADDRESS+0x0028)
#define IOMUX_CTRL_VD1_PAD_VD111_M23A0_T_OFF                  (BASEADDRESS+0x002C)
#define IOMUX_CTRL_VD1_PAD_VD112_M23A0_T_OFF                  (BASEADDRESS+0x0030)
#define IOMUX_CTRL_VD1_PAD_VD114_M23A0_T_OFF                  (BASEADDRESS+0x0038)
#define IOMUX_CTRL_VD1_PAD_VD164_M23A0_T_OFF                  (BASEADDRESS+0x0100)
#define IOMUX_CTRL_VD1_PAD_VD165_M23A0_T_OFF                  (BASEADDRESS+0x0104)
#define IOMUX_CTRL_VD1_PAD_VD166_M23A0_T_OFF                  (BASEADDRESS+0x0108)
#define IOMUX_CTRL_VD1_PAD_VD167_M23A0_T_OFF                  (BASEADDRESS+0x010C)
#define IOMUX_CTRL_VD1_PAD_VD168_M23A0_T_OFF                  (BASEADDRESS+0x0110)
#define IOMUX_CTRL_VD1_PAD_VD169_M23A0_T_OFF                  (BASEADDRESS+0x0114)
#define IOMUX_CTRL_VD1_PAD_VD170_M23A0_T_OFF                  (BASEADDRESS+0x0118)

/*-----------------------------------------------------------------------------------------
    0x0    pad_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_epi_vst__ds0: 1;    //      0
    UINT32 reg_pad_epi_vst__ds1: 1;    //      1
    UINT32 reg_pad_epi_vst__ds2: 1;    //      2
    UINT32 reg_pad_epi_vst__ds3: 1;    //      3
    UINT32 reg_pad_epi_vst__pd:  1;    //      4
    UINT32 reg_pad_epi_vst__pu:  1;    //      5
    UINT32 reg_pad_epi_vst__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_epi_eo__ds0:  1;    //      8
    UINT32 reg_pad_epi_eo__ds1:  1;    //      9
    UINT32 reg_pad_epi_eo__ds2:  1;    //     10
    UINT32 reg_pad_epi_eo__ds3:  1;    //     11
    UINT32 reg_pad_epi_eo__pd :  1;    //     12
    UINT32 reg_pad_epi_eo__pu :  1;    //     13
    UINT32 reg_pad_epi_eo__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_epi_gclk__ds0: 1;    //    16
    UINT32 reg_pad_epi_gclk__ds1: 1;    //    17
    UINT32 reg_pad_epi_gclk__ds2: 1;    //    18
    UINT32 reg_pad_epi_gclk__ds3: 1;    //    19
    UINT32 reg_pad_epi_gclk__pd: 1;    //     20
    UINT32 reg_pad_epi_gclk__pu: 1;    //     21
    UINT32 reg_pad_epi_gclk__st: 1;    //     22
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
}IOMUX_CTRL_VD1_PAD_VD100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pwm1__ds0  :  1;    //      0
    UINT32 reg_pad_pwm1__ds1  :  1;    //      1
    UINT32 reg_pad_pwm1__ds2  :  1;    //      2
    UINT32 reg_pad_pwm1__ds3  :  1;    //      3
    UINT32 reg_pad_pwm1__pd   :  1;    //      4
    UINT32 reg_pad_pwm1__pu   :  1;    //      5
    UINT32 reg_pad_pwm1__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_pwm0__ds0  :  1;    //      8
    UINT32 reg_pad_pwm0__ds1  :  1;    //      9
    UINT32 reg_pad_pwm0__ds2  :  1;    //     10
    UINT32 reg_pad_pwm0__ds3  :  1;    //     11
    UINT32 reg_pad_pwm0__pd   :  1;    //     12
    UINT32 reg_pad_pwm0__pu   :  1;    //     13
    UINT32 reg_pad_pwm0__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_epi_gclk2__ds0: 1;    //   16
    UINT32 reg_pad_epi_gclk2__ds1: 1;    //   17
    UINT32 reg_pad_epi_gclk2__ds2: 1;    //   18
    UINT32 reg_pad_epi_gclk2__ds3: 1;    //   19
    UINT32 reg_pad_epi_gclk2__pd: 1;    //    20
    UINT32 reg_pad_epi_gclk2__pu: 1;    //    21
    UINT32 reg_pad_epi_gclk2__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_epi_mclk2__ds0: 1;    //   24
    UINT32 reg_pad_epi_mclk2__ds1: 1;    //   25
    UINT32 reg_pad_epi_mclk2__ds2: 1;    //   26
    UINT32 reg_pad_epi_mclk2__ds3: 1;    //   27
    UINT32 reg_pad_epi_mclk2__pd: 1;    //    28
    UINT32 reg_pad_epi_mclk2__pu: 1;    //    29
    UINT32 reg_pad_epi_mclk2__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_do0__ds0: 1;    //      0
    UINT32 reg_pad_spi_do0__ds1: 1;    //      1
    UINT32 reg_pad_spi_do0__ds2: 1;    //      2
    UINT32 reg_pad_spi_do0__ds3: 1;    //      3
    UINT32 reg_pad_spi_do0__pd:  1;    //      4
    UINT32 reg_pad_spi_do0__pu:  1;    //      5
    UINT32 reg_pad_spi_do0__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_spi_di0__ds0: 1;    //      8
    UINT32 reg_pad_spi_di0__ds1: 1;    //      9
    UINT32 reg_pad_spi_di0__ds2: 1;    //     10
    UINT32 reg_pad_spi_di0__ds3: 1;    //     11
    UINT32 reg_pad_spi_di0__pd:  1;    //     12
    UINT32 reg_pad_spi_di0__pu:  1;    //     13
    UINT32 reg_pad_spi_di0__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_spi_cs0__ds0: 1;    //     16
    UINT32 reg_pad_spi_cs0__ds1: 1;    //     17
    UINT32 reg_pad_spi_cs0__ds2: 1;    //     18
    UINT32 reg_pad_spi_cs0__ds3: 1;    //     19
    UINT32 reg_pad_spi_cs0__pd:  1;    //     20
    UINT32 reg_pad_spi_cs0__pu:  1;    //     21
    UINT32 reg_pad_spi_cs0__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_pwm2__ds0  :  1;    //     24
    UINT32 reg_pad_pwm2__ds1  :  1;    //     25
    UINT32 reg_pad_pwm2__ds2  :  1;    //     26
    UINT32 reg_pad_pwm2__ds3  :  1;    //     27
    UINT32 reg_pad_pwm2__pd   :  1;    //     28
    UINT32 reg_pad_pwm2__pu   :  1;    //     29
    UINT32 reg_pad_pwm2__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_aec_lrch0__ds0: 1;    //    0
    UINT32 reg_pad_aec_lrch0__ds1: 1;    //    1
    UINT32 reg_pad_aec_lrch0__ds2: 1;    //    2
    UINT32 reg_pad_aec_lrch0__ds3: 1;    //    3
    UINT32 reg_pad_aec_lrch0__pd: 1;    //     4
    UINT32 reg_pad_aec_lrch0__pu: 1;    //     5
    UINT32 reg_pad_aec_lrch0__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_iec958out__ds0: 1;    //    8
    UINT32 reg_pad_iec958out__ds1: 1;    //    9
    UINT32 reg_pad_iec958out__ds2: 1;    //   10
    UINT32 reg_pad_iec958out__ds3: 1;    //   11
    UINT32 reg_pad_iec958out__pd: 1;    //    12
    UINT32 reg_pad_iec958out__pu: 1;    //    13
    UINT32 reg_pad_iec958out__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_boot_mode__ds0: 1;    //   16
    UINT32 reg_pad_boot_mode__ds1: 1;    //   17
    UINT32 reg_pad_boot_mode__ds2: 1;    //   18
    UINT32 reg_pad_boot_mode__ds3: 1;    //   19
    UINT32 reg_pad_boot_mode__pd: 1;    //    20
    UINT32 reg_pad_boot_mode__pu: 1;    //    21
    UINT32 reg_pad_boot_mode__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_spi_sclk0__ds0: 1;    //   24
    UINT32 reg_pad_spi_sclk0__ds1: 1;    //   25
    UINT32 reg_pad_spi_sclk0__ds2: 1;    //   26
    UINT32 reg_pad_spi_sclk0__ds3: 1;    //   27
    UINT32 reg_pad_spi_sclk0__pd: 1;    //    28
    UINT32 reg_pad_spi_sclk0__pu: 1;    //    29
    UINT32 reg_pad_spi_sclk0__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_vd104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dacsck__ds0:  1;    //      0
    UINT32 reg_pad_dacsck__ds1:  1;    //      1
    UINT32 reg_pad_dacsck__ds2:  1;    //      2
    UINT32 reg_pad_dacsck__ds3:  1;    //      3
    UINT32 reg_pad_dacsck__pd :  1;    //      4
    UINT32 reg_pad_dacsck__pu :  1;    //      5
    UINT32 reg_pad_dacsck__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_daclrck__ds0: 1;    //      8
    UINT32 reg_pad_daclrck__ds1: 1;    //      9
    UINT32 reg_pad_daclrck__ds2: 1;    //     10
    UINT32 reg_pad_daclrck__ds3: 1;    //     11
    UINT32 reg_pad_daclrck__pd:  1;    //     12
    UINT32 reg_pad_daclrck__pu:  1;    //     13
    UINT32 reg_pad_daclrck__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_daclrch__ds0: 1;    //     16
    UINT32 reg_pad_daclrch__ds1: 1;    //     17
    UINT32 reg_pad_daclrch__ds2: 1;    //     18
    UINT32 reg_pad_daclrch__ds3: 1;    //     19
    UINT32 reg_pad_daclrch__pd:  1;    //     20
    UINT32 reg_pad_daclrch__pu:  1;    //     21
    UINT32 reg_pad_daclrch__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_aec_lrch1__ds0: 1;    //   24
    UINT32 reg_pad_aec_lrch1__ds1: 1;    //   25
    UINT32 reg_pad_aec_lrch1__ds2: 1;    //   26
    UINT32 reg_pad_aec_lrch1__ds3: 1;    //   27
    UINT32 reg_pad_aec_lrch1__pd: 1;    //    28
    UINT32 reg_pad_aec_lrch1__pu: 1;    //    29
    UINT32 reg_pad_aec_lrch1__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD104_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_vd105 ''
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
    UINT32 reg_pad_ld_vs_out0__ds0: 1;    //  16
    UINT32 reg_pad_ld_vs_out0__ds1: 1;    //  17
    UINT32 reg_pad_ld_vs_out0__ds2: 1;    //  18
    UINT32 reg_pad_ld_vs_out0__ds3: 1;    //  19
    UINT32 reg_pad_ld_vs_out0__pd: 1;    //   20
    UINT32 reg_pad_ld_vs_out0__pu: 1;    //   21
    UINT32 reg_pad_ld_vs_out0__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dacslrch__ds0: 1;    //    24
    UINT32 reg_pad_dacslrch__ds1: 1;    //    25
    UINT32 reg_pad_dacslrch__ds2: 1;    //    26
    UINT32 reg_pad_dacslrch__ds3: 1;    //    27
    UINT32 reg_pad_dacslrch__pd: 1;    //     28
    UINT32 reg_pad_dacslrch__pu: 1;    //     29
    UINT32 reg_pad_dacslrch__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD105_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_vd106 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl0__ds0  :  1;    //      0
    UINT32 reg_pad_scl0__ds1  :  1;    //      1
    UINT32 reg_pad_scl0__ds2  :  1;    //      2
    UINT32 reg_pad_scl0__ds3  :  1;    //      3
    UINT32 reg_pad_scl0__pd   :  1;    //      4
    UINT32 reg_pad_scl0__pu   :  1;    //      5
    UINT32 reg_pad_scl0__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_dim1_sclk__ds0: 1;    //    8
    UINT32 reg_pad_dim1_sclk__ds1: 1;    //    9
    UINT32 reg_pad_dim1_sclk__ds2: 1;    //   10
    UINT32 reg_pad_dim1_sclk__ds3: 1;    //   11
    UINT32 reg_pad_dim1_sclk__pd: 1;    //    12
    UINT32 reg_pad_dim1_sclk__pu: 1;    //    13
    UINT32 reg_pad_dim1_sclk__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dim1_mosi__ds0: 1;    //   16
    UINT32 reg_pad_dim1_mosi__ds1: 1;    //   17
    UINT32 reg_pad_dim1_mosi__ds2: 1;    //   18
    UINT32 reg_pad_dim1_mosi__ds3: 1;    //   19
    UINT32 reg_pad_dim1_mosi__pd: 1;    //    20
    UINT32 reg_pad_dim1_mosi__pu: 1;    //    21
    UINT32 reg_pad_dim1_mosi__st: 1;    //    22
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
}IOMUX_CTRL_VD1_PAD_VD106_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_vd107 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl2__ds0  :  1;    //      0
    UINT32 reg_pad_scl2__ds1  :  1;    //      1
    UINT32 reg_pad_scl2__ds2  :  1;    //      2
    UINT32 reg_pad_scl2__ds3  :  1;    //      3
    UINT32 reg_pad_scl2__pd   :  1;    //      4
    UINT32 reg_pad_scl2__pu   :  1;    //      5
    UINT32 reg_pad_scl2__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda1__ds0  :  1;    //      8
    UINT32 reg_pad_sda1__ds1  :  1;    //      9
    UINT32 reg_pad_sda1__ds2  :  1;    //     10
    UINT32 reg_pad_sda1__ds3  :  1;    //     11
    UINT32 reg_pad_sda1__pd   :  1;    //     12
    UINT32 reg_pad_sda1__pu   :  1;    //     13
    UINT32 reg_pad_sda1__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl1__ds0  :  1;    //     16
    UINT32 reg_pad_scl1__ds1  :  1;    //     17
    UINT32 reg_pad_scl1__ds2  :  1;    //     18
    UINT32 reg_pad_scl1__ds3  :  1;    //     19
    UINT32 reg_pad_scl1__pd   :  1;    //     20
    UINT32 reg_pad_scl1__pu   :  1;    //     21
    UINT32 reg_pad_scl1__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda0__ds0  :  1;    //     24
    UINT32 reg_pad_sda0__ds1  :  1;    //     25
    UINT32 reg_pad_sda0__ds2  :  1;    //     26
    UINT32 reg_pad_sda0__ds3  :  1;    //     27
    UINT32 reg_pad_sda0__pd   :  1;    //     28
    UINT32 reg_pad_sda0__pu   :  1;    //     29
    UINT32 reg_pad_sda0__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD107_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_vd108 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio00__ds0:  1;    //      0
    UINT32 reg_pad_gpio00__ds1:  1;    //      1
    UINT32 reg_pad_gpio00__ds2:  1;    //      2
    UINT32 reg_pad_gpio00__ds3:  1;    //      3
    UINT32 reg_pad_gpio00__pd :  1;    //      4
    UINT32 reg_pad_gpio00__pu :  1;    //      5
    UINT32 reg_pad_gpio00__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_uart1_txd__ds0: 1;    //    8
    UINT32 reg_pad_uart1_txd__ds1: 1;    //    9
    UINT32 reg_pad_uart1_txd__ds2: 1;    //   10
    UINT32 reg_pad_uart1_txd__ds3: 1;    //   11
    UINT32 reg_pad_uart1_txd__pd: 1;    //    12
    UINT32 reg_pad_uart1_txd__pu: 1;    //    13
    UINT32 reg_pad_uart1_txd__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_uart1_rxd__ds0: 1;    //   16
    UINT32 reg_pad_uart1_rxd__ds1: 1;    //   17
    UINT32 reg_pad_uart1_rxd__ds2: 1;    //   18
    UINT32 reg_pad_uart1_rxd__ds3: 1;    //   19
    UINT32 reg_pad_uart1_rxd__pd: 1;    //    20
    UINT32 reg_pad_uart1_rxd__pu: 1;    //    21
    UINT32 reg_pad_uart1_rxd__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda2__ds0  :  1;    //     24
    UINT32 reg_pad_sda2__ds1  :  1;    //     25
    UINT32 reg_pad_sda2__ds2  :  1;    //     26
    UINT32 reg_pad_sda2__ds3  :  1;    //     27
    UINT32 reg_pad_sda2__pd   :  1;    //     28
    UINT32 reg_pad_sda2__pu   :  1;    //     29
    UINT32 reg_pad_sda2__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD108_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_vd109 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio04__ds0:  1;    //      0
    UINT32 reg_pad_gpio04__ds1:  1;    //      1
    UINT32 reg_pad_gpio04__ds2:  1;    //      2
    UINT32 reg_pad_gpio04__ds3:  1;    //      3
    UINT32 reg_pad_gpio04__pd :  1;    //      4
    UINT32 reg_pad_gpio04__pu :  1;    //      5
    UINT32 reg_pad_gpio04__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio03__ds0:  1;    //      8
    UINT32 reg_pad_gpio03__ds1:  1;    //      9
    UINT32 reg_pad_gpio03__ds2:  1;    //     10
    UINT32 reg_pad_gpio03__ds3:  1;    //     11
    UINT32 reg_pad_gpio03__pd :  1;    //     12
    UINT32 reg_pad_gpio03__pu :  1;    //     13
    UINT32 reg_pad_gpio03__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio02__ds0:  1;    //     16
    UINT32 reg_pad_gpio02__ds1:  1;    //     17
    UINT32 reg_pad_gpio02__ds2:  1;    //     18
    UINT32 reg_pad_gpio02__ds3:  1;    //     19
    UINT32 reg_pad_gpio02__pd :  1;    //     20
    UINT32 reg_pad_gpio02__pu :  1;    //     21
    UINT32 reg_pad_gpio02__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio01__ds0:  1;    //     24
    UINT32 reg_pad_gpio01__ds1:  1;    //     25
    UINT32 reg_pad_gpio01__ds2:  1;    //     26
    UINT32 reg_pad_gpio01__ds3:  1;    //     27
    UINT32 reg_pad_gpio01__pd :  1;    //     28
    UINT32 reg_pad_gpio01__pu :  1;    //     29
    UINT32 reg_pad_gpio01__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD109_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x28    pad_vd110 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio08__ds0:  1;    //      0
    UINT32 reg_pad_gpio08__ds1:  1;    //      1
    UINT32 reg_pad_gpio08__ds2:  1;    //      2
    UINT32 reg_pad_gpio08__ds3:  1;    //      3
    UINT32 reg_pad_gpio08__pd :  1;    //      4
    UINT32 reg_pad_gpio08__pu :  1;    //      5
    UINT32 reg_pad_gpio08__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio07__ds0:  1;    //      8
    UINT32 reg_pad_gpio07__ds1:  1;    //      9
    UINT32 reg_pad_gpio07__ds2:  1;    //     10
    UINT32 reg_pad_gpio07__ds3:  1;    //     11
    UINT32 reg_pad_gpio07__pd :  1;    //     12
    UINT32 reg_pad_gpio07__pu :  1;    //     13
    UINT32 reg_pad_gpio07__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio06__ds0:  1;    //     16
    UINT32 reg_pad_gpio06__ds1:  1;    //     17
    UINT32 reg_pad_gpio06__ds2:  1;    //     18
    UINT32 reg_pad_gpio06__ds3:  1;    //     19
    UINT32 reg_pad_gpio06__pd :  1;    //     20
    UINT32 reg_pad_gpio06__pu :  1;    //     21
    UINT32 reg_pad_gpio06__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio05__ds0:  1;    //     24
    UINT32 reg_pad_gpio05__ds1:  1;    //     25
    UINT32 reg_pad_gpio05__ds2:  1;    //     26
    UINT32 reg_pad_gpio05__ds3:  1;    //     27
    UINT32 reg_pad_gpio05__pd :  1;    //     28
    UINT32 reg_pad_gpio05__pu :  1;    //     29
    UINT32 reg_pad_gpio05__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD110_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C    pad_vd111 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio12__ds0:  1;    //      0
    UINT32 reg_pad_gpio12__ds1:  1;    //      1
    UINT32 reg_pad_gpio12__ds2:  1;    //      2
    UINT32 reg_pad_gpio12__ds3:  1;    //      3
    UINT32 reg_pad_gpio12__pd :  1;    //      4
    UINT32 reg_pad_gpio12__pu :  1;    //      5
    UINT32 reg_pad_gpio12__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio11__ds0:  1;    //      8
    UINT32 reg_pad_gpio11__ds1:  1;    //      9
    UINT32 reg_pad_gpio11__ds2:  1;    //     10
    UINT32 reg_pad_gpio11__ds3:  1;    //     11
    UINT32 reg_pad_gpio11__pd :  1;    //     12
    UINT32 reg_pad_gpio11__pu :  1;    //     13
    UINT32 reg_pad_gpio11__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio10__ds0:  1;    //     16
    UINT32 reg_pad_gpio10__ds1:  1;    //     17
    UINT32 reg_pad_gpio10__ds2:  1;    //     18
    UINT32 reg_pad_gpio10__ds3:  1;    //     19
    UINT32 reg_pad_gpio10__pd :  1;    //     20
    UINT32 reg_pad_gpio10__pu :  1;    //     21
    UINT32 reg_pad_gpio10__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio09__ds0:  1;    //     24
    UINT32 reg_pad_gpio09__ds1:  1;    //     25
    UINT32 reg_pad_gpio09__ds2:  1;    //     26
    UINT32 reg_pad_gpio09__ds3:  1;    //     27
    UINT32 reg_pad_gpio09__pd :  1;    //     28
    UINT32 reg_pad_gpio09__pu :  1;    //     29
    UINT32 reg_pad_gpio09__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD111_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x30    pad_vd112 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio15__ds0:  1;    //      0
    UINT32 reg_pad_gpio15__ds1:  1;    //      1
    UINT32 reg_pad_gpio15__ds2:  1;    //      2
    UINT32 reg_pad_gpio15__ds3:  1;    //      3
    UINT32 reg_pad_gpio15__pd :  1;    //      4
    UINT32 reg_pad_gpio15__pu :  1;    //      5
    UINT32 reg_pad_gpio15__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio14__ds0:  1;    //      8
    UINT32 reg_pad_gpio14__ds1:  1;    //      9
    UINT32 reg_pad_gpio14__ds2:  1;    //     10
    UINT32 reg_pad_gpio14__ds3:  1;    //     11
    UINT32 reg_pad_gpio14__pd :  1;    //     12
    UINT32 reg_pad_gpio14__pu :  1;    //     13
    UINT32 reg_pad_gpio14__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio13__ds0:  1;    //     16
    UINT32 reg_pad_gpio13__ds1:  1;    //     17
    UINT32 reg_pad_gpio13__ds2:  1;    //     18
    UINT32 reg_pad_gpio13__ds3:  1;    //     19
    UINT32 reg_pad_gpio13__pd :  1;    //     20
    UINT32 reg_pad_gpio13__pu :  1;    //     21
    UINT32 reg_pad_gpio13__st :  1;    //     22
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD112_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x38    pad_vd114 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 30;    //  29: 0 reserved
    UINT32 reg_isol_apb_en    :  1;    //     30
    UINT32 resvd01            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD114_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_vd164 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pwm1_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_pwm0_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_epi_gclk2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_epi_mclk2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_epi_vst_mux_sel: 4;    //  19:16
    UINT32 reg_pad_epi_eo_mux_sel: 4;    //  23:20
    UINT32 reg_pad_epi_gclk_mux_sel: 4;    //  27:24
    UINT32 reg_pad_epi_mclk_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD164_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_vd165 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_aec_lrch0_mux_sel: 4;    //  3:0
    UINT32 reg_pad_iec958out_mux_sel: 4;    //  7:4
    UINT32 reg_pad_boot_mode_mux_sel: 4;    //  11:8
    UINT32 reg_pad_spi_sclk0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_spi_do0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_spi_di0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_spi_cs0_mux_sel: 4;    //  27:24
    UINT32 reg_pad_pwm2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD165_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_vd166 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim0_sclk_mux_sel: 4;    //  3:0
    UINT32 reg_pad_dim0_mosi_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ld_vs_out0_mux_sel: 4;    //  11:8
    UINT32 reg_pad_dacslrch_mux_sel: 4;    //  15:12
    UINT32 reg_pad_dacsck_mux_sel: 4;    //  19:16
    UINT32 reg_pad_daclrck_mux_sel: 4;    //  23:20
    UINT32 reg_pad_daclrch_mux_sel: 4;    //  27:24
    UINT32 reg_pad_aec_lrch1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD166_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_vd167 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl2_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_sda1_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_scl1_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_sda0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_scl0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_dim1_sclk_mux_sel: 4;    //  23:20
    UINT32 reg_pad_dim1_mosi_mux_sel: 4;    //  27:24
    UINT32 reg_pad_ld_vs_out1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD167_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_vd168 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio04_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio03_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio02_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio01_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio00_mux_sel: 4;    //  19:16
    UINT32 reg_pad_uart1_txd_mux_sel: 4;    //  23:20
    UINT32 reg_pad_uart1_rxd_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD168_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x114    pad_vd169 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio12_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio11_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio10_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio09_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio08_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio07_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio06_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio05_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD1_PAD_VD169_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x118    pad_vd170 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio15_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio14_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio13_mux_sel: 4;    //  11:8
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}IOMUX_CTRL_VD1_PAD_VD170_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_VD1_PAD_VD100_M23A0_T     pad_vd100  ;             // 0x0
    IOMUX_CTRL_VD1_PAD_VD101_M23A0_T     pad_vd101  ;             // 0x4
    IOMUX_CTRL_VD1_PAD_VD102_M23A0_T     pad_vd102  ;             // 0x8
    IOMUX_CTRL_VD1_PAD_VD103_M23A0_T     pad_vd103  ;             // 0xC
    IOMUX_CTRL_VD1_PAD_VD104_M23A0_T     pad_vd104  ;             // 0x10
    IOMUX_CTRL_VD1_PAD_VD105_M23A0_T     pad_vd105  ;             // 0x14
    IOMUX_CTRL_VD1_PAD_VD106_M23A0_T     pad_vd106  ;             // 0x18
    IOMUX_CTRL_VD1_PAD_VD107_M23A0_T     pad_vd107  ;             // 0x1C
    IOMUX_CTRL_VD1_PAD_VD108_M23A0_T     pad_vd108  ;             // 0x20
    IOMUX_CTRL_VD1_PAD_VD109_M23A0_T     pad_vd109  ;             // 0x24
    IOMUX_CTRL_VD1_PAD_VD110_M23A0_T     pad_vd110  ;             // 0x28
    IOMUX_CTRL_VD1_PAD_VD111_M23A0_T     pad_vd111  ;             // 0x2C
    IOMUX_CTRL_VD1_PAD_VD112_M23A0_T     pad_vd112  ;             // 0x30
    UINT32                             _rsvd_00[1];             // 0x34
    IOMUX_CTRL_VD1_PAD_VD114_M23A0_T     pad_vd114  ;             // 0x38
    UINT32                             _rsvd_01[49];            // 0x3C ~ 0xFC
    IOMUX_CTRL_VD1_PAD_VD164_M23A0_T     pad_vd164  ;             // 0x100
    IOMUX_CTRL_VD1_PAD_VD165_M23A0_T     pad_vd165  ;             // 0x104
    IOMUX_CTRL_VD1_PAD_VD166_M23A0_T     pad_vd166  ;             // 0x108
    IOMUX_CTRL_VD1_PAD_VD167_M23A0_T     pad_vd167  ;             // 0x10C
    IOMUX_CTRL_VD1_PAD_VD168_M23A0_T     pad_vd168  ;             // 0x110
    IOMUX_CTRL_VD1_PAD_VD169_M23A0_T     pad_vd169  ;             // 0x114
    IOMUX_CTRL_VD1_PAD_VD170_M23A0_T     pad_vd170  ;             // 0x118
}IOMUX_CTRL_VD1_REG_M23A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_PAD_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

