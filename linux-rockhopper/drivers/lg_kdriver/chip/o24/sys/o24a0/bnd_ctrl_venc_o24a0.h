#ifndef _BND_CTRL_VENC_REG_O24A0_H_
#define _BND_CTRL_VENC_REG_O24A0_H_

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
    0xCE87_1000    rxclkdrv_md_m1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_md_m1_pdb    :  1,    //      0
    reg_rxclkdrv_md_m1_smv    :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_VENC_RXCLKDRV_MD_M1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_VENC_RXCLKDRV_MD_M1_O24A0_T    rxclkdrv_md_m1;     // 0xCE87_1000
}BND_CTRL_VENC_REG_O24A0_T;
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

#define BND_CTRL_VENC_RXCLKDRV_MD_M1_O24A0_T_OFF            (BASEADDRESS+0x0000)

/*-----------------------------------------------------------------------------------------
    0xCE87_1000    rxclkdrv_md_m1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_md_m1_pdb: 1;    //    0
    UINT32 reg_rxclkdrv_md_m1_smv: 1;    //    1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_VENC_RXCLKDRV_MD_M1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_VENC_RXCLKDRV_MD_M1_O24A0_T    rxclkdrv_md_m1;     // 0xCE87_1000
}BND_CTRL_VENC_REG_O24A0_T;
/* 1 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_VENC_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

