#ifndef _SCRG_CTRL_DMCU_REG_O24A0_H_
#define _SCRG_CTRL_DMCU_REG_O24A0_H_

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
    0xC417_0000    crg_dmcu0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DMCU_CRG_DMCU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_0004    crg_dmcu1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DMCU_CRG_DMCU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_0008    crg_dmcu2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_mc_clk_gate_en        :  1,    //      1
    reg_ss_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_DMCU_CRG_DMCU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_000C    crg_dmcu3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_mc_n         :  1,    //      1
    reg_soft_rst_p_cpu_3_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_dmcu_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_ss_n         :  1,    //      4
    reg_soft_rst_x_cpu_3_axi_n:  1,    //      5
    reg_soft_rst_x_dmcu_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_dmcu_0_axi_n: 1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_DMCU_CRG_DMCU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DMCU_CRG_DMCU0_O24A0_T    crg_dmcu0 ;             // 0xC417_0000
    SCRG_CTRL_DMCU_CRG_DMCU1_O24A0_T    crg_dmcu1 ;             // 0xC417_0004
    SCRG_CTRL_DMCU_CRG_DMCU2_O24A0_T    crg_dmcu2 ;             // 0xC417_0008
    SCRG_CTRL_DMCU_CRG_DMCU3_O24A0_T    crg_dmcu3 ;             // 0xC417_000C
}SCRG_CTRL_DMCU_REG_O24A0_T;
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

#define SCRG_CTRL_DMCU_CRG_DMCU0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_DMCU_CRG_DMCU1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_DMCU_CRG_DMCU2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_DMCU_CRG_DMCU3_O24A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC417_0000    crg_dmcu0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DMCU_CRG_DMCU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_0004    crg_dmcu1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DMCU_CRG_DMCU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_0008    crg_dmcu2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_mc_clk_gate_en :  1;    //      1
    UINT32 reg_ss_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_DMCU_CRG_DMCU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC417_000C    crg_dmcu3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_mc_n  :  1;    //      1
    UINT32 reg_soft_rst_p_cpu_3_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_dmcu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_ss_n  :  1;    //      4
    UINT32 reg_soft_rst_x_cpu_3_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_dmcu_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_dmcu_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_DMCU_CRG_DMCU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DMCU_CRG_DMCU0_O24A0_T    crg_dmcu0 ;             // 0xC417_0000
    SCRG_CTRL_DMCU_CRG_DMCU1_O24A0_T    crg_dmcu1 ;             // 0xC417_0004
    SCRG_CTRL_DMCU_CRG_DMCU2_O24A0_T    crg_dmcu2 ;             // 0xC417_0008
    SCRG_CTRL_DMCU_CRG_DMCU3_O24A0_T    crg_dmcu3 ;             // 0xC417_000C
}SCRG_CTRL_DMCU_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DMCU_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

