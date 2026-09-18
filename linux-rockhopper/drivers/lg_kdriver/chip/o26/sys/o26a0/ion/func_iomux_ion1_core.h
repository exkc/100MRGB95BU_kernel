#ifndef _FUNC_IOMUX_ION1_CORE_REG_H_
#define _FUNC_IOMUX_ION1_CORE_REG_H_

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
    0xC467_2000    pad_ion1_core00 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2004    pad_ion1_core01 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2008    pad_ion1_core02 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_200C    pad_ion1_core03 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2010    pad_ion1_core04 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2014    pad_ion1_core05 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2018    pad_ion1_core06 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_201C    pad_ion1_core07 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2100    pad_ion1_core64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpo_data3_cam_mux_sel: 4,    //  3:0
    reg_pad_tpo_data4_cam_mux_sel: 4,    //  7:4
    reg_pad_tpo_data7_cam_mux_sel: 4,    //  11:8
    reg_pad_tpo_data6_cam_mux_sel: 4,    //  15:12
    reg_pad_tpo_val_cam_mux_sel: 4,    //  19:16
    reg_pad_tpo_data1_cam_mux_sel: 4,    //  23:20
    reg_pad_tpo_clk_cam_mux_sel: 4,    //  27:24
    reg_pad_ci_intr_mux_sel   :  4;    //  31:28
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_2104    pad_ion1_core65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5_cam_mux_sel: 4,    //  3:0
    reg_pad_tpi_clk_cam_mux_sel: 4,    //   7: 4
    reg_pad_tpi_data7_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data2_cam_mux_sel: 4,    //  15:12
    reg_pad_tpo_data5_cam_mux_sel: 4,    //  19:16
    reg_pad_tpo_sop_cam_mux_sel: 4,    //  23:20
    reg_pad_tpo_data2_cam_mux_sel: 4,    //  27:24
    reg_pad_tpo_data0_cam_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_2108    pad_ion1_core66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion1_gpio00_mux_sel: 4,    //   3: 0
    reg_pad_tpi_val_cam_mux_sel: 4,    //   7: 4
    reg_pad_tpi_data6_cam_mux_sel: 4,    //  11:8
    reg_pad_tpi_data4_cam_mux_sel: 4,    //  15:12
    reg_pad_tpi_sop_cam_mux_sel: 4,    //  19:16
    reg_pad_tpi_data1_cam_mux_sel: 4,    //  23:20
    reg_pad_tpi_data3_cam_mux_sel: 4,    //  27:24
    reg_pad_tpi_data0_cam_mux_sel: 4;    //  31:28
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_210C    pad_ion1_core67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_ion1_gpio06_mux_sel: 4,    //   3: 0
    reg_pad_ion1_gpio05_mux_sel: 4,    //   7: 4
    reg_pad_ion1_gpio04_mux_sel: 4,    //  11: 8
    reg_pad_ion1_gpio03_mux_sel: 4,    //  15:12
    reg_pad_ion1_gpio02_mux_sel: 4,    //  19:16
    reg_pad_ion1_gpio01_mux_sel: 4,    //  23:20
                              :  8;    //  31:24 reserved
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion1_core Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             pad_ion1_core00;         // 0xC467_2000
    UINT32                             pad_ion1_core01;         // 0xC467_2004
    UINT32                             pad_ion1_core02;         // 0xC467_2008
    UINT32                             pad_ion1_core03;         // 0xC467_200C
    UINT32                             pad_ion1_core04;         // 0xC467_2010
    UINT32                             pad_ion1_core05;         // 0xC467_2014
    UINT32                             pad_ion1_core06;         // 0xC467_2018
    UINT32                             pad_ion1_core07;         // 0xC467_201C
    UINT32                             _rsvd_00[56];            // 0xC467_2020 ~ 0xC467_20FC
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE64_O26A0_T    pad_ion1_core64;    // 0xC467_2100
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE65_O26A0_T    pad_ion1_core65;    // 0xC467_2104
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE66_O26A0_T    pad_ion1_core66;    // 0xC467_2108
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE67_O26A0_T    pad_ion1_core67;    // 0xC467_210C
}FUNC_IOMUX_ION1_CORE_REG_O26A0_T;
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

#define FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE64_O26A0_T_OFF    (BASEADDRESS+0x0100)
#define FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE65_O26A0_T_OFF    (BASEADDRESS+0x0104)
#define FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE66_O26A0_T_OFF    (BASEADDRESS+0x0108)
#define FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE67_O26A0_T_OFF    (BASEADDRESS+0x010C)

/*-----------------------------------------------------------------------------------------
    0xC467_2000    pad_ion1_core00 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2004    pad_ion1_core01 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2008    pad_ion1_core02 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_200C    pad_ion1_core03 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2010    pad_ion1_core04 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2014    pad_ion1_core05 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2018    pad_ion1_core06 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_201C    pad_ion1_core07 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC467_2100    pad_ion1_core64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpo_data3_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpo_data4_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpo_data7_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpo_data6_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpo_val_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpo_data1_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpo_clk_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_ci_intr_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_2104    pad_ion1_core65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_tpi_data5_cam_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_clk_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data7_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data2_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpo_data5_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpo_sop_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpo_data2_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpo_data0_cam_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_2108    pad_ion1_core66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion1_gpio00_mux_sel: 4;    //  3:0
    UINT32 reg_pad_tpi_val_cam_mux_sel: 4;    //  7:4
    UINT32 reg_pad_tpi_data6_cam_mux_sel: 4;    //  11:8
    UINT32 reg_pad_tpi_data4_cam_mux_sel: 4;    //  15:12
    UINT32 reg_pad_tpi_sop_cam_mux_sel: 4;    //  19:16
    UINT32 reg_pad_tpi_data1_cam_mux_sel: 4;    //  23:20
    UINT32 reg_pad_tpi_data3_cam_mux_sel: 4;    //  27:24
    UINT32 reg_pad_tpi_data0_cam_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC467_210C    pad_ion1_core67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_ion1_gpio06_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ion1_gpio05_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ion1_gpio04_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ion1_gpio03_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ion1_gpio02_mux_sel: 4;    //  19:16
    UINT32 reg_pad_ion1_gpio01_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    func_iomux_ion1_core Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             pad_ion1_core00;         // 0xC467_2000
    UINT32                             pad_ion1_core01;         // 0xC467_2004
    UINT32                             pad_ion1_core02;         // 0xC467_2008
    UINT32                             pad_ion1_core03;         // 0xC467_200C
    UINT32                             pad_ion1_core04;         // 0xC467_2010
    UINT32                             pad_ion1_core05;         // 0xC467_2014
    UINT32                             pad_ion1_core06;         // 0xC467_2018
    UINT32                             pad_ion1_core07;         // 0xC467_201C
    UINT32                             _rsvd_00[56];            // 0xC467_2020 ~ 0xC467_20FC
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE64_O26A0_T    pad_ion1_core64;    // 0xC467_2100
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE65_O26A0_T    pad_ion1_core65;    // 0xC467_2104
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE66_O26A0_T    pad_ion1_core66;    // 0xC467_2108
    FUNC_IOMUX_ION1_CORE_PAD_ION1_CORE67_O26A0_T    pad_ion1_core67;    // 0xC467_210C
}FUNC_IOMUX_ION1_CORE_REG_O26A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _FUNC_IOMUX_ION1_CORE_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/

