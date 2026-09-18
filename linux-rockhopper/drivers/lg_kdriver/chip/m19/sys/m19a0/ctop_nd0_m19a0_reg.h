#ifndef _CTOP_ND0_M19A0_REG_H_
#define _CTOP_ND0_M19A0_REG_H_

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
    0xC930_4C00    ctop_nd0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_stpi0_data4_pu        :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_stpi0_data5_pu        :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_stpi0_data6_pu        :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_stpi0_data7_pu        :  1,    //     15
                              :  7,    //  22:16 reserved
    reg_stpi0_val_pu          :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_stpi0_sop_pu          :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_stpi0_clk_pu          :  1;    //     31
}CTOP_CTRL_ND0_CTOP_ND0_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C04    ctop_nd0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    reg_tp_dvb_val_pu         :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_tp_dvb_sop_pu         :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_tp_dvb_clk_pu         :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_stpi0_data0_pu        :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_stpi0_data1_pu        :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_stpi0_data2_pu        :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_stpi0_data3_pu        :  1;    //     31
}CTOP_CTRL_ND0_CTOP_ND0_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C08    ctop_nd0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_tp_dvb_data0_pu       :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_tp_dvb_data1_pu       :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_tp_dvb_data2_pu       :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_tp_dvb_data3_pu       :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_tp_dvb_data4_pu       :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_tp_dvb_data5_pu       :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_tp_dvb_data6_pu       :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_tp_dvb_data7_pu       :  1;    //     31
}CTOP_CTRL_ND0_CTOP_ND0_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C0C    ctop_nd0_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_scl5__pd          :  1,    //      0
    reg_pad_scl5__pu          :  1,    //      1
    reg_pad_sda5__pd          :  1,    //      2
    reg_pad_sda5__pu          :  1,    //      3
    reg_pad_dolby_efuse_disable__pd: 1,    //  4
                              :  1,    //      5 reserved
    reg_pad_gpio95__pd        :  1,    //      6
    reg_pad_gpio94__pd        :  1,    //      7
                              : 15,    //  22: 8 reserved
    reg_pad_diseqc__pu        :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_pad_ifagc_s__pu       :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_pad_ifagc__pu         :  1;    //     31
}CTOP_CTRL_ND0_CTOP_ND0_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C10    ctop_nd0_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_use_cpu_gpio_12_0     :  1,    //      8
    reg_use_cpu_gpio_12_1     :  1,    //      9
    reg_use_cpu_gpio_12_2     :  1,    //     10
    reg_use_cpu_gpio_12_3     :  1,    //     11
    reg_use_cpu_gpio_12_4     :  1,    //     12
    reg_use_cpu_gpio_12_5     :  1,    //     13
    reg_use_cpu_gpio_12_6     :  1,    //     14
    reg_use_cpu_gpio_12_7     :  1,    //     15
                              :  5,    //  20:16 reserved
    reg_use_cpu_gpio_5_5      :  1,    //     21
    reg_use_cpu_gpio_5_6      :  1,    //     22
    reg_use_cpu_gpio_5_7      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_ND0_CTOP_ND0_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C14    ctop_nd0_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dvb_out_ctrl0         :  1,    //      0
    reg_dvb_out_ctrl1         :  1,    //      1
    reg_fsc_en                :  1,    //      2
    reg_stpi0_out_ctrl0       :  1,    //      3
    reg_stpi0_out_ctrl1       :  1,    //      4
                              :  8,    //  12: 5 reserved
    reg_use_cpu_gpio_13_0     :  1,    //     13
    reg_use_cpu_gpio_13_7     :  1,    //     14
    reg_use_cpu_gpio_16_0     :  1,    //     15
    reg_use_cpu_gpio_16_1     :  1,    //     16
    reg_use_cpu_gpio_5_0      :  1,    //     17
    reg_use_cpu_gpio_5_4      :  1,    //     18
                              :  3,    //  21:19 reserved
    reg_use_cpu_gpio_8_1      :  1,    //     22
    reg_use_cpu_gpio_8_2      :  1,    //     23
    reg_use_cpu_gpio_8_3      :  1,    //     24
    reg_use_cpu_gpio_8_4      :  1,    //     25
    reg_use_cpu_gpio_8_5      :  1,    //     26
    reg_use_cpu_gpio_8_6      :  1,    //     27
    reg_use_cpu_gpio_8_7      :  1,    //     28
    reg_use_cpu_gpio_9_0      :  1,    //     29
    reg_use_cpu_gpio_9_1      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_ND0_CTOP_ND0_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C18    ctop_nd0_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_use_diseqc_cmd_en1    :  1,    //      0
    reg_use_diseqc_cmd_en2    :  1,    //      1
    reg_use_diseqci_en1       :  1,    //      2
    reg_use_diseqci_en2       :  1,    //      3
    reg_use_fefctrl_en1       :  1,    //      4
    reg_use_fefctrl_en2       :  1,    //      5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_ND0_CTOP_ND0_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_4C1C    ctop_nd0_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_tpi_ext_demod2_sel    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tpi_ext_demod1_sel    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_tpi_int_demod_sel     :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CTOP_CTRL_ND0_CTOP_ND0_R07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_ND0_CTOP_ND0_R00_M19A0_T           ctop_nd0_r00             ;         // 0xC930_4C00
CTOP_CTRL_ND0_CTOP_ND0_R01_M19A0_T           ctop_nd0_r01             ;         // 0xC930_4C04
CTOP_CTRL_ND0_CTOP_ND0_R02_M19A0_T           ctop_nd0_r02             ;         // 0xC930_4C08
CTOP_CTRL_ND0_CTOP_ND0_R03_M19A0_T           ctop_nd0_r03             ;         // 0xC930_4C0C
CTOP_CTRL_ND0_CTOP_ND0_R04_M19A0_T           ctop_nd0_r04             ;         // 0xC930_4C10
CTOP_CTRL_ND0_CTOP_ND0_R05_M19A0_T           ctop_nd0_r05             ;         // 0xC930_4C14
CTOP_CTRL_ND0_CTOP_ND0_R06_M19A0_T           ctop_nd0_r06             ;         // 0xC930_4C18
CTOP_CTRL_ND0_CTOP_ND0_R07_M19A0_T           ctop_nd0_r07             ;         // 0xC930_4C1C
} CTOP_CTRL_ND0_REG_M19A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_ND0_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

