#ifndef _SCRG_CTRL_VD0_M23A0_REG_H_
#define _SCRG_CTRL_VD0_M23A0_REG_H_

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
    0xCE67_0000    crg_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_0004    crg_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_0008    crg_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi0_clk_gate_en      :  1,    //      1
    reg_axi1_clk_gate_en      :  1,    //      2
    reg_bus_clk_gate_en       :  1,    //      3
    reg_hevc_clk_gate_en      :  1,    //      4
    reg_hevc_ed_clk_gate_en   :  1,    //      5
    reg_hevc_lcu_clk_gate_en  :  1,    //      6
    reg_mem_clk_gate_en       :  1,    //      7
    reg_vvc_ed_clk_gate_en    :  1,    //      8
    reg_vvc_lcu_clk_gate_en   :  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_VD0_CRG_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_000C    crg_vd003 ''
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
    reg_soft_rst_p_vd0_0_axi_bnd_n: 1,    //   8
    reg_soft_rst_p_vd0_1_axi_bnd_n: 1,    //   9
    reg_soft_rst_vvc_ed_n     :  1,    //     10
    reg_soft_rst_vvc_lcu_n    :  1,    //     11
    reg_soft_rst_vvc_n        :  1,    //     12
    reg_soft_rst_x_vd0_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     14
    reg_soft_rst_x_vd0_1_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_VD0_CRG_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD000_M23A0_T    crg_vd000  ;             // 0xCE67_0000
    SCRG_CTRL_VD0_CRG_VD001_M23A0_T    crg_vd001  ;             // 0xCE67_0004
    SCRG_CTRL_VD0_CRG_VD002_M23A0_T    crg_vd002  ;             // 0xCE67_0008
    SCRG_CTRL_VD0_CRG_VD003_M23A0_T    crg_vd003  ;             // 0xCE67_000C
}SCRG_CTRL_VD0_REG_M23A0_T;
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

#define SCRG_CTRL_VD0_CRG_VD000_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD0_CRG_VD001_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD0_CRG_VD002_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD0_CRG_VD003_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE67_0000    crg_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_0004    crg_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_0008    crg_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi0_clk_gate_en: 1;    //      1
    UINT32 reg_axi1_clk_gate_en: 1;    //      2
    UINT32 reg_bus_clk_gate_en:  1;    //      3
    UINT32 reg_hevc_clk_gate_en: 1;    //      4
    UINT32 reg_hevc_ed_clk_gate_en: 1;    //   5
    UINT32 reg_hevc_lcu_clk_gate_en: 1;    //  6
    UINT32 reg_mem_clk_gate_en:  1;    //      7
    UINT32 reg_vvc_ed_clk_gate_en: 1;    //    8
    UINT32 reg_vvc_lcu_clk_gate_en: 1;    //   9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_VD0_CRG_VD002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE67_000C    crg_vd003 ''
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
    UINT32 reg_soft_rst_p_vd0_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_vd0_1_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_vvc_ed_n: 1;    //    10
    UINT32 reg_soft_rst_vvc_lcu_n: 1;    //   11
    UINT32 reg_soft_rst_vvc_n :  1;    //     12
    UINT32 reg_soft_rst_x_vd0_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_vd0_1_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_VD0_CRG_VD003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD000_M23A0_T    crg_vd000  ;             // 0xCE67_0000
    SCRG_CTRL_VD0_CRG_VD001_M23A0_T    crg_vd001  ;             // 0xCE67_0004
    SCRG_CTRL_VD0_CRG_VD002_M23A0_T    crg_vd002  ;             // 0xCE67_0008
    SCRG_CTRL_VD0_CRG_VD003_M23A0_T    crg_vd003  ;             // 0xCE67_000C
}SCRG_CTRL_VD0_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

