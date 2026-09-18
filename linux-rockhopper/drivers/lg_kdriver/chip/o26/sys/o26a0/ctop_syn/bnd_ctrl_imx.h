#ifndef _BND_CTRL_IMX_REG_O26A0_H_
#define _BND_CTRL_IMX_REG_O26A0_H_

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
    0xCCC3_2100    imx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_imx_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_imx_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_IMX_IMX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2104    imx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_IMX_IMX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2108    imx_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_IMX_IMX_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_210C    imx_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_IMX_IMX_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2110    imx_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_IMX_IMX_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCCC3_2000 ~ 0xCCC3_20FC
    BND_CTRL_IMX_IMX_MEM0_O26A0_T      imx_mem0   ;             // 0xCCC3_2100
    BND_CTRL_IMX_IMX_MEM1_O26A0_T      imx_mem1   ;             // 0xCCC3_2104
    BND_CTRL_IMX_IMX_MEM2_O26A0_T      imx_mem2   ;             // 0xCCC3_2108
    BND_CTRL_IMX_IMX_MEM3_O26A0_T      imx_mem3   ;             // 0xCCC3_210C
    BND_CTRL_IMX_IMX_MEM4_O26A0_T      imx_mem4   ;             // 0xCCC3_2110
}BND_CTRL_IMX_REG_O26A0_T;
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

#define BND_CTRL_IMX_IMX_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_IMX_IMX_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_IMX_IMX_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_IMX_IMX_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_IMX_IMX_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x0110)

/*-----------------------------------------------------------------------------------------
    0xCCC3_2100    imx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_imx_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_imx_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_IMX_IMX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2104    imx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_IMX_IMX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2108    imx_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_IMX_IMX_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_210C    imx_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_IMX_IMX_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_2110    imx_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_IMX_IMX_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCCC3_2000 ~ 0xCCC3_20FC
    BND_CTRL_IMX_IMX_MEM0_O26A0_T      imx_mem0   ;             // 0xCCC3_2100
    BND_CTRL_IMX_IMX_MEM1_O26A0_T      imx_mem1   ;             // 0xCCC3_2104
    BND_CTRL_IMX_IMX_MEM2_O26A0_T      imx_mem2   ;             // 0xCCC3_2108
    BND_CTRL_IMX_IMX_MEM3_O26A0_T      imx_mem3   ;             // 0xCCC3_210C
    BND_CTRL_IMX_IMX_MEM4_O26A0_T      imx_mem4   ;             // 0xCCC3_2110
}BND_CTRL_IMX_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_IMX_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

