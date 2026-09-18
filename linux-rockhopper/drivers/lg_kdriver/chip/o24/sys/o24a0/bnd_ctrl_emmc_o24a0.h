#ifndef _BND_CTRL_EMMC_REG_O24A0_H_
#define _BND_CTRL_EMMC_REG_O24A0_H_

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
    0xC425_2000    emmc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_tmclk_en         :  1,    //      0
                              :  7,    //   7: 1 reserved
    reg_emmc_tmclk_div        : 10,    //  17: 8
                              : 14;    //  31:18 reserved
}BND_CTRL_EMMC_EMMC_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EMMC_EMMC_SYN_00_O24A0_T    emmc_syn_00;           // 0xC425_2000
}BND_CTRL_EMMC_REG_O24A0_T;
/* 1 regs */

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

#define BND_CTRL_EMMC_EMMC_SYN_00_O24A0_T_OFF               (BASEADDRESS+0x0000)

/*-----------------------------------------------------------------------------------------
    0xC425_2000    emmc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_tmclk_en  :  1;    //      0
    UINT32 resvd00            :  7;    //   7: 1 reserved
    UINT32 reg_emmc_tmclk_div : 10;    //  17: 8
    UINT32 resvd01            : 14;    //  31:18 reserved
    };
}BND_CTRL_EMMC_EMMC_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EMMC_EMMC_SYN_00_O24A0_T    emmc_syn_00;           // 0xC425_2000
}BND_CTRL_EMMC_REG_O24A0_T;
/* 1 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_EMMC_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

