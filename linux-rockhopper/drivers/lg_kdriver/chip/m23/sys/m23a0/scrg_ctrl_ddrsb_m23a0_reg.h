#ifndef _SCRG_CTRL_DDRSB_M23A0_REG_H_
#define _SCRG_CTRL_DDRSB_M23A0_REG_H_

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
    0xC455_0000    crg_sb_ddr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DDRSB_CRG_SB_DDR00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_0004    crg_sb_ddr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DDRSB_CRG_SB_DDR01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_0008    crg_sb_ddr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sb_axi_ddr_clk_gate_en:  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_DDRSB_CRG_SB_DDR02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_000C    crg_sb_ddr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_sb_axi_ddr_bnd_n: 1,    //    0
    reg_soft_rst_sb_axi_ddr_n :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_DDRSB_CRG_SB_DDR03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddrsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDRSB_CRG_SB_DDR00_M23A0_T    crg_sb_ddr00;       // 0xC455_0000
    SCRG_CTRL_DDRSB_CRG_SB_DDR01_M23A0_T    crg_sb_ddr01;       // 0xC455_0004
    SCRG_CTRL_DDRSB_CRG_SB_DDR02_M23A0_T    crg_sb_ddr02;       // 0xC455_0008
    SCRG_CTRL_DDRSB_CRG_SB_DDR03_M23A0_T    crg_sb_ddr03;       // 0xC455_000C
}SCRG_CTRL_DDRSB_REG_M23A0_T;
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

#define SCRG_CTRL_DDRSB_CRG_SB_DDR00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_DDRSB_CRG_SB_DDR01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_DDRSB_CRG_SB_DDR02_M23A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_DDRSB_CRG_SB_DDR03_M23A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC455_0000    crg_sb_ddr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DDRSB_CRG_SB_DDR00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_0004    crg_sb_ddr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DDRSB_CRG_SB_DDR01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_0008    crg_sb_ddr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sb_axi_ddr_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_DDRSB_CRG_SB_DDR02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC455_000C    crg_sb_ddr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_sb_axi_ddr_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_sb_axi_ddr_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_DDRSB_CRG_SB_DDR03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ddrsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DDRSB_CRG_SB_DDR00_M23A0_T    crg_sb_ddr00;       // 0xC455_0000
    SCRG_CTRL_DDRSB_CRG_SB_DDR01_M23A0_T    crg_sb_ddr01;       // 0xC455_0004
    SCRG_CTRL_DDRSB_CRG_SB_DDR02_M23A0_T    crg_sb_ddr02;       // 0xC455_0008
    SCRG_CTRL_DDRSB_CRG_SB_DDR03_M23A0_T    crg_sb_ddr03;       // 0xC455_000C
}SCRG_CTRL_DDRSB_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

