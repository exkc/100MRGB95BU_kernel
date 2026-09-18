/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2021 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

#ifndef _OVI_REG_O26A0_H_
#define _OVI_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930004 (RW 0x123F)
        UINT32 odc_en                        :1;   //(0)(RW 0x1)
        UINT32 wb_en                         :1;   //(1)(RW 0x1)
        UINT32 dga_en                        :1;   //(2)(RW 0x1)
        UINT32 pre_dither_en                 :1;   //(3)(RW 0x1)
        UINT32 post_dither_en                :1;   //(4)(RW 0x1)
        UINT32 resol                         :1;   //(5)(RW 0x1)
        UINT32 fcic_en                       :1;   //(6)(RW 0x0)
        UINT32 mem_sel                       :1;   //(7)(RW 0x0)
        UINT32 demu_en                       :1;   //(8)(RW 0x0)
        UINT32 epi_out                       :1;   //(9)(RW 0x1)
        UINT32 ls_logic_en                   :1;   //(10)(RW 0x0)
        UINT32 rsvd0                         :21;  //(31:11)
    };
} OVI_O26A0_TCON_CONTROL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930008 (RW 0x00)
        UINT32 odc_left_en                   :1;   //(0)(RW 0x0)
        UINT32 wb_left_en                    :1;   //(1)(RW 0x0)
        UINT32 dga_left_en                   :1;   //(2)(RW 0x0)
        UINT32 pre_dither_left_en            :1;   //(3)(RW 0x0)
        UINT32 post_dither_left_en           :1;   //(4)(RW 0x0)
        UINT32 tosel0                        :1;   //(5)(RW 0x0)
        UINT32 tosel1                        :1;   //(6)(RW 0x0)
        UINT32 bypass_en                     :1;   //(7)(RW 0x0)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_TEST_CTL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93000C (RW 0x00)
        UINT32 out_de_inv                    :1;   //(0)(RW 0x0)
        UINT32 out_hsync_inv                 :1;   //(1)(RW 0x0)
        UINT32 out_vsync_inv                 :1;   //(2)(RW 0x0)
        UINT32 out_vsync_sel                 :1;   //(3)(RW 0x0)
        UINT32 in_de_inv                     :1;   //(4)(RW 0x0)
        UINT32 in_hsync_inv                  :1;   //(5)(RW 0x0)
        UINT32 in_vsync_inv                  :1;   //(6)(RW 0x0)
        UINT32 rsvd0                         :25;  //(31:7)
    };
} OVI_O26A0_TCON_SYNC_CTL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930010 (RW/RO 0x00)
        UINT32 pix2_lock                     :1;   //(0)(RW 0x0)
        UINT32 init_done1                    :1;   //(1)(RO 0x0)
        UINT32 init_done2                    :1;   //(2)(RO 0x0)
        UINT32 rsvd0                         :29;  //(31:3)
    };
} OVI_O26A0_TCON_STS_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930018 (RW 0x00)
        UINT32 lodc_en_3D                    :1;   //(0)(RW 0x0)
        UINT32 lodc_en_2D                    :1;   //(1)(RW 0x0)
        UINT32 pcid_mode                     :2;   //(3:2)(RW 0x0)
        UINT32 rsvd0                         :1;   //(4)
        UINT32 subpix_shift_right_en         :1;   //(5)(RW 0x0)
        UINT32 first_last_subpix_en          :1;   //(6)(RW 0x0)
        UINT32 pcid20_en                     :1;   //(7)(RW 0x0)
        UINT32 pxod_oder                     :8;   //(15:8)(RW 0x00)
        UINT32 ltd_order                     :2;   //(17:16)(RW 0x0)
        UINT32 rsvd1                         :10;  //(27:18)
        UINT32 ltd_rb_swap                   :1;   //(28)(RW 0x0)
        UINT32 rsvd2                         :3;   //(31:29)
    };
} OVI_O26A0_TCON_ODC_OPT1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93001C (RW 0x03132008)
        UINT32 comp_mode                     :2;   //(1:0)(RW 0x0)
        UINT32 lodc_bypass                   :1;   //(2)(RW 0x0)
        UINT32 lr_ind_inv                    :1;   //(3)(RW 0x1)
        UINT32 odc_bypass                    :1;   //(4)(RW 0x0)
        UINT32 rsvd0                         :1;   //(5)
        UINT32 ddiv_in_sel                   :2;   //(7:6)(RW 0x0)
        UINT32 pre_dit_in_sel                :2;   //(9:8)(RW 0x0)
        UINT32 post_dit_in_sel               :1;   //(10)(RW 0x0)
        UINT32 rsvd1                         :1;   //(11)
        UINT32 lodc_in_sel                   :3;   //(14:12)(RW 0x2)
        UINT32 rsvd2                         :1;   //(15)
        UINT32 fcic_in_sel                   :3;   //(18:16)(RW 0x3)
        UINT32 rsvd3                         :1;   //(19)
        UINT32 odc_in_sel                    :3;   //(22:20)(RW 0x1)
        UINT32 rsvd4                         :1;   //(23)
        UINT32 dga_in_sel                    :3;   //(26:24)(RW 0x3)
        UINT32 rsvd5                         :1;   //(27)
        UINT32 wb_in_sel                     :3;   //(30:28)(RW 0x0)
        UINT32 rsvd6                         :1;   //(31)
    };
} OVI_O26A0_TCON_ODC_OPT2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930060 (RW 0x40)
        UINT32 wb_r_gain                     :16;  //(15:0)(RW 0x40)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_RGAIN_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930068 (RW 0x00)
        UINT32 wb_r_offset                   :16;  //(15:0)(RW 0x00)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_ROFFSET_U_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930070 (RW 0x40)
        UINT32 wb_g_gain                     :16;  //(15:0)(RW 0x40)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_GGAIN_U_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930078 (RW 0x00)
        UINT32 wb_g_offset                   :16;  //(15:0)(RW 0x00)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_GOFFSET_U_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930080 (RW 0x40)
        UINT32 wb_b_gain                     :16;  //(15:0)(RW 0x40)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_BGAIN_U_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930088 (RW 0x00)
        UINT32 wb_b_offset                   :16;  //(15:0)(RW 0x00)
        UINT32 rsvd0                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_WB_BOFFSET_U_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930090 (RW 0x14)
        UINT32 sgen_hbp                      :12;  //(11:0)(RW 0x14)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_HBP_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930094 (RW 0x14)
        UINT32 sgen_hs                       :12;  //(11:0)(RW 0x14)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_HS_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930098 (RW 0x1E)
        UINT32 sgen_hfp                      :12;  //(11:0)(RW 0x1E)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_HFP_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93009C (RW 0x19)
        UINT32 sgen_vbp                      :12;  //(11:0)(RW 0x19)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_VBP_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300A0 (RW 0x0a)
        UINT32 sgen_vs                       :12;  //(11:0)(RW 0x0a)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_VS_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300A4 (RW 0x0a)
        UINT32 sgen_vfp                      :12;  //(11:0)(RW 0x0a)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_VFP_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300A8 (RW 0x1e0)
        UINT32 sgen_dewidth                  :12;  //(11:0)(RW 0x1e0)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_DEWIDTH_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300B0 (RW 0x438)
        UINT32 sgen_denumber                 :12;  //(11:0)(RW 0x438)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_SGEN_DENUM_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300B8 (RW 0x30)
        UINT32 ver_blank_width               :8;   //(7:0)(RW 0x30)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_VBLANK_WIDTH_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300BC (RW 0x4)
        UINT32 vsync_width                   :8;   //(7:0)(RW 0x4)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_VSYNC_WIDTH_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300C0 (RW 0x0)
        UINT32 wpr_sd_en                     :1;   //(0)(RW 0x0)
        UINT32 odc_sd_en                     :1;   //(1)(RW 0x0)
        UINT32 pod_sd_en                     :1;   //(2)(RW 0x0)
        UINT32 siw_sd_en                     :1;   //(3)(RW 0x0)
        UINT32 fcic_sd_end                   :1;   //(4)(RW 0x0)
        UINT32 tcon_sd_en                    :1;   //(5)(RW 0x0)
        UINT32 ldiv_sd_en                    :1;   //(6)(RW 0x0)
        UINT32 tgen_sd_en                    :1;   //(7)(RW 0x0)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_SD_EN_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300C4 (RW 0x0)
        UINT32 wpr_sd_end                    :4;   //(3:0)(RW 0x0)
        UINT32 odc_sd_end                    :4;   //(7:4)(RW 0x0)
        UINT32 pod_sd_end                    :4;   //(11:8)(RW 0x0)
        UINT32 siw_sd_end                    :4;   //(15:12)(RW 0x0)
        UINT32 fcic_sd_end                   :4;   //(19:16)(RW 0x0)
        UINT32 tcon_sd_end                   :4;   //(23:20)(RW 0x0)
        UINT32 ldiv_sd_end                   :4;   //(27:24)(RW 0x0)
        UINT32 rsvd0                         :4;   //(31:28)
    };
} OVI_O26A0_TCON_SD_END_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300D4 (RW 0x00)
        UINT32 pgen_test                     :1;   //(0)(RW 0x0)
        UINT32 pgen_sync_mode                :1;   //(1)(RW 0x0)
        UINT32 pgen_reverse                  :1;   //(2)(RW 0x0)
        UINT32 pgen_mode                     :5;   //(7:3)(RW 0x00)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_PGEN_CTL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300D8 (RW 0x00)
        UINT32 mode_test                     :1;   //(0)(RW 0x0)
        UINT32 mode_test_sel                 :1;   //(1)(RW 0x0)
        UINT32 rsvd0                         :30;  //(31:2)
    };
} OVI_O26A0_TCON_MODE_CTL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300DC (RW 0x0)
        UINT32 pgen_vscr_val                 :8;   //(7:0)(RW 0x00)
        UINT32 pgen_vscr_en                  :1;   //(8)(RW 0x0)
        UINT32 pgen_vscr_up                  :1;   //(9)(RW 0x0)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_VSCR_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300E0 (RW 0x0)
        UINT32 pgen_hscr_val                 :8;   //(7:0)(RW 0x00)
        UINT32 pgen_hscr_en                  :1;   //(8)(RW 0x0)
        UINT32 pgen_hscr_left                :1;   //(9)(RW 0x0)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_HSCR_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300E4 (RW 0x00)
        UINT32 pgen_color_r1                 :10;  //(9:0)(RW 0x00)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPR1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300E8 (RW 0x00)
        UINT32 pgen_color_g1                 :10;  //(9:0)(RW 0x00)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPG1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300EC (RW 0x00)
        UINT32 pgen_color_b1                 :10;  //(9:0)(RW 0x00)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPB1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300F0 (RW 0x03)
        UINT32 pgen_color_r2                 :10;  //(9:0)(RW 0x03)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPR2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300F4 (RW 0x03)
        UINT32 pgen_color_g2                 :10;  //(9:0)(RW 0x03)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPG2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300F8 (RW 0x03)
        UINT32 pgen_color_b2                 :10;  //(9:0)(RW 0x03)
        UINT32 rsvd0                         :22;  //(31:10)
    };
} OVI_O26A0_TCON_PGEN_AGPB2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9300FC (RW 0x00)
        UINT32 pgen_vline1                   :12;  //(11:0)(RW 0x00)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_PGEN_VLINE1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930100 (RW 0x00)
        UINT32 pgen_vline2                   :12;  //(11:0)(RW 0x00)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_PGEN_VLINE2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930104 (RW 0x00)
        UINT32 pgen_hpixel1                  :12;  //(11:0)(RW 0x00)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_PGEN_HLINE1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930108 (RW 0x0)
        UINT32 pgen_hpixel2                  :12;  //(11:0)(RW 0x00)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_PGEN_HLINE2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93010C (RW 0x0)
        UINT32 pgen_vcomp0                   :24;  //(23:0)(RW 0x00)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_PGEN_VCOMP0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930110 (RW 0x0)
        UINT32 pgen_vcomp1                   :24;  //(23:0)(RW 0x00)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_PGEN_VCOMP1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930114 (RW 0x0)
        UINT32 pgen_vcomp2                   :24;  //(23:0)(RW 0x00)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_PGEN_VCOMP2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930118 (RW 0x0)
        UINT32 pgen_vcomp3                   :24;  //(23:0)(RW 0x00)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_PGEN_VCOMP3_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930130 (RW/RO 0x005a05a0)
        UINT32 dga_up_mode                   :1;   //(0)(RW 0x0)
        UINT32 dga_upload                    :1;   //(1)(RW 0x0)
        UINT32 dga_r_mode                    :1;   //(2)(RW 0x0)
        UINT32 dga_intp                      :1;   //(3)(RW 0x0)
        UINT32 dga_bank                      :1;   //(4)(RO 0x0)
        UINT32 rsvd0                         :3;   //(7:5)
        UINT32 in_frp_                       :8;   //(15:8)(RO 0x0)
        UINT32 rsvd1                         :16;  //(31:16)
    };
} OVI_O26A0_TCON_DGA_MODE_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930134 (RW 0x00000000)
        UINT32 dga_rgb0                      :24;  //(23:0)(RW 0x00000000)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_DGA_SEL0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930138 (RW 0x00000000)
        UINT32 dga_rgb1                      :24;  //(23:0)(RW 0x00000000)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_TCON_DGA_SEL1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930154 (RW 0x00)
        UINT32 pre_dither_sel                :4;   //(3:0)(RW 0x0)
        UINT32 post_dither_sel               :4;   //(7:4)(RW 0x0)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_TCON_DITHER_CARRY_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9301D8 (RW 0x00)
        UINT32 mon_sel0                      :1;   //(0)(RW 0x0)
        UINT32 mon_sel1                      :1;   //(1)(RW 0x0)
        UINT32 rsvd0                         :30;  //(31:2)
    };
} OVI_O26A0_TCON_MON_SEL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9301DC (RW 0x00)
        UINT32 init1_test                    :1;   //(0)(RW 0x0)
        UINT32 init2_test                    :1;   //(1)(RW 0x0)
        UINT32 rsvd0                         :30;  //(31:2)
    };
} OVI_O26A0_TCON_INIT_TEST_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930300 (RW 0x0000c0c0)
        UINT32 line_delay                    :1;   //(0)(RW 0)
        UINT32 rd_mode                       :1;   //(1)(RW 0)
        UINT32 de_st_mode                    :1;   //(2)(RW 0)
        UINT32 rgb_sel_en                    :1;   //(3)(RW 0)
        UINT32 lane_num                      :5;   //(8:4)(RW 0xc)
        UINT32 rsvd0                         :3;   //(11:9)
        UINT32 division                      :5;   //(16:12)(RW 0xc)
        UINT32 rsvd1                         :3;   //(19:17)
        UINT32 lv_mode                       :1;   //(20)(RW 0x0)
        UINT32 de_len_mode                   :1;   //(21)(RW 0x0)
        UINT32 rsvd2                         :10;  //(31:22)
    };
} OVI_O26A0_TCON_DDIV_MODE_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930304 (RW 0x20004)
        UINT32 hb_width                      :12;  //(11:0)(RW 0x4)
        UINT32 rsvd0                         :20;  //(31:12)
    };
} OVI_O26A0_TCON_DDIV_HBLANK_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930308 (RW 0x20)
        UINT32 ddiv_hwidth                   :12;  //(11:0)(RW 0x20)
        UINT32 rsvd0                         :4;   //(15:12)
        UINT32 de_len                        :11;  //(26:16)(BW 0x0)
        UINT32 rsvd1                         :5;   //(31:27)
    };
} OVI_O26A0_TCON_DDIV_HWIDTH_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93030C (RW 0x0)
        UINT32 ddiv_rgb_sel0                 :32;  //(31:0)(RW 0x0)
    };
} OVI_O26A0_TCON_DDIV_RGBSEL0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC930310 (RW 0x0)
        UINT32 ddiv_rgb_sel1                 :32;  //(31:0)(RW 0x0)
    };
} OVI_O26A0_TCON_DDIV_RGBSEL1_T;

typedef struct {
    OVI_O26A0_TCON_CONTROL_T                        tcon_control; //0xCC930004
    OVI_O26A0_TCON_TEST_CTL_T                      tcon_test_ctl; //0xCC930008
    OVI_O26A0_TCON_SYNC_CTL_T                      tcon_sync_ctl; //0xCC93000C
    OVI_O26A0_TCON_STS_T                                tcon_sts; //0xCC930010
    UINT32                                             reserved0; //0xCC930014
    OVI_O26A0_TCON_ODC_OPT1_T                      tcon_odc_opt1; //0xCC930018
    OVI_O26A0_TCON_ODC_OPT2_T                      tcon_odc_opt2; //0xCC93001C
    UINT32                                         reserved1[16]; //0xCC930020~0xCC93005C
    OVI_O26A0_TCON_WB_RGAIN_T                      tcon_wb_rgain; //0xCC930060
    UINT32                                             reserved2; //0xCC930064
    OVI_O26A0_TCON_WB_ROFFSET_U_T              tcon_wb_roffset_u; //0xCC930068
    UINT32                                             reserved3; //0xCC93006C
    OVI_O26A0_TCON_WB_GGAIN_U_T                  tcon_wb_ggain_u; //0xCC930070
    UINT32                                             reserved4; //0xCC930074
    OVI_O26A0_TCON_WB_GOFFSET_U_T              tcon_wb_goffset_u; //0xCC930078
    UINT32                                             reserved5; //0xCC93007C
    OVI_O26A0_TCON_WB_BGAIN_U_T                  tcon_wb_bgain_u; //0xCC930080
    UINT32                                             reserved6; //0xCC930084
    OVI_O26A0_TCON_WB_BOFFSET_U_T              tcon_wb_boffset_u; //0xCC930088
    UINT32                                             reserved7; //0xCC93008C
    OVI_O26A0_TCON_SGEN_HBP_T                      tcon_sgen_hbp; //0xCC930090
    OVI_O26A0_TCON_SGEN_HS_T                        tcon_sgen_hs; //0xCC930094
    OVI_O26A0_TCON_SGEN_HFP_T                      tcon_sgen_hfp; //0xCC930098
    OVI_O26A0_TCON_SGEN_VBP_T                      tcon_sgen_vbp; //0xCC93009C
    OVI_O26A0_TCON_SGEN_VS_T                        tcon_sgen_vs; //0xCC9300A0
    OVI_O26A0_TCON_SGEN_VFP_T                      tcon_sgen_vfp; //0xCC9300A4
    OVI_O26A0_TCON_SGEN_DEWIDTH_T              tcon_sgen_dewidth; //0xCC9300A8
    UINT32                                             reserved8; //0xCC9300AC
    OVI_O26A0_TCON_SGEN_DENUM_T                  tcon_sgen_denum; //0xCC9300B0
    UINT32                                             reserved9; //0xCC9300B4
    OVI_O26A0_TCON_VBLANK_WIDTH_T              tcon_vblank_width; //0xCC9300B8
    OVI_O26A0_TCON_VSYNC_WIDTH_T                tcon_vsync_width; //0xCC9300BC
    OVI_O26A0_TCON_SD_EN_T                            tcon_sd_en; //0xCC9300C0
    OVI_O26A0_TCON_SD_END_T                          tcon_sd_end; //0xCC9300C4
    UINT32                                         reserved10[3]; //0xCC9300C8~0xCC9300D0
    OVI_O26A0_TCON_PGEN_CTL_T                      tcon_pgen_ctl; //0xCC9300D4
    OVI_O26A0_TCON_MODE_CTL_T                      tcon_mode_ctl; //0xCC9300D8
    OVI_O26A0_TCON_PGEN_VSCR_T                    tcon_pgen_vscr; //0xCC9300DC
    OVI_O26A0_TCON_PGEN_HSCR_T                    tcon_pgen_hscr; //0xCC9300E0
    OVI_O26A0_TCON_PGEN_AGPR1_T                  tcon_pgen_agpr1; //0xCC9300E4
    OVI_O26A0_TCON_PGEN_AGPG1_T                  tcon_pgen_agpg1; //0xCC9300E8
    OVI_O26A0_TCON_PGEN_AGPB1_T                  tcon_pgen_agpb1; //0xCC9300EC
    OVI_O26A0_TCON_PGEN_AGPR2_T                  tcon_pgen_agpr2; //0xCC9300F0
    OVI_O26A0_TCON_PGEN_AGPG2_T                  tcon_pgen_agpg2; //0xCC9300F4
    OVI_O26A0_TCON_PGEN_AGPB2_T                  tcon_pgen_agpb2; //0xCC9300F8
    OVI_O26A0_TCON_PGEN_VLINE1_T                tcon_pgen_vline1; //0xCC9300FC
    OVI_O26A0_TCON_PGEN_VLINE2_T                tcon_pgen_vline2; //0xCC930100
    OVI_O26A0_TCON_PGEN_HLINE1_T                tcon_pgen_hline1; //0xCC930104
    OVI_O26A0_TCON_PGEN_HLINE2_T                tcon_pgen_hline2; //0xCC930108
    OVI_O26A0_TCON_PGEN_VCOMP0_T                tcon_pgen_vcomp0; //0xCC93010C
    OVI_O26A0_TCON_PGEN_VCOMP1_T                tcon_pgen_vcomp1; //0xCC930110
    OVI_O26A0_TCON_PGEN_VCOMP2_T                tcon_pgen_vcomp2; //0xCC930114
    OVI_O26A0_TCON_PGEN_VCOMP3_T                tcon_pgen_vcomp3; //0xCC930118
    UINT32                                         reserved11[5]; //0xCC93011C~0xCC93012C
    OVI_O26A0_TCON_DGA_MODE_T                      tcon_dga_mode; //0xCC930130
    OVI_O26A0_TCON_DGA_SEL0_T                      tcon_dga_sel0; //0xCC930134
    OVI_O26A0_TCON_DGA_SEL1_T                      tcon_dga_sel1; //0xCC930138
    UINT32                                         reserved12[6]; //0xCC93013C~0xCC930150
    OVI_O26A0_TCON_DITHER_CARRY_T              tcon_dither_carry; //0xCC930154
    UINT32                                        reserved13[32]; //0xCC930158~0xCC9301D4
    OVI_O26A0_TCON_MON_SEL_T                        tcon_mon_sel; //0xCC9301D8
    OVI_O26A0_TCON_INIT_TEST_T                    tcon_init_test; //0xCC9301DC
    UINT32                                        reserved14[72]; //0xCC9301E0~0xCC9302FC
    OVI_O26A0_TCON_DDIV_MODE_T                    tcon_ddiv_mode; //0xCC930300
    OVI_O26A0_TCON_DDIV_HBLANK_T                tcon_ddiv_hblank; //0xCC930304
    OVI_O26A0_TCON_DDIV_HWIDTH_T                tcon_ddiv_hwidth; //0xCC930308
    OVI_O26A0_TCON_DDIV_RGBSEL0_T              tcon_ddiv_rgbsel0; //0xCC93030C
    OVI_O26A0_TCON_DDIV_RGBSEL1_T              tcon_ddiv_rgbsel1; //0xCC930310
} OVI_O26A0_TCON_REG_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939008 (RW 0x00)
        UINT32 vx1_out_mode                  :1;   //(0)(RW 0x0)
        UINT32 vx1_en                        :1;   //(1)(RW 0x0)
        UINT32 vx1_5byte                     :1;   //(2)(RW 0x0)
        UINT32 vx1_video_mute                :1;   //(3)(RW 0x0)
        UINT32 vx1_sync_mute                 :1;   //(4)(RW 0x0)
        UINT32 vx1_4byte_ext                 :2;   //(6:5)(RW 0x0)
        UINT32 edp_en                        :1;   //(7)(RW 0x0)
        UINT32 rsvd0                         :24;  //(31:8)
    };
} OVI_O26A0_OIF_VX1_CONFIG0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93900C (RW 0x00000000)
        UINT32 vx1_resv13                    :2;   //(1:0)(RW 0x0)
        UINT32 vx1_resv12                    :2;   //(3:2)(RW 0x0)
        UINT32 vx1_resv11                    :2;   //(5:4)(RW 0x0)
        UINT32 vx1_resv10                    :2;   //(7:6)(RW 0x0)
        UINT32 vx1_resv9                     :2;   //(9:8)(RW 0x0)
        UINT32 vx1_resv8                     :2;   //(11:10)(RW 0x0)
        UINT32 vx1_resv7                     :2;   //(13:12)(RW 0x0)
        UINT32 vx1_resv6                     :2;   //(15:14)(RW 0x0)
        UINT32 vx1_resv5                     :2;   //(17:16)(RW 0x0)
        UINT32 vx1_resv4                     :2;   //(19:18)(RW 0x0)
        UINT32 vx1_resv3                     :2;   //(21:20)(RW 0x0)
        UINT32 vx1_resv2                     :2;   //(23:22)(RW 0x0)
        UINT32 vx1_resv1                     :2;   //(25:24)(RW 0x0)
        UINT32 vx1_resv0                     :2;   //(27:26)(RW 0x0)
        UINT32 vx1_resv_sel                  :4;   //(31:28)(RW 0x0)
    };
} OVI_O26A0_OIF_VX1_CONFIG1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939010 (RW 0x0)
        UINT32 vx1_resv15                    :2;   //(1:0)(RW 0x0)
        UINT32 vx1_resv14                    :2;   //(3:2)(RW 0x0)
        UINT32 rsvd0                         :28;  //(31:4)
    };
} OVI_O26A0_OIF_VX1_CONFIG2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939014 (RW 0x00000000)
        UINT32 vx1_force_even_data           :31;  //(30:0)(RW 0x00000000)
        UINT32 rsvd0                         :1;   //(31)
    };
} OVI_O26A0_OIF_VX1_CONFIG3_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939018 (RW 0x00000000)
        UINT32 vx1_force_odd_data            :31;  //(30:0)(RW 0x00000000)
        UINT32 rsvd0                         :1;   //(31)
    };
} OVI_O26A0_OIF_VX1_CONFIG4_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC93901C (RW 0x00000000)
        UINT32 lvds_sel                      :9;   //(8:0)(RW 0x0000)
        UINT32 rsvd0                         :6;   //(14:9)
        UINT32 lvds_swap                     :1;   //(15)(RW 0x0)
        UINT32 lvds_8bit_mode                :1;   //(16)(RW 0x0)
        UINT32 lvds_lsb_first                :1;   //(17)(RW 0x0)
        UINT32 rsvd1                         :14;  //(31:18)
    };
} OVI_O26A0_OIF_LVDS_CONFIG0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939020 (RW 0x00000000)
        UINT32 lvds_force_even_data          :31;  //(30:0)(RW 0x00000000)
        UINT32 rsvd0                         :1;   //(31)
    };
} OVI_O26A0_OIF_LVDS_CONFIG1_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939024 (RW 0x00000000)
        UINT32 lvds_force_odd_data           :31;  //(30:0)(RW 0x00000000)
        UINT32 rsvd0                         :1;   //(31)
    };
} OVI_O26A0_OIF_LVDS_CONFIG2_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC939028 (RW 0x00000000)
        UINT32 lvds_force_data               :16;  //(15:0)(RW 0x0000)
        UINT32 lvds_force_en                 :16;  //(31:16)(RW 0x0000)
    };
} OVI_O26A0_OIF_LVDS_CONFIG3_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9390AC (RW 0x000010)
        UINT32 vx1_apl_line                  :12;  //(11:0)(RW 0x010)
        UINT32 vx1_apl_pix                   :12;  //(23:12)(RW 0x000)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_OIF_VX1_APL_CTRL_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9390B0 (RW 0x0010)
        UINT32 info_ready_pix                :12;  //(11:0)(RW 0x010)
        UINT32 info_en                       :1;   //(12)(RW 0x0)
        UINT32 info_repeat_mode              :1;   //(13)(RW 0x0)
        UINT32 rsvd0                         :18;  //(31:14)
    };
} OVI_O26A0_OIF_VX1_INFO_CTRL0_T;

typedef union {
    UINT32 udata32;
    struct {        // 0xCC9390B4 (RW 0x005050)
        UINT32 info_end_line                 :12;  //(11:0)(RW 0x050)
        UINT32 info_start_line               :12;  //(23:12)(RW 0x005)
        UINT32 rsvd0                         :8;   //(31:24)
    };
} OVI_O26A0_OIF_VX1_INFO_CTRL1_T;

typedef struct {
    OVI_O26A0_OIF_VX1_CONFIG0_T                  oif_vx1_config0; //0xCC939008
    OVI_O26A0_OIF_VX1_CONFIG1_T                  oif_vx1_config1; //0xCC93900C
    OVI_O26A0_OIF_VX1_CONFIG2_T                  oif_vx1_config2; //0xCC939010
    OVI_O26A0_OIF_VX1_CONFIG3_T                  oif_vx1_config3; //0xCC939014
    OVI_O26A0_OIF_VX1_CONFIG4_T                  oif_vx1_config4; //0xCC939018
    OVI_O26A0_OIF_LVDS_CONFIG0_T                oif_lvds_config0; //0xCC93901C
    OVI_O26A0_OIF_LVDS_CONFIG1_T                oif_lvds_config1; //0xCC939020
    OVI_O26A0_OIF_LVDS_CONFIG2_T                oif_lvds_config2; //0xCC939024
    OVI_O26A0_OIF_LVDS_CONFIG3_T                oif_lvds_config3; //0xCC939028
    UINT32                                         reserved0[32]; //0xCC93902C~0xCC9390A8
    OVI_O26A0_OIF_VX1_APL_CTRL_T                oif_vx1_apl_ctrl; //0xCC9390AC
    OVI_O26A0_OIF_VX1_INFO_CTRL0_T            oif_vx1_info_ctrl0; //0xCC9390B0
    OVI_O26A0_OIF_VX1_INFO_CTRL1_T            oif_vx1_info_ctrl1; //0xCC9390B4
} OVI_O26A0_OIF_REG_T;

#endif
