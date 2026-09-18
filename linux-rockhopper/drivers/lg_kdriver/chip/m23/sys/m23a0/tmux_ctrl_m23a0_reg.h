#ifndef _TMUX_CTRL_M23A0_REG_H_
#define _TMUX_CTRL_M23A0_REG_H_

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
    0xCECB_3000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_monitor_sel_0     :  4,    //   3: 0
    reg_bus_monitor_sel_1     :  4,    //   7: 4
    reg_dpe_monitor_sel_0     :  4,    //  11: 8
    reg_dpe_monitor_sel_1     :  4,    //  15:12
    reg_fmc_monitor_sel_0     :  4,    //  19:16
    reg_fmc_monitor_sel_1     :  4,    //  23:20
    reg_top_monitor_sel_1     :  4,    //  27:24
    reg_top_monitor_sel_2     :  4;    //  31:28
}TMUX_CTRL_MON_SEL_0_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_3004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nd0_monitor_sel_0     :  4,    //   3: 0
    reg_nd0_monitor_sel_1     :  4,    //   7: 4
    reg_fms_monitor_sel_0     :  4,    //  11: 8
    reg_fms_monitor_sel_1     :  4,    //  15:12
                              : 16;    //  31:16 reserved
}TMUX_CTRL_MON_SEL_1_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_M23A0_T     mon_sel_0  ;             // 0xCECB_3000
    TMUX_CTRL_MON_SEL_1_M23A0_T     mon_sel_1  ;             // 0xCECB_3004
}TMUX_CTRL_REG_M23A0_T;
/* 2 regs */

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

#define TMUX_CTRL_MON_SEL_0_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define TMUX_CTRL_MON_SEL_1_M23A0_T_OFF                  (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCECB_3000    mon_sel_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_bus_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_dpe_monitor_sel_0: 4;    //  11:8
    UINT32 reg_dpe_monitor_sel_1: 4;    //  15:12
    UINT32 reg_fmc_monitor_sel_0: 4;    //  19:16
    UINT32 reg_fmc_monitor_sel_1: 4;    //  23:20
    UINT32 reg_top_monitor_sel_1: 4;    //  27:24
    UINT32 reg_top_monitor_sel_2: 4;    //  31:28
    };
}TMUX_CTRL_MON_SEL_0_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_3004    mon_sel_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nd0_monitor_sel_0: 4;    //  3: 0
    UINT32 reg_nd0_monitor_sel_1: 4;    //  7: 4
    UINT32 reg_fms_monitor_sel_0: 4;    //  11:8
    UINT32 reg_fms_monitor_sel_1: 4;    //  15:12
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}TMUX_CTRL_MON_SEL_1_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TMUX_CTRL_MON_SEL_0_M23A0_T     mon_sel_0  ;             // 0xCECB_3000
    TMUX_CTRL_MON_SEL_1_M23A0_T     mon_sel_1  ;             // 0xCECB_3004
}TMUX_CTRL_REG_M23A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

