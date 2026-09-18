#ifndef _BND_CTRL_BMC_A0_REG_H_
#define _BND_CTRL_BMC_A0_REG_H_

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
    0xC7FC_1000    crg_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apb_clk_gate_en           :  1,    //      0
    axi_clk_gate_en           :  1,    //      1
    axi_soc_clk_gate_en       :  1,    //      2
    fan_clk_gate_en           :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_BMC_CRG_BMC00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1004    crg_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_cvbs                :  1,    //      0
    swrst_f54m                :  1,    //      1
    swrst_f27m                :  1,    //      2
    swrst_vdac                :  1,    //      3
    swrst_auad                :  1,    //      4
    swrst_pix                 :  1,    //      5
    swrst_f24m                :  1,    //      6
    swrst_axi_soc             :  1,    //      7
    swrst_axi                 :  1,    //      8
    swrst_apb                 :  1,    //      9
    swrst_fan                 :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_BMC_CRG_BMC01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1008    crg_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_f256fs_src          :  1,    //      0
    swrst_audclk_out_sub2     :  1,    //      1
    swrst_audclk_out2         :  1,    //      2
    swrst_auda_f256fs_clk1    :  1,    //      3
    swrst_auda_f256fs_clk0    :  1,    //      4
    swrst_audclk_out_sub      :  1,    //      5
    swrst_aud_fs26clk         :  1,    //      6
    swrst_aud_fs25clk         :  1,    //      7
    swrst_aud_fs24clk         :  1,    //      8
    swrst_aud_fs23clk         :  1,    //      9
    swrst_aud_fs22clk         :  1,    //     10
    swrst_aud_fs21clk         :  1,    //     11
    swrst_aud_fs20clk         :  1,    //     12
    swrst_audclk_out          :  1,    //     13
    swrst_aclk_mux2           :  1,    //     14
    swrst_adto4               :  1,    //     15
    swrst_adto3               :  1,    //     16
    swrst_adto2               :  1,    //     17
    swrst_adto1               :  1,    //     18
    swrst_fs00                :  1,    //     19
                              : 12;    //  31:20 reserved
}BND_CTRL_BMC_CRG_BMC02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_100C    crg_bmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_afe3ch_ext_clock  :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_sel_hostif_clock      :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_BMC_CRG_BMC03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1010    crg_bmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_CRG_BMC04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1014    crg_bmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_CRG_BMC05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_101C    crg_bmc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_CRG_BMC06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1020    crg_bmc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_CRG_BMC07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1024    crg_bmc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_add_value       : 32;    //  31: 0
}BND_CTRL_BMC_CRG_BMC08_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1028    crg_bmc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto3_err_value       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}BND_CTRL_BMC_CRG_BMC09_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_102C    crg_bmc10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux4_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux4_src             :  4,    //   7: 4
    aclk_mux3_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux3_src             :  4,    //  15:12
    aclk_mux2_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux2_src             :  4,    //  23:20
    aclk_mux1_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux1_src             :  4;    //  31:28
}BND_CTRL_BMC_CRG_BMC10_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1038    crg_bmc13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux8_div             :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux8_src             :  4,    //   7: 4
    aclk_mux7_div             :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux7_src             :  4,    //  15:12
    aclk_mux6_div             :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux6_src             :  4,    //  23:20
    aclk_mux5_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux5_src             :  4;    //  31:28
}BND_CTRL_BMC_CRG_BMC13_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_103C    crg_bmc14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux12_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux12_src            :  4,    //   7: 4
    aclk_mux11_div            :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux11_src            :  4,    //  15:12
    aclk_mux10_div            :  3,    //  18:16
                              :  1,    //     19 reserved
    aclk_mux10_src            :  4,    //  23:20
    aclk_mux9_div             :  3,    //  26:24
                              :  1,    //     27 reserved
    aclk_mux9_src             :  4;    //  31:28
}BND_CTRL_BMC_CRG_BMC14_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1040    crg_bmc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aclk_mux14_div            :  3,    //   2: 0
                              :  1,    //      3 reserved
    aclk_mux14_src            :  4,    //   7: 4
    aclk_mux13_div            :  3,    //  10: 8
                              :  1,    //     11 reserved
    aclk_mux13_src            :  4,    //  15:12
                              : 16;    //  31:16 reserved
}BND_CTRL_BMC_CRG_BMC15_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1044    crg_bmc16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    audclk_out_mux_sel        :  1,    //      0
    audclk_out_sub_mux_sel    :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_BMC_CRG_BMC16_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1048    crg_bmc17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sel_inv_aud_fsclk         : 10,    //   9: 0
    sel_inv_aud_fs20clk       :  1,    //     10
    sel_inv_aclk_mux12        :  1,    //     11
    sel_inv_aclk_mux11        :  1,    //     12
    sel_inv_mclk1             :  1,    //     13
    sel_inv_mclk0             :  1,    //     14
    sel_inv_f54m_clock        :  1,    //     15
    sel_inv_f27m_clock        :  1,    //     16
    sel_inv_vdac_clock        :  1,    //     17
                              : 14;    //  31:18 reserved
}BND_CTRL_BMC_CRG_BMC17_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_104C    crg_bmc18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sync_update_adto4         :  1,    //      0
    sync_update_adto3         :  1,    //      1
    sync_update_adto2         :  1,    //      2
    sync_update_adto1         :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_BMC_CRG_BMC18_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1050    crg_bmc19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sel_diseqc_cmd            :  3,    //   2: 0
    sel_fefctrl               :  3,    //   5: 3
    sel_diseqc                :  3,    //   8: 6
    sel_ifagc_s               :  3,    //  11: 9
    sel_ifagc                 :  3,    //  14:12
                              :  1,    //     15 reserved
    sel_rc                    :  1,    //     16
    sel_vdac                  :  1,    //     17
    sel_cvbs                  :  1,    //     18
    sel_sif                   :  1,    //     19
    sel_aad                   :  1,    //     20
    sel_gpo                   :  1,    //     21
                              :  1,    //     22 reserved
    sel_abb_i2c_sel           :  2,    //  24:23
    sel_dbb_i2c_sel           :  1,    //     25
                              :  6;    //  31:26 reserved
}BND_CTRL_BMC_CRG_BMC19_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1054    crg_bmc20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dbb_opermode              :  8,    //   7: 0
    dbb_reset                 :  1,    //      8
    abb_reset                 :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_BMC_CRG_BMC20_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_1058    crg_bmc21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_earc_add_value_pos: 17,    //  16:0
                              : 15;    //  31:17 reserved
}BND_CTRL_BMC_CRG_BMC21_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FC_105C    crg_bmc22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto4_earc_add_value_neg: 17,    //  16:0
                              : 15;    //  31:17 reserved
}BND_CTRL_BMC_CRG_BMC22_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_BMC_CRG_BMC00_O18_A0                crg_bmc00                ;         // 0xC7FC_1000
BND_CTRL_BMC_CRG_BMC01_O18_A0                crg_bmc01                ;         // 0xC7FC_1004
BND_CTRL_BMC_CRG_BMC02_O18_A0                crg_bmc02                ;         // 0xC7FC_1008
BND_CTRL_BMC_CRG_BMC03_O18_A0                crg_bmc03                ;         // 0xC7FC_100C
BND_CTRL_BMC_CRG_BMC04_O18_A0                crg_bmc04                ;         // 0xC7FC_1010
BND_CTRL_BMC_CRG_BMC05_O18_A0                crg_bmc05                ;         // 0xC7FC_1014
UINT32                                                 _rsvd_00[   1] ;         // 0xC7FC_1018
BND_CTRL_BMC_CRG_BMC06_O18_A0                crg_bmc06                ;         // 0xC7FC_101C
BND_CTRL_BMC_CRG_BMC07_O18_A0                crg_bmc07                ;         // 0xC7FC_1020
BND_CTRL_BMC_CRG_BMC08_O18_A0                crg_bmc08                ;         // 0xC7FC_1024
BND_CTRL_BMC_CRG_BMC09_O18_A0                crg_bmc09                ;         // 0xC7FC_1028
BND_CTRL_BMC_CRG_BMC10_O18_A0                crg_bmc10                ;         // 0xC7FC_102C
UINT32                                                 _rsvd_01[   2] ;         // 0xC7FC_1030 ~ 0xC7FC_1034
BND_CTRL_BMC_CRG_BMC13_O18_A0                crg_bmc13                ;         // 0xC7FC_1038
BND_CTRL_BMC_CRG_BMC14_O18_A0                crg_bmc14                ;         // 0xC7FC_103C
BND_CTRL_BMC_CRG_BMC15_O18_A0                crg_bmc15                ;         // 0xC7FC_1040
BND_CTRL_BMC_CRG_BMC16_O18_A0                crg_bmc16                ;         // 0xC7FC_1044
BND_CTRL_BMC_CRG_BMC17_O18_A0                crg_bmc17                ;         // 0xC7FC_1048
BND_CTRL_BMC_CRG_BMC18_O18_A0                crg_bmc18                ;         // 0xC7FC_104C
BND_CTRL_BMC_CRG_BMC19_O18_A0                crg_bmc19                ;         // 0xC7FC_1050
BND_CTRL_BMC_CRG_BMC20_O18_A0                crg_bmc20                ;         // 0xC7FC_1054
BND_CTRL_BMC_CRG_BMC21_O18_A0                crg_bmc21                ;         // 0xC7FC_1058
BND_CTRL_BMC_CRG_BMC22_O18_A0                crg_bmc22                ;         // 0xC7FC_105C
} BND_CTRL_BMC_REG_O18_A0;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_BMC_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

