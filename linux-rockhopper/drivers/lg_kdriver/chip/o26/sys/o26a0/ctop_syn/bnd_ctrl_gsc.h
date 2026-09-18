#ifndef _BND_CTRL_GSC_REG_O26A0_H_
#define _BND_CTRL_GSC_REG_O26A0_H_

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
    0xCCC9_2000    rxclkdrv_m0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_m0_pdb       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_m0_div2_enb  :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_GSC_RXCLKDRV_M0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2100    gsc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_gsc_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_gsc_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_GSC_GSC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2104    gsc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_GSC_GSC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2108    gsc_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_GSC_GSC_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_210C    gsc_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_GSC_GSC_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_GSC_RXCLKDRV_M0_O26A0_T    rxclkdrv_m0;            // 0xCCC9_2000
    UINT32                             _rsvd_00[63];            // 0xCCC9_2004 ~ 0xCCC9_20FC
    BND_CTRL_GSC_GSC_MEM0_O26A0_T      gsc_mem0   ;             // 0xCCC9_2100
    BND_CTRL_GSC_GSC_MEM1_O26A0_T      gsc_mem1   ;             // 0xCCC9_2104
    BND_CTRL_GSC_GSC_MEM3_O26A0_T      gsc_mem3   ;             // 0xCCC9_2108
    BND_CTRL_GSC_GSC_MEM4_O26A0_T      gsc_mem4   ;             // 0xCCC9_210C
}BND_CTRL_GSC_REG_O26A0_T;
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

#define BND_CTRL_GSC_RXCLKDRV_M0_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_GSC_GSC_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_GSC_GSC_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_GSC_GSC_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_GSC_GSC_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x010C)

/*-----------------------------------------------------------------------------------------
    0xCCC9_2000    rxclkdrv_m0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_m0_pdb:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_m0_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_GSC_RXCLKDRV_M0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2100    gsc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_gsc_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_gsc_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_GSC_GSC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2104    gsc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_GSC_GSC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_2108    gsc_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_GSC_GSC_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC9_210C    gsc_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_GSC_GSC_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_GSC_RXCLKDRV_M0_O26A0_T    rxclkdrv_m0;            // 0xCCC9_2000
    UINT32                             _rsvd_00[63];            // 0xCCC9_2004 ~ 0xCCC9_20FC
    BND_CTRL_GSC_GSC_MEM0_O26A0_T      gsc_mem0   ;             // 0xCCC9_2100
    BND_CTRL_GSC_GSC_MEM1_O26A0_T      gsc_mem1   ;             // 0xCCC9_2104
    BND_CTRL_GSC_GSC_MEM3_O26A0_T      gsc_mem3   ;             // 0xCCC9_2108
    BND_CTRL_GSC_GSC_MEM4_O26A0_T      gsc_mem4   ;             // 0xCCC9_210C
}BND_CTRL_GSC_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_GSC_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

