#ifndef _SCRG_CTRL_ICOD_REG_O26A0_H_
#define _SCRG_CTRL_ICOD_REG_O26A0_H_

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
    0xCE46_0000    crg_icod000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0004    crg_icod001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0008    crg_icod002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_icod_0__jpeg_clk_gate_en: 1,    //  0
    reg_apb_clk_gate_en       :  1,    //      1
    reg_jpeg_clk_gate_en      :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ICOD_CRG_ICOD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_000C    crg_icod003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_jpeg_n       :  1,    //      1
    reg_soft_rst_p_icod_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_x_icod_0_axi_n: 1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_ICOD_CRG_ICOD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0010    crg_icod004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jpeg_clk_sel          :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_ICOD_CRG_ICOD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD000_O26A0_T    crg_icod000;          // 0xCE46_0000
    SCRG_CTRL_ICOD_CRG_ICOD001_O26A0_T    crg_icod001;          // 0xCE46_0004
    SCRG_CTRL_ICOD_CRG_ICOD002_O26A0_T    crg_icod002;          // 0xCE46_0008
    SCRG_CTRL_ICOD_CRG_ICOD003_O26A0_T    crg_icod003;          // 0xCE46_000C
    SCRG_CTRL_ICOD_CRG_ICOD004_O26A0_T    crg_icod004;          // 0xCE46_0010
}SCRG_CTRL_ICOD_REG_O26A0_T;
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

#define SCRG_CTRL_ICOD_CRG_ICOD000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_ICOD_CRG_ICOD001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_ICOD_CRG_ICOD002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_ICOD_CRG_ICOD003_O26A0_T_OFF              (BASEADDRESS+0x000C)
#define SCRG_CTRL_ICOD_CRG_ICOD004_O26A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE46_0000    crg_icod000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0004    crg_icod001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0008    crg_icod002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_icod_0__jpeg_clk_gate_en: 1;    //  0
    UINT32 reg_apb_clk_gate_en:  1;    //      1
    UINT32 reg_jpeg_clk_gate_en: 1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_000C    crg_icod003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_jpeg_n:  1;    //      1
    UINT32 reg_soft_rst_p_icod_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_icod_0_axi_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE46_0010    crg_icod004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_jpeg_clk_sel   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD000_O26A0_T    crg_icod000;          // 0xCE46_0000
    SCRG_CTRL_ICOD_CRG_ICOD001_O26A0_T    crg_icod001;          // 0xCE46_0004
    SCRG_CTRL_ICOD_CRG_ICOD002_O26A0_T    crg_icod002;          // 0xCE46_0008
    SCRG_CTRL_ICOD_CRG_ICOD003_O26A0_T    crg_icod003;          // 0xCE46_000C
    SCRG_CTRL_ICOD_CRG_ICOD004_O26A0_T    crg_icod004;          // 0xCE46_0010
}SCRG_CTRL_ICOD_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_ICOD_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

