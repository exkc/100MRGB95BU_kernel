#ifndef _SCRG_CTRL_EDID_REG_O24A0_H_
#define _SCRG_CTRL_EDID_REG_O24A0_H_

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
    0xC883_0000    crg_edid0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EDID_CRG_EDID0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0004    crg_edid1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EDID_CRG_EDID1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0008    crg_edid2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_apb_clk_gate_en: 1,    //    0
    reg_edid_comm_smpl_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_EDID_CRG_EDID2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_000C    crg_edid3 ''
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
}SCRG_CTRL_EDID_CRG_EDID3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0010    crg_edid4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_smpl_clk_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EDID_CRG_EDID4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID_CRG_EDID0_O24A0_T    crg_edid0 ;             // 0xC883_0000
    SCRG_CTRL_EDID_CRG_EDID1_O24A0_T    crg_edid1 ;             // 0xC883_0004
    SCRG_CTRL_EDID_CRG_EDID2_O24A0_T    crg_edid2 ;             // 0xC883_0008
    SCRG_CTRL_EDID_CRG_EDID3_O24A0_T    crg_edid3 ;             // 0xC883_000C
    SCRG_CTRL_EDID_CRG_EDID4_O24A0_T    crg_edid4 ;             // 0xC883_0010
}SCRG_CTRL_EDID_REG_O24A0_T;
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

#define SCRG_CTRL_EDID_CRG_EDID0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_EDID_CRG_EDID1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_EDID_CRG_EDID2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_EDID_CRG_EDID3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_EDID_CRG_EDID4_O24A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xC883_0000    crg_edid0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EDID_CRG_EDID0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0004    crg_edid1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EDID_CRG_EDID1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0008    crg_edid2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_apb_clk_gate_en: 1;    //  0
    UINT32 reg_edid_comm_smpl_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_EDID_CRG_EDID2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_000C    crg_edid3 ''
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
}SCRG_CTRL_EDID_CRG_EDID3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC883_0010    crg_edid4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_smpl_clk_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EDID_CRG_EDID4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID_CRG_EDID0_O24A0_T    crg_edid0 ;             // 0xC883_0000
    SCRG_CTRL_EDID_CRG_EDID1_O24A0_T    crg_edid1 ;             // 0xC883_0004
    SCRG_CTRL_EDID_CRG_EDID2_O24A0_T    crg_edid2 ;             // 0xC883_0008
    SCRG_CTRL_EDID_CRG_EDID3_O24A0_T    crg_edid3 ;             // 0xC883_000C
    SCRG_CTRL_EDID_CRG_EDID4_O24A0_T    crg_edid4 ;             // 0xC883_0010
}SCRG_CTRL_EDID_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_EDID_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

