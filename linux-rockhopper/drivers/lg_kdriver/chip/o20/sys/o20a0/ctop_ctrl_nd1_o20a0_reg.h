#ifndef _CTOP_CTRL_ND1_O20A0_REG_H_
#define _CTOP_CTRL_ND1_O20A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC930_8400    iomux_disable01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ir_enable             :  1,    //      0
    reg_dbb_tst_enable        :  1,    //      1
    reg_dbb_i2c_enable        :  1,    //      2
    reg_eb_wait_disable       :  1,    //      3
                              : 28;    //   31:4 reserved
}CTOP_CTRL_ND1_IOMUX_DISABLE01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8404    ioctrl_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mon0_en               :  1,    //      0
    reg_mon1_en               :  1,    //      1
    reg_mon2_en               :  1,    //      2
                              :  1,    //      3 reserved
    reg_mon_sel0              :  5,    //   8: 4
                              :  3,    //  11: 9 reserved
    reg_mon_sel1              :  5,    //  16:12
                              :  3,    //  19:17 reserved
    reg_mon_sel2              :  5,    //  24:20
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8408    ioctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_vccen_n__st   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_cam_vccen_n__pu   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_cam_vccen_n__pd   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_cam_vccen_n__ds3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_cam_vccen_n__ds2  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_cam_vccen_n__ds1  :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_cam_vccen_n__ds0  :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_840C    ioctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr0__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr0__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr0__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr0__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr0__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr0__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr0__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_2_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8410    ioctrl_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr1__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr1__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr1__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr1__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr1__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr1__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr1__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_3_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8414    ioctrl_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr10__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr10__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr10__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr10__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr10__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr10__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr10__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_4_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8418    ioctrl_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr11__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr11__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr11__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr11__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr11__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr11__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr11__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_5_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_841C    ioctrl_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr12__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr12__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr12__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr12__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr12__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr12__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr12__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_6_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8420    ioctrl_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr13__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr13__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr13__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr13__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr13__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr13__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr13__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_7_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8424    ioctrl_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr14__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr14__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr14__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr14__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr14__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr14__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr14__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_8_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8428    ioctrl_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr15__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr15__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr15__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr15__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr15__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr15__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr15__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_9_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_842C    ioctrl_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr2__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr2__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr2__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr2__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr2__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr2__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr2__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8430    ioctrl_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr3__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr3__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr3__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr3__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr3__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr3__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr3__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8434    ioctrl_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr4__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr4__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr4__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr4__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr4__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr4__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr4__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8438    ioctrl_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr5__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr5__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr5__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr5__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr5__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr5__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr5__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_843C    ioctrl_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr6__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr6__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr6__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr6__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr6__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr6__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr6__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8440    ioctrl_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr7__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr7__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr7__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr7__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr7__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr7__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr7__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8444    ioctrl_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr8__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr8__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr8__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr8__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr8__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr8__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr8__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8448    ioctrl_17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr9__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_addr9__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_addr9__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_addr9__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_addr9__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_addr9__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_addr9__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_844C    ioctrl_18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_be_n0__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_be_n0__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_be_n0__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_be_n0__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_be_n0__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_be_n0__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_be_n0__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8450    ioctrl_19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_be_n1__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_be_n1__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_be_n1__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_be_n1__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_be_n1__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_be_n1__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_be_n1__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8454    ioctrl_20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs0__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_cs0__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_cs0__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_cs0__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_cs0__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_cs0__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_cs0__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8458    ioctrl_21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs1__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_cs1__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_cs1__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_cs1__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_cs1__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_cs1__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_cs1__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_845C    ioctrl_22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs2__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_cs2__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_cs2__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_cs2__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_cs2__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_cs2__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_cs2__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8460    ioctrl_23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs3__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_cs3__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_cs3__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_cs3__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_cs3__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_cs3__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_cs3__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8464    ioctrl_24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data0__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data0__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data0__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data0__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data0__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data0__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data0__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8468    ioctrl_25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data1__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data1__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data1__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data1__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data1__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data1__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data1__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_846C    ioctrl_26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data2__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data2__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data2__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data2__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data2__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data2__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data2__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_26_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8470    ioctrl_27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data3__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data3__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data3__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data3__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data3__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data3__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data3__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_27_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8474    ioctrl_28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data4__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data4__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data4__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data4__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data4__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data4__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data4__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_28_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8478    ioctrl_29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data5__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data5__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data5__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data5__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data5__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data5__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data5__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_29_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_847C    ioctrl_30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data6__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data6__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data6__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data6__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data6__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data6__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data6__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_30_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8480    ioctrl_31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data7__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_data7__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_data7__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_data7__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_data7__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_data7__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_data7__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_31_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8484    ioctrl_32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_oe_n__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_oe_n__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_oe_n__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_oe_n__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_oe_n__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_oe_n__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_oe_n__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_32_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8488    ioctrl_33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_wait__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_wait__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_wait__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_wait__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_wait__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_wait__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_wait__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_33_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_848C    ioctrl_34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_we_n__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_eb_we_n__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_eb_we_n__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_eb_we_n__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_eb_we_n__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_eb_we_n__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_eb_we_n__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_34_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8490    ioctrl_35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio94__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio94__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio94__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio94__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio94__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio94__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio94__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_35_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8494    ioctrl_36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio95__st        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_gpio95__pu        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_gpio95__pd        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_gpio95__ds3       :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_gpio95__ds2       :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_gpio95__ds1       :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_gpio95__ds0       :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_36_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_8498    ioctrl_37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_clk__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_clk__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_clk__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_clk__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_clk__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_clk__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_37_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_849C    ioctrl_38 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data0__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data0__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data0__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data0__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data0__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data0__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_38_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84A0    ioctrl_39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data1__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data1__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data1__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data1__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data1__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data1__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data1__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_39_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84A4    ioctrl_40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data2__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data2__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data2__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data2__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data2__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data2__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data2__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_40_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84A8    ioctrl_41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data3__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data3__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data3__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data3__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data3__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data3__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data3__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_41_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84AC    ioctrl_42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data4__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data4__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data4__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data4__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data4__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data4__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_42_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84B0    ioctrl_43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data5__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data5__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data5__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data5__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data5__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data5__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_43_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84B4    ioctrl_44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data6__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data6__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data6__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data6__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data6__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data6__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data6__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_44_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84B8    ioctrl_45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7__st     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_data7__pu     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_data7__pd     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_data7__ds3    :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_data7__ds2    :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_data7__ds1    :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_data7__ds0    :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_45_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84BC    ioctrl_46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_sop__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_sop__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_sop__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_sop__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_sop__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_sop__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_sop__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_46_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84C0    ioctrl_47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_val__st       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpi_val__pu       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpi_val__pd       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpi_val__ds3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpi_val__ds2      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpi_val__ds1      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpi_val__ds0      :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_47_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84C4    ioctrl_48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_clk__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_clk__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_clk__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_clk__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_clk__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_clk__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_clk__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_48_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84C8    ioctrl_49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data0__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data0__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data0__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data0__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data0__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data0__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data0__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_49_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84D0    ioctrl_50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data1__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data1__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data1__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data1__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data1__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data1__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data1__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_50_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84D4    ioctrl_51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data2__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data2__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data2__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data2__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data2__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data2__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data2__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_51_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84D8    ioctrl_52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data3__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data3__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data3__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data3__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data3__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data3__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data3__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_52_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84DC    ioctrl_53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data4__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data4__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data4__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data4__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data4__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data4__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data4__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_53_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84E0    ioctrl_54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data5__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data5__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data5__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data5__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data5__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data5__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data5__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_54_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84E4    ioctrl_55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data6__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data6__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data6__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data6__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data6__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data6__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data6__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_55_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84E8    ioctrl_56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_data7__st    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_data7__pu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_data7__pd    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_data7__ds3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_data7__ds2   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_data7__ds1   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_data7__ds0   :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_56_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84EC    ioctrl_57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_sop__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_sop__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_sop__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_sop__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_sop__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_sop__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_sop__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_57_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84F0    ioctrl_58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpio_val__st      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pad_tpio_val__pu      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_tpio_val__pd      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pad_tpio_val__ds3     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_pad_tpio_val__ds2     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_pad_tpio_val__ds1     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_pad_tpio_val__ds0     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ND1_IOCTRL_58_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84F4    ioctrl_59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_11_5     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_11_4     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_11_3     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_11_2     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_11_1     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_11_0     :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_ND1_IOCTRL_59_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84F8    ioctrl_60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_14_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_14_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_14_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_14_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_14_3     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_14_2     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_14_1     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_14_0     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_ND1_IOCTRL_60_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_84FC    ioctrl_61 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_cpu_gpio_15_7     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_use_cpu_gpio_15_6     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_use_cpu_gpio_15_5     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_use_cpu_gpio_15_4     :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_use_cpu_gpio_15_3     :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_use_cpu_gpio_15_2     :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_use_cpu_gpio_15_1     :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_use_cpu_gpio_15_0     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_ND1_IOCTRL_61_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_ND1_IOMUX_DISABLE01_O20A0_T        iomux_disable01          ;         // 0xC930_8400
CTOP_CTRL_ND1_IOCTRL_0_O20A0_T               ioctrl_0                 ;         // 0xC930_8404
CTOP_CTRL_ND1_IOCTRL_1_O20A0_T               ioctrl_1                 ;         // 0xC930_8408
CTOP_CTRL_ND1_IOCTRL_2_O20A0_T               ioctrl_2                 ;         // 0xC930_840C
CTOP_CTRL_ND1_IOCTRL_3_O20A0_T               ioctrl_3                 ;         // 0xC930_8410
CTOP_CTRL_ND1_IOCTRL_4_O20A0_T               ioctrl_4                 ;         // 0xC930_8414
CTOP_CTRL_ND1_IOCTRL_5_O20A0_T               ioctrl_5                 ;         // 0xC930_8418
CTOP_CTRL_ND1_IOCTRL_6_O20A0_T               ioctrl_6                 ;         // 0xC930_841C
CTOP_CTRL_ND1_IOCTRL_7_O20A0_T               ioctrl_7                 ;         // 0xC930_8420
CTOP_CTRL_ND1_IOCTRL_8_O20A0_T               ioctrl_8                 ;         // 0xC930_8424
CTOP_CTRL_ND1_IOCTRL_9_O20A0_T               ioctrl_9                 ;         // 0xC930_8428
CTOP_CTRL_ND1_IOCTRL_10_O20A0_T              ioctrl_10                ;         // 0xC930_842C
CTOP_CTRL_ND1_IOCTRL_11_O20A0_T              ioctrl_11                ;         // 0xC930_8430
CTOP_CTRL_ND1_IOCTRL_12_O20A0_T              ioctrl_12                ;         // 0xC930_8434
CTOP_CTRL_ND1_IOCTRL_13_O20A0_T              ioctrl_13                ;         // 0xC930_8438
CTOP_CTRL_ND1_IOCTRL_14_O20A0_T              ioctrl_14                ;         // 0xC930_843C
CTOP_CTRL_ND1_IOCTRL_15_O20A0_T              ioctrl_15                ;         // 0xC930_8440
CTOP_CTRL_ND1_IOCTRL_16_O20A0_T              ioctrl_16                ;         // 0xC930_8444
CTOP_CTRL_ND1_IOCTRL_17_O20A0_T              ioctrl_17                ;         // 0xC930_8448
CTOP_CTRL_ND1_IOCTRL_18_O20A0_T              ioctrl_18                ;         // 0xC930_844C
CTOP_CTRL_ND1_IOCTRL_19_O20A0_T              ioctrl_19                ;         // 0xC930_8450
CTOP_CTRL_ND1_IOCTRL_20_O20A0_T              ioctrl_20                ;         // 0xC930_8454
CTOP_CTRL_ND1_IOCTRL_21_O20A0_T              ioctrl_21                ;         // 0xC930_8458
CTOP_CTRL_ND1_IOCTRL_22_O20A0_T              ioctrl_22                ;         // 0xC930_845C
CTOP_CTRL_ND1_IOCTRL_23_O20A0_T              ioctrl_23                ;         // 0xC930_8460
CTOP_CTRL_ND1_IOCTRL_24_O20A0_T              ioctrl_24                ;         // 0xC930_8464
CTOP_CTRL_ND1_IOCTRL_25_O20A0_T              ioctrl_25                ;         // 0xC930_8468
CTOP_CTRL_ND1_IOCTRL_26_O20A0_T              ioctrl_26                ;         // 0xC930_846C
CTOP_CTRL_ND1_IOCTRL_27_O20A0_T              ioctrl_27                ;         // 0xC930_8470
CTOP_CTRL_ND1_IOCTRL_28_O20A0_T              ioctrl_28                ;         // 0xC930_8474
CTOP_CTRL_ND1_IOCTRL_29_O20A0_T              ioctrl_29                ;         // 0xC930_8478
CTOP_CTRL_ND1_IOCTRL_30_O20A0_T              ioctrl_30                ;         // 0xC930_847C
CTOP_CTRL_ND1_IOCTRL_31_O20A0_T              ioctrl_31                ;         // 0xC930_8480
CTOP_CTRL_ND1_IOCTRL_32_O20A0_T              ioctrl_32                ;         // 0xC930_8484
CTOP_CTRL_ND1_IOCTRL_33_O20A0_T              ioctrl_33                ;         // 0xC930_8488
CTOP_CTRL_ND1_IOCTRL_34_O20A0_T              ioctrl_34                ;         // 0xC930_848C
CTOP_CTRL_ND1_IOCTRL_35_O20A0_T              ioctrl_35                ;         // 0xC930_8490
CTOP_CTRL_ND1_IOCTRL_36_O20A0_T              ioctrl_36                ;         // 0xC930_8494
CTOP_CTRL_ND1_IOCTRL_37_O20A0_T              ioctrl_37                ;         // 0xC930_8498
CTOP_CTRL_ND1_IOCTRL_38_O20A0_T              ioctrl_38                ;         // 0xC930_849C
CTOP_CTRL_ND1_IOCTRL_39_O20A0_T              ioctrl_39                ;         // 0xC930_84A0
CTOP_CTRL_ND1_IOCTRL_40_O20A0_T              ioctrl_40                ;         // 0xC930_84A4
CTOP_CTRL_ND1_IOCTRL_41_O20A0_T              ioctrl_41                ;         // 0xC930_84A8
CTOP_CTRL_ND1_IOCTRL_42_O20A0_T              ioctrl_42                ;         // 0xC930_84AC
CTOP_CTRL_ND1_IOCTRL_43_O20A0_T              ioctrl_43                ;         // 0xC930_84B0
CTOP_CTRL_ND1_IOCTRL_44_O20A0_T              ioctrl_44                ;         // 0xC930_84B4
CTOP_CTRL_ND1_IOCTRL_45_O20A0_T              ioctrl_45                ;         // 0xC930_84B8
CTOP_CTRL_ND1_IOCTRL_46_O20A0_T              ioctrl_46                ;         // 0xC930_84BC
CTOP_CTRL_ND1_IOCTRL_47_O20A0_T              ioctrl_47                ;         // 0xC930_84C0
CTOP_CTRL_ND1_IOCTRL_48_O20A0_T              ioctrl_48                ;         // 0xC930_84C4
CTOP_CTRL_ND1_IOCTRL_49_O20A0_T              ioctrl_49                ;         // 0xC930_84C8
UINT32                                                 _rsvd_00[   1] ;         // 0xC930_84CC
CTOP_CTRL_ND1_IOCTRL_50_O20A0_T              ioctrl_50                ;         // 0xC930_84D0
CTOP_CTRL_ND1_IOCTRL_51_O20A0_T              ioctrl_51                ;         // 0xC930_84D4
CTOP_CTRL_ND1_IOCTRL_52_O20A0_T              ioctrl_52                ;         // 0xC930_84D8
CTOP_CTRL_ND1_IOCTRL_53_O20A0_T              ioctrl_53                ;         // 0xC930_84DC
CTOP_CTRL_ND1_IOCTRL_54_O20A0_T              ioctrl_54                ;         // 0xC930_84E0
CTOP_CTRL_ND1_IOCTRL_55_O20A0_T              ioctrl_55                ;         // 0xC930_84E4
CTOP_CTRL_ND1_IOCTRL_56_O20A0_T              ioctrl_56                ;         // 0xC930_84E8
CTOP_CTRL_ND1_IOCTRL_57_O20A0_T              ioctrl_57                ;         // 0xC930_84EC
CTOP_CTRL_ND1_IOCTRL_58_O20A0_T              ioctrl_58                ;         // 0xC930_84F0
CTOP_CTRL_ND1_IOCTRL_59_O20A0_T              ioctrl_59                ;         // 0xC930_84F4
CTOP_CTRL_ND1_IOCTRL_60_O20A0_T              ioctrl_60                ;         // 0xC930_84F8
CTOP_CTRL_ND1_IOCTRL_61_O20A0_T              ioctrl_61                ;         // 0xC930_84FC
} CTOP_CTRL_ND1_REG_O20A0_T;
/* 63 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_ND1_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

