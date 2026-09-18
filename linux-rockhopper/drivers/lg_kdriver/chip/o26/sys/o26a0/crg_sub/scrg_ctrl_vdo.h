#ifndef _SCRG_CTRL_VDO_REG_O26A0_H_
#define _SCRG_CTRL_VDO_REG_O26A0_H_

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
    0xCC26_0000    crg_vdo000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_0004    crg_vdo001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_0008    crg_vdo002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_h_vdo_0__de_clk_gate_en: 1,    //  0
    reg_adaptx_h_vdo_1__de_clk_gate_en: 1,    //  1
    reg_adaptx_h_vdo_2__de_clk_gate_en: 1,    //  2
    reg_adaptx_h_vdo_3__de_clk_gate_en: 1,    //  3
    reg_adaptx_h_vdo_4__de_clk_gate_en: 1,    //  4
    reg_adaptx_h_vdo_5__de_clk_gate_en: 1,    //  5
    reg_adaptx_x_vdo_0__axi_clk_gate_en: 1,    //  6
    reg_adaptx_x_vdo_1__axi_clk_gate_en: 1,    //  7
    reg_apb_clk_gate_en       :  1,    //      8
    reg_axi_clk_gate_en       :  1,    //      9
    reg_de_clk_gate_en        :  1,    //     10
    reg_vdo0_clk_gate_en      :  1,    //     11
    reg_vdo1_clk_gate_en      :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_VDO_CRG_VDO002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_000C    crg_vdo003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_de_n         :  1,    //      3
    reg_soft_rst_h_vdo_0_de_bnd_n: 1,    //    4
    reg_soft_rst_h_vdo_1_de_bnd_n: 1,    //    5
    reg_soft_rst_h_vdo_2_de_bnd_n: 1,    //    6
    reg_soft_rst_h_vdo_3_de_bnd_n: 1,    //    7
    reg_soft_rst_h_vdo_4_de_bnd_n: 1,    //    8
    reg_soft_rst_h_vdo_5_de_bnd_n: 1,    //    9
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_vdo0_n       :  1,    //     12
    reg_soft_rst_vdo1_n       :  1,    //     13
    reg_soft_rst_x_vdo_0_axi_n:  1,    //     14
    reg_soft_rst_x_vdo_1_axi_n:  1,    //     15
                              : 16;    //  31:16 reserved
}SCRG_CTRL_VDO_CRG_VDO003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO000_O26A0_T    crg_vdo000;             // 0xCC26_0000
    SCRG_CTRL_VDO_CRG_VDO001_O26A0_T    crg_vdo001;             // 0xCC26_0004
    SCRG_CTRL_VDO_CRG_VDO002_O26A0_T    crg_vdo002;             // 0xCC26_0008
    SCRG_CTRL_VDO_CRG_VDO003_O26A0_T    crg_vdo003;             // 0xCC26_000C
}SCRG_CTRL_VDO_REG_O26A0_T;
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

#define SCRG_CTRL_VDO_CRG_VDO000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_VDO_CRG_VDO001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_VDO_CRG_VDO002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_VDO_CRG_VDO003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC26_0000    crg_vdo000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_0004    crg_vdo001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_0008    crg_vdo002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_h_vdo_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_h_vdo_1__de_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_h_vdo_2__de_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_h_vdo_3__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_h_vdo_4__de_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_h_vdo_5__de_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_x_vdo_0__axi_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_x_vdo_1__axi_clk_gate_en: 1;    //  7
    UINT32 reg_apb_clk_gate_en:  1;    //      8
    UINT32 reg_axi_clk_gate_en:  1;    //      9
    UINT32 reg_de_clk_gate_en :  1;    //     10
    UINT32 reg_vdo0_clk_gate_en: 1;    //     11
    UINT32 reg_vdo1_clk_gate_en: 1;    //     12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC26_000C    crg_vdo003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_de_n  :  1;    //      3
    UINT32 reg_soft_rst_h_vdo_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_vdo_1_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_vdo_2_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_vdo_3_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_vdo_4_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_vdo_5_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_vdo0_n:  1;    //     12
    UINT32 reg_soft_rst_vdo1_n:  1;    //     13
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO000_O26A0_T    crg_vdo000;             // 0xCC26_0000
    SCRG_CTRL_VDO_CRG_VDO001_O26A0_T    crg_vdo001;             // 0xCC26_0004
    SCRG_CTRL_VDO_CRG_VDO002_O26A0_T    crg_vdo002;             // 0xCC26_0008
    SCRG_CTRL_VDO_CRG_VDO003_O26A0_T    crg_vdo003;             // 0xCC26_000C
}SCRG_CTRL_VDO_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_VDO_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

