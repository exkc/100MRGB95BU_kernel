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

#ifndef _REG_PWM_E60A0_h
#define _REG_PWM_E60A0_h

/*
	PE_PWM
*/

/*-----------------------------------------------------------------------------
                             0xc9029100L PWM_INTR_STATUS_EN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_tx_intr                       :1 ,	// 0 
	pwm1_tx_intr                       :1 ,	// 1 
	pwm2_tx_intr                       :1 ,	// 2 
	pwm3_rx_intr0                      :1 ,	// 3 
	pwm3_rx_intr1                      :1 ;	// 4 
}E60A0_PE_PWM_INTR_STATUS_EN_T;
/*-----------------------------------------------------------------------------
                             0xc9029104L PWM_INTR_CLEAR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_tx_intr                       :1 ,	// 0 
	pwm1_tx_intr                       :1 ,	// 1 
	pwm2_tx_intr                       :1 ,	// 2 
	pwm3_rx_intr0                      :1 ,	// 3 
	pwm3_rx_intr1                      :1 ;	// 4 
}E60A0_PE_PWM_INTR_CLEAR_T;
/*-----------------------------------------------------------------------------
                             0xc9029108L PWM_INTR_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_tx_intr                       :1 ,	// 0 
	pwm1_tx_intr                       :1 ,	// 1 
	pwm2_tx_intr                       :1 ,	// 2 
	pwm3_rx_intr0                      :1 ,	// 3 
	pwm3_rx_intr1                      :1 ;	// 4 
}E60A0_PE_PWM_INTR_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc902910cL PWM_INTR_MASK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_tx_intr                       :1 ,	// 0 
	pwm1_tx_intr                       :1 ,	// 1 
	pwm2_tx_intr                       :1 ,	// 2 
	pwm3_rx_intr0                      :1 ,	// 3 
	pwm3_rx_intr1                      :1 ;	// 4 
}E60A0_PE_PWM_INTR_MASK_T;
/*-----------------------------------------------------------------------------
                             0xc9029110L PWM0_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_en                            :1 ,	// 0 
	pwm0_freq_mode                     :3 ,	// 3:1
	pwm0_resolution                    :2 ,	// 5:4
	pwm0_inv                           :1 ,	// 6 
	pwm0_sel                           :1 ,	// 7 
	pwm0_width_falling_pos             :24;	// 31:8
}E60A0_PE_PWM0_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9029114L PWM0_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_free_width                    :24,	// 23:0
	_rsvd_01                           :4 ,	// reserved
	pwm0_end_ctrl0                     :1 ,	// 28
	pwm0_end_ctrl1                     :1 ;	// 29
}E60A0_PE_PWM0_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9029118L PWM0_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_intr_mask                     :16,	// 15:0
	pwm0_method                        :1 ,	// 16
	pwm0_mon                           :3 ,	// 19:17
	pwm0_mux                           :4 ,	// 23:20
	pwm0_phase_mode                    :2 ,	// 25:24
	pwm0_phase_index                   :3 ,	// 28:26
	_rsvd_01                           :1 ,	// reserved
	pwm0_fc_h_disp                     :1 ,	// 30
	pwm0_fc_l_disp                     :1 ;	// 31
}E60A0_PE_PWM0_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc902911cL PWM1_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_en                            :1 ,	// 0 
	pwm1_freq_mode                     :3 ,	// 3:1
	pwm1_resolution                    :2 ,	// 5:4
	pwm1_inv                           :1 ,	// 6 
	pwm1_sel                           :1 ,	// 7 
	pwm1_width_falling_pos             :24;	// 31:8
}E60A0_PE_PWM1_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9029120L PWM1_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_free_width                    :24,	// 23:0
	_rsvd_01                           :4 ,	// reserved
	pwm1_end_ctrl0                     :1 ,	// 28
	pwm1_end_ctrl1                     :1 ;	// 29
}E60A0_PE_PWM1_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9029124L PWM1_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_intr_mask                     :16,	// 15:0
	pwm1_method                        :1 ,	// 16
	pwm1_mon                           :3 ,	// 19:17
	pwm1_mux                           :4 ,	// 23:20
	pwm1_phase_mode                    :2 ,	// 25:24
	pwm1_phase_index                   :3 ,	// 28:26
	_rsvd_01                           :1 ,	// reserved
	pwm1_fc_h_disp                     :1 ,	// 30
	pwm1_fc_l_disp                     :1 ;	// 31
}E60A0_PE_PWM1_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9029128L PWM2_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_en                            :1 ,	// 0 
	pwm2_freq_mode                     :3 ,	// 3:1
	pwm2_resolution                    :2 ,	// 5:4
	pwm2_inv                           :1 ,	// 6 
	pwm2_sel                           :1 ,	// 7 
	pwm2_width_falling_pos             :24;	// 31:8
}E60A0_PE_PWM2_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc902912cL PWM2_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_free_width                    :24,	// 23:0
	_rsvd_01                           :4 ,	// reserved
	pwm2_end_ctrl0                     :1 ,	// 28
	pwm2_end_ctrl1                     :1 ;	// 29
}E60A0_PE_PWM2_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9029130L PWM2_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_intr_mask                     :16,	// 15:0
	pwm2_method                        :1 ,	// 16
	pwm2_mon                           :3 ,	// 19:17
	pwm2_mux                           :4 ,	// 23:20
	pwm2_phase_mode                    :2 ,	// 25:24
	pwm2_phase_index                   :3 ,	// 28:26
	_rsvd_01                           :1 ,	// reserved
	pwm2_fc_h_disp                     :1 ,	// 30
	pwm2_fc_l_disp                     :1 ;	// 31
}E60A0_PE_PWM2_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9029134L PWM3_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_en                            :1 ,	// 0 
	pwm3_freq_mode                     :3 ,	// 3:1
	_rsvd_01                           :4 ,	// reserved
	pwm3_threshold                     :24;	// 31:8
}E60A0_PE_PWM3_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9029138L PWM3_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_intr_mask1                    :8 ,	// 7:0
	_rsvd_01                           :8 ,	// reserved
	pwm3_intr_mask0                    :1 ,	// 16
	_rsvd_02                           :3 ,	// reserved
	pwm3_in_mux                        :2 ;	// 21:20
}E60A0_PE_PWM3_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc902913cL PWM3_0_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_0_low                         :24;	// 23:0
}E60A0_PE_PWM3_0_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029140L PWM3_0_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_0_high                        :24;	// 23:0
}E60A0_PE_PWM3_0_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc9029144L PWM3_1_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_1_low                         :24;	// 23:0
}E60A0_PE_PWM3_1_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029148L PWM3_1_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_1_high                        :24;	// 23:0
}E60A0_PE_PWM3_1_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc902914cL PWM3_2_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_2_low                         :24;	// 23:0
}E60A0_PE_PWM3_2_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029150L PWM3_2_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_2_high                        :24;	// 23:0
}E60A0_PE_PWM3_2_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc9029154L PWM3_3_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_3_low                         :24;	// 23:0
}E60A0_PE_PWM3_3_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029158L PWM3_3_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_3_high                        :24;	// 23:0
}E60A0_PE_PWM3_3_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc902915cL PWM3_4_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_4_low                         :24;	// 23:0
}E60A0_PE_PWM3_4_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029160L PWM3_4_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_4_high                        :24;	// 23:0
}E60A0_PE_PWM3_4_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc9029164L PWM3_5_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_5_low                         :24;	// 23:0
}E60A0_PE_PWM3_5_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029168L PWM3_5_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_5_high                        :24;	// 23:0
}E60A0_PE_PWM3_5_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc902916cL PWM3_6_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_6_low                         :24;	// 23:0
}E60A0_PE_PWM3_6_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029170L PWM3_6_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_6_high                        :24;	// 23:0
}E60A0_PE_PWM3_6_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc9029174L PWM3_7_LOW                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_7_low                         :24;	// 23:0
}E60A0_PE_PWM3_7_LOW_T;
/*-----------------------------------------------------------------------------
                             0xc9029178L PWM3_7_HIGH                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_7_high                        :24;	// 23:0
}E60A0_PE_PWM3_7_HIGH_T;
/*-----------------------------------------------------------------------------
                             0xc902917cL PWM_V_LOAD_WRITE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_v_we                          :1 ,	// 0 
	pwm1_v_we                          :1 ,	// 1 
	pwm2_v_we                          :1 ,	// 2 
	pwm0_v_sub_we                      :1 ,	// 3 
	pwm1_v_sub_we                      :1 ,	// 4 
	pwm2_v_sub_we                      :1 ,	// 5 
	_rsvd_01                           :2 ,	// reserved
	pwm0_v_sub_f_we                    :1 ,	// 8 
	pwm1_v_sub_f_we                    :1 ,	// 9 
	pwm2_v_sub_f_we                    :1 ;	// 10
}E60A0_PE_PWM_V_LOAD_WRITE_T;
/*-----------------------------------------------------------------------------
                             0xc9029180L PWM0_V_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_v_r                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm0_v_r_id                        :4 ;	// 31:28
}E60A0_PE_PWM0_V_R_T;
/*-----------------------------------------------------------------------------
                             0xc9029184L PWM0_V_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_v_f                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm0_v_f_id                        :4 ;	// 31:28
}E60A0_PE_PWM0_V_F_T;
/*-----------------------------------------------------------------------------
                             0xc9029188L PWM1_V_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_v_r                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm1_v_r_id                        :4 ;	// 31:28
}E60A0_PE_PWM1_V_R_T;
/*-----------------------------------------------------------------------------
                             0xc902918cL PWM1_V_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_v_f                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm1_v_f_id                        :4 ;	// 31:28
}E60A0_PE_PWM1_V_F_T;
/*-----------------------------------------------------------------------------
                             0xc9029190L PWM2_V_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_v_r                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm2_v_r_id                        :4 ;	// 31:28
}E60A0_PE_PWM2_V_R_T;
/*-----------------------------------------------------------------------------
                             0xc9029194L PWM2_V_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_v_f                           :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm2_v_f_id                        :4 ;	// 31:28
}E60A0_PE_PWM2_V_F_T;
/*-----------------------------------------------------------------------------
                             0xc9029198L PWM0_V_SUB_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_v_sub                         :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm0_v_sub_id                      :4 ;	// 31:28
}E60A0_PE_PWM0_V_SUB_R_T;
/*-----------------------------------------------------------------------------
                             0xc902919cL PWM1_V_SUB_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_v_sub                         :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm1_v_sub_id                      :4 ;	// 31:28
}E60A0_PE_PWM1_V_SUB_R_T;
/*-----------------------------------------------------------------------------
                             0xc90291a0L PWM2_V_SUB_R                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	_rsvd_01                           :28,	// reserved
	pwm2_v_sub_id                      :4 ;	// 31:28
}E60A0_PE_PWM2_V_SUB_R_T;
/*-----------------------------------------------------------------------------
                             0xc90291a4L PWM0_LOCK_PULSE_XY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_lock_pulse_x                  :13,	// 12:0
	_rsvd_01                           :3 ,	// reserved
	pwm0_lock_pulse_y                  :13,	// 28:16
	_rsvd_02                           :2 ,	// reserved
	pwm0_lock_pulse_half_en            :1 ;	// 31
}E60A0_PE_PWM0_LOCK_PULSE_XY_T;
/*-----------------------------------------------------------------------------
                             0xc90291a8L PWM1_LOCK_PULSE_XY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_lock_pulse_x                  :13,	// 12:0
	_rsvd_01                           :3 ,	// reserved
	pwm1_lock_pulse_y                  :13,	// 28:16
	_rsvd_02                           :2 ,	// reserved
	pwm1_lock_pulse_half_en            :1 ;	// 31
}E60A0_PE_PWM1_LOCK_PULSE_XY_T;
/*-----------------------------------------------------------------------------
                             0xc90291acL PWM2_LOCK_PULSE_XY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_lock_pulse_x                  :13,	// 12:0
	_rsvd_01                           :3 ,	// reserved
	pwm2_lock_pulse_y                  :13,	// 28:16
	_rsvd_02                           :2 ,	// reserved
	pwm2_lock_pulse_half_en            :1 ;	// 31
}E60A0_PE_PWM2_LOCK_PULSE_XY_T;
/*-----------------------------------------------------------------------------
                             0xc90291b0L PWM3_LOCK_PULSE_XY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm3_lock_pulse_x                  :13,	// 12:0
	_rsvd_01                           :3 ,	// reserved
	pwm3_lock_pulse_y                  :13,	// 28:16
	_rsvd_02                           :2 ,	// reserved
	pwm3_lock_pulse_half_en            :1 ;	// 31
}E60A0_PE_PWM3_LOCK_PULSE_XY_T;
/*-----------------------------------------------------------------------------
                             0xc90291b4L PWM0_WIDTH                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291b8L PWM0_OFFSET                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291bcL PWM0_OFFSET_SUM                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291c0L PWM1_WIDTH                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291c4L PWM1_OFFSET                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291c8L PWM1_OFFSET_SUM                             
-----------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
                             0xc90291ccL PWM0_VWIDTH_MAN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_vwidth_man                    :24,	// 23:0
	pwm0_freq_offset_mode              :3 ,	// 26:24
	_rsvd_01                           :4 ,	// reserved
	pwm0_vwidth_man_en                 :1 ;	// 31
}E60A0_PE_PWM0_VWIDTH_MAN_T;
/*-----------------------------------------------------------------------------
                             0xc90291d0L PWM1_VWIDTH_MAN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_vwidth_man                    :24,	// 23:0
	pwm1_freq_offset_mode              :3 ,	// 26:24
	_rsvd_01                           :4 ,	// reserved
	pwm1_vwidth_man_en                 :1 ;	// 31
}E60A0_PE_PWM1_VWIDTH_MAN_T;
/*-----------------------------------------------------------------------------
                             0xc90291d4L PWM2_VWIDTH_MAN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_vwidth_man                    :24,	// 23:0
	pwm2_freq_offset_mode              :3 ,	// 26:24
	_rsvd_01                           :4 ,	// reserved
	pwm2_vwidth_man_en                 :1 ;	// 31
}E60A0_PE_PWM2_VWIDTH_MAN_T;
/*-----------------------------------------------------------------------------
                             0xc90291d8L PWM_MASTER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	_rsvd_01                           :16,	// reserved
	pwm_master_mode                    :3 ,	// 18:16
	_rsvd_02                           :1 ,	// reserved
	pwm2_ld_pwm                        :1 ,	// 20
	_rsvd_03                           :2 ,	// reserved
	pwm2_ld_pwm_tx_mode                :1 ,	// 23
	pwm1_ld_pwm                        :1 ,	// 24
	_rsvd_04                           :2 ,	// reserved
	pwm1_ld_pwm_tx_mode                :1 ,	// 27
	pwm0_ld_pwm                        :1 ,	// 28
	_rsvd_05                           :2 ,	// reserved
	pwm0_ld_pwm_tx_mode                :1 ;	// 31
}E60A0_PE_PWM_MASTER_T;
/*-----------------------------------------------------------------------------
                             0xc90291dcL PWM0_V_SUB_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm0_v_sub_f                       :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm0_v_sub_f_id                    :4 ;	// 31:28
}E60A0_PE_PWM0_V_SUB_F_T;
/*-----------------------------------------------------------------------------
                             0xc90291e0L PWM1_V_SUB_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm1_v_sub_f                       :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm1_v_sub_f_id                    :4 ;	// 31:28
}E60A0_PE_PWM1_V_SUB_F_T;
/*-----------------------------------------------------------------------------
                             0xc90291e4L PWM2_V_SUB_F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm2_v_sub_f                       :16,	// 15:0
	_rsvd_01                           :12,	// reserved
	pwm2_v_sub_f_id                    :4 ;	// 31:28
}E60A0_PE_PWM2_V_SUB_F_T;
/*-----------------------------------------------------------------------------
                             0xc90291ecL SW_RESET_LOCK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sw_reset_lock                      :1 ,	// 0 
	_rsvd_01                           :2 ,	// reserved
	end_mode                           :1 ,	// 3 
	vsync_sel                          :1 ,	// 4 
	_rsvd_02                           :3 ,	// reserved
	vcount_sel                         :1 ,	// 8 
	_rsvd_03                           :3 ,	// reserved
	ext_gain_apply                     :1 ,	// 12
	_rsvd_04                           :3 ,	// reserved
	hcount_num                         :16;	// 31:16
}E60A0_PE_SW_RESET_LOCK_T;
/*-----------------------------------------------------------------------------
                             0xc90291f0L PWM_TRG_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	trigger_low_num                    :28,	// 27:0
	_rsvd_01                           :2 ,	// reserved
	trigger_pt_sel                     :1 ,	// 30
	pwm_trigger_en                     :1 ;	// 31
}E60A0_PE_PWM_TRG_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc90291f4L PWM_TRG_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	trigger_high_num                   :28;	// 27:0
}E60A0_PE_PWM_TRG_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc90291f8L PWM_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pwm_gain                           :13;	// 12:0
}E60A0_PE_PWM_GAIN_T;


typedef struct
{ 
	E60A0_PE_PWM_INTR_STATUS_EN_T                    pe_pwm_intr_status_en;	//0x0000
	E60A0_PE_PWM_INTR_CLEAR_T                        pe_pwm_intr_clear;	//0x0004
	E60A0_PE_PWM_INTR_STATUS_T                       pe_pwm_intr_status;	//0x0008
	E60A0_PE_PWM_INTR_MASK_T                         pe_pwm_intr_mask;	//0x000C
	E60A0_PE_PWM0_CTRL0_T                            pe_pwm0_ctrl0;	//0x0010
	E60A0_PE_PWM0_CTRL1_T                            pe_pwm0_ctrl1;	//0x0014
	E60A0_PE_PWM0_CTRL2_T                            pe_pwm0_ctrl2;	//0x0018
	E60A0_PE_PWM1_CTRL0_T                            pe_pwm1_ctrl0;	//0x001C
	E60A0_PE_PWM1_CTRL1_T                            pe_pwm1_ctrl1;	//0x0020
	E60A0_PE_PWM1_CTRL2_T                            pe_pwm1_ctrl2;	//0x0024
	E60A0_PE_PWM2_CTRL0_T                            pe_pwm2_ctrl0;	//0x0028
	E60A0_PE_PWM2_CTRL1_T                            pe_pwm2_ctrl1;	//0x002C
	E60A0_PE_PWM2_CTRL2_T                            pe_pwm2_ctrl2;	//0x0030
	E60A0_PE_PWM3_CTRL0_T                            pe_pwm3_ctrl0;	//0x0034
	E60A0_PE_PWM3_CTRL1_T                            pe_pwm3_ctrl1;	//0x0038
	E60A0_PE_PWM3_0_LOW_T                            pe_pwm3_0_low;	//0x003C
	E60A0_PE_PWM3_0_HIGH_T                           pe_pwm3_0_high;	//0x0040
	E60A0_PE_PWM3_1_LOW_T                            pe_pwm3_1_low;	//0x0044
	E60A0_PE_PWM3_1_HIGH_T                           pe_pwm3_1_high;	//0x0048
	E60A0_PE_PWM3_2_LOW_T                            pe_pwm3_2_low;	//0x004C
	E60A0_PE_PWM3_2_HIGH_T                           pe_pwm3_2_high;	//0x0050
	E60A0_PE_PWM3_3_LOW_T                            pe_pwm3_3_low;	//0x0054
	E60A0_PE_PWM3_3_HIGH_T                           pe_pwm3_3_high;	//0x0058
	E60A0_PE_PWM3_4_LOW_T                            pe_pwm3_4_low;	//0x005C
	E60A0_PE_PWM3_4_HIGH_T                           pe_pwm3_4_high;	//0x0060
	E60A0_PE_PWM3_5_LOW_T                            pe_pwm3_5_low;	//0x0064
	E60A0_PE_PWM3_5_HIGH_T                           pe_pwm3_5_high;	//0x0068
	E60A0_PE_PWM3_6_LOW_T                            pe_pwm3_6_low;	//0x006C
	E60A0_PE_PWM3_6_HIGH_T                           pe_pwm3_6_high;	//0x0070
	E60A0_PE_PWM3_7_LOW_T                            pe_pwm3_7_low;	//0x0074
	E60A0_PE_PWM3_7_HIGH_T                           pe_pwm3_7_high;	//0x0078
	E60A0_PE_PWM_V_LOAD_WRITE_T                      pe_pwm_v_load_write;	//0x007C
	E60A0_PE_PWM0_V_R_T                              pe_pwm0_v_r;	//0x0080
	E60A0_PE_PWM0_V_F_T                              pe_pwm0_v_f;	//0x0084
	E60A0_PE_PWM1_V_R_T                              pe_pwm1_v_r;	//0x0088
	E60A0_PE_PWM1_V_F_T                              pe_pwm1_v_f;	//0x008C
	E60A0_PE_PWM2_V_R_T                              pe_pwm2_v_r;	//0x0090
	E60A0_PE_PWM2_V_F_T                              pe_pwm2_v_f;	//0x0094
	E60A0_PE_PWM0_V_SUB_R_T                          pe_pwm0_v_sub_r;	//0x0098
	E60A0_PE_PWM1_V_SUB_R_T                          pe_pwm1_v_sub_r;	//0x009C
	E60A0_PE_PWM2_V_SUB_R_T                          pe_pwm2_v_sub_r;	//0x00A0
	E60A0_PE_PWM0_LOCK_PULSE_XY_T                    pe_pwm0_lock_pulse_xy;	//0x00A4
	E60A0_PE_PWM1_LOCK_PULSE_XY_T                    pe_pwm1_lock_pulse_xy;	//0x00A8
	E60A0_PE_PWM2_LOCK_PULSE_XY_T                    pe_pwm2_lock_pulse_xy;	//0x00AC
	E60A0_PE_PWM3_LOCK_PULSE_XY_T                    pe_pwm3_lock_pulse_xy;	//0x00B0
	UINT32                                           pe_pwm0_width;	//0x00B4
	UINT32                                           pe_pwm0_offset;	//0x00B8
	UINT32                                           pe_pwm0_offset_sum;	//0x00BC
	UINT32                                           pe_pwm1_width;	//0x00C0
	UINT32                                           pe_pwm1_offset;	//0x00C4
	UINT32                                           pe_pwm1_offset_sum;	//0x00C8
	E60A0_PE_PWM0_VWIDTH_MAN_T                       pe_pwm0_vwidth_man;	//0x00CC
	E60A0_PE_PWM1_VWIDTH_MAN_T                       pe_pwm1_vwidth_man;	//0x00D0
	E60A0_PE_PWM2_VWIDTH_MAN_T                       pe_pwm2_vwidth_man;	//0x00D4
	E60A0_PE_PWM_MASTER_T                            pe_pwm_master;	//0x00D8
	E60A0_PE_PWM0_V_SUB_F_T                          pe_pwm0_v_sub_f;	//0x00DC
	E60A0_PE_PWM1_V_SUB_F_T                          pe_pwm1_v_sub_f;	//0x00E0
	E60A0_PE_PWM2_V_SUB_F_T                          pe_pwm2_v_sub_f;	//0x00E4
	UINT32                                            _rsvd_58;	//0xe8
	E60A0_PE_SW_RESET_LOCK_T                         pe_pwm_sw_reset_lock;	//0x00EC
	E60A0_PE_PWM_TRG_CTRL0_T                         pe_pwm_trg_ctrl0;	//0x00F0
	E60A0_PE_PWM_TRG_CTRL1_T                         pe_pwm_trg_ctrl1;	//0x00F4
	E60A0_PE_PWM_GAIN_T                              pe_pwm_gain;	//0x00F8
}PE_PWM_REG_E60A0_T;
#endif //#ifndef _REG_PWM_E60A0_h