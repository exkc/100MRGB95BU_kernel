#ifndef _CTOP_EDID_M19A0_REG_H_
#define _CTOP_EDID_M19A0_REG_H_

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
    0xC36C_8000    ctop_edid0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_edid_bnd            :  1,    //      0
    reg_ls_disable            :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_EDID_CTOP_EDID0_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC36C_807C    ctop_edid0_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    edid_prt3_hpd_out         :  1,    //      0
    edid_prt2_hpd_out         :  1,    //      1
    edid_prt1_hpd_out         :  1,    //      2
    edid_prt0_hpd_out         :  1,    //      3
    i_link_phy3_cbus_hpd_out  :  1,    //      4
    i_link_phy2_cbus_hpd_out  :  1,    //      5
    i_link_phy1_cbus_hpd_out  :  1,    //      6
    i_link_phy0_cbus_hpd_out  :  1,    //      7
    reg_edid_wr_done          :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_EDID_CTOP_EDID0_R31_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_EDID_CTOP_EDID0_R00_M19A0_T             ctop_edid0_r00           ;         // 0xC36C_8000
UINT32                                                 _rsvd_00[  30] ;         // 0xC36C_8004 ~ 0xC36C_8078
CTOP_EDID_CTOP_EDID0_R31_M19A0_T             ctop_edid0_r31           ;         // 0xC36C_807C
} CTOP_EDID_REG_M19A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_EDID_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

