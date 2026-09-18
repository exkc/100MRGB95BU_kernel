#ifndef _SCRG_CTRL_NPP_REG_O26A0_H_
#define _SCRG_CTRL_NPP_REG_O26A0_H_

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
    0xCCD3_0000    crg_npp000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_NPP_CRG_NPP000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_0004    crg_npp001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_NPP_CRG_NPP001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_0008    crg_npp002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_npp_0__axi_clk_gate_en: 1,    //  0
    reg_apb_clk_gate_en       :  1,    //      1
    reg_axi_clk_gate_en       :  1,    //      2
    reg_de_clk_gate_en        :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_NPP_CRG_NPP002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_000C    crg_npp003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_p_npp_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_npp_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_NPP_CRG_NPP003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_npp Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_NPP_CRG_NPP000_O26A0_T    crg_npp000;             // 0xCCD3_0000
    SCRG_CTRL_NPP_CRG_NPP001_O26A0_T    crg_npp001;             // 0xCCD3_0004
    SCRG_CTRL_NPP_CRG_NPP002_O26A0_T    crg_npp002;             // 0xCCD3_0008
    SCRG_CTRL_NPP_CRG_NPP003_O26A0_T    crg_npp003;             // 0xCCD3_000C
}SCRG_CTRL_NPP_REG_O26A0_T;
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

#define SCRG_CTRL_NPP_CRG_NPP000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_NPP_CRG_NPP001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_NPP_CRG_NPP002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_NPP_CRG_NPP003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCD3_0000    crg_npp000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_NPP_CRG_NPP000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_0004    crg_npp001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_NPP_CRG_NPP001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_0008    crg_npp002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_npp_0__axi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_clk_gate_en:  1;    //      1
    UINT32 reg_axi_clk_gate_en:  1;    //      2
    UINT32 reg_de_clk_gate_en :  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_NPP_CRG_NPP002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD3_000C    crg_npp003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_p_npp_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_npp_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_NPP_CRG_NPP003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_npp Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_NPP_CRG_NPP000_O26A0_T    crg_npp000;             // 0xCCD3_0000
    SCRG_CTRL_NPP_CRG_NPP001_O26A0_T    crg_npp001;             // 0xCCD3_0004
    SCRG_CTRL_NPP_CRG_NPP002_O26A0_T    crg_npp002;             // 0xCCD3_0008
    SCRG_CTRL_NPP_CRG_NPP003_O26A0_T    crg_npp003;             // 0xCCD3_000C
}SCRG_CTRL_NPP_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_NPP_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

