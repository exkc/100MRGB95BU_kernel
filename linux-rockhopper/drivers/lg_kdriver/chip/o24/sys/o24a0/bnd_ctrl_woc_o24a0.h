#ifndef _BND_CTRL_WOC_REG_O24A0_H_
#define _BND_CTRL_WOC_REG_O24A0_H_

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
    0xF33F_2000    woc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel0        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel1        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2008    woc_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel2        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_200C    woc_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel3        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2010    woc_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel4        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2020    woc_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel0        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2024    woc_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel1        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2028    woc_syn_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel2        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_WOC_WOC_SYN_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOC_WOC_SYN_00_O24A0_T    woc_syn_00 ;             // 0xF33F_2000
    BND_CTRL_WOC_WOC_SYN_01_O24A0_T    woc_syn_01 ;             // 0xF33F_2004
    BND_CTRL_WOC_WOC_SYN_02_O24A0_T    woc_syn_02 ;             // 0xF33F_2008
    BND_CTRL_WOC_WOC_SYN_03_O24A0_T    woc_syn_03 ;             // 0xF33F_200C
    BND_CTRL_WOC_WOC_SYN_04_O24A0_T    woc_syn_04 ;             // 0xF33F_2010
    UINT32                             _rsvd_00[3];             // 0xF33F_2014 ~ 0xF33F_201C
    BND_CTRL_WOC_WOC_SYN_05_O24A0_T    woc_syn_05 ;             // 0xF33F_2020
    BND_CTRL_WOC_WOC_SYN_06_O24A0_T    woc_syn_06 ;             // 0xF33F_2024
    BND_CTRL_WOC_WOC_SYN_07_O24A0_T    woc_syn_07 ;             // 0xF33F_2028
}BND_CTRL_WOC_REG_O24A0_T;
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

#define BND_CTRL_WOC_WOC_SYN_00_O24A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_WOC_WOC_SYN_01_O24A0_T_OFF                 (BASEADDRESS+0x0004)
#define BND_CTRL_WOC_WOC_SYN_02_O24A0_T_OFF                 (BASEADDRESS+0x0008)
#define BND_CTRL_WOC_WOC_SYN_03_O24A0_T_OFF                 (BASEADDRESS+0x000C)
#define BND_CTRL_WOC_WOC_SYN_04_O24A0_T_OFF                 (BASEADDRESS+0x0010)
#define BND_CTRL_WOC_WOC_SYN_05_O24A0_T_OFF                 (BASEADDRESS+0x0020)
#define BND_CTRL_WOC_WOC_SYN_06_O24A0_T_OFF                 (BASEADDRESS+0x0024)
#define BND_CTRL_WOC_WOC_SYN_07_O24A0_T_OFF                 (BASEADDRESS+0x0028)

/*-----------------------------------------------------------------------------------------
    0xF33F_2000    woc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel0 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel1 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2008    woc_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel2 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_200C    woc_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel3 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2010    woc_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel4 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2020    woc_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel0 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2024    woc_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel1 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33F_2028    woc_syn_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel2 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_WOC_WOC_SYN_07_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOC_WOC_SYN_00_O24A0_T    woc_syn_00 ;             // 0xF33F_2000
    BND_CTRL_WOC_WOC_SYN_01_O24A0_T    woc_syn_01 ;             // 0xF33F_2004
    BND_CTRL_WOC_WOC_SYN_02_O24A0_T    woc_syn_02 ;             // 0xF33F_2008
    BND_CTRL_WOC_WOC_SYN_03_O24A0_T    woc_syn_03 ;             // 0xF33F_200C
    BND_CTRL_WOC_WOC_SYN_04_O24A0_T    woc_syn_04 ;             // 0xF33F_2010
    UINT32                             _rsvd_00[3];             // 0xF33F_2014 ~ 0xF33F_201C
    BND_CTRL_WOC_WOC_SYN_05_O24A0_T    woc_syn_05 ;             // 0xF33F_2020
    BND_CTRL_WOC_WOC_SYN_06_O24A0_T    woc_syn_06 ;             // 0xF33F_2024
    BND_CTRL_WOC_WOC_SYN_07_O24A0_T    woc_syn_07 ;             // 0xF33F_2028
}BND_CTRL_WOC_REG_O24A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_WOC_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

