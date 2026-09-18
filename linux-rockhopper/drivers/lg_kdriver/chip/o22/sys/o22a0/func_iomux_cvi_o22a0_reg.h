#ifndef _FUNC_IOMUX_CVI_REG_H_
#define _FUNC_IOMUX_CVI_REG_H_

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
    0xCC87_4000    pad_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data0_cam__ds0:  1,    //      0
    reg_pad_tpo_data0_cam__ds1:  1,    //      1
    reg_pad_tpo_data0_cam__ds2:  1,    //      2
    reg_pad_tpo_data0_cam__ds3:  1,    //      3
    reg_pad_tpo_data0_cam__pd :  1,    //      4
    reg_pad_tpo_data0_cam__pu :  1,    //      5
    reg_pad_tpo_data0_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_val_cam__ds0  :  1,    //      8
    reg_pad_tpo_val_cam__ds1  :  1,    //      9
    reg_pad_tpo_val_cam__ds2  :  1,    //     10
    reg_pad_tpo_val_cam__ds3  :  1,    //     11
    reg_pad_tpo_val_cam__pd   :  1,    //     12
    reg_pad_tpo_val_cam__pu   :  1,    //     13
    reg_pad_tpo_val_cam__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_sop_cam__ds0  :  1,    //     16
    reg_pad_tpo_sop_cam__ds1  :  1,    //     17
    reg_pad_tpo_sop_cam__ds2  :  1,    //     18
    reg_pad_tpo_sop_cam__ds3  :  1,    //     19
    reg_pad_tpo_sop_cam__pd   :  1,    //     20
    reg_pad_tpo_sop_cam__pu   :  1,    //     21
    reg_pad_tpo_sop_cam__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_clk_cam__ds0  :  1,    //     24
    reg_pad_tpo_clk_cam__ds1  :  1,    //     25
    reg_pad_tpo_clk_cam__ds2  :  1,    //     26
    reg_pad_tpo_clk_cam__ds3  :  1,    //     27
    reg_pad_tpo_clk_cam__pd   :  1,    //     28
    reg_pad_tpo_clk_cam__pu   :  1,    //     29
    reg_pad_tpo_clk_cam__st   :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4004    pad_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data4_cam__ds0:  1,    //      0
    reg_pad_tpo_data4_cam__ds1:  1,    //      1
    reg_pad_tpo_data4_cam__ds2:  1,    //      2
    reg_pad_tpo_data4_cam__ds3:  1,    //      3
    reg_pad_tpo_data4_cam__pd :  1,    //      4
    reg_pad_tpo_data4_cam__pu :  1,    //      5
    reg_pad_tpo_data4_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data3_cam__ds0:  1,    //      8
    reg_pad_tpo_data3_cam__ds1:  1,    //      9
    reg_pad_tpo_data3_cam__ds2:  1,    //     10
    reg_pad_tpo_data3_cam__ds3:  1,    //     11
    reg_pad_tpo_data3_cam__pd :  1,    //     12
    reg_pad_tpo_data3_cam__pu :  1,    //     13
    reg_pad_tpo_data3_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data2_cam__ds0:  1,    //     16
    reg_pad_tpo_data2_cam__ds1:  1,    //     17
    reg_pad_tpo_data2_cam__ds2:  1,    //     18
    reg_pad_tpo_data2_cam__ds3:  1,    //     19
    reg_pad_tpo_data2_cam__pd :  1,    //     20
    reg_pad_tpo_data2_cam__pu :  1,    //     21
    reg_pad_tpo_data2_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data1_cam__ds0:  1,    //     24
    reg_pad_tpo_data1_cam__ds1:  1,    //     25
    reg_pad_tpo_data1_cam__ds2:  1,    //     26
    reg_pad_tpo_data1_cam__ds3:  1,    //     27
    reg_pad_tpo_data1_cam__pd :  1,    //     28
    reg_pad_tpo_data1_cam__pu :  1,    //     29
    reg_pad_tpo_data1_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4008    pad_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs0__ds0       :  1,    //      0
    reg_pad_eb_cs0__ds1       :  1,    //      1
    reg_pad_eb_cs0__ds2       :  1,    //      2
    reg_pad_eb_cs0__ds3       :  1,    //      3
    reg_pad_eb_cs0__pd        :  1,    //      4
    reg_pad_eb_cs0__pu        :  1,    //      5
    reg_pad_eb_cs0__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data7_cam__ds0:  1,    //      8
    reg_pad_tpo_data7_cam__ds1:  1,    //      9
    reg_pad_tpo_data7_cam__ds2:  1,    //     10
    reg_pad_tpo_data7_cam__ds3:  1,    //     11
    reg_pad_tpo_data7_cam__pd :  1,    //     12
    reg_pad_tpo_data7_cam__pu :  1,    //     13
    reg_pad_tpo_data7_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data6_cam__ds0:  1,    //     16
    reg_pad_tpo_data6_cam__ds1:  1,    //     17
    reg_pad_tpo_data6_cam__ds2:  1,    //     18
    reg_pad_tpo_data6_cam__ds3:  1,    //     19
    reg_pad_tpo_data6_cam__pd :  1,    //     20
    reg_pad_tpo_data6_cam__pu :  1,    //     21
    reg_pad_tpo_data6_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data5_cam__ds0:  1,    //     24
    reg_pad_tpo_data5_cam__ds1:  1,    //     25
    reg_pad_tpo_data5_cam__ds2:  1,    //     26
    reg_pad_tpo_data5_cam__ds3:  1,    //     27
    reg_pad_tpo_data5_cam__pd :  1,    //     28
    reg_pad_tpo_data5_cam__pu :  1,    //     29
    reg_pad_tpo_data5_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_400C    pad_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_oe_n__ds0      :  1,    //      0
    reg_pad_eb_oe_n__ds1      :  1,    //      1
    reg_pad_eb_oe_n__ds2      :  1,    //      2
    reg_pad_eb_oe_n__ds3      :  1,    //      3
    reg_pad_eb_oe_n__pd       :  1,    //      4
    reg_pad_eb_oe_n__pu       :  1,    //      5
    reg_pad_eb_oe_n__st       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_cs3__ds0       :  1,    //      8
    reg_pad_eb_cs3__ds1       :  1,    //      9
    reg_pad_eb_cs3__ds2       :  1,    //     10
    reg_pad_eb_cs3__ds3       :  1,    //     11
    reg_pad_eb_cs3__pd        :  1,    //     12
    reg_pad_eb_cs3__pu        :  1,    //     13
    reg_pad_eb_cs3__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_cs2__ds0       :  1,    //     16
    reg_pad_eb_cs2__ds1       :  1,    //     17
    reg_pad_eb_cs2__ds2       :  1,    //     18
    reg_pad_eb_cs2__ds3       :  1,    //     19
    reg_pad_eb_cs2__pd        :  1,    //     20
    reg_pad_eb_cs2__pu        :  1,    //     21
    reg_pad_eb_cs2__st        :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_cs1__ds0       :  1,    //     24
    reg_pad_eb_cs1__ds1       :  1,    //     25
    reg_pad_eb_cs1__ds2       :  1,    //     26
    reg_pad_eb_cs1__ds3       :  1,    //     27
    reg_pad_eb_cs1__pd        :  1,    //     28
    reg_pad_eb_cs1__pu        :  1,    //     29
    reg_pad_eb_cs1__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4010    pad_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_be_n1__ds0     :  1,    //      0
    reg_pad_eb_be_n1__ds1     :  1,    //      1
    reg_pad_eb_be_n1__ds2     :  1,    //      2
    reg_pad_eb_be_n1__ds3     :  1,    //      3
    reg_pad_eb_be_n1__pd      :  1,    //      4
    reg_pad_eb_be_n1__pu      :  1,    //      5
    reg_pad_eb_be_n1__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_be_n0__ds0     :  1,    //      8
    reg_pad_eb_be_n0__ds1     :  1,    //      9
    reg_pad_eb_be_n0__ds2     :  1,    //     10
    reg_pad_eb_be_n0__ds3     :  1,    //     11
    reg_pad_eb_be_n0__pd      :  1,    //     12
    reg_pad_eb_be_n0__pu      :  1,    //     13
    reg_pad_eb_be_n0__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_wait__ds0      :  1,    //     16
    reg_pad_eb_wait__ds1      :  1,    //     17
    reg_pad_eb_wait__ds2      :  1,    //     18
    reg_pad_eb_wait__ds3      :  1,    //     19
    reg_pad_eb_wait__pd       :  1,    //     20
    reg_pad_eb_wait__pu       :  1,    //     21
    reg_pad_eb_wait__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_we_n__ds0      :  1,    //     24
    reg_pad_eb_we_n__ds1      :  1,    //     25
    reg_pad_eb_we_n__ds2      :  1,    //     26
    reg_pad_eb_we_n__ds3      :  1,    //     27
    reg_pad_eb_we_n__pd       :  1,    //     28
    reg_pad_eb_we_n__pu       :  1,    //     29
    reg_pad_eb_we_n__st       :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4014    pad_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr3__ds0     :  1,    //      0
    reg_pad_eb_addr3__ds1     :  1,    //      1
    reg_pad_eb_addr3__ds2     :  1,    //      2
    reg_pad_eb_addr3__ds3     :  1,    //      3
    reg_pad_eb_addr3__pd      :  1,    //      4
    reg_pad_eb_addr3__pu      :  1,    //      5
    reg_pad_eb_addr3__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr2__ds0     :  1,    //      8
    reg_pad_eb_addr2__ds1     :  1,    //      9
    reg_pad_eb_addr2__ds2     :  1,    //     10
    reg_pad_eb_addr2__ds3     :  1,    //     11
    reg_pad_eb_addr2__pd      :  1,    //     12
    reg_pad_eb_addr2__pu      :  1,    //     13
    reg_pad_eb_addr2__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr1__ds0     :  1,    //     16
    reg_pad_eb_addr1__ds1     :  1,    //     17
    reg_pad_eb_addr1__ds2     :  1,    //     18
    reg_pad_eb_addr1__ds3     :  1,    //     19
    reg_pad_eb_addr1__pd      :  1,    //     20
    reg_pad_eb_addr1__pu      :  1,    //     21
    reg_pad_eb_addr1__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr0__ds0     :  1,    //     24
    reg_pad_eb_addr0__ds1     :  1,    //     25
    reg_pad_eb_addr0__ds2     :  1,    //     26
    reg_pad_eb_addr0__ds3     :  1,    //     27
    reg_pad_eb_addr0__pd      :  1,    //     28
    reg_pad_eb_addr0__pu      :  1,    //     29
    reg_pad_eb_addr0__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4018    pad_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr7__ds0     :  1,    //      0
    reg_pad_eb_addr7__ds1     :  1,    //      1
    reg_pad_eb_addr7__ds2     :  1,    //      2
    reg_pad_eb_addr7__ds3     :  1,    //      3
    reg_pad_eb_addr7__pd      :  1,    //      4
    reg_pad_eb_addr7__pu      :  1,    //      5
    reg_pad_eb_addr7__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr6__ds0     :  1,    //      8
    reg_pad_eb_addr6__ds1     :  1,    //      9
    reg_pad_eb_addr6__ds2     :  1,    //     10
    reg_pad_eb_addr6__ds3     :  1,    //     11
    reg_pad_eb_addr6__pd      :  1,    //     12
    reg_pad_eb_addr6__pu      :  1,    //     13
    reg_pad_eb_addr6__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr5__ds0     :  1,    //     16
    reg_pad_eb_addr5__ds1     :  1,    //     17
    reg_pad_eb_addr5__ds2     :  1,    //     18
    reg_pad_eb_addr5__ds3     :  1,    //     19
    reg_pad_eb_addr5__pd      :  1,    //     20
    reg_pad_eb_addr5__pu      :  1,    //     21
    reg_pad_eb_addr5__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr4__ds0     :  1,    //     24
    reg_pad_eb_addr4__ds1     :  1,    //     25
    reg_pad_eb_addr4__ds2     :  1,    //     26
    reg_pad_eb_addr4__ds3     :  1,    //     27
    reg_pad_eb_addr4__pd      :  1,    //     28
    reg_pad_eb_addr4__pu      :  1,    //     29
    reg_pad_eb_addr4__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_401C    pad_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr11__ds0    :  1,    //      0
    reg_pad_eb_addr11__ds1    :  1,    //      1
    reg_pad_eb_addr11__ds2    :  1,    //      2
    reg_pad_eb_addr11__ds3    :  1,    //      3
    reg_pad_eb_addr11__pd     :  1,    //      4
    reg_pad_eb_addr11__pu     :  1,    //      5
    reg_pad_eb_addr11__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr10__ds0    :  1,    //      8
    reg_pad_eb_addr10__ds1    :  1,    //      9
    reg_pad_eb_addr10__ds2    :  1,    //     10
    reg_pad_eb_addr10__ds3    :  1,    //     11
    reg_pad_eb_addr10__pd     :  1,    //     12
    reg_pad_eb_addr10__pu     :  1,    //     13
    reg_pad_eb_addr10__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr9__ds0     :  1,    //     16
    reg_pad_eb_addr9__ds1     :  1,    //     17
    reg_pad_eb_addr9__ds2     :  1,    //     18
    reg_pad_eb_addr9__ds3     :  1,    //     19
    reg_pad_eb_addr9__pd      :  1,    //     20
    reg_pad_eb_addr9__pu      :  1,    //     21
    reg_pad_eb_addr9__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr8__ds0     :  1,    //     24
    reg_pad_eb_addr8__ds1     :  1,    //     25
    reg_pad_eb_addr8__ds2     :  1,    //     26
    reg_pad_eb_addr8__ds3     :  1,    //     27
    reg_pad_eb_addr8__pd      :  1,    //     28
    reg_pad_eb_addr8__pu      :  1,    //     29
    reg_pad_eb_addr8__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4020    pad_cvi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr15__ds0    :  1,    //      0
    reg_pad_eb_addr15__ds1    :  1,    //      1
    reg_pad_eb_addr15__ds2    :  1,    //      2
    reg_pad_eb_addr15__ds3    :  1,    //      3
    reg_pad_eb_addr15__pd     :  1,    //      4
    reg_pad_eb_addr15__pu     :  1,    //      5
    reg_pad_eb_addr15__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr14__ds0    :  1,    //      8
    reg_pad_eb_addr14__ds1    :  1,    //      9
    reg_pad_eb_addr14__ds2    :  1,    //     10
    reg_pad_eb_addr14__ds3    :  1,    //     11
    reg_pad_eb_addr14__pd     :  1,    //     12
    reg_pad_eb_addr14__pu     :  1,    //     13
    reg_pad_eb_addr14__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr13__ds0    :  1,    //     16
    reg_pad_eb_addr13__ds1    :  1,    //     17
    reg_pad_eb_addr13__ds2    :  1,    //     18
    reg_pad_eb_addr13__ds3    :  1,    //     19
    reg_pad_eb_addr13__pd     :  1,    //     20
    reg_pad_eb_addr13__pu     :  1,    //     21
    reg_pad_eb_addr13__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr12__ds0    :  1,    //     24
    reg_pad_eb_addr12__ds1    :  1,    //     25
    reg_pad_eb_addr12__ds2    :  1,    //     26
    reg_pad_eb_addr12__ds3    :  1,    //     27
    reg_pad_eb_addr12__pd     :  1,    //     28
    reg_pad_eb_addr12__pu     :  1,    //     29
    reg_pad_eb_addr12__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4024    pad_cvi09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data3__ds0     :  1,    //      0
    reg_pad_eb_data3__ds1     :  1,    //      1
    reg_pad_eb_data3__ds2     :  1,    //      2
    reg_pad_eb_data3__ds3     :  1,    //      3
    reg_pad_eb_data3__pd      :  1,    //      4
    reg_pad_eb_data3__pu      :  1,    //      5
    reg_pad_eb_data3__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data2__ds0     :  1,    //      8
    reg_pad_eb_data2__ds1     :  1,    //      9
    reg_pad_eb_data2__ds2     :  1,    //     10
    reg_pad_eb_data2__ds3     :  1,    //     11
    reg_pad_eb_data2__pd      :  1,    //     12
    reg_pad_eb_data2__pu      :  1,    //     13
    reg_pad_eb_data2__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data1__ds0     :  1,    //     16
    reg_pad_eb_data1__ds1     :  1,    //     17
    reg_pad_eb_data1__ds2     :  1,    //     18
    reg_pad_eb_data1__ds3     :  1,    //     19
    reg_pad_eb_data1__pd      :  1,    //     20
    reg_pad_eb_data1__pu      :  1,    //     21
    reg_pad_eb_data1__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data0__ds0     :  1,    //     24
    reg_pad_eb_data0__ds1     :  1,    //     25
    reg_pad_eb_data0__ds2     :  1,    //     26
    reg_pad_eb_data0__ds3     :  1,    //     27
    reg_pad_eb_data0__pd      :  1,    //     28
    reg_pad_eb_data0__pu      :  1,    //     29
    reg_pad_eb_data0__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4028    pad_cvi10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data7__ds0     :  1,    //      0
    reg_pad_eb_data7__ds1     :  1,    //      1
    reg_pad_eb_data7__ds2     :  1,    //      2
    reg_pad_eb_data7__ds3     :  1,    //      3
    reg_pad_eb_data7__pd      :  1,    //      4
    reg_pad_eb_data7__pu      :  1,    //      5
    reg_pad_eb_data7__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data6__ds0     :  1,    //      8
    reg_pad_eb_data6__ds1     :  1,    //      9
    reg_pad_eb_data6__ds2     :  1,    //     10
    reg_pad_eb_data6__ds3     :  1,    //     11
    reg_pad_eb_data6__pd      :  1,    //     12
    reg_pad_eb_data6__pu      :  1,    //     13
    reg_pad_eb_data6__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data5__ds0     :  1,    //     16
    reg_pad_eb_data5__ds1     :  1,    //     17
    reg_pad_eb_data5__ds2     :  1,    //     18
    reg_pad_eb_data5__ds3     :  1,    //     19
    reg_pad_eb_data5__pd      :  1,    //     20
    reg_pad_eb_data5__pu      :  1,    //     21
    reg_pad_eb_data5__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data4__ds0     :  1,    //     24
    reg_pad_eb_data4__ds1     :  1,    //     25
    reg_pad_eb_data4__ds2     :  1,    //     26
    reg_pad_eb_data4__ds3     :  1,    //     27
    reg_pad_eb_data4__pd      :  1,    //     28
    reg_pad_eb_data4__pu      :  1,    //     29
    reg_pad_eb_data4__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_402C    pad_cvi11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_rst__ds0       :  1,    //      0
    reg_pad_sc_rst__ds1       :  1,    //      1
    reg_pad_sc_rst__ds2       :  1,    //      2
    reg_pad_sc_rst__ds3       :  1,    //      3
    reg_pad_sc_rst__pd        :  1,    //      4
    reg_pad_sc_rst__pu        :  1,    //      5
    reg_pad_sc_rst__st        :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sc_detect__ds0    :  1,    //      8
    reg_pad_sc_detect__ds1    :  1,    //      9
    reg_pad_sc_detect__ds2    :  1,    //     10
    reg_pad_sc_detect__ds3    :  1,    //     11
    reg_pad_sc_detect__pd     :  1,    //     12
    reg_pad_sc_detect__pu     :  1,    //     13
    reg_pad_sc_detect__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sc_data__ds0      :  1,    //     16
    reg_pad_sc_data__ds1      :  1,    //     17
    reg_pad_sc_data__ds2      :  1,    //     18
    reg_pad_sc_data__ds3      :  1,    //     19
    reg_pad_sc_data__pd       :  1,    //     20
    reg_pad_sc_data__pu       :  1,    //     21
    reg_pad_sc_data__st       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sc_clk_out__ds0   :  1,    //     24
    reg_pad_sc_clk_out__ds1   :  1,    //     25
    reg_pad_sc_clk_out__ds2   :  1,    //     26
    reg_pad_sc_clk_out__ds3   :  1,    //     27
    reg_pad_sc_clk_out__pd    :  1,    //     28
    reg_pad_sc_clk_out__pu    :  1,    //     29
    reg_pad_sc_clk_out__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4030    pad_cvi12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ce2_n__ds0    :  1,    //      0
    reg_pad_cam_ce2_n__ds1    :  1,    //      1
    reg_pad_cam_ce2_n__ds2    :  1,    //      2
    reg_pad_cam_ce2_n__ds3    :  1,    //      3
    reg_pad_cam_ce2_n__pd     :  1,    //      4
    reg_pad_cam_ce2_n__pu     :  1,    //      5
    reg_pad_cam_ce2_n__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_ce1_n__ds0    :  1,    //      8
    reg_pad_cam_ce1_n__ds1    :  1,    //      9
    reg_pad_cam_ce1_n__ds2    :  1,    //     10
    reg_pad_cam_ce1_n__ds3    :  1,    //     11
    reg_pad_cam_ce1_n__pd     :  1,    //     12
    reg_pad_cam_ce1_n__pu     :  1,    //     13
    reg_pad_cam_ce1_n__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sc_vccen__ds0     :  1,    //     16
    reg_pad_sc_vccen__ds1     :  1,    //     17
    reg_pad_sc_vccen__ds2     :  1,    //     18
    reg_pad_sc_vccen__ds3     :  1,    //     19
    reg_pad_sc_vccen__pd      :  1,    //     20
    reg_pad_sc_vccen__pu      :  1,    //     21
    reg_pad_sc_vccen__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sc_vcc_sel__ds0   :  1,    //     24
    reg_pad_sc_vcc_sel__ds1   :  1,    //     25
    reg_pad_sc_vcc_sel__ds2   :  1,    //     26
    reg_pad_sc_vcc_sel__ds3   :  1,    //     27
    reg_pad_sc_vcc_sel__pd    :  1,    //     28
    reg_pad_sc_vcc_sel__pu    :  1,    //     29
    reg_pad_sc_vcc_sel__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4034    pad_cvi13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reg_n__ds0    :  1,    //      0
    reg_pad_cam_reg_n__ds1    :  1,    //      1
    reg_pad_cam_reg_n__ds2    :  1,    //      2
    reg_pad_cam_reg_n__ds3    :  1,    //      3
    reg_pad_cam_reg_n__pd     :  1,    //      4
    reg_pad_cam_reg_n__pu     :  1,    //      5
    reg_pad_cam_reg_n__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_ireq_n__ds0   :  1,    //      8
    reg_pad_cam_ireq_n__ds1   :  1,    //      9
    reg_pad_cam_ireq_n__ds2   :  1,    //     10
    reg_pad_cam_ireq_n__ds3   :  1,    //     11
    reg_pad_cam_ireq_n__pd    :  1,    //     12
    reg_pad_cam_ireq_n__pu    :  1,    //     13
    reg_pad_cam_ireq_n__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_cam_cd2_n__ds0    :  1,    //     16
    reg_pad_cam_cd2_n__ds1    :  1,    //     17
    reg_pad_cam_cd2_n__ds2    :  1,    //     18
    reg_pad_cam_cd2_n__ds3    :  1,    //     19
    reg_pad_cam_cd2_n__pd     :  1,    //     20
    reg_pad_cam_cd2_n__pu     :  1,    //     21
    reg_pad_cam_cd2_n__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_cam_cd1_n__ds0    :  1,    //     24
    reg_pad_cam_cd1_n__ds1    :  1,    //     25
    reg_pad_cam_cd1_n__ds2    :  1,    //     26
    reg_pad_cam_cd1_n__ds3    :  1,    //     27
    reg_pad_cam_cd1_n__pd     :  1,    //     28
    reg_pad_cam_cd1_n__pu     :  1,    //     29
    reg_pad_cam_cd1_n__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_CVI_PAD_CVI13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4038    pad_cvi14 ''
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
                              :  9;    //  31:23 reserved
}FUNC_IOMUX_CVI_PAD_CVI14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4100    pad_cvi64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data4_cam_mux_sel: 4,    //  3:0
    reg_pad_tpo_data3_cam_mux_sel: 4,    //  7:4
    reg_pad_tpo_data2_cam_mux_sel: 4,    //  11:8
    reg_pad_tpo_data1_cam_mux_sel: 4,    //  15:12
    reg_pad_tpo_data0_cam_mux_sel: 4,    //  19:16
    reg_pad_tpo_val_cam_mux_sel: 4,    //  23:20
    reg_pad_tpo_sop_cam_mux_sel: 4,    //  27:24
    reg_pad_tpo_clk_cam_mux_sel: 4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4104    pad_cvi65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_oe_n_mux_sel   :  4,    //   3: 0
    reg_pad_eb_cs3_mux_sel    :  4,    //   7: 4
    reg_pad_eb_cs2_mux_sel    :  4,    //  11: 8
    reg_pad_eb_cs1_mux_sel    :  4,    //  15:12
    reg_pad_eb_cs0_mux_sel    :  4,    //  19:16
    reg_pad_tpo_data7_cam_mux_sel: 4,    //  23:20
    reg_pad_tpo_data6_cam_mux_sel: 4,    //  27:24
    reg_pad_tpo_data5_cam_mux_sel: 4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4108    pad_cvi66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr3_mux_sel  :  4,    //   3: 0
    reg_pad_eb_addr2_mux_sel  :  4,    //   7: 4
    reg_pad_eb_addr1_mux_sel  :  4,    //  11: 8
    reg_pad_eb_addr0_mux_sel  :  4,    //  15:12
    reg_pad_eb_be_n1_mux_sel  :  4,    //  19:16
    reg_pad_eb_be_n0_mux_sel  :  4,    //  23:20
    reg_pad_eb_wait_mux_sel   :  4,    //  27:24
    reg_pad_eb_we_n_mux_sel   :  4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_410C    pad_cvi67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr11_mux_sel :  4,    //   3: 0
    reg_pad_eb_addr10_mux_sel :  4,    //   7: 4
    reg_pad_eb_addr9_mux_sel  :  4,    //  11: 8
    reg_pad_eb_addr8_mux_sel  :  4,    //  15:12
    reg_pad_eb_addr7_mux_sel  :  4,    //  19:16
    reg_pad_eb_addr6_mux_sel  :  4,    //  23:20
    reg_pad_eb_addr5_mux_sel  :  4,    //  27:24
    reg_pad_eb_addr4_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4110    pad_cvi68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data3_mux_sel  :  4,    //   3: 0
    reg_pad_eb_data2_mux_sel  :  4,    //   7: 4
    reg_pad_eb_data1_mux_sel  :  4,    //  11: 8
    reg_pad_eb_data0_mux_sel  :  4,    //  15:12
    reg_pad_eb_addr15_mux_sel :  4,    //  19:16
    reg_pad_eb_addr14_mux_sel :  4,    //  23:20
    reg_pad_eb_addr13_mux_sel :  4,    //  27:24
    reg_pad_eb_addr12_mux_sel :  4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4114    pad_cvi69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_rst_mux_sel    :  4,    //   3: 0
    reg_pad_sc_detect_mux_sel :  4,    //   7: 4
    reg_pad_sc_data_mux_sel   :  4,    //  11: 8
    reg_pad_sc_clk_out_mux_sel:  4,    //  15:12
    reg_pad_eb_data7_mux_sel  :  4,    //  19:16
    reg_pad_eb_data6_mux_sel  :  4,    //  23:20
    reg_pad_eb_data5_mux_sel  :  4,    //  27:24
    reg_pad_eb_data4_mux_sel  :  4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4118    pad_cvi70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reg_n_mux_sel :  4,    //   3: 0
    reg_pad_cam_ireq_n_mux_sel:  4,    //   7: 4
    reg_pad_cam_cd2_n_mux_sel :  4,    //  11: 8
    reg_pad_cam_cd1_n_mux_sel :  4,    //  15:12
    reg_pad_cam_ce2_n_mux_sel :  4,    //  19:16
    reg_pad_cam_ce1_n_mux_sel :  4,    //  23:20
    reg_pad_sc_vccen_mux_sel  :  4,    //  27:24
    reg_pad_sc_vcc_sel_mux_sel:  4;    //  31:28
}FUNC_IOMUX_CVI_PAD_CVI70_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_411C    pad_cvi71 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reset_mux_sel :  4,    //   3: 0
    reg_pad_cam_vccen_n_mux_sel: 4,    //   7: 4
    reg_pad_cam_wait_n_mux_sel:  4,    //  11: 8
                              : 20;    //  31:12 reserved
}FUNC_IOMUX_CVI_PAD_CVI71_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_CVI_PAD_CVI00_O22A0_T          pad_cvi00  ;             // 0xCC87_4000
    FUNC_IOMUX_CVI_PAD_CVI01_O22A0_T          pad_cvi01  ;             // 0xCC87_4004
    FUNC_IOMUX_CVI_PAD_CVI02_O22A0_T          pad_cvi02  ;             // 0xCC87_4008
    FUNC_IOMUX_CVI_PAD_CVI03_O22A0_T          pad_cvi03  ;             // 0xCC87_400C
    FUNC_IOMUX_CVI_PAD_CVI04_O22A0_T          pad_cvi04  ;             // 0xCC87_4010
    FUNC_IOMUX_CVI_PAD_CVI05_O22A0_T          pad_cvi05  ;             // 0xCC87_4014
    FUNC_IOMUX_CVI_PAD_CVI06_O22A0_T          pad_cvi06  ;             // 0xCC87_4018
    FUNC_IOMUX_CVI_PAD_CVI07_O22A0_T          pad_cvi07  ;             // 0xCC87_401C
    FUNC_IOMUX_CVI_PAD_CVI08_O22A0_T          pad_cvi08  ;             // 0xCC87_4020
    FUNC_IOMUX_CVI_PAD_CVI09_O22A0_T          pad_cvi09  ;             // 0xCC87_4024
    FUNC_IOMUX_CVI_PAD_CVI10_O22A0_T          pad_cvi10  ;             // 0xCC87_4028
    FUNC_IOMUX_CVI_PAD_CVI11_O22A0_T          pad_cvi11  ;             // 0xCC87_402C
    FUNC_IOMUX_CVI_PAD_CVI12_O22A0_T          pad_cvi12  ;             // 0xCC87_4030
    FUNC_IOMUX_CVI_PAD_CVI13_O22A0_T          pad_cvi13  ;             // 0xCC87_4034
    FUNC_IOMUX_CVI_PAD_CVI14_O22A0_T          pad_cvi14  ;             // 0xCC87_4038
    UINT32                             _rsvd_00[49];            // 0xCC87_403C ~ 0xCC87_40FC
    FUNC_IOMUX_CVI_PAD_CVI64_O22A0_T          pad_cvi64  ;             // 0xCC87_4100
    FUNC_IOMUX_CVI_PAD_CVI65_O22A0_T          pad_cvi65  ;             // 0xCC87_4104
    FUNC_IOMUX_CVI_PAD_CVI66_O22A0_T          pad_cvi66  ;             // 0xCC87_4108
    FUNC_IOMUX_CVI_PAD_CVI67_O22A0_T          pad_cvi67  ;             // 0xCC87_410C
    FUNC_IOMUX_CVI_PAD_CVI68_O22A0_T          pad_cvi68  ;             // 0xCC87_4110
    FUNC_IOMUX_CVI_PAD_CVI69_O22A0_T          pad_cvi69  ;             // 0xCC87_4114
    FUNC_IOMUX_CVI_PAD_CVI70_O22A0_T          pad_cvi70  ;             // 0xCC87_4118
    FUNC_IOMUX_CVI_PAD_CVI71_O22A0_T          pad_cvi71  ;             // 0xCC87_411C
}FUNC_IOMUX_CVI_REG_O22A0_T;
/* 23 regs */

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

#define FUNC_IOMUX_CVI_PAD_CVI00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define FUNC_IOMUX_CVI_PAD_CVI01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define FUNC_IOMUX_CVI_PAD_CVI02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define FUNC_IOMUX_CVI_PAD_CVI03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define FUNC_IOMUX_CVI_PAD_CVI04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define FUNC_IOMUX_CVI_PAD_CVI05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define FUNC_IOMUX_CVI_PAD_CVI06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define FUNC_IOMUX_CVI_PAD_CVI07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define FUNC_IOMUX_CVI_PAD_CVI08_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define FUNC_IOMUX_CVI_PAD_CVI09_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define FUNC_IOMUX_CVI_PAD_CVI10_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define FUNC_IOMUX_CVI_PAD_CVI11_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define FUNC_IOMUX_CVI_PAD_CVI12_O22A0_T_OFF                       (BASEADDRESS+0x0030)
#define FUNC_IOMUX_CVI_PAD_CVI13_O22A0_T_OFF                       (BASEADDRESS+0x0034)
#define FUNC_IOMUX_CVI_PAD_CVI14_O22A0_T_OFF                       (BASEADDRESS+0x0038)
#define FUNC_IOMUX_CVI_PAD_CVI64_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define FUNC_IOMUX_CVI_PAD_CVI65_O22A0_T_OFF                       (BASEADDRESS+0x0104)
#define FUNC_IOMUX_CVI_PAD_CVI66_O22A0_T_OFF                       (BASEADDRESS+0x0108)
#define FUNC_IOMUX_CVI_PAD_CVI67_O22A0_T_OFF                       (BASEADDRESS+0x010C)
#define FUNC_IOMUX_CVI_PAD_CVI68_O22A0_T_OFF                       (BASEADDRESS+0x0110)
#define FUNC_IOMUX_CVI_PAD_CVI69_O22A0_T_OFF                       (BASEADDRESS+0x0114)
#define FUNC_IOMUX_CVI_PAD_CVI70_O22A0_T_OFF                       (BASEADDRESS+0x0118)
#define FUNC_IOMUX_CVI_PAD_CVI71_O22A0_T_OFF                       (BASEADDRESS+0x011C)

/*-----------------------------------------------------------------------------------------
    0xCC87_4000    pad_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data0_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpo_data0_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpo_data0_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpo_data0_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpo_data0_cam__pd: 1;    //  4
    UINT32 reg_pad_tpo_data0_cam__pu: 1;    //  5
    UINT32 reg_pad_tpo_data0_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpo_val_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpo_val_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpo_val_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpo_val_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpo_val_cam__pd: 1;    //  12
    UINT32 reg_pad_tpo_val_cam__pu: 1;    //  13
    UINT32 reg_pad_tpo_val_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_sop_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_sop_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_sop_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_sop_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_sop_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_sop_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_sop_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_clk_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_clk_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_clk_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_clk_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_clk_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_clk_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_clk_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4004    pad_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data4_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpo_data4_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpo_data4_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpo_data4_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpo_data4_cam__pd: 1;    //  4
    UINT32 reg_pad_tpo_data4_cam__pu: 1;    //  5
    UINT32 reg_pad_tpo_data4_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpo_data3_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpo_data3_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpo_data3_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpo_data3_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpo_data3_cam__pd: 1;    //  12
    UINT32 reg_pad_tpo_data3_cam__pu: 1;    //  13
    UINT32 reg_pad_tpo_data3_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_data2_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_data2_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_data2_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_data2_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_data2_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_data2_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_data2_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_data1_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_data1_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_data1_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_data1_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_data1_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_data1_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_data1_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4008    pad_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_cs0__ds0:  1;    //      0
    UINT32 reg_pad_eb_cs0__ds1:  1;    //      1
    UINT32 reg_pad_eb_cs0__ds2:  1;    //      2
    UINT32 reg_pad_eb_cs0__ds3:  1;    //      3
    UINT32 reg_pad_eb_cs0__pd :  1;    //      4
    UINT32 reg_pad_eb_cs0__pu :  1;    //      5
    UINT32 reg_pad_eb_cs0__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpo_data7_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpo_data7_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpo_data7_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpo_data7_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpo_data7_cam__pd: 1;    //  12
    UINT32 reg_pad_tpo_data7_cam__pu: 1;    //  13
    UINT32 reg_pad_tpo_data7_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpo_data6_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpo_data6_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpo_data6_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpo_data6_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpo_data6_cam__pd: 1;    //  20
    UINT32 reg_pad_tpo_data6_cam__pu: 1;    //  21
    UINT32 reg_pad_tpo_data6_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpo_data5_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpo_data5_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpo_data5_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpo_data5_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpo_data5_cam__pd: 1;    //  28
    UINT32 reg_pad_tpo_data5_cam__pu: 1;    //  29
    UINT32 reg_pad_tpo_data5_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_400C    pad_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_oe_n__ds0: 1;    //      0
    UINT32 reg_pad_eb_oe_n__ds1: 1;    //      1
    UINT32 reg_pad_eb_oe_n__ds2: 1;    //      2
    UINT32 reg_pad_eb_oe_n__ds3: 1;    //      3
    UINT32 reg_pad_eb_oe_n__pd:  1;    //      4
    UINT32 reg_pad_eb_oe_n__pu:  1;    //      5
    UINT32 reg_pad_eb_oe_n__st:  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_cs3__ds0:  1;    //      8
    UINT32 reg_pad_eb_cs3__ds1:  1;    //      9
    UINT32 reg_pad_eb_cs3__ds2:  1;    //     10
    UINT32 reg_pad_eb_cs3__ds3:  1;    //     11
    UINT32 reg_pad_eb_cs3__pd :  1;    //     12
    UINT32 reg_pad_eb_cs3__pu :  1;    //     13
    UINT32 reg_pad_eb_cs3__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_cs2__ds0:  1;    //     16
    UINT32 reg_pad_eb_cs2__ds1:  1;    //     17
    UINT32 reg_pad_eb_cs2__ds2:  1;    //     18
    UINT32 reg_pad_eb_cs2__ds3:  1;    //     19
    UINT32 reg_pad_eb_cs2__pd :  1;    //     20
    UINT32 reg_pad_eb_cs2__pu :  1;    //     21
    UINT32 reg_pad_eb_cs2__st :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_cs1__ds0:  1;    //     24
    UINT32 reg_pad_eb_cs1__ds1:  1;    //     25
    UINT32 reg_pad_eb_cs1__ds2:  1;    //     26
    UINT32 reg_pad_eb_cs1__ds3:  1;    //     27
    UINT32 reg_pad_eb_cs1__pd :  1;    //     28
    UINT32 reg_pad_eb_cs1__pu :  1;    //     29
    UINT32 reg_pad_eb_cs1__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4010    pad_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_be_n1__ds0: 1;    //     0
    UINT32 reg_pad_eb_be_n1__ds1: 1;    //     1
    UINT32 reg_pad_eb_be_n1__ds2: 1;    //     2
    UINT32 reg_pad_eb_be_n1__ds3: 1;    //     3
    UINT32 reg_pad_eb_be_n1__pd: 1;    //      4
    UINT32 reg_pad_eb_be_n1__pu: 1;    //      5
    UINT32 reg_pad_eb_be_n1__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_be_n0__ds0: 1;    //     8
    UINT32 reg_pad_eb_be_n0__ds1: 1;    //     9
    UINT32 reg_pad_eb_be_n0__ds2: 1;    //    10
    UINT32 reg_pad_eb_be_n0__ds3: 1;    //    11
    UINT32 reg_pad_eb_be_n0__pd: 1;    //     12
    UINT32 reg_pad_eb_be_n0__pu: 1;    //     13
    UINT32 reg_pad_eb_be_n0__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_wait__ds0: 1;    //     16
    UINT32 reg_pad_eb_wait__ds1: 1;    //     17
    UINT32 reg_pad_eb_wait__ds2: 1;    //     18
    UINT32 reg_pad_eb_wait__ds3: 1;    //     19
    UINT32 reg_pad_eb_wait__pd:  1;    //     20
    UINT32 reg_pad_eb_wait__pu:  1;    //     21
    UINT32 reg_pad_eb_wait__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_we_n__ds0: 1;    //     24
    UINT32 reg_pad_eb_we_n__ds1: 1;    //     25
    UINT32 reg_pad_eb_we_n__ds2: 1;    //     26
    UINT32 reg_pad_eb_we_n__ds3: 1;    //     27
    UINT32 reg_pad_eb_we_n__pd:  1;    //     28
    UINT32 reg_pad_eb_we_n__pu:  1;    //     29
    UINT32 reg_pad_eb_we_n__st:  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4014    pad_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr3__ds0: 1;    //     0
    UINT32 reg_pad_eb_addr3__ds1: 1;    //     1
    UINT32 reg_pad_eb_addr3__ds2: 1;    //     2
    UINT32 reg_pad_eb_addr3__ds3: 1;    //     3
    UINT32 reg_pad_eb_addr3__pd: 1;    //      4
    UINT32 reg_pad_eb_addr3__pu: 1;    //      5
    UINT32 reg_pad_eb_addr3__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr2__ds0: 1;    //     8
    UINT32 reg_pad_eb_addr2__ds1: 1;    //     9
    UINT32 reg_pad_eb_addr2__ds2: 1;    //    10
    UINT32 reg_pad_eb_addr2__ds3: 1;    //    11
    UINT32 reg_pad_eb_addr2__pd: 1;    //     12
    UINT32 reg_pad_eb_addr2__pu: 1;    //     13
    UINT32 reg_pad_eb_addr2__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr1__ds0: 1;    //    16
    UINT32 reg_pad_eb_addr1__ds1: 1;    //    17
    UINT32 reg_pad_eb_addr1__ds2: 1;    //    18
    UINT32 reg_pad_eb_addr1__ds3: 1;    //    19
    UINT32 reg_pad_eb_addr1__pd: 1;    //     20
    UINT32 reg_pad_eb_addr1__pu: 1;    //     21
    UINT32 reg_pad_eb_addr1__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr0__ds0: 1;    //    24
    UINT32 reg_pad_eb_addr0__ds1: 1;    //    25
    UINT32 reg_pad_eb_addr0__ds2: 1;    //    26
    UINT32 reg_pad_eb_addr0__ds3: 1;    //    27
    UINT32 reg_pad_eb_addr0__pd: 1;    //     28
    UINT32 reg_pad_eb_addr0__pu: 1;    //     29
    UINT32 reg_pad_eb_addr0__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4018    pad_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr7__ds0: 1;    //     0
    UINT32 reg_pad_eb_addr7__ds1: 1;    //     1
    UINT32 reg_pad_eb_addr7__ds2: 1;    //     2
    UINT32 reg_pad_eb_addr7__ds3: 1;    //     3
    UINT32 reg_pad_eb_addr7__pd: 1;    //      4
    UINT32 reg_pad_eb_addr7__pu: 1;    //      5
    UINT32 reg_pad_eb_addr7__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr6__ds0: 1;    //     8
    UINT32 reg_pad_eb_addr6__ds1: 1;    //     9
    UINT32 reg_pad_eb_addr6__ds2: 1;    //    10
    UINT32 reg_pad_eb_addr6__ds3: 1;    //    11
    UINT32 reg_pad_eb_addr6__pd: 1;    //     12
    UINT32 reg_pad_eb_addr6__pu: 1;    //     13
    UINT32 reg_pad_eb_addr6__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr5__ds0: 1;    //    16
    UINT32 reg_pad_eb_addr5__ds1: 1;    //    17
    UINT32 reg_pad_eb_addr5__ds2: 1;    //    18
    UINT32 reg_pad_eb_addr5__ds3: 1;    //    19
    UINT32 reg_pad_eb_addr5__pd: 1;    //     20
    UINT32 reg_pad_eb_addr5__pu: 1;    //     21
    UINT32 reg_pad_eb_addr5__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr4__ds0: 1;    //    24
    UINT32 reg_pad_eb_addr4__ds1: 1;    //    25
    UINT32 reg_pad_eb_addr4__ds2: 1;    //    26
    UINT32 reg_pad_eb_addr4__ds3: 1;    //    27
    UINT32 reg_pad_eb_addr4__pd: 1;    //     28
    UINT32 reg_pad_eb_addr4__pu: 1;    //     29
    UINT32 reg_pad_eb_addr4__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_401C    pad_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr11__ds0: 1;    //    0
    UINT32 reg_pad_eb_addr11__ds1: 1;    //    1
    UINT32 reg_pad_eb_addr11__ds2: 1;    //    2
    UINT32 reg_pad_eb_addr11__ds3: 1;    //    3
    UINT32 reg_pad_eb_addr11__pd: 1;    //     4
    UINT32 reg_pad_eb_addr11__pu: 1;    //     5
    UINT32 reg_pad_eb_addr11__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr10__ds0: 1;    //    8
    UINT32 reg_pad_eb_addr10__ds1: 1;    //    9
    UINT32 reg_pad_eb_addr10__ds2: 1;    //   10
    UINT32 reg_pad_eb_addr10__ds3: 1;    //   11
    UINT32 reg_pad_eb_addr10__pd: 1;    //    12
    UINT32 reg_pad_eb_addr10__pu: 1;    //    13
    UINT32 reg_pad_eb_addr10__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr9__ds0: 1;    //    16
    UINT32 reg_pad_eb_addr9__ds1: 1;    //    17
    UINT32 reg_pad_eb_addr9__ds2: 1;    //    18
    UINT32 reg_pad_eb_addr9__ds3: 1;    //    19
    UINT32 reg_pad_eb_addr9__pd: 1;    //     20
    UINT32 reg_pad_eb_addr9__pu: 1;    //     21
    UINT32 reg_pad_eb_addr9__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr8__ds0: 1;    //    24
    UINT32 reg_pad_eb_addr8__ds1: 1;    //    25
    UINT32 reg_pad_eb_addr8__ds2: 1;    //    26
    UINT32 reg_pad_eb_addr8__ds3: 1;    //    27
    UINT32 reg_pad_eb_addr8__pd: 1;    //     28
    UINT32 reg_pad_eb_addr8__pu: 1;    //     29
    UINT32 reg_pad_eb_addr8__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4020    pad_cvi08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr15__ds0: 1;    //    0
    UINT32 reg_pad_eb_addr15__ds1: 1;    //    1
    UINT32 reg_pad_eb_addr15__ds2: 1;    //    2
    UINT32 reg_pad_eb_addr15__ds3: 1;    //    3
    UINT32 reg_pad_eb_addr15__pd: 1;    //     4
    UINT32 reg_pad_eb_addr15__pu: 1;    //     5
    UINT32 reg_pad_eb_addr15__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_addr14__ds0: 1;    //    8
    UINT32 reg_pad_eb_addr14__ds1: 1;    //    9
    UINT32 reg_pad_eb_addr14__ds2: 1;    //   10
    UINT32 reg_pad_eb_addr14__ds3: 1;    //   11
    UINT32 reg_pad_eb_addr14__pd: 1;    //    12
    UINT32 reg_pad_eb_addr14__pu: 1;    //    13
    UINT32 reg_pad_eb_addr14__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_addr13__ds0: 1;    //   16
    UINT32 reg_pad_eb_addr13__ds1: 1;    //   17
    UINT32 reg_pad_eb_addr13__ds2: 1;    //   18
    UINT32 reg_pad_eb_addr13__ds3: 1;    //   19
    UINT32 reg_pad_eb_addr13__pd: 1;    //    20
    UINT32 reg_pad_eb_addr13__pu: 1;    //    21
    UINT32 reg_pad_eb_addr13__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_addr12__ds0: 1;    //   24
    UINT32 reg_pad_eb_addr12__ds1: 1;    //   25
    UINT32 reg_pad_eb_addr12__ds2: 1;    //   26
    UINT32 reg_pad_eb_addr12__ds3: 1;    //   27
    UINT32 reg_pad_eb_addr12__pd: 1;    //    28
    UINT32 reg_pad_eb_addr12__pu: 1;    //    29
    UINT32 reg_pad_eb_addr12__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4024    pad_cvi09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data3__ds0: 1;    //     0
    UINT32 reg_pad_eb_data3__ds1: 1;    //     1
    UINT32 reg_pad_eb_data3__ds2: 1;    //     2
    UINT32 reg_pad_eb_data3__ds3: 1;    //     3
    UINT32 reg_pad_eb_data3__pd: 1;    //      4
    UINT32 reg_pad_eb_data3__pu: 1;    //      5
    UINT32 reg_pad_eb_data3__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_data2__ds0: 1;    //     8
    UINT32 reg_pad_eb_data2__ds1: 1;    //     9
    UINT32 reg_pad_eb_data2__ds2: 1;    //    10
    UINT32 reg_pad_eb_data2__ds3: 1;    //    11
    UINT32 reg_pad_eb_data2__pd: 1;    //     12
    UINT32 reg_pad_eb_data2__pu: 1;    //     13
    UINT32 reg_pad_eb_data2__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_data1__ds0: 1;    //    16
    UINT32 reg_pad_eb_data1__ds1: 1;    //    17
    UINT32 reg_pad_eb_data1__ds2: 1;    //    18
    UINT32 reg_pad_eb_data1__ds3: 1;    //    19
    UINT32 reg_pad_eb_data1__pd: 1;    //     20
    UINT32 reg_pad_eb_data1__pu: 1;    //     21
    UINT32 reg_pad_eb_data1__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_data0__ds0: 1;    //    24
    UINT32 reg_pad_eb_data0__ds1: 1;    //    25
    UINT32 reg_pad_eb_data0__ds2: 1;    //    26
    UINT32 reg_pad_eb_data0__ds3: 1;    //    27
    UINT32 reg_pad_eb_data0__pd: 1;    //     28
    UINT32 reg_pad_eb_data0__pu: 1;    //     29
    UINT32 reg_pad_eb_data0__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4028    pad_cvi10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data7__ds0: 1;    //     0
    UINT32 reg_pad_eb_data7__ds1: 1;    //     1
    UINT32 reg_pad_eb_data7__ds2: 1;    //     2
    UINT32 reg_pad_eb_data7__ds3: 1;    //     3
    UINT32 reg_pad_eb_data7__pd: 1;    //      4
    UINT32 reg_pad_eb_data7__pu: 1;    //      5
    UINT32 reg_pad_eb_data7__st: 1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_eb_data6__ds0: 1;    //     8
    UINT32 reg_pad_eb_data6__ds1: 1;    //     9
    UINT32 reg_pad_eb_data6__ds2: 1;    //    10
    UINT32 reg_pad_eb_data6__ds3: 1;    //    11
    UINT32 reg_pad_eb_data6__pd: 1;    //     12
    UINT32 reg_pad_eb_data6__pu: 1;    //     13
    UINT32 reg_pad_eb_data6__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_eb_data5__ds0: 1;    //    16
    UINT32 reg_pad_eb_data5__ds1: 1;    //    17
    UINT32 reg_pad_eb_data5__ds2: 1;    //    18
    UINT32 reg_pad_eb_data5__ds3: 1;    //    19
    UINT32 reg_pad_eb_data5__pd: 1;    //     20
    UINT32 reg_pad_eb_data5__pu: 1;    //     21
    UINT32 reg_pad_eb_data5__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_eb_data4__ds0: 1;    //    24
    UINT32 reg_pad_eb_data4__ds1: 1;    //    25
    UINT32 reg_pad_eb_data4__ds2: 1;    //    26
    UINT32 reg_pad_eb_data4__ds3: 1;    //    27
    UINT32 reg_pad_eb_data4__pd: 1;    //     28
    UINT32 reg_pad_eb_data4__pu: 1;    //     29
    UINT32 reg_pad_eb_data4__st: 1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_402C    pad_cvi11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sc_rst__ds0:  1;    //      0
    UINT32 reg_pad_sc_rst__ds1:  1;    //      1
    UINT32 reg_pad_sc_rst__ds2:  1;    //      2
    UINT32 reg_pad_sc_rst__ds3:  1;    //      3
    UINT32 reg_pad_sc_rst__pd :  1;    //      4
    UINT32 reg_pad_sc_rst__pu :  1;    //      5
    UINT32 reg_pad_sc_rst__st :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_sc_detect__ds0: 1;    //    8
    UINT32 reg_pad_sc_detect__ds1: 1;    //    9
    UINT32 reg_pad_sc_detect__ds2: 1;    //   10
    UINT32 reg_pad_sc_detect__ds3: 1;    //   11
    UINT32 reg_pad_sc_detect__pd: 1;    //    12
    UINT32 reg_pad_sc_detect__pu: 1;    //    13
    UINT32 reg_pad_sc_detect__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_sc_data__ds0: 1;    //     16
    UINT32 reg_pad_sc_data__ds1: 1;    //     17
    UINT32 reg_pad_sc_data__ds2: 1;    //     18
    UINT32 reg_pad_sc_data__ds3: 1;    //     19
    UINT32 reg_pad_sc_data__pd:  1;    //     20
    UINT32 reg_pad_sc_data__pu:  1;    //     21
    UINT32 reg_pad_sc_data__st:  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sc_clk_out__ds0: 1;    //  24
    UINT32 reg_pad_sc_clk_out__ds1: 1;    //  25
    UINT32 reg_pad_sc_clk_out__ds2: 1;    //  26
    UINT32 reg_pad_sc_clk_out__ds3: 1;    //  27
    UINT32 reg_pad_sc_clk_out__pd: 1;    //   28
    UINT32 reg_pad_sc_clk_out__pu: 1;    //   29
    UINT32 reg_pad_sc_clk_out__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4030    pad_cvi12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_ce2_n__ds0: 1;    //    0
    UINT32 reg_pad_cam_ce2_n__ds1: 1;    //    1
    UINT32 reg_pad_cam_ce2_n__ds2: 1;    //    2
    UINT32 reg_pad_cam_ce2_n__ds3: 1;    //    3
    UINT32 reg_pad_cam_ce2_n__pd: 1;    //     4
    UINT32 reg_pad_cam_ce2_n__pu: 1;    //     5
    UINT32 reg_pad_cam_ce2_n__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_cam_ce1_n__ds0: 1;    //    8
    UINT32 reg_pad_cam_ce1_n__ds1: 1;    //    9
    UINT32 reg_pad_cam_ce1_n__ds2: 1;    //   10
    UINT32 reg_pad_cam_ce1_n__ds3: 1;    //   11
    UINT32 reg_pad_cam_ce1_n__pd: 1;    //    12
    UINT32 reg_pad_cam_ce1_n__pu: 1;    //    13
    UINT32 reg_pad_cam_ce1_n__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_sc_vccen__ds0: 1;    //    16
    UINT32 reg_pad_sc_vccen__ds1: 1;    //    17
    UINT32 reg_pad_sc_vccen__ds2: 1;    //    18
    UINT32 reg_pad_sc_vccen__ds3: 1;    //    19
    UINT32 reg_pad_sc_vccen__pd: 1;    //     20
    UINT32 reg_pad_sc_vccen__pu: 1;    //     21
    UINT32 reg_pad_sc_vccen__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_sc_vcc_sel__ds0: 1;    //  24
    UINT32 reg_pad_sc_vcc_sel__ds1: 1;    //  25
    UINT32 reg_pad_sc_vcc_sel__ds2: 1;    //  26
    UINT32 reg_pad_sc_vcc_sel__ds3: 1;    //  27
    UINT32 reg_pad_sc_vcc_sel__pd: 1;    //   28
    UINT32 reg_pad_sc_vcc_sel__pu: 1;    //   29
    UINT32 reg_pad_sc_vcc_sel__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4034    pad_cvi13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_reg_n__ds0: 1;    //    0
    UINT32 reg_pad_cam_reg_n__ds1: 1;    //    1
    UINT32 reg_pad_cam_reg_n__ds2: 1;    //    2
    UINT32 reg_pad_cam_reg_n__ds3: 1;    //    3
    UINT32 reg_pad_cam_reg_n__pd: 1;    //     4
    UINT32 reg_pad_cam_reg_n__pu: 1;    //     5
    UINT32 reg_pad_cam_reg_n__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_cam_ireq_n__ds0: 1;    //   8
    UINT32 reg_pad_cam_ireq_n__ds1: 1;    //   9
    UINT32 reg_pad_cam_ireq_n__ds2: 1;    //  10
    UINT32 reg_pad_cam_ireq_n__ds3: 1;    //  11
    UINT32 reg_pad_cam_ireq_n__pd: 1;    //   12
    UINT32 reg_pad_cam_ireq_n__pu: 1;    //   13
    UINT32 reg_pad_cam_ireq_n__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_cam_cd2_n__ds0: 1;    //   16
    UINT32 reg_pad_cam_cd2_n__ds1: 1;    //   17
    UINT32 reg_pad_cam_cd2_n__ds2: 1;    //   18
    UINT32 reg_pad_cam_cd2_n__ds3: 1;    //   19
    UINT32 reg_pad_cam_cd2_n__pd: 1;    //    20
    UINT32 reg_pad_cam_cd2_n__pu: 1;    //    21
    UINT32 reg_pad_cam_cd2_n__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_cam_cd1_n__ds0: 1;    //   24
    UINT32 reg_pad_cam_cd1_n__ds1: 1;    //   25
    UINT32 reg_pad_cam_cd1_n__ds2: 1;    //   26
    UINT32 reg_pad_cam_cd1_n__ds3: 1;    //   27
    UINT32 reg_pad_cam_cd1_n__pd: 1;    //    28
    UINT32 reg_pad_cam_cd1_n__pu: 1;    //    29
    UINT32 reg_pad_cam_cd1_n__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4038    pad_cvi14 ''
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
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4100    pad_cvi64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data4_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpo_data3_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpo_data2_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpo_data1_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpo_data0_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpo_val_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpo_sop_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpo_clk_cam_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4104    pad_cvi65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_oe_n_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_cs3_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_cs2_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_cs1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_cs0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpo_data7_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpo_data6_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpo_data5_cam_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4108    pad_cvi66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr3_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_addr2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_addr1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_addr0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_be_n1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_be_n0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_wait_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_we_n_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_410C    pad_cvi67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_addr11_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_addr10_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_addr9_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_addr8_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_addr7_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_addr6_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_addr5_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_addr4_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI67_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4110    pad_cvi68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_eb_data3_mux_sel: 4;    //  3:0
    UINT32 reg_pad_eb_data2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_eb_data1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_eb_data0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_addr15_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_addr14_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_addr13_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_addr12_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI68_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4114    pad_cvi69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sc_rst_mux_sel: 4;    //  3:0
    UINT32 reg_pad_sc_detect_mux_sel: 4;    //  7:4
    UINT32 reg_pad_sc_data_mux_sel: 4;    //  11:8
    UINT32 reg_pad_sc_clk_out_mux_sel: 4;    //  15:12
    UINT32 reg_pad_eb_data7_mux_sel: 4;    //  19:16
    UINT32 reg_pad_eb_data6_mux_sel: 4;    //  23:20
    UINT32 reg_pad_eb_data5_mux_sel: 4;    //  27:24
    UINT32 reg_pad_eb_data4_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI69_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_4118    pad_cvi70 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_reg_n_mux_sel: 4;    //  3:0
    UINT32 reg_pad_cam_ireq_n_mux_sel: 4;    //  7:4
    UINT32 reg_pad_cam_cd2_n_mux_sel: 4;    //  11:8
    UINT32 reg_pad_cam_cd1_n_mux_sel: 4;    //  15:12
    UINT32 reg_pad_cam_ce2_n_mux_sel: 4;    //  19:16
    UINT32 reg_pad_cam_ce1_n_mux_sel: 4;    //  23:20
    UINT32 reg_pad_sc_vccen_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sc_vcc_sel_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_CVI_PAD_CVI70_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_411C    pad_cvi71 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_cam_reset_mux_sel: 4;    //  3:0
    UINT32 reg_pad_cam_vccen_n_mux_sel: 4;    //  7:4
    UINT32 reg_pad_cam_wait_n_mux_sel: 4;    //  11:8
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FUNC_IOMUX_CVI_PAD_CVI71_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_CVI_PAD_CVI00_O22A0_T          pad_cvi00  ;             // 0xCC87_4000
    FUNC_IOMUX_CVI_PAD_CVI01_O22A0_T          pad_cvi01  ;             // 0xCC87_4004
    FUNC_IOMUX_CVI_PAD_CVI02_O22A0_T          pad_cvi02  ;             // 0xCC87_4008
    FUNC_IOMUX_CVI_PAD_CVI03_O22A0_T          pad_cvi03  ;             // 0xCC87_400C
    FUNC_IOMUX_CVI_PAD_CVI04_O22A0_T          pad_cvi04  ;             // 0xCC87_4010
    FUNC_IOMUX_CVI_PAD_CVI05_O22A0_T          pad_cvi05  ;             // 0xCC87_4014
    FUNC_IOMUX_CVI_PAD_CVI06_O22A0_T          pad_cvi06  ;             // 0xCC87_4018
    FUNC_IOMUX_CVI_PAD_CVI07_O22A0_T          pad_cvi07  ;             // 0xCC87_401C
    FUNC_IOMUX_CVI_PAD_CVI08_O22A0_T          pad_cvi08  ;             // 0xCC87_4020
    FUNC_IOMUX_CVI_PAD_CVI09_O22A0_T          pad_cvi09  ;             // 0xCC87_4024
    FUNC_IOMUX_CVI_PAD_CVI10_O22A0_T          pad_cvi10  ;             // 0xCC87_4028
    FUNC_IOMUX_CVI_PAD_CVI11_O22A0_T          pad_cvi11  ;             // 0xCC87_402C
    FUNC_IOMUX_CVI_PAD_CVI12_O22A0_T          pad_cvi12  ;             // 0xCC87_4030
    FUNC_IOMUX_CVI_PAD_CVI13_O22A0_T          pad_cvi13  ;             // 0xCC87_4034
    FUNC_IOMUX_CVI_PAD_CVI14_O22A0_T          pad_cvi14  ;             // 0xCC87_4038
    UINT32                             _rsvd_00[49];            // 0xCC87_403C ~ 0xCC87_40FC
    FUNC_IOMUX_CVI_PAD_CVI64_O22A0_T          pad_cvi64  ;             // 0xCC87_4100
    FUNC_IOMUX_CVI_PAD_CVI65_O22A0_T          pad_cvi65  ;             // 0xCC87_4104
    FUNC_IOMUX_CVI_PAD_CVI66_O22A0_T          pad_cvi66  ;             // 0xCC87_4108
    FUNC_IOMUX_CVI_PAD_CVI67_O22A0_T          pad_cvi67  ;             // 0xCC87_410C
    FUNC_IOMUX_CVI_PAD_CVI68_O22A0_T          pad_cvi68  ;             // 0xCC87_4110
    FUNC_IOMUX_CVI_PAD_CVI69_O22A0_T          pad_cvi69  ;             // 0xCC87_4114
    FUNC_IOMUX_CVI_PAD_CVI70_O22A0_T          pad_cvi70  ;             // 0xCC87_4118
    FUNC_IOMUX_CVI_PAD_CVI71_O22A0_T          pad_cvi71  ;             // 0xCC87_411C
}FUNC_IOMUX_CVI_REG_O22A0_T;
/* 23 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_CVI_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

