#ifndef _FUNC_IOMUX_LGSR_REG_H_
#define _FUNC_IOMUX_LGSR_REG_H_

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
    0xCC3F_4000    pad_lgsr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim3_mosi__ds0    :  1,    //      0
    reg_pad_dim3_mosi__ds1    :  1,    //      1
    reg_pad_dim3_mosi__ds2    :  1,    //      2
    reg_pad_dim3_mosi__ds3    :  1,    //      3
    reg_pad_dim3_mosi__pd     :  1,    //      4
    reg_pad_dim3_mosi__pu     :  1,    //      5
    reg_pad_dim3_mosi__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ld_vs_out3__ds0   :  1,    //      8
    reg_pad_ld_vs_out3__ds1   :  1,    //      9
    reg_pad_ld_vs_out3__ds2   :  1,    //     10
    reg_pad_ld_vs_out3__ds3   :  1,    //     11
    reg_pad_ld_vs_out3__pd    :  1,    //     12
    reg_pad_ld_vs_out3__pu    :  1,    //     13
    reg_pad_ld_vs_out3__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dim2_sclk__ds0    :  1,    //     16
    reg_pad_dim2_sclk__ds1    :  1,    //     17
    reg_pad_dim2_sclk__ds2    :  1,    //     18
    reg_pad_dim2_sclk__ds3    :  1,    //     19
    reg_pad_dim2_sclk__pd     :  1,    //     20
    reg_pad_dim2_sclk__pu     :  1,    //     21
    reg_pad_dim2_sclk__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim2_mosi__ds0    :  1,    //     24
    reg_pad_dim2_mosi__ds1    :  1,    //     25
    reg_pad_dim2_mosi__ds2    :  1,    //     26
    reg_pad_dim2_mosi__ds3    :  1,    //     27
    reg_pad_dim2_mosi__pd     :  1,    //     28
    reg_pad_dim2_mosi__pu     :  1,    //     29
    reg_pad_dim2_mosi__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4004    pad_lgsr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_cs0__ds0      :  1,    //      0
    reg_pad_spi_cs0__ds1      :  1,    //      1
    reg_pad_spi_cs0__ds2      :  1,    //      2
    reg_pad_spi_cs0__ds3      :  1,    //      3
    reg_pad_spi_cs0__pd       :  1,    //      4
    reg_pad_spi_cs0__pu       :  1,    //      5
    reg_pad_spi_cs0__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda0__ds0         :  1,    //      8
    reg_pad_sda0__ds1         :  1,    //      9
    reg_pad_sda0__ds2         :  1,    //     10
    reg_pad_sda0__ds3         :  1,    //     11
    reg_pad_sda0__pd          :  1,    //     12
    reg_pad_sda0__pu          :  1,    //     13
    reg_pad_sda0__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl0__ds0         :  1,    //     16
    reg_pad_scl0__ds1         :  1,    //     17
    reg_pad_scl0__ds2         :  1,    //     18
    reg_pad_scl0__ds3         :  1,    //     19
    reg_pad_scl0__pd          :  1,    //     20
    reg_pad_scl0__pu          :  1,    //     21
    reg_pad_scl0__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim3_sclk__ds0    :  1,    //     24
    reg_pad_dim3_sclk__ds1    :  1,    //     25
    reg_pad_dim3_sclk__ds2    :  1,    //     26
    reg_pad_dim3_sclk__ds3    :  1,    //     27
    reg_pad_dim3_sclk__pd     :  1,    //     28
    reg_pad_dim3_sclk__pu     :  1,    //     29
    reg_pad_dim3_sclk__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4008    pad_lgsr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_cs1__ds0      :  1,    //      0
    reg_pad_spi_cs1__ds1      :  1,    //      1
    reg_pad_spi_cs1__ds2      :  1,    //      2
    reg_pad_spi_cs1__ds3      :  1,    //      3
    reg_pad_spi_cs1__pd       :  1,    //      4
    reg_pad_spi_cs1__pu       :  1,    //      5
    reg_pad_spi_cs1__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_sclk0__ds0    :  1,    //      8
    reg_pad_spi_sclk0__ds1    :  1,    //      9
    reg_pad_spi_sclk0__ds2    :  1,    //     10
    reg_pad_spi_sclk0__ds3    :  1,    //     11
    reg_pad_spi_sclk0__pd     :  1,    //     12
    reg_pad_spi_sclk0__pu     :  1,    //     13
    reg_pad_spi_sclk0__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_do0__ds0      :  1,    //     16
    reg_pad_spi_do0__ds1      :  1,    //     17
    reg_pad_spi_do0__ds2      :  1,    //     18
    reg_pad_spi_do0__ds3      :  1,    //     19
    reg_pad_spi_do0__pd       :  1,    //     20
    reg_pad_spi_do0__pu       :  1,    //     21
    reg_pad_spi_do0__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_di0__ds0      :  1,    //     24
    reg_pad_spi_di0__ds1      :  1,    //     25
    reg_pad_spi_di0__ds2      :  1,    //     26
    reg_pad_spi_di0__ds3      :  1,    //     27
    reg_pad_spi_di0__pd       :  1,    //     28
    reg_pad_spi_di0__pu       :  1,    //     29
    reg_pad_spi_di0__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_400C    pad_lgsr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl1__ds0         :  1,    //      0
    reg_pad_scl1__ds1         :  1,    //      1
    reg_pad_scl1__ds2         :  1,    //      2
    reg_pad_scl1__ds3         :  1,    //      3
    reg_pad_scl1__pd          :  1,    //      4
    reg_pad_scl1__pu          :  1,    //      5
    reg_pad_scl1__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_spi_do1__ds0      :  1,    //      8
    reg_pad_spi_do1__ds1      :  1,    //      9
    reg_pad_spi_do1__ds2      :  1,    //     10
    reg_pad_spi_do1__ds3      :  1,    //     11
    reg_pad_spi_do1__pd       :  1,    //     12
    reg_pad_spi_do1__pu       :  1,    //     13
    reg_pad_spi_do1__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_spi_sclk1__ds0    :  1,    //     16
    reg_pad_spi_sclk1__ds1    :  1,    //     17
    reg_pad_spi_sclk1__ds2    :  1,    //     18
    reg_pad_spi_sclk1__ds3    :  1,    //     19
    reg_pad_spi_sclk1__pd     :  1,    //     20
    reg_pad_spi_sclk1__pu     :  1,    //     21
    reg_pad_spi_sclk1__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_spi_di1__ds0      :  1,    //     24
    reg_pad_spi_di1__ds1      :  1,    //     25
    reg_pad_spi_di1__ds2      :  1,    //     26
    reg_pad_spi_di1__ds3      :  1,    //     27
    reg_pad_spi_di1__pd       :  1,    //     28
    reg_pad_spi_di1__pu       :  1,    //     29
    reg_pad_spi_di1__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4010    pad_lgsr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl3__ds0         :  1,    //      0
    reg_pad_scl3__ds1         :  1,    //      1
    reg_pad_scl3__ds2         :  1,    //      2
    reg_pad_scl3__ds3         :  1,    //      3
    reg_pad_scl3__pd          :  1,    //      4
    reg_pad_scl3__pu          :  1,    //      5
    reg_pad_scl3__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda2__ds0         :  1,    //      8
    reg_pad_sda2__ds1         :  1,    //      9
    reg_pad_sda2__ds2         :  1,    //     10
    reg_pad_sda2__ds3         :  1,    //     11
    reg_pad_sda2__pd          :  1,    //     12
    reg_pad_sda2__pu          :  1,    //     13
    reg_pad_sda2__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl2__ds0         :  1,    //     16
    reg_pad_scl2__ds1         :  1,    //     17
    reg_pad_scl2__ds2         :  1,    //     18
    reg_pad_scl2__ds3         :  1,    //     19
    reg_pad_scl2__pd          :  1,    //     20
    reg_pad_scl2__pu          :  1,    //     21
    reg_pad_scl2__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda1__ds0         :  1,    //     24
    reg_pad_sda1__ds1         :  1,    //     25
    reg_pad_sda1__ds2         :  1,    //     26
    reg_pad_sda1__ds3         :  1,    //     27
    reg_pad_sda1__pd          :  1,    //     28
    reg_pad_sda1__pu          :  1,    //     29
    reg_pad_sda1__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4014    pad_lgsr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl5__ds0         :  1,    //      0
    reg_pad_scl5__ds1         :  1,    //      1
    reg_pad_scl5__ds2         :  1,    //      2
    reg_pad_scl5__ds3         :  1,    //      3
    reg_pad_scl5__pd          :  1,    //      4
    reg_pad_scl5__pu          :  1,    //      5
    reg_pad_scl5__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda4__ds0         :  1,    //      8
    reg_pad_sda4__ds1         :  1,    //      9
    reg_pad_sda4__ds2         :  1,    //     10
    reg_pad_sda4__ds3         :  1,    //     11
    reg_pad_sda4__pd          :  1,    //     12
    reg_pad_sda4__pu          :  1,    //     13
    reg_pad_sda4__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl4__ds0         :  1,    //     16
    reg_pad_scl4__ds1         :  1,    //     17
    reg_pad_scl4__ds2         :  1,    //     18
    reg_pad_scl4__ds3         :  1,    //     19
    reg_pad_scl4__pd          :  1,    //     20
    reg_pad_scl4__pu          :  1,    //     21
    reg_pad_scl4__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda3__ds0         :  1,    //     24
    reg_pad_sda3__ds1         :  1,    //     25
    reg_pad_sda3__ds2         :  1,    //     26
    reg_pad_sda3__ds3         :  1,    //     27
    reg_pad_sda3__pd          :  1,    //     28
    reg_pad_sda3__pu          :  1,    //     29
    reg_pad_sda3__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4018    pad_lgsr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio1__ds0        :  1,    //      0
    reg_pad_gpio1__ds1        :  1,    //      1
    reg_pad_gpio1__ds2        :  1,    //      2
    reg_pad_gpio1__ds3        :  1,    //      3
    reg_pad_gpio1__pd         :  1,    //      4
    reg_pad_gpio1__pu         :  1,    //      5
    reg_pad_gpio1__st         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio0__ds0        :  1,    //      8
    reg_pad_gpio0__ds1        :  1,    //      9
    reg_pad_gpio0__ds2        :  1,    //     10
    reg_pad_gpio0__ds3        :  1,    //     11
    reg_pad_gpio0__pd         :  1,    //     12
    reg_pad_gpio0__pu         :  1,    //     13
    reg_pad_gpio0__st         :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_boot_mode__ds0    :  1,    //     16
    reg_pad_boot_mode__ds1    :  1,    //     17
    reg_pad_boot_mode__ds2    :  1,    //     18
    reg_pad_boot_mode__ds3    :  1,    //     19
    reg_pad_boot_mode__pd     :  1,    //     20
    reg_pad_boot_mode__pu     :  1,    //     21
    reg_pad_boot_mode__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda5__ds0         :  1,    //     24
    reg_pad_sda5__ds1         :  1,    //     25
    reg_pad_sda5__ds2         :  1,    //     26
    reg_pad_sda5__ds3         :  1,    //     27
    reg_pad_sda5__pd          :  1,    //     28
    reg_pad_sda5__pu          :  1,    //     29
    reg_pad_sda5__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_401C    pad_lgsr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio5__ds0        :  1,    //      0
    reg_pad_gpio5__ds1        :  1,    //      1
    reg_pad_gpio5__ds2        :  1,    //      2
    reg_pad_gpio5__ds3        :  1,    //      3
    reg_pad_gpio5__pd         :  1,    //      4
    reg_pad_gpio5__pu         :  1,    //      5
    reg_pad_gpio5__st         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio4__ds0        :  1,    //      8
    reg_pad_gpio4__ds1        :  1,    //      9
    reg_pad_gpio4__ds2        :  1,    //     10
    reg_pad_gpio4__ds3        :  1,    //     11
    reg_pad_gpio4__pd         :  1,    //     12
    reg_pad_gpio4__pu         :  1,    //     13
    reg_pad_gpio4__st         :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio3__ds0        :  1,    //     16
    reg_pad_gpio3__ds1        :  1,    //     17
    reg_pad_gpio3__ds2        :  1,    //     18
    reg_pad_gpio3__ds3        :  1,    //     19
    reg_pad_gpio3__pd         :  1,    //     20
    reg_pad_gpio3__pu         :  1,    //     21
    reg_pad_gpio3__st         :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio2__ds0        :  1,    //     24
    reg_pad_gpio2__ds1        :  1,    //     25
    reg_pad_gpio2__ds2        :  1,    //     26
    reg_pad_gpio2__ds3        :  1,    //     27
    reg_pad_gpio2__pd         :  1,    //     28
    reg_pad_gpio2__pu         :  1,    //     29
    reg_pad_gpio2__st         :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4020    pad_lgsr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio9__ds0        :  1,    //      0
    reg_pad_gpio9__ds1        :  1,    //      1
    reg_pad_gpio9__ds2        :  1,    //      2
    reg_pad_gpio9__ds3        :  1,    //      3
    reg_pad_gpio9__pd         :  1,    //      4
    reg_pad_gpio9__pu         :  1,    //      5
    reg_pad_gpio9__st         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio8__ds0        :  1,    //      8
    reg_pad_gpio8__ds1        :  1,    //      9
    reg_pad_gpio8__ds2        :  1,    //     10
    reg_pad_gpio8__ds3        :  1,    //     11
    reg_pad_gpio8__pd         :  1,    //     12
    reg_pad_gpio8__pu         :  1,    //     13
    reg_pad_gpio8__st         :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio7__ds0        :  1,    //     16
    reg_pad_gpio7__ds1        :  1,    //     17
    reg_pad_gpio7__ds2        :  1,    //     18
    reg_pad_gpio7__ds3        :  1,    //     19
    reg_pad_gpio7__pd         :  1,    //     20
    reg_pad_gpio7__pu         :  1,    //     21
    reg_pad_gpio7__st         :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio6__ds0        :  1,    //     24
    reg_pad_gpio6__ds1        :  1,    //     25
    reg_pad_gpio6__ds2        :  1,    //     26
    reg_pad_gpio6__ds3        :  1,    //     27
    reg_pad_gpio6__pd         :  1,    //     28
    reg_pad_gpio6__pu         :  1,    //     29
    reg_pad_gpio6__st         :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4024    pad_lgsr09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio13__ds0       :  1,    //      0
    reg_pad_gpio13__ds1       :  1,    //      1
    reg_pad_gpio13__ds2       :  1,    //      2
    reg_pad_gpio13__ds3       :  1,    //      3
    reg_pad_gpio13__pd        :  1,    //      4
    reg_pad_gpio13__pu        :  1,    //      5
    reg_pad_gpio13__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio12__ds0       :  1,    //      8
    reg_pad_gpio12__ds1       :  1,    //      9
    reg_pad_gpio12__ds2       :  1,    //     10
    reg_pad_gpio12__ds3       :  1,    //     11
    reg_pad_gpio12__pd        :  1,    //     12
    reg_pad_gpio12__pu        :  1,    //     13
    reg_pad_gpio12__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio11__ds0       :  1,    //     16
    reg_pad_gpio11__ds1       :  1,    //     17
    reg_pad_gpio11__ds2       :  1,    //     18
    reg_pad_gpio11__ds3       :  1,    //     19
    reg_pad_gpio11__pd        :  1,    //     20
    reg_pad_gpio11__pu        :  1,    //     21
    reg_pad_gpio11__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio10__ds0       :  1,    //     24
    reg_pad_gpio10__ds1       :  1,    //     25
    reg_pad_gpio10__ds2       :  1,    //     26
    reg_pad_gpio10__ds3       :  1,    //     27
    reg_pad_gpio10__pd        :  1,    //     28
    reg_pad_gpio10__pu        :  1,    //     29
    reg_pad_gpio10__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4028    pad_lgsr10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio16__ds0       :  1,    //      0
    reg_pad_gpio16__ds1       :  1,    //      1
    reg_pad_gpio16__ds2       :  1,    //      2
    reg_pad_gpio16__ds3       :  1,    //      3
    reg_pad_gpio16__pd        :  1,    //      4
    reg_pad_gpio16__pu        :  1,    //      5
    reg_pad_gpio16__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio15__ds0       :  1,    //      8
    reg_pad_gpio15__ds1       :  1,    //      9
    reg_pad_gpio15__ds2       :  1,    //     10
    reg_pad_gpio15__ds3       :  1,    //     11
    reg_pad_gpio15__pd        :  1,    //     12
    reg_pad_gpio15__pu        :  1,    //     13
    reg_pad_gpio15__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio14__ds0       :  1,    //     16
    reg_pad_gpio14__ds1       :  1,    //     17
    reg_pad_gpio14__ds2       :  1,    //     18
    reg_pad_gpio14__ds3       :  1,    //     19
    reg_pad_gpio14__pd        :  1,    //     20
    reg_pad_gpio14__pu        :  1,    //     21
    reg_pad_gpio14__st        :  1,    //     22
                              :  9;    //  31:23 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4100    pad_lgsr64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_cs0_mux_sel   :  4,    //   3: 0
    reg_pad_sda0_mux_sel      :  4,    //   7: 4
    reg_pad_scl0_mux_sel      :  4,    //  11: 8
    reg_pad_dim3_sclk_mux_sel :  4,    //  15:12
    reg_pad_dim3_mosi_mux_sel :  4,    //  19:16
    reg_pad_ld_vs_out3_mux_sel:  4,    //  23:20
    reg_pad_dim2_sclk_mux_sel :  4,    //  27:24
    reg_pad_dim2_mosi_mux_sel :  4;    //  31:28
}FUNC_IOMUX_LGSR_PAD_LGSR64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4104    pad_lgsr65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl1_mux_sel      :  4,    //   3: 0
    reg_pad_spi_do1_mux_sel   :  4,    //   7: 4
    reg_pad_spi_sclk1_mux_sel :  4,    //  11: 8
    reg_pad_spi_di1_mux_sel   :  4,    //  15:12
    reg_pad_spi_cs1_mux_sel   :  4,    //  19:16
    reg_pad_spi_sclk0_mux_sel :  4,    //  23:20
    reg_pad_spi_do0_mux_sel   :  4,    //  27:24
    reg_pad_spi_di0_mux_sel   :  4;    //  31:28
}FUNC_IOMUX_LGSR_PAD_LGSR65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4108    pad_lgsr66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl5_mux_sel      :  4,    //   3: 0
    reg_pad_sda4_mux_sel      :  4,    //   7: 4
    reg_pad_scl4_mux_sel      :  4,    //  11: 8
    reg_pad_sda3_mux_sel      :  4,    //  15:12
    reg_pad_scl3_mux_sel      :  4,    //  19:16
    reg_pad_sda2_mux_sel      :  4,    //  23:20
    reg_pad_scl2_mux_sel      :  4,    //  27:24
    reg_pad_sda1_mux_sel      :  4;    //  31:28
}FUNC_IOMUX_LGSR_PAD_LGSR66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_410C    pad_lgsr67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio5_mux_sel     :  4,    //   3: 0
    reg_pad_gpio4_mux_sel     :  4,    //   7: 4
    reg_pad_gpio3_mux_sel     :  4,    //  11: 8
    reg_pad_gpio2_mux_sel     :  4,    //  15:12
    reg_pad_gpio1_mux_sel     :  4,    //  19:16
    reg_pad_gpio0_mux_sel     :  4,    //  23:20
    reg_pad_boot_mode_mux_sel :  4,    //  27:24
    reg_pad_sda5_mux_sel      :  4;    //  31:28
}FUNC_IOMUX_LGSR_PAD_LGSR67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4110    pad_lgsr68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio13_mux_sel    :  4,    //   3: 0
    reg_pad_gpio12_mux_sel    :  4,    //   7: 4
    reg_pad_gpio11_mux_sel    :  4,    //  11: 8
    reg_pad_gpio10_mux_sel    :  4,    //  15:12
    reg_pad_gpio9_mux_sel     :  4,    //  19:16
    reg_pad_gpio8_mux_sel     :  4,    //  23:20
    reg_pad_gpio7_mux_sel     :  4,    //  27:24
    reg_pad_gpio6_mux_sel     :  4;    //  31:28
}FUNC_IOMUX_LGSR_PAD_LGSR68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4114    pad_lgsr69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio16_mux_sel    :  4,    //   3: 0
    reg_pad_gpio15_mux_sel    :  4,    //   7: 4
    reg_pad_gpio14_mux_sel    :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}FUNC_IOMUX_LGSR_PAD_LGSR69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_LGSR_PAD_LGSR00_O22A0_T        pad_lgsr00 ;             // 0xCC3F_4000
    FUNC_IOMUX_LGSR_PAD_LGSR01_O22A0_T        pad_lgsr01 ;             // 0xCC3F_4004
    FUNC_IOMUX_LGSR_PAD_LGSR02_O22A0_T        pad_lgsr02 ;             // 0xCC3F_4008
    FUNC_IOMUX_LGSR_PAD_LGSR03_O22A0_T        pad_lgsr03 ;             // 0xCC3F_400C
    FUNC_IOMUX_LGSR_PAD_LGSR04_O22A0_T        pad_lgsr04 ;             // 0xCC3F_4010
    FUNC_IOMUX_LGSR_PAD_LGSR05_O22A0_T        pad_lgsr05 ;             // 0xCC3F_4014
    FUNC_IOMUX_LGSR_PAD_LGSR06_O22A0_T        pad_lgsr06 ;             // 0xCC3F_4018
    FUNC_IOMUX_LGSR_PAD_LGSR07_O22A0_T        pad_lgsr07 ;             // 0xCC3F_401C
    FUNC_IOMUX_LGSR_PAD_LGSR08_O22A0_T        pad_lgsr08 ;             // 0xCC3F_4020
    FUNC_IOMUX_LGSR_PAD_LGSR09_O22A0_T        pad_lgsr09 ;             // 0xCC3F_4024
    FUNC_IOMUX_LGSR_PAD_LGSR10_O22A0_T        pad_lgsr10 ;             // 0xCC3F_4028
    UINT32                             _rsvd_00[53];            // 0xCC3F_402C ~ 0xCC3F_40FC
    FUNC_IOMUX_LGSR_PAD_LGSR64_O22A0_T        pad_lgsr64 ;             // 0xCC3F_4100
    FUNC_IOMUX_LGSR_PAD_LGSR65_O22A0_T        pad_lgsr65 ;             // 0xCC3F_4104
    FUNC_IOMUX_LGSR_PAD_LGSR66_O22A0_T        pad_lgsr66 ;             // 0xCC3F_4108
    FUNC_IOMUX_LGSR_PAD_LGSR67_O22A0_T        pad_lgsr67 ;             // 0xCC3F_410C
    FUNC_IOMUX_LGSR_PAD_LGSR68_O22A0_T        pad_lgsr68 ;             // 0xCC3F_4110
    FUNC_IOMUX_LGSR_PAD_LGSR69_O22A0_T        pad_lgsr69 ;             // 0xCC3F_4114
}FUNC_IOMUX_LGSR_REG_O22A0_T;
/* 17 regs */

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

#define FUNC_IOMUX_LGSR_PAD_LGSR00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define FUNC_IOMUX_LGSR_PAD_LGSR01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define FUNC_IOMUX_LGSR_PAD_LGSR02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define FUNC_IOMUX_LGSR_PAD_LGSR03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define FUNC_IOMUX_LGSR_PAD_LGSR04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define FUNC_IOMUX_LGSR_PAD_LGSR05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define FUNC_IOMUX_LGSR_PAD_LGSR06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define FUNC_IOMUX_LGSR_PAD_LGSR07_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define FUNC_IOMUX_LGSR_PAD_LGSR08_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define FUNC_IOMUX_LGSR_PAD_LGSR09_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define FUNC_IOMUX_LGSR_PAD_LGSR10_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define FUNC_IOMUX_LGSR_PAD_LGSR64_O22A0_T_OFF                     (BASEADDRESS+0x0100)
#define FUNC_IOMUX_LGSR_PAD_LGSR65_O22A0_T_OFF                     (BASEADDRESS+0x0104)
#define FUNC_IOMUX_LGSR_PAD_LGSR66_O22A0_T_OFF                     (BASEADDRESS+0x0108)
#define FUNC_IOMUX_LGSR_PAD_LGSR67_O22A0_T_OFF                     (BASEADDRESS+0x010C)
#define FUNC_IOMUX_LGSR_PAD_LGSR68_O22A0_T_OFF                     (BASEADDRESS+0x0110)
#define FUNC_IOMUX_LGSR_PAD_LGSR69_O22A0_T_OFF                     (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xCC3F_4000    pad_lgsr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim3_mosi__ds0: 1;    //    0
    UINT32 reg_pad_dim3_mosi__ds1: 1;    //    1
    UINT32 reg_pad_dim3_mosi__ds2: 1;    //    2
    UINT32 reg_pad_dim3_mosi__ds3: 1;    //    3
    UINT32 reg_pad_dim3_mosi__pd: 1;    //     4
    UINT32 reg_pad_dim3_mosi__pu: 1;    //     5
    UINT32 reg_pad_dim3_mosi__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ld_vs_out3__ds0: 1;    //   8
    UINT32 reg_pad_ld_vs_out3__ds1: 1;    //   9
    UINT32 reg_pad_ld_vs_out3__ds2: 1;    //  10
    UINT32 reg_pad_ld_vs_out3__ds3: 1;    //  11
    UINT32 reg_pad_ld_vs_out3__pd: 1;    //   12
    UINT32 reg_pad_ld_vs_out3__pu: 1;    //   13
    UINT32 reg_pad_ld_vs_out3__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dim2_sclk__ds0: 1;    //   16
    UINT32 reg_pad_dim2_sclk__ds1: 1;    //   17
    UINT32 reg_pad_dim2_sclk__ds2: 1;    //   18
    UINT32 reg_pad_dim2_sclk__ds3: 1;    //   19
    UINT32 reg_pad_dim2_sclk__pd: 1;    //    20
    UINT32 reg_pad_dim2_sclk__pu: 1;    //    21
    UINT32 reg_pad_dim2_sclk__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dim2_mosi__ds0: 1;    //   24
    UINT32 reg_pad_dim2_mosi__ds1: 1;    //   25
    UINT32 reg_pad_dim2_mosi__ds2: 1;    //   26
    UINT32 reg_pad_dim2_mosi__ds3: 1;    //   27
    UINT32 reg_pad_dim2_mosi__pd: 1;    //    28
    UINT32 reg_pad_dim2_mosi__pu: 1;    //    29
    UINT32 reg_pad_dim2_mosi__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4004    pad_lgsr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_cs0__ds0: 1;    //      0
    UINT32 reg_pad_spi_cs0__ds1: 1;    //      1
    UINT32 reg_pad_spi_cs0__ds2: 1;    //      2
    UINT32 reg_pad_spi_cs0__ds3: 1;    //      3
    UINT32 reg_pad_spi_cs0__pd:  1;    //      4
    UINT32 reg_pad_spi_cs0__pu:  1;    //      5
    UINT32 reg_pad_spi_cs0__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda0__ds0  :  1;    //      8
    UINT32 reg_pad_sda0__ds1  :  1;    //      9
    UINT32 reg_pad_sda0__ds2  :  1;    //     10
    UINT32 reg_pad_sda0__ds3  :  1;    //     11
    UINT32 reg_pad_sda0__pd   :  1;    //     12
    UINT32 reg_pad_sda0__pu   :  1;    //     13
    UINT32 reg_pad_sda0__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl0__ds0  :  1;    //     16
    UINT32 reg_pad_scl0__ds1  :  1;    //     17
    UINT32 reg_pad_scl0__ds2  :  1;    //     18
    UINT32 reg_pad_scl0__ds3  :  1;    //     19
    UINT32 reg_pad_scl0__pd   :  1;    //     20
    UINT32 reg_pad_scl0__pu   :  1;    //     21
    UINT32 reg_pad_scl0__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dim3_sclk__ds0: 1;    //   24
    UINT32 reg_pad_dim3_sclk__ds1: 1;    //   25
    UINT32 reg_pad_dim3_sclk__ds2: 1;    //   26
    UINT32 reg_pad_dim3_sclk__ds3: 1;    //   27
    UINT32 reg_pad_dim3_sclk__pd: 1;    //    28
    UINT32 reg_pad_dim3_sclk__pu: 1;    //    29
    UINT32 reg_pad_dim3_sclk__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4008    pad_lgsr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_cs1__ds0: 1;    //      0
    UINT32 reg_pad_spi_cs1__ds1: 1;    //      1
    UINT32 reg_pad_spi_cs1__ds2: 1;    //      2
    UINT32 reg_pad_spi_cs1__ds3: 1;    //      3
    UINT32 reg_pad_spi_cs1__pd:  1;    //      4
    UINT32 reg_pad_spi_cs1__pu:  1;    //      5
    UINT32 reg_pad_spi_cs1__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_spi_sclk0__ds0: 1;    //    8
    UINT32 reg_pad_spi_sclk0__ds1: 1;    //    9
    UINT32 reg_pad_spi_sclk0__ds2: 1;    //   10
    UINT32 reg_pad_spi_sclk0__ds3: 1;    //   11
    UINT32 reg_pad_spi_sclk0__pd: 1;    //    12
    UINT32 reg_pad_spi_sclk0__pu: 1;    //    13
    UINT32 reg_pad_spi_sclk0__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_spi_do0__ds0: 1;    //     16
    UINT32 reg_pad_spi_do0__ds1: 1;    //     17
    UINT32 reg_pad_spi_do0__ds2: 1;    //     18
    UINT32 reg_pad_spi_do0__ds3: 1;    //     19
    UINT32 reg_pad_spi_do0__pd:  1;    //     20
    UINT32 reg_pad_spi_do0__pu:  1;    //     21
    UINT32 reg_pad_spi_do0__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_spi_di0__ds0: 1;    //     24
    UINT32 reg_pad_spi_di0__ds1: 1;    //     25
    UINT32 reg_pad_spi_di0__ds2: 1;    //     26
    UINT32 reg_pad_spi_di0__ds3: 1;    //     27
    UINT32 reg_pad_spi_di0__pd:  1;    //     28
    UINT32 reg_pad_spi_di0__pu:  1;    //     29
    UINT32 reg_pad_spi_di0__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_400C    pad_lgsr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl1__ds0  :  1;    //      0
    UINT32 reg_pad_scl1__ds1  :  1;    //      1
    UINT32 reg_pad_scl1__ds2  :  1;    //      2
    UINT32 reg_pad_scl1__ds3  :  1;    //      3
    UINT32 reg_pad_scl1__pd   :  1;    //      4
    UINT32 reg_pad_scl1__pu   :  1;    //      5
    UINT32 reg_pad_scl1__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_spi_do1__ds0: 1;    //      8
    UINT32 reg_pad_spi_do1__ds1: 1;    //      9
    UINT32 reg_pad_spi_do1__ds2: 1;    //     10
    UINT32 reg_pad_spi_do1__ds3: 1;    //     11
    UINT32 reg_pad_spi_do1__pd:  1;    //     12
    UINT32 reg_pad_spi_do1__pu:  1;    //     13
    UINT32 reg_pad_spi_do1__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_spi_sclk1__ds0: 1;    //   16
    UINT32 reg_pad_spi_sclk1__ds1: 1;    //   17
    UINT32 reg_pad_spi_sclk1__ds2: 1;    //   18
    UINT32 reg_pad_spi_sclk1__ds3: 1;    //   19
    UINT32 reg_pad_spi_sclk1__pd: 1;    //    20
    UINT32 reg_pad_spi_sclk1__pu: 1;    //    21
    UINT32 reg_pad_spi_sclk1__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_spi_di1__ds0: 1;    //     24
    UINT32 reg_pad_spi_di1__ds1: 1;    //     25
    UINT32 reg_pad_spi_di1__ds2: 1;    //     26
    UINT32 reg_pad_spi_di1__ds3: 1;    //     27
    UINT32 reg_pad_spi_di1__pd:  1;    //     28
    UINT32 reg_pad_spi_di1__pu:  1;    //     29
    UINT32 reg_pad_spi_di1__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4010    pad_lgsr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl3__ds0  :  1;    //      0
    UINT32 reg_pad_scl3__ds1  :  1;    //      1
    UINT32 reg_pad_scl3__ds2  :  1;    //      2
    UINT32 reg_pad_scl3__ds3  :  1;    //      3
    UINT32 reg_pad_scl3__pd   :  1;    //      4
    UINT32 reg_pad_scl3__pu   :  1;    //      5
    UINT32 reg_pad_scl3__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda2__ds0  :  1;    //      8
    UINT32 reg_pad_sda2__ds1  :  1;    //      9
    UINT32 reg_pad_sda2__ds2  :  1;    //     10
    UINT32 reg_pad_sda2__ds3  :  1;    //     11
    UINT32 reg_pad_sda2__pd   :  1;    //     12
    UINT32 reg_pad_sda2__pu   :  1;    //     13
    UINT32 reg_pad_sda2__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl2__ds0  :  1;    //     16
    UINT32 reg_pad_scl2__ds1  :  1;    //     17
    UINT32 reg_pad_scl2__ds2  :  1;    //     18
    UINT32 reg_pad_scl2__ds3  :  1;    //     19
    UINT32 reg_pad_scl2__pd   :  1;    //     20
    UINT32 reg_pad_scl2__pu   :  1;    //     21
    UINT32 reg_pad_scl2__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda1__ds0  :  1;    //     24
    UINT32 reg_pad_sda1__ds1  :  1;    //     25
    UINT32 reg_pad_sda1__ds2  :  1;    //     26
    UINT32 reg_pad_sda1__ds3  :  1;    //     27
    UINT32 reg_pad_sda1__pd   :  1;    //     28
    UINT32 reg_pad_sda1__pu   :  1;    //     29
    UINT32 reg_pad_sda1__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4014    pad_lgsr05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl5__ds0  :  1;    //      0
    UINT32 reg_pad_scl5__ds1  :  1;    //      1
    UINT32 reg_pad_scl5__ds2  :  1;    //      2
    UINT32 reg_pad_scl5__ds3  :  1;    //      3
    UINT32 reg_pad_scl5__pd   :  1;    //      4
    UINT32 reg_pad_scl5__pu   :  1;    //      5
    UINT32 reg_pad_scl5__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda4__ds0  :  1;    //      8
    UINT32 reg_pad_sda4__ds1  :  1;    //      9
    UINT32 reg_pad_sda4__ds2  :  1;    //     10
    UINT32 reg_pad_sda4__ds3  :  1;    //     11
    UINT32 reg_pad_sda4__pd   :  1;    //     12
    UINT32 reg_pad_sda4__pu   :  1;    //     13
    UINT32 reg_pad_sda4__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl4__ds0  :  1;    //     16
    UINT32 reg_pad_scl4__ds1  :  1;    //     17
    UINT32 reg_pad_scl4__ds2  :  1;    //     18
    UINT32 reg_pad_scl4__ds3  :  1;    //     19
    UINT32 reg_pad_scl4__pd   :  1;    //     20
    UINT32 reg_pad_scl4__pu   :  1;    //     21
    UINT32 reg_pad_scl4__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda3__ds0  :  1;    //     24
    UINT32 reg_pad_sda3__ds1  :  1;    //     25
    UINT32 reg_pad_sda3__ds2  :  1;    //     26
    UINT32 reg_pad_sda3__ds3  :  1;    //     27
    UINT32 reg_pad_sda3__pd   :  1;    //     28
    UINT32 reg_pad_sda3__pu   :  1;    //     29
    UINT32 reg_pad_sda3__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4018    pad_lgsr06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio1__ds0 :  1;    //      0
    UINT32 reg_pad_gpio1__ds1 :  1;    //      1
    UINT32 reg_pad_gpio1__ds2 :  1;    //      2
    UINT32 reg_pad_gpio1__ds3 :  1;    //      3
    UINT32 reg_pad_gpio1__pd  :  1;    //      4
    UINT32 reg_pad_gpio1__pu  :  1;    //      5
    UINT32 reg_pad_gpio1__st  :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio0__ds0 :  1;    //      8
    UINT32 reg_pad_gpio0__ds1 :  1;    //      9
    UINT32 reg_pad_gpio0__ds2 :  1;    //     10
    UINT32 reg_pad_gpio0__ds3 :  1;    //     11
    UINT32 reg_pad_gpio0__pd  :  1;    //     12
    UINT32 reg_pad_gpio0__pu  :  1;    //     13
    UINT32 reg_pad_gpio0__st  :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_boot_mode__ds0: 1;    //   16
    UINT32 reg_pad_boot_mode__ds1: 1;    //   17
    UINT32 reg_pad_boot_mode__ds2: 1;    //   18
    UINT32 reg_pad_boot_mode__ds3: 1;    //   19
    UINT32 reg_pad_boot_mode__pd: 1;    //    20
    UINT32 reg_pad_boot_mode__pu: 1;    //    21
    UINT32 reg_pad_boot_mode__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda5__ds0  :  1;    //     24
    UINT32 reg_pad_sda5__ds1  :  1;    //     25
    UINT32 reg_pad_sda5__ds2  :  1;    //     26
    UINT32 reg_pad_sda5__ds3  :  1;    //     27
    UINT32 reg_pad_sda5__pd   :  1;    //     28
    UINT32 reg_pad_sda5__pu   :  1;    //     29
    UINT32 reg_pad_sda5__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_401C    pad_lgsr07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio5__ds0 :  1;    //      0
    UINT32 reg_pad_gpio5__ds1 :  1;    //      1
    UINT32 reg_pad_gpio5__ds2 :  1;    //      2
    UINT32 reg_pad_gpio5__ds3 :  1;    //      3
    UINT32 reg_pad_gpio5__pd  :  1;    //      4
    UINT32 reg_pad_gpio5__pu  :  1;    //      5
    UINT32 reg_pad_gpio5__st  :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio4__ds0 :  1;    //      8
    UINT32 reg_pad_gpio4__ds1 :  1;    //      9
    UINT32 reg_pad_gpio4__ds2 :  1;    //     10
    UINT32 reg_pad_gpio4__ds3 :  1;    //     11
    UINT32 reg_pad_gpio4__pd  :  1;    //     12
    UINT32 reg_pad_gpio4__pu  :  1;    //     13
    UINT32 reg_pad_gpio4__st  :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio3__ds0 :  1;    //     16
    UINT32 reg_pad_gpio3__ds1 :  1;    //     17
    UINT32 reg_pad_gpio3__ds2 :  1;    //     18
    UINT32 reg_pad_gpio3__ds3 :  1;    //     19
    UINT32 reg_pad_gpio3__pd  :  1;    //     20
    UINT32 reg_pad_gpio3__pu  :  1;    //     21
    UINT32 reg_pad_gpio3__st  :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio2__ds0 :  1;    //     24
    UINT32 reg_pad_gpio2__ds1 :  1;    //     25
    UINT32 reg_pad_gpio2__ds2 :  1;    //     26
    UINT32 reg_pad_gpio2__ds3 :  1;    //     27
    UINT32 reg_pad_gpio2__pd  :  1;    //     28
    UINT32 reg_pad_gpio2__pu  :  1;    //     29
    UINT32 reg_pad_gpio2__st  :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4020    pad_lgsr08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio9__ds0 :  1;    //      0
    UINT32 reg_pad_gpio9__ds1 :  1;    //      1
    UINT32 reg_pad_gpio9__ds2 :  1;    //      2
    UINT32 reg_pad_gpio9__ds3 :  1;    //      3
    UINT32 reg_pad_gpio9__pd  :  1;    //      4
    UINT32 reg_pad_gpio9__pu  :  1;    //      5
    UINT32 reg_pad_gpio9__st  :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio8__ds0 :  1;    //      8
    UINT32 reg_pad_gpio8__ds1 :  1;    //      9
    UINT32 reg_pad_gpio8__ds2 :  1;    //     10
    UINT32 reg_pad_gpio8__ds3 :  1;    //     11
    UINT32 reg_pad_gpio8__pd  :  1;    //     12
    UINT32 reg_pad_gpio8__pu  :  1;    //     13
    UINT32 reg_pad_gpio8__st  :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio7__ds0 :  1;    //     16
    UINT32 reg_pad_gpio7__ds1 :  1;    //     17
    UINT32 reg_pad_gpio7__ds2 :  1;    //     18
    UINT32 reg_pad_gpio7__ds3 :  1;    //     19
    UINT32 reg_pad_gpio7__pd  :  1;    //     20
    UINT32 reg_pad_gpio7__pu  :  1;    //     21
    UINT32 reg_pad_gpio7__st  :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio6__ds0 :  1;    //     24
    UINT32 reg_pad_gpio6__ds1 :  1;    //     25
    UINT32 reg_pad_gpio6__ds2 :  1;    //     26
    UINT32 reg_pad_gpio6__ds3 :  1;    //     27
    UINT32 reg_pad_gpio6__pd  :  1;    //     28
    UINT32 reg_pad_gpio6__pu  :  1;    //     29
    UINT32 reg_pad_gpio6__st  :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4024    pad_lgsr09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio13__ds0:  1;    //      0
    UINT32 reg_pad_gpio13__ds1:  1;    //      1
    UINT32 reg_pad_gpio13__ds2:  1;    //      2
    UINT32 reg_pad_gpio13__ds3:  1;    //      3
    UINT32 reg_pad_gpio13__pd :  1;    //      4
    UINT32 reg_pad_gpio13__pu :  1;    //      5
    UINT32 reg_pad_gpio13__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio12__ds0:  1;    //      8
    UINT32 reg_pad_gpio12__ds1:  1;    //      9
    UINT32 reg_pad_gpio12__ds2:  1;    //     10
    UINT32 reg_pad_gpio12__ds3:  1;    //     11
    UINT32 reg_pad_gpio12__pd :  1;    //     12
    UINT32 reg_pad_gpio12__pu :  1;    //     13
    UINT32 reg_pad_gpio12__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio11__ds0:  1;    //     16
    UINT32 reg_pad_gpio11__ds1:  1;    //     17
    UINT32 reg_pad_gpio11__ds2:  1;    //     18
    UINT32 reg_pad_gpio11__ds3:  1;    //     19
    UINT32 reg_pad_gpio11__pd :  1;    //     20
    UINT32 reg_pad_gpio11__pu :  1;    //     21
    UINT32 reg_pad_gpio11__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio10__ds0:  1;    //     24
    UINT32 reg_pad_gpio10__ds1:  1;    //     25
    UINT32 reg_pad_gpio10__ds2:  1;    //     26
    UINT32 reg_pad_gpio10__ds3:  1;    //     27
    UINT32 reg_pad_gpio10__pd :  1;    //     28
    UINT32 reg_pad_gpio10__pu :  1;    //     29
    UINT32 reg_pad_gpio10__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4028    pad_lgsr10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio16__ds0:  1;    //      0
    UINT32 reg_pad_gpio16__ds1:  1;    //      1
    UINT32 reg_pad_gpio16__ds2:  1;    //      2
    UINT32 reg_pad_gpio16__ds3:  1;    //      3
    UINT32 reg_pad_gpio16__pd :  1;    //      4
    UINT32 reg_pad_gpio16__pu :  1;    //      5
    UINT32 reg_pad_gpio16__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio15__ds0:  1;    //      8
    UINT32 reg_pad_gpio15__ds1:  1;    //      9
    UINT32 reg_pad_gpio15__ds2:  1;    //     10
    UINT32 reg_pad_gpio15__ds3:  1;    //     11
    UINT32 reg_pad_gpio15__pd :  1;    //     12
    UINT32 reg_pad_gpio15__pu :  1;    //     13
    UINT32 reg_pad_gpio15__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio14__ds0:  1;    //     16
    UINT32 reg_pad_gpio14__ds1:  1;    //     17
    UINT32 reg_pad_gpio14__ds2:  1;    //     18
    UINT32 reg_pad_gpio14__ds3:  1;    //     19
    UINT32 reg_pad_gpio14__pd :  1;    //     20
    UINT32 reg_pad_gpio14__pu :  1;    //     21
    UINT32 reg_pad_gpio14__st :  1;    //     22
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4100    pad_lgsr64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_cs0_mux_sel: 4;    //  3:0
    UINT32 reg_pad_sda0_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_scl0_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_dim3_sclk_mux_sel: 4;    //  15:12
    UINT32 reg_pad_dim3_mosi_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ld_vs_out3_mux_sel: 4;    //  23:20
    UINT32 reg_pad_dim2_sclk_mux_sel: 4;    //  27:24
    UINT32 reg_pad_dim2_mosi_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_LGSR_PAD_LGSR64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4104    pad_lgsr65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl1_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_spi_do1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_spi_sclk1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_spi_di1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_spi_cs1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_spi_sclk0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_spi_do0_mux_sel: 4;    //  27:24
    UINT32 reg_pad_spi_di0_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_LGSR_PAD_LGSR65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4108    pad_lgsr66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl5_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_sda4_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_scl4_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_sda3_mux_sel: 4;    //  15:12
    UINT32 reg_pad_scl3_mux_sel: 4;    //  19:16
    UINT32 reg_pad_sda2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_scl2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda1_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_LGSR_PAD_LGSR66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_410C    pad_lgsr67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio5_mux_sel: 4;    //  3: 0
    UINT32 reg_pad_gpio4_mux_sel: 4;    //  7: 4
    UINT32 reg_pad_gpio3_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_boot_mode_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda5_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_LGSR_PAD_LGSR67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4110    pad_lgsr68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio13_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio12_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio11_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio10_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio9_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio8_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio7_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio6_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_LGSR_PAD_LGSR68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_4114    pad_lgsr69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio16_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio15_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio14_mux_sel: 4;    //  11:8
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FUNC_IOMUX_LGSR_PAD_LGSR69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_LGSR_PAD_LGSR00_O22A0_T        pad_lgsr00 ;             // 0xCC3F_4000
    FUNC_IOMUX_LGSR_PAD_LGSR01_O22A0_T        pad_lgsr01 ;             // 0xCC3F_4004
    FUNC_IOMUX_LGSR_PAD_LGSR02_O22A0_T        pad_lgsr02 ;             // 0xCC3F_4008
    FUNC_IOMUX_LGSR_PAD_LGSR03_O22A0_T        pad_lgsr03 ;             // 0xCC3F_400C
    FUNC_IOMUX_LGSR_PAD_LGSR04_O22A0_T        pad_lgsr04 ;             // 0xCC3F_4010
    FUNC_IOMUX_LGSR_PAD_LGSR05_O22A0_T        pad_lgsr05 ;             // 0xCC3F_4014
    FUNC_IOMUX_LGSR_PAD_LGSR06_O22A0_T        pad_lgsr06 ;             // 0xCC3F_4018
    FUNC_IOMUX_LGSR_PAD_LGSR07_O22A0_T        pad_lgsr07 ;             // 0xCC3F_401C
    FUNC_IOMUX_LGSR_PAD_LGSR08_O22A0_T        pad_lgsr08 ;             // 0xCC3F_4020
    FUNC_IOMUX_LGSR_PAD_LGSR09_O22A0_T        pad_lgsr09 ;             // 0xCC3F_4024
    FUNC_IOMUX_LGSR_PAD_LGSR10_O22A0_T        pad_lgsr10 ;             // 0xCC3F_4028
    UINT32                             _rsvd_00[53];            // 0xCC3F_402C ~ 0xCC3F_40FC
    FUNC_IOMUX_LGSR_PAD_LGSR64_O22A0_T        pad_lgsr64 ;             // 0xCC3F_4100
    FUNC_IOMUX_LGSR_PAD_LGSR65_O22A0_T        pad_lgsr65 ;             // 0xCC3F_4104
    FUNC_IOMUX_LGSR_PAD_LGSR66_O22A0_T        pad_lgsr66 ;             // 0xCC3F_4108
    FUNC_IOMUX_LGSR_PAD_LGSR67_O22A0_T        pad_lgsr67 ;             // 0xCC3F_410C
    FUNC_IOMUX_LGSR_PAD_LGSR68_O22A0_T        pad_lgsr68 ;             // 0xCC3F_4110
    FUNC_IOMUX_LGSR_PAD_LGSR69_O22A0_T        pad_lgsr69 ;             // 0xCC3F_4114
}FUNC_IOMUX_LGSR_REG_O22A0_T;
/* 17 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_LGSR_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

