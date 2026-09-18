#ifndef _MCRG_CTRL_CPU_REG_H_
#define _MCRG_CTRL_CPU_REG_H_

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
    0x7_0000    crg_main_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_CPU_CRG_MAIN_CPU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0004    crg_main_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_CPU_CRG_MAIN_CPU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0008    crg_main_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_f27m_clk_inv_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_000C    crg_main_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_stpo_clk_sel          :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0010    crg_main_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_ciout_clk_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0014    crg_main_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0018    crg_main_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_001C    crg_main_cpu07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0020    crg_main_cpu08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0024    crg_main_cpu09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0028    crg_main_cpu10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_002C    crg_main_cpu11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0030    crg_main_cpu12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0034    crg_main_cpu13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_bypass   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0038    crg_main_cpu14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_margin: 2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_003C    crg_main_cpu15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_flt_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0040    crg_main_cpu16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_invsel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0044    crg_main_cpu17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_bypass    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0048    crg_main_cpu18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_margin:  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_004C    crg_main_cpu19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_flt_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0050    crg_main_cpu20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_int_clk_invsel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0054    crg_main_cpu21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0058    crg_main_cpu22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_005C    crg_main_cpu23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0060    crg_main_cpu24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext1_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0064    crg_main_cpu25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0068    crg_main_cpu26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_006C    crg_main_cpu27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0070    crg_main_cpu28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext2_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0074    crg_main_cpu29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_bypass  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0078    crg_main_cpu30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_margin: 2,    //  1: 0
                              : 30;    //   31:2 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_007C    crg_main_cpu31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_flt_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU31_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0080    crg_main_cpu32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_sext3_clk_invsel  :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_CPU_CRG_MAIN_CPU32_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CPU_CRG_MAIN_CPU00_O22A0_T    crg_main_cpu00;      // 0x7_0000
    MCRG_CTRL_CPU_CRG_MAIN_CPU01_O22A0_T    crg_main_cpu01;      // 0x7_0004
    MCRG_CTRL_CPU_CRG_MAIN_CPU02_O22A0_T    crg_main_cpu02;      // 0x7_0008
    MCRG_CTRL_CPU_CRG_MAIN_CPU03_O22A0_T    crg_main_cpu03;      // 0x7_000C
    MCRG_CTRL_CPU_CRG_MAIN_CPU04_O22A0_T    crg_main_cpu04;      // 0x7_0010
    MCRG_CTRL_CPU_CRG_MAIN_CPU05_O22A0_T    crg_main_cpu05;      // 0x7_0014
    MCRG_CTRL_CPU_CRG_MAIN_CPU06_O22A0_T    crg_main_cpu06;      // 0x7_0018
    MCRG_CTRL_CPU_CRG_MAIN_CPU07_O22A0_T    crg_main_cpu07;      // 0x7_001C
    MCRG_CTRL_CPU_CRG_MAIN_CPU08_O22A0_T    crg_main_cpu08;      // 0x7_0020
    MCRG_CTRL_CPU_CRG_MAIN_CPU09_O22A0_T    crg_main_cpu09;      // 0x7_0024
    MCRG_CTRL_CPU_CRG_MAIN_CPU10_O22A0_T    crg_main_cpu10;      // 0x7_0028
    MCRG_CTRL_CPU_CRG_MAIN_CPU11_O22A0_T    crg_main_cpu11;      // 0x7_002C
    MCRG_CTRL_CPU_CRG_MAIN_CPU12_O22A0_T    crg_main_cpu12;      // 0x7_0030
    MCRG_CTRL_CPU_CRG_MAIN_CPU13_O22A0_T    crg_main_cpu13;      // 0x7_0034
    MCRG_CTRL_CPU_CRG_MAIN_CPU14_O22A0_T    crg_main_cpu14;      // 0x7_0038
    MCRG_CTRL_CPU_CRG_MAIN_CPU15_O22A0_T    crg_main_cpu15;      // 0x7_003C
    MCRG_CTRL_CPU_CRG_MAIN_CPU16_O22A0_T    crg_main_cpu16;      // 0x7_0040
    MCRG_CTRL_CPU_CRG_MAIN_CPU17_O22A0_T    crg_main_cpu17;      // 0x7_0044
    MCRG_CTRL_CPU_CRG_MAIN_CPU18_O22A0_T    crg_main_cpu18;      // 0x7_0048
    MCRG_CTRL_CPU_CRG_MAIN_CPU19_O22A0_T    crg_main_cpu19;      // 0x7_004C
    MCRG_CTRL_CPU_CRG_MAIN_CPU20_O22A0_T    crg_main_cpu20;      // 0x7_0050
    MCRG_CTRL_CPU_CRG_MAIN_CPU21_O22A0_T    crg_main_cpu21;      // 0x7_0054
    MCRG_CTRL_CPU_CRG_MAIN_CPU22_O22A0_T    crg_main_cpu22;      // 0x7_0058
    MCRG_CTRL_CPU_CRG_MAIN_CPU23_O22A0_T    crg_main_cpu23;      // 0x7_005C
    MCRG_CTRL_CPU_CRG_MAIN_CPU24_O22A0_T    crg_main_cpu24;      // 0x7_0060
    MCRG_CTRL_CPU_CRG_MAIN_CPU25_O22A0_T    crg_main_cpu25;      // 0x7_0064
    MCRG_CTRL_CPU_CRG_MAIN_CPU26_O22A0_T    crg_main_cpu26;      // 0x7_0068
    MCRG_CTRL_CPU_CRG_MAIN_CPU27_O22A0_T    crg_main_cpu27;      // 0x7_006C
    MCRG_CTRL_CPU_CRG_MAIN_CPU28_O22A0_T    crg_main_cpu28;      // 0x7_0070
    MCRG_CTRL_CPU_CRG_MAIN_CPU29_O22A0_T    crg_main_cpu29;      // 0x7_0074
    MCRG_CTRL_CPU_CRG_MAIN_CPU30_O22A0_T    crg_main_cpu30;      // 0x7_0078
    MCRG_CTRL_CPU_CRG_MAIN_CPU31_O22A0_T    crg_main_cpu31;      // 0x7_007C
    MCRG_CTRL_CPU_CRG_MAIN_CPU32_O22A0_T    crg_main_cpu32;      // 0x7_0080
}MCRG_CTRL_CPU_REG_O22A0_T;
/* 33 regs */

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

#define MCRG_CTRL_CPU_CRG_MAIN_CPU00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU02_O22A0_T_OFF             (BASEADDRESS+0x0008)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU03_O22A0_T_OFF             (BASEADDRESS+0x000C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU04_O22A0_T_OFF             (BASEADDRESS+0x0010)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU05_O22A0_T_OFF             (BASEADDRESS+0x0014)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU06_O22A0_T_OFF             (BASEADDRESS+0x0018)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU07_O22A0_T_OFF             (BASEADDRESS+0x001C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU08_O22A0_T_OFF             (BASEADDRESS+0x0020)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU09_O22A0_T_OFF             (BASEADDRESS+0x0024)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU10_O22A0_T_OFF             (BASEADDRESS+0x0028)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU11_O22A0_T_OFF             (BASEADDRESS+0x002C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU12_O22A0_T_OFF             (BASEADDRESS+0x0030)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU13_O22A0_T_OFF             (BASEADDRESS+0x0034)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU14_O22A0_T_OFF             (BASEADDRESS+0x0038)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU15_O22A0_T_OFF             (BASEADDRESS+0x003C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU16_O22A0_T_OFF             (BASEADDRESS+0x0040)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU17_O22A0_T_OFF             (BASEADDRESS+0x0044)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU18_O22A0_T_OFF             (BASEADDRESS+0x0048)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU19_O22A0_T_OFF             (BASEADDRESS+0x004C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU20_O22A0_T_OFF             (BASEADDRESS+0x0050)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU21_O22A0_T_OFF             (BASEADDRESS+0x0054)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU22_O22A0_T_OFF             (BASEADDRESS+0x0058)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU23_O22A0_T_OFF             (BASEADDRESS+0x005C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU24_O22A0_T_OFF             (BASEADDRESS+0x0060)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU25_O22A0_T_OFF             (BASEADDRESS+0x0064)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU26_O22A0_T_OFF             (BASEADDRESS+0x0068)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU27_O22A0_T_OFF             (BASEADDRESS+0x006C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU28_O22A0_T_OFF             (BASEADDRESS+0x0070)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU29_O22A0_T_OFF             (BASEADDRESS+0x0074)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU30_O22A0_T_OFF             (BASEADDRESS+0x0078)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU31_O22A0_T_OFF             (BASEADDRESS+0x007C)
#define MCRG_CTRL_CPU_CRG_MAIN_CPU32_O22A0_T_OFF             (BASEADDRESS+0x0080)

/*-----------------------------------------------------------------------------------------
    0x7_0000    crg_main_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0004    crg_main_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0008    crg_main_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_f27m_clk_inv_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_000C    crg_main_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_stpo_clk_sel   :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0010    crg_main_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_ciout_clk_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0014    crg_main_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0018    crg_main_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_001C    crg_main_cpu07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0020    crg_main_cpu08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0024    crg_main_cpu09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0028    crg_main_cpu10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_002C    crg_main_cpu11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0030    crg_main_cpu12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0034    crg_main_cpu13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_bypass: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0038    crg_main_cpu14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_003C    crg_main_cpu15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0040    crg_main_cpu16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_invsel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0044    crg_main_cpu17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_bypass: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0048    crg_main_cpu18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_004C    crg_main_cpu19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_flt_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0050    crg_main_cpu20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_int_clk_invsel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0054    crg_main_cpu21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0058    crg_main_cpu22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_005C    crg_main_cpu23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0060    crg_main_cpu24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext1_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0064    crg_main_cpu25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0068    crg_main_cpu26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_006C    crg_main_cpu27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0070    crg_main_cpu28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext2_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0074    crg_main_cpu29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_bypass: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0078    crg_main_cpu30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_margin: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_007C    crg_main_cpu31 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_flt_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU31_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x7_0080    crg_main_cpu32 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_sext3_clk_invsel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_CPU_CRG_MAIN_CPU32_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CPU_CRG_MAIN_CPU00_O22A0_T    crg_main_cpu00;      // 0x7_0000
    MCRG_CTRL_CPU_CRG_MAIN_CPU01_O22A0_T    crg_main_cpu01;      // 0x7_0004
    MCRG_CTRL_CPU_CRG_MAIN_CPU02_O22A0_T    crg_main_cpu02;      // 0x7_0008
    MCRG_CTRL_CPU_CRG_MAIN_CPU03_O22A0_T    crg_main_cpu03;      // 0x7_000C
    MCRG_CTRL_CPU_CRG_MAIN_CPU04_O22A0_T    crg_main_cpu04;      // 0x7_0010
    MCRG_CTRL_CPU_CRG_MAIN_CPU05_O22A0_T    crg_main_cpu05;      // 0x7_0014
    MCRG_CTRL_CPU_CRG_MAIN_CPU06_O22A0_T    crg_main_cpu06;      // 0x7_0018
    MCRG_CTRL_CPU_CRG_MAIN_CPU07_O22A0_T    crg_main_cpu07;      // 0x7_001C
    MCRG_CTRL_CPU_CRG_MAIN_CPU08_O22A0_T    crg_main_cpu08;      // 0x7_0020
    MCRG_CTRL_CPU_CRG_MAIN_CPU09_O22A0_T    crg_main_cpu09;      // 0x7_0024
    MCRG_CTRL_CPU_CRG_MAIN_CPU10_O22A0_T    crg_main_cpu10;      // 0x7_0028
    MCRG_CTRL_CPU_CRG_MAIN_CPU11_O22A0_T    crg_main_cpu11;      // 0x7_002C
    MCRG_CTRL_CPU_CRG_MAIN_CPU12_O22A0_T    crg_main_cpu12;      // 0x7_0030
    MCRG_CTRL_CPU_CRG_MAIN_CPU13_O22A0_T    crg_main_cpu13;      // 0x7_0034
    MCRG_CTRL_CPU_CRG_MAIN_CPU14_O22A0_T    crg_main_cpu14;      // 0x7_0038
    MCRG_CTRL_CPU_CRG_MAIN_CPU15_O22A0_T    crg_main_cpu15;      // 0x7_003C
    MCRG_CTRL_CPU_CRG_MAIN_CPU16_O22A0_T    crg_main_cpu16;      // 0x7_0040
    MCRG_CTRL_CPU_CRG_MAIN_CPU17_O22A0_T    crg_main_cpu17;      // 0x7_0044
    MCRG_CTRL_CPU_CRG_MAIN_CPU18_O22A0_T    crg_main_cpu18;      // 0x7_0048
    MCRG_CTRL_CPU_CRG_MAIN_CPU19_O22A0_T    crg_main_cpu19;      // 0x7_004C
    MCRG_CTRL_CPU_CRG_MAIN_CPU20_O22A0_T    crg_main_cpu20;      // 0x7_0050
    MCRG_CTRL_CPU_CRG_MAIN_CPU21_O22A0_T    crg_main_cpu21;      // 0x7_0054
    MCRG_CTRL_CPU_CRG_MAIN_CPU22_O22A0_T    crg_main_cpu22;      // 0x7_0058
    MCRG_CTRL_CPU_CRG_MAIN_CPU23_O22A0_T    crg_main_cpu23;      // 0x7_005C
    MCRG_CTRL_CPU_CRG_MAIN_CPU24_O22A0_T    crg_main_cpu24;      // 0x7_0060
    MCRG_CTRL_CPU_CRG_MAIN_CPU25_O22A0_T    crg_main_cpu25;      // 0x7_0064
    MCRG_CTRL_CPU_CRG_MAIN_CPU26_O22A0_T    crg_main_cpu26;      // 0x7_0068
    MCRG_CTRL_CPU_CRG_MAIN_CPU27_O22A0_T    crg_main_cpu27;      // 0x7_006C
    MCRG_CTRL_CPU_CRG_MAIN_CPU28_O22A0_T    crg_main_cpu28;      // 0x7_0070
    MCRG_CTRL_CPU_CRG_MAIN_CPU29_O22A0_T    crg_main_cpu29;      // 0x7_0074
    MCRG_CTRL_CPU_CRG_MAIN_CPU30_O22A0_T    crg_main_cpu30;      // 0x7_0078
    MCRG_CTRL_CPU_CRG_MAIN_CPU31_O22A0_T    crg_main_cpu31;      // 0x7_007C
    MCRG_CTRL_CPU_CRG_MAIN_CPU32_O22A0_T    crg_main_cpu32;      // 0x7_0080
}MCRG_CTRL_CPU_REG_O22A0_T;
/* 33 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

