#ifndef _SCRG_CTRL_DBB_M23A0_REG_H_
#define _SCRG_CTRL_DBB_M23A0_REG_H_

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
    0xC611_0000    crg_dbb00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DBB_CRG_DBB00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0004    crg_dbb01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DBB_CRG_DBB01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0008    crg_dbb02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_DBB_CRG_DBB02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_000C    crg_dbb03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_p_dbb_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_dbb_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_dbb_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_DBB_CRG_DBB03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DBB_CRG_DBB00_M23A0_T    crg_dbb00  ;             // 0xC611_0000
    SCRG_CTRL_DBB_CRG_DBB01_M23A0_T    crg_dbb01  ;             // 0xC611_0004
    SCRG_CTRL_DBB_CRG_DBB02_M23A0_T    crg_dbb02  ;             // 0xC611_0008
    SCRG_CTRL_DBB_CRG_DBB03_M23A0_T    crg_dbb03  ;             // 0xC611_000C
}SCRG_CTRL_DBB_REG_M23A0_T;
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

#define SCRG_CTRL_DBB_CRG_DBB00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_DBB_CRG_DBB01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_DBB_CRG_DBB02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_DBB_CRG_DBB03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC611_0000    crg_dbb00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DBB_CRG_DBB00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0004    crg_dbb01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DBB_CRG_DBB01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_0008    crg_dbb02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_DBB_CRG_DBB02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC611_000C    crg_dbb03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_p_dbb_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_dbb_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_dbb_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_DBB_CRG_DBB03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DBB_CRG_DBB00_M23A0_T    crg_dbb00  ;             // 0xC611_0000
    SCRG_CTRL_DBB_CRG_DBB01_M23A0_T    crg_dbb01  ;             // 0xC611_0004
    SCRG_CTRL_DBB_CRG_DBB02_M23A0_T    crg_dbb02  ;             // 0xC611_0008
    SCRG_CTRL_DBB_CRG_DBB03_M23A0_T    crg_dbb03  ;             // 0xC611_000C
}SCRG_CTRL_DBB_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

