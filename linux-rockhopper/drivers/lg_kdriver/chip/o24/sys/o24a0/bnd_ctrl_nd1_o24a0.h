#ifndef _BND_CTRL_ND1_REG_O24A0_H_
#define _BND_CTRL_ND1_REG_O24A0_H_

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
    0xCCCB_2000    nd1_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_pdb         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tx_lo_drv_pdb         :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tx_lo_drv_ck_div      :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_ND1_ND1_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ND1_ND1_SYN_00_O24A0_T    nd1_syn_00 ;             // 0xCCCB_2000
}BND_CTRL_ND1_REG_O24A0_T;
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

#define BND_CTRL_ND1_ND1_SYN_00_O24A0_T_OFF                 (BASEADDRESS+0x0000)

/*-----------------------------------------------------------------------------------------
    0xCCCB_2000    nd1_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_pdb  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tx_lo_drv_pdb  :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_tx_lo_drv_ck_div: 1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_ND1_ND1_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ND1_ND1_SYN_00_O24A0_T    nd1_syn_00 ;             // 0xCCCB_2000
}BND_CTRL_ND1_REG_O24A0_T;
/* 1 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_ND1_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

