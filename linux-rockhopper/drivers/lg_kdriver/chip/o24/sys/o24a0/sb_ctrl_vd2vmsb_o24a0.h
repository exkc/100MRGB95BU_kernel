#ifndef _SB_CTRL_VD2VMSB_REG_O24A0_H_
#define _SB_CTRL_VD2VMSB_REG_O24A0_H_

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
    0xCECE_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd2a_awuser           :  4,    //   3: 0
    reg_vd2a_aruser           :  4,    //   7: 4
    reg_vd2a_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_vd2a_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_VD2VMSB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECE_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vmcu_awuser           :  4,    //   3: 0
    reg_vmcu_aruser           :  4,    //   7: 4
    reg_vmcu_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_vmcu_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_VD2VMSB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_vd2vmsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[52];            // 0xCECE_1000 ~ 0xCECE_10CC
    SB_CTRL_VD2VMSB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCECE_10D0
    SB_CTRL_VD2VMSB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCECE_10D4
}SB_CTRL_VD2VMSB_REG_O24A0_T;
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

#define SB_CTRL_VD2VMSB_USER_BIT_CNTL_000_O24A0_T_OFF       (BASEADDRESS+0x00D0)
#define SB_CTRL_VD2VMSB_USER_BIT_CNTL_001_O24A0_T_OFF       (BASEADDRESS+0x00D4)

/*-----------------------------------------------------------------------------------------
    0xCECE_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd2a_awuser    :  4;    //   3: 0
    UINT32 reg_vd2a_aruser    :  4;    //   7: 4
    UINT32 reg_vd2a_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_vd2a_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_VD2VMSB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECE_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vmcu_awuser    :  4;    //   3: 0
    UINT32 reg_vmcu_aruser    :  4;    //   7: 4
    UINT32 reg_vmcu_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_vmcu_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_VD2VMSB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_vd2vmsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[52];            // 0xCECE_1000 ~ 0xCECE_10CC
    SB_CTRL_VD2VMSB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCECE_10D0
    SB_CTRL_VD2VMSB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCECE_10D4
}SB_CTRL_VD2VMSB_REG_O24A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SB_CTRL_VD2VMSB_REG_H_

/* from 'O24_IPW_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

