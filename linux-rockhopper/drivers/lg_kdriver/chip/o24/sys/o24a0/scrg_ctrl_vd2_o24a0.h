#ifndef _SCRG_CTRL_VD2_REG_O24A0_H_
#define _SCRG_CTRL_VD2_REG_O24A0_H_

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
    0xCECB_0000    crg_vd20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD2_CRG_VD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0004    crg_vd21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD2_CRG_VD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0008    crg_vd22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi0_clk_gate_en      :  1,    //      1
    reg_axi1_clk_gate_en      :  1,    //      2
    reg_bus_clk_gate_en       :  1,    //      3
    reg_mem_clk_gate_en       :  1,    //      4
    reg_msvc_396_clk_gate_en  :  1,    //      5
    reg_msvc_clk_gate_en      :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VD2_CRG_VD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_000C    crg_vd23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bus_n        :  1,    //      3
    reg_soft_rst_mem_n        :  1,    //      4
    reg_soft_rst_msvc_396_n   :  1,    //      5
    reg_soft_rst_msvc_n       :  1,    //      6
    reg_soft_rst_p_vd2_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_vd2_1_axi_bnd_n: 1,    //   8
    reg_soft_rst_x_vd2_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_vd2_0_axi_n:  1,    //     10
    reg_soft_rst_x_vd2_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_vd2_1_axi_n:  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_VD2_CRG_VD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0010    crg_vd24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_mem_clk_sel           :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_msvc_396_clk_sel      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_msvc_clk_sel          :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_VD2_CRG_VD24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD2_CRG_VD20_O24A0_T     crg_vd20   ;             // 0xCECB_0000
    SCRG_CTRL_VD2_CRG_VD21_O24A0_T     crg_vd21   ;             // 0xCECB_0004
    SCRG_CTRL_VD2_CRG_VD22_O24A0_T     crg_vd22   ;             // 0xCECB_0008
    SCRG_CTRL_VD2_CRG_VD23_O24A0_T     crg_vd23   ;             // 0xCECB_000C
    SCRG_CTRL_VD2_CRG_VD24_O24A0_T     crg_vd24   ;             // 0xCECB_0010
}SCRG_CTRL_VD2_REG_O24A0_T;
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

#define SCRG_CTRL_VD2_CRG_VD20_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD2_CRG_VD21_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD2_CRG_VD22_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD2_CRG_VD23_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_VD2_CRG_VD24_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCECB_0000    crg_vd20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD2_CRG_VD20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0004    crg_vd21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD2_CRG_VD21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0008    crg_vd22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi0_clk_gate_en: 1;    //      1
    UINT32 reg_axi1_clk_gate_en: 1;    //      2
    UINT32 reg_bus_clk_gate_en:  1;    //      3
    UINT32 reg_mem_clk_gate_en:  1;    //      4
    UINT32 reg_msvc_396_clk_gate_en: 1;    //  5
    UINT32 reg_msvc_clk_gate_en: 1;    //      6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VD2_CRG_VD22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_000C    crg_vd23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bus_n :  1;    //      3
    UINT32 reg_soft_rst_mem_n :  1;    //      4
    UINT32 reg_soft_rst_msvc_396_n: 1;    //   5
    UINT32 reg_soft_rst_msvc_n:  1;    //      6
    UINT32 reg_soft_rst_p_vd2_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_vd2_1_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_vd2_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_vd2_0_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_vd2_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_vd2_1_axi_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_VD2_CRG_VD23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_0010    crg_vd24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_mem_clk_sel    :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_msvc_396_clk_sel: 1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_msvc_clk_sel   :  1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_VD2_CRG_VD24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD2_CRG_VD20_O24A0_T     crg_vd20   ;             // 0xCECB_0000
    SCRG_CTRL_VD2_CRG_VD21_O24A0_T     crg_vd21   ;             // 0xCECB_0004
    SCRG_CTRL_VD2_CRG_VD22_O24A0_T     crg_vd22   ;             // 0xCECB_0008
    SCRG_CTRL_VD2_CRG_VD23_O24A0_T     crg_vd23   ;             // 0xCECB_000C
    SCRG_CTRL_VD2_CRG_VD24_O24A0_T     crg_vd24   ;             // 0xCECB_0010
}SCRG_CTRL_VD2_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_VD2_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

