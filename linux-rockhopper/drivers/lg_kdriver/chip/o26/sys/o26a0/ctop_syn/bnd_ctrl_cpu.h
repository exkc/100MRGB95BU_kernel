#ifndef _BND_CTRL_CPU_REG_O26A0_H_
#define _BND_CTRL_CPU_REG_O26A0_H_

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
    0xCE5A_2000    rxclkdrv_md_m1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_md_m1_pdb    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_md_m1_div2_enb: 1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_CPU_RXCLKDRV_MD_M1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2100    vd1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_vd1_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_vd1_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_CPU_VD1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2104    vd1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_CPU_VD1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2108    vd1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_CPU_VD1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_210C    vd1_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_CPU_VD1_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2110    tivsb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tivsb_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tivsb_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tivsb_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_CPU_TIVSB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2114    tivsb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tivsb_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_CPU_TIVSB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CPU_RXCLKDRV_MD_M1_O26A0_T    rxclkdrv_md_m1;      // 0xCE5A_2000
    UINT32                             _rsvd_00[63];            // 0xCE5A_2004 ~ 0xCE5A_20FC
    BND_CTRL_CPU_VD1_MEM0_O26A0_T      vd1_mem0   ;             // 0xCE5A_2100
    BND_CTRL_CPU_VD1_MEM1_O26A0_T      vd1_mem1   ;             // 0xCE5A_2104
    BND_CTRL_CPU_VD1_MEM2_O26A0_T      vd1_mem2   ;             // 0xCE5A_2108
    BND_CTRL_CPU_VD1_MEM3_O26A0_T      vd1_mem3   ;             // 0xCE5A_210C
    BND_CTRL_CPU_TIVSB_MEM0_O26A0_T    tivsb_mem0 ;             // 0xCE5A_2110
    BND_CTRL_CPU_TIVSB_MEM1_O26A0_T    tivsb_mem1 ;             // 0xCE5A_2114
}BND_CTRL_CPU_REG_O26A0_T;
/* 7 regs */

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

#define BND_CTRL_CPU_RXCLKDRV_MD_M1_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define BND_CTRL_CPU_VD1_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_CPU_VD1_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_CPU_VD1_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_CPU_VD1_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_CPU_TIVSB_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0110)
#define BND_CTRL_CPU_TIVSB_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0114)

/*-----------------------------------------------------------------------------------------
    0xCE5A_2000    rxclkdrv_md_m1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_md_m1_pdb: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_md_m1_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_CPU_RXCLKDRV_MD_M1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2100    vd1_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_vd1_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_vd1_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_CPU_VD1_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2104    vd1_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_CPU_VD1_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2108    vd1_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_CPU_VD1_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_210C    vd1_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_CPU_VD1_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2110    tivsb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tivsb_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tivsb_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_tivsb_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_CPU_TIVSB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_2114    tivsb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tivsb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_CPU_TIVSB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CPU_RXCLKDRV_MD_M1_O26A0_T    rxclkdrv_md_m1;      // 0xCE5A_2000
    UINT32                             _rsvd_00[63];            // 0xCE5A_2004 ~ 0xCE5A_20FC
    BND_CTRL_CPU_VD1_MEM0_O26A0_T      vd1_mem0   ;             // 0xCE5A_2100
    BND_CTRL_CPU_VD1_MEM1_O26A0_T      vd1_mem1   ;             // 0xCE5A_2104
    BND_CTRL_CPU_VD1_MEM2_O26A0_T      vd1_mem2   ;             // 0xCE5A_2108
    BND_CTRL_CPU_VD1_MEM3_O26A0_T      vd1_mem3   ;             // 0xCE5A_210C
    BND_CTRL_CPU_TIVSB_MEM0_O26A0_T    tivsb_mem0 ;             // 0xCE5A_2110
    BND_CTRL_CPU_TIVSB_MEM1_O26A0_T    tivsb_mem1 ;             // 0xCE5A_2114
}BND_CTRL_CPU_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_CPU_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

