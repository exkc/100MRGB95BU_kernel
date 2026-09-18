#ifndef _BND_CTRL_EDID_M23A0_REG_H_
#define _BND_CTRL_EDID_M23A0_REG_H_

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
    0xC61B_2000    edid_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hpd_out_prt1_edid     :  1,    //      0
    reg_hpd_out_prt2_edid     :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_hpd_out_prt1          :  1,    //      4
    reg_hpd_out_prt2          :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_hpd_out_prt1_polarity_ctrl: 1,    //   8
    reg_hpd_out_prt2_polarity_ctrl: 1,    //   9
                              :  2,    //  11:10 reserved
    reg_hpd_sel               :  2,    //  13:12
                              : 18;    //  31:14 reserved
}BND_CTRL_EDID_EDID_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_2004    edid_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}BND_CTRL_EDID_EDID_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_2008    edid_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_bot_icon     :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_txclkdrv_top_icon     :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}BND_CTRL_EDID_EDID_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_200C    edid_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auto_clk_gate_en      :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_EDID_SYN_00_M23A0_T    edid_syn_00;            // 0xC61B_2000
    BND_CTRL_EDID_EDID_SYN_01_M23A0_T    edid_syn_01;            // 0xC61B_2004
    BND_CTRL_EDID_EDID_SYN_02_M23A0_T    edid_syn_02;            // 0xC61B_2008
    BND_CTRL_EDID_EDID_SYN_03_M23A0_T    edid_syn_03;            // 0xC61B_200C
}BND_CTRL_EDID_REG_M23A0_T;
/* 4 regs */

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

#define BND_CTRL_EDID_EDID_SYN_00_M23A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_EDID_EDID_SYN_01_M23A0_T_OFF                (BASEADDRESS+0x0004)
#define BND_CTRL_EDID_EDID_SYN_02_M23A0_T_OFF                (BASEADDRESS+0x0008)
#define BND_CTRL_EDID_EDID_SYN_03_M23A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC61B_2000    edid_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hpd_out_prt1_edid: 1;    //     0
    UINT32 reg_hpd_out_prt2_edid: 1;    //     1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_hpd_out_prt1   :  1;    //      4
    UINT32 reg_hpd_out_prt2   :  1;    //      5
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_hpd_out_prt1_polarity_ctrl: 1;    //  8
    UINT32 reg_hpd_out_prt2_polarity_ctrl: 1;    //  9
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_hpd_sel        :  2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}BND_CTRL_EDID_EDID_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_2004    edid_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i2c_edid_gating:  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_i2c_link_gating:  5;    //  12: 8
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}BND_CTRL_EDID_EDID_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_2008    edid_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_bot_icon: 3;    //  2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_txclkdrv_top_icon: 3;    //  6: 4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}BND_CTRL_EDID_EDID_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC61B_200C    edid_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auto_clk_gate_en: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EDID_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_EDID_SYN_00_M23A0_T    edid_syn_00;            // 0xC61B_2000
    BND_CTRL_EDID_EDID_SYN_01_M23A0_T    edid_syn_01;            // 0xC61B_2004
    BND_CTRL_EDID_EDID_SYN_02_M23A0_T    edid_syn_02;            // 0xC61B_2008
    BND_CTRL_EDID_EDID_SYN_03_M23A0_T    edid_syn_03;            // 0xC61B_200C
}BND_CTRL_EDID_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

