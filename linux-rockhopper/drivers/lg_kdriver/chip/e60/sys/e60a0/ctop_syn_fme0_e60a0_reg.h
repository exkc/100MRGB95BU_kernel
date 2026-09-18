#ifndef _CTOP_SYN_FME0_E60A0_REG_H_
#define _CTOP_SYN_FME0_E60A0_REG_H_

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
    0xC935_4400    syn_fme000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_me0_ctrl          : 32;    //  31: 0
}CTOP_FME0_SYN_FME000_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4404    syn_fme001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_me0        :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FME0_SYN_FME001_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4408    syn_fme002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_cam__st :  1,    //      0
    reg_pad_tpi_data0_cam__pu :  1,    //      1
    reg_pad_tpi_data0_cam__pd :  1,    //      2
    reg_pad_tpi_data0_cam__ds3:  1,    //      3
    reg_pad_tpi_data0_cam__ds2:  1,    //      4
    reg_pad_tpi_data0_cam__ds1:  1,    //      5
    reg_pad_tpi_data0_cam__ds0:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_clk_cam__st   :  1,    //      8
    reg_pad_tpi_clk_cam__pu   :  1,    //      9
    reg_pad_tpi_clk_cam__pd   :  1,    //     10
    reg_pad_tpi_clk_cam__ds3  :  1,    //     11
    reg_pad_tpi_clk_cam__ds2  :  1,    //     12
    reg_pad_tpi_clk_cam__ds1  :  1,    //     13
    reg_pad_tpi_clk_cam__ds0  :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_FME0_SYN_FME002_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_440C    syn_fme003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_cam__st :  1,    //      0
    reg_pad_tpi_data4_cam__pu :  1,    //      1
    reg_pad_tpi_data4_cam__pd :  1,    //      2
    reg_pad_tpi_data4_cam__ds3:  1,    //      3
    reg_pad_tpi_data4_cam__ds2:  1,    //      4
    reg_pad_tpi_data4_cam__ds1:  1,    //      5
    reg_pad_tpi_data4_cam__ds0:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data3_cam__st :  1,    //      8
    reg_pad_tpi_data3_cam__pu :  1,    //      9
    reg_pad_tpi_data3_cam__pd :  1,    //     10
    reg_pad_tpi_data3_cam__ds3:  1,    //     11
    reg_pad_tpi_data3_cam__ds2:  1,    //     12
    reg_pad_tpi_data3_cam__ds1:  1,    //     13
    reg_pad_tpi_data3_cam__ds0:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data2_cam__st :  1,    //     16
    reg_pad_tpi_data2_cam__pu :  1,    //     17
    reg_pad_tpi_data2_cam__pd :  1,    //     18
    reg_pad_tpi_data2_cam__ds3:  1,    //     19
    reg_pad_tpi_data2_cam__ds2:  1,    //     20
    reg_pad_tpi_data2_cam__ds1:  1,    //     21
    reg_pad_tpi_data2_cam__ds0:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data1_cam__st :  1,    //     24
    reg_pad_tpi_data1_cam__pu :  1,    //     25
    reg_pad_tpi_data1_cam__pd :  1,    //     26
    reg_pad_tpi_data1_cam__ds3:  1,    //     27
    reg_pad_tpi_data1_cam__ds2:  1,    //     28
    reg_pad_tpi_data1_cam__ds1:  1,    //     29
    reg_pad_tpi_data1_cam__ds0:  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_SYN_FME003_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4410    syn_fme004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_sop_cam__st   :  1,    //      0
    reg_pad_tpi_sop_cam__pu   :  1,    //      1
    reg_pad_tpi_sop_cam__pd   :  1,    //      2
    reg_pad_tpi_sop_cam__ds3  :  1,    //      3
    reg_pad_tpi_sop_cam__ds2  :  1,    //      4
    reg_pad_tpi_sop_cam__ds1  :  1,    //      5
    reg_pad_tpi_sop_cam__ds0  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data7_cam__st :  1,    //      8
    reg_pad_tpi_data7_cam__pu :  1,    //      9
    reg_pad_tpi_data7_cam__pd :  1,    //     10
    reg_pad_tpi_data7_cam__ds3:  1,    //     11
    reg_pad_tpi_data7_cam__ds2:  1,    //     12
    reg_pad_tpi_data7_cam__ds1:  1,    //     13
    reg_pad_tpi_data7_cam__ds0:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data6_cam__st :  1,    //     16
    reg_pad_tpi_data6_cam__pu :  1,    //     17
    reg_pad_tpi_data6_cam__pd :  1,    //     18
    reg_pad_tpi_data6_cam__ds3:  1,    //     19
    reg_pad_tpi_data6_cam__ds2:  1,    //     20
    reg_pad_tpi_data6_cam__ds1:  1,    //     21
    reg_pad_tpi_data6_cam__ds0:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data5_cam__st :  1,    //     24
    reg_pad_tpi_data5_cam__pu :  1,    //     25
    reg_pad_tpi_data5_cam__pd :  1,    //     26
    reg_pad_tpi_data5_cam__ds3:  1,    //     27
    reg_pad_tpi_data5_cam__ds2:  1,    //     28
    reg_pad_tpi_data5_cam__ds1:  1,    //     29
    reg_pad_tpi_data5_cam__ds0:  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_SYN_FME004_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4414    syn_fme005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data1_cam__st :  1,    //      0
    reg_pad_tpo_data1_cam__pu :  1,    //      1
    reg_pad_tpo_data1_cam__pd :  1,    //      2
    reg_pad_tpo_data1_cam__ds3:  1,    //      3
    reg_pad_tpo_data1_cam__ds2:  1,    //      4
    reg_pad_tpo_data1_cam__ds1:  1,    //      5
    reg_pad_tpo_data1_cam__ds0:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data0_cam__st :  1,    //      8
    reg_pad_tpo_data0_cam__pu :  1,    //      9
    reg_pad_tpo_data0_cam__pd :  1,    //     10
    reg_pad_tpo_data0_cam__ds3:  1,    //     11
    reg_pad_tpo_data0_cam__ds2:  1,    //     12
    reg_pad_tpo_data0_cam__ds1:  1,    //     13
    reg_pad_tpo_data0_cam__ds0:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_clk_cam__st   :  1,    //     16
    reg_pad_tpo_clk_cam__pu   :  1,    //     17
    reg_pad_tpo_clk_cam__pd   :  1,    //     18
    reg_pad_tpo_clk_cam__ds3  :  1,    //     19
    reg_pad_tpo_clk_cam__ds2  :  1,    //     20
    reg_pad_tpo_clk_cam__ds1  :  1,    //     21
    reg_pad_tpo_clk_cam__ds0  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_val_cam__st   :  1,    //     24
    reg_pad_tpi_val_cam__pu   :  1,    //     25
    reg_pad_tpi_val_cam__pd   :  1,    //     26
    reg_pad_tpi_val_cam__ds3  :  1,    //     27
    reg_pad_tpi_val_cam__ds2  :  1,    //     28
    reg_pad_tpi_val_cam__ds1  :  1,    //     29
    reg_pad_tpi_val_cam__ds0  :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_SYN_FME005_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4418    syn_fme006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data5_cam__st :  1,    //      0
    reg_pad_tpo_data5_cam__pu :  1,    //      1
    reg_pad_tpo_data5_cam__pd :  1,    //      2
    reg_pad_tpo_data5_cam__ds3:  1,    //      3
    reg_pad_tpo_data5_cam__ds2:  1,    //      4
    reg_pad_tpo_data5_cam__ds1:  1,    //      5
    reg_pad_tpo_data5_cam__ds0:  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_data4_cam__st :  1,    //      8
    reg_pad_tpo_data4_cam__pu :  1,    //      9
    reg_pad_tpo_data4_cam__pd :  1,    //     10
    reg_pad_tpo_data4_cam__ds3:  1,    //     11
    reg_pad_tpo_data4_cam__ds2:  1,    //     12
    reg_pad_tpo_data4_cam__ds1:  1,    //     13
    reg_pad_tpo_data4_cam__ds0:  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data3_cam__st :  1,    //     16
    reg_pad_tpo_data3_cam__pu :  1,    //     17
    reg_pad_tpo_data3_cam__pd :  1,    //     18
    reg_pad_tpo_data3_cam__ds3:  1,    //     19
    reg_pad_tpo_data3_cam__ds2:  1,    //     20
    reg_pad_tpo_data3_cam__ds1:  1,    //     21
    reg_pad_tpo_data3_cam__ds0:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data2_cam__st :  1,    //     24
    reg_pad_tpo_data2_cam__pu :  1,    //     25
    reg_pad_tpo_data2_cam__pd :  1,    //     26
    reg_pad_tpo_data2_cam__ds3:  1,    //     27
    reg_pad_tpo_data2_cam__ds2:  1,    //     28
    reg_pad_tpo_data2_cam__ds1:  1,    //     29
    reg_pad_tpo_data2_cam__ds0:  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_SYN_FME006_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_441C    syn_fme007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_val_cam__st   :  1,    //      0
    reg_pad_tpo_val_cam__pu   :  1,    //      1
    reg_pad_tpo_val_cam__pd   :  1,    //      2
    reg_pad_tpo_val_cam__ds3  :  1,    //      3
    reg_pad_tpo_val_cam__ds2  :  1,    //      4
    reg_pad_tpo_val_cam__ds1  :  1,    //      5
    reg_pad_tpo_val_cam__ds0  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpo_sop_cam__st   :  1,    //      8
    reg_pad_tpo_sop_cam__pu   :  1,    //      9
    reg_pad_tpo_sop_cam__pd   :  1,    //     10
    reg_pad_tpo_sop_cam__ds3  :  1,    //     11
    reg_pad_tpo_sop_cam__ds2  :  1,    //     12
    reg_pad_tpo_sop_cam__ds1  :  1,    //     13
    reg_pad_tpo_sop_cam__ds0  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpo_data7_cam__st :  1,    //     16
    reg_pad_tpo_data7_cam__pu :  1,    //     17
    reg_pad_tpo_data7_cam__pd :  1,    //     18
    reg_pad_tpo_data7_cam__ds3:  1,    //     19
    reg_pad_tpo_data7_cam__ds2:  1,    //     20
    reg_pad_tpo_data7_cam__ds1:  1,    //     21
    reg_pad_tpo_data7_cam__ds0:  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpo_data6_cam__st :  1,    //     24
    reg_pad_tpo_data6_cam__pu :  1,    //     25
    reg_pad_tpo_data6_cam__pd :  1,    //     26
    reg_pad_tpo_data6_cam__ds3:  1,    //     27
    reg_pad_tpo_data6_cam__ds2:  1,    //     28
    reg_pad_tpo_data6_cam__ds1:  1,    //     29
    reg_pad_tpo_data6_cam__ds0:  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_SYN_FME007_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4420    syn_fme008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data3_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_data2_cam_mux_sel: 4,    //  7:4
    reg_pad_tpi_data1_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data0_cam_mux_sel: 4,    //  15:12
    reg_pad_tpi_clk_cam_mux_sel: 4,    //  19:16
                              : 12;    //  31:20 reserved
}CTOP_FME0_SYN_FME008_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4424    syn_fme009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_data6_cam_mux_sel: 4,    //  7:4
    reg_pad_tpi_data5_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data4_cam_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}CTOP_FME0_SYN_FME009_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4428    syn_fme010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_clk_cam_mux_sel: 4,    //   3: 0
    reg_pad_tpi_val_cam_mux_sel: 4,    //   7: 4
    reg_pad_tpi_sop_cam_mux_sel: 4,    //  11: 8
                              : 20;    //  31:12 reserved
}CTOP_FME0_SYN_FME010_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_442C    syn_fme011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data3_cam_mux_sel: 4,    //  3:0
    reg_pad_tpo_data2_cam_mux_sel: 4,    //  7:4
    reg_pad_tpo_data1_cam_mux_sel: 4,    //  11:8
    reg_pad_tpo_data0_cam_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}CTOP_FME0_SYN_FME011_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4430    syn_fme012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data7_cam_mux_sel: 4,    //  3:0
    reg_pad_tpo_data6_cam_mux_sel: 4,    //  7:4
    reg_pad_tpo_data5_cam_mux_sel: 4,    //  11:8
    reg_pad_tpo_data4_cam_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}CTOP_FME0_SYN_FME012_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_4434    syn_fme013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_val_cam_mux_sel: 4,    //   3: 0
    reg_pad_tpo_sop_cam_mux_sel: 4,    //   7: 4
                              : 24;    //   31:8 reserved
}CTOP_FME0_SYN_FME013_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    fme0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_FME0_SYN_FME000_E60_A0_T            syn_fme000               ;         // 0xC935_4400
    CTOP_FME0_SYN_FME001_E60_A0_T            syn_fme001               ;         // 0xC935_4404
    CTOP_FME0_SYN_FME002_E60_A0_T            syn_fme002               ;         // 0xC935_4408
    CTOP_FME0_SYN_FME003_E60_A0_T            syn_fme003               ;         // 0xC935_440C
    CTOP_FME0_SYN_FME004_E60_A0_T            syn_fme004               ;         // 0xC935_4410
    CTOP_FME0_SYN_FME005_E60_A0_T            syn_fme005               ;         // 0xC935_4414
    CTOP_FME0_SYN_FME006_E60_A0_T            syn_fme006               ;         // 0xC935_4418
    CTOP_FME0_SYN_FME007_E60_A0_T            syn_fme007               ;         // 0xC935_441C
    CTOP_FME0_SYN_FME008_E60_A0_T            syn_fme008               ;         // 0xC935_4420
    CTOP_FME0_SYN_FME009_E60_A0_T            syn_fme009               ;         // 0xC935_4424
    CTOP_FME0_SYN_FME010_E60_A0_T            syn_fme010               ;         // 0xC935_4428
    CTOP_FME0_SYN_FME011_E60_A0_T            syn_fme011               ;         // 0xC935_442C
    CTOP_FME0_SYN_FME012_E60_A0_T            syn_fme012               ;         // 0xC935_4430
    CTOP_FME0_SYN_FME013_E60_A0_T            syn_fme013               ;         // 0xC935_4434
} CTOP_SYN_FME0_REG_E60_A0_T;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_FME0_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

