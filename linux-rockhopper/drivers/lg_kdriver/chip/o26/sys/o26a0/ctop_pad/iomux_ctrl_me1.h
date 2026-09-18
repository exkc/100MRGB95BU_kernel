#ifndef _IOMUX_CTRL_ME1_REG_O26A0_H_
#define _IOMUX_CTRL_ME1_REG_O26A0_H_

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
    0xCCCF_3000    pad_me100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_dim1_sclk__ds0    :  1,    //      4
    reg_pad_dim1_sclk__ds1    :  1,    //      5
    reg_pad_dim1_sclk__ds2    :  1,    //      6
    reg_pad_dim1_sclk__ds3    :  1,    //      7
    reg_pad_dim1_sclk__pd     :  1,    //      8
    reg_pad_dim1_sclk__pu     :  1,    //      9
    reg_pad_dim1_sclk__st     :  1,    //     10
    reg_pad_dim1_mosi__ds0    :  1,    //     11
    reg_pad_dim1_mosi__ds1    :  1,    //     12
    reg_pad_dim1_mosi__ds2    :  1,    //     13
    reg_pad_dim1_mosi__ds3    :  1,    //     14
    reg_pad_dim1_mosi__pd     :  1,    //     15
    reg_pad_dim1_mosi__pu     :  1,    //     16
    reg_pad_dim1_mosi__st     :  1,    //     17
    reg_pad_dim0_sclk__ds0    :  1,    //     18
    reg_pad_dim0_sclk__ds1    :  1,    //     19
    reg_pad_dim0_sclk__ds2    :  1,    //     20
    reg_pad_dim0_sclk__ds3    :  1,    //     21
    reg_pad_dim0_sclk__pd     :  1,    //     22
    reg_pad_dim0_sclk__pu     :  1,    //     23
    reg_pad_dim0_sclk__st     :  1,    //     24
    reg_pad_dim0_mosi__ds0    :  1,    //     25
    reg_pad_dim0_mosi__ds1    :  1,    //     26
    reg_pad_dim0_mosi__ds2    :  1,    //     27
    reg_pad_dim0_mosi__ds3    :  1,    //     28
    reg_pad_dim0_mosi__pd     :  1,    //     29
    reg_pad_dim0_mosi__pu     :  1,    //     30
    reg_pad_dim0_mosi__st     :  1;    //     31
}IOMUX_CTRL_ME1_PAD_ME100_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3004    pad_me101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_pad_dim3_sclk__ds0    :  1,    //      6
    reg_pad_dim3_sclk__ds1    :  1,    //      7
    reg_pad_dim3_sclk__ds2    :  1,    //      8
    reg_pad_dim3_sclk__pd     :  1,    //      9
    reg_pad_dim3_sclk__pu     :  1,    //     10
    reg_pad_dim3_sclk__smt    :  1,    //     11
    reg_pad_dim3_mosi__ds0    :  1,    //     12
    reg_pad_dim3_mosi__ds1    :  1,    //     13
    reg_pad_dim3_mosi__ds2    :  1,    //     14
    reg_pad_dim3_mosi__pd     :  1,    //     15
    reg_pad_dim3_mosi__pu     :  1,    //     16
    reg_pad_dim3_mosi__smt    :  1,    //     17
    reg_pad_dim2_sclk__ds0    :  1,    //     18
    reg_pad_dim2_sclk__ds1    :  1,    //     19
    reg_pad_dim2_sclk__ds2    :  1,    //     20
    reg_pad_dim2_sclk__ds3    :  1,    //     21
    reg_pad_dim2_sclk__pd     :  1,    //     22
    reg_pad_dim2_sclk__pu     :  1,    //     23
    reg_pad_dim2_sclk__st     :  1,    //     24
    reg_pad_dim2_mosi__ds0    :  1,    //     25
    reg_pad_dim2_mosi__ds1    :  1,    //     26
    reg_pad_dim2_mosi__ds2    :  1,    //     27
    reg_pad_dim2_mosi__ds3    :  1,    //     28
    reg_pad_dim2_mosi__pd     :  1,    //     29
    reg_pad_dim2_mosi__pu     :  1,    //     30
    reg_pad_dim2_mosi__st     :  1;    //     31
}IOMUX_CTRL_ME1_PAD_ME101_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3008    pad_me102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_pad_ld_vs_out3__ds0   :  1,    //      6
    reg_pad_ld_vs_out3__ds1   :  1,    //      7
    reg_pad_ld_vs_out3__ds2   :  1,    //      8
    reg_pad_ld_vs_out3__ds3   :  1,    //      9
    reg_pad_ld_vs_out3__pd    :  1,    //     10
    reg_pad_ld_vs_out3__pu    :  1,    //     11
    reg_pad_ld_vs_out3__st    :  1,    //     12
    reg_pad_ld_vs_out2__ds0   :  1,    //     13
    reg_pad_ld_vs_out2__ds1   :  1,    //     14
    reg_pad_ld_vs_out2__ds2   :  1,    //     15
    reg_pad_ld_vs_out2__ds3   :  1,    //     16
    reg_pad_ld_vs_out2__pd    :  1,    //     17
    reg_pad_ld_vs_out2__pu    :  1,    //     18
    reg_pad_ld_vs_out2__st    :  1,    //     19
    reg_pad_ld_vs_out1__ds0   :  1,    //     20
    reg_pad_ld_vs_out1__ds1   :  1,    //     21
    reg_pad_ld_vs_out1__ds2   :  1,    //     22
    reg_pad_ld_vs_out1__pd    :  1,    //     23
    reg_pad_ld_vs_out1__pu    :  1,    //     24
    reg_pad_ld_vs_out1__smt   :  1,    //     25
    reg_pad_ld_vs_out0__ds0   :  1,    //     26
    reg_pad_ld_vs_out0__ds1   :  1,    //     27
    reg_pad_ld_vs_out0__ds2   :  1,    //     28
    reg_pad_ld_vs_out0__pd    :  1,    //     29
    reg_pad_ld_vs_out0__pu    :  1,    //     30
    reg_pad_ld_vs_out0__smt   :  1;    //     31
}IOMUX_CTRL_ME1_PAD_ME102_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3100    pad_me164 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim3_sclk_mux_sel :  4,    //   3: 0
    reg_pad_dim3_mosi_mux_sel :  4,    //   7: 4
    reg_pad_dim2_sclk_mux_sel :  4,    //  11: 8
    reg_pad_dim2_mosi_mux_sel :  4,    //  15:12
    reg_pad_dim1_sclk_mux_sel :  4,    //  19:16
    reg_pad_dim1_mosi_mux_sel :  4,    //  23:20
    reg_pad_dim0_sclk_mux_sel :  4,    //  27:24
    reg_pad_dim0_mosi_mux_sel :  4;    //  31:28
}IOMUX_CTRL_ME1_PAD_ME164_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3104    pad_me165 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ld_vs_out3_mux_sel:  4,    //   3: 0
    reg_pad_ld_vs_out2_mux_sel:  4,    //   7: 4
    reg_pad_ld_vs_out1_mux_sel:  4,    //  11: 8
    reg_pad_ld_vs_out0_mux_sel:  4,    //  15:12
                              : 16;    //  31:16 reserved
}IOMUX_CTRL_ME1_PAD_ME165_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_ME1_PAD_ME100_O26A0_T    pad_me100 ;             // 0xCCCF_3000
    IOMUX_CTRL_ME1_PAD_ME101_O26A0_T    pad_me101 ;             // 0xCCCF_3004
    IOMUX_CTRL_ME1_PAD_ME102_O26A0_T    pad_me102 ;             // 0xCCCF_3008
    UINT32                             _rsvd_00[61];            // 0xCCCF_300C ~ 0xCCCF_30FC
    IOMUX_CTRL_ME1_PAD_ME164_O26A0_T    pad_me164 ;             // 0xCCCF_3100
    IOMUX_CTRL_ME1_PAD_ME165_O26A0_T    pad_me165 ;             // 0xCCCF_3104
}IOMUX_CTRL_ME1_REG_O26A0_T;
/* 5 regs */

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

#define IOMUX_CTRL_ME1_PAD_ME100_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define IOMUX_CTRL_ME1_PAD_ME101_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define IOMUX_CTRL_ME1_PAD_ME102_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define IOMUX_CTRL_ME1_PAD_ME164_O26A0_T_OFF                (BASEADDRESS+0x0100)
#define IOMUX_CTRL_ME1_PAD_ME165_O26A0_T_OFF                (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xCCCF_3000    pad_me100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_dim1_sclk__ds0: 1;    //    4
    UINT32 reg_pad_dim1_sclk__ds1: 1;    //    5
    UINT32 reg_pad_dim1_sclk__ds2: 1;    //    6
    UINT32 reg_pad_dim1_sclk__ds3: 1;    //    7
    UINT32 reg_pad_dim1_sclk__pd: 1;    //     8
    UINT32 reg_pad_dim1_sclk__pu: 1;    //     9
    UINT32 reg_pad_dim1_sclk__st: 1;    //    10
    UINT32 reg_pad_dim1_mosi__ds0: 1;    //   11
    UINT32 reg_pad_dim1_mosi__ds1: 1;    //   12
    UINT32 reg_pad_dim1_mosi__ds2: 1;    //   13
    UINT32 reg_pad_dim1_mosi__ds3: 1;    //   14
    UINT32 reg_pad_dim1_mosi__pd: 1;    //    15
    UINT32 reg_pad_dim1_mosi__pu: 1;    //    16
    UINT32 reg_pad_dim1_mosi__st: 1;    //    17
    UINT32 reg_pad_dim0_sclk__ds0: 1;    //   18
    UINT32 reg_pad_dim0_sclk__ds1: 1;    //   19
    UINT32 reg_pad_dim0_sclk__ds2: 1;    //   20
    UINT32 reg_pad_dim0_sclk__ds3: 1;    //   21
    UINT32 reg_pad_dim0_sclk__pd: 1;    //    22
    UINT32 reg_pad_dim0_sclk__pu: 1;    //    23
    UINT32 reg_pad_dim0_sclk__st: 1;    //    24
    UINT32 reg_pad_dim0_mosi__ds0: 1;    //   25
    UINT32 reg_pad_dim0_mosi__ds1: 1;    //   26
    UINT32 reg_pad_dim0_mosi__ds2: 1;    //   27
    UINT32 reg_pad_dim0_mosi__ds3: 1;    //   28
    UINT32 reg_pad_dim0_mosi__pd: 1;    //    29
    UINT32 reg_pad_dim0_mosi__pu: 1;    //    30
    UINT32 reg_pad_dim0_mosi__st: 1;    //    31
    };
}IOMUX_CTRL_ME1_PAD_ME100_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3004    pad_me101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  6;    //   5: 0 reserved
    UINT32 reg_pad_dim3_sclk__ds0: 1;    //    6
    UINT32 reg_pad_dim3_sclk__ds1: 1;    //    7
    UINT32 reg_pad_dim3_sclk__ds2: 1;    //    8
    UINT32 reg_pad_dim3_sclk__pd: 1;    //     9
    UINT32 reg_pad_dim3_sclk__pu: 1;    //    10
    UINT32 reg_pad_dim3_sclk__smt: 1;    //   11
    UINT32 reg_pad_dim3_mosi__ds0: 1;    //   12
    UINT32 reg_pad_dim3_mosi__ds1: 1;    //   13
    UINT32 reg_pad_dim3_mosi__ds2: 1;    //   14
    UINT32 reg_pad_dim3_mosi__pd: 1;    //    15
    UINT32 reg_pad_dim3_mosi__pu: 1;    //    16
    UINT32 reg_pad_dim3_mosi__smt: 1;    //   17
    UINT32 reg_pad_dim2_sclk__ds0: 1;    //   18
    UINT32 reg_pad_dim2_sclk__ds1: 1;    //   19
    UINT32 reg_pad_dim2_sclk__ds2: 1;    //   20
    UINT32 reg_pad_dim2_sclk__ds3: 1;    //   21
    UINT32 reg_pad_dim2_sclk__pd: 1;    //    22
    UINT32 reg_pad_dim2_sclk__pu: 1;    //    23
    UINT32 reg_pad_dim2_sclk__st: 1;    //    24
    UINT32 reg_pad_dim2_mosi__ds0: 1;    //   25
    UINT32 reg_pad_dim2_mosi__ds1: 1;    //   26
    UINT32 reg_pad_dim2_mosi__ds2: 1;    //   27
    UINT32 reg_pad_dim2_mosi__ds3: 1;    //   28
    UINT32 reg_pad_dim2_mosi__pd: 1;    //    29
    UINT32 reg_pad_dim2_mosi__pu: 1;    //    30
    UINT32 reg_pad_dim2_mosi__st: 1;    //    31
    };
}IOMUX_CTRL_ME1_PAD_ME101_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3008    pad_me102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  6;    //   5: 0 reserved
    UINT32 reg_pad_ld_vs_out3__ds0: 1;    //   6
    UINT32 reg_pad_ld_vs_out3__ds1: 1;    //   7
    UINT32 reg_pad_ld_vs_out3__ds2: 1;    //   8
    UINT32 reg_pad_ld_vs_out3__ds3: 1;    //   9
    UINT32 reg_pad_ld_vs_out3__pd: 1;    //   10
    UINT32 reg_pad_ld_vs_out3__pu: 1;    //   11
    UINT32 reg_pad_ld_vs_out3__st: 1;    //   12
    UINT32 reg_pad_ld_vs_out2__ds0: 1;    //  13
    UINT32 reg_pad_ld_vs_out2__ds1: 1;    //  14
    UINT32 reg_pad_ld_vs_out2__ds2: 1;    //  15
    UINT32 reg_pad_ld_vs_out2__ds3: 1;    //  16
    UINT32 reg_pad_ld_vs_out2__pd: 1;    //   17
    UINT32 reg_pad_ld_vs_out2__pu: 1;    //   18
    UINT32 reg_pad_ld_vs_out2__st: 1;    //   19
    UINT32 reg_pad_ld_vs_out1__ds0: 1;    //  20
    UINT32 reg_pad_ld_vs_out1__ds1: 1;    //  21
    UINT32 reg_pad_ld_vs_out1__ds2: 1;    //  22
    UINT32 reg_pad_ld_vs_out1__pd: 1;    //   23
    UINT32 reg_pad_ld_vs_out1__pu: 1;    //   24
    UINT32 reg_pad_ld_vs_out1__smt: 1;    //  25
    UINT32 reg_pad_ld_vs_out0__ds0: 1;    //  26
    UINT32 reg_pad_ld_vs_out0__ds1: 1;    //  27
    UINT32 reg_pad_ld_vs_out0__ds2: 1;    //  28
    UINT32 reg_pad_ld_vs_out0__pd: 1;    //   29
    UINT32 reg_pad_ld_vs_out0__pu: 1;    //   30
    UINT32 reg_pad_ld_vs_out0__smt: 1;    //  31
    };
}IOMUX_CTRL_ME1_PAD_ME102_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3100    pad_me164 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim3_sclk_mux_sel: 4;    //  3:0
    UINT32 reg_pad_dim3_mosi_mux_sel: 4;    //  7:4
    UINT32 reg_pad_dim2_sclk_mux_sel: 4;    //  11:8
    UINT32 reg_pad_dim2_mosi_mux_sel: 4;    //  15:12
    UINT32 reg_pad_dim1_sclk_mux_sel: 4;    //  19:16
    UINT32 reg_pad_dim1_mosi_mux_sel: 4;    //  23:20
    UINT32 reg_pad_dim0_sclk_mux_sel: 4;    //  27:24
    UINT32 reg_pad_dim0_mosi_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_ME1_PAD_ME164_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3104    pad_me165 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ld_vs_out3_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ld_vs_out2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ld_vs_out1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ld_vs_out0_mux_sel: 4;    //  15:12
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}IOMUX_CTRL_ME1_PAD_ME165_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_ME1_PAD_ME100_O26A0_T    pad_me100 ;             // 0xCCCF_3000
    IOMUX_CTRL_ME1_PAD_ME101_O26A0_T    pad_me101 ;             // 0xCCCF_3004
    IOMUX_CTRL_ME1_PAD_ME102_O26A0_T    pad_me102 ;             // 0xCCCF_3008
    UINT32                             _rsvd_00[61];            // 0xCCCF_300C ~ 0xCCCF_30FC
    IOMUX_CTRL_ME1_PAD_ME164_O26A0_T    pad_me164 ;             // 0xCCCF_3100
    IOMUX_CTRL_ME1_PAD_ME165_O26A0_T    pad_me165 ;             // 0xCCCF_3104
}IOMUX_CTRL_ME1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_ME1_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

