#ifndef _SCRG_CTRL_VENC_REG_O24A0_H_
#define _SCRG_CTRL_VENC_REG_O24A0_H_

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
    0xCE84_0000    crg_venc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_0004    crg_venc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_0008    crg_venc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_bus_clk_gate_en       :  1,    //      2
    reg_venc_clk_gate_en      :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_VENC_CRG_VENC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_000C    crg_venc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_bus_n        :  1,    //      2
    reg_soft_rst_p_venc_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_venc_n       :  1,    //      4
    reg_soft_rst_x_venc_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_venc_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VENC_CRG_VENC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC0_O24A0_T    crg_venc0 ;             // 0xCE84_0000
    SCRG_CTRL_VENC_CRG_VENC1_O24A0_T    crg_venc1 ;             // 0xCE84_0004
    SCRG_CTRL_VENC_CRG_VENC2_O24A0_T    crg_venc2 ;             // 0xCE84_0008
    SCRG_CTRL_VENC_CRG_VENC3_O24A0_T    crg_venc3 ;             // 0xCE84_000C
}SCRG_CTRL_VENC_REG_O24A0_T;
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

#define SCRG_CTRL_VENC_CRG_VENC0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_VENC_CRG_VENC1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_VENC_CRG_VENC2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_VENC_CRG_VENC3_O24A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE84_0000    crg_venc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_0004    crg_venc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_0008    crg_venc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_bus_clk_gate_en:  1;    //      2
    UINT32 reg_venc_clk_gate_en: 1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE84_000C    crg_venc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_bus_n :  1;    //      2
    UINT32 reg_soft_rst_p_venc_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_venc_n:  1;    //      4
    UINT32 reg_soft_rst_x_venc_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_venc_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC0_O24A0_T    crg_venc0 ;             // 0xCE84_0000
    SCRG_CTRL_VENC_CRG_VENC1_O24A0_T    crg_venc1 ;             // 0xCE84_0004
    SCRG_CTRL_VENC_CRG_VENC2_O24A0_T    crg_venc2 ;             // 0xCE84_0008
    SCRG_CTRL_VENC_CRG_VENC3_O24A0_T    crg_venc3 ;             // 0xCE84_000C
}SCRG_CTRL_VENC_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_VENC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

