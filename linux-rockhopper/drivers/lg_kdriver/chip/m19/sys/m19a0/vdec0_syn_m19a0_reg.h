#ifndef _VDEC0_SYN_M19A0_REG_H_
#define _VDEC0_SYN_M19A0_REG_H_

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
    0xC9C7_0200    crg_vdec000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_msvc_clk_gate_en       :  1,    //      0
    vd_msvc_396_clk_gate_en   :  1,    //      1
    vd_mem_clk_gate_en        :  1,    //      2
    vd_mcu_clk_gate_en        :  1,    //      3
    vd_hevc_clk_gate_en       :  1,    //      4
    vd_axi0_clk_gate_en       :  1,    //      5
    vd_axi1_clk_gate_en       :  1,    //      6
    vd_axi2_clk_gate_en       :  1,    //      7
    teclk_gate_en             :  1,    //      8
    sysclk0_gate_en           :  1,    //      9
    sysclk1_gate_en           :  1,    //     10
    sysclk2_gate_en           :  1,    //     11
    sysclk3_gate_en           :  1,    //     12
    sysclk4_gate_en           :  1,    //     13
    sysclk5_gate_en           :  1,    //     14
    de_soc_clk_gate_en        :  1,    //     15
    axi_soc_clk_gate_en       :  1,    //     16
    apb_clk_gate_en           :  1,    //     17
    vd_mcu_bnd_clk_gate_en    :  1,    //     18
    vd_hevc_ed_clk_gate_en    :  1,    //     19
    vd_hevc_lcu_clk_gate_en   :  1,    //     20
                              : 11;    //  31:21 reserved
}VDEC0_SYN_CRG_VDEC000_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0204    crg_vdec001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_mem_clk_sel            :  2,    //   1: 0
    msvc_clk_sel              :  1,    //      2
    hevc_clk_sel              :  1,    //      3
    sysclk0_sel               :  1,    //      4
    sysclk1_sel               :  1,    //      5
    sysclk2_sel               :  1,    //      6
    sysclk3_sel               :  1,    //      7
    sysclk4_sel               :  1,    //      8
    sysclk5_sel               :  1,    //      9
                              : 16,    //  25:10 reserved
    core528_clk_sel           :  2,    //  27:26
    core480_clk_sel           :  2,    //  29:28
    core396_clk_sel           :  2;    //  31:30
}VDEC0_SYN_CRG_VDEC001_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0208    crg_vdec002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_27m_clk_inv_sel         :  1,    //      0
    i_sdco27_clk_inv_sel      :  1,    //      1
                              : 30;    //   31:2 reserved
}VDEC0_SYN_CRG_VDEC002_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_020C    crg_vdec003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    soft_rst_vda0_n           :  1,    //      0
    soft_rst_vda1_n           :  1,    //      1
    soft_rst_vda2_n           :  1,    //      2
    soft_rst_vd_n             :  1,    //      3
    soft_rst_te_n             :  1,    //      4
    soft_rst_mem_n            :  1,    //      5
    soft_rst_mcu_n            :  1,    //      6
    soft_rst_hevc_n           :  1,    //      7
    soft_rst_apb_n            :  1,    //      8
    soft_rst_sys0_n           :  1,    //      9
    soft_rst_sys1_n           :  1,    //     10
    soft_rst_sys2_n           :  1,    //     11
    soft_rst_sys3_n           :  1,    //     12
    soft_rst_sys4_n           :  1,    //     13
    soft_rst_sys5_n           :  1,    //     14
    soft_rst_axi_soc_n        :  1,    //     15
    soft_rst_axi_bnd_n        :  1,    //     16
    soft_rst_de_soc_n         :  1,    //     17
    soft_rst_hevc_bnd_n       :  1,    //     18
    soft_rst_te_bnd_n         :  1,    //     19
    soft_rst_mcu_bnd_n        :  1,    //     20
    soft_rst_hevc_lcu_n       :  1,    //     21
    soft_rst_hevc_ed_n        :  1,    //     22
                              :  9;    //  31:23 reserved
}VDEC0_SYN_CRG_VDEC003_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0228    syn_vdec000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrm_tx             :  1,    //      0
    vdec0_te_pchkerr          :  1,    //      1
                              : 30;    //   31:2 reserved
}VDEC0_SYN_SYN_VDEC000_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_022C    syn_vdec001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrs                :  1,    //      0
    swrst_te0                 :  1,    //      1
    swrst_te1                 :  1,    //      2
                              : 29;    //   31:3 reserved
}VDEC0_SYN_SYN_VDEC001_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0230    a_crg_check_vdec0_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk0_value          : 16,    //  15: 0
    vdec0_rst0_check          :  1,    //     16
    vdec0_clk0_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk0_off_value      :  8,    //  27:20
    vdec0_clk0_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk0_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_0_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0234    a_crg_check_vdec0_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk1_value          : 16,    //  15: 0
    vdec0_rst1_check          :  1,    //     16
    vdec0_clk1_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk1_off_value      :  8,    //  27:20
    vdec0_clk1_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk1_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_1_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0238    a_crg_check_vdec0_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk2_value          : 16,    //  15: 0
    vdec0_rst2_check          :  1,    //     16
    vdec0_clk2_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk2_off_value      :  8,    //  27:20
    vdec0_clk2_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk2_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_2_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_023C    a_crg_check_vdec0_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk3_value          : 16,    //  15: 0
    vdec0_rst3_check          :  1,    //     16
    vdec0_clk3_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk3_off_value      :  8,    //  27:20
    vdec0_clk3_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk3_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_3_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0240    a_crg_check_vdec0_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk4_value          : 16,    //  15: 0
    vdec0_rst4_check          :  1,    //     16
    vdec0_clk4_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk4_off_value      :  8,    //  27:20
    vdec0_clk4_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk4_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_4_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0244    a_crg_check_vdec0_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk5_value          : 16,    //  15: 0
    vdec0_rst5_check          :  1,    //     16
    vdec0_clk5_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk5_off_value      :  8,    //  27:20
    vdec0_clk5_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk5_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_5_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0248    a_crg_check_vdec0_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vdec0_clk6_value          : 16,    //  15: 0
    vdec0_rst6_check          :  1,    //     16
    vdec0_clk6_off_check      :  1,    //     17
                              :  2,    //  19:18 reserved
    vdec0_clk6_off_value      :  8,    //  27:20
    vdec0_clk6_sel            :  2,    //  29:28
                              :  1,    //     30 reserved
    vdec0_clk6_gate           :  1;    //     31
}VDEC0_SYN_A_CRG_CHECK_VDEC0_6_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_024C    syn_vdec002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 32;    //  31: 0
}VDEC0_SYN_SYN_VDEC002_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0250    syn_vdec003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 32;    //  31: 0
}VDEC0_SYN_SYN_VDEC003_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0254    syn_vdec004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable            :  1,    //      0
                              : 31;    //   31:1 reserved
}VDEC0_SYN_SYN_VDEC004_M19A0_T;

/*-----------------------------------------------------------------------------------------
    vdec0_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
VDEC0_SYN_CRG_VDEC000_M19A0_T                crg_vdec000              ;         // 0xC9C7_0200
VDEC0_SYN_CRG_VDEC001_M19A0_T                crg_vdec001              ;         // 0xC9C7_0204
VDEC0_SYN_CRG_VDEC002_M19A0_T                crg_vdec002              ;         // 0xC9C7_0208
VDEC0_SYN_CRG_VDEC003_M19A0_T                crg_vdec003              ;         // 0xC9C7_020C
UINT32                                                 _rsvd_00[   6] ;         // 0xC9C7_0210 ~ 0xC9C7_0224
VDEC0_SYN_SYN_VDEC000_M19A0_T                syn_vdec000              ;         // 0xC9C7_0228
VDEC0_SYN_SYN_VDEC001_M19A0_T                syn_vdec001              ;         // 0xC9C7_022C
VDEC0_SYN_A_CRG_CHECK_VDEC0_0_M19A0_T        a_crg_check_vdec0_0      ;         // 0xC9C7_0230
VDEC0_SYN_A_CRG_CHECK_VDEC0_1_M19A0_T        a_crg_check_vdec0_1      ;         // 0xC9C7_0234
VDEC0_SYN_A_CRG_CHECK_VDEC0_2_M19A0_T        a_crg_check_vdec0_2      ;         // 0xC9C7_0238
VDEC0_SYN_A_CRG_CHECK_VDEC0_3_M19A0_T        a_crg_check_vdec0_3      ;         // 0xC9C7_023C
VDEC0_SYN_A_CRG_CHECK_VDEC0_4_M19A0_T        a_crg_check_vdec0_4      ;         // 0xC9C7_0240
VDEC0_SYN_A_CRG_CHECK_VDEC0_5_M19A0_T        a_crg_check_vdec0_5      ;         // 0xC9C7_0244
VDEC0_SYN_A_CRG_CHECK_VDEC0_6_M19A0_T        a_crg_check_vdec0_6      ;         // 0xC9C7_0248
VDEC0_SYN_SYN_VDEC002_M19A0_T                syn_vdec002              ;         // 0xC9C7_024C
VDEC0_SYN_SYN_VDEC003_M19A0_T                syn_vdec003              ;         // 0xC9C7_0250
VDEC0_SYN_SYN_VDEC004_M19A0_T                syn_vdec004              ;         // 0xC9C7_0254
} VDEC0_SYN_REG_M19A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _VDEC0_SYN_M19A0_REG_H_ */

/* from 'M16P3_CTOP_SYN_Register_Manual_110.xlsx'  2018.4.19  KST by LGSiCRDV V2.2A*/

