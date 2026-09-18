#ifndef _IOMUX_CTRL_BMC_REG_O24A0_H_
#define _IOMUX_CTRL_BMC_REG_O24A0_H_

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
    0xC68A_3000    pad_lnx2_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_fefctrl__ds0      :  1,    //      0
    reg_pad_fefctrl__ds1      :  1,    //      1
    reg_pad_fefctrl__ds2      :  1,    //      2
    reg_pad_fefctrl__ds3      :  1,    //      3
    reg_pad_fefctrl__pd       :  1,    //      4
    reg_pad_fefctrl__pu       :  1,    //      5
    reg_pad_fefctrl__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_diseqci__ds0      :  1,    //      8
    reg_pad_diseqci__ds1      :  1,    //      9
    reg_pad_diseqci__ds2      :  1,    //     10
    reg_pad_diseqci__ds3      :  1,    //     11
    reg_pad_diseqci__pd       :  1,    //     12
    reg_pad_diseqci__pu       :  1,    //     13
    reg_pad_diseqci__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_diseqc_cmd__ds0   :  1,    //     16
    reg_pad_diseqc_cmd__ds1   :  1,    //     17
    reg_pad_diseqc_cmd__ds2   :  1,    //     18
    reg_pad_diseqc_cmd__ds3   :  1,    //     19
    reg_pad_diseqc_cmd__pd    :  1,    //     20
    reg_pad_diseqc_cmd__pu    :  1,    //     21
    reg_pad_diseqc_cmd__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_diseqc__ds0       :  1,    //     24
    reg_pad_diseqc__ds1       :  1,    //     25
    reg_pad_diseqc__ds2       :  1,    //     26
    reg_pad_diseqc__ds3       :  1,    //     27
    reg_pad_diseqc__pd        :  1,    //     28
    reg_pad_diseqc__pu        :  1,    //     29
    reg_pad_diseqc__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3004    pad_lnx2_01 ''
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
    reg_pad_scl0__ds0         :  1,    //      8
    reg_pad_scl0__ds1         :  1,    //      9
    reg_pad_scl0__ds2         :  1,    //     10
    reg_pad_scl0__ds3         :  1,    //     11
    reg_pad_scl0__pd          :  1,    //     12
    reg_pad_scl0__pu          :  1,    //     13
    reg_pad_scl0__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ifagc_s__ds0      :  1,    //     16
    reg_pad_ifagc_s__ds1      :  1,    //     17
    reg_pad_ifagc_s__ds2      :  1,    //     18
    reg_pad_ifagc_s__ds3      :  1,    //     19
    reg_pad_ifagc_s__pd       :  1,    //     20
    reg_pad_ifagc_s__pu       :  1,    //     21
    reg_pad_ifagc_s__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ifagc__ds0        :  1,    //     24
    reg_pad_ifagc__ds1        :  1,    //     25
    reg_pad_ifagc__ds2        :  1,    //     26
    reg_pad_ifagc__ds3        :  1,    //     27
    reg_pad_ifagc__pd         :  1,    //     28
    reg_pad_ifagc__pu         :  1,    //     29
    reg_pad_ifagc__st         :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3008    pad_lnx2_02 ''
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
    reg_pad_scl4__ds0         :  1,    //      8
    reg_pad_scl4__ds1         :  1,    //      9
    reg_pad_scl4__ds2         :  1,    //     10
    reg_pad_scl4__ds3         :  1,    //     11
    reg_pad_scl4__pd          :  1,    //     12
    reg_pad_scl4__pu          :  1,    //     13
    reg_pad_scl4__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_scl3__ds0         :  1,    //     16
    reg_pad_scl3__ds1         :  1,    //     17
    reg_pad_scl3__ds2         :  1,    //     18
    reg_pad_scl3__ds3         :  1,    //     19
    reg_pad_scl3__pd          :  1,    //     20
    reg_pad_scl3__pu          :  1,    //     21
    reg_pad_scl3__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_scl2__ds0         :  1,    //     24
    reg_pad_scl2__ds1         :  1,    //     25
    reg_pad_scl2__ds2         :  1,    //     26
    reg_pad_scl2__ds3         :  1,    //     27
    reg_pad_scl2__pd          :  1,    //     28
    reg_pad_scl2__pu          :  1,    //     29
    reg_pad_scl2__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_300C    pad_lnx2_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda3__ds0         :  1,    //      0
    reg_pad_sda3__ds1         :  1,    //      1
    reg_pad_sda3__ds2         :  1,    //      2
    reg_pad_sda3__ds3         :  1,    //      3
    reg_pad_sda3__pd          :  1,    //      4
    reg_pad_sda3__pu          :  1,    //      5
    reg_pad_sda3__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sda2__ds0         :  1,    //      8
    reg_pad_sda2__ds1         :  1,    //      9
    reg_pad_sda2__ds2         :  1,    //     10
    reg_pad_sda2__ds3         :  1,    //     11
    reg_pad_sda2__pd          :  1,    //     12
    reg_pad_sda2__pu          :  1,    //     13
    reg_pad_sda2__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sda1__ds0         :  1,    //     16
    reg_pad_sda1__ds1         :  1,    //     17
    reg_pad_sda1__ds2         :  1,    //     18
    reg_pad_sda1__ds3         :  1,    //     19
    reg_pad_sda1__pd          :  1,    //     20
    reg_pad_sda1__pu          :  1,    //     21
    reg_pad_sda1__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda0__ds0         :  1,    //     24
    reg_pad_sda0__ds1         :  1,    //     25
    reg_pad_sda0__ds2         :  1,    //     26
    reg_pad_sda0__ds3         :  1,    //     27
    reg_pad_sda0__pd          :  1,    //     28
    reg_pad_sda0__pu          :  1,    //     29
    reg_pad_sda0__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3010    pad_lnx2_04 ''
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
    reg_pad_tpi_clk_ext1__ds0 :  1,    //      8
    reg_pad_tpi_clk_ext1__ds1 :  1,    //      9
    reg_pad_tpi_clk_ext1__ds2 :  1,    //     10
    reg_pad_tpi_clk_ext1__ds3 :  1,    //     11
    reg_pad_tpi_clk_ext1__pd  :  1,    //     12
    reg_pad_tpi_clk_ext1__pu  :  1,    //     13
    reg_pad_tpi_clk_ext1__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sda5__ds0         :  1,    //     16
    reg_pad_sda5__ds1         :  1,    //     17
    reg_pad_sda5__ds2         :  1,    //     18
    reg_pad_sda5__ds3         :  1,    //     19
    reg_pad_sda5__pd          :  1,    //     20
    reg_pad_sda5__pu          :  1,    //     21
    reg_pad_sda5__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sda4__ds0         :  1,    //     24
    reg_pad_sda4__ds1         :  1,    //     25
    reg_pad_sda4__ds2         :  1,    //     26
    reg_pad_sda4__ds3         :  1,    //     27
    reg_pad_sda4__pd          :  1,    //     28
    reg_pad_sda4__pu          :  1,    //     29
    reg_pad_sda4__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3014    pad_lnx2_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data1_ext2__ds0: 1,    //      0
    reg_pad_tpi_data1_ext2__ds1: 1,    //      1
    reg_pad_tpi_data1_ext2__ds2: 1,    //      2
    reg_pad_tpi_data1_ext2__ds3: 1,    //      3
    reg_pad_tpi_data1_ext2__pd:  1,    //      4
    reg_pad_tpi_data1_ext2__pu:  1,    //      5
    reg_pad_tpi_data1_ext2__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data1_ext1__ds0: 1,    //      8
    reg_pad_tpi_data1_ext1__ds1: 1,    //      9
    reg_pad_tpi_data1_ext1__ds2: 1,    //     10
    reg_pad_tpi_data1_ext1__ds3: 1,    //     11
    reg_pad_tpi_data1_ext1__pd:  1,    //     12
    reg_pad_tpi_data1_ext1__pu:  1,    //     13
    reg_pad_tpi_data1_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data0_ext2__ds0: 1,    //     16
    reg_pad_tpi_data0_ext2__ds1: 1,    //     17
    reg_pad_tpi_data0_ext2__ds2: 1,    //     18
    reg_pad_tpi_data0_ext2__ds3: 1,    //     19
    reg_pad_tpi_data0_ext2__pd:  1,    //     20
    reg_pad_tpi_data0_ext2__pu:  1,    //     21
    reg_pad_tpi_data0_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data0_ext1__ds0: 1,    //     24
    reg_pad_tpi_data0_ext1__ds1: 1,    //     25
    reg_pad_tpi_data0_ext1__ds2: 1,    //     26
    reg_pad_tpi_data0_ext1__ds3: 1,    //     27
    reg_pad_tpi_data0_ext1__pd:  1,    //     28
    reg_pad_tpi_data0_ext1__pu:  1,    //     29
    reg_pad_tpi_data0_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3018    pad_lnx2_06 ''
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
    reg_pad_tpi_data3_ext1__ds0: 1,    //      8
    reg_pad_tpi_data3_ext1__ds1: 1,    //      9
    reg_pad_tpi_data3_ext1__ds2: 1,    //     10
    reg_pad_tpi_data3_ext1__ds3: 1,    //     11
    reg_pad_tpi_data3_ext1__pd:  1,    //     12
    reg_pad_tpi_data3_ext1__pu:  1,    //     13
    reg_pad_tpi_data3_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data2_ext2__ds0: 1,    //     16
    reg_pad_tpi_data2_ext2__ds1: 1,    //     17
    reg_pad_tpi_data2_ext2__ds2: 1,    //     18
    reg_pad_tpi_data2_ext2__ds3: 1,    //     19
    reg_pad_tpi_data2_ext2__pd:  1,    //     20
    reg_pad_tpi_data2_ext2__pu:  1,    //     21
    reg_pad_tpi_data2_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data2_ext1__ds0: 1,    //     24
    reg_pad_tpi_data2_ext1__ds1: 1,    //     25
    reg_pad_tpi_data2_ext1__ds2: 1,    //     26
    reg_pad_tpi_data2_ext1__ds3: 1,    //     27
    reg_pad_tpi_data2_ext1__pd:  1,    //     28
    reg_pad_tpi_data2_ext1__pu:  1,    //     29
    reg_pad_tpi_data2_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_301C    pad_lnx2_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5_ext2__ds0: 1,    //      0
    reg_pad_tpi_data5_ext2__ds1: 1,    //      1
    reg_pad_tpi_data5_ext2__ds2: 1,    //      2
    reg_pad_tpi_data5_ext2__ds3: 1,    //      3
    reg_pad_tpi_data5_ext2__pd:  1,    //      4
    reg_pad_tpi_data5_ext2__pu:  1,    //      5
    reg_pad_tpi_data5_ext2__st:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data5_ext1__ds0: 1,    //      8
    reg_pad_tpi_data5_ext1__ds1: 1,    //      9
    reg_pad_tpi_data5_ext1__ds2: 1,    //     10
    reg_pad_tpi_data5_ext1__ds3: 1,    //     11
    reg_pad_tpi_data5_ext1__pd:  1,    //     12
    reg_pad_tpi_data5_ext1__pu:  1,    //     13
    reg_pad_tpi_data5_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data4_ext2__ds0: 1,    //     16
    reg_pad_tpi_data4_ext2__ds1: 1,    //     17
    reg_pad_tpi_data4_ext2__ds2: 1,    //     18
    reg_pad_tpi_data4_ext2__ds3: 1,    //     19
    reg_pad_tpi_data4_ext2__pd:  1,    //     20
    reg_pad_tpi_data4_ext2__pu:  1,    //     21
    reg_pad_tpi_data4_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data4_ext1__ds0: 1,    //     24
    reg_pad_tpi_data4_ext1__ds1: 1,    //     25
    reg_pad_tpi_data4_ext1__ds2: 1,    //     26
    reg_pad_tpi_data4_ext1__ds3: 1,    //     27
    reg_pad_tpi_data4_ext1__pd:  1,    //     28
    reg_pad_tpi_data4_ext1__pu:  1,    //     29
    reg_pad_tpi_data4_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3020    pad_lnx2_08 ''
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
    reg_pad_tpi_data7_ext1__ds0: 1,    //      8
    reg_pad_tpi_data7_ext1__ds1: 1,    //      9
    reg_pad_tpi_data7_ext1__ds2: 1,    //     10
    reg_pad_tpi_data7_ext1__ds3: 1,    //     11
    reg_pad_tpi_data7_ext1__pd:  1,    //     12
    reg_pad_tpi_data7_ext1__pu:  1,    //     13
    reg_pad_tpi_data7_ext1__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data6_ext2__ds0: 1,    //     16
    reg_pad_tpi_data6_ext2__ds1: 1,    //     17
    reg_pad_tpi_data6_ext2__ds2: 1,    //     18
    reg_pad_tpi_data6_ext2__ds3: 1,    //     19
    reg_pad_tpi_data6_ext2__pd:  1,    //     20
    reg_pad_tpi_data6_ext2__pu:  1,    //     21
    reg_pad_tpi_data6_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data6_ext1__ds0: 1,    //     24
    reg_pad_tpi_data6_ext1__ds1: 1,    //     25
    reg_pad_tpi_data6_ext1__ds2: 1,    //     26
    reg_pad_tpi_data6_ext1__ds3: 1,    //     27
    reg_pad_tpi_data6_ext1__pd:  1,    //     28
    reg_pad_tpi_data6_ext1__pu:  1,    //     29
    reg_pad_tpi_data6_ext1__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3024    pad_lnx2_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_val_ext2__ds0 :  1,    //      0
    reg_pad_tpi_val_ext2__ds1 :  1,    //      1
    reg_pad_tpi_val_ext2__ds2 :  1,    //      2
    reg_pad_tpi_val_ext2__ds3 :  1,    //      3
    reg_pad_tpi_val_ext2__pd  :  1,    //      4
    reg_pad_tpi_val_ext2__pu  :  1,    //      5
    reg_pad_tpi_val_ext2__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_val_ext1__ds0 :  1,    //      8
    reg_pad_tpi_val_ext1__ds1 :  1,    //      9
    reg_pad_tpi_val_ext1__ds2 :  1,    //     10
    reg_pad_tpi_val_ext1__ds3 :  1,    //     11
    reg_pad_tpi_val_ext1__pd  :  1,    //     12
    reg_pad_tpi_val_ext1__pu  :  1,    //     13
    reg_pad_tpi_val_ext1__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_sop_ext2__ds0 :  1,    //     16
    reg_pad_tpi_sop_ext2__ds1 :  1,    //     17
    reg_pad_tpi_sop_ext2__ds2 :  1,    //     18
    reg_pad_tpi_sop_ext2__ds3 :  1,    //     19
    reg_pad_tpi_sop_ext2__pd  :  1,    //     20
    reg_pad_tpi_sop_ext2__pu  :  1,    //     21
    reg_pad_tpi_sop_ext2__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_sop_ext1__ds0 :  1,    //     24
    reg_pad_tpi_sop_ext1__ds1 :  1,    //     25
    reg_pad_tpi_sop_ext1__ds2 :  1,    //     26
    reg_pad_tpi_sop_ext1__ds3 :  1,    //     27
    reg_pad_tpi_sop_ext1__pd  :  1,    //     28
    reg_pad_tpi_sop_ext1__pu  :  1,    //     29
    reg_pad_tpi_sop_ext1__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3028    pad_lnx2_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_uart1_tx__ds0     :  1,    //      0
    reg_pad_uart1_tx__ds1     :  1,    //      1
    reg_pad_uart1_tx__ds2     :  1,    //      2
    reg_pad_uart1_tx__ds3     :  1,    //      3
    reg_pad_uart1_tx__pd      :  1,    //      4
    reg_pad_uart1_tx__pu      :  1,    //      5
    reg_pad_uart1_tx__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_uart1_rx__ds0     :  1,    //      8
    reg_pad_uart1_rx__ds1     :  1,    //      9
    reg_pad_uart1_rx__ds2     :  1,    //     10
    reg_pad_uart1_rx__ds3     :  1,    //     11
    reg_pad_uart1_rx__pd      :  1,    //     12
    reg_pad_uart1_rx__pu      :  1,    //     13
    reg_pad_uart1_rx__st      :  1,    //     14
                              : 17;    //  31:15 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_302C    pad_lnx2_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_out__ds0: 1,    //      0
    reg_pad_edid_nisol_out__ds1: 1,    //      1
    reg_pad_edid_nisol_out__ds2: 1,    //      2
    reg_pad_edid_nisol_out__ds3: 1,    //      3
    reg_pad_edid_nisol_out__st:  1,    //      4
                              : 27;    //   31:5 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3100    pad_lnx2_64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl1_mux_sel      :  4,    //   3: 0
    reg_pad_scl0_mux_sel      :  4,    //   7: 4
    reg_pad_ifagc_s_mux_sel   :  4,    //  11: 8
    reg_pad_ifagc_mux_sel     :  4,    //  15:12
    reg_pad_fefctrl_mux_sel   :  4,    //  19:16
    reg_pad_diseqci_mux_sel   :  4,    //  23:20
    reg_pad_diseqc_cmd_mux_sel:  4,    //  27:24
    reg_pad_diseqc_mux_sel    :  4;    //  31:28
}IOMUX_CTRL_BMC_PAD_LNX2_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3104    pad_lnx2_65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda3_mux_sel      :  4,    //   3: 0
    reg_pad_sda2_mux_sel      :  4,    //   7: 4
    reg_pad_sda1_mux_sel      :  4,    //  11: 8
    reg_pad_sda0_mux_sel      :  4,    //  15:12
    reg_pad_scl5_mux_sel      :  4,    //  19:16
    reg_pad_scl4_mux_sel      :  4,    //  23:20
    reg_pad_scl3_mux_sel      :  4,    //  27:24
    reg_pad_scl2_mux_sel      :  4;    //  31:28
}IOMUX_CTRL_BMC_PAD_LNX2_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3108    pad_lnx2_66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data1_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data1_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data0_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data0_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_clk_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_clk_ext1_mux_sel: 4,    //  23:20
    reg_pad_sda5_mux_sel      :  4,    //  27:24
    reg_pad_sda4_mux_sel      :  4;    //  31:28
}IOMUX_CTRL_BMC_PAD_LNX2_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_310C    pad_lnx2_67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data5_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data4_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data4_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data3_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data3_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_data2_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_data2_ext1_mux_sel: 4;    //  31:28
}IOMUX_CTRL_BMC_PAD_LNX2_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3110    pad_lnx2_68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_val_ext2_mux_sel: 4,    //  3: 0
    reg_pad_tpi_val_ext1_mux_sel: 4,    //  7: 4
    reg_pad_tpi_sop_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_sop_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data7_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data7_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_data6_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_data6_ext1_mux_sel: 4;    //  31:28
}IOMUX_CTRL_BMC_PAD_LNX2_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3114    pad_lnx2_69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_out_mux_sel: 4,    //  3:0
    reg_pad_uart1_tx_mux_sel  :  4,    //   7: 4
    reg_pad_uart1_rx_mux_sel  :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}IOMUX_CTRL_BMC_PAD_LNX2_69_O24A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_BMC_PAD_LNX2_00_O24A0_T    pad_lnx2_00;          // 0xC68A_3000
    IOMUX_CTRL_BMC_PAD_LNX2_01_O24A0_T    pad_lnx2_01;          // 0xC68A_3004
    IOMUX_CTRL_BMC_PAD_LNX2_02_O24A0_T    pad_lnx2_02;          // 0xC68A_3008
    IOMUX_CTRL_BMC_PAD_LNX2_03_O24A0_T    pad_lnx2_03;          // 0xC68A_300C
    IOMUX_CTRL_BMC_PAD_LNX2_04_O24A0_T    pad_lnx2_04;          // 0xC68A_3010
    IOMUX_CTRL_BMC_PAD_LNX2_05_O24A0_T    pad_lnx2_05;          // 0xC68A_3014
    IOMUX_CTRL_BMC_PAD_LNX2_06_O24A0_T    pad_lnx2_06;          // 0xC68A_3018
    IOMUX_CTRL_BMC_PAD_LNX2_07_O24A0_T    pad_lnx2_07;          // 0xC68A_301C
    IOMUX_CTRL_BMC_PAD_LNX2_08_O24A0_T    pad_lnx2_08;          // 0xC68A_3020
    IOMUX_CTRL_BMC_PAD_LNX2_09_O24A0_T    pad_lnx2_09;          // 0xC68A_3024
    IOMUX_CTRL_BMC_PAD_LNX2_10_O24A0_T    pad_lnx2_10;          // 0xC68A_3028
    IOMUX_CTRL_BMC_PAD_LNX2_11_O24A0_T    pad_lnx2_11;          // 0xC68A_302C
    UINT32                             _rsvd_00[52];            // 0xC68A_3030 ~ 0xC68A_30FC
    IOMUX_CTRL_BMC_PAD_LNX2_64_O24A0_T    pad_lnx2_64;          // 0xC68A_3100
    IOMUX_CTRL_BMC_PAD_LNX2_65_O24A0_T    pad_lnx2_65;          // 0xC68A_3104
    IOMUX_CTRL_BMC_PAD_LNX2_66_O24A0_T    pad_lnx2_66;          // 0xC68A_3108
    IOMUX_CTRL_BMC_PAD_LNX2_67_O24A0_T    pad_lnx2_67;          // 0xC68A_310C
    IOMUX_CTRL_BMC_PAD_LNX2_68_O24A0_T    pad_lnx2_68;          // 0xC68A_3110
    IOMUX_CTRL_BMC_PAD_LNX2_69_O24A0_T    pad_lnx2_69;          // 0xC68A_3114
}IOMUX_CTRL_BMC_REG_O24A0_T;
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

#define IOMUX_CTRL_BMC_PAD_LNX2_00_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define IOMUX_CTRL_BMC_PAD_LNX2_01_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define IOMUX_CTRL_BMC_PAD_LNX2_02_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define IOMUX_CTRL_BMC_PAD_LNX2_03_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define IOMUX_CTRL_BMC_PAD_LNX2_04_O24A0_T_OFF              (BASEADDRESS+0x0010)
#define IOMUX_CTRL_BMC_PAD_LNX2_05_O24A0_T_OFF              (BASEADDRESS+0x0014)
#define IOMUX_CTRL_BMC_PAD_LNX2_06_O24A0_T_OFF              (BASEADDRESS+0x0018)
#define IOMUX_CTRL_BMC_PAD_LNX2_07_O24A0_T_OFF              (BASEADDRESS+0x001C)
#define IOMUX_CTRL_BMC_PAD_LNX2_08_O24A0_T_OFF              (BASEADDRESS+0x0020)
#define IOMUX_CTRL_BMC_PAD_LNX2_09_O24A0_T_OFF              (BASEADDRESS+0x0024)
#define IOMUX_CTRL_BMC_PAD_LNX2_10_O24A0_T_OFF              (BASEADDRESS+0x0028)
#define IOMUX_CTRL_BMC_PAD_LNX2_11_O24A0_T_OFF              (BASEADDRESS+0x002C)
#define IOMUX_CTRL_BMC_PAD_LNX2_64_O24A0_T_OFF              (BASEADDRESS+0x0100)
#define IOMUX_CTRL_BMC_PAD_LNX2_65_O24A0_T_OFF              (BASEADDRESS+0x0104)
#define IOMUX_CTRL_BMC_PAD_LNX2_66_O24A0_T_OFF              (BASEADDRESS+0x0108)
#define IOMUX_CTRL_BMC_PAD_LNX2_67_O24A0_T_OFF              (BASEADDRESS+0x010C)
#define IOMUX_CTRL_BMC_PAD_LNX2_68_O24A0_T_OFF              (BASEADDRESS+0x0110)
#define IOMUX_CTRL_BMC_PAD_LNX2_69_O24A0_T_OFF              (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xC68A_3000    pad_lnx2_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_fefctrl__ds0: 1;    //      0
    UINT32 reg_pad_fefctrl__ds1: 1;    //      1
    UINT32 reg_pad_fefctrl__ds2: 1;    //      2
    UINT32 reg_pad_fefctrl__ds3: 1;    //      3
    UINT32 reg_pad_fefctrl__pd:  1;    //      4
    UINT32 reg_pad_fefctrl__pu:  1;    //      5
    UINT32 reg_pad_fefctrl__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_diseqci__ds0: 1;    //      8
    UINT32 reg_pad_diseqci__ds1: 1;    //      9
    UINT32 reg_pad_diseqci__ds2: 1;    //     10
    UINT32 reg_pad_diseqci__ds3: 1;    //     11
    UINT32 reg_pad_diseqci__pd:  1;    //     12
    UINT32 reg_pad_diseqci__pu:  1;    //     13
    UINT32 reg_pad_diseqci__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_diseqc_cmd__ds0: 1;    //  16
    UINT32 reg_pad_diseqc_cmd__ds1: 1;    //  17
    UINT32 reg_pad_diseqc_cmd__ds2: 1;    //  18
    UINT32 reg_pad_diseqc_cmd__ds3: 1;    //  19
    UINT32 reg_pad_diseqc_cmd__pd: 1;    //   20
    UINT32 reg_pad_diseqc_cmd__pu: 1;    //   21
    UINT32 reg_pad_diseqc_cmd__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_diseqc__ds0:  1;    //     24
    UINT32 reg_pad_diseqc__ds1:  1;    //     25
    UINT32 reg_pad_diseqc__ds2:  1;    //     26
    UINT32 reg_pad_diseqc__ds3:  1;    //     27
    UINT32 reg_pad_diseqc__pd :  1;    //     28
    UINT32 reg_pad_diseqc__pu :  1;    //     29
    UINT32 reg_pad_diseqc__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3004    pad_lnx2_01 ''
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
    UINT32 reg_pad_scl0__ds0  :  1;    //      8
    UINT32 reg_pad_scl0__ds1  :  1;    //      9
    UINT32 reg_pad_scl0__ds2  :  1;    //     10
    UINT32 reg_pad_scl0__ds3  :  1;    //     11
    UINT32 reg_pad_scl0__pd   :  1;    //     12
    UINT32 reg_pad_scl0__pu   :  1;    //     13
    UINT32 reg_pad_scl0__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ifagc_s__ds0: 1;    //     16
    UINT32 reg_pad_ifagc_s__ds1: 1;    //     17
    UINT32 reg_pad_ifagc_s__ds2: 1;    //     18
    UINT32 reg_pad_ifagc_s__ds3: 1;    //     19
    UINT32 reg_pad_ifagc_s__pd:  1;    //     20
    UINT32 reg_pad_ifagc_s__pu:  1;    //     21
    UINT32 reg_pad_ifagc_s__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ifagc__ds0 :  1;    //     24
    UINT32 reg_pad_ifagc__ds1 :  1;    //     25
    UINT32 reg_pad_ifagc__ds2 :  1;    //     26
    UINT32 reg_pad_ifagc__ds3 :  1;    //     27
    UINT32 reg_pad_ifagc__pd  :  1;    //     28
    UINT32 reg_pad_ifagc__pu  :  1;    //     29
    UINT32 reg_pad_ifagc__st  :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3008    pad_lnx2_02 ''
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
    UINT32 reg_pad_scl4__ds0  :  1;    //      8
    UINT32 reg_pad_scl4__ds1  :  1;    //      9
    UINT32 reg_pad_scl4__ds2  :  1;    //     10
    UINT32 reg_pad_scl4__ds3  :  1;    //     11
    UINT32 reg_pad_scl4__pd   :  1;    //     12
    UINT32 reg_pad_scl4__pu   :  1;    //     13
    UINT32 reg_pad_scl4__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_scl3__ds0  :  1;    //     16
    UINT32 reg_pad_scl3__ds1  :  1;    //     17
    UINT32 reg_pad_scl3__ds2  :  1;    //     18
    UINT32 reg_pad_scl3__ds3  :  1;    //     19
    UINT32 reg_pad_scl3__pd   :  1;    //     20
    UINT32 reg_pad_scl3__pu   :  1;    //     21
    UINT32 reg_pad_scl3__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_scl2__ds0  :  1;    //     24
    UINT32 reg_pad_scl2__ds1  :  1;    //     25
    UINT32 reg_pad_scl2__ds2  :  1;    //     26
    UINT32 reg_pad_scl2__ds3  :  1;    //     27
    UINT32 reg_pad_scl2__pd   :  1;    //     28
    UINT32 reg_pad_scl2__pu   :  1;    //     29
    UINT32 reg_pad_scl2__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_300C    pad_lnx2_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sda3__ds0  :  1;    //      0
    UINT32 reg_pad_sda3__ds1  :  1;    //      1
    UINT32 reg_pad_sda3__ds2  :  1;    //      2
    UINT32 reg_pad_sda3__ds3  :  1;    //      3
    UINT32 reg_pad_sda3__pd   :  1;    //      4
    UINT32 reg_pad_sda3__pu   :  1;    //      5
    UINT32 reg_pad_sda3__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sda2__ds0  :  1;    //      8
    UINT32 reg_pad_sda2__ds1  :  1;    //      9
    UINT32 reg_pad_sda2__ds2  :  1;    //     10
    UINT32 reg_pad_sda2__ds3  :  1;    //     11
    UINT32 reg_pad_sda2__pd   :  1;    //     12
    UINT32 reg_pad_sda2__pu   :  1;    //     13
    UINT32 reg_pad_sda2__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_sda1__ds0  :  1;    //     16
    UINT32 reg_pad_sda1__ds1  :  1;    //     17
    UINT32 reg_pad_sda1__ds2  :  1;    //     18
    UINT32 reg_pad_sda1__ds3  :  1;    //     19
    UINT32 reg_pad_sda1__pd   :  1;    //     20
    UINT32 reg_pad_sda1__pu   :  1;    //     21
    UINT32 reg_pad_sda1__st   :  1;    //     22
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
}IOMUX_CTRL_BMC_PAD_LNX2_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3010    pad_lnx2_04 ''
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
    UINT32 reg_pad_tpi_clk_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_clk_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_clk_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_clk_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_clk_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_clk_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_clk_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_sda5__ds0  :  1;    //     16
    UINT32 reg_pad_sda5__ds1  :  1;    //     17
    UINT32 reg_pad_sda5__ds2  :  1;    //     18
    UINT32 reg_pad_sda5__ds3  :  1;    //     19
    UINT32 reg_pad_sda5__pd   :  1;    //     20
    UINT32 reg_pad_sda5__pu   :  1;    //     21
    UINT32 reg_pad_sda5__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sda4__ds0  :  1;    //     24
    UINT32 reg_pad_sda4__ds1  :  1;    //     25
    UINT32 reg_pad_sda4__ds2  :  1;    //     26
    UINT32 reg_pad_sda4__ds3  :  1;    //     27
    UINT32 reg_pad_sda4__pd   :  1;    //     28
    UINT32 reg_pad_sda4__pu   :  1;    //     29
    UINT32 reg_pad_sda4__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3014    pad_lnx2_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data1_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data1_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data1_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data1_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data1_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_data1_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_data1_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data1_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data1_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data1_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data1_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data1_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data1_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data1_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data0_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data0_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data0_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data0_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data0_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data0_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data0_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data0_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data0_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data0_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data0_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data0_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data0_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data0_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3018    pad_lnx2_06 ''
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
    UINT32 reg_pad_tpi_data3_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data3_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data3_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data3_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data3_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data3_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data3_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data2_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data2_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data2_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data2_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data2_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data2_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data2_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data2_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data2_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data2_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data2_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data2_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data2_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data2_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_301C    pad_lnx2_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data5_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data5_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data5_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data5_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data5_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_data5_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_data5_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data5_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data5_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data5_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data5_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data5_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data5_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data5_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data4_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data4_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data4_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data4_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data4_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data4_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data4_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data4_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data4_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data4_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data4_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data4_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data4_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data4_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3020    pad_lnx2_08 ''
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
    UINT32 reg_pad_tpi_data7_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data7_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data7_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data7_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data7_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_data7_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_data7_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data6_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data6_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data6_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data6_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data6_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data6_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data6_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data6_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data6_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data6_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data6_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data6_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_data6_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_data6_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3024    pad_lnx2_09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_val_ext2__ds0: 1;    //  0
    UINT32 reg_pad_tpi_val_ext2__ds1: 1;    //  1
    UINT32 reg_pad_tpi_val_ext2__ds2: 1;    //  2
    UINT32 reg_pad_tpi_val_ext2__ds3: 1;    //  3
    UINT32 reg_pad_tpi_val_ext2__pd: 1;    //  4
    UINT32 reg_pad_tpi_val_ext2__pu: 1;    //  5
    UINT32 reg_pad_tpi_val_ext2__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_val_ext1__ds0: 1;    //  8
    UINT32 reg_pad_tpi_val_ext1__ds1: 1;    //  9
    UINT32 reg_pad_tpi_val_ext1__ds2: 1;    //  10
    UINT32 reg_pad_tpi_val_ext1__ds3: 1;    //  11
    UINT32 reg_pad_tpi_val_ext1__pd: 1;    //  12
    UINT32 reg_pad_tpi_val_ext1__pu: 1;    //  13
    UINT32 reg_pad_tpi_val_ext1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_sop_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_sop_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_sop_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_sop_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_sop_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_sop_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_sop_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_sop_ext1__ds0: 1;    //  24
    UINT32 reg_pad_tpi_sop_ext1__ds1: 1;    //  25
    UINT32 reg_pad_tpi_sop_ext1__ds2: 1;    //  26
    UINT32 reg_pad_tpi_sop_ext1__ds3: 1;    //  27
    UINT32 reg_pad_tpi_sop_ext1__pd: 1;    //  28
    UINT32 reg_pad_tpi_sop_ext1__pu: 1;    //  29
    UINT32 reg_pad_tpi_sop_ext1__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3028    pad_lnx2_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_uart1_tx__ds0: 1;    //     0
    UINT32 reg_pad_uart1_tx__ds1: 1;    //     1
    UINT32 reg_pad_uart1_tx__ds2: 1;    //     2
    UINT32 reg_pad_uart1_tx__ds3: 1;    //     3
    UINT32 reg_pad_uart1_tx__pd: 1;    //      4
    UINT32 reg_pad_uart1_tx__pu: 1;    //      5
    UINT32 reg_pad_uart1_tx__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_uart1_rx__ds0: 1;    //     8
    UINT32 reg_pad_uart1_rx__ds1: 1;    //     9
    UINT32 reg_pad_uart1_rx__ds2: 1;    //    10
    UINT32 reg_pad_uart1_rx__ds3: 1;    //    11
    UINT32 reg_pad_uart1_rx__pd: 1;    //     12
    UINT32 reg_pad_uart1_rx__pu: 1;    //     13
    UINT32 reg_pad_uart1_rx__st: 1;    //     14
    UINT32 resvd01            : 17;    //  31:15 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_302C    pad_lnx2_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edid_nisol_out__ds0: 1;    //  0
    UINT32 reg_pad_edid_nisol_out__ds1: 1;    //  1
    UINT32 reg_pad_edid_nisol_out__ds2: 1;    //  2
    UINT32 reg_pad_edid_nisol_out__ds3: 1;    //  3
    UINT32 reg_pad_edid_nisol_out__st: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3100    pad_lnx2_64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_scl1_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_scl0_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_ifagc_s_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ifagc_mux_sel: 4;    //  15:12
    UINT32 reg_pad_fefctrl_mux_sel: 4;    //  19:16
    UINT32 reg_pad_diseqci_mux_sel: 4;    //  23:20
    UINT32 reg_pad_diseqc_cmd_mux_sel: 4;    //  27:24
    UINT32 reg_pad_diseqc_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_LNX2_64_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3104    pad_lnx2_65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sda3_mux_sel: 4;    //   3: 0
    UINT32 reg_pad_sda2_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_sda1_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_sda0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_scl5_mux_sel: 4;    //  19:16
    UINT32 reg_pad_scl4_mux_sel: 4;    //  23:20
    UINT32 reg_pad_scl3_mux_sel: 4;    //  27:24
    UINT32 reg_pad_scl2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_LNX2_65_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3108    pad_lnx2_66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data1_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data1_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data0_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data0_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_clk_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_clk_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_sda5_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sda4_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_LNX2_66_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_310C    pad_lnx2_67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data5_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data5_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data4_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data4_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data3_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data3_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data2_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data2_ext1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_LNX2_67_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3110    pad_lnx2_68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_val_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_val_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_sop_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_sop_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data7_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data7_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data6_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data6_ext1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_LNX2_68_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC68A_3114    pad_lnx2_69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edid_nisol_out_mux_sel: 4;    //  3:0
    UINT32 reg_pad_uart1_tx_mux_sel: 4;    //  7:4
    UINT32 reg_pad_uart1_rx_mux_sel: 4;    //  11:8
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}IOMUX_CTRL_BMC_PAD_LNX2_69_O24A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_BMC_PAD_LNX2_00_O24A0_T    pad_lnx2_00;          // 0xC68A_3000
    IOMUX_CTRL_BMC_PAD_LNX2_01_O24A0_T    pad_lnx2_01;          // 0xC68A_3004
    IOMUX_CTRL_BMC_PAD_LNX2_02_O24A0_T    pad_lnx2_02;          // 0xC68A_3008
    IOMUX_CTRL_BMC_PAD_LNX2_03_O24A0_T    pad_lnx2_03;          // 0xC68A_300C
    IOMUX_CTRL_BMC_PAD_LNX2_04_O24A0_T    pad_lnx2_04;          // 0xC68A_3010
    IOMUX_CTRL_BMC_PAD_LNX2_05_O24A0_T    pad_lnx2_05;          // 0xC68A_3014
    IOMUX_CTRL_BMC_PAD_LNX2_06_O24A0_T    pad_lnx2_06;          // 0xC68A_3018
    IOMUX_CTRL_BMC_PAD_LNX2_07_O24A0_T    pad_lnx2_07;          // 0xC68A_301C
    IOMUX_CTRL_BMC_PAD_LNX2_08_O24A0_T    pad_lnx2_08;          // 0xC68A_3020
    IOMUX_CTRL_BMC_PAD_LNX2_09_O24A0_T    pad_lnx2_09;          // 0xC68A_3024
    IOMUX_CTRL_BMC_PAD_LNX2_10_O24A0_T    pad_lnx2_10;          // 0xC68A_3028
    IOMUX_CTRL_BMC_PAD_LNX2_11_O24A0_T    pad_lnx2_11;          // 0xC68A_302C
    UINT32                             _rsvd_00[52];            // 0xC68A_3030 ~ 0xC68A_30FC
    IOMUX_CTRL_BMC_PAD_LNX2_64_O24A0_T    pad_lnx2_64;          // 0xC68A_3100
    IOMUX_CTRL_BMC_PAD_LNX2_65_O24A0_T    pad_lnx2_65;          // 0xC68A_3104
    IOMUX_CTRL_BMC_PAD_LNX2_66_O24A0_T    pad_lnx2_66;          // 0xC68A_3108
    IOMUX_CTRL_BMC_PAD_LNX2_67_O24A0_T    pad_lnx2_67;          // 0xC68A_310C
    IOMUX_CTRL_BMC_PAD_LNX2_68_O24A0_T    pad_lnx2_68;          // 0xC68A_3110
    IOMUX_CTRL_BMC_PAD_LNX2_69_O24A0_T    pad_lnx2_69;          // 0xC68A_3114
}IOMUX_CTRL_BMC_REG_O24A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _IOMUX_CTRL_BMC_REG_H_

/* from 'O24_CTOP_PAD_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

