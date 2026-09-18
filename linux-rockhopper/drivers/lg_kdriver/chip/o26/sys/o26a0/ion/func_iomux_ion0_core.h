#ifndef _FUNC_IOMUX_ION0_CORE_REG_H_
#define _FUNC_IOMUX_ION0_CORE_REG_H_

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
    0xCA33_2000    pad_ion0_core00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl4__ds0         :  1,    //      0
    reg_pad_scl4__ds1         :  1,    //      1
    reg_pad_scl4__ds2         :  1,    //      2
    reg_pad_scl4__ds3         :  1,    //      3
    reg_pad_scl4__pd          :  1,    //      4
    reg_pad_scl4__pu          :  1,    //      5
    reg_pad_scl4__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda4__ds0         :  1,    //      8
    reg_pad_sda4__ds1         :  1,    //      9
    reg_pad_sda4__ds2         :  1,    //     10
    reg_pad_sda4__ds3         :  1,    //     11
    reg_pad_sda4__pd          :  1,    //     12
    reg_pad_sda4__pu          :  1,    //     13
    reg_pad_sda4__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl5__ds0         :  1,    //     16
    reg_pad_scl5__ds1         :  1,    //     17
    reg_pad_scl5__ds2         :  1,    //     18
    reg_pad_scl5__ds3         :  1,    //     19
    reg_pad_scl5__pd          :  1,    //     20
    reg_pad_scl5__pu          :  1,    //     21
    reg_pad_scl5__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda5__ds0         :  1,    //     24
    reg_pad_sda5__ds1         :  1,    //     25
    reg_pad_sda5__ds2         :  1,    //     26
    reg_pad_sda5__ds3         :  1,    //     27
    reg_pad_sda5__pd          :  1,    //     28
    reg_pad_sda5__pu          :  1,    //     29
    reg_pad_sda5__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2004    pad_ion0_core01 ''
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
    reg_pad_sda2__ds0         :  1,    //      8
    reg_pad_sda2__ds1         :  1,    //      9
    reg_pad_sda2__ds2         :  1,    //     10
    reg_pad_sda2__ds3         :  1,    //     11
    reg_pad_sda2__pd          :  1,    //     12
    reg_pad_sda2__pu          :  1,    //     13
    reg_pad_sda2__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl3__ds0         :  1,    //     16
    reg_pad_scl3__ds1         :  1,    //     17
    reg_pad_scl3__ds2         :  1,    //     18
    reg_pad_scl3__ds3         :  1,    //     19
    reg_pad_scl3__pd          :  1,    //     20
    reg_pad_scl3__pu          :  1,    //     21
    reg_pad_scl3__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda3__ds0         :  1,    //     24
    reg_pad_sda3__ds1         :  1,    //     25
    reg_pad_sda3__ds2         :  1,    //     26
    reg_pad_sda3__ds3         :  1,    //     27
    reg_pad_sda3__pd          :  1,    //     28
    reg_pad_sda3__pu          :  1,    //     29
    reg_pad_sda3__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2008    pad_ion0_core02 ''
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
    reg_pad_sda0__ds0         :  1,    //      8
    reg_pad_sda0__ds1         :  1,    //      9
    reg_pad_sda0__ds2         :  1,    //     10
    reg_pad_sda0__ds3         :  1,    //     11
    reg_pad_sda0__pd          :  1,    //     12
    reg_pad_sda0__pu          :  1,    //     13
    reg_pad_sda0__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl1__ds0         :  1,    //     16
    reg_pad_scl1__ds1         :  1,    //     17
    reg_pad_scl1__ds2         :  1,    //     18
    reg_pad_scl1__ds3         :  1,    //     19
    reg_pad_scl1__pd          :  1,    //     20
    reg_pad_scl1__pu          :  1,    //     21
    reg_pad_scl1__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda1__ds0         :  1,    //     24
    reg_pad_sda1__ds1         :  1,    //     25
    reg_pad_sda1__ds2         :  1,    //     26
    reg_pad_sda1__ds3         :  1,    //     27
    reg_pad_sda1__pd          :  1,    //     28
    reg_pad_sda1__pu          :  1,    //     29
    reg_pad_sda1__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_200C    pad_ion0_core03 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2010    pad_ion0_core04 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2014    pad_ion0_core05 ''
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
    reg_pad_tpi_sop_ext2__ds0 :  1,    //      8
    reg_pad_tpi_sop_ext2__ds1 :  1,    //      9
    reg_pad_tpi_sop_ext2__ds2 :  1,    //     10
    reg_pad_tpi_sop_ext2__ds3 :  1,    //     11
    reg_pad_tpi_sop_ext2__pd  :  1,    //     12
    reg_pad_tpi_sop_ext2__pu  :  1,    //     13
    reg_pad_tpi_sop_ext2__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_val_ext2__ds0 :  1,    //     16
    reg_pad_tpi_val_ext2__ds1 :  1,    //     17
    reg_pad_tpi_val_ext2__ds2 :  1,    //     18
    reg_pad_tpi_val_ext2__ds3 :  1,    //     19
    reg_pad_tpi_val_ext2__pd  :  1,    //     20
    reg_pad_tpi_val_ext2__pu  :  1,    //     21
    reg_pad_tpi_val_ext2__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_clk_ext2__ds0 :  1,    //     24
    reg_pad_tpi_clk_ext2__ds1 :  1,    //     25
    reg_pad_tpi_clk_ext2__ds2 :  1,    //     26
    reg_pad_tpi_clk_ext2__ds3 :  1,    //     27
    reg_pad_tpi_clk_ext2__pd  :  1,    //     28
    reg_pad_tpi_clk_ext2__pu  :  1,    //     29
    reg_pad_tpi_clk_ext2__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2018    pad_ion0_core06 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_201C    pad_ion0_core07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk_ext1__ds0 :  1,    //      0
    reg_pad_tpi_clk_ext1__ds1 :  1,    //      1
    reg_pad_tpi_clk_ext1__ds2 :  1,    //      2
    reg_pad_tpi_clk_ext1__ds3 :  1,    //      3
    reg_pad_tpi_clk_ext1__pd  :  1,    //      4
    reg_pad_tpi_clk_ext1__pu  :  1,    //      5
    reg_pad_tpi_clk_ext1__st  :  1,    //      6
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2020    pad_ion0_core08 ''
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
    reg_pad_hdmi_4_5v_in__ds0 :  1,    //      8
    reg_pad_hdmi_4_5v_in__ds1 :  1,    //      9
    reg_pad_hdmi_4_5v_in__ds2 :  1,    //     10
    reg_pad_hdmi_4_5v_in__ds3 :  1,    //     11
    reg_pad_hdmi_4_5v_in__pd  :  1,    //     12
    reg_pad_hdmi_4_5v_in__pu  :  1,    //     13
    reg_pad_hdmi_4_5v_in__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_sop_ext1__ds0 :  1,    //     16
    reg_pad_tpi_sop_ext1__ds1 :  1,    //     17
    reg_pad_tpi_sop_ext1__ds2 :  1,    //     18
    reg_pad_tpi_sop_ext1__ds3 :  1,    //     19
    reg_pad_tpi_sop_ext1__pd  :  1,    //     20
    reg_pad_tpi_sop_ext1__pu  :  1,    //     21
    reg_pad_tpi_sop_ext1__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_val_ext1__ds0 :  1,    //     24
    reg_pad_tpi_val_ext1__ds1 :  1,    //     25
    reg_pad_tpi_val_ext1__ds2 :  1,    //     26
    reg_pad_tpi_val_ext1__ds3 :  1,    //     27
    reg_pad_tpi_val_ext1__pd  :  1,    //     28
    reg_pad_tpi_val_ext1__pu  :  1,    //     29
    reg_pad_tpi_val_ext1__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2024    pad_ion0_core09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_scl__ds0   :  1,    //      0
    reg_pad_hdmi_3_scl__ds1   :  1,    //      1
    reg_pad_hdmi_3_scl__ds2   :  1,    //      2
    reg_pad_hdmi_3_scl__ds3   :  1,    //      3
    reg_pad_hdmi_3_scl__pd    :  1,    //      4
    reg_pad_hdmi_3_scl__pu    :  1,    //      5
    reg_pad_hdmi_3_scl__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_3_5v_in__ds0 :  1,    //      8
    reg_pad_hdmi_3_5v_in__ds1 :  1,    //      9
    reg_pad_hdmi_3_5v_in__ds2 :  1,    //     10
    reg_pad_hdmi_3_5v_in__ds3 :  1,    //     11
    reg_pad_hdmi_3_5v_in__pd  :  1,    //     12
    reg_pad_hdmi_3_5v_in__pu  :  1,    //     13
    reg_pad_hdmi_3_5v_in__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_4_hpd__ds0   :  1,    //     16
    reg_pad_hdmi_4_hpd__ds1   :  1,    //     17
    reg_pad_hdmi_4_hpd__ds2   :  1,    //     18
    reg_pad_hdmi_4_hpd__ds3   :  1,    //     19
    reg_pad_hdmi_4_hpd__pd    :  1,    //     20
    reg_pad_hdmi_4_hpd__pu    :  1,    //     21
    reg_pad_hdmi_4_hpd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_4_sda__ds0   :  1,    //     24
    reg_pad_hdmi_4_sda__ds1   :  1,    //     25
    reg_pad_hdmi_4_sda__ds2   :  1,    //     26
    reg_pad_hdmi_4_sda__ds3   :  1,    //     27
    reg_pad_hdmi_4_sda__pd    :  1,    //     28
    reg_pad_hdmi_4_sda__pu    :  1,    //     29
    reg_pad_hdmi_4_sda__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2028    pad_ion0_core10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_scl__ds0   :  1,    //      0
    reg_pad_hdmi_2_scl__ds1   :  1,    //      1
    reg_pad_hdmi_2_scl__ds2   :  1,    //      2
    reg_pad_hdmi_2_scl__ds3   :  1,    //      3
    reg_pad_hdmi_2_scl__pd    :  1,    //      4
    reg_pad_hdmi_2_scl__pu    :  1,    //      5
    reg_pad_hdmi_2_scl__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_2_5v_in__ds0 :  1,    //      8
    reg_pad_hdmi_2_5v_in__ds1 :  1,    //      9
    reg_pad_hdmi_2_5v_in__ds2 :  1,    //     10
    reg_pad_hdmi_2_5v_in__ds3 :  1,    //     11
    reg_pad_hdmi_2_5v_in__pd  :  1,    //     12
    reg_pad_hdmi_2_5v_in__pu  :  1,    //     13
    reg_pad_hdmi_2_5v_in__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_3_hpd__ds0   :  1,    //     16
    reg_pad_hdmi_3_hpd__ds1   :  1,    //     17
    reg_pad_hdmi_3_hpd__ds2   :  1,    //     18
    reg_pad_hdmi_3_hpd__ds3   :  1,    //     19
    reg_pad_hdmi_3_hpd__pd    :  1,    //     20
    reg_pad_hdmi_3_hpd__pu    :  1,    //     21
    reg_pad_hdmi_3_hpd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_3_sda__ds0   :  1,    //     24
    reg_pad_hdmi_3_sda__ds1   :  1,    //     25
    reg_pad_hdmi_3_sda__ds2   :  1,    //     26
    reg_pad_hdmi_3_sda__ds3   :  1,    //     27
    reg_pad_hdmi_3_sda__pd    :  1,    //     28
    reg_pad_hdmi_3_sda__pu    :  1,    //     29
    reg_pad_hdmi_3_sda__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_202C    pad_ion0_core11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_scl__ds0   :  1,    //      0
    reg_pad_hdmi_1_scl__ds1   :  1,    //      1
    reg_pad_hdmi_1_scl__ds2   :  1,    //      2
    reg_pad_hdmi_1_scl__ds3   :  1,    //      3
    reg_pad_hdmi_1_scl__pd    :  1,    //      4
    reg_pad_hdmi_1_scl__pu    :  1,    //      5
    reg_pad_hdmi_1_scl__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_1_5v_in__ds0 :  1,    //      8
    reg_pad_hdmi_1_5v_in__ds1 :  1,    //      9
    reg_pad_hdmi_1_5v_in__ds2 :  1,    //     10
    reg_pad_hdmi_1_5v_in__ds3 :  1,    //     11
    reg_pad_hdmi_1_5v_in__pd  :  1,    //     12
    reg_pad_hdmi_1_5v_in__pu  :  1,    //     13
    reg_pad_hdmi_1_5v_in__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_2_hpd__ds0   :  1,    //     16
    reg_pad_hdmi_2_hpd__ds1   :  1,    //     17
    reg_pad_hdmi_2_hpd__ds2   :  1,    //     18
    reg_pad_hdmi_2_hpd__ds3   :  1,    //     19
    reg_pad_hdmi_2_hpd__pd    :  1,    //     20
    reg_pad_hdmi_2_hpd__pu    :  1,    //     21
    reg_pad_hdmi_2_hpd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_2_sda__ds0   :  1,    //     24
    reg_pad_hdmi_2_sda__ds1   :  1,    //     25
    reg_pad_hdmi_2_sda__ds2   :  1,    //     26
    reg_pad_hdmi_2_sda__ds3   :  1,    //     27
    reg_pad_hdmi_2_sda__pd    :  1,    //     28
    reg_pad_hdmi_2_sda__pu    :  1,    //     29
    reg_pad_hdmi_2_sda__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2030    pad_ion0_core12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_det3__ds0    :  1,    //      0
    reg_pad_hdmi_det3__ds1    :  1,    //      1
    reg_pad_hdmi_det3__ds2    :  1,    //      2
    reg_pad_hdmi_det3__ds3    :  1,    //      3
    reg_pad_hdmi_det3__pd     :  1,    //      4
    reg_pad_hdmi_det3__pu     :  1,    //      5
    reg_pad_hdmi_det3__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_det4__ds0    :  1,    //      8
    reg_pad_hdmi_det4__ds1    :  1,    //      9
    reg_pad_hdmi_det4__ds2    :  1,    //     10
    reg_pad_hdmi_det4__ds3    :  1,    //     11
    reg_pad_hdmi_det4__pd     :  1,    //     12
    reg_pad_hdmi_det4__pu     :  1,    //     13
    reg_pad_hdmi_det4__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_1_hpd__ds0   :  1,    //     16
    reg_pad_hdmi_1_hpd__ds1   :  1,    //     17
    reg_pad_hdmi_1_hpd__ds2   :  1,    //     18
    reg_pad_hdmi_1_hpd__ds3   :  1,    //     19
    reg_pad_hdmi_1_hpd__pd    :  1,    //     20
    reg_pad_hdmi_1_hpd__pu    :  1,    //     21
    reg_pad_hdmi_1_hpd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_1_sda__ds0   :  1,    //     24
    reg_pad_hdmi_1_sda__ds1   :  1,    //     25
    reg_pad_hdmi_1_sda__ds2   :  1,    //     26
    reg_pad_hdmi_1_sda__ds3   :  1,    //     27
    reg_pad_hdmi_1_sda__pd    :  1,    //     28
    reg_pad_hdmi_1_sda__pu    :  1,    //     29
    reg_pad_hdmi_1_sda__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2034    pad_ion0_core13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio01__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio01__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio01__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio01__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio01__pd: 1,    //      4
    reg_pad_ion0_aux_gpio01__pu: 1,    //      5
    reg_pad_ion0_aux_gpio01__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio00__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio00__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio00__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio00__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio00__pd: 1,    //     12
    reg_pad_ion0_aux_gpio00__pu: 1,    //     13
    reg_pad_ion0_aux_gpio00__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_det1__ds0    :  1,    //     16
    reg_pad_hdmi_det1__ds1    :  1,    //     17
    reg_pad_hdmi_det1__ds2    :  1,    //     18
    reg_pad_hdmi_det1__ds3    :  1,    //     19
    reg_pad_hdmi_det1__pd     :  1,    //     20
    reg_pad_hdmi_det1__pu     :  1,    //     21
    reg_pad_hdmi_det1__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_det2__ds0    :  1,    //     24
    reg_pad_hdmi_det2__ds1    :  1,    //     25
    reg_pad_hdmi_det2__ds2    :  1,    //     26
    reg_pad_hdmi_det2__ds3    :  1,    //     27
    reg_pad_hdmi_det2__pd     :  1,    //     28
    reg_pad_hdmi_det2__pu     :  1,    //     29
    reg_pad_hdmi_det2__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2038    pad_ion0_core14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio05__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio05__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio05__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio05__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio05__pd: 1,    //      4
    reg_pad_ion0_aux_gpio05__pu: 1,    //      5
    reg_pad_ion0_aux_gpio05__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio04__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio04__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio04__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio04__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio04__pd: 1,    //     12
    reg_pad_ion0_aux_gpio04__pu: 1,    //     13
    reg_pad_ion0_aux_gpio04__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ion0_aux_gpio03__ds0: 1,    //    16
    reg_pad_ion0_aux_gpio03__ds1: 1,    //    17
    reg_pad_ion0_aux_gpio03__ds2: 1,    //    18
    reg_pad_ion0_aux_gpio03__ds3: 1,    //    19
    reg_pad_ion0_aux_gpio03__pd: 1,    //     20
    reg_pad_ion0_aux_gpio03__pu: 1,    //     21
    reg_pad_ion0_aux_gpio03__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ion0_aux_gpio02__ds0: 1,    //    24
    reg_pad_ion0_aux_gpio02__ds1: 1,    //    25
    reg_pad_ion0_aux_gpio02__ds2: 1,    //    26
    reg_pad_ion0_aux_gpio02__ds3: 1,    //    27
    reg_pad_ion0_aux_gpio02__pd: 1,    //     28
    reg_pad_ion0_aux_gpio02__pu: 1,    //     29
    reg_pad_ion0_aux_gpio02__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_203C    pad_ion0_core15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio09__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio09__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio09__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio09__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio09__pd: 1,    //      4
    reg_pad_ion0_aux_gpio09__pu: 1,    //      5
    reg_pad_ion0_aux_gpio09__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio08__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio08__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio08__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio08__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio08__pd: 1,    //     12
    reg_pad_ion0_aux_gpio08__pu: 1,    //     13
    reg_pad_ion0_aux_gpio08__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ion0_aux_gpio07__ds0: 1,    //    16
    reg_pad_ion0_aux_gpio07__ds1: 1,    //    17
    reg_pad_ion0_aux_gpio07__ds2: 1,    //    18
    reg_pad_ion0_aux_gpio07__ds3: 1,    //    19
    reg_pad_ion0_aux_gpio07__pd: 1,    //     20
    reg_pad_ion0_aux_gpio07__pu: 1,    //     21
    reg_pad_ion0_aux_gpio07__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ion0_aux_gpio06__ds0: 1,    //    24
    reg_pad_ion0_aux_gpio06__ds1: 1,    //    25
    reg_pad_ion0_aux_gpio06__ds2: 1,    //    26
    reg_pad_ion0_aux_gpio06__ds3: 1,    //    27
    reg_pad_ion0_aux_gpio06__pd: 1,    //     28
    reg_pad_ion0_aux_gpio06__pu: 1,    //     29
    reg_pad_ion0_aux_gpio06__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2040    pad_ion0_core16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio13__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio13__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio13__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio13__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio13__pd: 1,    //      4
    reg_pad_ion0_aux_gpio13__pu: 1,    //      5
    reg_pad_ion0_aux_gpio13__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio12__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio12__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio12__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio12__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio12__pd: 1,    //     12
    reg_pad_ion0_aux_gpio12__pu: 1,    //     13
    reg_pad_ion0_aux_gpio12__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ion0_aux_gpio11__ds0: 1,    //    16
    reg_pad_ion0_aux_gpio11__ds1: 1,    //    17
    reg_pad_ion0_aux_gpio11__ds2: 1,    //    18
    reg_pad_ion0_aux_gpio11__ds3: 1,    //    19
    reg_pad_ion0_aux_gpio11__pd: 1,    //     20
    reg_pad_ion0_aux_gpio11__pu: 1,    //     21
    reg_pad_ion0_aux_gpio11__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ion0_aux_gpio10__ds0: 1,    //    24
    reg_pad_ion0_aux_gpio10__ds1: 1,    //    25
    reg_pad_ion0_aux_gpio10__ds2: 1,    //    26
    reg_pad_ion0_aux_gpio10__ds3: 1,    //    27
    reg_pad_ion0_aux_gpio10__pd: 1,    //     28
    reg_pad_ion0_aux_gpio10__pu: 1,    //     29
    reg_pad_ion0_aux_gpio10__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2044    pad_ion0_core17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio17__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio17__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio17__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio17__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio17__pd: 1,    //      4
    reg_pad_ion0_aux_gpio17__pu: 1,    //      5
    reg_pad_ion0_aux_gpio17__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio16__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio16__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio16__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio16__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio16__pd: 1,    //     12
    reg_pad_ion0_aux_gpio16__pu: 1,    //     13
    reg_pad_ion0_aux_gpio16__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ion0_aux_gpio15__ds0: 1,    //    16
    reg_pad_ion0_aux_gpio15__ds1: 1,    //    17
    reg_pad_ion0_aux_gpio15__ds2: 1,    //    18
    reg_pad_ion0_aux_gpio15__ds3: 1,    //    19
    reg_pad_ion0_aux_gpio15__pd: 1,    //     20
    reg_pad_ion0_aux_gpio15__pu: 1,    //     21
    reg_pad_ion0_aux_gpio15__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ion0_aux_gpio14__ds0: 1,    //    24
    reg_pad_ion0_aux_gpio14__ds1: 1,    //    25
    reg_pad_ion0_aux_gpio14__ds2: 1,    //    26
    reg_pad_ion0_aux_gpio14__ds3: 1,    //    27
    reg_pad_ion0_aux_gpio14__pd: 1,    //     28
    reg_pad_ion0_aux_gpio14__pu: 1,    //     29
    reg_pad_ion0_aux_gpio14__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE17_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2048    pad_ion0_core18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio21__ds0: 1,    //     0
    reg_pad_ion0_aux_gpio21__ds1: 1,    //     1
    reg_pad_ion0_aux_gpio21__ds2: 1,    //     2
    reg_pad_ion0_aux_gpio21__ds3: 1,    //     3
    reg_pad_ion0_aux_gpio21__pd: 1,    //      4
    reg_pad_ion0_aux_gpio21__pu: 1,    //      5
    reg_pad_ion0_aux_gpio21__st: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ion0_aux_gpio20__ds0: 1,    //     8
    reg_pad_ion0_aux_gpio20__ds1: 1,    //     9
    reg_pad_ion0_aux_gpio20__ds2: 1,    //    10
    reg_pad_ion0_aux_gpio20__ds3: 1,    //    11
    reg_pad_ion0_aux_gpio20__pd: 1,    //     12
    reg_pad_ion0_aux_gpio20__pu: 1,    //     13
    reg_pad_ion0_aux_gpio20__st: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ion0_aux_gpio19__ds0: 1,    //    16
    reg_pad_ion0_aux_gpio19__ds1: 1,    //    17
    reg_pad_ion0_aux_gpio19__ds2: 1,    //    18
    reg_pad_ion0_aux_gpio19__ds3: 1,    //    19
    reg_pad_ion0_aux_gpio19__pd: 1,    //     20
    reg_pad_ion0_aux_gpio19__pu: 1,    //     21
    reg_pad_ion0_aux_gpio19__st: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ion0_aux_gpio18__ds0: 1,    //    24
    reg_pad_ion0_aux_gpio18__ds1: 1,    //    25
    reg_pad_ion0_aux_gpio18__ds2: 1,    //    26
    reg_pad_ion0_aux_gpio18__ds3: 1,    //    27
    reg_pad_ion0_aux_gpio18__pd: 1,    //     28
    reg_pad_ion0_aux_gpio18__pu: 1,    //     29
    reg_pad_ion0_aux_gpio18__st: 1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE18_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2100    pad_ion0_core64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl2_mux_sel      :  4,    //   3: 0
    reg_pad_sda2_mux_sel      :  4,    //   7: 4
    reg_pad_scl3_mux_sel      :  4,    //  11: 8
    reg_pad_sda3_mux_sel      :  4,    //  15:12
    reg_pad_scl4_mux_sel      :  4,    //  19:16
    reg_pad_sda4_mux_sel      :  4,    //  23:20
    reg_pad_scl5_mux_sel      :  4,    //  27:24
    reg_pad_sda5_mux_sel      :  4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2104    pad_ion0_core65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data3_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data2_ext2_mux_sel: 4,    //  7:4
    reg_pad_tpi_data1_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data0_ext2_mux_sel: 4,    //  15:12
    reg_pad_scl0_mux_sel      :  4,    //  19:16
    reg_pad_sda0_mux_sel      :  4,    //  23:20
    reg_pad_scl1_mux_sel      :  4,    //  27:24
    reg_pad_sda1_mux_sel      :  4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2108    pad_ion0_core66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_ext1_mux_sel: 4,    //  3:0
    reg_pad_tpi_sop_ext2_mux_sel: 4,    //  7: 4
    reg_pad_tpi_val_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_clk_ext2_mux_sel: 4,    //  15:12
    reg_pad_tpi_data7_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data6_ext2_mux_sel: 4,    //  23:20
    reg_pad_tpi_data5_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_data4_ext2_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_210C    pad_ion0_core67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk_ext1_mux_sel: 4,    //  3: 0
    reg_pad_tpi_data7_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data6_ext1_mux_sel: 4,    //  11:8
    reg_pad_tpi_data5_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data4_ext1_mux_sel: 4,    //  19:16
    reg_pad_tpi_data3_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_data2_ext1_mux_sel: 4,    //  27:24
    reg_pad_tpi_data1_ext1_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2110    pad_ion0_core68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_scl_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_3_5v_in_mux_sel: 4,    //  7: 4
    reg_pad_hdmi_4_hpd_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_4_sda_mux_sel:  4,    //  15:12
    reg_pad_hdmi_4_scl_mux_sel:  4,    //  19:16
    reg_pad_hdmi_4_5v_in_mux_sel: 4,    //  23:20
    reg_pad_tpi_sop_ext1_mux_sel: 4,    //  27:24
    reg_pad_tpi_val_ext1_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2114    pad_ion0_core69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_scl_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_1_5v_in_mux_sel: 4,    //  7: 4
    reg_pad_hdmi_2_hpd_mux_sel:  4,    //  11: 8
    reg_pad_hdmi_2_sda_mux_sel:  4,    //  15:12
    reg_pad_hdmi_2_scl_mux_sel:  4,    //  19:16
    reg_pad_hdmi_2_5v_in_mux_sel: 4,    //  23:20
    reg_pad_hdmi_3_hpd_mux_sel:  4,    //  27:24
    reg_pad_hdmi_3_sda_mux_sel:  4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2118    pad_ion0_core70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio01_mux_sel: 4,    //  3:0
    reg_pad_ion0_aux_gpio00_mux_sel: 4,    //  7:4
    reg_pad_hdmi_det1_mux_sel :  4,    //  11: 8
    reg_pad_hdmi_det2_mux_sel :  4,    //  15:12
    reg_pad_hdmi_det3_mux_sel :  4,    //  19:16
    reg_pad_hdmi_det4_mux_sel :  4,    //  23:20
    reg_pad_hdmi_1_hpd_mux_sel:  4,    //  27:24
    reg_pad_hdmi_1_sda_mux_sel:  4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_211C    pad_ion0_core71 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio09_mux_sel: 4,    //  3:0
    reg_pad_ion0_aux_gpio08_mux_sel: 4,    //  7:4
    reg_pad_ion0_aux_gpio07_mux_sel: 4,    //  11:8
    reg_pad_ion0_aux_gpio06_mux_sel: 4,    //  15:12
    reg_pad_ion0_aux_gpio05_mux_sel: 4,    //  19:16
    reg_pad_ion0_aux_gpio04_mux_sel: 4,    //  23:20
    reg_pad_ion0_aux_gpio03_mux_sel: 4,    //  27:24
    reg_pad_ion0_aux_gpio02_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE71_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2120    pad_ion0_core72 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio17_mux_sel: 4,    //  3:0
    reg_pad_ion0_aux_gpio16_mux_sel: 4,    //  7:4
    reg_pad_ion0_aux_gpio15_mux_sel: 4,    //  11:8
    reg_pad_ion0_aux_gpio14_mux_sel: 4,    //  15:12
    reg_pad_ion0_aux_gpio13_mux_sel: 4,    //  19:16
    reg_pad_ion0_aux_gpio12_mux_sel: 4,    //  23:20
    reg_pad_ion0_aux_gpio11_mux_sel: 4,    //  27:24
    reg_pad_ion0_aux_gpio10_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE72_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2124    pad_ion0_core73 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion0_aux_gpio21_mux_sel: 4,    //  3:0
    reg_pad_ion0_aux_gpio20_mux_sel: 4,    //  7:4
    reg_pad_ion0_aux_gpio19_mux_sel: 4,    //  11:8
    reg_pad_ion0_aux_gpio18_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE73_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2200    pad_ion0_core128 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aux_gpio21_oen        :  1,    //      0
    reg_aux_gpio20_oen        :  1,    //      1
    reg_aux_gpio19_oen        :  1,    //      2
    reg_aux_gpio18_oen        :  1,    //      3
    reg_aux_gpio17_oen        :  1,    //      4
    reg_aux_gpio16_oen        :  1,    //      5
    reg_aux_gpio15_oen        :  1,    //      6
    reg_aux_gpio14_oen        :  1,    //      7
    reg_aux_gpio13_oen        :  1,    //      8
    reg_aux_gpio12_oen        :  1,    //      9
    reg_aux_gpio11_oen        :  1,    //     10
    reg_aux_gpio10_oen        :  1,    //     11
    reg_aux_gpio09_oen        :  1,    //     12
    reg_aux_gpio08_oen        :  1,    //     13
    reg_aux_gpio07_oen        :  1,    //     14
    reg_aux_gpio06_oen        :  1,    //     15
    reg_aux_gpio05_oen        :  1,    //     16
    reg_aux_gpio04_oen        :  1,    //     17
    reg_aux_gpio03_oen        :  1,    //     18
    reg_aux_gpio02_oen        :  1,    //     19
    reg_aux_gpio01_oen        :  1,    //     20
    reg_aux_gpio00_oen        :  1,    //     21
                              : 10;    //  31:22 reserved
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE128_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion0_core Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE00_O26A0_T    pad_ion0_core00;    // 0xCA33_2000
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE01_O26A0_T    pad_ion0_core01;    // 0xCA33_2004
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE02_O26A0_T    pad_ion0_core02;    // 0xCA33_2008
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE03_O26A0_T    pad_ion0_core03;    // 0xCA33_200C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE04_O26A0_T    pad_ion0_core04;    // 0xCA33_2010
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE05_O26A0_T    pad_ion0_core05;    // 0xCA33_2014
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE06_O26A0_T    pad_ion0_core06;    // 0xCA33_2018
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE07_O26A0_T    pad_ion0_core07;    // 0xCA33_201C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE08_O26A0_T    pad_ion0_core08;    // 0xCA33_2020
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE09_O26A0_T    pad_ion0_core09;    // 0xCA33_2024
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE10_O26A0_T    pad_ion0_core10;    // 0xCA33_2028
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE11_O26A0_T    pad_ion0_core11;    // 0xCA33_202C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE12_O26A0_T    pad_ion0_core12;    // 0xCA33_2030
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE13_O26A0_T    pad_ion0_core13;    // 0xCA33_2034
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE14_O26A0_T    pad_ion0_core14;    // 0xCA33_2038
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE15_O26A0_T    pad_ion0_core15;    // 0xCA33_203C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE16_O26A0_T    pad_ion0_core16;    // 0xCA33_2040
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE17_O26A0_T    pad_ion0_core17;    // 0xCA33_2044
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE18_O26A0_T    pad_ion0_core18;    // 0xCA33_2048
    UINT32                             _rsvd_00[45];            // 0xCA33_204C ~ 0xCA33_20FC
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE64_O26A0_T    pad_ion0_core64;    // 0xCA33_2100
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE65_O26A0_T    pad_ion0_core65;    // 0xCA33_2104
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE66_O26A0_T    pad_ion0_core66;    // 0xCA33_2108
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE67_O26A0_T    pad_ion0_core67;    // 0xCA33_210C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE68_O26A0_T    pad_ion0_core68;    // 0xCA33_2110
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE69_O26A0_T    pad_ion0_core69;    // 0xCA33_2114
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE70_O26A0_T    pad_ion0_core70;    // 0xCA33_2118
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE71_O26A0_T    pad_ion0_core71;    // 0xCA33_211C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE72_O26A0_T    pad_ion0_core72;    // 0xCA33_2120
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE73_O26A0_T    pad_ion0_core73;    // 0xCA33_2124
    UINT32                             _rsvd_01[54];            // 0xCA33_2128 ~ 0xCA33_21FC
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE128_O26A0_T    pad_ion0_core128;    // 0xCA33_2200
}FUNC_IOMUX_ION0_CORE_REG_O26A0_T;
/* 30 regs */

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

#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE00_O26A0_T_OFF    (BASEADDRESS+0x0000)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE01_O26A0_T_OFF    (BASEADDRESS+0x0004)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE02_O26A0_T_OFF    (BASEADDRESS+0x0008)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE03_O26A0_T_OFF    (BASEADDRESS+0x000C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE04_O26A0_T_OFF    (BASEADDRESS+0x0010)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE05_O26A0_T_OFF    (BASEADDRESS+0x0014)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE06_O26A0_T_OFF    (BASEADDRESS+0x0018)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE07_O26A0_T_OFF    (BASEADDRESS+0x001C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE08_O26A0_T_OFF    (BASEADDRESS+0x0020)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE09_O26A0_T_OFF    (BASEADDRESS+0x0024)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE10_O26A0_T_OFF    (BASEADDRESS+0x0028)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE11_O26A0_T_OFF    (BASEADDRESS+0x002C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE12_O26A0_T_OFF    (BASEADDRESS+0x0030)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE13_O26A0_T_OFF    (BASEADDRESS+0x0034)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE14_O26A0_T_OFF    (BASEADDRESS+0x0038)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE15_O26A0_T_OFF    (BASEADDRESS+0x003C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE16_O26A0_T_OFF    (BASEADDRESS+0x0040)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE17_O26A0_T_OFF    (BASEADDRESS+0x0044)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE18_O26A0_T_OFF    (BASEADDRESS+0x0048)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE64_O26A0_T_OFF    (BASEADDRESS+0x0100)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE65_O26A0_T_OFF    (BASEADDRESS+0x0104)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE66_O26A0_T_OFF    (BASEADDRESS+0x0108)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE67_O26A0_T_OFF    (BASEADDRESS+0x010C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE68_O26A0_T_OFF    (BASEADDRESS+0x0110)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE69_O26A0_T_OFF    (BASEADDRESS+0x0114)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE70_O26A0_T_OFF    (BASEADDRESS+0x0118)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE71_O26A0_T_OFF    (BASEADDRESS+0x011C)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE72_O26A0_T_OFF    (BASEADDRESS+0x0120)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE73_O26A0_T_OFF    (BASEADDRESS+0x0124)
#define FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE128_O26A0_T_OFF   (BASEADDRESS+0x0200)

/*-----------------------------------------------------------------------------------------
    0xCA33_2000    pad_ion0_core00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl4__ds0  :  1;    //      0
    UINT32 reg_pad_scl4__ds1  :  1;    //      1
    UINT32 reg_pad_scl4__ds2  :  1;    //      2
    UINT32 reg_pad_scl4__ds3  :  1;    //      3
    UINT32 reg_pad_scl4__pd   :  1;    //      4
    UINT32 reg_pad_scl4__pu   :  1;    //      5
    UINT32 reg_pad_scl4__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda4__ds0  :  1;    //      8
    UINT32 reg_pad_sda4__ds1  :  1;    //      9
    UINT32 reg_pad_sda4__ds2  :  1;    //     10
    UINT32 reg_pad_sda4__ds3  :  1;    //     11
    UINT32 reg_pad_sda4__pd   :  1;    //     12
    UINT32 reg_pad_sda4__pu   :  1;    //     13
    UINT32 reg_pad_sda4__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl5__ds0  :  1;    //     16
    UINT32 reg_pad_scl5__ds1  :  1;    //     17
    UINT32 reg_pad_scl5__ds2  :  1;    //     18
    UINT32 reg_pad_scl5__ds3  :  1;    //     19
    UINT32 reg_pad_scl5__pd   :  1;    //     20
    UINT32 reg_pad_scl5__pu   :  1;    //     21
    UINT32 reg_pad_scl5__st   :  1;    //     22
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2004    pad_ion0_core01 ''
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
    UINT32 reg_pad_sda2__ds0  :  1;    //      8
    UINT32 reg_pad_sda2__ds1  :  1;    //      9
    UINT32 reg_pad_sda2__ds2  :  1;    //     10
    UINT32 reg_pad_sda2__ds3  :  1;    //     11
    UINT32 reg_pad_sda2__pd   :  1;    //     12
    UINT32 reg_pad_sda2__pu   :  1;    //     13
    UINT32 reg_pad_sda2__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl3__ds0  :  1;    //     16
    UINT32 reg_pad_scl3__ds1  :  1;    //     17
    UINT32 reg_pad_scl3__ds2  :  1;    //     18
    UINT32 reg_pad_scl3__ds3  :  1;    //     19
    UINT32 reg_pad_scl3__pd   :  1;    //     20
    UINT32 reg_pad_scl3__pu   :  1;    //     21
    UINT32 reg_pad_scl3__st   :  1;    //     22
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2008    pad_ion0_core02 ''
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
    UINT32 reg_pad_sda0__ds0  :  1;    //      8
    UINT32 reg_pad_sda0__ds1  :  1;    //      9
    UINT32 reg_pad_sda0__ds2  :  1;    //     10
    UINT32 reg_pad_sda0__ds3  :  1;    //     11
    UINT32 reg_pad_sda0__pd   :  1;    //     12
    UINT32 reg_pad_sda0__pu   :  1;    //     13
    UINT32 reg_pad_sda0__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl1__ds0  :  1;    //     16
    UINT32 reg_pad_scl1__ds1  :  1;    //     17
    UINT32 reg_pad_scl1__ds2  :  1;    //     18
    UINT32 reg_pad_scl1__ds3  :  1;    //     19
    UINT32 reg_pad_scl1__pd   :  1;    //     20
    UINT32 reg_pad_scl1__pu   :  1;    //     21
    UINT32 reg_pad_scl1__st   :  1;    //     22
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_200C    pad_ion0_core03 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2010    pad_ion0_core04 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2014    pad_ion0_core05 ''
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
    UINT32 reg_pad_tpi_sop_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_sop_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_sop_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_sop_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_sop_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_sop_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_sop_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_val_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_val_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_val_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_val_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_val_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_val_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_val_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_clk_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_clk_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_clk_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_clk_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_clk_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_clk_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_clk_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2018    pad_ion0_core06 ''
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_201C    pad_ion0_core07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_clk_ext1__ds0: 1;    //  0
    UINT32 reg_pad_tpi_clk_ext1__ds1: 1;    //  1
    UINT32 reg_pad_tpi_clk_ext1__ds2: 1;    //  2
    UINT32 reg_pad_tpi_clk_ext1__ds3: 1;    //  3
    UINT32 reg_pad_tpi_clk_ext1__pd: 1;    //  4
    UINT32 reg_pad_tpi_clk_ext1__pu: 1;    //  5
    UINT32 reg_pad_tpi_clk_ext1__st: 1;    //  6
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2020    pad_ion0_core08 ''
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
    UINT32 reg_pad_hdmi_4_5v_in__ds0: 1;    //  8
    UINT32 reg_pad_hdmi_4_5v_in__ds1: 1;    //  9
    UINT32 reg_pad_hdmi_4_5v_in__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_4_5v_in__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_4_5v_in__pd: 1;    //  12
    UINT32 reg_pad_hdmi_4_5v_in__pu: 1;    //  13
    UINT32 reg_pad_hdmi_4_5v_in__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_sop_ext1__ds0: 1;    //  16
    UINT32 reg_pad_tpi_sop_ext1__ds1: 1;    //  17
    UINT32 reg_pad_tpi_sop_ext1__ds2: 1;    //  18
    UINT32 reg_pad_tpi_sop_ext1__ds3: 1;    //  19
    UINT32 reg_pad_tpi_sop_ext1__pd: 1;    //  20
    UINT32 reg_pad_tpi_sop_ext1__pu: 1;    //  21
    UINT32 reg_pad_tpi_sop_ext1__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_val_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_val_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_val_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_val_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_val_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_val_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_val_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2024    pad_ion0_core09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_3_scl__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_3_scl__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_3_scl__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_3_scl__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_3_scl__pd: 1;    //    4
    UINT32 reg_pad_hdmi_3_scl__pu: 1;    //    5
    UINT32 reg_pad_hdmi_3_scl__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_3_5v_in__ds0: 1;    //  8
    UINT32 reg_pad_hdmi_3_5v_in__ds1: 1;    //  9
    UINT32 reg_pad_hdmi_3_5v_in__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_3_5v_in__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_3_5v_in__pd: 1;    //  12
    UINT32 reg_pad_hdmi_3_5v_in__pu: 1;    //  13
    UINT32 reg_pad_hdmi_3_5v_in__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_4_hpd__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_4_hpd__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_4_hpd__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_4_hpd__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_4_hpd__pd: 1;    //   20
    UINT32 reg_pad_hdmi_4_hpd__pu: 1;    //   21
    UINT32 reg_pad_hdmi_4_hpd__st: 1;    //   22
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
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2028    pad_ion0_core10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_2_scl__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_2_scl__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_2_scl__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_2_scl__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_2_scl__pd: 1;    //    4
    UINT32 reg_pad_hdmi_2_scl__pu: 1;    //    5
    UINT32 reg_pad_hdmi_2_scl__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_2_5v_in__ds0: 1;    //  8
    UINT32 reg_pad_hdmi_2_5v_in__ds1: 1;    //  9
    UINT32 reg_pad_hdmi_2_5v_in__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_2_5v_in__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_2_5v_in__pd: 1;    //  12
    UINT32 reg_pad_hdmi_2_5v_in__pu: 1;    //  13
    UINT32 reg_pad_hdmi_2_5v_in__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_3_hpd__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_3_hpd__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_3_hpd__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_3_hpd__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_3_hpd__pd: 1;    //   20
    UINT32 reg_pad_hdmi_3_hpd__pu: 1;    //   21
    UINT32 reg_pad_hdmi_3_hpd__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_3_sda__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_3_sda__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_3_sda__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_3_sda__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_3_sda__pd: 1;    //   28
    UINT32 reg_pad_hdmi_3_sda__pu: 1;    //   29
    UINT32 reg_pad_hdmi_3_sda__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_202C    pad_ion0_core11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_1_scl__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_1_scl__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_1_scl__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_1_scl__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_1_scl__pd: 1;    //    4
    UINT32 reg_pad_hdmi_1_scl__pu: 1;    //    5
    UINT32 reg_pad_hdmi_1_scl__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_1_5v_in__ds0: 1;    //  8
    UINT32 reg_pad_hdmi_1_5v_in__ds1: 1;    //  9
    UINT32 reg_pad_hdmi_1_5v_in__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_1_5v_in__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_1_5v_in__pd: 1;    //  12
    UINT32 reg_pad_hdmi_1_5v_in__pu: 1;    //  13
    UINT32 reg_pad_hdmi_1_5v_in__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_2_hpd__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_2_hpd__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_2_hpd__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_2_hpd__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_2_hpd__pd: 1;    //   20
    UINT32 reg_pad_hdmi_2_hpd__pu: 1;    //   21
    UINT32 reg_pad_hdmi_2_hpd__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_2_sda__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_2_sda__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_2_sda__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_2_sda__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_2_sda__pd: 1;    //   28
    UINT32 reg_pad_hdmi_2_sda__pu: 1;    //   29
    UINT32 reg_pad_hdmi_2_sda__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2030    pad_ion0_core12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_det3__ds0: 1;    //    0
    UINT32 reg_pad_hdmi_det3__ds1: 1;    //    1
    UINT32 reg_pad_hdmi_det3__ds2: 1;    //    2
    UINT32 reg_pad_hdmi_det3__ds3: 1;    //    3
    UINT32 reg_pad_hdmi_det3__pd: 1;    //     4
    UINT32 reg_pad_hdmi_det3__pu: 1;    //     5
    UINT32 reg_pad_hdmi_det3__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_det4__ds0: 1;    //    8
    UINT32 reg_pad_hdmi_det4__ds1: 1;    //    9
    UINT32 reg_pad_hdmi_det4__ds2: 1;    //   10
    UINT32 reg_pad_hdmi_det4__ds3: 1;    //   11
    UINT32 reg_pad_hdmi_det4__pd: 1;    //    12
    UINT32 reg_pad_hdmi_det4__pu: 1;    //    13
    UINT32 reg_pad_hdmi_det4__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_1_hpd__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_1_hpd__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_1_hpd__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_1_hpd__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_1_hpd__pd: 1;    //   20
    UINT32 reg_pad_hdmi_1_hpd__pu: 1;    //   21
    UINT32 reg_pad_hdmi_1_hpd__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_1_sda__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_1_sda__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_1_sda__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_1_sda__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_1_sda__pd: 1;    //   28
    UINT32 reg_pad_hdmi_1_sda__pu: 1;    //   29
    UINT32 reg_pad_hdmi_1_sda__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2034    pad_ion0_core13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio01__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio01__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio01__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio01__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio01__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio01__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio01__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio00__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio00__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio00__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio00__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio00__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio00__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio00__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_det1__ds0: 1;    //   16
    UINT32 reg_pad_hdmi_det1__ds1: 1;    //   17
    UINT32 reg_pad_hdmi_det1__ds2: 1;    //   18
    UINT32 reg_pad_hdmi_det1__ds3: 1;    //   19
    UINT32 reg_pad_hdmi_det1__pd: 1;    //    20
    UINT32 reg_pad_hdmi_det1__pu: 1;    //    21
    UINT32 reg_pad_hdmi_det1__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_det2__ds0: 1;    //   24
    UINT32 reg_pad_hdmi_det2__ds1: 1;    //   25
    UINT32 reg_pad_hdmi_det2__ds2: 1;    //   26
    UINT32 reg_pad_hdmi_det2__ds3: 1;    //   27
    UINT32 reg_pad_hdmi_det2__pd: 1;    //    28
    UINT32 reg_pad_hdmi_det2__pu: 1;    //    29
    UINT32 reg_pad_hdmi_det2__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2038    pad_ion0_core14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio05__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio05__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio05__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio05__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio05__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio05__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio05__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio04__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio04__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio04__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio04__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio04__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio04__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio04__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ion0_aux_gpio03__ds0: 1;    //  16
    UINT32 reg_pad_ion0_aux_gpio03__ds1: 1;    //  17
    UINT32 reg_pad_ion0_aux_gpio03__ds2: 1;    //  18
    UINT32 reg_pad_ion0_aux_gpio03__ds3: 1;    //  19
    UINT32 reg_pad_ion0_aux_gpio03__pd: 1;    //  20
    UINT32 reg_pad_ion0_aux_gpio03__pu: 1;    //  21
    UINT32 reg_pad_ion0_aux_gpio03__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ion0_aux_gpio02__ds0: 1;    //  24
    UINT32 reg_pad_ion0_aux_gpio02__ds1: 1;    //  25
    UINT32 reg_pad_ion0_aux_gpio02__ds2: 1;    //  26
    UINT32 reg_pad_ion0_aux_gpio02__ds3: 1;    //  27
    UINT32 reg_pad_ion0_aux_gpio02__pd: 1;    //  28
    UINT32 reg_pad_ion0_aux_gpio02__pu: 1;    //  29
    UINT32 reg_pad_ion0_aux_gpio02__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_203C    pad_ion0_core15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio09__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio09__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio09__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio09__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio09__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio09__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio09__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio08__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio08__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio08__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio08__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio08__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio08__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio08__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ion0_aux_gpio07__ds0: 1;    //  16
    UINT32 reg_pad_ion0_aux_gpio07__ds1: 1;    //  17
    UINT32 reg_pad_ion0_aux_gpio07__ds2: 1;    //  18
    UINT32 reg_pad_ion0_aux_gpio07__ds3: 1;    //  19
    UINT32 reg_pad_ion0_aux_gpio07__pd: 1;    //  20
    UINT32 reg_pad_ion0_aux_gpio07__pu: 1;    //  21
    UINT32 reg_pad_ion0_aux_gpio07__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ion0_aux_gpio06__ds0: 1;    //  24
    UINT32 reg_pad_ion0_aux_gpio06__ds1: 1;    //  25
    UINT32 reg_pad_ion0_aux_gpio06__ds2: 1;    //  26
    UINT32 reg_pad_ion0_aux_gpio06__ds3: 1;    //  27
    UINT32 reg_pad_ion0_aux_gpio06__pd: 1;    //  28
    UINT32 reg_pad_ion0_aux_gpio06__pu: 1;    //  29
    UINT32 reg_pad_ion0_aux_gpio06__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2040    pad_ion0_core16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio13__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio13__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio13__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio13__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio13__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio13__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio13__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio12__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio12__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio12__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio12__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio12__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio12__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio12__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ion0_aux_gpio11__ds0: 1;    //  16
    UINT32 reg_pad_ion0_aux_gpio11__ds1: 1;    //  17
    UINT32 reg_pad_ion0_aux_gpio11__ds2: 1;    //  18
    UINT32 reg_pad_ion0_aux_gpio11__ds3: 1;    //  19
    UINT32 reg_pad_ion0_aux_gpio11__pd: 1;    //  20
    UINT32 reg_pad_ion0_aux_gpio11__pu: 1;    //  21
    UINT32 reg_pad_ion0_aux_gpio11__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ion0_aux_gpio10__ds0: 1;    //  24
    UINT32 reg_pad_ion0_aux_gpio10__ds1: 1;    //  25
    UINT32 reg_pad_ion0_aux_gpio10__ds2: 1;    //  26
    UINT32 reg_pad_ion0_aux_gpio10__ds3: 1;    //  27
    UINT32 reg_pad_ion0_aux_gpio10__pd: 1;    //  28
    UINT32 reg_pad_ion0_aux_gpio10__pu: 1;    //  29
    UINT32 reg_pad_ion0_aux_gpio10__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2044    pad_ion0_core17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio17__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio17__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio17__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio17__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio17__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio17__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio17__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio16__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio16__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio16__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio16__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio16__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio16__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio16__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ion0_aux_gpio15__ds0: 1;    //  16
    UINT32 reg_pad_ion0_aux_gpio15__ds1: 1;    //  17
    UINT32 reg_pad_ion0_aux_gpio15__ds2: 1;    //  18
    UINT32 reg_pad_ion0_aux_gpio15__ds3: 1;    //  19
    UINT32 reg_pad_ion0_aux_gpio15__pd: 1;    //  20
    UINT32 reg_pad_ion0_aux_gpio15__pu: 1;    //  21
    UINT32 reg_pad_ion0_aux_gpio15__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ion0_aux_gpio14__ds0: 1;    //  24
    UINT32 reg_pad_ion0_aux_gpio14__ds1: 1;    //  25
    UINT32 reg_pad_ion0_aux_gpio14__ds2: 1;    //  26
    UINT32 reg_pad_ion0_aux_gpio14__ds3: 1;    //  27
    UINT32 reg_pad_ion0_aux_gpio14__pd: 1;    //  28
    UINT32 reg_pad_ion0_aux_gpio14__pu: 1;    //  29
    UINT32 reg_pad_ion0_aux_gpio14__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE17_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2048    pad_ion0_core18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio21__ds0: 1;    //  0
    UINT32 reg_pad_ion0_aux_gpio21__ds1: 1;    //  1
    UINT32 reg_pad_ion0_aux_gpio21__ds2: 1;    //  2
    UINT32 reg_pad_ion0_aux_gpio21__ds3: 1;    //  3
    UINT32 reg_pad_ion0_aux_gpio21__pd: 1;    //  4
    UINT32 reg_pad_ion0_aux_gpio21__pu: 1;    //  5
    UINT32 reg_pad_ion0_aux_gpio21__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ion0_aux_gpio20__ds0: 1;    //  8
    UINT32 reg_pad_ion0_aux_gpio20__ds1: 1;    //  9
    UINT32 reg_pad_ion0_aux_gpio20__ds2: 1;    //  10
    UINT32 reg_pad_ion0_aux_gpio20__ds3: 1;    //  11
    UINT32 reg_pad_ion0_aux_gpio20__pd: 1;    //  12
    UINT32 reg_pad_ion0_aux_gpio20__pu: 1;    //  13
    UINT32 reg_pad_ion0_aux_gpio20__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ion0_aux_gpio19__ds0: 1;    //  16
    UINT32 reg_pad_ion0_aux_gpio19__ds1: 1;    //  17
    UINT32 reg_pad_ion0_aux_gpio19__ds2: 1;    //  18
    UINT32 reg_pad_ion0_aux_gpio19__ds3: 1;    //  19
    UINT32 reg_pad_ion0_aux_gpio19__pd: 1;    //  20
    UINT32 reg_pad_ion0_aux_gpio19__pu: 1;    //  21
    UINT32 reg_pad_ion0_aux_gpio19__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ion0_aux_gpio18__ds0: 1;    //  24
    UINT32 reg_pad_ion0_aux_gpio18__ds1: 1;    //  25
    UINT32 reg_pad_ion0_aux_gpio18__ds2: 1;    //  26
    UINT32 reg_pad_ion0_aux_gpio18__ds3: 1;    //  27
    UINT32 reg_pad_ion0_aux_gpio18__pd: 1;    //  28
    UINT32 reg_pad_ion0_aux_gpio18__pu: 1;    //  29
    UINT32 reg_pad_ion0_aux_gpio18__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE18_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2100    pad_ion0_core64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl2_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_sda2_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_scl3_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_sda3_mux_sel: 4;    //  15:12
    UINT32 reg_pad_scl4_mux_sel: 4;    //  19:16
    UINT32 reg_pad_sda4_mux_sel: 4;    //  23:20
    UINT32 reg_pad_scl5_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda5_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2104    pad_ion0_core65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data3_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data2_ext2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data1_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data0_ext2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_scl0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_sda0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_scl1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda1_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2108    pad_ion0_core66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data0_ext1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_sop_ext2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_val_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_clk_ext2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data7_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data6_ext2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data5_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data4_ext2_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_210C    pad_ion0_core67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_clk_ext1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data7_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data6_ext1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data5_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data4_ext1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data3_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data2_ext1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data1_ext1_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2110    pad_ion0_core68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_3_scl_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_3_5v_in_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_4_hpd_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_4_sda_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_4_scl_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_4_5v_in_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_sop_ext1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_val_ext1_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2114    pad_ion0_core69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_1_scl_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_1_5v_in_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_2_hpd_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_2_sda_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_2_scl_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_2_5v_in_mux_sel: 4;    //  23:20
    UINT32 reg_pad_hdmi_3_hpd_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_3_sda_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2118    pad_ion0_core70 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio01_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ion0_aux_gpio00_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_det1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_det2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_det3_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_det4_mux_sel: 4;    //  23:20
    UINT32 reg_pad_hdmi_1_hpd_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_1_sda_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_211C    pad_ion0_core71 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio09_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ion0_aux_gpio08_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ion0_aux_gpio07_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ion0_aux_gpio06_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ion0_aux_gpio05_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ion0_aux_gpio04_mux_sel: 4;    //  23:20
    UINT32 reg_pad_ion0_aux_gpio03_mux_sel: 4;    //  27:24
    UINT32 reg_pad_ion0_aux_gpio02_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE71_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2120    pad_ion0_core72 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio17_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ion0_aux_gpio16_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ion0_aux_gpio15_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ion0_aux_gpio14_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ion0_aux_gpio13_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ion0_aux_gpio12_mux_sel: 4;    //  23:20
    UINT32 reg_pad_ion0_aux_gpio11_mux_sel: 4;    //  27:24
    UINT32 reg_pad_ion0_aux_gpio10_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE72_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2124    pad_ion0_core73 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion0_aux_gpio21_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ion0_aux_gpio20_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ion0_aux_gpio19_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ion0_aux_gpio18_mux_sel: 4;    //  15:12
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE73_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA33_2200    pad_ion0_core128 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aux_gpio21_oen :  1;    //      0
    UINT32 reg_aux_gpio20_oen :  1;    //      1
    UINT32 reg_aux_gpio19_oen :  1;    //      2
    UINT32 reg_aux_gpio18_oen :  1;    //      3
    UINT32 reg_aux_gpio17_oen :  1;    //      4
    UINT32 reg_aux_gpio16_oen :  1;    //      5
    UINT32 reg_aux_gpio15_oen :  1;    //      6
    UINT32 reg_aux_gpio14_oen :  1;    //      7
    UINT32 reg_aux_gpio13_oen :  1;    //      8
    UINT32 reg_aux_gpio12_oen :  1;    //      9
    UINT32 reg_aux_gpio11_oen :  1;    //     10
    UINT32 reg_aux_gpio10_oen :  1;    //     11
    UINT32 reg_aux_gpio09_oen :  1;    //     12
    UINT32 reg_aux_gpio08_oen :  1;    //     13
    UINT32 reg_aux_gpio07_oen :  1;    //     14
    UINT32 reg_aux_gpio06_oen :  1;    //     15
    UINT32 reg_aux_gpio05_oen :  1;    //     16
    UINT32 reg_aux_gpio04_oen :  1;    //     17
    UINT32 reg_aux_gpio03_oen :  1;    //     18
    UINT32 reg_aux_gpio02_oen :  1;    //     19
    UINT32 reg_aux_gpio01_oen :  1;    //     20
    UINT32 reg_aux_gpio00_oen :  1;    //     21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE128_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion0_core Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE00_O26A0_T    pad_ion0_core00;    // 0xCA33_2000
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE01_O26A0_T    pad_ion0_core01;    // 0xCA33_2004
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE02_O26A0_T    pad_ion0_core02;    // 0xCA33_2008
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE03_O26A0_T    pad_ion0_core03;    // 0xCA33_200C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE04_O26A0_T    pad_ion0_core04;    // 0xCA33_2010
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE05_O26A0_T    pad_ion0_core05;    // 0xCA33_2014
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE06_O26A0_T    pad_ion0_core06;    // 0xCA33_2018
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE07_O26A0_T    pad_ion0_core07;    // 0xCA33_201C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE08_O26A0_T    pad_ion0_core08;    // 0xCA33_2020
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE09_O26A0_T    pad_ion0_core09;    // 0xCA33_2024
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE10_O26A0_T    pad_ion0_core10;    // 0xCA33_2028
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE11_O26A0_T    pad_ion0_core11;    // 0xCA33_202C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE12_O26A0_T    pad_ion0_core12;    // 0xCA33_2030
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE13_O26A0_T    pad_ion0_core13;    // 0xCA33_2034
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE14_O26A0_T    pad_ion0_core14;    // 0xCA33_2038
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE15_O26A0_T    pad_ion0_core15;    // 0xCA33_203C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE16_O26A0_T    pad_ion0_core16;    // 0xCA33_2040
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE17_O26A0_T    pad_ion0_core17;    // 0xCA33_2044
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE18_O26A0_T    pad_ion0_core18;    // 0xCA33_2048
    UINT32                             _rsvd_00[45];            // 0xCA33_204C ~ 0xCA33_20FC
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE64_O26A0_T    pad_ion0_core64;    // 0xCA33_2100
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE65_O26A0_T    pad_ion0_core65;    // 0xCA33_2104
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE66_O26A0_T    pad_ion0_core66;    // 0xCA33_2108
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE67_O26A0_T    pad_ion0_core67;    // 0xCA33_210C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE68_O26A0_T    pad_ion0_core68;    // 0xCA33_2110
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE69_O26A0_T    pad_ion0_core69;    // 0xCA33_2114
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE70_O26A0_T    pad_ion0_core70;    // 0xCA33_2118
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE71_O26A0_T    pad_ion0_core71;    // 0xCA33_211C
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE72_O26A0_T    pad_ion0_core72;    // 0xCA33_2120
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE73_O26A0_T    pad_ion0_core73;    // 0xCA33_2124
    UINT32                             _rsvd_01[54];            // 0xCA33_2128 ~ 0xCA33_21FC
    FUNC_IOMUX_ION0_CORE_PAD_ION0_CORE128_O26A0_T    pad_ion0_core128;    // 0xCA33_2200
}FUNC_IOMUX_ION0_CORE_REG_O26A0_T;
/* 30 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _FUNC_IOMUX_ION0_CORE_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/

