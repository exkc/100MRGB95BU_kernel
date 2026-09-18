#ifndef _PE_OSD_REG_O24A0_H_
#define _PE_OSD_REG_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C00 RW
	UINT32 resvd0                           :4;
	UINT32 reg_top_detour                   :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_bypass                   :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//8:8	//0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}PE_O24_SHP_OSD0_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C04 RW
	UINT32 reg_core_width                   :16;	//15:0	//processing width  (default : 7680)
	UINT32 reg_core_height                  :16;	//31:16	//processing height (default : 4320)
	};
}PE_O24_SHP_OSD0_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C08 RW
	UINT32 reg_core0_width                  :16;	//15:0	//processing width  (default : 2016 = 1920 + 48 + 48)
	UINT32 reg_core0_height                 :16;	//31:16	//processing height (default : 4320)
	};
}PE_O24_SHP_OSD0_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C0C RW
	UINT32 reg_core1_width                  :16;	//15:0	//processing width  (default : 2016 = 1920 + 48 + 48)
	UINT32 reg_core1_height                 :16;	//31:16	//processing height (default : 4320)
	};
}PE_O24_SHP_OSD0_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C18 RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid (= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_SHP_OSD0_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C1C RW
	UINT32 reg_top_prefetch_cnt             :12;	//11:0	//Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//27:16	//Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C20 RW
	UINT32 reg_top_update_ctrl              :5;	//4:0	//[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O24_SHP_OSD0_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C30 RW
	UINT32 reg_split_pmode_out              :3;	//2:0	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd0                           :1;
	UINT32 reg_split_pmode_in               :3;	//6:4	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd1                           :1;
	UINT32 reg_split_split_mode             :2;	//9:8	//Split Configuation Select	0 := (S0 + 2GB) + (GB+S1+GB) + (GB+S2+GB) + (2GB+S3)	2 = (S0 + GB) + (GB+S1+GB) + (GB+S2+GB) + (GB+S3)	3 = (S0 + 0) + (GB+S1+0) + (GB+S2+0) + (GB+S3)
	UINT32 resvd2                           :2;
	UINT32 reg_split_sync_mode              :1;	//12 //0:= ready-valid mode	1 = sync_mode
	UINT32 resvd3                           :3;
	UINT32 reg_split_hsize                  :13;	//28:16	//
	UINT32 resvd4                           :3;
	};
}PE_O24_SHP_OSD0_SPLIT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C34 RW
	UINT32 reg_split_split_size             :13;	//12:0	//split size ( size in unit pixels)	ex) split-4 case	reg_split_size = reg_hsize / 4
	UINT32 resvd0                           :3;
	UINT32 reg_split_guardband              :13;	//28:16	//guardband (size in unit pixels)
	UINT32 resvd1                           :3;
	};
}PE_O24_SHP_OSD0_SPLIT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C38 RW
	UINT32 reg_split_split_ctrl_02          :32;	//31:0	//reserved
	};
}PE_O24_SHP_OSD0_SPLIT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C3C RW
	UINT32 reg_split_split_ctrl_03          :32;	//31:0	//reserved
	};
}PE_O24_SHP_OSD0_SPLIT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C40 RW
	UINT32 reg_merge_pmode_out              :3;	//2:0	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd0                           :1;
	UINT32 reg_merge_pmode_in               :3;	//6:4	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd1                           :1;
	UINT32 reg_merge_split_mode             :2;	//9:8	//Split Configuation Select	0 := (S0 + 2GB) + (GB+S1+GB) + (GB+S2+GB) + (2GB+S3)	2 = (S0 + GB) + (GB+S1+GB) + (GB+S2+GB) + (GB+S3)	3 = (S0 + 0) + (GB+S1+0) + (GB+S2+0) + (GB+S3)
	UINT32 resvd2                           :2;
	UINT32 reg_merge_sync_mode              :1;	//12 //0:= ready-valid mode	1 = sync_mode
	UINT32 resvd3                           :3;
	UINT32 reg_merge_hsize                  :13;	//28:16	//
	UINT32 resvd4                           :3;
	};
}PE_O24_SHP_OSD0_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C44 RW
	UINT32 reg_merge_split_size             :13;	//12:0	//split size ( size in unit pixels)	ex) split-4 case	reg_split_size = reg_hsize / 4
	UINT32 resvd0                           :3;
	UINT32 reg_merge_guardband              :13;	//28:16	//guardband (size in unit pixels)
	UINT32 resvd1                           :3;
	};
}PE_O24_SHP_OSD0_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C48 RW
	UINT32 reg_merge_fifo_th                :9;	//8:0	//Merge begins on the line basis satifying following condition	fifo_status[reg_fifo_sel] >= reg_fifo_th
	UINT32 resvd0                           :7;
	UINT32 reg_merge_fifo_sel               :3;	//18:16	//0 := fifo 0	1 = fifo 1	2 = fifo 2	3 = fifo 3	4 = fifo 4	5 = fifo 5	6 = fifo 6	7 = fifo 7
	UINT32 resvd1                           :13;
	};
}PE_O24_SHP_OSD0_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C4C RW
	UINT32 reg_merge_ctrl_03                :32;	//31:0	//reserved
	};
}PE_O24_SHP_OSD0_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C50 RW
	UINT32 reg_pat_en                       :1;	//0:0	//pattern enable
	UINT32 reg_pat_thickness                :2;	//2:1	//pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//15:8	//pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}PE_O24_SHP_OSD0_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C60 RW
	UINT32 reg_hti_enable                   :1;	//0:0	//HTI enable
	UINT32 reg_hti_debug_map_en             :1;	//1:1	//HTI debug map enable
	UINT32 reg_hti_mm_tap_size              :2;	//3:2	//HTI mm tap size
	UINT32 reg_hti_avg_tap_size             :2;	//5:4	//HTI avg tap size
	UINT32 reg_hti_ti_mode                  :1;	//6:6	//HTI ti mode
	UINT32 resvd0                           :1;
	UINT32 reg_hti_master_gain              :8;	//15:8	//HTI master gain
	UINT32 reg_hti_coring_en                :1;	//16:16	//HTI coring enable
	UINT32 resvd1                           :15;
	};
}PE_O24_SHP_OSD0_HTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C64 RW
	UINT32 reg_hti_coring_lut_y0            :8;	//7:0	//HTI coring LUT, x0
	UINT32 reg_hti_coring_lut_x0            :8;	//15:8	//HTI coring LUT, x1
	UINT32 reg_hti_coring_lut_y1            :8;	//23:16	//HTI coring LUT, y0
	UINT32 reg_hti_coring_lut_x1            :8;	//31:24	//HTI coring LUT, y1
	};
}PE_O24_SHP_OSD0_HTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C68 RW
	UINT32 reg_win_hti_core0_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_hti_core0_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_hti_core0_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_hti_core0_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_hti_core0_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_hti_core0_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_hti_core0_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_win_hti_core0_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_win_hti_core0_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_win_hti_core0_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_win_hti_core0_yy6            :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C6C RW
	UINT32 reg_win_hti_core0_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core0_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C70 RW
	UINT32 reg_win_hti_core0_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core0_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C74 RW
	UINT32 reg_win_hti_core0_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core0_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C78 RW
	UINT32 reg_win_hti_core0_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core0_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C7C RW
	UINT32 reg_win_hti_core1_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_hti_core1_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_hti_core1_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_hti_core1_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_hti_core1_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_hti_core1_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_hti_core1_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_win_hti_core1_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_win_hti_core1_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_win_hti_core1_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_win_hti_core1_yy6            :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C80 RW
	UINT32 reg_win_hti_core1_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core1_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C84 RW
	UINT32 reg_win_hti_core1_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core1_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C88 RW
	UINT32 reg_win_hti_core1_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core1_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033C8C RW
	UINT32 reg_win_hti_core1_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_core1_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CC0 RW
	UINT32 reg_vti_enable                   :1;	//0:0	//VTI enable
	UINT32 reg_vti_debug_map_en             :1;	//1:1	//VTI debug map enable
	UINT32 reg_vti_mm_tap_size              :2;	//3:2	//VTI mm tap size
	UINT32 reg_vti_avg_tap_size             :2;	//5:4	//VTI avg tap size
	UINT32 reg_vti_ti_mode                  :1;	//6:6	//VTI ti mode
	UINT32 resvd0                           :1;
	UINT32 reg_vti_master_gain              :8;	//15:8	//VTI master gain
	UINT32 resvd1                           :16;
	};
}PE_O24_SHP_OSD0_VTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CD0 RW
	UINT32 reg_lti_2d_en                    :1;	//0:0	//LTI enable
	UINT32 reg_lti_tap_size                 :2;	//2:1	//LTI tap size	0: 11x7	1: 7x5	2: 5x3	3: 3x3
	UINT32 resvd0                           :1;
	UINT32 reg_lti_coring_en                :1;	//4:4	//LTI coring enable
	UINT32 resvd1                           :3;
	UINT32 reg_lti_2d_gain                  :8;	//15:8	//LTI gain
	UINT32 reg_lti_2d_limit                 :10;	//25:16	//LTI bound limit
	UINT32 resvd2                           :6;
	};
}PE_O24_SHP_OSD0_LTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CD4 RW
	UINT32 reg_lti_coring_lut_y0            :8;	//7:0	//LTI coring LUT, x0
	UINT32 reg_lti_coring_lut_x0            :8;	//15:8	//LTI coring LUT, x1
	UINT32 reg_lti_coring_lut_y1            :8;	//23:16	//LTI coring LUT, y0
	UINT32 reg_lti_coring_lut_x1            :8;	//31:24	//LTI coring LUT, y1
	};
}PE_O24_SHP_OSD0_LTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CE0 RW
	UINT32 reg_win_ti_core0_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_ti_core0_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_ti_core0_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_ti_core0_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_ti_core0_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_ti_core0_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_ti_core0_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_win_ti_core0_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_win_ti_core0_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_win_ti_core0_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_win_ti_core0_yy6             :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CE4 RW
	UINT32 reg_win_ti_core0_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core0_win_w0_y0       :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CE8 RW
	UINT32 reg_win_ti_core0_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core0_win_w0_y1       :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CEC RW
	UINT32 reg_win_ti_core0_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core0_win_w1_y0       :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CF0 RW
	UINT32 reg_win_ti_core0_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core0_win_w1_y1       :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CF4 RW
	UINT32 reg_win_ti_core1_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_ti_core1_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_ti_core1_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_ti_core1_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_ti_core1_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_ti_core1_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_ti_core1_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_win_ti_core1_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_win_ti_core1_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_win_ti_core1_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_win_ti_core1_yy6             :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CF8 RW
	UINT32 reg_win_ti_core1_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core1_win_w0_y0       :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033CFC RW
	UINT32 reg_win_ti_core1_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core1_win_w0_y1       :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D00 RW
	UINT32 reg_win_ti_core1_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core1_win_w1_y0       :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D04 RW
	UINT32 reg_win_ti_core1_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_ti_core1_win_w1_y1       :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D30 RW
	UINT32 resvd0                           :16;
	UINT32 reg_ti_output_mux                :3;	//18:16	//000: normal display	001: direction map	010: g0: feature (matchness)	011: g0: gain	100: g1: gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_ti_buffer_detour_en          :1;	//19:19	//dj buffer detour enable
	UINT32 resvd1                           :3;
	UINT32 reg_ti_detour_en                 :1;	//23:23	//dejagging detour enable
	UINT32 resvd2                           :8;
	};
}PE_O24_SHP_OSD0_TI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D40 RW
	UINT32 reg_dj_edf_en                    :1;	//0:0	//edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//1:1	//H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//3:3	//edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//4:4	//0: sum of (cur - center)	1: sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//5:5	//L-type protection
	UINT32 resvd1                           :2;
	UINT32 reg_dj_count_diff_th             :5;	//12:8	//matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//18:16	//000: normal display	001: direction map	010: g0: feature (matchness)	011: g0: gain	100: g1: gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_dj_buffer_detour_en          :1;	//19:19	//dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//21:20	//center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//22:22	//neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//23:23	//dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//31:24	//line-variation threshold for edge-direction decision
	};
}PE_O24_SHP_OSD0_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D44 RW
	UINT32 reg_dj_level_th                  :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_O24_SHP_OSD0_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D48 RW
	UINT32 reg_dj_g0_cnt_min                :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_O24_SHP_OSD0_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D4C RW
	UINT32 reg_dj_g1_protect_min            :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//31:24	//edge adaptive filter multiplication value
	};
}PE_O24_SHP_OSD0_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D50 RW
	UINT32 reg_win_dj_core0_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dj_core0_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dj_core0_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_core0_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dj_core0_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dj_core0_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dj_core0_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_win_dj_core0_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_win_dj_core0_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_win_dj_core0_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_win_dj_core0_yy6             :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D54 RW
	UINT32 reg_win_dj_core0_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core0_win_w0_y0       :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D58 RW
	UINT32 reg_win_dj_core0_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core0_win_w0_y1       :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D5C RW
	UINT32 reg_win_dj_core0_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core0_win_w1_y0       :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D60 RW
	UINT32 reg_win_dj_core0_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core0_win_w1_y1       :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D64 RW
	UINT32 reg_win_dj_core1_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dj_core1_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dj_core1_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_core1_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dj_core1_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dj_core1_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dj_core1_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_win_dj_core1_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_win_dj_core1_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_win_dj_core1_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_win_dj_core1_yy6             :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D68 RW
	UINT32 reg_win_dj_core1_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core1_win_w0_y0       :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D6C RW
	UINT32 reg_win_dj_core1_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core1_win_w0_y1       :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D70 RW
	UINT32 reg_win_dj_core1_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core1_win_w1_y0       :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033D74 RW
	UINT32 reg_win_dj_core1_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_core1_win_w1_y1       :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E00 RO
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E04 RO
	UINT32 reg_mon_in_vert_cnt              :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E08 RO
	UINT32 reg_mon_out_vert_cnt             :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E0C RO
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E10 RO
	UINT32 reg_mon_shp_i_sucfail            :32;	//31:0	//Input success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E14 RO
	UINT32 reg_mon_shp_o_sucfail            :32;	//31:0	//Output success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E18 RO
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_CORE0_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E1C RO
	UINT32 reg_core0_mon_in_vert_cnt        :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_in_hori_cnt        :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE0_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E20 RO
	UINT32 reg_core0_mon_out_vert_cnt       :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_out_hori_cnt       :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE0_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E24 RO
	UINT32 reg_core0_mon_fin_out_vert_cnt   :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_fin_in_vert_cnt    :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE0_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E28 RO
	UINT32 reg_core0_mon_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE0_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E2C RO
	UINT32 reg_core0_mon_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE0_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E30 RO
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_CORE1_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E34 RO
	UINT32 reg_core1_mon_in_vert_cnt        :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_in_hori_cnt        :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE1_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E38 RO
	UINT32 reg_core1_mon_out_vert_cnt       :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_out_hori_cnt       :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE1_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E3C RO
	UINT32 reg_core1_mon_fin_out_vert_cnt   :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_fin_in_vert_cnt    :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD0_CORE1_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E40 RO
	UINT32 reg_core1_mon_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE1_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E44 RO
	UINT32 reg_core1_mon_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}PE_O24_SHP_OSD0_CORE1_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E80 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E84 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E88 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9033E8C RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD0_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034400 RW
	UINT32 resvd0                           :4;
	UINT32 reg_top_detour                   :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_bypass                   :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//8:8	//0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :11;
	UINT32 reg_osd_size_sel                 :1;	//24:24	//0: use osd top size setting 	1: use osd sharpness size setting (addr: 0x0004)
	UINT32 resvd4                           :7;
	};
}PE_O24_SHP_OSD1_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034404 RW
	UINT32 reg_top_width                    :16;	//15:0	//processing width  (default : 3840)
	UINT32 reg_top_height                   :16;	//31:16	//processing height (default : 2160)
	};
}PE_O24_SHP_OSD1_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034408 RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid (= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O24_SHP_OSD1_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903440C RW
	UINT32 reg_top_prefetch_cnt             :12;	//11:0	//Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//27:16	//Flush counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034410 RW
	UINT32 reg_top_update_ctrl              :5;	//4:0	//[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O24_SHP_OSD1_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034440 RW
	UINT32 reg_pat_en                       :1;	//0:0	//pattern enable
	UINT32 reg_pat_thickness                :2;	//2:1	//pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//15:8	//pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//23:16	//pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//31:24	//pattern pixel value (Cr)
	};
}PE_O24_SHP_OSD1_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034460 RW
	UINT32 reg_hti_enable                   :1;	//0:0	//HTI enable
	UINT32 reg_hti_debug_map_en             :1;	//1:1	//HTI debug map enable
	UINT32 reg_hti_mm_tap_size              :2;	//3:2	//HTI mm tap size
	UINT32 reg_hti_avg_tap_size             :2;	//5:4	//HTI avg tap size
	UINT32 reg_hti_ti_mode                  :1;	//6:6	//HTI ti mode
	UINT32 resvd0                           :1;
	UINT32 reg_hti_master_gain              :8;	//15:8	//HTI master gain
	UINT32 reg_hti_coring_en                :1;	//16:16	//HTI coring enable
	UINT32 resvd1                           :15;
	};
}PE_O24_SHP_OSD1_HTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034464 RW
	UINT32 reg_hti_coring_lut_y0            :8;	//7:0	//HTI coring LUT, x0
	UINT32 reg_hti_coring_lut_x0            :8;	//15:8	//HTI coring LUT, x1
	UINT32 reg_hti_coring_lut_y1            :8;	//23:16	//HTI coring LUT, y0
	UINT32 reg_hti_coring_lut_x1            :8;	//31:24	//HTI coring LUT, y1
	};
}PE_O24_SHP_OSD1_HTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034470 RW
	UINT32 reg_win_hti_win0_en              :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_hti_win1_en              :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_hti_win01_en             :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_hti_win_outside          :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_hti_win_en               :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_hti_bdr_alpha            :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_hti_bdr_wid              :2;	//14:13	//border width
	UINT32 reg_win_hti_bdr_en               :1;	//15:15	//border enable
	UINT32 reg_win_hti_cr5                  :5;	//20:16	//border color: cr5
	UINT32 reg_win_hti_cb5                  :5;	//25:21	//border color: cb5
	UINT32 reg_win_hti_yy6                  :6;	//31:26	//border color: yy6
	};
}PE_O24_SHP_OSD1_HTI_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034474 RW
	UINT32 reg_win_hti_win_w0_x0            :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_win_w0_y0            :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_HTI_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034478 RW
	UINT32 reg_win_hti_win_w0_x1            :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_win_w0_y1            :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_HTI_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903447C RW
	UINT32 reg_win_hti_win_w1_x0            :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_win_w1_y0            :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_HTI_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034480 RW
	UINT32 reg_win_hti_win_w1_x1            :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_hti_win_w1_y1            :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_HTI_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90345C0 RW
	UINT32 reg_cc_en                        :1;	//0:0	//Color contrast enable
	UINT32 resvd                            :31;
	};
}PE_O24_SHP_OSD1_CC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90345C4 RW
	UINT32 reg_cc_contrast_center           :8;	//7:0	//Color contrast luma contrast center
	UINT32 reg_cc_contrast                  :8;	//15:8	//Color contrast luma contrast
	UINT32 reg_cc_saturation                :8;	//23:16	//Color contrast chroma saturation
	UINT32 reg_cc_gain                      :8;	//31:24	//Color contrast gain
	};
}PE_O24_SHP_OSD1_CC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034600 RO
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD1_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034604 RO
	UINT32 reg_mon_in_vert_cnt              :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034608 RO
	UINT32 reg_mon_out_vert_cnt             :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903460C RO
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_O24_SHP_OSD1_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034610 RO
	UINT32 reg_mon_shp_i_sucfail            :32;	//31:0	//Input success/fail monitoring register
	};
}PE_O24_SHP_OSD1_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9034614 RO
	UINT32 reg_mon_shp_o_sucfail            :32;	//31:0	//Output success/fail monitoring register
	};
}PE_O24_SHP_OSD1_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90346F0 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90346F4 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90346F8 RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90346FC RW
	UINT32 tdata0                           :32;
	};
}PE_O24_SHP_OSD1_FSW_CTRL_03_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC860480 RW 0x0808_8000
	UINT32 reg_ord_en                       :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_ord_rand_en                  :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_blend_alpha                  :8;	//(15:8,RW,0x80) //
	UINT32 reg_round_shift                  :4;	//(19:16,RW,0x8) //
	UINT32 resvd2                           :4;
	UINT32 reg_resi_max                     :6;	//(29:24,RW,0x8) //
	UINT32 resvd3                           :2;
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860484 RW 0x0411_1133
	UINT32 reg_v_shift                      :3;	//(2:0,RW,0x3) //
	UINT32 resvd0                           :1;
	UINT32 reg_h_shift                      :3;	//(6:4,RW,0x3) //
	UINT32 resvd1                           :1;
	UINT32 reg_resi_v_over                  :6;	//(13:8,RW,0x11) //
	UINT32 resvd2                           :2;
	UINT32 reg_resi_h_over                  :6;	//(21:16,RW,0x11) //
	UINT32 resvd3                           :2;
	UINT32 reg_rand_number                  :6;	//(29:24,RW,0x4) //
	UINT32 resvd4                           :2;
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860488 RW 0x0F10_3FF2
	UINT32 reg_gyy_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86048C RW 0x0990_05F8
	UINT32 reg_gyy_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860490 RW 0x150A_E7C7
	UINT32 reg_gyy_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860494 RW 0x2B1A_0426
	UINT32 reg_bcb_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860498 RW 0x2B1A_0426
	UINT32 reg_bcb_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86049C RW 0x26D7_2F18
	UINT32 reg_bcb_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604A0 RW 0x12FD_7D1F
	UINT32 reg_rcr_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604A4 RW 0x15CB_6694
	UINT32 reg_rcr_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604A8 RW 0x1598_773A
	UINT32 reg_rcr_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604AC RW 0x103E_5A6C
	UINT32 reg_gyy_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604B0 RW 0x027B_52B8
	UINT32 reg_gyy_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604B4 RW 0x1217_8949
	UINT32 reg_gyy_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604B8 RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604BC RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604C0 RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604C4 RW 0x3371_F0CB
	UINT32 reg_rcr_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604C8 RW 0x2198_B54E
	UINT32 reg_rcr_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8604CC RW 0x0DEC_AFE2
	UINT32 reg_rcr_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL19_T;

typedef struct {
	PE_O24_SHP_OSD0_CORE_CTRL_00_T                   shp_core_ctrl_00;	//0xC9033C00
	PE_O24_SHP_OSD0_CORE_CTRL_01_T                   shp_core_ctrl_01;	//0xC9033C04
	PE_O24_SHP_OSD0_CORE0_CTRL_01_T                 shp_core0_ctrl_01;	//0xC9033C08
	PE_O24_SHP_OSD0_CORE1_CTRL_01_T                 shp_core1_ctrl_01;	//0xC9033C0C
	UINT32                                                    reserved0;	//0xC9033C10
	UINT32                                                    reserved1;	//0xC9033C14
	PE_O24_SHP_OSD0_CORE_CTRL_02_T                   shp_core_ctrl_02;	//0xC9033C18
	PE_O24_SHP_OSD0_CORE_CTRL_03_T                   shp_core_ctrl_03;	//0xC9033C1C
	PE_O24_SHP_OSD0_CORE_CTRL_04_T                   shp_core_ctrl_04;	//0xC9033C20
	UINT32                                                    reserved2;	//0xC9033C24
	UINT32                                                    reserved3;	//0xC9033C28
	UINT32                                                    reserved4;	//0xC9033C2C
	PE_O24_SHP_OSD0_SPLIT_CTRL_00_T                 shp_split_ctrl_00;	//0xC9033C30
	PE_O24_SHP_OSD0_SPLIT_CTRL_01_T                 shp_split_ctrl_01;	//0xC9033C34
	PE_O24_SHP_OSD0_SPLIT_CTRL_02_T                 shp_split_ctrl_02;	//0xC9033C38
	PE_O24_SHP_OSD0_SPLIT_CTRL_03_T                 shp_split_ctrl_03;	//0xC9033C3C
	PE_O24_SHP_OSD0_MERGE_CTRL_00_T                 shp_merge_ctrl_00;	//0xC9033C40
	PE_O24_SHP_OSD0_MERGE_CTRL_01_T                 shp_merge_ctrl_01;	//0xC9033C44
	PE_O24_SHP_OSD0_MERGE_CTRL_02_T                 shp_merge_ctrl_02;	//0xC9033C48
	PE_O24_SHP_OSD0_MERGE_CTRL_03_T                 shp_merge_ctrl_03;	//0xC9033C4C
	PE_O24_SHP_OSD0_PAT_GEN_CTRL_00_T             shp_pat_gen_ctrl_00;	//0xC9033C50
	UINT32                                                    reserved5;	//0xC9033C54
	UINT32                                                    reserved6;	//0xC9033C58
	UINT32                                                    reserved7;	//0xC9033C5C
	PE_O24_SHP_OSD0_HTI_CTRL_00_T                     shp_hti_ctrl_00;	//0xC9033C60
	PE_O24_SHP_OSD0_HTI_CTRL_01_T                     shp_hti_ctrl_01;	//0xC9033C64
	PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_00_T  shp_hti_win_core0_ctrl_00;	//0xC9033C68
	PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_01_T  shp_hti_win_core0_ctrl_01;	//0xC9033C6C
	PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_02_T  shp_hti_win_core0_ctrl_02;	//0xC9033C70
	PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_03_T  shp_hti_win_core0_ctrl_03;	//0xC9033C74
	PE_O24_SHP_OSD0_HTI_WIN_CORE0_CTRL_04_T  shp_hti_win_core0_ctrl_04;	//0xC9033C78
	PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_00_T  shp_hti_win_core1_ctrl_00;	//0xC9033C7C
	PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_01_T  shp_hti_win_core1_ctrl_01;	//0xC9033C80
	PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_02_T  shp_hti_win_core1_ctrl_02;	//0xC9033C84
	PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_03_T  shp_hti_win_core1_ctrl_03;	//0xC9033C88
	PE_O24_SHP_OSD0_HTI_WIN_CORE1_CTRL_04_T  shp_hti_win_core1_ctrl_04;	//0xC9033C8C
	UINT32                                                    reserved8;	//0xC9033C90
	UINT32                                                    reserved9;	//0xC9033C94
	UINT32                                                   reserved10;	//0xC9033C98
	UINT32                                                   reserved11;	//0xC9033C9C
	UINT32                                                   reserved12;	//0xC9033CA0
	UINT32                                                   reserved13;	//0xC9033CA4
	UINT32                                                   reserved14;	//0xC9033CA8
	UINT32                                                   reserved15;	//0xC9033CAC
	UINT32                                                   reserved16;	//0xC9033CB0
	UINT32                                                   reserved17;	//0xC9033CB4
	UINT32                                                   reserved18;	//0xC9033CB8
	UINT32                                                   reserved19;	//0xC9033CBC
	PE_O24_SHP_OSD0_VTI_CTRL_00_T                     shp_vti_ctrl_00;	//0xC9033CC0
	UINT32                                                   reserved20;	//0xC9033CC4
	UINT32                                                   reserved21;	//0xC9033CC8
	UINT32                                                   reserved22;	//0xC9033CCC
	PE_O24_SHP_OSD0_LTI_CTRL_00_T                     shp_lti_ctrl_00;	//0xC9033CD0
	PE_O24_SHP_OSD0_LTI_CTRL_01_T                     shp_lti_ctrl_01;	//0xC9033CD4
	UINT32                                                   reserved23;	//0xC9033CD8
	UINT32                                                   reserved24;	//0xC9033CDC
	PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_00_T   shp_ti_win_core0_ctrl_00;	//0xC9033CE0
	PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_01_T   shp_ti_win_core0_ctrl_01;	//0xC9033CE4
	PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_02_T   shp_ti_win_core0_ctrl_02;	//0xC9033CE8
	PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_03_T   shp_ti_win_core0_ctrl_03;	//0xC9033CEC
	PE_O24_SHP_OSD0_TI_WIN_CORE0_CTRL_04_T   shp_ti_win_core0_ctrl_04;	//0xC9033CF0
	PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_00_T   shp_ti_win_core1_ctrl_00;	//0xC9033CF4
	PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_01_T   shp_ti_win_core1_ctrl_01;	//0xC9033CF8
	PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_02_T   shp_ti_win_core1_ctrl_02;	//0xC9033CFC
	PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_03_T   shp_ti_win_core1_ctrl_03;	//0xC9033D00
	PE_O24_SHP_OSD0_TI_WIN_CORE1_CTRL_04_T   shp_ti_win_core1_ctrl_04;	//0xC9033D04
	UINT32                                                   reserved25;	//0xC9033D08
	UINT32                                                   reserved26;	//0xC9033D0C
	UINT32                                                   reserved27;	//0xC9033D10
	UINT32                                                   reserved28;	//0xC9033D14
	UINT32                                                   reserved29;	//0xC9033D18
	UINT32                                                   reserved30;	//0xC9033D1C
	UINT32                                                   reserved31;	//0xC9033D20
	UINT32                                                   reserved32;	//0xC9033D24
	UINT32                                                   reserved33;	//0xC9033D28
	UINT32                                                   reserved34;	//0xC9033D2C
	PE_O24_SHP_OSD0_TI_CTRL_00_T                       shp_ti_ctrl_00;	//0xC9033D30
	UINT32                                                   reserved35;	//0xC9033D34
	UINT32                                                   reserved36;	//0xC9033D38
	UINT32                                                   reserved37;	//0xC9033D3C
	PE_O24_SHP_OSD0_DJ_CTRL_00_T                       shp_dj_ctrl_00;	//0xC9033D40
	PE_O24_SHP_OSD0_DJ_CTRL_01_T                       shp_dj_ctrl_01;	//0xC9033D44
	PE_O24_SHP_OSD0_DJ_CTRL_02_T                       shp_dj_ctrl_02;	//0xC9033D48
	PE_O24_SHP_OSD0_DJ_CTRL_03_T                       shp_dj_ctrl_03;	//0xC9033D4C
	PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_00_T   shp_dj_win_core0_ctrl_00;	//0xC9033D50
	PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_01_T   shp_dj_win_core0_ctrl_01;	//0xC9033D54
	PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_02_T   shp_dj_win_core0_ctrl_02;	//0xC9033D58
	PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_03_T   shp_dj_win_core0_ctrl_03;	//0xC9033D5C
	PE_O24_SHP_OSD0_DJ_WIN_CORE0_CTRL_04_T   shp_dj_win_core0_ctrl_04;	//0xC9033D60
	PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_00_T   shp_dj_win_core1_ctrl_00;	//0xC9033D64
	PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_01_T   shp_dj_win_core1_ctrl_01;	//0xC9033D68
	PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_02_T   shp_dj_win_core1_ctrl_02;	//0xC9033D6C
	PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_03_T   shp_dj_win_core1_ctrl_03;	//0xC9033D70
	PE_O24_SHP_OSD0_DJ_WIN_CORE1_CTRL_04_T   shp_dj_win_core1_ctrl_04;	//0xC9033D74
	UINT32                                                   reserved38;	//0xC9033D78
	UINT32                                                   reserved39;	//0xC9033D7C
	UINT32                                                   reserved40;	//0xC9033D80
	UINT32                                                   reserved41;	//0xC9033D84
	UINT32                                                   reserved42;	//0xC9033D88
	UINT32                                                   reserved43;	//0xC9033D8C
	UINT32                                                   reserved44;	//0xC9033D90
	UINT32                                                   reserved45;	//0xC9033D94
	UINT32                                                   reserved46;	//0xC9033D98
	UINT32                                                   reserved47;	//0xC9033D9C
	UINT32                                                   reserved48;	//0xC9033DA0
	UINT32                                                   reserved49;	//0xC9033DA4
	UINT32                                                   reserved50;	//0xC9033DA8
	UINT32                                                   reserved51;	//0xC9033DAC
	UINT32                                                   reserved52;	//0xC9033DB0
	UINT32                                                   reserved53;	//0xC9033DB4
	UINT32                                                   reserved54;	//0xC9033DB8
	UINT32                                                   reserved55;	//0xC9033DBC
	UINT32                                                   reserved56;	//0xC9033DC0
	UINT32                                                   reserved57;	//0xC9033DC4
	UINT32                                                   reserved58;	//0xC9033DC8
	UINT32                                                   reserved59;	//0xC9033DCC
	UINT32                                                   reserved60;	//0xC9033DD0
	UINT32                                                   reserved61;	//0xC9033DD4
	UINT32                                                   reserved62;	//0xC9033DD8
	UINT32                                                   reserved63;	//0xC9033DDC
	UINT32                                                   reserved64;	//0xC9033DE0
	UINT32                                                   reserved65;	//0xC9033DE4
	UINT32                                                   reserved66;	//0xC9033DE8
	UINT32                                                   reserved67;	//0xC9033DEC
	UINT32                                                   reserved68;	//0xC9033DF0
	UINT32                                                   reserved69;	//0xC9033DF4
	UINT32                                                   reserved70;	//0xC9033DF8
	UINT32                                                   reserved71;	//0xC9033DFC
	PE_O24_SHP_OSD0_CORE_STAT_00_T                   shp_core_stat_00;	//0xC9033E00
	PE_O24_SHP_OSD0_CORE_STAT_01_T                   shp_core_stat_01;	//0xC9033E04
	PE_O24_SHP_OSD0_CORE_STAT_02_T                   shp_core_stat_02;	//0xC9033E08
	PE_O24_SHP_OSD0_CORE_STAT_03_T                   shp_core_stat_03;	//0xC9033E0C
	PE_O24_SHP_OSD0_CORE_STAT_04_T                   shp_core_stat_04;	//0xC9033E10
	PE_O24_SHP_OSD0_CORE_STAT_05_T                   shp_core_stat_05;	//0xC9033E14
	PE_O24_SHP_OSD0_CORE0_STAT_00_T                 shp_core0_stat_00;	//0xC9033E18
	PE_O24_SHP_OSD0_CORE0_STAT_01_T                 shp_core0_stat_01;	//0xC9033E1C
	PE_O24_SHP_OSD0_CORE0_STAT_02_T                 shp_core0_stat_02;	//0xC9033E20
	PE_O24_SHP_OSD0_CORE0_STAT_03_T                 shp_core0_stat_03;	//0xC9033E24
	PE_O24_SHP_OSD0_CORE0_STAT_04_T                 shp_core0_stat_04;	//0xC9033E28
	PE_O24_SHP_OSD0_CORE0_STAT_05_T                 shp_core0_stat_05;	//0xC9033E2C
	PE_O24_SHP_OSD0_CORE1_STAT_00_T                 shp_core1_stat_00;	//0xC9033E30
	PE_O24_SHP_OSD0_CORE1_STAT_01_T                 shp_core1_stat_01;	//0xC9033E34
	PE_O24_SHP_OSD0_CORE1_STAT_02_T                 shp_core1_stat_02;	//0xC9033E38
	PE_O24_SHP_OSD0_CORE1_STAT_03_T                 shp_core1_stat_03;	//0xC9033E3C
	PE_O24_SHP_OSD0_CORE1_STAT_04_T                 shp_core1_stat_04;	//0xC9033E40
	PE_O24_SHP_OSD0_CORE1_STAT_05_T                 shp_core1_stat_05;	//0xC9033E44
	UINT32                                                   reserved72;	//0xC9033E48
	UINT32                                                   reserved73;	//0xC9033E4C
	UINT32                                                   reserved74;	//0xC9033E50
	UINT32                                                   reserved75;	//0xC9033E54
	UINT32                                                   reserved76;	//0xC9033E58
	UINT32                                                   reserved77;	//0xC9033E5C
	UINT32                                                   reserved78;	//0xC9033O24
	UINT32                                                   reserved79;	//0xC9033E64
	UINT32                                                   reserved80;	//0xC9033E68
	UINT32                                                   reserved81;	//0xC9033E6C
	UINT32                                                   reserved82;	//0xC9033E70
	UINT32                                                   reserved83;	//0xC9033E74
	UINT32                                                   reserved84;	//0xC9033E78
	UINT32                                                   reserved85;	//0xC9033E7C
	PE_O24_SHP_OSD0_FSW_CTRL_00_T                     shp_fsw_ctrl_00;	//0xC9033E80
	PE_O24_SHP_OSD0_FSW_CTRL_01_T                     shp_fsw_ctrl_01;	//0xC9033E84
	PE_O24_SHP_OSD0_FSW_CTRL_02_T                     shp_fsw_ctrl_02;	//0xC9033E88
	PE_O24_SHP_OSD0_FSW_CTRL_03_T                     shp_fsw_ctrl_03;	//0xC9033E8C
}PE_SHP_OSD0_REG_O24_T;
typedef struct {
	PE_O24_SHP_OSD1_CORE_CTRL_00_T                  shp_core_ctrl_00;	//0xC9034400
	PE_O24_SHP_OSD1_CORE_CTRL_01_T                  shp_core_ctrl_01;	//0xC9034404
	PE_O24_SHP_OSD1_CORE_CTRL_02_T                  shp_core_ctrl_02;	//0xC9034408
	PE_O24_SHP_OSD1_CORE_CTRL_03_T                  shp_core_ctrl_03;	//0xC903440C
	PE_O24_SHP_OSD1_CORE_CTRL_04_T                  shp_core_ctrl_04;	//0xC9034410
	UINT32                                                    reserved0;	//0xC9034414
	UINT32                                                    reserved1;	//0xC9034418
	UINT32                                                    reserved2;	//0xC903441C
	UINT32                                                    reserved3;	//0xC9034420
	UINT32                                                    reserved4;	//0xC9034424
	UINT32                                                    reserved5;	//0xC9034428
	UINT32                                                    reserved6;	//0xC903442C
	UINT32                                                    reserved7;	//0xC9034430
	UINT32                                                    reserved8;	//0xC9034434
	UINT32                                                    reserved9;	//0xC9034438
	UINT32                                                   reserved10;	//0xC903443C
	PE_O24_SHP_OSD1_PAT_GEN_CTRL_00_T            shp_pat_gen_ctrl_00;	//0xC9034440
	UINT32                                                   reserved11;	//0xC9034444
	UINT32                                                   reserved12;	//0xC9034448
	UINT32                                                   reserved13;	//0xC903444C
	UINT32                                                   reserved14;	//0xC9034450
	UINT32                                                   reserved15;	//0xC9034454
	UINT32                                                   reserved16;	//0xC9034458
	UINT32                                                   reserved17;	//0xC903445C
	PE_O24_SHP_OSD1_HTI_CTRL_00_T                    shp_hti_ctrl_00;	//0xC9034460
	PE_O24_SHP_OSD1_HTI_CTRL_01_T                    shp_hti_ctrl_01;	//0xC9034464
	UINT32                                                   reserved18;	//0xC9034468
	UINT32                                                   reserved19;	//0xC903446C
	PE_O24_SHP_OSD1_HTI_WIN_CTRL_00_T            shp_hti_win_ctrl_00;	//0xC9034470
	PE_O24_SHP_OSD1_HTI_WIN_CTRL_01_T            shp_hti_win_ctrl_01;	//0xC9034474
	PE_O24_SHP_OSD1_HTI_WIN_CTRL_02_T            shp_hti_win_ctrl_02;	//0xC9034478
	PE_O24_SHP_OSD1_HTI_WIN_CTRL_03_T            shp_hti_win_ctrl_03;	//0xC903447C
	PE_O24_SHP_OSD1_HTI_WIN_CTRL_04_T            shp_hti_win_ctrl_04;	//0xC9034480
	UINT32                                                   reserved20;	//0xC9034484
	UINT32                                                   reserved21;	//0xC9034488
	UINT32                                                   reserved22;	//0xC903448C
	UINT32                                                   reserved23;	//0xC9034490
	UINT32                                                   reserved24;	//0xC9034494
	UINT32                                                   reserved25;	//0xC9034498
	UINT32                                                   reserved26;	//0xC903449C
	UINT32                                                   reserved27;	//0xC90344A0
	UINT32                                                   reserved28;	//0xC90344A4
	UINT32                                                   reserved29;	//0xC90344A8
	UINT32                                                   reserved30;	//0xC90344AC
	UINT32                                                   reserved31;	//0xC90344B0
	UINT32                                                   reserved32;	//0xC90344B4
	UINT32                                                   reserved33;	//0xC90344B8
	UINT32                                                   reserved34;	//0xC90344BC
	UINT32                                                   reserved35;	//0xC90344C0
	UINT32                                                   reserved36;	//0xC90344C4
	UINT32                                                   reserved37;	//0xC90344C8
	UINT32                                                   reserved38;	//0xC90344CC
	UINT32                                                   reserved39;	//0xC90344D0
	UINT32                                                   reserved40;	//0xC90344D4
	UINT32                                                   reserved41;	//0xC90344D8
	UINT32                                                   reserved42;	//0xC90344DC
	UINT32                                                   reserved43;	//0xC90344E0
	UINT32                                                   reserved44;	//0xC90344E4
	UINT32                                                   reserved45;	//0xC90344E8
	UINT32                                                   reserved46;	//0xC90344EC
	UINT32                                                   reserved47;	//0xC90344F0
	UINT32                                                   reserved48;	//0xC90344F4
	UINT32                                                   reserved49;	//0xC90344F8
	UINT32                                                   reserved50;	//0xC90344FC
	UINT32                                                   reserved51;	//0xC9034500
	UINT32                                                   reserved52;	//0xC9034504
	UINT32                                                   reserved53;	//0xC9034508
	UINT32                                                   reserved54;	//0xC903450C
	UINT32                                                   reserved55;	//0xC9034510
	UINT32                                                   reserved56;	//0xC9034514
	UINT32                                                   reserved57;	//0xC9034518
	UINT32                                                   reserved58;	//0xC903451C
	UINT32                                                   reserved59;	//0xC9034520
	UINT32                                                   reserved60;	//0xC9034524
	UINT32                                                   reserved61;	//0xC9034528
	UINT32                                                   reserved62;	//0xC903452C
	UINT32                                                   reserved63;	//0xC9034530
	UINT32                                                   reserved64;	//0xC9034534
	UINT32                                                   reserved65;	//0xC9034538
	UINT32                                                   reserved66;	//0xC903453C
	UINT32                                                   reserved67;	//0xC9034540
	UINT32                                                   reserved68;	//0xC9034544
	UINT32                                                   reserved69;	//0xC9034548
	UINT32                                                   reserved70;	//0xC903454C
	UINT32                                                   reserved71;	//0xC9034550
	UINT32                                                   reserved72;	//0xC9034554
	UINT32                                                   reserved73;	//0xC9034558
	UINT32                                                   reserved74;	//0xC903455C
	UINT32                                                   reserved75;	//0xC9034560
	UINT32                                                   reserved76;	//0xC9034564
	UINT32                                                   reserved77;	//0xC9034568
	UINT32                                                   reserved78;	//0xC903456C
	UINT32                                                   reserved79;	//0xC9034570
	UINT32                                                   reserved80;	//0xC9034574
	UINT32                                                   reserved81;	//0xC9034578
	UINT32                                                   reserved82;	//0xC903457C
	UINT32                                                   reserved83;	//0xC9034580
	UINT32                                                   reserved84;	//0xC9034584
	UINT32                                                   reserved85;	//0xC9034588
	UINT32                                                   reserved86;	//0xC903458C
	UINT32                                                   reserved87;	//0xC9034590
	UINT32                                                   reserved88;	//0xC9034594
	UINT32                                                   reserved89;	//0xC9034598
	UINT32                                                   reserved90;	//0xC903459C
	UINT32                                                   reserved91;	//0xC90345A0
	UINT32                                                   reserved92;	//0xC90345A4
	UINT32                                                   reserved93;	//0xC90345A8
	UINT32                                                   reserved94;	//0xC90345AC
	UINT32                                                   reserved95;	//0xC90345B0
	UINT32                                                   reserved96;	//0xC90345B4
	UINT32                                                   reserved97;	//0xC90345B8
	UINT32                                                   reserved98;	//0xC90345BC
	PE_O24_SHP_OSD1_CC_CTRL_00_T                      shp_cc_ctrl_00;	//0xC90345C0
	PE_O24_SHP_OSD1_CC_CTRL_01_T                      shp_cc_ctrl_01;	//0xC90345C4
	UINT32                                                   reserved99;	//0xC90345C8
	UINT32                                                  reserved100;	//0xC90345CC
	UINT32                                                  reserved101;	//0xC90345D0
	UINT32                                                  reserved102;	//0xC90345D4
	UINT32                                                  reserved103;	//0xC90345D8
	UINT32                                                  reserved104;	//0xC90345DC
	UINT32                                                  reserved105;	//0xC90345E0
	UINT32                                                  reserved106;	//0xC90345E4
	UINT32                                                  reserved107;	//0xC90345E8
	UINT32                                                  reserved108;	//0xC90345EC
	UINT32                                                  reserved109;	//0xC90345F0
	UINT32                                                  reserved110;	//0xC90345F4
	UINT32                                                  reserved111;	//0xC90345F8
	UINT32                                                  reserved112;	//0xC90345FC
	PE_O24_SHP_OSD1_CORE_STAT_00_T                  shp_core_stat_00;	//0xC9034600
	PE_O24_SHP_OSD1_CORE_STAT_01_T                  shp_core_stat_01;	//0xC9034604
	PE_O24_SHP_OSD1_CORE_STAT_02_T                  shp_core_stat_02;	//0xC9034608
	PE_O24_SHP_OSD1_CORE_STAT_03_T                  shp_core_stat_03;	//0xC903460C
	PE_O24_SHP_OSD1_CORE_STAT_04_T                  shp_core_stat_04;	//0xC9034610
	PE_O24_SHP_OSD1_CORE_STAT_05_T                  shp_core_stat_05;	//0xC9034614
	UINT32                                                  reserved113;	//0xC9034618
	UINT32                                                  reserved114;	//0xC903461C
	UINT32                                                  reserved115;	//0xC9034620
	UINT32                                                  reserved116;	//0xC9034624
	UINT32                                                  reserved117;	//0xC9034628
	UINT32                                                  reserved118;	//0xC903462C
	UINT32                                                  reserved119;	//0xC9034630
	UINT32                                                  reserved120;	//0xC9034634
	UINT32                                                  reserved121;	//0xC9034638
	UINT32                                                  reserved122;	//0xC903463C
	UINT32                                                  reserved123;	//0xC9034640
	UINT32                                                  reserved124;	//0xC9034644
	UINT32                                                  reserved125;	//0xC9034648
	UINT32                                                  reserved126;	//0xC903464C
	UINT32                                                  reserved127;	//0xC9034650
	UINT32                                                  reserved128;	//0xC9034654
	UINT32                                                  reserved129;	//0xC9034658
	UINT32                                                  reserved130;	//0xC903465C
	UINT32                                                  reserved131;	//0xC9034660
	UINT32                                                  reserved132;	//0xC9034664
	UINT32                                                  reserved133;	//0xC9034668
	UINT32                                                  reserved134;	//0xC903466C
	UINT32                                                  reserved135;	//0xC9034670
	UINT32                                                  reserved136;	//0xC9034674
	UINT32                                                  reserved137;	//0xC9034678
	UINT32                                                  reserved138;	//0xC903467C
	UINT32                                                  reserved139;	//0xC9034680
	UINT32                                                  reserved140;	//0xC9034684
	UINT32                                                  reserved141;	//0xC9034688
	UINT32                                                  reserved142;	//0xC903468C
	UINT32                                                  reserved143;	//0xC9034690
	UINT32                                                  reserved144;	//0xC9034694
	UINT32                                                  reserved145;	//0xC9034698
	UINT32                                                  reserved146;	//0xC903469C
	UINT32                                                  reserved147;	//0xC90346A0
	UINT32                                                  reserved148;	//0xC90346A4
	UINT32                                                  reserved149;	//0xC90346A8
	UINT32                                                  reserved150;	//0xC90346AC
	UINT32                                                  reserved151;	//0xC90346B0
	UINT32                                                  reserved152;	//0xC90346B4
	UINT32                                                  reserved153;	//0xC90346B8
	UINT32                                                  reserved154;	//0xC90346BC
	UINT32                                                  reserved155;	//0xC90346C0
	UINT32                                                  reserved156;	//0xC90346C4
	UINT32                                                  reserved157;	//0xC90346C8
	UINT32                                                  reserved158;	//0xC90346CC
	UINT32                                                  reserved159;	//0xC90346D0
	UINT32                                                  reserved160;	//0xC90346D4
	UINT32                                                  reserved161;	//0xC90346D8
	UINT32                                                  reserved162;	//0xC90346DC
	UINT32                                                  reserved163;	//0xC90346E0
	UINT32                                                  reserved164;	//0xC90346E4
	UINT32                                                  reserved165;	//0xC90346E8
	UINT32                                                  reserved166;	//0xC90346EC
	PE_O24_SHP_OSD1_FSW_CTRL_00_T                    shp_fsw_ctrl_00;	//0xC90346F0
	PE_O24_SHP_OSD1_FSW_CTRL_01_T                    shp_fsw_ctrl_01;	//0xC90346F4
	PE_O24_SHP_OSD1_FSW_CTRL_02_T                    shp_fsw_ctrl_02;	//0xC90346F8
	PE_O24_SHP_OSD1_FSW_CTRL_03_T                    shp_fsw_ctrl_03;	//0xC90346FC
}PE_SHP_OSD1_REG_O24_T;


typedef struct {
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL00_T          reg_osd0_ord_ctrl00;	//0xCC860480
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL01_T          reg_osd0_ord_ctrl01;	//0xCC860484
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL02_T          reg_osd0_ord_ctrl02;	//0xCC860488
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL03_T          reg_osd0_ord_ctrl03;	//0xCC86048C
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL04_T          reg_osd0_ord_ctrl04;	//0xCC860490
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL05_T          reg_osd0_ord_ctrl05;	//0xCC860494
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL06_T          reg_osd0_ord_ctrl06;	//0xCC860498
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL07_T          reg_osd0_ord_ctrl07;	//0xCC86049C
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL08_T          reg_osd0_ord_ctrl08;	//0xCC8604A0
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL09_T          reg_osd0_ord_ctrl09;	//0xCC8604A4
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL10_T          reg_osd0_ord_ctrl10;	//0xCC8604A8
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL11_T          reg_osd0_ord_ctrl11;	//0xCC8604AC
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL12_T          reg_osd0_ord_ctrl12;	//0xCC8604B0
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL13_T          reg_osd0_ord_ctrl13;	//0xCC8604B4
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL14_T          reg_osd0_ord_ctrl14;	//0xCC8604B8
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL15_T          reg_osd0_ord_ctrl15;	//0xCC8604BC
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL16_T          reg_osd0_ord_ctrl16;	//0xCC8604C0
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL17_T          reg_osd0_ord_ctrl17;	//0xCC8604C4
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL18_T          reg_osd0_ord_ctrl18;	//0xCC8604C8
	PE_O24_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL19_T          reg_osd0_ord_ctrl19;	//0xCC8604CC
}PE_OSD_ORD_REG_O24_T;

#endif
