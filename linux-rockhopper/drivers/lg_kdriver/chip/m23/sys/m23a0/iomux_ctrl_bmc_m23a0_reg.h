#ifndef _IOMUX_CTRL_BMC_M23A0_REG_H_
#define _IOMUX_CTRL_BMC_M23A0_REG_H_

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
    0x0    pad_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sda5__ds0         :  1,    //      0
    reg_pad_sda5__ds1         :  1,    //      1
    reg_pad_sda5__ds2         :  1,    //      2
    reg_pad_sda5__ds3         :  1,    //      3
    reg_pad_sda5__pd          :  1,    //      4
    reg_pad_sda5__pu          :  1,    //      5
    reg_pad_sda5__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_scl5__ds0         :  1,    //      8
    reg_pad_scl5__ds1         :  1,    //      9
    reg_pad_scl5__ds2         :  1,    //     10
    reg_pad_scl5__ds3         :  1,    //     11
    reg_pad_scl5__pd          :  1,    //     12
    reg_pad_scl5__pu          :  1,    //     13
    reg_pad_scl5__st          :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sda4__ds0         :  1,    //     16
    reg_pad_sda4__ds1         :  1,    //     17
    reg_pad_sda4__ds2         :  1,    //     18
    reg_pad_sda4__ds3         :  1,    //     19
    reg_pad_sda4__pd          :  1,    //     20
    reg_pad_sda4__pu          :  1,    //     21
    reg_pad_sda4__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_scl4__ds0         :  1,    //     24
    reg_pad_scl4__ds1         :  1,    //     25
    reg_pad_scl4__ds2         :  1,    //     26
    reg_pad_scl4__ds3         :  1,    //     27
    reg_pad_scl4__pd          :  1,    //     28
    reg_pad_scl4__pu          :  1,    //     29
    reg_pad_scl4__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_bmc01 ''
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
    reg_pad_ifagc_s__ds0      :  1,    //      8
    reg_pad_ifagc_s__ds1      :  1,    //      9
    reg_pad_ifagc_s__ds2      :  1,    //     10
    reg_pad_ifagc_s__ds3      :  1,    //     11
    reg_pad_ifagc_s__pd       :  1,    //     12
    reg_pad_ifagc_s__pu       :  1,    //     13
    reg_pad_ifagc_s__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ifagc__ds0        :  1,    //     16
    reg_pad_ifagc__ds1        :  1,    //     17
    reg_pad_ifagc__ds2        :  1,    //     18
    reg_pad_ifagc__ds3        :  1,    //     19
    reg_pad_ifagc__pd         :  1,    //     20
    reg_pad_ifagc__pu         :  1,    //     21
    reg_pad_ifagc__st         :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_diseqc__ds0       :  1,    //     24
    reg_pad_diseqc__ds1       :  1,    //     25
    reg_pad_diseqc__ds2       :  1,    //     26
    reg_pad_diseqc__ds3       :  1,    //     27
    reg_pad_diseqc__pd        :  1,    //     28
    reg_pad_diseqc__pu        :  1,    //     29
    reg_pad_diseqc__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_bmc02 ''
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
}IOMUX_CTRL_BMC_PAD_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_bmc03 ''
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
}IOMUX_CTRL_BMC_PAD_BMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_bmc04 ''
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
}IOMUX_CTRL_BMC_PAD_BMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_bmc05 ''
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
}IOMUX_CTRL_BMC_PAD_BMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_bmc06 ''
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
    reg_pad_tpi_data0_ext2__ds0: 1,    //      8
    reg_pad_tpi_data0_ext2__ds1: 1,    //      9
    reg_pad_tpi_data0_ext2__ds2: 1,    //     10
    reg_pad_tpi_data0_ext2__ds3: 1,    //     11
    reg_pad_tpi_data0_ext2__pd:  1,    //     12
    reg_pad_tpi_data0_ext2__pu:  1,    //     13
    reg_pad_tpi_data0_ext2__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_clk_ext2__ds0 :  1,    //     16
    reg_pad_tpi_clk_ext2__ds1 :  1,    //     17
    reg_pad_tpi_clk_ext2__ds2 :  1,    //     18
    reg_pad_tpi_clk_ext2__ds3 :  1,    //     19
    reg_pad_tpi_clk_ext2__pd  :  1,    //     20
    reg_pad_tpi_clk_ext2__pu  :  1,    //     21
    reg_pad_tpi_clk_ext2__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_val_ext1__ds0 :  1,    //     24
    reg_pad_tpi_val_ext1__ds1 :  1,    //     25
    reg_pad_tpi_val_ext1__ds2 :  1,    //     26
    reg_pad_tpi_val_ext1__ds3 :  1,    //     27
    reg_pad_tpi_val_ext1__pd  :  1,    //     28
    reg_pad_tpi_val_ext1__pu  :  1,    //     29
    reg_pad_tpi_val_ext1__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_BMC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_bmc07 ''
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
    reg_pad_tpi_data4_ext2__ds0: 1,    //      8
    reg_pad_tpi_data4_ext2__ds1: 1,    //      9
    reg_pad_tpi_data4_ext2__ds2: 1,    //     10
    reg_pad_tpi_data4_ext2__ds3: 1,    //     11
    reg_pad_tpi_data4_ext2__pd:  1,    //     12
    reg_pad_tpi_data4_ext2__pu:  1,    //     13
    reg_pad_tpi_data4_ext2__st:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data3_ext2__ds0: 1,    //     16
    reg_pad_tpi_data3_ext2__ds1: 1,    //     17
    reg_pad_tpi_data3_ext2__ds2: 1,    //     18
    reg_pad_tpi_data3_ext2__ds3: 1,    //     19
    reg_pad_tpi_data3_ext2__pd:  1,    //     20
    reg_pad_tpi_data3_ext2__pu:  1,    //     21
    reg_pad_tpi_data3_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data2_ext2__ds0: 1,    //     24
    reg_pad_tpi_data2_ext2__ds1: 1,    //     25
    reg_pad_tpi_data2_ext2__ds2: 1,    //     26
    reg_pad_tpi_data2_ext2__ds3: 1,    //     27
    reg_pad_tpi_data2_ext2__pd:  1,    //     28
    reg_pad_tpi_data2_ext2__pu:  1,    //     29
    reg_pad_tpi_data2_ext2__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_BMC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_bmc08 ''
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
    reg_pad_tpi_sop_ext2__ds0 :  1,    //      8
    reg_pad_tpi_sop_ext2__ds1 :  1,    //      9
    reg_pad_tpi_sop_ext2__ds2 :  1,    //     10
    reg_pad_tpi_sop_ext2__ds3 :  1,    //     11
    reg_pad_tpi_sop_ext2__pd  :  1,    //     12
    reg_pad_tpi_sop_ext2__pu  :  1,    //     13
    reg_pad_tpi_sop_ext2__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data7_ext2__ds0: 1,    //     16
    reg_pad_tpi_data7_ext2__ds1: 1,    //     17
    reg_pad_tpi_data7_ext2__ds2: 1,    //     18
    reg_pad_tpi_data7_ext2__ds3: 1,    //     19
    reg_pad_tpi_data7_ext2__pd:  1,    //     20
    reg_pad_tpi_data7_ext2__pu:  1,    //     21
    reg_pad_tpi_data7_ext2__st:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data6_ext2__ds0: 1,    //     24
    reg_pad_tpi_data6_ext2__ds1: 1,    //     25
    reg_pad_tpi_data6_ext2__ds2: 1,    //     26
    reg_pad_tpi_data6_ext2__ds3: 1,    //     27
    reg_pad_tpi_data6_ext2__pd:  1,    //     28
    reg_pad_tpi_data6_ext2__pu:  1,    //     29
    reg_pad_tpi_data6_ext2__st:  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_BMC_PAD_BMC08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_bmc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pad_edid_nisol_out__ds0: 1,    //      1
    reg_pad_edid_nisol_out__ds1: 1,    //      2
    reg_pad_edid_nisol_out__ds2: 1,    //      3
    reg_pad_edid_nisol_out__ds3: 1,    //      4
                              :  1,    //      5 reserved
    reg_pad_edid_nisol_out__st:  1,    //      6
                              : 25;    //   31:7 reserved
}IOMUX_CTRL_BMC_PAD_BMC09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_bmc64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio16_mux_sel    :  4,    //   3: 0
    reg_pad_ifagc_s_mux_sel   :  4,    //   7: 4
    reg_pad_ifagc_mux_sel     :  4,    //  11: 8
    reg_pad_diseqc_mux_sel    :  4,    //  15:12
    reg_pad_sda5_mux_sel      :  4,    //  19:16
    reg_pad_scl5_mux_sel      :  4,    //  23:20
    reg_pad_sda4_mux_sel      :  4,    //  27:24
    reg_pad_scl4_mux_sel      :  4;    //  31:28
}IOMUX_CTRL_BMC_PAD_BMC64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_bmc65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_ext1_mux_sel: 4,    //  3:0
    reg_pad_tpi_clk_ext1_mux_sel: 4,    //  7: 4
    reg_pad_gpio22_mux_sel    :  4,    //  11: 8
    reg_pad_gpio21_mux_sel    :  4,    //  15:12
    reg_pad_gpio20_mux_sel    :  4,    //  19:16
    reg_pad_gpio19_mux_sel    :  4,    //  23:20
    reg_pad_gpio18_mux_sel    :  4,    //  27:24
    reg_pad_gpio17_mux_sel    :  4;    //  31:28
}IOMUX_CTRL_BMC_PAD_BMC65_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_bmc66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_sop_ext1_mux_sel: 4,    //  3: 0
    reg_pad_tpi_data7_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data6_ext1_mux_sel: 4,    //  11:8
    reg_pad_tpi_data5_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data4_ext1_mux_sel: 4,    //  19:16
    reg_pad_tpi_data3_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_data2_ext1_mux_sel: 4,    //  27:24
    reg_pad_tpi_data1_ext1_mux_sel: 4;    //  31:28
}IOMUX_CTRL_BMC_PAD_BMC66_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_bmc67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data4_ext2_mux_sel: 4,    //  7:4
    reg_pad_tpi_data3_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data2_ext2_mux_sel: 4,    //  15:12
    reg_pad_tpi_data1_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data0_ext2_mux_sel: 4,    //  23:20
    reg_pad_tpi_clk_ext2_mux_sel: 4,    //  27:24
    reg_pad_tpi_val_ext1_mux_sel: 4;    //  31:28
}IOMUX_CTRL_BMC_PAD_BMC67_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_bmc68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_out_mux_sel: 4,    //  3:0
    reg_pad_tpi_val_ext2_mux_sel: 4,    //  7: 4
    reg_pad_tpi_sop_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data7_ext2_mux_sel: 4,    //  15:12
    reg_pad_tpi_data6_ext2_mux_sel: 4,    //  19:16
                              : 12;    //  31:20 reserved
}IOMUX_CTRL_BMC_PAD_BMC68_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_BMC_PAD_BMC00_M23A0_T     pad_bmc00  ;             // 0x0
    IOMUX_CTRL_BMC_PAD_BMC01_M23A0_T     pad_bmc01  ;             // 0x4
    IOMUX_CTRL_BMC_PAD_BMC02_M23A0_T     pad_bmc02  ;             // 0x8
    IOMUX_CTRL_BMC_PAD_BMC03_M23A0_T     pad_bmc03  ;             // 0xC
    IOMUX_CTRL_BMC_PAD_BMC04_M23A0_T     pad_bmc04  ;             // 0x10
    IOMUX_CTRL_BMC_PAD_BMC05_M23A0_T     pad_bmc05  ;             // 0x14
    IOMUX_CTRL_BMC_PAD_BMC06_M23A0_T     pad_bmc06  ;             // 0x18
    IOMUX_CTRL_BMC_PAD_BMC07_M23A0_T     pad_bmc07  ;             // 0x1C
    IOMUX_CTRL_BMC_PAD_BMC08_M23A0_T     pad_bmc08  ;             // 0x20
    IOMUX_CTRL_BMC_PAD_BMC09_M23A0_T     pad_bmc09  ;             // 0x24
    UINT32                             _rsvd_00[54];            // 0x28 ~ 0xFC
    IOMUX_CTRL_BMC_PAD_BMC64_M23A0_T     pad_bmc64  ;             // 0x100
    IOMUX_CTRL_BMC_PAD_BMC65_M23A0_T     pad_bmc65  ;             // 0x104
    IOMUX_CTRL_BMC_PAD_BMC66_M23A0_T     pad_bmc66  ;             // 0x108
    IOMUX_CTRL_BMC_PAD_BMC67_M23A0_T     pad_bmc67  ;             // 0x10C
    IOMUX_CTRL_BMC_PAD_BMC68_M23A0_T     pad_bmc68  ;             // 0x110
}IOMUX_CTRL_BMC_REG_M23A0_T;
/* 15 regs */

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

#define IOMUX_CTRL_BMC_PAD_BMC00_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define IOMUX_CTRL_BMC_PAD_BMC01_M23A0_T_OFF                  (BASEADDRESS+0x0004)
#define IOMUX_CTRL_BMC_PAD_BMC02_M23A0_T_OFF                  (BASEADDRESS+0x0008)
#define IOMUX_CTRL_BMC_PAD_BMC03_M23A0_T_OFF                  (BASEADDRESS+0x000C)
#define IOMUX_CTRL_BMC_PAD_BMC04_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define IOMUX_CTRL_BMC_PAD_BMC05_M23A0_T_OFF                  (BASEADDRESS+0x0014)
#define IOMUX_CTRL_BMC_PAD_BMC06_M23A0_T_OFF                  (BASEADDRESS+0x0018)
#define IOMUX_CTRL_BMC_PAD_BMC07_M23A0_T_OFF                  (BASEADDRESS+0x001C)
#define IOMUX_CTRL_BMC_PAD_BMC08_M23A0_T_OFF                  (BASEADDRESS+0x0020)
#define IOMUX_CTRL_BMC_PAD_BMC09_M23A0_T_OFF                  (BASEADDRESS+0x0024)
#define IOMUX_CTRL_BMC_PAD_BMC64_M23A0_T_OFF                  (BASEADDRESS+0x0100)
#define IOMUX_CTRL_BMC_PAD_BMC65_M23A0_T_OFF                  (BASEADDRESS+0x0104)
#define IOMUX_CTRL_BMC_PAD_BMC66_M23A0_T_OFF                  (BASEADDRESS+0x0108)
#define IOMUX_CTRL_BMC_PAD_BMC67_M23A0_T_OFF                  (BASEADDRESS+0x010C)
#define IOMUX_CTRL_BMC_PAD_BMC68_M23A0_T_OFF                  (BASEADDRESS+0x0110)

/*-----------------------------------------------------------------------------------------
    0x0    pad_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sda5__ds0  :  1;    //      0
    UINT32 reg_pad_sda5__ds1  :  1;    //      1
    UINT32 reg_pad_sda5__ds2  :  1;    //      2
    UINT32 reg_pad_sda5__ds3  :  1;    //      3
    UINT32 reg_pad_sda5__pd   :  1;    //      4
    UINT32 reg_pad_sda5__pu   :  1;    //      5
    UINT32 reg_pad_sda5__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_scl5__ds0  :  1;    //      8
    UINT32 reg_pad_scl5__ds1  :  1;    //      9
    UINT32 reg_pad_scl5__ds2  :  1;    //     10
    UINT32 reg_pad_scl5__ds3  :  1;    //     11
    UINT32 reg_pad_scl5__pd   :  1;    //     12
    UINT32 reg_pad_scl5__pu   :  1;    //     13
    UINT32 reg_pad_scl5__st   :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_sda4__ds0  :  1;    //     16
    UINT32 reg_pad_sda4__ds1  :  1;    //     17
    UINT32 reg_pad_sda4__ds2  :  1;    //     18
    UINT32 reg_pad_sda4__ds3  :  1;    //     19
    UINT32 reg_pad_sda4__pd   :  1;    //     20
    UINT32 reg_pad_sda4__pu   :  1;    //     21
    UINT32 reg_pad_sda4__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_scl4__ds0  :  1;    //     24
    UINT32 reg_pad_scl4__ds1  :  1;    //     25
    UINT32 reg_pad_scl4__ds2  :  1;    //     26
    UINT32 reg_pad_scl4__ds3  :  1;    //     27
    UINT32 reg_pad_scl4__pd   :  1;    //     28
    UINT32 reg_pad_scl4__pu   :  1;    //     29
    UINT32 reg_pad_scl4__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_bmc01 ''
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
    UINT32 reg_pad_ifagc_s__ds0: 1;    //      8
    UINT32 reg_pad_ifagc_s__ds1: 1;    //      9
    UINT32 reg_pad_ifagc_s__ds2: 1;    //     10
    UINT32 reg_pad_ifagc_s__ds3: 1;    //     11
    UINT32 reg_pad_ifagc_s__pd:  1;    //     12
    UINT32 reg_pad_ifagc_s__pu:  1;    //     13
    UINT32 reg_pad_ifagc_s__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ifagc__ds0 :  1;    //     16
    UINT32 reg_pad_ifagc__ds1 :  1;    //     17
    UINT32 reg_pad_ifagc__ds2 :  1;    //     18
    UINT32 reg_pad_ifagc__ds3 :  1;    //     19
    UINT32 reg_pad_ifagc__pd  :  1;    //     20
    UINT32 reg_pad_ifagc__pu  :  1;    //     21
    UINT32 reg_pad_ifagc__st  :  1;    //     22
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
}IOMUX_CTRL_BMC_PAD_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_bmc02 ''
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
}IOMUX_CTRL_BMC_PAD_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_bmc03 ''
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
}IOMUX_CTRL_BMC_PAD_BMC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_bmc04 ''
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
}IOMUX_CTRL_BMC_PAD_BMC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_bmc05 ''
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
}IOMUX_CTRL_BMC_PAD_BMC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_bmc06 ''
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
    UINT32 reg_pad_tpi_data0_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data0_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data0_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data0_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data0_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_data0_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_data0_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_clk_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_clk_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_clk_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_clk_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_clk_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_clk_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_clk_ext2__st: 1;    //  22
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
}IOMUX_CTRL_BMC_PAD_BMC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_bmc07 ''
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
    UINT32 reg_pad_tpi_data4_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data4_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data4_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data4_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data4_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_data4_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_data4_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data3_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data3_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data3_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data3_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data3_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data3_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data3_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data2_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data2_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data2_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data2_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data2_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_data2_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_data2_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_BMC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_bmc08 ''
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
    UINT32 reg_pad_tpi_sop_ext2__ds0: 1;    //  8
    UINT32 reg_pad_tpi_sop_ext2__ds1: 1;    //  9
    UINT32 reg_pad_tpi_sop_ext2__ds2: 1;    //  10
    UINT32 reg_pad_tpi_sop_ext2__ds3: 1;    //  11
    UINT32 reg_pad_tpi_sop_ext2__pd: 1;    //  12
    UINT32 reg_pad_tpi_sop_ext2__pu: 1;    //  13
    UINT32 reg_pad_tpi_sop_ext2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data7_ext2__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data7_ext2__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data7_ext2__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data7_ext2__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data7_ext2__pd: 1;    //  20
    UINT32 reg_pad_tpi_data7_ext2__pu: 1;    //  21
    UINT32 reg_pad_tpi_data7_ext2__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data6_ext2__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data6_ext2__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data6_ext2__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data6_ext2__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data6_ext2__pd: 1;    //  28
    UINT32 reg_pad_tpi_data6_ext2__pu: 1;    //  29
    UINT32 reg_pad_tpi_data6_ext2__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_BMC_PAD_BMC08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_bmc09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pad_edid_nisol_out__ds0: 1;    //  1
    UINT32 reg_pad_edid_nisol_out__ds1: 1;    //  2
    UINT32 reg_pad_edid_nisol_out__ds2: 1;    //  3
    UINT32 reg_pad_edid_nisol_out__ds3: 1;    //  4
    UINT32 resvd01            :  1;    //      5 reserved
    UINT32 reg_pad_edid_nisol_out__st: 1;    //  6
    UINT32 resvd02            : 25;    //   31:7 reserved
    };
}IOMUX_CTRL_BMC_PAD_BMC09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_bmc64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio16_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ifagc_s_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ifagc_mux_sel: 4;    //  11:8
    UINT32 reg_pad_diseqc_mux_sel: 4;    //  15:12
    UINT32 reg_pad_sda5_mux_sel: 4;    //  19:16
    UINT32 reg_pad_scl5_mux_sel: 4;    //  23:20
    UINT32 reg_pad_sda4_mux_sel: 4;    //  27:24
    UINT32 reg_pad_scl4_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_BMC64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_bmc65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data0_ext1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_clk_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio22_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio21_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio20_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio19_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio18_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio17_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_BMC65_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_bmc66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_sop_ext1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data7_ext1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data6_ext1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data5_ext1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data4_ext1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data3_ext1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data2_ext1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data1_ext1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_BMC66_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_bmc67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data5_ext2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data4_ext2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data3_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data2_ext2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data1_ext2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data0_ext2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_clk_ext2_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_val_ext1_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_BMC_PAD_BMC67_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_bmc68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edid_nisol_out_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_val_ext2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_sop_ext2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data7_ext2_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data6_ext2_mux_sel: 4;    //  19:16
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}IOMUX_CTRL_BMC_PAD_BMC68_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_BMC_PAD_BMC00_M23A0_T     pad_bmc00  ;             // 0x0
    IOMUX_CTRL_BMC_PAD_BMC01_M23A0_T     pad_bmc01  ;             // 0x4
    IOMUX_CTRL_BMC_PAD_BMC02_M23A0_T     pad_bmc02  ;             // 0x8
    IOMUX_CTRL_BMC_PAD_BMC03_M23A0_T     pad_bmc03  ;             // 0xC
    IOMUX_CTRL_BMC_PAD_BMC04_M23A0_T     pad_bmc04  ;             // 0x10
    IOMUX_CTRL_BMC_PAD_BMC05_M23A0_T     pad_bmc05  ;             // 0x14
    IOMUX_CTRL_BMC_PAD_BMC06_M23A0_T     pad_bmc06  ;             // 0x18
    IOMUX_CTRL_BMC_PAD_BMC07_M23A0_T     pad_bmc07  ;             // 0x1C
    IOMUX_CTRL_BMC_PAD_BMC08_M23A0_T     pad_bmc08  ;             // 0x20
    IOMUX_CTRL_BMC_PAD_BMC09_M23A0_T     pad_bmc09  ;             // 0x24
    UINT32                             _rsvd_00[54];            // 0x28 ~ 0xFC
    IOMUX_CTRL_BMC_PAD_BMC64_M23A0_T     pad_bmc64  ;             // 0x100
    IOMUX_CTRL_BMC_PAD_BMC65_M23A0_T     pad_bmc65  ;             // 0x104
    IOMUX_CTRL_BMC_PAD_BMC66_M23A0_T     pad_bmc66  ;             // 0x108
    IOMUX_CTRL_BMC_PAD_BMC67_M23A0_T     pad_bmc67  ;             // 0x10C
    IOMUX_CTRL_BMC_PAD_BMC68_M23A0_T     pad_bmc68  ;             // 0x110
}IOMUX_CTRL_BMC_REG_M23A0_T;
/* 15 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_PAD_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

