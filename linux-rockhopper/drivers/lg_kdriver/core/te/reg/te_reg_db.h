#ifndef _TE_REG_DB_H_
#define _TE_REG_DB_H_

#include "base_types.h"

// *INDENT-OFF*

/*
 * Removed tab with vim
 * :set tabstop=8 shiftwidth=8 expandtab
 * :retab
 */

/**************************************************
 * DEMOD REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000~0x0010 tpi_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stp_status                      : 2,    //  0: 1 s2p_fsm in M16+/O18
        bp_status                       : 2,    //  2: 3 //M16P3 ~
        fifo_full                       : 1,    //     4
                                        :11,    //  5:15 reserved
        stp_synctype                    : 2,    // 16:17 s2p_mode in M16+/O18
        bp_synctype                     : 2,    // 18:19 //M16P3 ~
        tlv_synctype                    : 2,    // 20:21 //M16P3 ~
                                        : 2,    // 22:23 reserved
        is_serial                       : 1,    //    24 tpi_serial in M16+/O18
                                        : 2,    // 25:26 reserved
        stream_type                     : 1,    //    27
        tpi_en                          : 1,    //    28
                                        : 2,    // 29:30 reserved
        swreset                         : 1;    //    31
} TPI_CONF;

/*-----------------------------------------------------------------------------
        0x0020 demod_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        : 4,    //  0: 3 reserved
        synctype                        : 2,    //  4: 5
                                        : 2,    //  6: 7 reserved
        num_drop                        : 2,    //  8: 9
                                        : 2,    // 10:11 reserved
        num_found                       : 2,    // 12:13
                                        : 2,    // 14:15 reserved
        flt_push_status0                : 3,    // 16:18 //M16P3 ~
        flt_pop_status0                 : 2,    // 19:20 //M16P3 ~
        zero_len_flt_en                 : 1,    //    21
        null_type_flt_en                : 1,    //    22
        flt_bypass_en                   : 1,    //    23
                                        : 4,    // 24:27 reserved
        bypass_sync                     : 1,    //    28
                                        : 2,    // 29:30 reserved
        swreset                         : 1;    //    31
} TPI_SYNC;

/*-----------------------------------------------------------------------------
        0x0024 demod_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sync_status                     : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        sync_drop_mon                   : 1,    //     4
        s_sync_drop_mon                 : 1,    //     5
                                        : 2,    //  6: 7 reserved
        stlv_status                     : 3,    //  8:10
        stlv_drop                       : 1,    //    11
        tlv_status                      : 3,    // 12:14
        tlv_drop                        : 1,    //    15
        sb_value                        : 8,    // 16:23
        sb_mask                         : 8;    // 24:31
} TPI_MON;

/*-----------------------------------------------------------------------------
        0x0028 demod_tei ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tei_cnt                         :28,    //  0:27
        tei_enable                      : 1;    //    28
} TPI_TEI;

/*-----------------------------------------------------------------------------
        0x002c demod_packcnt ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sync_tp_counter                 ;       // 31: 0
} TPI_PACKCNT;


typedef struct {
        TPI_SYNC                        sync;
        TPI_MON                         mon;
        TPI_TEI                         tei;
        TPI_PACKCNT                     packet;
} TPI_PORT;

/*-----------------------------------------------------------------------------
        0x0070 tpi0_len_lmt '' //M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        len_max                         : 8,    //  0: 7
        len_comp                        : 8,    //  8:15
        len_limiter_en                  : 1;    //    16
} TPI_LEN_LMT;


/*-----------------------------------------------------------------------------
        0x00a0 cip0_conf
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tpi                             : 3;    //  0: 2
} CIP_SEL;


/*-----------------------------------------------------------------------------
        0x00b0 cin_conf
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tpi                             : 3;    //  0: 2
} CIN_SEL;

/*-----------------------------------------------------------------------------
        0x00c0 debug_demod '' //modifed to d0 on M16P3
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        debug_sel_demod                 : 3;    //  0: 2
} DEBUG_DEMOD;


/*-----------------------------------------------------------------------------
        0x00e0 tlv_flt_mon '' //M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        flt_push_cnt                    :16,    //  0:15
        flt_pop_cnt                     :16;    // 16:31
} TLV_FLT_MON;


typedef struct {
        TPI_CONF                        tpi_conf[8];            // 0x0000 ~ 0x001c
        TPI_PORT                        tpi_port[5];            // 0x0020 ~ 0x006c
        TPI_LEN_LMT                     tpi_len_lmt[5];         // 0x0070 ~ 0x0080
        UINT32                          __rsvd_01[7];           // 0x0084 ~ 0x009c
        CIP_SEL                         cip_sel[4];             // 0x00a0 ~ 0x00ac
        CIN_SEL                         cin_sel;                // 0x00b0
        UINT32                          __rsvd_02[3];           // 0x00b4 ~ 0x00bc
        DEBUG_DEMOD                     debug_demod_old;        // 0x00c0 : ''
        UINT32                          __rsvd_03[3];           // 0x00c4 ~ 0x00cc
        DEBUG_DEMOD                     debug_demod;            // 0x00d0 : ''
        UINT32                          __rsvd_04[3];           // 0x00d4 ~ 0x00dc
        TLV_FLT_MON                     tlv_flt_mon[4];         // 0x00e0 ~ 0x00f0
} TPI_REG_T;


/**************************************************
 * TOP REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tsbuf_intr                      : 1,    //     0
        stcc_intr                       : 1,    //     1
        upload0_intr                    : 1,    //     2
        upload1_intr                    : 1,    //     3
        dsc_intr                        : 1,    //     4
        be_engine_intr                  : 1,    //     5
        ciplus_intr                     : 1,    //     6
        engine_intr                     : 1,    //     7 // O20 rename
        apb_tout0_intr                  : 1,    //     8
        apb_tout1_intr                  : 1,    //     9
        srst0_intr                      : 1,    //    10
        srst1_intr                      : 1,    //    11
        dsc2_intr                       : 1;    //    12 // O20 rename
} TOP_INTR;


/*-----------------------------------------------------------------------------
        0x0010 chan_sel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        chan0_sel                       : 4,    //  0: 3
        chan1_sel                       : 4,    //  4: 7
        chan2_sel                       : 4,    //  8:11
        chan3_sel                       : 4,    // 12:15
        sub_chan0_sel                   : 4,    // 16:19
        sub_chan1_sel                   : 4,    // 20:23
        upload0_rdy_sel                 : 4,    // 24:27
        upload1_rdy_sel                 : 4;    // 28:31
} CHAN_SEL;

/*-----------------------------------------------------------------------------
        0x0014 pes_sel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        vid0_sel                        : 4,    //  0: 3
        vid1_sel                        : 4,    //  4: 7
        aud0_sel                        : 4,    //  8:11
        aud1_sel                        : 4;    // 12:15
} PES_SEL;

/*-----------------------------------------------------------------------------
        0x0018 tpo_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stpo_cnt_mon                    : 8,    //  0: 7
        fifo_rlevel_mon                 : 2,    //  8: 9
        fifo_wlevel_mon                 : 2,    // 10:11
                                        : 4,    // 12:15 reserved
        stpo_sel                        : 4,    // 16:19
        tpo_clk_inv                     : 1,    //    20
        tpo_cg_en                       : 1,    //    21
                                        : 2,    // 22:23 reserved
        tpo_mode                        : 1,    //    24
                                        : 3,    // 25:27 reserved
        tpo_en                          : 1,    //    28
                                        : 2,    // 29:30 reserved
        tpo_swreset                     : 1;    //    31
} TPO_CONF;


/*-----------------------------------------------------------------------------
        0x001c dco_fcw_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sd_dco_fcw_ctrl_tote            :24;    //  0:23
} DCO_FCW_CTRL;

/*-----------------------------------------------------------------------------
        0x0020 dco_ref32 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_ref_32                     : 1;    //     0
} DCO_REF32;

/*-----------------------------------------------------------------------------
        0x0024 dco_ref31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_ref_31_0                   ;       // 31: 0
} DCO_REF31_0;

/*-----------------------------------------------------------------------------
        0x0028 dco_stcc_mon32 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_real_32                    : 1;    //     0
} DCO_STCC_MON32;

/*-----------------------------------------------------------------------------
        0x002c dco_stcc_mon31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_real_31_0                  ;       // 31: 0
} DCO_STCC_MON31_0;

/*-----------------------------------------------------------------------------
        0x0030 apb_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        apb_s0_prt                      : 4,    //  0: 3
        apb_s1_prt                      : 4,    //  4: 7
        apb_s2_prt                      : 4;    //  8:11
} APB_CONF;

/*-----------------------------------------------------------------------------
        0x0034 axi_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        awcache_s02_temcu0_1            : 1,    //     0
                                        : 3,    //  1: 3 reserved
        arcache_s02_temcu0_1            : 1,    //     4
                                        : 3,    //  5: 7 reserved
        awcache_s03_temcu1_1            : 1,    //     8
                                        : 3,    //  9:11 reserved
        arcache_s03_temcu1_1            : 1,    //    12
                                        : 3,    // 13:15 reserved
        awcache_s04_be_wmif_1           : 1;    //    16
} AXI_CONF;

/*-----------------------------------------------------------------------------
        0x0038 uart ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        uart_sel                        : 1;    //     0
} UART;

/*-----------------------------------------------------------------------------
        0x003c monitor_sel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        monitor_sel                     : 3;    //  0: 2
} MONITOR_SEL;

/*-----------------------------------------------------------------------------
        0x0040 mcu2adec_intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        adec_intr_en                    : 1;    //     0
} MCU2ADEC_INTR_EN;

/*-----------------------------------------------------------------------------
        0x0044 mcu2adec_intr_st ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        adec_intr_tg                    : 1;    //     0
} MCU2ADEC_INTR_ST;

/*-----------------------------------------------------------------------------
        0x0050 mcu2adec_intr_ev ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        vdec_intr_en                    : 1;    //     0
} MCU2ADEC_INTR_EV;

/*-----------------------------------------------------------------------------
        0x0054 mcu2vdec_intr_st ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        vdec_intr_tg                    : 1;    //     0
} MCU2VDEC_INTR_ST;

/*-----------------------------------------------------------------------------
        0x0060 ~ 0x0064 dsc_adr_a and b''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        :12,    //  0:11 reserved
        tx_addr                         :20;    // 12:31
} DSC_ADR;


/*-----------------------------------------------------------------------------
        0x0070 lgdemod_conf '' //rename
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_sel                         : 3,    //  0: 2
                                        : 1,    //     3 reserved
        ch1_sel                         : 3,    //  4: 6
                                        : 1,    //     7 reserved
        ch2_sel                         : 3,    //  8:10
                                        : 1,    //    11 reserved
        ch3_sel                         : 3;    //  12:14
} ENGINE_CHAN_SEL;

/*-----------------------------------------------------------------------------
        0x0074 engine_sel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        engine_sel                      : 1,    //     0
        time_latch_en                   : 1;    //     1 DUMPER only
} ENGINE_SEL;

/*-----------------------------------------------------------------------------
        0x0078 tp_iomux_sel '' // O20 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tpi_int_demod_sel               : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        tpi_ext_demod1_sel              : 1,    //  4
                                        : 3,    //  5: 7 reserved
        tpi_ext_demod2_sel              : 1,    //  8
                                        : 3,    //  9:11 reserved
        tpo_outmux_sel                  : 2;    // 12:13
} TP_IOMUX_SEL;

/*-----------------------------------------------------------------------------
        0x0080 dco_fcw_ctrl_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sd_dco_fcw_ctrl_toip            :24;    //  0:23
} DCO_FCW_CTRL_MON;

/*-----------------------------------------------------------------------------
        0x0084 dco_divint_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sd_dco_divint_ctrl_toip         : 9;    //  0: 8
} DCO_DIVINT_CTRL;

/*-----------------------------------------------------------------------------
        0x0088 dco_divint_ctrl_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sd_dco_divint_ctrl_toip         : 9;    //  0: 8
} DCO_DIVINT_CTRL_MON;

typedef struct {
        TOP_INTR                        intr_en                         ;       // 0x0000 : ''
        TOP_INTR                        intr_stat                       ;       // 0x0004 : ''
        TOP_INTR                        intr_clr                        ;       // 0x0008 : ''
        TOP_INTR                        intr_ev                         ;       // 0x000c : ''
        CHAN_SEL                        chan_sel                        ;       // 0x0010 : ''
        PES_SEL                         pes_sel                         ;       // 0x0014 : ''
        TPO_CONF                        tpo_conf                        ;       // 0x0018 : ''
        DCO_FCW_CTRL                    dco_fcw_ctrl                    ;       // 0x001c : ''
        DCO_REF32                       dco_ref32                       ;       // 0x0020 : ''
        DCO_REF31_0                     dco_ref31_0                     ;       // 0x0024 : ''
        DCO_STCC_MON32                  dco_stcc_mon32                  ;       // 0x0028 : ''
        DCO_STCC_MON31_0                dco_stcc_mon31_0                ;       // 0x002c : ''
        APB_CONF                        apb_conf                        ;       // 0x0030 : ''
        AXI_CONF                        axi_conf                        ;       // 0x0034 : ''
        UART                            uart                            ;       // 0x0038 : ''
        MONITOR_SEL                     monitor_sel                     ;       // 0x003c : ''
        MCU2ADEC_INTR_EN                mcu2adec_intr_en                ;       // 0x0040 : ''
        MCU2ADEC_INTR_ST                mcu2adec_intr_st                ;       // 0x0044 : ''
        UINT32                          __rsvd_00[   2]                 ;       // 0x0048 ~ 0x004c
        MCU2ADEC_INTR_EV                mcu2adec_intr_ev                ;       // 0x0050 : ''
        MCU2VDEC_INTR_ST                mcu2vdec_intr_st                ;       // 0x0054 : ''
        UINT32                          __rsvd_01[   2]                 ;       // 0x0058 ~ 0x005c
        DSC_ADR                         dsc_adr_a                       ;       // 0x0060 : ''
        DSC_ADR                         dsc_adr_b                       ;       // 0x0064 : ''
        UINT32                          __rsvd_02[   2]                 ;       // 0x0068 ~ 0x006c
        ENGINE_CHAN_SEL                 engine_chan_sel                 ;       // 0x0070 : ''
        ENGINE_SEL                      engine_sel                      ;       // 0x0074 : '' //deprecated
        TP_IOMUX_SEL                    tp_iomux_sel                    ;       // 0x0078 : ''
        UINT32                          __rsvd_03[   1]                 ;       // 0x007c
        DCO_FCW_CTRL_MON                dco_fcw_ctrl_mon                ;       // 0x0080 : ''
        DCO_DIVINT_CTRL                 dco_divint_ctrl                 ;       // 0x0084 : ''
        DCO_DIVINT_CTRL_MON             dco_divint_ctrl_mon             ;       // 0x0088 : ''
} TOP_REG_T;
/* 18 regs, 18 types */


/**************************************************
 * FE_PIDF REG
 **************************************************/
/*-----------------------------------------------------------------------------
        0x0000 ~ 0x03fc pidf_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        meta_dn_en                      : 1,    //     0
        meta_out_idx                    : 2,    //  1: 2
        meta_out_en                     : 1,    //     3
        meta_type                       : 2,    //  4: 5
        meta_chan                       : 3,    //  6: 8
        meta_ext                        : 2,    //  9:10 // O20 ~
                                        : 5,    // 11:15 reserved
        ref_pid                         :13,    // 16:28
                                        : 2,    // 29:30 reserved
        pidf_val                        : 1;    //    31
} PIDF_CONF;

/*-----------------------------------------------------------------------------
        0x0400 pidf_chan0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        meta_for_bypass                 :13,    //  0:12
                                        : 3,    // 13:15 reserved
        bypass_en                       : 2,    // 16:17
        dup_discard_en                  : 1,    //    18 // ~m16p3 deprecated
        dnload_idx                      : 1,    //    19
        dnload_en                       : 1,    //    20 //M16P3 ~
                                        :10,    // 21:30
        swreset                         : 1;    //    31
} PIDF_CHAN_CONF;

typedef struct {
        PIDF_CHAN_CONF                  conf;
        UINT32                          packet_count;
        UINT32                          reserved[2];
} PIDF_CHAN_CONFSET;

/*-----------------------------------------------------------------------------
        0x0440 pidf_sub_chan0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32                          : 9,    //  0: 8 reserved
        meta_ext                        : 2,    //  9:10
        meta_type                       : 2,    // 11:12
                                        : 2,    // 13:14 reserved
        pidf_val                        : 1,    //    15
        ref_pid                         :13,    // 16:28
        pidf_bypass                     : 2,    // 29:30
        swreset                         : 1;    //        31
} PIDF_SUB_CHAN_CONF;

typedef struct {
        PIDF_SUB_CHAN_CONF              conf;
        UINT32                          packet_count;
        UINT32                          reserved[2];
} PIDF_SUB_CHAN_CONFSET;

typedef struct {
        PIDF_CONF                       pidf_conf[256]                  ;       // 0x0000 ~ 0x03fc
        PIDF_CHAN_CONFSET               pidf_ch[4]                      ;       // 0x0400 ~ 0x043c
        PIDF_SUB_CHAN_CONFSET           pidf_sub_ch[2]                  ;       // 0x0440 ~ 0x045c
        UINT32                          pidf_cc_err[8]                  ;       // 0x0460 ~ 0x047c //deprecated
        UINT32                          pidf_dup_err[8]                 ;       // 0x0480 ~ 0x049c //deprecated
} FE_PIDF_REG_T;


/**************************************************
 * FE_TSBUF REG
 **************************************************/
/*-----------------------------------------------------------------------------
        0x0000 tsbuf_chan0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        flevel                          : 8,    //  0: 7
        endian                          : 1,    //     8
        debug                           : 1,    //     9
                                        :21,    // 10:30 reserved
        swreset                         : 1;    //    31
} TSBUF_CHAN_CONF;

/*-----------------------------------------------------------------------------
        0x0004 tsbuf_chan0_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        rptr                            : 9;    //  0: 8
} TSBUF_CHAN_CTRL;

/*-----------------------------------------------------------------------------
        0x0008 tsbuf_chan0_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        wptr                            : 9,    //  0: 8
                                        :19,    //  9:27 reserved
        fack                            : 1;    //    28
} TSBUF_CHAN_MON;

typedef struct {
        TSBUF_CHAN_CONF                 conf;
        TSBUF_CHAN_CTRL                 ctrl;
        TSBUF_CHAN_MON                  mon;
        UINT32                          reserved;
} TSBUF_CHAN_CONFSET;

/*-----------------------------------------------------------------------------
        0x0040 tsbuf_sub_chan0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        flevel                          : 7,    //  0: 6
                                        : 1,    //     7 reserved
        endian                          : 1,    //     8
        debug                           : 1,    //     9
                                        :21,    // 10:30 reserved
        swreset                         : 1;    //    31
} TSBUF_SUB_CHAN_CONF;

/*-----------------------------------------------------------------------------
        0x0044 tsbuf_sub_chan0_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        rptr                            : 8;    //  0: 7
} TSBUF_SUB_CHAN_CTRL;

/*-----------------------------------------------------------------------------
        0x0048 tsbuf_sub_chan0_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        wptr                            : 8,    //  0: 7
                                        :20,    //  8:27 reserved
        fack                            : 1;    //    28
} TSBUF_SUB_CHAN_MON;

typedef struct {
        TSBUF_SUB_CHAN_CONF             conf;
        TSBUF_SUB_CHAN_CTRL             ctrl;
        TSBUF_SUB_CHAN_MON              mon;
        UINT32                          reserved;
} TSBUF_SUB_CHAN_CONFSET;

/*-----------------------------------------------------------------------------
        0x0060 ~ 0x007c tsbuf_intr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_packet_intr                 : 1,    //     0
        ch1_packet_intr                 : 1,    //     1
        ch2_packet_intr                 : 1,    //     2
        ch3_packet_intr                 : 1,    //     3
        sub_ch0_packet_intr             : 1,    //     4
        sub_ch1_packet_intr             : 1,    //     5
        ch0_buf_full_intr               : 1,    //     6
        ch1_buf_full_intr               : 1,    //     7
        ch2_buf_full_intr               : 1,    //     8
        ch3_buf_full_intr               : 1,    //     9
        sub_ch0_buf_full_intr           : 1,    //    10
        sub_ch1_buf_full_intr           : 1,    //    11
        ch0_buf_ovf_intr                : 1,    //    12
        ch1_buf_ovf_intr                : 1,    //    13
        ch2_buf_ovf_intr                : 1,    //    14
        ch3_buf_ovf_intr                : 1,    //    15
        sub_ch0_buf_ovf_intr            : 1,    //    16
        sub_ch1_buf_ovf_intr            : 1;    //    17
} TSBUF_INTR;

typedef struct {
        TSBUF_CHAN_CONFSET              tsbuf_ch[4]                     ;       // 0x0000 ~ 0x003c
        TSBUF_SUB_CHAN_CONFSET          tsbuf_sub_ch[2]                 ;       // 0x0040 ~ 0x005c
        TSBUF_INTR                      tsbuf_intr_en_cpu               ;       // 0x0060 : ''
        TSBUF_INTR                      tsbuf_intr_stat_cpu             ;       // 0x0064 : ''
        TSBUF_INTR                      tsbuf_intr_clr_cpu              ;       // 0x0068 : ''
        TSBUF_INTR                      tsbuf_intr_ev_cpu               ;       // 0x006c : ''
        TSBUF_INTR                      tsbuf_intr_en_mcu               ;       // 0x0070 : ''
        TSBUF_INTR                      tsbuf_intr_stat_mcu             ;       // 0x0074 : ''
        TSBUF_INTR                      tsbuf_intr_clr_mcu              ;       // 0x0078 : ''
        TSBUF_INTR                      tsbuf_intr_ev_mcu               ;       // 0x007c : ''
} FE_TSBUF_REG_T;


/**************************************************
 * FE_STCC REG
 **************************************************/
/*-----------------------------------------------------------------------------
        0x0000 stcc_ch0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        pcr_pid                         :13,    //  0:12 //deprecated
                                        : 3,    // 13:15 reserved
        pcr_pid_val                     : 1,    //    16 //deprecated
        latch_en                        : 1,    //    17
        copy_en                         : 1,    //    18
                                        : 2,    // 19:20 reserved
        main                            : 1,    //    21
                                        : 6,    // 22:27 reserved
        stcc_en                         : 1,    //    28
                                        : 2,    // 29:30 reserved
        stcc_swreset                    : 1;    //    31
} STCC_CH_CONF;

/*-----------------------------------------------------------------------------
        0x0004 stcc_ch0_jitter ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        max_jitter                      :28,    //  0:27
        auto_discont_en                 : 1,    //    28
        tb_discont_en                   : 1;    //    29
} STCC_CH_JITTER;

/*-----------------------------------------------------------------------------
        0x0008 stcc_ch0_sub_rctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sub_unit_step                   :24,    //  0:23
        sub_rate_ctrl                   : 2,    // 24:25
        sub_auto_rate_ctrl_step_sel     : 2,    // 26:27
        sub_stcc_mode                   : 2,    // 28:29
                                        : 1,    //    30 reserved
        rate_ctrl_cnt_init              : 1;    //    31
} STCC_CH_SUB_RCTRL;

/*-----------------------------------------------------------------------------
        0x000c stcc_ch0_sub_gctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_ext_unit                   : 9,    //  0:8
                                        : 3,    //  9:11 reserved
        stcc_ext_incr                   : 2;    // 12:13
} STCC_CH_SUB_GCTRL;

/*-----------------------------------------------------------------------------
        0x0010 stcc_ch0_cur_stcc_base ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        hif_stcc_base_31_0              ;       // 31: 0
} STCC_CH_CUR_STCC_BASE;

/*-----------------------------------------------------------------------------
        0x0014 stcc_ch0_cur_stcc_ext ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        hif_stcc_ext                    : 9,    //  0: 8
                                        : 7,    //  9:15 reserved
        hif_stcc_base_32                : 1;    //    16
} STCC_CH_CUR_STCC_EXT;

/*-----------------------------------------------------------------------------
        0x0018 stcc_ch0_latched_stcc_base ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        latched_stcc_base_31_0          ;       // 31: 0
} STCC_CH_LATCHED_STCC_BASE;

/*-----------------------------------------------------------------------------
        0x001c stcc_ch0_latched_stcc_ext ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        latched_stcc_ext                : 9,    //  0: 8
                                        : 7,    //  9:15 reserved
        latched_stcc_base_32            : 1;    //    16
} STCC_CH_LATCHED_STCC_EXT;

/*-----------------------------------------------------------------------------
        0x0020 stcc_ch0_latched_pcr_base ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        latched_pcr_base_31_0           ;       // 31: 0
} STCC_CH_LATCHED_PCR_BASE;

/*-----------------------------------------------------------------------------
        0x0024 stcc_ch0_latched_pcr_ext ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        latched_pcr_ext                 : 9,    //  0: 8
                                        : 7,    //  9:15 reserved
        latched_pcr_base_32             : 1;    //    16
} STCC_CH_LATCHED_PCR_EXT;

/*-----------------------------------------------------------------------------
        0x0028 stcc_ch0_stcc_pcr_diff_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_pcr_diff_base_mon          :16,    //  0:15
        stcc_pcr_diff_ext_mon           : 9,    // 16:24
                                        : 6,    // 25:30 reserved
        stcc_pcr_diff_err_mon           : 1;    //    31
} STCC_CH_STCC_PCR_DIFF_MON;

/*-----------------------------------------------------------------------------
        0x002c stcc_ch0_stcc_incr_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        stcc_incr_mon                   :24;    //  0:23
} STCC_CH_STCC_INCR_MON;

/*-----------------------------------------------------------------------------
        0x0030 stcc_ch0_sub_rctrl_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sub_rctrl_step_mon              :24,    //  0:23
                                        : 4,    // 24:27 reserved
        sub_rate_high_mon               : 1,    //    28
        sub_rate_mismatch_mon           : 1;    //    29
} STCC_CH_SUB_RCTRL_MON;

typedef struct {
        STCC_CH_CONF                    conf;
        STCC_CH_JITTER                  jitter;
        STCC_CH_SUB_RCTRL               sub_rctrl;
        STCC_CH_SUB_GCTRL               sub_gctrl;
        STCC_CH_CUR_STCC_BASE           cur_stcc_base;
        STCC_CH_CUR_STCC_EXT            cur_stcc_ext;
        STCC_CH_LATCHED_STCC_BASE       latched_stcc_base;
        STCC_CH_LATCHED_STCC_EXT        latched_stcc_ext;
        STCC_CH_LATCHED_PCR_BASE        latched_pcr_base;
        STCC_CH_LATCHED_PCR_EXT         latched_pcr_ext;
        STCC_CH_STCC_PCR_DIFF_MON       stcc_pcr_diff_mon;
        STCC_CH_STCC_INCR_MON           stcc_incr_mon;
        STCC_CH_SUB_RCTRL_MON           sub_rctrl_mon;
        STCC_CH_CUR_STCC_BASE           cur_stcc_base_mcu;
        STCC_CH_CUR_STCC_EXT            cur_stcc_ext_mcu;
        UINT32                          __reserved_0[1];
} STCC_CH_CONFSET;

/*-----------------------------------------------------------------------------
        0x0100 gstcc_conf0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        gstcc_ext_unit                  :12,    //  0:11
        gstcc_ext_incr                  : 2,    // 12:13
                                        : 2,    // 14:15 reserved
        gstcc_en                        : 1,    //    16
                                        : 3,    // 17:19 reserved
        gstimer_en                      : 1,    //    20
                                        : 3,    // 21:23 reserved
        a3_latch_en                     : 1,    // 24 //TODO: should be 1 everytime
                                        : 6,    // 25:30 reserved
        gstcc_swreset                   : 1;    //    31
} GSTCC_CONF;

/*-----------------------------------------------------------------------------
        0x0104 gstcc0_rctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        unit_step                       :24,    //  0:23
        rate_ctrl                       : 2,    // 24:25
                                        : 2,    // 26:27 reserved
        ctrl_mode                       : 1,    //    28
                                        : 2,    // 29:30 reserved
        rate_ctrl_cnt_init              : 1;    //    31
} GSTCC_RCTRL;

/*-----------------------------------------------------------------------------
        0x0110 gstcc_base0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        gstcc_base_31_0                 ;       // 31: 0
} GSTCC_BASE;

/*-----------------------------------------------------------------------------
        0x0114 gstcc_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        gstcc_ext                       : 9,    //  0: 8
                                        : 7,    //  9:15 reserved
        gstcc_base_32                   : 1;    //    16
} GSTCC_EXT;

/*-----------------------------------------------------------------------------
        0x0118 gtimer_base0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        gtimer_base_31_0                ;       // 31: 0
} GTIMER_BASE;

/*-----------------------------------------------------------------------------
        0x011c gtimer_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        gtimer_ext                      : 9,    //  0: 8
                                        : 7,    //  9:15 reserved
        gtimer_base_32                  : 1;    //    16
} GTIMER_EXT;

typedef struct {
        GSTCC_CONF                      gstcc_conf;
        GSTCC_RCTRL                     gstcc_rctrl;
        GSTCC_BASE                      gstcc_latched_base;
        GSTCC_EXT                       gstcc_latched_ext;
        GSTCC_BASE                      gstcc_base;
        GSTCC_EXT                       gstcc_ext;
        GTIMER_BASE                     gtimer_base;
        GTIMER_EXT                      gtimer_ext;
} GSTCC_CONFSET_LEGACY;

typedef struct {
        GSTCC_CONF                      gstcc_conf;
        GSTCC_RCTRL                     gstcc_rctrl;
        GSTCC_BASE                      gstcc_latched_base;
        GSTCC_EXT                       gstcc_latched_ext;
        GSTCC_BASE                      gstcc_base;
        GSTCC_EXT                       gstcc_ext;
        GTIMER_BASE                     gtimer_base;
        GTIMER_EXT                      gtimer_ext;
        GSTCC_BASE                      gstcc_base_mcu;
        GSTCC_EXT                       gstcc_ext_mcu;
        UINT32                          __reserved_0[2];
} GSTCC_CONFSET;

/*-----------------------------------------------------------------------------
        0x0140 stcc_intr_en_cpu ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_pcr_intr                    : 1,    //     0
        ch1_pcr_intr                    : 1,    //     1
        ch2_pcr_intr                    : 1,    //     2
        ch3_pcr_intr                    : 1,    //     3
        ch0_discont_intr                : 1,    //     4
        ch1_discont_intr                : 1,    //     5
        ch2_discont_intr                : 1,    //     6
        ch3_discont_intr                : 1,    //     7
        gtimer_intr0                    : 1,    //     8
        gtimer_intr1                    : 1,    //     9
        gtimer_intr2                    : 1,    //    10
        gtimer_intr3                    : 1;    //    11
} STCC_INTR;


/*-----------------------------------------------------------------------------
        0x0160 stcc_out_sel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        vid0_stcc_sel                   : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        vid1_stcc_sel                   : 2,    //  4: 5
                                        : 6,    //  6:11 reserved
        aud0_stcc_sel                   : 2,    // 12:13
                                        : 2,    // 14:15 reserved
        aud1_stcc_sel                   : 2;    // 16:17
} STCC_OUT_SEL;

/*-----------------------------------------------------------------------------
        0x01e4 gstcc_latch_sel '' //M16P3
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        src_core_sel0                   : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        src_core_sel1                   : 2,    //  4: 5
                                        : 2,    //  6: 7 reserved
        src_core_sel2                   : 2,    //  8: 9
                                        : 2,    // 10:11 reserved
        src_core_sel3                   : 2;    // 12:13
} GSTCC_LATCH_SEL;

/*-----------------------------------------------------------------------------
    0x0170 stcc_pcr_pid                 for L18F
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        pcr_pid                         :13,    //  0:12
                                        : 3,    // 13:15 reserved
        pcr_pid_val                     : 1,    //    16
                                        :14,    // 17:30 reserved
        swreset                         : 1;    //    31 // O20 ~
} STCC_PCR_PID;

typedef struct {
        STCC_CH_CONFSET                 stcc_ch[4]                      ;       // 0x0000 ~ 0x00fc
        GSTCC_CONFSET_LEGACY            gstcc[2]                        ;       // 0x0100 ~ 0x013c

        STCC_INTR                       stcc_intr_en_cpu                ;       // 0x0140 : ''
        STCC_INTR                       stcc_intr_stat_cpu              ;       // 0x0144 : ''
        STCC_INTR                       stcc_intr_clr_cpu               ;       // 0x0148 : ''
        STCC_INTR                       stcc_intr_ev_cpu                ;       // 0x014c : ''

        STCC_INTR                       stcc_intr_en_mcu                ;       // 0x0150 : ''
        STCC_INTR                       stcc_intr_stat_mcu              ;       // 0x0154 : ''
        STCC_INTR                       stcc_intr_clr_mcu               ;       // 0x0158 : ''
        STCC_INTR                       stcc_intr_ev_mcu                ;       // 0x015c : ''
        STCC_OUT_SEL                    stcc_out_sel                    ;       // 0x0160 : ''
        UINT32                          reserved[3]                     ;       // 0x0164 ~ 0x016c
        STCC_PCR_PID                    stcc_pcr_pid[3]                 ;       // 0x0170 ~ 0x017c
} FE_STCC_Y18_REG_T;

//M16P3 ~ O20
typedef struct {
        STCC_CH_CONFSET                 stcc_ch[4]                      ;       // 0x0000 ~ 0x00fc
        GSTCC_CONFSET_LEGACY            gstcc[4]                        ;       // 0x0100 ~ 0x017c
        UINT32                          __rsvd_00[  16]                 ;       // 0x0180 ~ 0x01bc
        STCC_INTR                       stcc_intr_en_cpu                ;       // 0x01c0 : ''
        STCC_INTR                       stcc_intr_stat_cpu              ;       // 0x01c4 : ''
        STCC_INTR                       stcc_intr_clr_cpu               ;       // 0x01c8 : ''
        STCC_INTR                       stcc_intr_ev_cpu                ;       // 0x01cc : ''

        STCC_INTR                       stcc_intr_en_mcu                ;       // 0x01d0 : ''
        STCC_INTR                       stcc_intr_stat_mcu              ;       // 0x01d4 : ''
        STCC_INTR                       stcc_intr_clr_mcu               ;       // 0x01d8 : ''
        STCC_INTR                       stcc_intr_ev_mcu                ;       // 0x01dc : ''
        STCC_OUT_SEL                    stcc_out_sel                    ;       // 0x01e0 : ''
        GSTCC_LATCH_SEL                 gstcc_latch_sel                 ;       // 0x01e4 : '' //M16P3~
        UINT32                          reserved[2]                     ;       // 0x01e8 ~ 0x01ec
        STCC_PCR_PID                    stcc_pcr_pid[4]                 ;       // 0x01f0 ~ 0x01fc
} FE_STCC_Y21_REG_T;

// O22 ~
typedef struct {
        STCC_CH_CONFSET                 stcc_ch[4]                      ;       // 0x0000 ~ 0x00fc
        GSTCC_CONFSET                   gstcc[4]                        ;       // 0x0100 ~ 0x01bc
        STCC_INTR                       stcc_intr_en_cpu                ;       // 0x01c0 : ''
        STCC_INTR                       stcc_intr_stat_cpu              ;       // 0x01c4 : ''
        STCC_INTR                       stcc_intr_clr_cpu               ;       // 0x01c8 : ''
        STCC_INTR                       stcc_intr_ev_cpu                ;       // 0x01cc : ''
        STCC_INTR                       stcc_intr_en_mcu                ;       // 0x01d0 : ''
        STCC_INTR                       stcc_intr_stat_mcu              ;       // 0x01d4 : ''
        STCC_INTR                       stcc_intr_clr_mcu               ;       // 0x01d8 : ''
        STCC_INTR                       stcc_intr_ev_mcu                ;       // 0x01dc : ''
        STCC_OUT_SEL                    stcc_out_sel                    ;       // 0x01e0 : ''
        GSTCC_LATCH_SEL                 gstcc_latch_sel                 ;       // 0x01e4 : '' //M16P3~
        UINT32                          reserved[2]                     ;       // 0x01e8 ~ 0x01ec
        STCC_PCR_PID                    stcc_pcr_pid[4]                 ;       // 0x01f0 ~ 0x01fc
} FE_STCC_REG_T;

/**************************************************
 * UPLOAD REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 upload_conf0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        enable                          : 1,    //     0
                                        : 3,    //  1: 3 reserved
        pause                           : 1,    //     4
                                        : 3,    //  5: 7 reserved
        data_type                       : 1,    //     8
                                        : 3,    //  9:11 reserved
        wait_mode                       : 2,    // 12:13
                                        : 2,    // 14:15 reserved
        trick_mode                      : 2,    // 16:17
                                        : 2,    // 18:19 reserved
        auto_copy_en                    : 1,    //    20
                                        : 3,    // 21:23 reserved
        axi_endian0                     : 1,    //    24
                                        : 6,    // 25:30 reserved
        swreset0                        : 1;    //    31
} UP_CONF;

/*-----------------------------------------------------------------------------
        0x0004 up_max_jitter ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        max_jitter                      ;       // 31: 0
} UP_MAX_JITTER;

/*-----------------------------------------------------------------------------
        0x0008 up_wait_cycle ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        wait_cycle                      ;       // 31: 0
} UP_WAIT_CYCLE;

/*-----------------------------------------------------------------------------
        0x000c up_tsd_tune '' //Deprecated after M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tsd_tune_offset                 :16,    //  0:15
        tsd_tune                        : 1;    //    16
} UP_TSD_TUNE;

/*-----------------------------------------------------------------------------
        0x0010 up_start_ptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        : 4,    //  0: 3 reserved
        start_ptr                       :28;    //  4:31
} UP_START_PTR;

/*-----------------------------------------------------------------------------
        0x0014 up_end_ptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        : 4,    //  0: 3 reserved
        end_ptr                         :28;    //  4:31
} UP_END_PTR;

/*-----------------------------------------------------------------------------
        0x0018 up_write_ptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        : 4,    //  0: 3 reserved
        write_ptr                       :28;    //  4:31
} UP_WRITE_PTR;

/*-----------------------------------------------------------------------------
        0x001c up_read_ptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        read_ptr                        ;       // 31: 0
} UP_READ_PTR;

/*-----------------------------------------------------------------------------
        0x0030 up_intr_en_cpu ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        empty_intr                      : 1;    //     0
} UP_INTR;

/*-----------------------------------------------------------------------------
        0x0050 up_debug_pack_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        upload_packet_counter           ;       // 31: 0
} UP_DEBUG_PACK_CNT;

/*-----------------------------------------------------------------------------
        0x0054 up_debug_fifo_stat ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        fifo_rlevel                     : 3,    //  0: 2
                                        : 1,    //     3 reserved
        fifo_rlevel_err_clr             : 1,    //     4
                                        : 3,    //  5: 7 reserved
        fifo_wlevel                     : 3,    //  8:10
                                        : 1,    //    11 reserved
        fifo_wlevel_err_clr             : 1,    //    12
                                        : 3,    // 13:15 reserved
        fifo_rptr                       : 5,    // 16:20
                                        : 3,    // 21:23 reserved
        fifo_wptr                       : 5;    // 24:28
} UP_DEBUG_FIFO_STAT;

/*-----------------------------------------------------------------------------
        0x0058 up_debug_stat ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        out_status                      : 4,    //  0: 3
                                        :12,    //  4:15 reserved
        bus_status                      : 3;    // 16:18
} UP_DEBUG_STAT;

/*-----------------------------------------------------------------------------
        0x0060 up_pull_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        dec_rdy_en                      : 1,    //     0
        buf_rdy_en                      : 1,    //     1
                                        : 2,    //  2: 3 reserved
        vdec_sel                        : 1,    //     4
        adec_sel                        : 1,    //     5
                                        : 2,    //  6: 7 reserved
        vdec_rdy_en                     : 1,    //     8
        adec_rdy_en                     : 1;    //     9
} UP_PULL_CONF;

/*-----------------------------------------------------------------------------
        0x0064 up_axi_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ar_user                         : 4;    //  0: 3
} UP_AXI_CONF;

/*-----------------------------------------------------------------------------
        0x0068 up_tp2_tlv_conf '' // O20 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sb_value                        : 8,    //  0: 7
        sb_mask                         : 8,    //  8:15
                                        :15,    // 16:30
        en                              : 1;    //    31
} UP_TP2TLV_CONF;

/*-----------------------------------------------------------------------------
        0x006C up_tp2_tlv_mon '' // O20 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        status_mon                      : 3,    //  0: 2
                                        : 5,    //  3: 7
        sync_drop                       : 1;    //     8
} UP_TP2TLV_MON;

typedef struct {
        UP_CONF                         up_conf                         ;       // 0x0000 : ''
        UP_MAX_JITTER                   up_max_jitter                   ;       // 0x0004 : ''
        UP_WAIT_CYCLE                   up_wait_cycle                   ;       // 0x0008 : ''
        UP_TSD_TUNE                     up_tsd_tune                     ;       // 0x000c : ''
        UP_START_PTR                    up_start_ptr                    ;       // 0x0010 : ''
        UP_END_PTR                      up_end_ptr                      ;       // 0x0014 : ''
        UP_WRITE_PTR                    up_write_ptr                    ;       // 0x0018 : ''
        UP_READ_PTR                     up_read_ptr                     ;       // 0x001c : ''
        UINT32                                           __rsvd_00[   4];       // 0x0020 ~ 0x002c
        UP_INTR                         up_intr_en_cpu                  ;       // 0x0030 : ''
        UP_INTR                         up_intr_stat_cpu                ;       // 0x0034 : ''
        UP_INTR                         up_intr_clr_cpu                 ;       // 0x0038 : ''
        UP_INTR                         up_intr_ev_cpu                  ;       // 0x003c : ''
        UP_INTR                         up_intr_en_mcu                  ;       // 0x0040 : ''
        UP_INTR                         up_intr_stat_mcu                ;       // 0x0044 : ''
        UP_INTR                         up_intr_clr_mcu                 ;       // 0x0048 : ''
        UP_INTR                         up_intr_ev_mcu                  ;       // 0x004c : ''
        UP_DEBUG_PACK_CNT               up_debug_pack_cnt               ;       // 0x0050 : ''
        UP_DEBUG_FIFO_STAT              up_debug_fifo_stat              ;       // 0x0054 : ''
        UP_DEBUG_STAT                   up_debug_stat                   ;       // 0x0058 : ''
        UINT32                                           __rsvd_01[   1];       // 0x005c
        UP_PULL_CONF                    up_pull_conf                    ;       // 0x0060 : ''
        UP_AXI_CONF                     up_axi_conf                     ;       // 0x0064 : ''
        UP_TP2TLV_CONF                  up_tp2tlv_conf                  ;       // 0x0068 : ''
        UP_TP2TLV_MON                   up_tp2tlv_mon                   ;       // 0x006C : ''
} UPLOAD_REG_T;
/* 21 regs, 21 types */

/**************************************************
 * BE REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 ad_te_be_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        hw_dn_en                        : 1,    //     0
        hw_pie_en                       : 1,    //     1
        hw_tp2pes_en                    : 1,    //     2
        vid0_rdy_chk_en                 : 1,    //     3
        vid1_rdy_chk_en                 : 1,    //     4
        vid2_rdy_chk_en                 : 1,    //     5
        aud0_rdy_chk_en                 : 1,    //     6
        aud1_rdy_chk_en                 : 1,    //     7
        pes_start_offset                : 8,    //  8:15
        sw_start_addr                   : 9,    // 16:24
                                        : 2,    // 25:26 reserved
        time_stamp_mode                 : 1,    //    27
        rmif_endian                     : 1,    //    28
        wmif_endian                     : 1,    //    29
        hw_auto_read                    : 1,    //    30
        sw_start                        : 1;    //    31
} BE_CONF;

/*-----------------------------------------------------------------------------
        0x0004 ad_te_be_pie_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        dn0_pie_mask_en                 : 4,    //  0: 3
        dn1_pie_mask_en                 : 4,    //  4: 7
        dn0_dvr_en                      : 1,    //     8
        dn1_dvr_en                      : 1;    //     9
} BE_PIE_CONF;

/*-----------------------------------------------------------------------------
        0x0008 ad_te_be_pie_pid_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        dn0_pie_pid_filter              :13,    //  0:12
                                        : 3,    // 13:15 reserved
        dn1_pie_pid_filter              :13;    // 16:28
} BE_PIE_PID_CONF;

/*-----------------------------------------------------------------------------
        0x000c ad_te_be_hw_ver ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        last_modification_date          ;       // 31: 0
} BE_HW_VER;

/*-----------------------------------------------------------------------------
        0x0010 ~ 0x004c be buffer(PI[2], TP[2])
-----------------------------------------------------------------------------*/
typedef struct {
        UINT32                          start_addr;
        UINT32                          end_addr;
        UINT32                          rptr;
        UINT32                          wptr;
} BE_BUFF;


/*-----------------------------------------------------------------------------
        0x0050 ~ 0x005c, 0x0070 ~ 0x007c be_pie_det_value ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        pie_detect_value                :24,    //  0:23
        reserved_0                      : 8;    // 24:31
} BE_PIE_DET_VALUE;

/*-----------------------------------------------------------------------------
        0x0060 ~ 0x006c, 0x0080 ~ 0x008c be_pie_mask_value ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        pie_detect_mask                 :24,    //  0:23
        reserved_0                      : 8;    // 24:31
} BE_PIE_DET_MASK;


typedef struct {
        BE_PIE_DET_VALUE                value[4];
        BE_PIE_DET_MASK                 mask[4];
} BE_PIE_DET;

/*-----------------------------------------------------------------------------
        0x0090 ad_te_be_dn_buf_seg_size ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        dn0_buf_segment_size            :16,    //  0:15
        dn1_buf_segment_size            :16;    // 16:31
} BE_DN_BUF_SEG_SIZE;

/*-----------------------------------------------------------------------------
        0x0094 ad_te_be_status ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        be_top_ctrl_state               : 3,    //  0: 2
                                        : 1,    //     3 reserved
        be_dvr_state                    : 3,    //  4: 6
                                        : 1,    //     7 reserved
        be_rmif_state                   : 2;    //  8: 9
} BE_STATUS;

/*-----------------------------------------------------------------------------
        0x0098 ad_te_be_monitor ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        be_tp_count                     :16,    //  0:15
        be_ch_src                       : 2,    // 16:17
        be_pes_dst                      : 2,    // 18:19
        be_pes_type                     : 2;    // 20:21
} BE_MONITOR;

/*-----------------------------------------------------------------------------
        0x009c download_mode ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        download_mode_dn0               : 1,    //     0
        download_mode_dn1               : 1;    //     1
} DOWNLOAD_MODE;

/*-----------------------------------------------------------------------------
        0x00a0 ad_te_be_int_intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        reg_te_be                       : 6;    //  0: 5
} BE_INTR;

/*-----------------------------------------------------------------------------
        0x00d0 ad_te_be_cl_ts_buff_wptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        cleared_ts_buff_wptr            : 9;    //  0: 8
} BE_CL_TS_BUFF_WPTR;

/*-----------------------------------------------------------------------------
        0x00d4 ad_te_be_cl_ts_buff_flevel ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        cleared_ts_buff_flevel          : 9;    //  0: 8
} BE_CL_TS_BUFF_FLEVEL;

/*-----------------------------------------------------------------------------
        0x00d8 ad_te_be_cl_ts_buff_rptr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        cleared_ts_buff_rptr            : 9;    //  0: 8
} BE_CL_TS_BUFF_RPTR;

/*-----------------------------------------------------------------------------
        0x00dc ad_te_be_cl_ts_buff_rptr_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        cleared_ts_buff_rptr_mon        : 9;    //  0: 8
} BE_CL_TS_BUFF_RPTR_MON;

typedef struct {
        BE_CONF                         be_conf                   ;     // 0x0000 : ''
        BE_PIE_CONF                     be_pie_conf               ;     // 0x0004 : ''
        BE_PIE_PID_CONF                 be_pie_pid_conf           ;     // 0x0008 : ''
        BE_HW_VER                       be_hw_ver                 ;     // 0x000c : ''
        BE_BUFF                         be_pie_buff[2]            ;     // 0x0010 ~ 0x002c
        BE_BUFF                         be_tp_buff[2]             ;     // 0x0030 ~ 0x004c
        BE_PIE_DET                      be_pie_det[2];            ;     // 0x0050 ~ 0x008c
        BE_DN_BUF_SEG_SIZE              be_dn_buf_seg_size        ;     // 0x0090 : ''
        BE_STATUS                       be_status                 ;     // 0x0094 : ''
        BE_MONITOR                      be_monitor                ;     // 0x0098 : ''
        DOWNLOAD_MODE                   download_mode             ;     // 0x009c : ''
        BE_INTR                         be_int_intr_en            ;     // 0x00a0 : ''
        BE_INTR                         be_int_intr_cl            ;     // 0x00a4 : ''
        BE_INTR                         be_int_intr_ev            ;     // 0x00a8 : ''
        BE_INTR                         be_int_intr_st            ;     // 0x00ac : ''
        BE_INTR                         be_ext_intr_en            ;     // 0x00b0 : ''
        BE_INTR                         be_ext_intr_cl            ;     // 0x00b4 : ''
        BE_INTR                         be_ext_intr_ev            ;     // 0x00b8 : ''
        BE_INTR                         be_ext_intr_st            ;     // 0x00bc : ''
        UINT32                                     __rsvd_01[   4];     // 0x00c0 ~ 0x00cc
        BE_CL_TS_BUFF_WPTR              be_cl_ts_buff_wptr        ;     // 0x00d0 : ''
        BE_CL_TS_BUFF_FLEVEL            be_cl_ts_buff_flevel      ;     // 0x00d4 : ''
        BE_CL_TS_BUFF_RPTR              be_cl_ts_buff_rptr        ;     // 0x00d8 : ''
        BE_CL_TS_BUFF_RPTR_MON          be_cl_ts_buff_rptr_mon    ;     // 0x00dc : ''
} BE_REG_T;
/* 51 regs, 51 types */






/**************************************************
 * CIPLUS REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 ad_chan0_buf_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        raddr_mon                       : 9,    //  0: 8
                                        : 3,    //  9:11 reserved
        widx                            : 3,    // 12:14
        widx_upd                        : 1,    //    15
        flevel                          : 3,    // 16:18
                                        : 1,    //    19 reserved
        src_sel                         : 1,    //    20
        dest_sel                        : 1,    //    21
                                        : 6,    // 22:27 reserved
        mon_mode                        : 1,    //    28
                                        : 2,    // 29:30 reserved
        swreset                         : 1;    //    31
} CIPLUS_BUF_CONF;

/*-----------------------------------------------------------------------------
        0x000c ad_outbuf_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        raddr_mon                       : 9,    //  0: 8
                                        : 3,    //  9:11 reserved
        widx                            : 3,    // 12:14
        widx_upd                        : 1,    //    15
        flevel                          : 3,    // 16:18
                                        : 1,    //    19 reserved
        src_sel                         : 1,    //    20
        dest_sel                        : 1,    //    21
                                        : 9,    // 22:30 reserved
        swreset                         : 1;    //    31
} CIPLUS_OUTBUF_CONF;

/*-----------------------------------------------------------------------------
        0x0010 ad_chan0_buf_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        inbuf_pkt_full                  : 8;    //  0: 7
} CIPLUS_BUF_MON;

/*-----------------------------------------------------------------------------
        0x001c ad_outbuf_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        outbuf_pkt_full                 : 8,    //  0: 7
        reserved_0                      :24;    //  8:31
} CIPLUS_OUTBUF_MON;

/*-----------------------------------------------------------------------------
        0x0020 ad_chan0_pidf_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        syncbyte_r                      : 8,    //  0: 7
        sync_en                         : 1,    //     8
        tei_en                          : 1,    //     9
        bypass_en                       : 1,    //    10
                                        :20,    // 11:30 reserved
        swreset                         : 1;    //    31
} CIPLUS_PIDF_CONF;

/*-----------------------------------------------------------------------------
        0x0030 ad_queue_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        chan0_req_en                    : 1,    //     0
        chan1_req_en                    : 1,    //     1
        chan2_req_en                    : 1,    //     2
                                        : 5,    //  3: 7 reserved
        queue_status_mon                : 3,    //  8:10
                                        :20,    // 11:30 reserved
        queue_swreset                   : 1;    //    31
} CIPLUS_QUEUE_CONF;

/*-----------------------------------------------------------------------------
        0x0034 ad_outts_rst ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        :31,    //  0:30 reserved
        outts_swreset                   : 1;    //    31
} CIPLUS_OUTTS_RST;

/*-----------------------------------------------------------------------------
        0x0038 ad_sync_cam_in ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        :31,    //  0:30 reserved
        clk_inv                         : 1;    //    31
} CIPLUS_SYNC_CAM_IN;

/*-----------------------------------------------------------------------------
        0x003c ad_axi_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        endian_write                    : 2,    //  0: 1
        endian_read                     : 2;    //  2: 3
} CIPLUS_AXI_CONF;

/*-----------------------------------------------------------------------------
        0x0040 ad_demux0_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        demux_syncbyte                  : 8,    //  0: 7
                                        :20,    //  8:27 reserved
        demux_dest                      : 2,    // 28:29
        demux_vers                      : 1,    //    30
        demux_swreset                   : 1;    //    31
} CIPLUS_DEMUX_CONF;

/*-----------------------------------------------------------------------------
        0x0050 ad_inbuf_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        raddr_mon                       : 9,    //  0: 8
                                        : 3,    //  9:11 reserved
        widx                            : 3,    // 12:14
        widx_upd                        : 1,    //    15
        flevel                          : 3,    // 16:18
                                        : 9,    // 19:27 reserved
        mon_mode                        : 1,    //    28
                                        : 2,    // 29:30 reserved
        swreset                         : 1;    //    31
} CIPLUS_INBUF_CONF;

/*-----------------------------------------------------------------------------
        0x0054 ad_inbuf_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        inbuf_pkt_full                  : 8;    //  0: 7
} CIPLUS_INBUF_MON;

/*-----------------------------------------------------------------------------
        0x0060 ad_tpo_br_slot0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        br_slot                         :14;    //  0:13
} CIPLUS_TPO_BR_SLOT;

/*-----------------------------------------------------------------------------
        0x0070 ad_tpo_bitrate ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        bitrate                         :14;    //  0:13
} CIPLUS_TPO_BITRATE;


/*-----------------------------------------------------------------------------
        0x0074 cip_tpo_packet_cnt ''                    for L18F
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tpo_packet_cnt                  ;       // 31: 0
} CIPLUS_TPO_PACKET_CNT;

/*-----------------------------------------------------------------------------
        0x0080 ad_intr_en_cpu ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        inbuf0_full                     : 1,    //     0
        inbuf1_full                     : 1,    //     1
        inbuf2_full                     : 1,    //     2
        inbuf_full                      : 1,    //     3
        outbuf_full                     : 1,    //     4
                                        : 3,    //  5: 7 reserved
        inbuf0_empty                    : 1,    //     8
        inbuf1_empty                    : 1,    //     9
        inbuf2_empty                    : 1,    //    10
        inbuf_empty                     : 1,    //    11
        outbuf_empty                    : 1;    //    12
} CIPLUS_INTR;

/*-----------------------------------------------------------------------------
        0x0100 ad_chan0_pidf0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ref_pid                         :13,    //  0:12
                                        :18,    // 13:30 reserved
        pidf_val                        : 1;    //    31
} CIPLUS_PIDF;


typedef struct {
        CIPLUS_BUF_CONF                 ciplus_buf_conf[3]                  ;   // 0x0000 ~ 0x0008
        CIPLUS_OUTBUF_CONF              ciplus_outbuf_conf                  ;   // 0x000c : ''
        CIPLUS_BUF_MON                  ciplus_buf_mon[3]                   ;   // 0x0010 ~ 0x0018
        CIPLUS_OUTBUF_MON               ciplus_outbuf_mon                   ;   // 0x001c : ''
        CIPLUS_PIDF_CONF                ciplus_pidf_conf[3]                 ;   // 0x0020 ~ 0x0028
        UINT32                                               __rsvd_00[   1];   // 0x002c
        CIPLUS_QUEUE_CONF               ciplus_queue_conf                   ;   // 0x0030 : ''
        CIPLUS_OUTTS_RST                ciplus_outts_rst                    ;   // 0x0034 : ''
        CIPLUS_SYNC_CAM_IN              ciplus_sync_cam_in                  ;   // 0x0038 : ''
        CIPLUS_AXI_CONF                 ciplus_axi_conf                     ;   // 0x003c : ''
        CIPLUS_DEMUX_CONF               ciplus_demux_conf[3]                ;   // 0x0040 ~ 0x0048
        UINT32                                               __rsvd_01[   1];   // 0x004c
        CIPLUS_INBUF_CONF               ciplus_inbuf_conf                   ;   // 0x0050 : ''
        CIPLUS_INBUF_MON                ciplus_inbuf_mon                    ;   // 0x0054 : ''
        UINT32                                               __rsvd_02[   2];   // 0x0058 ~ 0x005c
        CIPLUS_TPO_BR_SLOT              ciplus_tpo_br_slot[4]               ;   // 0x0060 : ''
        CIPLUS_TPO_BITRATE              ciplus_tpo_bitrate                  ;   // 0x0070 : ''
        CIPLUS_TPO_PACKET_CNT           ciplus_tpo_packet_cnt               ;   // 0x0074
        UINT32                                               __rsvd_03[   2];   // 0x0078 ~ 0x007c
        CIPLUS_INTR                     ciplus_intr_en_cpu                  ;   // 0x0080 : ''
        CIPLUS_INTR                     ciplus_intr_stat_cpu                ;   // 0x0084 : ''
        CIPLUS_INTR                     ciplus_intr_clr_cpu                 ;   // 0x0088 : ''
        CIPLUS_INTR                     ciplus_intr_ev_cpu                  ;   // 0x008c : ''
        CIPLUS_INTR                     ciplus_intr_en_mcu                  ;   // 0x0090 : ''
        CIPLUS_INTR                     ciplus_intr_stat_mcu                ;   // 0x0094 : ''
        CIPLUS_INTR                     ciplus_intr_clr_mcu                 ;   // 0x0098 : ''
        CIPLUS_INTR                     ciplus_intr_ev_mcu                  ;   // 0x009c : ''
        UINT32                                               __rsvd_04[  24];   // 0x00a0 ~ 0x00fc
        CIPLUS_PIDF                     ciplus_pidf[3][32]                  ;   // 0x0100 ~ 0x027c
} CIPLUS_REG_T;
/* 39 regs, 39 types */


/**************************************************
 * A3 REG (ATSC 3.0 Register DB)
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 swreset_arb4x1 '' // M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        swreset_arb4x1                  : 1;    //     0
} SWRESET_ARB4X1;

/*-----------------------------------------------------------------------------
        0x0004 gmau_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        psk_cmd_dly_cnt                 : 4,    //  0: 3
        aw_user                         : 4;    //  4: 7
} GMAU_CONF;

/*-----------------------------------------------------------------------------
    0x0008 arb_4x1 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_cmd_pri                     : 6,    //  0: 5
                                        : 2,    //  6: 7 reserved
        ch1_cmd_pri                     : 6,    //  8:13
                                        : 2,    // 14:15 reserved
        ch2_cmd_pri                     : 6,    // 16:21
                                        : 2,    // 22:23 reserved
        ch3_cmd_pri                     : 6,    // 24:29
        use_last_bvalid                 : 1,    //    30 // M16P3 ~
        gmau_cac_full                   : 1;    //    31 // M16P3 ~
} ARB_4X1;

/*-----------------------------------------------------------------------------
    0x000c time_src_sel '' //Deprecated after M16P3
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ts_sel0                         : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        ts_sel1                         : 2;    //  4: 5
} TIME_SRC_SEL;

/*-----------------------------------------------------------------------------
        0x0010 timestamp_mon '' //M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        timestamp                       ;       // 31: 0
} TIMESTAMP_MON;

/*-----------------------------------------------------------------------------
        0x0020 ~ 0x003c A3_INTR
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_meta_wr                     : 1,    //     0
        ch1_meta_wr                     : 1,    //     1
        ch2_meta_wr                     : 1,    //     2
        ch3_meta_wr                     : 1,    //     3
        ch0_meta_unit_buf_full          : 1,    //     4
        ch1_meta_unit_buf_full          : 1,    //     5
        ch2_meta_unit_buf_full          : 1,    //     6
        ch3_meta_unit_buf_full          : 1,    //     7
        ch0_meta_almost_full            : 1,    //     8
        ch1_meta_almost_full            : 1,    //     9
        ch2_meta_almost_full            : 1,    //    10
        ch3_meta_almost_full            : 1,    //    11
        ch0_data_unit_buf_full          : 1,    //    12
        ch1_data_unit_buf_full          : 1,    //    13
        ch2_data_unit_buf_full          : 1,    //    14
        ch3_data_unit_buf_full          : 1,    //    15
        ch0_data_almost_full            : 1,    //    16
        ch1_data_almost_full            : 1,    //    17
        ch2_data_almost_full            : 1,    //    18
        ch3_data_almost_full            : 1,    //    19
        ch0_timestamp                   : 1,    //    20
        ch1_timestamp                   : 1,    //    21 //M16PP ~
        ch2_timestamp                   : 1,    //    22
        ch3_timestamp                   : 1,    //    23
        ch0_buf_full                    : 1,    //    24 //M16P3 ~
        ch1_buf_full                    : 1,    //    25
        ch2_buf_full                    : 1,    //    26
        ch3_buf_full                    : 1,    //    27
        ch0_buf_ovf                     : 1,    //    28
        ch1_buf_ovf                     : 1,    //    29
        ch2_buf_ovf                     : 1,    //    30
        ch3_buf_ovf                     : 1;    //    31
} A3_INTR;

/*-----------------------------------------------------------------------------
        0x0040 buf_full_ack '' //M16P3 ~
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_buf_full_ack                : 1,    //     0
        ch1_buf_full_ack                : 1,    //     1
        ch2_buf_full_ack                : 1,    //     2
        ch3_buf_full_ack                : 1;    //     3
} BUF_FULL_ACK;

/*-----------------------------------------------------------------------------
        0x0080 conf_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ref_plp_id                      : 6,    //  0: 5
                                        : 2,    //  6: 7 reserved
        plp_flt_en                      : 1,    //     8
                                        : 3,    //  9:11 reserved
        err_flt_en                      : 1,    //    12
                                        : 3,    // 13:15 reserved
        num_lock                        : 2,    // 16:17
                                        : 2,    // 18:19 reserved
        layer_sel                       : 2,    // 20:21
                                        : 2,    // 22:23 reserved
        lgd_sel                         : 2,    // 24:25
        ts_latch_en                     : 1,    //    26 // GSTCC latch control M16P3~
                                        : 1,    //    27 reserved
        enable                          : 1,    //    28
        meta_enable                     : 1,    //    29 // M16P3~
                                        : 1,    //    30 reserved
        swreset                         : 1;    //    31
} CONF_CH;

/*-----------------------------------------------------------------------------
        0x0084 cmd_pri_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        data_cmd_pri                    : 6,    //  0: 5
                                        : 2,    //  6: 7 reserved
        meta_cmd_pri                    : 6,    //  8:13
                                        : 2,    // 14:15 reserved
        data_last_bvalid_en             : 1,    //    16
        meta_last_bvalid_en             : 1;    //    17
} A3_CMD_PRI;

/*-----------------------------------------------------------------------------
        0x00c0 tmode ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        timestamp_mode                  : 2;    //  0: 1
} TMODE;

/*-----------------------------------------------------------------------------
        0x00c8 tdata_fsec ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
                                        : 2,    //  0: 1 reserved
        nsec                            :10,    //  2:11
        usec                            :10,    // 12:21
        msec                            :10;    // 22:31
} TDATA_FSEC;

/*-----------------------------------------------------------------------------
        0x00d0 lgc_stat_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sync_status_a0                  : 4,    //  0: 3
        drop_mon_a0                     : 1,    //     4
                                        : 3,    //  5: 7 reserved
        sync_status_b0                  : 4,    //  8:11
        drop_mon_b0                     : 1,    //    12
                                        : 3,    // 13:15 reserved
        ch0_sync_status_c0              : 4,    // 16:19
        ch0_drop_mon_c0                 : 1;    //    20
} LGC_STAT;

/*-----------------------------------------------------------------------------
    0x00d8 wmif_stat_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        meta_status_mon                 : 3,    //  0: 2
                                        : 1,    //     3 reserved
        data_status_mon                 : 3;    //  4: 6
} WMIF_STAT;

typedef struct {
        CONF_CH                         conf                            ;       //0x0080
        A3_CMD_PRI                      cmd_pri                         ;       //0x0084
        UINT32                          meta_flevel                     ;       //0x0088
        UINT32                          data_flevel                     ;       //0x008c
        UINT32                          meta_unit_buffer                ;       //0x0090
        UINT32                          data_unit_buffer                ;       //0x0094
        UINT32                          meta_full_ack                   ;       //0x0098
        UINT32                          data_full_ack                   ;       //0x009c
        UINT32                          meta_sptr                       ;       //0x00a0
        UINT32                          meta_eptr                       ;       //0x00a4
        UINT32                          meta_wptr                       ;       //0x00a8
        UINT32                          meta_rptr                       ;       //0x00ac
        UINT32                          data_sptr                       ;       //0x00b0
        UINT32                          data_eptr                       ;       //0x00b4
        UINT32                          data_wptr                       ;       //0x00b8
        UINT32                          data_rptr                       ;       //0x00bc
        TMODE                           tmode                           ;       //0x00c0
        UINT32                          tdata_sec                       ;       //0x00c4
        TDATA_FSEC                      tdata_fsec                      ;       //0x00c8
        UINT32                                              __rsvd_00[1];       //0x00cc
        LGC_STAT                        lgc_stat                        ;       //0x00d0
        UINT32                          dec_stat                        ;       //0x00d4
        WMIF_STAT                       wmif_stat                       ;       //0x00d8
        UINT32                          dn_stat                         ;       //0x00dc
        UINT32                          lgc_packet_cnt_a0               ;       //0x00e0
        UINT32                          lgc_packet_cnt_b0               ;       //0x00e4
        UINT32                          lgc_packet_cnt_c0               ;       //0x00e8
        UINT32                                              __rsvd_01[5];       //0x00ec ~ 0x00fc
} A3_CH_CONF;

typedef struct {
        UINT32                          swreset_arb4x1                  ;       // 0x0000 : ''
        GMAU_CONF                       gmau_conf                       ;       // 0x0004 : ''
        ARB_4X1                         arb_4x                          ;       // 0x0008
        TIME_SRC_SEL                    time_src_sel                    ;       // 0x000c : ''
        TIMESTAMP_MON                   timestamp_mon                   ;       // 0x0010 : ''
        UINT32                                               __rsvd_00[3];      // 0x0014 ~ 0x001c
        A3_INTR                         intr_cpu_en                     ;       // 0x0020
        A3_INTR                         intr_cpu_st                     ;       // 0x0024
        A3_INTR                         intr_cpu_clr                    ;       // 0x0028
        A3_INTR                         intr_cpu_ev                     ;       // 0x002c
        A3_INTR                         intr_mcu_en                     ;       // 0x0030
        A3_INTR                         intr_mcu_st                     ;       // 0x0034
        A3_INTR                         intr_mcu_clr                    ;       // 0x0038
        A3_INTR                         intr_mcu_ev                     ;       // 0x003c
        BUF_FULL_ACK                    buf_full_ack                    ;       // 0x0040 : ''
        UINT32                                           __rsvd_01[  15];       // 0x0044 ~ 0x007c
        A3_CH_CONF                      a3_conf_ch[4]                   ;       // 0x0080 ~ 0x027c
} A3_REG_T;


/**************************************************
 * ARIB REG (ARIB 2.0 Register DB)
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 arb_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_cmd_pri                     : 6,    //  0: 5
                                        : 2,    //  6: 7 reserved
        ch1_cmd_pri                     : 6,    //  8:13
                                        : 2,    // 14:15 reserved
        ch2_cmd_pri                     : 6,    // 16:21
                                        : 6,    // 22:27 reserved
        gmau_cac_full                   : 1,    //    28
                                        : 1,    //    29 reserved
        use_last_bvalid                 : 1,    //    30
        swreset_arb                     : 1;    //    31
} ARB_CONF;

/*-----------------------------------------------------------------------------
        0x0020 intr_cpu_en '' ~ 0x003C
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_meta_wr                     : 1,    //     0
        ch1_meta_wr                     : 1,    //     1
        ch2_meta_wr                     : 1,    //     2
        ch0_meta_unit_buf               : 1,    //     3
        ch1_meta_unit_buf               : 1,    //     4
        ch2_meta_unit_buf               : 1,    //     5
        ch0_meta_almost_full            : 1,    //     6
        ch1_meta_almost_full            : 1,    //     7
        ch2_meta_almost_full            : 1,    //     8
        ch0_data_unit_buf_full          : 1,    //     9
        ch1_data_unit_buf_full          : 1,    //    10
        ch2_data_unit_buf_full          : 1,    //    11
        ch0_data_almost_full            : 1,    //    12
        ch1_data_almost_full            : 1,    //    13
        ch2_data_almost_full            : 1,    //    14
        ch0_timstamp                    : 1,    //    15
        ch1_timstamp                    : 1,    //    16
        ch2_timstamp                    : 1;    //    17
} ARIB_INTR;

/*-----------------------------------------------------------------------------
        0x0100 ntp_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        latch_en                        : 1,    //     0 //~m16p3 deprecated
                                        : 1,    //     1 reserved
        len_check                       : 1,    //     2
                                        :28,    //  3:30 reserved
        swreset                         : 1;    //    31
} NTP_CONF;

/*-----------------------------------------------------------------------------
        0x0160 udp_port_v '' ~ 0x0164 udp_port_m
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        src                             :16,    //  0:15
        dst                             :16;    // 16:31
} UDP_PORT;

/*-----------------------------------------------------------------------------
        0x0170 ntp_info ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ntp_precision                   : 8,    //  0: 7
        ntp_poll                        : 8,    //  8:15
        ntp_mode                        : 3,    // 16:18
        ntp_vers                        : 3,    // 19:21
        ntp_li                          : 2;    // 22:23
} NTP_INFO;

/*-----------------------------------------------------------------------------
        0x017c ntp_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        tlv_status                      : 3,    //  0: 2
        ip_status                       : 3,    //  3: 5
        udp_status                      : 3,    //  6: 8
        ntp_status                      : 3;    //  9:11
} NTP_MON;

/*-----------------------------------------------------------------------------
        0x0180 wmif_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        mode                            : 2,    //  0: 1
        use_data_bvalid                 : 1,    //     2
        use_meta_bvalid                 : 1,    //     3
        data_fifo_flevel                : 5,    //  4: 8
                                        :19,    //  9:27 reserved
        enable                          : 1,    //    28
                                        : 2,    // 29:30 reserved
        swreset                         : 1;    //    31
} WMIF_CONF;

/*-----------------------------------------------------------------------------
        0x01d0 wmif_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        wmif_tlv_status                 : 3,    //  0: 2
        wmif_raw_status                 : 1,    //     3
        wmif_pvr_status                 : 1,    //     4
        wmif_rctrl_status               : 4,    //  5: 8
        cfifo_ovf                       : 1,    //     9
        cfifo_udf                       : 1,    //    10
        dfifo_ovf                       : 1,    //    11
        dfifo_udf                       : 1,    //    12
        mfifo_ovf                       : 1,    //    13
        mfifo_udf                       : 1,    //    14
        wmif_lgc_status                 : 1;    //    15 // DUMPER only
} WMIF_MON;

typedef struct {
        NTP_CONF                        ntp_conf                        ;       // 0x0100 : ''
        UINT32                                           __rsvd_02[   3];       // 0x0104 ~ 0x010c
        UINT32                          ip_src_v_127_96                 ;       // 0x0110 : ''
        UINT32                          ip_src_v_95_64                  ;       // 0x0114 : ''
        UINT32                          ip_src_v_63_32                  ;       // 0x0118 : ''
        UINT32                          ip_src_v_31_0                   ;       // 0x011c : ''
        UINT32                          ip_src_m_127_96                 ;       // 0x0120 : ''
        UINT32                          ip_src_m_95_64                  ;       // 0x0124 : ''
        UINT32                          ip_src_m_63_32                  ;       // 0x0128 : ''
        UINT32                          ip_src_m_31_0                   ;       // 0x012c : ''
        UINT32                          ip_dst_v_127_96                 ;       // 0x0130 : ''
        UINT32                          ip_dst_v_95_64                  ;       // 0x0134 : ''
        UINT32                          ip_dst_v_63_32                  ;       // 0x0138 : ''
        UINT32                          ip_dst_v_31_0                   ;       // 0x013c : ''
        UINT32                          ip_dst_m_127_96                 ;       // 0x0140 : ''
        UINT32                          ip_dst_m_95_64                  ;       // 0x0144 : ''
        UINT32                          ip_dst_m_63_32                  ;       // 0x0148 : ''
        UINT32                          ip_dst_m_31_0                   ;       // 0x014c : ''
        UINT32                          ip_ref_hdr_v_63_32              ;       // 0x0150 : ''
        UINT32                          ip_ref_hdr_v_31_0               ;       // 0x0154 : ''
        UINT32                          ip_ref_hdr_m_63_32              ;       // 0x0158 : ''
        UINT32                          ip_ref_hdr_m_31_0               ;       // 0x015c : ''
        UDP_PORT                        udp_port_v                      ;       // 0x0160 : ''
        UDP_PORT                        udp_port_m                      ;       // 0x0164 : ''
        UINT32                                           __rsvd_03[   2];       // 0x0168 ~ 0x016c
        NTP_INFO                        ntp_info                        ;       // 0x0170 : ''
        UINT32                          ntp_time_63_32                  ;       // 0x0174 : ''
        UINT32                          ntp_time_31_0                   ;       // 0x0178 : ''
        NTP_MON                         ntp_mon                         ;       // 0x017c : ''
        WMIF_CONF                       wmif_conf                       ;       // 0x0180 : ''
        UINT32                                           __rsvd_04[   3];       // 0x0184 ~ 0x018c
        UINT32                          dbuf_sptr                       ;       // 0x0190 : ''
        UINT32                          dbuf_eptr                       ;       // 0x0194 : ''
        UINT32                          dbuf_wptr                       ;       // 0x0198 : ''
        UINT32                          dbuf_rptr                       ;       // 0x019c : ''
        UINT32                          mbuf_sptr                       ;       // 0x01a0 : ''
        UINT32                          mbuf_eptr                       ;       // 0x01a4 : ''
        UINT32                          mbuf_wptr                       ;       // 0x01a8 : ''
        UINT32                          mbuf_rptr                       ;       // 0x01ac : ''
        UINT32                          dbuf_flevel                     ;       // 0x01b0 : ''
        UINT32                          dbuf_usize                      ;       // 0x01b4 : ''
        UINT32                                           __rsvd_05[   2];       // 0x01b8 ~ 0x01bc
        UINT32                          mbuf_flevel                     ;       // 0x01c0 : ''
        UINT32                          mbuf_usize                      ;       // 0x01c4 : ''
        UINT32                                           __rsvd_06[   2];       // 0x01c8 ~ 0x01cc
        WMIF_MON                        wmif_mon                        ;       // 0x01d0 : ''
        UINT32                                           __rsvd_07[  11];       // 0x01d4 ~ 0x01fc
} ARIB_CH_CONF;

typedef struct {
        ARB_CONF                        arb_conf                        ;       // 0x0000 : ''
        GMAU_CONF                       gmau_conf                       ;       // 0x0004 : ''
        UINT32                          timestamp                       ;       // 0x0008 : ''
        UINT32                                           __rsvd_00[   5];       // 0x000c ~ 0x001c
        ARIB_INTR                       intr_cpu_en                     ;       // 0x0020 : ''
        ARIB_INTR                       intr_cpu_st                     ;       // 0x0024 : ''
        ARIB_INTR                       intr_cpu_clr                    ;       // 0x0028 : ''
        ARIB_INTR                       intr_cpu_ev                     ;       // 0x002c : ''
        ARIB_INTR                       intr_mcu_en                     ;       // 0x0030 : ''
        ARIB_INTR                       intr_mcu_st                     ;       // 0x0034 : ''
        ARIB_INTR                       intr_mcu_clr                    ;       // 0x0038 : ''
        ARIB_INTR                       intr_mcu_ev                     ;       // 0x003c : ''
        UINT32                                           __rsvd_01[  48];       // 0x0040 ~ 0x00fc
        ARIB_CH_CONF                    arib_ch_conf[3]                 ;       // 0x0100 ~ 0x03fc
} ARIB2_REG_T;

/**************************************************
 * DUMPER REG (ATSC3 + ARIB2 + etc...)
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 arb_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_cmd_pri                     : 6,    //  0: 5
        ch1_cmd_pri                     : 6,    //  6:11
        ch2_cmd_pri                     : 6,    // 12:17
        ch3_cmd_pri                     : 6,    // 18:23
                                        : 4,    // 24:27 reserved
        gmau_cac_full                   : 1,    //    28
                                        : 1,    //    29 reserved
        use_last_bvalid                 : 1,    //    30
        swreset_arb                     : 1;    //    31
} DUMPER_ARB_CONF;

/*-----------------------------------------------------------------------------
        0x0020 ~ 0x003c DUMPER_INTR
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ch0_meta_wr                     : 1,    //     0
        ch1_meta_wr                     : 1,    //     1
        ch2_meta_wr                     : 1,    //     2
        ch3_meta_wr                     : 1,    //     3
        ch0_meta_unit_buf_full          : 1,    //     4
        ch1_meta_unit_buf_full          : 1,    //     5
        ch2_meta_unit_buf_full          : 1,    //     6
        ch3_meta_unit_buf_full          : 1,    //     7
        ch0_meta_almost_full            : 1,    //     8
        ch1_meta_almost_full            : 1,    //     9
        ch2_meta_almost_full            : 1,    //    10
        ch3_meta_almost_full            : 1,    //    11
        ch0_data_unit_buf_full          : 1,    //    12
        ch1_data_unit_buf_full          : 1,    //    13
        ch2_data_unit_buf_full          : 1,    //    14
        ch3_data_unit_buf_full          : 1,    //    15
        ch0_data_almost_full            : 1,    //    16
        ch1_data_almost_full            : 1,    //    17
        ch2_data_almost_full            : 1,    //    18
        ch3_data_almost_full            : 1,    //    19
        ch0_timestamp                   : 1,    //    20
        ch1_timestamp                   : 1,    //    21 //M16PP ~
        ch2_timestamp                   : 1,    //    22
        ch3_timestamp                   : 1,    //    23
                                        : 8;    // 24:31 reserved
} DUMPER_INTR;

/*-----------------------------------------------------------------------------
        0x01e4 dumper_a3_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        ref_plp_id                      : 6,    //  0: 5
                                        : 2,    //  6: 7 reserved
        plp_flt_en                      : 1,    //     8
                                        : 3,    //  9:11 reserved
        err_flt_en                      : 1,    //    12
                                        : 3,    // 13:15 reserved
        num_lock                        : 2,    // 16:17
                                        : 2,    // 18:19 reserved
        layer_sel                       : 2,    // 20:21
                                        : 2,    // 22:23 reserved
        lgc_vers                        : 1,    //    24
                                        : 6,    // 25:30 reserved
        swreset                         : 1;    //    31
} DUMPER_A3_CONF;

/*-----------------------------------------------------------------------------
        0x01e8 packet_cnt_conf ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        unit_byte                       :24,    //  0:23
                                        : 4,    // 24:27 reserved
        cnt_mode                        : 1,    //    28
                                        : 2,    // 29:30 reserved
        cnt_reset                       : 1;    //    31
} DUMPER_PACKET_CNT_CONF;

/*-----------------------------------------------------------------------------
        0x01fc lgc_mon ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sync_status                     : 4,    //  0: 3
        drop_mon                        : 1,    //     4
                                        : 3,    //  5: 7 reserved
        slgc_push_status                : 4,    //  8:11
        slgc_pop_status                 : 1,    //    12
        slgc_fifo0_full                 : 1,    //    13
        slgc_fifo0_empty                : 1,    //    14
        slgc_fifo1_full                 : 1,    //    15
        slgc_fifo1_empty                : 1,    //    16
                                        : 7,    // 17:23
        cc_err_cnt                      : 8;    // 24:31
} DUMPER_LGC_MON;


typedef struct {
        NTP_CONF                        ntp_conf                        ;       // 0x0100 : ''
        UINT32                                           __rsvd_02[   3];       // 0x0104 ~ 0x010c
        UINT32                          ip_src_v_127_96                 ;       // 0x0110 : ''
        UINT32                          ip_src_v_95_64                  ;       // 0x0114 : ''
        UINT32                          ip_src_v_63_32                  ;       // 0x0118 : ''
        UINT32                          ip_src_v_31_0                   ;       // 0x011c : ''
        UINT32                          ip_src_m_127_96                 ;       // 0x0120 : ''
        UINT32                          ip_src_m_95_64                  ;       // 0x0124 : ''
        UINT32                          ip_src_m_63_32                  ;       // 0x0128 : ''
        UINT32                          ip_src_m_31_0                   ;       // 0x012c : ''
        UINT32                          ip_dst_v_127_96                 ;       // 0x0130 : ''
        UINT32                          ip_dst_v_95_64                  ;       // 0x0134 : ''
        UINT32                          ip_dst_v_63_32                  ;       // 0x0138 : ''
        UINT32                          ip_dst_v_31_0                   ;       // 0x013c : ''
        UINT32                          ip_dst_m_127_96                 ;       // 0x0140 : ''
        UINT32                          ip_dst_m_95_64                  ;       // 0x0144 : ''
        UINT32                          ip_dst_m_63_32                  ;       // 0x0148 : ''
        UINT32                          ip_dst_m_31_0                   ;       // 0x014c : ''
        UINT32                          ip_ref_hdr_v_63_32              ;       // 0x0150 : ''
        UINT32                          ip_ref_hdr_v_31_0               ;       // 0x0154 : ''
        UINT32                          ip_ref_hdr_m_63_32              ;       // 0x0158 : ''
        UINT32                          ip_ref_hdr_m_31_0               ;       // 0x015c : ''
        UDP_PORT                        udp_port_v                      ;       // 0x0160 : ''
        UDP_PORT                        udp_port_m                      ;       // 0x0164 : ''
        UINT32                                           __rsvd_03[   2];       // 0x0168 ~ 0x016c
        NTP_INFO                        ntp_info                        ;       // 0x0170 : ''
        UINT32                          ntp_time_63_32                  ;       // 0x0174 : ''
        UINT32                          ntp_time_31_0                   ;       // 0x0178 : ''
        NTP_MON                         ntp_mon                         ;       // 0x017c : ''
        WMIF_CONF                       wmif_conf                       ;       // 0x0180 : ''
        UINT32                                           __rsvd_04[   3];       // 0x0184 ~ 0x018c
        UINT32                          dbuf_sptr                       ;       // 0x0190 : ''
        UINT32                          dbuf_eptr                       ;       // 0x0194 : ''
        UINT32                          dbuf_wptr                       ;       // 0x0198 : ''
        UINT32                          dbuf_rptr                       ;       // 0x019c : ''
        UINT32                          mbuf_sptr                       ;       // 0x01a0 : ''
        UINT32                          mbuf_eptr                       ;       // 0x01a4 : ''
        UINT32                          mbuf_wptr                       ;       // 0x01a8 : ''
        UINT32                          mbuf_rptr                       ;       // 0x01ac : ''
        UINT32                          dbuf_flevel                     ;       // 0x01b0 : ''
        UINT32                          dbuf_usize                      ;       // 0x01b4 : ''
        UINT32                                           __rsvd_05[   2];       // 0x01b8 ~ 0x01bc
        UINT32                          mbuf_flevel                     ;       // 0x01c0 : ''
        UINT32                          mbuf_usize                      ;       // 0x01c4 : ''
        UINT32                                           __rsvd_06[   2];       // 0x01c8 ~ 0x01cc
        WMIF_MON                        wmif_mon                        ;       // 0x01d0 : ''
        UINT32                                           __rsvd_07[   3];       // 0x01d4 ~ 0x01dc
        ENGINE_SEL                      time_latch_conf                 ;       // 0x01e0 : ''
        DUMPER_A3_CONF                  a3_conf                         ;       // 0x01e4 : ''
        DUMPER_PACKET_CNT_CONF          packet_cnt_conf                 ;       // 0x01e8 : ''
        UINT32                          packet_cnt                      ;       // 0x01ec : ''
        TMODE                           tmode                           ;       // 0x01f0 : ''
        UINT32                          tdata_sec                       ;       // 0x01f4 : ''
        TDATA_FSEC                      tdata_fsec                      ;       // 0x01f8 : ''
        DUMPER_LGC_MON                  lgc_mon                         ;       // 0x01fc : ''
} DUMPER_CH_CONF;

typedef struct {
        DUMPER_ARB_CONF                 arb_conf                        ;       // 0x0000 : ''
        GMAU_CONF                       gmau_conf                       ;       // 0x0004 : ''
        UINT32                          timestamp                       ;       // 0x0008 : ''
        UINT32                                           __rsvd_00[   5];       // 0x000c ~ 0x001c
        DUMPER_INTR                     intr_cpu_en                     ;       // 0x0020 : ''
        DUMPER_INTR                     intr_cpu_st                     ;       // 0x0024 : ''
        DUMPER_INTR                     intr_cpu_clr                    ;       // 0x0028 : ''
        DUMPER_INTR                     intr_cpu_ev                     ;       // 0x002c : ''
        DUMPER_INTR                     intr_mcu_en                     ;       // 0x0030 : ''
        DUMPER_INTR                     intr_mcu_st                     ;       // 0x0034 : ''
        DUMPER_INTR                     intr_mcu_clr                    ;       // 0x0038 : ''
        DUMPER_INTR                     intr_mcu_ev                     ;       // 0x003c : ''
        UINT32                                           __rsvd_01[  48];       // 0x0040 ~ 0x00fc
        DUMPER_CH_CONF                  ch_conf[4]                      ;       // 0x0100 ~ 0x04fc
} DUMPER_REG_T;


/**************************************************
 * DSC REG
 **************************************************/

/*-----------------------------------------------------------------------------
        0x0000 dma_start ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        start                           : 1,    //     0
                                        : 3,    //  1: 3 reserved
        busy                            : 1,    //     4
                                        : 7,    //  5:11 reserved
        ts_format                       : 2,    // 12:13
                                        : 2,    // 14:15 reserved
        ts_odd_mode                     : 1;    //    16
} DSC_DMA_START;

/*-----------------------------------------------------------------------------
        0x0044 dma_buf_stat ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        rfifo_full                      : 2,    //  0: 1
                                        : 2,    //  2: 3 reserved
        wfifo_full                      : 2;    //  4: 5
} DSC_DMA_BUF_STAT;

/*-----------------------------------------------------------------------------
        0x0050 crypto_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        crypto_type                     : 4,    //  0: 3
        blk_mode                        : 4,    //  4: 7
        res_mode                        : 4,    //  8:11
        key_size                        : 6,    // 12:17
                                        : 2,    // 18:19 reserved
        scramble                        : 1;    //    20
} DSC_CRYPTO_CTRL;

/*-----------------------------------------------------------------------------
        0x00f0 axi_user ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        aw_user                         : 4,    //  0: 3
        ar_user                         : 4;    //  4: 7
} DSC_AXI_USER;

/*-----------------------------------------------------------------------------
        0x0100 sw_reset ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        sw_reset                        : 1;    //     0
} DSC_SW_RESET;

/*-----------------------------------------------------------------------------
        0x0110 endian ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        endian                          : 1;    //     0
} DSC_ENDIAN;

/*-----------------------------------------------------------------------------
        0x0120 addr_cpu_intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_cpu_intr_en                : 1;    //     0
} DSC_ADDR_CPU_INTR_EN;

/*-----------------------------------------------------------------------------
        0x0124 addr_cpu_intr_stat ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_cpu_intr_stat              : 1;    //     0
} DSC_ADDR_CPU_INTR_STAT;

/*-----------------------------------------------------------------------------
        0x0128 addr_cpu_intr_clr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_cpu_intr_clr               : 1;    //     0
} DSC_ADDR_CPU_INTR_CLR;

/*-----------------------------------------------------------------------------
        0x0130 addr_mcu_intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_mcu_intr_en                : 1;    //     0
} DSC_ADDR_MCU_INTR_EN;

/*-----------------------------------------------------------------------------
        0x0134 addr_mcu_intr_stat ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_mcu_intr_stat              : 1;    //     0
} DSC_ADDR_MCU_INTR_STAT;

/*-----------------------------------------------------------------------------
        0x0138 addr_mcu_intr_clr ''
------------------------------------------------------------------------------*/
typedef struct {
        UINT32
        addr_mcu_intr_clr               : 1;    //     0
} DSC_ADDR_MCU_INTR_CLR;

/*-----------------------------------------------------------------------------
        0x01fc version ''
------------------------------------------------------------------------------*/


typedef struct {
        DSC_DMA_START                   dma_start                       ;       // 0x0000 : ''
        UINT32                          dma_src_addr                    ;       // 0x0004 : ''
        UINT32                          dma_src_len                     ;       // 0x0008 : ''
        UINT32                          dma_dst_addr                    ;       // 0x000c : ''
        UINT32                          dma_dst_len                     ;       // 0x0010 : ''
        UINT32                                           __rsvd_00[   3];       // 0x0014 ~ 0x001c
        UINT32                          proc_load_len                   ;       // 0x0020 : ''
        UINT32                          proc_skip_len                   ;       // 0x0024 : ''
        UINT32                                           __rsvd_01[   6];       // 0x0028 ~ 0x003c
        UINT32                          dma_src_stat                    ;       // 0x0040 : ''
        DSC_DMA_BUF_STAT                dma_buf_stat                    ;       // 0x0044 : ''
        UINT32                                           __rsvd_02[   2];       // 0x0048 ~ 0x004c
        DSC_CRYPTO_CTRL                 crypto_ctrl                     ;       // 0x0050 : ''
        UINT32                                           __rsvd_03[   3];       // 0x0054 ~ 0x005c
        UINT32                          even_key[10]                    ;       // 0x0060 ~ 0x0084
        UINT32                                           __rsvd_04[   2];       // 0x0088 ~ 0x008c
        UINT32                          even_iv[4]                      ;       // 0x0090 ~ 0x009c
        UINT32                          odd_key[10]                     ;       // 0x00a0 ~ 0x00c4
        UINT32                                           __rsvd_05[   2];       // 0x00c8 ~ 0x00cc
        UINT32                          odd_iv[4]                       ;       // 0x00d0 ~ 0x00dc
        UINT32                                           __rsvd_06[   4];       // 0x00e0 ~ 0x00ec
        DSC_AXI_USER                    axi_user                        ;       // 0x00f0 : ''
        UINT32                                           __rsvd_07[   3];       // 0x00f4 ~ 0x00fc
        DSC_SW_RESET                    sw_reset                        ;       // 0x0100 : ''
        UINT32                                           __rsvd_08[   3];       // 0x0104 ~ 0x010c
        DSC_ENDIAN                      endian                          ;       // 0x0110 : ''
        UINT32                                           __rsvd_09[   3];       // 0x0114 ~ 0x011c
        DSC_ADDR_CPU_INTR_EN            addr_cpu_intr_en                ;       // 0x0120 : ''
        DSC_ADDR_CPU_INTR_STAT          addr_cpu_intr_stat              ;       // 0x0124 : ''
        DSC_ADDR_CPU_INTR_CLR           addr_cpu_intr_clr               ;       // 0x0128 : ''
        UINT32                                           __rsvd_10[   1];       // 0x012c
        DSC_ADDR_MCU_INTR_EN            addr_mcu_intr_en                ;       // 0x0130 : ''
        DSC_ADDR_MCU_INTR_STAT          addr_mcu_intr_stat              ;       // 0x0134 : ''
        DSC_ADDR_MCU_INTR_CLR           addr_mcu_intr_clr               ;       // 0x0138 : ''
        UINT32                                           __rsvd_11[  48];       // 0x013c ~ 0x01f8
        UINT32                          version                         ;       // 0x01fc : ''
} DSC_TOP_REG_T;

// *INDENT-ON*

#endif                          /* _TE_REG_DB_H_ */
/* from 'TOP.csv' 20180820 19:00:00 KST by getregs v2.9 */
/* from 'FE_PIDF.csv' 20180820 19:00:00 KST by getregs v2.9 */
/* from 'FE_TSBUF_second.csv' 20151210 15:19:34 KST by getregs v2.9 */
/* from 'FE_STC.csv' 20180820 19:00:00 KST by getregs v2.9 */
/* from 'DEMOD.csv' 20171109 17:25:30 KST by getregs v2.9 */
/* from 'BE_second.csv' 20151210 15:19:34 KST by getregs v2.9 */
/* from 'UPLOAD.csv' 20180820 19:00:00 KST by getregs v2.9 */
/* from 'CIPLUS_second.csv' 20151210 15:19:34 KST by getregs v2.9 */
/* from 'A3.csv' 20171110 16:24:00 KST by getregs v2.9 */
/* from 'ARIB.csv' 20171109 16:47:59 KST by getregs v2.9 */
/* from 'DUMPER.csv' 20180820 19:00:00 KST by getregs v2.9 */
