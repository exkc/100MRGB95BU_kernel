#ifndef _CTOP_SYN_VDEC0_SYN_A0_REG_H_
#define _CTOP_SYN_VDEC0_SYN_A0_REG_H_

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
    0xC9C7_0000    crg_vdec000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_msvc_clk_sel           :  1,    //      0
    vd_mem_clk_sel            :  1,    //      1
    vd_hevc_clk_sel           :  1,    //      2
    vd_axi0_clk_sel           :  1,    //      3
    vd_axi1_clk_sel           :  1,    //      4
    sysclk0_sel               :  1,    //      5
    sysclk1_sel               :  1,    //      6
    sysclk2_sel               :  1,    //      7
    sysclk3_sel               :  1,    //      8
    sysclk4_sel               :  1,    //      9
    sysclk5_sel               :  1,    //     10
    sdco27m_clk_inv_sel       :  1,    //     11
    fixed_27m_clk_inv_sel     :  1,    //     12
                              : 19;    //  31:13 reserved
}SYN_VDEC0_SYN_CRG_VDEC000_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0004    crg_vdec01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_msvc_clk_gate_en       :  1,    //      0
    vd_mem_clk_gate_en        :  1,    //      1
    vd_hevc_clk_gate_en       :  1,    //      2
    vd_axi0_clk_gate_en       :  1,    //      3
    vd_axi1_clk_gate_en       :  1,    //      4
    sysclk0_gate_en           :  1,    //      5
    sysclk1_gate_en           :  1,    //      6
    sysclk2_gate_en           :  1,    //      7
    sysclk3_gate_en           :  1,    //      8
    sysclk4_gate_en           :  1,    //      9
    sysclk5_gate_en           :  1,    //     10
    te_clk_gate_en            :  1,    //     11
    apb_clk_gate_en           :  1,    //     12
                              : 19;    //  31:13 reserved
}SYN_VDEC0_SYN_CRG_VDEC01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_000C    crg_vdec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_vd_msvc             :  1,    //      0
    swrst_vd_mem              :  1,    //      1
    swrst_vd_hevc             :  1,    //      2
    swrst_vd_axi0             :  1,    //      3
    swrst_vd_axi1             :  1,    //      4
    swrst_sysclk0             :  1,    //      5
    swrst_sysclk1             :  1,    //      6
    swrst_sysclk2             :  1,    //      7
    swrst_sysclk3             :  1,    //      8
    swrst_sysclk4             :  1,    //      9
    swrst_sysclk5             :  1,    //     10
    swrst_te                  :  1,    //     11
    swrst_apb                 :  1,    //     12
                              : 19;    //  31:13 reserved
}SYN_VDEC0_SYN_CRG_VDEC02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0010    syn_vdec00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}SYN_VDEC0_SYN_SYN_VDEC00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_0014    syn_vdec01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}SYN_VDEC0_SYN_SYN_VDEC01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    vdec0_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SYN_VDEC0_SYN_CRG_VDEC000_L18F_A0        crg_vdec000              ;         // 0xC9C7_0000
    SYN_VDEC0_SYN_CRG_VDEC01_L18F_A0         crg_vdec01               ;         // 0xC9C7_0004
UINT32                                                 _rsvd_00[   1] ;         // 0xC9C7_0008
    SYN_VDEC0_SYN_CRG_VDEC02_L18F_A0         crg_vdec02               ;         // 0xC9C7_000C
    SYN_VDEC0_SYN_SYN_VDEC00_L18F_A0         syn_vdec00               ;         // 0xC9C7_0010
    SYN_VDEC0_SYN_SYN_VDEC01_L18F_A0         syn_vdec01               ;         // 0xC9C7_0014
} SYN_VDEC0_SYN_REG_L18F_A0;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_VDEC0_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_SYN_Register_Manual_55.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

