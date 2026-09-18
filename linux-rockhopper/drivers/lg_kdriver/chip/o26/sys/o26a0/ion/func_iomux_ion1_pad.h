#ifndef _FUNC_IOMUX_ION1_PAD_REG_H_
#define _FUNC_IOMUX_ION1_PAD_REG_H_

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
    0xC467_1000    pad_ion1_pad00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_sd00__ds0   :  1,    //      0
    reg_pad_ci_io_sd00__ds1   :  1,    //      1
    reg_pad_ci_io_sd00__ds2   :  1,    //      2
    reg_pad_ci_io_sd00__ds3   :  1,    //      3
    reg_pad_ci_io_sd00__pd    :  1,    //      4
    reg_pad_ci_io_sd00__pu    :  1,    //      5
    reg_pad_ci_io_sd00__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ci_io_pores_n__ds0:  1,    //      8
    reg_pad_ci_io_pores_n__ds1:  1,    //      9
    reg_pad_ci_io_pores_n__ds2:  1,    //     10
    reg_pad_ci_io_pores_n__ds3:  1,    //     11
    reg_pad_ci_io_pores_n__pd :  1,    //     12
    reg_pad_ci_io_pores_n__pu :  1,    //     13
    reg_pad_ci_io_pores_n__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ci_io_clk__ds0    :  1,    //     16
    reg_pad_ci_io_clk__ds1    :  1,    //     17
    reg_pad_ci_io_clk__ds2    :  1,    //     18
    reg_pad_ci_io_clk__ds3    :  1,    //     19
    reg_pad_ci_io_clk__pd     :  1,    //     20
    reg_pad_ci_io_clk__pu     :  1,    //     21
    reg_pad_ci_io_clk__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_cicam_clk__ds0    :  1,    //     24
    reg_pad_cicam_clk__ds1    :  1,    //     25
    reg_pad_cicam_clk__ds2    :  1,    //     26
    reg_pad_cicam_clk__ds3    :  1,    //     27
    reg_pad_cicam_clk__pd     :  1,    //     28
    reg_pad_cicam_clk__pu     :  1,    //     29
    reg_pad_cicam_clk__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1004    pad_ion1_pad01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_sd04__ds0   :  1,    //      0
    reg_pad_ci_io_sd04__ds1   :  1,    //      1
    reg_pad_ci_io_sd04__ds2   :  1,    //      2
    reg_pad_ci_io_sd04__ds3   :  1,    //      3
    reg_pad_ci_io_sd04__pd    :  1,    //      4
    reg_pad_ci_io_sd04__pu    :  1,    //      5
    reg_pad_ci_io_sd04__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ci_io_sd03__ds0   :  1,    //      8
    reg_pad_ci_io_sd03__ds1   :  1,    //      9
    reg_pad_ci_io_sd03__ds2   :  1,    //     10
    reg_pad_ci_io_sd03__ds3   :  1,    //     11
    reg_pad_ci_io_sd03__pd    :  1,    //     12
    reg_pad_ci_io_sd03__pu    :  1,    //     13
    reg_pad_ci_io_sd03__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ci_io_sd02__ds0   :  1,    //     16
    reg_pad_ci_io_sd02__ds1   :  1,    //     17
    reg_pad_ci_io_sd02__ds2   :  1,    //     18
    reg_pad_ci_io_sd02__ds3   :  1,    //     19
    reg_pad_ci_io_sd02__pd    :  1,    //     20
    reg_pad_ci_io_sd02__pu    :  1,    //     21
    reg_pad_ci_io_sd02__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ci_io_sd01__ds0   :  1,    //     24
    reg_pad_ci_io_sd01__ds1   :  1,    //     25
    reg_pad_ci_io_sd01__ds2   :  1,    //     26
    reg_pad_ci_io_sd01__ds3   :  1,    //     27
    reg_pad_ci_io_sd01__pd    :  1,    //     28
    reg_pad_ci_io_sd01__pu    :  1,    //     29
    reg_pad_ci_io_sd01__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1008    pad_ion1_pad02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_spi_clk__ds0:  1,    //      0
    reg_pad_ci_io_spi_clk__ds1:  1,    //      1
    reg_pad_ci_io_spi_clk__ds2:  1,    //      2
    reg_pad_ci_io_spi_clk__ds3:  1,    //      3
    reg_pad_ci_io_spi_clk__pd :  1,    //      4
    reg_pad_ci_io_spi_clk__pu :  1,    //      5
    reg_pad_ci_io_spi_clk__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ci_io_sd07__ds0   :  1,    //      8
    reg_pad_ci_io_sd07__ds1   :  1,    //      9
    reg_pad_ci_io_sd07__ds2   :  1,    //     10
    reg_pad_ci_io_sd07__ds3   :  1,    //     11
    reg_pad_ci_io_sd07__pd    :  1,    //     12
    reg_pad_ci_io_sd07__pu    :  1,    //     13
    reg_pad_ci_io_sd07__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ci_io_sd06__ds0   :  1,    //     16
    reg_pad_ci_io_sd06__ds1   :  1,    //     17
    reg_pad_ci_io_sd06__ds2   :  1,    //     18
    reg_pad_ci_io_sd06__ds3   :  1,    //     19
    reg_pad_ci_io_sd06__pd    :  1,    //     20
    reg_pad_ci_io_sd06__pu    :  1,    //     21
    reg_pad_ci_io_sd06__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_ci_io_sd05__ds0   :  1,    //     24
    reg_pad_ci_io_sd05__ds1   :  1,    //     25
    reg_pad_ci_io_sd05__ds2   :  1,    //     26
    reg_pad_ci_io_sd05__ds3   :  1,    //     27
    reg_pad_ci_io_sd05__pd    :  1,    //     28
    reg_pad_ci_io_sd05__pu    :  1,    //     29
    reg_pad_ci_io_sd05__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_100C    pad_ion1_pad03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_spi_do__ds0 :  1,    //      0
    reg_pad_ci_io_spi_do__ds1 :  1,    //      1
    reg_pad_ci_io_spi_do__ds2 :  1,    //      2
    reg_pad_ci_io_spi_do__ds3 :  1,    //      3
    reg_pad_ci_io_spi_do__pd  :  1,    //      4
    reg_pad_ci_io_spi_do__pu  :  1,    //      5
    reg_pad_ci_io_spi_do__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ci_io_spi_di__ds0 :  1,    //      8
    reg_pad_ci_io_spi_di__ds1 :  1,    //      9
    reg_pad_ci_io_spi_di__ds2 :  1,    //     10
    reg_pad_ci_io_spi_di__ds3 :  1,    //     11
    reg_pad_ci_io_spi_di__pd  :  1,    //     12
    reg_pad_ci_io_spi_di__pu  :  1,    //     13
    reg_pad_ci_io_spi_di__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ci_io_spi_cs__ds0 :  1,    //     16
    reg_pad_ci_io_spi_cs__ds1 :  1,    //     17
    reg_pad_ci_io_spi_cs__ds2 :  1,    //     18
    reg_pad_ci_io_spi_cs__ds3 :  1,    //     19
    reg_pad_ci_io_spi_cs__pd  :  1,    //     20
    reg_pad_ci_io_spi_cs__pu  :  1,    //     21
    reg_pad_ci_io_spi_cs__st  :  1,    //     22
                              :  9;    //  31:23 reserved
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1100    pad_ion1_pad64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_sd04_mux_sel:  4,    //   3: 0
    reg_pad_ci_io_sd03_mux_sel:  4,    //   7: 4
    reg_pad_ci_io_sd02_mux_sel:  4,    //  11: 8
    reg_pad_ci_io_sd01_mux_sel:  4,    //  15:12
    reg_pad_ci_io_sd00_mux_sel:  4,    //  19:16
    reg_pad_ci_io_pores_n_mux_sel: 4,    //  23:20
    reg_pad_ci_io_clk_mux_sel :  4,    //  27:24
    reg_pad_cicam_clk_mux_sel :  4;    //  31:28
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1104    pad_ion1_pad65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ci_io_spi_do_mux_sel: 4,    //  3: 0
    reg_pad_ci_io_spi_di_mux_sel: 4,    //  7: 4
    reg_pad_ci_io_spi_cs_mux_sel: 4,    //  11:8
    reg_pad_ci_io_spi_clk_mux_sel: 4,    //  15:12
    reg_pad_ci_io_sd07_mux_sel:  4,    //  19:16
    reg_pad_ci_io_sd06_mux_sel:  4,    //  23:20
    reg_pad_ci_io_sd05_mux_sel:  4,    //  27:24
                              :  4;    //  31:28 reserved
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion1_pad Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD00_O26A0_T    pad_ion1_pad00;    // 0xC467_1000
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD01_O26A0_T    pad_ion1_pad01;    // 0xC467_1004
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD02_O26A0_T    pad_ion1_pad02;    // 0xC467_1008
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD03_O26A0_T    pad_ion1_pad03;    // 0xC467_100C
    UINT32                             _rsvd_00[60];            // 0xC467_1010 ~ 0xC467_10FC
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD64_O26A0_T    pad_ion1_pad64;    // 0xC467_1100
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD65_O26A0_T    pad_ion1_pad65;    // 0xC467_1104
}FUNC_IOMUX_ION1_PAD_REG_O26A0_T;
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

#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD00_O26A0_T_OFF      (BASEADDRESS+0x0000)
#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD01_O26A0_T_OFF      (BASEADDRESS+0x0004)
#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD02_O26A0_T_OFF      (BASEADDRESS+0x0008)
#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD03_O26A0_T_OFF      (BASEADDRESS+0x000C)
#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD64_O26A0_T_OFF      (BASEADDRESS+0x0100)
#define FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD65_O26A0_T_OFF      (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xC467_1000    pad_ion1_pad00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_sd00__ds0: 1;    //   0
    UINT32 reg_pad_ci_io_sd00__ds1: 1;    //   1
    UINT32 reg_pad_ci_io_sd00__ds2: 1;    //   2
    UINT32 reg_pad_ci_io_sd00__ds3: 1;    //   3
    UINT32 reg_pad_ci_io_sd00__pd: 1;    //    4
    UINT32 reg_pad_ci_io_sd00__pu: 1;    //    5
    UINT32 reg_pad_ci_io_sd00__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ci_io_pores_n__ds0: 1;    //  8
    UINT32 reg_pad_ci_io_pores_n__ds1: 1;    //  9
    UINT32 reg_pad_ci_io_pores_n__ds2: 1;    //  10
    UINT32 reg_pad_ci_io_pores_n__ds3: 1;    //  11
    UINT32 reg_pad_ci_io_pores_n__pd: 1;    //  12
    UINT32 reg_pad_ci_io_pores_n__pu: 1;    //  13
    UINT32 reg_pad_ci_io_pores_n__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ci_io_clk__ds0: 1;    //   16
    UINT32 reg_pad_ci_io_clk__ds1: 1;    //   17
    UINT32 reg_pad_ci_io_clk__ds2: 1;    //   18
    UINT32 reg_pad_ci_io_clk__ds3: 1;    //   19
    UINT32 reg_pad_ci_io_clk__pd: 1;    //    20
    UINT32 reg_pad_ci_io_clk__pu: 1;    //    21
    UINT32 reg_pad_ci_io_clk__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_cicam_clk__ds0: 1;    //   24
    UINT32 reg_pad_cicam_clk__ds1: 1;    //   25
    UINT32 reg_pad_cicam_clk__ds2: 1;    //   26
    UINT32 reg_pad_cicam_clk__ds3: 1;    //   27
    UINT32 reg_pad_cicam_clk__pd: 1;    //    28
    UINT32 reg_pad_cicam_clk__pu: 1;    //    29
    UINT32 reg_pad_cicam_clk__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1004    pad_ion1_pad01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_sd04__ds0: 1;    //   0
    UINT32 reg_pad_ci_io_sd04__ds1: 1;    //   1
    UINT32 reg_pad_ci_io_sd04__ds2: 1;    //   2
    UINT32 reg_pad_ci_io_sd04__ds3: 1;    //   3
    UINT32 reg_pad_ci_io_sd04__pd: 1;    //    4
    UINT32 reg_pad_ci_io_sd04__pu: 1;    //    5
    UINT32 reg_pad_ci_io_sd04__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ci_io_sd03__ds0: 1;    //   8
    UINT32 reg_pad_ci_io_sd03__ds1: 1;    //   9
    UINT32 reg_pad_ci_io_sd03__ds2: 1;    //  10
    UINT32 reg_pad_ci_io_sd03__ds3: 1;    //  11
    UINT32 reg_pad_ci_io_sd03__pd: 1;    //   12
    UINT32 reg_pad_ci_io_sd03__pu: 1;    //   13
    UINT32 reg_pad_ci_io_sd03__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ci_io_sd02__ds0: 1;    //  16
    UINT32 reg_pad_ci_io_sd02__ds1: 1;    //  17
    UINT32 reg_pad_ci_io_sd02__ds2: 1;    //  18
    UINT32 reg_pad_ci_io_sd02__ds3: 1;    //  19
    UINT32 reg_pad_ci_io_sd02__pd: 1;    //   20
    UINT32 reg_pad_ci_io_sd02__pu: 1;    //   21
    UINT32 reg_pad_ci_io_sd02__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ci_io_sd01__ds0: 1;    //  24
    UINT32 reg_pad_ci_io_sd01__ds1: 1;    //  25
    UINT32 reg_pad_ci_io_sd01__ds2: 1;    //  26
    UINT32 reg_pad_ci_io_sd01__ds3: 1;    //  27
    UINT32 reg_pad_ci_io_sd01__pd: 1;    //   28
    UINT32 reg_pad_ci_io_sd01__pu: 1;    //   29
    UINT32 reg_pad_ci_io_sd01__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1008    pad_ion1_pad02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_spi_clk__ds0: 1;    //  0
    UINT32 reg_pad_ci_io_spi_clk__ds1: 1;    //  1
    UINT32 reg_pad_ci_io_spi_clk__ds2: 1;    //  2
    UINT32 reg_pad_ci_io_spi_clk__ds3: 1;    //  3
    UINT32 reg_pad_ci_io_spi_clk__pd: 1;    //  4
    UINT32 reg_pad_ci_io_spi_clk__pu: 1;    //  5
    UINT32 reg_pad_ci_io_spi_clk__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ci_io_sd07__ds0: 1;    //   8
    UINT32 reg_pad_ci_io_sd07__ds1: 1;    //   9
    UINT32 reg_pad_ci_io_sd07__ds2: 1;    //  10
    UINT32 reg_pad_ci_io_sd07__ds3: 1;    //  11
    UINT32 reg_pad_ci_io_sd07__pd: 1;    //   12
    UINT32 reg_pad_ci_io_sd07__pu: 1;    //   13
    UINT32 reg_pad_ci_io_sd07__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ci_io_sd06__ds0: 1;    //  16
    UINT32 reg_pad_ci_io_sd06__ds1: 1;    //  17
    UINT32 reg_pad_ci_io_sd06__ds2: 1;    //  18
    UINT32 reg_pad_ci_io_sd06__ds3: 1;    //  19
    UINT32 reg_pad_ci_io_sd06__pd: 1;    //   20
    UINT32 reg_pad_ci_io_sd06__pu: 1;    //   21
    UINT32 reg_pad_ci_io_sd06__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_ci_io_sd05__ds0: 1;    //  24
    UINT32 reg_pad_ci_io_sd05__ds1: 1;    //  25
    UINT32 reg_pad_ci_io_sd05__ds2: 1;    //  26
    UINT32 reg_pad_ci_io_sd05__ds3: 1;    //  27
    UINT32 reg_pad_ci_io_sd05__pd: 1;    //   28
    UINT32 reg_pad_ci_io_sd05__pu: 1;    //   29
    UINT32 reg_pad_ci_io_sd05__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_100C    pad_ion1_pad03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_spi_do__ds0: 1;    //  0
    UINT32 reg_pad_ci_io_spi_do__ds1: 1;    //  1
    UINT32 reg_pad_ci_io_spi_do__ds2: 1;    //  2
    UINT32 reg_pad_ci_io_spi_do__ds3: 1;    //  3
    UINT32 reg_pad_ci_io_spi_do__pd: 1;    //  4
    UINT32 reg_pad_ci_io_spi_do__pu: 1;    //  5
    UINT32 reg_pad_ci_io_spi_do__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ci_io_spi_di__ds0: 1;    //  8
    UINT32 reg_pad_ci_io_spi_di__ds1: 1;    //  9
    UINT32 reg_pad_ci_io_spi_di__ds2: 1;    //  10
    UINT32 reg_pad_ci_io_spi_di__ds3: 1;    //  11
    UINT32 reg_pad_ci_io_spi_di__pd: 1;    //  12
    UINT32 reg_pad_ci_io_spi_di__pu: 1;    //  13
    UINT32 reg_pad_ci_io_spi_di__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ci_io_spi_cs__ds0: 1;    //  16
    UINT32 reg_pad_ci_io_spi_cs__ds1: 1;    //  17
    UINT32 reg_pad_ci_io_spi_cs__ds2: 1;    //  18
    UINT32 reg_pad_ci_io_spi_cs__ds3: 1;    //  19
    UINT32 reg_pad_ci_io_spi_cs__pd: 1;    //  20
    UINT32 reg_pad_ci_io_spi_cs__pu: 1;    //  21
    UINT32 reg_pad_ci_io_spi_cs__st: 1;    //  22
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1100    pad_ion1_pad64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_sd04_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ci_io_sd03_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ci_io_sd02_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ci_io_sd01_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ci_io_sd00_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ci_io_pores_n_mux_sel: 4;    //  23:20
    UINT32 reg_pad_ci_io_clk_mux_sel: 4;    //  27:24
    UINT32 reg_pad_cicam_clk_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_1104    pad_ion1_pad65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ci_io_spi_do_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ci_io_spi_di_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ci_io_spi_cs_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ci_io_spi_clk_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ci_io_sd07_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ci_io_sd06_mux_sel: 4;    //  23:20
    UINT32 reg_pad_ci_io_sd05_mux_sel: 4;    //  27:24
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion1_pad Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD00_O26A0_T    pad_ion1_pad00;    // 0xC467_1000
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD01_O26A0_T    pad_ion1_pad01;    // 0xC467_1004
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD02_O26A0_T    pad_ion1_pad02;    // 0xC467_1008
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD03_O26A0_T    pad_ion1_pad03;    // 0xC467_100C
    UINT32                             _rsvd_00[60];            // 0xC467_1010 ~ 0xC467_10FC
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD64_O26A0_T    pad_ion1_pad64;    // 0xC467_1100
    FUNC_IOMUX_ION1_PAD_PAD_ION1_PAD65_O26A0_T    pad_ion1_pad65;    // 0xC467_1104
}FUNC_IOMUX_ION1_PAD_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _FUNC_IOMUX_ION1_PAD_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/

