#ifndef _MICOM_BND_CTRL_WOC_M23A0_REG_H_
#define _MICOM_BND_CTRL_WOC_M23A0_REG_H_

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
    0xF351_2000    woc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hpd_out_prt3_edid     :  1,    //      0
    reg_hpd_out_prt4_edid     :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_hpd_out_prt3          :  1,    //      4
    reg_hpd_out_prt4          :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_hpd_out_prt3_polarity_ctrl: 1,    //   8
    reg_hpd_out_prt4_polarity_ctrl: 1,    //   9
                              :  2,    //  11:10 reserved
    reg_hpd_sel               :  2,    //  13:12
                              : 18;    //  31:14 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2008    woc_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel2        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_200C    woc_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel1        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2010    woc_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_jtag_sel0        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2014    woc_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel2        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2018    woc_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel1        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_201C    woc_syn_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel0        :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MICOM_BND_CTRL_WOC_WOC_SYN_07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BND_CTRL_WOC_WOC_SYN_00_M23A0_T    woc_syn_00 ;             // 0xF351_2000
    MICOM_BND_CTRL_WOC_WOC_SYN_01_M23A0_T    woc_syn_01 ;             // 0xF351_2004
    MICOM_BND_CTRL_WOC_WOC_SYN_02_M23A0_T    woc_syn_02 ;             // 0xF351_2008
    MICOM_BND_CTRL_WOC_WOC_SYN_03_M23A0_T    woc_syn_03 ;             // 0xF351_200C
    MICOM_BND_CTRL_WOC_WOC_SYN_04_M23A0_T    woc_syn_04 ;             // 0xF351_2010
    MICOM_BND_CTRL_WOC_WOC_SYN_05_M23A0_T    woc_syn_05 ;             // 0xF351_2014
    MICOM_BND_CTRL_WOC_WOC_SYN_06_M23A0_T    woc_syn_06 ;             // 0xF351_2018
    MICOM_BND_CTRL_WOC_WOC_SYN_07_M23A0_T    woc_syn_07 ;             // 0xF351_201C
}MICOM_BND_CTRL_WOC_REG_M23A0_T;
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

#define MICOM_BND_CTRL_WOC_WOC_SYN_00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define MICOM_BND_CTRL_WOC_WOC_SYN_01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define MICOM_BND_CTRL_WOC_WOC_SYN_02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define MICOM_BND_CTRL_WOC_WOC_SYN_03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define MICOM_BND_CTRL_WOC_WOC_SYN_04_M23A0_T_OFF                 (BASEADDRESS+0x0010)
#define MICOM_BND_CTRL_WOC_WOC_SYN_05_M23A0_T_OFF                 (BASEADDRESS+0x0014)
#define MICOM_BND_CTRL_WOC_WOC_SYN_06_M23A0_T_OFF                 (BASEADDRESS+0x0018)
#define MICOM_BND_CTRL_WOC_WOC_SYN_07_M23A0_T_OFF                 (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xF351_2000    woc_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hpd_out_prt3_edid: 1;    //     0
    UINT32 reg_hpd_out_prt4_edid: 1;    //     1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_hpd_out_prt3   :  1;    //      4
    UINT32 reg_hpd_out_prt4   :  1;    //      5
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_hpd_out_prt3_polarity_ctrl: 1;    //  8
    UINT32 reg_hpd_out_prt4_polarity_ctrl: 1;    //  9
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_hpd_sel        :  2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i2c_edid_gating:  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_i2c_link_gating:  5;    //  12: 8
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2008    woc_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel2 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_200C    woc_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel1 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2010    woc_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_jtag_sel0 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2014    woc_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel2 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_2018    woc_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel1 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_201C    woc_syn_07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel0 :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MICOM_BND_CTRL_WOC_WOC_SYN_07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_BND_CTRL_WOC_WOC_SYN_00_M23A0_T    woc_syn_00 ;             // 0xF351_2000
    MICOM_BND_CTRL_WOC_WOC_SYN_01_M23A0_T    woc_syn_01 ;             // 0xF351_2004
    MICOM_BND_CTRL_WOC_WOC_SYN_02_M23A0_T    woc_syn_02 ;             // 0xF351_2008
    MICOM_BND_CTRL_WOC_WOC_SYN_03_M23A0_T    woc_syn_03 ;             // 0xF351_200C
    MICOM_BND_CTRL_WOC_WOC_SYN_04_M23A0_T    woc_syn_04 ;             // 0xF351_2010
    MICOM_BND_CTRL_WOC_WOC_SYN_05_M23A0_T    woc_syn_05 ;             // 0xF351_2014
    MICOM_BND_CTRL_WOC_WOC_SYN_06_M23A0_T    woc_syn_06 ;             // 0xF351_2018
    MICOM_BND_CTRL_WOC_WOC_SYN_07_M23A0_T    woc_syn_07 ;             // 0xF351_201C
}MICOM_BND_CTRL_WOC_REG_M23A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

