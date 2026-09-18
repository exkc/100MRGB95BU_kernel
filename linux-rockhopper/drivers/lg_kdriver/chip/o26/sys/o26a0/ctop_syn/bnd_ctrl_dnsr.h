#ifndef _BND_CTRL_DNSR_REG_O26A0_H_
#define _BND_CTRL_DNSR_REG_O26A0_H_

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
    0xCC4C_2100    dnsr0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr0_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dnsr0_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dnsr0_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DNSR_DNSR0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2104    dnsr0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr0_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_DNSR_DNSR0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2108    dnsr0_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr0_srf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_DNSR_DNSR0_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_210C    dnsr1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr1_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dnsr1_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dnsr1_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DNSR_DNSR1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2110    dnsr1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr1_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_DNSR_DNSR1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2114    dnsr1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr1_srf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_DNSR_DNSR1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2118    lb0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lb0_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_lb0_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_lb0_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DNSR_LB0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_211C    lb0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lb0_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DNSR_LB0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC4C_2000 ~ 0xCC4C_20FC
    BND_CTRL_DNSR_DNSR0_MEM0_O26A0_T    dnsr0_mem0;             // 0xCC4C_2100
    BND_CTRL_DNSR_DNSR0_MEM1_O26A0_T    dnsr0_mem1;             // 0xCC4C_2104
    BND_CTRL_DNSR_DNSR0_MEM2_O26A0_T    dnsr0_mem2;             // 0xCC4C_2108
    BND_CTRL_DNSR_DNSR1_MEM0_O26A0_T    dnsr1_mem0;             // 0xCC4C_210C
    BND_CTRL_DNSR_DNSR1_MEM1_O26A0_T    dnsr1_mem1;             // 0xCC4C_2110
    BND_CTRL_DNSR_DNSR1_MEM2_O26A0_T    dnsr1_mem2;             // 0xCC4C_2114
    BND_CTRL_DNSR_LB0_MEM0_O26A0_T     lb0_mem0   ;             // 0xCC4C_2118
    BND_CTRL_DNSR_LB0_MEM1_O26A0_T     lb0_mem1   ;             // 0xCC4C_211C
}BND_CTRL_DNSR_REG_O26A0_T;
/* 8 regs */

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

#define BND_CTRL_DNSR_DNSR0_MEM0_O26A0_T_OFF                (BASEADDRESS+0x0100)
#define BND_CTRL_DNSR_DNSR0_MEM1_O26A0_T_OFF                (BASEADDRESS+0x0104)
#define BND_CTRL_DNSR_DNSR0_MEM2_O26A0_T_OFF                (BASEADDRESS+0x0108)
#define BND_CTRL_DNSR_DNSR1_MEM0_O26A0_T_OFF                (BASEADDRESS+0x010C)
#define BND_CTRL_DNSR_DNSR1_MEM1_O26A0_T_OFF                (BASEADDRESS+0x0110)
#define BND_CTRL_DNSR_DNSR1_MEM2_O26A0_T_OFF                (BASEADDRESS+0x0114)
#define BND_CTRL_DNSR_LB0_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0118)
#define BND_CTRL_DNSR_LB0_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x011C)

/*-----------------------------------------------------------------------------------------
    0xCC4C_2100    dnsr0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr0_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dnsr0_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dnsr0_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DNSR_DNSR0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2104    dnsr0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr0_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DNSR_DNSR0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2108    dnsr0_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr0_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DNSR_DNSR0_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_210C    dnsr1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr1_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dnsr1_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dnsr1_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DNSR_DNSR1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2110    dnsr1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr1_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DNSR_DNSR1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2114    dnsr1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr1_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DNSR_DNSR1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_2118    lb0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lb0_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_lb0_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_lb0_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DNSR_LB0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_211C    lb0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lb0_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DNSR_LB0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC4C_2000 ~ 0xCC4C_20FC
    BND_CTRL_DNSR_DNSR0_MEM0_O26A0_T    dnsr0_mem0;             // 0xCC4C_2100
    BND_CTRL_DNSR_DNSR0_MEM1_O26A0_T    dnsr0_mem1;             // 0xCC4C_2104
    BND_CTRL_DNSR_DNSR0_MEM2_O26A0_T    dnsr0_mem2;             // 0xCC4C_2108
    BND_CTRL_DNSR_DNSR1_MEM0_O26A0_T    dnsr1_mem0;             // 0xCC4C_210C
    BND_CTRL_DNSR_DNSR1_MEM1_O26A0_T    dnsr1_mem1;             // 0xCC4C_2110
    BND_CTRL_DNSR_DNSR1_MEM2_O26A0_T    dnsr1_mem2;             // 0xCC4C_2114
    BND_CTRL_DNSR_LB0_MEM0_O26A0_T     lb0_mem0   ;             // 0xCC4C_2118
    BND_CTRL_DNSR_LB0_MEM1_O26A0_T     lb0_mem1   ;             // 0xCC4C_211C
}BND_CTRL_DNSR_REG_O26A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_DNSR_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

