#ifndef _SCRG_CTRL_VD1_REG_O24A0_H_
#define _SCRG_CTRL_VD1_REG_O24A0_H_

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
    0xCEC3_0000    crg_vd10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_0004    crg_vd11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_0008    crg_vd12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi0_clk_gate_en      :  1,    //      1
    reg_axi1_clk_gate_en      :  1,    //      2
    reg_bali_clk_gate_en      :  1,    //      3
    reg_bali_ed_clk_gate_en   :  1,    //      4
    reg_bali_lcu_clk_gate_en  :  1,    //      5
    reg_bus_clk_gate_en       :  1,    //      6
    reg_h264_clk_gate_en      :  1,    //      7
    reg_mem_clk_gate_en       :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_000C    crg_vd13 ''
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
    reg_soft_rst_f_vd0_0_bali_lcu_bnd_n: 1,    //  7
    reg_soft_rst_f_vd1_0_bali_lcu_bnd_n: 1,    //  8
    reg_soft_rst_h264_n       :  1,    //      9
    reg_soft_rst_mem_n        :  1,    //     10
    reg_soft_rst_p_vd1_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_vd1_1_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_vd1_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     14
    reg_soft_rst_x_vd1_1_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_vd1_1_axi_n:  1,    //     16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_VD1_CRG_VD13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD10_O24A0_T     crg_vd10   ;             // 0xCEC3_0000
    SCRG_CTRL_VD1_CRG_VD11_O24A0_T     crg_vd11   ;             // 0xCEC3_0004
    SCRG_CTRL_VD1_CRG_VD12_O24A0_T     crg_vd12   ;             // 0xCEC3_0008
    SCRG_CTRL_VD1_CRG_VD13_O24A0_T     crg_vd13   ;             // 0xCEC3_000C
}SCRG_CTRL_VD1_REG_O24A0_T;
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

#define SCRG_CTRL_VD1_CRG_VD10_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD1_CRG_VD11_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD1_CRG_VD12_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD1_CRG_VD13_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCEC3_0000    crg_vd10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_0004    crg_vd11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_0008    crg_vd12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi0_clk_gate_en: 1;    //      1
    UINT32 reg_axi1_clk_gate_en: 1;    //      2
    UINT32 reg_bali_clk_gate_en: 1;    //      3
    UINT32 reg_bali_ed_clk_gate_en: 1;    //   4
    UINT32 reg_bali_lcu_clk_gate_en: 1;    //  5
    UINT32 reg_bus_clk_gate_en:  1;    //      6
    UINT32 reg_h264_clk_gate_en: 1;    //      7
    UINT32 reg_mem_clk_gate_en:  1;    //      8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC3_000C    crg_vd13 ''
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
    UINT32 reg_soft_rst_f_vd0_0_bali_lcu_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_vd1_0_bali_lcu_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h264_n:  1;    //      9
    UINT32 reg_soft_rst_mem_n :  1;    //     10
    UINT32 reg_soft_rst_p_vd1_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_vd1_1_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_vd1_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_vd1_1_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_VD1_CRG_VD13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD10_O24A0_T     crg_vd10   ;             // 0xCEC3_0000
    SCRG_CTRL_VD1_CRG_VD11_O24A0_T     crg_vd11   ;             // 0xCEC3_0004
    SCRG_CTRL_VD1_CRG_VD12_O24A0_T     crg_vd12   ;             // 0xCEC3_0008
    SCRG_CTRL_VD1_CRG_VD13_O24A0_T     crg_vd13   ;             // 0xCEC3_000C
}SCRG_CTRL_VD1_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_VD1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

