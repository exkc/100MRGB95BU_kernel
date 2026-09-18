#ifndef _FUNC_IOMUX_VD0_REG_H_
#define _FUNC_IOMUX_VD0_REG_H_

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
    0xCE83_2000    pad_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio20__ds0       :  1,    //      0
    reg_pad_gpio20__ds1       :  1,    //      1
    reg_pad_gpio20__ds2       :  1,    //      2
    reg_pad_gpio20__ds3       :  1,    //      3
    reg_pad_gpio20__pd        :  1,    //      4
    reg_pad_gpio20__pu        :  1,    //      5
    reg_pad_gpio20__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio19__ds0       :  1,    //      8
    reg_pad_gpio19__ds1       :  1,    //      9
    reg_pad_gpio19__ds2       :  1,    //     10
    reg_pad_gpio19__ds3       :  1,    //     11
    reg_pad_gpio19__pd        :  1,    //     12
    reg_pad_gpio19__pu        :  1,    //     13
    reg_pad_gpio19__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio18__ds0       :  1,    //     16
    reg_pad_gpio18__ds1       :  1,    //     17
    reg_pad_gpio18__ds2       :  1,    //     18
    reg_pad_gpio18__ds3       :  1,    //     19
    reg_pad_gpio18__pd        :  1,    //     20
    reg_pad_gpio18__pu        :  1,    //     21
    reg_pad_gpio18__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio17__ds0       :  1,    //     24
    reg_pad_gpio17__ds1       :  1,    //     25
    reg_pad_gpio17__ds2       :  1,    //     26
    reg_pad_gpio17__ds3       :  1,    //     27
    reg_pad_gpio17__pd        :  1,    //     28
    reg_pad_gpio17__pu        :  1,    //     29
    reg_pad_gpio17__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2004    pad_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio24__ds0       :  1,    //      0
    reg_pad_gpio24__ds1       :  1,    //      1
    reg_pad_gpio24__ds2       :  1,    //      2
    reg_pad_gpio24__ds3       :  1,    //      3
    reg_pad_gpio24__pd        :  1,    //      4
    reg_pad_gpio24__pu        :  1,    //      5
    reg_pad_gpio24__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio23__ds0       :  1,    //      8
    reg_pad_gpio23__ds1       :  1,    //      9
    reg_pad_gpio23__ds2       :  1,    //     10
    reg_pad_gpio23__ds3       :  1,    //     11
    reg_pad_gpio23__pd        :  1,    //     12
    reg_pad_gpio23__pu        :  1,    //     13
    reg_pad_gpio23__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio22__ds0       :  1,    //     16
    reg_pad_gpio22__ds1       :  1,    //     17
    reg_pad_gpio22__ds2       :  1,    //     18
    reg_pad_gpio22__ds3       :  1,    //     19
    reg_pad_gpio22__pd        :  1,    //     20
    reg_pad_gpio22__pu        :  1,    //     21
    reg_pad_gpio22__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio21__ds0       :  1,    //     24
    reg_pad_gpio21__ds1       :  1,    //     25
    reg_pad_gpio21__ds2       :  1,    //     26
    reg_pad_gpio21__ds3       :  1,    //     27
    reg_pad_gpio21__pd        :  1,    //     28
    reg_pad_gpio21__pu        :  1,    //     29
    reg_pad_gpio21__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2008    pad_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqc__ds0       :  1,    //      0
    reg_pad_diseqc__ds1       :  1,    //      1
    reg_pad_diseqc__ds2       :  1,    //      2
    reg_pad_diseqc__ds3       :  1,    //      3
    reg_pad_diseqc__pd        :  1,    //      4
    reg_pad_diseqc__pu        :  1,    //      5
    reg_pad_diseqc__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_gpio27__ds0       :  1,    //      8
    reg_pad_gpio27__ds1       :  1,    //      9
    reg_pad_gpio27__ds2       :  1,    //     10
    reg_pad_gpio27__ds3       :  1,    //     11
    reg_pad_gpio27__pd        :  1,    //     12
    reg_pad_gpio27__pu        :  1,    //     13
    reg_pad_gpio27__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_gpio26__ds0       :  1,    //     16
    reg_pad_gpio26__ds1       :  1,    //     17
    reg_pad_gpio26__ds2       :  1,    //     18
    reg_pad_gpio26__ds3       :  1,    //     19
    reg_pad_gpio26__pd        :  1,    //     20
    reg_pad_gpio26__pu        :  1,    //     21
    reg_pad_gpio26__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio25__ds0       :  1,    //     24
    reg_pad_gpio25__ds1       :  1,    //     25
    reg_pad_gpio25__ds2       :  1,    //     26
    reg_pad_gpio25__ds3       :  1,    //     27
    reg_pad_gpio25__pd        :  1,    //     28
    reg_pad_gpio25__pu        :  1,    //     29
    reg_pad_gpio25__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_200C    pad_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ifagc__ds0        :  1,    //      0
    reg_pad_ifagc__ds1        :  1,    //      1
    reg_pad_ifagc__ds2        :  1,    //      2
    reg_pad_ifagc__ds3        :  1,    //      3
    reg_pad_ifagc__pd         :  1,    //      4
    reg_pad_ifagc__pu         :  1,    //      5
    reg_pad_ifagc__st         :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_fefctrl__ds0      :  1,    //      8
    reg_pad_fefctrl__ds1      :  1,    //      9
    reg_pad_fefctrl__ds2      :  1,    //     10
    reg_pad_fefctrl__ds3      :  1,    //     11
    reg_pad_fefctrl__pd       :  1,    //     12
    reg_pad_fefctrl__pu       :  1,    //     13
    reg_pad_fefctrl__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_diseqci__ds0      :  1,    //     16
    reg_pad_diseqci__ds1      :  1,    //     17
    reg_pad_diseqci__ds2      :  1,    //     18
    reg_pad_diseqci__ds3      :  1,    //     19
    reg_pad_diseqci__pd       :  1,    //     20
    reg_pad_diseqci__pu       :  1,    //     21
    reg_pad_diseqci__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_diseqc_cmd__ds0   :  1,    //     24
    reg_pad_diseqc_cmd__ds1   :  1,    //     25
    reg_pad_diseqc_cmd__ds2   :  1,    //     26
    reg_pad_diseqc_cmd__ds3   :  1,    //     27
    reg_pad_diseqc_cmd__pd    :  1,    //     28
    reg_pad_diseqc_cmd__pu    :  1,    //     29
    reg_pad_diseqc_cmd__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2010    pad_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_txd__ds0    :  1,    //      0
    reg_pad_uart1_txd__ds1    :  1,    //      1
    reg_pad_uart1_txd__ds2    :  1,    //      2
    reg_pad_uart1_txd__ds3    :  1,    //      3
    reg_pad_uart1_txd__pd     :  1,    //      4
    reg_pad_uart1_txd__pu     :  1,    //      5
    reg_pad_uart1_txd__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_uart0_txd__ds0    :  1,    //      8
    reg_pad_uart0_txd__ds1    :  1,    //      9
    reg_pad_uart0_txd__ds2    :  1,    //     10
    reg_pad_uart0_txd__ds3    :  1,    //     11
    reg_pad_uart0_txd__pd     :  1,    //     12
    reg_pad_uart0_txd__pu     :  1,    //     13
    reg_pad_uart0_txd__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_uart0_rxd__ds0    :  1,    //     16
    reg_pad_uart0_rxd__ds1    :  1,    //     17
    reg_pad_uart0_rxd__ds2    :  1,    //     18
    reg_pad_uart0_rxd__ds3    :  1,    //     19
    reg_pad_uart0_rxd__pd     :  1,    //     20
    reg_pad_uart0_rxd__pu     :  1,    //     21
    reg_pad_uart0_rxd__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ifagc_s__ds0      :  1,    //     24
    reg_pad_ifagc_s__ds1      :  1,    //     25
    reg_pad_ifagc_s__ds2      :  1,    //     26
    reg_pad_ifagc_s__ds3      :  1,    //     27
    reg_pad_ifagc_s__pd       :  1,    //     28
    reg_pad_ifagc_s__pu       :  1,    //     29
    reg_pad_ifagc_s__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2014    pad_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk_ext2__ds0 :  1,    //      0
    reg_pad_tpi_clk_ext2__ds1 :  1,    //      1
    reg_pad_tpi_clk_ext2__ds2 :  1,    //      2
    reg_pad_tpi_clk_ext2__ds3 :  1,    //      3
    reg_pad_tpi_clk_ext2__pd  :  1,    //      4
    reg_pad_tpi_clk_ext2__pu  :  1,    //      5
    reg_pad_tpi_clk_ext2__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_uart1_rts__ds0    :  1,    //      8
    reg_pad_uart1_rts__ds1    :  1,    //      9
    reg_pad_uart1_rts__ds2    :  1,    //     10
    reg_pad_uart1_rts__ds3    :  1,    //     11
    reg_pad_uart1_rts__pd     :  1,    //     12
    reg_pad_uart1_rts__pu     :  1,    //     13
    reg_pad_uart1_rts__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_uart1_cts__ds0    :  1,    //     16
    reg_pad_uart1_cts__ds1    :  1,    //     17
    reg_pad_uart1_cts__ds2    :  1,    //     18
    reg_pad_uart1_cts__ds3    :  1,    //     19
    reg_pad_uart1_cts__pd     :  1,    //     20
    reg_pad_uart1_cts__pu     :  1,    //     21
    reg_pad_uart1_cts__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_uart1_rxd__ds0    :  1,    //     24
    reg_pad_uart1_rxd__ds1    :  1,    //     25
    reg_pad_uart1_rxd__ds2    :  1,    //     26
    reg_pad_uart1_rxd__ds3    :  1,    //     27
    reg_pad_uart1_rxd__pd     :  1,    //     28
    reg_pad_uart1_rxd__pu     :  1,    //     29
    reg_pad_uart1_rxd__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2018    pad_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data3_ext2__ds0: 1,    //      0
    reg_pad_tpi_data3_ext2__ds1: 1,    //      1
    reg_pad_tpi_data3_ext2__ds2: 1,    //      2
    reg_pad_tpi_data3_ext2__ds3: 1,    //      3
    reg_pad_tpi_data3_ext2__pd:  1,    //      4
    reg_pad_tpi_data3_ext2__pu:  1,    //      5
    reg_pad_tpi_data3_ext2__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data2_ext2__ds0: 1,    //      8
    reg_pad_tpi_data2_ext2__ds1: 1,    //      9
    reg_pad_tpi_data2_ext2__ds2: 1,    //     10
    reg_pad_tpi_data2_ext2__ds3: 1,    //     11
    reg_pad_tpi_data2_ext2__pd:  1,    //     12
    reg_pad_tpi_data2_ext2__pu:  1,    //     13
    reg_pad_tpi_data2_ext2__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data1_ext2__ds0: 1,    //     16
    reg_pad_tpi_data1_ext2__ds1: 1,    //     17
    reg_pad_tpi_data1_ext2__ds2: 1,    //     18
    reg_pad_tpi_data1_ext2__ds3: 1,    //     19
    reg_pad_tpi_data1_ext2__pd:  1,    //     20
    reg_pad_tpi_data1_ext2__pu:  1,    //     21
    reg_pad_tpi_data1_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data0_ext2__ds0: 1,    //     24
    reg_pad_tpi_data0_ext2__ds1: 1,    //     25
    reg_pad_tpi_data0_ext2__ds2: 1,    //     26
    reg_pad_tpi_data0_ext2__ds3: 1,    //     27
    reg_pad_tpi_data0_ext2__pd:  1,    //     28
    reg_pad_tpi_data0_ext2__pu:  1,    //     29
    reg_pad_tpi_data0_ext2__st:  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_201C    pad_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_ext2__ds0: 1,    //      0
    reg_pad_tpi_data7_ext2__ds1: 1,    //      1
    reg_pad_tpi_data7_ext2__ds2: 1,    //      2
    reg_pad_tpi_data7_ext2__ds3: 1,    //      3
    reg_pad_tpi_data7_ext2__pd:  1,    //      4
    reg_pad_tpi_data7_ext2__pu:  1,    //      5
    reg_pad_tpi_data7_ext2__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data6_ext2__ds0: 1,    //      8
    reg_pad_tpi_data6_ext2__ds1: 1,    //      9
    reg_pad_tpi_data6_ext2__ds2: 1,    //     10
    reg_pad_tpi_data6_ext2__ds3: 1,    //     11
    reg_pad_tpi_data6_ext2__pd:  1,    //     12
    reg_pad_tpi_data6_ext2__pu:  1,    //     13
    reg_pad_tpi_data6_ext2__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data5_ext2__ds0: 1,    //     16
    reg_pad_tpi_data5_ext2__ds1: 1,    //     17
    reg_pad_tpi_data5_ext2__ds2: 1,    //     18
    reg_pad_tpi_data5_ext2__ds3: 1,    //     19
    reg_pad_tpi_data5_ext2__pd:  1,    //     20
    reg_pad_tpi_data5_ext2__pu:  1,    //     21
    reg_pad_tpi_data5_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data4_ext2__ds0: 1,    //     24
    reg_pad_tpi_data4_ext2__ds1: 1,    //     25
    reg_pad_tpi_data4_ext2__ds2: 1,    //     26
    reg_pad_tpi_data4_ext2__ds3: 1,    //     27
    reg_pad_tpi_data4_ext2__pd:  1,    //     28
    reg_pad_tpi_data4_ext2__pu:  1,    //     29
    reg_pad_tpi_data4_ext2__st:  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2020    pad_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_ext1__ds0: 1,    //      0
    reg_pad_tpi_data0_ext1__ds1: 1,    //      1
    reg_pad_tpi_data0_ext1__ds2: 1,    //      2
    reg_pad_tpi_data0_ext1__ds3: 1,    //      3
    reg_pad_tpi_data0_ext1__pd:  1,    //      4
    reg_pad_tpi_data0_ext1__pu:  1,    //      5
    reg_pad_tpi_data0_ext1__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_clk_ext1__ds0 :  1,    //      8
    reg_pad_tpi_clk_ext1__ds1 :  1,    //      9
    reg_pad_tpi_clk_ext1__ds2 :  1,    //     10
    reg_pad_tpi_clk_ext1__ds3 :  1,    //     11
    reg_pad_tpi_clk_ext1__pd  :  1,    //     12
    reg_pad_tpi_clk_ext1__pu  :  1,    //     13
    reg_pad_tpi_clk_ext1__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_val_ext2__ds0 :  1,    //     16
    reg_pad_tpi_val_ext2__ds1 :  1,    //     17
    reg_pad_tpi_val_ext2__ds2 :  1,    //     18
    reg_pad_tpi_val_ext2__ds3 :  1,    //     19
    reg_pad_tpi_val_ext2__pd  :  1,    //     20
    reg_pad_tpi_val_ext2__pu  :  1,    //     21
    reg_pad_tpi_val_ext2__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_sop_ext2__ds0 :  1,    //     24
    reg_pad_tpi_sop_ext2__ds1 :  1,    //     25
    reg_pad_tpi_sop_ext2__ds2 :  1,    //     26
    reg_pad_tpi_sop_ext2__ds3 :  1,    //     27
    reg_pad_tpi_sop_ext2__pd  :  1,    //     28
    reg_pad_tpi_sop_ext2__pu  :  1,    //     29
    reg_pad_tpi_sop_ext2__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2024    pad_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_ext1__ds0: 1,    //      0
    reg_pad_tpi_data4_ext1__ds1: 1,    //      1
    reg_pad_tpi_data4_ext1__ds2: 1,    //      2
    reg_pad_tpi_data4_ext1__ds3: 1,    //      3
    reg_pad_tpi_data4_ext1__pd:  1,    //      4
    reg_pad_tpi_data4_ext1__pu:  1,    //      5
    reg_pad_tpi_data4_ext1__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data3_ext1__ds0: 1,    //      8
    reg_pad_tpi_data3_ext1__ds1: 1,    //      9
    reg_pad_tpi_data3_ext1__ds2: 1,    //     10
    reg_pad_tpi_data3_ext1__ds3: 1,    //     11
    reg_pad_tpi_data3_ext1__pd:  1,    //     12
    reg_pad_tpi_data3_ext1__pu:  1,    //     13
    reg_pad_tpi_data3_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data2_ext1__ds0: 1,    //     16
    reg_pad_tpi_data2_ext1__ds1: 1,    //     17
    reg_pad_tpi_data2_ext1__ds2: 1,    //     18
    reg_pad_tpi_data2_ext1__ds3: 1,    //     19
    reg_pad_tpi_data2_ext1__pd:  1,    //     20
    reg_pad_tpi_data2_ext1__pu:  1,    //     21
    reg_pad_tpi_data2_ext1__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data1_ext1__ds0: 1,    //     24
    reg_pad_tpi_data1_ext1__ds1: 1,    //     25
    reg_pad_tpi_data1_ext1__ds2: 1,    //     26
    reg_pad_tpi_data1_ext1__ds3: 1,    //     27
    reg_pad_tpi_data1_ext1__pd:  1,    //     28
    reg_pad_tpi_data1_ext1__pu:  1,    //     29
    reg_pad_tpi_data1_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2028    pad_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_sop_ext1__ds0 :  1,    //      0
    reg_pad_tpi_sop_ext1__ds1 :  1,    //      1
    reg_pad_tpi_sop_ext1__ds2 :  1,    //      2
    reg_pad_tpi_sop_ext1__ds3 :  1,    //      3
    reg_pad_tpi_sop_ext1__pd  :  1,    //      4
    reg_pad_tpi_sop_ext1__pu  :  1,    //      5
    reg_pad_tpi_sop_ext1__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data7_ext1__ds0: 1,    //      8
    reg_pad_tpi_data7_ext1__ds1: 1,    //      9
    reg_pad_tpi_data7_ext1__ds2: 1,    //     10
    reg_pad_tpi_data7_ext1__ds3: 1,    //     11
    reg_pad_tpi_data7_ext1__pd:  1,    //     12
    reg_pad_tpi_data7_ext1__pu:  1,    //     13
    reg_pad_tpi_data7_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data6_ext1__ds0: 1,    //     16
    reg_pad_tpi_data6_ext1__ds1: 1,    //     17
    reg_pad_tpi_data6_ext1__ds2: 1,    //     18
    reg_pad_tpi_data6_ext1__ds3: 1,    //     19
    reg_pad_tpi_data6_ext1__pd:  1,    //     20
    reg_pad_tpi_data6_ext1__pu:  1,    //     21
    reg_pad_tpi_data6_ext1__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data5_ext1__ds0: 1,    //     24
    reg_pad_tpi_data5_ext1__ds1: 1,    //     25
    reg_pad_tpi_data5_ext1__ds2: 1,    //     26
    reg_pad_tpi_data5_ext1__ds3: 1,    //     27
    reg_pad_tpi_data5_ext1__pd:  1,    //     28
    reg_pad_tpi_data5_ext1__pu:  1,    //     29
    reg_pad_tpi_data5_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_VD0_PAD_VD010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_202C    pad_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_out__ds0: 1,    //      0
    reg_pad_edid_nisol_out__ds1: 1,    //      1
    reg_pad_edid_nisol_out__ds2: 1,    //      2
    reg_pad_edid_nisol_out__ds3: 1,    //      3
    reg_pad_edid_nisol_out__pd:  1,    //      4
    reg_pad_edid_nisol_out__pu:  1,    //      5
    reg_pad_edid_nisol_out__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_val_ext1__ds0 :  1,    //      8
    reg_pad_tpi_val_ext1__ds1 :  1,    //      9
    reg_pad_tpi_val_ext1__ds2 :  1,    //     10
    reg_pad_tpi_val_ext1__ds3 :  1,    //     11
    reg_pad_tpi_val_ext1__pd  :  1,    //     12
    reg_pad_tpi_val_ext1__pu  :  1,    //     13
    reg_pad_tpi_val_ext1__st  :  1,    //     14
                              : 17;    //  31:15 reserved
}FUNC_IOMUX_VD0_PAD_VD011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2100    pad_vd064 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio24_mux_sel    :  4,    //   3: 0
    reg_pad_gpio23_mux_sel    :  4,    //   7: 4
    reg_pad_gpio22_mux_sel    :  4,    //  11: 8
    reg_pad_gpio21_mux_sel    :  4,    //  15:12
    reg_pad_gpio20_mux_sel    :  4,    //  19:16
    reg_pad_gpio19_mux_sel    :  4,    //  23:20
    reg_pad_gpio18_mux_sel    :  4,    //  27:24
    reg_pad_gpio17_mux_sel    :  4;    //  31:28
}FUNC_IOMUX_VD0_PAD_VD064_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2104    pad_vd065 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ifagc_mux_sel     :  4,    //   3: 0
    reg_pad_fefctrl_mux_sel   :  4,    //   7: 4
    reg_pad_diseqci_mux_sel   :  4,    //  11: 8
    reg_pad_diseqc_cmd_mux_sel:  4,    //  15:12
    reg_pad_diseqc_mux_sel    :  4,    //  19:16
    reg_pad_gpio27_mux_sel    :  4,    //  23:20
    reg_pad_gpio26_mux_sel    :  4,    //  27:24
    reg_pad_gpio25_mux_sel    :  4;    //  31:28
}FUNC_IOMUX_VD0_PAD_VD065_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2108    pad_vd066 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk_ext2_mux_sel: 4,    //  3: 0
    reg_pad_uart1_rts_mux_sel :  4,    //   7: 4
    reg_pad_uart1_cts_mux_sel :  4,    //  11: 8
    reg_pad_uart1_rxd_mux_sel :  4,    //  15:12
    reg_pad_uart1_txd_mux_sel :  4,    //  19:16
    reg_pad_uart0_txd_mux_sel :  4,    //  23:20
    reg_pad_uart0_rxd_mux_sel :  4,    //  27:24
    reg_pad_ifagc_s_mux_sel   :  4;    //  31:28
}FUNC_IOMUX_VD0_PAD_VD066_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_210C    pad_vd067 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data6_ext2_mux_sel: 4,    //  7:4
    reg_pad_tpi_data5_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data4_ext2_mux_sel: 4,    //  15:12
    reg_pad_tpi_data3_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data2_ext2_mux_sel: 4,    //  23:20
    reg_pad_tpi_data1_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_data0_ext2_mux_sel: 4;    //  31:28
}FUNC_IOMUX_VD0_PAD_VD067_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2110    pad_vd068 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_ext1_mux_sel: 4,    //  3:0
    reg_pad_tpi_data3_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data2_ext1_mux_sel: 4,    //  11:8
    reg_pad_tpi_data1_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data0_ext1_mux_sel: 4,    //  19:16
    reg_pad_tpi_clk_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_val_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_sop_ext2_mux_sel: 4;    //  31:28
}FUNC_IOMUX_VD0_PAD_VD068_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2114    pad_vd069 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_out_mux_sel: 4,    //  3:0
    reg_pad_tpi_val_ext1_mux_sel: 4,    //  7: 4
    reg_pad_tpi_sop_ext1_mux_sel: 4,    //  11:8
    reg_pad_tpi_data7_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data6_ext1_mux_sel: 4,    //  19:16
    reg_pad_tpi_data5_ext1_mux_sel: 4,    //  23:20
                              :  8;    //  31:24 reserved
}FUNC_IOMUX_VD0_PAD_VD069_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_VD0_PAD_VD000_O22A0_T          pad_vd000  ;             // 0xCE83_2000
    FUNC_IOMUX_VD0_PAD_VD001_O22A0_T          pad_vd001  ;             // 0xCE83_2004
    FUNC_IOMUX_VD0_PAD_VD002_O22A0_T          pad_vd002  ;             // 0xCE83_2008
    FUNC_IOMUX_VD0_PAD_VD003_O22A0_T          pad_vd003  ;             // 0xCE83_200C
    FUNC_IOMUX_VD0_PAD_VD004_O22A0_T          pad_vd004  ;             // 0xCE83_2010
    FUNC_IOMUX_VD0_PAD_VD005_O22A0_T          pad_vd005  ;             // 0xCE83_2014
    FUNC_IOMUX_VD0_PAD_VD006_O22A0_T          pad_vd006  ;             // 0xCE83_2018
    FUNC_IOMUX_VD0_PAD_VD007_O22A0_T          pad_vd007  ;             // 0xCE83_201C
    FUNC_IOMUX_VD0_PAD_VD008_O22A0_T          pad_vd008  ;             // 0xCE83_2020
    FUNC_IOMUX_VD0_PAD_VD009_O22A0_T          pad_vd009  ;             // 0xCE83_2024
    FUNC_IOMUX_VD0_PAD_VD010_O22A0_T          pad_vd010  ;             // 0xCE83_2028
    FUNC_IOMUX_VD0_PAD_VD011_O22A0_T          pad_vd011  ;             // 0xCE83_202C
    UINT32                             _rsvd_00[52];            // 0xCE83_2030 ~ 0xCE83_20FC
    FUNC_IOMUX_VD0_PAD_VD064_O22A0_T          pad_vd064  ;             // 0xCE83_2100
    FUNC_IOMUX_VD0_PAD_VD065_O22A0_T          pad_vd065  ;             // 0xCE83_2104
    FUNC_IOMUX_VD0_PAD_VD066_O22A0_T          pad_vd066  ;             // 0xCE83_2108
    FUNC_IOMUX_VD0_PAD_VD067_O22A0_T          pad_vd067  ;             // 0xCE83_210C
    FUNC_IOMUX_VD0_PAD_VD068_O22A0_T          pad_vd068  ;             // 0xCE83_2110
    FUNC_IOMUX_VD0_PAD_VD069_O22A0_T          pad_vd069  ;             // 0xCE83_2114
}FUNC_IOMUX_VD0_REG_O22A0_T;
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

#define FUNC_IOMUX_VD0_PAD_VD000_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define FUNC_IOMUX_VD0_PAD_VD001_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define FUNC_IOMUX_VD0_PAD_VD002_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define FUNC_IOMUX_VD0_PAD_VD003_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define FUNC_IOMUX_VD0_PAD_VD004_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define FUNC_IOMUX_VD0_PAD_VD005_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define FUNC_IOMUX_VD0_PAD_VD006_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define FUNC_IOMUX_VD0_PAD_VD007_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define FUNC_IOMUX_VD0_PAD_VD008_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define FUNC_IOMUX_VD0_PAD_VD009_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define FUNC_IOMUX_VD0_PAD_VD010_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define FUNC_IOMUX_VD0_PAD_VD011_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define FUNC_IOMUX_VD0_PAD_VD064_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define FUNC_IOMUX_VD0_PAD_VD065_O22A0_T_OFF                       (BASEADDRESS+0x0104)
#define FUNC_IOMUX_VD0_PAD_VD066_O22A0_T_OFF                       (BASEADDRESS+0x0108)
#define FUNC_IOMUX_VD0_PAD_VD067_O22A0_T_OFF                       (BASEADDRESS+0x010C)
#define FUNC_IOMUX_VD0_PAD_VD068_O22A0_T_OFF                       (BASEADDRESS+0x0110)
#define FUNC_IOMUX_VD0_PAD_VD069_O22A0_T_OFF                       (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xCE83_2000    pad_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio20__ds0:  1;    //      0
    UINT32 reg_pad_gpio20__ds1:  1;    //      1
    UINT32 reg_pad_gpio20__ds2:  1;    //      2
    UINT32 reg_pad_gpio20__ds3:  1;    //      3
    UINT32 reg_pad_gpio20__pd :  1;    //      4
    UINT32 reg_pad_gpio20__pu :  1;    //      5
    UINT32 reg_pad_gpio20__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio19__ds0:  1;    //      8
    UINT32 reg_pad_gpio19__ds1:  1;    //      9
    UINT32 reg_pad_gpio19__ds2:  1;    //     10
    UINT32 reg_pad_gpio19__ds3:  1;    //     11
    UINT32 reg_pad_gpio19__pd :  1;    //     12
    UINT32 reg_pad_gpio19__pu :  1;    //     13
    UINT32 reg_pad_gpio19__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio18__ds0:  1;    //     16
    UINT32 reg_pad_gpio18__ds1:  1;    //     17
    UINT32 reg_pad_gpio18__ds2:  1;    //     18
    UINT32 reg_pad_gpio18__ds3:  1;    //     19
    UINT32 reg_pad_gpio18__pd :  1;    //     20
    UINT32 reg_pad_gpio18__pu :  1;    //     21
    UINT32 reg_pad_gpio18__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio17__ds0:  1;    //     24
    UINT32 reg_pad_gpio17__ds1:  1;    //     25
    UINT32 reg_pad_gpio17__ds2:  1;    //     26
    UINT32 reg_pad_gpio17__ds3:  1;    //     27
    UINT32 reg_pad_gpio17__pd :  1;    //     28
    UINT32 reg_pad_gpio17__pu :  1;    //     29
    UINT32 reg_pad_gpio17__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2004    pad_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio24__ds0:  1;    //      0
    UINT32 reg_pad_gpio24__ds1:  1;    //      1
    UINT32 reg_pad_gpio24__ds2:  1;    //      2
    UINT32 reg_pad_gpio24__ds3:  1;    //      3
    UINT32 reg_pad_gpio24__pd :  1;    //      4
    UINT32 reg_pad_gpio24__pu :  1;    //      5
    UINT32 reg_pad_gpio24__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio23__ds0:  1;    //      8
    UINT32 reg_pad_gpio23__ds1:  1;    //      9
    UINT32 reg_pad_gpio23__ds2:  1;    //     10
    UINT32 reg_pad_gpio23__ds3:  1;    //     11
    UINT32 reg_pad_gpio23__pd :  1;    //     12
    UINT32 reg_pad_gpio23__pu :  1;    //     13
    UINT32 reg_pad_gpio23__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio22__ds0:  1;    //     16
    UINT32 reg_pad_gpio22__ds1:  1;    //     17
    UINT32 reg_pad_gpio22__ds2:  1;    //     18
    UINT32 reg_pad_gpio22__ds3:  1;    //     19
    UINT32 reg_pad_gpio22__pd :  1;    //     20
    UINT32 reg_pad_gpio22__pu :  1;    //     21
    UINT32 reg_pad_gpio22__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio21__ds0:  1;    //     24
    UINT32 reg_pad_gpio21__ds1:  1;    //     25
    UINT32 reg_pad_gpio21__ds2:  1;    //     26
    UINT32 reg_pad_gpio21__ds3:  1;    //     27
    UINT32 reg_pad_gpio21__pd :  1;    //     28
    UINT32 reg_pad_gpio21__pu :  1;    //     29
    UINT32 reg_pad_gpio21__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2008    pad_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_diseqc__ds0:  1;    //      0
    UINT32 reg_pad_diseqc__ds1:  1;    //      1
    UINT32 reg_pad_diseqc__ds2:  1;    //      2
    UINT32 reg_pad_diseqc__ds3:  1;    //      3
    UINT32 reg_pad_diseqc__pd :  1;    //      4
    UINT32 reg_pad_diseqc__pu :  1;    //      5
    UINT32 reg_pad_diseqc__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_gpio27__ds0:  1;    //      8
    UINT32 reg_pad_gpio27__ds1:  1;    //      9
    UINT32 reg_pad_gpio27__ds2:  1;    //     10
    UINT32 reg_pad_gpio27__ds3:  1;    //     11
    UINT32 reg_pad_gpio27__pd :  1;    //     12
    UINT32 reg_pad_gpio27__pu :  1;    //     13
    UINT32 reg_pad_gpio27__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_gpio26__ds0:  1;    //     16
    UINT32 reg_pad_gpio26__ds1:  1;    //     17
    UINT32 reg_pad_gpio26__ds2:  1;    //     18
    UINT32 reg_pad_gpio26__ds3:  1;    //     19
    UINT32 reg_pad_gpio26__pd :  1;    //     20
    UINT32 reg_pad_gpio26__pu :  1;    //     21
    UINT32 reg_pad_gpio26__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio25__ds0:  1;    //     24
    UINT32 reg_pad_gpio25__ds1:  1;    //     25
    UINT32 reg_pad_gpio25__ds2:  1;    //     26
    UINT32 reg_pad_gpio25__ds3:  1;    //     27
    UINT32 reg_pad_gpio25__pd :  1;    //     28
    UINT32 reg_pad_gpio25__pu :  1;    //     29
    UINT32 reg_pad_gpio25__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_200C    pad_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ifagc__ds0 :  1;    //      0
    UINT32 reg_pad_ifagc__ds1 :  1;    //      1
    UINT32 reg_pad_ifagc__ds2 :  1;    //      2
    UINT32 reg_pad_ifagc__ds3 :  1;    //      3
    UINT32 reg_pad_ifagc__pd  :  1;    //      4
    UINT32 reg_pad_ifagc__pu  :  1;    //      5
    UINT32 reg_pad_ifagc__st  :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_fefctrl__ds0: 1;    //      8
    UINT32 reg_pad_fefctrl__ds1: 1;    //      9
    UINT32 reg_pad_fefctrl__ds2: 1;    //     10
    UINT32 reg_pad_fefctrl__ds3: 1;    //     11
    UINT32 reg_pad_fefctrl__pd:  1;    //     12
    UINT32 reg_pad_fefctrl__pu:  1;    //     13
    UINT32 reg_pad_fefctrl__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_diseqci__ds0: 1;    //     16
    UINT32 reg_pad_diseqci__ds1: 1;    //     17
    UINT32 reg_pad_diseqci__ds2: 1;    //     18
    UINT32 reg_pad_diseqci__ds3: 1;    //     19
    UINT32 reg_pad_diseqci__pd:  1;    //     20
    UINT32 reg_pad_diseqci__pu:  1;    //     21
    UINT32 reg_pad_diseqci__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_diseqc_cmd__ds0: 1;    //  24
    UINT32 reg_pad_diseqc_cmd__ds1: 1;    //  25
    UINT32 reg_pad_diseqc_cmd__ds2: 1;    //  26
    UINT32 reg_pad_diseqc_cmd__ds3: 1;    //  27
    UINT32 reg_pad_diseqc_cmd__pd: 1;    //   28
    UINT32 reg_pad_diseqc_cmd__pu: 1;    //   29
    UINT32 reg_pad_diseqc_cmd__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2010    pad_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_uart1_txd__ds0: 1;    //    0
    UINT32 reg_pad_uart1_txd__ds1: 1;    //    1
    UINT32 reg_pad_uart1_txd__ds2: 1;    //    2
    UINT32 reg_pad_uart1_txd__ds3: 1;    //    3
    UINT32 reg_pad_uart1_txd__pd: 1;    //     4
    UINT32 reg_pad_uart1_txd__pu: 1;    //     5
    UINT32 reg_pad_uart1_txd__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_uart0_txd__ds0: 1;    //    8
    UINT32 reg_pad_uart0_txd__ds1: 1;    //    9
    UINT32 reg_pad_uart0_txd__ds2: 1;    //   10
    UINT32 reg_pad_uart0_txd__ds3: 1;    //   11
    UINT32 reg_pad_uart0_txd__pd: 1;    //    12
    UINT32 reg_pad_uart0_txd__pu: 1;    //    13
    UINT32 reg_pad_uart0_txd__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_uart0_rxd__ds0: 1;    //   16
    UINT32 reg_pad_uart0_rxd__ds1: 1;    //   17
    UINT32 reg_pad_uart0_rxd__ds2: 1;    //   18
    UINT32 reg_pad_uart0_rxd__ds3: 1;    //   19
    UINT32 reg_pad_uart0_rxd__pd: 1;    //    20
    UINT32 reg_pad_uart0_rxd__pu: 1;    //    21
    UINT32 reg_pad_uart0_rxd__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ifagc_s__ds0: 1;    //     24
    UINT32 reg_pad_ifagc_s__ds1: 1;    //     25
    UINT32 reg_pad_ifagc_s__ds2: 1;    //     26
    UINT32 reg_pad_ifagc_s__ds3: 1;    //     27
    UINT32 reg_pad_ifagc_s__pd:  1;    //     28
    UINT32 reg_pad_ifagc_s__pu:  1;    //     29
    UINT32 reg_pad_ifagc_s__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2014    pad_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_clk_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_clk_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_clk_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_clk_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_clk_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_clk_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_clk_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_uart1_rts__ds0: 1;    //    8
    UINT32 reg_pad_uart1_rts__ds1: 1;    //    9
    UINT32 reg_pad_uart1_rts__ds2: 1;    //   10
    UINT32 reg_pad_uart1_rts__ds3: 1;    //   11
    UINT32 reg_pad_uart1_rts__pd: 1;    //    12
    UINT32 reg_pad_uart1_rts__pu: 1;    //    13
    UINT32 reg_pad_uart1_rts__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_uart1_cts__ds0: 1;    //   16
    UINT32 reg_pad_uart1_cts__ds1: 1;    //   17
    UINT32 reg_pad_uart1_cts__ds2: 1;    //   18
    UINT32 reg_pad_uart1_cts__ds3: 1;    //   19
    UINT32 reg_pad_uart1_cts__pd: 1;    //    20
    UINT32 reg_pad_uart1_cts__pu: 1;    //    21
    UINT32 reg_pad_uart1_cts__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_uart1_rxd__ds0: 1;    //   24
    UINT32 reg_pad_uart1_rxd__ds1: 1;    //   25
    UINT32 reg_pad_uart1_rxd__ds2: 1;    //   26
    UINT32 reg_pad_uart1_rxd__ds3: 1;    //   27
    UINT32 reg_pad_uart1_rxd__pd: 1;    //    28
    UINT32 reg_pad_uart1_rxd__pu: 1;    //    29
    UINT32 reg_pad_uart1_rxd__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2018    pad_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data3_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data3_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data3_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data3_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data3_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_data3_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_data3_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data2_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data2_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data2_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data2_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data2_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_data2_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_data2_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data1_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data1_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data1_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data1_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data1_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data1_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data1_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data0_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data0_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data0_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data0_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data0_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_data0_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_data0_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_201C    pad_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data7_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data7_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data7_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data7_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data7_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_data7_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_data7_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data6_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data6_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data6_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data6_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data6_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_data6_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_data6_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data5_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data5_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data5_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data5_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data5_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data5_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data5_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data4_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data4_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data4_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data4_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data4_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_data4_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_data4_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2020    pad_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data0_ext1__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data0_ext1__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data0_ext1__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data0_ext1__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data0_ext1__pd: 1;    //  4
    UINT32 reg_pad_tpi_data0_ext1__pu: 1;    //  5
    UINT32 reg_pad_tpi_data0_ext1__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_clk_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_clk_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_clk_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_clk_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_clk_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_clk_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_clk_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_val_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_val_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_val_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_val_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_val_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_val_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_val_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_sop_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_sop_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_sop_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_sop_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_sop_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_sop_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_sop_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2024    pad_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data4_ext1__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data4_ext1__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data4_ext1__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data4_ext1__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data4_ext1__pd: 1;    //  4
    UINT32 reg_pad_tpi_data4_ext1__pu: 1;    //  5
    UINT32 reg_pad_tpi_data4_ext1__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data3_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data3_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data3_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data3_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data3_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data3_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data3_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data2_ext1__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data2_ext1__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data2_ext1__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data2_ext1__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data2_ext1__pd: 1;    //  20
    UINT32 reg_pad_tpi_data2_ext1__pu: 1;    //  21
    UINT32 reg_pad_tpi_data2_ext1__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data1_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data1_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data1_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data1_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data1_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data1_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data1_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2028    pad_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_sop_ext1__ds0: 1;    //  0
    UINT32 reg_pad_tpi_sop_ext1__ds1: 1;    //  1
    UINT32 reg_pad_tpi_sop_ext1__ds2: 1;    //  2
    UINT32 reg_pad_tpi_sop_ext1__ds3: 1;    //  3
    UINT32 reg_pad_tpi_sop_ext1__pd: 1;    //  4
    UINT32 reg_pad_tpi_sop_ext1__pu: 1;    //  5
    UINT32 reg_pad_tpi_sop_ext1__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data7_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data7_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data7_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data7_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data7_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data7_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data7_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data6_ext1__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data6_ext1__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data6_ext1__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data6_ext1__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data6_ext1__pd: 1;    //  20
    UINT32 reg_pad_tpi_data6_ext1__pu: 1;    //  21
    UINT32 reg_pad_tpi_data6_ext1__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data5_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data5_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data5_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data5_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data5_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data5_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data5_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_202C    pad_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edid_nisol_out__ds0: 1;    //  0
    UINT32 reg_pad_edid_nisol_out__ds1: 1;    //  1
    UINT32 reg_pad_edid_nisol_out__ds2: 1;    //  2
    UINT32 reg_pad_edid_nisol_out__ds3: 1;    //  3
    UINT32 reg_pad_edid_nisol_out__pd: 1;    //  4
    UINT32 reg_pad_edid_nisol_out__pu: 1;    //  5
    UINT32 reg_pad_edid_nisol_out__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_val_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_val_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_val_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_val_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_val_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_val_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_val_ext1__st: 1;    //  14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2100    pad_vd064 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio24_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio23_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio22_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio21_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio20_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio19_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio18_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio17_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_VD0_PAD_VD064_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2104    pad_vd065 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ifagc_mux_sel: 4;    //  3: 0
    UINT32 reg_pad_fefctrl_mux_sel: 4;    //  7:4
    UINT32 reg_pad_diseqci_mux_sel: 4;    //  11:8
    UINT32 reg_pad_diseqc_cmd_mux_sel: 4;    //  15:12
    UINT32 reg_pad_diseqc_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio27_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio26_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio25_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_VD0_PAD_VD065_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2108    pad_vd066 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_clk_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_uart1_rts_mux_sel: 4;    //  7:4
    UINT32 reg_pad_uart1_cts_mux_sel: 4;    //  11:8
    UINT32 reg_pad_uart1_rxd_mux_sel: 4;    //  15:12
    UINT32 reg_pad_uart1_txd_mux_sel: 4;    //  19:16
    UINT32 reg_pad_uart0_txd_mux_sel: 4;    //  23:20
    UINT32 reg_pad_uart0_rxd_mux_sel: 4;    //  27:24
    UINT32 reg_pad_ifagc_s_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_VD0_PAD_VD066_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_210C    pad_vd067 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data7_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data6_ext2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data5_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data4_ext2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data3_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data2_ext2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data1_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data0_ext2_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_VD0_PAD_VD067_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2110    pad_vd068 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data4_ext1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data3_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data2_ext1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data1_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data0_ext1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_clk_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_val_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_sop_ext2_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_VD0_PAD_VD068_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE83_2114    pad_vd069 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edid_nisol_out_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_val_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_sop_ext1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data7_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data6_ext1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data5_ext1_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}FUNC_IOMUX_VD0_PAD_VD069_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_VD0_PAD_VD000_O22A0_T          pad_vd000  ;             // 0xCE83_2000
    FUNC_IOMUX_VD0_PAD_VD001_O22A0_T          pad_vd001  ;             // 0xCE83_2004
    FUNC_IOMUX_VD0_PAD_VD002_O22A0_T          pad_vd002  ;             // 0xCE83_2008
    FUNC_IOMUX_VD0_PAD_VD003_O22A0_T          pad_vd003  ;             // 0xCE83_200C
    FUNC_IOMUX_VD0_PAD_VD004_O22A0_T          pad_vd004  ;             // 0xCE83_2010
    FUNC_IOMUX_VD0_PAD_VD005_O22A0_T          pad_vd005  ;             // 0xCE83_2014
    FUNC_IOMUX_VD0_PAD_VD006_O22A0_T          pad_vd006  ;             // 0xCE83_2018
    FUNC_IOMUX_VD0_PAD_VD007_O22A0_T          pad_vd007  ;             // 0xCE83_201C
    FUNC_IOMUX_VD0_PAD_VD008_O22A0_T          pad_vd008  ;             // 0xCE83_2020
    FUNC_IOMUX_VD0_PAD_VD009_O22A0_T          pad_vd009  ;             // 0xCE83_2024
    FUNC_IOMUX_VD0_PAD_VD010_O22A0_T          pad_vd010  ;             // 0xCE83_2028
    FUNC_IOMUX_VD0_PAD_VD011_O22A0_T          pad_vd011  ;             // 0xCE83_202C
    UINT32                             _rsvd_00[52];            // 0xCE83_2030 ~ 0xCE83_20FC
    FUNC_IOMUX_VD0_PAD_VD064_O22A0_T          pad_vd064  ;             // 0xCE83_2100
    FUNC_IOMUX_VD0_PAD_VD065_O22A0_T          pad_vd065  ;             // 0xCE83_2104
    FUNC_IOMUX_VD0_PAD_VD066_O22A0_T          pad_vd066  ;             // 0xCE83_2108
    FUNC_IOMUX_VD0_PAD_VD067_O22A0_T          pad_vd067  ;             // 0xCE83_210C
    FUNC_IOMUX_VD0_PAD_VD068_O22A0_T          pad_vd068  ;             // 0xCE83_2110
    FUNC_IOMUX_VD0_PAD_VD069_O22A0_T          pad_vd069  ;             // 0xCE83_2114
}FUNC_IOMUX_VD0_REG_O22A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_VD0_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

