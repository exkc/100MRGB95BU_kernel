#ifndef _SCRG_CTRL_FMS_M23A0_REG_H_
#define _SCRG_CTRL_FMS_M23A0_REG_H_

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
    0xCC96_0000    crg_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_apb_clk_gate_en   :  1,    //      0
    reg_fms_axi_clk_gate_en   :  1,    //      1
    reg_fms_de_clk_gate_en    :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_FMS_CRG_FMS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_p_fms_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_fms_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_fms_0_axi_n:  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_FMS_CRG_FMS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS00_M23A0_T    crg_fms00  ;             // 0xCC96_0000
    SCRG_CTRL_FMS_CRG_FMS01_M23A0_T    crg_fms01  ;             // 0xCC96_0004
    SCRG_CTRL_FMS_CRG_FMS02_M23A0_T    crg_fms02  ;             // 0xCC96_0008
    SCRG_CTRL_FMS_CRG_FMS03_M23A0_T    crg_fms03  ;             // 0xCC96_000C
}SCRG_CTRL_FMS_REG_M23A0_T;
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

#define SCRG_CTRL_FMS_CRG_FMS00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMS_CRG_FMS01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMS_CRG_FMS02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMS_CRG_FMS03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC96_0000    crg_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_apb_clk_gate_en: 1;    //   0
    UINT32 reg_fms_axi_clk_gate_en: 1;    //   1
    UINT32 reg_fms_de_clk_gate_en: 1;    //    2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_p_fms_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_fms_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_fms_0_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS00_M23A0_T    crg_fms00  ;             // 0xCC96_0000
    SCRG_CTRL_FMS_CRG_FMS01_M23A0_T    crg_fms01  ;             // 0xCC96_0004
    SCRG_CTRL_FMS_CRG_FMS02_M23A0_T    crg_fms02  ;             // 0xCC96_0008
    SCRG_CTRL_FMS_CRG_FMS03_M23A0_T    crg_fms03  ;             // 0xCC96_000C
}SCRG_CTRL_FMS_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

