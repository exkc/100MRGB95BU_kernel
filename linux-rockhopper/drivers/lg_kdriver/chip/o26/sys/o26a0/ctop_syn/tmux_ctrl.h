#ifndef _TMUX_CTRL_REG_O26A0_H_
#define _TMUX_CTRL_REG_O26A0_H_

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
    0xCCC3_3000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_top_monitor_sel_1     :  4,    //   3: 0
    reg_top_monitor_sel_2     :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}TMUX_CTRL_MON_SEL_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_3004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbm_monitor_sel_0     :  4,    //   3: 0
    reg_lbm_monitor_sel_1     :  4,    //   7: 4
    reg_imx_monitor_sel_0     :  4,    //  11: 8
    reg_imx_monitor_sel_1     :  4,    //  15:12
    reg_fms_monitor_sel_0     :  4,    //  19:16
    reg_fms_monitor_sel_1     :  4,    //  23:20
                              :  8;    //  31:24 reserved
}TMUX_CTRL_MON_SEL_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_3008    mon_sel_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd0_monitor_sel_0     :  4,    //   3: 0
    reg_vd0_monitor_sel_1     :  4,    //   7: 4
    reg_me0_monitor_sel_0     :  4,    //  11: 8
    reg_me0_monitor_sel_1     :  4,    //  15:12
    reg_lnx0_monitor_sel_0    :  4,    //  19:16
    reg_lnx0_monitor_sel_1    :  4,    //  23:20
                              :  8;    //  31:24 reserved
}TMUX_CTRL_MON_SEL_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    tmux_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_O26A0_T        mon_sel_0  ;             // 0xCCC3_3000
    TMUX_CTRL_MON_SEL_1_O26A0_T        mon_sel_1  ;             // 0xCCC3_3004
    TMUX_CTRL_MON_SEL_2_O26A0_T        mon_sel_2  ;             // 0xCCC3_3008
}TMUX_CTRL_REG_O26A0_T;
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

#define TMUX_CTRL_MON_SEL_0_O26A0_T_OFF                     (BASEADDRESS+0x0000)
#define TMUX_CTRL_MON_SEL_1_O26A0_T_OFF                     (BASEADDRESS+0x0004)
#define TMUX_CTRL_MON_SEL_2_O26A0_T_OFF                     (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCCC3_3000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_top_monitor_sel_1: 4;    //  3: 0
    UINT32 reg_top_monitor_sel_2: 4;    //  7: 4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}TMUX_CTRL_MON_SEL_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_3004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lbm_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_lbm_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_imx_monitor_sel_0: 4;    //  11:8
    UINT32 reg_imx_monitor_sel_1: 4;    //  15:12
    UINT32 reg_fms_monitor_sel_0: 4;    //  19:16
    UINT32 reg_fms_monitor_sel_1: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}TMUX_CTRL_MON_SEL_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_3008    mon_sel_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd0_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_vd0_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_me0_monitor_sel_0: 4;    //  11:8
    UINT32 reg_me0_monitor_sel_1: 4;    //  15:12
    UINT32 reg_lnx0_monitor_sel_0: 4;    //  19:16
    UINT32 reg_lnx0_monitor_sel_1: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}TMUX_CTRL_MON_SEL_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    tmux_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_O26A0_T        mon_sel_0  ;             // 0xCCC3_3000
    TMUX_CTRL_MON_SEL_1_O26A0_T        mon_sel_1  ;             // 0xCCC3_3004
    TMUX_CTRL_MON_SEL_2_O26A0_T        mon_sel_2  ;             // 0xCCC3_3008
}TMUX_CTRL_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_TMUX_CTRL_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

