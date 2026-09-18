#ifndef _SCRG_CTRL_EDID1_M23A0_REG_H_
#define _SCRG_CTRL_EDID1_M23A0_REG_H_

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
    0xF311_0000    crg_edid100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EDID1_CRG_EDID100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0004    crg_edid101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EDID1_CRG_EDID101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0008    crg_edid102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_apb_clk_gate_en: 1,    //    0
    reg_edid_comm_smpl_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_EDID1_CRG_EDID102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_000C    crg_edid103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_edid_comm_apb_n: 1,    //     0
    reg_soft_rst_edid_prt1_apb_n: 1,    //     1
    reg_soft_rst_edid_prt1_smpl_n: 1,    //    2
    reg_soft_rst_edid_prt2_apb_n: 1,    //     3
    reg_soft_rst_edid_prt2_smpl_n: 1,    //    4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_EDID1_CRG_EDID103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0010    crg_edid104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_comm_smpl_clk_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EDID1_CRG_EDID104_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edid1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID1_CRG_EDID100_M23A0_T    crg_edid100;         // 0xF311_0000
    SCRG_CTRL_EDID1_CRG_EDID101_M23A0_T    crg_edid101;         // 0xF311_0004
    SCRG_CTRL_EDID1_CRG_EDID102_M23A0_T    crg_edid102;         // 0xF311_0008
    SCRG_CTRL_EDID1_CRG_EDID103_M23A0_T    crg_edid103;         // 0xF311_000C
    SCRG_CTRL_EDID1_CRG_EDID104_M23A0_T    crg_edid104;         // 0xF311_0010
}SCRG_CTRL_EDID1_REG_M23A0_T;
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

#define SCRG_CTRL_EDID1_CRG_EDID100_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_EDID1_CRG_EDID101_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_EDID1_CRG_EDID102_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_EDID1_CRG_EDID103_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define SCRG_CTRL_EDID1_CRG_EDID104_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xF311_0000    crg_edid100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EDID1_CRG_EDID100_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0004    crg_edid101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EDID1_CRG_EDID101_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0008    crg_edid102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_apb_clk_gate_en: 1;    //  0
    UINT32 reg_edid_comm_smpl_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_EDID1_CRG_EDID102_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_000C    crg_edid103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_edid_comm_apb_n: 1;    //  0
    UINT32 reg_soft_rst_edid_prt1_apb_n: 1;    //  1
    UINT32 reg_soft_rst_edid_prt1_smpl_n: 1;    //  2
    UINT32 reg_soft_rst_edid_prt2_apb_n: 1;    //  3
    UINT32 reg_soft_rst_edid_prt2_smpl_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_EDID1_CRG_EDID103_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF311_0010    crg_edid104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_comm_smpl_clk_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EDID1_CRG_EDID104_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edid1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDID1_CRG_EDID100_M23A0_T    crg_edid100;         // 0xF311_0000
    SCRG_CTRL_EDID1_CRG_EDID101_M23A0_T    crg_edid101;         // 0xF311_0004
    SCRG_CTRL_EDID1_CRG_EDID102_M23A0_T    crg_edid102;         // 0xF311_0008
    SCRG_CTRL_EDID1_CRG_EDID103_M23A0_T    crg_edid103;         // 0xF311_000C
    SCRG_CTRL_EDID1_CRG_EDID104_M23A0_T    crg_edid104;         // 0xF311_0010
}SCRG_CTRL_EDID1_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

