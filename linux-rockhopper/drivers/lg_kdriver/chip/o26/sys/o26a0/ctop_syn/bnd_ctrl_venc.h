#ifndef _BND_CTRL_VENC_REG_O26A0_H_
#define _BND_CTRL_VENC_REG_O26A0_H_

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
    0xCE47_2100    venc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_venc_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_venc_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_VENC_VENC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2104    venc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc_urf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_VENC_VENC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2108    venc_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_venc_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_VENC_VENC_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_210C    icod_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_icod_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_icod_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_icod_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_VENC_ICOD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2110    icod_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_icod_urf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_VENC_ICOD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2114    icod_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_icod_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_VENC_ICOD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCE47_2000 ~ 0xCE47_20FC
    BND_CTRL_VENC_VENC_MEM0_O26A0_T    venc_mem0  ;             // 0xCE47_2100
    BND_CTRL_VENC_VENC_MEM1_O26A0_T    venc_mem1  ;             // 0xCE47_2104
    BND_CTRL_VENC_VENC_MEM2_O26A0_T    venc_mem2  ;             // 0xCE47_2108
    BND_CTRL_VENC_ICOD_MEM0_O26A0_T    icod_mem0  ;             // 0xCE47_210C
    BND_CTRL_VENC_ICOD_MEM1_O26A0_T    icod_mem1  ;             // 0xCE47_2110
    BND_CTRL_VENC_ICOD_MEM2_O26A0_T    icod_mem2  ;             // 0xCE47_2114
}BND_CTRL_VENC_REG_O26A0_T;
/* 6 regs */

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

#define BND_CTRL_VENC_VENC_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0100)
#define BND_CTRL_VENC_VENC_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0104)
#define BND_CTRL_VENC_VENC_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0108)
#define BND_CTRL_VENC_ICOD_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x010C)
#define BND_CTRL_VENC_ICOD_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0110)
#define BND_CTRL_VENC_ICOD_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xCE47_2100    venc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_venc_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_venc_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_venc_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_VENC_VENC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2104    venc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_venc_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_VENC_VENC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2108    venc_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_venc_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_VENC_VENC_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_210C    icod_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_icod_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_icod_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_icod_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_VENC_ICOD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2110    icod_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_icod_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_VENC_ICOD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE47_2114    icod_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_icod_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_VENC_ICOD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCE47_2000 ~ 0xCE47_20FC
    BND_CTRL_VENC_VENC_MEM0_O26A0_T    venc_mem0  ;             // 0xCE47_2100
    BND_CTRL_VENC_VENC_MEM1_O26A0_T    venc_mem1  ;             // 0xCE47_2104
    BND_CTRL_VENC_VENC_MEM2_O26A0_T    venc_mem2  ;             // 0xCE47_2108
    BND_CTRL_VENC_ICOD_MEM0_O26A0_T    icod_mem0  ;             // 0xCE47_210C
    BND_CTRL_VENC_ICOD_MEM1_O26A0_T    icod_mem1  ;             // 0xCE47_2110
    BND_CTRL_VENC_ICOD_MEM2_O26A0_T    icod_mem2  ;             // 0xCE47_2114
}BND_CTRL_VENC_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_VENC_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

