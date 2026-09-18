/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 

#ifndef _IDS_TOPCTRL_CVI_H_
#define _IDS_TOPCTRL_CVI_H_

/*-----------------------------------------------------------------------------
                             0xc9000000L PIC_INIT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 g0_pic_init                        :1 ;	//0 
	UINT32 g1_pic_init                        :1 ;	//1 
	UINT32 g2_pic_init                        :1 ;	//2 
	UINT32 g3_pic_init                        :1 ;	//3 
	UINT32 g4_pic_init                        :1 ;	//4 
	UINT32 g5_pic_init                        :1 ;	//5 
	UINT32 g6_pic_init                        :1 ;	//6 
	UINT32 g7_pic_init                        :1 ;	//7 
	UINT32 g0_auto_init                       :1 ;	//16
	UINT32 g1_auto_init                       :1 ;	//17
	UINT32 g2_auto_init                       :1 ;	//18
	UINT32 g3_auto_init                       :1 ;	//19
	UINT32 g4_auto_init                       :1 ;	//20
	UINT32 g5_auto_init                       :1 ;	//21
	UINT32 g6_auto_init                       :1 ;	//22
	UINT32 g7_auto_init                       :1 ;	//23
}O18A0_CVC_PIC_INIT_T;
/*-----------------------------------------------------------------------------
                             0xc9000004L PIC_START                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 g0_pic_start                       :1 ;	//0 
	UINT32 g1_pic_start                       :1 ;	//1 
	UINT32 g2_pic_start                       :1 ;	//2 
	UINT32 g3_pic_start                       :1 ;	//3 
	UINT32 g4_pic_start                       :1 ;	//4 
	UINT32 g5_pic_start                       :1 ;	//5 
	UINT32 g6_pic_start                       :1 ;	//6 
	UINT32 g7_pic_start                       :1 ;	//7 
}O18A0_CVC_PIC_START_T;
/*-----------------------------------------------------------------------------
                             0xc9000008L CTRL_AUTO_INIT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 idx_src_g0_auto_init               :3 ;	//2:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 idx_src_g1_auto_init               :3 ;	//6:4
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 idx_src_g2_auto_init               :3 ;	//10:8
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 idx_src_g3_auto_init               :3 ;	//14:12
	UINT32 reserved04                         :1 ;	//reserved
	UINT32 idx_src_g4_auto_init               :3 ;	//18:16
	UINT32 reserved05                         :1 ;	//reserved
	UINT32 idx_src_g5_auto_init               :3 ;	//22:20
	UINT32 reserved06                         :1 ;	//reserved
	UINT32 idx_src_g6_auto_init               :3 ;	//26:24
	UINT32 reserved07                         :1 ;	//reserved
	UINT32 idx_src_g7_auto_init               :3 ;	//30:28
}O18A0_CVC_CTRL_AUTO_INIT_T;
/*-----------------------------------------------------------------------------
                             0xc900000cL CTRL_INTR_PULSE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 idx_src_i0_intr_pulse              :3 ;	//2:0
	UINT32 sel_src_i0_intr_pulse              :1 ;	//3 
	UINT32 idx_src_i1_intr_pulse              :3 ;	//6:4
	UINT32 sel_src_i1_intr_pulse              :1 ;	//7 
	UINT32 idx_src_i2_intr_pulse              :3 ;	//10:8
	UINT32 sel_src_i2_intr_pulse              :1 ;	//11
	UINT32 idx_src_i3_intr_pulse              :3 ;	//14:12
	UINT32 sel_src_i3_intr_pulse              :1 ;	//15
	UINT32 idx_src_i4_intr_pulse              :3 ;	//18:16
	UINT32 sel_src_i4_intr_pulse              :1 ;	//19
	UINT32 idx_src_i5_intr_pulse              :3 ;	//22:20
	UINT32 sel_src_i5_intr_pulse              :1 ;	//23
	UINT32 idx_src_i6_intr_pulse              :3 ;	//26:24
	UINT32 sel_src_i6_intr_pulse              :1 ;	//27
	UINT32 idx_src_i7_intr_pulse              :3 ;	//30:28
	UINT32 sel_src_i7_intr_pulse              :1 ;	//31
}O18A0_CVC_CTRL_INTR_PULSE_T;
/*-----------------------------------------------------------------------------
                             0xc9000010L INTR_REG                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 intr_i0_intr_pulse                 :1 ;	//0 
	UINT32 intr_i1_intr_pulse                 :1 ;	//1 
	UINT32 intr_i2_intr_pulse                 :1 ;	//2 
	UINT32 intr_i3_intr_pulse                 :1 ;	//3 
	UINT32 intr_i4_intr_pulse                 :1 ;	//4 
	UINT32 intr_i5_intr_pulse                 :1 ;	//5 
	UINT32 intr_i6_intr_pulse                 :1 ;	//6 
	UINT32 intr_i7_intr_pulse                 :1 ;	//7 
	UINT32 intr_g0_pic_end                    :1 ;	//8 
	UINT32 intr_g1_pic_end                    :1 ;	//9 
	UINT32 intr_g2_pic_end                    :1 ;	//10
	UINT32 intr_g3_pic_end                    :1 ;	//11
	UINT32 intr_g4_pic_end                    :1 ;	//12
//	UINT32 reserved00                         :11;	//reserved
	UINT32 intr_g5_pic_end                    :1 ;	//13
	UINT32 intr_g6_pic_end                    :1 ;	//14
	UINT32 intr_g7_pic_end                    :1 ;	//15
	UINT32 intr_cvi0_field                    :1 ;	//16
	UINT32 intr_cvi0_frame_lr                 :1 ;	//17
	UINT32 intr_cvi1_field                    :1 ;	//18
	UINT32 intr_cvi1_frame_lr                 :1 ;	//19
	UINT32 intr_cvi2_field                    :1 ;	//20
	UINT32 intr_cvi2_frame_lr                 :1 ;	//21
	UINT32 intr_cvi3_field                    :1 ;	//22
	UINT32 intr_cvi3_frame_lr                 :1 ;	//23
	UINT32 intr_cvi0                          :1 ;	//24
	UINT32 intr_cvi1                          :1 ;	//25
	UINT32 intr_cvi2                          :1 ;	//26
	UINT32 intr_cvi3                          :1 ;	//27
	UINT32 intr_cvd                           :1 ;	//28
	UINT32 intr_wss                           :1 ;	//29
	UINT32 intr_cgms                          :1 ;	//30
	UINT32 intr_hdmi_cvi                      :1 ;	//31
}O18A0_CVC_INTR_REG_T;
/*-----------------------------------------------------------------------------
                             0xc9000014L INTR_MASK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mask_i0_src_pulse                  :1 ;	//0 
	UINT32 mask_i1_src_pulse                  :1 ;	//1 
	UINT32 mask_i2_src_pulse                  :1 ;	//2 
	UINT32 mask_i3_src_pulse                  :1 ;	//3 
	UINT32 mask_i4_src_pulse                  :1 ;	//4 
	UINT32 mask_i5_src_pulse                  :1 ;	//5 
	UINT32 mask_i6_src_pulse                  :1 ;	//6 
	UINT32 mask_i7_src_pulse                  :1 ;	//7 
	UINT32 mask_g0_pic_end                    :1 ;	//8 
	UINT32 mask_g1_pic_end                    :1 ;	//9 
	UINT32 mask_g2_pic_end                    :1 ;	//10
	UINT32 mask_g3_pic_end                    :1 ;	//11
	UINT32 mask_g4_pic_end                    :1 ;	//12
//	UINT32 reserved00                         :11;	//reserved
	UINT32 mask_g5_pic_end                    :1 ;	//13
	UINT32 mask_g6_pic_end                    :1 ;	//14
	UINT32 mask_g7_pic_end                    :1 ;	//15
	UINT32 mask_cvi0_field                    :1 ;	//16
	UINT32 mask_cvi0_frame_lr                 :1 ;	//17
	UINT32 mask_cvi1_field                    :1 ;	//18
	UINT32 mask_cvi1_frame_lr                 :1 ;	//19
	UINT32 mask_cvi2_field                    :1 ;	//20
	UINT32 mask_cvi2_frame_lr                 :1 ;	//21
	UINT32 mask_cvi3_field                    :1 ;	//22
	UINT32 mask_cvi3_frame_lr                 :1 ;	//23
	UINT32 mask_cvi0                          :1 ;	//24
	UINT32 mask_cvi1                          :1 ;	//25
	UINT32 mask_cvi2                          :1 ;	//26
	UINT32 mask_cvi3                          :1 ;	//27
	UINT32 mask_cvd                           :1 ;	//28
	UINT32 mask_wss                           :1 ;	//29
	UINT32 mask_cgms                          :1 ;	//30
	UINT32 mask_hdmi_cvi                      :1 ;	//31
}O18A0_CVC_INTR_MASK_T;
/*-----------------------------------------------------------------------------
                             0xc9000018L INTR_MUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mux_i0_src_pulse                   :1 ;	//0 
	UINT32 mux_i1_src_pulse                   :1 ;	//1 
	UINT32 mux_i2_src_pulse                   :1 ;	//2 
	UINT32 mux_i3_src_pulse                   :1 ;	//3 
	UINT32 mux_i4_src_pulse                   :1 ;	//4 
	UINT32 mux_i5_src_pulse                   :1 ;	//5 
	UINT32 mux_i6_src_pulse                   :1 ;	//6 
	UINT32 mux_i7_src_pulse                   :1 ;	//7 
	UINT32 mux_g0_pic_end                     :1 ;	//8 
	UINT32 mux_g1_pic_end                     :1 ;	//9 
	UINT32 mux_g2_pic_end                     :1 ;	//10
	UINT32 mux_g3_pic_end                     :1 ;	//11
	UINT32 mux_g4_pic_end                     :1 ;	//12
//	UINT32 reserved00                         :11;	//reserved
	UINT32 mux_g5_pic_end                     :1 ;	//13
	UINT32 mux_g6_pic_end                     :1 ;	//14
	UINT32 mux_g7_pic_end                     :1 ;	//15
	UINT32 mux_cvi0_field                     :1 ;	//16
	UINT32 mux_cvi0_frame_lr                  :1 ;	//17
	UINT32 mux_cvi1_field                     :1 ;	//18
	UINT32 mux_cvi1_frame_lr                  :1 ;	//19
	UINT32 mux_cvi2_field                     :1 ;	//20
	UINT32 mux_cvi2_frame_lr                  :1 ;	//21
	UINT32 mux_cvi3_field                     :1 ;	//22
	UINT32 mux_cvi3_frame_lr                  :1 ;	//23
	UINT32 mux_cvi0                           :1 ;	//24
	UINT32 mux_cvi1                           :1 ;	//25
	UINT32 mux_cvi2                           :1 ;	//26
	UINT32 mux_cvi3                           :1 ;	//27
	UINT32 mux_cvd                            :1 ;	//28
	UINT32 mux_wss                            :1 ;	//29
	UINT32 mux_cgms                           :1 ;	//30
	UINT32 mux_hdmi_cvi                       :1 ;	//31
}O18A0_CVC_INTR_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc900001cL INTR_EN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 en_i0_src_pulse                    :1 ;	//0 
	UINT32 en_i1_src_pulse                    :1 ;	//1 
	UINT32 en_i2_src_pulse                    :1 ;	//2 
	UINT32 en_i3_src_pulse                    :1 ;	//3 
	UINT32 en_i4_src_pulse                    :1 ;	//4 
	UINT32 en_i5_src_pulse                    :1 ;	//5 
	UINT32 en_i6_src_pulse                    :1 ;	//6 
	UINT32 en_i7_src_pulse                    :1 ;	//7 
	UINT32 en_g0_pic_end                      :1 ;	//8 
	UINT32 en_g1_pic_end                      :1 ;	//9 
	UINT32 en_g2_pic_end                      :1 ;	//10
	UINT32 en_g3_pic_end                      :1 ;	//11
	UINT32 en_g4_pic_end                      :1 ;	//12
//	UINT32 reserved00                         :11;	//reserved
	UINT32 en_g5_pic_end                      :1 ;	//13
	UINT32 en_g6_pic_end                      :1 ;	//14
	UINT32 en_g7_pic_end                      :1 ;	//15
	UINT32 en_cvi0_field                      :1 ;	//16
	UINT32 en_cvi0_frame_lr                   :1 ;	//17
	UINT32 en_cvi1_field                      :1 ;	//18
	UINT32 en_cvi1_frame_lr                   :1 ;	//19
	UINT32 en_cvi2_field                      :1 ;	//20
	UINT32 en_cvi2_frame_lr                   :1 ;	//21
	UINT32 en_cvi3_field                      :1 ;	//22
	UINT32 en_cvi3_frame_lr                   :1 ;	//23
	UINT32 en_cvi0                            :1 ;	//24
	UINT32 en_cvi1                            :1 ;	//25
	UINT32 en_cvi2                            :1 ;	//26
	UINT32 en_hdmi_cvi_meta                   :1 ;	//27
	UINT32 en_cvd                             :1 ;	//28
	UINT32 en_wss                             :1 ;	//29
	UINT32 en_cgms                            :1 ;	//30
	UINT32 en_hdmi_cvi                        :1 ;	//31
}O18A0_CVC_INTR_EN_T;
/*-----------------------------------------------------------------------------
                             0xc9000050L INFO_HDMI0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmi_cvi_intr                      :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_2    :4 ;	//7:4
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_1    :4 ;	//11:8
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_0    :4 ;	//15:12
	UINT32 cnt_hdmi_cvi_intr_meas             :4 ;	//19:16
	UINT32 cnt_hdmi_cvi_intr_info             :4 ;	//23:20
	UINT32 cnt_hdmi_cvi_intr_cs               :4 ;	//27:24
	UINT32 cnt_hdmi_cvi_intr_meta             :4 ;	//31:28
}O18A0_CVC_INFO_HDMI0_T;
/*-----------------------------------------------------------------------------
                             0xc9000054L INFO_HDMI1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmi_cvi_cs                        :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_2    :4 ;	//7:4
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_1    :4 ;	//11:8
	UINT32 cnt_hdmirx_prt0_mcu_intr_ris_0    :4 ;	//15:12
	UINT32 cnt_hdmi_cvi_intr_meas             :4 ;	//19:16
	UINT32 cnt_hdmirx_prt2_mcu_intr_ris_2    :4 ;	//23:20
	UINT32 cnt_hdmirx_prt2_mcu_intr_ris_1    :4 ;	//27:24
	UINT32 cnt_hdmirx_prt2_mcu_intr_ris_0    :4 ;	//31:28
	UINT32 cnt_hdmirx_prt1_mcu_intr_ris_2    :4 ;	//23:20
	UINT32 cnt_hdmirx_prt1_mcu_intr_ris_1    :4 ;	//27:24
	UINT32 cnt_hdmirx_prt1_mcu_intr_ris_0    :4 ;	//31:28
}O18A0_CVC_INFO_HDMI1_T;
/*-----------------------------------------------------------------------------
                             0xc9000058L INFO_HDMI2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmi_cvi_size_info;	//31:0
}O18A0_CVC_INFO_HDMI2_T;
/*-----------------------------------------------------------------------------
                             0xc900005cL INFO_HDMI3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmi_cvi_size_meas;	//31:0
}O18A0_CVC_INFO_HDMI3_T;
/*-----------------------------------------------------------------------------
                             0xc9000060L INFO_HDMI4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmirx_prt0_mcu_intr               :3 ;	//2:0
	UINT32 hdmirx_prt1_mcu_intr               :3 ;	//5:3
	UINT32 hdmirx_prt2_mcu_intr               :3 ;	//8:6
}O18A0_CVC_INFO_HDMI4_T;
/*-----------------------------------------------------------------------------
                             0xc9000064L INTR_MASK_HDMI                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hdmirx_prt0_mcu_intr_mask          :3 ;	//2:0
	UINT32 hdmirx_prt1_mcu_intr_mask          :3 ;	//5:3
	UINT32 hdmirx_prt2_mcu_intr_mask          :3 ;	//8:6
	UINT32 hdmirx_prt3_mcu_intr_mask          :3 ;	//11:9
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hdmi_cvi_meas_intr_mask            :1 ;	//16
	UINT32 hdmi_cvi_info_intr_mask            :1 ;	//17
	UINT32 hdmi_cvi_cs_intr_mask              :1 ;	//18
}O18A0_CVC_INTR_MASK_HDMI_T;
/*-----------------------------------------------------------------------------
                             0xc9000070L INFO_CVI0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 valid_d                            :1 ;	//0 
	UINT32 valid_h                            :1 ;	//1 
	UINT32 valid_v                            :1 ;	//2 
	UINT32 valid_s                            :1 ;	//3 
	UINT32 scan                               :1 ;	//4 
	UINT32 bit_mode                           :1 ;	//5 
	UINT32 aspect                             :1 ;	//6 
	UINT32 sel_src                            :4 ;	//10:7
	UINT32 frame_lr                           :1 ;	//11
	UINT32 field_id                           :1 ;	//12
	UINT32 vactive                            :1 ;	//13
}O18A0_CVC_INFO_CVI0_T;
/*-----------------------------------------------------------------------------
                             0xc9000074L INFO_CVI1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 valid_d                            :1 ;	//0 
	UINT32 valid_h                            :1 ;	//1 
	UINT32 valid_v                            :1 ;	//2 
	UINT32 valid_s                            :1 ;	//3 
	UINT32 scan                               :1 ;	//4 
	UINT32 bit_mode                           :1 ;	//5 
	UINT32 aspect                             :1 ;	//6 
	UINT32 sel_src                            :4 ;	//10:7
	UINT32 frame_lr                           :1 ;	//11
	UINT32 field_id                           :1 ;	//12
	UINT32 vactive                            :1 ;	//13
}O18A0_CVC_INFO_CVI1_T;
/*-----------------------------------------------------------------------------
                             0xc9000078L INFO_CVI2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 valid_d                            :1 ;	//0 
	UINT32 valid_h                            :1 ;	//1 
	UINT32 valid_v                            :1 ;	//2 
	UINT32 valid_s                            :1 ;	//3 
	UINT32 scan                               :1 ;	//4 
	UINT32 bit_mode                           :1 ;	//5 
	UINT32 aspect                             :1 ;	//6 
	UINT32 sel_src                            :4 ;	//10:7
	UINT32 frame_lr                           :1 ;	//11
	UINT32 field_id                           :1 ;	//12
	UINT32 vactive                            :1 ;	//13
}O18A0_CVC_INFO_CVI2_T;
/*-----------------------------------------------------------------------------
                             0xc900007cL INFO_CVI3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 valid_d                            :1 ;	//0 
	UINT32 valid_h                            :1 ;	//1 
	UINT32 valid_v                            :1 ;	//2 
	UINT32 valid_s                            :1 ;	//3 
	UINT32 scan                               :1 ;	//4 
	UINT32 bit_mode                           :1 ;	//5 
	UINT32 aspect                             :1 ;	//6 
	UINT32 sel_src                            :4 ;	//10:7
	UINT32 frame_lr                           :1 ;	//11
	UINT32 field_id                           :1 ;	//12
	UINT32 vactive                            :1 ;	//13
}O18A0_CVC_INFO_CVI3_T;
/*-----------------------------------------------------------------------------
                             0xc9000080L CTRL_BLOCK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_cvd_scart_en                   :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_lvds_type_sel                  :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_ch3_input_type                 :1 ;	//8 
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_hdmi_input_type                :1 ;	//12
	UINT32 reserved04                         :11;	//reserved
	UINT32 reg_cvd_input_mux_sel              :1 ;	//24
	UINT32 reserved05                         :3 ;	//reserved
	UINT32 reg_sel_mif_axuser                 :4 ;	//31:28
}O18A0_CVC_CTRL_BLOCK_T;
/*-----------------------------------------------------------------------------
                             0xc9000084L PG_CVE_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :12;	//reserved
	UINT32 burst_amp                          :8 ;	//19:12
	UINT32 y_filter                           :2 ;	//9:8
	UINT32 c_filter                           :2 ;	//5:4
	UINT32 standard                           :3 ;	//2:0
	UINT32 reserved02                         :9 ;	//reserved
}O18A0_CVC_PG_CVE_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000088L PG_CVE_PHASE_INCR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 phase_incr;	//31:0
}O18A0_CVC_PG_CVE_PHASE_INCR_T;
/*-----------------------------------------------------------------------------
                             0xc900008cL HDMI_FBC_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fbd_en                             :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 fbd_reset_step                     :2 ;	//3:2
	UINT32 fbd_blur_cut                       :8 ;	//11:4
	UINT32 fbd_blur_en                        :1 ;	//12
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hdmi_fbd_imux                      :2 ;	//17:16
}O18A0_CVC_HDMI_FBC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000090L SUB_BUS_AXI_FLUSH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cvd_sub_bus_md_flush_done          :1 ;	//0 
	UINT32 cvd_sub_bus_md_flush_en            :1 ;	//1 
	UINT32 cvd_sub_bus_vd_flush_done          :1 ;	//2 
	UINT32 cvd_sub_bus_vd_flush_en            :1 ;	//3 
	UINT32 cvd_sub_bus_flush_byp              :1 ;	//4 
}O18A0_CVC_SUB_BUS_AXI_FLUSH_T;
/*-----------------------------------------------------------------------------
                             0xc9000094L CVI_INTR_MUX_SEL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cvi_intr_mux_sel;	//31:0
}O18A0_CVC_CVI_INTR_MUX_SEL_T;
/*-----------------------------------------------------------------------------
                             0xc90000c0L PIC_INIT_G0_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G0_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000c4L PIC_INIT_G1_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G1_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000c8L PIC_INIT_G2_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G2_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000ccL PIC_INIT_G3_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G3_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000d0L PIC_INIT_G4_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G4_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000d4L PIC_INIT_G5_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G5_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000d8L PIC_INIT_G6_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G6_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000dcL PIC_INIT_G7_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pic_init_timer                     :24;	//23:0
	UINT32 start_interval_mode_en             :1 ;	//24
	UINT32 start_interval_mode                :3 ;	//27:25
	UINT32 pic_init_width_mode_en             :1 ;	//28
	UINT32 pic_init_width_mode                :2 ;	//30:29
	UINT32 wait_pic_end_en                    :1 ;	//31
}O18A0_CVC_PIC_INIT_G7_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90000e4L DBG_TIMER_RUN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 info_timer_run                     :24;	//23:0
	UINT32 idx_end_src                        :3 ;	//26:24
	UINT32 sel_end_src                        :1 ;	//27
	UINT32 idx_start_src                      :3 ;	//30:28
	UINT32 sel_start_src                      :1 ;	//31
}O18A0_CVC_DBG_TIMER_RUN_T;
/*-----------------------------------------------------------------------------
                             0xc90000e8L DBG_TIMER_BLK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 info_timer_blk                     :24;	//23:0
	UINT32 ctrl_timer_blk                     :8 ;	//31:24
}O18A0_CVC_DBG_TIMER_BLK_T;
/*-----------------------------------------------------------------------------
                             0xc90000ecL CTRL_MONITOR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ctrl_monitor;	//31:0
}O18A0_CVC_CTRL_MONITOR_T;
/*-----------------------------------------------------------------------------
                             0xc90000f0L CTRL_PIC_END                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 g0_pic_end_en                      :1 ;	//0 
	UINT32 g1_pic_end_en                      :1 ;	//1 
	UINT32 g2_pic_end_en                      :1 ;	//2 
	UINT32 g3_pic_end_en                      :1 ;	//3 
	UINT32 g4_pic_end_en                      :1 ;	//4 
	UINT32 g5_pic_end_en                      :1 ;	//5 
	UINT32 g6_pic_end_en                      :1 ;	//6 
	UINT32 g7_pic_end_en                      :1 ;	//7 
	UINT32 b0_pic_end_en                      :1 ;	//8 
	UINT32 b1_pic_end_en                      :1 ;	//9 
	UINT32 b2_pic_end_en                      :1 ;	//10
	UINT32 b3_pic_end_en                      :1 ;	//11
	UINT32 b4_pic_end_en                      :1 ;	//12
	UINT32 b5_pic_end_en                      :1 ;	//13
	UINT32 b6_pic_end_en                      :1 ;	//14
	UINT32 b7_pic_end_en                      :1 ;	//15
	UINT32 pic_end_g0_force_en                :1 ;	//16
	UINT32 pic_end_g1_force_en                :1 ;	//17
	UINT32 pic_end_g2_force_en                :1 ;	//18
	UINT32 pic_end_g3_force_en                :1 ;	//19
	UINT32 pic_end_g4_force_en                :1 ;	//20
	UINT32 pic_end_g5_force_en                :1 ;	//21
	UINT32 pic_end_g6_force_en                :1 ;	//22
	UINT32 pic_end_g7_force_en                :1 ;	//23
	UINT32 pic_end_g0_force_value             :1 ;	//24
	UINT32 pic_end_g1_force_value             :1 ;	//25
	UINT32 pic_end_g2_force_value             :1 ;	//26
	UINT32 pic_end_g3_force_value             :1 ;	//27
	UINT32 pic_end_g4_force_value             :1 ;	//28
	UINT32 pic_end_g5_force_value             :1 ;	//29
	UINT32 pic_end_g6_force_value             :1 ;	//30
	UINT32 pic_end_g7_force_value             :1 ;	//31
}O18A0_CVC_CTRL_PIC_END_T;
/*-----------------------------------------------------------------------------
                             0xc90000f4L INFO_PIC_END                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 g0_pic_end                         :1 ;	//0 
	UINT32 g1_pic_end                         :1 ;	//1 
	UINT32 g2_pic_end                         :1 ;	//2 
	UINT32 g3_pic_end                         :1 ;	//3 
	UINT32 g4_pic_end                         :1 ;	//4 
	UINT32 g5_pic_end                         :1 ;	//5 
	UINT32 g6_pic_end                         :1 ;	//6 
	UINT32 g7_pic_end                         :1 ;	//7 
	UINT32 b0_pic_end                         :1 ;	//8 
	UINT32 b1_pic_end                         :1 ;	//9 
	UINT32 b2_pic_end                         :1 ;	//10
	UINT32 b3_pic_end                         :1 ;	//11
	UINT32 b4_pic_end                         :1 ;	//12
	UINT32 b5_pic_end                         :1 ;	//13
	UINT32 b6_pic_end                         :1 ;	//14
	UINT32 b7_pic_end                         :1 ;	//15
	UINT32 g0_pic_turn                        :1 ;	//16
	UINT32 g1_pic_turn                        :1 ;	//17
	UINT32 g2_pic_turn                        :1 ;	//18
	UINT32 g3_pic_turn                        :1 ;	//19
	UINT32 g4_pic_turn                        :1 ;	//20
	UINT32 g5_pic_turn                        :1 ;	//21
	UINT32 g6_pic_turn                        :1 ;	//22
	UINT32 g7_pic_turn                        :1 ;	//23
}O18A0_CVC_INFO_PIC_END_T;
/*-----------------------------------------------------------------------------
                             0xc90000f8L CTRL_GPIO                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 rst_async_bridge                   :8 ;	//7:0
	UINT32 reg_ctrl_gpio                      :16;	//23:8
	UINT32 hdmi0_clk                          :1 ;	//24
	UINT32 hdmi1_clk                          :1 ;	//25
	UINT32 hdmi2_clk                          :1 ;	//26
	UINT32 hdmi3_clk                          :1 ;	//27
	UINT32 cvi0_clk                           :1 ;	//28
	UINT32 cvi1_clk                           :1 ;	//29
	UINT32 cvi2_clk                           :1 ;	//30
	UINT32 cvi3_clk                           :1 ;	//31
}O18A0_CVC_CTRL_GPIO_T;
/*-----------------------------------------------------------------------------
                             0xc90000fcL CTRL_AXI_USER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cvd_vd_awuser                      :4 ;	//3:0
	UINT32 cvd_vd_aruser                      :4 ;	//7:4
	UINT32 cvd_md_awuser                      :4 ;	//11:8
	UINT32 cvd_md_aruser                      :4 ;	//15:12
}O18A0_CVC_CTRL_AXI_USER_T;


/*-----------------------------------------------------------------------------
		0xc800b000L pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_init                        : 1 ;  //     0     
	UINT32 g1_pic_init                        : 1 ;  //     1     
	UINT32 g2_pic_init                        : 1 ;  //     2     
	UINT32 g3_pic_init                        : 1 ;  //     3     
	UINT32 g4_pic_init                        : 1 ;  //     4     
	UINT32 g5_pic_init                        : 1 ;  //     5     
	UINT32 g6_pic_init                        : 1 ;  //     6     
	UINT32 g7_pic_init                        : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_init                       : 1 ;  //    16     
	UINT32 g1_auto_init                       : 1 ;  //    17     
	UINT32 g2_auto_init                       : 1 ;  //    18     
	UINT32 g3_auto_init                       : 1 ;  //    19     
	UINT32 g4_auto_init                       : 1 ;  //    20     
	UINT32 g5_auto_init                       : 1 ;  //    21     
	UINT32 g6_auto_init                       : 1 ;  //    22     
	UINT32 g7_auto_init                       : 1 ;  //    23     
} O18A0_VSD_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800b004L pic_start ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_start                       : 1 ;  //     0     
	UINT32 g1_pic_start                       : 1 ;  //     1     
	UINT32 g2_pic_start                       : 1 ;  //     2     
	UINT32 g3_pic_start                       : 1 ;  //     3     
	UINT32 g4_pic_start                       : 1 ;  //     4     
	UINT32 g5_pic_start                       : 1 ;  //     5     
	UINT32 g6_pic_start                       : 1 ;  //     6     
	UINT32 g7_pic_start                       : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_2nd                        : 1 ;  //    16     
	UINT32 g1_auto_2nd                        : 1 ;  //    17     
	UINT32 g2_auto_2nd                        : 1 ;  //    18     
	UINT32 g3_auto_2nd                        : 1 ;  //    19     
	UINT32 g4_auto_2nd                        : 1 ;  //    20     
	UINT32 g5_auto_2nd                        : 1 ;  //    21     
	UINT32 g6_auto_2nd                        : 1 ;  //    22     
	UINT32 g7_auto_2nd                        : 1 ;  //    23     
} O18A0_VSD_PIC_START_T;

/*-----------------------------------------------------------------------------
		0xc800b008L ctrl_auto_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_g0_auto_init               : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 idx_src_g1_auto_init               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_src_g2_auto_init               : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 idx_src_g3_auto_init               : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 idx_src_g4_auto_init               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 idx_src_g5_auto_init               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 idx_src_g6_auto_init               : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 idx_src_g7_auto_init               : 3 ;  // 30:28     
} O18A0_VSD_CTRL_AUTO_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800b00cL ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse              : 3 ;  //  2: 0     
	UINT32 sel_src_i0_intr_pulse              : 1 ;  //     3     
	UINT32 idx_src_i1_intr_pulse              : 3 ;  //  6: 4     
	UINT32 sel_src_i1_intr_pulse              : 1 ;  //     7     
	UINT32 idx_src_i2_intr_pulse              : 3 ;  // 10: 8     
	UINT32 sel_src_i2_intr_pulse              : 1 ;  //    11     
	UINT32 idx_src_i3_intr_pulse              : 3 ;  // 14:12     
	UINT32 sel_src_i3_intr_pulse              : 1 ;  //    15     
	UINT32 idx_src_i4_intr_pulse              : 3 ;  // 18:16     
	UINT32 sel_src_i4_intr_pulse              : 1 ;  //    19     
	UINT32 idx_src_i5_intr_pulse              : 3 ;  // 22:20     
	UINT32 sel_src_i5_intr_pulse              : 1 ;  //    23     
	UINT32 idx_src_i6_intr_pulse              : 3 ;  // 26:24     
	UINT32 sel_src_i6_intr_pulse              : 1 ;  //    27     
	UINT32 idx_src_i7_intr_pulse              : 3 ;  // 30:28     
	UINT32 sel_src_i7_intr_pulse              : 1 ;  //    31     
} O18A0_VSD_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc800b010L intr_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_i0_intr_pulse                 : 1 ;  //     0     
	UINT32 intr_i1_intr_pulse                 : 1 ;  //     1     
	UINT32 intr_i2_intr_pulse                 : 1 ;  //     2     
	UINT32 intr_i3_intr_pulse                 : 1 ;  //     3     
	UINT32 intr_i4_intr_pulse                 : 1 ;  //     4     
	UINT32 intr_i5_intr_pulse                 : 1 ;  //     5     
	UINT32 intr_i6_intr_pulse                 : 1 ;  //     6     
	UINT32 intr_i7_intr_pulse                 : 1 ;  //     7     
	UINT32 intr_g0_pic_end                    : 1 ;  //     8     
	UINT32 intr_g1_pic_end                    : 1 ;  //     9     
	UINT32 intr_g2_pic_end                    : 1 ;  //    10     
	UINT32 intr_g3_pic_end                    : 1 ;  //    11     
	UINT32 intr_g4_pic_end                    : 1 ;  //    12     
	UINT32 intr_g5_pic_end                    : 1 ;  //    13     
	UINT32 intr_g6_pic_end                    : 1 ;  //    14     
	UINT32 intr_g7_pic_end                    : 1 ;  //    15     
	UINT32 intr_vcp                           : 1 ;  //    16     
} O18A0_VSD_INTR_REG_T;

/*-----------------------------------------------------------------------------
		0xc800b014L intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                  : 1 ;  //     0     
	UINT32 mask_i1_src_pulse                  : 1 ;  //     1     
	UINT32 mask_i2_src_pulse                  : 1 ;  //     2     
	UINT32 mask_i3_src_pulse                  : 1 ;  //     3     
	UINT32 mask_i4_src_pulse                  : 1 ;  //     4     
	UINT32 mask_i5_src_pulse                  : 1 ;  //     5     
	UINT32 mask_i6_src_pulse                  : 1 ;  //     6     
	UINT32 mask_i7_src_pulse                  : 1 ;  //     7     
	UINT32 mask_g0_pic_end                    : 1 ;  //     8     
	UINT32 mask_g1_pic_end                    : 1 ;  //     9     
	UINT32 mask_g2_pic_end                    : 1 ;  //    10     
	UINT32 mask_g3_pic_end                    : 1 ;  //    11     
	UINT32 mask_g4_pic_end                    : 1 ;  //    12     
	UINT32 mask_g5_pic_end                    : 1 ;  //    13     
	UINT32 mask_g6_pic_end                    : 1 ;  //    14     
	UINT32 mask_g7_pic_end                    : 1 ;  //    15     
	UINT32 mask_vcp                           : 1 ;  //    16     
} O18A0_VSD_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xc800b018L intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                   : 1 ;  //     0     
	UINT32 mux_i1_src_pulse                   : 1 ;  //     1     
	UINT32 mux_i2_src_pulse                   : 1 ;  //     2     
	UINT32 mux_i3_src_pulse                   : 1 ;  //     3     
	UINT32 mux_i4_src_pulse                   : 1 ;  //     4     
	UINT32 mux_i5_src_pulse                   : 1 ;  //     5     
	UINT32 mux_i6_src_pulse                   : 1 ;  //     6     
	UINT32 mux_i7_src_pulse                   : 1 ;  //     7     
	UINT32 mux_g0_pic_end                     : 1 ;  //     8     
	UINT32 mux_g1_pic_end                     : 1 ;  //     9     
	UINT32 mux_g2_pic_end                     : 1 ;  //    10     
	UINT32 mux_g3_pic_end                     : 1 ;  //    11     
	UINT32 mux_g4_pic_end                     : 1 ;  //    12     
	UINT32 mux_g5_pic_end                     : 1 ;  //    13     
	UINT32 mux_g6_pic_end                     : 1 ;  //    14     
	UINT32 mux_g7_pic_end                     : 1 ;  //    15     
	UINT32 mux_vcp                            : 1 ;  //    16     
} O18A0_VSD_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xc800b01cL intr_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 en_i0_src_pulse                    : 1 ;  //     0     
	UINT32 en_i1_src_pulse                    : 1 ;  //     1     
	UINT32 en_i2_src_pulse                    : 1 ;  //     2     
	UINT32 en_i3_src_pulse                    : 1 ;  //     3     
	UINT32 en_i4_src_pulse                    : 1 ;  //     4     
	UINT32 en_i5_src_pulse                    : 1 ;  //     5     
	UINT32 en_i6_src_pulse                    : 1 ;  //     6     
	UINT32 en_i7_src_pulse                    : 1 ;  //     7     
	UINT32 en_g0_pic_end                      : 1 ;  //     8     
	UINT32 en_g1_pic_end                      : 1 ;  //     9     
	UINT32 en_g2_pic_end                      : 1 ;  //    10     
	UINT32 en_g3_pic_end                      : 1 ;  //    11     
	UINT32 en_g4_pic_end                      : 1 ;  //    12     
	UINT32 en_g5_pic_end                      : 1 ;  //    13     
	UINT32 en_g6_pic_end                      : 1 ;  //    14     
	UINT32 en_g7_pic_end                      : 1 ;  //    15     
	UINT32 en_vcp                             : 1 ;  //    16     
} O18A0_VSD_INTR_EN_T;

/*-----------------------------------------------------------------------------
		0xc800b020L ctrl_sync_gen_mv0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbp                                : 16;  // 15: 0     
	UINT32 vfp                                : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_MV0_T;

/*-----------------------------------------------------------------------------
		0xc800b024L ctrl_sync_gen_mv1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactv                              : 16;  // 15: 0     
	UINT32 vsync                              : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_MV1_T;

/*-----------------------------------------------------------------------------
		0xc800b028L ctrl_sync_gen_mv2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hbp                                : 16;  // 15: 0     
	UINT32 hfp                                : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_MV2_T;

/*-----------------------------------------------------------------------------
		0xc800b02cL ctrl_sync_gen_mv3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hactv                              : 16;  // 15: 0     
	UINT32 hsync                              : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_MV3_T;

/*-----------------------------------------------------------------------------
		0xc800b030L ctrl_sync_gen_mv4 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset0                           : 16;  // 15: 0     
	UINT32 force_update_auto_en               : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 force_update_src_sel               : 2 ;  // 21:20     
	UINT32                                    : 1 ;  //    22     reserved
	UINT32 sync_polarity                      : 1 ;  //    23     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 h3d_flag_update_sel                 : 1 ;  //    25     
	UINT32 h3d_flag_en                         : 1 ;  //    26     
	UINT32 disp_frame_lr                      : 1 ;  //    27     
	UINT32                                    : 3 ;  // 30:28     reserved
	UINT32 force_update                       : 1 ;  //    31     
} O18A0_VSD_CTRL_SYNC_GEN_MV4_T;

/*-----------------------------------------------------------------------------
		0xc800b034L ctrl_sync_gen_mv5 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_h                              : 16;  // 15: 0     
	UINT32 dly_v                              : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_MV5_T;

/*-----------------------------------------------------------------------------
		0xc800b038L ctrl_sync_gen_mv6 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_disp_pulse                     : 28;  // 27: 0     
	UINT32 disp_pulse_src_sel                 : 1 ;  //    28     
} O18A0_VSD_CTRL_SYNC_GEN_MV6_T;

/*-----------------------------------------------------------------------------
		0xc800b03cL ctrl_sync_gen_mv7 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_disp_pulse1                    : 28;  // 27: 0     
	UINT32 disp_pulse1_src_sel                : 1 ;  //    28     
} O18A0_VSD_CTRL_SYNC_GEN_MV7_T;

/*-----------------------------------------------------------------------------
		0xc800b060L ctrl_sync_gen_sb0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbp                                : 16;  // 15: 0     
	UINT32 vfp                                : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_SB0_T;

/*-----------------------------------------------------------------------------
		0xc800b064L ctrl_sync_gen_sb1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactv                              : 16;  // 15: 0     
	UINT32 vsync                              : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_SB1_T;

/*-----------------------------------------------------------------------------
		0xc800b068L ctrl_sync_gen_sb2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hbp                                : 16;  // 15: 0     
	UINT32 hfp                                : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_SB2_T;

/*-----------------------------------------------------------------------------
		0xc800b06cL ctrl_sync_gen_sb3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hactv                              : 16;  // 15: 0     
	UINT32 hsync                              : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_SB3_T;

/*-----------------------------------------------------------------------------
		0xc800b070L ctrl_sync_gen_sb4 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset0                           : 16;  // 15: 0     
	UINT32 force_update_auto_en               : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 force_update_src_sel               : 2 ;  // 21:20     
	UINT32                                    : 1 ;  //    22     reserved
	UINT32 sync_polarity                      : 1 ;  //    23     
	UINT32                                    : 3 ;  // 26:24     reserved
	UINT32 disp_frame_lr                      : 1 ;  //    27     
	UINT32                                    : 3 ;  // 30:28     reserved
	UINT32 force_update                       : 1 ;  //    31     
} O18A0_VSD_CTRL_SYNC_GEN_SB4_T;

/*-----------------------------------------------------------------------------
		0xc800b074L ctrl_sync_gen_sb5 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_hs                             : 16;  // 15: 0     
	UINT32 dly_vs                             : 16;  // 31:16     
} O18A0_VSD_CTRL_SYNC_GEN_SB5_T;

/*-----------------------------------------------------------------------------
		0xc800b078L ctrl_sync_gen_sb6 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_disp_pulse                     : 28;  // 27: 0     
	UINT32 disp_pulse1_src_sel                : 1 ;  //    28     
} O18A0_VSD_CTRL_SYNC_GEN_SB6_T;

/*-----------------------------------------------------------------------------
		0xc800b07cL ctrl_sync_gen_sb7 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_disp_pulse1                    : 28;  // 27: 0     
	UINT32 disp_pulse1_src_sel                : 1 ;  //    28     
} O18A0_VSD_CTRL_SYNC_GEN_SB7_T;

/*-----------------------------------------------------------------------------
		0xc800b080L info_mv_dco_mfc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_mfc                            : 32;  // 31: 0     
} O18A0_VSD_INFO_MV_DCO_MFC_T;

/*-----------------------------------------------------------------------------
		0xc800b084L info_mv_dco_dfc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dfc                            : 32;  // 31: 0     
} O18A0_VSD_INFO_MV_DCO_DFC_T;

/*-----------------------------------------------------------------------------
		0xc800b088L info_mv_dco_dflc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dflc                           : 32;  // 31: 0     
} O18A0_VSD_INFO_MV_DCO_DFLC_T;

/*-----------------------------------------------------------------------------
		0xc800b08cL ctrl_dco_num ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_o_vsync_num                    : 8 ;  //  7: 0     
	UINT32 reg_disable_gated_o_vsync          : 1 ;  //     8     
	UINT32                                    : 7 ;  // 15: 9     reserved
	UINT32 reg_i_vsync_num                    : 8 ;  // 23:16     
	UINT32 reg_disable_gated_i_vsync          : 1 ;  //    24     
} O18A0_VSD_CTRL_DCO_NUM_T;

/*-----------------------------------------------------------------------------
		0xc800b090L ctrl_dco_fcw ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_fcw                            : 22;  // 21: 0     
} O18A0_VSD_CTRL_DCO_FCW_T;

/*-----------------------------------------------------------------------------
		0xc800b094L info_sb_dco_mfc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_mfc                            : 32;  // 31: 0     
} O18A0_VSD_INFO_SB_DCO_MFC_T;

/*-----------------------------------------------------------------------------
		0xc800b098L info_sb_dco_dfc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dfc                            : 32;  // 31: 0     
} O18A0_VSD_INFO_SB_DCO_DFC_T;

/*-----------------------------------------------------------------------------
		0xc800b09cL info_sb_dco_dflc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dflc                           : 32;  // 31: 0     
} O18A0_VSD_INFO_SB_DCO_DFLC_T;

/*-----------------------------------------------------------------------------
		0xc800b0a0L ctrl_sr_pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 enable_sr_pic_init                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 idx_sr_src                         : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_sr_init                        : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 idx_sr_start                       : 2 ;  // 13:12     
	UINT32                                    : 14;  // 27:14     reserved
	UINT32 sel_sr_mif                         : 1 ;  //    28     
} O18A0_VSD_CTRL_SR_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800b0a4L pic_init_sr_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sr_pic_init_timer                  : 32;  // 31: 0     
} O18A0_VSD_PIC_INIT_SR_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0b0L ctrl_block ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsd_top_sync_out_sel               : 1 ;  //     0     
	UINT32                                    : 7 ;  //  7: 1     reserved
	UINT32 h3d_detour_swap                    : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 h3d_detour_en                      : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 shp_detour_en                      : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 h3d_flag_out_en                     : 1 ;  //    20     
	UINT32 h3d_flag_out_sel                    : 1 ;  //    21     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 mon_sync_mv_off                    : 1 ;  //    24     
	UINT32 mon_sync_so_off                    : 1 ;  //    25     
	UINT32 mon_sync_ht_off                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 reg_sel_timer_reset_src            : 3 ;  // 30:28     
	UINT32 sel_dco_fcw                        : 1 ;  //    31     
} O18A0_VSD_CTRL_BLOCK_T;

/*-----------------------------------------------------------------------------
		0xc800b0c0L pic_init_g0_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0c4L pic_init_g1_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0c8L pic_init_g2_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0ccL pic_init_g3_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0d0L pic_init_g4_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0d4L pic_init_g5_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G5_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0d8L pic_init_g6_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G6_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0dcL pic_init_g7_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_VSD_PIC_INIT_G7_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc800b0e4L dbg_timer_run ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_run                     : 24;  // 23: 0     
	UINT32 ctrl_timer_run                     : 8 ;  // 31:24     
} O18A0_VSD_DBG_TIMER_RUN_T;

/*-----------------------------------------------------------------------------
		0xc800b0e8L dbg_timer_blk ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_blk                     : 24;  // 23: 0     
	UINT32 ctrl_timer_blk                     : 8 ;  // 31:24     
} O18A0_VSD_DBG_TIMER_BLK_T;

/*-----------------------------------------------------------------------------
		0xc800b0ecL ctrl_monitor ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctrl_monitor                       : 4 ;  //  3: 0     
} O18A0_VSD_CTRL_MONITOR_T;

/*-----------------------------------------------------------------------------
		0xc800b0f0L ctrl_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 b0_pic_end_en                      : 1 ;  //     0     
	UINT32 b1_pic_end_en                      : 1 ;  //     1     
	UINT32 b2_pic_end_en                      : 1 ;  //     2     
	UINT32 b3_pic_end_en                      : 1 ;  //     3     
	UINT32 b4_pic_end_en                      : 1 ;  //     4     
	UINT32 b5_pic_end_en                      : 1 ;  //     5     
	UINT32 b6_pic_end_en                      : 1 ;  //     6     
	UINT32 b7_pic_end_en                      : 1 ;  //     7     
	UINT32 b8_pic_end_en                      : 1 ;  //     8     
	UINT32 b9_pic_end_en                      : 1 ;  //     9     
	UINT32 b10_pic_end_en                     : 1 ;  //    10     
	UINT32 b11_pic_end_en                     : 1 ;  //    11     
	UINT32 b12_pic_end_en                     : 1 ;  //    12     
	UINT32 b13_pic_end_en                     : 1 ;  //    13     
	UINT32 b14_pic_end_en                     : 1 ;  //    14     
	UINT32 b15_pic_end_en                     : 1 ;  //    15     
	UINT32 pic_end_g0_force_en                : 1 ;  //    16     
	UINT32 pic_end_g1_force_en                : 1 ;  //    17     
	UINT32 pic_end_g2_force_en                : 1 ;  //    18     
	UINT32 pic_end_g3_force_en                : 1 ;  //    19     
	UINT32 pic_end_g4_force_en                : 1 ;  //    20     
	UINT32 pic_end_g5_force_en                : 1 ;  //    21     
	UINT32 pic_end_g6_force_en                : 1 ;  //    22     
	UINT32 pic_end_g7_force_en                : 1 ;  //    23     
	UINT32 pic_end_g0_force_value             : 1 ;  //    24     
	UINT32 pic_end_g1_force_value             : 1 ;  //    25     
	UINT32 pic_end_g2_force_value             : 1 ;  //    26     
	UINT32 pic_end_g3_force_value             : 1 ;  //    27     
	UINT32 pic_end_g4_force_value             : 1 ;  //    28     
	UINT32 pic_end_g5_force_value             : 1 ;  //    29     
	UINT32 pic_end_g6_force_value             : 1 ;  //    30     
	UINT32 pic_end_g7_force_value             : 1 ;  //    31     
} O18A0_VSD_CTRL_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc800b0f4L info_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end                         : 1 ;  //     0     
	UINT32 g1_pic_end                         : 1 ;  //     1     
	UINT32 g2_pic_end                         : 1 ;  //     2     
	UINT32 g3_pic_end                         : 1 ;  //     3     
	UINT32 g4_pic_end                         : 1 ;  //     4     
	UINT32 g5_pic_end                         : 1 ;  //     5     
	UINT32 g6_pic_end                         : 1 ;  //     6     
	UINT32 g7_pic_end                         : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_pic_turn                        : 1 ;  //    16     
	UINT32 g1_pic_turn                        : 1 ;  //    17     
	UINT32 g2_pic_turn                        : 1 ;  //    18     
	UINT32 g3_pic_turn                        : 1 ;  //    19     
	UINT32 g4_pic_turn                        : 1 ;  //    20     
	UINT32 g5_pic_turn                        : 1 ;  //    21     
	UINT32 g6_pic_turn                        : 1 ;  //    22     
	UINT32 g7_pic_turn                        : 1 ;  //    23     
} O18A0_VSD_INFO_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc800b0f8L ctrl_gpio ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rst_async_bridge_0                 : 1 ;  //     0     
	UINT32 rst_async_bridge_1                 : 1 ;  //     1     
	UINT32 rst_async_bridge_2                 : 1 ;  //     2     
	UINT32                                    : 5 ;  //  7: 3     reserved
	UINT32 reg_gate_rx_u0_y_en                : 1 ;  //     8     
	UINT32                                    : 1 ;  //     9     reserved
	UINT32 reg_gate_rx_u0_c_en                : 1 ;  //    10     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_gate_rx_u1_y_en                : 1 ;  //    12     
	UINT32                                    : 1 ;  //    13     reserved
	UINT32 reg_gate_rx_u1_c_en                : 1 ;  //    14     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_gate_rx_sr_y_en                : 1 ;  //    16     
	UINT32                                    : 7 ;  // 23:17     reserved
	UINT32 sel_output0                        : 2 ;  // 25:24     
	UINT32 en_csc_for_video_output0           : 1 ;  //    26     
	UINT32 disp_stb_clk                       : 1 ;  //    27     
	UINT32 sel_output1                        : 2 ;  // 29:28     
} O18A0_VSD_CTRL_GPIO_T;

/*-----------------------------------------------------------------------------
		0xc800b0fcL ctrl_gmau ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                    : 8 ;  //  7: 0     
	UINT32 smx_aruser                         : 4 ;  // 11: 8     
	UINT32 smx_awuser                         : 4 ;  // 15:12     
	UINT32 ask_to_cnt                         : 10;  // 25:16     
} O18A0_VSD_CTRL_GMAU_T;

/*-----------------------------------------------------------------------------
		0xc8024000L pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_init                        : 1 ;  //     0     
	UINT32 g1_pic_init                        : 1 ;  //     1     
	UINT32 g2_pic_init                        : 1 ;  //     2     
	UINT32 g3_pic_init                        : 1 ;  //     3     
	UINT32 g4_pic_init                        : 1 ;  //     4     
	UINT32 g5_pic_init                        : 1 ;  //     5     
	UINT32 g6_pic_init                        : 1 ;  //     6     
	UINT32 g7_pic_init                        : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_init                       : 1 ;  //    16     
	UINT32 g1_auto_init                       : 1 ;  //    17     
	UINT32 g2_auto_init                       : 1 ;  //    18     
	UINT32 g3_auto_init                       : 1 ;  //    19     
	UINT32 g4_auto_init                       : 1 ;  //    20     
	UINT32 g5_auto_init                       : 1 ;  //    21     
	UINT32 g6_auto_init                       : 1 ;  //    22     
	UINT32 g7_auto_init                       : 1 ;  //    23     
} O18A0_CCO_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc8024004L pic_start ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_start                       : 1 ;  //     0     
	UINT32 g1_pic_start                       : 1 ;  //     1     
	UINT32 g2_pic_start                       : 1 ;  //     2     
	UINT32 g3_pic_start                       : 1 ;  //     3     
	UINT32 g4_pic_start                       : 1 ;  //     4     
	UINT32 g5_pic_start                       : 1 ;  //     5     
	UINT32 g6_pic_start                       : 1 ;  //     6     
	UINT32 g7_pic_start                       : 1 ;  //     7     
} O18A0_CCO_PIC_START_T;

/*-----------------------------------------------------------------------------
		0xc8024008L ctrl_auto_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_g0_auto_init               : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 idx_src_g1_auto_init               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_src_g2_auto_init               : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 idx_src_g3_auto_init               : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 idx_src_g4_auto_init               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 idx_src_g5_auto_init               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 idx_src_g6_auto_init               : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 idx_src_g7_auto_init               : 3 ;  // 30:28     
} O18A0_CCO_CTRL_AUTO_INIT_T;

/*-----------------------------------------------------------------------------
		0xc802400cL ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse              : 3 ;  //  2: 0     
	UINT32 sel_src_i0_intr_pulse              : 1 ;  //     3     
	UINT32 idx_src_i1_intr_pulse              : 3 ;  //  6: 4     
	UINT32 sel_src_i1_intr_pulse              : 1 ;  //     7     
	UINT32 idx_src_i2_intr_pulse              : 3 ;  // 10: 8     
	UINT32 sel_src_i2_intr_pulse              : 1 ;  //    11     
	UINT32 idx_src_i3_intr_pulse              : 3 ;  // 14:12     
	UINT32 sel_src_i3_intr_pulse              : 1 ;  //    15     
	UINT32 idx_src_i4_intr_pulse              : 3 ;  // 18:16     
	UINT32 sel_src_i4_intr_pulse              : 1 ;  //    19     
	UINT32 idx_src_i5_intr_pulse              : 3 ;  // 22:20     
	UINT32 sel_src_i5_intr_pulse              : 1 ;  //    23     
	UINT32 idx_src_i6_intr_pulse              : 3 ;  // 26:24     
	UINT32 sel_src_i6_intr_pulse              : 1 ;  //    27     
	UINT32 idx_src_i7_intr_pulse              : 3 ;  // 30:28     
	UINT32 sel_src_i7_intr_pulse              : 1 ;  //    31     
} O18A0_CCO_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8024010L intr_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_i0_intr_pulse                 : 1 ;  //     0     
	UINT32 intr_i1_intr_pulse                 : 1 ;  //     1     
	UINT32 intr_i2_intr_pulse                 : 1 ;  //     2     
	UINT32 intr_i3_intr_pulse                 : 1 ;  //     3     
	UINT32 intr_i4_intr_pulse                 : 1 ;  //     4     
	UINT32 intr_i5_intr_pulse                 : 1 ;  //     5     
	UINT32 intr_i6_intr_pulse                 : 1 ;  //     6     
	UINT32 intr_i7_intr_pulse                 : 1 ;  //     7     
	UINT32 intr_g0_pic_end                    : 1 ;  //     8     
	UINT32 intr_g1_pic_end                    : 1 ;  //     9     
	UINT32 intr_g2_pic_end                    : 1 ;  //    10     
	UINT32 intr_g3_pic_end                    : 1 ;  //    11     
	UINT32 intr_g4_pic_end                    : 1 ;  //    12     
	UINT32 intr_g5_pic_end                    : 1 ;  //    13     
	UINT32 intr_g6_pic_end                    : 1 ;  //    14     
	UINT32 intr_g7_pic_end                    : 1 ;  //    15     
	UINT32 intr_osd                           : 1 ;  //    16     
} O18A0_CCO_INTR_REG_T;

/*-----------------------------------------------------------------------------
		0xc8024014L intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                  : 1 ;  //     0     
	UINT32 mask_i1_src_pulse                  : 1 ;  //     1     
	UINT32 mask_i2_src_pulse                  : 1 ;  //     2     
	UINT32 mask_i3_src_pulse                  : 1 ;  //     3     
	UINT32 mask_i4_src_pulse                  : 1 ;  //     4     
	UINT32 mask_i5_src_pulse                  : 1 ;  //     5     
	UINT32 mask_i6_src_pulse                  : 1 ;  //     6     
	UINT32 mask_i7_src_pulse                  : 1 ;  //     7     
	UINT32 mask_g0_pic_end                    : 1 ;  //     8     
	UINT32 mask_g1_pic_end                    : 1 ;  //     9     
	UINT32 mask_g2_pic_end                    : 1 ;  //    10     
	UINT32 mask_g3_pic_end                    : 1 ;  //    11     
	UINT32 mask_g4_pic_end                    : 1 ;  //    12     
	UINT32 mask_g5_pic_end                    : 1 ;  //    13     
	UINT32 mask_g6_pic_end                    : 1 ;  //    14     
	UINT32 mask_g7_pic_end                    : 1 ;  //    15     
	UINT32 mask_osd                           : 1 ;  //    16     
} O18A0_CCO_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xc8024018L intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                   : 1 ;  //     0     
	UINT32 mux_i1_src_pulse                   : 1 ;  //     1     
	UINT32 mux_i2_src_pulse                   : 1 ;  //     2     
	UINT32 mux_i3_src_pulse                   : 1 ;  //     3     
	UINT32 mux_i4_src_pulse                   : 1 ;  //     4     
	UINT32 mux_i5_src_pulse                   : 1 ;  //     5     
	UINT32 mux_i6_src_pulse                   : 1 ;  //     6     
	UINT32 mux_i7_src_pulse                   : 1 ;  //     7     
	UINT32 mux_g0_pic_end                     : 1 ;  //     8     
	UINT32 mux_g1_pic_end                     : 1 ;  //     9     
	UINT32 mux_g2_pic_end                     : 1 ;  //    10     
	UINT32 mux_g3_pic_end                     : 1 ;  //    11     
	UINT32 mux_g4_pic_end                     : 1 ;  //    12     
	UINT32 mux_g5_pic_end                     : 1 ;  //    13     
	UINT32 mux_g6_pic_end                     : 1 ;  //    14     
	UINT32 mux_g7_pic_end                     : 1 ;  //    15     
	UINT32 mux_osd                            : 1 ;  //    16     
} O18A0_CCO_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xc802401cL intr_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 en_i0_src_pulse                    : 1 ;  //     0     
	UINT32 en_i1_src_pulse                    : 1 ;  //     1     
	UINT32 en_i2_src_pulse                    : 1 ;  //     2     
	UINT32 en_i3_src_pulse                    : 1 ;  //     3     
	UINT32 en_i4_src_pulse                    : 1 ;  //     4     
	UINT32 en_i5_src_pulse                    : 1 ;  //     5     
	UINT32 en_i6_src_pulse                    : 1 ;  //     6     
	UINT32 en_i7_src_pulse                    : 1 ;  //     7     
	UINT32 en_g0_pic_end                      : 1 ;  //     8     
	UINT32 en_g1_pic_end                      : 1 ;  //     9     
	UINT32 en_g2_pic_end                      : 1 ;  //    10     
	UINT32 en_g3_pic_end                      : 1 ;  //    11     
	UINT32 en_g4_pic_end                      : 1 ;  //    12     
	UINT32 en_g5_pic_end                      : 1 ;  //    13     
	UINT32 en_g6_pic_end                      : 1 ;  //    14     
	UINT32 en_g7_pic_end                      : 1 ;  //    15     
	UINT32 en_osd                             : 1 ;  //    16     
} O18A0_CCO_INTR_EN_T;

/*-----------------------------------------------------------------------------
		0xc8024020L ctrl_dpath ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_pe_path_sel                    : 2 ;  //  1: 0     
	UINT32 cco_fb_mux                         : 2 ;  //  3: 2     
	UINT32                                    : 8 ;  // 11: 4     reserved
	UINT32 sel_src_dco_dfc                    : 1 ;  //    12     
	UINT32                                    : 1 ;  //    13     reserved
	UINT32 sel_osd_src_bosd1                  : 1 ;  //    14     
	UINT32 sel_osd_src_sosd                   : 1 ;  //    15     
	UINT32                                    : 1 ;  //    16     reserved
	UINT32 mon_sync_mv_off                    : 1 ;  //    17     
	UINT32 mon_sync_so_on                     : 1 ;  //    18     
	UINT32 unaligned_addr_en                  : 1 ;  //    19     
	UINT32 osd0_afbc_en                       : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 osd1_afbc_en                       : 1 ;  //    24     
	UINT32 cc_eo_hif_en                       : 1 ;  //    25     
	UINT32 cc_eo_hif_data                     : 1 ;  //    26     
	UINT32 cc_eo_hif_ready                    : 1 ;  //    27     
	UINT32 detour_en                          : 1 ;  //    28     
	UINT32 reg_sel_mif_cmd_dly                : 1 ;  //    29     
	UINT32 reg_sel_mif_axuser                 : 1 ;  //    30     
} O18A0_CCO_CTRL_DPATH_T;

/*-----------------------------------------------------------------------------
		0xc8024024L ctrl_spath ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cco_dpe_o_vs_sel                   : 3 ;  //  2: 0     
	UINT32 cco_dpe_o_hs_sel                   : 3 ;  //  5: 3     
	UINT32 cco_dpe_o_va_sel                   : 3 ;  //  8: 6     
	UINT32 cco_dpe_o_ha_sel                   : 3 ;  // 11: 9     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 ctrl_bosd_src_vs                   : 1 ;  //    16     
	UINT32 ctrl_bosd_src_hs                   : 1 ;  //    17     
	UINT32 ctrl_bosd_src_de                   : 1 ;  //    18     
	UINT32 ctrl_sosd_src_vs                   : 1 ;  //    19     
	UINT32 ctrl_sosd_src_hs                   : 1 ;  //    20     
	UINT32 ctrl_sosd_src_de                   : 1 ;  //    21     
	UINT32 osd_sync_gen_vs_in                 : 1 ;  //    22     
	UINT32 osd_sync_gen_hs_in                 : 1 ;  //    23     
	UINT32 osd_sync_gen_va_in                 : 1 ;  //    24     
	UINT32 osd_sync_gen_ha_in                 : 1 ;  //    25     
	UINT32 gcf_sync_mask_en                   : 1 ;  //    26     
	UINT32 mof_sync_mask_sel                  : 2 ;  // 28:27     
} O18A0_CCO_CTRL_SPATH_T;

/*-----------------------------------------------------------------------------
		0xc8024028L ctrl_3d_flag ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_flag_3d_lr_force_value         : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_flag_3d_lr_force_en            : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_flag_3d_force_value            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_flag_3d_force_en               : 1 ;  //    12     
} O18A0_CCO_CTRL_3D_FLAG_T;

/*-----------------------------------------------------------------------------
		0xc8024030L ctrl_bosd_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_disp_pulse_timer               : 28;  // 27: 0     
	UINT32 reg_disp_pulse_src_sel             : 1 ;  //    28     
	UINT32 reg_disp_pulse_src_inv             : 1 ;  //    29     
} O18A0_CCO_CTRL_BOSD_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8024034L ctrl_sosd_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_disp_pulse_timer               : 28;  // 27: 0     
	UINT32 reg_disp_pulse_src_sel             : 1 ;  //    28     
	UINT32 reg_disp_pulse_src_inv             : 1 ;  //    29     
} O18A0_CCO_CTRL_SOSD_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8024038L ctrl_auto_init_afbc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_afbc0_init_en                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_afbc0_auto_init_en             : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_afbc0_auto_init_src            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 idx_afbc0_pic_init_src             : 3 ;  // 14:12     
	UINT32 reg_afbc0_partial_ack_en           : 1 ;  //    15     
	UINT32 reg_afbc1_init_en                  : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_afbc1_auto_init_en             : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_afbc1_auto_init_src            : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 idx_afbc1_pic_init_src             : 3 ;  // 30:28     
	UINT32 reg_afbc1_partial_ack_en           : 1 ;  //    31     
} O18A0_CCO_CTRL_AUTO_INIT_AFBC_T;

/*-----------------------------------------------------------------------------
		0xc802403cL ctrl_auto_init_lencon ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lencon0_init_en                : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_lencon0_auto_init_en           : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_lencon0_auto_init_src          : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 idx_lencon0_pic_init_src           : 3 ;  // 14:12     
	UINT32 sel_lencon0_pic_init_src           : 1 ;  //    15     
	UINT32 reg_lencon1_init_en                : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_lencon1_auto_init_en           : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_lencon1_auto_init_src          : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 idx_lencon1_pic_init_src           : 3 ;  // 30:28     
	UINT32 sel_lencon1_pic_init_src           : 1 ;  //    31     
} O18A0_CCO_CTRL_AUTO_INIT_LENCON_T;

/*-----------------------------------------------------------------------------
		0xc8024044L ctrl_osd_init_2nd ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_init_2nd_en                   : 1 ;  //     0     
	UINT32 osd0_init_2nd_sel                  : 1 ;  //     1     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 osd1_init_2nd_en                   : 1 ;  //     4     
	UINT32 osd1_init_2nd_sel                  : 1 ;  //     5     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 osd2_init_2nd_en                   : 1 ;  //     8     
	UINT32 osd2_init_2nd_sel                  : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 osd3_init_2nd_en                   : 1 ;  //    12     
	UINT32 osd3_init_2nd_sel                  : 1 ;  //    13     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 osd4_init_2nd_en                   : 1 ;  //    16     
	UINT32 osd4_init_2nd_sel                  : 1 ;  //    17     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 osd5_init_2nd_en                   : 1 ;  //    20     
	UINT32 osd5_init_2nd_sel                  : 1 ;  //    21     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 osd6_init_2nd_en                   : 1 ;  //    24     
	UINT32 osd6_init_2nd_sel                  : 1 ;  //    25     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 osd7_init_2nd_en                   : 1 ;  //    28     
	UINT32 osd7_init_2nd_sel                  : 1 ;  //    29     
} O18A0_CCO_CTRL_OSD_INIT_2ND_T;

/*-----------------------------------------------------------------------------
		0xc8024060L ctrl_fbdc0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_osd0_1x2_bypass_en             : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_osd0_1x2_sel_id                : 4 ;  //  7: 4     
	UINT32 reg_fbdc0_ctrl_path                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_fbdc0_ctrl_comp                : 4 ;  // 15:12     
	UINT32 reg_fbdc0_ctrl_alpha               : 4 ;  // 19:16     
	UINT32                                    : 4 ;  // 23:20     reserved
	UINT32 reg_fbdc0_ctrl_dbg_sel             : 6 ;  // 29:24     
} O18A0_CCO_CTRL_FBDC0_T;

/*-----------------------------------------------------------------------------
		0xc8024064L info_fbdc0_dbg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32                                    : 24;  // 23: 0     reserved
	UINT32 info_fbdc0_dbg                     : 6 ;  // 29:24     
} O18A0_CCO_INFO_FBDC0_DBG_T;

/*-----------------------------------------------------------------------------
		0xc8024068L ctrl_fbdc1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_osd1_1x2_bypass_en             : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_osd1_1x2_sel_id                : 4 ;  //  7: 4     
	UINT32 reg_fbdc1_ctrl_path                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_fbdc1_ctrl_comp                : 4 ;  // 15:12     
	UINT32 reg_fbdc1_ctrl_alpha               : 4 ;  // 19:16     
	UINT32                                    : 4 ;  // 23:20     reserved
	UINT32 reg_fbdc1_ctrl_dbg_sel             : 6 ;  // 29:24     
} O18A0_CCO_CTRL_FBDC1_T;

/*-----------------------------------------------------------------------------
		0xc802406cL info_fbdc1_dbg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32                                    : 24;  // 23: 0     reserved
	UINT32 info_fbdc1_dbg                     : 6 ;  // 29:24     
} O18A0_CCO_INFO_FBDC1_DBG_T;

/*-----------------------------------------------------------------------------
		0xc8024070L ctrl_dly_disp_sync_param0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync                              : 16;  // 15: 0     
	UINT32 vfp                                : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM0_T;

/*-----------------------------------------------------------------------------
		0xc8024074L ctrl_dly_disp_sync_param1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 va                                 : 16;  // 15: 0     
	UINT32 vbp                                : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM1_T;

/*-----------------------------------------------------------------------------
		0xc8024078L ctrl_dly_disp_sync_param2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync                              : 16;  // 15: 0     
	UINT32 hfp                                : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM2_T;

/*-----------------------------------------------------------------------------
		0xc802407cL ctrl_dly_disp_sync_param3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha                                 : 16;  // 15: 0     
	UINT32 hbp                                : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM3_T;

/*-----------------------------------------------------------------------------
		0xc8024080L ctrl_dly_disp_sync_param4 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_start                         : 16;  // 15: 0     
	UINT32 sel_in_h_src                       : 1 ;  //    16     
	UINT32 sel_in_v_src                       : 1 ;  //    17     
	UINT32 sel_in_h_inv                       : 1 ;  //    18     
	UINT32 sel_in_v_inv                       : 1 ;  //    19     
	UINT32 sel_out_ha                         : 1 ;  //    20     
	UINT32 sel_out_va                         : 1 ;  //    21     
	UINT32 sel_out_hs                         : 1 ;  //    22     
	UINT32 sel_out_vs                         : 1 ;  //    23     
	UINT32 tp_update_hv_zero                  : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 en_cnt_reset_h_value               : 1 ;  //    28     
	UINT32 en_cnt_reset_v_value               : 1 ;  //    29     
	UINT32                                    : 1 ;  //    30     reserved
	UINT32 force_update                       : 1 ;  //    31     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM4_T;

/*-----------------------------------------------------------------------------
		0xc8024084L ctrl_dly_disp_sync_param5 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_dly                              : 16;  // 15: 0     
	UINT32 v_dly                              : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM5_T;

/*-----------------------------------------------------------------------------
		0xc8024088L ctrl_dly_disp_sync_param6 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reset_h_value                      : 16;  // 15: 0     
	UINT32 reset_v_value                      : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM6_T;

/*-----------------------------------------------------------------------------
		0xc802408cL ctrl_dly_disp_sync_param7 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 auto_delay_ha                      : 16;  // 15: 0     
	UINT32 auto_delay_va                      : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM7_T;

/*-----------------------------------------------------------------------------
		0xc8024090L ctrl_dly_disp_sync_param8 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 auto_delay_hs                      : 16;  // 15: 0     
	UINT32 auto_delay_vs                      : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM8_T;

/*-----------------------------------------------------------------------------
		0xc8024094L ctrl_dly_disp_sync_param9 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_cnt_threshold                 : 16;  // 15: 0     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM9_T;

/*-----------------------------------------------------------------------------
		0xc8024098L ctrl_dly_disp_sync_parama ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 auto_delay_hs                      : 16;  // 15: 0     
	UINT32 auto_delay_vs                      : 16;  // 31:16     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAMA_T;

/*-----------------------------------------------------------------------------
		0xc802409cL ctrl_dly_disp_sync_paramb ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_cnt_threshold                 : 16;  // 15: 0     
} O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAMB_T;

/*-----------------------------------------------------------------------------
		0xc80240a0L osd_sync_gen_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync                              : 16;  // 15: 0     
	UINT32 vfp                                : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xc80240a4L osd_sync_gen_ctrl1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 va                                 : 16;  // 15: 0     
	UINT32 vbp                                : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL1_T;

/*-----------------------------------------------------------------------------
		0xc80240a8L osd_sync_gen_ctrl2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync                              : 16;  // 15: 0     
	UINT32 hfp                                : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL2_T;

/*-----------------------------------------------------------------------------
		0xc80240acL osd_sync_gen_ctrl3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha                                 : 16;  // 15: 0     
	UINT32 hbp                                : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL3_T;

/*-----------------------------------------------------------------------------
		0xc80240b0L osd_sync_gen_ctrl4 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 prev_vsync                         : 16;  // 15: 0     
	UINT32 prev_vfp                           : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL4_T;

/*-----------------------------------------------------------------------------
		0xc80240b4L osd_sync_gen_ctrl5 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 prev_va                            : 16;  // 15: 0     
	UINT32 prev_vbp                           : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL5_T;

/*-----------------------------------------------------------------------------
		0xc80240b8L osd_sync_gen_ctrl6 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_start                         : 16;  // 15: 0     
	UINT32 sel_in_h_src                       : 1 ;  //    16     
	UINT32 sel_in_v_src                       : 1 ;  //    17     
	UINT32 sel_in_h_inv                       : 1 ;  //    18     
	UINT32 sel_in_v_inv                       : 1 ;  //    19     
	UINT32 sel_out_ha                         : 1 ;  //    20     
	UINT32 sel_out_va                         : 1 ;  //    21     
	UINT32 sel_out_hs                         : 1 ;  //    22     
	UINT32 sel_out_vs                         : 1 ;  //    23     
	UINT32 tp_update_hv_zero                  : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 cnt_reset_h_value_en               : 1 ;  //    28     
	UINT32 cnt_reset_v_value_en               : 1 ;  //    29     
	UINT32                                    : 1 ;  //    30     reserved
	UINT32 force_update                       : 1 ;  //    31     
} O18A0_CCO_OSD_SYNC_GEN_CTRL6_T;

/*-----------------------------------------------------------------------------
		0xc80240bcL osd_sync_gen_ctrl7 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 manual_h                           : 16;  // 15: 0     
	UINT32 manual_v                           : 16;  // 31:16     
} O18A0_CCO_OSD_SYNC_GEN_CTRL7_T;

/*-----------------------------------------------------------------------------
		0xc80240c0L pic_init_g0_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240c4L pic_init_g1_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240c8L pic_init_g2_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240ccL pic_init_g3_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240d0L pic_init_g4_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240d4L pic_init_g5_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G5_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240d8L pic_init_g6_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G6_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240dcL pic_init_g7_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_CCO_PIC_INIT_G7_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80240e4L dbg_timer_run ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_run                     : 24;  // 23: 0     
	UINT32 ctrl_timer_run                     : 8 ;  // 31:24     
} O18A0_CCO_DBG_TIMER_RUN_T;

/*-----------------------------------------------------------------------------
		0xc80240e8L dbg_timer_blk ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_blk                     : 24;  // 23: 0     
	UINT32 ctrl_timer_blk                     : 8 ;  // 31:24     
} O18A0_CCO_DBG_TIMER_BLK_T;

/*-----------------------------------------------------------------------------
		0xc80240ecL ctrl_monitor ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctrl_monitor                       : 32;  // 31: 0     
} O18A0_CCO_CTRL_MONITOR_T;

/*-----------------------------------------------------------------------------
		0xc80240f0L ctrl_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 b0_pic_end_en                      : 1 ;  //     0     
	UINT32 b1_pic_end_en                      : 1 ;  //     1     
	UINT32 b2_pic_end_en                      : 1 ;  //     2     
	UINT32 b3_pic_end_en                      : 1 ;  //     3     
	UINT32 b4_pic_end_en                      : 1 ;  //     4     
	UINT32 b5_pic_end_en                      : 1 ;  //     5     
	UINT32 b6_pic_end_en                      : 1 ;  //     6     
	UINT32 b7_pic_end_en                      : 1 ;  //     7     
	UINT32 b8_pic_end_en                      : 1 ;  //     8     
	UINT32 b9_pic_end_en                      : 1 ;  //     9     
	UINT32 b10_pic_end_en                     : 1 ;  //    10     
	UINT32 b11_pic_end_en                     : 1 ;  //    11     
	UINT32 b12_pic_end_en                     : 1 ;  //    12     
	UINT32 b13_pic_end_en                     : 1 ;  //    13     
	UINT32 b14_pic_end_en                     : 1 ;  //    14     
	UINT32 b15_pic_end_en                     : 1 ;  //    15     
	UINT32 pic_end_g0_force_en                : 1 ;  //    16     
	UINT32 pic_end_g1_force_en                : 1 ;  //    17     
	UINT32 pic_end_g2_force_en                : 1 ;  //    18     
	UINT32 pic_end_g3_force_en                : 1 ;  //    19     
	UINT32 pic_end_g4_force_en                : 1 ;  //    20     
	UINT32 pic_end_g5_force_en                : 1 ;  //    21     
	UINT32 pic_end_g6_force_en                : 1 ;  //    22     
	UINT32 pic_end_g7_force_en                : 1 ;  //    23     
	UINT32 pic_end_g0_force_value             : 1 ;  //    24     
	UINT32 pic_end_g1_force_value             : 1 ;  //    25     
	UINT32 pic_end_g2_force_value             : 1 ;  //    26     
	UINT32 pic_end_g3_force_value             : 1 ;  //    27     
	UINT32 pic_end_g4_force_value             : 1 ;  //    28     
	UINT32 pic_end_g5_force_value             : 1 ;  //    29     
	UINT32 pic_end_g6_force_value             : 1 ;  //    30     
	UINT32 pic_end_g7_force_value             : 1 ;  //    31     
} O18A0_CCO_CTRL_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80240f4L info_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end                         : 1 ;  //     0     
	UINT32 g1_pic_end                         : 1 ;  //     1     
	UINT32 g2_pic_end                         : 1 ;  //     2     
	UINT32 g3_pic_end                         : 1 ;  //     3     
	UINT32 g4_pic_end                         : 1 ;  //     4     
	UINT32 g5_pic_end                         : 1 ;  //     5     
	UINT32 g6_pic_end                         : 1 ;  //     6     
	UINT32 g7_pic_end                         : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_pic_turn                        : 1 ;  //    16     
	UINT32 g1_pic_turn                        : 1 ;  //    17     
	UINT32 g2_pic_turn                        : 1 ;  //    18     
	UINT32 g3_pic_turn                        : 1 ;  //    19     
	UINT32 g4_pic_turn                        : 1 ;  //    20     
	UINT32 g5_pic_turn                        : 1 ;  //    21     
	UINT32 g6_pic_turn                        : 1 ;  //    22     
	UINT32 g7_pic_turn                        : 1 ;  //    23     
} O18A0_CCO_INFO_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80240f8L ctrl_gpio ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ctrl_gpio                      : 32;  // 31: 0     
} O18A0_CCO_CTRL_GPIO_T;

/*-----------------------------------------------------------------------------
		0xc80240fcL ctrl_gmau ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                    : 8 ;  //  7: 0     
	UINT32 smx_aruser                         : 4 ;  // 11: 8     
	UINT32 smx_awuser                         : 4 ;  // 15:12     
	UINT32 ask_to_cnt                         : 10;  // 25:16     
} O18A0_CCO_CTRL_GMAU_T;

/*-----------------------------------------------------------------------------
		0xc8001000L pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_init                        : 1 ;  //     0     
	UINT32 g1_pic_init                        : 1 ;  //     1     
	UINT32 g2_pic_init                        : 1 ;  //     2     
	UINT32 g3_pic_init                        : 1 ;  //     3     
	UINT32 g4_pic_init                        : 1 ;  //     4     
	UINT32 g5_pic_init                        : 1 ;  //     5     
	UINT32 g6_pic_init                        : 1 ;  //     6     
	UINT32 g7_pic_init                        : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_init                       : 1 ;  //    16     
	UINT32 g1_auto_init                       : 1 ;  //    17     
	UINT32 g2_auto_init                       : 1 ;  //    18     
	UINT32 g3_auto_init                       : 1 ;  //    19     
	UINT32 g4_auto_init                       : 1 ;  //    20     
	UINT32 g5_auto_init                       : 1 ;  //    21     
	UINT32 g6_auto_init                       : 1 ;  //    22     
	UINT32 g7_auto_init                       : 1 ;  //    23     
} O18A0_IMX_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc8001004L pic_start ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_start                       : 1 ;  //     0     
	UINT32 g1_pic_start                       : 1 ;  //     1     
	UINT32 g2_pic_start                       : 1 ;  //     2     
	UINT32 g3_pic_start                       : 1 ;  //     3     
	UINT32 g4_pic_start                       : 1 ;  //     4     
	UINT32 g5_pic_start                       : 1 ;  //     5     
	UINT32 g6_pic_start                       : 1 ;  //     6     
	UINT32 g7_pic_start                       : 1 ;  //     7     
} O18A0_IMX_PIC_START_T;

/*-----------------------------------------------------------------------------
		0xc8001008L ctrl_auto_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_g0_auto_init               : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 idx_src_g1_auto_init               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_src_g2_auto_init               : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 idx_src_g3_auto_init               : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 idx_src_g4_auto_init               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 idx_src_g5_auto_init               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 idx_src_g6_auto_init               : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 idx_src_g7_auto_init               : 3 ;  // 30:28     
} O18A0_IMX_CTRL_AUTO_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800100cL ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse              : 3 ;  //  2: 0     
	UINT32 sel_src_i0_intr_pulse              : 1 ;  //     3     
	UINT32 idx_src_i1_intr_pulse              : 3 ;  //  6: 4     
	UINT32 sel_src_i1_intr_pulse              : 1 ;  //     7     
	UINT32 idx_src_i2_intr_pulse              : 3 ;  // 10: 8     
	UINT32 sel_src_i2_intr_pulse              : 1 ;  //    11     
	UINT32 idx_src_i3_intr_pulse              : 3 ;  // 14:12     
	UINT32 sel_src_i3_intr_pulse              : 1 ;  //    15     
	UINT32 idx_src_i4_intr_pulse              : 3 ;  // 18:16     
	UINT32 sel_src_i4_intr_pulse              : 1 ;  //    19     
	UINT32 idx_src_i5_intr_pulse              : 3 ;  // 22:20     
	UINT32 sel_src_i5_intr_pulse              : 1 ;  //    23     
	UINT32 idx_src_i6_intr_pulse              : 3 ;  // 26:24     
	UINT32 sel_src_i6_intr_pulse              : 1 ;  //    27     
	UINT32 idx_src_i7_intr_pulse              : 3 ;  // 30:28     
	UINT32 sel_src_i7_intr_pulse              : 1 ;  //    31     
} O18A0_IMX_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8001010L intr_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_i0_intr_pulse                 : 1 ;  //     0     
	UINT32 intr_i1_intr_pulse                 : 1 ;  //     1     
	UINT32 intr_i2_intr_pulse                 : 1 ;  //     2     
	UINT32 intr_i3_intr_pulse                 : 1 ;  //     3     
	UINT32 intr_i4_intr_pulse                 : 1 ;  //     4     
	UINT32 intr_i5_intr_pulse                 : 1 ;  //     5     
	UINT32 intr_i6_intr_pulse                 : 1 ;  //     6     
	UINT32 intr_i7_intr_pulse                 : 1 ;  //     7     
	UINT32 intr_g0_pic_end                    : 1 ;  //     8     
	UINT32 intr_g1_pic_end                    : 1 ;  //     9     
	UINT32 intr_g2_pic_end                    : 1 ;  //    10     
	UINT32 intr_g3_pic_end                    : 1 ;  //    11     
	UINT32 intr_g4_pic_end                    : 1 ;  //    12     
	UINT32 intr_g5_pic_end                    : 1 ;  //    13     
	UINT32 intr_g6_pic_end                    : 1 ;  //    14     
	UINT32 intr_g7_pic_end                    : 1 ;  //    15     
	UINT32                                    : 5 ;  // 20:16     reserved
	UINT32 intr_capture                       : 1 ;  //    21     
} O18A0_IMX_INTR_REG_T;

/*-----------------------------------------------------------------------------
		0xc8001014L intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                  : 1 ;  //     0     
	UINT32 mask_i1_src_pulse                  : 1 ;  //     1     
	UINT32 mask_i2_src_pulse                  : 1 ;  //     2     
	UINT32 mask_i3_src_pulse                  : 1 ;  //     3     
	UINT32 mask_i4_src_pulse                  : 1 ;  //     4     
	UINT32 mask_i5_src_pulse                  : 1 ;  //     5     
	UINT32 mask_i6_src_pulse                  : 1 ;  //     6     
	UINT32 mask_i7_src_pulse                  : 1 ;  //     7     
	UINT32 mask_g0_pic_end                    : 1 ;  //     8     
	UINT32 mask_g1_pic_end                    : 1 ;  //     9     
	UINT32 mask_g2_pic_end                    : 1 ;  //    10     
	UINT32 mask_g3_pic_end                    : 1 ;  //    11     
	UINT32 mask_g4_pic_end                    : 1 ;  //    12     
	UINT32 mask_g5_pic_end                    : 1 ;  //    13     
	UINT32 mask_g6_pic_end                    : 1 ;  //    14     
	UINT32 mask_g7_pic_end                    : 1 ;  //    15     
	UINT32                                    : 5 ;  // 20:16     reserved
	UINT32 mask_capture                       : 1 ;  //    21     
} O18A0_IMX_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xc8001018L intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                   : 1 ;  //     0     
	UINT32 mux_i1_src_pulse                   : 1 ;  //     1     
	UINT32 mux_i2_src_pulse                   : 1 ;  //     2     
	UINT32 mux_i3_src_pulse                   : 1 ;  //     3     
	UINT32 mux_i4_src_pulse                   : 1 ;  //     4     
	UINT32 mux_i5_src_pulse                   : 1 ;  //     5     
	UINT32 mux_i6_src_pulse                   : 1 ;  //     6     
	UINT32 mux_i7_src_pulse                   : 1 ;  //     7     
	UINT32 mux_g0_pic_end                     : 1 ;  //     8     
	UINT32 mux_g1_pic_end                     : 1 ;  //     9     
	UINT32 mux_g2_pic_end                     : 1 ;  //    10     
	UINT32 mux_g3_pic_end                     : 1 ;  //    11     
	UINT32 mux_g4_pic_end                     : 1 ;  //    12     
	UINT32 mux_g5_pic_end                     : 1 ;  //    13     
	UINT32 mux_g6_pic_end                     : 1 ;  //    14     
	UINT32 mux_g7_pic_end                     : 1 ;  //    15     
	UINT32 mux_capture                        : 1 ;  //    16     
} O18A0_IMX_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xc800101cL intr_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 en_i0_src_pulse                    : 1 ;  //     0     
	UINT32 en_i1_src_pulse                    : 1 ;  //     1     
	UINT32 en_i2_src_pulse                    : 1 ;  //     2     
	UINT32 en_i3_src_pulse                    : 1 ;  //     3     
	UINT32 en_i4_src_pulse                    : 1 ;  //     4     
	UINT32 en_i5_src_pulse                    : 1 ;  //     5     
	UINT32 en_i6_src_pulse                    : 1 ;  //     6     
	UINT32 en_i7_src_pulse                    : 1 ;  //     7     
	UINT32 en_g0_pic_end                      : 1 ;  //     8     
	UINT32 en_g1_pic_end                      : 1 ;  //     9     
	UINT32 en_g2_pic_end                      : 1 ;  //    10     
	UINT32 en_g3_pic_end                      : 1 ;  //    11     
	UINT32 en_g4_pic_end                      : 1 ;  //    12     
	UINT32 en_g5_pic_end                      : 1 ;  //    13     
	UINT32 en_g6_pic_end                      : 1 ;  //    14     
	UINT32 en_g7_pic_end                      : 1 ;  //    15     
	UINT32 en_capture                         : 1 ;  //    16     
} O18A0_IMX_INTR_EN_T;

/*-----------------------------------------------------------------------------
		0xc8001020L s0_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv_vs                    : 1 ;  //     8     
	UINT32 sel_sync_inv_hs                    : 1 ;  //     9     
	UINT32 sel_sync_vs                        : 1 ;  //    10     
	UINT32 sel_sync_hs                        : 1 ;  //    11     
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S0_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001024L s0_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S0_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001028L s0_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S0_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc800102cL s1_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv_vs                    : 1 ;  //     8     
	UINT32 sel_sync_inv_hs                    : 1 ;  //     9     
	UINT32 sel_sync_vs                        : 1 ;  //    10     
	UINT32 sel_sync_hs                        : 1 ;  //    11     
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S1_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001030L s1_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S1_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001034L s1_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S1_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001038L s2_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv                       : 1 ;  //     8     
	UINT32 sel_sync_vs                        : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S2_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc800103cL s2_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S2_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001040L s2_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S2_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001044L s3_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv                       : 1 ;  //     8     
	UINT32 sel_sync_vs                        : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S3_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001048L s3_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S3_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc800104cL s3_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S3_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001050L s4_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv                       : 1 ;  //     8     
	UINT32 sel_sync_vs                        : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S4_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001054L s4_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S4_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001058L s4_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S4_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc800105cL s5_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv                       : 1 ;  //     8     
	UINT32 sel_sync_vs                        : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S5_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001060L s5_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S5_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001064L s5_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S5_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001068L s6_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv                       : 1 ;  //     8     
	UINT32 sel_sync_vs                        : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S6_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc800106cL s6_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S6_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc8001070L s6_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S6_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001074L s7_src_sync_mux_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_sync_src                       : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 idx_sync_src                       : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 sel_sync_inv_vs                    : 1 ;  //     8     
	UINT32 sel_sync_inv_hs                    : 1 ;  //     9     
	UINT32 sel_sync_vs                        : 1 ;  //    10     
	UINT32 sel_sync_hs                        : 1 ;  //    11     
	UINT32 en_auto_src_pulse_half_va          : 1 ;  //    12     
	UINT32 src_fall_pos_sel                   : 3 ;  // 15:13     
	UINT32 src_pulse_pos_sel                  : 8 ;  // 23:16     
	UINT32                                    : 1 ;  //    24     reserved
	UINT32 en_use_edge_fal                    : 1 ;  //    25     
	UINT32 en_use_edge_ris                    : 1 ;  //    26     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_manual_delay_of_src_pulse       : 1 ;  //    28     
	UINT32 en_line_delay_of_src_pulse         : 1 ;  //    29     
	UINT32 en_trans_mask                      : 1 ;  //    30     
	UINT32 ignore_src_vs_fal                  : 1 ;  //    31     
} O18A0_IMX_S7_SRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001078L s7_src_sync_dly ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly                       : 28;  // 27: 0     
} O18A0_IMX_S7_SRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
		0xc800107cL s7_src_sync_dly_line ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_dly_line                  : 16;  // 15: 0     
	UINT32                                    : 12;  // 27:16     reserved
	UINT32 cnt_src_pulse                      : 4 ;  // 31:28     
} O18A0_IMX_S7_SRC_SYNC_DLY_LINE_T;

/*-----------------------------------------------------------------------------
		0xc8001080L mem0_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM0_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc8001084L mem1_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM1_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc8001088L mem2_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM2_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc800108cL mem3_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM3_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc8001090L mem4_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM4_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc8001094L mem5_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM5_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc8001098L mem6_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM6_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc800109cL mem7_sync_period ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                    : 32;  // 31: 0     
} O18A0_IMX_MEM7_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
		0xc80010a0L ctrl_src_dco_mfc ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_dco_mfc                    : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 sel_src_dco_mfc                    : 1 ;  //     4     
} O18A0_IMX_CTRL_SRC_DCO_MFC_T;

/*-----------------------------------------------------------------------------
		0xc80010a4L ctrl_imux_m0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_m0_src_cvi_mvi                 : 1 ;  //     0     
	UINT32 idx_m0_src_of_group                : 3 ;  //  3: 1     
	UINT32 sel_m0_eo_ch_inv                   : 1 ;  //     4     
	UINT32                                    : 2 ;  //  6: 5     reserved
	UINT32 sw_rst_m0                          : 1 ;  //     7     
	UINT32 en_m0_y_tpg_0                      : 1 ;  //     8     
	UINT32 sel_m0_y_tpg_type_0                : 2 ;  // 10: 9     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 en_m0_y_tpg_1                      : 1 ;  //    12     
	UINT32 sel_m0_y_tpg_type_1                : 2 ;  // 14:13     
} O18A0_IMX_CTRL_IMUX_M0_T;

/*-----------------------------------------------------------------------------
		0xc80010a8L ctrl_imux_s0_f0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_s0_src_cvi_mvi                 : 1 ;  //     0     
	UINT32 idx_s0_src_of_group                : 3 ;  //  3: 1     
	UINT32 sel_s0_eo_ch_inv                   : 1 ;  //     4     
	UINT32                                    : 2 ;  //  6: 5     reserved
	UINT32 sw_rst_s0                          : 1 ;  //     7     
	UINT32 en_s0_y_tpg_0                      : 1 ;  //     8     
	UINT32 sel_s0_y_tpg_type_0                : 2 ;  // 10: 9     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 en_s0_y_tpg_1                      : 1 ;  //    12     
	UINT32 sel_s0_y_tpg_type_1                : 2 ;  // 14:13     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 sel_f0_src_cvi_mvi                 : 1 ;  //    16     
	UINT32 idx_f0_src_of_group                : 3 ;  // 19:17     
	UINT32 sel_f0_eo_ch_inv                   : 1 ;  //    20     
	UINT32                                    : 2 ;  // 22:21     reserved
	UINT32 sw_rst_f0                          : 1 ;  //    23     
	UINT32 en_f0_y_tpg_0                      : 1 ;  //    24     
	UINT32 sel_f0_y_tpg_type_0                : 2 ;  // 26:25     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_f0_y_tpg_1                      : 1 ;  //    28     
	UINT32 sel_f0_y_tpg_type_1                : 2 ;  // 30:29     
} O18A0_IMX_CTRL_IMUX_S0_F0_T;

/*-----------------------------------------------------------------------------
		0xc80010acL ctrl_imux_c0_c1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_c0_src_cvi_mvi                 : 1 ;  //     0     
	UINT32 idx_c0_src_of_group                : 3 ;  //  3: 1     
	UINT32 sel_c0_eo_ch_inv                   : 1 ;  //     4     
	UINT32                                    : 2 ;  //  6: 5     reserved
	UINT32 sw_rst_c0                          : 1 ;  //     7     
	UINT32 en_c0_y_tpg_0                      : 1 ;  //     8     
	UINT32 sel_c0_y_tpg_type_0                : 2 ;  // 10: 9     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 en_c0_y_tpg_1                      : 1 ;  //    12     
	UINT32 sel_c0_y_tpg_type_1                : 2 ;  // 14:13     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 sel_c1_src_cvi_mvi                 : 1 ;  //    16     
	UINT32 idx_c1_src_of_group                : 3 ;  // 19:17     
	UINT32 sel_c1_eo_ch_inv                   : 1 ;  //    20     
	UINT32                                    : 2 ;  // 22:21     reserved
	UINT32 sw_rst_c1                          : 1 ;  //    23     
	UINT32 en_c1_y_tpg_0                      : 1 ;  //    24     
	UINT32 sel_c1_y_tpg_type_0                : 2 ;  // 26:25     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 en_c1_y_tpg_1                      : 1 ;  //    28     
	UINT32 sel_c1_y_tpg_type_1                : 2 ;  // 30:29     
} O18A0_IMX_CTRL_IMUX_C0_C1_T;

/*-----------------------------------------------------------------------------
		0xc80010b0L ctrl_block_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_reset_en_m0_y                  : 1 ;  //     0     
	UINT32 reg_reset_en_m0_c                  : 1 ;  //     1     
	UINT32 reg_reset_en_m1_y                  : 1 ;  //     2     
	UINT32 reg_reset_en_m1_c                  : 1 ;  //     3     
	UINT32 reg_reset_en_s0_y                  : 1 ;  //     4     
	UINT32 reg_reset_en_s0_c                  : 1 ;  //     5     
	UINT32 reg_reset_en_s1_y                  : 1 ;  //     6     
	UINT32 reg_reset_en_s1_c                  : 1 ;  //     7     
	UINT32 reg_sel_timer_reset_disp           : 3 ;  // 10: 8     
	UINT32 reg_sel_mif_cmd_dly                : 1 ;  //    11     
	UINT32 reg_src_sel_fd3                    : 3 ;  // 14:12     
	UINT32 reg_sel_mif_axuser                 : 1 ;  //    15     
	UINT32 smx0_aruser                        : 4 ;  // 19:16     
	UINT32 smx0_awuser                        : 4 ;  // 23:20     
	UINT32 smx1_aruser                        : 4 ;  // 27:24     
	UINT32 smx1_awuser                        : 4 ;  // 31:28     
} O18A0_IMX_CTRL_BLOCK_MUX_T;

/*-----------------------------------------------------------------------------
		0xc80010b4L ctrl_src_sync_level ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 imx_nd0_src_sync_level_sel         : 1 ;  //     0     
	UINT32 imx_nd1_src_sync_level_sel         : 1 ;  //     1     
	UINT32 imx_fme_src_sync_level_sel         : 1 ;  //     2     
	UINT32 imx_fmc_src_sync_level_sel         : 1 ;  //     3     
	UINT32 imx_sre_src_sync_level_sel         : 1 ;  //     4     
	UINT32 imx_gsc_src_sync_level_sel         : 1 ;  //     5     
	UINT32 imx_sub_src_sync_level_sel         : 1 ;  //     6     
	UINT32 imx_vsd_src_sync_level_sel         : 1 ;  //     7     
	UINT32 imx_mon_src_sync_level_sel         : 1 ;  //     8     
} O18A0_IMX_CTRL_SRC_SYNC_LEVEL_T;

/*-----------------------------------------------------------------------------
		0xc80010b8L ctrl_m0_y_level_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lvctrl_en                      : 1 ;  //     0     
	UINT32 reg_lvctrl_detour                  : 1 ;  //     1     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 level_offset                       : 10;  // 13: 4     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 level_center                       : 8 ;  // 23:16     
	UINT32 level_gain                         : 8 ;  // 31:24     
} O18A0_IMX_CTRL_M0_Y_LEVEL_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc80010c0L pic_init_g0_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010c4L pic_init_g1_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010c8L pic_init_g2_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010ccL pic_init_g3_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010d0L pic_init_g4_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010d4L pic_init_g5_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G5_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010d8L pic_init_g6_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G6_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010dcL pic_init_g7_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_IMX_PIC_INIT_G7_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80010e4L dbg_timer_run ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_run                     : 24;  // 23: 0     
	UINT32 ctrl_timer_run                     : 8 ;  // 31:24     
} O18A0_IMX_DBG_TIMER_RUN_T;

/*-----------------------------------------------------------------------------
		0xc80010e8L dbg_timer_blk ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_blk                     : 24;  // 23: 0     
	UINT32 ctrl_timer_blk                     : 8 ;  // 31:24     
} O18A0_IMX_DBG_TIMER_BLK_T;

/*-----------------------------------------------------------------------------
		0xc80010ecL ctrl_monitor ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctrl_monitor                       : 4 ;  //  3: 0     
} O18A0_IMX_CTRL_MONITOR_T;

/*-----------------------------------------------------------------------------
		0xc80010f0L ctrl_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end_en                      : 1 ;  //     0     
	UINT32 g1_pic_end_en                      : 1 ;  //     1     
	UINT32 g2_pic_end_en                      : 1 ;  //     2     
	UINT32 g3_pic_end_en                      : 1 ;  //     3     
	UINT32 g4_pic_end_en                      : 1 ;  //     4     
	UINT32 g5_pic_end_en                      : 1 ;  //     5     
	UINT32 g6_pic_end_en                      : 1 ;  //     6     
	UINT32 g7_pic_end_en                      : 1 ;  //     7     
	UINT32 b0_pic_end_en                      : 1 ;  //     8     
	UINT32 b1_pic_end_en                      : 1 ;  //     9     
	UINT32 b2_pic_end_en                      : 1 ;  //    10     
	UINT32 b3_pic_end_en                      : 1 ;  //    11     
	UINT32 b4_pic_end_en                      : 1 ;  //    12     
	UINT32 b5_pic_end_en                      : 1 ;  //    13     
	UINT32 b6_pic_end_en                      : 1 ;  //    14     
	UINT32 b7_pic_end_en                      : 1 ;  //    15     
	UINT32 pic_end_g0_force_en                : 1 ;  //    16     
	UINT32 pic_end_g1_force_en                : 1 ;  //    17     
	UINT32 pic_end_g2_force_en                : 1 ;  //    18     
	UINT32 pic_end_g3_force_en                : 1 ;  //    19     
	UINT32 pic_end_g4_force_en                : 1 ;  //    20     
	UINT32 pic_end_g5_force_en                : 1 ;  //    21     
	UINT32 pic_end_g6_force_en                : 1 ;  //    22     
	UINT32 pic_end_g7_force_en                : 1 ;  //    23     
	UINT32 pic_end_g0_force_value             : 1 ;  //    24     
	UINT32 pic_end_g1_force_value             : 1 ;  //    25     
	UINT32 pic_end_g2_force_value             : 1 ;  //    26     
	UINT32 pic_end_g3_force_value             : 1 ;  //    27     
	UINT32 pic_end_g4_force_value             : 1 ;  //    28     
	UINT32 pic_end_g5_force_value             : 1 ;  //    29     
	UINT32 pic_end_g6_force_value             : 1 ;  //    30     
	UINT32 pic_end_g7_force_value             : 1 ;  //    31     
} O18A0_IMX_CTRL_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80010f4L info_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end                         : 1 ;  //     0     
	UINT32 g1_pic_end                         : 1 ;  //     1     
	UINT32 g2_pic_end                         : 1 ;  //     2     
	UINT32 g3_pic_end                         : 1 ;  //     3     
	UINT32 g4_pic_end                         : 1 ;  //     4     
	UINT32 g5_pic_end                         : 1 ;  //     5     
	UINT32 g6_pic_end                         : 1 ;  //     6     
	UINT32 g7_pic_end                         : 1 ;  //     7     
	UINT32 b0_pic_end                         : 1 ;  //     8     
	UINT32 b1_pic_end                         : 1 ;  //     9     
	UINT32 b2_pic_end                         : 1 ;  //    10     
	UINT32 b3_pic_end                         : 1 ;  //    11     
	UINT32 b4_pic_end                         : 1 ;  //    12     
	UINT32 b5_pic_end                         : 1 ;  //    13     
	UINT32 b6_pic_end                         : 1 ;  //    14     
	UINT32 b7_pic_end                         : 1 ;  //    15     
	UINT32 g0_pic_turn                        : 1 ;  //    16     
	UINT32 g1_pic_turn                        : 1 ;  //    17     
	UINT32 g2_pic_turn                        : 1 ;  //    18     
	UINT32 g3_pic_turn                        : 1 ;  //    19     
	UINT32 g4_pic_turn                        : 1 ;  //    20     
	UINT32 g5_pic_turn                        : 1 ;  //    21     
	UINT32 g6_pic_turn                        : 1 ;  //    22     
	UINT32 g7_pic_turn                        : 1 ;  //    23     
} O18A0_IMX_INFO_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80010f8L ctrl_gpio ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rst_async_bridge_m0_y              : 1 ;  //     0     
	UINT32 rst_async_bridge_m0_c              : 1 ;  //     1     
	UINT32 rst_async_bridge_m1_y              : 1 ;  //     2     
	UINT32 rst_async_bridge_m1_c              : 1 ;  //     3     
	UINT32 rst_async_bridge_s0_y              : 1 ;  //     4     
	UINT32 rst_async_bridge_s0_c              : 1 ;  //     5     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_gate_tx_m0_y_en                : 1 ;  //     8     
	UINT32 reg_gate_tx_m0_y_dp_en             : 1 ;  //     9     
	UINT32 reg_gate_tx_m0_y_dp_sel            : 2 ;  // 11:10     
	UINT32 reg_gate_tx_m0_c_en                : 1 ;  //    12     
	UINT32 reg_gate_tx_m0_c_dp_en             : 1 ;  //    13     
	UINT32 reg_gate_tx_m0_c_dp_sel            : 2 ;  // 15:14     
	UINT32 reg_gate_tx_s0_y_en                : 1 ;  //    16     
	UINT32 reg_gate_tx_s0_y_dp_en             : 1 ;  //    17     
	UINT32 reg_gate_tx_s0_y_dp_sel            : 2 ;  // 19:18     
	UINT32 reg_gate_tx_s0_c_en                : 1 ;  //    20     
	UINT32 reg_gate_tx_s0_c_dp_en             : 1 ;  //    21     
	UINT32 reg_gate_tx_s0_c_dp_sel            : 2 ;  // 23:22     
	UINT32 fpga_input_vsync_inv               : 1 ;  //    24     
	UINT32 fpga_input_hsync_inv               : 1 ;  //    25     
	UINT32 reserved0                          : 1 ;  //    26     
	UINT32 reserved1                          : 1 ;  //    27     
	UINT32 cveclk_reset                       : 1 ;  //    28     
} O18A0_IMX_CTRL_GPIO_T;

/*-----------------------------------------------------------------------------
		0xc80010fcL ctrl_gmau ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt_r0                 : 4 ;  //  3: 0     
	UINT32 ask_cmd_dly_cnt_r1                 : 4 ;  //  7: 4     
	UINT32 ask_cmd_dly_cnt_w0                 : 4 ;  // 11: 8     
	UINT32 ask_cmd_dly_cnt_w1                 : 4 ;  // 15:12     
	UINT32 ask_to_cnt                         : 10;  // 25:16     
} O18A0_IMX_CTRL_GMAU_T;

/*-----------------------------------------------------------------------------
		0xc8004000L pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_init                        : 1 ;  //     0     
	UINT32 g1_pic_init                        : 1 ;  //     1     
	UINT32 g2_pic_init                        : 1 ;  //     2     
	UINT32 g3_pic_init                        : 1 ;  //     3     
	UINT32 g4_pic_init                        : 1 ;  //     4     
	UINT32 g5_pic_init                        : 1 ;  //     5     
	UINT32 g6_pic_init                        : 1 ;  //     6     
	UINT32 g7_pic_init                        : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_init                       : 1 ;  //    16     
	UINT32 g1_auto_init                       : 1 ;  //    17     
	UINT32 g2_auto_init                       : 1 ;  //    18     
	UINT32 g3_auto_init                       : 1 ;  //    19     
	UINT32 g4_auto_init                       : 1 ;  //    20     
	UINT32 g5_auto_init                       : 1 ;  //    21     
	UINT32 g6_auto_init                       : 1 ;  //    22     
	UINT32 g7_auto_init                       : 1 ;  //    23     
} O18A0_ND0_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc8004004L pic_start ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_start                       : 1 ;  //     0     
	UINT32 g1_pic_start                       : 1 ;  //     1     
	UINT32 g2_pic_start                       : 1 ;  //     2     
	UINT32 g3_pic_start                       : 1 ;  //     3     
	UINT32 g4_pic_start                       : 1 ;  //     4     
	UINT32 g5_pic_start                       : 1 ;  //     5     
	UINT32 g6_pic_start                       : 1 ;  //     6     
	UINT32 g7_pic_start                       : 1 ;  //     7     
} O18A0_ND0_PIC_START_T;

/*-----------------------------------------------------------------------------
		0xc8004008L ctrl_auto_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_g0_auto_init               : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 idx_src_g1_auto_init               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_src_g2_auto_init               : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 idx_src_g3_auto_init               : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 idx_src_g4_auto_init               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 idx_src_g5_auto_init               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 idx_src_g6_auto_init               : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 idx_src_g7_auto_init               : 3 ;  // 30:28     
} O18A0_ND0_CTRL_AUTO_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800400cL ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse              : 3 ;  //  2: 0     
	UINT32 sel_src_i0_intr_pulse              : 1 ;  //     3     
	UINT32 idx_src_i1_intr_pulse              : 3 ;  //  6: 4     
	UINT32 sel_src_i1_intr_pulse              : 1 ;  //     7     
	UINT32 idx_src_i2_intr_pulse              : 3 ;  // 10: 8     
	UINT32 sel_src_i2_intr_pulse              : 1 ;  //    11     
	UINT32 idx_src_i3_intr_pulse              : 3 ;  // 14:12     
	UINT32 sel_src_i3_intr_pulse              : 1 ;  //    15     
	UINT32 idx_src_i4_intr_pulse              : 3 ;  // 18:16     
	UINT32 sel_src_i4_intr_pulse              : 1 ;  //    19     
	UINT32 idx_src_i5_intr_pulse              : 3 ;  // 22:20     
	UINT32 sel_src_i5_intr_pulse              : 1 ;  //    23     
	UINT32 idx_src_i6_intr_pulse              : 3 ;  // 26:24     
	UINT32 sel_src_i6_intr_pulse              : 1 ;  //    27     
	UINT32 idx_src_i7_intr_pulse              : 3 ;  // 30:28     
	UINT32 sel_src_i7_intr_pulse              : 1 ;  //    31     
} O18A0_ND0_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8004010L intr_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_i0_intr_pulse                 : 1 ;  //     0     
	UINT32 intr_i1_intr_pulse                 : 1 ;  //     1     
	UINT32 intr_i2_intr_pulse                 : 1 ;  //     2     
	UINT32 intr_i3_intr_pulse                 : 1 ;  //     3     
	UINT32 intr_i4_intr_pulse                 : 1 ;  //     4     
	UINT32 intr_i5_intr_pulse                 : 1 ;  //     5     
	UINT32 intr_i6_intr_pulse                 : 1 ;  //     6     
	UINT32 intr_i7_intr_pulse                 : 1 ;  //     7     
	UINT32 intr_g0_pic_end                    : 1 ;  //     8     
	UINT32 intr_g1_pic_end                    : 1 ;  //     9     
	UINT32 intr_g2_pic_end                    : 1 ;  //    10     
	UINT32 intr_g3_pic_end                    : 1 ;  //    11     
	UINT32 intr_g4_pic_end                    : 1 ;  //    12     
	UINT32 intr_g5_pic_end                    : 1 ;  //    13     
	UINT32 intr_g6_pic_end                    : 1 ;  //    14     
	UINT32 intr_g7_pic_end                    : 1 ;  //    15     
	UINT32 intr_nd0                           : 1 ;  //    16     
} O18A0_ND0_INTR_REG_T;

/*-----------------------------------------------------------------------------
		0xc8004014L intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                  : 1 ;  //     0     
	UINT32 mask_i1_src_pulse                  : 1 ;  //     1     
	UINT32 mask_i2_src_pulse                  : 1 ;  //     2     
	UINT32 mask_i3_src_pulse                  : 1 ;  //     3     
	UINT32 mask_i4_src_pulse                  : 1 ;  //     4     
	UINT32 mask_i5_src_pulse                  : 1 ;  //     5     
	UINT32 mask_i6_src_pulse                  : 1 ;  //     6     
	UINT32 mask_i7_src_pulse                  : 1 ;  //     7     
	UINT32 mask_g0_pic_end                    : 1 ;  //     8     
	UINT32 mask_g1_pic_end                    : 1 ;  //     9     
	UINT32 mask_g2_pic_end                    : 1 ;  //    10     
	UINT32 mask_g3_pic_end                    : 1 ;  //    11     
	UINT32 mask_g4_pic_end                    : 1 ;  //    12     
	UINT32 mask_g5_pic_end                    : 1 ;  //    13     
	UINT32 mask_g6_pic_end                    : 1 ;  //    14     
	UINT32 mask_g7_pic_end                    : 1 ;  //    15     
	UINT32 mask_nd0                           : 1 ;  //    16     
} O18A0_ND0_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xc8004018L intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                   : 1 ;  //     0     
	UINT32 mux_i1_src_pulse                   : 1 ;  //     1     
	UINT32 mux_i2_src_pulse                   : 1 ;  //     2     
	UINT32 mux_i3_src_pulse                   : 1 ;  //     3     
	UINT32 mux_i4_src_pulse                   : 1 ;  //     4     
	UINT32 mux_i5_src_pulse                   : 1 ;  //     5     
	UINT32 mux_i6_src_pulse                   : 1 ;  //     6     
	UINT32 mux_i7_src_pulse                   : 1 ;  //     7     
	UINT32 mux_g0_pic_end                     : 1 ;  //     8     
	UINT32 mux_g1_pic_end                     : 1 ;  //     9     
	UINT32 mux_g2_pic_end                     : 1 ;  //    10     
	UINT32 mux_g3_pic_end                     : 1 ;  //    11     
	UINT32 mux_g4_pic_end                     : 1 ;  //    12     
	UINT32 mux_g5_pic_end                     : 1 ;  //    13     
	UINT32 mux_g6_pic_end                     : 1 ;  //    14     
	UINT32 mux_g7_pic_end                     : 1 ;  //    15     
	UINT32 mux_nd0                            : 1 ;  //    16     
} O18A0_ND0_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xc800401cL intr_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 en_i0_src_pulse                    : 1 ;  //     0     
	UINT32 en_i1_src_pulse                    : 1 ;  //     1     
	UINT32 en_i2_src_pulse                    : 1 ;  //     2     
	UINT32 en_i3_src_pulse                    : 1 ;  //     3     
	UINT32 en_i4_src_pulse                    : 1 ;  //     4     
	UINT32 en_i5_src_pulse                    : 1 ;  //     5     
	UINT32 en_i6_src_pulse                    : 1 ;  //     6     
	UINT32 en_i7_src_pulse                    : 1 ;  //     7     
	UINT32 en_g0_pic_end                      : 1 ;  //     8     
	UINT32 en_g1_pic_end                      : 1 ;  //     9     
	UINT32 en_g2_pic_end                      : 1 ;  //    10     
	UINT32 en_g3_pic_end                      : 1 ;  //    11     
	UINT32 en_g4_pic_end                      : 1 ;  //    12     
	UINT32 en_g5_pic_end                      : 1 ;  //    13     
	UINT32 en_g6_pic_end                      : 1 ;  //    14     
	UINT32 en_g7_pic_end                      : 1 ;  //    15     
	UINT32 en_nd0                             : 1 ;  //    16     
} O18A0_ND0_INTR_EN_T;

/*-----------------------------------------------------------------------------
		0xc80040b0L ctrl_block_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_path_reset_en_m1_y             : 1 ;  //     0     
	UINT32 reg_path_reset_en_m1_c             : 1 ;  //     1     
} O18A0_ND0_CTRL_BLOCK_MUX_T;

/*-----------------------------------------------------------------------------
		0xc80040c0L pic_init_g0_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040c4L pic_init_g1_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040c8L pic_init_g2_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040ccL pic_init_g3_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040d0L pic_init_g4_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040d4L pic_init_g5_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G5_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040d8L pic_init_g6_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G6_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040dcL pic_init_g7_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_ND0_PIC_INIT_G7_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80040e4L dbg_timer_run ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_run                     : 24;  // 23: 0     
	UINT32 ctrl_timer_run                     : 8 ;  // 31:24     
} O18A0_ND0_DBG_TIMER_RUN_T;

/*-----------------------------------------------------------------------------
		0xc80040e8L dbg_timer_blk ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_blk                     : 24;  // 23: 0     
	UINT32 ctrl_timer_blk                     : 8 ;  // 31:24     
} O18A0_ND0_DBG_TIMER_BLK_T;

/*-----------------------------------------------------------------------------
		0xc80040ecL ctrl_monitor ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctrl_monitor                       : 32;  // 31: 0     
} O18A0_ND0_CTRL_MONITOR_T;

/*-----------------------------------------------------------------------------
		0xc80040f0L ctrl_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end_en                      : 1 ;  //     0     
	UINT32 g1_pic_end_en                      : 1 ;  //     1     
	UINT32 g2_pic_end_en                      : 1 ;  //     2     
	UINT32 g3_pic_end_en                      : 1 ;  //     3     
	UINT32 g4_pic_end_en                      : 1 ;  //     4     
	UINT32 g5_pic_end_en                      : 1 ;  //     5     
	UINT32 g6_pic_end_en                      : 1 ;  //     6     
	UINT32 g7_pic_end_en                      : 1 ;  //     7     
	UINT32 b0_pic_end_en                      : 1 ;  //     8     
	UINT32 b1_pic_end_en                      : 1 ;  //     9     
	UINT32 b2_pic_end_en                      : 1 ;  //    10     
	UINT32 b3_pic_end_en                      : 1 ;  //    11     
	UINT32 b4_pic_end_en                      : 1 ;  //    12     
	UINT32 b5_pic_end_en                      : 1 ;  //    13     
	UINT32 b6_pic_end_en                      : 1 ;  //    14     
	UINT32 b7_pic_end_en                      : 1 ;  //    15     
	UINT32 pic_end_g0_force_en                : 1 ;  //    16     
	UINT32 pic_end_g1_force_en                : 1 ;  //    17     
	UINT32 pic_end_g2_force_en                : 1 ;  //    18     
	UINT32 pic_end_g3_force_en                : 1 ;  //    19     
	UINT32 pic_end_g4_force_en                : 1 ;  //    20     
	UINT32 pic_end_g5_force_en                : 1 ;  //    21     
	UINT32 pic_end_g6_force_en                : 1 ;  //    22     
	UINT32 pic_end_g7_force_en                : 1 ;  //    23     
	UINT32 pic_end_g0_force_value             : 1 ;  //    24     
	UINT32 pic_end_g1_force_value             : 1 ;  //    25     
	UINT32 pic_end_g2_force_value             : 1 ;  //    26     
	UINT32 pic_end_g3_force_value             : 1 ;  //    27     
	UINT32 pic_end_g4_force_value             : 1 ;  //    28     
	UINT32 pic_end_g5_force_value             : 1 ;  //    29     
	UINT32 pic_end_g6_force_value             : 1 ;  //    30     
	UINT32 pic_end_g7_force_value             : 1 ;  //    31     
} O18A0_ND0_CTRL_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80040f4L info_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end                         : 1 ;  //     0     
	UINT32 g1_pic_end                         : 1 ;  //     1     
	UINT32 g2_pic_end                         : 1 ;  //     2     
	UINT32 g3_pic_end                         : 1 ;  //     3     
	UINT32 g4_pic_end                         : 1 ;  //     4     
	UINT32 g5_pic_end                         : 1 ;  //     5     
	UINT32 g6_pic_end                         : 1 ;  //     6     
	UINT32 g7_pic_end                         : 1 ;  //     7     
	UINT32 b0_pic_end                         : 1 ;  //     8     
	UINT32 b1_pic_end                         : 1 ;  //     9     
	UINT32 b2_pic_end                         : 1 ;  //    10     
	UINT32 b3_pic_end                         : 1 ;  //    11     
	UINT32 b4_pic_end                         : 1 ;  //    12     
	UINT32 b5_pic_end                         : 1 ;  //    13     
	UINT32 b6_pic_end                         : 1 ;  //    14     
	UINT32 b7_pic_end                         : 1 ;  //    15     
	UINT32 g0_pic_turn                        : 1 ;  //    16     
	UINT32 g1_pic_turn                        : 1 ;  //    17     
	UINT32 g2_pic_turn                        : 1 ;  //    18     
	UINT32 g3_pic_turn                        : 1 ;  //    19     
	UINT32 g4_pic_turn                        : 1 ;  //    20     
	UINT32 g5_pic_turn                        : 1 ;  //    21     
	UINT32 g6_pic_turn                        : 1 ;  //    22     
	UINT32 g7_pic_turn                        : 1 ;  //    23     
} O18A0_ND0_INFO_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80040f8L ctrl_gpio ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rst_async_bridge_m0_y              : 1 ;  //     0     
	UINT32 rst_async_bridge_m0_c              : 1 ;  //     1     
	UINT32                                    : 14;  // 15: 2     reserved
	UINT32 mon_m0_y_en                        : 1 ;  //    16     
	UINT32 mon_m0_y_const                     : 1 ;  //    17     
	UINT32 mon_m0_c_en                        : 1 ;  //    18     
	UINT32 mon_m0_c_const                     : 1 ;  //    19     
} O18A0_ND0_CTRL_GPIO_T;

/*-----------------------------------------------------------------------------
		0xc80040fcL ctrl_gmau ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                    : 8 ;  //  7: 0     
	UINT32 smx_aruser                         : 4 ;  // 11: 8     
	UINT32 smx_awuser                         : 4 ;  // 15:12     
	UINT32 ask_to_cnt                         : 10;  // 25:16     
} O18A0_ND0_CTRL_GMAU_T;

/*-----------------------------------------------------------------------------
		0xc8006000L pic_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_init                        : 1 ;  //     0     
	UINT32 g1_pic_init                        : 1 ;  //     1     
	UINT32 g2_pic_init                        : 1 ;  //     2     
	UINT32 g3_pic_init                        : 1 ;  //     3     
	UINT32 g4_pic_init                        : 1 ;  //     4     
	UINT32 g5_pic_init                        : 1 ;  //     5     
	UINT32 g6_pic_init                        : 1 ;  //     6     
	UINT32 g7_pic_init                        : 1 ;  //     7     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 g0_auto_init                       : 1 ;  //    16     
	UINT32 g1_auto_init                       : 1 ;  //    17     
	UINT32 g2_auto_init                       : 1 ;  //    18     
	UINT32 g3_auto_init                       : 1 ;  //    19     
	UINT32 g4_auto_init                       : 1 ;  //    20     
	UINT32 g5_auto_init                       : 1 ;  //    21     
	UINT32 g6_auto_init                       : 1 ;  //    22     
	UINT32 g7_auto_init                       : 1 ;  //    23     
} O18A0_SUB_PIC_INIT_T;

/*-----------------------------------------------------------------------------
		0xc8006004L pic_start ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_start                       : 1 ;  //     0     
	UINT32 g1_pic_start                       : 1 ;  //     1     
	UINT32 g2_pic_start                       : 1 ;  //     2     
	UINT32 g3_pic_start                       : 1 ;  //     3     
	UINT32 g4_pic_start                       : 1 ;  //     4     
	UINT32 g5_pic_start                       : 1 ;  //     5     
	UINT32 g6_pic_start                       : 1 ;  //     6     
	UINT32 g7_pic_start                       : 1 ;  //     7     
} O18A0_SUB_PIC_START_T;

/*-----------------------------------------------------------------------------
		0xc8006008L ctrl_auto_init ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_g0_auto_init               : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 idx_src_g1_auto_init               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 idx_src_g2_auto_init               : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 idx_src_g3_auto_init               : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 idx_src_g4_auto_init               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 idx_src_g5_auto_init               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 idx_src_g6_auto_init               : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 idx_src_g7_auto_init               : 3 ;  // 30:28     
} O18A0_SUB_CTRL_AUTO_INIT_T;

/*-----------------------------------------------------------------------------
		0xc800600cL ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse              : 3 ;  //  2: 0     
	UINT32 sel_src_i0_intr_pulse              : 1 ;  //     3     
	UINT32 idx_src_i1_intr_pulse              : 3 ;  //  6: 4     
	UINT32 sel_src_i1_intr_pulse              : 1 ;  //     7     
	UINT32 idx_src_i2_intr_pulse              : 3 ;  // 10: 8     
	UINT32 sel_src_i2_intr_pulse              : 1 ;  //    11     
	UINT32 idx_src_i3_intr_pulse              : 3 ;  // 14:12     
	UINT32 sel_src_i3_intr_pulse              : 1 ;  //    15     
	UINT32 idx_src_i4_intr_pulse              : 3 ;  // 18:16     
	UINT32 sel_src_i4_intr_pulse              : 1 ;  //    19     
	UINT32 idx_src_i5_intr_pulse              : 3 ;  // 22:20     
	UINT32 sel_src_i5_intr_pulse              : 1 ;  //    23     
	UINT32 idx_src_i6_intr_pulse              : 3 ;  // 26:24     
	UINT32 sel_src_i6_intr_pulse              : 1 ;  //    27     
	UINT32 idx_src_i7_intr_pulse              : 3 ;  // 30:28     
	UINT32 sel_src_i7_intr_pulse              : 1 ;  //    31     
} O18A0_SUB_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8006010L intr_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_i0_intr_pulse                 : 1 ;  //     0     
	UINT32 intr_i1_intr_pulse                 : 1 ;  //     1     
	UINT32 intr_i2_intr_pulse                 : 1 ;  //     2     
	UINT32 intr_i3_intr_pulse                 : 1 ;  //     3     
	UINT32 intr_i4_intr_pulse                 : 1 ;  //     4     
	UINT32 intr_i5_intr_pulse                 : 1 ;  //     5     
	UINT32 intr_i6_intr_pulse                 : 1 ;  //     6     
	UINT32 intr_i7_intr_pulse                 : 1 ;  //     7     
	UINT32 intr_g0_pic_end                    : 1 ;  //     8     
	UINT32 intr_g1_pic_end                    : 1 ;  //     9     
	UINT32 intr_g2_pic_end                    : 1 ;  //    10     
	UINT32 intr_g3_pic_end                    : 1 ;  //    11     
	UINT32 intr_g4_pic_end                    : 1 ;  //    12     
	UINT32 intr_g5_pic_end                    : 1 ;  //    13     
	UINT32 intr_g6_pic_end                    : 1 ;  //    14     
	UINT32 intr_g7_pic_end                    : 1 ;  //    15     
	UINT32 intr_nds                           : 1 ;  //    16     
	UINT32 intr_cve                           : 1 ;  //    17     
	UINT32 intr_cve_va_fal                    : 1 ;  //    18     
	UINT32 intr_cve_va_ris                    : 1 ;  //    19     
} O18A0_SUB_INTR_REG_T;

/*-----------------------------------------------------------------------------
		0xc8006014L intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                  : 1 ;  //     0     
	UINT32 mask_i1_src_pulse                  : 1 ;  //     1     
	UINT32 mask_i2_src_pulse                  : 1 ;  //     2     
	UINT32 mask_i3_src_pulse                  : 1 ;  //     3     
	UINT32 mask_i4_src_pulse                  : 1 ;  //     4     
	UINT32 mask_i5_src_pulse                  : 1 ;  //     5     
	UINT32 mask_i6_src_pulse                  : 1 ;  //     6     
	UINT32 mask_i7_src_pulse                  : 1 ;  //     7     
	UINT32 mask_g0_pic_end                    : 1 ;  //     8     
	UINT32 mask_g1_pic_end                    : 1 ;  //     9     
	UINT32 mask_g2_pic_end                    : 1 ;  //    10     
	UINT32 mask_g3_pic_end                    : 1 ;  //    11     
	UINT32 mask_g4_pic_end                    : 1 ;  //    12     
	UINT32 mask_g5_pic_end                    : 1 ;  //    13     
	UINT32 mask_g6_pic_end                    : 1 ;  //    14     
	UINT32 mask_g7_pic_end                    : 1 ;  //    15     
	UINT32 mask_nds                           : 1 ;  //    16     
	UINT32                                    : 1 ;  //    17     reserved
	UINT32 mask_cve_va_fal                    : 1 ;  //    18     
	UINT32 mask_cve_va_ris                    : 1 ;  //    19     
} O18A0_SUB_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xc8006018L intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                   : 1 ;  //     0     
	UINT32 mux_i1_src_pulse                   : 1 ;  //     1     
	UINT32 mux_i2_src_pulse                   : 1 ;  //     2     
	UINT32 mux_i3_src_pulse                   : 1 ;  //     3     
	UINT32 mux_i4_src_pulse                   : 1 ;  //     4     
	UINT32 mux_i5_src_pulse                   : 1 ;  //     5     
	UINT32 mux_i6_src_pulse                   : 1 ;  //     6     
	UINT32 mux_i7_src_pulse                   : 1 ;  //     7     
	UINT32 mux_g0_pic_end                     : 1 ;  //     8     
	UINT32 mux_g1_pic_end                     : 1 ;  //     9     
	UINT32 mux_g2_pic_end                     : 1 ;  //    10     
	UINT32 mux_g3_pic_end                     : 1 ;  //    11     
	UINT32 mux_g4_pic_end                     : 1 ;  //    12     
	UINT32 mux_g5_pic_end                     : 1 ;  //    13     
	UINT32 mux_g6_pic_end                     : 1 ;  //    14     
	UINT32 mux_g7_pic_end                     : 1 ;  //    15     
	UINT32 mux_nds                            : 1 ;  //    16     
	UINT32                                    : 1 ;  //    17     reserved
	UINT32 mux_cve_va_fal                     : 1 ;  //    18     
	UINT32 mux_cve_va_ris                     : 1 ;  //    19     
} O18A0_SUB_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xc800601cL intr_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 en_i0_src_pulse                    : 1 ;  //     0     
	UINT32 en_i1_src_pulse                    : 1 ;  //     1     
	UINT32 en_i2_src_pulse                    : 1 ;  //     2     
	UINT32 en_i3_src_pulse                    : 1 ;  //     3     
	UINT32 en_i4_src_pulse                    : 1 ;  //     4     
	UINT32 en_i5_src_pulse                    : 1 ;  //     5     
	UINT32 en_i6_src_pulse                    : 1 ;  //     6     
	UINT32 en_i7_src_pulse                    : 1 ;  //     7     
	UINT32 en_g0_pic_end                      : 1 ;  //     8     
	UINT32 en_g1_pic_end                      : 1 ;  //     9     
	UINT32 en_g2_pic_end                      : 1 ;  //    10     
	UINT32 en_g3_pic_end                      : 1 ;  //    11     
	UINT32 en_g4_pic_end                      : 1 ;  //    12     
	UINT32 en_g5_pic_end                      : 1 ;  //    13     
	UINT32 en_g6_pic_end                      : 1 ;  //    14     
	UINT32 en_g7_pic_end                      : 1 ;  //    15     
	UINT32 en_nds                             : 1 ;  //    16     
	UINT32                                    : 1 ;  //    17     reserved
	UINT32 en_cve_va_fal                      : 1 ;  //    18     
	UINT32 en_cve_va_ris                      : 1 ;  //    19     
} O18A0_SUB_INTR_EN_T;

/*-----------------------------------------------------------------------------
		0xc8006020L ctrl_venc_if ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 venc0_vs                           : 1 ;  //     0     
	UINT32 venc1_vs                           : 1 ;  //     1     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 sel_venc0_vs                       : 1 ;  //     4     
	UINT32 sel_venc1_vs                       : 1 ;  //     5     
} O18A0_SUB_CTRL_VENC_IF_T;

/*-----------------------------------------------------------------------------
		0xc800602cL ctrl_dly_cve_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_cve_pulse                      : 32;  // 31: 0     
} O18A0_SUB_CTRL_DLY_CVE_PULSE_T;

/*-----------------------------------------------------------------------------
		0xc8006030L ctrl_cve_sync_param0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vertical_back_period               : 8 ;  //  7: 0     
	UINT32 vertical_sync_period               : 8 ;  // 15: 8     
	UINT32 vertical_front_period              : 8 ;  // 23:16     
	UINT32 vsync_polarity                     : 1 ;  //    24     
} O18A0_SUB_CTRL_CVE_SYNC_PARAM0_T;

/*-----------------------------------------------------------------------------
		0xc8006034L ctrl_cve_sync_param1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 horizontal_back_period             : 8 ;  //  7: 0     
	UINT32 horizontal_sync_period             : 8 ;  // 15: 8     
	UINT32 horizontal_front_period            : 8 ;  // 23:16     
	UINT32 hsync_polarity                     : 1 ;  //    24     
} O18A0_SUB_CTRL_CVE_SYNC_PARAM1_T;

/*-----------------------------------------------------------------------------
		0xc8006038L ctrl_cve_sync_param2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_hoffset1                         : 11;  // 10: 0     
	UINT32 v_hoffset0                         : 11;  // 21:11     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 field_id_polarity                  : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 force_update                       : 1 ;  //    28     
	UINT32 force_reset                        : 1 ;  //    29     
} O18A0_SUB_CTRL_CVE_SYNC_PARAM2_T;

/*-----------------------------------------------------------------------------
		0xc800603cL ctrl_cve_sync_param3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cve_sync_ha                        : 11;  // 10: 0     
	UINT32                                    : 5 ;  // 15:11     reserved
	UINT32 cve_sync_va                        : 11;  // 26:16     
} O18A0_SUB_CTRL_CVE_SYNC_PARAM3_T;

/*-----------------------------------------------------------------------------
		0xc80060c0L pic_init_g0_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060c4L pic_init_g1_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060c8L pic_init_g2_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060ccL pic_init_g3_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060d0L pic_init_g4_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060d4L pic_init_g5_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G5_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060d8L pic_init_g6_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G6_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060dcL pic_init_g7_timer ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_timer                     : 24;  // 23: 0     
	UINT32 start_interval_mode_en             : 1 ;  //    24     
	UINT32 start_interval_mode                : 3 ;  // 27:25     
	UINT32 pic_init_width_mode_en             : 1 ;  //    28     
	UINT32 pic_init_width_mode                : 2 ;  // 30:29     
	UINT32 wait_pic_end_en                    : 1 ;  //    31     
} O18A0_SUB_PIC_INIT_G7_TIMER_T;

/*-----------------------------------------------------------------------------
		0xc80060e4L dbg_timer_run ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_run                     : 24;  // 23: 0     
	UINT32 ctrl_timer_run                     : 8 ;  // 31:24     
} O18A0_SUB_DBG_TIMER_RUN_T;

/*-----------------------------------------------------------------------------
		0xc80060e8L dbg_timer_blk ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 info_timer_blk                     : 24;  // 23: 0     
	UINT32 ctrl_timer_blk                     : 8 ;  // 31:24     
} O18A0_SUB_DBG_TIMER_BLK_T;

/*-----------------------------------------------------------------------------
		0xc80060ecL ctrl_monitor ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctrl_monitor                       : 32;  // 31: 0     
} O18A0_SUB_CTRL_MONITOR_T;

/*-----------------------------------------------------------------------------
		0xc80060f0L ctrl_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end_en                      : 1 ;  //     0     
	UINT32 g1_pic_end_en                      : 1 ;  //     1     
	UINT32 g2_pic_end_en                      : 1 ;  //     2     
	UINT32 g3_pic_end_en                      : 1 ;  //     3     
	UINT32 g4_pic_end_en                      : 1 ;  //     4     
	UINT32 g5_pic_end_en                      : 1 ;  //     5     
	UINT32 g6_pic_end_en                      : 1 ;  //     6     
	UINT32 g7_pic_end_en                      : 1 ;  //     7     
	UINT32 b0_pic_end_en                      : 1 ;  //     8     
	UINT32 b1_pic_end_en                      : 1 ;  //     9     
	UINT32 b2_pic_end_en                      : 1 ;  //    10     
	UINT32 b3_pic_end_en                      : 1 ;  //    11     
	UINT32 b4_pic_end_en                      : 1 ;  //    12     
	UINT32 b5_pic_end_en                      : 1 ;  //    13     
	UINT32 b6_pic_end_en                      : 1 ;  //    14     
	UINT32 b7_pic_end_en                      : 1 ;  //    15     
	UINT32 pic_end_g0_force_en                : 1 ;  //    16     
	UINT32 pic_end_g1_force_en                : 1 ;  //    17     
	UINT32 pic_end_g2_force_en                : 1 ;  //    18     
	UINT32 pic_end_g3_force_en                : 1 ;  //    19     
	UINT32 pic_end_g4_force_en                : 1 ;  //    20     
	UINT32 pic_end_g5_force_en                : 1 ;  //    21     
	UINT32 pic_end_g6_force_en                : 1 ;  //    22     
	UINT32 pic_end_g7_force_en                : 1 ;  //    23     
	UINT32 pic_end_g0_force_value             : 1 ;  //    24     
	UINT32 pic_end_g1_force_value             : 1 ;  //    25     
	UINT32 pic_end_g2_force_value             : 1 ;  //    26     
	UINT32 pic_end_g3_force_value             : 1 ;  //    27     
	UINT32 pic_end_g4_force_value             : 1 ;  //    28     
	UINT32 pic_end_g5_force_value             : 1 ;  //    29     
	UINT32 pic_end_g6_force_value             : 1 ;  //    30     
	UINT32 pic_end_g7_force_value             : 1 ;  //    31     
} O18A0_SUB_CTRL_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80060f4L info_pic_end ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 g0_pic_end                         : 1 ;  //     0     
	UINT32 g1_pic_end                         : 1 ;  //     1     
	UINT32 g2_pic_end                         : 1 ;  //     2     
	UINT32 g3_pic_end                         : 1 ;  //     3     
	UINT32 g4_pic_end                         : 1 ;  //     4     
	UINT32 g5_pic_end                         : 1 ;  //     5     
	UINT32 g6_pic_end                         : 1 ;  //     6     
	UINT32 g7_pic_end                         : 1 ;  //     7     
	UINT32 b0_pic_end                         : 1 ;  //     8     
	UINT32 b1_pic_end                         : 1 ;  //     9     
	UINT32 b2_pic_end                         : 1 ;  //    10     
	UINT32 b3_pic_end                         : 1 ;  //    11     
	UINT32 b4_pic_end                         : 1 ;  //    12     
	UINT32 b5_pic_end                         : 1 ;  //    13     
	UINT32 b6_pic_end                         : 1 ;  //    14     
	UINT32 b7_pic_end                         : 1 ;  //    15     
	UINT32 g0_pic_turn                        : 1 ;  //    16     
	UINT32 g1_pic_turn                        : 1 ;  //    17     
	UINT32 g2_pic_turn                        : 1 ;  //    18     
	UINT32 g3_pic_turn                        : 1 ;  //    19     
	UINT32 g4_pic_turn                        : 1 ;  //    20     
	UINT32 g5_pic_turn                        : 1 ;  //    21     
	UINT32 g6_pic_turn                        : 1 ;  //    22     
	UINT32 g7_pic_turn                        : 1 ;  //    23     
} O18A0_SUB_INFO_PIC_END_T;

/*-----------------------------------------------------------------------------
		0xc80060f8L ctrl_gpio ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ctrl_gpio                      : 32;  // 31: 0     
} O18A0_SUB_CTRL_GPIO_T;

/*-----------------------------------------------------------------------------
		0xc80060fcL ctrl_gmau ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                    : 8 ;  //  7: 0     
	UINT32 smx_aruser                         : 4 ;  // 11: 8     
	UINT32 smx_awuser                         : 4 ;  // 15:12     
	UINT32 ask_to_cnt                         : 10;  // 25:16     
} O18A0_SUB_CTRL_GMAU_T;

/*-----------------------------------------------------------------------------
		0xC900500C ctrl_intr_pulse ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 idx_src_i0_intr_pulse            :3;	//2:0	//Source Selection of INTR_I0_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i0_intr_pulse            :1;	//3 //Source Selection of INTR_I0_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i1_intr_pulse            :3;	//6:4	//Source Selection of INTR_I1_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i1_intr_pulse            :1;	//7 //Source Selection of INTR_I1_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i2_intr_pulse            :3;	//10:8	//Source Selection of INTR_I2_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i2_intr_pulse            :1;	//11 //Source Selection of INTR_I2_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i3_intr_pulse            :3;	//14:12	//Source Selection of INTR_I3_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i3_intr_pulse            :1;	//15 //Source Selection of INTR_I3_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i4_intr_pulse            :3;	//18:16	//Source Selection of INTR_I4_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i4_intr_pulse            :1;	//19 //Source Selection of INTR_I4_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i5_intr_pulse            :3;	//22:20	//Source Selection of INTR_I5_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i5_intr_pulse            :1;	//23 //Source Selection of INTR_I5_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i6_intr_pulse            :3;	//26:24	//Source Selection of INTR_I6_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i6_intr_pulse            :1;	//27 //Source Selection of INTR_I6_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i7_intr_pulse            :3;	//30:28	//Source Selection of INTR_I7_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i7_intr_pulse            :1;	//31 //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
} O18A0_HDR_CTRL_INTR_PULSE_T;

/*-----------------------------------------------------------------------------
		0xC9005014 intr_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                :1;	//0 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i1_src_pulse                :1;	//1 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i2_src_pulse                :1;	//2 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i3_src_pulse                :1;	//3 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i4_src_pulse                :1;	//4 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i5_src_pulse                :1;	//5 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i6_src_pulse                :1;	//6 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i7_src_pulse                :1;	//7 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g0_pic_end                  :1;	//8 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g1_pic_end                  :1;	//9 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g2_pic_end                  :1;	//10 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g3_pic_end                  :1;	//11 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g4_pic_end                  :1;	//12 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g5_pic_end                  :1;	//13 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g6_pic_end                  :1;	//14 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g7_pic_end                  :1;	//15 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_pic_end_intr            :1;	//16 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_md_ready_intr           :1;	//17 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_bl_va_f_intr      :1;	//18 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_bl_va_r_intr      :1;	//19 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_crc_intr                    :1;	//20 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_el_va_r_intr      :1;	//21 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_el_va_f_intr      :1;	//22 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_out_va_r_intr     :1;	//23 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_out_va_f_intr     :1;	//24 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_in_va_r_intr         :1;	//25 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_in_va_f_intr         :1;	//26 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_out_va_r_intr        :1;	//27 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_out_va_f_intr        :1;	//28 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_tone_pic_end_intr       :1;	//29 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_threed_pic_end_intr     :1;	//30 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dolby_intr                  :1;	//31 //interrupt mask	0  = unmask	1 := mask
}O18A0_HDR_CTRL_INTR_MASK_T;

/*-----------------------------------------------------------------------------
		0xC9005018 intr_mux ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_i0_src_pulse                 :1;	//0 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i1_src_pulse                 :1;	//1 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i2_src_pulse                 :1;	//2 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i3_src_pulse                 :1;	//3 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i4_src_pulse                 :1;	//4 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i5_src_pulse                 :1;	//5 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i6_src_pulse                 :1;	//6 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i7_src_pulse                 :1;	//7 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g0_pic_end                   :1;	//8 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g1_pic_end                   :1;	//9 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g2_pic_end                   :1;	//10 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g3_pic_end                   :1;	//11 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g4_pic_end                   :1;	//12 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g5_pic_end                   :1;	//13 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g6_pic_end                   :1;	//14 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g7_pic_end                   :1;	//15 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_pic_end_intr             :1;	//16 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_md_ready_intr            :1;	//17 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_bl_va_f_intr       :1;	//18 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_bl_va_r_intr       :1;	//19 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_crc_intr                     :1;	//20 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_el_va_r_intr       :1;	//21 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_el_va_f_intr       :1;	//22 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_out_va_r_intr      :1;	//23 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_dolby_out_va_f_intr      :1;	//24 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_lg_in_va_r_intr          :1;	//25 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_lg_in_va_f_intr          :1;	//26 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_lg_out_va_r_intr         :1;	//27 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_lg_out_va_f_intr         :1;	//28 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_tone_pic_end_intr        :1;	//29 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_hdr_threed_pic_end_intr      :1;	//30 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dolby_intr                   :1;	//31 //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
}O18A0_HDR_CTRL_INTR_MUX_T;

/*-----------------------------------------------------------------------------
		0xC9005050 intr_cpu_reg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 i0_src_pulse                :1;	//0 //interrupt mask	0  = unmask	1 := mask
	UINT32 i1_src_pulse                :1;	//1 //interrupt mask	0  = unmask	1 := mask
	UINT32 i2_src_pulse                :1;	//2 //interrupt mask	0  = unmask	1 := mask
	UINT32 i3_src_pulse                :1;	//3 //interrupt mask	0  = unmask	1 := mask
	UINT32 i4_src_pulse                :1;	//4 //interrupt mask	0  = unmask	1 := mask
	UINT32 i5_src_pulse                :1;	//5 //interrupt mask	0  = unmask	1 := mask
	UINT32 i6_src_pulse                :1;	//6 //interrupt mask	0  = unmask	1 := mask
	UINT32 i7_src_pulse                :1;	//7 //interrupt mask	0  = unmask	1 := mask
	UINT32 g0_pic_end                  :1;	//8 //interrupt mask	0  = unmask	1 := mask
	UINT32 g1_pic_end                  :1;	//9 //interrupt mask	0  = unmask	1 := mask
	UINT32 g2_pic_end                  :1;	//10 //interrupt mask	0  = unmask	1 := mask
	UINT32 g3_pic_end                  :1;	//11 //interrupt mask	0  = unmask	1 := mask
	UINT32 g4_pic_end                  :1;	//12 //interrupt mask	0  = unmask	1 := mask
	UINT32 g5_pic_end                  :1;	//13 //interrupt mask	0  = unmask	1 := mask
	UINT32 g6_pic_end                  :1;	//14 //interrupt mask	0  = unmask	1 := mask
	UINT32 g7_pic_end                  :1;	//15 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_pic_end_intr            :1;	//16 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_md_ready_intr           :1;	//17 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_bl_va_f_intr      :1;	//18 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_bl_va_r_intr      :1;	//19 //interrupt mask	0  = unmask	1 := mask
	UINT32 eserved                         :1;	//20 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_el_va_r_intr      :1;	//21 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_el_va_f_intr      :1;	//22 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_out_va_r_intr     :1;	//23 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_dolby_out_va_f_intr     :1;	//24 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_lg_in_va_r_intr         :1;	//25 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_lg_in_va_f_intr         :1;	//26 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_lg_out_va_r_intr        :1;	//27 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_lg_out_va_f_intr        :1;	//28 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_tone_pic_end_intr       :1;	//29 //interrupt mask	0  = unmask	1 := mask
	UINT32 hdr_threed_pic_end_intr     :1;	//30 //interrupt mask	0  = unmask	1 := mask
	UINT32 dolby_intr                  :1;	//31 //interrupt mask	0  = unmask	1 := mask
}O18A0_HDR_CTRL_INTR_CPU_REG_T;

/*-----------------------------------------------------------------------------
		0xC9005054 intr_cpu_mask ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_i0_src_pulse                :1;	//0 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i1_src_pulse                :1;	//1 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i2_src_pulse                :1;	//2 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i3_src_pulse                :1;	//3 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i4_src_pulse                :1;	//4 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i5_src_pulse                :1;	//5 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i6_src_pulse                :1;	//6 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i7_src_pulse                :1;	//7 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g0_pic_end                  :1;	//8 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g1_pic_end                  :1;	//9 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g2_pic_end                  :1;	//10 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g3_pic_end                  :1;	//11 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g4_pic_end                  :1;	//12 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g5_pic_end                  :1;	//13 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g6_pic_end                  :1;	//14 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g7_pic_end                  :1;	//15 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_pic_end_intr            :1;	//16 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_md_ready_intr           :1;	//17 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_bl_va_f_intr      :1;	//18 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_bl_va_r_intr      :1;	//19 //interrupt mask	0  = unmask	1 := mask
	UINT32 reserved                         :1;	//20 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_el_va_r_intr      :1;	//21 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_el_va_f_intr      :1;	//22 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_out_va_r_intr     :1;	//23 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_dolby_out_va_f_intr     :1;	//24 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_in_va_r_intr         :1;	//25 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_in_va_f_intr         :1;	//26 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_out_va_r_intr        :1;	//27 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_lg_out_va_f_intr        :1;	//28 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_tone_pic_end_intr       :1;	//29 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_hdr_threed_pic_end_intr     :1;	//30 //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dolby_intr                  :1;	//31 //interrupt mask	0  = unmask	1 := mask
}O18A0_HDR_CTRL_INTR_CPU_MASK_T;


typedef struct
{ 
	O18A0_CVC_PIC_INIT_T                              pic_init;	//0x0000
	O18A0_CVC_PIC_START_T                             pic_start;	//0x0004
	O18A0_CVC_CTRL_AUTO_INIT_T                        ctrl_auto_init;	//0x0008
	O18A0_CVC_CTRL_INTR_PULSE_T                       ctrl_intr_pulse;	//0x000C
	O18A0_CVC_INTR_REG_T                              intr_reg;	//0x0010
	O18A0_CVC_INTR_MASK_T                             intr_mask;	//0x0014
	O18A0_CVC_INTR_MUX_T                              intr_mux;	//0x0018
	O18A0_CVC_INTR_EN_T                               intr_en;	//0x001C
	UINT32                                            reserved8[12];	//0x20-0x4c
	O18A0_CVC_INFO_HDMI0_T                            info_hdmi0;	//0x0050
	O18A0_CVC_INFO_HDMI1_T                            info_hdmi1;	//0x0054
	O18A0_CVC_INFO_HDMI2_T                            info_hdmi2;	//0x0058
	O18A0_CVC_INFO_HDMI3_T                            info_hdmi3;	//0x005C
	O18A0_CVC_INFO_HDMI4_T                            info_hdmi4;	//0x0060
	O18A0_CVC_INTR_MASK_HDMI_T                        intr_mask_hdmi;	//0x0064
	UINT32                                            reserved14_2;	//0x68-0x6c
	O18A0_CVC_INFO_CVI0_T                             info_cvi0;	//0x0070
	O18A0_CVC_INFO_CVI1_T                             info_cvi1;	//0x0074
	O18A0_CVC_INFO_CVI2_T                             info_cvi2;	//0x0078
	O18A0_CVC_INFO_CVI3_T                             info_cvi3;	//0x007C
	O18A0_CVC_CTRL_BLOCK_T                            ctrl_block;	//0x0080
	O18A0_CVC_PG_CVE_CTRL_T                           pg_cve_ctrl;	//0x0084
	O18A0_CVC_PG_CVE_PHASE_INCR_T                     pg_cve_phase_incr;	//0x0088
	O18A0_CVC_HDMI_FBC_CTRL_T                         hdmi_fbc_ctrl;	//0x008C
	O18A0_CVC_SUB_BUS_AXI_FLUSH_T                     sub_bus_axi_flush;	//0x0090
	O18A0_CVC_CVI_INTR_MUX_SEL_T                      cvi_intr_mux_sel;	//0x0094
	UINT32                                            reserved24[10];	//0x98-0xbc
	O18A0_CVC_PIC_INIT_G0_TIMER_T                     pic_init_g0_timer;	//0x00C0
	O18A0_CVC_PIC_INIT_G1_TIMER_T                     pic_init_g1_timer;	//0x00C4
	O18A0_CVC_PIC_INIT_G2_TIMER_T                     pic_init_g2_timer;	//0x00C8
	O18A0_CVC_PIC_INIT_G3_TIMER_T                     pic_init_g3_timer;	//0x00CC
	O18A0_CVC_PIC_INIT_G4_TIMER_T                     pic_init_g4_timer;	//0x00D0
	O18A0_CVC_PIC_INIT_G5_TIMER_T                     pic_init_g5_timer;	//0x00D4
	O18A0_CVC_PIC_INIT_G6_TIMER_T                     pic_init_g6_timer;	//0x00D8
	O18A0_CVC_PIC_INIT_G7_TIMER_T                     pic_init_g7_timer;	//0x00DC
	UINT32                                            reserved32;	//0xe0
	O18A0_CVC_DBG_TIMER_RUN_T                         dbg_timer_run;	//0x00E4
	O18A0_CVC_DBG_TIMER_BLK_T                         dbg_timer_blk;	//0x00E8
	O18A0_CVC_CTRL_MONITOR_T                          ctrl_monitor;	//0x00EC
	O18A0_CVC_CTRL_PIC_END_T                          ctrl_pic_end;	//0x00F0
	O18A0_CVC_INFO_PIC_END_T                          info_pic_end;	//0x00F4
	O18A0_CVC_CTRL_GPIO_T                             ctrl_gpio;	//0x00F8
	O18A0_CVC_CTRL_AXI_USER_T                         ctrl_axi_user;	//0x00FC
}DE_CVC_REG_O18A0_T;

typedef struct {
	O18A0_VSD_PIC_INIT_T               	pic_init;                     //0xc800b000L
	O18A0_VSD_PIC_START_T              	pic_start;                    //0xc800b004L
	O18A0_VSD_CTRL_AUTO_INIT_T         	ctrl_auto_init;               //0xc800b008L
	O18A0_VSD_CTRL_INTR_PULSE_T        	ctrl_intr_pulse;              //0xc800b00cL
	O18A0_VSD_INTR_REG_T               	intr_reg;                     //0xc800b010L
	O18A0_VSD_INTR_MASK_T              	intr_mask;                    //0xc800b014L
	O18A0_VSD_INTR_MUX_T               	intr_mux;                     //0xc800b018L
	O18A0_VSD_INTR_EN_T                	intr_en;                      //0xc800b01cL
	O18A0_VSD_CTRL_SYNC_GEN_MV0_T      	ctrl_sync_gen_mv0;            //0xc800b020L
	O18A0_VSD_CTRL_SYNC_GEN_MV1_T      	ctrl_sync_gen_mv1;            //0xc800b024L
	O18A0_VSD_CTRL_SYNC_GEN_MV2_T      	ctrl_sync_gen_mv2;            //0xc800b028L
	O18A0_VSD_CTRL_SYNC_GEN_MV3_T      	ctrl_sync_gen_mv3;            //0xc800b02cL
	O18A0_VSD_CTRL_SYNC_GEN_MV4_T      	ctrl_sync_gen_mv4;            //0xc800b030L
	O18A0_VSD_CTRL_SYNC_GEN_MV5_T      	ctrl_sync_gen_mv5;            //0xc800b034L
	O18A0_VSD_CTRL_SYNC_GEN_MV6_T      	ctrl_sync_gen_mv6;            //0xc800b038L
	O18A0_VSD_CTRL_SYNC_GEN_MV7_T      	ctrl_sync_gen_mv7;            //0xc800b03cL
	UINT32                             	reserved00[8];                //0xc800b040L~0xc800b05cL
	O18A0_VSD_CTRL_SYNC_GEN_SB0_T      	ctrl_sync_gen_sb0;            //0xc800b060L
	O18A0_VSD_CTRL_SYNC_GEN_SB1_T      	ctrl_sync_gen_sb1;            //0xc800b064L
	O18A0_VSD_CTRL_SYNC_GEN_SB2_T      	ctrl_sync_gen_sb2;            //0xc800b068L
	O18A0_VSD_CTRL_SYNC_GEN_SB3_T      	ctrl_sync_gen_sb3;            //0xc800b06cL
	O18A0_VSD_CTRL_SYNC_GEN_SB4_T      	ctrl_sync_gen_sb4;            //0xc800b070L
	O18A0_VSD_CTRL_SYNC_GEN_SB5_T      	ctrl_sync_gen_sb5;            //0xc800b074L
	O18A0_VSD_CTRL_SYNC_GEN_SB6_T      	ctrl_sync_gen_sb6;            //0xc800b078L
	O18A0_VSD_CTRL_SYNC_GEN_SB7_T      	ctrl_sync_gen_sb7;            //0xc800b07cL
	O18A0_VSD_INFO_MV_DCO_MFC_T        	info_mv_dco_mfc;              //0xc800b080L
	O18A0_VSD_INFO_MV_DCO_DFC_T        	info_mv_dco_dfc;              //0xc800b084L
	O18A0_VSD_INFO_MV_DCO_DFLC_T       	info_mv_dco_dflc;             //0xc800b088L
	O18A0_VSD_CTRL_DCO_NUM_T           	ctrl_dco_num;                 //0xc800b08cL
	O18A0_VSD_CTRL_DCO_FCW_T           	ctrl_dco_fcw;                 //0xc800b090L
	O18A0_VSD_INFO_SB_DCO_MFC_T        	info_sb_dco_mfc;              //0xc800b094L
	O18A0_VSD_INFO_SB_DCO_DFC_T        	info_sb_dco_dfc;              //0xc800b098L
	O18A0_VSD_INFO_SB_DCO_DFLC_T       	info_sb_dco_dflc;             //0xc800b09cL
	O18A0_VSD_CTRL_SR_PIC_INIT_T       	ctrl_sr_pic_init;             //0xc800b0a0L
	O18A0_VSD_PIC_INIT_SR_TIMER_T      	pic_init_sr_timer;            //0xc800b0a4L
	UINT32                             	reserved01_2;                //0xc800b0a8L~0xc800b0acL
	O18A0_VSD_CTRL_BLOCK_T             	ctrl_block;                   //0xc800b0b0L
	UINT32                             	reserved02[3];                //0xc800b0b4L~0xc800b0bcL
	O18A0_VSD_PIC_INIT_G0_TIMER_T      	pic_init_g0_timer;            //0xc800b0c0L
	O18A0_VSD_PIC_INIT_G1_TIMER_T      	pic_init_g1_timer;            //0xc800b0c4L
	O18A0_VSD_PIC_INIT_G2_TIMER_T      	pic_init_g2_timer;            //0xc800b0c8L
	O18A0_VSD_PIC_INIT_G3_TIMER_T      	pic_init_g3_timer;            //0xc800b0ccL
	O18A0_VSD_PIC_INIT_G4_TIMER_T      	pic_init_g4_timer;            //0xc800b0d0L
	O18A0_VSD_PIC_INIT_G5_TIMER_T      	pic_init_g5_timer;            //0xc800b0d4L
	O18A0_VSD_PIC_INIT_G6_TIMER_T      	pic_init_g6_timer;            //0xc800b0d8L
	O18A0_VSD_PIC_INIT_G7_TIMER_T      	pic_init_g7_timer;            //0xc800b0dcL
	UINT32                             	reserved03;                   //0xc800b0e0L
	O18A0_VSD_DBG_TIMER_RUN_T          	dbg_timer_run;                //0xc800b0e4L
	O18A0_VSD_DBG_TIMER_BLK_T          	dbg_timer_blk;                //0xc800b0e8L
	O18A0_VSD_CTRL_MONITOR_T           	ctrl_monitor;                 //0xc800b0ecL
	O18A0_VSD_CTRL_PIC_END_T           	ctrl_pic_end;                 //0xc800b0f0L
	O18A0_VSD_INFO_PIC_END_T           	info_pic_end;                 //0xc800b0f4L
	O18A0_VSD_CTRL_GPIO_T              	ctrl_gpio;                    //0xc800b0f8L
	O18A0_VSD_CTRL_GMAU_T              	ctrl_gmau;                    //0xc800b0fcL
} DE_VSD_REG_O18A0_T;

typedef struct {
	O18A0_CCO_PIC_INIT_T               	pic_init;                     //0xc8024000L
	O18A0_CCO_PIC_START_T              	pic_start;                    //0xc8024004L
	O18A0_CCO_CTRL_AUTO_INIT_T         	ctrl_auto_init;               //0xc8024008L
	O18A0_CCO_CTRL_INTR_PULSE_T        	ctrl_intr_pulse;              //0xc802400cL
	O18A0_CCO_INTR_REG_T               	intr_reg;                     //0xc8024010L
	O18A0_CCO_INTR_MASK_T              	intr_mask;                    //0xc8024014L
	O18A0_CCO_INTR_MUX_T               	intr_mux;                     //0xc8024018L
	O18A0_CCO_INTR_EN_T                	intr_en;                      //0xc802401cL
	O18A0_CCO_CTRL_DPATH_T             	ctrl_dpath;                   //0xc8024020L
	O18A0_CCO_CTRL_SPATH_T             	ctrl_spath;                   //0xc8024024L
	O18A0_CCO_CTRL_3D_FLAG_T           	ctrl_3d_flag;                 //0xc8024028L
	UINT32                             	reserved00;                   //0xc802402cL
	O18A0_CCO_CTRL_BOSD_PULSE_T        	ctrl_bosd_pulse;              //0xc8024030L
	O18A0_CCO_CTRL_SOSD_PULSE_T        	ctrl_sosd_pulse;              //0xc8024034L
	O18A0_CCO_CTRL_AUTO_INIT_AFBC_T    	ctrl_auto_init_afbc;          //0xc8024038L
	O18A0_CCO_CTRL_AUTO_INIT_LENCON_T  	ctrl_auto_init_lencon;        //0xc802403cL
	UINT32                             	reserved01;                   //0xc8024040L
	O18A0_CCO_CTRL_OSD_INIT_2ND_T      	ctrl_osd_init_2nd;            //0xc8024044L
	UINT32                             	reserved02[6];                //0xc8024048L~0xc802405cL
	O18A0_CCO_CTRL_FBDC0_T             	ctrl_fbdc0;                   //0xc8024060L
	O18A0_CCO_INFO_FBDC0_DBG_T         	info_fbdc0_dbg;               //0xc8024064L
	O18A0_CCO_CTRL_FBDC1_T             	ctrl_fbdc1;                   //0xc8024068L
	O18A0_CCO_INFO_FBDC1_DBG_T         	info_fbdc1_dbg;               //0xc802406cL
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM0_T	ctrl_dly_disp_sync_param0;    //0xc8024070L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM1_T	ctrl_dly_disp_sync_param1;    //0xc8024074L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM2_T	ctrl_dly_disp_sync_param2;    //0xc8024078L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM3_T	ctrl_dly_disp_sync_param3;    //0xc802407cL
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM4_T	ctrl_dly_disp_sync_param4;    //0xc8024080L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM5_T	ctrl_dly_disp_sync_param5;    //0xc8024084L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM6_T	ctrl_dly_disp_sync_param6;    //0xc8024088L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM7_T	ctrl_dly_disp_sync_param7;    //0xc802408cL
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM8_T	ctrl_dly_disp_sync_param8;    //0xc8024090L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAM9_T	ctrl_dly_disp_sync_param9;    //0xc8024094L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAMA_T	ctrl_dly_disp_sync_parama;    //0xc8024098L
	O18A0_CCO_CTRL_DLY_DISP_SYNC_PARAMB_T	ctrl_dly_disp_sync_paramb;    //0xc802409cL
	O18A0_CCO_OSD_SYNC_GEN_CTRL0_T     	osd_sync_gen_ctrl0;           //0xc80240a0L
	O18A0_CCO_OSD_SYNC_GEN_CTRL1_T     	osd_sync_gen_ctrl1;           //0xc80240a4L
	O18A0_CCO_OSD_SYNC_GEN_CTRL2_T     	osd_sync_gen_ctrl2;           //0xc80240a8L
	O18A0_CCO_OSD_SYNC_GEN_CTRL3_T     	osd_sync_gen_ctrl3;           //0xc80240acL
	O18A0_CCO_OSD_SYNC_GEN_CTRL4_T     	osd_sync_gen_ctrl4;           //0xc80240b0L
	O18A0_CCO_OSD_SYNC_GEN_CTRL5_T     	osd_sync_gen_ctrl5;           //0xc80240b4L
	O18A0_CCO_OSD_SYNC_GEN_CTRL6_T     	osd_sync_gen_ctrl6;           //0xc80240b8L
	O18A0_CCO_OSD_SYNC_GEN_CTRL7_T     	osd_sync_gen_ctrl7;           //0xc80240bcL
	O18A0_CCO_PIC_INIT_G0_TIMER_T      	pic_init_g0_timer;            //0xc80240c0L
	O18A0_CCO_PIC_INIT_G1_TIMER_T      	pic_init_g1_timer;            //0xc80240c4L
	O18A0_CCO_PIC_INIT_G2_TIMER_T      	pic_init_g2_timer;            //0xc80240c8L
	O18A0_CCO_PIC_INIT_G3_TIMER_T      	pic_init_g3_timer;            //0xc80240ccL
	O18A0_CCO_PIC_INIT_G4_TIMER_T      	pic_init_g4_timer;            //0xc80240d0L
	O18A0_CCO_PIC_INIT_G5_TIMER_T      	pic_init_g5_timer;            //0xc80240d4L
	O18A0_CCO_PIC_INIT_G6_TIMER_T      	pic_init_g6_timer;            //0xc80240d8L
	O18A0_CCO_PIC_INIT_G7_TIMER_T      	pic_init_g7_timer;            //0xc80240dcL
	UINT32                             	reserved03;                   //0xc80240e0L
	O18A0_CCO_DBG_TIMER_RUN_T          	dbg_timer_run;                //0xc80240e4L
	O18A0_CCO_DBG_TIMER_BLK_T          	dbg_timer_blk;                //0xc80240e8L
	O18A0_CCO_CTRL_MONITOR_T           	ctrl_monitor;                 //0xc80240ecL
	O18A0_CCO_CTRL_PIC_END_T           	ctrl_pic_end;                 //0xc80240f0L
	O18A0_CCO_INFO_PIC_END_T           	info_pic_end;                 //0xc80240f4L
	O18A0_CCO_CTRL_GPIO_T              	ctrl_gpio;                    //0xc80240f8L
	O18A0_CCO_CTRL_GMAU_T              	ctrl_gmau;                    //0xc80240fcL
} DE_CCO_REG_O18A0_T;

typedef struct {
	O18A0_IMX_PIC_INIT_T               	pic_init;                     //0xc8001000L
	O18A0_IMX_PIC_START_T              	pic_start;                    //0xc8001004L
	O18A0_IMX_CTRL_AUTO_INIT_T         	ctrl_auto_init;               //0xc8001008L
	O18A0_IMX_CTRL_INTR_PULSE_T        	ctrl_intr_pulse;              //0xc800100cL
	O18A0_IMX_INTR_REG_T               	intr_reg;                     //0xc8001010L
	O18A0_IMX_INTR_MASK_T              	intr_mask;                    //0xc8001014L
	O18A0_IMX_INTR_MUX_T               	intr_mux;                     //0xc8001018L
	O18A0_IMX_INTR_EN_T                	intr_en;                      //0xc800101cL
	O18A0_IMX_S0_SRC_SYNC_MUX_CTRL_T   	s0_src_sync_mux_ctrl;         //0xc8001020L
	O18A0_IMX_S0_SRC_SYNC_DLY_T        	s0_src_sync_dly;              //0xc8001024L
	O18A0_IMX_S0_SRC_SYNC_DLY_LINE_T   	s0_src_sync_dly_line;         //0xc8001028L
	O18A0_IMX_S1_SRC_SYNC_MUX_CTRL_T   	s1_src_sync_mux_ctrl;         //0xc800102cL
	O18A0_IMX_S1_SRC_SYNC_DLY_T        	s1_src_sync_dly;              //0xc8001030L
	O18A0_IMX_S1_SRC_SYNC_DLY_LINE_T   	s1_src_sync_dly_line;         //0xc8001034L
	O18A0_IMX_S2_SRC_SYNC_MUX_CTRL_T   	s2_src_sync_mux_ctrl;         //0xc8001038L
	O18A0_IMX_S2_SRC_SYNC_DLY_T        	s2_src_sync_dly;              //0xc800103cL
	O18A0_IMX_S2_SRC_SYNC_DLY_LINE_T   	s2_src_sync_dly_line;         //0xc8001040L
	O18A0_IMX_S3_SRC_SYNC_MUX_CTRL_T   	s3_src_sync_mux_ctrl;         //0xc8001044L
	O18A0_IMX_S3_SRC_SYNC_DLY_T        	s3_src_sync_dly;              //0xc8001048L
	O18A0_IMX_S3_SRC_SYNC_DLY_LINE_T   	s3_src_sync_dly_line;         //0xc800104cL
	O18A0_IMX_S4_SRC_SYNC_MUX_CTRL_T   	s4_src_sync_mux_ctrl;         //0xc8001050L
	O18A0_IMX_S4_SRC_SYNC_DLY_T        	s4_src_sync_dly;              //0xc8001054L
	O18A0_IMX_S4_SRC_SYNC_DLY_LINE_T   	s4_src_sync_dly_line;         //0xc8001058L
	O18A0_IMX_S5_SRC_SYNC_MUX_CTRL_T   	s5_src_sync_mux_ctrl;         //0xc800105cL
	O18A0_IMX_S5_SRC_SYNC_DLY_T        	s5_src_sync_dly;              //0xc8001060L
	O18A0_IMX_S5_SRC_SYNC_DLY_LINE_T   	s5_src_sync_dly_line;         //0xc8001064L
	O18A0_IMX_S6_SRC_SYNC_MUX_CTRL_T   	s6_src_sync_mux_ctrl;         //0xc8001068L
	O18A0_IMX_S6_SRC_SYNC_DLY_T        	s6_src_sync_dly;              //0xc800106cL
	O18A0_IMX_S6_SRC_SYNC_DLY_LINE_T   	s6_src_sync_dly_line;         //0xc8001070L
	O18A0_IMX_S7_SRC_SYNC_MUX_CTRL_T   	s7_src_sync_mux_ctrl;         //0xc8001074L
	O18A0_IMX_S7_SRC_SYNC_DLY_T        	s7_src_sync_dly;              //0xc8001078L
	O18A0_IMX_S7_SRC_SYNC_DLY_LINE_T   	s7_src_sync_dly_line;         //0xc800107cL
	O18A0_IMX_MEM0_SYNC_PERIOD_T       	mem0_sync_period;             //0xc8001080L
	O18A0_IMX_MEM1_SYNC_PERIOD_T       	mem1_sync_period;             //0xc8001084L
	O18A0_IMX_MEM2_SYNC_PERIOD_T       	mem2_sync_period;             //0xc8001088L
	O18A0_IMX_MEM3_SYNC_PERIOD_T       	mem3_sync_period;             //0xc800108cL
	O18A0_IMX_MEM4_SYNC_PERIOD_T       	mem4_sync_period;             //0xc8001090L
	O18A0_IMX_MEM5_SYNC_PERIOD_T       	mem5_sync_period;             //0xc8001094L
	O18A0_IMX_MEM6_SYNC_PERIOD_T       	mem6_sync_period;             //0xc8001098L
	O18A0_IMX_MEM7_SYNC_PERIOD_T       	mem7_sync_period;             //0xc800109cL
	O18A0_IMX_CTRL_SRC_DCO_MFC_T       	ctrl_src_dco_mfc;             //0xc80010a0L
	O18A0_IMX_CTRL_IMUX_M0_T           	ctrl_imux_m0;                 //0xc80010a4L
	O18A0_IMX_CTRL_IMUX_S0_F0_T        	ctrl_imux_s0_f0;              //0xc80010a8L
	O18A0_IMX_CTRL_IMUX_C0_C1_T        	ctrl_imux_c0_c1;              //0xc80010acL
	O18A0_IMX_CTRL_BLOCK_MUX_T         	ctrl_block_mux;               //0xc80010b0L
	O18A0_IMX_CTRL_SRC_SYNC_LEVEL_T    	ctrl_src_sync_level;          //0xc80010b4L
	O18A0_IMX_CTRL_M0_Y_LEVEL_CTRL_T   	ctrl_m0_y_level_ctrl;         //0xc80010b8L
	UINT32                             	reserved00;                   //0xc80010bcL
	O18A0_IMX_PIC_INIT_G0_TIMER_T      	pic_init_g0_timer;            //0xc80010c0L
	O18A0_IMX_PIC_INIT_G1_TIMER_T      	pic_init_g1_timer;            //0xc80010c4L
	O18A0_IMX_PIC_INIT_G2_TIMER_T      	pic_init_g2_timer;            //0xc80010c8L
	O18A0_IMX_PIC_INIT_G3_TIMER_T      	pic_init_g3_timer;            //0xc80010ccL
	O18A0_IMX_PIC_INIT_G4_TIMER_T      	pic_init_g4_timer;            //0xc80010d0L
	O18A0_IMX_PIC_INIT_G5_TIMER_T      	pic_init_g5_timer;            //0xc80010d4L
	O18A0_IMX_PIC_INIT_G6_TIMER_T      	pic_init_g6_timer;            //0xc80010d8L
	O18A0_IMX_PIC_INIT_G7_TIMER_T      	pic_init_g7_timer;            //0xc80010dcL
	UINT32                             	reserved01;                   //0xc80010e0L
	O18A0_IMX_DBG_TIMER_RUN_T          	dbg_timer_run;                //0xc80010e4L
	O18A0_IMX_DBG_TIMER_BLK_T          	dbg_timer_blk;                //0xc80010e8L
	O18A0_IMX_CTRL_MONITOR_T           	ctrl_monitor;                 //0xc80010ecL
	O18A0_IMX_CTRL_PIC_END_T           	ctrl_pic_end;                 //0xc80010f0L
	O18A0_IMX_INFO_PIC_END_T           	info_pic_end;                 //0xc80010f4L
	O18A0_IMX_CTRL_GPIO_T              	ctrl_gpio;                    //0xc80010f8L
	O18A0_IMX_CTRL_GMAU_T              	ctrl_gmau;                    //0xc80010fcL
} DE_IMX_REG_O18A0_T;

typedef struct {
	O18A0_ND0_PIC_INIT_T               	pic_init;                     //0xc8004000L
	O18A0_ND0_PIC_START_T              	pic_start;                    //0xc8004004L
	O18A0_ND0_CTRL_AUTO_INIT_T         	ctrl_auto_init;               //0xc8004008L
	O18A0_ND0_CTRL_INTR_PULSE_T        	ctrl_intr_pulse;              //0xc800400cL
	O18A0_ND0_INTR_REG_T               	intr_reg;                     //0xc8004010L
	O18A0_ND0_INTR_MASK_T              	intr_mask;                    //0xc8004014L
	O18A0_ND0_INTR_MUX_T               	intr_mux;                     //0xc8004018L
	O18A0_ND0_INTR_EN_T                	intr_en;                      //0xc800401cL
	UINT32                             	reserved00[36];               //0xc8004020L~0xc80040acL
	O18A0_ND0_CTRL_BLOCK_MUX_T         	ctrl_block_mux;               //0xc80040b0L
	UINT32                             	reserved01[3];                //0xc80040b4L~0xc80040bcL
	O18A0_ND0_PIC_INIT_G0_TIMER_T      	pic_init_g0_timer;            //0xc80040c0L
	O18A0_ND0_PIC_INIT_G1_TIMER_T      	pic_init_g1_timer;            //0xc80040c4L
	O18A0_ND0_PIC_INIT_G2_TIMER_T      	pic_init_g2_timer;            //0xc80040c8L
	O18A0_ND0_PIC_INIT_G3_TIMER_T      	pic_init_g3_timer;            //0xc80040ccL
	O18A0_ND0_PIC_INIT_G4_TIMER_T      	pic_init_g4_timer;            //0xc80040d0L
	O18A0_ND0_PIC_INIT_G5_TIMER_T      	pic_init_g5_timer;            //0xc80040d4L
	O18A0_ND0_PIC_INIT_G6_TIMER_T      	pic_init_g6_timer;            //0xc80040d8L
	O18A0_ND0_PIC_INIT_G7_TIMER_T      	pic_init_g7_timer;            //0xc80040dcL
	UINT32                             	reserved02;                   //0xc80040e0L
	O18A0_ND0_DBG_TIMER_RUN_T          	dbg_timer_run;                //0xc80040e4L
	O18A0_ND0_DBG_TIMER_BLK_T          	dbg_timer_blk;                //0xc80040e8L
	O18A0_ND0_CTRL_MONITOR_T           	ctrl_monitor;                 //0xc80040ecL
	O18A0_ND0_CTRL_PIC_END_T           	ctrl_pic_end;                 //0xc80040f0L
	O18A0_ND0_INFO_PIC_END_T           	info_pic_end;                 //0xc80040f4L
	O18A0_ND0_CTRL_GPIO_T              	ctrl_gpio;                    //0xc80040f8L
	O18A0_ND0_CTRL_GMAU_T              	ctrl_gmau;                    //0xc80040fcL
} DE_ND0_REG_O18A0_T;

typedef struct {
	O18A0_SUB_PIC_INIT_T               	pic_init;                     //0xc8006000L
	O18A0_SUB_PIC_START_T              	pic_start;                    //0xc8006004L
	O18A0_SUB_CTRL_AUTO_INIT_T         	ctrl_auto_init;               //0xc8006008L
	O18A0_SUB_CTRL_INTR_PULSE_T        	ctrl_intr_pulse;              //0xc800600cL
	O18A0_SUB_INTR_REG_T               	intr_reg;                     //0xc8006010L
	O18A0_SUB_INTR_MASK_T              	intr_mask;                    //0xc8006014L
	O18A0_SUB_INTR_MUX_T               	intr_mux;                     //0xc8006018L
	O18A0_SUB_INTR_EN_T                	intr_en;                      //0xc800601cL
	O18A0_SUB_CTRL_VENC_IF_T           	ctrl_venc_if;                 //0xc8006020L
	UINT32                             	reserved00_2;                //0xc8006024L~0xc8006028L
	O18A0_SUB_CTRL_DLY_CVE_PULSE_T     	ctrl_dly_cve_pulse;           //0xc800602cL
	O18A0_SUB_CTRL_CVE_SYNC_PARAM0_T   	ctrl_cve_sync_param0;         //0xc8006030L
	O18A0_SUB_CTRL_CVE_SYNC_PARAM1_T   	ctrl_cve_sync_param1;         //0xc8006034L
	O18A0_SUB_CTRL_CVE_SYNC_PARAM2_T   	ctrl_cve_sync_param2;         //0xc8006038L
	O18A0_SUB_CTRL_CVE_SYNC_PARAM3_T   	ctrl_cve_sync_param3;         //0xc800603cL
	UINT32                             	reserved01[32];               //0xc8006040L~0xc80060bcL
	O18A0_SUB_PIC_INIT_G0_TIMER_T      	pic_init_g0_timer;            //0xc80060c0L
	O18A0_SUB_PIC_INIT_G1_TIMER_T      	pic_init_g1_timer;            //0xc80060c4L
	O18A0_SUB_PIC_INIT_G2_TIMER_T      	pic_init_g2_timer;            //0xc80060c8L
	O18A0_SUB_PIC_INIT_G3_TIMER_T      	pic_init_g3_timer;            //0xc80060ccL
	O18A0_SUB_PIC_INIT_G4_TIMER_T      	pic_init_g4_timer;            //0xc80060d0L
	O18A0_SUB_PIC_INIT_G5_TIMER_T      	pic_init_g5_timer;            //0xc80060d4L
	O18A0_SUB_PIC_INIT_G6_TIMER_T      	pic_init_g6_timer;            //0xc80060d8L
	O18A0_SUB_PIC_INIT_G7_TIMER_T      	pic_init_g7_timer;            //0xc80060dcL
	UINT32                             	reserved02;                   //0xc80060e0L
	O18A0_SUB_DBG_TIMER_RUN_T          	dbg_timer_run;                //0xc80060e4L
	O18A0_SUB_DBG_TIMER_BLK_T          	dbg_timer_blk;                //0xc80060e8L
	O18A0_SUB_CTRL_MONITOR_T           	ctrl_monitor;                 //0xc80060ecL
	O18A0_SUB_CTRL_PIC_END_T           	ctrl_pic_end;                 //0xc80060f0L
	O18A0_SUB_INFO_PIC_END_T           	info_pic_end;                 //0xc80060f4L
	O18A0_SUB_CTRL_GPIO_T              	ctrl_gpio;                    //0xc80060f8L
	O18A0_SUB_CTRL_GMAU_T              	ctrl_gmau;                    //0xc80060fcL
} DE_SUB_REG_O18A0_T;

typedef struct {
	UINT32                              pic_init;        //0xC9005000
	UINT32                              pic_start;       //0xC9005004
	UINT32                              ctrl_auto_init;  //0xC9005008
	O18A0_HDR_CTRL_INTR_PULSE_T         ctrl_intr_pulse; //0xC900500C
	UINT32                              intr_reg;        //0xC9005010
	O18A0_HDR_CTRL_INTR_MASK_T          intr_mask;       //0xC9005014
	O18A0_HDR_CTRL_INTR_MUX_T           intr_mux;        //0xC9005018
	UINT32                              intr_en;         //0xC900501C
	UINT32                              ctrl0;           //0xC9005020
	UINT32                              ctrl1;           //0xC9005024
	UINT32                              ctrl2;           //0xC9005028
	UINT32                              ctrl3;           //0xC900502C
	UINT32                              reserved0[8];
	O18A0_HDR_CTRL_INTR_CPU_REG_T       intr_cpu_reg;    //0xC9005050
	O18A0_HDR_CTRL_INTR_CPU_MASK_T      intr_cpu_mask;   //0xC9005054
	UINT32                              reserved[40];    //0xC9005020 ~ 0xC90050FC
} DE_HDR_REG_O18A0_T;

#endif
