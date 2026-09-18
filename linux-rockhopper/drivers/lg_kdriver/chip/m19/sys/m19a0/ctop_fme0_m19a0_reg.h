#ifndef _CTOP_FME0_M19A0_REG_H_
#define _CTOP_FME0_M19A0_REG_H_

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
    0xC930_6800    ctop_fme0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_tpio_data0_ds         :  1,    //      1
    reg_tpio_data0_pd         :  1,    //      2
                              :  2,    //   4: 3 reserved
    reg_tpio_data1_ds         :  1,    //      5
    reg_tpio_data1_pd         :  1,    //      6
                              :  2,    //   8: 7 reserved
    reg_tpio_sop_ds           :  1,    //      9
    reg_tpio_sop_pd           :  1,    //     10
                              :  2,    //  12:11 reserved
    reg_tpio_clk_ds           :  1,    //     13
    reg_tpio_clk_pd           :  1,    //     14
                              :  2,    //  16:15 reserved
    reg_tpio_err_ds           :  1,    //     17
    reg_tpio_err_pd           :  1,    //     18
                              :  2,    //  20:19 reserved
    reg_tpio_val_ds           :  1,    //     21
    reg_tpio_val_pd           :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_FME0_CTOP_FME0_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6804    ctop_fme0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_tpi_data1_pu          :  1,    //      1
    reg_tpi_data1_pd          :  1,    //      2
                              :  2,    //   4: 3 reserved
    reg_tpi_data0_pu          :  1,    //      5
    reg_tpi_data0_pd          :  1,    //      6
                              :  2,    //   8: 7 reserved
    reg_tpio_data7_ds         :  1,    //      9
    reg_tpio_data7_pd         :  1,    //     10
                              :  2,    //  12:11 reserved
    reg_tpio_data6_ds         :  1,    //     13
    reg_tpio_data6_pd         :  1,    //     14
                              :  2,    //  16:15 reserved
    reg_tpio_data5_ds         :  1,    //     17
    reg_tpio_data5_pd         :  1,    //     18
                              :  2,    //  20:19 reserved
    reg_tpio_data4_ds         :  1,    //     21
    reg_tpio_data4_pd         :  1,    //     22
                              :  2,    //  24:23 reserved
    reg_tpio_data3_ds         :  1,    //     25
    reg_tpio_data3_pd         :  1,    //     26
                              :  2,    //  28:27 reserved
    reg_tpio_data2_ds         :  1,    //     29
    reg_tpio_data2_pd         :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6808    ctop_fme0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_tpi_err_pu            :  1,    //      1
    reg_tpi_err_pd            :  1,    //      2
                              :  2,    //   4: 3 reserved
    reg_tpi_sop_pu            :  1,    //      5
    reg_tpi_sop_pd            :  1,    //      6
                              :  2,    //   8: 7 reserved
    reg_tpi_data7_pu          :  1,    //      9
    reg_tpi_data7_pd          :  1,    //     10
                              :  2,    //  12:11 reserved
    reg_tpi_data5_pu          :  1,    //     13
    reg_tpi_data5_pd          :  1,    //     14
                              :  2,    //  16:15 reserved
    reg_tpi_data6_pu          :  1,    //     17
    reg_tpi_data6_pd          :  1,    //     18
                              :  2,    //  20:19 reserved
    reg_tpi_data4_pu          :  1,    //     21
    reg_tpi_data4_pd          :  1,    //     22
                              :  2,    //  24:23 reserved
    reg_tpi_data3_pu          :  1,    //     25
    reg_tpi_data3_pd          :  1,    //     26
                              :  2,    //  28:27 reserved
    reg_tpi_data2_pu          :  1,    //     29
    reg_tpi_data2_pd          :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_680C    ctop_fme0_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 25,    //  24: 0 reserved
    reg_tpi_clk_pu            :  1,    //     25
    reg_tpi_clk_pd            :  1,    //     26
                              :  2,    //  28:27 reserved
    reg_tpi_val_pu            :  1,    //     29
    reg_tpi_val_pd            :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6810    ctop_fme0_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpo_outmux_sel        :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_tpi_ext_demod2_sel    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tpi_ext_demod1_sel    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_tpi_int_demod_sel     :  2,    //  13:12
                              : 18;    //  31:14 reserved
}CTOP_FME0_CTOP_FME0_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6814    ctop_fme0_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_eb_be_n0_pd           :  1,    //      2
    reg_eb_be_n1_pd           :  1,    //      3
    reg_eb_cs3_pd             :  1,    //      4
    reg_eb_cs2_pd             :  1,    //      5
    reg_eb_cs1_pd             :  1,    //      6
    reg_eb_cs0_pd             :  1,    //      7
    reg_eb_addr1_pd           :  1,    //      8
    reg_eb_addr2_pd           :  1,    //      9
    reg_eb_addr0_pd           :  1,    //     10
                              :  1,    //     11 reserved
    reg_eb_data7_pd           :  1,    //     12
    reg_eb_data6_pd           :  1,    //     13
    reg_eb_data5_pd           :  1,    //     14
    reg_eb_data4_pd           :  1,    //     15
    reg_eb_data3_pd           :  1,    //     16
    reg_eb_data2_pd           :  1,    //     17
    reg_eb_data1_pd           :  1,    //     18
    reg_eb_data0_pd           :  1,    //     19
    reg_eb_data7_pu           :  1,    //     20
    reg_eb_data6_pu           :  1,    //     21
    reg_eb_data5_pu           :  1,    //     22
    reg_eb_data4_pu           :  1,    //     23
    reg_eb_data3_pu           :  1,    //     24
    reg_eb_data2_pu           :  1,    //     25
    reg_eb_data1_pu           :  1,    //     26
    reg_eb_data0_pu           :  1,    //     27
    reg_eb_oe_n_pd            :  1,    //     28
    reg_eb_we_n_pd            :  1,    //     29
    reg_eb_wait_pd            :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FME0_CTOP_FME0_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6818    ctop_fme0_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 16,    //  15: 0 reserved
    reg_use_cpu_gpio_15_7     :  1,    //     16
    reg_use_cpu_gpio_15_6     :  1,    //     17
    reg_use_cpu_gpio_15_5     :  1,    //     18
    reg_use_cpu_gpio_15_4     :  1,    //     19
    reg_use_cpu_gpio_15_3     :  1,    //     20
    reg_use_cpu_gpio_15_2     :  1,    //     21
    reg_use_cpu_gpio_15_1     :  1,    //     22
    reg_use_cpu_gpio_15_0     :  1,    //     23
    reg_use_cpu_gpio_14_2     :  1,    //     24
    reg_use_cpu_gpio_14_1     :  1,    //     25
    reg_use_cpu_gpio_14_0     :  1,    //     26
    reg_use_cpu_gpio_11_5     :  1,    //     27
    reg_use_cpu_gpio_11_4     :  1,    //     28
    reg_use_cpu_gpio_11_3     :  1,    //     29
    reg_use_cpu_gpio_11_2     :  1,    //     30
    reg_use_cpu_gpio_11_0     :  1;    //     31
}CTOP_FME0_CTOP_FME0_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_681C    ctop_fme0_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 31,    //  30: 0 reserved
    reg_tpio_sel_ctrl         :  1;    //     31
}CTOP_FME0_CTOP_FME0_R07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_6820    ctop_fme0_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 29,    //  28: 0 reserved
    reg_ir_enable             :  1,    //     29
                              :  1,    //     30 reserved
    reg_aud_earc_en           :  1;    //     31
}CTOP_FME0_CTOP_FME0_R08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_fme0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_FME0_CTOP_FME0_R00_M19A0_T              ctop_fme0_r00            ;         // 0xC930_6800
CTOP_FME0_CTOP_FME0_R01_M19A0_T              ctop_fme0_r01            ;         // 0xC930_6804
CTOP_FME0_CTOP_FME0_R02_M19A0_T              ctop_fme0_r02            ;         // 0xC930_6808
CTOP_FME0_CTOP_FME0_R03_M19A0_T              ctop_fme0_r03            ;         // 0xC930_680C
CTOP_FME0_CTOP_FME0_R04_M19A0_T              ctop_fme0_r04            ;         // 0xC930_6810
CTOP_FME0_CTOP_FME0_R05_M19A0_T              ctop_fme0_r05            ;         // 0xC930_6814
CTOP_FME0_CTOP_FME0_R06_M19A0_T              ctop_fme0_r06            ;         // 0xC930_6818
CTOP_FME0_CTOP_FME0_R07_M19A0_T              ctop_fme0_r07            ;         // 0xC930_681C
CTOP_FME0_CTOP_FME0_R08_M19A0_T              ctop_fme0_r08            ;         // 0xC930_6820
} CTOP_FME0_REG_M19A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_FME0_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

