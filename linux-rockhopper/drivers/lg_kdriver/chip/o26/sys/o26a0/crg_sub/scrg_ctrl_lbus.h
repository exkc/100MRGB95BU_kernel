#ifndef _SCRG_CTRL_LBUS_REG_O26A0_H_
#define _SCRG_CTRL_LBUS_REG_O26A0_H_

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
    0xC422_0000    crg_lbus000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0004    crg_lbus001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0008    crg_lbus002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_aud_0__axi_bb_clk_gate_en: 1,    //  0
    reg_adaprx_x_fmc_0__axi_bb_clk_gate_en: 1,    //  1
    reg_adaprx_x_fmc_1__axi_bb_clk_gate_en: 1,    //  2
    reg_adaprx_x_fmc_2__axi_bb_clk_gate_en: 1,    //  3
    reg_adaprx_x_fmc_3__axi_bb_clk_gate_en: 1,    //  4
    reg_adaprx_x_fmesb_0__axi_bb_clk_gate_en: 1,    //  5
    reg_adaprx_x_fms_0__axi_bb_clk_gate_en: 1,    //  6
    reg_adaprx_x_gfx_0__axi_bb_clk_gate_en: 1,    //  7
    reg_adaprx_x_gpu_0__axi_bb_clk_gate_en: 1,    //  8
    reg_adaprx_x_gpu_1__axi_bb_clk_gate_en: 1,    //  9
    reg_adaprx_x_gsc_0__axi_bb_clk_gate_en: 1,    //  10
    reg_adaprx_x_gsc_1__axi_bb_clk_gate_en: 1,    //  11
    reg_adaprx_x_gsc_2__axi_bb_clk_gate_en: 1,    //  12
    reg_adaprx_x_gsc_3__axi_bb_clk_gate_en: 1,    //  13
    reg_adaprx_x_imx_0__axi_bb_clk_gate_en: 1,    //  14
    reg_adaprx_x_imx_1__axi_bb_clk_gate_en: 1,    //  15
    reg_adaprx_x_imx_2__axi_bb_clk_gate_en: 1,    //  16
    reg_adaprx_x_imx_3__axi_bb_clk_gate_en: 1,    //  17
    reg_adaprx_x_iommu_0__axi_bb_clk_gate_en: 1,    //  18
    reg_adaprx_x_iommu_1__axi_bb_clk_gate_en: 1,    //  19
    reg_adaprx_x_iommu_2__axi_bb_clk_gate_en: 1,    //  20
    reg_adaprx_x_lb1sb_0__axi_bb_clk_gate_en: 1,    //  21
    reg_adaprx_x_lnx2_0__axi_bb_clk_gate_en: 1,    //  22
    reg_adaprx_x_nd0_0__axi_bb_clk_gate_en: 1,    //  23
    reg_adaprx_x_nd1_0__axi_bb_clk_gate_en: 1,    //  24
    reg_adaprx_x_srcosb_0__axi_bb_clk_gate_en: 1,    //  25
    reg_adaprx_x_sre_0__axi_bb_clk_gate_en: 1,    //  26
    reg_adaprx_x_tivvmsb_0__axi_bb_clk_gate_en: 1,    //  27
    reg_adaprx_x_vd0_0__axi_bb_clk_gate_en: 1,    //  28
    reg_adaprx_x_vd0_1__axi_bb_clk_gate_en: 1,    //  29
    reg_adaprx_x_vd1_0__axi_bb_clk_gate_en: 1,    //  30
    reg_adaprx_x_vd1_1__axi_bb_clk_gate_en: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_000C    crg_lbus003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_vdo_0__axi_bb_clk_gate_en: 1,    //  0
    reg_adaprx_x_vdo_1__axi_bb_clk_gate_en: 1,    //  1
    reg_adaptx_x_lbus_0__axi_bb_clk_gate_en: 1,    //  2
    reg_adaptx_x_lbus_1__axi_bb_clk_gate_en: 1,    //  3
    reg_adaptx_x_lbus_2__axi_bb_clk_gate_en: 1,    //  4
    reg_adaptx_x_lbus_3__axi_bb_clk_gate_en: 1,    //  5
    reg_adaptx_x_lbus_4__axi_bb_clk_gate_en: 1,    //  6
    reg_adaptx_x_lbus_5__axi_bb_clk_gate_en: 1,    //  7
    reg_adaptx_x_lbus_6__axi_bb_clk_gate_en: 1,    //  8
    reg_adaptx_x_lbus_7__axi_bb_clk_gate_en: 1,    //  9
    reg_apb_clk_gate_en       :  1,    //     10
    reg_async_axi_bb_clk_gate_en: 1,    //    11
    reg_axi_884_clk_gate_en   :  1,    //     12
    reg_axi_bb_clk_gate_en    :  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_LBUS_CRG_LBUS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0010    crg_lbus004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_async_axi_bb_n: 1,    //      1
    reg_soft_rst_axi_bb_n     :  1,    //      2
    reg_soft_rst_p_aud_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_fmc_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_fmc_1_axi_bnd_n: 1,    //   5
    reg_soft_rst_p_fmc_2_axi_bnd_n: 1,    //   6
    reg_soft_rst_p_fmc_3_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_fmesb_0_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_fms_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_gpu_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_gpu_1_axi_bnd_n: 1,    //  12
    reg_soft_rst_p_gsc_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_gsc_1_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_gsc_2_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_gsc_3_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_imx_0_axi_bnd_n: 1,    //  17
    reg_soft_rst_p_imx_1_axi_bnd_n: 1,    //  18
    reg_soft_rst_p_imx_2_axi_bnd_n: 1,    //  19
    reg_soft_rst_p_imx_3_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_iommu_0_axi_bnd_n: 1,    //  21
    reg_soft_rst_p_iommu_1_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_iommu_2_axi_bnd_n: 1,    //  23
    reg_soft_rst_p_lb1sb_0_axi_bnd_n: 1,    //  24
    reg_soft_rst_p_lbus_0_axi_bnd_n: 1,    //  25
    reg_soft_rst_p_lbus_1_axi_bnd_n: 1,    //  26
    reg_soft_rst_p_lbus_2_axi_bnd_n: 1,    //  27
    reg_soft_rst_p_lbus_3_axi_bnd_n: 1,    //  28
    reg_soft_rst_p_lbus_4_axi_bnd_n: 1,    //  29
    reg_soft_rst_p_lbus_5_axi_bnd_n: 1,    //  30
    reg_soft_rst_p_lbus_6_axi_bnd_n: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0014    crg_lbus005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_lbus_7_axi_bnd_n: 1,    //  0
    reg_soft_rst_p_lnx2_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_nd0_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_nd1_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_srcosb_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_sre_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_p_tivvmsb_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_vd0_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_vd0_1_axi_bnd_n: 1,    //   8
    reg_soft_rst_p_vd1_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_vd1_1_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_aud_0_axi_n:  1,    //     13
    reg_soft_rst_x_fmc_0_axi_n:  1,    //     14
    reg_soft_rst_x_fmc_1_axi_n:  1,    //     15
    reg_soft_rst_x_fmc_2_axi_n:  1,    //     16
    reg_soft_rst_x_fmc_3_axi_n:  1,    //     17
    reg_soft_rst_x_fmesb_0_axi_n: 1,    //    18
    reg_soft_rst_x_fms_0_axi_n:  1,    //     19
    reg_soft_rst_x_gfx_0_axi_n:  1,    //     20
    reg_soft_rst_x_gpu_0_axi_n:  1,    //     21
    reg_soft_rst_x_gpu_1_axi_n:  1,    //     22
    reg_soft_rst_x_gsc_0_axi_n:  1,    //     23
    reg_soft_rst_x_gsc_1_axi_n:  1,    //     24
    reg_soft_rst_x_gsc_2_axi_n:  1,    //     25
    reg_soft_rst_x_gsc_3_axi_n:  1,    //     26
    reg_soft_rst_x_imx_0_axi_n:  1,    //     27
    reg_soft_rst_x_imx_1_axi_n:  1,    //     28
    reg_soft_rst_x_imx_2_axi_n:  1,    //     29
    reg_soft_rst_x_imx_3_axi_n:  1,    //     30
    reg_soft_rst_x_iommu_0_axi_n: 1;    //    31
}SCRG_CTRL_LBUS_CRG_LBUS005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0018    crg_lbus006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_iommu_1_axi_n: 1,    //     0
    reg_soft_rst_x_iommu_2_axi_n: 1,    //     1
    reg_soft_rst_x_lb1sb_0_axi_n: 1,    //     2
    reg_soft_rst_x_lbus_0_axi_n: 1,    //      3
    reg_soft_rst_x_lbus_1_axi_n: 1,    //      4
    reg_soft_rst_x_lbus_2_axi_n: 1,    //      5
    reg_soft_rst_x_lbus_3_axi_n: 1,    //      6
    reg_soft_rst_x_lbus_4_axi_n: 1,    //      7
    reg_soft_rst_x_lbus_5_axi_n: 1,    //      8
    reg_soft_rst_x_lbus_6_axi_n: 1,    //      9
    reg_soft_rst_x_lbus_7_axi_n: 1,    //     10
    reg_soft_rst_x_lnx2_0_axi_n: 1,    //     11
    reg_soft_rst_x_nd0_0_axi_n:  1,    //     12
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     13
    reg_soft_rst_x_srcosb_0_axi_n: 1,    //   14
    reg_soft_rst_x_sre_0_axi_n:  1,    //     15
    reg_soft_rst_x_tivvmsb_0_axi_n: 1,    //  16
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     17
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     18
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     19
    reg_soft_rst_x_vd1_1_axi_n:  1,    //     20
    reg_soft_rst_x_vdo_0_axi_n:  1,    //     21
    reg_soft_rst_x_vdo_1_axi_n:  1,    //     22
                              :  9;    //  31:23 reserved
}SCRG_CTRL_LBUS_CRG_LBUS006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS000_O26A0_T    crg_lbus000;          // 0xC422_0000
    SCRG_CTRL_LBUS_CRG_LBUS001_O26A0_T    crg_lbus001;          // 0xC422_0004
    SCRG_CTRL_LBUS_CRG_LBUS002_O26A0_T    crg_lbus002;          // 0xC422_0008
    SCRG_CTRL_LBUS_CRG_LBUS003_O26A0_T    crg_lbus003;          // 0xC422_000C
    SCRG_CTRL_LBUS_CRG_LBUS004_O26A0_T    crg_lbus004;          // 0xC422_0010
    SCRG_CTRL_LBUS_CRG_LBUS005_O26A0_T    crg_lbus005;          // 0xC422_0014
    SCRG_CTRL_LBUS_CRG_LBUS006_O26A0_T    crg_lbus006;          // 0xC422_0018
}SCRG_CTRL_LBUS_REG_O26A0_T;
/* 7 regs */

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

#define SCRG_CTRL_LBUS_CRG_LBUS000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_LBUS_CRG_LBUS001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_LBUS_CRG_LBUS002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_LBUS_CRG_LBUS003_O26A0_T_OFF              (BASEADDRESS+0x000C)
#define SCRG_CTRL_LBUS_CRG_LBUS004_O26A0_T_OFF              (BASEADDRESS+0x0010)
#define SCRG_CTRL_LBUS_CRG_LBUS005_O26A0_T_OFF              (BASEADDRESS+0x0014)
#define SCRG_CTRL_LBUS_CRG_LBUS006_O26A0_T_OFF              (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC422_0000    crg_lbus000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0004    crg_lbus001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0008    crg_lbus002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_aud_0__axi_bb_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_fmc_0__axi_bb_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_fmc_1__axi_bb_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_x_fmc_2__axi_bb_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_x_fmc_3__axi_bb_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_x_fmesb_0__axi_bb_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_x_fms_0__axi_bb_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_x_gfx_0__axi_bb_clk_gate_en: 1;    //  7
    UINT32 reg_adaprx_x_gpu_0__axi_bb_clk_gate_en: 1;    //  8
    UINT32 reg_adaprx_x_gpu_1__axi_bb_clk_gate_en: 1;    //  9
    UINT32 reg_adaprx_x_gsc_0__axi_bb_clk_gate_en: 1;    //  10
    UINT32 reg_adaprx_x_gsc_1__axi_bb_clk_gate_en: 1;    //  11
    UINT32 reg_adaprx_x_gsc_2__axi_bb_clk_gate_en: 1;    //  12
    UINT32 reg_adaprx_x_gsc_3__axi_bb_clk_gate_en: 1;    //  13
    UINT32 reg_adaprx_x_imx_0__axi_bb_clk_gate_en: 1;    //  14
    UINT32 reg_adaprx_x_imx_1__axi_bb_clk_gate_en: 1;    //  15
    UINT32 reg_adaprx_x_imx_2__axi_bb_clk_gate_en: 1;    //  16
    UINT32 reg_adaprx_x_imx_3__axi_bb_clk_gate_en: 1;    //  17
    UINT32 reg_adaprx_x_iommu_0__axi_bb_clk_gate_en: 1;    //  18
    UINT32 reg_adaprx_x_iommu_1__axi_bb_clk_gate_en: 1;    //  19
    UINT32 reg_adaprx_x_iommu_2__axi_bb_clk_gate_en: 1;    //  20
    UINT32 reg_adaprx_x_lb1sb_0__axi_bb_clk_gate_en: 1;    //  21
    UINT32 reg_adaprx_x_lnx2_0__axi_bb_clk_gate_en: 1;    //  22
    UINT32 reg_adaprx_x_nd0_0__axi_bb_clk_gate_en: 1;    //  23
    UINT32 reg_adaprx_x_nd1_0__axi_bb_clk_gate_en: 1;    //  24
    UINT32 reg_adaprx_x_srcosb_0__axi_bb_clk_gate_en: 1;    //  25
    UINT32 reg_adaprx_x_sre_0__axi_bb_clk_gate_en: 1;    //  26
    UINT32 reg_adaprx_x_tivvmsb_0__axi_bb_clk_gate_en: 1;    //  27
    UINT32 reg_adaprx_x_vd0_0__axi_bb_clk_gate_en: 1;    //  28
    UINT32 reg_adaprx_x_vd0_1__axi_bb_clk_gate_en: 1;    //  29
    UINT32 reg_adaprx_x_vd1_0__axi_bb_clk_gate_en: 1;    //  30
    UINT32 reg_adaprx_x_vd1_1__axi_bb_clk_gate_en: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_000C    crg_lbus003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_vdo_0__axi_bb_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_vdo_1__axi_bb_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_lbus_0__axi_bb_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_x_lbus_1__axi_bb_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_x_lbus_2__axi_bb_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_x_lbus_3__axi_bb_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_x_lbus_4__axi_bb_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_x_lbus_5__axi_bb_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_x_lbus_6__axi_bb_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_x_lbus_7__axi_bb_clk_gate_en: 1;    //  9
    UINT32 reg_apb_clk_gate_en:  1;    //     10
    UINT32 reg_async_axi_bb_clk_gate_en: 1;    //  11
    UINT32 reg_axi_884_clk_gate_en: 1;    //  12
    UINT32 reg_axi_bb_clk_gate_en: 1;    //   13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0010    crg_lbus004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_async_axi_bb_n: 1;    //  1
    UINT32 reg_soft_rst_axi_bb_n: 1;    //     2
    UINT32 reg_soft_rst_p_aud_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_fmc_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_fmc_1_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_fmc_2_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_fmc_3_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_fmesb_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_fms_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_gfx_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_gpu_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_gpu_1_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_gsc_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_gsc_1_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_gsc_2_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_gsc_3_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_imx_0_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_p_imx_1_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_p_imx_2_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_imx_3_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_iommu_0_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_iommu_1_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_iommu_2_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_lb1sb_0_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_p_lbus_0_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_p_lbus_1_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_p_lbus_2_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_p_lbus_3_axi_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_p_lbus_4_axi_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_p_lbus_5_axi_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_p_lbus_6_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0014    crg_lbus005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_lbus_7_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_p_lnx2_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_nd0_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_nd1_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_srcosb_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_sre_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_tivvmsb_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_vd0_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_vd0_1_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_vd1_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_vd1_1_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_fmc_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_fmc_1_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_fmc_2_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_fmc_3_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_fmesb_0_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_fms_0_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_gfx_0_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_gpu_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_gpu_1_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_gsc_0_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_gsc_1_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_gsc_2_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_gsc_3_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_imx_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_imx_1_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_imx_2_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_imx_3_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_iommu_0_axi_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_0018    crg_lbus006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_iommu_1_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_iommu_2_axi_n: 1;    //  1
    UINT32 reg_soft_rst_x_lb1sb_0_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_lbus_0_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_lbus_1_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_lbus_2_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_lbus_3_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lbus_4_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_lbus_5_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lbus_6_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_7_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_lnx2_0_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_nd0_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_srcosb_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_sre_0_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_tivvmsb_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  22
    UINT32 resvd00            :  9;    //  31:23 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS000_O26A0_T    crg_lbus000;          // 0xC422_0000
    SCRG_CTRL_LBUS_CRG_LBUS001_O26A0_T    crg_lbus001;          // 0xC422_0004
    SCRG_CTRL_LBUS_CRG_LBUS002_O26A0_T    crg_lbus002;          // 0xC422_0008
    SCRG_CTRL_LBUS_CRG_LBUS003_O26A0_T    crg_lbus003;          // 0xC422_000C
    SCRG_CTRL_LBUS_CRG_LBUS004_O26A0_T    crg_lbus004;          // 0xC422_0010
    SCRG_CTRL_LBUS_CRG_LBUS005_O26A0_T    crg_lbus005;          // 0xC422_0014
    SCRG_CTRL_LBUS_CRG_LBUS006_O26A0_T    crg_lbus006;          // 0xC422_0018
}SCRG_CTRL_LBUS_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_LBUS_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

