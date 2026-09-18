#ifndef _SCRG_CTRL_EMUSB_M23A0_REG_H_
#define _SCRG_CTRL_EMUSB_M23A0_REG_H_

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
    0xC458_0000    crg_sb_emu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EMUSB_CRG_SB_EMU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_0004    crg_sb_emu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EMUSB_CRG_SB_EMU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_0008    crg_sb_emu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sb_axi_emu_200_clk_gate_en: 1,    //   0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_EMUSB_CRG_SB_EMU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_000C    crg_sb_emu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_sb_axi_emu_200_bnd_n: 1,    //  0
    reg_soft_rst_sb_axi_emu_200_n: 1,    //    1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_EMUSB_CRG_SB_EMU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_emusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMUSB_CRG_SB_EMU00_M23A0_T    crg_sb_emu00;       // 0xC458_0000
    SCRG_CTRL_EMUSB_CRG_SB_EMU01_M23A0_T    crg_sb_emu01;       // 0xC458_0004
    SCRG_CTRL_EMUSB_CRG_SB_EMU02_M23A0_T    crg_sb_emu02;       // 0xC458_0008
    SCRG_CTRL_EMUSB_CRG_SB_EMU03_M23A0_T    crg_sb_emu03;       // 0xC458_000C
}SCRG_CTRL_EMUSB_REG_M23A0_T;
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

#define SCRG_CTRL_EMUSB_CRG_SB_EMU00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_EMUSB_CRG_SB_EMU01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_EMUSB_CRG_SB_EMU02_M23A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_EMUSB_CRG_SB_EMU03_M23A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC458_0000    crg_sb_emu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EMUSB_CRG_SB_EMU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_0004    crg_sb_emu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EMUSB_CRG_SB_EMU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_0008    crg_sb_emu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sb_axi_emu_200_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_EMUSB_CRG_SB_EMU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC458_000C    crg_sb_emu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_sb_axi_emu_200_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_sb_axi_emu_200_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_EMUSB_CRG_SB_EMU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_emusb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMUSB_CRG_SB_EMU00_M23A0_T    crg_sb_emu00;       // 0xC458_0000
    SCRG_CTRL_EMUSB_CRG_SB_EMU01_M23A0_T    crg_sb_emu01;       // 0xC458_0004
    SCRG_CTRL_EMUSB_CRG_SB_EMU02_M23A0_T    crg_sb_emu02;       // 0xC458_0008
    SCRG_CTRL_EMUSB_CRG_SB_EMU03_M23A0_T    crg_sb_emu03;       // 0xC458_000C
}SCRG_CTRL_EMUSB_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

