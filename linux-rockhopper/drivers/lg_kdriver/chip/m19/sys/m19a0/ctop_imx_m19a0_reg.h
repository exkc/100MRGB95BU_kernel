#ifndef _CTOP_IMX_M19A0_REG_H_
#define _CTOP_IMX_M19A0_REG_H_

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
    0xC930_3C00    ctop_imx_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_0_por                :  1,    //      0
    usb2_1_por                :  1,    //      1
    usb2_2_por                :  1,    //      2
                              : 28,    //  30: 3 reserved
    regmod_usb2scan           :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C04    ctop_imx_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_0_wordinterface0     :  1,    //      0
                              :  1,    //      1 reserved
    usb2_0_fsel               :  3,    //   4: 2
    usb2_0_txrestune0         :  2,    //   6: 5
    usb2_0_txhsxvtune0        :  2,    //   8: 7
    usb2_0_txvreftune0        :  4,    //  12: 9
    usb2_0_txrisetune0        :  2,    //  14:13
    usb2_0_txpreemppulsetune0 :  1,    //     15
    usb2_0_txpreempamptune0   :  2,    //  17:16
    usb2_0_txfslstune0        :  4,    //  21:18
    usb2_0_sqrxtune0          :  3,    //  24:22
    usb2_0_compdistune0       :  3,    //  27:25
    usb2_0_commononn          :  1,    //     28
    usb2_0_refclksel          :  2,    //  30:29
    usb2_0_portreset0         :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C08    ctop_imx_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_0_bypasssel0         :  1,    //      0
    usb2_0_bypassdmen0        :  1,    //      1
    usb2_0_bypassdpen0        :  1,    //      2
    usb2_0_bypassdmdata0      :  1,    //      3
    usb2_0_bypassdpdata0      :  1,    //      4
    usb2_0_otgdisable0        :  1,    //      5
    usb2_0_vatestenb          :  2,    //   7: 6
    usb2_0_loopbackenb0       :  1,    //      8
    usb2_0_siddq              :  1,    //      9
    usb2_0_testclk0           :  1,    //     10
                              :  1,    //     11 reserved
    usb2_0_testdataout0       :  4,    //  15:12
    usb2_0_testdatain0        :  8,    //  23:16
    usb2_0_testaddr0          :  4,    //  27:24
    usb2_0_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_0_atereset           :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C0C    ctop_imx_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_1_wordinterface0     :  1,    //      0
                              :  1,    //      1 reserved
    usb2_1_fsel               :  3,    //   4: 2
    usb2_1_txrestune0         :  2,    //   6: 5
    usb2_1_txhsxvtune0        :  2,    //   8: 7
    usb2_1_txvreftune0        :  4,    //  12: 9
    usb2_1_txrisetune0        :  2,    //  14:13
    usb2_1_txpreemppulsetune0 :  1,    //     15
    usb2_1_txpreempamptune0   :  2,    //  17:16
    usb2_1_txfslstune0        :  4,    //  21:18
    usb2_1_sqrxtune0          :  3,    //  24:22
    usb2_1_compdistune0       :  3,    //  27:25
    usb2_1_commononn          :  1,    //     28
    usb2_1_refclksel          :  2,    //  30:29
    usb2_1_portreset0         :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C10    ctop_imx_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_1_bypasssel0         :  1,    //      0
    usb2_1_bypassdmen0        :  1,    //      1
    usb2_1_bypassdpen0        :  1,    //      2
    usb2_1_bypassdmdata0      :  1,    //      3
    usb2_1_bypassdpdata0      :  1,    //      4
    usb2_1_otgdisable0        :  1,    //      5
    usb2_1_vatestenb          :  2,    //   7: 6
    usb2_1_loopbackenb0       :  1,    //      8
    usb2_1_siddq              :  1,    //      9
    usb2_1_testclk0           :  1,    //     10
                              :  1,    //     11 reserved
    usb2_1_testdataout0       :  4,    //  15:12
    usb2_1_testdatain0        :  8,    //  23:16
    usb2_1_testaddr0          :  4,    //  27:24
    usb2_1_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_1_atereset           :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C14    ctop_imx_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_2_wordinterface0     :  1,    //      0
                              :  1,    //      1 reserved
    usb2_2_fsel               :  3,    //   4: 2
    usb2_2_txrestune0         :  2,    //   6: 5
    usb2_2_txhsxvtune0        :  2,    //   8: 7
    usb2_2_txvreftune0        :  4,    //  12: 9
    usb2_2_txrisetune0        :  2,    //  14:13
    usb2_2_txpreemppulsetune0 :  1,    //     15
    usb2_2_txpreempamptune0   :  2,    //  17:16
    usb2_2_txfslstune0        :  4,    //  21:18
    usb2_2_sqrxtune0          :  3,    //  24:22
    usb2_2_compdistune0       :  3,    //  27:25
    usb2_2_commononn          :  1,    //     28
    usb2_2_refclksel          :  2,    //  30:29
    usb2_2_portreset0         :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_3C18    ctop_imx_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_2_bypasssel0         :  1,    //      0
    usb2_2_bypassdmen0        :  1,    //      1
    usb2_2_bypassdpen0        :  1,    //      2
    usb2_2_bypassdmdata0      :  1,    //      3
    usb2_2_bypassdpdata0      :  1,    //      4
    usb2_2_otgdisable0        :  1,    //      5
    usb2_2_vatestenb          :  2,    //   7: 6
    usb2_2_loopbackenb0       :  1,    //      8
    usb2_2_siddq              :  1,    //      9
    usb2_2_testclk0           :  1,    //     10
                              :  1,    //     11 reserved
    usb2_2_testdataout0       :  4,    //  15:12
    usb2_2_testdatain0        :  8,    //  23:16
    usb2_2_testaddr0          :  4,    //  27:24
    usb2_2_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_2_atereset           :  1;    //     31
}CTOP_CTRL_IMX_CTOP_IMX_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_IMX_CTOP_IMX_R00_M19A0_T           ctop_imx_r00             ;         // 0xC930_3C00
CTOP_CTRL_IMX_CTOP_IMX_R01_M19A0_T           ctop_imx_r01             ;         // 0xC930_3C04
CTOP_CTRL_IMX_CTOP_IMX_R02_M19A0_T           ctop_imx_r02             ;         // 0xC930_3C08
CTOP_CTRL_IMX_CTOP_IMX_R03_M19A0_T           ctop_imx_r03             ;         // 0xC930_3C0C
CTOP_CTRL_IMX_CTOP_IMX_R04_M19A0_T           ctop_imx_r04             ;         // 0xC930_3C10
CTOP_CTRL_IMX_CTOP_IMX_R05_M19A0_T           ctop_imx_r05             ;         // 0xC930_3C14
CTOP_CTRL_IMX_CTOP_IMX_R06_M19A0_T           ctop_imx_r06             ;         // 0xC930_3C18
} CTOP_CTRL_IMX_REG_M19A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_IMX_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

