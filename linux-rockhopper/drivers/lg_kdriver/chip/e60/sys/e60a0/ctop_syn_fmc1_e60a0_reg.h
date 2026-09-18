#ifndef _CTOP_SYN_FMC1_E60A0_REG_H_
#define _CTOP_SYN_FMC1_E60A0_REG_H_

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
    0xC932_4400    syn_fmc1_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc1__reg_pqe_fmc1_ctrl: 32;    //  31:0
}CTOP_FMC1_SYN_FMC1_00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_4404    syn_fmc1_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc1__ls_disable_fmc1 :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_FMC1_SYN_FMC1_01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_4408    syn_fmc1_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc1__swrst_rot_c_wd  :  1,    //      0
    reg_fmc1__swrst_rot_y_wd  :  1,    //      1
    reg_fmc1__swrst_rot_c_wd_req_bundle: 1,    //  2
    reg_fmc1__swrst_fmc_cur_c_l3_rd_req_bundle: 1,    //  3
    reg_fmc1__swrst_fmc_cur_y_l3_rd_req_bundle: 1,    //  4
    reg_fmc1__swrst_fmc_cur_c_l2_rd_req_bundle: 1,    //  5
    reg_fmc1__swrst_fmc_cur_y_l2_rd_req_bundle: 1,    //  6
    reg_fmc1__swrst_fmc_cur_c_l1_rd_req_bundle: 1,    //  7
    reg_fmc1__swrst_fmc_cur_y_l1_rd_req_bundle: 1,    //  8
    reg_fmc1__swrst_fmc_cur_c_l0_rd_req_bundle: 1,    //  9
    reg_fmc1__swrst_fmc_cur_y_l0_rd_req_bundle: 1,    //  10
    reg_fmc1__swrst_fmc_prv_c_l3_rd_req_bundle: 1,    //  11
    reg_fmc1__swrst_fmc_prv_y_l3_rd_req_bundle: 1,    //  12
    reg_fmc1__swrst_fmc_prv_c_l2_rd_req_bundle: 1,    //  13
    reg_fmc1__swrst_fmc_prv_y_l2_rd_req_bundle: 1,    //  14
    reg_fmc1__swrst_fmc_prv_c_l1_rd_req_bundle: 1,    //  15
    reg_fmc1__swrst_fmc_prv_y_l1_rd_req_bundle: 1,    //  16
    reg_fmc1__swrst_fmc_prv_c_l0_rd_req_bundle: 1,    //  17
    reg_fmc1__swrst_fmc_prv_y_l0_rd_req_bundle: 1,    //  18
    reg_fmc1__swrst_rot_y_wd_req_bundle: 1,    //  19
                              : 12;    //  31:20 reserved
}CTOP_FMC1_SYN_FMC1_02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_440C    syn_fmc1_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch1__st     :  1,    //      0
    reg_pad_aec_lrch1__pu     :  1,    //      1
    reg_pad_aec_lrch1__pd     :  1,    //      2
    reg_pad_aec_lrch1__ds3    :  1,    //      3
    reg_pad_aec_lrch1__ds2    :  1,    //      4
    reg_pad_aec_lrch1__ds1    :  1,    //      5
    reg_pad_aec_lrch1__ds0    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_aec_lrch0__st     :  1,    //      8
    reg_pad_aec_lrch0__pu     :  1,    //      9
    reg_pad_aec_lrch0__pd     :  1,    //     10
    reg_pad_aec_lrch0__ds3    :  1,    //     11
    reg_pad_aec_lrch0__ds2    :  1,    //     12
    reg_pad_aec_lrch0__ds1    :  1,    //     13
    reg_pad_aec_lrch0__ds0    :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_FMC1_SYN_FMC1_03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_4410    syn_fmc1_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dacslrch__st      :  1,    //      0
    reg_pad_dacslrch__pu      :  1,    //      1
    reg_pad_dacslrch__pd      :  1,    //      2
    reg_pad_dacslrch__ds3     :  1,    //      3
    reg_pad_dacslrch__ds2     :  1,    //      4
    reg_pad_dacslrch__ds1     :  1,    //      5
    reg_pad_dacslrch__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dacclfch__st      :  1,    //      8
    reg_pad_dacclfch__pu      :  1,    //      9
    reg_pad_dacclfch__pd      :  1,    //     10
    reg_pad_dacclfch__ds3     :  1,    //     11
    reg_pad_dacclfch__ds2     :  1,    //     12
    reg_pad_dacclfch__ds1     :  1,    //     13
    reg_pad_dacclfch__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_aec_lrch3__st     :  1,    //     16
    reg_pad_aec_lrch3__pu     :  1,    //     17
    reg_pad_aec_lrch3__pd     :  1,    //     18
    reg_pad_aec_lrch3__ds3    :  1,    //     19
    reg_pad_aec_lrch3__ds2    :  1,    //     20
    reg_pad_aec_lrch3__ds1    :  1,    //     21
    reg_pad_aec_lrch3__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_aec_lrch2__st     :  1,    //     24
    reg_pad_aec_lrch2__pu     :  1,    //     25
    reg_pad_aec_lrch2__pd     :  1,    //     26
    reg_pad_aec_lrch2__ds3    :  1,    //     27
    reg_pad_aec_lrch2__ds2    :  1,    //     28
    reg_pad_aec_lrch2__ds1    :  1,    //     29
    reg_pad_aec_lrch2__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC1_SYN_FMC1_04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_4414    syn_fmc1_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pqe_ip_enb__st    :  1,    //      0
    reg_pad_pqe_ip_enb__ds3   :  1,    //      1
    reg_pad_pqe_ip_enb__ds2   :  1,    //      2
    reg_pad_pqe_ip_enb__ds1   :  1,    //      3
    reg_pad_pqe_ip_enb__ds0   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_pad_pcmi3sck__st      :  1,    //      8
    reg_pad_pcmi3sck__pu      :  1,    //      9
    reg_pad_pcmi3sck__pd      :  1,    //     10
    reg_pad_pcmi3sck__ds3     :  1,    //     11
    reg_pad_pcmi3sck__ds2     :  1,    //     12
    reg_pad_pcmi3sck__ds1     :  1,    //     13
    reg_pad_pcmi3sck__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_pcmi3lrck__st     :  1,    //     16
    reg_pad_pcmi3lrck__pu     :  1,    //     17
    reg_pad_pcmi3lrck__pd     :  1,    //     18
    reg_pad_pcmi3lrck__ds3    :  1,    //     19
    reg_pad_pcmi3lrck__ds2    :  1,    //     20
    reg_pad_pcmi3lrck__ds1    :  1,    //     21
    reg_pad_pcmi3lrck__ds0    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pcmi3lrch__st     :  1,    //     24
    reg_pad_pcmi3lrch__pu     :  1,    //     25
    reg_pad_pcmi3lrch__pd     :  1,    //     26
    reg_pad_pcmi3lrch__ds3    :  1,    //     27
    reg_pad_pcmi3lrch__ds2    :  1,    //     28
    reg_pad_pcmi3lrch__ds1    :  1,    //     29
    reg_pad_pcmi3lrch__ds0    :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC1_SYN_FMC1_05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_4418    syn_fmc1_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrck_mux_sel :  4,    //   3: 0
    reg_pad_pcmi3lrch_mux_sel :  4,    //   7: 4
    reg_pad_dacslrch_mux_sel  :  4,    //  11: 8
    reg_pad_dacclfch_mux_sel  :  4,    //  15:12
    reg_pad_aec_lrch3_mux_sel :  4,    //  19:16
    reg_pad_aec_lrch2_mux_sel :  4,    //  23:20
    reg_pad_aec_lrch1_mux_sel :  4,    //  27:24
    reg_pad_aec_lrch0_mux_sel :  4;    //  31:28
}CTOP_FMC1_SYN_FMC1_06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC932_441C    syn_fmc1_07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3sck_mux_sel  :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}CTOP_FMC1_SYN_FMC1_07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    fmc1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_FMC1_SYN_FMC1_00_E60_A0_T           syn_fmc1_00              ;         // 0xC932_4400
    CTOP_FMC1_SYN_FMC1_01_E60_A0_T           syn_fmc1_01              ;         // 0xC932_4404
    CTOP_FMC1_SYN_FMC1_02_E60_A0_T           syn_fmc1_02              ;         // 0xC932_4408
    CTOP_FMC1_SYN_FMC1_03_E60_A0_T           syn_fmc1_03              ;         // 0xC932_440C
    CTOP_FMC1_SYN_FMC1_04_E60_A0_T           syn_fmc1_04              ;         // 0xC932_4410
    CTOP_FMC1_SYN_FMC1_05_E60_A0_T           syn_fmc1_05              ;         // 0xC932_4414
    CTOP_FMC1_SYN_FMC1_06_E60_A0_T           syn_fmc1_06              ;         // 0xC932_4418
    CTOP_FMC1_SYN_FMC1_07_E60_A0_T           syn_fmc1_07              ;         // 0xC932_441C
} CTOP_SYN_FMC1_REG_E60_A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_FMC1_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

