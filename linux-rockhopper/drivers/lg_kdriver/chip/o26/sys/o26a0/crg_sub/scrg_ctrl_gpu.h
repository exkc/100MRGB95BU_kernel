#ifndef _SCRG_CTRL_GPU_REG_O26A0_H_
#define _SCRG_CTRL_GPU_REG_O26A0_H_

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
    0xC604_0000    crg_gpu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GPU_CRG_GPU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0004    crg_gpu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GPU_CRG_GPU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0008    crg_gpu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_gpu_0__axi_clk_gate_en: 1,    //  0
    reg_adaptx_x_gpu_1__axi_clk_gate_en: 1,    //  1
    reg_apb_clk_gate_en       :  1,    //      2
    reg_axi_clk_gate_en       :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_GPU_CRG_GPU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_000C    crg_gpu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_gpu_n        :  1,    //      2
    reg_soft_rst_p_gpu_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_gpu_1_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_gpu_0_axi_n:  1,    //      5
    reg_soft_rst_x_gpu_1_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_GPU_CRG_GPU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0010    crg_gpu004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_sel           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_gpu_clk_sel           :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}SCRG_CTRL_GPU_CRG_GPU004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GPU_CRG_GPU000_O26A0_T    crg_gpu000;             // 0xC604_0000
    SCRG_CTRL_GPU_CRG_GPU001_O26A0_T    crg_gpu001;             // 0xC604_0004
    SCRG_CTRL_GPU_CRG_GPU002_O26A0_T    crg_gpu002;             // 0xC604_0008
    SCRG_CTRL_GPU_CRG_GPU003_O26A0_T    crg_gpu003;             // 0xC604_000C
    SCRG_CTRL_GPU_CRG_GPU004_O26A0_T    crg_gpu004;             // 0xC604_0010
}SCRG_CTRL_GPU_REG_O26A0_T;
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

#define SCRG_CTRL_GPU_CRG_GPU000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_GPU_CRG_GPU001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_GPU_CRG_GPU002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_GPU_CRG_GPU003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_GPU_CRG_GPU004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xC604_0000    crg_gpu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GPU_CRG_GPU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0004    crg_gpu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GPU_CRG_GPU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0008    crg_gpu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_gpu_0__axi_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_gpu_1__axi_clk_gate_en: 1;    //  1
    UINT32 reg_apb_clk_gate_en:  1;    //      2
    UINT32 reg_axi_clk_gate_en:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_GPU_CRG_GPU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_000C    crg_gpu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_gpu_n :  1;    //      2
    UINT32 reg_soft_rst_p_gpu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_gpu_1_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_gpu_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_gpu_1_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_GPU_CRG_GPU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC604_0010    crg_gpu004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_sel    :  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_gpu_clk_sel    :  2;    //   5: 4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_GPU_CRG_GPU004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GPU_CRG_GPU000_O26A0_T    crg_gpu000;             // 0xC604_0000
    SCRG_CTRL_GPU_CRG_GPU001_O26A0_T    crg_gpu001;             // 0xC604_0004
    SCRG_CTRL_GPU_CRG_GPU002_O26A0_T    crg_gpu002;             // 0xC604_0008
    SCRG_CTRL_GPU_CRG_GPU003_O26A0_T    crg_gpu003;             // 0xC604_000C
    SCRG_CTRL_GPU_CRG_GPU004_O26A0_T    crg_gpu004;             // 0xC604_0010
}SCRG_CTRL_GPU_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_GPU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

