#ifndef _CTOP_SYN_CVI_E60A0_REG_H_
#define _CTOP_SYN_CVI_E60A0_REG_H_

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
    0xC93B_8400    syn_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__pqe_cvi_ctrl     : 32;    //  31: 0
}CTOP_CVI_SYN_CVI00_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8404    syn_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__ls_disable_cvi   :  1,    //      0
    reg_cvi__ls_disable_venc  :  1,    //      1
    reg_cvi__ls_disable_icod  :  1,    //      2
    reg_cvi__ls_disable_te    :  1,    //      3
    reg_cvi__ls_disable_dsc   :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CVI_SYN_CVI01_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8408    syn_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__swrst_dsc_imx0_yc:  1,    //      0
    l                         :  1,    //      1
    reg_cvi__swrst_stcc23_data:  1,    //      2
    reg_cvi__swrst_vid0_data  :  1,    //      3
    reg_cvi__swrst_vid1_data  :  1,    //      4
    reg_cvi__swrst_aud0_data  :  1,    //      5
    reg_cvi__swrst_aud1_data  :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_CVI_SYN_CVI02_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_840C    syn_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__swrst_hdmi_rx_prt1_pix: 1,    //  0
    reg_cvi__swrst_hdmi_rx_prt2_pix: 1,    //  1
    reg_cvi__swrst_hdmi_rx_prt3_pix: 1,    //  2
    reg_cvi__swrst_hdmi_rx_prt4_pix: 1,    //  3
    reg_cvi__swrst_imx0_dsc_y :  1,    //      4
    reg_cvi__swrst_imx0_dsc_c :  1,    //      5
    reg_cvi__swrst_hdr_buf    :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_CVI_SYN_CVI03_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8430    syn_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__tpi_int_clk_bypass_mode: 1,    //  0
    reg_cvi__tpi_cam_clk_bypass_mode: 1,    //  1
    reg_cvi__tpi_ext1_clk_bypass_mode: 1,    //  2
    reg_cvi__tpi_ext2_clk_bypass_mode: 1,    //  3
    reg_cvi__stpi_ext1_clk_bypass_mode: 1,    //  4
    reg_cvi__stpi_ext2_clk_bypass_mode: 1,    //  5
    reg_cvi__stpi_ext3_clk_bypass_mode: 1,    //  6
                              : 25;    //   31:7 reserved
}CTOP_CVI_SYN_CVI04_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8434    syn_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__hdmirx_prt_pix_data_sel: 1,    //  0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI05_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8438    syn_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__cvi_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_cvi__cvi_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_cvi__cvi_ar_ag        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cvi__cvi_aw_ag        :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CVI_SYN_CVI06_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_843C    syn_cvi07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__cvi_flush_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI07_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8440    syn_cvi08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__cvi_flush_done   :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI08_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8444    syn_cvi09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__te_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_cvi__te_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_cvi__te_ar_ag         :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cvi__te_aw_ag         :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CVI_SYN_CVI09_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8448    syn_cvi10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__te_flush_en      :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI10_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_844C    syn_cvi11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__te_flush_done    :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI11_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8450    syn_cvi12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__venc_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_cvi__venc_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_cvi__venc_ar_ag       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cvi__venc_aw_ag       :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CVI_SYN_CVI12_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8454    syn_cvi13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__venc_flush_en    :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI13_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8458    syn_cvi14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__venc_flush_done  :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI14_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_845C    syn_cvi15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__icod_ar_bus_access_gating: 1,    //  0
                              :  3,    //   3: 1 reserved
    reg_cvi__icod_aw_bus_access_gating: 1,    //  4
                              :  3,    //   7: 5 reserved
    reg_cvi__icod_ar_ag       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_cvi__icod_aw_ag       :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CVI_SYN_CVI15_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8460    syn_cvi16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__icod_flush_en    :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI16_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8464    syn_cvi17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__icod_flush_done  :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI17_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8468    syn_cvi18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_clk_ext1__st  :  1,    //      0
    reg_pad_tpi_clk_ext1__pu  :  1,    //      1
    reg_pad_tpi_clk_ext1__pd  :  1,    //      2
    reg_pad_tpi_clk_ext1__ds3 :  1,    //      3
    reg_pad_tpi_clk_ext1__ds2 :  1,    //      4
    reg_pad_tpi_clk_ext1__ds1 :  1,    //      5
    reg_pad_tpi_clk_ext1__ds0 :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_edid_nisol_out__st:  1,    //      8
    reg_pad_edid_nisol_out__ds3: 1,    //      9
    reg_pad_edid_nisol_out__ds2: 1,    //     10
    reg_pad_edid_nisol_out__ds1: 1,    //     11
    reg_pad_edid_nisol_out__ds0: 1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CVI_SYN_CVI18_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_846C    syn_cvi19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data3_ext1__st:  1,    //      0
    reg_pad_tpi_data3_ext1__pu:  1,    //      1
    reg_pad_tpi_data3_ext1__pd:  1,    //      2
    reg_pad_tpi_data3_ext1__ds3: 1,    //      3
    reg_pad_tpi_data3_ext1__ds2: 1,    //      4
    reg_pad_tpi_data3_ext1__ds1: 1,    //      5
    reg_pad_tpi_data3_ext1__ds0: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data2_ext1__st:  1,    //      8
    reg_pad_tpi_data2_ext1__pu:  1,    //      9
    reg_pad_tpi_data2_ext1__pd:  1,    //     10
    reg_pad_tpi_data2_ext1__ds3: 1,    //     11
    reg_pad_tpi_data2_ext1__ds2: 1,    //     12
    reg_pad_tpi_data2_ext1__ds1: 1,    //     13
    reg_pad_tpi_data2_ext1__ds0: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data1_ext1__st:  1,    //     16
    reg_pad_tpi_data1_ext1__pu:  1,    //     17
    reg_pad_tpi_data1_ext1__pd:  1,    //     18
    reg_pad_tpi_data1_ext1__ds3: 1,    //     19
    reg_pad_tpi_data1_ext1__ds2: 1,    //     20
    reg_pad_tpi_data1_ext1__ds1: 1,    //     21
    reg_pad_tpi_data1_ext1__ds0: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data0_ext1__st:  1,    //     24
    reg_pad_tpi_data0_ext1__pu:  1,    //     25
    reg_pad_tpi_data0_ext1__pd:  1,    //     26
    reg_pad_tpi_data0_ext1__ds3: 1,    //     27
    reg_pad_tpi_data0_ext1__ds2: 1,    //     28
    reg_pad_tpi_data0_ext1__ds1: 1,    //     29
    reg_pad_tpi_data0_ext1__ds0: 1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CVI_SYN_CVI19_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8470    syn_cvi20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data5_ext2__st:  1,    //      0
    reg_pad_tpi_data5_ext2__pu:  1,    //      1
    reg_pad_tpi_data5_ext2__pd:  1,    //      2
    reg_pad_tpi_data5_ext2__ds3: 1,    //      3
    reg_pad_tpi_data5_ext2__ds2: 1,    //      4
    reg_pad_tpi_data5_ext2__ds1: 1,    //      5
    reg_pad_tpi_data5_ext2__ds0: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data5_ext1__st:  1,    //      8
    reg_pad_tpi_data5_ext1__pu:  1,    //      9
    reg_pad_tpi_data5_ext1__pd:  1,    //     10
    reg_pad_tpi_data5_ext1__ds3: 1,    //     11
    reg_pad_tpi_data5_ext1__ds2: 1,    //     12
    reg_pad_tpi_data5_ext1__ds1: 1,    //     13
    reg_pad_tpi_data5_ext1__ds0: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data4_ext2__st:  1,    //     16
    reg_pad_tpi_data4_ext2__pu:  1,    //     17
    reg_pad_tpi_data4_ext2__pd:  1,    //     18
    reg_pad_tpi_data4_ext2__ds3: 1,    //     19
    reg_pad_tpi_data4_ext2__ds2: 1,    //     20
    reg_pad_tpi_data4_ext2__ds1: 1,    //     21
    reg_pad_tpi_data4_ext2__ds0: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data4_ext1__st:  1,    //     24
    reg_pad_tpi_data4_ext1__pu:  1,    //     25
    reg_pad_tpi_data4_ext1__pd:  1,    //     26
    reg_pad_tpi_data4_ext1__ds3: 1,    //     27
    reg_pad_tpi_data4_ext1__ds2: 1,    //     28
    reg_pad_tpi_data4_ext1__ds1: 1,    //     29
    reg_pad_tpi_data4_ext1__ds0: 1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CVI_SYN_CVI20_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8474    syn_cvi21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_ext2__st:  1,    //      0
    reg_pad_tpi_data7_ext2__pu:  1,    //      1
    reg_pad_tpi_data7_ext2__pd:  1,    //      2
    reg_pad_tpi_data7_ext2__ds3: 1,    //      3
    reg_pad_tpi_data7_ext2__ds2: 1,    //      4
    reg_pad_tpi_data7_ext2__ds1: 1,    //      5
    reg_pad_tpi_data7_ext2__ds0: 1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_data7_ext1__st:  1,    //      8
    reg_pad_tpi_data7_ext1__pu:  1,    //      9
    reg_pad_tpi_data7_ext1__pd:  1,    //     10
    reg_pad_tpi_data7_ext1__ds3: 1,    //     11
    reg_pad_tpi_data7_ext1__ds2: 1,    //     12
    reg_pad_tpi_data7_ext1__ds1: 1,    //     13
    reg_pad_tpi_data7_ext1__ds0: 1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_data6_ext2__st:  1,    //     16
    reg_pad_tpi_data6_ext2__pu:  1,    //     17
    reg_pad_tpi_data6_ext2__pd:  1,    //     18
    reg_pad_tpi_data6_ext2__ds3: 1,    //     19
    reg_pad_tpi_data6_ext2__ds2: 1,    //     20
    reg_pad_tpi_data6_ext2__ds1: 1,    //     21
    reg_pad_tpi_data6_ext2__ds0: 1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_data6_ext1__st:  1,    //     24
    reg_pad_tpi_data6_ext1__pu:  1,    //     25
    reg_pad_tpi_data6_ext1__pd:  1,    //     26
    reg_pad_tpi_data6_ext1__ds3: 1,    //     27
    reg_pad_tpi_data6_ext1__ds2: 1,    //     28
    reg_pad_tpi_data6_ext1__ds1: 1,    //     29
    reg_pad_tpi_data6_ext1__ds0: 1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CVI_SYN_CVI21_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8478    syn_cvi22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_val_ext2__st  :  1,    //      0
    reg_pad_tpi_val_ext2__pu  :  1,    //      1
    reg_pad_tpi_val_ext2__pd  :  1,    //      2
    reg_pad_tpi_val_ext2__ds3 :  1,    //      3
    reg_pad_tpi_val_ext2__ds2 :  1,    //      4
    reg_pad_tpi_val_ext2__ds1 :  1,    //      5
    reg_pad_tpi_val_ext2__ds0 :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_tpi_val_ext1__st  :  1,    //      8
    reg_pad_tpi_val_ext1__pu  :  1,    //      9
    reg_pad_tpi_val_ext1__pd  :  1,    //     10
    reg_pad_tpi_val_ext1__ds3 :  1,    //     11
    reg_pad_tpi_val_ext1__ds2 :  1,    //     12
    reg_pad_tpi_val_ext1__ds1 :  1,    //     13
    reg_pad_tpi_val_ext1__ds0 :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_tpi_sop_ext2__st  :  1,    //     16
    reg_pad_tpi_sop_ext2__pu  :  1,    //     17
    reg_pad_tpi_sop_ext2__pd  :  1,    //     18
    reg_pad_tpi_sop_ext2__ds3 :  1,    //     19
    reg_pad_tpi_sop_ext2__ds2 :  1,    //     20
    reg_pad_tpi_sop_ext2__ds1 :  1,    //     21
    reg_pad_tpi_sop_ext2__ds0 :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_tpi_sop_ext1__st  :  1,    //     24
    reg_pad_tpi_sop_ext1__pu  :  1,    //     25
    reg_pad_tpi_sop_ext1__pd  :  1,    //     26
    reg_pad_tpi_sop_ext1__ds3 :  1,    //     27
    reg_pad_tpi_sop_ext1__ds2 :  1,    //     28
    reg_pad_tpi_sop_ext1__ds1 :  1,    //     29
    reg_pad_tpi_sop_ext1__ds0 :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CVI_SYN_CVI22_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_847C    syn_cvi23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data4_ext1_mux_sel: 4,    //  3:0
    reg_pad_tpi_data3_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data2_ext1_mux_sel: 4,    //  11:8
    reg_pad_tpi_data1_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data0_ext1_mux_sel: 4,    //  19:16
    reg_pad_tpi_clk_ext1_mux_sel: 4,    //  23:20
    reg_pad_edid_nisol_out_mux_sel: 4,    //  27:24
                              :  4;    //  31:28 reserved
}CTOP_CVI_SYN_CVI23_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8480    syn_cvi24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_data7_ext2_mux_sel: 4,    //  3:0
    reg_pad_tpi_data7_ext1_mux_sel: 4,    //  7:4
    reg_pad_tpi_data6_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_data6_ext1_mux_sel: 4,    //  15:12
    reg_pad_tpi_data5_ext2_mux_sel: 4,    //  19:16
    reg_pad_tpi_data5_ext1_mux_sel: 4,    //  23:20
    reg_pad_tpi_data4_ext2_mux_sel: 4,    //  27:24
                              :  4;    //  31:28 reserved
}CTOP_CVI_SYN_CVI24_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8484    syn_cvi25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_tpi_val_ext2_mux_sel: 4,    //  3: 0
    reg_pad_tpi_val_ext1_mux_sel: 4,    //  7: 4
    reg_pad_tpi_sop_ext2_mux_sel: 4,    //  11:8
    reg_pad_tpi_sop_ext1_mux_sel: 4,    //  15:12
                              : 16;    //  31:16 reserved
}CTOP_CVI_SYN_CVI25_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8488    syn_cvi26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_monitor_sel_3to0      :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_monitor_sel_7to4      :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_monitor_shift1        :  1,    //      8
    reg_monitor_shift2        :  1,    //      9
    reg_monitor_shift3        :  1,    //     10
    reg_monitor_shift4        :  1,    //     11
    reg_monitor_shift5        :  1,    //     12
    reg_monitor_shift6        :  1,    //     13
    reg_monitor_shift7        :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_CVI_SYN_CVI26_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_848C    syn_cvi27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpo_outmux_sel        :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI27_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8490    syn_cvi28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_nisol_out_oen    :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CVI_SYN_CVI28_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    0xC93B_8494    syn_cvi29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__soft_rst_edid_comm_apb_bnd_adpt_n: 1,    //  0
    reg_cvi__soft_rst_edid_comm_apb_bnd_n: 1,    //  1
                              : 30;    //   31:2 reserved
}CTOP_CVI_SYN_CVI29_E60_A0_T;

/*-----------------------------------------------------------------------------------------
    cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CTOP_CVI_SYN_CVI00_E60_A0_T              syn_cvi00                ;         // 0xC93B_8400
    CTOP_CVI_SYN_CVI01_E60_A0_T              syn_cvi01                ;         // 0xC93B_8404
    CTOP_CVI_SYN_CVI02_E60_A0_T              syn_cvi02                ;         // 0xC93B_8408
    CTOP_CVI_SYN_CVI03_E60_A0_T              syn_cvi03                ;         // 0xC93B_840C
UINT32                                                 _rsvd_00[   8] ;         // 0xC93B_8410 ~ 0xC93B_842C
    CTOP_CVI_SYN_CVI04_E60_A0_T              syn_cvi04                ;         // 0xC93B_8430
    CTOP_CVI_SYN_CVI05_E60_A0_T              syn_cvi05                ;         // 0xC93B_8434
    CTOP_CVI_SYN_CVI06_E60_A0_T              syn_cvi06                ;         // 0xC93B_8438
    CTOP_CVI_SYN_CVI07_E60_A0_T              syn_cvi07                ;         // 0xC93B_843C
    CTOP_CVI_SYN_CVI08_E60_A0_T              syn_cvi08                ;         // 0xC93B_8440
    CTOP_CVI_SYN_CVI09_E60_A0_T              syn_cvi09                ;         // 0xC93B_8444
    CTOP_CVI_SYN_CVI10_E60_A0_T              syn_cvi10                ;         // 0xC93B_8448
    CTOP_CVI_SYN_CVI11_E60_A0_T              syn_cvi11                ;         // 0xC93B_844C
    CTOP_CVI_SYN_CVI12_E60_A0_T              syn_cvi12                ;         // 0xC93B_8450
    CTOP_CVI_SYN_CVI13_E60_A0_T              syn_cvi13                ;         // 0xC93B_8454
    CTOP_CVI_SYN_CVI14_E60_A0_T              syn_cvi14                ;         // 0xC93B_8458
    CTOP_CVI_SYN_CVI15_E60_A0_T              syn_cvi15                ;         // 0xC93B_845C
    CTOP_CVI_SYN_CVI16_E60_A0_T              syn_cvi16                ;         // 0xC93B_8460
    CTOP_CVI_SYN_CVI17_E60_A0_T              syn_cvi17                ;         // 0xC93B_8464
    CTOP_CVI_SYN_CVI18_E60_A0_T              syn_cvi18                ;         // 0xC93B_8468
    CTOP_CVI_SYN_CVI19_E60_A0_T              syn_cvi19                ;         // 0xC93B_846C
    CTOP_CVI_SYN_CVI20_E60_A0_T              syn_cvi20                ;         // 0xC93B_8470
    CTOP_CVI_SYN_CVI21_E60_A0_T              syn_cvi21                ;         // 0xC93B_8474
    CTOP_CVI_SYN_CVI22_E60_A0_T              syn_cvi22                ;         // 0xC93B_8478
    CTOP_CVI_SYN_CVI23_E60_A0_T              syn_cvi23                ;         // 0xC93B_847C
    CTOP_CVI_SYN_CVI24_E60_A0_T              syn_cvi24                ;         // 0xC93B_8480
    CTOP_CVI_SYN_CVI25_E60_A0_T              syn_cvi25                ;         // 0xC93B_8484
    CTOP_CVI_SYN_CVI26_E60_A0_T              syn_cvi26                ;         // 0xC93B_8488
    CTOP_CVI_SYN_CVI27_E60_A0_T              syn_cvi27                ;         // 0xC93B_848C
    CTOP_CVI_SYN_CVI28_E60_A0_T              syn_cvi28                ;         // 0xC93B_8490
    CTOP_CVI_SYN_CVI29_E60_A0_T              syn_cvi29                ;         // 0xC93B_8494
} CTOP_SYN_CVI_REG_E60_A0_T;
/* 30 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_CVI_E60A0_REG_H_ */

/* from 'E60_CTOP_SYN_Register_Manual_20191211.xlsm'  2019.12.12  KST by LGSiCRDV V3.0B*/

