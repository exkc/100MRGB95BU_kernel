#ifndef _CTOP_CTRL_POR_O20A0_REG_H_
#define _CTOP_CTRL_POR_O20A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC330_0C00    power_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_wov             :  1,    //      0
    reg_nisol_lgsr            :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_nisolate_ethernet     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pwrup_lgsr            :  4,    //  11: 8
    reg_pwrup_wov             :  4,    //  15:12
    reg_npwrup_lgsr_sram      :  8,    //  23:16
    reg_npwrup_wov_sram       :  8;    //  31:24
}CTOP_CTRL_POR_POWER_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C04    power_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwrup_ack_lgsr        :  4,    //   3: 0
    reg_pwrup_ack_wov         :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}CTOP_CTRL_POR_POWER_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C08    micom_rst_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wdt_reset_mux_sel     :  1,    //      0
    reg_sw_reset_mux_sel      :  1,    //      1
    reg_crg_top_reset_mux_sel :  1,    //      2
    reg_soft_rst_micom_from_cpu: 1,    //      3
    reg_micom_peri_bnd_reset_mux_sel: 1,    //  4
    reg_micom_adapter_reset_mux_sel: 1,    //  5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_POR_MICOM_RST_CTRL_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C0C    fw_resetved_ctrl00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL00        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL00_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C10    fw_resetved_ctrl01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL01        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL01_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C14    fw_resetved_ctrl02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL02        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C18    fw_resetved_ctrl03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL03        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C1C    fw_resetved_ctrl04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL04        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C20    fw_resetved_ctrl05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL05        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C24    fw_resetved_ctrl06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL06        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C28    fw_resetved_ctrl07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL07        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C2C    fw_resetved_ctrl08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL08        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC330_0C30    fw_resetved_ctrl09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    FW_RESETVED_CTRL09        : 31;    //  31: 0
}CTOP_CTRL_POR_FW_RESETVED_CTRL09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_por Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_POR_POWER_CTRL00_O20A0_T           power_ctrl00             ;         // 0xC330_0C00
CTOP_CTRL_POR_POWER_CTRL01_O20A0_T           power_ctrl01             ;         // 0xC330_0C04
CTOP_CTRL_POR_MICOM_RST_CTRL_O20A0_T         micom_rst_ctrl           ;         // 0xC330_0C08
CTOP_CTRL_POR_FW_RESETVED_CTRL00_O20A0_T     fw_resetved_ctrl00       ;         // 0xC330_0C0C
CTOP_CTRL_POR_FW_RESETVED_CTRL01_O20A0_T     fw_resetved_ctrl01       ;         // 0xC330_0C10
CTOP_CTRL_POR_FW_RESETVED_CTRL02_O20A0_T     fw_resetved_ctrl02       ;         // 0xC330_0C14
CTOP_CTRL_POR_FW_RESETVED_CTRL03_O20A0_T     fw_resetved_ctrl03       ;         // 0xC330_0C18
CTOP_CTRL_POR_FW_RESETVED_CTRL04_O20A0_T     fw_resetved_ctrl04       ;         // 0xC330_0C1C
CTOP_CTRL_POR_FW_RESETVED_CTRL05_O20A0_T     fw_resetved_ctrl05       ;         // 0xC330_0C20
CTOP_CTRL_POR_FW_RESETVED_CTRL06_O20A0_T     fw_resetved_ctrl06       ;         // 0xC330_0C24
CTOP_CTRL_POR_FW_RESETVED_CTRL07_O20A0_T     fw_resetved_ctrl07       ;         // 0xC330_0C28
CTOP_CTRL_POR_FW_RESETVED_CTRL08_O20A0_T     fw_resetved_ctrl08       ;         // 0xC330_0C2C
CTOP_CTRL_POR_FW_RESETVED_CTRL09_O20A0_T     fw_resetved_ctrl09       ;         // 0xC330_0C30
} CTOP_CTRL_POR_REG_O20A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_POR_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

