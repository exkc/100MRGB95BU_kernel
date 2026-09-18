#ifndef _SCRG_CTRL_EDID_REG_H_
#define _SCRG_CTRL_EDID_REG_H_

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
    0x18_0000    crg_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EDID_CRG_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0004    crg_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EDID_CRG_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0008    crg_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_apb_clk_gate_en: 1,    //    0
    reg_edid_comm_smpl_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_EDID_CRG_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_000C    crg_edid03 ''
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
}SCRG_CTRL_EDID_CRG_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0010    crg_edid04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_smpl_clk_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EDID_CRG_EDID04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0014    crg_edid05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_apb_clk_skip_ctrl: 9,    //  8:0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_EDID_CRG_EDID05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID_CRG_EDID00_O22A0_T        crg_edid00 ;             // 0x18_0000
    SCRG_CTRL_EDID_CRG_EDID01_O22A0_T        crg_edid01 ;             // 0x18_0004
    SCRG_CTRL_EDID_CRG_EDID02_O22A0_T        crg_edid02 ;             // 0x18_0008
    SCRG_CTRL_EDID_CRG_EDID03_O22A0_T        crg_edid03 ;             // 0x18_000C
    SCRG_CTRL_EDID_CRG_EDID04_O22A0_T        crg_edid04 ;             // 0x18_0010
    SCRG_CTRL_EDID_CRG_EDID05_O22A0_T        crg_edid05 ;             // 0x18_0014
}SCRG_CTRL_EDID_REG_O22A0_T;
/* 6 regs */

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

#define SCRG_CTRL_EDID_CRG_EDID00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_EDID_CRG_EDID01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_EDID_CRG_EDID02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_EDID_CRG_EDID03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_EDID_CRG_EDID04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_EDID_CRG_EDID05_O22A0_T_OFF                     (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x18_0000    crg_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EDID_CRG_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0004    crg_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EDID_CRG_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0008    crg_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_apb_clk_gate_en: 1;    //  0
    UINT32 reg_edid_comm_smpl_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_EDID_CRG_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_000C    crg_edid03 ''
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
}SCRG_CTRL_EDID_CRG_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0010    crg_edid04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_smpl_clk_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EDID_CRG_EDID04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x18_0014    crg_edid05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_apb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_EDID_CRG_EDID05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID_CRG_EDID00_O22A0_T        crg_edid00 ;             // 0x18_0000
    SCRG_CTRL_EDID_CRG_EDID01_O22A0_T        crg_edid01 ;             // 0x18_0004
    SCRG_CTRL_EDID_CRG_EDID02_O22A0_T        crg_edid02 ;             // 0x18_0008
    SCRG_CTRL_EDID_CRG_EDID03_O22A0_T        crg_edid03 ;             // 0x18_000C
    SCRG_CTRL_EDID_CRG_EDID04_O22A0_T        crg_edid04 ;             // 0x18_0010
    SCRG_CTRL_EDID_CRG_EDID05_O22A0_T        crg_edid05 ;             // 0x18_0014
}SCRG_CTRL_EDID_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

