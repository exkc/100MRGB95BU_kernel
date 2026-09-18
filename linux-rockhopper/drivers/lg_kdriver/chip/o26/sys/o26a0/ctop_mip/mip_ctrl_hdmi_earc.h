#ifndef _MIP_CTRL_HDMI_EARC_REG_O26A0_H_
#define _MIP_CTRL_HDMI_EARC_REG_O26A0_H_

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
    0xC877_6000    mip_earc_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earctx_apb_i2c_sel    :  1,    //      0
                              : 31;    //   31:1 reserved
}MIP_CTRL_HDMI_EARC_MIP_EARC_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_hdmi_earc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_HDMI_EARC_MIP_EARC_00_O26A0_T    mip_earc_00;      // 0xC877_6000
}MIP_CTRL_HDMI_EARC_REG_O26A0_T;
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

#define MIP_CTRL_HDMI_EARC_MIP_EARC_00_O26A0_T_OFF          (BASEADDRESS+0x0000)

/*-----------------------------------------------------------------------------------------
    0xC877_6000    mip_earc_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earctx_apb_i2c_sel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MIP_CTRL_HDMI_EARC_MIP_EARC_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_hdmi_earc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_HDMI_EARC_MIP_EARC_00_O26A0_T    mip_earc_00;      // 0xC877_6000
}MIP_CTRL_HDMI_EARC_REG_O26A0_T;
/* 1 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_HDMI_EARC_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

