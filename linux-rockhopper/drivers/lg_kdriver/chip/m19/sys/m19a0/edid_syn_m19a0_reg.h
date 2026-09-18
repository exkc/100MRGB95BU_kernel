#ifndef _EDID_SYN_M19A0_REG_H_
#define _EDID_SYN_M19A0_REG_H_

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
    0xC36C_1050    crg_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apb_clk_gate_en           :  1,    //      0
    edid_clk_sel              :  2,    //   2: 1
                              :  1,    //      3 reserved
    swrst_comm_apb            :  1,    //      4
                              :  3,    //   7: 5 reserved
    swrst_edid0               :  1,    //      8
    swrst_edid1               :  1,    //      9
    swrst_edid2               :  1,    //     10
    swrst_edid3               :  1,    //     11
    swrst_apb0                :  1,    //     12
    swrst_apb1                :  1,    //     13
    swrst_apb2                :  1,    //     14
    swrst_apb3                :  1,    //     15
                              : 16;    //  31:16 reserved
}EDID_SYN_CRG_EDID00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC36C_1054    pad_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi2_0_scl_pd        :  1,    //      0
    reg_hdmi2_0_scl_pu        :  1,    //      1
    reg_hdmi2_0_scl_ds        :  1,    //      2
                              :  1,    //      3 reserved
    reg_hdmi2_0_sda_pd        :  1,    //      4
    reg_hdmi2_0_sda_pu        :  1,    //      5
    reg_hdmi2_0_sda_ds        :  1,    //      6
                              :  1,    //      7 reserved
    reg_hdmi2_1_scl_pd        :  1,    //      8
    reg_hdmi2_1_scl_pu        :  1,    //      9
    reg_hdmi2_1_scl_ds        :  1,    //     10
                              :  1,    //     11 reserved
    reg_hdmi2_1_sda_pd        :  1,    //     12
    reg_hdmi2_1_sda_pu        :  1,    //     13
    reg_hdmi2_1_sda_ds        :  1,    //     14
                              :  1,    //     15 reserved
    reg_hdmi2_2_scl_pd        :  1,    //     16
    reg_hdmi2_2_scl_pu        :  1,    //     17
    reg_hdmi2_2_scl_ds        :  1,    //     18
                              :  1,    //     19 reserved
    reg_hdmi2_2_sda_pd        :  1,    //     20
    reg_hdmi2_2_sda_pu        :  1,    //     21
    reg_hdmi2_2_sda_ds        :  1,    //     22
                              :  1,    //     23 reserved
    reg_hdmi2_3_scl_pd        :  1,    //     24
    reg_hdmi2_3_scl_pu        :  1,    //     25
    reg_hdmi2_3_scl_ds        :  1,    //     26
                              :  1,    //     27 reserved
    reg_hdmi2_3_sda_pd        :  1,    //     28
    reg_hdmi2_3_sda_pu        :  1,    //     29
    reg_hdmi2_3_sda_ds        :  1,    //     30
                              :  1;    //  31:31 reserved
}EDID_SYN_PAD_EDID01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC36C_1058    pad_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi2_0_5v_in_pd      :  1,    //      0
    reg_hdmi2_0_5v_in_pu      :  1,    //      1
    reg_hdmi2_0_5v_in_ds      :  1,    //      2
                              :  1,    //      3 reserved
    reg_hdmi2_1_5v_in_pd      :  1,    //      4
    reg_hdmi2_1_5v_in_pu      :  1,    //      5
    reg_hdmi2_1_5v_in_ds      :  1,    //      6
                              :  1,    //      7 reserved
    reg_hdmi2_2_5v_in_pd      :  1,    //      8
    reg_hdmi2_2_5v_in_pu      :  1,    //      9
    reg_hdmi2_2_5v_in_ds      :  1,    //     10
                              :  1,    //     11 reserved
    reg_hdmi2_3_5v_in_pd      :  1,    //     12
    reg_hdmi2_3_5v_in_pu      :  1,    //     13
    reg_hdmi2_3_5v_in_ds      :  1,    //     14
                              :  1,    //     15 reserved
    reg_hdmi2_0_hpd_pd        :  1,    //     16
    reg_hdmi2_0_hpd_pu        :  1,    //     17
    reg_hdmi2_0_hpd_ds        :  1,    //     18
                              :  1,    //     19 reserved
    reg_hdmi2_1_hpd_pd        :  1,    //     20
    reg_hdmi2_1_hpd_pu        :  1,    //     21
    reg_hdmi2_1_hpd_ds        :  1,    //     22
                              :  1,    //     23 reserved
    reg_hdmi2_2_hpd_pd        :  1,    //     24
    reg_hdmi2_2_hpd_pu        :  1,    //     25
    reg_hdmi2_2_hpd_ds        :  1,    //     26
                              :  1,    //     27 reserved
    reg_hdmi2_3_hpd_pd        :  1,    //     28
    reg_hdmi2_3_hpd_pu        :  1,    //     29
    reg_hdmi2_3_hpd_ds        :  1,    //     30
                              :  1;    //  31:31 reserved
}EDID_SYN_PAD_EDID02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC36C_1064    pad_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_ddr_icon     :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_txclkdrv_dmd_icon     :  3,    //   6: 4
    reg_txclkdrv_dmd_pdb      :  1,    //      7
                              :  8,    //  15: 8 reserved
    reg_use_cpu_gpio_6_0      :  1,    //     16
    reg_use_cpu_gpio_6_1      :  1,    //     17
    reg_use_cpu_gpio_6_2      :  1,    //     18
    reg_use_cpu_gpio_6_3      :  1,    //     19
    reg_use_cpu_gpio_6_4      :  1,    //     20
    reg_use_cpu_gpio_6_5      :  1,    //     21
    reg_use_cpu_gpio_6_6      :  1,    //     22
    reg_use_cpu_gpio_6_7      :  1,    //     23
    reg_jtag_hdmi_dbg         :  1,    //     24
                              :  7;    //  31:25 reserved
}EDID_SYN_PAD_EDID03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    edid_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
EDID_SYN_CRG_EDID00_M19A0_T                  crg_edid00               ;         // 0xC36C_1050
EDID_SYN_PAD_EDID01_M19A0_T                  pad_edid01               ;         // 0xC36C_1054
EDID_SYN_PAD_EDID02_M19A0_T                  pad_edid02               ;         // 0xC36C_1058
UINT32                                                 _rsvd_00[   2] ;         // 0xC36C_105C ~ 0xC36C_1060
EDID_SYN_PAD_EDID03_M19A0_T                  pad_edid03               ;         // 0xC36C_1064
} EDID_SYN_REG_M19A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _EDID_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

