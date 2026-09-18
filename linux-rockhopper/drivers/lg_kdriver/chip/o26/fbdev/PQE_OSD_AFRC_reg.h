#ifndef __PQE_OSD_AFRC_REG_H__
#define __PQE_OSD_AFRC_REG_H__

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
    0x0000 ctrl_afrc_0 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    start                           : 1,    //     0
                                    : 3,    //  1: 3 reserved
    ready                           : 3,    //  4: 6
                                    : 9,    //  7:15 reserved
    sw_reset                        : 1,    //    16
    sw_reset_fifo                   : 1,    //    17
                                    : 2,    // 18:19 reserved
    sw_reset_ack                    : 1,    //    20
                                    : 2,    // 21:22 reserved
    pl_gmau_pri_gen_en              : 1,    //    23
    gmau_arb_sw_reset               : 1,    //    24
    update_ready_flag_en            : 1,    //    25
    update_ready_flag               : 1,    //    26
                                    : 1,    //    27 reserved
    flip_mode                       : 1;    //    28
} CTRL_AFRC_0;

/*-----------------------------------------------------------------------------
    0x0004 ctrl_afrc_1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    barrel_rptr_sel             : 1,    //     0
    barrel_rptr_mode            : 1,    //     1
    dec_sram_rd_start_mode      : 1,    //     2
    dec_sram_rd_start_point     : 1,    //     3
    dec_sram_ptr_use            : 1;    //     4
} CTRL_AFRC_1;

/*-----------------------------------------------------------------------------
    0x0008 ctrl_afrc_2 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    col_format                  : 4,    //  0: 3
    bit_depth                   : 5,    //  4: 8
                                : 3,    //  9:11 reserved
    comp_size                   : 6,    // 12:17
                                : 2,    // 18:19 reserved
    partial_decode              : 2,    // 20:21
                                : 2,    // 22:23 reserved
    codec_params                : 8;    // 24:31
} CTRL_AFRC_2;

/*-----------------------------------------------------------------------------
    0x0010 ctrl_afrc_4 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_data_base                ;       // 31: 0
} CTRL_AFRC_4;

/*-----------------------------------------------------------------------------
    0x0014 ctrl_afrc_5 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    start_x                     :12,    //  0:11
                                : 4,    // 12:15 reserved
    start_y                     :12;    // 16:27
} CTRL_AFRC_5;

/*-----------------------------------------------------------------------------
    0x0018 ctrl_afrc_6 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    end_x                       :12,    //  0:11
                                : 4,    // 12:15 reserved
    end_y                       :12;    // 16:27
} CTRL_AFRC_6;

/*-----------------------------------------------------------------------------
    0x001c ctrl_afrc_7 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    img_width                   :12;    //  0:11
} CTRL_AFRC_7;

/*-----------------------------------------------------------------------------
    0x0020 ctrl_afrc_8 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    line_wait_cnt               :16,    //  0:15
    ignore_q_full               : 1;    //    16
} CTRL_AFRC_8;

/*-----------------------------------------------------------------------------
    0x0024 ctrl_afrc_9 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    afrc_pattern_en                 : 1,    //     0
    afrc_pattern_valid_mode         : 1,    //     1
                                    : 2,    //  2: 3 reserved
    afrc_pattern_mode               : 4;    //  4: 7
} CTRL_AFRC_9;

/*-----------------------------------------------------------------------------
    0x0028 ctrl_afrc_a ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_gmau_dly_cnt                 :16,    //  0:15
    pl_gmau_cmd_val_dly_cnt         :16;    // 16:31
} CTRL_AFRC_A;

/*-----------------------------------------------------------------------------
    0x002c ctrl_afrc_b ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_gmau_pri1                    : 4,    //  0: 3
                                    : 4,    //  4: 7 reserved
    pl_gmau_pri2                    : 4;    //  8:11
} CTRL_AFRC_B;

/*-----------------------------------------------------------------------------
    0x0030 ctrl_afrc_c ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_gmau_txid                    : 4,    //  0: 3
    pl_endian_sw                    : 4,    //  4: 7
                                    :12,    //  8:19 reserved
    pl_endian_arb                   : 1;    //    20
} CTRL_AFRC_C;

/*-----------------------------------------------------------------------------
    0x0034 ctrl_afrc_d ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    port0_max_cnt                   : 6,    //  0: 5
                                    : 2,    //  6: 7 reserved
    port1_max_cnt                   : 6,    //  8:13
                                    : 2,    // 14:15 reserved
    port2_max_cnt                   : 6;    // 16:21
} CTRL_AFRC_D;

/*-----------------------------------------------------------------------------
    0x0038 ctrl_afrc_e ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_stride                       ;       // 31: 0
} CTRL_AFRC_E;

/*-----------------------------------------------------------------------------
    0x0048 ctrl_afrc_12 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_check_timer                  :16,    //  0:15
    pl_period_value                 :16;    // 16:31
} CTRL_AFRC_12;

/*-----------------------------------------------------------------------------
    0x004c ctrl_afrc_13 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    afrc0_pl_cmd_info           : 2,    //  0: 1
    afrc0_pl_mode_cmd_info      : 2,    //  2: 3
                                : 1,    //     4 reserved
    afrc0_pl_start_sel          : 2,    //  5: 6
    afrc0_pl_mode_step          : 1;    //     7
} CTRL_AFRC_13;

/*-----------------------------------------------------------------------------
    0x0050 ctrl_afrc_14 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pl_data_end                    ;           // 31: 0
} CTRL_AFRC_14;

/*-----------------------------------------------------------------------------
    0x0060 info_debug_top_00 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ready_afrc                      : 3,    //  0: 2
    i_mb_rd_q_full                  : 1,    //     3
    o_mb_rd_valid                   : 1,    //     4
    o_mb_rd_done                    : 1;    //     5
} INFO_DEBUG_TOP_00;

/*-----------------------------------------------------------------------------
    0x0064 info_debug_req_00 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    state                           : 3,    //  0: 2
                                    : 1,    //     3 reserved
    state_cmd                       : 3,    //  4: 6
                                    : 1,    //     7 reserved
    state_load                      : 2,    //  8: 9
                                    : 2,    // 10:11 reserved
    w_fifo_full                     : 1,    //    12
    w_posx_last_cmd                 : 1,    //    13
    r_last_cmd_flag                 : 1,    //    14
    w_pl_sram_ptr_gap_check         : 1,    //    15
    r_pl_sram_virtual_wptr          :11;    // 16:26
} INFO_DEBUG_REQ_00;

/*-----------------------------------------------------------------------------
    0x0068 info_debug_req_01 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_posx_div                      :12,    //  0:11
    r_posy_div                      :10;    // 12:21
} INFO_DEBUG_REQ_01;

/*-----------------------------------------------------------------------------
    0x006c info_debug_req_02 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    w_abs_posx                      : 5,    //  0: 4
                                    : 3,    //  5: 7 reserved
    w_abs_posy                      : 4,    //  8:11
    w_pag_posx                      : 8,    // 12:19
    w_pag_posy                      : 8;    // 20:27
} INFO_DEBUG_REQ_02;

/*-----------------------------------------------------------------------------
    0x0070 info_debug_req_03 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    w_cur_len_dummy_64align         : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    w_cur_len_16byte                :12;    //  4:15
} INFO_DEBUG_REQ_03;

/*-----------------------------------------------------------------------------
    0x0074 info_debug_req_04 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_state                         : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    w_fifo_msg_last_cmd             : 1,    //     4
    i_psk_cmd_ack                   : 1,    //     5
    o_psk_cmd_val                   : 1,    //     6
                                    : 1,    //     7 reserved
    o_psk_cmd_len                   : 8;    //  8:15
} INFO_DEBUG_REQ_04;

/*-----------------------------------------------------------------------------
    0x0078 info_debug_req_05 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_state                         : 1,    //     0
                                    : 3,    //  1: 3 reserved
    o_sram0_adr                     :10,    //  4:13
                                    : 1,    //    14 reserved
    o_sram0_we                      : 1,    //    15
    o_sram0_wptr                    :11,    // 16:26
                                    : 1,    //    27 reserved
    r_dummy_len_d2                  : 4;    // 28:31
} INFO_DEBUG_REQ_05;

/*-----------------------------------------------------------------------------
    0x007c info_debug_dec_00 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    state_curr                      : 1,    //     0
    w_afrc_core_out_ready_mask      : 1,    //     1
    w_afrc_core_out_ready           : 1,    //     2
    w_afrc_core_in_ready            : 1,    //     3
    w_pl_bs_ready                   : 1;    //     4
} INFO_DEBUG_DEC_00;

/*-----------------------------------------------------------------------------
    0x0080 info_debug_dec_01 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    state                           : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    state_unpack                    : 2;    //  4: 5
} INFO_DEBUG_DEC_01;

/*-----------------------------------------------------------------------------
    0x0084 info_debug_dec_02 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    state_flush                     : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    r_curr_state                    : 1,    //     4
    w_posx_last                     : 1,    //     5
    w_posy_last                     : 1,    //     6
    w_24byte_dummy_en               : 1,    //     7
    r_swreset_start_mask            : 1,    //     8
    w_pl_sram_rd_avail              : 1,    //     9
    w_pl_sram_read_wait             : 1,    //    10
                                    : 1,    //    11 reserved
    o_pl0_rptr                      :11;    // 12:22
} INFO_DEBUG_DEC_02;

/*-----------------------------------------------------------------------------
    0x0088 info_debug_dec_03 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_posx_div                      :12,    //  0:11
    r_posy_div                      :11;    // 12:22
} INFO_DEBUG_DEC_03;

/*-----------------------------------------------------------------------------
    0x008c info_debug_dec_04 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_pl_bs_data_num                : 7,    //  0: 6
                                    : 1,    //     7 reserved
    r_bs_meb_pop_cnt                : 3,    //  8:10
                                    : 1,    //    11 reserved
    r_bs_flush_time                 : 1,    //    12
                                    : 3,    // 13:15 reserved
    r_bs_remove_push_num            : 3,    // 16:18
                                    : 1,    //    19 reserved
    r_bs_remove_push_cnt            : 3;    // 20:22
} INFO_DEBUG_DEC_04;

/*-----------------------------------------------------------------------------
    0x0090 info_debug_dec_05 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    w_dec_empty                     : 1,    //     0
    r_afrc_core_out_data_valid_mask : 1,    //     1
    w_afrc_core_out_data_valid      : 1,    //     2
                                    : 1,    //     3 reserved
    o_dec0_wptr                     :11;    //  4:14
} INFO_DEBUG_DEC_05;

/*-----------------------------------------------------------------------------
    0x0094 info_debug_mc_00 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    state_mc                        : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    state_rd                        : 1,    //     4
    r_last_start_mask               : 1,    //     5
    w_read_buf_empty                : 1,    //     6
    w_dec_sram_rd_avail             : 1,    //     7
    w_posy_last                     : 1,    //     8
    w_posx_last                     : 1,    //     9
                                    : 2,    // 10:11 reserved
    o_dec0_rptr                     :11,    // 12:22
                                    : 1,    //    23 reserved
    o_dec0_re                       : 1;    //    24
} INFO_DEBUG_MC_00;

/*-----------------------------------------------------------------------------
    0x0098 info_debug_mc_01 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_line_cnt                      : 2,    //  0: 1
                                    : 2,    //  2: 3 reserved
    r_mb_rd_line_cnt                : 2,    //  4: 5
                                    : 2,    //  6: 7 reserved
    r_mb_rd_valid_cnt               : 4,    //  8:11
    o_dec0_raddr                    :12;    // 12:23
} INFO_DEBUG_MC_01;

/*-----------------------------------------------------------------------------
    0x009c info_debug_mc_02 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    r_posx_div                      :12,    //  0:11
    r_posy_div                      :10,    // 12:21
    init_end_state                  :10;    // 22:31
} INFO_DEBUG_MC_02;

/*-----------------------------------------------------------------------------
    0x00b0 axi_addr_chk_en ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_chk_en0                 : 1,    //     0
                                    : 3,    //  1: 3 reserved
    invalid_chk_en1                 : 1;    //     4
} AXI_ADDR_CHK_EN;

/*-----------------------------------------------------------------------------
    0x00b4 axi_addr_chk_addr_st_0 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    addr_st_0                       ;       // 31: 0
} AXI_ADDR_CHK_ADDR_ST_0;

/*-----------------------------------------------------------------------------
    0x00b8 axi_addr_chk_addr_ed_0 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    addr_ed_0                       ;       // 31: 0
} AXI_ADDR_CHK_ADDR_ED_0;

/*-----------------------------------------------------------------------------
    0x00bc axi_addr_chk_addr_st_1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    addr_st_1                       ;       // 31: 0
} AXI_ADDR_CHK_ADDR_ST_1;

/*-----------------------------------------------------------------------------
    0x00c0 axi_addr_chk_addr_ed_1 ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    addr_ed_1                       ;       // 31: 0
} AXI_ADDR_CHK_ADDR_ED_1;

/*-----------------------------------------------------------------------------
    0x00c4 axi_addr_chk_clear ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    clear                           : 1;    //     0
} AXI_ADDR_CHK_CLEAR;

/*-----------------------------------------------------------------------------
    0x00c8 axi_addr_chk_status ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_status                  : 1;    //     0
} AXI_ADDR_CHK_STATUS;

/*-----------------------------------------------------------------------------
    0x00cc axi_addr_chk_addr ''
------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    invalid_addr                    ;       // 31: 0
} AXI_ADDR_CHK_ADDR;

typedef struct {
    CTRL_AFRC_0                         ctrl_afrc_0                     ;    // 0x0000 : ''
    CTRL_AFRC_1                         ctrl_afrc_1                     ;    // 0x0004 : ''
    CTRL_AFRC_2                         ctrl_afrc_2                     ;    // 0x0008 : ''
    UINT32                                               __rsvd_00[   1];    // 0x000c
    CTRL_AFRC_4                         ctrl_afrc_4                     ;    // 0x0010 : ''
    CTRL_AFRC_5                         ctrl_afrc_5                     ;    // 0x0014 : ''
    CTRL_AFRC_6                         ctrl_afrc_6                     ;    // 0x0018 : ''
    CTRL_AFRC_7                         ctrl_afrc_7                     ;    // 0x001c : ''
    CTRL_AFRC_8                         ctrl_afrc_8                     ;    // 0x0020 : ''
    CTRL_AFRC_9                         ctrl_afrc_9                     ;    // 0x0024 : ''
    CTRL_AFRC_A                         ctrl_afrc_a                     ;    // 0x0028 : ''
    CTRL_AFRC_B                         ctrl_afrc_b                     ;    // 0x002c : ''
    CTRL_AFRC_C                         ctrl_afrc_c                     ;    // 0x0030 : ''
    CTRL_AFRC_D                         ctrl_afrc_d                     ;    // 0x0034 : ''
    CTRL_AFRC_E                         ctrl_afrc_e                     ;    // 0x0038 : ''
    UINT32                                               __rsvd_01[   3];    // 0x003c ~ 0x0044
    CTRL_AFRC_12                        ctrl_afrc_12                    ;    // 0x0048 : ''
    CTRL_AFRC_13                        ctrl_afrc_13                    ;    // 0x004c : ''
    CTRL_AFRC_14                        ctrl_afrc_14                    ;    // 0x0050 : ''
    UINT32                                               __rsvd_02[   3];    // 0x0054 ~ 0x005c
    INFO_DEBUG_TOP_00                   info_debug_top_00               ;    // 0x0060 : ''
    INFO_DEBUG_REQ_00                   info_debug_req_00               ;    // 0x0064 : ''
    INFO_DEBUG_REQ_01                   info_debug_req_01               ;    // 0x0068 : ''
    INFO_DEBUG_REQ_02                   info_debug_req_02               ;    // 0x006c : ''
    INFO_DEBUG_REQ_03                   info_debug_req_03               ;    // 0x0070 : ''
    INFO_DEBUG_REQ_04                   info_debug_req_04               ;    // 0x0074 : ''
    INFO_DEBUG_REQ_05                   info_debug_req_05               ;    // 0x0078 : ''
    INFO_DEBUG_DEC_00                   info_debug_dec_00               ;    // 0x007c : ''
    INFO_DEBUG_DEC_01                   info_debug_dec_01               ;    // 0x0080 : ''
    INFO_DEBUG_DEC_02                   info_debug_dec_02               ;    // 0x0084 : ''
    INFO_DEBUG_DEC_03                   info_debug_dec_03               ;    // 0x0088 : ''
    INFO_DEBUG_DEC_04                   info_debug_dec_04               ;    // 0x008c : ''
    INFO_DEBUG_DEC_05                   info_debug_dec_05               ;    // 0x0090 : ''
    INFO_DEBUG_MC_00                    info_debug_mc_00                ;    // 0x0094 : ''
    INFO_DEBUG_MC_01                    info_debug_mc_01                ;    // 0x0098 : ''
    INFO_DEBUG_MC_02                    info_debug_mc_02                ;    // 0x009c : ''
    UINT32                                               __rsvd_03[   4];    // 0x00a0 ~ 0x00ac
    AXI_ADDR_CHK_EN                     axi_addr_chk_en                 ;    // 0x00b0 : ''
    AXI_ADDR_CHK_ADDR_ST_0              axi_addr_chk_addr_st_0          ;    // 0x00b4 : ''
    AXI_ADDR_CHK_ADDR_ED_0              axi_addr_chk_addr_ed_0          ;    // 0x00b8 : ''
    AXI_ADDR_CHK_ADDR_ST_1              axi_addr_chk_addr_st_1          ;    // 0x00bc : ''
    AXI_ADDR_CHK_ADDR_ED_1              axi_addr_chk_addr_ed_1          ;    // 0x00c0 : ''
    AXI_ADDR_CHK_CLEAR                  axi_addr_chk_clear              ;    // 0x00c4 : ''
    AXI_ADDR_CHK_STATUS                 axi_addr_chk_status             ;    // 0x00c8 : ''
    AXI_ADDR_CHK_ADDR                   axi_addr_chk_addr               ;    // 0x00cc : ''
} AFRC_O26_REG_T;
/* 41 regs, 41 types */

/* 41 regs, 41 types in Total*/

// *INDENT-ON*

#define AFRC_RdFL(idx,_r)      ((g_afrc_o26_reg_shadow[idx]->_r)=(g_afrc_o26_reg[idx]->_r))
#define AFRC_WrFL(idx,_r)      ((g_afrc_o26_reg[idx]->_r)=(g_afrc_o26_reg_shadow[idx]->_r))

#define AFRC_Rd(idx,_r)        *((UINT32*)(&(g_afrc_o26_reg_shadow[idx]->_r)))
#define AFRC_Wr(idx,_r,_v)     ((AFRC_Rd(idx,_r))=((UINT32)(_v)))

#define AFRC_Rd01(idx,_r,_f01,_v01)                                            \
                                do {                                                    \
                                    (_v01) = (g_afrc_o26_reg_shadow[idx]->_r._f01); \
                                } while(0)

#define AFRC_Rd02(idx,_r,_f01,_v01,_f02,_v02)                                  \
                                do {                                                    \
                                    (_v01) = (g_afrc_o26_reg_shadow[idx]->_r._f01); \
                                    (_v02) = (g_afrc_o26_reg_shadow[idx]->_r._f02); \
                                } while(0)

#define AFRC_Wr01(idx,_r,_f01,_v01)                                            \
                                do {                                                    \
                                    (g_afrc_o26_reg_shadow[idx]->_r._f01) = (_v01); \
                                } while(0)

#define AFRC_Wr02(idx,_r,_f01,_v01,_f02,_v02)                                  \
                                do {                                                    \
                                    (g_afrc_o26_reg_shadow[idx]->_r._f01) = (_v01); \
                                    (g_afrc_o26_reg_shadow[idx]->_r._f02) = (_v02); \
                                } while(0)

/** @} *//* end of macro documentation */

#define MAX_AFRC 4

extern volatile AFRC_O26_REG_T*     g_afrc_o26_reg[MAX_AFRC];
extern AFRC_O26_REG_T*              g_afrc_o26_reg_shadow[MAX_AFRC];

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O26-A0_PQE_AFRC_reg_man.csv' 20241210 17:57:49 KST by getregs v2.9 */
