#ifndef _SCRG_CTRL_ION1_REG_O26A0_H_
#define _SCRG_CTRL_ION1_REG_O26A0_H_

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
    0xC468_0000    crg_ion1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ION1_CRG_ION1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0004    crg_ion1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ION1_CRG_ION1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0008    crg_ion1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_ion1_cicam_clk_gate_en:  1,    //      1
    reg_ion1_main_clk_gate_en :  1,    //      2
    reg_skew_ff_sd0_clk_gate_en: 1,    //      3
    reg_skew_ff_sd1_clk_gate_en: 1,    //      4
    reg_skew_ff_sd2_clk_gate_en: 1,    //      5
    reg_skew_ff_sd3_clk_gate_en: 1,    //      6
    reg_skew_ff_sd4_clk_gate_en: 1,    //      7
    reg_skew_ff_sd5_clk_gate_en: 1,    //      8
    reg_skew_ff_sd6_clk_gate_en: 1,    //      9
    reg_skew_ff_sd7_clk_gate_en: 1,    //     10
    reg_srds_12to3_sd_rx1_clk_gate_en: 1,    //  11
    reg_srds_12to3_sd_tx0_clk_gate_en: 1,    //  12
    reg_srds_12to3_tp_rx1_clk_gate_en: 1,    //  13
    reg_srds_12to3_tp_tx0_clk_gate_en: 1,    //  14
    reg_srds_32to1_sd_rx_clk_gate_en: 1,    //  15
    reg_srds_32to1_sd_tx_clk_gate_en: 1,    //  16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_ION1_CRG_ION1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_000C    crg_ion1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_clk_n    :  1,    //      0
    reg_soft_rst_ion1_n       :  1,    //      1
    reg_soft_rst_skew_ff_sd0_n:  1,    //      2
    reg_soft_rst_skew_ff_sd1_n:  1,    //      3
    reg_soft_rst_skew_ff_sd2_n:  1,    //      4
    reg_soft_rst_skew_ff_sd3_n:  1,    //      5
    reg_soft_rst_skew_ff_sd4_n:  1,    //      6
    reg_soft_rst_skew_ff_sd5_n:  1,    //      7
    reg_soft_rst_skew_ff_sd6_n:  1,    //      8
    reg_soft_rst_skew_ff_sd7_n:  1,    //      9
    reg_soft_rst_srds_12to3_sd_rx1_n: 1,    //  10
    reg_soft_rst_srds_12to3_sd_tx0_n: 1,    //  11
    reg_soft_rst_srds_12to3_tp_rx1_n: 1,    //  12
    reg_soft_rst_srds_12to3_tp_tx0_n: 1,    //  13
    reg_soft_rst_srds_32to1_sd_rx_n: 1,    //  14
    reg_soft_rst_srds_32to1_sd_tx_n: 1,    //  15
                              : 16;    //  31:16 reserved
}SCRG_CTRL_ION1_CRG_ION1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0010    crg_ion1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion1_cicam_clk_sel    :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_ion_sd_12to3_rx1_clk_sel: 1,    //     4
                              :  3,    //   7: 5 reserved
    reg_ion_sd_12to3_tx0_clk_sel: 1,    //     8
                              :  3,    //  11: 9 reserved
    reg_ion_sd_32to1_rx_clk_sel: 1,    //     12
                              :  3,    //  15:13 reserved
    reg_ion_sd_32to1_tx_clk_sel: 1,    //     16
                              :  3,    //  19:17 reserved
    reg_ion_tp_12to3_rx1_clk_sel: 1,    //    20
                              :  3,    //  23:21 reserved
    reg_ion_tp_12to3_tx0_clk_sel: 1,    //    24
                              :  3,    //  27:25 reserved
    reg_skew_ff_sd0_clk_sel   :  1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_ION1_CRG_ION1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0014    crg_ion1005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_skew_ff_sd1_clk_sel   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_skew_ff_sd2_clk_sel   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_skew_ff_sd3_clk_sel   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_skew_ff_sd4_clk_sel   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_skew_ff_sd5_clk_sel   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_skew_ff_sd6_clk_sel   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_skew_ff_sd7_clk_sel   :  1,    //     24
                              :  7;    //  31:25 reserved
}SCRG_CTRL_ION1_CRG_ION1005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ion1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ION1_CRG_ION1000_O26A0_T    crg_ion1000;          // 0xC468_0000
    SCRG_CTRL_ION1_CRG_ION1001_O26A0_T    crg_ion1001;          // 0xC468_0004
    SCRG_CTRL_ION1_CRG_ION1002_O26A0_T    crg_ion1002;          // 0xC468_0008
    SCRG_CTRL_ION1_CRG_ION1003_O26A0_T    crg_ion1003;          // 0xC468_000C
    SCRG_CTRL_ION1_CRG_ION1004_O26A0_T    crg_ion1004;          // 0xC468_0010
    SCRG_CTRL_ION1_CRG_ION1005_O26A0_T    crg_ion1005;          // 0xC468_0014
}SCRG_CTRL_ION1_REG_O26A0_T;
/* 6 regs */

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

#define SCRG_CTRL_ION1_CRG_ION1000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_ION1_CRG_ION1001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_ION1_CRG_ION1002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_ION1_CRG_ION1003_O26A0_T_OFF              (BASEADDRESS+0x000C)
#define SCRG_CTRL_ION1_CRG_ION1004_O26A0_T_OFF              (BASEADDRESS+0x0010)
#define SCRG_CTRL_ION1_CRG_ION1005_O26A0_T_OFF              (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC468_0000    crg_ion1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ION1_CRG_ION1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0004    crg_ion1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ION1_CRG_ION1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0008    crg_ion1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_ion1_cicam_clk_gate_en: 1;    //  1
    UINT32 reg_ion1_main_clk_gate_en: 1;    //  2
    UINT32 reg_skew_ff_sd0_clk_gate_en: 1;    //  3
    UINT32 reg_skew_ff_sd1_clk_gate_en: 1;    //  4
    UINT32 reg_skew_ff_sd2_clk_gate_en: 1;    //  5
    UINT32 reg_skew_ff_sd3_clk_gate_en: 1;    //  6
    UINT32 reg_skew_ff_sd4_clk_gate_en: 1;    //  7
    UINT32 reg_skew_ff_sd5_clk_gate_en: 1;    //  8
    UINT32 reg_skew_ff_sd6_clk_gate_en: 1;    //  9
    UINT32 reg_skew_ff_sd7_clk_gate_en: 1;    //  10
    UINT32 reg_srds_12to3_sd_rx1_clk_gate_en: 1;    //  11
    UINT32 reg_srds_12to3_sd_tx0_clk_gate_en: 1;    //  12
    UINT32 reg_srds_12to3_tp_rx1_clk_gate_en: 1;    //  13
    UINT32 reg_srds_12to3_tp_tx0_clk_gate_en: 1;    //  14
    UINT32 reg_srds_32to1_sd_rx_clk_gate_en: 1;    //  15
    UINT32 reg_srds_32to1_sd_tx_clk_gate_en: 1;    //  16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_ION1_CRG_ION1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_000C    crg_ion1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_clk_n: 1;    //    0
    UINT32 reg_soft_rst_ion1_n:  1;    //      1
    UINT32 reg_soft_rst_skew_ff_sd0_n: 1;    //  2
    UINT32 reg_soft_rst_skew_ff_sd1_n: 1;    //  3
    UINT32 reg_soft_rst_skew_ff_sd2_n: 1;    //  4
    UINT32 reg_soft_rst_skew_ff_sd3_n: 1;    //  5
    UINT32 reg_soft_rst_skew_ff_sd4_n: 1;    //  6
    UINT32 reg_soft_rst_skew_ff_sd5_n: 1;    //  7
    UINT32 reg_soft_rst_skew_ff_sd6_n: 1;    //  8
    UINT32 reg_soft_rst_skew_ff_sd7_n: 1;    //  9
    UINT32 reg_soft_rst_srds_12to3_sd_rx1_n: 1;    //  10
    UINT32 reg_soft_rst_srds_12to3_sd_tx0_n: 1;    //  11
    UINT32 reg_soft_rst_srds_12to3_tp_rx1_n: 1;    //  12
    UINT32 reg_soft_rst_srds_12to3_tp_tx0_n: 1;    //  13
    UINT32 reg_soft_rst_srds_32to1_sd_rx_n: 1;    //  14
    UINT32 reg_soft_rst_srds_32to1_sd_tx_n: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}SCRG_CTRL_ION1_CRG_ION1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0010    crg_ion1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion1_cicam_clk_sel: 2;    //  1:0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_ion_sd_12to3_rx1_clk_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_ion_sd_12to3_tx0_clk_sel: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_ion_sd_32to1_rx_clk_sel: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_ion_sd_32to1_tx_clk_sel: 1;    //  16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_ion_tp_12to3_rx1_clk_sel: 1;    //  20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_ion_tp_12to3_tx0_clk_sel: 1;    //  24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_skew_ff_sd0_clk_sel: 1;    //  28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_ION1_CRG_ION1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC468_0014    crg_ion1005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_skew_ff_sd1_clk_sel: 1;    //   0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_skew_ff_sd2_clk_sel: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_skew_ff_sd3_clk_sel: 1;    //   8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_skew_ff_sd4_clk_sel: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_skew_ff_sd5_clk_sel: 1;    //  16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_skew_ff_sd6_clk_sel: 1;    //  20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_skew_ff_sd7_clk_sel: 1;    //  24
    UINT32 resvd06            :  7;    //  31:25 reserved
    };
}SCRG_CTRL_ION1_CRG_ION1005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ion1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ION1_CRG_ION1000_O26A0_T    crg_ion1000;          // 0xC468_0000
    SCRG_CTRL_ION1_CRG_ION1001_O26A0_T    crg_ion1001;          // 0xC468_0004
    SCRG_CTRL_ION1_CRG_ION1002_O26A0_T    crg_ion1002;          // 0xC468_0008
    SCRG_CTRL_ION1_CRG_ION1003_O26A0_T    crg_ion1003;          // 0xC468_000C
    SCRG_CTRL_ION1_CRG_ION1004_O26A0_T    crg_ion1004;          // 0xC468_0010
    SCRG_CTRL_ION1_CRG_ION1005_O26A0_T    crg_ion1005;          // 0xC468_0014
}SCRG_CTRL_ION1_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_ION1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

