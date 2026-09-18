#ifndef _MIP_CTRL_C4TX_M23A0_REG_H_
#define _MIP_CTRL_C4TX_M23A0_REG_H_

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
    0xCC53_2000    mip_c4tx12_00 ''
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
}MIP_CTRL_C4TX_MIP_C4TX12_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2004    mip_c4tx12_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_intr_polar_high_en: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_c4_vx1_intr_edge_en   :  1,    //      4
    reg_c4_vx1_intr_clear     :  1,    //      5
    reg_c4_vx1_lockn_intr_en  :  1,    //      6
                              : 25;    //   31:7 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2008    mip_c4tx12_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vx1_lockn_main_counter: 4,    //  3:0
    reg_c4_vx1_lockn_main_counter_clear: 1,    //  4
    reg_c4_vx1_lockn_main_counter_rising_edge: 1,    //  5
                              : 26;    //   31:6 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_200C    mip_c4tx12_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_epi_lock_tomain    :  1,    //      0
    reg_c4_vx1_lockn_tomain   :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2010    mip_c4tx12_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ext_reg_wrdata     :  8,    //   7: 0
    reg_c4_ext_reg_addr       :  8,    //  15: 8
    reg_c4_ext_reg_wr_en      :  1,    //     16
                              :  7,    //  23:17 reserved
    reg_c4_ext_reg_rstn       :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2014    mip_c4tx12_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link0_ext_reg_en   :  1,    //      0
    reg_c4_link1_ext_reg_en   :  1,    //      1
    reg_c4_link2_ext_reg_en   :  1,    //      2
                              :  1,    //      3 reserved
    reg_c4_pll_ext_reg_en     :  1,    //      4
                              : 27;    //   31:5 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2018    mip_c4tx12_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link2_ext_reg_rddata   :  8,    //   7: 0
    c4_link1_ext_reg_rddata   :  8,    //  15: 8
    c4_link0_ext_reg_rddata   :  8,    //  23:16
    c4_pll_ext_reg_rddata     :  8;    //  31:24
}MIP_CTRL_C4TX_MIP_C4TX12_06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_201C    mip_c4tx12_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pll_rstn_g             :  1,    //      0
    c4_pll_lock               :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2020    mip_c4tx12_08 ''
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
                              : 12,    //  23:12 reserved
    reg_c4_pdb                :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2024    mip_c4tx12_09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di2           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2028    mip_c4tx12_10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di1           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_10_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_202C    mip_c4tx12_11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di0           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}MIP_CTRL_C4TX_MIP_C4TX12_11_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX_MIP_C4TX12_00_M23A0_T    mip_c4tx12_00;       // 0xCC53_2000
    MIP_CTRL_C4TX_MIP_C4TX12_01_M23A0_T    mip_c4tx12_01;       // 0xCC53_2004
    MIP_CTRL_C4TX_MIP_C4TX12_02_M23A0_T    mip_c4tx12_02;       // 0xCC53_2008
    MIP_CTRL_C4TX_MIP_C4TX12_03_M23A0_T    mip_c4tx12_03;       // 0xCC53_200C
    MIP_CTRL_C4TX_MIP_C4TX12_04_M23A0_T    mip_c4tx12_04;       // 0xCC53_2010
    MIP_CTRL_C4TX_MIP_C4TX12_05_M23A0_T    mip_c4tx12_05;       // 0xCC53_2014
    MIP_CTRL_C4TX_MIP_C4TX12_06_M23A0_T    mip_c4tx12_06;       // 0xCC53_2018
    MIP_CTRL_C4TX_MIP_C4TX12_07_M23A0_T    mip_c4tx12_07;       // 0xCC53_201C
    MIP_CTRL_C4TX_MIP_C4TX12_08_M23A0_T    mip_c4tx12_08;       // 0xCC53_2020
    MIP_CTRL_C4TX_MIP_C4TX12_09_M23A0_T    mip_c4tx12_09;       // 0xCC53_2024
    MIP_CTRL_C4TX_MIP_C4TX12_10_M23A0_T    mip_c4tx12_10;       // 0xCC53_2028
    MIP_CTRL_C4TX_MIP_C4TX12_11_M23A0_T    mip_c4tx12_11;       // 0xCC53_202C
}MIP_CTRL_C4TX_REG_M23A0_T;
/* 12 regs */

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

#define MIP_CTRL_C4TX_MIP_C4TX12_00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define MIP_CTRL_C4TX_MIP_C4TX12_01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define MIP_CTRL_C4TX_MIP_C4TX12_02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define MIP_CTRL_C4TX_MIP_C4TX12_03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define MIP_CTRL_C4TX_MIP_C4TX12_04_M23A0_T_OFF             (BASEADDRESS+0x0010)
#define MIP_CTRL_C4TX_MIP_C4TX12_05_M23A0_T_OFF             (BASEADDRESS+0x0014)
#define MIP_CTRL_C4TX_MIP_C4TX12_06_M23A0_T_OFF             (BASEADDRESS+0x0018)
#define MIP_CTRL_C4TX_MIP_C4TX12_07_M23A0_T_OFF             (BASEADDRESS+0x001C)
#define MIP_CTRL_C4TX_MIP_C4TX12_08_M23A0_T_OFF             (BASEADDRESS+0x0020)
#define MIP_CTRL_C4TX_MIP_C4TX12_09_M23A0_T_OFF             (BASEADDRESS+0x0024)
#define MIP_CTRL_C4TX_MIP_C4TX12_10_M23A0_T_OFF             (BASEADDRESS+0x0028)
#define MIP_CTRL_C4TX_MIP_C4TX12_11_M23A0_T_OFF             (BASEADDRESS+0x002C)

/*-----------------------------------------------------------------------------------------
    0xCC53_2000    mip_c4tx12_00 ''
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
}MIP_CTRL_C4TX_MIP_C4TX12_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2004    mip_c4tx12_01 ''
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
}MIP_CTRL_C4TX_MIP_C4TX12_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2008    mip_c4tx12_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_vx1_lockn_main_counter: 4;    //  3:0
    UINT32 reg_c4_vx1_lockn_main_counter_clear: 1;    //  4
    UINT32 reg_c4_vx1_lockn_main_counter_rising_edge: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_200C    mip_c4tx12_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_epi_lock_tomain: 1;    //    0
    UINT32 reg_c4_vx1_lockn_tomain: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2010    mip_c4tx12_04 ''
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
}MIP_CTRL_C4TX_MIP_C4TX12_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2014    mip_c4tx12_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_link0_ext_reg_en: 1;    //   0
    UINT32 reg_c4_link1_ext_reg_en: 1;    //   1
    UINT32 reg_c4_link2_ext_reg_en: 1;    //   2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_c4_pll_ext_reg_en: 1;    //     4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2018    mip_c4tx12_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_link2_ext_reg_rddata: 8;    //  7:0
    UINT32 c4_link1_ext_reg_rddata: 8;    //  15:8
    UINT32 c4_link0_ext_reg_rddata: 8;    //  23:16
    UINT32 c4_pll_ext_reg_rddata: 8;    //  31:24
    };
}MIP_CTRL_C4TX_MIP_C4TX12_06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_201C    mip_c4tx12_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 c4_pll_rstn_g      :  1;    //      0
    UINT32 c4_pll_lock        :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2020    mip_c4tx12_08 ''
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
    UINT32 resvd00            : 12;    //  23:12 reserved
    UINT32 reg_c4_pdb         :  1;    //     24
    UINT32 resvd01            :  7;    //  31:25 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_08_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2024    mip_c4tx12_09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di2    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_09_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_2028    mip_c4tx12_10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di1    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_10_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_202C    mip_c4tx12_11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4_test_di0    : 28;    //  27: 0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MIP_CTRL_C4TX_MIP_C4TX12_11_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_c4tx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_C4TX_MIP_C4TX12_00_M23A0_T    mip_c4tx12_00;       // 0xCC53_2000
    MIP_CTRL_C4TX_MIP_C4TX12_01_M23A0_T    mip_c4tx12_01;       // 0xCC53_2004
    MIP_CTRL_C4TX_MIP_C4TX12_02_M23A0_T    mip_c4tx12_02;       // 0xCC53_2008
    MIP_CTRL_C4TX_MIP_C4TX12_03_M23A0_T    mip_c4tx12_03;       // 0xCC53_200C
    MIP_CTRL_C4TX_MIP_C4TX12_04_M23A0_T    mip_c4tx12_04;       // 0xCC53_2010
    MIP_CTRL_C4TX_MIP_C4TX12_05_M23A0_T    mip_c4tx12_05;       // 0xCC53_2014
    MIP_CTRL_C4TX_MIP_C4TX12_06_M23A0_T    mip_c4tx12_06;       // 0xCC53_2018
    MIP_CTRL_C4TX_MIP_C4TX12_07_M23A0_T    mip_c4tx12_07;       // 0xCC53_201C
    MIP_CTRL_C4TX_MIP_C4TX12_08_M23A0_T    mip_c4tx12_08;       // 0xCC53_2020
    MIP_CTRL_C4TX_MIP_C4TX12_09_M23A0_T    mip_c4tx12_09;       // 0xCC53_2024
    MIP_CTRL_C4TX_MIP_C4TX12_10_M23A0_T    mip_c4tx12_10;       // 0xCC53_2028
    MIP_CTRL_C4TX_MIP_C4TX12_11_M23A0_T    mip_c4tx12_11;       // 0xCC53_202C
}MIP_CTRL_C4TX_REG_M23A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

