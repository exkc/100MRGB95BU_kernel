#ifndef _BND_CTRL_LNX1_REG_O26A0_H_
#define _BND_CTRL_LNX1_REG_O26A0_H_

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
    0xCC5C_2100    lnx1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx1_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_lnx1_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_lnx1_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LNX1_LNX1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_2104    lnx1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx1_sra_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_LNX1_LNX1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_2108    lnx1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx1_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_LNX1_LNX1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC5C_2000 ~ 0xCC5C_20FC
    BND_CTRL_LNX1_LNX1_MEM0_O26A0_T    lnx1_mem0  ;             // 0xCC5C_2100
    BND_CTRL_LNX1_LNX1_MEM1_O26A0_T    lnx1_mem1  ;             // 0xCC5C_2104
    BND_CTRL_LNX1_LNX1_MEM2_O26A0_T    lnx1_mem2  ;             // 0xCC5C_2108
}BND_CTRL_LNX1_REG_O26A0_T;
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

#define BND_CTRL_LNX1_LNX1_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0100)
#define BND_CTRL_LNX1_LNX1_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0104)
#define BND_CTRL_LNX1_LNX1_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0108)

/*-----------------------------------------------------------------------------------------
    0xCC5C_2100    lnx1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx1_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_lnx1_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_lnx1_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LNX1_LNX1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_2104    lnx1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx1_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LNX1_LNX1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5C_2108    lnx1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx1_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LNX1_LNX1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC5C_2000 ~ 0xCC5C_20FC
    BND_CTRL_LNX1_LNX1_MEM0_O26A0_T    lnx1_mem0  ;             // 0xCC5C_2100
    BND_CTRL_LNX1_LNX1_MEM1_O26A0_T    lnx1_mem1  ;             // 0xCC5C_2104
    BND_CTRL_LNX1_LNX1_MEM2_O26A0_T    lnx1_mem2  ;             // 0xCC5C_2108
}BND_CTRL_LNX1_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_LNX1_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

