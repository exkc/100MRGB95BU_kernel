#ifndef _BND_CTRL_GEM_A0_REG_H_
#define _BND_CTRL_GEM_A0_REG_H_

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
    0xC750_1000    crg_gem00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pclk_gate_en              :  1,    //      0
    gem_aclk_gate_en          :  1,    //      1
    rx_clk_gate_en            :  1,    //      2
    rmii_ref_clk_gate_en      :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_GEM_CRG_GEM00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC750_1004    crg_gem01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_ephy                :  1,    //      0
    swrst_gem_rmii_ref        :  1,    //      1
    swrst_gem_rgmii_tx_n      :  1,    //      2
    swrst_gem_rgmii_tx        :  1,    //      3
    swrst_gem_rgmii_rx_n      :  1,    //      4
    swrst_gem_rgmii_rx        :  1,    //      5
    swrst_gem_rx              :  1,    //      6
    swrst_gem_tx              :  1,    //      7
    swrst_ctrl_preset         :  1,    //      8
    swrst_gem_preset          :  1,    //      9
    swrst_gem_areset          :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_GEM_CRG_GEM01_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_gem Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_GEM_CRG_GEM00_O18_A0                crg_gem00                ;         // 0xC750_1000
BND_CTRL_GEM_CRG_GEM01_O18_A0                crg_gem01                ;         // 0xC750_1004
} BND_CTRL_GEM_REG_O18_A0;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_GEM_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

