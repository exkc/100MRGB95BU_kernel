#ifndef _SCRG_CTRL_VDO_M23A0_REG_H_
#define _SCRG_CTRL_VDO_M23A0_REG_H_

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
    0xCC72_0000    crg_vdo00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0004    crg_vdo01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0008    crg_vdo02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bodp0_clk_gate_en     :  1,    //      0
    reg_vdo0_clk_gate_en      :  1,    //      1
    reg_vdo1_clk_gate_en      :  1,    //      2
    reg_vdo_apb_clk_gate_en   :  1,    //      3
    reg_vdo_axi_clk_gate_en   :  1,    //      4
    reg_vdo_de_clk_gate_en    :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_VDO_CRG_VDO02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_000C    crg_vdo03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_bodp0_n      :  1,    //      3
    reg_soft_rst_de_n         :  1,    //      4
    reg_soft_rst_h_vdo_0_de_bnd_n: 1,    //    5
    reg_soft_rst_h_vdo_1_de_bnd_n: 1,    //    6
    reg_soft_rst_h_vdo_2_de_bnd_n: 1,    //    7
    reg_soft_rst_h_vdo_3_de_bnd_n: 1,    //    8
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  10
    reg_soft_rst_vdo0_n       :  1,    //     11
    reg_soft_rst_vdo1_n       :  1,    //     12
    reg_soft_rst_x_vdo_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_vdo_0_axi_n:  1,    //     14
    reg_soft_rst_x_vdo_1_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_vdo_1_axi_n:  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_VDO_CRG_VDO03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0010    crg_vdo04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bodp0_clk_sel         :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_VDO_CRG_VDO04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO00_M23A0_T    crg_vdo00  ;             // 0xCC72_0000
    SCRG_CTRL_VDO_CRG_VDO01_M23A0_T    crg_vdo01  ;             // 0xCC72_0004
    SCRG_CTRL_VDO_CRG_VDO02_M23A0_T    crg_vdo02  ;             // 0xCC72_0008
    SCRG_CTRL_VDO_CRG_VDO03_M23A0_T    crg_vdo03  ;             // 0xCC72_000C
    SCRG_CTRL_VDO_CRG_VDO04_M23A0_T    crg_vdo04  ;             // 0xCC72_0010
}SCRG_CTRL_VDO_REG_M23A0_T;
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

#define SCRG_CTRL_VDO_CRG_VDO00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_VDO_CRG_VDO01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_VDO_CRG_VDO02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_VDO_CRG_VDO03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_VDO_CRG_VDO04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC72_0000    crg_vdo00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0004    crg_vdo01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0008    crg_vdo02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bodp0_clk_gate_en: 1;    //     0
    UINT32 reg_vdo0_clk_gate_en: 1;    //      1
    UINT32 reg_vdo1_clk_gate_en: 1;    //      2
    UINT32 reg_vdo_apb_clk_gate_en: 1;    //   3
    UINT32 reg_vdo_axi_clk_gate_en: 1;    //   4
    UINT32 reg_vdo_de_clk_gate_en: 1;    //    5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_000C    crg_vdo03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_bodp0_n: 1;    //      3
    UINT32 reg_soft_rst_de_n  :  1;    //      4
    UINT32 reg_soft_rst_h_vdo_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_vdo_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_vdo_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_vdo_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_vdo0_n:  1;    //     11
    UINT32 reg_soft_rst_vdo1_n:  1;    //     12
    UINT32 reg_soft_rst_x_vdo_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_vdo_1_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC72_0010    crg_vdo04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bodp0_clk_sel  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO00_M23A0_T    crg_vdo00  ;             // 0xCC72_0000
    SCRG_CTRL_VDO_CRG_VDO01_M23A0_T    crg_vdo01  ;             // 0xCC72_0004
    SCRG_CTRL_VDO_CRG_VDO02_M23A0_T    crg_vdo02  ;             // 0xCC72_0008
    SCRG_CTRL_VDO_CRG_VDO03_M23A0_T    crg_vdo03  ;             // 0xCC72_000C
    SCRG_CTRL_VDO_CRG_VDO04_M23A0_T    crg_vdo04  ;             // 0xCC72_0010
}SCRG_CTRL_VDO_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

