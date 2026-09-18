#ifndef _VMCU_SCRG_CTRL_VMCU_REG_O26A0_H_
#define _VMCU_SCRG_CTRL_VMCU_REG_O26A0_H_

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
    0xCE3C_0000    crg_vmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_0004    crg_vmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_0008    crg_vmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_e_te_6__te_clk_gate_en: 1,    //  0
    reg_adaprx_e_te_7__te_clk_gate_en: 1,    //  1
    reg_adaprx_f_teipw_0__apb_clk_gate_en: 1,    //  2
    reg_adaprx_f_teipw_1__apb_clk_gate_en: 1,    //  3
    reg_adaprx_f_teipw_2__apb_clk_gate_en: 1,    //  4
    reg_adaprx_f_teipw_3__apb_clk_gate_en: 1,    //  5
    reg_adaptx_x_vmcu_0__bus_clk_gate_en: 1,    //  6
    reg_apb_clk_gate_en       :  1,    //      7
    reg_axi0_clk_gate_en      :  1,    //      8
    reg_axi1_clk_gate_en      :  1,    //      9
    reg_bus_clk_gate_en       :  1,    //     10
    reg_mcu_clk_gate_en       :  1,    //     11
    reg_sys_0_clk_gate_en     :  1,    //     12
    reg_sys_1_clk_gate_en     :  1,    //     13
    reg_sys_2_clk_gate_en     :  1,    //     14
    reg_sys_3_clk_gate_en     :  1,    //     15
    reg_sys_4_clk_gate_en     :  1,    //     16
    reg_sys_5_clk_gate_en     :  1,    //     17
    reg_te_clk_gate_en        :  1,    //     18
                              : 13;    //  31:19 reserved
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_000C    crg_vmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bus_n        :  1,    //      3
    reg_soft_rst_e_te_6_te_bnd_n: 1,    //     4
    reg_soft_rst_e_te_7_te_bnd_n: 1,    //     5
    reg_soft_rst_f_teipw_0_apb_bnd_n: 1,    //  6
    reg_soft_rst_f_teipw_1_apb_bnd_n: 1,    //  7
    reg_soft_rst_f_teipw_2_apb_bnd_n: 1,    //  8
    reg_soft_rst_f_teipw_3_apb_bnd_n: 1,    //  9
    reg_soft_rst_mcu_n        :  1,    //     10
    reg_soft_rst_mcu_sbus_n   :  1,    //     11
    reg_soft_rst_p_vmcu_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_sys_0_n      :  1,    //     13
    reg_soft_rst_sys_1_n      :  1,    //     14
    reg_soft_rst_sys_2_n      :  1,    //     15
    reg_soft_rst_sys_3_n      :  1,    //     16
    reg_soft_rst_sys_4_n      :  1,    //     17
    reg_soft_rst_sys_5_n      :  1,    //     18
    reg_soft_rst_te_n         :  1,    //     19
    reg_soft_rst_x_vmcu_0_axi_n: 1,    //     20
                              : 11;    //  31:21 reserved
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    vmcu_scrg_ctrl_vmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU000_O26A0_T    crg_vmcu000;     // 0xCE3C_0000
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU001_O26A0_T    crg_vmcu001;     // 0xCE3C_0004
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU002_O26A0_T    crg_vmcu002;     // 0xCE3C_0008
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU003_O26A0_T    crg_vmcu003;     // 0xCE3C_000C
}VMCU_SCRG_CTRL_VMCU_REG_O26A0_T;
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

#define VMCU_SCRG_CTRL_VMCU_CRG_VMCU000_O26A0_T_OFF         (BASEADDRESS+0x0000)
#define VMCU_SCRG_CTRL_VMCU_CRG_VMCU001_O26A0_T_OFF         (BASEADDRESS+0x0004)
#define VMCU_SCRG_CTRL_VMCU_CRG_VMCU002_O26A0_T_OFF         (BASEADDRESS+0x0008)
#define VMCU_SCRG_CTRL_VMCU_CRG_VMCU003_O26A0_T_OFF         (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE3C_0000    crg_vmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_0004    crg_vmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_0008    crg_vmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_e_te_6__te_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_e_te_7__te_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_teipw_0__apb_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_f_teipw_1__apb_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_f_teipw_2__apb_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_f_teipw_3__apb_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_x_vmcu_0__bus_clk_gate_en: 1;    //  6
    UINT32 reg_apb_clk_gate_en:  1;    //      7
    UINT32 reg_axi0_clk_gate_en: 1;    //      8
    UINT32 reg_axi1_clk_gate_en: 1;    //      9
    UINT32 reg_bus_clk_gate_en:  1;    //     10
    UINT32 reg_mcu_clk_gate_en:  1;    //     11
    UINT32 reg_sys_0_clk_gate_en: 1;    //    12
    UINT32 reg_sys_1_clk_gate_en: 1;    //    13
    UINT32 reg_sys_2_clk_gate_en: 1;    //    14
    UINT32 reg_sys_3_clk_gate_en: 1;    //    15
    UINT32 reg_sys_4_clk_gate_en: 1;    //    16
    UINT32 reg_sys_5_clk_gate_en: 1;    //    17
    UINT32 reg_te_clk_gate_en :  1;    //     18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE3C_000C    crg_vmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bus_n :  1;    //      3
    UINT32 reg_soft_rst_e_te_6_te_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_e_te_7_te_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_teipw_0_apb_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_teipw_1_apb_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_teipw_2_apb_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_teipw_3_apb_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_mcu_n :  1;    //     10
    UINT32 reg_soft_rst_mcu_sbus_n: 1;    //  11
    UINT32 reg_soft_rst_p_vmcu_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_sys_0_n: 1;    //     13
    UINT32 reg_soft_rst_sys_1_n: 1;    //     14
    UINT32 reg_soft_rst_sys_2_n: 1;    //     15
    UINT32 reg_soft_rst_sys_3_n: 1;    //     16
    UINT32 reg_soft_rst_sys_4_n: 1;    //     17
    UINT32 reg_soft_rst_sys_5_n: 1;    //     18
    UINT32 reg_soft_rst_te_n  :  1;    //     19
    UINT32 reg_soft_rst_x_vmcu_0_axi_n: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}VMCU_SCRG_CTRL_VMCU_CRG_VMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    vmcu_scrg_ctrl_vmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU000_O26A0_T    crg_vmcu000;     // 0xCE3C_0000
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU001_O26A0_T    crg_vmcu001;     // 0xCE3C_0004
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU002_O26A0_T    crg_vmcu002;     // 0xCE3C_0008
    VMCU_SCRG_CTRL_VMCU_CRG_VMCU003_O26A0_T    crg_vmcu003;     // 0xCE3C_000C
}VMCU_SCRG_CTRL_VMCU_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_VMCU_SCRG_CTRL_VMCU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

