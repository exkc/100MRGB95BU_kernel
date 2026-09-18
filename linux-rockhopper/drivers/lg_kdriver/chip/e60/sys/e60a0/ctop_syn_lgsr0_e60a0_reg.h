#ifndef _CTOP_SYN_LGSR0_E60A0_REG_H_
#define _CTOP_SYN_LGSR0_E60A0_REG_H_

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
    0xC935_F400    syn_sr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ls_disable_lgsr0      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ls_disable_emmc       :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_LGSR0_SYN_SR000_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F404    syn_sr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_lgsr_y_sw_rst     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_LGSR0_SYN_SR001_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F408    syn_sr002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_res4_cv10_sw_rst      :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_LGSR0_SYN_SR002_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F40C    syn_sr003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tmclk_div                 : 10,    //   9: 0
                              :  2,    //  11:10 reserved
    tmclk_en                  :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_LGSR0_SYN_SR003_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F410    syn_sr004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_addr1__st      :  1,    //      0
    reg_pad_eb_addr1__pu      :  1,    //      1
    reg_pad_eb_addr1__pd      :  1,    //      2
    reg_pad_eb_addr1__ds3     :  1,    //      3
    reg_pad_eb_addr1__ds2     :  1,    //      4
    reg_pad_eb_addr1__ds1     :  1,    //      5
    reg_pad_eb_addr1__ds0     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_addr0__st      :  1,    //      8
    reg_pad_eb_addr0__pu      :  1,    //      9
    reg_pad_eb_addr0__pd      :  1,    //     10
    reg_pad_eb_addr0__ds3     :  1,    //     11
    reg_pad_eb_addr0__ds2     :  1,    //     12
    reg_pad_eb_addr0__ds1     :  1,    //     13
    reg_pad_eb_addr0__ds0     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_addr2__ds0     :  1,    //     16
    reg_pad_eb_addr2__ds1     :  1,    //     17
    reg_pad_eb_addr2__ds2     :  1,    //     18
    reg_pad_eb_addr2__ds3     :  1,    //     19
    reg_pad_eb_addr2__pd      :  1,    //     20
    reg_pad_eb_addr2__pu      :  1,    //     21
    reg_pad_eb_addr2__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_addr3__ds0     :  1,    //     24
    reg_pad_eb_addr3__ds1     :  1,    //     25
    reg_pad_eb_addr3__ds2     :  1,    //     26
    reg_pad_eb_addr3__ds3     :  1,    //     27
    reg_pad_eb_addr3__pd      :  1,    //     28
    reg_pad_eb_addr3__pu      :  1,    //     29
    reg_pad_eb_addr3__st      :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_LGSR0_SYN_SR004_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F414    syn_sr005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs1__st        :  1,    //      0
    reg_pad_eb_cs1__pu        :  1,    //      1
    reg_pad_eb_cs1__pd        :  1,    //      2
    reg_pad_eb_cs1__ds3       :  1,    //      3
    reg_pad_eb_cs1__ds2       :  1,    //      4
    reg_pad_eb_cs1__ds1       :  1,    //      5
    reg_pad_eb_cs1__ds0       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_cs0__st        :  1,    //      8
    reg_pad_eb_cs0__pu        :  1,    //      9
    reg_pad_eb_cs0__pd        :  1,    //     10
    reg_pad_eb_cs0__ds3       :  1,    //     11
    reg_pad_eb_cs0__ds2       :  1,    //     12
    reg_pad_eb_cs0__ds1       :  1,    //     13
    reg_pad_eb_cs0__ds0       :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_be_n1__st      :  1,    //     16
    reg_pad_eb_be_n1__pu      :  1,    //     17
    reg_pad_eb_be_n1__pd      :  1,    //     18
    reg_pad_eb_be_n1__ds3     :  1,    //     19
    reg_pad_eb_be_n1__ds2     :  1,    //     20
    reg_pad_eb_be_n1__ds1     :  1,    //     21
    reg_pad_eb_be_n1__ds0     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_eb_be_n0__st      :  1,    //     24
    reg_pad_eb_be_n0__pu      :  1,    //     25
    reg_pad_eb_be_n0__pd      :  1,    //     26
    reg_pad_eb_be_n0__ds3     :  1,    //     27
    reg_pad_eb_be_n0__ds2     :  1,    //     28
    reg_pad_eb_be_n0__ds1     :  1,    //     29
    reg_pad_eb_be_n0__ds0     :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_LGSR0_SYN_SR005_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F418    syn_sr006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_cs3__st        :  1,    //      0
    reg_pad_eb_cs3__pu        :  1,    //      1
    reg_pad_eb_cs3__pd        :  1,    //      2
    reg_pad_eb_cs3__ds3       :  1,    //      3
    reg_pad_eb_cs3__ds2       :  1,    //      4
    reg_pad_eb_cs3__ds1       :  1,    //      5
    reg_pad_eb_cs3__ds0       :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_cs2__st        :  1,    //      8
    reg_pad_eb_cs2__pu        :  1,    //      9
    reg_pad_eb_cs2__pd        :  1,    //     10
    reg_pad_eb_cs2__ds3       :  1,    //     11
    reg_pad_eb_cs2__ds2       :  1,    //     12
    reg_pad_eb_cs2__ds1       :  1,    //     13
    reg_pad_eb_cs2__ds0       :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_LGSR0_SYN_SR006_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F41C    syn_sr007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_we_n__st       :  1,    //      0
    reg_pad_eb_we_n__pu       :  1,    //      1
    reg_pad_eb_we_n__pd       :  1,    //      2
    reg_pad_eb_we_n__ds3      :  1,    //      3
    reg_pad_eb_we_n__ds2      :  1,    //      4
    reg_pad_eb_we_n__ds1      :  1,    //      5
    reg_pad_eb_we_n__ds0      :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_eb_wait__st       :  1,    //      8
    reg_pad_eb_wait__pu       :  1,    //      9
    reg_pad_eb_wait__pd       :  1,    //     10
    reg_pad_eb_wait__ds3      :  1,    //     11
    reg_pad_eb_wait__ds2      :  1,    //     12
    reg_pad_eb_wait__ds1      :  1,    //     13
    reg_pad_eb_wait__ds0      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_eb_oe_n__st       :  1,    //     16
    reg_pad_eb_oe_n__pu       :  1,    //     17
    reg_pad_eb_oe_n__pd       :  1,    //     18
    reg_pad_eb_oe_n__ds3      :  1,    //     19
    reg_pad_eb_oe_n__ds2      :  1,    //     20
    reg_pad_eb_oe_n__ds1      :  1,    //     21
    reg_pad_eb_oe_n__ds0      :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_LGSR0_SYN_SR007_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F420    syn_sr008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_be_n0_mux_sel  :  4,    //   3: 0
    reg_pad_eb_wait_mux_sel   :  4,    //   7: 4
    reg_pad_eb_cs3_mux_sel    :  4,    //  11: 8
    reg_pad_eb_cs2_mux_sel    :  4,    //  15:12
    reg_pad_eb_cs1_mux_sel    :  4,    //  19:16
    reg_pad_eb_cs0_mux_sel    :  4,    //  23:20
    reg_pad_eb_addr1_mux_sel  :  4,    //  27:24
    reg_pad_eb_addr0_mux_sel  :  4;    //  31:28
}CTOP_LGSR0_SYN_SR008_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F424    syn_sr009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_eb_we_n_mux_sel   :  4,    //   3: 0
    reg_pad_eb_oe_n_mux_sel   :  4,    //   7: 4
    reg_pad_eb_be_n1_mux_sel  :  4,    //  11: 8
                              : 12,    //  23:12 reserved
    reg_pad_eb_addr3_mux_sel  :  4,    //  27:24
    reg_pad_eb_addr2_mux_sel  :  4;    //  31:28
}CTOP_LGSR0_SYN_SR009_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC935_F428    syn_sr010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_isol_apb_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_LGSR0_SYN_SR010_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    lgsr0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_LGSR0_SYN_SR000_E60_A0_T            syn_sr000                ;         // 0xC935_F400
    CTOP_LGSR0_SYN_SR001_E60_A0_T            syn_sr001                ;         // 0xC935_F404
    CTOP_LGSR0_SYN_SR002_E60_A0_T            syn_sr002                ;         // 0xC935_F408
    CTOP_LGSR0_SYN_SR003_E60_A0_T            syn_sr003                ;         // 0xC935_F40C
    CTOP_LGSR0_SYN_SR004_E60_A0_T            syn_sr004                ;         // 0xC935_F410
    CTOP_LGSR0_SYN_SR005_E60_A0_T            syn_sr005                ;         // 0xC935_F414
    CTOP_LGSR0_SYN_SR006_E60_A0_T            syn_sr006                ;         // 0xC935_F418
    CTOP_LGSR0_SYN_SR007_E60_A0_T            syn_sr007                ;         // 0xC935_F41C
    CTOP_LGSR0_SYN_SR008_E60_A0_T            syn_sr008                ;         // 0xC935_F420
    CTOP_LGSR0_SYN_SR009_E60_A0_T            syn_sr009                ;         // 0xC935_F424
    CTOP_LGSR0_SYN_SR010_E60_A0_T            syn_sr010                ;         // 0xC935_F428
} CTOP_SYN_LGSR0_REG_E60_A0_T;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_LGSR0_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191216.xlsm'  2019.12.16  KST by LGSiCRDV V3.0B*/

