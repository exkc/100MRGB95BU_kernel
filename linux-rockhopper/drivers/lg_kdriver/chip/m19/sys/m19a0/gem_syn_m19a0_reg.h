#ifndef _GEM_SYN_M19A0_REG_H_
#define _GEM_SYN_M19A0_REG_H_

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
    0xC350_1000    crg_gem00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    apb_bnd_clk_gate_en       :  1,    //      0
    gem_rmii_ref_clk_gate_en  :  1,    //      1
    gem_rgmii_tx_n_clk_gate_en:  1,    //      2
    gem_rgmii_rx_n_clk_gate_en:  1,    //      3
    gem_rx_clk_gate_en        :  1,    //      4
    gem_tx_clk_gate_en        :  1,    //      5
    gem_pclk_gate_en          :  1,    //      6
    gem_aclk_gate_en          :  1,    //      7
                              : 24;    //   31:8 reserved
}GEM_SYN_CRG_GEM00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1004    crg_gem01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 30,    //  29: 0 reserved
    core396_clk_sel           :  2;    //  31:30
}GEM_SYN_CRG_GEM01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1008    crg_gem02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rmii_rx_clk_inv_sel       :  1,    //      0
    rmii_tx_clk_inv_sel       :  1,    //      1
    ephy_rx_clk_inv_sel       :  1,    //      2
    ephy_tx_clk_inv_sel       :  1,    //      3
    i_rgmii_rx_clk_inv_sel    :  1,    //      4
    i_rmii_ref_clk_inv_sel    :  1,    //      5
    i_ext_rmii_ref_clk_inv_sel:  1,    //      6
                              : 25;    //   31:7 reserved
}GEM_SYN_CRG_GEM02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_100C    syn_gem00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_axi_bnd_n        :  1,    //      0
    soft_ephy_reset_n         :  1,    //      1
    soft_gem_rmii_ref_reset_n :  1,    //      2
    soft_gem_rgmii_tx_n_reset_n: 1,    //      3
    soft_gem_rgmii_txreset_n  :  1,    //      4
    soft_gem_rgmii_rx_n_reset_n: 1,    //      5
    soft_gem_rgmii_rxreset_n  :  1,    //      6
    soft_gem_rxreset_n        :  1,    //      7
    soft_gem_txreset_n        :  1,    //      8
    soft_ctrl_preset_n        :  1,    //      9
    soft_gem_apreset_n        :  1,    //     10
    soft_gem_areset_n         :  1,    //     11
    soft_ephy_ctrl_preset_n   :  1,    //     12
                              : 19;    //  31:13 reserved
}GEM_SYN_SYN_GEM00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1010    syn_gem01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}GEM_SYN_SYN_GEM01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1014    syn_gem02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}GEM_SYN_SYN_GEM02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1018    a_crg_check_gem_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gem_clk0_value            : 16,    //  15: 0
    gem_rst0_check            :  1,    //     16
    gem_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gem_clk0_off_value        :  8,    //  27:20
    gem_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gem_clk0_gate             :  1;    //     31
}GEM_SYN_A_CRG_CHECK_GEM_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_101C    a_crg_check_gem_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gem_clk1_value            : 16,    //  15: 0
    gem_rst1_check            :  1,    //     16
    gem_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gem_clk1_off_value        :  8,    //  27:20
    gem_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gem_clk1_gate             :  1;    //     31
}GEM_SYN_A_CRG_CHECK_GEM_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1020    a_crg_check_gem_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gem_clk2_value            : 16,    //  15: 0
    gem_rst2_check            :  1,    //     16
    gem_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gem_clk2_off_value        :  8,    //  27:20
    gem_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gem_clk2_gate             :  1;    //     31
}GEM_SYN_A_CRG_CHECK_GEM_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1024    a_crg_check_gem_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gem_clk3_value            : 16,    //  15: 0
    gem_rst3_check            :  1,    //     16
    gem_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gem_clk3_off_value        :  8,    //  27:20
    gem_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gem_clk3_gate             :  1;    //     31
}GEM_SYN_A_CRG_CHECK_GEM_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1028    a_crg_check_gem_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gem_clk4_value            : 16,    //  15: 0
    gem_rst4_check            :  1,    //     16
    gem_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    gem_clk4_off_value        :  8,    //  27:20
    gem_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    gem_clk4_gate             :  1;    //     31
}GEM_SYN_A_CRG_CHECK_GEM_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_102C    syn_gem03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}GEM_SYN_SYN_GEM03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC350_1030    syn_gem04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rmii_ref_clk__pd  :  1,    //      0
    reg_pad_rmii_mdio__pd     :  1,    //      1
    reg_pad_rmii_mdc__pd      :  1,    //      2
    reg_pad_rmii_txd0__pd     :  1,    //      3
    reg_pad_rmii_txd1__pd     :  1,    //      4
    reg_pad_rmii_txen__pd     :  1,    //      5
    reg_pad_rmii_rxd0__pd     :  1,    //      6
    reg_pad_rmii_rxd1__pd     :  1,    //      7
    reg_pad_rmii_crs_dv__pd   :  1,    //      8
                              : 23;    //   31:9 reserved
}GEM_SYN_SYN_GEM04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    gem_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
GEM_SYN_CRG_GEM00_M19A0_T                    crg_gem00                ;         // 0xC350_1000
GEM_SYN_CRG_GEM01_M19A0_T                    crg_gem01                ;         // 0xC350_1004
GEM_SYN_CRG_GEM02_M19A0_T                    crg_gem02                ;         // 0xC350_1008
GEM_SYN_SYN_GEM00_M19A0_T                    syn_gem00                ;         // 0xC350_100C
GEM_SYN_SYN_GEM01_M19A0_T                    syn_gem01                ;         // 0xC350_1010
GEM_SYN_SYN_GEM02_M19A0_T                    syn_gem02                ;         // 0xC350_1014
GEM_SYN_A_CRG_CHECK_GEM_0_M19A0_T            a_crg_check_gem_0        ;         // 0xC350_1018
GEM_SYN_A_CRG_CHECK_GEM_1_M19A0_T            a_crg_check_gem_1        ;         // 0xC350_101C
GEM_SYN_A_CRG_CHECK_GEM_2_M19A0_T            a_crg_check_gem_2        ;         // 0xC350_1020
GEM_SYN_A_CRG_CHECK_GEM_3_M19A0_T            a_crg_check_gem_3        ;         // 0xC350_1024
GEM_SYN_A_CRG_CHECK_GEM_4_M19A0_T            a_crg_check_gem_4        ;         // 0xC350_1028
GEM_SYN_SYN_GEM03_M19A0_T                    syn_gem03                ;         // 0xC350_102C
GEM_SYN_SYN_GEM04_M19A0_T                    syn_gem04                ;         // 0xC350_1030
} GEM_SYN_REG_M19A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _GEM_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

