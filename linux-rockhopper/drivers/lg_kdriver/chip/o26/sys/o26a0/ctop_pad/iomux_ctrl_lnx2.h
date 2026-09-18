#ifndef _IOMUX_CTRL_LNX2_REG_O26A0_H_
#define _IOMUX_CTRL_LNX2_REG_O26A0_H_

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
    0xCC60_3000    pad_lnx200 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_gpio22__ds0       :  1,    //      4
    reg_pad_gpio22__ds1       :  1,    //      5
    reg_pad_gpio22__ds2       :  1,    //      6
    reg_pad_gpio22__ds3       :  1,    //      7
    reg_pad_gpio22__pd        :  1,    //      8
    reg_pad_gpio22__pu        :  1,    //      9
    reg_pad_gpio22__st        :  1,    //     10
    reg_pad_gpio21__ds0       :  1,    //     11
    reg_pad_gpio21__ds1       :  1,    //     12
    reg_pad_gpio21__ds2       :  1,    //     13
    reg_pad_gpio21__ds3       :  1,    //     14
    reg_pad_gpio21__pd        :  1,    //     15
    reg_pad_gpio21__pu        :  1,    //     16
    reg_pad_gpio21__st        :  1,    //     17
    reg_pad_gpio20__ds0       :  1,    //     18
    reg_pad_gpio20__ds1       :  1,    //     19
    reg_pad_gpio20__ds2       :  1,    //     20
    reg_pad_gpio20__ds3       :  1,    //     21
    reg_pad_gpio20__pd        :  1,    //     22
    reg_pad_gpio20__pu        :  1,    //     23
    reg_pad_gpio20__st        :  1,    //     24
    reg_pad_gpio19__ds0       :  1,    //     25
    reg_pad_gpio19__ds1       :  1,    //     26
    reg_pad_gpio19__ds2       :  1,    //     27
    reg_pad_gpio19__ds3       :  1,    //     28
    reg_pad_gpio19__pd        :  1,    //     29
    reg_pad_gpio19__pu        :  1,    //     30
    reg_pad_gpio19__st        :  1;    //     31
}IOMUX_CTRL_LNX2_PAD_LNX200_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_3004    pad_lnx201 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_gpio24__ds0       :  1,    //      4
    reg_pad_gpio24__ds1       :  1,    //      5
    reg_pad_gpio24__ds2       :  1,    //      6
    reg_pad_gpio24__pd        :  1,    //      7
    reg_pad_gpio24__pu        :  1,    //      8
    reg_pad_gpio24__smt       :  1,    //      9
    reg_pad_gpio23__ds0       :  1,    //     10
    reg_pad_gpio23__ds1       :  1,    //     11
    reg_pad_gpio23__ds2       :  1,    //     12
    reg_pad_gpio23__pd        :  1,    //     13
    reg_pad_gpio23__pu        :  1,    //     14
    reg_pad_gpio23__smt       :  1,    //     15
                              : 16;    //  31:16 reserved
}IOMUX_CTRL_LNX2_PAD_LNX201_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_3100    pad_lnx264 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_gpio24_mux_sel    :  4,    //   3: 0
    reg_pad_gpio23_mux_sel    :  4,    //   7: 4
    reg_pad_gpio22_mux_sel    :  4,    //  11: 8
    reg_pad_gpio21_mux_sel    :  4,    //  15:12
    reg_pad_gpio20_mux_sel    :  4,    //  19:16
    reg_pad_gpio19_mux_sel    :  4,    //  23:20
                              :  8;    //  31:24 reserved
}IOMUX_CTRL_LNX2_PAD_LNX264_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_LNX2_PAD_LNX200_O26A0_T    pad_lnx200;           // 0xCC60_3000
    IOMUX_CTRL_LNX2_PAD_LNX201_O26A0_T    pad_lnx201;           // 0xCC60_3004
    UINT32                             _rsvd_00[62];            // 0xCC60_3008 ~ 0xCC60_30FC
    IOMUX_CTRL_LNX2_PAD_LNX264_O26A0_T    pad_lnx264;           // 0xCC60_3100
}IOMUX_CTRL_LNX2_REG_O26A0_T;
/* 3 regs */

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

#define IOMUX_CTRL_LNX2_PAD_LNX200_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define IOMUX_CTRL_LNX2_PAD_LNX201_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define IOMUX_CTRL_LNX2_PAD_LNX264_O26A0_T_OFF              (BASEADDRESS+0x0100)

/*-----------------------------------------------------------------------------------------
    0xCC60_3000    pad_lnx200 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_gpio22__ds0:  1;    //      4
    UINT32 reg_pad_gpio22__ds1:  1;    //      5
    UINT32 reg_pad_gpio22__ds2:  1;    //      6
    UINT32 reg_pad_gpio22__ds3:  1;    //      7
    UINT32 reg_pad_gpio22__pd :  1;    //      8
    UINT32 reg_pad_gpio22__pu :  1;    //      9
    UINT32 reg_pad_gpio22__st :  1;    //     10
    UINT32 reg_pad_gpio21__ds0:  1;    //     11
    UINT32 reg_pad_gpio21__ds1:  1;    //     12
    UINT32 reg_pad_gpio21__ds2:  1;    //     13
    UINT32 reg_pad_gpio21__ds3:  1;    //     14
    UINT32 reg_pad_gpio21__pd :  1;    //     15
    UINT32 reg_pad_gpio21__pu :  1;    //     16
    UINT32 reg_pad_gpio21__st :  1;    //     17
    UINT32 reg_pad_gpio20__ds0:  1;    //     18
    UINT32 reg_pad_gpio20__ds1:  1;    //     19
    UINT32 reg_pad_gpio20__ds2:  1;    //     20
    UINT32 reg_pad_gpio20__ds3:  1;    //     21
    UINT32 reg_pad_gpio20__pd :  1;    //     22
    UINT32 reg_pad_gpio20__pu :  1;    //     23
    UINT32 reg_pad_gpio20__st :  1;    //     24
    UINT32 reg_pad_gpio19__ds0:  1;    //     25
    UINT32 reg_pad_gpio19__ds1:  1;    //     26
    UINT32 reg_pad_gpio19__ds2:  1;    //     27
    UINT32 reg_pad_gpio19__ds3:  1;    //     28
    UINT32 reg_pad_gpio19__pd :  1;    //     29
    UINT32 reg_pad_gpio19__pu :  1;    //     30
    UINT32 reg_pad_gpio19__st :  1;    //     31
    };
}IOMUX_CTRL_LNX2_PAD_LNX200_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_3004    pad_lnx201 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_gpio24__ds0:  1;    //      4
    UINT32 reg_pad_gpio24__ds1:  1;    //      5
    UINT32 reg_pad_gpio24__ds2:  1;    //      6
    UINT32 reg_pad_gpio24__pd :  1;    //      7
    UINT32 reg_pad_gpio24__pu :  1;    //      8
    UINT32 reg_pad_gpio24__smt:  1;    //      9
    UINT32 reg_pad_gpio23__ds0:  1;    //     10
    UINT32 reg_pad_gpio23__ds1:  1;    //     11
    UINT32 reg_pad_gpio23__ds2:  1;    //     12
    UINT32 reg_pad_gpio23__pd :  1;    //     13
    UINT32 reg_pad_gpio23__pu :  1;    //     14
    UINT32 reg_pad_gpio23__smt:  1;    //     15
    UINT32 resvd01            : 16;    //  31:16 reserved
    };
}IOMUX_CTRL_LNX2_PAD_LNX201_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC60_3100    pad_lnx264 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_gpio24_mux_sel: 4;    //  3:0
    UINT32 reg_pad_gpio23_mux_sel: 4;    //  7:4
    UINT32 reg_pad_gpio22_mux_sel: 4;    //  11:8
    UINT32 reg_pad_gpio21_mux_sel: 4;    //  15:12
    UINT32 reg_pad_gpio20_mux_sel: 4;    //  19:16
    UINT32 reg_pad_gpio19_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}IOMUX_CTRL_LNX2_PAD_LNX264_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_LNX2_PAD_LNX200_O26A0_T    pad_lnx200;           // 0xCC60_3000
    IOMUX_CTRL_LNX2_PAD_LNX201_O26A0_T    pad_lnx201;           // 0xCC60_3004
    UINT32                             _rsvd_00[62];            // 0xCC60_3008 ~ 0xCC60_30FC
    IOMUX_CTRL_LNX2_PAD_LNX264_O26A0_T    pad_lnx264;           // 0xCC60_3100
}IOMUX_CTRL_LNX2_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_LNX2_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

