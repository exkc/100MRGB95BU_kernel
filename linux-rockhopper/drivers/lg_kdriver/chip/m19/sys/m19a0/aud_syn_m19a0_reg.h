#ifndef _AUD_SYN_M19A0_REG_H_
#define _AUD_SYN_M19A0_REG_H_

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
    0xC9C6_0000    crg_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_hmr3spdifclk_gate_en  :  1,    //      0
    aud_hmr2spdifclk_gate_en  :  1,    //      1
    aud_hmr1spdifclk_gate_en  :  1,    //      2
    aud_hmr0spdifclk_gate_en  :  1,    //      3
    aad_i2s_sclk_gate_en      :  1,    //      4
    aud_fs00clk_gate_en       :  1,    //      5
    aud_fs26clk_gate_en       :  1,    //      6
    aud_fs25clk_gate_en       :  1,    //      7
    aud_fs24clk_gate_en       :  1,    //      8
    aud_fs23clk_gate_en       :  1,    //      9
    aud_fs22clk_gate_en       :  1,    //     10
    aud_fs21clk_gate_en       :  1,    //     11
    aud_fs20clk_gate_en       :  1,    //     12
    aud_teclk_gate_en         :  1,    //     13
    aud_aclk_gate_en          :  1,    //     14
    aud_apb_clk_gate_en       :  1,    //     15
                              :  1,    //     16 reserved
    tsadc_clk_gate_en         :  1,    //     17
    ts_clk_gate_en            :  1,    //     18
    de_soc_clk_gate_en        :  1,    //     19
                              : 12;    //  31:20 reserved
}AUD_SYN_CRG_AUD00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0004    crg_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_fs26clk_sel           :  1,    //      0
                              :  7,    //   7: 1 reserved
    i_aud_hmr3spdifclk_inv_sel:  1,    //      8
    i_aud_hmr2spdifclk_inv_sel:  1,    //      9
    i_aud_hmr1spdifclk_inv_sel:  1,    //     10
    i_aud_hmr0spdifclk_inv_sel:  1,    //     11
    i_fs00_clk_inv_sel        :  1,    //     12
    i_aud_fs26clk_inv_sel     :  1,    //     13
    i_aud_fs25clk_inv_sel     :  1,    //     14
    i_aud_fs24clk_inv_sel     :  1,    //     15
    i_aud_dto_clk_inv_sel     :  1,    //     16
    i_aud_fs23clk_inv_sel     :  1,    //     17
    i_aud_fs22clk_inv_sel     :  1,    //     18
    i_aud_fs21clk_inv_sel     :  1,    //     19
    i_aud_fs20clk_inv_sel     :  1,    //     20
    earc_dto_in_clk_sel       :  1,    //     21
    result_0_inv_sel          :  1,    //     22
                              :  5,    //  27:23 reserved
    core480_clk_sel           :  2,    //  29:28
    core396_clk_sel           :  2;    //  31:30
}AUD_SYN_CRG_AUD01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0008    syn_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    soft_rst_auda_n           :  1,    //      1
    soft_rst_apb_n            :  1,    //      2
    soft_rst_ts_n             :  1,    //      3
    soft_rst_earc_dto         :  1,    //      4
    soft_rst_de_soc_n         :  1,    //      5
    soft_rst_aud_axi_bnd_n    :  1,    //      6
                              : 25;    //   31:7 reserved
}AUD_SYN_SYN_AUD00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_000C    syn_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tpi0_clk_bypass           :  1,    //      0
    tpi1_clk_bypass           :  1,    //      1
    tpi2_clk_bypass           :  1,    //      2
    tpi3_clk_bypass           :  1,    //      3
    stpi0_clk_bypass          :  1,    //      4
    tpi0_clk_flt_sel          :  2,    //   6: 5
    tpi1_clk_flt_sel          :  2,    //   8: 7
    tpi2_clk_flt_sel          :  2,    //  10: 9
    tpi3_clk_flt_sel          :  2,    //  12:11
    stpi0_clk_flt_sel         :  2,    //  14:13
                              : 17;    //  31:15 reserved
}AUD_SYN_SYN_AUD01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0010    syn_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    icod_w_bus_ag             :  1,    //      0
    icod_ar_bus_ag            :  1,    //      1
    te_w_bus_ag               :  1,    //      2
    te_ar_bus_ag              :  1,    //      3
    icod_s_awcache            :  1,    //      4
    icod_s_arcache            :  1,    //      5
    te_s_awcache              :  1,    //      6
    te_s_arcache              :  1,    //      7
    swrst_gstcc_tx1           :  1,    //      8
    swrst_gstcc_tx0           :  1,    //      9
    swrst_pes_tx1             :  1,    //     10
    swrst_pes_tx0             :  1,    //     11
    swrst_aud_gnrm            :  1,    //     12
    swrst_gnrm_tx0            :  1,    //     13
    icod_flush_en             :  1,    //     14
    te_flush_en               :  1,    //     15
    icod_w_vio                :  1,    //     16
    icod_aw_vio               :  1,    //     17
    icod_ar_vio               :  1,    //     18
    te_w_vio                  :  1,    //     19
    te_aw_vio                 :  1,    //     20
    te_ar_vio                 :  1,    //     21
    icod_flush_done           :  1,    //     22
    te_flush_done             :  1,    //     23
    aud_te_ipc_pchkerr        :  1,    //     24
    isol_pchkerr              :  1,    //     25
    gnrs_swrst                :  1,    //     26
    swrst_gnr_rx0             :  1,    //     27
                              :  4;    //  31:28 reserved
}AUD_SYN_SYN_AUD02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0014    syn_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_earc_en               :  1,    //      0
                              :  3,    //   3: 1 reserved
    aud_earc_clk_sel          :  1,    //      4
                              : 27;    //   31:5 reserved
}AUD_SYN_SYN_AUD03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0018    syn_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    earc_add_value_pos        : 17,    //  16: 0
                              : 15;    //  31:17 reserved
}AUD_SYN_SYN_AUD04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_001C    syn_aud05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    earc_add_value_neg        : 17,    //  16: 0
                              : 15;    //  31:17 reserved
}AUD_SYN_SYN_AUD05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0020    syn_aud06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sync_update_earc_dto      :  1,    //      0
                              : 31;    //   31:1 reserved
}AUD_SYN_SYN_AUD06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0024    a_crg_check_aud_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk0_value            : 16,    //  15: 0
    aud_rst0_check            :  1,    //     16
    aud_clk0_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk0_off_value        :  8,    //  27:20
    aud_clk0_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk0_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0028    a_crg_check_aud_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk1_value            : 16,    //  15: 0
    aud_rst1_check            :  1,    //     16
    aud_clk1_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk1_off_value        :  8,    //  27:20
    aud_clk1_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk1_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_002C    a_crg_check_aud_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk2_value            : 16,    //  15: 0
    aud_rst2_check            :  1,    //     16
    aud_clk2_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk2_off_value        :  8,    //  27:20
    aud_clk2_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk2_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0030    a_crg_check_aud_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk3_value            : 16,    //  15: 0
    aud_rst3_check            :  1,    //     16
    aud_clk3_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk3_off_value        :  8,    //  27:20
    aud_clk3_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk3_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0034    a_crg_check_aud_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk4_value            : 16,    //  15: 0
    aud_rst4_check            :  1,    //     16
    aud_clk4_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk4_off_value        :  8,    //  27:20
    aud_clk4_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk4_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0038    a_crg_check_aud_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    aud_clk5_value            : 16,    //  15: 0
    aud_rst5_check            :  1,    //     16
    aud_clk5_off_check        :  1,    //     17
                              :  2,    //  19:18 reserved
    aud_clk5_off_value        :  8,    //  27:20
    aud_clk5_sel              :  2,    //  29:28
                              :  1,    //     30 reserved
    aud_clk5_gate             :  1;    //     31
}AUD_SYN_A_CRG_CHECK_AUD_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_003C    syn_aud07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_aud        :  1,    //      0
    reg_ls_disable_te         :  1,    //      1
    reg_ls_disable_icod       :  1,    //      2
                              : 29;    //   31:3 reserved
}AUD_SYN_SYN_AUD07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    aud_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
AUD_SYN_CRG_AUD00_M19A0_T                    crg_aud00                ;         // 0xC9C6_0000
AUD_SYN_CRG_AUD01_M19A0_T                    crg_aud01                ;         // 0xC9C6_0004
AUD_SYN_SYN_AUD00_M19A0_T                    syn_aud00                ;         // 0xC9C6_0008
AUD_SYN_SYN_AUD01_M19A0_T                    syn_aud01                ;         // 0xC9C6_000C
AUD_SYN_SYN_AUD02_M19A0_T                    syn_aud02                ;         // 0xC9C6_0010
AUD_SYN_SYN_AUD03_M19A0_T                    syn_aud03                ;         // 0xC9C6_0014
AUD_SYN_SYN_AUD04_M19A0_T                    syn_aud04                ;         // 0xC9C6_0018
AUD_SYN_SYN_AUD05_M19A0_T                    syn_aud05                ;         // 0xC9C6_001C
AUD_SYN_SYN_AUD06_M19A0_T                    syn_aud06                ;         // 0xC9C6_0020
AUD_SYN_A_CRG_CHECK_AUD_0_M19A0_T            a_crg_check_aud_0        ;         // 0xC9C6_0024
AUD_SYN_A_CRG_CHECK_AUD_1_M19A0_T            a_crg_check_aud_1        ;         // 0xC9C6_0028
AUD_SYN_A_CRG_CHECK_AUD_2_M19A0_T            a_crg_check_aud_2        ;         // 0xC9C6_002C
AUD_SYN_A_CRG_CHECK_AUD_3_M19A0_T            a_crg_check_aud_3        ;         // 0xC9C6_0030
AUD_SYN_A_CRG_CHECK_AUD_4_M19A0_T            a_crg_check_aud_4        ;         // 0xC9C6_0034
AUD_SYN_A_CRG_CHECK_AUD_5_M19A0_T            a_crg_check_aud_5        ;         // 0xC9C6_0038
AUD_SYN_SYN_AUD07_M19A0_T                    syn_aud07                ;         // 0xC9C6_003C
} AUD_SYN_REG_M19A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _AUD_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

