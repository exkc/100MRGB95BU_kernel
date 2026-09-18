#ifndef _SCRG_CTRL_ICOD_REG_H_
#define _SCRG_CTRL_ICOD_REG_H_

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
    0x5E_0000    crg_icod00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0004    crg_icod01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ICOD_CRG_ICOD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0008    crg_icod02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jpeg_clk_gate_en      :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_ICOD_CRG_ICOD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_000C    crg_icod03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_jpeg_n       :  1,    //      0
    reg_soft_rst_p_icod_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_x_icod_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_x_icod_0_axi_n: 1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_ICOD_CRG_ICOD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0010    crg_icod04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jpeg_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ICOD_CRG_ICOD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD00_O22A0_T        crg_icod00 ;             // 0x5E_0000
    SCRG_CTRL_ICOD_CRG_ICOD01_O22A0_T        crg_icod01 ;             // 0x5E_0004
    SCRG_CTRL_ICOD_CRG_ICOD02_O22A0_T        crg_icod02 ;             // 0x5E_0008
    SCRG_CTRL_ICOD_CRG_ICOD03_O22A0_T        crg_icod03 ;             // 0x5E_000C
    SCRG_CTRL_ICOD_CRG_ICOD04_O22A0_T        crg_icod04 ;             // 0x5E_0010
}SCRG_CTRL_ICOD_REG_O22A0_T;
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

#define SCRG_CTRL_ICOD_CRG_ICOD00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_ICOD_CRG_ICOD01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_ICOD_CRG_ICOD02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_ICOD_CRG_ICOD03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_ICOD_CRG_ICOD04_O22A0_T_OFF                     (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x5E_0000    crg_icod00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0004    crg_icod01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ICOD_CRG_ICOD01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0008    crg_icod02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_jpeg_clk_gate_en: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_000C    crg_icod03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_jpeg_n:  1;    //      0
    UINT32 reg_soft_rst_p_icod_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_x_icod_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_icod_0_axi_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5E_0010    crg_icod04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_jpeg_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ICOD_CRG_ICOD04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_icod Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICOD_CRG_ICOD00_O22A0_T        crg_icod00 ;             // 0x5E_0000
    SCRG_CTRL_ICOD_CRG_ICOD01_O22A0_T        crg_icod01 ;             // 0x5E_0004
    SCRG_CTRL_ICOD_CRG_ICOD02_O22A0_T        crg_icod02 ;             // 0x5E_0008
    SCRG_CTRL_ICOD_CRG_ICOD03_O22A0_T        crg_icod03 ;             // 0x5E_000C
    SCRG_CTRL_ICOD_CRG_ICOD04_O22A0_T        crg_icod04 ;             // 0x5E_0010
}SCRG_CTRL_ICOD_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

