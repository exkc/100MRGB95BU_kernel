#ifndef _CPU_IOMUX_CTRL_WOC_M23A0_REG_H_
#define _CPU_IOMUX_CTRL_WOC_M23A0_REG_H_

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
    0x0    pad_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_03__ds0     :  1,    //      0
    reg_pad_micom_03__ds1     :  1,    //      1
    reg_pad_micom_03__ds2     :  1,    //      2
    reg_pad_micom_03__ds3     :  1,    //      3
    reg_pad_micom_03__pd      :  1,    //      4
    reg_pad_micom_03__pu      :  1,    //      5
    reg_pad_micom_03__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_02__ds0     :  1,    //      8
    reg_pad_micom_02__ds1     :  1,    //      9
    reg_pad_micom_02__ds2     :  1,    //     10
    reg_pad_micom_02__ds3     :  1,    //     11
    reg_pad_micom_02__pd      :  1,    //     12
    reg_pad_micom_02__pu      :  1,    //     13
    reg_pad_micom_02__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_01__ds0     :  1,    //     16
    reg_pad_micom_01__ds1     :  1,    //     17
    reg_pad_micom_01__ds2     :  1,    //     18
    reg_pad_micom_01__ds3     :  1,    //     19
    reg_pad_micom_01__pd      :  1,    //     20
    reg_pad_micom_01__pu      :  1,    //     21
    reg_pad_micom_01__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_00__ds0     :  1,    //     24
    reg_pad_micom_00__ds1     :  1,    //     25
    reg_pad_micom_00__ds2     :  1,    //     26
    reg_pad_micom_00__ds3     :  1,    //     27
    reg_pad_micom_00__pd      :  1,    //     28
    reg_pad_micom_00__pu      :  1,    //     29
    reg_pad_micom_00__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_07__ds0     :  1,    //      0
    reg_pad_micom_07__ds1     :  1,    //      1
    reg_pad_micom_07__ds2     :  1,    //      2
    reg_pad_micom_07__ds3     :  1,    //      3
    reg_pad_micom_07__pd      :  1,    //      4
    reg_pad_micom_07__pu      :  1,    //      5
    reg_pad_micom_07__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_06__ds0     :  1,    //      8
    reg_pad_micom_06__ds1     :  1,    //      9
    reg_pad_micom_06__ds2     :  1,    //     10
    reg_pad_micom_06__ds3     :  1,    //     11
    reg_pad_micom_06__pd      :  1,    //     12
    reg_pad_micom_06__pu      :  1,    //     13
    reg_pad_micom_06__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_05__ds0     :  1,    //     16
    reg_pad_micom_05__ds1     :  1,    //     17
    reg_pad_micom_05__ds2     :  1,    //     18
    reg_pad_micom_05__ds3     :  1,    //     19
    reg_pad_micom_05__pd      :  1,    //     20
    reg_pad_micom_05__pu      :  1,    //     21
    reg_pad_micom_05__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_04__ds0     :  1,    //     24
    reg_pad_micom_04__ds1     :  1,    //     25
    reg_pad_micom_04__ds2     :  1,    //     26
    reg_pad_micom_04__ds3     :  1,    //     27
    reg_pad_micom_04__pd      :  1,    //     28
    reg_pad_micom_04__pu      :  1,    //     29
    reg_pad_micom_04__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_11__ds0     :  1,    //      0
    reg_pad_micom_11__ds1     :  1,    //      1
    reg_pad_micom_11__ds2     :  1,    //      2
    reg_pad_micom_11__ds3     :  1,    //      3
    reg_pad_micom_11__pd      :  1,    //      4
    reg_pad_micom_11__pu      :  1,    //      5
    reg_pad_micom_11__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_10__ds0     :  1,    //      8
    reg_pad_micom_10__ds1     :  1,    //      9
    reg_pad_micom_10__ds2     :  1,    //     10
    reg_pad_micom_10__ds3     :  1,    //     11
    reg_pad_micom_10__pd      :  1,    //     12
    reg_pad_micom_10__pu      :  1,    //     13
    reg_pad_micom_10__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_09__ds0     :  1,    //     16
    reg_pad_micom_09__ds1     :  1,    //     17
    reg_pad_micom_09__ds2     :  1,    //     18
    reg_pad_micom_09__ds3     :  1,    //     19
    reg_pad_micom_09__pd      :  1,    //     20
    reg_pad_micom_09__pu      :  1,    //     21
    reg_pad_micom_09__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_08__ds0     :  1,    //     24
    reg_pad_micom_08__ds1     :  1,    //     25
    reg_pad_micom_08__ds2     :  1,    //     26
    reg_pad_micom_08__ds3     :  1,    //     27
    reg_pad_micom_08__pd      :  1,    //     28
    reg_pad_micom_08__pu      :  1,    //     29
    reg_pad_micom_08__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_15__ds0     :  1,    //      0
    reg_pad_micom_15__ds1     :  1,    //      1
    reg_pad_micom_15__ds2     :  1,    //      2
    reg_pad_micom_15__ds3     :  1,    //      3
    reg_pad_micom_15__pd      :  1,    //      4
    reg_pad_micom_15__pu      :  1,    //      5
    reg_pad_micom_15__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_14__ds0     :  1,    //      8
    reg_pad_micom_14__ds1     :  1,    //      9
    reg_pad_micom_14__ds2     :  1,    //     10
    reg_pad_micom_14__ds3     :  1,    //     11
    reg_pad_micom_14__pd      :  1,    //     12
    reg_pad_micom_14__pu      :  1,    //     13
    reg_pad_micom_14__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_13__ds0     :  1,    //     16
    reg_pad_micom_13__ds1     :  1,    //     17
    reg_pad_micom_13__ds2     :  1,    //     18
    reg_pad_micom_13__ds3     :  1,    //     19
    reg_pad_micom_13__pd      :  1,    //     20
    reg_pad_micom_13__pu      :  1,    //     21
    reg_pad_micom_13__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_12__ds0     :  1,    //     24
    reg_pad_micom_12__ds1     :  1,    //     25
    reg_pad_micom_12__ds2     :  1,    //     26
    reg_pad_micom_12__ds3     :  1,    //     27
    reg_pad_micom_12__pd      :  1,    //     28
    reg_pad_micom_12__pu      :  1,    //     29
    reg_pad_micom_12__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_woc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_19__ds0     :  1,    //      0
    reg_pad_micom_19__ds1     :  1,    //      1
    reg_pad_micom_19__ds2     :  1,    //      2
    reg_pad_micom_19__ds3     :  1,    //      3
    reg_pad_micom_19__pd      :  1,    //      4
    reg_pad_micom_19__pu      :  1,    //      5
    reg_pad_micom_19__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_micom_18__ds0     :  1,    //      8
    reg_pad_micom_18__ds1     :  1,    //      9
    reg_pad_micom_18__ds2     :  1,    //     10
    reg_pad_micom_18__ds3     :  1,    //     11
    reg_pad_micom_18__pd      :  1,    //     12
    reg_pad_micom_18__pu      :  1,    //     13
    reg_pad_micom_18__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_17__ds0     :  1,    //     16
    reg_pad_micom_17__ds1     :  1,    //     17
    reg_pad_micom_17__ds2     :  1,    //     18
    reg_pad_micom_17__ds3     :  1,    //     19
    reg_pad_micom_17__pd      :  1,    //     20
    reg_pad_micom_17__pu      :  1,    //     21
    reg_pad_micom_17__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_16__ds0     :  1,    //     24
    reg_pad_micom_16__ds1     :  1,    //     25
    reg_pad_micom_16__ds2     :  1,    //     26
    reg_pad_micom_16__ds3     :  1,    //     27
    reg_pad_micom_16__pd      :  1,    //     28
    reg_pad_micom_16__pu      :  1,    //     29
    reg_pad_micom_16__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_woc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_txd__ds0    :  1,    //      0
    reg_pad_uart0_txd__ds1    :  1,    //      1
    reg_pad_uart0_txd__ds2    :  1,    //      2
    reg_pad_uart0_txd__ds3    :  1,    //      3
    reg_pad_uart0_txd__pd     :  1,    //      4
    reg_pad_uart0_txd__pu     :  1,    //      5
    reg_pad_uart0_txd__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_uart0_rxd__ds0    :  1,    //      8
    reg_pad_uart0_rxd__ds1    :  1,    //      9
    reg_pad_uart0_rxd__ds2    :  1,    //     10
    reg_pad_uart0_rxd__ds3    :  1,    //     11
    reg_pad_uart0_rxd__pd     :  1,    //     12
    reg_pad_uart0_rxd__pu     :  1,    //     13
    reg_pad_uart0_rxd__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_micom_sda__ds0    :  1,    //     16
    reg_pad_micom_sda__ds1    :  1,    //     17
    reg_pad_micom_sda__ds2    :  1,    //     18
    reg_pad_micom_sda__ds3    :  1,    //     19
    reg_pad_micom_sda__pd     :  1,    //     20
    reg_pad_micom_sda__pu     :  1,    //     21
    reg_pad_micom_sda__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_micom_scl__ds0    :  1,    //     24
    reg_pad_micom_scl__ds1    :  1,    //     25
    reg_pad_micom_scl__ds2    :  1,    //     26
    reg_pad_micom_scl__ds3    :  1,    //     27
    reg_pad_micom_scl__pd     :  1,    //     28
    reg_pad_micom_scl__pu     :  1,    //     29
    reg_pad_micom_scl__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_woc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_scl__ds0   :  1,    //      0
    reg_pad_hdmi_4_scl__ds1   :  1,    //      1
    reg_pad_hdmi_4_scl__ds2   :  1,    //      2
    reg_pad_hdmi_4_scl__ds3   :  1,    //      3
    reg_pad_hdmi_4_scl__pd    :  1,    //      4
    reg_pad_hdmi_4_scl__pu    :  1,    //      5
    reg_pad_hdmi_4_scl__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_cec__ds0     :  1,    //      8
    reg_pad_hdmi_cec__ds1     :  1,    //      9
    reg_pad_hdmi_cec__ds2     :  1,    //     10
    reg_pad_hdmi_cec__ds3     :  1,    //     11
    reg_pad_hdmi_cec__pd      :  1,    //     12
    reg_pad_hdmi_cec__pu      :  1,    //     13
    reg_pad_hdmi_cec__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_wov_pdm0_datain__ds0: 1,    //    16
    reg_pad_wov_pdm0_datain__ds1: 1,    //    17
    reg_pad_wov_pdm0_datain__ds2: 1,    //    18
    reg_pad_wov_pdm0_datain__ds3: 1,    //    19
    reg_pad_wov_pdm0_datain__pd: 1,    //     20
    reg_pad_wov_pdm0_datain__pu: 1,    //     21
    reg_pad_wov_pdm0_datain__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_wov_pdm_clkout__ds0: 1,    //     24
    reg_pad_wov_pdm_clkout__ds1: 1,    //     25
    reg_pad_wov_pdm_clkout__ds2: 1,    //     26
    reg_pad_wov_pdm_clkout__ds3: 1,    //     27
    reg_pad_wov_pdm_clkout__pd:  1,    //     28
    reg_pad_wov_pdm_clkout__pu:  1,    //     29
    reg_pad_wov_pdm_clkout__st:  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_woc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_5v_in__ds0 :  1,    //      0
    reg_pad_hdmi_4_5v_in__ds1 :  1,    //      1
    reg_pad_hdmi_4_5v_in__ds2 :  1,    //      2
    reg_pad_hdmi_4_5v_in__ds3 :  1,    //      3
    reg_pad_hdmi_4_5v_in__pd  :  1,    //      4
    reg_pad_hdmi_4_5v_in__pu  :  1,    //      5
    reg_pad_hdmi_4_5v_in__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_3_sda__ds0   :  1,    //      8
    reg_pad_hdmi_3_sda__ds1   :  1,    //      9
    reg_pad_hdmi_3_sda__ds2   :  1,    //     10
    reg_pad_hdmi_3_sda__ds3   :  1,    //     11
    reg_pad_hdmi_3_sda__pd    :  1,    //     12
    reg_pad_hdmi_3_sda__pu    :  1,    //     13
    reg_pad_hdmi_3_sda__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_3_scl__ds0   :  1,    //     16
    reg_pad_hdmi_3_scl__ds1   :  1,    //     17
    reg_pad_hdmi_3_scl__ds2   :  1,    //     18
    reg_pad_hdmi_3_scl__ds3   :  1,    //     19
    reg_pad_hdmi_3_scl__pd    :  1,    //     20
    reg_pad_hdmi_3_scl__pu    :  1,    //     21
    reg_pad_hdmi_3_scl__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_4_sda__ds0   :  1,    //     24
    reg_pad_hdmi_4_sda__ds1   :  1,    //     25
    reg_pad_hdmi_4_sda__ds2   :  1,    //     26
    reg_pad_hdmi_4_sda__ds3   :  1,    //     27
    reg_pad_hdmi_4_sda__pd    :  1,    //     28
    reg_pad_hdmi_4_sda__pu    :  1,    //     29
    reg_pad_hdmi_4_sda__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_woc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pad_m0_ret_ctrl__ds0  :  1,    //      1
    reg_pad_m0_ret_ctrl__ds1  :  1,    //      2
    reg_pad_m0_ret_ctrl__ds2  :  1,    //      3
    reg_pad_m0_ret_ctrl__ds3  :  1,    //      4
                              :  1,    //      5 reserved
    reg_pad_m0_ret_ctrl__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_3_hpd__ds0   :  1,    //      8
    reg_pad_hdmi_3_hpd__ds1   :  1,    //      9
    reg_pad_hdmi_3_hpd__ds2   :  1,    //     10
    reg_pad_hdmi_3_hpd__ds3   :  1,    //     11
    reg_pad_hdmi_3_hpd__pd    :  1,    //     12
    reg_pad_hdmi_3_hpd__pu    :  1,    //     13
    reg_pad_hdmi_3_hpd__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_4_hpd__ds0   :  1,    //     16
    reg_pad_hdmi_4_hpd__ds1   :  1,    //     17
    reg_pad_hdmi_4_hpd__ds2   :  1,    //     18
    reg_pad_hdmi_4_hpd__ds3   :  1,    //     19
    reg_pad_hdmi_4_hpd__pd    :  1,    //     20
    reg_pad_hdmi_4_hpd__pu    :  1,    //     21
    reg_pad_hdmi_4_hpd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_3_5v_in__ds0 :  1,    //     24
    reg_pad_hdmi_3_5v_in__ds1 :  1,    //     25
    reg_pad_hdmi_3_5v_in__ds2 :  1,    //     26
    reg_pad_hdmi_3_5v_in__ds3 :  1,    //     27
    reg_pad_hdmi_3_5v_in__pd  :  1,    //     28
    reg_pad_hdmi_3_5v_in__pu  :  1,    //     29
    reg_pad_hdmi_3_5v_in__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_woc09 ''
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
}CPU_IOMUX_CTRL_WOC_PAD_WOC09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_woc64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_07_mux_sel  :  4,    //   3: 0
    reg_pad_micom_06_mux_sel  :  4,    //   7: 4
    reg_pad_micom_05_mux_sel  :  4,    //  11: 8
    reg_pad_micom_04_mux_sel  :  4,    //  15:12
    reg_pad_micom_03_mux_sel  :  4,    //  19:16
    reg_pad_micom_02_mux_sel  :  4,    //  23:20
    reg_pad_micom_01_mux_sel  :  4,    //  27:24
    reg_pad_micom_00_mux_sel  :  4;    //  31:28
}CPU_IOMUX_CTRL_WOC_PAD_WOC64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_woc65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_15_mux_sel  :  4,    //   3: 0
    reg_pad_micom_14_mux_sel  :  4,    //   7: 4
    reg_pad_micom_13_mux_sel  :  4,    //  11: 8
    reg_pad_micom_12_mux_sel  :  4,    //  15:12
    reg_pad_micom_11_mux_sel  :  4,    //  19:16
    reg_pad_micom_10_mux_sel  :  4,    //  23:20
    reg_pad_micom_09_mux_sel  :  4,    //  27:24
    reg_pad_micom_08_mux_sel  :  4;    //  31:28
}CPU_IOMUX_CTRL_WOC_PAD_WOC65_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_woc66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart0_txd_mux_sel :  4,    //   3: 0
    reg_pad_uart0_rxd_mux_sel :  4,    //   7: 4
    reg_pad_micom_sda_mux_sel :  4,    //  11: 8
    reg_pad_micom_scl_mux_sel :  4,    //  15:12
    reg_pad_micom_19_mux_sel  :  4,    //  19:16
    reg_pad_micom_18_mux_sel  :  4,    //  23:20
    reg_pad_micom_17_mux_sel  :  4,    //  27:24
    reg_pad_micom_16_mux_sel  :  4;    //  31:28
}CPU_IOMUX_CTRL_WOC_PAD_WOC66_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_woc67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_5v_in_mux_sel: 4,    //  3: 0
    reg_pad_hdmi_3_sda_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_3_scl_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_4_sda_mux_sel:  4,    //  15:12
    reg_pad_hdmi_4_scl_mux_sel:  4,    //  19:16
    reg_pad_hdmi_cec_mux_sel  :  4,    //  23:20
    reg_pad_wov_pdm0_datain_mux_sel: 4,    //  27:24
    reg_pad_wov_pdm_clkout_mux_sel: 4;    //  31:28
}CPU_IOMUX_CTRL_WOC_PAD_WOC67_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_woc68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_m0_ret_ctrl_mux_sel: 4,    //   3: 0
    reg_pad_hdmi_3_hpd_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_4_hpd_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_3_5v_in_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC68_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x200    pad_woc128 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_prt3_hpd_oen     :  1,    //      0
    reg_edid_prt4_hpd_oen     :  1,    //      1
                              : 30;    //   31:2 reserved
}CPU_IOMUX_CTRL_WOC_PAD_WOC128_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_IOMUX_CTRL_WOC_PAD_WOC00_M23A0_T     pad_woc00  ;             // 0x0
    CPU_IOMUX_CTRL_WOC_PAD_WOC01_M23A0_T     pad_woc01  ;             // 0x4
    CPU_IOMUX_CTRL_WOC_PAD_WOC02_M23A0_T     pad_woc02  ;             // 0x8
    CPU_IOMUX_CTRL_WOC_PAD_WOC03_M23A0_T     pad_woc03  ;             // 0xC
    CPU_IOMUX_CTRL_WOC_PAD_WOC04_M23A0_T     pad_woc04  ;             // 0x10
    CPU_IOMUX_CTRL_WOC_PAD_WOC05_M23A0_T     pad_woc05  ;             // 0x14
    CPU_IOMUX_CTRL_WOC_PAD_WOC06_M23A0_T     pad_woc06  ;             // 0x18
    CPU_IOMUX_CTRL_WOC_PAD_WOC07_M23A0_T     pad_woc07  ;             // 0x1C
    CPU_IOMUX_CTRL_WOC_PAD_WOC08_M23A0_T     pad_woc08  ;             // 0x20
    CPU_IOMUX_CTRL_WOC_PAD_WOC09_M23A0_T     pad_woc09  ;             // 0x24
    UINT32                             _rsvd_00[54];            // 0x28 ~ 0xFC
    CPU_IOMUX_CTRL_WOC_PAD_WOC64_M23A0_T     pad_woc64  ;             // 0x100
    CPU_IOMUX_CTRL_WOC_PAD_WOC65_M23A0_T     pad_woc65  ;             // 0x104
    CPU_IOMUX_CTRL_WOC_PAD_WOC66_M23A0_T     pad_woc66  ;             // 0x108
    CPU_IOMUX_CTRL_WOC_PAD_WOC67_M23A0_T     pad_woc67  ;             // 0x10C
    CPU_IOMUX_CTRL_WOC_PAD_WOC68_M23A0_T     pad_woc68  ;             // 0x110
    UINT32                             _rsvd_01[59];            // 0x114 ~ 0x1FC
    CPU_IOMUX_CTRL_WOC_PAD_WOC128_M23A0_T    pad_woc128 ;             // 0x200
}CPU_IOMUX_CTRL_WOC_REG_M23A0_T;
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

#define CPU_IOMUX_CTRL_WOC_PAD_WOC00_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC01_M23A0_T_OFF                  (BASEADDRESS+0x0004)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC02_M23A0_T_OFF                  (BASEADDRESS+0x0008)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC03_M23A0_T_OFF                  (BASEADDRESS+0x000C)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC04_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC05_M23A0_T_OFF                  (BASEADDRESS+0x0014)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC06_M23A0_T_OFF                  (BASEADDRESS+0x0018)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC07_M23A0_T_OFF                  (BASEADDRESS+0x001C)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC08_M23A0_T_OFF                  (BASEADDRESS+0x0020)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC09_M23A0_T_OFF                  (BASEADDRESS+0x0024)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC64_M23A0_T_OFF                  (BASEADDRESS+0x0100)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC65_M23A0_T_OFF                  (BASEADDRESS+0x0104)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC66_M23A0_T_OFF                  (BASEADDRESS+0x0108)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC67_M23A0_T_OFF                  (BASEADDRESS+0x010C)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC68_M23A0_T_OFF                  (BASEADDRESS+0x0110)
#define CPU_IOMUX_CTRL_WOC_PAD_WOC128_M23A0_T_OFF                 (BASEADDRESS+0x0200)

/*-----------------------------------------------------------------------------------------
    0x0    pad_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_03__ds0: 1;    //     0
    UINT32 reg_pad_micom_03__ds1: 1;    //     1
    UINT32 reg_pad_micom_03__ds2: 1;    //     2
    UINT32 reg_pad_micom_03__ds3: 1;    //     3
    UINT32 reg_pad_micom_03__pd: 1;    //      4
    UINT32 reg_pad_micom_03__pu: 1;    //      5
    UINT32 reg_pad_micom_03__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_02__ds0: 1;    //     8
    UINT32 reg_pad_micom_02__ds1: 1;    //     9
    UINT32 reg_pad_micom_02__ds2: 1;    //    10
    UINT32 reg_pad_micom_02__ds3: 1;    //    11
    UINT32 reg_pad_micom_02__pd: 1;    //     12
    UINT32 reg_pad_micom_02__pu: 1;    //     13
    UINT32 reg_pad_micom_02__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_01__ds0: 1;    //    16
    UINT32 reg_pad_micom_01__ds1: 1;    //    17
    UINT32 reg_pad_micom_01__ds2: 1;    //    18
    UINT32 reg_pad_micom_01__ds3: 1;    //    19
    UINT32 reg_pad_micom_01__pd: 1;    //     20
    UINT32 reg_pad_micom_01__pu: 1;    //     21
    UINT32 reg_pad_micom_01__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_00__ds0: 1;    //    24
    UINT32 reg_pad_micom_00__ds1: 1;    //    25
    UINT32 reg_pad_micom_00__ds2: 1;    //    26
    UINT32 reg_pad_micom_00__ds3: 1;    //    27
    UINT32 reg_pad_micom_00__pd: 1;    //     28
    UINT32 reg_pad_micom_00__pu: 1;    //     29
    UINT32 reg_pad_micom_00__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_07__ds0: 1;    //     0
    UINT32 reg_pad_micom_07__ds1: 1;    //     1
    UINT32 reg_pad_micom_07__ds2: 1;    //     2
    UINT32 reg_pad_micom_07__ds3: 1;    //     3
    UINT32 reg_pad_micom_07__pd: 1;    //      4
    UINT32 reg_pad_micom_07__pu: 1;    //      5
    UINT32 reg_pad_micom_07__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_06__ds0: 1;    //     8
    UINT32 reg_pad_micom_06__ds1: 1;    //     9
    UINT32 reg_pad_micom_06__ds2: 1;    //    10
    UINT32 reg_pad_micom_06__ds3: 1;    //    11
    UINT32 reg_pad_micom_06__pd: 1;    //     12
    UINT32 reg_pad_micom_06__pu: 1;    //     13
    UINT32 reg_pad_micom_06__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_05__ds0: 1;    //    16
    UINT32 reg_pad_micom_05__ds1: 1;    //    17
    UINT32 reg_pad_micom_05__ds2: 1;    //    18
    UINT32 reg_pad_micom_05__ds3: 1;    //    19
    UINT32 reg_pad_micom_05__pd: 1;    //     20
    UINT32 reg_pad_micom_05__pu: 1;    //     21
    UINT32 reg_pad_micom_05__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_04__ds0: 1;    //    24
    UINT32 reg_pad_micom_04__ds1: 1;    //    25
    UINT32 reg_pad_micom_04__ds2: 1;    //    26
    UINT32 reg_pad_micom_04__ds3: 1;    //    27
    UINT32 reg_pad_micom_04__pd: 1;    //     28
    UINT32 reg_pad_micom_04__pu: 1;    //     29
    UINT32 reg_pad_micom_04__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_11__ds0: 1;    //     0
    UINT32 reg_pad_micom_11__ds1: 1;    //     1
    UINT32 reg_pad_micom_11__ds2: 1;    //     2
    UINT32 reg_pad_micom_11__ds3: 1;    //     3
    UINT32 reg_pad_micom_11__pd: 1;    //      4
    UINT32 reg_pad_micom_11__pu: 1;    //      5
    UINT32 reg_pad_micom_11__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_10__ds0: 1;    //     8
    UINT32 reg_pad_micom_10__ds1: 1;    //     9
    UINT32 reg_pad_micom_10__ds2: 1;    //    10
    UINT32 reg_pad_micom_10__ds3: 1;    //    11
    UINT32 reg_pad_micom_10__pd: 1;    //     12
    UINT32 reg_pad_micom_10__pu: 1;    //     13
    UINT32 reg_pad_micom_10__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_09__ds0: 1;    //    16
    UINT32 reg_pad_micom_09__ds1: 1;    //    17
    UINT32 reg_pad_micom_09__ds2: 1;    //    18
    UINT32 reg_pad_micom_09__ds3: 1;    //    19
    UINT32 reg_pad_micom_09__pd: 1;    //     20
    UINT32 reg_pad_micom_09__pu: 1;    //     21
    UINT32 reg_pad_micom_09__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_08__ds0: 1;    //    24
    UINT32 reg_pad_micom_08__ds1: 1;    //    25
    UINT32 reg_pad_micom_08__ds2: 1;    //    26
    UINT32 reg_pad_micom_08__ds3: 1;    //    27
    UINT32 reg_pad_micom_08__pd: 1;    //     28
    UINT32 reg_pad_micom_08__pu: 1;    //     29
    UINT32 reg_pad_micom_08__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_15__ds0: 1;    //     0
    UINT32 reg_pad_micom_15__ds1: 1;    //     1
    UINT32 reg_pad_micom_15__ds2: 1;    //     2
    UINT32 reg_pad_micom_15__ds3: 1;    //     3
    UINT32 reg_pad_micom_15__pd: 1;    //      4
    UINT32 reg_pad_micom_15__pu: 1;    //      5
    UINT32 reg_pad_micom_15__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_14__ds0: 1;    //     8
    UINT32 reg_pad_micom_14__ds1: 1;    //     9
    UINT32 reg_pad_micom_14__ds2: 1;    //    10
    UINT32 reg_pad_micom_14__ds3: 1;    //    11
    UINT32 reg_pad_micom_14__pd: 1;    //     12
    UINT32 reg_pad_micom_14__pu: 1;    //     13
    UINT32 reg_pad_micom_14__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_13__ds0: 1;    //    16
    UINT32 reg_pad_micom_13__ds1: 1;    //    17
    UINT32 reg_pad_micom_13__ds2: 1;    //    18
    UINT32 reg_pad_micom_13__ds3: 1;    //    19
    UINT32 reg_pad_micom_13__pd: 1;    //     20
    UINT32 reg_pad_micom_13__pu: 1;    //     21
    UINT32 reg_pad_micom_13__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_12__ds0: 1;    //    24
    UINT32 reg_pad_micom_12__ds1: 1;    //    25
    UINT32 reg_pad_micom_12__ds2: 1;    //    26
    UINT32 reg_pad_micom_12__ds3: 1;    //    27
    UINT32 reg_pad_micom_12__pd: 1;    //     28
    UINT32 reg_pad_micom_12__pu: 1;    //     29
    UINT32 reg_pad_micom_12__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_woc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_19__ds0: 1;    //     0
    UINT32 reg_pad_micom_19__ds1: 1;    //     1
    UINT32 reg_pad_micom_19__ds2: 1;    //     2
    UINT32 reg_pad_micom_19__ds3: 1;    //     3
    UINT32 reg_pad_micom_19__pd: 1;    //      4
    UINT32 reg_pad_micom_19__pu: 1;    //      5
    UINT32 reg_pad_micom_19__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_micom_18__ds0: 1;    //     8
    UINT32 reg_pad_micom_18__ds1: 1;    //     9
    UINT32 reg_pad_micom_18__ds2: 1;    //    10
    UINT32 reg_pad_micom_18__ds3: 1;    //    11
    UINT32 reg_pad_micom_18__pd: 1;    //     12
    UINT32 reg_pad_micom_18__pu: 1;    //     13
    UINT32 reg_pad_micom_18__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_17__ds0: 1;    //    16
    UINT32 reg_pad_micom_17__ds1: 1;    //    17
    UINT32 reg_pad_micom_17__ds2: 1;    //    18
    UINT32 reg_pad_micom_17__ds3: 1;    //    19
    UINT32 reg_pad_micom_17__pd: 1;    //     20
    UINT32 reg_pad_micom_17__pu: 1;    //     21
    UINT32 reg_pad_micom_17__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_16__ds0: 1;    //    24
    UINT32 reg_pad_micom_16__ds1: 1;    //    25
    UINT32 reg_pad_micom_16__ds2: 1;    //    26
    UINT32 reg_pad_micom_16__ds3: 1;    //    27
    UINT32 reg_pad_micom_16__pd: 1;    //     28
    UINT32 reg_pad_micom_16__pu: 1;    //     29
    UINT32 reg_pad_micom_16__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_woc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_uart0_txd__ds0: 1;    //    0
    UINT32 reg_pad_uart0_txd__ds1: 1;    //    1
    UINT32 reg_pad_uart0_txd__ds2: 1;    //    2
    UINT32 reg_pad_uart0_txd__ds3: 1;    //    3
    UINT32 reg_pad_uart0_txd__pd: 1;    //     4
    UINT32 reg_pad_uart0_txd__pu: 1;    //     5
    UINT32 reg_pad_uart0_txd__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_uart0_rxd__ds0: 1;    //    8
    UINT32 reg_pad_uart0_rxd__ds1: 1;    //    9
    UINT32 reg_pad_uart0_rxd__ds2: 1;    //   10
    UINT32 reg_pad_uart0_rxd__ds3: 1;    //   11
    UINT32 reg_pad_uart0_rxd__pd: 1;    //    12
    UINT32 reg_pad_uart0_rxd__pu: 1;    //    13
    UINT32 reg_pad_uart0_rxd__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_micom_sda__ds0: 1;    //   16
    UINT32 reg_pad_micom_sda__ds1: 1;    //   17
    UINT32 reg_pad_micom_sda__ds2: 1;    //   18
    UINT32 reg_pad_micom_sda__ds3: 1;    //   19
    UINT32 reg_pad_micom_sda__pd: 1;    //    20
    UINT32 reg_pad_micom_sda__pu: 1;    //    21
    UINT32 reg_pad_micom_sda__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_micom_scl__ds0: 1;    //   24
    UINT32 reg_pad_micom_scl__ds1: 1;    //   25
    UINT32 reg_pad_micom_scl__ds2: 1;    //   26
    UINT32 reg_pad_micom_scl__ds3: 1;    //   27
    UINT32 reg_pad_micom_scl__pd: 1;    //    28
    UINT32 reg_pad_micom_scl__pu: 1;    //    29
    UINT32 reg_pad_micom_scl__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_woc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_4_scl__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_4_scl__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_4_scl__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_4_scl__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_4_scl__pd: 1;    //    4
    UINT32 reg_pad_hdmi_4_scl__pu: 1;    //    5
    UINT32 reg_pad_hdmi_4_scl__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_cec__ds0: 1;    //     8
    UINT32 reg_pad_hdmi_cec__ds1: 1;    //     9
    UINT32 reg_pad_hdmi_cec__ds2: 1;    //    10
    UINT32 reg_pad_hdmi_cec__ds3: 1;    //    11
    UINT32 reg_pad_hdmi_cec__pd: 1;    //     12
    UINT32 reg_pad_hdmi_cec__pu: 1;    //     13
    UINT32 reg_pad_hdmi_cec__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_wov_pdm0_datain__ds0: 1;    //  16
    UINT32 reg_pad_wov_pdm0_datain__ds1: 1;    //  17
    UINT32 reg_pad_wov_pdm0_datain__ds2: 1;    //  18
    UINT32 reg_pad_wov_pdm0_datain__ds3: 1;    //  19
    UINT32 reg_pad_wov_pdm0_datain__pd: 1;    //  20
    UINT32 reg_pad_wov_pdm0_datain__pu: 1;    //  21
    UINT32 reg_pad_wov_pdm0_datain__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_wov_pdm_clkout__ds0: 1;    //  24
    UINT32 reg_pad_wov_pdm_clkout__ds1: 1;    //  25
    UINT32 reg_pad_wov_pdm_clkout__ds2: 1;    //  26
    UINT32 reg_pad_wov_pdm_clkout__ds3: 1;    //  27
    UINT32 reg_pad_wov_pdm_clkout__pd: 1;    //  28
    UINT32 reg_pad_wov_pdm_clkout__pu: 1;    //  29
    UINT32 reg_pad_wov_pdm_clkout__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_woc07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_4_5v_in__ds0: 1;    //  0
    UINT32 reg_pad_hdmi_4_5v_in__ds1: 1;    //  1
    UINT32 reg_pad_hdmi_4_5v_in__ds2: 1;    //  2
    UINT32 reg_pad_hdmi_4_5v_in__ds3: 1;    //  3
    UINT32 reg_pad_hdmi_4_5v_in__pd: 1;    //  4
    UINT32 reg_pad_hdmi_4_5v_in__pu: 1;    //  5
    UINT32 reg_pad_hdmi_4_5v_in__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_3_sda__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_3_sda__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_3_sda__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_3_sda__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_3_sda__pd: 1;    //   12
    UINT32 reg_pad_hdmi_3_sda__pu: 1;    //   13
    UINT32 reg_pad_hdmi_3_sda__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_3_scl__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_3_scl__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_3_scl__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_3_scl__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_3_scl__pd: 1;    //   20
    UINT32 reg_pad_hdmi_3_scl__pu: 1;    //   21
    UINT32 reg_pad_hdmi_3_scl__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_4_sda__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_4_sda__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_4_sda__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_4_sda__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_4_sda__pd: 1;    //   28
    UINT32 reg_pad_hdmi_4_sda__pu: 1;    //   29
    UINT32 reg_pad_hdmi_4_sda__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_woc08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pad_m0_ret_ctrl__ds0: 1;    //  1
    UINT32 reg_pad_m0_ret_ctrl__ds1: 1;    //  2
    UINT32 reg_pad_m0_ret_ctrl__ds2: 1;    //  3
    UINT32 reg_pad_m0_ret_ctrl__ds3: 1;    //  4
    UINT32 resvd01            :  1;    //      5 reserved
    UINT32 reg_pad_m0_ret_ctrl__st: 1;    //   6
    UINT32 resvd02            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_3_hpd__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_3_hpd__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_3_hpd__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_3_hpd__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_3_hpd__pd: 1;    //   12
    UINT32 reg_pad_hdmi_3_hpd__pu: 1;    //   13
    UINT32 reg_pad_hdmi_3_hpd__st: 1;    //   14
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_4_hpd__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_4_hpd__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_4_hpd__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_4_hpd__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_4_hpd__pd: 1;    //   20
    UINT32 reg_pad_hdmi_4_hpd__pu: 1;    //   21
    UINT32 reg_pad_hdmi_4_hpd__st: 1;    //   22
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_3_5v_in__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_3_5v_in__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_3_5v_in__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_3_5v_in__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_3_5v_in__pd: 1;    //  28
    UINT32 reg_pad_hdmi_3_5v_in__pu: 1;    //  29
    UINT32 reg_pad_hdmi_3_5v_in__st: 1;    //  30
    UINT32 resvd05            :  1;    //  31:31 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_woc09 ''
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
}CPU_IOMUX_CTRL_WOC_PAD_WOC09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_woc64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_07_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_06_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_05_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_04_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_03_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_02_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_01_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_00_mux_sel: 4;    //  31:28
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_woc65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_15_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_14_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_13_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_12_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_11_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_10_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_09_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_08_mux_sel: 4;    //  31:28
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC65_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_woc66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_uart0_txd_mux_sel: 4;    //  3:0
    UINT32 reg_pad_uart0_rxd_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_sda_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_scl_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_19_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_18_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_17_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_16_mux_sel: 4;    //  31:28
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC66_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_woc67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_4_5v_in_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_3_sda_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_3_scl_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_4_sda_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_4_scl_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_cec_mux_sel: 4;    //  23:20
    UINT32 reg_pad_wov_pdm0_datain_mux_sel: 4;    //  27:24
    UINT32 reg_pad_wov_pdm_clkout_mux_sel: 4;    //  31:28
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC67_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_woc68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_m0_ret_ctrl_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_3_hpd_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_4_hpd_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_3_5v_in_mux_sel: 4;    //  15:12
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC68_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x200    pad_woc128 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_prt3_hpd_oen: 1;    //     0
    UINT32 reg_edid_prt4_hpd_oen: 1;    //     1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}CPU_IOMUX_CTRL_WOC_PAD_WOC128_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_IOMUX_CTRL_WOC_PAD_WOC00_M23A0_T     pad_woc00  ;             // 0x0
    CPU_IOMUX_CTRL_WOC_PAD_WOC01_M23A0_T     pad_woc01  ;             // 0x4
    CPU_IOMUX_CTRL_WOC_PAD_WOC02_M23A0_T     pad_woc02  ;             // 0x8
    CPU_IOMUX_CTRL_WOC_PAD_WOC03_M23A0_T     pad_woc03  ;             // 0xC
    CPU_IOMUX_CTRL_WOC_PAD_WOC04_M23A0_T     pad_woc04  ;             // 0x10
    CPU_IOMUX_CTRL_WOC_PAD_WOC05_M23A0_T     pad_woc05  ;             // 0x14
    CPU_IOMUX_CTRL_WOC_PAD_WOC06_M23A0_T     pad_woc06  ;             // 0x18
    CPU_IOMUX_CTRL_WOC_PAD_WOC07_M23A0_T     pad_woc07  ;             // 0x1C
    CPU_IOMUX_CTRL_WOC_PAD_WOC08_M23A0_T     pad_woc08  ;             // 0x20
    CPU_IOMUX_CTRL_WOC_PAD_WOC09_M23A0_T     pad_woc09  ;             // 0x24
    UINT32                             _rsvd_00[54];            // 0x28 ~ 0xFC
    CPU_IOMUX_CTRL_WOC_PAD_WOC64_M23A0_T     pad_woc64  ;             // 0x100
    CPU_IOMUX_CTRL_WOC_PAD_WOC65_M23A0_T     pad_woc65  ;             // 0x104
    CPU_IOMUX_CTRL_WOC_PAD_WOC66_M23A0_T     pad_woc66  ;             // 0x108
    CPU_IOMUX_CTRL_WOC_PAD_WOC67_M23A0_T     pad_woc67  ;             // 0x10C
    CPU_IOMUX_CTRL_WOC_PAD_WOC68_M23A0_T     pad_woc68  ;             // 0x110
    UINT32                             _rsvd_01[59];            // 0x114 ~ 0x1FC
    CPU_IOMUX_CTRL_WOC_PAD_WOC128_M23A0_T    pad_woc128 ;             // 0x200
}CPU_IOMUX_CTRL_WOC_REG_M23A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_PAD_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

