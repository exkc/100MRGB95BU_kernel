#ifndef _MIP_CTRL_C4TX_REG_O24A0_H_
#define _MIP_CTRL_C4TX_REG_O24A0_H_

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
    0xCC93_3000    mip_c4tx24_00 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3004    mip_c4tx24_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_intr_polar_high_en: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_c4_vx1_intr_edge_en   :  1,    //      4
    reg_c4_vx1_intr_clear     :  1,    //      5
    reg_c4_vx1_lockn_intr_en  :  1,    //      6
                              : 25;    //   31:7 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3008    mip_c4tx24_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_main_counter: 4,    //  3:0
    reg_c4_vx1_lockn_main_counter_clear: 1,    //  4
    reg_c4_vx1_lockn_main_counter_rising_edge: 1,    //  5
                              : 26;    //   31:6 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_300C    mip_c4tx24_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_epi_lock_tomain    :  1,    //      0
    reg_c4_vx1_lockn_tomain   :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3010    mip_c4tx24_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ext_reg_wrdata     :  8,    //   7: 0
    reg_c4_ext_reg_addr       :  8,    //  15: 8
    reg_c4_ext_reg_wr_en      :  1,    //     16
                              :  7,    //  23:17 reserved
    reg_c4_ext_reg_rstn       :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3014    mip_c4tx24_05 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3018    mip_c4tx24_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link2_ext_reg_rddata   :  8,    //   7: 0
    c4_link1_ext_reg_rddata   :  8,    //  15: 8
    c4_link0_ext_reg_rddata   :  8,    //  23:16
    c4_pll_ext_reg_rddata     :  8;    //  31:24
}MIP_CTRL_C4TX_MIP_C4TX24_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_301C    mip_c4tx24_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link5_ext_reg_rddata   :  8,    //   7: 0
    c4_link4_ext_reg_rddata   :  8,    //  15: 8
    c4_link3_ext_reg_rddata   :  8,    //  23:16
                              :  8;    //  31:24 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3020    mip_c4tx24_08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pll_rstn_g             :  1,    //      0
    c4_pll_lock               :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3024    mip_c4tx24_09 ''
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
    reg_c4_pdb_ch16           :  1,    //     16
    reg_c4_pdb_ch17           :  1,    //     17
    reg_c4_pdb_ch18           :  1,    //     18
    reg_c4_pdb_ch19           :  1,    //     19
    reg_c4_pdb_ch20           :  1,    //     20
    reg_c4_pdb_ch21           :  1,    //     21
    reg_c4_pdb_ch22           :  1,    //     22
    reg_c4_pdb_ch23           :  1,    //     23
    reg_c4_pdb                :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3028    mip_c4tx24_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di5           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_302C    mip_c4tx24_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di4           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3030    mip_c4tx24_12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di3           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3034    mip_c4tx24_13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di2           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3038    mip_c4tx24_14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di1           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_303C    mip_c4tx24_15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di0           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX24_15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX_MIP_C4TX24_00_O24A0_T    mip_c4tx24_00;       // 0xCC93_3000
    MIP_CTRL_C4TX_MIP_C4TX24_01_O24A0_T    mip_c4tx24_01;       // 0xCC93_3004
    MIP_CTRL_C4TX_MIP_C4TX24_02_O24A0_T    mip_c4tx24_02;       // 0xCC93_3008
    MIP_CTRL_C4TX_MIP_C4TX24_03_O24A0_T    mip_c4tx24_03;       // 0xCC93_300C
    MIP_CTRL_C4TX_MIP_C4TX24_04_O24A0_T    mip_c4tx24_04;       // 0xCC93_3010
    MIP_CTRL_C4TX_MIP_C4TX24_05_O24A0_T    mip_c4tx24_05;       // 0xCC93_3014
    MIP_CTRL_C4TX_MIP_C4TX24_06_O24A0_T    mip_c4tx24_06;       // 0xCC93_3018
    MIP_CTRL_C4TX_MIP_C4TX24_07_O24A0_T    mip_c4tx24_07;       // 0xCC93_301C
    MIP_CTRL_C4TX_MIP_C4TX24_08_O24A0_T    mip_c4tx24_08;       // 0xCC93_3020
    MIP_CTRL_C4TX_MIP_C4TX24_09_O24A0_T    mip_c4tx24_09;       // 0xCC93_3024
    MIP_CTRL_C4TX_MIP_C4TX24_10_O24A0_T    mip_c4tx24_10;       // 0xCC93_3028
    MIP_CTRL_C4TX_MIP_C4TX24_11_O24A0_T    mip_c4tx24_11;       // 0xCC93_302C
    MIP_CTRL_C4TX_MIP_C4TX24_12_O24A0_T    mip_c4tx24_12;       // 0xCC93_3030
    MIP_CTRL_C4TX_MIP_C4TX24_13_O24A0_T    mip_c4tx24_13;       // 0xCC93_3034
    MIP_CTRL_C4TX_MIP_C4TX24_14_O24A0_T    mip_c4tx24_14;       // 0xCC93_3038
    MIP_CTRL_C4TX_MIP_C4TX24_15_O24A0_T    mip_c4tx24_15;       // 0xCC93_303C
}MIP_CTRL_C4TX_REG_O24A0_T;
/* 16 regs */

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

#define MIP_CTRL_C4TX_MIP_C4TX24_00_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define MIP_CTRL_C4TX_MIP_C4TX24_01_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define MIP_CTRL_C4TX_MIP_C4TX24_02_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define MIP_CTRL_C4TX_MIP_C4TX24_03_O24A0_T_OFF             (BASEADDRESS+0x000C)
#define MIP_CTRL_C4TX_MIP_C4TX24_04_O24A0_T_OFF             (BASEADDRESS+0x0010)
#define MIP_CTRL_C4TX_MIP_C4TX24_05_O24A0_T_OFF             (BASEADDRESS+0x0014)
#define MIP_CTRL_C4TX_MIP_C4TX24_06_O24A0_T_OFF             (BASEADDRESS+0x0018)
#define MIP_CTRL_C4TX_MIP_C4TX24_07_O24A0_T_OFF             (BASEADDRESS+0x001C)
#define MIP_CTRL_C4TX_MIP_C4TX24_08_O24A0_T_OFF             (BASEADDRESS+0x0020)
#define MIP_CTRL_C4TX_MIP_C4TX24_09_O24A0_T_OFF             (BASEADDRESS+0x0024)
#define MIP_CTRL_C4TX_MIP_C4TX24_10_O24A0_T_OFF             (BASEADDRESS+0x0028)
#define MIP_CTRL_C4TX_MIP_C4TX24_11_O24A0_T_OFF             (BASEADDRESS+0x002C)
#define MIP_CTRL_C4TX_MIP_C4TX24_12_O24A0_T_OFF             (BASEADDRESS+0x0030)
#define MIP_CTRL_C4TX_MIP_C4TX24_13_O24A0_T_OFF             (BASEADDRESS+0x0034)
#define MIP_CTRL_C4TX_MIP_C4TX24_14_O24A0_T_OFF             (BASEADDRESS+0x0038)
#define MIP_CTRL_C4TX_MIP_C4TX24_15_O24A0_T_OFF             (BASEADDRESS+0x003C)

/*-----------------------------------------------------------------------------------------
    0xCC93_3000    mip_c4tx24_00 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3004    mip_c4tx24_01 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3008    mip_c4tx24_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_lockn_main_counter: 4;    //  3:0
    UINT32 reg_c4_vx1_lockn_main_counter_clear: 1;    //  4
    UINT32 reg_c4_vx1_lockn_main_counter_rising_edge: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_300C    mip_c4tx24_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_epi_lock_tomain: 1;    //    0
    UINT32 reg_c4_vx1_lockn_tomain: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3010    mip_c4tx24_04 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3014    mip_c4tx24_05 ''
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
}MIP_CTRL_C4TX_MIP_C4TX24_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3018    mip_c4tx24_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_link2_ext_reg_rddata: 8;    //  7:0
    UINT32 c4_link1_ext_reg_rddata: 8;    //  15:8
    UINT32 c4_link0_ext_reg_rddata: 8;    //  23:16
    UINT32 c4_pll_ext_reg_rddata: 8;    //  31:24
    };
}MIP_CTRL_C4TX_MIP_C4TX24_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_301C    mip_c4tx24_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_link5_ext_reg_rddata: 8;    //  7:0
    UINT32 c4_link4_ext_reg_rddata: 8;    //  15:8
    UINT32 c4_link3_ext_reg_rddata: 8;    //  23:16
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3020    mip_c4tx24_08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_pll_rstn_g      :  1;    //      0
    UINT32 c4_pll_lock        :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_08_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3024    mip_c4tx24_09 ''
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
    UINT32 reg_c4_pdb_ch16    :  1;    //     16
    UINT32 reg_c4_pdb_ch17    :  1;    //     17
    UINT32 reg_c4_pdb_ch18    :  1;    //     18
    UINT32 reg_c4_pdb_ch19    :  1;    //     19
    UINT32 reg_c4_pdb_ch20    :  1;    //     20
    UINT32 reg_c4_pdb_ch21    :  1;    //     21
    UINT32 reg_c4_pdb_ch22    :  1;    //     22
    UINT32 reg_c4_pdb_ch23    :  1;    //     23
    UINT32 reg_c4_pdb         :  1;    //     24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_09_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3028    mip_c4tx24_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di5    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_302C    mip_c4tx24_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di4    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3030    mip_c4tx24_12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di3    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3034    mip_c4tx24_13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di2    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_3038    mip_c4tx24_14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di1    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_303C    mip_c4tx24_15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di0    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX24_15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX_MIP_C4TX24_00_O24A0_T    mip_c4tx24_00;       // 0xCC93_3000
    MIP_CTRL_C4TX_MIP_C4TX24_01_O24A0_T    mip_c4tx24_01;       // 0xCC93_3004
    MIP_CTRL_C4TX_MIP_C4TX24_02_O24A0_T    mip_c4tx24_02;       // 0xCC93_3008
    MIP_CTRL_C4TX_MIP_C4TX24_03_O24A0_T    mip_c4tx24_03;       // 0xCC93_300C
    MIP_CTRL_C4TX_MIP_C4TX24_04_O24A0_T    mip_c4tx24_04;       // 0xCC93_3010
    MIP_CTRL_C4TX_MIP_C4TX24_05_O24A0_T    mip_c4tx24_05;       // 0xCC93_3014
    MIP_CTRL_C4TX_MIP_C4TX24_06_O24A0_T    mip_c4tx24_06;       // 0xCC93_3018
    MIP_CTRL_C4TX_MIP_C4TX24_07_O24A0_T    mip_c4tx24_07;       // 0xCC93_301C
    MIP_CTRL_C4TX_MIP_C4TX24_08_O24A0_T    mip_c4tx24_08;       // 0xCC93_3020
    MIP_CTRL_C4TX_MIP_C4TX24_09_O24A0_T    mip_c4tx24_09;       // 0xCC93_3024
    MIP_CTRL_C4TX_MIP_C4TX24_10_O24A0_T    mip_c4tx24_10;       // 0xCC93_3028
    MIP_CTRL_C4TX_MIP_C4TX24_11_O24A0_T    mip_c4tx24_11;       // 0xCC93_302C
    MIP_CTRL_C4TX_MIP_C4TX24_12_O24A0_T    mip_c4tx24_12;       // 0xCC93_3030
    MIP_CTRL_C4TX_MIP_C4TX24_13_O24A0_T    mip_c4tx24_13;       // 0xCC93_3034
    MIP_CTRL_C4TX_MIP_C4TX24_14_O24A0_T    mip_c4tx24_14;       // 0xCC93_3038
    MIP_CTRL_C4TX_MIP_C4TX24_15_O24A0_T    mip_c4tx24_15;       // 0xCC93_303C
}MIP_CTRL_C4TX_REG_O24A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MIP_CTRL_C4TX_REG_H_

/* from 'O24_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

