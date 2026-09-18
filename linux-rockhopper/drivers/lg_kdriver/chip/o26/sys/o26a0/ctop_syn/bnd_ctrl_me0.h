#ifndef _BND_CTRL_ME0_REG_O26A0_H_
#define _BND_CTRL_ME0_REG_O26A0_H_

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
    0xCCCC_2100    me0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_me0_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_me0_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_me0_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_ME0_ME0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2104    me0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_me0_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_ME0_ME0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2108    me0_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_me0_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_ME0_ME0_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_210C    fmesb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmesb_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_fmesb_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_fmesb_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_ME0_FMESB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2110    fmesb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmesb_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_ME0_FMESB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCCCC_2000 ~ 0xCCCC_20FC
    BND_CTRL_ME0_ME0_MEM0_O26A0_T      me0_mem0   ;             // 0xCCCC_2100
    BND_CTRL_ME0_ME0_MEM1_O26A0_T      me0_mem1   ;             // 0xCCCC_2104
    BND_CTRL_ME0_ME0_MEM3_O26A0_T      me0_mem3   ;             // 0xCCCC_2108
    BND_CTRL_ME0_FMESB_MEM0_O26A0_T    fmesb_mem0 ;             // 0xCCCC_210C
    BND_CTRL_ME0_FMESB_MEM1_O26A0_T    fmesb_mem1 ;             // 0xCCCC_2110
}BND_CTRL_ME0_REG_O26A0_T;
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

#define BND_CTRL_ME0_ME0_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_ME0_ME0_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_ME0_ME0_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_ME0_FMESB_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x010C)
#define BND_CTRL_ME0_FMESB_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0110)

/*-----------------------------------------------------------------------------------------
    0xCCCC_2100    me0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_me0_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_me0_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_me0_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_ME0_ME0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2104    me0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_me0_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_ME0_ME0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2108    me0_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_me0_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_ME0_ME0_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_210C    fmesb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmesb_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_fmesb_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_fmesb_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_ME0_FMESB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCC_2110    fmesb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmesb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_ME0_FMESB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCCCC_2000 ~ 0xCCCC_20FC
    BND_CTRL_ME0_ME0_MEM0_O26A0_T      me0_mem0   ;             // 0xCCCC_2100
    BND_CTRL_ME0_ME0_MEM1_O26A0_T      me0_mem1   ;             // 0xCCCC_2104
    BND_CTRL_ME0_ME0_MEM3_O26A0_T      me0_mem3   ;             // 0xCCCC_2108
    BND_CTRL_ME0_FMESB_MEM0_O26A0_T    fmesb_mem0 ;             // 0xCCCC_210C
    BND_CTRL_ME0_FMESB_MEM1_O26A0_T    fmesb_mem1 ;             // 0xCCCC_2110
}BND_CTRL_ME0_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_ME0_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

