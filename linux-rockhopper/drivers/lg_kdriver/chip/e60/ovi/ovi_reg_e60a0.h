/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

#ifndef _REG_OVI_E60A0_h
#define _REG_OVI_E60A0_h

/*-----------------------------------------------------------------------------
                             0xc90b0004L TCON_CONTROL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	_rsvd                              :1 ,	// 0 
	wb_en                              :1 ,	// 1 
	dga_en                             :1 ,	// 2 
	pre_dither_en                      :1 ;	// 3 
}E60A0_OVI_TCON_CONTROL_T;
/*-----------------------------------------------------------------------------
                             0xc90b0008L TCON_TEST_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	_rsvd_00                           :1 ,	// 0 
	wb_left_en                         :1 ,	// 1 
	dga_left_en                        :1 ,	// 2 
	pre_dither_left_en                 :1 ,	// 3 
	_rsvd_01                           :1 ,	// 4 
	_rsvd_02                           :1 ,	// 5 
	_rsvd_03                           :1 ,	// 6 
	bypass_en                          :1 ;	// 7 
}E60A0_OVI_TCON_TEST_CTL_T;
/*-----------------------------------------------------------------------------
                             0xc90b000cL TCON_SYNC_CTL                             
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
	_rsvd                              :1 ;	// 7 
}E60A0_OVI_TCON_SYNC_CTL_T;
/*-----------------------------------------------------------------------------
                             0xc90b0010L TCON_STS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix2_lock                          :1 ,	// 0 
	init_done1                         :1 ,	// 1 
	init_done2                         :1 ,	// 2 
	_rsvd_00                           :1 ,	// 3 
	_rsvd_01                           :1 ,	// 4 
	_rsvd_02                           :1 ,	// 5 
	_rsvd_03                           :1 ,	// 6 
	_rsvd_04                           :1 ;	// 7 
}E60A0_OVI_TCON_STS_T;
/*-----------------------------------------------------------------------------
                             0xc90b0060L TCON_WB_RGAIN_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_r_gain                          :16;	// 15:0
}E60A0_OVI_TCON_WB_RGAIN_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0068L TCON_WB_ROFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_r_offset                        :16;	// 15:0
}E60A0_OVI_TCON_WB_ROFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0070L TCON_WB_GGAIN_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_g_gain                          :16;	// 15:0
}E60A0_OVI_TCON_WB_GGAIN_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0078L TCON_WB_GOFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_g_offset                        :16;	// 15:0
}E60A0_OVI_TCON_WB_GOFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0080L TCON_WB_BGAIN_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_b_gain                          :16;	// 15:0
}E60A0_OVI_TCON_WB_BGAIN_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0088L TCON_WB_BOFFSET_U                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wb_b_offset                        :16;	// 15:0
}E60A0_OVI_TCON_WB_BOFFSET_U_T;
/*-----------------------------------------------------------------------------
                             0xc90b0090L TCON_SGEN_HBP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hbp                           :12;	// 11:0
}E60A0_OVI_TCON_SGEN_HBP_T;
/*-----------------------------------------------------------------------------
                             0xc90b0094L TCON_SGEN_HS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hs                            :12;	// 11:0
}E60A0_OVI_TCON_SGEN_HS_T;
/*-----------------------------------------------------------------------------
                             0xc90b0098L TCON_SGEN_HFP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_hfp                           :12;	// 11:0
}E60A0_OVI_TCON_SGEN_HFP_T;
/*-----------------------------------------------------------------------------
                             0xc90b009cL TCON_SGEN_VBP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vbp                           :12;	// 11:0
}E60A0_OVI_TCON_SGEN_VBP_T;
/*-----------------------------------------------------------------------------
                             0xc90b00a0L TCON_SGEN_VS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vs                            :12;	// 11:0
}E60A0_OVI_TCON_SGEN_VS_T;
/*-----------------------------------------------------------------------------
                             0xc90b00a4L TCON_SGEN_VFP                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_vfp                           :12;	// 11:0
}E60A0_OVI_TCON_SGEN_VFP_T;
/*-----------------------------------------------------------------------------
                             0xc90b00a8L TCON_SGEN_DEWIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_dewidth                       :12;	// 11:0
}E60A0_OVI_TCON_SGEN_DEWIDTH_T;
/*-----------------------------------------------------------------------------
                             0xc90b00b0L TCON_SGEN_DENUM                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgen_denumber                      :12;	// 11:0
}E60A0_OVI_TCON_SGEN_DENUM_T;
/*-----------------------------------------------------------------------------
                             0xc90b00b8L TCON_VBLANK_WIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ver_blank_width                    :8 ;	// 7:0
}E60A0_OVI_TCON_VBLANK_WIDTH_T;
/*-----------------------------------------------------------------------------
                             0xc90b00bcL TCON_VSYNC_WIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync_width                        :8 ;	// 7:0
}E60A0_OVI_TCON_VSYNC_WIDTH_T;
/*-----------------------------------------------------------------------------
                             0xc90b00d4L TCON_PGEN_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_test                          :1 ,	// 0 
	pgen_sync_mode                     :1 ,	// 1 
	pgen_reverse                       :1 ,	// 2 
	pgen_mode                          :5 ;	// 7:3
}E60A0_OVI_TCON_PGEN_CTL_T;
/*-----------------------------------------------------------------------------
                             0xc90b00d8L TCON_MODE_CTL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mode_test                          :1 ,	// 0 
	mode_test_sel                      :1 ;	// 1 
}E60A0_OVI_TCON_MODE_CTL_T;
/*-----------------------------------------------------------------------------
                             0xc90b00dcL TCON_PGEN_VSCR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vscr_val                      :8 ,	// 7:0
	pgen_vscr_en                       :1 ,	// 8 
	pgen_vscr_up                       :1 ;	// 9 
}E60A0_OVI_TCON_PGEN_VSCR_T;
/*-----------------------------------------------------------------------------
                             0xc90b00e0L TCON_PGEN_HSCR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hscr_val                      :8 ,	// 7:0
	pgen_hscr_en                       :1 ,	// 8 
	pgen_hscr_left                     :1 ;	// 9 
}E60A0_OVI_TCON_PGEN_HSCR_T;
/*-----------------------------------------------------------------------------
                             0xc90b00e4L TCON_PGEN_AGPR1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_r1                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPR1_T;
/*-----------------------------------------------------------------------------
                             0xc90b00e8L TCON_PGEN_AGPG1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_g1                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPG1_T;
/*-----------------------------------------------------------------------------
                             0xc90b00ecL TCON_PGEN_AGPB1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_b1                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPB1_T;
/*-----------------------------------------------------------------------------
                             0xc90b00f0L TCON_PGEN_AGPR2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_r2                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPR2_T;
/*-----------------------------------------------------------------------------
                             0xc90b00f4L TCON_PGEN_AGPG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_g2                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPG2_T;
/*-----------------------------------------------------------------------------
                             0xc90b00f8L TCON_PGEN_AGPB2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_color_b2                      :10;	// 9:0
}E60A0_OVI_TCON_PGEN_AGPB2_T;
/*-----------------------------------------------------------------------------
                             0xc90b00fcL TCON_PGEN_VLINE1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vline1                        :12;	// 11:0
}E60A0_OVI_TCON_PGEN_VLINE1_T;
/*-----------------------------------------------------------------------------
                             0xc90b0100L TCON_PGEN_VLINE2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vline2                        :12;	// 11:0
}E60A0_OVI_TCON_PGEN_VLINE2_T;
/*-----------------------------------------------------------------------------
                             0xc90b0104L TCON_PGEN_HLINE1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hpixel1                       :12;	// 11:0
}E60A0_OVI_TCON_PGEN_HLINE1_T;
/*-----------------------------------------------------------------------------
                             0xc90b0108L TCON_PGEN_HLINE2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_hpixel2                       :12;	// 11:0
}E60A0_OVI_TCON_PGEN_HLINE2_T;
/*-----------------------------------------------------------------------------
                             0xc90b010cL TCON_PGEN_VCOMP0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp0                        :24;	// 23:0
}E60A0_OVI_TCON_PGEN_VCOMP0_T;
/*-----------------------------------------------------------------------------
                             0xc90b0110L TCON_PGEN_VCOMP1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp1                        :24;	// 23:0
}E60A0_OVI_TCON_PGEN_VCOMP1_T;
/*-----------------------------------------------------------------------------
                             0xc90b0114L TCON_PGEN_VCOMP2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp2                        :24;	// 23:0
}E60A0_OVI_TCON_PGEN_VCOMP2_T;
/*-----------------------------------------------------------------------------
                             0xc90b0118L TCON_PGEN_VCOMP3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pgen_vcomp3                        :24;	// 23:0
}E60A0_OVI_TCON_PGEN_VCOMP3_T;
/*-----------------------------------------------------------------------------
                             0xc90b0130L TCON_DGA_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dga_up_mode                        :1 ,	// 0 
	dga_upload                         :1 ,	// 1 
	dga_r_mode                         :1 ;	// 2 
}E60A0_OVI_TCON_DGA_MODE_T;
/*-----------------------------------------------------------------------------
                             0xc90b0134L TCON_DGA_SEL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dga_rgb0                           :24;	// 23:0
}E60A0_OVI_TCON_DGA_SEL0_T;
/*-----------------------------------------------------------------------------
                             0xc90b0138L TCON_DGA_SEL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dga_rgb1                           :24;	// 23:0
}E60A0_OVI_TCON_DGA_SEL1_T;
/*-----------------------------------------------------------------------------
                             0xc90b0154L TCON_DITHER_CARRY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_dither_sel                     :3 ,	// 2:0
	_rsvd_00                           :1 ,	// reserved
	post_dither_sel                    :3 ;	// 6:4
}E60A0_OVI_TCON_DITHER_CARRY_T;
/*-----------------------------------------------------------------------------
                             0xc90b01d8L TCON_MON_SEL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mon_sel0                           :1 ,	// 0 
	mon_sel1                           :1 ;	// 1 
}E60A0_OVI_TCON_MON_SEL_T;
/*-----------------------------------------------------------------------------
                             0xc90b01dcL TCON_INIT_TEST                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	init1_test                         :1 ,	// 0 
	init2_test                         :1 ;	// 1 
}E60A0_OVI_TCON_INIT_TEST_T;
/*-----------------------------------------------------------------------------
                             0xc90b0300L TCON_DDIV_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_delay                         :1 ,	// 0 
	rd_mode                            :1 ,	// 1 
	drd_mode                           :1 ,	// 2 
	epi10                              :1 ,	// 3 
	lane_num                           :5 ,	// 8:4
	_rsvd                              :3 ,	// reserved
	division                           :5 ;	// 16:12
}E60A0_OVI_TCON_DDIV_MODE_T;
/*-----------------------------------------------------------------------------
                             0xc90b0304L TCON_DDIV_HBLANK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hb_width                           :12,	// 11:0
	drd_h_blank                        :9 ;	// 20:12
}E60A0_OVI_TCON_DDIV_HBLANK_T;
/*-----------------------------------------------------------------------------
                             0xc90b0308L TCON_DDIV_HWIDTH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ddiv_hwidth                        :12;	// 11:0
}E60A0_OVI_TCON_DDIV_HWIDTH_T;
/*-----------------------------------------------------------------------------
                             0xc90b8640L TCON_END                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	_rsvd;	// 0:31
}E60A0_OVI_TCON_END_T;

typedef struct
{ 
	UINT32                                            _rsvd_00;	//0x0000
	E60A0_OVI_TCON_CONTROL_T                        tcon_control;	//0x0004
	E60A0_OVI_TCON_TEST_CTL_T                       tcon_test_ctl;	//0x0008
	E60A0_OVI_TCON_SYNC_CTL_T                       tcon_sync_ctl;	//0x000C
	E60A0_OVI_TCON_STS_T                            tcon_sts;	//0x0010
	UINT32                                          _rsvd_001;	//0x14
	UINT32                        					_rsvd_002;	//0x0018
	UINT32                        					tcon_pgen_path;	//0x001C
	UINT32                                            _rsvd_01[16];	//0x20-0x5c
	E60A0_OVI_TCON_WB_RGAIN_U_T                     tcon_wb_rgain_u;	//0x0060
	UINT32                                            _rsvd_02;	//0x64
	E60A0_OVI_TCON_WB_ROFFSET_U_T                   tcon_wb_roffset_u;	//0x0068
	UINT32                                            _rsvd_03;	//0x6c
	E60A0_OVI_TCON_WB_GGAIN_U_T                     tcon_wb_ggain_u;	//0x0070
	UINT32                                            _rsvd_04;	//0x74
	E60A0_OVI_TCON_WB_GOFFSET_U_T                   tcon_wb_goffset_u;	//0x0078
	UINT32                                            _rsvd_05;	//0x7c
	E60A0_OVI_TCON_WB_BGAIN_U_T                     tcon_wb_bgain_u;	//0x0080
	UINT32                                            _rsvd_06;	//0x84
	E60A0_OVI_TCON_WB_BOFFSET_U_T                   tcon_wb_boffset_u;	//0x0088
	UINT32                                            _rsvd_07;	//0x8c
	E60A0_OVI_TCON_SGEN_HBP_T                       tcon_sgen_hbp;	//0x0090
	E60A0_OVI_TCON_SGEN_HS_T                        tcon_sgen_hs;	//0x0094
	E60A0_OVI_TCON_SGEN_HFP_T                       tcon_sgen_hfp;	//0x0098
	E60A0_OVI_TCON_SGEN_VBP_T                       tcon_sgen_vbp;	//0x009C
	E60A0_OVI_TCON_SGEN_VS_T                        tcon_sgen_vs;	//0x00A0
	E60A0_OVI_TCON_SGEN_VFP_T                       tcon_sgen_vfp;	//0x00A4
	E60A0_OVI_TCON_SGEN_DEWIDTH_T                   tcon_sgen_dewidth;	//0x00A8
	UINT32                                            _rsvd_08;	//0xac
	E60A0_OVI_TCON_SGEN_DENUM_T                     tcon_sgen_denum;	//0x00B0
	UINT32                                            _rsvd_09;	//0xb4
	E60A0_OVI_TCON_VBLANK_WIDTH_T                   tcon_vblank_width;	//0x00B8
	E60A0_OVI_TCON_VSYNC_WIDTH_T                    tcon_vsync_width;	//0x00BC
	UINT32                                            _rsvd_10[5];	//0xc0-0xd0
	E60A0_OVI_TCON_PGEN_CTL_T                       tcon_pgen_ctl;	//0x00D4
	E60A0_OVI_TCON_MODE_CTL_T                       tcon_mode_ctl;	//0x00D8
	E60A0_OVI_TCON_PGEN_VSCR_T                      tcon_pgen_vscr;	//0x00DC
	E60A0_OVI_TCON_PGEN_HSCR_T                      tcon_pgen_hscr;	//0x00E0
	E60A0_OVI_TCON_PGEN_AGPR1_T                     tcon_pgen_agpr1;	//0x00E4
	E60A0_OVI_TCON_PGEN_AGPG1_T                     tcon_pgen_agpg1;	//0x00E8
	E60A0_OVI_TCON_PGEN_AGPB1_T                     tcon_pgen_agpb1;	//0x00EC
	E60A0_OVI_TCON_PGEN_AGPR2_T                     tcon_pgen_agpr2;	//0x00F0
	E60A0_OVI_TCON_PGEN_AGPG2_T                     tcon_pgen_agpg2;	//0x00F4
	E60A0_OVI_TCON_PGEN_AGPB2_T                     tcon_pgen_agpb2;	//0x00F8
	E60A0_OVI_TCON_PGEN_VLINE1_T                    tcon_pgen_vline1;	//0x00FC
	E60A0_OVI_TCON_PGEN_VLINE2_T                    tcon_pgen_vline2;	//0x0100
	E60A0_OVI_TCON_PGEN_HLINE1_T                    tcon_pgen_hline1;	//0x0104
	E60A0_OVI_TCON_PGEN_HLINE2_T                    tcon_pgen_hline2;	//0x0108
	E60A0_OVI_TCON_PGEN_VCOMP0_T                    tcon_pgen_vcomp0;	//0x010C
	E60A0_OVI_TCON_PGEN_VCOMP1_T                    tcon_pgen_vcomp1;	//0x0110
	E60A0_OVI_TCON_PGEN_VCOMP2_T                    tcon_pgen_vcomp2;	//0x0114
	E60A0_OVI_TCON_PGEN_VCOMP3_T                    tcon_pgen_vcomp3;	//0x0118
	UINT32                                            _rsvd_11[5];	//0x11c-0x12c
	E60A0_OVI_TCON_DGA_MODE_T                       tcon_dga_mode;	//0x0130
	E60A0_OVI_TCON_DGA_SEL0_T                       tcon_dga_sel0;	//0x0134
	E60A0_OVI_TCON_DGA_SEL1_T                       tcon_dga_sel1;	//0x0138
	UINT32                                            _rsvd_12[6];	//0x13c-0x150
	E60A0_OVI_TCON_DITHER_CARRY_T                   tcon_dither_carry;	//0x0154
	UINT32                                            _rsvd_13[32];	//0x158-0x1d4
	E60A0_OVI_TCON_MON_SEL_T                        tcon_mon_sel;	//0x01D8
	E60A0_OVI_TCON_INIT_TEST_T                      tcon_init_test;	//0x01DC
	UINT32                                            _rsvd_14[72];	//0x1e0-0x2fc
	E60A0_OVI_TCON_DDIV_MODE_T                      tcon_ddiv_mode;	//0x0300
	E60A0_OVI_TCON_DDIV_HBLANK_T                    tcon_ddiv_hblank;	//0x0304
	E60A0_OVI_TCON_DDIV_HWIDTH_T                    tcon_ddiv_hwidth;	//0x0308
	UINT32                                            _rsvd_15[8397];	//0x30c-0x863c
	E60A0_OVI_TCON_END_T                            tcon_end;	//0x8640
} OVI_TCON_REG_E60A0_T;

/*-----------------------------------------------------------------------------
                             0xc90b9000L OIF_PCH_CONFIG                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pch_out_port                       :2 ,	// 1:0
	pch_en                             :1 ;	// 2 
}E60A0_OVI_OIF_PCH_CONFIG_T;
/*-----------------------------------------------------------------------------
                             0xc90b9004L OIF_OCH_CONFIG                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	och_out_port                       :2 ,	// 1:0
	och_en                             :1 ;	// 2 
}E60A0_OVI_OIF_OCH_CONFIG_T;
/*-----------------------------------------------------------------------------
                             0xc90b9008L OIF_VX1_CONFIG0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_out_mode                       :1 ,	// 0 
	vx1_en                             :1 ,	// 1 
	vx1_5byte                          :1 ,	// 2 
	vx1_video_mute                     :1 ,	// 3 
	vx1_sync_mute                      :1 ;	// 4 
}E60A0_OVI_OIF_VX1_CONFIG0_T;
/*-----------------------------------------------------------------------------
                             0xc90b900cL OIF_VX1_CONFIG1                             
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
}E60A0_OVI_OIF_VX1_CONFIG1_T;
/*-----------------------------------------------------------------------------
                             0xc90b9010L OIF_VX1_CONFIG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_resv15                         :2 ,	// 1:0
	vx1_resv14                         :2 ;	// 3:2
}E60A0_OVI_OIF_VX1_CONFIG2_T;
/*-----------------------------------------------------------------------------
                             0xc90b9014L OIF_VX1_CONFIG3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_force_even_data                :31;	// 30:0
}E60A0_OVI_OIF_VX1_CONFIG3_T;
/*-----------------------------------------------------------------------------
                             0xc90b9018L OIF_VX1_CONFIG4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_force_odd_data                 :31;	// 30:0
}E60A0_OVI_OIF_VX1_CONFIG4_T;
/*-----------------------------------------------------------------------------
                             0xc90b901cL OIF_LVDS_CONFIG0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_sel                           :15,	// 14:0
	lvds_swap                          :1 ,	// 15
	lvds_8bit_mode                     :1 ,	// 16
	lvds_lsb_first                     :1 ;	// 17
}E60A0_OVI_OIF_LVDS_CONFIG0_T;
/*-----------------------------------------------------------------------------
                             0xc90b9020L OIF_LVDS_CONFIG1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_even_data               :31;	// 30:0
}E60A0_OVI_OIF_LVDS_CONFIG1_T;
/*-----------------------------------------------------------------------------
                             0xc90b9024L OIF_LVDS_CONFIG2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_odd_data                :31;	// 30:0
}E60A0_OVI_OIF_LVDS_CONFIG2_T;
/*-----------------------------------------------------------------------------
                             0xc90b9028L OIF_LVDS_CONFIG3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lvds_force_data                    :16,	// 15:0
	lvds_force_en                      :16;	// 31:16
}E60A0_OVI_OIF_LVDS_CONFIG3_T;
/*-----------------------------------------------------------------------------
                             0xc90b9094L OIF_VX1_LANE_SEL0                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel3                          :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel2                          :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel1                          :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel0                          :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL0_T;
/*-----------------------------------------------------------------------------
                             0xc90b9098L OIF_VX1_LANE_SEL1                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel7                          :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel6                          :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel5                          :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel4                          :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL1_T;
/*-----------------------------------------------------------------------------
                             0xc90b909cL OIF_VX1_LANE_SEL2                              
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel11                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel10                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel9                          :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel8                          :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL2_T;
/*-----------------------------------------------------------------------------
                             0xc90b90a0L OIF_VX1_LANE_SEL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel15                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel14                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel13                         :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel12                         :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL3_T;
/*-----------------------------------------------------------------------------
                             0xc90b90a4L OIF_VX1_LANE_SEL4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel19                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel18                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel17                         :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel16                         :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL4_T;
/*-----------------------------------------------------------------------------
                             0xc90b90a8L OIF_VX1_LANE_SEL5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel23                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel22                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel21                         :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel20                         :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL5_T;
/*-----------------------------------------------------------------------------
                             0xc90b90acL OIF_VX1_LANE_SEL6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel27                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel26                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel25                         :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel24                         :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL6_T;
/*-----------------------------------------------------------------------------
                             0xc90b90b0L OIF_VX1_LANE_SEL7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lane_sel31                         :5 ,	// 4:0
	_rsvd_00                           :3 ,	// reserved
	lane_sel30                         :5 ,	// 12:8
	_rsvd_01                           :3 ,	// reserved
	lane_sel29                         :5 ,	// 20:16
	_rsvd_02                           :3 ,	// reserved
	lane_sel28                         :5 ;	// 28:24
}E60A0_OVI_OIF_VX1_LANE_SEL7_T;
/*-----------------------------------------------------------------------------
                             0xc90b90d4L OIF_VX1_APL_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vx1_apl_line                       :12,	// 11:0
	vx1_apl_pix                        :12;	// 23:12
}E60A0_OVI_OIF_VX1_APL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90b90d8L OIF_VX1_INFO_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	info_ready_pix                     :12,	// 11:0
	info_en                            :1 ,	// 12
	info_repeat_mode                   :1 ;	// 13
}E60A0_OVI_OIF_VX1_INFO_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc90b90dcL OIF_VX1_INFO_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	info_end_line                      :12,	// 11:0
	info_start_line                    :12;	// 23:12
}E60A0_OVI_OIF_VX1_INFO_CTRL1_T;

typedef struct
{
	E60A0_OVI_OIF_PCH_CONFIG_T                      oif_pch_config;	//0x9000
	E60A0_OVI_OIF_OCH_CONFIG_T                      oif_och_config;	//0x9004
	E60A0_OVI_OIF_VX1_CONFIG0_T                     oif_vx1_config0;	//0x9008
	E60A0_OVI_OIF_VX1_CONFIG1_T                     oif_vx1_config1;	//0x900C
	E60A0_OVI_OIF_VX1_CONFIG2_T                     oif_vx1_config2;	//0x9010
	E60A0_OVI_OIF_VX1_CONFIG3_T                     oif_vx1_config3;	//0x9014
	E60A0_OVI_OIF_VX1_CONFIG4_T                     oif_vx1_config4;	//0x9018
	E60A0_OVI_OIF_LVDS_CONFIG0_T                    oif_lvds_config0;	//0x901C
	E60A0_OVI_OIF_LVDS_CONFIG1_T                    oif_lvds_config1;	//0x9020
	E60A0_OVI_OIF_LVDS_CONFIG2_T                    oif_lvds_config2;	//0x9024
	E60A0_OVI_OIF_LVDS_CONFIG3_T                    oif_lvds_config3;	//0x9028
	UINT32                                            _rsvd_00[26];	//0x902c-0x9090
	E60A0_OVI_OIF_VX1_LANE_SEL0_T                  oif_vx1_lane_sel0 ;	//0x9094
	E60A0_OVI_OIF_VX1_LANE_SEL1_T                  oif_vx1_lane_sel1 ;	//0x9098
	E60A0_OVI_OIF_VX1_LANE_SEL2_T                  oif_vx1_lane_sel2 ;	//0x909C
	E60A0_OVI_OIF_VX1_LANE_SEL3_T                   oif_vx1_lane_sel3;	//0x90A0
	E60A0_OVI_OIF_VX1_LANE_SEL4_T                   oif_vx1_lane_sel4;	//0x90A4
	E60A0_OVI_OIF_VX1_LANE_SEL5_T                   oif_vx1_lane_sel5;	//0x90A8
	E60A0_OVI_OIF_VX1_LANE_SEL6_T                   oif_vx1_lane_sel6;	//0x90AC
	E60A0_OVI_OIF_VX1_LANE_SEL7_T                   oif_vx1_lane_sel7;	//0x90B0
	UINT32                                            _rsvd_01[8];	//0x90B4-0x90D0
	E60A0_OVI_OIF_VX1_APL_CTRL_T                    oif_vx1_apl_ctrl;	//0x90D4
	E60A0_OVI_OIF_VX1_INFO_CTRL0_T                  oif_vx1_info_ctrl0;	//0x90D8
	E60A0_OVI_OIF_VX1_INFO_CTRL1_T                  oif_vx1_info_ctrl1;	//0x90DC
}OVI_OIF_REG_E60A0_T;
#endif