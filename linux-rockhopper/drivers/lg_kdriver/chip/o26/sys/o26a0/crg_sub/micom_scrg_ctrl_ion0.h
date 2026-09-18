#ifndef _MICOM_SCRG_CTRL_ION0_REG_O26A0_H_
#define _MICOM_SCRG_CTRL_ION0_REG_O26A0_H_

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
    0xF334_0000    crg_ion0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_SCRG_CTRL_ION0_CRG_ION0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0004    crg_ion0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_SCRG_CTRL_ION0_CRG_ION0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0008    crg_ion0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_ion0_main_clk_gate_en :  1,    //      1
    reg_skew_ff_sd0_clk_gate_en: 1,    //      2
    reg_skew_ff_sd1_clk_gate_en: 1,    //      3
    reg_skew_ff_sd2_clk_gate_en: 1,    //      4
    reg_skew_ff_sd3_clk_gate_en: 1,    //      5
    reg_skew_ff_sd4_clk_gate_en: 1,    //      6
    reg_skew_ff_sd5_clk_gate_en: 1,    //      7
    reg_skew_ff_sd6_clk_gate_en: 1,    //      8
    reg_skew_ff_sd7_clk_gate_en: 1,    //      9
    reg_srds_12to3_sd_rx0_clk_gate_en: 1,    //  10
    reg_srds_12to3_sd_rx1_clk_gate_en: 1,    //  11
    reg_srds_12to3_tp_rx0_clk_gate_en: 1,    //  12
    reg_srds_12to3_tp_rx1_clk_gate_en: 1,    //  13
    reg_srds_32to1_sd_rx0_clk_gate_en: 1,    //  14
    reg_srds_32to1_sd_rx1_clk_gate_en: 1,    //  15
    reg_srds_32to1_sd_tx0_clk_gate_en: 1,    //  16
    reg_srds_32to1_sd_tx1_clk_gate_en: 1,    //  17
                              : 14;    //  31:18 reserved
}MICOM_SCRG_CTRL_ION0_CRG_ION0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_000C    crg_ion0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_clk_n    :  1,    //      0
    reg_soft_rst_ion0_n       :  1,    //      1
    reg_soft_rst_skew_ff_sd0_n:  1,    //      2
    reg_soft_rst_skew_ff_sd1_n:  1,    //      3
    reg_soft_rst_skew_ff_sd2_n:  1,    //      4
    reg_soft_rst_skew_ff_sd3_n:  1,    //      5
    reg_soft_rst_skew_ff_sd4_n:  1,    //      6
    reg_soft_rst_skew_ff_sd5_n:  1,    //      7
    reg_soft_rst_skew_ff_sd6_n:  1,    //      8
    reg_soft_rst_skew_ff_sd7_n:  1,    //      9
    reg_soft_rst_srds_12to3_sd_rx0_n: 1,    //  10
    reg_soft_rst_srds_12to3_sd_rx1_n: 1,    //  11
    reg_soft_rst_srds_12to3_tp_rx0_n: 1,    //  12
    reg_soft_rst_srds_12to3_tp_rx1_n: 1,    //  13
    reg_soft_rst_srds_32to1_sd_rx0_n: 1,    //  14
    reg_soft_rst_srds_32to1_sd_rx1_n: 1,    //  15
    reg_soft_rst_srds_32to1_sd_tx0_n: 1,    //  16
    reg_soft_rst_srds_32to1_sd_tx1_n: 1,    //  17
                              : 14;    //  31:18 reserved
}MICOM_SCRG_CTRL_ION0_CRG_ION0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0010    crg_ion0004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_skew_ff_sd0_clk_sel   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_skew_ff_sd1_clk_sel   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_skew_ff_sd2_clk_sel   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_skew_ff_sd3_clk_sel   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_skew_ff_sd4_clk_sel   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_skew_ff_sd5_clk_sel   :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_skew_ff_sd6_clk_sel   :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_skew_ff_sd7_clk_sel   :  1,    //     28
                              :  3;    //  31:29 reserved
}MICOM_SCRG_CTRL_ION0_CRG_ION0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0014    crg_ion0005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_srds_12to3_sd_rx0_clk_sel: 1,    //    0
                              :  3,    //   3: 1 reserved
    reg_srds_12to3_sd_rx1_clk_sel: 1,    //    4
                              :  3,    //   7: 5 reserved
    reg_srds_12to3_tp_rx0_clk_sel: 2,    //  9:8
                              :  2,    //  11:10 reserved
    reg_srds_12to3_tp_rx1_clk_sel: 2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_srds_32to1_sd_rx0_clk_sel: 1,    //   16
                              :  3,    //  19:17 reserved
    reg_srds_32to1_sd_rx1_clk_sel: 1,    //   20
                              :  3,    //  23:21 reserved
    reg_srds_32to1_sd_tx0_clk_sel: 1,    //   24
                              :  3,    //  27:25 reserved
    reg_srds_32to1_sd_tx1_clk_sel: 1,    //   28
                              :  3;    //  31:29 reserved
}MICOM_SCRG_CTRL_ION0_CRG_ION0005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_ion0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_ION0_CRG_ION0000_O26A0_T    crg_ion0000;    // 0xF334_0000
    MICOM_SCRG_CTRL_ION0_CRG_ION0001_O26A0_T    crg_ion0001;    // 0xF334_0004
    MICOM_SCRG_CTRL_ION0_CRG_ION0002_O26A0_T    crg_ion0002;    // 0xF334_0008
    MICOM_SCRG_CTRL_ION0_CRG_ION0003_O26A0_T    crg_ion0003;    // 0xF334_000C
    MICOM_SCRG_CTRL_ION0_CRG_ION0004_O26A0_T    crg_ion0004;    // 0xF334_0010
    MICOM_SCRG_CTRL_ION0_CRG_ION0005_O26A0_T    crg_ion0005;    // 0xF334_0014
}MICOM_SCRG_CTRL_ION0_REG_O26A0_T;
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

#define MICOM_SCRG_CTRL_ION0_CRG_ION0000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define MICOM_SCRG_CTRL_ION0_CRG_ION0001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define MICOM_SCRG_CTRL_ION0_CRG_ION0002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define MICOM_SCRG_CTRL_ION0_CRG_ION0003_O26A0_T_OFF        (BASEADDRESS+0x000C)
#define MICOM_SCRG_CTRL_ION0_CRG_ION0004_O26A0_T_OFF        (BASEADDRESS+0x0010)
#define MICOM_SCRG_CTRL_ION0_CRG_ION0005_O26A0_T_OFF        (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xF334_0000    crg_ion0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0004    crg_ion0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0008    crg_ion0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_ion0_main_clk_gate_en: 1;    //  1
    UINT32 reg_skew_ff_sd0_clk_gate_en: 1;    //  2
    UINT32 reg_skew_ff_sd1_clk_gate_en: 1;    //  3
    UINT32 reg_skew_ff_sd2_clk_gate_en: 1;    //  4
    UINT32 reg_skew_ff_sd3_clk_gate_en: 1;    //  5
    UINT32 reg_skew_ff_sd4_clk_gate_en: 1;    //  6
    UINT32 reg_skew_ff_sd5_clk_gate_en: 1;    //  7
    UINT32 reg_skew_ff_sd6_clk_gate_en: 1;    //  8
    UINT32 reg_skew_ff_sd7_clk_gate_en: 1;    //  9
    UINT32 reg_srds_12to3_sd_rx0_clk_gate_en: 1;    //  10
    UINT32 reg_srds_12to3_sd_rx1_clk_gate_en: 1;    //  11
    UINT32 reg_srds_12to3_tp_rx0_clk_gate_en: 1;    //  12
    UINT32 reg_srds_12to3_tp_rx1_clk_gate_en: 1;    //  13
    UINT32 reg_srds_32to1_sd_rx0_clk_gate_en: 1;    //  14
    UINT32 reg_srds_32to1_sd_rx1_clk_gate_en: 1;    //  15
    UINT32 reg_srds_32to1_sd_tx0_clk_gate_en: 1;    //  16
    UINT32 reg_srds_32to1_sd_tx1_clk_gate_en: 1;    //  17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_000C    crg_ion0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_clk_n: 1;    //    0
    UINT32 reg_soft_rst_ion0_n:  1;    //      1
    UINT32 reg_soft_rst_skew_ff_sd0_n: 1;    //  2
    UINT32 reg_soft_rst_skew_ff_sd1_n: 1;    //  3
    UINT32 reg_soft_rst_skew_ff_sd2_n: 1;    //  4
    UINT32 reg_soft_rst_skew_ff_sd3_n: 1;    //  5
    UINT32 reg_soft_rst_skew_ff_sd4_n: 1;    //  6
    UINT32 reg_soft_rst_skew_ff_sd5_n: 1;    //  7
    UINT32 reg_soft_rst_skew_ff_sd6_n: 1;    //  8
    UINT32 reg_soft_rst_skew_ff_sd7_n: 1;    //  9
    UINT32 reg_soft_rst_srds_12to3_sd_rx0_n: 1;    //  10
    UINT32 reg_soft_rst_srds_12to3_sd_rx1_n: 1;    //  11
    UINT32 reg_soft_rst_srds_12to3_tp_rx0_n: 1;    //  12
    UINT32 reg_soft_rst_srds_12to3_tp_rx1_n: 1;    //  13
    UINT32 reg_soft_rst_srds_32to1_sd_rx0_n: 1;    //  14
    UINT32 reg_soft_rst_srds_32to1_sd_rx1_n: 1;    //  15
    UINT32 reg_soft_rst_srds_32to1_sd_tx0_n: 1;    //  16
    UINT32 reg_soft_rst_srds_32to1_sd_tx1_n: 1;    //  17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0010    crg_ion0004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_skew_ff_sd0_clk_sel: 1;    //   0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_skew_ff_sd1_clk_sel: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_skew_ff_sd2_clk_sel: 1;    //   8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_skew_ff_sd3_clk_sel: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_skew_ff_sd4_clk_sel: 1;    //  16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_skew_ff_sd5_clk_sel: 1;    //  20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_skew_ff_sd6_clk_sel: 1;    //  24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_skew_ff_sd7_clk_sel: 1;    //  28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF334_0014    crg_ion0005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_srds_12to3_sd_rx0_clk_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_srds_12to3_sd_rx1_clk_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_srds_12to3_tp_rx0_clk_sel: 2;    //  9:8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_srds_12to3_tp_rx1_clk_sel: 2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_srds_32to1_sd_rx0_clk_sel: 1;    //  16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_srds_32to1_sd_rx1_clk_sel: 1;    //  20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_srds_32to1_sd_tx0_clk_sel: 1;    //  24
    UINT32 resvd06            :  3;    //  27:25 reserved
    UINT32 reg_srds_32to1_sd_tx1_clk_sel: 1;    //  28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}MICOM_SCRG_CTRL_ION0_CRG_ION0005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_ion0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_ION0_CRG_ION0000_O26A0_T    crg_ion0000;    // 0xF334_0000
    MICOM_SCRG_CTRL_ION0_CRG_ION0001_O26A0_T    crg_ion0001;    // 0xF334_0004
    MICOM_SCRG_CTRL_ION0_CRG_ION0002_O26A0_T    crg_ion0002;    // 0xF334_0008
    MICOM_SCRG_CTRL_ION0_CRG_ION0003_O26A0_T    crg_ion0003;    // 0xF334_000C
    MICOM_SCRG_CTRL_ION0_CRG_ION0004_O26A0_T    crg_ion0004;    // 0xF334_0010
    MICOM_SCRG_CTRL_ION0_CRG_ION0005_O26A0_T    crg_ion0005;    // 0xF334_0014
}MICOM_SCRG_CTRL_ION0_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_SCRG_CTRL_ION0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

