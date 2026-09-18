#ifndef _CTOP_SYN_FMS_E60A0_REG_H_
#define _CTOP_SYN_FMS_E60A0_REG_H_

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
    0xC934_4400    crg_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_fms_ctrl          : 32;    //  31: 0
}CTOP_FMS_CRG_FMS000_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4404    crg_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_fms        :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FMS_CRG_FMS001_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4408    crg_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_cd1_n__st     :  1,    //      0
    reg_pad_cam_cd1_n__pu     :  1,    //      1
    reg_pad_cam_cd1_n__pd     :  1,    //      2
    reg_pad_cam_cd1_n__ds3    :  1,    //      3
    reg_pad_cam_cd1_n__ds2    :  1,    //      4
    reg_pad_cam_cd1_n__ds1    :  1,    //      5
    reg_pad_cam_cd1_n__ds0    :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_FMS_CRG_FMS002_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_440C    crg_fms003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_ireq_n__st    :  1,    //      0
    reg_pad_cam_ireq_n__pu    :  1,    //      1
    reg_pad_cam_ireq_n__pd    :  1,    //      2
    reg_pad_cam_ireq_n__ds3   :  1,    //      3
    reg_pad_cam_ireq_n__ds2   :  1,    //      4
    reg_pad_cam_ireq_n__ds1   :  1,    //      5
    reg_pad_cam_ireq_n__ds0   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_ce2_n__st     :  1,    //      8
    reg_pad_cam_ce2_n__pu     :  1,    //      9
    reg_pad_cam_ce2_n__pd     :  1,    //     10
    reg_pad_cam_ce2_n__ds3    :  1,    //     11
    reg_pad_cam_ce2_n__ds2    :  1,    //     12
    reg_pad_cam_ce2_n__ds1    :  1,    //     13
    reg_pad_cam_ce2_n__ds0    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_cam_ce1_n__st     :  1,    //     16
    reg_pad_cam_ce1_n__pu     :  1,    //     17
    reg_pad_cam_ce1_n__pd     :  1,    //     18
    reg_pad_cam_ce1_n__ds3    :  1,    //     19
    reg_pad_cam_ce1_n__ds2    :  1,    //     20
    reg_pad_cam_ce1_n__ds1    :  1,    //     21
    reg_pad_cam_ce1_n__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_cam_cd2_n__st     :  1,    //     24
    reg_pad_cam_cd2_n__pu     :  1,    //     25
    reg_pad_cam_cd2_n__pd     :  1,    //     26
    reg_pad_cam_cd2_n__ds3    :  1,    //     27
    reg_pad_cam_cd2_n__ds2    :  1,    //     28
    reg_pad_cam_cd2_n__ds1    :  1,    //     29
    reg_pad_cam_cd2_n__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS003_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4410    crg_fms004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_wait_n__st    :  1,    //      0
    reg_pad_cam_wait_n__pu    :  1,    //      1
    reg_pad_cam_wait_n__pd    :  1,    //      2
    reg_pad_cam_wait_n__ds3   :  1,    //      3
    reg_pad_cam_wait_n__ds2   :  1,    //      4
    reg_pad_cam_wait_n__ds1   :  1,    //      5
    reg_pad_cam_wait_n__ds0   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_cam_vccen_n__st   :  1,    //      8
    reg_pad_cam_vccen_n__pu   :  1,    //      9
    reg_pad_cam_vccen_n__pd   :  1,    //     10
    reg_pad_cam_vccen_n__ds3  :  1,    //     11
    reg_pad_cam_vccen_n__ds2  :  1,    //     12
    reg_pad_cam_vccen_n__ds1  :  1,    //     13
    reg_pad_cam_vccen_n__ds0  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_cam_reset__st     :  1,    //     16
    reg_pad_cam_reset__pu     :  1,    //     17
    reg_pad_cam_reset__pd     :  1,    //     18
    reg_pad_cam_reset__ds3    :  1,    //     19
    reg_pad_cam_reset__ds2    :  1,    //     20
    reg_pad_cam_reset__ds1    :  1,    //     21
    reg_pad_cam_reset__ds0    :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_FMS_CRG_FMS004_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4414    crg_fms005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr13__st     :  1,    //      0
    reg_pad_eb_addr13__pu     :  1,    //      1
    reg_pad_eb_addr13__pd     :  1,    //      2
    reg_pad_eb_addr13__ds3    :  1,    //      3
    reg_pad_eb_addr13__ds2    :  1,    //      4
    reg_pad_eb_addr13__ds1    :  1,    //      5
    reg_pad_eb_addr13__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr12__st     :  1,    //      8
    reg_pad_eb_addr12__pu     :  1,    //      9
    reg_pad_eb_addr12__pd     :  1,    //     10
    reg_pad_eb_addr12__ds3    :  1,    //     11
    reg_pad_eb_addr12__ds2    :  1,    //     12
    reg_pad_eb_addr12__ds1    :  1,    //     13
    reg_pad_eb_addr12__ds0    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr11__st     :  1,    //     16
    reg_pad_eb_addr11__pu     :  1,    //     17
    reg_pad_eb_addr11__pd     :  1,    //     18
    reg_pad_eb_addr11__ds3    :  1,    //     19
    reg_pad_eb_addr11__ds2    :  1,    //     20
    reg_pad_eb_addr11__ds1    :  1,    //     21
    reg_pad_eb_addr11__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr10__st     :  1,    //     24
    reg_pad_eb_addr10__pu     :  1,    //     25
    reg_pad_eb_addr10__pd     :  1,    //     26
    reg_pad_eb_addr10__ds3    :  1,    //     27
    reg_pad_eb_addr10__ds2    :  1,    //     28
    reg_pad_eb_addr10__ds1    :  1,    //     29
    reg_pad_eb_addr10__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS005_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4418    crg_fms006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data1__st      :  1,    //      0
    reg_pad_eb_data1__pu      :  1,    //      1
    reg_pad_eb_data1__pd      :  1,    //      2
    reg_pad_eb_data1__ds3     :  1,    //      3
    reg_pad_eb_data1__ds2     :  1,    //      4
    reg_pad_eb_data1__ds1     :  1,    //      5
    reg_pad_eb_data1__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data0__st      :  1,    //      8
    reg_pad_eb_data0__pu      :  1,    //      9
    reg_pad_eb_data0__pd      :  1,    //     10
    reg_pad_eb_data0__ds3     :  1,    //     11
    reg_pad_eb_data0__ds2     :  1,    //     12
    reg_pad_eb_data0__ds1     :  1,    //     13
    reg_pad_eb_data0__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr15__st     :  1,    //     16
    reg_pad_eb_addr15__pu     :  1,    //     17
    reg_pad_eb_addr15__pd     :  1,    //     18
    reg_pad_eb_addr15__ds3    :  1,    //     19
    reg_pad_eb_addr15__ds2    :  1,    //     20
    reg_pad_eb_addr15__ds1    :  1,    //     21
    reg_pad_eb_addr15__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr14__st     :  1,    //     24
    reg_pad_eb_addr14__pu     :  1,    //     25
    reg_pad_eb_addr14__pd     :  1,    //     26
    reg_pad_eb_addr14__ds3    :  1,    //     27
    reg_pad_eb_addr14__ds2    :  1,    //     28
    reg_pad_eb_addr14__ds1    :  1,    //     29
    reg_pad_eb_addr14__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS006_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_441C    crg_fms007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data5__st      :  1,    //      0
    reg_pad_eb_data5__pu      :  1,    //      1
    reg_pad_eb_data5__pd      :  1,    //      2
    reg_pad_eb_data5__ds3     :  1,    //      3
    reg_pad_eb_data5__ds2     :  1,    //      4
    reg_pad_eb_data5__ds1     :  1,    //      5
    reg_pad_eb_data5__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_data4__st      :  1,    //      8
    reg_pad_eb_data4__pu      :  1,    //      9
    reg_pad_eb_data4__pd      :  1,    //     10
    reg_pad_eb_data4__ds3     :  1,    //     11
    reg_pad_eb_data4__ds2     :  1,    //     12
    reg_pad_eb_data4__ds1     :  1,    //     13
    reg_pad_eb_data4__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data3__st      :  1,    //     16
    reg_pad_eb_data3__pu      :  1,    //     17
    reg_pad_eb_data3__pd      :  1,    //     18
    reg_pad_eb_data3__ds3     :  1,    //     19
    reg_pad_eb_data3__ds2     :  1,    //     20
    reg_pad_eb_data3__ds1     :  1,    //     21
    reg_pad_eb_data3__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data2__st      :  1,    //     24
    reg_pad_eb_data2__pu      :  1,    //     25
    reg_pad_eb_data2__pd      :  1,    //     26
    reg_pad_eb_data2__ds3     :  1,    //     27
    reg_pad_eb_data2__ds2     :  1,    //     28
    reg_pad_eb_data2__ds1     :  1,    //     29
    reg_pad_eb_data2__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS007_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4420    crg_fms008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_data__st       :  1,    //      0
    reg_pad_sc_data__pu       :  1,    //      1
    reg_pad_sc_data__pd       :  1,    //      2
    reg_pad_sc_data__ds3      :  1,    //      3
    reg_pad_sc_data__ds2      :  1,    //      4
    reg_pad_sc_data__ds1      :  1,    //      5
    reg_pad_sc_data__ds0      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sc_clk_out__st    :  1,    //      8
    reg_pad_sc_clk_out__pu    :  1,    //      9
    reg_pad_sc_clk_out__pd    :  1,    //     10
    reg_pad_sc_clk_out__ds3   :  1,    //     11
    reg_pad_sc_clk_out__ds2   :  1,    //     12
    reg_pad_sc_clk_out__ds1   :  1,    //     13
    reg_pad_sc_clk_out__ds0   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_data7__st      :  1,    //     16
    reg_pad_eb_data7__pu      :  1,    //     17
    reg_pad_eb_data7__pd      :  1,    //     18
    reg_pad_eb_data7__ds3     :  1,    //     19
    reg_pad_eb_data7__ds2     :  1,    //     20
    reg_pad_eb_data7__ds1     :  1,    //     21
    reg_pad_eb_data7__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_data6__st      :  1,    //     24
    reg_pad_eb_data6__pu      :  1,    //     25
    reg_pad_eb_data6__pd      :  1,    //     26
    reg_pad_eb_data6__ds3     :  1,    //     27
    reg_pad_eb_data6__ds2     :  1,    //     28
    reg_pad_eb_data6__ds1     :  1,    //     29
    reg_pad_eb_data6__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS008_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4424    crg_fms009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_vccen__st      :  1,    //      0
    reg_pad_sc_vccen__pu      :  1,    //      1
    reg_pad_sc_vccen__pd      :  1,    //      2
    reg_pad_sc_vccen__ds3     :  1,    //      3
    reg_pad_sc_vccen__ds2     :  1,    //      4
    reg_pad_sc_vccen__ds1     :  1,    //      5
    reg_pad_sc_vccen__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_sc_vcc_sel__st    :  1,    //      8
    reg_pad_sc_vcc_sel__pu    :  1,    //      9
    reg_pad_sc_vcc_sel__pd    :  1,    //     10
    reg_pad_sc_vcc_sel__ds3   :  1,    //     11
    reg_pad_sc_vcc_sel__ds2   :  1,    //     12
    reg_pad_sc_vcc_sel__ds1   :  1,    //     13
    reg_pad_sc_vcc_sel__ds0   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_sc_rst__st        :  1,    //     16
    reg_pad_sc_rst__pu        :  1,    //     17
    reg_pad_sc_rst__pd        :  1,    //     18
    reg_pad_sc_rst__ds3       :  1,    //     19
    reg_pad_sc_rst__ds2       :  1,    //     20
    reg_pad_sc_rst__ds1       :  1,    //     21
    reg_pad_sc_rst__ds0       :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_sc_detect__st     :  1,    //     24
    reg_pad_sc_detect__pu     :  1,    //     25
    reg_pad_sc_detect__pd     :  1,    //     26
    reg_pad_sc_detect__ds3    :  1,    //     27
    reg_pad_sc_detect__ds2    :  1,    //     28
    reg_pad_sc_detect__ds1    :  1,    //     29
    reg_pad_sc_detect__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS009_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4428    crg_fms010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr6__ds0     :  1,    //      0
    reg_pad_eb_addr6__ds1     :  1,    //      1
    reg_pad_eb_addr6__ds2     :  1,    //      2
    reg_pad_eb_addr6__ds3     :  1,    //      3
    reg_pad_eb_addr6__pd      :  1,    //      4
    reg_pad_eb_addr6__pu      :  1,    //      5
    reg_pad_eb_addr6__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr7__ds0     :  1,    //      8
    reg_pad_eb_addr7__ds1     :  1,    //      9
    reg_pad_eb_addr7__ds2     :  1,    //     10
    reg_pad_eb_addr7__ds3     :  1,    //     11
    reg_pad_eb_addr7__pd      :  1,    //     12
    reg_pad_eb_addr7__pu      :  1,    //     13
    reg_pad_eb_addr7__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr8__ds0     :  1,    //     16
    reg_pad_eb_addr8__ds1     :  1,    //     17
    reg_pad_eb_addr8__ds2     :  1,    //     18
    reg_pad_eb_addr8__ds3     :  1,    //     19
    reg_pad_eb_addr8__pd      :  1,    //     20
    reg_pad_eb_addr8__pu      :  1,    //     21
    reg_pad_eb_addr8__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr9__ds0     :  1,    //     24
    reg_pad_eb_addr9__ds1     :  1,    //     25
    reg_pad_eb_addr9__ds2     :  1,    //     26
    reg_pad_eb_addr9__ds3     :  1,    //     27
    reg_pad_eb_addr9__pd      :  1,    //     28
    reg_pad_eb_addr9__pu      :  1,    //     29
    reg_pad_eb_addr9__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMS_CRG_FMS010_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_442C    crg_fms011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr4__ds0     :  1,    //      0
    reg_pad_eb_addr4__ds1     :  1,    //      1
    reg_pad_eb_addr4__ds2     :  1,    //      2
    reg_pad_eb_addr4__ds3     :  1,    //      3
    reg_pad_eb_addr4__pd      :  1,    //      4
    reg_pad_eb_addr4__pu      :  1,    //      5
    reg_pad_eb_addr4__st      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr5__ds0     :  1,    //      8
    reg_pad_eb_addr5__ds1     :  1,    //      9
    reg_pad_eb_addr5__ds2     :  1,    //     10
    reg_pad_eb_addr5__ds3     :  1,    //     11
    reg_pad_eb_addr5__pd      :  1,    //     12
    reg_pad_eb_addr5__pu      :  1,    //     13
    reg_pad_eb_addr5__st      :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_FMS_CRG_FMS011_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4430    crg_fms012 ''
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
                              : 25;    //   31:7 reserved
}CTOP_FMS_CRG_FMS012_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4434    crg_fms013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_cam_reset_mux_sel :  4,    //   3: 0
    reg_pad_cam_reg_n_mux_sel :  4,    //   7: 4
    reg_pad_cam_ce2_n_mux_sel :  4,    //  11: 8
    reg_pad_cam_ce1_n_mux_sel :  4,    //  15:12
    reg_pad_cam_wait_n_mux_sel:  4,    //  19:16
    reg_pad_cam_ireq_n_mux_sel:  4,    //  23:20
    reg_pad_cam_cd2_n_mux_sel :  4,    //  27:24
    reg_pad_cam_cd1_n_mux_sel :  4;    //  31:28
}CTOP_FMS_CRG_FMS013_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4438    crg_fms014 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_vccen_mux_sel  :  4,    //   3: 0
    reg_pad_sc_vcc_sel_mux_sel:  4,    //   7: 4
    reg_pad_sc_rst_mux_sel    :  4,    //  11: 8
    reg_pad_sc_detect_mux_sel :  4,    //  15:12
    reg_pad_sc_data_mux_sel   :  4,    //  19:16
    reg_pad_sc_clk_out_mux_sel:  4,    //  23:20
    reg_pad_cam_vccen_n_mux_sel: 4,    //  27:24
                              :  4;    //  31:28 reserved
}CTOP_FMS_CRG_FMS014_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_443C    crg_fms015 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_data7_mux_sel  :  4,    //   3: 0
    reg_pad_eb_data6_mux_sel  :  4,    //   7: 4
    reg_pad_eb_data5_mux_sel  :  4,    //  11: 8
    reg_pad_eb_data4_mux_sel  :  4,    //  15:12
    reg_pad_eb_data3_mux_sel  :  4,    //  19:16
    reg_pad_eb_data2_mux_sel  :  4,    //  23:20
    reg_pad_eb_data1_mux_sel  :  4,    //  27:24
    reg_pad_eb_data0_mux_sel  :  4;    //  31:28
}CTOP_FMS_CRG_FMS015_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4440    crg_fms016 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr9_mux_sel  :  4,    //   3: 0
    reg_pad_eb_addr8_mux_sel  :  4,    //   7: 4
    reg_pad_eb_addr7_mux_sel  :  4,    //  11: 8
    reg_pad_eb_addr6_mux_sel  :  4,    //  15:12
    reg_pad_eb_addr5_mux_sel  :  4,    //  19:16
    reg_pad_eb_addr4_mux_sel  :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_FMS_CRG_FMS016_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC934_4444    crg_fms017 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr15_mux_sel :  4,    //   3: 0
    reg_pad_eb_addr14_mux_sel :  4,    //   7: 4
    reg_pad_eb_addr13_mux_sel :  4,    //  11: 8
    reg_pad_eb_addr12_mux_sel :  4,    //  15:12
    reg_pad_eb_addr11_mux_sel :  4,    //  19:16
    reg_pad_eb_addr10_mux_sel :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_FMS_CRG_FMS017_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_FMS_CRG_FMS000_E60_A0_T             crg_fms000               ;         // 0xC934_4400
    CTOP_FMS_CRG_FMS001_E60_A0_T             crg_fms001               ;         // 0xC934_4404
    CTOP_FMS_CRG_FMS002_E60_A0_T             crg_fms002               ;         // 0xC934_4408
    CTOP_FMS_CRG_FMS003_E60_A0_T             crg_fms003               ;         // 0xC934_440C
    CTOP_FMS_CRG_FMS004_E60_A0_T             crg_fms004               ;         // 0xC934_4410
    CTOP_FMS_CRG_FMS005_E60_A0_T             crg_fms005               ;         // 0xC934_4414
    CTOP_FMS_CRG_FMS006_E60_A0_T             crg_fms006               ;         // 0xC934_4418
    CTOP_FMS_CRG_FMS007_E60_A0_T             crg_fms007               ;         // 0xC934_441C
    CTOP_FMS_CRG_FMS008_E60_A0_T             crg_fms008               ;         // 0xC934_4420
    CTOP_FMS_CRG_FMS009_E60_A0_T             crg_fms009               ;         // 0xC934_4424
    CTOP_FMS_CRG_FMS010_E60_A0_T             crg_fms010               ;         // 0xC934_4428
    CTOP_FMS_CRG_FMS011_E60_A0_T             crg_fms011               ;         // 0xC934_442C
    CTOP_FMS_CRG_FMS012_E60_A0_T             crg_fms012               ;         // 0xC934_4430
    CTOP_FMS_CRG_FMS013_E60_A0_T             crg_fms013               ;         // 0xC934_4434
    CTOP_FMS_CRG_FMS014_E60_A0_T             crg_fms014               ;         // 0xC934_4438
    CTOP_FMS_CRG_FMS015_E60_A0_T             crg_fms015               ;         // 0xC934_443C
    CTOP_FMS_CRG_FMS016_E60_A0_T             crg_fms016               ;         // 0xC934_4440
    CTOP_FMS_CRG_FMS017_E60_A0_T             crg_fms017               ;         // 0xC934_4444
} CTOP_SYN_FMS_REG_E60_A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_FMS_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

