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

#ifndef _REG_OVI_O22A0_h
#define _REG_OVI_O22A0_h

/*-----------------------------------------------------------------------------
                             0xcc440004L TCON_CONTROL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odc_en                             :1 ,	// 0 
	wb_en                              :1 ,	// 1 
	dga_en                             :1 ,	// 2 
	pre_dither_en                      :1 ,	// 3 
	post_dither_en                     :1 ,	// 4 
	resol                              :1 ,	// 5 
	fcic_en                            :1 ,	// 6 
	mem_sel                            :1 ,	// 7 
	dgc_en                             :1 ,	// 8 
	epi_out                            :1 ,	// 9 
	ls_logic_en                        :1 ;	// 10
}O20A0_OVI_TCON_CONTROL_T;
/*-----------------------------------------------------------------------------
                             0xcc440008L TCON_TEST_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odc_left_en                        :1 ,	// 0 
	wb_left_en                         :1 ,	// 1 
	dga_left_en                        :1 ,	// 2 
	pre_dither_left_en                 :1 ,	// 3 
	post_dither_left_en                :1 ,	// 4 
	tosel0                             :1 ,	// 5 
	tosel1                             :1 ,	// 6 
	bypass_en                          :1 ;	// 7 
}O20A0_OVI_TCON_TEST_CTL_T;
/*-----------------------------------------------------------------------------
                             0xcc44000cL TCON_SYNC_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_de_inv                         :1 ,	// 0 
	out_hsync_inv                      :1 ,	// 1 
	out_vsync_inv                      :1 ,	// 2 
	out_vsync_sel                      :1 ,	// 3 
	in_de_inv                          :1 ,	// 4 
	in_hsync_inv                       :1 ,	// 5 
	in_vsync_inv                       :1 ,	// 6 
	reserved01                         :1 ;	// 7 
}O20A0_OVI_TCON_SYNC_CTL_T;
/*-----------------------------------------------------------------------------
                             0xcc440010L TCON_STS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix2_lock                          :1 ,	// 0 
	init_done1                         :1 ,	// 1 
	init_done2                         :1 ,	// 2 
	reserved01                         :1 ,	// 3 
	reserved02                         :1 ,	// 4 
	reserved03                         :1 ,	// 5 
	reserved04                         :1 ,	// 6 
	reserved05                         :1 ;	// 7 
}O20A0_OVI_TCON_STS_T;
/*-----------------------------------------------------------------------------
                             0xcc44001cL TCON_ODC_OPT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	comp_mode                          :2 ,	// 1:0
	lodc_bypass                        :1 ,	// 2 
	lr_ind_inv                         :1 ,	// 3 
	odc_bypass                         :1 ,	// 4 
	pre_dit_in_sel                     :1 ,	// 5 
	ddiv_in_sel                        :2 ,	// 7:6
	post_dit_in_sel                    :3 ,	// 10:8
	reserved01                         :1 ,	// reserved
	lodc_in_sel                        :3 ,	// 14:12
	reserved02                         :1 ,	// reserved
	fcic_in_sel                        :3 ,	// 18:16
	reserved03                         :1 ,	// reserved
	odc_in_sel                         :3 ,	// 22:20
	reserved04                         :1 ,	// reserved
	dga_in_sel                         :3 ,	// 26:24
	reserved05                         :1 ,	// reserved
	wb_in_sel                          :3 ;	// 30:28
}O20A0_OVI_TCON_ODC_OPT2_T;
/*-----------------------------------------------------------------------------
                             0xcc440060L TCON_WB_RGAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_r_gain                          :16;	// 15:0
}O20A0_OVI_TCON_WB_RGAIN_T;
/*-----------------------------------------------------------------------------
                             0xcc440068L TCON_WB_ROFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_r_offset                        :16;	// 15:0
}O20A0_OVI_TCON_WB_ROFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xcc440070L TCON_WB_GGAIN_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_g_gain                          :16;	// 15:0
}O20A0_OVI_TCON_WB_GGAIN_U_T;
/*-----------------------------------------------------------------------------
                             0xcc440078L TCON_WB_GOFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_g_offset                        :16;	// 15:0
}O20A0_OVI_TCON_WB_GOFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xcc440080L TCON_WB_BGAIN_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_b_gain                          :16;	// 15:0
}O20A0_OVI_TCON_WB_BGAIN_U_T;
/*-----------------------------------------------------------------------------
                             0xcc440088L TCON_WB_BOFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_b_offset                        :16;	// 15:0
}O20A0_OVI_TCON_WB_BOFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xcc440090L TCON_SGEN_HBP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hbp                           :12;	// 11:0
}O20A0_OVI_TCON_SGEN_HBP_T;
/*-----------------------------------------------------------------------------
                             0xcc440094L TCON_SGEN_HS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hs                            :12;	// 11:0
}O20A0_OVI_TCON_SGEN_HS_T;
/*-----------------------------------------------------------------------------
                             0xcc440098L TCON_SGEN_HFP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hfp                           :12;	// 11:0
}O20A0_OVI_TCON_SGEN_HFP_T;
/*-----------------------------------------------------------------------------
                             0xcc44009cL TCON_SGEN_VBP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vbp                           :12;	// 11:0
}O20A0_OVI_TCON_SGEN_VBP_T;
/*-----------------------------------------------------------------------------
                             0xcc4400a0L TCON_SGEN_VS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vs                            :12;	// 11:0
}O20A0_OVI_TCON_SGEN_VS_T;
/*-----------------------------------------------------------------------------
                             0xcc4400a4L TCON_SGEN_VFP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vfp                           :12;	// 11:0
}O20A0_OVI_TCON_SGEN_VFP_T;
/*-----------------------------------------------------------------------------
                             0xcc4400a8L TCON_SGEN_DEWIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_dewidth                       :12;	// 11:0
}O20A0_OVI_TCON_SGEN_DEWIDTH_T;
/*-----------------------------------------------------------------------------
                             0xcc4400b0L TCON_SGEN_DENUM                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_denumber                      :12;	// 11:0
}O20A0_OVI_TCON_SGEN_DENUM_T;
/*-----------------------------------------------------------------------------
                             0xcc4400b8L TCON_VBLANK_WIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ver_blank_width                    :8 ;	// 7:0
}O20A0_OVI_TCON_VBLANK_WIDTH_T;
/*-----------------------------------------------------------------------------
                             0xcc4400bcL TCON_VSYNC_WIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync_width                        :8 ;	// 7:0
}O20A0_OVI_TCON_VSYNC_WIDTH_T;
/*-----------------------------------------------------------------------------
                             0xcc4400d4L TCON_PGEN_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_test                          :1 ,	// 0 
	pgen_sync_mode                     :1 ,	// 1 
	pgen_reverse                       :1 ,	// 2 
	pgen_mode                          :5 ;	// 7:3
}O20A0_OVI_TCON_PGEN_CTL_T;
/*-----------------------------------------------------------------------------
                             0xcc4400d8L TCON_MODE_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mode_test                          :1 ,	// 0 
	mode_test_sel                      :1 ;	// 1 
}O20A0_OVI_TCON_MODE_CTL_T;
/*-----------------------------------------------------------------------------
                             0xcc4400dcL TCON_PGEN_VSCR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vscr_val                      :8 ,	// 7:0
	pgen_vscr_en                       :1 ,	// 8 
	pgen_vscr_up                       :1 ;	// 9 
}O20A0_OVI_TCON_PGEN_VSCR_T;
/*-----------------------------------------------------------------------------
                             0xcc4400e0L TCON_PGEN_HSCR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hscr_val                      :8 ,	// 7:0
	pgen_hscr_en                       :1 ,	// 8 
	pgen_hscr_left                     :1 ;	// 9 
}O20A0_OVI_TCON_PGEN_HSCR_T;
/*-----------------------------------------------------------------------------
                             0xcc4400e4L TCON_PGEN_AGPR1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_r1                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPR1_T;
/*-----------------------------------------------------------------------------
                             0xcc4400e8L TCON_PGEN_AGPG1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_g1                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPG1_T;
/*-----------------------------------------------------------------------------
                             0xcc4400ecL TCON_PGEN_AGPB1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_b1                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPB1_T;
/*-----------------------------------------------------------------------------
                             0xcc4400f0L TCON_PGEN_AGPR2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_r2                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPR2_T;
/*-----------------------------------------------------------------------------
                             0xcc4400f4L TCON_PGEN_AGPG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_g2                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPG2_T;
/*-----------------------------------------------------------------------------
                             0xcc4400f8L TCON_PGEN_AGPB2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_b2                      :10;	// 9:0
}O20A0_OVI_TCON_PGEN_AGPB2_T;
/*-----------------------------------------------------------------------------
                             0xcc4400fcL TCON_PGEN_VLINE1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vline1                        :12;	// 11:0
}O20A0_OVI_TCON_PGEN_VLINE1_T;
/*-----------------------------------------------------------------------------
                             0xcc440100L TCON_PGEN_VLINE2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vline2                        :12;	// 11:0
}O20A0_OVI_TCON_PGEN_VLINE2_T;
/*-----------------------------------------------------------------------------
                             0xcc440104L TCON_PGEN_HLINE1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hpixel1                       :12;	// 11:0
}O20A0_OVI_TCON_PGEN_HLINE1_T;
/*-----------------------------------------------------------------------------
                             0xcc440108L TCON_PGEN_HLINE2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hpixel2                       :12;	// 11:0
}O20A0_OVI_TCON_PGEN_HLINE2_T;
/*-----------------------------------------------------------------------------
                             0xcc44010cL TCON_PGEN_VCOMP0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp0                        :24;	// 23:0
}O20A0_OVI_TCON_PGEN_VCOMP0_T;
/*-----------------------------------------------------------------------------
                             0xcc440110L TCON_PGEN_VCOMP1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp1                        :24;	// 23:0
}O20A0_OVI_TCON_PGEN_VCOMP1_T;
/*-----------------------------------------------------------------------------
                             0xcc440114L TCON_PGEN_VCOMP2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp2                        :24;	// 23:0
}O20A0_OVI_TCON_PGEN_VCOMP2_T;
/*-----------------------------------------------------------------------------
                             0xcc440118L TCON_PGEN_VCOMP3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp3                        :24;	// 23:0
}O20A0_OVI_TCON_PGEN_VCOMP3_T;
/*-----------------------------------------------------------------------------
                             0xcc440130L TCON_DGA_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dga_up_mode                        :1 ,	// 0 
	dga_upload                         :1 ,	// 1 
	dga_r_mode                         :1 ;	// 2 
}O20A0_OVI_TCON_DGA_MODE_T;
/*-----------------------------------------------------------------------------
                             0xcc440154L TCON_DITHER_CARRY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_dither_sel                     :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	post_dither_sel                    :3 ;	// 6:4
}O20A0_OVI_TCON_DITHER_CARRY_T;
/*-----------------------------------------------------------------------------
                             0xcc4401d8L TCON_MON_SEL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mon_sel0                           :1 ,	// 0 
	mon_sel1                           :1 ;	// 1 
}O20A0_OVI_TCON_MON_SEL_T;
/*-----------------------------------------------------------------------------
                             0xcc4401dcL TCON_INIT_TEST                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	init1_test                         :1 ,	// 0 
	init2_test                         :1 ;	// 1 
}O20A0_OVI_TCON_INIT_TEST_T;
/*-----------------------------------------------------------------------------
                             0xcc440300L TCON_DDIV_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_delay                         :1 ,	// 0 
	rd_mode                            :1 ,	// 1 
	drd_mode                           :1 ,	// 2 
	epi10                              :1 ,	// 3 
	lane_num                           :5 ,	// 8:4
	reserved01                         :3 ,	// reserved
	division                           :5 ,	// 16:12
	reserved02                         :3 ,	// reserved
	lv_mode                            :1 ,	// 20
	p8k_en                             :1 ,	// 21
	p8k_out_mode                       :1 ;	// 22
}O20A0_OVI_TCON_DDIV_MODE_T;
/*-----------------------------------------------------------------------------
                             0xcc440304L TCON_DDIV_HBLANK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hb_width                           :12,	// 11:0
	drd_h_blank                        :9 ;	// 20:12
}O20A0_OVI_TCON_DDIV_HBLANK_T;
/*-----------------------------------------------------------------------------
                             0xcc440308L TCON_DDIV_HWIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ddiv_hwidth                        :12;	// 11:0
}O20A0_OVI_TCON_DDIV_HWIDTH_T;

typedef struct
{ 
	UINT32                                           _rsvd_00;	//0x0000
	O20A0_OVI_TCON_CONTROL_T                        tcon_control;	//0x0004
	O20A0_OVI_TCON_TEST_CTL_T                       tcon_test_ctl;	//0x0008
	O20A0_OVI_TCON_SYNC_CTL_T                       tcon_sync_ctl;	//0x000C
	O20A0_OVI_TCON_STS_T                            tcon_sts;	//0x0010
	UINT32                                            reserved4[2];	//0x14-0x18
	O20A0_OVI_TCON_ODC_OPT2_T                       tcon_odc_opt2;	//0x001C
	UINT32                                            reserved5[16];	//0x20-0x5c
	O20A0_OVI_TCON_WB_RGAIN_T                       tcon_wb_rgain;	//0x0060
	UINT32                                            reserved6;	//0x64
	O20A0_OVI_TCON_WB_ROFFSET_U_T                   tcon_wb_roffset_u;	//0x0068
	UINT32                                            reserved7;	//0x6c
	O20A0_OVI_TCON_WB_GGAIN_U_T                     tcon_wb_ggain_u;	//0x0070
	UINT32                                            reserved8;	//0x74
	O20A0_OVI_TCON_WB_GOFFSET_U_T                   tcon_wb_goffset_u;	//0x0078
	UINT32                                            reserved9;	//0x7c
	O20A0_OVI_TCON_WB_BGAIN_U_T                     tcon_wb_bgain_u;	//0x0080
	UINT32                                            reserved10;	//0x84
	O20A0_OVI_TCON_WB_BOFFSET_U_T                   tcon_wb_boffset_u;	//0x0088
	UINT32                                            reserved11;	//0x8c
	O20A0_OVI_TCON_SGEN_HBP_T                       tcon_sgen_hbp;	//0x0090
	O20A0_OVI_TCON_SGEN_HS_T                        tcon_sgen_hs;	//0x0094
	O20A0_OVI_TCON_SGEN_HFP_T                       tcon_sgen_hfp;	//0x0098
	O20A0_OVI_TCON_SGEN_VBP_T                       tcon_sgen_vbp;	//0x009C
	O20A0_OVI_TCON_SGEN_VS_T                        tcon_sgen_vs;	//0x00A0
	O20A0_OVI_TCON_SGEN_VFP_T                       tcon_sgen_vfp;	//0x00A4
	O20A0_OVI_TCON_SGEN_DEWIDTH_T                   tcon_sgen_dewidth;	//0x00A8
	UINT32                                            reserved18;	//0xac
	O20A0_OVI_TCON_SGEN_DENUM_T                     tcon_sgen_denum;	//0x00B0
	UINT32                                            reserved19;	//0xb4
	O20A0_OVI_TCON_VBLANK_WIDTH_T                   tcon_vblank_width;	//0x00B8
	O20A0_OVI_TCON_VSYNC_WIDTH_T                    tcon_vsync_width;	//0x00BC
	UINT32                                            reserved21[5];	//0xc0-0xd0
	O20A0_OVI_TCON_PGEN_CTL_T                       tcon_pgen_ctl;	//0x00D4
	O20A0_OVI_TCON_MODE_CTL_T                       tcon_mode_ctl;	//0x00D8
	O20A0_OVI_TCON_PGEN_VSCR_T                      tcon_pgen_vscr;	//0x00DC
	O20A0_OVI_TCON_PGEN_HSCR_T                      tcon_pgen_hscr;	//0x00E0
	O20A0_OVI_TCON_PGEN_AGPR1_T                     tcon_pgen_agpr1;	//0x00E4
	O20A0_OVI_TCON_PGEN_AGPG1_T                     tcon_pgen_agpg1;	//0x00E8
	O20A0_OVI_TCON_PGEN_AGPB1_T                     tcon_pgen_agpb1;	//0x00EC
	O20A0_OVI_TCON_PGEN_AGPR2_T                     tcon_pgen_agpr2;	//0x00F0
	O20A0_OVI_TCON_PGEN_AGPG2_T                     tcon_pgen_agpg2;	//0x00F4
	O20A0_OVI_TCON_PGEN_AGPB2_T                     tcon_pgen_agpb2;	//0x00F8
	O20A0_OVI_TCON_PGEN_VLINE1_T                    tcon_pgen_vline1;	//0x00FC
	O20A0_OVI_TCON_PGEN_VLINE2_T                    tcon_pgen_vline2;	//0x0100
	O20A0_OVI_TCON_PGEN_HLINE1_T                    tcon_pgen_hline1;	//0x0104
	O20A0_OVI_TCON_PGEN_HLINE2_T                    tcon_pgen_hline2;	//0x0108
	O20A0_OVI_TCON_PGEN_VCOMP0_T                    tcon_pgen_vcomp0;	//0x010C
	O20A0_OVI_TCON_PGEN_VCOMP1_T                    tcon_pgen_vcomp1;	//0x0110
	O20A0_OVI_TCON_PGEN_VCOMP2_T                    tcon_pgen_vcomp2;	//0x0114
	O20A0_OVI_TCON_PGEN_VCOMP3_T                    tcon_pgen_vcomp3;	//0x0118
	UINT32                                            reserved39[5];	//0x11c-0x12c
	O20A0_OVI_TCON_DGA_MODE_T                       tcon_dga_mode;	//0x0130
	UINT32                                            reserved40[8];	//0x134-0x150
	O20A0_OVI_TCON_DITHER_CARRY_T                   tcon_dither_carry;	//0x0154
	UINT32                                            reserved41[32];	//0x158-0x1d4
	O20A0_OVI_TCON_MON_SEL_T                        tcon_mon_sel;	//0x01D8
	O20A0_OVI_TCON_INIT_TEST_T                      tcon_init_test;	//0x01DC
	UINT32                                            reserved43[72];	//0x1e0-0x2fc
	O20A0_OVI_TCON_DDIV_MODE_T                      tcon_ddiv_mode;	//0x0300
	O20A0_OVI_TCON_DDIV_HBLANK_T                    tcon_ddiv_hblank;	//0x0304
	O20A0_OVI_TCON_DDIV_HWIDTH_T                    tcon_ddiv_hwidth;	//0x0308
}OVI_TCON_REG_O22A0_T;

/*-----------------------------------------------------------------------------
                             0xcc449000L OIF_PCH_CONFIG                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pch_out_port                       :2 ,	// 1:0
	pch_en                             :1 ;	// 2 
}O20A0_OVI_OIF_PCH_CONFIG_T;
/*-----------------------------------------------------------------------------
                             0xcc449004L OIF_OCH_CONFIG                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	och_out_port                       :2 ,	// 1:0
	och_en                             :1 ;	// 2 
}O20A0_OVI_OIF_OCH_CONFIG_T;
/*-----------------------------------------------------------------------------
                             0xcc449008L OIF_VX1_CONFIG0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_out_mode                       :1 ,	// 0 
	vx1_en                             :1 ,	// 1 
	vx1_5byte                          :1 ,	// 2 
	vx1_video_mute                     :1 ,	// 3 
	vx1_sync_mute                      :1 ,	// 4 
	vx1_8k                             :1 ,	// 5 
	vx1_11bit_4byte                    :1 ;	// 6 
}O20A0_OVI_OIF_VX1_CONFIG0_T;
/*-----------------------------------------------------------------------------
                             0xcc44900cL OIF_VX1_CONFIG1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_resv13                         :2 ,	// 1:0
	vx1_resv12                         :2 ,	// 3:2
	vx1_resv11                         :2 ,	// 5:4
	vx1_resv10                         :2 ,	// 7:6
	vx1_resv9                          :2 ,	// 9:8
	vx1_resv8                          :2 ,	// 11:10
	vx1_resv7                          :2 ,	// 13:12
	vx1_resv6                          :2 ,	// 15:14
	vx1_resv5                          :2 ,	// 17:16
	vx1_resv4                          :2 ,	// 19:18
	vx1_resv3                          :2 ,	// 21:20
	vx1_resv2                          :2 ,	// 23:22
	vx1_resv1                          :2 ,	// 25:24
	vx1_resv0                          :2 ,	// 27:26
	vx1_resv_sel                       :4 ;	// 31:28
}O20A0_OVI_OIF_VX1_CONFIG1_T;
/*-----------------------------------------------------------------------------
                             0xcc449010L OIF_VX1_CONFIG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_resv15                         :2 ,	// 1:0
	vx1_resv14                         :2 ;	// 3:2
}O20A0_OVI_OIF_VX1_CONFIG2_T;
/*-----------------------------------------------------------------------------
                             0xcc449014L OIF_VX1_CONFIG3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_force_even_data                :31;	// 30:0
}O20A0_OVI_OIF_VX1_CONFIG3_T;
/*-----------------------------------------------------------------------------
                             0xcc449018L OIF_VX1_CONFIG4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_force_odd_data                 :31;	// 30:0
}O20A0_OVI_OIF_VX1_CONFIG4_T;
/*-----------------------------------------------------------------------------
                             0xcc44901cL OIF_LVDS_CONFIG0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_sel                           :15,	// 14:0
	lvds_swap                          :1 ,	// 15
	lvds_8bit_mode                     :1 ,	// 16
	lvds_lsb_first                     :1 ;	// 17
}O20A0_OVI_OIF_LVDS_CONFIG0_T;
/*-----------------------------------------------------------------------------
                             0xcc449020L OIF_LVDS_CONFIG1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_even_data               :31;	// 30:0
}O20A0_OVI_OIF_LVDS_CONFIG1_T;
/*-----------------------------------------------------------------------------
                             0xcc449024L OIF_LVDS_CONFIG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_odd_data                :31;	// 30:0
}O20A0_OVI_OIF_LVDS_CONFIG2_T;
/*-----------------------------------------------------------------------------
                             0xcc449028L OIF_LVDS_CONFIG3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_data                    :16,	// 15:0
	lvds_force_en                      :16;	// 31:16
}O20A0_OVI_OIF_LVDS_CONFIG3_T;
/*-----------------------------------------------------------------------------
                             0xcc449094L OIF_VX1_LANE_SEL0                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel3                          :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel2                          :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel1                          :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel0                          :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL0_T;
/*-----------------------------------------------------------------------------
                             0xcc449098L OIF_VX1_LANE_SEL1                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel7                          :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel6                          :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel5                          :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel4                          :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL1_T;
/*-----------------------------------------------------------------------------
                             0xcc44909cL OIF_VX1_LANE_SEL2                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel11                         :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel10                         :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel9                          :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel8                          :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL2_T;
/*-----------------------------------------------------------------------------
                             0xcc4490a0L OIF_VX1_LANE_SEL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel15                         :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel14                         :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel13                         :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel12                         :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL3_T;
/*-----------------------------------------------------------------------------
                             0xcc4490a4L OIF_VX1_LANE_SEL4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel19                         :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel18                         :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel17                         :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel16                         :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL4_T;
/*-----------------------------------------------------------------------------
                             0xcc4490a8L OIF_VX1_LANE_SEL5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel23                         :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	lane_sel22                         :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	lane_sel21                         :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	lane_sel20                         :5 ;	// 28:24
}O20A0_OVI_OIF_VX1_LANE_SEL5_T;
/*-----------------------------------------------------------------------------
                             0xcc4490acL OIF_VX1_APL_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_apl_line                       :12,	// 11:0
	vx1_apl_pix                        :12;	// 23:12
}O20A0_OVI_OIF_VX1_APL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xcc4490b0L OIF_VX1_INFO_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	info_ready_pix                     :12,	// 11:0
	info_en                            :1 ,	// 12
	info_repeat_mode                   :1 ;	// 13
}O20A0_OVI_OIF_VX1_INFO_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xcc4490b4L OIF_VX1_INFO_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	info_end_line                      :12,	// 11:0
	info_start_line                    :12;	// 23:12
}O20A0_OVI_OIF_VX1_INFO_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xcc4490b8L OIF_VX1_OSD_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	osd_ctl_ready_pix                  :12,	// 11:0
	osd_ctl_en                         :1 ;	// 12
}O20A0_OVI_OIF_VX1_OSD_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xcc4490bcL OIF_VX1_OSD_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	osd_ctl_end_line                   :12,	// 11:0
	osd_ctl_start_line                 :12;	// 23:12
}O20A0_OVI_OIF_VX1_OSD_CTRL1_T;

typedef struct
{
	O20A0_OVI_OIF_PCH_CONFIG_T                      oif_pch_config;	//0x9000
	O20A0_OVI_OIF_OCH_CONFIG_T                      oif_och_config;	//0x9004
	O20A0_OVI_OIF_VX1_CONFIG0_T                     oif_vx1_config0;	//0x9008
	O20A0_OVI_OIF_VX1_CONFIG1_T                     oif_vx1_config1;	//0x900C
	O20A0_OVI_OIF_VX1_CONFIG2_T                     oif_vx1_config2;	//0x9010
	O20A0_OVI_OIF_VX1_CONFIG3_T                     oif_vx1_config3;	//0x9014
	O20A0_OVI_OIF_VX1_CONFIG4_T                     oif_vx1_config4;	//0x9018
	O20A0_OVI_OIF_LVDS_CONFIG0_T                    oif_lvds_config0;	//0x901C
	O20A0_OVI_OIF_LVDS_CONFIG1_T                    oif_lvds_config1;	//0x9020
	O20A0_OVI_OIF_LVDS_CONFIG2_T                    oif_lvds_config2;	//0x9024
	O20A0_OVI_OIF_LVDS_CONFIG3_T                    oif_lvds_config3;	//0x9028
	UINT32                                            reserved57[26];	//0x902c-0x9090
	O20A0_OVI_OIF_VX1_LANE_SEL0_T                  oif_vx1_lane_sel0 ;	//0x9094
	O20A0_OVI_OIF_VX1_LANE_SEL1_T                  oif_vx1_lane_sel1 ;	//0x9098
	O20A0_OVI_OIF_VX1_LANE_SEL2_T                  oif_vx1_lane_sel2 ;	//0x909C
	O20A0_OVI_OIF_VX1_LANE_SEL3_T                   oif_vx1_lane_sel3;	//0x90A0
	O20A0_OVI_OIF_VX1_LANE_SEL4_T                   oif_vx1_lane_sel4;	//0x90A4
	O20A0_OVI_OIF_VX1_LANE_SEL5_T                   oif_vx1_lane_sel5;	//0x90A8
	O20A0_OVI_OIF_VX1_APL_CTRL_T                    oif_vx1_apl_ctrl;	//0x90AC
	O20A0_OVI_OIF_VX1_INFO_CTRL0_T                  oif_vx1_info_ctrl0;	//0x90B0
	O20A0_OVI_OIF_VX1_INFO_CTRL1_T                  oif_vx1_info_ctrl1;	//0x90B4
	O20A0_OVI_OIF_VX1_OSD_CTRL0_T                   oif_vx1_osd_ctrl0;	//0x90B8
	O20A0_OVI_OIF_VX1_OSD_CTRL1_T                   oif_vx1_osd_ctrl1;	//0x90BC
}OVI_OIF_REG_O22A0_T;
#endif