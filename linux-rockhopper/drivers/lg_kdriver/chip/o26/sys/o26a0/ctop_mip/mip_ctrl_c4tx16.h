#ifndef _MIP_CTRL_C4TX16_REG_O26A0_H_
#define _MIP_CTRL_C4TX16_REG_O26A0_H_

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
    0xCC97_4000    mip_c4tx16_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_rstn_vtxlink       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_clk_sel               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_c4tx_c4_lockn_sel     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_c4tx_data_sel         :  2,    //  13:12
                              : 18;    //  31:14 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4004    mip_c4tx16_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_intr_polar_high_en: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_c4_vx1_intr_edge_en   :  1,    //      4
    reg_c4_vx1_intr_clear     :  1,    //      5
    reg_c4_vx1_lockn_intr_en  :  1,    //      6
                              : 25;    //   31:7 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4008    mip_c4tx16_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_main_counter: 4,    //  3:0
    reg_c4_vx1_lockn_main_counter_clear: 1,    //  4
    reg_c4_vx1_lockn_main_counter_rising_edge: 1,    //  5
                              : 26;    //   31:6 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_400C    mip_c4tx16_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_epi_lock_tomain    :  1,    //      0
    reg_c4_vx1_lockn_tomain   :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4010    mip_c4tx16_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ext_reg_wrdata     :  8,    //   7: 0
    reg_c4_ext_reg_addr       :  8,    //  15: 8
    reg_c4_ext_reg_wr_en      :  1,    //     16
                              :  7,    //  23:17 reserved
    reg_c4_ext_reg_rstn       :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4014    mip_c4tx16_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link0_ext_reg_en   :  1,    //      0
    reg_c4_link1_ext_reg_en   :  1,    //      1
    reg_c4_link2_ext_reg_en   :  1,    //      2
    reg_c4_link3_ext_reg_en   :  1,    //      3
    reg_c4_link4_ext_reg_en   :  1,    //      4
    reg_c4_link5_ext_reg_en   :  1,    //      5
    reg_c4_pll_ext_reg_en     :  1,    //      6
                              : 25;    //   31:7 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4018    mip_c4tx16_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link2_ext_reg_rddata: 8,    //   7: 0
    reg_c4_link1_ext_reg_rddata: 8,    //  15: 8
    reg_c4_link0_ext_reg_rddata: 8,    //  23:16
    reg_c4_pll_ext_reg_rddata :  8;    //  31:24
}MIP_CTRL_C4TX16_MIP_C4TX16_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_401C    mip_c4tx16_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link5_ext_reg_rddata: 8,    //   7: 0
    reg_c4_link4_ext_reg_rddata: 8,    //  15: 8
    reg_c4_link3_ext_reg_rddata: 8,    //  23:16
                              :  8;    //  31:24 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4020    mip_c4tx16_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pll_rstn_g         :  1,    //      0
    reg_c4_pll_lock           :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4024    mip_c4tx16_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb_ch0            :  1,    //      0
    reg_c4_pdb_ch1            :  1,    //      1
    reg_c4_pdb_ch2            :  1,    //      2
    reg_c4_pdb_ch3            :  1,    //      3
    reg_c4_pdb_ch4            :  1,    //      4
    reg_c4_pdb_ch5            :  1,    //      5
    reg_c4_pdb_ch6            :  1,    //      6
    reg_c4_pdb_ch7            :  1,    //      7
    reg_c4_pdb_ch8            :  1,    //      8
    reg_c4_pdb_ch9            :  1,    //      9
    reg_c4_pdb_ch10           :  1,    //     10
    reg_c4_pdb_ch11           :  1,    //     11
    reg_c4_pdb_ch12           :  1,    //     12
    reg_c4_pdb_ch13           :  1,    //     13
    reg_c4_pdb_ch14           :  1,    //     14
    reg_c4_pdb_ch15           :  1,    //     15
                              :  8,    //  23:16 reserved
    reg_c4_pdb                :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4028    mip_c4tx16_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di5           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_402C    mip_c4tx16_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di4           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4030    mip_c4tx16_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di3           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4034    mip_c4tx16_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di2           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4038    mip_c4tx16_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di1           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_403C    mip_c4tx16_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di0           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4040    mip_c4tx16_16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb_sel            :  1,    //      0
                              : 31;    //   31:1 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4100    mip_c4tx16_64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_ctrl_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_edp34_mode_on         :  1,    //      4
                              : 27;    //   31:5 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4104    mip_c4tx16_65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_pre_emp0      :  2,    //   1: 0
    reg_edp_phy_pre_emp1      :  2,    //   3: 2
    reg_edp_phy_pre_emp2      :  2,    //   5: 4
    reg_edp_phy_pre_emp3      :  2,    //   7: 6
    reg_edp_phy_pre_emp4      :  2,    //   9: 8
    reg_edp_phy_pre_emp5      :  2,    //  11:10
    reg_edp_phy_pre_emp6      :  2,    //  13:12
    reg_edp_phy_pre_emp7      :  2,    //  15:14
    reg_edp_phy_pre_emp8      :  2,    //  17:16
    reg_edp_phy_pre_emp9      :  2,    //  19:18
    reg_edp_phy_pre_emp10     :  2,    //  21:20
    reg_edp_phy_pre_emp11     :  2,    //  23:22
    reg_edp_phy_pre_emp12     :  2,    //  25:24
    reg_edp_phy_pre_emp13     :  2,    //  27:26
    reg_edp_phy_pre_emp14     :  2,    //  29:28
    reg_edp_phy_pre_emp15     :  2;    //  31:30
}MIP_CTRL_C4TX16_MIP_C4TX16_65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4108    mip_c4tx16_66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_rate_link0    :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_edp_phy_rate_link1    :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_edp_phy_rate_link2    :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_edp_phy_rate_link3    :  3,    //  14:12
                              : 17;    //  31:15 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_410C    mip_c4tx16_67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_req_link0     :  1,    //      0
    reg_edp_phy_req_link1     :  1,    //      1
    reg_edp_phy_req_link2     :  1,    //      2
    reg_edp_phy_req_link3     :  1,    //      3
                              : 28;    //   31:4 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4110    mip_c4tx16_68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_rstn0         :  1,    //      0
    reg_edp_phy_rstn1         :  1,    //      1
    reg_edp_phy_rstn2         :  1,    //      2
    reg_edp_phy_rstn3         :  1,    //      3
    reg_edp_phy_rstn4         :  1,    //      4
    reg_edp_phy_rstn5         :  1,    //      5
    reg_edp_phy_rstn6         :  1,    //      6
    reg_edp_phy_rstn7         :  1,    //      7
    reg_edp_phy_rstn8         :  1,    //      8
    reg_edp_phy_rstn9         :  1,    //      9
    reg_edp_phy_rstn10        :  1,    //     10
    reg_edp_phy_rstn11        :  1,    //     11
    reg_edp_phy_rstn12        :  1,    //     12
    reg_edp_phy_rstn13        :  1,    //     13
    reg_edp_phy_rstn14        :  1,    //     14
    reg_edp_phy_rstn15        :  1,    //     15
                              : 16;    //  31:16 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4114    mip_c4tx16_69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_vswing0       :  2,    //   1: 0
    reg_edp_phy_vswing1       :  2,    //   3: 2
    reg_edp_phy_vswing2       :  2,    //   5: 4
    reg_edp_phy_vswing3       :  2,    //   7: 6
    reg_edp_phy_vswing4       :  2,    //   9: 8
    reg_edp_phy_vswing5       :  2,    //  11:10
    reg_edp_phy_vswing6       :  2,    //  13:12
    reg_edp_phy_vswing7       :  2,    //  15:14
    reg_edp_phy_vswing8       :  2,    //  17:16
    reg_edp_phy_vswing9       :  2,    //  19:18
    reg_edp_phy_vswing10      :  2,    //  21:20
    reg_edp_phy_vswing11      :  2,    //  23:22
    reg_edp_phy_vswing12      :  2,    //  25:24
    reg_edp_phy_vswing13      :  2,    //  27:26
    reg_edp_phy_vswing14      :  2,    //  29:28
    reg_edp_phy_vswing15      :  2;    //  31:30
}MIP_CTRL_C4TX16_MIP_C4TX16_69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4118    mip_c4tx16_70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edp_phy_width_link0   :  1,    //      0
    reg_edp_phy_width_link1   :  1,    //      1
    reg_edp_phy_width_link2   :  1,    //      2
    reg_edp_phy_width_link3   :  1,    //      3
                              : 28;    //   31:4 reserved
}MIP_CTRL_C4TX16_MIP_C4TX16_70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx16 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX16_MIP_C4TX16_00_O26A0_T    mip_c4tx16_00;     // 0xCC97_4000
    MIP_CTRL_C4TX16_MIP_C4TX16_01_O26A0_T    mip_c4tx16_01;     // 0xCC97_4004
    MIP_CTRL_C4TX16_MIP_C4TX16_02_O26A0_T    mip_c4tx16_02;     // 0xCC97_4008
    MIP_CTRL_C4TX16_MIP_C4TX16_03_O26A0_T    mip_c4tx16_03;     // 0xCC97_400C
    MIP_CTRL_C4TX16_MIP_C4TX16_04_O26A0_T    mip_c4tx16_04;     // 0xCC97_4010
    MIP_CTRL_C4TX16_MIP_C4TX16_05_O26A0_T    mip_c4tx16_05;     // 0xCC97_4014
    MIP_CTRL_C4TX16_MIP_C4TX16_06_O26A0_T    mip_c4tx16_06;     // 0xCC97_4018
    MIP_CTRL_C4TX16_MIP_C4TX16_07_O26A0_T    mip_c4tx16_07;     // 0xCC97_401C
    MIP_CTRL_C4TX16_MIP_C4TX16_08_O26A0_T    mip_c4tx16_08;     // 0xCC97_4020
    MIP_CTRL_C4TX16_MIP_C4TX16_09_O26A0_T    mip_c4tx16_09;     // 0xCC97_4024
    MIP_CTRL_C4TX16_MIP_C4TX16_10_O26A0_T    mip_c4tx16_10;     // 0xCC97_4028
    MIP_CTRL_C4TX16_MIP_C4TX16_11_O26A0_T    mip_c4tx16_11;     // 0xCC97_402C
    MIP_CTRL_C4TX16_MIP_C4TX16_12_O26A0_T    mip_c4tx16_12;     // 0xCC97_4030
    MIP_CTRL_C4TX16_MIP_C4TX16_13_O26A0_T    mip_c4tx16_13;     // 0xCC97_4034
    MIP_CTRL_C4TX16_MIP_C4TX16_14_O26A0_T    mip_c4tx16_14;     // 0xCC97_4038
    MIP_CTRL_C4TX16_MIP_C4TX16_15_O26A0_T    mip_c4tx16_15;     // 0xCC97_403C
    MIP_CTRL_C4TX16_MIP_C4TX16_16_O26A0_T    mip_c4tx16_16;     // 0xCC97_4040
    UINT32                             _rsvd_00[47];            // 0xCC97_4044 ~ 0xCC97_40FC
    MIP_CTRL_C4TX16_MIP_C4TX16_64_O26A0_T    mip_c4tx16_64;     // 0xCC97_4100
    MIP_CTRL_C4TX16_MIP_C4TX16_65_O26A0_T    mip_c4tx16_65;     // 0xCC97_4104
    MIP_CTRL_C4TX16_MIP_C4TX16_66_O26A0_T    mip_c4tx16_66;     // 0xCC97_4108
    MIP_CTRL_C4TX16_MIP_C4TX16_67_O26A0_T    mip_c4tx16_67;     // 0xCC97_410C
    MIP_CTRL_C4TX16_MIP_C4TX16_68_O26A0_T    mip_c4tx16_68;     // 0xCC97_4110
    MIP_CTRL_C4TX16_MIP_C4TX16_69_O26A0_T    mip_c4tx16_69;     // 0xCC97_4114
    MIP_CTRL_C4TX16_MIP_C4TX16_70_O26A0_T    mip_c4tx16_70;     // 0xCC97_4118
}MIP_CTRL_C4TX16_REG_O26A0_T;
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

#define MIP_CTRL_C4TX16_MIP_C4TX16_00_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define MIP_CTRL_C4TX16_MIP_C4TX16_01_O26A0_T_OFF           (BASEADDRESS+0x0004)
#define MIP_CTRL_C4TX16_MIP_C4TX16_02_O26A0_T_OFF           (BASEADDRESS+0x0008)
#define MIP_CTRL_C4TX16_MIP_C4TX16_03_O26A0_T_OFF           (BASEADDRESS+0x000C)
#define MIP_CTRL_C4TX16_MIP_C4TX16_04_O26A0_T_OFF           (BASEADDRESS+0x0010)
#define MIP_CTRL_C4TX16_MIP_C4TX16_05_O26A0_T_OFF           (BASEADDRESS+0x0014)
#define MIP_CTRL_C4TX16_MIP_C4TX16_06_O26A0_T_OFF           (BASEADDRESS+0x0018)
#define MIP_CTRL_C4TX16_MIP_C4TX16_07_O26A0_T_OFF           (BASEADDRESS+0x001C)
#define MIP_CTRL_C4TX16_MIP_C4TX16_08_O26A0_T_OFF           (BASEADDRESS+0x0020)
#define MIP_CTRL_C4TX16_MIP_C4TX16_09_O26A0_T_OFF           (BASEADDRESS+0x0024)
#define MIP_CTRL_C4TX16_MIP_C4TX16_10_O26A0_T_OFF           (BASEADDRESS+0x0028)
#define MIP_CTRL_C4TX16_MIP_C4TX16_11_O26A0_T_OFF           (BASEADDRESS+0x002C)
#define MIP_CTRL_C4TX16_MIP_C4TX16_12_O26A0_T_OFF           (BASEADDRESS+0x0030)
#define MIP_CTRL_C4TX16_MIP_C4TX16_13_O26A0_T_OFF           (BASEADDRESS+0x0034)
#define MIP_CTRL_C4TX16_MIP_C4TX16_14_O26A0_T_OFF           (BASEADDRESS+0x0038)
#define MIP_CTRL_C4TX16_MIP_C4TX16_15_O26A0_T_OFF           (BASEADDRESS+0x003C)
#define MIP_CTRL_C4TX16_MIP_C4TX16_16_O26A0_T_OFF           (BASEADDRESS+0x0040)
#define MIP_CTRL_C4TX16_MIP_C4TX16_64_O26A0_T_OFF           (BASEADDRESS+0x0100)
#define MIP_CTRL_C4TX16_MIP_C4TX16_65_O26A0_T_OFF           (BASEADDRESS+0x0104)
#define MIP_CTRL_C4TX16_MIP_C4TX16_66_O26A0_T_OFF           (BASEADDRESS+0x0108)
#define MIP_CTRL_C4TX16_MIP_C4TX16_67_O26A0_T_OFF           (BASEADDRESS+0x010C)
#define MIP_CTRL_C4TX16_MIP_C4TX16_68_O26A0_T_OFF           (BASEADDRESS+0x0110)
#define MIP_CTRL_C4TX16_MIP_C4TX16_69_O26A0_T_OFF           (BASEADDRESS+0x0114)
#define MIP_CTRL_C4TX16_MIP_C4TX16_70_O26A0_T_OFF           (BASEADDRESS+0x0118)

/*-----------------------------------------------------------------------------------------
    0xCC97_4000    mip_c4tx16_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_rstn_vtxlink:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_clk_sel        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_c4tx_c4_lockn_sel: 1;    //     8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_c4tx_data_sel  :  2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4004    mip_c4tx16_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_intr_polar_high_en: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_c4_vx1_intr_edge_en: 1;    //   4
    UINT32 reg_c4_vx1_intr_clear: 1;    //     5
    UINT32 reg_c4_vx1_lockn_intr_en: 1;    //  6
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4008    mip_c4tx16_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_lockn_main_counter: 4;    //  3:0
    UINT32 reg_c4_vx1_lockn_main_counter_clear: 1;    //  4
    UINT32 reg_c4_vx1_lockn_main_counter_rising_edge: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_400C    mip_c4tx16_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_epi_lock_tomain: 1;    //    0
    UINT32 reg_c4_vx1_lockn_tomain: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4010    mip_c4tx16_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_ext_reg_wrdata: 8;    //  7: 0
    UINT32 reg_c4_ext_reg_addr:  8;    //  15: 8
    UINT32 reg_c4_ext_reg_wr_en: 1;    //     16
    UINT32 resvd00            :  7;    //  23:17 reserved
    UINT32 reg_c4_ext_reg_rstn:  1;    //     24
    UINT32 resvd01            :  7;    //  31:25 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4014    mip_c4tx16_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link0_ext_reg_en: 1;    //   0
    UINT32 reg_c4_link1_ext_reg_en: 1;    //   1
    UINT32 reg_c4_link2_ext_reg_en: 1;    //   2
    UINT32 reg_c4_link3_ext_reg_en: 1;    //   3
    UINT32 reg_c4_link4_ext_reg_en: 1;    //   4
    UINT32 reg_c4_link5_ext_reg_en: 1;    //   5
    UINT32 reg_c4_pll_ext_reg_en: 1;    //     6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4018    mip_c4tx16_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link2_ext_reg_rddata: 8;    //  7:0
    UINT32 reg_c4_link1_ext_reg_rddata: 8;    //  15:8
    UINT32 reg_c4_link0_ext_reg_rddata: 8;    //  23:16
    UINT32 reg_c4_pll_ext_reg_rddata: 8;    //  31:24
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_401C    mip_c4tx16_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link5_ext_reg_rddata: 8;    //  7:0
    UINT32 reg_c4_link4_ext_reg_rddata: 8;    //  15:8
    UINT32 reg_c4_link3_ext_reg_rddata: 8;    //  23:16
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4020    mip_c4tx16_08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pll_rstn_g  :  1;    //      0
    UINT32 reg_c4_pll_lock    :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4024    mip_c4tx16_09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pdb_ch0     :  1;    //      0
    UINT32 reg_c4_pdb_ch1     :  1;    //      1
    UINT32 reg_c4_pdb_ch2     :  1;    //      2
    UINT32 reg_c4_pdb_ch3     :  1;    //      3
    UINT32 reg_c4_pdb_ch4     :  1;    //      4
    UINT32 reg_c4_pdb_ch5     :  1;    //      5
    UINT32 reg_c4_pdb_ch6     :  1;    //      6
    UINT32 reg_c4_pdb_ch7     :  1;    //      7
    UINT32 reg_c4_pdb_ch8     :  1;    //      8
    UINT32 reg_c4_pdb_ch9     :  1;    //      9
    UINT32 reg_c4_pdb_ch10    :  1;    //     10
    UINT32 reg_c4_pdb_ch11    :  1;    //     11
    UINT32 reg_c4_pdb_ch12    :  1;    //     12
    UINT32 reg_c4_pdb_ch13    :  1;    //     13
    UINT32 reg_c4_pdb_ch14    :  1;    //     14
    UINT32 reg_c4_pdb_ch15    :  1;    //     15
    UINT32 resvd00            :  8;    //  23:16 reserved
    UINT32 reg_c4_pdb         :  1;    //     24
    UINT32 resvd01            :  7;    //  31:25 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4028    mip_c4tx16_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di5    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_402C    mip_c4tx16_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di4    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4030    mip_c4tx16_12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di3    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4034    mip_c4tx16_13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di2    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4038    mip_c4tx16_14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di1    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_403C    mip_c4tx16_15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di0    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4040    mip_c4tx16_16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_pdb_sel     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_16_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4100    mip_c4tx16_64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_ctrl_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_edp34_mode_on  :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4104    mip_c4tx16_65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_pre_emp0: 2;    //   1: 0
    UINT32 reg_edp_phy_pre_emp1: 2;    //   3: 2
    UINT32 reg_edp_phy_pre_emp2: 2;    //   5: 4
    UINT32 reg_edp_phy_pre_emp3: 2;    //   7: 6
    UINT32 reg_edp_phy_pre_emp4: 2;    //   9: 8
    UINT32 reg_edp_phy_pre_emp5: 2;    //  11:10
    UINT32 reg_edp_phy_pre_emp6: 2;    //  13:12
    UINT32 reg_edp_phy_pre_emp7: 2;    //  15:14
    UINT32 reg_edp_phy_pre_emp8: 2;    //  17:16
    UINT32 reg_edp_phy_pre_emp9: 2;    //  19:18
    UINT32 reg_edp_phy_pre_emp10: 2;    //  21:20
    UINT32 reg_edp_phy_pre_emp11: 2;    //  23:22
    UINT32 reg_edp_phy_pre_emp12: 2;    //  25:24
    UINT32 reg_edp_phy_pre_emp13: 2;    //  27:26
    UINT32 reg_edp_phy_pre_emp14: 2;    //  29:28
    UINT32 reg_edp_phy_pre_emp15: 2;    //  31:30
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4108    mip_c4tx16_66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_rate_link0: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_edp_phy_rate_link1: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_edp_phy_rate_link2: 3;    //  10:8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_edp_phy_rate_link3: 3;    //  14:12
    UINT32 resvd03            : 17;    //  31:15 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_410C    mip_c4tx16_67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_req_link0: 1;    //     0
    UINT32 reg_edp_phy_req_link1: 1;    //     1
    UINT32 reg_edp_phy_req_link2: 1;    //     2
    UINT32 reg_edp_phy_req_link3: 1;    //     3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4110    mip_c4tx16_68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_rstn0  :  1;    //      0
    UINT32 reg_edp_phy_rstn1  :  1;    //      1
    UINT32 reg_edp_phy_rstn2  :  1;    //      2
    UINT32 reg_edp_phy_rstn3  :  1;    //      3
    UINT32 reg_edp_phy_rstn4  :  1;    //      4
    UINT32 reg_edp_phy_rstn5  :  1;    //      5
    UINT32 reg_edp_phy_rstn6  :  1;    //      6
    UINT32 reg_edp_phy_rstn7  :  1;    //      7
    UINT32 reg_edp_phy_rstn8  :  1;    //      8
    UINT32 reg_edp_phy_rstn9  :  1;    //      9
    UINT32 reg_edp_phy_rstn10 :  1;    //     10
    UINT32 reg_edp_phy_rstn11 :  1;    //     11
    UINT32 reg_edp_phy_rstn12 :  1;    //     12
    UINT32 reg_edp_phy_rstn13 :  1;    //     13
    UINT32 reg_edp_phy_rstn14 :  1;    //     14
    UINT32 reg_edp_phy_rstn15 :  1;    //     15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4114    mip_c4tx16_69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_vswing0:  2;    //   1: 0
    UINT32 reg_edp_phy_vswing1:  2;    //   3: 2
    UINT32 reg_edp_phy_vswing2:  2;    //   5: 4
    UINT32 reg_edp_phy_vswing3:  2;    //   7: 6
    UINT32 reg_edp_phy_vswing4:  2;    //   9: 8
    UINT32 reg_edp_phy_vswing5:  2;    //  11:10
    UINT32 reg_edp_phy_vswing6:  2;    //  13:12
    UINT32 reg_edp_phy_vswing7:  2;    //  15:14
    UINT32 reg_edp_phy_vswing8:  2;    //  17:16
    UINT32 reg_edp_phy_vswing9:  2;    //  19:18
    UINT32 reg_edp_phy_vswing10: 2;    //  21:20
    UINT32 reg_edp_phy_vswing11: 2;    //  23:22
    UINT32 reg_edp_phy_vswing12: 2;    //  25:24
    UINT32 reg_edp_phy_vswing13: 2;    //  27:26
    UINT32 reg_edp_phy_vswing14: 2;    //  29:28
    UINT32 reg_edp_phy_vswing15: 2;    //  31:30
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_4118    mip_c4tx16_70 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edp_phy_width_link0: 1;    //   0
    UINT32 reg_edp_phy_width_link1: 1;    //   1
    UINT32 reg_edp_phy_width_link2: 1;    //   2
    UINT32 reg_edp_phy_width_link3: 1;    //   3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MIP_CTRL_C4TX16_MIP_C4TX16_70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx16 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX16_MIP_C4TX16_00_O26A0_T    mip_c4tx16_00;     // 0xCC97_4000
    MIP_CTRL_C4TX16_MIP_C4TX16_01_O26A0_T    mip_c4tx16_01;     // 0xCC97_4004
    MIP_CTRL_C4TX16_MIP_C4TX16_02_O26A0_T    mip_c4tx16_02;     // 0xCC97_4008
    MIP_CTRL_C4TX16_MIP_C4TX16_03_O26A0_T    mip_c4tx16_03;     // 0xCC97_400C
    MIP_CTRL_C4TX16_MIP_C4TX16_04_O26A0_T    mip_c4tx16_04;     // 0xCC97_4010
    MIP_CTRL_C4TX16_MIP_C4TX16_05_O26A0_T    mip_c4tx16_05;     // 0xCC97_4014
    MIP_CTRL_C4TX16_MIP_C4TX16_06_O26A0_T    mip_c4tx16_06;     // 0xCC97_4018
    MIP_CTRL_C4TX16_MIP_C4TX16_07_O26A0_T    mip_c4tx16_07;     // 0xCC97_401C
    MIP_CTRL_C4TX16_MIP_C4TX16_08_O26A0_T    mip_c4tx16_08;     // 0xCC97_4020
    MIP_CTRL_C4TX16_MIP_C4TX16_09_O26A0_T    mip_c4tx16_09;     // 0xCC97_4024
    MIP_CTRL_C4TX16_MIP_C4TX16_10_O26A0_T    mip_c4tx16_10;     // 0xCC97_4028
    MIP_CTRL_C4TX16_MIP_C4TX16_11_O26A0_T    mip_c4tx16_11;     // 0xCC97_402C
    MIP_CTRL_C4TX16_MIP_C4TX16_12_O26A0_T    mip_c4tx16_12;     // 0xCC97_4030
    MIP_CTRL_C4TX16_MIP_C4TX16_13_O26A0_T    mip_c4tx16_13;     // 0xCC97_4034
    MIP_CTRL_C4TX16_MIP_C4TX16_14_O26A0_T    mip_c4tx16_14;     // 0xCC97_4038
    MIP_CTRL_C4TX16_MIP_C4TX16_15_O26A0_T    mip_c4tx16_15;     // 0xCC97_403C
    MIP_CTRL_C4TX16_MIP_C4TX16_16_O26A0_T    mip_c4tx16_16;     // 0xCC97_4040
    UINT32                             _rsvd_00[47];            // 0xCC97_4044 ~ 0xCC97_40FC
    MIP_CTRL_C4TX16_MIP_C4TX16_64_O26A0_T    mip_c4tx16_64;     // 0xCC97_4100
    MIP_CTRL_C4TX16_MIP_C4TX16_65_O26A0_T    mip_c4tx16_65;     // 0xCC97_4104
    MIP_CTRL_C4TX16_MIP_C4TX16_66_O26A0_T    mip_c4tx16_66;     // 0xCC97_4108
    MIP_CTRL_C4TX16_MIP_C4TX16_67_O26A0_T    mip_c4tx16_67;     // 0xCC97_410C
    MIP_CTRL_C4TX16_MIP_C4TX16_68_O26A0_T    mip_c4tx16_68;     // 0xCC97_4110
    MIP_CTRL_C4TX16_MIP_C4TX16_69_O26A0_T    mip_c4tx16_69;     // 0xCC97_4114
    MIP_CTRL_C4TX16_MIP_C4TX16_70_O26A0_T    mip_c4tx16_70;     // 0xCC97_4118
}MIP_CTRL_C4TX16_REG_O26A0_T;
/* 24 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_C4TX16_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

