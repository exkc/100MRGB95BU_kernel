#ifndef _MICOM_IOMUX_CTRL_WOC_REG_O24A0_H_
#define _MICOM_IOMUX_CTRL_WOC_REG_O24A0_H_

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
    0xC63F_5000    pad_woc_00 ''
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
    reg_pad_m0_ret_ctrl__ds0  :  1,    //     16
    reg_pad_m0_ret_ctrl__ds1  :  1,    //     17
    reg_pad_m0_ret_ctrl__ds2  :  1,    //     18
    reg_pad_m0_ret_ctrl__ds3  :  1,    //     19
    reg_pad_m0_ret_ctrl__st   :  1,    //     20
    reg_pad_hdmi_cec__ds0     :  1,    //     21
    reg_pad_hdmi_cec__ds1     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_cec__ds2     :  1,    //     24
    reg_pad_hdmi_cec__ds3     :  1,    //     25
    reg_pad_hdmi_cec__pd      :  1,    //     26
    reg_pad_hdmi_cec__pu      :  1,    //     27
    reg_pad_hdmi_cec__st      :  1,    //     28
                              :  3;    //  31:29 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5004    pad_woc_01 ''
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
    reg_pad_micom_04__ds0     :  1,    //      8
    reg_pad_micom_04__ds1     :  1,    //      9
    reg_pad_micom_04__ds2     :  1,    //     10
    reg_pad_micom_04__ds3     :  1,    //     11
    reg_pad_micom_04__pd      :  1,    //     12
    reg_pad_micom_04__pu      :  1,    //     13
    reg_pad_micom_04__st      :  1,    //     14
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5008    pad_woc_02 ''
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
    reg_pad_micom_07__ds0     :  1,    //     16
    reg_pad_micom_07__ds1     :  1,    //     17
    reg_pad_micom_07__ds2     :  1,    //     18
    reg_pad_micom_07__ds3     :  1,    //     19
    reg_pad_micom_07__pd      :  1,    //     20
    reg_pad_micom_07__pu      :  1,    //     21
    reg_pad_micom_07__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_06__ds0     :  1,    //     24
    reg_pad_micom_06__ds1     :  1,    //     25
    reg_pad_micom_06__ds2     :  1,    //     26
    reg_pad_micom_06__ds3     :  1,    //     27
    reg_pad_micom_06__pd      :  1,    //     28
    reg_pad_micom_06__pu      :  1,    //     29
    reg_pad_micom_06__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_500C    pad_woc_03 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5010    pad_woc_04 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5014    pad_woc_05 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5018    pad_woc_06 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_501C    pad_woc_07 ''
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
                              : 17;    //  31:15 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5020    pad_woc_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pdm_clkout__ds0   :  1,    //      0
    reg_pad_pdm_clkout__ds1   :  1,    //      1
    reg_pad_pdm_clkout__ds2   :  1,    //      2
    reg_pad_pdm_clkout__ds3   :  1,    //      3
    reg_pad_pdm_clkout__pd    :  1,    //      4
    reg_pad_pdm_clkout__pu    :  1,    //      5
    reg_pad_pdm_clkout__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_32__ds0     :  1,    //      8
    reg_pad_micom_32__ds1     :  1,    //      9
    reg_pad_micom_32__ds2     :  1,    //     10
    reg_pad_micom_32__ds3     :  1,    //     11
    reg_pad_micom_32__pd      :  1,    //     12
    reg_pad_micom_32__pu      :  1,    //     13
    reg_pad_micom_32__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_31__ds0     :  1,    //     16
    reg_pad_micom_31__ds1     :  1,    //     17
    reg_pad_micom_31__ds2     :  1,    //     18
    reg_pad_micom_31__ds3     :  1,    //     19
    reg_pad_micom_31__pd      :  1,    //     20
    reg_pad_micom_31__pu      :  1,    //     21
    reg_pad_micom_31__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_30__ds0     :  1,    //     24
    reg_pad_micom_30__ds1     :  1,    //     25
    reg_pad_micom_30__ds2     :  1,    //     26
    reg_pad_micom_30__ds3     :  1,    //     27
    reg_pad_micom_30__pd      :  1,    //     28
    reg_pad_micom_30__pu      :  1,    //     29
    reg_pad_micom_30__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5024    pad_woc_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pdm1_datain__ds0  :  1,    //      0
    reg_pad_pdm1_datain__ds1  :  1,    //      1
    reg_pad_pdm1_datain__ds2  :  1,    //      2
    reg_pad_pdm1_datain__ds3  :  1,    //      3
    reg_pad_pdm1_datain__pd   :  1,    //      4
    reg_pad_pdm1_datain__pu   :  1,    //      5
    reg_pad_pdm1_datain__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pdm0_datain__ds0  :  1,    //      8
    reg_pad_pdm0_datain__ds1  :  1,    //      9
    reg_pad_pdm0_datain__ds2  :  1,    //     10
    reg_pad_pdm0_datain__ds3  :  1,    //     11
    reg_pad_pdm0_datain__pd   :  1,    //     12
    reg_pad_pdm0_datain__pu   :  1,    //     13
    reg_pad_pdm0_datain__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_uart0_tx__ds0     :  1,    //     16
    reg_pad_uart0_tx__ds1     :  1,    //     17
    reg_pad_uart0_tx__ds2     :  1,    //     18
    reg_pad_uart0_tx__ds3     :  1,    //     19
    reg_pad_uart0_tx__pd      :  1,    //     20
    reg_pad_uart0_tx__pu      :  1,    //     21
    reg_pad_uart0_tx__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_uart0_rx__ds0     :  1,    //     24
    reg_pad_uart0_rx__ds1     :  1,    //     25
    reg_pad_uart0_rx__ds2     :  1,    //     26
    reg_pad_uart0_rx__ds3     :  1,    //     27
    reg_pad_uart0_rx__pd      :  1,    //     28
    reg_pad_uart0_rx__pu      :  1,    //     29
    reg_pad_uart0_rx__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5028    pad_woc_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_pad_opm__ds0          :  1,    //      2
    reg_pad_opm__ds1          :  1,    //      3
    reg_pad_opm__ds2          :  1,    //      4
    reg_pad_opm__ds3          :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_pad_opm__st           :  1,    //      8
    reg_pad_pores_n__ds0      :  1,    //      9
    reg_pad_pores_n__ds1      :  1,    //     10
    reg_pad_pores_n__ds2      :  1,    //     11
    reg_pad_pores_n__ds3      :  1,    //     12
                              :  1,    //     13 reserved
    reg_pad_pores_n__st       :  1,    //     14
                              : 17;    //  31:15 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5100    pad_woc_64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_05_mux_sel  :  4,    //   3: 0
    reg_pad_micom_04_mux_sel  :  4,    //   7: 4
    reg_pad_micom_03_mux_sel  :  4,    //  11: 8
    reg_pad_micom_02_mux_sel  :  4,    //  15:12
    reg_pad_micom_01_mux_sel  :  4,    //  19:16
    reg_pad_micom_00_mux_sel  :  4,    //  23:20
    reg_pad_m0_ret_ctrl_mux_sel: 4,    //  27:24
    reg_pad_hdmi_cec_mux_sel  :  4;    //  31:28
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5104    pad_woc_65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_13_mux_sel  :  4,    //   3: 0
    reg_pad_micom_12_mux_sel  :  4,    //   7: 4
    reg_pad_micom_11_mux_sel  :  4,    //  11: 8
    reg_pad_micom_10_mux_sel  :  4,    //  15:12
    reg_pad_micom_09_mux_sel  :  4,    //  19:16
    reg_pad_micom_08_mux_sel  :  4,    //  23:20
    reg_pad_micom_07_mux_sel  :  4,    //  27:24
    reg_pad_micom_06_mux_sel  :  4;    //  31:28
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5108    pad_woc_66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_21_mux_sel  :  4,    //   3: 0
    reg_pad_micom_20_mux_sel  :  4,    //   7: 4
    reg_pad_micom_19_mux_sel  :  4,    //  11: 8
    reg_pad_micom_18_mux_sel  :  4,    //  15:12
    reg_pad_micom_17_mux_sel  :  4,    //  19:16
    reg_pad_micom_16_mux_sel  :  4,    //  23:20
    reg_pad_micom_15_mux_sel  :  4,    //  27:24
    reg_pad_micom_14_mux_sel  :  4;    //  31:28
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_510C    pad_woc_67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_29_mux_sel  :  4,    //   3: 0
    reg_pad_micom_28_mux_sel  :  4,    //   7: 4
    reg_pad_uart0_tx_mux_sel  :  4,    //  11: 8
    reg_pad_uart0_rx_mux_sel  :  4,    //  15:12
    reg_pad_micom_25_mux_sel  :  4,    //  19:16
    reg_pad_micom_24_mux_sel  :  4,    //  23:20
    reg_pad_micom_23_mux_sel  :  4,    //  27:24
    reg_pad_micom_22_mux_sel  :  4;    //  31:28
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5110    pad_woc_68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pdm1_datain_mux_sel: 4,    //   3: 0
    reg_pad_pdm0_datain_mux_sel: 4,    //   7: 4
    reg_pad_pdm_clkout_mux_sel:  4,    //  11: 8
    reg_pad_micom_32_mux_sel  :  4,    //  15:12
    reg_pad_micom_31_mux_sel  :  4,    //  19:16
    reg_pad_micom_30_mux_sel  :  4,    //  23:20
                              :  8;    //  31:24 reserved
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_iomux_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_00_O24A0_T    pad_woc_00;      // 0xC63F_5000
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_01_O24A0_T    pad_woc_01;      // 0xC63F_5004
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_02_O24A0_T    pad_woc_02;      // 0xC63F_5008
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_03_O24A0_T    pad_woc_03;      // 0xC63F_500C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_04_O24A0_T    pad_woc_04;      // 0xC63F_5010
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_05_O24A0_T    pad_woc_05;      // 0xC63F_5014
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_06_O24A0_T    pad_woc_06;      // 0xC63F_5018
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_07_O24A0_T    pad_woc_07;      // 0xC63F_501C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_08_O24A0_T    pad_woc_08;      // 0xC63F_5020
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_09_O24A0_T    pad_woc_09;      // 0xC63F_5024
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_10_O24A0_T    pad_woc_10;      // 0xC63F_5028
    UINT32                             _rsvd_00[53];            // 0xC63F_502C ~ 0xC63F_50FC
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_64_O24A0_T    pad_woc_64;      // 0xC63F_5100
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_65_O24A0_T    pad_woc_65;      // 0xC63F_5104
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_66_O24A0_T    pad_woc_66;      // 0xC63F_5108
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_67_O24A0_T    pad_woc_67;      // 0xC63F_510C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_68_O24A0_T    pad_woc_68;      // 0xC63F_5110
}MICOM_IOMUX_CTRL_WOC_REG_O24A0_T;
/* 16 regs */

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

#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_00_O24A0_T_OFF         (BASEADDRESS+0x0000)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_01_O24A0_T_OFF         (BASEADDRESS+0x0004)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_02_O24A0_T_OFF         (BASEADDRESS+0x0008)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_03_O24A0_T_OFF         (BASEADDRESS+0x000C)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_04_O24A0_T_OFF         (BASEADDRESS+0x0010)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_05_O24A0_T_OFF         (BASEADDRESS+0x0014)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_06_O24A0_T_OFF         (BASEADDRESS+0x0018)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_07_O24A0_T_OFF         (BASEADDRESS+0x001C)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_08_O24A0_T_OFF         (BASEADDRESS+0x0020)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_09_O24A0_T_OFF         (BASEADDRESS+0x0024)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_10_O24A0_T_OFF         (BASEADDRESS+0x0028)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_64_O24A0_T_OFF         (BASEADDRESS+0x0100)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_65_O24A0_T_OFF         (BASEADDRESS+0x0104)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_66_O24A0_T_OFF         (BASEADDRESS+0x0108)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_67_O24A0_T_OFF         (BASEADDRESS+0x010C)
#define MICOM_IOMUX_CTRL_WOC_PAD_WOC_68_O24A0_T_OFF         (BASEADDRESS+0x0110)

/*-----------------------------------------------------------------------------------------
    0xC63F_5000    pad_woc_00 ''
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
    UINT32 reg_pad_m0_ret_ctrl__ds0: 1;    //  16
    UINT32 reg_pad_m0_ret_ctrl__ds1: 1;    //  17
    UINT32 reg_pad_m0_ret_ctrl__ds2: 1;    //  18
    UINT32 reg_pad_m0_ret_ctrl__ds3: 1;    //  19
    UINT32 reg_pad_m0_ret_ctrl__st: 1;    //  20
    UINT32 reg_pad_hdmi_cec__ds0: 1;    //    21
    UINT32 reg_pad_hdmi_cec__ds1: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_cec__ds2: 1;    //    24
    UINT32 reg_pad_hdmi_cec__ds3: 1;    //    25
    UINT32 reg_pad_hdmi_cec__pd: 1;    //     26
    UINT32 reg_pad_hdmi_cec__pu: 1;    //     27
    UINT32 reg_pad_hdmi_cec__st: 1;    //     28
    UINT32 resvd03            :  3;    //  31:29 reserved
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5004    pad_woc_01 ''
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
    UINT32 reg_pad_micom_04__ds0: 1;    //     8
    UINT32 reg_pad_micom_04__ds1: 1;    //     9
    UINT32 reg_pad_micom_04__ds2: 1;    //    10
    UINT32 reg_pad_micom_04__ds3: 1;    //    11
    UINT32 reg_pad_micom_04__pd: 1;    //     12
    UINT32 reg_pad_micom_04__pu: 1;    //     13
    UINT32 reg_pad_micom_04__st: 1;    //     14
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5008    pad_woc_02 ''
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
    UINT32 reg_pad_micom_07__ds0: 1;    //    16
    UINT32 reg_pad_micom_07__ds1: 1;    //    17
    UINT32 reg_pad_micom_07__ds2: 1;    //    18
    UINT32 reg_pad_micom_07__ds3: 1;    //    19
    UINT32 reg_pad_micom_07__pd: 1;    //     20
    UINT32 reg_pad_micom_07__pu: 1;    //     21
    UINT32 reg_pad_micom_07__st: 1;    //     22
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_500C    pad_woc_03 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5010    pad_woc_04 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5014    pad_woc_05 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5018    pad_woc_06 ''
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_501C    pad_woc_07 ''
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
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5020    pad_woc_08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pdm_clkout__ds0: 1;    //   0
    UINT32 reg_pad_pdm_clkout__ds1: 1;    //   1
    UINT32 reg_pad_pdm_clkout__ds2: 1;    //   2
    UINT32 reg_pad_pdm_clkout__ds3: 1;    //   3
    UINT32 reg_pad_pdm_clkout__pd: 1;    //    4
    UINT32 reg_pad_pdm_clkout__pu: 1;    //    5
    UINT32 reg_pad_pdm_clkout__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_32__ds0: 1;    //     8
    UINT32 reg_pad_micom_32__ds1: 1;    //     9
    UINT32 reg_pad_micom_32__ds2: 1;    //    10
    UINT32 reg_pad_micom_32__ds3: 1;    //    11
    UINT32 reg_pad_micom_32__pd: 1;    //     12
    UINT32 reg_pad_micom_32__pu: 1;    //     13
    UINT32 reg_pad_micom_32__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_31__ds0: 1;    //    16
    UINT32 reg_pad_micom_31__ds1: 1;    //    17
    UINT32 reg_pad_micom_31__ds2: 1;    //    18
    UINT32 reg_pad_micom_31__ds3: 1;    //    19
    UINT32 reg_pad_micom_31__pd: 1;    //     20
    UINT32 reg_pad_micom_31__pu: 1;    //     21
    UINT32 reg_pad_micom_31__st: 1;    //     22
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
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5024    pad_woc_09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pdm1_datain__ds0: 1;    //  0
    UINT32 reg_pad_pdm1_datain__ds1: 1;    //  1
    UINT32 reg_pad_pdm1_datain__ds2: 1;    //  2
    UINT32 reg_pad_pdm1_datain__ds3: 1;    //  3
    UINT32 reg_pad_pdm1_datain__pd: 1;    //   4
    UINT32 reg_pad_pdm1_datain__pu: 1;    //   5
    UINT32 reg_pad_pdm1_datain__st: 1;    //   6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_pdm0_datain__ds0: 1;    //  8
    UINT32 reg_pad_pdm0_datain__ds1: 1;    //  9
    UINT32 reg_pad_pdm0_datain__ds2: 1;    //  10
    UINT32 reg_pad_pdm0_datain__ds3: 1;    //  11
    UINT32 reg_pad_pdm0_datain__pd: 1;    //  12
    UINT32 reg_pad_pdm0_datain__pu: 1;    //  13
    UINT32 reg_pad_pdm0_datain__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_uart0_tx__ds0: 1;    //    16
    UINT32 reg_pad_uart0_tx__ds1: 1;    //    17
    UINT32 reg_pad_uart0_tx__ds2: 1;    //    18
    UINT32 reg_pad_uart0_tx__ds3: 1;    //    19
    UINT32 reg_pad_uart0_tx__pd: 1;    //     20
    UINT32 reg_pad_uart0_tx__pu: 1;    //     21
    UINT32 reg_pad_uart0_tx__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_uart0_rx__ds0: 1;    //    24
    UINT32 reg_pad_uart0_rx__ds1: 1;    //    25
    UINT32 reg_pad_uart0_rx__ds2: 1;    //    26
    UINT32 reg_pad_uart0_rx__ds3: 1;    //    27
    UINT32 reg_pad_uart0_rx__pd: 1;    //     28
    UINT32 reg_pad_uart0_rx__pu: 1;    //     29
    UINT32 reg_pad_uart0_rx__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5028    pad_woc_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  2;    //   1: 0 reserved
    UINT32 reg_pad_opm__ds0   :  1;    //      2
    UINT32 reg_pad_opm__ds1   :  1;    //      3
    UINT32 reg_pad_opm__ds2   :  1;    //      4
    UINT32 reg_pad_opm__ds3   :  1;    //      5
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_pad_opm__st    :  1;    //      8
    UINT32 reg_pad_pores_n__ds0: 1;    //      9
    UINT32 reg_pad_pores_n__ds1: 1;    //     10
    UINT32 reg_pad_pores_n__ds2: 1;    //     11
    UINT32 reg_pad_pores_n__ds3: 1;    //     12
    UINT32 resvd02            :  1;    //     13 reserved
    UINT32 reg_pad_pores_n__st:  1;    //     14
    UINT32 resvd03            : 17;    //  31:15 reserved
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5100    pad_woc_64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_05_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_04_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_03_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_02_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_01_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_00_mux_sel: 4;    //  23:20
    UINT32 reg_pad_m0_ret_ctrl_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_cec_mux_sel: 4;    //  31:28
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5104    pad_woc_65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_13_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_12_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_11_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_10_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_09_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_08_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_07_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_06_mux_sel: 4;    //  31:28
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5108    pad_woc_66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_21_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_20_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_19_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_18_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_17_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_16_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_15_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_14_mux_sel: 4;    //  31:28
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_510C    pad_woc_67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_29_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_28_mux_sel: 4;    //  7:4
    UINT32 reg_pad_uart0_tx_mux_sel: 4;    //  11:8
    UINT32 reg_pad_uart0_rx_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_25_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_24_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_23_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_22_mux_sel: 4;    //  31:28
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_5110    pad_woc_68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pdm1_datain_mux_sel: 4;    //  3:0
    UINT32 reg_pad_pdm0_datain_mux_sel: 4;    //  7:4
    UINT32 reg_pad_pdm_clkout_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_32_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_31_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_30_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}MICOM_IOMUX_CTRL_WOC_PAD_WOC_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_iomux_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_00_O24A0_T    pad_woc_00;      // 0xC63F_5000
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_01_O24A0_T    pad_woc_01;      // 0xC63F_5004
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_02_O24A0_T    pad_woc_02;      // 0xC63F_5008
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_03_O24A0_T    pad_woc_03;      // 0xC63F_500C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_04_O24A0_T    pad_woc_04;      // 0xC63F_5010
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_05_O24A0_T    pad_woc_05;      // 0xC63F_5014
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_06_O24A0_T    pad_woc_06;      // 0xC63F_5018
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_07_O24A0_T    pad_woc_07;      // 0xC63F_501C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_08_O24A0_T    pad_woc_08;      // 0xC63F_5020
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_09_O24A0_T    pad_woc_09;      // 0xC63F_5024
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_10_O24A0_T    pad_woc_10;      // 0xC63F_5028
    UINT32                             _rsvd_00[53];            // 0xC63F_502C ~ 0xC63F_50FC
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_64_O24A0_T    pad_woc_64;      // 0xC63F_5100
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_65_O24A0_T    pad_woc_65;      // 0xC63F_5104
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_66_O24A0_T    pad_woc_66;      // 0xC63F_5108
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_67_O24A0_T    pad_woc_67;      // 0xC63F_510C
    MICOM_IOMUX_CTRL_WOC_PAD_WOC_68_O24A0_T    pad_woc_68;      // 0xC63F_5110
}MICOM_IOMUX_CTRL_WOC_REG_O24A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MICOM_IOMUX_CTRL_WOC_REG_H_

/* from 'O24_CTOP_PAD_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

