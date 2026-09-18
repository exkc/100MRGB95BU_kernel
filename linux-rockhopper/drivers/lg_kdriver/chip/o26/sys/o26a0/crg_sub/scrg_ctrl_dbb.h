#ifndef _SCRG_CTRL_DBB_REG_O26A0_H_
#define _SCRG_CTRL_DBB_REG_O26A0_H_

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
    0xC8A1_0000    crg_dbb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DBB_CRG_DBB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_0004    crg_dbb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DBB_CRG_DBB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_0008    crg_dbb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_dbb_0__axi_clk_gate_en: 1,    //  0
    reg_apb_clk_gate_en       :  1,    //      1
    reg_axi_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_DBB_CRG_DBB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_000C    crg_dbb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_mcu_n        :  1,    //      2
    reg_soft_rst_p_dbb_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_dbb_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_DBB_CRG_DBB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DBB_CRG_DBB000_O26A0_T    crg_dbb000;             // 0xC8A1_0000
    SCRG_CTRL_DBB_CRG_DBB001_O26A0_T    crg_dbb001;             // 0xC8A1_0004
    SCRG_CTRL_DBB_CRG_DBB002_O26A0_T    crg_dbb002;             // 0xC8A1_0008
    SCRG_CTRL_DBB_CRG_DBB003_O26A0_T    crg_dbb003;             // 0xC8A1_000C
}SCRG_CTRL_DBB_REG_O26A0_T;
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

#define SCRG_CTRL_DBB_CRG_DBB000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_DBB_CRG_DBB001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_DBB_CRG_DBB002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_DBB_CRG_DBB003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC8A1_0000    crg_dbb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DBB_CRG_DBB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_0004    crg_dbb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DBB_CRG_DBB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_0008    crg_dbb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_dbb_0__axi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_clk_gate_en:  1;    //      1
    UINT32 reg_axi_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_DBB_CRG_DBB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A1_000C    crg_dbb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_mcu_n :  1;    //      2
    UINT32 reg_soft_rst_p_dbb_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_dbb_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_DBB_CRG_DBB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dbb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DBB_CRG_DBB000_O26A0_T    crg_dbb000;             // 0xC8A1_0000
    SCRG_CTRL_DBB_CRG_DBB001_O26A0_T    crg_dbb001;             // 0xC8A1_0004
    SCRG_CTRL_DBB_CRG_DBB002_O26A0_T    crg_dbb002;             // 0xC8A1_0008
    SCRG_CTRL_DBB_CRG_DBB003_O26A0_T    crg_dbb003;             // 0xC8A1_000C
}SCRG_CTRL_DBB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_DBB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

