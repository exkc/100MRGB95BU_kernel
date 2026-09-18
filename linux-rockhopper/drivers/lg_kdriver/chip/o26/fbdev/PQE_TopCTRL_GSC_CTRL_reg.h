#ifndef __PQE_TOP_GSC_CTRL_REG_H__
#define __PQE_TOP_GSC_CTRL_REG_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

// *INDENT-OFF*

/*-----------------------------------------------------------------------------
    0x0000 pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    g0_pic_init                     : 1,    //     0
    g1_pic_init                     : 1,    //     1
    g2_pic_init                     : 1,    //     2
    g3_pic_init                     : 1,    //     3
    g4_pic_init                     : 1,    //     4
    g5_pic_init                     : 1,    //     5
    g6_pic_init                     : 1,    //     6
    g7_pic_init                     : 1,    //     7
                                    : 8,    //  8:15 reserved
    g0_auto_init                    : 1,    //    16
    g1_auto_init                    : 1,    //    17
    g2_auto_init                    : 1,    //    18
    g3_auto_init                    : 1,    //    19
    g4_auto_init                    : 1,    //    20
    g5_auto_init                    : 1,    //    21
    g6_auto_init                    : 1,    //    22
    g7_auto_init                    : 1,    //    23
    g0_pic_init_mask                : 1,    //    24
    g1_pic_init_mask                : 1,    //    25
    g2_pic_init_mask                : 1,    //    26
    g3_pic_init_mask                : 1,    //    27
    g4_pic_init_mask                : 1,    //    28
    g5_pic_init_mask                : 1,    //    29
    g6_pic_init_mask                : 1,    //    30
    g7_pic_init_mask                : 1;    //    31
} GSC_PIC_INIT;

/*-----------------------------------------------------------------------------
    0x0004 pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    g0_pic_start                    : 1,    //     0
    g1_pic_start                    : 1,    //     1
    g2_pic_start                    : 1,    //     2
    g3_pic_start                    : 1,    //     3
    g4_pic_start                    : 1,    //     4
    g5_pic_start                    : 1,    //     5
    g6_pic_start                    : 1,    //     6
    g7_pic_start                    : 1,    //     7
                                    : 8,    //  8:15 reserved
    g0_auto_half_en                 : 1,    //    16
    g1_auto_half_en                 : 1,    //    17
    g2_auto_half_en                 : 1,    //    18
    g3_auto_half_en                 : 1,    //    19
    g4_auto_half_en                 : 1,    //    20
    g5_auto_half_en                 : 1,    //    21
    g6_auto_half_en                 : 1,    //    22
    g7_auto_half_en                 : 1,    //    23
    g0_pic_start_mask               : 1,    //    24
    g1_pic_start_mask               : 1,    //    25
    g2_pic_start_mask               : 1,    //    26
    g3_pic_start_mask               : 1,    //    27
    g4_pic_start_mask               : 1,    //    28
    g5_pic_start_mask               : 1,    //    29
    g6_pic_start_mask               : 1,    //    30
    g7_pic_start_mask               : 1;    //    31
} GSC_PIC_START;

/*-----------------------------------------------------------------------------
    0x0008 ctrl_auto_init ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    idx_src_g0_auto_init            : 3,    //  0: 2
                                    : 1,    //     3 reserved
    idx_src_g1_auto_init            : 3,    //  4: 6
                                    : 1,    //     7 reserved
    idx_src_g2_auto_init            : 3,    //  8:10
                                    : 1,    //    11 reserved
    idx_src_g3_auto_init            : 3,    // 12:14
                                    : 1,    //    15 reserved
    idx_src_g4_auto_init            : 3,    // 16:18
                                    : 1,    //    19 reserved
    idx_src_g5_auto_init            : 3,    // 20:22
                                    : 1,    //    23 reserved
    idx_src_g6_auto_init            : 3,    // 24:26
                                    : 1,    //    27 reserved
    idx_src_g7_auto_init            : 3;    // 28:30
} GSC_CTRL_AUTO_INIT;

/*-----------------------------------------------------------------------------
    0x000c ctrl_intr_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    idx_src_i0_intr_pulse           : 3,    //  0: 2
    sel_src_i0_intr_pulse           : 1,    //     3
    idx_src_i1_intr_pulse           : 3,    //  4: 6
    sel_src_i1_intr_pulse           : 1,    //     7
    idx_src_i2_intr_pulse           : 3,    //  8:10
    sel_src_i2_intr_pulse           : 1,    //    11
    idx_src_i3_intr_pulse           : 3,    // 12:14
    sel_src_i3_intr_pulse           : 1,    //    15
    idx_src_i4_intr_pulse           : 3,    // 16:18
    sel_src_i4_intr_pulse           : 1,    //    19
    idx_src_i5_intr_pulse           : 3,    // 20:22
    sel_src_i5_intr_pulse           : 1,    //    23
    idx_src_i6_intr_pulse           : 3,    // 24:26
    sel_src_i6_intr_pulse           : 1,    //    27
    idx_src_i7_intr_pulse           : 3,    // 28:30
    sel_src_i7_intr_pulse           : 1;    //    31
} GSC_CTRL_INTR_PULSE;

/*-----------------------------------------------------------------------------
    0x0010 intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    intr_i0_intr_pulse              : 1,    //     0
    intr_i1_intr_pulse              : 1,    //     1
    intr_i2_intr_pulse              : 1,    //     2
    intr_i3_intr_pulse              : 1,    //     3
    intr_i4_intr_pulse              : 1,    //     4
    intr_i5_intr_pulse              : 1,    //     5
    intr_i6_intr_pulse              : 1,    //     6
    intr_i7_intr_pulse              : 1,    //     7
    intr_g0_pic_end                 : 1,    //     8
    intr_g1_pic_end                 : 1,    //     9
    intr_g2_pic_end                 : 1,    //    10
    intr_g3_pic_end                 : 1,    //    11
    intr_g4_pic_end                 : 1,    //    12
    intr_g5_pic_end                 : 1,    //    13
    intr_g6_pic_end                 : 1,    //    14
    intr_g7_pic_end                 : 1,    //    15
                                    : 4,    // 16:19 reserved
    intr_mif_gsc0                   : 1,    //    20
    intr_mif_gsc1                   : 1;    //    21
} GSC_INTR_REG;

/*-----------------------------------------------------------------------------
    0x0014 intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mask_i0_src_pulse               : 1,    //     0
    mask_i1_src_pulse               : 1,    //     1
    mask_i2_src_pulse               : 1,    //     2
    mask_i3_src_pulse               : 1,    //     3
    mask_i4_src_pulse               : 1,    //     4
    mask_i5_src_pulse               : 1,    //     5
    mask_i6_src_pulse               : 1,    //     6
    mask_i7_src_pulse               : 1,    //     7
    mask_g0_pic_end                 : 1,    //     8
    mask_g1_pic_end                 : 1,    //     9
    mask_g2_pic_end                 : 1,    //    10
    mask_g3_pic_end                 : 1,    //    11
    mask_g4_pic_end                 : 1,    //    12
    mask_g5_pic_end                 : 1,    //    13
    mask_g6_pic_end                 : 1,    //    14
    mask_g7_pic_end                 : 1,    //    15
                                    : 4,    // 16:19 reserved
    mask_mif_gsc0                   : 1,    //    20
    mask_mif_gsc1                   : 1;    //    21
} GSC_INTR_MASK;

/*-----------------------------------------------------------------------------
    0x0018 intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mux_i0_src_pulse                : 1,    //     0
    mux_i1_src_pulse                : 1,    //     1
    mux_i2_src_pulse                : 1,    //     2
    mux_i3_src_pulse                : 1,    //     3
    mux_i4_src_pulse                : 1,    //     4
    mux_i5_src_pulse                : 1,    //     5
    mux_i6_src_pulse                : 1,    //     6
    mux_i7_src_pulse                : 1,    //     7
    mux_g0_pic_end                  : 1,    //     8
    mux_g1_pic_end                  : 1,    //     9
    mux_g2_pic_end                  : 1,    //    10
    mux_g3_pic_end                  : 1,    //    11
    mux_g4_pic_end                  : 1,    //    12
    mux_g5_pic_end                  : 1,    //    13
    mux_g6_pic_end                  : 1,    //    14
    mux_g7_pic_end                  : 1,    //    15
                                    : 4,    // 16:19 reserved
    mux_mif_gsc0                    : 1,    //    20
    mux_mif_gsc1                    : 1;    //    21
} GSC_INTR_MUX;

/*-----------------------------------------------------------------------------
    0x001c intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    en_i0_src_pulse                 : 1,    //     0
    en_i1_src_pulse                 : 1,    //     1
    en_i2_src_pulse                 : 1,    //     2
    en_i3_src_pulse                 : 1,    //     3
    en_i4_src_pulse                 : 1,    //     4
    en_i5_src_pulse                 : 1,    //     5
    en_i6_src_pulse                 : 1,    //     6
    en_i7_src_pulse                 : 1,    //     7
    en_g0_pic_end                   : 1,    //     8
    en_g1_pic_end                   : 1,    //     9
    en_g2_pic_end                   : 1,    //    10
    en_g3_pic_end                   : 1,    //    11
    en_g4_pic_end                   : 1,    //    12
    en_g5_pic_end                   : 1,    //    13
    en_g6_pic_end                   : 1,    //    14
    en_g7_pic_end                   : 1,    //    15
                                    : 4,    // 16:19 reserved
    en_mif_gsc0                     : 1,    //    20
    en_mif_gsc1                     : 1;    //    21
} GSC_INTR_EN;

/*-----------------------------------------------------------------------------
    0x0070 sub_bus_flush ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_s0_flush_en             : 1,    //     0
    reg_gsc_s1_flush_en             : 1,    //     1
                                    : 2,    //  2: 3 reserved
    reg_gsc_a0_flush_en             : 1,    //     4
    reg_gsc_a1_flush_en             : 1,    //     5
    reg_gsc_a2_flush_en             : 1,    //     6
    reg_gsc_a3_flush_en             : 1,    //     7
    reg_gsc_sub_bus_flush_det       : 6;    //  8:13
} GSC_SUB_BUS_FLUSH;

/*-----------------------------------------------------------------------------
    0x0074 sub_bus_flush_status ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc_s0_flush_done           : 1,    //     0
    reg_gsc_s1_flush_done           : 1,    //     1
                                    : 2,    //  2: 3 reserved
    reg_gsc_a0_flush_done           : 1,    //     4
    reg_gsc_a1_flush_done           : 1,    //     5
    reg_gsc_a2_flush_done           : 1,    //     6
    reg_gsc_a3_flush_done           : 1;    //     7
} GSC_SUB_BUS_FLUSH_STATUS;

/*-----------------------------------------------------------------------------
    0x0078 ctrl_subus_axi_mux ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mif0_bus_axi_mux                : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    mif1_bus_axi_mux                : 2,    //  4: 5
                                    : 2,    //  6: 7 reserved
    afbc_afrc0_bus_axi_mux          : 2,    //  8: 9
                                    : 2,    // 10:11 reserved
    afbc_afrc1_bus_axi_mux          : 2,    // 12:13
                                    : 2,    // 14:15 reserved
    afbc_afrc2_bus_axi_mux          : 2,    // 16:17
                                    : 2,    // 18:19 reserved
    afbc_afrc3_bus_axi_mux          : 2,    // 20:21
                                    : 6,    // 22:27 reserved
    gsc_bus_axi_mux_on              : 2;    // 28:29
} GSC_CTRL_SUBUS_AXI_MUX;

/*-----------------------------------------------------------------------------
    0x007c ctrl_auto_init_afbc0 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_afbc0_init_en               : 1,    //     0
                                    : 3,    //  1: 3 reserved
    reg_afbc0_auto_init_en          : 1,    //     4
                                    : 3,    //  5: 7 reserved
    reg_afbc0_auto_start_en         : 1,    //     8
                                    : 3,    //  9:11 reserved
    reg_afbc0_swreset_sel           : 1,    //    12
                                    : 2,    // 13:14 reserved
    reg_afbc0_partial_ack_en        : 1,    //    15
    reg_afbc1_init_en               : 1,    //    16
                                    : 3,    // 17:19 reserved
    reg_afbc1_auto_init_en          : 1,    //    20
                                    : 3,    // 21:23 reserved
    reg_afbc1_auto_start_en         : 1,    //    24
                                    : 3,    // 25:27 reserved
    reg_afbc1_swreset_sel           : 1,    //    28
                                    : 2,    // 29:30 reserved
    reg_afbc1_partial_ack_en        : 1;    //    31
} GSC_CTRL_AUTO_INIT_AFBC0;

/*-----------------------------------------------------------------------------
    0x0080 ctrl_auto_init_afbc1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_afbc2_init_en               : 1,    //     0
                                    : 3,    //  1: 3 reserved
    reg_afbc2_auto_init_en          : 1,    //     4
                                    : 3,    //  5: 7 reserved
    reg_afbc2_auto_start_en         : 1,    //     8
                                    : 3,    //  9:11 reserved
    reg_afbc2_swreset_sel           : 1,    //    12
                                    : 2,    // 13:14 reserved
    reg_afbc2_partial_ack_en        : 1,    //    15
    reg_afbc3_init_en               : 1,    //    16
                                    : 3,    // 17:19 reserved
    reg_afbc3_auto_init_en          : 1,    //    20
                                    : 3,    // 21:23 reserved
    reg_afbc3_auto_start_en         : 1,    //    24
                                    : 3,    // 25:27 reserved
    reg_afbc3_swreset_sel           : 1,    //    28
                                    : 2,    // 29:30 reserved
    reg_afbc3_partial_ack_en        : 1;    //    31
} GSC_CTRL_AUTO_INIT_AFBC1;

/*-----------------------------------------------------------------------------
    0x0084 ctrl_out_pic_end_sel ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc_y_pic_end_sel           : 1,    //     0
                                    : 3,    //  1: 3 reserved
    reg_fmc_c_pic_end_sel           : 1,    //     4
                                    : 3,    //  5: 7 reserved
    reg_u0_y_pic_end_sel            : 1,    //     8
                                    : 3,    //  9:11 reserved
    reg_u0_c_pic_end_sel            : 1,    //    12
                                    : 3,    // 13:15 reserved
    reg_u1_y_pic_end_sel            : 3,    // 16:18
                                    : 1,    //    19 reserved
    reg_u1_c_pic_end_sel            : 3;    // 20:22
} GSC_CTRL_OUT_PIC_END_SEL;

/*-----------------------------------------------------------------------------
    0x0088 ctrl_osc2_pic_init_sel ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_osc2_pic_init_sel           : 1;    //     0
} GSC_CTRL_OSC2_PIC_INIT_SEL;

/*-----------------------------------------------------------------------------
    0x008c ctrl_osc3_pic_init_sel ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_osc3_pic_init_sel           : 1;    //     0
} GSC_CTRL_OSC3_PIC_INIT_SEL;

/*-----------------------------------------------------------------------------
    0x0090 ctrl_dpath ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gate_cmd_len0               : 1,    //     0
                                    : 3,    //  1: 3 reserved
    reg_gate_cmd_len1               : 1,    //     4
                                    : 3,    //  5: 7 reserved
    reg_gate_cmd_len2               : 1,    //     8
                                    : 3,    //  9:11 reserved
    reg_gate_cmd_len3               : 1,    //    12
                                    : 3,    // 13:15 reserved
    unaligned_addr_en               : 1;    //    16
} GSC_CTRL_DPATH;

/*-----------------------------------------------------------------------------
    0x0094 ctrl_gate_gsc ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gate_tx_cco_en              : 1,    //     0
    reg_gate_tx_cco_dp_sel          : 3,    //  1: 3
    reg_gate_tx_fmc_y_en            : 1,    //     4
    reg_gate_tx_fmc_y_dp_sel        : 3,    //  5: 7
    reg_gate_tx_fmc_c_en            : 1,    //     8
    reg_gate_tx_fmc_c_dp_sel        : 3;    //  9:11
} GSC_CTRL_GATE_GSC;

/*-----------------------------------------------------------------------------
    0x0098 ctrl_reg_update1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_update_ctrl_osc2            : 5,    //  0: 4
    reg_update_ctrl_osc3            : 5,    //  5: 9
    reg_update_ctrl_osd             : 5,    // 10:14
    reg_update_ctrl_smth            : 5,    // 15:19
    reg_update_ctrl_glb             : 5,    // 20:24
    reg_update_ctrl_vlb             : 5;    // 25:29
} GSC_CTRL_REG_UPDATE1;

/*-----------------------------------------------------------------------------
    0x009c ctrl_reg_update0 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_update_ctrl_core            : 5,    //  0: 4
    reg_update_ctrl_gpd             : 5,    //  5: 9
    reg_update_ctrl_osc0_y          : 5,    // 10:14
    reg_update_ctrl_osc0_c          : 5,    // 15:19
    reg_update_ctrl_osc1_y          : 5,    // 20:24
    reg_update_ctrl_osc1_c          : 5;    // 25:29
} GSC_CTRL_REG_UPDATE0;

/*-----------------------------------------------------------------------------
    0x00a0 ctrl_gmau2 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    subbus_a0_ask_r_cmd_dly_cnt     : 8,    //  0: 7
    subbus_a1_ask_r_cmd_dly_cnt     : 8,    //  8:15
    subbus_a2_ask_r_cmd_dly_cnt     : 8,    // 16:23
    subbus_a3_ask_r_cmd_dly_cnt     : 8;    // 24:31
} GSC_CTRL_GMAU2;

/*-----------------------------------------------------------------------------
    0x00a8 ctrl_cg_on ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_smth_de_clk_cg              : 1,    //     0
    reg_osc0_y_de_clk_cg            : 1,    //     1
    reg_osc0_c_de_clk_cg            : 1,    //     2
    reg_osc1_y_de_clk_cg            : 1,    //     3
    reg_osc1_c_de_clk_cg            : 1,    //     4
    reg_osc2_y_de_clk_cg            : 1,    //     5
    reg_osc2_c_de_clk_cg            : 1,    //     6
    reg_osc3_y_de_clk_cg            : 1,    //     7
    reg_osc3_c_de_clk_cg            : 1,    //     8
    reg_osd_de_clk_cg               : 1,    //     9
    reg_glb_de_clk_cg               : 1,    //    10
    reg_vlb_de_clk_cg               : 1;    //    11
} GSC_CTRL_CG_ON;

/*-----------------------------------------------------------------------------
    0x00ac ctrl_reg_update2 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_update_ctrl_out_u0          : 5,    //  0: 4
    reg_update_ctrl_out_u1          : 5,    //  5: 9
    reg_update_ctrl_out_fmc         : 5;    // 10:14
} GSC_CTRL_REG_UPDATE2;

/*-----------------------------------------------------------------------------
    0x00b0 ctrl_block ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_path_reset_en_u0_y          : 1,    //     0
    reg_path_reset_en_u0_c          : 1,    //     1
    reg_path_reset_en_u1_y          : 1,    //     2
    reg_path_reset_en_u1_c          : 1,    //     3
    reg_path_reset_en_cco           : 1,    //     4
    reg_path_reset_en_fmc           : 1,    //     5
                                    : 2,    //  6: 7 reserved
    reg_vlb_pic_init_sel            : 2,    //  8: 9
    reg_sel_mif_cmd_dly             : 1,    //    10
                                    : 1,    //    11 reserved
    reg_gpd_in_mif_mux              : 2,    // 12:13
                                    : 2,    // 14:15 reserved
    reg_sel_timer_reset_src         : 3,    // 16:18
                                    : 1,    //    19 reserved
    reg_sel_timer_reset_disp        : 3,    // 20:22
                                    : 1,    //    23 reserved
    reg_bus_disp_sync_sel           : 3,    // 24:26
                                    : 1,    //    27 reserved
    reg_bus_src_sync_sel            : 3;    // 28:30
} GSC_CTRL_BLOCK;

/*-----------------------------------------------------------------------------
    0x00b4 ctrl_block1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_mif_axuser              : 6,    //  0: 5
                                    : 6,    //  6:11 reserved
    reg_osc1_c_mif_pg_en            : 1,    //    12
                                    : 3,    // 13:15 reserved
    reg_gate_tx_u2_y_en             : 1,    //    16
    reg_gate_tx_u2_y_dp_sel         : 3,    // 17:19
    reg_gate_tx_u2_c_en             : 1,    //    20
    reg_gate_tx_u2_c_dp_sel         : 3,    // 21:23
    reg_afbc_afrc_0_sel             : 1,    //    24
    reg_afbc_afrc_1_sel             : 1,    //    25
    reg_afbc_afrc_2_sel             : 1,    //    26
    reg_afbc_afrc_3_sel             : 1;    //    27
} GSC_CTRL_BLOCK1;

/*-----------------------------------------------------------------------------
    0x00b8 ctrl_block2 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc_vsd_info                    : 4,    //  0: 3
    fmc_gsc_info                    : 4,    //  4: 7
    fmc_gsc_info_sel                : 1;    //     8
} GSC_CTRL_BLOCK2;

/*-----------------------------------------------------------------------------
    0x00bc ctrl_axi_user ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gsc0_aruser                     : 4,    //  0: 3
    gsc1_aruser                     : 4,    //  4: 7
    gsc2_aruser                     : 4,    //  8:11
    gsc3_aruser                     : 4,    // 12:15
    gsc4_aruser                     : 4,    // 16:19
    gsc5_aruser                     : 4;    // 20:23
} GSC_CTRL_AXI_USER;

/*-----------------------------------------------------------------------------
    0x00c0 pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G0_TIMER;

/*-----------------------------------------------------------------------------
    0x00c4 pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G1_TIMER;

/*-----------------------------------------------------------------------------
    0x00c8 pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G2_TIMER;

/*-----------------------------------------------------------------------------
    0x00cc pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G3_TIMER;

/*-----------------------------------------------------------------------------
    0x00d0 pic_init_g4_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G4_TIMER;

/*-----------------------------------------------------------------------------
    0x00d4 pic_init_g5_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G5_TIMER;

/*-----------------------------------------------------------------------------
    0x00d8 pic_init_g6_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G6_TIMER;

/*-----------------------------------------------------------------------------
    0x00dc pic_init_g7_timer ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pic_init_timer                  :24,    //  0:23
    start_interval_mode_en          : 1,    //    24
    start_interval_mode             : 3,    // 25:27
    pic_init_width_mode_en          : 1,    //    28
    pic_init_width_mode             : 2,    // 29:30
    wait_pic_end_en                 : 1;    //    31
} GSC_PIC_INIT_G7_TIMER;

/*-----------------------------------------------------------------------------
    0x00e0 ctrl_block4 ''
------------------------------------------------------------------------------*/
/*    no field */

/*-----------------------------------------------------------------------------
    0x00e4 dbg_timer_run ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    info_timer_run                  :24,    //  0:23
    idx_end_src                     : 3,    // 24:26
    sel_end_src                     : 1,    //    27
    idx_start_src                   : 3,    // 28:30
    sel_start_src                   : 1;    //    31
} GSC_DBG_TIMER_RUN;

/*-----------------------------------------------------------------------------
    0x00e8 gx_pic_start_end_proc ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rw_gx_pic_start_end             : 1,    //     0
    dly_gx_pic_start_end            :23,    //  1:23
    ctrl_gx_pic_start_end           : 3,    // 24:26
    idx_gx_pic_start_end            : 5;    // 27:31
} GSC_GX_PIC_START_END_PROC;

/*-----------------------------------------------------------------------------
    0x00ec ctrl_monitor ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctrl_monitor                    : 4;    //  0: 3
} GSC_CTRL_MONITOR;

/*-----------------------------------------------------------------------------
    0x00f0 ctrl_pic_end ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    g0_pic_end_en                   : 1,    //     0
    g1_pic_end_en                   : 1,    //     1
    g2_pic_end_en                   : 1,    //     2
    g3_pic_end_en                   : 1,    //     3
    g4_pic_end_en                   : 1,    //     4
    g5_pic_end_en                   : 1,    //     5
    g6_pic_end_en                   : 1,    //     6
    g7_pic_end_en                   : 1,    //     7
    b0_pic_end_en                   : 1,    //     8
    b1_pic_end_en                   : 1,    //     9
    b2_pic_end_en                   : 1,    //    10
    b3_pic_end_en                   : 1,    //    11
    b4_pic_end_en                   : 1,    //    12
    b5_pic_end_en                   : 1,    //    13
    b6_pic_end_en                   : 1,    //    14
    b7_pic_end_en                   : 1,    //    15
    pic_end_g0_force_en             : 1,    //    16
    pic_end_g1_force_en             : 1,    //    17
    pic_end_g2_force_en             : 1,    //    18
    pic_end_g3_force_en             : 1,    //    19
    pic_end_g4_force_en             : 1,    //    20
    pic_end_g5_force_en             : 1,    //    21
    pic_end_g6_force_en             : 1,    //    22
    pic_end_g7_force_en             : 1,    //    23
    pic_end_g0_force_value          : 1,    //    24
    pic_end_g1_force_value          : 1,    //    25
    pic_end_g2_force_value          : 1,    //    26
    pic_end_g3_force_value          : 1,    //    27
    pic_end_g4_force_value          : 1,    //    28
    pic_end_g5_force_value          : 1,    //    29
    pic_end_g6_force_value          : 1,    //    30
    pic_end_g7_force_value          : 1;    //    31
} GSC_CTRL_PIC_END;

/*-----------------------------------------------------------------------------
    0x00f4 info_pic_end ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    g0_pic_end                      : 1,    //     0
    g1_pic_end                      : 1,    //     1
    g2_pic_end                      : 1,    //     2
    g3_pic_end                      : 1,    //     3
    g4_pic_end                      : 1,    //     4
    g5_pic_end                      : 1,    //     5
    g6_pic_end                      : 1,    //     6
    g7_pic_end                      : 1,    //     7
    b0_pic_end                      : 1,    //     8
    b1_pic_end                      : 1,    //     9
    b2_pic_end                      : 1,    //    10
    b3_pic_end                      : 1,    //    11
    b4_pic_end                      : 1,    //    12
    b5_pic_end                      : 1,    //    13
    b6_pic_end                      : 1,    //    14
    b7_pic_end                      : 1,    //    15
    g0_pic_end_init                 : 1,    //    16
    g1_pic_end_init                 : 1,    //    17
    g2_pic_end_init                 : 1,    //    18
    g3_pic_end_init                 : 1,    //    19
    g4_pic_end_init                 : 1,    //    20
    g5_pic_end_init                 : 1,    //    21
    g6_pic_end_init                 : 1,    //    22
    g7_pic_end_init                 : 1;    //    23
} GSC_INFO_PIC_END;

/*-----------------------------------------------------------------------------
    0x00f8 ctrl_gpio ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rst_async_bridge_u0_y           : 1,    //     0
    rst_async_bridge_u0_c           : 1,    //     1
    rst_async_bridge_u1_y           : 1,    //     2
    rst_async_bridge_u1_c           : 1,    //     3
    rst_async_bridge_fmc            : 1,    //     4
                                    : 1,    //     5 reserved
    rst_async_bridge_cco            : 1,    //     6
                                    : 1,    //     7 reserved
    reg_gate_tx_u0_y_en             : 1,    //     8
    reg_gate_tx_u0_y_dp_sel         : 3,    //  9:11
    reg_gate_tx_u0_c_en             : 1,    //    12
    reg_gate_tx_u0_c_dp_sel         : 3,    // 13:15
    reg_gate_tx_u1_y_en             : 1,    //    16
    reg_gate_tx_u1_y_dp_sel         : 3,    // 17:19
    reg_gate_tx_u1_c_en             : 1,    //    20
    reg_gate_tx_u1_c_dp_sel         : 3,    // 21:23
    reg_gate_rx_m0_y_en             : 1,    //    24
    reg_gate_rx_m0_c_en             : 1,    //    25
    reg_gate_rx_m1_y_en             : 1,    //    26
    reg_gate_rx_m1_c_en             : 1,    //    27
    reg_gate_rx_m2_y_en             : 1,    //    28
    reg_gate_rx_m2_c_en             : 1,    //    29
    reg_gate_rx_cco_en              : 1;    //    30
} GSC_CTRL_GPIO;

/*-----------------------------------------------------------------------------
    0x00fc ctrl_gmau ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ask_cmd_dly_cnt_r0              : 4,    //  0: 3
                                    : 4,    //  4: 7 reserved
    ask_cmd_dly_cnt_r1              : 4,    //  8:11
                                    : 4,    // 12:15 reserved
    ask_to_cnt                      : 8;    // 16:23
} GSC_CTRL_GMAU;

typedef struct {
    GSC_PIC_INIT                            pic_init                        ;    // 0x0000 : ''
    GSC_PIC_START                           pic_start                       ;    // 0x0004 : ''
    GSC_CTRL_AUTO_INIT                      ctrl_auto_init                  ;    // 0x0008 : ''
    GSC_CTRL_INTR_PULSE                     ctrl_intr_pulse                 ;    // 0x000c : ''
    GSC_INTR_REG                            intr_reg                        ;    // 0x0010 : ''
    GSC_INTR_MASK                           intr_mask                       ;    // 0x0014 : ''
    GSC_INTR_MUX                            intr_mux                        ;    // 0x0018 : ''
    GSC_INTR_EN                             intr_en                         ;    // 0x001c : ''
    UINT32                                                   __rsvd_00[  20];    // 0x0020 ~ 0x006c
    GSC_SUB_BUS_FLUSH                       sub_bus_flush                   ;    // 0x0070 : ''
    GSC_SUB_BUS_FLUSH_STATUS                sub_bus_flush_status            ;    // 0x0074 : ''
    GSC_CTRL_SUBUS_AXI_MUX                  ctrl_subus_axi_mux              ;    // 0x0078 : ''
    GSC_CTRL_AUTO_INIT_AFBC0                ctrl_auto_init_afbc0            ;    // 0x007c : ''
    GSC_CTRL_AUTO_INIT_AFBC1                ctrl_auto_init_afbc1            ;    // 0x0080 : ''
    GSC_CTRL_OUT_PIC_END_SEL                ctrl_out_pic_end_sel            ;    // 0x0084 : ''
    GSC_CTRL_OSC2_PIC_INIT_SEL              ctrl_osc2_pic_init_sel          ;    // 0x0088 : ''
    GSC_CTRL_OSC3_PIC_INIT_SEL              ctrl_osc3_pic_init_sel          ;    // 0x008c : ''
    GSC_CTRL_DPATH                          ctrl_dpath                      ;    // 0x0090 : ''
    GSC_CTRL_GATE_GSC                       ctrl_gate_gsc                   ;    // 0x0094 : ''
    GSC_CTRL_REG_UPDATE1                    ctrl_reg_update1                ;    // 0x0098 : ''
    GSC_CTRL_REG_UPDATE0                    ctrl_reg_update0                ;    // 0x009c : ''
    GSC_CTRL_GMAU2                          ctrl_gmau2                      ;    // 0x00a0 : ''
    UINT32                                                   __rsvd_01[   1];    // 0x00a4
    GSC_CTRL_CG_ON                          ctrl_cg_on                      ;    // 0x00a8 : ''
    GSC_CTRL_REG_UPDATE2                    ctrl_reg_update2                ;    // 0x00ac : ''
    GSC_CTRL_BLOCK                          ctrl_block                      ;    // 0x00b0 : ''
    GSC_CTRL_BLOCK1                         ctrl_block1                     ;    // 0x00b4 : ''
    GSC_CTRL_BLOCK2                         ctrl_block2                     ;    // 0x00b8 : ''
    GSC_CTRL_AXI_USER                       ctrl_axi_user                   ;    // 0x00bc : ''
    GSC_PIC_INIT_G0_TIMER                   pic_init_g0_timer               ;    // 0x00c0 : ''
    GSC_PIC_INIT_G1_TIMER                   pic_init_g1_timer               ;    // 0x00c4 : ''
    GSC_PIC_INIT_G2_TIMER                   pic_init_g2_timer               ;    // 0x00c8 : ''
    GSC_PIC_INIT_G3_TIMER                   pic_init_g3_timer               ;    // 0x00cc : ''
    GSC_PIC_INIT_G4_TIMER                   pic_init_g4_timer               ;    // 0x00d0 : ''
    GSC_PIC_INIT_G5_TIMER                   pic_init_g5_timer               ;    // 0x00d4 : ''
    GSC_PIC_INIT_G6_TIMER                   pic_init_g6_timer               ;    // 0x00d8 : ''
    GSC_PIC_INIT_G7_TIMER                   pic_init_g7_timer               ;    // 0x00dc : ''
    UINT32                                  ctrl_block4                     ;    // 0x00e0 : ''
    GSC_DBG_TIMER_RUN                       dbg_timer_run                   ;    // 0x00e4 : ''
    GSC_GX_PIC_START_END_PROC               gx_pic_start_end_proc           ;    // 0x00e8 : ''
    GSC_CTRL_MONITOR                        ctrl_monitor                    ;    // 0x00ec : ''
    GSC_CTRL_PIC_END                        ctrl_pic_end                    ;    // 0x00f0 : ''
    GSC_INFO_PIC_END                        info_pic_end                    ;    // 0x00f4 : ''
    GSC_CTRL_GPIO                           ctrl_gpio                       ;    // 0x00f8 : ''
    GSC_CTRL_GMAU                           ctrl_gmau                       ;    // 0x00fc : ''
} GSC_CTRL_O26_REG_T;
/* 43 regs, 43 types */

/* 43 regs, 43 types in Total*/

// *INDENT-ON*

#define GSC_CTRL_RdFL(_r)           ((g_gsc_ctrl_o26_reg_shadow->_r)=(g_gsc_ctrl_o26_reg->_r))
#define GSC_CTRL_WrFL(_r)           ((g_gsc_ctrl_o26_reg->_r)=(g_gsc_ctrl_o26_reg_shadow->_r))

#define GSC_CTRL_Rd(_r)             *((UINT32*)(&(g_gsc_ctrl_o26_reg_shadow->_r)))
#define GSC_CTRL_Wr(_r,_v)          ((GSC_CTRL_Rd(_r))=((UINT32)(_v)))

#define GSC_CTRL_Rd01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (_v01) = (g_gsc_ctrl_o26_reg_shadow->_r._f01);  \
                                } while(0)

#define GSC_CTRL_Rd02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (_v01) = (g_gsc_ctrl_o26_reg_shadow->_r._f01);  \
                                    (_v02) = (g_gsc_ctrl_o26_reg_shadow->_r._f02);  \
                                } while(0)

#define GSC_CTRL_Wr01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (g_gsc_ctrl_o26_reg_shadow->_r._f01) = (_v01);  \
                                } while(0)

#define GSC_CTRL_Wr02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (g_gsc_ctrl_o26_reg_shadow->_r._f01) = (_v01);  \
                                    (g_gsc_ctrl_o26_reg_shadow->_r._f02) = (_v02);  \
                                } while(0)

extern volatile GSC_CTRL_O26_REG_T* g_gsc_ctrl_o26_reg;
extern GSC_CTRL_O26_REG_T*          g_gsc_ctrl_o26_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O26-A0_PQE_TopCTRL_reg_man_GSC_CTRL.csv' 20241210 18:02:26 KST by getregs v2.9 */
