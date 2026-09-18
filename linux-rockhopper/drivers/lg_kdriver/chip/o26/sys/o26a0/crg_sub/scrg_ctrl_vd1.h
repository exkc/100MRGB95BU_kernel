#ifndef _SCRG_CTRL_VD1_REG_O26A0_H_
#define _SCRG_CTRL_VD1_REG_O26A0_H_

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
    0xCE59_0000    crg_vd1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_0004    crg_vd1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_0008    crg_vd1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_vd1_0__bus_clk_gate_en: 1,    //  0
    reg_adaptx_x_vd1_1__bus_clk_gate_en: 1,    //  1
    reg_apb_clk_gate_en       :  1,    //      2
    reg_axi0_clk_gate_en      :  1,    //      3
    reg_axi1_clk_gate_en      :  1,    //      4
    reg_bali_clk_gate_en      :  1,    //      5
    reg_bali_ed_clk_gate_en   :  1,    //      6
    reg_bali_lcu_clk_gate_en  :  1,    //      7
    reg_bus_clk_gate_en       :  1,    //      8
    reg_h264_clk_gate_en      :  1,    //      9
    reg_mem_clk_gate_en       :  1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_VD1_CRG_VD1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_000C    crg_vd1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bali_ed_n    :  1,    //      3
    reg_soft_rst_bali_lcu_n   :  1,    //      4
    reg_soft_rst_bali_n       :  1,    //      5
    reg_soft_rst_bus_n        :  1,    //      6
    reg_soft_rst_h264_n       :  1,    //      7
    reg_soft_rst_mem_n        :  1,    //      8
    reg_soft_rst_p_vd1_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_vd1_1_axi_bnd_n: 1,    //  10
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     11
    reg_soft_rst_x_vd1_1_axi_n:  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_VD1_CRG_VD1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD1000_O26A0_T    crg_vd1000;             // 0xCE59_0000
    SCRG_CTRL_VD1_CRG_VD1001_O26A0_T    crg_vd1001;             // 0xCE59_0004
    SCRG_CTRL_VD1_CRG_VD1002_O26A0_T    crg_vd1002;             // 0xCE59_0008
    SCRG_CTRL_VD1_CRG_VD1003_O26A0_T    crg_vd1003;             // 0xCE59_000C
}SCRG_CTRL_VD1_REG_O26A0_T;
/* 4 regs */

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

#define SCRG_CTRL_VD1_CRG_VD1000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD1_CRG_VD1001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD1_CRG_VD1002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD1_CRG_VD1003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE59_0000    crg_vd1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_0004    crg_vd1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_0008    crg_vd1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_vd1_0__bus_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_vd1_1__bus_clk_gate_en: 1;    //  1
    UINT32 reg_apb_clk_gate_en:  1;    //      2
    UINT32 reg_axi0_clk_gate_en: 1;    //      3
    UINT32 reg_axi1_clk_gate_en: 1;    //      4
    UINT32 reg_bali_clk_gate_en: 1;    //      5
    UINT32 reg_bali_ed_clk_gate_en: 1;    //   6
    UINT32 reg_bali_lcu_clk_gate_en: 1;    //  7
    UINT32 reg_bus_clk_gate_en:  1;    //      8
    UINT32 reg_h264_clk_gate_en: 1;    //      9
    UINT32 reg_mem_clk_gate_en:  1;    //     10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_VD1_CRG_VD1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE59_000C    crg_vd1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bali_ed_n: 1;    //    3
    UINT32 reg_soft_rst_bali_lcu_n: 1;    //   4
    UINT32 reg_soft_rst_bali_n:  1;    //      5
    UINT32 reg_soft_rst_bus_n :  1;    //      6
    UINT32 reg_soft_rst_h264_n:  1;    //      7
    UINT32 reg_soft_rst_mem_n :  1;    //      8
    UINT32 reg_soft_rst_p_vd1_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_vd1_1_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_VD1_CRG_VD1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD1000_O26A0_T    crg_vd1000;             // 0xCE59_0000
    SCRG_CTRL_VD1_CRG_VD1001_O26A0_T    crg_vd1001;             // 0xCE59_0004
    SCRG_CTRL_VD1_CRG_VD1002_O26A0_T    crg_vd1002;             // 0xCE59_0008
    SCRG_CTRL_VD1_CRG_VD1003_O26A0_T    crg_vd1003;             // 0xCE59_000C
}SCRG_CTRL_VD1_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_VD1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

