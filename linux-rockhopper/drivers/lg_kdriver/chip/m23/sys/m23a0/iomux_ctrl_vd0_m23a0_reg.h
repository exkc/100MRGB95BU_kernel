#ifndef _IOMUX_CTRL_VD0_M23A0_REG_H_
#define _IOMUX_CTRL_VD0_M23A0_REG_H_

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
    0x0    pad_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data2_cam__ds0:  1,    //      0
    reg_pad_tpi_data2_cam__ds1:  1,    //      1
    reg_pad_tpi_data2_cam__ds2:  1,    //      2
    reg_pad_tpi_data2_cam__ds3:  1,    //      3
    reg_pad_tpi_data2_cam__pd :  1,    //      4
    reg_pad_tpi_data2_cam__pu :  1,    //      5
    reg_pad_tpi_data2_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data1_cam__ds0:  1,    //      8
    reg_pad_tpi_data1_cam__ds1:  1,    //      9
    reg_pad_tpi_data1_cam__ds2:  1,    //     10
    reg_pad_tpi_data1_cam__ds3:  1,    //     11
    reg_pad_tpi_data1_cam__pd :  1,    //     12
    reg_pad_tpi_data1_cam__pu :  1,    //     13
    reg_pad_tpi_data1_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data0_cam__ds0:  1,    //     16
    reg_pad_tpi_data0_cam__ds1:  1,    //     17
    reg_pad_tpi_data0_cam__ds2:  1,    //     18
    reg_pad_tpi_data0_cam__ds3:  1,    //     19
    reg_pad_tpi_data0_cam__pd :  1,    //     20
    reg_pad_tpi_data0_cam__pu :  1,    //     21
    reg_pad_tpi_data0_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_clk_cam__ds0  :  1,    //     24
    reg_pad_tpi_clk_cam__ds1  :  1,    //     25
    reg_pad_tpi_clk_cam__ds2  :  1,    //     26
    reg_pad_tpi_clk_cam__ds3  :  1,    //     27
    reg_pad_tpi_clk_cam__pd   :  1,    //     28
    reg_pad_tpi_clk_cam__pu   :  1,    //     29
    reg_pad_tpi_clk_cam__st   :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data6_cam__ds0:  1,    //      0
    reg_pad_tpi_data6_cam__ds1:  1,    //      1
    reg_pad_tpi_data6_cam__ds2:  1,    //      2
    reg_pad_tpi_data6_cam__ds3:  1,    //      3
    reg_pad_tpi_data6_cam__pd :  1,    //      4
    reg_pad_tpi_data6_cam__pu :  1,    //      5
    reg_pad_tpi_data6_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data5_cam__ds0:  1,    //      8
    reg_pad_tpi_data5_cam__ds1:  1,    //      9
    reg_pad_tpi_data5_cam__ds2:  1,    //     10
    reg_pad_tpi_data5_cam__ds3:  1,    //     11
    reg_pad_tpi_data5_cam__pd :  1,    //     12
    reg_pad_tpi_data5_cam__pu :  1,    //     13
    reg_pad_tpi_data5_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data4_cam__ds0:  1,    //     16
    reg_pad_tpi_data4_cam__ds1:  1,    //     17
    reg_pad_tpi_data4_cam__ds2:  1,    //     18
    reg_pad_tpi_data4_cam__ds3:  1,    //     19
    reg_pad_tpi_data4_cam__pd :  1,    //     20
    reg_pad_tpi_data4_cam__pu :  1,    //     21
    reg_pad_tpi_data4_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data3_cam__ds0:  1,    //     24
    reg_pad_tpi_data3_cam__ds1:  1,    //     25
    reg_pad_tpi_data3_cam__ds2:  1,    //     26
    reg_pad_tpi_data3_cam__ds3:  1,    //     27
    reg_pad_tpi_data3_cam__pd :  1,    //     28
    reg_pad_tpi_data3_cam__pu :  1,    //     29
    reg_pad_tpi_data3_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_clk_cam__ds0  :  1,    //      0
    reg_pad_tpo_clk_cam__ds1  :  1,    //      1
    reg_pad_tpo_clk_cam__ds2  :  1,    //      2
    reg_pad_tpo_clk_cam__ds3  :  1,    //      3
    reg_pad_tpo_clk_cam__pd   :  1,    //      4
    reg_pad_tpo_clk_cam__pu   :  1,    //      5
    reg_pad_tpo_clk_cam__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_val_cam__ds0  :  1,    //      8
    reg_pad_tpi_val_cam__ds1  :  1,    //      9
    reg_pad_tpi_val_cam__ds2  :  1,    //     10
    reg_pad_tpi_val_cam__ds3  :  1,    //     11
    reg_pad_tpi_val_cam__pd   :  1,    //     12
    reg_pad_tpi_val_cam__pu   :  1,    //     13
    reg_pad_tpi_val_cam__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_sop_cam__ds0  :  1,    //     16
    reg_pad_tpi_sop_cam__ds1  :  1,    //     17
    reg_pad_tpi_sop_cam__ds2  :  1,    //     18
    reg_pad_tpi_sop_cam__ds3  :  1,    //     19
    reg_pad_tpi_sop_cam__pd   :  1,    //     20
    reg_pad_tpi_sop_cam__pu   :  1,    //     21
    reg_pad_tpi_sop_cam__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data7_cam__ds0:  1,    //     24
    reg_pad_tpi_data7_cam__ds1:  1,    //     25
    reg_pad_tpi_data7_cam__ds2:  1,    //     26
    reg_pad_tpi_data7_cam__ds3:  1,    //     27
    reg_pad_tpi_data7_cam__pd :  1,    //     28
    reg_pad_tpi_data7_cam__pu :  1,    //     29
    reg_pad_tpi_data7_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data3_cam__ds0:  1,    //      0
    reg_pad_tpo_data3_cam__ds1:  1,    //      1
    reg_pad_tpo_data3_cam__ds2:  1,    //      2
    reg_pad_tpo_data3_cam__ds3:  1,    //      3
    reg_pad_tpo_data3_cam__pd :  1,    //      4
    reg_pad_tpo_data3_cam__pu :  1,    //      5
    reg_pad_tpo_data3_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data2_cam__ds0:  1,    //      8
    reg_pad_tpo_data2_cam__ds1:  1,    //      9
    reg_pad_tpo_data2_cam__ds2:  1,    //     10
    reg_pad_tpo_data2_cam__ds3:  1,    //     11
    reg_pad_tpo_data2_cam__pd :  1,    //     12
    reg_pad_tpo_data2_cam__pu :  1,    //     13
    reg_pad_tpo_data2_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data1_cam__ds0:  1,    //     16
    reg_pad_tpo_data1_cam__ds1:  1,    //     17
    reg_pad_tpo_data1_cam__ds2:  1,    //     18
    reg_pad_tpo_data1_cam__ds3:  1,    //     19
    reg_pad_tpo_data1_cam__pd :  1,    //     20
    reg_pad_tpo_data1_cam__pu :  1,    //     21
    reg_pad_tpo_data1_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data0_cam__ds0:  1,    //     24
    reg_pad_tpo_data0_cam__ds1:  1,    //     25
    reg_pad_tpo_data0_cam__ds2:  1,    //     26
    reg_pad_tpo_data0_cam__ds3:  1,    //     27
    reg_pad_tpo_data0_cam__pd :  1,    //     28
    reg_pad_tpo_data0_cam__pu :  1,    //     29
    reg_pad_tpo_data0_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data7_cam__ds0:  1,    //      0
    reg_pad_tpo_data7_cam__ds1:  1,    //      1
    reg_pad_tpo_data7_cam__ds2:  1,    //      2
    reg_pad_tpo_data7_cam__ds3:  1,    //      3
    reg_pad_tpo_data7_cam__pd :  1,    //      4
    reg_pad_tpo_data7_cam__pu :  1,    //      5
    reg_pad_tpo_data7_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data6_cam__ds0:  1,    //      8
    reg_pad_tpo_data6_cam__ds1:  1,    //      9
    reg_pad_tpo_data6_cam__ds2:  1,    //     10
    reg_pad_tpo_data6_cam__ds3:  1,    //     11
    reg_pad_tpo_data6_cam__pd :  1,    //     12
    reg_pad_tpo_data6_cam__pu :  1,    //     13
    reg_pad_tpo_data6_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data5_cam__ds0:  1,    //     16
    reg_pad_tpo_data5_cam__ds1:  1,    //     17
    reg_pad_tpo_data5_cam__ds2:  1,    //     18
    reg_pad_tpo_data5_cam__ds3:  1,    //     19
    reg_pad_tpo_data5_cam__pd :  1,    //     20
    reg_pad_tpo_data5_cam__pu :  1,    //     21
    reg_pad_tpo_data5_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data4_cam__ds0:  1,    //     24
    reg_pad_tpo_data4_cam__ds1:  1,    //     25
    reg_pad_tpo_data4_cam__ds2:  1,    //     26
    reg_pad_tpo_data4_cam__ds3:  1,    //     27
    reg_pad_tpo_data4_cam__pd :  1,    //     28
    reg_pad_tpo_data4_cam__pu :  1,    //     29
    reg_pad_tpo_data4_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data1__ds0     :  1,    //      0
    reg_pad_eb_data1__ds1     :  1,    //      1
    reg_pad_eb_data1__ds2     :  1,    //      2
    reg_pad_eb_data1__ds3     :  1,    //      3
    reg_pad_eb_data1__pd      :  1,    //      4
    reg_pad_eb_data1__pu      :  1,    //      5
    reg_pad_eb_data1__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data0__ds0     :  1,    //      8
    reg_pad_eb_data0__ds1     :  1,    //      9
    reg_pad_eb_data0__ds2     :  1,    //     10
    reg_pad_eb_data0__ds3     :  1,    //     11
    reg_pad_eb_data0__pd      :  1,    //     12
    reg_pad_eb_data0__pu      :  1,    //     13
    reg_pad_eb_data0__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_val_cam__ds0  :  1,    //     16
    reg_pad_tpo_val_cam__ds1  :  1,    //     17
    reg_pad_tpo_val_cam__ds2  :  1,    //     18
    reg_pad_tpo_val_cam__ds3  :  1,    //     19
    reg_pad_tpo_val_cam__pd   :  1,    //     20
    reg_pad_tpo_val_cam__pu   :  1,    //     21
    reg_pad_tpo_val_cam__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_sop_cam__ds0  :  1,    //     24
    reg_pad_tpo_sop_cam__ds1  :  1,    //     25
    reg_pad_tpo_sop_cam__ds2  :  1,    //     26
    reg_pad_tpo_sop_cam__ds3  :  1,    //     27
    reg_pad_tpo_sop_cam__pd   :  1,    //     28
    reg_pad_tpo_sop_cam__pu   :  1,    //     29
    reg_pad_tpo_sop_cam__st   :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD005_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data5__ds0     :  1,    //      0
    reg_pad_eb_data5__ds1     :  1,    //      1
    reg_pad_eb_data5__ds2     :  1,    //      2
    reg_pad_eb_data5__ds3     :  1,    //      3
    reg_pad_eb_data5__pd      :  1,    //      4
    reg_pad_eb_data5__pu      :  1,    //      5
    reg_pad_eb_data5__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data4__ds0     :  1,    //      8
    reg_pad_eb_data4__ds1     :  1,    //      9
    reg_pad_eb_data4__ds2     :  1,    //     10
    reg_pad_eb_data4__ds3     :  1,    //     11
    reg_pad_eb_data4__pd      :  1,    //     12
    reg_pad_eb_data4__pu      :  1,    //     13
    reg_pad_eb_data4__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data3__ds0     :  1,    //     16
    reg_pad_eb_data3__ds1     :  1,    //     17
    reg_pad_eb_data3__ds2     :  1,    //     18
    reg_pad_eb_data3__ds3     :  1,    //     19
    reg_pad_eb_data3__pd      :  1,    //     20
    reg_pad_eb_data3__pu      :  1,    //     21
    reg_pad_eb_data3__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data2__ds0     :  1,    //     24
    reg_pad_eb_data2__ds1     :  1,    //     25
    reg_pad_eb_data2__ds2     :  1,    //     26
    reg_pad_eb_data2__ds3     :  1,    //     27
    reg_pad_eb_data2__pd      :  1,    //     28
    reg_pad_eb_data2__pu      :  1,    //     29
    reg_pad_eb_data2__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD006_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr1__ds0     :  1,    //      0
    reg_pad_eb_addr1__ds1     :  1,    //      1
    reg_pad_eb_addr1__ds2     :  1,    //      2
    reg_pad_eb_addr1__ds3     :  1,    //      3
    reg_pad_eb_addr1__pd      :  1,    //      4
    reg_pad_eb_addr1__pu      :  1,    //      5
    reg_pad_eb_addr1__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr0__ds0     :  1,    //      8
    reg_pad_eb_addr0__ds1     :  1,    //      9
    reg_pad_eb_addr0__ds2     :  1,    //     10
    reg_pad_eb_addr0__ds3     :  1,    //     11
    reg_pad_eb_addr0__pd      :  1,    //     12
    reg_pad_eb_addr0__pu      :  1,    //     13
    reg_pad_eb_addr0__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data7__ds0     :  1,    //     16
    reg_pad_eb_data7__ds1     :  1,    //     17
    reg_pad_eb_data7__ds2     :  1,    //     18
    reg_pad_eb_data7__ds3     :  1,    //     19
    reg_pad_eb_data7__pd      :  1,    //     20
    reg_pad_eb_data7__pu      :  1,    //     21
    reg_pad_eb_data7__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data6__ds0     :  1,    //     24
    reg_pad_eb_data6__ds1     :  1,    //     25
    reg_pad_eb_data6__ds2     :  1,    //     26
    reg_pad_eb_data6__ds3     :  1,    //     27
    reg_pad_eb_data6__pd      :  1,    //     28
    reg_pad_eb_data6__pu      :  1,    //     29
    reg_pad_eb_data6__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD007_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr5__ds0     :  1,    //      0
    reg_pad_eb_addr5__ds1     :  1,    //      1
    reg_pad_eb_addr5__ds2     :  1,    //      2
    reg_pad_eb_addr5__ds3     :  1,    //      3
    reg_pad_eb_addr5__pd      :  1,    //      4
    reg_pad_eb_addr5__pu      :  1,    //      5
    reg_pad_eb_addr5__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr4__ds0     :  1,    //      8
    reg_pad_eb_addr4__ds1     :  1,    //      9
    reg_pad_eb_addr4__ds2     :  1,    //     10
    reg_pad_eb_addr4__ds3     :  1,    //     11
    reg_pad_eb_addr4__pd      :  1,    //     12
    reg_pad_eb_addr4__pu      :  1,    //     13
    reg_pad_eb_addr4__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr3__ds0     :  1,    //     16
    reg_pad_eb_addr3__ds1     :  1,    //     17
    reg_pad_eb_addr3__ds2     :  1,    //     18
    reg_pad_eb_addr3__ds3     :  1,    //     19
    reg_pad_eb_addr3__pd      :  1,    //     20
    reg_pad_eb_addr3__pu      :  1,    //     21
    reg_pad_eb_addr3__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr2__ds0     :  1,    //     24
    reg_pad_eb_addr2__ds1     :  1,    //     25
    reg_pad_eb_addr2__ds2     :  1,    //     26
    reg_pad_eb_addr2__ds3     :  1,    //     27
    reg_pad_eb_addr2__pd      :  1,    //     28
    reg_pad_eb_addr2__pu      :  1,    //     29
    reg_pad_eb_addr2__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD008_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr9__ds0     :  1,    //      0
    reg_pad_eb_addr9__ds1     :  1,    //      1
    reg_pad_eb_addr9__ds2     :  1,    //      2
    reg_pad_eb_addr9__ds3     :  1,    //      3
    reg_pad_eb_addr9__pd      :  1,    //      4
    reg_pad_eb_addr9__pu      :  1,    //      5
    reg_pad_eb_addr9__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr8__ds0     :  1,    //      8
    reg_pad_eb_addr8__ds1     :  1,    //      9
    reg_pad_eb_addr8__ds2     :  1,    //     10
    reg_pad_eb_addr8__ds3     :  1,    //     11
    reg_pad_eb_addr8__pd      :  1,    //     12
    reg_pad_eb_addr8__pu      :  1,    //     13
    reg_pad_eb_addr8__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr7__ds0     :  1,    //     16
    reg_pad_eb_addr7__ds1     :  1,    //     17
    reg_pad_eb_addr7__ds2     :  1,    //     18
    reg_pad_eb_addr7__ds3     :  1,    //     19
    reg_pad_eb_addr7__pd      :  1,    //     20
    reg_pad_eb_addr7__pu      :  1,    //     21
    reg_pad_eb_addr7__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr6__ds0     :  1,    //     24
    reg_pad_eb_addr6__ds1     :  1,    //     25
    reg_pad_eb_addr6__ds2     :  1,    //     26
    reg_pad_eb_addr6__ds3     :  1,    //     27
    reg_pad_eb_addr6__pd      :  1,    //     28
    reg_pad_eb_addr6__pu      :  1,    //     29
    reg_pad_eb_addr6__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD009_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x28    pad_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr13__ds0    :  1,    //      0
    reg_pad_eb_addr13__ds1    :  1,    //      1
    reg_pad_eb_addr13__ds2    :  1,    //      2
    reg_pad_eb_addr13__ds3    :  1,    //      3
    reg_pad_eb_addr13__pd     :  1,    //      4
    reg_pad_eb_addr13__pu     :  1,    //      5
    reg_pad_eb_addr13__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr12__ds0    :  1,    //      8
    reg_pad_eb_addr12__ds1    :  1,    //      9
    reg_pad_eb_addr12__ds2    :  1,    //     10
    reg_pad_eb_addr12__ds3    :  1,    //     11
    reg_pad_eb_addr12__pd     :  1,    //     12
    reg_pad_eb_addr12__pu     :  1,    //     13
    reg_pad_eb_addr12__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr11__ds0    :  1,    //     16
    reg_pad_eb_addr11__ds1    :  1,    //     17
    reg_pad_eb_addr11__ds2    :  1,    //     18
    reg_pad_eb_addr11__ds3    :  1,    //     19
    reg_pad_eb_addr11__pd     :  1,    //     20
    reg_pad_eb_addr11__pu     :  1,    //     21
    reg_pad_eb_addr11__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr10__ds0    :  1,    //     24
    reg_pad_eb_addr10__ds1    :  1,    //     25
    reg_pad_eb_addr10__ds2    :  1,    //     26
    reg_pad_eb_addr10__ds3    :  1,    //     27
    reg_pad_eb_addr10__pd     :  1,    //     28
    reg_pad_eb_addr10__pu     :  1,    //     29
    reg_pad_eb_addr10__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD010_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C    pad_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs1__ds0       :  1,    //      0
    reg_pad_eb_cs1__ds1       :  1,    //      1
    reg_pad_eb_cs1__ds2       :  1,    //      2
    reg_pad_eb_cs1__ds3       :  1,    //      3
    reg_pad_eb_cs1__pd        :  1,    //      4
    reg_pad_eb_cs1__pu        :  1,    //      5
    reg_pad_eb_cs1__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_cs0__ds0       :  1,    //      8
    reg_pad_eb_cs0__ds1       :  1,    //      9
    reg_pad_eb_cs0__ds2       :  1,    //     10
    reg_pad_eb_cs0__ds3       :  1,    //     11
    reg_pad_eb_cs0__pd        :  1,    //     12
    reg_pad_eb_cs0__pu        :  1,    //     13
    reg_pad_eb_cs0__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr15__ds0    :  1,    //     16
    reg_pad_eb_addr15__ds1    :  1,    //     17
    reg_pad_eb_addr15__ds2    :  1,    //     18
    reg_pad_eb_addr15__ds3    :  1,    //     19
    reg_pad_eb_addr15__pd     :  1,    //     20
    reg_pad_eb_addr15__pu     :  1,    //     21
    reg_pad_eb_addr15__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr14__ds0    :  1,    //     24
    reg_pad_eb_addr14__ds1    :  1,    //     25
    reg_pad_eb_addr14__ds2    :  1,    //     26
    reg_pad_eb_addr14__ds3    :  1,    //     27
    reg_pad_eb_addr14__pd     :  1,    //     28
    reg_pad_eb_addr14__pu     :  1,    //     29
    reg_pad_eb_addr14__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD011_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x30    pad_vd012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_we_n__ds0      :  1,    //      0
    reg_pad_eb_we_n__ds1      :  1,    //      1
    reg_pad_eb_we_n__ds2      :  1,    //      2
    reg_pad_eb_we_n__ds3      :  1,    //      3
    reg_pad_eb_we_n__pd       :  1,    //      4
    reg_pad_eb_we_n__pu       :  1,    //      5
    reg_pad_eb_we_n__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_oe_n__ds0      :  1,    //      8
    reg_pad_eb_oe_n__ds1      :  1,    //      9
    reg_pad_eb_oe_n__ds2      :  1,    //     10
    reg_pad_eb_oe_n__ds3      :  1,    //     11
    reg_pad_eb_oe_n__pd       :  1,    //     12
    reg_pad_eb_oe_n__pu       :  1,    //     13
    reg_pad_eb_oe_n__st       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_cs3__ds0       :  1,    //     16
    reg_pad_eb_cs3__ds1       :  1,    //     17
    reg_pad_eb_cs3__ds2       :  1,    //     18
    reg_pad_eb_cs3__ds3       :  1,    //     19
    reg_pad_eb_cs3__pd        :  1,    //     20
    reg_pad_eb_cs3__pu        :  1,    //     21
    reg_pad_eb_cs3__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_cs2__ds0       :  1,    //     24
    reg_pad_eb_cs2__ds1       :  1,    //     25
    reg_pad_eb_cs2__ds2       :  1,    //     26
    reg_pad_eb_cs2__ds3       :  1,    //     27
    reg_pad_eb_cs2__pd        :  1,    //     28
    reg_pad_eb_cs2__pu        :  1,    //     29
    reg_pad_eb_cs2__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD012_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x34    pad_vd013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ce1_n__ds0    :  1,    //      0
    reg_pad_cam_ce1_n__ds1    :  1,    //      1
    reg_pad_cam_ce1_n__ds2    :  1,    //      2
    reg_pad_cam_ce1_n__ds3    :  1,    //      3
    reg_pad_cam_ce1_n__pd     :  1,    //      4
    reg_pad_cam_ce1_n__pu     :  1,    //      5
    reg_pad_cam_ce1_n__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_be_n1__ds0     :  1,    //      8
    reg_pad_eb_be_n1__ds1     :  1,    //      9
    reg_pad_eb_be_n1__ds2     :  1,    //     10
    reg_pad_eb_be_n1__ds3     :  1,    //     11
    reg_pad_eb_be_n1__pd      :  1,    //     12
    reg_pad_eb_be_n1__pu      :  1,    //     13
    reg_pad_eb_be_n1__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_be_n0__ds0     :  1,    //     16
    reg_pad_eb_be_n0__ds1     :  1,    //     17
    reg_pad_eb_be_n0__ds2     :  1,    //     18
    reg_pad_eb_be_n0__ds3     :  1,    //     19
    reg_pad_eb_be_n0__pd      :  1,    //     20
    reg_pad_eb_be_n0__pu      :  1,    //     21
    reg_pad_eb_be_n0__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_wait__ds0      :  1,    //     24
    reg_pad_eb_wait__ds1      :  1,    //     25
    reg_pad_eb_wait__ds2      :  1,    //     26
    reg_pad_eb_wait__ds3      :  1,    //     27
    reg_pad_eb_wait__pd       :  1,    //     28
    reg_pad_eb_wait__pu       :  1,    //     29
    reg_pad_eb_wait__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD013_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x38    pad_vd014 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ireq_n__ds0   :  1,    //      0
    reg_pad_cam_ireq_n__ds1   :  1,    //      1
    reg_pad_cam_ireq_n__ds2   :  1,    //      2
    reg_pad_cam_ireq_n__ds3   :  1,    //      3
    reg_pad_cam_ireq_n__pd    :  1,    //      4
    reg_pad_cam_ireq_n__pu    :  1,    //      5
    reg_pad_cam_ireq_n__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_cd2_n__ds0    :  1,    //      8
    reg_pad_cam_cd2_n__ds1    :  1,    //      9
    reg_pad_cam_cd2_n__ds2    :  1,    //     10
    reg_pad_cam_cd2_n__ds3    :  1,    //     11
    reg_pad_cam_cd2_n__pd     :  1,    //     12
    reg_pad_cam_cd2_n__pu     :  1,    //     13
    reg_pad_cam_cd2_n__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_cam_cd1_n__ds0    :  1,    //     16
    reg_pad_cam_cd1_n__ds1    :  1,    //     17
    reg_pad_cam_cd1_n__ds2    :  1,    //     18
    reg_pad_cam_cd1_n__ds3    :  1,    //     19
    reg_pad_cam_cd1_n__pd     :  1,    //     20
    reg_pad_cam_cd1_n__pu     :  1,    //     21
    reg_pad_cam_cd1_n__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_cam_ce2_n__ds0    :  1,    //     24
    reg_pad_cam_ce2_n__ds1    :  1,    //     25
    reg_pad_cam_ce2_n__ds2    :  1,    //     26
    reg_pad_cam_ce2_n__ds3    :  1,    //     27
    reg_pad_cam_ce2_n__pd     :  1,    //     28
    reg_pad_cam_ce2_n__pu     :  1,    //     29
    reg_pad_cam_ce2_n__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD014_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C    pad_vd015 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reset__ds0    :  1,    //      0
    reg_pad_cam_reset__ds1    :  1,    //      1
    reg_pad_cam_reset__ds2    :  1,    //      2
    reg_pad_cam_reset__ds3    :  1,    //      3
    reg_pad_cam_reset__pd     :  1,    //      4
    reg_pad_cam_reset__pu     :  1,    //      5
    reg_pad_cam_reset__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_vccen_n__ds0  :  1,    //      8
    reg_pad_cam_vccen_n__ds1  :  1,    //      9
    reg_pad_cam_vccen_n__ds2  :  1,    //     10
    reg_pad_cam_vccen_n__ds3  :  1,    //     11
    reg_pad_cam_vccen_n__pd   :  1,    //     12
    reg_pad_cam_vccen_n__pu   :  1,    //     13
    reg_pad_cam_vccen_n__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_cam_wait_n__ds0   :  1,    //     16
    reg_pad_cam_wait_n__ds1   :  1,    //     17
    reg_pad_cam_wait_n__ds2   :  1,    //     18
    reg_pad_cam_wait_n__ds3   :  1,    //     19
    reg_pad_cam_wait_n__pd    :  1,    //     20
    reg_pad_cam_wait_n__pu    :  1,    //     21
    reg_pad_cam_wait_n__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_cam_reg_n__ds0    :  1,    //     24
    reg_pad_cam_reg_n__ds1    :  1,    //     25
    reg_pad_cam_reg_n__ds2    :  1,    //     26
    reg_pad_cam_reg_n__ds3    :  1,    //     27
    reg_pad_cam_reg_n__pd     :  1,    //     28
    reg_pad_cam_reg_n__pu     :  1,    //     29
    reg_pad_cam_reg_n__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_VD0_PAD_VD015_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_vd064 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data6_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_data5_cam_mux_sel: 4,    //  7:4
    reg_pad_tpi_data4_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data3_cam_mux_sel: 4,    //  15:12
    reg_pad_tpi_data2_cam_mux_sel: 4,    //  19:16
    reg_pad_tpi_data1_cam_mux_sel: 4,    //  23:20
    reg_pad_tpi_data0_cam_mux_sel: 4,    //  27:24
    reg_pad_tpi_clk_cam_mux_sel: 4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD064_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_vd065 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data3_cam_mux_sel: 4,    //  3:0
    reg_pad_tpo_data2_cam_mux_sel: 4,    //  7:4
    reg_pad_tpo_data1_cam_mux_sel: 4,    //  11:8
    reg_pad_tpo_data0_cam_mux_sel: 4,    //  15:12
    reg_pad_tpo_clk_cam_mux_sel: 4,    //  19:16
    reg_pad_tpi_val_cam_mux_sel: 4,    //  23:20
    reg_pad_tpi_sop_cam_mux_sel: 4,    //  27:24
    reg_pad_tpi_data7_cam_mux_sel: 4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD065_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_vd066 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data1_mux_sel  :  4,    //   3: 0
    reg_pad_eb_data0_mux_sel  :  4,    //   7: 4
    reg_pad_tpo_val_cam_mux_sel: 4,    //  11: 8
    reg_pad_tpo_sop_cam_mux_sel: 4,    //  15:12
    reg_pad_tpo_data7_cam_mux_sel: 4,    //  19:16
    reg_pad_tpo_data6_cam_mux_sel: 4,    //  23:20
    reg_pad_tpo_data5_cam_mux_sel: 4,    //  27:24
    reg_pad_tpo_data4_cam_mux_sel: 4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD066_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_vd067 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr1_mux_sel  :  4,    //   3: 0
    reg_pad_eb_addr0_mux_sel  :  4,    //   7: 4
    reg_pad_eb_data7_mux_sel  :  4,    //  11: 8
    reg_pad_eb_data6_mux_sel  :  4,    //  15:12
    reg_pad_eb_data5_mux_sel  :  4,    //  19:16
    reg_pad_eb_data4_mux_sel  :  4,    //  23:20
    reg_pad_eb_data3_mux_sel  :  4,    //  27:24
    reg_pad_eb_data2_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD067_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_vd068 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr9_mux_sel  :  4,    //   3: 0
    reg_pad_eb_addr8_mux_sel  :  4,    //   7: 4
    reg_pad_eb_addr7_mux_sel  :  4,    //  11: 8
    reg_pad_eb_addr6_mux_sel  :  4,    //  15:12
    reg_pad_eb_addr5_mux_sel  :  4,    //  19:16
    reg_pad_eb_addr4_mux_sel  :  4,    //  23:20
    reg_pad_eb_addr3_mux_sel  :  4,    //  27:24
    reg_pad_eb_addr2_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD068_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x114    pad_vd069 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs1_mux_sel    :  4,    //   3: 0
    reg_pad_eb_cs0_mux_sel    :  4,    //   7: 4
    reg_pad_eb_addr15_mux_sel :  4,    //  11: 8
    reg_pad_eb_addr14_mux_sel :  4,    //  15:12
    reg_pad_eb_addr13_mux_sel :  4,    //  19:16
    reg_pad_eb_addr12_mux_sel :  4,    //  23:20
    reg_pad_eb_addr11_mux_sel :  4,    //  27:24
    reg_pad_eb_addr10_mux_sel :  4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD069_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x118    pad_vd070 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ce1_n_mux_sel :  4,    //   3: 0
    reg_pad_eb_be_n1_mux_sel  :  4,    //   7: 4
    reg_pad_eb_be_n0_mux_sel  :  4,    //  11: 8
    reg_pad_eb_wait_mux_sel   :  4,    //  15:12
    reg_pad_eb_we_n_mux_sel   :  4,    //  19:16
    reg_pad_eb_oe_n_mux_sel   :  4,    //  23:20
    reg_pad_eb_cs3_mux_sel    :  4,    //  27:24
    reg_pad_eb_cs2_mux_sel    :  4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD070_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x11C    pad_vd071 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reset_mux_sel :  4,    //   3: 0
    reg_pad_cam_vccen_n_mux_sel: 4,    //   7: 4
    reg_pad_cam_wait_n_mux_sel:  4,    //  11: 8
    reg_pad_cam_reg_n_mux_sel :  4,    //  15:12
    reg_pad_cam_ireq_n_mux_sel:  4,    //  19:16
    reg_pad_cam_cd2_n_mux_sel :  4,    //  23:20
    reg_pad_cam_cd1_n_mux_sel :  4,    //  27:24
    reg_pad_cam_ce2_n_mux_sel :  4;    //  31:28
}IOMUX_CTRL_VD0_PAD_VD071_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_VD0_PAD_VD000_M23A0_T     pad_vd000  ;             // 0x0
    IOMUX_CTRL_VD0_PAD_VD001_M23A0_T     pad_vd001  ;             // 0x4
    IOMUX_CTRL_VD0_PAD_VD002_M23A0_T     pad_vd002  ;             // 0x8
    IOMUX_CTRL_VD0_PAD_VD003_M23A0_T     pad_vd003  ;             // 0xC
    IOMUX_CTRL_VD0_PAD_VD004_M23A0_T     pad_vd004  ;             // 0x10
    IOMUX_CTRL_VD0_PAD_VD005_M23A0_T     pad_vd005  ;             // 0x14
    IOMUX_CTRL_VD0_PAD_VD006_M23A0_T     pad_vd006  ;             // 0x18
    IOMUX_CTRL_VD0_PAD_VD007_M23A0_T     pad_vd007  ;             // 0x1C
    IOMUX_CTRL_VD0_PAD_VD008_M23A0_T     pad_vd008  ;             // 0x20
    IOMUX_CTRL_VD0_PAD_VD009_M23A0_T     pad_vd009  ;             // 0x24
    IOMUX_CTRL_VD0_PAD_VD010_M23A0_T     pad_vd010  ;             // 0x28
    IOMUX_CTRL_VD0_PAD_VD011_M23A0_T     pad_vd011  ;             // 0x2C
    IOMUX_CTRL_VD0_PAD_VD012_M23A0_T     pad_vd012  ;             // 0x30
    IOMUX_CTRL_VD0_PAD_VD013_M23A0_T     pad_vd013  ;             // 0x34
    IOMUX_CTRL_VD0_PAD_VD014_M23A0_T     pad_vd014  ;             // 0x38
    IOMUX_CTRL_VD0_PAD_VD015_M23A0_T     pad_vd015  ;             // 0x3C
    UINT32                             _rsvd_00[48];            // 0x40 ~ 0xFC
    IOMUX_CTRL_VD0_PAD_VD064_M23A0_T     pad_vd064  ;             // 0x100
    IOMUX_CTRL_VD0_PAD_VD065_M23A0_T     pad_vd065  ;             // 0x104
    IOMUX_CTRL_VD0_PAD_VD066_M23A0_T     pad_vd066  ;             // 0x108
    IOMUX_CTRL_VD0_PAD_VD067_M23A0_T     pad_vd067  ;             // 0x10C
    IOMUX_CTRL_VD0_PAD_VD068_M23A0_T     pad_vd068  ;             // 0x110
    IOMUX_CTRL_VD0_PAD_VD069_M23A0_T     pad_vd069  ;             // 0x114
    IOMUX_CTRL_VD0_PAD_VD070_M23A0_T     pad_vd070  ;             // 0x118
    IOMUX_CTRL_VD0_PAD_VD071_M23A0_T     pad_vd071  ;             // 0x11C
}IOMUX_CTRL_VD0_REG_M23A0_T;
/* 24 regs */

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

#define IOMUX_CTRL_VD0_PAD_VD000_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define IOMUX_CTRL_VD0_PAD_VD001_M23A0_T_OFF                  (BASEADDRESS+0x0004)
#define IOMUX_CTRL_VD0_PAD_VD002_M23A0_T_OFF                  (BASEADDRESS+0x0008)
#define IOMUX_CTRL_VD0_PAD_VD003_M23A0_T_OFF                  (BASEADDRESS+0x000C)
#define IOMUX_CTRL_VD0_PAD_VD004_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define IOMUX_CTRL_VD0_PAD_VD005_M23A0_T_OFF                  (BASEADDRESS+0x0014)
#define IOMUX_CTRL_VD0_PAD_VD006_M23A0_T_OFF                  (BASEADDRESS+0x0018)
#define IOMUX_CTRL_VD0_PAD_VD007_M23A0_T_OFF                  (BASEADDRESS+0x001C)
#define IOMUX_CTRL_VD0_PAD_VD008_M23A0_T_OFF                  (BASEADDRESS+0x0020)
#define IOMUX_CTRL_VD0_PAD_VD009_M23A0_T_OFF                  (BASEADDRESS+0x0024)
#define IOMUX_CTRL_VD0_PAD_VD010_M23A0_T_OFF                  (BASEADDRESS+0x0028)
#define IOMUX_CTRL_VD0_PAD_VD011_M23A0_T_OFF                  (BASEADDRESS+0x002C)
#define IOMUX_CTRL_VD0_PAD_VD012_M23A0_T_OFF                  (BASEADDRESS+0x0030)
#define IOMUX_CTRL_VD0_PAD_VD013_M23A0_T_OFF                  (BASEADDRESS+0x0034)
#define IOMUX_CTRL_VD0_PAD_VD014_M23A0_T_OFF                  (BASEADDRESS+0x0038)
#define IOMUX_CTRL_VD0_PAD_VD015_M23A0_T_OFF                  (BASEADDRESS+0x003C)
#define IOMUX_CTRL_VD0_PAD_VD064_M23A0_T_OFF                  (BASEADDRESS+0x0100)
#define IOMUX_CTRL_VD0_PAD_VD065_M23A0_T_OFF                  (BASEADDRESS+0x0104)
#define IOMUX_CTRL_VD0_PAD_VD066_M23A0_T_OFF                  (BASEADDRESS+0x0108)
#define IOMUX_CTRL_VD0_PAD_VD067_M23A0_T_OFF                  (BASEADDRESS+0x010C)
#define IOMUX_CTRL_VD0_PAD_VD068_M23A0_T_OFF                  (BASEADDRESS+0x0110)
#define IOMUX_CTRL_VD0_PAD_VD069_M23A0_T_OFF                  (BASEADDRESS+0x0114)
#define IOMUX_CTRL_VD0_PAD_VD070_M23A0_T_OFF                  (BASEADDRESS+0x0118)
#define IOMUX_CTRL_VD0_PAD_VD071_M23A0_T_OFF                  (BASEADDRESS+0x011C)

/*-----------------------------------------------------------------------------------------
    0x0    pad_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data2_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data2_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data2_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data2_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data2_cam__pd: 1;    //  4
    UINT32 reg_pad_tpi_data2_cam__pu: 1;    //  5
    UINT32 reg_pad_tpi_data2_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data1_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data1_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data1_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data1_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data1_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_data1_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_data1_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data0_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data0_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data0_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data0_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data0_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_data0_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_data0_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_clk_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpi_clk_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpi_clk_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpi_clk_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpi_clk_cam__pd: 1;    //  28
    UINT32 reg_pad_tpi_clk_cam__pu: 1;    //  29
    UINT32 reg_pad_tpi_clk_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data6_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data6_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data6_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data6_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data6_cam__pd: 1;    //  4
    UINT32 reg_pad_tpi_data6_cam__pu: 1;    //  5
    UINT32 reg_pad_tpi_data6_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data5_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data5_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data5_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data5_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data5_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_data5_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_data5_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data4_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data4_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data4_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data4_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data4_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_data4_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_data4_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data3_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data3_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data3_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data3_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data3_cam__pd: 1;    //  28
    UINT32 reg_pad_tpi_data3_cam__pu: 1;    //  29
    UINT32 reg_pad_tpi_data3_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_clk_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpo_clk_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpo_clk_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpo_clk_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpo_clk_cam__pd: 1;    //   4
    UINT32 reg_pad_tpo_clk_cam__pu: 1;    //   5
    UINT32 reg_pad_tpo_clk_cam__st: 1;    //   6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_val_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_val_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_val_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_val_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_val_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_val_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_val_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_sop_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_sop_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_sop_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_sop_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_sop_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_sop_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_sop_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data7_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data7_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data7_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data7_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data7_cam__pd: 1;    //  28
    UINT32 reg_pad_tpi_data7_cam__pu: 1;    //  29
    UINT32 reg_pad_tpi_data7_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data3_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpo_data3_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpo_data3_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpo_data3_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpo_data3_cam__pd: 1;    //  4
    UINT32 reg_pad_tpo_data3_cam__pu: 1;    //  5
    UINT32 reg_pad_tpo_data3_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpo_data2_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpo_data2_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpo_data2_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpo_data2_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpo_data2_cam__pd: 1;    //  12
    UINT32 reg_pad_tpo_data2_cam__pu: 1;    //  13
    UINT32 reg_pad_tpo_data2_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_data1_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_data1_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_data1_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_data1_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_data1_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_data1_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_data1_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_data0_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_data0_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_data0_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_data0_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_data0_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_data0_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_data0_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10    pad_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data7_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpo_data7_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpo_data7_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpo_data7_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpo_data7_cam__pd: 1;    //  4
    UINT32 reg_pad_tpo_data7_cam__pu: 1;    //  5
    UINT32 reg_pad_tpo_data7_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpo_data6_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpo_data6_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpo_data6_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpo_data6_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpo_data6_cam__pd: 1;    //  12
    UINT32 reg_pad_tpo_data6_cam__pu: 1;    //  13
    UINT32 reg_pad_tpo_data6_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_data5_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_data5_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_data5_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_data5_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_data5_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_data5_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_data5_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_data4_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_data4_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_data4_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_data4_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_data4_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_data4_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_data4_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x14    pad_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data1__ds0: 1;    //     0
    UINT32 reg_pad_eb_data1__ds1: 1;    //     1
    UINT32 reg_pad_eb_data1__ds2: 1;    //     2
    UINT32 reg_pad_eb_data1__ds3: 1;    //     3
    UINT32 reg_pad_eb_data1__pd: 1;    //      4
    UINT32 reg_pad_eb_data1__pu: 1;    //      5
    UINT32 reg_pad_eb_data1__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_data0__ds0: 1;    //     8
    UINT32 reg_pad_eb_data0__ds1: 1;    //     9
    UINT32 reg_pad_eb_data0__ds2: 1;    //    10
    UINT32 reg_pad_eb_data0__ds3: 1;    //    11
    UINT32 reg_pad_eb_data0__pd: 1;    //     12
    UINT32 reg_pad_eb_data0__pu: 1;    //     13
    UINT32 reg_pad_eb_data0__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_val_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_val_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_val_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_val_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_val_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_val_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_val_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_sop_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_sop_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_sop_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_sop_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_sop_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_sop_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_sop_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD005_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x18    pad_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data5__ds0: 1;    //     0
    UINT32 reg_pad_eb_data5__ds1: 1;    //     1
    UINT32 reg_pad_eb_data5__ds2: 1;    //     2
    UINT32 reg_pad_eb_data5__ds3: 1;    //     3
    UINT32 reg_pad_eb_data5__pd: 1;    //      4
    UINT32 reg_pad_eb_data5__pu: 1;    //      5
    UINT32 reg_pad_eb_data5__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_data4__ds0: 1;    //     8
    UINT32 reg_pad_eb_data4__ds1: 1;    //     9
    UINT32 reg_pad_eb_data4__ds2: 1;    //    10
    UINT32 reg_pad_eb_data4__ds3: 1;    //    11
    UINT32 reg_pad_eb_data4__pd: 1;    //     12
    UINT32 reg_pad_eb_data4__pu: 1;    //     13
    UINT32 reg_pad_eb_data4__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_data3__ds0: 1;    //    16
    UINT32 reg_pad_eb_data3__ds1: 1;    //    17
    UINT32 reg_pad_eb_data3__ds2: 1;    //    18
    UINT32 reg_pad_eb_data3__ds3: 1;    //    19
    UINT32 reg_pad_eb_data3__pd: 1;    //     20
    UINT32 reg_pad_eb_data3__pu: 1;    //     21
    UINT32 reg_pad_eb_data3__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_data2__ds0: 1;    //    24
    UINT32 reg_pad_eb_data2__ds1: 1;    //    25
    UINT32 reg_pad_eb_data2__ds2: 1;    //    26
    UINT32 reg_pad_eb_data2__ds3: 1;    //    27
    UINT32 reg_pad_eb_data2__pd: 1;    //     28
    UINT32 reg_pad_eb_data2__pu: 1;    //     29
    UINT32 reg_pad_eb_data2__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD006_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x1C    pad_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr1__ds0: 1;    //     0
    UINT32 reg_pad_eb_addr1__ds1: 1;    //     1
    UINT32 reg_pad_eb_addr1__ds2: 1;    //     2
    UINT32 reg_pad_eb_addr1__ds3: 1;    //     3
    UINT32 reg_pad_eb_addr1__pd: 1;    //      4
    UINT32 reg_pad_eb_addr1__pu: 1;    //      5
    UINT32 reg_pad_eb_addr1__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr0__ds0: 1;    //     8
    UINT32 reg_pad_eb_addr0__ds1: 1;    //     9
    UINT32 reg_pad_eb_addr0__ds2: 1;    //    10
    UINT32 reg_pad_eb_addr0__ds3: 1;    //    11
    UINT32 reg_pad_eb_addr0__pd: 1;    //     12
    UINT32 reg_pad_eb_addr0__pu: 1;    //     13
    UINT32 reg_pad_eb_addr0__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_data7__ds0: 1;    //    16
    UINT32 reg_pad_eb_data7__ds1: 1;    //    17
    UINT32 reg_pad_eb_data7__ds2: 1;    //    18
    UINT32 reg_pad_eb_data7__ds3: 1;    //    19
    UINT32 reg_pad_eb_data7__pd: 1;    //     20
    UINT32 reg_pad_eb_data7__pu: 1;    //     21
    UINT32 reg_pad_eb_data7__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_data6__ds0: 1;    //    24
    UINT32 reg_pad_eb_data6__ds1: 1;    //    25
    UINT32 reg_pad_eb_data6__ds2: 1;    //    26
    UINT32 reg_pad_eb_data6__ds3: 1;    //    27
    UINT32 reg_pad_eb_data6__pd: 1;    //     28
    UINT32 reg_pad_eb_data6__pu: 1;    //     29
    UINT32 reg_pad_eb_data6__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD007_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x20    pad_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr5__ds0: 1;    //     0
    UINT32 reg_pad_eb_addr5__ds1: 1;    //     1
    UINT32 reg_pad_eb_addr5__ds2: 1;    //     2
    UINT32 reg_pad_eb_addr5__ds3: 1;    //     3
    UINT32 reg_pad_eb_addr5__pd: 1;    //      4
    UINT32 reg_pad_eb_addr5__pu: 1;    //      5
    UINT32 reg_pad_eb_addr5__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr4__ds0: 1;    //     8
    UINT32 reg_pad_eb_addr4__ds1: 1;    //     9
    UINT32 reg_pad_eb_addr4__ds2: 1;    //    10
    UINT32 reg_pad_eb_addr4__ds3: 1;    //    11
    UINT32 reg_pad_eb_addr4__pd: 1;    //     12
    UINT32 reg_pad_eb_addr4__pu: 1;    //     13
    UINT32 reg_pad_eb_addr4__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr3__ds0: 1;    //    16
    UINT32 reg_pad_eb_addr3__ds1: 1;    //    17
    UINT32 reg_pad_eb_addr3__ds2: 1;    //    18
    UINT32 reg_pad_eb_addr3__ds3: 1;    //    19
    UINT32 reg_pad_eb_addr3__pd: 1;    //     20
    UINT32 reg_pad_eb_addr3__pu: 1;    //     21
    UINT32 reg_pad_eb_addr3__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr2__ds0: 1;    //    24
    UINT32 reg_pad_eb_addr2__ds1: 1;    //    25
    UINT32 reg_pad_eb_addr2__ds2: 1;    //    26
    UINT32 reg_pad_eb_addr2__ds3: 1;    //    27
    UINT32 reg_pad_eb_addr2__pd: 1;    //     28
    UINT32 reg_pad_eb_addr2__pu: 1;    //     29
    UINT32 reg_pad_eb_addr2__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD008_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x24    pad_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr9__ds0: 1;    //     0
    UINT32 reg_pad_eb_addr9__ds1: 1;    //     1
    UINT32 reg_pad_eb_addr9__ds2: 1;    //     2
    UINT32 reg_pad_eb_addr9__ds3: 1;    //     3
    UINT32 reg_pad_eb_addr9__pd: 1;    //      4
    UINT32 reg_pad_eb_addr9__pu: 1;    //      5
    UINT32 reg_pad_eb_addr9__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr8__ds0: 1;    //     8
    UINT32 reg_pad_eb_addr8__ds1: 1;    //     9
    UINT32 reg_pad_eb_addr8__ds2: 1;    //    10
    UINT32 reg_pad_eb_addr8__ds3: 1;    //    11
    UINT32 reg_pad_eb_addr8__pd: 1;    //     12
    UINT32 reg_pad_eb_addr8__pu: 1;    //     13
    UINT32 reg_pad_eb_addr8__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr7__ds0: 1;    //    16
    UINT32 reg_pad_eb_addr7__ds1: 1;    //    17
    UINT32 reg_pad_eb_addr7__ds2: 1;    //    18
    UINT32 reg_pad_eb_addr7__ds3: 1;    //    19
    UINT32 reg_pad_eb_addr7__pd: 1;    //     20
    UINT32 reg_pad_eb_addr7__pu: 1;    //     21
    UINT32 reg_pad_eb_addr7__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr6__ds0: 1;    //    24
    UINT32 reg_pad_eb_addr6__ds1: 1;    //    25
    UINT32 reg_pad_eb_addr6__ds2: 1;    //    26
    UINT32 reg_pad_eb_addr6__ds3: 1;    //    27
    UINT32 reg_pad_eb_addr6__pd: 1;    //     28
    UINT32 reg_pad_eb_addr6__pu: 1;    //     29
    UINT32 reg_pad_eb_addr6__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD009_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x28    pad_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr13__ds0: 1;    //    0
    UINT32 reg_pad_eb_addr13__ds1: 1;    //    1
    UINT32 reg_pad_eb_addr13__ds2: 1;    //    2
    UINT32 reg_pad_eb_addr13__ds3: 1;    //    3
    UINT32 reg_pad_eb_addr13__pd: 1;    //     4
    UINT32 reg_pad_eb_addr13__pu: 1;    //     5
    UINT32 reg_pad_eb_addr13__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr12__ds0: 1;    //    8
    UINT32 reg_pad_eb_addr12__ds1: 1;    //    9
    UINT32 reg_pad_eb_addr12__ds2: 1;    //   10
    UINT32 reg_pad_eb_addr12__ds3: 1;    //   11
    UINT32 reg_pad_eb_addr12__pd: 1;    //    12
    UINT32 reg_pad_eb_addr12__pu: 1;    //    13
    UINT32 reg_pad_eb_addr12__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr11__ds0: 1;    //   16
    UINT32 reg_pad_eb_addr11__ds1: 1;    //   17
    UINT32 reg_pad_eb_addr11__ds2: 1;    //   18
    UINT32 reg_pad_eb_addr11__ds3: 1;    //   19
    UINT32 reg_pad_eb_addr11__pd: 1;    //    20
    UINT32 reg_pad_eb_addr11__pu: 1;    //    21
    UINT32 reg_pad_eb_addr11__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr10__ds0: 1;    //   24
    UINT32 reg_pad_eb_addr10__ds1: 1;    //   25
    UINT32 reg_pad_eb_addr10__ds2: 1;    //   26
    UINT32 reg_pad_eb_addr10__ds3: 1;    //   27
    UINT32 reg_pad_eb_addr10__pd: 1;    //    28
    UINT32 reg_pad_eb_addr10__pu: 1;    //    29
    UINT32 reg_pad_eb_addr10__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD010_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C    pad_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_cs1__ds0:  1;    //      0
    UINT32 reg_pad_eb_cs1__ds1:  1;    //      1
    UINT32 reg_pad_eb_cs1__ds2:  1;    //      2
    UINT32 reg_pad_eb_cs1__ds3:  1;    //      3
    UINT32 reg_pad_eb_cs1__pd :  1;    //      4
    UINT32 reg_pad_eb_cs1__pu :  1;    //      5
    UINT32 reg_pad_eb_cs1__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_cs0__ds0:  1;    //      8
    UINT32 reg_pad_eb_cs0__ds1:  1;    //      9
    UINT32 reg_pad_eb_cs0__ds2:  1;    //     10
    UINT32 reg_pad_eb_cs0__ds3:  1;    //     11
    UINT32 reg_pad_eb_cs0__pd :  1;    //     12
    UINT32 reg_pad_eb_cs0__pu :  1;    //     13
    UINT32 reg_pad_eb_cs0__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr15__ds0: 1;    //   16
    UINT32 reg_pad_eb_addr15__ds1: 1;    //   17
    UINT32 reg_pad_eb_addr15__ds2: 1;    //   18
    UINT32 reg_pad_eb_addr15__ds3: 1;    //   19
    UINT32 reg_pad_eb_addr15__pd: 1;    //    20
    UINT32 reg_pad_eb_addr15__pu: 1;    //    21
    UINT32 reg_pad_eb_addr15__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr14__ds0: 1;    //   24
    UINT32 reg_pad_eb_addr14__ds1: 1;    //   25
    UINT32 reg_pad_eb_addr14__ds2: 1;    //   26
    UINT32 reg_pad_eb_addr14__ds3: 1;    //   27
    UINT32 reg_pad_eb_addr14__pd: 1;    //    28
    UINT32 reg_pad_eb_addr14__pu: 1;    //    29
    UINT32 reg_pad_eb_addr14__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD011_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x30    pad_vd012 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_we_n__ds0: 1;    //      0
    UINT32 reg_pad_eb_we_n__ds1: 1;    //      1
    UINT32 reg_pad_eb_we_n__ds2: 1;    //      2
    UINT32 reg_pad_eb_we_n__ds3: 1;    //      3
    UINT32 reg_pad_eb_we_n__pd:  1;    //      4
    UINT32 reg_pad_eb_we_n__pu:  1;    //      5
    UINT32 reg_pad_eb_we_n__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_oe_n__ds0: 1;    //      8
    UINT32 reg_pad_eb_oe_n__ds1: 1;    //      9
    UINT32 reg_pad_eb_oe_n__ds2: 1;    //     10
    UINT32 reg_pad_eb_oe_n__ds3: 1;    //     11
    UINT32 reg_pad_eb_oe_n__pd:  1;    //     12
    UINT32 reg_pad_eb_oe_n__pu:  1;    //     13
    UINT32 reg_pad_eb_oe_n__st:  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_cs3__ds0:  1;    //     16
    UINT32 reg_pad_eb_cs3__ds1:  1;    //     17
    UINT32 reg_pad_eb_cs3__ds2:  1;    //     18
    UINT32 reg_pad_eb_cs3__ds3:  1;    //     19
    UINT32 reg_pad_eb_cs3__pd :  1;    //     20
    UINT32 reg_pad_eb_cs3__pu :  1;    //     21
    UINT32 reg_pad_eb_cs3__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_cs2__ds0:  1;    //     24
    UINT32 reg_pad_eb_cs2__ds1:  1;    //     25
    UINT32 reg_pad_eb_cs2__ds2:  1;    //     26
    UINT32 reg_pad_eb_cs2__ds3:  1;    //     27
    UINT32 reg_pad_eb_cs2__pd :  1;    //     28
    UINT32 reg_pad_eb_cs2__pu :  1;    //     29
    UINT32 reg_pad_eb_cs2__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD012_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x34    pad_vd013 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_ce1_n__ds0: 1;    //    0
    UINT32 reg_pad_cam_ce1_n__ds1: 1;    //    1
    UINT32 reg_pad_cam_ce1_n__ds2: 1;    //    2
    UINT32 reg_pad_cam_ce1_n__ds3: 1;    //    3
    UINT32 reg_pad_cam_ce1_n__pd: 1;    //     4
    UINT32 reg_pad_cam_ce1_n__pu: 1;    //     5
    UINT32 reg_pad_cam_ce1_n__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_be_n1__ds0: 1;    //     8
    UINT32 reg_pad_eb_be_n1__ds1: 1;    //     9
    UINT32 reg_pad_eb_be_n1__ds2: 1;    //    10
    UINT32 reg_pad_eb_be_n1__ds3: 1;    //    11
    UINT32 reg_pad_eb_be_n1__pd: 1;    //     12
    UINT32 reg_pad_eb_be_n1__pu: 1;    //     13
    UINT32 reg_pad_eb_be_n1__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_be_n0__ds0: 1;    //    16
    UINT32 reg_pad_eb_be_n0__ds1: 1;    //    17
    UINT32 reg_pad_eb_be_n0__ds2: 1;    //    18
    UINT32 reg_pad_eb_be_n0__ds3: 1;    //    19
    UINT32 reg_pad_eb_be_n0__pd: 1;    //     20
    UINT32 reg_pad_eb_be_n0__pu: 1;    //     21
    UINT32 reg_pad_eb_be_n0__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_wait__ds0: 1;    //     24
    UINT32 reg_pad_eb_wait__ds1: 1;    //     25
    UINT32 reg_pad_eb_wait__ds2: 1;    //     26
    UINT32 reg_pad_eb_wait__ds3: 1;    //     27
    UINT32 reg_pad_eb_wait__pd:  1;    //     28
    UINT32 reg_pad_eb_wait__pu:  1;    //     29
    UINT32 reg_pad_eb_wait__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD013_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x38    pad_vd014 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_ireq_n__ds0: 1;    //   0
    UINT32 reg_pad_cam_ireq_n__ds1: 1;    //   1
    UINT32 reg_pad_cam_ireq_n__ds2: 1;    //   2
    UINT32 reg_pad_cam_ireq_n__ds3: 1;    //   3
    UINT32 reg_pad_cam_ireq_n__pd: 1;    //    4
    UINT32 reg_pad_cam_ireq_n__pu: 1;    //    5
    UINT32 reg_pad_cam_ireq_n__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_cam_cd2_n__ds0: 1;    //    8
    UINT32 reg_pad_cam_cd2_n__ds1: 1;    //    9
    UINT32 reg_pad_cam_cd2_n__ds2: 1;    //   10
    UINT32 reg_pad_cam_cd2_n__ds3: 1;    //   11
    UINT32 reg_pad_cam_cd2_n__pd: 1;    //    12
    UINT32 reg_pad_cam_cd2_n__pu: 1;    //    13
    UINT32 reg_pad_cam_cd2_n__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_cam_cd1_n__ds0: 1;    //   16
    UINT32 reg_pad_cam_cd1_n__ds1: 1;    //   17
    UINT32 reg_pad_cam_cd1_n__ds2: 1;    //   18
    UINT32 reg_pad_cam_cd1_n__ds3: 1;    //   19
    UINT32 reg_pad_cam_cd1_n__pd: 1;    //    20
    UINT32 reg_pad_cam_cd1_n__pu: 1;    //    21
    UINT32 reg_pad_cam_cd1_n__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_cam_ce2_n__ds0: 1;    //   24
    UINT32 reg_pad_cam_ce2_n__ds1: 1;    //   25
    UINT32 reg_pad_cam_ce2_n__ds2: 1;    //   26
    UINT32 reg_pad_cam_ce2_n__ds3: 1;    //   27
    UINT32 reg_pad_cam_ce2_n__pd: 1;    //    28
    UINT32 reg_pad_cam_ce2_n__pu: 1;    //    29
    UINT32 reg_pad_cam_ce2_n__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD014_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C    pad_vd015 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_reset__ds0: 1;    //    0
    UINT32 reg_pad_cam_reset__ds1: 1;    //    1
    UINT32 reg_pad_cam_reset__ds2: 1;    //    2
    UINT32 reg_pad_cam_reset__ds3: 1;    //    3
    UINT32 reg_pad_cam_reset__pd: 1;    //     4
    UINT32 reg_pad_cam_reset__pu: 1;    //     5
    UINT32 reg_pad_cam_reset__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_cam_vccen_n__ds0: 1;    //  8
    UINT32 reg_pad_cam_vccen_n__ds1: 1;    //  9
    UINT32 reg_pad_cam_vccen_n__ds2: 1;    //  10
    UINT32 reg_pad_cam_vccen_n__ds3: 1;    //  11
    UINT32 reg_pad_cam_vccen_n__pd: 1;    //  12
    UINT32 reg_pad_cam_vccen_n__pu: 1;    //  13
    UINT32 reg_pad_cam_vccen_n__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_cam_wait_n__ds0: 1;    //  16
    UINT32 reg_pad_cam_wait_n__ds1: 1;    //  17
    UINT32 reg_pad_cam_wait_n__ds2: 1;    //  18
    UINT32 reg_pad_cam_wait_n__ds3: 1;    //  19
    UINT32 reg_pad_cam_wait_n__pd: 1;    //   20
    UINT32 reg_pad_cam_wait_n__pu: 1;    //   21
    UINT32 reg_pad_cam_wait_n__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_cam_reg_n__ds0: 1;    //   24
    UINT32 reg_pad_cam_reg_n__ds1: 1;    //   25
    UINT32 reg_pad_cam_reg_n__ds2: 1;    //   26
    UINT32 reg_pad_cam_reg_n__ds3: 1;    //   27
    UINT32 reg_pad_cam_reg_n__pd: 1;    //    28
    UINT32 reg_pad_cam_reg_n__pu: 1;    //    29
    UINT32 reg_pad_cam_reg_n__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_VD0_PAD_VD015_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_vd064 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data6_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data5_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data4_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data3_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data2_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data1_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data0_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_clk_cam_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD064_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x104    pad_vd065 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data3_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpo_data2_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpo_data1_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpo_data0_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpo_clk_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_val_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_sop_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data7_cam_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD065_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x108    pad_vd066 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_data0_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpo_val_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpo_sop_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpo_data7_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpo_data6_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpo_data5_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpo_data4_cam_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD066_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x10C    pad_vd067 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_addr0_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_data7_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_data6_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_data5_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_data4_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_data3_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_data2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD067_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x110    pad_vd068 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr9_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_addr8_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_addr7_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_addr6_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_addr5_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_addr4_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_addr3_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_addr2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD068_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x114    pad_vd069 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_cs1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_cs0_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_addr15_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_addr14_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_addr13_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_addr12_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_addr11_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_addr10_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD069_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x118    pad_vd070 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_ce1_n_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_be_n1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_be_n0_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_wait_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_we_n_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_oe_n_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_cs3_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_cs2_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD070_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x11C    pad_vd071 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_reset_mux_sel: 4;    //  3:0
    UINT32 reg_pad_cam_vccen_n_mux_sel: 4;    //  7:4
    UINT32 reg_pad_cam_wait_n_mux_sel: 4;    //  11:8
    UINT32 reg_pad_cam_reg_n_mux_sel: 4;    //  15:12
    UINT32 reg_pad_cam_ireq_n_mux_sel: 4;    //  19:16
    UINT32 reg_pad_cam_cd2_n_mux_sel: 4;    //  23:20
    UINT32 reg_pad_cam_cd1_n_mux_sel: 4;    //  27:24
    UINT32 reg_pad_cam_ce2_n_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_VD0_PAD_VD071_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_VD0_PAD_VD000_M23A0_T     pad_vd000  ;             // 0x0
    IOMUX_CTRL_VD0_PAD_VD001_M23A0_T     pad_vd001  ;             // 0x4
    IOMUX_CTRL_VD0_PAD_VD002_M23A0_T     pad_vd002  ;             // 0x8
    IOMUX_CTRL_VD0_PAD_VD003_M23A0_T     pad_vd003  ;             // 0xC
    IOMUX_CTRL_VD0_PAD_VD004_M23A0_T     pad_vd004  ;             // 0x10
    IOMUX_CTRL_VD0_PAD_VD005_M23A0_T     pad_vd005  ;             // 0x14
    IOMUX_CTRL_VD0_PAD_VD006_M23A0_T     pad_vd006  ;             // 0x18
    IOMUX_CTRL_VD0_PAD_VD007_M23A0_T     pad_vd007  ;             // 0x1C
    IOMUX_CTRL_VD0_PAD_VD008_M23A0_T     pad_vd008  ;             // 0x20
    IOMUX_CTRL_VD0_PAD_VD009_M23A0_T     pad_vd009  ;             // 0x24
    IOMUX_CTRL_VD0_PAD_VD010_M23A0_T     pad_vd010  ;             // 0x28
    IOMUX_CTRL_VD0_PAD_VD011_M23A0_T     pad_vd011  ;             // 0x2C
    IOMUX_CTRL_VD0_PAD_VD012_M23A0_T     pad_vd012  ;             // 0x30
    IOMUX_CTRL_VD0_PAD_VD013_M23A0_T     pad_vd013  ;             // 0x34
    IOMUX_CTRL_VD0_PAD_VD014_M23A0_T     pad_vd014  ;             // 0x38
    IOMUX_CTRL_VD0_PAD_VD015_M23A0_T     pad_vd015  ;             // 0x3C
    UINT32                             _rsvd_00[48];            // 0x40 ~ 0xFC
    IOMUX_CTRL_VD0_PAD_VD064_M23A0_T     pad_vd064  ;             // 0x100
    IOMUX_CTRL_VD0_PAD_VD065_M23A0_T     pad_vd065  ;             // 0x104
    IOMUX_CTRL_VD0_PAD_VD066_M23A0_T     pad_vd066  ;             // 0x108
    IOMUX_CTRL_VD0_PAD_VD067_M23A0_T     pad_vd067  ;             // 0x10C
    IOMUX_CTRL_VD0_PAD_VD068_M23A0_T     pad_vd068  ;             // 0x110
    IOMUX_CTRL_VD0_PAD_VD069_M23A0_T     pad_vd069  ;             // 0x114
    IOMUX_CTRL_VD0_PAD_VD070_M23A0_T     pad_vd070  ;             // 0x118
    IOMUX_CTRL_VD0_PAD_VD071_M23A0_T     pad_vd071  ;             // 0x11C
}IOMUX_CTRL_VD0_REG_M23A0_T;
/* 24 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_PAD_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

