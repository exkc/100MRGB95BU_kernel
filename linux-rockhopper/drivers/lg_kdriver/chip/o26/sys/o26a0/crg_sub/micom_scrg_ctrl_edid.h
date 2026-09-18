#ifndef _MICOM_SCRG_CTRL_EDID_REG_O26A0_H_
#define _MICOM_SCRG_CTRL_EDID_REG_O26A0_H_

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
    0xF336_0000    crg_edid000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_SCRG_CTRL_EDID_CRG_EDID000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0004    crg_edid001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_SCRG_CTRL_EDID_CRG_EDID001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0008    crg_edid002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_apb_clk_gate_en: 1,    //    0
    reg_edid_comm_smpl_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}MICOM_SCRG_CTRL_EDID_CRG_EDID002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_000C    crg_edid003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_edid_comm_apb_n: 1,    //     0
    reg_soft_rst_edid_prt1_apb_n: 1,    //     1
    reg_soft_rst_edid_prt1_smpl_n: 1,    //    2
    reg_soft_rst_edid_prt2_apb_n: 1,    //     3
    reg_soft_rst_edid_prt2_smpl_n: 1,    //    4
    reg_soft_rst_edid_prt3_apb_n: 1,    //     5
    reg_soft_rst_edid_prt3_smpl_n: 1,    //    6
    reg_soft_rst_edid_prt4_apb_n: 1,    //     7
    reg_soft_rst_edid_prt4_smpl_n: 1,    //    8
                              : 23;    //   31:9 reserved
}MICOM_SCRG_CTRL_EDID_CRG_EDID003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0010    crg_edid004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_smpl_clk_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_SCRG_CTRL_EDID_CRG_EDID004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_EDID_CRG_EDID000_O26A0_T    crg_edid000;    // 0xF336_0000
    MICOM_SCRG_CTRL_EDID_CRG_EDID001_O26A0_T    crg_edid001;    // 0xF336_0004
    MICOM_SCRG_CTRL_EDID_CRG_EDID002_O26A0_T    crg_edid002;    // 0xF336_0008
    MICOM_SCRG_CTRL_EDID_CRG_EDID003_O26A0_T    crg_edid003;    // 0xF336_000C
    MICOM_SCRG_CTRL_EDID_CRG_EDID004_O26A0_T    crg_edid004;    // 0xF336_0010
}MICOM_SCRG_CTRL_EDID_REG_O26A0_T;
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

#define MICOM_SCRG_CTRL_EDID_CRG_EDID000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define MICOM_SCRG_CTRL_EDID_CRG_EDID001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define MICOM_SCRG_CTRL_EDID_CRG_EDID002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define MICOM_SCRG_CTRL_EDID_CRG_EDID003_O26A0_T_OFF        (BASEADDRESS+0x000C)
#define MICOM_SCRG_CTRL_EDID_CRG_EDID004_O26A0_T_OFF        (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xF336_0000    crg_edid000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_EDID_CRG_EDID000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0004    crg_edid001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_EDID_CRG_EDID001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0008    crg_edid002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_apb_clk_gate_en: 1;    //  0
    UINT32 reg_edid_comm_smpl_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_SCRG_CTRL_EDID_CRG_EDID002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_000C    crg_edid003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_edid_comm_apb_n: 1;    //  0
    UINT32 reg_soft_rst_edid_prt1_apb_n: 1;    //  1
    UINT32 reg_soft_rst_edid_prt1_smpl_n: 1;    //  2
    UINT32 reg_soft_rst_edid_prt2_apb_n: 1;    //  3
    UINT32 reg_soft_rst_edid_prt2_smpl_n: 1;    //  4
    UINT32 reg_soft_rst_edid_prt3_apb_n: 1;    //  5
    UINT32 reg_soft_rst_edid_prt3_smpl_n: 1;    //  6
    UINT32 reg_soft_rst_edid_prt4_apb_n: 1;    //  7
    UINT32 reg_soft_rst_edid_prt4_smpl_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}MICOM_SCRG_CTRL_EDID_CRG_EDID003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_0010    crg_edid004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_smpl_clk_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_SCRG_CTRL_EDID_CRG_EDID004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_EDID_CRG_EDID000_O26A0_T    crg_edid000;    // 0xF336_0000
    MICOM_SCRG_CTRL_EDID_CRG_EDID001_O26A0_T    crg_edid001;    // 0xF336_0004
    MICOM_SCRG_CTRL_EDID_CRG_EDID002_O26A0_T    crg_edid002;    // 0xF336_0008
    MICOM_SCRG_CTRL_EDID_CRG_EDID003_O26A0_T    crg_edid003;    // 0xF336_000C
    MICOM_SCRG_CTRL_EDID_CRG_EDID004_O26A0_T    crg_edid004;    // 0xF336_0010
}MICOM_SCRG_CTRL_EDID_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_SCRG_CTRL_EDID_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

