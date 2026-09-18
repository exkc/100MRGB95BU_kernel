#ifndef _BND_CTRL_EDID_A0_REG_H_
#define _BND_CTRL_EDID_A0_REG_H_

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
    0xC68F_0000    edid_bnd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_edid_bnd            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_BND00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC68F_0004    edid_bnd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag_hdmi_dbg         :  1,    //      0
    reg_gp6_0_mux_en          :  1,    //      1
    reg_gp6_1_mux_en          :  1,    //      2
    reg_gp6_2_mux_en          :  1,    //      3
    reg_gp6_3_mux_en          :  1,    //      4
    reg_gp6_4_mux_en          :  1,    //      5
    reg_gp6_5_mux_en          :  1,    //      6
    reg_ddc_write_en__and__hdmi1_en: 1,    //  7
    reg_ddc_write_en__and__hdmi2_en: 1,    //  8
    reg_ddc_write_en__and__hdmi3_en: 1,    //  9
    reg_ddc_write_en__and__hdmi4_en: 1,    //  10
                              : 21;    //  31:11 reserved
}BND_CTRL_EDID_EDID_BND01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC68F_0008    edid_bnd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    edid_prt0_hpd_out         :  1,    //      0
    edid_prt1_hpd_out         :  1,    //      1
    edid_prt2_hpd_out         :  1,    //      2
    edid_prt3_hpd_out         :  1,    //      3
    reg_phy0_cbus_hpd_out     :  1,    //      4
    reg_phy1_cbus_hpd_out     :  1,    //      5
    reg_phy2_cbus_hpd_out     :  1,    //      6
    reg_phy3_cbus_hpd_out     :  1,    //      7
    reg_edid_wr_done          :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_EDID_EDID_BND02_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_EDID_EDID_BND00_O18_A0              edid_bnd00               ;         // 0xC68F_0000
BND_CTRL_EDID_EDID_BND01_O18_A0              edid_bnd01               ;         // 0xC68F_0004
BND_CTRL_EDID_EDID_BND02_O18_A0              edid_bnd02               ;         // 0xC68F_0008
} BND_CTRL_EDID_REG_O18_A0;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_EDID_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

