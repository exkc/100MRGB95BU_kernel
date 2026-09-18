#ifndef _IOMUX_CTRL_AUD_REG_O26A0_H_
#define _IOMUX_CTRL_AUD_REG_O26A0_H_

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
    0xCE7B_3000    pad_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_gpio02__ds0       :  1,    //      4
    reg_pad_gpio02__ds1       :  1,    //      5
    reg_pad_gpio02__ds2       :  1,    //      6
    reg_pad_gpio02__ds3       :  1,    //      7
    reg_pad_gpio02__pd        :  1,    //      8
    reg_pad_gpio02__pu        :  1,    //      9
    reg_pad_gpio02__st        :  1,    //     10
    reg_pad_gpio01__ds0       :  1,    //     11
    reg_pad_gpio01__ds1       :  1,    //     12
    reg_pad_gpio01__ds2       :  1,    //     13
    reg_pad_gpio01__ds3       :  1,    //     14
    reg_pad_gpio01__pd        :  1,    //     15
    reg_pad_gpio01__pu        :  1,    //     16
    reg_pad_gpio01__st        :  1,    //     17
    reg_pad_gpio00__ds0       :  1,    //     18
    reg_pad_gpio00__ds1       :  1,    //     19
    reg_pad_gpio00__ds2       :  1,    //     20
    reg_pad_gpio00__ds3       :  1,    //     21
    reg_pad_gpio00__pd        :  1,    //     22
    reg_pad_gpio00__pu        :  1,    //     23
    reg_pad_gpio00__st        :  1,    //     24
    reg_pad_sc_detect__ds0    :  1,    //     25
    reg_pad_sc_detect__ds1    :  1,    //     26
    reg_pad_sc_detect__ds2    :  1,    //     27
    reg_pad_sc_detect__ds3    :  1,    //     28
    reg_pad_sc_detect__pd     :  1,    //     29
    reg_pad_sc_detect__pu     :  1,    //     30
    reg_pad_sc_detect__st     :  1;    //     31
}IOMUX_CTRL_AUD_PAD_AUD00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3004    pad_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_pad_gpio08__ds0       :  1,    //      5
    reg_pad_gpio08__ds1       :  1,    //      6
    reg_pad_gpio08__ds2       :  1,    //      7
    reg_pad_gpio08__ds3       :  1,    //      8
    reg_pad_gpio08__pd        :  1,    //      9
    reg_pad_gpio08__pu        :  1,    //     10
    reg_pad_gpio08__st        :  1,    //     11
    reg_pad_gpio07__ds0       :  1,    //     12
    reg_pad_gpio07__ds1       :  1,    //     13
    reg_pad_gpio07__ds2       :  1,    //     14
    reg_pad_gpio07__ds3       :  1,    //     15
    reg_pad_gpio07__pd        :  1,    //     16
    reg_pad_gpio07__pu        :  1,    //     17
    reg_pad_gpio07__st        :  1,    //     18
    reg_pad_gpio06__ds0       :  1,    //     19
    reg_pad_gpio06__ds1       :  1,    //     20
    reg_pad_gpio06__ds2       :  1,    //     21
    reg_pad_gpio06__pd        :  1,    //     22
    reg_pad_gpio06__pu        :  1,    //     23
    reg_pad_gpio06__smt       :  1,    //     24
    reg_pad_gpio05__ds0       :  1,    //     25
    reg_pad_gpio05__ds1       :  1,    //     26
    reg_pad_gpio05__ds2       :  1,    //     27
    reg_pad_gpio05__ds3       :  1,    //     28
    reg_pad_gpio05__pd        :  1,    //     29
    reg_pad_gpio05__pu        :  1,    //     30
    reg_pad_gpio05__st        :  1;    //     31
}IOMUX_CTRL_AUD_PAD_AUD01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3008    pad_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_gpio12__ds0       :  1,    //      4
    reg_pad_gpio12__ds1       :  1,    //      5
    reg_pad_gpio12__ds2       :  1,    //      6
    reg_pad_gpio12__ds3       :  1,    //      7
    reg_pad_gpio12__pd        :  1,    //      8
    reg_pad_gpio12__pu        :  1,    //      9
    reg_pad_gpio12__st        :  1,    //     10
    reg_pad_gpio11__ds0       :  1,    //     11
    reg_pad_gpio11__ds1       :  1,    //     12
    reg_pad_gpio11__ds2       :  1,    //     13
    reg_pad_gpio11__ds3       :  1,    //     14
    reg_pad_gpio11__pd        :  1,    //     15
    reg_pad_gpio11__pu        :  1,    //     16
    reg_pad_gpio11__st        :  1,    //     17
    reg_pad_gpio10__ds0       :  1,    //     18
    reg_pad_gpio10__ds1       :  1,    //     19
    reg_pad_gpio10__ds2       :  1,    //     20
    reg_pad_gpio10__ds3       :  1,    //     21
    reg_pad_gpio10__pd        :  1,    //     22
    reg_pad_gpio10__pu        :  1,    //     23
    reg_pad_gpio10__st        :  1,    //     24
    reg_pad_gpio09__ds0       :  1,    //     25
    reg_pad_gpio09__ds1       :  1,    //     26
    reg_pad_gpio09__ds2       :  1,    //     27
    reg_pad_gpio09__ds3       :  1,    //     28
    reg_pad_gpio09__pd        :  1,    //     29
    reg_pad_gpio09__pu        :  1,    //     30
    reg_pad_gpio09__st        :  1;    //     31
}IOMUX_CTRL_AUD_PAD_AUD02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_300C    pad_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_pad_gpio16__ds0       :  1,    //      5
    reg_pad_gpio16__ds1       :  1,    //      6
    reg_pad_gpio16__ds2       :  1,    //      7
    reg_pad_gpio16__ds3       :  1,    //      8
    reg_pad_gpio16__pd        :  1,    //      9
    reg_pad_gpio16__pu        :  1,    //     10
    reg_pad_gpio16__st        :  1,    //     11
    reg_pad_gpio15__ds0       :  1,    //     12
    reg_pad_gpio15__ds1       :  1,    //     13
    reg_pad_gpio15__ds2       :  1,    //     14
    reg_pad_gpio15__ds3       :  1,    //     15
    reg_pad_gpio15__pd        :  1,    //     16
    reg_pad_gpio15__pu        :  1,    //     17
    reg_pad_gpio15__st        :  1,    //     18
    reg_pad_gpio14__ds0       :  1,    //     19
    reg_pad_gpio14__ds1       :  1,    //     20
    reg_pad_gpio14__ds2       :  1,    //     21
    reg_pad_gpio14__ds3       :  1,    //     22
    reg_pad_gpio14__pd        :  1,    //     23
    reg_pad_gpio14__pu        :  1,    //     24
    reg_pad_gpio14__st        :  1,    //     25
    reg_pad_gpio13__ds0       :  1,    //     26
    reg_pad_gpio13__ds1       :  1,    //     27
    reg_pad_gpio13__ds2       :  1,    //     28
    reg_pad_gpio13__pd        :  1,    //     29
    reg_pad_gpio13__pu        :  1,    //     30
    reg_pad_gpio13__smt       :  1;    //     31
}IOMUX_CTRL_AUD_PAD_AUD03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3010    pad_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_pad_gpio18__ds0       :  1,    //      2
    reg_pad_gpio18__ds1       :  1,    //      3
    reg_pad_gpio18__ds2       :  1,    //      4
    reg_pad_gpio18__ds3       :  1,    //      5
    reg_pad_gpio18__pd        :  1,    //      6
    reg_pad_gpio18__pu        :  1,    //      7
    reg_pad_gpio18__st        :  1,    //      8
    reg_pad_gpio17__ds0       :  1,    //      9
    reg_pad_gpio17__ds1       :  1,    //     10
    reg_pad_gpio17__ds2       :  1,    //     11
    reg_pad_gpio17__ds3       :  1,    //     12
    reg_pad_gpio17__pd        :  1,    //     13
    reg_pad_gpio17__pu        :  1,    //     14
    reg_pad_gpio17__st        :  1,    //     15
                              : 16;    //  31:16 reserved
}IOMUX_CTRL_AUD_PAD_AUD04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3100    pad_aud64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio08_mux_sel    :  4,    //   3: 0
    reg_pad_gpio07_mux_sel    :  4,    //   7: 4
    reg_pad_gpio06_mux_sel    :  4,    //  11: 8
    reg_pad_gpio05_mux_sel    :  4,    //  15:12
    reg_pad_gpio02_mux_sel    :  4,    //  19:16
    reg_pad_gpio01_mux_sel    :  4,    //  23:20
    reg_pad_gpio00_mux_sel    :  4,    //  27:24
    reg_pad_sc_detect_mux_sel :  4;    //  31:28
}IOMUX_CTRL_AUD_PAD_AUD64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3104    pad_aud65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio16_mux_sel    :  4,    //   3: 0
    reg_pad_gpio15_mux_sel    :  4,    //   7: 4
    reg_pad_gpio14_mux_sel    :  4,    //  11: 8
    reg_pad_gpio13_mux_sel    :  4,    //  15:12
    reg_pad_gpio12_mux_sel    :  4,    //  19:16
    reg_pad_gpio11_mux_sel    :  4,    //  23:20
    reg_pad_gpio10_mux_sel    :  4,    //  27:24
    reg_pad_gpio09_mux_sel    :  4;    //  31:28
}IOMUX_CTRL_AUD_PAD_AUD65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3108    pad_aud66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio18_mux_sel    :  4,    //   3: 0
    reg_pad_gpio17_mux_sel    :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}IOMUX_CTRL_AUD_PAD_AUD66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_AUD_PAD_AUD00_O26A0_T    pad_aud00 ;             // 0xCE7B_3000
    IOMUX_CTRL_AUD_PAD_AUD01_O26A0_T    pad_aud01 ;             // 0xCE7B_3004
    IOMUX_CTRL_AUD_PAD_AUD02_O26A0_T    pad_aud02 ;             // 0xCE7B_3008
    IOMUX_CTRL_AUD_PAD_AUD03_O26A0_T    pad_aud03 ;             // 0xCE7B_300C
    IOMUX_CTRL_AUD_PAD_AUD04_O26A0_T    pad_aud04 ;             // 0xCE7B_3010
    UINT32                             _rsvd_00[59];            // 0xCE7B_3014 ~ 0xCE7B_30FC
    IOMUX_CTRL_AUD_PAD_AUD64_O26A0_T    pad_aud64 ;             // 0xCE7B_3100
    IOMUX_CTRL_AUD_PAD_AUD65_O26A0_T    pad_aud65 ;             // 0xCE7B_3104
    IOMUX_CTRL_AUD_PAD_AUD66_O26A0_T    pad_aud66 ;             // 0xCE7B_3108
}IOMUX_CTRL_AUD_REG_O26A0_T;
/* 8 regs */

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

#define IOMUX_CTRL_AUD_PAD_AUD00_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define IOMUX_CTRL_AUD_PAD_AUD01_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define IOMUX_CTRL_AUD_PAD_AUD02_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define IOMUX_CTRL_AUD_PAD_AUD03_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define IOMUX_CTRL_AUD_PAD_AUD04_O26A0_T_OFF                (BASEADDRESS+0x0010)
#define IOMUX_CTRL_AUD_PAD_AUD64_O26A0_T_OFF                (BASEADDRESS+0x0100)
#define IOMUX_CTRL_AUD_PAD_AUD65_O26A0_T_OFF                (BASEADDRESS+0x0104)
#define IOMUX_CTRL_AUD_PAD_AUD66_O26A0_T_OFF                (BASEADDRESS+0x0108)

/*-----------------------------------------------------------------------------------------
    0xCE7B_3000    pad_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_gpio02__ds0:  1;    //      4
    UINT32 reg_pad_gpio02__ds1:  1;    //      5
    UINT32 reg_pad_gpio02__ds2:  1;    //      6
    UINT32 reg_pad_gpio02__ds3:  1;    //      7
    UINT32 reg_pad_gpio02__pd :  1;    //      8
    UINT32 reg_pad_gpio02__pu :  1;    //      9
    UINT32 reg_pad_gpio02__st :  1;    //     10
    UINT32 reg_pad_gpio01__ds0:  1;    //     11
    UINT32 reg_pad_gpio01__ds1:  1;    //     12
    UINT32 reg_pad_gpio01__ds2:  1;    //     13
    UINT32 reg_pad_gpio01__ds3:  1;    //     14
    UINT32 reg_pad_gpio01__pd :  1;    //     15
    UINT32 reg_pad_gpio01__pu :  1;    //     16
    UINT32 reg_pad_gpio01__st :  1;    //     17
    UINT32 reg_pad_gpio00__ds0:  1;    //     18
    UINT32 reg_pad_gpio00__ds1:  1;    //     19
    UINT32 reg_pad_gpio00__ds2:  1;    //     20
    UINT32 reg_pad_gpio00__ds3:  1;    //     21
    UINT32 reg_pad_gpio00__pd :  1;    //     22
    UINT32 reg_pad_gpio00__pu :  1;    //     23
    UINT32 reg_pad_gpio00__st :  1;    //     24
    UINT32 reg_pad_sc_detect__ds0: 1;    //   25
    UINT32 reg_pad_sc_detect__ds1: 1;    //   26
    UINT32 reg_pad_sc_detect__ds2: 1;    //   27
    UINT32 reg_pad_sc_detect__ds3: 1;    //   28
    UINT32 reg_pad_sc_detect__pd: 1;    //    29
    UINT32 reg_pad_sc_detect__pu: 1;    //    30
    UINT32 reg_pad_sc_detect__st: 1;    //    31
    };
}IOMUX_CTRL_AUD_PAD_AUD00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3004    pad_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_pad_gpio08__ds0:  1;    //      5
    UINT32 reg_pad_gpio08__ds1:  1;    //      6
    UINT32 reg_pad_gpio08__ds2:  1;    //      7
    UINT32 reg_pad_gpio08__ds3:  1;    //      8
    UINT32 reg_pad_gpio08__pd :  1;    //      9
    UINT32 reg_pad_gpio08__pu :  1;    //     10
    UINT32 reg_pad_gpio08__st :  1;    //     11
    UINT32 reg_pad_gpio07__ds0:  1;    //     12
    UINT32 reg_pad_gpio07__ds1:  1;    //     13
    UINT32 reg_pad_gpio07__ds2:  1;    //     14
    UINT32 reg_pad_gpio07__ds3:  1;    //     15
    UINT32 reg_pad_gpio07__pd :  1;    //     16
    UINT32 reg_pad_gpio07__pu :  1;    //     17
    UINT32 reg_pad_gpio07__st :  1;    //     18
    UINT32 reg_pad_gpio06__ds0:  1;    //     19
    UINT32 reg_pad_gpio06__ds1:  1;    //     20
    UINT32 reg_pad_gpio06__ds2:  1;    //     21
    UINT32 reg_pad_gpio06__pd :  1;    //     22
    UINT32 reg_pad_gpio06__pu :  1;    //     23
    UINT32 reg_pad_gpio06__smt:  1;    //     24
    UINT32 reg_pad_gpio05__ds0:  1;    //     25
    UINT32 reg_pad_gpio05__ds1:  1;    //     26
    UINT32 reg_pad_gpio05__ds2:  1;    //     27
    UINT32 reg_pad_gpio05__ds3:  1;    //     28
    UINT32 reg_pad_gpio05__pd :  1;    //     29
    UINT32 reg_pad_gpio05__pu :  1;    //     30
    UINT32 reg_pad_gpio05__st :  1;    //     31
    };
}IOMUX_CTRL_AUD_PAD_AUD01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3008    pad_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_gpio12__ds0:  1;    //      4
    UINT32 reg_pad_gpio12__ds1:  1;    //      5
    UINT32 reg_pad_gpio12__ds2:  1;    //      6
    UINT32 reg_pad_gpio12__ds3:  1;    //      7
    UINT32 reg_pad_gpio12__pd :  1;    //      8
    UINT32 reg_pad_gpio12__pu :  1;    //      9
    UINT32 reg_pad_gpio12__st :  1;    //     10
    UINT32 reg_pad_gpio11__ds0:  1;    //     11
    UINT32 reg_pad_gpio11__ds1:  1;    //     12
    UINT32 reg_pad_gpio11__ds2:  1;    //     13
    UINT32 reg_pad_gpio11__ds3:  1;    //     14
    UINT32 reg_pad_gpio11__pd :  1;    //     15
    UINT32 reg_pad_gpio11__pu :  1;    //     16
    UINT32 reg_pad_gpio11__st :  1;    //     17
    UINT32 reg_pad_gpio10__ds0:  1;    //     18
    UINT32 reg_pad_gpio10__ds1:  1;    //     19
    UINT32 reg_pad_gpio10__ds2:  1;    //     20
    UINT32 reg_pad_gpio10__ds3:  1;    //     21
    UINT32 reg_pad_gpio10__pd :  1;    //     22
    UINT32 reg_pad_gpio10__pu :  1;    //     23
    UINT32 reg_pad_gpio10__st :  1;    //     24
    UINT32 reg_pad_gpio09__ds0:  1;    //     25
    UINT32 reg_pad_gpio09__ds1:  1;    //     26
    UINT32 reg_pad_gpio09__ds2:  1;    //     27
    UINT32 reg_pad_gpio09__ds3:  1;    //     28
    UINT32 reg_pad_gpio09__pd :  1;    //     29
    UINT32 reg_pad_gpio09__pu :  1;    //     30
    UINT32 reg_pad_gpio09__st :  1;    //     31
    };
}IOMUX_CTRL_AUD_PAD_AUD02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_300C    pad_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_pad_gpio16__ds0:  1;    //      5
    UINT32 reg_pad_gpio16__ds1:  1;    //      6
    UINT32 reg_pad_gpio16__ds2:  1;    //      7
    UINT32 reg_pad_gpio16__ds3:  1;    //      8
    UINT32 reg_pad_gpio16__pd :  1;    //      9
    UINT32 reg_pad_gpio16__pu :  1;    //     10
    UINT32 reg_pad_gpio16__st :  1;    //     11
    UINT32 reg_pad_gpio15__ds0:  1;    //     12
    UINT32 reg_pad_gpio15__ds1:  1;    //     13
    UINT32 reg_pad_gpio15__ds2:  1;    //     14
    UINT32 reg_pad_gpio15__ds3:  1;    //     15
    UINT32 reg_pad_gpio15__pd :  1;    //     16
    UINT32 reg_pad_gpio15__pu :  1;    //     17
    UINT32 reg_pad_gpio15__st :  1;    //     18
    UINT32 reg_pad_gpio14__ds0:  1;    //     19
    UINT32 reg_pad_gpio14__ds1:  1;    //     20
    UINT32 reg_pad_gpio14__ds2:  1;    //     21
    UINT32 reg_pad_gpio14__ds3:  1;    //     22
    UINT32 reg_pad_gpio14__pd :  1;    //     23
    UINT32 reg_pad_gpio14__pu :  1;    //     24
    UINT32 reg_pad_gpio14__st :  1;    //     25
    UINT32 reg_pad_gpio13__ds0:  1;    //     26
    UINT32 reg_pad_gpio13__ds1:  1;    //     27
    UINT32 reg_pad_gpio13__ds2:  1;    //     28
    UINT32 reg_pad_gpio13__pd :  1;    //     29
    UINT32 reg_pad_gpio13__pu :  1;    //     30
    UINT32 reg_pad_gpio13__smt:  1;    //     31
    };
}IOMUX_CTRL_AUD_PAD_AUD03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3010    pad_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  2;    //   1: 0 reserved
    UINT32 reg_pad_gpio18__ds0:  1;    //      2
    UINT32 reg_pad_gpio18__ds1:  1;    //      3
    UINT32 reg_pad_gpio18__ds2:  1;    //      4
    UINT32 reg_pad_gpio18__ds3:  1;    //      5
    UINT32 reg_pad_gpio18__pd :  1;    //      6
    UINT32 reg_pad_gpio18__pu :  1;    //      7
    UINT32 reg_pad_gpio18__st :  1;    //      8
    UINT32 reg_pad_gpio17__ds0:  1;    //      9
    UINT32 reg_pad_gpio17__ds1:  1;    //     10
    UINT32 reg_pad_gpio17__ds2:  1;    //     11
    UINT32 reg_pad_gpio17__ds3:  1;    //     12
    UINT32 reg_pad_gpio17__pd :  1;    //     13
    UINT32 reg_pad_gpio17__pu :  1;    //     14
    UINT32 reg_pad_gpio17__st :  1;    //     15
    UINT32 resvd01            : 16;    //  31:16 reserved
    };
}IOMUX_CTRL_AUD_PAD_AUD04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3100    pad_aud64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio08_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio07_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio06_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio05_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio02_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio01_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio00_mux_sel: 4;    //  27:24
    UINT32 reg_pad_sc_detect_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_AUD_PAD_AUD64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3104    pad_aud65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio16_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio15_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio14_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio13_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio12_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio11_mux_sel: 4;    //  23:20
    UINT32 reg_pad_gpio10_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio09_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_AUD_PAD_AUD65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_3108    pad_aud66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio18_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio17_mux_sel: 4;    //  7:4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}IOMUX_CTRL_AUD_PAD_AUD66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_AUD_PAD_AUD00_O26A0_T    pad_aud00 ;             // 0xCE7B_3000
    IOMUX_CTRL_AUD_PAD_AUD01_O26A0_T    pad_aud01 ;             // 0xCE7B_3004
    IOMUX_CTRL_AUD_PAD_AUD02_O26A0_T    pad_aud02 ;             // 0xCE7B_3008
    IOMUX_CTRL_AUD_PAD_AUD03_O26A0_T    pad_aud03 ;             // 0xCE7B_300C
    IOMUX_CTRL_AUD_PAD_AUD04_O26A0_T    pad_aud04 ;             // 0xCE7B_3010
    UINT32                             _rsvd_00[59];            // 0xCE7B_3014 ~ 0xCE7B_30FC
    IOMUX_CTRL_AUD_PAD_AUD64_O26A0_T    pad_aud64 ;             // 0xCE7B_3100
    IOMUX_CTRL_AUD_PAD_AUD65_O26A0_T    pad_aud65 ;             // 0xCE7B_3104
    IOMUX_CTRL_AUD_PAD_AUD66_O26A0_T    pad_aud66 ;             // 0xCE7B_3108
}IOMUX_CTRL_AUD_REG_O26A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_AUD_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

