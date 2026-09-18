#ifndef _SB_CTRL_LB1SB_REG_O24A0_H_
#define _SB_CTRL_LB1SB_REG_O24A0_H_

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
    0xCC55_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr_awuser           :  4,    //   3: 0
    reg_dnsr_aruser           :  4,    //   7: 4
    reg_dnsr_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dnsr_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_LB1SB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnnr_awuser           :  4,    //   3: 0
    reg_dnnr_aruser           :  4,    //   7: 4
    reg_dnnr_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dnnr_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_LB1SB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_10D8    user_bit_cntl_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pmcu_awuser           :  4,    //   3: 0
    reg_pmcu_aruser           :  4,    //   7: 4
    reg_pmcu_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_pmcu_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_LB1SB_USER_BIT_CNTL_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_lb1sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[52];            // 0xCC55_1000 ~ 0xCC55_10CC
    SB_CTRL_LB1SB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCC55_10D0
    SB_CTRL_LB1SB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCC55_10D4
    SB_CTRL_LB1SB_USER_BIT_CNTL_002_O24A0_T    user_bit_cntl_002;    // 0xCC55_10D8
}SB_CTRL_LB1SB_REG_O24A0_T;
/* 3 regs */

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

#define SB_CTRL_LB1SB_USER_BIT_CNTL_000_O24A0_T_OFF         (BASEADDRESS+0x00D0)
#define SB_CTRL_LB1SB_USER_BIT_CNTL_001_O24A0_T_OFF         (BASEADDRESS+0x00D4)
#define SB_CTRL_LB1SB_USER_BIT_CNTL_002_O24A0_T_OFF         (BASEADDRESS+0x00D8)

/*-----------------------------------------------------------------------------------------
    0xCC55_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr_awuser    :  4;    //   3: 0
    UINT32 reg_dnsr_aruser    :  4;    //   7: 4
    UINT32 reg_dnsr_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_dnsr_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_LB1SB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnnr_awuser    :  4;    //   3: 0
    UINT32 reg_dnnr_aruser    :  4;    //   7: 4
    UINT32 reg_dnnr_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_dnnr_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_LB1SB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC55_10D8    user_bit_cntl_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pmcu_awuser    :  4;    //   3: 0
    UINT32 reg_pmcu_aruser    :  4;    //   7: 4
    UINT32 reg_pmcu_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_pmcu_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_LB1SB_USER_BIT_CNTL_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_lb1sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[52];            // 0xCC55_1000 ~ 0xCC55_10CC
    SB_CTRL_LB1SB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCC55_10D0
    SB_CTRL_LB1SB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCC55_10D4
    SB_CTRL_LB1SB_USER_BIT_CNTL_002_O24A0_T    user_bit_cntl_002;    // 0xCC55_10D8
}SB_CTRL_LB1SB_REG_O24A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SB_CTRL_LB1SB_REG_H_

/* from 'O24_IPW_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

