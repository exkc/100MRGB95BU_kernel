#ifndef _BND_CTRL_HDR_REG_O26A0_H_
#define _BND_CTRL_HDR_REG_O26A0_H_

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
    0xCC27_2100    hdr_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdr_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdr_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_HDR_HDR_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2104    hdr_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_HDR_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2108    hdr_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_rom_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_HDR_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_210C    hdr_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_HDR_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2110    hdr_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_HDR_HDR_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2114    vdo_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_vdo_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_vdo_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_HDR_VDO_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2118    vdo_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_VDO_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_211C    vdo_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_HDR_VDO_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2120    vdo_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_VDO_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2124    vdo_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDR_VDO_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC27_2000 ~ 0xCC27_20FC
    BND_CTRL_HDR_HDR_MEM0_O26A0_T      hdr_mem0   ;             // 0xCC27_2100
    BND_CTRL_HDR_HDR_MEM1_O26A0_T      hdr_mem1   ;             // 0xCC27_2104
    BND_CTRL_HDR_HDR_MEM2_O26A0_T      hdr_mem2   ;             // 0xCC27_2108
    BND_CTRL_HDR_HDR_MEM3_O26A0_T      hdr_mem3   ;             // 0xCC27_210C
    BND_CTRL_HDR_HDR_MEM4_O26A0_T      hdr_mem4   ;             // 0xCC27_2110
    BND_CTRL_HDR_VDO_MEM0_O26A0_T      vdo_mem0   ;             // 0xCC27_2114
    BND_CTRL_HDR_VDO_MEM1_O26A0_T      vdo_mem1   ;             // 0xCC27_2118
    BND_CTRL_HDR_VDO_MEM2_O26A0_T      vdo_mem2   ;             // 0xCC27_211C
    BND_CTRL_HDR_VDO_MEM3_O26A0_T      vdo_mem3   ;             // 0xCC27_2120
    BND_CTRL_HDR_VDO_MEM4_O26A0_T      vdo_mem4   ;             // 0xCC27_2124
}BND_CTRL_HDR_REG_O26A0_T;
/* 10 regs */

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

#define BND_CTRL_HDR_HDR_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_HDR_HDR_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_HDR_HDR_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_HDR_HDR_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_HDR_HDR_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x0110)
#define BND_CTRL_HDR_VDO_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0114)
#define BND_CTRL_HDR_VDO_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0118)
#define BND_CTRL_HDR_VDO_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x011C)
#define BND_CTRL_HDR_VDO_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0120)
#define BND_CTRL_HDR_VDO_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x0124)

/*-----------------------------------------------------------------------------------------
    0xCC27_2100    hdr_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdr_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdr_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_HDR_HDR_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2104    hdr_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_HDR_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2108    hdr_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_rom_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_HDR_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_210C    hdr_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_HDR_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2110    hdr_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_HDR_HDR_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2114    vdo_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_vdo_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_vdo_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_HDR_VDO_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2118    vdo_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_VDO_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_211C    vdo_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_HDR_VDO_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2120    vdo_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_VDO_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_2124    vdo_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDR_VDO_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC27_2000 ~ 0xCC27_20FC
    BND_CTRL_HDR_HDR_MEM0_O26A0_T      hdr_mem0   ;             // 0xCC27_2100
    BND_CTRL_HDR_HDR_MEM1_O26A0_T      hdr_mem1   ;             // 0xCC27_2104
    BND_CTRL_HDR_HDR_MEM2_O26A0_T      hdr_mem2   ;             // 0xCC27_2108
    BND_CTRL_HDR_HDR_MEM3_O26A0_T      hdr_mem3   ;             // 0xCC27_210C
    BND_CTRL_HDR_HDR_MEM4_O26A0_T      hdr_mem4   ;             // 0xCC27_2110
    BND_CTRL_HDR_VDO_MEM0_O26A0_T      vdo_mem0   ;             // 0xCC27_2114
    BND_CTRL_HDR_VDO_MEM1_O26A0_T      vdo_mem1   ;             // 0xCC27_2118
    BND_CTRL_HDR_VDO_MEM2_O26A0_T      vdo_mem2   ;             // 0xCC27_211C
    BND_CTRL_HDR_VDO_MEM3_O26A0_T      vdo_mem3   ;             // 0xCC27_2120
    BND_CTRL_HDR_VDO_MEM4_O26A0_T      vdo_mem4   ;             // 0xCC27_2124
}BND_CTRL_HDR_REG_O26A0_T;
/* 10 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_HDR_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

