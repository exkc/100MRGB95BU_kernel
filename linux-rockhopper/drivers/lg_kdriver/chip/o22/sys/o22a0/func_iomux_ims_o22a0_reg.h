#ifndef _IOMUX_CTRL_IMX_REG_H_
#define _IOMUX_CTRL_IMX_REG_H_

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
    0xCC8F_2000    pad_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data0_cam__ds0:  1,    //      0
    reg_pad_tpi_data0_cam__ds1:  1,    //      1
    reg_pad_tpi_data0_cam__ds2:  1,    //      2
    reg_pad_tpi_data0_cam__ds3:  1,    //      3
    reg_pad_tpi_data0_cam__pd :  1,    //      4
    reg_pad_tpi_data0_cam__pu :  1,    //      5
    reg_pad_tpi_data0_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_val_cam__ds0  :  1,    //      8
    reg_pad_tpi_val_cam__ds1  :  1,    //      9
    reg_pad_tpi_val_cam__ds2  :  1,    //     10
    reg_pad_tpi_val_cam__ds3  :  1,    //     11
    reg_pad_tpi_val_cam__pd   :  1,    //     12
    reg_pad_tpi_val_cam__pu   :  1,    //     13
    reg_pad_tpi_val_cam__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_sop_cam__ds0  :  1,    //     16
    reg_pad_tpi_sop_cam__ds1  :  1,    //     17
    reg_pad_tpi_sop_cam__ds2  :  1,    //     18
    reg_pad_tpi_sop_cam__ds3  :  1,    //     19
    reg_pad_tpi_sop_cam__pd   :  1,    //     20
    reg_pad_tpi_sop_cam__pu   :  1,    //     21
    reg_pad_tpi_sop_cam__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_clk_cam__ds0  :  1,    //     24
    reg_pad_tpi_clk_cam__ds1  :  1,    //     25
    reg_pad_tpi_clk_cam__ds2  :  1,    //     26
    reg_pad_tpi_clk_cam__ds3  :  1,    //     27
    reg_pad_tpi_clk_cam__pd   :  1,    //     28
    reg_pad_tpi_clk_cam__pu   :  1,    //     29
    reg_pad_tpi_clk_cam__st   :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_IMX_PAD_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2004    pad_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_cam__ds0:  1,    //      0
    reg_pad_tpi_data4_cam__ds1:  1,    //      1
    reg_pad_tpi_data4_cam__ds2:  1,    //      2
    reg_pad_tpi_data4_cam__ds3:  1,    //      3
    reg_pad_tpi_data4_cam__pd :  1,    //      4
    reg_pad_tpi_data4_cam__pu :  1,    //      5
    reg_pad_tpi_data4_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data3_cam__ds0:  1,    //      8
    reg_pad_tpi_data3_cam__ds1:  1,    //      9
    reg_pad_tpi_data3_cam__ds2:  1,    //     10
    reg_pad_tpi_data3_cam__ds3:  1,    //     11
    reg_pad_tpi_data3_cam__pd :  1,    //     12
    reg_pad_tpi_data3_cam__pu :  1,    //     13
    reg_pad_tpi_data3_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data2_cam__ds0:  1,    //     16
    reg_pad_tpi_data2_cam__ds1:  1,    //     17
    reg_pad_tpi_data2_cam__ds2:  1,    //     18
    reg_pad_tpi_data2_cam__ds3:  1,    //     19
    reg_pad_tpi_data2_cam__pd :  1,    //     20
    reg_pad_tpi_data2_cam__pu :  1,    //     21
    reg_pad_tpi_data2_cam__st :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data1_cam__ds0:  1,    //     24
    reg_pad_tpi_data1_cam__ds1:  1,    //     25
    reg_pad_tpi_data1_cam__ds2:  1,    //     26
    reg_pad_tpi_data1_cam__ds3:  1,    //     27
    reg_pad_tpi_data1_cam__pd :  1,    //     28
    reg_pad_tpi_data1_cam__pu :  1,    //     29
    reg_pad_tpi_data1_cam__st :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_IMX_PAD_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2008    pad_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_cam__ds0:  1,    //      0
    reg_pad_tpi_data7_cam__ds1:  1,    //      1
    reg_pad_tpi_data7_cam__ds2:  1,    //      2
    reg_pad_tpi_data7_cam__ds3:  1,    //      3
    reg_pad_tpi_data7_cam__pd :  1,    //      4
    reg_pad_tpi_data7_cam__pu :  1,    //      5
    reg_pad_tpi_data7_cam__st :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data6_cam__ds0:  1,    //      8
    reg_pad_tpi_data6_cam__ds1:  1,    //      9
    reg_pad_tpi_data6_cam__ds2:  1,    //     10
    reg_pad_tpi_data6_cam__ds3:  1,    //     11
    reg_pad_tpi_data6_cam__pd :  1,    //     12
    reg_pad_tpi_data6_cam__pu :  1,    //     13
    reg_pad_tpi_data6_cam__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data5_cam__ds0:  1,    //     16
    reg_pad_tpi_data5_cam__ds1:  1,    //     17
    reg_pad_tpi_data5_cam__ds2:  1,    //     18
    reg_pad_tpi_data5_cam__ds3:  1,    //     19
    reg_pad_tpi_data5_cam__pd :  1,    //     20
    reg_pad_tpi_data5_cam__pu :  1,    //     21
    reg_pad_tpi_data5_cam__st :  1,    //     22
                              :  9;    //  31:23 reserved
}IOMUX_CTRL_IMX_PAD_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2100    pad_imx64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_data3_cam_mux_sel: 4,    //  7:4
    reg_pad_tpi_data2_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data1_cam_mux_sel: 4,    //  15:12
    reg_pad_tpi_data0_cam_mux_sel: 4,    //  19:16
    reg_pad_tpi_val_cam_mux_sel: 4,    //  23:20
    reg_pad_tpi_sop_cam_mux_sel: 4,    //  27:24
    reg_pad_tpi_clk_cam_mux_sel: 4;    //  31:28
}IOMUX_CTRL_IMX_PAD_IMX64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2104    pad_imx65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_data6_cam_mux_sel: 4,    //  7:4
    reg_pad_tpi_data5_cam_mux_sel: 4,    //  11:8
                              : 20;    //  31:12 reserved
}IOMUX_CTRL_IMX_PAD_IMX65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_IMX_PAD_IMX00_O22A0_T          pad_imx00  ;             // 0xCC8F_2000
    IOMUX_CTRL_IMX_PAD_IMX01_O22A0_T          pad_imx01  ;             // 0xCC8F_2004
    IOMUX_CTRL_IMX_PAD_IMX02_O22A0_T          pad_imx02  ;             // 0xCC8F_2008
    UINT32                             _rsvd_00[61];            // 0xCC8F_200C ~ 0xCC8F_20FC
    IOMUX_CTRL_IMX_PAD_IMX64_O22A0_T          pad_imx64  ;             // 0xCC8F_2100
    IOMUX_CTRL_IMX_PAD_IMX65_O22A0_T          pad_imx65  ;             // 0xCC8F_2104
}IOMUX_CTRL_IMX_REG_O22A0_T;
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

#define IOMUX_CTRL_IMX_PAD_IMX00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define IOMUX_CTRL_IMX_PAD_IMX01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define IOMUX_CTRL_IMX_PAD_IMX02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define IOMUX_CTRL_IMX_PAD_IMX64_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define IOMUX_CTRL_IMX_PAD_IMX65_O22A0_T_OFF                       (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xCC8F_2000    pad_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data0_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data0_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data0_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data0_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data0_cam__pd: 1;    //  4
    UINT32 reg_pad_tpi_data0_cam__pu: 1;    //  5
    UINT32 reg_pad_tpi_data0_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_val_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_val_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_val_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_val_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_val_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_val_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_val_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_sop_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_sop_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_sop_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_sop_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_sop_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_sop_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_sop_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_clk_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpi_clk_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpi_clk_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpi_clk_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpi_clk_cam__pd: 1;    //  28
    UINT32 reg_pad_tpi_clk_cam__pu: 1;    //  29
    UINT32 reg_pad_tpi_clk_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_IMX_PAD_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2004    pad_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data4_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data4_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data4_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data4_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data4_cam__pd: 1;    //  4
    UINT32 reg_pad_tpi_data4_cam__pu: 1;    //  5
    UINT32 reg_pad_tpi_data4_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data3_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data3_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data3_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data3_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data3_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_data3_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_data3_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data2_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data2_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data2_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data2_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data2_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_data2_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_data2_cam__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_tpi_data1_cam__ds0: 1;    //  24
    UINT32 reg_pad_tpi_data1_cam__ds1: 1;    //  25
    UINT32 reg_pad_tpi_data1_cam__ds2: 1;    //  26
    UINT32 reg_pad_tpi_data1_cam__ds3: 1;    //  27
    UINT32 reg_pad_tpi_data1_cam__pd: 1;    //  28
    UINT32 reg_pad_tpi_data1_cam__pu: 1;    //  29
    UINT32 reg_pad_tpi_data1_cam__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_IMX_PAD_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2008    pad_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data7_cam__ds0: 1;    //  0
    UINT32 reg_pad_tpi_data7_cam__ds1: 1;    //  1
    UINT32 reg_pad_tpi_data7_cam__ds2: 1;    //  2
    UINT32 reg_pad_tpi_data7_cam__ds3: 1;    //  3
    UINT32 reg_pad_tpi_data7_cam__pd: 1;    //  4
    UINT32 reg_pad_tpi_data7_cam__pu: 1;    //  5
    UINT32 reg_pad_tpi_data7_cam__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_tpi_data6_cam__ds0: 1;    //  8
    UINT32 reg_pad_tpi_data6_cam__ds1: 1;    //  9
    UINT32 reg_pad_tpi_data6_cam__ds2: 1;    //  10
    UINT32 reg_pad_tpi_data6_cam__ds3: 1;    //  11
    UINT32 reg_pad_tpi_data6_cam__pd: 1;    //  12
    UINT32 reg_pad_tpi_data6_cam__pu: 1;    //  13
    UINT32 reg_pad_tpi_data6_cam__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_tpi_data5_cam__ds0: 1;    //  16
    UINT32 reg_pad_tpi_data5_cam__ds1: 1;    //  17
    UINT32 reg_pad_tpi_data5_cam__ds2: 1;    //  18
    UINT32 reg_pad_tpi_data5_cam__ds3: 1;    //  19
    UINT32 reg_pad_tpi_data5_cam__pd: 1;    //  20
    UINT32 reg_pad_tpi_data5_cam__pu: 1;    //  21
    UINT32 reg_pad_tpi_data5_cam__st: 1;    //  22
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}IOMUX_CTRL_IMX_PAD_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2100    pad_imx64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data4_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data3_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data2_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data1_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_data0_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_val_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_sop_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_clk_cam_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_IMX_PAD_IMX64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8F_2104    pad_imx65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data7_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_data6_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data5_cam_mux_sel: 4;    //  11:8
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}IOMUX_CTRL_IMX_PAD_IMX65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_IMX_PAD_IMX00_O22A0_T          pad_imx00  ;             // 0xCC8F_2000
    IOMUX_CTRL_IMX_PAD_IMX01_O22A0_T          pad_imx01  ;             // 0xCC8F_2004
    IOMUX_CTRL_IMX_PAD_IMX02_O22A0_T          pad_imx02  ;             // 0xCC8F_2008
    UINT32                             _rsvd_00[61];            // 0xCC8F_200C ~ 0xCC8F_20FC
    IOMUX_CTRL_IMX_PAD_IMX64_O22A0_T          pad_imx64  ;             // 0xCC8F_2100
    IOMUX_CTRL_IMX_PAD_IMX65_O22A0_T          pad_imx65  ;             // 0xCC8F_2104
}IOMUX_CTRL_IMX_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_IMX_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

