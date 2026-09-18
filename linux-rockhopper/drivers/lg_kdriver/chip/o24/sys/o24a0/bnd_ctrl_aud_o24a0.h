#ifndef _BND_CTRL_AUD_REG_O24A0_H_
#define _BND_CTRL_AUD_REG_O24A0_H_

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
    0xCE49_2000    aud_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpo_outmux_sel        :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AUD_AUD_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_2004    aud_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_audio_dto0_sel        :  1,    //      0
    reg_audio_dto1_sel        :  1,    //      1
    reg_audio_dto2_sel        :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_AUD_AUD_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AUD_AUD_SYN_00_O24A0_T    aud_syn_00 ;             // 0xCE49_2000
    BND_CTRL_AUD_AUD_SYN_01_O24A0_T    aud_syn_01 ;             // 0xCE49_2004
}BND_CTRL_AUD_REG_O24A0_T;
/* 2 regs */

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

#define BND_CTRL_AUD_AUD_SYN_00_O24A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_AUD_AUD_SYN_01_O24A0_T_OFF                 (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCE49_2000    aud_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpo_outmux_sel :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AUD_AUD_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_2004    aud_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_audio_dto0_sel :  1;    //      0
    UINT32 reg_audio_dto1_sel :  1;    //      1
    UINT32 reg_audio_dto2_sel :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_AUD_AUD_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AUD_AUD_SYN_00_O24A0_T    aud_syn_00 ;             // 0xCE49_2000
    BND_CTRL_AUD_AUD_SYN_01_O24A0_T    aud_syn_01 ;             // 0xCE49_2004
}BND_CTRL_AUD_REG_O24A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_AUD_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

