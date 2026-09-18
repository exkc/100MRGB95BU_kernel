#ifndef _SCRG_CTRL_VDO_REG_O24A0_H_
#define _SCRG_CTRL_VDO_REG_O24A0_H_

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
    0xCCC4_0000    crg_vdo0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_0004    crg_vdo1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_0008    crg_vdo2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
    reg_vdo0_clk_gate_en      :  1,    //      3
    reg_vdo1_clk_gate_en      :  1,    //      4
    reg_vdo2_clk_gate_en      :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_VDO_CRG_VDO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_000C    crg_vdo3 ''
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
    reg_soft_rst_h_vdo_6_de_bnd_n: 1,    //   10
    reg_soft_rst_h_vdo_7_de_bnd_n: 1,    //   11
    reg_soft_rst_h_vdo_8_de_bnd_n: 1,    //   12
    reg_soft_rst_h_vdo_9_de_bnd_n: 1,    //   13
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_vdo_2_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_vdo_3_axi_bnd_n: 1,    //  17
    reg_soft_rst_vdo0_n       :  1,    //     18
    reg_soft_rst_vdo1_n       :  1,    //     19
    reg_soft_rst_vdo2_n       :  1,    //     20
    reg_soft_rst_x_vdo_0_axi_bnd_n: 1,    //  21
    reg_soft_rst_x_vdo_0_axi_n:  1,    //     22
    reg_soft_rst_x_vdo_1_axi_bnd_n: 1,    //  23
    reg_soft_rst_x_vdo_1_axi_n:  1,    //     24
    reg_soft_rst_x_vdo_2_axi_bnd_n: 1,    //  25
    reg_soft_rst_x_vdo_2_axi_n:  1,    //     26
    reg_soft_rst_x_vdo_3_axi_bnd_n: 1,    //  27
    reg_soft_rst_x_vdo_3_axi_n:  1,    //     28
                              :  3;    //  31:29 reserved
}SCRG_CTRL_VDO_CRG_VDO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO0_O24A0_T     crg_vdo0   ;             // 0xCCC4_0000
    SCRG_CTRL_VDO_CRG_VDO1_O24A0_T     crg_vdo1   ;             // 0xCCC4_0004
    SCRG_CTRL_VDO_CRG_VDO2_O24A0_T     crg_vdo2   ;             // 0xCCC4_0008
    SCRG_CTRL_VDO_CRG_VDO3_O24A0_T     crg_vdo3   ;             // 0xCCC4_000C
}SCRG_CTRL_VDO_REG_O24A0_T;
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

#define SCRG_CTRL_VDO_CRG_VDO0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_VDO_CRG_VDO1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_VDO_CRG_VDO2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_VDO_CRG_VDO3_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCC4_0000    crg_vdo0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_0004    crg_vdo1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_0008    crg_vdo2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 reg_vdo0_clk_gate_en: 1;    //      3
    UINT32 reg_vdo1_clk_gate_en: 1;    //      4
    UINT32 reg_vdo2_clk_gate_en: 1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC4_000C    crg_vdo3 ''
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
    UINT32 reg_soft_rst_h_vdo_6_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_vdo_7_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_vdo_8_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_vdo_9_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_vdo_2_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_vdo_3_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_vdo0_n:  1;    //     18
    UINT32 reg_soft_rst_vdo1_n:  1;    //     19
    UINT32 reg_soft_rst_vdo2_n:  1;    //     20
    UINT32 reg_soft_rst_x_vdo_0_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_vdo_1_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_vdo_2_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_x_vdo_2_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_vdo_3_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_x_vdo_3_axi_n: 1;    //  28
    UINT32 resvd00            :  3;    //  31:29 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vdo Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO0_O24A0_T     crg_vdo0   ;             // 0xCCC4_0000
    SCRG_CTRL_VDO_CRG_VDO1_O24A0_T     crg_vdo1   ;             // 0xCCC4_0004
    SCRG_CTRL_VDO_CRG_VDO2_O24A0_T     crg_vdo2   ;             // 0xCCC4_0008
    SCRG_CTRL_VDO_CRG_VDO3_O24A0_T     crg_vdo3   ;             // 0xCCC4_000C
}SCRG_CTRL_VDO_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_VDO_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

