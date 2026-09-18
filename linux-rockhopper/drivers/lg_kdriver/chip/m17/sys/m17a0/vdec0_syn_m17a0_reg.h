#ifndef _VDEC0_SYN_M17A0_REG_H_
#define _VDEC0_SYN_M17A0_REG_H_

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
    0xC9C7_01C0    crg_vdec000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_apbclk_gate_en         :  1,    //      0
    vd_mcu_clk_gate_en        :  1,    //      1
    vd_msvc_clk_gate_en       :  1,    //      2
    vd_axi0_clk_gate_en       :  1,    //      3
    vd_axi1_clk_gate_en       :  1,    //      4
    vd_mem_clk_gate_en        :  1,    //      5
    vd_hevc_clk_gate_en       :  1,    //      6
    te_clk_gate_en            :  1,    //      7
    sys_clk_gate_en           :  6,    //  13: 8
    axi_soc_clk_gate_en       :  1,    //     14
    de_soc_clk_gate_en        :  1,    //     15
    vd_axi2_clk_gate_en       :  1,    //     16
    vd_msvc_396_clk_gate_en   :  1,    //     17
                              :  2,    //  19:18 reserved
    vd_mem_clk_sel            :  2,    //  21:20
    sysclk_sel                :  6,    //  27:22
    vd_msvc_clk_sel           :  1,    //     28
    vd_hevc_clk_sel           :  1,    //     29
                              :  2;    //  31:30 reserved
}VDEC0_SYN_CRG_VDEC000_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_01C4    crg_vdec001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_apb                 :  1,    //      0
    swrst_mcu                 :  1,    //      1
    swrst_vd                  :  1,    //      2
    swrst_vda0                :  1,    //      3
    swrst_vda1                :  1,    //      4
    swrst_mem                 :  1,    //      5
    swrst_hevc                :  1,    //      6
    swrst_te                  :  1,    //      7
    swrst_sys                 :  6,    //  13: 8
    swrst_axi_soc             :  1,    //     14
    swrst_de_soc              :  1,    //     15
    swrst_vda2                :  1,    //     16
                              : 15;    //  31:17 reserved
}VDEC0_SYN_CRG_VDEC001_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_01C8    syn_vdec000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}VDEC0_SYN_SYN_VDEC000_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC9C7_01CC    syn_vdec001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}VDEC0_SYN_SYN_VDEC001_M17_A0;

/*-----------------------------------------------------------------------------------------
    vdec0_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
VDEC0_SYN_CRG_VDEC000_M17_A0                 crg_vdec000              ;         // 0xC9C7_01C0
VDEC0_SYN_CRG_VDEC001_M17_A0                 crg_vdec001              ;         // 0xC9C7_01C4
VDEC0_SYN_SYN_VDEC000_M17_A0                 syn_vdec000              ;         // 0xC9C7_01C8
VDEC0_SYN_SYN_VDEC001_M17_A0                 syn_vdec001              ;         // 0xC9C7_01CC
} VDEC0_SYN_REG_M17_A0;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _VDEC0_SYN_M17A0_REG_H_ */

/* from 'M16PP_CTOP_SYN_Register_Manual_52.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

