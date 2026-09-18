#ifndef _BND_CTRL_EMMC_REG_O26A0_H_
#define _BND_CTRL_EMMC_REG_O26A0_H_

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
    0xC622_2000    emmc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_tmclk_en         :  1,    //      0
                              :  7,    //   7: 1 reserved
    reg_emmc_tmclk_div        : 10,    //  17: 8
                              : 14;    //  31:18 reserved
}BND_CTRL_EMMC_EMMC_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC622_2100    emmc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_emmc_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_emmc_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_EMMC_EMMC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC622_2104    emmc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_EMMC_EMMC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EMMC_EMMC_SYN_00_O26A0_T    emmc_syn_00;           // 0xC622_2000
    UINT32                             _rsvd_00[63];            // 0xC622_2004 ~ 0xC622_20FC
    BND_CTRL_EMMC_EMMC_MEM0_O26A0_T    emmc_mem0  ;             // 0xC622_2100
    BND_CTRL_EMMC_EMMC_MEM1_O26A0_T    emmc_mem1  ;             // 0xC622_2104
}BND_CTRL_EMMC_REG_O26A0_T;
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

#define BND_CTRL_EMMC_EMMC_SYN_00_O26A0_T_OFF               (BASEADDRESS+0x0000)
#define BND_CTRL_EMMC_EMMC_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0100)
#define BND_CTRL_EMMC_EMMC_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xC622_2000    emmc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_tmclk_en  :  1;    //      0
    UINT32 resvd00            :  7;    //   7: 1 reserved
    UINT32 reg_emmc_tmclk_div : 10;    //  17: 8
    UINT32 resvd01            : 14;    //  31:18 reserved
    };
}BND_CTRL_EMMC_EMMC_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC622_2100    emmc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_emmc_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_emmc_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_EMMC_EMMC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC622_2104    emmc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_EMMC_EMMC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EMMC_EMMC_SYN_00_O26A0_T    emmc_syn_00;           // 0xC622_2000
    UINT32                             _rsvd_00[63];            // 0xC622_2004 ~ 0xC622_20FC
    BND_CTRL_EMMC_EMMC_MEM0_O26A0_T    emmc_mem0  ;             // 0xC622_2100
    BND_CTRL_EMMC_EMMC_MEM1_O26A0_T    emmc_mem1  ;             // 0xC622_2104
}BND_CTRL_EMMC_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_EMMC_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

