#ifndef _SCRG_CTRL_VD0_REG_O26A0_H_
#define _SCRG_CTRL_VD0_REG_O26A0_H_

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
    0xCE51_0000    crg_vd0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_0004    crg_vd0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_0008    crg_vd0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_vd0_0__bus_clk_gate_en: 1,    //  0
    reg_adaptx_x_vd0_1__bus_clk_gate_en: 1,    //  1
    reg_apb_clk_gate_en       :  1,    //      2
    reg_axi0_clk_gate_en      :  1,    //      3
    reg_axi1_clk_gate_en      :  1,    //      4
    reg_bus_clk_gate_en       :  1,    //      5
    reg_hevc_clk_gate_en      :  1,    //      6
    reg_hevc_ed_clk_gate_en   :  1,    //      7
    reg_hevc_lcu_clk_gate_en  :  1,    //      8
    reg_mem_clk_gate_en       :  1,    //      9
    reg_msvc_396_clk_gate_en  :  1,    //     10
    reg_msvc_clk_gate_en      :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_VD0_CRG_VD0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_000C    crg_vd0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bus_n        :  1,    //      3
    reg_soft_rst_hevc_ed_n    :  1,    //      4
    reg_soft_rst_hevc_lcu_n   :  1,    //      5
    reg_soft_rst_hevc_n       :  1,    //      6
    reg_soft_rst_mem_n        :  1,    //      7
    reg_soft_rst_msvc_396_n   :  1,    //      8
    reg_soft_rst_msvc_n       :  1,    //      9
    reg_soft_rst_p_vd0_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_vd0_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     12
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_VD0_CRG_VD0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD0000_O26A0_T    crg_vd0000;             // 0xCE51_0000
    SCRG_CTRL_VD0_CRG_VD0001_O26A0_T    crg_vd0001;             // 0xCE51_0004
    SCRG_CTRL_VD0_CRG_VD0002_O26A0_T    crg_vd0002;             // 0xCE51_0008
    SCRG_CTRL_VD0_CRG_VD0003_O26A0_T    crg_vd0003;             // 0xCE51_000C
}SCRG_CTRL_VD0_REG_O26A0_T;
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

#define SCRG_CTRL_VD0_CRG_VD0000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD0_CRG_VD0001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD0_CRG_VD0002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD0_CRG_VD0003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE51_0000    crg_vd0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_0004    crg_vd0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_0008    crg_vd0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_vd0_0__bus_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_vd0_1__bus_clk_gate_en: 1;    //  1
    UINT32 reg_apb_clk_gate_en:  1;    //      2
    UINT32 reg_axi0_clk_gate_en: 1;    //      3
    UINT32 reg_axi1_clk_gate_en: 1;    //      4
    UINT32 reg_bus_clk_gate_en:  1;    //      5
    UINT32 reg_hevc_clk_gate_en: 1;    //      6
    UINT32 reg_hevc_ed_clk_gate_en: 1;    //   7
    UINT32 reg_hevc_lcu_clk_gate_en: 1;    //  8
    UINT32 reg_mem_clk_gate_en:  1;    //      9
    UINT32 reg_msvc_396_clk_gate_en: 1;    //  10
    UINT32 reg_msvc_clk_gate_en: 1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_VD0_CRG_VD0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE51_000C    crg_vd0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bus_n :  1;    //      3
    UINT32 reg_soft_rst_hevc_ed_n: 1;    //    4
    UINT32 reg_soft_rst_hevc_lcu_n: 1;    //   5
    UINT32 reg_soft_rst_hevc_n:  1;    //      6
    UINT32 reg_soft_rst_mem_n :  1;    //      7
    UINT32 reg_soft_rst_msvc_396_n: 1;    //   8
    UINT32 reg_soft_rst_msvc_n:  1;    //      9
    UINT32 reg_soft_rst_p_vd0_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_vd0_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_VD0_CRG_VD0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD0000_O26A0_T    crg_vd0000;             // 0xCE51_0000
    SCRG_CTRL_VD0_CRG_VD0001_O26A0_T    crg_vd0001;             // 0xCE51_0004
    SCRG_CTRL_VD0_CRG_VD0002_O26A0_T    crg_vd0002;             // 0xCE51_0008
    SCRG_CTRL_VD0_CRG_VD0003_O26A0_T    crg_vd0003;             // 0xCE51_000C
}SCRG_CTRL_VD0_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_VD0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

