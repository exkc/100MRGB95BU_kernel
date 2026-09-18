#ifndef _SCRG_CTRL_ICOD_REG_O24A0_H_
#define _SCRG_CTRL_ICOD_REG_O24A0_H_

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
    0xCE86_0000    crg_icod0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0004    crg_icod1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0008    crg_icod2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_jpeg_clk_gate_en      :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_ICOD_CRG_ICOD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_000C    crg_icod3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_jpeg_n       :  1,    //      1
    reg_soft_rst_p_icod_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_x_icod_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_icod_0_axi_n: 1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_ICOD_CRG_ICOD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0010    crg_icod4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jpeg_clk_sel          :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_ICOD_CRG_ICOD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD0_O24A0_T    crg_icod0 ;             // 0xCE86_0000
    SCRG_CTRL_ICOD_CRG_ICOD1_O24A0_T    crg_icod1 ;             // 0xCE86_0004
    SCRG_CTRL_ICOD_CRG_ICOD2_O24A0_T    crg_icod2 ;             // 0xCE86_0008
    SCRG_CTRL_ICOD_CRG_ICOD3_O24A0_T    crg_icod3 ;             // 0xCE86_000C
    SCRG_CTRL_ICOD_CRG_ICOD4_O24A0_T    crg_icod4 ;             // 0xCE86_0010
}SCRG_CTRL_ICOD_REG_O24A0_T;
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

#define SCRG_CTRL_ICOD_CRG_ICOD0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_ICOD_CRG_ICOD1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_ICOD_CRG_ICOD2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_ICOD_CRG_ICOD3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_ICOD_CRG_ICOD4_O24A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE86_0000    crg_icod0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0004    crg_icod1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0008    crg_icod2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_jpeg_clk_gate_en: 1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_000C    crg_icod3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_jpeg_n:  1;    //      1
    UINT32 reg_soft_rst_p_icod_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_icod_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_icod_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE86_0010    crg_icod4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_jpeg_clk_sel   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD0_O24A0_T    crg_icod0 ;             // 0xCE86_0000
    SCRG_CTRL_ICOD_CRG_ICOD1_O24A0_T    crg_icod1 ;             // 0xCE86_0004
    SCRG_CTRL_ICOD_CRG_ICOD2_O24A0_T    crg_icod2 ;             // 0xCE86_0008
    SCRG_CTRL_ICOD_CRG_ICOD3_O24A0_T    crg_icod3 ;             // 0xCE86_000C
    SCRG_CTRL_ICOD_CRG_ICOD4_O24A0_T    crg_icod4 ;             // 0xCE86_0010
}SCRG_CTRL_ICOD_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ICOD_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

