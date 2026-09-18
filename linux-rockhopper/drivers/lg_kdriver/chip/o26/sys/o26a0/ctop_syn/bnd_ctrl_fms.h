#ifndef _BND_CTRL_FMS_REG_O26A0_H_
#define _BND_CTRL_FMS_REG_O26A0_H_

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
    0xCC32_2000    fms_syn_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_tp          :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_FMS_FMS_SYN_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2100    fms_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_fms_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_fms_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_FMS_FMS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2104    fms_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_FMS_FMS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2108    fms_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_FMS_FMS_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_210C    fms_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_FMS_FMS_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_FMS_FMS_SYN_000_O26A0_T    fms_syn_000;            // 0xCC32_2000
    UINT32                             _rsvd_00[63];            // 0xCC32_2004 ~ 0xCC32_20FC
    BND_CTRL_FMS_FMS_MEM0_O26A0_T      fms_mem0   ;             // 0xCC32_2100
    BND_CTRL_FMS_FMS_MEM1_O26A0_T      fms_mem1   ;             // 0xCC32_2104
    BND_CTRL_FMS_FMS_MEM2_O26A0_T      fms_mem2   ;             // 0xCC32_2108
    BND_CTRL_FMS_FMS_MEM3_O26A0_T      fms_mem3   ;             // 0xCC32_210C
}BND_CTRL_FMS_REG_O26A0_T;
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

#define BND_CTRL_FMS_FMS_SYN_000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_FMS_FMS_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_FMS_FMS_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_FMS_FMS_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_FMS_FMS_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)

/*-----------------------------------------------------------------------------------------
    0xCC32_2000    fms_syn_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_tp   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_FMS_FMS_SYN_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2100    fms_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_fms_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_fms_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_FMS_FMS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2104    fms_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_FMS_FMS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_2108    fms_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_FMS_FMS_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_210C    fms_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_FMS_FMS_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_FMS_FMS_SYN_000_O26A0_T    fms_syn_000;            // 0xCC32_2000
    UINT32                             _rsvd_00[63];            // 0xCC32_2004 ~ 0xCC32_20FC
    BND_CTRL_FMS_FMS_MEM0_O26A0_T      fms_mem0   ;             // 0xCC32_2100
    BND_CTRL_FMS_FMS_MEM1_O26A0_T      fms_mem1   ;             // 0xCC32_2104
    BND_CTRL_FMS_FMS_MEM2_O26A0_T      fms_mem2   ;             // 0xCC32_2108
    BND_CTRL_FMS_FMS_MEM3_O26A0_T      fms_mem3   ;             // 0xCC32_210C
}BND_CTRL_FMS_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_FMS_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

