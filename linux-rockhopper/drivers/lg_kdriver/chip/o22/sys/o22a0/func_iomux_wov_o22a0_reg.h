#ifndef _FUNC_IOMUX_WOV_REG_H_
#define _FUNC_IOMUX_WOV_REG_H_

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
    0xF308_2000    pad_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_spi_clk__ds0:  1,    //      0
    reg_pad_micom_spi_clk__ds1:  1,    //      1
    reg_pad_micom_spi_clk__ds2:  1,    //      2
    reg_pad_micom_spi_clk__ds3:  1,    //      3
    reg_pad_micom_spi_clk__pd :  1,    //      4
    reg_pad_micom_spi_clk__pu :  1,    //      5
    reg_pad_micom_spi_clk__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_spi_do__ds0 :  1,    //      8
    reg_pad_micom_spi_do__ds1 :  1,    //      9
    reg_pad_micom_spi_do__ds2 :  1,    //     10
    reg_pad_micom_spi_do__ds3 :  1,    //     11
    reg_pad_micom_spi_do__pd  :  1,    //     12
    reg_pad_micom_spi_do__pu  :  1,    //     13
    reg_pad_micom_spi_do__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_opm__ds0          :  1,    //     16
    reg_pad_opm__ds1          :  1,    //     17
    reg_pad_opm__ds2          :  1,    //     18
    reg_pad_opm__ds3          :  1,    //     19
    reg_pad_opm__pd           :  1,    //     20
    reg_pad_opm__pu           :  1,    //     21
    reg_pad_opm__st           :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pores_n__ds0      :  1,    //     24
    reg_pad_pores_n__ds1      :  1,    //     25
    reg_pad_pores_n__ds2      :  1,    //     26
    reg_pad_pores_n__ds3      :  1,    //     27
    reg_pad_pores_n__pd       :  1,    //     28
    reg_pad_pores_n__pu       :  1,    //     29
    reg_pad_pores_n__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2004    pad_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_01__ds0     :  1,    //      0
    reg_pad_micom_01__ds1     :  1,    //      1
    reg_pad_micom_01__ds2     :  1,    //      2
    reg_pad_micom_01__ds3     :  1,    //      3
    reg_pad_micom_01__pd      :  1,    //      4
    reg_pad_micom_01__pu      :  1,    //      5
    reg_pad_micom_01__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_00__ds0     :  1,    //      8
    reg_pad_micom_00__ds1     :  1,    //      9
    reg_pad_micom_00__ds2     :  1,    //     10
    reg_pad_micom_00__ds3     :  1,    //     11
    reg_pad_micom_00__pd      :  1,    //     12
    reg_pad_micom_00__pu      :  1,    //     13
    reg_pad_micom_00__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_spi_di__ds0 :  1,    //     16
    reg_pad_micom_spi_di__ds1 :  1,    //     17
    reg_pad_micom_spi_di__ds2 :  1,    //     18
    reg_pad_micom_spi_di__ds3 :  1,    //     19
    reg_pad_micom_spi_di__pd  :  1,    //     20
    reg_pad_micom_spi_di__pu  :  1,    //     21
    reg_pad_micom_spi_di__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_spi_cs__ds0 :  1,    //     24
    reg_pad_micom_spi_cs__ds1 :  1,    //     25
    reg_pad_micom_spi_cs__ds2 :  1,    //     26
    reg_pad_micom_spi_cs__ds3 :  1,    //     27
    reg_pad_micom_spi_cs__pd  :  1,    //     28
    reg_pad_micom_spi_cs__pu  :  1,    //     29
    reg_pad_micom_spi_cs__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2008    pad_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_05__ds0     :  1,    //      0
    reg_pad_micom_05__ds1     :  1,    //      1
    reg_pad_micom_05__ds2     :  1,    //      2
    reg_pad_micom_05__ds3     :  1,    //      3
    reg_pad_micom_05__pd      :  1,    //      4
    reg_pad_micom_05__pu      :  1,    //      5
    reg_pad_micom_05__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_m1_ret_ctrl__ds0  :  1,    //      8
    reg_pad_m1_ret_ctrl__ds1  :  1,    //      9
    reg_pad_m1_ret_ctrl__ds2  :  1,    //     10
    reg_pad_m1_ret_ctrl__ds3  :  1,    //     11
    reg_pad_m1_ret_ctrl__pd   :  1,    //     12
    reg_pad_m1_ret_ctrl__pu   :  1,    //     13
    reg_pad_m1_ret_ctrl__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_03__ds0     :  1,    //     16
    reg_pad_micom_03__ds1     :  1,    //     17
    reg_pad_micom_03__ds2     :  1,    //     18
    reg_pad_micom_03__ds3     :  1,    //     19
    reg_pad_micom_03__pd      :  1,    //     20
    reg_pad_micom_03__pu      :  1,    //     21
    reg_pad_micom_03__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_02__ds0     :  1,    //     24
    reg_pad_micom_02__ds1     :  1,    //     25
    reg_pad_micom_02__ds2     :  1,    //     26
    reg_pad_micom_02__ds3     :  1,    //     27
    reg_pad_micom_02__pd      :  1,    //     28
    reg_pad_micom_02__pu      :  1,    //     29
    reg_pad_micom_02__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_200C    pad_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_09__ds0     :  1,    //      0
    reg_pad_micom_09__ds1     :  1,    //      1
    reg_pad_micom_09__ds2     :  1,    //      2
    reg_pad_micom_09__ds3     :  1,    //      3
    reg_pad_micom_09__pd      :  1,    //      4
    reg_pad_micom_09__pu      :  1,    //      5
    reg_pad_micom_09__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_08__ds0     :  1,    //      8
    reg_pad_micom_08__ds1     :  1,    //      9
    reg_pad_micom_08__ds2     :  1,    //     10
    reg_pad_micom_08__ds3     :  1,    //     11
    reg_pad_micom_08__pd      :  1,    //     12
    reg_pad_micom_08__pu      :  1,    //     13
    reg_pad_micom_08__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_m0_ret_ctrl__ds0  :  1,    //     16
    reg_pad_m0_ret_ctrl__ds1  :  1,    //     17
    reg_pad_m0_ret_ctrl__ds2  :  1,    //     18
    reg_pad_m0_ret_ctrl__ds3  :  1,    //     19
    reg_pad_m0_ret_ctrl__pd   :  1,    //     20
    reg_pad_m0_ret_ctrl__pu   :  1,    //     21
    reg_pad_m0_ret_ctrl__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_06__ds0     :  1,    //     24
    reg_pad_micom_06__ds1     :  1,    //     25
    reg_pad_micom_06__ds2     :  1,    //     26
    reg_pad_micom_06__ds3     :  1,    //     27
    reg_pad_micom_06__pd      :  1,    //     28
    reg_pad_micom_06__pu      :  1,    //     29
    reg_pad_micom_06__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2010    pad_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_13__ds0     :  1,    //      0
    reg_pad_micom_13__ds1     :  1,    //      1
    reg_pad_micom_13__ds2     :  1,    //      2
    reg_pad_micom_13__ds3     :  1,    //      3
    reg_pad_micom_13__pd      :  1,    //      4
    reg_pad_micom_13__pu      :  1,    //      5
    reg_pad_micom_13__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_12__ds0     :  1,    //      8
    reg_pad_micom_12__ds1     :  1,    //      9
    reg_pad_micom_12__ds2     :  1,    //     10
    reg_pad_micom_12__ds3     :  1,    //     11
    reg_pad_micom_12__pd      :  1,    //     12
    reg_pad_micom_12__pu      :  1,    //     13
    reg_pad_micom_12__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_11__ds0     :  1,    //     16
    reg_pad_micom_11__ds1     :  1,    //     17
    reg_pad_micom_11__ds2     :  1,    //     18
    reg_pad_micom_11__ds3     :  1,    //     19
    reg_pad_micom_11__pd      :  1,    //     20
    reg_pad_micom_11__pu      :  1,    //     21
    reg_pad_micom_11__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_10__ds0     :  1,    //     24
    reg_pad_micom_10__ds1     :  1,    //     25
    reg_pad_micom_10__ds2     :  1,    //     26
    reg_pad_micom_10__ds3     :  1,    //     27
    reg_pad_micom_10__pd      :  1,    //     28
    reg_pad_micom_10__pu      :  1,    //     29
    reg_pad_micom_10__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2014    pad_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_17__ds0     :  1,    //      0
    reg_pad_micom_17__ds1     :  1,    //      1
    reg_pad_micom_17__ds2     :  1,    //      2
    reg_pad_micom_17__ds3     :  1,    //      3
    reg_pad_micom_17__pd      :  1,    //      4
    reg_pad_micom_17__pu      :  1,    //      5
    reg_pad_micom_17__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_16__ds0     :  1,    //      8
    reg_pad_micom_16__ds1     :  1,    //      9
    reg_pad_micom_16__ds2     :  1,    //     10
    reg_pad_micom_16__ds3     :  1,    //     11
    reg_pad_micom_16__pd      :  1,    //     12
    reg_pad_micom_16__pu      :  1,    //     13
    reg_pad_micom_16__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_15__ds0     :  1,    //     16
    reg_pad_micom_15__ds1     :  1,    //     17
    reg_pad_micom_15__ds2     :  1,    //     18
    reg_pad_micom_15__ds3     :  1,    //     19
    reg_pad_micom_15__pd      :  1,    //     20
    reg_pad_micom_15__pu      :  1,    //     21
    reg_pad_micom_15__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_14__ds0     :  1,    //     24
    reg_pad_micom_14__ds1     :  1,    //     25
    reg_pad_micom_14__ds2     :  1,    //     26
    reg_pad_micom_14__ds3     :  1,    //     27
    reg_pad_micom_14__pd      :  1,    //     28
    reg_pad_micom_14__pu      :  1,    //     29
    reg_pad_micom_14__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2018    pad_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_21__ds0     :  1,    //      0
    reg_pad_micom_21__ds1     :  1,    //      1
    reg_pad_micom_21__ds2     :  1,    //      2
    reg_pad_micom_21__ds3     :  1,    //      3
    reg_pad_micom_21__pd      :  1,    //      4
    reg_pad_micom_21__pu      :  1,    //      5
    reg_pad_micom_21__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_20__ds0     :  1,    //      8
    reg_pad_micom_20__ds1     :  1,    //      9
    reg_pad_micom_20__ds2     :  1,    //     10
    reg_pad_micom_20__ds3     :  1,    //     11
    reg_pad_micom_20__pd      :  1,    //     12
    reg_pad_micom_20__pu      :  1,    //     13
    reg_pad_micom_20__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_19__ds0     :  1,    //     16
    reg_pad_micom_19__ds1     :  1,    //     17
    reg_pad_micom_19__ds2     :  1,    //     18
    reg_pad_micom_19__ds3     :  1,    //     19
    reg_pad_micom_19__pd      :  1,    //     20
    reg_pad_micom_19__pu      :  1,    //     21
    reg_pad_micom_19__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_18__ds0     :  1,    //     24
    reg_pad_micom_18__ds1     :  1,    //     25
    reg_pad_micom_18__ds2     :  1,    //     26
    reg_pad_micom_18__ds3     :  1,    //     27
    reg_pad_micom_18__pd      :  1,    //     28
    reg_pad_micom_18__pu      :  1,    //     29
    reg_pad_micom_18__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_201C    pad_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_25__ds0     :  1,    //      0
    reg_pad_micom_25__ds1     :  1,    //      1
    reg_pad_micom_25__ds2     :  1,    //      2
    reg_pad_micom_25__ds3     :  1,    //      3
    reg_pad_micom_25__pd      :  1,    //      4
    reg_pad_micom_25__pu      :  1,    //      5
    reg_pad_micom_25__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_24__ds0     :  1,    //      8
    reg_pad_micom_24__ds1     :  1,    //      9
    reg_pad_micom_24__ds2     :  1,    //     10
    reg_pad_micom_24__ds3     :  1,    //     11
    reg_pad_micom_24__pd      :  1,    //     12
    reg_pad_micom_24__pu      :  1,    //     13
    reg_pad_micom_24__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_23__ds0     :  1,    //     16
    reg_pad_micom_23__ds1     :  1,    //     17
    reg_pad_micom_23__ds2     :  1,    //     18
    reg_pad_micom_23__ds3     :  1,    //     19
    reg_pad_micom_23__pd      :  1,    //     20
    reg_pad_micom_23__pu      :  1,    //     21
    reg_pad_micom_23__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_22__ds0     :  1,    //     24
    reg_pad_micom_22__ds1     :  1,    //     25
    reg_pad_micom_22__ds2     :  1,    //     26
    reg_pad_micom_22__ds3     :  1,    //     27
    reg_pad_micom_22__pd      :  1,    //     28
    reg_pad_micom_22__pu      :  1,    //     29
    reg_pad_micom_22__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2020    pad_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_29__ds0     :  1,    //      0
    reg_pad_micom_29__ds1     :  1,    //      1
    reg_pad_micom_29__ds2     :  1,    //      2
    reg_pad_micom_29__ds3     :  1,    //      3
    reg_pad_micom_29__pd      :  1,    //      4
    reg_pad_micom_29__pu      :  1,    //      5
    reg_pad_micom_29__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_28__ds0     :  1,    //      8
    reg_pad_micom_28__ds1     :  1,    //      9
    reg_pad_micom_28__ds2     :  1,    //     10
    reg_pad_micom_28__ds3     :  1,    //     11
    reg_pad_micom_28__pd      :  1,    //     12
    reg_pad_micom_28__pu      :  1,    //     13
    reg_pad_micom_28__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_27__ds0     :  1,    //     16
    reg_pad_micom_27__ds1     :  1,    //     17
    reg_pad_micom_27__ds2     :  1,    //     18
    reg_pad_micom_27__ds3     :  1,    //     19
    reg_pad_micom_27__pd      :  1,    //     20
    reg_pad_micom_27__pu      :  1,    //     21
    reg_pad_micom_27__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_26__ds0     :  1,    //     24
    reg_pad_micom_26__ds1     :  1,    //     25
    reg_pad_micom_26__ds2     :  1,    //     26
    reg_pad_micom_26__ds3     :  1,    //     27
    reg_pad_micom_26__pd      :  1,    //     28
    reg_pad_micom_26__pu      :  1,    //     29
    reg_pad_micom_26__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2024    pad_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm0_datain__ds0: 1,    //     0
    reg_pad_wov_pdm0_datain__ds1: 1,    //     1
    reg_pad_wov_pdm0_datain__ds2: 1,    //     2
    reg_pad_wov_pdm0_datain__ds3: 1,    //     3
    reg_pad_wov_pdm0_datain__pd: 1,    //      4
    reg_pad_wov_pdm0_datain__pu: 1,    //      5
    reg_pad_wov_pdm0_datain__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_wov_pdm1_datain__ds0: 1,    //     8
    reg_pad_wov_pdm1_datain__ds1: 1,    //     9
    reg_pad_wov_pdm1_datain__ds2: 1,    //    10
    reg_pad_wov_pdm1_datain__ds3: 1,    //    11
    reg_pad_wov_pdm1_datain__pd: 1,    //     12
    reg_pad_wov_pdm1_datain__pu: 1,    //     13
    reg_pad_wov_pdm1_datain__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_wov_pdm_clkout__ds0: 1,    //     16
    reg_pad_wov_pdm_clkout__ds1: 1,    //     17
    reg_pad_wov_pdm_clkout__ds2: 1,    //     18
    reg_pad_wov_pdm_clkout__ds3: 1,    //     19
    reg_pad_wov_pdm_clkout__pd:  1,    //     20
    reg_pad_wov_pdm_clkout__pu:  1,    //     21
    reg_pad_wov_pdm_clkout__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_30__ds0     :  1,    //     24
    reg_pad_micom_30__ds1     :  1,    //     25
    reg_pad_micom_30__ds2     :  1,    //     26
    reg_pad_micom_30__ds3     :  1,    //     27
    reg_pad_micom_30__pd      :  1,    //     28
    reg_pad_micom_30__pu      :  1,    //     29
    reg_pad_micom_30__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2028    pad_wov10 ''
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
    reg_pad_audclk_out__ds0   :  1,    //     16
    reg_pad_audclk_out__ds1   :  1,    //     17
    reg_pad_audclk_out__ds2   :  1,    //     18
    reg_pad_audclk_out__ds3   :  1,    //     19
    reg_pad_audclk_out__pd    :  1,    //     20
    reg_pad_audclk_out__pu    :  1,    //     21
    reg_pad_audclk_out__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_boot_mode__ds0: 1,    //    24
    reg_pad_micom_boot_mode__ds1: 1,    //    25
    reg_pad_micom_boot_mode__ds2: 1,    //    26
    reg_pad_micom_boot_mode__ds3: 1,    //    27
    reg_pad_micom_boot_mode__pd: 1,    //     28
    reg_pad_micom_boot_mode__pu: 1,    //     29
    reg_pad_micom_boot_mode__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_WOV_PAD_WOV10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_202C    pad_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_cec__ds0     :  1,    //      0
    reg_pad_hdmi_cec__ds1     :  1,    //      1
    reg_pad_hdmi_cec__ds2     :  1,    //      2
    reg_pad_hdmi_cec__ds3     :  1,    //      3
    reg_pad_hdmi_cec__pd      :  1,    //      4
    reg_pad_hdmi_cec__pu      :  1,    //      5
    reg_pad_hdmi_cec__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_daclrch__ds0      :  1,    //      8
    reg_pad_daclrch__ds1      :  1,    //      9
    reg_pad_daclrch__ds2      :  1,    //     10
    reg_pad_daclrch__ds3      :  1,    //     11
    reg_pad_daclrch__pd       :  1,    //     12
    reg_pad_daclrch__pu       :  1,    //     13
    reg_pad_daclrch__st       :  1,    //     14
                              : 17;    //  31:15 reserved
}FUNC_IOMUX_WOV_PAD_WOV11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2100    pad_wov64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_01_mux_sel  :  4,    //   3: 0
    reg_pad_micom_00_mux_sel  :  4,    //   7: 4
    reg_pad_micom_spi_di_mux_sel: 4,    //  11:8
    reg_pad_micom_spi_cs_mux_sel: 4,    //  15:12
    reg_pad_micom_spi_clk_mux_sel: 4,    //  19:16
    reg_pad_micom_spi_do_mux_sel: 4,    //  23:20
    reg_pad_opm_mux_sel       :  4,    //  27:24
    reg_pad_pores_n_mux_sel   :  4;    //  31:28
}FUNC_IOMUX_WOV_PAD_WOV64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2104    pad_wov65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_09_mux_sel  :  4,    //   3: 0
    reg_pad_micom_08_mux_sel  :  4,    //   7: 4
    reg_pad_m0_ret_ctrl_mux_sel: 4,    //  11: 8
    reg_pad_micom_06_mux_sel  :  4,    //  15:12
    reg_pad_micom_05_mux_sel  :  4,    //  19:16
    reg_pad_m1_ret_ctrl_mux_sel: 4,    //  23:20
    reg_pad_micom_03_mux_sel  :  4,    //  27:24
    reg_pad_micom_02_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_WOV_PAD_WOV65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2108    pad_wov66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_17_mux_sel  :  4,    //   3: 0
    reg_pad_micom_16_mux_sel  :  4,    //   7: 4
    reg_pad_micom_15_mux_sel  :  4,    //  11: 8
    reg_pad_micom_14_mux_sel  :  4,    //  15:12
    reg_pad_micom_13_mux_sel  :  4,    //  19:16
    reg_pad_micom_12_mux_sel  :  4,    //  23:20
    reg_pad_micom_11_mux_sel  :  4,    //  27:24
    reg_pad_micom_10_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_WOV_PAD_WOV66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_210C    pad_wov67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_25_mux_sel  :  4,    //   3: 0
    reg_pad_micom_24_mux_sel  :  4,    //   7: 4
    reg_pad_micom_23_mux_sel  :  4,    //  11: 8
    reg_pad_micom_22_mux_sel  :  4,    //  15:12
    reg_pad_micom_21_mux_sel  :  4,    //  19:16
    reg_pad_micom_20_mux_sel  :  4,    //  23:20
    reg_pad_micom_19_mux_sel  :  4,    //  27:24
    reg_pad_micom_18_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_WOV_PAD_WOV67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2110    pad_wov68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_wov_pdm0_datain_mux_sel: 4,    //  3:0
    reg_pad_wov_pdm1_datain_mux_sel: 4,    //  7:4
    reg_pad_wov_pdm_clkout_mux_sel: 4,    //  11:8
    reg_pad_micom_30_mux_sel  :  4,    //  15:12
    reg_pad_micom_29_mux_sel  :  4,    //  19:16
    reg_pad_micom_28_mux_sel  :  4,    //  23:20
    reg_pad_micom_27_mux_sel  :  4,    //  27:24
    reg_pad_micom_26_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_WOV_PAD_WOV68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2114    pad_wov69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_cec_mux_sel  :  4,    //   3: 0
    reg_pad_daclrch_mux_sel   :  4,    //   7: 4
    reg_pad_dacsck_mux_sel    :  4,    //  11: 8
    reg_pad_daclrck_mux_sel   :  4,    //  15:12
    reg_pad_audclk_out_mux_sel:  4,    //  19:16
    reg_pad_micom_boot_mode_mux_sel: 4,    //  23:20
                              :  8;    //  31:24 reserved
}FUNC_IOMUX_WOV_PAD_WOV69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_WOV_PAD_WOV00_O22A0_T          pad_wov00  ;             // 0xF308_2000
    FUNC_IOMUX_WOV_PAD_WOV01_O22A0_T          pad_wov01  ;             // 0xF308_2004
    FUNC_IOMUX_WOV_PAD_WOV02_O22A0_T          pad_wov02  ;             // 0xF308_2008
    FUNC_IOMUX_WOV_PAD_WOV03_O22A0_T          pad_wov03  ;             // 0xF308_200C
    FUNC_IOMUX_WOV_PAD_WOV04_O22A0_T          pad_wov04  ;             // 0xF308_2010
    FUNC_IOMUX_WOV_PAD_WOV05_O22A0_T          pad_wov05  ;             // 0xF308_2014
    FUNC_IOMUX_WOV_PAD_WOV06_O22A0_T          pad_wov06  ;             // 0xF308_2018
    FUNC_IOMUX_WOV_PAD_WOV07_O22A0_T          pad_wov07  ;             // 0xF308_201C
    FUNC_IOMUX_WOV_PAD_WOV08_O22A0_T          pad_wov08  ;             // 0xF308_2020
    FUNC_IOMUX_WOV_PAD_WOV09_O22A0_T          pad_wov09  ;             // 0xF308_2024
    FUNC_IOMUX_WOV_PAD_WOV10_O22A0_T          pad_wov10  ;             // 0xF308_2028
    FUNC_IOMUX_WOV_PAD_WOV11_O22A0_T          pad_wov11  ;             // 0xF308_202C
    UINT32                             _rsvd_00[52];            // 0xF308_2030 ~ 0xF308_20FC
    FUNC_IOMUX_WOV_PAD_WOV64_O22A0_T          pad_wov64  ;             // 0xF308_2100
    FUNC_IOMUX_WOV_PAD_WOV65_O22A0_T          pad_wov65  ;             // 0xF308_2104
    FUNC_IOMUX_WOV_PAD_WOV66_O22A0_T          pad_wov66  ;             // 0xF308_2108
    FUNC_IOMUX_WOV_PAD_WOV67_O22A0_T          pad_wov67  ;             // 0xF308_210C
    FUNC_IOMUX_WOV_PAD_WOV68_O22A0_T          pad_wov68  ;             // 0xF308_2110
    FUNC_IOMUX_WOV_PAD_WOV69_O22A0_T          pad_wov69  ;             // 0xF308_2114
}FUNC_IOMUX_WOV_REG_O22A0_T;
/* 18 regs */

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

#define FUNC_IOMUX_WOV_PAD_WOV00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define FUNC_IOMUX_WOV_PAD_WOV01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define FUNC_IOMUX_WOV_PAD_WOV02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define FUNC_IOMUX_WOV_PAD_WOV03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define FUNC_IOMUX_WOV_PAD_WOV04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define FUNC_IOMUX_WOV_PAD_WOV05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define FUNC_IOMUX_WOV_PAD_WOV06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define FUNC_IOMUX_WOV_PAD_WOV07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define FUNC_IOMUX_WOV_PAD_WOV08_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define FUNC_IOMUX_WOV_PAD_WOV09_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define FUNC_IOMUX_WOV_PAD_WOV10_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define FUNC_IOMUX_WOV_PAD_WOV11_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define FUNC_IOMUX_WOV_PAD_WOV64_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define FUNC_IOMUX_WOV_PAD_WOV65_O22A0_T_OFF                       (BASEADDRESS+0x0104)
#define FUNC_IOMUX_WOV_PAD_WOV66_O22A0_T_OFF                       (BASEADDRESS+0x0108)
#define FUNC_IOMUX_WOV_PAD_WOV67_O22A0_T_OFF                       (BASEADDRESS+0x010C)
#define FUNC_IOMUX_WOV_PAD_WOV68_O22A0_T_OFF                       (BASEADDRESS+0x0110)
#define FUNC_IOMUX_WOV_PAD_WOV69_O22A0_T_OFF                       (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xF308_2000    pad_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_spi_clk__ds0: 1;    //  0
    UINT32 reg_pad_micom_spi_clk__ds1: 1;    //  1
    UINT32 reg_pad_micom_spi_clk__ds2: 1;    //  2
    UINT32 reg_pad_micom_spi_clk__ds3: 1;    //  3
    UINT32 reg_pad_micom_spi_clk__pd: 1;    //  4
    UINT32 reg_pad_micom_spi_clk__pu: 1;    //  5
    UINT32 reg_pad_micom_spi_clk__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_spi_do__ds0: 1;    //  8
    UINT32 reg_pad_micom_spi_do__ds1: 1;    //  9
    UINT32 reg_pad_micom_spi_do__ds2: 1;    //  10
    UINT32 reg_pad_micom_spi_do__ds3: 1;    //  11
    UINT32 reg_pad_micom_spi_do__pd: 1;    //  12
    UINT32 reg_pad_micom_spi_do__pu: 1;    //  13
    UINT32 reg_pad_micom_spi_do__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_opm__ds0   :  1;    //     16
    UINT32 reg_pad_opm__ds1   :  1;    //     17
    UINT32 reg_pad_opm__ds2   :  1;    //     18
    UINT32 reg_pad_opm__ds3   :  1;    //     19
    UINT32 reg_pad_opm__pd    :  1;    //     20
    UINT32 reg_pad_opm__pu    :  1;    //     21
    UINT32 reg_pad_opm__st    :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_pores_n__ds0: 1;    //     24
    UINT32 reg_pad_pores_n__ds1: 1;    //     25
    UINT32 reg_pad_pores_n__ds2: 1;    //     26
    UINT32 reg_pad_pores_n__ds3: 1;    //     27
    UINT32 reg_pad_pores_n__pd:  1;    //     28
    UINT32 reg_pad_pores_n__pu:  1;    //     29
    UINT32 reg_pad_pores_n__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2004    pad_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_01__ds0: 1;    //     0
    UINT32 reg_pad_micom_01__ds1: 1;    //     1
    UINT32 reg_pad_micom_01__ds2: 1;    //     2
    UINT32 reg_pad_micom_01__ds3: 1;    //     3
    UINT32 reg_pad_micom_01__pd: 1;    //      4
    UINT32 reg_pad_micom_01__pu: 1;    //      5
    UINT32 reg_pad_micom_01__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_00__ds0: 1;    //     8
    UINT32 reg_pad_micom_00__ds1: 1;    //     9
    UINT32 reg_pad_micom_00__ds2: 1;    //    10
    UINT32 reg_pad_micom_00__ds3: 1;    //    11
    UINT32 reg_pad_micom_00__pd: 1;    //     12
    UINT32 reg_pad_micom_00__pu: 1;    //     13
    UINT32 reg_pad_micom_00__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_spi_di__ds0: 1;    //  16
    UINT32 reg_pad_micom_spi_di__ds1: 1;    //  17
    UINT32 reg_pad_micom_spi_di__ds2: 1;    //  18
    UINT32 reg_pad_micom_spi_di__ds3: 1;    //  19
    UINT32 reg_pad_micom_spi_di__pd: 1;    //  20
    UINT32 reg_pad_micom_spi_di__pu: 1;    //  21
    UINT32 reg_pad_micom_spi_di__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_spi_cs__ds0: 1;    //  24
    UINT32 reg_pad_micom_spi_cs__ds1: 1;    //  25
    UINT32 reg_pad_micom_spi_cs__ds2: 1;    //  26
    UINT32 reg_pad_micom_spi_cs__ds3: 1;    //  27
    UINT32 reg_pad_micom_spi_cs__pd: 1;    //  28
    UINT32 reg_pad_micom_spi_cs__pu: 1;    //  29
    UINT32 reg_pad_micom_spi_cs__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2008    pad_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_05__ds0: 1;    //     0
    UINT32 reg_pad_micom_05__ds1: 1;    //     1
    UINT32 reg_pad_micom_05__ds2: 1;    //     2
    UINT32 reg_pad_micom_05__ds3: 1;    //     3
    UINT32 reg_pad_micom_05__pd: 1;    //      4
    UINT32 reg_pad_micom_05__pu: 1;    //      5
    UINT32 reg_pad_micom_05__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_m1_ret_ctrl__ds0: 1;    //  8
    UINT32 reg_pad_m1_ret_ctrl__ds1: 1;    //  9
    UINT32 reg_pad_m1_ret_ctrl__ds2: 1;    //  10
    UINT32 reg_pad_m1_ret_ctrl__ds3: 1;    //  11
    UINT32 reg_pad_m1_ret_ctrl__pd: 1;    //  12
    UINT32 reg_pad_m1_ret_ctrl__pu: 1;    //  13
    UINT32 reg_pad_m1_ret_ctrl__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_03__ds0: 1;    //    16
    UINT32 reg_pad_micom_03__ds1: 1;    //    17
    UINT32 reg_pad_micom_03__ds2: 1;    //    18
    UINT32 reg_pad_micom_03__ds3: 1;    //    19
    UINT32 reg_pad_micom_03__pd: 1;    //     20
    UINT32 reg_pad_micom_03__pu: 1;    //     21
    UINT32 reg_pad_micom_03__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_02__ds0: 1;    //    24
    UINT32 reg_pad_micom_02__ds1: 1;    //    25
    UINT32 reg_pad_micom_02__ds2: 1;    //    26
    UINT32 reg_pad_micom_02__ds3: 1;    //    27
    UINT32 reg_pad_micom_02__pd: 1;    //     28
    UINT32 reg_pad_micom_02__pu: 1;    //     29
    UINT32 reg_pad_micom_02__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_200C    pad_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_09__ds0: 1;    //     0
    UINT32 reg_pad_micom_09__ds1: 1;    //     1
    UINT32 reg_pad_micom_09__ds2: 1;    //     2
    UINT32 reg_pad_micom_09__ds3: 1;    //     3
    UINT32 reg_pad_micom_09__pd: 1;    //      4
    UINT32 reg_pad_micom_09__pu: 1;    //      5
    UINT32 reg_pad_micom_09__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_08__ds0: 1;    //     8
    UINT32 reg_pad_micom_08__ds1: 1;    //     9
    UINT32 reg_pad_micom_08__ds2: 1;    //    10
    UINT32 reg_pad_micom_08__ds3: 1;    //    11
    UINT32 reg_pad_micom_08__pd: 1;    //     12
    UINT32 reg_pad_micom_08__pu: 1;    //     13
    UINT32 reg_pad_micom_08__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_m0_ret_ctrl__ds0: 1;    //  16
    UINT32 reg_pad_m0_ret_ctrl__ds1: 1;    //  17
    UINT32 reg_pad_m0_ret_ctrl__ds2: 1;    //  18
    UINT32 reg_pad_m0_ret_ctrl__ds3: 1;    //  19
    UINT32 reg_pad_m0_ret_ctrl__pd: 1;    //  20
    UINT32 reg_pad_m0_ret_ctrl__pu: 1;    //  21
    UINT32 reg_pad_m0_ret_ctrl__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_06__ds0: 1;    //    24
    UINT32 reg_pad_micom_06__ds1: 1;    //    25
    UINT32 reg_pad_micom_06__ds2: 1;    //    26
    UINT32 reg_pad_micom_06__ds3: 1;    //    27
    UINT32 reg_pad_micom_06__pd: 1;    //     28
    UINT32 reg_pad_micom_06__pu: 1;    //     29
    UINT32 reg_pad_micom_06__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2010    pad_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_13__ds0: 1;    //     0
    UINT32 reg_pad_micom_13__ds1: 1;    //     1
    UINT32 reg_pad_micom_13__ds2: 1;    //     2
    UINT32 reg_pad_micom_13__ds3: 1;    //     3
    UINT32 reg_pad_micom_13__pd: 1;    //      4
    UINT32 reg_pad_micom_13__pu: 1;    //      5
    UINT32 reg_pad_micom_13__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_12__ds0: 1;    //     8
    UINT32 reg_pad_micom_12__ds1: 1;    //     9
    UINT32 reg_pad_micom_12__ds2: 1;    //    10
    UINT32 reg_pad_micom_12__ds3: 1;    //    11
    UINT32 reg_pad_micom_12__pd: 1;    //     12
    UINT32 reg_pad_micom_12__pu: 1;    //     13
    UINT32 reg_pad_micom_12__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_11__ds0: 1;    //    16
    UINT32 reg_pad_micom_11__ds1: 1;    //    17
    UINT32 reg_pad_micom_11__ds2: 1;    //    18
    UINT32 reg_pad_micom_11__ds3: 1;    //    19
    UINT32 reg_pad_micom_11__pd: 1;    //     20
    UINT32 reg_pad_micom_11__pu: 1;    //     21
    UINT32 reg_pad_micom_11__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_10__ds0: 1;    //    24
    UINT32 reg_pad_micom_10__ds1: 1;    //    25
    UINT32 reg_pad_micom_10__ds2: 1;    //    26
    UINT32 reg_pad_micom_10__ds3: 1;    //    27
    UINT32 reg_pad_micom_10__pd: 1;    //     28
    UINT32 reg_pad_micom_10__pu: 1;    //     29
    UINT32 reg_pad_micom_10__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2014    pad_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_17__ds0: 1;    //     0
    UINT32 reg_pad_micom_17__ds1: 1;    //     1
    UINT32 reg_pad_micom_17__ds2: 1;    //     2
    UINT32 reg_pad_micom_17__ds3: 1;    //     3
    UINT32 reg_pad_micom_17__pd: 1;    //      4
    UINT32 reg_pad_micom_17__pu: 1;    //      5
    UINT32 reg_pad_micom_17__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_16__ds0: 1;    //     8
    UINT32 reg_pad_micom_16__ds1: 1;    //     9
    UINT32 reg_pad_micom_16__ds2: 1;    //    10
    UINT32 reg_pad_micom_16__ds3: 1;    //    11
    UINT32 reg_pad_micom_16__pd: 1;    //     12
    UINT32 reg_pad_micom_16__pu: 1;    //     13
    UINT32 reg_pad_micom_16__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_15__ds0: 1;    //    16
    UINT32 reg_pad_micom_15__ds1: 1;    //    17
    UINT32 reg_pad_micom_15__ds2: 1;    //    18
    UINT32 reg_pad_micom_15__ds3: 1;    //    19
    UINT32 reg_pad_micom_15__pd: 1;    //     20
    UINT32 reg_pad_micom_15__pu: 1;    //     21
    UINT32 reg_pad_micom_15__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_14__ds0: 1;    //    24
    UINT32 reg_pad_micom_14__ds1: 1;    //    25
    UINT32 reg_pad_micom_14__ds2: 1;    //    26
    UINT32 reg_pad_micom_14__ds3: 1;    //    27
    UINT32 reg_pad_micom_14__pd: 1;    //     28
    UINT32 reg_pad_micom_14__pu: 1;    //     29
    UINT32 reg_pad_micom_14__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2018    pad_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_21__ds0: 1;    //     0
    UINT32 reg_pad_micom_21__ds1: 1;    //     1
    UINT32 reg_pad_micom_21__ds2: 1;    //     2
    UINT32 reg_pad_micom_21__ds3: 1;    //     3
    UINT32 reg_pad_micom_21__pd: 1;    //      4
    UINT32 reg_pad_micom_21__pu: 1;    //      5
    UINT32 reg_pad_micom_21__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_20__ds0: 1;    //     8
    UINT32 reg_pad_micom_20__ds1: 1;    //     9
    UINT32 reg_pad_micom_20__ds2: 1;    //    10
    UINT32 reg_pad_micom_20__ds3: 1;    //    11
    UINT32 reg_pad_micom_20__pd: 1;    //     12
    UINT32 reg_pad_micom_20__pu: 1;    //     13
    UINT32 reg_pad_micom_20__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_19__ds0: 1;    //    16
    UINT32 reg_pad_micom_19__ds1: 1;    //    17
    UINT32 reg_pad_micom_19__ds2: 1;    //    18
    UINT32 reg_pad_micom_19__ds3: 1;    //    19
    UINT32 reg_pad_micom_19__pd: 1;    //     20
    UINT32 reg_pad_micom_19__pu: 1;    //     21
    UINT32 reg_pad_micom_19__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_18__ds0: 1;    //    24
    UINT32 reg_pad_micom_18__ds1: 1;    //    25
    UINT32 reg_pad_micom_18__ds2: 1;    //    26
    UINT32 reg_pad_micom_18__ds3: 1;    //    27
    UINT32 reg_pad_micom_18__pd: 1;    //     28
    UINT32 reg_pad_micom_18__pu: 1;    //     29
    UINT32 reg_pad_micom_18__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_201C    pad_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_25__ds0: 1;    //     0
    UINT32 reg_pad_micom_25__ds1: 1;    //     1
    UINT32 reg_pad_micom_25__ds2: 1;    //     2
    UINT32 reg_pad_micom_25__ds3: 1;    //     3
    UINT32 reg_pad_micom_25__pd: 1;    //      4
    UINT32 reg_pad_micom_25__pu: 1;    //      5
    UINT32 reg_pad_micom_25__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_24__ds0: 1;    //     8
    UINT32 reg_pad_micom_24__ds1: 1;    //     9
    UINT32 reg_pad_micom_24__ds2: 1;    //    10
    UINT32 reg_pad_micom_24__ds3: 1;    //    11
    UINT32 reg_pad_micom_24__pd: 1;    //     12
    UINT32 reg_pad_micom_24__pu: 1;    //     13
    UINT32 reg_pad_micom_24__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_23__ds0: 1;    //    16
    UINT32 reg_pad_micom_23__ds1: 1;    //    17
    UINT32 reg_pad_micom_23__ds2: 1;    //    18
    UINT32 reg_pad_micom_23__ds3: 1;    //    19
    UINT32 reg_pad_micom_23__pd: 1;    //     20
    UINT32 reg_pad_micom_23__pu: 1;    //     21
    UINT32 reg_pad_micom_23__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_22__ds0: 1;    //    24
    UINT32 reg_pad_micom_22__ds1: 1;    //    25
    UINT32 reg_pad_micom_22__ds2: 1;    //    26
    UINT32 reg_pad_micom_22__ds3: 1;    //    27
    UINT32 reg_pad_micom_22__pd: 1;    //     28
    UINT32 reg_pad_micom_22__pu: 1;    //     29
    UINT32 reg_pad_micom_22__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2020    pad_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_29__ds0: 1;    //     0
    UINT32 reg_pad_micom_29__ds1: 1;    //     1
    UINT32 reg_pad_micom_29__ds2: 1;    //     2
    UINT32 reg_pad_micom_29__ds3: 1;    //     3
    UINT32 reg_pad_micom_29__pd: 1;    //      4
    UINT32 reg_pad_micom_29__pu: 1;    //      5
    UINT32 reg_pad_micom_29__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_28__ds0: 1;    //     8
    UINT32 reg_pad_micom_28__ds1: 1;    //     9
    UINT32 reg_pad_micom_28__ds2: 1;    //    10
    UINT32 reg_pad_micom_28__ds3: 1;    //    11
    UINT32 reg_pad_micom_28__pd: 1;    //     12
    UINT32 reg_pad_micom_28__pu: 1;    //     13
    UINT32 reg_pad_micom_28__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_27__ds0: 1;    //    16
    UINT32 reg_pad_micom_27__ds1: 1;    //    17
    UINT32 reg_pad_micom_27__ds2: 1;    //    18
    UINT32 reg_pad_micom_27__ds3: 1;    //    19
    UINT32 reg_pad_micom_27__pd: 1;    //     20
    UINT32 reg_pad_micom_27__pu: 1;    //     21
    UINT32 reg_pad_micom_27__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_26__ds0: 1;    //    24
    UINT32 reg_pad_micom_26__ds1: 1;    //    25
    UINT32 reg_pad_micom_26__ds2: 1;    //    26
    UINT32 reg_pad_micom_26__ds3: 1;    //    27
    UINT32 reg_pad_micom_26__pd: 1;    //     28
    UINT32 reg_pad_micom_26__pu: 1;    //     29
    UINT32 reg_pad_micom_26__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2024    pad_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_wov_pdm0_datain__ds0: 1;    //  0
    UINT32 reg_pad_wov_pdm0_datain__ds1: 1;    //  1
    UINT32 reg_pad_wov_pdm0_datain__ds2: 1;    //  2
    UINT32 reg_pad_wov_pdm0_datain__ds3: 1;    //  3
    UINT32 reg_pad_wov_pdm0_datain__pd: 1;    //  4
    UINT32 reg_pad_wov_pdm0_datain__pu: 1;    //  5
    UINT32 reg_pad_wov_pdm0_datain__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_wov_pdm1_datain__ds0: 1;    //  8
    UINT32 reg_pad_wov_pdm1_datain__ds1: 1;    //  9
    UINT32 reg_pad_wov_pdm1_datain__ds2: 1;    //  10
    UINT32 reg_pad_wov_pdm1_datain__ds3: 1;    //  11
    UINT32 reg_pad_wov_pdm1_datain__pd: 1;    //  12
    UINT32 reg_pad_wov_pdm1_datain__pu: 1;    //  13
    UINT32 reg_pad_wov_pdm1_datain__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_wov_pdm_clkout__ds0: 1;    //  16
    UINT32 reg_pad_wov_pdm_clkout__ds1: 1;    //  17
    UINT32 reg_pad_wov_pdm_clkout__ds2: 1;    //  18
    UINT32 reg_pad_wov_pdm_clkout__ds3: 1;    //  19
    UINT32 reg_pad_wov_pdm_clkout__pd: 1;    //  20
    UINT32 reg_pad_wov_pdm_clkout__pu: 1;    //  21
    UINT32 reg_pad_wov_pdm_clkout__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_30__ds0: 1;    //    24
    UINT32 reg_pad_micom_30__ds1: 1;    //    25
    UINT32 reg_pad_micom_30__ds2: 1;    //    26
    UINT32 reg_pad_micom_30__ds3: 1;    //    27
    UINT32 reg_pad_micom_30__pd: 1;    //     28
    UINT32 reg_pad_micom_30__pu: 1;    //     29
    UINT32 reg_pad_micom_30__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2028    pad_wov10 ''
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
    UINT32 reg_pad_audclk_out__ds0: 1;    //  16
    UINT32 reg_pad_audclk_out__ds1: 1;    //  17
    UINT32 reg_pad_audclk_out__ds2: 1;    //  18
    UINT32 reg_pad_audclk_out__ds3: 1;    //  19
    UINT32 reg_pad_audclk_out__pd: 1;    //   20
    UINT32 reg_pad_audclk_out__pu: 1;    //   21
    UINT32 reg_pad_audclk_out__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_boot_mode__ds0: 1;    //  24
    UINT32 reg_pad_micom_boot_mode__ds1: 1;    //  25
    UINT32 reg_pad_micom_boot_mode__ds2: 1;    //  26
    UINT32 reg_pad_micom_boot_mode__ds3: 1;    //  27
    UINT32 reg_pad_micom_boot_mode__pd: 1;    //  28
    UINT32 reg_pad_micom_boot_mode__pu: 1;    //  29
    UINT32 reg_pad_micom_boot_mode__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_202C    pad_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_cec__ds0: 1;    //     0
    UINT32 reg_pad_hdmi_cec__ds1: 1;    //     1
    UINT32 reg_pad_hdmi_cec__ds2: 1;    //     2
    UINT32 reg_pad_hdmi_cec__ds3: 1;    //     3
    UINT32 reg_pad_hdmi_cec__pd: 1;    //      4
    UINT32 reg_pad_hdmi_cec__pu: 1;    //      5
    UINT32 reg_pad_hdmi_cec__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_daclrch__ds0: 1;    //      8
    UINT32 reg_pad_daclrch__ds1: 1;    //      9
    UINT32 reg_pad_daclrch__ds2: 1;    //     10
    UINT32 reg_pad_daclrch__ds3: 1;    //     11
    UINT32 reg_pad_daclrch__pd:  1;    //     12
    UINT32 reg_pad_daclrch__pu:  1;    //     13
    UINT32 reg_pad_daclrch__st:  1;    //     14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2100    pad_wov64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_01_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_00_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_spi_di_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_spi_cs_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_spi_clk_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_spi_do_mux_sel: 4;    //  23:20
    UINT32 reg_pad_opm_mux_sel:  4;    //  27:24
    UINT32 reg_pad_pores_n_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_WOV_PAD_WOV64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2104    pad_wov65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_09_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_08_mux_sel: 4;    //  7:4
    UINT32 reg_pad_m0_ret_ctrl_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_06_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_05_mux_sel: 4;    //  19:16
    UINT32 reg_pad_m1_ret_ctrl_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_03_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_02_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_WOV_PAD_WOV65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2108    pad_wov66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_17_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_16_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_15_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_14_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_13_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_12_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_11_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_10_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_WOV_PAD_WOV66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_210C    pad_wov67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_25_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_24_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_23_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_22_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_21_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_20_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_19_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_18_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_WOV_PAD_WOV67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2110    pad_wov68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_wov_pdm0_datain_mux_sel: 4;    //  3:0
    UINT32 reg_pad_wov_pdm1_datain_mux_sel: 4;    //  7:4
    UINT32 reg_pad_wov_pdm_clkout_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_30_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_29_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_28_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_27_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_26_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_WOV_PAD_WOV68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_2114    pad_wov69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_cec_mux_sel: 4;    //  3:0
    UINT32 reg_pad_daclrch_mux_sel: 4;    //  7:4
    UINT32 reg_pad_dacsck_mux_sel: 4;    //  11:8
    UINT32 reg_pad_daclrck_mux_sel: 4;    //  15:12
    UINT32 reg_pad_audclk_out_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_boot_mode_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}FUNC_IOMUX_WOV_PAD_WOV69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_WOV_PAD_WOV00_O22A0_T          pad_wov00  ;             // 0xF308_2000
    FUNC_IOMUX_WOV_PAD_WOV01_O22A0_T          pad_wov01  ;             // 0xF308_2004
    FUNC_IOMUX_WOV_PAD_WOV02_O22A0_T          pad_wov02  ;             // 0xF308_2008
    FUNC_IOMUX_WOV_PAD_WOV03_O22A0_T          pad_wov03  ;             // 0xF308_200C
    FUNC_IOMUX_WOV_PAD_WOV04_O22A0_T          pad_wov04  ;             // 0xF308_2010
    FUNC_IOMUX_WOV_PAD_WOV05_O22A0_T          pad_wov05  ;             // 0xF308_2014
    FUNC_IOMUX_WOV_PAD_WOV06_O22A0_T          pad_wov06  ;             // 0xF308_2018
    FUNC_IOMUX_WOV_PAD_WOV07_O22A0_T          pad_wov07  ;             // 0xF308_201C
    FUNC_IOMUX_WOV_PAD_WOV08_O22A0_T          pad_wov08  ;             // 0xF308_2020
    FUNC_IOMUX_WOV_PAD_WOV09_O22A0_T          pad_wov09  ;             // 0xF308_2024
    FUNC_IOMUX_WOV_PAD_WOV10_O22A0_T          pad_wov10  ;             // 0xF308_2028
    FUNC_IOMUX_WOV_PAD_WOV11_O22A0_T          pad_wov11  ;             // 0xF308_202C
    UINT32                             _rsvd_00[52];            // 0xF308_2030 ~ 0xF308_20FC
    FUNC_IOMUX_WOV_PAD_WOV64_O22A0_T          pad_wov64  ;             // 0xF308_2100
    FUNC_IOMUX_WOV_PAD_WOV65_O22A0_T          pad_wov65  ;             // 0xF308_2104
    FUNC_IOMUX_WOV_PAD_WOV66_O22A0_T          pad_wov66  ;             // 0xF308_2108
    FUNC_IOMUX_WOV_PAD_WOV67_O22A0_T          pad_wov67  ;             // 0xF308_210C
    FUNC_IOMUX_WOV_PAD_WOV68_O22A0_T          pad_wov68  ;             // 0xF308_2110
    FUNC_IOMUX_WOV_PAD_WOV69_O22A0_T          pad_wov69  ;             // 0xF308_2114
}FUNC_IOMUX_WOV_REG_O22A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_WOV_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

