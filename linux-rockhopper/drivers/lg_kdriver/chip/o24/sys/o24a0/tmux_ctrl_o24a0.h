#ifndef _TMUX_CTRL_REG_O24A0_H_
#define _TMUX_CTRL_REG_O24A0_H_

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
    0xCC84_2000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_top_monitor_sel_1     :  4,    //   3: 0
    reg_top_monitor_sel_2     :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}TMUX_CTRL_MON_SEL_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_2004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_monitor_sel_0     :  4,    //   3: 0
    reg_nd0_monitor_sel_1     :  4,    //   7: 4
    reg_me0_monitor_sel_0     :  4,    //  11: 8
    reg_me0_monitor_sel_1     :  4,    //  15:12
    reg_vd1_monitor_sel_0     :  4,    //  19:16
    reg_vd1_monitor_sel_1     :  4,    //  23:20
                              :  8;    //  31:24 reserved
}TMUX_CTRL_MON_SEL_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_2008    mon_sel_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc_monitor_sel_0     :  4,    //   3: 0
    reg_fmc_monitor_sel_1     :  4,    //   7: 4
    reg_hdmi_monitor_sel_0    :  4,    //  11: 8
    reg_hdmi_monitor_sel_1    :  4,    //  15:12
    reg_me1_monitor_sel_0     :  4,    //  19:16
    reg_me1_monitor_sel_1     :  4,    //  23:20
                              :  8;    //  31:24 reserved
}TMUX_CTRL_MON_SEL_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    tmux_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_O24A0_T        mon_sel_0  ;             // 0xCC84_2000
    TMUX_CTRL_MON_SEL_1_O24A0_T        mon_sel_1  ;             // 0xCC84_2004
    TMUX_CTRL_MON_SEL_2_O24A0_T        mon_sel_2  ;             // 0xCC84_2008
}TMUX_CTRL_REG_O24A0_T;
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

#define TMUX_CTRL_MON_SEL_0_O24A0_T_OFF                     (BASEADDRESS+0x0000)
#define TMUX_CTRL_MON_SEL_1_O24A0_T_OFF                     (BASEADDRESS+0x0004)
#define TMUX_CTRL_MON_SEL_2_O24A0_T_OFF                     (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCC84_2000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_top_monitor_sel_1: 4;    //  3: 0
    UINT32 reg_top_monitor_sel_2: 4;    //  7: 4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}TMUX_CTRL_MON_SEL_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_2004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nd0_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_nd0_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_me0_monitor_sel_0: 4;    //  11:8
    UINT32 reg_me0_monitor_sel_1: 4;    //  15:12
    UINT32 reg_vd1_monitor_sel_0: 4;    //  19:16
    UINT32 reg_vd1_monitor_sel_1: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}TMUX_CTRL_MON_SEL_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_2008    mon_sel_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_fmc_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_hdmi_monitor_sel_0: 4;    //  11:8
    UINT32 reg_hdmi_monitor_sel_1: 4;    //  15:12
    UINT32 reg_me1_monitor_sel_0: 4;    //  19:16
    UINT32 reg_me1_monitor_sel_1: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}TMUX_CTRL_MON_SEL_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    tmux_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_O24A0_T        mon_sel_0  ;             // 0xCC84_2000
    TMUX_CTRL_MON_SEL_1_O24A0_T        mon_sel_1  ;             // 0xCC84_2004
    TMUX_CTRL_MON_SEL_2_O24A0_T        mon_sel_2  ;             // 0xCC84_2008
}TMUX_CTRL_REG_O24A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _TMUX_CTRL_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

